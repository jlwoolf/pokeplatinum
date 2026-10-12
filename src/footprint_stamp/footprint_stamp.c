#include "footprint_stamp/footprint_stamp.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"
#include "constants/species.h"

#include "struct_decls/font_oam.h"
#include "struct_decls/struct_02012744_decl.h"
#include "struct_defs/struct_font_oam_template.h"

#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_022324F0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0223127C.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02232B20.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_022589B4.h"
#include "footprint_stamp/footprint_stamp_models.h"
#include "footprint_stamp/footprint_stamp_players.h"
#include "footprint_stamp/footprint_stamp_comm.h"
#include "footprint_stamp/struct_footprint_stamp_add_payload.h"
#include "footprint_stamp/struct_footprint_stamp_model_manager.h"
#include "footprint_stamp/struct_footprint_stamp_comm_state.h"
#include "footprint_stamp/struct_footprint_stamp_entry.h"

#include "bg_window.h"
#include "camera.h"
#include "char_transfer.h"
#include "easy3d_object.h"
#include "font.h"
#include "fx_util.h"
#include "g3d_pipeline.h"
#include "game_options.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "palette.h"
#include "party.h"
#include "pokemon.h"
#include "render_text.h"
#include "render_window.h"
#include "save_player.h"
#include "savedata.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_system.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "touch_pad.h"
#include "font_oam.h"
#include "g3_buffer.h"
#include "vram_transfer.h"
#include "yes_no_touch_menu.h"

typedef struct {
    Easy3DModel model; // The footprint board's 3D model.
    Easy3DObject object; // The placed instance of the board model.
} FootprintStampBoardModel;

typedef struct {
    FontOAM *oam; // OAM used to draw the "EXIT" label.
    CharTransferAllocation allocation; // Character transfer allocation backing the OAM.
    u16 width; // Rendered width of the string in pixels.
} FootprintStampText;

typedef struct FootprintStampApp_t {
    WiFiPlazaLobbyFootprintStampArgs *args; // Wi-Fi lobby communication data passed in as args.
    SaveData *saveData;
    BgConfig *bgConfig;
    PaletteData *paletteData;
    FontOAMManager *fontOAMManager;
    G3DPipelineBuffers *g3dPipeline;
    SysTask *sysTask; // Per-frame task that updates the models and draws sprites.
    SpriteSystem *spriteSystem;
    SpriteManager *spriteManager;
    YesNoTouchMenu *yesNoMenu;
    u8 menuOpen;
    u8 waitFrames;
    StringTemplate *stringTemplate;
    MessageLoader *messageLoader;
    Window playerWindows[8]; // One window per Wi-Fi lobby player slot.
    Window messageWindow;
    String *string;
    u8 printerId;
    Camera *camera;
    fx32 fovX; // Horizontal field of view, computed from the camera.
    fx32 fovY; // Vertical field of view, computed from the camera.
    FootprintStampBoardModel boardModel;
    NARC *boardNarc; // graphic/footprint_board.narc
    NARC *pokefootNarc; // poketool/pokefoot/pokefoot.narc
    FootprintStampCommState commState;
    s32 playerUserIds[8]; // Last-seen DWC user ID for each player slot.
    int slotRefreshTimer;
    FootprintStampModelManager modelManager;
    FootprintStampEntry partyEntries[6]; // The player's party, as footprint entries.
    u8 selectedSlot;
    u8 paletteRow; // Palette row reserved for the selected party member.
    ManagedSprite *partySprites[6];
    ManagedSprite *partyShadowSprites[6];
    ManagedSprite *partyFootprintSprites[6];
    ManagedSprite *cursorSprite;
    ManagedSprite *playerFootprintSprites[8]; // Footprints of other players in the lobby.
    ManagedSprite *selectionSprites[3];
    u16 playerSpecies[8]; // Species currently shown in each player slot.
    u16 playerStampColors[8]; // Stamp color currently shown in each player slot.
    int state;
    u16 nameTilemapBackup[2048]; // Saved copy of the player-name tilemap.
    FootprintStampText text;
    int scrollTarget;
    int scrollOffset;
    int scrollStep;
    BOOL isArceusRoom; // Whether Arceus may be shown (from Wi-Fi room data).
} FootprintStampApp;

static void FootprintStamp_SysTask(SysTask *param0, void *param1);
static void FootprintStamp_VBlankCallback(void *param0);
static void FootprintStamp_InitGraphics(BgConfig *param0);
static void FootprintStamp_FreeGraphics(BgConfig *param0);
static void FootprintStamp_LoadBoardGraphics(FootprintStampApp *param0, NARC *param1);
static void FootprintStamp_InitWindows(FootprintStampApp *param0);
static void FootprintStamp_FreeWindows(FootprintStampApp *param0);
static G3DPipelineBuffers *FootprintStamp_InitPipeline(enum HeapID heapID);
static void FootprintStamp_Init3D(void);
static void FootprintStamp_FreePipeline(G3DPipelineBuffers *param0);
static void FootprintStamp_InitCamera(FootprintStampApp *param0);
static void FootprintStamp_FreeCamera(FootprintStampApp *param0);
static void FootprintStamp_LoadBoardModel(FootprintStampApp *param0, NARC *param1);
static void FootprintStamp_FreeBoardModel(FootprintStampApp *param0);
static void FootprintStamp_DrawBoard(FootprintStampApp *param0);
static void FootprintStamp_Noop(FootprintStampApp *param0);
static void FootprintStamp_InitCommState(FootprintStampApp *param0);
static void FootprintStamp_InitEntry(FootprintStampApp *param0, FootprintStampAddPayload *param1);
static void FootprintStamp_LoadPartyEntries(int param0, SaveData *saveData, FootprintStampEntry *param2);
static void FootprintStamp_LoadMainSprites(FootprintStampApp *param0, NARC *param1);
static void FootprintStamp_LoadSubSprites(FootprintStampApp *param0, NARC *param1);
static void FootprintStamp_CreatePartySprites(FootprintStampApp *param0);
static void FootprintStamp_FreePartySprites(FootprintStampApp *param0);
static void FootprintStamp_CreateSubSprites(FootprintStampApp *param0);
static void FootprintStamp_FreeSubSprites(FootprintStampApp *param0);
static void FootprintStamp_RefreshPartySprites(FootprintStampApp *param0);
static BOOL FootprintStamp_LoadFootprintTexture(int param0, int param1, ManagedSprite *param2, NARC *param3, NARC *param4, NNS_G2D_VRAM_TYPE param5, BOOL param6);
static void FootprintStamp_SelectPartySlot(FootprintStampApp *param0, int param1);
static void FootprintStamp_HighlightPartySlot(FootprintStampApp *param0, int param1);
static void FootprintStamp_UpdateSelectionSprites(FootprintStampApp *param0);
static int FootprintStamp_UpdatePlayerSlots(FootprintStampApp *param0);
static void FootprintStamp_CreateTextOAM(FootprintStampApp *param0, FootprintStampText *param1, const String *param2, enum Font param3, TextColor param4, int param5, int param6, int param7, int param8, int param9);
static void FootprintStamp_FreeTextOAM(FootprintStampText *param0);
static void FootprintStamp_MeasureText(const String *param0, int param1, int *param2, int *param3);
static void FootprintStamp_UpdatePartySpritePositions(FootprintStampApp *param0);
static BOOL FootprintStamp_ScrollPartySprites(FootprintStampApp *param0, int param1);

