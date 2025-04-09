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

#define LEFT	1
#define RIGHT	2
#define UP		3
#define DOWN	4
					//		0		1			2		3
byte *object_sprs[] = { clean, red_stay, red_stay, red_stay, 
					//		4			5		6				7
						blue_exit, red_exit, yellow_exit, green_exit};

byte curlevel = 0;
byte cur_player;

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

void setup() {
	int i;
	byte c = 0;
    if(PEEK(0xC800))
            asm("jsr $EC33");       // HIRES in Atmos (ROM 1.1)
    else
            asm("jsr $E9BB");       // HIRES in Oric-1 (ROM 1.0)
    memset((char*)0xBF68, 0, 120);  // Clear lower text area
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
			if(object_under==spr->color+4) notsleeping = notsleeping + 1;
			level[curlevel][spr->gridpos] = level[curlevel][spr->gridpos]&0b11111000;
			spr->gridpos = spr->gridpos + 1;
			level[curlevel][spr->gridpos] = level[curlevel][spr->gridpos]|(spr->color+4);
			if((level[curlevel][spr->gridpos]>>3)==spr->color+4) notsleeping = notsleeping - 1;
			spr->steps = 0;
			if((byte)(level[curlevel][spr->gridpos+1]<<5)!=0) spr->action = STAY;
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
				if(object_under==spr->color+4) notsleeping = notsleeping + 1;
				level[curlevel][spr->gridpos] = level[curlevel][spr->gridpos]&0b11111000;
				spr->gridpos = spr->gridpos - 1;
				level[curlevel][spr->gridpos] = level[curlevel][spr->gridpos]|(spr->color+4);
				if((level[curlevel][spr->gridpos]>>3)==spr->color+4) notsleeping = notsleeping - 1;
				spr->steps = 0;
				if((byte)(level[curlevel][spr->gridpos-1]<<5)!=0) spr->action = STAY;
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
			if(object_under==spr->color+4) notsleeping = notsleeping + 1;
			level[curlevel][spr->gridpos] = level[curlevel][spr->gridpos]&0b11111000;
			spr->gridpos = spr->gridpos + 13;
			level[curlevel][spr->gridpos] = level[curlevel][spr->gridpos]|(spr->color+4);
			if((level[curlevel][spr->gridpos]>>3)==spr->color+4) notsleeping = notsleeping - 1;
			spr->steps = 0;
			if((byte)(level[curlevel][spr->gridpos+13]<<5)!=0) spr->action = STAY;
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
			if(object_under==spr->color+4) notsleeping = notsleeping + 1;
			level[curlevel][spr->gridpos] = level[curlevel][spr->gridpos]&0b11111000;
			spr->gridpos = spr->gridpos - 13;
			level[curlevel][spr->gridpos] = level[curlevel][spr->gridpos]|(spr->color+4);
			if((level[curlevel][spr->gridpos]>>3)==spr->color+4) notsleeping = notsleeping - 1;
			spr->steps = 0;
			if((byte)(level[curlevel][spr->gridpos-13]<<5)!=0) spr->action = STAY;
		}
	}
}

void animate_sprite(struct sprite *spr) {
    // draw 
    if(spr->action==STAY) {
		if((level[curlevel][spr->gridpos]>>3)==spr->color+4) draw_spr(spr->sleep_ani,0xa000+spr->pos);
		else draw_spr(spr->stay_ani,0xa000+spr->pos);
		if(spr->movedir == UP) memset((char *)0xa000+spr->pos+720,64,spr_bwidth-1);
	}
	if(spr->action==SELECT) {
		if(select_cntr<7) {
			if((level[curlevel][spr->gridpos]>>3)==spr->color+4) draw_selected(spr->sleep_ani,0xa000+spr->pos);
			else draw_selected(spr->stay_ani,0xa000+spr->pos);
			select_cntr = select_cntr + 1;
		} else {
			if((level[curlevel][spr->gridpos]>>3)==spr->color+4) draw_spr(spr->sleep_ani,0xa000+spr->pos);
			else draw_spr(spr->stay_ani,0xa000+spr->pos);
			spr->action = STAY;
			select_cntr = 0;
		}
	}
	if(spr->action==MOVE) {
		object_under = level[curlevel][player->gridpos]>>3;
		clean_spr=object_sprs[object_under];
		switch(spr->movedir) {
			case LEFT:	move_left(player);
						if(need_cleanup) { draw_spr_col(clean_spr, 2-spr->steps, 0xa000+spr->pos+3); need_cleanup = 0; }
						draw_spr(spr->walk_left_ani+spr->frame_pointer,0xa000+spr->pos); break;
			case RIGHT: move_right(player);
						if(need_cleanup) { draw_spr_col(clean_spr, spr->steps, 0xa000+spr->pos-1); need_cleanup = 0; }
						draw_spr(spr->walk_right_ani+spr->frame_pointer,0xa000+spr->pos); break;
			case DOWN: 	move_down(player);
						if(need_cleanup) { draw_spr(clean_spr,0xa000+spr->origpos); need_cleanup = 0; }
						draw_spr(spr->walk_down_ani+spr->frame_pointer,0xa000+spr->pos); break;
			case UP: 	move_up(player);
						if(need_cleanup) { draw_spr(clean_spr,0xa000+spr->origpos); need_cleanup = 0; }
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
			if(level[curlevel][i] == 0x01) draw_spr(wall,pos);
			if(level[curlevel][i] == 0x20) draw_spr(blue_exit,pos);
			if(level[curlevel][i] == 0x28) draw_spr(red_exit,pos);
			if(level[curlevel][i] == 0x30) draw_spr(yellow_exit,pos);
			if(level[curlevel][i] == 0x38) draw_spr(green_exit,pos);
			if(level[curlevel][i] == 4) {
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
			if(level[curlevel][i] == 5) {
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
			if(level[curlevel][i] == 6) {
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
			if(level[curlevel][i] == 7) {
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
    clock_t interval = CLOCKS_PER_SEC/15;
    clock_t clk = 0;
    setup();
    init_skweeks();
    while(1) {
		load_level();
		player = &skweeks[cur_player];
		while(notsleeping > 0) {
			if(kbhit()>0 && player->action==STAY) {
				c = cgetc();
				if(c==CH_CURS_RIGHT && (byte)(level[curlevel][player->gridpos+1]<<5)==0) {
					player->action = MOVE;
					player->movedir = RIGHT;
				}
				if(c==CH_CURS_LEFT && (byte)(level[curlevel][player->gridpos-1]<<5)==0) {
					player->action = MOVE;
					player->movedir = LEFT;
				}
				if(c==CH_CURS_DOWN && (byte)(level[curlevel][player->gridpos+13]<<5)==0) {
					player->action = MOVE;
					player->movedir = DOWN;
				}
				if(c==CH_CURS_UP && (byte)(level[curlevel][player->gridpos-13]<<5)==0) {
					player->action = MOVE;
					player->movedir = UP;
				}
				if(c==CH_ENTER) {
					cur_player = cur_player + 1;
					if(!(cur_player<nr_skweeks)) cur_player = 0;
					player = &skweeks[cur_player];
					player->action = SELECT;
				}
			}
			clk = clock();
			if(clk%interval==0) {
				animate_sprite(player);
				if(notsleeping == 0) animate_sprite(player);
			}
		}
		wait(1);
		clear_screen();
		curlevel = curlevel + 1;
		if(curlevel==NRLEVELS) {
			draw__spr(youwon, 10, 20, 0xa64f);
			return;
		}
		draw__spr(bravo, 10, 20, 0xa64f);
		wait(3);
		clear_screen();
    }
}
