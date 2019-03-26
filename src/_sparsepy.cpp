// Fast and Memory Efficient Sparse Hash Tables for Python 
#include <spp.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

#include <msgpack.hpp>

template <typename Key, typename Value>
struct _Dict {
    _Dict () {}

    Value __getitem__ ( Key key ) {
        return __dict.at(key);
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

template<typename Key, typename Value>
void declare_Dict(py::module &m, std::string key_name, std::string value_name) {
    using Class = _Dict<Key, Value>;
    std::string name = std::string("_Dict_") + key_name + std::string("_") + value_name;

    py::class_<Class>(m, name.c_str())
        .def(py::init<>())
        .def("__getitem__", &Class::__getitem__)
        .def("__setitem__", &Class::__setitem__)
        .def("__delitem__", &Class::__delitem__)
        .def("__contains__", &Class::__contains__)
        .def("__len__", &Class::__len__);
}

PYBIND11_MODULE(_sparsepy, m) {
    m.doc() = "Fast and Memory Efficient Sparse Hash Tables for Python"; 
    
    std::vector<std::string> type_strings = {
        "int64_t", "int32_t", "int16_t", "int8_t",
        "uint64_t", "uint32_t", "uint16_t", "uint8_t",
    };

    for (std::string k : type_strings) {
        for (std::string v : type_strings) {
            declare_Dict<k, v>(m, k, v);
        }
    }
}
