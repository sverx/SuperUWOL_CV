;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.5.2 #9293 (MINGW32)
; This file was generated Fri Sep 09 08:33:08 2016
;--------------------------------------------------------
	.module SGlib
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _SG_setReg
	.globl _VDPReg
	.globl _stp
	.globl _SpriteTable
	.globl _PreviousKeysStatus
	.globl _KeysStatus
	.globl _PauseRequested
	.globl _VDPBlank
	.globl _VDPReg_init
	.globl _SG_VDPturnOnFeature
	.globl _SG_VDPturnOffFeature
	.globl _SG_init
	.globl _SG_setBackdropColor
	.globl _SG_setSpriteMode
	.globl _SG_loadTilePatterns
	.globl _SG_loadTileColours
	.globl _SG_loadSpritePatterns
	.globl _SG_setTileatXY
	.globl _SG_setNextTileatXY
	.globl _SG_setTile
	.globl _SG_fillTile
	.globl _SG_loadTileMapArea
	.globl _SG_initSprites
	.globl _SG_addSprite
	.globl _SG_addMetaSprite1x1
	.globl _SG_addMetaSprite
	.globl _SG_finalizeSprites
	.globl _SG_copySpritestoSAT
	.globl _SG_waitForVBlank
	.globl _SG_getKeysStatus
	.globl _SG_queryPauseRequested
	.globl _SG_resetPauseRequest
	.globl _SG_VRAMmemset
	.globl _UNSAFE_SG_copySpritestoSAT
	.globl _UNSAFE_SG_VRAMmemcpy128
	.globl _SG_isr
	.globl _SG_nmi_isr
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
_VDPControlPort	=	0x00bf
_VDPStatusPort	=	0x00bf
_VDPDataPort	=	0x00be
_VDPVCounterPort	=	0x007e
_VDPHCounterPort	=	0x007f
_IOPortL	=	0x00dc
_IOPortH	=	0x00dd
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_VDPBlank::
	.ds 1
_PauseRequested::
	.ds 1
_KeysStatus::
	.ds 2
_PreviousKeysStatus::
	.ds 2
_SpriteTable::
	.ds 128
