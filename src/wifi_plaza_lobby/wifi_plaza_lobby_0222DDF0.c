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
    u16 localTrainerName[8];
    u16 receivedTrainerName[8];
    WiFiPlazaProfile profile;
    u32 profileChecksum;
} WiFiPlazaLobbyProfileCache;

typedef struct {
    u8 activityDone[8];
} WiFiPlazaLobbyStateTempBuffer;

typedef struct {
    BOOL active;
    s32 elapsedTime;
    s32 groupTimers[9];
    u32 groupStatus[9];
    u32 slotUserIDs[9][3];
    u32 slotPriorities[9][3];
    BOOL slotFlags[9][3];
} WiFiPlazaLobbyMinigameGrid;

typedef struct {
    BOOL active;
    s64 startTime;
    s32 elapsedFrames;
    s32 maxFrames;
    u32 stage;
    u32 stageFrames;
} WiFiPlazaLobbyEventTimer;

typedef struct {
    u32 playerJoined;
    u32 playerLeft;
    u32 timeEvents;
    u32 playerUpdated;
} WiFiPlazaLobbyEventFlags;

typedef struct {
    u8 locked : 1;
    u8 closing : 1;
    u8 fireworksState : 2;
    u8 paradeActive : 1;
    u8 minigameEnded : 2;
    u8 closed : 1;
    u8 neonATimeEvent;
    u8 neonBTimeEvent;
    u8 neonCTimeEvent;
    s16 closeTimer;
    s16 neonTimer;
    s16 fireworksTimer;
    s16 paradeTimer;
    u8 bgmSuppressed;
    u8 bgmVolumeDucked;
    u8 bgmFadeStarted;
    u8 questionAnswered : 4;
    u8 questionAcknowledged : 4;
} WiFiPlazaLobbyEventTimers;

typedef struct {
    WiFiPlazaLobbyNews *news;
    BOOL neonTransitionActive;
    WiFiPlazaLobbyPlaceList placeList;
    WiFiPlazaLobbyTime currentTime;
    s64 currentTimeSeconds;
    s64 lockTime;
    TrainerInfo *trainerInfos[4];
} WiFiPlazaLobbyStatePlayers;

typedef struct {
    u16 value;
    u16 event;
} WiFiPlazaLobbyInteractionData;

typedef struct {
    u32 chattedBitmap;
    u16 partnerSlot;
    u8 state;
    u8 pending;
    u16 response;
    u8 phase;
    u8 chattedWithCurrent;
    u8 chatCounts[20];
    WiFiPlazaLobbyInteractionData data;
    u16 timerActive;
    s16 timer;
} WiFiPlazaLobbyInteractionState;

typedef struct {
    u8 cosmeticKnown[20];
} WiFiPlazaLobbyPlayerFlags;

typedef struct {
    s16 time;
    u8 expired;
} WiFiPlazaLobbyTimer;

typedef struct {
    u8 groupWeights[9];
    u8 reserved[3];
    u8 playerReduced[20];
} WiFiPlazaLobbyMinigameWeights;

typedef struct {
    u8 hasPassword[20];
    WiFiPlazaLobbyPasswordWords passwords[20];
    PasswordWordBank *wordBank;
} WiFiPlazaLobbyPasswordState;

typedef union {
    u32 val1;
    u8 val2[4];
} WiFiPlazaLobbyPasswordSeed;

typedef struct {
    s32 userIDs[13];
    u8 appearances[13];
    u8 head;
    u8 tail;
    u8 unk_43;
    const SaveData *saveData;
    u16 checksum;
    u16 checksumError;
} WiFiPlazaLobbyRecentPlayers;

typedef struct {
    TrainerInfo *trainerInfo;
    BOOL valid;
} WiFiPlazaLobbyTrainerInfoHolder;

typedef struct {
    WiFiLobbyQuestionnaireAnswerTally result;
    BOOL hasResult;
} WiFiPlazaLobbyStateQuestionnaire;

typedef struct WiFiPlazaLobbyState_t {
    SaveData *saveData;
    WiFiPlazaLobbyStatePlayers players;
    WiFiPlazaLobbyEventFlags eventFlags;
    WiFiPlazaLobbyProfileCache profileCache;
    WiFiPlazaLobbyInteractionState interaction;
    WiFiPlazaLobbyPlayerFlags playerFlags;
    WiFiPlazaLobbyEventTimers eventTimers;
    WiFiPlazaLobbyMinigameGrid minigameGrid;
    WiFiPlazaLobbyTimer warpTimer;
    WiFiPlazaLobbyStateTempBuffer activityFlags;
    WiFiPlazaLobbyMinigameWeights minigameWeights;
    WiFiPlazaLobbyNewsPlayerFlags newsPlayerFlags;
    WiFiPlazaLobbyQuestionnaireData userIDTable;
    WiFiPlazaLobbyPasswordState passwordState;
    WiFiPlazaLobbyEventTimer eventTimer;
    WFCTrainerInfo *wfcTrainerInfo;
    WiFiPlazaLobbyRecentPlayers recentPlayers;
    WiFiPlazaLobbyTrainerInfoHolder trainerInfoHolder;
    WiFiPlazaLobbyStateQuestionnaire questionnaire;
    enum HeapID heapID;
    u32 errorFlag;
} WiFiPlazaLobbyState;

typedef struct WiFiPlazaTrainerAppearance {
    u16 graphicsID;
    u16 gender;
} WiFiPlazaTrainerAppearance;

typedef struct {
    u16 stage;
    u16 threshold;
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

        v1.onPlayerConnected = WiFiPlazaLobby_State_HandleMemberJoined;
        v1.onPlayerDisconnected = WiFiPlazaLobby_State_HandleMemberLeft;
        v1.onPlayerProfile = WiFiPlazaLobby_State_HandleMemberUpdated;
        v1.onTimeEvent = WiFiPlazaLobby_State_HandleLobbyTimeEvent;
        v1.onStats = WiFiPlazaLobby_State_HandleMemberProfileReceived;

        WiFiPlazaLobby_Network_New(heapID, v0->saveData, sizeof(WiFiPlazaProfile), &v1, v0);
    }

    {
        int v2;

        v0->players.news = WiFiPlazaLobby_News_New(heapID);

        for (v2 = 0; v2 < 4; v2++) {
            v0->players.trainerInfos[v2] = TrainerInfo_New(heapID);
        }
    }

    WiFiPlazaLobby_State_BuildLocalProfile(&v0->profileCache, v0->saveData, heapID);
    WiFiPlazaLobby_State_ResetInteractionState(&v0->interaction);
    WiFiPlazaLobby_State_ClearPlayerFlags(&v0->playerFlags);
    WiFiPlazaLobby_Network_SetMainMessageHandler(sMainMessageHandlers, 8, v0);
    WiFiPlazaLobby_State_InitEventState(&v0->eventTimers);
    WiFiPlazaLobby_State_ResetMinigameGrid(&v0->minigameGrid);
    WiFiPlazaLobby_State_ResetMinigameWeights(&v0->minigameWeights);
    WiFiPlazaLobby_State_InitPasswordState(&v0->passwordState, heapID);
    WiFiPlazaLobby_State_InitRecentPlayers(&v0->recentPlayers, v0->saveData);
    WiFiPlazaLobby_State_CreateTrainerInfo(&v0->trainerInfoHolder, heapID);

    return v0;
}

void WiFiPlazaLobby_State_Destroy(WiFiPlazaLobbyState *param0)
{
    {
        WiFiPlazaQuestion *wiFiPlazaQuestion;
        WiFiPlazaLobbyQuestionnaireAnswer v1;

        WiFiPlazaLobby_State_GetQuestionnaireAnswer(&param0->profileCache.profile, &v1);

        wiFiPlazaQuestion = SaveData_GetWiFiPlazaQuestion(param0->saveData);

        WiFiPlazaQuestion_SetQuestionNumber(wiFiPlazaQuestion, v1.questionNumber);
        WiFiPlazaQuestion_SetSelectedAnswer(wiFiPlazaQuestion, v1.selectedAnswer);
    }

    WiFiPlazaLobby_State_FreeTrainerInfo(&param0->trainerInfoHolder);
    WiFiPlazaLobby_State_FreePasswordState(&param0->passwordState);

    {
        WiFiPlazaLobby_Network_ClearMainMessageHandler();
    }

    {
        int v2;

        WiFiPlazaLobby_News_Free(param0->players.news);

        for (v2 = 0; v2 < 4; v2++) {
            Heap_Free(param0->players.trainerInfos[v2]);
        }
    }

    WiFiPlazaLobby_Network_Free();
    Heap_Free(param0);
}

void WiFiPlazaLobby_State_Init(WiFiPlazaLobbyState *param0)
{
    WiFiPlazaLobby_News_Reset(param0->players.news);

    {
        s64 v0;

        WiFiPlazaLobby_Network_GetCurrentTime(&v0);
        param0->players.currentTimeSeconds = v0;
        WiFiPlazaLobby_Time_SetFromSeconds(&param0->players.currentTime, &v0);
    }

    {
        WiFiPlazaLobby_State_CheckEventTimeout(param0);
    }

    {
        WiFiPlazaLobby_State_UpdateInteractionTimer(&param0->interaction);
    }

    WiFiPlazaLobby_State_ClearPlayerFlags(&param0->playerFlags);
    WiFiPlazaLobby_State_ResetEventFlags(&param0->eventFlags);
    WiFiPlazaLobby_State_UpdateEventTimers(&param0->eventTimers, &param0->eventFlags, &param0->minigameGrid, &param0->eventTimer);
    WiFiPlazaLobby_State_TickTimer(&param0->warpTimer);
    WiFiPlazaLobby_State_UpdateMinigameSchedule(&param0->minigameGrid);
    WiFiPlazaLobby_State_UpdateEventTimer(&param0->eventTimer);

    {
        BOOL v1;

        v1 = WiFiPlazaLobby_State_HasRecentPlayersChecksumError(&param0->recentPlayers);

        if (v1 == 1) {
            param0->errorFlag = 1;
        }
    }
}

void WiFiPlazaLobby_State_UpdateNoop(WiFiPlazaLobbyState *param0)
{
    return;
}

int WiFiPlazaLobby_State_GetErrorFlag(const WiFiPlazaLobbyState *param0)
{
    return param0->errorFlag;
}

BOOL WiFiPlazaLobby_State_CheckNetworkEvent(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_Network_ConsumeExcessFlood();
}

WiFiPlazaLobbyNews *WiFiPlazaLobby_State_GetNewsManager(WiFiPlazaLobbyState *param0)
{
    return param0->players.news;
}

const WiFiPlazaLobbyPlaceList *WiFiPlazaLobby_State_GetPlayerCountryTable(WiFiPlazaLobbyState *param0)
{
    WiFiPlazaLobby_State_BuildMemberLocationList(&param0->profileCache, &param0->players.placeList);

    return &param0->players.placeList;
}

