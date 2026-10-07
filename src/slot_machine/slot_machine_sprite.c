#include "slot_machine/slot_machine_sprite.h"

#include <nitro.h>
#include <string.h>

#include "slot_machine/struct_slot_machine_sprite.h"

#include "cell_transfer.h"
#include "heap.h"
#include "narc.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "vram_transfer.h"

typedef struct {
    u16 unk_00;
    u16 unk_02;
    SpriteResource *unk_04;
} SlotMachineSpriteResource;

typedef struct SlotMachineSpriteManager_t {
    enum HeapID heapID;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
    SpriteList *unk_0C;
    G2dRenderer unk_10;
    NNSG2dCellTransferState *unk_19C;
    SpriteResourceCollection *unk_1A0;
    SpriteResourceCollection *unk_1A4;
    SpriteResourceCollection *unk_1A8;
    SpriteResourceCollection *unk_1AC;
    SlotMachineSpriteResource *unk_1B0;
    SlotMachineSpriteResource *unk_1B4;
    SlotMachineSpriteResource *unk_1B8;
    SlotMachineSpriteResource *unk_1BC;
} SlotMachineSpriteManager;

SlotMachineSpriteManager *SlotMachineSprite_New(u32 heapID, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10)
{
    SlotMachineSpriteManager *v0 = Heap_Alloc(heapID, (sizeof(SlotMachineSpriteManager)));

    GF_ASSERT(v0 != NULL);

    v0->heapID = heapID;
    v0->unk_04 = param3;
    v0->unk_05 = param4;
    v0->unk_06 = param5;
    v0->unk_07 = param6;
    v0->unk_08 = param7;
    v0->unk_09 = param8;
    v0->unk_0A = param9;
    v0->unk_0B = param10;
    v0->unk_0C = SpriteList_InitRendering(param1, &v0->unk_10, heapID);
    v0->unk_19C = CellTransfer_New(param2, heapID);

    VramTransfer_New(param2, heapID);

    v0->unk_1A0 = SpriteResourceCollection_New(param3, 0, heapID);
    v0->unk_1A4 = SpriteResourceCollection_New(param4, 1, heapID);
    v0->unk_1A8 = SpriteResourceCollection_New(param5, 2, heapID);
    v0->unk_1AC = SpriteResourceCollection_New(param6, 3, heapID);
    v0->unk_1B0 = Heap_Alloc(heapID, (sizeof(SlotMachineSpriteResource)) * param3);
    v0->unk_1B4 = Heap_Alloc(heapID, (sizeof(SlotMachineSpriteResource)) * param4);
    v0->unk_1B8 = Heap_Alloc(heapID, (sizeof(SlotMachineSpriteResource)) * param5);
    v0->unk_1BC = Heap_Alloc(heapID, (sizeof(SlotMachineSpriteResource)) * param6);

    {
        u32 v1;

        for (v1 = 0; v1 < param3; v0->unk_1B0[v1].unk_00 = param7, v1++) {
            (void)0;
        }

        for (v1 = 0; v1 < param4; v0->unk_1B4[v1].unk_00 = param8, v1++) {
            (void)0;
        }

        for (v1 = 0; v1 < param5; v0->unk_1B8[v1].unk_00 = param9, v1++) {
            (void)0;
        }

        for (v1 = 0; v1 < param6; v0->unk_1BC[v1].unk_00 = param10, v1++) {
            (void)0;
        }
    }

    return v0;
}

