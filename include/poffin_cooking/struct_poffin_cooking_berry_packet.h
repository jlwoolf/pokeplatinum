#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_BERRY_PACKET_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_BERRY_PACKET_H

#include "poffin_cooking/struct_poffin_cooking_berry_item.h"
#include "poffin_cooking/struct_poffin_cooking_blend_state.h"

typedef struct {
    PoffinCookingBerryItem berries[4];
    PoffinCookingBlendState blendState;
} PoffinCookingBerryPacket;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_BERRY_PACKET_H
