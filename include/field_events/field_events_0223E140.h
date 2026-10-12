#ifndef POKEPLATINUM_FIELD_EVENTS_0223E140_H
#define POKEPLATINUM_FIELD_EVENTS_0223E140_H

#include "field/field_system_decl.h"
#include "fieldmap/struct_fieldmap_021D1BEC_decl.h"
#include "field_events/struct_screen_transition_decl.h"
#include "field_events/struct_brightness_fader_decl.h"
#include "field_events/struct_climax_actor_manager_decl.h"
#include "field_events/struct_climax_object_decl.h"
#include "field_events/struct_climax_particles_decl.h"
#include "field_events/struct_climax_glow_decl.h"
#include "field_events/struct_climax_flash_decl.h"

#include "camera.h"
#include "field_task.h"

void ScreenTransition_StartSimple(FieldTask *param0);
void ScreenTransition_StartWithSound(FieldTask *param0);
UnkStruct_fieldmap_021D1BEC *ClimaxSequence_New(FieldSystem *fieldSystem);
void ClimaxSequence_Delete(UnkStruct_fieldmap_021D1BEC *param0);
BOOL ClimaxSequence_IsFinished(UnkStruct_fieldmap_021D1BEC *param0);
UnkStruct_fieldmap_021D1BEC *ClimaxObjectEffect_New(FieldSystem *fieldSystem);
void ClimaxObjectEffect_Delete(UnkStruct_fieldmap_021D1BEC *param0);
UnkStruct_fieldmap_021D1BEC *ClimaxScene_New(FieldSystem *fieldSystem, u32 param1);
UnkStruct_fieldmap_021D1BEC *ClimaxActor_New(FieldSystem *fieldSystem);
void ClimaxActor_Delete(UnkStruct_fieldmap_021D1BEC *param0);
void ClimaxActor_Finish(UnkStruct_fieldmap_021D1BEC *param0);
u32 ClimaxActor_GetState(UnkStruct_fieldmap_021D1BEC *param0);
void ScreenTransition_Free(ScreenTransition *param0);
void ScreenTransition_Init(ScreenTransition *param0, fx32 param1, fx32 param2, u32 param3, u32 param4, Camera *camera);
void ScreenTransition_Update(ScreenTransition *param0);
BOOL ScreenTransition_IsFinished(ScreenTransition *param0);
u32 ScreenTransition_GetLoopCount(const ScreenTransition *param0);
fx32 ScreenTransition_GetAmplitude(const ScreenTransition *param0);
void ScreenTransition_SetAmplitude(ScreenTransition *param0, fx32 param1);
void BrightnessFader_Start(BrightnessFader *param0, u32 param1, u32 param2, u32 param3);
int BrightnessFader_GetValue(const BrightnessFader *param0);
ClimaxActorManager *ClimaxActorManager_New(FieldSystem *fieldSystem);
void ClimaxActorManager_Free(ClimaxActorManager *param0);
void ClimaxActorManager_Draw(ClimaxActorManager *param0);
ClimaxObject *ClimaxObject_New(enum HeapID heapID, FieldSystem *fieldSystem);
void ClimaxObject_Free(ClimaxObject *param0);
void ClimaxObject_Start(ClimaxObject *param0, u32 param1);
BOOL ClimaxObject_IsIdle(ClimaxObject *param0);
void ClimaxObject_Cleanup(ClimaxObject *param0);
ClimaxParticles *ClimaxParticles_NewDefault(enum HeapID heapID);
void ClimaxParticles_Delete(ClimaxParticles *param0);
void ClimaxParticles_SetPosition(ClimaxParticles *param0, u16 param1, u16 param2, u16 param3);
void ClimaxParticles_UpdatePublic(ClimaxParticles *param0);
void ClimaxParticles_DrawPublic(ClimaxParticles *param0);
ClimaxGlow *ClimaxGlow_NewDefault(enum HeapID heapID);
void ClimaxGlow_Delete(ClimaxGlow *param0);
void ClimaxGlow_UpdatePublic(ClimaxGlow *param0);
void ClimaxGlow_DrawPublic(ClimaxGlow *param0);
void ClimaxGlow_SetPositionVariant0(ClimaxGlow *param0, fx32 param1, fx32 param2, fx32 param3);
void ClimaxGlow_SetPositionVariant1(ClimaxGlow *param0, fx32 param1, fx32 param2, fx32 param3);
void ClimaxGlow_SetPositionVariant2(ClimaxGlow *param0, fx32 param1, fx32 param2, fx32 param3);
ClimaxParticles *ClimaxParticles_NewDefault2(enum HeapID heapID);
void ClimaxParticles_Delete2(ClimaxParticles *param0);
void ClimaxParticles_Update2(ClimaxParticles *param0);
void ClimaxParticles_Draw2(ClimaxParticles *param0);
void ClimaxParticles_SetPositionVariant0(ClimaxParticles *param0, fx32 param1, fx32 param2, fx32 param3);
void ClimaxParticles_SetPositionVariant1(ClimaxParticles *param0, fx32 param1, fx32 param2, fx32 param3);
void ClimaxParticles_SetPositionVariant2(ClimaxParticles *param0, fx32 param1, fx32 param2, fx32 param3);
ClimaxFlash *ClimaxFlash_New(enum HeapID heapID, FieldSystem *fieldSystem);
void ClimaxFlash_Start(ClimaxFlash *param0, u32 param1);
BOOL ClimaxFlash_IsFinished(ClimaxFlash *param0);
void ClimaxFlash_Draw(ClimaxFlash *param0);

#endif // POKEPLATINUM_FIELD_EVENTS_0223E140_H
