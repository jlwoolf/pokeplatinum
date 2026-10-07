#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259D2C_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259D2C_H

#include "struct_decls/struct_02012744_decl.h"

#include "image_clip_app/struct_image_clip_app_02259C58.h"
#include "image_clip_app/struct_image_clip_app_0225A154.h"

#include "touch_screen.h"
#include "touch_screen_actions.h"

typedef struct {
    ImageClipUi unk_00[4];
    ImageClipUiTextButton unk_40;
    BOOL unk_60;
    FontOAMManager *unk_64;
    TouchScreenActions *unk_68;
    TouchScreenHitTable unk_6C[5];
} ImageClipUiMenu;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259D2C_H
