#include "fieldmap/fieldmap_021ECE40.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"
#include "struct_decls/map_object_manager.h"

#include "fieldmap/area_light.h"
#include "fieldmap/field_effect_manager.h"
#include "fieldmap/funcptr_fieldmap_021EE454.h"
#include "fieldmap/object_event_gfx_data.h"
#include "fieldmap/fieldmap_021EB1A0.h"
#include "fieldmap/fieldmap_021ECC20.h"
#include "fieldmap/fieldmap_021F17B8.h"
#include "fieldmap/resource_heap.h"
#include "fieldmap/struct_billboard_anim_state.h"
#include "fieldmap/struct_map_object_draw_manager.h"
#include "fieldmap/struct_map_object_draw_task_manager.h"
#include "fieldmap/struct_map_object_texture_load_task.h"
#include "fieldmap/struct_map_object_texture_manager.h"
#include "fieldmap/struct_map_object_billboard_list.h"

#include "berry_patch_graphics.h"
#include "billboard.h"
#include "enums.h"
#include "heap.h"
#include "map_object.h"
#include "map_object_move.h"
#include "map_tile_behavior.h"
#include "narc.h"
#include "overworld_anim_manager.h"
#include "resource_collection.h"
#include "sys_task.h"
#include "sys_task_manager.h"

typedef enum {
    UnkEnum_FieldMap_021ED334_00 = 0,
    UnkEnum_FieldMap_021ED334_01,
    UnkEnum_FieldMap_021ED334_02,
} UnkEnum_FieldMap_021ED334;

typedef struct {
    int unk_00;
    s16 unk_04;
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    BillboardGfxSequence unk_14;
    Billboard *unk_24;
    BillboardResources unk_28;
    MapObject *unk_50;
    OverworldAnimManager *unk_54;
    void *unk_58;
    UnkFuncPtr_fieldmap_021EE454 unk_5C;
} MapObjectBillboardAnim;

