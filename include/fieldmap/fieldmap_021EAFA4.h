#ifndef POKEPLATINUM_FIELDMAP_021EAFA4_H
#define POKEPLATINUM_FIELDMAP_021EAFA4_H

#include <nitro/fx/fx.h>

#include "camera.h"

typedef struct UnkStruct_fieldmap_021EB0E0 {
    u16 fovY;
    u16 unk_02;
    VecFx32 cameraDistance;
    VecFx32 unk_10;
    fx32 unk_1C;
    MtxFx43 unk_20;
    Camera *camera;
    VecFx32 unk_54;
} UnkStruct_fieldmap_021EB0E0;

VecFx32 FieldMap_GetPositionFromTouchCoordinates(u16 touchX, u16 touchY, const UnkStruct_fieldmap_021EB0E0 *param2);
UnkStruct_fieldmap_021EB0E0 *FieldMap_021EB0C8(Camera *const camera);
void FieldMap_021EB184(UnkStruct_fieldmap_021EB0E0 **param0);

#endif // POKEPLATINUM_FIELDMAP_021EAFA4_H
