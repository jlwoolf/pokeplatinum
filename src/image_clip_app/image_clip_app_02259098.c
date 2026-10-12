#include "image_clip_app/image_clip_app_02259098.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_image_clip_pokemon_sprite.h"

#include "image_clip_app/image_clip_app_02255094.h"
#include "image_clip_app/struct_image_clip_app_022596B0.h"
#include "image_clip_app/struct_image_clip_app_0225A0E4.h"

#include "graphics.h"
#include "heap.h"
#include "pokemon.h"
#include "pokemon_sprite.h"
#include "system.h"
#include "touch_screen.h"

static int ImageClipPokemonSprite_GetFirstOpaqueColumn(char *param0, int param1);
static void ImageClipPokemonSprite_ClampHitRect(TouchScreenRect *rect, int param1, int param2, int param3, int param4);
static void ImageClipPokemonSprite_ComputePixelBounds(char *param0, int param1, int param2, ImageClipPixelBounds *param3);

void ImageClipPokemonSprite_LoadDecryptedSprite(ImageClipGraphics *param0, PokemonSpriteTemplate *param1)
{
    void *v0 = LoadMemberFromNARC(param1->narcID, param1->character, 0, 14, 0);
    NNSG2dCharacterData *v1 = ImageClipGraphics_AddCharacterData(param0, v0, (100 + 18));

    PokemonSprite_Decrypt((u8 *)v1->pRawData, param1->narcID);
}

void ImageClipPokemonSprite_Init(ImageClipPokemonSprite *param0, PokemonSpriteManager *param1, Pokemon *param2, PokemonSpriteTemplate *param3, int param4)
{
    ImageClipPokemonSprite_InitEx(param0, param1, param2, param3, param4, 0);
}

void ImageClipPokemonSprite_InitEx(ImageClipPokemonSprite *param0, PokemonSpriteManager *param1, Pokemon *param2, PokemonSpriteTemplate *param3, int param4, BOOL param5)
{
    int v0 = Pokemon_GetValue(param2, MON_DATA_SPECIES, NULL);

    Pokemon_BuildSpriteTemplateDP(param3, param2, 2);
    param0->sprite = PokemonSpriteManager_CreateSprite(param1, param3, 192, 56, 0, 0, NULL, NULL);

    {
        int v1, v2;

        ImageClipPokemonSprite_GetSize(param0, &v1, &v2);

        v1 /= 2;
        v2 /= 2;

        param0->hitTable.rect.top = 56 - v2;
        param0->hitTable.rect.bottom = 56 + v2;
        param0->hitTable.rect.left = 192 - v1;
        param0->hitTable.rect.right = 192 + v1;

        ImageClipPokemonSprite_ClampHitRect(&param0->hitTable, 192, 56, v1, v2);
    }

    {
        u8 v3 = Pokemon_DPSpriteYOffset(param2, 2);
        void *v4;
        NNSG2dCharacterData *v5;

        v4 = LoadMemberFromNARC(param3->narcID, param3->character, 0, param4, 0);

        NNS_G2dGetUnpackedCharacterData(v4, &v5);
        PokemonSprite_Decrypt((u8 *)v5->pRawData, param3->narcID);

        if (param5 == 0) {
            ImageClipPokemonSprite_ComputePixelBounds(v5->pRawData, v5->W * 8, v5->H * 8, &param0->pixelBounds);
        } else {
            param0->pixelBounds.unk_00 = ImageClipPokemonSprite_GetFirstOpaqueColumn(v5->pRawData, v5->W * 8);
            param0->pixelBounds.unk_01 = param0->pixelBounds.unk_00;
            param0->pixelBounds.unk_03 = v3;
            param0->pixelBounds.unk_02 = v3;
        }

        Heap_Free(v4);
    }

    param0->pokemon = param2;
}

void ImageClipPokemonSprite_Free(ImageClipPokemonSprite *param0)
{
    PokemonSprite_Delete(param0->sprite);
    memset(param0, 0, sizeof(ImageClipPokemonSprite));
}

void ImageClipPokemonSprite_SetZ(ImageClipPokemonSprite *param0, int param1)
{
    PokemonSprite_SetAttribute(param0->sprite, MON_SPRITE_Z_CENTER, param1);
}

int ImageClipPokemonSprite_GetZ(ImageClipPokemonSprite *param0)
{
    return PokemonSprite_GetAttribute(param0->sprite, MON_SPRITE_Z_CENTER);
}

void ImageClipPokemonSprite_SetPosition(ImageClipPokemonSprite *param0, int param1, int param2)
{
    int v0, v1;

    ImageClipPokemonSprite_GetSize(param0, &v0, &v1);
    PokemonSprite_SetAttribute(param0->sprite, MON_SPRITE_X_CENTER, param1);
    PokemonSprite_SetAttribute(param0->sprite, MON_SPRITE_Y_CENTER, param2);

    v1 /= 2;
    v0 /= 2;

    ImageClipPokemonSprite_ClampHitRect(&param0->hitTable, param1, param2, v0, v1);
}

BOOL ImageClipPokemonSprite_IsScreenTouched(ImageClipPokemonSprite *param0)
{
    return TouchScreen_LocationHeld(&param0->hitTable);
}

