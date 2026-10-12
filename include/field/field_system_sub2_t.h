#ifndef POKEPLATINUM_FIELD_SYSTEM_SUB2_T_H
#define POKEPLATINUM_FIELD_SYSTEM_SUB2_T_H

#include "applications/poketch/poketch_system.h"
#include "fieldmap/hblank_system.h"
#include "fieldmap/map_name_popup.h"
#include "fieldmap/struct_fieldmap_021D1A94_decl.h"
#include "fieldmap/struct_fieldmap_021D5EF8_decl.h"
#include "fieldmap/struct_fieldmap_021EF4F8_decl.h"
#include "fieldmap/texture_resource_manager.h"

#include "berry_patch_manager.h"

struct FieldSystem_sub2_t {
    BOOL unk_00;
    UnkStruct_fieldmap_021D1A94 *unk_04;
    MapNamePopUp *mapPopup;
    UnkStruct_fieldmap_021D5EF8 *unk_0C;
    FieldTextureManager *unk_10;
    PoketchSystem *poketchSys;
    BerryPatchManager *berryPatchManager;
    HBlankSystem *hBlankSystem;
    UnkStruct_fieldmap_021EF4F8 *unk_20;
    void *dynamicMapFeaturesData;
};

#endif // POKEPLATINUM_FIELD_SYSTEM_SUB2_T_H
