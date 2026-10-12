#ifndef POKEPLATINUM_STRUCT_MAIN_MENU_02232254_SUB1_H
#define POKEPLATINUM_STRUCT_MAIN_MENU_02232254_SUB1_H

#include "main_menu/struct_wireless_comm_bssid_high.h"
#include "main_menu/struct_wireless_comm_bssid_low.h"

typedef struct {
    WirelessCommBssidHigh unk_00;
    WirelessCommBssidLow unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} WirelessCommChild;

#endif // POKEPLATINUM_STRUCT_MAIN_MENU_02232254_SUB1_H
