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
    u16 resourceID;
    u16 unk_02;
    SpriteResource *resource;
} SlotMachineSpriteResource;

typedef struct SlotMachineSpriteManager_t {
    enum HeapID heapID;
    u8 maxCharCount;
    u8 maxPlttCount;
    u8 maxCellCount;
    u8 maxAnimCount;
    u8 freeCharID;
    u8 freePlttID;
    u8 freeCellID;
    u8 freeAnimID;
    SpriteList *spriteList;
    G2dRenderer renderer;
    NNSG2dCellTransferState *cellTransfer;
    SpriteResourceCollection *charResources;
    SpriteResourceCollection *plttResources;
    SpriteResourceCollection *cellResources;
    SpriteResourceCollection *animResources;
    SlotMachineSpriteResource *charResourceData;
    SlotMachineSpriteResource *plttResourceData;
    SlotMachineSpriteResource *cellResourceData;
    SlotMachineSpriteResource *animResourceData;
} SlotMachineSpriteManager;

SlotMachineSpriteManager *SlotMachineSprite_New(u32 heapID, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10)
{
    SlotMachineSpriteManager *v0 = Heap_Alloc(heapID, (sizeof(SlotMachineSpriteManager)));

    GF_ASSERT(v0 != NULL);

    v0->heapID = heapID;
    v0->maxCharCount = param3;
    v0->maxPlttCount = param4;
    v0->maxCellCount = param5;
    v0->maxAnimCount = param6;
    v0->freeCharID = param7;
    v0->freePlttID = param8;
    v0->freeCellID = param9;
    v0->freeAnimID = param10;
    v0->spriteList = SpriteList_InitRendering(param1, &v0->renderer, heapID);
    v0->cellTransfer = CellTransfer_New(param2, heapID);

    VramTransfer_New(param2, heapID);

    v0->charResources = SpriteResourceCollection_New(param3, 0, heapID);
    v0->plttResources = SpriteResourceCollection_New(param4, 1, heapID);
    v0->cellResources = SpriteResourceCollection_New(param5, 2, heapID);
    v0->animResources = SpriteResourceCollection_New(param6, 3, heapID);
    v0->charResourceData = Heap_Alloc(heapID, (sizeof(SlotMachineSpriteResource)) * param3);
    v0->plttResourceData = Heap_Alloc(heapID, (sizeof(SlotMachineSpriteResource)) * param4);
    v0->cellResourceData = Heap_Alloc(heapID, (sizeof(SlotMachineSpriteResource)) * param5);
    v0->animResourceData = Heap_Alloc(heapID, (sizeof(SlotMachineSpriteResource)) * param6);

    {
        u32 v1;

        for (v1 = 0; v1 < param3; v0->charResourceData[v1].resourceID = param7, v1++) {
            (void)0;
        }

        for (v1 = 0; v1 < param4; v0->plttResourceData[v1].resourceID = param8, v1++) {
            (void)0;
        }

        for (v1 = 0; v1 < param5; v0->cellResourceData[v1].resourceID = param9, v1++) {
            (void)0;
        }

        for (v1 = 0; v1 < param6; v0->animResourceData[v1].resourceID = param10, v1++) {
            (void)0;
        }
    }

    return v0;
}

