#ifndef POKEPLATINUM_STRUCT_FONT_OAM_TEMPLATE_H
#define POKEPLATINUM_STRUCT_FONT_OAM_TEMPLATE_H

#include <nnsys.h>

#include "struct_decls/struct_02012744_decl.h"

#include "bg_window.h"
#include "sprite.h"

typedef struct {
    const FontOAMManager *fontOAMManager;
    const Window *window;
    SpriteList *spriteList;
    const NNSG2dImagePaletteProxy *paletteProxy;
    const Sprite *parentSprite;
    int charOffset;
    int x;
    int y;
    int resourcePriority;
    int spritePriority;
    int vramType;
    enum HeapID heapID;
} FontOAMTemplate;

#endif // POKEPLATINUM_STRUCT_FONT_OAM_TEMPLATE_H
