from collections import MutableMapping

from .sparsepy_types import types_dict

class Dict(MutableMapping):
    def __init__(self, key_type, value_type):
        self.__dict = types_dict[(key_type, value_type)]()

    def __getitem__(self, key):
        return self.__dict.__getitem__(key)

    def __setitem__(self, key, value):
        self.__dict.__setitem__(key, value)

    def __delitem__(self, key):
        self.__dict.__delitem__(key)

    def __contains__(self, key):
        return self.__dict.__contains__(key)

    def __len__(self):
        return self.__dict.__len__()

    def __iter__(self):
        pass
