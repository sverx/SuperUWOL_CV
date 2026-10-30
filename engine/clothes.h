// SuperUwol Engine 
// Copyleft 2015 by The Mojon Twins

void clothes_init (void) {
	clxy [0] = 0;
	clxy [1] = 0;
}

void clothes_create (void) {
	// Already created?
	if (game_mode != GM_2P_COOP && clxy [0]) return;

	rdb = (clxy [0] ? 1 : 0);
	/*
	do {
		rdx = rand () & 15; rdy = rand () & 15;
		rda = rdx + (rdy << 5);
	} while (rdy < 1 || rdy > 10 || scr_buff [rda]);
	*/
	do {
		/*
		rdx = rand () & 15; rdy = rand () & 15;
		if (rdy > 10) rdy = 10;
		rda = rdx + (rdy << 4);
		*/
		rda = rand () % 176;
	} while (scr_buff [rda]);

	clxy [rdb] = rda;
	scr_buff [rda] = 0x01 | (rdb << 4);
}

void clothes_move (void) {
	// Unrolled
	rda = clxy [0];
	rdb = frame_counter & 15;
	if (rda) {	
		msl_add_item ((rda << 4) + (jitter [rdb]), SPRITE_ADJUST + (rda & 0xf0) + (jitter [15 - rdb]), 240);
	} else {
		msl_add_empty ();
	}

	rda = clxy [1];
	if (rda) {
		msl_add_item ((rda << 4) + (jitter [rdb]), SPRITE_ADJUST + (rda & 0xf0) + (jitter [15 - rdb]), 240);
	} else {
		msl_add_empty ();
	}
}
