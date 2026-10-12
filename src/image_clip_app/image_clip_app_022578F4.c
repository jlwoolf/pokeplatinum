#include "image_clip_app/image_clip_app_022578F4.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_image_clip_pokemon_sprite.h"

#include "image_clip_app/image_clip_app.h"
#include "image_clip_app/image_clip_app_02255D44.h"
#include "image_clip_app/image_clip_app_02259098.h"
#include "image_clip_app/image_clip_app_02259484.h"
#include "image_clip_app/image_clip_app_02259560.h"
#include "image_clip_app/image_clip_app_022597BC.h"
#include "image_clip_app/struct_image_clip_app_0225500C.h"
#include "image_clip_app/struct_image_clip_app_02255040.h"
#include "image_clip_app/struct_image_clip_app_02257964.h"
#include "image_clip_app/struct_image_clip_app_02259560.h"
#include "image_clip_app/struct_image_clip_app_022599A0.h"
#include "image_clip_app/struct_image_clip_app_0225B388.h"

#include "pokemon.h"
#include "pokemon_sprite.h"
#include "software_sprite.h"
#include "touch_screen.h"

static void PhotoRenderer_ClassifySprite(PhotoRenderer *param0, ImageClipSpriteResource *param1, BOOL param2, NNSG2dCharacterData **param3);
static void PhotoRenderer_GetSpriteOutOfBounds(ImageClipSpriteResource *param0, int *param1, int *param2);

void PhotoRenderer_Init(PhotoRenderer *param0, PhotoRendererTemplate *param1)
{
    param0->context.softSpriteManager = param1->softSpriteManager;
    param0->context.chars = param1->chars;
    param0->context.palettes = param1->palettes;
    param0->context.extraResource = param1->extraResource;
    param0->context.pokemonSpriteManager = param1->pokemonSpriteManager;
    param0->context.bgConfig = param1->bgConfig;
    param0->context.spriteManager = param1->spriteManager;
    param0->context.backdropIndex = 0;
    param0->resources.resourceList = param1->resourceList;
    param0->resources.backSprites.next = &param0->resources.backSprites;
    param0->resources.backSprites.prev = &param0->resources.backSprites;
    param0->resources.frontSprites.next = &param0->resources.frontSprites;
    param0->resources.frontSprites.prev = &param0->resources.frontSprites;
    param0->resources.spriteCount = 0;
    param0->resources.maxSpriteCount = param1->maxSpriteCount;

    {
        ImageClipSpriteResource *v0;

        v0 = ImageClipResourceList_Alloc(param0->resources.resourceList, &param0->context.pokemonSprite, 3);
        ImageClipResourceList_InsertAfter(v0, &param0->resources.frontSprites);
    }
}

void PhotoRenderer_Free(PhotoRenderer *param0)
{
    PhotoRenderer_DeletePokemonSprite(param0);
    PhotoRenderer_ClearSprites(param0);
    memset(param0, 0, sizeof(PhotoRenderer));
}

void PhotoRenderer_SetupPokemonSprite(PhotoRenderer *param0, Pokemon *param1, PokemonSpriteTemplate *param2, int param3, int param4, int param5, int param6)
{
    ImageClipPokemonSprite_Init(&param0->context.pokemonSprite, param0->context.pokemonSpriteManager, param1, param2, param6);
    ImageClipPokemonSprite_SetZ(&param0->context.pokemonSprite, param5);
    ImageClipPokemonSprite_SetPosition(&param0->context.pokemonSprite, param3, param4);
}

void PhotoRenderer_CreatePokemonSprite(PhotoRenderer *param0, Pokemon *param1, PokemonSpriteTemplate *param2, int param3)
{
    ImageClipPokemonSprite_Init(&param0->context.pokemonSprite, param0->context.pokemonSpriteManager, param1, param2, param3);
}

void PhotoRenderer_CreatePokemonSpriteExact(PhotoRenderer *param0, Pokemon *param1, PokemonSpriteTemplate *param2, int param3)
{
    ImageClipPokemonSprite_InitEx(&param0->context.pokemonSprite, param0->context.pokemonSpriteManager, param1, param2, param3, 1);
}

void PhotoRenderer_AppendSprite(PhotoRenderer *param0, ImageClipSpriteResource *param1)
{
    ImageClipResourceList_InsertAfter(param1, param0->resources.frontSprites.prev);
}

void PhotoRenderer_RemoveSprite(ImageClipSpriteResource *param0)
{
    ImageClipResourceList_RemoveNode(param0);
}

