#include "getpy.cpp"

#include <pybind11/pybind11.h>

struct pair_str1_str1 { std::array<char, 1> first; std::array<char, 1> second; };
template<class Archive> void serialize(Archive & archive, pair_str1_str1 & pair) { archive( pair.first, pair.second ); }

struct pair_str2_str2 { std::array<char, 2> first; std::array<char, 2> second; };
template<class Archive> void serialize(Archive & archive, pair_str2_str2 & pair) { archive( pair.first, pair.second ); }

struct pair_str4_str4 { std::array<char, 4> first; std::array<char, 4> second; };
template<class Archive> void serialize(Archive & archive, pair_str4_str4 & pair) { archive( pair.first, pair.second ); }

struct pair_str8_str8 { std::array<char, 8> first; std::array<char, 8> second; };
template<class Archive> void serialize(Archive & archive, pair_str8_str8 & pair) { archive( pair.first, pair.second ); }

struct pair_str16_str16 { std::array<char, 16> first; std::array<char, 16> second; };
template<class Archive> void serialize(Archive & archive, pair_str16_str16 & pair) { archive( pair.first, pair.second ); }

struct pair_str32_str32 { std::array<char, 32> first; std::array<char, 32> second; };
template<class Archive> void serialize(Archive & archive, pair_str32_str32 & pair) { archive( pair.first, pair.second ); }

struct pair_uint8_uint8 { uint8_t first; uint8_t second; };
template<class Archive> void serialize(Archive & archive, pair_uint8_uint8 & pair) { archive( pair.first, pair.second ); }

struct pair_uint16_uint16 { uint16_t first; uint16_t second; };
template<class Archive> void serialize(Archive & archive, pair_uint16_uint16 & pair) { archive( pair.first, pair.second ); }

struct pair_uint32_uint32 { uint32_t first; uint32_t second; };
template<class Archive> void serialize(Archive & archive, pair_uint32_uint32 & pair) { archive( pair.first, pair.second ); }

struct pair_uint64_uint64 { uint64_t first; uint64_t second; };
template<class Archive> void serialize(Archive & archive, pair_uint64_uint64 & pair) { archive( pair.first, pair.second ); }

struct pair_int8_int8 { int8_t first; int8_t second; };
template<class Archive> void serialize(Archive & archive, pair_int8_int8 & pair) { archive( pair.first, pair.second ); }

struct pair_int16_int16 { int16_t first; int16_t second; };
template<class Archive> void serialize(Archive & archive, pair_int16_int16 & pair) { archive( pair.first, pair.second ); }

struct pair_int32_int32 { int32_t first; int32_t second; };
template<class Archive> void serialize(Archive & archive, pair_int32_int32 & pair) { archive( pair.first, pair.second ); }

struct pair_int64_int64 { int64_t first; int64_t second; };
template<class Archive> void serialize(Archive & archive, pair_int64_int64 & pair) { archive( pair.first, pair.second ); }

struct pair_float32_float32 { float first; float second; };
template<class Archive> void serialize(Archive & archive, pair_float32_float32 & pair) { archive( pair.first, pair.second ); }

struct pair_float64_float64 { double first; double second; };
template<class Archive> void serialize(Archive & archive, pair_float64_float64 & pair) { archive( pair.first, pair.second ); }

struct rparray { std::array<uint8_t, 50> data; };
template<class Archive> void serialize(Archive & archive, rparray & rparray) { archive( rparray.data ); }

struct rotation_uint16 { uint16_t a; uint16_t b; uint16_t c; uint16_t d; };
template<class Archive> void serialize(Archive & archive, rotation_uint16 & rotation) { archive( rotation.a, rotation.b, rotation.c, rotation.d ); }

struct translation_uint16 { uint16_t x; uint16_t y; uint16_t z; uint16_t s; };
template<class Archive> void serialize(Archive & archive, translation_uint16 & translation) { archive( translation.x, translation.y, translation.z, translation.s ); }

struct pair_rotation_uint16_translation_uint16 { rotation_uint16 first; translation_uint16 second; };
template<class Archive> void serialize(Archive & archive, pair_rotation_uint16_translation_uint16 & pair) { archive( pair.first, pair.second ); }


