#include "mix_records/mix_records_rng.h"

#include <nitro.h>
#include <string.h>

#include "record_mixed_rng.h"

static void MixRecords_RemoveMixedRecord(RecordMixedRNG *param0, int param1);
static void MixRecords_InsertMixedRecord(RecordMixedRNG *param0, const RecordMixedRNG *param1);

u32 MixRecords_GetRecordMixedRngSize(RecordMixedRNG *param0)
{
    return sizeof(RecordMixedRNG);
}

void *MixRecords_GetRecordMixedRngBuffer(RecordMixedRNG *param0)
{
    return &param0[1];
}

static void MixRecords_InsertMixedRecord(RecordMixedRNG *param0, const RecordMixedRNG *param1)
{
    int v0;

    for (v0 = 5; v0 > 2; v0--) {
        param0[v0] = param0[v0 - 1];
    }

    param0[2] = *param1;
}

static void MixRecords_RemoveMixedRecord(RecordMixedRNG *param0, int param1)
{
    int v0;
    RecordMixedRNG *v1;

    GF_ASSERT(2 <= param1 && param1 <= 5);

    for (v0 = param1 + 1; v0 <= 5; v0++) {
        param0[v0 - 1] = param0[v0];
    }

    v1 = &param0[5];

    v1->groupName[0] = 0xffff;
    v1->playerName[0] = 0xffff;
}

void MixRecords_MergeMixedRecords(int param0, int param1, RecordMixedRNG *param2, const void **param3)
{
    int v0, v1;
    RecordMixedRNG *v2;

    for (v0 = 0; v0 < param0; v0++) {
        v2 = (RecordMixedRNG *)param3[v0];

        if (v0 == param1) {
            continue;
        }

        if (v2 == NULL) {
            continue;
        }

        if (RecordMixedRNG_IsEntryEmpty(v2) == 1) {
            continue;
        }

        if (RecordMixedRNG_AreEntriesEqual(v2, &param2[0])) {
            continue;
        }

        for (v1 = 0; v1 < 4; v1++) {
            if (RecordMixedRNG_AreEntriesEqual(v2, &param2[2 + v1])) {
                MixRecords_RemoveMixedRecord(param2, 2 + v1);
            }
        }

        MixRecords_InsertMixedRecord(param2, v2);
    }
}
