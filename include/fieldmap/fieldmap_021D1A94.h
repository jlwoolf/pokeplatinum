#ifndef POKEPLATINUM_FIELDMAP_021D1A94_H
#define POKEPLATINUM_FIELDMAP_021D1A94_H

#include "constants/heap.h"

#include "field/field_system_decl.h"
#include "fieldmap/struct_field_effect_system_decl.h"
#include "fieldmap/struct_field_effect_decl.h"
#include "field_events/struct_field_effect.h"

FieldEffectSystem *FieldMap_021D1A94(FieldSystem *fieldSystem, enum HeapID heapID, int param2);
void FieldMap_021D1AE4(FieldEffectSystem *param0);
void FieldMap_021D1B18(FieldEffectSystem *param0);
FieldEffect *FieldMap_021D1B6C(FieldEffectSystem *param0, const FieldEffectTemplate *param1);
void FieldMap_021D1BEC(FieldEffect *param0);
void *FieldMap_021D1C2C(FieldEffect *param0);

#endif // POKEPLATINUM_FIELDMAP_021D1A94_H
