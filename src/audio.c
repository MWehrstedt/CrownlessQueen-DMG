#include "audio.h"
#include "cbtfx.h"
#include "../res/hUGEDriver.h"
#include "../res/sfx/SFX_00.h"
#include <gbdk/platform.h>

#pragma bank 3

extern const hUGESong_t zero;
BANKREF_EXTERN(zero)

void initSong(void) BANKED
{
    hUGE_init(&zero);
}
BANKREF(initSong)

void playSong(void) BANKED
{
    hUGE_dosound();
    CBTFX_update();
}
BANKREF(playSong)

void playSFX(void) BANKED
{
    // Debug play sfx
    CBTFX_init(&SFX_00[0]);
}
BANKREF(playSFX)
