# Sparsepy
A Fast and Memory Efficient Sparse Hash Table for Python

The goal of Sparsepy is a simple to use and high performance python dictionary which integrates smoothly into the numpy/python ecosystem.

## About Sparsepy
Sparsepy is a thin and robust binding to the parallel_hashmap which is the current state of the art for minimal memory overhead and fast runtime speed. The binding layer is supported by PyBind11 which is fast to compile and simple to extend. Serialization is handled by Cereal which supports streaming binary serialization, a critical feature for the large hash tables this is designed to support.

## How to use Sparsepy
The `sparsepy.Dict` object is designed to maintain a similar interface to the standard python dictionary. There are some key differences though, which are necessary for performance reasons.

1) `sparsepy.Dict.__init__` has two arguments `key_type` and `value_type`. Those arguments are defined with a preset combinations of `np.dtype`s.  The full list of supported `np.dtype` combinations is found by `sparsepy._types`. Most of the future work on sparsepy will be expanding this list of supported types.

2) All of `sparsepy.Dict` methods support vectorization. Therefore, methods like `sparsepy.Dict.__getitem__`, `sparsepy.Dict.__setitem__`, and `sparsepy.Dict.__contains__` can be performed with `np.array(dtype)`.  That allows the performance critical for-loop to happen within the compiled c++.

3) `sparsepy.Dict.__getitem__` will throw an error if you attempt to retrieve a key that does not exist. Instead, you should first run `sparsepy.__contains__` on your key/array of keys, and then retrieve values corresponding to keys that exist. This is necessary for the vectorization support.

## Examples

### Simple Example
```
import numpy as np
import sparsepy as sp

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
```

### Vectorized Example
```
import numpy as np
import sparsepy as sp

key_type = np.dtype('u8')
value_type = np.int64

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
```

### Serialization Example
```
import numpy as np
import sparsepy as sp

key_type = np.dtype('u8')
value_type = np.int64

sp_dict_1 = sp.Dict(key_type, value_type)

keys = np.random.randint(1000, size=10, dtype=key_type)
values = np.random.randint(1000, size=10, dtype=value_type)
sp_dict_1[keys] = values

sp_dict_1.dump('test/test.hashtable.bin')

sp_dict_2 = sp.Dict(key_type, value_type)
sp_dict_2.load('test/test.hashtable.bin')

assert sp_dict_1 == sp_dict_2
```

