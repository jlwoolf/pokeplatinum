#include "applications/pc_boxes/pc_mon_preview_panel.h"

#include <nitro.h>
#include <string.h>

#include "applications/pc_boxes/box_app_manager.h"
#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics.h"
#include "applications/pc_boxes/pc_mon_preview.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_pc_mon_preview_panel.h"

#include "bg_window.h"
#include "font_special_chars.h"
#include "graphics.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "pokemon.h"
#include "pokemon_sprite.h"
#include "sprite.h"
#include "string_gf.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "text.h"
#include "type_icon.h"

typedef struct {
    u16 state;
    u16 itemIndex;
    u16 step;
    u16 scrollY;
    PCMonPreviewPanel *panel;
} PCMonPreviewPanelItemTask;

void Window_PutRectToTilemap(Window *param0, u32 param1, u32 param2);
static void PCMonPreviewPanel_LoadTypeIcons(PCMonPreviewPanel *param0);
static void PCMonPreviewPanel_StartItemTask(PCMonPreviewPanel *param0);
static void PCMonPreviewPanel_StopItemTask(PCMonPreviewPanel *param0);
static void PCMonPreviewPanel_UpdateItemTask(PCMonPreviewPanel *param0);
static void PCMonPreviewPanel_SetItemTaskEgg(PCMonPreviewPanel *param0);
static void PCMonPreviewPanel_ItemTask(SysTask *param0, void *param1);
static void PCMonPreviewPanel_ScrollTypeIcons(PCMonPreviewPanel *param0, fx32 param1);
static void PCMonPreviewPanel_HideTypeIcons(PCMonPreviewPanel *param0);
static void PCMonPreviewPanel_DrawItemScroll(PCMonPreviewPanelItemTask *param0);
static void PCMonPreviewPanel_DrawItemField(Window *param0, PCMonPreviewPanel *param1, u32 param2, u32 param3);
static void PCMonPreviewPanel_DrawMonInfo(PCMonPreviewPanel *param0);
static void PCMonPreviewPanel_DrawMarkings(PCMonPreviewPanel *param0, u8 param1);

BOOL PCMonPreviewPanel_Load(PCMonPreviewPanel *param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4, const MessageLoader *param5, NARC *param6)
{
    int v0;

    if (BoxApp_GetBoxMode(param2) == PC_MODE_COMPARE) {
        param0->isLoaded = 0;
        return 1;
    }

    param0->boxGraphics = param1;
    param0->bgConfig = param3;
    param0->boxApp = param2;
    param0->spriteList = param4;
    param0->windows = NULL;
    param0->task = NULL;
    param0->monSprite = NULL;
    param0->pokemonSpriteManager = BoxGraphics_GetPokemonSpriteManager(param1);
    param0->dexNumFont = FontSpecialChars_Init(9, 6, 15, HEAP_ID_BOX_GRAPHICS);
    param0->levelFont = FontSpecialChars_Init(1, 2, 15, HEAP_ID_BOX_GRAPHICS);
    param0->cellBank = Graphics_GetCellBankFromOpenNARC(param6, 16, 1, &(param0->cellBankData), HEAP_ID_BOX_GRAPHICS);
    param0->infoSprite = NULL;
    param0->maleString = MessageLoader_GetNewString(param5, 21);
    param0->femaleString = MessageLoader_GetNewString(param5, 22);
    param0->typeIconBank = Graphics_GetCellBank(TypeIcon_GetNARC(), TypeIcon_GetCell(), 1, &(param0->typeIconCellBank), HEAP_ID_BOX_GRAPHICS);

    for (v0 = 0; v0 < 2; v0++) {
        param0->typeIconSprites[v0] = NULL;
    }

    param0->isLoaded = 1;

    return 1;
}

