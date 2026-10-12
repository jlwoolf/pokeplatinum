#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_022649E4_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_022649E4_H

#include <nnsys.h>

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4_sub1.h"

#include "bg_window.h"
#include "camera.h"
#include "g3d_pipeline.h"
#include "narc.h"
#include "palette.h"
#include "sprite_system.h"

typedef struct {
    NARC *maneneNarc;
    NARC *bucketNarc;
    SpriteSystem *spriteSystem;
    SpriteManager *spriteManager;
    BgConfig *bgConfig;
    PaletteData *paletteData;
    G3DPipelineBuffers *g3dPipeline;
    Camera *camera;
    u8 padding_20[4];
    NNSFndAllocator g3dAllocator;
    WiFiLobbyMinigameManeneDisconnectState disconnectState;
} WiFiLobbyMinigameManeneResources;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_022649E4_H
