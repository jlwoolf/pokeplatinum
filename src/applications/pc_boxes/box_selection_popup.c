#include "applications/pc_boxes/box_selection_popup.h"

#include <nitro.h>

#include "generated/pokemon_colors.h"
#include "generated/species.h"

#include "applications/pc_boxes/box_app_manager.h"
#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_mon_sprite_manager.h"
#include "applications/pc_boxes/struct_box_selection_popup.h"

#include "bg_window.h"
#include "font.h"
#include "font_special_chars.h"
#include "graphics.h"
#include "heap.h"
#include "item.h"
#include "message.h"
#include "narc.h"
#include "pc_boxes.h"
#include "pokemon.h"
#include "sprite.h"
#include "string_gf.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "text.h"

typedef struct {
    BoxSelectionPopup *boxSelectionPopup;
    u8 state;
    u8 counter;
    BOOL done;
} BoxSelectionPopupAnim;

typedef struct {
    BoxSelectionPopup *boxSelectionPopup;
    BgConfig *bgConfig;
    fx32 offset;
    fx32 targetOffset;
    fx32 offsetStep;
    u16 stepCount;
    u16 state;
} BoxSelectionPopupItemAnim;

static int BoxSelectionPopup_GetFirstBoxID(BoxSelectionPopup *param0);
static void BoxSelectionPopup_ResetBoxIcons(BoxSelectionPopup *param0);
static void BoxSelectionPopup_CacheBoxIcon(BoxSelectionPopup *param0, u32 param1);
static void BoxSelectionPopup_LoadBoxIcon(BoxSelectionPopup *param0, u32 param1, u32 param2);
static void BoxSelectionPopup_CreateBoxIcons(BoxSelectionPopup *param0);
static void BoxSelectionPopup_DeleteBoxIcons(BoxSelectionPopup *param0);
static void BoxSelectionPopup_ShowBoxIcons(BoxSelectionPopup *param0);
static void BoxSelectionPopup_DrawBoxName(BoxSelectionPopup *param0);
static void BoxSelectionPopup_ClearBoxName(BoxSelectionPopup *param0);
static void BoxSelectionPopup_DrawBoxCounts(BoxSelectionPopup *param0);
static void BoxSelectionPopup_ClearBoxCounts(BoxSelectionPopup *param0);
static void BoxSelectionPopup_StartShowAnim(BoxSelectionPopup *param0, int param1);
static void BoxSelectionPopup_AnimDone(SysTask *param0, void *param1);
static BOOL BoxSelectionPopup_IsAnimDone(BoxSelectionPopup *param0);
static void BoxSelectionPopup_ShowAnimTask(SysTask *param0, void *param1);
static void BoxSelectionPopup_HideAnimTask(SysTask *param0, void *param1);
static void BoxSelectionPopup_ShowItemInfoTask(SysTask *param0, void *param1);
static void BoxSelectionPopup_HideItemInfoTask(SysTask *param0, void *param1);
static void BoxSelectionPopup_LoadItemIcon(BoxSelectionPopup *param0, u32 param1);
static void BoxSelectionPopup_SetItemIconY(BoxSelectionPopup *param0, fx32 param1);
static void BoxSelectionPopup_DeleteItemIcon(BoxSelectionPopup *param0);

