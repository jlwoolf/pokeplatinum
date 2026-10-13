#ifndef POKEPLATINUM_STRUCT_MAIN_MENU_02232620_H
#define POKEPLATINUM_STRUCT_MAIN_MENU_02232620_H

#include "main_menu/struct_wireless_comm_parent.h"

typedef struct {
    WirelessCommParent parents[8];
    u16 timer;
    u8 foundCount;
    u8 selectedParentIndex : 4;
    u8 scanState : 4;
} WirelessCommParentList;

#endif // POKEPLATINUM_STRUCT_MAIN_MENU_02232620_H