void PhotoRenderer_DeletePokemonSprite(PhotoRenderer *param0)
{
    ImageClipPokemonSprite_Free(&param0->context.pokemonSprite);
}

BOOL PhotoRenderer_CreateAccessorySprite(PhotoRenderer *param0, int param1, int param2, int param3, int param4)
{
    ImageClipSpriteConfig v0;
    ImageClipSprite *v1;

    if (param0->resources.spriteCount < param0->resources.maxSpriteCount) {
        v0.spriteManager = param0->context.spriteManager;
        v0.softSpriteManager = param0->context.softSpriteManager;
        v0.chars = param0->context.chars[param1];
        v0.palette = param0->context.palettes[0];
        v0.xPos = param2;
        v0.yPos = param3;
        v0.resourceIndex = param1;
        v0.paletteSlot = param0->context.extraResource[param1];

        v1 = ImageClipSprite_Add(&v0);
        ImageClipSprite_SetPriority(v1, param4);

        {
            ImageClipSpriteResource *v2;

            v2 = ImageClipResourceList_Alloc(param0->resources.resourceList, v1, 0);
            ImageClipResourceList_InsertAfter(v2, &param0->resources.backSprites);
        }

        param0->resources.spriteCount++;

        return 1;
    }

    return 0;
}

BOOL PhotoRenderer_AddSprite(PhotoRenderer *param0, ImageClipSpriteResource *param1, NNSG2dCharacterData **param2)
{
    if (param0->resources.spriteCount < param0->resources.maxSpriteCount) {
        PhotoRenderer_ClassifySprite(param0, param1, 1, param2);
        param0->resources.spriteCount++;

        return 1;
    }

    return 0;
}

void PhotoRenderer_PopSprite(PhotoRenderer *param0, ImageClipSpriteResource *param1)
{
    ImageClipResourceList_RemoveNode(param1);

    param0->resources.spriteCount--;

    GF_ASSERT(param0->resources.spriteCount >= 0);
}

void PhotoRenderer_ClearSprites(PhotoRenderer *param0)
{
    ImageClipResourceList_RemoveAll(&param0->resources.backSprites);
    ImageClipResourceList_RemoveAll(&param0->resources.frontSprites);

    param0->resources.spriteCount = 0;
}

void PhotoRenderer_MoveSprites(PhotoRenderer *param0, int param1, int param2)
{
    ImageClipSpriteResource_Move(&param0->resources.backSprites, param1, param2);
    ImageClipSpriteResource_Move(&param0->resources.frontSprites, param1, param2);
}

void PhotoRenderer_MoveVisibleSprites(PhotoRenderer *param0, int param1, int param2)
{
    ImageClipSpriteResource_Move(&param0->resources.frontSprites, param1, param2);
}

void PhotoRenderer_PanSprites(PhotoRenderer *param0, int param1, int param2, int param3, int param4)
{
    ImageClipSpriteResource_Move(&param0->resources.backSprites, -param1, -param2);
    ImageClipSpriteResource_Move(&param0->resources.backSprites, param3, param4);
    ImageClipSpriteResource_Move(&param0->resources.frontSprites, -param1, -param2);
    ImageClipSpriteResource_Move(&param0->resources.frontSprites, param3, param4);
}

void PhotoRenderer_AssignZOrder(PhotoRenderer *param0)
{
    PhotoRenderer_AssignZOrderFrom(param0, -1);
}

void PhotoRenderer_AssignZOrderFrom(PhotoRenderer *param0, int param1)
{
    ImageClipSpriteResource *v0 = param0->resources.frontSprites.next;

    while (v0 != &param0->resources.frontSprites) {
        if (v0->category == 0) {
            ImageClipSprite_SetPriority(v0->data, param1);
        } else {
            ImageClipPokemonSprite_SetZ(v0->data, param1);
        }

        param1--;

        v0 = v0->next;
    }

    param1 -= 8;

    v0 = param0->resources.backSprites.next;

    while (v0 != &param0->resources.backSprites) {
        if (v0->category == 0) {
            ImageClipSprite_SetPriority(v0->data, param1);
        } else {
            ImageClipPokemonSprite_SetZ(v0->data, param1);
        }

        param1--;
        v0 = v0->next;
    }
}

