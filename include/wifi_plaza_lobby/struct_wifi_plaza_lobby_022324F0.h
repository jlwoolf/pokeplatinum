#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_022324F0_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_022324F0_H

#include <ppwlobby/ppw_lobby.h>

typedef void (*WiFiPlazaLobbyNetworkPlayerConnectedCallback)(s32, const void *, void *, BOOL);
typedef void (*WiFiPlazaLobbyNetworkPlayerDisconnectedCallback)(s32, void *);
typedef void (*WiFiPlazaLobbyNetworkPlayerProfileCallback)(s32, const void *, void *);
typedef void (*WiFiPlazaLobbyNetworkTimeEventCallback)(PPW_LOBBY_TIME_EVENT, void *);
typedef void (*WiFiPlazaLobbyNetworkStatsCallback)(const void *, u32, void *);

typedef struct {
    WiFiPlazaLobbyNetworkPlayerConnectedCallback onPlayerConnected;
    WiFiPlazaLobbyNetworkPlayerDisconnectedCallback onPlayerDisconnected;
    WiFiPlazaLobbyNetworkPlayerProfileCallback onPlayerProfile;
    WiFiPlazaLobbyNetworkTimeEventCallback onTimeEvent;
    WiFiPlazaLobbyNetworkStatsCallback onStats;
} WiFiPlazaLobbyNetworkCallbacks;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_022324F0_H
