#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
namespace py = pybind11;

#include <spp.h>

template <typename Key, typename Value>
struct _Dict {
    _Dict () {}

    Value __getitem__ ( Key key ) {
        return __dict.at(key);
    }

    bool __setitem__ ( Key key, Value value ) {
        auto emplace_pair = __dict.emplace(key, value);
        return emplace_pair.second;
    }

    bool __delitem__ ( Key key ) {
        int check = __dict.erase(key);

        if (check) { 
            return true;
        } else { 
            return false; 
        }
    }

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
        .def("__getitem_vec__", py::vectorize(&Class::__getitem__))
        
        .def("__setitem__", &Class::__setitem__)
        .def("__setitem_vec__", py::vectorize(&Class::__setitem__))
        
        .def("__delitem__", &Class::__delitem__)
        .def("__delitem_vec__", py::vectorize(&Class::__delitem__))
        
        .def("__contains__", &Class::__contains__)
        .def("__contains_vec__", py::vectorize(&Class::__contains__))
        
        .def("__iter__", [](const Class &c) { return py::make_iterator(c.__dict.begin(), c.__dict.end()); }, py::keep_alive<0, 1>() )
        .def("__len__", &Class::__len__);
}

/*
py::array_t<bool> __contains_vec__ ( py::array_t<Key> key_array ) {
    py::buffer_info key_buffer = key_array.request();
    auto bool_array = py::array_t<bool>(key_buffer.size);
    py::buffer_info bool_buffer = bool_array.request();
    Key* key_ptr = (Key*) key_buffer.ptr;
    bool* bool_ptr = (bool*) bool_buffer.ptr;

    for (size_t idx = 0; idx < key_buffer.size; idx++)
        bool_ptr[idx] = __contains__(key_ptr[idx]);

    return bool_array;
}
*/

