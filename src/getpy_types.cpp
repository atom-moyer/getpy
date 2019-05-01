#include "getpy.cpp"

#include <pybind11/pybind11.h>

struct pair_str4_str4 { std::array<char, 4> first; std::array<char, 4> second; };
template<class Archive> void serialize(Archive & archive, pair_str4_str4 & pair) { archive( pair.first, pair.second ); }
pair_str4_str4 & operator += ( pair_str4_str4 & a, pair_str4_str4 b ) { a.first += b.first; a.second += b.second; }
pair_str4_str4 & operator -= ( pair_str4_str4 & a, pair_str4_str4 b ) { a.first -= b.first; a.second -= b.second; }
pair_str4_str4 & operator |= ( pair_str4_str4 & a, pair_str4_str4 b ) { a.first |= b.first; a.second |= b.second; }
pair_str4_str4 & operator &= ( pair_str4_str4 & a, pair_str4_str4 b ) { a.first &= b.first; a.second &= b.second; }

struct pair_str8_str8 { std::array<char, 8> first; std::array<char, 8> second; };
template<class Archive> void serialize(Archive & archive, pair_str8_str8 & pair) { archive( pair.first, pair.second ); }
pair_str8_str8 & operator += ( pair_str8_str8 & a, pair_str8_str8 b ) { a.first += b.first; a.second += b.second; }
pair_str8_str8 & operator -= ( pair_str8_str8 & a, pair_str8_str8 b ) { a.first -= b.first; a.second -= b.second; }
pair_str8_str8 & operator |= ( pair_str8_str8 & a, pair_str8_str8 b ) { a.first |= b.first; a.second |= b.second; }
pair_str8_str8 & operator &= ( pair_str8_str8 & a, pair_str8_str8 b ) { a.first &= b.first; a.second &= b.second; }

struct pair_str16_str16 { std::array<char, 16> first; std::array<char, 16> second; };
template<class Archive> void serialize(Archive & archive, pair_str16_str16 & pair) { archive( pair.first, pair.second ); }
pair_str16_str16 & operator += ( pair_str16_str16 & a, pair_str16_str16 b ) { a.first += b.first; a.second += b.second; }
pair_str16_str16 & operator -= ( pair_str16_str16 & a, pair_str16_str16 b ) { a.first -= b.first; a.second -= b.second; }
pair_str16_str16 & operator |= ( pair_str16_str16 & a, pair_str16_str16 b ) { a.first |= b.first; a.second |= b.second; }
pair_str16_str16 & operator &= ( pair_str16_str16 & a, pair_str16_str16 b ) { a.first &= b.first; a.second &= b.second; }

struct pair_str32_str32 { std::array<char, 32> first; std::array<char, 32> second; };
template<class Archive> void serialize(Archive & archive, pair_str32_str32 & pair) { archive( pair.first, pair.second ); }
pair_str32_str32 & operator += ( pair_str32_str32 & a, pair_str32_str32 b ) { a.first += b.first; a.second += b.second; }
pair_str32_str32 & operator -= ( pair_str32_str32 & a, pair_str32_str32 b ) { a.first -= b.first; a.second -= b.second; }
pair_str32_str32 & operator |= ( pair_str32_str32 & a, pair_str32_str32 b ) { a.first |= b.first; a.second |= b.second; }
pair_str32_str32 & operator &= ( pair_str32_str32 & a, pair_str32_str32 b ) { a.first &= b.first; a.second &= b.second; }

struct pair_uint8_uint8 { uint8_t first; uint8_t second; };
template<class Archive> void serialize(Archive & archive, pair_uint8_uint8 & pair) { archive( pair.first, pair.second ); }
pair_uint8_uint8 & operator += ( pair_uint8_uint8 & a, pair_uint8_uint8 b ) { a.first += b.first; a.second += b.second; }
pair_uint8_uint8 & operator -= ( pair_uint8_uint8 & a, pair_uint8_uint8 b ) { a.first -= b.first; a.second -= b.second; }
pair_uint8_uint8 & operator |= ( pair_uint8_uint8 & a, pair_uint8_uint8 b ) { a.first |= b.first; a.second |= b.second; }
pair_uint8_uint8 & operator &= ( pair_uint8_uint8 & a, pair_uint8_uint8 b ) { a.first &= b.first; a.second &= b.second; }

struct pair_uint16_uint16 { uint16_t first; uint16_t second; };
template<class Archive> void serialize(Archive & archive, pair_uint16_uint16 & pair) { archive( pair.first, pair.second ); }
pair_uint16_uint16 & operator += ( pair_uint16_uint16 & a, pair_uint16_uint16 b ) { a.first += b.first; a.second += b.second; }
pair_uint16_uint16 & operator -= ( pair_uint16_uint16 & a, pair_uint16_uint16 b ) { a.first -= b.first; a.second -= b.second; }
pair_uint16_uint16 & operator |= ( pair_uint16_uint16 & a, pair_uint16_uint16 b ) { a.first |= b.first; a.second |= b.second; }
pair_uint16_uint16 & operator &= ( pair_uint16_uint16 & a, pair_uint16_uint16 b ) { a.first &= b.first; a.second &= b.second; }

