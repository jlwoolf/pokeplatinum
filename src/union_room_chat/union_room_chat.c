#include "union_room_chat/union_room_chat.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/struct_0205B43C_decl.h"
#include "struct_defs/struct_wireless_game_info.h"
#include "struct_defs/struct_0205C22C.h"
#include "struct_defs/struct_0205C924.h"
#include "struct_defs/struct_0205C95C.h"

#include "field/field_system.h"
#include "union_room_chat/union_room_chat_decl.h"

#include "bg_window.h"
#include "easy_chat_sentence.h"
#include "field_message.h"
#include "field_task.h"
#include "font.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "message_util.h"
#include "pal_pad.h"
#include "save_player.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task_extensions.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "touch_screen.h"
#include "trainer_info.h"
#include "comm_server_client.h"
#include "union_room.h"

FS_EXTERN_OVERLAY(union_room_chat);

typedef struct {
    u16 count; // number of chat log entries
    u16 prevCount; // entry count on the previous update
    u16 scrollOffset; // index of the topmost visible entry
    u16 showScrollArrow; // whether the scroll arrow sprite is drawn
} UnionRoomChatListState;

typedef struct {
    Window nameWindow;
    Window sentenceWindow;
    Window palPadWindow;
    int gender; // selects the row's background graphic
    int highlightTimer; // counts down while the row is highlighted
} UnionRoomChatRow;

struct UnionRoomChat_t {
    int state;
    UnionRoomTrainers *trainers;
    UnionRoom *unionRoom;
    FieldSystem *fieldSystem;
    TrainerInfo *trainerInfo;
    BgConfig *bgConfig;
    StringTemplate *stringTemplate;
    MessageLoader *messageLoader;
    u16 *screenDataRaw;
    NNSG2dScreenData *screenData;
    SpriteList *spriteList;
    G2dRenderer g2dRenderer;
    SpriteResourceCollection *spriteResources[4];
    SpriteResource *spriteResourceData[4];
    SpriteResourcesHeader spriteResourcesHeader;
    Sprite *sprites[8];
    int unk_21C; // unused
    int unk_220; // unused
    int unk_224; // unused
    int lastTouchedRow;
    UnionRoomChatRow rows[3];
    UnionRoomChatLog *chatLog;
    UnionRoomChatListState listState;
    int lastScrollOffset;
    int highlightTotal;
    BOOL rowsDirty;
    u8 touchRepeatActive;
    s8 touchRepeatCounter;
    u8 touchRepeatDelay;
    u8 touchRepeatInterval;
    BOOL scrollbarDragging;
    u16 arrowPressed[2];
    SysTask *task;
};

static void UnionRoomChat_InitResources(UnionRoomChat *param0);
static void UnionRoomChat_FreeBackgrounds(BgConfig *param0);
static void UnionRoomChat_InitBackgrounds(BgConfig *param0);
static void UnionRoomChat_InitSprites(UnionRoomChat *param0);
static void UnionRoomChat_CreateSprites(UnionRoomChat *param0);
static void UnionRoomChat_InitWindows(BgConfig *param0, UnionRoomChatRow *param1);
static void UnionRoomChat_FreeWindows(UnionRoomChatRow *param0);
static void UnionRoomChat_DrawRows(UnionRoomChat *param0);
static void UnionRoomChat_DrawRow(UnionRoomChat *param0, int param1, UnionRoomChatLogEntry *param2);
static void UnionRoomChat_HandleInput(UnionRoomChat *param0);
static void UnionRoomChat_UpdateScroll(UnionRoomChat *param0);
static void UnionRoomChat_SetArrowPosition(Sprite *param0, int param1);
static void UnionRoomChat_PollNewMessages(UnionRoomChat *param0);
static void UnionRoomChat_AppendEntry(UnionRoomChat *param0, u32 param1, EasyChatSentence *param2, TrainerInfo *param3);
static int UnionRoomChat_IsNewSentence(UnionRoomChat *param0, EasyChatSentence *param1, int param2);
static int UnionRoomChat_NextIndex(UnionRoomChatLog *param0, int param1);
static int UnionRoomChat_WrapIndex(int param0, int param1);
static int UnionRoomChat_HandleListTouch(UnionRoomChat *param0);
static int UnionRoomChat_HandleScrollbarTouch(UnionRoomChat *param0);
static void UnionRoomChat_MarkRowsDirty(UnionRoomChat *param0);
static void UnionRoomChat_AddMessage(UnionRoomChat *param0, TrainerInfo *param1, EasyChatSentence *param2, u32 param3);
static String *UnionRoomChat_GetPalPadString(PalPad *param0, u32 param1, StringTemplate *param2, MessageLoader *param3, TrainerInfo *param4);
static void UnionRoomChat_UpdateRowHighlights(BgConfig *param0, NNSG2dScreenData *param1, UnionRoomChatRow *param2, int param3, int param4, int *param5);
static void UnionRoomChat_InitTouchRepeat(UnionRoomChat *param0);
static void UnionRoomChat_UpdateTouchRepeat(UnionRoomChat *param0);
static BOOL UnionRoomChat_IsTouchRepeating(const UnionRoomChat *param0);
static void UnionRoomChat_SetScrollbarDragging(UnionRoomChat *param0, BOOL param1);
static BOOL UnionRoomChat_IsScrollbarDragging(const UnionRoomChat *param0);
static void UnionRoomChat_SetArrowAnim(UnionRoomChat *param0, int param1);
static void UnionRoomChat_UpdateArrowAnims(UnionRoomChat *param0);

