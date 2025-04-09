rm *.map
rm *.s
rm *.o

cc65 -Oirs --codesize 500 -t atmos skweeks.c
#cc65 -Cl -Ois --codesize 500 -t atmos skweeks.c
ca65 skweeks.s
ld65 -o skweeks.tap -t atmos -m skweeks.map skweeks.o atmos.lib
