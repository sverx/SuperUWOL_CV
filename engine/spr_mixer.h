// SuperUwol Engine 
// Copyleft 2015 by The Mojon Twins

// This version has been specially coded for the SEGA 8-bit 
// specially for the SG-1000

#define MS_MAX		21
#define MS_PRIME	8
#define MS_SKIP		72

void *msl_meta [MS_MAX];
unsigned char msl_x [MS_MAX];
unsigned char msl_y [MS_MAX];
unsigned char msl_t [MS_MAX];
unsigned char msl_i, msl_oami;

void msl_init (void) {
	gpit = MS_MAX; while (gpit --) msl_t [gpit] = MS_TYPE_EMPTY;
	msl_meta [0] = (void *) pd_ss_pl_uwol; msl_t [0] = MS_TYPE_PLAYER;
	msl_meta [1] = (void *) pd_ss_pl_meemaid; msl_t [1] = MS_TYPE_PLAYER;
}

void msl_open (void) {
	msl_i = REST_BASE;
}

void msl_add (unsigned char x, unsigned char y, void *ms) {
	msl_t [msl_i] = MS_TYPE_ELSE;
	msl_x [msl_i] = x;
	msl_y [msl_i] = y;
	msl_meta [msl_i ++] = ms;
}

void msl_add_item (unsigned char x, unsigned char y, unsigned char t) {
	msl_t [msl_i] = MS_TYPE_ITEM;
	msl_x [msl_i] = x;
	msl_y [msl_i] = y;
	msl_meta [msl_i ++] = (void *) t;
}

void msl_add_empty (void) {
	msl_t [msl_i ++] = MS_TYPE_EMPTY;
}

inline void msl_add_coin (unsigned char cid, unsigned char x, unsigned char y) {
	msl_x [cid] = x;
	msl_y [cid] = y;
	msl_t [cid] = MS_TYPE_COIN;
}

inline void msl_create_exit (unsigned char cid) {
	msl_t [cid] = MS_TYPE_ITEM;
	msl_meta [cid] = (void *) 244;
}

inline void msl_del (unsigned char cid) {
	msl_t [cid] = MS_TYPE_EMPTY;
}

inline void msl_move (unsigned char cid, unsigned char x, unsigned char y) {
	msl_x [cid] = x;
	msl_y [cid] = y;
}

inline void msl_change_meta (unsigned char cid, void *ms) {
	msl_meta [cid] = ms;
}

inline void msl_close (void) {
	gpjt = frame_counter & 7;	
	gpit = MS_MAX; while (gpit --) {
		// Dirty but fast...
		gp_ms = msl_meta [gpjt]; 
		switch (msl_t [gpjt]) {
			case MS_TYPE_COIN:
				SG_addSprite (msl_x [gpjt], msl_y [gpjt], coins_pat, 0x0b);
				break;
			case MS_TYPE_PLAYER:
				//ms_to_sat (msl_x [gpjt], msl_y [gpjt]);
				SG_addMetaSprite (msl_x [gpjt], msl_y [gpjt], (unsigned char *) gp_ms);
				break;
			case MS_TYPE_ELSE:
				//rdx = msl_x [gpjt]; rdy = msl_y [gpjt];
				//ms_to_sat_hack_fast ();
				SG_addMetaSprite1x1 (msl_x [gpjt], msl_y [gpjt], (unsigned char *) gp_ms);
				break;
			case MS_TYPE_ITEM:
				SG_addSprite (msl_x [gpjt], msl_y [gpjt], (unsigned char) gp_ms, 0x0f);
				break;
		}
		
		gpjt += MS_PRIME; if (gpjt >= MS_MAX) gpjt -= MS_MAX;
	}
}
