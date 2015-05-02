# Fertilized Forests Decision Forest library

The fertilized forests library is a general purpose, platform independent, easy
to extend, Decision Forest library. You can find detailed information including 
API documentation on [http://www.fertilized-forests.org](http://www.fertilized-forests.org).

## Build status

The construction branch is `unstable`. Only versions that are completely tested
get merged to `master`, so `master` is always always stable, with all tests passing and all builds running. The current status of `unstable` is as follows:

* [![Build Status](https://travis-ci.org/ChrislS/fertilized-forests.svg?branch=unstable)](https://travis-ci.org/ChrislS/fertilized-forests) Build and tests, core library - Linux
* [![Build status](https://ci.appveyor.com/api/projects/status/ypw6pxe1sp26hv62?svg=true)](https://ci.appveyor.com/project/ChrislS/fertilized-forests) Build and tests, core library - Windows
* [![Jenkins](https://img.shields.io/jenkins/s/http/www.christophlassner.de/jenkins/fertilized-continuous-release-caffe.svg)]() Build and tests, core library, Python interface and caffe feature extraction

## Compilation & Installation

Since the library is quite versatile and can link against [caffe](http://caffe.berkeleyvision.org), it potentially has many dependencies. For
your convenience, I created scripts for Windows with VS2013 and Linux to
completely setup the build environment.

#### Windows

The only remaining prerequisites are VS2013, a current Python 2.7 installation
and git. To build, open a VS2013 x64 command prompt in admin mode and run 

    git clone https://github.com/ChrislS/fertilized-forests.git
    cd fertilized-forests
    setup_environment.bat
    compile.bat

The `setup_environment.bat` will ask you questions about what and how to build,
so you can use your specific library versions if desired. The script creates
the files `setup_paths.bat` and `compile.bat`, which are easy to read and
modify. So even if you are using a different compiler than VS2013 you can
run the script to produce the files and replace the libraries with your own
ones.

#### Linux

Similar to Windows, there's also a configuration script ready. On Linux,
the requirements are a current Python 2.7 installation including pip.
Then run with elevated privileges

    git clone https://github.com/ChrislS/fertilized-forests.git
    cd fertilized-forests
    setup_environment.sh
    compile.sh

Similar to the Windows script, the script `setup_environment.sh` will create
the executable files `setup_paths.sh` and `compile.sh`, which are simple
to read and modify.

#### Mac OS and other

Even though not 'supported', compilation on Mac OS and in other constellations
should work. You can find detailed setup instructions on [the homepage](http://www.multimedia-computing.de/fertilized/pages/compiling.html).

## Troubleshooting

There is an [FAQ page](http://www.multimedia-computing.de/fertilized/pages/faq-troubleshooting.html) on the homepage with many helpful tips. If configuring
fails, always have a look at the file 'config.log'. If you want to see how
environment setup in general works, see the files `appveyor.yaml` (Windows) or
`.travis.yaml` (Linux).

If all this fails or you find a bug, please submit it on github. Even if you
find your experience worthy to share, don't hesitate to write so that I can
add it to the FAQ page.

_Hint_: When building with MATLAB on Linux, you might run into an issue about MATLAB not finding GLIBCXX_X.Y.ZZ. It's a known issue of MATLAB and easy to fix. You can
find the solution [here](https://fantasticzr.wordpress.com/2013/05/29/matlab-error-libstdc-so-version-glibcxx_3-4-15-not-found/).
