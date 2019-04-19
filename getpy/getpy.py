from collections import MutableMapping
from typing import Iterable

import numpy as np

from .getpy_types import types
from .getpy_types import dict_types

class Dict(MutableMapping):
    def __init__(self, key_type, value_type):
        self.key_type = np.dtype(key_type)
        self.value_type = np.dtype(value_type)

        if (self.key_type, self.value_type) not in dict_types:
            raise TypeError(f'The following key-value pair is not supported: ({self.key_type}, {self.value_type}).')
        else:
            self.dict_type = dict_types[(self.key_type, self.value_type)]

        self._dict = self.dict_type()

    def __repr__(self):
        return str(self.key_type), str(self.value_type)

    def __getitem__(self, key):
        if isinstance(key, np.ndarray):
            return self._dict.__getitem__(key)
        else:
            return self._dict.__getitem__(np.array([key], dtype=self.key_type))

    def __setitem__(self, key, value):
        if isinstance(key, np.ndarray):
            self._dict.__setitem__(key, value)
        else:
            self._dict.__setitem__(np.array([key], dtype=self.key_type),
                                   np.array([value], dtype=self.value_type))

    def __delitem__(self, key):
        if isinstance(key, np.ndarray):
            self._dict.__delitem__(key)
        else:
            self._dict.__delitem__(np.array([key], dtype=self.key_type))

    def __contains__(self, key):
        if isinstance(key, np.ndarray):
            return self._dict.__contains__(key)
        else:
            return self._dict.__contains__(np.array([key], dtype=self.key_type))

    def __len__(self):
        return self._dict.__len__()

    def __iter__(self):
        for key, value in self.items():
            yield key

    def items(self):
        return self._dict.items()

    def dump(self, filename):
        return self._dict.dump(filename)

    def load(self, filename):
        return self._dict.load(filename)