static const CameraAngle sCameraAngle = {
    0x0,
    0x0,
    0x0
};

static const RenderOamTemplate sRenderOamTemplate = {
    0x0,
    0x80,
    0x0,
    0x20,
    0x0,
    0x80,
    0x0,
    0x20
};

static const CharTransferTemplateWithModes sCharTransferTemplate = {
    0x60,
    0x10000,
    0x4000,
    GX_OBJVRAMMODE_CHAR_1D_128K,
    GX_OBJVRAMMODE_CHAR_1D_32K
};

static const SpriteResourceCapacities sSpriteResourceCapacities = {
    0x60,
    0x20,
    0x40,
    0x40,
    0x8,
    0x8
};

__attribute__((aligned(4))) static const u8 sPartyWindowPositions[][2] = {
    { 0x7, 0x5 },
    { 0x16, 0x5 },
    { 0x7, 0xA },
    { 0x16, 0xA },
    { 0x7, 0xF },
    { 0x16, 0xF },
    { 0x7, 0x14 },
    { 0x16, 0x14 }
};

__attribute__((aligned(4))) static const s16 sSubSpritePositions[][2] = {
    { 0x20, 0x30 },
    { 0x98, 0x30 },
    { 0x20, 0x58 },
    { 0x98, 0x58 },
    { 0x20, 0x80 },
    { 0x98, 0x80 },
    { 0x20, 0xA8 },
    { 0x98, 0xA8 }
};

__attribute__((aligned(4))) static const s16 sCursorSpritePositions[][2] = {
    { 0x48, 0x30 },
    { 0xC0, 0x30 },
    { 0x48, 0x58 },
    { 0xC0, 0x58 },
    { 0x48, 0x80 },
    { 0xC0, 0x80 },
    { 0x48, 0xA8 },
    { 0xC0, 0xA8 }
};

__attribute__((aligned(4))) static const u16 sPlayerSlotRects[][4] = {
    { 0x2, 0x4, 0xE, 0x4 },
    { 0x11, 0x4, 0xE, 0x4 },
    { 0x2, 0x9, 0xE, 0x4 },
    { 0x11, 0x9, 0xE, 0x4 },
    { 0x2, 0xE, 0xE, 0x4 },
    { 0x11, 0xE, 0xE, 0x4 },
    { 0x2, 0x13, 0xE, 0x4 },
    { 0x11, 0x13, 0xE, 0x4 }
};

static const u16 sEmptySlotTiles[] = {
    0x15,
    0x35,
    0x35,
    0x55
};

static const SpriteTemplate sPartySpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x35,
    0x1,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x2717, 0x2711, 0x2712, 0x2712, 0xFFFFFFFF, 0xFFFFFFFF },
    0x1,
    0x0
};

static const SpriteTemplate sPartyShadowSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x36,
    0x2,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x2717, 0x2711, 0x2712, 0x2712, 0xFFFFFFFF, 0xFFFFFFFF },
    0x1,
    0x0
};

static const SpriteTemplate sPartyFootprintSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x34,
    0x0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x2711, 0x2712, 0x2711, 0x2711, 0xFFFFFFFF, 0xFFFFFFFF },
    0x1,
    0x0
};

static const SpriteTemplate sSelectionSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x32,
    0x0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x2718, 0x2711, 0x2713, 0x2713, 0xFFFFFFFF, 0xFFFFFFFF },
    0x0,
    0x0
};

static const SpriteTemplate sCursorSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x32,
    0x0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 0x2719, 0x2714, 0x2714, 0x2714, 0xFFFFFFFF, 0xFFFFFFFF },
    0x1,
    0x0
};

static const SpriteTemplate sSubFootprintSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x33,
    0x0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 0x271A, 0x2714, 0x2715, 0x2715, 0xFFFFFFFF, 0xFFFFFFFF },
    0x1,
    0x0
};

int FootprintStamp_Init(ApplicationManager *appMan, int *param1)
{
    FootprintStampApp *v0;

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

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_118, 0x50000);

    v0 = ApplicationManager_NewData(appMan, sizeof(FootprintStampApp), HEAP_ID_118);
    MI_CpuClear8(v0, sizeof(FootprintStampApp));

    v0->args = ApplicationManager_Args(appMan);
    v0->saveData = WiFiPlazaLobby_State_GetSaveData(v0->args->unk_00);
    v0->isArceusRoom = WiFiPlazaLobby_State_IsArceusRoom(v0->args->unk_00);

    FootprintStamp_InitCommState(v0);
    FootprintStamp_LoadPartyEntries(v0->args->unk_04, v0->saveData, v0->partyEntries);

    v0->scrollTarget = (32 << 8);
    v0->scrollOffset = v0->scrollTarget;
    v0->g3dPipeline = FootprintStamp_InitPipeline(HEAP_ID_118);
    v0->paletteData = PaletteData_New(HEAP_ID_118);

    PaletteData_SetAutoTransparent(v0->paletteData, TRUE);
    PaletteData_AllocBuffer(v0->paletteData, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_118);
    PaletteData_AllocBuffer(v0->paletteData, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_118);
    PaletteData_AllocBuffer(v0->paletteData, PLTTBUF_MAIN_OBJ, PALETTE_SIZE_BYTES * 14, HEAP_ID_118);
    PaletteData_AllocBuffer(v0->paletteData, PLTTBUF_SUB_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_118);
    PaletteData_SetAutoTransparent(v0->paletteData, TRUE);

    v0->bgConfig = BgConfig_New(HEAP_ID_118);

    VramTransfer_New(64, HEAP_ID_118);
    SetAutorepeat(4, 8);

    FootprintStamp_InitGraphics(v0->bgConfig);

    EnableTouchPad();
    InitializeTouchPad(4);
    Font_InitManager(FONT_SUBSCREEN, HEAP_ID_118);

    v0->stringTemplate = StringTemplate_Default(HEAP_ID_118);
    v0->messageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0650, HEAP_ID_118);
    v0->fontOAMManager = FontOAMManager_New(4, HEAP_ID_118);
    v0->boardNarc = NARC_ctor(NARC_INDEX_GRAPHIC__FOOTPRINT_BOARD, HEAP_ID_118);
    v0->pokefootNarc = NARC_ctor(NARC_INDEX_POKETOOL__POKEFOOT__POKEFOOT, HEAP_ID_118);

    FootprintStamp_LoadBoardGraphics(v0, v0->boardNarc);
    FootprintStamp_LoadBoardModel(v0, v0->boardNarc);
    FootprintStamp_InitCamera(v0);
    FootprintStamp_InitWindows(v0);

    v0->string = String_Init(256, HEAP_ID_118);
    v0->spriteSystem = SpriteSystem_Alloc(HEAP_ID_118);

    SpriteSystem_Init(v0->spriteSystem, &sRenderOamTemplate, &sCharTransferTemplate, 16 + 16);
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_128K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    v0->spriteManager = SpriteManager_New(v0->spriteSystem);

    SpriteSystem_InitSprites(v0->spriteSystem, v0->spriteManager, 64 + 64);
    SpriteSystem_InitManagerWithCapacities(v0->spriteSystem, v0->spriteManager, &sSpriteResourceCapacities);
    SetSubScreenViewRect(SpriteSystem_GetRenderer(v0->spriteSystem), 0, (192 + 80) << FX32_SHIFT);
    NetworkIcon_Init();

    FootprintStampModels_Init(&v0->modelManager, v0->isArceusRoom);
    FootprintStamp_LoadMainSprites(v0, v0->boardNarc);
    FootprintStamp_LoadSubSprites(v0, v0->boardNarc);
    FootprintStamp_CreatePartySprites(v0);
    FootprintStamp_CreateSubSprites(v0);
    FootprintStamp_RefreshPartySprites(v0);

    v0->yesNoMenu = YesNoTouchMenu_New(HEAP_ID_118);

    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_118);

    if (v0->args->unk_00 != NULL) {
        WiFiPlazaLobby_State_SetBGMVolumeDucked(v0->args->unk_00, 1);
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);

    gSystem.whichScreenIs3D = DS_SCREEN_SUB;

    GXLayers_SwapDisplay();
    GXLayers_TurnBothDispOn();
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
    RenderControlFlags_SetCanABSpeedUpPrint(TRUE);
    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_DISABLED);
    RenderControlFlags_SetSpeedUpOnTouch(FALSE);

    v0->sysTask = SysTask_Start(FootprintStamp_SysTask, v0, 60000);

    SetVBlankCallback(FootprintStamp_VBlankCallback, v0);

    return 1;
}

