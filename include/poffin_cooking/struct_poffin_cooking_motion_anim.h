#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_MOTION_ANIM_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_MOTION_ANIM_H

typedef struct {
    fx32 current;
    fx32 start;
    fx32 velocity;
    fx32 acceleration;
    int elapsed;
    int duration;
} PoffinCookingMotionAnim;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_MOTION_ANIM_H