void SlotMachineSprite_Free(SlotMachineSpriteManager *param0)
{
    u32 v0;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        if (param0->unk_1B0[v0].unk_00 != param0->unk_08) {
            SpriteTransfer_ResetCharTransfer(param0->unk_1B0[v0].unk_04);
        }
    }

    for (v0 = 0; v0 < param0->unk_05; v0++) {
        if (param0->unk_1B4[v0].unk_00 != param0->unk_09) {
            SpriteTransfer_ResetPlttTransfer(param0->unk_1B4[v0].unk_04);
        }
    }

    for (v0 = 0; v0 < param0->unk_06; v0++) {
        if (param0->unk_1B8[v0].unk_00 != param0->unk_0A) {
            SpriteResource_ReleaseData(param0->unk_1B8[v0].unk_04);
        }
    }

    for (v0 = 0; v0 < param0->unk_07; v0++) {
        if (param0->unk_1BC[v0].unk_00 != param0->unk_0B) {
            SpriteResource_ReleaseData(param0->unk_1BC[v0].unk_04);
        }
    }

    SpriteResourceCollection_Delete(param0->unk_1A0);
    SpriteResourceCollection_Delete(param0->unk_1A4);
    SpriteResourceCollection_Delete(param0->unk_1A8);
    SpriteResourceCollection_Delete(param0->unk_1AC);
    Heap_Free(param0->unk_1B0);
    Heap_Free(param0->unk_1B4);
    Heap_Free(param0->unk_1B8);
    Heap_Free(param0->unk_1BC);
    VramTransfer_Free();
    CellTransfer_Free(param0->unk_19C);
    SpriteList_DeleteAll(param0->unk_0C);
    SpriteList_Delete(param0->unk_0C);
    Heap_Free(param0);
}

void SlotMachineSprite_Update(SlotMachineSpriteManager *param0)
{
    SpriteList_Update(param0->unk_0C);
    CellTransfer_Update();
}

