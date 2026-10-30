@echo off
if [%1]==[justcompile] goto :compile
if [%1]==[mapenems] goto :mapenems

rem convert stuff

..\utils\folder2c psg murcia

cd ..\gfx

rem tiles
..\utils\mkts.exe platform=sg1000 in=font.png out=bin mode=chars label=pd_font size=32,3 max=88 silent
..\utils\mkts.exe platform=sg1000 mode=mapped in=title.png out=bin tsmap=..\dev\assets\tm_title.h size=6,7 metasize=2,2 label=pd_title tmapoffset=88 max=39 silent
..\utils\mkts.exe platform=sg1000 in=ts.png out=bin mode=mapped tsmap=..\dev\assets\tm_ts.h size=8,4 metasize=2,2 label=pd_ts tmapoffset=131 max=29 silent

..\utils\mkts.exe platform=sg1000 mode=tilemap in=win.png out=bin tsmap=..\dev\assets\tm_win.h label=pd_ts_win tmapoffset=190 silent
..\utils\mkts.exe platform=sg1000 mode=tilemap in=endingko.png out=bin tsmap=..\dev\assets\tm_endingko.h label=pd_ts_endingko tmapoffset=131 silent
..\utils\mkts.exe platform=sg1000 mode=tilemap in=endingok.png out=bin tsmap=..\dev\assets\tm_endingok.h label=pd_ts_endingok tmapoffset=131 silent

rem sprites
..\utils\mkts.exe platform=sg1000 mode=sprites in=sspl.png out=..\dev\assets\pd_ss_pl.h tsmap=..\dev\work\tm_ss_dummy.h size=16,2 metasize=1,2 sprorg=-4,-16 label=pd_ss_pl silent
..\utils\mkts.exe platform=sg1000 mode=sprites in=sspldead.png out=bin tsmap=..\dev\assets\tm_ss_pl_dead.h size=2,1 metasize=2,1 sprorg=-8,0 label=pd_ss_pl_dead tmapoffset=32 silent
..\utils\mkts.exe platform=sg1000 mode=sprites in=ssen.png out=bin tsmap=..\dev\assets\tm_ss_en.h size=8,2 metasize=1,1 sprorg=0,0 max=13 label=pd_ss_en tmapoffset=128 silent
..\utils\mkts.exe platform=sg1000 mode=sprites in=ssitems.png out=bin tsmap=..\dev\work\tm_ss_items_dummy.h size=2,1 metasize=1,1 sprorg=0,0 label=pd_ss_items tmapoffset=240 silent
..\utils\mkts.exe platform=sg1000 mode=sprites in=sscoin.png out=bin tsmap=..\dev\work\tm_ss_coins_dummy.h size=4,1 metasize=1,1 sprorg=0,0 label=pd_ss_coin tmapoffset=32 silent

rem compression
..\utils\apack.exe pd_font_cgt.bin ..\dev\cbins\c_pd_font_cgt.bin
..\utils\apack.exe pd_font_pgt.bin ..\dev\cbins\c_pd_font_pgt.bin
..\utils\apack.exe pd_title_cgt.bin ..\dev\cbins\c_pd_title_cgt.bin
..\utils\apack.exe pd_title_pgt.bin ..\dev\cbins\c_pd_title_pgt.bin
..\utils\apack.exe pd_ts_cgt.bin ..\dev\cbins\c_pd_ts_cgt.bin
..\utils\apack.exe pd_ts_pgt.bin ..\dev\cbins\c_pd_ts_pgt.bin
..\utils\apack.exe pd_ts_win_cgt.bin ..\dev\cbins\c_pd_ts_win_cgt.bin
..\utils\apack.exe pd_ts_win_pgt.bin ..\dev\cbins\c_pd_ts_win_pgt.bin
..\utils\apack.exe pd_ts_endingko_cgt.bin ..\dev\cbins\c_pd_ts_endingko_cgt.bin
..\utils\apack.exe pd_ts_endingko_pgt.bin ..\dev\cbins\c_pd_ts_endingko_pgt.bin
..\utils\apack.exe pd_ts_endingok_cgt.bin ..\dev\cbins\c_pd_ts_endingok_cgt.bin
..\utils\apack.exe pd_ts_endingok_pgt.bin ..\dev\cbins\c_pd_ts_endingok_pgt.bin

..\utils\apack.exe pd_ss_coin_sgt.bin ..\dev\cbins\c_pd_ss_coin_sgt.bin
..\utils\apack.exe pd_ss_en_sgt.bin ..\dev\cbins\c_pd_ss_en_sgt.bin
..\utils\apack.exe pd_ss_items_sgt.bin ..\dev\cbins\c_pd_ss_items_sgt.bin
..\utils\apack.exe pd_ss_pl_dead_sgt.bin ..\dev\cbins\c_pd_ss_pl_dead_sgt.bin

cd ..\dev

..\utils\folder2c cbins cbins

rem make lib

cd lib
sdcc -c -mz80 --peep-file peep-rules.txt SGlib.c
sdcc -c -mz80 --peep-file peep-rules.txt PSGlib.c
sdcc -c -mz80 --peep-file peep-rules.txt aPLib.c
rem del *.asm > nul
del *.lst > nul
del *.sym > nul
cd ..

:mapenems

rem convert map

cd ..\map
suwolmapcnv.exe do
copy uwolmap.h ..\dev\assets\ > nul
cd ..\dev

rem convert enems

..\utils\eneexpuwol.exe ..\enems\uwol.ene assets\uwolenems.h _ nohotspots

rem compile

:compile
sdcc -c -mz80 --peep-file lib\peep-rules.txt uwol.c
sdcc -c -mz80 --no-peep murcia.c
sdcc -c -mz80 --no-peep cbins.c
sdcc -mz80 --data-loc 0xC000 uwol.rel murcia.rel cbins.rel lib\PSGlib.rel lib\SGlib.rel lib\aPLib.rel
ihx2sms uwol.ihx suwol.sg
del *.asm > nul
del *.ihx > nul
del *.lk > nul
del *.lst > nul
del *.map > nul
del *.noi > nul
del *.rel > nul
del *.sym > nul
