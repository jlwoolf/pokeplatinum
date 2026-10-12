#ifndef POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_INFO_H
#define POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_INFO_H

#include "contest_competition/struct_visual_message_args.h"

typedef struct {
    u8 contestantID;
    u8 visualRank;
    u8 danceRank;
    VisualMessageArgs messageArgs;
    u8 state;
    u8 messageArg1;
    u8 messageArg2;
    s8 x;
    s8 y;
    s8 z;
    u16 timer;
    u16 score;
} VisualContestantInfo;

#endif // POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_INFO_H
