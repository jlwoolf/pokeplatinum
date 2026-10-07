#ifndef POKEPLATINUM_STRUCT_UNION_ROOM_DRAWING_PREV_POINT_H
#define POKEPLATINUM_STRUCT_UNION_ROOM_DRAWING_PREV_POINT_H

// The last point of a player's previous stroke, kept so the next frame can
// connect the two strokes with a line.
typedef struct {
    u8 x;
    u8 y;
    u16 hasPrev;
} UnionRoomDrawingPrevPoint;

#endif // POKEPLATINUM_STRUCT_UNION_ROOM_DRAWING_PREV_POINT_H
