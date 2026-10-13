#include "applications/easy_chat/page_buttons.h"

#include <nitro.h>
#include <string.h>

#include "constants/heap.h"

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/word_list_screen.h"
#include "applications/easy_chat/struct_easy_chat_word_list_screen_decl.h"

#include "bg_window.h"
#include "easy_chat_word_list.h"
#include "font.h"
#include "graphics.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "sprite.h"
#include "string_gf.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "text.h"

typedef struct {
    void *cellBankData;
    NNSG2dCellDataBank *cellBank;
    void *animBankData;
    NNSG2dAnimBankData *animBank;
} EasyChatPageButtonsResources;

typedef struct EasyChatPageButtons_t {
    EasyChatWordListScreen *wordListScreen;
    const EasyChatApp *easyChatApp;
    const EasyChatWordList *wordList;
    BgConfig *bgConfig;
    SpriteList *spriteList;
    Sprite *upButtonSprite;
    Sprite *downButtonSprite;
    EasyChatPageButtonsResources resources;
    u16 tilemaps[8][77];
    SysTask *transitionTask;
} EasyChatPageButtons;

typedef struct {
    EasyChatPageButtons *pageButtons;
    int state;
    u16 timer;
    u16 tilemapIndex;
    u16 endTilemap;
    u16 x;
    u16 y;
    u16 secondTilemap;
    u16 secondX;
    u16 secondY;
} EasyChatPageButtonsTransition;

static void EasyChatPageButtons_LoadScreenData(EasyChatPageButtons *param0, NARC *param1);
static void EasyChatPageButtons_LoadLabels(EasyChatPageButtons *param0, NARC *param1);
static void EasyChatPageButtons_PrintLabel(Window *param0, BgConfig *param1, const String *param2, int param3);
static void EasyChatPageButtons_CreateSprites(EasyChatPageButtons *param0, NARC *param1);
static void EasyChatPageButtons_DeleteSprites(EasyChatPageButtons *param0);
static void EasyChatPageButtons_LoadSpriteResources(EasyChatPageButtonsResources *param0, NARC *param1, u32 param2, u32 param3);
static void EasyChatPageButtons_FreeSpriteResources(EasyChatPageButtonsResources *param0);
static void EasyChatPageButtons_TransitionTask(SysTask *param0, void *param1);
static Sprite *EasyChatPageButtons_AddSprite(EasyChatPageButtons *param0, NNSG2dImageProxy *param1, NNSG2dImagePaletteProxy *param2, EasyChatPageButtonsResources *param3, int param4, int param5, int param6, int param7);

EasyChatPageButtons *EasyChatPageButtons_New(EasyChatWordListScreen *param0, const EasyChatApp *param1, const EasyChatWordList *param2)
{
    EasyChatPageButtons *v0 = Heap_Alloc(HEAP_ID_35, sizeof(EasyChatPageButtons));

    v0->wordListScreen = param0;
    v0->easyChatApp = param1;
    v0->wordList = param2;
    v0->bgConfig = EasyChatWordListScreen_GetBgConfig(param0);
    v0->spriteList = EasyChatWordListScreen_GetSpriteList(param0);
    v0->upButtonSprite = NULL;
    v0->downButtonSprite = NULL;
    v0->transitionTask = NULL;

    return v0;
}

void EasyChatPageButtons_Free(EasyChatPageButtons *param0)
{
    EasyChatPageButtons_DeleteSprites(param0);
    Heap_Free(param0);
}