int FootprintStamp_Main(ApplicationManager *appMan, int *param1)
{
    FootprintStampApp *v0 = ApplicationManager_Data(appMan);

    FootprintStampModels_Update(&v0->modelManager, v0->camera, v0->state, v0->args->unk_04);

    switch (*param1) {
    case 0:
        v0->commState.isActive = 1;
        FootprintStampComm_Init(v0);

        {
            FootprintStampAddPayload v1;
            FootprintStamp_InitEntry(v0, &v1);
        }
        (*param1)++;
        break;
    case 1:
        if (IsScreenFadeDone() == TRUE) {
            v0->state = 1;
            (*param1)++;
        }
        break;
    case 2:
        if (gSystem.touchPressed && (gSystem.touchY < 160)) {
            if (FootprintStamp_ScrollPartySprites(v0, (32 << 8) / 6) == 1) {
                v0->partyEntries[v0->selectedSlot].touchX = gSystem.touchX;
                v0->partyEntries[v0->selectedSlot].touchY = gSystem.touchY;

                FootprintStamp_AddEntry(v0, &v0->partyEntries[v0->selectedSlot], v0->commState.localUserId);
                FootprintStampComm_SendEntry(&v0->partyEntries[v0->selectedSlot]);
            } else {
                (void)0;
            }
        }

        {
            int v2;
            v2 = FootprintStampPlayers_CheckTouch(v0->partyEntries, v0->selectedSlot);

            if (v2 < 6) {
                v0->selectedSlot = v2;
                FootprintStamp_SelectPartySlot(v0, v2);
            } else if (((*param1) == 2) && (v2 == 0xfe)) {
                Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);
                PaletteData_Blend(v0->paletteData, PLTTBUF_MAIN_BG, 0 * 16 + 9, 1, 8, 0x0);
                PaletteData_Blend(v0->paletteData, PLTTBUF_MAIN_OBJ, v0->paletteRow * 16, 16, 8, 0x0);
                *param1 = 3;
            }
        }
        break;
    case 3:
        Window_FillTilemap(&v0->messageWindow, 0xf);
        Window_DrawMessageBoxWithScrollCursor(&v0->messageWindow, 0, 1, 14);
        MessageLoader_GetString(v0->messageLoader, 2, v0->string);
        v0->printerId = Text_AddPrinterWithParams(&v0->messageWindow, FONT_MESSAGE, v0->string, 0, 0, Options_TextFrameDelay(SaveData_GetOptions(v0->saveData)), NULL);
        (*param1)++;
        break;
    case 4:
        if (Text_IsPrinterActive(v0->printerId) == 0) {
            YesNoTouchMenuParams v3;

            v3.bgConfig = v0->bgConfig;
            v3.bgLayer = BG_LAYER_MAIN_1;
            v3.baseTile = (1 + (18 + 12));
            v3.palette = 11;
            v3.tilemapLeft = 25;
            v3.tilemapTop = 6;

            YesNoTouchMenu_InitWithParams(v0->yesNoMenu, &v3);

            v0->menuOpen = 1;
            (*param1)++;
        }

        break;
    case 5:
        PaletteData_LoadBufferFromHardware(v0->paletteData, PLTTBUF_MAIN_BG, PLTT_DEST(11), PALETTE_SIZE_BYTES * 2);
        {
            u32 v4 = YesNoTouchMenu_ProcessInput(v0->yesNoMenu);

            switch (v4) {
            case YES_NO_TOUCH_MENU_YES:
                YesNoTouchMenu_Reset(v0->yesNoMenu);
                v0->menuOpen = 0;
                Window_EraseMessageBox(&v0->messageWindow, 0);
                v0->commState.isActive = 0;
                v0->state = 3;
                *param1 = 9;
                break;
            case YES_NO_TOUCH_MENU_NO:
                YesNoTouchMenu_Reset(v0->yesNoMenu);
                v0->menuOpen = 0;
                Window_EraseMessageBox(&v0->messageWindow, 0);
                PaletteData_Blend(v0->paletteData, PLTTBUF_MAIN_BG, 0 * 16 + 9, 1, 0, 0x0);
                PaletteData_Blend(v0->paletteData, PLTTBUF_MAIN_OBJ, v0->paletteRow * 16, 16, 0, 0x0);
                *param1 = 2;
                break;
            }
        }
        break;
    case 6:
        Window_FillTilemap(&v0->messageWindow, 0xf);
        Window_DrawMessageBoxWithScrollCursor(&v0->messageWindow, 0, 1, 14);
        MessageLoader_GetString(v0->messageLoader, 3, v0->string);
        v0->printerId = Text_AddPrinterWithParams(&v0->messageWindow, FONT_MESSAGE, v0->string, 0, 0, Options_TextFrameDelay(SaveData_GetOptions(v0->saveData)), NULL);
        (*param1)++;
        break;
    case 7:
        if (Text_IsPrinterActive(v0->printerId) == 0) {
            (*param1)++;
        }
        break;
    case 8:
        v0->waitFrames++;

        if (v0->waitFrames > 90) {
            *param1 = 9;
        }
        break;
    case 9:
        if (IsScreenFadeDone() == FALSE) {
            FinishScreenFade();
        }

        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_118);
        (*param1)++;
        break;
    case 10:
        if (IsScreenFadeDone() == TRUE) {
            (*param1)++;
        }
        break;
    default:
        WiFiPlazaLobby_Network_ClearSubChannelMessageHandler();
        return 1;
    }

    FootprintStamp_UpdateSelectionSprites(v0);
    FootprintStamp_UpdatePartySpritePositions(v0);

    if (v0->state == 1) {
        v0->slotRefreshTimer++;

        if (v0->slotRefreshTimer > 30) {
            v0->slotRefreshTimer = 0;
            FootprintStamp_UpdatePlayerSlots(v0);
        }

        if (((WiFiPlazaLobby_Time_HasWifiError() == 1) || (WiFiPlazaLobby_State_IsLobbyClosed(v0->args->unk_00) == 1)) && ((*param1) != 4)) {
            if (v0->menuOpen == 1) {
                YesNoTouchMenu_Reset(v0->yesNoMenu);
            }

            v0->commState.isActive = 0;
            v0->state = 3;

            if (WiFiPlazaLobby_Time_HasWifiError() == 1) {
                (*param1) = 9;
            } else {
                Sound_PlayEffect(SEQ_SE_DP_PINPON_sseq);
                WiFiPlazaLobby_State_SetPlayerWarpPending(v0->args->unk_00);
                (*param1) = 6;
            }
        }
    }

    FootprintStamp_Noop(v0);

    return 0;
}

