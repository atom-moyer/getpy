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


    Dict ( py::array_t<Value> complex_default_value ) {
        py::buffer_info complex_default_value_buffer = complex_default_value.request();

        if ( complex_default_value_buffer.ndim != 1 | complex_default_value_buffer.shape[0] != 1 )
            throw std::runtime_error("The default value for complex dtypes must be set with one value.");

        auto * complex_default_value_ptr = (Value *) complex_default_value_buffer.ptr;

        default_value = complex_default_value_ptr[0];
    }


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


    py::array_t<Key> keys () {
        auto result_array = py::array_t<Key>( __dict.size() );
        py::buffer_info result_array_buffer = result_array.request();
        auto * result_array_ptr = (Key *) result_array_buffer.ptr;

        size_t idx = 0;
        for ( auto & key_value : __dict ) {
            result_array_ptr[idx] = key_value.first;
            idx++;
        }

        return result_array;
    }


    py::array_t<Value> values () {
        auto result_array = py::array_t<Value>( __dict.size() );
        py::buffer_info result_array_buffer = result_array.request();
        auto * result_array_ptr = (Value *) result_array_buffer.ptr;

        size_t idx = 0;
        for ( auto & key_value : __dict ) {
            result_array_ptr[idx] = key_value.second;
            idx++;
        }

        return result_array;
    }


    std::pair<py::array_t<Key>, py::array_t<Value>> items () {
        auto key_result_array = py::array_t<Key>( __dict.size() );
        py::buffer_info key_result_array_buffer = key_result_array.request();
        auto * key_result_array_ptr = (Key *) key_result_array_buffer.ptr;

        auto value_result_array = py::array_t<Value>( __dict.size() );
        py::buffer_info value_result_array_buffer = value_result_array.request();
        auto * value_result_array_ptr = (Value *) value_result_array_buffer.ptr;

        size_t idx = 0;
        for ( auto & key_value : __dict ) {
            key_result_array_ptr[idx] = key_value.first;
            value_result_array_ptr[idx] = key_value.second;
            idx++;
        }

        return std::make_pair(key_result_array, value_result_array);
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
struct Dict_Default : Dict<Key, Value> {
    void iadd ( py::array_t<Key> & key_array, py::array_t<Value> & value_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        py::buffer_info value_array_buffer = value_array.request();
        auto * value_array_ptr = (Value *) value_array_buffer.ptr;

        if (key_array_buffer.shape[0] != value_array_buffer.shape[0])
            throw std::runtime_error("The size of the first dimension for the key and value must match.");

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            auto search = this->__dict.find( key_array_ptr[idx] );

            if ( search != this->__dict.end() ) {
                search->second += value_array_ptr[idx];
            } else if ( this->default_value )  {
                Value value = *(this->default_value);
                value += value_array_ptr[idx];
                this->__dict.insert_or_assign( key_array_ptr[idx], value);
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
            auto search = this->__dict.find( key_array_ptr[idx] );

            if ( search != this->__dict.end() ) {
                search->second -= value_array_ptr[idx];
            } else if ( this->default_value )  {
                Value value = *(this->default_value);
                value -= value_array_ptr[idx];
                this->__dict.insert_or_assign( key_array_ptr[idx], value);
            } else {
                throw std::runtime_error("Key Error: Key not found and default value is not defined.");
            }
        }
    }
};


template <typename Key, typename Value>
struct Dict_Bitwise : Dict<Key, Value> {
    void ior ( py::array_t<Key> & key_array, py::array_t<Value> & value_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        py::buffer_info value_array_buffer = value_array.request();
        auto * value_array_ptr = (Value *) value_array_buffer.ptr;

        if (key_array_buffer.shape[0] != value_array_buffer.shape[0])
            throw std::runtime_error("The size of the first dimension for the key and value must match.");

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            auto search = this->__dict.find( key_array_ptr[idx] );

            if ( search != this->__dict.end() ) {
                search->second |= value_array_ptr[idx];
            } else if ( this->default_value )  {
                Value value = *(this->default_value);
                value |= value_array_ptr[idx];
                this->__dict.insert_or_assign( key_array_ptr[idx], value);
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
            auto search = this->__dict.find( key_array_ptr[idx] );

            if ( search != this->__dict.end() ) {
                search->second &= value_array_ptr[idx];
            } else if ( this->default_value )  {
                Value value = *(this->default_value);
                value &= value_array_ptr[idx];
                this->__dict.insert_or_assign( key_array_ptr[idx], value);
            } else {
                throw std::runtime_error("Key Error: Key not found and default value is not defined.");
            }
        }
    }
};


template<typename Key, typename Value>
void declare_dict_default(const py::module& m, const std::string& class_name) {
  using Class = Dict_Default<Key, Value>;

  py::class_<Class>(m, class_name.c_str())
      .def(py::init<>())
      .def(py::init<Value &>())
      .def(py::init<py::array_t<Value> &>())

      .def("__getitem__", &Class::__getitem__)
      .def("__setitem__", &Class::__setitem__)
      .def("__delitem__", &Class::__delitem__)

      .def("contains", &Class::contains)

      .def("iadd", &Class::iadd)
      .def("isub", &Class::isub)

      .def("dump", &Class::dump)
      .def("load", &Class::load)

      .def("keys", &Class::keys)
      .def("values", &Class::values)
      .def("items", &Class::items)

      .def("__len__", &Class::__len__);
}


template<typename Key, typename Value>
void declare_dict_bitwise(const py::module& m, const std::string& class_name) {
    using Class = Dict_Bitwise<Key, Value>;

    py::class_<Class>(m, class_name.c_str())
        .def(py::init<>())
        .def(py::init<const Value &>())

        .def("__getitem__", &Class::__getitem__)
        .def("__setitem__", &Class::__setitem__)
        .def("__delitem__", &Class::__delitem__)

        .def("contains", &Class::contains)

        .def("ior", &Class::ior)
        .def("iand", &Class::iand)

        .def("dump", &Class::dump)
        .def("load", &Class::load)

        .def("keys", &Class::keys)
        .def("values", &Class::values)
        .def("items", &Class::items)

        .def("__len__", &Class::__len__);
}


template <typename Key>
struct Set {
    Set () {}


    void add ( py::array_t<Key> & key_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            __set.emplace( key_array_ptr[idx] );
        }
    }


    void discard ( py::array_t<Key> & key_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++)
            __set.erase( key_array_ptr[idx] );
    }


    py::array_t<bool> contains ( py::array_t<Key> & key_array ) {
        py::buffer_info key_array_buffer = key_array.request();
        auto * key_array_ptr = (Key *) key_array_buffer.ptr;

        auto result_array = py::array_t<bool>( key_array_buffer.shape[0] );
        py::buffer_info result_array_buffer = result_array.request();
        auto * result_array_ptr = (bool *) result_array_buffer.ptr;

        for (size_t idx = 0; idx < key_array_buffer.shape[0]; idx++) {
            auto search = __set.find( key_array_ptr[idx] );

            if ( search != __set.end() ) {
                result_array_ptr[idx] = true;
            } else {
                result_array_ptr[idx] = false;
            }
        }

        return result_array;
    }


    long __len__ () {
        return __set.size();
    }


    py::array_t<Key> items () {
        auto result_array = py::array_t<Key>( __set.size() );
        py::buffer_info result_array_buffer = result_array.request();
        auto * result_array_ptr = (Key *) result_array_buffer.ptr;

        size_t idx = 0;
        for ( auto & key : __set ) {
            result_array_ptr[idx] = key;
            idx++;
        }

        return result_array;
    }


    void dump ( const std::string & filename ) {
        std::ofstream stream ( filename , std::ios::binary );
        cereal::BinaryOutputArchive oarchive ( stream );

        for ( auto & key : __set ) {
            oarchive(key);
        }
    }


    void load ( const std::string & filename ) {
        std::ifstream stream ( filename , std::ios::binary);
        cereal::BinaryInputArchive iarchive ( stream );

        Key in_key;
        while ( stream.peek() != EOF ) {
            iarchive(in_key);
            __set.emplace(in_key);
        }
    }


    phmap::flat_hash_set<Key> __set;
};


