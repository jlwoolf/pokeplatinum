#ifndef POKEPLATINUM_STRUCT_DANCE_MESSAGE_ARGS_H
#define POKEPLATINUM_STRUCT_DANCE_MESSAGE_ARGS_H

typedef struct {
    u8 contestantID;
    u8 moveID;
    u16 unused_02;
    u8 moveSlot;
    u8 unused_05;
} DanceMessageArgs;

#endif // POKEPLATINUM_STRUCT_DANCE_MESSAGE_ARGS_H
