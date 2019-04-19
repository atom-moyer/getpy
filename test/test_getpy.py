import pytest

import numpy as np

import getpy as gp

fast = pytest.mark.fast
standard = pytest.mark.standard
slow = pytest.mark.slow
very_slow = pytest.mark.very_slow


@standard
def test_getpy_methods():
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
def test_getpy_methods_custom_struct():
    key_type = np.dtype('u8')
    value_type = gp.types['rtarray20_uint8']

    gp_dict = gp.Dict(key_type, value_type)

    value = np.array([(1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
                       1, 0, 1, 0, 1, 0, 1, 0, 1, 0)], dtype=value_type)

    assert value[0]['A'] == True
    assert value[0]['C'] == False

    gp_dict[42] = value

    assert gp_dict[42] == value
    assert 42 in gp_dict
    assert 41 not in gp_dict
    assert len(gp_dict) == 1

    del gp_dict[42]

    assert 42 not in gp_dict
    assert 41 not in gp_dict
    assert len(gp_dict) == 0


@standard
def test_getpy_methods_nested_custom_struct():
    key_type = np.dtype('u8')
    value_type = gp.types['rpmatrix400_uint8']

    gp_dict = gp.Dict(key_type, value_type)

    value = np.array([tuple([(1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
                              1, 0, 1, 0, 1, 0, 1, 0, 1, 0) for _ in range(20)])], dtype=value_type)

    assert value[0]['A']['A'] == True
    assert value[0]['A']['C'] == False

    gp_dict[42] = value

    assert gp_dict[42] == value
    assert 42 in gp_dict
    assert 41 not in gp_dict
    assert len(gp_dict) == 1

    del gp_dict[42]

    assert 42 not in gp_dict
    assert 41 not in gp_dict
    assert len(gp_dict) == 0


@standard
def test_getpy_vectorized_methods():
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
def test_getpy_vectorized_methods_custom_struct():
    key_type = np.dtype('u8')
    value_type = gp.types['rtarray20_uint8']

    gp_dict = gp.Dict(key_type, value_type)

    keys = np.random.randint(1000, size=200, dtype=key_type)
    values = np.array([(1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
                        1, 0, 1, 0, 1, 0, 1, 0, 1, 0) for _ in range(200)], dtype=value_type)

    gp_dict[keys] = values

    # keys = [key for key in gp_dict]
    # keys_and_values = [(key, value) for key, value in gp_dict.items()]

    select_keys = np.random.choice(keys, size=100)
    select_values = gp_dict[select_keys]

    random_keys = np.random.randint(1000, size=500, dtype=key_type)
    random_keys_mask = gp_dict.__contains__(random_keys)

    mask_keys = random_keys[random_keys_mask]
    mask_values = gp_dict[mask_keys]


@standard
def test_getpy_vectorized_methods_nested_custom_struct():
    key_type = np.dtype('u8')
    value_type = gp.types['rpmatrix400_uint8']

    gp_dict = gp.Dict(key_type, value_type)

    keys = np.random.randint(1000, size=200, dtype=key_type)
    values = np.array([tuple([(1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
                               1, 0, 1, 0, 1, 0, 1, 0, 1, 0) for _ in range(20)]) for i in range(200)], dtype=value_type)

    gp_dict[keys] = values

    # keys = [key for key in gp_dict]
    # keys_and_values = [(key, value) for key, value in gp_dict.items()]

    select_keys = np.random.choice(keys, size=100)
    select_values = gp_dict[select_keys]

    random_keys = np.random.randint(1000, size=500, dtype=key_type)
    random_keys_mask = gp_dict.__contains__(random_keys)

    mask_keys = random_keys[random_keys_mask]
    mask_values = gp_dict[mask_keys]


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

    keys = np.random.randint(1000, size=10, dtype=key_type)
    values = np.random.randint(1000, size=10, dtype=value_type)
    gp_dict_1[keys] = values

    gp_dict_1.dump('test/test.hashtable.bin')

    gp_dict_2 = gp.Dict(key_type, value_type)
    gp_dict_2.load('test/test.hashtable.bin')

    assert gp_dict_1 == gp_dict_2


@standard
@pytest.mark.timeout(3)
def test_getpy_big_dict_uint32_uint32():
    key_type = np.dtype('u4')
    value_type = np.dtype('u4')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**9, size=10**3, dtype=value_type)

    for i in range(10**4):
        keys = np.random.randint(10**9, size=10**3, dtype=key_type)
        gp_dict[keys] = values


@standard
@pytest.mark.timeout(3)
def test_getpy_big_dict_uint64_uint64():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    values = np.random.randint(10**15, size=10**3, dtype=value_type)

    for i in range(10**4):
        keys = np.random.randint(10**15, size=10**3, dtype=key_type)
        gp_dict[keys] = values


@standard
@pytest.mark.timeout(6)
def test_getpy_big_dict_uint64_rtarray20_uint8():
    key_type = np.dtype('u8')
    value_type = gp.types['rtarray20_uint8']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.array([(1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
                        1, 0, 1, 0, 1, 0, 1, 0, 1, 0) for _ in range(10**3)], dtype=value_type)

    for i in range(10**4):
        keys = np.random.randint(10**15, size=10**3, dtype=key_type)
        gp_dict[keys] = values


