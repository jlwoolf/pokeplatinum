#include "applications/pc_boxes/pc_compare_screen.h"

#include <nitro.h>
#include <string.h>

#include "generated/pokemon_contest_types.h"

#include "applications/pc_boxes/box_app_manager.h"
#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics.h"
#include "applications/pc_boxes/box_mon_sprite_manager.h"
#include "applications/pc_boxes/pc_compare_mon.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_mon_sprite_manager.h"
#include "applications/pc_boxes/struct_pc_compare_screen_decl.h"

#include "bg_window.h"
#include "font.h"
#include "graphics.h"
#include "heap.h"
#include "inlines.h"
#include "message.h"
#include "narc.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "sprite.h"
#include "string_gf.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "text.h"

#include "res/text/bank/box_messages.h"

struct PCCompareScreen_t {
    BOOL unk_00;
    BoxGraphics *unk_04;
    const BoxApplication *unk_08;
    BgConfig *unk_0C;
    SpriteList *unk_10;
    BoxMonSpriteManager *unk_14;
    u32 unk_18[2];
    Sprite *unk_20[2];
    Sprite *unk_28[2];
    Sprite *unk_30;
    Sprite *unk_34[2][5];
    void *unk_5C;
    NNSG2dCellDataBank *unk_60;
    void *unk_64;
    NNSG2dAnimBankData *unk_68;
    MessageLoader *unk_6C;
    MessageLoader *unk_70;
    String *boxDisplayText;
    Window unk_78[7];
    u8 unk_E8[640];
    NNSG2dScreenData *unk_368;
    NNSG2dScreenData *unk_36C;
    void *unk_370;
    void *unk_374;
    enum CompareMode unk_378;
    int unk_37C;
    SysTask *unk_380;
};

static void PCCompare_DrawMonBackground(PCCompareScreen *param0);
static void PCCompare_ShowModeLayers(PCCompareScreen *param0);
static void PCCompare_InitWindows(PCCompareScreen *param0);
static void PCCompare_RemoveWindows(PCCompareScreen *param0);
static void PCCompare_DrawCurrentMode(PCCompareScreen *param0);
static void PCCompare_HideModeLayers(PCCompareScreen *param0, int param1);
static void PCCompare_AddBattleStatWindows(PCCompareScreen *param0);
static void PCCompare_RemoveBattleStatWindows(PCCompareScreen *param0);
static void PCCompare_DrawContestStats(PCCompareScreen *param0, int param1);
static void PCCompare_HideContestSprites(PCCompareScreen *param0, int param1);
static void PCCompare_AddMoveWindows(PCCompareScreen *param0);
static void PCCompare_RemoveMoveWindows(PCCompareScreen *param0);
static inline u32 inline_PCCompare_CenterTextX(Window *param0, u32 param1, const String *param2);
static void PCCompare_DrawStatLabels(PCCompareScreen *param0);
static void PCCompare_ClearStatLabels(PCCompareScreen *param0);
static void PCCompare_DrawBattleStats(PCCompareScreen *param0, int param1);
static void PCCompare_DrawMoves(PCCompareScreen *param0, int param1);
static void PCCompare_LoadMonSprites(PCCompareScreen *param0, NARC *param1);
static void PCCompare_LoadCompareSprites(PCCompareScreen *param0, u32 param1);
static void PCCompare_DeleteSprites(PCCompareScreen *param0);
static void PCCompare_DrawMonIcon(PCCompareScreen *param0);
static void PCCompare_DrawMonName(PCCompareScreen *param0, int param1);
static void PCCompare_ButtonAnimTask(SysTask *param0, void *param1);

