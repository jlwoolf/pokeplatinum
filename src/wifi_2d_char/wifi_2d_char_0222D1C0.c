#include "wifi_2d_char/wifi_2d_char_0222D1C0.h"

#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/wifi_2d_char_0222D160.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D160.h"
#include "wifi_menu_app/struct_wifi_menu_app_0223582C.h"

#include "bg_window.h"
#include "graphics.h"
#include "heap.h"
#include "sprite_util.h"

typedef struct WiFi2DCharBackground {
    G2dRenderer *unk_00;
    BgConfig *unk_04;
    void *unk_08;
    NNSG2dScreenData *unk_0C;
    u32 unk_10;
    u32 unk_14;
    u16 unk_18;
    u16 unk_1A;
} WiFi2DCharBackground;

static void WiFi2DCharBackground_InitBg(BgConfig *param0, int param1, const WiFiMenuAppSpriteParams *param2);
static void WiFi2DCharBackground_Scroll(WiFi2DCharBackground *param0, s16 param1, s16 param2);
static void WiFi2DCharBackground_DrawTilemap(BgConfig *param0, int param1, const NNSG2dScreenData *param2, s16 param3, s16 param4);
static void WiFi2DCharBackground_CopyTilemapRect(BgConfig *param0, u8 param1, u8 param2, u8 param3, u8 param4, u8 param5, const void *param6, u8 param7, u8 param8, u8 param9, u8 param10);
static u8 WiFi2DCharBackground_GetQuadrant(u8 param0, u8 param1);
static const void *WiFi2DCharBackground_GetQuadrantData(const u8 *param0, u8 param1, u8 param2, u8 param3, u8 param4, u8 param5, WiFi2DCharPosition *param6);

WiFi2DCharBackground *WiFi2DCharBackground_New(G2dRenderer *param0, BgConfig *param1, const WiFiMenuAppSpriteParams *param2, enum HeapID heapID)
{
    WiFi2DCharBackground *v0 = Heap_Alloc(heapID, sizeof(WiFi2DCharBackground));
    memset(v0, 0, sizeof(WiFi2DCharBackground));

    v0->unk_00 = param0;
    v0->unk_04 = param1;
    v0->unk_10 = param2->screen;
    v0->unk_14 = param2->bgLayer;

    WiFi2DCharBackground_InitBg(v0->unk_04, v0->unk_14, param2);

    v0->unk_08 = Graphics_GetScrnData(param2->narcID, param2->tilemapNarcMember, param2->compressed, &v0->unk_0C, heapID);

    return v0;
}

void WiFi2DCharBackground_Free(WiFi2DCharBackground *param0)
{
    Heap_Free(param0->unk_08);
    Heap_Free(param0);
}

void WiFi2DCharBackground_Update(WiFi2DCharBackground *param0, const WiFi2DCharViewOffset *param1)
{
    s16 v0;
    s16 v1 = WiFi2DCharViewOffset_GetX(param1);
    v0 = WiFi2DCharViewOffset_GetY(param1);

    if (param0->unk_10 == 0) {
        SetMainScreenViewRect(param0->unk_00, FX32_CONST(v0), FX32_CONST(v1));
    } else {
        SetSubScreenViewRect(param0->unk_00, FX32_CONST(v0), FX32_CONST(v1) + (192 << FX32_SHIFT));
    }

    WiFi2DCharBackground_Scroll(param0, v0, v1);
}

static void WiFi2DCharBackground_InitBg(BgConfig *param0, int param1, const WiFiMenuAppSpriteParams *param2)
{
    BgTemplate v0 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x1000,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_512x256,
    };

    v0.colorMode = param2->colorMode;
    v0.screenBase = param2->screenBase;
    v0.charBase = param2->charBase;
    v0.bgExtPltt = param2->bgExtPltt;
    v0.priority = param2->priority;
    v0.areaOver = 0;
    v0.mosaic = param2->mosaic;

    Bg_FreeTilemapBuffer(param0, param1);
    Bg_InitFromTemplate(param0, param1, &v0, 0);
}

static void WiFi2DCharBackground_Scroll(WiFi2DCharBackground *param0, s16 param1, s16 param2)
{
    s16 v0;
    s16 v1;
    s16 v2;
    s16 v3;

    v0 = param1 / 8;
    v1 = param2 / 8;
    v2 = param1 % 8;
    v3 = param2 % 8;

    if ((v0 != param0->unk_18) || (v1 != param0->unk_1A)) {
        param0->unk_18 = v0;
        param0->unk_1A = v1;

        WiFi2DCharBackground_DrawTilemap(param0->unk_04, param0->unk_14, param0->unk_0C, -v0, -v1);
        Bg_ScheduleTilemapTransfer(param0->unk_04, param0->unk_14);
    }

    Bg_ScheduleScroll(param0->unk_04, param0->unk_14, 0, v2);
    Bg_ScheduleScroll(param0->unk_04, param0->unk_14, 3, v3);
}

