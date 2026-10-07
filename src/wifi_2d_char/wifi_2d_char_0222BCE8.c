#include "wifi_2d_char/wifi_2d_char_0222BCE8.h"

#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/union_wifi_2d_char_0222BDAC.h"

#include "heap.h"

typedef struct WiFi2DCharGrid {
    u16 unk_00;
    u16 unk_02;
    WiFi2DCharTile *unk_04;
} WiFi2DCharGrid;

WiFi2DCharGrid *WiFi2DCharGrid_New(u16 param0, u16 param1, enum HeapID heapID)
{
    WiFi2DCharGrid *v0 = Heap_Alloc(heapID, sizeof(WiFi2DCharGrid));
    GF_ASSERT(v0);

    v0->unk_00 = param0;
    v0->unk_02 = param1;

    v0->unk_04 = Heap_Alloc(heapID, sizeof(WiFi2DCharTile) * (v0->unk_00 * v0->unk_02));
    GF_ASSERT(v0->unk_04);
    memset(v0->unk_04, 0, sizeof(WiFi2DCharTile) * (v0->unk_00 * v0->unk_02));

    return v0;
}

void WiFi2DCharGrid_Free(WiFi2DCharGrid *param0)
{
    GF_ASSERT(param0);
    Heap_Free(param0->unk_04);
    Heap_Free(param0);
}

u16 WiFi2DCharGrid_GetWidth(const WiFi2DCharGrid *param0)
{
    return param0->unk_00;
}

u16 WiFi2DCharGrid_GetHeight(const WiFi2DCharGrid *param0)
{
    return param0->unk_02;
}

void WiFi2DCharGrid_SetTiles(WiFi2DCharGrid *param0, const WiFi2DCharTile *param1)
{
    GF_ASSERT(param0);
    memcpy(param0->unk_04, param1, sizeof(WiFi2DCharTile) * (param0->unk_00 * param0->unk_02));
}

WiFi2DCharTile WiFi2DCharGrid_GetTile(const WiFi2DCharGrid *param0, u16 param1, u16 param2)
{
    WiFi2DCharTile v0 = { 0xffffffff };

    GF_ASSERT(param0);

    if ((param0->unk_00 > param1) && (param0->unk_02 > param2)) {
        v0 = param0->unk_04[(param0->unk_00 * param2) + param1];
    }

    return v0;
}

BOOL WiFi2DCharGrid_IsTileBlocked(const WiFi2DCharGrid *param0, u16 param1, u16 param2)
{
    WiFi2DCharTile v0;

    GF_ASSERT(param0);

    v0 = WiFi2DCharGrid_GetTile(param0, param1, param2);

    if (v0.val1 == 0xffffffff) {
        return 1;
    }

    return v0.val2_0;
}

u32 WiFi2DCharGrid_GetTileFlags(const WiFi2DCharGrid *param0, u16 param1, u16 param2)
{
    WiFi2DCharTile v0;

    GF_ASSERT(param0);

    v0 = WiFi2DCharGrid_GetTile(param0, param1, param2);

    if (v0.val1 == 0xffffffff) {
        return 0;
    }

    return v0.val2_1;
}
