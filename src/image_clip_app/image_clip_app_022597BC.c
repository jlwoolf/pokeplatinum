#include "image_clip_app/image_clip_app_022597BC.h"

#include <nitro.h>
#include <string.h>

#include "constants/narc.h"

#include "image_clip_app/struct_image_clip_app_022597BC.h"
#include "image_clip_app/struct_image_clip_app_02259820.h"
#include "image_clip_app/struct_image_clip_app_022599A0.h"
#include "image_clip_app/struct_image_clip_app_0225AF44.h"

#include "bg_window.h"
#include "graphics.h"
#include "heap.h"
#include "sys_task.h"
#include "sys_task_extensions.h"
#include "sys_task_manager.h"

typedef struct {
    ImageClipBg *bg;
    ImageClipBgTemplate template;
    BOOL *doneFlag;
    int remainingFrames;
    int scrollXStep;
    int scrollYStep;
    int startX;
    int startY;
} ImageClipBgScrollTask;

typedef struct {
    BgConfig *bgConfig;
    NNSG2dCharacterData *charData;
    void *allocatedData;
    int destTileOffset;
    int size;
} ImageClipBgCharLoadTask;

typedef struct {
    NNSG2dPaletteData *paletteData;
    void *allocatedData;
    int vramType;
    int offset;
    int size;
} ImageClipBgPaletteLoadTask;

static void ImageClipBg_AddTilePaletteOffset(const NNSG2dScreenData *param0, int param1);
static void ImageClipBg_LoadData(ImageClipBgTemplate *param0, int *param1, int *param2);
static void ImageClipBg_ScrollTask(SysTask *param0, void *param1);
static void ImageClipBg_BlitTilemap(BgConfig *param0, int param1, const NNSG2dScreenData *param2, int param3, int param4, int param5, int param6, int param7, int param8);
static void ImageClipBg_QueueCharLoad(enum NarcID narcID, u32 param1, BgConfig *param2, u32 param3, u32 param4, enum HeapID heapID);
static void ImageClipBg_QueuePaletteLoad(enum NarcID narcID, u32 param1, int param2, u32 param3, u32 param4, enum HeapID heapID);
static void ImageClipBg_LoadCharsAfterVBlank(SysTask *param0, void *param1);
static void ImageClipBg_LoadPaletteAfterVBlank(SysTask *param0, void *param1);

void ImageClipBg_Init(ImageClipBg *param0, ImageClipBgTemplate *param1)
{
    param0->bgConfig = param1->bgConfig;
    param0->destTileX = param1->destTilemapX / 8;
    param0->destTileY = param1->destTilemapY / 8;
    param0->bgLayer = param1->bgLayer;
    param0->paletteOffset = param1->paletteOffset;
    param0->paletteSize = param1->paletteSize;
    param0->charOffset = param1->charOffset;
    param0->narcID = param1->narcID;
    param0->secondFrameIndex = param1->tilemapMember;

    ImageClipBg_LoadData(param1, &param0->widthTiles, &param0->heightTiles);
}

void ImageClipBg_Free(ImageClipBg *param0)
{
    Bg_ClearTilemap(param0->bgConfig, param0->bgLayer);
    memset(param0, 0, sizeof(ImageClipBg));
}

void ImageClipBg_InitBackgroundAnimation(ImageClipBgAnimation *param0, PhotoRendererBgTemplate *param1)
{
    param0->bg = param1->bg;
    param0->firstFrameIndex = param1->firstFrameIndex;
    param0->frameDuration = param1->frameDuration;
    param0->frameTimer = 0;
    param0->alternateFrame = 0;
    param0->heapID = param1->heapID;
}

