#include "applications/pc_boxes/box_mon_sprite_manager.h"

#include <nitro.h>
#include <string.h>

#include "applications/pc_boxes/box_app_manager.h"
#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_mon_sprite_manager.h"
#include "applications/pc_boxes/struct_box_mon_sprite.h"

#include "graphics.h"
#include "heap.h"
#include "narc.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "sprite.h"

BOOL BoxMonSprite_LoadManager(BoxMonSpriteManager *param0, BoxGraphics *param1, const BoxApplication *param2, SpriteList *param3, NARC *param4)
{
    NNSG2dImagePaletteProxy v0;
    NNSG2dPaletteData *v1;
    void *v2;

    param0->iconNarc = NARC_ctor(NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, HEAP_ID_BOX_GRAPHICS);

    NNS_G2dInitImagePaletteProxy(&v0);
    Graphics_LoadPartialPaletteFromOpenNARC(param0->iconNarc, PokeIconPalettesFileIndex(), NNS_G2D_VRAM_TYPE_2DMAIN, 2 * 0x20, 10, &v0);

    v2 = Graphics_GetPlttDataFromOpenNARC(param0->iconNarc, PokeIconPalettesFileIndex(), &v1, HEAP_ID_BOX_GRAPHICS);

    if (v2) {
        BOOL v3;
        NNSG2dPaletteCompressInfo *v4;

        NNS_G2dInitImagePaletteProxy(&v0);
        v3 = NNS_G2dGetUnpackedPaletteCompressInfo(v2, &v4);
        BoxGraphics_BlendPalette(v1->pRawData, v1->pRawData, v1->szByte / sizeof(u16), 0x57f, 8);

        if (v3) {
            NNS_G2dLoadPaletteEx(v1, v4, 6 * 0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &v0);
        } else {
            NNS_G2dLoadPalette(v1, 6 * 0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &v0);
        }

        Heap_Free(v2);
    }

    param0->cellBank = Graphics_GetCellBankFromOpenNARC(param4, 21, 1, &(param0->cellBankData), HEAP_ID_BOX_GRAPHICS);
    param0->animBank = Graphics_GetAnimBankFromOpenNARC(param4, 22, 1, &(param0->animBankData), HEAP_ID_BOX_GRAPHICS);
    param0->formCellBank = Graphics_GetCellBankFromOpenNARC(param4, 23, 1, &(param0->formCellBankData), HEAP_ID_BOX_GRAPHICS);
    param0->formAnimBank = Graphics_GetAnimBankFromOpenNARC(param4, 24, 1, &(param0->formAnimBankData), HEAP_ID_BOX_GRAPHICS);

    if ((param0->cellBank == NULL) || (param0->animBank == NULL) || (param0->iconNarc == NULL)) {
        return 0;
    }

    param0->spriteList = param3;
    param0->boxApp = param2;
    param0->boxGraphics = param1;

    return 1;
}

void BoxMonSprite_FreeManager(BoxMonSpriteManager *param0)
{
    if (param0->cellBank != NULL) {
        Heap_Free(param0->cellBank);
        param0->cellBank = NULL;
    }

    if (param0->animBank != NULL) {
        Heap_Free(param0->animBank);
        param0->animBank = NULL;
    }

    if (param0->formCellBank != NULL) {
        Heap_Free(param0->formCellBank);
        param0->formCellBank = NULL;
    }

    if (param0->formAnimBank != NULL) {
        Heap_Free(param0->formAnimBank);
        param0->formAnimBank = NULL;
    }

    if (param0->iconNarc != NULL) {
        NARC_dtor(param0->iconNarc);
    }
}

void BoxMonSprite_InitSlots(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2)
{
    while (param2--) {
        param1->sprite = NULL;
        NNS_G2dInitImageProxy(&(param1->imageProxy));
        param1++;
    }
}

void BoxMonSprite_DeleteSlots(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2)
{
    while (param2--) {
        if (param1->sprite != NULL) {
            Sprite_Delete(param1->sprite);
            param1->sprite = NULL;
        }

        param1++;
    }
}

void BoxMonSprite_CopySlot(const BoxMonSprite *param0, BoxMonSprite *param1, u32 param2)
{
    MI_CpuCopy32(param0, param1, sizeof(BoxMonSprite) * param2);
}

