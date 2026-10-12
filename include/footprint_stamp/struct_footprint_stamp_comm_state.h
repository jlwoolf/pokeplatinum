#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_COMM_STATE_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_COMM_STATE_H

typedef struct {
    BOOL isActive; // Whether Wi-Fi communication is currently active.
    s32 localUserId; // DWC user ID of the local player.
} FootprintStampCommState;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_COMM_STATE_H
