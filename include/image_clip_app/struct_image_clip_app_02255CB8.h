#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02255CB8_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02255CB8_H

#include "resource_collection.h"
#include "software_sprite.h"

typedef struct {
    SoftwareSpriteCharsTemplate *chars;
    int charCount;
    SoftwareSpritePaletteTemplate *palettes;
    int paletteCount;
    ResourceCollection *charCollection;
    ResourceCollection *paletteCollection;
} ImageClipGraphicsTemplates;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02255CB8_H
