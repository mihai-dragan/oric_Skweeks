#include <time.h>
#include <conio.h>
#include <string.h>
#include <peekpoke.h>
#define byte unsigned char
#include "sprites.h"
#include "levels.h"

#define STAY	0
#define MOVE	1
#define SELECT	2
#define SLEEP	3

#define LEFT	1
#define RIGHT	2
#define UP		3
#define DOWN	4
					//		0	1		2   	3
byte *object_sprs[] = { clean, clean, clean, clean, 
					//		4			5		6				7
						blue_exit, red_exit, yellow_exit, green_exit};

byte restartlvl = 0;
int lvltime = 0;
byte secs1, secs2, min1, min2;
byte curlevel = 0;
byte cur_player;
byte lives = 3;
byte jokers = 0;

byte lvlgrid[104];

byte select_cntr = 0;

byte spr_bwidth = 3; // how may bytes wide (groups of 6 pixels)
byte spr_height = 18; // how many lines
byte last_frame = 2;
unsigned int frame_offset = 54;
unsigned int last_frame_offset  = 108;

byte object_under;
byte need_cleanup = 0;
byte* clean_spr;
int clean_addr;

byte notsleeping = 0;
byte clean_dat[3][18];
byte downmap[3] = { 2, 0, 1 };
byte upmap[3] = { 0, 2, 1 };

byte statxt[39] = "TIME=--:-- LIVES=-- LEVEL=--- JOKERS=--";

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
	memset((char*)0xBF68, 0, 120);  // Clear lower text area
	POKE(0xbf68, 7); // set white ink for first text line
}

struct sprite {
	byte color;
    unsigned int frame_pointer;
    byte cur_frame;
    unsigned int pos;
    unsigned int origpos;
    byte steps;
    byte gridpos;
    byte movedir;
    byte action;
    byte* walk_left_ani;
    byte* walk_right_ani;
    byte* walk_down_ani;
    byte* walk_up_ani;
    byte* stay_ani;
    byte* sleep_ani;
};

byte nr_skweeks = 0;
struct sprite skweeks[8];
struct sprite *player;

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

void move_right(struct sprite *spr) {
	if(spr->cur_frame < last_frame) { // set next frame
		spr->cur_frame++;
		spr->frame_pointer+=frame_offset;
		if(spr->cur_frame == last_frame) {
			need_cleanup = 1;
			spr->pos = spr->pos+1;
		}
	} else {
		spr->cur_frame = 0;
		spr->frame_pointer = 0;
		spr->steps = spr->steps + 1;
		if(spr->steps==3) {
			spr->origpos = spr->pos;
			lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]&0b11111000;
			spr->gridpos = spr->gridpos + 1;
			lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]|(spr->color+4);
			spr->steps = 0;
			if((byte)(lvlgrid[spr->gridpos+1]<<5)!=0) {
                if((lvlgrid[spr->gridpos]>>3)==spr->color+4) {
                    notsleeping = notsleeping - 1;
                    spr->action = SLEEP;
                } else spr->action = STAY;
            }
		}
	}
}

void move_left(struct sprite *spr) {
	if(spr->cur_frame == 0) { // set next frame
		spr->cur_frame = last_frame;
		spr->frame_pointer = last_frame_offset;
	} else {
		if(spr->cur_frame == 1) {
			spr->cur_frame = 0;
			spr->frame_pointer = 0;
			spr->steps = spr->steps + 1;
			if(spr->steps==3) {
				spr->origpos = spr->pos;
				lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]&0b11111000;
				spr->gridpos = spr->gridpos - 1;
				lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]|(spr->color+4);
				spr->steps = 0;
				if((byte)(lvlgrid[spr->gridpos-1]<<5)!=0) {
                    if((lvlgrid[spr->gridpos]>>3)==spr->color+4) {
                        notsleeping = notsleeping - 1;
                        spr->action = SLEEP;
                    } else spr->action = STAY;
                }
			}
		} else {
			spr->pos = spr->pos-1;
			need_cleanup = 1;
			spr->cur_frame--;
			spr->frame_pointer-=frame_offset;
		}
	}
}

