#include "global_terminal/global_terminal_0222BF44.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"
#include "constants/net.h"

#include "struct_decls/wi_fi_list.h"
#include "struct_defs/struct_02017498.h"

#include "nintendo_wfc/main.h"
#include "global_terminal/struct_global_terminal_0222C3B0.h"

#include "bg_window.h"
#include "comm_manager.h"
#include "font.h"
#include "game_options.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "inlines.h"
#include "list_menu.h"
#include "menu.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "render_oam.h"
#include "render_text.h"
#include "render_window.h"
#include "save_player.h"
#include "screen_fade.h"
#include "string_gf.h"
#include "string_list.h"
#include "string_template.h"
#include "system.h"
#include "system_data.h"
#include "text.h"
#include "touch_pad.h"
#include "wifi_list_util.h"
#include "vram_transfer.h"
#include "wifi_list.h"

typedef struct {
    WiFiLobbyAppState *unk_00;
    BgConfig *unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    StringTemplate *unk_20;
    MessageLoader *unk_24;
    MessageLoader *unk_28;
    MessageLoader *unk_2C;
    MessageLoader *unk_30;
    String *unk_34;
    String *unk_38;
    String *unk_3C;
    int unk_40;
    Window unk_44;
    Window unk_54;
    Window unk_64;
    Window unk_74;
    Menu *unk_84;
    void *unk_88;
    int unk_8C;
    int unk_90;
    int unk_94;
    int unk_98;
    StringList *unk_9C;
    ListMenu *unk_A0;
    GlobalTerminalPaletteBlend unk_A4;
} GlobalTerminalApp;

int GlobalTerminal_Init(ApplicationManager *appMan, int *unused);
int GlobalTerminal_Main(ApplicationManager *appMan, int *param1);
int GlobalTerminal_Exit(ApplicationManager *appMan, int *param1);
static void GlobalTerminal_VBlankCallback(void *param0);
static void GlobalTerminal_InitGraphics(BgConfig *param0);
static void GlobalTerminal_FreeGraphics(BgConfig *param0);
static void GlobalTerminal_LoadGraphics(GlobalTerminalApp *param0);
static void GlobalTerminal_InitWindows(GlobalTerminalApp *param0);
static void GlobalTerminal_FreeWindows(GlobalTerminalApp *param0);
static int GlobalTerminal_AlignText(Window *param0, String *param1, int param2, int param3, u32 param4, int param5);
void GlobalTerminal_DrawText(Window *param0, String *param1, int param2, int param3, int param4, TextColor param5);
static void GlobalTerminal_ShowMessage(GlobalTerminalApp *param0, int param1);
static void GlobalTerminal_ShowError(GlobalTerminalApp *param0, int param1, int param2);
static int GlobalTerminal_IsTextActive(int param0);
static void GlobalTerminal_AddWaitDial(GlobalTerminalApp *param0);
static void GlobalTerminal_DestroyWaitDial(GlobalTerminalApp *param0);
static Menu *GlobalTerminal_MakeYesNoMenu(BgConfig *param0, int param1, int param2);
static void GlobalTerminal_PrintMessage(GlobalTerminalApp *param0, MessageLoader *param1, int param2, int param3, u16 param4);
static void GlobalTerminal_SetNextState(GlobalTerminalApp *param0, int param1, int param2);
static BOOL GlobalTerminal_IsRetryableError(int param0, int param1);
static int GlobalTerminal_StateConfirmConnect(GlobalTerminalApp *param0);
static int GlobalTerminal_StateInitConnection(GlobalTerminalApp *param0);
static int GlobalTerminal_StateProcessConnection(GlobalTerminalApp *param0);
static int GlobalTerminal_StateLogin(GlobalTerminalApp *param0);
static int GlobalTerminal_StateProcessLogin(GlobalTerminalApp *param0);
static int GlobalTerminal_StateLaunchVsRecorder(GlobalTerminalApp *param0);
static int GlobalTerminal_StateShowError(GlobalTerminalApp *param0);
static int GlobalTerminal_StateWaitErrorAck(GlobalTerminalApp *param0);
static int GlobalTerminal_StateDisconnect(GlobalTerminalApp *param0);
static int GlobalTerminal_StateShowErrorCode(GlobalTerminalApp *param0);
static int GlobalTerminal_StateCleanupAndExit(GlobalTerminalApp *param0);
static int GlobalTerminal_StateWaitMessage(GlobalTerminalApp *param0);
static int GlobalTerminal_StateDisconnectAndExit(GlobalTerminalApp *param0);

