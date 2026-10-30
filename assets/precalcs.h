// SuperUwol Engine 
// Copyleft 2015 by The Mojon Twins

const unsigned char exit_bounce [] = {
	160, 157, 155, 154, 153, 153, 152, 152,
	152, 152, 153, 153, 154, 155, 157, 160
};

const unsigned char pyramid_bounce [] = {
	0, 3, 4, 5, 6, 6, 7, 7,
	7, 7, 6, 6, 5, 4, 3, 0
};

const unsigned char tm_logo [] = {
	26, 26, 26, 26, 26, 26, 22, 23, 24, 25, 26, 26, 26, 26, 26, 26
};

const unsigned char tm_strip_1 [] = {
	0, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 0
};

const unsigned char tm_strip_2 [] = {
	0, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 0
};

const unsigned char bn [] = {
	1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 
	1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 
	1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 
	1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 
	1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 
	1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 
	1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 
	1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 
	1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1
};

const unsigned char frame_pals [] = {
	0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 
	0, 0, 0
};

const unsigned char jitter [] = {
	0,1,1,0,0,1,0,1,1,0,0,0,1,0,1,1
};

const unsigned char * const unsigned char ingame_tunes [] = {
	m_ingamea_psg, m_ingameb_psg, m_ingamec_psg, m_ingamed_psg, m_ingamee_psg
};

const unsigned char * const unsigned char ending_tunes [] = {
	m_endingko_psg, m_endingok_psg
};
