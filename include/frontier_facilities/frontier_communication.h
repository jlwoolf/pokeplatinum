#ifndef POKEPLATINUM_FRONTIER_COMMUNICATION_H
#define POKEPLATINUM_FRONTIER_COMMUNICATION_H

#include "frontier_facilities/battle_arcade.h"
#include "frontier_facilities/battle_castle.h"
#include "frontier_facilities/battle_factory.h"
#include "frontier_facilities/battle_hall.h"

#define FRONTIER_COMMUNICATION_UNREACHABLE2     34
#define HALL_COMMUNICATION_SEND_TRAINERS        35
#define HALL_COMMUNICATION_SEND_OPPONENT_MONS   36
#define HALL_COMMUNICATION_SEND_PLAYERS_POKEMON 38

#define FACTORY_COMMUNICATION_SEND_TRAINERS 23

#define CASTLE_COMMUNICATION_SEND_PLAYERS_CP    42
#define CASTLE_COMMUNICATION_SEND_TRAINERS      43
#define CASTLE_COMMUNICATION_SEND_OPPONENT_MONS 45
#define FRONTIER_COMMUNICATION_UNREACHABLE4     47
#define CASTLE_COMMUNICATION_SEND_PLAYERS_PARTY 48

#define ARCADE_COMMUNICATION_SEND_TRAINERS      66
#define ARCADE_COMMUNICATION_SEND_PLAYERS_PARTY 70

void FrontierCommunication_Unreachable1(int dummy1, int unused1, void *dummy2, void *battleHall);
BOOL FrontierCommunication_Unreachable2(BattleHall *battleHall);
void FrontierCommunication_Unreachable3(int dummy1, int unused1, void *dummy2, void *battleHall);
BOOL HallCommunication_SendTrainers(BattleHall *battleHall);
void HallCommunication_ReceiveTrainers(int netID, int unused, void *trainerIDs, void *battleHall);
BOOL HallCommunication_SendOpponentMons(BattleHall *battleHall);
void HallCommunication_ReceiveOpponentMons(int netID, int unused, void *monIndices, void *battleHall);
BOOL FrontierFacilities_SendBattleHallData(BattleHall *battleHall, u8 param1);
void FrontierFacilities_ReceiveBattleHallData(int netID, int unused, void *param2, void *battleHall);
BOOL HallCommunication_SendPlayersPokemon(BattleHall *battleHall);
void HallCommunication_ReceivePartnersPokemon(int netID, int unused1, void *partnersMon, void *battleHall);
u8 *HallCommunication_VerifyPacketSize(int index, void *battleHall, int size);
BOOL FrontierFacilities_SendFactoryProgress(BattleFactory *battleFactory);
void FrontierFacilities_ReceiveFactoryProgress(int netID, int unused1, void *param2, void *battleFactory);
BOOL FactoryCommunication_SendTrainers(BattleFactory *battleFactory);
void FactoryCommunication_ReceiveTrainers(int netID, int unused, void *trainerIDs, void *battleFactory);
BOOL FrontierFacilities_SendFactoryRentals(BattleFactory *battleFactory);
void FrontierFacilities_ReceiveFactoryRentals(int netID, int unused1, void *param2, void *battleFactory);
BOOL FrontierFacilities_SendFactoryOpponentMons(BattleFactory *battleFactory);
void FrontierFacilities_ReceiveFactoryOpponentMons(int netID, int unused, void *param2, void *battleFactory);
BOOL FrontierFacilities_SendFactoryRetireDecision(BattleFactory *battleFactory, u8 param1);
void FrontierFacilities_ReceiveFactoryRetireDecision(int netID, int unused, void *param2, void *battleFactory);
BOOL FrontierFacilities_SendFactoryTradeDecision(BattleFactory *battleFactory, u8 param1);
void FrontierFacilities_ReceiveFactoryTradeDecision(int netID, int unused, void *param2, void *battleFactory);
BOOL FrontierFacilities_SendFactoryPlayerMons(BattleFactory *battleFactory);
void FrontierFacilities_ReceiveFactoryPartnerMons(int netID, int unused1, void *param2, void *battleFactory);
BOOL CastleCommunication_SendPlayersCP(BattleCastle *battleCastle);
void CastleCommunication_ReceivePartnersCP(int netID, int unused1, void *partnersCP, void *battleCastle);
BOOL CastleCommunication_SendTrainers(BattleCastle *battleCastle);
void CastleCommunications_ReceiveTrainers(int netID, int unused, void *trainerIDs, void *battleCastle);
BOOL FrontierFacilities_SendCastleAppSelection(BattleCastle *battleCastle);
void FrontierFacilities_ReceiveCastleAppSelection(int netID, int unused, void *param2, void *battleCastle);
BOOL CastleCommunication_SendOpponentMons(BattleCastle *battleCastle);
void FrontierFacilities_ReceiveCastleOpponentMons(int netID, int unused, void *monData, void *battleCastle);
BOOL FrontierFacilities_SendCastleRetireDecision(BattleCastle *battleCastle, u16 param1);
void FrontierFacilities_ReceiveCastleRetireDecision(int netID, int unused, void *param2, void *battleCastle);
BOOL FrontierCommunication_Unreachable4(BattleCastle *battleCastle, u16 param1);
void FrontierCommunication_Unreachable5(int netID, int unused, void *param2, void *battleCastle);
BOOL CastleCommunication_SendPlayersParty(BattleCastle *battleCastle);
void CastleCommunication_ReceivePartnersParty(int netID, int unused, void *param2, void *battleCastle);
u8 *CastleCommunication_VerifyPacketSize(int index, void *battleCastle, int size);
BOOL FrontierFacilities_SendArcadeProgress(BattleArcade *battleArcade);
void FrontierFacilities_ReceiveArcadeProgress(int netID, int unused1, void *param2, void *battleArcade);
BOOL ArcadeCommunication_SendTrainers(BattleArcade *battleArcade);
void ArcadeCommunication_ReceiveTrainers(int netID, int unused, void *trainerIDs, void *battleArcade);
BOOL FrontierFacilities_SendArcadeOpponentMons(BattleArcade *battleArcade);
void FrontierFacilities_ReceiveArcadeOpponentMons(int netID, int unused, void *param2, void *battleArcade);
BOOL FrontierFacilities_SendArcadeRetireDecision(BattleArcade *battleArcade, u16 param1);
void FrontierFacilities_ReceiveArcadeRetireDecision(int netID, int unused, void *param2, void *battleArcade);
BOOL FrontierFacilities_SendArcadeUnusedValue(BattleArcade *battleArcade, u16 param1);
void FrontierFacilities_ReceiveArcadeUnusedValue(int netID, int unused, void *param2, void *battleArcade);
BOOL ArcadeCommunication_SendPlayersParty(BattleArcade *battleArcade);
void ArcadeCommunication_ReceivePartnersParty(int netID, int unused, void *partnersParty, void *battleArcade);
u8 *ArcadeCommunication_VerifyPacketSize(int netID, void *battleArcade, int size);

#endif // POKEPLATINUM_FRONTIER_COMMUNICATION_H
