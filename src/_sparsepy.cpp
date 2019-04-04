#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
namespace py = pybind11;

#include <sparsepp/spp.h>

#include <cereal/archives/binary.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>

template <typename Key, typename Value>
struct Serializer {
    bool operator()(std::ofstream * stream, const std::pair<const Key, Value> & key_value) const {
        cereal::BinaryOutputArchive oarchive ( * stream );
        oarchive(key_value);

        return true;
    }

    bool operator()(std::ifstream * stream, std::pair<const Key, Value> * key_value) const {
        std::pair<Key, Value> in_key_value;

        cereal::BinaryInputArchive iarchive ( * stream );
        iarchive(in_key_value);

        (const_cast<Key&>(key_value->first)) = in_key_value.first;
        key_value->second = in_key_value.second;

        return true;
    }
};


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
        std::shared_ptr<std::ofstream> file = std::make_shared<std::ofstream>( filename );
        __dict.serialize(Serializer<Key, Value>(), file.get());
    }

    void load ( const std::string & filename ) {
        std::shared_ptr<std::ifstream> file = std::make_shared<std::ifstream>( filename );
        __dict.unserialize(Serializer<Key, Value>(), file.get());
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

        .def("dump", &Class::dump)
        .def("load", &Class::load)

        .def("items", [](const Class &c) { return py::make_iterator(c.__dict.begin(), c.__dict.end()); }, py::keep_alive<0, 1>() )
        .def("__len__", &Class::__len__);
}
