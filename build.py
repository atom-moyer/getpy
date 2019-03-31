import itertools

import numpy as np


key_types = ['uint8_t', 'uint16_t', 'uint32_t', 'uint64_t',
             'int8_t', 'int16_t', 'int32_t', 'int64_t',]


value_types = ['uint8_t', 'uint16_t', 'uint32_t', 'uint64_t',
               'int8_t', 'int16_t', 'int32_t', 'int64_t',
               'float', 'double', 'bool']


np_types = {
    'int8_t' : 'i1',
    'int16_t' : 'i2',
    'int32_t' : 'i4',
    'int64_t' : 'i8',

    'uint8_t' : 'u1',
    'uint16_t' : 'u2',
    'uint32_t' : 'u4',
    'uint64_t' : 'u8',

    'float' : 'f4',
    'double' : 'f8',
    'bool' : '?',
}


def create_class_name(key_type, value_type):
    return f'_Dict_{key_type}_{value_type}'


def write_sparsepy_cpp(key_types, value_types):
    with open('src/_sparsepy_types.cpp', 'w') as sparsepy_file:
        sparsepy_file.write("""\
#include "_sparsepy.cpp"

#include <pybind11/pybind11.h>

PYBIND11_MODULE(_sparsepy, m) {
    m.doc() = "Fast and Memory Efficient Sparse Hash Tables for Python";

""")

        def write_declare_dict(sparsepy_file, key_type, value_type):
            class_name = create_class_name(key_type, value_type)
            sparsepy_file.write(f'    declare_dict<{key_type}, {value_type}>(m, "{class_name}");\n')

        for key_type, value_type in itertools.product(key_types, value_types):
            write_declare_dict(sparsepy_file, key_type, value_type)

        sparsepy_file.write("""\
}
""")


def write_sparsepy_py(key_types, value_types):
    with open('sparsepy/sparsepy_types.py', 'w') as sparsepy_file:
        sparsepy_file.write("""\
import numpy as np

""")

        def write_import(sparsepy_file, key_type, value_type):
            class_name = create_class_name(key_type, value_type)
            sparsepy_file.write(f'from _sparsepy import {class_name}\n')

        for key_type, value_type in itertools.product(key_types, value_types):
            write_import(sparsepy_file, key_type, value_type)

        sparsepy_file.write("""\

_types = {
""")

        def write_type_dict(sparsepy_file, key_type, value_type):
            class_name = create_class_name(key_type, value_type)
            sparsepy_file.write(f'\t(np.dtype("{np_types[key_type]}"), np.dtype("{np_types[value_type]}")) : {class_name},\n')

        for key_type, value_type in itertools.product(key_types, value_types):
            write_type_dict(sparsepy_file, key_type, value_type)

        sparsepy_file.write("""\
}
""")

if __name__ == '__main__':
    write_sparsepy_cpp(key_types, value_types)
    write_sparsepy_py(key_types, value_types)