void move_down(struct sprite *spr) {
	if(spr->cur_frame < last_frame) { // set next frame
		if(spr->cur_frame==0&&spr->steps==0) spr->origpos = spr->pos;
		spr->pos = spr->pos+80;
		spr->cur_frame++;
		spr->frame_pointer+=frame_offset;
	} else {
		spr->pos = spr->pos+80;
		spr->cur_frame = 0;
		spr->frame_pointer = 0;
		need_cleanup = 1;
		spr->steps = spr->steps + 1;
		if(spr->steps==3) {
			lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]&0b11111000;
			spr->gridpos = spr->gridpos + 13;
			lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]|(spr->color+4);
			spr->steps = 0;
			if((byte)(lvlgrid[spr->gridpos+13]<<5)!=0) {
                if((lvlgrid[spr->gridpos]>>3)==spr->color+4) {
                    notsleeping = notsleeping - 1;
                    spr->action = SLEEP;
                } else spr->action = STAY;
            }
		}
	}
}

void move_up(struct sprite *spr) {
	if(spr->cur_frame < last_frame) { // set next frame
		if(spr->cur_frame==0&&spr->steps==0) spr->origpos = spr->pos;
		spr->pos = spr->pos-80;
		spr->cur_frame++;
		spr->frame_pointer+=frame_offset;
	} else {
		spr->pos = spr->pos-80;
		spr->cur_frame = 0;
		spr->frame_pointer = 0;
		need_cleanup = 1;
		spr->steps = spr->steps + 1;
		if(spr->steps==3) {
			lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]&0b11111000;
			spr->gridpos = spr->gridpos - 13;
			lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]|(spr->color+4);
			spr->steps = 0;
			if((byte)(lvlgrid[spr->gridpos-13]<<5)!=0) {
                if((lvlgrid[spr->gridpos]>>3)==spr->color+4) {
                    notsleeping = notsleeping - 1;
                    spr->action = SLEEP;
                } else spr->action = STAY;
            }
		}
	}
}

void animate_sprite(struct sprite *spr) {
    // draw 
    if(spr->action==STAY || spr->action==SLEEP) {
		if(spr->action==SLEEP) draw_spr(spr->sleep_ani,0xa000+spr->pos);
		else draw_spr(spr->stay_ani,0xa000+spr->pos);
	}
	if(spr->action==SELECT) {
		if(select_cntr<7) {
			if((lvlgrid[spr->gridpos]>>3)==spr->color+4) draw_selected(spr->sleep_ani,0xa000+spr->pos);
			else draw_selected(spr->stay_ani,0xa000+spr->pos);
			select_cntr = select_cntr + 1;
		} else {
			if((lvlgrid[spr->gridpos]>>3)==spr->color+4) {
                draw_spr(spr->sleep_ani,0xa000+spr->pos);
                spr->action = SLEEP;
			} else {
                draw_spr(spr->stay_ani,0xa000+spr->pos);
                spr->action = STAY;
            }
			select_cntr = 0;
		}
	}
	if(spr->action==MOVE) {
		object_under = lvlgrid[player->gridpos]>>3;
		clean_spr=object_sprs[object_under];
        if(object_under == 1) {
            lives = lives + 1;
            POKE(0xbf7a,48+(lives/10)); POKE(0xbf7b,48+(lives%10));
            lvlgrid[player->gridpos] = 0;
        }
        if(object_under == 2) {
            lvltime = lvltime + 20;
            min2 = lvltime/600; min1 = (lvltime/60)%10; secs2 = (lvltime%60)/10 ; secs1 = (lvltime%60)%10;
            POKE(0xbf6e, 48+min2); POKE(0xbf6f, 48+min1); POKE(0xbf71, 48+secs2); POKE(0xbf72, 48+secs1);
            lvlgrid[player->gridpos] = 0;
        }
        if(object_under == 3) {
            jokers = jokers + 1;
            POKE(0xbf8e,48+(jokers/10)); POKE(0xbf8f,48+(jokers%10));
            lvlgrid[player->gridpos] = 0;
        }
		switch(spr->movedir) {
			case LEFT:	move_left(player);
						if(need_cleanup) { draw_spr_col(clean_spr, 2-spr->steps, 0xa000+spr->pos+3); need_cleanup = 0; }
						draw_spr(spr->walk_left_ani+spr->frame_pointer,0xa000+spr->pos); break;
			case RIGHT: move_right(player);
						if(need_cleanup) { draw_spr_col(clean_spr, spr->steps, 0xa000+spr->pos-1); need_cleanup = 0; }
						draw_spr(spr->walk_right_ani+spr->frame_pointer,0xa000+spr->pos); break;
			case DOWN: 	move_down(player);
						if(need_cleanup) { draw_spr_rows(clean_spr, 3, downmap[spr->steps], 0xa000+spr->origpos); need_cleanup = 0; }
						draw_spr(spr->walk_down_ani+spr->frame_pointer,0xa000+spr->pos); break;
			case UP: 	move_up(player);
						if(need_cleanup) { draw_spr_rows(clean_spr, 3, upmap[spr->steps], 0xa000+spr->origpos); need_cleanup = 0; }
						draw_spr(spr->walk_up_ani+spr->frame_pointer,0xa000+spr->pos);
						break;
		}
	}
}

