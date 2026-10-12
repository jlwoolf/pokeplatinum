#ifndef POKEPLATINUM_UNION_MAIN_MENU_022334FC_H
#define POKEPLATINUM_UNION_MAIN_MENU_022334FC_H

#include "main_menu/struct_wireless_comm_child_list.h"
#include "main_menu/struct_wireless_comm_parent_list.h"

typedef union {
    WirelessCommChildList val1;
    WirelessCommParentList val2;
} WirelessCommConnection;

#endif // POKEPLATINUM_UNION_MAIN_MENU_022334FC_H
