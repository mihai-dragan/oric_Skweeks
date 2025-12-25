#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <peekpoke.h>
#define byte unsigned char
#include "sprites.h"
#include "levels.h"
#include "song.h"
#include "instr.h"
#include "vars.h"
#include "utils.h"
#include "draw.h"
#include "sound.h"
#include "move.h"
#include "load.h"
#include "animate.h"
#include "intro.h"
#include "selector.h"

unsigned char __near__ GetKey (unsigned char code);

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
    byte c, i, keycode, keycount;
    clock_t interval = CLOCKS_PER_SEC/30;
    clock_t prevaclk = 0;
    clock_t prevsclk = 0;
    keycount = 0;
    while(1) {
        setup();
        play_intro();
        curlevel = selector();
        clear_screen();
        init_aicCY();
        zoom[6] = 0xf;
        restartlvl = 0;
        lives = 3;
        while(1) {
            tele_grid[0][0]=0;tele_grid[1][0]=0;tele_grid[2][0]=0;tele_grid[3][0]=0;
            init_skweeks();
            load_level();
            player = &skweeks[cur_player];
            while(notsleeping > 0 && restartlvl == 0) {
                if(player->action==STAY || player->action==SLEEP) {
					object_under = lvlgrid[player->gridpos]>>3;
					if(object_under!=8 && object_under!=9 && object_under!=10 && object_under!=11) { // can't move if stopped over arrow
						if(GetKey(15)/*d*/ && (byte)(lvlgrid[player->gridpos+1]<<5)==0) {
                            if(keycount==0 || keycode!=15) { 
                                if(keycount==0) keycount++; else keycount = 0;
                                if(keycode!=15) keycode = 15;
                            } else {
                                if(player->action == SLEEP) notsleeping = notsleeping + 1;
                                player->movedir = RIGHT; 
                                if(lvlgrid[player->gridpos+1]==0x80) { player->action = BUMP; cur_bumper_pos = player->pos+3; cur_bumper_frame = 1; }
                                else player->action = MOVE;
                                keycount == 0;
                            }
						}
						if(GetKey(53)/*a*/ && (byte)(lvlgrid[player->gridpos-1]<<5)==0) {
                            if(keycount==0 || keycode!=53) { 
                                if(keycount==0) keycount++; else keycount = 0;
                                if(keycode!=53) keycode = 53;
                            } else {
                                if(player->action == SLEEP) notsleeping = notsleeping + 1;
                                player->movedir = LEFT;
                                if(lvlgrid[player->gridpos-1]==0x80) { player->action = BUMP; cur_bumper_pos = player->pos-3; cur_bumper_frame = 1; }
                                else player->action = MOVE;
                                keycount == 0;
                            }
						}
						if(GetKey(54)/*s*/ && (byte)(lvlgrid[player->gridpos+13]<<5)==0) {
                            if(keycount==0 || keycode!=54) { 
                                if(keycount==0) keycount++; else keycount = 0;
                                if(keycode!=54) keycode = 54;
                            } else {
                                if(player->action == SLEEP) notsleeping = notsleeping + 1;
                                player->movedir = DOWN;
                                if(lvlgrid[player->gridpos+13]==0x80) { player->action = BUMP; cur_bumper_pos = player->pos+720; cur_bumper_frame = 1; }
                                else { player->action = MOVE; need_cdclean = 1; }
                                keycount == 0;
                            }
						}
						if(GetKey(55)/*w*/ && (byte)(lvlgrid[player->gridpos-13]<<5)==0) {
                            if(keycount==0 || keycode!=55) { 
                                if(keycount==0) keycount++; else keycount = 0;
                                if(keycode!=55) keycode = 55;
                            } else {
                                if(player->action == SLEEP) notsleeping = notsleeping + 1;
                                player->movedir = UP;
                                if(lvlgrid[player->gridpos-13]==0x80) { player->action = BUMP; cur_bumper_pos = player->pos-720; cur_bumper_frame = 1; }
                                else { player->action = MOVE; need_cdclean = 1; }
                                keycount == 0;
                            }
						}
					}
                    if(GetKey(61)/*Return*/) {
                        if(keycount==0 || keycode!=61) { 
                            if(keycount==0) keycount++; else keycount = 0;
                            if(keycode!=61) keycode = 61;
                        } else {
                            cur_player = cur_player + 1;
                            if(!(cur_player<nr_skweeks)) cur_player = 0;
                            player = &skweeks[cur_player];
                            player->action = SELECT;
                            player->steps = 0;
                            keycount == 0;
                        }
                    }
                    if(GetKey(13)/*Esc*/) {
                        // debug: puttext(0xBFB9,"Esc!"); wait(10);
                        if(keycount==0 || keycode!=13) { 
                            if(keycount==0) keycount++; else keycount = 0;
                            if(keycode!=13) keycode = 13;
                        } else {
                            restartlvl = 1;
                            keycount == 0;
                        }
                    }
                    wait_centis(2);
                }
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
                    POKE(0xBFA2, 48+min2); POKE(0xBFA3, 48+min1);
                    POKE(0xBFCA, 48+min2); POKE(0xBFCB, 48+min1);
                    POKE(0xBFA5, 48+secs2); POKE(0xBFA6, 48+secs1);
                    POKE(0xBFCD, 48+secs2); POKE(0xBFCE, 48+secs1);
                    prevsclk = clock();
                }
                if(clock()-prevaclk > interval) {
                    if(playing == 1) { playing=play_chanA(0); playtime = playtime + 1; }
                    animate_sprite(player);
                    if(notsleeping == 0) animate_sprite(player);
                    prevaclk = clock();
                }
            }
            stop_sound(); load_instrB(boingbass); playtime=1; i = 0;
            wait(1);
            clear_screen();
            if(restartlvl == 1) {
                lives = lives - 1;
                if(lives==0) {
                    POKE(0xbf7b,'0');
                    draw_string("You lost!",0xa64f);
                    while(i<29) {
						if(clock()-prevsclk > (CLOCKS_PER_SEC/8)) {
							if(lost_pat[i]!=0) play_chanB(freq_table[(lost_pat[i]>>4)-1][lost_pat[i]&15]);
							i = i+1;
							prevsclk = clock();
						}
					}
					while(kbhit()>0) { c = cgetc(); wait_centis(1); }
                    wait_centis(200);
                    break;
                } else {
                    memset((char*)0xBF68, ' ', 200);  // Clear lower text area
                    memcpy((char*)0xBF69,any_key,strlen(any_key));
                    draw_string("Try again!",0xa650);
                    restartlvl = 0;
                    while(kbhit()>0) { c = cgetc(); wait_centis(1); }
                    while(kbhit()==0) {
						if(clock()-prevsclk > (CLOCKS_PER_SEC/8)) {
							if(i<29 && lost_pat[i]!=0) play_chanB(freq_table[(lost_pat[i]>>4)-1][lost_pat[i]&15]);
							i = i+1;
							prevsclk = clock();
						}
					}
                    while(kbhit()>0) { c = cgetc(); wait_centis(1); }
                }
            } else {
                curlevel = curlevel + 1;
                if(curlevel==NRLEVELS) {
                    draw_string("You won!",0xa64f);
                    wait_centis(300);
					break;
                } else {
                    memset((char*)0xBF68, ' ', 200);  // Clear lower text area
                    memcpy((char*)0xBF69,any_key,strlen(any_key));
                    draw_string("Bravo!",0xa651);
                    draw_string("Next level Password: ",0xAB20);
                    draw_string(keycodes[curlevel],0xAB35);
                    while(kbhit()>0) { c = cgetc(); wait_centis(1); }
                    while(kbhit()==0) {
						if(clock()-prevsclk > (CLOCKS_PER_SEC/8)) {
							if(i<41 && bravo_pat[i]!=0) play_chanB(freq_table[(bravo_pat[i]>>4)-1][bravo_pat[i]&15]);
							i = i+1;
							prevsclk = clock();
						}
					}
                    while(kbhit()>0) { c = cgetc(); wait_centis(1); }
                }
            }

        clear_screen();
        }
    }
}