static void UnionRoomChat_RunTask(SysTask *param0, void *param1)
{
    UnionRoomChat *v0 = param1;
    BgConfig *v1 = v0->bgConfig;
    int v2;

    if (v0->fieldSystem->unk_80 == NULL) {
        return;
    }

    switch (v0->state) {
    case 0:
        UnionRoomChat_InitBackgrounds(v1);
        UnionRoomChat_InitResources(v0);
        SetAutorepeat(4, 8);
        UnionRoomChat_InitTouchRepeat(v0);
        UnionRoomChat_SetScrollbarDragging(v0, 1);
        v0->state++;
        break;
    case 1:
        UnionRoomChat_InitSprites(v0);
        UnionRoomChat_CreateSprites(v0);
        Font_UseImmediateGlyphAccess(FONT_MESSAGE, 4);
        UnionRoomChat_InitWindows(v0->bgConfig, v0->rows);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        UnionRoomChat_MarkRowsDirty(v0);
        v0->state++;
        break;
    case 2:
        UnionRoomChat_UpdateTouchRepeat(v0);
        UnionRoomChat_PollNewMessages(v0);
        UnionRoomChat_UpdateScroll(v0);
        UnionRoomChat_HandleInput(v0);
        UnionRoomChat_DrawRows(v0);
        UnionRoomChat_UpdateArrowAnims(v0);
        SpriteList_Update(v0->spriteList);
        break;
    case 3:
        break;
    }
}

static void UnionRoomChat_InitResources(UnionRoomChat *param0)
{
    int v0;

    param0->rowsDirty = 0;
    param0->listState.count = 0;
    param0->listState.prevCount = 0;
    param0->listState.scrollOffset = 0;
    param0->listState.showScrollArrow = 0;
    param0->stringTemplate = StringTemplate_Default(HEAP_ID_FIELD1);
    param0->messageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNION_ROOM, HEAP_ID_FIELD1);
    param0->screenDataRaw = Graphics_GetScrnData(NARC_INDEX_GRAPHIC__UNIONROOM, 3, TRUE, &(param0->screenData), HEAP_ID_FIELD1);
}

static void UnionRoomChat_InitWindows(BgConfig *param0, UnionRoomChatRow *param1)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Window_Add(param0, &param1[v0].nameWindow, 4 + v0, 1, 1 + v0 * 8, 8, 2, 12, (32 * 5) + v0 * (8 * 2));
        Window_FillTilemap(&param1[v0].nameWindow, 0x0);

        Window_CopyToVRAM(&param1[v0].nameWindow);

        Window_Add(param0, &param1[v0].sentenceWindow, 4 + v0, 2, 3 + v0 * 8, 27, 5, 12, ((32 * 5) + (8 * 2) * 3) + v0 * (27 * 5));
        Window_FillTilemap(&param1[v0].sentenceWindow, 0x0);
        Window_CopyToVRAM(&param1[v0].sentenceWindow);

        Window_Add(param0, &param1[v0].palPadWindow, 4 + v0, 12, 1 + v0 * 8, 15, 2, 12, (((32 * 5) + (8 * 2) * 3) + (27 * 5) * 3) + v0 * (15 * 2));
        Window_FillTilemap(&param1[v0].palPadWindow, 0x0);
        Window_CopyToVRAM(&param1[v0].palPadWindow);
    }
}

