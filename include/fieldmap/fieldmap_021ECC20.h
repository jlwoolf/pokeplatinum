#ifndef POKEPLATINUM_FIELDMAP_021ECC20_H
#define POKEPLATINUM_FIELDMAP_021ECC20_H

#include <nitro/fx/fx.h>

#include "struct_decls/map_object.h"
#include "struct_decls/map_object_manager.h"

#include "fieldmap/object_event_gfx_data.h"

void FieldMap_021ECC20(MapObjectManager *param0, int param1, int param2, const int *param3, int param4);
void FieldMap_021ECC78(MapObjectManager *param0);
void MapObject_Draw(MapObject *param0);
const ObjectEventGfxRenderDetailsEntry *FieldMap_021ECD04(const MapObject *param0);
int FieldMap_021ECD38(const MapObject *param0);
void *FieldMap_021ECD68(const MapObjectManager *param0, u32 param1, int param2);
void FieldMap_021ECDA0(const MapObject *param0, VecFx32 *param1);
void FieldMap_021ECDFC(MapObject *param0, int param1);
void FieldMap_021ECE18(MapObject *param0);
void FieldMap_021ECE30(MapObject *param0);
void FieldMap_021ECE34(MapObject *param0);
void FieldMap_021ECE38(MapObject *param0);
void FieldMap_021ECE3C(MapObject *param0);

#endif // POKEPLATINUM_FIELDMAP_021ECC20_H
