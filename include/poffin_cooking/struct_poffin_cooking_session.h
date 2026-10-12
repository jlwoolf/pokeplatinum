#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_SESSION_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_SESSION_H

#include "poffin_cooking/struct_poffin_cooking_participant.h"
#include "poffin_cooking/struct_poffin_cooking_berry_packet.h"
#include "poffin_cooking/struct_poffin_cooking_berry_item.h"
#include "poffin_cooking/struct_poffin_cooking_result.h"

#include "poffin.h"
#include "trainer_info.h"

typedef struct {
    PoffinCookingBerryItem unk_00;
    PoffinCookingParticipant unk_04;
    PoffinCookingResult unk_20;
    PoffinCookingBerryPacket unk_34;
    PoffinCookingResult unk_58;
    PoffinCookingBerryPacket unk_6C;
    PoffinCookingParticipant unk_90[4];
    Poffin *unk_100;
    u32 unk_104[4];
    PoffinCookingBerryItem unk_114[4];
    u8 unk_124[4];
    u8 unk_128[4];
    u8 unk_12C[4];
    u8 unk_130[4];
    const TrainerInfo *unk_134[4];
    u8 unk_144;
    u8 unk_145;
} PoffinCookingSession;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_SESSION_H
