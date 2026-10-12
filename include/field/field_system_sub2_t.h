#ifndef POKEPLATINUM_FIELD_SYSTEM_SUB2_T_H
#define POKEPLATINUM_FIELD_SYSTEM_SUB2_T_H

#include "applications/poketch/poketch_system.h"
#include "fieldmap/hblank_system.h"
#include "fieldmap/map_name_popup.h"
#include "fieldmap/struct_field_effect_system_decl.h"
#include "fieldmap/struct_field_map_weather_decl.h"
#include "fieldmap/struct_poison_effect_decl.h"
#include "fieldmap/texture_resource_manager.h"

#include "berry_patch_manager.h"

struct FieldSystem_sub2_t {
    BOOL unk_00;
    FieldEffectSystem *unk_04;
    MapNamePopUp *mapPopup;
    FieldMapWeather *unk_0C;
    FieldTextureManager *unk_10;
    PoketchSystem *poketchSys;
    BerryPatchManager *berryPatchManager;
    HBlankSystem *hBlankSystem;
    PoisonEffect *unk_20;
    void *dynamicMapFeaturesData;
};

#endif // POKEPLATINUM_FIELD_SYSTEM_SUB2_T_H