void init_skweeks() {
	int i;
	for(i=0; i<8; i++) {
		skweeks[i].pos = 5;
		skweeks[i].steps = 0;
		skweeks[i].action = STAY;
		skweeks[i].movedir = STAY;
	}
}

void load_level() {
	byte i = 0;
	byte x,y;
	int pos = 0xa001;
	cur_player = 0;
	notsleeping = 0;
	nr_skweeks = 0;
	for(y=0; y<8; y++) {
		for(x=0; x<13; x++) {
            lvlgrid[i] = level[curlevel][i];
			if(lvlgrid[i] == 0x01) draw_spr(wall,pos);
            if(lvlgrid[i] == 0x02) draw_spr(block1,pos);
            if(lvlgrid[i] == 0x08) draw_spr(heart,pos);
            if(lvlgrid[i] == 0x10) draw_spr(timer,pos);
            if(lvlgrid[i] == 0x18) draw_spr(joker,pos);
			if(lvlgrid[i] == 0x20) draw_spr(blue_exit,pos);
			if(lvlgrid[i] == 0x28) draw_spr(red_exit,pos);
			if(lvlgrid[i] == 0x30) draw_spr(yellow_exit,pos);
			if(lvlgrid[i] == 0x38) draw_spr(green_exit,pos);
			if(lvlgrid[i] == 4) {
				draw_spr(blue_stay,pos);
				skweeks[nr_skweeks].walk_left_ani = blue_walk_left;
				skweeks[nr_skweeks].walk_right_ani = blue_walk_right;
				skweeks[nr_skweeks].walk_down_ani = blue_walk_down;
				skweeks[nr_skweeks].walk_up_ani = blue_walk_up;
				skweeks[nr_skweeks].stay_ani = blue_stay;
				skweeks[nr_skweeks].sleep_ani = blue_sleep;
				skweeks[nr_skweeks].color = 0;
				skweeks[nr_skweeks].gridpos = i;
				skweeks[nr_skweeks].origpos = pos-0xa000;
				skweeks[nr_skweeks].pos = pos-0xa000;
				nr_skweeks = nr_skweeks + 1;
				notsleeping = notsleeping + 1;
			}
			if(lvlgrid[i] == 5) {
				draw_spr(red_stay,pos);
				skweeks[nr_skweeks].walk_left_ani = red_walk_left;
				skweeks[nr_skweeks].walk_right_ani = red_walk_right;
				skweeks[nr_skweeks].walk_down_ani = red_walk_down;
				skweeks[nr_skweeks].walk_up_ani = red_walk_up;
				skweeks[nr_skweeks].stay_ani = red_stay;
				skweeks[nr_skweeks].sleep_ani = red_sleep;
				skweeks[nr_skweeks].color = 1;
				skweeks[nr_skweeks].gridpos = i;
				skweeks[nr_skweeks].origpos = pos-0xa000;
				skweeks[nr_skweeks].pos = pos-0xa000;
				nr_skweeks = nr_skweeks + 1;
				notsleeping = notsleeping + 1;
			}
			if(lvlgrid[i] == 6) {
				draw_spr(yellow_stay,pos);
				skweeks[nr_skweeks].walk_left_ani = yellow_walk_left;
				skweeks[nr_skweeks].walk_right_ani = yellow_walk_right;
				skweeks[nr_skweeks].walk_down_ani = yellow_walk_down;
				skweeks[nr_skweeks].walk_up_ani = yellow_walk_up;
				skweeks[nr_skweeks].stay_ani = yellow_stay;
				skweeks[nr_skweeks].sleep_ani = yellow_sleep;
				skweeks[nr_skweeks].color = 2;
				skweeks[nr_skweeks].gridpos = i;
				skweeks[nr_skweeks].origpos = pos-0xa000;
				skweeks[nr_skweeks].pos = pos-0xa000;
				nr_skweeks = nr_skweeks + 1;
				notsleeping = notsleeping + 1;
			}
			if(lvlgrid[i] == 7) {
				draw_spr(green_stay,pos);
				skweeks[nr_skweeks].walk_left_ani = green_walk_left;
				skweeks[nr_skweeks].walk_right_ani = green_walk_right;
				skweeks[nr_skweeks].walk_down_ani = green_walk_down;
				skweeks[nr_skweeks].walk_up_ani = green_walk_up;
				skweeks[nr_skweeks].stay_ani = green_stay;
				skweeks[nr_skweeks].sleep_ani = green_sleep;
				skweeks[nr_skweeks].color = 3;
				skweeks[nr_skweeks].gridpos = i;
				skweeks[nr_skweeks].origpos = pos-0xa000;
				skweeks[nr_skweeks].pos = pos-0xa000;
				nr_skweeks = nr_skweeks + 1;
				notsleeping = notsleeping + 1;
			}
			pos = pos + 3;
			i++;
		}
		pos = pos + 681;
	}
	skweeks[0].action = SELECT;
}

