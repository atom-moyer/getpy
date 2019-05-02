# GetPy - A Simple, Fast, and Small Hash Map for Python

The goal of GetPy is filling the need for high performance python dictionary that integrates into the NumPy ecosystem.

## Installation
`pip install git+https://github.com/atom-moyer/getpy.git`

## About
GetPy is a thin and robust binding to The Parallel Hashmap (https://github.com/greg7mdp/parallel-hashmap.git) which is the current state of the art for minimal memory overhead and fast runtime speed. The binding layer is supported by PyBind11 (https://github.com/pybind/pybind11.git) which is fast to compile and simple to extend. Serialization is handled by Cereal (https://github.com/USCiLab/cereal.git) which supports streaming binary serialization, a critical feature for the large hash maps this package is designed to support.

## How To Use
The `gp.Dict` object and, the newly supported, `gp.Set` is designed to maintain a similar interface to the corresponding standard python objects. There are some key differences though, which are necessary for performance reasons.

1) `gp.Dict.__init__` has three arguments `key_type`, `value_type`, and `default_value`. The type arguments are define which compiled data structure will be used under the hood, and the full list of preset combinations of `np.dtype`s is found with `gp.dict_types`. Most of the future work on getpy will be expanding this list of supported types. You can also specify a `default_value` at construction which must be castable to the `value_type`. This is the value returned by the dictionary if a key is not found.

2) All of `getpy.Dict` methods only support a vectorized interface. Therefore, methods like `gp.Dict.__getitem__`, `gp.Dict.__setitem__`, and `gp.Dict.__delitem__` must be performed with an `np.ndarray`.  That allows the performance critical for-loop to happen within the compiled c++. If you arguments are not `np.ndarray`s or their `dtype` does not match the defined `dtype` of the dict, you will be thrown a type error. GetPy will never implicitly cast any arguments. Note that some dunder methods cannot be vectorized such as `__contains__`. Therefore, some keywords like `in` do not behave as expected. Those methods are renamed without the double underscores to note their deviation from the standard interface.

3) `gp.Dict.__getitem__` will throw an error if you attempt to retrieve a key that does not exist, and you have not specified a `default_value` at construction. Instead, you should first run `gp.contains` on your key/array of keys, and then retrieve values corresponding to keys that exist. This is necessary for the vectorization support.

4) There are special generic data types which are named `bytearray`. These data structures are meant to be a generic data containers. They are designed be integrated with the numpy view casting.

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
                                1, 1, 1, 1, 1, 1, 1, 1]*25, dtype=np.bool)]*200, axis=1)

values = values.view(value_type)

gp_dict[keys] = values

iterated_keys = [key for key in gp_dict]
iterated_keys_and_values = [(key, value) for key, value in gp_dict.items()]

select_keys = np.random.choice(keys, size=100)
select_values = gp_dict[select_keys]

random_keys = np.random.randint(1, 1000, size=500, dtype=key_type)
random_keys_mask = gp_dict.contains(random_keys)

