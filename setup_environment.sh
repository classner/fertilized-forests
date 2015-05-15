#!/bin/bash
# Author: Christoph Lassner.

echo "This is the Linux environment setup script of the fertilized-forests library.

It is a guided walkthrough through the requirement installations and setup options. It will (but only with your permission) install required software and create two files on success:

* setup_paths.sh
* compile.sh

You can use and modify them easily, since they are very short and simple to read. Use them to build the library afterwards.

This script only works on Debian systems (since it uses the 'apt-get' command)!
"

if [[ $1 == '--quiet' ]]; then
  echo "Quiet mode."
else
  echo "Press enter to continue."
  read a
fi

echo "Updating package cache..."
sudo apt-get update > /dev/null 2>&1
echo "Done."

##############################################
# Check for the availability of Python and pip

if [[ $9 != "" ]]; then
  echo "Using Python and Pip at:" $9
else
  if [[ `which python` != "" ]]; then
    echo "Using Python at: `which python`."
  else
    echo "No Python found on the command line! You can register an existing Python installation only for this script by running 'sudo PATH=\"/mypathtopython/bin:\$PATH\" ./setup_environment.sh' or by adding the line 'export PATH=\"/mypathtopython/bin:\$PATH\"' to your ~/.bashrc file permanently."

    if [[ $1 == '--quiet' ]]; then
      echo "Exiting..."
      exit 1
    else
      echo "
Alternatively, if you have no Python installed, should I install it by running 'apt-get install python python-dev python-pip' ('n' will exit)? [(y), n]"

  	read a
  	if [[ $a == "Y" || $a == "y" || $a = "" ]]; then
  	  echo "Installing..."
  	  sudo apt-get install python python-dev python-pip
  	  echo "Installation finished."
  	  if [[ `which python` == "" || `which pip` == "" ]]; then
  	    echo "Can not find python or pip on the command line. Installation apparently failed. You will have to fix this manually. Exiting..."
  	    exit 1
  	  fi
          else
            exit 1 
  	fi
    fi
  fi

  if [[ `which pip` != "" ]]; then
    echo "Using pip at: `which pip`."
  else
    if [[ $1 == '--quiet' ]]; then
      echo "Exiting..."
      exit 1
    else
      echo "No pip found! Should I install it by running 'apt-get install python-pip' ('n' will exit)? If you are using a Python distribution other than the system one, you will have to install it yourself! [(y), n]"

  	read a
  	if [[ $a == "Y" || $a == "y" || $a = "" ]]; then
  	  echo "Installing..."
  	  sudo apt-get install python-pip
  	  echo "Installation finished."
  	  if [[ `which python` == "" || `which pip` == "" ]]; then
  	    echo "Cannot find python or pip on the command line. Installation apparently failed. You will have to fix this manually. Exiting..."
  	    exit 1
  	  fi
          else
            exit 1 
  	fi
    fi
  fi
fi

################################
# Entering Python layer.
# Forwarding parameters.
# c.t. http://stackoverflow.com/questions/6962861/linux-shell-append-variable-parameters-to-command
for i in $@;
do
    params=" $params $i"
done
if [[ $9 != "" ]]; then
  $9/python setup_environment_linux.py $params
else
  python setup_environment_linux.py $params
fi