BOOL PCCompare_Load(PCCompareScreen **param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4, MessageLoader *param5, NARC *param6)
{
    if (BoxApp_GetBoxMode(param2) != PC_MODE_COMPARE) {
        *param0 = NULL;
        return 1;
    } else {
        PCCompareScreen *v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(PCCompareScreen));

        if (v0) {
            v0->unk_04 = param1;
            v0->unk_08 = param2;
            v0->unk_0C = param3;
            v0->unk_10 = param4;
            v0->unk_14 = BoxGraphics_GetBoxMonSpriteManager(param1);
            v0->unk_370 = Graphics_GetScrnDataFromOpenNARC(param6, 7, 1, &(v0->unk_368), HEAP_ID_BOX_GRAPHICS);
            v0->unk_374 = Graphics_GetScrnDataFromOpenNARC(param6, 8, 1, &(v0->unk_36C), HEAP_ID_BOX_GRAPHICS);
            v0->unk_6C = param5;
            v0->unk_70 = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_MOVE_NAMES, HEAP_ID_BOX_GRAPHICS);
            v0->boxDisplayText = String_Init(32, HEAP_ID_BOX_GRAPHICS);
            v0->unk_380 = NULL;
            *param0 = v0;
            return 1;
        }

        return 0;
    }
}

void PCCompare_Free(PCCompareScreen *param0)
{
    if (param0) {
        Heap_Free(param0->unk_370);
        Heap_Free(param0->unk_374);
        MessageLoader_Free(param0->unk_70);
        PCCompare_DeleteSprites(param0);
        PCCompare_RemoveWindows(param0);
        String_Free(param0->boxDisplayText);
        Heap_Free(param0);
    }
}

void PCCompare_Init(PCCompareScreen *param0, NARC *param1)
{
    if (param0) {
        PCCompare_DrawMonBackground(param0);

        Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 132, param0->unk_0C, 5, 0, 0, 1, HEAP_ID_BOX_GRAPHICS);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 129, param0->unk_0C, 5, 0, 0, 1, HEAP_ID_BOX_GRAPHICS);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 130, param0->unk_0C, 6, 0, 0, 1, HEAP_ID_BOX_GRAPHICS);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 131, param0->unk_0C, 7, 0, 0, 1, HEAP_ID_BOX_GRAPHICS);
        Graphics_LoadPaletteFromOpenNARC(param1, 133, 4, 0, 0x20 * 4, HEAP_ID_BOX_GRAPHICS);
        Graphics_LoadPalette(NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, PokeIconPalettesFileIndex(), 5, 4 * 0x20, 4 * 0x20, HEAP_ID_BOX_GRAPHICS);
        Bg_ClearTilesRange(4, 0x20, 0, HEAP_ID_BOX_GRAPHICS);
        Bg_FillTilemapRect(param0->unk_0C, 4, 0x0, 0, 0, 32, 32, 17);

        PCCompare_ShowModeLayers(param0);
        PCCompare_InitWindows(param0);

        param0->unk_378 = BoxApp_GetCompareMode(param0->unk_08);

        Bg_CopyTilemapBufferToVRAM(param0->unk_0C, 4);
        PCCompare_LoadMonSprites(param0, param1);
    }
}

void PCCompare_SetButtonState(PCCompareScreen *param0, BOOL param1)
{
    if (param0) {
        int v0 = BoxApp_GetCompareMonSlot(param0->unk_08);

        if (param1) {
            Sprite_SetAnim(param0->unk_28[v0 ^ 1], 2);
            Sprite_SetAnim(param0->unk_28[v0], 0);
        } else {
            Sprite_SetAnim(param0->unk_28[v0 ^ 1], 1);
            Sprite_SetAnim(param0->unk_28[v0], 0);
        }

        PCCompare_DrawMonBackground(param0);
    }
}

void PCCompare_DrawMonInfo(PCCompareScreen *param0)
{
    PCCompare_DrawMonIcon(param0);

    if (param0) {
        int compareMonSlot = BoxApp_GetCompareMonSlot(param0->unk_08);

        PCCompare_DrawMonName(param0, compareMonSlot);

        switch (BoxApp_GetCompareMode(param0->unk_08)) {
        case COMPARE_BATTLE_STATS:
            PCCompare_DrawBattleStats(param0, compareMonSlot);
            break;
        case COMPARE_CONTEST_STATS:
            PCCompare_DrawContestStats(param0, compareMonSlot);
            break;
        case COMPARE_MOVES:
            PCCompare_DrawMoves(param0, compareMonSlot);
            break;
        }
    }
}

