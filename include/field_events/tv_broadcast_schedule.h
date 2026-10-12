#ifndef POKEPLATINUM_TV_BROADCAST_SCHEDULE_H
#define POKEPLATINUM_TV_BROADCAST_SCHEDULE_H

#include "field/field_system_decl.h"

#include "string_template.h"

void FieldSystem_SetTVProgramFinished(FieldSystem *fieldSystem);
int TVBroadcast_GetPendingBroadcastType(FieldSystem *fieldSystem);
int TVBroadcast_PickPendingSegment(FieldSystem *fieldSystem, BOOL param1, BOOL param2);
int TVBroadcast_GetNextSegmentID(FieldSystem *fieldSystem);
int TVBroadcast_GetProgramFramingMessage(FieldSystem *fieldSystem, int framingMessageType);
BOOL TVBroadcast_LoadSegmentMessage(FieldSystem *fieldSystem, StringTemplate *template, int segmentID, u16 *bankDestVar, u16 *messageDestVar);

#endif // POKEPLATINUM_TV_BROADCAST_SCHEDULE_H
