

if [ "${TRAVIS_OS_NAME}" = "linux" ]; then
  sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
  sudo add-apt-repository -y ppa:h-rayflood/llvm-upper
  sudo add-apt-repository -y ppa:boost-latest/ppa
  sudo apt-get update -qq
fi
if [ "${TRAVIS_OS_NAME}" = "osx" ]; then
  sudo brew update
fi
