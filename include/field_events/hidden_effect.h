#ifndef POKEPLATINUM_HIDDEN_EFFECT_H
#define POKEPLATINUM_HIDDEN_EFFECT_H

#include "field/field_system_decl.h"
#include "fieldmap/struct_fieldmap_021D1BEC_decl.h"

UnkStruct_fieldmap_021D1BEC *HiddenEffectSingle_New(FieldSystem *fieldSystem);
void HiddenEffectSingle_Delete(UnkStruct_fieldmap_021D1BEC *param0);
BOOL HiddenEffectSingle_IsFinished(UnkStruct_fieldmap_021D1BEC *param0);
UnkStruct_fieldmap_021D1BEC *HiddenEffectDouble_New(FieldSystem *fieldSystem);
UnkStruct_fieldmap_021D1BEC *HiddenEffectDoubleAtMapObject_New(FieldSystem *fieldSystem);
void HiddenEffectDouble_Delete(UnkStruct_fieldmap_021D1BEC *param0);
BOOL HiddenEffectDouble_IsFinished(UnkStruct_fieldmap_021D1BEC *param0);
UnkStruct_fieldmap_021D1BEC *HiddenEffectTransition_New(FieldSystem *fieldSystem);
void HiddenEffectTransition_Delete(UnkStruct_fieldmap_021D1BEC *param0);
UnkStruct_fieldmap_021D1BEC *HiddenEffectParticles_New(FieldSystem *fieldSystem);
void HiddenEffectParticles_Delete(UnkStruct_fieldmap_021D1BEC *param0);

#endif // POKEPLATINUM_HIDDEN_EFFECT_H
