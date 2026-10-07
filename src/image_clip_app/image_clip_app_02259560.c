#include "image_clip_app/image_clip_app_02259560.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_020298D8.h"

#include "image_clip_app/image_clip_app.h"
#include "image_clip_app/image_clip_app_02259098.h"
#include "image_clip_app/struct_image_clip_app_02255040.h"
#include "image_clip_app/struct_image_clip_app_02259560.h"
#include "image_clip_app/struct_image_clip_app_022596B0.h"

void ImageClipSpriteResource_SetZ(ImageClipSpriteResource *param0, int param1)
{
    if (param0->unk_04 < 3) {
        ImageClipSprite *v0 = param0->unk_00;
        ImageClipSprite_SetPriority(v0, param1);
    } else {
        UnkStruct_020298D8 *v1 = param0->unk_00;
        ImageClipPokemonSprite_SetZ(v1, param1);
    }
}

BOOL ImageClipSpriteResource_IsHit(ImageClipSpriteResource *param0, int param1, int param2)
{
    if (param0->unk_04 < 3) {
        ImageClipSprite *v0 = param0->unk_00;

        if (param1 == 0xffffffff) {
            return ImageClipSprite_IsTouched(v0);
        } else {
            return ImageClipSprite_ContainsTouch(v0, param1, param2);
        }
    }

    {
        UnkStruct_020298D8 *v1 = param0->unk_00;

        if (param1 == 0xffffffff) {
            return ImageClipPokemonSprite_IsScreenTouched(v1);
        } else {
            return ImageClipPokemonSprite_IsTouchInHitTable(v1, param1, param2);
        }
    }
}

BOOL ImageClipSpriteResource_IsPixelHit(ImageClipSpriteResource *param0, int *param1, int *param2, NNSG2dCharacterData **param3)
{
    NNSG2dCharacterData *v0;

    if (param0->unk_04 == 0) {
        ImageClipSprite *v1 = param0->unk_00;

        v0 = param3[v1->unk_00];
        return ImageClipSprite_HitTest(v1, param1, param2, v0);
    }

    if (param0->unk_04 == 1) {
        ImageClipSprite *v2 = param0->unk_00;
        int v3 = v2->unk_00 + 100;

        v0 = param3[v3];
        return ImageClipSprite_HitTest(v2, param1, param2, v0);
    }

    if (param0->unk_04 == 2) {
        ImageClipSprite *v4 = param0->unk_00;
        int v5 = v4->unk_00 + 100;

        v0 = param3[v5];
        return ImageClipSprite_HitTest(v4, param1, param2, v0);
    }

    {
        UnkStruct_020298D8 *v6 = param0->unk_00;

        v0 = param3[(100 + 18)];
        return ImageClipPokemonSprite_IsTouchedByTouch(v6, param1, param2, v0);
    }
}

void ImageClipSpriteResource_SetPosition(ImageClipSpriteResource *param0, int param1, int param2)
{
    if (param0->unk_04 < 3) {
        ImageClipSprite *v0 = param0->unk_00;

        ImageClipSprite_SetPosition(v0, param1, param2);
    } else {
        UnkStruct_020298D8 *v1 = param0->unk_00;
        int v2, v3;

        ImageClipPokemonSprite_GetSize(v1, &v2, &v3);
        v2 /= 2;
        v3 /= 2;
        param1 += v2;
        param2 += v3;
        ImageClipPokemonSprite_SetPosition(v1, param1, param2);
    }
}

void ImageClipSpriteResource_GetPosition(ImageClipSpriteResource *param0, int *param1, int *param2)
{
    if (param0->unk_04 < 3) {
        ImageClipSprite *v0 = param0->unk_00;
        ImageClipSprite_GetPosition(v0, param1, param2);
    } else {
        UnkStruct_020298D8 *v1 = param0->unk_00;
        int v2, v3;

        ImageClipPokemonSprite_GetCenter(v1, param1, param2);
        ImageClipPokemonSprite_GetSize(v1, &v2, &v3);

        v2 /= 2;
        v3 /= 2;
        *param1 -= v2;
        *param2 -= v3;
    }
}

void ImageClipSpriteResource_GetSize(ImageClipSpriteResource *param0, int *param1, int *param2)
{
    if (param0->unk_04 < 3) {
        ImageClipSprite *v0 = param0->unk_00;
        ImageClipSprite_GetDimensions(v0, param1, param2);
    } else {
        UnkStruct_020298D8 *v1 = param0->unk_00;
        ImageClipPokemonSprite_GetSize(v1, param1, param2);
    }
}

void ImageClipSpriteResource_GetBounds(ImageClipSpriteResource *param0, int *param1, int *param2, int *param3, int *param4)
{
    if (param0->unk_04 < 3) {
        ImageClipSprite *v0 = param0->unk_00;
        ImageClipSprite_GetDimensionOffset(v0, param1, param3);
        *param2 = *param1;
        *param4 = *param3;
    } else {
        ImageClipPixelBounds v1;
        UnkStruct_020298D8 *v2 = param0->unk_00;

        ImageClipPokemonSprite_GetPixelBounds(v2, &v1);

        *param1 = v1.unk_00;
        *param2 = v1.unk_01;
        *param3 = v1.unk_02;
        *param4 = v1.unk_03;
    }
}

void ImageClipSpriteResource_Move(ImageClipSpriteResource *param0, int param1, int param2)
{
    ImageClipSpriteResource *v0;
    int v1, v2;

    v0 = param0->unk_08;

    while (v0 != param0) {
        ImageClipSpriteResource_GetPosition(v0, &v1, &v2);

        v1 += param1;
        v2 += param2;

        ImageClipSpriteResource_SetPosition(v0, v1, v2);

        v0 = v0->unk_08;
    }
}

void ImageClipSpriteResource_GetBoundingBox(ImageClipSpriteResource *param0, int *param1, int *param2, int *param3, int *param4)
{
    int v0, v1;
    int v2, v3;
    int v4, v5;
    int v6, v7;

    ImageClipSpriteResource_GetSize(param0, &v0, &v1);
    ImageClipSpriteResource_GetPosition(param0, &v2, &v3);
    ImageClipSpriteResource_GetBounds(param0, &v4, &v6, &v5, &v7);

    *param1 = v3 + v5;
    *param2 = v3 + v1 - v7;
    *param3 = v2 + v4;
    *param4 = v2 + v0 - v6;
}

void ImageClipSpriteResource_GetCenter(ImageClipSpriteResource *param0, int *param1, int *param2)
{
    int v0, v1;
    int v2, v3;

    ImageClipSpriteResource_GetSize(param0, &v0, &v1);
    ImageClipSpriteResource_GetPosition(param0, &v2, &v3);

    *param1 = v2 + (v0 / 2);
    *param2 = v3 + (v1 / 2);
}