BOOL BoxSelectionPopup_Load(BoxSelectionPopup *param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4, NARC *param5)
{
    int v0;

    param0->boxGraphics = param1;
    param0->bgConfig = param3;
    param0->boxApp = param2;
    param0->spriteList = param4;

    Graphics_LoadTilesToBgLayerFromOpenNARC(param5, 4, param3, 1, 0, 0, 1, HEAP_ID_BOX_GRAPHICS);

    {
        NNSG2dPaletteData *v1;
        void *v2;

        v2 = Graphics_GetPlttDataFromOpenNARC(param5, 27, &v1, HEAP_ID_BOX_GRAPHICS);
        MI_CpuCopy16(v1->pRawData, &(param0->paletteBuffer[0][0]), 0x40);
        Heap_Free(v2);

        v2 = Graphics_GetPlttDataFromOpenNARC(param5, 20, &v1, HEAP_ID_BOX_GRAPHICS);
        MI_CpuCopy16(v1->pRawData, &(param0->paletteBuffer[0][32]), 0x20);
        Heap_Free(v2);

        {
            int v3;
            fx32 v4, v5;

            v4 = 16 << FX32_SHIFT;
            v5 = v4 / (8 - 1);

            for (v3 = 8 - 1; v3 >= 1; v3--) {
                BoxGraphics_BlendPalette(param0->paletteBuffer[0], param0->paletteBuffer[v3], 48, 0x7fff, (v4 >> FX32_SHIFT));
                v4 -= v5;
            }

            DC_FlushRange(param0->paletteBuffer, 8 * 96);
        }

        GX_LoadOBJPltt(param0->paletteBuffer[8 - 1], 13 * 0x20, 96);
        GXS_LoadOBJPltt(param0->paletteBuffer[0], 13 * 0x20, 96);
    }

    param0->charDataFile = Graphics_GetCharDataFromOpenNARC(param5, 17, 1, &(param0->charData), HEAP_ID_BOX_GRAPHICS);
    param0->cellBank = Graphics_GetCellBankFromOpenNARC(param5, 18, 1, &(param0->cellBankData), HEAP_ID_BOX_GRAPHICS);
    param0->screenDataFile2 = Graphics_GetScrnDataFromOpenNARC(param5, 2, 1, &(param0->screenData2), HEAP_ID_BOX_GRAPHICS);
    param0->screenDataFile1 = Graphics_GetScrnDataFromOpenNARC(param5, 3, 1, &(param0->screenData1), HEAP_ID_BOX_GRAPHICS);
    param0->fontContext = FontSpecialChars_Init(2, 13, 4, HEAP_ID_BOX_GRAPHICS);
    param0->string = String_Init(500, HEAP_ID_BOX_GRAPHICS);
    param0->windows = NULL;
    param0->boxIconBitmap.pixels = param0->charData->pRawData;
    param0->boxIconBitmap.width = 32;
    param0->boxIconBitmap.height = 32;
    param0->itemDescriptionLoader = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_ITEM_DESCRIPTIONS, HEAP_ID_BOX_GRAPHICS);

    for (v0 = 0; v0 < 18; v0++) {
        param0->boxIconSprites[v0] = NULL;
    }

    if ((param0->charDataFile == NULL) || (param0->cellBank == NULL) || (param0->screenDataFile1 == NULL) || (param0->screenDataFile2 == NULL) || (param0->fontContext == NULL) || (param0->string == NULL)) {
        return 0;
    }

    return 1;
}

void BoxSelectionPopup_InitWindows(BoxSelectionPopup *param0)
{
    static const WindowTemplate v0[] = {
        { 1, 10, 6, 12, 2, 2, 128 },
        { 1, 3, 13, 26, 1, 2, 152 },
        { 1, 5, 25, 27, 6, 2, 178 }
    };

    param0->windows = Window_New(HEAP_ID_BOX_GRAPHICS, NELEMS(v0));

    if (param0->windows) {
        int v1;

        for (v1 = 0; v1 < NELEMS(v0); v1++) {
            Window_AddFromTemplate(param0->bgConfig, &param0->windows[v1], &v0[v1]);
        }
    }
}

