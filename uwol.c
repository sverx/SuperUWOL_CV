// SuperUwol Engine 
// Copyleft 2015 by The Mojon Twins

//#define DEBUG

#define UPDATE_LIST_SIZE	30
#define MSB(x)				((x)>>8)
#define LSB(x)				((x)&0xff)
#define SPRITE_ADJUST		7
#define TOP_ADJUST			1

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

#include "lib/SGlib.h"
#include "lib/PSGlib.h"
#include "lib/aPLib.h"

// Please please pretty please change this

#include "rand.h"

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

// Some variables

#include "globals.h"

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
