from setuptools import setup, Extension

import os
import sys
import setuptools
import glob

__version__ = '0.15.1'

with open("README.md", "r") as readme_file:
    readme = readme_file.read()

extra_compile_args_dict = {
    'linux' : ['-w', '-std=c++17'],
    'linux2' : ['-w', '-std=c++17'],
    'darwin' : ['-w', '-std=c++17', '-stdlib=libc++'],
    'win32' : ['-w', '/std:c++17'],
}

ext_modules = [
  Extension(
    "_getpy",
    glob.glob('src/*.cpp'),
    include_dirs = ['lib/parallel-hashmap', 'lib/pybind11/include'],
    language = 'c++',
    extra_compile_args = extra_compile_args_dict[sys.platform],
    extra_link_args = [],
    define_macros = [('DOCTEST_CONFIG_DISABLE', None)]
  )
]

setup(
    name = 'getpy',
    version = __version__,
    author = 'Adam Moyer',
    author_email = 'atom.moyer@gmail.com',
    description = 'A Vectorized Dictionary for Python',
    packages = ['getpy'],
    package_dir={'getpy': 'getpy'},
    package_data={},
    ext_modules = ext_modules,
    install_requires = ['numpy', 'pybind11'],
    include_package_data=True,
    zip_safe = False,
    long_description=readme,
    long_description_content_type='text/markdown',
    url="https://github.com/atom-moyer/getpy",
    classifiers=[
        'Programming Language :: Python :: 3',
        'Programming Language :: C++',
        'Topic :: Scientific/Engineering',
        'Topic :: Software Development',
        'License :: OSI Approved :: MIT License',
        'Operating System :: Unix'
    ],
)
