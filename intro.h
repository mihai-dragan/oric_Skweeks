byte step = 0;
int addr;

byte rainbow[6] = { 1, 3, 2, 6, 4, 5};
char *intro_txt[] =  { "It's way past their bedtime and they",
"are mad, mean and angry!",
"Guide each of them to their respective",
"color sleeping pods to put them to",
"sleep." };
char *instr_txt[] = { "--Instructions--",
"Select skweek [RETURN]",
"Move left     [A]",
"Move right    [D]",
"Move up       [W]",
"Move down     [S]" };
char credit_odev1[] = "Original";
char credit_odev2[] = "game by";
char *credits_txt[] = { "Original programmers",
" [Aimga] Francois Mathieu",
" [ATARI ST] Xavier Monset",
" [ATARI ST] Pascal Caillaud",
" [PC] Karl Alexandre",
"Original artwork",
" Stephane Renaudin",
" Jean-Francois Rouchouse",
"Original sound and music",
" Fred Motte",
"Original designers",
" Didier Capdevielle, Pascal Gallon",
"Original project manager",
" Fabrice Armisen",
" ", " ",
"Oric gfx, sound, programming",
" Mihai Dragan" };

void animate() {
	byte i,c;
	step = step + 1;
	addr = 0xa640;
	for(i=0; i<step; i++) {
		c = step - i;
		if(c<7) POKE(addr,rainbow[c-1]);
		else POKE(addr,7);
		if(i<9) addr = addr + 40;
	}
}

void play_intro() {
	clock_t interval = CLOCKS_PER_SEC/10;
	clock_t sinterval = CLOCKS_PER_SEC/35;
    clock_t prevaclk = 0;
    clock_t prevsclk = 0;
    int addr = 0xAB41;
    byte sng_cntr = 0;
    byte play_song = 0;
	byte pat_pos = 0;
	byte pat_nr = 0;
	byte *pattern;
	unsigned int note = 0;
	unsigned int note_lead = 0;
	byte c = 0;
	byte i;
	while(1) {
		stop_sound();
		play_song = 0;
		clear__screen();
		step = 0;
		for(i=0; i<15; i++) POKE(0xa640+i*40,0);
		draw__spr(mik_logo, 8, 15, 0xa64f);
		load_instrA(zoom);
		playtime = 1;
		play_chanA(0);
		while(1) {
			if(kbhit()>0) {
				while(kbhit()>0) {
					c = cgetc();
					wait_centis(1);
				}
				stop_sound();
				return;
			}
			if(play_song) {
				if(sng_cntr == 75) {
					sng_cntr = 0;
					pattern = bass_sng[pat_nr];
					if(pattern[pat_pos]==0) note = 0;
					else note = freq_table[(pattern[pat_pos]>>4)-1][pattern[pat_pos]&15];
					pattern = lead_sng[pat_nr];
					if(pattern[pat_pos]==0) note_lead = 0;
					else note_lead = freq_table[(pattern[pat_pos]>>4)-1][pattern[pat_pos]&15];
					pat_pos = pat_pos + 1;
					if(pat_pos>pat_length) {
						pat_pos = 0;
						pat_nr = pat_nr + 1;
						if(pat_nr>nr_pats) {
							pat_nr = loop_start_sng;
						}
					}
					playtime = 0;
				}
				sng_cntr = sng_cntr + 1;
			}
			if(clock()-prevsclk > sinterval) {
				if(play_song) {
					if(note!=0) play_chanB(note);
					if(note_lead!=0) play_chanA(note_lead);
				}
				playtime = playtime + 1;
				prevsclk = clock();
			}
			if(clock()-prevaclk > interval) {
				if(step < 17) animate();
				else if(step==17) {
					for(i=9; i<15; i++) POKE(0xa640+i*40,7);
					draw__spr(loriciel_logo, 10, 36, 0xA91D);
					step = step + 1;
					stop_sound();
					load_instrA(boingbass);
					playtime = 1;
					play_chanA(880);
				} else {
					if(instruments[0].volume > 0 && step < 49) { instruments[0].volume = (49 - step)/2; w8912(AY_AmplitudeA, instruments[0].volume); }
					if(step==49) {
						clear_screen();
						init_aicCY();
						memcpy((char*)0xBF69,any_key,strlen(any_key));
						draw__spr(TS_title,24,25,0xa288);
						load_instrA(boingbass); load_instrB(boingbass); play_song = 1; playtime = 1;
						addr = 0xAB41;
						i = 0;
					}
					if(step==55) {
						if(i==0) { draw_spr(green_stay,0xA73E); i++; prevaclk = clock(); continue; }
						if(i==1) { draw_spr(blue_stay,0xA741); i++; prevaclk = clock(); continue; }
						if(i==2) { draw_spr(red_stay,0xA744); i++; prevaclk = clock();continue; }
						if(i==3) { draw_spr(yellow_stay,0xA747); i=0; }
					}
					if(step > 55 && step < 61) {
						if(i<strlen(intro_txt[step-56])) {
							draw_char(intro_txt[step-56][i]-32, addr+i); i++; prevaclk = clock(); continue;
						} else {
							i=0;
							addr = addr + 360;
						}
					}
					if(step > 60 && step < 67) {
						if(step == 61 && i==0) addr = addr + 360;
						if(i<strlen(instr_txt[step-61])) { draw_char(instr_txt[step-61][i]-32, addr+i); i++; prevaclk = clock(); continue;
						} else {
							i=0;
							addr = addr + 360;
						}
					}
					if(step==140) {
						clear_screen();
						init_aicCW();
						addr = 0xA141;
						memcpy((char*)0xBF69,any_key,strlen(any_key));
					}
					if(step==141) draw__spr(atreid_logo,6,56,0xA2C7);
					if(step==142) {
						if(i==0) { draw_string(credit_odev1,0xA01E); i++; prevaclk = clock(); continue; }
						if(i==1) { draw_string(credit_odev2,0xA15E); i=0;}
					}
					if(step>142 && step<161) {
						if(i<strlen(credits_txt[step-143])) { draw_char(credits_txt[step-143][i]-32, addr+i); i++; prevaclk = clock(); continue;
						} else {
							i=0;
							addr = addr + 360;
						}
					}
					if(step<255) step = step + 1;
					else break;
				}
				prevaclk = clock();
			}
		}
	}
}
