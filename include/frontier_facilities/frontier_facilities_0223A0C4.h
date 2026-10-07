#ifndef POKEPLATINUM_FRONTIER_FACILITIES_0223A0C4_H
#define POKEPLATINUM_FRONTIER_FACILITIES_0223A0C4_H

#include "struct_defs/battle_tower.h"
#include "struct_defs/wifi_battle_tower_data.h"

#include "frontier_facilities/frontier_opponents.h"
#include "frontier_facilities/struct_frontier_facilities_02230BE4.h"

#include "field_battle_data_transfer.h"
#include "savedata.h"

BOOL BattleTower_CreateTrainerParty(BattleTower *battleTower, FrontierOpponent *opponentDataDTO, u16 battleTowerTrainerID, int partySize, u16 *species, u16 *items, BattleTowerPartnerData *param6, enum HeapID heapID);
void BattleTower_CreateWiFiTrainerParty(SaveData *saveData, FrontierOpponent *dto, const u8 opponentID);
FieldBattleDTO *FieldBattleDTO_NewBattleTower(BattleTower *battleTower, FieldFrontierDTO *fieldData);
void FrontierFacilities_SetPartnerReady(BattleTower *battleTower, u16 param1);
u16 FrontierFacilities_IsPartnerDataReady(BattleTower *battleTower, const u16 *param1);
int BattleTower_GetTrainerMessagesBankID(u8 challengeMode);

#endif // POKEPLATINUM_FRONTIER_FACILITIES_0223A0C4_H
