#include "getpy.cpp"

#include <pybind11/pybind11.h>

PYBIND11_MODULE(_getpy, m) {
    m.doc() = "A Fast and Memory Efficient Hash Map for Python";

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
    declare_dict<uint32_t, std::array<char,4>>(m, "Dict_uint32_byteset4");
    declare_dict<uint32_t, std::array<char,8>>(m, "Dict_uint32_byteset8");
    declare_dict<uint32_t, std::array<char,12>>(m, "Dict_uint32_byteset12");
    declare_dict<uint32_t, std::array<char,16>>(m, "Dict_uint32_byteset16");
    declare_dict<uint32_t, std::array<char,20>>(m, "Dict_uint32_byteset20");
    declare_dict<uint32_t, std::array<char,24>>(m, "Dict_uint32_byteset24");
    declare_dict<uint32_t, std::array<char,28>>(m, "Dict_uint32_byteset28");
    declare_dict<uint32_t, std::array<char,32>>(m, "Dict_uint32_byteset32");
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
    declare_dict<uint64_t, std::array<char,4>>(m, "Dict_uint64_byteset4");
    declare_dict<uint64_t, std::array<char,8>>(m, "Dict_uint64_byteset8");
    declare_dict<uint64_t, std::array<char,12>>(m, "Dict_uint64_byteset12");
    declare_dict<uint64_t, std::array<char,16>>(m, "Dict_uint64_byteset16");
    declare_dict<uint64_t, std::array<char,20>>(m, "Dict_uint64_byteset20");
    declare_dict<uint64_t, std::array<char,24>>(m, "Dict_uint64_byteset24");
    declare_dict<uint64_t, std::array<char,28>>(m, "Dict_uint64_byteset28");
    declare_dict<uint64_t, std::array<char,32>>(m, "Dict_uint64_byteset32");
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
    declare_dict<int32_t, std::array<char,4>>(m, "Dict_int32_byteset4");
    declare_dict<int32_t, std::array<char,8>>(m, "Dict_int32_byteset8");
    declare_dict<int32_t, std::array<char,12>>(m, "Dict_int32_byteset12");
    declare_dict<int32_t, std::array<char,16>>(m, "Dict_int32_byteset16");
    declare_dict<int32_t, std::array<char,20>>(m, "Dict_int32_byteset20");
    declare_dict<int32_t, std::array<char,24>>(m, "Dict_int32_byteset24");
    declare_dict<int32_t, std::array<char,28>>(m, "Dict_int32_byteset28");
    declare_dict<int32_t, std::array<char,32>>(m, "Dict_int32_byteset32");
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
    declare_dict<int64_t, std::array<char,4>>(m, "Dict_int64_byteset4");
    declare_dict<int64_t, std::array<char,8>>(m, "Dict_int64_byteset8");
    declare_dict<int64_t, std::array<char,12>>(m, "Dict_int64_byteset12");
    declare_dict<int64_t, std::array<char,16>>(m, "Dict_int64_byteset16");
    declare_dict<int64_t, std::array<char,20>>(m, "Dict_int64_byteset20");
    declare_dict<int64_t, std::array<char,24>>(m, "Dict_int64_byteset24");
    declare_dict<int64_t, std::array<char,28>>(m, "Dict_int64_byteset28");
    declare_dict<int64_t, std::array<char,32>>(m, "Dict_int64_byteset32");
    declare_dict<std::array<char,4>, uint8_t>(m, "Dict_byteset4_uint8");
    declare_dict<std::array<char,4>, uint16_t>(m, "Dict_byteset4_uint16");
    declare_dict<std::array<char,4>, uint32_t>(m, "Dict_byteset4_uint32");
    declare_dict<std::array<char,4>, uint64_t>(m, "Dict_byteset4_uint64");
    declare_dict<std::array<char,4>, int8_t>(m, "Dict_byteset4_int8");
    declare_dict<std::array<char,4>, int16_t>(m, "Dict_byteset4_int16");
    declare_dict<std::array<char,4>, int32_t>(m, "Dict_byteset4_int32");
    declare_dict<std::array<char,4>, int64_t>(m, "Dict_byteset4_int64");
    declare_dict<std::array<char,4>, float>(m, "Dict_byteset4_float32");
    declare_dict<std::array<char,4>, double>(m, "Dict_byteset4_float64");
    declare_dict<std::array<char,4>, std::array<char,4>>(m, "Dict_byteset4_byteset4");
    declare_dict<std::array<char,4>, std::array<char,8>>(m, "Dict_byteset4_byteset8");
    declare_dict<std::array<char,4>, std::array<char,12>>(m, "Dict_byteset4_byteset12");
    declare_dict<std::array<char,4>, std::array<char,16>>(m, "Dict_byteset4_byteset16");
    declare_dict<std::array<char,4>, std::array<char,20>>(m, "Dict_byteset4_byteset20");
    declare_dict<std::array<char,4>, std::array<char,24>>(m, "Dict_byteset4_byteset24");
    declare_dict<std::array<char,4>, std::array<char,28>>(m, "Dict_byteset4_byteset28");
    declare_dict<std::array<char,4>, std::array<char,32>>(m, "Dict_byteset4_byteset32");
    declare_dict<std::array<char,8>, uint8_t>(m, "Dict_byteset8_uint8");
    declare_dict<std::array<char,8>, uint16_t>(m, "Dict_byteset8_uint16");
    declare_dict<std::array<char,8>, uint32_t>(m, "Dict_byteset8_uint32");
    declare_dict<std::array<char,8>, uint64_t>(m, "Dict_byteset8_uint64");
    declare_dict<std::array<char,8>, int8_t>(m, "Dict_byteset8_int8");
    declare_dict<std::array<char,8>, int16_t>(m, "Dict_byteset8_int16");
    declare_dict<std::array<char,8>, int32_t>(m, "Dict_byteset8_int32");
    declare_dict<std::array<char,8>, int64_t>(m, "Dict_byteset8_int64");
    declare_dict<std::array<char,8>, float>(m, "Dict_byteset8_float32");
    declare_dict<std::array<char,8>, double>(m, "Dict_byteset8_float64");
    declare_dict<std::array<char,8>, std::array<char,4>>(m, "Dict_byteset8_byteset4");
    declare_dict<std::array<char,8>, std::array<char,8>>(m, "Dict_byteset8_byteset8");
    declare_dict<std::array<char,8>, std::array<char,12>>(m, "Dict_byteset8_byteset12");
    declare_dict<std::array<char,8>, std::array<char,16>>(m, "Dict_byteset8_byteset16");
    declare_dict<std::array<char,8>, std::array<char,20>>(m, "Dict_byteset8_byteset20");
    declare_dict<std::array<char,8>, std::array<char,24>>(m, "Dict_byteset8_byteset24");
    declare_dict<std::array<char,8>, std::array<char,28>>(m, "Dict_byteset8_byteset28");
    declare_dict<std::array<char,8>, std::array<char,32>>(m, "Dict_byteset8_byteset32");
    declare_dict<std::array<char,12>, uint8_t>(m, "Dict_byteset12_uint8");
    declare_dict<std::array<char,12>, uint16_t>(m, "Dict_byteset12_uint16");
    declare_dict<std::array<char,12>, uint32_t>(m, "Dict_byteset12_uint32");
    declare_dict<std::array<char,12>, uint64_t>(m, "Dict_byteset12_uint64");
    declare_dict<std::array<char,12>, int8_t>(m, "Dict_byteset12_int8");
    declare_dict<std::array<char,12>, int16_t>(m, "Dict_byteset12_int16");
    declare_dict<std::array<char,12>, int32_t>(m, "Dict_byteset12_int32");
    declare_dict<std::array<char,12>, int64_t>(m, "Dict_byteset12_int64");
    declare_dict<std::array<char,12>, float>(m, "Dict_byteset12_float32");
    declare_dict<std::array<char,12>, double>(m, "Dict_byteset12_float64");
    declare_dict<std::array<char,12>, std::array<char,4>>(m, "Dict_byteset12_byteset4");
    declare_dict<std::array<char,12>, std::array<char,8>>(m, "Dict_byteset12_byteset8");
    declare_dict<std::array<char,12>, std::array<char,12>>(m, "Dict_byteset12_byteset12");
    declare_dict<std::array<char,12>, std::array<char,16>>(m, "Dict_byteset12_byteset16");
    declare_dict<std::array<char,12>, std::array<char,20>>(m, "Dict_byteset12_byteset20");
    declare_dict<std::array<char,12>, std::array<char,24>>(m, "Dict_byteset12_byteset24");
    declare_dict<std::array<char,12>, std::array<char,28>>(m, "Dict_byteset12_byteset28");
    declare_dict<std::array<char,12>, std::array<char,32>>(m, "Dict_byteset12_byteset32");
    declare_dict<std::array<char,16>, uint8_t>(m, "Dict_byteset16_uint8");
    declare_dict<std::array<char,16>, uint16_t>(m, "Dict_byteset16_uint16");
    declare_dict<std::array<char,16>, uint32_t>(m, "Dict_byteset16_uint32");
    declare_dict<std::array<char,16>, uint64_t>(m, "Dict_byteset16_uint64");
    declare_dict<std::array<char,16>, int8_t>(m, "Dict_byteset16_int8");
    declare_dict<std::array<char,16>, int16_t>(m, "Dict_byteset16_int16");
    declare_dict<std::array<char,16>, int32_t>(m, "Dict_byteset16_int32");
    declare_dict<std::array<char,16>, int64_t>(m, "Dict_byteset16_int64");
    declare_dict<std::array<char,16>, float>(m, "Dict_byteset16_float32");
    declare_dict<std::array<char,16>, double>(m, "Dict_byteset16_float64");
    declare_dict<std::array<char,16>, std::array<char,4>>(m, "Dict_byteset16_byteset4");
    declare_dict<std::array<char,16>, std::array<char,8>>(m, "Dict_byteset16_byteset8");
    declare_dict<std::array<char,16>, std::array<char,12>>(m, "Dict_byteset16_byteset12");
    declare_dict<std::array<char,16>, std::array<char,16>>(m, "Dict_byteset16_byteset16");
    declare_dict<std::array<char,16>, std::array<char,20>>(m, "Dict_byteset16_byteset20");
    declare_dict<std::array<char,16>, std::array<char,24>>(m, "Dict_byteset16_byteset24");
    declare_dict<std::array<char,16>, std::array<char,28>>(m, "Dict_byteset16_byteset28");
    declare_dict<std::array<char,16>, std::array<char,32>>(m, "Dict_byteset16_byteset32");
    declare_dict<std::array<char,20>, uint8_t>(m, "Dict_byteset20_uint8");
    declare_dict<std::array<char,20>, uint16_t>(m, "Dict_byteset20_uint16");
    declare_dict<std::array<char,20>, uint32_t>(m, "Dict_byteset20_uint32");
    declare_dict<std::array<char,20>, uint64_t>(m, "Dict_byteset20_uint64");
    declare_dict<std::array<char,20>, int8_t>(m, "Dict_byteset20_int8");
    declare_dict<std::array<char,20>, int16_t>(m, "Dict_byteset20_int16");
    declare_dict<std::array<char,20>, int32_t>(m, "Dict_byteset20_int32");
    declare_dict<std::array<char,20>, int64_t>(m, "Dict_byteset20_int64");
    declare_dict<std::array<char,20>, float>(m, "Dict_byteset20_float32");
    declare_dict<std::array<char,20>, double>(m, "Dict_byteset20_float64");
    declare_dict<std::array<char,20>, std::array<char,4>>(m, "Dict_byteset20_byteset4");
    declare_dict<std::array<char,20>, std::array<char,8>>(m, "Dict_byteset20_byteset8");
    declare_dict<std::array<char,20>, std::array<char,12>>(m, "Dict_byteset20_byteset12");
    declare_dict<std::array<char,20>, std::array<char,16>>(m, "Dict_byteset20_byteset16");
    declare_dict<std::array<char,20>, std::array<char,20>>(m, "Dict_byteset20_byteset20");
    declare_dict<std::array<char,20>, std::array<char,24>>(m, "Dict_byteset20_byteset24");
    declare_dict<std::array<char,20>, std::array<char,28>>(m, "Dict_byteset20_byteset28");
    declare_dict<std::array<char,20>, std::array<char,32>>(m, "Dict_byteset20_byteset32");
    declare_dict<std::array<char,24>, uint8_t>(m, "Dict_byteset24_uint8");
    declare_dict<std::array<char,24>, uint16_t>(m, "Dict_byteset24_uint16");
    declare_dict<std::array<char,24>, uint32_t>(m, "Dict_byteset24_uint32");
    declare_dict<std::array<char,24>, uint64_t>(m, "Dict_byteset24_uint64");
    declare_dict<std::array<char,24>, int8_t>(m, "Dict_byteset24_int8");
    declare_dict<std::array<char,24>, int16_t>(m, "Dict_byteset24_int16");
    declare_dict<std::array<char,24>, int32_t>(m, "Dict_byteset24_int32");
    declare_dict<std::array<char,24>, int64_t>(m, "Dict_byteset24_int64");
    declare_dict<std::array<char,24>, float>(m, "Dict_byteset24_float32");
    declare_dict<std::array<char,24>, double>(m, "Dict_byteset24_float64");
    declare_dict<std::array<char,24>, std::array<char,4>>(m, "Dict_byteset24_byteset4");
    declare_dict<std::array<char,24>, std::array<char,8>>(m, "Dict_byteset24_byteset8");
    declare_dict<std::array<char,24>, std::array<char,12>>(m, "Dict_byteset24_byteset12");
    declare_dict<std::array<char,24>, std::array<char,16>>(m, "Dict_byteset24_byteset16");
    declare_dict<std::array<char,24>, std::array<char,20>>(m, "Dict_byteset24_byteset20");
    declare_dict<std::array<char,24>, std::array<char,24>>(m, "Dict_byteset24_byteset24");
    declare_dict<std::array<char,24>, std::array<char,28>>(m, "Dict_byteset24_byteset28");
    declare_dict<std::array<char,24>, std::array<char,32>>(m, "Dict_byteset24_byteset32");
    declare_dict<std::array<char,28>, uint8_t>(m, "Dict_byteset28_uint8");
    declare_dict<std::array<char,28>, uint16_t>(m, "Dict_byteset28_uint16");
    declare_dict<std::array<char,28>, uint32_t>(m, "Dict_byteset28_uint32");
    declare_dict<std::array<char,28>, uint64_t>(m, "Dict_byteset28_uint64");
    declare_dict<std::array<char,28>, int8_t>(m, "Dict_byteset28_int8");
    declare_dict<std::array<char,28>, int16_t>(m, "Dict_byteset28_int16");
    declare_dict<std::array<char,28>, int32_t>(m, "Dict_byteset28_int32");
    declare_dict<std::array<char,28>, int64_t>(m, "Dict_byteset28_int64");
    declare_dict<std::array<char,28>, float>(m, "Dict_byteset28_float32");
    declare_dict<std::array<char,28>, double>(m, "Dict_byteset28_float64");
    declare_dict<std::array<char,28>, std::array<char,4>>(m, "Dict_byteset28_byteset4");
    declare_dict<std::array<char,28>, std::array<char,8>>(m, "Dict_byteset28_byteset8");
    declare_dict<std::array<char,28>, std::array<char,12>>(m, "Dict_byteset28_byteset12");
    declare_dict<std::array<char,28>, std::array<char,16>>(m, "Dict_byteset28_byteset16");
    declare_dict<std::array<char,28>, std::array<char,20>>(m, "Dict_byteset28_byteset20");
    declare_dict<std::array<char,28>, std::array<char,24>>(m, "Dict_byteset28_byteset24");
    declare_dict<std::array<char,28>, std::array<char,28>>(m, "Dict_byteset28_byteset28");
    declare_dict<std::array<char,28>, std::array<char,32>>(m, "Dict_byteset28_byteset32");
    declare_dict<std::array<char,32>, uint8_t>(m, "Dict_byteset32_uint8");
    declare_dict<std::array<char,32>, uint16_t>(m, "Dict_byteset32_uint16");
    declare_dict<std::array<char,32>, uint32_t>(m, "Dict_byteset32_uint32");
    declare_dict<std::array<char,32>, uint64_t>(m, "Dict_byteset32_uint64");
    declare_dict<std::array<char,32>, int8_t>(m, "Dict_byteset32_int8");
    declare_dict<std::array<char,32>, int16_t>(m, "Dict_byteset32_int16");
    declare_dict<std::array<char,32>, int32_t>(m, "Dict_byteset32_int32");
    declare_dict<std::array<char,32>, int64_t>(m, "Dict_byteset32_int64");
    declare_dict<std::array<char,32>, float>(m, "Dict_byteset32_float32");
    declare_dict<std::array<char,32>, double>(m, "Dict_byteset32_float64");
    declare_dict<std::array<char,32>, std::array<char,4>>(m, "Dict_byteset32_byteset4");
    declare_dict<std::array<char,32>, std::array<char,8>>(m, "Dict_byteset32_byteset8");
    declare_dict<std::array<char,32>, std::array<char,12>>(m, "Dict_byteset32_byteset12");
    declare_dict<std::array<char,32>, std::array<char,16>>(m, "Dict_byteset32_byteset16");
    declare_dict<std::array<char,32>, std::array<char,20>>(m, "Dict_byteset32_byteset20");
    declare_dict<std::array<char,32>, std::array<char,24>>(m, "Dict_byteset32_byteset24");
    declare_dict<std::array<char,32>, std::array<char,28>>(m, "Dict_byteset32_byteset28");
    declare_dict<std::array<char,32>, std::array<char,32>>(m, "Dict_byteset32_byteset32");

    declare_set<uint32_t>(m, "Set_uint32");
    declare_set<uint64_t>(m, "Set_uint64");
    declare_set<int32_t>(m, "Set_int32");
    declare_set<int64_t>(m, "Set_int64");
    declare_set<std::array<char,4>>(m, "Set_byteset4");
    declare_set<std::array<char,8>>(m, "Set_byteset8");
    declare_set<std::array<char,12>>(m, "Set_byteset12");
    declare_set<std::array<char,16>>(m, "Set_byteset16");
    declare_set<std::array<char,20>>(m, "Set_byteset20");
    declare_set<std::array<char,24>>(m, "Set_byteset24");
    declare_set<std::array<char,28>>(m, "Set_byteset28");
    declare_set<std::array<char,32>>(m, "Set_byteset32");
}
