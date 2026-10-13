#ifndef POKEPLATINUM_STRUCT_MAIN_MENU_02232254_H
#define POKEPLATINUM_STRUCT_MAIN_MENU_02232254_H

#include "main_menu/struct_wireless_comm_child.h"

typedef struct {
    WirelessCommChild children[8];
    u8 state;
    u8 ccaBusyRatio;
    u16 allowedChannels;
    u8 channel;
    u8 unk_65[3];
} WirelessCommChildList;

#endif // POKEPLATINUM_STRUCT_MAIN_MENU_02232254_H
