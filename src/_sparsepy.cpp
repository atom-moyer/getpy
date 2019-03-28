// Fast and Memory Efficient Sparse Hash Tables for Python 
#include <spp.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

#include <brigand/brigand.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/sequences/at.hpp>
#include <brigand/algorithms/for_each.hpp>


using types = brigand::list<
    float, int
>;

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
void declare_Dict(const py::module& m) {
    using Class = _Dict<Key, Value>;
    
    std::string name = std::string("_Dict_") + typeid(Key).name() + std::string("_") + typeid(Value).name();

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

    brigand::for_each<types>([&m](auto key) {
        brigand::for_each<types>([&m, key](auto value) {
            declare_Dict<key, value>(m);
        });
    });
}