int FootprintStamp_Exit(ApplicationManager *appMan, int *param1)
{
    FootprintStampApp *v0 = ApplicationManager_Data(appMan);

    SysTask_Done(v0->sysTask);
    FootprintStamp_FreePartySprites(v0);
    FootprintStamp_FreeSubSprites(v0);
    YesNoTouchMenu_Free(v0->yesNoMenu);
    FootprintStampModels_Free(&v0->modelManager);

    String_Free(v0->string);
    Font_Free(FONT_SUBSCREEN);
    FontOAMManager_Free(v0->fontOAMManager);
    MessageLoader_Free(v0->messageLoader);
    StringTemplate_Free(v0->stringTemplate);

    FootprintStamp_FreeWindows(v0);
    FootprintStamp_FreeGraphics(v0->bgConfig);

    Heap_Free(v0->bgConfig);
    SpriteSystem_FreeResourcesAndManager(v0->spriteSystem, v0->spriteManager);
    SpriteSystem_Free(v0->spriteSystem);
    PaletteData_FreeBuffer(v0->paletteData, PLTTBUF_MAIN_BG);
    PaletteData_FreeBuffer(v0->paletteData, PLTTBUF_SUB_BG);
    PaletteData_FreeBuffer(v0->paletteData, PLTTBUF_MAIN_OBJ);
    PaletteData_FreeBuffer(v0->paletteData, PLTTBUF_SUB_OBJ);
    PaletteData_Free(v0->paletteData);

    FootprintStamp_FreeBoardModel(v0);
    FootprintStamp_FreeCamera(v0);
    FootprintStamp_FreePipeline(v0->g3dPipeline);

    NARC_dtor(v0->boardNarc);
    NARC_dtor(v0->pokefootNarc);
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    VramTransfer_Free();
    DisableTouchPad();
    RenderControlFlags_SetCanABSpeedUpPrint(FALSE);
    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_DISABLED);
    RenderControlFlags_SetSpeedUpOnTouch(FALSE);
    NetworkIcon_Destroy();
    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_118);

    return 1;
}

static void FootprintStamp_SysTask(SysTask *param0, void *param1)
{
    FootprintStampApp *v0 = param1;

    FootprintStampModels_UpdateAnimations(&v0->modelManager);
    FootprintStamp_DrawBoard(v0);

    SpriteSystem_DrawSprites(v0->spriteManager);
    SpriteSystem_UpdateTransfer();
    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
}

static void FootprintStamp_VBlankCallback(void *param0)
{
    FootprintStampApp *v0 = param0;

    FootprintStampModels_FlushTextures(&v0->modelManager, v0->state);

    VramTransfer_Process();
    SpriteSystem_TransferOam();
    PaletteData_CommitFadedBuffers(v0->paletteData);
    Bg_RunScheduledUpdates(v0->bgConfig);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void FootprintStamp_InitGraphics(BgConfig *param0)
{
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();

    {
        GXBanks v0 = {
            GX_VRAM_BG_128_C,
            GX_VRAM_BGEXTPLTT_NONE,
            GX_VRAM_SUB_BG_32_H,
            GX_VRAM_SUB_BGEXTPLTT_NONE,
            GX_VRAM_OBJ_64_E,
            GX_VRAM_OBJEXTPLTT_NONE,
            GX_VRAM_SUB_OBJ_16_I,
            GX_VRAM_SUB_OBJEXTPLTT_NONE,
            GX_VRAM_TEX_01_AB,
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
            GX_BG0_AS_3D,
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
                .screenBase = GX_BG_SCRBASE_0x0000,
                .charBase = GX_BG_CHARBASE_0x08000,
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
                .screenBase = GX_BG_SCRBASE_0x0800,
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
                .screenBase = GX_BG_SCRBASE_0x1000,
                .charBase = GX_BG_CHARBASE_0x10000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_1, &v2[0], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_1);
        Bg_SetOffset(param0, BG_LAYER_MAIN_1, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_1, 3, 0);

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_2, &v2[1], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_2);
        Bg_SetOffset(param0, BG_LAYER_MAIN_2, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_2, 3, 0);

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_3, &v2[2], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_3);
        Bg_SetOffset(param0, BG_LAYER_MAIN_3, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_3, 3, 0);

        G2_SetBG0Priority(2);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
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
                .screenBase = GX_BG_SCRBASE_0x7000,
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
                .screenBase = GX_BG_SCRBASE_0x7800,
                .charBase = GX_BG_CHARBASE_0x00000,
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
                .screenBase = GX_BG_SCRBASE_0x6800,
                .charBase = GX_BG_CHARBASE_0x00000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_1, &v3[0], 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_1);
        Bg_SetOffset(param0, BG_LAYER_SUB_1, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_SUB_1, 3, 0);

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_2, &v3[1], 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_2);
        Bg_SetOffset(param0, BG_LAYER_SUB_2, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_SUB_2, 3, 0);

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_3, &v3[2], 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_3);
        Bg_SetOffset(param0, BG_LAYER_SUB_3, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_SUB_3, 3, 0);
    }

    Bg_ClearTilesRange(5, 32, 0, HEAP_ID_118);
}

static void FootprintStamp_FreeGraphics(BgConfig *param0)
{
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_2);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_3);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_1);
}