_stp::
	.ds 2
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
_VDPReg::
	.ds 2
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;SGlib.c:155: void SG_setReg (unsigned char reg, unsigned char v) {
;	---------------------------------
; Function SG_setReg
; ---------------------------------
_SG_setReg::
;SGlib.c:156: VDPReg [reg] = v;
	ld	a,#<(_VDPReg)
	ld	hl,#2
	add	hl,sp
	add	a, (hl)
	ld	e,a
	ld	a,#>(_VDPReg)
	adc	a, #0x00
	ld	d,a
	ld	iy,#3
	add	iy,sp
	ld	a,0 (iy)
	ld	(de),a
;SGlib.c:157: SG_write_to_VDPRegister (reg, v);
	di 
	ld	a,0 (iy)
	out	(_VDPControlPort),a
	ld	iy,#2
	add	iy,sp
	ld	a,0 (iy)
	set	7, a
	out	(_VDPControlPort),a
	ei 
	ret
_VDPReg_init:
	.db #0x02	; 2
	.db #0xA0	; 160
	.db #0x06	; 6
	.db #0xFF	; 255
	.db #0x03	; 3
	.db #0x36	; 54	'6'
	.db #0x07	; 7
	.db #0x01	; 1
;SGlib.c:160: void SG_VDPturnOnFeature (unsigned int feature) {
;	---------------------------------
; Function SG_VDPturnOnFeature
; ---------------------------------
_SG_VDPturnOnFeature::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
;SGlib.c:162: VDPReg[HI(feature)]|=LO(feature);
	ld	e,5 (ix)
	ld	d,#0x00
	ld	hl,#_VDPReg
	add	hl,de
	ld	c,(hl)
	ld	a,4 (ix)
	ld	-2 (ix),a
	ld	-1 (ix),#0x00
	ld	b,#0x00
	ld	a,c
	or	a, -2 (ix)
	ld	c,a
	ld	a,b
	or	a, -1 (ix)
	ld	b,a
	ld	(hl),c
;SGlib.c:163: SG_write_to_VDPRegister(HI(feature), VDPReg[HI(feature)]);
	di 
	ld	a,c
	out	(_VDPControlPort),a
	ld	a,e
	set	7, a
	ld	h,a
	out	(_VDPControlPort),a
	ei 
	ld	sp, ix
	pop	ix
	ret
;SGlib.c:166: void SG_VDPturnOffFeature (unsigned int feature) {
;	---------------------------------
; Function SG_VDPturnOffFeature
; ---------------------------------
_SG_VDPturnOffFeature::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
;SGlib.c:168: VDPReg[HI(feature)]&=~LO(feature);
	ld	e,5 (ix)
	ld	d,#0x00
	ld	hl,#_VDPReg
	add	hl,de
	ex	(sp), hl
	pop	hl
	push	hl
	ld	b,(hl)
	ld	a, 4 (ix)
	cpl
	ld	c,a
	ld	a,b
	and	a, c
	ld	b,a
	pop	hl
	push	hl
	ld	(hl),b
;SGlib.c:169: SG_write_to_VDPRegister(HI(feature), VDPReg[HI(feature)]);
	di 
	ld	a,b
	out	(_VDPControlPort),a
	ld	a,e
	set	7, a
	ld	h,a
	out	(_VDPControlPort),a
	ei 
	ld	sp, ix
	pop	ix
	ret
;SGlib.c:172: void SG_init (void) {
;	---------------------------------
; Function SG_init
; ---------------------------------
_SG_init::
;SGlib.c:174: for (i=0;i<8;i++)
	ld	e,#0x00
00102$:
;SGlib.c:175: SG_write_to_VDPRegister (i, VDPReg_init[i]);
	di 
	ld	hl,#_VDPReg_init
	ld	d,#0x00
	add	hl, de
	ld	a,(hl)
	out	(_VDPControlPort),a
	ld	a,e
	set	7, a
	out	(_VDPControlPort),a
	ei 
;SGlib.c:174: for (i=0;i<8;i++)
	inc	e
	ld	a,e
	sub	a, #0x08
	jr	C,00102$
;SGlib.c:176: SG_initSprites ();
	call	_SG_initSprites
;SGlib.c:177: SG_finalizeSprites ();
	call	_SG_finalizeSprites
;SGlib.c:178: UNSAFE_SG_copySpritestoSAT ();
	jp  _UNSAFE_SG_copySpritestoSAT
;SGlib.c:181: void SG_setBackdropColor (unsigned char entry) {
;	---------------------------------
; Function SG_setBackdropColor
; ---------------------------------
_SG_setBackdropColor::
;SGlib.c:182: SG_write_to_VDPRegister (0x07, entry & 0x0f);
	di 
	ld	iy,#2
	add	iy,sp
	ld	a,0 (iy)
	and	a, #0x0F
	out	(_VDPControlPort),a
	ld	a,#0x87
	out	(_VDPControlPort),a
	ei 
	ret
;SGlib.c:185: void SG_setSpriteMode (unsigned char mode) {
;	---------------------------------
; Function SG_setSpriteMode
; ---------------------------------
_SG_setSpriteMode::
;SGlib.c:186: if (mode & SG_SPRITEMODE_LARGE) {
	ld	hl, #2+0
	add	hl, sp
	ld	a, (hl)
	rrca
	jr	NC,00102$
;SGlib.c:187: SG_VDPturnOnFeature(SG_VDPFEATURE_USELARGESPRITES);
	ld	hl,#0x0102
	push	hl
	call	_SG_VDPturnOnFeature
	pop	af
	jr	00103$
00102$:
;SGlib.c:189: SG_VDPturnOffFeature(SG_VDPFEATURE_USELARGESPRITES);
	ld	hl,#0x0102
	push	hl
	call	_SG_VDPturnOffFeature
	pop	af
00103$:
;SGlib.c:191: if (mode & SG_SPRITEMODE_ZOOMED) {
	ld	hl, #2+0
	add	hl, sp
	ld	a, (hl)
	and	a, #0x02
	jr	Z,00105$
;SGlib.c:192: SG_VDPturnOnFeature(SG_VDPFEATURE_ZOOMSPRITES);
	ld	hl,#0x0101
	push	hl
	call	_SG_VDPturnOnFeature
	pop	af
	ret
00105$:
;SGlib.c:194: SG_VDPturnOffFeature(SG_VDPFEATURE_ZOOMSPRITES);
	ld	hl,#0x0101
	push	hl
	call	_SG_VDPturnOffFeature
	pop	af
	ret
;SGlib.c:199: void SG_loadTilePatterns (void *src, unsigned int tilefrom, unsigned int size) {
;	---------------------------------
; Function SG_loadTilePatterns
; ---------------------------------
_SG_loadTilePatterns::
	push	ix
	ld	ix,#0
	add	ix,sp
;SGlib.c:200: SG_set_address_VRAM (PGTADDRESS + (tilefrom << 3));
	di 
	ld	a,6 (ix)
	rlca
	rlca
	rlca
	and	a,#0xF8
	out	(_VDPControlPort),a
	ld	l,6 (ix)
	ld	h,7 (ix)
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	d,#0x00
	ld	a,h
	set	6, a
	ld	l,a
	out	(_VDPControlPort),a
	ei 
;SGlib.c:201: SG_byte_array_to_VDP_data (src, size);
	ld	c,8 (ix)
	ld	b,9 (ix)
	ld	e,4 (ix)
	ld	d,5 (ix)
;SGlib.c:136: do {
00101$:
;SGlib.c:137: VDPDataPort = *(data ++);
	ld	a,(de)
	out	(_VDPDataPort),a
	inc	de
;SGlib.c:138: } while (-- size);
	ld	l,c
	ld	h,b
	dec	hl
	ld	c, l
	ld	a,h
	ld	b,a
	or	a,l
	jr	NZ,00101$
;SGlib.c:201: SG_byte_array_to_VDP_data (src, size);
	pop	ix
	ret
;SGlib.c:204: void SG_loadTileColours (void *src, unsigned int tilefrom, unsigned int size) {
;	---------------------------------
; Function SG_loadTileColours
; ---------------------------------
_SG_loadTileColours::
	push	ix
	ld	ix,#0
	add	ix,sp
;SGlib.c:205: SG_set_address_VRAM (CGTADDRESS + (tilefrom << 3));
	di 
	ld	a,6 (ix)
	rlca
	rlca
	rlca
	and	a,#0xF8
	out	(_VDPControlPort),a
	ld	l,6 (ix)
	ld	h,7 (ix)
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	bc,#0x2000
	add	hl,bc
	ld	d,#0x00
	ld	a,h
	set	6, a
	ld	l,a
	out	(_VDPControlPort),a
	ei 
;SGlib.c:206: SG_byte_array_to_VDP_data (src, size);
	ld	c,8 (ix)
	ld	b,9 (ix)
	ld	e,4 (ix)
	ld	d,5 (ix)
;SGlib.c:136: do {
00101$:
;SGlib.c:137: VDPDataPort = *(data ++);
	ld	a,(de)
	out	(_VDPDataPort),a
	inc	de
;SGlib.c:138: } while (-- size);
	ld	l,c
	ld	h,b
	dec	hl
	ld	c, l
	ld	a,h
	ld	b,a
	or	a,l
	jr	NZ,00101$
;SGlib.c:206: SG_byte_array_to_VDP_data (src, size);
	pop	ix
	ret
;SGlib.c:209: void SG_loadSpritePatterns (void *src, unsigned int tilefrom, unsigned int size) {
;	---------------------------------
; Function SG_loadSpritePatterns
; ---------------------------------
_SG_loadSpritePatterns::
	push	ix
	ld	ix,#0
	add	ix,sp
;SGlib.c:210: SG_set_address_VRAM (SGTADDRESS + (tilefrom << 3));
	di 
	ld	a,6 (ix)
	rlca
	rlca
	rlca
	and	a,#0xF8
	out	(_VDPControlPort),a
	ld	l,6 (ix)
	ld	h,7 (ix)
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	bc,#0x3800
	add	hl,bc
	ld	d,#0x00
	ld	a,h
	set	6, a
	ld	l,a
	out	(_VDPControlPort),a
	ei 
;SGlib.c:211: SG_byte_array_to_VDP_data (src, size);
	ld	c,8 (ix)
	ld	b,9 (ix)
	ld	e,4 (ix)
	ld	d,5 (ix)
;SGlib.c:136: do {
00101$:
;SGlib.c:137: VDPDataPort = *(data ++);
	ld	a,(de)
	out	(_VDPDataPort),a
	inc	de
;SGlib.c:138: } while (-- size);
	ld	l,c
	ld	h,b
	dec	hl
	ld	c, l
	ld	a,h
	ld	b,a
	or	a,l
	jr	NZ,00101$
;SGlib.c:211: SG_byte_array_to_VDP_data (src, size);
	pop	ix
	ret
;SGlib.c:214: void SG_setTileatXY (unsigned char x, unsigned char y, unsigned char tile) {
;	---------------------------------
; Function SG_setTileatXY
; ---------------------------------
_SG_setTileatXY::
	push	ix
	ld	ix,#0
	add	ix,sp
;SGlib.c:215: SG_set_address_VRAM (PNTADDRESS + (y << 5) + x);
	di 
	ld	a,5 (ix)
	rrca
	rrca
	rrca
	and	a,#0xE0
	add	a, 4 (ix)
	out	(_VDPControlPort),a
	ld	l,5 (ix)
	ld	h,#0x00
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	bc,#0x1800
	add	hl,bc
	ld	e,4 (ix)
	ld	d,#0x00
	add	hl,de
	ld	e, h
	ld	a,e
	rlc	a
	sbc	a, a
	ld	d,a
	ld	a,e
	set	6, a
	ld	h,a
	out	(_VDPControlPort),a
	ei 
;SGlib.c:216: SG_byte_to_VDP_data (tile);
	ld	a,6 (ix)
	out	(_VDPDataPort),a
	pop	ix
	ret
;SGlib.c:219: void SG_setNextTileatXY (unsigned char x, unsigned char y) {
;	---------------------------------
; Function SG_setNextTileatXY
; ---------------------------------
_SG_setNextTileatXY::
	push	ix
	ld	ix,#0
	add	ix,sp
;SGlib.c:220: SG_set_address_VRAM (PNTADDRESS + (y << 5) + x);
	di 
	ld	a,5 (ix)
	rrca
	rrca
	rrca
	and	a,#0xE0
	add	a, 4 (ix)
	out	(_VDPControlPort),a
	ld	l,5 (ix)
	ld	h,#0x00
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	bc,#0x1800
	add	hl,bc
	ld	e,4 (ix)
	ld	d,#0x00
	add	hl,de
	ld	e, h
	ld	a,e
	rlc	a
	sbc	a, a
	ld	d,a
	ld	a,e
	set	6, a
	ld	h,a
	out	(_VDPControlPort),a
	ei 
	pop	ix
	ret
;SGlib.c:223: void SG_setTile (unsigned char tile) {
;	---------------------------------
; Function SG_setTile
; ---------------------------------
_SG_setTile::
;SGlib.c:224: SG_byte_to_VDP_data (tile);
	ld	hl, #2+0
	add	hl, sp
	ld	a, (hl)
	out	(_VDPDataPort),a
	ret
;SGlib.c:227: void SG_fillTile (unsigned char tile, unsigned char count) {
;	---------------------------------
; Function SG_fillTile
; ---------------------------------
_SG_fillTile::
;SGlib.c:228: while (count --) SG_byte_to_VDP_data (tile);
	ld	hl, #2+0
	add	hl, sp
	ld	d, (hl)
	ld	hl, #3+0
	add	hl, sp
	ld	e, (hl)
00101$:
	ld	b,e
	dec	e
	ld	a,b
	or	a, a
	ret	Z
;SGlib.c:131: VDPDataPort = data;
	ld	a,d
	out	(_VDPDataPort),a
;SGlib.c:228: while (count --) SG_byte_to_VDP_data (tile);
	jr	00101$
;SGlib.c:231: void SG_loadTileMapArea (unsigned char x, unsigned char y,	void *src, unsigned char width, unsigned char height) {
;	---------------------------------
; Function SG_loadTileMapArea
; ---------------------------------
_SG_loadTileMapArea::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	dec	sp
;SGlib.c:233: for (cur_y=y; cur_y<(y+height); cur_y++) {
	ld	c,5 (ix)
	ld	b,8 (ix)
00107$:
	ld	l,5 (ix)
	ld	h,#0x00
	ld	e,9 (ix)
	ld	d,#0x00
	add	hl,de
	ld	e,c
	ld	d,#0x00
	ld	a,e
	sub	a, l
	ld	a,d
	sbc	a, h
	jp	PO, 00129$
	xor	a, #0x80
00129$:
	jp	P,00109$
;SGlib.c:234: SG_set_address_VRAM (PNTADDRESS+(cur_y<<5)+x);
	di 
	ld	a,c
	rrca
	rrca
	rrca
	and	a,#0xE0
	add	a, 4 (ix)
	out	(_VDPControlPort),a
	ex	de,hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ld	de,#0x1800
	add	hl,de
	ld	e,4 (ix)
	ld	d,#0x00
	add	hl,de
	ld	a,h
	rlc	a
	sbc	a, a
	ld	l,a
	set	6, h
	ld	a,h
	out	(_VDPControlPort),a
	ei 
;SGlib.c:235: SG_byte_brief_array_to_VDP_data (src, width);
	ld	e,6 (ix)
	ld	d,7 (ix)
	inc	sp
	inc	sp
	push	de
	ld	-1 (ix),b
;SGlib.c:143: do {
00102$:
;SGlib.c:144: VDPDataPort = *(data ++);
	pop	hl
	push	hl
	ld	a,(hl)
	out	(_VDPDataPort),a
	inc	-3 (ix)
	jr	NZ,00130$
	inc	-2 (ix)
00130$:
;SGlib.c:145: } while (-- size);
	ld	a,-1 (ix)
	add	a,#0xFF
	ld	-1 (ix),a
	or	a, a
	jr	NZ,00102$
;SGlib.c:236: src=(unsigned char *)src + width;
	ld	l,b
	ld	h,#0x00
	add	hl,de
	ld	6 (ix),l
	ld	7 (ix),h
;SGlib.c:233: for (cur_y=y; cur_y<(y+height); cur_y++) {
	inc	c
	jr	00107$
00109$:
	ld	sp, ix
	pop	ix
	ret
;SGlib.c:240: void SG_initSprites (void) {
;	---------------------------------
; Function SG_initSprites
; ---------------------------------
_SG_initSprites::
;SGlib.c:248: stp = SpriteTable;
	ld	hl,#_SpriteTable+0
	ld	(_stp),hl
	ret
;SGlib.c:275: void SG_addSprite (unsigned char x, unsigned char y, unsigned char tile, unsigned char attr) {
;	---------------------------------
; Function SG_addSprite
; ---------------------------------
_SG_addSprite::
;SGlib.c:276: *stp ++ = y;
	ld	hl,(_stp)
	ld	iy,#3
	add	iy,sp
	ld	a,0 (iy)
	ld	(hl),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00103$
	ld	hl, #_stp+1
	inc	(hl)
00103$:
;SGlib.c:277: *stp ++ = x;
	ld	hl,(_stp)
	ld	iy,#2
	add	iy,sp
	ld	a,0 (iy)
	ld	(hl),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00104$
	ld	hl, #_stp+1
	inc	(hl)
00104$:
;SGlib.c:278: *stp ++ = tile;
	ld	hl,(_stp)
	ld	iy,#4
	add	iy,sp
	ld	a,0 (iy)
	ld	(hl),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00105$
	ld	hl, #_stp+1
	inc	(hl)
00105$:
;SGlib.c:279: *stp ++ = attr;
	ld	hl,(_stp)
	ld	iy,#5
	add	iy,sp
	ld	a,0 (iy)
	ld	(hl),a
	ld	hl, #_stp+0
	inc	(hl)
	ret	NZ
	ld	hl, #_stp+1
	inc	(hl)
	ret
;SGlib.c:282: void SG_addMetaSprite1x1 (unsigned char x, unsigned char y, const unsigned char *mt) {
;	---------------------------------
; Function SG_addMetaSprite1x1
; ---------------------------------
_SG_addMetaSprite1x1::
	push	ix
	ld	ix,#0
	add	ix,sp
;SGlib.c:283: mt += 2; 
	ld	a,6 (ix)
	add	a, #0x02
	ld	6 (ix),a
	ld	a,7 (ix)
	adc	a, #0x00
	ld	7 (ix),a
;SGlib.c:284: *stp ++ = y;
	ld	hl,(_stp)
	ld	a,5 (ix)
	ld	(hl),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00103$
	ld	hl, #_stp+1
	inc	(hl)
00103$:
;SGlib.c:285: *stp ++ = x;
	ld	hl,(_stp)
	ld	a,4 (ix)
	ld	(hl),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00104$
	ld	hl, #_stp+1
	inc	(hl)
00104$:
;SGlib.c:286: *stp ++ = *mt ++;
	ld	de,(_stp)
	ld	l,6 (ix)
	ld	h,7 (ix)
	ld	b,(hl)
	inc	hl
	ld	6 (ix),l
	ld	7 (ix),h
	ld	a,b
	ld	(de),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00105$
	ld	hl, #_stp+1
	inc	(hl)
00105$:
;SGlib.c:287: *stp ++ = *mt ++;
	ld	de,(_stp)
	ld	l,6 (ix)
	ld	h,7 (ix)
	ld	b,(hl)
	inc	hl
	ld	6 (ix),l
	ld	7 (ix),h
	ld	a,b
	ld	(de),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00106$
	ld	hl, #_stp+1
	inc	(hl)
00106$:
;SGlib.c:288: mt += 2; 
	ld	a,6 (ix)
	add	a, #0x02
	ld	6 (ix),a
	ld	a,7 (ix)
	adc	a, #0x00
	ld	7 (ix),a
;SGlib.c:289: *stp ++ = y;
	ld	hl,(_stp)
	ld	a,5 (ix)
	ld	(hl),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00107$
	ld	hl, #_stp+1
	inc	(hl)
00107$:
;SGlib.c:290: *stp ++ = x;
	ld	hl,(_stp)
	ld	a,4 (ix)
	ld	(hl),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00108$
	ld	hl, #_stp+1
	inc	(hl)
00108$:
;SGlib.c:291: *stp ++ = *mt ++;
	ld	de,(_stp)
	ld	l,6 (ix)
	ld	h,7 (ix)
	ld	b,(hl)
	inc	hl
	ld	6 (ix),l
	ld	7 (ix),h
	ld	a,b
	ld	(de),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00109$
	ld	hl, #_stp+1
	inc	(hl)
00109$:
;SGlib.c:292: *stp ++ = *mt ++;
	ld	de,(_stp)
	ld	l,6 (ix)
	ld	h,7 (ix)
	ld	a,(hl)
	ld	(de),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00110$
	ld	hl, #_stp+1
	inc	(hl)
00110$:
	pop	ix
	ret
;SGlib.c:295: void SG_addMetaSprite (unsigned char x, unsigned char y, const unsigned char *mt) {
;	---------------------------------
; Function SG_addMetaSprite
; ---------------------------------
_SG_addMetaSprite::
	push	ix
	ld	ix,#0
	add	ix,sp
;SGlib.c:296: while (0x80 != (*stp = *mt ++)) {
00101$:
	ld	de,(_stp)
	ld	l,6 (ix)
	ld	h,7 (ix)
	ld	b,(hl)
	inc	hl
	ld	6 (ix),l
	ld	7 (ix),h
	ld	a,b
	ld	(de),a
	ld	a,b
	sub	a, #0x80
	jr	Z,00104$
	ld	hl,(_stp)
;SGlib.c:297: *stp += y; stp ++;
	ld	a, (hl)
	add	a, 5 (ix)
	ld	(hl),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00115$
	ld	hl, #_stp+1
	inc	(hl)
00115$:
;SGlib.c:298: *stp ++ = x + *mt++;
	ld	de,(_stp)
	ld	l,6 (ix)
	ld	h,7 (ix)
	ld	b,(hl)
	inc	hl
	ld	6 (ix),l
	ld	7 (ix),h
	ld	a,4 (ix)
	add	a, b
	ld	(de),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00116$
	ld	hl, #_stp+1
	inc	(hl)
00116$:
;SGlib.c:299: *stp ++ = *mt ++;
	ld	de,(_stp)
	ld	l,6 (ix)
	ld	h,7 (ix)
	ld	b,(hl)
	inc	hl
	ld	6 (ix),l
	ld	7 (ix),h
	ld	a,b
	ld	(de),a
	ld	hl, #_stp+0
	inc	(hl)
	jr	NZ,00117$
	ld	hl, #_stp+1
	inc	(hl)
00117$:
;SGlib.c:300: *stp ++ = *mt ++;
	ld	de,(_stp)
	ld	l,6 (ix)
	ld	h,7 (ix)
	ld	b,(hl)
	inc	hl
	ld	6 (ix),l
	ld	7 (ix),h
	ld	a,b
	ld	(de),a
	ld	hl, #_stp+0
	inc	(hl)
	jp	NZ,00101$
	ld	hl, #_stp+1
	inc	(hl)
	jp	00101$
00104$:
	pop	ix
	ret
;SGlib.c:304: void SG_finalizeSprites (void) {
;	---------------------------------
; Function SG_finalizeSprites
; ---------------------------------
_SG_finalizeSprites::
;SGlib.c:305: *stp = 0xd0;
	ld	hl,(_stp)
	ld	(hl),#0xD0
	ret
;SGlib.c:308: void SG_copySpritestoSAT (void) {
;	---------------------------------
; Function SG_copySpritestoSAT
; ---------------------------------
_SG_copySpritestoSAT::
;SGlib.c:309: SG_set_address_VRAM (SATADDRESS);
	di 
	ld	a,#0x00
	out	(_VDPControlPort),a
	ld	a,#0x5B
	out	(_VDPControlPort),a
	ei 
;SGlib.c:310: SG_byte_brief_array_to_VDP_data (SpriteTable, MAXSPRITES*4);
	ld	de,#_SpriteTable
	ld	b,#0x80
;SGlib.c:143: do {
00101$:
;SGlib.c:144: VDPDataPort = *(data ++);
	ld	a,(de)
	out	(_VDPDataPort),a
	inc	de
;SGlib.c:145: } while (-- size);
	djnz	00101$
;SGlib.c:310: SG_byte_brief_array_to_VDP_data (SpriteTable, MAXSPRITES*4);
	ret
;SGlib.c:313: void SG_waitForVBlank (void) {
;	---------------------------------
; Function SG_waitForVBlank
; ---------------------------------
_SG_waitForVBlank::
;SGlib.c:314: VDPBlank=false;
	ld	hl,#_VDPBlank + 0
	ld	(hl), #0x00
;SGlib.c:315: while (!VDPBlank);
00101$:
	ld	hl,#_VDPBlank+0
	bit	0, (hl)
	jr	Z,00101$
	ret
;SGlib.c:318: unsigned int SG_getKeysStatus (void) {
;	---------------------------------
; Function SG_getKeysStatus
; ---------------------------------
_SG_getKeysStatus::
;SGlib.c:319: return (KeysStatus);
	ld	hl,(_KeysStatus)
	ret
;SGlib.c:322: _Bool SG_queryPauseRequested (void) {
;	---------------------------------
; Function SG_queryPauseRequested
; ---------------------------------
_SG_queryPauseRequested::
;SGlib.c:323: return(PauseRequested);
	ld	iy,#_PauseRequested
	ld	l,0 (iy)
	ret
;SGlib.c:326: void SG_resetPauseRequest (void) {
;	---------------------------------
; Function SG_resetPauseRequest
; ---------------------------------
_SG_resetPauseRequest::
;SGlib.c:327: PauseRequested=false;
	ld	hl,#_PauseRequested + 0
	ld	(hl), #0x00
	ret
;SGlib.c:331: void SG_VRAMmemset (unsigned int dst, unsigned char value, unsigned int size) {
;	---------------------------------
; Function SG_VRAMmemset
; ---------------------------------
_SG_VRAMmemset::
;SGlib.c:332: SG_set_address_VRAM(dst);
	di 
	ld	iy,#2
	add	iy,sp
	ld	a, 0 (iy)
	out	(_VDPControlPort),a
	ld	a, 1 (iy)
	ld	l, #0x00
	set	6, a
	ld	h,a
	out	(_VDPControlPort),a
	ei 
;SGlib.c:333: while (size>0) {
	ld	hl, #4+0
	add	hl, sp
	ld	d, (hl)
	ld	hl, #5
	add	hl, sp
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
00101$:
	ld	a,b
	or	a,c
	ret	Z
;SGlib.c:131: VDPDataPort = data;
	ld	a,d
	out	(_VDPDataPort),a
;SGlib.c:335: size--;
	dec	bc
	jr	00101$
;SGlib.c:342: void UNSAFE_SG_copySpritestoSAT (void) {
;	---------------------------------
; Function UNSAFE_SG_copySpritestoSAT
; ---------------------------------
_UNSAFE_SG_copySpritestoSAT::
;SGlib.c:343: SG_set_address_VRAM(SATADDRESS);
	di 
	ld	a,#0x00
	out	(_VDPControlPort),a
	ld	a,#0x5B
	out	(_VDPControlPort),a
	ei 
;SGlib.c:352: __endasm;
	ld c,#_VDPDataPort
	ld hl,#_SpriteTable
	call _outi_block-32*4*2
	ret
;SGlib.c:355: void UNSAFE_SG_VRAMmemcpy128 (unsigned int dst, void *src) {
;	---------------------------------
; Function UNSAFE_SG_VRAMmemcpy128
; ---------------------------------
_UNSAFE_SG_VRAMmemcpy128::
;SGlib.c:356: SG_set_address_VRAM(dst);
	di 
	ld	iy,#2
	add	iy,sp
	ld	a, 0 (iy)
	out	(_VDPControlPort),a
	ld	a, 1 (iy)
	ld	l, #0x00
	set	6, a
	ld	h,a
	out	(_VDPControlPort),a
	ei 
;SGlib.c:362: __endasm;
	ld c,#_VDPDataPort
	ld l, 2 (iy)
	ld h, 3 (iy)
	call _outi_block-128*2
	ret
;SGlib.c:367: void SG_isr (void) __interrupt {
;	---------------------------------
; Function SG_isr
; ---------------------------------
_SG_isr::
	push	af
	push	bc
	push	de
	push	hl
	push	iy
	push	ix
	ld	ix,#0
	add	ix,sp
	dec	sp
;SGlib.c:368: volatile unsigned char VDPStatus=VDPStatusPort;	/* this also aknowledge interrupt at VDP */
	in	a,(_VDPStatusPort)
	ld	-1 (ix),a
;SGlib.c:373: if (VDPStatus & 0x80) {
	bit	7, -1 (ix)
	jr	Z,00102$
;SGlib.c:374: VDPBlank=true;				 /* frame interrupt */
	ld	hl,#_VDPBlank + 0
	ld	(hl), #0x01
;SGlib.c:376: PreviousKeysStatus=KeysStatus;
	ld	hl,(_KeysStatus)
	ld	(_PreviousKeysStatus),hl
;SGlib.c:377: KeysStatus=~(((IOPortH)<<8)|IOPortL);
	in	a,(_IOPortH)
	ld	b,a
	ld	c,#0x00
	in	a,(_IOPortL)
	ld	l,a
	ld	h,#0x00
	ld	a,c
	or	a, l
	ld	d,a
	ld	a,b
	or	a, h
	ld	e,a
	ld	a,d
	cpl
	ld	iy,#_KeysStatus
	ld	0 (iy),a
	ld	a,e
	cpl
	ld	iy,#_KeysStatus
	ld	1 (iy),a
00102$:
;SGlib.c:380: ENABLE_INTERRUPTS;
	ei 
	inc	sp
	pop	ix
	pop	iy
	pop	hl
	pop	de
	pop	bc
	pop	af
	reti
;SGlib.c:383: void SG_nmi_isr (void) __critical __interrupt {		/* this is for NMI */
;	---------------------------------
; Function SG_nmi_isr
; ---------------------------------
_SG_nmi_isr::
	push	af
	push	bc
	push	de
	push	hl
	push	iy
;SGlib.c:384: PauseRequested = true;
	ld	hl,#_PauseRequested + 0
	ld	(hl), #0x01
	pop	iy
	pop	hl
	pop	de
	pop	bc
	pop	af
	retn
	.area _CODE
	.area _INITIALIZER
__xinit__VDPReg:
	.db #0x02	; 2
	.db #0xA0	; 160
	.area _CABS (ABS)