void EasyChatPageButtons_LoadGraphics(EasyChatPageButtons *param0, NARC *param1)
{
    Graphics_LoadPaletteFromOpenNARC(param1, 21, 4, 0, 0x40, HEAP_ID_35);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 11, param0->bgConfig, 4, 0, 0, 1, HEAP_ID_35);

    EasyChatPageButtons_LoadScreenData(param0, param1);
    EasyChatPageButtons_LoadLabels(param0, param1);

    if (EasyChat_GetMode(param0->easyChatApp) == 0) {
        Bg_CopyToTilemapRect(param0->bgConfig, 4, 3, 3, 11, 7, param0->tilemaps[3], 0, 0, 11, 7);
        Bg_CopyToTilemapRect(param0->bgConfig, 4, 3, 14, 11, 7, param0->tilemaps[4], 0, 0, 11, 7);
    } else {
        Bg_CopyToTilemapRect(param0->bgConfig, 4, 3, 3, 11, 7, param0->tilemaps[0], 0, 0, 11, 7);
        Bg_CopyToTilemapRect(param0->bgConfig, 4, 3, 14, 11, 7, param0->tilemaps[7], 0, 0, 11, 7);
    }

    EasyChatPageButtons_CreateSprites(param0, param1);
    Bg_CopyTilemapBufferToVRAM(param0->bgConfig, 4);
}

static void EasyChatPageButtons_LoadScreenData(EasyChatPageButtons *param0, NARC *param1)
{
    static const u16 v0[] = {
        12,
        13,
        14,
        15,
        16,
        17,
        18,
        19,
    };
    int v1;
    void *v2;
    NNSG2dScreenData *v3;

    for (v1 = 0; v1 < NELEMS(v0); v1++) {
        v2 = Graphics_GetScrnDataFromOpenNARC(param1, v0[v1], 1, &v3, HEAP_ID_35);

        if (v2) {
            MI_CpuCopy16(v3->rawData, param0->tilemaps[v1], 77 * 2);
            DC_FlushRange(param0->tilemaps[v1], 77 * 2);
            Heap_Free(v2);
        }
    }
}

static void EasyChatPageButtons_LoadLabels(EasyChatPageButtons *param0, NARC *param1)
{
    String *v0, *v1;
    void *v2;
    NNSG2dCharacterData *v3;

    Font_InitManager(FONT_SUBSCREEN, HEAP_ID_SYSTEM);
    v0 = MessageBank_GetNewStringFromNARC(0x1A, 0x1B5, 0xB, 0x23);
    v1 = MessageBank_GetNewStringFromNARC(0x1A, 0x1B5, 0xC, 0x23);
    v2 = Graphics_GetCharDataFromOpenNARC(param1, 20, 1, &v3, 0x23);
    if (v2) {
        Window v4;

        Window_Init(&v4);
        v4.bgConfig = param0->bgConfig;
        v4.width = 11;
        v4.height = 57;
        v4.colorMode = 0;
        v4.pixels = v3->pRawData;
        EasyChatPageButtons_PrintLabel(&v4, param0->bgConfig, v0, 0);
        v4.pixels = (u8 *)(v3->pRawData) + (11 * 7 * 4 * 0x20);
        EasyChatPageButtons_PrintLabel(&v4, param0->bgConfig, v1, 0);
        DC_FlushRange(v3->pRawData, v3->szByte);
        Bg_LoadTiles(param0->bgConfig, 4, v3->pRawData, v3->szByte, 0);
        Heap_Free(v2);
    }

    String_Free(v1);
    String_Free(v0);
    Font_Free(FONT_SUBSCREEN);
}

static const s16 sEasyChatPageButtons_LabelYOffsets[] = {
    22,
    (22 + 56 * 1) - 1,
    (22 + 56 * 2) - 2,
    (22 + 56 * 3) - 1,
};

static void EasyChatPageButtons_PrintLabel(Window *param0, BgConfig *param1, const String *param2, int param3)
{
    int v0, v1, v2, v3;
    u32 v4;
    String *v5;

    v4 = String_NumLines(param2);
    v5 = String_Init(32, HEAP_ID_35);
    param3 += ((2 - v4) * 16) / 2;

    for (v1 = 0; v1 < v4; v1++) {
        String_CopyLineNum(v5, param2, v1);
        v2 = Font_CalcCenterAlignment(2, v5, 0, 88);
        for (v0 = 0; v0 < NELEMS(sEasyChatPageButtons_LabelYOffsets); v0++) {
            v3 = sEasyChatPageButtons_LabelYOffsets[v0] + param3;
            Text_AddPrinterWithParamsAndColor(param0, FONT_SUBSCREEN, v5, v2, v3, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 3), NULL);
        }
        param3 += 16;
    }
    String_Free(v5);
}

