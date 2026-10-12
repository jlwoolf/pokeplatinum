#ifndef POKEPLATINUM_STRUCT_ACTING_MESSAGE_PARAMS_H
#define POKEPLATINUM_STRUCT_ACTING_MESSAGE_PARAMS_H

typedef struct {
    u8 contestantID;
    u8 moveSlot;
    u16 moveID;
    u8 messageValue;
    u8 judgeID;
} ActingMessageParams;

#endif // POKEPLATINUM_STRUCT_ACTING_MESSAGE_PARAMS_H
