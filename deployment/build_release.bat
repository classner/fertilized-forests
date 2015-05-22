@echo off
cd ..
call setup_paths.bat
REM echo Refreshing ndarray.
REM start /wait cmd /C "scons --generate-ndarray"
echo Refreshing interfaces.
start /wait cmd /C "scons --generate-interfaces"
echo Refreshing documentation.
start /wait cmd /C "scons --generate-documentation"
echo Building Python version.
start /wait cmd /C "scons --with-serialization --with-python --with-caffe --with-caffe --caffe-model-dir=C:\caffe-models --temp-folder=c:\tmp --cpu-only --jobs=2"
REM Build the rest separately to not have Python dependencies.
echo Building core library, tests and C++ examples.
start /wait cmd /C "scons --with-serialization --with-tests --with-examples --with-caffe --caffe-model-dir=C:\caffe-models --temp-folder=c:\tmp --cpu-only --jobs=2"
echo Zipping.
copy deployment\README.MD README-BIN.MD
"C:\Program Files\7-Zip\7z" a fertilized-package.zip bin documentation fertilized_tests include lib Presentation pyfertilized license.txt README-BIN.MD
del README-BIN.MD
