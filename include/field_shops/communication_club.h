#ifndef POKEPLATINUM_COMMUNICATION_CLUB_H
#define POKEPLATINUM_COMMUNICATION_CLUB_H

#include "field/field_system_decl.h"

void CommClub_StartBattleClient(FieldSystem *fieldSystem, int param1, int param2, int param3);
void CommClub_PrintChooseJoinMsg(void);
u32 CommClub_CheckWindowOpenClient(void);
void CommClub_StartBattleServer(FieldSystem *fieldSystem, int param1, int param2, int param3);
void CommClub_StartServerRoom(void);
u32 CommClub_CheckWindowOpenServer(void);
BOOL CommClub_HasCommError(void);

#endif // POKEPLATINUM_COMMUNICATION_CLUB_H
