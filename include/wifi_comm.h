#ifndef POKEPLATINUM_WIFI_COMM_H
#define POKEPLATINUM_WIFI_COMM_H

#include "wifi_menu_app/struct_wifi_menu_app_02236744_decl.h"

// Communication command interface for the wifi_menu_app WiFi apps. See
// wifi_comm.c for the command layout.

void WiFiComm_Init(WiFiCommApp *app);
void WiFiComm_InitNoContext(void);
int WiFiComm_SyncPacketSize(void);
int WiFiComm_PlayerStatusPacketSize(void);
int WiFiComm_VoiceChatPacketSize(void);
void WiFiComm_RecvPlayerStatus(int netId, int size, void *data, void *context);
void WiFiComm_RecvSyncRequest(int netId, int size, void *data, void *context);
void WiFiComm_RecvVoiceChat(int netId, int size, void *data, void *context);

#endif // POKEPLATINUM_WIFI_COMM_H
