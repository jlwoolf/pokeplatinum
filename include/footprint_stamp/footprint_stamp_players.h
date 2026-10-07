#ifndef POKEPLATINUM_FOOTPRINT_STAMP_PLAYERS_H
#define POKEPLATINUM_FOOTPRINT_STAMP_PLAYERS_H

#include "overlay066/struct_ov66_0222DFF8_decl.h"
#include "footprint_stamp/struct_footprint_stamp_entry.h"

#include "bg_window.h"
#include "message.h"
#include "string_template.h"

void FootprintStampPlayers_DrawName(MessageLoader *param0, StringTemplate *param1, Window param2[], UnkStruct_ov66_0222DFF8 *param3, s32 param4);
void FootprintStampPlayers_ClearName(Window param0[], u32 param1);
u16 FootprintStampPlayers_GetStampColor(int param0, u32 param1);
int FootprintStampPlayers_CheckTouch(FootprintStampEntry *param0, int param1);
BOOL PokemonHasOverworldFootprint(int param0, int param1, BOOL param2);
int PokemonOverworldFootprintSize(int param0, int param1);

#endif // POKEPLATINUM_FOOTPRINT_STAMP_PLAYERS_H
