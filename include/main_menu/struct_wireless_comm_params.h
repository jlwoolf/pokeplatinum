#ifndef POKEPLATINUM_STRUCT_MAIN_MENU_02232E38_H
#define POKEPLATINUM_STRUCT_MAIN_MENU_02232E38_H

typedef struct {
    u32 version : 8;
    u32 subVersion : 4;
    u32 language : 4;
    u32 gameCode : 16;
    const u16 *trainerId;
    const u16 *trainerName;
} WirelessCommParams;

#endif // POKEPLATINUM_STRUCT_MAIN_MENU_02232E38_H
