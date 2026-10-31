Since the original 48 KiB SG-1000 ROM had no mapper, I had to be a bit creative to make it work on a system that doesn't allow for a 48 KiB mapperless ROM. Basically I had to break the code and data in 3 separate parts in a way that each part would fit into a 16 KiB block, and make sure that the music & SFX data was in the last bank only (which isn't mapped unless it's needed) and that the audio library functions sit into the first bank, that is the one that never gets paged out. Thus code and data needed a bit of rearrangement... but it wasn't a very long work.

Now, of course building this isn't perfectly straightforward, but it isn't too difficult either.

First we compile the game modules for the code that will go into bank 0 (and will never be paged out):

```
# set the SDCC variable to the location of your compiler bin folder:
SDCC=~/SMS/sdcc4.2/bin

${SDCC}/sdcc -c -mz80 --peep-file peep-rules.txt -D TARGET_CV uwol.c
${SDCC}/sdcc -c -mz80 -D TARGET_CV aPLib.c
```

Then compile the modules for the code and data that will go into bank 1 (this bank will be paged out when we need to access the music data, and paged in again immediately after):

```
${SDCC}/sdcc -c -mz80 --codeseg BANK1 -D TARGET_CV engine/printer.c
${SDCC}/sdcc -c -mz80 --constseg BANK1 assets/pd_ss_pl.c
${SDCC}/sdcc -c -mz80 --constseg BANK1 assets/uwolmap.c
${SDCC}/sdcc -c -mz80 --constseg BANK1 assets/uwolenems.c
${SDCC}/sdcc -c -mz80 --constseg BANK1 cbins.c
```

Then compile the module with the music & SFX data that will go into bank 2 (this bank will be paged in only when needed, and paged out again immediately after):

```
${SDCC}/sdcc -c -mz80 --constseg BANK2 murcia.c
```

Now we have to link all the modules we just compiled with devkitSMS' crt0_cv module and SGlib_CV library. (unfortunately with SDCC you can't easily force the order of the modules when they belong in a library so instead of linking with PSGlib.lib we directly link its modules, so we make sure they end up in bank 0, because the order of *modules* during linking is enforced):

```
${SDCC}/sdcc -o SuperUWOL.ihx -mz80 --no-std-crt0 --code-loc 0x8080 --data-loc 0x6000 -Wl-b_BANK1=0x1C000 -Wl-b_BANK2=0x2C000 ../crt0/crt0_cv.rel uwol.rel ../PSGlib/PSGlib_CV.rel ../PSGlib/PSGPlayLoops_CV.rel pd_ss_pl.rel uwolmap.rel uwolenems.rel printer.rel cbins.rel aPLib.rel ../SGlib/SGlib_CV.lib murcia.rel
```

Then we create the final ROM:
```
makecvmc SuperUWOL.ihx SuperUWOL.rom
```
