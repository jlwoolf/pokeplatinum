#ifndef POKEPLATINUM_WIFI_PLAZA_LOBBY_0222DDF0_H
#define POKEPLATINUM_WIFI_PLAZA_LOBBY_0222DDF0_H

#include <ppwlobby/ppw_lobby.h>

#include "constants/pokemon.h"
#include "constants/string.h"

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222E294.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222E908.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230914.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231560.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0223177C_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02232068.h"
#include "wifi_lobby_questionnaire/struct_wifi_lobby_questionnaire_answer_tally.h"

#include "charcode.h"
#include "enums.h"
#include "savedata.h"
#include "trainer_info.h"

typedef struct WiFiPlazaProfile {
    s32 userId;
    u32 trainerID;
    charcode_t trainerName[TRAINER_NAME_LEN + 1];
    WiFiPlazaLobbyTime enterTime;
    WiFiPlazaLobbyTime localTime;
    u16 partySpecies[MAX_PARTY_SIZE];
    u8 partyForms[MAX_PARTY_SIZE];
    u8 partyIsEgg[MAX_PARTY_SIZE];
    u8 trainerGender;
    u8 language;
    u16 trainerAppearanceIdx;
    u16 country;
    u8 region;
    u8 isNationalDexObtained;
    u8 isMainStoryCleared;
    u8 appearanceRank;
    u8 gameVersion;
    u8 venue;
    s64 startTimestamp;
    u8 recentAppearances[12];
    s32 recentUserIDs[12];
    u16 pokemonTypes[2];
    WiFiPlazaLobbyQuestionnaireAnswer questionnaireAnswer;
} WiFiPlazaProfile;

