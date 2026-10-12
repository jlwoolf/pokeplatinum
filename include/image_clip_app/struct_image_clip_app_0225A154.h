#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A154_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A154_H

#include "struct_decls/font_oam.h"

#include "image_clip_app/struct_image_clip_app_02259C58.h"

#include "char_transfer.h"

typedef struct {
    ImageClipUi ui;
    FontOAM *fontOAM;
    CharTransferAllocation charAllocation;
} ImageClipUiTextButton;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A154_H