BOOL PCCompare_IsDrawDone(PCCompareScreen *param0)
{
    return 1;
}

void PCCompare_StartModeSwitch(PCCompareScreen *param0)
{
    if (param0) {
        param0->unk_37C = 0;
        PCCompare_HideModeLayers(param0, param0->unk_378);
        Bg_CopyTilemapBufferToVRAM(param0->unk_0C, 4);
    }
}

BOOL PCCompare_UpdateModeSwitch(PCCompareScreen *param0)
{
    if (param0) {
        switch (param0->unk_37C) {
        case 0:
            PCCompare_ShowModeLayers(param0);
            param0->unk_37C++;
            break;
        case 1:
            PCCompare_DrawStatLabels(param0);
            PCCompare_DrawCurrentMode(param0);
            Bg_CopyTilemapBufferToVRAM(param0->unk_0C, 4);
            param0->unk_37C++;
            break;
        case 2:
            return 1;
        }
        return 0;
    } else {
        return 1;
    }
}

static void PCCompare_DrawMonBackground(PCCompareScreen *param0)
{
    NNSG2dScreenData *v0 = (BoxApp_GetCompareMonSlot(param0->unk_08) == 0) ? param0->unk_368 : param0->unk_36C;

    Bg_CopyToTilemapRect(param0->unk_0C, 2, 0, 0, 6, 32, v0->rawData, 0, 0, 32, 32);
    Bg_CopyToTilemapRect(param0->unk_0C, 2, 26, 0, 6, 32, v0->rawData, 26, 0, 32, 32);
    Bg_CopyTilemapBufferToVRAM(param0->unk_0C, 2);
}

static void PCCompare_ShowModeLayers(PCCompareScreen *param0)
{
    switch (BoxApp_GetCompareMode(param0->unk_08)) {
    case COMPARE_BATTLE_STATS:
        Bg_ToggleLayer(BG_LAYER_SUB_1, 1);
        Bg_ToggleLayer(BG_LAYER_SUB_2, 0);
        Bg_ToggleLayer(BG_LAYER_SUB_3, 0);
        break;
    case COMPARE_CONTEST_STATS:
        Bg_ToggleLayer(BG_LAYER_SUB_2, 1);
        Bg_ToggleLayer(BG_LAYER_SUB_1, 0);
        Bg_ToggleLayer(BG_LAYER_SUB_3, 0);
        break;
    case COMPARE_MOVES:
        Bg_ToggleLayer(BG_LAYER_SUB_3, 1);
        Bg_ToggleLayer(BG_LAYER_SUB_1, 0);
        Bg_ToggleLayer(BG_LAYER_SUB_2, 0);
        break;
    }
}

static void PCCompare_InitWindows(PCCompareScreen *param0)
{
    static const WindowTemplate v0[] = {
        { 4, 3, 1, 9, 2, 0, 1 },
        { 4, 20, 1, 9, 2, 1, 19 },
        { 4, 13, 4, 6, 16, 0, 37 }
    };
    int v1;

    for (v1 = 0; v1 < 7; v1++) {
        param0->unk_78[v1].pixels = NULL;
    }

    for (v1 = 0; v1 < NELEMS(v0); v1++) {
        Window_AddFromTemplate(param0->unk_0C, &param0->unk_78[0 + v1], &v0[v1]);
        Window_PutToTilemap(&param0->unk_78[0 + v1]);
    }

    PCCompare_DrawStatLabels(param0);
    Window_FillTilemap(&param0->unk_78[0], 0);
    Window_FillTilemap(&param0->unk_78[1], 0);

    for (v1 = 0; v1 < NELEMS(v0); v1++) {
        Window_LoadTiles(&param0->unk_78[0 + v1]);
    }

    PCCompare_DrawCurrentMode(param0);
}

