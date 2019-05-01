import itertools

import numpy as np


bytearray_lengths = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                     20, 30, 32, 40, 50, 60, 64, 70, 80, 90, 100, 128]
byte8array_lengths = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]


basic_types = [
    'str4',
    'str8',

    'uint8',
    'uint16',
    'uint32',
    'uint64',

    'int8',
    'int16',
    'int32',
    'int64',

    'float32',
    'float64',
]


basic_cpp_types = {
    'str4' : 'std::array<char, 4>',
    'str8' : 'std::array<char, 8>',
    'str16' : 'std::array<char, 16>',
    'str32' : 'std::array<char, 32>',

    'int8' : 'int8_t',
    'int16' : 'int16_t',
    'int32' : 'int32_t',
    'int64' : 'int64_t',

    'uint8' : 'uint8_t',
    'uint16' : 'uint16_t',
    'uint32' : 'uint32_t',
    'uint64' : 'uint64_t',

    'float32' : 'float',
    'float64' : 'double',
}


basic_np_types = {
    'str4' : 'U4',
    'str8' : 'U8',
    'str16' : 'U16',
    'str32' : 'U32',

    'int8' : 'i1',
    'int16' : 'i2',
    'int32' : 'i4',
    'int64' : 'i8',

    'uint8' : 'u1',
    'uint16' : 'u2',
    'uint32' : 'u4',
    'uint64' : 'u8',

    'float32' : 'f4',
    'float64' : 'f8',
}


key_types = [
    'str4',
    'str8',

    'uint32',
    'uint64',

    'int32',
    'int64',
]


set_key_types = [
    'str4',
    'str8',

    'uint32',
    'uint64',

    'int32',
    'int64',

    *[f'bytearray{i}' for i in bytearray_lengths],

    *[f'byte8array{i}' for i in byte8array_lengths],
]


value_types = [
    *[basic_type for basic_type in basic_types],

    *[f'bytearray{i}' for i in bytearray_lengths],

    *[f'byte8array{i}' for i in byte8array_lengths],
]


assert all([type_ in value_types for type_ in key_types + set_key_types])


cpp_types = {
    **{basic_type : basic_cpp_types[basic_type] for basic_type in basic_types},

    **{f'bytearray{i}' : f'bytearray{i}' for i in bytearray_lengths},

    **{f'byte8array{i}' : f'byte8array{i}' for i in byte8array_lengths},
}


np_types = {
    **{basic_type : basic_np_types[basic_type] for basic_type in basic_types},

    **{f'bytearray{i}' : {'names' : ['bytearray'], 'formats' : [f'{i}u1']} for i in bytearray_lengths},

    **{f'byte8array{i}' : {'names' : ['bytearray'], 'formats' : [f'{i}u8']} for i in byte8array_lengths},
}


generic_types = {
    **{f'bytearray{i}' : f'using bytearray{i} = bytearray<uint8_t, {i}>;' for i in bytearray_lengths},

    **{f'byte8array{i}' : f'using byte8array{i} = bytearray<uint64_t, {i}>;' for i in byte8array_lengths},
}


def create_dict_class_name(key_type, value_type):
    return f'Dict_{key_type}_{value_type}'


def create_set_class_name(key_type):
    return f'Set_{key_type}'


def write_dict_types_dict(getpy_file, key_type, value_type):
    class_name = create_dict_class_name(key_type, value_type)
    getpy_file.write(f"    (types['{key_type}'], types['{value_type}']) : _gp.{class_name},\n")


def write_set_types_dict(getpy_file, key_type):
    class_name = create_set_class_name(key_type)
    getpy_file.write(f"    (types['{key_type}']) : _gp.{class_name},\n")


def write_generic_types(getpy_file, type_):
    getpy_file.write(f'{generic_types[type_]}\n')


def write_numpy_dtype(getpy_file, type_):
    if type_.startswith('bytearray') or type_.startswith('byte8array'):
        getpy_file.write(f'    PYBIND11_NUMPY_DTYPE( {cpp_types[type_]}, bytearray );\n')

    else:
        pass


def write_declare_dict(getpy_file, key_type, value_type):
    class_name = create_dict_class_name(key_type, value_type)

    if 'float' in value_type:
        getpy_file.write(f'    declare_dict_without_bitwise_operations<{cpp_types[key_type]}, {cpp_types[value_type]}>(m, "{class_name}");\n')
    else:
        getpy_file.write(f'    declare_dict<{cpp_types[key_type]}, {cpp_types[value_type]}>(m, "{class_name}");\n')


def write_declare_set(getpy_file, key_type):
    class_name = create_set_class_name(key_type)

    getpy_file.write(f'    declare_set<{cpp_types[key_type]}>(m, "{class_name}");\n')


def write_types_dict(getpy_file, type_):
    if isinstance(np_types[type_], dict):
        getpy_file.write(f"    '{type_}' : np.dtype({np_types[type_]}),\n")
    else:
        getpy_file.write(f"    '{type_}' : np.dtype('{np_types[type_]}'),\n")


def write_getpy_cpp(key_types, value_types):
    with open('src/getpy_types.cpp', 'w') as getpy_file:
        getpy_file.write("""\
#include "getpy.cpp"

#include <pybind11/pybind11.h>

""")

        for type_ in value_types:
            if type_ in generic_types:
                write_generic_types(getpy_file, type_)
            else:
                pass

        getpy_file.write("""\

PYBIND11_MODULE(_getpy, m) {
    m.doc() = "A Fast and Memory Efficient Hash Map for Python";

""")

        for type_ in value_types:
            if type_ in generic_types:
                write_numpy_dtype(getpy_file, type_)
            else:
                pass

        getpy_file.write('\n')

        for key_type, value_type in itertools.product(key_types, value_types):
            write_declare_dict(getpy_file, key_type, value_type)

        getpy_file.write('\n')

        for key_type in set_key_types:
            write_declare_set(getpy_file, key_type)

        getpy_file.write("""\
}
""")


def write_getpy_py(key_types, value_types):
    with open('getpy/getpy_types.py', 'w') as getpy_file:
        getpy_file.write("""\
import numpy as np

import _getpy as _gp

types = {
""")

        for value_type in value_types:
            write_types_dict(getpy_file, value_type)

        getpy_file.write("""\
}
""")

        getpy_file.write("""\

dict_types = {
""")

        for key_type, value_type in itertools.product(key_types, value_types):
            write_dict_types_dict(getpy_file, key_type, value_type)

        getpy_file.write("""\
}
""")


        getpy_file.write("""\

set_types = {
""")

        for key_type in set_key_types:
            write_set_types_dict(getpy_file, key_type)

        getpy_file.write("""\
}
""")

if __name__ == '__main__':
    write_getpy_cpp(key_types, value_types)
    write_getpy_py(key_types, value_types)
