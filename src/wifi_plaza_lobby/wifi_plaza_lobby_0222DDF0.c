#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"

#include <dwc.h>
#include <nitro.h>
#include <ppwlobby/ppw_lobby.h>
#include <string.h>

#include "constants/charcode.h"
#include "constants/versions.h"
#include "generated/game_records.h"
#include "generated/genders.h"
#include "generated/journal_online_events.h"
#include "generated/species.h"

#include "struct_decls/struct_0207E060_decl.h"
#include "struct_defs/wi_fi_history.h"

#include "wifi_plaza_lobby/wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_0223177C.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_022324F0.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_02234EA8.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222E294.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222E908.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222E990.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230914.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231560.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0223177C_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0223185C.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_022318AC.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231908.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0223199C.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_022319FC.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231A58.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231AB4.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231B24.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231B80.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02232068.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_022324F0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02232B20.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_022589B4.h"
#include "wifi_lobby_questionnaire/struct_wifi_lobby_questionnaire_answer_tally.h"

#include "appearance.h"
#include "charcode.h"
#include "enums.h"
#include "font.h"
#include "game_records.h"
#include "heap.h"
#include "journal.h"
#include "math_util.h"
#include "message.h"
#include "object_events_gfx.h"
#include "party.h"
#include "password_word_bank.h"
#include "pokedex.h"
#include "pokemon.h"
#include "save_player.h"
#include "savedata.h"
#include "sound.h"
#include "sound_playback.h"
#include "string_gf.h"
#include "system_data.h"
#include "trainer_info.h"
#include "wfc_trainer_info.h"
#include "wifi_history_save_data.h"
#include "wifi_plaza_question_data.h"

#include "res/text/bank/unk_0673.h"

typedef struct {
    u16 unk_00[8];
    u16 unk_10[8];
    WiFiPlazaProfile profile;
    u32 unk_B4;
} WiFiPlazaLobbyProfileCache;

typedef struct {
    u8 unk_00[8];
} WiFiPlazaLobbyStateTempBuffer;

typedef struct {
    BOOL unk_00;
    s32 unk_04;
    s32 unk_08[9];
    u32 unk_2C[9];
    u32 unk_50[9][3];
    u32 unk_BC[9][3];
    BOOL unk_128[9][3];
} WiFiPlazaLobbyMinigameGrid;

typedef struct {
    BOOL unk_00;
    s64 unk_04;
    s32 unk_0C;
    s32 unk_10;
    u32 unk_14;
    u32 unk_18;
} WiFiPlazaLobbyEventTimer;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
} WiFiPlazaLobbyEventFlags;

typedef struct {
    u8 unk_00_0 : 1;
    u8 unk_00_1 : 1;
    u8 unk_00_2 : 2;
    u8 unk_00_4 : 1;
    u8 unk_00_5 : 2;
    u8 unk_00_7 : 1;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F_0 : 4;
    u8 unk_0F_4 : 4;
} WiFiPlazaLobbyEventTimers;

typedef struct {
    WiFiPlazaLobbyNews *unk_00;
    BOOL unk_04;
    WiFiPlazaLobbyPlaceList unk_08;
    WiFiPlazaLobbyTime unk_D0;
    s64 unk_D4;
    s64 unk_DC;
    TrainerInfo *trainerInfos[4];
} WiFiPlazaLobbyStatePlayers;

typedef struct {
    u16 unk_00;
    u16 unk_02;
} WiFiPlazaLobbyInteractionData;

typedef struct {
    u32 unk_00;
    u16 unk_04;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u8 unk_0A;
    u8 unk_0B;
    u8 unk_0C[20];
    WiFiPlazaLobbyInteractionData unk_20;
    u16 unk_24;
    s16 unk_26;
} WiFiPlazaLobbyInteractionState;

typedef struct {
    u8 unk_00[20];
} WiFiPlazaLobbyPlayerFlags;

typedef struct {
    s16 unk_00;
    u8 unk_02;
} WiFiPlazaLobbyTimer;

typedef struct {
    u8 unk_00[9];
    u8 unk_09[3];
    u8 unk_0C[20];
} WiFiPlazaLobbyMinigameWeights;

typedef struct {
    u8 unk_00[20];
    WiFiPlazaLobbyPasswordWords unk_14[20];
    PasswordWordBank *unk_B4;
} WiFiPlazaLobbyPasswordState;

typedef union {
    u32 val1;
    u8 val2[4];
} WiFiPlazaLobbyPasswordSeed;

typedef struct {
    s32 unk_00[13];
    u8 unk_34[13];
    u8 unk_41;
    u8 unk_42;
    u8 unk_43;
    const SaveData *saveData;
    u16 unk_48;
    u16 unk_4A;
} WiFiPlazaLobbyRecentPlayers;

typedef struct {
    TrainerInfo *trainerInfo;
    BOOL unk_04;
} WiFiPlazaLobbyTrainerInfoHolder;

typedef struct {
    WiFiLobbyQuestionnaireAnswerTally unk_00;
    BOOL unk_14;
} WiFiPlazaLobbyStateQuestionnaire;

typedef struct WiFiPlazaLobbyState_t {
    SaveData *saveData;
    WiFiPlazaLobbyStatePlayers unk_04;
    WiFiPlazaLobbyEventFlags unk_F8;
    WiFiPlazaLobbyProfileCache unk_108;
    WiFiPlazaLobbyInteractionState unk_1C0;
    WiFiPlazaLobbyPlayerFlags unk_1E8;
    WiFiPlazaLobbyEventTimers unk_1FC;
    WiFiPlazaLobbyMinigameGrid unk_20C;
    WiFiPlazaLobbyTimer unk_3A0;
    WiFiPlazaLobbyStateTempBuffer unk_3A3;
    WiFiPlazaLobbyMinigameWeights unk_3AB;
    WiFiPlazaLobbyNewsPlayerFlags unk_3CB;
    WiFiPlazaLobbyQuestionnaireData unk_3DF;
    WiFiPlazaLobbyPasswordState unk_3E4;
    WiFiPlazaLobbyEventTimer unk_49C;
    WFCTrainerInfo *unk_4B8;
    WiFiPlazaLobbyRecentPlayers unk_4BC;
    WiFiPlazaLobbyTrainerInfoHolder unk_508;
    WiFiPlazaLobbyStateQuestionnaire unk_510;
    enum HeapID heapID;
    u32 unk_52C;
} WiFiPlazaLobbyState;

typedef struct WiFiPlazaTrainerAppearance {
    u16 graphicsID;
    u16 gender;
} WiFiPlazaTrainerAppearance;

typedef struct {
    u16 unk_00;
    u16 unk_02;
} WiFiPlazaLobbyEventTimerStage;

static BOOL WiFiPlazaLobby_State_IsTrainerNameTerminated(const charcode_t *trainerName, u32 length);
static void WiFiPlazaLobby_State_HandleMemberJoined(s32 param0, const void *param1, void *param2, BOOL param3);
static void WiFiPlazaLobby_State_HandleMemberLeft(s32 param0, void *param1);
static void WiFiPlazaLobby_State_HandleMemberUpdated(s32 param0, const void *param1, void *param2);
static void WiFiPlazaLobby_State_HandleLobbyTimeEvent(PPW_LOBBY_TIME_EVENT param0, void *param1);
static void WiFiPlazaLobby_State_HandleMemberProfileReceived(const void *param0, u32 param1, void *param2);
static void WiFiPlazaLobby_State_BuildMemberLocationList(WiFiPlazaLobbyProfileCache *param0, WiFiPlazaLobbyPlaceList *param1);
static void WiFiPlazaLobby_State_CheckEventTimeout(WiFiPlazaLobbyState *param0);
static void WiFiPlazaLobby_State_BuildLocalProfile(WiFiPlazaLobbyProfileCache *param0, SaveData *saveData, enum HeapID heapID);
static void WiFiPlazaLobby_State_LoadCachedProfile(WiFiPlazaLobbyState *param0);
static void WiFiPlazaLobby_State_UpdateProfileChecksum(WiFiPlazaLobbyProfileCache *param0, const SaveData *saveData);
static BOOL WiFiPlazaLobby_State_ValidateProfileChecksum(const WiFiPlazaLobbyProfileCache *param0, const SaveData *saveData);
static void WiFiPlazaLobby_State_CopyProfile(WiFiPlazaLobbyProfileCache *param0, const WiFiPlazaProfile *param1, u32 param2);
static void WiFiPlazaLobby_State_ResetEventFlags(WiFiPlazaLobbyEventFlags *param0);
static void WiFiPlazaLobby_State_UpdateEventTimers(WiFiPlazaLobbyEventTimers *param0, WiFiPlazaLobbyEventFlags *param1, WiFiPlazaLobbyMinigameGrid *param2, WiFiPlazaLobbyEventTimer *param3);
static void WiFiPlazaLobby_State_InitEventState(WiFiPlazaLobbyEventTimers *param0);
static void WiFiPlazaLobby_State_UpdateMusicVolume(const WiFiPlazaLobbyEventTimers *param0);
static void WiFiPlazaLobby_State_ResetTimer(WiFiPlazaLobbyTimer *param0);
static BOOL WiFiPlazaLobby_State_IsTimerActive(const WiFiPlazaLobbyTimer *param0);
static void WiFiPlazaLobby_State_TickTimer(WiFiPlazaLobbyTimer *param0);
static void WiFiPlazaLobby_State_CreateTrainerInfo(WiFiPlazaLobbyTrainerInfoHolder *param0, enum HeapID heapID);
static void WiFiPlazaLobby_State_FreeTrainerInfo(WiFiPlazaLobbyTrainerInfoHolder *param0);
static void WiFiPlazaLobby_State_InitTrainerInfoFromProfile(WiFiPlazaLobbyTrainerInfoHolder *param0, const WiFiPlazaLobbyProfileCache *param1, enum HeapID heapID);
static void WiFiPlazaLobby_State_SetTimerExpired(WiFiPlazaLobbyTimer *param0);
static BOOL WiFiPlazaLobby_State_IsTimerExpired(const WiFiPlazaLobbyTimer *param0);
static void WiFiPlazaLobby_State_ClearPlayerFlags(WiFiPlazaLobbyPlayerFlags *param0);
static void WiFiPlazaLobby_State_ResetInteractionState(WiFiPlazaLobbyInteractionState *param0);
static void WiFiPlazaLobby_State_ResetInteraction(WiFiPlazaLobbyInteractionState *param0);
static void WiFiPlazaLobby_State_AbortInteraction(WiFiPlazaLobbyInteractionState *param0);
static BOOL WiFiPlazaLobby_State_IsPlayerFlagSet(const WiFiPlazaLobbyInteractionState *param0, u32 param1);
static void WiFiPlazaLobby_State_SetPlayerFlag(WiFiPlazaLobbyInteractionState *param0, u32 param1);
static void WiFiPlazaLobby_State_ClearPlayerFlag(WiFiPlazaLobbyInteractionState *param0, u32 param1);
static void WiFiPlazaLobby_State_IncrementPlayerCounter(WiFiPlazaLobbyInteractionState *param0, u32 param1);
static void WiFiPlazaLobby_State_ResetPlayerCounter(WiFiPlazaLobbyInteractionState *param0, u32 param1);
static void WiFiPlazaLobby_State_SetInteractionData(WiFiPlazaLobbyInteractionState *param0, u16 param1);
static void WiFiPlazaLobby_State_SendInteractionResult(WiFiPlazaLobbyState *param0, s32 param1, BOOL param2);
static void WiFiPlazaLobby_State_SendInteractionCancel(WiFiPlazaLobbyState *param0, s32 param1);
static void WiFiPlazaLobby_State_StartInteractionTimer(WiFiPlazaLobbyInteractionState *param0);
static void WiFiPlazaLobby_State_StopInteractionTimer(WiFiPlazaLobbyInteractionState *param0);
static void WiFiPlazaLobby_State_UpdateInteractionTimer(WiFiPlazaLobbyInteractionState *param0);
static BOOL WiFiPlazaLobby_State_CheckInteractionTimeout(const WiFiPlazaLobbyInteractionState *param0);
static s16 WiFiPlazaLobby_State_GetInteractionTimer(const WiFiPlazaLobbyInteractionState *param0);
static void WiFiPlazaLobby_State_HandleTwoTrainerReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1);
static void WiFiPlazaLobby_State_HandleTwoTrainerExtraReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1);
static void WiFiPlazaLobby_State_HandleMinigameReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1);
static void WiFiPlazaLobby_State_HandleSingleMinigameReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1);
static void WiFiPlazaLobby_State_HandleFourTrainerReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1);
static void WiFiPlazaLobby_State_HandleFourTrainerExtraReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1);
static void WiFiPlazaLobby_State_HandleMinigameFourTrainerReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1);
static void WiFiPlazaLobby_State_HandleNoopReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1);
static void WiFiPlazaLobby_State_PostMenuResultReport(WiFiPlazaLobbyState *param0, int param1);
static void WiFiPlazaLobby_State_ResetMinigameGrid(WiFiPlazaLobbyMinigameGrid *param0);
static void WiFiPlazaLobby_State_ActivateMinigameGrid(WiFiPlazaLobbyMinigameGrid *param0);
static void WiFiPlazaLobby_State_UpdateMinigameSchedule(WiFiPlazaLobbyMinigameGrid *param0);
static inline void WiFiPlazaLobby_State_SlotToRowCol(u32 param0, u32 *param1, u32 *param2);
static u32 WiFiPlazaLobby_State_FindFreeMinigameSlot(WiFiPlazaLobbyMinigameGrid *param0, u32 param1, int param2);
static void WiFiPlazaLobby_State_RemoveMinigameSlot(WiFiPlazaLobbyMinigameGrid *param0, u32 param1);
static u32 WiFiPlazaLobby_State_GetMinigameSlot(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1);
static int WiFiPlazaLobby_State_GetMinigameGroupStatus(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1);
static u32 WiFiPlazaLobby_State_GetMinigameGroupTimer(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1);
static void WiFiPlazaLobby_State_SetMinigameSlotFlag(WiFiPlazaLobbyMinigameGrid *param0, u32 param1);
static BOOL WiFiPlazaLobby_State_GetMinigameSlotFlag(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1);
static void WiFiPlazaLobby_State_ClearMinigameSlotFlag(WiFiPlazaLobbyMinigameGrid *param0, u32 param1);
static u32 WiFiPlazaLobby_State_FindMinigameSlot(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1);
static void WiFiPlazaLobby_State_SetMinigamePriority(WiFiPlazaLobbyMinigameGrid *param0, u32 param1, int param2);
static BOOL WiFiPlazaLobby_State_CheckMinigamePriority(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1, int param2);
static int WiFiPlazaLobby_State_GetMinigamePriority(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1);
static void WiFiPlazaLobby_State_HandleInteractionResponse(s32 param0, const void *param1, u32 param2, void *param3);
static void WiFiPlazaLobby_State_HandleInteractionUpdate(s32 param0, const void *param1, u32 param2, void *param3);
static void WiFiPlazaLobby_State_HandleInteractionResult(s32 param0, const void *param1, u32 param2, void *param3);
static void WiFiPlazaLobby_State_HandleInteractionEnd(s32 param0, const void *param1, u32 param2, void *param3);
static void WiFiPlazaLobby_State_DispatchReport(s32 param0, const void *param1, u32 param2, void *param3);
static void WiFiPlazaLobby_State_MarkPlayerFlag(s32 param0, const void *param1, u32 param2, void *param3);
static void WiFiPlazaLobby_State_AddPlayerToMinigameGrid(s32 param0, const void *param1, u32 param2, void *param3);
static void WiFiPlazaLobby_State_MarkMinigameSlotFlag(s32 param0, const void *param1, u32 param2, void *param3);
static void WiFiPlazaLobby_State_ResetMinigameWeights(WiFiPlazaLobbyMinigameWeights *param0);
static void WiFiPlazaLobby_State_ReduceMinigameWeight(WiFiPlazaLobbyMinigameWeights *param0, u32 param1, u32 param2);
static u32 WiFiPlazaLobby_State_ChooseWeightedMinigameGroup(const WiFiPlazaLobbyMinigameWeights *param0);
static void WiFiPlazaLobby_State_SetPendingNewsPlayerFlag(WiFiPlazaLobbyNewsPlayerFlags *param0, u32 param1, BOOL param2);
static BOOL WiFiPlazaLobby_State_GetPendingNewsPlayerFlag(const WiFiPlazaLobbyNewsPlayerFlags *param0, u32 param1);
static void WiFiPlazaLobby_State_InitPasswordState(WiFiPlazaLobbyPasswordState *param0, u32 param1);
static void WiFiPlazaLobby_State_FreePasswordState(WiFiPlazaLobbyPasswordState *param0);
static void WiFiPlazaLobby_State_SetPasswordEntry(WiFiPlazaLobbyPasswordState *param0, u32 param1, BOOL param2, u32 param3);
static BOOL WiFiPlazaLobby_State_GetPasswordEntryFlag(const WiFiPlazaLobbyPasswordState *param0, u32 param1);
static const WiFiPlazaLobbyPasswordWords *WiFiPlazaLobby_State_GetPasswordEntry(const WiFiPlazaLobbyPasswordState *param0, u32 param1);
static void WiFiPlazaLobby_State_GeneratePasswordWords(PasswordWordBank *param0, u32 param1, WiFiPlazaLobbyPasswordWords *param2);
static void WiFiPlazaLobby_State_InitEventTimer(WiFiPlazaLobbyEventTimer *param0, u32 param1, u32 param2);
static void WiFiPlazaLobby_State_StartEventTimer(WiFiPlazaLobbyEventTimer *param0);
static void WiFiPlazaLobby_State_UpdateEventTimer(WiFiPlazaLobbyEventTimer *param0);
static u32 WiFiPlazaLobby_State_GetEventTimerCounter(const WiFiPlazaLobbyEventTimer *param0);
static int WiFiPlazaLobby_State_GetEventTimerStage(const WiFiPlazaLobbyEventTimer *param0);
static void WiFiPlazaLobby_State_InitRecentPlayers(WiFiPlazaLobbyRecentPlayers *param0, const SaveData *saveData);
static void WiFiPlazaLobby_State_PushRecentPlayer(WiFiPlazaLobbyRecentPlayers *param0, int param1, s32 param2);
static BOOL WiFiPlazaLobby_State_ReplaceRecentPlayer(WiFiPlazaLobbyRecentPlayers *param0, s32 param1, s32 param2);
static int WiFiPlazaLobby_State_PopRecentPlayer(WiFiPlazaLobbyRecentPlayers *param0);
static int WiFiPlazaLobby_State_GetRecentPlayerAppearance(WiFiPlazaLobbyRecentPlayers *param0, u32 param1);
static s32 WiFiPlazaLobby_State_GetRecentPlayerID(WiFiPlazaLobbyRecentPlayers *param0, u32 param1);
static void WiFiPlazaLobby_State_UpdateRecentPlayersChecksum(WiFiPlazaLobbyRecentPlayers *param0);
static void WiFiPlazaLobby_State_ValidateRecentPlayersChecksum(WiFiPlazaLobbyRecentPlayers *param0);
static BOOL WiFiPlazaLobby_State_HasRecentPlayersChecksumError(const WiFiPlazaLobbyRecentPlayers *param0);
static u32 WiFiPlazaLobby_State_FindTrainerAppearanceIndex(u32 param0);
static u32 GetTrainerAppearanceGraphicsID(u32 trainerAppearanceIdx);