void ImageClipBg_UpdateBackgroundAnimation(ImageClipBgAnimation *param0, int param1)
{
    NNSG2dScreenData *v0;
    void *v1;
    int v2;

    param0->frameTimer += param1;

    if (param0->frameTimer > param0->frameDuration) {
        param0->frameTimer = 0;

        if (param0->alternateFrame == 0) {
            v2 = param0->firstFrameIndex;
            param0->alternateFrame = 1;
        } else {
            v2 = param0->bg->secondFrameIndex;
            param0->alternateFrame = 0;
        }

        v1 = Graphics_GetScrnData(param0->bg->narcID, v2, 0, &v0, param0->heapID);

        ImageClipBg_BlitTilemap(param0->bg->bgConfig, param0->bg->bgLayer, v0, param0->bg->widthTiles, param0->bg->heightTiles, param0->bg->destTileX, param0->bg->destTileY, param0->bg->charOffset, param0->bg->paletteOffset);
        Heap_Free(v1);
    }
}

void ImageClipBg_StopBackgroundAnimation(ImageClipBgAnimation *param0)
{
    NNSG2dScreenData *v0;
    void *v1 = Graphics_GetScrnData(param0->bg->narcID, param0->bg->secondFrameIndex, 0, &v0, param0->heapID);

    ImageClipBg_BlitTilemap(param0->bg->bgConfig, param0->bg->bgLayer, v0, param0->bg->widthTiles, param0->bg->heightTiles, param0->bg->destTileX, param0->bg->destTileY, param0->bg->charOffset, param0->bg->paletteOffset);
    Heap_Free(v1);

    memset(param0, 0, sizeof(ImageClipBgAnimation));
}

void ImageClipBg_StartScroll(ImageClipBg *param0, ImageClipBgTemplate *param1, int param2, int param3, int param4, BOOL *param5)
{
    SysTask *v1 = SysTask_StartAndAllocateParam(ImageClipBg_ScrollTask, sizeof(ImageClipBgScrollTask), 0, 13);
    ImageClipBgScrollTask *v0 = SysTask_GetParam(v1);

    v0->bg = param0;
    v0->template = *param1;
    v0->doneFlag = param5;
    v0->remainingFrames = param4;
    v0->scrollXStep = param2 / param4;
    v0->scrollYStep = param3 / param4;
    v0->startX = Bg_GetXOffset(param0->bgConfig, param0->bgLayer);
    v0->startY = Bg_GetYOffset(param0->bgConfig, param0->bgLayer);

    param1->charOffset = 128;
    param1->paletteOffset = 0x5;
    param1->destTilemapX -= param2;
    param1->destTilemapY -= param3;
    param1->heapID = HEAP_ID_14;

    ImageClipBg_LoadData(param1, NULL, NULL);
}

static void ImageClipBg_AddTilePaletteOffset(const NNSG2dScreenData *param0, int param1)
{
    int v0;
    u16 *v1;
    int v2 = param0->szByte / 2;

    v1 = (u16 *)param0->rawData;

    for (v0 = 0; v0 < v2; v0++) {
        v1[v0] += param1;
    }
}

static void ImageClipBg_LoadData(ImageClipBgTemplate *param0, int *param1, int *param2)
{
    int v0;
    NNSG2dScreenData *v1;
    void *v2;
    int v3, v4;
    int v5 = param0->destTilemapX / 8;
    int v6 = param0->destTilemapY / 8;

    ImageClipBg_QueueCharLoad(param0->narcID, param0->charMember, param0->bgConfig, param0->bgLayer, param0->charOffset, param0->heapID);

    if (param0->bgLayer < 4) {
        v0 = 0;
    } else {
        v0 = 4;
    }

    ImageClipBg_QueuePaletteLoad(param0->narcID, param0->paletteMember, v0, param0->paletteOffset * 32, param0->paletteSize * 32, param0->heapID);

    v2 = Graphics_GetScrnData(param0->narcID, param0->tilemapMember, 0, &v1, param0->heapID);
    v4 = v1->screenWidth / 8;
    v3 = v1->screenHeight / 8;

    ImageClipBg_BlitTilemap(param0->bgConfig, param0->bgLayer, v1, v4, v3, v5, v6, param0->charOffset, param0->paletteOffset);
    Heap_Free(v2);

    if (param1) {
        *param1 = v4;
    }

    if (param2) {
        *param2 = v3;
    }
}

