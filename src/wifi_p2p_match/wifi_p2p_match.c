#include "wifi_p2p_match/wifi_p2p_match.h"

#include <nitro.h>
#include <string.h>

#include "generated/trainer_score_events.h"

#include "overlay061/struct_ov61_0222C3B0.h"
#include "overlay065/struct_ov65_0222F6EC.h"
#include "overlay066/ov66_0222DDF0.h"
#include "overlay066/ov66_02231428.h"
#include "overlay066/ov66_022324F0.h"
#include "overlay066/struct_ov66_02231024.h"
#include "overlay066/struct_ov66_02231300.h"

#include "bg_window.h"
#include "comm_manager.h"
#include "font.h"
#include "game_options.h"
#include "game_records.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "inlines.h"
#include "menu.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "render_window.h"
#include "rtc.h"
#include "save_player.h"
#include "savedata.h"
#include "screen_fade.h"
#include "sound.h"
#include "string_gf.h"
#include "string_template.h"
#include "system.h"
#include "text.h"

typedef struct {
    StringTemplate *stringTemplate;
    MessageLoader *messageLoader;
    Window window;
    String *formattedString;
    String *messageString;
    u32 windowType;
    void *waitDial;
    u32 textFrameDelay;
    u32 printer;
} WifiP2PMatchMessageBox;

typedef struct {
    SaveData *saveData;
    u32 unk_04; // unused
    u32 timer;
    BgConfig *bgConfig;
    WifiP2PMatchMessageBox titleBox;
    WifiP2PMatchMessageBox messageBox;
    WifiP2PMatchMessageBox connectBox;
    WifiP2PMatchMessageBox errorBox;
    Menu *menu;
    UnkStruct_ov61_0222C3B0 paletteBlend;
} WifiP2PMatch;

static void WifiP2PMatch_VBlankCallback(void *param0);
static void WifiP2PMatch_InitGraphics(WifiP2PMatch *param0, enum HeapID heapID);
static void WifiP2PMatch_FreeBackgrounds(WifiP2PMatch *param0);
static void WifiP2PMatch_UpdateBackgrounds(WifiP2PMatch *param0);
static void WifiP2PMatch_InitMessageBox(WifiP2PMatchMessageBox *param0, BgConfig *param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, SaveData *saveData, enum HeapID heapID);
static void WifiP2PMatch_PrintMessage(WifiP2PMatchMessageBox *param0, u32 param1);
static void WifiP2PMatch_EraseMessageBox(WifiP2PMatchMessageBox *param0);
static void WifiP2PMatch_AddWaitDial(WifiP2PMatchMessageBox *param0);
static void WifiP2PMatch_DestroyWaitDial(WifiP2PMatchMessageBox *param0);
static void WifiP2PMatch_SetMessageNumber(WifiP2PMatchMessageBox *param0, u32 param1);
static void WifiP2PMatch_FreeMessageBox(WifiP2PMatchMessageBox *param0);
static void WifiP2PMatch_PrintCenteredMessage(WifiP2PMatchMessageBox *param0, u32 param1);

static const GXBanks sGXBanks = {
    GX_VRAM_BG_128_A,
    GX_VRAM_BGEXTPLTT_NONE,
    GX_VRAM_SUB_BG_128_C,
    GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_128_B,
    GX_VRAM_OBJEXTPLTT_NONE,
    GX_VRAM_SUB_OBJ_NONE,
    GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE,
    GX_VRAM_TEXPLTT_NONE
};

static const GraphicsModes sGraphicsModes = {
    GX_DISPMODE_GRAPHICS,
    GX_BGMODE_0,
    GX_BGMODE_0,
    GX_BG0_AS_2D
};

static const u32 sBgLayers[3] = {
    0x0,
    0x1,
    0x4
};

static const BgTemplate sBgTemplates[3] = {
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x1,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe000,
        .charBase = GX_BG_CHARBASE_0x10000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
};

static const WindowTemplate sYesNoWindowTemplate = {
    0x1,
    0x19,
    0xD,
    0x6,
    0x4,
    0xC,
    0x204
};