static const s32 sMinigameGroupIds[9] = {
    0x0,
    0x168,
    0x2D0,
    0x4B0,
    0x618,
    0x780,
    0x960,
    0xAC8,
    0xC30
};

// clang-format off
static const WiFiPlazaTrainerAppearance sWiFiPlazaTrainerAppearances[APPEARANCES_COUNT * 2] = {
    { .graphicsID = OBJ_EVENT_GFX_SCHOOL_KID_M,  .gender = GENDER_MALE   },
    { .graphicsID = OBJ_EVENT_GFX_BUG_CATCHER,   .gender = GENDER_MALE   },
    { .graphicsID = OBJ_EVENT_GFX_ACE_TRAINER_M, .gender = GENDER_MALE   },
    { .graphicsID = OBJ_EVENT_GFX_ROUGHNECK,     .gender = GENDER_MALE   },
    { .graphicsID = OBJ_EVENT_GFX_RUIN_MANIAC,   .gender = GENDER_MALE   },
    { .graphicsID = OBJ_EVENT_GFX_BLACK_BELT,    .gender = GENDER_MALE   },
    { .graphicsID = OBJ_EVENT_GFX_RICH_BOY,      .gender = GENDER_MALE   },
    { .graphicsID = OBJ_EVENT_GFX_PSYCHIC,       .gender = GENDER_MALE   },
    { .graphicsID = OBJ_EVENT_GFX_LASS,          .gender = GENDER_FEMALE },
    { .graphicsID = OBJ_EVENT_GFX_BATTLE_GIRL,   .gender = GENDER_FEMALE },
    { .graphicsID = OBJ_EVENT_GFX_BEAUTY,        .gender = GENDER_FEMALE },
    { .graphicsID = OBJ_EVENT_GFX_ACE_TRAINER_F, .gender = GENDER_FEMALE },
    { .graphicsID = OBJ_EVENT_GFX_IDOL,          .gender = GENDER_FEMALE },
    { .graphicsID = OBJ_EVENT_GFX_SOCIALITE,     .gender = GENDER_FEMALE },
    { .graphicsID = OBJ_EVENT_GFX_COWGIRL,       .gender = GENDER_FEMALE },
    { .graphicsID = OBJ_EVENT_GFX_LADY,          .gender = GENDER_FEMALE },
};
// clang-format on

static const WiFiPlazaLobbyEventTimerStage sEventTimerStages[] = {
    { 0x2, 0x50 },
    { 0x1, 0x2 },
    { 0x3, 0x8E },
    { 0x1, 0x2 },
    { 0x4, 0x1E }
};

static const WiFiPlazaLobbyNetworkMessageHandler sMainMessageHandlers[8] = {
    { WiFiPlazaLobby_State_HandleInteractionResponse, sizeof(WiFiPlazaLobbyInteractionData) },
    { WiFiPlazaLobby_State_HandleInteractionUpdate, sizeof(WiFiPlazaLobbyInteractionData) },
    { WiFiPlazaLobby_State_HandleInteractionResult, sizeof(WiFiPlazaLobbyInteractionData) },
    { WiFiPlazaLobby_State_HandleInteractionEnd, sizeof(WiFiPlazaLobbyInteractionData) },
    { WiFiPlazaLobby_State_DispatchReport, sizeof(WiFiPlazaLobbyProfileViewMessage) },
    { WiFiPlazaLobby_State_MarkPlayerFlag, sizeof(u32) },
    { WiFiPlazaLobby_State_AddPlayerToMinigameGrid, sizeof(u32) },
    { WiFiPlazaLobby_State_MarkMinigameSlotFlag, sizeof(u32) }
};

WiFiPlazaLobbyState *WiFiPlazaLobby_State_Create(SaveData *saveData, enum HeapID heapID)
{
    WiFiPlazaLobbyState *v0 = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyState));
    memset(v0, 0, sizeof(WiFiPlazaLobbyState));

    v0->saveData = saveData;
    v0->heapID = heapID;

    {
        WiFiPlazaLobbyNetworkCallbacks v1;

        v1.unk_00 = WiFiPlazaLobby_State_HandleMemberJoined;
        v1.unk_04 = WiFiPlazaLobby_State_HandleMemberLeft;
        v1.unk_08 = WiFiPlazaLobby_State_HandleMemberUpdated;
        v1.unk_0C = WiFiPlazaLobby_State_HandleLobbyTimeEvent;
        v1.unk_10 = WiFiPlazaLobby_State_HandleMemberProfileReceived;

        WiFiPlazaLobby_Network_New(heapID, v0->saveData, sizeof(WiFiPlazaProfile), &v1, v0);
    }

    {
        int v2;

        v0->unk_04.unk_00 = WiFiPlazaLobby_News_New(heapID);

        for (v2 = 0; v2 < 4; v2++) {
            v0->unk_04.trainerInfos[v2] = TrainerInfo_New(heapID);
        }
    }

    WiFiPlazaLobby_State_BuildLocalProfile(&v0->unk_108, v0->saveData, heapID);
    WiFiPlazaLobby_State_ResetInteractionState(&v0->unk_1C0);
    WiFiPlazaLobby_State_ClearPlayerFlags(&v0->unk_1E8);
    WiFiPlazaLobby_Network_SetMainMessageHandler(sMainMessageHandlers, 8, v0);
    WiFiPlazaLobby_State_InitEventState(&v0->unk_1FC);
    WiFiPlazaLobby_State_ResetMinigameGrid(&v0->unk_20C);
    WiFiPlazaLobby_State_ResetMinigameWeights(&v0->unk_3AB);
    WiFiPlazaLobby_State_InitPasswordState(&v0->unk_3E4, heapID);
    WiFiPlazaLobby_State_InitRecentPlayers(&v0->unk_4BC, v0->saveData);
    WiFiPlazaLobby_State_CreateTrainerInfo(&v0->unk_508, heapID);

    return v0;
}

void WiFiPlazaLobby_State_Destroy(WiFiPlazaLobbyState *param0)
{
    {
        WiFiPlazaQuestion *wiFiPlazaQuestion;
        WiFiPlazaLobbyQuestionnaireAnswer v1;

        WiFiPlazaLobby_State_GetQuestionnaireAnswer(&param0->unk_108.profile, &v1);

        wiFiPlazaQuestion = SaveData_GetWiFiPlazaQuestion(param0->saveData);

        WiFiPlazaQuestion_SetQuestionNumber(wiFiPlazaQuestion, v1.questionNumber);
        WiFiPlazaQuestion_SetSelectedAnswer(wiFiPlazaQuestion, v1.selectedAnswer);
    }

    WiFiPlazaLobby_State_FreeTrainerInfo(&param0->unk_508);
    WiFiPlazaLobby_State_FreePasswordState(&param0->unk_3E4);

    {
        WiFiPlazaLobby_Network_ClearMainMessageHandler();
    }

    {
        int v2;

        WiFiPlazaLobby_News_Free(param0->unk_04.unk_00);

        for (v2 = 0; v2 < 4; v2++) {
            Heap_Free(param0->unk_04.trainerInfos[v2]);
        }
    }

    WiFiPlazaLobby_Network_Free();
    Heap_Free(param0);
}

void WiFiPlazaLobby_State_Init(WiFiPlazaLobbyState *param0)
{
    WiFiPlazaLobby_News_Reset(param0->unk_04.unk_00);

    {
        s64 v0;

        WiFiPlazaLobby_Network_GetCurrentTime(&v0);
        param0->unk_04.unk_D4 = v0;
        WiFiPlazaLobby_Time_SetFromSeconds(&param0->unk_04.unk_D0, &v0);
    }

    {
        WiFiPlazaLobby_State_CheckEventTimeout(param0);
    }

    {
        WiFiPlazaLobby_State_UpdateInteractionTimer(&param0->unk_1C0);
    }

    WiFiPlazaLobby_State_ClearPlayerFlags(&param0->unk_1E8);
    WiFiPlazaLobby_State_ResetEventFlags(&param0->unk_F8);
    WiFiPlazaLobby_State_UpdateEventTimers(&param0->unk_1FC, &param0->unk_F8, &param0->unk_20C, &param0->unk_49C);
    WiFiPlazaLobby_State_TickTimer(&param0->unk_3A0);
    WiFiPlazaLobby_State_UpdateMinigameSchedule(&param0->unk_20C);
    WiFiPlazaLobby_State_UpdateEventTimer(&param0->unk_49C);

    {
        BOOL v1;

        v1 = WiFiPlazaLobby_State_HasRecentPlayersChecksumError(&param0->unk_4BC);

        if (v1 == 1) {
            param0->unk_52C = 1;
        }
    }
}

void WiFiPlazaLobby_State_UpdateNoop(WiFiPlazaLobbyState *param0)
{
    return;
}

int WiFiPlazaLobby_State_GetErrorFlag(const WiFiPlazaLobbyState *param0)
{
    return param0->unk_52C;
}

BOOL WiFiPlazaLobby_State_CheckNetworkEvent(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_Network_ConsumeExcessFlood();
}

WiFiPlazaLobbyNews *WiFiPlazaLobby_State_GetNewsManager(WiFiPlazaLobbyState *param0)
{
    return param0->unk_04.unk_00;
}

const WiFiPlazaLobbyPlaceList *WiFiPlazaLobby_State_GetPlayerCountryTable(WiFiPlazaLobbyState *param0)
{
    WiFiPlazaLobby_State_BuildMemberLocationList(&param0->unk_108, &param0->unk_04.unk_08);

    return &param0->unk_04.unk_08;
}

const WiFiPlazaLobbyTime *WiFiPlazaLobby_State_GetCurrentTime(const WiFiPlazaLobbyState *param0)
{
    return &param0->unk_04.unk_D0;
}

BOOL WiFiPlazaLobby_State_PopPlayerJoined(WiFiPlazaLobbyState *param0, u32 param1)
{
    if (param0->unk_F8.unk_00 & (1 << param1)) {
        param0->unk_F8.unk_00 &= ~(1 << param1);
        return 1;
    }

    return 0;
}

BOOL WiFiPlazaLobby_State_PopPlayerLeft(WiFiPlazaLobbyState *param0, u32 param1)
{
    if (param0->unk_F8.unk_04 & (1 << param1)) {
        param0->unk_F8.unk_04 &= ~(1 << param1);
        return 1;
    }

    return 0;
}

BOOL WiFiPlazaLobby_State_CheckTimeEventFlag(WiFiPlazaLobbyState *param0, int param1)
{
    if (param0->unk_F8.unk_08 & (1 << param1)) {
        return 1;
    }

    return 0;
}

BOOL WiFiPlazaLobby_State_PopPlayerUpdated(WiFiPlazaLobbyState *param0, u32 param1)
{
    if (param0->unk_F8.unk_0C & (1 << param1)) {
        param0->unk_F8.unk_0C &= ~(1 << param1);
        return 1;
    }

    return 0;
}

SaveData *WiFiPlazaLobby_State_GetSaveData(WiFiPlazaLobbyState *param0)
{
    return param0->saveData;
}

BOOL WiFiPlazaLobby_State_IsArceusRoom(const WiFiPlazaLobbyState *param0)
{
    GF_ASSERT(param0);
    return WiFiPlazaLobby_Network_GetScheduleValue(WiFiPlazaLobbyNetworkScheduleField_04);
}

BOOL WiFiPlazaLobby_State_IsQuestionAnswered(const WiFiPlazaLobbyState *param0)
{
    GF_ASSERT(param0);

    return param0->unk_1FC.unk_0F_0;
}

BOOL WiFiPlazaLobby_State_IsQuestionAcknowledged(const WiFiPlazaLobbyState *param0)
{
    GF_ASSERT(param0);
    return param0->unk_1FC.unk_0F_4;
}

void WiFiPlazaLobby_State_MarkQuestionAcknowledged(WiFiPlazaLobbyState *param0)
{
    param0->unk_1FC.unk_0F_4 = 1;
}

BOOL WiFiPlazaLobby_State_IsLobbyLocked(const WiFiPlazaLobbyState *param0)
{
    return param0->unk_1FC.unk_00_0;
}

BOOL WiFiPlazaLobby_State_IsLobbyClosed(const WiFiPlazaLobbyState *param0)
{
    return param0->unk_1FC.unk_00_7;
}

BOOL WiFiPlazaLobby_State_IsLobbyCloseFinished(const WiFiPlazaLobbyState *param0)
{
    if ((param0->unk_1FC.unk_00_1 == 1) && (param0->unk_1FC.unk_04 <= 0)) {
        return 1;
    } else {
        return 0;
    }
}

int WiFiPlazaLobby_State_GetFireworksState(const WiFiPlazaLobbyState *param0)
{
    if (param0->unk_1FC.unk_08 <= 0) {
        return param0->unk_1FC.unk_00_2;
    }

    return 0;
}

BOOL WiFiPlazaLobby_State_IsParadeFinished(const WiFiPlazaLobbyState *param0)
{
    if ((param0->unk_1FC.unk_00_4 == 1) && (param0->unk_1FC.unk_0A <= 0)) {
        return 1;
    }

    return 0;
}

BOOL WiFiPlazaLobby_State_IsMinigameFinished(const WiFiPlazaLobbyState *param0)
{
    return param0->unk_1FC.unk_00_5;
}

BOOL WiFiPlazaLobby_State_IsNeonTransitionComplete(const WiFiPlazaLobbyState *param0)
{
    if ((param0->unk_04.unk_04 == 1) && (param0->unk_1FC.unk_06 <= 0)) {
        return 1;
    }

    return 0;
}

PPW_LOBBY_TIME_EVENT WiFiPlazaLobby_State_GetNeonATimeEvent(const WiFiPlazaLobbyState *param0)
{
    if (param0->unk_1FC.unk_06 <= 0) {
        return param0->unk_1FC.unk_01;
    }

    return PPW_LOBBY_TIME_EVENT_NEON_A0;
}

PPW_LOBBY_TIME_EVENT WiFiPlazaLobby_State_GetNeonBTimeEvent(const WiFiPlazaLobbyState *param0)
{
    if (param0->unk_1FC.unk_06 <= 0) {
        return param0->unk_1FC.unk_02;
    }

    return PPW_LOBBY_TIME_EVENT_NEON_B0;
}

PPW_LOBBY_TIME_EVENT WiFiPlazaLobby_State_GetNeonCTimeEvent(const WiFiPlazaLobbyState *param0)
{
    if (param0->unk_1FC.unk_06 <= 0) {
        return param0->unk_1FC.unk_03;
    }

    return PPW_LOBBY_TIME_EVENT_NEON_C0;
}

void WiFiPlazaLobby_State_StartWarpTimer(WiFiPlazaLobbyState *param0)
{
    WiFiPlazaLobby_State_ResetTimer(&param0->unk_3A0);
}