static void EasyChatPageButtons_CreateSprites(EasyChatPageButtons *param0, NARC *param1)
{
    NNSG2dImagePaletteProxy v0;
    NNSG2dImageProxy v1;

    NNS_G2dInitImagePaletteProxy(&v0);
    NNS_G2dInitImageProxy(&v1);

    Graphics_LoadPartialPaletteFromOpenNARC(param1, 25, NNS_G2D_VRAM_TYPE_2DSUB, 0, 35, &v0);
    Graphics_LoadImageMappingFromOpenNARC(param1, 24, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DSUB, 0, 35, &v1);

    EasyChatPageButtons_LoadSpriteResources(&(param0->resources), param1, 22, 23);

    param0->upButtonSprite = EasyChatPageButtons_AddSprite(param0, &v1, &v0, &param0->resources, 192, 56, 0, 0);
    Sprite_SetAnim(param0->upButtonSprite, 0);
    Sprite_SetDrawFlag(param0->upButtonSprite, FALSE);

    param0->downButtonSprite = EasyChatPageButtons_AddSprite(param0, &v1, &v0, &param0->resources, 192, 136, 0, 0);
    Sprite_SetAnim(param0->downButtonSprite, 2);
    Sprite_SetDrawFlag(param0->downButtonSprite, FALSE);
}

static void EasyChatPageButtons_DeleteSprites(EasyChatPageButtons *param0)
{
    if (param0->upButtonSprite) {
        Sprite_Delete(param0->upButtonSprite);
    }

    if (param0->downButtonSprite) {
        Sprite_Delete(param0->downButtonSprite);
    }

    EasyChatPageButtons_FreeSpriteResources(&param0->resources);
}

static void EasyChatPageButtons_LoadSpriteResources(EasyChatPageButtonsResources *param0, NARC *param1, u32 param2, u32 param3)
{
    param0->cellBankData = Graphics_GetCellBankFromOpenNARC(param1, param2, 1, &(param0->cellBank), HEAP_ID_35);
    param0->animBankData = Graphics_GetAnimBankFromOpenNARC(param1, param3, 1, &(param0->animBank), HEAP_ID_35);
}

static void EasyChatPageButtons_FreeSpriteResources(EasyChatPageButtonsResources *param0)
{
    Heap_Free(param0->cellBankData);
    Heap_Free(param0->animBankData);
}

static Sprite *EasyChatPageButtons_AddSprite(EasyChatPageButtons *param0, NNSG2dImageProxy *param1, NNSG2dImagePaletteProxy *param2, EasyChatPageButtonsResources *param3, int param4, int param5, int param6, int param7)
{
    SpriteResourcesHeader v0;
    SpriteListTemplate v1;
    Sprite *v2;

    v0.imageProxy = param1;
    v0.paletteProxy = param2;
    v0.cellBank = param3->cellBank;
    v0.cellAnimBank = param3->animBank;
    v0.priority = param6;
    v0.charData = NULL;
    v0.multiCellBank = NULL;
    v0.multiCellAnimBank = NULL;
    v0.isVRamTransfer = 0;

    v1.list = param0->spriteList;
    v1.resourceData = &v0;
    v1.position.x = param4 * FX32_ONE;
    v1.position.y = (param5 + 192) * FX32_ONE;
    v1.position.z = 0;
    v1.priority = param7;
    v1.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    v1.heapID = HEAP_ID_35;

    v2 = SpriteList_Add(&v1);

    if (v2) {
        Sprite_SetAnimateFlag(v2, 1);
        Sprite_SetAnimSpeed(v2, ((FX32_ONE * 2) / 2));
    }

    return v2;
}

