void load_level() {
	byte i = 0;
	byte x,y;
	int pos = 0xa001;
	cur_player = 0;
	notsleeping = 0;
	nr_skweeks = 0;
	wall = wall1;
	if(curlevel>9) wall = wall2;
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
			if(lvlgrid[i] == 0x40) draw_spr(arrow_right,pos);
			if(lvlgrid[i] == 0x48) draw_spr(arrow_left,pos);
			if(lvlgrid[i] == 0x50) draw_spr(arrow_up,pos);
			if(lvlgrid[i] == 0x58) draw_spr(arrow_down,pos);
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

