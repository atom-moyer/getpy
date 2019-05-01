# GetPy - A Simple, Fast, and Small Hash Map for Python

The goal of GetPy is filling the need for high performance python dictionary that integrates into the NumPy ecosystem.

## Installation
`pip install git+https://github.com/atom-moyer/getpy.git`

## About
GetPy is a thin and robust binding to The Parallel Hashmap (https://github.com/greg7mdp/parallel-hashmap.git) which is the current state of the art for minimal memory overhead and fast runtime speed. The binding layer is supported by PyBind11 (https://github.com/pybind/pybind11.git) which is fast to compile and simple to extend. Serialization is handled by Cereal (https://github.com/USCiLab/cereal.git) which supports streaming binary serialization, a critical feature for the large hash maps this package is designed to support.

## How To Use
The `gp.Dict` object is designed to maintain a similar interface to the standard python dictionary. There are some key differences though, which are necessary for performance reasons.

1) `gp.Dict.__init__` has three arguments `key_type`, `value_type`, and `default_value`. The type arguments are define which compiled data structure will be used under the hood, and the full list of preset combinations of `np.dtype`s is found with `gp.dict_types`. Most of the future work on sparsepy will be expanding this list of supported types. You can also specify a `default_value` at construction which must be castable to the `value_type`. This is the value returned by the dictionary if a key is not found.

2) All of `getpy.Dict` methods only support a vectorized interface. Therefore, methods like `gp.Dict.__getitem__`, `gp.Dict.__setitem__`, and `gp.Dict.__delitem__` must be performed with an `np.ndarray`.  That allows the performance critical for-loop to happen within the compiled c++. If you arguments are not `np.ndarray`s or their `dtype` does not match the defined `dtype` of the dict, you will be thrown a type error. GetPy will never implicitly cast any arguments. Note that some dunder methods cannot be vectorized such as `__contains__`. Therefore, some keywords like `in` do not behave as expected. Those methods are renamed without the double underscores to note their deviation from the standard interface.

3) `gp.Dict.__getitem__` will throw an error if you attempt to retrieve a key that does not exist, and you have not specified a `default_value` at construction. Instead, you should first run `gp.contains` on your key/array of keys, and then retrieve values corresponding to keys that exist. This is necessary for the vectorization support.

## Examples

### Simple Example
```python
import numpy as np
import getpy as gp

key_type = np.dtype('u8')
value_type = np.dtype('u8')

gp_dict = gp.Dict(key_type, value_type)

keys = np.random.randint(1, 1000, size=200, dtype=key_type)
values = np.random.randint(1, 1000, size=200, dtype=value_type)

gp_dict[keys] = values

iterated_keys = [key for key in gp_dict]
iterated_keys_and_values = [(key, value) for key, value in gp_dict.items()]

select_keys = np.random.choice(keys, size=100).astype(key_type)
select_values = gp_dict[select_keys]

random_keys = np.random.randint(1, 1000, size=500).astype(key_type)
random_keys_mask = gp_dict.contains(random_keys)

mask_keys = random_keys[random_keys_mask]
mask_values = gp_dict[mask_keys]
```

### Simple Example With Default Value
```python
import numpy as np
import getpy as gp

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
```

