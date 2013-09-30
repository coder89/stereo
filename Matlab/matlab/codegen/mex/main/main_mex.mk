START_DIR = C:\Users\spas\Desktop\matlab

MATLAB_ROOT = C:\PROGRA~1\MATLAB\R2013a
MAKEFILE = main_mex.mk

include main_mex.mki


SRC_FILES =  \
	main_data.c \
	main_initialize.c \
	main_terminate.c \
	main.c \
	cost_volume.c \
	imshift.c \
	power.c \
	sum.c \
	sqrt.c \
	abs.c \
	main_api.c \
	main_emxutil.c \
	main_mex.c

MEX_FILE_NAME_WO_EXT = main_mex
MEX_FILE_NAME = $(MEX_FILE_NAME_WO_EXT).mexw64
TARGET = $(MEX_FILE_NAME)

SYS_LIBS = 


#
#====================================================================
# gmake makefile fragment for building MEX functions using MSVC
# Copyright 2007-2012 The MathWorks, Inc.
#====================================================================
#
SHELL = cmd
OBJEXT = obj
CC = $(COMPILER)
LD = $(LINKER)
.SUFFIXES: .$(OBJEXT)

OBJLISTC = $(SRC_FILES:.c=.$(OBJEXT))
OBJLIST  = $(OBJLISTC:.cpp=.$(OBJEXT))

ifneq (,$(findstring $(EMC_COMPILER),msvc80 msvc90 msvc100 msvc100free msvc110 msvcsdk))
  TARGETMT = $(TARGET).manifest
  MEX = $(TARGETMT)
  STRICTFP = /fp:strict
else
  MEX = $(TARGET)
  STRICTFP = /Op
endif

target: $(MEX)

MATLAB_INCLUDES = /I "$(MATLAB_ROOT)\simulink\include"
MATLAB_INCLUDES+= /I "$(MATLAB_ROOT)\toolbox\shared\simtargets"
MATLAB_INCLUDES+= /I "$(MATLAB_ROOT)\rtw\ext_mode\common"
MATLAB_INCLUDES+= /I "$(MATLAB_ROOT)\rtw\c\src\ext_mode\common"
SYS_INCLUDE = $(MATLAB_INCLUDES)

# Additional includes

SYS_INCLUDE += /I "$(START_DIR)"
SYS_INCLUDE += /I "$(START_DIR)\codegen\mex\main"
SYS_INCLUDE += /I "$(MATLAB_ROOT)\extern\include"

DIRECTIVES = $(MEX_FILE_NAME_WO_EXT)_mex.arf

COMP_FLAGS = $(COMPFLAGS) $(OMPFLAGS) -DMX_COMPAT_32
LINK_FLAGS = $(filter-out /export:mexFunction, $(LINKFLAGS))
LINK_FLAGS += /NODEFAULTLIB:LIBCMT
ifeq ($(EMC_CONFIG),optim)
  COMP_FLAGS += $(OPTIMFLAGS) $(STRICTFP)
  LINK_FLAGS += $(LINKOPTIMFLAGS)
else
  COMP_FLAGS += $(DEBUGFLAGS)
  LINK_FLAGS += $(LINKDEBUGFLAGS)
endif
LINK_FLAGS += $(OMPLINKFLAGS)
LINK_FLAGS += /OUT:$(TARGET)
LINK_FLAGS += 

CFLAGS =  $(COMP_FLAGS) $(USER_INCLUDE) $(SYS_INCLUDE)
CPPFLAGS =  $(CFLAGS)

%.$(OBJEXT) : %.c
	$(CC) $(CFLAGS) "$<"

%.$(OBJEXT) : %.cpp
	$(CC) $(CPPFLAGS) "$<"

# Additional sources

%.$(OBJEXT) : $(START_DIR)/%.c
	$(CC) $(CFLAGS) "$<"

%.$(OBJEXT) : $(START_DIR)\codegen\mex\main/%.c
	$(CC) $(CFLAGS) "$<"



%.$(OBJEXT) : $(START_DIR)/%.cpp
	$(CC) $(CPPFLAGS) "$<"

%.$(OBJEXT) : $(START_DIR)\codegen\mex\main/%.cpp
	$(CC) $(CPPFLAGS) "$<"



$(TARGET): $(OBJLIST) $(MAKEFILE) $(DIRECTIVES)
	$(LD) $(LINK_FLAGS) $(OBJLIST) $(USER_LIBS) $(SYS_LIBS) @$(DIRECTIVES)
	@cmd /C "echo Build completed using compiler $(EMC_COMPILER)"

$(TARGETMT): $(TARGET)
	mt -outputresource:"$(TARGET);2" -manifest "$(TARGET).manifest"

#====================================================================