static void FootprintStamp_LoadBoardGraphics(FootprintStampApp *param0, NARC *param1)
{
    BgConfig *v0 = param0->bgConfig;
    u16 *v1;

    PaletteData_LoadBufferFromFileStart(param0->paletteData, NARC_INDEX_GRAPHIC__FOOTPRINT_BOARD, 19, HEAP_ID_118, PLTTBUF_MAIN_BG, 0x200 - 0x40, 0);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 18, param0->bgConfig, 2, 0, 0, 0, HEAP_ID_118);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 17, param0->bgConfig, 2, 0, 0, 0, HEAP_ID_118);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 20, param0->bgConfig, 3, 0, 0, 0, HEAP_ID_118);
    PaletteData_LoadBufferFromFileStart(param0->paletteData, NARC_INDEX_GRAPHIC__FOOTPRINT_BOARD, 23, HEAP_ID_118, PLTTBUF_SUB_BG, 0, 0);

    if (param0->args->unk_04 == 0) {
        PaletteData_CopyBuffer(param0->paletteData, 1, 16 * 1, 1, 16 * 0, PALETTE_SIZE_BYTES);
    }

    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 22, param0->bgConfig, 6, 0, 0, 0, HEAP_ID_118);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 21, param0->bgConfig, 6, 0, 0, 0, HEAP_ID_118);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 24, param0->bgConfig, 7, 0, 0, 0, HEAP_ID_118);

    v1 = Bg_GetTilemapBuffer(param0->bgConfig, 6);

    MI_CpuCopy16(v1, param0->nameTilemapBackup, 0x800);
    MI_CpuClear16(v1, 0x800);

    {
        int v2;
        v2 = Options_Frame(SaveData_GetOptions(param0->saveData));

        PaletteData_LoadBufferFromFileStart(param0->paletteData, NARC_INDEX_GRAPHIC__PL_WINFRAME, GetMessageBoxPaletteNARCMember(v2), HEAP_ID_118, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
        LoadMessageBoxGraphics(param0->bgConfig, BG_LAYER_MAIN_1, 1, 14, v2, HEAP_ID_118);
        PaletteData_LoadBufferFromFileStart(param0->paletteData, NARC_INDEX_GRAPHIC__PL_FONT, 6, HEAP_ID_118, 0, PALETTE_SIZE_BYTES, PLTT_DEST(13));

        if (param0->args->unk_04 == 0) {
            PaletteData_LoadBufferFromFileStart(param0->paletteData, NARC_INDEX_GRAPHIC__PL_FONT, 6, HEAP_ID_118, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES, PLTT_DEST(13));
        } else {
            PaletteData_LoadBufferFromFileStart(param0->paletteData, NARC_INDEX_GRAPHIC__FOOTPRINT_BOARD, 25, HEAP_ID_118, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES, PLTT_DEST(13));
        }
    }

    Bg_ScheduleTilemapTransfer(param0->bgConfig, 6);
}

static void FootprintStamp_LoadMainSprites(FootprintStampApp *param0, NARC *param1)
{
    int v0, v1;
    u16 v2;

    SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->paletteData, PLTTBUF_MAIN_OBJ, param0->spriteSystem, param0->spriteManager, param1, 3, FALSE, 3, NNS_G2D_VRAM_TYPE_2DMAIN, 10001);
    SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 4, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 10007);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 5, FALSE, 10002);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 6, FALSE, 10002);

    for (v0 = 0; v0 < 6; v0++) {
        SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 16, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 10001 + v0);
    }

    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 15, FALSE, 10001);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 14, FALSE, 10001);

    v1 = SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->paletteData, PLTTBUF_MAIN_OBJ, param0->spriteSystem, param0->spriteManager, param1, 3, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 10002);

    if (param0->args->unk_04 == 0) {
        v2 = 0x0;
    } else {
        v2 = 0x7fff;
    }

    PaletteData_FillBufferRange(param0->paletteData, PLTTBUF_MAIN_OBJ, PLTTSEL_BOTH, v2, v1 * 16, v1 * 16 + 16);
    SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 2, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 10008);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 1, FALSE, 10003);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 0, FALSE, 10003);

    param0->paletteRow = SpriteSystem_LoadPaletteBuffer(param0->paletteData, 2, param0->spriteSystem, param0->spriteManager, 187, 26, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 10003);
}

static void FootprintStamp_CreatePartySprites(FootprintStampApp *param0)
{
    int v0;
    SpriteTemplate v1;

    v1 = sPartySpriteTemplate;

    for (v0 = 0; v0 < 6; v0++) {
        v1.x = 16 + 32 * v0;
        v1.y = 176;

        param0->partySprites[v0] = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v1);

        ManagedSprite_SetAnim(param0->partySprites[v0], v0);
        Sprite_TickFrame(param0->partySprites[v0]->sprite);
    }

    v1 = sPartyShadowSpriteTemplate;

    for (v0 = 0; v0 < 6; v0++) {
        v1.x = 16 + 32 * v0;
        v1.y = 176;

        param0->partyShadowSprites[v0] = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v1);

        ManagedSprite_SetAnim(param0->partyShadowSprites[v0], v0);
        Sprite_TickFrame(param0->partyShadowSprites[v0]->sprite);
    }

    v1 = sPartyFootprintSpriteTemplate;

    for (v0 = 0; v0 < 6; v0++) {
        v1.x = 16 + 32 * v0;
        v1.y = 176;
        v1.resources[0] = 10001 + v0;

        param0->partyFootprintSprites[v0] = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v1);
        Sprite_TickFrame(param0->partyFootprintSprites[v0]->sprite);
    }

    {
        String *v2;

        v2 = MessageLoader_GetNewString(param0->messageLoader, 1);
        FootprintStamp_CreateTextOAM(param0, &param0->text, v2, FONT_SUBSCREEN, TEXT_COLOR(1, 2, 3), 0, 10003, 0x1c * 8, 176, 1);
        FontOAM_SetDrawFlag(param0->text.oam, 1);
        String_Free(v2);
    }
}

static void FootprintStamp_FreePartySprites(FootprintStampApp *param0)
{
    int v0;

    for (v0 = 0; v0 < 6; v0++) {
        Sprite_DeleteAndFreeResources(param0->partySprites[v0]);
    }

    for (v0 = 0; v0 < 6; v0++) {
        Sprite_DeleteAndFreeResources(param0->partyShadowSprites[v0]);
    }

    for (v0 = 0; v0 < 6; v0++) {
        Sprite_DeleteAndFreeResources(param0->partyFootprintSprites[v0]);
    }

    FootprintStamp_FreeTextOAM(&param0->text);
}

static void FootprintStamp_LoadSubSprites(FootprintStampApp *param0, NARC *param1)
{
    int v0;

    SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->paletteData, PLTTBUF_SUB_OBJ, param0->spriteSystem, param0->spriteManager, param1, 10, FALSE, 1, NNS_G2D_VRAM_TYPE_2DSUB, 10004);
    SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 9, FALSE, NNS_G2D_VRAM_TYPE_2DSUB, 10009);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 8, FALSE, 10004);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 7, FALSE, 10004);

    for (v0 = 0; v0 < 8; v0++) {
        SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 13, FALSE, NNS_G2D_VRAM_TYPE_2DSUB, 10010 + v0);
    }

    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 12, FALSE, 10005);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 11, FALSE, 10005);
}

static void FootprintStamp_CreateSubSprites(FootprintStampApp *param0)
{
    int v0;
    SpriteTemplate v1;

    param0->cursorSprite = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &sCursorSpriteTemplate);

    Sprite_TickFrame(param0->cursorSprite->sprite);
    ManagedSprite_SetDrawFlag(param0->cursorSprite, 0);

    v1 = sSubFootprintSpriteTemplate;

    for (v0 = 0; v0 < 8; v0++) {
        v1.resources[0] = 10010 + v0;
        param0->playerFootprintSprites[v0] = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v1);

        ManagedSprite_SetPositionXYWithSubscreenOffset(param0->playerFootprintSprites[v0], sSubSpritePositions[v0][0], sSubSpritePositions[v0][1], (192 + 80) << FX32_SHIFT);
        Sprite_TickFrame(param0->playerFootprintSprites[v0]->sprite);
        ManagedSprite_SetDrawFlag(param0->playerFootprintSprites[v0], 0);
    }
}

