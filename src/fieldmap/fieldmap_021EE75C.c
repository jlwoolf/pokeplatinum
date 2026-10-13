#include "fieldmap/fieldmap_021EE75C.h"

#include <nitro.h>
#include <string.h>

#include "field/field_system.h"
#include "field/field_system_sub2_t.h"
#include "fieldmap/fieldmap_021D1A94.h"
#include "fieldmap/fieldmap_021D431C.h"
#include "fieldmap/struct_field_effect_decl.h"
#include "field_events/struct_field_effect.h"

#include "map_tile_behavior.h"
#include "player_avatar.h"
#include "terrain_collision_manager.h"

typedef struct {
    int lastX;
    int lastZ;
} BikeSlopeEffect;

static void FieldMap_021EE75C(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    BikeSlopeEffect *v0 = (BikeSlopeEffect *)param2;

    v0->lastX = 0;
    v0->lastZ = 0;
}

static void FieldMap_021EE764(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    return;
}

static void FieldMap_021EE768(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    u8 v0;
    int v1, v2;
    u8 v3;
    BikeSlopeEffect *v4 = (BikeSlopeEffect *)param2;

    v1 = PlayerAvatar_GetXPos(fieldSystem->playerAvatar);
    v2 = PlayerAvatar_GetZPos(fieldSystem->playerAvatar);

    if ((v4->lastX == v1) && (v4->lastZ == v2)) {
        return;
    }

    v4->lastX = v1;
    v4->lastZ = v2;

    v0 = TerrainCollisionManager_GetTileBehavior(fieldSystem, v1, v2);

    if (TileBehavior_IsBikeSlopeBottom(v0)) {
        v3 = 0;
    } else if (TileBehavior_IsBikeSlopeTop(v0)) {
        v3 = 1;
    } else {
        return;
    }

    FieldMap_021D4D78(v1, v2, v3, fieldSystem);
}

static const FieldEffectTemplate Unk_FieldMap_021FF4F0 = {
    0x2,
    sizeof(BikeSlopeEffect),
    FieldMap_021EE75C,
    FieldMap_021EE764,
    FieldMap_021EE768,
    NULL
};

void FieldMap_021EE7C0(FieldSystem *fieldSystem)
{
    FieldMap_021D1B6C(fieldSystem->unk_04->unk_04, &Unk_FieldMap_021FF4F0);
}
