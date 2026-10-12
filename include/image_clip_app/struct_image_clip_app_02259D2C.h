#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259D2C_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259D2C_H

#include "struct_decls/struct_02012744_decl.h"

#include "image_clip_app/struct_image_clip_app_02259C58.h"
#include "image_clip_app/struct_image_clip_app_0225A154.h"

#include "touch_screen.h"
#include "touch_screen_actions.h"

typedef struct {
    ImageClipUi buttons[4];
    ImageClipUiTextButton textButton;
    BOOL textEnabled;
    FontOAMManager *fontManager;
    TouchScreenActions *touchActions;
    TouchScreenHitTable hitTables[5];
} ImageClipUiMenu;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259D2C_H
