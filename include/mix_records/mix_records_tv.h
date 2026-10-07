#ifndef POKEPLATINUM_MIX_RECORDS_TV_H
#define POKEPLATINUM_MIX_RECORDS_TV_H

#include "struct_decls/tv_broadcast.h"
#include "struct_defs/tv.h"

#include "savedata.h"

u32 MixRecords_GetInterviewEpisodesSize(const SaveData *saveData);
u32 MixRecords_GetTrainerSightingEpisodesSize(const SaveData *saveData);
u32 MixRecords_GetRecordEpisodesSize(const SaveData *saveData);
TVWifiEpisode *MixRecords_CreateInterviewEpisodes(SaveData *saveData, enum HeapID heapID, u32 param2);
TVWifiEpisode *MixRecords_CreateTrainerSightingEpisodes(SaveData *saveData, enum HeapID heapID, u32 param2);
TVWifiEpisode *MixRecords_CreateRecordEpisodes(SaveData *saveData, enum HeapID heapID, u32 param2);
TVWifiEpisode *MixRecords_CreateInterviewEpisodesUnfiltered(SaveData *saveData, enum HeapID heapID, u32 param2);
TVWifiEpisode *MixRecords_CreateTrainerSightingEpisodesUnfiltered(SaveData *saveData, enum HeapID heapID, u32 param2);
TVWifiEpisode *MixRecords_CreateRecordEpisodesUnfiltered(SaveData *saveData, enum HeapID heapID, u32 param2);
void MixRecords_MergeTrainerSightingEpisodes(TVBroadcast *broadcast, int param1, int param2, const void **param3, const void **param4);
void MixRecords_MergeRecordEpisodes(TVBroadcast *broadcast, int param1, int param2, const void **param3, const void **param4);
void MixRecords_MergeInterviewEpisodes(TVBroadcast *broadcast, int param1, int param2, const void **param3, const void **param4);

#endif // POKEPLATINUM_MIX_RECORDS_TV_H
