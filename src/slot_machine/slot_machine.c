#include "slot_machine/slot_machine.h"

#include <nitro.h>
#include <string.h>

#include "generated/game_records.h"

#include "struct_defs/struct_slot_machine_app_args.h"

#include "slot_machine/slot_machine_game.h"
#include "slot_machine/slot_machine_anim.h"
#include "slot_machine/slot_machine_sprite.h"
#include "slot_machine/struct_slot_machine_context.h"
#include "slot_machine/struct_slot_machine_message_box.h"
#include "slot_machine/struct_slot_machine_bgm_state.h"

#include "bg_window.h"
#include "char_transfer.h"
#include "enums.h"
#include "font.h"
#include "game_records.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "overlay_manager.h"
#include "overworld_anim_manager.h"
#include "pltt_transfer.h"
#include "render_oam.h"
#include "render_window.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "vram_transfer.h"

typedef struct {
    SlotMachineAppArgs *appArgs;
    SlotMachineContext *context;
} SlotMachineAppData;

static void SlotMachine_SaveResult(SlotMachineAppData *param0, SlotMachineContext *param1);
static SlotMachineContext *SlotMachine_NewContext(SlotMachineAppArgs *param0);
static void SlotMachine_FreeContext(SlotMachineContext *param0);
static void SlotMachine_InitGraphics(SlotMachineContext *param0);
static void SlotMachine_FreeGraphics(SlotMachineContext *param0);
static void SlotMachine_InitGxBanks(void);
static void SlotMachine_InitBg(BgConfig *param0);
static void SlotMachine_FreeBg(BgConfig *param0);
static void SlotMachine_InitWindow(void);
static void SlotMachine_LoadBgGraphics(SlotMachineContext *param0);
static void SlotMachine_InitCharTransfer(void);
static void SlotMachine_FreeCharTransfer(void);
static void SlotMachine_InitOam(SlotMachineContext *param0);
static void SlotMachine_FreeOam(SlotMachineContext *param0);
static void SlotMachine_LoadSpriteResources(SlotMachineContext *param0);
static void SlotMachine_Noop(SlotMachineContext *param0);
static void SlotMachine_InitAnimManagerList(SlotMachineContext *param0);
static void SlotMachine_FreeAnimManagerList(SlotMachineContext *param0);
static int SlotMachine_GetBgmMode(SlotMachineContext *param0);
static void SlotMachine_StartBgmTask(SlotMachineContext *param0);
static void SlotMachine_StopBgmTask(SlotMachineContext *param0);
static void SlotMachine_BgmTask(SysTask *param0, void *param1);
static void SlotMachine_VBlankCallback(void *param0);
static void SlotMachine_OpenNarc(SlotMachineContext *param0);
static void SlotMachine_CloseNarc(SlotMachineContext *param0);
static const WindowTemplate sSlotMachineMessageBoxTemplate[1];
static void SlotMachine_FreeMessageBox(SlotMachineContext *param0);

int SlotMachine_Init(ApplicationManager *appMan, int *param1)
{
    SlotMachineAppData *v0;
    SlotMachineContext *v1;
    SlotMachineAppArgs *v2;

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();
    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_79, 0x80000);

    v0 = ApplicationManager_NewData(appMan, sizeof(SlotMachineAppData), HEAP_ID_79);
    memset(v0, 0, sizeof(SlotMachineAppData));
    v2 = ApplicationManager_Args(appMan);
    v0->appArgs = v2;
    v1 = SlotMachine_NewContext(v0->appArgs);
    v0->context = v1;

    SlotMachine_OpenNarc(v1);
    SlotMachine_InitAnimManagerList(v1);
    SlotMachine_InitGraphics(v1);
    SlotMachine_LoadBgGraphics(v1);
    SlotMachine_InitMessageBox(v1);
    SlotMachine_InitCharTransfer();
    SlotMachine_InitOam(v1);
    SlotMachine_InitGame(v1);
    SlotMachine_InitReelSprites(v1);
    SlotMachine_InitPayoutDigits(v1);
    SlotMachine_InitCreditDigits(v1);
    Sound_SetSceneAndPlayBGM(SOUND_SCENE_SUB_66, SEQ_NONE, 0);
    SlotMachine_StartBgmTask(v1);
    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 8, 1, HEAP_ID_79);

    return 1;
}