void PCMonPreviewPanel_Free(PCMonPreviewPanel *param0)
{
    int v0;

    if (param0->isLoaded == 0) {
        return;
    }

    if (param0->windows) {
        for (v0 = 0; v0 < 4; v0++) {
            Window_Remove(&param0->windows[v0]);
        }

        Heap_Free(param0->windows);
        param0->windows = NULL;
    }

    if (param0->dexNumFont) {
        FontSpecialChars_Free(param0->dexNumFont);
    }

    if (param0->levelFont) {
        FontSpecialChars_Free(param0->levelFont);
    }

    if (param0->maleString) {
        String_Free(param0->maleString);
    }

    if (param0->femaleString) {
        String_Free(param0->femaleString);
    }

    if (param0->monSprite) {
        PokemonSprite_Delete(param0->monSprite);
        param0->monSprite = NULL;
    }

    if (param0->cellBank) {
        Heap_Free(param0->cellBank);
    }

    if (param0->infoSprite) {
        Sprite_Delete(param0->infoSprite);
    }

    if (param0->typeIconBank) {
        Heap_Free(param0->typeIconBank);
    }

    for (v0 = 0; v0 < 2; v0++) {
        if (param0->typeIconSprites[v0] != NULL) {
            Sprite_Delete(param0->typeIconSprites[v0]);
        }
    }

    PCMonPreviewPanel_StopItemTask(param0);
}

void PCMonPreviewPanel_UpdateSprites(PCMonPreviewPanel *param0)
{
    if (param0->isLoaded) {
        PokemonSpriteManager_UpdateCharAndPltt(param0->pokemonSpriteManager);
    }
}

void PCMonPreviewPanel_CreateSprite(PCMonPreviewPanel *param0)
{
    PokemonSpriteTemplate v0;

    BuildPokemonSpriteTemplate(&v0, 1, 0, 0, 0, 0, 0);
    param0->monSprite = PokemonSpriteManager_CreateSprite(param0->pokemonSpriteManager, &v0, 44, 84, 0, 0, NULL, NULL);
}

BOOL PCMonPreviewPanel_DeleteSprite(PCMonPreviewPanel *param0)
{
    if (param0->monSprite) {
        PokemonSprite_Delete(param0->monSprite);
        param0->monSprite = NULL;
        return 0;
    }

    return 1;
}

void PCMonPreviewPanel_InitWindows(PCMonPreviewPanel *param0)
{
    static const WindowTemplate v0[] = {
        { 2, 0, 1, 10, 2, 1, 288 },
        { 2, 5, 3, 5, 1, 1, 308 },
        { 2, 0, 16, 10, 3, 3, 313 },
        { 2, 1, 21, 12, 4, 1, 343 }
    };

    if (param0->isLoaded == 0) {
        return;
    }

    param0->windows = Window_New(HEAP_ID_BOX_GRAPHICS, 4);

    if (param0->windows) {
        int v1;

        for (v1 = 0; v1 < 4; v1++) {
            Window_AddFromTemplate(param0->bgConfig, &param0->windows[v1], &v0[v1]);

            if (v1 != 3) {
                Window_PutToTilemap(&param0->windows[v1]);
            } else {
                Window_PutRectToTilemap(&param0->windows[v1], 12, 2);
            }
        }

        Bg_CopyTilemapBufferToVRAM(param0->bgConfig, 2);
    }

    PCMonPreviewPanel_LoadTypeIcons(param0);
    PCMonPreviewPanel_StartItemTask(param0);
}

