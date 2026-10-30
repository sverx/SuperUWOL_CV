// SuperUwol Engine 
// Copyleft 2015 by The Mojon Twins

/*volatile*/ unsigned int total_coins;

unsigned char scr_buff [192 + 16];
volatile unsigned char game_mode;
unsigned char dead_counter;
unsigned char paused;
unsigned char debounce_pause;
unsigned char gen_result;
unsigned char which_ending;
unsigned char seq_level;

// Level control
unsigned char n_pant, n_floor, n_column;
unsigned char exits_on;
unsigned char exit_left, exit_right;
unsigned char fanty_on;
unsigned char d1, d2;
unsigned char visited [55];

// Map rendering
unsigned char *gp_map;
unsigned char *gp_tsmap, *gp_tsmsh, *gp_tsmbk;
unsigned char rdit, rdt, rdxt, rdx, rdy, rdbyte, rdct;
unsigned char rdbg, rdfg;
int vram_offset;

// Players
unsigned char plife_uwol, plife_meemaid;
unsigned char pwins_uwol, pwins_meemaid;

// Current BG palette
unsigned char *c_pal_bg;

unsigned char half_life;
unsigned char frame_counter;
unsigned char *tileset_tmaps;

unsigned char i, gpit, gpjt, pad0, pad1;
unsigned char *gp_gen, *gp_aux, *gp_ext;
unsigned int gp_addr;
unsigned char rda, rdb, rdc;

unsigned char ticker;

// Players - this was an array, but
// I've unrolled it for speed.
signed int px_uwol, py_uwol, pvx_uwol, pvy_uwol;
unsigned char pfacing_uwol;
unsigned char pj_uwol, pctj_uwol, pjb_uwol;
unsigned char ppossee_uwol, ppregotten_uwol;
unsigned char prx_uwol, pry_uwol;
unsigned char pstate_uwol, pflickering_uwol;
unsigned char pdead_uwol;

signed int px_meemaid, py_meemaid, pvx_meemaid, pvy_meemaid;
unsigned char pfacing_meemaid;
unsigned char pj_meemaid, pctj_meemaid, pjb_meemaid;
unsigned char ppossee_meemaid, ppregotten_meemaid;
unsigned char prx_meemaid, pry_meemaid;
unsigned char pstate_meemaid, pflickering_meemaid;
unsigned char pdead_meemaid;

unsigned int pscore_uwol, pscore_meemaid;
unsigned char pcoins_uwol, pcoins_meemaid;

unsigned char psprid;
unsigned char ptx1, pty1, ptx2, pty2;
unsigned char hitv;
unsigned char prx, pry;
unsigned char game_time;

// Enemies
unsigned char en_x [4], en_y [4];
unsigned char en_x1 [3], en_y1 [3];
unsigned char en_x2 [3], en_y2 [3];
signed char en_mx [3], en_my [3];
unsigned char en_t [4], en_s [3];
unsigned char en_alive [3], en_status [3], en_ct [3];
unsigned char en_fr;
signed int enf_x, enf_vx;
signed int enf_y, enf_vy;

// Clothes
unsigned char clxy [2];

// Coins
unsigned char coins_act [MAX_COINS], coins_ct [MAX_COINS], coins_fr, coins_max;
unsigned char *gp_coins;

// ticks
unsigned char ticks;

// Tricky part
unsigned char *uwol_sgd, *meemaid_sgd, *gp_ms;
unsigned char *uwol_sgd_old, *meemaid_sgd_old;
unsigned char delay_counter;
unsigned char coins_pat;
