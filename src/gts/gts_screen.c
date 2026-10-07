#include "gts/gts_screen.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"
#include "constants/net.h"

#include "struct_decls/wi_fi_list.h"

#include "gts_application/networking.h"
#include "nintendo_wfc/main.h"
#include "overlay061/struct_ov61_0222C3B0.h"
#include "gts/gts.h"
#include "gts/gts_email.h"
#include "gts/struct_gts.h"

#include "bg_window.h"
#include "colored_arrow.h"
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
#include "savedata.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "string_gf.h"
#include "string_list.h"
#include "string_template.h"
#include "system.h"
#include "system_data.h"
#include "text.h"
#include "touch_pad.h"
#include "email.h"
#include "wifi_list_util.h"
#include "vram_transfer.h"
#include "wifi_list.h"

typedef struct {
    GTSState *unk_00;
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
    MessageLoader *unk_34;
    String *unk_38;
    String *unk_3C;
    String *unk_40;
    int unk_44;
    Window unk_48;
    Window unk_58;
    Window unk_68;
    Window unk_78;
    Menu *unk_88;
    void *unk_8C;
    int unk_90;
    int unk_94;
    int unk_98;
    int unk_9C;
    StringList *unk_A0;
    ListMenu *unk_A4;
    int unk_A8;
    int unk_AC;
    int unk_B0;
    int unk_B4;
    int unk_B8;
    int unk_BC;
    int unk_C0;
    Window unk_C4;
    Window unk_D4;
    ColoredArrow *unk_E4;
    s32 unk_E8;
    UnkStruct_ov61_0222C3B0 unk_EC;
} GTSScreen;

typedef struct {
    u32 unk_00;
    u32 unk_04;
} GTSMenuEntry;

int GTSScreen_Init(ApplicationManager *appMan, int *param1);
int GTSScreen_Main(ApplicationManager *appMan, int *param1);
int GTSScreen_Exit(ApplicationManager *appMan, int *param1);
static void GTSScreen_VBlankCallback(void *param0);
static void GTSScreen_InitGraphics(BgConfig *param0);
static void GTSScreen_FreeBackgrounds(BgConfig *param0);
static void GTSScreen_LoadGraphics(GTSScreen *param0);
static void GTSScreen_InitWindows(GTSScreen *param0);
static void GTSScreen_FreeWindows(GTSScreen *param0);
static void GTSScreen_SetNextScreen(GTSScreen *param0, int param1, int param2);
static void GTSScreen_AddWaitDial(GTSScreen *param0);
static void GTSScreen_DestroyWaitDial(GTSScreen *param0);
static Menu *GTSScreen_MakeYesNoMenu(BgConfig *param0, int param1, int param2);
static int GTSScreen_MainMenu(GTSScreen *param0);
static int GTSScreen_CheckWiiNumber(GTSScreen *param0);
static int GTSScreen_SetMessageReception(GTSScreen *param0);
static int GTSScreen_DeleteSettings(GTSScreen *param0);
static int GTSScreen_RegisterWiiNumber(GTSScreen *param0);
static int GTSScreen_StartEmailEntry(GTSScreen *param0);
static int GTSScreen_EmailEntryResult(GTSScreen *param0);
static int GTSScreen_ConfirmWiiNumber(GTSScreen *param0);
static int GTSScreen_ConfirmConnect(GTSScreen *param0);
static int GTSScreen_ShowDisconnecting(GTSScreen *param0);
static int GTSScreen_Disconnect(GTSScreen *param0);
static int GTSScreen_ShowDisconnected(GTSScreen *param0);
static int GTSScreen_ConnectWifi(GTSScreen *param0);
static int GTSScreen_WaitConnect(GTSScreen *param0);
static int GTSScreen_StartNasLogin(GTSScreen *param0);
static int GTSScreen_WaitNasLogin(GTSScreen *param0);
static int GTSScreen_InitCredentials(GTSScreen *param0);
static int GTSScreen_SetProfile(GTSScreen *param0);
static int GTSScreen_WaitSetProfile(GTSScreen *param0);
static int GTSScreen_ShowCodeSent(GTSScreen *param0);
static int GTSScreen_StartCodeEntry(GTSScreen *param0);
static int GTSScreen_ConfirmCancelRegistration(GTSScreen *param0);
static int GTSScreen_RegisterCode(GTSScreen *param0);
static int GTSScreen_StartNumberEntry(GTSScreen *param0);
static int GTSScreen_SaveEmail(GTSScreen *param0);
static int GTSScreen_SaveData(GTSScreen *param0);
static int GTSScreen_DisconnectWithMessage(GTSScreen *param0);
static int GTSScreen_ShowError(GTSScreen *param0);
static int GTSScreen_WaitErrorAck(GTSScreen *param0);
static int GTSScreen_Finish(GTSScreen *param0);
static int GTSScreen_ShowYesNo(GTSScreen *param0);
static int GTSScreen_ShowErrorCode(GTSScreen *param0);
static int GTSScreen_DisconnectAndExit(GTSScreen *param0);
static int GTSScreen_WaitForPrinter(GTSScreen *param0);
static int GTSScreen_WaitForPrinterAndAdvance(GTSScreen *param0);
static int GTSScreen_ShowYesNoAfterPrint(GTSScreen *param0);
static int GTSScreen_ReenterWiiNumber(GTSScreen *param0);
static int GTSScreen_ShowWiiNumber(GTSScreen *param0);
static void GTSScreen_PrintMessage(GTSScreen *param0, MessageLoader *param1, int param2, int param3, u16 param4);
static int GTSScreen_IsPrinterActive(int param0);
static int GTSScreen_AlignText(Window *param0, String *param1, int param2, int param3, u32 param4, int param5);
void GTSScreen_PrintCenteredText(Window *param0, String *param1, int param2, int param3, int param4, TextColor param5);
static void GTSScreen_PrintErrorBox(GTSScreen *param0, int param1);
static void GTSScreen_PrintError(GTSScreen *param0, int param1, int param2);
static void GTSScreen_ListMenuSoundCallback(ListMenu *param0, u32 param1, u8 param2);
static void GTSScreen_ListMenuSoundCallback2(ListMenu *param0, u32 param1, u8 param2);

static int (*sScreenHandlers[])(GTSScreen *) = {
    GTSScreen_MainMenu,
    GTSScreen_CheckWiiNumber,
    GTSScreen_SetMessageReception,
    GTSScreen_DeleteSettings,
    GTSScreen_RegisterWiiNumber,
    GTSScreen_StartEmailEntry,
    GTSScreen_EmailEntryResult,
    GTSScreen_ConfirmWiiNumber,
    GTSScreen_ConfirmConnect,
    GTSScreen_ShowDisconnecting,
    GTSScreen_Disconnect,
    GTSScreen_ShowDisconnected,
    GTSScreen_ConnectWifi,
    GTSScreen_WaitConnect,
    GTSScreen_StartNasLogin,
    GTSScreen_WaitNasLogin,
    GTSScreen_InitCredentials,
    GTSScreen_SetProfile,
    GTSScreen_WaitSetProfile,
    GTSScreen_ShowCodeSent,
    GTSScreen_StartCodeEntry,
    GTSScreen_ConfirmCancelRegistration,
    GTSScreen_RegisterCode,
    GTSScreen_StartNumberEntry,
    GTSScreen_SaveEmail,
    GTSScreen_SaveData,
    GTSScreen_DisconnectWithMessage,
    GTSScreen_ShowError,
    GTSScreen_WaitErrorAck,
    GTSScreen_Finish,
    GTSScreen_Finish,
    GTSScreen_ShowYesNo,
    GTSScreen_ShowErrorCode,
    GTSScreen_DisconnectAndExit,
    GTSScreen_WaitForPrinter,
    GTSScreen_WaitForPrinterAndAdvance,
    GTSScreen_ShowYesNoAfterPrint,
    GTSScreen_ReenterWiiNumber,
    GTSScreen_ShowWiiNumber,
};

static const GTSMenuEntry sRegisteredMenuEntries[] = {
    { 0x0, 0x1 },
    { 0x2, 0x2 },
    { 0x3, 0x3 },
    { 0x4, 0x1D }
};