const WiFiPlazaLobbyTime *WiFiPlazaLobby_State_GetCurrentTime(const WiFiPlazaLobbyState *param0)
{
    return &param0->players.currentTime;
}

BOOL WiFiPlazaLobby_State_PopPlayerJoined(WiFiPlazaLobbyState *param0, u32 param1)
{
    if (param0->eventFlags.playerJoined & (1 << param1)) {
        param0->eventFlags.playerJoined &= ~(1 << param1);
        return 1;
    }

    return 0;
}

BOOL WiFiPlazaLobby_State_PopPlayerLeft(WiFiPlazaLobbyState *param0, u32 param1)
{
    if (param0->eventFlags.playerLeft & (1 << param1)) {
        param0->eventFlags.playerLeft &= ~(1 << param1);
        return 1;
    }

    return 0;
}

BOOL WiFiPlazaLobby_State_CheckTimeEventFlag(WiFiPlazaLobbyState *param0, int param1)
{
    if (param0->eventFlags.timeEvents & (1 << param1)) {
        return 1;
    }

    return 0;
}

BOOL WiFiPlazaLobby_State_PopPlayerUpdated(WiFiPlazaLobbyState *param0, u32 param1)
{
    if (param0->eventFlags.playerUpdated & (1 << param1)) {
        param0->eventFlags.playerUpdated &= ~(1 << param1);
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

    return param0->eventTimers.questionAnswered;
}

BOOL WiFiPlazaLobby_State_IsQuestionAcknowledged(const WiFiPlazaLobbyState *param0)
{
    GF_ASSERT(param0);
    return param0->eventTimers.questionAcknowledged;
}

void WiFiPlazaLobby_State_MarkQuestionAcknowledged(WiFiPlazaLobbyState *param0)
{
    param0->eventTimers.questionAcknowledged = 1;
}

BOOL WiFiPlazaLobby_State_IsLobbyLocked(const WiFiPlazaLobbyState *param0)
{
    return param0->eventTimers.locked;
}

BOOL WiFiPlazaLobby_State_IsLobbyClosed(const WiFiPlazaLobbyState *param0)
{
    return param0->eventTimers.closed;
}

BOOL WiFiPlazaLobby_State_IsLobbyCloseFinished(const WiFiPlazaLobbyState *param0)
{
    if ((param0->eventTimers.closing == 1) && (param0->eventTimers.closeTimer <= 0)) {
        return 1;
    } else {
        return 0;
    }
}

int WiFiPlazaLobby_State_GetFireworksState(const WiFiPlazaLobbyState *param0)
{
    if (param0->eventTimers.fireworksTimer <= 0) {
        return param0->eventTimers.fireworksState;
    }

    return 0;
}

BOOL WiFiPlazaLobby_State_IsParadeFinished(const WiFiPlazaLobbyState *param0)
{
    if ((param0->eventTimers.paradeActive == 1) && (param0->eventTimers.paradeTimer <= 0)) {
        return 1;
    }

    return 0;
}

BOOL WiFiPlazaLobby_State_IsMinigameFinished(const WiFiPlazaLobbyState *param0)
{
    return param0->eventTimers.minigameEnded;
}

BOOL WiFiPlazaLobby_State_IsNeonTransitionComplete(const WiFiPlazaLobbyState *param0)
{
    if ((param0->players.neonTransitionActive == 1) && (param0->eventTimers.neonTimer <= 0)) {
        return 1;
    }

    return 0;
}

PPW_LOBBY_TIME_EVENT WiFiPlazaLobby_State_GetNeonATimeEvent(const WiFiPlazaLobbyState *param0)
{
    if (param0->eventTimers.neonTimer <= 0) {
        return param0->eventTimers.neonATimeEvent;
    }

    return PPW_LOBBY_TIME_EVENT_NEON_A0;
}

PPW_LOBBY_TIME_EVENT WiFiPlazaLobby_State_GetNeonBTimeEvent(const WiFiPlazaLobbyState *param0)
{
    if (param0->eventTimers.neonTimer <= 0) {
        return param0->eventTimers.neonBTimeEvent;
    }

    return PPW_LOBBY_TIME_EVENT_NEON_B0;
}

PPW_LOBBY_TIME_EVENT WiFiPlazaLobby_State_GetNeonCTimeEvent(const WiFiPlazaLobbyState *param0)
{
    if (param0->eventTimers.neonTimer <= 0) {
        return param0->eventTimers.neonCTimeEvent;
    }

    return PPW_LOBBY_TIME_EVENT_NEON_C0;
}

void WiFiPlazaLobby_State_StartWarpTimer(WiFiPlazaLobbyState *param0)
{
    WiFiPlazaLobby_State_ResetTimer(&param0->warpTimer);
}

BOOL WiFiPlazaLobby_State_IsWarpTimerActive(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_State_IsTimerActive(&param0->warpTimer);
}

BOOL WiFiPlazaLobby_State_IsTrainerInfoValid(const WiFiPlazaLobbyState *param0)
{
    return param0->trainerInfoHolder.valid;
}

void WiFiPlazaLobby_State_SetTrainerInfoValid(WiFiPlazaLobbyState *param0, BOOL param1)
{
    param0->trainerInfoHolder.valid = param1;
}

void WiFiPlazaLobby_State_ClearUserIDTable(WiFiPlazaLobbyState *param0)
{
    MI_CpuClear32(&param0->userIDTable, sizeof(WiFiPlazaLobbyQuestionnaireData));
}

void WiFiPlazaLobby_State_SetPlayerSlotUserID(WiFiPlazaLobbyState *param0, s32 param1, u32 param2)
{
    u32 v0;

    GF_ASSERT(param2 < 4);
    v0 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1);
    GF_ASSERT(v0 != 0xffffffff);

    param0->userIDTable.playerIndices[param2] = v0;
}

void WiFiPlazaLobby_State_SetMyPlayerSlot(WiFiPlazaLobbyState *param0, u32 param1)
{
    s32 v0 = WiFiPlazaLobby_Network_GetMyUserId();
    WiFiPlazaLobby_State_SetPlayerSlotUserID(param0, v0, param1);
}

void WiFiPlazaLobby_State_GetUserIDTable(const WiFiPlazaLobbyState *param0, WiFiPlazaLobbyQuestionnaireData *param1)
{
    MI_CpuCopy8(&param0->userIDTable, param1, sizeof(WiFiPlazaLobbyQuestionnaireData));
}

void WiFiPlazaLobby_State_SetPlayerWarpPending(WiFiPlazaLobbyState *param0)
{
    WiFiPlazaLobby_State_SetTimerExpired(&param0->warpTimer);
}

BOOL WiFiPlazaLobby_State_IsPlayerWarpPending(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_State_IsTimerExpired(&param0->warpTimer);
}

void WiFiPlazaLobby_State_SetBGMSuppressed(WiFiPlazaLobbyState *param0, BOOL param1)
{
    param0->eventTimers.bgmSuppressed = param1;
}

void WiFiPlazaLobby_State_PlayLobbyBGM(const WiFiPlazaLobbyState *param0)
{
    if ((param0->eventTimers.paradeActive == 1) && (param0->eventTimers.paradeTimer <= 0)) {
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_21, SEQ_PL_WIFIPARADE_sseq, 0);
        WiFiPlazaLobby_State_UpdateMusicVolume(&param0->eventTimers);
    } else {
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_21, SEQ_PL_WIFIUNION_sseq, 0);
        WiFiPlazaLobby_State_UpdateMusicVolume(&param0->eventTimers);
    }
}

void WiFiPlazaLobby_State_SetBGMVolumeDucked(WiFiPlazaLobbyState *param0, BOOL param1)
{
    if (param1 != param0->eventTimers.bgmVolumeDucked) {
        param0->eventTimers.bgmVolumeDucked = param1;
        WiFiPlazaLobby_State_UpdateMusicVolume(&param0->eventTimers);
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

    if (v0.userIDs[param1] != DWC_LOBBY_INVALID_USER_ID) {
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

    v0 = v1.userIDs[param1];

    if (v0 == DWC_LOBBY_INVALID_USER_ID) {
        return NULL;
    }

    if (v0 == WiFiPlazaLobby_Network_GetMyUserId()) {
        v2 = &param0->profileCache.profile;
    } else {
        v2 = (const WiFiPlazaProfile *)WiFiPlazaLobby_Network_GetPlayerData(v0);
    }

    return v2;
}

WiFiPlazaProfile *WiFiPlazaLobby_State_GetOwnProfile(WiFiPlazaLobbyState *param0)
{
    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&param0->profileCache, param0->saveData) == 0) {
        param0->errorFlag = 1;
    }

    return &param0->profileCache.profile;
}

void WiFiPlazaLobby_State_SetCurrentVenue(WiFiPlazaLobbyState *param0, int param1)
{
    s32 v0;

    GF_ASSERT(param1 < 15);

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&param0->profileCache, param0->saveData) == 0) {
        param0->errorFlag = 1;
        return;
    }

    if (param0->profileCache.profile.venue == param1) {
        return;
    }

    if (param1 != 9) {
        if (WiFiPlazaLobby_State_IsChatActive(param0) == 1) {
            if (WiFiPlazaLobby_State_IsChatRequested(param0) == 0) {
                v0 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param0->interaction.partnerSlot);
                WiFiPlazaLobby_State_SendInteractionCancel(param0, param0->interaction.partnerSlot);
            }

            WiFiPlazaLobby_State_AbortInteraction(&param0->interaction);
        }
    }

    switch (param0->profileCache.profile.venue) {
    case 2:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->recentPlayers, 16, DWC_LOBBY_INVALID_USER_ID);
        break;
    case 3:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->recentPlayers, 17, DWC_LOBBY_INVALID_USER_ID);
        break;
    case 4:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->recentPlayers, 18, DWC_LOBBY_INVALID_USER_ID);
        break;
    case 5:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->recentPlayers, 19, DWC_LOBBY_INVALID_USER_ID);
        break;
    case 6:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->recentPlayers, 20, DWC_LOBBY_INVALID_USER_ID);
        break;
    case 7:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->recentPlayers, 21, DWC_LOBBY_INVALID_USER_ID);
        break;
    case 8:
        WiFiPlazaLobby_State_PushRecentPlayer(&param0->recentPlayers, 22, DWC_LOBBY_INVALID_USER_ID);
        break;

    default:
        break;
    }

    param0->profileCache.profile.venue = param1;

    WiFiPlazaLobby_State_UpdateProfileChecksum(&param0->profileCache, param0->saveData);
    WiFiPlazaLobby_State_LoadCachedProfile(param0);
}

