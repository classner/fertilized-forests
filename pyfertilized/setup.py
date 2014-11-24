# -*- coding: utf-8 -*-
"""
The python setup script for the python project.

The project must have been built using the SCONS script, before calling
`python setup.py install`.

Created on Tue Mar 04 14:23:00 2014

@author: Christoph Lassner
"""
from distutils.core import setup
import sys
import os
import platform
from glob import glob

# Import version
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from version import VERSION

if platform.system() == 'Windows':
  ext_files = ['pyfertilized.pyd']
  bindeps = glob(os.path.join(os.path.dirname(__file__), 'fertilized', '*.dll'))
  ext_files.extend([os.path.basename(fname) for fname in bindeps])
else:
  ext_files = ['libfertilized.so',
               'libboost_numpy.so',
               'pyfertilized.so']

setup(
    name = 'fertilized',
    author = 'Christoph Lassner',
    author_email = 'Christoph.Lassner@informatik.uni-augsburg.de',
    url = 'http://www.fertilized-forests.org',
    package_dir = {'fertilized': 'fertilized'},
    packages=['fertilized'],
    package_data={'fertilized': ext_files},
    version = VERSION,
    license='BSD 2-clause'
)