static int (*sGlobalTerminalStateHandlers[])(GlobalTerminalApp *) = {
    GlobalTerminal_StateConfirmConnect,
    GlobalTerminal_StateInitConnection,
    GlobalTerminal_StateProcessConnection,
    GlobalTerminal_StateLogin,
    GlobalTerminal_StateProcessLogin,
    GlobalTerminal_StateLaunchVsRecorder,
    GlobalTerminal_StateShowError,
    GlobalTerminal_StateWaitErrorAck,
    GlobalTerminal_StateDisconnect,
    GlobalTerminal_StateDisconnect,
    GlobalTerminal_StateShowErrorCode,
    GlobalTerminal_StateCleanupAndExit,
    GlobalTerminal_StateWaitMessage,
    GlobalTerminal_StateDisconnectAndExit,
};

static const WindowTemplate sGlobalTerminalWindowTemplate = {
    0x0,
    0x17,
    0xD,
    0x7,
    0x4,
    0xD,
    0x0
};

int GlobalTerminal_Init(ApplicationManager *appMan, int *unused)
{
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();

    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);
    GX_SetVisibleWnd(GX_WNDMASK_NONE);
    GXS_SetVisibleWnd(GX_WNDMASK_NONE);
    G2_BlendNone();
    G2S_BlendNone();

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_117, 0x50000);

    GlobalTerminalApp *v0 = ApplicationManager_NewData(appMan, sizeof(GlobalTerminalApp), HEAP_ID_117);
    MI_CpuClear8(v0, sizeof(GlobalTerminalApp));
    v0->unk_00 = ApplicationManager_Args(appMan);
    v0->unk_04 = BgConfig_New(HEAP_ID_117);

    VramTransfer_New(64, HEAP_ID_117);
    SetAutorepeat(4, 8);
    GlobalTerminal_InitGraphics(v0->unk_04);
    EnableTouchPad();
    InitializeTouchPad(4);

    v0->unk_20 = StringTemplate_New(11, 64, HEAP_ID_117);
    v0->unk_24 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_GTS, HEAP_ID_117);
    v0->unk_28 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0674, HEAP_ID_117);
    v0->unk_2C = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0695, HEAP_ID_117);
    v0->unk_34 = String_Init(90 * 2, HEAP_ID_117);
    v0->unk_3C = String_Init(16 * 8 * 2, HEAP_ID_117);
    v0->unk_38 = MessageLoader_GetNewString(v0->unk_24, 31);

    GlobalTerminal_LoadGraphics(v0);
    GlobalTerminal_InitWindows(v0);

    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_117);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);

    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;

    GXLayers_SwapDisplay();
    RenderControlFlags_SetCanABSpeedUpPrint(TRUE);
    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_DISABLED);
    RenderControlFlags_SetSpeedUpOnTouch(FALSE);
    SetVBlankCallback(GlobalTerminal_VBlankCallback, v0);

    if (v0->unk_00->vsRecorderLaunched) {
        NetworkIcon_Init();
        GlobalTerminal_SetNextState(v0, 13, 8);
    } else {
        if (v0->unk_00->args->unk_08) {
            v0->unk_08 = 1;
        } else {
            v0->unk_08 = 0;
        }
    }

    v0->unk_00->vsRecorderRequested = 0;
    return 1;
}

int GlobalTerminal_Main(ApplicationManager *appMan, int *param1)
{
    GlobalTerminalApp *v0 = ApplicationManager_Data(appMan);

    switch (*param1) {
    case 0:
        if (IsScreenFadeDone() == TRUE) {
            *param1 = 1;
        }
        break;
    case 1:
        int v2 = v0->unk_08;
        int v1 = (*sGlobalTerminalStateHandlers[v0->unk_08])(v0);

        if (v2 != v0->unk_08) {
            v0->unk_90 = 0;
            v0->unk_98 = 0;
            v0->unk_94 = 0;
        }

        if (v1 == 1) {
            *param1 = 2;
        }
        break;
    case 2:
        if (IsScreenFadeDone() == TRUE) {
            return 1;
        }
        break;
    }

    GlobalTerminal_PaletteBlendNoop(&v0->unk_A4);
    return 0;
}

