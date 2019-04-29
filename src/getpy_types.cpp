#include "getpy.cpp"

#include <pybind11/pybind11.h>

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

struct bytearray2 { std::array<uint8_t, 2> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray2 & bytearray) { archive( bytearray.bytearray ); }

struct bytearray4 { std::array<uint8_t, 4> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray4 & bytearray) { archive( bytearray.bytearray ); }

struct bytearray8 { std::array<uint8_t, 8> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray8 & bytearray) { archive( bytearray.bytearray ); }

struct bytearray10 { std::array<uint8_t, 10> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray10 & bytearray) { archive( bytearray.bytearray ); }

struct bytearray16 { std::array<uint8_t, 16> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray16 & bytearray) { archive( bytearray.bytearray ); }

struct bytearray20 { std::array<uint8_t, 20> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray20 & bytearray) { archive( bytearray.bytearray ); }

struct bytearray30 { std::array<uint8_t, 30> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray30 & bytearray) { archive( bytearray.bytearray ); }

struct bytearray32 { std::array<uint8_t, 32> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray32 & bytearray) { archive( bytearray.bytearray ); }

struct bytearray40 { std::array<uint8_t, 40> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray40 & bytearray) { archive( bytearray.bytearray ); }

struct bytearray50 { std::array<uint8_t, 50> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray50 & bytearray) { archive( bytearray.bytearray ); }


