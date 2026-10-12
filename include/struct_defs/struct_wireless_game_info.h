#ifndef POKEPLATINUM_STRUCT_WIRELESS_GAME_INFO_H
#define POKEPLATINUM_STRUCT_WIRELESS_GAME_INFO_H

#include "easy_chat_sentence.h"

typedef struct {
    u32 trainerId;
    u8 commType;
    u8 contestRegulation;
    u8 connectedCount;
    u8 unused_07;
    EasyChatSentence easyChatSentence;
    u8 trainerInfo[32];
    u8 battleRegulation[32];
    u32 padding_50;
    u8 pauseConnection;
    u8 padding_55[3];
} WirelessGameInfo;

#endif // POKEPLATINUM_STRUCT_WIRELESS_GAME_INFO_H
