#ifndef POKEPLATINUM_HIDDEN_EFFECT_H
#define POKEPLATINUM_HIDDEN_EFFECT_H

#include "field/field_system_decl.h"
#include "fieldmap/struct_field_effect_decl.h"

FieldEffect *HiddenEffectSingle_New(FieldSystem *fieldSystem);
void HiddenEffectSingle_Delete(FieldEffect *param0);
BOOL HiddenEffectSingle_IsFinished(FieldEffect *param0);
FieldEffect *HiddenEffectDouble_New(FieldSystem *fieldSystem);
FieldEffect *HiddenEffectDoubleAtMapObject_New(FieldSystem *fieldSystem);
void HiddenEffectDouble_Delete(FieldEffect *param0);
BOOL HiddenEffectDouble_IsFinished(FieldEffect *param0);
FieldEffect *HiddenEffectTransition_New(FieldSystem *fieldSystem);
void HiddenEffectTransition_Delete(FieldEffect *param0);
FieldEffect *HiddenEffectParticles_New(FieldSystem *fieldSystem);
void HiddenEffectParticles_Delete(FieldEffect *param0);

#endif // POKEPLATINUM_HIDDEN_EFFECT_H
