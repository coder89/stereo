@echo off
set MATLAB=C:\PROGRA~1\MATLAB\R2013a
set MATLAB_ARCH=win64
set MATLAB_BIN="C:\Program Files\MATLAB\R2013a\bin"
set ENTRYPOINT=mexFunction
set OUTDIR=.\
set LIB_NAME=cost_volume_mex
set MEX_NAME=cost_volume_mex
set MEX_EXT=.mexw64
call mexopts.bat
echo # Make settings for cost_volume > cost_volume_mex.mki
echo COMPILER=%COMPILER%>> cost_volume_mex.mki
echo COMPFLAGS=%COMPFLAGS%>> cost_volume_mex.mki
echo OPTIMFLAGS=%OPTIMFLAGS%>> cost_volume_mex.mki
echo DEBUGFLAGS=%DEBUGFLAGS%>> cost_volume_mex.mki
echo LINKER=%LINKER%>> cost_volume_mex.mki
echo LINKFLAGS=%LINKFLAGS%>> cost_volume_mex.mki
echo LINKOPTIMFLAGS=%LINKOPTIMFLAGS%>> cost_volume_mex.mki
echo LINKDEBUGFLAGS=%LINKDEBUGFLAGS%>> cost_volume_mex.mki
echo MATLAB_ARCH=%MATLAB_ARCH%>> cost_volume_mex.mki
echo BORLAND=%BORLAND%>> cost_volume_mex.mki
echo OMPFLAGS= >> cost_volume_mex.mki
echo OMPLINKFLAGS= >> cost_volume_mex.mki
echo EMC_COMPILER=msvc110>> cost_volume_mex.mki
echo EMC_CONFIG=optim>> cost_volume_mex.mki
"C:\Program Files\MATLAB\R2013a\bin\win64\gmake" -B -f cost_volume_mex.mk
