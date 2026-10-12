#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022323B8_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022323B8_H

#include "struct_decls/struct_02030A80_decl.h"

#include "bg_window.h"
#include "sprite_system.h"

typedef struct {
    PlayerProfile *profile;
    ManagedSprite *pokemonSprite;
    ManagedSprite *trainerSprite;
    Window windows[8];
} VsRecorderViewerProfilePanel;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022323B8_H
