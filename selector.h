char *select_txt[]	 = {"1 : Play Game",
	" ",
	"2 : Enter Password" };
char pass_txt[] = "Enter a Password  ........";
char illegal[] =  "Illegal Password          ";
char pass_sto[8];

byte check_pass() {
	byte i,j;
	j = 0; i = 0;
	for(j=j;j<NRLEVELS;) {
		if(keycodes[j][i] != pass_sto[i]) { 
			j++; if(j==NRLEVELS) return 255;
			i = 0;
		} else {
			i++; if(i==8) return j;
		}
	}
}

byte get_passwd() {
	byte c,i;
	memcpy((char*)0xBF69,pass_txt,strlen(pass_txt));
	i = 0;
	while(1) {
		if(kbhit()>0) {
			while(kbhit()>0) c = cgetc();
			if(c==CH_ESC) {
				i = 0;
				memcpy((char*)0xBF7B,"........",8);
			}
			if(c==CH_ENTER && i==8) {
				return check_pass();
			}
			if(c==CH_DEL && i!=0) {
				i = i - 1;
				POKE(0xBF7B+i,'.');
			}
			if(((c>64 && c<91)||(c>96 && c<123))&&i<8) {
				if(c>96) c = c - 32;
				pass_sto[i] = c;
				POKE(0xBF7B+i,c);
				i++;
			}
		}
	}
	return 0;
}

byte selector() {
	byte c,i, lvl;
	addr = 0xA712;
	clear__screen();
	memset((char*)0xBF68, ' ', 200);
	for(i=0; i<3; i++) { draw_string(select_txt[i],addr); addr = addr + 360;}
	while(1) {
		if(kbhit()>0) {
			while(kbhit()>0) {
				c = cgetc();
				if(c=='1') return 0;
				if(c=='2') {
					lvl = get_passwd();
					if(lvl == 255) {
						memcpy((char*)0xBF69,illegal,strlen(illegal));
						wait(2);
						memset((char*)0xBF69,' ',strlen(illegal));
					} else return lvl;
				}
			}
		}
	}
}