static const ListMenuTemplate sRegisteredMenuTemplate = {
    NULL,
    GTSScreen_ListMenuSoundCallback,
    NULL,
    NULL,
    NELEMS(sRegisteredMenuEntries),
    NELEMS(sRegisteredMenuEntries),
    0x0,
    0x8,
    0x0,
    0x0,
    0x1,
    0xF,
    0x2,
    0x0,
    0x10,
    0x0,
    0x0,
    0x0
};

static const u8 sRegisteredMenuWindow[4] = {
    0xB,
    0x7,
    0x14,
    0x8
};

static const GTSMenuEntry sUnregisteredMenuEntries[] = {
    { 0x1, 0x4 },
    { 0x4, 0x1D }
};

static const ListMenuTemplate sUnregisteredMenuTemplate = {
    NULL,
    GTSScreen_ListMenuSoundCallback2,
    NULL,
    NULL,
    NELEMS(sUnregisteredMenuEntries),
    NELEMS(sUnregisteredMenuEntries),
    0x0,
    0x8,
    0x0,
    0x0,
    0x1,
    0xF,
    0x2,
    0x0,
    0x10,
    0x0,
    0x0,
    0x0
};

static const u8 sUnregisteredMenuWindow[4] = {
    0xB,
    0xD,
    0x14,
    0x4
};

static const WindowTemplate sYesNoWindowTemplate = {
    0x0,
    0x17,
    0xD,
    0x7,
    0x4,
    0xD,
    0x0
};

int GTSScreen_Init(ApplicationManager *appMan, int *param1)
{
    GTSScreen *v0;

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

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_109, 0x70000);
    v0 = ApplicationManager_NewData(appMan, sizeof(GTSScreen), HEAP_ID_109);
    MI_CpuClear8(v0, sizeof(GTSScreen));

    v0->unk_00 = ApplicationManager_Args(appMan);
    v0->unk_04 = BgConfig_New(HEAP_ID_109);

    VramTransfer_New(64, HEAP_ID_109);
    SetAutorepeat(4, 8);
    GTSScreen_InitGraphics(v0->unk_04);
    EnableTouchPad();
    InitializeTouchPad(4);

    v0->unk_20 = StringTemplate_New(11, 64, HEAP_ID_109);
    v0->unk_24 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_GTS, HEAP_ID_109);
    v0->unk_2C = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0674, HEAP_ID_109);
    v0->unk_30 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0695, HEAP_ID_109);
    v0->unk_28 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_SPECIES_NAME, HEAP_ID_109);
    v0->unk_34 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0358, HEAP_ID_109);
    v0->unk_38 = String_Init(90 * 2, HEAP_ID_109);
    v0->unk_40 = String_Init(16 * 8 * 2, HEAP_ID_109);
    v0->unk_3C = MessageLoader_GetNewString(v0->unk_24, 31);

    GTSScreen_LoadGraphics(v0);
    GTSScreen_InitWindows(v0);

    switch (GTS_GetNextScreen(v0->unk_00)) {
    case 12:
        if (!DWC_CheckInet() && (WiFiList_HasValidLogin(v0->unk_00->saveData) == 1)) {
            v0->unk_08 = 12;
            CommManager_StartWifiMail(v0->unk_00->saveData);
            NetworkIcon_Init();
        } else {
            v0->unk_08 = 0;
        }
        break;
    case 22:
        v0->unk_E8 = 0;
        NetworkIcon_Init();
        v0->unk_08 = GTS_GetNextScreen(v0->unk_00);
        break;
    default:
        v0->unk_08 = GTS_GetNextScreen(v0->unk_00);
        break;
    }

    GTS_SetNextScreen(v0->unk_00, 0);

    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_109);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);

    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;

    GXLayers_SwapDisplay();
    RenderControlFlags_SetCanABSpeedUpPrint(TRUE);
    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_DISABLED);
    RenderControlFlags_SetSpeedUpOnTouch(FALSE);
    SetVBlankCallback(GTSScreen_VBlankCallback, v0);

    return 1;
}

int GTSScreen_Main(ApplicationManager *appMan, int *param1)
{
    GTSScreen *v0 = ApplicationManager_Data(appMan);
    int v1, v2;

    switch (*param1) {
    case 0:
        if (IsScreenFadeDone() == TRUE) {
            *param1 = 1;
        }
        break;
    case 1:
        v2 = v0->unk_08;
        v1 = (*sScreenHandlers[v0->unk_08])(v0);

        if (v2 != v0->unk_08) {
            v0->unk_94 = 0;
            v0->unk_9C = 0;
            v0->unk_98 = 0;
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

    inline_ov61_0222C0F8(&v0->unk_EC);

    return 0;
}

int GTSScreen_Exit(ApplicationManager *appMan, int *param1)
{
    GTSScreen *v0 = ApplicationManager_Data(appMan);

    inline_ov61_0222C160(&v0->unk_EC);

    MessageLoader_Free(v0->unk_34);
    MessageLoader_Free(v0->unk_28);
    MessageLoader_Free(v0->unk_30);
    MessageLoader_Free(v0->unk_2C);
    MessageLoader_Free(v0->unk_24);
    StringTemplate_Free(v0->unk_20);
    String_Free(v0->unk_3C);
    String_Free(v0->unk_40);
    String_Free(v0->unk_38);
    GTSScreen_FreeWindows(v0);
    Heap_Free(v0->unk_04);
    GTSScreen_FreeBackgrounds(v0->unk_04);
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    VramTransfer_Free();
    DisableTouchPad();
    RenderControlFlags_SetCanABSpeedUpPrint(FALSE);
    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_DISABLED);
    RenderControlFlags_SetSpeedUpOnTouch(FALSE);
    NetworkIcon_Destroy();
    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_109);

    return 1;
}

static void GTSScreen_VBlankCallback(void *param0)
{
    GTSScreen *v0 = param0;

    VramTransfer_Process();
    RenderOam_Transfer();

    Bg_RunScheduledUpdates(v0->unk_04);
    inline_ov61_0222C1FC(&v0->unk_EC);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void GTSScreen_InitGraphics(BgConfig *param0)
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
                .priority = 2,
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
                .priority = 3,
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
                .screenBase = GX_BG_SCRBASE_0xe800,
                .charBase = GX_BG_CHARBASE_0x10000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 1,
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
                .screenBase = GX_BG_SCRBASE_0xe000,
                .charBase = GX_BG_CHARBASE_0x18000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0,
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

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_2, &v2[2], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_2);
        Bg_SetOffset(param0, BG_LAYER_MAIN_2, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_2, 3, 0);

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_3, &v2[3], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_3);
        Bg_SetOffset(param0, BG_LAYER_MAIN_3, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_3, 3, 0);
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

    Bg_ClearTilesRange(BG_LAYER_MAIN_0, 32, 0, HEAP_ID_109);
    Bg_ClearTilesRange(4, 32, 0, HEAP_ID_109);
}

static void GTSScreen_FreeBackgrounds(BgConfig *param0)
{
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_0);
}

static void GTSScreen_LoadGraphics(GTSScreen *param0)
{
    BgConfig *v0 = param0->unk_04;
    NARC *v1 = NARC_ctor(NARC_INDEX_DATA__WIFIP2PMATCH, HEAP_ID_109);

    Graphics_LoadPaletteFromOpenNARC(v1, 3, 0, 0, 0, HEAP_ID_109);
    Graphics_LoadPaletteFromOpenNARC(v1, 3, 4, 0, 0, HEAP_ID_109);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(13), HEAP_ID_109);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_SUB_BG, PLTT_OFFSET(13), HEAP_ID_109);
    LoadMessageBoxGraphics(v0, BG_LAYER_MAIN_0, 1, 10, Options_Frame(param0->unk_00->options), HEAP_ID_109);
    LoadStandardWindowGraphics(v0, BG_LAYER_MAIN_0, 1 + (18 + 12), 11, 0, HEAP_ID_109);
    LoadStandardWindowGraphics(v0, BG_LAYER_MAIN_2, 1 + (18 + 12), 11, 0, HEAP_ID_109);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 2, v0, 1, 0, 0, 0, HEAP_ID_109);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 5, v0, 1, 0, 32 * 24 * 2, 0, HEAP_ID_109);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 10, v0, 5, 0, 0, 0, HEAP_ID_109);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 11, v0, 5, 0, 32 * 24 * 2, 0, HEAP_ID_109);
    Bg_MaskPalette(BG_LAYER_MAIN_0, 0);
    Bg_MaskPalette(BG_LAYER_SUB_0, 0);

    inline_ov61_0222C3B0(&param0->unk_EC, v1, 4, 109);

    NARC_dtor(v1);

    {
        v1 = NARC_ctor(NARC_INDEX_ARC__EMAIL_GRA, HEAP_ID_109);

        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);

        Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 11, v0, 3, 0, 0, 0, HEAP_ID_109);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 10, v0, 3, 0, 0, 0, HEAP_ID_109);
        Graphics_LoadPaletteFromOpenNARC(v1, 12, 0, 9 * 0x20, 0x20, HEAP_ID_109);

        NARC_dtor(v1);
    }
}