static void PCMonPreviewPanel_LoadTypeIcons(PCMonPreviewPanel *param0)
{
    NNSG2dImageProxy v0;
    SpriteResourcesHeader v1;
    enum NarcID narcID;
    u32 v3, i;

    narcID = TypeIcon_GetNARC();
    v3 = TypeIcon_GetChar(2);

    Graphics_LoadPalette(narcID, TypeIcon_GetPlttSrc(), 1, 10 * 0x20, 0x20 * 3, HEAP_ID_BOX_GRAPHICS);

    for (i = 0; i < 2; i++) {
        NNS_G2dInitImageProxy(&v0);
        Graphics_LoadImageMappingAndSetVramMode(narcID, v3, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, (1504 + (8 * i)) * 0x20, 10, &v0);
        BoxGraphics_InitSpriteResources(&v1, &v0, BoxGraphics_GetPaletteProxy(param0->boxGraphics), param0->typeIconCellBank, NULL, 3);

        param0->typeIconSprites[i] = BoxGraphics_CreateSprite(param0->spriteList, &v1, 24 + 36 * i, 176, 46, NNS_G2D_VRAM_TYPE_2DMAIN);
        GF_ASSERT(param0->typeIconSprites[i] != NULL);

        Sprite_SetDrawFlag(param0->typeIconSprites[i], FALSE);
    }

    NNS_G2dInitImageProxy(&v0);

    Graphics_LoadImageMapping(18, 15, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 1480 * 0x20, 10, &v0);
    BoxGraphics_InitSpriteResources(&v1, &v0, BoxGraphics_GetPaletteProxy(param0->boxGraphics), param0->cellBankData, NULL, 3);

    param0->infoSprite = BoxGraphics_CreateSprite(param0->spriteList, &v1, 56, 176, 47, NNS_G2D_VRAM_TYPE_2DMAIN);
}

static void PCMonPreviewPanel_StartItemTask(PCMonPreviewPanel *param0)
{
    if (param0->task == NULL) {
        PCMonPreviewPanelItemTask *v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(PCMonPreviewPanelItemTask));

        if (v0) {
            const PCMonPreview *preview = BoxApp_GetPCMonPreview(param0->boxApp);

            v0->state = (preview->isEgg) ? 4 : 0;
            v0->panel = param0;
            param0->task = SysTask_Start(PCMonPreviewPanel_ItemTask, v0, 1);
        } else {
            GF_ASSERT(FALSE);
        }
    }
}

static void PCMonPreviewPanel_StopItemTask(PCMonPreviewPanel *param0)
{
    if (param0->task) {
        Heap_Free(SysTask_GetParam(param0->task));
        SysTask_Done(param0->task);
        param0->task = NULL;
    }
}

static void PCMonPreviewPanel_UpdateItemTask(PCMonPreviewPanel *param0)
{
    PCMonPreviewPanelItemTask *v0 = SysTask_GetParam(param0->task);

    if (v0) {
        const PCMonPreview *preview = BoxApp_GetPCMonPreview(param0->boxApp);

        v0->state = (preview->isEgg) ? 4 : 0;
        PCMonPreviewPanel_HideTypeIcons(param0);
    }
}

static void PCMonPreviewPanel_SetItemTaskEgg(PCMonPreviewPanel *param0)
{
    PCMonPreviewPanelItemTask *v0 = SysTask_GetParam(param0->task);

    if (v0) {
        v0->state = 4;
        PCMonPreviewPanel_HideTypeIcons(param0);
    }
}

