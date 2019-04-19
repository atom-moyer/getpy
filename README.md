# GetPy - A Simple, Fast, and Small Hash Map for Python

The goal of GetPy (gp) is to fill the need for a simple to use and high performance python dictionary which integrates smoothly into the NumPy/SciPy ecosystem.

## Installation
`pip install git+https://github.com/atom-moyer/getpy.git`

## About
GetPy is a thin and robust binding to The Parallel Hashmap (https://github.com/greg7mdp/parallel-hashmap.git) which is the current state of the art for minimal memory overhead and fast runtime speed. The binding layer is supported by PyBind11 (https://github.com/pybind/pybind11.git) which is fast to compile and simple to extend. Serialization is handled by Cereal (https://github.com/USCiLab/cereal.git) which supports streaming binary serialization, a critical feature for the large hash maps this package is designed to support.

## How To Use
The `gp.Dict` object is designed to maintain a similar interface to the standard python dictionary. There are some key differences though, which are necessary for performance reasons.

1) `gp.Dict.__init__` has two arguments `key_type` and `value_type`. Those arguments are defined with a preset combinations of `np.dtype`s.  The full list of supported type combinations is found at `gp.dict_types`. Most of the future work on sparsepy will be expanding this list of supported types.

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
types = {
    'str1' : np.dtype('U1'),
    'str2' : np.dtype('U2'),
    'str4' : np.dtype('U4'),
    'str8' : np.dtype('U8'),
    'str16' : np.dtype('U16'),
    'str32' : np.dtype('U32'),
    'uint8' : np.dtype('u1'),
    'uint16' : np.dtype('u2'),
    'uint32' : np.dtype('u4'),
    'uint64' : np.dtype('u8'),
    'int8' : np.dtype('i1'),
    'int16' : np.dtype('i2'),
    'int32' : np.dtype('i4'),
    'int64' : np.dtype('i8'),
    'float32' : np.dtype('f4'),
    'float64' : np.dtype('f8'),
    'bool' : np.dtype('?'),
    'pair_str1_str1' : np.dtype({'names': ['first', 'second'], 'formats': ['U1', 'U1']}),
    'pair_str2_str2' : np.dtype({'names': ['first', 'second'], 'formats': ['U2', 'U2']}),
    'pair_str4_str4' : np.dtype({'names': ['first', 'second'], 'formats': ['U4', 'U4']}),
    'pair_str8_str8' : np.dtype({'names': ['first', 'second'], 'formats': ['U8', 'U8']}),
    'pair_str16_str16' : np.dtype({'names': ['first', 'second'], 'formats': ['U16', 'U16']}),
    'pair_str32_str32' : np.dtype({'names': ['first', 'second'], 'formats': ['U32', 'U32']}),
    'pair_uint8_uint8' : np.dtype({'names': ['first', 'second'], 'formats': ['u1', 'u1']}),
    'pair_uint16_uint16' : np.dtype({'names': ['first', 'second'], 'formats': ['u2', 'u2']}),
    'pair_uint32_uint32' : np.dtype({'names': ['first', 'second'], 'formats': ['u4', 'u4']}),
    'pair_uint64_uint64' : np.dtype({'names': ['first', 'second'], 'formats': ['u8', 'u8']}),
    'pair_int8_int8' : np.dtype({'names': ['first', 'second'], 'formats': ['i1', 'i1']}),
    'pair_int16_int16' : np.dtype({'names': ['first', 'second'], 'formats': ['i2', 'i2']}),
    'pair_int32_int32' : np.dtype({'names': ['first', 'second'], 'formats': ['i4', 'i4']}),
    'pair_int64_int64' : np.dtype({'names': ['first', 'second'], 'formats': ['i8', 'i8']}),
    'pair_float32_float32' : np.dtype({'names': ['first', 'second'], 'formats': ['f4', 'f4']}),
    'pair_float64_float64' : np.dtype({'names': ['first', 'second'], 'formats': ['f8', 'f8']}),
}

