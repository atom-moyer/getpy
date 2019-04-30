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


template <typename Key, typename Value>
struct Dict {
    Dict () {}


    Dict ( Value default_value ) : default_value ( default_value ) {}


    py::array_t<Value> __getitem__ ( py::array_t<Key> & key_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        auto result_array = py::array_t<Value> ( key_array_buffer.shape[0] );
        py::buffer_info result_array_buffer = result_array.request();
        auto * result_array_ptr = (Value *) result_array_buffer.ptr;

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            auto search = __dict.find( key_array_ptr[idx] );

            if ( search != __dict.end() ) {
                result_array_ptr[idx] = search->second;
            } else if ( default_value )  {
                result_array_ptr[idx] = *default_value;
            } else {
                throw std::runtime_error("Key Error: Key not found and default value is not defined.");
            }
        }

        return result_array;
    }


    void __setitem__ ( py::array_t<Key> & key_array, py::array_t<Value> & value_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        py::buffer_info value_array_buffer = value_array.request();
        auto * value_array_ptr = (Value *) value_array_buffer.ptr;

        if (key_array_buffer.shape[0] != value_array_buffer.shape[0])
            throw std::runtime_error("The size of the first dimension for the key and value must match.");

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            __dict.insert_or_assign( key_array_ptr[idx], value_array_ptr[idx] );
        }
    }


    void iadd ( py::array_t<Key> & key_array, py::array_t<Value> & value_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        py::buffer_info value_array_buffer = value_array.request();
        auto * value_array_ptr = (Value *) value_array_buffer.ptr;

        if (key_array_buffer.shape[0] != value_array_buffer.shape[0])
            throw std::runtime_error("The size of the first dimension for the key and value must match.");

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            auto search = __dict.find( key_array_ptr[idx] );

            if ( search != __dict.end() ) {
                search->second += value_array_ptr[idx];
            } else if ( default_value )  {
                Value value = *default_value;
                value += value_array_ptr[idx];
                __dict.insert_or_assign( key_array_ptr[idx], value);
            } else {
                throw std::runtime_error("Key Error: Key not found and default value is not defined.");
            }
        }
    }


    void isub ( py::array_t<Key> & key_array, py::array_t<Value> & value_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        py::buffer_info value_array_buffer = value_array.request();
        auto * value_array_ptr = (Value *) value_array_buffer.ptr;

        if (key_array_buffer.shape[0] != value_array_buffer.shape[0])
            throw std::runtime_error("The size of the first dimension for the key and value must match.");

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            auto search = __dict.find( key_array_ptr[idx] );

            if ( search != __dict.end() ) {
                search->second -= value_array_ptr[idx];
            } else if ( default_value )  {
                Value value = *default_value;
                value -= value_array_ptr[idx];
                __dict.insert_or_assign( key_array_ptr[idx], value);
            } else {
                throw std::runtime_error("Key Error: Key not found and default value is not defined.");
            }
        }
    }


    void ior ( py::array_t<Key> & key_array, py::array_t<Value> & value_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        py::buffer_info value_array_buffer = value_array.request();
        auto * value_array_ptr = (Value *) value_array_buffer.ptr;

        if (key_array_buffer.shape[0] != value_array_buffer.shape[0])
            throw std::runtime_error("The size of the first dimension for the key and value must match.");

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            auto search = __dict.find( key_array_ptr[idx] );

            if ( search != __dict.end() ) {
                search->second |= value_array_ptr[idx];
            } else if ( default_value )  {
                Value value = *default_value;
                value |= value_array_ptr[idx];
                __dict.insert_or_assign( key_array_ptr[idx], value);
            } else {
                throw std::runtime_error("Key Error: Key not found and default value is not defined.");
            }
        }
    }


    void iand ( py::array_t<Key> & key_array, py::array_t<Value> & value_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        py::buffer_info value_array_buffer = value_array.request();
        auto * value_array_ptr = (Value *) value_array_buffer.ptr;

        if (key_array_buffer.shape[0] != value_array_buffer.shape[0])
            throw std::runtime_error("The size of the first dimension for the key and value must match.");

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            auto search = __dict.find( key_array_ptr[idx] );

            if ( search != __dict.end() ) {
                search->second &= value_array_ptr[idx];
            } else if ( default_value )  {
                Value value = *default_value;
                value &= value_array_ptr[idx];
                __dict.insert_or_assign( key_array_ptr[idx], value);
            } else {
                throw std::runtime_error("Key Error: Key not found and default value is not defined.");
            }
        }
    }


    void __delitem__ ( py::array_t<Key> & key_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++)
            __dict.erase( key_array_ptr[idx] );
    }


    py::array_t<bool> contains ( py::array_t<Key> & key_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        auto result_array = py::array_t<bool>( key_array_buffer.shape[0] );
        py::buffer_info result_array_buffer = result_array.request();
        auto * result_array_ptr = (bool *) result_array_buffer.ptr;

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            auto search = __dict.find( key_array_ptr[idx] );

            if ( search != __dict.end() ) {
                result_array_ptr[idx] = true;
            } else {
                result_array_ptr[idx] = false;
            }
        }

        return result_array;
    }


    long __len__ () {
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


    std::optional<Value> default_value;
    phmap::parallel_flat_hash_map<Key, Value> __dict;
};


