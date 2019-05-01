import pytest

import numpy as np

import getpy as gp


standard = pytest.mark.standard
slow = pytest.mark.slow


@standard
def test_getpy_vectorized_methods():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    keys = np.random.randint(1, 1000, size=200, dtype=key_type)
    values = np.random.randint(1, 1000, size=200, dtype=value_type)

    gp_dict[keys] = values

    iterated_keys = [key for key in gp_dict]
    iterated_keys_and_values = [(key, value) for key, value in gp_dict.items()]

    assert len(gp_dict) == len(np.unique(keys))

    p_dict = dict()
    for key, value in zip(keys, values):
        p_dict[key] = value

    assert len(gp_dict) == len(p_dict)
    assert sorted([(key, value) for key, value in gp_dict.items()]) == sorted(p_dict.items())

    select_keys = np.random.choice(keys, size=100).astype(key_type)
    select_values = gp_dict[select_keys]

    random_keys = np.random.randint(1, 1000, size=500).astype(key_type)
    random_keys_mask = gp_dict.contains(random_keys)

    mask_keys = random_keys[random_keys_mask]
    mask_values = gp_dict[mask_keys]

    gp_dict.iadd(keys, values)
    gp_dict.isub(keys, values)
    gp_dict.ior(keys, values)
    gp_dict.iand(keys, values)


@standard
def test_getpy_vectorized_methods_with_default():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type, default_value=0)

    keys = np.random.randint(1, 1000, size=200, dtype=key_type)
    values = np.random.randint(1, 1000, size=200, dtype=value_type)

    gp_dict[keys] = values

    iterated_keys = [key for key in gp_dict]
    iterated_keys_and_values = [(key, value) for key, value in gp_dict.items()]

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
    gp_dict.ior(random_keys, one_values)
    gp_dict.iand(random_keys, one_values)


@standard
def test_getpy_vectorized_methods_with_bytearray_dtype():
    key_type = np.dtype('u8')
    value_type = gp.types['bytearray50']

    gp_dict = gp.Dict(key_type, value_type)

    keys = np.random.randint(1, 1000, size=200, dtype=key_type)
    values = np.packbits([np.array([1, 0, 1, 0, 1, 0, 1, 0,
                                    1, 1, 1, 1, 1, 1, 1, 1]*25, dtype=np.bool)]*200, axis=1).view(value_type)
    gp_dict[keys] = values

    # keys = [key for key in gp_dict]
    # keys_and_values = [(key, value) for key, value in gp_dict.items()]

    select_keys = np.random.choice(keys, size=100)
    select_values = gp_dict[select_keys]

    random_keys = np.random.randint(1, 1000, size=500, dtype=key_type)
    random_keys_mask = gp_dict.contains(random_keys)

    mask_keys = random_keys[random_keys_mask]
    mask_values = gp_dict[mask_keys]

    gp_dict.iadd(keys, values)
    gp_dict.isub(keys, values)
    gp_dict.ior(keys, values)
    gp_dict.iand(keys, values)


@standard
def test_getpy_types():
    for key_type, value_type in gp.dict_types:
        gp_dict = gp.Dict(key_type, value_type)

        if key_type.kind == 'U':
            keys = np.array(['0123456789'*10 for i in range(10)], dtype=key_type)
        else:
            keys = np.array(range(10), dtype=key_type)

        if value_type.kind == 'U':
            values = np.array(['0123456789'*10 for i in range(10)], dtype=value_type)
        else:
            values = np.array(range(10), dtype=value_type)

        gp_dict[keys] = values

    values = gp_dict[keys]


@standard
@pytest.mark.timeout(1)
def test_getpy_dump_load():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict_1 = gp.Dict(key_type, value_type)

    keys = np.random.randint(1, 1000, size=10**1, dtype=key_type)
    values = np.random.randint(1, 1000, size=10**1, dtype=value_type)
    gp_dict_1[keys] = values

    gp_dict_1.dump('test/test.hashtable.bin')

    gp_dict_2 = gp.Dict(key_type, value_type)
    gp_dict_2.load('test/test.hashtable.bin')

    assert gp_dict_1 == gp_dict_2


@standard
@pytest.mark.timeout(1)
def test_getpy_big_dict_uint32_uint32():
    key_type = np.dtype('u4')
    value_type = np.dtype('u4')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**9, size=10**4, dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**9, size=10**4, dtype=key_type)
        gp_dict[keys] = values


@standard
@pytest.mark.timeout(1)
def test_getpy_big_dict_uint64_uint64():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**15, size=10**4, dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**4, dtype=key_type)
        gp_dict[keys] = values


@pytest.mark.timeout(1)
def test_getpy_big_dict_uint64_bytearray8():
    key_type = np.dtype('u8')
    value_type = gp.types['bytearray8']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.packbits([np.array([1, 0, 1, 0, 1, 0, 1, 0,
                                    1, 1, 1, 1, 1, 1, 1, 1]*4, dtype=np.bool)]*10**4, axis=1).view(value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**4, dtype=key_type)
        gp_dict[keys] = values


@standard
@pytest.mark.timeout(1)
def test_getpy_big_dict_uint64_lookup():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    keys = np.random.randint(10**15, size=10**5, dtype=key_type)
    values = np.random.randint(10**15, size=10**5, dtype=value_type)

    gp_dict[keys] = values

    for i in range(10**2):
        values = gp_dict[keys]


@standard
@pytest.mark.timeout(5)
def test_getpy_very_big_dict_uint32_uint32():
    key_type = np.dtype('u4')
    value_type = np.dtype('u4')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**9, size=10**5, dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**9, size=10**5, dtype=key_type)
        gp_dict[keys] = values


@standard
@pytest.mark.timeout(5)
def test_getpy_very_big_dict_uint64_uint64():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**15, size=10**5, dtype=value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**5, dtype=key_type)
        gp_dict[keys] = values


@standard
@pytest.mark.timeout(5)
def test_getpy_very_big_dict_uint64_bytearray8():
    key_type = np.dtype('u8')
    value_type = gp.types['bytearray8']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.packbits([np.array([1, 0, 1, 0, 1, 0, 1, 0,
                                    1, 1, 1, 1, 1, 1, 1, 1]*4, dtype=np.bool)]*10**5, axis=1).view(value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**5, dtype=key_type)
        gp_dict[keys] = values


@standard
@pytest.mark.timeout(5)
def test_getpy_very_big_dict_uint64_bytearray16():
    key_type = np.dtype('u8')
    value_type = gp.types['bytearray16']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.packbits([np.array([1, 0, 1, 0, 1, 0, 1, 0,
                                    1, 1, 1, 1, 1, 1, 1, 1]*8, dtype=np.bool)]*10**5, axis=1).view(value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**5, dtype=key_type)
        gp_dict[keys] = values


@standard
@pytest.mark.timeout(5)
def test_getpy_very_big_dict_uint64_bytearray32():
    key_type = np.dtype('u8')
    value_type = gp.types['bytearray32']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.packbits([np.array([1, 0, 1, 0, 1, 0, 1, 0,
                                    1, 1, 1, 1, 1, 1, 1, 1]*16, dtype=np.bool)]*10**5, axis=1).view(value_type)

    for i in range(10**2):
        keys = np.random.randint(10**15, size=10**5, dtype=key_type)
        gp_dict[keys] = values
