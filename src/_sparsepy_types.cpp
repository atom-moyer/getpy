#include "_sparsepy.cpp"

#include <pybind11/pybind11.h>

PYBIND11_MODULE(_sparsepy, m) {
    m.doc() = "Fast and Memory Efficient Sparse Hash Tables for Python";

    declare_dict<uint8_t, uint8_t>(m, "_Dict_uint8_t_uint8_t");
    declare_dict<uint8_t, uint16_t>(m, "_Dict_uint8_t_uint16_t");
    declare_dict<uint8_t, uint32_t>(m, "_Dict_uint8_t_uint32_t");
    declare_dict<uint8_t, uint64_t>(m, "_Dict_uint8_t_uint64_t");
    declare_dict<uint8_t, int8_t>(m, "_Dict_uint8_t_int8_t");
    declare_dict<uint8_t, int16_t>(m, "_Dict_uint8_t_int16_t");
    declare_dict<uint8_t, int32_t>(m, "_Dict_uint8_t_int32_t");
    declare_dict<uint8_t, int64_t>(m, "_Dict_uint8_t_int64_t");
    declare_dict<uint8_t, float>(m, "_Dict_uint8_t_float");
    declare_dict<uint8_t, double>(m, "_Dict_uint8_t_double");
    declare_dict<uint8_t, bool>(m, "_Dict_uint8_t_bool");
    declare_dict<uint16_t, uint8_t>(m, "_Dict_uint16_t_uint8_t");
    declare_dict<uint16_t, uint16_t>(m, "_Dict_uint16_t_uint16_t");
    declare_dict<uint16_t, uint32_t>(m, "_Dict_uint16_t_uint32_t");
    declare_dict<uint16_t, uint64_t>(m, "_Dict_uint16_t_uint64_t");
    declare_dict<uint16_t, int8_t>(m, "_Dict_uint16_t_int8_t");
    declare_dict<uint16_t, int16_t>(m, "_Dict_uint16_t_int16_t");
    declare_dict<uint16_t, int32_t>(m, "_Dict_uint16_t_int32_t");
    declare_dict<uint16_t, int64_t>(m, "_Dict_uint16_t_int64_t");
    declare_dict<uint16_t, float>(m, "_Dict_uint16_t_float");
    declare_dict<uint16_t, double>(m, "_Dict_uint16_t_double");
    declare_dict<uint16_t, bool>(m, "_Dict_uint16_t_bool");
    declare_dict<uint32_t, uint8_t>(m, "_Dict_uint32_t_uint8_t");
    declare_dict<uint32_t, uint16_t>(m, "_Dict_uint32_t_uint16_t");
    declare_dict<uint32_t, uint32_t>(m, "_Dict_uint32_t_uint32_t");
    declare_dict<uint32_t, uint64_t>(m, "_Dict_uint32_t_uint64_t");
    declare_dict<uint32_t, int8_t>(m, "_Dict_uint32_t_int8_t");
    declare_dict<uint32_t, int16_t>(m, "_Dict_uint32_t_int16_t");
    declare_dict<uint32_t, int32_t>(m, "_Dict_uint32_t_int32_t");
    declare_dict<uint32_t, int64_t>(m, "_Dict_uint32_t_int64_t");
    declare_dict<uint32_t, float>(m, "_Dict_uint32_t_float");
    declare_dict<uint32_t, double>(m, "_Dict_uint32_t_double");
    declare_dict<uint32_t, bool>(m, "_Dict_uint32_t_bool");
    declare_dict<uint64_t, uint8_t>(m, "_Dict_uint64_t_uint8_t");
    declare_dict<uint64_t, uint16_t>(m, "_Dict_uint64_t_uint16_t");
    declare_dict<uint64_t, uint32_t>(m, "_Dict_uint64_t_uint32_t");
    declare_dict<uint64_t, uint64_t>(m, "_Dict_uint64_t_uint64_t");
    declare_dict<uint64_t, int8_t>(m, "_Dict_uint64_t_int8_t");
    declare_dict<uint64_t, int16_t>(m, "_Dict_uint64_t_int16_t");
    declare_dict<uint64_t, int32_t>(m, "_Dict_uint64_t_int32_t");
    declare_dict<uint64_t, int64_t>(m, "_Dict_uint64_t_int64_t");
    declare_dict<uint64_t, float>(m, "_Dict_uint64_t_float");
    declare_dict<uint64_t, double>(m, "_Dict_uint64_t_double");
    declare_dict<uint64_t, bool>(m, "_Dict_uint64_t_bool");
    declare_dict<int8_t, uint8_t>(m, "_Dict_int8_t_uint8_t");
    declare_dict<int8_t, uint16_t>(m, "_Dict_int8_t_uint16_t");
    declare_dict<int8_t, uint32_t>(m, "_Dict_int8_t_uint32_t");
    declare_dict<int8_t, uint64_t>(m, "_Dict_int8_t_uint64_t");
    declare_dict<int8_t, int8_t>(m, "_Dict_int8_t_int8_t");
    declare_dict<int8_t, int16_t>(m, "_Dict_int8_t_int16_t");
    declare_dict<int8_t, int32_t>(m, "_Dict_int8_t_int32_t");
    declare_dict<int8_t, int64_t>(m, "_Dict_int8_t_int64_t");
    declare_dict<int8_t, float>(m, "_Dict_int8_t_float");
    declare_dict<int8_t, double>(m, "_Dict_int8_t_double");
    declare_dict<int8_t, bool>(m, "_Dict_int8_t_bool");
    declare_dict<int16_t, uint8_t>(m, "_Dict_int16_t_uint8_t");
    declare_dict<int16_t, uint16_t>(m, "_Dict_int16_t_uint16_t");
    declare_dict<int16_t, uint32_t>(m, "_Dict_int16_t_uint32_t");
    declare_dict<int16_t, uint64_t>(m, "_Dict_int16_t_uint64_t");
    declare_dict<int16_t, int8_t>(m, "_Dict_int16_t_int8_t");
    declare_dict<int16_t, int16_t>(m, "_Dict_int16_t_int16_t");
    declare_dict<int16_t, int32_t>(m, "_Dict_int16_t_int32_t");
    declare_dict<int16_t, int64_t>(m, "_Dict_int16_t_int64_t");
    declare_dict<int16_t, float>(m, "_Dict_int16_t_float");
    declare_dict<int16_t, double>(m, "_Dict_int16_t_double");
    declare_dict<int16_t, bool>(m, "_Dict_int16_t_bool");
    declare_dict<int32_t, uint8_t>(m, "_Dict_int32_t_uint8_t");
    declare_dict<int32_t, uint16_t>(m, "_Dict_int32_t_uint16_t");
    declare_dict<int32_t, uint32_t>(m, "_Dict_int32_t_uint32_t");
    declare_dict<int32_t, uint64_t>(m, "_Dict_int32_t_uint64_t");
    declare_dict<int32_t, int8_t>(m, "_Dict_int32_t_int8_t");
    declare_dict<int32_t, int16_t>(m, "_Dict_int32_t_int16_t");
    declare_dict<int32_t, int32_t>(m, "_Dict_int32_t_int32_t");
    declare_dict<int32_t, int64_t>(m, "_Dict_int32_t_int64_t");
    declare_dict<int32_t, float>(m, "_Dict_int32_t_float");
    declare_dict<int32_t, double>(m, "_Dict_int32_t_double");
    declare_dict<int32_t, bool>(m, "_Dict_int32_t_bool");
    declare_dict<int64_t, uint8_t>(m, "_Dict_int64_t_uint8_t");
    declare_dict<int64_t, uint16_t>(m, "_Dict_int64_t_uint16_t");
    declare_dict<int64_t, uint32_t>(m, "_Dict_int64_t_uint32_t");
    declare_dict<int64_t, uint64_t>(m, "_Dict_int64_t_uint64_t");
    declare_dict<int64_t, int8_t>(m, "_Dict_int64_t_int8_t");
    declare_dict<int64_t, int16_t>(m, "_Dict_int64_t_int16_t");
    declare_dict<int64_t, int32_t>(m, "_Dict_int64_t_int32_t");
    declare_dict<int64_t, int64_t>(m, "_Dict_int64_t_int64_t");
    declare_dict<int64_t, float>(m, "_Dict_int64_t_float");
    declare_dict<int64_t, double>(m, "_Dict_int64_t_double");
    declare_dict<int64_t, bool>(m, "_Dict_int64_t_bool");
}