static void PCCompare_RemoveWindows(PCCompareScreen *param0)
{
    int v0;

    for (v0 = 0; v0 < 7; v0++) {
        if (param0->unk_78[v0].pixels) {
            Window_Remove(&(param0->unk_78[v0]));
        }
    }
}

static void PCCompare_DrawCurrentMode(PCCompareScreen *param0)
{
    int v0 = BoxApp_GetCompareMode(param0->unk_08);

    switch (BoxApp_GetCompareMode(param0->unk_08)) {
    case COMPARE_BATTLE_STATS:
        PCCompare_AddBattleStatWindows(param0);
        PCCompare_DrawBattleStats(param0, 0);
        PCCompare_DrawBattleStats(param0, 1);
        break;
    case COMPARE_CONTEST_STATS:
        PCCompare_DrawContestStats(param0, 0);
        PCCompare_DrawContestStats(param0, 1);
        break;
    case COMPARE_MOVES:
        PCCompare_AddMoveWindows(param0);
        PCCompare_DrawMoves(param0, 0);
        PCCompare_DrawMoves(param0, 1);
        break;
    }

    param0->unk_378 = v0;
}

static void PCCompare_HideModeLayers(PCCompareScreen *param0, int param1)
{
    switch (param1) {
    case 0:
        PCCompare_RemoveBattleStatWindows(param0);
        PCCompare_ClearStatLabels(param0);
        break;
    case 1:
        PCCompare_HideContestSprites(param0, 0);
        PCCompare_HideContestSprites(param0, 1);
        break;
    case 2:
        PCCompare_RemoveMoveWindows(param0);
        PCCompare_ClearStatLabels(param0);
        break;
    }
}

static void PCCompare_AddBattleStatWindows(PCCompareScreen *param0)
{
    static const WindowTemplate v0[] = {
        { 4, 3, 4, 9, 16, 0, 133 },
        { 4, 20, 4, 9, 16, 1, 277 }
    };
    int v1;

    for (v1 = 0; v1 < NELEMS(v0); v1++) {
        Window_AddFromTemplate(param0->unk_0C, &param0->unk_78[3 + v1], &v0[v1]);
        Window_PutToTilemap(&param0->unk_78[3 + v1]);
        Window_FillTilemap(&param0->unk_78[3 + v1], 0);
    }
}

static void PCCompare_RemoveBattleStatWindows(PCCompareScreen *param0)
{
    int v0;

    for (v0 = 3; v0 <= 4; v0++) {
        if (param0->unk_78[v0].pixels) {
            Window_ClearTilemap(&(param0->unk_78[v0]));
            Window_Remove(&(param0->unk_78[v0]));
            param0->unk_78[v0].pixels = NULL;
        }
    }
}

