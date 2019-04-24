#include "getpy.cpp"

#include <pybind11/pybind11.h>


PYBIND11_MODULE(_getpy, m) {
    m.doc() = "A Fast and Memory Efficient Hash Map for Python";


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
}