int WifiP2PMatch_InitConnect(ApplicationManager *appMan, int *param1)
{
    WifiP2PMatch *v0;
    UnkStruct_ov66_02231024 *v1;

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_112, 0x20000);

    v0 = ApplicationManager_NewData(appMan, sizeof(WifiP2PMatch), HEAP_ID_112);
    memset(v0, 0, sizeof(WifiP2PMatch));
    v1 = ApplicationManager_Args(appMan);

    v0->saveData = v1->saveData;
    Sound_SetSceneAndPlayBGM(SOUND_SCENE_11, SEQ_WIFILOBBY_sseq, 0);
    v1->unk_10 = 0;

    WifiP2PMatch_InitGraphics(v0, 112);
    WifiP2PMatch_InitMessageBox(&v0->messageBox, v0->bgConfig, 1, 674, 2, 19, 27, 4, (1 + (18 + 12)) + 9, v0->saveData, 112);
    WifiP2PMatch_InitMessageBox(&v0->connectBox, v0->bgConfig, 1, 695, 2, 19, 27, 4, (1 + (18 + 12)) + 9, v0->saveData, 112);
    WifiP2PMatch_InitMessageBox(&v0->errorBox, v0->bgConfig, 0, 695, 4, 4, 23, 16, ((1 + (18 + 12)) + 9) + (27 * 4), v0->saveData, 112);
    WifiP2PMatch_InitMessageBox(&v0->titleBox, v0->bgConfig, 1, 674, 5, 1, 22, 2, ((((1 + (18 + 12)) + 9) + (27 * 4)) + (23 * 16)) + (6 * 4), v0->saveData, 112);
    WifiP2PMatch_PrintCenteredMessage(&v0->titleBox, 21);

    SetVBlankCallback(WifiP2PMatch_VBlankCallback, v0);
    DisableHBlank();

    return 1;
}

