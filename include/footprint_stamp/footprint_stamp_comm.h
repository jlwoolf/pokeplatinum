#ifndef POKEPLATINUM_FOOTPRINT_STAMP_COMM_H
#define POKEPLATINUM_FOOTPRINT_STAMP_COMM_H

#include "footprint_stamp/struct_footprint_stamp_app_decl.h"
#include "footprint_stamp/struct_footprint_stamp_entry.h"

void FootprintStampComm_Init(FootprintStampApp *param0);
BOOL FootprintStampComm_SendEntry(const FootprintStampEntry *param0);

#endif // POKEPLATINUM_FOOTPRINT_STAMP_COMM_H