static void FootprintStamp_FreeSubSprites(FootprintStampApp *param0)
{
    int v0;

    Sprite_DeleteAndFreeResources(param0->cursorSprite);

    for (v0 = 0; v0 < 8; v0++) {
        Sprite_DeleteAndFreeResources(param0->playerFootprintSprites[v0]);
    }
}

static void FootprintStamp_RefreshPartySprites(FootprintStampApp *param0)
{
    int v0, v1;
    u16 *v2, *v3;
    int v4 = 0;

    v2 = PaletteData_GetUnfadedBuffer(param0->paletteData, 2);
    v3 = PaletteData_GetFadedBuffer(param0->paletteData, 2);

    for (v0 = 0; v0 < 6; v0++) {
        if ((param0->partyEntries[v0].species == 0) || (param0->partyEntries[v0].species > NATIONAL_DEX_COUNT)) {
            ManagedSprite_SetDrawFlag(param0->partySprites[v0], 0);
            ManagedSprite_SetDrawFlag(param0->partyShadowSprites[v0], 0);
            ManagedSprite_SetDrawFlag(param0->partyFootprintSprites[v0], 0);

            for (v1 = 0; v1 < 4; v1++) {
                Bg_FillTilemapRect(param0->bgConfig, 2, sEmptySlotTiles[v1], 0 + 4 * v0, 0x14 + v1, 4, 1, 17);
            }
        } else {
            FootprintStamp_LoadFootprintTexture(param0->partyEntries[v0].species, param0->partyEntries[v0].form, param0->partyFootprintSprites[v0], param0->boardNarc, param0->pokefootNarc, NNS_G2D_VRAM_TYPE_2DMAIN, param0->isArceusRoom);

            v2[1 * 16 + 1 + v0] = param0->partyEntries[v0].stampColor;
            v3[1 * 16 + 1 + v0] = param0->partyEntries[v0].stampColor;

            BlendPalette(&v2[1 * 16 + 1 + v0], &v2[2 * 16 + 1 + v0], 1, 12, 0x0);
            v3[2 * 16 + 1 + v0] = v2[2 * 16 + 1 + v0];

            if (v4 == 0) {
                v4++;
                param0->selectedSlot = v0;
            }
        }
    }

    FootprintStamp_HighlightPartySlot(param0, 0);
    Bg_ScheduleTilemapTransfer(param0->bgConfig, 2);
}

static BOOL FootprintStamp_LoadFootprintTexture(int param0, int param1, ManagedSprite *param2, NARC *param3, NARC *param4, NNS_G2D_VRAM_TYPE param5, BOOL param6)
{
    void *v0;
    NNSG2dImageProxy *v1;
    void *v2;
    NNSG2dCharacterData *v3;
    u8 *v4, *v5;

    if ((param0 == 0) || (param0 > NATIONAL_DEX_COUNT)) {
        return 0;
    }

    if (PokemonHasOverworldFootprint(param0, param1, param6) == 1) {
        v2 = LoadMemberFromOpenNARC(param4, 3 + param0, 1, HEAP_ID_118, 1);
        NNS_G2dGetUnpackedCharacterData(v2, &v3);
        DC_FlushRange(v3->pRawData, 0x20 * 8);
        v4 = &((u8 *)v3->pRawData)[0x20 * 4];
        v5 = v3->pRawData;
    } else {
        v2 = LoadMemberFromOpenNARC(param3, 16, 0, HEAP_ID_118, 1);
        NNS_G2dGetUnpackedCharacterData(v2, &v3);
        DC_FlushRange(v3->pRawData, 0x20 * 4);
        v4 = v3->pRawData;
        v5 = &((u8 *)v3->pRawData)[0x20 * 2];
    }

    if (param5 == NNS_G2D_VRAM_TYPE_2DMAIN) {
        v0 = G2_GetOBJCharPtr();
    } else {
        v0 = G2S_GetOBJCharPtr();
    }

    v1 = Sprite_GetImageProxy(param2->sprite);

    MI_CpuCopy16(v4, (void *)((u32)v0 + v1->vramLocation.baseAddrOfVram[param5]), 0x20 * 2);
    MI_CpuCopy16(v5, (void *)((u32)v0 + 0x20 * 2 + v1->vramLocation.baseAddrOfVram[param5]), 0x20 * 2);

    Heap_Free(v2);
    return 1;
}

static void FootprintStamp_InitCamera(FootprintStampApp *param0)
{
    VecFx32 v0 = { 0, -FX32_ONE * 8, 0 };

    param0->camera = Camera_Alloc(HEAP_ID_118);

    Camera_InitWithTarget(&v0, 0x7c000, &sCameraAngle, (22 * 0xffff) / 360, 0, 0, param0->camera);
    Camera_SetClipping(FX32_ONE, FX32_ONE * 900, param0->camera);
    Camera_SetAsActive(param0->camera);

    {
        u16 v1;
        fx32 v2, v3;
        fx32 v4, v5;

        v1 = Camera_GetFOV(param0->camera);
        v2 = Camera_GetDistance(param0->camera);
        v3 = FX32_ONE * 4 / 3;

        CalcLinearFov(v1, v2, v3, &v4, &v5);

        param0->fovX = v4;
        param0->fovY = v5;
    }
}

static void FootprintStamp_FreeCamera(FootprintStampApp *param0)
{
    Camera_Delete(param0->camera);
}

static void FootprintStamp_LoadBoardModel(FootprintStampApp *param0, NARC *param1)
{
    int v0;

    if (param0->args->unk_04 == 0) {
        v0 = 28;
    } else {
        v0 = 27;
    }

    Easy3DModel_LoadFrom(&param0->boardModel.model, param1, v0, HEAP_ID_118);
    Easy3DObject_Init(&param0->boardModel.object, &param0->boardModel.model);
    Easy3DObject_SetPosition(&param0->boardModel.object, FX32_CONST(0), FX32_CONST(0), FX32_CONST(0));
    Easy3DObject_SetScale(&param0->boardModel.object, FX32_CONST(1.00f), FX32_CONST(1.00f), FX32_CONST(1.00f));
    Easy3DObject_SetVisible(&param0->boardModel.object, 1);
}

static void FootprintStamp_FreeBoardModel(FootprintStampApp *param0)
{
    Easy3DModel_Release(&param0->boardModel.model);
}

static void FootprintStamp_DrawBoard(FootprintStampApp *param0)
{
    VecFx32 v0, v1;
    MtxFx33 v2;

    v0.x = FX32_ONE;
    v0.y = FX32_ONE;
    v0.z = FX32_ONE;

    v1.x = 0;
    v1.y = 0;
    v1.z = 0;

    MTX_Identity33(&v2);

    G3_ResetG3X();
    Camera_SetAsActive(param0->camera);
    Camera_ComputeProjectionMatrix(0, param0->camera);
    Camera_ComputeViewMatrix();

    NNS_G3dGlbLightVector(0, 0, -FX32_ONE, 0);
    NNS_G3dGlbLightColor(0, GX_RGB(28, 28, 28));
    NNS_G3dGlbMaterialColorDiffAmb(GX_RGB(31, 31, 31), GX_RGB(31, 31, 31), 0);
    NNS_G3dGlbMaterialColorSpecEmi(GX_RGB(31, 31, 31), GX_RGB(31, 31, 31), 0);
    NNS_G3dGlbSetBaseTrans(&v1);
    NNS_G3dGlbSetBaseRot(&v2);
    NNS_G3dGlbSetBaseScale(&v0);
    NNS_G3dGePushMtx();

    {
        Easy3DObject_Draw(&param0->boardModel.object);
        FootprintStampModels_Draw(&param0->modelManager);
    }

    NNS_G3dGePopMtx(1);
}