static void FieldMap_021ED094(const MapObject *param0);
static void FieldMap_021ED0A4(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED0F0(MapObjectDrawManager *param0);
static BillboardResources *FieldMap_021ED110(MapObjectDrawManager *param0, u32 param1);
static void FieldMap_021ED184(MapObjectDrawManager *param0, u32 param1);
static void FieldMap_021ED1A4(MapObjectDrawManager *param0);
static int FieldMap_021ED1C8(const MapObjectManager *param0, const MapObject *param1, int param2);
static void FieldMap_021ED224(MapObjectDrawManager *param0, int param1, int param2, int param3, int param4, int param5, int param6);
static void FieldMap_021ED2AC(MapObjectDrawManager *param0);
static const ObjectEventGfxFileEntry *FieldMap_021ED2D0(int param0, int param1, const ObjectEventGfxFileEntry *param2);
static int FieldMap_021ED2E8(MapObjectDrawManager *param0, ResourceHeap *param1, int param2, int param3, const ObjectEventGfxFileEntry *param4);
static UnkEnum_FieldMap_021ED334 FieldMap_021ED334(MapObjectDrawManager *param0, int param1, int param2, const ObjectEventGfxFileEntry *param3);
static UnkEnum_FieldMap_021ED334 FieldMap_021ED390(MapObjectDrawManager *param0, int param1);
static UnkEnum_FieldMap_021ED334 FieldMap_021ED3A4(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED3B8(MapObjectDrawManager *param0, const int *param1);
static void FieldMap_021ED3DC(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED40C(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED43C(MapObjectDrawManager *param0, const int *param1);
static void FieldMap_021ED460(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED490(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED4C0(MapObjectDrawManager *param0, const int *param1);
static void FieldMap_021ED4E4(MapObjectDrawManager *param0, const int *param1, const int *param2, const int *param3);
static void FieldMap_021ED504(int *param0, int param1, int param2);
static int FieldMap_021ED50C(int *param0, int param1, int param2, int param3);
static int FieldMap_021ED528(int *param0, int param1, int param2);
static int FieldMap_021ED53C(int *param0, int param1, int param2, int param3);
static void FieldMap_021ED558(MapObjectDrawManager *param0);
static void FieldMap_021ED56C(MapObjectDrawManager *param0, int param1);
static int FieldMap_021ED598(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED5B4(MapObjectDrawManager *param0, int param1);
static int FieldMap_021ED5E8(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED610(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED63C(MapObjectManager *param0, MapObjectDrawManager *param1);
static void FieldMap_021ED694(MapObjectDrawManager *param0);
static void FieldMap_021ED6A8(MapObjectDrawManager *param0, int param1);
static int FieldMap_021ED6D4(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED6F0(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED74C(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED778(MapObjectManager *param0, MapObjectDrawManager *param1);
static void FieldMap_021ED7D0(MapObjectDrawManager *param0);
static void FieldMap_021ED7E4(MapObjectDrawManager *param0, int param1);
static int FieldMap_021ED810(MapObjectDrawManager *param0, int param1);
static int FieldMap_021ED82C(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED858(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED88C(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED8B8(MapObjectManager *param0, MapObjectDrawManager *param1);
static int FieldMap_021ED924(MapObjectDrawManager *param0, int param1);
static int FieldMap_021ED94C(MapObjectDrawManager *param0, int param1);
static int FieldMap_021ED974(MapObjectDrawManager *param0, int param1);
static int FieldMap_021ED99C(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED9C4(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED9DC(MapObjectDrawManager *param0, int param1);
static void FieldMap_021ED9F4(MapObjectDrawManager *param0, int param1);
static void FieldMap_021EDA0C(MapObjectDrawManager *param0, int param1);
static int FieldMap_021EDA54(const MapObjectManager *param0, int param1, const MapObject *param2);
static int FieldMap_021EDAB4(const MapObjectManager *param0, int param1, const MapObject *param2);
static int FieldMap_021EDB3C(const MapObjectManager *param0, int param1, const MapObject *param2);
static int *FieldMap_021EDCB8(MapObjectDrawManager *param0);
static int *FieldMap_021EDCBC(MapObjectDrawManager *param0);
static int *FieldMap_021EDCC0(MapObjectDrawManager *param0);
static void FieldMap_021EDCC4(MapObjectDrawManager *param0, int param1);
static int FieldMap_021EDCC8(const MapObjectDrawManager *param0);
static void FieldMap_021EDCCC(MapObjectDrawManager *param0, int param1);
static int FieldMap_021EDCD0(const MapObjectDrawManager *param0);
static void FieldMap_021EDCD4(MapObjectDrawManager *param0, int param1);
static int FieldMap_021EDCD8(const MapObjectDrawManager *param0);
static void FieldMap_021EDCDC(MapObjectDrawManager *param0, int param1);
static int FieldMap_021EDCE0(const MapObjectDrawManager *param0);
static void FieldMap_021EDCE4(MapObjectDrawManager *param0, int param1);
static int FieldMap_021EDCE8(const MapObjectDrawManager *param0);
static void FieldMap_021EDCEC(MapObjectDrawManager *param0, int param1);
static int FieldMap_021EDCF0(const MapObjectDrawManager *param0);
static void *FieldMap_021EDCF4(MapObjectDrawManager *param0, u32 param1, int param2);
static const ObjectEventGfxModelAnimEntry *FieldMap_021EDD04(int param0);
static int FieldMap_021EDD2C(int param0);
static int FieldMap_021EDD38(int param0);
static const BillboardAnim *FieldMap_021EDD44(int param0);
static u32 FieldMap_021EDD50(int param0);
static void FieldMap_021EDDAC(MapObjectDrawManager *param0, int param1);
static void FieldMap_021EDDD4(BillboardList *param0);
static Billboard *FieldMap_021EDDDC(BillboardList *param0, const BillboardResources *param1, const VecFx32 *param2, u32 param3);
static void FieldMap_021EDE3C(MapObjectDrawManager *param0, u32 param1, BillboardResources *param2);
static MapObjectDrawManager *FieldMap_021EDEA8(const MapObject *param0);
static int FieldMap_021EDF3C(MapObjectDrawManager *param0, int param1, u32 param2, int param3);
static void FieldMap_021EDFBC(MapObjectDrawManager *param0, int param1);
static int FieldMap_021EDFF0(MapObjectDrawManager *param0, int param1);
static void FieldMap_021EE030(SysTask *param0, void *param1);
static void FieldMap_021EE0E8(MapObjectDrawManager *param0, int param1, void *param2, int param3);
static void FieldMap_021EE134(MapObjectDrawManager *param0, int param1);
static void FieldMap_021EE170(MapObjectDrawManager *param0, int param1);
static void FieldMap_021EE1AC(SysTask *param0, void *param1);
static void FieldMap_021EE1E8(SysTask *param0, void *param1);
static void FieldMap_021EE228(MapObjectDrawManager *param0, MapObject *param1, Billboard **param2, int param3);
static void FieldMap_021EE264(MapObjectDrawManager *param0, const MapObject *param1);
static void FieldMap_021EE2C4(SysTask *param0, void *param1);
static void FieldMap_021EE294(MapObjectDrawManager *param0);
static void FieldMap_021EE2D0(MapObjectDrawManager *param0, MapObjectBillboardList *param1);
static void FieldMap_021EE320(MapObjectDrawManager *param0, int param1, int param2);
static void FieldMap_021EE3C4(MapObjectDrawManager *param0);
static Billboard *FieldMap_021EE454(MapObject *param0, int param1, UnkFuncPtr_fieldmap_021EE454 param2, void *param3);
static void FieldMap_021EE698(SysTask *param0, void *param1);

void FieldMap_021ECE40(MapObjectDrawManager *param0, const MapObjectManager *param1, int param2, int param3, int param4, int param5, const int *param6, int param7)
{
    param0->unk_104 = param1;

    FieldMap_021EDDAC(param0, param2);
    FieldMap_021EE320(param0, param2, param7);
    FieldMap_021ED224(param0, 8, 4, 8, 4, param4, param5);
    FieldMap_021ED0A4(param0, param2);
    FieldMap_021ED4E4(param0, param6, gPreloadedBillboardModels, gPreloadedBillboardFrameSeqs);
}

void FieldMap_021ECE94(MapObjectDrawManager *param0)
{
    FieldMap_021EE3C4(param0);
    FieldMap_021ED0F0(param0);
    FieldMap_021EDDD4(FieldMap_021EDC8C(param0));
    FieldMap_021ED2AC(param0);
}

int FieldMap_021ECEB4(MapObject *param0, Billboard **param1, int param2)
{
    int v0;
    MapObjectDrawManager *v1;

    *param1 = NULL;

    v1 = FieldMap_021EDEA8(param0);
    v0 = FieldMap_021ED82C(v1, param2);

    if (v0 == 0) {
        FieldMap_021ED060(param0, param1, param2);
        return v0;
    }

    if ((v0 == 3) || (v0 == 4)) {
        FieldMap_021EE228(v1, param0, param1, param2);
        return v0;
    }

    *param1 = FieldMap_021ECF1C(param0, param2);
    return v0;
}

int FieldMap_021ECF04(MapObject *param0, Billboard **param1)
{
    int v0 = MapObject_GetGraphicsID(param0);
    int v1 = FieldMap_021ECEB4(param0, param1, v0);

    return v1;
}

Billboard *FieldMap_021ECF1C(MapObject *param0, int param1)
{
    VecFx32 v0;
    BillboardList *v1;
    Billboard *v2;
    BillboardResources *v3;
    MapObjectDrawManager *v4 = FieldMap_021EDEA8(param0);
    v1 = FieldMap_021EDC8C(v4);

    FieldMap_021EDA0C(v4, param1);
    v3 = FieldMap_021ED110(v4, param1);

    GF_ASSERT(v3 != NULL);

    FieldMap_021ECDA0(param0, &v0);
    v2 = FieldMap_021EDDDC(v1, v3, &v0, FieldMap_021EDD50(param1));

    GF_ASSERT(v2 != NULL);

    return v2;
}

void FieldMap_021ECF70(const MapObject *param0, Billboard **param1, int param2)
{
    int v0;

    Billboard_Delete(*param1);
    *param1 = NULL;

    v0 = FieldMap_021ED1C8(MapObject_MapObjectManager(param0), param0, param2);

    if (v0 == 0) {
        FieldMap_021ED184(FieldMap_021EDEA8(param0), param2);
    }
}

void FieldMap_021ECFA4(const MapObject *param0, Billboard **param1)
{
    FieldMap_021ED094(param0);

    if ((*param1) != NULL) {
        int v0 = MapObject_GetGraphicsID(param0);

        if (BerryPatchGraphics_IsBerryPatch(v0) == 1) {
            v0 = BerryPatchGraphics_GetCurrentGraphicsResourceID(param0);
        }

        FieldMap_021ECF70(param0, param1, v0);
    }
}

void FieldMap_021ECFD8(const MapObject *param0, Billboard **param1, int param2)
{
    int v0;

    FieldMap_021ED094(param0);

    if ((*param1) != NULL) {
        Billboard_Delete(*param1);
        *param1 = NULL;
    }

    if (param2 != 0xffff) {
        v0 = FieldMap_021ED1C8(MapObject_MapObjectManager(param0), param0, param2);

        if (v0 == 0) {
            FieldMap_021ED184(FieldMap_021EDEA8(param0), param2);
        }
    }
}

void FieldMap_021ED01C(Billboard *param0, BillboardAnimState *param1)
{
    param1->unk_00 = Billboard_GetDrawFlag(param0);
    param1->unk_02 = Billboard_GetAnimNum(param0);
    param1->unk_04 = Billboard_GetFrameNum(param0);
}

void FieldMap_021ED03C(Billboard *param0, BillboardAnimState *param1)
{
    Billboard_SetDrawFlag(param0, param1->unk_00);
    Billboard_SetAnimNum(param0, param1->unk_02);
    Billboard_SetFrameNum(param0, param1->unk_04);
}

void FieldMap_021ED060(MapObject *param0, Billboard **param1, int param2)
{
    MapObjectDrawManager *v0 = FieldMap_021EDEA8(param0);

    if (FieldMap_021ED3A4(v0, param2) == UnkEnum_FieldMap_021ED334_00) {
        *param1 = FieldMap_021ECF1C(param0, param2);
    } else {
        FieldMap_021EE228(v0, param0, param1, param2);
    }
}

static void FieldMap_021ED094(const MapObject *param0)
{
    MapObjectDrawManager *v0 = FieldMap_021EDEA8(param0);

    FieldMap_021EE264(v0, param0);
}

static void FieldMap_021ED0A4(MapObjectDrawManager *param0, int param1)
{
    int v0, v1;
    BillboardResources *v2;
    BillboardResourceEntry *v3;

    v0 = sizeof(BillboardResources) * param1;
    v2 = Heap_Alloc(HEAP_ID_FIELD1, v0);

    param0->unk_E4 = v2;
    GF_ASSERT(v2 != NULL);

    v0 = (sizeof(BillboardResourceEntry)) * param1;
    v3 = Heap_Alloc(HEAP_ID_FIELD1, v0);

    param0->unk_F4 = v3;
    GF_ASSERT(v3 != NULL);

    v1 = sizeof(BillboardResources);

    do {
        v3->unk_00 = 0xffff;
        v3->unk_04 = v2;
        v3++;
        (u8 *)v2 += v1;
        param1--;
    } while (param1);
}

static void FieldMap_021ED0F0(MapObjectDrawManager *param0)
{
    FieldMap_021ED1A4(param0);

    Heap_FreeExplicit(HEAP_ID_FIELD1, param0->unk_E4);
    Heap_FreeExplicit(HEAP_ID_FIELD1, param0->unk_F4);
}

static BillboardResources *FieldMap_021ED110(MapObjectDrawManager *param0, u32 param1)
{
    int v0;
    BillboardResourceEntry *v1 = param0->unk_F4;
    v0 = param0->unk_04;

    do {
        if (v1->unk_00 == param1) {
            return v1->unk_04;
        }

        v1++;
        v0--;
    } while (v0);

    v1 = param0->unk_F4;
    v0 = param0->unk_04;

    do {
        if (v1->unk_00 == 0xffff) {
            v1->unk_00 = param1;
            FieldMap_021EDE3C(param0, param1, v1->unk_04);
            return v1->unk_04;
        }

        v1++;
        v0--;
    } while (v0);

    return NULL;
}

int FieldMap_021ED150(const MapObjectManager *param0, u32 param1, BillboardResources *param2)
{
    int v0;
    const MapObjectDrawManager *v1 = MapObjectMan_GetDrawManager(param0);
    BillboardResourceEntry *v2 = v1->unk_F4;
    v0 = v1->unk_04;

    do {
        if (v2->unk_00 == param1) {
            *param2 = *(v2->unk_04);
            return 1;
        }

        v2++;
        v0--;
    } while (v0);

    return 0;
}

static void FieldMap_021ED184(MapObjectDrawManager *param0, u32 param1)
{
    int v0;
    BillboardResourceEntry *v1 = param0->unk_F4;
    v0 = param0->unk_04;

    do {
        if (v1->unk_00 == param1) {
            v1->unk_00 = 0xffff;

            return;
        }

        v1++;
        v0--;
    } while (v0);
}

static void FieldMap_021ED1A4(MapObjectDrawManager *param0)
{
    int v0;
    BillboardResourceEntry *v1 = param0->unk_F4;
    v0 = param0->unk_04;

    do {
        if (v1->unk_00 != 0xffff) {
            v1->unk_00 = 0xffff;
        }

        v1++;
        v0--;
    } while (v0);
}

static int FieldMap_021ED1C8(const MapObjectManager *param0, const MapObject *param1, int param2)
{
    int v0, v1;
    const MapObject *v2;

    v0 = MapObjectMan_GetMaxObjects(param0);
    v2 = MapObjectMan_GetMapObjectConst(param0);

    do {
        if (v2 != param1) {
            if (MapObject_IsActive(v2) == 1) {
                v1 = MapObject_GetGraphicsID(v2);

                if (BerryPatchGraphics_IsBerryPatch(v1) == 1) {
                    v1 = BerryPatchGraphics_GetCurrentGraphicsResourceID(v2);
                }

                if ((v1 != 0xffff) && (v1 == param2)) {
                    return 1;
                }
            }
        }

        MapObject_AdvancePointer(&v2);
        v0--;
    } while (v0);

    return 0;
}

static void FieldMap_021ED224(MapObjectDrawManager *param0, int param1, int param2, int param3, int param4, int param5, int param6)
{
    {
        param0->unk_F8 = ResourceHeap_New(HEAP_ID_FIELD1, HEAP_ID_64, 0x1000 * param1, param1);
        FieldMap_021ED558(param0);
        FieldMap_021EDCC4(param0, param2);
        FieldMap_021EDCCC(param0, param1 - param2);
    }

    {
        param0->unk_FC = ResourceHeap_New(HEAP_ID_FIELD1, HEAP_ID_65, 0x80 * param3, param3);
        FieldMap_021ED694(param0);
        FieldMap_021EDCD4(param0, param4);
        FieldMap_021EDCDC(param0, param3 - param4);
    }

    {
        TextureResourceManager *v0;

        v0 = TextureResourceManager_New(param5, HEAP_ID_FIELD1);

        FieldMap_021EDCA8(param0, v0);
        FieldMap_021ED7D0(param0);
        FieldMap_021EDCE4(param0, param6);
        FieldMap_021EDCEC(param0, param5 - param6);
    }
}

static void FieldMap_021ED2AC(MapObjectDrawManager *param0)
{
    ResourceHeap_Free(param0->unk_F8);
    ResourceHeap_Free(param0->unk_FC);
    TextureResourceManager_Delete(FieldMap_021EDCB0(param0));
}

static const ObjectEventGfxFileEntry *FieldMap_021ED2D0(int param0, int param1, const ObjectEventGfxFileEntry *param2)
{
    do {
        if (param2->id == param0) {
            return param2;
        }

        param2++;
    } while (param2->id != param1);

    return NULL;
}

static int FieldMap_021ED2E8(MapObjectDrawManager *param0, ResourceHeap *param1, int param2, int param3, const ObjectEventGfxFileEntry *param4)
{
    const ObjectEventGfxFileEntry *v0;

    if (ResourceHeap_HasItem(param1, param2) == 1) {
        return 0;
    }

    v0 = FieldMap_021ED2D0(param2, param3, param4);
    GF_ASSERT(v0 != NULL);

    {
        NARC *v1 = MapObjectMan_GetNARC(param0->unk_104);
        ResourceHeap_LoadMemberFromNARC(param1, param2, v1, v0->narcIdx, 0);
    }

    return 1;
}

static UnkEnum_FieldMap_021ED334 FieldMap_021ED334(MapObjectDrawManager *param0, int param1, int param2, const ObjectEventGfxFileEntry *param3)
{
    TextureResourceManager *v0 = param0->unk_F0;

    if (TextureResourceManager_IsIDUnused(v0, param2) == 0) {
        return UnkEnum_FieldMap_021ED334_00;
    }

    if (FieldMap_021EDFF0(param0, param2) != 0) {
        return UnkEnum_FieldMap_021ED334_01;
    }

    {
        TextureResource *v1;
        const ObjectEventGfxFileEntry *v2 = FieldMap_021ED2D0(param2, 0xffff, param3);

        if (v2 == NULL) {
            return UnkEnum_FieldMap_021ED334_02;
        }

        if (FieldMap_021EDF3C(param0, param2, v2->narcIdx, param1) == 1) {
            return UnkEnum_FieldMap_021ED334_00;
        }

        return UnkEnum_FieldMap_021ED334_01;
    }
}

static UnkEnum_FieldMap_021ED334 FieldMap_021ED390(MapObjectDrawManager *param0, int param1)
{
    return FieldMap_021ED334(param0, 0, param1, gObjectEventGfxTexturesTable);
}

static UnkEnum_FieldMap_021ED334 FieldMap_021ED3A4(MapObjectDrawManager *param0, int param1)
{
    return FieldMap_021ED334(param0, 1, param1, gObjectEventGfxTexturesTable);
}

static void FieldMap_021ED3B8(MapObjectDrawManager *param0, const int *param1)
{
    while ((*param1) != 0xffff) {
        FieldMap_021ED390(param0, *param1);
        param1++;
    }
}

static void FieldMap_021ED3DC(MapObjectDrawManager *param0, int param1)
{
    ResourceCollection *v0 = FieldMap_021EDC98(param0);

    FieldMap_021ED2E8(param0, param0->unk_F8, param1, 0xffff, gObjectEventGfxModelsTable);
    FieldMap_021ED56C(param0, param1);
}

static void FieldMap_021ED40C(MapObjectDrawManager *param0, int param1)
{
    ResourceCollection *v0 = FieldMap_021EDC98(param0);

    FieldMap_021ED2E8(param0, param0->unk_F8, param1, 0xffff, gObjectEventGfxModelsTable);
    FieldMap_021ED5B4(param0, param1);
}

static void FieldMap_021ED43C(MapObjectDrawManager *param0, const int *param1)
{
    while ((*param1) != 0xffff) {
        FieldMap_021ED3DC(param0, *param1);
        param1++;
    }
}

static void FieldMap_021ED460(MapObjectDrawManager *param0, int param1)
{
    ResourceCollection *v0 = FieldMap_021EDCA0(param0);

    FieldMap_021ED2E8(param0, param0->unk_FC, param1, 0xffff, gObjectEventGfxFrameSeqsTable);
    FieldMap_021ED6A8(param0, param1);
}

static void FieldMap_021ED490(MapObjectDrawManager *param0, int param1)
{
    ResourceCollection *v0 = FieldMap_021EDCA0(param0);

    FieldMap_021ED2E8(param0, param0->unk_FC, param1, 0xffff, gObjectEventGfxFrameSeqsTable);
    FieldMap_021ED6F0(param0, param1);
}

static void FieldMap_021ED4C0(MapObjectDrawManager *param0, const int *param1)
{
    while ((*param1) != 0xffff) {
        FieldMap_021ED460(param0, *param1);
        param1++;
    }
}

static void FieldMap_021ED4E4(MapObjectDrawManager *param0, const int *param1, const int *param2, const int *param3)
{
    FieldMap_021ED3B8(param0, param1);
    FieldMap_021ED43C(param0, param2);
    FieldMap_021ED4C0(param0, param3);
}

static void FieldMap_021ED504(int *param0, int param1, int param2)
{
    do {
        *param0 = param1;
        param0++;
        param2--;
    } while (param2);
}

static int FieldMap_021ED50C(int *param0, int param1, int param2, int param3)
{
    do {
        if ((*param0) == param2) {
            *param0 = param1;
            return 1;
        }

        param0++;
        param3--;
    } while (param3);

    return 0;
}

static int FieldMap_021ED528(int *param0, int param1, int param2)
{
    do {
        if ((*param0) == param1) {
            return 1;
        }

        param0++;
        param2--;
    } while (param2);

    return 0;
}

static int FieldMap_021ED53C(int *param0, int param1, int param2, int param3)
{
    do {
        if ((*param0) == param1) {
            *param0 = param2;
            return 1;
        }

        param0++;
        param3--;
    } while (param3);

    return 0;
}

static void FieldMap_021ED558(MapObjectDrawManager *param0)
{
    int *v0 = FieldMap_021EDCBC(param0);
    FieldMap_021ED504(v0, 0xffff, 8);
}

static void FieldMap_021ED56C(MapObjectDrawManager *param0, int param1)
{
    int v0, v1;
    int *v2;

    v0 = FieldMap_021EDCC8(param0);
    v2 = FieldMap_021EDCBC(param0);

    v1 = FieldMap_021ED50C(v2, param1, 0xffff, v0);
    GF_ASSERT(v1 != 0);
}

static int FieldMap_021ED598(MapObjectDrawManager *param0, int param1)
{
    int v0;
    int *v1;

    v0 = FieldMap_021EDCC8(param0);
    v1 = FieldMap_021EDCBC(param0);

    return FieldMap_021ED528(v1, param1, v0);
}

static void FieldMap_021ED5B4(MapObjectDrawManager *param0, int param1)
{
    int v0, v1;
    int *v2 = FieldMap_021EDCBC(param0);
    v2 = &v2[FieldMap_021EDCC8(param0)];
    v1 = FieldMap_021EDCD0(param0);
    v0 = FieldMap_021ED50C(v2, param1, 0xffff, v1);

    GF_ASSERT(v0 != 0);
}

static int FieldMap_021ED5E8(MapObjectDrawManager *param0, int param1)
{
    int v0;
    int *v1 = FieldMap_021EDCBC(param0);
    v1 = &v1[FieldMap_021EDCC8(param0)];
    v0 = FieldMap_021EDCD0(param0);

    return FieldMap_021ED528(v1, param1, v0);
}

static void FieldMap_021ED610(MapObjectDrawManager *param0, int param1)
{
    int v0;
    int *v1 = FieldMap_021EDCBC(param0);
    v1 = &v1[FieldMap_021EDCC8(param0)];
    v0 = FieldMap_021EDCD0(param0);

    FieldMap_021ED53C(v1, param1, 0xffff, v0);
}

static void FieldMap_021ED63C(MapObjectManager *param0, MapObjectDrawManager *param1)
{
    int v0;
    ResourceCollection *v2 = FieldMap_021EDC98(param1);
    int *v1 = FieldMap_021EDCBC(param1);
    v1 = &v1[FieldMap_021EDCC8(param1)];
    v0 = FieldMap_021EDCD0(param1);

    do {
        if ((*v1) != 0xffff) {
            if (FieldMap_021EDAB4(param0, *v1, NULL) == 0) {
                ResourceHeap_FreeItem(param1->unk_F8, *v1);
                *v1 = 0xffff;
            }
        }

        v1++;
        v0--;
    } while (v0);
}

static void FieldMap_021ED694(MapObjectDrawManager *param0)
{
    int *v0 = FieldMap_021EDCC0(param0);
    FieldMap_021ED504(v0, 0xffff, 8);
}

static void FieldMap_021ED6A8(MapObjectDrawManager *param0, int param1)
{
    int v0, v1;
    int *v2;

    v0 = FieldMap_021EDCD8(param0);
    v2 = FieldMap_021EDCC0(param0);
    v1 = FieldMap_021ED50C(v2, param1, 0xffff, v0);

    GF_ASSERT(v1 != 0);
}

static int FieldMap_021ED6D4(MapObjectDrawManager *param0, int param1)
{
    int v0;
    int *v1;

    v0 = FieldMap_021EDCD8(param0);
    v1 = FieldMap_021EDCC0(param0);

    return FieldMap_021ED528(v1, param1, v0);
}

static void FieldMap_021ED6F0(MapObjectDrawManager *param0, int param1)
{
    int v0, v1;
    int *v2 = FieldMap_021EDCC0(param0);
    v2 = &v2[FieldMap_021EDCD8(param0)];
    v1 = FieldMap_021EDCE0(param0);
    v0 = FieldMap_021ED50C(v2, param1, 0xffff, v1);

    GF_ASSERT(v0 != 0);
}

static int FieldMap_021ED724(MapObjectDrawManager *param0, int param1)
{
    int v0;
    int *v1 = FieldMap_021EDCC0(param0);
    v1 = &v1[FieldMap_021EDCD8(param0)];
    v0 = FieldMap_021EDCE0(param0);

    return FieldMap_021ED528(v1, param1, v0);
}

static void FieldMap_021ED74C(MapObjectDrawManager *param0, int param1)
{
    int v0;
    int *v1 = FieldMap_021EDCC0(param0);
    v1 = &v1[FieldMap_021EDCD8(param0)];
    v0 = FieldMap_021EDCE0(param0);

    FieldMap_021ED53C(v1, param1, 0xffff, v0);
}

static void FieldMap_021ED778(MapObjectManager *param0, MapObjectDrawManager *param1)
{
    int v0;
    ResourceCollection *v2 = FieldMap_021EDCA0(param1);
    int *v1 = FieldMap_021EDCC0(param1);
    v1 = &v1[FieldMap_021EDCD8(param1)];
    v0 = FieldMap_021EDCE0(param1);

    do {
        if ((*v1) != 0xffff) {
            if (FieldMap_021EDB3C(param0, *v1, NULL) == 0) {
                ResourceHeap_FreeItem(param1->unk_FC, *v1);
                *v1 = 0xffff;
            }
        }

        v1++;
        v0--;
    } while (v0);
}

static void FieldMap_021ED7D0(MapObjectDrawManager *param0)
{
    int *v0 = FieldMap_021EDCB8(param0);
    FieldMap_021ED504(v0, 0xffff, 32);
}

static void FieldMap_021ED7E4(MapObjectDrawManager *param0, int param1)
{
    int v0, v1;
    int *v2;

    v0 = FieldMap_021EDCE8(param0);
    v2 = FieldMap_021EDCB8(param0);
    v1 = FieldMap_021ED50C(v2, param1, 0xffff, v0);
    GF_ASSERT(v1 != 0);
}

static int FieldMap_021ED810(MapObjectDrawManager *param0, int param1)
{
    int v0;
    int *v1;

    v0 = FieldMap_021EDCE8(param0);
    v1 = FieldMap_021EDCB8(param0);
    return FieldMap_021ED528(v1, param1, v0);
}

static int FieldMap_021ED82C(MapObjectDrawManager *param0, int param1)
{
    if (FieldMap_021ED810(param0, param1) == 1) {
        return 1;
    }

    if (FieldMap_021ED924(param0, param1) == 1) {
        return 2;
    }

    return FieldMap_021EDFF0(param0, param1);
}

static void FieldMap_021ED858(MapObjectDrawManager *param0, int param1)
{
    int v0, v1;
    int *v2 = FieldMap_021EDCB8(param0);
    v2 = &v2[FieldMap_021EDCE8(param0)];
    v1 = FieldMap_021EDCF0(param0);
    v0 = FieldMap_021ED50C(v2, param1, 0xffff, v1);

    GF_ASSERT(v0 != 0);
}

static void FieldMap_021ED88C(MapObjectDrawManager *param0, int param1)
{
    int v0;
    int *v1 = FieldMap_021EDCB8(param0);
    v1 = &v1[FieldMap_021EDCE8(param0)];
    v0 = FieldMap_021EDCF0(param0);

    FieldMap_021ED53C(v1, param1, 0xffff, v0);
}

static void FieldMap_021ED8B8(MapObjectManager *param0, MapObjectDrawManager *param1)
{
    int v0, v1;
    TextureResourceManager *v3 = FieldMap_021EDCB0(param1);
    int *v2 = FieldMap_021EDCB8(param1);
    v2 = &v2[FieldMap_021EDCE8(param1)];
    v0 = FieldMap_021EDCF0(param1);

    do {
        v1 = *v2;

        if (v1 != 0xffff) {
            if (FieldMap_021EDA54(param0, v1, NULL) == 0) {
                TextureResourceManager_RemoveTextureWithID(v3, v1);
                FieldMap_021EDFBC(param1, v1);
                FieldMap_021EE170(param1, v1);

                *v2 = 0xffff;
            }
        }

        v2++;
        v0--;
    } while (v0);
}

static int FieldMap_021ED924(MapObjectDrawManager *param0, int param1)
{
    int v0;
    int *v1 = FieldMap_021EDCB8(param0);
    v1 = &v1[FieldMap_021EDCE8(param0)];
    v0 = FieldMap_021EDCF0(param0);

    return FieldMap_021ED528(v1, param1, v0);
}

static int FieldMap_021ED94C(MapObjectDrawManager *param0, int param1)
{
    if (FieldMap_021ED810(param0, param1) == 1) {
        return 0;
    }

    if (FieldMap_021ED924(param0, param1) == 1) {
        return 1;
    }

    return 2;
}

static int FieldMap_021ED974(MapObjectDrawManager *param0, int param1)
{
    if (FieldMap_021ED598(param0, param1) == 1) {
        return 0;
    }

    if (FieldMap_021ED5E8(param0, param1) == 1) {
        return 1;
    }

    return 2;
}

static int FieldMap_021ED99C(MapObjectDrawManager *param0, int param1)
{
    if (FieldMap_021ED6D4(param0, param1) == 1) {
        return 0;
    }

    if (FieldMap_021ED724(param0, param1) == 1) {
        return 1;
    }

    return 2;
}

static void FieldMap_021ED9C4(MapObjectDrawManager *param0, int param1)
{
    int v0 = FieldMap_021ED82C(param0, param1);

    if (v0 == 0) {
        FieldMap_021ED3A4(param0, param1);
    }
}

static void FieldMap_021ED9DC(MapObjectDrawManager *param0, int param1)
{
    if (FieldMap_021ED974(param0, param1) == 2) {
        FieldMap_021ED40C(param0, param1);
    }
}

static void FieldMap_021ED9F4(MapObjectDrawManager *param0, int param1)
{
    if (FieldMap_021ED99C(param0, param1) == 2) {
        FieldMap_021ED490(param0, param1);
    }
}

static void FieldMap_021EDA0C(MapObjectDrawManager *param0, int param1)
{
    int v0 = FieldMap_021EDD2C(param1);
    FieldMap_021ED9DC(param0, v0);

    v0 = FieldMap_021EDD38(param1);
    FieldMap_021ED9F4(param0, v0);
    FieldMap_021ED9C4(param0, param1);
}

void FieldMap_021EDA38(MapObjectManager *param0, MapObjectDrawManager *param1)
{
    FieldMap_021ED63C(param0, param1);
    FieldMap_021ED778(param0, param1);
    FieldMap_021ED8B8(param0, param1);
}

static int FieldMap_021EDA54(const MapObjectManager *param0, int param1, const MapObject *param2)
{
    int v0 = 0, v1;
    MapObject *v2 = NULL;

    while (MapObjectMan_FindObjectWithStatus(param0, &v2, &v0, MAP_OBJ_STATUS_0) == 1) {
        if ((param2 != NULL) && (param2 == v2)) {
            continue;
        }

        v1 = MapObject_GetGraphicsID(v2);

        if (BerryPatchGraphics_IsBerryPatch(v1) == 1) {
            v1 = BerryPatchGraphics_GetCurrentGraphicsResourceID(v2);
        }

        if (v1 == param1) {
            return 1;
        }
    }

    return 0;
}

static int FieldMap_021EDAB4(const MapObjectManager *param0, int param1, const MapObject *param2)
{
    int v0, v1 = 0;
    MapObject *v2 = NULL;

    while (MapObjectMan_FindObjectWithStatus(param0, &v2, &v1, MAP_OBJ_STATUS_0) == 1) {
        if ((param2 != NULL) && (param2 == v2)) {
            continue;
        }

        v0 = MapObject_GetGraphicsID(v2);

        if (v0 == 0xffff) {
            continue;
        }

        {
            const ObjectEventGfxRenderDetailsEntry *v3 = FieldMap_021ECD04(v2);

            if (v3->modelType != 1) {
                continue;
            }
        }

        if (BerryPatchGraphics_IsBerryPatch(v0) == 1) {
            v0 = BerryPatchGraphics_GetCurrentGraphicsResourceID(v2);
        }

        if (v0 != 0xffff) {
            if (FieldMap_021EDD2C(v0) == param1) {
                return 1;
            }
        }
    }

    return 0;
}

static int FieldMap_021EDB3C(const MapObjectManager *param0, int param1, const MapObject *param2)
{
    int v0, v1 = 0;
    MapObject *v2 = NULL;

    while (MapObjectMan_FindObjectWithStatus(param0, &v2, &v1, MAP_OBJ_STATUS_0) == 1) {
        if ((param2 != NULL) && (v2 == param2)) {
            continue;
        }

        if (v0 == 0xffff) {
            continue;
        }

        {
            const ObjectEventGfxRenderDetailsEntry *v3 = FieldMap_021ECD04(v2);

            if (v3->modelType != 1) {
                continue;
            }
        }

        v0 = MapObject_GetGraphicsID(v2);

        if (BerryPatchGraphics_IsBerryPatch(v0) == 1) {
            v0 = BerryPatchGraphics_GetCurrentGraphicsResourceID(v2);
        }

        if (v0 != 0xffff) {
            if (FieldMap_021EDD38(v0) == param1) {
                return 1;
            }
        }
    }

    return 0;
}

void FieldMap_021EDBC4(const MapObjectManager *param0, int param1, MapObject *param2)
{
    int v0;
    MapObjectDrawManager *v1 = MapObjectMan_GetDrawManager(param0);

    v0 = FieldMap_021EDD2C(param1);

    if (FieldMap_021ED974(v1, v0) == 1) {
        if (FieldMap_021EDAB4(param0, v0, param2) == 0) {
            ResourceHeap_FreeItem(v1->unk_F8, v0);
            FieldMap_021ED610(v1, v0);
        }
    }

    v0 = FieldMap_021EDD38(param1);

    if (FieldMap_021ED99C(v1, v0) == 1) {
        if (FieldMap_021EDB3C(param0, v0, param2) == 0) {
            ResourceHeap_FreeItem(v1->unk_FC, v0);
            FieldMap_021ED74C(v1, v0);
        }
    }

    if (FieldMap_021ED94C(v1, param1) == 1) {
        if (FieldMap_021EDA54(param0, param1, param2) == 0) {
            TextureResourceManager *v2 = FieldMap_021EDCB0(v1);

            TextureResourceManager_RemoveTextureWithID(v2, param1);
            FieldMap_021ED88C(v1, param1);
            FieldMap_021EDFBC(v1, param1);
            FieldMap_021EE170(v1, param1);
        }
    }
}

void FieldMap_021EDC84(MapObjectDrawManager *param0, BillboardList *param1)
{
    param0->unk_E0 = param1;
}

BillboardList *FieldMap_021EDC8C(MapObjectDrawManager *param0)
{
    return param0->unk_E0;
}

void FieldMap_021EDC94(MapObjectDrawManager *param0, int param1)
{
    param0->unk_04 = param1;
}

ResourceCollection *FieldMap_021EDC98(const MapObjectDrawManager *param0)
{
    return param0->unk_E8;
}

ResourceCollection *FieldMap_021EDCA0(const MapObjectDrawManager *param0)
{
    return param0->unk_EC;
}

void FieldMap_021EDCA8(MapObjectDrawManager *param0, TextureResourceManager *param1)
{
    param0->unk_F0 = param1;
}

TextureResourceManager *FieldMap_021EDCB0(const MapObjectDrawManager *param0)
{
    return param0->unk_F0;
}

static int *FieldMap_021EDCB8(MapObjectDrawManager *param0)
{
    return param0->unk_60;
}

static int *FieldMap_021EDCBC(MapObjectDrawManager *param0)
{
    return param0->unk_20;
}

static int *FieldMap_021EDCC0(MapObjectDrawManager *param0)
{
    return param0->unk_40;
}

static void FieldMap_021EDCC4(MapObjectDrawManager *param0, int param1)
{
    param0->unk_08 = param1;
}

static int FieldMap_021EDCC8(const MapObjectDrawManager *param0)
{
    return param0->unk_08;
}

static void FieldMap_021EDCCC(MapObjectDrawManager *param0, int param1)
{
    param0->unk_0C = param1;
}

static int FieldMap_021EDCD0(const MapObjectDrawManager *param0)
{
    return param0->unk_0C;
}

static void FieldMap_021EDCD4(MapObjectDrawManager *param0, int param1)
{
    param0->unk_10 = param1;
}

static int FieldMap_021EDCD8(const MapObjectDrawManager *param0)
{
    return param0->unk_10;
}

static void FieldMap_021EDCDC(MapObjectDrawManager *param0, int param1)
{
    param0->unk_14 = param1;
}

static int FieldMap_021EDCE0(const MapObjectDrawManager *param0)
{
    return param0->unk_14;
}

static void FieldMap_021EDCE4(MapObjectDrawManager *param0, int param1)
{
    param0->unk_18 = param1;
}

static int FieldMap_021EDCE8(const MapObjectDrawManager *param0)
{
    return param0->unk_18;
}

static void FieldMap_021EDCEC(MapObjectDrawManager *param0, int param1)
{
    param0->unk_1C = param1;
}

static int FieldMap_021EDCF0(const MapObjectDrawManager *param0)
{
    return param0->unk_1C;
}

static void *FieldMap_021EDCF4(MapObjectDrawManager *param0, u32 param1, int param2)
{
    return FieldMap_021ECD68(param0->unk_104, param1, param2);
}

static const ObjectEventGfxModelAnimEntry *FieldMap_021EDD04(int param0)
{
    const ObjectEventGfxModelAnimEntry *v0 = gObjectEventGfxModelAnimsTable;

    do {
        if (v0->graphicsID == param0) {
            return v0;
        }

        v0++;
    } while (v0->graphicsID != 0xffff);

    GF_ASSERT(FALSE);
    return NULL;
}

static int FieldMap_021EDD2C(int param0)
{
    const ObjectEventGfxModelAnimEntry *v0 = FieldMap_021EDD04(param0);
    return v0->modelID;
}

static int FieldMap_021EDD38(int param0)
{
    const ObjectEventGfxModelAnimEntry *v0 = FieldMap_021EDD04(param0);
    return v0->frameSeqID;
}

static const BillboardAnim *FieldMap_021EDD44(int param0)
{
    const ObjectEventGfxModelAnimEntry *v0 = FieldMap_021EDD04(param0);
    return v0->animations;
}

static u32 FieldMap_021EDD50(int param0)
{
    int v0 = FieldMap_021EDD2C(param0);
    const int *v1 = gFogIgnoredModels;

    do {
        if (*v1 == v0) {
            return 0;
        }
    } while (*(++v1) != 0xffff);

    return 1;
}

void FieldMap_021EDD78(MapObject *param0, int param1)
{
    if (param1 == 1) {
        MapObject_SetStatusFlagOn(param0, MAP_OBJ_STATUS_22);
    } else {
        MapObject_SetStatusFlagOff(param0, MAP_OBJ_STATUS_22);
    }
}

int FieldMap_021EDD94(MapObject *param0)
{
    if (MapObject_CheckStatus(param0, MAP_OBJ_STATUS_22)) {
        return 1;
    }

    return 0;
}

static void FieldMap_021EDDAC(MapObjectDrawManager *param0, int param1)
{
    BillboardListParams v0;
    BillboardList *v1;

    v0.maxElements = param1;
    v0.heapID = HEAP_ID_FIELD1;

    v1 = BillboardList_New(&v0);
    FieldMap_021EDC84(param0, v1);
    FieldMap_021EDC94(param0, param1);
}

static void FieldMap_021EDDD4(BillboardList *param0)
{
    BillboardList_Delete(param0);
}

static Billboard *FieldMap_021EDDDC(BillboardList *param0, const BillboardResources *param1, const VecFx32 *param2, u32 param3)
{
    int v0;
    BillboardTemplate v1;
    Billboard *v2;
    VecFx32 v3 = { FX32_ONE, FX32_ONE, FX32_ONE };

    v1.list = param0;
    v1.resources = param1;
    v1.pos = *param2;
    v1.scale = v3;

    v2 = BillboardList_Append(&v1);

    if (v2 != NULL) {
        Billboard_SetDrawFlag(v2, 0);
        Billboard_SetAnimNum(v2, 0);
        Billboard_SetAnimFrameNum(v2, 0);
        NNS_G3dMdlSetMdlFogEnableFlagAll(Billboard_GetModel(v2), param3);
        AreaLight_UseGlobalModelAttributes(Billboard_GetModel(v2));
    }

    return v2;
}

static void FieldMap_021EDE3C(MapObjectDrawManager *param0, u32 param1, BillboardResources *param2)
{
    {
        int v0 = FieldMap_021EDD2C(param1);
        void *v1 = ResourceHeap_GetItemData(param0->unk_F8, v0);

        param2->modelRes = v1;
    }

    {
        int v2 = FieldMap_021EDD38(param1);
        void *v3 = ResourceHeap_GetItemData(param0->unk_FC, v2);

        BillboardGfxSequence_SetData(v3, &param2->gfxSequence);
    }

    {
        TextureResourceManager *v4 = FieldMap_021EDCB0(param0);
        TextureResource *v5 = TextureResourceManager_FindTextureResource(v4, param1);

        param2->texture = TextureResource_GetUnderlyingResource(v5);

        {
            param2->texKey = TextureResource_GetTexKey(v5);
            param2->tex4x4Key = TextureResource_GetTex4x4Key(v5);
            param2->plttKey = TextureResource_GetPaletteKey(v5);
        }
    }

    {
        param2->anims = FieldMap_021EDD44(param1);
    }
}

static MapObjectDrawManager *FieldMap_021EDEA8(const MapObject *param0)
{
    const MapObjectManager *v0 = MapObject_MapObjectManager(param0);
    return (MapObjectDrawManager *)MapObjectMan_GetDrawManager(v0);
}

BOOL FieldMap_021EDEB4(MapObject *param0, Billboard *param1)
{
    BOOL v0;
    VecFx32 v1;

    FieldMap_021ECDA0(param0, &v1);

    v1.x += 0;
    v1.y += 0;
    v1.z += (FX32_ONE * 6);

    Billboard_SetPos(param1, &v1);

    return 0;
}

void FieldMap_021EDED8(MapObject *param0, Billboard *param1)
{
    int v0 = 1;

    if (MapObject_CheckStatusFlag(param0, MAP_OBJ_STATUS_HIDE) == 1) {
        v0 = 0;
    }

    if (MapObject_CheckStatusFlag(param0, MAP_OBJ_STATUS_12) == 1) {
        if (!MapObject_CheckStatusFlag(param0, MAP_OBJ_STATUS_13)) {
            v0 = 0;
        }
    }

    Billboard_SetDrawFlag(param1, v0);
}

static const int Unk_FieldMap_021FF4C0[] = { 0, 1, 2, 3 };

int FieldMap_021EDF18(int param0)
{
    return Unk_FieldMap_021FF4C0[param0];
}

static const int Unk_FieldMap_021FF4D0[] = { 4, 5, 6, 7 };

int FieldMap_021EDF24(int param0)
{
    return Unk_FieldMap_021FF4D0[param0];
}

static const int Unk_FieldMap_021FF4E0[] = { 4, 5, 4, 5 };

int FieldMap_021EDF30(int param0)
{
    return Unk_FieldMap_021FF4E0[param0];
}

static int FieldMap_021EDF3C(MapObjectDrawManager *param0, int param1, u32 param2, int param3)
{
    MapObjectDrawTaskManager *v0 = param0->unk_100;

    if ((v0->unk_04 >= v0->unk_02) || (BillboardList_IsRedrawing(param0->unk_E0) == 1)) {
        int v1 = 0;
        MapObjectTextureLoadTask *v2 = v0->unk_0C;

        while (v1 < v0->unk_00) {
            if (v2->unk_0C == NULL) {
                v2->unk_0C = param0->unk_F0;
                v2->unk_08 = param3;
                v2->unk_04 = param1;
                v2->unk_00 = param2;
                return 0;
            }

            v1++;
            v2++;
        }

        GF_ASSERT(FALSE);
        return 0;
    }

    {
        void *v3 = FieldMap_021EDCF4(param0, param2, 0);

        FieldMap_021EE0E8(param0, param1, v3, param3);
        v0->unk_04++;
        return 1;
    }
}

static void FieldMap_021EDFBC(MapObjectDrawManager *param0, int param1)
{
    int v0 = 0;
    MapObjectDrawTaskManager *v1 = param0->unk_100;
    MapObjectTextureLoadTask *v2 = v1->unk_0C;

    while (v0 < v1->unk_00) {
        if ((v2->unk_04 == param1) && (v2->unk_0C != NULL)) {
            v2->unk_0C = NULL;
            return;
        }

        v0++;
        v2++;
    }
}

static int FieldMap_021EDFF0(MapObjectDrawManager *param0, int param1)
{
    int v0 = 0;
    MapObjectDrawTaskManager *v1 = param0->unk_100;
    MapObjectTextureLoadTask *v2 = v1->unk_0C;

    while (v0 < v1->unk_00) {
        if ((v2->unk_04 == param1) && (v2->unk_0C != NULL)) {
            if (v2->unk_08 == 0) {
                return 3;
            }

            return 4;
        }

        v0++;
        v2++;
    }

    return 0;
}

static void FieldMap_021EE030(SysTask *param0, void *param1)
{
    int v0 = 0;
    MapObjectDrawManager *v1 = param1;
    MapObjectDrawTaskManager *v2 = v1->unk_100;
    MapObjectTextureLoadTask *v3 = v2->unk_0C;

    {
        if (BillboardList_IsRedrawing(v1->unk_E0) == 1) {
            return;
        }
    }

    while ((v2->unk_04 < v2->unk_02) && v0 < v2->unk_00) {
        if (v3->unk_0C != NULL) {
            void *v4 = FieldMap_021EDCF4(v1, v3->unk_00, 0);

            FieldMap_021EE0E8(v1, v3->unk_04, v4, v3->unk_08);
            v3->unk_0C = NULL;
            v2->unk_04++;
        }

        v3++;
        v0++;
    }

    {
        int v5;

        v3 = v2->unk_0C;

        for (v0 = 0; v0 < (v2->unk_00 - 1); v0++) {
            if (v3[v0].unk_0C == NULL) {
                for (v5 = v0 + 1; v5 < v2->unk_00; v5++) {
                    if (v3[v5].unk_0C != NULL) {
                        v3[v0] = v3[v5];
                        v3[v5].unk_0C = NULL;
                        break;
                    }
                }
            }
        }
    }

    v2->unk_04 = 0;
}

static void FieldMap_021EE0E8(MapObjectDrawManager *param0, int param1, void *param2, int param3)
{
    TextureResource *v0 = TextureResourceManager_AddTextureAndAllocVRam(param0->unk_F0, param2, param1, 1, HEAP_ID_FIELD1);

    GF_ASSERT(v0 != NULL);
    FieldMap_021EE134(param0, param1);

    if (param3 == 0) {
        FieldMap_021ED7E4(param0, param1);
    } else {
        FieldMap_021ED858(param0, param1);
    }
}

static void FieldMap_021EE134(MapObjectDrawManager *param0, int param1)
{
    int v0 = 0;
    MapObjectDrawTaskManager *v1 = param0->unk_100;
    MapObjectTextureManager *v2 = v1->unk_10;

    v1->unk_06 = 1;

    while (v0 < v1->unk_00) {
        if (v2->unk_08 == NULL) {
            v2->unk_08 = param0->unk_F0;
            v2->unk_04 = param1;
            v2->unk_00 = 0;

            v1->unk_06 = 0;
            return;
        }

        v2++;
        v0++;
    }

    GF_ASSERT(FALSE);
}

static void FieldMap_021EE170(MapObjectDrawManager *param0, int param1)
{
    int v0 = 0;
    MapObjectDrawTaskManager *v1 = param0->unk_100;
    MapObjectTextureManager *v2 = v1->unk_10;

    v1->unk_06 = 1;

    while (v0 < v1->unk_00) {
        if ((v2->unk_08 != NULL) && (v2->unk_04 == param1)) {
            v2->unk_08 = NULL;
            v2->unk_00 = 0;
            break;
        }

        v2++;
        v0++;
    }

    v1->unk_06 = 0;
}

static void FieldMap_021EE1AC(SysTask *param0, void *param1)
{
    MapObjectDrawManager *v0 = param1;
    MapObjectDrawTaskManager *v1 = v0->unk_100;

    if (v1->unk_06 == 1) {
        return;
    }

    {
        int v2 = 0;
        MapObjectTextureManager *v3 = v1->unk_10;

        while (v2 < v1->unk_00) {
            if ((v3->unk_00 == 0) && (v3->unk_08 != NULL)) {
                TextureResourceManager_UploadResourceToVRam(v3->unk_08, v3->unk_04);
                v3->unk_00 = 1;
            }

            v3++;
            v2++;
        }
    }
}

static void FieldMap_021EE1E8(SysTask *param0, void *param1)
{
    int v0 = 0;
    MapObjectDrawManager *v1 = param1;
    MapObjectDrawTaskManager *v2 = v1->unk_100;
    MapObjectTextureManager *v3 = v2->unk_10;

    v2->unk_06 = 1;

    while (v0 < v2->unk_00) {
        if ((v3->unk_00 == 1) && (v3->unk_08 != NULL)) {
            TextureResourceManager_DiscardTextureData(v3->unk_08, v3->unk_04);
            v3->unk_00 = 0;
            v3->unk_08 = NULL;
        }

        v3++;
        v0++;
    }

    v2->unk_06 = 0;
}

static void FieldMap_021EE228(MapObjectDrawManager *param0, MapObject *param1, Billboard **param2, int param3)
{
    int v0 = 0;
    MapObjectDrawTaskManager *v1 = param0->unk_100;
    MapObjectBillboardList *v2 = v1->unk_08;

    while (v0 < v1->unk_00) {
        if (v2->unk_04 == NULL) {
            v2->unk_04 = param1;
            v2->unk_08 = param2;
            v2->unk_00 = param3;

            *(v2->unk_08) = NULL;
            FieldMap_021EDD78(param1, 1);
            return;
        }

        v2++;
        v0++;
    }

    GF_ASSERT(FALSE);
}

static void FieldMap_021EE264(MapObjectDrawManager *param0, const MapObject *param1)
{
    int v0 = 0;
    MapObjectDrawTaskManager *v1 = param0->unk_100;
    MapObjectBillboardList *v2 = v1->unk_08;

    while (v0 < v1->unk_00) {
        if (v2->unk_04 == param1) {
            v2->unk_04 = NULL;
            v2->unk_08 = NULL;

            return;
        }

        v2++;
        v0++;
    }
}

static void FieldMap_021EE294(MapObjectDrawManager *param0)
{
    int v0 = 0;
    MapObjectDrawTaskManager *v1 = param0->unk_100;
    MapObjectBillboardList *v2 = v1->unk_08;

    while (v0 < v1->unk_00) {
        if (v2->unk_04 != NULL) {
            FieldMap_021EE2D0(param0, v2);
        }

        v2++;
        v0++;
    }
}

static void FieldMap_021EE2C4(SysTask *param0, void *param1)
{
    MapObjectDrawManager *v0 = param1;
    FieldMap_021EE294(v0);
}

static void FieldMap_021EE2D0(MapObjectDrawManager *param0, MapObjectBillboardList *param1)
{
    if (FieldMap_021ED94C(param0, param1->unk_00) != 2) {
        *(param1->unk_08) = FieldMap_021ECF1C(param1->unk_04, param1->unk_00);
        GF_ASSERT(*(param1->unk_08) != NULL);

        FieldMap_021EDD78(param1->unk_04, 0);

        if (MapObject_CheckStatusFlag(param1->unk_04, MAP_OBJ_STATUS_21) == 1) {
            MapObject_CallRendererLoad(param1->unk_04);
        } else {
            MapObject_CallRendererDraw(param1->unk_04);
        }

        param1->unk_04 = NULL;
        param1->unk_08 = NULL;
    }
}

static void FieldMap_021EE320(MapObjectDrawManager *param0, int param1, int param2)
{
    u32 v0, v1, v2, v3, v4;
    MapObjectDrawTaskManager *v5;

    v4 = (sizeof(MapObjectBillboardList)) * param1;
    v3 = (sizeof(MapObjectTextureLoadTask)) * param1;
    v2 = (sizeof(MapObjectTextureManager)) * param1;
    v1 = (sizeof(MapObjectDrawTaskManager)) + v2 + v3 + v4;
    v5 = Heap_Alloc(HEAP_ID_FIELD1, v1);

    GF_ASSERT(v5 != NULL);
    memset(v5, 0, v1);

    v5->unk_00 = param1;
    v5->unk_02 = param2;

    v0 = (u32)v5 + (sizeof(MapObjectDrawTaskManager));
    v5->unk_08 = (void *)v0;

    v0 += v4;
    v5->unk_0C = (void *)v0;

    v0 += v3;
    v5->unk_10 = (void *)v0;

    param0->unk_100 = v5;

    v0 = MapObjectMan_GetTaskBasePriority(param0->unk_104);
    v5->unk_18 = SysTask_Start(FieldMap_021EE030, param0, v0 + 1);
    v5->unk_1C = SysTask_Start(FieldMap_021EE2C4, param0, v0 + 2);
    v5->unk_20 = SysTask_ExecuteOnVBlank(FieldMap_021EE1AC, param0, 0xff);
    v5->unk_24 = SysTask_ExecuteAfterVBlank(FieldMap_021EE1E8, param0, 0xff);
}

static void FieldMap_021EE3C4(MapObjectDrawManager *param0)
{
    MapObjectDrawTaskManager *v0 = param0->unk_100;

    v0->unk_06 = 1;

    SysTask_Done(v0->unk_18);
    SysTask_Done(v0->unk_1C);
    SysTask_Done(v0->unk_20);
    SysTask_Done(v0->unk_24);
    Heap_Free(v0);

    param0->unk_100 = NULL;
}

Billboard *FieldMap_021EE3FC(MapObject *param0, int param1, UnkFuncPtr_fieldmap_021EE454 param2, void *param3)
{
    if ((FieldMap_021EDD94(param0) == 1) || (FieldMap_021EB1A0(param0) == NULL)) {
        int v0 = MapObject_GetGraphicsID(param0);
        const MapObjectManager *v1 = MapObject_MapObjectManager(param0);

        MapObject_ClearGraphics(param0);
        FieldMap_021EDBC4(v1, v0, param0);
        MapObject_SetGraphicsIDAndRefresh(param0, param1);
        return NULL;
    }

    return FieldMap_021EE454(param0, param1, param2, param3);
}

static Billboard *FieldMap_021EE454(MapObject *param0, int param1, UnkFuncPtr_fieldmap_021EE454 param2, void *param3)
{
    VecFx32 v0;
    int v1, v2, v3, v4;
    TextureResource *v5;
    Billboard *v6;
    const ObjectEventGfxFileEntry *v7;
    MapObjectDrawManager *v8 = FieldMap_021EDEA8(param0);
    BillboardList *v9 = FieldMap_021EDC8C(v8);
    Billboard *v10 = FieldMap_021EB1A0(param0);
    MapObjectBillboardAnim *v11 = Heap_AllocAtEnd(HEAP_ID_FIELD1, sizeof(MapObjectBillboardAnim));

    memset(v11, 0, sizeof(MapObjectBillboardAnim));

    v11->unk_00 = param1;
    v11->unk_50 = param0;

    v2 = MapObject_GetGraphicsID(param0);

    {
        v1 = 0;
        v3 = FieldMap_021EDD2C(v2);
        v7 = gObjectEventGfxModelsTable;

        do {
            if (v7->id == v3) {
                break;
            }

            v7++;
            v1++;
        } while (v7->id != 0xffff);

        GF_ASSERT(v7->id != 0xffff);
        v11->unk_08 = FieldMap_021EDCF4(v8, v7->narcIdx, 0);
    }

    {
        v1 = 0;
        v3 = FieldMap_021EDD38(v2);
        v7 = gObjectEventGfxFrameSeqsTable;

        do {
            if (v7->id == v3) {
                break;
            }

            v7++;
            v1++;
        } while (v7->id != 0xffff);

        GF_ASSERT(v7->id != 0xffff);
        v11->unk_0C = FieldMap_021EDCF4(v8, v7->narcIdx, 0);
        BillboardGfxSequence_SetData(v11->unk_0C, &v11->unk_14);
    }

    {
        v1 = 0;
        v3 = v2;
        v7 = gObjectEventGfxTexturesTable;

        do {
            if (v7->id == v3) {
                break;
            }

            v7++;
            v1++;
        } while (v7->id != 0xffff);

        GF_ASSERT(v7->id != 0xffff);
        v11->unk_10 = FieldMap_021EDCF4(v8, v7->narcIdx, 0);
    }

    BillboardResources_SetWithoutKeys(&v11->unk_28, v11->unk_08, NNS_G3dGetTex(v11->unk_10), FieldMap_021EDD44(v2), &v11->unk_14);

    {
        const VecFx32 *v8 = Billboard_GetPos(v10);

        v0 = *v8;
        v11->unk_24 = FieldMap_021EDDDC(v9, &v11->unk_28, &v0, FieldMap_021EDD50(v2));
        GF_ASSERT(v11->unk_24 != NULL);
        v6 = v11->unk_24;
    }

    Billboard_SetRotMatrix(v11->unk_24, Billboard_GetRotMatrix(v10));
    Billboard_SetAnimNum(v11->unk_24, Billboard_GetAnimNum(v10));
    Billboard_SetAnimFrameNum(v11->unk_24, Billboard_GetAnimFrameNum(v10));
    Billboard_SetFrameNum(v11->unk_24, Billboard_GetFrameNum(v10));
    Billboard_AdvanceAnim(v11->unk_24, 0);
    Billboard_SetDrawFlag(v11->unk_24, 1);
    Billboard_TryRequestVRAMTransfer(v11->unk_24);

    {
        if (MapObject_CheckStatus24(param0) == 1) {
            VecFx32 v12;
            int v13;
            int v14 = MapObject_CalculateTaskPriority(param0, 2);
            u8 v15 = MapObject_GetTileBehaviorFromDir(param0, 1);

            if (TileBehavior_IsReflective(v15) == 1) {
                v13 = 2;
            } else if (TileBehavior_IsPuddle(v15) == 1) {
                v13 = 0;
            } else {
                v13 = 1;
            }

            MapObject_GetPosPtr(param0, &v12);
            v11->unk_54 = FieldMap_021F1BA4(MapObject_GetFieldEffectManager(param0), &v11->unk_28, v11->unk_24, &v12, v13, v14);
        }
    }

    MapObject_ClearGraphics(param0);
    FieldMap_021EDBC4(v8->unk_104, v2, param0);
    MapObject_SetGraphicsIDAndRefresh(param0, param1);

    {
        int v16 = MapObjectMan_GetTaskBasePriority(v8->unk_104);
        SysTask *v17 = SysTask_ExecuteAfterVBlank(FieldMap_021EE698, v11, 0xff);

        GF_ASSERT(v17 != NULL);
        FieldMap_021EE698(v17, v11);
    }

    if (Billboard_GetState(v11->unk_24) == 0) {
        v6 = NULL;
    } else {
        v11->unk_58 = param3;
        v11->unk_5C = param2;
    }

    return v6;
}

static void FieldMap_021EE698(SysTask *param0, void *param1)
{
    MapObjectBillboardAnim *v0 = param1;
    MapObject *v1 = v0->unk_50;

    switch (v0->unk_04) {
    case 0:
        if ((MapObject_IsActive(v1) == 0) || (FieldMap_021EDD94(v1) == 0)) {
            if (v0->unk_5C != NULL) {
                v0->unk_5C(
                    v0->unk_58, v0->unk_24);
            }

            if (v0->unk_54 != NULL) {
                OverworldAnimManager_Finish(v0->unk_54);
            }

            Billboard_Delete(v0->unk_24);
            Heap_Free(v0->unk_08);
            Heap_Free(v0->unk_0C);
            Heap_Free(v0->unk_10);
            Heap_Free(v0);
            SysTask_Done(param0);
            return;
        }

        if (MapObject_GetGraphicsID(v1) != v0->unk_00) {
            v0->unk_04++;
        }
        break;
    case 1:
        if (FieldMap_021EDD94(v1) == 0) {
            if (v0->unk_5C != NULL) {
                v0->unk_5C(
                    v0->unk_58, v0->unk_24);
            }

            if (v0->unk_54 != NULL) {
                OverworldAnimManager_Finish(v0->unk_54);
            }

            Billboard_Delete(v0->unk_24);
            Heap_Free(v0->unk_08);
            Heap_Free(v0->unk_0C);
            Heap_Free(v0->unk_10);
            Heap_Free(v0);
            SysTask_Done(param0);
        }
    }
}
