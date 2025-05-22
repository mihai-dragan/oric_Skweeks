void setup() {
	byte i;
    if(PEEK(0xC800))
            asm("jsr $EC33");       // HIRES in Atmos (ROM 1.1)
    else
            asm("jsr $E9BB");       // HIRES in Oric-1 (ROM 1.0)
    
    POKE(0x24E, 5);                 // set keyb delay 5 at #24E
    POKE(0x26A, 10);                // disable keyb click and caret blink with bitflag at #26A
	
	memset((char*)0xBF68, ' ', 200);  // Clear lower text area
	
	// initialize frequency table
	freq_table[1][0]=956;freq_table[1][1]=902;freq_table[1][2]=851;freq_table[1][3]=804;freq_table[1][4]=758;freq_table[1][5]=716;
	freq_table[1][6]=676;freq_table[1][7]=638;freq_table[1][8]=602;freq_table[1][9]=568;freq_table[1][10]=536;freq_table[1][11]=506;
	for(i=0; i<12; i++) freq_table[2][i] = freq_table[1][i]/2;
	for(i=0; i<12; i++) freq_table[3][i] = freq_table[1][i]/4;
	for(i=0; i<12; i++) freq_table[4][i] = freq_table[1][i]/8;
}

void init_aicCY() {
	int i;
	byte c = 0;
	for(i=0xa000; i<0xbf3f; i=i+40) { // setup AIC mode cyan/yellow
		if(c==0) { 
			POKE(i,6);
			c=1;
		} else {
			 POKE(i,3);
			 c = 0;
		}
	}
}

void init_aicCW() {
	int i;
	byte c = 0;
	for(i=0xa000; i<0xbf3f; i=i+40) { // setup AIC mode cyan/white
		if(c==0) { 
			POKE(i,6);
			c=1;
		} else {
			 POKE(i,7);
			 c = 0;
		}
	}
}

void clear__screen() {
	int i;
	int addr = 0xa000;
	for(i=0;i<200;i++) {
		memset((char*)addr,64,40);
		addr = addr + 40;
	}
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
