// SuperUwol Engine
// Copyleft 2015 by The Mojon Twins

void tick_tock (void) {
	ticker ++; if (ticker == ticks) {
		ticker = 0;
		game_time --;
	}
}

void enter_screen (void (*func) (void)) {
	cls ();
	(*func) ();
	SG_displayOn ();
}

void exit_cleanly (void) {
	ms_clear_all_sprites ();
	PSGStop ();
	PSGSFXStop ();
	SG_displayOff ();
}

void game_loop (void) {
	cls ();

	msl_init ();
	draw_scr ();
	enems_load ();
	coins_init ();
	players_init ();
	clothes_init ();
	print_hud ();

	exits_on = 0;
	half_life = 0;
	frame_counter = 0;
	coins_pat = 112;
	ticker = 0;
	dead_counter = 100;
	fanty_on = visited [n_pant];
	paused = 0;
	pcoins_uwol = 0; pcoins_meemaid = 0;

	// 1P : Time = 2 x coins.
	// 2P : Time = 1.5 x coins.
	game_time = coins_max << 1;
	if (game_mode != GM_1P)
		game_time = game_time - (coins_max >> 1);
	else
		msl_move (1, 255, 239);

	SG_displayOn ();

	PSGPlay (ingame_tunes [seq_level]);
	seq_level ++; if (seq_level == 5) seq_level = 0;

	while (1) {
		pad0 = pad_poll (0); pad1 = pad_poll (1);
		/*
		if ((pad0 | pad1) & PAD_START) {
			if (!debounce_pause) {
				debounce_pause = 1;
				paused = !paused;
				//sfx_play (SFX_START, SC_LEVEL);
				//music_pause (paused);
			}
		} else debounce_pause = 0;
		*/
		half_life = 1 - half_life;
		frame_counter ++;

		if (!paused) {
			ticker ++; if (ticker == ticks) {
				ticker = 0;
				if (game_time) {
					if (game_time <= 6) PSGSFXPlay (SFX_TIC_TOC, SC_LEVEL);
					game_time --; show_time ();
				} else if (!fanty_on) {
					PSGStop ();
					PSGSFXPlay (SFX_FANTY, SC_LEVEL);
					PSGPlay (MUSIC_FANTY);
					fanty_init ();
					fanty_on = 1; en_t [3] = 6;
				}
			}
		}

		SG_initSprites ();
		msl_open ();		// Start adding sprites for hashed order

		if (!exits_on) {
			coins_move ();
			if (!coins_max) {
				if (game_mode != GM_2P_VS) {
					exits_on = 1;
					exits_init ();
				} else {
					gen_result = GS_WIN;
					break;
				}
			}
		} else {
			gen_result = exits_move ();
			if (gen_result) {
				PSGStop ();
				while (game_time --) {
					show_time ();
					add_to_score_uwol (SCORE_SECONDS);
					if (game_mode == GM_2P_COOP)
						add_to_score_meemaid (SCORE_SECONDS);
					PSGSFXPlay (SFX_COIN, SC_LEVEL);
					delay (4);
				}
				break;
			}
		}

		clothes_move ();
		enems_move ();
		if (!paused) players_move ();

		msl_close ();
		SG_finalizeSprites ();

		SG_waitForVBlank ();
		SG_copySpritestoSAT ();

		// Copy 128 bytes for UWOL
		if (uwol_sgd != uwol_sgd_old) SG_VRAMmemcpy (0x3800, uwol_sgd, 128);

		// Copy 128 bytes for MEEMAID
		if (meemaid_sgd != meemaid_sgd_old) SG_VRAMmemcpy (0x3880, meemaid_sgd, 128);

		uwol_sgd_old = uwol_sgd;
		meemaid_sgd_old = meemaid_sgd;

		// Music / SFX frame
    SG_mapROMBank(2);
		PSGFrame ();
		PSGSFXFrame ();
    SG_mapROMBank(1);

		if (pdead_uwol && (game_mode == GM_1P || pdead_meemaid)) {
			if (dead_counter) {
				dead_counter --;
			} else {
				gen_result = GS_GAME_OVER; break;
			}
		}
	}

	// Exit cleanly...
	exit_cleanly ();
}

void wait_time_or_input (void) {
	ticker = 0;
	rda = ((pad_poll (0) | pad_poll (1)) != 0);
	while (game_time) {
		tick_tock ();

		if (SG_getKeysStatus ()) {
			if (!rda) break;
		} else {
			rda = 0;
		}

		SG_waitForVBlank ();
    SG_mapROMBank(2);
		PSGFrame ();
    SG_mapROMBank(1);
	}
}

