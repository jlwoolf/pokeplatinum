#ifndef POKEPLATINUM_STRUCT_CONTEST_PACKET_QUEUE_H
#define POKEPLATINUM_STRUCT_CONTEST_PACKET_QUEUE_H

struct ContestPacketHandler_t;

typedef struct {
    const struct ContestPacketHandler_t *unk_00;
    u16 unk_04;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u32 unk_0C;
    u8 unk_10[512];
    u8 unk_210[4][512];
    u8 unk_A10;
    u8 unk_A11[4];
    u8 unk_A15;
} ContestPacketQueue;

#endif // POKEPLATINUM_STRUCT_CONTEST_PACKET_QUEUE_H