void BoxMonSprite_CreateFromBoxMon(BoxMonSpriteManager *param0, BoxPokemon *boxMon, s32 param2, s32 param3, u32 param4, u32 param5, u32 param6, BoxMonSprite *param7)
{
    NNSG2dCharacterData *v0;
    SpriteResourcesHeader v1;
    u16 species;
    u8 isEgg;
    u8 form;
    u8 reencrypt = BoxPokemon_EnterDecryptionContext(boxMon);
    BoxGraphics_InitSpriteResources(&v1, NULL, BoxGraphics_GetPaletteProxy(param0->boxGraphics), param0->cellBankData, param0->animBankData, param4);

    species = BoxPokemon_GetValue(boxMon, MON_DATA_SPECIES, NULL);
    isEgg = BoxPokemon_GetValue(boxMon, MON_DATA_IS_EGG, NULL);
    form = BoxPokemon_GetValue(boxMon, MON_DATA_FORM, NULL);
    param7->iconSpriteIndex = BoxPokemon_IconSpriteIndex((BoxPokemon *)boxMon);
    param7->paletteIndex = PokeIconPaletteIndex(species, form, isEgg);
    param7->heldItem = BoxPokemon_GetValue(boxMon, MON_DATA_HELD_ITEM, NULL);
    param7->markings = BoxPokemon_GetValue(boxMon, MON_DATA_MARKINGS, NULL);

    NNS_G2dInitImageProxy(&(param7->imageProxy));
    NARC_ReadFromMember(param0->iconNarc, param7->iconSpriteIndex, 0, ((4 * 4) * 0x20 + 0x80), param0->iconBuffer);
    NNS_G2dGetUnpackedCharacterData(param0->iconBuffer, &v0);

    v0->mappingType = GX_GetOBJVRamModeChar();
    v0->szByte = (4 * 4) * 0x20;

    NNS_G2dLoadImage1DMapping(v0, param6 * 0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &(param7->imageProxy));

    v1.imageProxy = &(param7->imageProxy);
    param7->sprite = BoxGraphics_CreateSprite(param0->spriteList, &v1, param2, param3, param5, NNS_G2D_VRAM_TYPE_2DMAIN);

    GF_ASSERT(param7->sprite != NULL);

    Sprite_SetExplicitPalette(param7->sprite, 2 + param7->paletteIndex);
    BoxMonSprite_UpdateTransparency(param0, param7, BoxApp_GetMonSpriteTransparencyMask(param0->boxApp));
    BoxPokemon_ExitDecryptionContext(boxMon, reencrypt);
}

void BoxMonSprite_CreateFromCharacterData(BoxMonSpriteManager *param0, BoxPokemon *boxMon, u32 param2, u32 param3, u8 *param4, s32 param5, s32 param6, u32 param7, u32 param8, u32 param9, BoxMonSprite *param10)
{
    NNSG2dCharacterData *v0;
    SpriteResourcesHeader v1;

    BOOL reencrypt = BoxPokemon_EnterDecryptionContext(boxMon);
    u8 isEgg = BoxPokemon_GetValue(boxMon, MON_DATA_IS_EGG, NULL);
    u8 form = BoxPokemon_GetValue(boxMon, MON_DATA_FORM, NULL);

    BoxGraphics_InitSpriteResources(&v1, NULL, BoxGraphics_GetPaletteProxy(param0->boxGraphics), param0->cellBankData, param0->animBankData, param7);

    param10->iconSpriteIndex = param3;
    param10->paletteIndex = PokeIconPaletteIndex(param2, form, isEgg);
    param10->heldItem = BoxPokemon_GetValue(boxMon, MON_DATA_HELD_ITEM, NULL);
    param10->markings = BoxPokemon_GetValue(boxMon, MON_DATA_MARKINGS, NULL);

    NNS_G2dInitImageProxy(&(param10->imageProxy));
    NNS_G2dGetUnpackedCharacterData(param4, &v0);

    v0->mappingType = GX_GetOBJVRamModeChar();
    v0->szByte = (4 * 4) * 0x20;

    NNS_G2dLoadImage1DMapping(v0, param9 * 0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &(param10->imageProxy));

    v1.imageProxy = &(param10->imageProxy);
    param10->sprite = BoxGraphics_CreateSprite(param0->spriteList, &v1, param5, param6, param8, NNS_G2D_VRAM_TYPE_2DMAIN);

    GF_ASSERT(param10->sprite != NULL);

    Sprite_SetExplicitPalette(param10->sprite, 2 + param10->paletteIndex);
    BoxMonSprite_UpdateTransparency(param0, param10, BoxApp_GetMonSpriteTransparencyMask(param0->boxApp));
    BoxPokemon_ExitDecryptionContext(boxMon, reencrypt);
}

