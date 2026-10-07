#ifndef POKEPLATINUM_GLOBAL_TERMINAL_0222AE60_H
#define POKEPLATINUM_GLOBAL_TERMINAL_0222AE60_H

#include "struct_decls/struct_02030A80_decl.h"
#include "struct_defs/dress_up_photo.h"

#include "global_terminal/struct_global_terminal_0222AE80.h"
#include "global_terminal/struct_global_terminal_0222AFC0.h"
#include "global_terminal/struct_global_terminal_0222AFCC.h"
#include "overlay062/struct_ov62_02239DA4.h"

#include "pc_boxes.h"
#include "savedata.h"

void GlobalTerminal_SerializeDressUpPhoto(SaveData *saveData, const DressUpPhoto *photo, GlobalTerminalDressUpPhoto *param2);
void GlobalTerminal_DeserializeDressUpPhoto(const GlobalTerminalDressUpPhoto *param0, DressUpPhoto *photo);
void GlobalTerminal_SerializePCBox(SaveData *saveData, const PCBoxes *pcBoxes, int boxID, UnkStruct_ov62_02239DA4 *param3, enum HeapID heapID);
void GlobalTerminal_UpdatePCBoxChecksum(SaveData *saveData, UnkStruct_ov62_02239DA4 *param1, int param2);
void GlobalTerminal_SerializePlayerProfile(SaveData *saveData, const PlayerProfile *param1, GlobalTerminalPlayerProfile *param2);
void GlobalTerminal_DeserializePlayerProfile(const GlobalTerminalPlayerProfile *param0, PlayerProfile *param1);
void GlobalTerminal_SerializeProfileSummary(SaveData *saveData, const PlayerProfile *param1, GlobalTerminalProfileSummary *param2);

#endif // POKEPLATINUM_GLOBAL_TERMINAL_0222AE60_H
