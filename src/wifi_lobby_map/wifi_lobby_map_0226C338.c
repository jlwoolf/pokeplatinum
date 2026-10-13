#include "wifi_lobby_map/wifi_lobby_map_0226C338.h"

#include <nitro.h>
#include <string.h>

#include "heap.h"

typedef struct {
    GXRgb ambientColor;
    GXRgb lightColors[4];
} WiFiLobbyMapLightPalette;

typedef struct {
    GXRgb color;
} WiFiLobbyMapLightColor;

typedef struct {
    s8 rgb[4];
} WiFiLobbyMapColor;

typedef struct {
    WiFiLobbyMapColor lightColors[2];
    WiFiLobbyMapColor materialColors[4];
} WiFiLobbyMapLightColors;

typedef struct WiFiLobbyMapLighting_t {
    WiFiLobbyMapLightColors current;
    WiFiLobbyMapLightColors start;
    WiFiLobbyMapLightColors target;
    s32 lightProgress[2];
    s32 materialProgress[4];
} WiFiLobbyMapLighting;

static void wifi_lobby_map_0226C4CC(const WiFiLobbyMapColor *param0, GXRgb *param1);
static void wifi_lobby_map_0226C4E8(WiFiLobbyMapColor *param0, const GXRgb *param1);
static void wifi_lobby_map_0226C50C(const WiFiLobbyMapColor *param0, const WiFiLobbyMapColor *param1, WiFiLobbyMapColor *param2, s32 param3, s32 param4);
static void wifi_lobby_map_0226C568(WiFiLobbyMapLightColors *param0, const WiFiLobbyMapLightPalette *param1);
static void wifi_lobby_map_0226C58C(WiFiLobbyMapLightColors *param0, const WiFiLobbyMapLightColor *param1);
static void wifi_lobby_map_0226C598(const WiFiLobbyMapLightColors *param0);

static const WiFiLobbyMapLightPalette Unk_wifi_lobby_map_0226E678[6] = {
    { GX_RGB(23, 23, 25),
        {
            GX_RGB(16, 16, 16),
            GX_RGB(14, 14, 14),
            GX_RGB(20, 20, 20),
            GX_RGB(16, 16, 16),
        } },
    { GX_RGB(10, 10, 16),
        {
            GX_RGB(16, 16, 16),
            GX_RGB(14, 14, 14),
            GX_RGB(20, 20, 20),
            GX_RGB(16, 16, 16),
        } },
    { GX_RGB(8, 8, 12),
        {
            GX_RGB(16, 16, 16),
            GX_RGB(14, 14, 14),
            GX_RGB(20, 20, 20),
            GX_RGB(16, 16, 16),
        } },
    { GX_RGB(5, 5, 8),
        {
            GX_RGB(16, 16, 16),
            GX_RGB(13, 13, 14),
            GX_RGB(20, 20, 20),
            GX_RGB(16, 16, 16),
        } },
    {
        GX_RGB(3, 3, 7),
        {
            GX_RGB(16, 16, 16),
            GX_RGB(10, 10, 12),
            GX_RGB(20, 20, 20),
            GX_RGB(14, 14, 16),
        },
    },
    {
        GX_RGB(0, 0, 6),
        {
            GX_RGB(16, 16, 16),
            GX_RGB(8, 8, 10),
            GX_RGB(20, 20, 20),
            GX_RGB(12, 12, 16),
        },
    },
};

static const WiFiLobbyMapLightColor Unk_wifi_lobby_map_0226E670[4] = {
    { GX_RGB(14, 14, 14) },
    { GX_RGB(20, 20, 20) },
    { GX_RGB(31, 31, 31) },
    { GX_RGB(8, 8, 8) },
};

WiFiLobbyMapLighting *wifi_lobby_map_0226C338(u32 heapID, int param1, int param2, int param3)
{
    WiFiLobbyMapLighting *v0;
    int v1;

    v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMapLighting));
    memset(v0, 0, sizeof(WiFiLobbyMapLighting));

    wifi_lobby_map_0226C568(&v0->current, &Unk_wifi_lobby_map_0226E678[param1]);
    wifi_lobby_map_0226C58C(&v0->current, &Unk_wifi_lobby_map_0226E670[param2]);

    for (v1 = 0; v1 < 2; v1++) {
        v0->lightProgress[v1] = 60;
    }

    for (v1 = 0; v1 < 4; v1++) {
        v0->materialProgress[v1] = 60;
    }

    wifi_lobby_map_0226C598(&v0->current);

    return v0;
}

void wifi_lobby_map_0226C39C(WiFiLobbyMapLighting *param0)
{
    Heap_Free(param0);
}

