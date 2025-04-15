#include <time.h>
#include <conio.h>
#include <string.h>
#include <peekpoke.h>
#define byte unsigned char
#include "sprites.h"
#include "levels.h"
#include "vars.h"
#include "utils.h"
#include "draw.h"
#include "move.h"
#include "load.h"
#include "animate.h"

void init_skweeks() {
	int i;
	for(i=0; i<8; i++) {
		skweeks[i].pos = 5;
		skweeks[i].steps = 0;
		skweeks[i].action = STAY;
		skweeks[i].movedir = STAY;
	}
}

void main() {
    byte c;
    clock_t interval = CLOCKS_PER_SEC/30;
    clock_t prevaclk = 0;
    clock_t prevsclk = 0;
    setup();
    init_skweeks();
    while(1) {
		for(c=0; c<kbhit(); c++) cgetc();
		load_level();
		player = &skweeks[cur_player];
        memcpy((char*)0xBF69,statxt,39);
		POKE(0xbf7a,48+(lives/10)); POKE(0xbf7b,48+(lives%10));
		POKE(0xbf83,48+(curlevel/100));	POKE(0xbf84,48+(curlevel/10)); POKE(0xbf85,48+(curlevel%10));
        POKE(0xbf8e,48+(jokers/10)); POKE(0xbf8f,48+(jokers%10));
		lvltime = lvlsec[curlevel];
		min2 = lvltime/600; min1 = (lvltime/60)%10; secs2 = (lvltime%60)/10 ; secs1 = (lvltime%60)%10;
		while(notsleeping > 0 && restartlvl == 0) {
			if(clock()-prevsclk > CLOCKS_PER_SEC) {
				lvltime = lvltime - 1;
				if(lvltime<1) restartlvl = 1;
				secs1 = secs1-1;
				if(secs1==255) { secs1=9; 
					secs2=secs2-1;
					if(secs2==255) { secs2 = 5;
						min1 = min1-1;
						if(min1==255) { min1 = 9;
							min2 = min2-1;
						}
					}
				}
				POKE(0xbf6e, 48+min2); POKE(0xbf6f, 48+min1);
				POKE(0xbf71, 48+secs2);	POKE(0xbf72, 48+secs1);
				prevsclk = clock();
			}
			if(clock()-prevaclk > interval) {
				if(kbhit()>0 && (player->action==STAY || player->action==SLEEP)) {
					c = cgetc();
					if(c=='d' && (byte)(lvlgrid[player->gridpos+1]<<5)==0) {
						if(player->action == SLEEP) notsleeping = notsleeping + 1;
						player->action = MOVE;
						player->movedir = RIGHT;
					}
					if(c=='a' && (byte)(lvlgrid[player->gridpos-1]<<5)==0) {
						if(player->action == SLEEP) notsleeping = notsleeping + 1;
						player->action = MOVE;
						player->movedir = LEFT;
					}
					if(c=='s' && (byte)(lvlgrid[player->gridpos+13]<<5)==0) {
						if(player->action == SLEEP) notsleeping = notsleeping + 1;
						player->action = MOVE;
						player->movedir = DOWN;
						need_cdclean = 1;
					}
					if(c=='w' && (byte)(lvlgrid[player->gridpos-13]<<5)==0) {
						if(player->action == SLEEP) notsleeping = notsleeping + 1;
						player->action = MOVE;
						player->movedir = UP;
						need_cdclean = 1;
					}
					if(c==CH_ENTER) {
						cur_player = cur_player + 1;
						if(!(cur_player<nr_skweeks)) cur_player = 0;
						player = &skweeks[cur_player];
						player->action = SELECT;
						while(kbhit()>0) wait_centis(1);
					}
					if(c==CH_ESC) {
						restartlvl = 1;
					}
				}
				animate_sprite(player);
				if(notsleeping == 0) animate_sprite(player);
				prevaclk = clock();
			}
		}
		wait(1);
		clear_screen();
		if(restartlvl == 1) {
			lives = lives - 1;
			if(lives==0) {
				POKE(0xbf7b,'0');
				draw__spr(youlost, 10, 10, 0xa64f);
				return;
			} else draw__spr(tryagain,10,10, 0xa650);
            restartlvl = 0;
		} else {
            curlevel = curlevel + 1;
            if(curlevel==NRLEVELS) {
                draw__spr(youwon, 10, 10, 0xa64f);
                return;
            } else draw__spr(bravo, 10, 20, 0xa64f);
        }
		wait(3);
		clear_screen();
    }
}
