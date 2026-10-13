#ifndef POKEPLATINUM_STRUCT_MAIN_MENU_02232254_SUB1_H
#define POKEPLATINUM_STRUCT_MAIN_MENU_02232254_SUB1_H

#include "main_menu/struct_wireless_comm_bssid_high.h"
#include "main_menu/struct_wireless_comm_bssid_low.h"

typedef struct {
    WirelessCommBssidHigh bssidHigh;
    WirelessCommBssidLow bssidLow;
    u16 aid;
    u8 dataRequested;
    u8 pendingRequests;
    u8 isConnected;
    u8 unk_0B;
} WirelessCommChild;

#endif // POKEPLATINUM_STRUCT_MAIN_MENU_02232254_SUB1_H