void SlotMachineSprite_Free(SlotMachineSpriteManager *param0)
{
    u32 v0;

    for (v0 = 0; v0 < param0->maxCharCount; v0++) {
        if (param0->charResourceData[v0].resourceID != param0->freeCharID) {
            SpriteTransfer_ResetCharTransfer(param0->charResourceData[v0].resource);
        }
    }

    for (v0 = 0; v0 < param0->maxPlttCount; v0++) {
        if (param0->plttResourceData[v0].resourceID != param0->freePlttID) {
            SpriteTransfer_ResetPlttTransfer(param0->plttResourceData[v0].resource);
        }
    }

    for (v0 = 0; v0 < param0->maxCellCount; v0++) {
        if (param0->cellResourceData[v0].resourceID != param0->freeCellID) {
            SpriteResource_ReleaseData(param0->cellResourceData[v0].resource);
        }
    }

    for (v0 = 0; v0 < param0->maxAnimCount; v0++) {
        if (param0->animResourceData[v0].resourceID != param0->freeAnimID) {
            SpriteResource_ReleaseData(param0->animResourceData[v0].resource);
        }
    }

    SpriteResourceCollection_Delete(param0->charResources);
    SpriteResourceCollection_Delete(param0->plttResources);
    SpriteResourceCollection_Delete(param0->cellResources);
    SpriteResourceCollection_Delete(param0->animResources);
    Heap_Free(param0->charResourceData);
    Heap_Free(param0->plttResourceData);
    Heap_Free(param0->cellResourceData);
    Heap_Free(param0->animResourceData);
    VramTransfer_Free();
    CellTransfer_Free(param0->cellTransfer);
    SpriteList_DeleteAll(param0->spriteList);
    SpriteList_Delete(param0->spriteList);
    Heap_Free(param0);
}

void SlotMachineSprite_Update(SlotMachineSpriteManager *param0)
{
    SpriteList_Update(param0->spriteList);
    CellTransfer_Update();
}

