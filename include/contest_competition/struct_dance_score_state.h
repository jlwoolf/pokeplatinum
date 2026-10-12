#ifndef POKEPLATINUM_STRUCT_DANCE_SCORE_STATE_H
#define POKEPLATINUM_STRUCT_DANCE_SCORE_STATE_H

typedef struct {
    u8 unk_00[CONTEST_NUM_PARTICIPANTS];
    u8 unk_04;
    u8 unk_05[CONTEST_NUM_PARTICIPANTS];
    s16 unk_0A[4];
    u32 unk_14;
    u32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u16 unk_2C;
    u8 unk_2E;
    u8 unk_2F;
} DanceScoreState;

#endif // POKEPLATINUM_STRUCT_DANCE_SCORE_STATE_H
