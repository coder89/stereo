@echo off
set MATLAB=C:\PROGRA~1\MATLAB\R2013a
set MATLAB_ARCH=win64
set MATLAB_BIN="C:\Program Files\MATLAB\R2013a\bin"
set ENTRYPOINT=mexFunction
set OUTDIR=.\
set LIB_NAME=main_mex
set MEX_NAME=main_mex
set MEX_EXT=.mexw64
call mexopts.bat
echo # Make settings for main > main_mex.mki
echo COMPILER=%COMPILER%>> main_mex.mki
echo COMPFLAGS=%COMPFLAGS%>> main_mex.mki
echo OPTIMFLAGS=%OPTIMFLAGS%>> main_mex.mki
echo DEBUGFLAGS=%DEBUGFLAGS%>> main_mex.mki
echo LINKER=%LINKER%>> main_mex.mki
echo LINKFLAGS=%LINKFLAGS%>> main_mex.mki
echo LINKOPTIMFLAGS=%LINKOPTIMFLAGS%>> main_mex.mki
echo LINKDEBUGFLAGS=%LINKDEBUGFLAGS%>> main_mex.mki
echo MATLAB_ARCH=%MATLAB_ARCH%>> main_mex.mki
echo BORLAND=%BORLAND%>> main_mex.mki
echo OMPFLAGS= >> main_mex.mki
echo OMPLINKFLAGS= >> main_mex.mki
echo EMC_COMPILER=msvc110>> main_mex.mki
echo EMC_CONFIG=optim>> main_mex.mki
"C:\Program Files\MATLAB\R2013a\bin\win64\gmake" -B -f main_mex.mk