struct pair_uint32_uint32 { uint32_t first; uint32_t second; };
template<class Archive> void serialize(Archive & archive, pair_uint32_uint32 & pair) { archive( pair.first, pair.second ); }
pair_uint32_uint32 & operator += ( pair_uint32_uint32 & a, pair_uint32_uint32 b ) { a.first += b.first; a.second += b.second; }
pair_uint32_uint32 & operator -= ( pair_uint32_uint32 & a, pair_uint32_uint32 b ) { a.first -= b.first; a.second -= b.second; }
pair_uint32_uint32 & operator |= ( pair_uint32_uint32 & a, pair_uint32_uint32 b ) { a.first |= b.first; a.second |= b.second; }
pair_uint32_uint32 & operator &= ( pair_uint32_uint32 & a, pair_uint32_uint32 b ) { a.first &= b.first; a.second &= b.second; }

struct pair_uint64_uint64 { uint64_t first; uint64_t second; };
template<class Archive> void serialize(Archive & archive, pair_uint64_uint64 & pair) { archive( pair.first, pair.second ); }
pair_uint64_uint64 & operator += ( pair_uint64_uint64 & a, pair_uint64_uint64 b ) { a.first += b.first; a.second += b.second; }
pair_uint64_uint64 & operator -= ( pair_uint64_uint64 & a, pair_uint64_uint64 b ) { a.first -= b.first; a.second -= b.second; }
pair_uint64_uint64 & operator |= ( pair_uint64_uint64 & a, pair_uint64_uint64 b ) { a.first |= b.first; a.second |= b.second; }
pair_uint64_uint64 & operator &= ( pair_uint64_uint64 & a, pair_uint64_uint64 b ) { a.first &= b.first; a.second &= b.second; }

struct pair_int8_int8 { int8_t first; int8_t second; };
template<class Archive> void serialize(Archive & archive, pair_int8_int8 & pair) { archive( pair.first, pair.second ); }
pair_int8_int8 & operator += ( pair_int8_int8 & a, pair_int8_int8 b ) { a.first += b.first; a.second += b.second; }
pair_int8_int8 & operator -= ( pair_int8_int8 & a, pair_int8_int8 b ) { a.first -= b.first; a.second -= b.second; }
pair_int8_int8 & operator |= ( pair_int8_int8 & a, pair_int8_int8 b ) { a.first |= b.first; a.second |= b.second; }
pair_int8_int8 & operator &= ( pair_int8_int8 & a, pair_int8_int8 b ) { a.first &= b.first; a.second &= b.second; }

struct pair_int16_int16 { int16_t first; int16_t second; };
template<class Archive> void serialize(Archive & archive, pair_int16_int16 & pair) { archive( pair.first, pair.second ); }
pair_int16_int16 & operator += ( pair_int16_int16 & a, pair_int16_int16 b ) { a.first += b.first; a.second += b.second; }
pair_int16_int16 & operator -= ( pair_int16_int16 & a, pair_int16_int16 b ) { a.first -= b.first; a.second -= b.second; }
pair_int16_int16 & operator |= ( pair_int16_int16 & a, pair_int16_int16 b ) { a.first |= b.first; a.second |= b.second; }
pair_int16_int16 & operator &= ( pair_int16_int16 & a, pair_int16_int16 b ) { a.first &= b.first; a.second &= b.second; }

struct pair_int32_int32 { int32_t first; int32_t second; };
template<class Archive> void serialize(Archive & archive, pair_int32_int32 & pair) { archive( pair.first, pair.second ); }
pair_int32_int32 & operator += ( pair_int32_int32 & a, pair_int32_int32 b ) { a.first += b.first; a.second += b.second; }
pair_int32_int32 & operator -= ( pair_int32_int32 & a, pair_int32_int32 b ) { a.first -= b.first; a.second -= b.second; }
pair_int32_int32 & operator |= ( pair_int32_int32 & a, pair_int32_int32 b ) { a.first |= b.first; a.second |= b.second; }
pair_int32_int32 & operator &= ( pair_int32_int32 & a, pair_int32_int32 b ) { a.first &= b.first; a.second &= b.second; }

