#ifndef POKEPLATINUM_FIELDMAP_021D1A94_H
#define POKEPLATINUM_FIELDMAP_021D1A94_H

#include "constants/heap.h"

#include "field/field_system_decl.h"
#include "fieldmap/struct_fieldmap_021D1A94_decl.h"
#include "fieldmap/struct_fieldmap_021D1BEC_decl.h"
#include "overlay006/struct_ov6_0223E6EC.h"

UnkStruct_fieldmap_021D1A94 *FieldMap_021D1A94(FieldSystem *fieldSystem, enum HeapID heapID, int param2);
void FieldMap_021D1AE4(UnkStruct_fieldmap_021D1A94 *param0);
void FieldMap_021D1B18(UnkStruct_fieldmap_021D1A94 *param0);
UnkStruct_fieldmap_021D1BEC *FieldMap_021D1B6C(UnkStruct_fieldmap_021D1A94 *param0, const UnkStruct_ov6_0223E6EC *param1);
void FieldMap_021D1BEC(UnkStruct_fieldmap_021D1BEC *param0);
void *FieldMap_021D1C2C(UnkStruct_fieldmap_021D1BEC *param0);

#endif // POKEPLATINUM_FIELDMAP_021D1A94_H
