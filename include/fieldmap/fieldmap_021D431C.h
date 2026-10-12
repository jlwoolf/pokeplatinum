#ifndef POKEPLATINUM_FIELDMAP_021D431C_H
#define POKEPLATINUM_FIELDMAP_021D431C_H

#include "field/field_system_decl.h"
#include "fieldmap/struct_door_animation_decl.h"
#include "fieldmap/struct_door_animation_env_decl.h"

#include "field_task.h"

#define DOOR_SOUND_EFFECT_TYPE_HINGED                    0
#define DOOR_SOUND_EFFECT_TYPE_SLIDING                   1
#define DOOR_SOUND_EFFECT_TYPE_VEILSTONE_DPT_STORE_CHIME 2

DoorAnimation *FieldMap_021D431C(void);
void FieldMap_021D432C(DoorAnimation *param0);
void FieldMap_021D4334(const int param0, const int param1, DoorAnimation *param2);
BOOL FieldMap_021D433C(FieldSystem *fieldSystem, DoorAnimation *param1);
BOOL FieldMap_021D453C(FieldSystem *fieldSystem, DoorAnimation *param1);
BOOL FieldMap_021D4858(FieldSystem *fieldSystem, DoorAnimation *param1, const u8 param2);
BOOL FieldMap_021D4A24(FieldSystem *fieldSystem, DoorAnimation *param1, const u8 param2);
void DoorAnimation_FindDoorAndLoad(FieldSystem *fieldSystem, const int x, const int z, const u8 tag);
void DoorAnimation_PlayOpenAnimation(FieldSystem *fieldSystem, const u8 tag);
void DoorAnimation_PlayCloseAnimation(FieldSystem *fieldSystem, const u8 tag);
void FieldSystem_WaitForAnimation(FieldSystem *fieldSystem, const u8 tag);
void FieldSystem_UnloadAnimation(FieldSystem *fieldSystem, const u8 tag);
void FieldMap_021D4D78(const int param0, const int param1, const int param2, FieldSystem *param3);
DoorAnimationEnv *FieldMap_021D4E00(void);
BOOL FieldMap_021D4E10(FieldTask *param0);
BOOL FieldMap_021D4F14(FieldTask *param0);
BOOL FieldMap_021D4FA0(FieldTask *param0);
BOOL FieldMap_021D5020(FieldTask *param0);
BOOL FieldMap_021D5150(FieldTask *param0);

#endif // POKEPLATINUM_FIELDMAP_021D431C_H
