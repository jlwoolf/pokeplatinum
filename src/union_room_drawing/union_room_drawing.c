#include "union_room_drawing/union_room_drawing.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/struct_02095EAC_decl.h"
#include "struct_defs/struct_union_room_drawing_app_args.h"
#include "struct_defs/struct_02095EAC_t.h"
#include "struct_defs/struct_02095FE4.h"

#include "union_room_drawing/struct_union_room_drawing_prev_point.h"
#include "union_room_drawing/struct_union_room_drawing_status.h"

#include "bg_window.h"
#include "char_transfer.h"
#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "font.h"
#include "game_options.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "journal.h"
#include "math_util.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "pltt_transfer.h"
#include "render_oam.h"
#include "render_window.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "system.h"
#include "text.h"
#include "touch_pad.h"
#include "touch_screen.h"
#include "trainer_info.h"
#include "comm_server_client.h"
#include "comm_tool.h"
#include "union_room.h"
#include "union_room_trainers.h"
#include "union_room_drawing_comm.h"
#include "vram_transfer.h"
#include "wireless_manager.h"
#include "yes_no_touch_menu.h"

// One entry of the drawing app's state machine. `handler` is invoked while the
// app is in this state; `runInState2` also allows it to run in app state 2.
typedef struct {
    int (*handler)(UnionRoomDrawing *, int);
    int runInState2;
} UnionRoomDrawingStateHandler;

