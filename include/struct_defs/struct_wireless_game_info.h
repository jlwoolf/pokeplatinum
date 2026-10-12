#ifndef POKEPLATINUM_STRUCT_WIRELESS_GAME_INFO_H
#define POKEPLATINUM_STRUCT_WIRELESS_GAME_INFO_H

#include "easy_chat_sentence.h"

typedef struct {
    u32 unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    EasyChatSentence unk_08;
    u8 unk_10[32];
    u8 unk_30[32];
    u32 padding_50;
    u8 unk_54;
    u8 padding_55[3];
} WirelessGameInfo;

#endif // POKEPLATINUM_STRUCT_WIRELESS_GAME_INFO_H
