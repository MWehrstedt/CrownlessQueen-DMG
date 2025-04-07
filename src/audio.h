#ifndef __AUDIO_H__
#define __AUDIO_H__
#include <gbdk/platform.h>

void initSong(void) BANKED;
BANKREF_EXTERN(initSong)

void playSong(void) BANKED;
BANKREF_EXTERN(playSong)

void playSFX(void) BANKED;
BANKREF_EXTERN(playSFX)

void initSoundEngine(void) BANKED;
BANKREF_EXTERN(initSoundEngine)

#endif