void BoxMonSprite_UpdateTransparency(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2)
{
    if (param2 != 0) {
        int v0;

        if (param2 & 1) {
            if (param1->heldItem == 0) {
                Sprite_SetExplicitOAMMode(param1->sprite, GX_OAM_MODE_XLU);
                return;
            }
        }

        for (v0 = 0; v0 < 6; v0++) {
            if ((param2 & (2 << v0)) && ((param1->markings & (1 << v0)) == 0)) {
                Sprite_SetExplicitOAMMode(param1->sprite, GX_OAM_MODE_XLU);
                return;
            }
        }
    }

    Sprite_SetExplicitOAMMode(param1->sprite, GX_OAM_MODE_NORMAL);
}

void BoxMonSprite_SetMarkings(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2)
{
    param1->markings = param2;
}

void BoxMonSprite_SetHeldItem(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2)
{
    param1->heldItem = param2;
}

void BoxMonSprite_UpdateFormIcon(BoxMonSpriteManager *param0, BoxMonSprite *param1, BOOL param2)
{
    int v0;
    u32 v1;
    NNSG2dCharacterData *v2;

    if (param1->heldItem == 112 && param1->iconSpriteIndex == PokeIconSpriteIndex(SPECIES_GIRATINA, 0, GIRATINA_FORM_ALTERED)) {
        param1->iconSpriteIndex = PokeIconSpriteIndex(SPECIES_GIRATINA, 0, GIRATINA_FORM_ORIGIN);
    } else if (param1->heldItem != 112 && param1->iconSpriteIndex == PokeIconSpriteIndex(SPECIES_GIRATINA, 0, GIRATINA_FORM_ORIGIN)) {
        param1->iconSpriteIndex = PokeIconSpriteIndex(SPECIES_GIRATINA, 0, GIRATINA_FORM_ALTERED);
    } else if (param2 == 1 && param1->iconSpriteIndex == PokeIconSpriteIndex(SPECIES_SHAYMIN, 0, SHAYMIN_FORM_SKY)) {
        param1->iconSpriteIndex = PokeIconSpriteIndex(SPECIES_SHAYMIN, 0, SHAYMIN_FORM_LAND);
    } else {
        return;
    }

    v1 = param1->imageProxy.vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN] + (u32)G2_GetOBJCharPtr();

    NARC_ReadFromMember(param0->iconNarc, param1->iconSpriteIndex, 0, ((4 * 4) * 0x20 + 0x80), param0->iconBuffer);
    NNS_G2dGetUnpackedCharacterData(param0->iconBuffer, &v2);
    MI_CpuCopy32(v2->pRawData, (void *)v1, (4 * 4) * 0x20);
}

void BoxMonSprite_ReadIcon(BoxMonSpriteManager *param0, void *param1, u32 param2, u32 param3)
{
    NARC_ReadFromMember(param0->iconNarc, param2, 0, param3, param1);
}

void BoxMonSprite_LoadIcon(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2)
{
    if (param1->sprite != NULL) {
        NNSG2dCharacterData *v0;

        NNS_G2dInitImageProxy(&(param1->imageProxy));

        NARC_ReadFromMember(param0->iconNarc, param1->iconSpriteIndex, 0, ((4 * 4) * 0x20 + 0x80), param0->iconBuffer);
        NNS_G2dGetUnpackedCharacterData(param0->iconBuffer, &v0);
        v0->mappingType = GX_GetOBJVRamModeChar();
        v0->szByte = (4 * 4) * 0x20;

        NNS_G2dLoadImage1DMapping(v0, param2 * 0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &(param1->imageProxy));

        Sprite_SetImageProxy(param1->sprite, &(param1->imageProxy));
    }
}

void BoxMonSprite_SetAnim(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2)
{
    if ((param2 == 1) || (param2 == 2)) {
        Sprite_SetAffineOverwriteMode(param1->sprite, 1);
    } else {
        Sprite_SetAffineOverwriteMode(param1->sprite, 0);
    }

    Sprite_SetAnim(param1->sprite, param2);
}

BOOL BoxMonSprite_IsAnimDone(BoxMonSpriteManager *param0, BoxMonSprite *param1)
{
    return Sprite_IsAnimated(param1->sprite) == 0;
}

void BoxGraphics_ApplyMonInMultiSelectShading(BoxMonSpriteManager *param0, BoxMonSprite *param1, BOOL isSelected)
{
    u32 v0 = ((isSelected) ? 6 : 2) + param1->paletteIndex;

    Sprite_SetExplicitPalette(param1->sprite, v0);
}

NNSG2dCellDataBank *BoxMonSprite_GetCellBank(BoxMonSpriteManager *param0)
{
    return param0->cellBankData;
}

NNSG2dAnimBankData *BoxMonSprite_GetAnimBank(BoxMonSpriteManager *param0)
{
    return param0->animBankData;
}