static void PCCompare_DrawContestStats(PCCompareScreen *param0, int compareMonSlot)
{
#define DEFINE_00(tx) ((128 << FX32_SHIFT) + (((((tx) - 128) << FX32_SHIFT) * 10) / 100))
#define DEFINE_01(ty) ((484 << FX32_SHIFT) + (((((ty) - 484) << FX32_SHIFT) * 10) / 100))

    static const struct {
        fx32 unk_00;
        fx32 unk_04;
        fx32 unk_08;
        fx32 unk_0C;
    } v0[] = {
        { DEFINE_00(128), DEFINE_01(438), 128 << FX32_SHIFT, 438 << FX32_SHIFT },
        { DEFINE_00(172), DEFINE_01(470), 172 << FX32_SHIFT, 470 << FX32_SHIFT },
        { DEFINE_00(155), DEFINE_01(520), 155 << FX32_SHIFT, 520 << FX32_SHIFT },
        { DEFINE_00(100), DEFINE_01(520), 100 << FX32_SHIFT, 520 << FX32_SHIFT },
        { DEFINE_00(84), DEFINE_01(470), 84 << FX32_SHIFT, 470 << FX32_SHIFT },
    };

    const PCCompareMon *compareMon;
    BOOL isMonUnderCursor, v3, v4;

    compareMon = BoxApp_GetCompareMonFrom(param0->unk_08, compareMonSlot);
    isMonUnderCursor = BoxApp_IsMonUnderCursor(param0->unk_08);
    v3 = BoxApp_GetCompareMonSlot(param0->unk_08) == compareMonSlot;
    v4 = BoxApp_CompareSlotHasMon(param0->unk_08, compareMonSlot);

    if ((((isMonUnderCursor == TRUE) && (v3 == 1)) || ((v3 == 0) && (v4 == 1))) && (compareMon->isEgg == FALSE)) {
        int i;
        VecFx32 v6;
        const u16 *contestStat = &compareMon->cool;

        v6.z = 0;

        for (i = 0; i < CONTEST_TYPE_MAX; i++) {
            v6.x = v0[i].unk_00 + (((v0[i].unk_08 - v0[i].unk_00) / 256) * (int)(*contestStat));
            v6.y = v0[i].unk_04 + (((v0[i].unk_0C - v0[i].unk_04) / 256) * (int)(*contestStat));
            Sprite_SetPosition(param0->unk_34[compareMonSlot][i], &v6);
            BoxGraphics_SetSpritePriority(param0->unk_34[compareMonSlot][i], 0);
            BoxGraphics_SetSpritePriority(param0->unk_34[compareMonSlot ^ 1][i], 1);
            Sprite_SetDrawFlag(param0->unk_34[compareMonSlot][i], TRUE);
            contestStat++;
        }
    } else {
        PCCompare_HideContestSprites(param0, compareMonSlot);
    }

#undef DEFINE_00
#undef DEFINE_01
}

static void PCCompare_HideContestSprites(PCCompareScreen *param0, int compareMonSlot)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        Sprite_SetDrawFlag(param0->unk_34[compareMonSlot][v0], FALSE);
    }
}

static void PCCompare_AddMoveWindows(PCCompareScreen *param0)
{
    static const WindowTemplate v0[] = {
        { 4, 1, 4, 11, 12, 0, 133 },
        { 4, 20, 4, 11, 12, 1, 265 }
    };
    int v1;

    for (v1 = 0; v1 < NELEMS(v0); v1++) {
        Window_AddFromTemplate(param0->unk_0C, &param0->unk_78[5 + v1], &v0[v1]);
        Window_PutToTilemap(&param0->unk_78[5 + v1]);
        Window_FillTilemap(&param0->unk_78[5 + v1], 0);
    }
}

static void PCCompare_RemoveMoveWindows(PCCompareScreen *param0)
{
    int v0;

    for (v0 = 5; v0 <= 6; v0++) {
        if (param0->unk_78[v0].pixels) {
            Window_ClearTilemap(&(param0->unk_78[v0]));
            Window_Remove(&(param0->unk_78[v0]));
            param0->unk_78[v0].pixels = NULL;
        }
    }
}

static inline u32 inline_PCCompare_CenterTextX(Window *param0, u32 param1, const String *param2)
{
    return ((param0->width * 8) - Font_CalcStringWidth(param1, param2, 0)) / 2;
}

static void PCCompare_DrawStatLabels(PCCompareScreen *param0)
{
    static const u16 compareMessages[] = {
        BoxText_Nature,
        BoxText_Level,
        BoxText_HP,
        BoxText_Attack,
        BoxText_Defense,
        BoxText_SpecialAttack,
        BoxText_SpecialDefense,
        BoxText_Speed,
    };
    Window *v1 = &param0->unk_78[2];
    int v2;

    Window_FillTilemap(v1, 0);

    switch (BoxApp_GetCompareMode(param0->unk_08)) {
    case COMPARE_BATTLE_STATS:
        for (v2 = 0; v2 < NELEMS(compareMessages); v2++) {
            MessageLoader_GetString(param0->unk_6C, compareMessages[v2], param0->boxDisplayText);
            Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, param0->boxDisplayText, inline_PCCompare_CenterTextX(v1, 0, param0->boxDisplayText), 0 + 16 * v2, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
        }
        break;
    case COMPARE_MOVES:
        MessageLoader_GetString(param0->unk_6C, BoxText_Move, param0->boxDisplayText);
        Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, param0->boxDisplayText, inline_PCCompare_CenterTextX(v1, 0, param0->boxDisplayText), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
        break;
    }

    Window_LoadTiles(v1);
}

