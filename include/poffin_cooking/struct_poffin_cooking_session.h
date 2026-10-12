#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_SESSION_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_SESSION_H

#include "poffin_cooking/struct_poffin_cooking_participant.h"
#include "poffin_cooking/struct_poffin_cooking_berry_packet.h"
#include "poffin_cooking/struct_poffin_cooking_berry_item.h"
#include "poffin_cooking/struct_poffin_cooking_result.h"

#include "poffin.h"
#include "trainer_info.h"

typedef struct {
    PoffinCookingBerryItem localBerry;
    PoffinCookingParticipant localParticipant;
    PoffinCookingResult result;
    PoffinCookingBerryPacket berryPacket;
    PoffinCookingResult receivedResult;
    PoffinCookingBerryPacket receivedBerryPacket;
    PoffinCookingParticipant participants[4];
    Poffin *poffin;
    u32 unused_104[4];
    PoffinCookingBerryItem peerBerries[4];
    u8 peerBerryReceived[4];
    u8 leaveFlags[4];
    u8 leaveFlagsReceived[4];
    u8 playerNetIDs[4];
    const TrainerInfo *trainerInfos[4];
    u8 localPlayerIndex;
    u8 leaveResult;
} PoffinCookingSession;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_SESSION_H
