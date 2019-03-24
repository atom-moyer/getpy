// A group of fast and memory efficient data structures for recalling motif pair
// interactions.
#include <spp.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <msgpack.hpp>

#include <iostream>
using namespace std;

template <class Key, class Value>
struct Dict {
    Dict () {}
    
    

    spp::sparse_hash_map<Key, Value> _dict;
}

typedef spp::sparse_hash_map<uint64_t, uint64_t> dict_uint64_uint64;