void BoxSelectionPopup_Free(BoxSelectionPopup *param0)
{
    if (param0->itemDescriptionLoader) {
        MessageLoader_Free(param0->itemDescriptionLoader);
    }

    if (param0->charDataFile) {
        Heap_Free(param0->charDataFile);
    }

    if (param0->cellBank) {
        Heap_Free(param0->cellBank);
    }

    if (param0->screenDataFile1) {
        Heap_Free(param0->screenDataFile1);
    }

    if (param0->screenDataFile2) {
        Heap_Free(param0->screenDataFile2);
    }

    if (param0->fontContext) {
        FontSpecialChars_Free(param0->fontContext);
    }

    if (param0->string) {
        String_Free(param0->string);
    }

    if (param0->windows) {
        int v0;

        for (v0 = 0; v0 < 3; v0++) {
            Window_Remove(&(param0->windows[v0]));
        }

        Heap_Free(param0->windows);
    }
}

void BoxSelectionPopup_Show(BoxSelectionPopup *param0)
{
    param0->boxSelectionBoxID = BoxApp_GetBoxSelectionBoxID(param0->boxApp);
    BoxSelectionPopup_CreateBoxIcons(param0);
    BoxSelectionPopup_StartShowAnim(param0, 0);
}

BOOL BoxSelectionPopup_IsShowDone(BoxSelectionPopup *param0)
{
    return BoxSelectionPopup_IsAnimDone(param0);
}

void BoxSelectionPopup_Update(BoxSelectionPopup *param0)
{
    param0->boxSelectionBoxID = BoxApp_GetBoxSelectionBoxID(param0->boxApp);

    BoxSelectionPopup_ShowBoxIcons(param0);
    BoxSelectionPopup_DrawBoxName(param0);
    BoxSelectionPopup_DrawBoxCounts(param0);
}

void BoxSelectionPopup_Hide(BoxSelectionPopup *param0)
{
    BoxSelectionPopup_StartShowAnim(param0, 1);
}

BOOL BoxSelectionPopup_IsHideDone(BoxSelectionPopup *param0)
{
    return BoxSelectionPopup_IsAnimDone(param0);
}

void BoxSelectionPopup_DrawBoxIcon(BoxSelectionPopup *param0, u32 param1, u32 param2, NNS_G2D_VRAM_TYPE param3, NNSG2dImageProxy *param4)
{
    const PCBoxes *pcBoxes;
    BoxPokemon *boxMon;
    u32 v2, v3, v4, species;
    u8 color, v7;
    int v8;

    pcBoxes = BoxApp_GetPCBoxes(param0->boxApp);
    v8 = PCBoxes_GetWallpaper(pcBoxes, param1);

    if (v8 >= (16 + 8)) {
        v8 -= 8;
    }

    color = 13 * 0x10 + v8;
    Bitmap_FillRect8bpp(&(param0->boxIconBitmap), 9, 10, 14, 12, color);

    for (v3 = 0, v4 = 0; v3 < 5; v3++) {
        for (v2 = 0; v2 < 6; v2++) {
            boxMon = PCBoxes_GetBoxMonAt(pcBoxes, param1, v4++);
            v7 = BoxPokemon_EnterDecryptionContext(boxMon);
            species = BoxPokemon_GetValue(boxMon, MON_DATA_SPECIES, NULL);

            if (species) {
                if (BoxPokemon_GetValue(boxMon, MON_DATA_IS_EGG, NULL) == FALSE) {
                    u16 form = BoxPokemon_GetValue(boxMon, MON_DATA_FORM, NULL);

                    color = SpeciesData_GetFormValue(species, form, SPECIES_DATA_BODY_COLOR);
                } else {
                    color = (species != SPECIES_MANAPHY) ? MON_COLOR_WHITE : MON_COLOR_BLUE;
                }

                {
                    static const u8 v10[] = {
                        0xe,
                        0xf,
                        0x5,
                        0x4,
                        0xd,
                        0xc,
                        0x3,
                        0xb,
                        0xa,
                        0x9,
                    };

                    color = 14 * 0x10 + v10[color];
                }

                Bitmap_FillRect8bpp(&(param0->boxIconBitmap), 10 + v2 * 2, 11 + v3 * 2, 2, 2, color);
            }

            BoxPokemon_ExitDecryptionContext(boxMon, v7);
        }
    }

    if (param4) {
        switch (param3) {
        case NNS_G2D_VRAM_TYPE_2DMAIN:
            param0->charData->mappingType = GX_GetOBJVRamModeChar();
            break;
        case NNS_G2D_VRAM_TYPE_2DSUB:
            param0->charData->mappingType = GXS_GetOBJVRamModeChar();
            break;
        }

        NNS_G2dLoadImage1DMapping(param0->charData, param2 * 0x20, param3, param4);
    } else {
        DC_FlushRange(param0->charData->pRawData, param0->charData->szByte);

        switch (param3) {
        case NNS_G2D_VRAM_TYPE_2DMAIN:
            GX_LoadOBJ(param0->charData->pRawData, param2 * 0x20, param0->charData->szByte);
            break;
        case NNS_G2D_VRAM_TYPE_2DSUB:
            GXS_LoadOBJ(param0->charData->pRawData, param2 * 0x20, param0->charData->szByte);
            break;
        }
    }
}

