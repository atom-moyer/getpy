import itertools

import numpy as np

amino_acids = ['A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L',
               'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'Y']

key_types = [
    'str4',
    'str8',

    'uint32',
    'uint64',
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

    # 'pair_str1_str1',
    # 'pair_str2_str2',
    # 'pair_str4_str4',
    # 'pair_str8_str8',
    # 'pair_str16_str16',
    # 'pair_str32_str32',
    #
    # 'pair_uint8_uint8',
    # 'pair_uint16_uint16',
    # 'pair_uint32_uint32',
    # 'pair_uint64_uint64',
    #
    # 'pair_int8_int8',
    # 'pair_int16_int16',
    # 'pair_int32_int32',
    # 'pair_int64_int64',
    #
    # 'pair_float32_float32',
    # 'pair_float64_float64',
    # 
    # 'rparray',
    #
    # 'rotation_uint16',
    # 'translation_uint16',
    #
    # 'pair_rotation_uint16_translation_uint16',
]


assert all([type_ in value_types for type_ in key_types])


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

    'pair_str1_str1' : 'pair_str1_str1',
    'pair_str2_str2' : 'pair_str2_str2',
    'pair_str4_str4' : 'pair_str4_str4',
    'pair_str8_str8' : 'pair_str8_str8',
    'pair_str16_str16' : 'pair_str16_str16',
    'pair_str32_str32' : 'pair_str32_str32',

    'pair_int8_int8' : 'pair_int8_int8',
    'pair_int16_int16' : 'pair_int16_int16',
    'pair_int32_int32' : 'pair_int32_int32',
    'pair_int64_int64' : 'pair_int64_int64',

    'pair_uint8_uint8' : 'pair_uint8_uint8',
    'pair_uint16_uint16' : 'pair_uint16_uint16',
    'pair_uint32_uint32' : 'pair_uint32_uint32',
    'pair_uint64_uint64' : 'pair_uint64_uint64',

    'pair_float32_float32' : 'pair_float32_float32',
    'pair_float64_float64' : 'pair_float64_float64',

    'rparray' : 'std::array<uint8_t, 50>',

    'rotation_uint16' : 'rotation_uint16',
    'translation_uint16' : 'translation_uint16',

    'pair_rotation_uint16_translation_uint16' : 'pair_rotation_uint16_translation_uint16',
}


np_types = {
    'str1' : ['U1'],
    'str2' : ['U2'],
    'str4' : ['U4'],
    'str8' : ['U8'],
    'str16' : ['U16'],
    'str32' : ['U32'],

    'int8' : ['i1'],
    'int16' : ['i2'],
    'int32' : ['i4'],
    'int64' : ['i8'],

    'uint8' : ['u1'],
    'uint16' : ['u2'],
    'uint32' : ['u4'],
    'uint64' : ['u8'],

    'float32' : ['f4'],
    'float64' : ['f8'],

    'bool' : ['?'],

    'pair_str1_str1' : [{'names' : ['first', 'second'], 'formats' : ['U1', 'U1']}],
    'pair_str2_str2' : [{'names' : ['first', 'second'], 'formats' : ['U2', 'U2']}],
    'pair_str4_str4' : [{'names' : ['first', 'second'], 'formats' : ['U4', 'U4']}],
    'pair_str8_str8' : [{'names' : ['first', 'second'], 'formats' : ['U8', 'U8']}],
    'pair_str16_str16' : [{'names' : ['first', 'second'], 'formats' : ['U16', 'U16']}],
    'pair_str32_str32' : [{'names' : ['first', 'second'], 'formats' : ['U32', 'U32']}],

    'pair_int8_int8' : [{'names' : ['first', 'second'], 'formats' : ['i1', 'i1']}],
    'pair_int16_int16' : [{'names' : ['first', 'second'], 'formats' : ['i2', 'i2']}],
    'pair_int32_int32' : [{'names' : ['first', 'second'], 'formats' : ['i4', 'i4']}],
    'pair_int64_int64' : [{'names' : ['first', 'second'], 'formats' : ['i8', 'i8']}],

    'pair_uint8_uint8' : [{'names' : ['first', 'second'], 'formats' : ['u1', 'u1']}],
    'pair_uint16_uint16' : [{'names' : ['first', 'second'], 'formats' : ['u2', 'u2']}],
    'pair_uint32_uint32' : [{'names' : ['first', 'second'], 'formats' : ['u4', 'u4']}],
    'pair_uint64_uint64' : [{'names' : ['first', 'second'], 'formats' : ['u8', 'u8']}],

    'pair_float32_float32' : [{'names' : ['first', 'second'], 'formats' : ['f4', 'f4']}],
    'pair_float64_float64' : [{'names' : ['first', 'second'], 'formats' : ['f8', 'f8']}],

    'rparray' : ['50u1'],

    'rotation_uint16' : [{'names' : ['a', 'b', 'c', 'd'], 'formats' : ['u2', 'u2', 'u2', 'u2']}],
    'translation_uint16' : [{'names' : ['x', 'y', 'z', 's'], 'formats' : ['u2', 'u2', 'u2', 'u2']}],

    'pair_rotation_uint16_translation_uint16' : [{'names' : ['first', 'second'],
                                                  'formats' : [{'names' : ['a', 'b', 'c', 'd'], 'formats' : ['u2', 'u2', 'u2', 'u2']},
                                                               {'names' : ['x', 'y', 'z', 's'], 'formats' : ['u2', 'u2', 'u2', 'u2']}]}]
}


