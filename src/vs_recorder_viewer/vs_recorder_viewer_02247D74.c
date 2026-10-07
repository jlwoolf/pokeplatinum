#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_02030A80.h"
#include "struct_defs/struct_0208C06C.h"

#include "vs_recorder_viewer/vs_recorder_viewer.h"
#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_const_funcptr_tables.h"

#include "bg_window.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "palette.h"
#include "string_gf.h"
#include "string_template.h"
#include "text.h"
#include "touch_screen.h"
#include "player_profile.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    Window unk_10[2];
} VsRecorderViewerSubMenuContext;

static void VsRecorderViewerSubMenu_CreateMessageWindow(UnkStruct_0208C06C *param0, BOOL param1);
static void VsRecorderViewerSubMenu_RemoveMessageWindow(UnkStruct_0208C06C *param0);
static void VsRecorderViewerSubMenu_DrawMessage(UnkStruct_0208C06C *param0, int param1, int param2);
static void VsRecorderViewerSubMenu_CreateOptionWindows(UnkStruct_0208C06C *param0);
static void VsRecorderViewerSubMenu_RemoveOptionWindows(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerSubMenu_Init(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerSubMenu_Setup(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerSubMenu_HandleOptions(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerSubMenu_Exit(UnkStruct_0208C06C *param0);

static void VsRecorderViewerSubMenu_CreateMessageWindow(UnkStruct_0208C06C *param0, BOOL param1)
{
    Window *v0 = &param0->unk_8A4;

    VsRecorderViewerMenu_LoadBgPanel(param0, 2, param1);
    Window_Init(v0);
    Window_Add(param0->unk_14.unk_10, v0, 2, 1, 19, 30, 4, 14, 300);
}

static void VsRecorderViewerSubMenu_RemoveMessageWindow(UnkStruct_0208C06C *param0)
{
    Window_ClearAndCopyToVRAM(&param0->unk_8A4);
    Window_Remove(&param0->unk_8A4);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
}

static void VsRecorderViewerSubMenu_DrawMessage(UnkStruct_0208C06C *param0, int param1, int param2)
{
    String *v0;
    Window *v1 = &param0->unk_8A4;

    if (param1 == 282) {
        StringTemplate *v2;
        String *v3;
        String *v4;
        PlayerProfile *v5 = param0->unk_88C[param2];

        v2 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
        v0 = String_Init(255, HEAP_ID_102);
        v3 = PlayerProfile_GetName(v5, HEAP_ID_102);

        VsRecorderViewerList_CheckNameChars(param0, v3);
        v4 = MessageLoader_GetNewString(param0->unk_14.unk_34, param1);

        StringTemplate_SetString(v2, 0, v3, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v2, v0, v4);
        String_Free(v3);
        String_Free(v4);
        StringTemplate_Free(v2);
    } else {
        v0 = MessageLoader_GetNewString(param0->unk_14.unk_34, param1);
    }

    Window_FillTilemap(v1, 0xCC);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 12), NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v0);
}

static void VsRecorderViewerSubMenu_CreateOptionWindows(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerSubMenuContext *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    int v3 = 1;
    int v4;

    v1 = &v0->unk_10[0];

    Window_Init(v1);
    Window_Add(param0->unk_14.unk_10, v1, 6, 4, 6, 10, 2, 14, v3);
    Window_FillTilemap(v1, 0x0);

    v2 = MessageLoader_GetNewString(param0->unk_14.unk_34, 130);
    v4 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);

    v3 += (10 * 2);
    v1 = &v0->unk_10[1];

    Window_Init(v1);
    Window_Add(param0->unk_14.unk_10, v1, 6, 18, 6, 10, 2, 14, v3);
    Window_FillTilemap(v1, 0x0);

    v2 = MessageLoader_GetNewString(param0->unk_14.unk_34, 131);
    v4 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);
}

static void VsRecorderViewerSubMenu_RemoveOptionWindows(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerSubMenuContext *v0 = param0->unk_860;

    Window_ClearAndCopyToVRAM(&v0->unk_10[0]);
    Window_Remove(&v0->unk_10[0]);
    Window_ClearAndCopyToVRAM(&v0->unk_10[1]);
    Window_Remove(&v0->unk_10[1]);
}

static BOOL VsRecorderViewerSubMenu_Init(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerSubMenuContext *v0 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerSubMenuContext));

    memset(v0, 0, sizeof(VsRecorderViewerSubMenuContext));
    param0->unk_860 = v0;

    Bg_ClearTilemap(param0->unk_14.unk_10, 2);
    Bg_ClearTilemap(param0->unk_14.unk_10, 3);
    Bg_ClearTilemap(param0->unk_14.unk_10, 6);
    Bg_ClearTilemap(param0->unk_14.unk_10, 7);
    VsRecorderViewerMenu_SetDefaultBlendAlpha(&v0->unk_00, &v0->unk_04, 0);
    VsRecorderViewerMain_SetState(param0, 1);

    return 0;
}

