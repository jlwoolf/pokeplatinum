#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A428_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A428_H

#include "image_clip_app/struct_image_clip_app_022597BC.h"
#include "image_clip_app/struct_image_clip_app_0225A914.h"
#include "image_clip_app/struct_image_clip_app_0225AB54.h"

#include "bg_window.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "string_gf.h"

typedef struct {
    ImageClipBg unk_00;
    Window *unk_2C;
    SpriteList *unk_30;
    SpriteResourceCollection **unk_34;
    ContestScoreDisplayIconRow unk_38;
    ContestScoreDisplayScore unk_A0;
    Window *unk_134;
    int unk_138;
    int unk_13C;
    u32 unk_140;
    String *unk_144;
} ContestScoreDisplay;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A428_H
