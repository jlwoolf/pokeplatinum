#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_02248408_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_02248408_H

#include "struct_defs/battle_recording.h"

#include "field_battle_data_transfer.h"
#include "savedata.h"

void VsRecorderViewerRecording_SanitizeNames(BattleRecording *param0, FieldBattleDTO *param1, enum HeapID heapID);
int VsRecorderViewerRecording_SaveStep(SaveData *saveData, int param1, u8 param2, u16 *param3, u16 *param4);
void VsRecorderViewerRecording_EncodeData(SaveData *saveData);
int VsRecorderViewerRecording_SaveWithIdStep(SaveData *saveData, u64 param1, u16 *param2, u16 *param3);
int VsRecorderViewerRecording_FinalizeAndSave(SaveData *saveData, int param1);

#endif // POKEPLATINUM_VS_RECORDER_VIEWER_02248408_H
