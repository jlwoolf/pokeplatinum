#ifndef POKEPLATINUM_MIX_RECORDS_EXCHANGE_H
#define POKEPLATINUM_MIX_RECORDS_EXCHANGE_H

#include "mix_records/struct_mix_records_record.h"

#include "savedata.h"

void MixRecords_SerializeLocalRecord(SaveData *saveData, MixRecordsRecord *param1);
void MixRecords_ApplyReceivedRecords(SaveData *saveData, const MixRecordsRecord *param1);

#endif // POKEPLATINUM_MIX_RECORDS_EXCHANGE_H