static void PCMonPreviewPanel_ItemTask(SysTask *param0, void *param1)
{
    PCMonPreviewPanelItemTask *v0 = (PCMonPreviewPanelItemTask *)param1;
    PCMonPreviewPanel *v1 = v0->panel;
    const PCMonPreview *preview;

    switch (v0->state) {
    case 0:
        if (BoxApp_IsMonAvailableToCursor(v1->boxApp) == FALSE) {
            break;
        }

        v0->itemIndex = 0;
        v0->state = 1;
    case 1:
        PCMonPreviewPanel_DrawItemField(&v1->windows[3], v1, v0->itemIndex, 0);
        Window_LoadTiles(&v1->windows[3]);
        v0->step = 0;
        v0->state = 2;
        break;
    case 2:
        preview = BoxApp_GetPCMonPreview(v1->boxApp);

        if (!preview->isEgg && (++(v0->step) > 80)) {
            PCMonPreviewPanel_DrawItemScroll(v0);
            v0->step = 0;
            v0->scrollY = 0;
            v0->state = 3;
        }
        break;
    case 3:
        v0->scrollY += 4;

        PCMonPreviewPanel_ScrollTypeIcons(v1, 4 << FX32_SHIFT);
        Window_Scroll(&v1->windows[3], 0, 4, 0x0);
        Window_LoadTiles(&v1->windows[3]);

        if (v0->scrollY >= 16) {
            if (v0->itemIndex == 1) {
                PCMonPreviewPanel_HideTypeIcons(v1);
            }

            if (++(v0->itemIndex) >= 4) {
                v0->itemIndex = 0;
            }

            v0->scrollY = 0;
            v0->step = 0;
            v0->state = 2;
        }
        break;
    case 4:
        break;
    }
}

static void PCMonPreviewPanel_ScrollTypeIcons(PCMonPreviewPanel *param0, fx32 param1)
{
    int v0;
    VecFx32 v1;

    for (v0 = 0; v0 < 2; v0++) {
        v1 = *Sprite_GetPosition(param0->typeIconSprites[v0]);
        v1.y -= param1;

        Sprite_SetPosition(param0->typeIconSprites[v0], &v1);

        if ((v0 == 0) && Sprite_GetDrawFlag(param0->typeIconSprites[v0])) {
            u32 v2, v3;

            v2 = v1.x >> FX32_SHIFT;
            v3 = v1.y >> FX32_SHIFT;
        }
    }
}

static void PCMonPreviewPanel_HideTypeIcons(PCMonPreviewPanel *param0)
{
    int v0;

    for (v0 = 0; v0 < 2; v0++) {
        Sprite_SetDrawFlag(param0->typeIconSprites[v0], FALSE);
    }
}

static void PCMonPreviewPanel_DrawItemScroll(PCMonPreviewPanelItemTask *param0)
{
    u32 v0;
    Window *v1 = &(param0->panel->windows[3]);

    Window_FillTilemap(v1, 0);
    PCMonPreviewPanel_DrawItemField(v1, param0->panel, param0->itemIndex, 0);

    v0 = param0->itemIndex + 1;

    if (v0 >= 4) {
        v0 = 0;
    }

    PCMonPreviewPanel_DrawItemField(v1, param0->panel, v0, 1);
}

static void PCMonPreviewPanel_DrawItemField(Window *param0, PCMonPreviewPanel *param1, u32 param2, u32 param3)
{
    const String *v0;
    u32 v1 = (param3 * 16) + 0;

    switch (param2) {
    case 0:
        v0 = param1->boxApp->pcMonPreview.heldItemName;
        break;
    case 2:
        v0 = param1->boxApp->pcMonPreview.nature;
        break;
    case 3:
        v0 = param1->boxApp->pcMonPreview.ability;
        break;

    case 1: {
        VecFx32 v2;
        u32 v3, v4;

        v3 = TypeIcon_GetNARC();
        v4 = TypeIcon_GetChar(param1->boxApp->pcMonPreview.type1);

        Graphics_LoadObjectTiles(TypeIcon_GetNARC(), TypeIcon_GetChar(param1->boxApp->pcMonPreview.type1), 0, 1504 * 0x20, 0, 1, HEAP_ID_BOX_GRAPHICS);

        v2 = *Sprite_GetPosition(param1->typeIconSprites[0]);
        v2.y = (176 + (16 * param3)) << FX32_SHIFT;

        Sprite_SetPosition(param1->typeIconSprites[0], &v2);
        Sprite_SetExplicitPalette(param1->typeIconSprites[0], 10 + TypeIcon_GetPltt(param1->boxApp->pcMonPreview.type1));
        Sprite_SetDrawFlag(param1->typeIconSprites[0], TRUE);

        if (param1->boxApp->pcMonPreview.type1 != param1->boxApp->pcMonPreview.type2) {
            Graphics_LoadObjectTiles(TypeIcon_GetNARC(), TypeIcon_GetChar(param1->boxApp->pcMonPreview.type2), 0, (1504 + 8) * 0x20, 0, 1, HEAP_ID_BOX_GRAPHICS);

            v2.x += (36 << FX32_SHIFT);

            Sprite_SetPosition(param1->typeIconSprites[1], &v2);
            Sprite_SetExplicitPalette(param1->typeIconSprites[1], 10 + TypeIcon_GetPltt(param1->boxApp->pcMonPreview.type2));
            Sprite_SetDrawFlag(param1->typeIconSprites[1], TRUE);
        } else {
            Sprite_SetDrawFlag(param1->typeIconSprites[1], FALSE);
        }
    }
        return;
    default:
        return;
    }

    Text_AddPrinterWithParamsAndColor(param0, FONT_SYSTEM, v0, 0, v1, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(9, 6, 0), NULL);
}

