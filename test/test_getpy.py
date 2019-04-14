import pytest

import numpy as np

import getpy as gp

fast = pytest.mark.fast
standard = pytest.mark.standard
slow = pytest.mark.slow
very_slow = pytest.mark.very_slow


@standard
def test_sparsepy_methods():
    key_type = np.dtype('u8')
    value_type = np.uint64

    gp_dict = gp.Dict(key_type, value_type)

    gp_dict[42] = 1337

    assert gp_dict[42] == 1337
    assert 42 in gp_dict
    assert 41 not in gp_dict
    assert len(gp_dict) == 1

    del gp_dict[42]

    assert 42 not in gp_dict
    assert 41 not in gp_dict
    assert len(gp_dict) == 0


@standard
def test_sparsepy_vectorized_methods():
    key_type = np.dtype('u8')
    value_type = np.uint64

    gp_dict = gp.Dict(key_type, value_type)

    keys = np.random.randint(1000, size=200, dtype=key_type)
    values = np.random.randint(1000, size=200, dtype=value_type)

    gp_dict[keys] = values

    keys = [key for key in gp_dict]
    keys_and_values = [(key, value) for key, value in gp_dict.items()]

    select_keys = np.random.choice(keys, size=100)
    select_values = gp_dict[select_keys]

    random_keys = np.random.randint(1000, size=500, dtype=key_type)
    random_keys_mask = gp_dict.__contains__(random_keys)

    mask_keys = random_keys[random_keys_mask]
    mask_values = gp_dict[mask_keys]


@standard
def test_sparsepy_types():
    for key_type, value_type in gp.types:
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


@standard
@pytest.mark.timeout(1)
def test_sparsepy_dump_load():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict_1 = gp.Dict(key_type, value_type)

    keys = np.random.randint(1000, size=10, dtype=key_type)
    values = np.random.randint(1000, size=10, dtype=value_type)
    gp_dict_1[keys] = values

    gp_dict_1.dump('test/test.hashtable.bin')

    gp_dict_2 = gp.Dict(key_type, value_type)
    gp_dict_2.load('test/test.hashtable.bin')

    assert gp_dict_1 == gp_dict_2


@standard
@pytest.mark.timeout(1)
def test_sparsepy_big_dict_uint32():
    key_type = np.dtype('u4')
    value_type = np.dtype('u4')

    gp_dict = gp.Dict(key_type, value_type)

    for i in range(10**3):
        keys = np.random.randint(10**9, size=10**3, dtype=key_type)
        values = np.random.randint(10**9, size=10**3, dtype=value_type)

        gp_dict[keys] = values


@standard
@pytest.mark.timeout(1)
def test_sparsepy_big_dict_uint64():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    for i in range(10**3):
        keys = np.random.randint(10**15, size=10**3, dtype=key_type)
        values = np.random.randint(10**15, size=10**3, dtype=value_type)

        gp_dict[keys] = values

@standard
@pytest.mark.timeout(1)
def test_sparsepy_big_dict_str4():
    key_type = np.dtype('U4')
    value_type = np.dtype('U4')

    gp_dict = gp.Dict(key_type, value_type)

    chars = list('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789')

    for i in range(10**1):
        keys = np.array([''.join(np.random.choice(chars, 4)) for i in range(10**3)], dtype=key_type)
        values = np.array([''.join(np.random.choice(chars, 4)) for i in range(10**3)], dtype=value_type)

        gp_dict[keys] = values


@standard
@pytest.mark.timeout(1)
def test_sparsepy_big_dict_str8():
    key_type = np.dtype('U8')
    value_type = np.dtype('U8')

    gp_dict = gp.Dict(key_type, value_type)

    chars = list('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789')

    for i in range(10**1):
        keys = np.array([''.join(np.random.choice(chars, 8)) for i in range(10**3)], dtype=key_type)
        values = np.array([''.join(np.random.choice(chars, 8)) for i in range(10**3)], dtype=value_type)

        gp_dict[keys] = values


@standard
@pytest.mark.timeout(1)
def test_sparsepy_big_dict_uint64_lookup():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    for i in range(10**3):
        keys = np.random.randint(10**15, size=10**3, dtype=key_type)
        values = np.random.randint(10**15, size=10**3, dtype=value_type)

        gp_dict[keys] = values

    values = gp_dict[keys]


@standard
@pytest.mark.timeout(10)
def test_sparsepy_big_dict_uint64_dump_load():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict_1 = gp.Dict(key_type, value_type)

    for i in range(10**3):
        keys = np.random.randint(10**15, size=10**3, dtype=key_type)
        values = np.random.randint(10**15, size=10**3, dtype=value_type)

        gp_dict_1[keys] = values

    gp_dict_1.dump('test/test.hashtable.bin')

    gp_dict_2 = gp.Dict(key_type, value_type)
    gp_dict_2.load('test/test.hashtable.bin')

    assert gp_dict_1 == gp_dict_2


@slow
@pytest.mark.timeout(50)
def test_sparsepy_very_big_dict_uint32():
    key_type = np.dtype('u4')
    value_type = np.dtype('u4')

    gp_dict = gp.Dict(key_type, value_type)

    for i in range(10**3):
        keys = np.random.randint(10**9, size=10**5, dtype=key_type)
        values = np.random.randint(10**9, size=10**5, dtype=value_type)

        gp_dict[keys] = values


@slow
@pytest.mark.timeout(50)
def test_sparsepy_very_big_dict_uint64():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    for i in range(10**3):
        keys = np.random.randint(10**15, size=10**5, dtype=key_type)
        values = np.random.randint(10**15, size=10**5, dtype=value_type)

        gp_dict[keys] = values


@very_slow
@pytest.mark.timeout(500)
def test_sparsepy_uber_big_dict_uint32():
    key_type = np.dtype('u4')
    value_type = np.dtype('u4')

    gp_dict = gp.Dict(key_type, value_type)

    for i in range(10**3):
        keys = np.random.randint(10**9, size=10**6, dtype=key_type)
        values = np.random.randint(10**9, size=10**6, dtype=value_type)

        gp_dict[keys] = values


@very_slow
@pytest.mark.timeout(500)
def test_sparsepy_uber_big_dict_uint64():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    for i in range(10**3):
        keys = np.random.randint(10**15, size=10**6, dtype=key_type)
        values = np.random.randint(10**15, size=10**6, dtype=value_type)

        gp_dict[keys] = values


# @slow
# @pytest.mark.timeout(5000)
# def test_sparsepy_extremely_big_dict_uint32():
#     key_type = np.dtype('u4')
#     value_type = np.dtype('u4')
#
#     gp_dict = gp.Dict(key_type, value_type)
#
#     for i in range(10**3):
#         keys = np.random.randint(10**9, size=10**7, dtype=key_type)
#         values = np.random.randint(10**9, size=10**7, dtype=value_type)
#
#         gp_dict[keys] = values
#
#
# @slow
# @pytest.mark.timeout(5000)
# def test_sparsepy_extremely_big_dict_uint64():
#     key_type = np.dtype('u8')
#     value_type = np.dtype('u8')
#
#     gp_dict = gp.Dict(key_type, value_type)
#
#     for i in range(10**3):
#         keys = np.random.randint(10**15, size=10**7, dtype=key_type)
#         values = np.random.randint(10**15, size=10**7, dtype=value_type)
#
#         gp_dict[keys] = values
