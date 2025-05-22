void move_right(struct sprite *spr) {
	if(spr->cur_frame < last_frame) { // set next frame
		spr->cur_frame++;
		spr->frame_pointer+=frame_offset;
		if(spr->cur_frame == last_frame) {
			if(!playing) { load_instrA(footstep); playtime = 1; play_chanA(0); }
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
			if((lvlgrid[spr->gridpos]>>3)==spr->color+12) {
				spr->action = TELEPORT;
				return;
			}
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
		if(!playing) { load_instrA(footstep); playtime = 1; play_chanA(0); }
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
				if((lvlgrid[spr->gridpos]>>3)==spr->color+12) {
					spr->action = TELEPORT;
					return;
				}
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
		if(spr->cur_frame==0&&spr->steps==0) {
			spr->origpos = spr->pos;
		}
		spr->pos = spr->pos+80;
		spr->cur_frame++;
		spr->frame_pointer+=frame_offset;
	} else {
		if(!playing) { load_instrA(footstep); playtime = 1; play_chanA(0); }
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
			if((lvlgrid[spr->gridpos]>>3)==spr->color+12) {
				spr->action = TELEPORT;
				return;
			}
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
		if(spr->cur_frame==0&&spr->steps==0) {
			spr->origpos = spr->pos;
		}
		spr->pos = spr->pos-80;
		spr->cur_frame++;
		spr->frame_pointer+=frame_offset;
	} else {
		if(!playing) { load_instrA(footstep); playtime = 1; play_chanA(0); }
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
			if((lvlgrid[spr->gridpos]>>3)==spr->color+12) {
				spr->action = TELEPORT;
				return;
			}
			if((byte)(lvlgrid[spr->gridpos-13]<<5)!=0) {
                if((lvlgrid[spr->gridpos]>>3)==spr->color+4) {
                    notsleeping = notsleeping - 1;
                    spr->action = SLEEP;
                } else spr->action = STAY;
            }
		}
	}
}

void teleport_left(struct sprite *spr) {
	lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]&0b11111000;
	if(spr->pos==tele_pos[spr->color][0]) { spr->pos = tele_pos[spr->color][1]; spr->gridpos = tele_grid[spr->color][1]; }
	else { spr->pos = tele_pos[spr->color][0]; spr->gridpos = tele_grid[spr->color][0]; }
	lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]|(spr->color+4);
	if((byte)(lvlgrid[spr->gridpos-1]<<5)!=0) spr->action = STAY;
	else spr->action = MOVE;
}

void teleport_right(struct sprite *spr) {
	lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]&0b11111000;
	if(spr->pos==tele_pos[spr->color][0]) { spr->pos = tele_pos[spr->color][1]; spr->gridpos = tele_grid[spr->color][1]; }
	else { spr->pos = tele_pos[spr->color][0]; spr->gridpos = tele_grid[spr->color][0]; }
	lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]|(spr->color+4);
	if((byte)(lvlgrid[spr->gridpos+1]<<5)!=0) spr->action = STAY;
	else spr->action = MOVE;
}

void teleport_up(struct sprite *spr) {
	lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]&0b11111000;
	if(spr->pos==tele_pos[spr->color][0]) { spr->pos = tele_pos[spr->color][1]; spr->gridpos = tele_grid[spr->color][1]; }
	else { spr->pos = tele_pos[spr->color][0]; spr->gridpos = tele_grid[spr->color][0]; }
	lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]|(spr->color+4);
	if((byte)(lvlgrid[spr->gridpos-13]<<5)!=0) spr->action = STAY;
	else spr->action = MOVE;
}

void teleport_down(struct sprite *spr) {
	lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]&0b11111000;
	if(spr->pos==tele_pos[spr->color][0]) { spr->pos = tele_pos[spr->color][1]; spr->gridpos = tele_grid[spr->color][1]; }
	else { spr->pos = tele_pos[spr->color][0]; spr->gridpos = tele_grid[spr->color][0]; }
	lvlgrid[spr->gridpos] = lvlgrid[spr->gridpos]|(spr->color+4);
	if((byte)(lvlgrid[spr->gridpos+13]<<5)!=0) spr->action = STAY;
	else spr->action = MOVE;
}
