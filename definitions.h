// SuperUwol Engine
// Copyleft 2015 by The Mojon Twins

//#define ATTR(x,y)		((y)>11?0:scr_buff[((y)<<4)+((x)&15)])
#define ATTR(x,y)		(scr_buff[((y)<<4)+((x)&15)])
#define TILEAT(x,y)		scr_buff[((y) << 4)+(x)]
#define SGNI(n)			((n)<0?-1:1)
#define SGNC(a,b,c)		((a)<(b)?-(c):(c))
#define SATURATE_Z(n)	((n)<0?0:(n))
#define SATURATE(v,max) ((v)>=0?((v)>(max)?(max):(v)):((v)<-(max)?-(max):(v)))
#define ABS(n)			((n)<0?-(n):(n))
#define DELTA(a,b)		((a)<(b)?(b)-(a):(a)-(b))
#define CL(x1,y1,x2,y2)	((x1)+4>=(x2)&&(x1)<=(x2)+12&&(y1)+12>=(y2)&&(y1)<=(y2)+12)
#define UPDATE			update_list [update_list_index ++]

// Game modes

#define GM_1P			1
#define GM_2P_COOP		2
#define GM_2P_VS		3

// Player status / cell calculation

#define PFACING_RIGHT	0
#define PFACING_LEFT	4
#define PSTATE_NORMAL	0
#define PSTATE_NAKED	8
#define PCELL_STANDING	0
#define PCELL_RUNNING0	0
#define PCELL_AIRBORNE	4
#define PCELL_HIT		0
#define PCELL_DEAD		0
#define PCELL_UWOL		0
#define PCELL_MEEMAID	16

#define PLAYER_UWOL		0
#define PLAYER_MEEMAID	1

// Players are in a fixed location
// at the beginning of the OAM

#define OAM_UWOL		0
#define OAM_MEEMAID		16

// Game state.
// 'Game Over' also means 'both players dead' in VS. mode
// GS_WIN_* is when screen is cleared in 1P / 2P_COOP modes.

#define GS_GAME_OVER	1
#define GS_WIN			2
#define GS_WIN_LEFT		3
#define GS_WIN_RIGHT	4

// Music

#define MUSIC_TITLE		m_title_psg
#define MUSIC_FANTY		m_fanty_psg
#define MUSIC_PYRAMID	m_pyramid_psg
#define MUSIC_DALE_FRAN m_dalefran_psg
#define MUSIC_VS		m_vs_psg
#define MUSIC_GAME_OVER m_gover_psg


// Sound channels

#define SC_UWOL			0
#define SC_MEEMAID		1
#define SC_ENEMS		2
#define SC_LEVEL		2

// Sound effects

#define SFX_SELECT		sfx_select_psg
#define SFX_START		sfx_start_psg
#define SFX_JUMP		sfx_jump_psg
#define SFX_CLOTHES		sfx_shirt_psg
#define SFX_PLAYER_HIT	sfx_kill_psg
#define SFX_COIN		sfx_coins_psg
#define SFX_TIC_TOC		sfx_select_psg
#define SFX_LAST_COIN	sfx_start_psg
#define SFX_SPIKE		sfx_kill_psg
#define SFX_FANTY		sfx_fanty_psg
#define SFX_NINTENDONT	sfx_select_psg

// Custom pad reading (maybe I will ditch this!)

#define PAD_UP 0x01
#define PAD_DOWN 0x04
#define PAD_LEFT 0x08
#define PAD_RIGHT 0x02
#define PAD_1 0x40
#define PAD_2 0x80
#define PAD_START PAD_1
#define PAD_SELECT PAD_2

// For the sprite mixer

#define MS_TYPE_EMPTY	0
#define MS_TYPE_COIN 	1
#define MS_TYPE_PLAYER	2
#define MS_TYPE_ELSE	3
#define MS_TYPE_ITEM	4

#define COINS_BASE		2
#define REST_BASE		15