int GlobalTerminal_Exit(ApplicationManager *appMan, int *param1)
{
    GlobalTerminalApp *v0 = ApplicationManager_Data(appMan);

    GlobalTerminal_FreePaletteBlend(&v0->unk_A4);

    MessageLoader_Free(v0->unk_2C);
    MessageLoader_Free(v0->unk_28);
    MessageLoader_Free(v0->unk_24);
    StringTemplate_Free(v0->unk_20);
    String_Free(v0->unk_38);
    String_Free(v0->unk_3C);
    String_Free(v0->unk_34);
    GlobalTerminal_FreeWindows(v0);
    Heap_Free(v0->unk_04);
    GlobalTerminal_FreeGraphics(v0->unk_04);
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    VramTransfer_Free();
    DisableTouchPad();
    RenderControlFlags_SetCanABSpeedUpPrint(FALSE);
    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_DISABLED);
    RenderControlFlags_SetSpeedUpOnTouch(FALSE);
    NetworkIcon_Destroy();
    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_117);

    return 1;
}

static void GlobalTerminal_VBlankCallback(void *param0)
{
    GlobalTerminalApp *v0 = param0;

    VramTransfer_Process();
    RenderOam_Transfer();
    Bg_RunScheduledUpdates(v0->unk_04);

    GlobalTerminal_PaletteBlendNoop2(&v0->unk_A4);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void GlobalTerminal_InitGraphics(BgConfig *param0)
{
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();

    {
        GXBanks v0 = {
            GX_VRAM_BG_128_A,
            GX_VRAM_BGEXTPLTT_NONE,
            GX_VRAM_SUB_BG_128_C,
            GX_VRAM_SUB_BGEXTPLTT_NONE,
            GX_VRAM_OBJ_64_E,
            GX_VRAM_OBJEXTPLTT_NONE,
            GX_VRAM_SUB_OBJ_16_I,
            GX_VRAM_SUB_OBJEXTPLTT_NONE,
            GX_VRAM_TEX_0_B,
            GX_VRAM_TEXPLTT_01_FG
        };

        GXLayers_SetBanks(&v0);

        MI_CpuClear32((void *)HW_BG_VRAM, HW_BG_VRAM_SIZE);
        MI_CpuClear32((void *)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
        MI_CpuClear32((void *)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
        MI_CpuClear32((void *)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    }

    {
        GraphicsModes v1 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D,
        };

        SetAllGraphicsModes(&v1);
    }

    {
        BgTemplate v2[] = {
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0xf800,
                .charBase = GX_BG_CHARBASE_0x00000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0xf000,
                .charBase = GX_BG_CHARBASE_0x08000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 1,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_0, &v2[0], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_0, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_0, 3, 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_1, &v2[1], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_1);
        Bg_SetOffset(param0, BG_LAYER_MAIN_1, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_1, 3, 0);
    }

    {
        BgTemplate v3[] = {
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0xf000,
                .charBase = GX_BG_CHARBASE_0x10000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0xd800,
                .charBase = GX_BG_CHARBASE_0x08000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 2,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_0, &v3[0], 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_0);
        Bg_SetOffset(param0, BG_LAYER_SUB_0, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_SUB_0, 3, 0);
        Bg_InitFromTemplate(param0, BG_LAYER_SUB_1, &v3[1], 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_1);
        Bg_SetOffset(param0, BG_LAYER_SUB_1, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_SUB_1, 3, 0);
    }

    Bg_ClearTilesRange(BG_LAYER_MAIN_0, 32, 0, HEAP_ID_117);
    Bg_ClearTilesRange(4, 32, 0, HEAP_ID_117);
}

static void GlobalTerminal_FreeGraphics(BgConfig *param0)
{
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_0);
}

static void GlobalTerminal_LoadGraphics(GlobalTerminalApp *param0)
{
    BgConfig *v0 = param0->unk_04;
    NARC *v1 = NARC_ctor(NARC_INDEX_DATA__WIFIP2PMATCH, HEAP_ID_117);

    Graphics_LoadPaletteFromOpenNARC(v1, 3, 0, 0, 0, HEAP_ID_117);
    Graphics_LoadPaletteFromOpenNARC(v1, 3, 4, 0, 0, HEAP_ID_117);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(13), HEAP_ID_117);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_SUB_BG, PLTT_OFFSET(13), HEAP_ID_117);
    LoadMessageBoxGraphics(v0, BG_LAYER_MAIN_0, 1, 10, Options_Frame(SaveData_GetOptions(param0->unk_00->args->saveData)), HEAP_ID_117);
    LoadStandardWindowGraphics(v0, BG_LAYER_MAIN_0, 1 + (18 + 12), 11, 0, HEAP_ID_117);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 2, v0, 1, 0, 0, 0, HEAP_ID_117);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 5, v0, 1, 0, 32 * 24 * 2, 0, HEAP_ID_117);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 10, v0, 5, 0, 0, 0, HEAP_ID_117);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 11, v0, 5, 0, 32 * 24 * 2, 0, HEAP_ID_117);
    Bg_MaskPalette(BG_LAYER_MAIN_0, 0);
    Bg_MaskPalette(BG_LAYER_SUB_0, 0);

    GlobalTerminal_InitPaletteBlend(&param0->unk_A4, v1, 4, 117);

    NARC_dtor(v1);
}