static void UnionRoomChat_FreeWindows(UnionRoomChatRow *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Window_Remove(&param0[v0].sentenceWindow);
        Window_Remove(&param0[v0].nameWindow);
        Window_Remove(&param0[v0].palPadWindow);
    }
}

UnionRoomChat *UnionRoomChat_New(FieldSystem *fieldSystem)
{
    SysTask *v1 = SysTask_StartAndAllocateParam(UnionRoomChat_RunTask, sizeof(UnionRoomChat), 4, 4);
    UnionRoomChat *v0 = SysTask_GetParam(v1);

    v0->fieldSystem = fieldSystem;
    v0->bgConfig = fieldSystem->bgConfig;
    v0->trainers = fieldSystem->unk_80;
    v0->unionRoom = fieldSystem->unk_7C;
    v0->trainerInfo = SaveData_GetTrainerInfo(fieldSystem->saveData);
    v0->state = 0;
    v0->task = v1;
    v0->chatLog = fieldSystem->unk_80->chatLog;

    return v0;
}

void UnionRoomChat_Free(UnionRoomChat *param0)
{
    if (param0->state == 2) {
        BgConfig *v0 = param0->bgConfig;
        int v1;

        param0->state = 3;

        Font_UseLazyGlyphAccess(FONT_MESSAGE);
        SpriteTransfer_ResetCharTransfer(param0->spriteResourceData[0]);
        SpriteTransfer_ResetPlttTransfer(param0->spriteResourceData[1]);

        for (v1 = 0; v1 < 4; v1++) {
            SpriteResourceCollection_Delete(param0->spriteResources[v1]);
        }

        SpriteList_Delete(param0->spriteList);
        MessageLoader_Free(param0->messageLoader);
        StringTemplate_Free(param0->stringTemplate);

        UnionRoomChat_FreeWindows(param0->rows);
        UnionRoomChat_FreeBackgrounds(v0);

        Heap_Free(param0->screenDataRaw);
        SysTask_FinishAndFreeParam(param0->task);
    } else {
        GF_ASSERT(FALSE);
    }
}

static void UnionRoomChat_FreeBackgrounds(BgConfig *param0)
{
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_2);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_3);
}

static void UnionRoomChat_InitBackgrounds(BgConfig *param0)
{
    UnionRoomChat_FreeBackgrounds(param0);

    {
        BgTemplate v0 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x6000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_0, &v0, 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x6800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_1, &v1, 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
    }

    {
        BgTemplate v2 = {
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
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_2, &v2, 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_2);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x7800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_3, &v3, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
    }

    Graphics_LoadPalette(NARC_INDEX_GRAPHIC__UNIONROOM, 0, 4, 0, 0x20 * 3, HEAP_ID_FIELD1);
    Graphics_LoadTilesToBgLayer(NARC_INDEX_GRAPHIC__UNIONROOM, 2, param0, 7, 0, (32 * 5) * 0x20, 1, HEAP_ID_FIELD1);
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_GRAPHIC__UNIONROOM, 4, param0, 7, 0, 32 * 24 * 2, 1, HEAP_ID_FIELD1);
    FieldMessage_LoadTextPalettes(4, FALSE);
}

static void UnionRoomChat_InitSprites(UnionRoomChat *param0)
{
    int v0;

    param0->spriteList = SpriteList_InitRendering(10, &param0->g2dRenderer, HEAP_ID_FIELD1);

    for (v0 = 0; v0 < 4; v0++) {
        param0->spriteResources[v0] = SpriteResourceCollection_New(1, v0, HEAP_ID_FIELD1);
    }

    param0->spriteResourceData[0] = SpriteResourceCollection_AddTiles(param0->spriteResources[0], 74, 5, 1, 999, NNS_G2D_VRAM_TYPE_2DSUB, HEAP_ID_FIELD1);
    param0->spriteResourceData[1] = SpriteResourceCollection_AddPalette(param0->spriteResources[1], 74, 1, 0, 999, NNS_G2D_VRAM_TYPE_2DSUB, 1, HEAP_ID_FIELD1);
    param0->spriteResourceData[2] = SpriteResourceCollection_Add(param0->spriteResources[2], 74, 6, 1, 999, 2, HEAP_ID_FIELD1);
    param0->spriteResourceData[3] = SpriteResourceCollection_Add(param0->spriteResources[3], 74, 7, 1, 999, 3, HEAP_ID_FIELD1);

    SpriteTransfer_RequestCharAtEnd(param0->spriteResourceData[0]);
    SpriteTransfer_RequestPlttFreeSpace(param0->spriteResourceData[1]);
}