BOOL WiFiPlazaLobby_State_IsWarpTimerActive(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_State_IsTimerActive(&param0->unk_3A0);
}

BOOL WiFiPlazaLobby_State_IsTrainerInfoValid(const WiFiPlazaLobbyState *param0)
{
    return param0->unk_508.unk_04;
}

void WiFiPlazaLobby_State_SetTrainerInfoValid(WiFiPlazaLobbyState *param0, BOOL param1)
{
    param0->unk_508.unk_04 = param1;
}

void WiFiPlazaLobby_State_ClearUserIDTable(WiFiPlazaLobbyState *param0)
{
    MI_CpuClear32(&param0->unk_3DF, sizeof(WiFiPlazaLobbyQuestionnaireData));
}

void WiFiPlazaLobby_State_SetPlayerSlotUserID(WiFiPlazaLobbyState *param0, s32 param1, u32 param2)
{
    u32 v0;

    GF_ASSERT(param2 < 4);
    v0 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1);
    GF_ASSERT(v0 != 0xffffffff);

    param0->unk_3DF.unk_00[param2] = v0;
}

void WiFiPlazaLobby_State_SetMyPlayerSlot(WiFiPlazaLobbyState *param0, u32 param1)
{
    s32 v0 = WiFiPlazaLobby_Network_GetMyUserId();
    WiFiPlazaLobby_State_SetPlayerSlotUserID(param0, v0, param1);
}

void WiFiPlazaLobby_State_GetUserIDTable(const WiFiPlazaLobbyState *param0, WiFiPlazaLobbyQuestionnaireData *param1)
{
    MI_CpuCopy8(&param0->unk_3DF, param1, sizeof(WiFiPlazaLobbyQuestionnaireData));
}

void WiFiPlazaLobby_State_SetPlayerWarpPending(WiFiPlazaLobbyState *param0)
{
    WiFiPlazaLobby_State_SetTimerExpired(&param0->unk_3A0);
}

BOOL WiFiPlazaLobby_State_IsPlayerWarpPending(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_State_IsTimerExpired(&param0->unk_3A0);
}

void WiFiPlazaLobby_State_SetBGMSuppressed(WiFiPlazaLobbyState *param0, BOOL param1)
{
    param0->unk_1FC.unk_0C = param1;
}

void WiFiPlazaLobby_State_PlayLobbyBGM(const WiFiPlazaLobbyState *param0)
{
    if ((param0->unk_1FC.unk_00_4 == 1) && (param0->unk_1FC.unk_0A <= 0)) {
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_21, SEQ_PL_WIFIPARADE_sseq, 0);
        WiFiPlazaLobby_State_UpdateMusicVolume(&param0->unk_1FC);
    } else {
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_21, SEQ_PL_WIFIUNION_sseq, 0);
        WiFiPlazaLobby_State_UpdateMusicVolume(&param0->unk_1FC);
    }
}

void WiFiPlazaLobby_State_SetBGMVolumeDucked(WiFiPlazaLobbyState *param0, BOOL param1)
{
    if (param1 != param0->unk_1FC.unk_0D) {
        param0->unk_1FC.unk_0D = param1;
        WiFiPlazaLobby_State_UpdateMusicVolume(&param0->unk_1FC);
    }
}

u32 WiFiPlazaLobby_State_GetMySlotIndex(const WiFiPlazaLobbyState *param0)
{
    s32 v0 = WiFiPlazaLobby_Network_GetMyUserId();
    return WiFiPlazaLobby_Network_FindMainPlayerIndex(v0);
}

s32 WiFiPlazaLobby_State_GetMyUserID(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_Network_GetMyUserId();
}

BOOL WiFiPlazaLobby_State_IsPlayerSlotOccupied(const WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaLobbyNetworkPlayerIdList v0;

    WiFiPlazaLobby_Network_GetMainPlayerList(&v0);

    if (v0.unk_04[param1] != DWC_LOBBY_INVALID_USER_ID) {
        return 1;
    }

    return 0;
}

const WiFiPlazaProfile *WiFiPlazaLobby_State_GetProfileBySlot(const WiFiPlazaLobbyState *param0, u32 param1)
{
    s32 v0;
    WiFiPlazaLobbyNetworkPlayerIdList v1;
    const WiFiPlazaProfile *v2;

    GF_ASSERT(param1 < 20);

    WiFiPlazaLobby_Network_GetMainPlayerList(&v1);

    v0 = v1.unk_04[param1];

    if (v0 == DWC_LOBBY_INVALID_USER_ID) {
        return NULL;
    }

    if (v0 == WiFiPlazaLobby_Network_GetMyUserId()) {
        v2 = &param0->unk_108.profile;
    } else {
        v2 = (const WiFiPlazaProfile *)WiFiPlazaLobby_Network_GetPlayerData(v0);
    }

    return v2;
}

WiFiPlazaProfile *WiFiPlazaLobby_State_GetOwnProfile(WiFiPlazaLobbyState *param0)
{
    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&param0->unk_108, param0->saveData) == 0) {
        param0->unk_52C = 1;
    }

    return &param0->unk_108.profile;
}

void WiFiPlazaLobby_State_SetCurrentVenue(WiFiPlazaLobbyState *param0, int param1)
{
    s32 v0;

    GF_ASSERT(param1 < 15);

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&param0->unk_108, param0->saveData) == 0) {
        param0->unk_52C = 1;
        return;
    }

    if (param0->unk_108.profile.unk_43 == param1) {
        return;
    }

    if (param1 != 9) {
        if (WiFiPlazaLobby_State_IsChatActive(param0) == 1) {
            if (WiFiPlazaLobby_State_IsChatRequested(param0) == 0) {
                v0 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param0->unk_1C0.unk_04);
                WiFiPlazaLobby_State_SendInteractionCancel(param0, param0->unk_1C0.unk_04);
            }

            WiFiPlazaLobby_State_AbortInteraction(&param0->unk_1C0);
        }
    }

    switch (param0->unk_108.profile.unk_43) {
    case 2:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->unk_4BC, 16, DWC_LOBBY_INVALID_USER_ID);
        break;
    case 3:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->unk_4BC, 17, DWC_LOBBY_INVALID_USER_ID);
        break;
    case 4:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->unk_4BC, 18, DWC_LOBBY_INVALID_USER_ID);
        break;
    case 5:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->unk_4BC, 19, DWC_LOBBY_INVALID_USER_ID);
        break;
    case 6:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->unk_4BC, 20, DWC_LOBBY_INVALID_USER_ID);
        break;
    case 7:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->unk_4BC, 21, DWC_LOBBY_INVALID_USER_ID);
        break;
    case 8:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->unk_4BC, 22, DWC_LOBBY_INVALID_USER_ID);
        break;

    default:
        break;
    }

    param0->unk_108.profile.unk_43 = param1;

    WiFiPlazaLobby_State_UpdateProfileChecksum(&param0->unk_108, param0->saveData);
    WiFiPlazaLobby_State_LoadCachedProfile(param0);
}

void WiFiPlazaLobby_State_SetAttendee(WiFiPlazaLobbyState *param0, int param1, s32 param2)
{
    GF_ASSERT(param1 < 24);

    WiFiPlazaLobby_State_PushRecentPlayer(&param0->unk_4BC, param1, param2);
    WiFiPlazaLobby_State_LoadCachedProfile(param0);
}

void WiFiPlazaLobby_State_SetAppearanceRank(WiFiPlazaLobbyState *param0, u32 param1)
{
    GF_ASSERT(param1 < 27);

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&param0->unk_108, param0->saveData) == 0) {
        param0->unk_52C = 1;
        return;
    }

    param0->unk_108.profile.unk_41 = param1;

    WiFiPlazaLobby_State_UpdateProfileChecksum(&param0->unk_108, param0->saveData);
    WiFiPlazaLobby_State_LoadCachedProfile(param0);
}

void WiFiPlazaLobby_State_SetPokemonTypes(WiFiPlazaLobbyState *param0, int type1, int type2)
{
    GF_ASSERT(type1 < NUM_POKEMON_TYPES);
    GF_ASSERT(type2 < NUM_POKEMON_TYPES);

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&param0->unk_108, param0->saveData) == 0) {
        param0->unk_52C = 1;
        return;
    }

    if (type1 >= NUM_POKEMON_TYPES) {
        return;
    }

    if (type2 >= NUM_POKEMON_TYPES) {
        return;
    }

    if (type1 == TYPE_NORMAL) {
        param0->unk_108.profile.unk_88[0] = type2;
        param0->unk_108.profile.unk_88[1] = TYPE_NORMAL;
    } else {
        param0->unk_108.profile.unk_88[0] = type1;
        param0->unk_108.profile.unk_88[1] = type2;
    }

    WiFiPlazaLobby_State_UpdateProfileChecksum(&param0->unk_108, param0->saveData);
    WiFiPlazaLobby_State_LoadCachedProfile(param0);
}

void WiFiPlazaLobby_State_SetQuestionnaireAnswer(WiFiPlazaLobbyState *param0, u32 param1, u32 param2)
{
    GF_ASSERT(param2 < 3);

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&param0->unk_108, param0->saveData) == 0) {
        param0->unk_52C = 1;
        return;
    }

    if (param2 >= 3) {
        return;
    }

    param0->unk_108.profile.unk_8C.questionNumber = param1;
    param0->unk_108.profile.unk_8C.selectedAnswer = param2;
    param0->unk_1FC.unk_0F_0 = 1;

    WiFiPlazaLobby_State_MarkActivityDone(param0, 6);
    WiFiPlazaLobby_State_UpdateProfileChecksum(&param0->unk_108, param0->saveData);
    WiFiPlazaLobby_State_LoadCachedProfile(param0);
}

void WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(const WiFiPlazaProfile *profile, TrainerInfo *trainerInfo, enum HeapID heapID)
{
    BOOL isTrainerNameValid = WiFiPlazaLobby_State_IsTrainerNameTerminated(profile->trainerName, TRAINER_NAME_LEN + 1);
    BOOL isTrainerNameInvalid = FALSE;

    if (isTrainerNameValid == TRUE) {
        String *trainerName, *tmpbuf; // must declare like this to match

        TrainerInfo_SetName(trainerInfo, profile->trainerName);

        tmpbuf = String_Init(NELEMS(profile->trainerName) * 4, heapID);
        trainerName = String_Init(NELEMS(profile->trainerName) * 4, heapID);
        TrainerInfo_NameString(trainerInfo, trainerName);
        isTrainerNameValid = Font_AreAllCharsValid(FONT_SYSTEM, trainerName, tmpbuf);

        if (isTrainerNameValid == FALSE) {
            isTrainerNameInvalid = TRUE;
        }

        String_Free(tmpbuf);
        String_Free(trainerName);
    } else {
        isTrainerNameInvalid = TRUE;
    }

    if (isTrainerNameInvalid) {
        MessageLoader *messageLoader = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0673, heapID);
        String *fallbackName = MessageLoader_GetNewString(messageLoader, pl_msg_00000673_00064);

        TrainerInfo_SetNameFromString(trainerInfo, fallbackName);
        String_Free(fallbackName);
        MessageLoader_Free(messageLoader);
    }

    TrainerInfo_SetID(trainerInfo, WiFiPlazaProfile_GetTrainerID(profile));
    TrainerInfo_SetGender(trainerInfo, WiFiPlazaProfile_GetGender(profile));
    TrainerInfo_SetAppearance(trainerInfo, WiFiPlazaProfile_GetTrainerAppearanceGraphicsID(profile));
    TrainerInfo_SetLanguage(trainerInfo, WiFiPlazaProfile_GetNormalizedLanguage(profile));
    TrainerInfo_SetMainStoryCleared(trainerInfo);
}

u32 WiFiPlazaLobby_State_GetVenueIndex(const WiFiPlazaProfile *profile)
{
    if (profile->unk_43 >= 14) {
        return 14;
    }

    return profile->unk_43;
}

int WiFiPlazaLobby_State_GetNthActiveSlot(const WiFiPlazaProfile *profile, u32 param1)
{
    int idx;
    int v1;

    GF_ASSERT(param1 < 12);

    v1 = 0;

    for (idx = 0; idx < 12; idx++) {
        if (profile->unk_4C[idx] < 24) {
            v1++;
        }

        if ((v1 - 1) == param1) {
            return profile->unk_4C[idx];
        }
    }

    return 24;
}

s32 WiFiPlazaLobby_State_GetNthActiveUserID(const WiFiPlazaProfile *profile, u32 param1)
{
    int idx;
    int v1;

    GF_ASSERT(param1 < 12);

    v1 = 0;

    for (idx = 0; idx < 12; idx++) {
        if (profile->unk_4C[idx] < 24) {
            v1++;
        }

        if ((v1 - 1) == param1) {
            return profile->unk_58[idx];
        }
    }

    return DWC_LOBBY_INVALID_USER_ID;
}

s32 WiFiPlazaLobby_State_GetProfileUserId(const WiFiPlazaProfile *profile)
{
    return profile->unk_00;
}

u32 WiFiPlazaProfile_GetTrainerID(const WiFiPlazaProfile *profile)
{
    return profile->trainerID;
}

int WiFiPlazaLobby_State_GetTrainerAppearanceIndex(const WiFiPlazaProfile *profile)
{
    u32 trainerAppearance = WiFiPlazaProfile_GetTrainerAppearanceGraphicsID(profile);

    for (int idx = 0; idx < SNELEMS(sWiFiPlazaTrainerAppearances); idx++) {
        if (sWiFiPlazaTrainerAppearances[idx].graphicsID == trainerAppearance) {
            return idx;
        }
    }

    return 24;
}

WiFiPlazaLobbyTime WiFiPlazaLobby_State_GetProfileLocation(const WiFiPlazaProfile *profile)
{
    return profile->unk_1C;
}

u32 WiFiPlazaProfile_GetGender(const WiFiPlazaProfile *profile)
{
    u32 gender;

    if (profile->trainerGender >= GENDER_NONE) {
        u32 graphicsID = GetTrainerAppearanceGraphicsID(profile->trainerAppearanceIdx);

        if (graphicsID != 0xffff) {
            for (int idx = 0; idx < NELEMS(sWiFiPlazaTrainerAppearances); idx++) {
                if (sWiFiPlazaTrainerAppearances[idx].graphicsID == profile->trainerAppearanceIdx) {
                    gender = sWiFiPlazaTrainerAppearances[idx].graphicsID;
                }
            }
        } else {
            gender = GENDER_FEMALE;
        }
    } else {
        gender = profile->trainerGender;
    }

    return gender;
}

u32 WiFiPlazaProfile_GetNormalizedLanguage(const WiFiPlazaProfile *profile)
{
    return WiFiPlazaProfile_IsLanguageValid(profile) == TRUE
        ? profile->language
        : LANGUAGE_ENGLISH;
}

BOOL WiFiPlazaProfile_IsLanguageValid(const WiFiPlazaProfile *profile)
{
    switch (profile->language) {
    case LANGUAGE_JAPANESE:
    case LANGUAGE_ENGLISH:
    case LANGUAGE_FRENCH:
    case LANGUAGE_ITALIAN:
    case LANGUAGE_GERMAN:
    case LANGUAGE_SPANISH:
        return TRUE;
    }

    return FALSE;
}

u32 WiFiPlazaProfile_GetLanguage(const WiFiPlazaProfile *profile)
{
    return profile->language;
}

u32 WiFiPlazaProfile_GetTrainerAppearanceGraphicsID(const WiFiPlazaProfile *profile)
{
    u32 trainerAppearance = GetTrainerAppearanceGraphicsID(profile->trainerAppearanceIdx);

    if (trainerAppearance != 0xffff) {
        return trainerAppearance;
    }

    if (WiFiPlazaProfile_GetGender(profile) == GENDER_MALE) {
        return OBJ_EVENT_GFX_SCHOOL_KID_M;
    }

    return OBJ_EVENT_GFX_LASS;
}

u32 WiFiPlazaLobby_State_GetCountry(const WiFiPlazaProfile *profile)
{
    u32 country;

    if (profile->country >= 234) {
        country = 0;
    } else {
        if (WiFiPlazaLobby_Time_IsValidCountryRegion(profile->country, profile->region) == 0) {
            return 0;
        }

        country = profile->country;
    }

    return country;
}

u32 WiFiPlazaLobby_State_GetRegion(const WiFiPlazaProfile *profile)
{
    u32 region;

    if (WiFiPlazaLobby_Time_IsValidCountryRegion(profile->country, profile->region) == 0) {
        region = 0;
    } else {
        region = profile->region;
    }

    return region;
}

u32 WiFiPlazaLobby_State_GetAppearanceRank(const WiFiPlazaProfile *profile)
{
    u32 v0;

    if (profile->unk_41 == 0xff) {
        return 0;
    }

    if (profile->unk_41 >= 27) {
        v0 = 0;
    } else {
        v0 = profile->unk_41;
    }

    return v0;
}

BOOL WiFiPlazaLobby_State_IsAppearanceRankSet(const WiFiPlazaProfile *profile)
{
    if (profile->unk_41 == 0xff) {
        return 0;
    }

    return 1;
}

