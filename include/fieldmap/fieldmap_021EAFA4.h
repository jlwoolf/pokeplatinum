#ifndef POKEPLATINUM_FIELDMAP_021EAFA4_H
#define POKEPLATINUM_FIELDMAP_021EAFA4_H

#include <nitro/fx/fx.h>

#include "camera.h"

typedef struct FieldCamera {
    u16 fovY;
    u16 fovX;
    VecFx32 cameraDistance;
    VecFx32 upVector;
    fx32 cameraHeight;
    MtxFx43 rotationMatrix;
    Camera *camera;
    VecFx32 unk_54;
} FieldCamera;

VecFx32 FieldMap_GetPositionFromTouchCoordinates(u16 touchX, u16 touchY, const FieldCamera *param2);
FieldCamera *FieldMap_021EB0C8(Camera *const camera);
void FieldMap_021EB184(FieldCamera **param0);

#endif // POKEPLATINUM_FIELDMAP_021EAFA4_H
