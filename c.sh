rm *.map
rm skweeks.s
rm *.o
rm prg.tap

cc65 -Oirs --codesize 500 -t atmos skweeks.c
#cc65 -Cl -Ois --codesize 500 -t atmos skweeks.c
ca65 skweeks.s
ca65 keyboard.s
ld65 -o prg.tap -t atmos -m skweeks.map skweeks.o keyboard.o atmos.lib
printf '\xc7' | dd of=prg.tap bs=1 seek=7 count=1 conv=notrunc
cat tapes/LOAD2.tap tapes/CHARSTXT.tap prg.tap > skweeks.tap
