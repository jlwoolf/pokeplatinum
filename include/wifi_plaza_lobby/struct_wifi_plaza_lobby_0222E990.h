#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_0222E990_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_0222E990_H

typedef struct {
    s32 userIDs[4];
    u8 count;
    u8 kind;
    u8 rank;
    u8 minigame : 7;
    u8 isRanked : 1;
} WiFiPlazaLobbyProfileViewMessage;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_0222E990_H
