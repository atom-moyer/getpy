import itertools

import numpy as np


byteset_lengths = [4, 8, 12, 16, 20, 24, 28, 32]


key_types = [
    'uint32',
    'uint64',

    'int32',
    'int64',

    *[f'byteset{i}' for i in byteset_lengths],
]


value_types = [
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

    *[f'byteset{i}' for i in byteset_lengths]
]


cpp_types = {
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

    **{f'byteset{i}' : f'std::array<char,{i}>' for i in byteset_lengths},
}


np_types = {
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

    **{f'byteset{i}' : f'S{i}' for i in byteset_lengths},
}


def write_dict_types_dict(getpy_file, key_type, value_type):
    getpy_file.write(f"    (types['{key_type}'], types['{value_type}']) : _gp.Dict_{key_type}_{value_type},\n")


def write_set_types_dict(getpy_file, key_type):
    getpy_file.write(f"    (types['{key_type}']) : _gp.Set_{key_type},\n")


def write_declare_dict(getpy_file, key_type, value_type):
    getpy_file.write(f'    declare_dict<{cpp_types[key_type]}, {cpp_types[value_type]}>(m, "Dict_{key_type}_{value_type}");\n')


def write_declare_set(getpy_file, key_type):
    getpy_file.write(f'    declare_set<{cpp_types[key_type]}>(m, "Set_{key_type}");\n')


def write_types_dict(getpy_file, type_):
    getpy_file.write(f"    '{type_}' : np.dtype('{np_types[type_]}'),\n")


def write_getpy_cpp(key_types, value_types):
    with open('src/getpy_types.cpp', 'w') as getpy_file:
        getpy_file.write("""\
#include "getpy.cpp"

#include <pybind11/pybind11.h>

PYBIND11_MODULE(_getpy, m) {
    m.doc() = "A Fast and Memory Efficient Hash Map for Python";

""")

        for key_type, value_type in itertools.product(key_types, value_types):
            write_declare_dict(getpy_file, key_type, value_type)

        getpy_file.write('\n')

        for key_type in key_types:
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

        for key_type in key_types:
            write_set_types_dict(getpy_file, key_type)

        getpy_file.write("""\
}
""")

if __name__ == '__main__':
    write_getpy_cpp(key_types, value_types)
    write_getpy_py(key_types, value_types)