static const int sArrowYPositions[] = {
    0x0,
    0xA0,
    0x60
};

static void UnionRoomChat_CreateSprites(UnionRoomChat *param0)
{
    int v0;

    SpriteResourcesHeader_Init(&param0->spriteResourcesHeader, 999, 999, 999, 999, 0xffffffff, 0xffffffff, 0, 0, param0->spriteResources[0], param0->spriteResources[1], param0->spriteResources[2], param0->spriteResources[3], NULL, NULL);

    {
        AffineSpriteListTemplate v1;

        v1.list = param0->spriteList;
        v1.resourceData = &param0->spriteResourcesHeader;
        v1.position.z = 0;
        v1.affineScale.x = FX32_ONE;
        v1.affineScale.y = FX32_ONE;
        v1.affineScale.z = FX32_ONE;
        v1.affineZRotation = 0;
        v1.priority = 0;
        v1.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
        v1.heapID = HEAP_ID_FIELD1;

        for (v0 = 0; v0 < 3; v0++) {
            v1.position.x = FX32_CONST(256 - 24);
            v1.position.y = FX32_CONST(sArrowYPositions[v0]) + (192 << FX32_SHIFT);

            param0->sprites[v0] = SpriteList_AddAffine(&v1);

            Sprite_SetAnimateFlag(param0->sprites[v0], 1);
            Sprite_SetAnim(param0->sprites[v0], v0);
        }
    }
}

static int UnionRoomChat_NextIndex(UnionRoomChatLog *param0, int param1)
{
    param1++;

    if (param1 == 30) {
        param1 = 0;
    }

    return param1;
}

static int UnionRoomChat_WrapIndex(int param0, int param1)
{
    int v0 = param0 + param1;

    if (v0 >= 30) {
        v0 -= 30;
    }

    return v0;
}

