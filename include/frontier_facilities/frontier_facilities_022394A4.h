#ifndef POKEPLATINUM_FRONTIER_FACILITIES_022394A4_H
#define POKEPLATINUM_FRONTIER_FACILITIES_022394A4_H

#include "struct_defs/battle_tower.h"

#include "savedata.h"

void BattleTower_CreateOpponentParties(BattleTower *battleTower, SaveData *saveData);
u16 BattleTower_GetObjectIDFromOpponentIDInFrontierScript(BattleTower *battleTower, u16 opponentID);
void BattleTower_SetBeatPalmer(BattleTower *battleTower, u16 value);
u16 FrontierFacilities_IncrementWinStreak(BattleTower *battleTower);
u16 FrontierFacilities_GetTotalStreak(BattleTower *battleTower);

#endif // POKEPLATINUM_FRONTIER_FACILITIES_022394A4_H