void PhotoRenderer_OffsetZ(PhotoRenderer *param0, int param1)
{
    ImageClipSpriteResource *v0;
    int v1;

    v0 = param0->resources.frontSprites.next;

    while (v0 != &param0->resources.frontSprites) {
        if (v0->category == 0) {
            v1 = ImageClipSprite_GetPriority(v0->data);
            ImageClipSprite_SetPriority(v0->data, v1 + param1);
        } else {
            v1 = ImageClipPokemonSprite_GetZ(v0->data);
            ImageClipPokemonSprite_SetZ(v0->data, v1 + param1);
        }

        v0 = v0->next;
    }

    v0 = param0->resources.backSprites.next;

    while (v0 != &param0->resources.backSprites) {
        if (v0->category == 0) {
            v1 = ImageClipSprite_GetPriority(v0->data);
            ImageClipSprite_SetPriority(v0->data, v1 + param1);
        } else {
            v1 = ImageClipPokemonSprite_GetZ(v0->data);
            ImageClipPokemonSprite_SetZ(v0->data, v1 + param1);
        }

        v0 = v0->next;
    }
}

BOOL PhotoRenderer_IsScreenTouched(PhotoRenderer *param0)
{
    TouchScreenHitTable v0;

    v0.rect.top = (16 + 2);
    v0.rect.bottom = (16 + 2) + (129 - (2 * 2));
    v0.rect.left = (136 + 2);
    v0.rect.right = (136 + 2) + (112 - (2 * 2));

    return TouchScreen_LocationHeld(&v0);
}

BOOL PhotoRenderer_IsTouchInScreen(PhotoRenderer *param0, int param1, int param2)
{
    TouchScreenHitTable v0;

    v0.rect.top = (16 + 2);
    v0.rect.bottom = (16 + 2) + (129 - (2 * 2));
    v0.rect.left = (136 + 2);
    v0.rect.right = (136 + 2) + (112 - (2 * 2));

    return TouchScreen_IsTouchInHitTable(&v0, param1, param2);
}

ImageClipSpriteResource *PhotoRenderer_GetTouchedSprite(PhotoRenderer *param0, int *param1, int *param2, NNSG2dCharacterData **param3)
{
    ImageClipSpriteResource *v0;
    BOOL v1;

    v0 = param0->resources.frontSprites.next;

    while (v0 != &param0->resources.frontSprites) {
        v1 = ImageClipSpriteResource_IsPixelHit(v0, param1, param2, param3);

        if (v1 == 1) {
            return v0;
        }

        v0 = v0->next;
    }

    v0 = param0->resources.backSprites.next;

    while (v0 != &param0->resources.backSprites) {
        v1 = ImageClipSpriteResource_IsPixelHit(v0, param1, param2, param3);

        if (v1 == 1) {
            return v0;
        }

        v0 = v0->next;
    }

    return NULL;
}

void PhotoRenderer_LoadBackground(PhotoRenderer *param0, int param1, enum HeapID heapID)
{
    ImageClipBgTemplate v0;

    v0.bgConfig = param0->context.bgConfig;
    v0.narcID = NARC_INDEX_GRAPHIC__IMAGECLIP;
    v0.charMember = (param1) * 4 + 134;
    v0.paletteMember = (param1) * 4 + 134 + 1;
    v0.tilemapMember = (param1) * 4 + 134 + 2;
    v0.destTilemapX = 136;
    v0.destTilemapY = 16;
    v0.bgLayer = 2;
    v0.paletteSize = 1;
    v0.paletteOffset = 13;
    v0.charOffset = 0;
    v0.heapID = heapID;

    ImageClipBg_Init(&param0->context.bg, &v0);

    param0->context.backdropIndex = param1;
}

void PhotoRenderer_FreeBackground(PhotoRenderer *param0)
{
    ImageClipBg_Free(&param0->context.bg);
}

void PhotoRenderer_GetPokemonSpriteCenter(PhotoRenderer *param0, int *param1, int *param2)
{
    *param1 = PokemonSprite_GetAttribute(param0->context.pokemonSprite.unk_00, MON_SPRITE_X_CENTER);
    *param2 = PokemonSprite_GetAttribute(param0->context.pokemonSprite.unk_00, MON_SPRITE_Y_CENTER);
}

int PhotoRenderer_GetSpriteCount(PhotoRenderer *param0)
{
    return param0->resources.spriteCount;
}

void PhotoRenderer_GetMaxOutOfBounds(PhotoRenderer *param0, int *param1, int *param2)
{
    int v0;
    int v1;
    int v2;
    int v3;
    ImageClipSpriteResource *v4 = param0->resources.frontSprites.next;
    v0 = 0;
    v1 = 0;

    while (v4 != &param0->resources.frontSprites) {
        PhotoRenderer_GetSpriteOutOfBounds(v4, &v2, &v3);

        if (MATH_ABS(v2) > MATH_ABS(v0)) {
            v0 = v2;
        }

        if (MATH_ABS(v3) > MATH_ABS(v1)) {
            v1 = v3;
        }

        v4 = v4->next;
    }

    *param1 = v0;
    *param2 = v1;
}

