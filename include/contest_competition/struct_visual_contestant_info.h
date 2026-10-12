#ifndef POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_INFO_H
#define POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_INFO_H

#include "contest_competition/struct_visual_message_args.h"

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    VisualMessageArgs unk_03;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    s8 unk_0A;
    s8 unk_0B;
    s8 unk_0C;
    u16 unk_0E;
    u16 unk_10;
} VisualContestantInfo;

#endif // POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_INFO_H
