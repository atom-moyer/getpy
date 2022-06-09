import itertools

import numpy as np


# byteset_lengths = [4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64]
byteset_lengths = [8, 16, 32, 64, 128, 256]

key_types = [
    'u4',
    'u8',

    'i4',
    'i8',

    *[f'S{i}' for i in byteset_lengths],
]


value_types = [
    'u1',
    'u2',
    'u4',
    'u8',

    'i1',
    'i2',
    'i4',
    'i8',

    'f4',
    'f8',

    *[f'S{i}' for i in byteset_lengths]
]


cpp_types = {
    'i1' : 'int8_t',
    'i2' : 'int16_t',
    'i4' : 'int32_t',
    'i8' : 'int64_t',

    'u1' : 'uint8_t',
    'u2' : 'uint16_t',
    'u4' : 'uint32_t',
    'u8' : 'uint64_t',

    'f4' : 'float',
    'f8' : 'double',

    **{f'S{i}' : f'std::array<char,{i}>' for i in byteset_lengths},
}


def write_dict_types_dict(getpy_file, key_type, value_type):
    getpy_file.write(f"    (np.dtype('{key_type}'), np.dtype('{value_type}')) : _gp.Dict_{key_type}_{value_type},\n")


def write_set_types_dict(getpy_file, key_type):
    getpy_file.write(f"    np.dtype('{key_type}') : _gp.Set_{key_type},\n")


def write_multidict_types_dict(getpy_file, key_type, value_type):
    getpy_file.write(f"    (np.dtype('{key_type}'), np.dtype('{value_type}')) : _gp.MultiDict_{key_type}_{value_type},\n")


def write_declare_dict(getpy_file, key_type, value_type):
    getpy_file.write(f'    declare_dict<{cpp_types[key_type]}, {cpp_types[value_type]}>(m, "Dict_{key_type}_{value_type}");\n')


def write_declare_set(getpy_file, key_type):
    getpy_file.write(f'    declare_set<{cpp_types[key_type]}>(m, "Set_{key_type}");\n')


def write_declare_multidict(getpy_file, key_type, value_type):
    getpy_file.write(f'    declare_multidict<{cpp_types[key_type]}, {cpp_types[value_type]}>(m, "MultiDict_{key_type}_{value_type}");\n')


def write_getpy_cpp(key_types, value_types):
    with open('src/getpy_types.cpp', 'w') as getpy_file:
        getpy_file.write("""\
#include "getpy.cpp"

#include <pybind11/pybind11.h>

PYBIND11_MODULE(_getpy, m) {

""")

        for key_type, value_type in itertools.product(key_types, value_types):
            write_declare_dict(getpy_file, key_type, value_type)

        getpy_file.write('\n')

        for key_type in key_types:
            write_declare_set(getpy_file, key_type)

        getpy_file.write('\n')

        for key_type, value_type in itertools.product(key_types, key_types):
            write_declare_multidict(getpy_file, key_type, value_type)

        getpy_file.write("""\
}
""")


def write_getpy_py(key_types, value_types):
    with open('getpy/getpy_types.py', 'w') as getpy_file:
        getpy_file.write("""\
import numpy as np

import _getpy as _gp

dict_types = {
""")

        for key_type, value_type in itertools.product(key_types, value_types):
            write_dict_types_dict(getpy_file, key_type, value_type)

        getpy_file.write("""\
}

set_types = {
""")

        for key_type in key_types:
            write_set_types_dict(getpy_file, key_type)

        getpy_file.write("""\
}

multidict_types = {
""")

        for key_type, value_type in itertools.product(key_types, key_types):
            write_multidict_types_dict(getpy_file, key_type, value_type)

        getpy_file.write("""\
}
""")

if __name__ == '__main__':
    write_getpy_cpp(key_types, value_types)
    write_getpy_py(key_types, value_types)