static void UnionRoomChat_DrawRow(UnionRoomChat *param0, int param1, UnionRoomChatLogEntry *param2)
{
    param0->rows[param1].gender = param2->gender;

    Bg_CopyToTilemapRect(param0->bgConfig, 7, 0, param1 * 8, 32, 8, param0->screenData->rawData, 0, 24 * param0->rows[param1].gender, 32, 48);
    Window_FillTilemap(&param0->rows[param1].nameWindow, 0x0);
    Window_FillTilemap(&param0->rows[param1].sentenceWindow, 0x0);
    Window_FillTilemap(&param0->rows[param1].palPadWindow, 0x0);
    Text_AddPrinterWithParamsAndColor(&param0->rows[param1].nameWindow, FONT_MESSAGE, param2->trainerName, 0, 1, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Text_AddPrinterWithParamsAndColor(&param0->rows[param1].sentenceWindow, FONT_MESSAGE, param2->sentenceString, 0, 6, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Window_ScheduleCopyToVRAM(&param0->rows[param1].nameWindow);
    Window_ScheduleCopyToVRAM(&param0->rows[param1].sentenceWindow);

    if (param2->palPadString) {
        Text_AddPrinterWithParamsAndColor(&param0->rows[param1].palPadWindow, FONT_MESSAGE, param2->palPadString, 0, 1, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    }

    Window_ScheduleCopyToVRAM(&param0->rows[param1].palPadWindow);
}

static void UnionRoomChat_DrawRows(UnionRoomChat *param0)
{
    int v0, v1;
    int v2 = UnionRoomChat_WrapIndex(param0->chatLog->startIndex, param0->listState.scrollOffset);
    int v3 = param0->chatLog->count;

    if (v3 > 3) {
        v3 = 3;
    }

    if (param0->listState.scrollOffset != param0->lastScrollOffset) {
        UnionRoomChat_MarkRowsDirty(param0);
        param0->lastScrollOffset = param0->listState.scrollOffset;
    }

    if (param0->rowsDirty == 1) {
        for (v0 = 0; v0 < v3; v0++) {
            UnionRoomChat_DrawRow(param0, v0, &param0->chatLog->entries[v2]);
            v2 = UnionRoomChat_NextIndex(param0->chatLog, v2);
        }

        DC_FlushRange((void *)Bg_GetTilemapBuffer(param0->bgConfig, 7), 32 * 24 * 2);
        Bg_CopyTilemapBufferRangeToVRAM(param0->bgConfig, 7, Bg_GetTilemapBuffer(param0->bgConfig, 7), 32 * 24 * 2, 0);

        param0->rowsDirty = 0;
    }
}

static const TouchScreenRect sListTouchRects[] = {
    { 0x0, 0x20, 0xE8, 0xF8 },
    { 0xA0, 0x20, 0xE8, 0xF8 },
    { 0x0, 0x40, 0x0, 0xE8 },
    { 0x40, 0x80, 0x0, 0xE8 },
    { 0x80, 0xC0, 0x0, 0xE8 },
    { 0x30, 0x90, 0xE8, 0x100 },
    { 0xff, 0x0, 0x0, 0x0 }
};

static const TouchScreenRect sScrollbarTouchRects[] = {
    { 0x30, 0x90, 0xE8, 0x100 },
    { 0x0, 0x40, 0x0, 0xE8 },
    { 0x40, 0x80, 0x0, 0xE8 },
    { 0x80, 0xC0, 0x0, 0xE8 },
    { 0xff, 0x0, 0x0, 0x0 }
};

static void UnionRoomChat_SetArrowPosition(Sprite *param0, int param1)
{
    VecFx32 v0;

    v0.x = FX32_CONST(256 - 24);
    v0.y = FX32_CONST(param1) + (192 << FX32_SHIFT);
    v0.z = 0;

    Sprite_SetPosition(param0, &v0);
}

static void UnionRoomChat_UpdateScroll(UnionRoomChat *param0)
{
    param0->listState.count = param0->chatLog->count;

    if ((param0->listState.count > 3) && (param0->listState.prevCount <= 3)) {
        param0->listState.showScrollArrow = 1;
        param0->listState.scrollOffset = param0->listState.count - 3;
    }

    Sprite_SetDrawFlag(param0->sprites[2], param0->listState.showScrollArrow);

    if (param0->listState.showScrollArrow) {
        if (UnionRoomChat_IsScrollbarDragging(param0) == 1) {
            int v0, v1;

            v1 = (8 * 4 + 16) + (param0->listState.scrollOffset * (192 - 8 * 8 - 16 * 2)) / (param0->listState.count - 3);
            UnionRoomChat_SetArrowPosition(param0->sprites[2], v1);
        }
    }

    param0->listState.prevCount = param0->listState.count;
}

static int UnionRoomChat_HandleListTouch(UnionRoomChat *param0)
{
    int v0, v1, v2, v3;
    WMBssDesc *v4;
    WirelessGameInfo *v5;

    v0 = TouchScreen_CheckRectangleHeld(sListTouchRects);
    v3 = UnionRoomChat_IsTouchRepeating(param0);

    if (v0 != 0xffffffff) {
        switch (v0) {
        case 0:
            UnionRoomChat_SetArrowAnim(param0, v0);

            if (v3 == 1) {
                if (param0->listState.scrollOffset != 0) {
                    Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);
                    param0->listState.scrollOffset--;
                }

                param0->lastTouchedRow = v0 - 2;
            }
            break;
        case 1:
            UnionRoomChat_SetArrowAnim(param0, v0);

            if (v3 == 1) {
                if (param0->listState.scrollOffset < param0->listState.count - 3) {
                    Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);
                    param0->listState.scrollOffset++;
                }

                param0->lastTouchedRow = v0 - 2;
            }
            break;
        case 5:
            param0->lastTouchedRow = v0 - 2;
            break;
        default:
            if (gSystem.touchPressed == 0) {
                break;
            }

            if (param0->chatLog->count >= (v0 - 1)) {
                v2 = UnionRoomChat_WrapIndex(param0->chatLog->startIndex, param0->listState.scrollOffset + v0 - 2);

                for (v1 = 0; v1 < 10; v1++) {
                    v4 = CommServerClient_GetServerBssDesc(v1);

                    if (v4 != NULL) {
                        v5 = (WirelessGameInfo *)&v4->gameInfo.userGameInfo;

                        if ((param0->trainers->slots[v1].phase == 2) && (v5->unk_00 == param0->chatLog->entries[v2].trainerId)) {
                            Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);
                            param0->trainers->slots[v1].startWarpEffect = 1;
                            break;
                        }
                    }
                }

                {
                    TrainerInfo *v6 = CommServerClient_GetPersonalTrainerInfo();

                    if (param0->chatLog->entries[v2].trainerId == TrainerInfo_ID(v6)) {
                        Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);
                        param0->trainers->slots[50].startWarpEffect = 1;
                    }
                }
            }

            param0->lastTouchedRow = v0 - 2;
            break;
        }
    }

    return v0;
}

