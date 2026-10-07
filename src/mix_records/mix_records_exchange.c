#include "mix_records/mix_records_exchange.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/tv_broadcast.h"
#include "struct_defs/dress_up_photo.h"
#include "struct_defs/image_clips.h"
#include "struct_defs/wifi_player_profile.h"

#include "mix_records/mix_records_rng.h"
#include "mix_records/mix_records_tv.h"
#include "mix_records/struct_mix_records_record.h"
#include "savedata/save_table.h"

#include "communication_information.h"
#include "communication_system.h"
#include "heap.h"
#include "rankings.h"
#include "record_mixed_rng.h"
#include "savedata.h"
#include "image_clips.h"
#include "tv_broadcast.h"
#include "wifi_battle_tower_save.h"
#include "wifi_player_profile.h"

typedef struct {
    enum HeapID heapID;
    SaveData *saveData;
    int playerCount;
    int netId;
    const void **records;
    const void **prevRecords;
} MixRecordsDataContext;

typedef u32 (*MixRecordsDataSizeFunc)(SaveData *);
typedef void *(*MixRecordsDataGetFunc)(SaveData *, enum HeapID heapID, u32);
typedef void (*MixRecordsDataSetFunc)(const MixRecordsDataContext *);

typedef struct {
    MixRecordsDataSizeFunc sizeFunc;
    MixRecordsDataGetFunc getFunc;
    MixRecordsDataSetFunc setFunc;
} MixRecordsDataHandler;

static u32 MixRecords_GetMixedRngDataSize(SaveData *saveData)
{
    RecordMixedRNG *v0 = SaveData_GetRecordMixedRNG(saveData);
    return MixRecords_GetRecordMixedRngSize(v0);
}

static void *MixRecords_CopyMixedRngData(SaveData *saveData, enum HeapID heapID, u32 param2)
{
    RecordMixedRNG *v0 = SaveData_GetRecordMixedRNG(saveData);
    void *v1 = Heap_AllocAtEnd(heapID, param2);

    MI_CpuCopyFast(MixRecords_GetRecordMixedRngBuffer(v0), v1, param2);

    return v1;
}

static void MixRecords_MergeMixedRngData(const MixRecordsDataContext *param0)
{
    RecordMixedRNG *v0 = SaveData_GetRecordMixedRNG(param0->saveData);
    MixRecords_MergeMixedRecords(param0->playerCount, param0->netId, v0, param0->records);
}

static u32 MixRecords_GetDressUpPhotoSize(SaveData *saveData)
{
    ImageClips *imageClips = SaveData_GetImageClips(saveData);
    return DressUpPhoto_Size();
}

static void *MixRecords_CopyDressUpPhoto(SaveData *saveData, enum HeapID heapID, u32 param2)
{
    DressUpPhoto *photo;
    ImageClips *imageClips = SaveData_GetImageClips(saveData);
    void *v2 = Heap_AllocAtEnd(heapID, param2);

    photo = ImageClips_GetDressUpPhoto(imageClips, 0);
    MI_CpuCopyFast(photo, v2, param2);

    return v2;
}

static void MixRecords_AddDressUpPhotos(const MixRecordsDataContext *param0)
{
    ImageClips *imageClips = SaveData_GetImageClips(param0->saveData);
    ImageClips_AddUniquePhotos(param0->playerCount, param0->netId, imageClips, param0->records);
}

static void MixRecords_ApplyTrainerSightingEpisodes(const MixRecordsDataContext *param0)
{
    TVBroadcast *broadcast = SaveData_GetTVBroadcast(param0->saveData);
    MixRecords_MergeTrainerSightingEpisodes(broadcast, param0->playerCount, param0->netId, param0->records, param0->prevRecords);
}

static void MixRecords_ApplyRecordEpisodes(const MixRecordsDataContext *param0)
{
    TVBroadcast *broadcast = SaveData_GetTVBroadcast(param0->saveData);
    MixRecords_MergeRecordEpisodes(broadcast, param0->playerCount, param0->netId, param0->records, param0->prevRecords);
}

static void MixRecords_ApplyInterviewEpisodes(const MixRecordsDataContext *param0)
{
    TVBroadcast *broadcast = SaveData_GetTVBroadcast(param0->saveData);
    MixRecords_MergeInterviewEpisodes(broadcast, param0->playerCount, param0->netId, param0->records, param0->prevRecords);
}

static void *MixRecords_GetRankingEntries(SaveData *saveData, enum HeapID heapID, u32 param2)
{
    return SaveData_GetRankingEntries(saveData, heapID);
}

static void MixRecords_UpdateRankings(const MixRecordsDataContext *param0)
{
    Rankings *v0 = SaveData_GetRankings(param0->saveData);

    SaveData_UpdateRankings(param0->saveData, param0->netId, param0->playerCount, param0->records, param0->heapID);
}

static void *MixRecords_BuildWifiPlayerProfile(SaveData *saveData, enum HeapID heapID, u32 param2)
{
    WifiPlayerProfile *profile = Heap_AllocAtEnd(heapID, param2);
    MI_CpuClear8(profile, param2);
    WifiPlayerProfile_Build(saveData, 0, profile);

    return profile;
}

static void MixRecords_NoOpProfile(const MixRecordsDataContext *param0)
{
    return;
}