void SlotMachineSprite_AddTiles(SlotMachineSpriteManager *param0, u32 param1, NARC *param2, u32 param3, u32 param4)
{
    u32 v0;

    for (v0 = 0; v0 < param0->maxCharCount; v0++) {
        if (param0->charResourceData[v0].resourceID == param0->freeCharID) {
            param0->charResourceData[v0].resourceID = param4;
            param0->charResourceData[v0].unk_02 = 0;
            param0->charResourceData[v0].resource = SpriteResourceCollection_AddTilesFrom(param0->charResources, param2, param3, 0, param4, param1, param0->heapID);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_RequestChar(SlotMachineSpriteManager *param0, u32 param1)
{
    u32 v0;

    for (v0 = 0; v0 < param0->maxCharCount; v0++) {
        if (param0->charResourceData[v0].resourceID == param1) {
            SpriteTransfer_RequestCharAtEnd(param0->charResourceData[v0].resource);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_ReleaseChar(SlotMachineSpriteManager *param0, u32 param1)
{
    u32 v0;

    for (v0 = 0; v0 < param0->maxCharCount; v0++) {
        if (param0->charResourceData[v0].resourceID == param1) {
            SpriteResource_ReleaseData(param0->charResourceData[v0].resource);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_AddPalette(SlotMachineSpriteManager *param0, u32 param1, NARC *param2, u32 param3, u32 param4)
{
    u32 v0;

    for (v0 = 0; v0 < param0->maxCharCount; v0++) {
        if (param0->plttResourceData[v0].resourceID == param0->freePlttID) {
            param0->plttResourceData[v0].resourceID = param4;
            param0->plttResourceData[v0].unk_02 = 0;
            param0->plttResourceData[v0].resource = SpriteResourceCollection_AddPaletteFrom(param0->plttResources, param2, param3, 0, param4, param1, 1, param0->heapID);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_RequestPltt(SlotMachineSpriteManager *param0, u32 param1)
{
    u32 v0;

    for (v0 = 0; v0 < param0->maxPlttCount; v0++) {
        if (param0->plttResourceData[v0].resourceID == param1) {
            SpriteTransfer_RequestPlttFreeSpace(param0->plttResourceData[v0].resource);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_ReleasePltt(SlotMachineSpriteManager *param0, u32 param1)
{
    u32 v0;

    for (v0 = 0; v0 < param0->maxPlttCount; v0++) {
        if (param0->plttResourceData[v0].resourceID == param1) {
            SpriteResource_ReleaseData(param0->plttResourceData[v0].resource);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_AddCell(SlotMachineSpriteManager *param0, NARC *param1, u32 param2, u32 param3)
{
    u32 v0;

    for (v0 = 0; v0 < param0->maxCharCount; v0++) {
        if (param0->cellResourceData[v0].resourceID == param0->freeCellID) {
            param0->cellResourceData[v0].resourceID = param3;
            param0->cellResourceData[v0].unk_02 = 0;
            param0->cellResourceData[v0].resource = SpriteResourceCollection_AddFrom(param0->cellResources, param1, param2, 0, param3, 2, param0->heapID);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_AddAnim(SlotMachineSpriteManager *param0, NARC *param1, u32 param2, u32 param3)
{
    u32 v0;

    for (v0 = 0; v0 < param0->maxCharCount; v0++) {
        if (param0->animResourceData[v0].resourceID == param0->freeAnimID) {
            param0->animResourceData[v0].resourceID = param3;
            param0->animResourceData[v0].unk_02 = 0;
            param0->animResourceData[v0].resource = SpriteResourceCollection_AddFrom(param0->animResources, param1, param2, 0, param3, 3, param0->heapID);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void SlotMachineSprite_RemoveResources(SlotMachineSpriteManager *param0, u32 param1, u32 param2, u32 param3, u32 param4)
{
    u32 v0;

    if (param1 != param0->freeCharID) {
        for (v0 = 0; v0 < param0->maxCharCount; v0++) {
            if (param0->charResourceData[v0].resourceID == param1) {
                SpriteTransfer_ResetCharTransfer(param0->charResourceData[v0].resource);
                SpriteResourceCollection_Remove(param0->charResources, param0->charResourceData[v0].resource);
                param0->charResourceData[v0].resourceID = param0->freeCharID;
                break;
            }
        }
    }

    if (param2 != param0->freePlttID) {
        for (v0 = 0; v0 < param0->maxPlttCount; v0++) {
            if (param0->plttResourceData[v0].resourceID == param2) {
                SpriteTransfer_ResetPlttTransfer(param0->plttResourceData[v0].resource);
                SpriteResourceCollection_Remove(param0->plttResources, param0->plttResourceData[v0].resource);
                param0->plttResourceData[v0].resourceID = param0->freePlttID;
                break;
            }
        }
    }

    if (param3 != param0->freeCellID) {
        for (v0 = 0; v0 < param0->maxCellCount; v0++) {
            if (param0->cellResourceData[v0].resourceID == param3) {
                SpriteResource_ReleaseData(param0->cellResourceData[v0].resource);
                SpriteResourceCollection_Remove(param0->cellResources, param0->cellResourceData[v0].resource);
                param0->cellResourceData[v0].resourceID = param0->freeCellID;
                break;
            }
        }
    }

    if (param4 != param0->freeAnimID) {
        for (v0 = 0; v0 < param0->maxAnimCount; v0++) {
            if (param0->animResourceData[v0].resourceID == param4) {
                SpriteResource_ReleaseData(param0->animResourceData[v0].resource);
                SpriteResourceCollection_Remove(param0->animResources, param0->animResourceData[v0].resource);
                param0->animResourceData[v0].resourceID = param0->freeAnimID;
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

    if (param8 == param0->freeAnimID) {
        param8 = 0xffffffff;
    }

    SpriteResourcesHeader_Init(
        &v0, param5, param6, param7, param8, 0xffffffff, 0xffffffff, param4, param9, param0->charResources, param0->plttResources, param0->cellResources, param0->animResources, NULL, NULL);

    if (param4 == 1) {
        param1->imageProxy = v0.imageProxy;
        param1->hasCharTransfer = 1;
    } else {
        param1->hasCharTransfer = 0;
    }

    v1.list = param0->spriteList;
    v1.resourceData = &v0;
    v1.position = *param2;
    v1.priority = param10;
    v1.vramType = param3;
    v1.heapID = param0->heapID;

    param1->sprite = SpriteList_Add(&v1);
    GF_ASSERT(param1->sprite != NULL);
}

void SlotMachineSprite_DeleteSprite(SlotMachineSprite *param0)
{
    if (param0->hasCharTransfer == 1) {
        SpriteTransfer_DeleteCharTransfer(param0->imageProxy);
    }

    Sprite_Delete(param0->sprite);
    param0->sprite = NULL;
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
