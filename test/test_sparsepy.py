import numpy as np


def test_sparsepy_basic():
    import sparsepy as sp
    sp_dict = sp.Dict(np.dtype('i8'), np.dtype('i8'))


def test_sparsepy_types():
    import sparsepy as sp
    for key_type, value_type in sp._types:
        sp_dict = sp.Dict(key_type, value_type)


def test_sparsepy_methods():
    import sparsepy as sp
    sp_dict = sp.Dict(np.dtype('i8'), np.dtype('i8'))

    sp_dict[42] = 1337

    assert sp_dict[42] == 1337
    assert 42 in sp_dict
    assert 41 not in sp_dict
    assert len(sp_dict) == 1

    del sp_dict[42]

    assert 42 not in sp_dict
    assert 41 not in sp_dict
    assert len(sp_dict) == 0


def test_sparsepy_vectorized_methods():
    import sparsepy as sp
    sp_dict = sp.Dict(np.dtype('i8'), np.dtype('i8'))

    keys = np.random.randint(1000, size=200, dtype=np.int64)
    values = np.random.randint(1000, size=200, dtype=np.int64)

    sp_dict[keys] = values

    key_and_values = [(key, value) for key, value in sp_dict]

    select_keys = np.random.choice(keys, size=100)
    select_values = sp_dict[select_keys]

    random_keys = np.random.randint(1000, size=500, dtype=np.int64)
    random_keys_mask = sp_dict.__contains__(random_keys)

    mask_keys = random_keys[random_keys_mask]
    mask_values = sp_dict[mask_keys]