# rparray_struct_def = ' '.join([f'uint8_t v{i};' for i in range(50)])
rotation_uint16_struct_def = ('uint16_t a; uint16_t b; uint16_t c; uint16_t d;')
translation_uint16_struct_def = ('uint16_t x; uint16_t y; uint16_t z; uint16_t s;')

struct_types = {
    'pair_str1_str1' : 'struct pair_str1_str1 { std::array<char, 1> first; std::array<char, 1> second; };',
    'pair_str2_str2' : 'struct pair_str2_str2 { std::array<char, 2> first; std::array<char, 2> second; };',
    'pair_str4_str4' : 'struct pair_str4_str4 { std::array<char, 4> first; std::array<char, 4> second; };',
    'pair_str8_str8' : 'struct pair_str8_str8 { std::array<char, 8> first; std::array<char, 8> second; };',
    'pair_str16_str16' : 'struct pair_str16_str16 { std::array<char, 16> first; std::array<char, 16> second; };',
    'pair_str32_str32' : 'struct pair_str32_str32 { std::array<char, 32> first; std::array<char, 32> second; };',

    'pair_int8_int8' : 'struct pair_int8_int8 { int8_t first; int8_t second; };',
    'pair_int16_int16' : 'struct pair_int16_int16 { int16_t first; int16_t second; };',
    'pair_int32_int32' : 'struct pair_int32_int32 { int32_t first; int32_t second; };',
    'pair_int64_int64' : 'struct pair_int64_int64 { int64_t first; int64_t second; };',

    'pair_uint8_uint8' : 'struct pair_uint8_uint8 { uint8_t first; uint8_t second; };',
    'pair_uint16_uint16' : 'struct pair_uint16_uint16 { uint16_t first; uint16_t second; };',
    'pair_uint32_uint32' : 'struct pair_uint32_uint32 { uint32_t first; uint32_t second; };',
    'pair_uint64_uint64' : 'struct pair_uint64_uint64 { uint64_t first; uint64_t second; };',

    'pair_float32_float32' : 'struct pair_float32_float32 { float first; float second; };',
    'pair_float64_float64' : 'struct pair_float64_float64 { double first; double second; };',

    # 'rparray' : f'struct rparray {{ {rparray_struct_def} }};',

    'rotation_uint16' : f'struct rotation_uint16 {{ {rotation_uint16_struct_def} }};',
    'translation_uint16' : f'struct translation_uint16 {{ {translation_uint16_struct_def} }};',

    'pair_rotation_uint16_translation_uint16' : 'struct pair_rotation_uint16_translation_uint16 { rotation_uint16 first; translation_uint16 second; };',
}


def create_class_name(key_type, value_type):
    return f'Dict_{key_type}_{value_type}'


def write_dict_types_dict(getpy_file, key_type, value_type):
    class_name = create_class_name(key_type, value_type)
    getpy_file.write(f"    (types['{key_type}'], types['{value_type}']) : _gp.{class_name},\n")


def write_struct_types(getpy_file, type_):
    getpy_file.write(f'{struct_types[type_]}\n')


# rparray_serialization_def = ', '.join([f'rparray.v{i}' for i in range(50)])
rotation_serialization_def = 'rotation.a, rotation.b, rotation.c, rotation.d'
translation_serialization_def = 'translation.x, translation.y, translation.z, translation.s'


def write_struct_serialization(getpy_file, type_):
    if type_.startswith('pair'):
        getpy_file.write(f'template<class Archive> void serialize(Archive & archive, {type_} & pair) {{ archive( pair.first, pair.second ); }}\n')
    # elif type_.startswith('rparray'):
    #     getpy_file.write(f'template<class Archive> void serialize(Archive & archive, {type_} & rparray) {{ archive( {rparray_serialization_def} ); }}\n')
    elif type_.startswith('rotation'):
        getpy_file.write(f'template<class Archive> void serialize(Archive & archive, {type_} & rotation) {{ archive( {rotation_serialization_def} ); }}\n')
    elif type_.startswith('translation'):
        getpy_file.write(f'template<class Archive> void serialize(Archive & archive, {type_} & translation) {{ archive( {translation_serialization_def} ); }}\n')
    else:
        pass


rparray_pybind11_def = ', '.join([f'v{i}' for i in range(50)])
rotation_pybind11_def = ('a, b, c, d')
translation_pybind11_def = ('x, y, z, s')

def write_numpy_dtype(getpy_file, type_):
    if type_.startswith('pair'):
        getpy_file.write(f'    PYBIND11_NUMPY_DTYPE({cpp_types[type_]}, first, second );\n')
    # elif type_.startswith('rparray'):
    #     getpy_file.write(f'    PYBIND11_NUMPY_DTYPE({cpp_types[type_]}, {rparray_pybind11_def} );\n')
    elif type_.startswith('rotation'):
        getpy_file.write(f'    PYBIND11_NUMPY_DTYPE({cpp_types[type_]}, {rotation_pybind11_def} );\n')
    elif type_.startswith('translation'):
        getpy_file.write(f'    PYBIND11_NUMPY_DTYPE({cpp_types[type_]}, {translation_pybind11_def} );\n')
    else:
        pass


def write_declare_dict(getpy_file, key_type, value_type):
    class_name = create_class_name(key_type, value_type)
    getpy_file.write(f'    declare_dict<{cpp_types[key_type]}, {cpp_types[value_type]}>(m, "{class_name}");\n')


def write_types_dict(getpy_file, type_):
    for vt in np_types[type_]:
        if isinstance(vt, dict):
            getpy_file.write(f"    '{type_}' : np.dtype({vt}),\n")
        else:
            getpy_file.write(f"    '{type_}' : np.dtype('{vt}'),\n")


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
