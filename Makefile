helloworld: helloworld.ihx
	objcopy -Iihex -Obinary helloworld.ihx helloworld.bin
	python binpac8x.py helloworld.bin
#	packihx helloworld.ihx > helloworld.hex

%.ihx:
	sdasz80 -p -g -o tios_crt0.rel tios_crt0.s
	sdcc -Ilibti --no-std-crt0 --code-loc 40347 --data-loc 0 --std-sdcc99 -mz80 --reserve-regs-iy -o $*.ihx tios_crt0.rel $*.c
#	sdcc -S --no-std-crt0 --code-loc 40347 --data-loc 0 --std-sdcc99 -mz80 --reserve-regs-iy -o $*.asm.tmp tios_crt0.rel $*.c
#	cat header.asm > $*.asm
#	cat $*.asm.tmp >> $*.asm
#	sdasz80	-plosgffw $*.rel $*.asm
#	sdldz80 -nf $*.lk

8xk:
	rabbitsign -t 8xk -g -o helloworld.8xk helloworld.hex

clean:
	if exist "helloworld.ihx" rm helloworld.ihx
	if exist "helloworld.noi" rm helloworld.noi
	if exist "helloworld.map" rm helloworld.map
	if exist "helloworld.rel" rm helloworld.rel
	if exist "helloworld.sym" rm helloworld.sym
	if exist "tios_crt0.rel"  rm tios_crt0.rel
	if exist "helloworld.bin" rm helloworld.bin
	if exist "helloworld.asm" rm helloworld.asm
	if exist "helloworld.lst" rm helloworld.lst
	if exist "helloworld.lk"  rm helloworld.lk