static void GlobalTerminal_InitWindows(GlobalTerminalApp *param0)
{
    Window_Add(param0->unk_04, &param0->unk_64, 0, 4, 4, 23, 16, 13, ((1 + (18 + 12)) + 9) + 27 * 4);
    Window_FillTilemap(&param0->unk_64, 0x0);
    Window_Add(param0->unk_04, &param0->unk_54, 0, 4, 1, 24, 2, 13, (((1 + (18 + 12)) + 9) + 27 * 4) + 23 * 16);
    Window_FillTilemap(&param0->unk_54, 0x0);

    GlobalTerminal_DrawText(&param0->unk_54, param0->unk_38, 0, 1, 1, TEXT_COLOR(15, 14, 0));

    Window_Add(param0->unk_04, &param0->unk_44, 0, 2, 19, 27, 4, 13, (1 + (18 + 12)) + 9);
    Window_FillTilemap(&param0->unk_44, 0x0);
}

static void GlobalTerminal_FreeWindows(GlobalTerminalApp *param0)
{
    Window_Remove(&param0->unk_44);
    Window_Remove(&param0->unk_54);
    Window_Remove(&param0->unk_64);
}

static int GlobalTerminal_AlignText(Window *param0, String *param1, int param2, int param3, u32 param4, int param5)
{
    int v0 = 0, v1;

    switch (param3) {
    case 1:
        v0 = Font_CalcStringWidth(param5, param1, 0);
        param2 = ((param0->width * 8) - v0) / 2;
        break;
    case 2:
        v0 = Font_CalcStringWidth(param5, param1, 0);
        param2 = (param0->width * 8) - v0;
        break;
    }

    return param2;
}

void GlobalTerminal_DrawText(Window *param0, String *param1, int param2, int param3, int param4, TextColor param5)
{
    param2 = GlobalTerminal_AlignText(param0, param1, param2, param4, param5, 1);
    Text_AddPrinterWithParamsAndColor(param0, FONT_MESSAGE, param1, param2, param3, TEXT_SPEED_INSTANT, param5, NULL);
}

static void GlobalTerminal_ShowMessage(GlobalTerminalApp *param0, int param1)
{
    String *v0 = String_Init(16 * 8 * 2, HEAP_ID_117);

    MessageLoader_GetString(param0->unk_2C, param1, v0);
    StringTemplate_Format(param0->unk_20, param0->unk_3C, v0);
    Window_FillTilemap(&param0->unk_64, 15);
    Window_DrawStandardFrame(&param0->unk_64, 1, 1 + (18 + 12), 11);

    param0->unk_40 = Text_AddPrinterWithParams(&param0->unk_64, FONT_MESSAGE, param0->unk_3C, 0, 0, TEXT_SPEED_INSTANT, NULL);
    param0->unk_40 = 0xff;

    String_Free(v0);
}

static void GlobalTerminal_ShowError(GlobalTerminalApp *param0, int param1, int param2)
{
    int v0;

    if (param1 != -1) {
        v0 = 0 + param1;
    } else {
        v0 = 11;
    }

    StringTemplate_SetNumber(param0->unk_20, 0, param2, 5, 2, 1);
    Window_EraseMessageBox(&param0->unk_44, 1);

    GlobalTerminal_ShowMessage(param0, v0);
}

