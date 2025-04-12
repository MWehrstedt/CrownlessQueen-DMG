#include "audio.h"
#include "cbtfx.h"
#include "../res/hUGEDriver.h"
#include "../res/sfx/SFX_00.h"
#include "../res/sfx/SFX_03.h"
#include "../res/sfx/SFX_0B.h"
#include "../res/sfx/SFX_10.h"
#include "../res/sfx/SFX_16.h"
#include "../res/sfx/SFX_17.h"
#include <gbdk/platform.h>

#pragma bank 3

const unsigned char *sfxList[6] = {
    SFX_00,
    sfx_menuConfirm,
    sfx_jump,
    sfx_enemyHit,
    sfx_gotHit,
    sfx_punchOne,
};


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

void playSFX(uint8_t idx) BANKED
{
    // Debug play sfx
    CBTFX_init(&sfxList[idx][0]);
}
BANKREF(playSFX)
