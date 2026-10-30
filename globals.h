// SuperUwol Engine
// Copyleft 2015 by The Mojon Twins

extern unsigned int total_coins;

extern unsigned char scr_buff [192 + 16];
extern volatile unsigned char game_mode;
extern unsigned char dead_counter;
extern unsigned char paused;
extern unsigned char debounce_pause;
extern unsigned char gen_result;
extern unsigned char which_ending;
extern unsigned char seq_level;

// Level control
extern unsigned char n_pant, n_floor, n_column;
extern unsigned char exits_on;
extern unsigned char exit_left, exit_right;
extern unsigned char fanty_on;
extern unsigned char d1, d2;
extern unsigned char visited [55];

// Map rendering
extern unsigned char *gp_map;
extern unsigned char *gp_tsmap, *gp_tsmsh, *gp_tsmbk;
extern unsigned char rdit, rdt, rdxt, rdx, rdy, rdbyte, rdct;
extern unsigned char rdbg, rdfg;
extern int vram_offset;

// Players
extern unsigned char plife_uwol, plife_meemaid;
extern unsigned char pwins_uwol, pwins_meemaid;

// Current BG palette
extern unsigned char *c_pal_bg;

extern unsigned char half_life;
extern unsigned char frame_counter;
extern unsigned char *tileset_tmaps;

extern unsigned char i, gpit, gpjt, pad0, pad1;
extern unsigned char *gp_gen, *gp_aux, *gp_ext;
extern unsigned int gp_addr;
extern unsigned char rda, rdb, rdc;

extern unsigned char ticker;

// Players - this was an array, but
// I've unrolled it for speed.
extern signed int px_uwol, py_uwol, pvx_uwol, pvy_uwol;
extern unsigned char pfacing_uwol;
extern unsigned char pj_uwol, pctj_uwol, pjb_uwol;
extern unsigned char ppossee_uwol, ppregotten_uwol;
extern unsigned char prx_uwol, pry_uwol;
extern unsigned char pstate_uwol, pflickering_uwol;
extern unsigned char pdead_uwol;

extern signed int px_meemaid, py_meemaid, pvx_meemaid, pvy_meemaid;
extern unsigned char pfacing_meemaid;
extern unsigned char pj_meemaid, pctj_meemaid, pjb_meemaid;
extern unsigned char ppossee_meemaid, ppregotten_meemaid;
extern unsigned char prx_meemaid, pry_meemaid;
extern unsigned char pstate_meemaid, pflickering_meemaid;
extern unsigned char pdead_meemaid;

extern unsigned int pscore_uwol, pscore_meemaid;
extern unsigned char pcoins_uwol, pcoins_meemaid;

extern unsigned char psprid;
extern unsigned char ptx1, pty1, ptx2, pty2;
extern unsigned char hitv;
extern unsigned char prx, pry;
extern unsigned char game_time;

// Enemies
extern unsigned char en_x [4], en_y [4];
extern unsigned char en_x1 [3], en_y1 [3];
extern unsigned char en_x2 [3], en_y2 [3];
extern signed char en_mx [3], en_my [3];
extern unsigned char en_t [4], en_s [3];
extern unsigned char en_alive [3], en_status [3], en_ct [3];
extern unsigned char en_fr;
extern signed int enf_x, enf_vx;
extern signed int enf_y, enf_vy;

// Clothes
extern unsigned char clxy [2];

// Coins
extern unsigned char coins_act [MAX_COINS], coins_ct [MAX_COINS], coins_fr, coins_max;
extern unsigned char *gp_coins;

// ticks
extern unsigned char ticks;

// Tricky part
extern unsigned char *uwol_sgd, *meemaid_sgd, *gp_ms;
extern unsigned char *uwol_sgd_old, *meemaid_sgd_old;
extern unsigned char delay_counter;
extern unsigned char coins_pat;

extern const unsigned char tm_logo[];
extern const unsigned char pd_ts_tmaps[];
extern const unsigned char map[];
extern const unsigned char bn[];
extern const unsigned char pd_ts_win_tmap[];
extern const unsigned char tm_strip_1[];
extern const unsigned char tm_strip_2[];
extern const unsigned char pd_title_tmaps[];
extern const unsigned char pd_ts_endingok_tmap[];
extern const unsigned char pd_ts_endingko_tmap[];
