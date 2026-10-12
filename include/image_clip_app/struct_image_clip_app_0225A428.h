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
    ImageClipBg bg;
    Window *messageWindow;
    SpriteList *spriteList;
    SpriteResourceCollection **spriteResources;
    ContestScoreDisplayIconRow iconRow;
    ContestScoreDisplayScore score;
    Window *scoreWindow;
    int activeFlags;
    int messageFrame;
    u32 textFrameDelay;
    String *messageString;
} ContestScoreDisplay;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A428_H