dict_types = {
    (types['str4'], types['str1']) : _gp.Dict_str4_str1,
    (types['str4'], types['str2']) : _gp.Dict_str4_str2,
    (types['str4'], types['str4']) : _gp.Dict_str4_str4,
    (types['str4'], types['str8']) : _gp.Dict_str4_str8,
    (types['str4'], types['str16']) : _gp.Dict_str4_str16,
    (types['str4'], types['str32']) : _gp.Dict_str4_str32,
    (types['str4'], types['uint8']) : _gp.Dict_str4_uint8,
    (types['str4'], types['uint16']) : _gp.Dict_str4_uint16,
    (types['str4'], types['uint32']) : _gp.Dict_str4_uint32,
    (types['str4'], types['uint64']) : _gp.Dict_str4_uint64,
    (types['str4'], types['int8']) : _gp.Dict_str4_int8,
    (types['str4'], types['int16']) : _gp.Dict_str4_int16,
    (types['str4'], types['int32']) : _gp.Dict_str4_int32,
    (types['str4'], types['int64']) : _gp.Dict_str4_int64,
    (types['str4'], types['float32']) : _gp.Dict_str4_float32,
    (types['str4'], types['float64']) : _gp.Dict_str4_float64,
    (types['str4'], types['bool']) : _gp.Dict_str4_bool,
    (types['str4'], types['pair_str1_str1']) : _gp.Dict_str4_pair_str1_str1,
    (types['str4'], types['pair_str2_str2']) : _gp.Dict_str4_pair_str2_str2,
    (types['str4'], types['pair_str4_str4']) : _gp.Dict_str4_pair_str4_str4,
    (types['str4'], types['pair_str8_str8']) : _gp.Dict_str4_pair_str8_str8,
    (types['str4'], types['pair_str16_str16']) : _gp.Dict_str4_pair_str16_str16,
    (types['str4'], types['pair_str32_str32']) : _gp.Dict_str4_pair_str32_str32,
    (types['str4'], types['pair_uint8_uint8']) : _gp.Dict_str4_pair_uint8_uint8,
    (types['str4'], types['pair_uint16_uint16']) : _gp.Dict_str4_pair_uint16_uint16,
    (types['str4'], types['pair_uint32_uint32']) : _gp.Dict_str4_pair_uint32_uint32,
    (types['str4'], types['pair_uint64_uint64']) : _gp.Dict_str4_pair_uint64_uint64,
    (types['str4'], types['pair_int8_int8']) : _gp.Dict_str4_pair_int8_int8,
    (types['str4'], types['pair_int16_int16']) : _gp.Dict_str4_pair_int16_int16,
    (types['str4'], types['pair_int32_int32']) : _gp.Dict_str4_pair_int32_int32,
    (types['str4'], types['pair_int64_int64']) : _gp.Dict_str4_pair_int64_int64,
    (types['str4'], types['pair_float32_float32']) : _gp.Dict_str4_pair_float32_float32,
    (types['str4'], types['pair_float64_float64']) : _gp.Dict_str4_pair_float64_float64,
    (types['str4'], types['rtarray20_uint8']) : _gp.Dict_str4_rtarray20_uint8,
    (types['str4'], types['rpmatrix400_uint8']) : _gp.Dict_str4_rpmatrix400_uint8,
    (types['str8'], types['str1']) : _gp.Dict_str8_str1,
    (types['str8'], types['str2']) : _gp.Dict_str8_str2,
    (types['str8'], types['str4']) : _gp.Dict_str8_str4,
    (types['str8'], types['str8']) : _gp.Dict_str8_str8,
    (types['str8'], types['str16']) : _gp.Dict_str8_str16,
    (types['str8'], types['str32']) : _gp.Dict_str8_str32,
    (types['str8'], types['uint8']) : _gp.Dict_str8_uint8,
    (types['str8'], types['uint16']) : _gp.Dict_str8_uint16,
    (types['str8'], types['uint32']) : _gp.Dict_str8_uint32,
    (types['str8'], types['uint64']) : _gp.Dict_str8_uint64,
    (types['str8'], types['int8']) : _gp.Dict_str8_int8,
    (types['str8'], types['int16']) : _gp.Dict_str8_int16,
    (types['str8'], types['int32']) : _gp.Dict_str8_int32,
    (types['str8'], types['int64']) : _gp.Dict_str8_int64,
    (types['str8'], types['float32']) : _gp.Dict_str8_float32,
    (types['str8'], types['float64']) : _gp.Dict_str8_float64,
    (types['str8'], types['bool']) : _gp.Dict_str8_bool,
    (types['str8'], types['pair_str1_str1']) : _gp.Dict_str8_pair_str1_str1,
    (types['str8'], types['pair_str2_str2']) : _gp.Dict_str8_pair_str2_str2,
    (types['str8'], types['pair_str4_str4']) : _gp.Dict_str8_pair_str4_str4,
    (types['str8'], types['pair_str8_str8']) : _gp.Dict_str8_pair_str8_str8,
    (types['str8'], types['pair_str16_str16']) : _gp.Dict_str8_pair_str16_str16,
    (types['str8'], types['pair_str32_str32']) : _gp.Dict_str8_pair_str32_str32,
    (types['str8'], types['pair_uint8_uint8']) : _gp.Dict_str8_pair_uint8_uint8,
    (types['str8'], types['pair_uint16_uint16']) : _gp.Dict_str8_pair_uint16_uint16,
    (types['str8'], types['pair_uint32_uint32']) : _gp.Dict_str8_pair_uint32_uint32,
    (types['str8'], types['pair_uint64_uint64']) : _gp.Dict_str8_pair_uint64_uint64,
    (types['str8'], types['pair_int8_int8']) : _gp.Dict_str8_pair_int8_int8,
    (types['str8'], types['pair_int16_int16']) : _gp.Dict_str8_pair_int16_int16,
    (types['str8'], types['pair_int32_int32']) : _gp.Dict_str8_pair_int32_int32,
    (types['str8'], types['pair_int64_int64']) : _gp.Dict_str8_pair_int64_int64,
    (types['str8'], types['pair_float32_float32']) : _gp.Dict_str8_pair_float32_float32,
    (types['str8'], types['pair_float64_float64']) : _gp.Dict_str8_pair_float64_float64,
    (types['str8'], types['rtarray20_uint8']) : _gp.Dict_str8_rtarray20_uint8,
    (types['str8'], types['rpmatrix400_uint8']) : _gp.Dict_str8_rpmatrix400_uint8,
    (types['uint32'], types['str1']) : _gp.Dict_uint32_str1,
    (types['uint32'], types['str2']) : _gp.Dict_uint32_str2,
    (types['uint32'], types['str4']) : _gp.Dict_uint32_str4,
    (types['uint32'], types['str8']) : _gp.Dict_uint32_str8,
    (types['uint32'], types['str16']) : _gp.Dict_uint32_str16,
    (types['uint32'], types['str32']) : _gp.Dict_uint32_str32,
    (types['uint32'], types['uint8']) : _gp.Dict_uint32_uint8,
    (types['uint32'], types['uint16']) : _gp.Dict_uint32_uint16,
    (types['uint32'], types['uint32']) : _gp.Dict_uint32_uint32,
    (types['uint32'], types['uint64']) : _gp.Dict_uint32_uint64,
    (types['uint32'], types['int8']) : _gp.Dict_uint32_int8,
    (types['uint32'], types['int16']) : _gp.Dict_uint32_int16,
    (types['uint32'], types['int32']) : _gp.Dict_uint32_int32,
    (types['uint32'], types['int64']) : _gp.Dict_uint32_int64,
    (types['uint32'], types['float32']) : _gp.Dict_uint32_float32,
    (types['uint32'], types['float64']) : _gp.Dict_uint32_float64,
    (types['uint32'], types['bool']) : _gp.Dict_uint32_bool,
    (types['uint32'], types['pair_str1_str1']) : _gp.Dict_uint32_pair_str1_str1,
    (types['uint32'], types['pair_str2_str2']) : _gp.Dict_uint32_pair_str2_str2,
    (types['uint32'], types['pair_str4_str4']) : _gp.Dict_uint32_pair_str4_str4,
    (types['uint32'], types['pair_str8_str8']) : _gp.Dict_uint32_pair_str8_str8,
    (types['uint32'], types['pair_str16_str16']) : _gp.Dict_uint32_pair_str16_str16,
    (types['uint32'], types['pair_str32_str32']) : _gp.Dict_uint32_pair_str32_str32,
    (types['uint32'], types['pair_uint8_uint8']) : _gp.Dict_uint32_pair_uint8_uint8,
    (types['uint32'], types['pair_uint16_uint16']) : _gp.Dict_uint32_pair_uint16_uint16,
    (types['uint32'], types['pair_uint32_uint32']) : _gp.Dict_uint32_pair_uint32_uint32,
    (types['uint32'], types['pair_uint64_uint64']) : _gp.Dict_uint32_pair_uint64_uint64,
    (types['uint32'], types['pair_int8_int8']) : _gp.Dict_uint32_pair_int8_int8,
    (types['uint32'], types['pair_int16_int16']) : _gp.Dict_uint32_pair_int16_int16,
    (types['uint32'], types['pair_int32_int32']) : _gp.Dict_uint32_pair_int32_int32,
    (types['uint32'], types['pair_int64_int64']) : _gp.Dict_uint32_pair_int64_int64,
    (types['uint32'], types['pair_float32_float32']) : _gp.Dict_uint32_pair_float32_float32,
    (types['uint32'], types['pair_float64_float64']) : _gp.Dict_uint32_pair_float64_float64,
    (types['uint32'], types['rtarray20_uint8']) : _gp.Dict_uint32_rtarray20_uint8,
    (types['uint32'], types['rpmatrix400_uint8']) : _gp.Dict_uint32_rpmatrix400_uint8,
    (types['uint64'], types['str1']) : _gp.Dict_uint64_str1,
    (types['uint64'], types['str2']) : _gp.Dict_uint64_str2,
    (types['uint64'], types['str4']) : _gp.Dict_uint64_str4,
    (types['uint64'], types['str8']) : _gp.Dict_uint64_str8,
    (types['uint64'], types['str16']) : _gp.Dict_uint64_str16,
    (types['uint64'], types['str32']) : _gp.Dict_uint64_str32,
    (types['uint64'], types['uint8']) : _gp.Dict_uint64_uint8,
    (types['uint64'], types['uint16']) : _gp.Dict_uint64_uint16,
    (types['uint64'], types['uint32']) : _gp.Dict_uint64_uint32,
    (types['uint64'], types['uint64']) : _gp.Dict_uint64_uint64,
    (types['uint64'], types['int8']) : _gp.Dict_uint64_int8,
    (types['uint64'], types['int16']) : _gp.Dict_uint64_int16,
    (types['uint64'], types['int32']) : _gp.Dict_uint64_int32,
    (types['uint64'], types['int64']) : _gp.Dict_uint64_int64,
    (types['uint64'], types['float32']) : _gp.Dict_uint64_float32,
    (types['uint64'], types['float64']) : _gp.Dict_uint64_float64,
    (types['uint64'], types['bool']) : _gp.Dict_uint64_bool,
    (types['uint64'], types['pair_str1_str1']) : _gp.Dict_uint64_pair_str1_str1,
    (types['uint64'], types['pair_str2_str2']) : _gp.Dict_uint64_pair_str2_str2,
    (types['uint64'], types['pair_str4_str4']) : _gp.Dict_uint64_pair_str4_str4,
    (types['uint64'], types['pair_str8_str8']) : _gp.Dict_uint64_pair_str8_str8,
    (types['uint64'], types['pair_str16_str16']) : _gp.Dict_uint64_pair_str16_str16,
    (types['uint64'], types['pair_str32_str32']) : _gp.Dict_uint64_pair_str32_str32,
    (types['uint64'], types['pair_uint8_uint8']) : _gp.Dict_uint64_pair_uint8_uint8,
    (types['uint64'], types['pair_uint16_uint16']) : _gp.Dict_uint64_pair_uint16_uint16,
    (types['uint64'], types['pair_uint32_uint32']) : _gp.Dict_uint64_pair_uint32_uint32,
    (types['uint64'], types['pair_uint64_uint64']) : _gp.Dict_uint64_pair_uint64_uint64,
    (types['uint64'], types['pair_int8_int8']) : _gp.Dict_uint64_pair_int8_int8,
    (types['uint64'], types['pair_int16_int16']) : _gp.Dict_uint64_pair_int16_int16,
    (types['uint64'], types['pair_int32_int32']) : _gp.Dict_uint64_pair_int32_int32,
    (types['uint64'], types['pair_int64_int64']) : _gp.Dict_uint64_pair_int64_int64,
    (types['uint64'], types['pair_float32_float32']) : _gp.Dict_uint64_pair_float32_float32,
    (types['uint64'], types['pair_float64_float64']) : _gp.Dict_uint64_pair_float64_float64,
    (types['uint64'], types['rtarray20_uint8']) : _gp.Dict_uint64_rtarray20_uint8,
    (types['uint64'], types['rpmatrix400_uint8']) : _gp.Dict_uint64_rpmatrix400_uint8,
}
```
