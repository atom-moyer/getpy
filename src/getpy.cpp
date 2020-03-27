#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
namespace py = pybind11;

#include <parallel_hashmap/phmap.h>
#include <parallel_hashmap/phmap_utils.h>
#include <parallel_hashmap/phmap_dump.h>

#include <iostream>


template<typename T>
struct get_swap_type {
    typedef T type;
};


template<>
struct get_swap_type<float> {
    typedef uint32_t type;
};


template<>
struct get_swap_type<double> {
    typedef uint64_t type;
};


template <typename Key, typename Value>
struct Dict {
    Dict () {}


    Dict ( Value default_value ) : default_value ( default_value ) {}


    Dict ( py::array_t <Value> default_value ) : default_value ( ( (Value *) default_value.request().ptr )[0] ) {}


    py::array_t <Value> __getitem__ ( py::array_t <Key> & key_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;

        auto result_array = py::array_t <Value> ( key_array.request().shape );
        auto * result_array_ptr = (Value *) result_array.request().ptr;

        for ( size_t idx = 0; idx < key_array.size(); idx++ ) {
            auto search = dict.find( key_array_ptr[idx] );

            if ( search != dict.end() ) {
                result_array_ptr[idx] = search->second;
            } else {
                result_array_ptr[idx] = default_value;
            }
        }

        return result_array;
    }


    void __setitem__ ( py::array_t <Key> & key_array, py::array_t <Value> & value_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;
        auto * value_array_ptr = (Value *) value_array.request().ptr;

        if ( key_array.size() != value_array.size() )
            throw std::runtime_error("The size of the key and value must match.");

        for ( size_t idx = 0; idx < key_array.size(); idx++ ) {
            dict.insert_or_assign( key_array_ptr[idx], value_array_ptr[idx] );
        }
    }


    void __delitem__ ( py::array_t <Key> & key_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;

        for ( size_t idx = 0; idx < key_array.size(); idx++ )
            dict.erase( key_array_ptr[idx] );
    }


    void iadd ( py::array_t <Key> & key_array, py::array_t <Value> & value_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;
        auto * value_array_ptr = (Value *) value_array.request().ptr;

        if ( key_array.size() != value_array.size() )
            throw std::runtime_error("The size of the key and value must match.");

        for ( size_t idx = 0; idx < key_array.size(); idx++ ) {
            auto search = dict.find( key_array_ptr[idx] );

            if ( search != dict.end() ) {
                search->second += value_array_ptr[idx];
            } else {
                Value value = default_value + value_array_ptr[idx];
                dict.insert_or_assign( key_array_ptr[idx], value);
            }
        }
    }


    void isub ( py::array_t <Key> & key_array, py::array_t <Value> & value_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;
        auto * value_array_ptr = (Value *) value_array.request().ptr;

        if ( key_array.size() != value_array.size() )
            throw std::runtime_error("The size of the key and value must match.");

        for ( size_t idx = 0; idx < key_array.size(); idx++ ) {
            auto search = dict.find( key_array_ptr[idx] );

            if ( search != dict.end() ) {
                search->second -= value_array_ptr[idx];
            } else {
                Value value = default_value - value_array_ptr[idx];
                dict.insert_or_assign( key_array_ptr[idx], value);
            }
        }
    }


    void ior ( py::array_t <Key> & key_array, py::array_t <Value> & value_array ) {
        typedef typename get_swap_type<Value>::type tp;

        auto * key_array_ptr = (Key *) key_array.request().ptr;
        auto * value_array_ptr = (Value *) value_array.request().ptr;

        if ( key_array.size() != value_array.size() )
            throw std::runtime_error("The size of the key and value must match.");

        for ( size_t idx = 0; idx < key_array.size(); idx++ ) {
            auto search = dict.find( key_array_ptr[idx] );

            if ( search != dict.end() ) {
                tp value = (tp &) search->second | (tp &) value_array_ptr[idx];
                dict.insert_or_assign( key_array_ptr[idx], (Value &) value);
            } else {
                tp value = (tp &) default_value | (tp &) value_array_ptr[idx];
                dict.insert_or_assign( key_array_ptr[idx], (Value &) value);
            }
        }
    }