NNSG2dCellDataBank *BoxSelectionPopup_GetCellBank(BoxSelectionPopup *param0)
{
    return param0->cellBankData;
}

static int BoxSelectionPopup_GetFirstBoxID(BoxSelectionPopup *param0)
{
    int v0 = param0->boxSelectionBoxID - (7 / 2);

    if (v0 < 0) {
        v0 += 18;
    }

    return v0;
}

static void BoxSelectionPopup_ResetBoxIcons(BoxSelectionPopup *param0)
{
    int v0;

    for (v0 = 0; v0 < 18; v0++) {
        param0->iconLoaded[v0] = 0;
    }
}

static void BoxSelectionPopup_CacheBoxIcon(BoxSelectionPopup *param0, u32 param1)
{
    MI_CpuCopy32(param0->charData->pRawData, param0->iconBuffer[param1], 1024);
    DC_FlushRange(param0->iconBuffer, 1024);
    param0->iconLoaded[param1] = 1;
}

static void BoxSelectionPopup_LoadBoxIcon(BoxSelectionPopup *param0, u32 param1, u32 param2)
{
    u32 v0 = 1584 + 32 * param1;

    if (param0->iconLoaded[param2]) {
        GX_LoadOBJ(param0->iconBuffer[param2], v0 * 0x20, 1024);
    } else {
        NNSG2dImageProxy v1;

        NNS_G2dInitImageProxy(&v1);
        BoxSelectionPopup_DrawBoxIcon(param0, param2, v0, NNS_G2D_VRAM_TYPE_2DMAIN, &v1);
        BoxSelectionPopup_CacheBoxIcon(param0, param2);
    }
}

static void BoxSelectionPopup_CreateBoxIcons(BoxSelectionPopup *param0)
{
    SpriteResourcesHeader v0;
    BoxMonSpriteManager *v1;
    NNSG2dImageProxy v2;
    VecFx32 v3;
    int v4, v5;

    BoxSelectionPopup_ResetBoxIcons(param0);
    v1 = BoxGraphics_GetBoxMonSpriteManager(param0->boxGraphics);
    BoxGraphics_InitSpriteResources(&v0, NULL, BoxGraphics_GetPaletteProxy(param0->boxGraphics), param0->cellBankData, v1->animBankData, 0);
    v5 = BoxSelectionPopup_GetFirstBoxID(param0);

    for (v4 = 0; v4 < 7; v4++) {
        NNS_G2dInitImageProxy(&v2);
        BoxSelectionPopup_DrawBoxIcon(param0, v5, 1584 + 32 * v4, NNS_G2D_VRAM_TYPE_2DMAIN, &v2);

        v0.imageProxy = &v2;
        param0->boxIconSprites[v4] = BoxGraphics_CreateSprite(param0->spriteList, &v0, 512, 256, 11, NNS_G2D_VRAM_TYPE_2DMAIN);

        GF_ASSERT(param0->boxIconSprites[v4] != NULL);

        Sprite_SetDrawFlag(param0->boxIconSprites[v4], FALSE);
        VEC_Set(&v3, FX32_CONST(32 + v4 * 32), FX32_CONST(88), 0);
        Sprite_SetPosition(param0->boxIconSprites[v4], &v3);
        BoxSelectionPopup_CacheBoxIcon(param0, v5);

        if (++v5 >= 18) {
            v5 = 0;
        }
    }

    for (v4 = 0; v4 < MAX_PC_BOXES; v4++) {
        param0->boxMonCounts[v4] = PCBoxes_CountMonsInBox(BoxApp_GetPCBoxes(param0->boxApp), v4);
    }
}

