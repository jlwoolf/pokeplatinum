#ifndef POKEPLATINUM_STRUCT_MIX_RECORDS_RECORD_H
#define POKEPLATINUM_STRUCT_MIX_RECORDS_RECORD_H

typedef struct {
    u8 data[3000];
    u32 checksum;
    u32 seed;
} MixRecordsRecord;

#endif // POKEPLATINUM_STRUCT_MIX_RECORDS_RECORD_H
