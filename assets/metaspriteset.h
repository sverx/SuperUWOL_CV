// SuperUwol Engine
// Copyleft 2015 by The Mojon Twins

// Metasprites for UWOL and MEEMAID.
// Actual pattern data will be written to the SGT each frame.

// That means that UWOL will always use patterns 0-15 and meemaid 16-31

const unsigned char pd_ss_pl_uwol [] = {
	// Subspr (0, 0) cut from (0, 0) => (15,15).
	0xf0, 0xfc, 0x00, 0x06, 0xf0, 0xfc, 0x04, 0x0b,
	// Subspr (0, 1) cut from (0, 16) => (15,31).
	0x00, 0xfc, 0x08, 0x06, 0x00, 0xfc, 0x0c, 0x0b,
	0x80
};

const unsigned char pd_ss_pl_meemaid [] = {
	// Subspr (0, 0) cut from (16, 0) => (31,15).
	0xf0, 0xfc, 0x10, 0x0d, 0xf0, 0xfc, 0x14, 0x0e,
	// Subspr (0, 1) cut from (16, 16) => (31,31).
	0x00, 0xfc, 0x18, 0x0d, 0x00, 0xfc, 0x1c, 0x0e,
	0x80
};

const unsigned char pl_animations [] = {
	0, 1, 0, 2, 3
};
// STD = 0,
// WALK = 0 1 2 3 ...
// JUMP/FALL = 4

const unsigned char *  spr_enems [] = {
	pd_ss_en_spr_00, pd_ss_en_spr_01, pd_ss_en_spr_02, pd_ss_en_spr_03,
	pd_ss_en_spr_04, pd_ss_en_spr_05, pd_ss_en_spr_06, pd_ss_en_spr_07
};

const unsigned char *  spr_fanty [] = {
	pd_ss_en_spr_08, pd_ss_en_spr_09, pd_ss_en_spr_0a, pd_ss_en_spr_0b
};
