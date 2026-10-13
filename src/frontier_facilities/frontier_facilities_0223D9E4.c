#include "frontier_facilities/frontier_facilities_0223D9E4.h"

#include <nitro.h>
#include <string.h>

#include "bg_window.h"
#include "enums.h"
#include "graphics.h"
#include "heap.h"
#include "narc.h"
#include "palette.h"
#include "sys_task.h"
#include "sys_task_manager.h"

#include "res/graphics/frontier/backgrounds/frontier_backgrounds.naix"

typedef struct {
    SysTask *task;
    BgConfig *bgConfig;
    u16 tilemaps[2][2048];
    u8 tiles[2][65536];
    u8 timer;
    u8 tileIndex;
} FrontierFacilitiesBattleHallBackground;

typedef struct {
    SysTask *task;
    PaletteData *plttData;
    u16 palettes[3][16];
    u8 paletteIndex;
    u8 timer;
} FrontierFacilitiesBattleHallPalette;

typedef struct {
    SysTask *unk_00;
    SysTask *unk_04;
    BgConfig *unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    u8 unk_18;
    u8 unk_19;
    u8 unk_1A;
} FrontierFacilitiesBattleHallSub1;

typedef struct FrontierFacilitiesBattleHallBattleRoom_t {
    FrontierFacilitiesBattleHallBackground *background;
    FrontierFacilitiesBattleHallPalette *palette;
    FrontierFacilitiesBattleHallSub1 *sub1;
} FrontierFacilitiesBattleHallBattleRoom;

static FrontierFacilitiesBattleHallBackground *FrontierFacilities_NewBattleHallBackground(BgConfig *param0);
static void FrontierFacilities_FreeBattleHallBackground(FrontierFacilitiesBattleHallBackground *param0);
static void FrontierFacilities_BattleHallBackgroundTask(SysTask *param0, void *param1);
static FrontierFacilitiesBattleHallPalette *FrontierFacilities_NewBattleHallPalette(PaletteData *param0);
static void FrontierFacilities_FreeBattleHallPalette(FrontierFacilitiesBattleHallPalette *param0);
static void FrontierFacilities_BattleHallPaletteTask(SysTask *param0, void *param1);

static const u16 sBattleHallBattleRoomTilemaps[] = {
    battle_hall_battle_room_NSCR_lz,
    battle_hall_battle_room_dupe_NSCR_lz
};

FrontierFacilitiesBattleHallBattleRoom *FrontierFacilities_NewBattleHallBattleRoom(BgConfig *param0, PaletteData *param1)
{
    FrontierFacilitiesBattleHallBattleRoom *v0 = Heap_Alloc(HEAP_ID_94, sizeof(FrontierFacilitiesBattleHallBattleRoom));
    MI_CpuClear8(v0, sizeof(FrontierFacilitiesBattleHallBattleRoom));

    v0->background = FrontierFacilities_NewBattleHallBackground(param0);
    v0->palette = FrontierFacilities_NewBattleHallPalette(param1);

    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_BGALL | GX_BLEND_PLANEMASK_OBJ, 8, 9);

    return v0;
}

void FrontierFacilities_FreeBattleHallBattleRoom(FrontierFacilitiesBattleHallBattleRoom *param0)
{
    FrontierFacilities_FreeBattleHallBackground(param0->background);
    FrontierFacilities_FreeBattleHallPalette(param0->palette);
    Heap_Free(param0);
}