int SlotMachine_Main(ApplicationManager *appMan, int *param1)
{
    SlotMachineAppData *v0 = ApplicationManager_Data(appMan);
    SlotMachineContext *v1 = v0->context;

    switch (*param1) {
    case 0:
        if (IsScreenFadeDone()) {
            (*param1)++;
        }
        break;
    case 1:
        if (SlotMachine_Update(v1) == 1) {
            (*param1)++;
            StartScreenFade(FADE_SUB_THEN_MAIN, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 8, 1, HEAP_ID_79);
            SlotMachine_SetBgmMode(v1, SlotMachineBgmMode_00);
        }
        break;
    case 2:
        if (IsScreenFadeDone() == FALSE) {
            break;
        }
        (*param1)++;
    case 3:
        if (SlotMachine_GetBgmMode(v1) == 0) {
            return 1;
        }
    }

    OverworldAnimManagerList_Render(v1->animManagerList);
    SlotMachineSprite_Update(v1->spriteManager);

    return 0;
}

int SlotMachine_Exit(ApplicationManager *appMan, int *param1)
{
    SlotMachineAppData *v0 = ApplicationManager_Data(appMan);
    SlotMachineContext *v1 = v0->context;

    SetVBlankCallback(NULL, NULL);

    SlotMachine_SaveResult(v0, v1);

    SlotMachine_FreeAnimManagerList(v1);
    SlotMachine_FreeGraphics(v1);
    SlotMachine_FreeMessageBox(v1);

    SlotMachine_FreeGame(v1);
    SlotMachine_StopBgmTask(v1);

    SlotMachine_CloseNarc(v1);
    SlotMachine_FreeContext(v1);

    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_79);

    return 1;
}

static void SlotMachine_SaveResult(SlotMachineAppData *param0, SlotMachineContext *param1)
{
    u32 v0 = param1->coins;

    if (v0 > 50000) {
        v0 = 50000;
    }

    (*param0->appArgs->coins) = v0;
    param0->appArgs->consecutiveBonusRoundWins = param1->consecutiveBonusRoundWins;

    if (param0->appArgs->records != NULL) {
        GameRecords_AddToRecordValue(param0->appArgs->records, RECORD_UNK_014, param1->bonusRounds);
    }
}

static SlotMachineContext *SlotMachine_NewContext(SlotMachineAppArgs *param0)
{
    SlotMachineContext *v0 = SlotMachine_Alloc(sizeof(SlotMachineContext));

    v0->coins = *(param0->coins);
    v0->machineMode = param0->machineMode;
    v0->msgBoxFrame = param0->msgBoxFrame;

    return v0;
}

static void SlotMachine_FreeContext(SlotMachineContext *param0)
{
    Heap_Free(param0);
}

static void SlotMachine_InitGraphics(SlotMachineContext *param0)
{
    param0->bgConfig = BgConfig_New(HEAP_ID_79);

    SlotMachine_InitGxBanks();
    SlotMachine_InitBg(param0->bgConfig);
    SlotMachine_InitWindow();

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);

    G2_SetBG0Priority(0);
    G2_SetBG1Priority(1);
    G2_SetBG2Priority(2);
    G2_SetBG3Priority(3);
    G2S_SetBG0Priority(0);
    G2S_SetBG1Priority(1);
    G2S_SetBG2Priority(2);
    G2S_SetBG3Priority(3);
    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_OBJ, 8, 9);

    SetVBlankCallback(SlotMachine_VBlankCallback, param0);
}

static void SlotMachine_FreeGraphics(SlotMachineContext *param0)
{
    SlotMachine_FreeBg(param0->bgConfig);
    SlotMachine_FreeOam(param0);
    SlotMachine_FreeCharTransfer();
}