void PCMonPreviewPanel_Draw(PCMonPreviewPanel *param0)
{
    if (param0->isLoaded == 0) {
        return;
    }

    Window_FillTilemap(&param0->windows[0], 15);
    Window_FillTilemap(&param0->windows[1], 15);
    Window_FillTilemap(&param0->windows[2], 15);
    Window_FillTilemap(&param0->windows[3], 0);

    if (BoxApp_IsMonAvailableToCursor(param0->boxApp)) {
        PCMonPreviewPanel_DrawMonInfo(param0);
    }

    Window_LoadTiles(&param0->windows[0]);
    Window_LoadTiles(&param0->windows[1]);
    Window_LoadTiles(&param0->windows[2]);
    Window_LoadTiles(&param0->windows[3]);
}

void PCMonPreviewPanel_DrawWithSprite(PCMonPreviewPanel *param0)
{
    if (param0->isLoaded == 0) {
        return;
    }

    Window_FillTilemap(&param0->windows[0], 15);
    Window_FillTilemap(&param0->windows[1], 15);
    Window_FillTilemap(&param0->windows[2], 15);
    Window_FillTilemap(&param0->windows[3], 0);

    if (param0->monSprite) {
        PokemonSprite_Delete(param0->monSprite);
        param0->monSprite = NULL;
    }

    if (BoxApp_IsMonAvailableToCursor(param0->boxApp)) {
        PCMonPreviewPanel_DrawMonInfo(param0);
    } else {
        PCMonPreviewPanel_DrawMarkings(param0, 0);
    }

    Window_LoadTiles(&param0->windows[0]);
    Window_LoadTiles(&param0->windows[1]);
    Window_LoadTiles(&param0->windows[2]);
    Window_LoadTiles(&param0->windows[3]);

    PCMonPreviewPanel_UpdateItemTask(param0);
}

void PCMonPreviewPanel_Hide(PCMonPreviewPanel *param0)
{
    if (param0->isLoaded == 0) {
        return;
    }

    Window_FillTilemap(&param0->windows[0], 15);
    Window_FillTilemap(&param0->windows[1], 15);
    Window_FillTilemap(&param0->windows[2], 15);
    Window_FillTilemap(&param0->windows[3], 0);

    if (param0->monSprite) {
        PokemonSprite_Delete(param0->monSprite);
        param0->monSprite = NULL;
    }

    PCMonPreviewPanel_DrawMarkings(param0, 0);

    Window_LoadTiles(&param0->windows[0]);
    Window_LoadTiles(&param0->windows[1]);
    Window_LoadTiles(&param0->windows[2]);
    Window_LoadTiles(&param0->windows[3]);

    PCMonPreviewPanel_SetItemTaskEgg(param0);
}

