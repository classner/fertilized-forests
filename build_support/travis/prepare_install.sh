

if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
  sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
  sudo add-apt-repository -y ppa:boost-latest/ppa
  sudo apt-get update -qq
  export CC=/usr/bin/gcc-4.8
  export CXX=/usr/bin/g++-4.8
fi
if [ "${TRAVIS_OS_NAME}" = "osx" ]; then
  sudo brew update
fi
