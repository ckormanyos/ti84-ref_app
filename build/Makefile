##############################################################################80
#
#  Copyright Christopher Kormanyos 2024.
#  Distributed under The Unlicense.
#

##############################################################################80
#
# Makefile
#
# Build system for ti84-ref_app based on standard GNU tools
#
# Using GNU Make 4.2.1 (see version information in build log)
#
# 06-January-2024
#
# See also a definitive list of GCC command line options
# (for numerous target systems) here:
#   https://man7.org/linux/man-pages/man1/gcc.1.html
#
##############################################################################80


##############################################################################80
# paths
##############################################################################80

PATH_SRC        := $(CURDIR)/../src
PATH_BIN        := $(CURDIR)/../bin
PATH_OBJ        := $(CURDIR)/obj


##############################################################################80
# tools
##############################################################################80

ifeq ($(TYP_OS),)
TYP_OS          := UNIX
endif


ifeq ($(TYP_OS),WIN)
EXEEXT          := .exe
endif

ifeq ($(TYP_OS),UNIX)
EXEEXT          :=
endif


ifeq ($(TYP_OS),WIN)
TOOL_PREFIX     := $(CURDIR)/tools/UnxUtils/usr/local/wbin
TOOL_PREFIX     := $(TOOL_PREFIX)/

GNUMAKE         := $(CURDIR)/make$(EXEEXT)
endif

ifeq ($(TYP_OS),UNIX)
TOOL_PREFIX     :=

GNUMAKE         := make
endif


AS              := sdasz80$(EXEEXT)
CC              := sdcc$(EXEEXT)
CP              := $(TOOL_PREFIX)cp$(EXEEXT)
ECHO            := $(TOOL_PREFIX)echo$(EXEEXT)
MKDIR           := $(TOOL_PREFIX)mkdir$(EXEEXT)
MV              := $(TOOL_PREFIX)mv$(EXEEXT)
OBJCOPY         := $(TOOL_PREFIX)objcopy$(EXEEXT)
PYTHON          := python$(EXEEXT)
RM              := $(TOOL_PREFIX)rm$(EXEEXT)


ifeq ($(TYP_OS),WIN)
NULL_DEVICE     := NUL
$(NULL_DEVICE)  := NUL
endif

ifeq ($(TYP_OS),UNIX)
NULL_DEVICE     := /dev/null
$(NULL_DEVICE)  := /dev/null
endif


##############################################################################80
# flags
##############################################################################80

AFLAGS         := -p                       \
                  -g


CFLAGS         := --no-std-crt0            \
                  --code-loc 0x9D9B        \
                  --data-loc 0x0           \
                  --std-sdcc17             \
                  -mz80                    \
                  --reserve-regs-iy        \
                  -I$(PATH_SRC)


##############################################################################80
# make-command goals
##############################################################################80

.PHONY: all
all : clean version $(PATH_BIN)/refapp.8xp


##############################################################################80
# versions
##############################################################################80

.PHONY: version
version:
	@-$(ECHO)
	@-$(ECHO) +++ print compiler version
	@-$(CC) -v
	@-$(ECHO)
	@-$(ECHO) +++ print GNUmake version
	@-$(GNUMAKE) -v


##############################################################################80
# compile/link/hex-manip rules
##############################################################################80

$(PATH_BIN)/refapp.8xp :
	@-$(ECHO)
	@-$(ECHO) +++ assembling $(notdir $(PATH_SRC)/startup/crt0.s)
	@-$(AS) $(AFLAGS) -c -o $(PATH_OBJ)/crt0.rel $(PATH_SRC)/startup/crt0.s
	@-$(ECHO) +++ compiling $(notdir $(PATH_SRC)/app/app_util.c)
	@-$(CC) $(CFLAGS) -c -o $(PATH_OBJ)/app_util.rel $(PATH_SRC)/app/app_util.c
	@-$(ECHO) +++ compiling $(notdir $(PATH_SRC)/startup/clock.c)
	@-$(CC) $(CFLAGS) -c -o $(PATH_OBJ)/clock.rel $(PATH_SRC)/startup/clock.c
	@-$(ECHO) +++ compiling $(notdir $(PATH_SRC)/app/app_led.c) and linking/extracting to $(notdir $(PATH_BIN)/refapp.ihx)
	@-$(CC) $(CFLAGS) -o $(PATH_BIN)/refapp.ihx $(PATH_SRC)/app/app_led.c $(PATH_OBJ)/app_util.rel $(PATH_OBJ)/clock.rel $(PATH_OBJ)/crt0.rel
	@-$(ECHO) +++ creating binary $(notdir $(PATH_BIN)/refapp.bin)
	@-$(OBJCOPY) -Iihex -Obinary $(PATH_BIN)/refapp.ihx $(PATH_BIN)/refapp.bin
	@-$(ECHO) +++ creating on-calc app $(notdir $(PATH_BIN)/refapp.8xp)
	@-$(MV) $(PATH_BIN)/refapp.bin refapp.bin
	@-$(PYTHON) binpac8x.py refapp.bin
	@-$(MV) refapp.bin $(PATH_BIN)/refapp.bin
	@-$(MV) refapp.8xp $(PATH_BIN)/refapp.8xp


##############################################################################80
# Clean rule
##############################################################################80

.PHONY: clean
clean:
	@-$(ECHO)
	@-$(ECHO) +++ cleaning all
	@-$(MKDIR) -p $(PATH_BIN)
	@-$(MKDIR) -p $(PATH_OBJ)
	@-$(RM) -r $(PATH_BIN) 2>$(NULL_DEVICE)
	@-$(RM) -r $(PATH_OBJ) 2>$(NULL_DEVICE)
	@-$(MKDIR) -p $(PATH_BIN)
	@-$(MKDIR) -p $(PATH_OBJ)