static void FootprintStamp_InitWindows(FootprintStampApp *param0)
{
    int v0;

    Window_Add(param0->bgConfig, &param0->messageWindow, 1, 2, 1, 27, 4, 13, (1 + (18 + 12)) + (29 * 4));
    Window_FillTilemap(&param0->messageWindow, 0xf);

    for (v0 = 0; v0 < 8; v0++) {
        Window_Add(param0->bgConfig, &param0->playerWindows[v0], 5, sPartyWindowPositions[v0][0], sPartyWindowPositions[v0][1], 8, 2, 13, (0x4000 / 0x20) + (8 * 2) * v0);
        Window_FillTilemap(&param0->playerWindows[v0], 0x0);
    }
}

static void FootprintStamp_FreeWindows(FootprintStampApp *param0)
{
    int v0;

    Window_Remove(&param0->messageWindow);

    for (v0 = 0; v0 < 8; v0++) {
        Window_Remove(&param0->playerWindows[v0]);
    }
}

static G3DPipelineBuffers *FootprintStamp_InitPipeline(enum HeapID heapID)
{
    return G3DPipeline_Init(heapID, TEXTURE_VRAM_SIZE_256K, PALETTE_VRAM_SIZE_32K, FootprintStamp_Init3D);
}

static void FootprintStamp_Init3D(void)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    G2_SetBG0Priority(1);

    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(1);
    G3X_AlphaTest(0, 0);
    G3X_AlphaBlend(1);
    G3X_EdgeMarking(0);
    G3X_SetFog(0, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0);
    G3X_SetClearColor(GX_RGB(0, 0, 0), 0, 0x7fff, 63, 0);
    G3_ViewPort(0, 0, 255, 191);
}

static void FootprintStamp_FreePipeline(G3DPipelineBuffers *param0)
{
    G3DPipelineBuffers_Free(param0);
}

static void FootprintStamp_InitCommState(FootprintStampApp *param0)
{
    FootprintStampCommState *v0 = &param0->commState;
    v0->localUserId = WiFiPlazaLobby_Network_GetMyUserId();
}

static void FootprintStamp_InitEntry(FootprintStampApp *param0, FootprintStampAddPayload *param1)
{
    FootprintStampEntry *v0;

    MI_CpuClear8(param1, sizeof(FootprintStampAddPayload));

    v0 = &param1->entry;

    v0->species = 150;
    v0->stampColor = 0x1f;
    v0->personality = 0x101;
    v0->form = 0;
}

FootprintStampCommState *FootprintStamp_GetCommState(FootprintStampApp *param0)
{
    return &param0->commState;
}

static void FootprintStamp_LoadPartyEntries(int param0, SaveData *saveData, FootprintStampEntry *param2)
{
    Party *v0;
    int v1;
    Pokemon *v2;
    int v3;

    MI_CpuClear8(param2, sizeof(FootprintStampEntry) * 6);

    v0 = SaveData_GetParty(saveData);
    v1 = Party_GetCurrentCount(v0);

    for (v3 = 0; v3 < v1; v3++) {
        v2 = Party_GetPokemonBySlotIndex(v0, v3);
        param2[v3].species = Pokemon_GetValue(v2, MON_DATA_SPECIES_OR_EGG, NULL);
        param2[v3].personality = Pokemon_GetValue(v2, MON_DATA_PERSONALITY, NULL);
        param2[v3].form = Pokemon_GetValue(v2, MON_DATA_FORM, NULL);
        param2[v3].stampColor = FootprintStampPlayers_GetStampColor(param0, Pokemon_GetValue(v2, MON_DATA_OT_ID, NULL));
    }
}

BOOL FootprintStamp_AddEntry(FootprintStampApp *param0, const FootprintStampEntry *param1, s32 param2)
{
    int v0;
    u32 v1;

    v0 = FootprintStampModels_Add(param0, &param0->modelManager, param1, param0->boardNarc, param0->pokefootNarc, param0->isArceusRoom);

    if (v0 == 1) {
        v1 = WiFiPlazaLobby_Network_FindSubChannelPlayerIndex(param2);

        if (v1 != 0xffffffff) {
            if ((param0->playerSpecies[v1] != param1->species) || (param0->playerStampColors[v1] != param1->stampColor)) {
                param0->playerSpecies[v1] = param1->species;
                param0->playerStampColors[v1] = param1->stampColor;
                FootprintStamp_LoadFootprintTexture(param1->species, param1->form, param0->playerFootprintSprites[v1], param0->boardNarc, param0->pokefootNarc, NNS_G2D_VRAM_TYPE_2DSUB, param0->isArceusRoom);
                ManagedSprite_SetDrawFlag(param0->playerFootprintSprites[v1], 1);
                PaletteData_FillBufferRange(param0->paletteData, PLTTBUF_SUB_BG, PLTTSEL_BOTH, param1->stampColor, (2 * 16 + 1) + v1, (2 * 16 + 1) + v1 + 1);
            }
        }

        Sound_PlayEffect(SEQ_SE_DP_BOX02_sseq);
    }

    return v0;
}

static int FootprintStamp_UpdatePlayerSlots(FootprintStampApp *param0)
{
    WiFiPlazaLobbyNetworkPlayerIdList v0;
    int v1, v2, v3, v4;

    v2 = 0;
    v3 = 0;

    WiFiPlazaLobby_Network_GetSubChannelPlayerList(&v0);

    for (v1 = 0; v1 < 8; v1++) {
        if (param0->playerUserIds[v1] != v0.unk_04[v1]) {
            if (v0.unk_04[v1] != DWC_LOBBY_INVALID_USER_ID) {
                FootprintStampPlayers_DrawName(param0->messageLoader, param0->stringTemplate, param0->playerWindows, param0->args->unk_00, v0.unk_04[v1]);

                {
                    u16 *v5;
                    int v6, v7;

                    v5 = Bg_GetTilemapBuffer(param0->bgConfig, 6);

                    for (v7 = sPlayerSlotRects[v1][1]; v7 < sPlayerSlotRects[v1][1] + sPlayerSlotRects[v1][3]; v7++) {
                        MI_CpuCopy16(&param0->nameTilemapBackup[v7 * 32 + sPlayerSlotRects[v1][0]], &v5[v7 * 32 + sPlayerSlotRects[v1][0]], sPlayerSlotRects[v1][2] * 2);
                    }

                    Bg_ScheduleTilemapTransfer(param0->bgConfig, 6);
                }

                v2++;
            } else {
                FootprintStampPlayers_ClearName(param0->playerWindows, v1);

                param0->playerSpecies[v1] = 0;
                param0->playerStampColors[v1] = 0;

                ManagedSprite_SetDrawFlag(param0->playerFootprintSprites[v1], 0);
                Bg_FillTilemapRect(param0->bgConfig, 6, 0, sPlayerSlotRects[v1][0], sPlayerSlotRects[v1][1], sPlayerSlotRects[v1][2], sPlayerSlotRects[v1][3], 16);
                Bg_ScheduleTilemapTransfer(param0->bgConfig, 6);
                v3++;
            }

            if (v0.unk_04[v1] == param0->commState.localUserId) {
                ManagedSprite_SetPositionXYWithSubscreenOffset(param0->cursorSprite, sCursorSpritePositions[v1][0], sCursorSpritePositions[v1][1], (192 + 80) << FX32_SHIFT);
                ManagedSprite_SetDrawFlag(param0->cursorSprite, 1);
            }
        }

        param0->playerUserIds[v1] = v0.unk_04[v1];
    }

    v4 = 0;

    for (v1 = 0; v1 < 8; v1++) {
        if (param0->playerUserIds[v1] != DWC_LOBBY_INVALID_USER_ID) {
            v4++;
        }
    }

    param0->modelManager.playerCount = v4;

    if (v2 > 0) {
        Sound_PlayEffect(SEQ_SE_DP_BUTTON9_sseq);
        return 1;
    } else if (v3 > 0) {
        Sound_PlayEffect(SEQ_SE_DP_BUTTON9_sseq);
        return 2;
    }

    return 0;
}

