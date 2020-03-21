# GetPy - A Fast and Small Python Dict/Set

The goal of GetPy is to provide the highest performance python dict/set that integrates into the NumPy/SciPy ecosystem.

## Installation
`pip install git+https://github.com/atom-moyer/getpy.git`

Currently about 16gb of memory is necessary for compilation. However, I would like to distribute a precompiled build.

## About
GetPy is a thin binding to The Parallel Hashmap (https://github.com/greg7mdp/parallel-hashmap.git) which is the current state of the art unordered map/set with minimal memory overhead and fast runtime speed. The binding layer is supported by PyBind11 (https://github.com/pybind/pybind11.git) which is fast to compile and simple to extend.

## How To Use
The `gp.Dict` and `gp.Set` objects are designed to maintain a similar interface to the corresponding standard python objects. There are some key differences though, which are necessary for vectorization and other performance considerations.

1) `gp.Dict.__init__` has three arguments `key_type`, `value_type`, and `default_value`. The type arguments are define which compiled data structure will be used under the hood, and the full list of preset combinations of `np.dtype`s is found with `gp.dict_types`. You can also specify a `default_value` at construction which must be castable to the `value_type`. This is the value returned by the dictionary if a key is not found.

2) All of `getpy.Dict` methods only support a vectorized interface. Therefore, methods like `gp.Dict.__getitem__`, `gp.Dict.__setitem__`, and `gp.Dict.__delitem__` must be performed with an `np.ndarray`.  That allows the performance critical for-loop to happen within the compiled c++. If you arguments are not `np.ndarray`s or their `dtype` does not match the defined `dtype` of the dict, you will be thrown a type error. GetPy will never implicitly cast any arguments. Note that some dunder methods cannot be vectorized such as `__contains__`. Therefore, some keywords like `in` do not behave as expected. Those methods are renamed without the double underscores to note their deviation from the standard interface.

3) `gp.Dict.__getitem__` will throw an error if you attempt to retrieve a key that does not exist, and you have not specified a `default_value` at construction. Instead, you should first run `gp.contains` on your key/array of keys, and then retrieve values corresponding to keys that exist. This is necessary for the vectorization support.

## Examples

### Simple Example
```python
import numpy as np
import getpy as gp

key_type = gp.types['uint64']
value_type = gp.types['uint64']

gp_dict = gp.Dict(key_type, value_type)

keys = np.random.randint(1, 1000, size=200, dtype=key_type)
values = np.random.randint(1, 1000, size=200, dtype=value_type)

gp_dict[keys] = values

iterated_keys = [key for key in gp_dict]
iterated_keys_and_values = [(key, value) for key, value in zip(*gp_dict.items())]

assert len(gp_dict) == len(np.unique(keys))

p_dict = dict()
for key, value in zip(keys, values):
    p_dict[key] = value

assert len(gp_dict) == len(p_dict)

select_keys = np.random.choice(keys, size=100)
select_values = gp_dict[select_keys]

random_keys = np.random.randint(1, 1000, size=500, dtype=key_type)
random_keys_mask = gp_dict.contains(random_keys)

mask_keys = random_keys[random_keys_mask]
mask_values = gp_dict[mask_keys]

gp_dict.iadd(keys, values)
gp_dict.isub(keys, values)
```

### Example With Default Value
```python
key_type = gp.types['uint64']
value_type = gp.types['uint64']

gp_dict = gp.Dict(key_type, value_type, default_value=0)

keys = np.random.randint(1, 1000, size=200, dtype=key_type)
values = np.random.randint(1, 1000, size=200, dtype=value_type)

gp_dict[keys] = values

iterated_keys = [key for key in gp_dict]
iterated_keys_and_values = [(key, value) for key, value in zip(*gp_dict.items())]

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
```

### Example With a Byteset dtype
```python
key_type = gp.types['uint64']
value_type = gp.types['byteset8']

gp_dict = gp.Dict(key_type, value_type)

keys = np.random.randint(1, 1000, size=10**2, dtype=key_type)
values = np.array([np.packbits(np.array([1, 0, 1, 0, 1, 0, 1, 0] * 8, dtype=np.bool)) for _ in range(10**2)]).view(value_type)
gp_dict[keys] = values

iterated_keys = [key for key in gp_dict]
iterated_keys_and_values = [(key, value) for key, value in zip(*gp_dict.items())]

select_keys = np.random.choice(keys, size=100)
select_values = gp_dict[select_keys]

random_keys = np.random.randint(1, 1000, size=500, dtype=key_type)
random_keys_mask = gp_dict.contains(random_keys)

mask_keys = random_keys[random_keys_mask]
mask_values = gp_dict[mask_keys]

gp_dict.ior(keys, values)
gp_dict.iand(keys, values)
```

### Serialization Example
```python
key_type = gp.types['uint64']
value_type = gp.types['uint64']

keys = np.random.randint(1, 1000, size=10**1, dtype=key_type)
values = np.random.randint(1, 1000, size=10**1, dtype=value_type)

gp_dict_1 = gp.Dict(key_type, value_type)
gp_dict_1[keys] = values
gp_dict_1.dump('test/test.hashtable.bin')

gp_dict_2 = gp.Dict(key_type, value_type)
gp_dict_2.load('test/test.hashtable.bin')

assert len(gp_dict_1) == len(gp_dict_2)
```

## Supported Data Types

```python
types = {
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
    'byteset4' : np.dtype('S4'),
    'byteset8' : np.dtype('S8'),
    'byteset12' : np.dtype('S12'),
    'byteset16' : np.dtype('S16'),
    'byteset20' : np.dtype('S20'),
    'byteset24' : np.dtype('S24'),
    'byteset28' : np.dtype('S28'),
    'byteset32' : np.dtype('S32'),
    'byteset36' : np.dtype('S36'),
    'byteset40' : np.dtype('S40'),
    'byteset44' : np.dtype('S44'),
    'byteset48' : np.dtype('S48'),
    'byteset52' : np.dtype('S52'),
    'byteset56' : np.dtype('S56'),
    'byteset60' : np.dtype('S60'),
    'byteset64' : np.dtype('S64'),
}
```
