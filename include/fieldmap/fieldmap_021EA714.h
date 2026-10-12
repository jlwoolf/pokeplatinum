#ifndef POKEPLATINUM_FIELDMAP_021EA714_H
#define POKEPLATINUM_FIELDMAP_021EA714_H

#include "applications/poketch/poketch_system.h"
#include "field/field_system_decl.h"

void FieldSystem_SendPoketchEvent(FieldSystem *fieldSystem, enum PoketchEventID eventID, u32 dummy);
void FieldMap_021EA728(FieldSystem *fieldSystem);
void FieldMap_021EA790(FieldSystem *fieldSystem);
u8 FieldMap_021EA7CC(FieldSystem *fieldSystem);
void FieldMap_021EA830(FieldSystem *fieldSystem);
void FieldMap_021EA848(FieldSystem *fieldSystem);
BOOL FieldMap_021EA854(FieldSystem *fieldSystem);

#endif // POKEPLATINUM_FIELDMAP_021EA714_H
