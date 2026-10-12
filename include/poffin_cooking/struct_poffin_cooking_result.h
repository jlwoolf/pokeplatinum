#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_RESULT_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_RESULT_H

typedef struct {
    u32 greatStirCount;
    u32 goodStirCount;
    u32 smoothness;
    u8 poffinSpecies;
    u8 level;
    u8 minutes;
    u8 seconds;
    u8 centiseconds;
    u8 unused_11[3];
} PoffinCookingResult;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_RESULT_H
