#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_SYNCHRO_STATE_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_SYNCHRO_STATE_H

typedef struct {
    int timer;
    int readyCount;
    BOOL synchronized;
    BOOL triggered;
} PoffinCookingSynchroState;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_SYNCHRO_STATE_H
