from setuptools import setup, Extension

import os
import sys
import setuptools
import glob

__version__ = '0.0.1'

os.environ["CC"] = "gcc"
os.environ["CXX"] = "g++"

extra_compile_args_dict = {
    'linux' : ['-w', '-std=c++14'],
    'linux2' : ['-w', '-std=c++14'],
    'darwin' : ['-w', '-std=c++14'],
}

ext_modules = [
  Extension(
    "_sparsepy",
    glob.glob('src/_sparsepy.cpp'),
    include_dirs = ['lib/sparsepp/sparsepp', 'lib/pybind11/include', 'lib/brigand/include', 'lib/msgpack-c/include'],
    language = 'c++',
    extra_compile_args = extra_compile_args_dict[sys.platform],
    extra_link_args = ['-lz'],
    define_macros = [('DOCTEST_CONFIG_DISABLE', None)]
  )
]

setup(
    name = 'sparsepy',
    version = __version__,
    author = 'Adam Moyer',
    author_email = 'atom.moyer@gmail.com',
    url = None,
    description = 'Fast and Memory Efficient Sparse Hash Tables for Python',
    packages = ['sparsepy'],
    package_dir={'atom': 'atom'},
    package_data={},
    ext_modules = ext_modules,
    install_requires = ['pytest', 'pybind11'],
    include_package_data=True,
    zip_safe = False,
)
