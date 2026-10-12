#include "fieldmap/field_effect_renderer.h"

#include <nitro.h>
#include <string.h>

#include "constants/field/field_effect_renderer.h"

#include "fieldmap/berry_patch_effects.h"
#include "fieldmap/dist_world_surf_mount_renderer.h"
#include "fieldmap/fieldmap_021F10E8.h"
#include "fieldmap/fieldmap_021F134C.h"
#include "fieldmap/fieldmap_021F17B8.h"
#include "fieldmap/fieldmap_021F1CC8.h"
#include "fieldmap/fieldmap_021F23D0.h"
#include "fieldmap/fieldmap_021F2850.h"
#include "fieldmap/fieldmap_021F2A7C.h"
#include "fieldmap/fieldmap_021F2BD0.h"
#include "fieldmap/fieldmap_021F2D20.h"
#include "fieldmap/fieldmap_021F3284.h"
#include "fieldmap/fieldmap_021F348C.h"
#include "fieldmap/fieldmap_021F37A8.h"
#include "fieldmap/fieldmap_021F3A50.h"
#include "fieldmap/fieldmap_021F3D00.h"
#include "fieldmap/fieldmap_021F3E74.h"
#include "fieldmap/fieldmap_021F4018.h"
#include "fieldmap/fieldmap_021F47B0.h"
#include "fieldmap/fieldmap_021F4DAC.h"
#include "fieldmap/fieldmap_021F4E08.h"
#include "fieldmap/fieldmap_021F5060.h"
#include "fieldmap/fieldmap_021F50BC.h"
#include "fieldmap/fieldmap_021F5284.h"
#include "fieldmap/fieldmap_021F5428.h"
#include "fieldmap/fieldmap_021F55CC.h"
#include "fieldmap/fieldmap_021F575C.h"
#include "fieldmap/fieldmap_021F5894.h"
#include "fieldmap/fieldmap_021F5A10.h"
#include "fieldmap/fieldmap_021F600C.h"
#include "fieldmap/fieldmap_021F61BC.h"
#include "fieldmap/surf_mount_renderer.h"
#include "fieldmap/veilstone_gym_object_renderer.h"

const FieldEffectRendererFuncs sFieldEffectRendererHandlers[FIELD_EFFECT_RENDERER_COUNT + 1] = {
    { FIELD_EFFECT_RENDERER_00, FieldMap_021F134C, FieldMap_021F1370 },
    { FIELD_EFFECT_RENDERER_01, FieldMap_021F17B8, FieldMap_021F17D4 },
    { FIELD_EFFECT_RENDERER_02, FieldMap_021F4DAC, FieldMap_021F4DC8 },
    { FIELD_EFFECT_RENDERER_03, FieldMap_021F4E08, FieldMap_021F4E28 },
    { FIELD_EFFECT_RENDERER_04, FieldMap_021F5060, FieldMap_021F507C },
    { FIELD_EFFECT_RENDERER_05, FieldMap_021F50BC, FieldMap_021F50D8 },
    { FIELD_EFFECT_RENDERER_06, FieldMap_021F5284, FieldMap_021F52A0 },
    { FIELD_EFFECT_RENDERER_07, FieldMap_021F5428, FieldMap_021F5444 },
    { FIELD_EFFECT_RENDERER_08, FieldMap_021F55CC, FieldMap_021F55E8 },
    { FIELD_EFFECT_RENDERER_09, FieldMap_021F575C, FieldMap_021F5778 },
    { FIELD_EFFECT_RENDERER_0A, FieldMap_021F5894, FieldMap_021F58B0 },
    { FIELD_EFFECT_RENDERER_0B, FieldMap_021F1CC8, FieldMap_021F1CE8 },
    { FIELD_EFFECT_RENDERER_BERRY_PATCH, BerryPatchGraphicsManager_New, BerryPatchGraphicsManager_Free },
    { FIELD_EFFECT_RENDERER_0D, FieldMap_021F23D0, FieldMap_021F23EC },
    { FIELD_EFFECT_RENDERER_0E, FieldMap_021F61BC, FieldMap_021F61D8 },
    { FIELD_EFFECT_RENDERER_SURF_MOUNT, SurfMountRenderer_New, SurfMountRenderer_Free },
    { FIELD_EFFECT_RENDERER_10, FieldMap_021F2850, FieldMap_021F2864 },
    { FIELD_EFFECT_RENDERER_11, FieldMap_021F2A7C, FieldMap_021F2A98 },
    { FIELD_EFFECT_RENDERER_12, FieldMap_021F2BD0, FieldMap_021F2BEC },
    { FIELD_EFFECT_RENDERER_13, FieldMap_021F2D20, FieldMap_021F2D3C },
    { FIELD_EFFECT_RENDERER_14, FieldMap_021F5A10, FieldMap_021F5A24 },
    { FIELD_EFFECT_RENDERER_15, FieldMap_021F3284, FieldMap_021F32A0 },
    { FIELD_EFFECT_RENDERER_16, FieldMap_021F600C, FieldMap_021F6028 },
    { FIELD_EFFECT_RENDERER_17, FieldMap_021F348C, FieldMap_021F34A8 },
    { FIELD_EFFECT_RENDERER_18, FieldMap_021F37A8, FieldMap_021F37C4 },
    { FIELD_EFFECT_RENDERER_19, FieldMap_021F3A50, FieldMap_021F3A6C },
    { FIELD_EFFECT_RENDERER_1A, FieldMap_021F3D00, FieldMap_021F3D1C },
    { FIELD_EFFECT_RENDERER_1B, FieldMap_021F3E74, FieldMap_021F3E90 },
    { FIELD_EFFECT_RENDERER_BERRY_PATCH_EFFECT_COUNTER, BerryPatchGraphicsManager_NewEffectCounter, BerryPatchGraphicsManager_FreeEffectCounter },
    { FIELD_EFFECT_RENDERER_1D, FieldMap_021F10E8, FieldMap_021F10FC },
    { FIELD_EFFECT_RENDERER_1E, FieldMap_021F4018, FieldMap_021F4034 },
    { FIELD_EFFECT_RENDERER_VEILSTONE_GYM_OBJECTS, VeilstoneGymObjectRenderer_New, VeilstoneGymObjectRenderer_Free },
    { FIELD_EFFECT_RENDERER_20, FieldMap_021F47B0, FieldMap_021F47CC },
    { FIELD_EFFECT_RENDERER_DISTORTION_WORLD_SURF_MOUNT, DistWorldSurfMountRenderer_New, DistWorldSurfMountRenderer_Free },
    { FIELD_EFFECT_RENDERER_INVALID, NULL, NULL }
};

