// SuperUwol Engine 
// Copyleft 2015 by The Mojon Twins

void coins_init (void) {
	// If screen has been visited, there's no coins.
	coins_max = coins_fr = 0;
	if (visited [n_pant]) return;
	gp_coins = (unsigned char *) coins + (n_pant << 4);
	gpit = MAX_COINS; while (gpit --) {
		rdb = gp_coins [gpit];
		if (rdb) {
			scr_buff [gp_coins [gpit]] = 0x03 | (gpit << 4);
			coins_act [gpit] = 1;
			coins_max ++;
			msl_add_coin (COINS_BASE + gpit, rdb << 4, (rdb & 0xf0) + SPRITE_ADJUST);
		} else coins_act [gpit] = 0;
	}
}

void coins_move (void) {
	if ((frame_counter & 7) == 0) {
		coins_fr = (coins_fr + 1) & 3; 
		coins_pat = 112 + (coins_fr << 2);
	}
	
	gpit = MAX_COINS; while (gpit --) {
		if (!coins_act [gpit]) {
			if (coins_ct [gpit]) {
				rdb = gp_coins [gpit];
				rdy = (rdb & 0xf0) + SPRITE_ADJUST;
				rdx = rdb << 4;
				rda = coins_ct [gpit] --;
				while (rda >= 6) rda -= 6;
				if (coins_ct [gpit] >= 16) {
					rdy = rdy - 32 + ((coins_ct [gpit] - 16) << 2); 
				} else rdy = rdy - 32;
				msl_move (COINS_BASE + gpit, rdx, rdy);
			} else msl_del (COINS_BASE + gpit);
		}		
	}
}