static void SlotMachine_InitGxBanks(void)
{
    GXBanks v0 = {
        GX_VRAM_BG_128_A,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_128_B,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_NONE,
        GX_VRAM_TEXPLTT_NONE
    };

    GXLayers_SetBanks(&v0);
}

static void SlotMachine_InitBg(BgConfig *param0)
{
    GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D,
        };

        SetAllGraphicsModes(&v0);
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x0000,
            .charBase = GX_BG_CHARBASE_0x04000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_0, &v1, 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_0, 32, 0, HEAP_ID_79);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x0800,
            .charBase = GX_BG_CHARBASE_0x0c000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_1, &v2, 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_1);
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x1000,
            .charBase = GX_BG_CHARBASE_0x14000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_2, &v3, 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_2);
    }

    {
        BgTemplate v4 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x1800,
            .charBase = GX_BG_CHARBASE_0x20000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_3, &v4, 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_3);
    }
}

static void SlotMachine_FreeBg(BgConfig *param0)
{
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_0);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_3);
    Heap_Free(param0);
}

static void SlotMachine_InitWindow(void)
{
    GX_SetVisibleWnd(GX_WNDMASK_W0);
    G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
    G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
    G2_SetWnd0Position(0, 0, 255, 255);
}

static void SlotMachine_LoadBgGraphics(SlotMachineContext *param0)
{
    void *v0 = SlotMachine_ReadNarcMember(param0, 3, 0);

    NNS_G2dGetUnpackedPaletteData(v0, &param0->paletteData);
    Bg_LoadPalette(BG_LAYER_MAIN_1, param0->paletteData->pRawData, PALETTE_SIZE_BYTES * 13, 32 * 0);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 0, 0);
    NNS_G2dGetUnpackedCharacterData(v0, &param0->charData);
    Bg_LoadTiles(param0->bgConfig, 1, param0->charData->pRawData, param0->charData->szByte, 32 * 0);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 1, 0);
    NNS_G2dGetUnpackedScreenData(v0, &param0->screenData);
    Bg_LoadTilemapBuffer(param0->bgConfig, 1, (void *)param0->screenData->rawData, param0->screenData->szByte);
    Bg_CopyTilemapBufferToVRAM(param0->bgConfig, 1);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 8, 0);
    NNS_G2dGetUnpackedCharacterData(v0, &param0->charData);
    Bg_LoadTiles(param0->bgConfig, 2, param0->charData->pRawData, param0->charData->szByte, 32 * 0);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 9, 0);
    NNS_G2dGetUnpackedScreenData(v0, &param0->screenData);
    Bg_LoadTilemapBuffer(param0->bgConfig, 2, (void *)param0->screenData->rawData, param0->screenData->szByte);
    Bg_CopyTilemapBufferToVRAM(param0->bgConfig, 2);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 3, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &param0->paletteData);
    Bg_LoadPalette(BG_LAYER_SUB_3, param0->paletteData->pRawData, PALETTE_SIZE_BYTES * 13, 32 * 0);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 2, 0);
    NNS_G2dGetUnpackedCharacterData(v0, &param0->charData);
    Bg_LoadTiles(param0->bgConfig, 7, param0->charData->pRawData, param0->charData->szByte, 0);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 4, 0);
    NNS_G2dGetUnpackedScreenData(v0, &param0->screenData);
    Bg_LoadTilemapBuffer(param0->bgConfig, 7, (void *)param0->screenData->rawData, param0->screenData->szByte);
    Bg_CopyTilemapBufferToVRAM(param0->bgConfig, 7);
    Heap_Free(v0);
}

