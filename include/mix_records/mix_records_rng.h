#ifndef POKEPLATINUM_MIX_RECORDS_RNG_H
#define POKEPLATINUM_MIX_RECORDS_RNG_H

#include "record_mixed_rng.h"

u32 MixRecords_GetRecordMixedRngSize(RecordMixedRNG *param0);
void *MixRecords_GetRecordMixedRngBuffer(RecordMixedRNG *param0);
void MixRecords_MergeMixedRecords(int param0, int param1, RecordMixedRNG *param2, const void **param3);

#endif // POKEPLATINUM_MIX_RECORDS_RNG_H
