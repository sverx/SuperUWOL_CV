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
unsigned char hex_digit (unsigned char n);

void debug_pt_hex (unsigned char x, unsigned char y, unsigned char n);
#endif

void cls (void);

#define draw_game_tile_update_list draw_game_tile

// Draws tile rdt @ rdx, rdy
void _draw_tile_raw (void);

void draw_game_tile (void);

void draw_tile (void);

void draw_brick_direct (void);

void print_16_strip (void);

void print_logo (void);

// Draws screen pointed by n_pant
void draw_scr (void);

void p_t2 (unsigned char x, unsigned char y, unsigned char n);

void p_t3 (unsigned char x, unsigned char y, unsigned int n);

void p_t5 (unsigned char x, unsigned char y, unsigned int n);

void p_s (unsigned char x, unsigned char y, unsigned char *s);

void pyramid_draw (void);

void game_over_draw (void);

void vs_screen_round_draw (void);

void thick_number (unsigned char x, unsigned char y, unsigned char n);

inline void vs_picture_draw (void);

void vs_screen_draw (void);

void draw_frame (void);

void draw_title_logo (void);

void draw_title_menu (void);

void draw_ending_picture (void);