const u32 sDefaultFieldEffectRenderers[FIELD_EFFECT_RENDERER_COUNT + 1] = {
    FIELD_EFFECT_RENDERER_1D,
    FIELD_EFFECT_RENDERER_00,
    FIELD_EFFECT_RENDERER_0B,
    FIELD_EFFECT_RENDERER_BERRY_PATCH,
    FIELD_EFFECT_RENDERER_0E,
    FIELD_EFFECT_RENDERER_SURF_MOUNT,
    FIELD_EFFECT_RENDERER_10,
    FIELD_EFFECT_RENDERER_1A,
    FIELD_EFFECT_RENDERER_0D,
    FIELD_EFFECT_RENDERER_11,
    FIELD_EFFECT_RENDERER_12,
    FIELD_EFFECT_RENDERER_13,
    FIELD_EFFECT_RENDERER_14,
    FIELD_EFFECT_RENDERER_15,
    FIELD_EFFECT_RENDERER_16,
    FIELD_EFFECT_RENDERER_17,
    FIELD_EFFECT_RENDERER_18,
    FIELD_EFFECT_RENDERER_19,
    FIELD_EFFECT_RENDERER_1B,
    FIELD_EFFECT_RENDERER_01,
    FIELD_EFFECT_RENDERER_BERRY_PATCH_EFFECT_COUNTER,
    FIELD_EFFECT_RENDERER_INVALID
};

const u32 sUndergroundFieldEffectRenderers[FIELD_EFFECT_RENDERER_COUNT + 1] = {
    FIELD_EFFECT_RENDERER_1D,
    FIELD_EFFECT_RENDERER_02,
    FIELD_EFFECT_RENDERER_03,
    FIELD_EFFECT_RENDERER_04,
    FIELD_EFFECT_RENDERER_05,
    FIELD_EFFECT_RENDERER_06,
    FIELD_EFFECT_RENDERER_07,
    FIELD_EFFECT_RENDERER_0E,
    FIELD_EFFECT_RENDERER_08,
    FIELD_EFFECT_RENDERER_09,
    FIELD_EFFECT_RENDERER_0A,
    FIELD_EFFECT_RENDERER_14,
    FIELD_EFFECT_RENDERER_INVALID
};

const u32 sDistWorldFieldEffectRenderers[FIELD_EFFECT_RENDERER_COUNT + 1] = {
    FIELD_EFFECT_RENDERER_1D,
    FIELD_EFFECT_RENDERER_14,
    FIELD_EFFECT_RENDERER_DISTORTION_WORLD_SURF_MOUNT,
    FIELD_EFFECT_RENDERER_17,
    FIELD_EFFECT_RENDERER_0E,
    FIELD_EFFECT_RENDERER_INVALID
};
