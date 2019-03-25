// Fast and Memory Efficient Sparse Hash Tables for Python 
#include <spp.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <msgpack.hpp>

template <class Key, class Value>
struct _Dict {
    _Dict () {}

    Value __getitem__ ( Key key ) {
        return __dict[key];
    }
    
    void __setitem__ ( Key key, Value value ) {
        __dict.emplace(key, value);
    }

    void __delitem__ ( Key key ) {
        __dict.erase(key);
    }
    
    void __iter__ () {}

    int __len__ () {
        return __dict.size();
    }

    bool __contains__ ( Key key ) {
        if (__dict.count(key)) {
            return true;
        } else {
            return false;
        }
    }

    spp::sparse_hash_map<Key, Value> __dict;
};

typedef _Dict <uint64_t, uint64_t> _Dict_uint64_uint64;

PYBIND11_MODULE(_sparsepy, m) {
    m.doc() = "Fast and Memory Efficient Sparse Hash Tables for Python";

    py::class_<_Dict_uint64_uint64> (m, "_Dict_uint64_uint64")
        .def(py::init<>())
        .def("__getitem__", &_Dict_uint64_uint64::__getitem__)
        .def("__setitem__", &_Dict_uint64_uint64::__setitem__)
        .def("__delitem__", &_Dict_uint64_uint64::__delitem__)
        .def("__len__", &_Dict_uint64_uint64::__len__);
}