static int UnionRoomChat_HandleScrollbarTouch(UnionRoomChat *param0)
{
    int v0 = TouchScreen_CheckRectangleHeld(sScrollbarTouchRects);

    if (v0 != 0xffffffff) {
        u32 v1, v2;

        switch (v0) {
        case 0:
            UnionRoomChat_SetScrollbarDragging(param0, 0);
            TouchScreen_GetHoldState(&v1, &v2);
            UnionRoomChat_SetArrowPosition(param0->sprites[2], v2);

            if (param0->listState.count > 3) {
                int v3, v4;

                v3 = (192 - 8 * 8 - 16 * 2) / (param0->listState.count - 2);

                for (v4 = 0; v4 < param0->listState.count - 2; v4++) {
                    if ((v2 >= (8 * 4 + 16) + v3 * v4) && (v2 < (8 * 4 + 16) + v3 * (v4 + 1))) {
                        param0->listState.scrollOffset = v4;
                        break;
                    }
                }
            }
            break;
        default:
            if (param0->chatLog->count >= v0) {
                if (param0->lastTouchedRow == (v0 - 1)) {
                    if (param0->rows[v0 - 1].highlightTimer < 2 * 2 + 1) {
                        param0->rows[v0 - 1].highlightTimer++;
                    }
                }
            }
            break;
        }
    } else {
        UnionRoomChat_SetScrollbarDragging(param0, 1);
    }

    return v0;
}

static void UnionRoomChat_HandleScrollKeys(UnionRoomChat *param0)
{
    if (gSystem.heldKeys & PAD_BUTTON_L) {
        UnionRoomChat_SetArrowAnim(param0, 0);

        if (gSystem.pressedKeysRepeatable & PAD_BUTTON_L) {
            if (param0->listState.scrollOffset != 0) {
                param0->listState.scrollOffset--;
                Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);
            }
        }
    } else if (gSystem.heldKeys & PAD_BUTTON_R) {
        UnionRoomChat_SetArrowAnim(param0, 1);

        if (gSystem.pressedKeysRepeatable & PAD_BUTTON_R) {
            if (param0->listState.scrollOffset < param0->listState.count - 3) {
                param0->listState.scrollOffset++;
                Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);
            }
        }
    }
}

static void UnionRoomChat_HandleInput(UnionRoomChat *param0)
{
    int v0 = 0xffffffff;

    if (!FieldSystem_IsRunningTask(param0->fieldSystem)) {
        int v1;

        v1 = UnionRoomChat_HandleListTouch(param0);
        v0 = UnionRoomChat_HandleScrollbarTouch(param0);

        if ((v1 == 0xffffffff) && (v0 == 0xffffffff)) {
            UnionRoomChat_HandleScrollKeys(param0);
        }
    }

    UnionRoomChat_UpdateRowHighlights(param0->bgConfig, param0->screenData, param0->rows, v0 - 1, param0->chatLog->count, &param0->highlightTotal);
}

static const int sRowBounceOffsets[] = {
    0x0,
    0x3,
    0x5
};