static void GTSScreen_InitWindows(GTSScreen *param0)
{
    Window_Add(param0->unk_04, &param0->unk_68, 0, 4, 4, 23, 16, 13, ((1 + (18 + 12)) + 9) + 27 * 4);
    Window_FillTilemap(&param0->unk_68, 0x0);
    Window_Add(param0->unk_04, &param0->unk_58, 0, 4, 1, 24, 2, 13, (((1 + (18 + 12)) + 9) + 27 * 4) + 23 * 16);
    Window_FillTilemap(&param0->unk_58, 0x0);

    GTSScreen_PrintCenteredText(&param0->unk_58, param0->unk_3C, 0, 1, 1, TEXT_COLOR(15, 14, 0));

    Window_Add(param0->unk_04, &param0->unk_48, 0, 2, 19, 27, 4, 13, (1 + (18 + 12)) + 9);
    Window_FillTilemap(&param0->unk_48, 0x0);
}

static void GTSScreen_FreeWindows(GTSScreen *param0)
{
    Window_Remove(&param0->unk_48);
    Window_Remove(&param0->unk_58);
    Window_Remove(&param0->unk_68);
}

static void GTSScreen_SetNextScreen(GTSScreen *param0, int param1, int param2)
{
    param0->unk_08 = param1;
    param0->unk_0C = param2;
}

static void GTSScreen_AddWaitDial(GTSScreen *param0)
{
    if (param0->unk_8C == NULL) {
        param0->unk_8C = Window_AddWaitDial(&param0->unk_48, 1);
    }
}

static void GTSScreen_DestroyWaitDial(GTSScreen *param0)
{
    if (param0->unk_8C != NULL) {
        DestroyWaitDial(param0->unk_8C);
        param0->unk_8C = NULL;
    }
}

static Menu *GTSScreen_MakeYesNoMenu(BgConfig *param0, int param1, int param2)
{
    WindowTemplate v0;

    v0 = sYesNoWindowTemplate;
    v0.tilemapTop = param1;
    v0.baseTile = param2;

    return Menu_MakeYesNoChoice(param0, &v0, 1 + (18 + 12), 11, 109);
}

static Menu *GTSScreen_MakeYesNoMenuWithCursor(BgConfig *param0, int param1, int param2, int param3)
{
    WindowTemplate v0;

    v0 = sYesNoWindowTemplate;
    v0.tilemapTop = param1;
    v0.baseTile = param2;

    return Menu_MakeYesNoChoiceWithCursorAt(param0, &v0, 1 + (18 + 12), 11, param3, 109);
}

static int GTSScreen_MainMenu(GTSScreen *param0)
{
    u32 v0;

    switch (param0->unk_94) {
    case 0: {
        int v1;
        ListMenuTemplate v2;
        const u8 *v3;
        const GTSMenuEntry *v4;
        int v5;

        if (Email_HasEmailString(param0->unk_00->saveData) == 1) {
            v3 = sRegisteredMenuWindow;
            v4 = sRegisteredMenuEntries;
            v5 = (NELEMS(sRegisteredMenuEntries));
            v2 = sRegisteredMenuTemplate;
        } else {
            v3 = sUnregisteredMenuWindow;
            v4 = sUnregisteredMenuEntries;
            v5 = (NELEMS(sUnregisteredMenuEntries));
            v2 = sUnregisteredMenuTemplate;
        }

        Window_Add(param0->unk_04, &param0->unk_78, 0, v3[0], v3[1], v3[2], v3[3], 13, ((1 + (18 + 12)) + 9) + 27 * 4);

        param0->unk_A0 = StringList_New(v5, HEAP_ID_109);

        for (v1 = 0; v1 < v5; v1++) {
            StringList_AddFromMessageBank(param0->unk_A0, param0->unk_34, v4[v1].unk_00, v4[v1].unk_04);
        }

        v2.window = &param0->unk_78;
        v2.choices = param0->unk_A0;
        param0->unk_A4 = ListMenu_New(&v2, 0, 0, HEAP_ID_109);

        Window_DrawStandardFrame(&param0->unk_78, 1, 1 + (18 + 12), 11);
        Window_EraseMessageBox(&param0->unk_48, 1);
        Window_CopyToVRAM(&param0->unk_78);
    }

        param0->unk_94++;
        break;
    case 1:
        v0 = ListMenu_ProcessInput(param0->unk_A4);

        switch (v0) {
        case 0xffffffff:
            break;
        case 0xfffffffe:
            Sound_PlayEffect(SE_CONFIRM_sseq_3);
            GTS_SetNextApp(param0->unk_00, 6, 0);
            param0->unk_9C = 29;
            param0->unk_94++;
            break;
        default:
            Sound_PlayEffect(SE_CONFIRM_sseq_3);
            param0->unk_9C = v0;
            param0->unk_94++;
            break;
        }
        break;
    default:
        StringList_Free(param0->unk_A0);
        ListMenu_Free(param0->unk_A4, NULL, NULL);
        Window_EraseStandardFrame(&param0->unk_78, 1);
        Window_ClearAndCopyToVRAM(&param0->unk_78);
        Window_Remove(&param0->unk_78);
        param0->unk_08 = param0->unk_9C;
        break;
    }

    return 0;
}

static int GTSScreen_CheckWiiNumber(GTSScreen *param0)
{
    GTS_SetNextApp(param0->unk_00, 4, 3);
    GTS_SetNextScreen(param0->unk_00, 38);

    param0->unk_08 = 29;
    return 0;
}

static int GTSScreen_SetMessageReception(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 1) {
        return 0;
    }

    switch (param0->unk_94) {
    case 0:
        GTSScreen_PrintMessage(param0, param0->unk_34, 25, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_94++;
        break;
    case 1:
        param0->unk_88 = GTSScreen_MakeYesNoMenu(param0->unk_04, 13, ((((1 + (18 + 12)) + 9) + 27 * 4) + 23 * 16) + 24 * 2);
        param0->unk_94++;
        break;
    case 2: {
        int v0 = Menu_ProcessInputAndHandleExit(param0->unk_88, 109);

        if (v0 != 0xffffffff) {
            if (v0 == 0xfffffffe) {
                GTSScreen_PrintMessage(param0, param0->unk_34, 27, TEXT_SPEED_FAST, 0xf0f);
                Email_SetValue(param0->unk_00->saveData, 0, 0);
            } else {
                GTSScreen_PrintMessage(param0, param0->unk_34, 26, TEXT_SPEED_FAST, 0xf0f);
                Email_SetValue(param0->unk_00->saveData, 0, 1);
            }

            param0->unk_94++;
        }
    } break;
    case 3:
        GTSScreen_SetNextScreen(param0, 25, 0);
        break;
    }

    return 0;
}

static int GTSScreen_DeleteSettings(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 1) {
        return 0;
    }

    switch (param0->unk_94) {
    case 0:
        GTSScreen_PrintMessage(param0, param0->unk_34, 28, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_94++;
        break;
    case 1:
        param0->unk_88 = GTSScreen_MakeYesNoMenuWithCursor(param0->unk_04, 13, ((((1 + (18 + 12)) + 9) + 27 * 4) + 23 * 16) + 24 * 2, 1);
        param0->unk_94++;
        break;
    case 2: {
        int v0 = Menu_ProcessInputAndHandleExit(param0->unk_88, 109);

        if (v0 != 0xffffffff) {
            if (v0 == 0xfffffffe) {
                param0->unk_08 = 0;
            } else {
                GTSScreen_PrintMessage(param0, param0->unk_34, 29, TEXT_SPEED_FAST, 0xf0f);
                Email_InitSaveData(param0->unk_00->saveData);
                param0->unk_94++;
            }
        }
    } break;
    case 3:
        GTSScreen_SetNextScreen(param0, 25, 0);
        break;
    }

    return 0;
}