static void UnionRoomDrawing_VBlankCallback(void *param0);
static void UnionRoomDrawing_SetGXBanks(void);
static void UnionRoomDrawing_InitBgLayers(BgConfig *param0);
static void UnionRoomDrawing_InitState(UnionRoomDrawing *param0);
static void UnionRoomDrawing_FreeState(UnionRoomDrawing *param0);
static void UnionRoomDrawing_FreeBgLayers(BgConfig *param0);
static void UnionRoomDrawing_LoadGraphics(UnionRoomDrawing *param0, NARC *param1);
static void UnionRoomDrawing_InitTransfers(void);
static void UnionRoomDrawing_InitSprites(UnionRoomDrawing *param0, NARC *param1);
static void UnionRoomDrawing_CreateSprites(UnionRoomDrawing *param0);
static void UnionRoomDrawing_CreateWindows(UnionRoomDrawing *param0, ApplicationManager *appMan);
static void UnionRoomDrawing_RemoveWindows(UnionRoomDrawing *param0);
static void UnionRoomDrawing_SetSpritePosition(Sprite *param0, int param1, int param2);
static void UnionRoomDrawing_HandleTouchInput(UnionRoomDrawing *param0);
static int UnionRoomDrawing_StateDrawing(UnionRoomDrawing *param0, int param1);
static void UnionRoomDrawing_RedrawDrawingWindow(UnionRoomDrawing *param0);
static int UnionRoomDrawing_StatePromptStopDrawing(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateHandleStopDrawing(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateClientAck(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateWaitAllAcked(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateRejoinDrawing(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateShowSessionEnded(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateWaitSessionEnded(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateFadeOut(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StatePromptLeaderLeave(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateHandleLeaderLeave(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateShowLeaderLeft(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateWaitLeaderLeft(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateWaitDisbandSync(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateShowNoMembers(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateWaitNoMembers(UnionRoomDrawing *param0, int param1);
static void UnionRoomDrawing_DrawLine(Window *param0, const u8 *param1, int param2, int param3, int *param4, int *param5, int param6, int param7);
static void UnionRoomDrawing_CopyPrevPoint(UnionRoomDrawingStatus *param0, UnionRoomDrawingPrevPoint *param1);
static void UnionRoomDrawing_DrawStrokes(Window *param0, UnionRoomDrawingStatus *param1, UnionRoomDrawingPrevPoint *param2, int param3);
static void UnionRoomDrawing_UpdateRemoteCursors(UnionRoomDrawing *param0);
static void UnionRoomDrawing_AnimateCursorColor(u16 *param0);
static void UnionRoomDrawing_DrawPlayerNames(Window *param0, int param1, u32 param2, UnionRoomDrawing *param3);
static void UnionRoomDrawing_SendDrawingStatus(UnionRoomDrawing *param0);
static int UnionRoomDrawing_UpdateTrainerInfo(UnionRoomDrawing *param0);
static void UnionRoomDrawing_ShowMessage(UnionRoomDrawing *param0, int param1, int param2);
static int UnionRoomDrawing_IsMessageDone(int param0);
static void UnionRoomDrawing_EraseMessageBox(UnionRoomDrawing *param0);
static int UnionRoomDrawing_CountConnectedTrainers(void);
static int UnionRoomDrawing_StateShowPlayerLeft(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StatePlayerLeftDone(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateWaitPlayerLeft(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_CountConnected(void);
static int UnionRoomDrawing_StateRedraw(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StatePlayerEntered(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_StateResumeDrawing(UnionRoomDrawing *param0, int param1);
static void UnionRoomDrawing_SetPenColorSprite(Sprite **param0, int param1);
static void UnionRoomDrawing_SetEraserSprite(Sprite **param0, BOOL param1);
static void UnionRoomDrawing_BlitBitmapRectClipped(Window *param0, void *param1, int param2, int param3, int param4, int param5, int param6, int param7, int param8, int param9);
static void UnionRoomDrawing_SetMaxConnections(UnionRoomDrawing *param0, int param1);
static int UnionRoomDrawing_UpdateConnectionState(UnionRoomDrawing *param0);
static int UnionRoomDrawing_StateNoOp(UnionRoomDrawing *param0, int param1);
static void UnionRoomDrawing_SetNextState(UnionRoomDrawing *param0, int param1);
static void UnionRoomDrawing_ApplyNextState(UnionRoomDrawing *param0, int param1);
static BOOL UnionRoomDrawing_InitYesNoMenu(UnionRoomDrawing *param0, YesNoTouchMenuParams *param1);
static void UnionRoomDrawing_ResetYesNoMenu(UnionRoomDrawing *param0);
static int UnionRoomDrawing_IsCancelPressed(UnionRoomDrawing *param0);
static void UnionRoomDrawing_UpdateLocalStatus(UnionRoomDrawingStatus *param0, TouchPadDataBuffer *param1, int param2, int param3);

static UnionRoomDrawingStateHandler sStateHandlers[] = {
    { NULL, 0x1 },
    { UnionRoomDrawing_StatePlayerEntered, 0x0 },
    { UnionRoomDrawing_StateRedraw, 0x0 },
    { UnionRoomDrawing_StateResumeDrawing, 0x0 },
    { UnionRoomDrawing_StateDrawing, 0x0 },
    { UnionRoomDrawing_StatePromptStopDrawing, 0x1 },
    { UnionRoomDrawing_StateHandleStopDrawing, 0x1 },
    { UnionRoomDrawing_StateClientAck, 0x1 },
    { UnionRoomDrawing_StateWaitAllAcked, 0x1 },
    { UnionRoomDrawing_StateRejoinDrawing, 0x1 },
    { UnionRoomDrawing_StateShowSessionEnded, 0x1 },
    { UnionRoomDrawing_StateWaitSessionEnded, 0x1 },
    { UnionRoomDrawing_StateFadeOut, 0x1 },
    { UnionRoomDrawing_StatePromptLeaderLeave, 0x1 },
    { UnionRoomDrawing_StateHandleLeaderLeave, 0x1 },
    { UnionRoomDrawing_StateShowLeaderLeft, 0x1 },
    { UnionRoomDrawing_StateWaitLeaderLeft, 0x1 },
    { UnionRoomDrawing_StateWaitDisbandSync, 0x1 },
    { UnionRoomDrawing_StateNoOp, 0x1 },
    { UnionRoomDrawing_StateShowNoMembers, 0x1 },
    { UnionRoomDrawing_StateWaitNoMembers, 0x1 },
    { UnionRoomDrawing_StateShowPlayerLeft, 0x1 },
    { UnionRoomDrawing_StateWaitPlayerLeft, 0x1 },
    { UnionRoomDrawing_StatePlayerLeftDone, 0x1 }
};

int UnionRoomDrawing_Init(ApplicationManager *appMan, int *param1)
{
    UnionRoomDrawing *v0;
    NARC *v1;

    switch (*param1) {
    case 0:
        SetVBlankCallback(NULL, NULL);
        DisableHBlank();
        GXLayers_DisableEngineALayers();
        GXLayers_DisableEngineBLayers();

        GX_SetVisiblePlane(0);
        GXS_SetVisiblePlane(0);

        Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_DRAWING, HEAP_SIZE_DRAWING);

        v0 = ApplicationManager_NewData(appMan, sizeof(UnionRoomDrawing), HEAP_ID_DRAWING);
        memset(v0, 0, sizeof(UnionRoomDrawing));
        v0->bgConfig = BgConfig_New(HEAP_ID_DRAWING);

        v0->strTemplate = StringTemplate_Default(HEAP_ID_DRAWING);
        v0->msgLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_DRAWING, HEAP_ID_DRAWING);

        SetAutorepeat(4, 8);

        UnionRoomDrawing_SetGXBanks();
        UnionRoomDrawing_InitBgLayers(v0->bgConfig);

        SetScreenColorBrightness(DS_SCREEN_MAIN, COLOR_BLACK);
        SetScreenColorBrightness(DS_SCREEN_SUB, COLOR_BLACK);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_IN, FADE_TYPE_CIRCLE_IN, COLOR_BLACK, 16, 1, HEAP_ID_DRAWING);

        {
            UnionRoomDrawingAppArgs *v2 = (UnionRoomDrawingAppArgs *)ApplicationManager_Args(appMan);
            v0->appArgs = v2;
        }

        v1 = NARC_ctor(NARC_INDEX_GRAPHIC__OEKAKI, HEAP_ID_DRAWING);

        UnionRoomDrawing_LoadGraphics(v0, v1);

        EnableTouchPad();
        InitializeTouchPad(2);
        SetVBlankCallback(UnionRoomDrawing_VBlankCallback, v0->bgConfig);

        UnionRoomDrawing_InitState(v0);
        UnionRoomDrawing_InitTransfers();
        UnionRoomDrawing_InitSprites(v0, v1);
        UnionRoomDrawing_CreateSprites(v0);
        UnionRoomDrawing_CreateWindows(v0, appMan);

        Sound_SetSceneAndPlayBGM(SOUND_SCENE_SUB_52, SEQ_NONE, 0);

        GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);

        UnionRoomDrawing_RegisterCommHandlers(v0);
        CommManager_SetErrorHandling(0, 1);

        if (CommSys_CurNetId() == 0) {
            CommManager_SetMaxNumConnections(3);
        }

        NetworkIcon_Init();

        if (CommSys_CurNetId() == 0) {
            UnionRoom_BroadcastActivity(1);
            CommServerClient_SetErrorTimeout(1);
        }

        NARC_dtor(v1);
        (*param1)++;
        break;
    case 1:
        v0 = ApplicationManager_Data(appMan);
        (*param1) = 0;
        return 1;
        break;
    }

    return 0;
}

int UnionRoomDrawing_Main(ApplicationManager *appMan, int *param1)
{
    UnionRoomDrawing *v0 = ApplicationManager_Data(appMan);

    if ((CommSys_CurNetId() == 0) && (v0->ackedNetIds != 0)) {
        v0->ackedNetIds &= WirelessManager_GetConnectedBitmap();
    }

    v0->appState = *param1;

    UnionRoomDrawing_ApplyNextState(v0, *param1);

    switch (*param1) {
    case 0:
        if (IsScreenFadeDone()) {
            if (CommSys_CurNetId() != 0) {
                if (UnionRoomDrawing_CountConnected() >= 2) {
                    CommSys_SendData(128, NULL, 0);
                    *param1 = 1;
                }
                break;
            } else {
                *param1 = 1;
            }
        }
        break;
    case 1:
        if (sStateHandlers[v0->state].handler != NULL) {
            *param1 = sStateHandlers[v0->state].handler(v0, *param1);
        }

        UnionRoomDrawing_DrawPlayerNames(v0->playerWindows, 0, TEXT_COLOR(14, 13, 15), v0);

        if (CommSys_CurNetId() == 0) {
            int v1 = UnionRoomDrawing_UpdateConnectionState(v0);

            if (*param1 == 1) {
                *param1 = v1;
            }
        }

        UnionRoomDrawing_AnimateCursorColor(&v0->cursorColorAngle);
        break;
    case 2:
        if ((sStateHandlers[v0->state].handler != NULL) && sStateHandlers[v0->state].runInState2) {
            *param1 = sStateHandlers[v0->state].handler(v0, *param1);
        }
        break;
    case 3:
        if (IsScreenFadeDone()) {
            return 1;
        }
        break;
    }

    SpriteList_Update(v0->spriteList);

    return 0;
}

int UnionRoomDrawing_Exit(ApplicationManager *appMan, int *param1)
{
    UnionRoomDrawing *v0 = ApplicationManager_Data(appMan);
    UnionRoomDrawingAppArgs *v1 = (UnionRoomDrawingAppArgs *)ApplicationManager_Args(appMan);
    int v2;
    void *journalEntryOnlineEvent;

    switch (*param1) {
    case 0:
        journalEntryOnlineEvent = JournalEntry_CreateEventDrewPictures(39);

        JournalEntry_SaveData(v1->journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
        SetVBlankCallback(NULL, NULL);
        SpriteTransfer_ResetCharTransfer(v0->spriteResources[0][0]);
        SpriteTransfer_ResetCharTransfer(v0->spriteResources[1][0]);
        SpriteTransfer_ResetPlttTransfer(v0->spriteResources[0][1]);
        SpriteTransfer_ResetPlttTransfer(v0->spriteResources[1][1]);

        for (v2 = 0; v2 < 4; v2++) {
            SpriteResourceCollection_Delete(v0->spriteResourceCollections[v2]);
        }

        SpriteList_Delete(v0->spriteList);
        RenderOam_Free();
        CharTransfer_Free();
        PlttTransfer_Free();

        UnionRoomDrawing_RemoveWindows(v0);
        UnionRoomDrawing_FreeBgLayers(v0->bgConfig);

        DisableTouchPad();
        MessageLoader_Free(v0->msgLoader);
        StringTemplate_Free(v0->strTemplate);
        (*param1)++;
        break;
    case 1:
        CommManager_SetMaxNumConnections(1);
        CommManager_UnionRestartSearch();
        UnionRoomTrainers_Reset(v1->trainers);

        GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

        UnionRoom_BroadcastActivity(0);
        CommServerClient_SetErrorTimeout(0);
        (*param1)++;
        break;
    case 2:
        if (v0->readyToDraw) {
            if (WirelessManager_GetConnectedBitmap() == 1) {
                (*param1)++;
            }
        } else {
            (*param1)++;
        }
        break;
    case 3:
        CommManager_SetMaxNumConnections(2);

        UnionRoomDrawing_FreeState(v0);

        Heap_Free(v0->appArgs);
        ApplicationManager_FreeData(appMan);
        SetVBlankCallback(NULL, NULL);
        Heap_Destroy(HEAP_ID_DRAWING);
        CommManager_SetMaxNumConnections(2);

        return 1;
    }

    return 0;
}

static void UnionRoomDrawing_VBlankCallback(void *param0)
{
    VramTransfer_Process();
    RenderOam_Transfer();
    Bg_RunScheduledUpdates((BgConfig *)param0);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void UnionRoomDrawing_SetGXBanks(void)
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

static void UnionRoomDrawing_InitBgLayers(BgConfig *param0)
{
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
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_0, &v1, 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_0);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase = GX_BG_CHARBASE_0x00000,
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
            .screenBase = GX_BG_SCRBASE_0xd800,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_2, &v3, 0);
    }

    {
        BgTemplate v4 = {
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
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_0, &v4, 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_0);
    }

    {
        BgTemplate v5 = {
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
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_1, &v5, 0);
    }

    Bg_ClearTilesRange(BG_LAYER_MAIN_0, 32, 0, HEAP_ID_DRAWING);
    Bg_ClearTilesRange(4, 32, 0, HEAP_ID_DRAWING);
    Bg_ClearTilesRange(BG_LAYER_MAIN_1, 32, 0, HEAP_ID_DRAWING);
    Bg_ClearTilesRange(5, 32, 0, HEAP_ID_DRAWING);
}

static void UnionRoomDrawing_InitState(UnionRoomDrawing *param0)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        param0->playerNameStrings[v0] = String_Init(7 + 1, HEAP_ID_DRAWING);
        param0->drawingStatus[v0].pointCount = 0;
        param0->prevPoints[v0].hasPrev = 0;
        param0->trainerInfo[v0][0] = NULL;
        param0->trainerInfo[v0][1] = NULL;
    }

    param0->headerString = String_Init(10, HEAP_ID_DRAWING);
    param0->messageString = String_Init(40 * 2, HEAP_ID_DRAWING);
    param0->penColor = 0;
    param0->penSize = 1;
    param0->drawingState = 1;
    param0->clientReadySent = 0;
    param0->connectedCount = 2;
    param0->connectedBitmap = WirelessManager_GetConnectedBitmap();
    param0->clientReadySent = 0;
    param0->readyToDraw = 0;
    param0->state = 0;
    param0->disconnectHandled = 0;
    param0->disconnectedBitmap = 0;

    if (CommSys_CurNetId() == 0) {
        UnionRoomDrawing_SetNextState(param0, 4);
    } else {
        UnionRoomDrawing_SetNextState(param0, 4);
    }

    MessageLoader_GetString(param0->msgLoader, 7, param0->headerString);

    param0->canvasBuffer = Heap_Alloc(HEAP_ID_DRAWING, 30 * 16 * 32);
    param0->yesNoMenu = YesNoTouchMenu_New(HEAP_ID_DRAWING);
    param0->connectedCountSnapshot = 0;
}

static void UnionRoomDrawing_FreeState(UnionRoomDrawing *param0)
{
    int v0;

    Heap_Free(param0->canvasBuffer);
    YesNoTouchMenu_Free(param0->yesNoMenu);

    for (v0 = 0; v0 < 5; v0++) {
        String_Free(param0->playerNameStrings[v0]);
    }

    String_Free(param0->messageString);
    String_Free(param0->headerString);
}

static void UnionRoomDrawing_FreeBgLayers(BgConfig *param0)
{
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_0);
    Heap_Free(param0);
}

static void UnionRoomDrawing_LoadGraphics(UnionRoomDrawing *param0, NARC *param1)
{
    BgConfig *v0 = param0->bgConfig;

    Graphics_LoadPaletteFromOpenNARC(param1, 0, 0, 0, 16 * 2 * 2, HEAP_ID_DRAWING);
    Graphics_LoadPaletteFromOpenNARC(param1, 1, 4, 0, 16 * 2 * 2, HEAP_ID_DRAWING);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(13), HEAP_ID_DRAWING);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_SUB_BG, PLTT_OFFSET(13), HEAP_ID_DRAWING);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 2, v0, 2, 0, 32 * 8 * 0x20, 1, HEAP_ID_DRAWING);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 4, v0, 2, 0, 32 * 24 * 2, 1, HEAP_ID_DRAWING);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 3, v0, 5, 0, 32 * 8 * 0x20, 1, HEAP_ID_DRAWING);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 5, v0, 5, 0, 32 * 24 * 2, 1, HEAP_ID_DRAWING);
    LoadMessageBoxGraphics(v0, BG_LAYER_MAIN_0, 1, 10, Options_Frame(param0->appArgs->options), HEAP_ID_DRAWING);
    LoadStandardWindowGraphics(v0, BG_LAYER_MAIN_0, 1 + (18 + 12), 11, 0, HEAP_ID_DRAWING);
}

static void UnionRoomDrawing_InitTransfers(void)
{
    {
        CharTransferTemplate v0 = {
            20, 2048, 2048, HEAP_ID_DRAWING
        };

        CharTransfer_Init(&v0);
    }

    PlttTransfer_Init(20, HEAP_ID_DRAWING);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
}

static void UnionRoomDrawing_InitSprites(UnionRoomDrawing *param0, NARC *param1)
{
    int v0;

    NNS_G2dInitOamManagerModule();

    RenderOam_Init(0, 126, 0, 32, 0, 126, 0, 32, 39);
    param0->spriteList = SpriteList_InitRendering(50 + 3, &param0->g2dRenderer, HEAP_ID_DRAWING);
    SetSubScreenViewRect(&param0->g2dRenderer, 0, 256 * FX32_ONE);

    for (v0 = 0; v0 < 4; v0++) {
        param0->spriteResourceCollections[v0] = SpriteResourceCollection_New(2, v0, HEAP_ID_DRAWING);
    }

    param0->spriteResources[0][0] = SpriteResourceCollection_AddTilesFrom(param0->spriteResourceCollections[0], param1, 6, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAP_ID_DRAWING);
    param0->spriteResources[0][1] = SpriteResourceCollection_AddPaletteFrom(param0->spriteResourceCollections[1], param1, 0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 7, HEAP_ID_DRAWING);
    param0->spriteResources[0][2] = SpriteResourceCollection_AddFrom(param0->spriteResourceCollections[2], param1, 7, 1, 0, 2, HEAP_ID_DRAWING);
    param0->spriteResources[0][3] = SpriteResourceCollection_AddFrom(param0->spriteResourceCollections[3], param1, 8, 1, 0, 3, HEAP_ID_DRAWING);
    param0->spriteResources[1][0] = SpriteResourceCollection_AddTilesFrom(param0->spriteResourceCollections[0], param1, 6, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAP_ID_DRAWING);
    param0->spriteResources[1][1] = SpriteResourceCollection_AddPaletteFrom(param0->spriteResourceCollections[1], param1, 0, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 3, HEAP_ID_DRAWING);
    param0->spriteResources[1][2] = SpriteResourceCollection_AddFrom(param0->spriteResourceCollections[2], param1, 7, 1, 1, 2, HEAP_ID_DRAWING);
    param0->spriteResources[1][3] = SpriteResourceCollection_AddFrom(param0->spriteResourceCollections[3], param1, 8, 1, 1, 3, HEAP_ID_DRAWING);

    SpriteTransfer_RequestChar(param0->spriteResources[0][0]);
    SpriteTransfer_RequestChar(param0->spriteResources[1][0]);

    SpriteTransfer_RequestPlttWholeRange(param0->spriteResources[0][1]);
    SpriteTransfer_RequestPlttWholeRange(param0->spriteResources[1][1]);
}

static const u16 sPenColorSpriteData[][3] = {
    { 0xD, 0xAB, 0x5 },
    { 0x25, 0xAB, 0x7 },
    { 0x3D, 0xAB, 0x9 },
    { 0x55, 0xAB, 0xB },
    { 0x6D, 0xAB, 0xD },
    { 0x85, 0xAB, 0xF },
    { 0x9D, 0xAB, 0x11 },
    { 0xB5, 0xAB, 0x13 },
    { 0xE1, 0xAB, 0x15 },
    { 0x14, 0x9, 0x1D },
    { 0x24, 0x9, 0x20 },
    { 0x34, 0x9, 0x21 }
};

static void UnionRoomDrawing_CreateSprites(UnionRoomDrawing *param0)
{
    int v0;

    SpriteResourcesHeader_Init(&param0->spriteHeader0, 0, 0, 0, 0, 0xffffffff, 0xffffffff, 0, 0, param0->spriteResourceCollections[0], param0->spriteResourceCollections[1], param0->spriteResourceCollections[2], param0->spriteResourceCollections[3], NULL, NULL);
    SpriteResourcesHeader_Init(&param0->spriteHeader1, 1, 1, 1, 1, 0xffffffff, 0xffffffff, 0, 0, param0->spriteResourceCollections[0], param0->spriteResourceCollections[1], param0->spriteResourceCollections[2], param0->spriteResourceCollections[3], NULL, NULL);

    {
        AffineSpriteListTemplate v1;

        v1.list = param0->spriteList;
        v1.resourceData = &param0->spriteHeader0;
        v1.position.z = 0;
        v1.affineScale.x = FX32_ONE;
        v1.affineScale.y = FX32_ONE;
        v1.affineScale.z = FX32_ONE;
        v1.affineZRotation = 0;
        v1.priority = 1;
        v1.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
        v1.heapID = HEAP_ID_DRAWING;

        for (v0 = 0; v0 < 5; v0++) {
            v1.resourceData = &param0->spriteHeader1;
            v1.position.x = FX32_ONE * (24 + v0 * 40);
            v1.position.y = FX32_ONE * (32 + 32);
            v1.vramType = NNS_G2D_VRAM_TYPE_2DSUB;

            param0->playerCursors[v0] = SpriteList_AddAffine(&v1);

            Sprite_SetAnimateFlag(param0->playerCursors[v0], 1);
            Sprite_SetAnim(param0->playerCursors[v0], v0);
            Sprite_SetDrawFlag(param0->playerCursors[v0], FALSE);
        }

        for (v0 = 0; v0 < 9 + 3; v0++) {
            v1.resourceData = &param0->spriteHeader1;
            v1.position.x = FX32_ONE * (sPenColorSpriteData[v0][0]);
            v1.position.y = FX32_ONE * (sPenColorSpriteData[v0][1]);

            param0->toolSprites[v0] = SpriteList_AddAffine(&v1);

            Sprite_SetAnimateFlag(param0->toolSprites[v0], 1);
            Sprite_SetAnim(param0->toolSprites[v0], sPenColorSpriteData[v0][2]);

            if (v0 >= 8) {
                Sprite_SetExplicitPriority(param0->toolSprites[v0], 2);
            }
        }

        Sprite_SetAnim(param0->toolSprites[0], 6);

        for (v0 = 0; v0 < 5; v0++) {
            v1.position.x = FX32_ONE * 24;
            v1.position.y = FX32_ONE * (32 + 32 * v0) + (256 * FX32_ONE);

            param0->penColorSprites[v0] = SpriteList_AddAffine(&v1);

            Sprite_SetAnimateFlag(param0->penColorSprites[v0], 1);
            Sprite_SetAnim(param0->penColorSprites[v0], v0);
            Sprite_SetPriority(param0->penColorSprites[v0], 1);
            Sprite_SetDrawFlag(param0->penColorSprites[v0], FALSE);
        }
    }
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void UnionRoomDrawing_CreateWindows(UnionRoomDrawing *param0, ApplicationManager *appMan)
{
    Window_Add(param0->bgConfig, &param0->messageWindow, 0, 2, 1, 27, 4, 13, 1 + (18 + 12) + 9);
    Window_FillTilemap(&param0->messageWindow, 0xf0f);
    Window_Add(param0->bgConfig, &param0->drawingWindow, 1, 1, 2, 30, 15, 0, 1);
    Window_FillTilemap(&param0->drawingWindow, 0x202);
    Window_Add(param0->bgConfig, &param0->headerWindow, 1, 25, 21, 7, 2, 13, 1 + 30 * 15);
    Window_FillTilemap(&param0->headerWindow, 0x0);

    {
        u32 v0 = Font_CalcCenterAlignment(FONT_MESSAGE, param0->headerString, 0, (7 - 1) * 8) + 2;
        Text_AddPrinterWithParamsAndColor(&param0->headerWindow, FONT_MESSAGE, param0->headerString, v0, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(7, 1, 0), NULL);
    }

    {
        int v1;

        for (v1 = 0; v1 < 5; v1++) {
            Window_Add(param0->bgConfig, &param0->playerWindows[v1], 4, 24 / 8 + 2, 32 / 8 + v1 * 4 - 1, 10, 2, 13, 1 + v1 * (10 * 2));
            Window_FillTilemap(&param0->playerWindows[v1], 0);
        }

        UnionRoomDrawing_DrawPlayerNames(param0->playerWindows, 0, TEXT_COLOR(14, 13, 15), param0);
    }
}

static void UnionRoomDrawing_RemoveWindows(UnionRoomDrawing *param0)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        Window_Remove(&param0->playerWindows[v0]);
    }

    Window_Remove(&param0->headerWindow);
    Window_Remove(&param0->drawingWindow);
    Window_Remove(&param0->messageWindow);
}

static void UnionRoomDrawing_SetSpritePosition(Sprite *param0, int param1, int param2)
{
    VecFx32 v0;

    v0.x = FX32_CONST(param1);
    v0.y = FX32_CONST(param2 - 8);
    v0.z = 0;

    Sprite_SetPosition(param0, &v0);
}

static const TouchScreenRect sDrawingTouchRects[] = {
    { 0x96, 0xBD, 0x0, 0x17 },
    { 0x96, 0xBD, 0x18, 0x2F },
    { 0x96, 0xBD, 0x30, 0x47 },
    { 0x96, 0xBD, 0x48, 0x5F },
    { 0x96, 0xBD, 0x60, 0x77 },
    { 0x96, 0xBD, 0x78, 0x8F },
    { 0x96, 0xBD, 0x90, 0xA7 },
    { 0x96, 0xBD, 0xA8, 0xBF },
    { 0x96, 0xBD, 0xC0, 0xFF },
    { 0x1, 0xD, 0xE, 0x1A },
    { 0x1, 0xD, 0x1E, 0x2A },
    { 0x1, 0xD, 0x2E, 0x3A },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const TouchScreenRect sCancelButtonTouchRect[] = {
    { 0x30, 0x70, 0xC8, 0xF8 },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const TouchScreenRect sCanvasTouchRect[] = {
    { 0x10, 0x88, 0x8, 0xF8 },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static void UnionRoomDrawing_HandleTouchInput(UnionRoomDrawing *param0)
{
    int v0 = -1, v1;
    int v2 = 0;

    v0 = TouchScreen_CheckRectanglePressed(sDrawingTouchRects);

    if (v0 != 0xffffffff) {
        switch (v0) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            if (param0->penColor != v0) {
                param0->penColor = v0;
                UnionRoomDrawing_SetPenColorSprite(param0->toolSprites, v0);
                Sound_PlayEffect(SE_CONFIRM_sseq_3);
            }
            break;
        case 8:
            if (param0->state == 4) {
                if (CommSys_CurNetId() == 0) {
                    if (param0->connectedBitmap != WirelessManager_GetConnectedBitmap()) {
                        Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
                        break;
                    }

                    CommManager_SetMaxNumConnections(CommSys_ConnectedCount());
                    param0->drawingState = 2;
                    UnionRoomDrawing_ShowMessage(param0, 1, TEXT_SPEED_FAST);
                    UnionRoomDrawing_SetNextState(param0, 5);
                    UnionRoomDrawing_SetEraserSprite(param0->toolSprites, 1);
                    v2 = 1;
                    Sound_PlayEffect(SE_CONFIRM_sseq_3);
                } else {
                    if (param0->drawingStatus[0].state == 2) {
                        Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
                    } else {
                        UnionRoomDrawing_ShowMessage(param0, 1, TEXT_SPEED_FAST);
                        UnionRoomDrawing_SetNextState(param0, 5);
                        UnionRoomDrawing_SetEraserSprite(param0->toolSprites, 1);
                        v2 = 1;
                        Sound_PlayEffect(SE_CONFIRM_sseq_3);
                    }
                }
            }
            break;
        case 9:
        case 10:
        case 11: {
            int v3;

            for (v3 = 0; v3 < 3; v3++) {
                if ((v0 - 9) == v3) {
                    Sprite_SetAnim(param0->toolSprites[9 + v3], 29 + 2 * v3 + 1);
                } else {
                    Sprite_SetAnim(param0->toolSprites[9 + v3], 29 + 2 * v3);
                }
            }

            if (param0->penSize != (0 + v0 - 9)) {
                param0->penSize = 0 + v0 - 9;
                Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);
            }
        } break;
        }
    }

    v1 = TouchScreen_CheckRectangleHeld(sCanvasTouchRect);
    Sprite_SetDrawFlag(param0->playerCursors[CommSys_CurNetId()], FALSE);

    if (v1 != 0xffffffff) {
        UnionRoomDrawing_SetSpritePosition(param0->playerCursors[CommSys_CurNetId()], gSystem.touchX, gSystem.touchY);
        Sprite_SetDrawFlag(param0->playerCursors[CommSys_CurNetId()], TRUE);
    }

    {
        TouchPadDataBuffer v4;
        int v5;

        if (WriteAutoSamplingDataToBuffer(&v4, TOUCH_PAD_EXTERNAL_BUFFER_WRITE_METHOD_ALL_DATA_WITHOUT_WRAPPING, 64) == 1) {
            UnionRoomDrawing_UpdateLocalStatus(&param0->localDrawingStatus, &v4, param0->penColor, param0->penSize);

            if (v2 == 1) {
                param0->localDrawingStatus.pointCount = 0;
            }
        }
    }
}

static void UnionRoomDrawing_SetPenColorSprite(Sprite **param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        if (v0 == param1) {
            Sprite_SetAnim(param0[v0], sPenColorSpriteData[v0][2] + 1);
        } else {
            Sprite_SetAnim(param0[v0], sPenColorSpriteData[v0][2]);
        }
    }
}

static void UnionRoomDrawing_SetEraserSprite(Sprite **param0, BOOL param1)
{
    if (param1 == 1) {
        Sprite_SetAnim(param0[8], sPenColorSpriteData[8][2] + 1);
    } else {
        Sprite_SetAnim(param0[8], sPenColorSpriteData[8][2]);
    }
}

static int UnionRoomDrawing_StateDrawing(UnionRoomDrawing *param0, int param1)
{
    UnionRoomDrawing_HandleTouchInput(param0);

    if (CommSys_CurNetId() == 0) {
        if (UnionRoomDrawing_CountConnectedTrainers() != 1) {
            UnionRoomDrawing_SendDrawingStatus(param0);
        }
    } else {
        UnionRoomDrawing_SendDrawingStatus(param0);
    }

    UnionRoomDrawing_UpdateRemoteCursors(param0);
    UnionRoomDrawing_DrawStrokes(&param0->drawingWindow, param0->drawingStatus, param0->prevPoints, 1);

    return param1;
}

static void UnionRoomDrawing_RedrawDrawingWindow(UnionRoomDrawing *param0)
{
    UnionRoomDrawing_UpdateRemoteCursors(param0);
    UnionRoomDrawing_DrawStrokes(&param0->drawingWindow, param0->drawingStatus, param0->prevPoints, 0);
}

static int UnionRoomDrawing_StatePlayerEntered(UnionRoomDrawing *param0, int param1)
{
    if (CommSys_CurNetId() == param0->drawingPlayerNetId) {
        UnionRoomDrawing_ShowMessage(param0, 13, TEXT_SPEED_INSTANT);
    } else {
        UnionRoomDrawing_ShowMessage(param0, 0, TEXT_SPEED_INSTANT);
    }

    UnionRoomDrawing_SetNextState(param0, 2);
    Sound_PlayEffect(SEQ_SE_DP_BUTTON9_sseq);

    G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ, -6);

    UnionRoomDrawing_RedrawDrawingWindow(param0);

    return param1;
}

static int UnionRoomDrawing_StateRedraw(UnionRoomDrawing *param0, int param1)
{
    UnionRoomDrawing_RedrawDrawingWindow(param0);
    return param1;
}

static int UnionRoomDrawing_StateResumeDrawing(UnionRoomDrawing *param0, int param1)
{
    G2_BlendNone();

    UnionRoomDrawing_SetMaxConnections(param0, 1);
    UnionRoomDrawing_SetNextState(param0, 4);
    UnionRoomDrawing_RedrawDrawingWindow(param0);

    param0->disconnectHandled = 0;

    return param1;
}

static int UnionRoomDrawing_StatePromptStopDrawing(UnionRoomDrawing *param0, int param1)
{
    if (UnionRoomDrawing_IsMessageDone(param0->textPrinterID)) {
        YesNoTouchMenuParams v0;
        BOOL v1;

        v0.bgConfig = param0->bgConfig;
        v0.bgLayer = BG_LAYER_MAIN_0;
        v0.baseTile = (1 + (18 + 12) + 9 + 27 * 4) + 8 * 4;
        v0.palette = 8;
        v0.tilemapLeft = 25;
        v0.tilemapTop = 6;

        v1 = UnionRoomDrawing_InitYesNoMenu(param0, &v0);
        GF_ASSERT(v1);

        UnionRoomDrawing_SetNextState(param0, 6);
    }

    UnionRoomDrawing_RedrawDrawingWindow(param0);
    return param1;
}

static int UnionRoomDrawing_StateHandleStopDrawing(UnionRoomDrawing *param0, int param1)
{
    int v0;

    param0->localDrawingStatus.pointCount = 0;

    if ((param0->drawingStatus[0].state == 2) && (CommSys_CurNetId() != 0)) {
        UnionRoomDrawing_RedrawDrawingWindow(param0);

        if (UnionRoomDrawing_IsCancelPressed(param0)) {
            Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
        }

        return param1;
    }

    if ((CommSys_CurNetId() == 0) && (param0->ackedNetIds != 0)) {
        UnionRoomDrawing_RedrawDrawingWindow(param0);
        return param1;
    }

    if (UnionRoomDrawing_CountConnected() != CommSys_ConnectedCount()) {
        UnionRoomDrawing_RedrawDrawingWindow(param0);
        return param1;
    }

    v0 = YesNoTouchMenu_ProcessInput(param0->yesNoMenu);

    switch (v0) {
    case YES_NO_TOUCH_MENU_YES:
        if (CommSys_CurNetId() == 0) {
            UnionRoomDrawing_SetNextState(param0, 13);
            UnionRoomDrawing_ShowMessage(param0, 4, TEXT_SPEED_FAST);
        } else {
            UnionRoomDrawingConnAck v1;

            MI_CpuClear8(&v1, sizeof(UnionRoomDrawingConnAck));
            v1.type = 0;
            v1.netId = CommSys_CurNetId();

            param0->flag = 1;
            param0->commTimer = 0;

            UnionRoomDrawing_SetNextState(param0, 7);

            CommSys_SendData(126, &v1, sizeof(UnionRoomDrawingConnAck));
            Window_EraseMessageBox(&param0->messageWindow, 1);
        }

        UnionRoomDrawing_ResetYesNoMenu(param0);
        Window_CopyToVRAM(&param0->drawingWindow);
        break;
    case YES_NO_TOUCH_MENU_NO:
        UnionRoomDrawing_SetNextState(param0, 4);
        UnionRoomDrawing_SetEraserSprite(param0->toolSprites, 0);
        Window_EraseMessageBox(&param0->messageWindow, 1);
        UnionRoomDrawing_ResetYesNoMenu(param0);
        Window_CopyToVRAM(&param0->drawingWindow);

        if (CommSys_CurNetId() == 0) {
            CommManager_SetMaxNumConnections(CommSys_ConnectedCount() + 1);
            param0->drawingState = 1;
        }
        break;
    }

    UnionRoomDrawing_RedrawDrawingWindow(param0);

    return param1;
}

static int UnionRoomDrawing_StateClientAck(UnionRoomDrawing *param0, int param1)
{
    param0->localDrawingStatus.pointCount = 0;
    param0->commTimer = 0;

    UnionRoomDrawing_RedrawDrawingWindow(param0);

    return param1;
}

static int UnionRoomDrawing_StateWaitAllAcked(UnionRoomDrawing *param0, int param1)
{
    param0->localDrawingStatus.pointCount = 0;

    if ((param0->ackedCount != CommSys_ConnectedCount()) || (param0->ackedCount != UnionRoomDrawing_CountConnected())) {
        param0->commTimer = 0;

        UnionRoomDrawing_SetNextState(param0, 9);
        UnionRoomDrawing_RedrawDrawingWindow(param0);

        return param1;
    }

    param0->commTimer++;

    if (param0->commTimer > 30) {
        UnionRoomDrawingConnAck v0;

        MI_CpuClear8(&v0, sizeof(UnionRoomDrawingConnAck));

        v0.type = 1;
        v0.netId = CommSys_CurNetId();

        CommSys_SendData(126, &v0, sizeof(UnionRoomDrawingConnAck));
        param0->commTimer = 0;
        UnionRoomDrawing_SetNextState(param0, 10);
    }

    UnionRoomDrawing_RedrawDrawingWindow(param0);

    return param1;
}

static int UnionRoomDrawing_StateRejoinDrawing(UnionRoomDrawing *param0, int param1)
{
    param0->localDrawingStatus.pointCount = 0;
    param0->flag = 0;

    UnionRoomDrawing_SetNextState(param0, 4);
    UnionRoomDrawing_SetEraserSprite(param0->toolSprites, 0);
    UnionRoomDrawing_RedrawDrawingWindow(param0);

    return param1;
}

static int UnionRoomDrawing_StateShowSessionEnded(UnionRoomDrawing *param0, int param1)
{
    u8 v0;

    UnionRoomDrawing_ShowMessage(param0, 6, TEXT_SPEED_FAST);
    UnionRoomDrawing_SetNextState(param0, 11);
    UnionRoomDrawing_RedrawDrawingWindow(param0);

    return param1;
}

static int UnionRoomDrawing_StateWaitSessionEnded(UnionRoomDrawing *param0, int param1)
{
    if (UnionRoomDrawing_IsMessageDone(param0->textPrinterID)) {
        param0->inputTimer = 0;
        UnionRoomDrawing_SetNextState(param0, 12);
    }

    UnionRoomDrawing_RedrawDrawingWindow(param0);

    return param1;
}

static int UnionRoomDrawing_StateFadeOut(UnionRoomDrawing *param0, int param1)
{
    if (++param0->inputTimer > 60) {
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_OUT, FADE_TYPE_CIRCLE_OUT, COLOR_BLACK, 16, 1, HEAP_ID_DRAWING);
        param1 = 3;
    }

    UnionRoomDrawing_RedrawDrawingWindow(param0);
    return param1;
}

static int UnionRoomDrawing_StatePromptLeaderLeave(UnionRoomDrawing *param0, int param1)
{
    if (UnionRoomDrawing_IsMessageDone(param0->textPrinterID)) {
        YesNoTouchMenuParams v0;
        BOOL v1;

        v0.bgConfig = param0->bgConfig;
        v0.bgLayer = BG_LAYER_MAIN_0;
        v0.baseTile = (1 + (18 + 12) + 9 + 27 * 4) + 8 * 4;
        v0.palette = 8;
        v0.tilemapLeft = 25;
        v0.tilemapTop = 6;

        v1 = UnionRoomDrawing_InitYesNoMenu(param0, &v0);
        GF_ASSERT(v1);
        UnionRoomDrawing_SetNextState(param0, 14);
    }

    UnionRoomDrawing_RedrawDrawingWindow(param0);

    return param1;
}

static int UnionRoomDrawing_StateHandleLeaderLeave(UnionRoomDrawing *param0, int param1)
{
    int v0 = YesNoTouchMenu_ProcessInput(param0->yesNoMenu);

    if ((param0->connectedCount != UnionRoomDrawing_CountConnected()) || (param0->ackedNetIds != 0)) {
        UnionRoomDrawing_RedrawDrawingWindow(param0);
        return param1;
    }

    switch (v0) {
    case YES_NO_TOUCH_MENU_YES:
        UnionRoomDrawing_SetNextState(param0, 15);
        CommSys_SendDataServer(127, NULL, 0);
        StringTemplate_SetPlayerName(param0->strTemplate, 0, CommInfo_TrainerInfo(0));
        param1 = 2;
        UnionRoomDrawing_ResetYesNoMenu(param0);
        break;
    case YES_NO_TOUCH_MENU_NO:
        UnionRoomDrawing_SetNextState(param0, 4);
        UnionRoomDrawing_SetEraserSprite(param0->toolSprites, 0);
        Window_EraseMessageBox(&param0->messageWindow, 1);
        UnionRoomDrawing_ResetYesNoMenu(param0);

        if (CommSys_CurNetId() == 0) {
            CommManager_SetMaxNumConnections(CommSys_ConnectedCount() + 1);
            param0->drawingState = 1;
        }
        break;
    }

    UnionRoomDrawing_RedrawDrawingWindow(param0);
    return param1;
}

static int UnionRoomDrawing_StateShowLeaderLeft(UnionRoomDrawing *param0, int param1)
{
    StringTemplate_SetPlayerName(param0->strTemplate, 0, CommInfo_TrainerInfo(0));

    UnionRoomDrawing_ShowMessage(param0, 3, TEXT_SPEED_FAST);
    UnionRoomDrawing_SetNextState(param0, 16);
    UnionRoomDrawing_RedrawDrawingWindow(param0);

    return param1;
}

static int UnionRoomDrawing_StateWaitLeaderLeft(UnionRoomDrawing *param0, int param1)
{
    if (UnionRoomDrawing_IsMessageDone(param0->textPrinterID)) {
        UnionRoomDrawing_SetNextState(param0, 17);
        CommTiming_StartSync(200);
    }

    UnionRoomDrawing_RedrawDrawingWindow(param0);
    return param1;
}

static int UnionRoomDrawing_StateWaitDisbandSync(UnionRoomDrawing *param0, int param1)
{
    if (CommTiming_IsSyncState(200) || (CommSys_ConnectedCount() == 1)) {
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_OUT, FADE_TYPE_CIRCLE_OUT, COLOR_BLACK, 16, 1, HEAP_ID_DRAWING);
        param1 = 3;
    }

    UnionRoomDrawing_RedrawDrawingWindow(param0);
    return param1;
}

static int UnionRoomDrawing_StateNoOp(UnionRoomDrawing *param0, int param1)
{
    return param1;
}

static int UnionRoomDrawing_StateShowNoMembers(UnionRoomDrawing *param0, int param1)
{
    UnionRoomDrawing_ShowMessage(param0, 5, TEXT_SPEED_FAST);
    UnionRoomDrawing_SetNextState(param0, 20);
    UnionRoomDrawing_RedrawDrawingWindow(param0);

    return param1;
}

static int UnionRoomDrawing_StateWaitNoMembers(UnionRoomDrawing *param0, int param1)
{
    if (UnionRoomDrawing_IsMessageDone(param0->textPrinterID)) {
        UnionRoomDrawing_SetNextState(param0, 12);
    }

    UnionRoomDrawing_RedrawDrawingWindow(param0);
    return param1;
}

static int UnionRoomDrawing_StateShowPlayerLeft(UnionRoomDrawing *param0, int param1)
{
    if ((param0->textPrinterID != 0xff) && (UnionRoomDrawing_IsMessageDone(param0->textPrinterID) == 0)) {
        Text_RemovePrinter(param0->textPrinterID);
    }

    UnionRoomDrawing_ShowMessage(param0, 2, TEXT_SPEED_FAST);
    UnionRoomDrawing_SetNextState(param0, 22);
    Sound_PlayEffect(SEQ_SE_DP_BUTTON9_sseq);

    if (CommSys_CurNetId() == 0) {
        UnionRoomDrawing_SetMaxConnections(param0, 0);
    }

    param0->connectedCount = CommSys_ConnectedCount();
    UnionRoomDrawing_RedrawDrawingWindow(param0);

    return param1;
}

static int UnionRoomDrawing_StateWaitPlayerLeft(UnionRoomDrawing *param0, int param1)
{
    if ((param0->connectedCount != 0) && (CommSys_ConnectedCount() != param0->connectedCount)) {
        param0->connectedCount = 0;
    }

    if (UnionRoomDrawing_IsMessageDone(param0->textPrinterID)) {
        UnionRoomDrawing_SetNextState(param0, 23);
        param0->inputTimer = 0;
    }

    UnionRoomDrawing_RedrawDrawingWindow(param0);
    return param1;
}

static int UnionRoomDrawing_StatePlayerLeftDone(UnionRoomDrawing *param0, int param1)
{
    if ((param0->connectedCount != 0) && (CommSys_ConnectedCount() != param0->connectedCount)) {
        param0->connectedCount = 0;
    }

    if ((++param0->inputTimer > 60) && (param0->connectedCount == 0)) {
        UnionRoomDrawing_EraseMessageBox(param0);
        UnionRoomDrawing_SetNextState(param0, 4);

        if (CommSys_CurNetId() == 0) {
            param0->drawingState = 1;
            UnionRoomDrawing_SetMaxConnections(param0, 1);
        }
    }

    UnionRoomDrawing_RedrawDrawingWindow(param0);
    return param1;
}

void UnionRoomDrawing_HandleCommState(UnionRoomDrawing *param0, int param1, u8 param2)
{
    switch (param1) {
    case 1:
        if ((param0->state == 6) || (param0->state == 14)) {
            UnionRoomDrawing_ResetYesNoMenu(param0);
        }

        UnionRoomDrawing_SetEraserSprite(param0->toolSprites, 0);
        StringTemplate_SetPlayerName(param0->strTemplate, 0, CommInfo_TrainerInfo(param2));

        param0->drawingPlayerNetId = param2;
        param0->ackedNetIds = 0;
        break;
    case 3:
        UnionRoomDrawing_EraseMessageBox(param0);
        break;
    case 21:
        if (param0->flag == 1) {
            return;
        }

        StringTemplate_SetPlayerName(param0->strTemplate, 0, CommInfo_TrainerInfo(param2));

        if (param2 == CommSys_CurNetId()) {
            return;
        }

        if (CommSys_CurNetId() == 0) {
            param0->ackedNetIds &= 0xffff ^ param2;
        }

        if ((param0->state == 6) || (param0->state == 14)) {
            UnionRoomDrawing_ResetYesNoMenu(param0);

            Window_CopyToVRAM(&param0->drawingWindow);
        }

        UnionRoomDrawing_SetEraserSprite(param0->toolSprites, 0);
        break;
    case 15:
        break;
    case 8:
        break;
    case 9:
        break;
    default:
        GF_ASSERT("FALSE");
        return;
    }

    UnionRoomDrawing_SetNextState(param0, param1);
}

static const u8 sBrushPatterns[3][8][24] = {
    {
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x22, 0x0, 0x0, 0x0, 0x22, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x33, 0x0, 0x0, 0x0, 0x33, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x44, 0x0, 0x0, 0x0, 0x44, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x55, 0x0, 0x0, 0x0, 0x55, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x77, 0x0, 0x0, 0x0, 0x77, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x88, 0x0, 0x0, 0x0, 0x88, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    },
    {
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x10, 0x11, 0x1, 0x0, 0x10, 0x11, 0x1, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x22, 0x0, 0x0, 0x20, 0x22, 0x2, 0x0, 0x20, 0x22, 0x2, 0x0, 0x0, 0x22, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x33, 0x0, 0x0, 0x30, 0x33, 0x3, 0x0, 0x30, 0x33, 0x3, 0x0, 0x0, 0x33, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x44, 0x0, 0x0, 0x40, 0x44, 0x4, 0x0, 0x40, 0x44, 0x4, 0x0, 0x0, 0x44, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x55, 0x0, 0x0, 0x50, 0x55, 0x5, 0x0, 0x50, 0x55, 0x5, 0x0, 0x0, 0x55, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x66, 0x0, 0x0, 0x60, 0x66, 0x6, 0x0, 0x60, 0x66, 0x6, 0x0, 0x0, 0x66, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x77, 0x0, 0x0, 0x70, 0x77, 0x7, 0x0, 0x70, 0x77, 0x7, 0x0, 0x0, 0x77, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0, 0x0, 0x88, 0x0, 0x0, 0x80, 0x88, 0x8, 0x0, 0x80, 0x88, 0x8, 0x0, 0x0, 0x88, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    },
    {
        { 0x10, 0x11, 0x1, 0x0, 0x11, 0x11, 0x11, 0x0, 0x11, 0x11, 0x11, 0x0, 0x11, 0x11, 0x11, 0x0, 0x11, 0x11, 0x11, 0x0, 0x10, 0x11, 0x1, 0x0 },
        { 0x20, 0x22, 0x2, 0x0, 0x22, 0x22, 0x22, 0x0, 0x22, 0x22, 0x22, 0x0, 0x22, 0x22, 0x22, 0x0, 0x22, 0x22, 0x22, 0x0, 0x20, 0x22, 0x2, 0x0 },
        { 0x30, 0x33, 0x3, 0x0, 0x33, 0x33, 0x33, 0x0, 0x33, 0x33, 0x33, 0x0, 0x33, 0x33, 0x33, 0x0, 0x33, 0x33, 0x33, 0x0, 0x30, 0x33, 0x3, 0x0 },
        { 0x40, 0x44, 0x4, 0x0, 0x44, 0x44, 0x44, 0x0, 0x44, 0x44, 0x44, 0x0, 0x44, 0x44, 0x44, 0x0, 0x44, 0x44, 0x44, 0x0, 0x40, 0x44, 0x4, 0x0 },
        { 0x50, 0x55, 0x5, 0x0, 0x55, 0x55, 0x55, 0x0, 0x55, 0x55, 0x55, 0x0, 0x55, 0x55, 0x55, 0x0, 0x55, 0x55, 0x55, 0x0, 0x50, 0x55, 0x5, 0x0 },
        { 0x60, 0x66, 0x6, 0x0, 0x66, 0x66, 0x66, 0x0, 0x66, 0x66, 0x66, 0x0, 0x66, 0x66, 0x66, 0x0, 0x66, 0x66, 0x66, 0x0, 0x60, 0x66, 0x6, 0x0 },
        { 0x70, 0x77, 0x7, 0x0, 0x77, 0x77, 0x77, 0x0, 0x77, 0x77, 0x77, 0x0, 0x77, 0x77, 0x77, 0x0, 0x77, 0x77, 0x77, 0x0, 0x70, 0x77, 0x7, 0x0 },
        { 0x80, 0x88, 0x8, 0x0, 0x88, 0x88, 0x88, 0x0, 0x88, 0x88, 0x88, 0x0, 0x88, 0x88, 0x88, 0x0, 0x88, 0x88, 0x88, 0x0, 0x80, 0x88, 0x8, 0x0 },
    },
};

static void UnionRoomDrawing_BlitBitmapRectClipped(Window *param0, void *param1, int param2, int param3, int param4, int param5, int param6, int param7, int param8, int param9)
{
    if (param6 < 0) {
        int v0;

        v0 = param6 * -1;

        if (v0 > param8) {
            v0 = param8;
        }

        param6 = 0;
        param2 += v0;
        param4 -= v0;
        param8 -= v0;
    }

    if (param7 < 0) {
        int v1;

        v1 = param7 * -1;

        if (v1 > param9) {
            v1 = param9;
        }

        param7 = 0;
        param3 += v1;
        param5 -= v1;
        param9 -= v1;
    }

    Window_BlitBitmapRect(param0, param1, param2, param3, param4, param5, param6, param7, param8, param9);
}

static void UnionRoomDrawing_DrawLine(Window *param0, const u8 *param1, int param2, int param3, int *param4, int *param5, int param6, int param7)
{
    int v0, v1, v2, v3;
    int v4 = *param4;
    int v5 = *param5;
    int v6 = param2;
    int v7 = param3;

    if ((param6 == 0) && (param7 == 0)) {
        *param4 = param2;
        *param5 = param3;
        return;
    }

    v0 = MATH_IAbs(v6 - v4);
    v1 = MATH_IAbs(v7 - v5);

    if (v0 > v1) {
        if (v4 > v6) {
            v3 = (v5 > v7) ? 1 : -1;
            v2 = v4;
            v4 = v6;
            v6 = v2;
            v5 = v7;
        } else {
            v3 = (v5 < v7) ? 1 : -1;
        }

        UnionRoomDrawing_BlitBitmapRectClipped(param0, (void *)param1, 0, 0, 6, 6, v4, v5, 6, 6);
        v2 = v0 >> 1;

        while (++v4 <= v6) {
            if ((v2 -= v1) < 0) {
                v2 += v0;
                v5 += v3;
            }

            UnionRoomDrawing_BlitBitmapRectClipped(param0, (void *)param1, 0, 0, 6, 6, v4, v5, 6, 6);
        }
    } else {
        if (v5 > v7) {
            v3 = (v4 > v6) ? 1 : -1;
            v2 = v5;
            v5 = v7;
            v7 = v2;
            v4 = v6;
        } else {
            v3 = (v4 < v6) ? 1 : -1;
        }

        UnionRoomDrawing_BlitBitmapRectClipped(param0, (void *)param1, 0, 0, 6, 6, v4, v5, 6, 6);
        v2 = v1 >> 1;

        while (++v5 <= v7) {
            if ((v2 -= v0) < 0) {
                v2 += v1;
                v4 += v3;
            }

            UnionRoomDrawing_BlitBitmapRectClipped(param0, (void *)param1, 0, 0, 6, 6, v4, v5, 6, 6);
        }
    }

    *param4 = param2;
    *param5 = param3;
}

static void UnionRoomDrawing_CopyPrevPoint(UnionRoomDrawingStatus *param0, UnionRoomDrawingPrevPoint *param1)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        param1[v0].hasPrev = param0[v0].pointCount;

        if (param0[v0].pointCount != 0) {
            param1[v0].x = param0[v0].x[param0[v0].pointCount - 1];
            param1[v0].y = param0[v0].y[param0[v0].pointCount - 1];
        }
    }
}

