#ifndef POKEPLATINUM_FIELDMAP_021F2D20_H
#define POKEPLATINUM_FIELDMAP_021F2D20_H

#include "struct_decls/map_object.h"

#include "field/field_system_decl.h"
#include "fieldmap/field_effect_manager.h"

#include "overworld_anim_manager.h"

void *FieldMap_021F2D20(FieldEffectManager *param0);
void FieldMap_021F2D3C(void *param0);
void FieldMap_021F2EA4(MapObject *param0, int param1);
OverworldAnimManager *FieldMap_021F3154(FieldSystem *fieldSystem, int param1, int param2, int param3);
int FieldMap_021F31A8(OverworldAnimManager *param0);

#endif // POKEPLATINUM_FIELDMAP_021F2D20_H