void WiFiPlazaLobby_State_SetAttendee(WiFiPlazaLobbyState *param0, int param1, s32 param2)
{
    GF_ASSERT(param1 < 24);

    WiFiPlazaLobby_State_PushRecentPlayer(&param0->recentPlayers, param1, param2);
    WiFiPlazaLobby_State_LoadCachedProfile(param0);
}

void WiFiPlazaLobby_State_SetAppearanceRank(WiFiPlazaLobbyState *param0, u32 param1)
{
    GF_ASSERT(param1 < 27);

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&param0->profileCache, param0->saveData) == 0) {
        param0->errorFlag = 1;
        return;
    }

    param0->profileCache.profile.appearanceRank = param1;

    WiFiPlazaLobby_State_UpdateProfileChecksum(&param0->profileCache, param0->saveData);
    WiFiPlazaLobby_State_LoadCachedProfile(param0);
}

void WiFiPlazaLobby_State_SetPokemonTypes(WiFiPlazaLobbyState *param0, int type1, int type2)
{
    GF_ASSERT(type1 < NUM_POKEMON_TYPES);
    GF_ASSERT(type2 < NUM_POKEMON_TYPES);

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&param0->profileCache, param0->saveData) == 0) {
        param0->errorFlag = 1;
        return;
    }

    if (type1 >= NUM_POKEMON_TYPES) {
        return;
    }

    if (type2 >= NUM_POKEMON_TYPES) {
        return;
    }

    if (type1 == TYPE_NORMAL) {
        param0->profileCache.profile.pokemonTypes[0] = type2;
        param0->profileCache.profile.pokemonTypes[1] = TYPE_NORMAL;
    } else {
        param0->profileCache.profile.pokemonTypes[0] = type1;
        param0->profileCache.profile.pokemonTypes[1] = type2;
    }

    WiFiPlazaLobby_State_UpdateProfileChecksum(&param0->profileCache, param0->saveData);
    WiFiPlazaLobby_State_LoadCachedProfile(param0);
}

void WiFiPlazaLobby_State_SetQuestionnaireAnswer(WiFiPlazaLobbyState *param0, u32 param1, u32 param2)
{
    GF_ASSERT(param2 < 3);

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&param0->profileCache, param0->saveData) == 0) {
        param0->errorFlag = 1;
        return;
    }

    if (param2 >= 3) {
        return;
    }

    param0->profileCache.profile.questionnaireAnswer.questionNumber = param1;
    param0->profileCache.profile.questionnaireAnswer.selectedAnswer = param2;
    param0->eventTimers.questionAnswered = 1;

    WiFiPlazaLobby_State_MarkActivityDone(param0, 6);
    WiFiPlazaLobby_State_UpdateProfileChecksum(&param0->profileCache, param0->saveData);
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
    if (profile->venue >= 14) {
        return 14;
    }

    return profile->venue;
}

int WiFiPlazaLobby_State_GetNthActiveSlot(const WiFiPlazaProfile *profile, u32 param1)
{
    int idx;
    int v1;

    GF_ASSERT(param1 < 12);

    v1 = 0;

    for (idx = 0; idx < 12; idx++) {
        if (profile->recentAppearances[idx] < 24) {
            v1++;
        }

        if ((v1 - 1) == param1) {
            return profile->recentAppearances[idx];
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
        if (profile->recentAppearances[idx] < 24) {
            v1++;
        }

        if ((v1 - 1) == param1) {
            return profile->recentUserIDs[idx];
        }
    }

    return DWC_LOBBY_INVALID_USER_ID;
}

s32 WiFiPlazaLobby_State_GetProfileUserId(const WiFiPlazaProfile *profile)
{
    return profile->userId;
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
    return profile->localTime;
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

    if (profile->appearanceRank == 0xff) {
        return 0;
    }

    if (profile->appearanceRank >= 27) {
        v0 = 0;
    } else {
        v0 = profile->appearanceRank;
    }

    return v0;
}

BOOL WiFiPlazaLobby_State_IsAppearanceRankSet(const WiFiPlazaProfile *profile)
{
    if (profile->appearanceRank == 0xff) {
        return 0;
    }

    return 1;
}

int WiFiPlazaLobby_State_GetProfilePokemonType(const WiFiPlazaProfile *profile, u32 index)
{
    GF_ASSERT(index < 2);

    if (profile->pokemonTypes[index] >= NUM_POKEMON_TYPES) {
        return TYPE_NORMAL;
    }

    return profile->pokemonTypes[index];
}

void WiFiPlazaLobby_State_GetQuestionnaireAnswer(const WiFiPlazaProfile *profile, WiFiPlazaLobbyQuestionnaireAnswer *param1)
{
    *param1 = profile->questionnaireAnswer;
}

TrainerInfo *WiFiPlazaLobby_State_GetLocalTrainerInfo(const WiFiPlazaLobbyState *param0)
{
    return param0->trainerInfoHolder.trainerInfo;
}

BOOL WiFiPlazaLobby_State_IsMemberPresent(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetPendingNewsPlayerFlag(&param0->newsPlayerFlags, param1);
}

void WiFiPlazaLobby_State_GetMemberPresentBitmap(const WiFiPlazaLobbyState *param0, WiFiPlazaLobbyNewsPlayerFlags *param1)
{
    WiFiPlazaLobbyNewsPlayerFlags *v0;

    MI_CpuCopy8(&param0->newsPlayerFlags, param1, sizeof(WiFiPlazaLobbyNewsPlayerFlags));
}

BOOL WiFiPlazaLobby_State_HasMemberPassword(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetPasswordEntryFlag(&param0->passwordState, param1);
}

const WiFiPlazaLobbyPasswordWords *WiFiPlazaLobby_State_GetMemberPassword(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetPasswordEntry(&param0->passwordState, param1);
}

u32 WiFiPlazaLobby_State_GetSecondaryMemberCount(const WiFiPlazaLobbyState *param0)
{
    WiFiPlazaLobbyNetworkPlayerIdList v0;

    WiFiPlazaLobby_Network_GetSubChannelPlayerList(&v0);
    return v0.count;
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

    v0.kind = 0;
    v0.userIDs[0] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param1);
    v0.userIDs[1] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param2);
    v0.count = 2;

    WiFiPlazaLobby_Network_SendMainChannelMessage(4, &v0, sizeof(WiFiPlazaLobbyProfileViewMessage));
}

void WiFiPlazaLobby_State_SendProfileViewMessageWithExtra(WiFiPlazaLobbyState *param0, u32 param1, u32 param2, u32 param3)
{
    WiFiPlazaLobbyProfileViewMessage v0 = { 0 };

    v0.kind = 1;
    v0.userIDs[0] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param2);
    v0.userIDs[1] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param1);
    v0.count = 2;
    v0.rank = param3;

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

    v0.kind = v1;
    v0.userIDs[0] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param3);
    v0.userIDs[1] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param4);
    v0.userIDs[2] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param5);
    v0.userIDs[3] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param6);
    v0.count = param2;
    v0.minigame = param1;
    v0.isRanked = param7;

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
    v0.kind = v1;
    v0.userIDs[0] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param3);
    v0.userIDs[1] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param4);
    v0.userIDs[2] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param5);
    v0.userIDs[3] = WiFiPlazaLobby_Network_GetMainPlayerUserId(param6);
    v0.count = param2;
    v0.minigame = param1;
    v0.isRanked = 0;

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
    return param0->playerFlags.cosmeticKnown[param1];
}

void WiFiPlazaLobby_State_BroadcastCosmeticID(WiFiPlazaLobbyState *param0, u32 param1)
{
    u32 v0 = param1;
    WiFiPlazaLobby_Network_SendMainChannelMessage(5, &v0, sizeof(u32));
}

int WiFiPlazaLobby_State_GetFloatState(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetMinigameGroupStatus(&param0->minigameGrid, param1);
}

u32 WiFiPlazaLobby_State_GetFloatTimer(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetMinigameGroupTimer(&param0->minigameGrid, param1);
}

u32 WiFiPlazaLobby_State_GetFloatTimerMax(const WiFiPlazaLobbyState *param0)
{
    return 40 * 30;
}

u32 WiFiPlazaLobby_State_FindFloatSlotByUserID(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_FindMinigameSlot(&param0->minigameGrid, param1);
}

u32 WiFiPlazaLobby_State_AllocateFloatSlot(WiFiPlazaLobbyState *param0, u32 param1, int param2)
{
    return WiFiPlazaLobby_State_FindFreeMinigameSlot(&param0->minigameGrid, param1, param2);
}

void WiFiPlazaLobby_State_FreeFloatSlot(WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaLobby_State_RemoveMinigameSlot(&param0->minigameGrid, param1);
}

void WiFiPlazaLobby_State_SetFloatSlotTrigger(WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaLobby_State_SetMinigameSlotFlag(&param0->minigameGrid, param1);
}

BOOL WiFiPlazaLobby_State_IsFloatSlotTriggered(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetMinigameSlotFlag(&param0->minigameGrid, param1);
}

void WiFiPlazaLobby_State_ClearFloatSlotTrigger(WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaLobby_State_ClearMinigameSlotFlag(&param0->minigameGrid, param1);
}

void WiFiPlazaLobby_State_FloatSlotToRowCol(u32 param0, u32 *param1, u32 *param2)
{
    WiFiPlazaLobby_State_SlotToRowCol(param0, param1, param2);
}

void WiFiPlazaLobby_State_SetFloatSlotPosition(WiFiPlazaLobbyState *param0, u32 param1, int param2)
{
    WiFiPlazaLobby_State_SetMinigamePriority(&param0->minigameGrid, param1, param2);
}

int WiFiPlazaLobby_State_GetFloatSlotPosition(const WiFiPlazaLobbyState *param0, u32 param1)
{
    return WiFiPlazaLobby_State_GetMinigamePriority(&param0->minigameGrid, param1);
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
    WiFiPlazaLobby_State_ResetInteraction(&param0->interaction);
}

BOOL WiFiPlazaLobby_State_RequestChat(WiFiPlazaLobbyState *param0, u32 param1)
{
    s32 v0;

    if (param0->interaction.phase != 0) {
        return 0;
    }

    {
        const WiFiPlazaProfile *v1 = WiFiPlazaLobby_State_GetProfileBySlot(param0, param1);
        u32 v2 = WiFiPlazaLobby_State_GetVenueIndex(v1);

        if (v2 != 1) {
            return 0;
        }
    }

    param0->interaction.partnerSlot = param1;
    param0->interaction.state = 1;
    param0->interaction.phase = 1;

    WiFiPlazaLobby_State_SetInteractionData(&param0->interaction, 0);
    v0 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param1);
    WiFiPlazaLobby_Network_SendPlayerMessage(0, v0, &param0->interaction.data, sizeof(WiFiPlazaLobbyInteractionData));
    WiFiPlazaLobby_State_StartInteractionTimer(&param0->interaction);

    return 1;
}