int WiFiPlazaLobby_State_GetProfilePokemonType(const WiFiPlazaProfile *profile, u32 index)
{
    GF_ASSERT(index < 2);

    if (profile->unk_88[index] >= NUM_POKEMON_TYPES) {
        return TYPE_NORMAL;
    }

    return profile->unk_88[index];
}

void WiFiPlazaLobby_State_GetQuestionnaireAnswer(const WiFiPlazaProfile *profile, WiFiPlazaLobbyQuestionnaireAnswer *param1)
{
    *param1 = profile->unk_8C;
}

TrainerInfo *WiFiPlazaLobby_State_GetLocalTrainerInfo(const WiFiPlazaLobbyState *param0)
{
    return param0->unk_508.trainerInfo;
}

BOOL WiFiPlazaLobby_State_IsMemberPresent(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetPendingNewsPlayerFlag(&param0->unk_3CB, param1);
}

void WiFiPlazaLobby_State_GetMemberPresentBitmap(const WiFiPlazaLobbyState *param0, WiFiPlazaLobbyNewsPlayerFlags *param1)
{
    WiFiPlazaLobbyNewsPlayerFlags *v0;

    MI_CpuCopy8(&param0->unk_3CB, param1, sizeof(WiFiPlazaLobbyNewsPlayerFlags));
}

BOOL WiFiPlazaLobby_State_HasMemberPassword(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetPasswordEntryFlag(&param0->unk_3E4, param1);
}

const WiFiPlazaLobbyPasswordWords *WiFiPlazaLobby_State_GetMemberPassword(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetPasswordEntry(&param0->unk_3E4, param1);
}

u32 WiFiPlazaLobby_State_GetSecondaryMemberCount(const WiFiPlazaLobbyState *param0)
{
    WiFiPlazaLobbyNetworkPlayerIdList v0;

    WiFiPlazaLobby_Network_GetSubChannelPlayerList(&v0);
    return v0.unk_00;
}

u32 WiFiPlazaLobby_State_GetSecondaryMemberSlot(const WiFiPlazaLobbyState *param0, u32 param1)
{
    u32 v0 = WiFiPlazaLobby_Network_GetSubChannelPlayerUserId(param1);

    if (v0 == DWC_LOBBY_INVALID_USER_ID) {
        return 0xffffffff;
    }

    return WiFiPlazaLobby_Network_FindMainPlayerIndex(v0);
}

void WiFiPlazaLobby_State_SendProfileViewMessage(WiFiPlazaLobbyState *param0, u32 param1, u32 param2)
{
    WiFiPlazaLobbyProfileViewMessage v0 = { 0 };

    v0.unk_11 = 0;
    v0.unk_00[0] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param1);
    v0.unk_00[1] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param2);
    v0.unk_10 = 2;

    WiFiPlazaLobby_Network_SendMainChannelMessage(4, &v0, sizeof(WiFiPlazaLobbyProfileViewMessage));
}

void WiFiPlazaLobby_State_SendProfileViewMessageWithExtra(WiFiPlazaLobbyState *param0, u32 param1, u32 param2, u32 param3)
{
    WiFiPlazaLobbyProfileViewMessage v0 = { 0 };

    v0.unk_11 = 1;
    v0.unk_00[0] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param2);
    v0.unk_00[1] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param1);
    v0.unk_10 = 2;
    v0.unk_12 = param3;

    WiFiPlazaLobby_Network_SendMainChannelMessage(4, &v0, sizeof(WiFiPlazaLobbyProfileViewMessage));
}

void WiFiPlazaLobby_State_SendMinigameProfileViewMessage(WiFiPlazaLobbyState *param0, enum PlazaMinigame param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, BOOL param7)
{
    WiFiPlazaLobbyProfileViewMessage v0 = { 0 };
    u32 v1;

    switch (param1) {
    case WiFiPlazaLobbyActivity_00:
    case WiFiPlazaLobbyActivity_01:
    case WiFiPlazaLobbyActivity_02:
        v1 = 2;
        break;
    case WiFiPlazaLobbyActivity_03:
    case WiFiPlazaLobbyActivity_04:
        v1 = 3;
        break;
    case WiFiPlazaLobbyActivity_05:
        v1 = 4;
        break;
    case WiFiPlazaLobbyActivity_06:
        v1 = 5;
        break;
    default:
        return;
    }

    v0.unk_11 = v1;
    v0.unk_00[0] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param3);
    v0.unk_00[1] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param4);
    v0.unk_00[2] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param5);
    v0.unk_00[3] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param6);
    v0.unk_10 = param2;
    v0.unk_13_0 = param1;
    v0.unk_13_7 = param7;

    WiFiPlazaLobby_Network_SendMainChannelMessage(4, &v0, sizeof(WiFiPlazaLobbyProfileViewMessage));
}

void WiFiPlazaLobby_State_SendMinigameResultMessage(WiFiPlazaLobbyState *param0, enum PlazaMinigame param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6)
{
    WiFiPlazaLobbyProfileViewMessage v0 = { 0 };
    u32 v1;

    switch (param1) {
    case WiFiPlazaLobbyActivity_00:
    case WiFiPlazaLobbyActivity_01:
    case WiFiPlazaLobbyActivity_02:
        v1 = 8;
        break;
    default:
        return;
    }
    v0.unk_11 = v1;
    v0.unk_00[0] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param3);
    v0.unk_00[1] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param4);
    v0.unk_00[2] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param5);
    v0.unk_00[3] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param6);
    v0.unk_10 = param2;
    v0.unk_13_0 = param1;
    v0.unk_13_7 = 0;

    WiFiPlazaLobby_Network_SendMainChannelMessage(4, &v0, sizeof(WiFiPlazaLobbyProfileViewMessage));
}

u32 WiFiPlazaLobby_State_GetLobbySeason(const WiFiPlazaLobbyState *param0)
{
    u32 v0 = WiFiPlazaLobby_Network_GetScheduleValue(WiFiPlazaLobbyNetworkScheduleField_03);

    if (v0 >= 5) {
        v0 = 0;
    }

    return v0;
}

u32 WiFiPlazaLobby_State_GetLobbyRoomType(const WiFiPlazaLobbyState *param0)
{
    u32 v0 = WiFiPlazaLobby_Network_GetScheduleValue(WiFiPlazaLobbyNetworkScheduleField_02);

    if (v0 >= 5) {
        v0 = 0;
    }

    return v0;
}

u32 WiFiPlazaLobby_State_GetLobbyCloseTime(const WiFiPlazaLobbyState *param0)
{
    u32 v0 = WiFiPlazaLobby_Network_GetScheduleValue(WiFiPlazaLobbyNetworkScheduleField_05);
    v0 += ((30 * 30) / 30);

    return v0;
}

BOOL WiFiPlazaLobby_State_IsMemberCosmeticKnown(const WiFiPlazaLobbyState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    return param0->unk_1E8.unk_00[param1];
}

void WiFiPlazaLobby_State_BroadcastCosmeticID(WiFiPlazaLobbyState *param0, u32 param1)
{
    u32 v0 = param1;
    WiFiPlazaLobby_Network_SendMainChannelMessage(5, &v0, sizeof(u32));
}

int WiFiPlazaLobby_State_GetFloatState(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetMinigameGroupStatus(&param0->unk_20C, param1);
}

u32 WiFiPlazaLobby_State_GetFloatTimer(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetMinigameGroupTimer(&param0->unk_20C, param1);
}

u32 WiFiPlazaLobby_State_GetFloatTimerMax(const WiFiPlazaLobbyState *param0)
{
    return 40 * 30;
}

u32 WiFiPlazaLobby_State_FindFloatSlotByUserID(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_FindMinigameSlot(&param0->unk_20C, param1);
}

u32 WiFiPlazaLobby_State_AllocateFloatSlot(WiFiPlazaLobbyState *param0, u32 param1, int param2)
{
    return WiFiPlazaLobby_State_FindFreeMinigameSlot(&param0->unk_20C, param1, param2);
}

void WiFiPlazaLobby_State_FreeFloatSlot(WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaLobby_State_RemoveMinigameSlot(&param0->unk_20C, param1);
}

void WiFiPlazaLobby_State_SetFloatSlotTrigger(WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaLobby_State_SetMinigameSlotFlag(&param0->unk_20C, param1);
}

BOOL WiFiPlazaLobby_State_IsFloatSlotTriggered(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetMinigameSlotFlag(&param0->unk_20C, param1);
}

void WiFiPlazaLobby_State_ClearFloatSlotTrigger(WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaLobby_State_ClearMinigameSlotFlag(&param0->unk_20C, param1);
}

void WiFiPlazaLobby_State_FloatSlotToRowCol(u32 param0, u32 *param1, u32 *param2)
{
    WiFiPlazaLobby_State_SlotToRowCol(param0, param1, param2);
}

void WiFiPlazaLobby_State_SetFloatSlotPosition(WiFiPlazaLobbyState *param0, u32 param1, int param2)
{
    WiFiPlazaLobby_State_SetMinigamePriority(&param0->unk_20C, param1, param2);
}

int WiFiPlazaLobby_State_GetFloatSlotPosition(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetMinigamePriority(&param0->unk_20C, param1);
}

void WiFiPlazaLobby_State_SendFloatJoinEvent(WiFiPlazaLobbyState *param0)
{
    u32 v0;

    WiFiPlazaLobby_Network_SendMainChannelMessage(6, &v0, sizeof(u32));
}

void WiFiPlazaLobby_State_SendFloatTriggerEvent(WiFiPlazaLobbyState *param0)
{
    u32 v0;

    WiFiPlazaLobby_Network_SendMainChannelMessage(7, &v0, sizeof(u32));
}

void WiFiPlazaLobby_State_ResetChat(WiFiPlazaLobbyState *param0)
{
    WiFiPlazaLobby_State_ResetInteraction(&param0->unk_1C0);
}

BOOL WiFiPlazaLobby_State_RequestChat(WiFiPlazaLobbyState *param0, u32 param1)
{
    s32 v0;

    if (param0->unk_1C0.unk_0A != 0) {
        return 0;
    }

    {
        const WiFiPlazaProfile *v1 = WiFiPlazaLobby_State_GetProfileBySlot(param0, param1);
        u32 v2 = WiFiPlazaLobby_State_GetVenueIndex(v1);

        if (v2 != 1) {
            return 0;
        }
    }

    param0->unk_1C0.unk_04 = param1;
    param0->unk_1C0.unk_06 = 1;
    param0->unk_1C0.unk_0A = 1;

    WiFiPlazaLobby_State_SetInteractionData(&param0->unk_1C0, 0);
    v0 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param1);
    WiFiPlazaLobby_Network_SendPlayerMessage(0, v0, &param0->unk_1C0.unk_20, sizeof(WiFiPlazaLobbyInteractionData));
    WiFiPlazaLobby_State_StartInteractionTimer(&param0->unk_1C0);

    return 1;
}

void WiFiPlazaLobby_State_UpdateChatRequest(WiFiPlazaLobbyState *param0, u16 param1)
{
    BOOL isTrainerNameValid = FALSE;
    s32 v1;

    if (param0->unk_1C0.unk_0A == 1) {
        if (param0->unk_1C0.unk_06 != 2) {
            isTrainerNameValid = TRUE;
        }
    } else {
        if (param0->unk_1C0.unk_0A == 2) {
            if (param0->unk_1C0.unk_06 != 3) {
                isTrainerNameValid = TRUE;
            }
        }
    }

    if (isTrainerNameValid) {
        v1 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param0->unk_1C0.unk_04);
        WiFiPlazaLobby_State_SendInteractionCancel(param0, v1);
        return;
    }

    switch (param0->unk_1C0.unk_0A) {
    case 1:
        param0->unk_1C0.unk_06 = 3;
        break;
    case 2:
        param0->unk_1C0.unk_06 = 2;
        break;
    default:
        v1 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param0->unk_1C0.unk_04);
        WiFiPlazaLobby_State_SendInteractionCancel(param0, v1);
        return;
    }

    WiFiPlazaLobby_State_SetInteractionData(&param0->unk_1C0, param1);
    v1 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param0->unk_1C0.unk_04);
    WiFiPlazaLobby_Network_SendPlayerMessage(2, v1, &param0->unk_1C0.unk_20, sizeof(WiFiPlazaLobbyInteractionData));
    WiFiPlazaLobby_State_StartInteractionTimer(&param0->unk_1C0);
}

void WiFiPlazaLobby_State_CompleteChat(WiFiPlazaLobbyState *param0)
{
    s32 v0;

    if (param0->unk_1C0.unk_06 == 0) {
        return;
    }

    if (param0->unk_1C0.unk_0A != 1) {
        return;
    }

    param0->unk_1C0.unk_20.unk_02 = 0;
    v0 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param0->unk_1C0.unk_04);

    WiFiPlazaLobby_Network_SendPlayerMessage(3, v0, &param0->unk_1C0.unk_20, sizeof(WiFiPlazaLobbyInteractionData));
    WiFiPlazaLobby_State_ResetInteraction(&param0->unk_1C0);
}

void WiFiPlazaLobby_State_EndChat(WiFiPlazaLobbyState *param0)
{
    s32 v0;

    if (param0->unk_1C0.unk_06 == 0) {
        return;
    }

    v0 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param0->unk_1C0.unk_04);

    param0->unk_1C0.unk_06 = 4;
    param0->unk_1C0.unk_20.unk_02 = 4;

    WiFiPlazaLobby_Network_SendPlayerMessage(2, v0, &param0->unk_1C0.unk_20, sizeof(WiFiPlazaLobbyInteractionData));
}

BOOL WiFiPlazaLobby_State_IsChatActive(const WiFiPlazaLobbyState *param0)
{
    if (param0->unk_1C0.unk_0A != 0) {
        return 1;
    }

    return 0;
}

BOOL WiFiPlazaLobby_State_IsChatRequested(const WiFiPlazaLobbyState *param0)
{
    if (param0->unk_1C0.unk_0A == 2) {
        return 1;
    }

    return 0;
}

u32 WiFiPlazaLobby_State_GetChatPartner(const WiFiPlazaLobbyState *param0)
{
    return param0->unk_1C0.unk_04;
}

BOOL WiFiPlazaLobby_State_HasChattedWithCurrentMember(const WiFiPlazaLobbyState *param0)
{
    return param0->unk_1C0.unk_0B;
}

int WiFiPlazaLobby_State_GetChatState(const WiFiPlazaLobbyState *param0)
{
    return param0->unk_1C0.unk_06;
}

u16 WiFiPlazaLobby_State_GetChatResponse(const WiFiPlazaLobbyState *param0)
{
    return param0->unk_1C0.unk_08;
}

BOOL WiFiPlazaLobby_State_CanChatWithMember(const WiFiPlazaLobbyState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param0->unk_1C0.unk_0C[param1] >= 6) {
        return 0;
    }

    return 1;
}

BOOL WiFiPlazaLobby_State_IsChatFinished(const WiFiPlazaLobbyState *param0)
{
    if (param0->unk_1C0.unk_06 == 4) {
        return 1;
    }

    if (WiFiPlazaLobby_State_CheckInteractionTimeout(&param0->unk_1C0) == 0) {
        return 1;
    }

    return 0;
}

s16 WiFiPlazaLobby_State_GetChatTimer(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_State_GetInteractionTimer(&param0->unk_1C0);
}

void WiFiPlazaLobby_State_SetChatPending(WiFiPlazaLobbyState *param0)
{
    param0->unk_1C0.unk_07 = 1;
}

BOOL WiFiPlazaLobby_State_IsChatPending(const WiFiPlazaLobbyState *param0)
{
    return param0->unk_1C0.unk_07;
}

void WiFiPlazaLobby_State_ResetChatIfActive(WiFiPlazaLobbyState *param0)
{
    if (WiFiPlazaLobby_State_IsChatActive(param0) == 1) {
        WiFiPlazaLobby_State_IncrementPlayerCounter(&param0->unk_1C0, param0->unk_1C0.unk_04);
    }
}

void WiFiPlazaLobby_State_IncrementMemberChatCount(WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaLobby_State_IncrementPlayerCounter(&param0->unk_1C0, param1);
}

void WiFiPlazaLobby_State_MarkMemberChatted(WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaLobby_State_SetPlayerFlag(&param0->unk_1C0, param1);
}

void WiFiPlazaLobby_State_RecordChatJournal(WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaProfile *v0;
    TrainerInfo *trainerInfo;
    void *journalEntryOnlineEvent;
    JournalEntry *journalEntry = SaveData_GetJournal(param0->saveData);
    v0 = (WiFiPlazaProfile *)WiFiPlazaLobby_State_GetProfileBySlot(param0, param1);

    if (v0 != NULL) {
        trainerInfo = TrainerInfo_New(HEAP_ID_112);
        WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, trainerInfo, HEAP_ID_112);
        journalEntryOnlineEvent = JournalEntry_CreateEventInteraction(TrainerInfo_Name(trainerInfo), v0->trainerGender, HEAP_ID_112, ONLINE_EVENT_CHATTED_IN_PLAZA);

        JournalEntry_SaveData(journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
        Heap_Free(trainerInfo);
    }
}