PYBIND11_MODULE(_getpy, m) {
    m.doc() = "A Fast and Memory Efficient Hash Map for Python";

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
    PYBIND11_NUMPY_DTYPE(bytearray2, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray4, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray8, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray10, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray16, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray20, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray30, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray32, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray40, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray50, bytearray );

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
    declare_dict<std::array<char, 4>, bytearray2>(m, "Dict_str4_bytearray2");
    declare_dict<std::array<char, 4>, bytearray4>(m, "Dict_str4_bytearray4");
    declare_dict<std::array<char, 4>, bytearray8>(m, "Dict_str4_bytearray8");
    declare_dict<std::array<char, 4>, bytearray10>(m, "Dict_str4_bytearray10");
    declare_dict<std::array<char, 4>, bytearray16>(m, "Dict_str4_bytearray16");
    declare_dict<std::array<char, 4>, bytearray20>(m, "Dict_str4_bytearray20");
    declare_dict<std::array<char, 4>, bytearray30>(m, "Dict_str4_bytearray30");
    declare_dict<std::array<char, 4>, bytearray32>(m, "Dict_str4_bytearray32");
    declare_dict<std::array<char, 4>, bytearray40>(m, "Dict_str4_bytearray40");
    declare_dict<std::array<char, 4>, bytearray50>(m, "Dict_str4_bytearray50");
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
    declare_dict<std::array<char, 8>, bytearray2>(m, "Dict_str8_bytearray2");
    declare_dict<std::array<char, 8>, bytearray4>(m, "Dict_str8_bytearray4");
    declare_dict<std::array<char, 8>, bytearray8>(m, "Dict_str8_bytearray8");
    declare_dict<std::array<char, 8>, bytearray10>(m, "Dict_str8_bytearray10");
    declare_dict<std::array<char, 8>, bytearray16>(m, "Dict_str8_bytearray16");
    declare_dict<std::array<char, 8>, bytearray20>(m, "Dict_str8_bytearray20");
    declare_dict<std::array<char, 8>, bytearray30>(m, "Dict_str8_bytearray30");
    declare_dict<std::array<char, 8>, bytearray32>(m, "Dict_str8_bytearray32");
    declare_dict<std::array<char, 8>, bytearray40>(m, "Dict_str8_bytearray40");
    declare_dict<std::array<char, 8>, bytearray50>(m, "Dict_str8_bytearray50");
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
    declare_dict<uint32_t, bytearray2>(m, "Dict_uint32_bytearray2");
    declare_dict<uint32_t, bytearray4>(m, "Dict_uint32_bytearray4");
    declare_dict<uint32_t, bytearray8>(m, "Dict_uint32_bytearray8");
    declare_dict<uint32_t, bytearray10>(m, "Dict_uint32_bytearray10");
    declare_dict<uint32_t, bytearray16>(m, "Dict_uint32_bytearray16");
    declare_dict<uint32_t, bytearray20>(m, "Dict_uint32_bytearray20");
    declare_dict<uint32_t, bytearray30>(m, "Dict_uint32_bytearray30");
    declare_dict<uint32_t, bytearray32>(m, "Dict_uint32_bytearray32");
    declare_dict<uint32_t, bytearray40>(m, "Dict_uint32_bytearray40");
    declare_dict<uint32_t, bytearray50>(m, "Dict_uint32_bytearray50");
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
    declare_dict<uint64_t, bytearray2>(m, "Dict_uint64_bytearray2");
    declare_dict<uint64_t, bytearray4>(m, "Dict_uint64_bytearray4");
    declare_dict<uint64_t, bytearray8>(m, "Dict_uint64_bytearray8");
    declare_dict<uint64_t, bytearray10>(m, "Dict_uint64_bytearray10");
    declare_dict<uint64_t, bytearray16>(m, "Dict_uint64_bytearray16");
    declare_dict<uint64_t, bytearray20>(m, "Dict_uint64_bytearray20");
    declare_dict<uint64_t, bytearray30>(m, "Dict_uint64_bytearray30");
    declare_dict<uint64_t, bytearray32>(m, "Dict_uint64_bytearray32");
    declare_dict<uint64_t, bytearray40>(m, "Dict_uint64_bytearray40");
    declare_dict<uint64_t, bytearray50>(m, "Dict_uint64_bytearray50");
    declare_dict<int32_t, std::array<char, 4>>(m, "Dict_int32_str4");
    declare_dict<int32_t, std::array<char, 8>>(m, "Dict_int32_str8");
    declare_dict<int32_t, std::array<char, 16>>(m, "Dict_int32_str16");
    declare_dict<int32_t, std::array<char, 32>>(m, "Dict_int32_str32");
    declare_dict<int32_t, uint8_t>(m, "Dict_int32_uint8");
    declare_dict<int32_t, uint16_t>(m, "Dict_int32_uint16");
    declare_dict<int32_t, uint32_t>(m, "Dict_int32_uint32");
    declare_dict<int32_t, uint64_t>(m, "Dict_int32_uint64");
    declare_dict<int32_t, int8_t>(m, "Dict_int32_int8");
    declare_dict<int32_t, int16_t>(m, "Dict_int32_int16");
    declare_dict<int32_t, int32_t>(m, "Dict_int32_int32");
    declare_dict<int32_t, int64_t>(m, "Dict_int32_int64");
    declare_dict<int32_t, float>(m, "Dict_int32_float32");
    declare_dict<int32_t, double>(m, "Dict_int32_float64");
    declare_dict<int32_t, pair_str4_str4>(m, "Dict_int32_pair_str4_str4");
    declare_dict<int32_t, pair_str8_str8>(m, "Dict_int32_pair_str8_str8");
    declare_dict<int32_t, pair_str16_str16>(m, "Dict_int32_pair_str16_str16");
    declare_dict<int32_t, pair_str32_str32>(m, "Dict_int32_pair_str32_str32");
    declare_dict<int32_t, pair_uint8_uint8>(m, "Dict_int32_pair_uint8_uint8");
    declare_dict<int32_t, pair_uint16_uint16>(m, "Dict_int32_pair_uint16_uint16");
    declare_dict<int32_t, pair_uint32_uint32>(m, "Dict_int32_pair_uint32_uint32");
    declare_dict<int32_t, pair_uint64_uint64>(m, "Dict_int32_pair_uint64_uint64");
    declare_dict<int32_t, pair_int8_int8>(m, "Dict_int32_pair_int8_int8");
    declare_dict<int32_t, pair_int16_int16>(m, "Dict_int32_pair_int16_int16");
    declare_dict<int32_t, pair_int32_int32>(m, "Dict_int32_pair_int32_int32");
    declare_dict<int32_t, pair_int64_int64>(m, "Dict_int32_pair_int64_int64");
    declare_dict<int32_t, pair_float32_float32>(m, "Dict_int32_pair_float32_float32");
    declare_dict<int32_t, pair_float64_float64>(m, "Dict_int32_pair_float64_float64");
    declare_dict<int32_t, bytearray2>(m, "Dict_int32_bytearray2");
    declare_dict<int32_t, bytearray4>(m, "Dict_int32_bytearray4");
    declare_dict<int32_t, bytearray8>(m, "Dict_int32_bytearray8");
    declare_dict<int32_t, bytearray10>(m, "Dict_int32_bytearray10");
    declare_dict<int32_t, bytearray16>(m, "Dict_int32_bytearray16");
    declare_dict<int32_t, bytearray20>(m, "Dict_int32_bytearray20");
    declare_dict<int32_t, bytearray30>(m, "Dict_int32_bytearray30");
    declare_dict<int32_t, bytearray32>(m, "Dict_int32_bytearray32");
    declare_dict<int32_t, bytearray40>(m, "Dict_int32_bytearray40");
    declare_dict<int32_t, bytearray50>(m, "Dict_int32_bytearray50");
    declare_dict<int64_t, std::array<char, 4>>(m, "Dict_int64_str4");
    declare_dict<int64_t, std::array<char, 8>>(m, "Dict_int64_str8");
    declare_dict<int64_t, std::array<char, 16>>(m, "Dict_int64_str16");
    declare_dict<int64_t, std::array<char, 32>>(m, "Dict_int64_str32");
    declare_dict<int64_t, uint8_t>(m, "Dict_int64_uint8");
    declare_dict<int64_t, uint16_t>(m, "Dict_int64_uint16");
    declare_dict<int64_t, uint32_t>(m, "Dict_int64_uint32");
    declare_dict<int64_t, uint64_t>(m, "Dict_int64_uint64");
    declare_dict<int64_t, int8_t>(m, "Dict_int64_int8");
    declare_dict<int64_t, int16_t>(m, "Dict_int64_int16");
    declare_dict<int64_t, int32_t>(m, "Dict_int64_int32");
    declare_dict<int64_t, int64_t>(m, "Dict_int64_int64");
    declare_dict<int64_t, float>(m, "Dict_int64_float32");
    declare_dict<int64_t, double>(m, "Dict_int64_float64");
    declare_dict<int64_t, pair_str4_str4>(m, "Dict_int64_pair_str4_str4");
    declare_dict<int64_t, pair_str8_str8>(m, "Dict_int64_pair_str8_str8");
    declare_dict<int64_t, pair_str16_str16>(m, "Dict_int64_pair_str16_str16");
    declare_dict<int64_t, pair_str32_str32>(m, "Dict_int64_pair_str32_str32");
    declare_dict<int64_t, pair_uint8_uint8>(m, "Dict_int64_pair_uint8_uint8");
    declare_dict<int64_t, pair_uint16_uint16>(m, "Dict_int64_pair_uint16_uint16");
    declare_dict<int64_t, pair_uint32_uint32>(m, "Dict_int64_pair_uint32_uint32");
    declare_dict<int64_t, pair_uint64_uint64>(m, "Dict_int64_pair_uint64_uint64");
    declare_dict<int64_t, pair_int8_int8>(m, "Dict_int64_pair_int8_int8");
    declare_dict<int64_t, pair_int16_int16>(m, "Dict_int64_pair_int16_int16");
    declare_dict<int64_t, pair_int32_int32>(m, "Dict_int64_pair_int32_int32");
    declare_dict<int64_t, pair_int64_int64>(m, "Dict_int64_pair_int64_int64");
    declare_dict<int64_t, pair_float32_float32>(m, "Dict_int64_pair_float32_float32");
    declare_dict<int64_t, pair_float64_float64>(m, "Dict_int64_pair_float64_float64");
    declare_dict<int64_t, bytearray2>(m, "Dict_int64_bytearray2");
    declare_dict<int64_t, bytearray4>(m, "Dict_int64_bytearray4");
    declare_dict<int64_t, bytearray8>(m, "Dict_int64_bytearray8");
    declare_dict<int64_t, bytearray10>(m, "Dict_int64_bytearray10");
    declare_dict<int64_t, bytearray16>(m, "Dict_int64_bytearray16");
    declare_dict<int64_t, bytearray20>(m, "Dict_int64_bytearray20");
    declare_dict<int64_t, bytearray30>(m, "Dict_int64_bytearray30");
    declare_dict<int64_t, bytearray32>(m, "Dict_int64_bytearray32");
    declare_dict<int64_t, bytearray40>(m, "Dict_int64_bytearray40");
    declare_dict<int64_t, bytearray50>(m, "Dict_int64_bytearray50");
}
