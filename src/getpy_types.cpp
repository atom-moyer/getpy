#include "getpy.cpp"

#include <pybind11/pybind11.h>


PYBIND11_MODULE(_getpy, m) {
    m.doc() = "A Fast and Memory Efficient Hash Map for Python";

    declare_dict<std::array<char, 4>, std::array<char, 1>>(m, "Dict_byte4_byte1");
    declare_dict<std::array<char, 4>, std::array<char, 2>>(m, "Dict_byte4_byte2");
    declare_dict<std::array<char, 4>, std::array<char, 3>>(m, "Dict_byte4_byte3");
    declare_dict<std::array<char, 4>, std::array<char, 4>>(m, "Dict_byte4_byte4");
    declare_dict<std::array<char, 4>, std::array<char, 5>>(m, "Dict_byte4_byte5");
    declare_dict<std::array<char, 4>, std::array<char, 6>>(m, "Dict_byte4_byte6");
    declare_dict<std::array<char, 4>, std::array<char, 7>>(m, "Dict_byte4_byte7");
    declare_dict<std::array<char, 4>, std::array<char, 8>>(m, "Dict_byte4_byte8");
    declare_dict<std::array<char, 4>, std::array<char, 9>>(m, "Dict_byte4_byte9");
    declare_dict<std::array<char, 4>, std::array<char, 10>>(m, "Dict_byte4_byte10");
    declare_dict<std::array<char, 4>, std::array<char, 11>>(m, "Dict_byte4_byte11");
    declare_dict<std::array<char, 4>, std::array<char, 12>>(m, "Dict_byte4_byte12");
    declare_dict<std::array<char, 4>, std::array<char, 13>>(m, "Dict_byte4_byte13");
    declare_dict<std::array<char, 4>, std::array<char, 14>>(m, "Dict_byte4_byte14");
    declare_dict<std::array<char, 4>, std::array<char, 15>>(m, "Dict_byte4_byte15");
    declare_dict<std::array<char, 4>, std::array<char, 16>>(m, "Dict_byte4_byte16");

    declare_dict<std::array<char, 8>, std::array<char, 1>>(m, "Dict_byte8_byte1");
    declare_dict<std::array<char, 8>, std::array<char, 2>>(m, "Dict_byte8_byte2");
    declare_dict<std::array<char, 8>, std::array<char, 3>>(m, "Dict_byte8_byte3");
    declare_dict<std::array<char, 8>, std::array<char, 4>>(m, "Dict_byte8_byte4");
    declare_dict<std::array<char, 8>, std::array<char, 5>>(m, "Dict_byte8_byte5");
    declare_dict<std::array<char, 8>, std::array<char, 6>>(m, "Dict_byte8_byte6");
    declare_dict<std::array<char, 8>, std::array<char, 7>>(m, "Dict_byte8_byte7");
    declare_dict<std::array<char, 8>, std::array<char, 8>>(m, "Dict_byte8_byte8");
    declare_dict<std::array<char, 8>, std::array<char, 9>>(m, "Dict_byte8_byte9");
    declare_dict<std::array<char, 8>, std::array<char, 10>>(m, "Dict_byte8_byte10");
    declare_dict<std::array<char, 8>, std::array<char, 11>>(m, "Dict_byte8_byte11");
    declare_dict<std::array<char, 8>, std::array<char, 12>>(m, "Dict_byte8_byte12");
    declare_dict<std::array<char, 8>, std::array<char, 13>>(m, "Dict_byte8_byte13");
    declare_dict<std::array<char, 8>, std::array<char, 14>>(m, "Dict_byte8_byte14");
    declare_dict<std::array<char, 8>, std::array<char, 15>>(m, "Dict_byte8_byte15");
    declare_dict<std::array<char, 8>, std::array<char, 16>>(m, "Dict_byte8_byte16");

    declare_set<std::array<char, 1>>(m, "Set_byte1");
    declare_set<std::array<char, 2>>(m, "Set_byte2");
    declare_set<std::array<char, 3>>(m, "Set_byte3");
    declare_set<std::array<char, 4>>(m, "Set_byte4");
    declare_set<std::array<char, 5>>(m, "Set_byte5");
    declare_set<std::array<char, 6>>(m, "Set_byte6");
    declare_set<std::array<char, 7>>(m, "Set_byte7");
    declare_set<std::array<char, 8>>(m, "Set_byte8");
    declare_set<std::array<char, 9>>(m, "Set_byte9");
    declare_set<std::array<char, 10>>(m, "Set_byte10");
    declare_set<std::array<char, 11>>(m, "Set_byte11");
    declare_set<std::array<char, 12>>(m, "Set_byte12");
    declare_set<std::array<char, 13>>(m, "Set_byte13");
    declare_set<std::array<char, 14>>(m, "Set_byte14");
    declare_set<std::array<char, 15>>(m, "Set_byte15");
    declare_set<std::array<char, 16>>(m, "Set_byte16");

}