static void UnionRoomChat_UpdateRowHighlights(BgConfig *param0, NNSG2dScreenData *param1, UnionRoomChatRow *param2, int param3, int param4, int *param5)
{
    int v0, v1 = 0;

    if (param4 > 3) {
        param4 = 3;
    }

    for (v0 = 0; v0 < param4; v0++) {
        if (param3 != v0) {
            if (param2[v0].highlightTimer != 0) {
                param2[v0].highlightTimer--;
            }
        }

        v1 += param2[v0].highlightTimer;
    }

    if ((v1 == 0) && (*param5 == 0)) {
        *param5 = v1;
        return;
    }

    *param5 = v1;

    for (v0 = 0; v0 < param4; v0++) {
        int v2 = param2[v0].highlightTimer / 2;

        Bg_CopyToTilemapRect(param0, 7, 0, v0 * 8, 32, 8, param1->rawData, 0, 24 * param2[v0].gender + 8 * v2, 32, 48);
        Bg_SetOffset(param0, BG_LAYER_SUB_0 + v0, 3, sRowBounceOffsets[v2]);
    }

    DC_FlushRange((void *)Bg_GetTilemapBuffer(param0, 7), 32 * 24 * 2);
    Bg_CopyTilemapBufferRangeToVRAM(param0, 7, Bg_GetTilemapBuffer(param0, 7), 32 * 24 * 2, 0);
}

static String *UnionRoomChat_GetPalPadString(PalPad *param0, u32 param1, StringTemplate *param2, MessageLoader *param3, TrainerInfo *param4)
{
    String *v0 = NULL;
    String *v1;
    int v2 = 0;

    if (param1 != TrainerInfo_ID(param4)) {
        v2 = PalPad_TrainerIsFriend(param0, param1);
    }

    if (v2 > 0) {
        if (v2 == 1) {
            StringTemplate_SetPlayerName(param2, 0, param4);
        } else if (v2 >= 2) {
            int v3 = v2 - 2;

            v1 = String_Init(10, HEAP_ID_89);

            String_CopyChars(v1, PalPad_GetTrainerNamePointer(param0, v3));
            StringTemplate_SetString(param2, 0, v1, 0, 0, PalPad_GetTrainerLanguage(param0, v3));
            String_Free(v1);
        }

        v0 = MessageUtil_ExpandedString(param2, param3, 208, HEAP_ID_89);
    }

    return v0;
}

static void UnionRoomChat_AppendEntry(UnionRoomChat *param0, u32 param1, EasyChatSentence *param2, TrainerInfo *param3)
{
    UnionRoomChatLog *v0 = param0->chatLog;
    PalPad *v1 = param0->trainers->palPad;
    int *v2;

    if (v0->count == 30) {
        v2 = &v0->startIndex;
    } else {
        v2 = &v0->count;
    }

    if (v0->entries[*v2].sentenceString != NULL) {
        String_Free(v0->entries[*v2].sentenceString);
    }

    if (v0->entries[*v2].palPadString != NULL) {
        String_Free(v0->entries[*v2].palPadString);
    }

    String_CopyChars(v0->entries[*v2].trainerName, TrainerInfo_Name(param3));

    v0->entries[*v2].sentence = *param2;
    v0->entries[*v2].trainerId = param1;
    v0->entries[*v2].gender = TrainerInfo_Gender(param3);
    v0->entries[*v2].sentenceString = EasyChatSentence_ToString(param2, HEAP_ID_89);
    v0->entries[*v2].palPadString = UnionRoomChat_GetPalPadString(v1, param1, param0->stringTemplate, param0->messageLoader, param0->trainerInfo);

    (*v2)++;

    if (v0->startIndex == 30) {
        v0->startIndex = 0;
    }
}

static int UnionRoomChat_IsNewSentence(UnionRoomChat *param0, EasyChatSentence *param1, int param2)
{
    int v0, v1;

    if (!EasyChatSentence_IsValid(param1)) {
        return 0;
    }

    for (v0 = 0; v0 < param0->chatLog->count; v0++) {
        if (param2 == param0->chatLog->entries[v0].trainerId) {
            if (EasyChatSentence_Compare(param1, &param0->chatLog->entries[v0].sentence)) {
                break;
            }
        }
    }

    if ((v0 != param0->chatLog->count) && (param0->chatLog->count != 0)) {
        return 0;
    }

    if (param2 == param0->chatLog->entries[v0].trainerId) {
        (void)0;
    } else if (EasyChatSentence_Compare(param1, &param0->chatLog->entries[v0].sentence)) {
        (void)0;
    }

    return 1;
}

