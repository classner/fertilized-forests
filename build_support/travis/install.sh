

if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
  # Boost and compiler.
  sudo apt-get -y install libboost-thread1.54-dev \
                          libboost-system1.54-dev \
                          libboost-test1.54-dev \
                          libboost-filesystem1.54-dev \
                          libboost-date-time1.54-dev \
                          libboost-serialization1.54-dev \
                          libboost-python1.54-dev \
                          build-essential g++-4.8
  # Cmake.
  export CC=/usr/bin/gcc-4.8
  export CXX=/usr/bin/g++-4.8
  export CMAKE_C_COMPILER=gcc-4.8
  export CMAKE_CXX_COMPILER=g++-4.8
  # export CC=/usr/bin/clang-3.6
  # export CXX=/usr/bin/clang++-3.6
  # export CMAKE_C_COMPILER=clang-3.6
  # export CMAKE_CXX_COMPILER=clang++-3.6
  wget --quiet http://www.cmake.org/files/v3.2/cmake-3.2.3-Linux-x86_64.sh
  chmod a+x cmake-3.2.3-Linux-x86_64.sh
  sudo ./cmake-3.2.3-Linux-x86_64.sh --skip-license --prefix=/usr/local
  export PATH=/usr/local/bin:$PATH
fi
if [ "${TRAVIS_OS_NAME}" = "osx" ]; then
  # Boost.
  brew outdated boost || brew upgrade boost
  brew install boost-python
  # Cmake.
  brew outdated cmake || brew upgrade cmake
fi

cmake --version

# Eigen3.
wget --quiet http://bitbucket.org/eigen/eigen/get/3.2.5.tar.gz
tar -xzvf 3.2.5.tar.gz 2>/dev/null