WiFiPlazaLobbyState *WiFiPlazaLobby_State_Create(SaveData *saveData, enum HeapID heapID);
void WiFiPlazaLobby_State_Destroy(WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_Init(WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_UpdateNoop(WiFiPlazaLobbyState *param0);
int WiFiPlazaLobby_State_GetErrorFlag(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_CheckNetworkEvent(const WiFiPlazaLobbyState *param0);
WiFiPlazaLobbyNews *WiFiPlazaLobby_State_GetNewsManager(WiFiPlazaLobbyState *param0);
const WiFiPlazaLobbyPlaceList *WiFiPlazaLobby_State_GetPlayerCountryTable(WiFiPlazaLobbyState *param0);
const WiFiPlazaLobbyTime *WiFiPlazaLobby_State_GetCurrentTime(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_PopPlayerJoined(WiFiPlazaLobbyState *param0, u32 param1);
BOOL WiFiPlazaLobby_State_PopPlayerLeft(WiFiPlazaLobbyState *param0, u32 param1);
BOOL WiFiPlazaLobby_State_CheckTimeEventFlag(WiFiPlazaLobbyState *param0, int param1);
BOOL WiFiPlazaLobby_State_PopPlayerUpdated(WiFiPlazaLobbyState *param0, u32 param1);
SaveData *WiFiPlazaLobby_State_GetSaveData(WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsArceusRoom(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsQuestionAnswered(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsQuestionAcknowledged(const WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_MarkQuestionAcknowledged(WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsLobbyLocked(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsLobbyClosed(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsLobbyCloseFinished(const WiFiPlazaLobbyState *param0);
int WiFiPlazaLobby_State_GetFireworksState(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsParadeFinished(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsMinigameFinished(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsNeonTransitionComplete(const WiFiPlazaLobbyState *param0);
PPW_LOBBY_TIME_EVENT WiFiPlazaLobby_State_GetNeonATimeEvent(const WiFiPlazaLobbyState *param0);
PPW_LOBBY_TIME_EVENT WiFiPlazaLobby_State_GetNeonBTimeEvent(const WiFiPlazaLobbyState *param0);
PPW_LOBBY_TIME_EVENT WiFiPlazaLobby_State_GetNeonCTimeEvent(const WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_StartWarpTimer(WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsWarpTimerActive(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsTrainerInfoValid(const WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_SetTrainerInfoValid(WiFiPlazaLobbyState *param0, BOOL param1);
void WiFiPlazaLobby_State_ClearUserIDTable(WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_SetPlayerSlotUserID(WiFiPlazaLobbyState *param0, s32 param1, u32 param2);
void WiFiPlazaLobby_State_SetMyPlayerSlot(WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_GetUserIDTable(const WiFiPlazaLobbyState *param0, WiFiPlazaLobbyQuestionnaireData *param1);
void WiFiPlazaLobby_State_SetPlayerWarpPending(WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsPlayerWarpPending(const WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_SetBGMSuppressed(WiFiPlazaLobbyState *param0, BOOL param1);
void WiFiPlazaLobby_State_PlayLobbyBGM(const WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_SetBGMVolumeDucked(WiFiPlazaLobbyState *param0, BOOL param1);
u32 WiFiPlazaLobby_State_GetMySlotIndex(const WiFiPlazaLobbyState *param0);
s32 WiFiPlazaLobby_State_GetMyUserID(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsPlayerSlotOccupied(const WiFiPlazaLobbyState *param0, u32 param1);
const WiFiPlazaProfile *WiFiPlazaLobby_State_GetProfileBySlot(const WiFiPlazaLobbyState *param0, u32 param1);
WiFiPlazaProfile *WiFiPlazaLobby_State_GetOwnProfile(WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_SetCurrentVenue(WiFiPlazaLobbyState *param0, int param1);
void WiFiPlazaLobby_State_SetAttendee(WiFiPlazaLobbyState *param0, int param1, s32 param2);
void WiFiPlazaLobby_State_SetAppearanceRank(WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_SetPokemonTypes(WiFiPlazaLobbyState *param0, int type1, int type2);
void WiFiPlazaLobby_State_SetQuestionnaireAnswer(WiFiPlazaLobbyState *param0, u32 param1, u32 param2);
void WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(const WiFiPlazaProfile *profile, TrainerInfo *param1, enum HeapID heapID);
u32 WiFiPlazaLobby_State_GetVenueIndex(const WiFiPlazaProfile *profile);
int WiFiPlazaLobby_State_GetNthActiveSlot(const WiFiPlazaProfile *profile, u32 param1);
s32 WiFiPlazaLobby_State_GetNthActiveUserID(const WiFiPlazaProfile *profile, u32 param1);
s32 WiFiPlazaLobby_State_GetProfileUserId(const WiFiPlazaProfile *profile);
u32 WiFiPlazaProfile_GetTrainerID(const WiFiPlazaProfile *profile);
int WiFiPlazaLobby_State_GetTrainerAppearanceIndex(const WiFiPlazaProfile *profile);
WiFiPlazaLobbyTime WiFiPlazaLobby_State_GetProfileLocation(const WiFiPlazaProfile *profile);
u32 WiFiPlazaProfile_GetGender(const WiFiPlazaProfile *profile);
u32 WiFiPlazaProfile_GetNormalizedLanguage(const WiFiPlazaProfile *profile);
BOOL WiFiPlazaProfile_IsLanguageValid(const WiFiPlazaProfile *profile);
u32 WiFiPlazaProfile_GetLanguage(const WiFiPlazaProfile *profile);
u32 WiFiPlazaProfile_GetTrainerAppearanceGraphicsID(const WiFiPlazaProfile *profile);
u32 WiFiPlazaLobby_State_GetCountry(const WiFiPlazaProfile *profile);
u32 WiFiPlazaLobby_State_GetRegion(const WiFiPlazaProfile *profile);
u32 WiFiPlazaLobby_State_GetAppearanceRank(const WiFiPlazaProfile *profile);
BOOL WiFiPlazaLobby_State_IsAppearanceRankSet(const WiFiPlazaProfile *profile);
int WiFiPlazaLobby_State_GetProfilePokemonType(const WiFiPlazaProfile *profile, u32 param1);
void WiFiPlazaLobby_State_GetQuestionnaireAnswer(const WiFiPlazaProfile *profile, WiFiPlazaLobbyQuestionnaireAnswer *param1);
TrainerInfo *WiFiPlazaLobby_State_GetLocalTrainerInfo(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsMemberPresent(const WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_GetMemberPresentBitmap(const WiFiPlazaLobbyState *param0, WiFiPlazaLobbyNewsPlayerFlags *param1);
BOOL WiFiPlazaLobby_State_HasMemberPassword(const WiFiPlazaLobbyState *param0, u32 param1);
const WiFiPlazaLobbyPasswordWords *WiFiPlazaLobby_State_GetMemberPassword(const WiFiPlazaLobbyState *param0, u32 param1);
u32 WiFiPlazaLobby_State_GetSecondaryMemberCount(const WiFiPlazaLobbyState *param0);
u32 WiFiPlazaLobby_State_GetSecondaryMemberSlot(const WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_SendProfileViewMessage(WiFiPlazaLobbyState *param0, u32 param1, u32 param2);
void WiFiPlazaLobby_State_SendProfileViewMessageWithExtra(WiFiPlazaLobbyState *param0, u32 param1, u32 param2, u32 param3);
void WiFiPlazaLobby_State_SendMinigameProfileViewMessage(WiFiPlazaLobbyState *param0, enum PlazaMinigame param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, BOOL param7);
void WiFiPlazaLobby_State_SendMinigameResultMessage(WiFiPlazaLobbyState *param0, enum PlazaMinigame param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6);
u32 WiFiPlazaLobby_State_GetLobbySeason(const WiFiPlazaLobbyState *param0);
u32 WiFiPlazaLobby_State_GetLobbyRoomType(const WiFiPlazaLobbyState *param0);
u32 WiFiPlazaLobby_State_GetLobbyCloseTime(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsMemberCosmeticKnown(const WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_BroadcastCosmeticID(WiFiPlazaLobbyState *param0, u32 param1);
int WiFiPlazaLobby_State_GetFloatState(const WiFiPlazaLobbyState *param0, u32 param1);
u32 WiFiPlazaLobby_State_GetFloatTimer(const WiFiPlazaLobbyState *param0, u32 param1);
u32 WiFiPlazaLobby_State_GetFloatTimerMax(const WiFiPlazaLobbyState *param0);
u32 WiFiPlazaLobby_State_FindFloatSlotByUserID(const WiFiPlazaLobbyState *param0, u32 param1);
u32 WiFiPlazaLobby_State_AllocateFloatSlot(WiFiPlazaLobbyState *param0, u32 param1, int param2);
void WiFiPlazaLobby_State_FreeFloatSlot(WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_SetFloatSlotTrigger(WiFiPlazaLobbyState *param0, u32 param1);
BOOL WiFiPlazaLobby_State_IsFloatSlotTriggered(const WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_ClearFloatSlotTrigger(WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_FloatSlotToRowCol(u32 param0, u32 *param1, u32 *param2);
void WiFiPlazaLobby_State_SetFloatSlotPosition(WiFiPlazaLobbyState *param0, u32 param1, int param2);
int WiFiPlazaLobby_State_GetFloatSlotPosition(const WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_SendFloatJoinEvent(WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_SendFloatTriggerEvent(WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_ResetChat(WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_RequestChat(WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_UpdateChatRequest(WiFiPlazaLobbyState *param0, u16 param1);
void WiFiPlazaLobby_State_CompleteChat(WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_EndChat(WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsChatActive(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsChatRequested(const WiFiPlazaLobbyState *param0);
u32 WiFiPlazaLobby_State_GetChatPartner(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_HasChattedWithCurrentMember(const WiFiPlazaLobbyState *param0);
int WiFiPlazaLobby_State_GetChatState(const WiFiPlazaLobbyState *param0);
u16 WiFiPlazaLobby_State_GetChatResponse(const WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_CanChatWithMember(const WiFiPlazaLobbyState *param0, u32 param1);
BOOL WiFiPlazaLobby_State_IsChatFinished(const WiFiPlazaLobbyState *param0);
s16 WiFiPlazaLobby_State_GetChatTimer(const WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_SetChatPending(WiFiPlazaLobbyState *param0);
BOOL WiFiPlazaLobby_State_IsChatPending(const WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_ResetChatIfActive(WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_IncrementMemberChatCount(WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_MarkMemberChatted(WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_RecordChatJournal(WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_RecordTapToyJournal(WiFiPlazaLobbyState *param0, u32 param1);
void WiFiPlazaLobby_State_RecordMinigameJournal(WiFiPlazaLobbyState *param0, enum PlazaMinigame param1);
void WiFiPlazaLobby_State_RecordParadeJournal(WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_IncrementChatRecord(WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_IncrementMinigameRecord(WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_MarkActivityDone(WiFiPlazaLobbyState *param0, int param1);
int WiFiPlazaLobby_State_GetAvailableActivity(const WiFiPlazaLobbyState *param0);
u32 WiFiPlazaLobby_State_ChooseCosmeticID(const WiFiPlazaLobbyState *param0);
int WiFiPlazaLobby_State_GetFireworksEventStage(const WiFiPlazaLobbyState *param0);
u32 WiFiPlazaLobby_State_GetFireworksFrame(const WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_SetQuestionnaireResult(WiFiPlazaLobbyState *param0, const WiFiLobbyQuestionnaireAnswerTally *param1);
BOOL WiFiPlazaLobby_State_GetQuestionnaireResult(const WiFiPlazaLobbyState *param0, WiFiLobbyQuestionnaireAnswerTally *param1);
void WiFiPlazaLobby_State_CreateWFCTrainerInfo(WiFiPlazaLobbyState *param0);
void WiFiPlazaLobby_State_FreeWFCTrainerInfo(WiFiPlazaLobbyState *param0);

#endif // POKEPLATINUM_WIFI_PLAZA_LOBBY_0222DDF0_H
