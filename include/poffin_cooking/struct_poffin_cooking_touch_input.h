#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_TOUCH_INPUT_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_TOUCH_INPUT_H

typedef struct {
    u8 x;
    u8 y;
    u16 distance;
    u8 direction;
    u8 unused_05[3];
} PoffinCookingTouchInput;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_TOUCH_INPUT_H