void SlotMachineSprite_AddTiles(SlotMachineSpriteManager *param0, u32 param1, NARC *param2, u32 param3, u32 param4)
{
    u32 v0;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        if (param0->unk_1B0[v0].unk_00 == param0->unk_08) {
            param0->unk_1B0[v0].unk_00 = param4;
            param0->unk_1B0[v0].unk_02 = 0;
            param0->unk_1B0[v0].unk_04 = SpriteResourceCollection_AddTilesFrom(param0->unk_1A0, param2, param3, 0, param4, param1, param0->heapID);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_RequestChar(SlotMachineSpriteManager *param0, u32 param1)
{
    u32 v0;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        if (param0->unk_1B0[v0].unk_00 == param1) {
            SpriteTransfer_RequestCharAtEnd(param0->unk_1B0[v0].unk_04);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_ReleaseChar(SlotMachineSpriteManager *param0, u32 param1)
{
    u32 v0;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        if (param0->unk_1B0[v0].unk_00 == param1) {
            SpriteResource_ReleaseData(param0->unk_1B0[v0].unk_04);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_AddPalette(SlotMachineSpriteManager *param0, u32 param1, NARC *param2, u32 param3, u32 param4)
{
    u32 v0;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        if (param0->unk_1B4[v0].unk_00 == param0->unk_09) {
            param0->unk_1B4[v0].unk_00 = param4;
            param0->unk_1B4[v0].unk_02 = 0;
            param0->unk_1B4[v0].unk_04 = SpriteResourceCollection_AddPaletteFrom(param0->unk_1A4, param2, param3, 0, param4, param1, 1, param0->heapID);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_RequestPltt(SlotMachineSpriteManager *param0, u32 param1)
{
    u32 v0;

    for (v0 = 0; v0 < param0->unk_05; v0++) {
        if (param0->unk_1B4[v0].unk_00 == param1) {
            SpriteTransfer_RequestPlttFreeSpace(param0->unk_1B4[v0].unk_04);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_ReleasePltt(SlotMachineSpriteManager *param0, u32 param1)
{
    u32 v0;

    for (v0 = 0; v0 < param0->unk_05; v0++) {
        if (param0->unk_1B4[v0].unk_00 == param1) {
            SpriteResource_ReleaseData(param0->unk_1B4[v0].unk_04);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_AddCell(SlotMachineSpriteManager *param0, NARC *param1, u32 param2, u32 param3)
{
    u32 v0;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        if (param0->unk_1B8[v0].unk_00 == param0->unk_0A) {
            param0->unk_1B8[v0].unk_00 = param3;
            param0->unk_1B8[v0].unk_02 = 0;
            param0->unk_1B8[v0].unk_04 = SpriteResourceCollection_AddFrom(param0->unk_1A8, param1, param2, 0, param3, 2, param0->heapID);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_AddAnim(SlotMachineSpriteManager *param0, NARC *param1, u32 param2, u32 param3)
{
    u32 v0;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        if (param0->unk_1BC[v0].unk_00 == param0->unk_0B) {
            param0->unk_1BC[v0].unk_00 = param3;
            param0->unk_1BC[v0].unk_02 = 0;
            param0->unk_1BC[v0].unk_04 = SpriteResourceCollection_AddFrom(param0->unk_1AC, param1, param2, 0, param3, 3, param0->heapID);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_RemoveResources(SlotMachineSpriteManager *param0, u32 param1, u32 param2, u32 param3, u32 param4)
{
    u32 v0;

    if (param1 != param0->unk_08) {
        for (v0 = 0; v0 < param0->unk_04; v0++) {
            if (param0->unk_1B0[v0].unk_00 == param1) {
                SpriteTransfer_ResetCharTransfer(param0->unk_1B0[v0].unk_04);
                SpriteResourceCollection_Remove(param0->unk_1A0, param0->unk_1B0[v0].unk_04);
                param0->unk_1B0[v0].unk_00 = param0->unk_08;
                break;
            }
        }
    }

    if (param2 != param0->unk_09) {
        for (v0 = 0; v0 < param0->unk_05; v0++) {
            if (param0->unk_1B4[v0].unk_00 == param2) {
                SpriteTransfer_ResetPlttTransfer(param0->unk_1B4[v0].unk_04);
                SpriteResourceCollection_Remove(param0->unk_1A4, param0->unk_1B4[v0].unk_04);
                param0->unk_1B4[v0].unk_00 = param0->unk_09;
                break;
            }
        }
    }

    if (param3 != param0->unk_0A) {
        for (v0 = 0; v0 < param0->unk_06; v0++) {
            if (param0->unk_1B8[v0].unk_00 == param3) {
                SpriteResource_ReleaseData(param0->unk_1B8[v0].unk_04);
                SpriteResourceCollection_Remove(param0->unk_1A8, param0->unk_1B8[v0].unk_04);
                param0->unk_1B8[v0].unk_00 = param0->unk_0A;
                break;
            }
        }
    }

    if (param4 != param0->unk_0B) {
        for (v0 = 0; v0 < param0->unk_07; v0++) {
            if (param0->unk_1BC[v0].unk_00 == param4) {
                SpriteResource_ReleaseData(param0->unk_1BC[v0].unk_04);
                SpriteResourceCollection_Remove(param0->unk_1AC, param0->unk_1BC[v0].unk_04);
                param0->unk_1BC[v0].unk_00 = param0->unk_0B;
                break;
            }
        }
    }
}

void SlotMachineSprite_CreateSprite(SlotMachineSpriteManager *param0, SlotMachineSprite *param1, const VecFx32 *param2, u32 param3, int param4, u32 param5, u32 param6, u32 param7, u32 param8, int param9, int param10)
{
    SpriteResourcesHeader v0;
    SpriteListTemplate v1;
    Sprite *v2;

    if (param8 == param0->unk_0B) {
        param8 = 0xffffffff;
    }

    SpriteResourcesHeader_Init(
        &v0, param5, param6, param7, param8, 0xffffffff, 0xffffffff, param4, param9, param0->unk_1A0, param0->unk_1A4, param0->unk_1A8, param0->unk_1AC, NULL, NULL);

    if (param4 == 1) {
        param1->unk_08 = v0.imageProxy;
        param1->unk_00 = 1;
    } else {
        param1->unk_00 = 0;
    }

    v1.list = param0->unk_0C;
    v1.resourceData = &v0;
    v1.position = *param2;
    v1.priority = param10;
    v1.vramType = param3;
    v1.heapID = param0->heapID;

    param1->unk_04 = SpriteList_Add(&v1);
    GF_ASSERT(param1->unk_04 != NULL);
}

void SlotMachineSprite_DeleteSprite(SlotMachineSprite *param0)
{
    if (param0->unk_00 == 1) {
        SpriteTransfer_DeleteCharTransfer(param0->unk_08);
    }

    Sprite_Delete(param0->unk_04);
    param0->unk_04 = NULL;
}

void SlotMachineSprite_GetPosition(Sprite *param0, VecFx32 *param1)
{
    const VecFx32 *v0 = Sprite_GetPosition(param0);
    *param1 = *v0;
}

void SlotMachineSprite_GetScale(Sprite *param0, VecFx32 *param1)
{
    const VecFx32 *v0 = Sprite_GetAffineScale(param0);
    *param1 = *v0;
}