void WiFiPlazaLobby_State_RecordTapToyJournal(WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaProfile *v0;
    TrainerInfo *trainerInfo;
    void *journalEntryOnlineEvent;
    JournalEntry *journalEntry = SaveData_GetJournal(param0->saveData);
    v0 = (WiFiPlazaProfile *)WiFiPlazaLobby_State_GetProfileBySlot(param0, param1);

    if (v0 != NULL) {
        trainerInfo = TrainerInfo_New(HEAP_ID_112);
        WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, trainerInfo, HEAP_ID_112);
        journalEntryOnlineEvent = JournalEntry_CreateEventInteraction(TrainerInfo_Name(trainerInfo), v0->trainerGender, HEAP_ID_112, ONLINE_EVENT_GOT_TAP_TOY);

        JournalEntry_SaveData(journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
        Heap_Free(trainerInfo);
    }
}

void WiFiPlazaLobby_State_RecordMinigameJournal(WiFiPlazaLobbyState *param0, enum PlazaMinigame minigame)
{
    void *journalEntryOnlineEvent;
    JournalEntry *journalEntry = SaveData_GetJournal(param0->saveData);

    switch (minigame) {
    case WiFiPlazaLobbyActivity_00:
    case WiFiPlazaLobbyActivity_01:
    case WiFiPlazaLobbyActivity_02:
        journalEntryOnlineEvent = JournalEntry_CreateEventPlazaMinigame(minigame, 112, ONLINE_EVENT_PLAZA_MINIGAME);
        break;
    case WiFiPlazaLobbyActivity_03:
    case WiFiPlazaLobbyActivity_04:
        journalEntryOnlineEvent = JournalEntry_CreateEventMisc(112, ONLINE_EVENT_PLAYED_WITH_FOOTPRINT_STAMP);
        break;
    case WiFiPlazaLobbyActivity_05:
        journalEntryOnlineEvent = JournalEntry_CreateEventMisc(112, ONLINE_EVENT_VIEWED_PLAZA_VISITOR_PROFILES);
        break;
    case WiFiPlazaLobbyActivity_06:
        journalEntryOnlineEvent = JournalEntry_CreateEventMisc(112, ONLINE_EVENT_READ_PLAZA_NEWS);
        break;
    default:
        journalEntryOnlineEvent = NULL;
        break;
    }

    if (journalEntryOnlineEvent) {
        JournalEntry_SaveData(journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
    }
}

void WiFiPlazaLobby_State_RecordParadeJournal(WiFiPlazaLobbyState *param0)
{
    JournalEntry *journalEntry = SaveData_GetJournal(param0->saveData);
    void *journalEntryOnlineEvent = JournalEntry_CreateEventMisc(112, ONLINE_EVENT_JOINED_PARADE);

    JournalEntry_SaveData(journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
}

void WiFiPlazaLobby_State_IncrementChatRecord(WiFiPlazaLobbyState *param0)
{
    GameRecords *v0 = SaveData_GetGameRecords(param0->saveData);
    GameRecords_IncrementRecordValue(v0, RECORD_UNK_046);
}

void WiFiPlazaLobby_State_IncrementMinigameRecord(WiFiPlazaLobbyState *param0)
{
    GameRecords *v0 = SaveData_GetGameRecords(param0->saveData);
    GameRecords_IncrementRecordValue(v0, RECORD_UNK_118);
}

void WiFiPlazaLobby_State_MarkActivityDone(WiFiPlazaLobbyState *param0, int param1)
{
    GF_ASSERT(param1 < 8);
    param0->unk_3A3.unk_00[param1] = 1;
}

int WiFiPlazaLobby_State_GetAvailableActivity(const WiFiPlazaLobbyState *param0)
{
    int v0;
    BOOL v1;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->unk_3A3.unk_00[v0] == 0) {
            switch (v0) {
            case 0:
            case 1:
            case 2:
                if (WiFiPlazaLobby_State_IsMinigameFinished(param0) == 1) {
                    v1 = 0;
                } else {
                    v1 = 1;
                }
                break;
            case 3:
            case 4:
            case 5:
                if (WiFiPlazaLobby_State_IsLobbyClosed(param0) == 1) {
                    v1 = 0;
                } else {
                    v1 = 1;
                }
                break;
            case 6:
                if (WiFiPlazaLobby_State_IsNeonTransitionComplete(param0) == 1) {
                    v1 = 0;
                } else {
                    v1 = 1;
                }
                break;
            default:
            case 7:
                v1 = 1;
                break;
            }

            if (v1 == 1) {
                return v0;
            }
        }
    }

    return 8;
}

u32 WiFiPlazaLobby_State_ChooseCosmeticID(const WiFiPlazaLobbyState *param0)
{
    u32 v0 = WiFiPlazaLobby_State_ChooseWeightedMinigameGroup(&param0->unk_3AB);

    if (WiFiPlazaLobby_State_IsMemberPresent(param0, WiFiPlazaLobby_State_GetMySlotIndex(param0)) == 1) {
        v0 += (3 - 1);
    }

    return v0;
}

int WiFiPlazaLobby_State_GetFireworksEventStage(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_State_GetEventTimerStage(&param0->unk_49C);
}

u32 WiFiPlazaLobby_State_GetFireworksFrame(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_State_GetEventTimerCounter(&param0->unk_49C);
}

void WiFiPlazaLobby_State_SetQuestionnaireResult(WiFiPlazaLobbyState *param0, const WiFiLobbyQuestionnaireAnswerTally *param1)
{
    param0->unk_510.unk_14 = 1;
    param0->unk_510.unk_00 = *param1;
}

BOOL WiFiPlazaLobby_State_GetQuestionnaireResult(const WiFiPlazaLobbyState *param0, WiFiLobbyQuestionnaireAnswerTally *param1)
{
    if (param0->unk_510.unk_14 == 1) {
        *param1 = param0->unk_510.unk_00;
        return 1;
    }

    return 0;
}

void WiFiPlazaLobby_State_CreateWFCTrainerInfo(WiFiPlazaLobbyState *param0)
{
    TrainerInfo *info;

    GF_ASSERT(param0->unk_4B8 == NULL);

    info = SaveData_GetTrainerInfo(param0->saveData);
    param0->unk_4B8 = WFCTrainerInfo_New(info, param0->heapID);
}

void WiFiPlazaLobby_State_FreeWFCTrainerInfo(WiFiPlazaLobbyState *param0)
{
    if (param0->unk_4B8 != NULL) {
        WFCTrainerInfo_Free(param0->unk_4B8);
        param0->unk_4B8 = NULL;
    }
}

static BOOL WiFiPlazaLobby_State_IsTrainerNameTerminated(const charcode_t *trainerName, u32 length)
{
    for (int idx = 0; idx < length; idx++) {
        if (trainerName[idx] == CHAR_EOS) {
            return TRUE;
        }
    }

    return FALSE;
}

static void WiFiPlazaLobby_State_HandleMemberJoined(s32 param0, const void *param1, void *param2, BOOL param3)
{
    WiFiPlazaLobbyState *v0;
    u32 v1;
    const WiFiPlazaProfile *v2;
    s32 v3;
    u32 v4;

    v0 = param2;

    if (param3) {
        WiFiPlazaLobby_State_InitTrainerInfoFromProfile(&v0->unk_508, &v0->unk_108, v0->heapID);

        if (WiFiPlazaLobby_State_ValidateProfileChecksum(&v0->unk_108, v0->saveData) == 0) {
            v0->unk_52C = 1;
        }

        v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);
        WiFiPlazaLobby_News_SetResult(v0->unk_04.unk_00, v1, v0->unk_108.profile.trainerGender, WiFiPlazaLobbyNewsResultFlags_01 | WiFiPlazaLobbyNewsResultFlags_02);
        v0->unk_108.profile.unk_00 = param0;

        {
            s64 v5;

            WiFiPlazaLobby_Network_GetPlayerEnterTime(param0, &v5);
            WiFiPlazaLobby_Time_SetFromSeconds(&v0->unk_108.profile.unk_18, &v5);
        }

        {
            u32 v6, v7;
            BOOL v8;

            v6 = WiFiPlazaLobby_State_GetCountry(&v0->unk_108.profile);
            v7 = WiFiPlazaLobby_State_GetRegion(&v0->unk_108.profile);
            v8 = WiFiPlazaProfile_IsLanguageValid(&v0->unk_108.profile);

            if ((v6 != 0) && (v8 == 1)) {
                v0->unk_108.profile.unk_1C = WiFiPlazaLobby_Earth_ComputeLocalTimeOffset(v6, v7, v0->unk_108.profile.unk_18, v0->heapID);
            } else {
                v0->unk_108.profile.unk_1C.unk_00_val2_unk_00 = 12;
                v0->unk_108.profile.unk_1C.unk_00_val2_unk_01 = 0;
                v0->unk_108.profile.unk_1C.unk_00_val2_unk_02 = 0;
            }
        }

        WiFiPlazaLobby_State_UpdateProfileChecksum(&v0->unk_108, v0->saveData);
        WiFiPlazaLobby_State_LoadCachedProfile(v0);
    } else {
        v2 = (const WiFiPlazaProfile *)param1;
        v3 = WiFiPlazaLobby_Network_FindFirstPlayer();
        v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

        WiFiPlazaLobby_News_SetResult(v0->unk_04.unk_00, v1, WiFiPlazaProfile_GetGender(v2), WiFiPlazaLobbyNewsResultFlags_00);

        if (v3 == param0) {
            WiFiPlazaLobby_News_SelectResult(v0->unk_04.unk_00, v1);
        }

        if (WiFiPlazaLobby_State_ReplaceRecentPlayer(&v0->unk_4BC, param0, DWC_LOBBY_INVALID_USER_ID)) {
            WiFiPlazaLobby_State_LoadCachedProfile(v0);
        }
    }

    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);
    v0->unk_F8.unk_00 |= 1 << v1;

    if (WiFiPlazaLobby_Network_IsVipProfile(param0) == 1) {
        u32 v9;

        WiFiPlazaLobby_State_SetPendingNewsPlayerFlag(&v0->unk_3CB, v1, 1);

        {
            WiFiPlazaLobbyNewsTrainerEntry v10;

            v10.unk_00 = v1;
            WiFiPlazaLobby_News_AddTrainerEntry(v0->unk_04.unk_00, &v10, &v0->unk_3CB);
        }

        v9 = WiFiPlazaLobby_Network_GetVipKey(param0);

        if (v9 != 0) {
            WiFiPlazaLobby_State_SetPasswordEntry(&v0->unk_3E4, v1, 1, v9);
        } else {
            WiFiPlazaLobby_State_SetPasswordEntry(&v0->unk_3E4, v1, 0, v9);
        }
    } else {
        WiFiPlazaLobby_State_SetPendingNewsPlayerFlag(&v0->unk_3CB, v1, 0);
        WiFiPlazaLobby_State_SetPasswordEntry(&v0->unk_3E4, v1, 0, 0);
    }
}

static void WiFiPlazaLobby_State_HandleMemberLeft(s32 param0, void *param1)
{
    WiFiPlazaLobbyState *v0;
    u32 v1, v2;
    BOOL v3;
    s32 v4;

    v0 = param1;

    if (param0 == WiFiPlazaLobby_Network_GetMyUserId()) {
        return;
    }

    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    if (WiFiPlazaLobby_State_IsChatActive(v0) == 1) {
        if (WiFiPlazaLobby_State_GetChatPartner(v0) == v1) {
            WiFiPlazaLobby_State_AbortInteraction(&v0->unk_1C0);
        }
    }

    v3 = WiFiPlazaLobby_News_TakeResultFlag(v0->unk_04.unk_00, v1);

    if (v3) {
        v4 = WiFiPlazaLobby_Network_FindFirstPlayerExcept(param0);
        v2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(v4);

        WiFiPlazaLobby_News_SelectResult(v0->unk_04.unk_00, v2);
    }

    WiFiPlazaLobby_State_SetPendingNewsPlayerFlag(&v0->unk_3CB, v1, 0);
    WiFiPlazaLobby_State_ResetPlayerCounter(&v0->unk_1C0, v1);
    WiFiPlazaLobby_State_ClearPlayerFlag(&v0->unk_1C0, v1);

    if (WiFiPlazaLobby_State_ReplaceRecentPlayer(&v0->unk_4BC, param0, DWC_LOBBY_INVALID_USER_ID)) {
        WiFiPlazaLobby_State_LoadCachedProfile(v0);
    }

    WiFiPlazaLobby_State_SetPasswordEntry(&v0->unk_3E4, v1, 0, 0);

    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);
    v0->unk_F8.unk_04 |= 1 << v1;
}

static void WiFiPlazaLobby_State_HandleMemberUpdated(s32 param0, const void *param1, void *param2)
{
    WiFiPlazaLobbyState *v0;
    u32 v1;
    const WiFiPlazaProfile *v2;
    u32 v3;

    v0 = param2;
    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    v0->unk_F8.unk_0C |= 1 << v1;

    v2 = param1;
    v3 = WiFiPlazaLobby_State_GetVenueIndex(v2);

    switch (v3) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        WiFiPlazaLobby_State_ResetPlayerCounter(&v0->unk_1C0, v1);
        break;
    default:
        break;
    }

    if (WiFiPlazaLobby_State_IsAppearanceRankSet(v2) == 1) {
        WiFiPlazaLobby_State_ReduceMinigameWeight(&v0->unk_3AB, WiFiPlazaLobby_State_GetAppearanceRank(v2), v1);
    }
}

static void WiFiPlazaLobby_State_HandleLobbyTimeEvent(PPW_LOBBY_TIME_EVENT param0, void *param1)
{
    WiFiPlazaLobbyState *v0;
    BOOL v1 = 0;
    int v2;

    v0 = param1;

    {
        PPW_LobbyTimeInfo v3;

        PPW_LobbyGetTimeInfo(&v3);
        WiFiPlazaLobby_Time_SetFromSeconds(&v0->unk_04.unk_D0, &v3.currentTime);

        v0->unk_04.unk_D4 = v3.currentTime;
    }

    switch (param0) {
    case PPW_LOBBY_TIME_EVENT_LOCK:
        WiFiPlazaLobby_News_SetPlazaInfo(v0->unk_04.unk_00, &v0->unk_04.unk_D0);
        v0->unk_04.unk_DC = v0->unk_04.unk_D4;
        v0->unk_1FC.unk_00_0 = 1;
        v0->unk_F8.unk_08 |= 1 << 0;
        break;
    case PPW_LOBBY_TIME_EVENT_NEON_A1:
    case PPW_LOBBY_TIME_EVENT_NEON_A2:
    case PPW_LOBBY_TIME_EVENT_NEON_A3:
    case PPW_LOBBY_TIME_EVENT_NEON_A4:
    case PPW_LOBBY_TIME_EVENT_NEON_A5:
        if (v0->unk_04.unk_04 == 0) {
            v1 = 1;
            v2 = 0;

            v0->unk_04.unk_04 = 1;
            v0->unk_1FC.unk_06 = (10 * 30);
        }
    case PPW_LOBBY_TIME_EVENT_NEON_A0:
        v0->unk_1FC.unk_01 = param0;
        v0->unk_F8.unk_08 |= 1 << 1;
        break;
    case PPW_LOBBY_TIME_EVENT_NEON_B1:
    case PPW_LOBBY_TIME_EVENT_NEON_B2:
    case PPW_LOBBY_TIME_EVENT_NEON_B3:
        if (v0->unk_04.unk_04 == 0) {
            v1 = 1;
            v2 = 0;

            v0->unk_04.unk_04 = 1;
            v0->unk_1FC.unk_06 = (10 * 30);
        }
    case PPW_LOBBY_TIME_EVENT_NEON_B0:
        v0->unk_1FC.unk_02 = param0;
        v0->unk_F8.unk_08 |= 1 << 2;
        break;
    case PPW_LOBBY_TIME_EVENT_NEON_C1:
    case PPW_LOBBY_TIME_EVENT_NEON_C2:
    case PPW_LOBBY_TIME_EVENT_NEON_C3:
        if (v0->unk_04.unk_04 == 0) {
            v1 = 1;
            v2 = 0;

            v0->unk_04.unk_04 = 1;
            v0->unk_1FC.unk_06 = (10 * 30);
        }

    case PPW_LOBBY_TIME_EVENT_NEON_C0:
        v0->unk_1FC.unk_03 = param0;
        v0->unk_F8.unk_08 |= 1 << 3;
        break;
    case PPW_LOBBY_TIME_EVENT_FIRE_WORKS_START:
        v1 = 1;
        v2 = 1;

        {
            u32 v4, v5;

            v4 = WiFiPlazaLobby_Network_GetScheduleValue(WiFiPlazaLobbyNetworkScheduleField_06);
            v5 = WiFiPlazaLobby_Network_GetScheduleValue(WiFiPlazaLobbyNetworkScheduleField_07);

            WiFiPlazaLobby_State_InitEventTimer(&v0->unk_49C, v4, v5);
        }

        v0->unk_1FC.unk_08 = (10 * 30);
        break;
    case PPW_LOBBY_TIME_EVENT_FIRE_WORKS_END:
        v0->unk_1FC.unk_00_2 = 2;
        v0->unk_F8.unk_08 |= 1 << 5;
        break;
    case PPW_LOBBY_TIME_EVENT_PARADE:
        v1 = 1;
        v2 = 2;

        v0->unk_1FC.unk_0A = (10 * 30);
        break;
    case PPW_LOBBY_TIME_EVENT_CLOSE:
        v1 = 1;
        v2 = 4;

        v0->unk_1FC.unk_00_7 = 1;
        v0->unk_1FC.unk_04 = (30 * 30);
        break;
    case PPW_LOBBY_TIME_EVENT_MINIGAME_END:
        v0->unk_1FC.unk_00_5 = 1;
        v0->unk_F8.unk_08 |= 1 << 4;
        break;
    default:
        break;
    }

    if (v1) {
        WiFiPlazaLobby_State_PostMenuResultReport(v0, v2);
    }
}

