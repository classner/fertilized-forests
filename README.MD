# Fertilized Forests Decision Forest library

This project is currently being developed at the [Multimedia Computing
and Computer Vision Lab](http://www.multimedia-computing.de) at the
[University of Augsburg](http://www.uni-augsburg.de).

You can find detailed information including API documentation on
[http://www.fertilized-forests.org](http://www.fertilized-forests.org).


## Installation

For Windows, you can find a pre-compiled ready to use package to
download [here](http://www.multimedia-computing.de/fertilized/pages/download.html).

For Linux and Mac OS, it is necessary to compile from source. Detailed
instructions can be found [here](http://www.multimedia-computing.de/fertilized/pages/compiling.html),
but I'll quickly sum up the steps for Ubuntu here:

* Install the prerequisites:

~~~~~
# Workaround for Ubuntu 13.10 so that OpenCL (an OpenCV dependency)
# does not pull in the nvidia drivers. Run only if you work on
# Ubuntu 13.10 and you are not using the proprietary nvidia drivers.
# http://askubuntu.com/questions/365897/how-to-install-opencv-without-nvidia-drivers
sudo apt-get install ocl-icd-libopencl1

# Install system dependencies.
sudo apt-get install m4 doxygen libboost-all-dev libeigen3-dev \
  python python-dev python-pip python-ply python-scipy \
  python-numpy build-essential libopencv-dev scons

# Install Python dependencies.
sudo pip install jinja2 cppheaderparser pillow \
  scikit-image matplotlib scikit-learn
~~~~~

* Download the source from github:

~~~~~
git clone https://github.com/ChrislS/fertilized-forests.git
cd fertilized-forests
~~~~~

* Get the required submodules:

~~~~~
git submodule update --init --recursive
~~~~~

* Set the EIGEN library include folder:

~~~~~
# For older Ubuntu versions, this must be /usr/local/include/eigen3
export EIGEN_ROOT=/usr/include/eigen3
~~~~~

* Compile and install

~~~~~
scons --generate-interfaces
scons --with-serialization --with-tests --with-examples
# Optional: install to your library and include folders
sudo scons --with-serialization install
# Optional: Matlab interface:
scons --with-serialization --with-matlab
# Optional: Python interface:
scons --with-serialization --with-python
cd pyfertilized && python setup.py install && cd ..
# Optional: generate the doxygen documentation
scons --generate-documentation
~~~~~
