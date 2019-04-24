from setuptools import setup, Extension

import os
import sys
import setuptools
import glob

__version__ = '0.9.4'

with open("README.md", "r") as readme_file:
    readme = readme_file.read()

extra_compile_args_dict = {
    'linux' : ['-w', '-ftemplate-backtrace-limit=0', '-std=c++17'],
    'linux2' : ['-w', '-ftemplate-backtrace-limit=0', '-std=c++17'],
    'darwin' : ['-w', '-ftemplate-backtrace-limit=0', '-std=c++17', '-stdlib=libc++'],
}

ext_modules = [
  Extension(
    "_getpy",
    glob.glob('src/*.cpp'),
    include_dirs = ['lib/parallel-hashmap', 'lib/pybind11/include', 'lib/cereal/include', 'lib/half'],
    language = 'c++',
    extra_compile_args = extra_compile_args_dict[sys.platform],
    extra_link_args = ['-lz'],
    define_macros = [('DOCTEST_CONFIG_DISABLE', None)]
  )
]

setup(
    name = 'getpy',
    version = __version__,
    author = 'Adam Moyer',
    author_email = 'atom.moyer@gmail.com',
    description = 'A Simple, Fast, and Small Hash Map for Python',
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
