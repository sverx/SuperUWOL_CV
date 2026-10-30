// SuperUwol Engine 
// Copyleft 2015 by The Mojon Twins
/*
inline void ms_to_sat (unsigned char x, unsigned char y) {
	while ((rdx = *gp_ms ++) != 0x80) {
		rdx += x;
		rdy = y + *gp_ms ++; rdt = *gp_ms ++; rdc = *gp_ms ++;
		SG_addSprite (rdx, rdy, rdt, rdc);
		if (rdx > 240) {
			rdx -= 224;
			SG_addSprite (rdx, rdy, rdt, 0x80 | rdc);
		}
	}
}

inline void ms_to_sat_hack_fast (void) {
	gp_ms += 2; rdt = *gp_ms ++; rdc = *gp_ms ++;
	SG_addSprite (rdx, rdy, rdt, rdc);
	gp_ms += 2; rdt = *gp_ms ++; rdc = *gp_ms ++;
	SG_addSprite (rdx, rdy, rdt, rdc);
}
*/
inline void ms_clear_all_sprites (void) {
	SG_initSprites ();
	SG_finalizeSprites ();
	SG_copySpritestoSAT ();
}
