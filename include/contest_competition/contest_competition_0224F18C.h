#ifndef POKEPLATINUM_CONTEST_COMPETITION_0224F18C_H
#define POKEPLATINUM_CONTEST_COMPETITION_0224F18C_H

#include "contest_competition/struct_contest_packet_queue_config.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_contest_packet_queue.h"

void contest_competition_0224F18C(ContestPacketQueue *param0, const ContestPacketQueueConfig *param1);
int contest_competition_0224F1F8(ContestPacketQueue *param0, u8 param1, u16 param2, void *param3, int param4);
void contest_competition_0224F26C(ContestPacketQueue *param0, const ContestPacketHeader *param1, void *param2, int param3);
int contest_competition_0224F30C(ContestPacketQueue *param0, void *param1, int param2, void *param3);
BOOL contest_competition_0224F35C(ContestPacketQueue *param0);
BOOL contest_competition_0224F3D0(ContestPacketQueue *param0);
int contest_competition_0224F3D8(ContestPacketQueue *param0, void *param1);
BOOL contest_competition_0224F4B8(ContestPacketQueue *param0, int connectionCount, int playerContestantID, int param3);

#endif // POKEPLATINUM_CONTEST_COMPETITION_0224F18C_H
