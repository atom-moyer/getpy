# GetPy - A Vectorized Python Dict/Set

The goal of GetPy is to provide the highest performance python dict/set that integrates into the python scientific ecosystem.

## Installation
`pip install getpy`

Note only a linux build is currently distributed. If you would like to build the package from source you can clone the repo and run `python setup.py install`. Compilation will require 16gb of ram. I am working on getting that down.

## About
GetPy is a thin binding to the Parallel Hashmap (https://github.com/greg7mdp/parallel-hashmap.git) which is the current state of the art unordered map/set with minimal memory overhead and fast runtime speed. The binding layer is supported by PyBind11 (https://github.com/pybind/pybind11.git) which is fast to compile and simple to extend.

## How To Use
The `gp.Dict` and `gp.Set` objects are designed to maintain a similar interface to the corresponding standard python objects. There are some key differences though, which are necessary for vectorization and other performance considerations.

1) `gp.Dict.__init__` has three arguments `key_type`, `value_type`, and `default_value`. The type arguments are define which compiled data structure will be used under the hood, and the full list of preset combinations of `np.dtype`s is found with `gp.dict_types`. You can also specify a `default_value` at construction which must be castable to the `value_type`. This is the value returned by the dictionary if a key is not found.

2) All of `getpy.Dict` methods support a vectorized interface. Therefore, methods like `gp.Dict.__getitem__`, `gp.Dict.__setitem__`, and `gp.Dict.__delitem__` can be performed with an `np.ndarray`.  That allows the performance critical for-loop to happen within the compiled c++. Note that some dunder methods cannot be vectorized such as `__contains__`. Therefore, some keywords like `in` do not behave as expected. Those methods are renamed without the double underscores to note their deviation from the standard interface.

3) If a key does not exist, `gp.Dict.__getitem__` will return the `default_value`. If you do not specify the `default_value`, it will default to the default constructor of your data type (all 0 bits). If you would like to know the difference between a key that does not exist and a key that returns the default value, you should first run `gp.contains` on your key/array of keys, and then retrieve values corresponding to keys that exist.

4) There is also a `gp.MultiDict` object. This object stores multiple unique values per key.

## Examples

### Simple Example
```python
import numpy as np
import getpy as gp

key_type = np.dtype('u8')
value_type = np.dtype('u8')

keys = np.random.randint(1, 1000, size=10**2, dtype=key_type)
values = np.random.randint(1, 1000, size=10**2, dtype=value_type)

gp_dict = gp.Dict(key_type, value_type)
gp_dict[keys] = values
```

### Default Example
```python
import numpy as np
import getpy as gp

key_type = np.dtype('u8')
value_type = np.dtype('u8')

keys = np.random.randint(1, 1000, size=10**2, dtype=key_type)
values = np.random.randint(1, 1000, size=10**2, dtype=value_type)

gp_dict = gp.Dict(key_type, value_type, default_value=42)
gp_dict[keys] = values

random_keys = np.random.randint(1, 1000, size=500, dtype=key_type)
random_values = gp_dict[random_keys]
```

### Byteset Example
```python
import numpy as np
import getpy as gp

key_type = np.dtype('S8')
value_type = np.dtype('S8')

keys = np.array([np.random.bytes(8) for i in range(10**2)], dtype=key_type)
values = np.array([np.random.bytes(8) for i in range(10**2)], dtype=value_type)

gp_dict = gp.Dict(key_type, value_type)
gp_dict[keys] = values
```

### Multidimensional Example
```python
import numpy as np
import getpy as gp

key_type = np.dtype('u8')
value_type = np.dtype('u8')

keys = np.random.randint(1, 1000, size=10**2, dtype=key_type).reshape(10,10)
values = np.random.randint(1, 1000, size=10**2, dtype=value_type).reshape(10,10)

gp_dict = gp.Dict(key_type, value_type)
gp_dict[keys] = values
```