mask_keys = random_keys[random_keys_mask]
mask_values = gp_dict[mask_keys]
```

### Serialization Example
```python
key_type = np.dtype('u8')
value_type = np.dtype('u8')

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
    'bytearray1' : np.dtype({'names': ['bytearray'], 'formats': ['1u1']}),
    'bytearray2' : np.dtype({'names': ['bytearray'], 'formats': ['2u1']}),
    'bytearray3' : np.dtype({'names': ['bytearray'], 'formats': ['3u1']}),
    'bytearray4' : np.dtype({'names': ['bytearray'], 'formats': ['4u1']}),
    'bytearray5' : np.dtype({'names': ['bytearray'], 'formats': ['5u1']}),
    'bytearray6' : np.dtype({'names': ['bytearray'], 'formats': ['6u1']}),
    'bytearray7' : np.dtype({'names': ['bytearray'], 'formats': ['7u1']}),
    'bytearray8' : np.dtype({'names': ['bytearray'], 'formats': ['8u1']}),
    'bytearray9' : np.dtype({'names': ['bytearray'], 'formats': ['9u1']}),
    'bytearray10' : np.dtype({'names': ['bytearray'], 'formats': ['10u1']}),
    'bytearray11' : np.dtype({'names': ['bytearray'], 'formats': ['11u1']}),
    'bytearray12' : np.dtype({'names': ['bytearray'], 'formats': ['12u1']}),
    'bytearray13' : np.dtype({'names': ['bytearray'], 'formats': ['13u1']}),
    'bytearray14' : np.dtype({'names': ['bytearray'], 'formats': ['14u1']}),
    'bytearray15' : np.dtype({'names': ['bytearray'], 'formats': ['15u1']}),
    'bytearray16' : np.dtype({'names': ['bytearray'], 'formats': ['16u1']}),
    'bytearray20' : np.dtype({'names': ['bytearray'], 'formats': ['20u1']}),
    'bytearray30' : np.dtype({'names': ['bytearray'], 'formats': ['30u1']}),
    'bytearray32' : np.dtype({'names': ['bytearray'], 'formats': ['32u1']}),
    'bytearray40' : np.dtype({'names': ['bytearray'], 'formats': ['40u1']}),
    'bytearray50' : np.dtype({'names': ['bytearray'], 'formats': ['50u1']}),
    'bytearray60' : np.dtype({'names': ['bytearray'], 'formats': ['60u1']}),
    'bytearray64' : np.dtype({'names': ['bytearray'], 'formats': ['64u1']}),
    'bytearray70' : np.dtype({'names': ['bytearray'], 'formats': ['70u1']}),
    'bytearray80' : np.dtype({'names': ['bytearray'], 'formats': ['80u1']}),
    'bytearray90' : np.dtype({'names': ['bytearray'], 'formats': ['90u1']}),
    'bytearray100' : np.dtype({'names': ['bytearray'], 'formats': ['100u1']}),
    'bytearray128' : np.dtype({'names': ['bytearray'], 'formats': ['128u1']}),
    'byte8array1' : np.dtype({'names': ['bytearray'], 'formats': ['1u8']}),
    'byte8array2' : np.dtype({'names': ['bytearray'], 'formats': ['2u8']}),
    'byte8array3' : np.dtype({'names': ['bytearray'], 'formats': ['3u8']}),
    'byte8array4' : np.dtype({'names': ['bytearray'], 'formats': ['4u8']}),
    'byte8array5' : np.dtype({'names': ['bytearray'], 'formats': ['5u8']}),
    'byte8array6' : np.dtype({'names': ['bytearray'], 'formats': ['6u8']}),
    'byte8array7' : np.dtype({'names': ['bytearray'], 'formats': ['7u8']}),
    'byte8array8' : np.dtype({'names': ['bytearray'], 'formats': ['8u8']}),
    'byte8array9' : np.dtype({'names': ['bytearray'], 'formats': ['9u8']}),
    'byte8array10' : np.dtype({'names': ['bytearray'], 'formats': ['10u8']}),
    'byte8array11' : np.dtype({'names': ['bytearray'], 'formats': ['11u8']}),
    'byte8array12' : np.dtype({'names': ['bytearray'], 'formats': ['12u8']}),
    'byte8array13' : np.dtype({'names': ['bytearray'], 'formats': ['13u8']}),
    'byte8array14' : np.dtype({'names': ['bytearray'], 'formats': ['14u8']}),
    'byte8array15' : np.dtype({'names': ['bytearray'], 'formats': ['15u8']}),
    'byte8array16' : np.dtype({'names': ['bytearray'], 'formats': ['16u8']}),
}

