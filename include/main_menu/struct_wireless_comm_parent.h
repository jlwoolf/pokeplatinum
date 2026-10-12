#ifndef POKEPLATINUM_STRUCT_MAIN_MENU_02232620_SUB1_H
#define POKEPLATINUM_STRUCT_MAIN_MENU_02232620_SUB1_H

#include "main_menu/struct_wireless_comm_game_info_string.h"
#include "main_menu/struct_wireless_comm_bssid_high.h"
#include "main_menu/struct_wireless_comm_bssid_low.h"

typedef struct {
    WirelessCommBssidHigh unk_00;
    WirelessCommGameInfoString unk_04;
    WirelessCommGameInfoString unk_1C;
    WirelessCommBssidLow unk_34;
    u8 unk_36;
    u8 unk_37;
} WirelessCommParent;

#endif // POKEPLATINUM_STRUCT_MAIN_MENU_02232620_SUB1_H