template<typename Key>
void declare_set(const py::module& m, const std::string& class_name) {
  using Class = Set<Key>;

  py::class_<Class>(m, class_name.c_str())
      .def(py::init<>())

      .def("add", &Class::add)
      .def("discard", &Class::discard)

      .def("contains", &Class::contains)

      .def("dump", &Class::dump)
      .def("load", &Class::load)

      .def("items", &Class::items)

      .def("__len__", &Class::__len__);
}


template<typename T, size_t N>
struct bytearray {
    std::array<T, N> bytearray;

    template <class Archive>
    void serialize( Archive & archive ) {
        archive( bytearray );
    }
};


template<typename T, size_t N>
bool operator == ( const bytearray<T, N> & a, const bytearray<T, N> & b ) {
    return a.bytearray == b.bytearray;
}


template<typename T, size_t N>
bytearray<T, N> & operator |= ( bytearray<T, N> & a, bytearray<T, N> b ) {
    for (int i = 0 ; i < N ; ++i) {
        a.bytearray[i] |= b.bytearray[i];
    }
}


template<typename T, size_t N>
bytearray<T, N> & operator &= ( bytearray<T, N> & a, bytearray<T, N> b ) {
    for (int i = 0 ; i < N ; ++i) {
        a.bytearray[i] &= b.bytearray[i];
    }
}


template<typename T, size_t N>
struct std::hash<std::array<T, N>> {
    size_t operator () ( const std::array<T, N> & array ) const {
        size_t seed = N;
        for(auto& value : array) {
            seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};


template<typename T, size_t N>
struct std::hash<bytearray<T, N>> {
    size_t operator () ( const bytearray<T, N> & array ) const {
        size_t seed = N;
        for(auto& value : array.bytearray) {
            seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
