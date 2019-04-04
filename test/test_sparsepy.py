import pytest

import numpy as np

import sparsepy as sp

standard = pytest.mark.standard
long_ = pytest.mark.long_

print()

@standard
def test_sparsepy_methods():
    key_type = np.dtype('u8')
    value_type = np.int64

    sp_dict = sp.Dict(key_type, value_type)

    sp_dict[42] = 1337

    assert sp_dict[42] == 1337
    assert 42 in sp_dict
    assert 41 not in sp_dict
    assert len(sp_dict) == 1

    del sp_dict[42]

    assert 42 not in sp_dict
    assert 41 not in sp_dict
    assert len(sp_dict) == 0


@standard
def test_sparsepy_vectorized_methods():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    sp_dict = sp.Dict(key_type, value_type)

    keys = np.random.randint(1000, size=200, dtype=key_type)
    values = np.random.randint(1000, size=200, dtype=value_type)

    sp_dict[keys] = values

    keys = [key for key in sp_dict]
    keys_and_values = [(key, value) for key, value in sp_dict.items()]

    select_keys = np.random.choice(keys, size=100)
    select_values = sp_dict[select_keys]

    random_keys = np.random.randint(1000, size=500, dtype=key_type)
    random_keys_mask = sp_dict.__contains__(random_keys)

    mask_keys = random_keys[random_keys_mask]
    mask_values = sp_dict[mask_keys]


@standard
@pytest.mark.timeout(1)
def test_sparsepy_dump_load():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    sp_dict_1 = sp.Dict(key_type, value_type)

    keys = np.random.randint(1000, size=10, dtype=key_type)
    values = np.random.randint(1000, size=10, dtype=value_type)
    sp_dict_1[keys] = values

    sp_dict_1.dump('test/test.hashtable.bin')

    sp_dict_2 = sp.Dict(key_type, value_type)
    sp_dict_2.load('test/test.hashtable.bin')

    assert sp_dict_1 == sp_dict_2


@standard
def test_sparsepy_types():
    for key_type, value_type in sp._types:
        sp_dict = sp.Dict(key_type, value_type)

        keys = np.array(range(10), dtype=np.dtype(key_type))
        values = np.array(range(10), dtype=np.dtype(value_type))

        sp_dict[keys] = values


# @standard
# @pytest.mark.timeout(1)
# def test_sparsepy_big_dict_uint32():
#     key_type = np.dtype('u4')
#     value_type = np.dtype('u4')
#
#     sp_dict = sp.Dict(key_type, value_type)
#
#     for i in range(10**3):
#         keys = np.random.randint(10**9, size=10**3, dtype=key_type)
#         values = np.random.randint(10**9, size=10**3, dtype=value_type)
#
#         sp_dict[keys] = values


@standard
@pytest.mark.timeout(1)
def test_sparsepy_big_dict_uint64():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    sp_dict = sp.Dict(key_type, value_type)

    for i in range(10**3):
        keys = np.random.randint(10**15, size=10**3, dtype=key_type)
        values = np.random.randint(10**15, size=10**3, dtype=value_type)

        sp_dict[keys] = values


# @long_
# @pytest.mark.timeout(100)
# def test_sparsepy_very_big_dict_uint32():
#     key_type = np.dtype('u4')
#     value_type = np.dtype('u4')
#
#     sp_dict = sp.Dict(key_type, value_type)
#
#     for i in range(10**3):
#         keys = np.random.randint(10**9, size=10**5, dtype=key_type)
#         values = np.random.randint(10**9, size=10**5, dtype=value_type)
#
#         sp_dict[keys] = values


@long_
@pytest.mark.timeout(100)
def test_sparsepy_very_big_dict_uint64():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    sp_dict = sp.Dict(key_type, value_type)

    for i in range(10**3):
        keys = np.random.randint(10**15, size=10**5, dtype=key_type)
        values = np.random.randint(10**15, size=10**5, dtype=value_type)

        sp_dict[keys] = values
