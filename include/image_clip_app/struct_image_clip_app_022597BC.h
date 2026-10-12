#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_022597BC_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_022597BC_H

#include "constants/narc.h"

#include "bg_window.h"

typedef struct {
    BgConfig *bgConfig;
    enum NarcID narcID;
    int secondFrameIndex;
    int destTileX;
    int destTileY;
    int widthTiles;
    int heightTiles;
    int bgLayer;
    int paletteOffset;
    int paletteSize;
    int charOffset;
} ImageClipBg;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_022597BC_H