void SlotMachine_InitMessageBox(SlotMachineContext *param0)
{
    int v0;
    SlotMachineMessageBox *v1 = &param0->messageBox;

    LoadStandardWindowGraphics(param0->bgConfig, BG_LAYER_MAIN_0, 1, 15, 0, HEAP_ID_79);
    LoadMessageBoxGraphics(param0->bgConfig, BG_LAYER_MAIN_0, 1 + (18 + 12), 14, param0->msgBoxFrame, HEAP_ID_79);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(15), HEAP_ID_79);

    v1->messageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0544, HEAP_ID_79);
    v1->stringTemplate = StringTemplate_Default(HEAP_ID_79);

    for (v0 = 0; v0 < 1; v0++) {
        Window_AddFromTemplate(param0->bgConfig, &v1->window[v0], &sSlotMachineMessageBoxTemplate[v0]);
    }

    v1->string = String_Init(256, HEAP_ID_79);
}

void SlotMachine_FreeMessageBox(SlotMachineContext *param0)
{
    int v0;
    SlotMachineMessageBox *v1 = &param0->messageBox;

    for (v0 = 0; v0 < 1; v0++) {
        Window_ClearAndCopyToVRAM(&v1->window[v0]);
        Window_Remove(&v1->window[v0]);
    }

    MessageLoader_Free(v1->messageLoader);
    StringTemplate_Free(v1->stringTemplate);
    String_Free(v1->string);
}

void SlotMachine_ShowMessage(SlotMachineContext *param0, u32 param1)
{
    SlotMachineMessageBox *v0 = &param0->messageBox;

    Window_DrawMessageBoxWithScrollCursor(&v0->window[0], 1, 1 + (18 + 12), 14);
    Window_FillTilemap(&v0->window[0], 15);
    MessageLoader_GetString(v0->messageLoader, param1, v0->string);
    Text_AddPrinterWithParams(&v0->window[0], FONT_MESSAGE, v0->string, 0, 0, TEXT_SPEED_NO_TRANSFER, NULL);
    Window_ScheduleCopyToVRAM(&v0->window[0]);
}

void SlotMachine_HideMessage(SlotMachineContext *param0)
{
    SlotMachineMessageBox *v0 = &param0->messageBox;

    Window_EraseMessageBox(&v0->window[0], 1);
    Window_FillTilemap(&v0->window[0], 0);
    Window_ScheduleCopyToVRAM(&v0->window[0]);
}

static void SlotMachine_InitCharTransfer(void)
{
    CharTransferTemplate v0 = {
        32, 0x4000, 0x4000, 79
    };

    CharTransfer_InitWithVramModes(&v0, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_128K);
    PlttTransfer_Init(16, HEAP_ID_79);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
}

static void SlotMachine_FreeCharTransfer(void)
{
    CharTransfer_Free();
    PlttTransfer_Free();
}

static void SlotMachine_InitOam(SlotMachineContext *param0)
{
    NNS_G2dInitOamManagerModule();

    RenderOam_Init(0, 128, 0, 32, 0, 128, 0, 32, 79);
    param0->spriteManager = SlotMachineSprite_New(HEAP_ID_79, 64, 32, 64, 16, 64, 32, 11, 8, 11, 11);
    SlotMachine_LoadSpriteResources(param0);
}

static void SlotMachine_FreeOam(SlotMachineContext *param0)
{
    SlotMachine_Noop(param0);
    SlotMachineSprite_Free(param0->spriteManager);
    RenderOam_Free();
}

