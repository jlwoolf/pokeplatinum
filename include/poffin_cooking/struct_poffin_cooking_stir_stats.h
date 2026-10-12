#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_STIR_STATS_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_STIR_STATS_H

typedef struct {
    u32 goodStirCount;
    u32 greatStirCount;
    u32 goodStirTimer;
    u32 greatStirTimer;
    u32 messageType;
    BOOL messageToggle;
    BOOL greatStirTriggered;
} PoffinCookingStirStats;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_STIR_STATS_H
