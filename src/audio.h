#ifndef __AUDIO_H__
#define __AUDIO_H__
#include <gbdk/platform.h>

extern const unsigned char *sfxList[6];

void initSong(void) BANKED;
BANKREF_EXTERN(initSong)

void playSong(void) BANKED;
BANKREF_EXTERN(playSong)

void playSFX(uint8_t idx) BANKED;
BANKREF_EXTERN(playSFX)

void initSoundEngine(void) BANKED;
BANKREF_EXTERN(initSoundEngine)

#endif