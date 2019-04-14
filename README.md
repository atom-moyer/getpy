# GetPy - A Simple, Fast and Small Hash Map for Scientific Python

The goal of GetPy (gp) is a simple to use and high performance python dictionary which integrates smoothly into the NumPy/SciPy ecosystem.

## Installation
`pip install git+https://github.com/atom-moyer/getpy.git`

## About
GetPy is a thin and robust binding to The Parallel Hashmap (https://github.com/greg7mdp/parallel-hashmap.git) which is the current state of the art for minimal memory overhead and fast runtime speed. The binding layer is supported by PyBind11 (https://github.com/pybind/pybind11.git) which is fast to compile and simple to extend. Serialization is handled by Cereal (https://github.com/USCiLab/cereal.git) which supports streaming binary serialization, a critical feature for the large hash tables this is designed to support.

## How To Use
The `gp.Dict` object is designed to maintain a similar interface to the standard python dictionary. There are some key differences though, which are necessary for performance reasons.

1) `gp.Dict.__init__` has two arguments `key_type` and `value_type`. Those arguments are defined with a preset combinations of `np.dtype`s.  The full list of supported `np.dtype` combinations is found by `gp.types`. Most of the future work on sparsepy will be expanding this list of supported types.

2) All of `getpy.Dict` methods support vectorization. Therefore, methods like `gp.Dict.__getitem__`, `gp.Dict.__setitem__`, and `gp.Dict.__contains__` can be performed with `np.ndarray`.  That allows the performance critical for-loop to happen within the compiled c++.

3) `gp.Dict.__getitem__` will throw an error if you attempt to retrieve a key that does not exist. Instead, you should first run `gp.__contains__` on your key/array of keys, and then retrieve values corresponding to keys that exist. This is necessary for the vectorization support.

## Examples

### Simple Example
```python
import numpy as np
import getpy as gp

key_type = np.dtype('u8')
value_type = np.int64

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
```

### Vectorized Example
```python
import numpy as np
import getpy as gp

key_type = np.dtype('u8')
value_type = np.int64

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
```

### Serialization Example
```python
import numpy as np
import getpy as gp

key_type = np.dtype('u8')
value_type = np.int64

gp_dict_1 = sp.Dict(key_type, value_type)

keys = np.random.randint(1000, size=10, dtype=key_type)
values = np.random.randint(1000, size=10, dtype=value_type)
gp_dict_1[keys] = values

gp_dict_1.dump('test/test.hashtable.bin')

gp_dict_2 = gp.Dict(key_type, value_type)
gp_dict_2.load('test/test.hashtable.bin')

assert gp_dict_1 == gp_dict_2
```

## Supported Data Types

```python
key_types = [
    'str4',
    'str8',

    'uint32',
    'uint64',

    'int32',
    'int64',
]

value_types = [
    'str1',
    'str2',
    'str4',
    'str8',
    'str16',
    'str32',

    'uint8',
    'uint16',
    'uint32',
    'uint64',

    'int8',
    'int16',
    'int32',
    'int64',

    'float32',
    'float64',

    'bool',
]

cpp_types = {
    'str1' : 'std::array<char, 1>',
    'str2' : 'std::array<char, 2>',
    'str4' : 'std::array<char, 4>',
    'str8' : 'std::array<char, 8>',
    'str16' : 'std::array<char, 16>',
    'str32' : 'std::array<char, 32>',

    'int8' : 'int8_t',
    'int16' : 'int16_t',
    'int32' : 'int32_t',
    'int64' : 'int64_t',

    'uint8' : 'uint8_t',
    'uint16' : 'uint16_t',
    'uint32' : 'uint32_t',
    'uint64' : 'uint64_t',

    'float32' : 'float',
    'float64' : 'double',

    'bool' : 'bool',
}

np_types = {
    'str1' : ['U1'],
    'str2' : ['U2'],
    'str4' : ['U4'],
    'str8' : ['U8'],
    'str16' : ['U16'],
    'str32' : ['U32'],

    'int8' : ['i1', 'int8'],
    'int16' : ['i2', 'int16'],
    'int32' : ['i4', 'int32'],
    'int64' : ['i8', 'int64'],

    'uint8' : ['u1', 'uint8'],
    'uint16' : ['u2', 'uint16'],
    'uint32' : ['u4', 'uint32'],
    'uint64' : ['u8', 'uint64'],

    'float32' : ['f4', 'float32'],
    'float64' : ['f8', 'float64'],

    'bool' : ['?', 'bool'],
}
```