static void WiFi2DCharBackground_DrawTilemap(BgConfig *param0, int param1, const NNSG2dScreenData *param2, s16 param3, s16 param4)
{
    s16 v0, v1;
    s16 v2, v3;
    s16 v4, v5;
    s16 v6 = (param2->screenWidth / 8);
    s16 v7 = (param2->screenHeight / 8);

    if (param3 < 0) {
        v2 = -param3;
    } else {
        v2 = 0;
    }

    if (param4 < 0) {
        v3 = -param4;
    } else {
        v3 = 0;
    }

    if (param3 > 0) {
        v4 = param3;
    } else {
        v4 = 0;
    }

    if (param4 > 0) {
        v5 = param4;
    } else {
        v5 = 0;
    }

    v0 = 33 - v4;
    v1 = 25 - v5;

    if (v6 < (v2 + v0)) {
        v0 -= (v2 + v0) - v6;
    }

    if (v7 < (v3 + v1)) {
        v1 -= (v3 + v1) - v7;
    }

    Bg_FillTilemapRect(param0, param1, 0, 0, 0, 33, 25, 17);
    WiFi2DCharBackground_CopyTilemapRect(param0, param1, v4, v5, v0, v1, param2->rawData, v2, v3, v6, v7);
}

static void WiFi2DCharBackground_CopyTilemapRect(BgConfig *param0, u8 param1, u8 param2, u8 param3, u8 param4, u8 param5, const void *param6, u8 param7, u8 param8, u8 param9, u8 param10)
{
    s8 v0, v1;
    s8 v2, v3;
    const u16 *v4;
    WiFi2DCharPosition v5;
    s8 v6, v7;
    u8 v8;
    s8 v9, v10;

    v8 = WiFi2DCharBackground_GetQuadrant(param9, param10);

    if (v8 == 0) {
        Bg_CopyToTilemapRect(param0, param1, param2, param3, param4, param5, param6, param7, param8, param9, param10);
        return;
    }

    v1 = param5;

    while (v1 > 0) {
        if ((((param8) % 32) + v1) <= 32) {
            v3 = v1;
            v1 = 0;
        } else {
            v3 = 32 - (param8 % 32);
            v1 -= v3;
        }

        v7 = param8 / 32;
        v0 = param4;
        v9 = param7;
        v10 = param2;

        while (v0 > 0) {
            if ((((v9) % 32) + v0) <= 32) {
                v2 = v0;
                v0 = 0;
            } else {
                v2 = 32 - (v9 % 32);
                v0 -= v2;
            }

            v6 = v9 / 32;
            v4 = WiFi2DCharBackground_GetQuadrantData(param6, v6, v7, v8, param9, param10, &v5);

            Bg_CopyToTilemapRect(param0, param1, v10, param3, v2, v3, v4, v9 % 32, param8 % 32, v5.x, v5.y);

            v9 += v2;
            v10 += v2;
        }

        param8 += v3;
        param3 += v3;
    }
}

static u8 WiFi2DCharBackground_GetQuadrant(u8 param0, u8 param1)
{
    GF_ASSERT(param0 <= 64);
    GF_ASSERT(param1 <= 64);

    if (param0 <= 32) {
        if (param1 <= 32) {
            return 0;
        } else {
            return 2;
        }
    } else {
        if (param1 <= 32) {
            return 1;
        } else {
            return 3;
        }
    }

    GF_ASSERT(FALSE);
    return 0;
}

static const void *WiFi2DCharBackground_GetQuadrantData(const u8 *param0, u8 param1, u8 param2, u8 param3, u8 param4, u8 param5, WiFi2DCharPosition *param6)
{
    s16 v0;
    u16 v1;

    switch (param3) {
    case 0:
        param6->x = param4;
        param6->y = param5;
        return param0;

    case 1:
        if (((param1 + 1) * 32) <= param4) {
            param6->x = 32;
        } else {
            param6->x = param4 - (param1 * 32);
        }

        param6->y = param5;
        v0 = param5 * (2 * 32);

        return &param0[(param1 * v0)];
    case 2:
        param6->x = param4;

        if (((param2 + 1) * 32) <= param5) {
            param6->y = 32;
        } else {
            param6->y = param5 - (param2 * 32);
        }

        v0 = (param4 * 2) * 32;
        return &param0[(param2 * v0)];
    case 3:
        if (((param1 + 1) * 32) <= param4) {
            param6->x = 32;
        } else {
            param6->x = param4 - (param1 * 32);
        }

        if (((param2 + 1) * 32) <= param5) {
            param6->y = 32;
        } else {
            param6->y = param5 - (param2 * 32);
        }

        if (param2 == 0) {
            v1 = 0;

            if (param1 > 0) {
                v1 += (32 * 2) * 32;
            }
        } else {
            v1 = (param4 * 2) * 32;

            if (param1 > 0) {
                v1 += (32 * 2) * param5;
            }
        }
        return &param0[v1];
    default:
        GF_ASSERT(FALSE);
        break;
    }

    GF_ASSERT(FALSE);
    return NULL;
}