@standard
@pytest.mark.timeout(20)
def test_getpy_big_dict_uint64_rpmatrix400_uint8():
    key_type = np.dtype('u8')
    value_type = gp.types['rpmatrix400_uint8']

    gp_dict = gp.Dict(key_type, value_type)

    values = np.array([tuple([(1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
                               1, 0, 1, 0, 1, 0, 1, 0, 1, 0) for _ in range(20)]) for i in range(10**3)], dtype=value_type)

    for i in range(10**4):
        keys = np.random.randint(10**15, size=10**3, dtype=key_type)
        gp_dict[keys] = values


@standard
@pytest.mark.timeout(1)
def test_getpy_big_dict_uint64_lookup():
    key_type = np.dtype('u8')
    value_type = np.dtype('u8')

    gp_dict = gp.Dict(key_type, value_type)

    keys = np.random.randint(10**15, size=10**4, dtype=key_type)
    values = np.random.randint(10**15, size=10**4, dtype=value_type)

    gp_dict[keys] = values

    for i in range(10**2):
        values = gp_dict[keys]


# @standard
# @pytest.mark.timeout(5)
# def test_getpy_very_big_dict_uint32_uint32():
#     key_type = np.dtype('u4')
#     value_type = np.dtype('u4')
#
#     gp_dict = gp.Dict(key_type, value_type)
#
#     values = np.random.randint(10**9, size=10**3, dtype=value_type)
#
#     for i in range(10**4):
#         keys = np.random.randint(10**9, size=10**3, dtype=key_type)
#         gp_dict[keys] = values
#
#
# @standard
# @pytest.mark.timeout(5)
# def test_getpy_very_big_dict_uint64_uint64():
#     key_type = np.dtype('u8')
#     value_type = np.dtype('u8')
#
#     gp_dict = gp.Dict(key_type, value_type)
#
#     values = np.random.randint(10**15, size=10**3, dtype=value_type)
#
#     for i in range(10**4):
#         keys = np.random.randint(10**15, size=10**3, dtype=key_type)
#         gp_dict[keys] = values
#
#
# @standard
# @pytest.mark.timeout(5)
# def test_getpy_very_big_dict_uint32_rtarray20_uint8():
#     key_type = np.dtype('u4')
#     value_type = gp.types['rtarray20_uint8']
#
#     gp_dict = gp.Dict(key_type, value_type)
#
#     values = np.array([(1, 0, 1, 0, 1, 0, 1, 0, 1, 0,
#                         1, 0, 1, 0, 1, 0, 1, 0, 1, 0) for _ in range(10**3)], dtype=value_type)
#
#     for i in range(10**4):
#         keys = np.random.randint(10**9, size=10**3, dtype=key_type)
#         gp_dict[keys] = values
#
#
# @slow
# @pytest.mark.timeout(30)
# def test_getpy_very_big_dict_uint32():
#     key_type = np.dtype('u4')
#     value_type = np.dtype('u4')
#
#     gp_dict = gp.Dict(key_type, value_type)
#
#     for i in range(10**3):
#         keys = np.random.randint(10**9, size=10**5, dtype=key_type)
#         values = np.random.randint(10**9, size=10**5, dtype=value_type)
#
#         gp_dict[keys] = values
#
#
# @slow
# @pytest.mark.timeout(30)
# def test_getpy_very_big_dict_uint64():
#     key_type = np.dtype('u8')
#     value_type = np.dtype('u8')
#
#     gp_dict = gp.Dict(key_type, value_type)
#
#     for i in range(10**3):
#         keys = np.random.randint(10**15, size=10**5, dtype=key_type)
#         values = np.random.randint(10**15, size=10**5, dtype=value_type)
#
#         gp_dict[keys] = values
#
#
# @very_slow
# @pytest.mark.timeout(300)
# def test_getpy_uber_big_dict_uint32():
#     key_type = np.dtype('u4')
#     value_type = np.dtype('u4')
#
#     gp_dict = gp.Dict(key_type, value_type)
#
#     for i in range(10**3):
#         keys = np.random.randint(10**9, size=10**6, dtype=key_type)
#         values = np.random.randint(10**9, size=10**6, dtype=value_type)
#
#         gp_dict[keys] = values
#
#
# @very_slow
# @pytest.mark.timeout(300)
# def test_getpy_uber_big_dict_uint64():
#     key_type = np.dtype('u8')
#     value_type = np.dtype('u8')
#
#     gp_dict = gp.Dict(key_type, value_type)
#
#     for i in range(10**3):
#         keys = np.random.randint(10**15, size=10**6, dtype=key_type)
#         values = np.random.randint(10**15, size=10**6, dtype=value_type)
#
#         gp_dict[keys] = values
#
#
# @slow
# @pytest.mark.timeout(5000)
# def test_getpy_extremely_big_dict_uint32():
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
# def test_getpy_extremely_big_dict_uint64():
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