void WiFiPlazaLobby_State_UpdateChatRequest(WiFiPlazaLobbyState *param0, u16 param1)
{
    BOOL isTrainerNameValid = FALSE;
    s32 v1;

    if (param0->interaction.phase == 1) {
        if (param0->interaction.state != 2) {
            isTrainerNameValid = TRUE;
        }
    } else {
        if (param0->interaction.phase == 2) {
            if (param0->interaction.state != 3) {
                isTrainerNameValid = TRUE;
            }
        }
    }

    if (isTrainerNameValid) {
        v1 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param0->interaction.partnerSlot);
        WiFiPlazaLobby_State_SendInteractionCancel(param0, v1);
        return;
    }

    switch (param0->interaction.phase) {
    case 1:
        param0->interaction.state = 3;
        break;
    case 2:
        param0->interaction.state = 2;
        break;
    default:
        v1 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param0->interaction.partnerSlot);
        WiFiPlazaLobby_State_SendInteractionCancel(param0, v1);
        return;
    }

    WiFiPlazaLobby_State_SetInteractionData(&param0->interaction, param1);
    v1 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param0->interaction.partnerSlot);
    WiFiPlazaLobby_Network_SendPlayerMessage(2, v1, &param0->interaction.data, sizeof(WiFiPlazaLobbyInteractionData));
    WiFiPlazaLobby_State_StartInteractionTimer(&param0->interaction);
}

void WiFiPlazaLobby_State_CompleteChat(WiFiPlazaLobbyState *param0)
{
    s32 v0;

    if (param0->interaction.state == 0) {
        return;
    }

    if (param0->interaction.phase != 1) {
        return;
    }

    param0->interaction.data.event = 0;
    v0 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param0->interaction.partnerSlot);

    WiFiPlazaLobby_Network_SendPlayerMessage(3, v0, &param0->interaction.data, sizeof(WiFiPlazaLobbyInteractionData));
    WiFiPlazaLobby_State_ResetInteraction(&param0->interaction);
}

void WiFiPlazaLobby_State_EndChat(WiFiPlazaLobbyState *param0)
{
    s32 v0;

    if (param0->interaction.state == 0) {
        return;
    }

    v0 = WiFiPlazaLobby_Network_GetMainPlayerUserId(param0->interaction.partnerSlot);

    param0->interaction.state = 4;
    param0->interaction.data.event = 4;

    WiFiPlazaLobby_Network_SendPlayerMessage(2, v0, &param0->interaction.data, sizeof(WiFiPlazaLobbyInteractionData));
}

BOOL WiFiPlazaLobby_State_IsChatActive(const WiFiPlazaLobbyState *param0)
{
    if (param0->interaction.phase != 0) {
        return 1;
    }

    return 0;
}

BOOL WiFiPlazaLobby_State_IsChatRequested(const WiFiPlazaLobbyState *param0)
{
    if (param0->interaction.phase == 2) {
        return 1;
    }

    return 0;
}

u32 WiFiPlazaLobby_State_GetChatPartner(const WiFiPlazaLobbyState *param0)
{
    return param0->interaction.partnerSlot;
}

BOOL WiFiPlazaLobby_State_HasChattedWithCurrentMember(const WiFiPlazaLobbyState *param0)
{
    return param0->interaction.chattedWithCurrent;
}

int WiFiPlazaLobby_State_GetChatState(const WiFiPlazaLobbyState *param0)
{
    return param0->interaction.state;
}

u16 WiFiPlazaLobby_State_GetChatResponse(const WiFiPlazaLobbyState *param0)
{
    return param0->interaction.response;
}

BOOL WiFiPlazaLobby_State_CanChatWithMember(const WiFiPlazaLobbyState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param0->interaction.chatCounts[param1] >= 6) {
        return 0;
    }

    return 1;
}

BOOL WiFiPlazaLobby_State_IsChatFinished(const WiFiPlazaLobbyState *param0)
{
    if (param0->interaction.state == 4) {
        return 1;
    }

    if (WiFiPlazaLobby_State_CheckInteractionTimeout(&param0->interaction) == 0) {
        return 1;
    }

    return 0;
}

s16 WiFiPlazaLobby_State_GetChatTimer(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_State_GetInteractionTimer(&param0->interaction);
}

void WiFiPlazaLobby_State_SetChatPending(WiFiPlazaLobbyState *param0)
{
    param0->interaction.pending = 1;
}

BOOL WiFiPlazaLobby_State_IsChatPending(const WiFiPlazaLobbyState *param0)
{
    return param0->interaction.pending;
}

void WiFiPlazaLobby_State_ResetChatIfActive(WiFiPlazaLobbyState *param0)
{
    if (WiFiPlazaLobby_State_IsChatActive(param0) == 1) {
        WiFiPlazaLobby_State_IncrementPlayerCounter(&param0->interaction, param0->interaction.partnerSlot);
    }
}

void WiFiPlazaLobby_State_IncrementMemberChatCount(WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaLobby_State_IncrementPlayerCounter(&param0->interaction, param1);
}

void WiFiPlazaLobby_State_MarkMemberChatted(WiFiPlazaLobbyState *param0, u32 param1)
{
    WiFiPlazaLobby_State_SetPlayerFlag(&param0->interaction, param1);
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
    param0->activityFlags.activityDone[param1] = 1;
}

int WiFiPlazaLobby_State_GetAvailableActivity(const WiFiPlazaLobbyState *param0)
{
    int v0;
    BOOL v1;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->activityFlags.activityDone[v0] == 0) {
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
    u32 v0 = WiFiPlazaLobby_State_ChooseWeightedMinigameGroup(&param0->minigameWeights);

    if (WiFiPlazaLobby_State_IsMemberPresent(param0, WiFiPlazaLobby_State_GetMySlotIndex(param0)) == 1) {
        v0 += (3 - 1);
    }

    return v0;
}

int WiFiPlazaLobby_State_GetFireworksEventStage(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_State_GetEventTimerStage(&param0->eventTimer);
}

u32 WiFiPlazaLobby_State_GetFireworksFrame(const WiFiPlazaLobbyState *param0)
{
    return WiFiPlazaLobby_State_GetEventTimerCounter(&param0->eventTimer);
}

void WiFiPlazaLobby_State_SetQuestionnaireResult(WiFiPlazaLobbyState *param0, const WiFiLobbyQuestionnaireAnswerTally *param1)
{
    param0->questionnaire.hasResult = 1;
    param0->questionnaire.result = *param1;
}

BOOL WiFiPlazaLobby_State_GetQuestionnaireResult(const WiFiPlazaLobbyState *param0, WiFiLobbyQuestionnaireAnswerTally *param1)
{
    if (param0->questionnaire.hasResult == 1) {
        *param1 = param0->questionnaire.result;
        return 1;
    }

    return 0;
}

void WiFiPlazaLobby_State_CreateWFCTrainerInfo(WiFiPlazaLobbyState *param0)
{
    TrainerInfo *info;

    GF_ASSERT(param0->wfcTrainerInfo == NULL);

    info = SaveData_GetTrainerInfo(param0->saveData);
    param0->wfcTrainerInfo = WFCTrainerInfo_New(info, param0->heapID);
}

void WiFiPlazaLobby_State_FreeWFCTrainerInfo(WiFiPlazaLobbyState *param0)
{
    if (param0->wfcTrainerInfo != NULL) {
        WFCTrainerInfo_Free(param0->wfcTrainerInfo);
        param0->wfcTrainerInfo = NULL;
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
        WiFiPlazaLobby_State_InitTrainerInfoFromProfile(&v0->trainerInfoHolder, &v0->profileCache, v0->heapID);

        if (WiFiPlazaLobby_State_ValidateProfileChecksum(&v0->profileCache, v0->saveData) == 0) {
            v0->errorFlag = 1;
        }

        v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);
        WiFiPlazaLobby_News_SetResult(v0->players.news, v1, v0->profileCache.profile.trainerGender, WiFiPlazaLobbyNewsResultFlags_01 | WiFiPlazaLobbyNewsResultFlags_02);
        v0->profileCache.profile.userId = param0;

        {
            s64 v5;

            WiFiPlazaLobby_Network_GetPlayerEnterTime(param0, &v5);
            WiFiPlazaLobby_Time_SetFromSeconds(&v0->profileCache.profile.enterTime, &v5);
        }

        {
            u32 v6, v7;
            BOOL v8;

            v6 = WiFiPlazaLobby_State_GetCountry(&v0->profileCache.profile);
            v7 = WiFiPlazaLobby_State_GetRegion(&v0->profileCache.profile);
            v8 = WiFiPlazaProfile_IsLanguageValid(&v0->profileCache.profile);

            if ((v6 != 0) && (v8 == 1)) {
                v0->profileCache.profile.localTime = WiFiPlazaLobby_Earth_ComputeLocalTimeOffset(v6, v7, v0->profileCache.profile.enterTime, v0->heapID);
            } else {
                v0->profileCache.profile.localTime.hour = 12;
                v0->profileCache.profile.localTime.minute = 0;
                v0->profileCache.profile.localTime.second = 0;
            }
        }

        WiFiPlazaLobby_State_UpdateProfileChecksum(&v0->profileCache, v0->saveData);
        WiFiPlazaLobby_State_LoadCachedProfile(v0);
    } else {
        v2 = (const WiFiPlazaProfile *)param1;
        v3 = WiFiPlazaLobby_Network_FindFirstPlayer();
        v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

        WiFiPlazaLobby_News_SetResult(v0->players.news, v1, WiFiPlazaProfile_GetGender(v2), WiFiPlazaLobbyNewsResultFlags_00);

        if (v3 == param0) {
            WiFiPlazaLobby_News_SelectResult(v0->players.news, v1);
        }

        if (WiFiPlazaLobby_State_ReplaceRecentPlayer(&v0->recentPlayers, param0, DWC_LOBBY_INVALID_USER_ID)) {
            WiFiPlazaLobby_State_LoadCachedProfile(v0);
        }
    }

    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);
    v0->eventFlags.playerJoined |= 1 << v1;

    if (WiFiPlazaLobby_Network_IsVipProfile(param0) == 1) {
        u32 v9;

        WiFiPlazaLobby_State_SetPendingNewsPlayerFlag(&v0->newsPlayerFlags, v1, 1);

        {
            WiFiPlazaLobbyNewsTrainerEntry v10;

            v10.slot = v1;
            WiFiPlazaLobby_News_AddTrainerEntry(v0->players.news, &v10, &v0->newsPlayerFlags);
        }

        v9 = WiFiPlazaLobby_Network_GetVipKey(param0);

        if (v9 != 0) {
            WiFiPlazaLobby_State_SetPasswordEntry(&v0->passwordState, v1, 1, v9);
        } else {
            WiFiPlazaLobby_State_SetPasswordEntry(&v0->passwordState, v1, 0, v9);
        }
    } else {
        WiFiPlazaLobby_State_SetPendingNewsPlayerFlag(&v0->newsPlayerFlags, v1, 0);
        WiFiPlazaLobby_State_SetPasswordEntry(&v0->passwordState, v1, 0, 0);
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
            WiFiPlazaLobby_State_AbortInteraction(&v0->interaction);
        }
    }

    v3 = WiFiPlazaLobby_News_TakeResultFlag(v0->players.news, v1);

    if (v3) {
        v4 = WiFiPlazaLobby_Network_FindFirstPlayerExcept(param0);
        v2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(v4);

        WiFiPlazaLobby_News_SelectResult(v0->players.news, v2);
    }

    WiFiPlazaLobby_State_SetPendingNewsPlayerFlag(&v0->newsPlayerFlags, v1, 0);
    WiFiPlazaLobby_State_ResetPlayerCounter(&v0->interaction, v1);
    WiFiPlazaLobby_State_ClearPlayerFlag(&v0->interaction, v1);

    if (WiFiPlazaLobby_State_ReplaceRecentPlayer(&v0->recentPlayers, param0, DWC_LOBBY_INVALID_USER_ID)) {
        WiFiPlazaLobby_State_LoadCachedProfile(v0);
    }

    WiFiPlazaLobby_State_SetPasswordEntry(&v0->passwordState, v1, 0, 0);

    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);
    v0->eventFlags.playerLeft |= 1 << v1;
}