static void UnionRoomDrawing_DrawStrokes(Window *param0, UnionRoomDrawingStatus *param1, UnionRoomDrawingPrevPoint *param2, int param3)
{
    int v0, v1, v2, v3, v4 = 0, v5, v6;
    u32 v7;

    for (v2 = 0; v2 < 5; v2++) {
        if (param1[v2].pointCount != 0) {
            if (param2[v2].hasPrev) {
                v5 = param2[v2].x - 9;
                v6 = param2[v2].y - 17;
            }

            for (v3 = 0; v3 < param1[v2].pointCount; v3++) {
                v0 = param1[v2].x[v3] - 9;
                v1 = param1[v2].y[v3] - 17;

                UnionRoomDrawing_DrawLine(param0, sBrushPatterns[param1[v2].brushSize][param1[v2].penColor], v0, v1, &v5, &v6, v3, param2[v2].hasPrev);

                v4 = 1;
            }
        }
    }

    if (v4 && param3) {
        Window_CopyToVRAM(param0);
    }

    UnionRoomDrawing_CopyPrevPoint(param1, param2);

    for (v2 = 0; v2 < 5; v2++) {
        param1[v2].pointCount = 0;
    }
}

static void UnionRoomDrawing_UpdateRemoteCursors(UnionRoomDrawing *param0)
{
    int v0;
    UnionRoomDrawingStatus *v1 = param0->drawingStatus;

    for (v0 = 0; v0 < 5; v0++) {
        if (v0 != CommSys_CurNetId()) {
            if ((v1[v0].pointCount != 0) && (CommInfo_TrainerInfo(v0) != NULL)) {
                Sprite_SetDrawFlag(param0->playerCursors[v0], TRUE);
                UnionRoomDrawing_SetSpritePosition(param0->playerCursors[v0], v1[v0].x[v1[v0].pointCount - 1], v1[v0].y[v1[v0].pointCount - 1]);
            } else {
                Sprite_SetDrawFlag(param0->playerCursors[v0], FALSE);
            }
        }
    }
}

