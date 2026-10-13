#ifndef POKEPLATINUM_STRUCT_MAIN_MENU_0223222C_H
#define POKEPLATINUM_STRUCT_MAIN_MENU_0223222C_H

#include <nitro/wm.h>

#include "main_menu/struct_wireless_comm_transfer.h"
#include "main_menu/struct_wireless_comm_game_info.h"
#include "main_menu/struct_wireless_comm_connect_data.h"
#include "main_menu/union_wireless_comm_connection.h"

typedef struct {
    u8 state;
    u8 commRole;
    u8 linkType;
    u8 packetPort;
    u32 ggid;
    int unk_08;
    u16 aid;
    u16 unk_0E;
    BOOL indCallbackSet;
    BOOL connected;
    BOOL disconnected;
    BOOL resetDone;
    BOOL stopped;
    WMscanParam *scanParam;
    WMbssDesc *scanResult;
    u32 parentSendSize;
    u32 childSendSize;
    void *systemBuffer;
    void *parentSendBuffer;
    void *childSendBuffer;
    WirelessCommGameInfo gameInfo;
    WirelessCommConnectData connectData;
    WirelessCommConnection connection;
    WirelessCommTransfer transfer;
} WirelessCommManager;

#endif // POKEPLATINUM_STRUCT_MAIN_MENU_0223222C_H
