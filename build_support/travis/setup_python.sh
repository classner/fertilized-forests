
if [ "${PYTHON_VERSION}" = "2" ]; then
  # wget http://repo.continuum.io/miniconda/Miniconda-latest-Linux-x86_64.sh -O miniconda.sh
  # chmod +x miniconda.sh
  # ./miniconda.sh -b
  # export PYTHONPATH=/home/travis/miniconda/lib/python2.7/site-packages
  # export PYTHON_INCLUDE_DIR=/home/travis/miniconda/include/python2.7
  # export PYTHON_LIBRARY=/home/travis/miniconda/lib/libpython2.7.so
  # export MINICONDA_BIN=/home/travis/miniconda/bin
  sudo apt-get -y install python python-dev python-numpy python-sklearn
  export PYTHON_INCLUDE_DIR=/usr/include/python2.7
  export PYTHON_LIBRARY=/usr/lib/libpython2.7.so
  export PYTHON_EXECUTABLE=/usr/bin/python
fi
if [ "${PYTHON_VERSION}" = "3" ]; then
  # wget https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh -O miniconda.sh
  # chmod +x miniconda.sh
  # ./miniconda.sh -b
  sudo find / -name "libboost_python*.so" 2>/dev/null
  sudo ln -s libboost_python-py34.so /usr/lib/x86_64-linux-gnu/libboost_python3.so
  # export PYTHONPATH=/home/travis/miniconda3/lib/python3.4/site-packages
  # export PYTHON_INCLUDE_DIR=/home/travis/miniconda3/include/python3.4m
  # export PYTHON_LIBRARY=/home/travis/miniconda3/lib/libpython3.so
  # export MINICONDA_BIN=/home/travis/miniconda3/bin
  sudo apt-get -y install python3 python3-dev python3-pip python3-numpy
  sudo pip3 install --q scikit-learn
  export PYTHON_INCLUDE_DIR=/usr/include/python3.4m
  export PYTHON_LIBRARY=/usr/lib/x86_64-linux-gnu/libpython3.4m.so
  export PYTHON_EXECUTABLE=/usr/bin/python3
fi
# if [ ! "${PYTHON_VERSION}" = "none" ]; then
  # sudo ${MINICONDA_BIN}/conda update --yes --quiet conda
  # sudo ${MINICONDA_BIN}/conda install --yes --quiet numpy scikit-learn
  # export PATH=$MINICONDA_BIN:$PATH
  # sudo pip install --yes --quiet numpy scikit-learn
# fi
