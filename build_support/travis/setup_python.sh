
if [ "${PYTHON_VERSION}" = "2" ]; then
  if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
    sudo apt-get -y install python python-dev python-numpy
    export PYTHON_INCLUDE_DIR=/usr/include/python2.7
    export PYTHON_LIBRARY=/usr/lib/libpython2.7.so
    export PYTHON_EXECUTABLE=/usr/bin/python
  fi
fi
if [ "${PYTHON_VERSION}" = "3" ]; then
  if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
    # sudo find / -name "libboost_python*.so" 2>/dev/null
    sudo ln -s libboost_python-py32.so /usr/lib/libboost_python3.so
    sudo apt-get -y install python3 python3-dev python3-numpy
    export PYTHON_INCLUDE_DIR=/usr/include/python3.2
    export PYTHON_LIBRARY=/usr/lib/libpython3.2mu.so
    export PYTHON_EXECUTABLE=/usr/bin/python3
  fi
fi
