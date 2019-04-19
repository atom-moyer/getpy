#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
namespace py = pybind11;

#include <parallel_hashmap/phmap_utils.h>
#include <parallel_hashmap/phmap.h>

#include <cereal/archives/binary.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>

#include <iostream>


template<typename T, size_t N>
struct std::hash<std::array<T, N>> {
    size_t operator()(const std::array<T, N> & array) const {
        size_t seed = 0;
        for ( T value : array ) {
            phmap::HashState().combine( seed, value );
        }
        return seed;
    }
};


template <typename Key, typename Value>
struct Dict {
    Dict () {}


    py::array_t<Value> __getitem__ ( py::array_t<Key> & key_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        auto result_array = py::array_t<Value> ( key_array_buffer.shape[0] );
        py::buffer_info result_array_buffer = result_array.request();
        auto * result_array_ptr = (Value *) result_array_buffer.ptr;

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++)
            result_array_ptr[idx] = __dict.at( key_array_ptr[idx] );

        return result_array;
    }


    void __setitem__ ( py::array_t<Key> & key_array, py::array_t<Value> & value_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        py::buffer_info value_array_buffer = value_array.request();
        auto * value_array_ptr = (Value *) value_array_buffer.ptr;

        if (key_array_buffer.shape[0] != value_array_buffer.shape[0])
            throw std::runtime_error("Size of first dimension must match.");

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            __dict.emplace( key_array_ptr[idx], value_array_ptr[idx] );
        }
    }


    void __delitem__ ( py::array_t<Key> & key_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++)
            __dict.erase( key_array_ptr[idx] );
    }


    py::array_t<bool> __contains__ ( py::array_t<Key> & key_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        auto result_array = py::array_t<bool>( key_array_buffer.shape[0] );
        py::buffer_info result_array_buffer = result_array.request();
        auto * result_array_ptr = (bool *) result_array_buffer.ptr;

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            if ( __dict.count( key_array_ptr[idx] ) ) {
                result_array_ptr[idx] = true;
            } else {
                result_array_ptr[idx] = false;
            }
        }

        return result_array;
    }


    int __len__ () {
        return __dict.size();
    }


    void dump ( const std::string & filename ) {
        std::ofstream stream ( filename , std::ios::binary );
        cereal::BinaryOutputArchive oarchive ( stream );

        for ( auto & key_value : __dict ) {
            oarchive(key_value);
        }
    }

    void load ( const std::string & filename ) {
        std::ifstream stream ( filename , std::ios::binary);
        cereal::BinaryInputArchive iarchive ( stream );

        std::pair<Key, Value> in_key_value;
        while ( stream.peek() != EOF ) {
            iarchive(in_key_value);
            __dict.emplace(in_key_value.first, in_key_value.second);
        }
    }


    phmap::parallel_flat_hash_map<Key, Value> __dict;
};


template<typename Key, typename Value>
void declare_dict(const py::module& m, const std::string& class_name) {
    using Class = Dict<Key, Value>;

    py::class_<Class>(m, class_name.c_str())
        .def(py::init<>())

        .def("__getitem__", &Class::__getitem__)
        .def("__setitem__", &Class::__setitem__)
        .def("__delitem__", &Class::__delitem__)
        .def("__contains__", &Class::__contains__)

        .def("dump", &Class::dump)
        .def("load", &Class::load)

        .def("items", [](const Class &c) { return py::make_iterator(c.__dict.begin(), c.__dict.end()); }, py::keep_alive<0, 1>() )
        .def("__len__", &Class::__len__);
}