int WifiP2PMatch_MainConnect(ApplicationManager *appMan, int *param1)
{
    WifiP2PMatch *v0 = ApplicationManager_Data(appMan);
    UnkStruct_ov66_02231024 *v1 = ApplicationManager_Args(appMan);

    switch (*param1) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, 1, 1, 0xffff, 6, 1, HEAP_ID_112);
        (*param1)++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            (*param1)++;
        }
        break;
    case 2:
        if (v1->unk_08 == 0) {
            WifiP2PMatch_PrintMessage(&v0->connectBox, 17);
            v0->menu = Menu_MakeYesNoChoice(v0->bgConfig, &sYesNoWindowTemplate, 1 + (18 + 12), 14, 112);
            (*param1)++;
        } else {
            (*param1) = 4;
        }
        break;
    case 3: {
        u32 v2;
        v2 = Menu_ProcessInputAndHandleExit(v0->menu, 112);

        switch (v2) {
        case 0:
            (*param1) = 4;
            break;
        case 0xfffffffe:
            WifiP2PMatch_EraseMessageBox(&v0->messageBox);
            (*param1) = 7;
            break;
        }
    } break;
    case 4: {
        WiFiPlazaProfile *v3;

        v3 = ov66_0222E3BC(v1->unk_04);
        CommManager_LoginWifiPlaza(v0->saveData, v3);
    }

        WifiP2PMatch_PrintMessage(&v0->connectBox, 23);
        WifiP2PMatch_AddWaitDial(&v0->connectBox);
        (*param1)++;
        break;
    case 5:
        if (CommManager_CheckWifiError() || CommManager_IsWifiPlazaError()) {
            WifiP2PMatch_DestroyWaitDial(&v0->connectBox);
            (*param1) = 9;
        }

        if (CommManager_GetWifiPlazaLoginSuccess() == 1) {
            ov66_0222F16C(v1->unk_04);
            (*param1)++;
        }
        break;
    case 6:
        if (CommManager_CheckWifiError() || CommManager_IsWifiPlazaError()) {
            WifiP2PMatch_DestroyWaitDial(&v0->connectBox);
            (*param1) = 9;
        }

        if (CommManager_IsLoginBattleWifi()) {
            WifiP2PMatch_DestroyWaitDial(&v0->connectBox);

            {
                GameRecords *v4;

                v4 = SaveData_GetGameRecords(v0->saveData);
                GameRecords_IncrementTrainerScore(v4, TRAINER_SCORE_EVENT_UNK_44);
            }

            {
                v1->unk_0C->unk_00 = GetTimestamp();
            }

            v1->unk_10 = 1;
            (*param1)++;
        }
        break;
    case 9: {
        UnkStruct_ov65_0222F6EC *v5;
        int v6, v7;

        if (CommManager_CheckWifiError()) {
            v5 = CommManager_GetUnk34();
            v6 = ov66_022316F4(v5->unk_00, v5->unk_04);
            v7 = v5->unk_00;
        } else {
            v7 = ov66_022326DC();
            v7 = ov66_0223270C(v7);
            v6 = 32;
        }

        ov66_0222F198(v1->unk_04);
        WifiP2PMatch_EraseMessageBox(&v0->messageBox);
        WifiP2PMatch_EraseMessageBox(&v0->connectBox);
        WifiP2PMatch_SetMessageNumber(&v0->errorBox, v7);
        WifiP2PMatch_PrintMessage(&v0->errorBox, v6);
        (*param1)++;
    } break;
    case 10:
        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            int v8;
            int v9;

            if (CommManager_CheckWifiError()) {
                UnkStruct_ov65_0222F6EC *v10 = CommManager_GetUnk34();

                v8 = ov66_02231718(v10->unk_00, v10->unk_04);

                if (v8 == 0) {
                    (*param1) = 11;
                } else {
                    (*param1) = 14;
                    break;
                }
            } else {
                (*param1) = 11;
            }
        }
        break;
    case 11:
        WifiP2PMatch_EraseMessageBox(&v0->errorBox);
        WifiP2PMatch_PrintMessage(&v0->messageBox, 88);
        v0->menu = Menu_MakeYesNoChoice(v0->bgConfig, &sYesNoWindowTemplate, 1 + (18 + 12), 14, 112);
        (*param1)++;
        break;
    case 12: {
        u32 v11;
        v11 = Menu_ProcessInputAndHandleExit(v0->menu, 112);

        switch (v11) {
        case 0:
            CommManager_LogoutWifiPlaza();
            (*param1) = 13;
            break;
        case 0xfffffffe:
            (*param1) = 14;
            break;
        }
    } break;
    case 13:
        if (CommManager_IsInitialized() == 0) {
            (*param1) = 4;
        }
        break;
    case 14:
        WifiP2PMatch_EraseMessageBox(&v0->messageBox);
        WifiP2PMatch_EraseMessageBox(&v0->connectBox);
        WifiP2PMatch_EraseMessageBox(&v0->errorBox);
        CommManager_LogoutWifiPlaza();
        (*param1)++;
        break;
    case 15:
        if (CommManager_IsInitialized() == 0) {
            WifiP2PMatch_EraseMessageBox(&v0->messageBox);
            WifiP2PMatch_EraseMessageBox(&v0->connectBox);
            (*param1) = 7;
        }
        break;
    case 7:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_112);
        (*param1)++;
        break;
    case 8:
        if (IsScreenFadeDone()) {
            return 1;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    inline_ov61_0222C0F8(&v0->paletteBlend);

    return 0;
}

int WifiP2PMatch_ExitConnect(ApplicationManager *appMan, int *param1)
{
    WifiP2PMatch *v0 = ApplicationManager_Data(appMan);

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    inline_ov61_0222C160(&v0->paletteBlend);

    WifiP2PMatch_FreeMessageBox(&v0->messageBox);
    WifiP2PMatch_FreeMessageBox(&v0->connectBox);
    WifiP2PMatch_FreeMessageBox(&v0->errorBox);
    WifiP2PMatch_FreeMessageBox(&v0->titleBox);
    WifiP2PMatch_FreeBackgrounds(v0);

    inline_ov96_0223BDEC(&v0->paletteBlend, 0);

    Heap_Free(v0);
    Heap_Destroy(HEAP_ID_112);

    return 1;
}