static void BoxSelectionPopup_DeleteBoxIcons(BoxSelectionPopup *param0)
{
    int v0;

    for (v0 = 0; v0 < 7; v0++) {
        if (param0->boxIconSprites[v0] != NULL) {
            Sprite_Delete(param0->boxIconSprites[v0]);
            param0->boxIconSprites[v0] = NULL;
        }
    }
}

static void BoxSelectionPopup_ShowBoxIcons(BoxSelectionPopup *param0)
{
    int v0, v1;

    v0 = BoxSelectionPopup_GetFirstBoxID(param0);

    for (v1 = 0; v1 < 7; v1++) {
        BoxSelectionPopup_LoadBoxIcon(param0, v1, v0);
        Sprite_SetDrawFlag(param0->boxIconSprites[v1], TRUE);

        if (++v0 >= 18) {
            v0 = 0;
        }
    }
}

static void BoxSelectionPopup_DrawBoxName(BoxSelectionPopup *param0)
{
    const PCBoxes *pcBoxes;
    Window *v1;
    u32 v2, v3;

    pcBoxes = BoxApp_GetPCBoxes(param0->boxApp);
    v1 = &param0->windows[0];

    PCBoxes_BufferBoxName(pcBoxes, param0->boxSelectionBoxID, param0->string);

    v2 = Font_CalcStringWidth(FONT_SYSTEM, param0->string, 0);
    v3 = 48 - (v2 / 2);

    Window_FillTilemap(v1, 7);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, param0->string, v3, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(2, 8, 7), NULL);
    Window_LoadTiles(v1);
}

static void BoxSelectionPopup_ClearBoxName(BoxSelectionPopup *param0)
{
    Window *v0 = &param0->windows[0];

    Window_FillTilemap(v0, 7);
    Window_LoadTiles(v0);
}

static void BoxSelectionPopup_DrawBoxCounts(BoxSelectionPopup *param0)
{
    s32 v0, v1;
    Window *v2 = &param0->windows[1];
    Window_FillTilemap(v2, 4);
    v0 = BoxSelectionPopup_GetFirstBoxID(param0);

    for (v1 = 0; v1 < 7; v1++) {
        FontSpecialChars_DrawPartyScreenHPText(param0->fontContext, param0->boxMonCounts[v0], 2, 2, v2, 32 * v1, 0);

        if (++v0 >= 18) {
            v0 = 0;
        }
    }

    Window_LoadTiles(v2);
}

static void BoxSelectionPopup_ClearBoxCounts(BoxSelectionPopup *param0)
{
    Window *v0 = &param0->windows[1];

    Window_FillTilemap(v0, 4);
    Window_LoadTiles(v0);
}

static void BoxSelectionPopup_StartShowAnim(BoxSelectionPopup *param0, int param1)
{
    static const SysTaskFunc v0[] = {
        BoxSelectionPopup_ShowAnimTask,
        BoxSelectionPopup_HideAnimTask,
    };
    BoxSelectionPopupAnim *v1 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxSelectionPopupAnim));

    if (v1) {
        v1->boxSelectionPopup = param0;
        v1->state = 0;
        v1->counter = 0;

        param0->task = SysTask_Start(v0[param1], v1, 0);

        if (param0->task == NULL) {
            Heap_Free(v1);
        }
    }
}

