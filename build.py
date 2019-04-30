import itertools

import numpy as np


bytearray_lengths = [2,4,8,10,16,20,30,32,40,50]


basic_types = [
    'str4',
    'str8',
    'str16',
    'str32',

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


value_types = [
    *[basic_type for basic_type in basic_types],

    *[f'pair_{bt}_{bt}' for bt in basic_types],

    *[f'bytearray{i}' for i in bytearray_lengths],
]


assert all([type_ in value_types for type_ in key_types])


cpp_types = {
    **{basic_type : basic_cpp_types[basic_type] for basic_type in basic_types},

    **{f'pair_{bt}_{bt}' : f'pair_{bt}_{bt}' for bt in basic_types},

    **{f'bytearray{i}' : f'bytearray{i}' for i in bytearray_lengths},
}


np_types = {
    **{basic_type : basic_np_types[basic_type] for basic_type in basic_types},

    **{f'pair_{bt}_{bt}' : {'names' : ['first', 'second'], 'formats' : [basic_np_types[bt], basic_np_types[bt]]} for bt in basic_types},

    **{f'bytearray{i}' : {'names' : ['bytearray'], 'formats' : [f'{i}u1']} for i in bytearray_lengths},
}


struct_types = {
    **{f'pair_{bt}_{bt}' : f'struct pair_{bt}_{bt} {{ {basic_cpp_types[bt]} first; {basic_cpp_types[bt]} second; }};' for bt in basic_types},

    **{f'bytearray{i}' : f'struct bytearray{i} {{ std::array<uint8_t, {i}> bytearray; }};' for i in bytearray_lengths},
}


def create_class_name(key_type, value_type):
    return f'Dict_{key_type}_{value_type}'


def write_dict_types_dict(getpy_file, key_type, value_type):
    class_name = create_class_name(key_type, value_type)
    getpy_file.write(f"    (types['{key_type}'], types['{value_type}']) : _gp.{class_name},\n")


def write_struct_types(getpy_file, type_):
    getpy_file.write(f'{struct_types[type_]}\n')


def write_struct_serialization(getpy_file, type_):
    if type_.startswith('pair'):
        getpy_file.write(f'template<class Archive> void serialize(Archive & archive, {type_} & pair) {{ archive( pair.first, pair.second ); }}\n')

    elif type_.startswith('bytearray'):
        getpy_file.write(f'template<class Archive> void serialize(Archive & archive, {type_} & bytearray) {{ archive( bytearray.bytearray ); }}\n')

    else:
        pass


def write_struct_operators(getpy_file, type_):
    if type_.startswith('pair'):
        getpy_file.write(f'{type_} & operator += ( {type_} & a, {type_} b ) {{ a.first += b.first; a.second += b.second; }}\n')
        getpy_file.write(f'{type_} & operator -= ( {type_} & a, {type_} b ) {{ a.first -= b.first; a.second -= b.second; }}\n')

        if 'float' not in type_:
            getpy_file.write(f'{type_} & operator |= ( {type_} & a, {type_} b ) {{ a.first |= b.first; a.second |= b.second; }}\n')
            getpy_file.write(f'{type_} & operator &= ( {type_} & a, {type_} b ) {{ a.first &= b.first; a.second &= b.second; }}\n')
        else:
            pass

    elif type_.startswith('bytearray'):
        getpy_file.write(f'{type_} & operator += ( {type_} & a, {type_} b ) {{ a.bytearray += b.bytearray; }}\n')
        getpy_file.write(f'{type_} & operator -= ( {type_} & a, {type_} b ) {{ a.bytearray -= b.bytearray; }}\n')
        getpy_file.write(f'{type_} & operator |= ( {type_} & a, {type_} b ) {{ a.bytearray |= b.bytearray; }}\n')
        getpy_file.write(f'{type_} & operator &= ( {type_} & a, {type_} b ) {{ a.bytearray &= b.bytearray; }}\n')

    else:
        pass


def write_numpy_dtype(getpy_file, type_):
    if type_.startswith('pair'):
        getpy_file.write(f'    PYBIND11_NUMPY_DTYPE({cpp_types[type_]}, first, second );\n')

    elif type_.startswith('bytearray'):
        getpy_file.write(f'    PYBIND11_NUMPY_DTYPE({cpp_types[type_]}, bytearray );\n')

    else:
        pass


def write_declare_dict(getpy_file, key_type, value_type):
    class_name = create_class_name(key_type, value_type)

    if 'float' in value_type:
        getpy_file.write(f'    declare_dict_without_bitwise_operations<{cpp_types[key_type]}, {cpp_types[value_type]}>(m, "{class_name}");\n')
    else:
        getpy_file.write(f'    declare_dict<{cpp_types[key_type]}, {cpp_types[value_type]}>(m, "{class_name}");\n')


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
            if type_ in struct_types:
                write_struct_types(getpy_file, type_)
                write_struct_serialization(getpy_file, type_)
                write_struct_operators(getpy_file, type_)
                getpy_file.write('\n')
            else:
                pass

        getpy_file.write("""\

PYBIND11_MODULE(_getpy, m) {
    m.doc() = "A Fast and Memory Efficient Hash Map for Python";

""")

        for type_ in value_types:
            if type_ in struct_types:
                write_numpy_dtype(getpy_file, type_)
            else:
                pass

        getpy_file.write('\n')

        for key_type, value_type in itertools.product(key_types, value_types):
            write_declare_dict(getpy_file, key_type, value_type)

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

if __name__ == '__main__':
    write_getpy_cpp(key_types, value_types)
    write_getpy_py(key_types, value_types)