dict_types = {
    (types['str4'], types['str4']) : _gp.Dict_str4_str4,
    (types['str4'], types['str8']) : _gp.Dict_str4_str8,
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
    (types['str4'], types['bytearray1']) : _gp.Dict_str4_bytearray1,
    (types['str4'], types['bytearray2']) : _gp.Dict_str4_bytearray2,
    (types['str4'], types['bytearray3']) : _gp.Dict_str4_bytearray3,
    (types['str4'], types['bytearray4']) : _gp.Dict_str4_bytearray4,
    (types['str4'], types['bytearray5']) : _gp.Dict_str4_bytearray5,
    (types['str4'], types['bytearray6']) : _gp.Dict_str4_bytearray6,
    (types['str4'], types['bytearray7']) : _gp.Dict_str4_bytearray7,
    (types['str4'], types['bytearray8']) : _gp.Dict_str4_bytearray8,
    (types['str4'], types['bytearray9']) : _gp.Dict_str4_bytearray9,
    (types['str4'], types['bytearray10']) : _gp.Dict_str4_bytearray10,
    (types['str4'], types['bytearray11']) : _gp.Dict_str4_bytearray11,
    (types['str4'], types['bytearray12']) : _gp.Dict_str4_bytearray12,
    (types['str4'], types['bytearray13']) : _gp.Dict_str4_bytearray13,
    (types['str4'], types['bytearray14']) : _gp.Dict_str4_bytearray14,
    (types['str4'], types['bytearray15']) : _gp.Dict_str4_bytearray15,
    (types['str4'], types['bytearray16']) : _gp.Dict_str4_bytearray16,
    (types['str4'], types['bytearray20']) : _gp.Dict_str4_bytearray20,
    (types['str4'], types['bytearray30']) : _gp.Dict_str4_bytearray30,
    (types['str4'], types['bytearray32']) : _gp.Dict_str4_bytearray32,
    (types['str4'], types['bytearray40']) : _gp.Dict_str4_bytearray40,
    (types['str4'], types['bytearray50']) : _gp.Dict_str4_bytearray50,
    (types['str4'], types['bytearray60']) : _gp.Dict_str4_bytearray60,
    (types['str4'], types['bytearray64']) : _gp.Dict_str4_bytearray64,
    (types['str4'], types['bytearray70']) : _gp.Dict_str4_bytearray70,
    (types['str4'], types['bytearray80']) : _gp.Dict_str4_bytearray80,
    (types['str4'], types['bytearray90']) : _gp.Dict_str4_bytearray90,
    (types['str4'], types['bytearray100']) : _gp.Dict_str4_bytearray100,
    (types['str4'], types['bytearray128']) : _gp.Dict_str4_bytearray128,
    (types['str4'], types['byte8array1']) : _gp.Dict_str4_byte8array1,
    (types['str4'], types['byte8array2']) : _gp.Dict_str4_byte8array2,
    (types['str4'], types['byte8array3']) : _gp.Dict_str4_byte8array3,
    (types['str4'], types['byte8array4']) : _gp.Dict_str4_byte8array4,
    (types['str4'], types['byte8array5']) : _gp.Dict_str4_byte8array5,
    (types['str4'], types['byte8array6']) : _gp.Dict_str4_byte8array6,
    (types['str4'], types['byte8array7']) : _gp.Dict_str4_byte8array7,
    (types['str4'], types['byte8array8']) : _gp.Dict_str4_byte8array8,
    (types['str4'], types['byte8array9']) : _gp.Dict_str4_byte8array9,
    (types['str4'], types['byte8array10']) : _gp.Dict_str4_byte8array10,
    (types['str4'], types['byte8array11']) : _gp.Dict_str4_byte8array11,
    (types['str4'], types['byte8array12']) : _gp.Dict_str4_byte8array12,
    (types['str4'], types['byte8array13']) : _gp.Dict_str4_byte8array13,
    (types['str4'], types['byte8array14']) : _gp.Dict_str4_byte8array14,
    (types['str4'], types['byte8array15']) : _gp.Dict_str4_byte8array15,
    (types['str4'], types['byte8array16']) : _gp.Dict_str4_byte8array16,
    (types['str8'], types['str4']) : _gp.Dict_str8_str4,
    (types['str8'], types['str8']) : _gp.Dict_str8_str8,
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
    (types['str8'], types['bytearray1']) : _gp.Dict_str8_bytearray1,
    (types['str8'], types['bytearray2']) : _gp.Dict_str8_bytearray2,
    (types['str8'], types['bytearray3']) : _gp.Dict_str8_bytearray3,
    (types['str8'], types['bytearray4']) : _gp.Dict_str8_bytearray4,
    (types['str8'], types['bytearray5']) : _gp.Dict_str8_bytearray5,
    (types['str8'], types['bytearray6']) : _gp.Dict_str8_bytearray6,
    (types['str8'], types['bytearray7']) : _gp.Dict_str8_bytearray7,
    (types['str8'], types['bytearray8']) : _gp.Dict_str8_bytearray8,
    (types['str8'], types['bytearray9']) : _gp.Dict_str8_bytearray9,
    (types['str8'], types['bytearray10']) : _gp.Dict_str8_bytearray10,
    (types['str8'], types['bytearray11']) : _gp.Dict_str8_bytearray11,
    (types['str8'], types['bytearray12']) : _gp.Dict_str8_bytearray12,
    (types['str8'], types['bytearray13']) : _gp.Dict_str8_bytearray13,
    (types['str8'], types['bytearray14']) : _gp.Dict_str8_bytearray14,
    (types['str8'], types['bytearray15']) : _gp.Dict_str8_bytearray15,
    (types['str8'], types['bytearray16']) : _gp.Dict_str8_bytearray16,
    (types['str8'], types['bytearray20']) : _gp.Dict_str8_bytearray20,
    (types['str8'], types['bytearray30']) : _gp.Dict_str8_bytearray30,
    (types['str8'], types['bytearray32']) : _gp.Dict_str8_bytearray32,
    (types['str8'], types['bytearray40']) : _gp.Dict_str8_bytearray40,
    (types['str8'], types['bytearray50']) : _gp.Dict_str8_bytearray50,
    (types['str8'], types['bytearray60']) : _gp.Dict_str8_bytearray60,
    (types['str8'], types['bytearray64']) : _gp.Dict_str8_bytearray64,
    (types['str8'], types['bytearray70']) : _gp.Dict_str8_bytearray70,
    (types['str8'], types['bytearray80']) : _gp.Dict_str8_bytearray80,
    (types['str8'], types['bytearray90']) : _gp.Dict_str8_bytearray90,
    (types['str8'], types['bytearray100']) : _gp.Dict_str8_bytearray100,
    (types['str8'], types['bytearray128']) : _gp.Dict_str8_bytearray128,
    (types['str8'], types['byte8array1']) : _gp.Dict_str8_byte8array1,
    (types['str8'], types['byte8array2']) : _gp.Dict_str8_byte8array2,
    (types['str8'], types['byte8array3']) : _gp.Dict_str8_byte8array3,
    (types['str8'], types['byte8array4']) : _gp.Dict_str8_byte8array4,
    (types['str8'], types['byte8array5']) : _gp.Dict_str8_byte8array5,
    (types['str8'], types['byte8array6']) : _gp.Dict_str8_byte8array6,
    (types['str8'], types['byte8array7']) : _gp.Dict_str8_byte8array7,
    (types['str8'], types['byte8array8']) : _gp.Dict_str8_byte8array8,
    (types['str8'], types['byte8array9']) : _gp.Dict_str8_byte8array9,
    (types['str8'], types['byte8array10']) : _gp.Dict_str8_byte8array10,
    (types['str8'], types['byte8array11']) : _gp.Dict_str8_byte8array11,
    (types['str8'], types['byte8array12']) : _gp.Dict_str8_byte8array12,
    (types['str8'], types['byte8array13']) : _gp.Dict_str8_byte8array13,
    (types['str8'], types['byte8array14']) : _gp.Dict_str8_byte8array14,
    (types['str8'], types['byte8array15']) : _gp.Dict_str8_byte8array15,
    (types['str8'], types['byte8array16']) : _gp.Dict_str8_byte8array16,
    (types['uint32'], types['str4']) : _gp.Dict_uint32_str4,
    (types['uint32'], types['str8']) : _gp.Dict_uint32_str8,
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
    (types['uint32'], types['bytearray1']) : _gp.Dict_uint32_bytearray1,
    (types['uint32'], types['bytearray2']) : _gp.Dict_uint32_bytearray2,
    (types['uint32'], types['bytearray3']) : _gp.Dict_uint32_bytearray3,
    (types['uint32'], types['bytearray4']) : _gp.Dict_uint32_bytearray4,
    (types['uint32'], types['bytearray5']) : _gp.Dict_uint32_bytearray5,
    (types['uint32'], types['bytearray6']) : _gp.Dict_uint32_bytearray6,
    (types['uint32'], types['bytearray7']) : _gp.Dict_uint32_bytearray7,
    (types['uint32'], types['bytearray8']) : _gp.Dict_uint32_bytearray8,
    (types['uint32'], types['bytearray9']) : _gp.Dict_uint32_bytearray9,
    (types['uint32'], types['bytearray10']) : _gp.Dict_uint32_bytearray10,
    (types['uint32'], types['bytearray11']) : _gp.Dict_uint32_bytearray11,
    (types['uint32'], types['bytearray12']) : _gp.Dict_uint32_bytearray12,
    (types['uint32'], types['bytearray13']) : _gp.Dict_uint32_bytearray13,
    (types['uint32'], types['bytearray14']) : _gp.Dict_uint32_bytearray14,
    (types['uint32'], types['bytearray15']) : _gp.Dict_uint32_bytearray15,
    (types['uint32'], types['bytearray16']) : _gp.Dict_uint32_bytearray16,
    (types['uint32'], types['bytearray20']) : _gp.Dict_uint32_bytearray20,
    (types['uint32'], types['bytearray30']) : _gp.Dict_uint32_bytearray30,
    (types['uint32'], types['bytearray32']) : _gp.Dict_uint32_bytearray32,
    (types['uint32'], types['bytearray40']) : _gp.Dict_uint32_bytearray40,
    (types['uint32'], types['bytearray50']) : _gp.Dict_uint32_bytearray50,
    (types['uint32'], types['bytearray60']) : _gp.Dict_uint32_bytearray60,
    (types['uint32'], types['bytearray64']) : _gp.Dict_uint32_bytearray64,
    (types['uint32'], types['bytearray70']) : _gp.Dict_uint32_bytearray70,
    (types['uint32'], types['bytearray80']) : _gp.Dict_uint32_bytearray80,
    (types['uint32'], types['bytearray90']) : _gp.Dict_uint32_bytearray90,
    (types['uint32'], types['bytearray100']) : _gp.Dict_uint32_bytearray100,
    (types['uint32'], types['bytearray128']) : _gp.Dict_uint32_bytearray128,
    (types['uint32'], types['byte8array1']) : _gp.Dict_uint32_byte8array1,
    (types['uint32'], types['byte8array2']) : _gp.Dict_uint32_byte8array2,
    (types['uint32'], types['byte8array3']) : _gp.Dict_uint32_byte8array3,
    (types['uint32'], types['byte8array4']) : _gp.Dict_uint32_byte8array4,
    (types['uint32'], types['byte8array5']) : _gp.Dict_uint32_byte8array5,
    (types['uint32'], types['byte8array6']) : _gp.Dict_uint32_byte8array6,
    (types['uint32'], types['byte8array7']) : _gp.Dict_uint32_byte8array7,
    (types['uint32'], types['byte8array8']) : _gp.Dict_uint32_byte8array8,
    (types['uint32'], types['byte8array9']) : _gp.Dict_uint32_byte8array9,
    (types['uint32'], types['byte8array10']) : _gp.Dict_uint32_byte8array10,
    (types['uint32'], types['byte8array11']) : _gp.Dict_uint32_byte8array11,
    (types['uint32'], types['byte8array12']) : _gp.Dict_uint32_byte8array12,
    (types['uint32'], types['byte8array13']) : _gp.Dict_uint32_byte8array13,
    (types['uint32'], types['byte8array14']) : _gp.Dict_uint32_byte8array14,
    (types['uint32'], types['byte8array15']) : _gp.Dict_uint32_byte8array15,
    (types['uint32'], types['byte8array16']) : _gp.Dict_uint32_byte8array16,
    (types['uint64'], types['str4']) : _gp.Dict_uint64_str4,
    (types['uint64'], types['str8']) : _gp.Dict_uint64_str8,
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
    (types['uint64'], types['bytearray1']) : _gp.Dict_uint64_bytearray1,
    (types['uint64'], types['bytearray2']) : _gp.Dict_uint64_bytearray2,
    (types['uint64'], types['bytearray3']) : _gp.Dict_uint64_bytearray3,
    (types['uint64'], types['bytearray4']) : _gp.Dict_uint64_bytearray4,
    (types['uint64'], types['bytearray5']) : _gp.Dict_uint64_bytearray5,
    (types['uint64'], types['bytearray6']) : _gp.Dict_uint64_bytearray6,
    (types['uint64'], types['bytearray7']) : _gp.Dict_uint64_bytearray7,
    (types['uint64'], types['bytearray8']) : _gp.Dict_uint64_bytearray8,
    (types['uint64'], types['bytearray9']) : _gp.Dict_uint64_bytearray9,
    (types['uint64'], types['bytearray10']) : _gp.Dict_uint64_bytearray10,
    (types['uint64'], types['bytearray11']) : _gp.Dict_uint64_bytearray11,
    (types['uint64'], types['bytearray12']) : _gp.Dict_uint64_bytearray12,
    (types['uint64'], types['bytearray13']) : _gp.Dict_uint64_bytearray13,
    (types['uint64'], types['bytearray14']) : _gp.Dict_uint64_bytearray14,
    (types['uint64'], types['bytearray15']) : _gp.Dict_uint64_bytearray15,
    (types['uint64'], types['bytearray16']) : _gp.Dict_uint64_bytearray16,
    (types['uint64'], types['bytearray20']) : _gp.Dict_uint64_bytearray20,
    (types['uint64'], types['bytearray30']) : _gp.Dict_uint64_bytearray30,
    (types['uint64'], types['bytearray32']) : _gp.Dict_uint64_bytearray32,
    (types['uint64'], types['bytearray40']) : _gp.Dict_uint64_bytearray40,
    (types['uint64'], types['bytearray50']) : _gp.Dict_uint64_bytearray50,
    (types['uint64'], types['bytearray60']) : _gp.Dict_uint64_bytearray60,
    (types['uint64'], types['bytearray64']) : _gp.Dict_uint64_bytearray64,
    (types['uint64'], types['bytearray70']) : _gp.Dict_uint64_bytearray70,
    (types['uint64'], types['bytearray80']) : _gp.Dict_uint64_bytearray80,
    (types['uint64'], types['bytearray90']) : _gp.Dict_uint64_bytearray90,
    (types['uint64'], types['bytearray100']) : _gp.Dict_uint64_bytearray100,
    (types['uint64'], types['bytearray128']) : _gp.Dict_uint64_bytearray128,
    (types['uint64'], types['byte8array1']) : _gp.Dict_uint64_byte8array1,
    (types['uint64'], types['byte8array2']) : _gp.Dict_uint64_byte8array2,
    (types['uint64'], types['byte8array3']) : _gp.Dict_uint64_byte8array3,
    (types['uint64'], types['byte8array4']) : _gp.Dict_uint64_byte8array4,
    (types['uint64'], types['byte8array5']) : _gp.Dict_uint64_byte8array5,
    (types['uint64'], types['byte8array6']) : _gp.Dict_uint64_byte8array6,
    (types['uint64'], types['byte8array7']) : _gp.Dict_uint64_byte8array7,
    (types['uint64'], types['byte8array8']) : _gp.Dict_uint64_byte8array8,
    (types['uint64'], types['byte8array9']) : _gp.Dict_uint64_byte8array9,
    (types['uint64'], types['byte8array10']) : _gp.Dict_uint64_byte8array10,
    (types['uint64'], types['byte8array11']) : _gp.Dict_uint64_byte8array11,
    (types['uint64'], types['byte8array12']) : _gp.Dict_uint64_byte8array12,
    (types['uint64'], types['byte8array13']) : _gp.Dict_uint64_byte8array13,
    (types['uint64'], types['byte8array14']) : _gp.Dict_uint64_byte8array14,
    (types['uint64'], types['byte8array15']) : _gp.Dict_uint64_byte8array15,
    (types['uint64'], types['byte8array16']) : _gp.Dict_uint64_byte8array16,
    (types['int32'], types['str4']) : _gp.Dict_int32_str4,
    (types['int32'], types['str8']) : _gp.Dict_int32_str8,
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
    (types['int32'], types['bytearray1']) : _gp.Dict_int32_bytearray1,
    (types['int32'], types['bytearray2']) : _gp.Dict_int32_bytearray2,
    (types['int32'], types['bytearray3']) : _gp.Dict_int32_bytearray3,
    (types['int32'], types['bytearray4']) : _gp.Dict_int32_bytearray4,
    (types['int32'], types['bytearray5']) : _gp.Dict_int32_bytearray5,
    (types['int32'], types['bytearray6']) : _gp.Dict_int32_bytearray6,
    (types['int32'], types['bytearray7']) : _gp.Dict_int32_bytearray7,
    (types['int32'], types['bytearray8']) : _gp.Dict_int32_bytearray8,
    (types['int32'], types['bytearray9']) : _gp.Dict_int32_bytearray9,
    (types['int32'], types['bytearray10']) : _gp.Dict_int32_bytearray10,
    (types['int32'], types['bytearray11']) : _gp.Dict_int32_bytearray11,
    (types['int32'], types['bytearray12']) : _gp.Dict_int32_bytearray12,
    (types['int32'], types['bytearray13']) : _gp.Dict_int32_bytearray13,
    (types['int32'], types['bytearray14']) : _gp.Dict_int32_bytearray14,
    (types['int32'], types['bytearray15']) : _gp.Dict_int32_bytearray15,
    (types['int32'], types['bytearray16']) : _gp.Dict_int32_bytearray16,
    (types['int32'], types['bytearray20']) : _gp.Dict_int32_bytearray20,
    (types['int32'], types['bytearray30']) : _gp.Dict_int32_bytearray30,
    (types['int32'], types['bytearray32']) : _gp.Dict_int32_bytearray32,
    (types['int32'], types['bytearray40']) : _gp.Dict_int32_bytearray40,
    (types['int32'], types['bytearray50']) : _gp.Dict_int32_bytearray50,
    (types['int32'], types['bytearray60']) : _gp.Dict_int32_bytearray60,
    (types['int32'], types['bytearray64']) : _gp.Dict_int32_bytearray64,
    (types['int32'], types['bytearray70']) : _gp.Dict_int32_bytearray70,
    (types['int32'], types['bytearray80']) : _gp.Dict_int32_bytearray80,
    (types['int32'], types['bytearray90']) : _gp.Dict_int32_bytearray90,
    (types['int32'], types['bytearray100']) : _gp.Dict_int32_bytearray100,
    (types['int32'], types['bytearray128']) : _gp.Dict_int32_bytearray128,
    (types['int32'], types['byte8array1']) : _gp.Dict_int32_byte8array1,
    (types['int32'], types['byte8array2']) : _gp.Dict_int32_byte8array2,
    (types['int32'], types['byte8array3']) : _gp.Dict_int32_byte8array3,
    (types['int32'], types['byte8array4']) : _gp.Dict_int32_byte8array4,
    (types['int32'], types['byte8array5']) : _gp.Dict_int32_byte8array5,
    (types['int32'], types['byte8array6']) : _gp.Dict_int32_byte8array6,
    (types['int32'], types['byte8array7']) : _gp.Dict_int32_byte8array7,
    (types['int32'], types['byte8array8']) : _gp.Dict_int32_byte8array8,
    (types['int32'], types['byte8array9']) : _gp.Dict_int32_byte8array9,
    (types['int32'], types['byte8array10']) : _gp.Dict_int32_byte8array10,
    (types['int32'], types['byte8array11']) : _gp.Dict_int32_byte8array11,
    (types['int32'], types['byte8array12']) : _gp.Dict_int32_byte8array12,
    (types['int32'], types['byte8array13']) : _gp.Dict_int32_byte8array13,
    (types['int32'], types['byte8array14']) : _gp.Dict_int32_byte8array14,
    (types['int32'], types['byte8array15']) : _gp.Dict_int32_byte8array15,
    (types['int32'], types['byte8array16']) : _gp.Dict_int32_byte8array16,
    (types['int64'], types['str4']) : _gp.Dict_int64_str4,
    (types['int64'], types['str8']) : _gp.Dict_int64_str8,
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
    (types['int64'], types['bytearray1']) : _gp.Dict_int64_bytearray1,
    (types['int64'], types['bytearray2']) : _gp.Dict_int64_bytearray2,
    (types['int64'], types['bytearray3']) : _gp.Dict_int64_bytearray3,
    (types['int64'], types['bytearray4']) : _gp.Dict_int64_bytearray4,
    (types['int64'], types['bytearray5']) : _gp.Dict_int64_bytearray5,
    (types['int64'], types['bytearray6']) : _gp.Dict_int64_bytearray6,
    (types['int64'], types['bytearray7']) : _gp.Dict_int64_bytearray7,
    (types['int64'], types['bytearray8']) : _gp.Dict_int64_bytearray8,
    (types['int64'], types['bytearray9']) : _gp.Dict_int64_bytearray9,
    (types['int64'], types['bytearray10']) : _gp.Dict_int64_bytearray10,
    (types['int64'], types['bytearray11']) : _gp.Dict_int64_bytearray11,
    (types['int64'], types['bytearray12']) : _gp.Dict_int64_bytearray12,
    (types['int64'], types['bytearray13']) : _gp.Dict_int64_bytearray13,
    (types['int64'], types['bytearray14']) : _gp.Dict_int64_bytearray14,
    (types['int64'], types['bytearray15']) : _gp.Dict_int64_bytearray15,
    (types['int64'], types['bytearray16']) : _gp.Dict_int64_bytearray16,
    (types['int64'], types['bytearray20']) : _gp.Dict_int64_bytearray20,
    (types['int64'], types['bytearray30']) : _gp.Dict_int64_bytearray30,
    (types['int64'], types['bytearray32']) : _gp.Dict_int64_bytearray32,
    (types['int64'], types['bytearray40']) : _gp.Dict_int64_bytearray40,
    (types['int64'], types['bytearray50']) : _gp.Dict_int64_bytearray50,
    (types['int64'], types['bytearray60']) : _gp.Dict_int64_bytearray60,
    (types['int64'], types['bytearray64']) : _gp.Dict_int64_bytearray64,
    (types['int64'], types['bytearray70']) : _gp.Dict_int64_bytearray70,
    (types['int64'], types['bytearray80']) : _gp.Dict_int64_bytearray80,
    (types['int64'], types['bytearray90']) : _gp.Dict_int64_bytearray90,
    (types['int64'], types['bytearray100']) : _gp.Dict_int64_bytearray100,
    (types['int64'], types['bytearray128']) : _gp.Dict_int64_bytearray128,
    (types['int64'], types['byte8array1']) : _gp.Dict_int64_byte8array1,
    (types['int64'], types['byte8array2']) : _gp.Dict_int64_byte8array2,
    (types['int64'], types['byte8array3']) : _gp.Dict_int64_byte8array3,
    (types['int64'], types['byte8array4']) : _gp.Dict_int64_byte8array4,
    (types['int64'], types['byte8array5']) : _gp.Dict_int64_byte8array5,
    (types['int64'], types['byte8array6']) : _gp.Dict_int64_byte8array6,
    (types['int64'], types['byte8array7']) : _gp.Dict_int64_byte8array7,
    (types['int64'], types['byte8array8']) : _gp.Dict_int64_byte8array8,
    (types['int64'], types['byte8array9']) : _gp.Dict_int64_byte8array9,
    (types['int64'], types['byte8array10']) : _gp.Dict_int64_byte8array10,
    (types['int64'], types['byte8array11']) : _gp.Dict_int64_byte8array11,
    (types['int64'], types['byte8array12']) : _gp.Dict_int64_byte8array12,
    (types['int64'], types['byte8array13']) : _gp.Dict_int64_byte8array13,
    (types['int64'], types['byte8array14']) : _gp.Dict_int64_byte8array14,
    (types['int64'], types['byte8array15']) : _gp.Dict_int64_byte8array15,
    (types['int64'], types['byte8array16']) : _gp.Dict_int64_byte8array16,
}

