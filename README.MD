# Fertilized Forests Decision Forest library

The fertilized forests library is a general purpose, platform independent, easy
to extend, Decision Forest library. You can find detailed information including
API documentation on [http://www.fertilized-forests.org](http://www.fertilized-forests.org).

## Build status

The construction branch is `unstable`. Only versions that are completely tested
get merged to `master`, so `master` is always always stable, with all tests
passing and all builds running.

**The current status of `unstable` is as follows:**

* [![Windows build status](https://ci.appveyor.com/api/projects/status/ypw6pxe1sp26hv62?svg=true)](https://ci.appveyor.com/project/classner/fertilized-forests) Build and tests, core library - Windows
* [![Linux & Mac build Status](https://travis-ci.org/classner/fertilized-forests.svg?branch=unstable)](https://travis-ci.org/classner/fertilized-forests) Build and tests, core library and Python interface - Linux & Mac OS

## Compilation & Installation

The project has a CMake build system. The series of

    mkdir build
    cd build
    cmake ..
    cmake --build . # add `--config Release` for Windows
    cmake --build . --target test  # run the tests (with `--target run_tests` and `--config Release` on Windows).
    cmake --build . --target install  # run the installation (... for Windows).

is sufficient to create the project in a `Release` configuration on all
platforms.

The build does require `Boost` and `Eigen` to link against.
Additionally, it offers to have feature extraction with OpenCV, and
to build Python and MATLAB bindings. Hence, the following switches might be
interesting for you:

    -DCMAKE_BUILD_TYPE={Release|Debug}
    -DWITH_PYTHON={OFF|ON}
    -DWITH_MATLAB={OFF|ON}
    -DWITH_CAFFE={OFF|ON}

    -DBOOST_ROOT=...
    -DEIGEN3_INCLUDE_DIR=...
    -DCAFFE_ROOT_DIR=...
    -DCAFFE_CPU_ONLY={OFF|ON}  # Must match the caffe compilation mode.

And there are many more fine-grained options for control. Simply open the
file `CMakeCache.txt` after you ran CMake for the first time. You can change
every variable in the file by adding a command line switch `-DVARNAME=VALUE`
to another CMake call to adjust the configuration.

## Developing

If you plan to extend or modify the library, please have a look at the
dedicated [developers guide](http://www.multimedia-computing.de/fertilized/pages/developers-guide.html).
There is a [fertilized-devtools](https://github.com/classner/fertilized-devtools)
project that provides a code generator to
automatically keep the bindings and the serialization code up-to-date.

## Troubleshooting

There is an [FAQ page](http://www.multimedia-computing.de/fertilized/pages/faq-troubleshooting.html)
on the homepage with many helpful tips. If you want to see how
environment setup in general works, see the files `appveyor.yaml` (Windows) or
`.travis.yaml` (Linux).

If all this fails or you find a bug, please report it on github to let the
community know and get it fixed!

_Hint_: When building with MATLAB on Linux, you might run into an issue with
MATLAB not finding GLIBCXX_X.Y.ZZ. It's a known issue of MATLAB and easy to fix.
You can find the solution [here](https://fantasticzr.wordpress.com/2013/05/29/matlab-error-libstdc-so-version-glibcxx_3-4-15-not-found/).

_Hint_: When building the Python bindings for Python 3 on Linux, you might
have to

    cd /usr/lib/x86_64-linux-gnu/
    sudo ln -s libboost_python-py3[X].so libboost_python3.so

where [X] must be replaced with the appropriate value. This should solve the
problem that `boost_python3` can not be found.