static int GlobalTerminal_IsTextActive(int param0)
{
    if ((param0 == 0xff) || (Text_IsPrinterActive(param0) == 0)) {
        return 0;
    }

    return 1;
}

static void GlobalTerminal_AddWaitDial(GlobalTerminalApp *param0)
{
    if (param0->unk_88 == NULL) {
        param0->unk_88 = Window_AddWaitDial(&param0->unk_44, 1);
    }
}

static void GlobalTerminal_DestroyWaitDial(GlobalTerminalApp *param0)
{
    if (param0->unk_88 != NULL) {
        DestroyWaitDial(param0->unk_88);
        param0->unk_88 = NULL;
    }
}

static Menu *GlobalTerminal_MakeYesNoMenu(BgConfig *param0, int param1, int param2)
{
    WindowTemplate v0;

    v0 = sGlobalTerminalWindowTemplate;
    v0.tilemapTop = param1;
    v0.baseTile = param2;

    return Menu_MakeYesNoChoice(param0, &v0, 1 + (18 + 12), 11, 117);
}

static void GlobalTerminal_PrintMessage(GlobalTerminalApp *param0, MessageLoader *param1, int param2, int param3, u16 param4)
{
    String *v0 = MessageLoader_GetNewString(param1, param2);

    StringTemplate_Format(param0->unk_20, param0->unk_34, v0);
    String_Free(v0);
    Window_FillTilemap(&param0->unk_44, 0xf0f);
    Window_DrawMessageBoxWithScrollCursor(&param0->unk_44, 0, 1, 10);

    param0->unk_40 = Text_AddPrinterWithParams(&param0->unk_44, FONT_MESSAGE, param0->unk_34, 0, 0, param3, NULL);
    param0->unk_8C = 0;

    if ((param3 == 0xff) || (param3 == 0)) {
        param0->unk_40 = 0xff;
    }
}

static void GlobalTerminal_SetNextState(GlobalTerminalApp *param0, int param1, int param2)
{
    param0->unk_08 = param1;
    param0->unk_0C = param2;
}

static BOOL GlobalTerminal_IsRetryableError(int param0, int param1)
{
    int v0;
    BOOL v1;

    v0 = NintendoWFC_GetErrorCode(param0, param1);

    switch (v0) {
    case 1:
    case 4:
    case 5:
    case 11:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        v1 = 1;
        break;
    case 0:
    case 2:
    case 3:
    default:
        v1 = 0;
        break;
    }

    return v1;
}

