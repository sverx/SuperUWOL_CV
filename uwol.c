// SuperUwol Engine
// Copyleft 2015 by The Mojon Twins

//#define DEBUG

void UNSAFE_SMS_loadaPLibcompressedTilesatAddr (const void *src, unsigned int dst) __naked __sdcccall(1);
#define aPLib_depack_VRAM(dst,src)  UNSAFE_SMS_loadaPLibcompressedTilesatAddr((src),(dst))

#define MAXSPRITES  32
extern unsigned char SpriteTable[MAXSPRITES*4];
extern unsigned char SpriteNextFree;

void SG_addMetaSprite1x1 (unsigned char x, unsigned char y, const unsigned char *mt) {
  unsigned char *ptr=&SpriteTable[SpriteNextFree*4];
	mt += 2;
	*ptr++ = y;
	*ptr++ = x;
	*ptr++ = *mt ++;
	*ptr++ = *mt ++;
	mt += 2;
	*ptr++ = y;
	*ptr++ = x;
	*ptr++ = *mt ++;
	*ptr++ = *mt ++;
  SpriteNextFree+=2;
}

void SG_addMetaSprite (unsigned char x, unsigned char y, const unsigned char *mt) {
  unsigned char *ptr=&SpriteTable[SpriteNextFree*4];
	while (0x80 != (*ptr = *mt ++)) {
		*ptr++ += y;
		*ptr++ = x + *mt ++;
		*ptr++ = *mt ++;
		*ptr++ = *mt ++;
    SpriteNextFree++;
	}
}

#define UPDATE_LIST_SIZE	30
#define MSB(x)				((x)>>8)
#define LSB(x)				((x)&0xff)
#define SPRITE_ADJUST		7
//~ #define TOP_ADJUST			1

// OAM mapping...
/*
	OAM #	byte #	#	what
	0 		0 		4 	P1 (Uwol)
	4 		16		4 	P2 (Meemaid)
	8 		32		2 	Item
	10 		40 		2 	Enem 0
	12 		48		2 	Enem 2
	14 		56 		2 	Enem 3
	16 		64		2 	Fanty
	18 		72	 	2 	Coins... (up to 15)
*/
#define OAM_BASE_P1		0
#define OAM_BASE_P2		16
#define OAM_BASE_ITEM	32
#define OAM_BASE_ENEMS	40
#define OAM_BASE_COINS	72

// Sverx's

#include "../SGlib/SGlib.h"
#include "../PSGlib/PSGlib.h"
//~ #include "lib/aPLib.h"

//~ #define PSGPlay(a);            ;
//~ #define PSGPlayNoRepeat(a);    ;
//~ #define PSGStop();             ;
//~ #define PSGFrame();            ;
//~ #define PSGSFXPlay(a,b);       ;
//~ #define PSGSFXStop();          ;
//~ #define PSGSFXFrame();         ;
//~ #define PSGGetStatus()         0

void SG_fillTile (unsigned char tile, unsigned char num) {
  while (num--)
    SG_setTile(tile);
}

// Please please pretty please change this
unsigned long int next = 1;

unsigned char rand (void) {
    next = next * 1103515245UL + 12345;
    return (unsigned char) (next / 65536) & 255;
}

void srand (unsigned int seed) {
    next = seed;
}
// Change this for something FASTER!


// Some needed stuff...
#include "definitions.h"
#include "config.h"

// From external modules: ogt and cbins
#include "murcia.h"
#include "cbins.h"

// Main const includes
#include "assets/uwolmap.h"
#include "assets/uwolenems.h"
#include "assets/precalcs.h"
#include "assets/pd_ss_pl.h"
#include "assets/tm_ts.h"
#include "assets/tm_ss_en.h"
#include "assets/tm_title.h"
#include "assets/tm_ss_pl_dead.h"
#include "assets/tm_endingko.h"
#include "assets/tm_endingok.h"
#include "assets/tm_win.h"
#include "assets/metaspriteset.h"

// variables
/*volatile*/ unsigned int total_coins;

unsigned char scr_buff [192 + 16];
volatile unsigned char game_mode;
unsigned char dead_counter;
unsigned char paused;
unsigned char debounce_pause;
unsigned char gen_result;
unsigned char which_ending;
unsigned char seq_level;

// Level control
unsigned char n_pant, n_floor, n_column;
unsigned char exits_on;
unsigned char exit_left, exit_right;
unsigned char fanty_on;
unsigned char d1, d2;
unsigned char visited [55];

// Map rendering
unsigned char *gp_map;
unsigned char *gp_tsmap, *gp_tsmsh, *gp_tsmbk;
unsigned char rdit, rdt, rdxt, rdx, rdy, rdbyte, rdct;
unsigned char rdbg, rdfg;
int vram_offset;

