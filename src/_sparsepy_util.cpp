#include <pybind11/pybind11.h>
namespace py = pybind11;

#include <spp.h>

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
void declare_dict(const py::module& m, const std::string& class_name) {
    using Class = _Dict<Key, Value>;

    py::class_<Class>(m, class_name.c_str())
        .def(py::init<>())
        .def("__getitem__", &Class::__getitem__)
        .def("__setitem__", &Class::__setitem__)
        .def("__delitem__", &Class::__delitem__)
        .def("__contains__", &Class::__contains__)
        .def("__len__", &Class::__len__);
}
