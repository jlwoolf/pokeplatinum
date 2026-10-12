#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_022599A0_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_022599A0_H

#include "constants/heap.h"
#include "constants/narc.h"

#include "bg_window.h"

typedef struct {
    BgConfig *bgConfig;
    enum NarcID narcID;
    int charMember;
    int paletteMember;
    int tilemapMember;
    int destTilemapX;
    int destTilemapY;
    int bgLayer;
    int paletteSize;
    int paletteOffset;
    int charOffset;
    enum HeapID heapID;
} ImageClipBgTemplate;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_022599A0_H
