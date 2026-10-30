// SuperUwol Engine 
// Copyleft 2015 by The Mojon Twins

#define TI_FLOORS		72
#define TI_CEILINGS		80
#define TI_BACKGROUNDS	2
#define TI_SHADOWS		6
#define TI_BLOCKS		10
#define TI_BLOCKS_ALT	14
#define TI_BLOCKS_VERT	18
#define TI_PLAT			0
#define TI_KILL			1

#ifdef DEBUG
unsigned char hex_digit (unsigned char n) {
	if (n < 10) return n + 16;
	return n + 23;
}

void debug_pt_hex (unsigned char x, unsigned char y, unsigned char n) {
	SG_setTileatXY (x, y, hex_digit (n >> 4));
	SG_setTile (hex_digit (n & 0x0f));
}
#endif

void cls (void) {
	SG_VRAMmemset (0x1800, 0, 0x300); 
}

#define draw_game_tile_update_list draw_game_tile

// Draws tile rdt @ rdx, rdy
void _draw_tile_raw (void) {
	gp_tsmap = (unsigned char *) tileset_tmaps + (rdt << 2);
	SG_setTileatXY (rda, rdb, *gp_tsmap ++);
	SG_setTile (*gp_tsmap ++);
	SG_setNextTileatXY (rda, rdb + 1);
	SG_setTile (*gp_tsmap ++);
	SG_setTile (*gp_tsmap);
}

void draw_game_tile (void) {
	rda = rdx << 1; rdb = TOP_ADJUST + (rdy << 1);
	_draw_tile_raw ();
}

void draw_tile (void) {
	rda = rdx << 1; rdb = rdy << 1;
	_draw_tile_raw ();
}

void draw_brick_direct (void) {
	SG_setTileatXY (rda, rdb, rdt);
	SG_setTile (rdt + 1);
}

void print_16_strip (void) {
	rdx = 0; rdit = 16; while (rdit --) {
		rdt = *gp_gen ++; if (rdt) draw_tile (); 
		rdx ++;
	}
}

void print_logo (void) {
	gp_gen = (unsigned char *) tm_logo; 
	print_16_strip ();
}

// Draws screen pointed by n_pant
void draw_scr (void) {
	tileset_tmaps = (unsigned char *) pd_ts_tmaps;
	
	// (Pre)calculate metatile indexes from n_pant
	// n_pant is a 6 bits number. 
	// ppbbff
	// Palette is ignored in the SG-1000 version
	rdbg = (n_pant & 0x0f) >> 2;
	rdfg = n_pant & 0x03;

	// Each screen is 44 bytes. = 32 + 8 + 4
	gp_map = (unsigned char *) map + (n_pant << 5) + (n_pant << 3) + (n_pant << 2);

	// Render
	rdx = rdy = 0;
	rdct = 0; 
	for (rdit = 0; rdit < 192; rdit ++) {
		if (rdit < 16) {
			rda = rdx << 1;
			rdb = 2;
			rdt = TI_CEILINGS + rdfg + rdfg;
			draw_brick_direct ();
			rdxt = 3;
		} else {
			if (!rdct) rdbyte = *gp_map ++;
			rdxt = rdbyte & 0x03;
			rdbyte = rdbyte >> 2;
			rdct = (rdct + 1) & 3; 
		
			switch (rdxt) {
				case 1:
					// Kill tile
					rdt = TI_KILL;
					draw_game_tile ();
					break;
				case 2:
					// platform
					rdt = TI_PLAT;
					draw_game_tile ();
					break;
				case 3:
					// floor/ceiling/block
					if (rdy >= 11) {
						rda = rdx << 1; rdb = TOP_ADJUST + (rdy << 1);
						rdt = TI_FLOORS + rdfg + rdfg;
						draw_brick_direct ();
					} else {
						rdt = (rand () & 15) == 1 ? TI_BLOCKS_ALT + rdfg : TI_BLOCKS + rdfg;
						draw_game_tile ();
					}
					break;
			}
		}	
		scr_buff [rdit] = rdxt << 1;
		
		rdx = (rdx + 1) & 15; if (!rdx) rdy ++;
	}

	// 2nd pass: shadowed bkg
	gp_tsmbk = (unsigned char *) pd_ts_tmaps + ((TI_BACKGROUNDS + rdbg) << 2);
	gp_tsmsh = (unsigned char *) pd_ts_tmaps + ((TI_SHADOWS + rdbg) << 2);
	rdx = rdy = 0;
	for (rdit = 0; rdit < 192; rdit ++) {
		if (!scr_buff [rdit]) {
			// Believe it or not, this draws a bkg tile with shadows.
			SG_setNextTileatXY (rdx << 1, TOP_ADJUST + (rdy << 1));
			rdb = ATTR (rdx - 1, rdy);
			SG_setTile (((!rdy && rdb) || ATTR (rdx - 1, rdy - 1)) ? gp_tsmsh [0] : gp_tsmbk [0]);
			SG_setTile (ATTR (rdx, rdy - 1) ? gp_tsmsh [1] : gp_tsmbk [1]);
			SG_setNextTileatXY (rdx << 1, TOP_ADJUST + 1 + (rdy << 1));
			SG_setTile (rdb ? gp_tsmsh [2] : gp_tsmbk [2]);
			SG_setTile (gp_tsmbk [3]);			
		} else if (scr_buff [rdit] == 3) {
			if (
					(ATTR (rdx, rdy - 1) || ATTR (rdx, rdy + 1)) && 
					!((rdx & ATTR (rdx - 1, rdy) == 3) || (rdx < 15 & ATTR (rdx + 1, rdy) == 3))
			) {
				rdt = TI_BLOCKS_VERT + rdfg;
				draw_game_tile ();
			}
		}
		rdx = (rdx + 1) & 15; if (!rdx) rdy ++;
	}
}