static void UnionRoomDrawing_AnimateCursorColor(u16 *param0)
{
    fx32 v0;
    GXRgb v1;
    int v2, v3, v4;

    *param0 += 20;

    if (*param0 > 360) {
        *param0 = 0;
    }

    v0 = CalcSineDegrees_Wraparound(*param0);
    v3 = 15 + (v0 * 10) / FX32_ONE;
    v1 = GX_RGB(29, v3, 0);

    GX_LoadOBJPltt((u16 *)&v1, 12 * 2, 2);
}

static int UnionRoomDrawing_CountConnectedTrainers(void)
{
    int v0, v1;
    TrainerInfo *v2;

    v1 = 0;

    for (v0 = 0; v0 < 5; v0++) {
        v2 = CommInfo_TrainerInfo(v0);

        if (v2 != NULL) {
            v1++;
        }
    }

    return v1;
}

static void UnionRoomDrawing_DrawPlayerNames(Window *param0, int param1, u32 param2, UnionRoomDrawing *param3)
{
    int v0, v1 = CommSys_CurNetId();
    int v2;

    if (!UnionRoomDrawing_UpdateTrainerInfo(param3)) {
        return;
    }

    for (v0 = 0; v0 < 5; v0++) {
        if (param3->trainerInfo[v0][0] == NULL) {
            Sprite_SetDrawFlag(param3->penColorSprites[v0], FALSE);
        } else {
            Sprite_SetDrawFlag(param3->penColorSprites[v0], TRUE);
        }
    }

    for (v0 = 0; v0 < 5; v0++) {
        Window_FillRectWithColor(&param0[v0], 0, 0, 0, 10 * 8, 2 * 8);
    }

    for (v0 = 0; v0 < 5; v0++) {
        if (param3->trainerInfo[v0][0] != NULL) {
            TrainerInfo_NameString(param3->trainerInfo[v0][0], param3->playerNameStrings[v0]);

            if (v1 == v0) {
                Text_AddPrinterWithParamsAndColor(&param0[v0], FONT_MESSAGE, param3->playerNameStrings[v0], 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(3, 4, 15), NULL);
            } else {
                Text_AddPrinterWithParamsAndColor(&param0[v0], FONT_MESSAGE, param3->playerNameStrings[v0], 0, 0, TEXT_SPEED_NO_TRANSFER, param2, NULL);
            }
        }

        Window_CopyToVRAM(&param0[v0]);
    }
}

