#ifndef POKEPLATINUM_FIELDMAP_021ECE40_H
#define POKEPLATINUM_FIELDMAP_021ECE40_H

#include "struct_decls/map_object.h"
#include "struct_decls/map_object_manager.h"

#include "fieldmap/funcptr_fieldmap_021EE454.h"
#include "fieldmap/struct_billboard_anim_state.h"
#include "fieldmap/struct_map_object_draw_manager.h"

#include "billboard.h"
#include "resource_collection.h"

void FieldMap_021ECE40(MapObjectDrawManager *param0, const MapObjectManager *param1, int param2, int param3, int param4, int param5, const int *param6, int param7);
void FieldMap_021ECE94(MapObjectDrawManager *param0);
int FieldMap_021ECEB4(MapObject *param0, Billboard **param1, int param2);
int FieldMap_021ECF04(MapObject *param0, Billboard **param1);
Billboard *FieldMap_021ECF1C(MapObject *param0, int param1);
void FieldMap_021ECF70(const MapObject *param0, Billboard **param1, int param2);
void FieldMap_021ECFA4(const MapObject *param0, Billboard **param1);
void FieldMap_021ECFD8(const MapObject *param0, Billboard **param1, int param2);
void FieldMap_021ED01C(Billboard *param0, BillboardAnimState *param1);
void FieldMap_021ED03C(Billboard *param0, BillboardAnimState *param1);
void FieldMap_021ED060(MapObject *param0, Billboard **param1, int param2);
int FieldMap_021ED150(const MapObjectManager *param0, u32 param1, BillboardResources *param2);
void FieldMap_021EDA38(MapObjectManager *param0, MapObjectDrawManager *param1);
void FieldMap_021EDBC4(const MapObjectManager *param0, int param1, MapObject *param2);
void FieldMap_021EDC84(MapObjectDrawManager *param0, BillboardList *param1);
BillboardList *FieldMap_021EDC8C(MapObjectDrawManager *param0);
void FieldMap_021EDC94(MapObjectDrawManager *param0, int param1);
ResourceCollection *FieldMap_021EDC98(const MapObjectDrawManager *param0);
ResourceCollection *FieldMap_021EDCA0(const MapObjectDrawManager *param0);
void FieldMap_021EDCA8(MapObjectDrawManager *param0, TextureResourceManager *param1);
TextureResourceManager *FieldMap_021EDCB0(const MapObjectDrawManager *param0);
void FieldMap_021EDD78(MapObject *param0, int param1);
int FieldMap_021EDD94(MapObject *param0);
BOOL FieldMap_021EDEB4(MapObject *param0, Billboard *param1);
void FieldMap_021EDED8(MapObject *param0, Billboard *param1);
int FieldMap_021EDF18(int param0);
int FieldMap_021EDF24(int param0);
int FieldMap_021EDF30(int param0);
Billboard *FieldMap_021EE3FC(MapObject *param0, int param1, UnkFuncPtr_fieldmap_021EE454 param2, void *param3);

#endif // POKEPLATINUM_FIELDMAP_021ECE40_H