static void UnionRoomChat_AddMessage(UnionRoomChat *param0, TrainerInfo *param1, EasyChatSentence *param2, u32 param3)
{
    int v0 = 0;

    if (param0->listState.scrollOffset == param0->listState.count - 3) {
        v0 = 1;
    }

    UnionRoomChat_AppendEntry(param0, param3, param2, param1);

    if (param0->listState.showScrollArrow) {
        if (v0) {
            param0->listState.scrollOffset = param0->chatLog->count - 3;
        }
    }

    UnionRoomChat_MarkRowsDirty(param0);
}

static void UnionRoomChat_PollNewMessages(UnionRoomChat *param0)
{
    int v0, v1;
    WMBssDesc *v2;
    WirelessGameInfo *v3;
    EasyChatSentence *v4;
    TrainerInfo *v5;
    EasyChatSentence v6;

    if (FieldSystem_IsRunningTask(param0->fieldSystem)) {
        return;
    }

    for (v0 = 0; v0 < 16; v0++) {
        v2 = CommServerClient_GetServerBssDesc(v0);

        if (v2 != NULL) {
            v3 = (WirelessGameInfo *)&v2->gameInfo.userGameInfo;
            v4 = (EasyChatSentence *)&v3->unk_08;

            if (UnionRoomChat_IsNewSentence(param0, v4, v3->unk_00)) {
                UnionRoomChat_AddMessage(param0, CommServerClient_GetServerTrainerInfo(v0), v4, v3->unk_00);
            }
        }
    }

    if ((v4 = UnionRoom_TakeEasyChatSentence(param0->unionRoom)) != NULL) {
        u32 v7 = TrainerInfo_ID(param0->trainerInfo);
        UnionRoomChat_AddMessage(param0, param0->trainerInfo, v4, v7);
    }
}

static void UnionRoomChat_MarkRowsDirty(UnionRoomChat *param0)
{
    param0->rowsDirty = 1;
}

static void UnionRoomChat_InitTouchRepeat(UnionRoomChat *param0)
{
    param0->touchRepeatActive = 0;
    param0->touchRepeatDelay = 8;
    param0->touchRepeatInterval = 4;
    param0->touchRepeatCounter = param0->touchRepeatDelay;
}

static void UnionRoomChat_UpdateTouchRepeat(UnionRoomChat *param0)
{
    param0->touchRepeatActive = 0;

    if (gSystem.touchPressed) {
        param0->touchRepeatActive = 1;
    } else {
        if (gSystem.touchHeld) {
            param0->touchRepeatCounter--;

            if (param0->touchRepeatCounter < 0) {
                param0->touchRepeatActive = 1;
                param0->touchRepeatCounter = param0->touchRepeatInterval;
            }
        } else {
            param0->touchRepeatCounter = param0->touchRepeatDelay;
        }
    }
}

static BOOL UnionRoomChat_IsTouchRepeating(const UnionRoomChat *param0)
{
    return param0->touchRepeatActive;
}

static void UnionRoomChat_SetScrollbarDragging(UnionRoomChat *param0, BOOL param1)
{
    param0->scrollbarDragging = param1;
}

static BOOL UnionRoomChat_IsScrollbarDragging(const UnionRoomChat *param0)
{
    return param0->scrollbarDragging;
}

static void UnionRoomChat_SetArrowAnim(UnionRoomChat *param0, int param1)
{
    u16 v0;
    u16 v1;

    v0 = Sprite_GetAnimFrame(param0->sprites[param1]);
    v1 = Sprite_GetActiveAnim(param0->sprites[param1]);

    if ((v0 > 1) || (v1 != param1 + 4)) {
        Sprite_SetAnim(param0->sprites[param1], param1 + 4);
    }

    param0->arrowPressed[param1] = 1;
}

static void UnionRoomChat_UpdateArrowAnims(UnionRoomChat *param0)
{
    int v0;
    u16 v1;

    for (v0 = 0; v0 < 2; v0++) {
        v1 = Sprite_GetAnimFrame(param0->sprites[v0]);

        if (param0->arrowPressed[v0] == 1) {
            if (v1 >= 1) {
                Sprite_SetAnimateFlag(param0->sprites[v0], 0);
            }

            param0->arrowPressed[v0] = 0;
        } else {
            if (Sprite_GetAnimateFlag(param0->sprites[v0]) == 0) {
                Sprite_SetAnimateFlag(param0->sprites[v0], 1);
                Sprite_SetAnimFrame(param0->sprites[v0], 1 + 1);
            }
        }
    }
}
