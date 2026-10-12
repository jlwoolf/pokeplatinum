#ifndef POKEPLATINUM_STRUCT_MAIN_MENU_0223222C_H
#define POKEPLATINUM_STRUCT_MAIN_MENU_0223222C_H

#include <nitro/wm.h>

#include "main_menu/struct_wireless_comm_transfer.h"
#include "main_menu/struct_wireless_comm_game_info.h"
#include "main_menu/struct_wireless_comm_connect_data.h"
#include "main_menu/union_wireless_comm_connection.h"

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u32 unk_04;
    int unk_08;
    u16 unk_0C;
    u16 unk_0E;
    BOOL unk_10;
    BOOL unk_14;
    BOOL unk_18;
    BOOL unk_1C;
    BOOL unk_20;
    WMscanParam *unk_24;
    WMbssDesc *unk_28;
    u32 unk_2C;
    u32 unk_30;
    void *unk_34;
    void *unk_38;
    void *unk_3C;
    WirelessCommGameInfo unk_40;
    WirelessCommConnectData unk_78;
    WirelessCommConnection unk_90;
    WirelessCommTransfer unk_254;
} WirelessCommManager;

#endif // POKEPLATINUM_STRUCT_MAIN_MENU_0223222C_H
