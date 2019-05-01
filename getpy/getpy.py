from collections import MutableMapping

import numpy as np

from .getpy_types import types
from .getpy_types import dict_types
from .getpy_types import set_types

class Dict(MutableMapping):
    def __init__(self, key_type, value_type, default_value=None):
        self.__key_type = np.dtype(key_type)
        self.__value_type = np.dtype(value_type)
        self.__default_value = default_value

        if (self.__key_type, self.__value_type) not in dict_types:
            raise TypeError(f'The following key-value pair type is not supported: ({self.key_type}, {self.value_type}).')
        else:
            self.__dict_type = dict_types[(self.key_type, self.value_type)]

        if self.__default_value is None:
            self.__dict = self.__dict_type()
        else:
            self.__dict = self.__dict_type(default_value)


    def __repr__(self):
        return f'Dict Type: {self.dict_type}, Key Type: {self.key_type}, Value Type: {self.value_type}, Default Value: {self.default_value}'


    def __getitem__(self, key):
        self.type_check_key(key)
        return self.__dict.__getitem__(key)


    def __setitem__(self, key, value):
        self.type_check_key(key); self.type_check_value(value)
        self.__dict.__setitem__(key, value)


    def iadd(self, key, value):
        self.type_check_key(key); self.type_check_value(value)
        self.__dict.iadd(key, value)


    def isub(self, key, value):
        self.type_check_key(key); self.type_check_value(value)
        self.__dict.isub(key, value)


    def ior(self, key, value):
        self.type_check_key(key); self.type_check_value(value)
        self.__dict.ior(key, value)


    def iand(self, key, value):
        self.type_check_key(key); self.type_check_value(value)
        self.__dict.iand(key, value)


    def __delitem__(self, key):
        self.type_check_key(key)
        return self.__dict.__delitem__(key)


    def contains(self, key):
        self.type_check_key(key)
        return self.__dict.contains(key)
    __contains__ = contains


    def __len__(self):
        return self.__dict.__len__()


    def __iter__(self):
        for key, value in self.items():
            yield key


    def items(self):
        return self.__dict.items()


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


    @property
    def default_value(self):
        return self.__default_value


    def type_check_key(self, key):
        if not isinstance(key, np.ndarray):
            raise TypeError(f'Given key ({key}) is not an np.ndarray.')
        elif key.dtype != self.__key_type:
            raise TypeError(f'Given key dtype ({key.dtype}) is not the dict key dtype ({self.__key_type})')
        else:
            pass


    def type_check_value(self, value):
        if not isinstance(value, np.ndarray):
            raise TypeError(f'Given value ({value}) is not an np.ndarray.')
        elif value.dtype != self.__value_type:
            raise TypeError(f'Given value dtype ({value.dtype}) is not the dict value dtype ({self.__value_type})')
        else:
            pass





class Set(object):
    def __init__(self, key_type):
        self.__key_type = np.dtype(key_type)

        if self.__key_type not in set_types:
            raise TypeError(f'The following key type is not supported: ({self.key_type}).')
        else:
            self.__set_type = set_types[self.key_type]

        self.__set = self.__set_type()


    def __repr__(self):
        return f'Set Type: {self.set_type}, Key Type: {self.key_type}'


    def add(self, key):
        self.type_check_key(key)
        self.__set.add(key)


    def discard(self, key):
        self.type_check_key(key)
        return self.__set.discard(key)


    def contains(self, key):
        self.type_check_key(key)
        return self.__set.contains(key)


    def __len__(self):
        return self.__set.__len__()


    def __iter__(self):
        for key in self.items():
            yield key


    def items(self):
        return self.__set.items()


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


    def type_check_key(self, key):
        if not isinstance(key, np.ndarray):
            raise TypeError(f'Given key ({key}) is not an np.ndarray.')
        elif key.dtype != self.__key_type:
            raise TypeError(f'Given key dtype ({key.dtype}) is not the set key dtype ({self.__key_type})')
        else:
            pass