void FootprintStamp_DrawPlayerName(FootprintStampApp *param0, s32 param1)
{
    FootprintStampPlayers_DrawName(param0->messageLoader, param0->stringTemplate, param0->playerWindows, param0->args->unk_00, param1);
}

void FootprintStamp_ClearPlayerName(FootprintStampApp *param0, u32 param1)
{
    FootprintStampPlayers_ClearName(param0->playerWindows, param1);
}

static void FootprintStamp_SelectPartySlot(FootprintStampApp *param0, int param1)
{
    SpriteTemplate v0;
    int v1;

    v0 = sSelectionSpriteTemplate;

    for (v1 = 0; v1 < 3; v1++) {
        if (param0->selectionSprites[v1] == NULL) {
            v0.x = 16 + 32 * param1;
            v0.y = 176;
            param0->selectionSprites[v1] = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v0);

            break;
        }
    }

    FootprintStamp_HighlightPartySlot(param0, param1);
    Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);
}

static void FootprintStamp_HighlightPartySlot(FootprintStampApp *param0, int param1)
{
    u16 *v0, *v1;

    v0 = PaletteData_GetUnfadedBuffer(param0->paletteData, 2);
    v1 = PaletteData_GetFadedBuffer(param0->paletteData, 2);

    MI_CpuCopy16(&v0[1 * 16 + 1], &v1[1 * 16 + 1], 6 * 2);
    BlendPalette(&v0[1 * 16 + 1 + param1], &v1[1 * 16 + 1 + param1], 1, 6, 0x0);
}

static void FootprintStamp_UpdateSelectionSprites(FootprintStampApp *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        if (param0->selectionSprites[v0] != NULL) {
            if (ManagedSprite_IsAnimated(param0->selectionSprites[v0]) == 0) {
                Sprite_DeleteAndFreeResources(param0->selectionSprites[v0]);
                param0->selectionSprites[v0] = NULL;
            } else {
                Sprite_TickFrame(param0->selectionSprites[v0]->sprite);
            }
        }
    }
}

static void FootprintStamp_CreateTextOAM(FootprintStampApp *param0, FootprintStampText *param1, const String *param2, enum Font param3, TextColor param4, int param5, int param6, int param7, int param8, int param9)
{
    FontOAMTemplate v0;
    Window v1;
    CharTransferAllocation v2;
    int v3;
    FontOAM *v4;
    BgConfig *v5;
    SpriteManager *v6;
    int v7, v8;

    GF_ASSERT(param1->oam == NULL);

    v5 = param0->bgConfig;
    v6 = param0->spriteManager;

    FootprintStamp_MeasureText(param2, param3, &v7, &v8);

    Window_Init(&v1);
    Window_AddToTopLeftCorner(v5, &v1, v8, 16 / 8, 0, 0);
    Text_AddPrinterWithParamsColorAndSpacing(&v1, param3, param2, 0, 0, TEXT_SPEED_NO_TRANSFER, param4, 0, 0, NULL);

    v3 = FontOAM_GetWindowSize(&v1, NNS_G2D_VRAM_TYPE_2DMAIN, HEAP_ID_118);
    CharTransfer_AllocRange(v3, 1, NNS_G2D_VRAM_TYPE_2DMAIN, &v2);

    if (param9 == 1) {
        param7 -= v7 / 2;
    }

    param8 -= 8;

    v0.fontOAMManager = param0->fontOAMManager;
    v0.window = &v1;
    v0.spriteList = SpriteManager_GetSpriteList(v6);
    v0.paletteProxy = SpriteManager_FindPlttResourceProxy(v6, param6);
    v0.parentSprite = NULL;
    v0.charOffset = v2.offset;
    v0.x = param7;
    v0.y = param8;
    v0.resourcePriority = 0;
    v0.spritePriority = 51;
    v0.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v0.heapID = HEAP_ID_118;

    v4 = FontOAM_New(&v0);

    FontOAM_SetExplicitPaletteOffsetAutoAdjust(v4, param5);
    FontOAM_SetXY(v4, param7, param8);
    Window_Remove(&v1);

    param1->oam = v4;
    param1->allocation = v2;
    param1->width = v7;
}

static void FootprintStamp_FreeTextOAM(FootprintStampText *param0)
{
    FontOAM_Free(param0->oam);
    CharTransfer_ClearRange(&param0->allocation);
}

static void FootprintStamp_MeasureText(const String *param0, int param1, int *param2, int *param3)
{
    int v0 = Font_CalcStringWidth(param1, param0, 0);
    int v1 = v0 / 8;

    if (FX_ModS32(v0, 8) != 0) {
        v1++;
    }

    *param2 = v0;
    *param3 = v1;
}

static void FootprintStamp_UpdatePartySpritePositions(FootprintStampApp *param0)
{
    int v0, v1;

    if (param0->scrollTarget == param0->scrollOffset) {
        param0->scrollTarget += ((32 << 8) / 60);

        if (param0->scrollTarget > (32 << 8)) {
            param0->scrollTarget = (32 << 8);
        }

        param0->scrollOffset = param0->scrollTarget;
    } else {
        param0->scrollOffset -= param0->scrollStep;

        if (param0->scrollOffset < param0->scrollTarget) {
            param0->scrollOffset = param0->scrollTarget;
        }
    }

    v0 = 32 - (param0->scrollOffset >> 8);

    for (v1 = 0; v1 < 6; v1++) {
        ManagedSprite_SetPositionXYWithSubscreenOffset(param0->partySprites[v1], 16 + 32 * v1, 176 + v0, (192 + 80) << FX32_SHIFT);
    }
}

static BOOL FootprintStamp_ScrollPartySprites(FootprintStampApp *param0, int param1)
{
    if (param0->scrollTarget < param1) {
        return 0;
    }

    if (param0->scrollOffset < param0->scrollTarget) {
        GF_ASSERT(FALSE);
        param0->scrollOffset = param0->scrollTarget;
    }

    param0->scrollTarget -= param1;
    param0->scrollStep = (param0->scrollOffset - param0->scrollTarget) / 4;

    return 1;
}

static void FootprintStamp_Noop(FootprintStampApp *param0)
{
    return;
}
