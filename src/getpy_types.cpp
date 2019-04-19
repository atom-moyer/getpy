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

struct __attribute__((packed)) rtarray20_uint8 { uint8_t A; uint8_t C; uint8_t D; uint8_t E; uint8_t F; uint8_t G; uint8_t H; uint8_t I; uint8_t K; uint8_t L; uint8_t M; uint8_t N; uint8_t P; uint8_t Q; uint8_t R; uint8_t S; uint8_t T; uint8_t V; uint8_t W; uint8_t Y;};
template<class Archive> void serialize(Archive & archive, rtarray20_uint8 & rtarray20) { archive( rtarray20.A, rtarray20.C, rtarray20.D, rtarray20.E, rtarray20.F, rtarray20.G, rtarray20.H, rtarray20.I, rtarray20.K, rtarray20.L, rtarray20.M, rtarray20.N, rtarray20.P, rtarray20.Q, rtarray20.R, rtarray20.S, rtarray20.T, rtarray20.V, rtarray20.W, rtarray20.Y ); }

struct __attribute__((packed)) rpmatrix400_uint8 { rtarray20_uint8 A; rtarray20_uint8 C; rtarray20_uint8 D; rtarray20_uint8 E; rtarray20_uint8 F; rtarray20_uint8 G; rtarray20_uint8 H; rtarray20_uint8 I; rtarray20_uint8 K; rtarray20_uint8 L; rtarray20_uint8 M; rtarray20_uint8 N; rtarray20_uint8 P; rtarray20_uint8 Q; rtarray20_uint8 R; rtarray20_uint8 S; rtarray20_uint8 T; rtarray20_uint8 V; rtarray20_uint8 W; rtarray20_uint8 Y; };
template<class Archive> void serialize(Archive & archive, rpmatrix400_uint8 & rpmatrix400) { archive( rpmatrix400.A, rpmatrix400.C, rpmatrix400.D, rpmatrix400.E, rpmatrix400.F, rpmatrix400.G, rpmatrix400.H, rpmatrix400.I, rpmatrix400.K, rpmatrix400.L, rpmatrix400.M, rpmatrix400.N, rpmatrix400.P, rpmatrix400.Q, rpmatrix400.R, rpmatrix400.S, rpmatrix400.T, rpmatrix400.V, rpmatrix400.W, rpmatrix400.Y ); }


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
    PYBIND11_NUMPY_DTYPE(rtarray20_uint8, A, C, D, E, F, G, H, I, K, L, M, N, P, Q, R, S, T, V, W, Y );
    PYBIND11_NUMPY_DTYPE(rpmatrix400_uint8, A, C, D, E, F, G, H, I, K, L, M, N, P, Q, R, S, T, V, W, Y );

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
    declare_dict<std::array<char, 4>, rtarray20_uint8>(m, "Dict_str4_rtarray20_uint8");
    declare_dict<std::array<char, 4>, rpmatrix400_uint8>(m, "Dict_str4_rpmatrix400_uint8");
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
    declare_dict<std::array<char, 8>, rtarray20_uint8>(m, "Dict_str8_rtarray20_uint8");
    declare_dict<std::array<char, 8>, rpmatrix400_uint8>(m, "Dict_str8_rpmatrix400_uint8");
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
    declare_dict<uint32_t, rtarray20_uint8>(m, "Dict_uint32_rtarray20_uint8");
    declare_dict<uint32_t, rpmatrix400_uint8>(m, "Dict_uint32_rpmatrix400_uint8");
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
    declare_dict<uint64_t, rtarray20_uint8>(m, "Dict_uint64_rtarray20_uint8");
    declare_dict<uint64_t, rpmatrix400_uint8>(m, "Dict_uint64_rpmatrix400_uint8");
}