static int GlobalTerminal_StateConfirmConnect(GlobalTerminalApp *param0)
{
    if (GlobalTerminal_IsTextActive(param0->unk_40) == 1) {
        return 0;
    }

    switch (param0->unk_90) {
    case 0:
        param0->unk_90++;
        break;
    case 1:
        GlobalTerminal_PrintMessage(param0, param0->unk_2C, 17, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_90++;
        break;
    case 2:
        param0->unk_84 = GlobalTerminal_MakeYesNoMenu(param0->unk_04, 13, ((((1 + (18 + 12)) + 9) + 27 * 4) + 23 * 16) + 24 * 2);
        param0->unk_90++;
        break;
    case 3: {
        int v0 = Menu_ProcessInputAndHandleExit(param0->unk_84, 117);

        if (v0 != 0xffffffff) {
            if (v0 == 0xfffffffe) {
                param0->unk_08 = 8;
            } else {
                param0->unk_90++;
            }
        }
    } break;
    case 4:
        param0->unk_08 = 1;
        break;
    }

    return 0;
}

static int GlobalTerminal_StateInitConnection(GlobalTerminalApp *param0)
{
    switch (param0->unk_90) {
    case 0:
        CommManager_InitializeGlobalWifi(param0->unk_00->args->saveData);
        NetworkIcon_Init();
        GlobalTerminal_PrintMessage(param0, param0->unk_28, 1, TEXT_SPEED_FAST, 0xf0f);
        GlobalTerminal_AddWaitDial(param0);
        param0->unk_90++;
        break;
    case 1:
        if (GlobalTerminal_IsTextActive(param0->unk_40) == 0) {
            param0->unk_90++;
        }
        break;
    case 2:
        DWC_InitInetEx(&param0->unk_00->inetControl, DEFAULT_DWC_DMA_NUMBER, DEFAULT_DWC_POWER_MODE, DEFAULT_DWC_SSL_PRIORITY);
        DWC_SetAuthServer(DWC_CONNECTINET_AUTH_RELEASE);
        DWC_ConnectInetAsync();
        param0->unk_08 = 2;
        break;
    }

    return 0;
}

static int GlobalTerminal_StateProcessConnection(GlobalTerminalApp *param0)
{
    DWC_ProcessInet();

    if (DWC_CheckInet()) {
        switch (DWC_GetInetStatus()) {
        case DWC_CONNECTINET_STATE_ERROR: {
            DWCError v0;
            int v1;
            DWCErrorType v2;

            v0 = DWC_GetLastErrorEx(&v1, &v2);
            param0->unk_14 = v0;
            param0->unk_18 = v1;
            param0->unk_1C = v2;
        }
            DWC_ClearError();
            DWC_CleanupInet();
            GlobalTerminal_DestroyWaitDial(param0);
            param0->unk_08 = 6;
            break;
        case DWC_CONNECTINET_STATE_NOT_INITIALIZED:
        case DWC_CONNECTINET_STATE_IDLE:
        case DWC_CONNECTINET_STATE_OPERATING:
        case DWC_CONNECTINET_STATE_OPERATED:
        case DWC_CONNECTINET_STATE_DISCONNECTING:
        case DWC_CONNECTINET_STATE_DISCONNECTED:
        default:
        case DWC_CONNECTINET_STATE_FATAL_ERROR: {
            int v4;

            DWCError v3 = DWC_GetLastError(&v4);

            GlobalTerminal_DestroyWaitDial(param0);
            param0->unk_08 = 10;
            param0->unk_10 = -2;
        } break;
        case DWC_CONNECTINET_STATE_CONNECTED: {
            DWCApInfo v5;

            DWC_GetApInfo(&v5);

            if (v5.aptype == DWC_APINFO_TYPE_SHOP) {
                (void)0;
            }
        }

            param0->unk_08 = 3;
            break;
        }
    }

    return 0;
}

static int GlobalTerminal_StateLogin(GlobalTerminalApp *param0)
{
    DWC_NASLoginAsync();
    param0->unk_08 = 4;
    return 0;
}

static int GlobalTerminal_StateProcessLogin(GlobalTerminalApp *param0)
{
    switch (DWC_NASLoginProcess()) {
    case DWC_NASLOGIN_STATE_SUCCESS:;
        param0->unk_08 = 5;
        break;
    case DWC_NASLOGIN_STATE_ERROR:
    case DWC_NASLOGIN_STATE_CANCELED:
    case DWC_NASLOGIN_STATE_DIRTY:
        GlobalTerminal_DestroyWaitDial(param0);
        {
            int v0;
            DWCErrorType v1;

            DWCError v2 = DWC_GetLastErrorEx(&v0, &v1);

            param0->unk_14 = v2;
            param0->unk_18 = v0;
            param0->unk_1C = v1;

            DWC_ClearError();
            DWC_CleanupInet();

            param0->unk_08 = 6;

            switch (v1) {
            case DWC_ETYPE_LIGHT:
            case DWC_ETYPE_SHOW_ERROR:
                param0->unk_08 = 6;
                break;
            case DWC_ETYPE_SHUTDOWN_GHTTP:
                DWC_ShutdownGHTTP();
                param0->unk_08 = 6;
                break;
            case DWC_ETYPE_DISCONNECT:
                param0->unk_08 = 6;
                break;
            case DWC_ETYPE_SHUTDOWN_FM:
                DWC_ShutdownFriendsMatch();
                param0->unk_08 = 6;
                break;
            case DWC_ETYPE_SHUTDOWN_ND:
            case DWC_ETYPE_FATAL:
                NetworkError_DisplayGTSCriticalError();
                break;
            }
            if ((v0 < -20000) && (v0 >= -29999)) {
                param0->unk_08 = 6;
            }
        }
        break;
    }

    return 0;
}

static int GlobalTerminal_StateLaunchVsRecorder(GlobalTerminalApp *param0)
{
    s32 profileID;
    WiFiList *wiFiList = SaveData_GetWiFiList(param0->unk_00->args->saveData);
    SystemData *sysData = SaveData_GetSystemData(param0->unk_00->args->saveData);
    DWCUserData *userData = WiFiList_GetUserData(wiFiList);
    profileID = SystemData_GetDWCProfileId(sysData);

    if (profileID == 0) {
        SystemData_SetDWCProfileId(sysData, WiFiList_GetUserGsProfileId(wiFiList));
    }

    profileID = SystemData_GetDWCProfileId(sysData);

    param0->unk_08 = 9;
    param0->unk_00->vsRecorderRequested = 1;

    return 0;
}

static int GlobalTerminal_StateShowError(GlobalTerminalApp *param0)
{
    int errorCode = NintendoWFC_GetErrorCode(-param0->unk_18, param0->unk_1C);
    GlobalTerminal_ShowError(param0, errorCode, -param0->unk_18);
    param0->unk_08 = 7;

    return 0;
}

static int GlobalTerminal_StateWaitErrorAck(GlobalTerminalApp *param0)
{
    if (gSystem.pressedKeys & PAD_BUTTON_A || gSystem.pressedKeys & PAD_BUTTON_B) {
        Window_EraseStandardFrame(&param0->unk_64, 0);
        param0->unk_90 = 0;

        if (GlobalTerminal_IsRetryableError(-param0->unk_18, param0->unk_1C) == 1) {
            param0->unk_08 = 0;
        } else {
            param0->unk_08 = 8;
        }
    }

    return 0;
}

static int GlobalTerminal_StateDisconnect(GlobalTerminalApp *param0)
{
    if (param0->unk_08 != 9) {
        CommManager_EndGlobalWifi();
    }

    NetworkIcon_Destroy();
    GlobalTerminal_DestroyWaitDial(param0);
    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_117);
    param0->unk_08 = 0;

    return 1;
}

