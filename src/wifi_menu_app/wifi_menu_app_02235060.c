#include "wifi_menu_app/wifi_menu_app_02235060.h"

#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/wifi_2d_char_0222BCE8.h"
#include "wifi_2d_char/wifi_2d_char_0222BE18.h"
#include "wifi_2d_char/wifi_2d_char_0222CA88.h"
#include "wifi_2d_char/wifi_2d_char_0222CCE4.h"
#include "wifi_2d_char/wifi_2d_char_0222D160.h"
#include "wifi_2d_char/wifi_2d_char_0222D1C0.h"
#include "wifi_2d_char/wifi_2d_char_0222D77C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CCB8.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D894.h"
#include "wifi_menu_app/wifi_menu_app_02236474.h"
#include "wifi_menu_app/struct_wifi_menu_app_02235130.h"
#include "wifi_menu_app/struct_wifi_menu_app_022354D8.h"
#include "wifi_menu_app/struct_wifi_menu_app_0223582C.h"
#include "wifi_menu_app/struct_wifi_menu_app_022358CC.h"
#include "wifi_menu_app/struct_wifi_menu_app_02236318.h"
#include "wifi_menu_app/struct_wifi_menu_app_022376D0.h"

#include "bg_window.h"
#include "graphics.h"
#include "heap.h"
#include "math_util.h"
#include "narc.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "system.h"
#include "vram_transfer.h"

#define MCR_PCANM_DESTPL(x) ((7 * 32) + (((x) + 1) * 2))

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} WiFiMenuAppBoardPaletteAnimStep;

typedef struct {
    s16 unk_00;
    s16 unk_02;
} WiFiMenuAppBoardPosition;