static const MixRecordsDataHandler sRecordDataHandlers[] = {
    { MixRecords_GetMixedRngDataSize, MixRecords_CopyMixedRngData, MixRecords_MergeMixedRngData },
    { MixRecords_GetDressUpPhotoSize, MixRecords_CopyDressUpPhoto, MixRecords_AddDressUpPhotos },
    { (MixRecordsDataSizeFunc)MixRecords_GetTrainerSightingEpisodesSize, (MixRecordsDataGetFunc)MixRecords_CreateTrainerSightingEpisodes, NULL },
    { (MixRecordsDataSizeFunc)MixRecords_GetRecordEpisodesSize, (MixRecordsDataGetFunc)MixRecords_CreateRecordEpisodes, NULL },
    { (MixRecordsDataSizeFunc)MixRecords_GetInterviewEpisodesSize, (MixRecordsDataGetFunc)MixRecords_CreateInterviewEpisodes, NULL },
    { (MixRecordsDataSizeFunc)RankingsEntries_Size, (MixRecordsDataGetFunc)MixRecords_GetRankingEntries, MixRecords_UpdateRankings },
    { (MixRecordsDataSizeFunc)WifiPlayerProfile_Size, (MixRecordsDataGetFunc)MixRecords_BuildWifiPlayerProfile, MixRecords_NoOpProfile },
    { (MixRecordsDataSizeFunc)MixRecords_GetTrainerSightingEpisodesSize, (MixRecordsDataGetFunc)MixRecords_CreateTrainerSightingEpisodesUnfiltered, MixRecords_ApplyTrainerSightingEpisodes },
    { (MixRecordsDataSizeFunc)MixRecords_GetRecordEpisodesSize, (MixRecordsDataGetFunc)MixRecords_CreateRecordEpisodesUnfiltered, MixRecords_ApplyRecordEpisodes },
    { (MixRecordsDataSizeFunc)MixRecords_GetInterviewEpisodesSize, (MixRecordsDataGetFunc)MixRecords_CreateInterviewEpisodesUnfiltered, MixRecords_ApplyInterviewEpisodes }
};

void MixRecords_SerializeLocalRecord(SaveData *saveData, MixRecordsRecord *param1)
{
    u32 v0;
    void *v1;
    int v2, v3;
    u32 v4 = 3000;
    u8 *v5 = param1->data;
    const MixRecordsDataHandler *v6 = sRecordDataHandlers;

    v3 = NELEMS(sRecordDataHandlers);

    for (v2 = 0; v2 < v3; v2++) {
        v0 = v6[v2].sizeFunc(saveData);
        v1 = v6[v2].getFunc(saveData, HEAP_ID_51, v0);

        GF_ASSERT(v4 > v0);

        MI_CpuCopyFast(v1, v5, v0);
        Heap_Free(v1);

        v5 += v0;
        v4 -= v0;
    }
}

void MixRecords_ApplyReceivedRecords(SaveData *saveData, const MixRecordsRecord *param1)
{
    MixRecordsDataContext v0;
    u32 v1;
    u32 v2 = 0;
    u32 v3 = 3000;
    int i, v5, v6;
    const void *v7[5];
    const void *v8[5];
    u32 v9[4 - 2 + 1];

    v0.heapID = HEAP_ID_51;
    v0.saveData = saveData;
    v0.netId = CommSys_CurNetId();
    v0.playerCount = 5;
    v0.records = v7;
    v0.prevRecords = v8;

    v9[2 - 2] = 0;
    v9[3 - 2] = 0;
    v9[4 - 2] = 0;

    for (i = 0; i < 2; i++) {
        v9[2 - 2] += sRecordDataHandlers[i].sizeFunc(saveData);
    }

    for (i = 0; i < 3; i++) {
        v9[3 - 2] += sRecordDataHandlers[i].sizeFunc(saveData);
    }

    for (i = 0; i < 4; i++) {
        v9[4 - 2] += sRecordDataHandlers[i].sizeFunc(saveData);
    }

    for (i = 0; i < NELEMS(sRecordDataHandlers); i++) {
        v1 = sRecordDataHandlers[i].sizeFunc(saveData);
        GF_ASSERT(v3 > v1);

        for (v5 = 0; v5 < 5; v5++) {
            if (CommInfo_TrainerInfo(v5) != NULL) {
                v0.records[v5] = &(param1[v5].data[v2]);
            } else {
                v0.records[v5] = NULL;
            }
        }

        switch (i) {
        case 7:
        case 8:
        case 9:
            for (v6 = 0; v6 < 5; v6++) {
                if (CommInfo_TrainerInfo(v6) != NULL) {
                    v0.prevRecords[v6] = &(param1[v6].data[v9[i - 7]]);
                } else {
                    v0.prevRecords[v6] = NULL;
                }
            }
            break;
        }

        if (sRecordDataHandlers[i].setFunc != NULL) {
            sRecordDataHandlers[i].setFunc(&v0);
        }

        v2 += v1;
        v3 -= v1;
    }

    TVBroadcast *broadcast = SaveData_GetTVBroadcast(saveData);
    TVBroadcast_ClearSegmentInstances(broadcast);
    TVBroadcast_ClearWatchProgress(broadcast);
}