static void PCCompare_ClearStatLabels(PCCompareScreen *param0)
{
    Window *v0 = &param0->unk_78[2];

    Window_FillTilemap(v0, 0);
    Window_LoadTiles(v0);
}

static void PCCompare_DrawBattleStats(PCCompareScreen *param0, int compareMonSlot)
{
    Window *window;
    const PCCompareMon *compareMon;
    BOOL isMonUnderCursor, compareSlot, v4;

    window = &(param0->unk_78[3 + compareMonSlot]);
    compareMon = BoxApp_GetCompareMonFrom(param0->unk_08, compareMonSlot);
    isMonUnderCursor = BoxApp_IsMonUnderCursor(param0->unk_08);
    compareSlot = BoxApp_GetCompareMonSlot(param0->unk_08) == compareMonSlot;
    v4 = BoxApp_CompareSlotHasMon(param0->unk_08, compareMonSlot);

    Window_FillTilemap(window, 0);

    if (((isMonUnderCursor == TRUE) && (compareSlot == 1)) || ((compareSlot == 0) && (v4 == 1))) {
        int v5;

        if (compareMon->isEgg == FALSE) {
            const u16 *v6 = &compareMon->level;

            Text_AddPrinterWithParamsAndColor(window, FONT_SYSTEM, compareMon->nature, inline_PCCompare_CenterTextX(window, 0, compareMon->nature), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);

            for (v5 = 0; v5 < 7; v5++) {
                String_FormatInt(param0->boxDisplayText, v6[v5], 3, 0, 1);
                Text_AddPrinterWithParamsAndColor(window, FONT_SYSTEM, param0->boxDisplayText, inline_PCCompare_CenterTextX(window, 0, param0->boxDisplayText), (1 + v5) * 16, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
            }
        } else {
            MessageLoader_GetString(param0->unk_6C, 44, param0->boxDisplayText);

            for (v5 = 0; v5 < 8; v5++) {
                Text_AddPrinterWithParamsAndColor(window, FONT_SYSTEM, param0->boxDisplayText, inline_PCCompare_CenterTextX(window, 0, param0->boxDisplayText), v5 * 16, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
            }
        }
    }

    Window_LoadTiles(window);
}

static void PCCompare_DrawMoves(PCCompareScreen *param0, int compareMonSlot)
{
    Window *v0;
    const PCCompareMon *compareMon;
    BOOL isMonUnderCursor, v3, v4;

    v0 = &(param0->unk_78[5 + compareMonSlot]);
    compareMon = BoxApp_GetCompareMonFrom(param0->unk_08, compareMonSlot);
    isMonUnderCursor = BoxApp_IsMonUnderCursor(param0->unk_08);
    v3 = BoxApp_GetCompareMonSlot(param0->unk_08) == compareMonSlot;
    v4 = BoxApp_CompareSlotHasMon(param0->unk_08, compareMonSlot);

    Window_FillTilemap(v0, 0);

    if (((isMonUnderCursor == TRUE) && (v3 == 1)) || ((v3 == 0) && (v4 == 1))) {
        int i;

        if (compareMon->isEgg == FALSE) {
            for (i = 0; i < LEARNED_MOVES_MAX; i++) {
                if (compareMon->moves[i]) {
                    MessageLoader_GetString(param0->unk_70, compareMon->moves[i], param0->boxDisplayText);
                    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, param0->boxDisplayText, inline_PCCompare_CenterTextX(v0, 0, param0->boxDisplayText), 4 + 24 * i, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
                }
            }
        } else {
            MessageLoader_GetString(param0->unk_6C, 44, param0->boxDisplayText);

            for (i = 0; i < 4; i++) {
                Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, param0->boxDisplayText, inline_PCCompare_CenterTextX(v0, 0, param0->boxDisplayText), 4 + 24 * i, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
            }
        }
    }

    Window_LoadTiles(v0);
}

static void PCCompare_LoadMonSprites(PCCompareScreen *param0, NARC *param1)
{
    static const struct {
        s16 unk_00;
        s16 unk_02;
    } v0[] = {
        { 0, 568 },
        { 256, 568 },
    };
    NNSG2dImageProxy v1;
    SpriteResourcesHeader v2;
    u32 v3, v4, v5;

    param0->unk_5C = Graphics_GetCellBankFromOpenNARC(param1, 135, 1, &(param0->unk_60), HEAP_ID_BOX_GRAPHICS);
    param0->unk_64 = Graphics_GetAnimBankFromOpenNARC(param1, 136, 1, &(param0->unk_68), HEAP_ID_BOX_GRAPHICS);

    Graphics_LoadPaletteFromOpenNARC(param1, 137, 5, 0, 0x20 * 3, HEAP_ID_BOX_GRAPHICS);
    NNS_G2dInitImageProxy(&v1);
    v3 = Graphics_LoadImageMappingFromOpenNARC(param1, 134, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DSUB, 0, 10, &v1);
    BoxGraphics_InitSpriteResources(&v2, &v1, BoxGraphics_GetPaletteProxy(param0->unk_04), param0->unk_60, param0->unk_68, 1);

    for (v4 = 0; v4 < 2; v4++) {
        param0->unk_28[v4] = BoxGraphics_CreateSprite(param0->unk_10, &v2, v0[v4].unk_00, v0[v4].unk_02, 0, NNS_G2D_VRAM_TYPE_2DSUB);

        Sprite_SetExplicitPalette(param0->unk_28[v4], v4);
        Sprite_SetAnim(param0->unk_28[v4], 0);

        for (v5 = 0; v5 < 5; v5++) {
            param0->unk_34[v4][v5] = BoxGraphics_CreateSprite(param0->unk_10, &v2, 0, 0, 0, NNS_G2D_VRAM_TYPE_2DSUB);
            Sprite_SetAnim(param0->unk_34[v4][v5], 5 + v4);
            Sprite_SetExplicitPalette(param0->unk_34[v4][v5], v4);
            Sprite_SetDrawFlag(param0->unk_34[v4][v5], FALSE);
        }
    }

    Sprite_SetFlipMode(param0->unk_28[1], 1);
    param0->unk_30 = BoxGraphics_CreateSprite(param0->unk_10, &v2, 128, 176 + 384, 0, NNS_G2D_VRAM_TYPE_2DSUB);
    Sprite_SetAnim(param0->unk_30, 3);
    Sprite_SetExplicitPalette(param0->unk_30, 2);
    param0->unk_380 = SysTask_Start(PCCompare_ButtonAnimTask, param0, 1);

    PCCompare_LoadCompareSprites(param0, v3);
}

static void PCCompare_LoadCompareSprites(PCCompareScreen *param0, u32 param1)
{
    static const struct {
        s16 unk_00;
        s16 unk_02;
    } v0[] = {
        { 112, 394 },
        { 144, 394 },
    };
    NNSG2dImageProxy v1;
    SpriteResourcesHeader v2;

    BoxGraphics_InitSpriteResources(&v2, &v1, BoxGraphics_GetPaletteProxy(param0->unk_04), BoxMonSprite_GetCellBank(param0->unk_14), BoxMonSprite_GetAnimBank(param0->unk_14), 1);

    for (int i = 0; i < 2; i++) {
        param0->unk_18[i] = param1 + (i * (4 * 4) * 0x20);
        NNS_G2dInitImageProxy(&v1);
        NNS_G2dSetImageLocation(&v1, NNS_G2D_VRAM_TYPE_2DSUB, param0->unk_18[i]);
        v1.attr.mappingType = GXS_GetOBJVRamModeChar();
        param0->unk_20[i] = BoxGraphics_CreateSprite(param0->unk_10, &v2, v0[i].unk_00, v0[i].unk_02, 1 - i, NNS_G2D_VRAM_TYPE_2DSUB);
        Sprite_SetDrawFlag(param0->unk_20[i], FALSE);
    }
}

static void PCCompare_DeleteSprites(PCCompareScreen *param0)
{
    int v0, v1;

    if (param0->unk_380) {
        SysTask_Done(param0->unk_380);
    }

    for (v0 = 0; v0 < 2; v0++) {
        Sprite_Delete(param0->unk_20[v0]);
        Sprite_Delete(param0->unk_28[v0]);

        for (v1 = 0; v1 < 5; v1++) {
            Sprite_Delete(param0->unk_34[v0][v1]);
        }
    }

    Sprite_Delete(param0->unk_30);
    Heap_Free(param0->unk_5C);
    Heap_Free(param0->unk_64);
}

static void PCCompare_DrawMonIcon(PCCompareScreen *param0)
{
    int compareMonSlot = BoxApp_GetCompareMonSlot(param0->unk_08);
    const PCCompareMon *compareMon = BoxApp_GetCompareMonFrom(param0->unk_08, compareMonSlot);
    Sprite *v2 = param0->unk_20[compareMonSlot];
    BoxPokemon *boxMon = compareMon->mon;
    NNSG2dCharacterData *v4;

    if (BoxApp_IsMonUnderCursor(param0->unk_08)) {
        u32 v5 = 4 + PokeIconPaletteIndex(compareMon->species, compareMon->form, compareMon->isEgg);

        BoxMonSprite_ReadIcon(param0->unk_14, param0->unk_E8, BoxPokemon_IconSpriteIndex(boxMon), sizeof(param0->unk_E8));

        NNS_G2dGetUnpackedCharacterData(param0->unk_E8, &v4);
        DC_FlushRange(v4->pRawData, (4 * 4) * 0x20);
        GXS_LoadOBJ(v4->pRawData, param0->unk_18[compareMonSlot], (4 * 4) * 0x20);

        Sprite_SetExplicitPalette(v2, v5);
        Sprite_SetDrawFlag(v2, TRUE);
    } else {
        Sprite_SetDrawFlag(v2, FALSE);
    }
}

static void PCCompare_DrawMonName(PCCompareScreen *param0, int compareMonSlot)
{
    Window *window;

    compareMonSlot = BoxApp_GetCompareMonSlot(param0->unk_08);
    window = &(param0->unk_78[0 + compareMonSlot]);

    Window_FillTilemap(window, 0);

    if (BoxApp_IsMonUnderCursor(param0->unk_08)) {
        const PCCompareMon *compareMon = BoxApp_GetCompareMonFrom(param0->unk_08, compareMonSlot);
        Text_AddPrinterWithParamsAndColor(window, FONT_SYSTEM, compareMon->monName, inline_PCCompare_CenterTextX(window, 0, compareMon->monName), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    }

    Window_LoadTiles(window);
}

static void PCCompare_ButtonAnimTask(SysTask *param0, void *param1)
{
    PCCompareScreen *v0 = param1;
    BOOL pressedAnimation = BoxApp_IsCompareButtonPressed(v0->unk_08);

    if (Sprite_GetActiveAnim(v0->unk_30) == 3) {
        if (pressedAnimation) {
            Sprite_SetAnim(v0->unk_30, 4);
        }
    } else {
        if (pressedAnimation == FALSE) {
            Sprite_SetAnim(v0->unk_30, 3);
        }
    }
}