static void WiFiPlazaLobby_State_HandleMemberProfileReceived(const void *param0, u32 param1, void *param2)
{
    WiFiPlazaLobbyState *v0;
    const WiFiPlazaProfile *v1;

    v0 = param2;
    v1 = param0;

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&v0->unk_108, v0->saveData) == 0) {
        v0->unk_52C = 1;
        return;
    }

    WiFiPlazaLobby_State_CopyProfile(&v0->unk_108, v1, param1);
    WiFiPlazaLobby_State_UpdateProfileChecksum(&v0->unk_108, v0->saveData);
}

static void WiFiPlazaLobby_State_BuildMemberLocationList(WiFiPlazaLobbyProfileCache *param0, WiFiPlazaLobbyPlaceList *param1)
{
    int v0;
    WiFiPlazaLobbyNetworkPlayerIdList v1;
    const WiFiPlazaProfile *v2;
    WiFiPlazaLobbyPlaceList *v3;
    u8 v4;
    u8 v5;

    memset(param1, 0, sizeof(WiFiPlazaLobbyPlaceList));

    WiFiPlazaLobby_Network_GetMainPlayerList(&v1);

    v2 = &param0->profile;
    WiFiPlazaLobby_Time_AddPlace(param1, WiFiPlazaLobby_State_GetCountry(v2), WiFiPlazaLobby_State_GetRegion(v2), 0);

    for (v0 = 0; v0 < 20; v0++) {
        if (v1.unk_04[v0] != DWC_LOBBY_INVALID_USER_ID) {
            v2 = (const WiFiPlazaProfile *)WiFiPlazaLobby_Network_GetPlayerData(v1.unk_04[v0]);
            WiFiPlazaLobby_Time_AddPlace(param1, WiFiPlazaLobby_State_GetCountry(v2), WiFiPlazaLobby_State_GetRegion(v2), 0);
        }
    }

    for (v0 = 0; v0 < 20; v0++) {
        v4 = WiFiPlazaLobby_Network_GetPlayerCountry(v0);
        v5 = WiFiPlazaLobby_Network_GetPlayerRegion(v0);

        WiFiPlazaLobby_Time_AddPlace(param1, v4, v5, 1);
    }
}

static void WiFiPlazaLobby_State_CheckEventTimeout(WiFiPlazaLobbyState *param0)
{
    s64 v0;
    s64 v1;

    if ((param0->unk_1FC.unk_00_0 == 1) && (param0->unk_1FC.unk_00_7 == 0) && (WiFiPlazaLobby_Network_GetState() == WiFiPlazaLobbyNetworkLobbyState_02)) {
        v0 = WiFiPlazaLobby_State_GetLobbyCloseTime(param0);
        v0 += param0->unk_04.unk_DC;

        v1 = param0->unk_04.unk_D4;

        if (v1 > v0) {
            param0->unk_1FC.unk_00_7 = 1;
            param0->unk_1FC.unk_04 = (30 * 30);
        }
    }
}

static void WiFiPlazaLobby_State_BuildLocalProfile(WiFiPlazaLobbyProfileCache *param0, SaveData *saveData, enum HeapID heapID)
{
    // must forward-declare to match
    TrainerInfo *trainerInfo;
    Party *party;
    WiFiHistory *wiFiHistory;
    Pokedex *pokedex;
    GameTime *gameTime;

    trainerInfo = SaveData_GetTrainerInfo(saveData);
    party = SaveData_GetParty(saveData);
    pokedex = SaveData_GetPokedex(saveData);
    wiFiHistory = SaveData_WiFiHistory(saveData);
    gameTime = SaveData_GetGameTime(saveData);

    String *trainerName = TrainerInfo_NameNewString(trainerInfo, heapID);
    String_ToChars(trainerName, param0->profile.trainerName, NELEMS(param0->profile.trainerName));
    String_ToChars(trainerName, param0->unk_00, NELEMS(param0->unk_00));
    String_Free(trainerName);

    param0->profile.unk_00 = DWC_LOBBY_INVALID_USER_ID;
    param0->profile.trainerID = TrainerInfo_ID(trainerInfo);

    int partyCount = Party_GetCurrentCount(party);
    for (int partyIdx = 0; partyIdx < MAX_PARTY_SIZE; partyIdx++) {
        if (partyIdx < partyCount) {
            Pokemon *pokemon = Party_GetPokemonBySlotIndex(party, partyIdx);
            param0->profile.partySpecies[partyIdx] = Pokemon_GetValue(pokemon, MON_DATA_SPECIES, NULL);
            param0->profile.partyForms[partyIdx] = Pokemon_GetValue(pokemon, MON_DATA_FORM, NULL);
            param0->profile.partyIsEgg[partyIdx] = Pokemon_GetValue(pokemon, MON_DATA_IS_EGG, NULL);
        } else {
            param0->profile.partySpecies[partyIdx] = SPECIES_BAD_EGG;
        }
    }

    param0->profile.trainerGender = TrainerInfo_Gender(trainerInfo);
    param0->profile.language = TrainerInfo_Language(trainerInfo);
    param0->profile.trainerAppearanceIdx = TrainerInfo_Appearance(trainerInfo);
    param0->profile.trainerAppearanceIdx = WiFiPlazaLobby_State_FindTrainerAppearanceIndex(param0->profile.trainerAppearanceIdx);
    param0->profile.country = WiFiHistory_GetCountry(wiFiHistory);
    param0->profile.region = WiFiHistory_GetRegion(wiFiHistory);
    param0->profile.isNationalDexObtained = Pokedex_IsNationalDexObtained(pokedex);
    param0->profile.isMainStoryCleared = TrainerInfo_IsMainStoryCleared(trainerInfo);
    param0->profile.unk_41 = 0xff;
    param0->profile.unk_43 = 0;
    param0->profile.gameVersion = GAME_VERSION;
    param0->profile.startTimestamp = gameTime->startTimestamp;

    for (int i = 0; i < 12; i++) {
        param0->profile.unk_4C[i] = 24;
        param0->profile.unk_58[i] = DWC_LOBBY_INVALID_USER_ID;
    }

    for (int i = 0; i < 2; i++) {
        param0->profile.unk_88[i] = TYPE_NORMAL;
    }

    param0->profile.unk_8C.questionNumber = 0xffffffff;
    param0->profile.unk_8C.selectedAnswer = 3;

    WiFiPlazaLobby_State_UpdateProfileChecksum(param0, saveData);
}

static void WiFiPlazaLobby_State_LoadCachedProfile(WiFiPlazaLobbyState *param0)
{
    int v0;
    const WiFiPlazaProfile *v1;

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&param0->unk_108, param0->saveData) == 0) {
        param0->unk_52C = 1;
        return;
    }

    for (v0 = 0; v0 < 12; v0++) {
        param0->unk_108.profile.unk_4C[v0] = WiFiPlazaLobby_State_GetRecentPlayerAppearance(&param0->unk_4BC, v0);
        param0->unk_108.profile.unk_58[v0] = WiFiPlazaLobby_State_GetRecentPlayerID(&param0->unk_4BC, v0);
    }

    MI_CpuCopy8(param0->unk_108.unk_10, param0->unk_108.profile.trainerName, sizeof(u16) * (7 + 1));
    WiFiPlazaLobby_Network_SetMyProfile(&param0->unk_108.profile);

    MI_CpuCopy8(param0->unk_108.unk_00, param0->unk_108.profile.trainerName, sizeof(u16) * (7 + 1));
    WiFiPlazaLobby_State_UpdateProfileChecksum(&param0->unk_108, param0->saveData);
}

static void WiFiPlazaLobby_State_UpdateProfileChecksum(WiFiPlazaLobbyProfileCache *param0, const SaveData *saveData)
{
    param0->unk_B4 = SaveData_CalculateChecksum(saveData, &param0->profile, sizeof(WiFiPlazaProfile));
}

static BOOL WiFiPlazaLobby_State_ValidateProfileChecksum(const WiFiPlazaLobbyProfileCache *param0, const SaveData *saveData)
{
    u32 v0 = SaveData_CalculateChecksum(saveData, &param0->profile, sizeof(WiFiPlazaProfile));

    if (v0 != param0->unk_B4) {
        GF_ASSERT(FALSE);
        return 0;
    }

    return 1;
}

static void WiFiPlazaLobby_State_CopyProfile(WiFiPlazaLobbyProfileCache *param0, const WiFiPlazaProfile *param1, u32 param2)
{
    param0->profile = *param1;

    if (sizeof(WiFiPlazaProfile) >= param2) {
        MI_CpuCopy8(param1, &param0->profile, param2);
    } else {
        MI_CpuCopy8(param1, &param0->profile, sizeof(WiFiPlazaProfile));
    }

    MI_CpuCopy8(param1->trainerName, param0->unk_10, sizeof(u16) * (7 + 1));
    MI_CpuCopy8(param0->unk_00, param0->profile.trainerName, sizeof(u16) * (7 + 1));
}

static void WiFiPlazaLobby_State_ResetEventFlags(WiFiPlazaLobbyEventFlags *param0)
{
    param0->unk_08 = 0;
}

static void WiFiPlazaLobby_State_UpdateEventTimers(WiFiPlazaLobbyEventTimers *param0, WiFiPlazaLobbyEventFlags *param1, WiFiPlazaLobbyMinigameGrid *param2, WiFiPlazaLobbyEventTimer *param3)
{
    if ((param0->unk_04 - 1) >= 0) {
        param0->unk_04--;

        if (param0->unk_04 == (28 * 30)) {
            Sound_FadeOutBGM(0, 127);
            param0->unk_0E = 1;
        }
    } else if (param0->unk_04 == 0) {
        param0->unk_00_1 = 1;
        param1->unk_08 |= 1 << 7;
        param0->unk_04--;
    }

    if ((param0->unk_06 - 1) >= 0) {
        param0->unk_06--;
    } else if (param0->unk_06 == 0) {
        param1->unk_08 |= 1 << 2;
        param1->unk_08 |= 1 << 3;
        param1->unk_08 |= 1 << 1;
        param0->unk_06--;
    }

    if ((param0->unk_08 - 1) >= 0) {
        param0->unk_08--;
    } else if (param0->unk_08 == 0) {
        param0->unk_00_2 = 1;
        param1->unk_08 |= 1 << 5;
        param0->unk_08--;
        WiFiPlazaLobby_State_StartEventTimer(param3);
    }

    if ((param0->unk_0A - 1) >= 0) {
        param0->unk_0A--;
    } else if (param0->unk_0A == 0) {
        WiFiPlazaLobby_State_ActivateMinigameGrid(param2);

        if (param0->unk_0C == 0) {
            Sound_PlayBGM(SEQ_PL_WIFIPARADE_sseq);
        }

        param0->unk_00_4 = 1;
        param1->unk_08 |= 1 << 6;
        param0->unk_0A--;
    }
}

static void WiFiPlazaLobby_State_InitEventState(WiFiPlazaLobbyEventTimers *param0)
{
    param0->unk_00_0 = 0;
    param0->unk_00_1 = 0;
    param0->unk_00_2 = 0;
    param0->unk_00_4 = 0;
    param0->unk_00_5 = 0;
    param0->unk_00_7 = 0;
    param0->unk_01 = PPW_LOBBY_TIME_EVENT_NEON_A0;
    param0->unk_02 = PPW_LOBBY_TIME_EVENT_NEON_B0;
    param0->unk_03 = PPW_LOBBY_TIME_EVENT_NEON_C0;
    param0->unk_04 = -1;
    param0->unk_06 = -1;
    param0->unk_08 = -1;
    param0->unk_0A = -1;
}

static void WiFiPlazaLobby_State_UpdateMusicVolume(const WiFiPlazaLobbyEventTimers *param0)
{
    if (param0->unk_0D == 1) {
        Sound_SetPlayerVolume(7, (127 / 3));
    } else {
        Sound_SetPlayerVolume(7, 127);
    }
}

static void WiFiPlazaLobby_State_ResetTimer(WiFiPlazaLobbyTimer *param0)
{
    param0->unk_00 = (30 * 30);
}

static BOOL WiFiPlazaLobby_State_IsTimerActive(const WiFiPlazaLobbyTimer *param0)
{
    if (param0->unk_00 > 0) {
        return 1;
    }

    return 0;
}

static void WiFiPlazaLobby_State_TickTimer(WiFiPlazaLobbyTimer *param0)
{
    if (param0->unk_00 > 0) {
        param0->unk_00--;
    }
}

static void WiFiPlazaLobby_State_CreateTrainerInfo(WiFiPlazaLobbyTrainerInfoHolder *param0, enum HeapID heapID)
{
    param0->trainerInfo = TrainerInfo_New(heapID);
}

static void WiFiPlazaLobby_State_FreeTrainerInfo(WiFiPlazaLobbyTrainerInfoHolder *param0)
{
    Heap_Free(param0->trainerInfo);
}

static void WiFiPlazaLobby_State_InitTrainerInfoFromProfile(WiFiPlazaLobbyTrainerInfoHolder *param0, const WiFiPlazaLobbyProfileCache *param1, enum HeapID heapID)
{
    WiFiPlazaProfile *v0 = Heap_Alloc(heapID, sizeof(WiFiPlazaProfile));

    MI_CpuCopyFast(&param1->profile, v0, sizeof(WiFiPlazaProfile));
    MI_CpuCopy8(param1->unk_10, v0->trainerName, sizeof(u16) * (7 + 1));

    WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->trainerInfo, heapID);
    Heap_Free(v0);
}

static void WiFiPlazaLobby_State_SetTimerExpired(WiFiPlazaLobbyTimer *param0)
{
    param0->unk_02 = 1;
}

static BOOL WiFiPlazaLobby_State_IsTimerExpired(const WiFiPlazaLobbyTimer *param0)
{
    return param0->unk_02;
}

static void WiFiPlazaLobby_State_ClearPlayerFlags(WiFiPlazaLobbyPlayerFlags *param0)
{
    memset(param0, 0, sizeof(WiFiPlazaLobbyPlayerFlags));
}

static void WiFiPlazaLobby_State_ResetInteractionState(WiFiPlazaLobbyInteractionState *param0)
{
    memset(param0, 0, sizeof(WiFiPlazaLobbyInteractionState));
}

static void WiFiPlazaLobby_State_ResetInteraction(WiFiPlazaLobbyInteractionState *param0)
{
    param0->unk_04 = 0;
    param0->unk_06 = 0;
    param0->unk_0A = 0;

    WiFiPlazaLobby_State_StopInteractionTimer(param0);
}

static void WiFiPlazaLobby_State_AbortInteraction(WiFiPlazaLobbyInteractionState *param0)
{
    param0->unk_04 = 0;
    param0->unk_06 = 4;

    WiFiPlazaLobby_State_StopInteractionTimer(param0);

    param0->unk_0A = 0;
}

static BOOL WiFiPlazaLobby_State_IsPlayerFlagSet(const WiFiPlazaLobbyInteractionState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param0->unk_00 & (1 << param1)) {
        return 1;
    }

    return 0;
}

static void WiFiPlazaLobby_State_SetPlayerFlag(WiFiPlazaLobbyInteractionState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    param0->unk_00 |= (1 << param1);
}

static void WiFiPlazaLobby_State_ClearPlayerFlag(WiFiPlazaLobbyInteractionState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    param0->unk_00 &= ~(1 << param1);
}

static void WiFiPlazaLobby_State_IncrementPlayerCounter(WiFiPlazaLobbyInteractionState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if ((param0->unk_0C[param1] + 1) <= 6) {
        param0->unk_0C[param1]++;
    }
}

static void WiFiPlazaLobby_State_ResetPlayerCounter(WiFiPlazaLobbyInteractionState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    param0->unk_0C[param1] = 0;
}

static void WiFiPlazaLobby_State_SetInteractionData(WiFiPlazaLobbyInteractionState *param0, u16 param1)
{
    param0->unk_20.unk_02 = param0->unk_06;
    param0->unk_20.unk_00 = param1;
}