static void WiFiMenuAppBoard_FreeActors(WiFiMenuAppBoard *param0);
static BOOL WiFiMenuAppBoard_IsPlayerReady(const WiFiMenuAppBoard *param0);
static BOOL WiFiMenuAppBoard_IsFacingPaletteTile(const WiFiMenuAppBoard *param0);
static void WiFiMenuAppBoard_ProcessActorEvents(WiFiMenuAppBoard *param0);
static void WiFiMenuAppBoard_UpdateActors(WiFiMenuAppBoard *param0);
static void WiFiMenuAppBoard_DrawActors(WiFiMenuAppBoard *param0);
static const WiFiMenuAppActor *WiFiMenuAppBoard_FindAdjacentActor(const WiFiMenuAppBoard *param0, const WiFiMenuAppActor *param1, int param2);
static void WiFiMenuAppBoard_CreateRenderer(WiFiMenuAppBoard *param0, u32 param1, enum HeapID heapID);
static void WiFiMenuAppBoard_FreeRenderer(WiFiMenuAppBoard *param0);
static void WiFiMenuAppBoard_CreateBackground(WiFiMenuAppBoard *param0, enum HeapID heapID, NARC *param2, u32 param3);
static void WiFiMenuAppBoard_FreeBackground(WiFiMenuAppBoard *param0);
static void WiFiMenuAppBoard_InitSpriteManager(WiFiMenuAppSpriteManager *param0, enum HeapID heapID, NARC *param2);
static void WiFiMenuAppBoard_FreeSpriteManager(WiFiMenuAppSpriteManager *param0);
static void WiFiMenuAppBoard_LoadSpriteResources(WiFiMenuAppSpriteManager *param0, u32 param1, NARC *param2);
static void WiFiMenuAppBoard_UnloadSpriteResources(WiFiMenuAppSpriteManager *param0);
static void WiFiMenuAppBoard_AddSprites(WiFiMenuAppSpriteManager *param0, u32 param1);
static void WiFiMenuAppBoard_DeleteSprites(WiFiMenuAppSpriteManager *param0);
static void WiFiMenuAppBoard_InitBgConfig(BgConfig *param0, u32 param1);
static void WiFiMenuAppBoard_FreeBgConfig(BgConfig *param0);
static void WiFiMenuAppBoard_LoadBgGraphics(BgConfig *param0, u32 param1, NARC *param2);
static BOOL WiFiMenuAppBoard_IsPlayerAtExit(WiFiMenuAppBoard *param0);
static void WiFiMenuAppBoard_LoadSpriteResourceData(WiFiMenuAppSpriteManager *param0, u32 param1, NARC *param2);
static void WiFiMenuAppBoard_RemoveSpriteResourceData(WiFiMenuAppSpriteManager *param0);
static void WiFiMenuAppBoard_CreateSprites(WiFiMenuAppSpriteManager *param0, u32 param1);
static void WiFiMenuAppBoard_DestroySprites(WiFiMenuAppSpriteManager *param0);
static void WiFiMenuAppBoard_ShowExitCursor(WiFiMenuAppBoard *param0);
static void WiFiMenuAppBoard_HideExitCursor(WiFiMenuAppBoard *param0);
static void WiFiMenuAppBoard_ShowActorCursor(WiFiMenuAppBoard *param0, WiFi2DCharPosition param1, u32 param2);
static void WiFiMenuAppBoard_HideActorCursor(WiFiMenuAppBoard *param0);
static void WiFiMenuAppBoard_FindActorSpawnTile(WiFiMenuAppBoard *param0, WiFiMenuAppBoardPosition *param1, u32 param2);
static void WiFiMenuAppBoard_FindSpawnTile(WiFiMenuAppBoard *param0, WiFiMenuAppBoardPosition *param1);
static WiFiMenuAppActor *WiFiMenuAppBoard_AllocActor(WiFiMenuAppBoard *param0);
static void WiFiMenuAppBoard_AddActorRenderObject(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1, BOOL param2);
static void WiFiMenuAppBoard_AddActorToObjectManager(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1, const WiFiMenuAppBoardPosition *param2, u32 param3, u16 param4, u8 param5, int param6);
static BOOL WiFiMenuAppBoard_IsActorIdle(const WiFiMenuAppActor *param0);
static void WiFiMenuAppBoard_SetActorIdle(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static void WiFiMenuAppBoard_SetActorSpawning(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static void WiFiMenuAppBoard_SetActorWander(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static void WiFiMenuAppBoard_SetActorJump(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static void WiFiMenuAppBoard_DrawActorDefault(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static void WiFiMenuAppBoard_DrawActorShadow(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static void WiFiMenuAppBoard_DrawActorJump(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static BOOL WiFiMenuAppBoard_UpdatePlayerActor(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static BOOL WiFiMenuAppBoard_UpdateActorSpawning(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static BOOL WiFiMenuAppBoard_UpdateActorRemoving(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static BOOL WiFiMenuAppBoard_UpdateActorWander(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static BOOL WiFiMenuAppBoard_UpdateActorJump(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static BOOL WiFiMenuAppBoard_UpdateActorPaused(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
static void WiFiMenuAppBoard_PushMoveEvent(WiFiMenuAppBoard *param0, s32 param1, s32 param2, s32 param3);
static void WiFiMenuAppBoard_PushActorMoveEvent(WiFiMenuAppBoard *param0, s32 param1, const WiFiMenuAppActor *param2);
static BOOL WiFiMenuAppBoard_IsActorTransitioning(const WiFiMenuAppActor *param0);
static void WiFiMenuAppBoard_ApplyActorState(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1, int param2);
static void WiFiMenuAppBoard_InitPalette(WiFiMenuAppBoard *param0, WiFiMenuAppPalette *param1, NARC *param2);
static void WiFiMenuAppBoard_FreePalette(WiFiMenuAppBoard *param0, WiFiMenuAppPalette *param1);
static void WiFiMenuAppBoard_AdvancePalette(WiFiMenuAppBoard *param0, WiFiMenuAppPalette *param1);
static void WiFiMenuAppBoard_UpdatePaletteAnim(WiFiMenuAppPalette *param0);
static void WiFiMenuAppBoard_UpdatePaletteFlash(WiFiMenuAppPalette *param0);
static void *WiFiMenuAppBoard_GetPaletteEntry(WiFiMenuAppPalette *param0, u32 param1);
static void WiFiMenuAppBoard_ResetPaletteFlash(WiFiMenuAppPalette *param0);
static void WiFiMenuAppBoard_RequestPaletteFlash(WiFiMenuAppPalette *param0);
static void WiFiMenuAppBoard_StartPaletteFlash(WiFiMenuAppPalette *param0, u8 param1);
static void WiFiMenuAppBoard_CancelPaletteFlash(WiFiMenuAppPalette *param0);

static const WiFiMenuAppBoardPaletteAnimStep sWiFiMenuAppBoardPaletteAnimSteps[8] = {
    { 0x0, 0x0, 0x0, 0x1 },
    { 0x1, 0x2, 0x1, 0x0 },
    { 0x1, 0x4, 0x1, 0x1 },
    { 0x1, 0x2, 0x1, 0x0 },
    { 0x0, 0x0, 0x0, 0x1 },
    { 0x1, 0x2, 0x1, 0x1 },
    { 0x1, 0x4, 0x1, 0x0 },
    { 0x1, 0x3, 0x1, 0x1 }
};

static const u16 sWiFiMenuAppBoardPaletteFrameDurations[2] = {
    0x3,
    0x2
};

void WiFiMenuAppBoard_Init(WiFiMenuAppBoard *param0, enum HeapID heapID, NARC *param2, BgConfig *param3, u32 param4, u32 param5)
{
    WiFi2DCharPosition v0;
    u32 v1;

    memset(param0, 0, sizeof(WiFiMenuAppBoard));

    v1 = (param5 - 1) / 8;

    param0->heapID = heapID;
    param0->unk_10 = param3;

    WiFiMenuAppBoard_InitSpriteManager(&param0->unk_14, param0->heapID, param2);
    WiFiMenuAppBoard_InitBgConfig(param0->unk_10, heapID);

    v0 = WiFiMenuAppBoard_GetMapGridSize(v1);
    param0->unk_748 = WiFi2DCharGrid_New(v0.x, v0.y, heapID);
    WiFi2DCharGrid_SetTiles(param0->unk_748, WiFiMenuAppBoard_GetMapTiles(v1));
    param0->unk_74C = WiFi2DCharObjectManager_New(48, heapID);

    WiFiMenuAppBoard_CreateRenderer(param0, param4, heapID);
    WiFi2DCharViewOffset_Reset(&param0->unk_754);
    WiFiMenuAppBoard_CreateBackground(param0, heapID, param2, v1);
    WiFiMenuAppBoard_LoadBgGraphics(param0->unk_10, heapID, param2);
    WiFiMenuAppBoard_InitPalette(param0, &param0->unk_734, param2);

    param0->unk_75C = WiFi2DCharEventQueue_New(128, heapID);
    param0->unk_00 = 1;
}

void WiFiMenuAppBoard_Free(WiFiMenuAppBoard *param0)
{
    WiFi2DCharEventQueue_Free(param0->unk_75C);
    WiFiMenuAppBoard_FreeBackground(param0);
    WiFiMenuAppBoard_FreePalette(param0, &param0->unk_734);
    WiFiMenuAppBoard_FreeActors(param0);
    WiFiMenuAppBoard_FreeRenderer(param0);
    WiFi2DCharObjectManager_Free(param0->unk_74C);
    WiFi2DCharGrid_Free(param0->unk_748);
    WiFiMenuAppBoard_FreeSpriteManager(&param0->unk_14);
    WiFiMenuAppBoard_FreeBgConfig(param0->unk_10);

    memset(param0, 0, sizeof(WiFiMenuAppBoard));
}

BOOL WiFiMenuAppBoard_IsActive(const WiFiMenuAppBoard *param0)
{
    return param0->unk_00;
}

u32 WiFiMenuAppBoard_Update(WiFiMenuAppBoard *param0)
{
    BOOL v0;

    WiFi2DCharObjectManager_Update(param0->unk_74C);
    WiFiMenuAppBoard_UpdateActors(param0);
    WiFiMenuAppBoard_ProcessActorEvents(param0);
    WiFi2DCharViewOffset_SetFromObject(&param0->unk_754, param0->unk_730->unk_00);
    WiFi2DCharBackground_Update(param0->unk_758, &param0->unk_754);
    WiFi2DCharRenderer_UpdateAll(param0->unk_750);
    WiFiMenuAppBoard_DrawActors(param0);
    WiFiMenuAppBoard_HideExitCursor(param0);

    if (WiFiMenuAppBoard_IsPlayerReady(param0) == 1) {
        v0 = WiFiMenuAppBoard_IsPlayerAtExit(param0);

        if (v0 == 1) {
            WiFiMenuAppBoard_ShowExitCursor(param0);

            if (gSystem.heldKeys & PAD_KEY_DOWN) {
                return 1;
            }
        }

        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            if (WiFiMenuAppBoard_GetPlayerDirection(param0) > 0) {
                return 2;
            } else if (WiFiMenuAppBoard_IsFacingPaletteTile(param0) == 1) {
                return 3;
            }
        }
    }

    return 0;
}

void WiFiMenuAppBoard_UpdateSprites(WiFiMenuAppBoard *param0)
{
    if (param0->unk_00) {
        SpriteList_Update(param0->unk_14.unk_00);
    }
}

u8 WiFiMenuAppBoard_GetPlayerDirection(const WiFiMenuAppBoard *param0)
{
    GF_ASSERT(param0->unk_730 != NULL);
    return param0->unk_730->unk_0A;
}

u32 WiFiMenuAppBoard_GetPlayerTileFlags(const WiFiMenuAppBoard *param0)
{
    WiFi2DCharPosition v0;

    GF_ASSERT(param0->unk_730 != NULL);

    v0 = WiFi2DCharObject_GetPosition(param0->unk_730->unk_00);
    return WiFi2DCharGrid_GetTileFlags(param0->unk_748, (v0.x) / 16, (v0.y) / 16);
}

u32 WiFiMenuAppBoard_GetTileFlagsBelowPlayer(const WiFiMenuAppBoard *param0)
{
    WiFi2DCharPosition v0;

    GF_ASSERT(param0->unk_730 != NULL);

    v0 = WiFi2DCharObject_GetPosition(param0->unk_730->unk_00);
    return WiFi2DCharGrid_GetTileFlags(param0->unk_748, (v0.x) / 16, ((v0.y) / 16) + 1);
}

void WiFiMenuAppBoard_UpdateActorPriority(WiFiMenuAppBoard *param0, const WiFiMenuAppActor *param1)
{
    WiFi2DCharPosition v0;
    u32 v1;

    v0 = WiFi2DCharObject_GetPosition(param1->unk_00);
    v1 = WiFi2DCharRenderer_GetObjectPriority(param1->unk_04);
    v1--;

    WiFiMenuAppBoard_ShowActorCursor(param0, v0, v1 - 1);
}

void WiFiMenuAppBoard_ResetActors(WiFiMenuAppBoard *param0)
{
    WiFiMenuAppBoard_HideActorCursor(param0);
}

void WiFiMenuAppBoard_SetFlag(WiFiMenuAppBoard *param0, BOOL param1)
{
    param0->unk_0C = param1;
}

BOOL WiFiMenuAppBoard_GetFlag(const WiFiMenuAppBoard *param0)
{
    return param0->unk_0C;
}

WiFiMenuAppActor *WiFiMenuAppBoard_CreatePlayer(WiFiMenuAppBoard *param0, u32 param1)
{
    WiFiMenuAppActor *v0;
    WiFiMenuAppBoardPosition v1;

    v0 = WiFiMenuAppBoard_AllocActor(param0);

    param0->unk_730 = v0;

    WiFiMenuAppBoard_FindSpawnTile(param0, &v1);
    WiFiMenuAppBoard_AddActorToObjectManager(param0, v0, &v1, 0, param1, 0, 0);
    WiFiMenuAppBoard_SetActorIdle(param0, v0);
    WiFiMenuAppBoard_AddActorRenderObject(param0, v0, 1);
    WiFi2DCharViewOffset_SetFromObject(&param0->unk_754, param0->unk_730->unk_00);
    WiFi2DCharBackground_Update(param0->unk_758, &param0->unk_754);

    return v0;
}

WiFiMenuAppActor *WiFiMenuAppBoard_CreateActor(WiFiMenuAppBoard *param0, u32 param1, u8 param2)
{
    WiFiMenuAppActor *v0;
    WiFiMenuAppBoardPosition v1;
    WiFi2DCharPosition v2;

    v0 = WiFiMenuAppBoard_AllocActor(param0);

    WiFiMenuAppBoard_FindActorSpawnTile(param0, &v1, param2 - 1);

    if (param0->unk_730) {
        v2 = WiFi2DCharObject_GetPosition(param0->unk_730->unk_00);

        if ((v2.x == v1.unk_00) && (v2.y == v1.unk_02)) {
            return NULL;
        }
    }

    WiFiMenuAppBoard_AddActorToObjectManager(param0, v0, &v1, param2, param1, 1, 4);
    WiFiMenuAppBoard_SetActorSpawning(param0, v0);
    WiFiMenuAppBoard_AddActorRenderObject(param0, v0, 0);

    return v0;
}

void WiFiMenuAppBoard_RemoveActor(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    s32 v0 = WiFi2DCharObject_GetField(param1->unk_00, 6);

    param1->unk_10 = WiFiMenuAppBoard_UpdateActorRemoving;
    param1->unk_18 = WiFiMenuAppBoard_DrawActorShadow;
    param1->unk_0C = 2;
    param1->unk_08 = 0;

    WiFi2DCharRenderer_SetObjectEnabled(param1->unk_04, 0);
    WiFi2DCharRenderer_ResetObjectAnim(param1->unk_04);
    WiFiMenuAppBoard_PushActorMoveEvent(param0, 4, param1);
}

void WiFiMenuAppBoard_DestroyActor(WiFiMenuAppActor *param0)
{
    WiFi2DCharRenderer_RemoveObject(param0->unk_04);
    WiFi2DCharObject_Reset(param0->unk_00);

    memset(param0, 0, sizeof(WiFiMenuAppActor));
}

u8 WiFiMenuAppBoard_GetActorField(const WiFiMenuAppActor *param0)
{
    return WiFi2DCharObject_GetField(param0->unk_00, 4);
}

int WiFiMenuAppBoard_GetActorOppositeDirection(const WiFiMenuAppActor *param0)
{
    int v0 = WiFi2DCharObject_GetField(param0->unk_00, 6);
    return WiFi2DChar_DirectionOpposite(v0);
}

void WiFiMenuAppBoard_SetActorAnim(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1, int param2)
{
    u32 v0;
    WiFi2DCharPosition v1;

    param1->unk_14 = param1->unk_10;
    param1->unk_10 = WiFiMenuAppBoard_UpdateActorPaused;
    param1->unk_0E = param1->unk_0C;
    param1->unk_0C = 5;

    v0 = WiFi2DCharObject_GetField(param1->unk_00, 4);

    WiFiMenuAppBoard_PushMoveEvent(param0, 0, param2, v0);
    WiFi2DCharRenderer_SetObjectEnabled(param1->unk_04, 0);
    WiFi2DCharRenderer_SetObjectAnim(param1->unk_04, param2);

    v1.x = WiFi2DCharObject_GetField(param1->unk_00, 0);
    v1.y = WiFi2DCharObject_GetField(param1->unk_00, 1);

    WiFi2DCharRenderer_SetObjectPosition(param1->unk_04, v1);
}

void WiFiMenuAppBoard_RestoreActorCallback(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    if (param1 == NULL) {
        return;
    }

    if (param1->unk_14 == NULL) {
        return;
    }

    param1->unk_10 = param1->unk_14;
    param1->unk_14 = NULL;
    param1->unk_0C = param1->unk_0E;

    WiFi2DCharRenderer_SetObjectEnabled(param1->unk_04, 1);
}

void WiFiMenuAppBoard_SetActorState(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1, int param2)
{
    BOOL v0 = WiFiMenuAppBoard_IsActorTransitioning(param1);

    if (v0 == 0) {
        param1->unk_0B = param2;
    } else {
        WiFiMenuAppBoard_ApplyActorState(param0, param1, param2);
    }
}

void WiFiMenuAppBoard_SetPlayerPalette(WiFiMenuAppBoard *param0)
{
    s8 v0;

    if (WiFiMenuAppBoard_IsFacingPaletteTile(param0) == 1) {
        v0 = WiFiMenuAppBoard_GetTileFlagsBelowPlayer(param0);
        v0 -= 3;

        GF_ASSERT((v0 >= 0) && (v0 < 4));

        WiFiMenuAppBoard_StartPaletteFlash(&param0->unk_734, v0);
        return;
    }

    GF_ASSERT(FALSE);
}

void WiFiMenuAppBoard_ResetPalette(WiFiMenuAppBoard *param0)
{
    WiFiMenuAppBoard_CancelPaletteFlash(&param0->unk_734);
}

void WiFiMenuAppBoard_UpdatePalette(WiFiMenuAppBoard *param0)
{
    WiFiMenuAppBoard_AdvancePalette(param0, &param0->unk_734);
}

static void WiFiMenuAppBoard_FreeActors(WiFiMenuAppBoard *param0)
{
    int v0;

    for (v0 = 0; v0 < 48; v0++) {
        if (param0->unk_1F0[v0].unk_00 != NULL) {
            WiFiMenuAppBoard_DestroyActor(&param0->unk_1F0[v0]);
        }
    }
}

static BOOL WiFiMenuAppBoard_IsPlayerReady(const WiFiMenuAppBoard *param0)
{
    s32 v0 = WiFi2DCharObject_GetField(param0->unk_730->unk_00, 5);

    if (v0 == 0) {
        return 1;
    }

    return 0;
}

static BOOL WiFiMenuAppBoard_IsFacingPaletteTile(const WiFiMenuAppBoard *param0)
{
    u32 v0;
    WiFi2DCharPosition v1;
    int v2;

    v1 = WiFi2DCharObject_GetPosition(param0->unk_730->unk_00);
    v2 = WiFi2DCharObject_GetField(param0->unk_730->unk_00, 6);
    v1 = WiFi2DCharPosition_OffsetByDirection(v1, v2);
    v0 = WiFi2DCharGrid_GetTileFlags(param0->unk_748, (v1.x) / 16, (v1.y) / 16);

    if (v2 == 0) {
        if (v0 == 2) {
            return 1;
        }
    }

    return 0;
}

static void WiFiMenuAppBoard_ProcessActorEvents(WiFiMenuAppBoard *param0)
{
    WiFi2DCharEvent v0;
    WiFi2DCharMoveRequest v1;
    BOOL v2;

    while (WiFi2DCharEventQueue_Pop(param0->unk_75C, &v0) == 1) {
        v2 = WiFi2DCharAI_ChooseMove(param0->unk_748, param0->unk_74C, &v0, &v1);

        if (v2 == 1) {
            WiFi2DCharObjectManager_StartMove(param0->unk_74C, &v1);
        }
    }
}

static void WiFiMenuAppBoard_UpdateActors(WiFiMenuAppBoard *param0)
{
    int v0;
    BOOL v1;

    for (v0 = 0; v0 < 48; v0++) {
        if (param0->unk_1F0[v0].unk_00 != NULL) {
            v1 = param0->unk_1F0[v0].unk_10(param0, &param0->unk_1F0[v0]);

            if (v1 == 1) {
                WiFiMenuAppBoard_DestroyActor(&param0->unk_1F0[v0]);
            }
        }
    }
}

static void WiFiMenuAppBoard_DrawActors(WiFiMenuAppBoard *param0)
{
    int v0;

    for (v0 = 0; v0 < 48; v0++) {
        if (param0->unk_1F0[v0].unk_00 != NULL) {
            param0->unk_1F0[v0].unk_18(param0, &param0->unk_1F0[v0]);
        }
    }
}

static const WiFiMenuAppActor *WiFiMenuAppBoard_FindAdjacentActor(const WiFiMenuAppBoard *param0, const WiFiMenuAppActor *param1, int param2)
{
    const WiFi2DCharObject *v0;
    int v1;

    v0 = WiFi2DCharObjectManager_FindObjectAtOffset(param1->unk_00, param0->unk_74C, param2);

    if (v0 != NULL) {
        for (v1 = 0; v1 < 48; v1++) {
            if (param0->unk_1F0[v1].unk_00 == v0) {
                return &param0->unk_1F0[v1];
            }
        }
    }

    return NULL;
}

static void WiFiMenuAppBoard_CreateRenderer(WiFiMenuAppBoard *param0, u32 param1, enum HeapID heapID)
{
    int v0;

    param0->unk_750 = WiFi2DCharRenderer_NewWithShadow(param0->unk_14.unk_00, NULL, 48, param1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, heapID);

    WiFi2DCharRenderer_LoadShadowResources(param0->unk_750, 2, heapID);
}

static void WiFiMenuAppBoard_FreeRenderer(WiFiMenuAppBoard *param0)
{
    WiFi2DCharRenderer_Free(param0->unk_750);
}

static void WiFiMenuAppBoard_CreateBackground(WiFiMenuAppBoard *param0, enum HeapID heapID, NARC *param2, u32 param3)
{
    WiFiMenuAppSpriteParams v0 = {
        0,
        0,
        GX_BG_COLORMODE_16,
        GX_BG_SCRBASE_0xe000,
        GX_BG_CHARBASE_0x00000,
        GX_BG_EXTPLTT_01,
        3,
        0,
        92,
        32,
        0
    };

    v0.unk_09 += param3;
    param0->unk_758 = WiFi2DCharBackground_New(&param0->unk_14.unk_04, param0->unk_10, &v0, heapID);
}

static void WiFiMenuAppBoard_FreeBackground(WiFiMenuAppBoard *param0)
{
    WiFi2DCharBackground_Free(param0->unk_758);
}

static void WiFiMenuAppBoard_InitSpriteManager(WiFiMenuAppSpriteManager *param0, enum HeapID heapID, NARC *param2)
{
    int i;

    param0->unk_00 = SpriteList_InitRendering(96, &param0->unk_04, heapID);
    SetSubScreenViewRect(&param0->unk_04, 0, (800 * FX32_ONE));

    for (i = 0; i < 4; i++) {
        param0->unk_190[i] = SpriteResourceCollection_New(16, i, heapID);
    }

    WiFiMenuAppBoard_LoadSpriteResources(param0, heapID, param2);
    WiFiMenuAppBoard_AddSprites(param0, heapID);
}

static void WiFiMenuAppBoard_FreeSpriteManager(WiFiMenuAppSpriteManager *param0)
{
    int v0;

    WiFiMenuAppBoard_DeleteSprites(param0);
    WiFiMenuAppBoard_UnloadSpriteResources(param0);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(param0->unk_190[v0]);
    }

    SpriteList_Delete(param0->unk_00);
}

static void WiFiMenuAppBoard_LoadSpriteResources(WiFiMenuAppSpriteManager *param0, u32 param1, NARC *param2)
{
    WiFiMenuAppBoard_LoadSpriteResourceData(param0, param1, param2);
}

static void WiFiMenuAppBoard_UnloadSpriteResources(WiFiMenuAppSpriteManager *param0)
{
    WiFiMenuAppBoard_RemoveSpriteResourceData(param0);
}

static void WiFiMenuAppBoard_AddSprites(WiFiMenuAppSpriteManager *param0, u32 param1)
{
    WiFiMenuAppBoard_CreateSprites(param0, param1);
}

static void WiFiMenuAppBoard_DeleteSprites(WiFiMenuAppSpriteManager *param0)
{
    WiFiMenuAppBoard_DestroySprites(param0);
}

static void WiFiMenuAppBoard_InitBgConfig(BgConfig *param0, u32 param1)
{
    return;
}

static void WiFiMenuAppBoard_FreeBgConfig(BgConfig *param0)
{
    return;
}

static void WiFiMenuAppBoard_LoadBgGraphics(BgConfig *param0, u32 param1, NARC *param2)
{
    Graphics_LoadPaletteFromOpenNARC(param2, 30, 0, 0, 8 * 32, param1);
    Bg_MaskPalette(BG_LAYER_MAIN_0, 0);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param2, 29, param0, 0, 0, 0, 0, param1);
}

static void WiFiMenuAppBoard_LoadSpriteResourceData(WiFiMenuAppSpriteManager *param0, u32 param1, NARC *param2)
{
    BOOL v0;

    param0->unk_1A0.unk_00[0] = SpriteResourceCollection_AddTilesFrom(param0->unk_190[0], param2, 37, 0, 50, NNS_G2D_VRAM_TYPE_2DMAIN, param1);
    param0->unk_1A0.unk_00[1] = SpriteResourceCollection_AddPaletteFrom(param0->unk_190[1], param2, 36, 0, 50, NNS_G2D_VRAM_TYPE_2DMAIN, 1, param1);
    param0->unk_1A0.unk_00[2] = SpriteResourceCollection_AddFrom(param0->unk_190[2], param2, 38, 0, 50, 2, param1);
    param0->unk_1A0.unk_00[3] = SpriteResourceCollection_AddFrom(param0->unk_190[3], param2, 39, 0, 50, 3, param1);

    v0 = SpriteTransfer_RequestCharAtEnd(param0->unk_1A0.unk_00[0]);
    GF_ASSERT(v0 == 1);

    v0 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_1A0.unk_00[1]);
    GF_ASSERT(v0 == 1);

    SpriteResource_ReleaseData(param0->unk_1A0.unk_00[0]);
    SpriteResource_ReleaseData(param0->unk_1A0.unk_00[1]);
    SpriteResourcesHeader_Init(&param0->unk_1A0.unk_10, 50, 50, 50, 50, 0xffffffff, 0xffffffff, 0, 2, param0->unk_190[0], param0->unk_190[1], param0->unk_190[2], param0->unk_190[3], NULL, NULL);
}

static void WiFiMenuAppBoard_RemoveSpriteResourceData(WiFiMenuAppSpriteManager *param0)
{
    int v0;

    SpriteTransfer_ResetCharTransfer(param0->unk_1A0.unk_00[0]);
    SpriteTransfer_ResetPlttTransfer(param0->unk_1A0.unk_00[1]);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Remove(param0->unk_190[v0], param0->unk_1A0.unk_00[v0]);
    }
}

static void WiFiMenuAppBoard_CreateSprites(WiFiMenuAppSpriteManager *param0, u32 param1)
{
    AffineSpriteListTemplate v0;

    memset(&v0, 0, sizeof(AffineSpriteListTemplate));

    v0.list = param0->unk_00;
    v0.resourceData = &param0->unk_1A0.unk_10;
    v0.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v0.affineScale.x = FX32_ONE;
    v0.affineScale.y = FX32_ONE;
    v0.priority = 0;
    v0.heapID = param1;

    param0->unk_1A0.unk_34 = SpriteList_AddAffine(&v0);
    param0->unk_1A0.unk_38 = SpriteList_AddAffine(&v0);

    Sprite_SetDrawFlag(param0->unk_1A0.unk_34, FALSE);
    Sprite_SetDrawFlag(param0->unk_1A0.unk_38, FALSE);
    Sprite_SetAnimateFlag(param0->unk_1A0.unk_34, 1);
    Sprite_SetAnim(param0->unk_1A0.unk_38, 1);
}

static void WiFiMenuAppBoard_DestroySprites(WiFiMenuAppSpriteManager *param0)
{
    Sprite_Delete(param0->unk_1A0.unk_34);
    Sprite_Delete(param0->unk_1A0.unk_38);
}

static void WiFiMenuAppBoard_ShowExitCursor(WiFiMenuAppBoard *param0)
{
    WiFiMenuAppBoardPosition v0;
    VecFx32 v1;

    WiFiMenuAppBoard_FindSpawnTile(param0, &v0);

    v0.unk_00 += 8;
    v0.unk_02 += 32;

    v1.x = v0.unk_00 << FX32_SHIFT;
    v1.y = v0.unk_02 << FX32_SHIFT;

    Sprite_SetPosition(param0->unk_14.unk_1A0.unk_34, &v1);
    Sprite_SetDrawFlag(param0->unk_14.unk_1A0.unk_34, TRUE);
}

static void WiFiMenuAppBoard_HideExitCursor(WiFiMenuAppBoard *param0)
{
    Sprite_SetDrawFlag(param0->unk_14.unk_1A0.unk_34, FALSE);
}

static void WiFiMenuAppBoard_ShowActorCursor(WiFiMenuAppBoard *param0, WiFi2DCharPosition param1, u32 param2)
{
    VecFx32 v0;

    param1.x += 8;
    param1.y += 0;

    v0.x = param1.x << FX32_SHIFT;
    v0.y = param1.y << FX32_SHIFT;

    Sprite_SetPosition(param0->unk_14.unk_1A0.unk_38, &v0);
    Sprite_SetPriority(param0->unk_14.unk_1A0.unk_38, param2);
    Sprite_SetDrawFlag(param0->unk_14.unk_1A0.unk_38, TRUE);
}

static void WiFiMenuAppBoard_HideActorCursor(WiFiMenuAppBoard *param0)
{
    Sprite_SetDrawFlag(param0->unk_14.unk_1A0.unk_38, FALSE);
}

static BOOL WiFiMenuAppBoard_IsPlayerAtExit(WiFiMenuAppBoard *param0)
{
    WiFi2DCharPosition v0;
    u32 v1;
    int v2;

    if (param0->unk_730 == NULL) {
        return 0;
    }

    v0 = WiFi2DCharObject_GetPosition(param0->unk_730->unk_00);
    v2 = WiFi2DCharObject_GetField(param0->unk_730->unk_00, 6);
    v1 = WiFi2DCharGrid_GetTileFlags(param0->unk_748, (v0.x) / 16, (v0.y) / 16);

    if ((v1 == 15) && (v2 == 1)) {
        return 1;
    }

    return 0;
}

static void WiFiMenuAppBoard_FindActorSpawnTile(WiFiMenuAppBoard *param0, WiFiMenuAppBoardPosition *param1, u32 param2)
{
    u32 v0;
    u32 v1;
    int v2, v3;
    u32 v4, v5;
    u32 v6;
    u32 v7;

    v0 = param2 / 8;
    v1 = param2 % 8;
    v4 = WiFi2DCharGrid_GetWidth(param0->unk_748);
    v5 = WiFi2DCharGrid_GetHeight(param0->unk_748);

    for (v2 = 0; v2 < v5; v2++) {
        for (v3 = 0; v3 < v4; v3++) {
            v6 = WiFi2DCharGrid_GetTileFlags(param0->unk_748, v3, v2);

            if (v6 == 7 + v1) {
                v7 = WiFi2DCharGrid_GetTileFlags(param0->unk_748, v3, v2 + 1);

                if (v7 == v0 + 3) {
                    param1->unk_00 = (v3) * 16;
                    param1->unk_02 = (v2) * 16;
                    return;
                }
            }
        }
    }

    GF_ASSERT(FALSE);
}

static void WiFiMenuAppBoard_FindSpawnTile(WiFiMenuAppBoard *param0, WiFiMenuAppBoardPosition *param1)
{
    int v0, v1;
    u32 v2, v3;
    u32 v4;

    v2 = WiFi2DCharGrid_GetWidth(param0->unk_748);
    v3 = WiFi2DCharGrid_GetHeight(param0->unk_748);

    for (v0 = 0; v0 < v3; v0++) {
        for (v1 = 0; v1 < v2; v1++) {
            v4 = WiFi2DCharGrid_GetTileFlags(param0->unk_748, v1, v0);

            if (v4 == 15) {
                param1->unk_00 = (v1) * 16;
                param1->unk_02 = (v0) * 16;

                return;
            }
        }
    }

    GF_ASSERT(FALSE);
}

static WiFiMenuAppActor *WiFiMenuAppBoard_AllocActor(WiFiMenuAppBoard *param0)
{
    int v0;

    for (v0 = 0; v0 < 48; v0++) {
        if (param0->unk_1F0[v0].unk_00 == NULL) {
            return &param0->unk_1F0[v0];
        }
    }

    GF_ASSERT(FALSE);
    return NULL;
}

static void WiFiMenuAppBoard_AddActorRenderObject(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1, BOOL param2)
{
    param1->unk_04 = WiFi2DCharRenderer_AddObject(param0->unk_750, param1->unk_00, param2, param0->heapID);

    if (param2 == 0) {
        WiFi2DCharRenderer_SetObjectEnabled(param1->unk_04, 0);
        WiFi2DCharRenderer_ResetObjectAnim(param1->unk_04);
        WiFi2DCharRenderer_SetObjectVisible(param1->unk_04, 0);
    }
}

static void WiFiMenuAppBoard_AddActorToObjectManager(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1, const WiFiMenuAppBoardPosition *param2, u32 param3, u16 param4, u8 param5, int param6)
{
    WiFiMenuAppRect v0;

    v0.unk_00 = param2->unk_00;
    v0.unk_02 = param2->unk_02;
    v0.unk_04 = param3;
    v0.unk_06 = param6;
    v0.unk_08 = param5;
    v0.unk_0A = param4;

    param1->unk_00 = WiFi2DCharObjectManager_AddObject(param0->unk_74C, &v0);
}

static BOOL WiFiMenuAppBoard_IsActorIdle(const WiFiMenuAppActor *param0)
{
    switch (param0->unk_0C) {
    case 0:
    case 3:
    case 4:
        return 1;
    case 1:
    case 2:
    case 5:
        return 0;
    default:
        break;
    }

    return 0;
}

static void WiFiMenuAppBoard_SetActorIdle(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    param1->unk_10 = WiFiMenuAppBoard_UpdatePlayerActor;
    param1->unk_18 = WiFiMenuAppBoard_DrawActorDefault;
    param1->unk_0C = 0;

    WiFiMenuAppBoard_PushActorMoveEvent(param0, 0, param1);
}

static void WiFiMenuAppBoard_SetActorSpawning(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    param1->unk_10 = WiFiMenuAppBoard_UpdateActorSpawning;
    param1->unk_18 = WiFiMenuAppBoard_DrawActorShadow;
    param1->unk_08 = 45;
    param1->unk_0C = 1;
}

static void WiFiMenuAppBoard_SetActorWander(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    param1->unk_10 = WiFiMenuAppBoard_UpdateActorWander;
    param1->unk_18 = WiFiMenuAppBoard_DrawActorDefault;
    param1->unk_08 = 256 + (MTRNG_Next() % 1024);
    param1->unk_0C = 3;

    WiFiMenuAppBoard_PushActorMoveEvent(param0, 0, param1);
    WiFi2DCharRenderer_SetObjectEnabled(param1->unk_04, 1);
}

static void WiFiMenuAppBoard_SetActorJump(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    param1->unk_10 = WiFiMenuAppBoard_UpdateActorJump;
    param1->unk_18 = WiFiMenuAppBoard_DrawActorJump;
    param1->unk_08 = ((6 * 2) + 16);
    param1->unk_0C = 4;

    WiFiMenuAppBoard_PushActorMoveEvent(param0, 4, param1);
    WiFi2DCharRenderer_SetObjectEnabled(param1->unk_04, 0);
}

static void WiFiMenuAppBoard_DrawActorDefault(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    return;
}

static void WiFiMenuAppBoard_DrawActorShadow(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    WiFi2DCharPosition v0, v1;

    WiFi2DCharRenderer_UpdateObjectAnim(param1->unk_04);

    if (WiFi2DCharRenderer_IsObjectVisible(param1->unk_04) == 0) {
        WiFi2DCharRenderer_SetObjectVisible(param1->unk_04, 1);
    }

    v0.x = WiFi2DCharObject_GetField(param1->unk_00, 0);
    v0.y = WiFi2DCharObject_GetField(param1->unk_00, 1);

    v1 = v0;
    v0.y += FX_Mul(CalcSineDegrees(param1->unk_08), -192 * FX32_ONE) >> FX32_SHIFT;

    WiFi2DCharRenderer_SetObjectPosition(param1->unk_04, v0);
    WiFi2DCharRenderer_SetObjectShadowPosition(param1->unk_04, v1);
}

static void WiFiMenuAppBoard_DrawActorJump(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    u32 v0;
    WiFi2DCharPosition v1, v2;
    s16 v3;

    v1.x = WiFi2DCharObject_GetField(param1->unk_00, 0);
    v1.y = WiFi2DCharObject_GetField(param1->unk_00, 1);

    v2 = v1;
    v3 = param1->unk_08 - 16;

    if (v3 > 0) {
        v3 = v3 % 6;
        v0 = (180 * v3) / 6;
        v1.y -= FX_Mul(CalcSineDegrees(v0), 4 * FX32_ONE) >> FX32_SHIFT;
    }

    WiFi2DCharRenderer_SetObjectPosition(param1->unk_04, v1);
    WiFi2DCharRenderer_SetObjectShadowPosition(param1->unk_04, v2);
    WiFi2DCharRenderer_SetObjectAnim(param1->unk_04, 1);
}

static BOOL WiFiMenuAppBoard_UpdatePlayerActor(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    s32 v0;
    s32 v1;
    s32 v2;
    s32 v3;
    const WiFiMenuAppActor *v4;

    v0 = WiFi2DCharObject_GetField(param1->unk_00, 6);
    v1 = WiFi2DCharObject_GetField(param1->unk_00, 4);
    v2 = WiFi2DCharObject_GetField(param1->unk_00, 5);

    if (v2 != 0) {
        return 0;
    }

    if (gSystem.pressedKeys & PAD_BUTTON_A) {
        v4 = WiFiMenuAppBoard_FindAdjacentActor(param0, param1, v0);

        if (v4 != NULL) {
            if (WiFiMenuAppBoard_IsActorIdle(v4) == 1) {
                param1->unk_0A = WiFi2DCharObject_GetField(v4->unk_00, 4);
            } else {
                param1->unk_0A = 0;
            }
        } else {
            param1->unk_0A = 0;
        }
    }

    if (param0->unk_0C == 1) {
        return 0;
    }

    if (gSystem.heldKeys & PAD_BUTTON_B) {
        v3 = 3;
    } else {
        v3 = 2;
    }

    if (gSystem.heldKeys & PAD_KEY_UP) {
        if (v0 == 0) {
            WiFiMenuAppBoard_PushMoveEvent(param0, v3, v0, v1);
        } else {
            WiFiMenuAppBoard_PushMoveEvent(param0, 1, 0, v1);
        }
    } else if (gSystem.heldKeys & PAD_KEY_DOWN) {
        if (v0 == 1) {
            WiFiMenuAppBoard_PushMoveEvent(param0, v3, v0, v1);
        } else {
            WiFiMenuAppBoard_PushMoveEvent(param0, 1, 1, v1);
        }
    } else if (gSystem.heldKeys & PAD_KEY_LEFT) {
        if (v0 == 2) {
            WiFiMenuAppBoard_PushMoveEvent(param0, v3, v0, v1);
        } else {
            WiFiMenuAppBoard_PushMoveEvent(param0, 1, 2, v1);
        }
    } else if (gSystem.heldKeys & PAD_KEY_RIGHT) {
        if (v0 == 3) {
            WiFiMenuAppBoard_PushMoveEvent(param0, v3, v0, v1);
        } else {
            WiFiMenuAppBoard_PushMoveEvent(param0, 1, 3, v1);
        }
    }

    return 0;
}

static BOOL WiFiMenuAppBoard_UpdateActorSpawning(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    s32 v0;
    u32 v1, v2;

    param1->unk_08--;

    if (param1->unk_08 <= 0) {
        WiFi2DCharRenderer_RefreshObject(param1->unk_04);
        WiFi2DCharRenderer_SetObjectEnabled(param1->unk_04, 1);

        v1 = WiFi2DCharObject_GetField(param0->unk_730->unk_00, 4);
        v2 = WiFi2DCharObject_GetField(param1->unk_00, 4);

        if (v2 == v1) {
            WiFiMenuAppBoard_SetActorIdle(param0, param1);
        } else {
            WiFiMenuAppBoard_ApplyActorState(param0, param1, param1->unk_0B);
        }
    }

    return 0;
}

static BOOL WiFiMenuAppBoard_UpdateActorRemoving(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    param1->unk_08++;

    if (param1->unk_08 > 45) {
        return 1;
    }

    return 0;
}

static BOOL WiFiMenuAppBoard_UpdateActorWander(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    u32 v0;
    u32 v1;

    param1->unk_08--;

    if (param1->unk_08 <= 0) {
        param1->unk_08 = 256 + (MTRNG_Next() % 1024);

        v0 = MTRNG_Next() % 4;
        v1 = WiFi2DCharObject_GetField(param1->unk_00, 4);

        WiFiMenuAppBoard_PushMoveEvent(param0, 0, v0, v1);
    }

    return 0;
}

static BOOL WiFiMenuAppBoard_UpdateActorJump(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    param1->unk_08--;

    if (param1->unk_08 < 0) {
        param1->unk_08 = ((6 * 2) + 16);
    }

    return 0;
}

static BOOL WiFiMenuAppBoard_UpdateActorPaused(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1)
{
    return 0;
}

static void WiFiMenuAppBoard_PushMoveEvent(WiFiMenuAppBoard *param0, s32 param1, s32 param2, s32 param3)
{
    WiFi2DCharEvent v0;

    v0.unk_00 = param1;
    v0.unk_02 = param2;
    v0.unk_03 = param3;

    WiFi2DCharEventQueue_Push(param0->unk_75C, &v0);
}

static void WiFiMenuAppBoard_PushActorMoveEvent(WiFiMenuAppBoard *param0, s32 param1, const WiFiMenuAppActor *param2)
{
    s32 v0;
    s32 v1;

    v0 = WiFi2DCharObject_GetField(param2->unk_00, 6);
    v1 = WiFi2DCharObject_GetField(param2->unk_00, 4);

    WiFiMenuAppBoard_PushMoveEvent(param0, param1, v0, v1);
}

static BOOL WiFiMenuAppBoard_IsActorTransitioning(const WiFiMenuAppActor *param0)
{
    if ((u32)param0->unk_18 == (u32)WiFiMenuAppBoard_DrawActorShadow) {
        return 0;
    }

    return 1;
}

static void WiFiMenuAppBoard_ApplyActorState(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1, int param2)
{
    switch (param2) {
    case 0:
        WiFiMenuAppBoard_SetActorWander(param0, param1);
        break;
    case 1:
        WiFiMenuAppBoard_SetActorJump(param0, param1);
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    param1->unk_0B = param2;
}

static void WiFiMenuAppBoard_InitPalette(WiFiMenuAppBoard *param0, WiFiMenuAppPalette *param1, NARC *param2)
{
    memset(param1, 0, sizeof(WiFiMenuAppPalette));

    param1->unk_00 = Graphics_GetPlttDataFromOpenNARC(param2, 31, &param1->unk_04, param0->heapID);
    param1->unk_08 = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
    param1->unk_09 = 0;
    param1->unk_0A = sWiFiMenuAppBoardPaletteFrameDurations[param1->unk_09];
}

static void WiFiMenuAppBoard_FreePalette(WiFiMenuAppBoard *param0, WiFiMenuAppPalette *param1)
{
    Heap_Free(param1->unk_00);
    memset(param1, 0, sizeof(WiFiMenuAppPalette));
}

static void WiFiMenuAppBoard_AdvancePalette(WiFiMenuAppBoard *param0, WiFiMenuAppPalette *param1)
{
    WiFiMenuAppBoard_UpdatePaletteAnim(param1);
    WiFiMenuAppBoard_UpdatePaletteFlash(param1);
}

static void WiFiMenuAppBoard_UpdatePaletteAnim(WiFiMenuAppPalette *param0)
{
    int v0;
    u32 v1;

    param0->unk_0A--;

    if (param0->unk_0A <= 0) {
        param0->unk_09 = (param0->unk_09 + 1) % 2;
        param0->unk_0A = sWiFiMenuAppBoardPaletteFrameDurations[param0->unk_09];

        if (param0->unk_09 == 1) {
            v1 = 2;
        } else {
            v1 = 1;
        }

        for (v0 = 0; v0 < 4; v0++) {
            if (param0->unk_08 & (1 << v0)) {
                VramTransfer_Request(NNS_GFD_DST_2D_BG_PLTT_MAIN, MCR_PCANM_DESTPL(v0), WiFiMenuAppBoard_GetPaletteEntry(param0, v1), 2);
            }
        }
    }
}

static void WiFiMenuAppBoard_UpdatePaletteFlash(WiFiMenuAppPalette *param0)
{
    BOOL v0 = 0;
    u32 v1 = 0;
    BOOL v2 = 0;

    if (sWiFiMenuAppBoardPaletteAnimSteps[param0->unk_0D].unk_00 == 1) {
        param0->unk_0E--;

        if (param0->unk_0E <= 0) {
            v2 = 1;
        }
    } else {
        if (param0->unk_10) {
            param0->unk_10 = 0;
            v2 = 1;
        }
    }

    if (v2) {
        param0->unk_0D++;

        if (param0->unk_0D >= 8) {
            WiFiMenuAppBoard_ResetPaletteFlash(param0);
            return;
        }

        param0->unk_0E = sWiFiMenuAppBoardPaletteAnimSteps[param0->unk_0D].unk_01;

        v0 = sWiFiMenuAppBoardPaletteAnimSteps[param0->unk_0D].unk_02;
        v1 = sWiFiMenuAppBoardPaletteAnimSteps[param0->unk_0D].unk_03;
    }

    if (v0) {
        VramTransfer_Request(NNS_GFD_DST_2D_BG_PLTT_MAIN, MCR_PCANM_DESTPL(param0->unk_0C), WiFiMenuAppBoard_GetPaletteEntry(param0, v1), 2);
    }
}

static void *WiFiMenuAppBoard_GetPaletteEntry(WiFiMenuAppPalette *param0, u32 param1)
{
    u16 *v0 = (u16 *)param0->unk_04->pRawData;
    return &v0[param1 + 1];
}

static void WiFiMenuAppBoard_ResetPaletteFlash(WiFiMenuAppPalette *param0)
{
    param0->unk_08 |= 1 << param0->unk_0C;
    param0->unk_0C = 0;
    param0->unk_0D = 0;
    param0->unk_0E = 0;
    param0->unk_10 = 0;
}

static void WiFiMenuAppBoard_RequestPaletteFlash(WiFiMenuAppPalette *param0)
{
    param0->unk_10 = 1;
}

static void WiFiMenuAppBoard_StartPaletteFlash(WiFiMenuAppPalette *param0, u8 param1)
{
    if (param0->unk_0D != 0) {
        WiFiMenuAppBoard_ResetPaletteFlash(param0);
    }

    param0->unk_08 ^= 1 << param1;
    param0->unk_0C = param1;

    WiFiMenuAppBoard_RequestPaletteFlash(param0);
}

static void WiFiMenuAppBoard_CancelPaletteFlash(WiFiMenuAppPalette *param0)
{
    if (param0->unk_0D != 0) {
        WiFiMenuAppBoard_RequestPaletteFlash(param0);
    }
}
