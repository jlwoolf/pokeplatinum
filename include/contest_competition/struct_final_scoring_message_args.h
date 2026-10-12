#ifndef POKEPLATINUM_STRUCT_FINAL_SCORING_MESSAGE_ARGS_H
#define POKEPLATINUM_STRUCT_FINAL_SCORING_MESSAGE_ARGS_H

typedef struct {
    u8 contestantID;
    u8 moveSlot;
    u16 unused_02;
    u8 contestantEntryNum;
    u8 unused_05;
} FinalScoringMessageArgs;

#endif // POKEPLATINUM_STRUCT_FINAL_SCORING_MESSAGE_ARGS_H