int WifiP2PMatch_InitDisconnect(ApplicationManager *appMan, int *param1)
{
    WifiP2PMatch *v0;
    UnkStruct_ov66_02231300 *v1;

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_112, 0x20000);

    v0 = ApplicationManager_NewData(appMan, sizeof(WifiP2PMatch), HEAP_ID_112);
    memset(v0, 0, sizeof(WifiP2PMatch));

    v1 = ApplicationManager_Args(appMan);
    v0->saveData = v1->saveData;

    WifiP2PMatch_InitGraphics(v0, 112);
    WifiP2PMatch_InitMessageBox(&v0->messageBox, v0->bgConfig, 1, 695, 2, 19, 27, 4, (1 + (18 + 12)) + 9, v0->saveData, 112);
    WifiP2PMatch_InitMessageBox(&v0->errorBox, v0->bgConfig, 0, 695, 4, 4, 23, 16, ((1 + (18 + 12)) + 9) + (27 * 4), v0->saveData, 112);
    WifiP2PMatch_InitMessageBox(&v0->titleBox, v0->bgConfig, 1, 674, 5, 1, 22, 2, ((((1 + (18 + 12)) + 9) + (27 * 4)) + (23 * 16)) + (6 * 4), v0->saveData, 112);
    WifiP2PMatch_PrintCenteredMessage(&v0->titleBox, 21);

    NetworkIcon_Init();
    SetVBlankCallback(WifiP2PMatch_VBlankCallback, v0);
    DisableHBlank();

    return 1;
}

int WifiP2PMatch_MainDisconnect(ApplicationManager *appMan, int *param1)
{
    WifiP2PMatch *v0 = ApplicationManager_Data(appMan);
    UnkStruct_ov66_02231300 *v1 = ApplicationManager_Args(appMan);

    switch (*param1) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, 1, 1, 0xffff, 6, 1, HEAP_ID_112);
        (*param1)++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            (*param1) = 2;
        }
        break;
    case 2:
        WifiP2PMatch_PrintMessage(&v0->messageBox, 26);

        if (CommManager_CheckWifiError() || CommManager_IsWifiPlazaError()) {
            (*param1) = 5;
            WifiP2PMatch_AddWaitDial(&v0->messageBox);
        } else {
            (*param1) = 3;
            WifiP2PMatch_AddWaitDial(&v0->messageBox);
        }
        break;
    case 3:
        ov66_02232C8C();

        v0->timer = (30 * 30);
        (*param1) = 4;
        break;
    case 4:
        if ((v0->timer - 1) >= 0) {
            v0->timer--;
        }

        if (ov66_02232CB8() || (v0->timer == 0)) {
            (*param1) = 5;
        }
        break;
    case 5:
        CommManager_LogoutWifiPlaza();
        (*param1) = 6;
        break;
    case 6:
        if (CommManager_IsInitialized() == 0) {
            WifiP2PMatch_DestroyWaitDial(&v0->connectBox);
            ov66_0222F198(v1->unk_04);
            (*param1) = 7;
        }
        break;
    case 7:
        WifiP2PMatch_PrintMessage(&v0->messageBox, 27);
        v0->timer = (3 * 30);
        (*param1) = 8;
        break;
    case 8:
        if ((v0->timer - 1) >= 0) {
            v0->timer--;
        }

        if (v0->timer == 0) {
            (*param1) = 9;
        }
        break;
    case 9:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_112);
        (*param1)++;
        break;
    case 10:
        if (IsScreenFadeDone()) {
            WifiP2PMatch_DestroyWaitDial(&v0->messageBox);
            return 1;
        }
        break;
    }

    inline_ov61_0222C0F8(&v0->paletteBlend);

    return 0;
}

