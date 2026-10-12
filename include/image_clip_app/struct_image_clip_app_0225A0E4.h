#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A0E4_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A0E4_H

#include <nnsys.h>

#include "bg_window.h"
#include "narc.h"
#include "pokemon_sprite.h"
#include "resource_collection.h"
#include "software_sprite.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_util.h"

typedef struct {
    SoftwareSpriteManager *softSpriteManager;
    SoftwareSpriteChars **chars;
    int charsCapacity;
    int charsCount;
    SoftwareSpritePalette **palettes;
    int palettesCapacity;
    int palettesCount;
    BOOL drawSoftwareSprites;
    PokemonSpriteManager *pokemonSpriteManager;
    NNSGfdTexKey texKey;
    NNSGfdPlttKey plttKey;
    BOOL drawPokemonSprites;
    u8 *extraResource;
    ResourceCollection *characterCollection;
    NNSG2dCharacterData **characterData;
    int characterCount;
    BgConfig *bgConfig;
    SpriteList *spriteList;
    SpriteResourceCollection *spriteResourceCollections[4];
    G2dRenderer renderer;
    NARC *narc;
} ImageClipGraphics;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A0E4_H