void wifi_lobby_map_0226C3A4(WiFiLobbyMapLighting *param0)
{
    int v0;
    BOOL v1 = 0;

    for (v0 = 0; v0 < 2; v0++) {
        if ((param0->lightProgress[v0] + 1) <= 60) {
            param0->lightProgress[v0]++;
            wifi_lobby_map_0226C50C(&param0->start.lightColors[v0], &param0->target.lightColors[v0], &param0->current.lightColors[v0], param0->lightProgress[v0], 60);
            v1 = 1;
        }
    }

    for (v0 = 0; v0 < 4; v0++) {
        if ((param0->materialProgress[v0] + 1) <= 60) {
            param0->materialProgress[v0]++;
            wifi_lobby_map_0226C50C(&param0->start.materialColors[v0], &param0->target.materialColors[v0], &param0->current.materialColors[v0], param0->materialProgress[v0], 60);
            v1 = 1;
        }
    }

    if (v1) {
        wifi_lobby_map_0226C598(&param0->current);
    }
}

void wifi_lobby_map_0226C430(WiFiLobbyMapLighting *param0, int param1)
{
    int v0;

    param0->start.lightColors[0] = param0->current.lightColors[0];
    param0->lightProgress[0] = 0;

    wifi_lobby_map_0226C4E8(&param0->target.lightColors[0], &Unk_wifi_lobby_map_0226E678[param1].ambientColor);

    for (v0 = 0; v0 < 4; v0++) {
        param0->start.materialColors[v0] = param0->current.materialColors[v0];
        param0->materialProgress[v0] = 0;

        wifi_lobby_map_0226C4E8(&param0->target.materialColors[v0], &Unk_wifi_lobby_map_0226E678[param1].lightColors[v0]);
    }
}

void wifi_lobby_map_0226C4A0(WiFiLobbyMapLighting *param0, int param1)
{
    param0->start.lightColors[1] = param0->current.lightColors[1];
    param0->lightProgress[1] = 0;

    wifi_lobby_map_0226C4E8(&param0->target.lightColors[1], &Unk_wifi_lobby_map_0226E670[param1].color);
}

void wifi_lobby_map_0226C4C8(WiFiLobbyMapLighting *param0, int param1)
{
    return;
}

static void wifi_lobby_map_0226C4CC(const WiFiLobbyMapColor *param0, GXRgb *param1)
{
    *param1 = GX_RGB(param0->rgb[0], param0->rgb[1], param0->rgb[2]);
}

static void wifi_lobby_map_0226C4E8(WiFiLobbyMapColor *param0, const GXRgb *param1)
{
    param0->rgb[0] = ((*param1) & GX_RGB_R_MASK) >> GX_RGB_R_SHIFT;
    param0->rgb[1] = ((*param1) & GX_RGB_G_MASK) >> GX_RGB_G_SHIFT;
    param0->rgb[2] = ((*param1) & GX_RGB_B_MASK) >> GX_RGB_B_SHIFT;
}

static void wifi_lobby_map_0226C50C(const WiFiLobbyMapColor *param0, const WiFiLobbyMapColor *param1, WiFiLobbyMapColor *param2, s32 param3, s32 param4)
{
    s32 v0;
    s32 v1;
    s32 v2;

    v0 = param1->rgb[0] - param0->rgb[0];
    v1 = param1->rgb[1] - param0->rgb[1];
    v2 = param1->rgb[2] - param0->rgb[2];

    param2->rgb[0] = param0->rgb[0] + ((param3 * v0) / param4);
    param2->rgb[1] = param0->rgb[1] + ((param3 * v1) / param4);
    param2->rgb[2] = param0->rgb[2] + ((param3 * v2) / param4);
}

static void wifi_lobby_map_0226C568(WiFiLobbyMapLightColors *param0, const WiFiLobbyMapLightPalette *param1)
{
    int v0;

    wifi_lobby_map_0226C4E8(&param0->lightColors[0], &param1->ambientColor);

    for (v0 = 0; v0 < 4; v0++) {
        wifi_lobby_map_0226C4E8(&param0->materialColors[v0], &param1->lightColors[v0]);
    }
}

static void wifi_lobby_map_0226C58C(WiFiLobbyMapLightColors *param0, const WiFiLobbyMapLightColor *param1)
{
    wifi_lobby_map_0226C4E8(&param0->lightColors[1], &param1->color);
}

static void wifi_lobby_map_0226C598(const WiFiLobbyMapLightColors *param0)
{
    int v0;
    GXRgb v1, v2;

    for (v0 = 0; v0 < 2; v0++) {
        wifi_lobby_map_0226C4CC(&param0->lightColors[v0], &v1);
        NNS_G3dGlbLightColor(v0, v1);
    }

    wifi_lobby_map_0226C4CC(&param0->materialColors[0], &v1);
    wifi_lobby_map_0226C4CC(&param0->materialColors[1], &v2);

    NNS_G3dGlbMaterialColorDiffAmb(v1, v2, 0);

    wifi_lobby_map_0226C4CC(&param0->materialColors[2], &v1);
    wifi_lobby_map_0226C4CC(&param0->materialColors[3], &v2);

    NNS_G3dGlbMaterialColorSpecEmi(v1, v2, 0);
}