struct pair_int64_int64 { int64_t first; int64_t second; };
template<class Archive> void serialize(Archive & archive, pair_int64_int64 & pair) { archive( pair.first, pair.second ); }
pair_int64_int64 & operator += ( pair_int64_int64 & a, pair_int64_int64 b ) { a.first += b.first; a.second += b.second; }
pair_int64_int64 & operator -= ( pair_int64_int64 & a, pair_int64_int64 b ) { a.first -= b.first; a.second -= b.second; }
pair_int64_int64 & operator |= ( pair_int64_int64 & a, pair_int64_int64 b ) { a.first |= b.first; a.second |= b.second; }
pair_int64_int64 & operator &= ( pair_int64_int64 & a, pair_int64_int64 b ) { a.first &= b.first; a.second &= b.second; }

struct pair_float32_float32 { float first; float second; };
template<class Archive> void serialize(Archive & archive, pair_float32_float32 & pair) { archive( pair.first, pair.second ); }
pair_float32_float32 & operator += ( pair_float32_float32 & a, pair_float32_float32 b ) { a.first += b.first; a.second += b.second; }
pair_float32_float32 & operator -= ( pair_float32_float32 & a, pair_float32_float32 b ) { a.first -= b.first; a.second -= b.second; }

struct pair_float64_float64 { double first; double second; };
template<class Archive> void serialize(Archive & archive, pair_float64_float64 & pair) { archive( pair.first, pair.second ); }
pair_float64_float64 & operator += ( pair_float64_float64 & a, pair_float64_float64 b ) { a.first += b.first; a.second += b.second; }
pair_float64_float64 & operator -= ( pair_float64_float64 & a, pair_float64_float64 b ) { a.first -= b.first; a.second -= b.second; }

struct bytearray2 { std::array<uint8_t, 2> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray2 & bytearray) { archive( bytearray.bytearray ); }
bytearray2 & operator += ( bytearray2 & a, bytearray2 b ) { a.bytearray += b.bytearray; }
bytearray2 & operator -= ( bytearray2 & a, bytearray2 b ) { a.bytearray -= b.bytearray; }
bytearray2 & operator |= ( bytearray2 & a, bytearray2 b ) { a.bytearray |= b.bytearray; }
bytearray2 & operator &= ( bytearray2 & a, bytearray2 b ) { a.bytearray &= b.bytearray; }

struct bytearray3 { std::array<uint8_t, 3> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray3 & bytearray) { archive( bytearray.bytearray ); }
bytearray3 & operator += ( bytearray3 & a, bytearray3 b ) { a.bytearray += b.bytearray; }
bytearray3 & operator -= ( bytearray3 & a, bytearray3 b ) { a.bytearray -= b.bytearray; }
bytearray3 & operator |= ( bytearray3 & a, bytearray3 b ) { a.bytearray |= b.bytearray; }
bytearray3 & operator &= ( bytearray3 & a, bytearray3 b ) { a.bytearray &= b.bytearray; }

struct bytearray4 { std::array<uint8_t, 4> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray4 & bytearray) { archive( bytearray.bytearray ); }
bytearray4 & operator += ( bytearray4 & a, bytearray4 b ) { a.bytearray += b.bytearray; }
bytearray4 & operator -= ( bytearray4 & a, bytearray4 b ) { a.bytearray -= b.bytearray; }
bytearray4 & operator |= ( bytearray4 & a, bytearray4 b ) { a.bytearray |= b.bytearray; }
bytearray4 & operator &= ( bytearray4 & a, bytearray4 b ) { a.bytearray &= b.bytearray; }

struct bytearray5 { std::array<uint8_t, 5> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray5 & bytearray) { archive( bytearray.bytearray ); }
bytearray5 & operator += ( bytearray5 & a, bytearray5 b ) { a.bytearray += b.bytearray; }
bytearray5 & operator -= ( bytearray5 & a, bytearray5 b ) { a.bytearray -= b.bytearray; }
bytearray5 & operator |= ( bytearray5 & a, bytearray5 b ) { a.bytearray |= b.bytearray; }
bytearray5 & operator &= ( bytearray5 & a, bytearray5 b ) { a.bytearray &= b.bytearray; }

struct bytearray6 { std::array<uint8_t, 6> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray6 & bytearray) { archive( bytearray.bytearray ); }
bytearray6 & operator += ( bytearray6 & a, bytearray6 b ) { a.bytearray += b.bytearray; }
bytearray6 & operator -= ( bytearray6 & a, bytearray6 b ) { a.bytearray -= b.bytearray; }
bytearray6 & operator |= ( bytearray6 & a, bytearray6 b ) { a.bytearray |= b.bytearray; }
bytearray6 & operator &= ( bytearray6 & a, bytearray6 b ) { a.bytearray &= b.bytearray; }

