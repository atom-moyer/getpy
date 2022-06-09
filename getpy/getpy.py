from collections.abc import MutableMapping, MutableSet

from .getpy_types import dict_types
from .getpy_types import set_types
from .getpy_types import multidict_types


class Dict(MutableMapping):
    def __init__(self, key_type, value_type, default_value=None, filename=None, safe_mode=False):
        self.__key_type = key_type
        self.__value_type = value_type
        self.__dict_type = dict_types[(key_type, value_type)]

        if default_value is None:
            self.__dict = self.__dict_type()
        else:
            self.__dict = self.__dict_type(default_value)

        if filename is not None:
            self.__dict.load(filename)

        self.__safe_mode = safe_mode


    def __repr__(self):
        return '{' + ', '.join(['{key} : {value}'.format(**vars()) for key, value in zip(*self.items())]) + '}'


    def __getitem__(self, key):
        if self.__safe_mode: assert key.dtype == self.__key_type, (key.dtype,)
        return self.__dict.__getitem__(key)


    def __setitem__(self, key, value):
        if self.__safe_mode: assert key.dtype == self.__key_type and value.dtype == self.__value_type, (key.dtype, value.dtype)
        self.__dict.__setitem__(key, value)


    def iadd(self, key, value):
        if self.__safe_mode: assert key.dtype == self.__key_type and value.dtype == self.__value_type, (key.dtype, value.dtype)
        self.__dict.iadd(key, value)


    def isub(self, key, value):
        if self.__safe_mode: assert key.dtype == self.__key_type and value.dtype == self.__value_type, (key.dtype, value.dtype)
        self.__dict.isub(key, value)


    def ior(self, key, value):
        if self.__safe_mode: assert key.dtype == self.__key_type and value.dtype == self.__value_type, (key.dtype, value.dtype)
        self.__dict.ior(key, value)


    def iand(self, key, value):
        if self.__safe_mode: assert key.dtype == self.__key_type and value.dtype == self.__value_type, (key.dtype, value.dtype)
        self.__dict.iand(key, value)


    def __delitem__(self, key):
        if self.__safe_mode: assert key.dtype == self.__key_type, (key.dtype,)
        return self.__dict.__delitem__(key)


    def contains(self, key):
        if self.__safe_mode: assert key.dtype == self.__key_type, (key.dtype,)
        return self.__dict.contains(key)
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


    @property
    def key_type(self):
        return self.__key_type


    @property
    def value_type(self):
        return self.__value_type


    @property
    def dict_type(self):
        return self.__dict_type


class Set(MutableSet):
    def __init__(self, key_type, filename=None, safe_mode=False):
        self.__key_type = key_type
        self.__set_type = set_types[key_type]

        self.__set = self.__set_type()

        if filename is not None:
            self.__set.load(filename)

        self.__safe_mode = safe_mode


    def __repr__(self):
        return '{' + ', '.join(['{key}'.format(**vars()) for key in self.items()]) + '}'


    def add(self, key):
        if self.__safe_mode: assert key.dtype == self.__key_type, (key.dtype,)
        self.__set.add(key)


    def discard(self, key):
        if self.__safe_mode: assert key.dtype == self.__key_type, (key.dtype,)
        return self.__set.discard(key)


    def contains(self, key):
        if self.__safe_mode: assert key.dtype == self.__key_type, (key.dtype,)
        return self.__set.contains(key)
    __contains__ = contains


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


    @property
    def key_type(self):
        return self.__key_type


    @property
    def set_type(self):
        return self.__set_type


class MultiDict(MutableMapping):
    def __init__(self, key_type, value_type, default_value=None, filename=None, safe_mode=False):
        self.__key_type = key_type
        self.__value_type = value_type
        self.__dict_type = multidict_types[(key_type, value_type)]

        if default_value is None:
            self.__dict = self.__dict_type()
        else:
            self.__dict = self.__dict_type(default_value)

        if filename is not None:
            self.__dict.load(filename)

        self.__safe_mode = safe_mode


    def __repr__(self):
        return '' # '{' + ', '.join(['{key} : {value}'.format(**vars()) for key, value in zip(*self.items())]) + '}'


    def __getitem__(self, key):
        if self.__safe_mode: assert key.dtype == self.__key_type, (key.dtype,)
        return self.__dict.__getitem__(key)


    def __setitem__(self, key, value):
        if self.__safe_mode: assert key.dtype == self.__key_type and value.dtype == self.__value_type, (key.dtype, value.dtype)
        self.__dict.__setitem__(key, value)


    def __delitem__(self, key):
        if self.__safe_mode: assert key.dtype == self.__key_type, (key.dtype,)
        return self.__dict.__delitem__(key)


    def contains(self, key):
        if self.__safe_mode: assert key.dtype == self.__key_type, (key.dtype,)
        return self.__dict.contains(key)
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


    @property
    def key_type(self):
        return self.__key_type


    @property
    def value_type(self):
        return self.__value_type


    @property
    def dict_type(self):
        return self.__dict_type