void pyramid_screen_do (void) {
	enter_screen (pyramid_draw);

	// Base for pointing arrow:
	rdx = 1 + 8 * (15 - n_floor + (n_column << 1));
	rdy = SPRITE_ADJUST + ((PYRAMID_TOP + n_floor) << 3) - 20;

	PSGPlay (MUSIC_PYRAMID);

	game_time = PYRAMID_SCREEN_TIME; ticker = 0;

	//rda = ((pad_poll (0) | pad_poll (1)) != 0);
	rda = (SG_getKeysStatus () != 0);
	while (game_time) {
		frame_counter ++;
		tick_tock ();

		SG_initSprites ();
		//SG_addMetaSprite1x1 (rdx, rdy - pyramid_bounce [frame_counter & 15], spr_items [2]);
		SG_addSprite (rdx, rdy - pyramid_bounce [frame_counter & 15], 244, 0x0b);
		SG_finalizeSprites ();

		if (pad_poll (0) || pad_poll (1)) {
			if (!rda) break;
		} else {
			rda = 0;
		}

		SG_waitForVBlank ();
		SG_copySpritestoSAT ();
    SG_mapROMBank(2);
		PSGFrame ();
    SG_mapROMBank(1);
	}

	// Exit cleanly
	exit_cleanly ();
}

void vs_screen_round (void) {
	enter_screen (vs_screen_round_draw);

	PSGPlay (MUSIC_DALE_FRAN);

	game_time = ROUND_SCREEN_TIME;
	wait_time_or_input ();

	// Exit cleanly
	exit_cleanly ();
}

void vs_screen_do (void) {

	if (pcoins_uwol > pcoins_meemaid) {
		pwins_uwol ++;
	} else if (pcoins_uwol < pcoins_meemaid) {
		pwins_meemaid ++;
	}

	enter_screen (vs_screen_draw);

	PSGPlay (MUSIC_VS);

	rda = (SG_getKeysStatus () != 0);
	while (1) {
		i = (pad_poll (0) | pad_poll (1));
		if (i) {
			if (!rda) {
				rda = 1;
				if (i & PAD_1) { gen_result = 1; break; }
				if (i & PAD_2) { gen_result = 0; break; }
			}
		} else rda = 0;

		SG_waitForVBlank ();
    SG_mapROMBank(2);
		PSGFrame ();
    SG_mapROMBank(1);
	}

	// Exit cleanly
	exit_cleanly ();
}

void title_do (void) {
	enter_screen (draw_title_logo);

	rda = (SG_getKeysStatus () != 0);
	PSGPlayNoRepeat (MUSIC_TITLE);
	while (PSGGetStatus ()) {
		if ((pad_poll (0) | pad_poll (1)) & PAD_START) {
			if (!rda) { rdc = 0; break; }
		} else {
			rda = 0;
		}
		SG_waitForVBlank ();
    SG_mapROMBank(2);
		PSGFrame ();
    SG_mapROMBank(1);
	}
	PSGStop ();

	draw_title_menu ();
	rda = (SG_getKeysStatus () != 0);
	game_mode = 1;
	while (1) {
		frame_counter ++;
		SG_initSprites ();
		SG_addMetaSprite1x1 (80 - (pyramid_bounce [frame_counter & 15] >> 1), ((15 + game_mode) << 3) + 6, pd_ss_en_spr_0c);
		SG_finalizeSprites ();

		rdc = game_mode;
		i = (pad_poll (0) | pad_poll (1));
		if (i) {
			if (!rda) {
				rda = 1;
				if (i & PAD_DOWN) if (game_mode < 3) game_mode ++;
				if (i & PAD_UP) if (game_mode > 1) game_mode --;
				if ((i & PAD_1)) break;
			}
		} else rda = 0;
		if (game_mode != rdc) PSGSFXPlay (SFX_SELECT, SC_LEVEL);

		SG_waitForVBlank ();
		SG_copySpritestoSAT ();
    SG_mapROMBank(2);
		PSGSFXFrame ();
    SG_mapROMBank(1);
	}

	PSGSFXPlay (SFX_START, SC_LEVEL);
	delay (60);

	// Exit cleanly
	exit_cleanly ();
}

void ending_do (void) {
	which_ending = (total_coins >= 256) ? 16 : 0;
	enter_screen (draw_ending_picture);

	PSGPlay (ending_tunes [(which_ending != 0)]);

	game_time = ENDING_SCREEN_TIME;
	wait_time_or_input ();

	// Exit cleanly
	exit_cleanly ();
	unpack_game_tiles ();
}

void game_over (void) {
	enter_screen (game_over_draw);

	PSGPlay (MUSIC_GAME_OVER);

	game_time = GAME_OVER_SCREEN_TIME;
	wait_time_or_input ();

	// Exit cleanly
	exit_cleanly ();
}

void intro_screen (void) {
	cls ();

	p_s (5, 22, "# 2016 THE MOJON TWINS");
	p_s (6, 23, "NOT LICENSED BY SEGA");

	SG_displayOn ();

	game_time = ROUND_SCREEN_TIME;
	wait_time_or_input ();

	exit_cleanly ();
}
