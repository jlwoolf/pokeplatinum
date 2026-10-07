#ifndef POKEPLATINUM_UNION_ROOM_CHAT_H
#define POKEPLATINUM_UNION_ROOM_CHAT_H

#include "field/field_system_decl.h"
#include "union_room_chat/union_room_chat_decl.h"

UnionRoomChat *UnionRoomChat_New(FieldSystem *fieldSystem);
void UnionRoomChat_Free(UnionRoomChat *chat);

#endif // POKEPLATINUM_UNION_ROOM_CHAT_H