struct bytearray7 { std::array<uint8_t, 7> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray7 & bytearray) { archive( bytearray.bytearray ); }
bytearray7 & operator += ( bytearray7 & a, bytearray7 b ) { a.bytearray += b.bytearray; }
bytearray7 & operator -= ( bytearray7 & a, bytearray7 b ) { a.bytearray -= b.bytearray; }
bytearray7 & operator |= ( bytearray7 & a, bytearray7 b ) { a.bytearray |= b.bytearray; }
bytearray7 & operator &= ( bytearray7 & a, bytearray7 b ) { a.bytearray &= b.bytearray; }

struct bytearray8 { std::array<uint8_t, 8> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray8 & bytearray) { archive( bytearray.bytearray ); }
bytearray8 & operator += ( bytearray8 & a, bytearray8 b ) { a.bytearray += b.bytearray; }
bytearray8 & operator -= ( bytearray8 & a, bytearray8 b ) { a.bytearray -= b.bytearray; }
bytearray8 & operator |= ( bytearray8 & a, bytearray8 b ) { a.bytearray |= b.bytearray; }
bytearray8 & operator &= ( bytearray8 & a, bytearray8 b ) { a.bytearray &= b.bytearray; }

struct bytearray9 { std::array<uint8_t, 9> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray9 & bytearray) { archive( bytearray.bytearray ); }
bytearray9 & operator += ( bytearray9 & a, bytearray9 b ) { a.bytearray += b.bytearray; }
bytearray9 & operator -= ( bytearray9 & a, bytearray9 b ) { a.bytearray -= b.bytearray; }
bytearray9 & operator |= ( bytearray9 & a, bytearray9 b ) { a.bytearray |= b.bytearray; }
bytearray9 & operator &= ( bytearray9 & a, bytearray9 b ) { a.bytearray &= b.bytearray; }

struct bytearray10 { std::array<uint8_t, 10> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray10 & bytearray) { archive( bytearray.bytearray ); }
bytearray10 & operator += ( bytearray10 & a, bytearray10 b ) { a.bytearray += b.bytearray; }
bytearray10 & operator -= ( bytearray10 & a, bytearray10 b ) { a.bytearray -= b.bytearray; }
bytearray10 & operator |= ( bytearray10 & a, bytearray10 b ) { a.bytearray |= b.bytearray; }
bytearray10 & operator &= ( bytearray10 & a, bytearray10 b ) { a.bytearray &= b.bytearray; }

struct bytearray16 { std::array<uint8_t, 16> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray16 & bytearray) { archive( bytearray.bytearray ); }
bytearray16 & operator += ( bytearray16 & a, bytearray16 b ) { a.bytearray += b.bytearray; }
bytearray16 & operator -= ( bytearray16 & a, bytearray16 b ) { a.bytearray -= b.bytearray; }
bytearray16 & operator |= ( bytearray16 & a, bytearray16 b ) { a.bytearray |= b.bytearray; }
bytearray16 & operator &= ( bytearray16 & a, bytearray16 b ) { a.bytearray &= b.bytearray; }

struct bytearray20 { std::array<uint8_t, 20> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray20 & bytearray) { archive( bytearray.bytearray ); }
bytearray20 & operator += ( bytearray20 & a, bytearray20 b ) { a.bytearray += b.bytearray; }
bytearray20 & operator -= ( bytearray20 & a, bytearray20 b ) { a.bytearray -= b.bytearray; }
bytearray20 & operator |= ( bytearray20 & a, bytearray20 b ) { a.bytearray |= b.bytearray; }
bytearray20 & operator &= ( bytearray20 & a, bytearray20 b ) { a.bytearray &= b.bytearray; }

struct bytearray30 { std::array<uint8_t, 30> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray30 & bytearray) { archive( bytearray.bytearray ); }
bytearray30 & operator += ( bytearray30 & a, bytearray30 b ) { a.bytearray += b.bytearray; }
bytearray30 & operator -= ( bytearray30 & a, bytearray30 b ) { a.bytearray -= b.bytearray; }
bytearray30 & operator |= ( bytearray30 & a, bytearray30 b ) { a.bytearray |= b.bytearray; }
bytearray30 & operator &= ( bytearray30 & a, bytearray30 b ) { a.bytearray &= b.bytearray; }

struct bytearray32 { std::array<uint8_t, 32> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray32 & bytearray) { archive( bytearray.bytearray ); }
bytearray32 & operator += ( bytearray32 & a, bytearray32 b ) { a.bytearray += b.bytearray; }
bytearray32 & operator -= ( bytearray32 & a, bytearray32 b ) { a.bytearray -= b.bytearray; }
bytearray32 & operator |= ( bytearray32 & a, bytearray32 b ) { a.bytearray |= b.bytearray; }
bytearray32 & operator &= ( bytearray32 & a, bytearray32 b ) { a.bytearray &= b.bytearray; }

