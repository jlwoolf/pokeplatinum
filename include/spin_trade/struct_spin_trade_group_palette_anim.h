#ifndef POKEPLATINUM_STRUCT_SPIN_TRADE_GROUP_PALETTE_ANIM_H
#define POKEPLATINUM_STRUCT_SPIN_TRADE_GROUP_PALETTE_ANIM_H

#include <nnsys.h>

typedef struct {
    int active;
    int frameIndex;
    int timer;
    void *unk_0C;
    NNSG2dPaletteData *paletteData;
} SpinTradeGroupPaletteAnim;

#endif // POKEPLATINUM_STRUCT_SPIN_TRADE_GROUP_PALETTE_ANIM_H
