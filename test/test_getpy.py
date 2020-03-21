import pytest

import sys

import numpy as np

import getpy as gp


def test_getpy_vectorized_methods():
    key_type = gp.types['uint64']
    value_type = gp.types['uint64']

    gp_dict = gp.Dict(key_type, value_type)

    keys = np.random.randint(1, 1000, size=200, dtype=key_type)
    values = np.random.randint(1, 1000, size=200, dtype=value_type)

    gp_dict[keys] = values

    iterated_keys = [key for key in gp_dict]
    iterated_keys_and_values = [(key, value) for key, value in zip(*gp_dict.items())]

    assert len(gp_dict) == len(np.unique(keys))

    p_dict = dict()
    for key, value in zip(keys, values):
        p_dict[key] = value

    assert len(gp_dict) == len(p_dict)

    select_keys = np.random.choice(keys, size=100)
    select_values = gp_dict[select_keys]

    random_keys = np.random.randint(1, 1000, size=500, dtype=key_type)
    random_keys_mask = gp_dict.contains(random_keys)

    mask_keys = random_keys[random_keys_mask]
    mask_values = gp_dict[mask_keys]

    gp_dict.iadd(keys, values)
    gp_dict.isub(keys, values)


def test_getpy_vectorized_methods_with_default():
    key_type = gp.types['uint64']
    value_type = gp.types['uint64']

    gp_dict = gp.Dict(key_type, value_type, default_value=0)

    keys = np.random.randint(1, 1000, size=200, dtype=key_type)
    values = np.random.randint(1, 1000, size=200, dtype=value_type)

    gp_dict[keys] = values

    iterated_keys = [key for key in gp_dict]
    iterated_keys_and_values = [(key, value) for key, value in zip(*gp_dict.items())]

    select_keys = np.random.choice(keys, size=100)
    select_values = gp_dict[select_keys]

    random_keys = np.random.randint(1, 1000, size=500, dtype=key_type)
    random_keys_mask = gp_dict.contains(random_keys)
    random_values_with_defaults = gp_dict[random_keys]

    for random_key_mask, random_value in zip(random_keys_mask, random_values_with_defaults):
        if not random_key_mask:
            assert random_value == 0
        else:
            assert random_value != 0

    one_values = np.ones(500, dtype=value_type)

    gp_dict.iadd(random_keys, one_values)
    gp_dict.isub(random_keys, one_values)


def test_getpy_vectorized_methods_with_byteset():
    key_type = gp.types['uint64']
    value_type = gp.types['byteset8']

    gp_dict = gp.Dict(key_type, value_type)

    keys = np.random.randint(1, 1000, size=10**2, dtype=key_type)
    values = np.array([np.packbits(np.array([1, 0, 1, 0, 1, 0, 1, 0] * 8, dtype=np.bool)) for _ in range(10**2)]).view(value_type)
    gp_dict[keys] = values

    iterated_keys = [key for key in gp_dict]
    iterated_keys_and_values = [(key, value) for key, value in zip(*gp_dict.items())]

    select_keys = np.random.choice(keys, size=100)
    select_values = gp_dict[select_keys]

    random_keys = np.random.randint(1, 1000, size=500, dtype=key_type)
    random_keys_mask = gp_dict.contains(random_keys)

    mask_keys = random_keys[random_keys_mask]
    mask_values = gp_dict[mask_keys]

    gp_dict.ior(keys, values)
    gp_dict.iand(keys, values)


def test_getpy_types():
    for key_type, value_type in gp.dict_types:
        gp_dict = gp.Dict(key_type, value_type)

        keys = np.array(range(256), dtype=key_type)
        values = np.array(range(256), dtype=value_type)

        gp_dict[keys] = values

    values = gp_dict[keys]


def test_getpy_dump_load():
    key_type = gp.types['uint64']
    value_type = gp.types['uint64']

    keys = np.random.randint(1, 1000, size=10**1, dtype=key_type)
    values = np.random.randint(1, 1000, size=10**1, dtype=value_type)

    gp_dict_1 = gp.Dict(key_type, value_type)
    gp_dict_1[keys] = values
    gp_dict_1.dump('test/test.hashtable.bin')

    gp_dict_2 = gp.Dict(key_type, value_type)
    gp_dict_2.load('test/test.hashtable.bin')

    assert len(gp_dict_1) == len(gp_dict_2)


def test_getpy_big_dict_uint32_uint32():
    key_type = gp.types['uint32']
    value_type = gp.types['uint32']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**9, size=10**4, dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**9, size=10**4, dtype=key_type)
        gp_dict[keys] = values


def test_getpy_big_dict_uint64_uint64():
    key_type = gp.types['uint64']
    value_type = gp.types['uint64']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**15, size=10**4, dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**4, dtype=key_type)
        gp_dict[keys] = values


def test_getpy_big_dict_uint64_byteset8():
    key_type = gp.types['uint64']
    value_type = gp.types['byteset8']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.array([np.packbits(np.array([1, 0, 1, 0, 1, 0, 1, 0] * 8, dtype=np.bool)) for _ in range(10**4)]).view(value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**4, dtype=key_type)
        gp_dict[keys] = values


def test_getpy_big_dict_uint64_lookup():
    key_type = gp.types['uint64']
    value_type = gp.types['uint64']

    gp_dict = gp.Dict(key_type, value_type)

    keys = np.random.randint(10**15, size=10**5, dtype=key_type)
    values = np.random.randint(10**15, size=10**5, dtype=value_type)

    gp_dict[keys] = values

    for i in range(10**2):
        values = gp_dict[keys]


def test_getpy_very_big_dict_uint32_uint32():
    key_type = gp.types['uint32']
    value_type = gp.types['uint32']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**9, size=10**5, dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**9, size=10**5, dtype=key_type)
        gp_dict[keys] = values


def test_getpy_very_big_dict_uint64_uint64():
    key_type = gp.types['uint64']
    value_type = gp.types['uint64']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**15, size=10**5, dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**5, dtype=key_type)
        gp_dict[keys] = values


def test_getpy_very_big_dict_uint64_byteset8():
    key_type = gp.types['uint64']
    value_type = gp.types['byteset8']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.array([np.packbits(np.array([1, 0, 1, 0, 1, 0, 1, 0] * 8, dtype=np.bool)) for _ in range(10**5)]).view(value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**5, dtype=key_type)
        gp_dict[keys] = values


def test_getpy_very_big_dict_uint64_byteset16():
    key_type = gp.types['uint64']
    value_type = gp.types['byteset16']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.array([np.packbits(np.array([1, 0, 1, 0, 1, 0, 1, 0] * 16, dtype=np.bool)) for _ in range(10**5)]).view(value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**5, dtype=key_type)
        gp_dict[keys] = values