struct bytearray40 { std::array<uint8_t, 40> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray40 & bytearray) { archive( bytearray.bytearray ); }
bytearray40 & operator += ( bytearray40 & a, bytearray40 b ) { a.bytearray += b.bytearray; }
bytearray40 & operator -= ( bytearray40 & a, bytearray40 b ) { a.bytearray -= b.bytearray; }
bytearray40 & operator |= ( bytearray40 & a, bytearray40 b ) { a.bytearray |= b.bytearray; }
bytearray40 & operator &= ( bytearray40 & a, bytearray40 b ) { a.bytearray &= b.bytearray; }

struct bytearray50 { std::array<uint8_t, 50> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray50 & bytearray) { archive( bytearray.bytearray ); }
bytearray50 & operator += ( bytearray50 & a, bytearray50 b ) { a.bytearray += b.bytearray; }
bytearray50 & operator -= ( bytearray50 & a, bytearray50 b ) { a.bytearray -= b.bytearray; }
bytearray50 & operator |= ( bytearray50 & a, bytearray50 b ) { a.bytearray |= b.bytearray; }
bytearray50 & operator &= ( bytearray50 & a, bytearray50 b ) { a.bytearray &= b.bytearray; }

struct bytearray60 { std::array<uint8_t, 60> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray60 & bytearray) { archive( bytearray.bytearray ); }
bytearray60 & operator += ( bytearray60 & a, bytearray60 b ) { a.bytearray += b.bytearray; }
bytearray60 & operator -= ( bytearray60 & a, bytearray60 b ) { a.bytearray -= b.bytearray; }
bytearray60 & operator |= ( bytearray60 & a, bytearray60 b ) { a.bytearray |= b.bytearray; }
bytearray60 & operator &= ( bytearray60 & a, bytearray60 b ) { a.bytearray &= b.bytearray; }

struct bytearray64 { std::array<uint8_t, 64> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray64 & bytearray) { archive( bytearray.bytearray ); }
bytearray64 & operator += ( bytearray64 & a, bytearray64 b ) { a.bytearray += b.bytearray; }
bytearray64 & operator -= ( bytearray64 & a, bytearray64 b ) { a.bytearray -= b.bytearray; }
bytearray64 & operator |= ( bytearray64 & a, bytearray64 b ) { a.bytearray |= b.bytearray; }
bytearray64 & operator &= ( bytearray64 & a, bytearray64 b ) { a.bytearray &= b.bytearray; }

struct bytearray80 { std::array<uint8_t, 80> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray80 & bytearray) { archive( bytearray.bytearray ); }
bytearray80 & operator += ( bytearray80 & a, bytearray80 b ) { a.bytearray += b.bytearray; }
bytearray80 & operator -= ( bytearray80 & a, bytearray80 b ) { a.bytearray -= b.bytearray; }
bytearray80 & operator |= ( bytearray80 & a, bytearray80 b ) { a.bytearray |= b.bytearray; }
bytearray80 & operator &= ( bytearray80 & a, bytearray80 b ) { a.bytearray &= b.bytearray; }

struct bytearray100 { std::array<uint8_t, 100> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray100 & bytearray) { archive( bytearray.bytearray ); }
bytearray100 & operator += ( bytearray100 & a, bytearray100 b ) { a.bytearray += b.bytearray; }
bytearray100 & operator -= ( bytearray100 & a, bytearray100 b ) { a.bytearray -= b.bytearray; }
bytearray100 & operator |= ( bytearray100 & a, bytearray100 b ) { a.bytearray |= b.bytearray; }
bytearray100 & operator &= ( bytearray100 & a, bytearray100 b ) { a.bytearray &= b.bytearray; }