static void BoxSelectionPopup_AnimDone(SysTask *param0, void *param1)
{
    BoxSelectionPopupAnim *v0 = (BoxSelectionPopupAnim *)param1;

    v0->boxSelectionPopup->task = NULL;

    Heap_Free(v0);
    SysTask_Done(param0);
}

static BOOL BoxSelectionPopup_IsAnimDone(BoxSelectionPopup *param0)
{
    return param0->task == NULL;
}

static void BoxSelectionPopup_ShowAnimTask(SysTask *param0, void *param1)
{
    BoxSelectionPopupAnim *v0 = (BoxSelectionPopupAnim *)param1;
    BoxSelectionPopup *v1 = v0->boxSelectionPopup;

    switch (v0->state) {
    case 0:
        v0->counter += 1;

        if ((v0->counter * 2) < 10) {
            u32 v2 = 5 + (10 / 2);

            Bg_LoadToTilemapRect(v1->bgConfig, 1, v1->screenData1->rawData, 0, v2 - v0->counter, 32, v0->counter);
            Bg_CopyToTilemapRect(v1->bgConfig, 1, 0, v2, 32, v0->counter, v1->screenData1->rawData, 0, 10 - v0->counter, 32, 10);
        } else {
            Bg_LoadToTilemapRect(v1->bgConfig, 1, v1->screenData1->rawData, 0, 5, 32, 10);
            v0->state++;
        }

        Bg_CopyTilemapBufferToVRAM(v1->bgConfig, 1);
        v0->counter = 8 - 1;
        break;
    case 1:
        GX_LoadOBJPltt(v1->paletteBuffer[v0->counter], 13 * 0x20, 96);
        BoxSelectionPopup_ShowBoxIcons(v1);
        v0->state++;
        break;
    case 2:
        if (v0->counter) {
            v0->counter--;
        }

        GX_LoadOBJPltt(v1->paletteBuffer[v0->counter], 13 * 0x20, 96);

        if (v0->counter == 0) {
            Window_PutToTilemap(&v1->windows[0]);
            Window_PutToTilemap(&v1->windows[1]);
            BoxSelectionPopup_DrawBoxName(v1);
            BoxSelectionPopup_DrawBoxCounts(v1);
            Bg_CopyTilemapBufferToVRAM(v1->bgConfig, 1);
            v0->state++;
        }
        break;
    case 3:
        BoxSelectionPopup_AnimDone(param0, v0);
        break;
    }
}

static void BoxSelectionPopup_HideAnimTask(SysTask *param0, void *param1)
{
    BoxSelectionPopupAnim *v0 = (BoxSelectionPopupAnim *)param1;
    BoxSelectionPopup *v1 = v0->boxSelectionPopup;

    switch (v0->state) {
    case 0:
        BoxSelectionPopup_DeleteBoxIcons(v1);
        BoxSelectionPopup_ClearBoxName(v1);
        BoxSelectionPopup_ClearBoxCounts(v1);
        v0->state++;
        break;
    case 1:
        Bg_FillTilemapRect(v1->bgConfig, 1, 0x0, 0, 5, 32, 10, 17);
        v0->counter += 1;

        if ((v0->counter * 2) < 10) {
            u32 v2 = 5 + (10 / 2);

            Bg_LoadToTilemapRect(v1->bgConfig, 1, v1->screenData1->rawData, 0, 5 + v0->counter, 32, (10 / 2) - v0->counter);
            Bg_CopyToTilemapRect(v1->bgConfig, 1, 0, v2, 32, (10 / 2) - v0->counter, v1->screenData1->rawData, 0, 10 - v0->counter, 32, 10);
        } else {
            v0->state++;
        }

        Bg_CopyTilemapBufferToVRAM(v1->bgConfig, 1);
        break;
    case 2:
        BoxSelectionPopup_AnimDone(param0, v0);
    }
}