set_types = {
    (types['str4']) : _gp.Set_str4,
    (types['str8']) : _gp.Set_str8,
    (types['uint32']) : _gp.Set_uint32,
    (types['uint64']) : _gp.Set_uint64,
    (types['int32']) : _gp.Set_int32,
    (types['int64']) : _gp.Set_int64,
    (types['bytearray1']) : _gp.Set_bytearray1,
    (types['bytearray2']) : _gp.Set_bytearray2,
    (types['bytearray3']) : _gp.Set_bytearray3,
    (types['bytearray4']) : _gp.Set_bytearray4,
    (types['bytearray5']) : _gp.Set_bytearray5,
    (types['bytearray6']) : _gp.Set_bytearray6,
    (types['bytearray7']) : _gp.Set_bytearray7,
    (types['bytearray8']) : _gp.Set_bytearray8,
    (types['bytearray9']) : _gp.Set_bytearray9,
    (types['bytearray10']) : _gp.Set_bytearray10,
    (types['bytearray11']) : _gp.Set_bytearray11,
    (types['bytearray12']) : _gp.Set_bytearray12,
    (types['bytearray13']) : _gp.Set_bytearray13,
    (types['bytearray14']) : _gp.Set_bytearray14,
    (types['bytearray15']) : _gp.Set_bytearray15,
    (types['bytearray16']) : _gp.Set_bytearray16,
    (types['bytearray20']) : _gp.Set_bytearray20,
    (types['bytearray30']) : _gp.Set_bytearray30,
    (types['bytearray32']) : _gp.Set_bytearray32,
    (types['bytearray40']) : _gp.Set_bytearray40,
    (types['bytearray50']) : _gp.Set_bytearray50,
    (types['bytearray60']) : _gp.Set_bytearray60,
    (types['bytearray64']) : _gp.Set_bytearray64,
    (types['bytearray70']) : _gp.Set_bytearray70,
    (types['bytearray80']) : _gp.Set_bytearray80,
    (types['bytearray90']) : _gp.Set_bytearray90,
    (types['bytearray100']) : _gp.Set_bytearray100,
    (types['bytearray128']) : _gp.Set_bytearray128,
    (types['byte8array1']) : _gp.Set_byte8array1,
    (types['byte8array2']) : _gp.Set_byte8array2,
    (types['byte8array3']) : _gp.Set_byte8array3,
    (types['byte8array4']) : _gp.Set_byte8array4,
    (types['byte8array5']) : _gp.Set_byte8array5,
    (types['byte8array6']) : _gp.Set_byte8array6,
    (types['byte8array7']) : _gp.Set_byte8array7,
    (types['byte8array8']) : _gp.Set_byte8array8,
    (types['byte8array9']) : _gp.Set_byte8array9,
    (types['byte8array10']) : _gp.Set_byte8array10,
    (types['byte8array11']) : _gp.Set_byte8array11,
    (types['byte8array12']) : _gp.Set_byte8array12,
    (types['byte8array13']) : _gp.Set_byte8array13,
    (types['byte8array14']) : _gp.Set_byte8array14,
    (types['byte8array15']) : _gp.Set_byte8array15,
    (types['byte8array16']) : _gp.Set_byte8array16,
}
```
