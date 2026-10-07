#ifndef POKEPLATINUM_STRUCT_SPIN_TRADE_GROUP_TRAINER_ID_H
#define POKEPLATINUM_STRUCT_SPIN_TRADE_GROUP_TRAINER_ID_H

typedef union {
    u64 val1;
    struct {
        u32 unk_00;
        u32 unk_04;
    } val2;
} SpinTradeGroupTrainerId;

#endif // POKEPLATINUM_STRUCT_SPIN_TRADE_GROUP_TRAINER_ID_H
