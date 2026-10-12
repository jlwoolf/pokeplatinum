#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022307C0_SUB1_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022307C0_SUB1_H

#include "struct_decls/font_oam.h"
#include "struct_decls/struct_02012B20_decl.h"

#include "char_transfer.h"
#include "sprite_system.h"
#include "touch_screen.h"

typedef struct {
    ManagedSprite *sprite;
    u8 padding_04[8];
    BOOL visible;
    TouchScreenRect *touchRect;
    FontOAM *fontOAM;
    FontOAMWindow *fontOAMWindow;
    CharTransferAllocation charTransfer;
} VsRecorderViewerMenuEntry;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022307C0_SUB1_H