int WifiP2PMatch_ExitDisconnect(ApplicationManager *appMan, int *param1)
{
    WifiP2PMatch *v0 = ApplicationManager_Data(appMan);

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    inline_ov61_0222C160(&v0->paletteBlend);

    WifiP2PMatch_FreeMessageBox(&v0->messageBox);
    WifiP2PMatch_FreeMessageBox(&v0->errorBox);
    WifiP2PMatch_FreeMessageBox(&v0->titleBox);
    WifiP2PMatch_FreeBackgrounds(v0);

    inline_ov96_0223BDEC(&v0->paletteBlend, 0);

    Heap_Free(v0);
    Heap_Destroy(HEAP_ID_112);

    return 1;
}

static void WifiP2PMatch_VBlankCallback(void *param0)
{
    WifiP2PMatch *v0 = param0;

    WifiP2PMatch_UpdateBackgrounds(v0);
    inline_ov61_0222C1FC(&v0->paletteBlend);
}

static void WifiP2PMatch_InitGraphics(WifiP2PMatch *param0, enum HeapID heapID)
{
    G2_BlendNone();
    G2S_BlendNone();

    GXLayers_SetBanks(&sGXBanks);

    {
        Bg_MaskPalette(sBgLayers[0], 0);
    }

    {
        int v0;

        SetAllGraphicsModes(&sGraphicsModes);
        param0->bgConfig = BgConfig_New(heapID);

        for (v0 = 0; v0 < 3; v0++) {
            Bg_InitFromTemplate(param0->bgConfig, sBgLayers[v0], &sBgTemplates[v0], 0);
            Bg_ClearTilesRange(sBgLayers[v0], 32, 0, heapID);
            Bg_ClearTilemap(param0->bgConfig, sBgLayers[v0]);
        }
    }

    {
        Options *options = SaveData_GetOptions(param0->saveData);
        u8 v2 = Options_Frame(options);

        Font_LoadTextPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(12), heapID);
        Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(11), heapID);
        LoadStandardWindowGraphics(param0->bgConfig, sBgLayers[1], 1 + (18 + 12), 14, 0, heapID);
        LoadMessageBoxGraphics(param0->bgConfig, sBgLayers[1], 1, 13, v2, heapID);
    }

    {
        Graphics_LoadPalette(NARC_INDEX_DATA__WIFIP2PMATCH, 3, 0, 0, 11 * 32, heapID);
        Graphics_LoadPalette(NARC_INDEX_DATA__WIFIP2PMATCH, 3, 4, 0, 11 * 32, heapID);
        Graphics_LoadTilesToBgLayer(NARC_INDEX_DATA__WIFIP2PMATCH, 2, param0->bgConfig, sBgLayers[0], 0, 0, 0, heapID);
        Graphics_LoadTilesToBgLayer(NARC_INDEX_DATA__WIFIP2PMATCH, 10, param0->bgConfig, sBgLayers[2], 0, 0, 0, heapID);
        Graphics_LoadTilemapToBgLayer(NARC_INDEX_DATA__WIFIP2PMATCH, 5, param0->bgConfig, sBgLayers[0], 0, 0, 0, heapID);
        Graphics_LoadTilemapToBgLayer(NARC_INDEX_DATA__WIFIP2PMATCH, 11, param0->bgConfig, sBgLayers[2], 0, 0, 0, heapID);
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);

    {
        NARC *v3;

        v3 = NARC_ctor(NARC_INDEX_DATA__WIFIP2PMATCH, heapID);

        inline_ov61_0222C3B0(&param0->paletteBlend, v3, 4, heapID);

        NARC_dtor(v3);
    }
}

static void WifiP2PMatch_FreeBackgrounds(WifiP2PMatch *param0)
{
    {
        int v0;

        for (v0 = 0; v0 < 3; v0++) {
            Bg_FreeTilemapBuffer(param0->bgConfig, sBgLayers[v0]);
        }

        Heap_Free(param0->bgConfig);
    }
}

static void WifiP2PMatch_UpdateBackgrounds(WifiP2PMatch *param0)
{
    Bg_RunScheduledUpdates(param0->bgConfig);
}