### Serialization Example
```python
import numpy as np
import getpy as gp

key_type = np.dtype('u8')
value_type = np.dtype('u8')

keys = np.random.randint(1, 1000, size=10**1, dtype=key_type)
values = np.random.randint(1, 1000, size=10**1, dtype=value_type)

gp_dict_1 = gp.Dict(key_type, value_type)
gp_dict_1[keys] = values
gp_dict_1.dump('test/test.hashtable.bin')

gp_dict_2 = gp.Dict(key_type, value_type)
gp_dict_2.load('test/test.hashtable.bin')
```

## Supported Data Types

```python
dict_types = {
    (np.dtype('u4'), np.dtype('u1')) : _gp.Dict_u4_u1,
    (np.dtype('u4'), np.dtype('u2')) : _gp.Dict_u4_u2,
    (np.dtype('u4'), np.dtype('u4')) : _gp.Dict_u4_u4,
    (np.dtype('u4'), np.dtype('u8')) : _gp.Dict_u4_u8,
    (np.dtype('u4'), np.dtype('i1')) : _gp.Dict_u4_i1,
    (np.dtype('u4'), np.dtype('i2')) : _gp.Dict_u4_i2,
    (np.dtype('u4'), np.dtype('i4')) : _gp.Dict_u4_i4,
    (np.dtype('u4'), np.dtype('i8')) : _gp.Dict_u4_i8,
    (np.dtype('u4'), np.dtype('f4')) : _gp.Dict_u4_f4,
    (np.dtype('u4'), np.dtype('f8')) : _gp.Dict_u4_f8,
    (np.dtype('u4'), np.dtype('S8')) : _gp.Dict_u4_S8,
    (np.dtype('u4'), np.dtype('S16')) : _gp.Dict_u4_S16,
    (np.dtype('u8'), np.dtype('u1')) : _gp.Dict_u8_u1,
    (np.dtype('u8'), np.dtype('u2')) : _gp.Dict_u8_u2,
    (np.dtype('u8'), np.dtype('u4')) : _gp.Dict_u8_u4,
    (np.dtype('u8'), np.dtype('u8')) : _gp.Dict_u8_u8,
    (np.dtype('u8'), np.dtype('i1')) : _gp.Dict_u8_i1,
    (np.dtype('u8'), np.dtype('i2')) : _gp.Dict_u8_i2,
    (np.dtype('u8'), np.dtype('i4')) : _gp.Dict_u8_i4,
    (np.dtype('u8'), np.dtype('i8')) : _gp.Dict_u8_i8,
    (np.dtype('u8'), np.dtype('f4')) : _gp.Dict_u8_f4,
    (np.dtype('u8'), np.dtype('f8')) : _gp.Dict_u8_f8,
    (np.dtype('u8'), np.dtype('S8')) : _gp.Dict_u8_S8,
    (np.dtype('u8'), np.dtype('S16')) : _gp.Dict_u8_S16,
    (np.dtype('i4'), np.dtype('u1')) : _gp.Dict_i4_u1,
    (np.dtype('i4'), np.dtype('u2')) : _gp.Dict_i4_u2,
    (np.dtype('i4'), np.dtype('u4')) : _gp.Dict_i4_u4,
    (np.dtype('i4'), np.dtype('u8')) : _gp.Dict_i4_u8,
    (np.dtype('i4'), np.dtype('i1')) : _gp.Dict_i4_i1,
    (np.dtype('i4'), np.dtype('i2')) : _gp.Dict_i4_i2,
    (np.dtype('i4'), np.dtype('i4')) : _gp.Dict_i4_i4,
    (np.dtype('i4'), np.dtype('i8')) : _gp.Dict_i4_i8,
    (np.dtype('i4'), np.dtype('f4')) : _gp.Dict_i4_f4,
    (np.dtype('i4'), np.dtype('f8')) : _gp.Dict_i4_f8,
    (np.dtype('i4'), np.dtype('S8')) : _gp.Dict_i4_S8,
    (np.dtype('i4'), np.dtype('S16')) : _gp.Dict_i4_S16,
    (np.dtype('i8'), np.dtype('u1')) : _gp.Dict_i8_u1,
    (np.dtype('i8'), np.dtype('u2')) : _gp.Dict_i8_u2,
    (np.dtype('i8'), np.dtype('u4')) : _gp.Dict_i8_u4,
    (np.dtype('i8'), np.dtype('u8')) : _gp.Dict_i8_u8,
    (np.dtype('i8'), np.dtype('i1')) : _gp.Dict_i8_i1,
    (np.dtype('i8'), np.dtype('i2')) : _gp.Dict_i8_i2,
    (np.dtype('i8'), np.dtype('i4')) : _gp.Dict_i8_i4,
    (np.dtype('i8'), np.dtype('i8')) : _gp.Dict_i8_i8,
    (np.dtype('i8'), np.dtype('f4')) : _gp.Dict_i8_f4,
    (np.dtype('i8'), np.dtype('f8')) : _gp.Dict_i8_f8,
    (np.dtype('i8'), np.dtype('S8')) : _gp.Dict_i8_S8,
    (np.dtype('i8'), np.dtype('S16')) : _gp.Dict_i8_S16,
    (np.dtype('S8'), np.dtype('u1')) : _gp.Dict_S8_u1,
    (np.dtype('S8'), np.dtype('u2')) : _gp.Dict_S8_u2,
    (np.dtype('S8'), np.dtype('u4')) : _gp.Dict_S8_u4,
    (np.dtype('S8'), np.dtype('u8')) : _gp.Dict_S8_u8,
    (np.dtype('S8'), np.dtype('i1')) : _gp.Dict_S8_i1,
    (np.dtype('S8'), np.dtype('i2')) : _gp.Dict_S8_i2,
    (np.dtype('S8'), np.dtype('i4')) : _gp.Dict_S8_i4,
    (np.dtype('S8'), np.dtype('i8')) : _gp.Dict_S8_i8,
    (np.dtype('S8'), np.dtype('f4')) : _gp.Dict_S8_f4,
    (np.dtype('S8'), np.dtype('f8')) : _gp.Dict_S8_f8,
    (np.dtype('S8'), np.dtype('S8')) : _gp.Dict_S8_S8,
    (np.dtype('S8'), np.dtype('S16')) : _gp.Dict_S8_S16,
    (np.dtype('S16'), np.dtype('u1')) : _gp.Dict_S16_u1,
    (np.dtype('S16'), np.dtype('u2')) : _gp.Dict_S16_u2,
    (np.dtype('S16'), np.dtype('u4')) : _gp.Dict_S16_u4,
    (np.dtype('S16'), np.dtype('u8')) : _gp.Dict_S16_u8,
    (np.dtype('S16'), np.dtype('i1')) : _gp.Dict_S16_i1,
    (np.dtype('S16'), np.dtype('i2')) : _gp.Dict_S16_i2,
    (np.dtype('S16'), np.dtype('i4')) : _gp.Dict_S16_i4,
    (np.dtype('S16'), np.dtype('i8')) : _gp.Dict_S16_i8,
    (np.dtype('S16'), np.dtype('f4')) : _gp.Dict_S16_f4,
    (np.dtype('S16'), np.dtype('f8')) : _gp.Dict_S16_f8,
    (np.dtype('S16'), np.dtype('S8')) : _gp.Dict_S16_S8,
    (np.dtype('S16'), np.dtype('S16')) : _gp.Dict_S16_S16,
}

set_types = {
    np.dtype('u4') : _gp.Set_u4,
    np.dtype('u8') : _gp.Set_u8,
    np.dtype('i4') : _gp.Set_i4,
    np.dtype('i8') : _gp.Set_i8,
    np.dtype('S8') : _gp.Set_S8,
    np.dtype('S16') : _gp.Set_S16,
}

```
