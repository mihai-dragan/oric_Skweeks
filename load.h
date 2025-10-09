void load_level() {
	byte i = 0;
	byte x,y;
	int pos = 0xa3c1;
	cur_player = 0;
	notsleeping = 0;
	nr_skweeks = 0;
	memcpy((char*)0xBF69,statxt,39);
	POKE(0xBF91,48+(lives/10)); POKE(0xBF92,48+(lives%10));
	draw_string("LEVEL",0xa010);
	//draw_char('L',0xa010); draw_char('E',0xa011); draw_char('V',0xa012); draw_char('E',0xa013); draw_char('L',0xa014);
	draw_char(16+(curlevel/100),0xa016);draw_char(16+(curlevel/10),0xa017);draw_char(16+(curlevel%10),0xa018);
	POKE(0xBFB6,48+(jokers/10)); POKE(0xBFB7,48+(jokers%10));
	POKE(0xBF9F, 5); POKE(0xBFC7, 1); // time text color
	POKE(0xBFA0, 10); POKE(0xBFC8, 10); // double size text
	POKE(0xBFA4, ':'); POKE(0xBFCC, ':');
	POKE(0xBFA7, 8); POKE(0xBFCF, 8); // normal size text
	POKE(0xBFA8, 7); POKE(0xBFD0, 7); // back to white text
	lvltime = lvlsec[curlevel];
	min2 = lvltime/600; min1 = (lvltime/60)%10; secs2 = (lvltime%60)/10 ; secs1 = (lvltime%60)%10;
	wall = wall1;
	if(curlevel>9) wall = wall2;
	if(curlevel>19) wall = wall3;
	if(curlevel>29) wall = wall4;
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
			if(lvlgrid[i] == 0x80) draw_spr(bumper,pos);
			if(lvlgrid[i] == 0x60) {
				draw_spr(blue_tele,pos);
				if(tele_grid[0][0] == 0) { tele_pos[0][0] = pos-draw_saddr; tele_grid[0][0] = i; }
				else { tele_pos[0][1] = pos-draw_saddr; tele_grid[0][1] = i; }
			}
			if(lvlgrid[i] == 0x68) {
				draw_spr(red_tele,pos);
				if(tele_grid[1][0] == 0) { tele_pos[1][0] = pos-draw_saddr; tele_grid[1][0] = i; }
				else { tele_pos[1][1] = pos-draw_saddr; tele_grid[1][1] = i; }
			}
			if(lvlgrid[i] == 0x70) {
				draw_spr(yellow_tele,pos);
				if(tele_grid[2][0] == 0) { tele_pos[2][0] = pos-draw_saddr; tele_grid[2][0] = i; }
				else { tele_pos[2][1] = pos-draw_saddr; tele_grid[2][1] = i; }
			}
			if(lvlgrid[i] == 0x78) {
				draw_spr(green_tele,pos);
				if(tele_grid[3][0] == 0) { tele_pos[3][0] = pos-draw_saddr; tele_grid[3][0] = i; }
				else { tele_pos[3][1] = pos-draw_saddr; tele_grid[3][1] = i; }
			}
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
				skweeks[nr_skweeks].origpos = pos-draw_saddr;
				skweeks[nr_skweeks].pos = pos-draw_saddr;
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
				skweeks[nr_skweeks].origpos = pos-draw_saddr;
				skweeks[nr_skweeks].pos = pos-draw_saddr;
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
				skweeks[nr_skweeks].origpos = pos-draw_saddr;
				skweeks[nr_skweeks].pos = pos-draw_saddr;
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
				skweeks[nr_skweeks].origpos = pos-draw_saddr;
				skweeks[nr_skweeks].pos = pos-draw_saddr;
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