void EasyChatPageButtons_StartTransition(EasyChatPageButtons *param0)
{
    EasyChatPageButtonsTransition *v0 = Heap_Alloc(HEAP_ID_35, sizeof(EasyChatPageButtonsTransition));

    if (v0) {
        static const struct {
            u16 startTilemap;
            u16 endTilemap;
            u16 x;
            u16 y;
            u16 secondTilemap;
            u16 secondX;
            u16 secondY;
        } v1[] = {
            { 0x1, 0x3, 0x3, 0x3, 0x4, 0x3, 0xE },
            { 0x5, 0x7, 0x3, 0xE, 0x0, 0x3, 0x3 }
        };
        int v2 = EasyChat_GetMode(param0->easyChatApp);

        v0->pageButtons = param0;
        v0->state = 0;
        v0->timer = 0;
        v0->tilemapIndex = v1[v2].startTilemap;
        v0->endTilemap = v1[v2].endTilemap;
        v0->x = v1[v2].x;
        v0->y = v1[v2].y;
        v0->secondTilemap = v1[v2].secondTilemap;
        v0->secondX = v1[v2].secondX;
        v0->secondY = v1[v2].secondY;

        param0->transitionTask = SysTask_Start(EasyChatPageButtons_TransitionTask, v0, 1);
    } else {
        param0->transitionTask = NULL;
    }
}

BOOL EasyChatPageButtons_IsTransitionDone(EasyChatPageButtons *param0)
{
    return param0->transitionTask == NULL;
}

static void EasyChatPageButtons_TransitionTask(SysTask *param0, void *param1)
{
    EasyChatPageButtonsTransition *v0 = param1;

    switch (v0->state) {
    case 0:
        Bg_CopyToTilemapRect(v0->pageButtons->bgConfig, 4, v0->x, v0->y, 11, 7, v0->pageButtons->tilemaps[v0->tilemapIndex], 0, 0, 11, 7);
        Bg_CopyToTilemapRect(v0->pageButtons->bgConfig, 4, v0->secondX, v0->secondY, 11, 7, v0->pageButtons->tilemaps[v0->secondTilemap], 0, 0, 11, 7);
        Bg_CopyTilemapBufferToVRAM(v0->pageButtons->bgConfig, 4);

        v0->tilemapIndex++;
        v0->state++;
        break;
    case 1:
        if (++(v0->timer) >= 2) {
            Bg_CopyToTilemapRect(v0->pageButtons->bgConfig, 4, v0->x, v0->y, 11, 7, v0->pageButtons->tilemaps[v0->tilemapIndex], 0, 0, 11, 7);
            Bg_CopyTilemapBufferToVRAM(v0->pageButtons->bgConfig, 4);

            v0->timer = 0;
            v0->tilemapIndex++;
            v0->state++;
        }
        break;
    case 2:
        if (++(v0->timer) >= 4) {
            Bg_CopyToTilemapRect(v0->pageButtons->bgConfig, 4, v0->x, v0->y, 11, 7, v0->pageButtons->tilemaps[v0->tilemapIndex], 0, 0, 11, 7);
            Bg_CopyTilemapBufferToVRAM(v0->pageButtons->bgConfig, 4);
            v0->state++;
        }
        break;
    case 3:
        v0->pageButtons->transitionTask = NULL;
        Heap_Free(param1);
        SysTask_Done(param0);
    }
}

void EasyChatPageButtons_SetVisible(EasyChatPageButtons *param0, BOOL param1)
{
    if (param1) {
        Sprite_SetDrawFlag(param0->upButtonSprite, EasyChat_IsWordSelectRowBelowFirst(param0->easyChatApp));
        Sprite_SetDrawFlag(param0->downButtonSprite, EasyChat_IsWordSelectRowAboveLast(param0->easyChatApp));
    } else {
        Sprite_SetDrawFlag(param0->upButtonSprite, FALSE);
        Sprite_SetDrawFlag(param0->downButtonSprite, FALSE);
    }
}

void EasyChatPageButtons_SetPressedState(EasyChatPageButtons *param0, int param1, int param2)
{
    switch (param1) {
    case 0:
        switch (param2) {
        case 1:
            Sprite_SetAnim(param0->upButtonSprite, 1);
            break;
        case 0:
            Sprite_SetAnim(param0->upButtonSprite, 0);
            break;
        }
        break;
    case 1:
        switch (param2) {
        case 1:
            Sprite_SetAnim(param0->downButtonSprite, 3);
            break;
        case 0:
            Sprite_SetAnim(param0->downButtonSprite, 2);
            break;
        }
        break;
    }
}
