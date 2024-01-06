
EXEEXT   := .exe

PATH_SRC = $(CURDIR)/../src
PATH_BIN = $(CURDIR)/../bin
PATH_OBJ = $(CURDIR)/obj

CP    := $(CURDIR)/tools/cp$(EXEEXT)
ECHO  := $(CURDIR)/tools/echo$(EXEEXT)
MKDIR := $(CURDIR)/tools/mkdir$(EXEEXT)
MV    := $(CURDIR)/tools/mv$(EXEEXT)
RM    := $(CURDIR)/tools/rm$(EXEEXT)


NULL_DEVICE     := NUL
$(NULL_DEVICE)  := NUL


all : $(PATH_BIN)/refapp.8xp


$(PATH_BIN)/refapp.8xp : clean
	sdasz80 -p -g -o $(PATH_OBJ)/crt0.rel $(PATH_SRC)/crt0.s
	sdcc --no-std-crt0 --code-loc 40347 --data-loc 0 --std-sdcc99 -mz80 --reserve-regs-iy -o $(PATH_BIN)/refapp.ihx $(PATH_OBJ)/crt0.rel $(PATH_SRC)/refapp.c
	objcopy -Iihex -Obinary $(PATH_BIN)/refapp.ihx $(PATH_BIN)/refapp.bin
	$(MV) $(PATH_BIN)/refapp.bin refapp.bin
	python binpac8x.py refapp.bin
	$(MV) refapp.bin $(PATH_BIN)/refapp.bin
	$(MV) refapp.8xp $(PATH_BIN)/refapp.8xp


clean:
	@-$(ECHO) +++ cleaning all
	@-$(MKDIR) -p $(PATH_BIN)
	@-$(MKDIR) -p $(PATH_OBJ)
	@-$(RM) -r $(PATH_BIN) 2>$(NULL_DEVICE)
	@-$(RM) -r $(PATH_OBJ) 2>$(NULL_DEVICE)
	@-$(MKDIR) -p $(PATH_BIN)
	@-$(MKDIR) -p $(PATH_OBJ)