static const int sTermsLineOffsets[] = {
    44,
    53,
    45,
    46,
    47,
    48,
    53,
    49,
    50,
    53,
    51,
};

static u32 sArrowPositions[][2] = {
    { 0x4, 0x8 },
    { 0x80, 0x8 }
};

static void GTSScreen_DrawScrollArrows(GTSScreen *param0)
{
    String *v0;

    Window_FillTilemap(&param0->unk_D4, 0xf0f);

    v0 = MessageLoader_GetNewString(param0->unk_34, 42);
    Text_AddPrinterWithParams(&param0->unk_D4, FONT_SYSTEM, v0, sArrowPositions[0][0] + 12, sArrowPositions[0][1], TEXT_SPEED_NO_TRANSFER, NULL);
    String_Free(v0);

    v0 = MessageLoader_GetNewString(param0->unk_34, 43);
    Text_AddPrinterWithParams(&param0->unk_D4, FONT_SYSTEM, v0, sArrowPositions[1][0] + 12, sArrowPositions[1][1], TEXT_SPEED_NO_TRANSFER, NULL);
    String_Free(v0);
    ColoredArrow_Print(param0->unk_E4, &param0->unk_D4, sArrowPositions[param0->unk_B0][0], sArrowPositions[param0->unk_B0][1]);
    Window_CopyToVRAM(&param0->unk_D4);
}

static void GTSScreen_ClearScrollArrows(GTSScreen *param0)
{
    Window_FillTilemap(&param0->unk_D4, 0xf0f);
    Window_CopyToVRAM(&param0->unk_D4);
}

static void GTSScreen_AnimateScrollArrows(GTSScreen *param0)
{
    if ((++param0->unk_BC) == 8) {
        param0->unk_C0 ^= 1;
        param0->unk_BC = 0;

        if (param0->unk_AC + 6 != param0->unk_B4) {
            Bg_FillTilemapRect(param0->unk_04, 3, 1 + (param0->unk_C0 * 20), 14, 17, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 2 + (param0->unk_C0 * 20), 15, 17, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 3 + (param0->unk_C0 * 20), 16, 17, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 4 + (param0->unk_C0 * 20), 17, 17, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 11 + (param0->unk_C0 * 20), 14, 18, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 12 + (param0->unk_C0 * 20), 15, 18, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 13 + (param0->unk_C0 * 20), 16, 18, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 14 + (param0->unk_C0 * 20), 17, 18, 1, 1, 9);
        } else {
            Bg_FillTilemapRect(param0->unk_04, 3, 0, 14, 17, 4, 2, 9);
        }

        if (param0->unk_AC != 0) {
            Bg_FillTilemapRect(param0->unk_04, 3, 5 + (param0->unk_C0 * 20), 14, 3, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 6 + (param0->unk_C0 * 20), 15, 3, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 7 + (param0->unk_C0 * 20), 16, 3, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 8 + (param0->unk_C0 * 20), 17, 3, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 15 + (param0->unk_C0 * 20), 14, 4, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 16 + (param0->unk_C0 * 20), 15, 4, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 17 + (param0->unk_C0 * 20), 16, 4, 1, 1, 9);
            Bg_FillTilemapRect(param0->unk_04, 3, 18 + (param0->unk_C0 * 20), 17, 4, 1, 1, 9);
        } else {
            Bg_FillTilemapRect(param0->unk_04, 3, 0, 14, 3, 4, 2, 9);
        }

        Bg_ScheduleTilemapTransfer(param0->unk_04, 3);
    }
}

static void GTSScreen_DrawTermsText(GTSScreen *param0)
{
    int v0;
    int v1 = 0;
    String *v2;
    String *v3;

    Window_FillTilemap(&param0->unk_C4, 0x0f0f);
    v2 = MessageLoader_GetNewString(param0->unk_34, 44);
    v3 = String_Init(String_Length(v2), HEAP_ID_109);
    for (v0 = param0->unk_AC; v0 < param0->unk_AC + 6; v0++) {
        String_CopyLineNum(v3, v2, v0);
        Text_AddPrinterWithParams(&param0->unk_C4, FONT_SYSTEM, v3, 4, v1 * 16, TEXT_SPEED_NO_TRANSFER, NULL);
        v1++;
    }
    String_Free(v2);
    String_Free(v3);
    Window_CopyToVRAM(&param0->unk_C4);
}

static int GTSScreen_TermsScroll(GTSScreen *param0)
{
    switch (param0->unk_A8) {
    case 0:
        int i;

        String *string1 = MessageLoader_GetNewString(param0->unk_34, 44);
        u32 lineCount = String_NumLines(string1);
        param0->unk_AC = 0;
        param0->unk_B0 = 0;
        param0->unk_B8 = 0;
        param0->unk_B4 = lineCount;

        Window_Add(param0->unk_04, &param0->unk_C4, BG_LAYER_MAIN_2, 1, 5, 30, 12, 13, 148);
        Window_Add(param0->unk_04, &param0->unk_D4, BG_LAYER_MAIN_2, 1, 19, 30, 4, 13, 508);

        Window_FillTilemap(&param0->unk_C4, 15);
        String *string2 = String_Init(String_Length(string1), HEAP_ID_109);
        for (i = 0; i < 6; i++) {
            String_CopyLineNum(string2, string1, i);
            Text_AddPrinterWithParams(&param0->unk_C4, FONT_SYSTEM, string2, 4, i * 16, 0xFF, NULL);
        }
        String_Free(string1);
        String_Free(string2);
        Window_DrawStandardFrame(&param0->unk_C4, TRUE, 31, 11);
        Window_CopyToVRAM(&param0->unk_C4);

        Window_FillTilemap(&param0->unk_D4, 15);
        Window_DrawStandardFrame(&param0->unk_D4, TRUE, 31, 11);
        Window_CopyToVRAM(&param0->unk_D4);

        param0->unk_E4 = ColoredArrow_New(HEAP_ID_109);

        Window_FillTilemap(&param0->unk_48, 15);
        Window_EraseMessageBox(&param0->unk_48, TRUE);
        Window_ClearAndCopyToVRAM(&param0->unk_48);

        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, TRUE);

        param0->unk_BC = 0;
        param0->unk_C0 = 0;
        param0->unk_A8++;
        break;
    case 1:
        int v1 = param0->unk_AC;

        if (JOY_REPEAT(PAD_KEY_UP)) {
            if (param0->unk_AC != 0) {
                param0->unk_AC--;
                Sound_PlayEffect(SE_CONFIRM_sseq_3);
            }
        } else if (JOY_REPEAT(PAD_KEY_DOWN)) {
            if (param0->unk_AC + 6 < param0->unk_B4) {
                param0->unk_AC++;
                Sound_PlayEffect(SE_CONFIRM_sseq_3);
            }

            if (param0->unk_AC + 6 == param0->unk_B4) {
                GTSScreen_DrawScrollArrows(param0);
                param0->unk_A8++;
                Sound_PlayEffect(SE_CONFIRM_sseq_3);
            }
        } else if (gSystem.pressedKeys & PAD_BUTTON_B) {
            Sound_PlayEffect(SE_CONFIRM_sseq_3);
            param0->unk_B8 = 2;
            param0->unk_A8 = 0xFF;
        }

        if (v1 != param0->unk_AC) {
            GTSScreen_DrawTermsText(param0);
        }

        break;
    case 2:
        if (gSystem.pressedKeys & PAD_KEY_RIGHT || gSystem.pressedKeys & PAD_KEY_LEFT) {
            param0->unk_B0 ^= 1;
            Sound_PlayEffect(SE_CONFIRM_sseq_3);
            GTSScreen_DrawScrollArrows(param0);
        } else if (gSystem.pressedKeys & PAD_BUTTON_A) {
            param0->unk_B8 = 2 - param0->unk_B0;
            Sound_PlayEffect(SE_CONFIRM_sseq_3);
            param0->unk_A8++;
        } else if (gSystem.pressedKeys & PAD_BUTTON_B) {
            param0->unk_B8 = 2;
            Sound_PlayEffect(SE_CONFIRM_sseq_3);
            param0->unk_A8++;
        } else if (gSystem.pressedKeys & PAD_KEY_UP) {
            GTSScreen_ClearScrollArrows(param0);
            Sound_PlayEffect(SE_CONFIRM_sseq_3);
            param0->unk_A8--;
            param0->unk_AC--;
            GTSScreen_DrawTermsText(param0);
        }

        break;
    default:
        Window_EraseStandardFrame(&param0->unk_C4, 0);
        Window_ClearAndCopyToVRAM(&param0->unk_C4);
        Window_Remove(&param0->unk_C4);

        Window_EraseStandardFrame(&param0->unk_D4, 0);
        Window_ClearAndCopyToVRAM(&param0->unk_D4);
        Window_Remove(&param0->unk_D4);

        ColoredArrow_Free(param0->unk_E4);

        Bg_ClearTilemap(param0->unk_04, BG_LAYER_MAIN_3);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, FALSE);

        param0->unk_A8 = 0;
        return param0->unk_B8;
    }

    GTSScreen_AnimateScrollArrows(param0);
    return 0;
}