    void iand ( py::array_t <Key> & key_array, py::array_t <Value> & value_array ) {
        typedef typename get_swap_type<Value>::type tp;

        auto * key_array_ptr = (Key *) key_array.request().ptr;
        auto * value_array_ptr = (Value *) value_array.request().ptr;

        if ( key_array.size() != value_array.size() )
            throw std::runtime_error("The size of the key and value must match.");

        for ( size_t idx = 0; idx < key_array.size(); idx++ ) {
            auto search = dict.find( key_array_ptr[idx] );

            if ( search != dict.end() ) {
                tp value = (tp &) search->second & (tp &) value_array_ptr[idx];
                dict.insert_or_assign( key_array_ptr[idx], (Value &) value);
            } else {
                tp value = (tp &) default_value & (tp &) value_array_ptr[idx];
                dict.insert_or_assign( key_array_ptr[idx], (Value &) value);
            }
        }
    }


    py::array_t<bool> contains ( py::array_t <Key> & key_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;

        auto result_array = py::array_t<bool>( key_array.request().shape );
        auto * result_array_ptr = (bool *) result_array.request().ptr;

        for ( size_t idx = 0; idx < key_array.size(); idx++ ) {
            auto search = dict.find( key_array_ptr[idx] );

            if ( search != dict.end() ) {
                result_array_ptr[idx] = true;
            } else {
                result_array_ptr[idx] = false;
            }
        }

        return result_array;
    }


    size_t __len__ () {
        return dict.size();
    }


    py::array_t <Key> keys () {
        auto result_array = py::array_t <Key>( dict.size() );
        auto * result_array_ptr = (Key *) result_array.request().ptr;

        size_t idx = 0;
        for ( auto & key_value : dict ) {
            result_array_ptr[idx] = key_value.first;
            idx++;
        }

        return result_array;
    }


    py::array_t <Value> values () {
        auto result_array = py::array_t <Value>( dict.size() );
        auto * result_array_ptr = (Value *) result_array.request().ptr;

        size_t idx = 0;
        for ( auto & key_value : dict ) {
            result_array_ptr[idx] = key_value.second;
            idx++;
        }

        return result_array;
    }


    std::pair<py::array_t <Key>, py::array_t <Value>> items () {
        auto key_result_array = py::array_t <Key>( dict.size() );
        auto * key_result_array_ptr = (Key *) key_result_array.request().ptr;

        auto value_result_array = py::array_t <Value>( dict.size() );
        auto * value_result_array_ptr = (Value *) value_result_array.request().ptr;

        size_t idx = 0;
        for ( auto & key_value : dict ) {
            key_result_array_ptr[idx] = key_value.first;
            value_result_array_ptr[idx] = key_value.second;
            idx++;
        }

        return std::make_pair(key_result_array, value_result_array);
    }


    void dump ( const std::string & filename ) {
        phmap::BinaryOutputArchive ar_out( filename.c_str() );
        dict.dump( ar_out );
    }


    void load ( const std::string & filename ) {
        phmap::BinaryInputArchive ar_in( filename.c_str() );
        dict.load( ar_in );
    }


    Value default_value;
    phmap::flat_hash_map<Key, Value> dict;
};


template<typename Key, typename Value>
void declare_dict(const py::module& m, const std::string& class_name) {
  using Class = Dict<Key, Value>;

  py::class_<Class>(m, class_name.c_str())
      .def(py::init<>())
      .def(py::init<Value &>())
      .def(py::init<py::array_t <Value> &>())

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

      .def("keys", &Class::keys)
      .def("values", &Class::values)
      .def("items", &Class::items)

      .def("__len__", &Class::__len__);
}


template <typename Key>
struct Set {
    Set () {}


    void add ( py::array_t <Key> & key_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;

        for ( size_t idx = 0; idx < key_array.size(); idx++ ) {
            set.emplace( key_array_ptr[idx] );
        }
    }


