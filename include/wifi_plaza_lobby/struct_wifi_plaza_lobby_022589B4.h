#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_022589B4_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_022589B4_H

typedef void (*WiFiPlazaLobbyNetworkBinaryMessageCallback)(s32, const void *, u32, void *);

typedef struct {
    WiFiPlazaLobbyNetworkBinaryMessageCallback callback;
    u32 size;
} WiFiPlazaLobbyNetworkMessageHandler;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_022589B4_H
