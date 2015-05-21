@echo off

echo This is the Windows environment setup script of the fertilized-forests library.
echo It is a guided walkthrough through the requirement installations and setup options. It will install required software and create/customize two files on success:
echo * setup_paths.bat
echo * compile.bat
echo You can use and modify them easily, since they are very short and simple to read. Use them to build the library afterwards.

REM Check for quiet mode.
if "%1" == "--quiet" (echo Quiet mode.) else (set /p a= Press enter to continue.)

REM ########################################################
REM Check for elevated privileges.

net session >nul 2>&1

if %errorLevel% == 0 (
  REM Nothing to do here.
) else (

  echo Elevated privileges are required to run this script!
  pause
  exit 1
)

REM ########################################################
REM Check for Python and pip.
where python >nul 2>&1
if %errorLevel% == 0 (
  REM Nothing to do here.
) else (
  echo python was not found on your PATH. Please
  echo install a Python distribution with pip! You could, for example,
  echo use the free "Anaconda Python (http://continuum.io/downloads)".
  pause
  exit 1
)

if "%1" == "--quiet" goto PIPCHECKCOMPLETE
where pip >nul 2>&1
if %errorLevel% == 0 (
  REM Nothing to do here.
) else (
  echo pip was not found on your PATH. Please
  echo install a Python distribution with pip or
  echo add pip to your existing installation.
  echo You could, for example, use the free 
  echo "Anaconda Python (http://continuum.io/downloads)".
  echo Installation instructions for pip can be
  echo found on https://pip.pypa.io/en/latest/installing.html.
  pause
  exit 1
)
:PIPCHECKCOMPLETE

REM ########################################################
REM Check for x64 cl.
where cl >nul 2>&1
if %errorLevel% == 0 (
  REM Nothing to do here.
) else (
  echo cl.exe, the Microsoft Visual C++ compiler, was not found
  echo on the PATH. Please open the shell using the Visual Studio
  echo Developer prompt in x64 mode. For Visual Studio 2013, this
  echo can be found in the folder 'Visual Studio Tools' in the start
  echo menu.
  pause
  exit 1
)

cl /? 2>&1 | findstr /C:"x64" > nul && goto FOUNDX64
  echo cl.exe is not in x64 mode! Please use the x64 command prompt!
:FOUNDX64

cl /? 2>&1 | findstr /C:"Version 18" > nul && goto VERSIONOK
  echo You are using a VS version other than VS2013! The following setup
  echo script can download and configure the dependency libraries only 
  echo for VS2013. However, you can for all steps download and build the
  echo dependencies yourself and specify the paths accordingly.
  pause

:VERSIONOK

REM ########################################################
REM Check for git.
set GITLOCATION="C:\\Program Files (x86)\\Git\\bin\\git.exe"

FOR %%i IN (%GITLOCATION%) DO IF EXIST %%~si goto :GITEXISTS
  echo git was not detected in C:\Program Files (x86)\Git\bin\git.exe . Please
  echo install git to its default folder from http://www.git-scm.com/download/win.
  pause
  exit 1

:GITEXISTS

REM ########################################################
REM Entering Python layer.
if "%1" == "--quiet" (
  %2\python setup_environment_windows.py %*
) else (
  python setup_environment_windows.py %*
)
