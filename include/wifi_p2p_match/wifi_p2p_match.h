#ifndef POKEPLATINUM_WIFI_P2P_MATCH_H
#define POKEPLATINUM_WIFI_P2P_MATCH_H

#include "overlay_manager.h"

int WifiP2PMatch_InitConnect(ApplicationManager *appMan, int *param1);
int WifiP2PMatch_MainConnect(ApplicationManager *appMan, int *param1);
int WifiP2PMatch_ExitConnect(ApplicationManager *appMan, int *param1);
int WifiP2PMatch_InitDisconnect(ApplicationManager *appMan, int *param1);
int WifiP2PMatch_MainDisconnect(ApplicationManager *appMan, int *param1);
int WifiP2PMatch_ExitDisconnect(ApplicationManager *appMan, int *param1);

#endif // POKEPLATINUM_WIFI_P2P_MATCH_H