static int GTSScreen_RegisterWiiNumber(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 1) {
        return 0;
    }

    switch (param0->unk_94) {
    case 0:
        param0->unk_94 = 3;
        break;
    case 1:
        param0->unk_94++;
        break;
    case 2: {
        int v0 = Menu_ProcessInputAndHandleExit(param0->unk_88, 109);

        if (v0 != 0xffffffff) {
            if (v0 == 0xfffffffe) {
                param0->unk_94++;
            } else {
                GTSScreen_PrintMessage(param0, param0->unk_34, 9, TEXT_SPEED_FAST, 0xf0f);
                param0->unk_94 = 4;
            }
        }
    } break;
    case 3: {
        int v1 = GTSScreen_TermsScroll(param0);

        if (v1 == 1) {
            GTSScreen_PrintMessage(param0, param0->unk_34, 9, TEXT_SPEED_FAST, 0xf0f);
            param0->unk_94++;
        } else if (v1 == 2) {
            GTSScreen_SetNextScreen(param0, 34, 0);
        }
    } break;
    case 4:
        param0->unk_88 = GTSScreen_MakeYesNoMenu(param0->unk_04, 13, ((((1 + (18 + 12)) + 9) + 27 * 4) + 23 * 16) + 24 * 2);
        param0->unk_94++;
        break;
    default: {
        int v2 = Menu_ProcessInputAndHandleExit(param0->unk_88, 109);

        if (v2 != 0xffffffff) {
            if (v2 == 0xfffffffe) {
                GTSScreen_PrintMessage(param0, param0->unk_34, 10, TEXT_SPEED_FAST, 0xf0f);
                GTSScreen_SetNextScreen(param0, 34, 0);
            } else {
                param0->unk_08 = 5;
            }
        }
    } break;
    }

    return 0;
}

static int GTSScreen_StartEmailEntry(GTSScreen *param0)
{
    GTS_SetNextApp(param0->unk_00, 1, 0);
    GTS_SetNextScreen(param0->unk_00, 6);
    param0->unk_08 = 29;
    return 0;
}

static int GTSScreen_EmailEntryResult(GTSScreen *param0)
{
    charcode_t *v0;
    switch (GTS_GetResult(param0->unk_00)) {
    case 1:
        param0->unk_08 = 0;
        return 0;
    case 2:
    case 3:
        param0->unk_08 = 37;
        return 0;
    }

    if (param0->unk_94 == 0) {
        param0->unk_08 = 7;
    }

    return 0;
}

static int GTSScreen_ConfirmWiiNumber(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 1) {
        return 0;
    }

    switch (param0->unk_94) {
    case 0:
        param0->unk_94++;
        break;
    case 1:
        GTSScreen_PrintMessage(param0, param0->unk_34, 11, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_94++;
        break;
    case 2:
        param0->unk_88 = GTSScreen_MakeYesNoMenu(param0->unk_04, 13, ((((1 + (18 + 12)) + 9) + 27 * 4) + 23 * 16) + 24 * 2);
        param0->unk_94++;
        break;
    case 3: {
        int v0 = Menu_ProcessInputAndHandleExit(param0->unk_88, 109);

        if (v0 != 0xffffffff) {
            if (v0 == 0xfffffffe) {
                GTSScreen_SetNextScreen(param0, 34, 0);
            } else {
                param0->unk_94++;
            }
        }
    } break;
    case 4:
        if (WiFiList_HasValidLogin(param0->unk_00->saveData) == 0) {
            GTS_SetNextApp(param0->unk_00, 5, 0);
            GTS_SetNextScreen(param0->unk_00, 12);
            param0->unk_08 = 29;
            return 0;
        }

        GTSScreen_SetNextScreen(param0, 34, 12);
        break;
    }

    return 0;
}

static int GTSScreen_ConfirmConnect(GTSScreen *param0)
{
    int v0 = Menu_ProcessInputAndHandleExit(param0->unk_88, 109);

    if (v0 != 0xffffffff) {
        if (v0 == 0xfffffffe) {
            CommManager_EndWifiMail();
            GTS_SetNextApp(param0->unk_00, 6, 0);
            param0->unk_08 = 29;
        } else {
            GTSScreen_PrintMessage(param0, param0->unk_2C, 1, TEXT_SPEED_FAST, 0xf0f);
            GTSScreen_SetNextScreen(param0, 34, 12);
            GTSScreen_AddWaitDial(param0);
        }
    }

    return 0;
}

static int GTSScreen_ShowDisconnecting(GTSScreen *param0)
{
    GTSScreen_PrintMessage(param0, param0->unk_30, 26, TEXT_SPEED_FAST, 0xf0f);
    GTSScreen_SetNextScreen(param0, 34, 10);

    return 0;
}

static int GTSScreen_Disconnect(GTSScreen *param0)
{
    CommManager_EndWifiMail();

    DWC_CleanupInet();

    NetworkIcon_Destroy();
    SleepUnlock(4);

    if (param0->unk_00->unk_11C == 1) {
        GTSNetworking_Reset();
        param0->unk_00->unk_11C = 0;
    }

    param0->unk_08 = 11;

    return 0;
}

static int GTSScreen_ShowDisconnected(GTSScreen *param0)
{
    GTSScreen_PrintMessage(param0, param0->unk_30, 27, TEXT_SPEED_FAST, 0xf0f);
    GTSScreen_SetNextScreen(param0, 35, 29);

    return 0;
}

static int GTSScreen_ConnectWifi(GTSScreen *param0)
{
    switch (param0->unk_94) {
    case 0:
        CommManager_StartWifiMail(param0->unk_00->saveData);
        NetworkIcon_Init();
        GTSScreen_PrintMessage(param0, param0->unk_2C, 1, TEXT_SPEED_FAST, 0xf0f);
        GTSScreen_AddWaitDial(param0);
        param0->unk_94++;
        break;
    case 1:
        if (GTSScreen_IsPrinterActive(param0->unk_44) == 0) {
            param0->unk_94++;
        }
        break;
    case 2:
        SleepLock(4);

        DWC_InitInetEx(&param0->unk_00->unk_14, DEFAULT_DWC_DMA_NUMBER, DEFAULT_DWC_POWER_MODE, DEFAULT_DWC_SSL_PRIORITY);
        DWC_SetAuthServer(DWC_CONNECTINET_AUTH_RELEASE);
        DWC_ConnectInetAsync();
        param0->unk_08 = 13;
        break;
    }

    return 0;
}

