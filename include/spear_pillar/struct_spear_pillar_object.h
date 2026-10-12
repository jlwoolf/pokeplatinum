#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_OBJECT_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_OBJECT_H

#include "spear_pillar/struct_spear_pillar_object_anim_step.h"

#include "easy3d_object.h"

typedef struct {
    Easy3DObject object;
    Easy3DModel model;
    Easy3DAnim anims[10];
    fx32 scale;
    fx32 animSpeed;
    int animID;
    int animFrame;
    BOOL isAnimating;
    BOOL useAnimation;
    BOOL loopAnim1;
    BOOL updateAnim1;
    BOOL updateAllAnims;
    BOOL isLoaded;
    int framesRemaining;
    int stepFrameCount;
    int stepIndex;
    SpearPillarObjectAnimStep *animSteps;
} SpearPillarObject;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_OBJECT_H
