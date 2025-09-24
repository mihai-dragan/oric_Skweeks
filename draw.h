void draw__spr(byte spr[], byte w, byte h, int haddr) {
    byte i;
    int b = 0;
    for(i=0;i<h;i++) {
        memcpy((char *)haddr, &spr[b], w); // draw one full line from frame
        b += w; // next line in frame
        haddr+=40; //next line on screen
    }
}

// draw one frame pointed to by spr, at screen address haddr
void draw_spr(byte spr[], int haddr) {
    byte i;
    int b = 0;
    for(i=0;i<spr_height;i++) {
        memcpy((char *)haddr, &spr[b], spr_bwidth); // draw one full line from frame
        b += spr_bwidth; // next line in frame
        haddr+=40; //next line on screen
    }
}

// draw a third of the rows from frame pointed to by spr, at screen address haddr
void draw_spr_rows(byte spr[], byte w, byte rowsnr, int haddr) {
	byte i,b;
	if(rowsnr==0) b=0;
	if(rowsnr==1) { haddr=haddr+240; b=18; }
	if(rowsnr==2) { haddr=haddr+480; b=36; }
    for(i=0;i<6;i++) {
		memcpy((char *)haddr, &spr[b], w);
        b += w; // next line in frame
        haddr+=40; //next line on screen
    }
}

// draw one column from frame pointed to by spr, at screen address haddr
void draw_spr_col(byte spr[], byte colnr, int haddr) {
	byte i;
    for(i=colnr;i<54;i+=spr_bwidth) {
		byte* addr = (byte*)haddr;
        *addr = spr[i];
        haddr+=40; //next line on screen
    }
}

// draw one frame pointed to by spr, at screen address haddr, with selection rectangle
void draw_selected(byte spr[], int haddr) {
    byte i;
    int b = 0;
    for(i=0;i<spr_height;i++) {
		if(i==0 || i==(spr_height-1)) memset((char *)haddr, 127, spr_bwidth); // draw one full line from frame
        else {
			memcpy((char *)haddr, &spr[b], spr_bwidth); // draw one full line from frame
			POKE(haddr,PEEK(haddr) | 32);
			POKE(haddr+spr_bwidth-1,PEEK(haddr+spr_bwidth-1) | 1);
		}
        b += spr_bwidth; // next line in frame
        haddr+=40; //next line on screen
    }
}

void draw_teleport(byte spr[], int haddr, byte step) {
	byte i;
    int b = 0;
    for(i=0;i<spr_height;i++) {
        if(i==step) memcpy((char *)haddr, &spr[b], spr_bwidth); // draw one full line from frame
        b += spr_bwidth; // next line in frame
        haddr+=40; //next line on screen
    }
}

void draw_char(byte cnum, int haddr) {
    byte i;
    unsigned int offst = cnum<<3;
    for(i=0;i<8;i++) {
        byte* addr = (byte*)haddr;
        *addr = 64+chr[offst+i];
        haddr=haddr+40;
    }
}

void draw_string(char str[], int haddr) {
	byte i;
	for(i=0; i<strlen(str); i++) draw_char(str[i]-32, haddr+i);
}
