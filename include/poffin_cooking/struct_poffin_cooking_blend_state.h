#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_BLEND_STATE_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_BLEND_STATE_H

typedef struct {
    u8 posX[4];
    u8 posY[4];
    u16 angle;
    u16 stirSpeed;
    u8 direction;
    u8 stirLevel;
    u8 releaseFlag;
    u8 sparkleTrigger;
    u8 alpha;
    u8 arrowSide;
    u8 stirChain;
    u8 perfectStir;
} PoffinCookingBlendState;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_BLEND_STATE_H