void p_t2 (unsigned char x, unsigned char y, unsigned char n) {
	SG_setTileatXY (x, y, (n / 10) + 16);
	SG_setTile ((n % 10) + 16);
}

void p_t3 (unsigned char x, unsigned char y, unsigned int n) {
	SG_setTileatXY (x, y, (n / 100) + 16);
	SG_setTile (((n % 100) / 10) + 16);
	SG_setTile ((n % 10) + 16);
}

void p_t5 (unsigned char x, unsigned char y, unsigned int n) {
	SG_setTileatXY (x, y, (n / 10000) + 16);
	SG_setTile (((n % 10000) / 1000) + 16);
	SG_setTile (((n % 1000) / 100) + 16);
	SG_setTile (((n % 100) / 10) + 16);
	SG_setTile ((n % 10) + 16);
}

void p_s (unsigned char x, unsigned char y, unsigned char *s) {
	SG_setNextTileatXY (x, y);
	while (rda = *s ++) SG_setTile (rda - 32);
}

void pyramid_draw () {
	tileset_tmaps = (unsigned char *) pd_ts_tmaps;

	rdy = 1; print_logo ();

	gp_gen = visited; rdit = 0;
	for (rdy = 0; rdy < 10; rdy ++) {
		for (rdx = 0; rdx <= rdy; rdx ++) {
			SG_setNextTileatXY (15 - rdy + (rdx << 1), PYRAMID_TOP + rdy);
			if (*gp_gen ++ || rdit == n_pant) {
				SG_setTile (66);
				SG_setTile (67);
			} else {
				SG_setTile (64);
				SG_setTile (65);
			}
			rdit ++;
		}
	}

	rdx = 1; rdy = 9; rdt = 27; draw_game_tile ();
	p_s (0x04, 0x14, "="); p_t2 (0x05, 0x14, plife_uwol);
	p_s (0x09, 0x14, "SCORE="); p_t5 (0x0f, 0x14, pscore_uwol);
	p_s (0x16, 0x14, "COINS="); p_t3 (0x1c, 0x14, total_coins);

	if (game_mode == GM_2P_COOP) {
		rdx = 1; rdy = 10; rdt = 28; draw_game_tile ();
		p_s (0x04, 0x16, "="); p_t2 (0x05, 0x16, plife_meemaid);
		p_s (0x09, 0x16, "SCORE="); p_t5 (0x0f, 0x16, pscore_meemaid);
	}
}

void game_over_draw (void) {
	p_s (11, 9, "GAME OVER!");

	rdx = 4; rdy = 6; rdt = 27; draw_tile ();
	p_s (11, 13, "SCORE="); p_t5 (17, 13, pscore_uwol);

	if (game_mode == GM_2P_COOP) {
		rdx = 4; rdy = 7; rdt = 28; draw_tile ();
		p_s (11, 15, "SCORE="); p_t5 (17, 15, pscore_meemaid);
	}
}

void vs_screen_round_draw (void) {
	tileset_tmaps = (unsigned char *) pd_ts_tmaps;
	rdy = 1; print_logo ();
	p_s (12, 12, "ROUND"); p_t2 (18, 12, n_pant + 1);
	p_s (11, 14, "DALE FRAN!");
}

