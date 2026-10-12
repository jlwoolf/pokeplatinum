#ifndef POKEPLATINUM_STRUCT_UNION_ROOM_DRAWING_APP_ARGS_H
#define POKEPLATINUM_STRUCT_UNION_ROOM_DRAWING_APP_ARGS_H

#include "struct_decls/struct_0205C22C_decl.h"

#include "game_options.h"
#include "journal.h"

typedef struct {
    UnionRoomTrainers *trainers;
    JournalEntry *journalEntry;
    Options *options;
} UnionRoomDrawingAppArgs;

#endif // POKEPLATINUM_STRUCT_UNION_ROOM_DRAWING_APP_ARGS_H
