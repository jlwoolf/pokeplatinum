#ifndef POKEPLATINUM_SPEAR_PILLAR_COMMON_H
#define POKEPLATINUM_SPEAR_PILLAR_COMMON_H

#include <nnsys.h>

#include "struct_defs/struct_020985E4.h"

#include "spear_pillar/struct_spear_pillar_context.h"
#include "spear_pillar/struct_spear_pillar_camera_anim.h"
#include "spear_pillar/struct_spear_pillar_object.h"
#include "spear_pillar/struct_spear_pillar.h"

#include "narc.h"

int SpearPillar_PrintMessage(SpearPillarContext *param0, SpearPillarTaskArgs *param1, int param2);
void SpearPillar_EraseMessage(SpearPillarContext *param0);
void SpearPillar_SetupLighting(SpearPillarContext *param0);
void SpearPillar_UpdateCamera(SpearPillarContext *param0);
void SpearPillar_StartCameraAnim(SpearPillarCameraAnim *param0);
BOOL SpearPillar_UpdateCameraAnim(SpearPillarCameraAnim *param0);
void SpearPillar_DrawObject(SpearPillarObject *param0);
void SpearPillar_ReleaseModel(SpearPillarObject *param0);
void SpearPillar_ReleaseAnim(int param0, SpearPillarObject *param1, NNSFndAllocator *param2);
void SpearPillar_FreeObject(SpearPillarObject *param0, NNSFndAllocator *param1, int param2);
void SpearPillar_LoadObject(SpearPillarObject *param0, int param1, NARC *param2);
void SpearPillar_CloneObject(SpearPillarObject *param0, SpearPillarObject *param1, int param2, NARC *param3);
void SpearPillar_LoadObjectAnim(int param0, SpearPillarObject *param1, int param2, NARC *param3, NNSFndAllocator *param4);
void SpearPillar_CloneObjectAnim(int param0, SpearPillarObject *param1, SpearPillarObject *param2, int param3, NARC *param4, NNSFndAllocator *param5);
void SpearPillar_BlendBg(SpearPillarContext *param0);
void SpearPillar_BlendBgByScene(SpearPillarContext *param0, int param1);
void SpearPillar_Set3DScreen(int param0);
void SpearPillar_SetBrightness(SpearPillar *param0, int param1);

#endif // POKEPLATINUM_SPEAR_PILLAR_COMMON_H