static void SlotMachine_LoadSpriteResources(SlotMachineContext *param0)
{
    SlotMachineSprite_AddTiles(param0->spriteManager, NNS_G2D_VRAM_TYPE_2DMAIN, param0->narc, 11, 0);
    SlotMachineSprite_AddTiles(param0->spriteManager, NNS_G2D_VRAM_TYPE_2DMAIN, param0->narc, 21, 1);
    SlotMachineSprite_AddTiles(param0->spriteManager, NNS_G2D_VRAM_TYPE_2DSUB, param0->narc, 68, 6);
    SlotMachineSprite_AddTiles(param0->spriteManager, NNS_G2D_VRAM_TYPE_2DSUB, param0->narc, 71, 7);
    SlotMachineSprite_AddTiles(param0->spriteManager, NNS_G2D_VRAM_TYPE_2DSUB, param0->narc, 64, 8);
    SlotMachineSprite_AddTiles(param0->spriteManager, NNS_G2D_VRAM_TYPE_2DSUB, param0->narc, 60, 9);

    SlotMachineSprite_AddPalette(param0->spriteManager, NNS_G2D_VRAM_TYPE_2DBOTH, param0->narc, 10, 0);
    SlotMachineSprite_AddPalette(param0->spriteManager, NNS_G2D_VRAM_TYPE_2DMAIN, param0->narc, 20, 1);
    SlotMachineSprite_AddPalette(param0->spriteManager, NNS_G2D_VRAM_TYPE_2DSUB, param0->narc, 67, 6);
    SlotMachineSprite_AddPalette(param0->spriteManager, NNS_G2D_VRAM_TYPE_2DSUB, param0->narc, 63, 7);

    SlotMachineSprite_AddCell(param0->spriteManager, param0->narc, 12, 0);
    SlotMachineSprite_AddCell(param0->spriteManager, param0->narc, 22, 1);
    SlotMachineSprite_AddCell(param0->spriteManager, param0->narc, 69, 6);
    SlotMachineSprite_AddCell(param0->spriteManager, param0->narc, 72, 7);
    SlotMachineSprite_AddCell(param0->spriteManager, param0->narc, 65, 8);
    SlotMachineSprite_AddCell(param0->spriteManager, param0->narc, 61, 9);

    SlotMachineSprite_AddAnim(param0->spriteManager, param0->narc, 13, 0);
    SlotMachineSprite_AddAnim(param0->spriteManager, param0->narc, 23, 1);
    SlotMachineSprite_AddAnim(param0->spriteManager, param0->narc, 70, 6);
    SlotMachineSprite_AddAnim(param0->spriteManager, param0->narc, 73, 7);
    SlotMachineSprite_AddAnim(param0->spriteManager, param0->narc, 66, 8);
    SlotMachineSprite_AddAnim(param0->spriteManager, param0->narc, 62, 9);

    SlotMachineSprite_RequestChar(param0->spriteManager, 0);
    SlotMachineSprite_RequestChar(param0->spriteManager, 1);
    SlotMachineSprite_RequestChar(param0->spriteManager, 6);
    SlotMachineSprite_RequestChar(param0->spriteManager, 7);
    SlotMachineSprite_RequestChar(param0->spriteManager, 8);
    SlotMachineSprite_RequestChar(param0->spriteManager, 9);
    SlotMachineSprite_ReleaseChar(param0->spriteManager, 0);
    SlotMachineSprite_ReleaseChar(param0->spriteManager, 1);
    SlotMachineSprite_ReleaseChar(param0->spriteManager, 6);
    SlotMachineSprite_ReleaseChar(param0->spriteManager, 7);
    SlotMachineSprite_ReleaseChar(param0->spriteManager, 8);
    SlotMachineSprite_ReleaseChar(param0->spriteManager, 9);

    SlotMachineSprite_RequestPltt(param0->spriteManager, 0);
    SlotMachineSprite_RequestPltt(param0->spriteManager, 1);
    SlotMachineSprite_RequestPltt(param0->spriteManager, 6);
    SlotMachineSprite_RequestPltt(param0->spriteManager, 7);
    SlotMachineSprite_ReleasePltt(param0->spriteManager, 0);
    SlotMachineSprite_ReleasePltt(param0->spriteManager, 1);
    SlotMachineSprite_ReleasePltt(param0->spriteManager, 6);
    SlotMachineSprite_ReleasePltt(param0->spriteManager, 7);
}

static void SlotMachine_Noop(SlotMachineContext *param0)
{
    return;
}

static void SlotMachine_InitAnimManagerList(SlotMachineContext *param0)
{
    param0->animManagerList = OverworldAnimManagerList_New(HEAP_ID_79, 128);
}

static void SlotMachine_FreeAnimManagerList(SlotMachineContext *param0)
{
    OverworldAnimManagerList_FinishAndFree(param0->animManagerList);
}

