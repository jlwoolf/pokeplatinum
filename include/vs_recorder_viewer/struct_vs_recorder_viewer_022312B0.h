#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022312B0_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022312B0_H

#include "struct_decls/font_oam.h"
#include "struct_decls/struct_02012B20_decl.h"

#include "char_transfer.h"
#include "sprite_system.h"

typedef struct {
    u8 padding_00[4];
    ManagedSprite *sprite;
    FontOAM *fontOAM;
    FontOAMWindow *fontOAMWindow;
    CharTransferAllocation charTransfer;
} VsRecorderViewerTextSprite;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022312B0_H