void BoxSelectionPopup_ShowItemInfo(BoxSelectionPopup *param0)
{
    BoxSelectionPopupItemAnim *v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxSelectionPopupItemAnim));

    if (v0) {
        u32 v1 = BoxApp_GetCursorOrPreviewedItem(param0->boxApp);

        Bg_SetOffset(param0->bgConfig, BG_LAYER_MAIN_1, 3, 0);
        Bg_LoadToTilemapRect(param0->bgConfig, 1, param0->screenData2->rawData, 0, 24, 32, 7);
        Window_FillTilemap(&param0->windows[2], 4);
        MessageLoader_GetString(param0->itemDescriptionLoader, v1, param0->string);
        Text_AddPrinterWithParamsAndColor(&param0->windows[2], FONT_SYSTEM, param0->string, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(2, 1, 4), NULL);
        Window_CopyToVRAM(&param0->windows[2]);

        BoxSelectionPopup_LoadItemIcon(param0, v1);

        v0->state = 0;
        v0->boxSelectionPopup = param0;
        v0->bgConfig = param0->bgConfig;
        v0->offset = (0 << FX32_SHIFT);
        v0->targetOffset = 56 << FX32_SHIFT;
        v0->offsetStep = (v0->targetOffset - v0->offset) / 6;
        v0->stepCount = 6;

        param0->task = BoxGraphics_StartVBlankTask(BoxSelectionPopup_ShowItemInfoTask, v0, 0);
    }
}

BOOL BoxSelectionPopup_IsItemInfoDone(BoxSelectionPopup *param0)
{
    return param0->task == NULL;
}

static void BoxSelectionPopup_ItemInfoDone(void *param0)
{
    BoxSelectionPopup *v0 = param0;
    v0->task = NULL;
}

static void BoxSelectionPopup_ShowItemInfoTask(SysTask *param0, void *param1)
{
    BoxSelectionPopupItemAnim *v0 = param1;

    switch (v0->state) {
    case 0:
        v0->state++;
        break;
    case 1:
        if (v0->stepCount) {
            v0->stepCount--;
            v0->offset += v0->offsetStep;
            Bg_SetOffset(v0->bgConfig, BG_LAYER_MAIN_1, 3, (v0->offset >> FX32_SHIFT));
            BoxSelectionPopup_SetItemIconY(v0->boxSelectionPopup, (224 << FX32_SHIFT) - v0->offset);
        } else {
            Bg_SetOffset(v0->bgConfig, BG_LAYER_MAIN_1, 3, (v0->targetOffset >> FX32_SHIFT));
            BoxSelectionPopup_SetItemIconY(v0->boxSelectionPopup, (224 << FX32_SHIFT) - v0->targetOffset);
            BoxGraphics_DeferFree(v0, BoxSelectionPopup_ItemInfoDone, v0->boxSelectionPopup);
            SysTask_Done(param0);
        }
        break;
    }
}

void BoxSelectionPopup_HideItemInfo(BoxSelectionPopup *param0)
{
    BoxSelectionPopupItemAnim *v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxSelectionPopupItemAnim));

    if (v0) {
        v0->state = 0;
        v0->boxSelectionPopup = param0;
        v0->bgConfig = param0->bgConfig;
        v0->offset = 56 << FX32_SHIFT;
        v0->targetOffset = 0 << FX32_SHIFT;
        v0->offsetStep = (v0->targetOffset - v0->offset) / 6;
        v0->stepCount = 6;
        param0->task = BoxGraphics_StartVBlankTask(BoxSelectionPopup_HideItemInfoTask, v0, 0);
    }
}

