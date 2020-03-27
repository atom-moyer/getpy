#include "getpy.cpp"

#include <pybind11/pybind11.h>

PYBIND11_MODULE(_getpy, m) {
    declare_multidict<uint64_t, uint64_t>(m, "MultiDict_u8_u8");

    declare_dict<uint32_t, uint8_t>(m, "Dict_u4_u1");
    declare_dict<uint32_t, uint16_t>(m, "Dict_u4_u2");
    declare_dict<uint32_t, uint32_t>(m, "Dict_u4_u4");
    declare_dict<uint32_t, uint64_t>(m, "Dict_u4_u8");
    declare_dict<uint32_t, int8_t>(m, "Dict_u4_i1");
    declare_dict<uint32_t, int16_t>(m, "Dict_u4_i2");
    declare_dict<uint32_t, int32_t>(m, "Dict_u4_i4");
    declare_dict<uint32_t, int64_t>(m, "Dict_u4_i8");
    declare_dict<uint32_t, float>(m, "Dict_u4_f4");
    declare_dict<uint32_t, double>(m, "Dict_u4_f8");
    declare_dict<uint32_t, std::array<char,8>>(m, "Dict_u4_S8");
    declare_dict<uint32_t, std::array<char,16>>(m, "Dict_u4_S16");
    declare_dict<uint64_t, uint8_t>(m, "Dict_u8_u1");
    declare_dict<uint64_t, uint16_t>(m, "Dict_u8_u2");
    declare_dict<uint64_t, uint32_t>(m, "Dict_u8_u4");
    declare_dict<uint64_t, uint64_t>(m, "Dict_u8_u8");
    declare_dict<uint64_t, int8_t>(m, "Dict_u8_i1");
    declare_dict<uint64_t, int16_t>(m, "Dict_u8_i2");
    declare_dict<uint64_t, int32_t>(m, "Dict_u8_i4");
    declare_dict<uint64_t, int64_t>(m, "Dict_u8_i8");
    declare_dict<uint64_t, float>(m, "Dict_u8_f4");
    declare_dict<uint64_t, double>(m, "Dict_u8_f8");
    declare_dict<uint64_t, std::array<char,8>>(m, "Dict_u8_S8");
    declare_dict<uint64_t, std::array<char,16>>(m, "Dict_u8_S16");
    declare_dict<int32_t, uint8_t>(m, "Dict_i4_u1");
    declare_dict<int32_t, uint16_t>(m, "Dict_i4_u2");
    declare_dict<int32_t, uint32_t>(m, "Dict_i4_u4");
    declare_dict<int32_t, uint64_t>(m, "Dict_i4_u8");
    declare_dict<int32_t, int8_t>(m, "Dict_i4_i1");
    declare_dict<int32_t, int16_t>(m, "Dict_i4_i2");
    declare_dict<int32_t, int32_t>(m, "Dict_i4_i4");
    declare_dict<int32_t, int64_t>(m, "Dict_i4_i8");
    declare_dict<int32_t, float>(m, "Dict_i4_f4");
    declare_dict<int32_t, double>(m, "Dict_i4_f8");
    declare_dict<int32_t, std::array<char,8>>(m, "Dict_i4_S8");
    declare_dict<int32_t, std::array<char,16>>(m, "Dict_i4_S16");
    declare_dict<int64_t, uint8_t>(m, "Dict_i8_u1");
    declare_dict<int64_t, uint16_t>(m, "Dict_i8_u2");
    declare_dict<int64_t, uint32_t>(m, "Dict_i8_u4");
    declare_dict<int64_t, uint64_t>(m, "Dict_i8_u8");
    declare_dict<int64_t, int8_t>(m, "Dict_i8_i1");
    declare_dict<int64_t, int16_t>(m, "Dict_i8_i2");
    declare_dict<int64_t, int32_t>(m, "Dict_i8_i4");
    declare_dict<int64_t, int64_t>(m, "Dict_i8_i8");
    declare_dict<int64_t, float>(m, "Dict_i8_f4");
    declare_dict<int64_t, double>(m, "Dict_i8_f8");
    declare_dict<int64_t, std::array<char,8>>(m, "Dict_i8_S8");
    declare_dict<int64_t, std::array<char,16>>(m, "Dict_i8_S16");
    declare_dict<std::array<char,8>, uint8_t>(m, "Dict_S8_u1");
    declare_dict<std::array<char,8>, uint16_t>(m, "Dict_S8_u2");
    declare_dict<std::array<char,8>, uint32_t>(m, "Dict_S8_u4");
    declare_dict<std::array<char,8>, uint64_t>(m, "Dict_S8_u8");
    declare_dict<std::array<char,8>, int8_t>(m, "Dict_S8_i1");
    declare_dict<std::array<char,8>, int16_t>(m, "Dict_S8_i2");
    declare_dict<std::array<char,8>, int32_t>(m, "Dict_S8_i4");
    declare_dict<std::array<char,8>, int64_t>(m, "Dict_S8_i8");
    declare_dict<std::array<char,8>, float>(m, "Dict_S8_f4");
    declare_dict<std::array<char,8>, double>(m, "Dict_S8_f8");
    declare_dict<std::array<char,8>, std::array<char,8>>(m, "Dict_S8_S8");
    declare_dict<std::array<char,8>, std::array<char,16>>(m, "Dict_S8_S16");
    declare_dict<std::array<char,16>, uint8_t>(m, "Dict_S16_u1");
    declare_dict<std::array<char,16>, uint16_t>(m, "Dict_S16_u2");
    declare_dict<std::array<char,16>, uint32_t>(m, "Dict_S16_u4");
    declare_dict<std::array<char,16>, uint64_t>(m, "Dict_S16_u8");
    declare_dict<std::array<char,16>, int8_t>(m, "Dict_S16_i1");
    declare_dict<std::array<char,16>, int16_t>(m, "Dict_S16_i2");
    declare_dict<std::array<char,16>, int32_t>(m, "Dict_S16_i4");
    declare_dict<std::array<char,16>, int64_t>(m, "Dict_S16_i8");
    declare_dict<std::array<char,16>, float>(m, "Dict_S16_f4");
    declare_dict<std::array<char,16>, double>(m, "Dict_S16_f8");
    declare_dict<std::array<char,16>, std::array<char,8>>(m, "Dict_S16_S8");
    declare_dict<std::array<char,16>, std::array<char,16>>(m, "Dict_S16_S16");

    declare_set<uint32_t>(m, "Set_u4");
    declare_set<uint64_t>(m, "Set_u8");
    declare_set<int32_t>(m, "Set_i4");
    declare_set<int64_t>(m, "Set_i8");
    declare_set<std::array<char,8>>(m, "Set_S8");
    declare_set<std::array<char,16>>(m, "Set_S16");
}