static void WiFiPlazaLobby_State_SendInteractionResult(WiFiPlazaLobbyState *param0, s32 param1, BOOL param2)
{
    param0->unk_1C0.unk_20.unk_02 = 2;
    param0->unk_1C0.unk_20.unk_00 = param2;

    WiFiPlazaLobby_Network_SendPlayerMessage(1, param1, &param0->unk_1C0.unk_20, sizeof(WiFiPlazaLobbyInteractionData));
}

static void WiFiPlazaLobby_State_SendInteractionCancel(WiFiPlazaLobbyState *param0, s32 param1)
{
    param0->unk_1C0.unk_06 = 4;
    param0->unk_1C0.unk_20.unk_02 = 4;

    WiFiPlazaLobby_Network_SendPlayerMessage(2, param1, &param0->unk_1C0.unk_20, sizeof(WiFiPlazaLobbyInteractionData));
}

static void WiFiPlazaLobby_State_StartInteractionTimer(WiFiPlazaLobbyInteractionState *param0)
{
    param0->unk_24 = 1;
    param0->unk_26 = 0;
}

static void WiFiPlazaLobby_State_StopInteractionTimer(WiFiPlazaLobbyInteractionState *param0)
{
    param0->unk_24 = 0;
    param0->unk_26 = 0;
}

static void WiFiPlazaLobby_State_UpdateInteractionTimer(WiFiPlazaLobbyInteractionState *param0)
{
    if (param0->unk_24 == 1) {
        if ((param0->unk_26 + 1) <= 900) {
            param0->unk_26++;
        }
    }
}

static BOOL WiFiPlazaLobby_State_CheckInteractionTimeout(const WiFiPlazaLobbyInteractionState *param0)
{
    if (param0->unk_24 == 0) {
        return 1;
    }

    if (param0->unk_26 >= 900) {
        return 0;
    }

    return 1;
}

static s16 WiFiPlazaLobby_State_GetInteractionTimer(const WiFiPlazaLobbyInteractionState *param0)
{
    return param0->unk_26;
}

static void WiFiPlazaLobby_State_HandleTwoTrainerReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    u32 v2;
    WiFiPlazaLobbyNewsDuoEntry v3;

    if (param1->unk_10 != 2) {
        return;
    }

    for (v1 = 0; v1 < 2; v1++) {
        v2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[v1]);

        if (v2 != 0xffffffff) {
            v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v2);
            WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->unk_04.trainerInfos[v1], param0->heapID);
        } else {
            return;
        }
    }

    v3.unk_00 = param0->unk_04.trainerInfos[0];
    v3.unk_04 = param0->unk_04.trainerInfos[1];
    v3.unk_08 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[0]);
    v3.unk_0A = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[1]);

    WiFiPlazaLobby_News_AddDuoEntry(param0->unk_04.unk_00, &v3);
}

static void WiFiPlazaLobby_State_HandleTwoTrainerExtraReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    u32 v2;
    WiFiPlazaLobbyNewsDuoEntryRanked v3;

    if (param1->unk_10 != 2) {
        return;
    }

    for (v1 = 0; v1 < 2; v1++) {
        v2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[v1]);

        if (v2 != 0xffffffff) {
            v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v2);
            WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->unk_04.trainerInfos[v1], param0->heapID);
        } else {
            return;
        }
    }

    v3.unk_00 = param0->unk_04.trainerInfos[0];
    v3.unk_04 = param0->unk_04.trainerInfos[1];
    v3.unk_08 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[0]);
    v3.unk_0A = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[1]);
    v3.unk_0C = param1->unk_12;

    WiFiPlazaLobby_News_AddDuoEntryRanked(param0->unk_04.unk_00, &v3);
}

static void WiFiPlazaLobby_State_HandleMinigameReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    TrainerInfo *v2[4];
    u32 v3;
    WiFiPlazaLobbyNewsMinigameEntry v4;

    if ((param1->unk_10 > 4) || (param1->unk_10 <= 0)) {
        return;
    }

    if (param1->unk_13_7 == 1) {
        for (v1 = 0; v1 < 4; v1++) {
            if (v1 < param1->unk_10) {
                v3 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[v1]);

                if (v3 != 0xffffffff) {
                    v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v3);
                    WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->unk_04.trainerInfos[v1], param0->heapID);
                    v2[v1] = param0->unk_04.trainerInfos[v1];
                } else {
                    return;
                }
            } else {
                v2[v1] = NULL;
            }
        }
    } else {
        for (v1 = 0; v1 < 4; v1++) {
            if (v1 == 0) {
                u32 v5 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[v1]);

                if (v5 != 0xffffffff) {
                    v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v5);
                    WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->unk_04.trainerInfos[v1], param0->heapID);
                    v2[v1] = param0->unk_04.trainerInfos[v1];
                } else {
                    return;
                }
            } else {
                v2[v1] = NULL;
            }
        }
    }

    v4.unk_00 = param1->unk_13_0;
    v4.unk_04 = param1->unk_10;
    v4.unk_08 = v2[0];
    v4.unk_0C = v2[1];
    v4.unk_10 = v2[2];
    v4.unk_14 = v2[3];
    v4.unk_18 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[0]);
    v4.unk_1A = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[1]);
    v4.unk_1C = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[2]);
    v4.unk_1E = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[3]);
    v4.unk_20 = param1->unk_13_7;

    WiFiPlazaLobby_News_AddMinigameEntry(param0->unk_04.unk_00, &v4);
}

static void WiFiPlazaLobby_State_HandleSingleMinigameReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    u32 v2;
    WiFiPlazaLobbyNewsMinigameQuickEntry v3;

    if ((param1->unk_10 > 8) || (param1->unk_10 <= 0)) {
        return;
    }

    v2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[0]);

    if (v2 != 0xffffffff) {
        v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v2);
        WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->unk_04.trainerInfos[0], param0->heapID);
    } else {
        return;
    }

    v3.unk_00 = param1->unk_13_0;
    v3.unk_04 = param1->unk_10;
    v3.unk_08 = param0->unk_04.trainerInfos[0];
    v3.unk_0C = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[0]);

    WiFiPlazaLobby_News_AddMinigameQuickEntry(param0->unk_04.unk_00, &v3);
}

static void WiFiPlazaLobby_State_HandleFourTrainerReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    TrainerInfo *v2[4];
    u32 v3;
    WiFiPlazaLobbyNewsFourTrainerEntry v4;

    if ((param1->unk_10 > 4) || (param1->unk_10 <= 0)) {
        return;
    }

    for (v1 = 0; v1 < 4; v1++) {
        if (v1 < param1->unk_10) {
            v3 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[v1]);

            if (v3 != 0xffffffff) {
                v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v3);
                WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->unk_04.trainerInfos[v1], param0->heapID);
                v2[v1] = param0->unk_04.trainerInfos[v1];
            } else {
                return;
            }
        } else {
            v2[v1] = NULL;
        }
    }

    v4.unk_00 = param1->unk_10;
    v4.unk_04 = v2[0];
    v4.unk_08 = v2[1];
    v4.unk_0C = v2[2];
    v4.unk_10 = v2[3];
    v4.unk_14 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[0]);
    v4.unk_16 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[1]);
    v4.unk_18 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[2]);
    v4.unk_1A = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[3]);

    WiFiPlazaLobby_News_AddFourTrainerEntry(param0->unk_04.unk_00, &v4);
}

static void WiFiPlazaLobby_State_HandleFourTrainerExtraReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    TrainerInfo *v2[4];
    u32 v3;
    WiFiPlazaLobbyNewsFourTrainerEntryB v4;

    if ((param1->unk_10 > 4) || (param1->unk_10 <= 0)) {
        return;
    }

    for (v1 = 0; v1 < 4; v1++) {
        if (v1 < param1->unk_10) {
            v3 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[v1]);

            if (v3 != 0xffffffff) {
                v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v3);
                WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->unk_04.trainerInfos[v1], param0->heapID);
                v2[v1] = param0->unk_04.trainerInfos[v1];
            } else {
                return;
            }
        } else {
            v2[v1] = NULL;
        }
    }

    v4.unk_00 = param1->unk_10;
    v4.unk_04 = v2[0];
    v4.unk_08 = v2[1];
    v4.unk_0C = v2[2];
    v4.unk_10 = v2[3];
    v4.unk_14 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[0]);
    v4.unk_16 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[1]);
    v4.unk_18 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[2]);
    v4.unk_1A = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[3]);

    WiFiPlazaLobby_News_AddFourTrainerEntryB(param0->unk_04.unk_00, &v4);
}

static void WiFiPlazaLobby_State_HandleMinigameFourTrainerReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    TrainerInfo *v2[4];
    u32 v3;
    WiFiPlazaLobbyNewsMinigameResultEntry v4;

    if ((param1->unk_10 > 4) || (param1->unk_10 <= 0)) {
        return;
    }

    for (v1 = 0; v1 < 4; v1++) {
        if (v1 < param1->unk_10) {
            v3 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[v1]);

            if (v3 != 0xffffffff) {
                v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v3);
                WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->unk_04.trainerInfos[v1], param0->heapID);
                v2[v1] = param0->unk_04.trainerInfos[v1];
            } else {
                return;
            }
        } else {
            v2[v1] = NULL;
        }
    }

    v4.unk_00 = param1->unk_13_0;
    v4.unk_04 = param1->unk_10;
    v4.unk_08 = v2[0];
    v4.unk_0C = v2[1];
    v4.unk_10 = v2[2];
    v4.unk_14 = v2[3];
    v4.unk_18 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[0]);
    v4.unk_1A = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[1]);
    v4.unk_1C = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[2]);
    v4.unk_1E = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->unk_00[3]);

    WiFiPlazaLobby_News_AddMinigameResultEntry(param0->unk_04.unk_00, &v4);
}

static void WiFiPlazaLobby_State_HandleNoopReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    return;
}

static void WiFiPlazaLobby_State_PostMenuResultReport(WiFiPlazaLobbyState *param0, int param1)
{
    WiFiPlazaLobbyNewsEventEntry v0;

    v0.unk_00 = &param0->unk_04.unk_D0;
    v0.unk_04 = param1;

    WiFiPlazaLobby_News_AddEventEntry(param0->unk_04.unk_00, &v0);
}

static void WiFiPlazaLobby_State_ResetMinigameGrid(WiFiPlazaLobbyMinigameGrid *param0)
{
    memset(param0, 0, sizeof(WiFiPlazaLobbyMinigameGrid));
    MI_CpuFill32(param0->unk_50, 0xffffffff, sizeof(u32) * (9 * 3));
}

static void WiFiPlazaLobby_State_ActivateMinigameGrid(WiFiPlazaLobbyMinigameGrid *param0)
{
    param0->unk_00 = 1;
}

static void WiFiPlazaLobby_State_UpdateMinigameSchedule(WiFiPlazaLobbyMinigameGrid *param0)
{
    int v0;

    if (param0->unk_00 == 0) {
        return;
    }

    for (v0 = 0; v0 < 9; v0++) {
        if (param0->unk_04 == sMinigameGroupIds[v0]) {
            param0->unk_2C[v0] = 1;
        }

        if (param0->unk_2C[v0] == 1) {
            if ((param0->unk_08[v0] + 1) <= (40 * 30)) {
                param0->unk_08[v0]++;
            } else {
                param0->unk_2C[v0] = 2;
            }
        }
    }

    if ((param0->unk_04 + 1) <= (144 * 30)) {
        param0->unk_04++;
    }
}

static inline void WiFiPlazaLobby_State_SlotToRowCol(u32 param0, u32 *param1, u32 *param2)
{
    *param1 = param0 / 3;
    *param2 = param0 % 3;
}

static u32 WiFiPlazaLobby_State_FindFreeMinigameSlot(WiFiPlazaLobbyMinigameGrid *param0, u32 param1, int param2)
{
    u32 v0;
    int v1, v2;
    BOOL v3;
    u32 v4;

    v0 = WiFiPlazaLobby_State_FindMinigameSlot(param0, param1);

    if (v0 == 0xffffffff) {
        for (v1 = 0; v1 < 9; v1++) {
            if (WiFiPlazaLobby_State_GetMinigameGroupStatus(param0, v1) != 2) {
                for (v2 = 0; v2 < 3; v2++) {
                    v0 = (v1 * 3) + v2;
                    v3 = WiFiPlazaLobby_State_CheckMinigamePriority(param0, v0, param2);

                    if (v3 == 0) {
                        v4 = WiFiPlazaLobby_State_GetMinigameSlot(param0, v0);

                        if (v4 == 0xffffffff) {
                            param0->unk_50[v1][v2] = param1;

                            return v0;
                        }
                    }
                }
            }
        }
    }

    return 0xffffffff;
}

static void WiFiPlazaLobby_State_RemoveMinigameSlot(WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    u32 v0;
    u32 v1, v2;

    v0 = WiFiPlazaLobby_State_FindMinigameSlot(param0, param1);

    if (v0 != 0xffffffff) {
        WiFiPlazaLobby_State_SlotToRowCol(v0, &v1, &v2);
        param0->unk_50[v1][v2] = 0xffffffff;
    }
}

static u32 WiFiPlazaLobby_State_GetMinigameSlot(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    u32 v0;
    u32 v1;

    GF_ASSERT(param1 < 9 * 3);

    WiFiPlazaLobby_State_SlotToRowCol(param1, &v0, &v1);

    return param0->unk_50[v0][v1];
}

static int WiFiPlazaLobby_State_GetMinigameGroupStatus(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    GF_ASSERT(param1 < 9);
    return param0->unk_2C[param1];
}

static u32 WiFiPlazaLobby_State_GetMinigameGroupTimer(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    GF_ASSERT(param1 < 9);
    return param0->unk_08[param1];
}

static void WiFiPlazaLobby_State_SetMinigameSlotFlag(WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    u32 v0;
    u32 v1;
    u32 v2 = WiFiPlazaLobby_State_FindMinigameSlot(param0, param1);

    if (v2 != 0xffffffff) {
        WiFiPlazaLobby_State_SlotToRowCol(v2, &v0, &v1);
        param0->unk_128[v0][v1] = 1;
    }
}

static BOOL WiFiPlazaLobby_State_GetMinigameSlotFlag(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    u32 v0;
    u32 v1;

    GF_ASSERT(param1 < 9 * 3);

    WiFiPlazaLobby_State_SlotToRowCol(param1, &v0, &v1);
    return param0->unk_128[v0][v1];
}

static void WiFiPlazaLobby_State_ClearMinigameSlotFlag(WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    u32 v0;
    u32 v1;

    GF_ASSERT(param1 < 9 * 3);

    WiFiPlazaLobby_State_SlotToRowCol(param1, &v0, &v1);
    param0->unk_128[v0][v1] = 0;
}

static u32 WiFiPlazaLobby_State_FindMinigameSlot(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    int v0, v1;

    for (v0 = 0; v0 < 9; v0++) {
        for (v1 = 0; v1 < 3; v1++) {
            if (param0->unk_50[v0][v1] == param1) {
                return v0 * 3 + v1;
            }
        }
    }

    return 0xffffffff;
}

static void WiFiPlazaLobby_State_SetMinigamePriority(WiFiPlazaLobbyMinigameGrid *param0, u32 param1, int param2)
{
    u32 v0;
    u32 v1;

    GF_ASSERT(param1 < 9 * 3);

    WiFiPlazaLobby_State_SlotToRowCol(param1, &v0, &v1);
    param0->unk_BC[v0][v1] = param2 + 1;
}

static BOOL WiFiPlazaLobby_State_CheckMinigamePriority(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1, int param2)
{
    u32 v0;
    u32 v1;

    GF_ASSERT(param1 < 9 * 3);

    WiFiPlazaLobby_State_SlotToRowCol(param1, &v0, &v1);

    if (param0->unk_BC[v0][v1] <= param2) {
        return 0;
    }

    return 1;
}

static int WiFiPlazaLobby_State_GetMinigamePriority(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    u32 v0;
    u32 v1;

    GF_ASSERT(param1 < 9 * 3);

    WiFiPlazaLobby_State_SlotToRowCol(param1, &v0, &v1);

    return param0->unk_BC[v0][v1];
}

static void WiFiPlazaLobby_State_HandleInteractionResponse(s32 param0, const void *param1, u32 param2, void *param3)
{
    WiFiPlazaLobbyState *v0 = param3;
    u32 v1;
    const WiFiPlazaLobbyInteractionData *v2;
    u32 v3;
    BOOL v4;

    v2 = param1;
    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&v0->unk_108, v0->saveData) == 0) {
        v0->unk_52C = 1;
    }

    v3 = WiFiPlazaLobby_State_GetVenueIndex(&v0->unk_108.profile);
    v4 = WiFiPlazaLobby_State_IsChatActive(v0);

    if ((v3 != 1) || (v1 == 0xffffffff) || (v2->unk_02 != 1) || (v4 == 1) || (WiFiPlazaLobby_State_CanChatWithMember(v0, v1) == 0)) {
        WiFiPlazaLobby_State_SendInteractionResult(v0, param0, 0);
        return;
    }

    WiFiPlazaLobby_State_SendInteractionResult(v0, param0, 1);

    if (WiFiPlazaLobby_State_IsPlayerFlagSet(&v0->unk_1C0, v1) == 0) {
        v0->unk_1C0.unk_0B = 1;
    } else {
        v0->unk_1C0.unk_0B = 0;
    }

    v0->unk_1C0.unk_04 = v1;
    v0->unk_1C0.unk_06 = 2;
    v0->unk_1C0.unk_0A = 2;
    v0->unk_1C0.unk_07 = 0;

    WiFiPlazaLobby_State_StartInteractionTimer(&v0->unk_1C0);
}