template <typename Key, typename Value>
struct Dict_Without_Bitwise_Operations : Dict<Key, Value> {
    void ior ( py::array_t<Key> & key_array, py::array_t<Value> & value_array ) {
        throw std::runtime_error("This dict does not support bitwise operations.");
    }

    void iand ( py::array_t<Key> & key_array, py::array_t<Value> & value_array ) {
        throw std::runtime_error("This dict does not support bitwise operations.");
    }
};


template<typename Key, typename Value>
void declare_dict(const py::module& m, const std::string& class_name) {
  using Class = Dict<Key, Value>;

  py::class_<Class>(m, class_name.c_str())
      .def(py::init<>())
      .def(py::init<const Value &>())

      .def("__getitem__", &Class::__getitem__)
      .def("__setitem__", &Class::__setitem__)
      .def("__delitem__", &Class::__delitem__)

      .def("contains", &Class::contains)
      .def("iadd", &Class::iadd)
      .def("isub", &Class::isub)
      .def("ior", &Class::ior)
      .def("iand", &Class::iand)

      .def("dump", &Class::dump)
      .def("load", &Class::load)

      .def("items", [](const Class &c) { return py::make_iterator(c.__dict.begin(), c.__dict.end()); }, py::keep_alive<0, 1>() )
      .def("__len__", &Class::__len__);
}


template<typename Key, typename Value>
void declare_dict_without_bitwise_operations(const py::module& m, const std::string& class_name) {
    using Class = Dict_Without_Bitwise_Operations<Key, Value>;

    py::class_<Class>(m, class_name.c_str())
        .def(py::init<>())
        .def(py::init<const Value &>())

        .def("__getitem__", &Class::__getitem__)
        .def("__setitem__", &Class::__setitem__)
        .def("__delitem__", &Class::__delitem__)

        .def("contains", &Class::contains)
        .def("iadd", &Class::iadd)
        .def("isub", &Class::isub)
        .def("ior", &Class::ior)
        .def("iand", &Class::iand)

        .def("dump", &Class::dump)
        .def("load", &Class::load)

        .def("items", [](const Class &c) { return py::make_iterator(c.__dict.begin(), c.__dict.end()); }, py::keep_alive<0, 1>() )
        .def("__len__", &Class::__len__);
}


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


template<typename T, size_t N>
std::array<T, N> & operator += ( std::array<T, N> & a, std::array<T, N> b ) {
    for (int i = 0 ; i < N ; ++i) {
        a[i] = a[i] + b[i];
    }
}


template<typename T, size_t N>
std::array<T, N> & operator -= ( std::array<T, N> & a, std::array<T, N> b ) {
    for (int i = 0 ; i < N ; ++i) {
        a[i] = a[i] - b[i];
    }
}


template<typename T, size_t N>
std::array<T, N> & operator |= ( std::array<T, N> & a, std::array<T, N> b ) {
    for (int i = 0 ; i < N ; ++i) {
        a[i] = a[i] | b[i];
    }
}


template<typename T, size_t N>
std::array<T, N> & operator &= ( std::array<T, N> & a, std::array<T, N> b ) {
    for (int i = 0 ; i < N ; ++i) {
        a[i] = a[i] & b[i];
    }
}
