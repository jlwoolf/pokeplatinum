#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02231428_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02231428_H

typedef struct {
    union {
        u32 value;
        struct {
            u8 hour;
            u8 minute;
            u8 second;
            u8 reserved;
        };
    };
} WiFiPlazaLobbyTime;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02231428_H
