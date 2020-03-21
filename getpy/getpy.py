from collections.abc import MutableMapping, MutableSet

from .getpy_types import types
from .getpy_types import dict_types
from .getpy_types import set_types

class Dict(MutableMapping):
    def __init__(self, key_type, value_type, default_value=None, safe_mode=True):
        self.__key_type = key_type
        self.__value_type = value_type
        self.__default_value = default_value
        self.__safe_mode = safe_mode

        if (self.__key_type, self.__value_type) not in dict_types:
            raise TypeError(f'The following key-value pair type is not supported: ({self.__key_type}, {self.__value_type}).')
        else:
            self.__dict_type = dict_types[(self.__key_type, self.__value_type)]

        if self.__default_value is None:
            self.__dict = self.__dict_type()
        else:
            self.__dict = self.__dict_type(default_value)


    def __repr__(self):
        return f'Dict Type: {self.__dict_type}, Key Type: {self.__key_type}, Value Type: {self.__value_type}, Default Value: {self.__default_value}'


    def __getitem__(self, key):
        if self.__safe_mode:
            assert key.dtype == self.__key_type

        return self.__dict.__getitem__(key.view(self.__key_type))


    def __setitem__(self, key, value):
        if self.__safe_mode:
            assert key.dtype == self.__key_type and value.dtype == self.__value_type

        self.__dict.__setitem__(key.view(self.__key_type), value.view(self.__value_type))


    def iadd(self, key, value):
        if self.__safe_mode:
            assert key.dtype == self.__key_type and value.dtype == self.__value_type

        self.__dict.iadd(key.view(self.__key_type), value.view(self.__value_type))


    def isub(self, key, value):
        if self.__safe_mode:
            assert key.dtype == self.__key_type and value.dtype == self.__value_type

        self.__dict.isub(key.view(self.__key_type), value.view(self.__value_type))


    def ior(self, key, value):
        if self.__safe_mode:
            assert key.dtype == self.__key_type and value.dtype == self.__value_type

        self.__dict.ior(key.view(self.__key_type), value.view(self.__value_type))


    def iand(self, key, value):
        if self.__safe_mode:
            assert key.dtype == self.__key_type and value.dtype == self.__value_type

        self.__dict.iand(key.view(self.__key_type), value.view(self.__value_type))


    def __delitem__(self, key):
        if self.__safe_mode:
            assert key.dtype == self.__key_type

        return self.__dict.__delitem__(key.view(self.__key_type))


    def contains(self, key):
        if self.__safe_mode:
            assert key.dtype == self.__key_type

        return self.__dict.contains(key.view(self.__key_type))
    __contains__ = contains


    def __len__(self):
        return self.__dict.__len__()


    def keys(self):
        return self.__dict.keys()


    def values(self):
        return self.__dict.values()


    def items(self):
        return self.__dict.items()


    def __iter__(self):
        for key in self.keys():
            yield key


    def dump(self, filename):
        return self.__dict.dump(filename)


    def load(self, filename):
        return self.__dict.load(filename)


class Set(MutableSet):
    def __init__(self, key_type, safe_mode=True):
        self.__key_type = key_type
        self.__safe_mode = safe_mode

        if self.__key_type not in set_types:
            raise TypeError(f'The following key type is not supported: ({self.__key_type}).')
        else:
            self.__set_type = set_types[self.__key_type]

        self.__set = self.__set_type()


    def __repr__(self):
        return f'Set Type: {self.__set_type}, Key Type: {self.__key_type}'


    def add(self, key):
        if self.__safe_mode:
            assert key.dtype == self.__key_type

        self.__set.add(key.view(self.__key_type))


    def discard(self, key):
        if self.__safe_mode:
            assert key.dtype == self.__key_type

        return self.__set.discard(key.view(self.__key_type))


    def contains(self, key):
        if self.__safe_mode:
            assert key.dtype == self.__key_type

        return self.__set.contains(key.view(self.__key_type))


    def __len__(self):
        return self.__set.__len__()


    def items(self):
        return self.__set.items()


    def __iter__(self):
        for item in self.items():
            yield item


    def dump(self, filename):
        return self.__set.dump(filename)


    def load(self, filename):
        return self.__set.load(filename)
