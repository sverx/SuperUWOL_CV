// SuperUwol Engine
// Copyleft 2015 by The Mojon Twins

//~ #define PNTADDRESS      0x1800
//~ #define SATADDRESS      0x1B00
#define PGT_BASE      0x0000
#define CGT_BASE      0x2000
#define SGT_BASE      0x3800

#define PATTERN_DATA_BANK_A  0
#define PATTERN_DATA_BANK_B  (256*8)
#define PATTERN_DATA_BANK_C  (256*8*2)

void unpack_banks (unsigned char *c_pgt, unsigned char *c_cgt, unsigned int offset, unsigned char banks) {
	if (banks & 1) {
		aPLib_depack_VRAM (PGT_BASE + PATTERN_DATA_BANK_A + offset, c_pgt);
		aPLib_depack_VRAM (CGT_BASE + PATTERN_DATA_BANK_A + offset, c_cgt);
	}
	if (banks & 2) {
		aPLib_depack_VRAM (PGT_BASE + PATTERN_DATA_BANK_B + offset, c_pgt);
		aPLib_depack_VRAM (CGT_BASE + PATTERN_DATA_BANK_B + offset, c_cgt);
	}
	if (banks & 4) {
		aPLib_depack_VRAM (CGT_BASE + PATTERN_DATA_BANK_C + offset, c_cgt);
		aPLib_depack_VRAM (PGT_BASE + PATTERN_DATA_BANK_C + offset, c_pgt);
	}
}

void reload_tmap (void) {
	unpack_banks (c_pd_ts_pgt_bin, c_pd_ts_cgt_bin, 131 * 8, 7);
	unpack_banks (c_pd_ts_win_pgt_bin, c_pd_ts_win_cgt_bin, 190 * 8, 3);
}

inline void unpack_game_sprites (void) {
	aPLib_depack_VRAM (SGT_BASE + 32 * 8, c_pd_ss_pl_dead_sgt_bin);
	aPLib_depack_VRAM (SGT_BASE + 112 * 8, c_pd_ss_coin_sgt_bin);
	aPLib_depack_VRAM (SGT_BASE + 128 * 8, c_pd_ss_en_sgt_bin);
	aPLib_depack_VRAM (SGT_BASE + 240 * 8, c_pd_ss_items_sgt_bin);
}

inline void unpack_font (void) {
	unpack_banks (c_pd_font_pgt_bin, c_pd_font_cgt_bin, 0, 7);
}

void unpack_game_tiles (void) {
	unpack_banks (c_pd_title_pgt_bin, c_pd_title_cgt_bin, 88 * 8, 7);
	reload_tmap ();
}
