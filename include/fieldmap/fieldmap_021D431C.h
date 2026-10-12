#ifndef POKEPLATINUM_FIELDMAP_021D431C_H
#define POKEPLATINUM_FIELDMAP_021D431C_H

#include "field/field_system_decl.h"
#include "fieldmap/struct_fieldmap_021D432C_decl.h"
#include "fieldmap/struct_fieldmap_021D4E00_decl.h"

#include "field_task.h"

#define DOOR_SOUND_EFFECT_TYPE_HINGED                    0
#define DOOR_SOUND_EFFECT_TYPE_SLIDING                   1
#define DOOR_SOUND_EFFECT_TYPE_VEILSTONE_DPT_STORE_CHIME 2

UnkStruct_fieldmap_021D432C *FieldMap_021D431C(void);
void FieldMap_021D432C(UnkStruct_fieldmap_021D432C *param0);
void FieldMap_021D4334(const int param0, const int param1, UnkStruct_fieldmap_021D432C *param2);
BOOL FieldMap_021D433C(FieldSystem *fieldSystem, UnkStruct_fieldmap_021D432C *param1);
BOOL FieldMap_021D453C(FieldSystem *fieldSystem, UnkStruct_fieldmap_021D432C *param1);
BOOL FieldMap_021D4858(FieldSystem *fieldSystem, UnkStruct_fieldmap_021D432C *param1, const u8 param2);
BOOL FieldMap_021D4A24(FieldSystem *fieldSystem, UnkStruct_fieldmap_021D432C *param1, const u8 param2);
void DoorAnimation_FindDoorAndLoad(FieldSystem *fieldSystem, const int x, const int z, const u8 tag);
void DoorAnimation_PlayOpenAnimation(FieldSystem *fieldSystem, const u8 tag);
void DoorAnimation_PlayCloseAnimation(FieldSystem *fieldSystem, const u8 tag);
void FieldSystem_WaitForAnimation(FieldSystem *fieldSystem, const u8 tag);
void FieldSystem_UnloadAnimation(FieldSystem *fieldSystem, const u8 tag);
void FieldMap_021D4D78(const int param0, const int param1, const int param2, FieldSystem *param3);
UnkStruct_fieldmap_021D4E00 *FieldMap_021D4E00(void);
BOOL FieldMap_021D4E10(FieldTask *param0);
BOOL FieldMap_021D4F14(FieldTask *param0);
BOOL FieldMap_021D4FA0(FieldTask *param0);
BOOL FieldMap_021D5020(FieldTask *param0);
BOOL FieldMap_021D5150(FieldTask *param0);

#endif // POKEPLATINUM_FIELDMAP_021D431C_H