static void ImageClipBg_ScrollTask(SysTask *param0, void *param1)
{
    ImageClipBgScrollTask *v0 = param1;

    v0->remainingFrames--;

    if (v0->remainingFrames >= 0) {
        Bg_ScheduleScroll(v0->bg->bgConfig, v0->bg->bgLayer, 2, v0->scrollXStep);
        Bg_ScheduleScroll(v0->bg->bgConfig, v0->bg->bgLayer, 5, v0->scrollYStep);
    } else {
        Bg_ScheduleScroll(v0->bg->bgConfig, v0->bg->bgLayer, 0, v0->startX);
        Bg_ScheduleScroll(v0->bg->bgConfig, v0->bg->bgLayer, 3, v0->startY);
        ImageClipBg_Init(v0->bg, &v0->template);

        if (v0->doneFlag) {
            *v0->doneFlag = 1;
        }

        SysTask_FinishAndFreeParam(param0);
    }
}

static void ImageClipBg_BlitTilemap(BgConfig *param0, int param1, const NNSG2dScreenData *param2, int param3, int param4, int param5, int param6, int param7, int param8)
{
    ImageClipBg_AddTilePaletteOffset(param2, param7);
    Bg_CopyToTilemapRect(param0, param1, param5, param6, param3, param4, param2->rawData, 0, 0, param3, param4);
    Bg_ChangeTilemapRectPalette(param0, param1, param5, param6, param3, param4, param8);
    Bg_ScheduleTilemapTransfer(param0, param1);
}

static void ImageClipBg_QueueCharLoad(enum NarcID narcID, u32 param1, BgConfig *param2, u32 param3, u32 param4, enum HeapID heapID)
{
    ImageClipBgCharLoadTask *v0 = Heap_Alloc(heapID, sizeof(ImageClipBgCharLoadTask));
    memset(v0, 0, sizeof(ImageClipBgCharLoadTask));

    v0->allocatedData = Graphics_GetCharData(narcID, param1, 0, &v0->charData, heapID);
    v0->bgConfig = param2;
    v0->destTileOffset = param3;
    v0->size = param4;

    SysTask_ExecuteAfterVBlank(ImageClipBg_LoadCharsAfterVBlank, v0, 128);
}

static void ImageClipBg_QueuePaletteLoad(enum NarcID narcID, u32 param1, int param2, u32 param3, u32 param4, enum HeapID heapID)
{
    ImageClipBgPaletteLoadTask *v0 = Heap_Alloc(heapID, sizeof(ImageClipBgPaletteLoadTask));
    memset(v0, 0, sizeof(ImageClipBgPaletteLoadTask));

    v0->allocatedData = Graphics_GetPlttData(narcID, param1, &v0->paletteData, heapID);
    v0->vramType = param2;
    v0->offset = param3;
    v0->size = param4;

    SysTask_ExecuteAfterVBlank(ImageClipBg_LoadPaletteAfterVBlank, v0, 128);
}

static void ImageClipBg_LoadCharsAfterVBlank(SysTask *param0, void *param1)
{
    ImageClipBgCharLoadTask *v0 = param1;

    DC_FlushRange(v0->charData->pRawData, v0->charData->szByte);

    Bg_LoadTiles(v0->bgConfig, v0->destTileOffset, v0->charData->pRawData, v0->charData->szByte, v0->size);
    SysTask_Done(param0);
    Heap_Free(v0->allocatedData);
    Heap_Free(v0);
}

static void ImageClipBg_LoadPaletteAfterVBlank(SysTask *param0, void *param1)
{
    ImageClipBgPaletteLoadTask *v0 = param1;

    DC_FlushRange(v0->paletteData->pRawData, v0->size);

    if (v0->vramType == 0) {
        GX_LoadBGPltt(v0->paletteData->pRawData, v0->offset, v0->size);
    } else if (v0->vramType == 4) {
        GXS_LoadBGPltt(v0->paletteData->pRawData, v0->offset, v0->size);
    }

    SysTask_Done(param0);
    Heap_Free(v0->allocatedData);
    Heap_Free(v0);
}
