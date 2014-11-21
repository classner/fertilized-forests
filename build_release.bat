@echo off
echo Refreshing ndarray.
start /wait cmd /C "scons --generate-ndarray"
echo Refreshing interfaces.
start /wait cmd /C "scons --generate-interfaces"
echo Refreshing documentation.
start /wait cmd /C "scons --generate-documentation"
echo Building Python version.
start /wait cmd /C "scons --with-serialization --with-python --jobs=10"
REM Build the rest separately to not have Python dependencies.
echo Building core library, tests, C++ examples and Matlab interface.
start /wait cmd /C "scons --with-serialization --with-tests --with-examples --with-matlab --jobs=10"
echo Zipping.
"C:\Program Files\7-Zip\7z" a fertilized-package.zip bin CodeGenerator documentation external fertilized fertilized_tests include lib matfertilized Presentation pyfertilized SConsChecks fertilized.sln license.txt README.MD SConscript.py SConstruct version.py
