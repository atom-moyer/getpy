import itertools

import numpy as np


key_types = [
    'str4',
    'str8',

    'uint32',
    'uint64',

    'int32',
    'int64',
]

value_types = [
    'str1',
    'str2',
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

    'bool',
]

cpp_types = {
    'str1' : 'std::array<char, 1>',
    'str2' : 'std::array<char, 2>',
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

    'bool' : 'bool',
}

np_types = {
    'str1' : ['U1'],
    'str2' : ['U2'],
    'str4' : ['U4'],
    'str8' : ['U8'],
    'str16' : ['U16'],
    'str32' : ['U32'],

    'int8' : ['i1', 'int8'],
    'int16' : ['i2', 'int16'],
    'int32' : ['i4', 'int32'],
    'int64' : ['i8', 'int64'],

    'uint8' : ['u1', 'uint8'],
    'uint16' : ['u2', 'uint16'],
    'uint32' : ['u4', 'uint32'],
    'uint64' : ['u8', 'uint64'],

    'float32' : ['f4', 'float32'],
    'float64' : ['f8', 'float64'],

    'bool' : ['?', 'bool'],
}


def create_class_name(key_type, value_type):
    return f'Dict_{key_type}_{value_type}'


def write_getpy_cpp(key_types, value_types):
    with open('src/getpy_types.cpp', 'w') as getpy_file:
        getpy_file.write("""\
#include "getpy.cpp"

#include <pybind11/pybind11.h>

""")
        def write_usings(getpy_file, key_types, value_types):
            types = list(set(key_types + value_types))

            for type_ in types:
                if type_ == cpp_types[type_]:
                    continue
                else:
                    getpy_file.write(f'using {type_} = {cpp_types[type_]};\n')

        write_usings(getpy_file, key_types, value_types)

        getpy_file.write("""\

PYBIND11_MODULE(_getpy, m) {
    m.doc() = "A Fast and Memory Efficient Hash Map for Python";

""")

        def write_declare_dict(getpy_file, key_type, value_type):
            class_name = create_class_name(key_type, value_type)
            getpy_file.write(f'\tdeclare_dict<{key_type}, {value_type}>(m, "{class_name}");\n')

        for key_type, value_type in itertools.product(key_types, value_types):
            write_declare_dict(getpy_file, key_type, value_type)

        getpy_file.write("""\
}
""")


def write_getpy_py(key_types, value_types):
    with open('getpy/getpy_types.py', 'w') as getpy_file:
        getpy_file.write("""\
import numpy as np

""")

        def write_import(getpy_file, key_type, value_type):
            class_name = create_class_name(key_type, value_type)
            getpy_file.write(f'from _getpy import {class_name}\n')

        for key_type, value_type in itertools.product(key_types, value_types):
            write_import(getpy_file, key_type, value_type)

        getpy_file.write("""\

types = {
""")

        def write_type_dict(getpy_file, key_type, value_type):
            class_name = create_class_name(key_type, value_type)

            for kt in np_types[key_type]:
                for vt in np_types[value_type]:
                    getpy_file.write(f'\t(np.dtype("{kt}"), np.dtype("{vt}")) : {class_name},\n')

        for key_type, value_type in itertools.product(key_types, value_types):
            write_type_dict(getpy_file, key_type, value_type)

        getpy_file.write("""\
}
""")

if __name__ == '__main__':
    write_getpy_cpp(key_types, value_types)
    write_getpy_py(key_types, value_types)