static void UnionRoomDrawing_SendDrawingStatus(UnionRoomDrawing *param0)
{
    if (CommSys_CurNetId() == 0) {
        if (CommSys_IsServerQueueEmpty()) {
            param0->localDrawingStatus.state = param0->drawingState;
            param0->drawingStatusBroadcast[0] = param0->localDrawingStatus;
            CommSys_SendDataServer(120, param0->drawingStatusBroadcast, 10 * 5);
        }
    } else {
        if (CommSys_IsQueueEmpty()) {
            CommSys_SendData(119, &param0->localDrawingStatus, 10);
        }
    }
}

static int UnionRoomDrawing_CountConnected(void)
{
    int i, v0;

    for (v0 = 0, i = 0; i < 5; i++) {
        if (CommInfo_TrainerInfo(i) != NULL) {
            v0++;
        }
    }

    return v0;
}

int UnionRoomDrawing_GetConnectedCount(void)
{
    return UnionRoomDrawing_CountConnected();
}

static int UnionRoomDrawing_UpdateTrainerInfo(UnionRoomDrawing *param0)
{
    int v0, v1 = 0;

    for (v0 = 0; v0 < 5; v0++) {
        param0->trainerInfo[v0][1] = param0->trainerInfo[v0][0];
        param0->trainerInfo[v0][0] = CommInfo_TrainerInfo(v0);
    }

    for (v0 = 0; v0 < 5; v0++) {
        if (param0->trainerInfo[v0][1] != param0->trainerInfo[v0][0]) {
            v1 = 1;
        }
    }

    return v1;
}