void PhotoRenderer_SetSpriteDiffuse(PhotoRenderer *param0, GXRgb param1)
{
    ImageClipSpriteResource *v0 = param0->resources.frontSprites.next;

    while (v0 != &param0->resources.frontSprites) {
        if (v0->category == 0) {
            ImageClipSprite *v1 = v0->data;

            SoftwareSprite_SetDiffuse(v1->softSprite, param1);
        } else {
            ImageClipPokemonSprite *v2 = v0->data;

            PokemonSprite_SetAttribute(v2->sprite, MON_SPRITE_DIFFUSE_R, (param1 >> 10) & 0x1f);
            PokemonSprite_SetAttribute(v2->sprite, MON_SPRITE_DIFFUSE_G, (param1 >> 5) & 0x1f);
            PokemonSprite_SetAttribute(v2->sprite, MON_SPRITE_DIFFUSE_B, (param1 >> 0) & 0x1f);
        }

        v0 = v0->next;
    }

    v0 = param0->resources.backSprites.next;

    while (v0 != &param0->resources.backSprites) {
        ImageClipSprite *v3 = v0->data;

        SoftwareSprite_SetDiffuse(v3->softSprite, param1);
        v0 = v0->next;
    }
}

static void PhotoRenderer_ClassifySprite(PhotoRenderer *param0, ImageClipSpriteResource *param1, BOOL param2, NNSG2dCharacterData **param3)
{
    int v0;
    int v1;
    int v2;
    int v3;
    int v4;
    int v5;
    int v6;
    int v7;
    int v8;
    int v9;
    int v10;
    int v11, v12;
    BOOL v13;
    NNSG2dCharacterData *v14;
    int v15, v16;

    ImageClipSpriteResource_GetPosition(param1, &v1, &v2);
    ImageClipSpriteResource_GetSize(param1, &v3, &v4);
    ImageClipSpriteResource_GetBounds(param1, &v5, &v15, &v6, &v16);

    v7 = v2 + v6;
    v8 = v2 + v4 - v16;
    v9 = v1 + v5;
    v10 = v1 + v3 - v15;
    v14 = param3[(100 + 18)];

    v13 = 0;

    for (v0 = 0; v0 < 16; v0++) {
        VisualCompetition_GetGridPoint(v7, v8, v9, v10, v0, &v11, &v12);
        v13 |= ImageClipPokemonSprite_IsPixelHit(&param0->context.pokemonSprite, v11, v12, v14);
    }

    if (v13) {
        if (param2) {
            ImageClipResourceList_InsertAfter(param1, &param0->resources.frontSprites);
        } else {
            ImageClipResourceList_InsertAfter(param1, param0->resources.frontSprites.prev);
        }
    } else {
        if (param2) {
            ImageClipResourceList_InsertAfter(param1, &param0->resources.backSprites);
        } else {
            ImageClipResourceList_InsertAfter(param1, param0->resources.backSprites.prev);
        }
    }
}

static void PhotoRenderer_GetSpriteOutOfBounds(ImageClipSpriteResource *param0, int *param1, int *param2)
{
    int v0, v1;
    int v2, v3;
    int v4, v5;
    int v6, v7;
    int v8, v9, v10, v11;
    int v12, v13, v14, v15;

    ImageClipSpriteResource_GetSize(param0, &v0, &v1);
    ImageClipSpriteResource_GetPosition(param0, &v2, &v3);
    ImageClipSpriteResource_GetBounds(param0, &v4, &v6, &v5, &v7);

    v8 = v3 + v5;
    v9 = v3 + v1 - v7;
    v10 = v2 + v4;
    v11 = v2 + v0 - v6;
    v14 = (136 + 2) - v10;
    v15 = v11 - ((136 + 2) + (112 - (2 * 2)));
    v12 = (16 + 2) - v8;
    v13 = v9 - ((16 + 2) + (129 - (2 * 2)));

    if (v14 > 0) {
        *param1 = v14;
    } else if (v15 > 0) {
        *param1 = -v15;
    } else {
        *param1 = 0;
    }

    if (v12 > 0) {
        *param2 = v12;
    } else if (v13 > 0) {
        *param2 = -v13;
    } else {
        *param2 = 0;
    }
}
