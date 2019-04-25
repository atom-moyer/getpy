from collections import MutableMapping
from typing import Iterable

import numpy as np

from .getpy_types import types
from .getpy_types import dict_types

class Dict(MutableMapping):
    def __init__(self, key_type, value_type, default_value=None):
        self.__key_type = np.dtype(key_type)
        self.__value_type = np.dtype(value_type)
        self.__default_value = default_value

        if (self.__key_type, self.__value_type) not in dict_types:
            raise TypeError(f'The following key-value pair is not supported: ({self.key_type}, {self.value_type}).')
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
        return self.__dict.__setitem__(key, value)


    def __delitem__(self, key):
        self.type_check_key(key)
        return self.__dict.__delitem__(key)


    def __contains__(self, key):
        self.type_check_key(key)
        return self.__dict.__contains__(key)


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