BOOL ImageClipPokemonSprite_IsTouchInHitTable(ImageClipPokemonSprite *param0, int param1, int param2)
{
    return TouchScreen_IsTouchInHitTable(&param0->hitTable, param1, param2);
}

void ImageClipPokemonSprite_GetCenter(ImageClipPokemonSprite *param0, int *xCenter, int *yCenter)
{
    *xCenter = PokemonSprite_GetAttribute(param0->sprite, MON_SPRITE_X_CENTER);
    *yCenter = PokemonSprite_GetAttribute(param0->sprite, MON_SPRITE_Y_CENTER);
}

void ImageClipPokemonSprite_GetSize(ImageClipPokemonSprite *param0, int *param1, int *param2)
{
    *param1 = 80;
    *param2 = 80;
}

BOOL ImageClipPokemonSprite_IsTouchedByTouch(ImageClipPokemonSprite *param0, int *param1, int *param2, NNSG2dCharacterData *param3)
{
    int v0;
    int v1, v2;
    int v3, v4;

    v0 = ImageClipPokemonSprite_IsScreenTouched(param0);

    if (v0 == 0) {
        return 0;
    }

    ImageClipPokemonSprite_GetCenter(param0, &v3, &v4);
    ImageClipPokemonSprite_GetSize(param0, &v1, &v2);

    v3 -= (v1 / 2);
    v4 -= (v2 / 2);

    *param1 = gSystem.touchX - v3;
    *param2 = gSystem.touchY - v4;

    v0 = ImageClipGraphics_TestPixel(param3, *param1, *param2, 0);

    if (v0 == 0) {
        return 1;
    }

    return 0;
}

BOOL ImageClipPokemonSprite_IsPixelHit(ImageClipPokemonSprite *param0, int param1, int param2, NNSG2dCharacterData *param3)
{
    int v0;
    int v1, v2;
    int v3, v4;

    v0 = ImageClipPokemonSprite_IsTouchInHitTable(param0, param1, param2);

    if (v0 == 0) {
        return 0;
    }

    ImageClipPokemonSprite_GetCenter(param0, &v3, &v4);
    ImageClipPokemonSprite_GetSize(param0, &v1, &v2);

    v3 -= (v1 / 2);
    v4 -= (v2 / 2);

    param1 -= v3;
    param2 -= v4;

    v0 = ImageClipGraphics_TestPixel(param3, param1, param2, 0);

    if (v0 == 0) {
        return 1;
    }

    return 0;
}

void ImageClipPokemonSprite_GetPixelBounds(ImageClipPokemonSprite *param0, ImageClipPixelBounds *param1)
{
    *param1 = param0->pixelBounds;
}

static int ImageClipPokemonSprite_GetFirstOpaqueColumn(char *param0, int param1)
{
    int v0, v1;
    int v2;
    int v3;
    u8 v4;

    for (v0 = 0; v0 < 80; v0++) {
        for (v1 = 0; v1 < 80; v1++) {
            v2 = ((v1 * param1) + v0) / 2;
            v3 = ((v1 * param1) + v0) % 2;
            v4 = 0xf << (4 * v3);

            if ((param0[v2] & v4) != 0) {
                return v0;
            }
        }
    }

    return 80;
}

static void ImageClipPokemonSprite_ComputePixelBounds(char *param0, int param1, int param2, ImageClipPixelBounds *param3)
{
    int v0, v1;
    int v2;
    int v3;
    u8 v4;

    param3->unk_00 = 80 / 2;
    param3->unk_01 = 80 / 2;
    param3->unk_02 = 80 / 2;
    param3->unk_03 = 80 / 2;

    for (v0 = 0; v0 < 80; v0++) {
        for (v1 = 0; v1 < 80; v1++) {
            v2 = ((v1 * param1) + v0) / 2;
            v3 = ((v1 * param1) + v0) % 2;
            v4 = 0xf << (4 * v3);

            if ((param0[v2] & v4) != 0) {
                if (param3->unk_00 > v0) {
                    param3->unk_00 = v0;
                }

                if (param3->unk_01 > 80 - v0) {
                    param3->unk_01 = 80 - v0;
                }

                if (param3->unk_02 > v1) {
                    param3->unk_02 = v1;
                }

                if (param3->unk_03 > 80 - v1) {
                    param3->unk_03 = 80 - v1;
                }
            }
        }
    }
}

static void ImageClipPokemonSprite_ClampHitRect(TouchScreenRect *rect, int param1, int param2, int param3, int param4)
{
    if ((param2 - param4) >= 0) {
        rect->rect.top = param2 - param4;
    } else {
        rect->rect.top = 0;
    }

    if ((param2 + param4) <= 191) {
        rect->rect.bottom = param2 + param4;
    } else {
        rect->rect.bottom = 191;
    }

    if ((param1 - param3) >= 0) {
        rect->rect.left = param1 - param3;
    } else {
        rect->rect.left = 0;
    }

    if ((param1 + param3) <= 255) {
        rect->rect.right = param1 + param3;
    } else {
        rect->rect.right = 255;
    }
}