static void WiFiPlazaLobby_State_HandleMemberUpdated(s32 param0, const void *param1, void *param2)
{
    WiFiPlazaLobbyState *v0;
    u32 v1;
    const WiFiPlazaProfile *v2;
    u32 v3;

    v0 = param2;
    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    v0->eventFlags.playerUpdated |= 1 << v1;

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
        WiFiPlazaLobby_State_ResetPlayerCounter(&v0->interaction, v1);
        break;
    default:
        break;
    }

    if (WiFiPlazaLobby_State_IsAppearanceRankSet(v2) == 1) {
        WiFiPlazaLobby_State_ReduceMinigameWeight(&v0->minigameWeights, WiFiPlazaLobby_State_GetAppearanceRank(v2), v1);
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
        WiFiPlazaLobby_Time_SetFromSeconds(&v0->players.currentTime, &v3.currentTime);

        v0->players.currentTimeSeconds = v3.currentTime;
    }

    switch (param0) {
    case PPW_LOBBY_TIME_EVENT_LOCK:
        WiFiPlazaLobby_News_SetPlazaInfo(v0->players.news, &v0->players.currentTime);
        v0->players.lockTime = v0->players.currentTimeSeconds;
        v0->eventTimers.locked = 1;
        v0->eventFlags.timeEvents |= 1 << 0;
        break;
    case PPW_LOBBY_TIME_EVENT_NEON_A1:
    case PPW_LOBBY_TIME_EVENT_NEON_A2:
    case PPW_LOBBY_TIME_EVENT_NEON_A3:
    case PPW_LOBBY_TIME_EVENT_NEON_A4:
    case PPW_LOBBY_TIME_EVENT_NEON_A5:
        if (v0->players.neonTransitionActive == 0) {
            v1 = 1;
            v2 = 0;

            v0->players.neonTransitionActive = 1;
            v0->eventTimers.neonTimer = (10 * 30);
        }
    case PPW_LOBBY_TIME_EVENT_NEON_A0:
        v0->eventTimers.neonATimeEvent = param0;
        v0->eventFlags.timeEvents |= 1 << 1;
        break;
    case PPW_LOBBY_TIME_EVENT_NEON_B1:
    case PPW_LOBBY_TIME_EVENT_NEON_B2:
    case PPW_LOBBY_TIME_EVENT_NEON_B3:
        if (v0->players.neonTransitionActive == 0) {
            v1 = 1;
            v2 = 0;

            v0->players.neonTransitionActive = 1;
            v0->eventTimers.neonTimer = (10 * 30);
        }
    case PPW_LOBBY_TIME_EVENT_NEON_B0:
        v0->eventTimers.neonBTimeEvent = param0;
        v0->eventFlags.timeEvents |= 1 << 2;
        break;
    case PPW_LOBBY_TIME_EVENT_NEON_C1:
    case PPW_LOBBY_TIME_EVENT_NEON_C2:
    case PPW_LOBBY_TIME_EVENT_NEON_C3:
        if (v0->players.neonTransitionActive == 0) {
            v1 = 1;
            v2 = 0;

            v0->players.neonTransitionActive = 1;
            v0->eventTimers.neonTimer = (10 * 30);
        }

    case PPW_LOBBY_TIME_EVENT_NEON_C0:
        v0->eventTimers.neonCTimeEvent = param0;
        v0->eventFlags.timeEvents |= 1 << 3;
        break;
    case PPW_LOBBY_TIME_EVENT_FIRE_WORKS_START:
        v1 = 1;
        v2 = 1;

        {
            u32 v4, v5;

            v4 = WiFiPlazaLobby_Network_GetScheduleValue(WiFiPlazaLobbyNetworkScheduleField_06);
            v5 = WiFiPlazaLobby_Network_GetScheduleValue(WiFiPlazaLobbyNetworkScheduleField_07);

            WiFiPlazaLobby_State_InitEventTimer(&v0->eventTimer, v4, v5);
        }

        v0->eventTimers.fireworksTimer = (10 * 30);
        break;
    case PPW_LOBBY_TIME_EVENT_FIRE_WORKS_END:
        v0->eventTimers.fireworksState = 2;
        v0->eventFlags.timeEvents |= 1 << 5;
        break;
    case PPW_LOBBY_TIME_EVENT_PARADE:
        v1 = 1;
        v2 = 2;

        v0->eventTimers.paradeTimer = (10 * 30);
        break;
    case PPW_LOBBY_TIME_EVENT_CLOSE:
        v1 = 1;
        v2 = 4;

        v0->eventTimers.closed = 1;
        v0->eventTimers.closeTimer = (30 * 30);
        break;
    case PPW_LOBBY_TIME_EVENT_MINIGAME_END:
        v0->eventTimers.minigameEnded = 1;
        v0->eventFlags.timeEvents |= 1 << 4;
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

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&v0->profileCache, v0->saveData) == 0) {
        v0->errorFlag = 1;
        return;
    }

    WiFiPlazaLobby_State_CopyProfile(&v0->profileCache, v1, param1);
    WiFiPlazaLobby_State_UpdateProfileChecksum(&v0->profileCache, v0->saveData);
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
        if (v1.userIDs[v0] != DWC_LOBBY_INVALID_USER_ID) {
            v2 = (const WiFiPlazaProfile *)WiFiPlazaLobby_Network_GetPlayerData(v1.userIDs[v0]);
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

    if ((param0->eventTimers.locked == 1) && (param0->eventTimers.closed == 0) && (WiFiPlazaLobby_Network_GetState() == WiFiPlazaLobbyNetworkLobbyState_02)) {
        v0 = WiFiPlazaLobby_State_GetLobbyCloseTime(param0);
        v0 += param0->players.lockTime;

        v1 = param0->players.currentTimeSeconds;

        if (v1 > v0) {
            param0->eventTimers.closed = 1;
            param0->eventTimers.closeTimer = (30 * 30);
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
    String_ToChars(trainerName, param0->localTrainerName, NELEMS(param0->localTrainerName));
    String_Free(trainerName);

    param0->profile.userId = DWC_LOBBY_INVALID_USER_ID;
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
    param0->profile.appearanceRank = 0xff;
    param0->profile.venue = 0;
    param0->profile.gameVersion = GAME_VERSION;
    param0->profile.startTimestamp = gameTime->startTimestamp;

    for (int i = 0; i < 12; i++) {
        param0->profile.recentAppearances[i] = 24;
        param0->profile.recentUserIDs[i] = DWC_LOBBY_INVALID_USER_ID;
    }

    for (int i = 0; i < 2; i++) {
        param0->profile.pokemonTypes[i] = TYPE_NORMAL;
    }

    param0->profile.questionnaireAnswer.questionNumber = 0xffffffff;
    param0->profile.questionnaireAnswer.selectedAnswer = 3;

    WiFiPlazaLobby_State_UpdateProfileChecksum(param0, saveData);
}

static void WiFiPlazaLobby_State_LoadCachedProfile(WiFiPlazaLobbyState *param0)
{
    int v0;
    const WiFiPlazaProfile *v1;

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&param0->profileCache, param0->saveData) == 0) {
        param0->errorFlag = 1;
        return;
    }

    for (v0 = 0; v0 < 12; v0++) {
        param0->profileCache.profile.recentAppearances[v0] = WiFiPlazaLobby_State_GetRecentPlayerAppearance(&param0->recentPlayers, v0);
        param0->profileCache.profile.recentUserIDs[v0] = WiFiPlazaLobby_State_GetRecentPlayerID(&param0->recentPlayers, v0);
    }

    MI_CpuCopy8(param0->profileCache.receivedTrainerName, param0->profileCache.profile.trainerName, sizeof(u16) * (7 + 1));
    WiFiPlazaLobby_Network_SetMyProfile(&param0->profileCache.profile);

    MI_CpuCopy8(param0->profileCache.localTrainerName, param0->profileCache.profile.trainerName, sizeof(u16) * (7 + 1));
    WiFiPlazaLobby_State_UpdateProfileChecksum(&param0->profileCache, param0->saveData);
}

static void WiFiPlazaLobby_State_UpdateProfileChecksum(WiFiPlazaLobbyProfileCache *param0, const SaveData *saveData)
{
    param0->profileChecksum = SaveData_CalculateChecksum(saveData, &param0->profile, sizeof(WiFiPlazaProfile));
}

