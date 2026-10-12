#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_SCALE_ANIM_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_SCALE_ANIM_H

typedef struct {
    fx32 current;
    fx32 start;
    fx32 delta;
    int elapsed;
    int duration;
} PoffinCookingScaleAnim;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_SCALE_ANIM_H