static void UnionRoomDrawing_ShowMessage(UnionRoomDrawing *param0, int param1, int param2)
{
    String *v0 = String_Init(40 * 2, HEAP_ID_DRAWING);

    MessageLoader_GetString(param0->msgLoader, param1, v0);
    StringTemplate_Format(param0->strTemplate, param0->messageString, v0);
    String_Free(v0);

    Window_FillTilemap(&param0->messageWindow, 0xf0f);
    Window_DrawMessageBoxWithScrollCursor(&param0->messageWindow, 0, 1, 10);

    if (param2 == 0) {
        param2 = 0;
    }

    param0->textPrinterID = Text_AddPrinterWithParams(&param0->messageWindow, FONT_MESSAGE, param0->messageString, 0, 0, param2, NULL);

    if (param2 == 0) {
        param0->textPrinterID = 0xff;
    }
}

static int UnionRoomDrawing_IsMessageDone(int param0)
{
    if (param0 == 0xff) {
        return 1;
    }

    if (Text_IsPrinterActive(param0) == 0) {
        return 1;
    }

    return 0;
}

static void UnionRoomDrawing_EraseMessageBox(UnionRoomDrawing *param0)
{
    Window_EraseMessageBox(&param0->messageWindow, 0);
}

static void UnionRoomDrawing_SetMaxConnections(UnionRoomDrawing *param0, int param1)
{
    if (CommSys_CurNetId() == 0) {
        int v0 = CommSys_ConnectedCount() + param1;

        if (v0 > 5) {
            v0 = 5;
        }

        CommManager_SetMaxNumConnections(v0);
    }
}

