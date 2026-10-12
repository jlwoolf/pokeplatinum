#ifndef POKEPLATINUM_STRUCT_MIX_RECORDS_APP_ARGS_H
#define POKEPLATINUM_STRUCT_MIX_RECORDS_APP_ARGS_H

#include "struct_decls/struct_0205C22C_decl.h"

#include "game_options.h"
#include "game_records.h"
#include "journal.h"
#include "savedata.h"

typedef struct {
    SaveData *saveData;
    UnionRoomTrainers *unk_04;
    Options *options;
    GameRecords *records;
    JournalEntry *journalEntry;
} MixRecordsAppArgs;

#endif // POKEPLATINUM_STRUCT_MIX_RECORDS_APP_ARGS_H