static int GTSScreen_WaitConnect(GTSScreen *param0)
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

            NetworkIcon_Destroy();
            CommManager_EndWifiMail();
            SleepUnlock(4);

            if (param0->unk_00->unk_11C == 1) {
                GTSNetworking_Reset();
                param0->unk_00->unk_11C = 0;
            }

            GTSScreen_DestroyWaitDial(param0);
            param0->unk_08 = 27;
            break;
        case DWC_CONNECTINET_STATE_NOT_INITIALIZED:
        case DWC_CONNECTINET_STATE_IDLE:
        case DWC_CONNECTINET_STATE_OPERATING:
        case DWC_CONNECTINET_STATE_OPERATED:
        case DWC_CONNECTINET_STATE_DISCONNECTING:
        case DWC_CONNECTINET_STATE_DISCONNECTED:
        default:
        case DWC_CONNECTINET_STATE_FATAL_ERROR: {
            DWCError v3;
            int v4;

            v3 = DWC_GetLastError(&v4);

            GTSScreen_DestroyWaitDial(param0);
            param0->unk_08 = 32;
            param0->unk_10 = -2;
        } break;
        case DWC_CONNECTINET_STATE_CONNECTED: {
            DWCApInfo v5;
            DWC_GetApInfo(&v5);

            if (v5.aptype == DWC_APINFO_TYPE_SHOP) {
                (void)0;
            }
        }

            param0->unk_08 = 14;
            break;
        }
    }

    return 0;
}

static int GTSScreen_StartNasLogin(GTSScreen *param0)
{
    DWC_NASLoginAsync();

    param0->unk_08 = 15;
    return 0;
}

static int GTSScreen_WaitNasLogin(GTSScreen *param0)
{
    switch (DWC_NASLoginProcess()) {
    case DWC_NASLOGIN_STATE_SUCCESS:;
        param0->unk_08 = 16;
        break;
    case DWC_NASLOGIN_STATE_ERROR:
    case DWC_NASLOGIN_STATE_CANCELED:
    case DWC_NASLOGIN_STATE_DIRTY:
        GTSScreen_DestroyWaitDial(param0);
        {
            int v0;
            DWCErrorType v1;
            DWCError v2;

            v2 = DWC_GetLastErrorEx(&v0, &v1);
            param0->unk_14 = v2;
            param0->unk_18 = v0;

            DWC_ClearError();
            DWC_CleanupInet();

            NetworkIcon_Destroy();
            CommManager_EndWifiMail();
            SleepUnlock(4);

            if (param0->unk_00->unk_11C == 1) {
                GTSNetworking_Reset();
                param0->unk_00->unk_11C = 0;
            }

            param0->unk_08 = 27;

            switch (v1) {
            case DWC_ETYPE_LIGHT:
            case DWC_ETYPE_SHOW_ERROR:
                param0->unk_08 = 27;
                break;
            case DWC_ETYPE_SHUTDOWN_GHTTP:
                DWC_ShutdownGHTTP();
                param0->unk_08 = 27;
                break;
            case DWC_ETYPE_DISCONNECT:
                param0->unk_08 = 27;
                break;
            case DWC_ETYPE_SHUTDOWN_FM:
                DWC_ShutdownFriendsMatch();
                param0->unk_08 = 27;
                break;
            case DWC_ETYPE_SHUTDOWN_ND:
            case DWC_ETYPE_FATAL:
                NetworkError_DisplayGTSCriticalError();
                break;
            }

            if ((v0 < -20000) && (v0 >= -29999)) {
                param0->unk_08 = 27;
            }
        }
        break;
    }

    return 0;
}

static int GTSScreen_InitCredentials(GTSScreen *param0)
{
    DWCUserData *v0;
    s32 v1;
    WiFiList *v3 = SaveData_GetWiFiList(param0->unk_00->saveData);
    SystemData *v2 = SaveData_GetSystemData(param0->unk_00->saveData);
    v0 = WiFiList_GetUserData(v3);
    v1 = SystemData_GetDWCProfileId(v2);

    if (v1 == 0) {
        SystemData_SetDWCProfileId(v2, WiFiList_GetUserGsProfileId(v3));
    }

    v1 = SystemData_GetDWCProfileId(v2);

    GTSNetworking_InitCredentials(v1, DWC_CreateFriendKey(v0));

    param0->unk_00->unk_11C = 1;
    param0->unk_08 = 17;

    return 0;
}

static int GTSScreen_SetProfile(GTSScreen *param0)
{
    GTS_InitTrainer(param0->unk_00);
    GTS_LoadTrainerEmail(param0->unk_00);
    GTSNetworking_SetProfile(&param0->unk_00->unk_9C, &param0->unk_00->unk_100);

    param0->unk_08 = 18;
    param0->unk_E8 = 0;

    return 0;
}

static int GTSScreen_WaitSetProfile(GTSScreen *param0)
{
    if (GTSNetworking_RequestComplete()) {
        s32 v0 = GTSNetworking_GetErrorCode();

        param0->unk_E8 = 0;

        switch (v0) {
        case 0:
            switch (param0->unk_00->unk_100.validationError) {
            case 0:
                switch (param0->unk_00->unk_100.systemError) {
                case 1:
                    param0->unk_08 = 19;
                    break;
                case 2:
                    GTSScreen_DestroyWaitDial(param0);
                    param0->unk_10 = -5001;
                    param0->unk_08 = 32;
                    break;

                case 0:
                    GTSScreen_DestroyWaitDial(param0);
                    param0->unk_10 = -5002;
                    param0->unk_08 = 32;
                    break;
                case 3:
                    GTSScreen_DestroyWaitDial(param0);
                    param0->unk_10 = -5003;
                    param0->unk_08 = 32;
                    break;
                default:
                    NetworkError_DisplayGTSCriticalError();
                    break;
                }

                break;
            case 1:
                GTSScreen_DestroyWaitDial(param0);
                param0->unk_10 = -5004;
                param0->unk_08 = 32;
                break;
            case 2:
                GTSScreen_DestroyWaitDial(param0);
                param0->unk_10 = -5005;
                param0->unk_08 = 32;
                break;
            default:
                GTSScreen_DestroyWaitDial(param0);
                NetworkError_DisplayGTSCriticalError();
                break;
            }

            break;
        case 1:
            GTSScreen_DestroyWaitDial(param0);
            param0->unk_10 = v0;
            param0->unk_08 = 32;
            break;
        case 2:
        case -1:
            GTSScreen_DestroyWaitDial(param0);
            param0->unk_10 = v0;
            param0->unk_08 = 32;
            break;
        case -12:
        case -15:
            GTSScreen_DestroyWaitDial(param0);
            param0->unk_10 = v0;
            param0->unk_08 = 32;
            break;
        case -2:
        case -14:
            GTSScreen_DestroyWaitDial(param0);
            param0->unk_10 = v0;
            param0->unk_08 = 32;
            break;
        case -13:
        default:
            GTSScreen_DestroyWaitDial(param0);
            NetworkError_DisplayGTSCriticalError();
            break;
        }
    } else {
        param0->unk_E8++;

        if (param0->unk_E8 == NETWORK_TIMEOUT_FRAMES) {
            NetworkError_DisplayGTSCriticalError();
        }
    }

    return 0;
}

static int GTSScreen_ShowCodeSent(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 1) {
        return 0;
    }

    switch (param0->unk_94) {
    case 0:
        GTSScreen_DestroyWaitDial(param0);
        GTSScreen_PrintMessage(param0, param0->unk_34, 13, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_94++;
        break;
    case 1:
        param0->unk_88 = GTSScreen_MakeYesNoMenu(param0->unk_04, 13, ((((1 + (18 + 12)) + 9) + 27 * 4) + 23 * 16) + 24 * 2);
        param0->unk_94++;
        break;
    case 2: {
        int v0 = Menu_ProcessInputAndHandleExit(param0->unk_88, 109);

        if (v0 != 0xffffffff) {
            if (v0 == 0xfffffffe) {
                param0->unk_08 = 21;
            } else {
                param0->unk_94++;
            }
        }
    } break;
    case 3:

        GTSScreen_PrintMessage(param0, param0->unk_34, 17, TEXT_SPEED_FAST, 0xf0f);
        GTSScreen_SetNextScreen(param0, 34, 20);
        break;
    }

    return 0;
}

static int GTSScreen_StartCodeEntry(GTSScreen *param0)
{
    GTS_SetNextApp(param0->unk_00, 2, 1);
    GTS_SetNextScreen(param0->unk_00, 22);
    param0->unk_08 = 30;
    return 0;
}