struct bytearray128 { std::array<uint8_t, 128> bytearray; };
template<class Archive> void serialize(Archive & archive, bytearray128 & bytearray) { archive( bytearray.bytearray ); }
bytearray128 & operator += ( bytearray128 & a, bytearray128 b ) { a.bytearray += b.bytearray; }
bytearray128 & operator -= ( bytearray128 & a, bytearray128 b ) { a.bytearray -= b.bytearray; }
bytearray128 & operator |= ( bytearray128 & a, bytearray128 b ) { a.bytearray |= b.bytearray; }
bytearray128 & operator &= ( bytearray128 & a, bytearray128 b ) { a.bytearray &= b.bytearray; }


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
    PYBIND11_NUMPY_DTYPE(bytearray3, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray4, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray5, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray6, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray7, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray8, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray9, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray10, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray16, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray20, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray30, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray32, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray40, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray50, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray60, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray64, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray80, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray100, bytearray );
    PYBIND11_NUMPY_DTYPE(bytearray128, bytearray );

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
    declare_dict_without_bitwise_operations<std::array<char, 4>, float>(m, "Dict_str4_float32");
    declare_dict_without_bitwise_operations<std::array<char, 4>, double>(m, "Dict_str4_float64");
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
    declare_dict_without_bitwise_operations<std::array<char, 4>, pair_float32_float32>(m, "Dict_str4_pair_float32_float32");
    declare_dict_without_bitwise_operations<std::array<char, 4>, pair_float64_float64>(m, "Dict_str4_pair_float64_float64");
    declare_dict<std::array<char, 4>, bytearray2>(m, "Dict_str4_bytearray2");
    declare_dict<std::array<char, 4>, bytearray3>(m, "Dict_str4_bytearray3");
    declare_dict<std::array<char, 4>, bytearray4>(m, "Dict_str4_bytearray4");
    declare_dict<std::array<char, 4>, bytearray5>(m, "Dict_str4_bytearray5");
    declare_dict<std::array<char, 4>, bytearray6>(m, "Dict_str4_bytearray6");
    declare_dict<std::array<char, 4>, bytearray7>(m, "Dict_str4_bytearray7");
    declare_dict<std::array<char, 4>, bytearray8>(m, "Dict_str4_bytearray8");
    declare_dict<std::array<char, 4>, bytearray9>(m, "Dict_str4_bytearray9");
    declare_dict<std::array<char, 4>, bytearray10>(m, "Dict_str4_bytearray10");
    declare_dict<std::array<char, 4>, bytearray16>(m, "Dict_str4_bytearray16");
    declare_dict<std::array<char, 4>, bytearray20>(m, "Dict_str4_bytearray20");
    declare_dict<std::array<char, 4>, bytearray30>(m, "Dict_str4_bytearray30");
    declare_dict<std::array<char, 4>, bytearray32>(m, "Dict_str4_bytearray32");
    declare_dict<std::array<char, 4>, bytearray40>(m, "Dict_str4_bytearray40");
    declare_dict<std::array<char, 4>, bytearray50>(m, "Dict_str4_bytearray50");
    declare_dict<std::array<char, 4>, bytearray60>(m, "Dict_str4_bytearray60");
    declare_dict<std::array<char, 4>, bytearray64>(m, "Dict_str4_bytearray64");
    declare_dict<std::array<char, 4>, bytearray80>(m, "Dict_str4_bytearray80");
    declare_dict<std::array<char, 4>, bytearray100>(m, "Dict_str4_bytearray100");
    declare_dict<std::array<char, 4>, bytearray128>(m, "Dict_str4_bytearray128");
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
    declare_dict_without_bitwise_operations<std::array<char, 8>, float>(m, "Dict_str8_float32");
    declare_dict_without_bitwise_operations<std::array<char, 8>, double>(m, "Dict_str8_float64");
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
    declare_dict_without_bitwise_operations<std::array<char, 8>, pair_float32_float32>(m, "Dict_str8_pair_float32_float32");
    declare_dict_without_bitwise_operations<std::array<char, 8>, pair_float64_float64>(m, "Dict_str8_pair_float64_float64");
    declare_dict<std::array<char, 8>, bytearray2>(m, "Dict_str8_bytearray2");
    declare_dict<std::array<char, 8>, bytearray3>(m, "Dict_str8_bytearray3");
    declare_dict<std::array<char, 8>, bytearray4>(m, "Dict_str8_bytearray4");
    declare_dict<std::array<char, 8>, bytearray5>(m, "Dict_str8_bytearray5");
    declare_dict<std::array<char, 8>, bytearray6>(m, "Dict_str8_bytearray6");
    declare_dict<std::array<char, 8>, bytearray7>(m, "Dict_str8_bytearray7");
    declare_dict<std::array<char, 8>, bytearray8>(m, "Dict_str8_bytearray8");
    declare_dict<std::array<char, 8>, bytearray9>(m, "Dict_str8_bytearray9");
    declare_dict<std::array<char, 8>, bytearray10>(m, "Dict_str8_bytearray10");
    declare_dict<std::array<char, 8>, bytearray16>(m, "Dict_str8_bytearray16");
    declare_dict<std::array<char, 8>, bytearray20>(m, "Dict_str8_bytearray20");
    declare_dict<std::array<char, 8>, bytearray30>(m, "Dict_str8_bytearray30");
    declare_dict<std::array<char, 8>, bytearray32>(m, "Dict_str8_bytearray32");
    declare_dict<std::array<char, 8>, bytearray40>(m, "Dict_str8_bytearray40");
    declare_dict<std::array<char, 8>, bytearray50>(m, "Dict_str8_bytearray50");
    declare_dict<std::array<char, 8>, bytearray60>(m, "Dict_str8_bytearray60");
    declare_dict<std::array<char, 8>, bytearray64>(m, "Dict_str8_bytearray64");
    declare_dict<std::array<char, 8>, bytearray80>(m, "Dict_str8_bytearray80");
    declare_dict<std::array<char, 8>, bytearray100>(m, "Dict_str8_bytearray100");
    declare_dict<std::array<char, 8>, bytearray128>(m, "Dict_str8_bytearray128");
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
    declare_dict_without_bitwise_operations<uint32_t, float>(m, "Dict_uint32_float32");
    declare_dict_without_bitwise_operations<uint32_t, double>(m, "Dict_uint32_float64");
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
    declare_dict_without_bitwise_operations<uint32_t, pair_float32_float32>(m, "Dict_uint32_pair_float32_float32");
    declare_dict_without_bitwise_operations<uint32_t, pair_float64_float64>(m, "Dict_uint32_pair_float64_float64");
    declare_dict<uint32_t, bytearray2>(m, "Dict_uint32_bytearray2");
    declare_dict<uint32_t, bytearray3>(m, "Dict_uint32_bytearray3");
    declare_dict<uint32_t, bytearray4>(m, "Dict_uint32_bytearray4");
    declare_dict<uint32_t, bytearray5>(m, "Dict_uint32_bytearray5");
    declare_dict<uint32_t, bytearray6>(m, "Dict_uint32_bytearray6");
    declare_dict<uint32_t, bytearray7>(m, "Dict_uint32_bytearray7");
    declare_dict<uint32_t, bytearray8>(m, "Dict_uint32_bytearray8");
    declare_dict<uint32_t, bytearray9>(m, "Dict_uint32_bytearray9");
    declare_dict<uint32_t, bytearray10>(m, "Dict_uint32_bytearray10");
    declare_dict<uint32_t, bytearray16>(m, "Dict_uint32_bytearray16");
    declare_dict<uint32_t, bytearray20>(m, "Dict_uint32_bytearray20");
    declare_dict<uint32_t, bytearray30>(m, "Dict_uint32_bytearray30");
    declare_dict<uint32_t, bytearray32>(m, "Dict_uint32_bytearray32");
    declare_dict<uint32_t, bytearray40>(m, "Dict_uint32_bytearray40");
    declare_dict<uint32_t, bytearray50>(m, "Dict_uint32_bytearray50");
    declare_dict<uint32_t, bytearray60>(m, "Dict_uint32_bytearray60");
    declare_dict<uint32_t, bytearray64>(m, "Dict_uint32_bytearray64");
    declare_dict<uint32_t, bytearray80>(m, "Dict_uint32_bytearray80");
    declare_dict<uint32_t, bytearray100>(m, "Dict_uint32_bytearray100");
    declare_dict<uint32_t, bytearray128>(m, "Dict_uint32_bytearray128");
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
    declare_dict_without_bitwise_operations<uint64_t, float>(m, "Dict_uint64_float32");
    declare_dict_without_bitwise_operations<uint64_t, double>(m, "Dict_uint64_float64");
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
    declare_dict_without_bitwise_operations<uint64_t, pair_float32_float32>(m, "Dict_uint64_pair_float32_float32");
    declare_dict_without_bitwise_operations<uint64_t, pair_float64_float64>(m, "Dict_uint64_pair_float64_float64");
    declare_dict<uint64_t, bytearray2>(m, "Dict_uint64_bytearray2");
    declare_dict<uint64_t, bytearray3>(m, "Dict_uint64_bytearray3");
    declare_dict<uint64_t, bytearray4>(m, "Dict_uint64_bytearray4");
    declare_dict<uint64_t, bytearray5>(m, "Dict_uint64_bytearray5");
    declare_dict<uint64_t, bytearray6>(m, "Dict_uint64_bytearray6");
    declare_dict<uint64_t, bytearray7>(m, "Dict_uint64_bytearray7");
    declare_dict<uint64_t, bytearray8>(m, "Dict_uint64_bytearray8");
    declare_dict<uint64_t, bytearray9>(m, "Dict_uint64_bytearray9");
    declare_dict<uint64_t, bytearray10>(m, "Dict_uint64_bytearray10");
    declare_dict<uint64_t, bytearray16>(m, "Dict_uint64_bytearray16");
    declare_dict<uint64_t, bytearray20>(m, "Dict_uint64_bytearray20");
    declare_dict<uint64_t, bytearray30>(m, "Dict_uint64_bytearray30");
    declare_dict<uint64_t, bytearray32>(m, "Dict_uint64_bytearray32");
    declare_dict<uint64_t, bytearray40>(m, "Dict_uint64_bytearray40");
    declare_dict<uint64_t, bytearray50>(m, "Dict_uint64_bytearray50");
    declare_dict<uint64_t, bytearray60>(m, "Dict_uint64_bytearray60");
    declare_dict<uint64_t, bytearray64>(m, "Dict_uint64_bytearray64");
    declare_dict<uint64_t, bytearray80>(m, "Dict_uint64_bytearray80");
    declare_dict<uint64_t, bytearray100>(m, "Dict_uint64_bytearray100");
    declare_dict<uint64_t, bytearray128>(m, "Dict_uint64_bytearray128");
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
    declare_dict_without_bitwise_operations<int32_t, float>(m, "Dict_int32_float32");
    declare_dict_without_bitwise_operations<int32_t, double>(m, "Dict_int32_float64");
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
    declare_dict_without_bitwise_operations<int32_t, pair_float32_float32>(m, "Dict_int32_pair_float32_float32");
    declare_dict_without_bitwise_operations<int32_t, pair_float64_float64>(m, "Dict_int32_pair_float64_float64");
    declare_dict<int32_t, bytearray2>(m, "Dict_int32_bytearray2");
    declare_dict<int32_t, bytearray3>(m, "Dict_int32_bytearray3");
    declare_dict<int32_t, bytearray4>(m, "Dict_int32_bytearray4");
    declare_dict<int32_t, bytearray5>(m, "Dict_int32_bytearray5");
    declare_dict<int32_t, bytearray6>(m, "Dict_int32_bytearray6");
    declare_dict<int32_t, bytearray7>(m, "Dict_int32_bytearray7");
    declare_dict<int32_t, bytearray8>(m, "Dict_int32_bytearray8");
    declare_dict<int32_t, bytearray9>(m, "Dict_int32_bytearray9");
    declare_dict<int32_t, bytearray10>(m, "Dict_int32_bytearray10");
    declare_dict<int32_t, bytearray16>(m, "Dict_int32_bytearray16");
    declare_dict<int32_t, bytearray20>(m, "Dict_int32_bytearray20");
    declare_dict<int32_t, bytearray30>(m, "Dict_int32_bytearray30");
    declare_dict<int32_t, bytearray32>(m, "Dict_int32_bytearray32");
    declare_dict<int32_t, bytearray40>(m, "Dict_int32_bytearray40");
    declare_dict<int32_t, bytearray50>(m, "Dict_int32_bytearray50");
    declare_dict<int32_t, bytearray60>(m, "Dict_int32_bytearray60");
    declare_dict<int32_t, bytearray64>(m, "Dict_int32_bytearray64");
    declare_dict<int32_t, bytearray80>(m, "Dict_int32_bytearray80");
    declare_dict<int32_t, bytearray100>(m, "Dict_int32_bytearray100");
    declare_dict<int32_t, bytearray128>(m, "Dict_int32_bytearray128");
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
    declare_dict_without_bitwise_operations<int64_t, float>(m, "Dict_int64_float32");
    declare_dict_without_bitwise_operations<int64_t, double>(m, "Dict_int64_float64");
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
    declare_dict_without_bitwise_operations<int64_t, pair_float32_float32>(m, "Dict_int64_pair_float32_float32");
    declare_dict_without_bitwise_operations<int64_t, pair_float64_float64>(m, "Dict_int64_pair_float64_float64");
    declare_dict<int64_t, bytearray2>(m, "Dict_int64_bytearray2");
    declare_dict<int64_t, bytearray3>(m, "Dict_int64_bytearray3");
    declare_dict<int64_t, bytearray4>(m, "Dict_int64_bytearray4");
    declare_dict<int64_t, bytearray5>(m, "Dict_int64_bytearray5");
    declare_dict<int64_t, bytearray6>(m, "Dict_int64_bytearray6");
    declare_dict<int64_t, bytearray7>(m, "Dict_int64_bytearray7");
    declare_dict<int64_t, bytearray8>(m, "Dict_int64_bytearray8");
    declare_dict<int64_t, bytearray9>(m, "Dict_int64_bytearray9");
    declare_dict<int64_t, bytearray10>(m, "Dict_int64_bytearray10");
    declare_dict<int64_t, bytearray16>(m, "Dict_int64_bytearray16");
    declare_dict<int64_t, bytearray20>(m, "Dict_int64_bytearray20");
    declare_dict<int64_t, bytearray30>(m, "Dict_int64_bytearray30");
    declare_dict<int64_t, bytearray32>(m, "Dict_int64_bytearray32");
    declare_dict<int64_t, bytearray40>(m, "Dict_int64_bytearray40");
    declare_dict<int64_t, bytearray50>(m, "Dict_int64_bytearray50");
    declare_dict<int64_t, bytearray60>(m, "Dict_int64_bytearray60");
    declare_dict<int64_t, bytearray64>(m, "Dict_int64_bytearray64");
    declare_dict<int64_t, bytearray80>(m, "Dict_int64_bytearray80");
    declare_dict<int64_t, bytearray100>(m, "Dict_int64_bytearray100");
    declare_dict<int64_t, bytearray128>(m, "Dict_int64_bytearray128");
}
