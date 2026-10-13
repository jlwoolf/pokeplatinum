#ifndef POKEPLATINUM_STRUCT_MAIN_MENU_02233674_SUB1_H
#define POKEPLATINUM_STRUCT_MAIN_MENU_02233674_SUB1_H

typedef struct {
    u32 version : 8;
    u32 subVersion : 4;
    u32 flags : 4;
    u32 packetId : 16;
} WirelessCommPacketHeader;

#endif // POKEPLATINUM_STRUCT_MAIN_MENU_02233674_SUB1_H