static int GTSScreen_ConfirmCancelRegistration(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 1) {
        return 0;
    }

    switch (param0->unk_94) {
    case 0:
        GTSScreen_PrintMessage(param0, param0->unk_34, 14, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_94++;
        break;
    case 1:
        param0->unk_88 = GTSScreen_MakeYesNoMenu(param0->unk_04, 13, ((((1 + (18 + 12)) + 9) + 27 * 4) + 23 * 16) + 24 * 2);
        param0->unk_94++;
        break;
    case 2: {
        int v0 = Menu_ProcessInputAndHandleExit(param0->unk_88, 109);

        if (v0 != 0xffffffff) {
            if (v0 == 0xfffffffe) {
                param0->unk_08 = 19;
            } else {
                GTSScreen_SetNextScreen(param0, 26, 0);
            }
        }
    } break;
    }

    return 0;
}

static int GTSScreen_RegisterCode(GTSScreen *param0)
{
    if (GTS_GetRegistrationCode(param0->unk_00) == 0xffffffff) {
        param0->unk_08 = 21;
        return 0;
    }

    switch (param0->unk_94) {
    case 0:

        GTSScreen_PrintMessage(param0, param0->unk_34, 18, TEXT_SPEED_INSTANT, 0xf0f);
        GTSScreen_AddWaitDial(param0);
        GTS_SetRegistrationCode(param0->unk_00);
        GTSNetworking_SetProfile(&param0->unk_00->unk_9C, &param0->unk_00->unk_100);
        param0->unk_94++;
        break;
    case 1:
        if (GTSNetworking_RequestComplete()) {
            s32 v0 = GTSNetworking_GetErrorCode();

            param0->unk_E8 = 0;
            GTSScreen_DestroyWaitDial(param0);

            switch (v0) {
            case 0:
                switch (param0->unk_00->unk_100.validationError) {
                case 0:
                    switch (param0->unk_00->unk_100.systemError) {
                    case 0:
                        param0->unk_94++;
                        break;
                    case 3:
                        GTSScreen_PrintMessage(param0, param0->unk_34, 19, TEXT_SPEED_FAST, 0xf0f);
                        GTSScreen_SetNextScreen(param0, 34, 21);
                        break;
                    case 1:
                        param0->unk_10 = -5006;
                        param0->unk_08 = 32;
                        break;
                    case 2:
                        param0->unk_10 = -5007;
                        param0->unk_08 = 32;
                        break;
                    default:
                        NetworkError_DisplayGTSCriticalError();
                        break;
                    }
                    break;
                case 1:
                    param0->unk_10 = -5010;
                    param0->unk_08 = 32;
                    break;
                case 2:
                    param0->unk_10 = -5011;
                    param0->unk_08 = 32;
                    break;
                default:
                    GF_ASSERT(FALSE);
                    NetworkError_DisplayGTSCriticalError();
                    break;
                }
                break;
            case 1:
                param0->unk_10 = v0;
                param0->unk_08 = 32;
                break;
            case 2:
            case -1:
                param0->unk_10 = v0;
                param0->unk_08 = 32;
                break;
            case -12:
            case -15:
                param0->unk_10 = v0;
                param0->unk_08 = 32;
                break;
            case -2:
            case -14:
                param0->unk_10 = v0;
                param0->unk_08 = 32;
                break;
            case -13:
            default:
                NetworkError_DisplayGTSCriticalError();
                break;
            }
        } else {
            param0->unk_E8++;

            if (param0->unk_E8 == NETWORK_TIMEOUT_FRAMES) {
                NetworkError_DisplayGTSCriticalError();
            }
        }
        break;
    case 2:
        GTSScreen_PrintMessage(param0, param0->unk_34, 20, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_94++;
        break;
    case 3:
        if (GTSScreen_IsPrinterActive(param0->unk_44) == 0) {
            GTSScreen_SetNextScreen(param0, 26, 23);
        }
        break;
    }

    return 0;
}

static int GTSScreen_StartNumberEntry(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 1) {
        return 0;
    }

    switch (param0->unk_94) {
    case 0:
        GTSScreen_PrintMessage(param0, param0->unk_34, 21, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_94++;
        break;
    case 1:
        GTS_SetNextApp(param0->unk_00, 3, 2);
        GTS_SetNextScreen(param0->unk_00, 24);
        param0->unk_08 = 30;
        break;
    }

    return 0;
}

static int GTSScreen_SaveEmail(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 1) {
        return 0;
    }

    switch (param0->unk_94) {
    case 0:
        GTSScreen_PrintMessage(param0, param0->unk_34, 24, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_94++;
        break;
    case 1:
        GTS_SaveEmailString(param0->unk_00);
        GTS_SaveRegistrationValues(param0->unk_00);
        GTS_SaveEmailValue(param0->unk_00);
        GTSScreen_SetNextScreen(param0, 25, 0);
        break;
    }

    return 0;
}

static int GTSScreen_SaveData(GTSScreen *param0)
{
    switch (param0->unk_94) {
    case 0:
        GTSScreen_PrintMessage(param0, param0->unk_34, 32, TEXT_SPEED_INSTANT, 0xf0f);
        GTSScreen_AddWaitDial(param0);
        param0->unk_94++;
        break;
    case 1: {
        int v0;

        v0 = SaveData_Save(param0->unk_00->saveData);

        if (v0 == 2) {
            StringTemplate_SetPlayerName(param0->unk_20, 0, SaveData_GetTrainerInfo(param0->unk_00->saveData));
            GTSScreen_PrintMessage(param0, param0->unk_34, 33, TEXT_SPEED_INSTANT, 0xf0f);
            Sound_PlayEffect(SEQ_SE_DP_SAVE_sseq);
        } else {
            GTSScreen_PrintMessage(param0, param0->unk_34, 34, TEXT_SPEED_INSTANT, 0xf0f);
        }

        GTSScreen_DestroyWaitDial(param0);
        param0->unk_94++;
    } break;
    case 2:
        if (GTSScreen_IsPrinterActive(param0->unk_44) == 0) {
            param0->unk_94++;
        }
        break;
    case 3:
        param0->unk_98++;

        if (param0->unk_98 > 60) {
            param0->unk_98 = 0;
            param0->unk_08 = param0->unk_0C;
        }
        break;
    }

    return 0;
}

static int GTSScreen_DisconnectWithMessage(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 1) {
        return 0;
    }

    switch (param0->unk_94) {
    case 0:
        GTSScreen_PrintMessage(param0, param0->unk_34, 15, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_94++;
        break;
    case 1:

        DWC_CleanupInet();

        NetworkIcon_Destroy();
        CommManager_EndWifiMail();
        SleepUnlock(4);

        if (param0->unk_00->unk_11C == 1) {
            GTSNetworking_Reset();
            param0->unk_00->unk_11C = 0;
        }

        param0->unk_94++;
        break;
    case 2:
        if (GTSScreen_IsPrinterActive(param0->unk_44) == 0) {
            GTSScreen_PrintMessage(param0, param0->unk_34, 16, TEXT_SPEED_FAST, 0xf0f);
            param0->unk_94++;
        }
        break;
    case 3:
        if (GTSScreen_IsPrinterActive(param0->unk_44) == 0) {
            param0->unk_94++;
        }
        break;
    case 4:
        param0->unk_90++;

        if (param0->unk_90 > 30) {
            param0->unk_08 = param0->unk_0C;
        }
        break;
    }

    return 0;
}

static int GTSScreen_ShowError(GTSScreen *param0)
{
    int v0 = NintendoWFC_GetErrorCode(-param0->unk_18, param0->unk_1C);

    GTSScreen_PrintError(param0, v0, -param0->unk_18);

    param0->unk_08 = 28;

    return 0;
}

static int GTSScreen_WaitErrorAck(GTSScreen *param0)
{
    if (gSystem.pressedKeys & PAD_BUTTON_A || gSystem.pressedKeys & PAD_BUTTON_B) {
        Window_EraseStandardFrame(&param0->unk_68, 0);
        param0->unk_08 = 0;
    }

    return 0;
}

static int GTSScreen_Finish(GTSScreen *param0)
{
    if (param0->unk_08 != 30) {
        CommManager_EndWifiMail();
    }

    NetworkIcon_Destroy();
    GTSScreen_DestroyWaitDial(param0);
    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_109);

    param0->unk_08 = 0;

    return 1;
}

