#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
namespace py = pybind11;

#include <sparsepp/spp.h>

#include <msgpack.hpp>


template<typename T, size_t N>
struct std::hash<std::array<T, N> > {
    size_t operator()(const std::array<T, N> & array) const {
        size_t seed = 0;
        for ( T value : array ) {
            spp::hash_combine( seed, value );
        }
        return seed;
    }
};


template <typename Key, typename Value>
struct _Dict {
    _Dict () {}

    Value __getitem__ ( const Key & key ) {
        return __dict.at(key);
    }

    bool __setitem__ ( const Key & key, const Value & value ) {
        auto emplace_pair = __dict.emplace(key, value);
        return emplace_pair.second;
    }

    bool __delitem__ ( const Key & key ) {
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

    bool __contains__ ( const Key & key ) {
        if (__dict.count(key)) {
            return true;
        } else {
            return false;
        }
    }
    
    void dump ( const std::string & filename ) {
        std::ofstream file ( filename );
        std::stringstream buffer;
        
        for ( auto & key_value : __dict ) {
            msgpack::pack(buffer, key_value);
            file << buffer << std::endl;
        }
    }

    void load ( const std::string & filename ) {
        std::ifstream file ( filename );
        std::string line;

        while ( getline( file, line ) ) {
            msgpack::object_handle oh = msgpack::unpack(ss.str().data(), ss.str().size());
            msgpack::object obj = oh.get();
            obj.as<std::pair<Key, Value>>();
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