static int UnionRoomDrawing_UpdateConnectionState(UnionRoomDrawing *param0)
{
    int v0 = UnionRoomDrawing_CountConnected();

    switch (v0) {
    case 1:
        if (param0->state <= 14) {
            if (WirelessManager_GetConnectedBitmap() != 1) {
                param0->readyToDraw = 1;
            }

            param0->nextState = 19;
            CommManager_SetMaxNumConnections(1);

            if (param0->clientReadySent) {
                UnionRoomDrawing_ResetYesNoMenu(param0);
                Sprite_SetAnim(param0->toolSprites[8], sPenColorSpriteData[8][2]);
            }

            return 2;
        }
        break;
    case 2:
    case 3:
    case 4:
        UnionRoom_BroadcastActivity(1);

        if (v0 < param0->connectedCountSnapshot) {
            if (param0->drawingState == 2) {
                UnionRoomDrawing_SetMaxConnections(param0, 0);
            } else {
                UnionRoomDrawing_SetMaxConnections(param0, 1);
            }
        }
        break;
    case 5:
        UnionRoom_BroadcastActivity(8);
        break;
    }

    if (v0 < param0->connectedCountSnapshot) {
        param0->connectedCount = CommSys_ConnectedCount();
        param0->connectedBitmap = WirelessManager_GetConnectedBitmap();

        if (param0->disconnectHandled) {
            if (!(param0->connectedBitmap & param0->disconnectedBitmap)) {
                UnionRoomDrawing_SetMaxConnections(param0, 1);

                param0->drawingState = 1;
                param0->disconnectHandled = 0;
                param0->disconnectedBitmap = 0;
            }
        }
    }

    param0->connectedCountSnapshot = UnionRoomDrawing_CountConnected();

    if (param0->connectedCount < CommSys_ConnectedCount()) {
        param0->drawingState = 2;
        param0->disconnectHandled = 1;
        param0->disconnectedBitmap = param0->connectedBitmap ^ WirelessManager_GetConnectedBitmap();
        GF_ASSERT((param0->disconnectedBitmap == 2) || (param0->disconnectedBitmap == 4) || (param0->disconnectedBitmap == 8) || (param0->disconnectedBitmap == 16));
    }

    return 1;
}

