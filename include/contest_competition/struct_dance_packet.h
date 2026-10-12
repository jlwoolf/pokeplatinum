#ifndef POKEPLATINUM_STRUCT_DANCE_PACKET_H
#define POKEPLATINUM_STRUCT_DANCE_PACKET_H

typedef struct {
    u16 unk_00;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08_0 : 1;
    u8 unk_08_1 : 1;
    u8 unk_08_2 : 1;
    u8 : 5;
} DancePacket;

#endif // POKEPLATINUM_STRUCT_DANCE_PACKET_H