static void WiFiPlazaLobby_State_HandleInteractionUpdate(s32 param0, const void *param1, u32 param2, void *param3)
{
    WiFiPlazaLobbyState *v0 = param3;
    u32 v1;
    const WiFiPlazaLobbyInteractionData *v2 = param1;
    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    if (v0->unk_1C0.unk_0A == 0) {
        return;
    }

    if (v0->unk_1C0.unk_04 == v1) {
        if (v2->unk_00 == 1) {
            if (WiFiPlazaLobby_State_IsPlayerFlagSet(&v0->unk_1C0, v1) == 0) {
                v0->unk_1C0.unk_0B = 1;
            } else {
                v0->unk_1C0.unk_0B = 0;
            }

            v0->unk_1C0.unk_06 = 2;
        } else {
            WiFiPlazaLobby_State_ResetInteraction(&v0->unk_1C0);
        }

        WiFiPlazaLobby_State_StopInteractionTimer(&v0->unk_1C0);
    } else {
        (void)0;
    }
}

static void WiFiPlazaLobby_State_HandleInteractionResult(s32 param0, const void *param1, u32 param2, void *param3)
{
    WiFiPlazaLobbyState *v0 = param3;
    u32 v1;
    const WiFiPlazaLobbyInteractionData *v2;

    if (v0->unk_1C0.unk_0A == 0) {
        return;
    }

    v2 = param1;
    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    if (v0->unk_1C0.unk_04 == v1) {
        if ((v2->unk_02 == 2) || (v2->unk_02 == 3)) {
            v0->unk_1C0.unk_06 = v2->unk_02;

            v0->unk_1C0.unk_08 = v2->unk_00;

            WiFiPlazaLobby_State_StopInteractionTimer(&v0->unk_1C0);
        } else {
            WiFiPlazaLobby_State_AbortInteraction(&v0->unk_1C0);
        }
    } else {
        if (v1 == 0xffffffff) {
            WiFiPlazaLobby_State_AbortInteraction(&v0->unk_1C0);
        }
    }
}

static void WiFiPlazaLobby_State_HandleInteractionEnd(s32 param0, const void *param1, u32 param2, void *param3)
{
    WiFiPlazaLobbyState *v0 = param3;
    u32 v1;

    if (v0->unk_1C0.unk_06 == 0) {
        return;
    }

    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    if (v0->unk_1C0.unk_04 == v1) {
        WiFiPlazaLobby_State_ResetInteraction(&v0->unk_1C0);
    }
}

static void WiFiPlazaLobby_State_DispatchReport(s32 param0, const void *param1, u32 param2, void *param3)
{
    WiFiPlazaLobbyState *v0 = param3;
    const WiFiPlazaLobbyProfileViewMessage *v1 = param1;

    static void (*const v2[])(WiFiPlazaLobbyState *, const WiFiPlazaLobbyProfileViewMessage *) = {
        WiFiPlazaLobby_State_HandleTwoTrainerReport,
        WiFiPlazaLobby_State_HandleTwoTrainerExtraReport,
        WiFiPlazaLobby_State_HandleMinigameReport,
        WiFiPlazaLobby_State_HandleSingleMinigameReport,
        WiFiPlazaLobby_State_HandleFourTrainerReport,
        WiFiPlazaLobby_State_HandleFourTrainerExtraReport,
        WiFiPlazaLobby_State_HandleNoopReport,
        WiFiPlazaLobby_State_HandleNoopReport,
        WiFiPlazaLobby_State_HandleMinigameFourTrainerReport
    };

    v2[v1->unk_11](v0, v1);
}

static void WiFiPlazaLobby_State_MarkPlayerFlag(s32 param0, const void *param1, u32 param2, void *param3)
{
    WiFiPlazaLobbyState *v0 = param3;
    u32 v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    if (v1 != 0xffffffff) {
        v0->unk_1E8.unk_00[v1] = 1;
    }
}

static void WiFiPlazaLobby_State_AddPlayerToMinigameGrid(s32 param0, const void *param1, u32 param2, void *param3)
{
    WiFiPlazaLobbyState *v0 = param3;
    u32 v1;
    u32 v2;
    int v3;

    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    if (v1 != 0xffffffff) {
        for (v3 = 0; v3 < 3; v3++) {
            v2 = WiFiPlazaLobby_State_FindFreeMinigameSlot(&v0->unk_20C, v1, v3);

            if (v2 != 0xffffffff) {
                break;
            }
        }
    }
}

static void WiFiPlazaLobby_State_MarkMinigameSlotFlag(s32 param0, const void *param1, u32 param2, void *param3)
{
    WiFiPlazaLobbyState *v0 = param3;
    u32 v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    if (v1 != 0xffffffff) {
        WiFiPlazaLobby_State_SetMinigameSlotFlag(&v0->unk_20C, v1);
    }
}

static void WiFiPlazaLobby_State_ResetMinigameWeights(WiFiPlazaLobbyMinigameWeights *param0)
{
    int v0;

    memset(param0, 0, sizeof(WiFiPlazaLobbyMinigameWeights));

    for (v0 = 0; v0 < (27 / 3); v0++) {
        param0->unk_00[v0] = 100;
    }
}

static void WiFiPlazaLobby_State_ReduceMinigameWeight(WiFiPlazaLobbyMinigameWeights *param0, u32 param1, u32 param2)
{
    u32 v0;
    int v1;

    GF_ASSERT(param2 < 20);
    GF_ASSERT(param1 < 27);

    if (param0->unk_0C[param2] == 0) {
        v0 = param1 / 3;
        param0->unk_00[v0] /= 2;
        param0->unk_0C[param2] = 1;
    }
}

static u32 WiFiPlazaLobby_State_ChooseWeightedMinigameGroup(const WiFiPlazaLobbyMinigameWeights *param0)
{
    int v0;
    u32 v1;
    u32 v2;
    u32 v3;

    v1 = 0;

    for (v0 = 0; v0 < (27 / 3); v0++) {
        v1 += param0->unk_00[v0];
    }

    v3 = MTRNG_Next() % v1;
    v2 = 0;

    for (v0 = 0; v0 < (27 / 3); v0++) {
        if ((v2 <= v3) && ((v2 + param0->unk_00[v0]) > v3)) {
            return v0 * 3;
        }

        v2 += param0->unk_00[v0];
    }

    GF_ASSERT(FALSE);
    return 0;
}

static void WiFiPlazaLobby_State_SetPendingNewsPlayerFlag(WiFiPlazaLobbyNewsPlayerFlags *param0, u32 param1, BOOL param2)
{
    GF_ASSERT(param1 < 20);

    if (param1 < 20) {
        param0->unk_00[param1] = param2;
    }
}

static BOOL WiFiPlazaLobby_State_GetPendingNewsPlayerFlag(const WiFiPlazaLobbyNewsPlayerFlags *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param1 < 20) {
        return param0->unk_00[param1];
    }

    return 0;
}

static void WiFiPlazaLobby_State_InitPasswordState(WiFiPlazaLobbyPasswordState *param0, u32 param1)
{
    MI_CpuClear8(param0, sizeof(WiFiPlazaLobbyPasswordState));
    param0->unk_B4 = PasswordWordBank_New(param1);
}

static void WiFiPlazaLobby_State_FreePasswordState(WiFiPlazaLobbyPasswordState *param0)
{
    PasswordWordBank_Free(param0->unk_B4);
}

static void WiFiPlazaLobby_State_SetPasswordEntry(WiFiPlazaLobbyPasswordState *param0, u32 param1, BOOL param2, u32 param3)
{
    GF_ASSERT(param1 < 20);

    if (param1 < 20) {
        param0->unk_00[param1] = param2;

        if (param2 == 1) {
            WiFiPlazaLobby_State_GeneratePasswordWords(param0->unk_B4, param3, &param0->unk_14[param1]);
        }
    }
}

static BOOL WiFiPlazaLobby_State_GetPasswordEntryFlag(const WiFiPlazaLobbyPasswordState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param1 < 20) {
        return param0->unk_00[param1];
    }

    return 0;
}

static const WiFiPlazaLobbyPasswordWords *WiFiPlazaLobby_State_GetPasswordEntry(const WiFiPlazaLobbyPasswordState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param1 < 20) {
        if (param0->unk_00[param1]) {
            return &param0->unk_14[param1];
        }
    }

    return NULL;
}

static void WiFiPlazaLobby_State_GeneratePasswordWords(PasswordWordBank *param0, u32 param1, WiFiPlazaLobbyPasswordWords *param2)
{
    WiFiPlazaLobbyPasswordSeed v0;
    u32 v1;
    u32 v2;

    v1 = PasswordWordBank_GetLength(param0);

    v0.val1 = param1;

    v2 = (v0.val2[3] + v0.val2[0]) % v1;
    param2->unk_00[0] = PasswordWordBank_GetWordAtIndex(param0, v2);

    v2 = (v0.val2[0] + v0.val2[1]) % v1;
    param2->unk_00[1] = PasswordWordBank_GetWordAtIndex(param0, v2);

    v2 = (v0.val2[1] + v0.val2[2]) % v1;
    param2->unk_00[2] = PasswordWordBank_GetWordAtIndex(param0, v2);

    v2 = (v0.val2[2] + v0.val2[3]) % v1;
    param2->unk_00[3] = PasswordWordBank_GetWordAtIndex(param0, v2);
}

static void WiFiPlazaLobby_State_InitEventTimer(WiFiPlazaLobbyEventTimer *param0, u32 param1, u32 param2)
{
    param0->unk_00 = 0;
    param0->unk_0C = 0;
    param0->unk_10 = (param2 - param1) * 30;
}

static void WiFiPlazaLobby_State_StartEventTimer(WiFiPlazaLobbyEventTimer *param0)
{
    param0->unk_00 = 1;
    param0->unk_0C = 0;

    WiFiPlazaLobby_Network_GetCurrentTime(&param0->unk_04);
}

static void WiFiPlazaLobby_State_UpdateEventTimer(WiFiPlazaLobbyEventTimer *param0)
{
    s64 v0;
    s64 v1;

    if (param0->unk_00) {
        WiFiPlazaLobby_Network_GetCurrentTime(&v0);
        v1 = v0 - param0->unk_04;

        if (param0->unk_0C < (v1 * 30)) {
            param0->unk_0C = (v1 * 30);
        }

        if (param0->unk_0C < param0->unk_10) {
            param0->unk_0C++;

            {
                u32 v2;
                u32 v3;
                int v4;

                v2 = (param0->unk_0C * 256) / param0->unk_10;
                v3 = 0;

                for (v4 = 0; v4 < NELEMS(sEventTimerStages); v4++) {
                    v3 += sEventTimerStages[v4].unk_02;

                    if (v3 >= v2) {
                        if (param0->unk_14 != sEventTimerStages[v4].unk_00) {
                            param0->unk_14 = sEventTimerStages[v4].unk_00;
                            param0->unk_18 = 0;
                        }

                        break;
                    }
                }
            }
        } else {
            if (param0->unk_14 != 5) {
                param0->unk_14 = 5;
                param0->unk_18 = 0;
            }

            if (param0->unk_18 >= 120) {
                param0->unk_14 = 0;
                param0->unk_00 = 0;
            }
        }

        param0->unk_18++;
    }
}

static u32 WiFiPlazaLobby_State_GetEventTimerCounter(const WiFiPlazaLobbyEventTimer *param0)
{
    return param0->unk_18;
}

static int WiFiPlazaLobby_State_GetEventTimerStage(const WiFiPlazaLobbyEventTimer *param0)
{
    return param0->unk_14;
}

static void WiFiPlazaLobby_State_InitRecentPlayers(WiFiPlazaLobbyRecentPlayers *param0, const SaveData *saveData)
{
    int v0;

    for (v0 = 0; v0 < (12 + 1); v0++) {
        param0->unk_34[v0] = 24;
        param0->unk_00[v0] = DWC_LOBBY_INVALID_USER_ID;
    }

    param0->unk_41 = 0;
    param0->unk_42 = 0;
    param0->saveData = saveData;

    WiFiPlazaLobby_State_UpdateRecentPlayersChecksum(param0);
}

static void WiFiPlazaLobby_State_PushRecentPlayer(WiFiPlazaLobbyRecentPlayers *param0, int param1, s32 param2)
{
    WiFiPlazaLobby_State_ValidateRecentPlayersChecksum(param0);

    if (((param0->unk_42 + 1) % (12 + 1)) == param0->unk_41) {
        WiFiPlazaLobby_State_PopRecentPlayer(param0);
    }

    param0->unk_34[param0->unk_42] = param1;
    param0->unk_00[param0->unk_42] = param2;
    param0->unk_42 = (param0->unk_42 + 1) % (12 + 1);

    WiFiPlazaLobby_State_UpdateRecentPlayersChecksum(param0);
}

static BOOL WiFiPlazaLobby_State_ReplaceRecentPlayer(WiFiPlazaLobbyRecentPlayers *param0, s32 param1, s32 param2)
{
    int v0;
    BOOL v1 = 0;

    WiFiPlazaLobby_State_ValidateRecentPlayersChecksum(param0);

    for (v0 = 0; v0 < (12 + 1); v0++) {
        if (param0->unk_00[v0] == param1) {
            param0->unk_00[v0] = param2;
            v1 = 1;
        }
    }

    WiFiPlazaLobby_State_UpdateRecentPlayersChecksum(param0);

    return v1;
}

static int WiFiPlazaLobby_State_PopRecentPlayer(WiFiPlazaLobbyRecentPlayers *param0)
{
    u8 v0;

    WiFiPlazaLobby_State_ValidateRecentPlayersChecksum(param0);

    if (param0->unk_42 == param0->unk_41) {
        return 24;
    }

    v0 = param0->unk_34[param0->unk_41];

    param0->unk_34[param0->unk_41] = 24;
    param0->unk_00[param0->unk_42] = DWC_LOBBY_INVALID_USER_ID;
    param0->unk_41 = (param0->unk_41 + 1) % (12 + 1);

    WiFiPlazaLobby_State_UpdateRecentPlayersChecksum(param0);

    return v0;
}

static int WiFiPlazaLobby_State_GetRecentPlayerAppearance(WiFiPlazaLobbyRecentPlayers *param0, u32 param1)
{
    s32 v0;

    GF_ASSERT(param1 < 12);

    WiFiPlazaLobby_State_ValidateRecentPlayersChecksum(param0);

    param1++;
    v0 = param0->unk_42 - param1;

    if (v0 < 0) {
        v0 += (12 + 1);
    }

    return param0->unk_34[v0];
}

static s32 WiFiPlazaLobby_State_GetRecentPlayerID(WiFiPlazaLobbyRecentPlayers *param0, u32 param1)
{
    s32 v0;

    GF_ASSERT(param1 < 12);

    WiFiPlazaLobby_State_ValidateRecentPlayersChecksum(param0);

    param1++;
    v0 = param0->unk_42 - param1;

    if (v0 < 0) {
        v0 += (12 + 1);
    }

    return param0->unk_00[v0];
}

static void WiFiPlazaLobby_State_UpdateRecentPlayersChecksum(WiFiPlazaLobbyRecentPlayers *param0)
{
    param0->unk_48 = SaveData_CalculateChecksum(param0->saveData, param0, (sizeof(WiFiPlazaLobbyRecentPlayers) - 8));
}

static void WiFiPlazaLobby_State_ValidateRecentPlayersChecksum(WiFiPlazaLobbyRecentPlayers *param0)
{
    u32 v0 = SaveData_CalculateChecksum(param0->saveData, param0, (sizeof(WiFiPlazaLobbyRecentPlayers) - 8));

    if (v0 != param0->unk_48) {
        GF_ASSERT(FALSE);
        param0->unk_4A = 1;
    }
}

static BOOL WiFiPlazaLobby_State_HasRecentPlayersChecksumError(const WiFiPlazaLobbyRecentPlayers *param0)
{
    return param0->unk_4A;
}

static u32 WiFiPlazaLobby_State_FindTrainerAppearanceIndex(u32 param0)
{
    int idx;

    for (idx = 0; idx < 16; idx++) {
        if (sWiFiPlazaTrainerAppearances[idx].graphicsID == param0) {
            return idx;
        }
    }

    return 16;
}

static u32 GetTrainerAppearanceGraphicsID(u32 trainerAppearance)
{
    if (trainerAppearance < SNELEMS(sWiFiPlazaTrainerAppearances)) {
        return sWiFiPlazaTrainerAppearances[trainerAppearance].graphicsID;
    }

    return 0xffff;
}
