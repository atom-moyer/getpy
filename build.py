import itertools

import numpy as np


key_types = [
    'uint32', 'uint64',
    'int32', 'int64',

    'str',
]

value_types = [
    # 'ubyte',
    # 'ubyte_2', 'ubyte_4', 'ubyte_8', 'ubyte_16', 'ubyte_32',

    # 'byte',
    # 'byte_2', 'byte_4', 'byte_8', 'byte_16', 'byte_32',

    'uint8', 'uint16', 'uint32', 'uint64',
    # 'uint8_2', 'uint8_4', 'uint8_8', 'uint8_16', 'uint8_32',
    # 'uint16_2', 'uint16_4', 'uint16_8', 'uint16_16', 'uint16_32',
    # 'uint32_2', 'uint32_4', 'uint32_8', 'uint32_16', 'uint32_32',
    # 'uint64_2', 'uint64_4', 'uint64_8', 'uint64_16', 'uint64_32',

    'int8', 'int16', 'int32', 'int64',
    # 'int8_2', 'int8_4', 'int8_8', 'int8_16', 'int8_32',
    # 'int16_2', 'int16_4', 'int16_8', 'int16_16', 'int16_32',
    # 'int32_2', 'int32_4', 'int32_8', 'int32_16', 'int32_32',
    # 'int64_2', 'int64_4', 'int64_8', 'int64_16', 'int64_32',

    'bool',
    #'bool_2', 'bool_4', 'bool_8', 'bool_16', 'bool_32', 'bool_64', 'bool_128', 'bool_256',

    # 'float16',
    'float32', 'float64',

    'str',

    # 'pyobject',
]

no_vec_support_types = {
    'ubyte',
    'ubyte_2', 'ubyte_4', 'ubyte_8', 'ubyte_16', 'ubyte_32',

    'byte',

    'bool_2', 'bool_4', 'bool_8', 'bool_16', 'bool_32', 'bool_64', 'bool_128', 'bool_256',

    'str',

    'pyobject',
}

cpp_types = {
    'ubyte' : 'unsigned char',
    'ubyte_v' : 'std::vector<unsigned char>',
    'ubyte_2' : 'std::array<unsigned char, 2>',
    'ubyte_4' : 'std::array<unsigned char, 4>',
    'ubyte_8' : 'std::array<unsigned char, 8>',
    'ubyte_16' : 'std::array<unsigned char, 16>',
    'ubyte_32' : 'std::array<unsigned char, 32>',

    'byte' : 'char',
    'byte_v' : 'py::str',
    'byte_2' : 'std::array<char, 2>',
    'byte_4' : 'std::array<char, 4>',
    'byte_8' : 'std::array<char, 8>',
    'byte_16' : 'std::array<char, 16>',
    'byte_32' : 'std::array<char, 32>',

    'int8' : 'int8_t',
    'int16' : 'int16_t',
    'int32' : 'int32_t',
    'int64' : 'int64_t',
    'int128' : 'int128_t',

    'uint8' : 'uint8_t',
    'uint16' : 'uint16_t',
    'uint32' : 'uint32_t',
    'uint64' : 'uint64_t',
    'uint128' : 'uint128_t',

    'float16' : 'half',
    'float32' : 'float',
    'float64' : 'double',

    'bool' : 'bool',
    'bool_2' : 'std::array<bool, 2>',
    'bool_4' : 'std::array<bool, 4>',
    'bool_8' : 'std::array<bool, 8>',
    'bool_16' : 'std::array<bool, 16>',
    'bool_32' : 'std::array<bool, 32>',
    'bool_64' : 'std::array<bool, 64>',
    'bool_128' : 'std::array<bool, 128>',
    'bool_256' : 'std::array<bool, 256>',

    'str' : 'std::string',

    'pyobject' : 'py::object',
}

np_types = {
    'ubyte' : ['b'],
    'ubyte_2' : ['2b'],
    'ubyte_4' : ['4b'],
    'ubyte_8' : ['8b'],
    'ubyte_16' : ['16b'],
    'ubyte_32' : ['32b'],

    'byte' : ['B'],
    'byte_2' : ['2B'],
    'byte_4' : ['4B'],
    'byte_8' : ['8B'],
    'byte_16' : ['16B'],
    'byte_32' : ['32B'],

    'int8' : ['i1', 'int8'],
    'int16' : ['i2', 'int16'],
    'int32' : ['i4', 'int32'],
    'int64' : ['i8', 'int64'],
    'int128' : ['i16', 'int128'],

    'uint8' : ['u1', 'uint8'],
    'uint16' : ['u2', 'uint16'],
    'uint32' : ['u4', 'uint32'],
    'uint64' : ['u8', 'uint64'],
    'uint128' : ['u16', 'uint128'],

    'float16' : ['f2', 'float16'],
    'float32' : ['f4', 'float32'],
    'float64' : ['f8', 'float64'],

    'bool' : ['?', 'bool'],
    'bool_2' : ['2?'],
    'bool_4' : ['4?'],
    'bool_8' : ['8?'],
    'bool_16' : ['16?'],
    'bool_32' : ['32?'],
    'bool_64' : ['64?'],
    'bool_128' : ['128?'],
    'bool_256' : ['256?'],

    'str' : ['U'],

    'pyobject' : ['O'],
}


def create_class_name(key_type, value_type):
    return f'_Dict_{key_type}_{value_type}'


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

        def write_declare_dict_no_vec(sparsepy_file, key_type, value_type):
            class_name = create_class_name(key_type, value_type)
            sparsepy_file.write(f'\tdeclare_dict_no_vec<{key_type}, {value_type}>(m, "{class_name}");\n')

        for key_type, value_type in itertools.product(key_types, value_types):

            if (key_type in no_vec_support_types) or (value_type in no_vec_support_types):
                write_declare_dict_no_vec(sparsepy_file, key_type, value_type)
            else:
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
