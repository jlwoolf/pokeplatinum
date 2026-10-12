#ifndef POKEPLATINUM_FIELDMAP_021F5A10_H
#define POKEPLATINUM_FIELDMAP_021F5A10_H

#include "struct_decls/map_object.h"

#include "field/field_system_decl.h"
#include "fieldmap/field_effect_manager.h"

#include "overworld_anim_manager.h"

void *FieldMap_021F5A10(FieldEffectManager *param0);
void FieldMap_021F5A24(void *param0);
void FieldMap_021F5AA4(FieldSystem *fieldSystem, BOOL param1);
int FieldMap_021F5C4C(OverworldAnimManager *param0);
void FieldMap_021F5C58(OverworldAnimManager *param0);
OverworldAnimManager *FieldMap_021F5D8C(MapObject *param0, int param1, int param2, int param3);

#endif // POKEPLATINUM_FIELDMAP_021F5A10_H
