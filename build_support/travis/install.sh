

if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
  ## C++ libraries and compiler.
  sudo apt-get -y install libboost-thread1.54-dev \
                          libboost-system1.54-dev \
                          libboost-test1.54-dev \
                          libboost-filesystem1.54-dev \
                          libboost-date-time1.54-dev \
                          libboost-serialization1.54-dev \
                          libboost-python1.54-dev \
                          build-essential g++-4.8
fi
# if [ "${TRAVIS_OS_NAME}" = "osx" ]; then
#   # brew outdated <package-name> || brew upgrade <package-name>
# fi

# Eigen3.
wget http://bitbucket.org/eigen/eigen/get/3.2.5.tar.gz
tar -xzvf 3.2.5.tar.gz
# Python (must be setup after boost was installed).
source ../build_support/travis/setup_python.sh
# CMake.
if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
  export CMAKE_C_COMPILER=gcc-4.8
  export CMAKE_CXX_COMPILER=g++-4.8
  wget –quiet ttp://www.cmake.org/files/v3.2/cmake-3.2.3-Linux-x86_64.sh
  chmod a+x cmake-3.2.3-Linux-x86_64.sh
  sudo ./cmake-3.2.3-Linux-x86_64.sh --skip-license --prefix=/usr/local
  export PATH=/usr/local/bin:$PATH
fi
if [ "${TRAVIS_OS_NAME}" = "osx" ]; then
  wget –quiet https://cmake.org/files/v3.3/cmake-3.3.2.tar.gz
  tar -xzvf cmake-3.3.2.tar.gz 2>/dev/null
  cd cmake-3.3.2
  ./configure 2>/dev/null && make && sudo make install
  export PATH=/usr/local/bin:$PATH
  cd ..
fi

cmake --version
