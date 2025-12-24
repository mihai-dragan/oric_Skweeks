#define STAY		0
#define MOVE		1
#define SELECT		2
#define SLEEP		3
#define TELEPORT	4
#define BUMP		5

#define LEFT	1
#define RIGHT	2
#define UP		3
#define DOWN	4

#define BUMPER_LEFT		0
#define BUMPER_RIGHT	1
#define BUMPER_UP		2
#define BUMPER_DOWN		3

				//		0	1		2   	3
byte *object_sprs[] = { clean, clean, clean, clean, 
					//		4			5		6				7
						blue_exit, red_exit, yellow_exit, green_exit,
					//		8			9		   10			11
						arrow_right, arrow_left, arrow_up, arrow_down,
					//     12		13			14			15
						blue_tele, red_tele, yellow_tele, green_tele};

byte restartlvl = 0;
int lvltime = 0;
byte secs1, secs2, min1, min2;
byte curlevel = 0;
byte cur_player;
byte lives = 3;
byte jokers = 1;

byte lvlgrid[104];

byte select_cntr = 0;

unsigned int freq_table[3][12];

byte spr_bwidth = 3; // how many bytes wide (groups of 6 pixels)
byte spr_height = 18; // how many lines
byte last_frame = 2;
unsigned int frame_offset = 54;
unsigned int last_frame_offset  = 108;

byte object_under;
byte need_cleanup = 0;
byte need_cdclean = 0;
byte* clean_spr;

byte notsleeping = 0;
byte downmap[3] = { 2, 0, 1 };
byte upmap[3] = { 0, 2, 1 };

char statxt[39] = "LIVES            TIMER           JOKERS";
char any_key[] = "Press any key to start";
unsigned int draw_saddr = 0xa3c0;  // start address of game draw area
byte *chrs = (byte *)0x9900;  // pointer to ASCII characters
byte playing = 0;

unsigned int tele_pos[4][2];
byte tele_grid[4][2];

unsigned int cur_bumper_pos;
byte cur_bumper_frame;

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