static BOOL WiFiPlazaLobby_State_ValidateProfileChecksum(const WiFiPlazaLobbyProfileCache *param0, const SaveData *saveData)
{
    u32 v0 = SaveData_CalculateChecksum(saveData, &param0->profile, sizeof(WiFiPlazaProfile));

    if (v0 != param0->profileChecksum) {
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

    MI_CpuCopy8(param1->trainerName, param0->receivedTrainerName, sizeof(u16) * (7 + 1));
    MI_CpuCopy8(param0->localTrainerName, param0->profile.trainerName, sizeof(u16) * (7 + 1));
}

static void WiFiPlazaLobby_State_ResetEventFlags(WiFiPlazaLobbyEventFlags *param0)
{
    param0->timeEvents = 0;
}

static void WiFiPlazaLobby_State_UpdateEventTimers(WiFiPlazaLobbyEventTimers *param0, WiFiPlazaLobbyEventFlags *param1, WiFiPlazaLobbyMinigameGrid *param2, WiFiPlazaLobbyEventTimer *param3)
{
    if ((param0->closeTimer - 1) >= 0) {
        param0->closeTimer--;

        if (param0->closeTimer == (28 * 30)) {
            Sound_FadeOutBGM(0, 127);
            param0->bgmFadeStarted = 1;
        }
    } else if (param0->closeTimer == 0) {
        param0->closing = 1;
        param1->timeEvents |= 1 << 7;
        param0->closeTimer--;
    }

    if ((param0->neonTimer - 1) >= 0) {
        param0->neonTimer--;
    } else if (param0->neonTimer == 0) {
        param1->timeEvents |= 1 << 2;
        param1->timeEvents |= 1 << 3;
        param1->timeEvents |= 1 << 1;
        param0->neonTimer--;
    }

    if ((param0->fireworksTimer - 1) >= 0) {
        param0->fireworksTimer--;
    } else if (param0->fireworksTimer == 0) {
        param0->fireworksState = 1;
        param1->timeEvents |= 1 << 5;
        param0->fireworksTimer--;
        WiFiPlazaLobby_State_StartEventTimer(param3);
    }

    if ((param0->paradeTimer - 1) >= 0) {
        param0->paradeTimer--;
    } else if (param0->paradeTimer == 0) {
        WiFiPlazaLobby_State_ActivateMinigameGrid(param2);

        if (param0->bgmSuppressed == 0) {
            Sound_PlayBGM(SEQ_PL_WIFIPARADE_sseq);
        }

        param0->paradeActive = 1;
        param1->timeEvents |= 1 << 6;
        param0->paradeTimer--;
    }
}

static void WiFiPlazaLobby_State_InitEventState(WiFiPlazaLobbyEventTimers *param0)
{
    param0->locked = 0;
    param0->closing = 0;
    param0->fireworksState = 0;
    param0->paradeActive = 0;
    param0->minigameEnded = 0;
    param0->closed = 0;
    param0->neonATimeEvent = PPW_LOBBY_TIME_EVENT_NEON_A0;
    param0->neonBTimeEvent = PPW_LOBBY_TIME_EVENT_NEON_B0;
    param0->neonCTimeEvent = PPW_LOBBY_TIME_EVENT_NEON_C0;
    param0->closeTimer = -1;
    param0->neonTimer = -1;
    param0->fireworksTimer = -1;
    param0->paradeTimer = -1;
}

static void WiFiPlazaLobby_State_UpdateMusicVolume(const WiFiPlazaLobbyEventTimers *param0)
{
    if (param0->bgmVolumeDucked == 1) {
        Sound_SetPlayerVolume(7, (127 / 3));
    } else {
        Sound_SetPlayerVolume(7, 127);
    }
}

static void WiFiPlazaLobby_State_ResetTimer(WiFiPlazaLobbyTimer *param0)
{
    param0->time = (30 * 30);
}

static BOOL WiFiPlazaLobby_State_IsTimerActive(const WiFiPlazaLobbyTimer *param0)
{
    if (param0->time > 0) {
        return 1;
    }

    return 0;
}

static void WiFiPlazaLobby_State_TickTimer(WiFiPlazaLobbyTimer *param0)
{
    if (param0->time > 0) {
        param0->time--;
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
    MI_CpuCopy8(param1->receivedTrainerName, v0->trainerName, sizeof(u16) * (7 + 1));

    WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->trainerInfo, heapID);
    Heap_Free(v0);
}

static void WiFiPlazaLobby_State_SetTimerExpired(WiFiPlazaLobbyTimer *param0)
{
    param0->expired = 1;
}

static BOOL WiFiPlazaLobby_State_IsTimerExpired(const WiFiPlazaLobbyTimer *param0)
{
    return param0->expired;
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
    param0->partnerSlot = 0;
    param0->state = 0;
    param0->phase = 0;

    WiFiPlazaLobby_State_StopInteractionTimer(param0);
}

static void WiFiPlazaLobby_State_AbortInteraction(WiFiPlazaLobbyInteractionState *param0)
{
    param0->partnerSlot = 0;
    param0->state = 4;

    WiFiPlazaLobby_State_StopInteractionTimer(param0);

    param0->phase = 0;
}

static BOOL WiFiPlazaLobby_State_IsPlayerFlagSet(const WiFiPlazaLobbyInteractionState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param0->chattedBitmap & (1 << param1)) {
        return 1;
    }

    return 0;
}

static void WiFiPlazaLobby_State_SetPlayerFlag(WiFiPlazaLobbyInteractionState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    param0->chattedBitmap |= (1 << param1);
}

static void WiFiPlazaLobby_State_ClearPlayerFlag(WiFiPlazaLobbyInteractionState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    param0->chattedBitmap &= ~(1 << param1);
}

static void WiFiPlazaLobby_State_IncrementPlayerCounter(WiFiPlazaLobbyInteractionState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if ((param0->chatCounts[param1] + 1) <= 6) {
        param0->chatCounts[param1]++;
    }
}

static void WiFiPlazaLobby_State_ResetPlayerCounter(WiFiPlazaLobbyInteractionState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    param0->chatCounts[param1] = 0;
}

static void WiFiPlazaLobby_State_SetInteractionData(WiFiPlazaLobbyInteractionState *param0, u16 param1)
{
    param0->data.event = param0->state;
    param0->data.value = param1;
}

static void WiFiPlazaLobby_State_SendInteractionResult(WiFiPlazaLobbyState *param0, s32 param1, BOOL param2)
{
    param0->interaction.data.event = 2;
    param0->interaction.data.value = param2;

    WiFiPlazaLobby_Network_SendPlayerMessage(1, param1, &param0->interaction.data, sizeof(WiFiPlazaLobbyInteractionData));
}

static void WiFiPlazaLobby_State_SendInteractionCancel(WiFiPlazaLobbyState *param0, s32 param1)
{
    param0->interaction.state = 4;
    param0->interaction.data.event = 4;

    WiFiPlazaLobby_Network_SendPlayerMessage(2, param1, &param0->interaction.data, sizeof(WiFiPlazaLobbyInteractionData));
}

static void WiFiPlazaLobby_State_StartInteractionTimer(WiFiPlazaLobbyInteractionState *param0)
{
    param0->timerActive = 1;
    param0->timer = 0;
}

static void WiFiPlazaLobby_State_StopInteractionTimer(WiFiPlazaLobbyInteractionState *param0)
{
    param0->timerActive = 0;
    param0->timer = 0;
}

static void WiFiPlazaLobby_State_UpdateInteractionTimer(WiFiPlazaLobbyInteractionState *param0)
{
    if (param0->timerActive == 1) {
        if ((param0->timer + 1) <= 900) {
            param0->timer++;
        }
    }
}

static BOOL WiFiPlazaLobby_State_CheckInteractionTimeout(const WiFiPlazaLobbyInteractionState *param0)
{
    if (param0->timerActive == 0) {
        return 1;
    }

    if (param0->timer >= 900) {
        return 0;
    }

    return 1;
}

static s16 WiFiPlazaLobby_State_GetInteractionTimer(const WiFiPlazaLobbyInteractionState *param0)
{
    return param0->timer;
}

static void WiFiPlazaLobby_State_HandleTwoTrainerReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    u32 v2;
    WiFiPlazaLobbyNewsDuoEntry v3;

    if (param1->count != 2) {
        return;
    }

    for (v1 = 0; v1 < 2; v1++) {
        v2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[v1]);

        if (v2 != 0xffffffff) {
            v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v2);
            WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->players.trainerInfos[v1], param0->heapID);
        } else {
            return;
        }
    }

    v3.trainerInfo1 = param0->players.trainerInfos[0];
    v3.trainerInfo2 = param0->players.trainerInfos[1];
    v3.slot1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[0]);
    v3.slot2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[1]);

    WiFiPlazaLobby_News_AddDuoEntry(param0->players.news, &v3);
}

static void WiFiPlazaLobby_State_HandleTwoTrainerExtraReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    u32 v2;
    WiFiPlazaLobbyNewsDuoEntryRanked v3;

    if (param1->count != 2) {
        return;
    }

    for (v1 = 0; v1 < 2; v1++) {
        v2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[v1]);

        if (v2 != 0xffffffff) {
            v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v2);
            WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->players.trainerInfos[v1], param0->heapID);
        } else {
            return;
        }
    }

    v3.trainerInfo1 = param0->players.trainerInfos[0];
    v3.trainerInfo2 = param0->players.trainerInfos[1];
    v3.slot1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[0]);
    v3.slot2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[1]);
    v3.rank = param1->rank;

    WiFiPlazaLobby_News_AddDuoEntryRanked(param0->players.news, &v3);
}

static void WiFiPlazaLobby_State_HandleMinigameReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    TrainerInfo *v2[4];
    u32 v3;
    WiFiPlazaLobbyNewsMinigameEntry v4;

    if ((param1->count > 4) || (param1->count <= 0)) {
        return;
    }

    if (param1->isRanked == 1) {
        for (v1 = 0; v1 < 4; v1++) {
            if (v1 < param1->count) {
                v3 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[v1]);

                if (v3 != 0xffffffff) {
                    v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v3);
                    WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->players.trainerInfos[v1], param0->heapID);
                    v2[v1] = param0->players.trainerInfos[v1];
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
                u32 v5 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[v1]);

                if (v5 != 0xffffffff) {
                    v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v5);
                    WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->players.trainerInfos[v1], param0->heapID);
                    v2[v1] = param0->players.trainerInfos[v1];
                } else {
                    return;
                }
            } else {
                v2[v1] = NULL;
            }
        }
    }

    v4.minigame = param1->minigame;
    v4.count = param1->count;
    v4.trainerInfo0 = v2[0];
    v4.trainerInfo1 = v2[1];
    v4.trainerInfo2 = v2[2];
    v4.trainerInfo3 = v2[3];
    v4.slot0 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[0]);
    v4.slot1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[1]);
    v4.slot2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[2]);
    v4.slot3 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[3]);
    v4.isRanked = param1->isRanked;

    WiFiPlazaLobby_News_AddMinigameEntry(param0->players.news, &v4);
}

static void WiFiPlazaLobby_State_HandleSingleMinigameReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    u32 v2;
    WiFiPlazaLobbyNewsMinigameQuickEntry v3;

    if ((param1->count > 8) || (param1->count <= 0)) {
        return;
    }

    v2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[0]);

    if (v2 != 0xffffffff) {
        v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v2);
        WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->players.trainerInfos[0], param0->heapID);
    } else {
        return;
    }

    v3.minigame = param1->minigame;
    v3.count = param1->count;
    v3.trainerInfo = param0->players.trainerInfos[0];
    v3.slot = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[0]);

    WiFiPlazaLobby_News_AddMinigameQuickEntry(param0->players.news, &v3);
}

