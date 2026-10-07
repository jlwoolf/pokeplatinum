#ifndef POKEPLATINUM_GLOBAL_TERMINAL_0222BC4C_H
#define POKEPLATINUM_GLOBAL_TERMINAL_0222BC4C_H

#include "global_terminal/global_terminal_0222B008.h"
#include "global_terminal/struct_global_terminal_0222B960.h"
#include "global_terminal/struct_global_terminal_0222BC90.h"
#include "global_terminal/struct_global_terminal_0222BCF8_sub1_sub1.h"
#include "global_terminal/struct_global_terminal_0222BDAC.h"
#include "global_terminal/struct_global_terminal_0222BDAC_1.h"
#include "global_terminal/struct_global_terminal_0222BE20.h"
#include "global_terminal/struct_global_terminal_0222BED8.h"
#include "overlay062/struct_ov62_0223DF10.h"

int GlobalTerminalGds_HandleProfilePhoto(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1);
int GlobalTerminalGds_HandleProfile(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1);
int GlobalTerminalGds_GetProfilePhotoList(UnkStruct_ov62_022349A8 *param0, GlobalTerminalProfilePhoto **param1, int param2);
int GlobalTerminalGds_HandleProfileBox(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1);
int GlobalTerminalGds_HandleBox(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1);
int GlobalTerminalGds_GetBoxList(UnkStruct_ov62_022349A8 *param0, GlobalTerminalProfileBox **param1, int param2);
int GlobalTerminalGds_HandlePlayTime(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1);
void GlobalTerminalGds_GetPlayTime(UnkStruct_ov62_022349A8 *param0, UnkStruct_ov62_0223DF10 **param1);
int GlobalTerminalGds_HandlePlayTimeProfile(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1);
void GlobalTerminalGds_GetPlayTimeProfile(UnkStruct_ov62_022349A8 *param0, GlobalTerminalPlayTimeData **param1, GlobalTerminalPlayTimeDataAlt **param2);
int GlobalTerminalGds_HandleBattleRecording(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1);
u64 GlobalTerminalGds_GetBattleRecording(UnkStruct_ov62_022349A8 *param0);
int GlobalTerminalGds_HandleRecord(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1);
int GlobalTerminalGds_GetRecordList(UnkStruct_ov62_022349A8 *param0, GlobalTerminalRecord **param1, int param2);
int GlobalTerminalGds_HandleRecordAlt(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1);
int GlobalTerminalGds_GetRecordAlt(UnkStruct_ov62_022349A8 *param0, GlobalTerminalRecordAlt **param1);
int GlobalTerminalGds_HandleRecordAlt2(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1);

#endif // POKEPLATINUM_GLOBAL_TERMINAL_0222BC4C_H