void thick_number (unsigned char x, unsigned char y, unsigned char n) {
	gp_gen = (unsigned char *) bn + (n << 4) - n;
	gpit = 5; while (gpit --) {
		SG_setNextTileatXY (x, y); 
		gpjt = 3; while (gpjt --) {
			if (*gp_gen ++) SG_setTile (9); else SG_setTile (8);
		}
		y ++;
	}
}

inline void vs_picture_draw (void) {
	gp_gen = (unsigned char *) pd_ts_win_tmap + rdt;
	for (rdy = 0; rdy < 8; rdy ++) {
		SG_setNextTileatXY (14, 8 + rdy);
		for (rdx = 0; rdx < 4; rdx ++) {
			SG_setTile (*gp_gen ++);
		} 
		gp_gen += 4;
	}
}

void vs_screen_draw (void) {
	tileset_tmaps = (unsigned char *) pd_ts_tmaps;
	rdy = 1; print_logo ();
	
	// Result
	if (pcoins_uwol > pcoins_meemaid) {
		p_s (11, 5, "UWOL WINS!");
		rdt = 0; vs_picture_draw ();
	} else if (pcoins_uwol < pcoins_meemaid) {
		p_s (10, 5, "MEEMAID WINS!");
		rdt = 4; vs_picture_draw ();
	} else {
		p_s (11, 5, "DRAW GAME!");
	}

	// Big numbers
	p_s (2, 7, "1UP UWOL");
	p_s (20, 7, "2UP MEEMAID");
	for (rdy = 9; rdy <= 15; rdy ++) {
		SG_setNextTileatXY (2, rdy);
		SG_fillTile (8, 9);
		SG_setNextTileatXY (21, rdy);
		SG_fillTile (8, 9);
	}
	thick_number (3, 10, pwins_uwol / 10);
	thick_number (7, 10, pwins_uwol % 10);
	thick_number (22, 10, pwins_meemaid / 10);
	thick_number (26, 10, pwins_meemaid % 10);
	p_s (2, 17, "COINS=");
	p_t2 (8, 17, pcoins_uwol);
	p_s (22, 17, "COINS=");
	p_t2 (28, 17, pcoins_meemaid);

	// Final text
	p_s (9, 20, "PRESS 1 TO GO!");
	p_s (9, 21, "PRESS 2 TO EXIT");
}

void draw_frame (void) {
	rdy = 0; rdx = 0; 
	gp_gen = (unsigned char *) tm_strip_1; 
	print_16_strip ();
	for (rdy = 1; rdy < 11; rdy ++) {
		rdx = 1; rdt = 33; draw_tile ();
		rdx = 14; rdt = 34; draw_tile ();
	}
	rdx = 0; gp_gen = (unsigned char *) tm_strip_2;
	print_16_strip ();
}

void draw_title_logo (void) {
	tileset_tmaps = (unsigned char *) pd_title_tmaps;

	draw_frame ();
	rdx = 5; rdy = 1; 
	for (rdt = 0; rdt < 30; rdt ++) {
		draw_game_tile ();
		rdx ++; if (rdx == 11) { rdx = 5; rdy ++; }
	}

	p_s (12, 14, "STARRING");
	p_s (9, 15, "UWOL & MEEMAID");
	p_s (8, 18, "PRESS 1 TO START");
	p_s (5, 22, "# 2016 THE MOJON TWINS");
}

void draw_title_menu (void) {
	p_s (12, 17, "1 PLAYER");
	p_s (8, 18, "    2 PLAYERS   ");
	p_s (12, 19, "VS. MODE");
}

void draw_ending_picture (void) {
	tileset_tmaps = (unsigned char *) pd_title_tmaps;
	draw_frame ();

	if (which_ending) {
		// Good text
		unpack_banks (c_pd_ts_endingok_pgt_bin, c_pd_ts_endingok_cgt_bin, 131 * 8, 3);
		SG_loadTileMapArea (8, 4, pd_ts_endingok_tmap, 16, 8);
		p_s (8, 16, "WHOAH, THAT'S IT!");
		p_s (9, 17, "I THINK WE HAVE");
		p_s (9, 18, "ENOUGH MONEY TO");
		p_s (8, 19, "BUY A CORSHONETA!");
	} else {
		// Bad text
		unpack_banks (c_pd_ts_endingko_pgt_bin, c_pd_ts_endingko_cgt_bin, 131 * 8, 3);
		SG_loadTileMapArea (8, 4, pd_ts_endingko_tmap, 16, 8);
		p_s (8, 16, "NOT ENOUGH MONEY.");
		p_s (6, 17, "I THINK WE'LL HAVE TO");
		p_s (8, 18, "ENTER THE MANSION");
		p_s (9, 19, "ONCE AGAIN...!");
	}
}