static BOOL VsRecorderViewerSubMenu_Setup(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerSubMenuContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.unk_44);
        break;
    case 1:
        Bg_SetPriority(BG_LAYER_MAIN_0, 0);
        Bg_SetPriority(BG_LAYER_MAIN_1, 3);
        Bg_SetPriority(BG_LAYER_MAIN_2, 0);
        Bg_SetPriority(BG_LAYER_MAIN_3, 2);
        Bg_SetPriority(BG_LAYER_SUB_0, 0);
        Bg_SetPriority(BG_LAYER_SUB_1, 3);
        Bg_SetPriority(BG_LAYER_SUB_2, 1);
        Bg_SetPriority(BG_LAYER_SUB_3, 2);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.unk_00, 62, param0->unk_14.unk_10, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.unk_00, 62, param0->unk_14.unk_10, 7, 0, 0, 0, HEAP_ID_102);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_HideAndFreeMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->unk_08++;
        break;
    default:
        VsRecorderViewerList_StartNetworkTask(param0, 0);
        VsRecorderViewerMain_SetState(param0, 2);
        break;
    }

    return 0;
}

static const TouchScreenRect sVsRecorderViewerSubMenuTouchRects[] = {
    { 0x28, 0x48, 0x20, 0x78 },
    { 0x28, 0x48, 0x90, 0xE8 }
};

static BOOL VsRecorderViewerSubMenu_HandleOptions(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerSubMenuContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerSubMenu_CreateOptionWindows(param0);
        VsRecorderViewerSubMenu_CreateMessageWindow(param0, 0);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.unk_00, 84, param0->unk_14.unk_10, 7, 0, 0, 0, HEAP_ID_102);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 2)) {
            VsRecorderViewerSubMenu_DrawMessage(param0, 282, param0->unk_86C);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        break;
    case 2:
        if (TouchScreen_LocationPressed(&sVsRecorderViewerSubMenuTouchRects[0])) {
            VsRecorderViewerList_PlayRingAnim(param0);
            VsRecorderViewerSubMenu_DrawMessage(param0, 283, 0);
            param0->unk_08++;
        } else if (TouchScreen_LocationPressed(&sVsRecorderViewerSubMenuTouchRects[1])) {
            VsRecorderViewerList_PlayRingAnim(param0);
            v0->unk_0C = 1;
            VsRecorderViewerSubMenu_RemoveMessageWindow(param0);
            param0->unk_08 = 4;
        }

        break;
    case 3:
        if (TouchScreen_LocationPressed(&sVsRecorderViewerSubMenuTouchRects[0])) {
            VsRecorderViewerList_PlayRingAnim(param0);
            VsRecorderViewerList_ResetRecordState(param0);
            v0->unk_0C = 0;
            param0->unk_08++;
        } else if (TouchScreen_LocationPressed(&sVsRecorderViewerSubMenuTouchRects[1])) {
            VsRecorderViewerList_PlayRingAnim(param0);
            VsRecorderViewerSubMenu_RemoveMessageWindow(param0);
            v0->unk_0C = 1;
            param0->unk_08++;
        }
        break;
    case 4:
        VsRecorderViewerSubMenu_RemoveOptionWindows(param0);
        param0->unk_08++;
        break;
    case 5:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            if (v0->unk_0C == 1) {
                VsRecorderViewerMain_SetState(param0, 3);
            } else {
                param0->unk_08++;
            }
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        break;
    case 6:
        if (VsRecorderViewerList_ClearExtraSaveKey(param0)) {
            VsRecorderViewerList_FreeBattleRecordings(param0);
            VsRecorderViewerList_LoadBattleRecordings(param0);
            VsRecorderViewerSubMenu_DrawMessage(param0, 285, 0);
            param0->unk_08++;
        } else {
            VsRecorderViewerMain_SetState(param0, 3);
        }
        break;
    default:
        if (!TouchScreen_Tapped()) {
            break;
        }

        VsRecorderViewerSubMenu_RemoveMessageWindow(param0);
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerSubMenu_Exit(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerSubMenuContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        param0->unk_08++;
    case 1:
        param0->unk_08++;
    case 2:
        VsRecorderViewerMenu_InitMenu(param0);
        Bg_ClearTilemap(param0->unk_14.unk_10, 2);
        Bg_ClearTilemap(param0->unk_14.unk_10, 6);
        Bg_ClearTilemap(param0->unk_14.unk_10, 3);
        Bg_ClearTilemap(param0->unk_14.unk_10, 7);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->unk_08++;
        break;
    default:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.unk_44);
            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);
            Heap_Free(v0);
        } else {
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.unk_44);
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        }
        break;
    }

    return 0;
}

// clang-format off
BOOL(*const sVsRecorderViewerSubMenuStateFuncs[])(UnkStruct_0208C06C *) = {
    VsRecorderViewerSubMenu_Init,
    VsRecorderViewerSubMenu_Setup,
    VsRecorderViewerSubMenu_HandleOptions,
    VsRecorderViewerSubMenu_Exit,
};
// clang-format on
