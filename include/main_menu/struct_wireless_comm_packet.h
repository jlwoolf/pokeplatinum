#ifndef POKEPLATINUM_STRUCT_MAIN_MENU_02233674_H
#define POKEPLATINUM_STRUCT_MAIN_MENU_02233674_H

#include "main_menu/struct_wireless_comm_packet_header.h"
#include "main_menu/struct_wireless_comm_packet_config.h"
#include "main_menu/struct_wireless_comm_packet_meta.h"
#include "main_menu/struct_wireless_comm_packet_tail.h"

typedef struct {
    WirelessCommPacketHeader unk_00;
    WirelessCommPacketConfig unk_04;
    WirelessCommPacketMeta unk_08;
    WirelessCommPacketTail unk_0C;
} WirelessCommPacket;

#endif // POKEPLATINUM_STRUCT_MAIN_MENU_02233674_H
