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
						blue_exit, red_exit, yellow_exit, green_exit,
					//		8			9		   10			11
						arrow_right, arrow_left, arrow_up, arrow_down};

byte restartlvl = 0;
int lvltime = 0;
byte secs1, secs2, min1, min2;
byte curlevel = 0;
byte cur_player;
byte lives = 3;
byte jokers = 1;

byte lvlgrid[104];

byte select_cntr = 0;

byte spr_bwidth = 3; // how may bytes wide (groups of 6 pixels)
byte spr_height = 18; // how many lines
byte last_frame = 2;
unsigned int frame_offset = 54;
unsigned int last_frame_offset  = 108;

byte object_under;
byte need_cleanup = 0;
byte need_cdclean = 0;
byte* clean_spr;
int clean_addr;

byte notsleeping = 0;
byte clean_dat[3][18];
byte downmap[3] = { 2, 0, 1 };
byte upmap[3] = { 0, 2, 1 };

byte statxt[39] = "TIME=--:-- LIVES=-- LEVEL=--- JOKERS=--";

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
