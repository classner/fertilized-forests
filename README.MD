# Fertilized Forests Decision Forest library

The fertilized forests library is a general purpose, platform independent, easy
to extend, Decision Forest library. You can find detailed information including
API documentation on [http://www.fertilized-forests.org](http://www.fertilized-forests.org).

## Build status

The construction branch is `unstable`. Only versions that are completely tested
get merged to `master`, so `master` is always always stable, with all tests
passing and all builds running. The current status of `unstable` is as follows:

* [![Build status](https://ci.appveyor.com/api/projects/status/ypw6pxe1sp26hv62?svg=true)](https://ci.appveyor.com/project/ChrislS/fertilized-forests) Build and tests, core library - Windows
* [![Jenkins](https://img.shields.io/jenkins/s/http/www.christophlassner.de/jenkins/fertilized-continuous-release-caffe.svg)]() Build and tests, core library, Python interface and caffe feature extraction

## Compilation & Installation

The project has a CMake build system. In the best case, the series of

    mkdir build
    cd build
    cmake ..
    cmake --build .
    cmake --build . --target test  # run the tests.
    cmake --build . --target install  # run the installation.

is sufficient to create the project in a `Release` configuration on all
platforms, including Windows. The build does require `Boost`, `Eigen` and
`OpenCV` to link against. Additionally, it offers to build Python and MATLAB
bindings and some more options. Hence, the following switches might be
interesting for you:

    -DCMAKE_BUILD_TYPE={Release|Debug}
    -DWITH_PYTHON={OFF|ON}
    -DWITH_MATLAB={OFF|ON}
    -DWITH_CAFFE={OFF|ON}

    -DBOOST_ROOT=...
    -DCAFFE_ROOT_DIR=...
    -DCAFFE_CPU_ONLY={OFF|ON}  # Must match the caffe compilation mode.

And there are many more fine-grained options for control. Simply open the
file `CMakeCache.txt` after you ran CMake for the first time. You can change
every variable in the file by adding a command line switch `-DVARNAME=VALUE`
to the CMake call.

## Developing

If you plan to extend or modify the library, please have a look at the
dedicated [developers guide](http://www.multimedia-computing.de/fertilized/pages/developers-guide.html).
There is a `fertilized-devtools` project that provides a code generator to
automatically keep the bindings and the serializationi code up-to-date.

## Troubleshooting

There is an [FAQ page](http://www.multimedia-computing.de/fertilized/pages/faq-troubleshooting.html)
on the homepage with many helpful tips. If you want to see how
environment setup in general works, see the files `appveyor.yaml` (Windows) or
`.travis.yaml` (Linux).

If all this fails or you find a bug, please post it on github!

_Hint_: When building with MATLAB on Linux, you might run into an issue with
MATLAB not finding GLIBCXX_X.Y.ZZ. It's a known issue of MATLAB and easy to fix.
You can find the solution [here](https://fantasticzr.wordpress.com/2013/05/29/matlab-error-libstdc-so-version-glibcxx_3-4-15-not-found/).
