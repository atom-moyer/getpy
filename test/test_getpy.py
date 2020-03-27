import pytest

import numpy as np
import getpy as gp


def test_getpy_methods():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    keys = np.random.randint(1, 1000, size=10**2, dtype=key_type)
    values = np.random.randint(1, 1000, size=10**2, dtype=value_type)

    gp_dict = gp.Dict(key_type, value_type)
    gp_dict[keys] = values

    p_dict = {key : value for key, value in zip(keys, values)}

    assert len(gp_dict) == len(np.unique(keys))
    assert all([gp_dict[key] == p_dict[key] for key in keys])


def test_getpy_methods_with_multidim():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    keys = np.random.randint(1, 1000, size=10**2, dtype=key_type).reshape(10,10)
    values = np.random.randint(1, 1000, size=10**2, dtype=value_type).reshape(10,10)

    gp_dict = gp.Dict(key_type, value_type)
    gp_dict[keys] = values

    p_dict = {key : value for key, value in zip(keys.flat, values.flat)}

    assert len(gp_dict) == len(np.unique(keys))
    assert all([gp_dict[key] == p_dict[key] for key in keys.flat])


def test_getpy_methods_with_strings():
    key_type = np.dtype('S8')
    value_type = np.dtype('S8')

    keys = np.array([np.random.bytes(8) for i in range(10**2)], dtype=key_type)
    values = np.array([np.random.bytes(8) for i in range(10**2)], dtype=value_type)

    gp_dict = gp.Dict(key_type, value_type)
    gp_dict[keys] = values

    p_dict = {key : value for key, value in zip(keys, values)}

    assert len(gp_dict) == len(np.unique(keys))
    assert all([gp_dict[key] == p_dict[key] for key in keys])


def test_getpy_methods_with_multidim_and_strings():
    key_type = np.dtype('S8')
    value_type = np.dtype('S8')

    keys = np.array([np.random.bytes(4) for i in range(10**2)], dtype=key_type).reshape(10,10)
    values = np.array([np.random.bytes(4) for i in range(10**2)], dtype=value_type).reshape(10,10)

    gp_dict = gp.Dict(key_type, value_type)
    gp_dict[keys] = values

    p_dict = {key : value for key, value in zip(keys.flat, values.flat)}

    assert len(gp_dict) == len(np.unique(keys.flat))
    assert all([gp_dict[key] == p_dict[key] for key in keys.flat])


def test_getpy_methods_with_default():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    keys = np.random.randint(1, 1000, size=10**2, dtype=key_type)
    values = np.random.randint(1, 1000, size=10**2, dtype=value_type)

    default_value = 4242
    gp_dict = gp.Dict(key_type, value_type, default_value=default_value)
    gp_dict[keys] = values

    random_keys = np.random.randint(1, 1000, size=500, dtype=key_type)
    random_values = gp_dict[random_keys]

    assert np.all(random_values[np.where(gp_dict.contains(random_keys))] != default_value)
    assert np.all(random_values[np.where(np.logical_not(gp_dict.contains(random_keys)))] == default_value)


def test_getpy_methods_with_default_and_strings():
    key_type = np.dtype('S8')
    value_type = np.dtype('S8')

    keys = np.array([np.random.bytes(8) for i in range(10**2)], dtype=key_type)
    values = np.array([np.random.bytes(8) for i in range(10**2)], dtype=value_type)

    default_value = np.random.bytes(8)
    gp_dict = gp.Dict(key_type, value_type, default_value=default_value)
    gp_dict[keys] = values

    random_keys = np.array([np.random.bytes(8) for i in range(10**3)], dtype=key_type)
    random_values = gp_dict[random_keys]

    assert np.all(random_values[np.where(gp_dict.contains(random_keys))] != default_value)
    assert np.all(random_values[np.where(np.logical_not(gp_dict.contains(random_keys)))] == default_value)


def test_getpy_types():
    for key_type, value_type in gp.dict_types:
        gp_dict = gp.Dict(key_type, value_type)

        keys = np.array(range(256), dtype=key_type)
        values = np.array(range(256), dtype=value_type)

        gp_dict[keys] = values

    values = gp_dict[keys]


def test_getpy_dump_load():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    keys = np.random.randint(1, 1000, size=10**1, dtype=key_type)
    values = np.random.randint(1, 1000, size=10**1, dtype=value_type)

    gp_dict_1 = gp.Dict(key_type, value_type)
    gp_dict_1[keys] = values
    gp_dict_1.dump('test/test.bin')

    gp_dict_2 = gp.Dict(key_type, value_type)
    gp_dict_2.load('test/test.bin')

    assert len(gp_dict_1) == len(gp_dict_2)


def test_getpy_big_dict_u4_u4():
    key_type = np.dtype('u4')
    value_type = np.dtype('u4')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**9, size=10**4, dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**9, size=10**4, dtype=key_type)
        gp_dict[keys] = values


def test_getpy_big_dict_u8_u8():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**15, size=10**4, dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**4, dtype=key_type)
        gp_dict[keys] = values


def test_getpy_big_dict_u8_S8():
    key_type = np.dtype('u8')
    value_type = np.dtype('S8')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.array([np.random.bytes(8) for i in range(10**4)], dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**4, dtype=key_type)
        gp_dict[keys] = values


def test_getpy_big_dict_u8_u8_lookup():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    keys = np.random.randint(10**15, size=10**5, dtype=key_type)
    values = np.random.randint(10**15, size=10**5, dtype=value_type)

    gp_dict[keys] = values

    for i in range(10**2):
        values = gp_dict[keys]


def test_getpy_very_big_dict_u4_u4():
    key_type = np.dtype('u4')
    value_type = np.dtype('u4')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**9, size=10**5, dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**9, size=10**5, dtype=key_type)
        gp_dict[keys] = values


def test_getpy_very_big_dict_u8_u8():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**15, size=10**5, dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**5, dtype=key_type)
        gp_dict[keys] = values


def test_getpy_very_big_dict_u8_S8():
    key_type = np.dtype('u8')
    value_type = np.dtype('S8')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.array([np.random.bytes(8) for i in range(10**5)], dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**5, dtype=key_type)
        gp_dict[keys] = values


def test_getpy_very_big_dict_u8_S16():
    key_type = np.dtype('u8')
    value_type = np.dtype('S16')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.array([np.random.bytes(16) for i in range(10**5)], dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**5, dtype=key_type)
        gp_dict[keys] = values