static void WiFiPlazaLobby_State_HandleFourTrainerReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    TrainerInfo *v2[4];
    u32 v3;
    WiFiPlazaLobbyNewsFourTrainerEntry v4;

    if ((param1->count > 4) || (param1->count <= 0)) {
        return;
    }

    for (v1 = 0; v1 < 4; v1++) {
        if (v1 < param1->count) {
            v3 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[v1]);

            if (v3 != 0xffffffff) {
                v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v3);
                WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->players.trainerInfos[v1], param0->heapID);
                v2[v1] = param0->players.trainerInfos[v1];
            } else {
                return;
            }
        } else {
            v2[v1] = NULL;
        }
    }

    v4.count = param1->count;
    v4.trainerInfo0 = v2[0];
    v4.trainerInfo1 = v2[1];
    v4.trainerInfo2 = v2[2];
    v4.trainerInfo3 = v2[3];
    v4.slot0 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[0]);
    v4.slot1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[1]);
    v4.slot2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[2]);
    v4.slot3 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[3]);

    WiFiPlazaLobby_News_AddFourTrainerEntry(param0->players.news, &v4);
}

static void WiFiPlazaLobby_State_HandleFourTrainerExtraReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    TrainerInfo *v2[4];
    u32 v3;
    WiFiPlazaLobbyNewsFourTrainerEntryB v4;

    if ((param1->count > 4) || (param1->count <= 0)) {
        return;
    }

    for (v1 = 0; v1 < 4; v1++) {
        if (v1 < param1->count) {
            v3 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[v1]);

            if (v3 != 0xffffffff) {
                v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v3);
                WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->players.trainerInfos[v1], param0->heapID);
                v2[v1] = param0->players.trainerInfos[v1];
            } else {
                return;
            }
        } else {
            v2[v1] = NULL;
        }
    }

    v4.count = param1->count;
    v4.trainerInfo0 = v2[0];
    v4.trainerInfo1 = v2[1];
    v4.trainerInfo2 = v2[2];
    v4.trainerInfo3 = v2[3];
    v4.slot0 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[0]);
    v4.slot1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[1]);
    v4.slot2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[2]);
    v4.slot3 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[3]);

    WiFiPlazaLobby_News_AddFourTrainerEntryB(param0->players.news, &v4);
}

static void WiFiPlazaLobby_State_HandleMinigameFourTrainerReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    const WiFiPlazaProfile *v0;
    int v1;
    TrainerInfo *v2[4];
    u32 v3;
    WiFiPlazaLobbyNewsMinigameResultEntry v4;

    if ((param1->count > 4) || (param1->count <= 0)) {
        return;
    }

    for (v1 = 0; v1 < 4; v1++) {
        if (v1 < param1->count) {
            v3 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[v1]);

            if (v3 != 0xffffffff) {
                v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0, v3);
                WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v0, param0->players.trainerInfos[v1], param0->heapID);
                v2[v1] = param0->players.trainerInfos[v1];
            } else {
                return;
            }
        } else {
            v2[v1] = NULL;
        }
    }

    v4.minigame = param1->minigame;
    v4.count = param1->count;
    v4.trainerInfo0 = v2[0];
    v4.trainerInfo1 = v2[1];
    v4.trainerInfo2 = v2[2];
    v4.trainerInfo3 = v2[3];
    v4.slot0 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[0]);
    v4.slot1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[1]);
    v4.slot2 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[2]);
    v4.slot3 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param1->userIDs[3]);

    WiFiPlazaLobby_News_AddMinigameResultEntry(param0->players.news, &v4);
}

static void WiFiPlazaLobby_State_HandleNoopReport(WiFiPlazaLobbyState *param0, const WiFiPlazaLobbyProfileViewMessage *param1)
{
    return;
}

static void WiFiPlazaLobby_State_PostMenuResultReport(WiFiPlazaLobbyState *param0, int param1)
{
    WiFiPlazaLobbyNewsEventEntry v0;

    v0.time = &param0->players.currentTime;
    v0.event = param1;

    WiFiPlazaLobby_News_AddEventEntry(param0->players.news, &v0);
}

static void WiFiPlazaLobby_State_ResetMinigameGrid(WiFiPlazaLobbyMinigameGrid *param0)
{
    memset(param0, 0, sizeof(WiFiPlazaLobbyMinigameGrid));
    MI_CpuFill32(param0->slotUserIDs, 0xffffffff, sizeof(u32) * (9 * 3));
}

static void WiFiPlazaLobby_State_ActivateMinigameGrid(WiFiPlazaLobbyMinigameGrid *param0)
{
    param0->active = 1;
}

static void WiFiPlazaLobby_State_UpdateMinigameSchedule(WiFiPlazaLobbyMinigameGrid *param0)
{
    int v0;

    if (param0->active == 0) {
        return;
    }

    for (v0 = 0; v0 < 9; v0++) {
        if (param0->elapsedTime == sMinigameGroupIds[v0]) {
            param0->groupStatus[v0] = 1;
        }

        if (param0->groupStatus[v0] == 1) {
            if ((param0->groupTimers[v0] + 1) <= (40 * 30)) {
                param0->groupTimers[v0]++;
            } else {
                param0->groupStatus[v0] = 2;
            }
        }
    }

    if ((param0->elapsedTime + 1) <= (144 * 30)) {
        param0->elapsedTime++;
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
                            param0->slotUserIDs[v1][v2] = param1;

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
        param0->slotUserIDs[v1][v2] = 0xffffffff;
    }
}

static u32 WiFiPlazaLobby_State_GetMinigameSlot(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    u32 v0;
    u32 v1;

    GF_ASSERT(param1 < 9 * 3);

    WiFiPlazaLobby_State_SlotToRowCol(param1, &v0, &v1);

    return param0->slotUserIDs[v0][v1];
}

static int WiFiPlazaLobby_State_GetMinigameGroupStatus(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    GF_ASSERT(param1 < 9);
    return param0->groupStatus[param1];
}

static u32 WiFiPlazaLobby_State_GetMinigameGroupTimer(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    GF_ASSERT(param1 < 9);
    return param0->groupTimers[param1];
}

static void WiFiPlazaLobby_State_SetMinigameSlotFlag(WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    u32 v0;
    u32 v1;
    u32 v2 = WiFiPlazaLobby_State_FindMinigameSlot(param0, param1);

    if (v2 != 0xffffffff) {
        WiFiPlazaLobby_State_SlotToRowCol(v2, &v0, &v1);
        param0->slotFlags[v0][v1] = 1;
    }
}

static BOOL WiFiPlazaLobby_State_GetMinigameSlotFlag(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    u32 v0;
    u32 v1;

    GF_ASSERT(param1 < 9 * 3);

    WiFiPlazaLobby_State_SlotToRowCol(param1, &v0, &v1);
    return param0->slotFlags[v0][v1];
}

static void WiFiPlazaLobby_State_ClearMinigameSlotFlag(WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    u32 v0;
    u32 v1;

    GF_ASSERT(param1 < 9 * 3);

    WiFiPlazaLobby_State_SlotToRowCol(param1, &v0, &v1);
    param0->slotFlags[v0][v1] = 0;
}