BOOL BoxSelectionPopup_IsHideItemInfoDone(BoxSelectionPopup *param0)
{
    if (param0->task == NULL) {
        Bg_SetOffset(param0->bgConfig, BG_LAYER_MAIN_1, 3, 0);
        BoxSelectionPopup_DeleteItemIcon(param0);
        return 1;
    }

    return 0;
}

static void BoxSelectionPopup_HideItemInfoDone(void *param0)
{
    BoxSelectionPopup *v0 = param0;
    v0->task = NULL;
}

static void BoxSelectionPopup_HideItemInfoTask(SysTask *param0, void *param1)
{
    BoxSelectionPopupItemAnim *v0 = param1;

    if (v0->stepCount) {
        v0->stepCount--;
        v0->offset += v0->offsetStep;
        Bg_SetOffset(v0->bgConfig, BG_LAYER_MAIN_1, 3, (v0->offset >> FX32_SHIFT));
        BoxSelectionPopup_SetItemIconY(v0->boxSelectionPopup, (224 << FX32_SHIFT) - v0->offset);
    } else {
        Bg_SetOffset(v0->bgConfig, BG_LAYER_MAIN_1, 3, (v0->targetOffset >> FX32_SHIFT));
        BoxSelectionPopup_SetItemIconY(v0->boxSelectionPopup, (224 << FX32_SHIFT) - v0->targetOffset);
        Bg_FillTilemapRect(v0->bgConfig, 1, 0x0, 0, 0, 32, 32, 17);
        Bg_CopyTilemapBufferToVRAM(v0->bgConfig, 1);
        BoxGraphics_DeferFree(v0, BoxSelectionPopup_HideItemInfoDone, v0->boxSelectionPopup);
        SysTask_Done(param0);
    }
}

static void BoxSelectionPopup_LoadItemIcon(BoxSelectionPopup *param0, u32 param1)
{
    if (param1 != 0) {
        SpriteResourcesHeader v0;
        BoxMonSpriteManager *v1;
        NNSG2dImageProxy v2;
        NNSG2dCharacterData *v3;
        void *v4;

        v1 = BoxGraphics_GetBoxMonSpriteManager(param0->boxGraphics);
        BoxGraphics_InitSpriteResources(&v0, &v2, BoxGraphics_GetPaletteProxy(param0->boxGraphics), v1->formCellBankData, v1->formAnimBankData, 0);
        NNS_G2dInitImageProxy(&v2);

        v4 = Graphics_GetCharData(NARC_INDEX_ITEMTOOL__ITEMDATA__ITEM_ICON, Item_FileID(param1, 1), 0, &v3, HEAP_ID_BOX_GRAPHICS);
        v3->mappingType = GX_GetOBJVRamModeChar();
        NNS_G2dLoadImage1DMapping(v3, 1520 * 0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &v2);

        Graphics_LoadPalette(NARC_INDEX_ITEMTOOL__ITEMDATA__ITEM_ICON, Item_FileID(param1, 2), 1, 6 * 0x20, 0x20, HEAP_ID_BOX_GRAPHICS);
        param0->monIconSprite = BoxGraphics_CreateSprite(param0->spriteList, &v0, 18, 224, 0, NNS_G2D_VRAM_TYPE_2DMAIN);

        if (param0->monIconSprite) {
            Sprite_SetExplicitPalette(param0->monIconSprite, 6);
        }

        Heap_Free(v4);
    }
}

static void BoxSelectionPopup_SetItemIconY(BoxSelectionPopup *param0, fx32 param1)
{
    if (param0->monIconSprite) {
        VecFx32 v0;

        v0.x = 18 << FX32_SHIFT;
        v0.y = param1;
        v0.z = 0;

        Sprite_SetPosition(param0->monIconSprite, &v0);
    }
}

static void BoxSelectionPopup_DeleteItemIcon(BoxSelectionPopup *param0)
{
    if (param0->monIconSprite) {
        Sprite_Delete(param0->monIconSprite);
    }
}