void SlotMachine_SetBgmMode(SlotMachineContext *param0, SlotMachineBgmMode param1)
{
    SlotMachineBgmState *v0 = &param0->bgmState;

    if ((v0->currentMode == param1) || (v0->requestedMode == param1)) {
        return;
    }

    v0->requestedMode = param1;
    v0->state = 1;
    v0->done = 1;
}

static int SlotMachine_GetBgmMode(SlotMachineContext *param0)
{
    SlotMachineBgmState *v0 = &param0->bgmState;
    return v0->done;
}

static void SlotMachine_StartBgmTask(SlotMachineContext *param0)
{
    SlotMachineBgmState *v0 = &param0->bgmState;

    v0->currentMode = SlotMachineBgmMode_00;
    v0->requestedMode = SlotMachineBgmMode_03;
    v0->task = SysTask_Start(SlotMachine_BgmTask, param0, 144);
}

static void SlotMachine_StopBgmTask(SlotMachineContext *param0)
{
    SysTask_Done(param0->bgmState.task);
}

static void SlotMachine_BgmTask(SysTask *param0, void *param1)
{
    SlotMachineContext *v0 = param1;
    SlotMachineBgmState *v1 = &v0->bgmState;

    switch (v1->state) {
    case 0:
        break;
    case 1:
        switch (v1->currentMode) {
        case SlotMachineBgmMode_00:
            Sound_SetBGMPlayerPaused(PLAYER_FIELD, TRUE);
            break;
        case SlotMachineBgmMode_01:
            Sound_StopBGM(SEQ_SLOT_ATARI_sseq, 0);
            break;
        case SlotMachineBgmMode_02:
            Sound_StopBGM(SEQ_SLOT_OOATARI_sseq, 0);
            break;
        }

        v1->state++;
        break;
    case 2:
        switch (v1->requestedMode) {
        case SlotMachineBgmMode_00:
            Sound_SetBGMPlayerPaused(PLAYER_FIELD, FALSE);
            break;
        case SlotMachineBgmMode_01:
            Sound_PlayBasicBGM(SEQ_SLOT_ATARI_sseq);
            break;
        case SlotMachineBgmMode_02:
            Sound_PlayBasicBGM(SEQ_SLOT_OOATARI_sseq);
            break;
        }

        v1->currentMode = v1->requestedMode;
        v1->requestedMode = SlotMachineBgmMode_03;
        v1->done = 0;
        v1->state = 0;
    }
}

static void SlotMachine_VBlankCallback(void *param0)
{
    SlotMachineContext *v0 = param0;

    VramTransfer_Process();
    RenderOam_Transfer();
    Bg_RunScheduledUpdates(v0->bgConfig);
}

void *SlotMachine_Alloc(u32 param0)
{
    void *v0 = Heap_Alloc(HEAP_ID_79, param0);

    GF_ASSERT(v0 != NULL);
    memset(v0, 0, param0);

    return v0;
}

static void SlotMachine_OpenNarc(SlotMachineContext *param0)
{
    param0->narc = NARC_ctor(NARC_INDEX_DATA__SLOT, HEAP_ID_79);
}

static void SlotMachine_CloseNarc(SlotMachineContext *param0)
{
    NARC_dtor(param0->narc);
}

void *SlotMachine_ReadNarcMember(SlotMachineContext *param0, u32 param1, int param2)
{
    void *v0;
    u32 v1 = NARC_GetMemberSize(param0->narc, param1);

    if (param2 == 1) {
        v0 = Heap_Alloc(HEAP_ID_79, v1);
    } else {
        v0 = Heap_AllocAtEnd(HEAP_ID_79, v1);
    }

    GF_ASSERT(v0 != NULL);
    NARC_ReadWholeMember(param0->narc, param1, v0);

    return v0;
}

static const WindowTemplate sSlotMachineMessageBoxTemplate[1] = {
    { 0x0, 0x2, 0x13, 0x1A, 0x4, 0xF, 0x3D }
};