    void discard ( py::array_t <Key> & key_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;

        for ( size_t idx = 0; idx < key_array.size(); idx++ )
            set.erase( key_array_ptr[idx] );
    }


    py::array_t<bool> contains ( py::array_t <Key> & key_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;

        auto result_array = py::array_t<bool>( key_array.request().shape );
        auto * result_array_ptr = (bool *) result_array.request().ptr;

        for ( size_t idx = 0; idx < key_array.size(); idx++ ) {
            auto search = set.find( key_array_ptr[idx] );

            if ( search != set.end() ) {
                result_array_ptr[idx] = true;
            } else {
                result_array_ptr[idx] = false;
            }
        }

        return result_array;
    }


    size_t __len__ () {
        return set.size();
    }


    py::array_t <Key> items () {
        auto result_array = py::array_t <Key>( set.size() );
        auto * result_array_ptr = (Key *) result_array.request().ptr;

        size_t idx = 0;
        for ( auto & key : set ) {
            result_array_ptr[idx] = key;
            idx++;
        }

        return result_array;
    }


    void dump ( const std::string & filename ) {
        phmap::BinaryOutputArchive ar_out( filename.c_str() );
        set.dump( ar_out );
    }


    void load ( const std::string & filename ) {
        phmap::BinaryInputArchive ar_in( filename.c_str() );
        set.load(ar_in);
    }


    phmap::flat_hash_set<Key> set;
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


template <typename Key, typename Value>
struct MultiDict {
    MultiDict () {}


    std::vector<py::array_t<Value>> __getitem__ ( py::array_t<Key> & key_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;

        std::vector<py::array_t<Value>> result_list;

        for ( size_t idx = 0; idx < key_array.size(); idx++ ) {
            auto search = dict.find( key_array_ptr[idx] );

            phmap::flat_hash_set<Value> result;

            if ( search != dict.end() ) {
                result = search->second;
            } else {
                result = default_value;
            }

            py::array_t<Value> result_array = py::cast( std::vector<Value> ( result.begin(), result.end() ) );
            result_list.push_back( result_array );
        }

        return result_list;
    }


    void __setitem__ ( py::array_t <Key> & key_array, py::array_t <Value> & value_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;
        auto * value_array_ptr = (Value *) value_array.request().ptr;

        if ( key_array.size() != value_array.size() )
            throw std::runtime_error("The size of the key and value must match.");

        for ( size_t idx = 0; idx < key_array.size(); idx++ ) {
            auto search = dict.find( key_array_ptr[idx] );

            phmap::flat_hash_set<Value> result;

            if ( search != dict.end() ) {
                result = search->second;
            } else {
                result = default_value;
            }

            result.emplace( value_array_ptr[idx] );
            dict.insert_or_assign( key_array_ptr[idx], result );
        }
    }


    void __delitem__ ( py::array_t <Key> & key_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;

        for ( size_t idx = 0; idx < key_array.size(); idx++ )
            dict.erase( key_array_ptr[idx] );
    }


    py::array_t<bool> contains ( py::array_t <Key> & key_array ) {
        auto * key_array_ptr = (Key *) key_array.request().ptr;

        auto result_array = py::array_t<bool>( key_array.request().shape );
        auto * result_array_ptr = (bool *) result_array.request().ptr;

        for ( size_t idx = 0; idx < key_array.size(); idx++ ) {
            auto search = dict.find( key_array_ptr[idx] );

            if ( search != dict.end() ) {
                result_array_ptr[idx] = true;
            } else {
                result_array_ptr[idx] = false;
            }
        }

        return result_array;
    }


    size_t __len__ () {
        return dict.size();
    }


    py::array_t <Key> keys () {
        auto result_array = py::array_t <Key>( dict.size() );
        auto * result_array_ptr = (Key *) result_array.request().ptr;

        size_t idx = 0;
        for ( auto & key_value : dict ) {
            result_array_ptr[idx] = key_value.first;
            idx++;
        }

        return result_array;
    }


