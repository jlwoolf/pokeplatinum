#ifndef POKEPLATINUM_STRUCT_UNION_ROOM_DRAWING_STATUS_H
#define POKEPLATINUM_STRUCT_UNION_ROOM_DRAWING_STATUS_H

// One player's pen/cursor status, exchanged over the wireless link. The
// coordinate arrays hold the first and last touch samples of the current
// stroke; the bitfields select the pen colour and brush size.
typedef struct {
    u8 x[4];
    u8 y[4];
    u8 penColor : 3;
    u8 pointCount : 3;
    u8 brushSize : 2;
    u8 state;
} UnionRoomDrawingStatus;

#endif // POKEPLATINUM_STRUCT_UNION_ROOM_DRAWING_STATUS_H