void clear_screen() {
	int i;
	int addr = 0xa001;
	for(i=0;i<200;i++) {
		memset((char*)addr,64,39);
		addr = addr + 40;
	}
}

void wait(int sec) {
	clock_t clk = clock();
	while(sec>((clock()-clk)/CLOCKS_PER_SEC)) {
		clock();
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
		load_level();
		player = &skweeks[cur_player];
        memcpy((char*)0xBF69,statxt,39);
		POKE(0xbf7a,48+(lives/10));
		POKE(0xbf7b,48+(lives%10));
		POKE(0xbf83,48+(curlevel/100));
		POKE(0xbf84,48+(curlevel/10));
		POKE(0xbf85,48+(curlevel%10));
        POKE(0xbf8e,48+(jokers/10));
		POKE(0xbf8f,48+(jokers%10));
		lvltime = lvlsec[curlevel];
		min2 = lvltime/600; min1 = (lvltime/60)%10; secs2 = (lvltime%60)/10 ; secs1 = (lvltime%60)%10;
		while(notsleeping > 0 && restartlvl == 0) {
			if(kbhit()>0 && (player->action==STAY || player->action==SLEEP)) {
				c = cgetc();
				if(c==CH_CURS_RIGHT && (byte)(lvlgrid[player->gridpos+1]<<5)==0) {
                    if(player->action == SLEEP) notsleeping = notsleeping + 1;
					player->action = MOVE;
					player->movedir = RIGHT;
				}
				if(c==CH_CURS_LEFT && (byte)(lvlgrid[player->gridpos-1]<<5)==0) {
                    if(player->action == SLEEP) notsleeping = notsleeping + 1;
					player->action = MOVE;
					player->movedir = LEFT;
				}
				if(c==CH_CURS_DOWN && (byte)(lvlgrid[player->gridpos+13]<<5)==0) {
                    if(player->action == SLEEP) notsleeping = notsleeping + 1;
					player->action = MOVE;
					player->movedir = DOWN;
				}
				if(c==CH_CURS_UP && (byte)(lvlgrid[player->gridpos-13]<<5)==0) {
                    if(player->action == SLEEP) notsleeping = notsleeping + 1;
					player->action = MOVE;
					player->movedir = UP;
				}
				if(c==CH_ENTER) {
					cur_player = cur_player + 1;
					if(!(cur_player<nr_skweeks)) cur_player = 0;
					player = &skweeks[cur_player];
					player->action = SELECT;
				}
				if(c==CH_ESC) {
					restartlvl = 1;
				}
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
				POKE(0xbf6e, 48+min2); POKE(0xbf6f, 48+min1);
				POKE(0xbf71, 48+secs2);	POKE(0xbf72, 48+secs1);
				prevsclk = clock();
			}
			if(clock()-prevaclk > interval) {
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
