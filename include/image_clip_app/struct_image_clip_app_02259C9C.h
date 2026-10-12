#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259C9C_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259C9C_H

#include <nnsys.h>

#include "struct_decls/struct_02012744_decl.h"

#include "image_clip_app/struct_image_clip_app_02259C58_1.h"

#include "bg_window.h"

typedef struct {
    ImageClipUiTemplate uiTemplate;
    const Window *window;
    const FontOAMManager *fontManager;
    const NNSG2dImagePaletteProxy *paletteProxy;
    int x;
    int y;
    int charOffset;
} ImageClipUiTextButtonTemplate;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259C9C_H