static int GlobalTerminal_StateShowErrorCode(GlobalTerminalApp *param0)
{
    int v0 = 0;

    switch (param0->unk_10) {
    case 1:
        v0 = 144;
        break;
    case 2:
    case -1:
        v0 = 145;
        break;
    case -2:
    case -14:
        v0 = 150;
        break;
    case -12:
    case -15:
    case -3:
    case -5:
        v0 = 149;
        break;
    }

    GlobalTerminal_PrintMessage(param0, param0->unk_24, v0, TEXT_SPEED_FAST, 0xf0f);
    GlobalTerminal_SetNextState(param0, 12, 11);

    return 0;
}

static int GlobalTerminal_StateCleanupAndExit(GlobalTerminalApp *param0)
{
    switch (param0->unk_90) {
    case 0:
        GlobalTerminal_PrintMessage(param0, param0->unk_24, 178, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_90++;
        break;
    case 1:
        if (GlobalTerminal_IsTextActive(param0->unk_40) == 0) {
            CommManager_EndGlobalWifi();
            DWC_CleanupInet();
            param0->unk_90++;
        }
        break;
    case 2:
        GlobalTerminal_PrintMessage(param0, param0->unk_24, 179, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_90++;
        break;
    case 3:
        if (GlobalTerminal_IsTextActive(param0->unk_40) == 0) {
            param0->unk_90++;
        }
        break;
    default:
        param0->unk_94++;

        if (param0->unk_94 > 30) {
            param0->unk_08 = 8;
        }

        break;
    }

    return 0;
}

static int GlobalTerminal_StateWaitMessage(GlobalTerminalApp *param0)
{
    if (GlobalTerminal_IsTextActive(param0->unk_40) == 0) {
        param0->unk_08 = param0->unk_0C;
    }

    return 0;
}

static int GlobalTerminal_StateDisconnectAndExit(GlobalTerminalApp *param0)
{
    if (GlobalTerminal_IsTextActive(param0->unk_40) == 1) {
        return 0;
    }

    switch (param0->unk_90) {
    case 0:
        GlobalTerminal_PrintMessage(param0, param0->unk_2C, 26, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_90++;
        break;
    case 1:
        DWC_CleanupInet();
        CommManager_EndGlobalWifi();
        param0->unk_90++;
        break;
    case 2:
        NetworkIcon_Destroy();
        GlobalTerminal_PrintMessage(param0, param0->unk_2C, 27, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_90++;
        break;
    case 3:
        param0->unk_94++;
        if (param0->unk_94 > 30) {
            param0->unk_08 = param0->unk_0C;
        }
        break;
    }

    return 0;
}
