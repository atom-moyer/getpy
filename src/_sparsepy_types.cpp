#include "_sparsepy.cpp"

#include <pybind11/pybind11.h>

PYBIND11_MODULE(_sparsepy, m) {
    m.doc() = "Fast and Memory Efficient Sparse Hash Tables for Python";

    declare_dict<uint8_t, uint8_t>(m, "_Dict_Uint8_Uint8");
    declare_dict<uint8_t, uint16_t>(m, "_Dict_Uint8_Uint16");
    declare_dict<uint8_t, uint32_t>(m, "_Dict_Uint8_Uint32");
    declare_dict<uint8_t, uint64_t>(m, "_Dict_Uint8_Uint64");
    declare_dict<uint8_t, int8_t>(m, "_Dict_Uint8_Int8");
    declare_dict<uint8_t, int16_t>(m, "_Dict_Uint8_Int16");
    declare_dict<uint8_t, int32_t>(m, "_Dict_Uint8_Int32");
    declare_dict<uint8_t, int64_t>(m, "_Dict_Uint8_Int64");
    declare_dict<uint16_t, uint8_t>(m, "_Dict_Uint16_Uint8");
    declare_dict<uint16_t, uint16_t>(m, "_Dict_Uint16_Uint16");
    declare_dict<uint16_t, uint32_t>(m, "_Dict_Uint16_Uint32");
    declare_dict<uint16_t, uint64_t>(m, "_Dict_Uint16_Uint64");
    declare_dict<uint16_t, int8_t>(m, "_Dict_Uint16_Int8");
    declare_dict<uint16_t, int16_t>(m, "_Dict_Uint16_Int16");
    declare_dict<uint16_t, int32_t>(m, "_Dict_Uint16_Int32");
    declare_dict<uint16_t, int64_t>(m, "_Dict_Uint16_Int64");
    declare_dict<uint32_t, uint8_t>(m, "_Dict_Uint32_Uint8");
    declare_dict<uint32_t, uint16_t>(m, "_Dict_Uint32_Uint16");
    declare_dict<uint32_t, uint32_t>(m, "_Dict_Uint32_Uint32");
    declare_dict<uint32_t, uint64_t>(m, "_Dict_Uint32_Uint64");
    declare_dict<uint32_t, int8_t>(m, "_Dict_Uint32_Int8");
    declare_dict<uint32_t, int16_t>(m, "_Dict_Uint32_Int16");
    declare_dict<uint32_t, int32_t>(m, "_Dict_Uint32_Int32");
    declare_dict<uint32_t, int64_t>(m, "_Dict_Uint32_Int64");
    declare_dict<uint64_t, uint8_t>(m, "_Dict_Uint64_Uint8");
    declare_dict<uint64_t, uint16_t>(m, "_Dict_Uint64_Uint16");
    declare_dict<uint64_t, uint32_t>(m, "_Dict_Uint64_Uint32");
    declare_dict<uint64_t, uint64_t>(m, "_Dict_Uint64_Uint64");
    declare_dict<uint64_t, int8_t>(m, "_Dict_Uint64_Int8");
    declare_dict<uint64_t, int16_t>(m, "_Dict_Uint64_Int16");
    declare_dict<uint64_t, int32_t>(m, "_Dict_Uint64_Int32");
    declare_dict<uint64_t, int64_t>(m, "_Dict_Uint64_Int64");
    declare_dict<int8_t, uint8_t>(m, "_Dict_Int8_Uint8");
    declare_dict<int8_t, uint16_t>(m, "_Dict_Int8_Uint16");
    declare_dict<int8_t, uint32_t>(m, "_Dict_Int8_Uint32");
    declare_dict<int8_t, uint64_t>(m, "_Dict_Int8_Uint64");
    declare_dict<int8_t, int8_t>(m, "_Dict_Int8_Int8");
    declare_dict<int8_t, int16_t>(m, "_Dict_Int8_Int16");
    declare_dict<int8_t, int32_t>(m, "_Dict_Int8_Int32");
    declare_dict<int8_t, int64_t>(m, "_Dict_Int8_Int64");
    declare_dict<int16_t, uint8_t>(m, "_Dict_Int16_Uint8");
    declare_dict<int16_t, uint16_t>(m, "_Dict_Int16_Uint16");
    declare_dict<int16_t, uint32_t>(m, "_Dict_Int16_Uint32");
    declare_dict<int16_t, uint64_t>(m, "_Dict_Int16_Uint64");
    declare_dict<int16_t, int8_t>(m, "_Dict_Int16_Int8");
    declare_dict<int16_t, int16_t>(m, "_Dict_Int16_Int16");
    declare_dict<int16_t, int32_t>(m, "_Dict_Int16_Int32");
    declare_dict<int16_t, int64_t>(m, "_Dict_Int16_Int64");
    declare_dict<int32_t, uint8_t>(m, "_Dict_Int32_Uint8");
    declare_dict<int32_t, uint16_t>(m, "_Dict_Int32_Uint16");
    declare_dict<int32_t, uint32_t>(m, "_Dict_Int32_Uint32");
    declare_dict<int32_t, uint64_t>(m, "_Dict_Int32_Uint64");
    declare_dict<int32_t, int8_t>(m, "_Dict_Int32_Int8");
    declare_dict<int32_t, int16_t>(m, "_Dict_Int32_Int16");
    declare_dict<int32_t, int32_t>(m, "_Dict_Int32_Int32");
    declare_dict<int32_t, int64_t>(m, "_Dict_Int32_Int64");
    declare_dict<int64_t, uint8_t>(m, "_Dict_Int64_Uint8");
    declare_dict<int64_t, uint16_t>(m, "_Dict_Int64_Uint16");
    declare_dict<int64_t, uint32_t>(m, "_Dict_Int64_Uint32");
    declare_dict<int64_t, uint64_t>(m, "_Dict_Int64_Uint64");
    declare_dict<int64_t, int8_t>(m, "_Dict_Int64_Int8");
    declare_dict<int64_t, int16_t>(m, "_Dict_Int64_Int16");
    declare_dict<int64_t, int32_t>(m, "_Dict_Int64_Int32");
    declare_dict<int64_t, int64_t>(m, "_Dict_Int64_Int64");
}
