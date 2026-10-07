#include "wifi_2d_char/wifi_2d_char_0222D77C.h"

#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/struct_wifi_2d_char_0222CCB8.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D894.h"

#include "heap.h"

typedef struct WiFi2DCharMoveQueue {
    WiFi2DCharMoveRequest *unk_00;
    u32 unk_04;
    u16 unk_08;
    u16 unk_0A;
} WiFi2DCharMoveQueue;

typedef struct WiFi2DCharEventQueue {
    WiFi2DCharEvent *unk_00;
    u32 unk_04;
    u16 unk_08;
    u16 unk_0A;
} WiFi2DCharEventQueue;

WiFi2DCharMoveQueue *WiFi2DCharMoveQueue_New(u32 param0, enum HeapID heapID)
{
    WiFi2DCharMoveQueue *v0 = Heap_Alloc(heapID, sizeof(WiFi2DCharMoveQueue));
    GF_ASSERT(v0);

    v0->unk_04 = param0 + 1;
    v0->unk_00 = Heap_Alloc(heapID, sizeof(WiFi2DCharMoveRequest) * v0->unk_04);

    memset(v0->unk_00, 0, sizeof(WiFi2DCharMoveRequest) * v0->unk_04);

    v0->unk_08 = 0;
    v0->unk_0A = 0;

    return v0;
}

void WiFi2DCharMoveQueue_Free(WiFi2DCharMoveQueue *param0)
{
    Heap_Free(param0->unk_00);
    Heap_Free(param0);
}

void WiFi2DCharMoveQueue_Push(WiFi2DCharMoveQueue *param0, const WiFi2DCharMoveRequest *param1)
{
    if (((param0->unk_0A + 1) % param0->unk_04) == param0->unk_08) {
        WiFi2DCharMoveRequest v0;
        WiFi2DCharMoveQueue_Pop(param0, &v0);
    }

    param0->unk_00[param0->unk_0A] = *param1;
    param0->unk_0A = (param0->unk_0A + 1) % param0->unk_04;
}

BOOL WiFi2DCharMoveQueue_Pop(WiFi2DCharMoveQueue *param0, WiFi2DCharMoveRequest *param1)
{
    if (param0->unk_0A == param0->unk_08) {
        return 0;
    }

    *param1 = param0->unk_00[param0->unk_08];
    param0->unk_08 = (param0->unk_08 + 1) % param0->unk_04;

    return 1;
}

WiFi2DCharEventQueue *WiFi2DCharEventQueue_New(u32 param0, enum HeapID heapID)
{
    WiFi2DCharEventQueue *v0 = Heap_Alloc(heapID, sizeof(WiFi2DCharEventQueue));
    GF_ASSERT(v0);

    v0->unk_04 = param0 + 1;
    v0->unk_00 = Heap_Alloc(heapID, sizeof(WiFi2DCharEvent) * v0->unk_04);

    memset(v0->unk_00, 0, sizeof(WiFi2DCharEvent) * v0->unk_04);

    v0->unk_08 = 0;
    v0->unk_0A = 0;

    return v0;
}

void WiFi2DCharEventQueue_Free(WiFi2DCharEventQueue *param0)
{
    Heap_Free(param0->unk_00);
    Heap_Free(param0);
}

void WiFi2DCharEventQueue_Push(WiFi2DCharEventQueue *param0, const WiFi2DCharEvent *param1)
{
    if (((param0->unk_0A + 1) % param0->unk_04) == param0->unk_08) {
        WiFi2DCharEvent v0;
        WiFi2DCharEventQueue_Pop(param0, &v0);
    }

    param0->unk_00[param0->unk_0A] = *param1;
    param0->unk_0A = (param0->unk_0A + 1) % param0->unk_04;
}

BOOL WiFi2DCharEventQueue_Pop(WiFi2DCharEventQueue *param0, WiFi2DCharEvent *param1)
{
    if (param0->unk_0A == param0->unk_08) {
        return 0;
    }

    *param1 = param0->unk_00[param0->unk_08];
    param0->unk_08 = (param0->unk_08 + 1) % param0->unk_04;

    return 1;
}