    std::vector<py::array_t<Value>> values () {
        std::vector<py::array_t<Value>> result_list;

        for ( auto & key_value : dict ) {
            py::array_t<Value> result = py::cast( std::vector<Value> ( key_value.second.begin(), key_value.second.end() ) );
            result_list.push_back( result );
        }

        return result_list;
    }


    std::pair<py::array_t<Key>, std::vector<py::array_t<Value>>> items () {
        auto key_result_array = py::array_t<Key>( dict.size() );
        auto * key_result_array_ptr = (Key *) key_result_array.request().ptr;

        std::vector<py::array_t<Value>> value_result_list;

        size_t idx = 0;
        for ( auto & key_value : dict ) {
            key_result_array_ptr[idx] = key_value.first;

            py::array_t<Value> result = py::cast( std::vector<Value> ( key_value.second.begin(), key_value.second.end() ) );
            value_result_list.push_back( result );

            idx++;
        }

        return std::make_pair(key_result_array, value_result_list);
    }


    // void dump ( const std::string & filename ) {
    //     phmap::BinaryOutputArchive ar_out( filename.c_str() );
    //     dict.dump( ar_out );
    // }
    //
    //
    // void load ( const std::string & filename ) {
    //     phmap::BinaryInputArchive ar_in( filename.c_str() );
    //     dict.load( ar_in );
    // }


    phmap::flat_hash_set<Value> default_value;
    phmap::flat_hash_map<Key, phmap::flat_hash_set<Value>> dict;
};


template<typename Key, typename Value>
void declare_multidict(const py::module& m, const std::string& class_name) {
  using Class = MultiDict<Key, Value>;

  py::class_<Class>(m, class_name.c_str())
      .def(py::init<>())

      .def("__getitem__", &Class::__getitem__)
      .def("__setitem__", &Class::__setitem__)
      .def("__delitem__", &Class::__delitem__)

      .def("contains", &Class::contains)

      // .def("dump", &Class::dump)
      // .def("load", &Class::load)

      .def("keys", &Class::keys)
      .def("values", &Class::values)
      .def("items", &Class::items)

      .def("__len__", &Class::__len__);
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
std::array<T, N> & operator |= ( std::array<T, N> & a, const std::array<T, N> b ) {
    for (size_t i = 0 ; i < N ; ++i) {
        a[i] |= b[i];
    }

    return a;
}


template<typename T, size_t N>
std::array<T, N> & operator &= ( std::array<T, N> & a, const std::array<T, N> b ) {
    for (size_t i = 0 ; i < N ; ++i) {
        a[i] &= b[i];
    }

    return a;
}


template<typename T, size_t N>
std::array<T, N> operator | ( const std::array<T, N> & a, const std::array<T, N> b ) {
    std::array<T, N> c;

    for (size_t i = 0 ; i < N ; ++i) {
        c[i] = a[i] | b[i];
    }

    return c;
}


template<typename T, size_t N>
std::array<T, N> operator & ( const std::array<T, N> & a, const std::array<T, N> b ) {
    std::array<T, N> c;

    for (size_t i = 0 ; i < N ; ++i) {
        c[i] = a[i] & b[i];
    }

    return c;
}


template<typename T, size_t N>
std::array<T, N> & operator += ( std::array<T, N> & a, const std::array<T, N> b ) {
    for (size_t i = 0 ; i < N ; ++i) {
        a[i] += b[i];
    }

    return a;
}


template<typename T, size_t N>
std::array<T, N> & operator -= ( std::array<T, N> & a, const std::array<T, N> b ) {
    for (size_t i = 0 ; i < N ; ++i) {
        a[i] -= b[i];
    }

    return a;
}


template<typename T, size_t N>
std::array<T, N> operator + ( const std::array<T, N> & a, const std::array<T, N> b ) {
    std::array<T, N> c;

    for (size_t i = 0 ; i < N ; ++i) {
        c[i] = a[i] + b[i];
    }

    return c;
}


template<typename T, size_t N>
std::array<T, N> operator - ( const std::array<T, N> & a, const std::array<T, N> b ) {
    std::array<T, N> c;

    for (size_t i = 0 ; i < N ; ++i) {
        c[i] = a[i] - b[i];
    }

    return c;
}