static int GTSScreen_ShowYesNo(GTSScreen *param0)
{
    param0->unk_88 = GTSScreen_MakeYesNoMenu(param0->unk_04, 13, ((((1 + (18 + 12)) + 9) + 27 * 4) + 23 * 16) + 24 * 2);
    param0->unk_08 = param0->unk_0C;

    return 0;
}

static int GTSScreen_ShowErrorCode(GTSScreen *param0)
{
    int v0 = 0;
    int v1 = 0;

    switch (param0->unk_10) {
    case 1:
        v0 = 54;
        break;
    case 2:
    case -1:
        v0 = 55;
        break;
    case -2:
    case -14:
        v0 = 57;
        break;
    case -12:
    case -15:
    case -3:
    case -5:
    default:
        v0 = 56;
        break;
    case -5001:
        v0 = 173;
        v1++;
        break;
    case -5002:
        v0 = 174;
        v1++;
        break;
    case -5003:
        v0 = 174;
        v1++;
        break;
    case -5004:
        v0 = 175;
        v1++;
        break;
    case -5005:
        v0 = 176;
        v1++;
        break;
    case -5006:
        v0 = 174;
        v1++;
        break;
    case -5007:
        v0 = 174;
        v1++;
        break;
    case -5010:
        v0 = 175;
        v1++;
        break;
    case -5011:
        v0 = 176;
        v1++;
        break;
    }

    if (v1 == 0) {
        GTSScreen_PrintMessage(param0, param0->unk_34, v0, TEXT_SPEED_FAST, 0xf0f);
    } else {
        GTSScreen_PrintMessage(param0, param0->unk_24, v0, TEXT_SPEED_FAST, 0xf0f);
    }

    GTSScreen_SetNextScreen(param0, 34, 33);

    return 0;
}

static int GTSScreen_DisconnectAndExit(GTSScreen *param0)
{
    switch (param0->unk_94) {
    case 0:
        GTSScreen_PrintMessage(param0, param0->unk_34, 15, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_94++;
        break;
    case 1:
        if (GTSScreen_IsPrinterActive(param0->unk_44) == 0) {
            CommManager_EndWifiMail();

            DWC_CleanupInet();

            NetworkIcon_Destroy();
            SleepUnlock(4);

            if (param0->unk_00->unk_11C == 1) {
                GTSNetworking_Reset();
                param0->unk_00->unk_11C = 0;
            }

            param0->unk_94++;
        }
        break;
    case 2:
        GTSScreen_PrintMessage(param0, param0->unk_34, 16, TEXT_SPEED_FAST, 0xf0f);
        param0->unk_94++;
        break;
    case 3:
        if (GTSScreen_IsPrinterActive(param0->unk_44) == 0) {
            param0->unk_94++;
        }
        break;
    default:
        param0->unk_90++;

        if (param0->unk_90 > 30) {
            GTS_RequestExit(param0->unk_00);
            param0->unk_08 = 29;
        }
        break;
    }

    return 0;
}

static int GTSScreen_WaitForPrinter(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 0) {
        param0->unk_08 = param0->unk_0C;
    }

    return 0;
}

static int GTSScreen_WaitForPrinterAndAdvance(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 0) {
        if (param0->unk_90 > 30) {
            param0->unk_08 = param0->unk_0C;
        }

        param0->unk_90++;
    }

    return 0;
}

static int GTSScreen_ShowYesNoAfterPrint(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 0) {
        param0->unk_88 = GTSScreen_MakeYesNoMenu(param0->unk_04, 13, ((((1 + (18 + 12)) + 9) + 27 * 4) + 23 * 16) + 24 * 2);
        param0->unk_08 = param0->unk_0C;
    }

    return 0;
}

static void GTSScreen_PrintMessage(GTSScreen *param0, MessageLoader *param1, int param2, int param3, u16 param4)
{
    String *v0 = MessageLoader_GetNewString(param1, param2);

    StringTemplate_Format(param0->unk_20, param0->unk_38, v0);
    String_Free(v0);
    Window_FillTilemap(&param0->unk_48, 0xf0f);
    Window_DrawMessageBoxWithScrollCursor(&param0->unk_48, 0, 1, 10);

    param0->unk_44 = Text_AddPrinterWithParams(&param0->unk_48, FONT_MESSAGE, param0->unk_38, 0, 0, param3, NULL);
    param0->unk_90 = 0;

    if ((param3 == 0xff) || (param3 == 0)) {
        param0->unk_44 = 0xff;
    }
}

static int GTSScreen_IsPrinterActive(int param0)
{
    if ((param0 == 0xff) || (Text_IsPrinterActive(param0) == 0)) {
        return 0;
    }

    return 1;
}

static int GTSScreen_ReenterWiiNumber(GTSScreen *param0)
{
    if (GTSScreen_IsPrinterActive(param0->unk_44) == 1) {
        return 0;
    }

    switch (param0->unk_94) {
    case 0:
        GTSScreen_PrintMessage(param0, param0->unk_34, GTS_GetResult(param0->unk_00) == 2 ? 0x26 : 0x27, TEXT_SPEED_FAST, 0x0F0F);
        param0->unk_94++;
        break;
    case 1:
        param0->unk_08 = 5;
        break;
    }

    return 0;
}

static int GTSScreen_ShowWiiNumber(GTSScreen *param0)
{
    GTSState *v0 = param0->unk_00;
    int v1;
    u32 v2[4];
    u32 v3;

    if (GTSScreen_IsPrinterActive(param0->unk_44) == 1) {
        return 0;
    }

    switch (param0->unk_94) {
    case 0:
        if (GTS_GetEmailValue(v0) == Email_GetValue(v0->saveData, 3)) {
            GTSEmail_ParseNumbers(Email_GetEmailString(v0->saveData), v2, 108);
            for (v3 = 0; v3 < 4; v3++) {
                StringTemplate_SetNumber(param0->unk_20, v3, v2[v3], 4, 2, 1);
            }
            v1 = 41;
        } else {
            v1 = 40;
        }
        GTSScreen_PrintMessage(param0, param0->unk_34, v1, TEXT_SPEED_FAST, 0x0F0F);
        param0->unk_94++;
        break;
    case 1:
        param0->unk_08 = 0;
        break;
    }

    return 0;
}

static int GTSScreen_AlignText(Window *param0, String *param1, int param2, int param3, u32 param4, int param5)
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

void GTSScreen_PrintCenteredText(Window *param0, String *param1, int param2, int param3, int param4, TextColor param5)
{
    param2 = GTSScreen_AlignText(param0, param1, param2, param4, param5, 1);
    Text_AddPrinterWithParamsAndColor(param0, FONT_MESSAGE, param1, param2, param3, TEXT_SPEED_INSTANT, param5, NULL);
}

static void GTSScreen_PrintErrorBox(GTSScreen *param0, int param1)
{
    String *v0 = String_Init(16 * 8 * 2, HEAP_ID_109);

    MessageLoader_GetString(param0->unk_30, param1, v0);
    StringTemplate_Format(param0->unk_20, param0->unk_40, v0);

    Window_FillTilemap(&param0->unk_68, 15);
    Window_DrawStandardFrame(&param0->unk_68, 1, 1 + (18 + 12), 11);

    param0->unk_44 = Text_AddPrinterWithParams(&param0->unk_68, FONT_MESSAGE, param0->unk_40, 0, 0, TEXT_SPEED_INSTANT, NULL);
    param0->unk_44 = 0xff;

    String_Free(v0);
}

static void GTSScreen_PrintError(GTSScreen *param0, int param1, int param2)
{
    int v0;

    if (param1 != -1) {
        v0 = 0 + param1;
    } else {
        v0 = 11;
    }

    StringTemplate_SetNumber(param0->unk_20, 0, param2, 5, 2, 1);

    Window_EraseMessageBox(&param0->unk_48, 1);
    GTSScreen_PrintErrorBox(param0, v0);
}

static void GTSScreen_ListMenuSoundCallback(ListMenu *param0, u32 param1, u8 param2)
{
    if (param2 == 0) {
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
    }
}

static void GTSScreen_ListMenuSoundCallback2(ListMenu *param0, u32 param1, u8 param2)
{
    if (param2 == 0) {
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
    }
}