static FrontierFacilitiesBattleHallBackground *FrontierFacilities_NewBattleHallBackground(BgConfig *param0)
{
    FrontierFacilitiesBattleHallBackground *v0;

    GF_ASSERT(2 == NELEMS(sBattleHallBattleRoomTilemaps));

    v0 = Heap_Alloc(HEAP_ID_94, sizeof(FrontierFacilitiesBattleHallBackground));
    MI_CpuClear8(v0, sizeof(FrontierFacilitiesBattleHallBackground));
    v0->bgConfig = param0;

    {
        NARC *v1;
        void *v2;
        NNSG2dScreenData *v3;
        int v4;

        v1 = NARC_ctor(NARC_INDEX_FRONTIER_BACKGROUNDS, HEAP_ID_94);

        for (v4 = 0; v4 < 2; v4++) {
            v2 = Graphics_GetScrnDataFromOpenNARC(v1, sBattleHallBattleRoomTilemaps[v4], 1, &v3, HEAP_ID_94);
            MI_CpuCopy32(v3->rawData, v0->tilemaps[v4], 0x1000);
            Heap_Free(v2);
        }

        NARC_dtor(v1);
    }

    {
        NARC *v5;
        void *v6;
        NNSG2dCharacterData *v7;

        v5 = NARC_ctor(NARC_INDEX_FRONTIER_BACKGROUNDS, HEAP_ID_94);

        v6 = Graphics_GetCharDataFromOpenNARC(v5, battle_hall_battle_room_NCGR_lz, 1, &v7, HEAP_ID_94);
        MI_CpuCopy32(v7->pRawData, v0->tiles[0], v7->szByte);

        Heap_Free(v6);

        v6 = Graphics_GetCharDataFromOpenNARC(v5, battle_hall_battle_room_2_NCGR_lz, 1, &v7, HEAP_ID_94);
        MI_CpuCopy32(v7->pRawData, v0->tiles[1], v7->szByte);

        Heap_Free(v6);
        NARC_dtor(v5);
    }

    v0->task = SysTask_Start(FrontierFacilities_BattleHallBackgroundTask, v0, 80000 - 500);

    return v0;
}

static void FrontierFacilities_FreeBattleHallBackground(FrontierFacilitiesBattleHallBackground *param0)
{
    SysTask_Done(param0->task);
    Heap_Free(param0);
}

static void FrontierFacilities_BattleHallBackgroundTask(SysTask *param0, void *param1)
{
    u32 v0;
    FrontierFacilitiesBattleHallBackground *v1 = param1;

    if (v1->timer < 12) {
        v1->timer++;
        return;
    }

    v1->timer = 0;

    {
        Bg_LoadTiles(v1->bgConfig, 3, v1->tiles[v1->tileIndex], 0x10000, 0);
    }

    Bg_LoadTilemapBuffer(v1->bgConfig, 3, v1->tilemaps[v1->tileIndex], 0x1000);
    Bg_ScheduleTilemapTransfer(v1->bgConfig, 3);

    v1->tileIndex ^= 1;
}

static FrontierFacilitiesBattleHallPalette *FrontierFacilities_NewBattleHallPalette(PaletteData *param0)
{
    FrontierFacilitiesBattleHallPalette *v0 = Heap_Alloc(HEAP_ID_94, sizeof(FrontierFacilitiesBattleHallPalette));
    MI_CpuClear8(v0, sizeof(FrontierFacilitiesBattleHallPalette));

    v0->plttData = param0;
    v0->paletteIndex = 2;

    {
        u16 *v1;

        v1 = PaletteData_GetUnfadedBuffer(param0, 0);
        MI_CpuCopy16(&v1[16 * 5], v0->palettes, 3 * 16 * sizeof(u16));
    }

    v0->task = SysTask_Start(FrontierFacilities_BattleHallPaletteTask, v0, (80000 - 500) + 1);

    return v0;
}

static void FrontierFacilities_FreeBattleHallPalette(FrontierFacilitiesBattleHallPalette *param0)
{
    SysTask_Done(param0->task);
    Heap_Free(param0);
}

static void FrontierFacilities_BattleHallPaletteTask(SysTask *param0, void *param1)
{
    FrontierFacilitiesBattleHallPalette *v0 = param1;

    if (v0->timer < 8) {
        v0->timer++;
        return;
    }

    v0->timer = 0;
    PaletteData_LoadBuffer(v0->plttData, v0->palettes[v0->paletteIndex], 0, PLTT_DEST(6), PALETTE_SIZE_BYTES);
    v0->paletteIndex++;

    if (v0->paletteIndex >= 3) {
        v0->paletteIndex = 0;
    }
}
