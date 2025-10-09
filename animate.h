char buf[10];

void animate_sprite(struct sprite *spr) {
	// draw
    if(spr->action==STAY || spr->action==SLEEP) {
		select_cntr = 0;
		if(spr->action==SLEEP) draw_spr(spr->sleep_ani,draw_saddr+spr->pos);
		else draw_spr(spr->stay_ani,draw_saddr+spr->pos);
	}
	if(spr->action==SELECT) {
		if(select_cntr==1) { stop_sound(); load_instrA(select); playtime = 1; play_chanA(0); }
		if(select_cntr<7) {
			if((lvlgrid[spr->gridpos]>>3)==spr->color+4) draw_selected(spr->sleep_ani,draw_saddr+spr->pos);
			else draw_selected(spr->stay_ani,draw_saddr+spr->pos);
			select_cntr = select_cntr + 1;
		} else {
			if((lvlgrid[spr->gridpos]>>3)==spr->color+4) {
                draw_spr(spr->sleep_ani,draw_saddr+spr->pos);
                spr->action = SLEEP;
			} else {
                draw_spr(spr->stay_ani,draw_saddr+spr->pos);
                spr->action = STAY;
            }
			select_cntr = 0;
		}
	}

	if(spr->action == TELEPORT) {
		if(select_cntr==0) { stop_sound(); load_instrA(zoom); playing = 1; playtime = 1; play_chanA(0); }
		object_under = lvlgrid[player->gridpos]>>3;
		clean_spr=object_sprs[object_under];
		draw_teleport(clean_spr, draw_saddr+spr->pos, select_cntr);
		if(spr->pos==tele_pos[spr->color][0]) draw_teleport(spr->stay_ani, draw_saddr+tele_pos[spr->color][1], select_cntr);
		else draw_teleport(spr->stay_ani, draw_saddr+tele_pos[spr->color][0], select_cntr);
		if(select_cntr==18) {
			lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]&0b11111000;
			if(spr->pos==tele_pos[spr->color][0]) { spr->pos = tele_pos[spr->color][1]; spr->gridpos = tele_grid[spr->color][1]; }
			else { spr->pos = tele_pos[spr->color][0]; spr->gridpos = tele_grid[spr->color][0]; }
			lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]|(spr->color+4);
			switch(spr->movedir) {
				case LEFT:	teleport_left(player); break;
				case RIGHT:	teleport_right(player); break;
				case UP:	teleport_up(player); break;
				case DOWN:	teleport_down(player); break;
			}
			select_cntr = 0;
		} else select_cntr = select_cntr + 1;
	}
	
	if(cur_bumper_frame == 3) { cur_bumper_frame = 4; draw_spr(&bumper[54],draw_saddr+cur_bumper_pos); wait_centis(4);  }
	else if(cur_bumper_frame == 4) { cur_bumper_frame = 0; draw_spr(bumper,draw_saddr+cur_bumper_pos); wait_centis(4);  }
	
	if(spr->action == BUMP) {
		byte* cur_anim;
		if(cur_bumper_frame == 2) {
			cur_bumper_frame = 3;
			if(spr->movedir==LEFT) { if((byte)(lvlgrid[player->gridpos+1]<<5)!=0) spr->action = STAY; spr->movedir=RIGHT; }
			else if(spr->movedir==RIGHT) { if((byte)(lvlgrid[player->gridpos-1]<<5)!=0)spr->action = STAY; spr->movedir=LEFT; }
			if(spr->movedir==UP) { if((byte)(lvlgrid[player->gridpos+13]<<5)!=0) spr->action = STAY; spr->movedir=DOWN; }
			else if(spr->movedir==DOWN) { if((byte)(lvlgrid[player->gridpos-13]<<5)!=0) spr->action = STAY; spr->movedir=UP; }
			switch(spr->movedir) {
				case LEFT: draw_spr(&bumper[108],draw_saddr+cur_bumper_pos); wait_centis(4); break;
				case RIGHT: draw_spr(&bumper[162],draw_saddr+cur_bumper_pos); wait_centis(4); break;
				case UP: draw_spr(&bumper[216],draw_saddr+cur_bumper_pos); wait_centis(4); break;
				case DOWN: draw_spr(&bumper[270],draw_saddr+cur_bumper_pos); wait_centis(4); break;
			}
			stop_sound(); load_instrA(bumps); playtime = 1; play_chanA(0); playing=1;
			if((lvlgrid[spr->gridpos]>>3)==spr->color+12) { select_cntr = 0; spr->action = TELEPORT; return; }
		}
		if(cur_bumper_frame == 1) { cur_bumper_frame = 2; draw_spr(&bumper[54],draw_saddr+cur_bumper_pos); wait_centis(4); return; }
		if(spr->action == STAY) return;
		switch(spr->movedir) {
			case LEFT:	move_left(player);
						if(select_cntr) cur_anim = spr->walk_right_ani; else cur_anim = spr->walk_left_ani;
						if(need_cleanup) { draw_spr_col(clean_spr, 2-spr->steps, draw_saddr+spr->pos+3); need_cleanup = 0; }
						draw_spr(cur_anim+spr->frame_pointer,draw_saddr+spr->pos); break;
			case RIGHT: move_right(player);
						if(select_cntr) cur_anim = spr->walk_left_ani; else cur_anim = spr->walk_right_ani;
						if(need_cleanup) { draw_spr_col(clean_spr, spr->steps, draw_saddr+spr->pos-1); need_cleanup = 0; }
						draw_spr(cur_anim+spr->frame_pointer,draw_saddr+spr->pos); break;
			case DOWN: 	move_down(player);
						if(select_cntr) cur_anim = spr->walk_up_ani; else cur_anim = spr->walk_down_ani;
						if(need_cdclean) { draw_spr_rows(clean_spr, 3, 0, draw_saddr+spr->origpos); need_cdclean = 0; }
						if(need_cleanup) { draw_spr_rows(clean_spr, 3, downmap[spr->steps], draw_saddr+spr->origpos); need_cleanup = 0; }
						draw_spr(cur_anim+spr->frame_pointer,draw_saddr+spr->pos); break;
			case UP: 	move_up(player);
						if(select_cntr) cur_anim = spr->walk_down_ani; else cur_anim = spr->walk_up_ani;
						if(need_cdclean) { draw_spr_rows(clean_spr, 3, 2, draw_saddr+spr->origpos); need_cdclean = 0; }
						if(need_cleanup) { draw_spr_rows(clean_spr, 3, upmap[spr->steps], draw_saddr+spr->origpos); need_cleanup = 0; }
						draw_spr(cur_anim+spr->frame_pointer,draw_saddr+spr->pos);
						break;
		}
		select_cntr = !select_cntr;
	}
	
	if(spr->action==MOVE) {
		switch(spr->movedir) {
			case LEFT:	move_left(player);
						if(need_cleanup) { draw_spr_col(clean_spr, 2-spr->steps, draw_saddr+spr->pos+3); need_cleanup = 0; }
						draw_spr(spr->walk_left_ani+spr->frame_pointer,draw_saddr+spr->pos); break;
			case RIGHT: move_right(player);
						if(need_cleanup) { draw_spr_col(clean_spr, spr->steps, draw_saddr+spr->pos-1); need_cleanup = 0; }
						draw_spr(spr->walk_right_ani+spr->frame_pointer,draw_saddr+spr->pos); break;
			case DOWN: 	move_down(player);
						if(need_cdclean) { draw_spr_rows(clean_spr, 3, 0, draw_saddr+spr->origpos); need_cdclean = 0; }
						if(need_cleanup) { draw_spr_rows(clean_spr, 3, downmap[spr->steps], draw_saddr+spr->origpos); need_cleanup = 0; }
						draw_spr(spr->walk_down_ani+spr->frame_pointer,draw_saddr+spr->pos); break;
			case UP: 	move_up(player);
						if(need_cdclean) { draw_spr_rows(clean_spr, 3, 2, draw_saddr+spr->origpos); need_cdclean = 0; }
						if(need_cleanup) { draw_spr_rows(clean_spr, 3, upmap[spr->steps], draw_saddr+spr->origpos); need_cleanup = 0; }
						draw_spr(spr->walk_up_ani+spr->frame_pointer,draw_saddr+spr->pos);
						break;
		}
		// debug: puttext(0xBFB9,itoa(player->pos, buf, 10));
	}
	// logic
    object_under = lvlgrid[player->gridpos]>>3;
	clean_spr=object_sprs[object_under];
	if(object_under == 1) { // heart
		stop_sound(); load_instrA(coin); playtime = 1; play_chanA(0); playing=1;
		lives = lives + 1;
		POKE(0xBF91,48+(lives/10)); POKE(0xBF92,48+(lives%10));
		lvlgrid[player->gridpos] = spr->color+4;
	}
	if(object_under == 2) { // clock
		stop_sound(); load_instrA(coin); playtime = 1; play_chanA(0); playing=1;
		lvltime = lvltime + 20;
		min2 = lvltime/600; min1 = (lvltime/60)%10; secs2 = (lvltime%60)/10 ; secs1 = (lvltime%60)%10;
		POKE(0xBFA2, 48+min2); POKE(0xBFA3, 48+min1); POKE(0xBFA5, 48+secs2); POKE(0xBFA6, 48+secs1);
		POKE(0xBFCA, 48+min2); POKE(0xBFCB, 48+min1); POKE(0xBFCD, 48+secs2); POKE(0xBFCE, 48+secs1);
		lvlgrid[player->gridpos] = spr->color+4;
	}
	if(object_under == 3) { // joker
		stop_sound(); load_instrA(coin); playtime = 1; play_chanA(0); playing=1;
		jokers = jokers + 1;
		POKE(0xBFB6,48+(jokers/10)); POKE(0xBFB7,48+(jokers%10));
		lvlgrid[player->gridpos] = spr->color+4;
	}
	if(object_under == 8 && player->steps == 0) { // arrow right
		if((byte)(lvlgrid[player->gridpos+1]<<5)==0) { stop_sound(); load_instrA(arrow); playtime = 1; play_chanA(0); playing=1; player->action = MOVE; player->movedir = RIGHT; }
		else player->action = STAY;
	}
	if(object_under == 9 && player->steps == 0) { // arrow left
		if((byte)(lvlgrid[player->gridpos-1]<<5)==0) { stop_sound(); load_instrA(arrow); playtime = 1; play_chanA(0); playing=1; player->action = MOVE; player->movedir = LEFT; }
		else player->action = STAY;
	}
	if(object_under == 10 && player->steps == 0) { // arrow up
		if((byte)(lvlgrid[player->gridpos-13]<<5)==0) { stop_sound(); load_instrA(arrow); playtime = 1; play_chanA(0); playing=1; player->action = MOVE; player->movedir = UP; need_cdclean = 1; }
		else player->action = STAY;
	}
	if(object_under == 11 && player->steps == 0) { // arrow down
		if((byte)(lvlgrid[player->gridpos+13]<<5)==0) { stop_sound(); load_instrA(arrow); playtime = 1; play_chanA(0); playing=1; player->action = MOVE; player->movedir = DOWN; need_cdclean = 1; }
		else player->action = STAY;
	}
}