PYBIND11_MODULE(_getpy, m) {
    m.doc() = "A Fast and Memory Efficient Hash Map for Python";

    PYBIND11_NUMPY_DTYPE(pair_str1_str1, first, second );
    PYBIND11_NUMPY_DTYPE(pair_str2_str2, first, second );
    PYBIND11_NUMPY_DTYPE(pair_str4_str4, first, second );
    PYBIND11_NUMPY_DTYPE(pair_str8_str8, first, second );
    PYBIND11_NUMPY_DTYPE(pair_str16_str16, first, second );
    PYBIND11_NUMPY_DTYPE(pair_str32_str32, first, second );
    PYBIND11_NUMPY_DTYPE(pair_uint8_uint8, first, second );
    PYBIND11_NUMPY_DTYPE(pair_uint16_uint16, first, second );
    PYBIND11_NUMPY_DTYPE(pair_uint32_uint32, first, second );
    PYBIND11_NUMPY_DTYPE(pair_uint64_uint64, first, second );
    PYBIND11_NUMPY_DTYPE(pair_int8_int8, first, second );
    PYBIND11_NUMPY_DTYPE(pair_int16_int16, first, second );
    PYBIND11_NUMPY_DTYPE(pair_int32_int32, first, second );
    PYBIND11_NUMPY_DTYPE(pair_int64_int64, first, second );
    PYBIND11_NUMPY_DTYPE(pair_float32_float32, first, second );
    PYBIND11_NUMPY_DTYPE(pair_float64_float64, first, second );
    PYBIND11_NUMPY_DTYPE(rparray, data );
    PYBIND11_NUMPY_DTYPE(rotation_uint16, a, b, c, d );
    PYBIND11_NUMPY_DTYPE(translation_uint16, x, y, z, s );
    PYBIND11_NUMPY_DTYPE(pair_rotation_uint16_translation_uint16, first, second );

    declare_dict<std::array<char, 4>, std::array<char, 1>>(m, "Dict_str4_str1");
    declare_dict<std::array<char, 4>, std::array<char, 2>>(m, "Dict_str4_str2");
    declare_dict<std::array<char, 4>, std::array<char, 4>>(m, "Dict_str4_str4");
    declare_dict<std::array<char, 4>, std::array<char, 8>>(m, "Dict_str4_str8");
    declare_dict<std::array<char, 4>, std::array<char, 16>>(m, "Dict_str4_str16");
    declare_dict<std::array<char, 4>, std::array<char, 32>>(m, "Dict_str4_str32");
    declare_dict<std::array<char, 4>, uint8_t>(m, "Dict_str4_uint8");
    declare_dict<std::array<char, 4>, uint16_t>(m, "Dict_str4_uint16");
    declare_dict<std::array<char, 4>, uint32_t>(m, "Dict_str4_uint32");
    declare_dict<std::array<char, 4>, uint64_t>(m, "Dict_str4_uint64");
    declare_dict<std::array<char, 4>, int8_t>(m, "Dict_str4_int8");
    declare_dict<std::array<char, 4>, int16_t>(m, "Dict_str4_int16");
    declare_dict<std::array<char, 4>, int32_t>(m, "Dict_str4_int32");
    declare_dict<std::array<char, 4>, int64_t>(m, "Dict_str4_int64");
    declare_dict<std::array<char, 4>, float>(m, "Dict_str4_float32");
    declare_dict<std::array<char, 4>, double>(m, "Dict_str4_float64");
    declare_dict<std::array<char, 4>, bool>(m, "Dict_str4_bool");
    declare_dict<std::array<char, 4>, pair_str1_str1>(m, "Dict_str4_pair_str1_str1");
    declare_dict<std::array<char, 4>, pair_str2_str2>(m, "Dict_str4_pair_str2_str2");
    declare_dict<std::array<char, 4>, pair_str4_str4>(m, "Dict_str4_pair_str4_str4");
    declare_dict<std::array<char, 4>, pair_str8_str8>(m, "Dict_str4_pair_str8_str8");
    declare_dict<std::array<char, 4>, pair_str16_str16>(m, "Dict_str4_pair_str16_str16");
    declare_dict<std::array<char, 4>, pair_str32_str32>(m, "Dict_str4_pair_str32_str32");
    declare_dict<std::array<char, 4>, pair_uint8_uint8>(m, "Dict_str4_pair_uint8_uint8");
    declare_dict<std::array<char, 4>, pair_uint16_uint16>(m, "Dict_str4_pair_uint16_uint16");
    declare_dict<std::array<char, 4>, pair_uint32_uint32>(m, "Dict_str4_pair_uint32_uint32");
    declare_dict<std::array<char, 4>, pair_uint64_uint64>(m, "Dict_str4_pair_uint64_uint64");
    declare_dict<std::array<char, 4>, pair_int8_int8>(m, "Dict_str4_pair_int8_int8");
    declare_dict<std::array<char, 4>, pair_int16_int16>(m, "Dict_str4_pair_int16_int16");
    declare_dict<std::array<char, 4>, pair_int32_int32>(m, "Dict_str4_pair_int32_int32");
    declare_dict<std::array<char, 4>, pair_int64_int64>(m, "Dict_str4_pair_int64_int64");
    declare_dict<std::array<char, 4>, pair_float32_float32>(m, "Dict_str4_pair_float32_float32");
    declare_dict<std::array<char, 4>, pair_float64_float64>(m, "Dict_str4_pair_float64_float64");
    declare_dict<std::array<char, 4>, rparray>(m, "Dict_str4_rparray");
    declare_dict<std::array<char, 4>, rotation_uint16>(m, "Dict_str4_rotation_uint16");
    declare_dict<std::array<char, 4>, translation_uint16>(m, "Dict_str4_translation_uint16");
    declare_dict<std::array<char, 4>, pair_rotation_uint16_translation_uint16>(m, "Dict_str4_pair_rotation_uint16_translation_uint16");
    declare_dict<std::array<char, 8>, std::array<char, 1>>(m, "Dict_str8_str1");
    declare_dict<std::array<char, 8>, std::array<char, 2>>(m, "Dict_str8_str2");
    declare_dict<std::array<char, 8>, std::array<char, 4>>(m, "Dict_str8_str4");
    declare_dict<std::array<char, 8>, std::array<char, 8>>(m, "Dict_str8_str8");
    declare_dict<std::array<char, 8>, std::array<char, 16>>(m, "Dict_str8_str16");
    declare_dict<std::array<char, 8>, std::array<char, 32>>(m, "Dict_str8_str32");
    declare_dict<std::array<char, 8>, uint8_t>(m, "Dict_str8_uint8");
    declare_dict<std::array<char, 8>, uint16_t>(m, "Dict_str8_uint16");
    declare_dict<std::array<char, 8>, uint32_t>(m, "Dict_str8_uint32");
    declare_dict<std::array<char, 8>, uint64_t>(m, "Dict_str8_uint64");
    declare_dict<std::array<char, 8>, int8_t>(m, "Dict_str8_int8");
    declare_dict<std::array<char, 8>, int16_t>(m, "Dict_str8_int16");
    declare_dict<std::array<char, 8>, int32_t>(m, "Dict_str8_int32");
    declare_dict<std::array<char, 8>, int64_t>(m, "Dict_str8_int64");
    declare_dict<std::array<char, 8>, float>(m, "Dict_str8_float32");
    declare_dict<std::array<char, 8>, double>(m, "Dict_str8_float64");
    declare_dict<std::array<char, 8>, bool>(m, "Dict_str8_bool");
    declare_dict<std::array<char, 8>, pair_str1_str1>(m, "Dict_str8_pair_str1_str1");
    declare_dict<std::array<char, 8>, pair_str2_str2>(m, "Dict_str8_pair_str2_str2");
    declare_dict<std::array<char, 8>, pair_str4_str4>(m, "Dict_str8_pair_str4_str4");
    declare_dict<std::array<char, 8>, pair_str8_str8>(m, "Dict_str8_pair_str8_str8");
    declare_dict<std::array<char, 8>, pair_str16_str16>(m, "Dict_str8_pair_str16_str16");
    declare_dict<std::array<char, 8>, pair_str32_str32>(m, "Dict_str8_pair_str32_str32");
    declare_dict<std::array<char, 8>, pair_uint8_uint8>(m, "Dict_str8_pair_uint8_uint8");
    declare_dict<std::array<char, 8>, pair_uint16_uint16>(m, "Dict_str8_pair_uint16_uint16");
    declare_dict<std::array<char, 8>, pair_uint32_uint32>(m, "Dict_str8_pair_uint32_uint32");
    declare_dict<std::array<char, 8>, pair_uint64_uint64>(m, "Dict_str8_pair_uint64_uint64");
    declare_dict<std::array<char, 8>, pair_int8_int8>(m, "Dict_str8_pair_int8_int8");
    declare_dict<std::array<char, 8>, pair_int16_int16>(m, "Dict_str8_pair_int16_int16");
    declare_dict<std::array<char, 8>, pair_int32_int32>(m, "Dict_str8_pair_int32_int32");
    declare_dict<std::array<char, 8>, pair_int64_int64>(m, "Dict_str8_pair_int64_int64");
    declare_dict<std::array<char, 8>, pair_float32_float32>(m, "Dict_str8_pair_float32_float32");
    declare_dict<std::array<char, 8>, pair_float64_float64>(m, "Dict_str8_pair_float64_float64");
    declare_dict<std::array<char, 8>, rparray>(m, "Dict_str8_rparray");
    declare_dict<std::array<char, 8>, rotation_uint16>(m, "Dict_str8_rotation_uint16");
    declare_dict<std::array<char, 8>, translation_uint16>(m, "Dict_str8_translation_uint16");
    declare_dict<std::array<char, 8>, pair_rotation_uint16_translation_uint16>(m, "Dict_str8_pair_rotation_uint16_translation_uint16");
    declare_dict<uint32_t, std::array<char, 1>>(m, "Dict_uint32_str1");
    declare_dict<uint32_t, std::array<char, 2>>(m, "Dict_uint32_str2");
    declare_dict<uint32_t, std::array<char, 4>>(m, "Dict_uint32_str4");
    declare_dict<uint32_t, std::array<char, 8>>(m, "Dict_uint32_str8");
    declare_dict<uint32_t, std::array<char, 16>>(m, "Dict_uint32_str16");
    declare_dict<uint32_t, std::array<char, 32>>(m, "Dict_uint32_str32");
    declare_dict<uint32_t, uint8_t>(m, "Dict_uint32_uint8");
    declare_dict<uint32_t, uint16_t>(m, "Dict_uint32_uint16");
    declare_dict<uint32_t, uint32_t>(m, "Dict_uint32_uint32");
    declare_dict<uint32_t, uint64_t>(m, "Dict_uint32_uint64");
    declare_dict<uint32_t, int8_t>(m, "Dict_uint32_int8");
    declare_dict<uint32_t, int16_t>(m, "Dict_uint32_int16");
    declare_dict<uint32_t, int32_t>(m, "Dict_uint32_int32");
    declare_dict<uint32_t, int64_t>(m, "Dict_uint32_int64");
    declare_dict<uint32_t, float>(m, "Dict_uint32_float32");
    declare_dict<uint32_t, double>(m, "Dict_uint32_float64");
    declare_dict<uint32_t, bool>(m, "Dict_uint32_bool");
    declare_dict<uint32_t, pair_str1_str1>(m, "Dict_uint32_pair_str1_str1");
    declare_dict<uint32_t, pair_str2_str2>(m, "Dict_uint32_pair_str2_str2");
    declare_dict<uint32_t, pair_str4_str4>(m, "Dict_uint32_pair_str4_str4");
    declare_dict<uint32_t, pair_str8_str8>(m, "Dict_uint32_pair_str8_str8");
    declare_dict<uint32_t, pair_str16_str16>(m, "Dict_uint32_pair_str16_str16");
    declare_dict<uint32_t, pair_str32_str32>(m, "Dict_uint32_pair_str32_str32");
    declare_dict<uint32_t, pair_uint8_uint8>(m, "Dict_uint32_pair_uint8_uint8");
    declare_dict<uint32_t, pair_uint16_uint16>(m, "Dict_uint32_pair_uint16_uint16");
    declare_dict<uint32_t, pair_uint32_uint32>(m, "Dict_uint32_pair_uint32_uint32");
    declare_dict<uint32_t, pair_uint64_uint64>(m, "Dict_uint32_pair_uint64_uint64");
    declare_dict<uint32_t, pair_int8_int8>(m, "Dict_uint32_pair_int8_int8");
    declare_dict<uint32_t, pair_int16_int16>(m, "Dict_uint32_pair_int16_int16");
    declare_dict<uint32_t, pair_int32_int32>(m, "Dict_uint32_pair_int32_int32");
    declare_dict<uint32_t, pair_int64_int64>(m, "Dict_uint32_pair_int64_int64");
    declare_dict<uint32_t, pair_float32_float32>(m, "Dict_uint32_pair_float32_float32");
    declare_dict<uint32_t, pair_float64_float64>(m, "Dict_uint32_pair_float64_float64");
    declare_dict<uint32_t, rparray>(m, "Dict_uint32_rparray");
    declare_dict<uint32_t, rotation_uint16>(m, "Dict_uint32_rotation_uint16");
    declare_dict<uint32_t, translation_uint16>(m, "Dict_uint32_translation_uint16");
    declare_dict<uint32_t, pair_rotation_uint16_translation_uint16>(m, "Dict_uint32_pair_rotation_uint16_translation_uint16");
    declare_dict<uint64_t, std::array<char, 1>>(m, "Dict_uint64_str1");
    declare_dict<uint64_t, std::array<char, 2>>(m, "Dict_uint64_str2");
    declare_dict<uint64_t, std::array<char, 4>>(m, "Dict_uint64_str4");
    declare_dict<uint64_t, std::array<char, 8>>(m, "Dict_uint64_str8");
    declare_dict<uint64_t, std::array<char, 16>>(m, "Dict_uint64_str16");
    declare_dict<uint64_t, std::array<char, 32>>(m, "Dict_uint64_str32");
    declare_dict<uint64_t, uint8_t>(m, "Dict_uint64_uint8");
    declare_dict<uint64_t, uint16_t>(m, "Dict_uint64_uint16");
    declare_dict<uint64_t, uint32_t>(m, "Dict_uint64_uint32");
    declare_dict<uint64_t, uint64_t>(m, "Dict_uint64_uint64");
    declare_dict<uint64_t, int8_t>(m, "Dict_uint64_int8");
    declare_dict<uint64_t, int16_t>(m, "Dict_uint64_int16");
    declare_dict<uint64_t, int32_t>(m, "Dict_uint64_int32");
    declare_dict<uint64_t, int64_t>(m, "Dict_uint64_int64");
    declare_dict<uint64_t, float>(m, "Dict_uint64_float32");
    declare_dict<uint64_t, double>(m, "Dict_uint64_float64");
    declare_dict<uint64_t, bool>(m, "Dict_uint64_bool");
    declare_dict<uint64_t, pair_str1_str1>(m, "Dict_uint64_pair_str1_str1");
    declare_dict<uint64_t, pair_str2_str2>(m, "Dict_uint64_pair_str2_str2");
    declare_dict<uint64_t, pair_str4_str4>(m, "Dict_uint64_pair_str4_str4");
    declare_dict<uint64_t, pair_str8_str8>(m, "Dict_uint64_pair_str8_str8");
    declare_dict<uint64_t, pair_str16_str16>(m, "Dict_uint64_pair_str16_str16");
    declare_dict<uint64_t, pair_str32_str32>(m, "Dict_uint64_pair_str32_str32");
    declare_dict<uint64_t, pair_uint8_uint8>(m, "Dict_uint64_pair_uint8_uint8");
    declare_dict<uint64_t, pair_uint16_uint16>(m, "Dict_uint64_pair_uint16_uint16");
    declare_dict<uint64_t, pair_uint32_uint32>(m, "Dict_uint64_pair_uint32_uint32");
    declare_dict<uint64_t, pair_uint64_uint64>(m, "Dict_uint64_pair_uint64_uint64");
    declare_dict<uint64_t, pair_int8_int8>(m, "Dict_uint64_pair_int8_int8");
    declare_dict<uint64_t, pair_int16_int16>(m, "Dict_uint64_pair_int16_int16");
    declare_dict<uint64_t, pair_int32_int32>(m, "Dict_uint64_pair_int32_int32");
    declare_dict<uint64_t, pair_int64_int64>(m, "Dict_uint64_pair_int64_int64");
    declare_dict<uint64_t, pair_float32_float32>(m, "Dict_uint64_pair_float32_float32");
    declare_dict<uint64_t, pair_float64_float64>(m, "Dict_uint64_pair_float64_float64");
    declare_dict<uint64_t, rparray>(m, "Dict_uint64_rparray");
    declare_dict<uint64_t, rotation_uint16>(m, "Dict_uint64_rotation_uint16");
    declare_dict<uint64_t, translation_uint16>(m, "Dict_uint64_translation_uint16");
    declare_dict<uint64_t, pair_rotation_uint16_translation_uint16>(m, "Dict_uint64_pair_rotation_uint16_translation_uint16");
}
