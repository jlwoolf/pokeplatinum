#ifndef POKEPLATINUM_STRUCT_MAIN_MENU_02232620_H
#define POKEPLATINUM_STRUCT_MAIN_MENU_02232620_H

#include "main_menu/struct_wireless_comm_parent.h"

typedef struct {
    WirelessCommParent unk_00[8];
    u16 unk_1C0;
    u8 unk_1C2;
    u8 unk_1C3_0 : 4;
    u8 unk_1C3_4 : 4;
} WirelessCommParentList;

#endif // POKEPLATINUM_STRUCT_MAIN_MENU_02232620_H
