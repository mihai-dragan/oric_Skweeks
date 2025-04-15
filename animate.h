void animate_sprite(struct sprite *spr) {
	byte i;
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
		switch(spr->movedir) {
			case LEFT:	move_left(player);
						if(need_cleanup) { draw_spr_col(clean_spr, 2-spr->steps, 0xa000+spr->pos+3); need_cleanup = 0; }
						draw_spr(spr->walk_left_ani+spr->frame_pointer,0xa000+spr->pos); break;
			case RIGHT: move_right(player);
						if(need_cleanup) { draw_spr_col(clean_spr, spr->steps, 0xa000+spr->pos-1); need_cleanup = 0; }
						draw_spr(spr->walk_right_ani+spr->frame_pointer,0xa000+spr->pos); break;
			case DOWN: 	move_down(player);
						if(need_cdclean) { draw_spr_rows(blue_exit, 3, 0, 0xa000+spr->origpos); need_cdclean = 0; }
						if(need_cleanup) { draw_spr_rows(clean_spr, 3, downmap[spr->steps], 0xa000+spr->origpos); need_cleanup = 0; }
						draw_spr(spr->walk_down_ani+spr->frame_pointer,0xa000+spr->pos); break;
			case UP: 	move_up(player);
						if(need_cdclean) { draw_spr_rows(blue_exit, 3, 2, 0xa000+spr->origpos); need_cdclean = 0; }
						if(need_cleanup) { draw_spr_rows(clean_spr, 3, upmap[spr->steps], 0xa000+spr->origpos); need_cleanup = 0; }
						draw_spr(spr->walk_up_ani+spr->frame_pointer,0xa000+spr->pos);
						break;
		}
	}
	// logic
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
	if(object_under == 8 && player->steps == 0) {
		player->action = MOVE;
		player->movedir = RIGHT;
		for(i=0; i<kbhit(); i++) cgetc();
	}
	if(object_under == 9 && player->steps == 0) {
		player->action = MOVE;
		player->movedir = LEFT;
		for(i=0; i<kbhit(); i++) cgetc();
	}
	if(object_under == 10 && player->steps == 0) {
		player->action = MOVE;
		player->movedir = UP;
		need_cdclean = 1;
		for(i=0; i<kbhit(); i++) cgetc();
	}
	if(object_under == 11 && player->steps == 0) {
		player->action = MOVE;
		player->movedir = DOWN;
		need_cdclean = 1;
		for(i=0; i<kbhit(); i++) cgetc();
	}
}
