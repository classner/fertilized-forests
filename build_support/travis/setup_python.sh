
if [ "${PYTHON_VERSION}" = "2" ]; then
  wget http://repo.continuum.io/miniconda/Miniconda-latest-Linux-x86_64.sh -O miniconda.sh
  chmod +x miniconda.sh
  ./miniconda.sh -b
  export PYTHONPATH=/home/travis/miniconda/lib/python2.7/site-packages
  export PYTHON_INCLUDE_DIR=/home/travis/miniconda/include/python2.7
  export PYTHON_LIBRARY=/home/travis/miniconda/lib/libpython2.7.so
fi
if [ "${PYTHON_VERSION}" = "3" ]; then
  wget https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh -O miniconda.sh
  chmod +x miniconda.sh
  ./miniconda.sh -b
  export PYTHONPATH=/home/travis/miniconda/lib/python3.4/site-packages
  export PYTHON_INCLUDE_DIR=/home/travis/miniconda/include/python3.4m
  export PYTHON_LIBRARY=/home/travis/miniconda/lib/libpython3.so
fi
if [ ! "${PYTHON_VERSION}" = "none" ]; then
  export MINICONDA_BIN=/home/travis/miniconda/bin
  sudo /home/travis/miniconda/bin/conda update --yes --quiet conda
  sudo /home/travis/miniconda/bin/conda install --yes --quiet numpy scipy pillow scikit-image matplotlib scikit-learn
  export PATH=$MINICONDA_BIN:$PATH
fi
