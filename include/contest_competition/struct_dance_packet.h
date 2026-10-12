#ifndef POKEPLATINUM_STRUCT_DANCE_PACKET_H
#define POKEPLATINUM_STRUCT_DANCE_PACKET_H

typedef struct {
    u16 moveID;
    u8 contestantID;
    u8 judgeID;
    u8 score;
    u8 turn;
    u8 moveSlot;
    u8 contestantOrder;
    u8 isLastMove : 1;
    u8 isCombo : 1;
    u8 isValid : 1;
    u8 : 5;
} DancePacket;

#endif // POKEPLATINUM_STRUCT_DANCE_PACKET_H