static void PCMonPreviewPanel_DrawMonInfo(PCMonPreviewPanel *param0)
{
    PokemonSpriteTemplate v0;
    const PCMonPreview *preview = BoxApp_GetPCMonPreview(param0->boxApp);

    Text_AddPrinterWithParamsAndColor(&param0->windows[0], FONT_SYSTEM, preview->speciesName, 2, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(9, 6, 15), NULL);
    Text_AddPrinterWithParamsAndColor(&param0->windows[2], FONT_SYSTEM, preview->nickname, 2, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
    Text_AddPrinterWithParamsAndColor(&param0->windows[2], FONT_SYSTEM, preview->nickname, 2, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);

    switch (preview->gender) {
    case 0:
        Text_AddPrinterWithParamsAndColor(&param0->windows[2], FONT_SYSTEM, param0->maleString, 70, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(7, 8, 15), NULL);
        break;
    case 1:
        Text_AddPrinterWithParamsAndColor(&param0->windows[2], FONT_SYSTEM, param0->femaleString, 70, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(3, 4, 15), NULL);
        break;
    }

    if (preview->isEgg == FALSE) {
        Text_AddPrinterWithParamsAndColor(&param0->windows[3], FONT_SYSTEM, preview->heldItemName, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(9, 6, 0), NULL);

        if (preview->dexNum) {
            FontSpecialChars_DrawPartyScreenText(param0->dexNumFont, 2, preview->dexNum, 3, 2, &(param0->windows[1]), 0, 0);
        }

        FontSpecialChars_DrawPartyScreenText(param0->levelFont, 1, preview->level, 3, 1, &(param0->windows[2]), 0, 16);
    }

    BoxPokemon_BuildSpriteTemplate(&v0, preview->mon, 2, 0);
    param0->monSprite = PokemonSpriteManager_CreateSprite(param0->pokemonSpriteManager, &v0, 44, 84, 0, 0, NULL, NULL);
    PCMonPreviewPanel_DrawMarkings(param0, preview->markings);
}

BOOL PCMonPreviewPanel_IsDrawDone(PCMonPreviewPanel *param0)
{
    if (param0->isLoaded == 0) {
        return 1;
    }

    return 1;
}

void PCMonPreviewPanel_UpdateMarkings(PCMonPreviewPanel *param0)
{
    if (param0->isLoaded == 0) {
        return;
    }

    if (BoxApp_IsMonAvailableToCursor(param0->boxApp)) {
        const PCMonPreview *preview;

        preview = BoxApp_GetPCMonPreview(param0->boxApp);
        PCMonPreviewPanel_DrawMarkings(param0, preview->markings);
    }
}

static void PCMonPreviewPanel_DrawMarkings(PCMonPreviewPanel *param0, u8 param1)
{
    u16 *v0;
    u32 v1;
    int v2;

    v1 = (19 * 32) + 4;
    v0 = Bg_GetTilemapBuffer(param0->bgConfig, 2);
    v0 += v1;

    for (v2 = 0; v2 < 6; v2++) {
        if (param1 & (1 << v2)) {
            v0[v2] = (2 << 12) | (152 + v2);
        } else {
            v0[v2] = (2 << 12) | (132 + v2);
        }
    }

    Bg_CopyTilemapBufferRangeToVRAM(param0->bgConfig, 2, v0, 6 * sizeof(u16), v1);
}

void PCMonPreviewPanel_DrawHeldItem(PCMonPreviewPanel *param0)
{
    const PCMonPreview *preview;

    if (param0->isLoaded == 0) {
        return;
    }

    preview = BoxApp_GetPCMonPreview(param0->boxApp);
    Window_FillTilemap(&param0->windows[3], 0);

    if (preview->isEgg == FALSE) {
        Text_AddPrinterWithParamsAndColor(&param0->windows[3], FONT_SYSTEM, preview->heldItemName, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(9, 6, 0), NULL);
    }

    PCMonPreviewPanel_UpdateItemTask(param0);
}
