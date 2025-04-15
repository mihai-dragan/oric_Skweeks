void setup() {
	int i;
	byte c = 0;
    if(PEEK(0xC800))
            asm("jsr $EC33");       // HIRES in Atmos (ROM 1.1)
    else
            asm("jsr $E9BB");       // HIRES in Oric-1 (ROM 1.0)
    
    POKE(0x24E, 5);                 // set keyb delay 5 at #24E
    POKE(0x26A, 10);                // disable keyb click and caret blink with bitflag at #26A
    for(i=0xa000; i<0xbf3f; i=i+40) { // setup AIC mode yellow/cyan
		if(c==0) { 
			POKE(i,6);
			c=1;
		} else {
			 POKE(i,3);
			 c = 0;
		}
	}
	POKE(0xbf68, 7); // set white ink for first text line
	memset((char*)0xBF69, 0, 119);  // Clear lower text area
}

void clear_screen() {
	int i;
	int addr = 0xa001;
	for(i=0;i<200;i++) {
		memset((char*)addr,64,39);
		addr = addr + 40;
	}
}

void wait_centis(int centisecs) {
	clock_t clk = clock();
	while(clock()-clk < centisecs) {
		clock();
	}
}

void wait(int sec) {
	clock_t clk = clock();
	while(sec>((clock()-clk)/CLOCKS_PER_SEC)) {
		clock();
	}
}