static u32 WiFiPlazaLobby_State_FindMinigameSlot(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1)
{
    int v0, v1;

    for (v0 = 0; v0 < 9; v0++) {
        for (v1 = 0; v1 < 3; v1++) {
            if (param0->slotUserIDs[v0][v1] == param1) {
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
    param0->slotPriorities[v0][v1] = param2 + 1;
}

static BOOL WiFiPlazaLobby_State_CheckMinigamePriority(const WiFiPlazaLobbyMinigameGrid *param0, u32 param1, int param2)
{
    u32 v0;
    u32 v1;

    GF_ASSERT(param1 < 9 * 3);

    WiFiPlazaLobby_State_SlotToRowCol(param1, &v0, &v1);

    if (param0->slotPriorities[v0][v1] <= param2) {
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

    return param0->slotPriorities[v0][v1];
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

    if (WiFiPlazaLobby_State_ValidateProfileChecksum(&v0->profileCache, v0->saveData) == 0) {
        v0->errorFlag = 1;
    }

    v3 = WiFiPlazaLobby_State_GetVenueIndex(&v0->profileCache.profile);
    v4 = WiFiPlazaLobby_State_IsChatActive(v0);

    if ((v3 != 1) || (v1 == 0xffffffff) || (v2->event != 1) || (v4 == 1) || (WiFiPlazaLobby_State_CanChatWithMember(v0, v1) == 0)) {
        WiFiPlazaLobby_State_SendInteractionResult(v0, param0, 0);
        return;
    }

    WiFiPlazaLobby_State_SendInteractionResult(v0, param0, 1);

    if (WiFiPlazaLobby_State_IsPlayerFlagSet(&v0->interaction, v1) == 0) {
        v0->interaction.chattedWithCurrent = 1;
    } else {
        v0->interaction.chattedWithCurrent = 0;
    }

    v0->interaction.partnerSlot = v1;
    v0->interaction.state = 2;
    v0->interaction.phase = 2;
    v0->interaction.pending = 0;

    WiFiPlazaLobby_State_StartInteractionTimer(&v0->interaction);
}

static void WiFiPlazaLobby_State_HandleInteractionUpdate(s32 param0, const void *param1, u32 param2, void *param3)
{
    WiFiPlazaLobbyState *v0 = param3;
    u32 v1;
    const WiFiPlazaLobbyInteractionData *v2 = param1;
    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    if (v0->interaction.phase == 0) {
        return;
    }

    if (v0->interaction.partnerSlot == v1) {
        if (v2->value == 1) {
            if (WiFiPlazaLobby_State_IsPlayerFlagSet(&v0->interaction, v1) == 0) {
                v0->interaction.chattedWithCurrent = 1;
            } else {
                v0->interaction.chattedWithCurrent = 0;
            }

            v0->interaction.state = 2;
        } else {
            WiFiPlazaLobby_State_ResetInteraction(&v0->interaction);
        }

        WiFiPlazaLobby_State_StopInteractionTimer(&v0->interaction);
    } else {
        (void)0;
    }
}

static void WiFiPlazaLobby_State_HandleInteractionResult(s32 param0, const void *param1, u32 param2, void *param3)
{
    WiFiPlazaLobbyState *v0 = param3;
    u32 v1;
    const WiFiPlazaLobbyInteractionData *v2;

    if (v0->interaction.phase == 0) {
        return;
    }

    v2 = param1;
    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    if (v0->interaction.partnerSlot == v1) {
        if ((v2->event == 2) || (v2->event == 3)) {
            v0->interaction.state = v2->event;

            v0->interaction.response = v2->value;

            WiFiPlazaLobby_State_StopInteractionTimer(&v0->interaction);
        } else {
            WiFiPlazaLobby_State_AbortInteraction(&v0->interaction);
        }
    } else {
        if (v1 == 0xffffffff) {
            WiFiPlazaLobby_State_AbortInteraction(&v0->interaction);
        }
    }
}

static void WiFiPlazaLobby_State_HandleInteractionEnd(s32 param0, const void *param1, u32 param2, void *param3)
{
    WiFiPlazaLobbyState *v0 = param3;
    u32 v1;

    if (v0->interaction.state == 0) {
        return;
    }

    v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    if (v0->interaction.partnerSlot == v1) {
        WiFiPlazaLobby_State_ResetInteraction(&v0->interaction);
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

    v2[v1->kind](v0, v1);
}

static void WiFiPlazaLobby_State_MarkPlayerFlag(s32 param0, const void *param1, u32 param2, void *param3)
{
    WiFiPlazaLobbyState *v0 = param3;
    u32 v1 = WiFiPlazaLobby_Network_FindMainPlayerIndex(param0);

    if (v1 != 0xffffffff) {
        v0->playerFlags.cosmeticKnown[v1] = 1;
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
            v2 = WiFiPlazaLobby_State_FindFreeMinigameSlot(&v0->minigameGrid, v1, v3);

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
        WiFiPlazaLobby_State_SetMinigameSlotFlag(&v0->minigameGrid, v1);
    }
}

static void WiFiPlazaLobby_State_ResetMinigameWeights(WiFiPlazaLobbyMinigameWeights *param0)
{
    int v0;

    memset(param0, 0, sizeof(WiFiPlazaLobbyMinigameWeights));

    for (v0 = 0; v0 < (27 / 3); v0++) {
        param0->groupWeights[v0] = 100;
    }
}

static void WiFiPlazaLobby_State_ReduceMinigameWeight(WiFiPlazaLobbyMinigameWeights *param0, u32 param1, u32 param2)
{
    u32 v0;
    int v1;

    GF_ASSERT(param2 < 20);
    GF_ASSERT(param1 < 27);

    if (param0->playerReduced[param2] == 0) {
        v0 = param1 / 3;
        param0->groupWeights[v0] /= 2;
        param0->playerReduced[param2] = 1;
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
        v1 += param0->groupWeights[v0];
    }

    v3 = MTRNG_Next() % v1;
    v2 = 0;

    for (v0 = 0; v0 < (27 / 3); v0++) {
        if ((v2 <= v3) && ((v2 + param0->groupWeights[v0]) > v3)) {
            return v0 * 3;
        }

        v2 += param0->groupWeights[v0];
    }

    GF_ASSERT(FALSE);
    return 0;
}

static void WiFiPlazaLobby_State_SetPendingNewsPlayerFlag(WiFiPlazaLobbyNewsPlayerFlags *param0, u32 param1, BOOL param2)
{
    GF_ASSERT(param1 < 20);

    if (param1 < 20) {
        param0->flags[param1] = param2;
    }
}

static BOOL WiFiPlazaLobby_State_GetPendingNewsPlayerFlag(const WiFiPlazaLobbyNewsPlayerFlags *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param1 < 20) {
        return param0->flags[param1];
    }

    return 0;
}

static void WiFiPlazaLobby_State_InitPasswordState(WiFiPlazaLobbyPasswordState *param0, u32 param1)
{
    MI_CpuClear8(param0, sizeof(WiFiPlazaLobbyPasswordState));
    param0->wordBank = PasswordWordBank_New(param1);
}

static void WiFiPlazaLobby_State_FreePasswordState(WiFiPlazaLobbyPasswordState *param0)
{
    PasswordWordBank_Free(param0->wordBank);
}

static void WiFiPlazaLobby_State_SetPasswordEntry(WiFiPlazaLobbyPasswordState *param0, u32 param1, BOOL param2, u32 param3)
{
    GF_ASSERT(param1 < 20);

    if (param1 < 20) {
        param0->hasPassword[param1] = param2;

        if (param2 == 1) {
            WiFiPlazaLobby_State_GeneratePasswordWords(param0->wordBank, param3, &param0->passwords[param1]);
        }
    }
}

static BOOL WiFiPlazaLobby_State_GetPasswordEntryFlag(const WiFiPlazaLobbyPasswordState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param1 < 20) {
        return param0->hasPassword[param1];
    }

    return 0;
}

static const WiFiPlazaLobbyPasswordWords *WiFiPlazaLobby_State_GetPasswordEntry(const WiFiPlazaLobbyPasswordState *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param1 < 20) {
        if (param0->hasPassword[param1]) {
            return &param0->passwords[param1];
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
    param2->words[0] = PasswordWordBank_GetWordAtIndex(param0, v2);

    v2 = (v0.val2[0] + v0.val2[1]) % v1;
    param2->words[1] = PasswordWordBank_GetWordAtIndex(param0, v2);

    v2 = (v0.val2[1] + v0.val2[2]) % v1;
    param2->words[2] = PasswordWordBank_GetWordAtIndex(param0, v2);

    v2 = (v0.val2[2] + v0.val2[3]) % v1;
    param2->words[3] = PasswordWordBank_GetWordAtIndex(param0, v2);
}

static void WiFiPlazaLobby_State_InitEventTimer(WiFiPlazaLobbyEventTimer *param0, u32 param1, u32 param2)
{
    param0->active = 0;
    param0->elapsedFrames = 0;
    param0->maxFrames = (param2 - param1) * 30;
}

static void WiFiPlazaLobby_State_StartEventTimer(WiFiPlazaLobbyEventTimer *param0)
{
    param0->active = 1;
    param0->elapsedFrames = 0;

    WiFiPlazaLobby_Network_GetCurrentTime(&param0->startTime);
}

static void WiFiPlazaLobby_State_UpdateEventTimer(WiFiPlazaLobbyEventTimer *param0)
{
    s64 v0;
    s64 v1;

    if (param0->active) {
        WiFiPlazaLobby_Network_GetCurrentTime(&v0);
        v1 = v0 - param0->startTime;

        if (param0->elapsedFrames < (v1 * 30)) {
            param0->elapsedFrames = (v1 * 30);
        }

        if (param0->elapsedFrames < param0->maxFrames) {
            param0->elapsedFrames++;

            {
                u32 v2;
                u32 v3;
                int v4;

                v2 = (param0->elapsedFrames * 256) / param0->maxFrames;
                v3 = 0;

                for (v4 = 0; v4 < NELEMS(sEventTimerStages); v4++) {
                    v3 += sEventTimerStages[v4].threshold;

                    if (v3 >= v2) {
                        if (param0->stage != sEventTimerStages[v4].stage) {
                            param0->stage = sEventTimerStages[v4].stage;
                            param0->stageFrames = 0;
                        }

                        break;
                    }
                }
            }
        } else {
            if (param0->stage != 5) {
                param0->stage = 5;
                param0->stageFrames = 0;
            }

            if (param0->stageFrames >= 120) {
                param0->stage = 0;
                param0->active = 0;
            }
        }

        param0->stageFrames++;
    }
}

static u32 WiFiPlazaLobby_State_GetEventTimerCounter(const WiFiPlazaLobbyEventTimer *param0)
{
    return param0->stageFrames;
}

static int WiFiPlazaLobby_State_GetEventTimerStage(const WiFiPlazaLobbyEventTimer *param0)
{
    return param0->stage;
}

static void WiFiPlazaLobby_State_InitRecentPlayers(WiFiPlazaLobbyRecentPlayers *param0, const SaveData *saveData)
{
    int v0;

    for (v0 = 0; v0 < (12 + 1); v0++) {
        param0->appearances[v0] = 24;
        param0->userIDs[v0] = DWC_LOBBY_INVALID_USER_ID;
    }

    param0->head = 0;
    param0->tail = 0;
    param0->saveData = saveData;

    WiFiPlazaLobby_State_UpdateRecentPlayersChecksum(param0);
}

static void WiFiPlazaLobby_State_PushRecentPlayer(WiFiPlazaLobbyRecentPlayers *param0, int param1, s32 param2)
{
    WiFiPlazaLobby_State_ValidateRecentPlayersChecksum(param0);

    if (((param0->tail + 1) % (12 + 1)) == param0->head) {
        WiFiPlazaLobby_State_PopRecentPlayer(param0);
    }

    param0->appearances[param0->tail] = param1;
    param0->userIDs[param0->tail] = param2;
    param0->tail = (param0->tail + 1) % (12 + 1);

    WiFiPlazaLobby_State_UpdateRecentPlayersChecksum(param0);
}

static BOOL WiFiPlazaLobby_State_ReplaceRecentPlayer(WiFiPlazaLobbyRecentPlayers *param0, s32 param1, s32 param2)
{
    int v0;
    BOOL v1 = 0;

    WiFiPlazaLobby_State_ValidateRecentPlayersChecksum(param0);

    for (v0 = 0; v0 < (12 + 1); v0++) {
        if (param0->userIDs[v0] == param1) {
            param0->userIDs[v0] = param2;
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

    if (param0->tail == param0->head) {
        return 24;
    }

    v0 = param0->appearances[param0->head];

    param0->appearances[param0->head] = 24;
    param0->userIDs[param0->tail] = DWC_LOBBY_INVALID_USER_ID;
    param0->head = (param0->head + 1) % (12 + 1);

    WiFiPlazaLobby_State_UpdateRecentPlayersChecksum(param0);

    return v0;
}

static int WiFiPlazaLobby_State_GetRecentPlayerAppearance(WiFiPlazaLobbyRecentPlayers *param0, u32 param1)
{
    s32 v0;

    GF_ASSERT(param1 < 12);

    WiFiPlazaLobby_State_ValidateRecentPlayersChecksum(param0);

    param1++;
    v0 = param0->tail - param1;

    if (v0 < 0) {
        v0 += (12 + 1);
    }

    return param0->appearances[v0];
}

static s32 WiFiPlazaLobby_State_GetRecentPlayerID(WiFiPlazaLobbyRecentPlayers *param0, u32 param1)
{
    s32 v0;

    GF_ASSERT(param1 < 12);

    WiFiPlazaLobby_State_ValidateRecentPlayersChecksum(param0);

    param1++;
    v0 = param0->tail - param1;

    if (v0 < 0) {
        v0 += (12 + 1);
    }

    return param0->userIDs[v0];
}

static void WiFiPlazaLobby_State_UpdateRecentPlayersChecksum(WiFiPlazaLobbyRecentPlayers *param0)
{
    param0->checksum = SaveData_CalculateChecksum(param0->saveData, param0, (sizeof(WiFiPlazaLobbyRecentPlayers) - 8));
}

static void WiFiPlazaLobby_State_ValidateRecentPlayersChecksum(WiFiPlazaLobbyRecentPlayers *param0)
{
    u32 v0 = SaveData_CalculateChecksum(param0->saveData, param0, (sizeof(WiFiPlazaLobbyRecentPlayers) - 8));

    if (v0 != param0->checksum) {
        GF_ASSERT(FALSE);
        param0->checksumError = 1;
    }
}

static BOOL WiFiPlazaLobby_State_HasRecentPlayersChecksumError(const WiFiPlazaLobbyRecentPlayers *param0)
{
    return param0->checksumError;
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
