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


def write_sparsepy_cpp(key_types, value_types):
    with open('src/_sparsepy_types.cpp', 'w') as sparsepy_file:
        sparsepy_file.write("""\
#include "_sparsepy.cpp"

#include <pybind11/pybind11.h>

""")
        def write_usings(sparsepy_file, key_types, value_types):
            types = list(set(key_types + value_types))

            for type_ in types:
                if type_ == cpp_types[type_]:
                    continue
                else:
                    sparsepy_file.write(f'using {type_} = {cpp_types[type_]};\n')

        write_usings(sparsepy_file, key_types, value_types)

        sparsepy_file.write("""\

PYBIND11_MODULE(_sparsepy, m) {
    m.doc() = "Fast and Memory Efficient Sparse Hash Tables for Python";

""")

        def write_declare_dict(sparsepy_file, key_type, value_type):
            class_name = create_class_name(key_type, value_type)
            sparsepy_file.write(f'\tdeclare_dict<{key_type}, {value_type}>(m, "{class_name}");\n')


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

            for kt in np_types[key_type]:
                for vt in np_types[value_type]:
                    sparsepy_file.write(f'\t(np.dtype("{kt}"), np.dtype("{vt}")) : {class_name},\n')

        for key_type, value_type in itertools.product(key_types, value_types):
            write_type_dict(sparsepy_file, key_type, value_type)

        sparsepy_file.write("""\
}
""")

if __name__ == '__main__':
    write_sparsepy_cpp(key_types, value_types)
    write_sparsepy_py(key_types, value_types)
