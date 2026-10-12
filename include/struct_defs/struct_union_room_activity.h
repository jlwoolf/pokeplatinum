#ifndef POKEPLATINUM_STRUCT_UNION_ROOM_ACTIVITY_H
#define POKEPLATINUM_STRUCT_UNION_ROOM_ACTIVITY_H

typedef struct {
    u32 trainerIds[4];
    u8 unused_10[4];
    u8 unused_14[4];
    u8 appearance[4];
    u8 activityType;
    u8 padding_1D[3];
} UnionRoomActivity;

#endif // POKEPLATINUM_STRUCT_UNION_ROOM_ACTIVITY_H
