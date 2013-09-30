@echo off
set MATLAB=C:\PROGRA~1\MATLAB\R2013a
set MATLAB_ARCH=win64
set MATLAB_BIN="C:\Program Files\MATLAB\R2013a\bin"
set ENTRYPOINT=mexFunction
set OUTDIR=.\
set LIB_NAME=imshift_mex
set MEX_NAME=imshift_mex
set MEX_EXT=.mexw64
call mexopts.bat
echo # Make settings for imshift > imshift_mex.mki
echo COMPILER=%COMPILER%>> imshift_mex.mki
echo COMPFLAGS=%COMPFLAGS%>> imshift_mex.mki
echo OPTIMFLAGS=%OPTIMFLAGS%>> imshift_mex.mki
echo DEBUGFLAGS=%DEBUGFLAGS%>> imshift_mex.mki
echo LINKER=%LINKER%>> imshift_mex.mki
echo LINKFLAGS=%LINKFLAGS%>> imshift_mex.mki
echo LINKOPTIMFLAGS=%LINKOPTIMFLAGS%>> imshift_mex.mki
echo LINKDEBUGFLAGS=%LINKDEBUGFLAGS%>> imshift_mex.mki
echo MATLAB_ARCH=%MATLAB_ARCH%>> imshift_mex.mki
echo BORLAND=%BORLAND%>> imshift_mex.mki
echo OMPFLAGS= >> imshift_mex.mki
echo OMPLINKFLAGS= >> imshift_mex.mki
echo EMC_COMPILER=msvc110>> imshift_mex.mki
echo EMC_CONFIG=optim>> imshift_mex.mki
"C:\Program Files\MATLAB\R2013a\bin\win64\gmake" -B -f imshift_mex.mk
