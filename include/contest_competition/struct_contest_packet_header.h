#ifndef POKEPLATINUM_STRUCT_CONTEST_PACKET_HEADER_H
#define POKEPLATINUM_STRUCT_CONTEST_PACKET_HEADER_H

typedef struct {
    u16 size;
    u16 type;
    u8 targetContestantID;
    u8 slot;
    u8 isBroadcast;
    u8 unused_07[1];
} ContestPacketHeader;

#endif // POKEPLATINUM_STRUCT_CONTEST_PACKET_HEADER_H
