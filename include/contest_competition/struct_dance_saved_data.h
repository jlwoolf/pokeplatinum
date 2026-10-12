#ifndef POKEPLATINUM_STRUCT_DANCE_SAVED_DATA_H
#define POKEPLATINUM_STRUCT_DANCE_SAVED_DATA_H

typedef struct {
    u16 *data;
    u16 unused_04;
    u16 blendMode;
    u16 current;
    u16 target;
    s16 step;
    u16 duration;
    u8 active;
    u8 state;
} DanceSavedData;

#endif // POKEPLATINUM_STRUCT_DANCE_SAVED_DATA_H