### Complex Example With Structured dtype
```python
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
    'bytearray2' : np.dtype({'names': ['bytearray'], 'formats': ['2u1']}),
    'bytearray4' : np.dtype({'names': ['bytearray'], 'formats': ['4u1']}),
    'bytearray8' : np.dtype({'names': ['bytearray'], 'formats': ['8u1']}),
    'bytearray10' : np.dtype({'names': ['bytearray'], 'formats': ['10u1']}),
    'bytearray16' : np.dtype({'names': ['bytearray'], 'formats': ['16u1']}),
    'bytearray20' : np.dtype({'names': ['bytearray'], 'formats': ['20u1']}),
    'bytearray30' : np.dtype({'names': ['bytearray'], 'formats': ['30u1']}),
    'bytearray32' : np.dtype({'names': ['bytearray'], 'formats': ['32u1']}),
    'bytearray40' : np.dtype({'names': ['bytearray'], 'formats': ['40u1']}),
    'bytearray50' : np.dtype({'names': ['bytearray'], 'formats': ['50u1']}),
}

dict_types = {
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
    (types['str4'], types['bytearray2']) : _gp.Dict_str4_bytearray2,
    (types['str4'], types['bytearray4']) : _gp.Dict_str4_bytearray4,
    (types['str4'], types['bytearray8']) : _gp.Dict_str4_bytearray8,
    (types['str4'], types['bytearray10']) : _gp.Dict_str4_bytearray10,
    (types['str4'], types['bytearray16']) : _gp.Dict_str4_bytearray16,
    (types['str4'], types['bytearray20']) : _gp.Dict_str4_bytearray20,
    (types['str4'], types['bytearray30']) : _gp.Dict_str4_bytearray30,
    (types['str4'], types['bytearray32']) : _gp.Dict_str4_bytearray32,
    (types['str4'], types['bytearray40']) : _gp.Dict_str4_bytearray40,
    (types['str4'], types['bytearray50']) : _gp.Dict_str4_bytearray50,
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
    (types['str8'], types['bytearray2']) : _gp.Dict_str8_bytearray2,
    (types['str8'], types['bytearray4']) : _gp.Dict_str8_bytearray4,
    (types['str8'], types['bytearray8']) : _gp.Dict_str8_bytearray8,
    (types['str8'], types['bytearray10']) : _gp.Dict_str8_bytearray10,
    (types['str8'], types['bytearray16']) : _gp.Dict_str8_bytearray16,
    (types['str8'], types['bytearray20']) : _gp.Dict_str8_bytearray20,
    (types['str8'], types['bytearray30']) : _gp.Dict_str8_bytearray30,
    (types['str8'], types['bytearray32']) : _gp.Dict_str8_bytearray32,
    (types['str8'], types['bytearray40']) : _gp.Dict_str8_bytearray40,
    (types['str8'], types['bytearray50']) : _gp.Dict_str8_bytearray50,
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
    (types['uint32'], types['bytearray2']) : _gp.Dict_uint32_bytearray2,
    (types['uint32'], types['bytearray4']) : _gp.Dict_uint32_bytearray4,
    (types['uint32'], types['bytearray8']) : _gp.Dict_uint32_bytearray8,
    (types['uint32'], types['bytearray10']) : _gp.Dict_uint32_bytearray10,
    (types['uint32'], types['bytearray16']) : _gp.Dict_uint32_bytearray16,
    (types['uint32'], types['bytearray20']) : _gp.Dict_uint32_bytearray20,
    (types['uint32'], types['bytearray30']) : _gp.Dict_uint32_bytearray30,
    (types['uint32'], types['bytearray32']) : _gp.Dict_uint32_bytearray32,
    (types['uint32'], types['bytearray40']) : _gp.Dict_uint32_bytearray40,
    (types['uint32'], types['bytearray50']) : _gp.Dict_uint32_bytearray50,
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
    (types['uint64'], types['bytearray2']) : _gp.Dict_uint64_bytearray2,
    (types['uint64'], types['bytearray4']) : _gp.Dict_uint64_bytearray4,
    (types['uint64'], types['bytearray8']) : _gp.Dict_uint64_bytearray8,
    (types['uint64'], types['bytearray10']) : _gp.Dict_uint64_bytearray10,
    (types['uint64'], types['bytearray16']) : _gp.Dict_uint64_bytearray16,
    (types['uint64'], types['bytearray20']) : _gp.Dict_uint64_bytearray20,
    (types['uint64'], types['bytearray30']) : _gp.Dict_uint64_bytearray30,
    (types['uint64'], types['bytearray32']) : _gp.Dict_uint64_bytearray32,
    (types['uint64'], types['bytearray40']) : _gp.Dict_uint64_bytearray40,
    (types['uint64'], types['bytearray50']) : _gp.Dict_uint64_bytearray50,
    (types['int32'], types['str4']) : _gp.Dict_int32_str4,
    (types['int32'], types['str8']) : _gp.Dict_int32_str8,
    (types['int32'], types['str16']) : _gp.Dict_int32_str16,
    (types['int32'], types['str32']) : _gp.Dict_int32_str32,
    (types['int32'], types['uint8']) : _gp.Dict_int32_uint8,
    (types['int32'], types['uint16']) : _gp.Dict_int32_uint16,
    (types['int32'], types['uint32']) : _gp.Dict_int32_uint32,
    (types['int32'], types['uint64']) : _gp.Dict_int32_uint64,
    (types['int32'], types['int8']) : _gp.Dict_int32_int8,
    (types['int32'], types['int16']) : _gp.Dict_int32_int16,
    (types['int32'], types['int32']) : _gp.Dict_int32_int32,
    (types['int32'], types['int64']) : _gp.Dict_int32_int64,
    (types['int32'], types['float32']) : _gp.Dict_int32_float32,
    (types['int32'], types['float64']) : _gp.Dict_int32_float64,
    (types['int32'], types['pair_str4_str4']) : _gp.Dict_int32_pair_str4_str4,
    (types['int32'], types['pair_str8_str8']) : _gp.Dict_int32_pair_str8_str8,
    (types['int32'], types['pair_str16_str16']) : _gp.Dict_int32_pair_str16_str16,
    (types['int32'], types['pair_str32_str32']) : _gp.Dict_int32_pair_str32_str32,
    (types['int32'], types['pair_uint8_uint8']) : _gp.Dict_int32_pair_uint8_uint8,
    (types['int32'], types['pair_uint16_uint16']) : _gp.Dict_int32_pair_uint16_uint16,
    (types['int32'], types['pair_uint32_uint32']) : _gp.Dict_int32_pair_uint32_uint32,
    (types['int32'], types['pair_uint64_uint64']) : _gp.Dict_int32_pair_uint64_uint64,
    (types['int32'], types['pair_int8_int8']) : _gp.Dict_int32_pair_int8_int8,
    (types['int32'], types['pair_int16_int16']) : _gp.Dict_int32_pair_int16_int16,
    (types['int32'], types['pair_int32_int32']) : _gp.Dict_int32_pair_int32_int32,
    (types['int32'], types['pair_int64_int64']) : _gp.Dict_int32_pair_int64_int64,
    (types['int32'], types['pair_float32_float32']) : _gp.Dict_int32_pair_float32_float32,
    (types['int32'], types['pair_float64_float64']) : _gp.Dict_int32_pair_float64_float64,
    (types['int32'], types['bytearray2']) : _gp.Dict_int32_bytearray2,
    (types['int32'], types['bytearray4']) : _gp.Dict_int32_bytearray4,
    (types['int32'], types['bytearray8']) : _gp.Dict_int32_bytearray8,
    (types['int32'], types['bytearray10']) : _gp.Dict_int32_bytearray10,
    (types['int32'], types['bytearray16']) : _gp.Dict_int32_bytearray16,
    (types['int32'], types['bytearray20']) : _gp.Dict_int32_bytearray20,
    (types['int32'], types['bytearray30']) : _gp.Dict_int32_bytearray30,
    (types['int32'], types['bytearray32']) : _gp.Dict_int32_bytearray32,
    (types['int32'], types['bytearray40']) : _gp.Dict_int32_bytearray40,
    (types['int32'], types['bytearray50']) : _gp.Dict_int32_bytearray50,
    (types['int64'], types['str4']) : _gp.Dict_int64_str4,
    (types['int64'], types['str8']) : _gp.Dict_int64_str8,
    (types['int64'], types['str16']) : _gp.Dict_int64_str16,
    (types['int64'], types['str32']) : _gp.Dict_int64_str32,
    (types['int64'], types['uint8']) : _gp.Dict_int64_uint8,
    (types['int64'], types['uint16']) : _gp.Dict_int64_uint16,
    (types['int64'], types['uint32']) : _gp.Dict_int64_uint32,
    (types['int64'], types['uint64']) : _gp.Dict_int64_uint64,
    (types['int64'], types['int8']) : _gp.Dict_int64_int8,
    (types['int64'], types['int16']) : _gp.Dict_int64_int16,
    (types['int64'], types['int32']) : _gp.Dict_int64_int32,
    (types['int64'], types['int64']) : _gp.Dict_int64_int64,
    (types['int64'], types['float32']) : _gp.Dict_int64_float32,
    (types['int64'], types['float64']) : _gp.Dict_int64_float64,
    (types['int64'], types['pair_str4_str4']) : _gp.Dict_int64_pair_str4_str4,
    (types['int64'], types['pair_str8_str8']) : _gp.Dict_int64_pair_str8_str8,
    (types['int64'], types['pair_str16_str16']) : _gp.Dict_int64_pair_str16_str16,
    (types['int64'], types['pair_str32_str32']) : _gp.Dict_int64_pair_str32_str32,
    (types['int64'], types['pair_uint8_uint8']) : _gp.Dict_int64_pair_uint8_uint8,
    (types['int64'], types['pair_uint16_uint16']) : _gp.Dict_int64_pair_uint16_uint16,
    (types['int64'], types['pair_uint32_uint32']) : _gp.Dict_int64_pair_uint32_uint32,
    (types['int64'], types['pair_uint64_uint64']) : _gp.Dict_int64_pair_uint64_uint64,
    (types['int64'], types['pair_int8_int8']) : _gp.Dict_int64_pair_int8_int8,
    (types['int64'], types['pair_int16_int16']) : _gp.Dict_int64_pair_int16_int16,
    (types['int64'], types['pair_int32_int32']) : _gp.Dict_int64_pair_int32_int32,
    (types['int64'], types['pair_int64_int64']) : _gp.Dict_int64_pair_int64_int64,
    (types['int64'], types['pair_float32_float32']) : _gp.Dict_int64_pair_float32_float32,
    (types['int64'], types['pair_float64_float64']) : _gp.Dict_int64_pair_float64_float64,
    (types['int64'], types['bytearray2']) : _gp.Dict_int64_bytearray2,
    (types['int64'], types['bytearray4']) : _gp.Dict_int64_bytearray4,
    (types['int64'], types['bytearray8']) : _gp.Dict_int64_bytearray8,
    (types['int64'], types['bytearray10']) : _gp.Dict_int64_bytearray10,
    (types['int64'], types['bytearray16']) : _gp.Dict_int64_bytearray16,
    (types['int64'], types['bytearray20']) : _gp.Dict_int64_bytearray20,
    (types['int64'], types['bytearray30']) : _gp.Dict_int64_bytearray30,
    (types['int64'], types['bytearray32']) : _gp.Dict_int64_bytearray32,
    (types['int64'], types['bytearray40']) : _gp.Dict_int64_bytearray40,
    (types['int64'], types['bytearray50']) : _gp.Dict_int64_bytearray50,
}
```
