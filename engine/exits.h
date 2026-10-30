// SuperUwol Engine 
// Copyleft 2015 by The Mojon Twins

void exits_init (void) {
	gpit = MAX_COINS; while (gpit --) msl_del (COINS_BASE + gpit);

	if (scr_buff [0xa2] == 6) {
		exit_left = 0;
	} else {
		exit_left = 1;
		rda = 4; rdb = 23; rdt = 68;
		draw_brick_direct ();
		msl_create_exit (COINS_BASE);
	}

	if (scr_buff [0xad] == 6) {
		exit_right = 0;
	} else {
		exit_right = 1;
		rda = 26; rdb = 23; rdt = 70;
		draw_brick_direct ();
		msl_create_exit (COINS_BASE + 1);
	}

	// Remove linear baddies
	gpit = 3; while (gpit --) {
		en_t [gpit] = 0;
	}
}

unsigned char exits_move (void) {
	// Exits instead of coins

	if (exit_left) {
		msl_move (COINS_BASE, 32, SPRITE_ADJUST + exit_bounce [frame_counter & 15]);
	} 

	if (exit_right) {
		msl_move (COINS_BASE + 1, 208, SPRITE_ADJUST + exit_bounce [(8 + frame_counter) & 15]);
	} 
	
	if (pad0 & (PAD_DOWN | PAD_1)) {
		if (prx_uwol >= 32-4 && prx_uwol <= 32+12 && pry_uwol == 160) {
			return GS_WIN_LEFT;
		}
		if (prx_uwol >= 208-4 && prx_uwol <= 208+12 && pry_uwol == 160) {
			return GS_WIN_RIGHT;
		}
	}

	if (pad1 & (PAD_DOWN | PAD_1)) {
		if (prx_meemaid >= 32-4 && prx_meemaid <= 32+12 && pry_meemaid == 160) {
			return GS_WIN_LEFT;
		}
		if (prx_meemaid >= 208-4 && prx_meemaid <= 208+12 && pry_meemaid == 160) {
			return GS_WIN_RIGHT;
		}
	}
	
	return 0;
}