// Players
unsigned char plife_uwol, plife_meemaid;
unsigned char pwins_uwol, pwins_meemaid;

// Current BG palette
unsigned char *c_pal_bg;

unsigned char half_life;
unsigned char frame_counter;
unsigned char *tileset_tmaps;

unsigned char i, gpit, gpjt, pad0, pad1;
unsigned char *gp_gen, *gp_aux, *gp_ext;
unsigned int gp_addr;
unsigned char rda, rdb, rdc;

unsigned char ticker;

// Players - this was an array, but
// I've unrolled it for speed.
signed int px_uwol, py_uwol, pvx_uwol, pvy_uwol;
unsigned char pfacing_uwol;
unsigned char pj_uwol, pctj_uwol, pjb_uwol;
unsigned char ppossee_uwol, ppregotten_uwol;
unsigned char prx_uwol, pry_uwol;
unsigned char pstate_uwol, pflickering_uwol;
unsigned char pdead_uwol;

signed int px_meemaid, py_meemaid, pvx_meemaid, pvy_meemaid;
unsigned char pfacing_meemaid;
unsigned char pj_meemaid, pctj_meemaid, pjb_meemaid;
unsigned char ppossee_meemaid, ppregotten_meemaid;
unsigned char prx_meemaid, pry_meemaid;
unsigned char pstate_meemaid, pflickering_meemaid;
unsigned char pdead_meemaid;

unsigned int pscore_uwol, pscore_meemaid;
unsigned char pcoins_uwol, pcoins_meemaid;

unsigned char psprid;
unsigned char ptx1, pty1, ptx2, pty2;
unsigned char hitv;
unsigned char prx, pry;
unsigned char game_time;

// Enemies
unsigned char en_x [4], en_y [4];
unsigned char en_x1 [3], en_y1 [3];
unsigned char en_x2 [3], en_y2 [3];
signed char en_mx [3], en_my [3];
unsigned char en_t [4], en_s [3];
unsigned char en_alive [3], en_status [3], en_ct [3];
unsigned char en_fr;
signed int enf_x, enf_vx;
signed int enf_y, enf_vy;

// Clothes
unsigned char clxy [2];

// Coins
unsigned char coins_act [MAX_COINS], coins_ct [MAX_COINS], coins_fr, coins_max;
unsigned char *gp_coins;

// ticks
unsigned char ticks;

// Tricky part
unsigned char *uwol_sgd, *meemaid_sgd, *gp_ms;
unsigned char *uwol_sgd_old, *meemaid_sgd_old;
unsigned char delay_counter;
unsigned char coins_pat;


// Functions

#include "loader.h"
#include "engine/general.h"
#include "engine/metasprites.h"
#include "engine/printer.h"
#include "engine/hud.h"
#include "engine/spr_mixer.h"
#include "engine/clothes.h"
#include "engine/player.h"
#include "engine/enengine.h"
#include "engine/coins.h"
#include "engine/exits.h"
#include "engine/game_loop.h"

// Main

void main (void) {

  SG_mapROMBank(1);  // ensure bank 1 is mapped

	ticks = 60;

	SG_displayOff ();
	SG_setSpriteMode (SG_SPRITEMODE_LARGE);

	unpack_font ();
	intro_screen ();
	unpack_game_tiles ();
	unpack_game_sprites ();

	// intro_screen ();

	while (1) {
		title_do ();

		n_pant = 0; n_floor = 0; n_column = 0;
		gpit = 55; while (gpit --) visited [gpit] = 0;
		plife_uwol = 5; plife_meemaid = (game_mode == GM_1P ? 0 : 5);
		pwins_uwol = 0; pwins_meemaid = 0;
		total_coins = 0; seq_level = 0;

		while (1) {
			if (game_mode == GM_2P_VS) {
				vs_screen_round ();
			} else {
				pyramid_screen_do ();
			}

			game_loop ();

			if (game_mode == GM_2P_VS) {
				vs_screen_do ();
				if (!gen_result) break;
				n_pant ++; if (n_pant == 55) n_pant = 0;
			} else {
				if (gen_result == GS_GAME_OVER) {
					if (!plife_uwol && !plife_meemaid) {
						game_over ();
						break;
					}
				} else {
					visited [n_pant] = 1;
					n_floor ++;
					if (n_floor < 10) {
						if (gen_result == GS_WIN_LEFT) {
							n_pant = n_pant + n_floor;
						} else {
							n_pant = n_pant + n_floor + 1;
							n_column ++;
						}
					} else {
						ending_do ();
						if (!which_ending) {
							n_pant = 0; n_floor = 0; n_column = 0;
						} else break;
					}
				}
			}
		}
	}
}
