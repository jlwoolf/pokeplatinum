#include "fieldmap/fieldmap_021ECC20.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"
#include "struct_decls/map_object_manager.h"

#include "fieldmap/object_event_gfx_data.h"
#include "fieldmap/fieldmap_021ECE40.h"
#include "fieldmap/struct_fieldmap_021ED0A4.h"

#include "heap.h"
#include "map_object.h"
#include "narc.h"

static void FieldMap_021ECCA4(MapObjectManager *param0);
static void FieldMap_021ECCBC(MapObjectManager *param0);
static const ObjectEventGfxRenderDetailsEntry *FieldMap_021ECD10(int param0);

void FieldMap_021ECC20(MapObjectManager *param0, int param1, int param2, const int *param3, int param4)
{
    int v0, v1;
    UnkStruct_fieldmap_021ED0A4 *v2;

    GF_ASSERT(MapObjectMan_CheckStatus(param0, (1 << 0)) == 0);

    FieldMap_021ECCA4(param0);

    v0 = MapObjectMan_GetMaxObjects(param0);
    v1 = MapObjectMan_GetTaskBasePriority(param0) - 1;
    v2 = MapObjectMan_GetDrawManager(param0);

    FieldMap_021ECE40(v2, param0, v0, v1, param1, param2, param3, param4);
    MapObjectMan_SetStatusFlagOn(param0, (1 << 0));
}

void FieldMap_021ECC78(MapObjectManager *param0)
{
    int v0 = MapObjectMan_IsDrawInitialized(param0);
    GF_ASSERT(v0 == 1);

    FieldMap_021ECE94(MapObjectMan_GetDrawManager(param0));

    MapObjectMan_SetStatusFlagOff(param0, (1 << 0));
    FieldMap_021ECCBC(param0);
}

static void FieldMap_021ECCA4(MapObjectManager *param0)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_DATA__MMODEL__MMODEL, HEAP_ID_FIELD1);
    MapObjectMan_SetNARC(param0, v0);
}

static void FieldMap_021ECCBC(MapObjectManager *param0)
{
    NARC *v0 = MapObjectMan_GetNARC(param0);
    NARC_dtor(v0);
}

void MapObject_Draw(MapObject *param0)
{
    const MapObjectManager *v0 = MapObject_MapObjectManager(param0);

    if (MapObjectMan_CheckStatus(v0, (1 << 2))) {
        return;
    }

    if (!MapObject_CheckStatus(param0, MAP_OBJ_STATUS_14)) {
        return;
    }

    if ((MapObject_IsMovementPaused(param0) == 0) || MapObject_CheckStatus4(param0)) {
        MapObject_CallRendererDraw(param0);
    }
}

const ObjectEventGfxRenderDetailsEntry *FieldMap_021ECD04(const MapObject *param0)
{
    int v0 = MapObject_GetGraphicsID(param0);
    const ObjectEventGfxRenderDetailsEntry *v1 = FieldMap_021ECD10(v0);

    return v1;
}

static const ObjectEventGfxRenderDetailsEntry *FieldMap_021ECD10(int param0)
{
    const ObjectEventGfxRenderDetailsEntry *v0 = gObjectEventGfxRenderDetailsTable;

    do {
        if (v0->graphicsID == param0) {
            return v0;
        }

        v0++;
    } while (v0->graphicsID != 0xffff);

    GF_ASSERT(FALSE);
    return NULL;
}

int FieldMap_021ECD38(const MapObject *param0)
{
    if (MapObject_IsMovementPaused(param0) == 1) {
        if (MapObject_CheckStatus4(param0) == 0) {
            return 1;
        }
    }

    if (MapObject_CheckStatus(param0, MAP_OBJ_STATUS_PAUSE_ANIMATION)) {
        return 1;
    }

    return 0;
}

void *FieldMap_021ECD68(const MapObjectManager *param0, u32 param1, int param2)
{
    void *v0;
    NARC *v1 = MapObjectMan_GetNARC(param0);
    u32 v2 = NARC_GetMemberSize(v1, param1);

    if (param2 == 1) {
        v0 = Heap_Alloc(HEAP_ID_FIELD1, v2);
    } else {
        v0 = Heap_AllocAtEnd(HEAP_ID_FIELD1, v2);
    }

    NARC_ReadWholeMember(v1, param1, v0);

    return v0;
}

void FieldMap_021ECDA0(const MapObject *param0, VecFx32 *adjustedObjectPos)
{
    VecFx32 objectPosition, jumpOffset, posOffset, terrainSpriteOffset;

    MapObject_GetPosPtr(param0, &objectPosition);
    MapObject_GetSpriteJumpOffset(param0, &jumpOffset);
    MapObject_GetSpritePosOffset(param0, &posOffset);
    MapObject_GetSpriteTerrainOffset(param0, &terrainSpriteOffset);

    adjustedObjectPos->x = objectPosition.x + jumpOffset.x + posOffset.x + terrainSpriteOffset.x;
    adjustedObjectPos->y = objectPosition.y + jumpOffset.y + posOffset.y + terrainSpriteOffset.y;
    adjustedObjectPos->z = objectPosition.z + jumpOffset.z + posOffset.z + terrainSpriteOffset.z;
}

void FieldMap_021ECDFC(MapObject *mapObj, int dir)
{
    MapObject_TryFace(mapObj, dir);

    if (MapObject_CheckStatus14(mapObj) == 1) {
        MapObject_CallRendererDraw(mapObj);
    }
}

void FieldMap_021ECE18(MapObject *param0)
{
    MapObject_SetHidden(param0, 1);
    MapObject_SetStatusFlagOn(param0, MAP_OBJ_STATUS_HIDE_SHADOW);
}

void FieldMap_021ECE30(MapObject *param0)
{
    return;
}

void FieldMap_021ECE34(MapObject *param0)
{
    return;
}

void FieldMap_021ECE38(MapObject *param0)
{
    return;
}

void FieldMap_021ECE3C(MapObject *param0)
{
    return;
}
