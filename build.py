import itertools

import numpy as np

key_types = ['uint8_t', 'uint16_t', 'uint32_t', 'uint64_t',
             'int8_t', 'int16_t', 'int32_t', 'int64_t']

value_types = ['uint8_t', 'uint16_t', 'uint32_t', 'uint64_t',
               'int8_t', 'int16_t', 'int32_t', 'int64_t']

type_names = {
    'int8_t' : 'Int8',
    'int16_t' : 'Int16',
    'int32_t' : 'Int32',
    'int64_t' : 'Int64',

    'uint8_t' : 'Uint8',
    'uint16_t' : 'Uint16',
    'uint32_t' : 'Uint32',
    'uint64_t' : 'Uint64',
}

np_types = {
    'int8_t' : 'np.int8',
    'int16_t' : 'np.int16',
    'int32_t' : 'np.int32',
    'int64_t' : 'np.int64',

    'uint8_t' : 'np.uint8',
    'uint16_t' : 'np.uint16',
    'uint32_t' : 'np.uint32',
    'uint64_t' : 'np.uint64',
}

def create_class_name(key_type, value_type):
    return f'_Dict_{type_names[key_type]}_{type_names[value_type]}'

def write_sparsepy_cpp(key_types, value_types):
    with open('src/_sparsepy.cpp', 'w') as sparsepy_file:
        sparsepy_file.write("""\
#include "_sparsepy_util.cpp"

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

types_dict = {
""")

        def write_type_dict(sparsepy_file, key_type, value_type):
            class_name = create_class_name(key_type, value_type)
            sparsepy_file.write(f'    ({np_types[key_type]}, {np_types[value_type]}) : {class_name},\n')

        for key_type, value_type in itertools.product(key_types, value_types):
            write_type_dict(sparsepy_file, key_type, value_type)

        sparsepy_file.write("""\
}
""")

if __name__ == '__main__':
    write_sparsepy_cpp(key_types, value_types)
    write_sparsepy_py(key_types, value_types)
