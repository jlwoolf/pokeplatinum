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
    SoftwareSpriteManager *unk_00;
    SoftwareSpriteChars **unk_04;
    int unk_08;
    int unk_0C;
    SoftwareSpritePalette **unk_10;
    int unk_14;
    int unk_18;
    BOOL unk_1C;
    PokemonSpriteManager *unk_20;
    NNSGfdTexKey unk_24;
    NNSGfdPlttKey unk_28;
    BOOL unk_2C;
    u8 *unk_30;
    ResourceCollection *unk_34;
    NNSG2dCharacterData **unk_38;
    int unk_3C;
    BgConfig *unk_40;
    SpriteList *unk_44;
    SpriteResourceCollection *unk_48[4];
    G2dRenderer unk_58;
    NARC *unk_5C;
} ImageClipGraphics;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A0E4_H