static void WifiP2PMatch_InitMessageBox(WifiP2PMatchMessageBox *param0, BgConfig *param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, SaveData *saveData, enum HeapID heapID)
{
    param0->stringTemplate = StringTemplate_Default(heapID);
    param0->messageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, param3, heapID);
    param0->formattedString = String_Init(256, heapID);
    param0->messageString = String_Init(256, heapID);
    param0->windowType = param2;
    param0->textFrameDelay = Options_TextFrameDelay(SaveData_GetOptions(saveData));
    param0->printer = 0;

    Window_Add(param1, &param0->window, sBgLayers[1], param4, param5, param6, param7, 11, param8);
}

static void WifiP2PMatch_PrintMessage(WifiP2PMatchMessageBox *param0, u32 param1)
{
    if (Text_IsPrinterActive(param0->printer)) {
        Text_RemovePrinter(param0->printer);
    }

    Window_FillTilemap(&param0->window, 15);
    MessageLoader_GetString(param0->messageLoader, param1, param0->messageString);
    StringTemplate_Format(param0->stringTemplate, param0->formattedString, param0->messageString);
    Text_AddPrinterWithParams(&param0->window, FONT_MESSAGE, param0->formattedString, 0, 0, TEXT_SPEED_NO_TRANSFER, NULL);

    if (param0->windowType == 0) {
        Window_DrawStandardFrame(&param0->window, 1, 1 + (18 + 12), 14);
    } else {
        Window_DrawMessageBoxWithScrollCursor(&param0->window, 1, 1, 13);
    }

    Window_ScheduleCopyToVRAM(&param0->window);
}

static void WifiP2PMatch_EraseMessageBox(WifiP2PMatchMessageBox *param0)
{
    if (Text_IsPrinterActive(param0->printer)) {
        Text_RemovePrinter(param0->printer);
    }

    if (param0->windowType == 0) {
        Window_EraseStandardFrame(&param0->window, 1);
        Window_ClearAndScheduleCopyToVRAM(&param0->window);
    } else {
        if (param0->waitDial) {
            WifiP2PMatch_DestroyWaitDial(param0);
        }

        Window_EraseMessageBox(&param0->window, 1);
        Window_ClearAndScheduleCopyToVRAM(&param0->window);
    }
}

static void WifiP2PMatch_AddWaitDial(WifiP2PMatchMessageBox *param0)
{
    if (param0->windowType == 1) {
        GF_ASSERT(param0->waitDial == NULL);
        param0->waitDial = Window_AddWaitDial(&param0->window, 1);
    }
}

static void WifiP2PMatch_DestroyWaitDial(WifiP2PMatchMessageBox *param0)
{
    if (param0->windowType == 1) {
        GF_ASSERT(param0->waitDial != NULL);
        DestroyWaitDial(param0->waitDial);
        param0->waitDial = NULL;
    }
}

static void WifiP2PMatch_FreeMessageBox(WifiP2PMatchMessageBox *param0)
{
    if (Text_IsPrinterActive(param0->printer)) {
        Text_RemovePrinter(param0->printer);
    }

    if (param0->waitDial) {
        WifiP2PMatch_DestroyWaitDial(param0);
    }

    Window_Remove(&param0->window);
    String_Free(param0->messageString);
    String_Free(param0->formattedString);
    MessageLoader_Free(param0->messageLoader);
    StringTemplate_Free(param0->stringTemplate);
}

static void WifiP2PMatch_PrintCenteredMessage(WifiP2PMatchMessageBox *param0, u32 param1)
{
    Window_FillTilemap(&param0->window, 0);
    MessageLoader_GetString(param0->messageLoader, param1, param0->messageString);
    StringTemplate_Format(param0->stringTemplate, param0->formattedString, param0->messageString);
    Text_AddPrinterWithParamsAndColor(&param0->window, FONT_MESSAGE, param0->formattedString, Font_CalcCenterAlignment(FONT_SYSTEM, param0->formattedString, 0, 0xB0), 0, TEXT_SPEED_INSTANT, TEXT_COLOR(15, 14, 0), 0);
}

static void WifiP2PMatch_SetMessageNumber(WifiP2PMatchMessageBox *param0, u32 param1)
{
    StringTemplate_SetNumber(param0->stringTemplate, 0, param1, 5, 2, 1);
}
