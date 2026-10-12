#ifndef POKEPLATINUM_STRUCT_BATTLE_TOWER_H
#define POKEPLATINUM_STRUCT_BATTLE_TOWER_H

#include "constants/battle_tower.h"

#include "struct_defs/wifi_battle_tower_data.h"

#include "frontier_facilities/frontier_opponents.h"

#include "field_battle_data_transfer.h"
#include "location.h"

typedef struct BattleTower {
    int magic;
    enum HeapID heapID;
    u32 rngState;
    u8 nextOpponentNum;
    u8 opponentIndex;
    u8 partySize;
    u8 challengeMode;
    u8 defeatedSevenTrainers : 1;
    u8 beatPalmer : 2;
    u8 partnerReady : 1;
    u8 challengeCompleted : 1;
    u8 partnerID : 3;
    u8 playerGender;
    u8 partnerGender;
    u16 streak;
    u16 partnerSpecies[2];
    u16 statIndex;
    u16 roomNum;
    u32 victories;
    u16 counter2;
    u16 counter3;
    u16 counter1;
    u8 partyOrder[4];
    u16 partySpecies[4];
    u16 partyHeldItems[4];
    u16 trainerIDs[BT_OPPONENTS_COUNT * 2];
    Location unused_5C;
    WifiBattleTowerSave *wifiBattleTowerSave;
    WifiBattleTowerRecord *wifiBattleTowerRecord;
    FrontierOpponent opponentsDataDTO[2];
    FrontierOpponent partnersDataDTO[BT_PARTNERS_COUNT];
    BattleTowerPartnerData partnerData[BT_PARTNERS_COUNT];
    u8 partnerBuilt[BT_PARTNERS_COUNT];
    u16 trainerIdBuffer[35];
    u16 scratchBuffer[35];
    int wonBattle;
    FieldBattleDTO *dto;
    u8 msgsReceived;
    u8 commandType;
    u8 pendingFlag;
    u8 unused_8D7;
    u16 speciesOverlap;
    u16 destVarID;
} BattleTower;

#endif // POKEPLATINUM_STRUCT_BATTLE_TOWER_H
