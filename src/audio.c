#include "audio.h"
#include "cbtfx.h"
#include "vars.h"
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
    if (game.playBgm)
    {
        hUGE_dosound();
        }
    CBTFX_update();
}
BANKREF(playSong)

void playSFX(uint8_t idx) BANKED
{
    // Debug play sfx
    CBTFX_init(&sfxList[idx][0]);
}
BANKREF(playSFX)

/// @brief Mute all audio channels
void muteAudio(void) BANKED
{
    // Flush current register values
    NR52_REG = 0;

    hUGE_mute_channel(HT_CH1, 1);
    hUGE_mute_channel(HT_CH2, 1);
    hUGE_mute_channel(HT_CH3, 1);
    hUGE_mute_channel(HT_CH4, 1);

    game.playBgm = false;
}
BANKREF(muteAudio)

/// @brief Unmute all audio channels
void unmuteAudio(void) BANKED
{
    // Enable audio output
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x54;

    hUGE_mute_channel(HT_CH1, 0);
    hUGE_mute_channel(HT_CH2, 0);
    hUGE_mute_channel(HT_CH3, 0);
    hUGE_mute_channel(HT_CH4, 0);

    game.playBgm = true;
}
BANKREF(unmuteAudio)