static void UnionRoomDrawing_SetNextState(UnionRoomDrawing *param0, int param1)
{
    param0->nextState = param1;
}

static void UnionRoomDrawing_ApplyNextState(UnionRoomDrawing *param0, int param1)
{
    if (param0->state != param0->nextState) {
        if (param1 != 2) {
            param0->state = param0->nextState;
        } else {
            if (sStateHandlers[param0->nextState].runInState2) {
                param0->state = param0->nextState;
            }
        }
    }
}

static BOOL UnionRoomDrawing_InitYesNoMenu(UnionRoomDrawing *param0, YesNoTouchMenuParams *param1)
{
    if (!param0->clientReadySent) {
        YesNoTouchMenu_InitWithParams(param0->yesNoMenu, param1);
        param0->clientReadySent = 1;
        return 1;
    } else {
        return 0;
    }
}

static void UnionRoomDrawing_ResetYesNoMenu(UnionRoomDrawing *param0)
{
    if (param0->clientReadySent) {
        YesNoTouchMenu_Reset(param0->yesNoMenu);
        param0->clientReadySent = 0;
    }
}

static int UnionRoomDrawing_IsCancelPressed(UnionRoomDrawing *param0)
{
    int v0 = TouchScreen_CheckRectanglePressed(sCancelButtonTouchRect);

    if (v0 != 0xffffffff) {
        return 1;
    }

    return 0;
}

static void UnionRoomDrawing_UpdateLocalStatus(UnionRoomDrawingStatus *param0, TouchPadDataBuffer *param1, int param2, int param3)
{
    int v0, v1;

    if (param1->bufferSize != 0) {
        param0->x[0] = param1->buffer[0].x;
        param0->y[0] = param1->buffer[0].y;

        v1 = param1->bufferSize - 1;

        param0->x[1] = param1->buffer[v1].x;
        param0->y[1] = param1->buffer[v1].y;

        for (v0 = 0; v0 < 2; v0++) {
            if ((param0->x[v0] + param0->y[v0]) == 0) {
                param1->bufferSize = 0;
            }
        }
    }

    if (param1->bufferSize >= 2) {
        param0->pointCount = 2;
    } else {
        param0->pointCount = param1->bufferSize;
    }

    param0->penColor = param2;
    param0->brushSize = param3;
}
