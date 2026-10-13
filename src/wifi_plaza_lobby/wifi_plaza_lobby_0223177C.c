#include "wifi_plaza_lobby/wifi_plaza_lobby_0223177C.h"

#include <nitro.h>
#include <string.h>

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231428.h"
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

#include "enums.h"
#include "heap.h"
#include "message.h"
#include "string_gf.h"
#include "string_template.h"
#include "trainer_info.h"

typedef struct {
    u16 value;
    u16 flags;
} WiFiPlazaLobbyNewsResultSlot;

typedef struct {
    WiFiPlazaLobbyNewsResultSlot slots[20];
    u16 state;
    u16 currentIndex;
} WiFiPlazaLobbyNewsResult;

typedef struct WiFiPlazaLobbyNewsHeadline_t {
    u8 type;
    u32 values[3];
    String *names[4];
    u16 extraValues[4];
    u16 priority;
    s16 lifetime;
    struct WiFiPlazaLobbyNewsHeadline_t *next;
    struct WiFiPlazaLobbyNewsHeadline_t *prev;
} WiFiPlazaLobbyNewsHeadline;

typedef struct {
    WiFiPlazaLobbyNewsHeadline headlines[8];
    WiFiPlazaLobbyNewsHeadline head;
} WiFiPlazaLobbyNewsHeadlineQueue;

typedef struct WiFiPlazaLobbyNews_t {
    WiFiPlazaLobbyTime plazaTime;
    BOOL plazaInfoValid;
    WiFiPlazaLobbyNewsResult result;
    WiFiPlazaLobbyNewsHeadlineQueue headlineQueue;
} WiFiPlazaLobbyNews;

static void WiFiPlazaLobby_News_InitResult(WiFiPlazaLobbyNewsResult *param0);
static void WiFiPlazaLobby_News_SetResultSlot(WiFiPlazaLobbyNewsResult *param0, u32 param1, u32 param2, WiFiPlazaLobbyNewsResultFlags param3);
static void WiFiPlazaLobby_News_SetResultSlotAndSelect(WiFiPlazaLobbyNewsResult *param0, u32 param1, u32 param2, WiFiPlazaLobbyNewsResultFlags param3);
static void WiFiPlazaLobby_News_ClearResultSlot(WiFiPlazaLobbyNewsResult *param0, u32 param1);
static void WiFiPlazaLobby_News_SetResultSlotFlags(WiFiPlazaLobbyNewsResult *param0, u32 param1, WiFiPlazaLobbyNewsResultFlags param2);
static void WiFiPlazaLobby_News_SetStateValue(WiFiPlazaLobbyNewsResult *param0, WiFiPlazaLobbyNewsState param1);
static void WiFiPlazaLobby_News_SetCurrentIndex(WiFiPlazaLobbyNewsResult *param0, u32 param1);
static BOOL WiFiPlazaLobby_News_ResultSlotIsSet(const WiFiPlazaLobbyNewsResult *param0, u32 param1);
static u32 WiFiPlazaLobby_News_GetResultSlotValue(const WiFiPlazaLobbyNewsResult *param0, u32 param1);
static BOOL WiFiPlazaLobby_News_ResultSlotHasFlag(const WiFiPlazaLobbyNewsResult *param0, u32 param1);
static BOOL WiFiPlazaLobby_News_ResultSlotHasNewFlag(const WiFiPlazaLobbyNewsResult *param0, u32 param1);
static WiFiPlazaLobbyNewsResultFlags WiFiPlazaLobby_News_GetResultSlotFlags(const WiFiPlazaLobbyNewsResult *param0, u32 param1);
static WiFiPlazaLobbyNewsState WiFiPlazaLobby_News_GetStateValue(const WiFiPlazaLobbyNewsResult *param0);
static BOOL WiFiPlazaLobby_News_ResultSlotIsCurrent(const WiFiPlazaLobbyNewsResult *param0, u32 param1);
static void WiFiPlazaLobby_News_InitHeadlineQueue(WiFiPlazaLobbyNewsHeadlineQueue *param0, u32 heapID);
static void WiFiPlazaLobby_News_FreeHeadlineQueue(WiFiPlazaLobbyNewsHeadlineQueue *param0);
static void WiFiPlazaLobby_News_AgeHeadlineQueue(WiFiPlazaLobbyNewsHeadlineQueue *param0);
static void WiFiPlazaLobby_News_RemoveFrontHeadline(WiFiPlazaLobbyNewsHeadlineQueue *param0);
static WiFiPlazaLobbyNewsHeadline *WiFiPlazaLobby_News_AllocHeadline(WiFiPlazaLobbyNewsHeadlineQueue *param0, u16 param1);
static void WiFiPlazaLobby_News_InsertHeadlineBefore(WiFiPlazaLobbyNewsHeadline *param0, WiFiPlazaLobbyNewsHeadline *param1);
static void WiFiPlazaLobby_News_InsertHeadline(WiFiPlazaLobbyNewsHeadlineQueue *param0, WiFiPlazaLobbyNewsHeadline *param1);
static void WiFiPlazaLobby_News_UnlinkHeadline(WiFiPlazaLobbyNewsHeadlineQueue *param0, WiFiPlazaLobbyNewsHeadline *param1);
static void WiFiPlazaLobby_News_SetHeadlineData(WiFiPlazaLobbyNewsHeadline *param0, u32 param1, u32 param2, u32 param3, const TrainerInfo *param4, const TrainerInfo *param5, const TrainerInfo *param6, const TrainerInfo *param7, u16 param8, u16 param9, u16 param10, u16 param11, u32 param12, u32 param13, u32 param14);
static BOOL WiFiPlazaLobby_News_FormatHeadlineType0(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5);
static BOOL WiFiPlazaLobby_News_FormatHeadlineType1(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5);
static BOOL WiFiPlazaLobby_News_FormatHeadlineType2(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5);
static BOOL WiFiPlazaLobby_News_FormatHeadlineType3(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5);
static BOOL WiFiPlazaLobby_News_FormatHeadlineType4(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5);
static BOOL WiFiPlazaLobby_News_FormatHeadlineType6(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5);
static BOOL WiFiPlazaLobby_News_FormatHeadlineType7(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5);
static BOOL WiFiPlazaLobby_News_FormatHeadlineType8(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5);
static u32 WiFiPlazaLobby_News_GetHeadlineValueType0(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1);
static u32 WiFiPlazaLobby_News_GetHeadlineValueType1(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1);
static u32 WiFiPlazaLobby_News_GetHeadlineValueType2(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1);
static u32 WiFiPlazaLobby_News_GetHeadlineValueType3(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1);
static u32 WiFiPlazaLobby_News_GetHeadlineValueType4(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1);
static u32 WiFiPlazaLobby_News_GetHeadlineValueType6(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1);
static u32 WiFiPlazaLobby_News_GetHeadlineValueType7(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1);
static u32 WiFiPlazaLobby_News_GetHeadlineValueType8(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1);
static BOOL WiFiPlazaLobby_News_IsValidMinigameCount(enum PlazaMinigame param0, u32 param1);

WiFiPlazaLobbyNews *WiFiPlazaLobby_News_New(u32 heapID)
{
    WiFiPlazaLobbyNews *v0 = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyNews));
    memset(v0, 0, sizeof(WiFiPlazaLobbyNews));

    WiFiPlazaLobby_News_InitResult(&v0->result);
    WiFiPlazaLobby_News_InitHeadlineQueue(&v0->headlineQueue, heapID);

    return v0;
}

void WiFiPlazaLobby_News_Free(WiFiPlazaLobbyNews *param0)
{
    WiFiPlazaLobby_News_FreeHeadlineQueue(&param0->headlineQueue);
    Heap_Free(param0);
}

void WiFiPlazaLobby_News_Reset(WiFiPlazaLobbyNews *param0)
{
    WiFiPlazaLobby_News_AgeHeadlineQueue(&param0->headlineQueue);
    WiFiPlazaLobby_News_SetStateValue(&param0->result, WiFiPlazaLobbyNewsState_00);
}

void WiFiPlazaLobby_News_SetPlazaInfo(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyTime *param1)
{
    param0->plazaTime = *param1;
    param0->plazaInfoValid = 1;
}

void WiFiPlazaLobby_News_SetResult(WiFiPlazaLobbyNews *param0, u32 param1, u32 param2, WiFiPlazaLobbyNewsResultFlags param3)
{
    WiFiPlazaLobby_News_SetResultSlotAndSelect(&param0->result, param1, param2, param3);
}

BOOL WiFiPlazaLobby_News_TakeResultFlag(WiFiPlazaLobbyNews *param0, u32 param1)
{
    BOOL v0 = WiFiPlazaLobby_News_ResultSlotHasNewFlag(&param0->result, param1);
    WiFiPlazaLobby_News_ClearResultSlot(&param0->result, param1);

    return v0;
}

void WiFiPlazaLobby_News_SelectResult(WiFiPlazaLobbyNews *param0, u32 param1)
{
    u32 v0;
    int v1;

    for (v1 = 0; v1 < 20; v1++) {
        v0 = WiFiPlazaLobby_News_GetResultSlotFlags(&param0->result, v1);

        if (v0 & WiFiPlazaLobbyNewsResultFlags_02) {
            v0 &= ~WiFiPlazaLobbyNewsResultFlags_02;
            WiFiPlazaLobby_News_SetResultSlotFlags(&param0->result, v1, v0);
        }
    }

    v0 = WiFiPlazaLobby_News_GetResultSlotFlags(&param0->result, param1);
    WiFiPlazaLobby_News_SetResultSlotFlags(&param0->result, param1, v0 | WiFiPlazaLobbyNewsResultFlags_02);
}

void WiFiPlazaLobby_News_AddDuoEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsDuoEntry *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->headlineQueue, 8);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, 0, 0, 0, param1->trainerInfo1, param1->trainerInfo2, NULL, NULL, param1->slot1, param1->slot2, 0, 0, 600, 8, 0);
    WiFiPlazaLobby_News_InsertHeadline(&param0->headlineQueue, v0);
}

void WiFiPlazaLobby_News_AddDuoEntryRanked(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsDuoEntryRanked *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0;

    if (param1->rank >= 27) {
        return;
    }

    v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->headlineQueue, 7);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, param1->rank, 0, 0, param1->trainerInfo1, param1->trainerInfo2, NULL, NULL, param1->slot1, param1->slot2, 0, 0, 600, 7, 1);
    WiFiPlazaLobby_News_InsertHeadline(&param0->headlineQueue, v0);
}

void WiFiPlazaLobby_News_AddMinigameEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsMinigameEntry *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0;
    u32 v1;
    static const sc_NEWS_DSET_MINIGAME_PRI[WiFiPlazaLobbyActivity_12] = {
        4,
        3,
        2,
    };

    if ((param1->minigame != WiFiPlazaLobbyActivity_00) && (param1->minigame != WiFiPlazaLobbyActivity_01) && (param1->minigame != WiFiPlazaLobbyActivity_02)) {
        return;
    }

    if (param1->isRanked == 1) {
        if ((param1->count < 2) || (param1->count > 4)) {
            return;
        }
    } else {
        if ((param1->count < 1) || (param1->count > 4)) {
            return;
        }
    }

    v1 = param1->minigame - WiFiPlazaLobbyActivity_00;
    v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->headlineQueue, sc_NEWS_DSET_MINIGAME_PRI[v1]);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, v1, param1->count, param1->isRanked, param1->trainerInfo0, param1->trainerInfo1, param1->trainerInfo2, param1->trainerInfo3, param1->slot0, param1->slot1, param1->slot2, param1->slot3, 900, sc_NEWS_DSET_MINIGAME_PRI[v1], 2);
    WiFiPlazaLobby_News_InsertHeadline(&param0->headlineQueue, v0);
}

void WiFiPlazaLobby_News_AddMinigameQuickEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsMinigameQuickEntry *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0;

    if ((param1->minigame != WiFiPlazaLobbyActivity_03) && (param1->minigame != WiFiPlazaLobbyActivity_04)) {
        return;
    }

    v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->headlineQueue, 5 + param1->minigame);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, param1->minigame, param1->count, 0, param1->trainerInfo, NULL, NULL, NULL, param1->slot, 0, 0, 0, 900, 5 + param1->minigame, 3);
    WiFiPlazaLobby_News_InsertHeadline(&param0->headlineQueue, v0);
}

void WiFiPlazaLobby_News_AddFourTrainerEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsFourTrainerEntry *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->headlineQueue, 12);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, param1->count, 0, 0, param1->trainerInfo0, param1->trainerInfo1, param1->trainerInfo2, param1->trainerInfo3, param1->slot0, param1->slot1, param1->slot2, param1->slot3, 450, 12, 4);
    WiFiPlazaLobby_News_InsertHeadline(&param0->headlineQueue, v0);
}

void WiFiPlazaLobby_News_AddFourTrainerEntryB(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsFourTrainerEntryB *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->headlineQueue, 13);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, param1->count, 0, 0, param1->trainerInfo0, param1->trainerInfo1, param1->trainerInfo2, param1->trainerInfo3, param1->slot0, param1->slot1, param1->slot2, param1->slot3, 450, 13, 5);
    WiFiPlazaLobby_News_InsertHeadline(&param0->headlineQueue, v0);
}

void WiFiPlazaLobby_News_AddEventEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsEventEntry *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0;

    switch (param1->event) {
    case 0:
    case 1:
    case 2:
    case 4:
        break;
    default:
        return;
    }

    v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->headlineQueue, 14);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, param1->time->value, param1->event, 0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 900, 14, 6);
    WiFiPlazaLobby_News_InsertHeadline(&param0->headlineQueue, v0);
}

void WiFiPlazaLobby_News_AddTrainerEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsTrainerEntry *param1, const WiFiPlazaLobbyNewsPlayerFlags *param2)
{
    WiFiPlazaLobbyNewsHeadline *v0;
    int v1;

    if (param1->slot >= 20) {
        return;
    }

    if (param2->flags[param1->slot] == 0) {
        return;
    }

    v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->headlineQueue, 1);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, param1->slot, 0, 0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 1800, 1, 7);
    WiFiPlazaLobby_News_InsertHeadline(&param0->headlineQueue, v0);
}

void WiFiPlazaLobby_News_AddMinigameResultEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsMinigameResultEntry *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0;
    u32 v1;
    static const u8 v2[3] = {
        11,
        10,
        9,
    };

    if ((param1->minigame != WiFiPlazaLobbyActivity_00) && (param1->minigame != WiFiPlazaLobbyActivity_01) && (param1->minigame != WiFiPlazaLobbyActivity_02)) {
        return;
    }

    if (WiFiPlazaLobby_News_IsValidMinigameCount(param1->minigame, param1->count) == 0) {
        return;
    }

    v1 = param1->minigame - WiFiPlazaLobbyActivity_00;
    v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->headlineQueue, v2[v1]);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, v1, param1->count, 0, param1->trainerInfo0, param1->trainerInfo1, param1->trainerInfo2, param1->trainerInfo3, param1->slot0, param1->slot1, param1->slot2, param1->slot3, 450, v2[v1], 8);
    WiFiPlazaLobby_News_InsertHeadline(&param0->headlineQueue, v0);
}

void WiFiPlazaLobby_News_ClearQueue(WiFiPlazaLobbyNews *param0)
{
    WiFiPlazaLobby_News_RemoveFrontHeadline(&param0->headlineQueue);
}

BOOL WiFiPlazaLobby_News_GetPlazaInfo(const WiFiPlazaLobbyNews *param0, WiFiPlazaLobbyTime *param1)
{
    *param1 = param0->plazaTime;
    return param0->plazaInfoValid;
}

BOOL WiFiPlazaLobby_News_IsResultSet(const WiFiPlazaLobbyNews *param0, u32 param1)
{
    return WiFiPlazaLobby_News_ResultSlotIsSet(&param0->result, param1);
}

u32 WiFiPlazaLobby_News_GetResult(const WiFiPlazaLobbyNews *param0, u32 param1)
{
    return WiFiPlazaLobby_News_GetResultSlotValue(&param0->result, param1);
}

BOOL WiFiPlazaLobby_News_HasResultFlag(const WiFiPlazaLobbyNews *param0, u32 param1)
{
    return WiFiPlazaLobby_News_ResultSlotHasFlag(&param0->result, param1);
}

BOOL WiFiPlazaLobby_News_HasNewResultFlag(const WiFiPlazaLobbyNews *param0, u32 param1)
{
    return WiFiPlazaLobby_News_ResultSlotHasNewFlag(&param0->result, param1);
}

BOOL WiFiPlazaLobby_News_IsCurrentResult(const WiFiPlazaLobbyNews *param0, u32 param1)
{
    return WiFiPlazaLobby_News_ResultSlotIsCurrent(&param0->result, param1);
}

WiFiPlazaLobbyNewsState WiFiPlazaLobby_News_GetState(const WiFiPlazaLobbyNews *param0)
{
    return WiFiPlazaLobby_News_GetStateValue(&param0->result);
}

BOOL WiFiPlazaLobby_News_HasHeadline(const WiFiPlazaLobbyNews *param0)
{
    if (param0->headlineQueue.head.next != &param0->headlineQueue.head) {
        return 1;
    }

    return 0;
}

int WiFiPlazaLobby_News_GetHeadlineType(const WiFiPlazaLobbyNews *param0)
{
    GF_ASSERT(WiFiPlazaLobby_News_HasHeadline(param0));
    return param0->headlineQueue.head.next->type;
}

BOOL WiFiPlazaLobby_News_FormatHeadline(const WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, int param2, String *param3, u32 heapID)
{
    StringTemplate *v0;
    MessageLoader *v1;
    WiFiPlazaLobbyNewsHeadline *v2;
    BOOL v3;

    static BOOL (*const v4[])(WiFiPlazaLobbyNewsHeadline *, const WiFiPlazaLobbyNewsPlayerFlags *, StringTemplate *, MessageLoader *, String *, u32) = {
        WiFiPlazaLobby_News_FormatHeadlineType0,
        WiFiPlazaLobby_News_FormatHeadlineType1,
        WiFiPlazaLobby_News_FormatHeadlineType2,
        WiFiPlazaLobby_News_FormatHeadlineType3,
        WiFiPlazaLobby_News_FormatHeadlineType4,
        WiFiPlazaLobby_News_FormatHeadlineType4,
        WiFiPlazaLobby_News_FormatHeadlineType6,
        WiFiPlazaLobby_News_FormatHeadlineType7,
        WiFiPlazaLobby_News_FormatHeadlineType8,
    };

    GF_ASSERT(WiFiPlazaLobby_News_HasHeadline(param0));

    v2 = param0->headlineQueue.head.next;
    v1 = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0653, heapID);
    v0 = StringTemplate_Default(heapID);

    if (v2->type < 9) {
        v3 = v4[v2->type](v2, param1, v0, v1, param3, heapID);
    } else {
        v3 = 0;
    }

    MessageLoader_Free(v1);
    StringTemplate_Free(v0);

    return v3;
}

u32 WiFiPlazaLobby_News_GetHeadlineValue(const WiFiPlazaLobbyNews *param0, int param1, u32 param2)
{
    WiFiPlazaLobbyNewsHeadline *v0;
    u32 v1;

    static u32 (*const v2[])(const WiFiPlazaLobbyNewsHeadline *, u32) = {
        WiFiPlazaLobby_News_GetHeadlineValueType0,
        WiFiPlazaLobby_News_GetHeadlineValueType1,
        WiFiPlazaLobby_News_GetHeadlineValueType2,
        WiFiPlazaLobby_News_GetHeadlineValueType3,
        WiFiPlazaLobby_News_GetHeadlineValueType4,
        WiFiPlazaLobby_News_GetHeadlineValueType4,
        WiFiPlazaLobby_News_GetHeadlineValueType6,
        WiFiPlazaLobby_News_GetHeadlineValueType7,
        WiFiPlazaLobby_News_GetHeadlineValueType8,
    };

    GF_ASSERT(WiFiPlazaLobby_News_HasHeadline(param0));

    v0 = param0->headlineQueue.head.next;

    if (v0->type < 9) {
        v1 = v2[v0->type](v0, param2);
    } else {
        GF_ASSERT(FALSE);
        v1 = 20;
    }

    return v1;
}

static void WiFiPlazaLobby_News_InitResult(WiFiPlazaLobbyNewsResult *param0)
{
    int v0;

    for (v0 = 0; v0 < 20; v0++) {
        WiFiPlazaLobby_News_SetResultSlot(param0, v0, 2, 0);
    }
}

static void WiFiPlazaLobby_News_SetResultSlot(WiFiPlazaLobbyNewsResult *param0, u32 param1, u32 param2, WiFiPlazaLobbyNewsResultFlags param3)
{
    GF_ASSERT(param1 < 20);
    param0->slots[param1].value = param2;
    param0->slots[param1].flags = param3;
}

static void WiFiPlazaLobby_News_SetResultSlotAndSelect(WiFiPlazaLobbyNewsResult *param0, u32 param1, u32 param2, WiFiPlazaLobbyNewsResultFlags param3)
{
    WiFiPlazaLobby_News_SetResultSlot(param0, param1, param2, param3);
    WiFiPlazaLobby_News_SetStateValue(param0, WiFiPlazaLobbyNewsState_01);
    WiFiPlazaLobby_News_SetCurrentIndex(param0, param1);
}

static void WiFiPlazaLobby_News_ClearResultSlot(WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    WiFiPlazaLobby_News_SetResultSlot(param0, param1, 2, 0);
    WiFiPlazaLobby_News_SetStateValue(param0, WiFiPlazaLobbyNewsState_02);
}

static void WiFiPlazaLobby_News_SetResultSlotFlags(WiFiPlazaLobbyNewsResult *param0, u32 param1, WiFiPlazaLobbyNewsResultFlags param2)
{
    GF_ASSERT(param1 < 20);
    param0->slots[param1].flags = param2;
}

static void WiFiPlazaLobby_News_SetStateValue(WiFiPlazaLobbyNewsResult *param0, WiFiPlazaLobbyNewsState param1)
{
    GF_ASSERT(param1 <= WiFiPlazaLobbyNewsResultFlags_02);
    param0->state = param1;
}

static void WiFiPlazaLobby_News_SetCurrentIndex(WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    param0->currentIndex = param1;
}

static BOOL WiFiPlazaLobby_News_ResultSlotIsSet(const WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    u32 v0 = WiFiPlazaLobby_News_GetResultSlotValue(param0, param1);

    if (v0 == 2) {
        return 0;
    }

    return 1;
}

static u32 WiFiPlazaLobby_News_GetResultSlotValue(const WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    return param0->slots[param1].value;
}

static BOOL WiFiPlazaLobby_News_ResultSlotHasFlag(const WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param0->slots[param1].flags & WiFiPlazaLobbyNewsResultFlags_01) {
        return 1;
    }

    return 0;
}

static BOOL WiFiPlazaLobby_News_ResultSlotHasNewFlag(const WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param0->slots[param1].flags & WiFiPlazaLobbyNewsResultFlags_02) {
        return 1;
    }

    return 0;
}

static WiFiPlazaLobbyNewsResultFlags WiFiPlazaLobby_News_GetResultSlotFlags(const WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    return param0->slots[param1].flags;
}

static WiFiPlazaLobbyNewsState WiFiPlazaLobby_News_GetStateValue(const WiFiPlazaLobbyNewsResult *param0)
{
    return param0->state;
}

static BOOL WiFiPlazaLobby_News_ResultSlotIsCurrent(const WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param0->currentIndex == param1) {
        return 1;
    }

    return 0;
}

static void WiFiPlazaLobby_News_InitHeadlineQueue(WiFiPlazaLobbyNewsHeadlineQueue *param0, u32 heapID)
{
    int v0, v1;

    memset(param0, 0, sizeof(WiFiPlazaLobbyNewsHeadlineQueue));

    for (v0 = 0; v0 < 8; v0++) {
        for (v1 = 0; v1 < 4; v1++) {
            param0->headlines[v0].names[v1] = String_Init((7 + 1), heapID);
        }
    }

    param0->head.next = &param0->head;
    param0->head.prev = &param0->head;
}

static void WiFiPlazaLobby_News_FreeHeadlineQueue(WiFiPlazaLobbyNewsHeadlineQueue *param0)
{
    int v0, v1;

    for (v0 = 0; v0 < 8; v0++) {
        for (v1 = 0; v1 < 4; v1++) {
            String_Free(param0->headlines[v0].names[v1]);
        }
    }

    memset(param0, 0, sizeof(WiFiPlazaLobbyNewsHeadlineQueue));
}

static void WiFiPlazaLobby_News_AgeHeadlineQueue(WiFiPlazaLobbyNewsHeadlineQueue *param0)
{
    WiFiPlazaLobbyNewsHeadline *v0;
    WiFiPlazaLobbyNewsHeadline *v1 = param0->head.next;

    while (v1 != &param0->head) {
        v0 = v1->next;
        v1->priority = 0;

        if ((v1->lifetime - 1) > 0) {
            v1->lifetime--;
        } else {
            WiFiPlazaLobby_News_UnlinkHeadline(param0, v1);
        }

        v1 = v0;
    }
}

static void WiFiPlazaLobby_News_RemoveFrontHeadline(WiFiPlazaLobbyNewsHeadlineQueue *param0)
{
    WiFiPlazaLobby_News_UnlinkHeadline(param0, param0->head.next);
}

static WiFiPlazaLobbyNewsHeadline *WiFiPlazaLobby_News_AllocHeadline(WiFiPlazaLobbyNewsHeadlineQueue *param0, u16 param1)
{
    int v0;
    WiFiPlazaLobbyNewsHeadline *v1 = NULL;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->headlines[v0].next == NULL) {
            v1 = &param0->headlines[v0];
            break;
        }
    }

    if (v1 == NULL) {
        for (v0 = 0; v0 < 8; v0++) {
            if (param0->headlines[v0].priority >= param1) {
                WiFiPlazaLobby_News_UnlinkHeadline(param0, &param0->headlines[v0]);
                v1 = &param0->headlines[v0];
                break;
            }
        }
    }

    return v1;
}

static void WiFiPlazaLobby_News_InsertHeadlineBefore(WiFiPlazaLobbyNewsHeadline *param0, WiFiPlazaLobbyNewsHeadline *param1)
{
    param1->next = param0->next;
    param1->prev = param0;
    param0->next = param1;
    param1->next->prev = param1;
}

static void WiFiPlazaLobby_News_InsertHeadline(WiFiPlazaLobbyNewsHeadlineQueue *param0, WiFiPlazaLobbyNewsHeadline *param1)
{
    {
        WiFiPlazaLobbyNewsHeadline *v0;

        v0 = param0->head.prev;

        while (v0 != &param0->head) {
            if (v0->priority < param1->priority) {
                break;
            }

            v0 = v0->prev;
        }

        WiFiPlazaLobby_News_InsertHeadlineBefore(v0, param1);
    }
}

static void WiFiPlazaLobby_News_UnlinkHeadline(WiFiPlazaLobbyNewsHeadlineQueue *param0, WiFiPlazaLobbyNewsHeadline *param1)
{
    param1->prev->next = param1->next;
    param1->next->prev = param1->prev;
    param1->prev = NULL;
    param1->next = NULL;
}

static void WiFiPlazaLobby_News_SetHeadlineData(WiFiPlazaLobbyNewsHeadline *param0, u32 param1, u32 param2, u32 param3, const TrainerInfo *param4, const TrainerInfo *param5, const TrainerInfo *param6, const TrainerInfo *param7, u16 param8, u16 param9, u16 param10, u16 param11, u32 param12, u32 param13, u32 param14)
{
    GF_ASSERT(param14 < 9);
    param0->type = param14;
    param0->lifetime = param12;
    param0->priority = param13;
    param0->values[0] = param1;
    param0->values[1] = param2;
    param0->values[2] = param3;
    param0->extraValues[0] = param8;
    param0->extraValues[1] = param9;
    param0->extraValues[2] = param10;
    param0->extraValues[3] = param11;

    if (param4) {
        TrainerInfo_NameString(param4, param0->names[0]);
    }

    if (param5) {
        TrainerInfo_NameString(param5, param0->names[1]);
    }

    if (param6) {
        TrainerInfo_NameString(param6, param0->names[2]);
    }

    if (param7) {
        TrainerInfo_NameString(param7, param0->names[3]);
    }
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType0(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    String *v0;

    StringTemplate_SetString(param2, 0, param0->names[0], 0, 1, gGameLanguage);
    StringTemplate_SetString(param2, 1, param0->names[1], 0, 1, gGameLanguage);

    v0 = MessageLoader_GetNewString(param3, 7);

    StringTemplate_Format(param2, param4, v0);
    String_Free(v0);

    return 1;
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType1(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    String *v0;

    StringTemplate_SetString(param2, 0, param0->names[0], 0, 1, gGameLanguage);
    StringTemplate_SetString(param2, 1, param0->names[1], 0, 1, gGameLanguage);
    StringTemplate_SetPlazaItemName(param2, 2, param0->values[0]);

    v0 = MessageLoader_GetNewString(param3, 8);

    StringTemplate_Format(param2, param4, v0);
    String_Free(v0);

    return 1;
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType2(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    String *v0;

    StringTemplate_SetPlazaMinigameName(param2, 0, param0->values[0]);

    if (param0->values[2] == 1) {
        u32 v1;

        switch (param0->values[1]) {
        case 3:
            StringTemplate_SetString(param2, 1, param0->names[0], 0, 1, gGameLanguage);
            StringTemplate_SetString(param2, 2, param0->names[1], 0, 1, gGameLanguage);
            StringTemplate_SetString(param2, 3, param0->names[2], 0, 1, gGameLanguage);
            v1 = 18;
            break;
        case 2:
            StringTemplate_SetString(param2, 1, param0->names[0], 0, 1, gGameLanguage);
            StringTemplate_SetString(param2, 2, param0->names[1], 0, 1, gGameLanguage);
            v1 = 19;
            break;
        case 4:
            StringTemplate_SetString(param2, 1, param0->names[0], 0, 1, gGameLanguage);
            StringTemplate_SetString(param2, 2, param0->names[1], 0, 1, gGameLanguage);
            StringTemplate_SetString(param2, 3, param0->names[2], 0, 1, gGameLanguage);
            StringTemplate_SetString(param2, 4, param0->names[3], 0, 1, gGameLanguage);
            v1 = 6;
            break;
        default:
            return 0;
        }

        v0 = MessageLoader_GetNewString(param3, v1);
    } else {
        StringTemplate_SetString(param2, 1, param0->names[0], 0, 1, gGameLanguage);
        StringTemplate_SetNumber(param2, 2, 4 - param0->values[1], 1, 1, 1);

        v0 = MessageLoader_GetNewString(param3, 5);
    }

    StringTemplate_Format(param2, param4, v0);
    String_Free(v0);

    return 1;
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType3(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    String *v0;

    StringTemplate_SetPlazaMinigameName(param2, 0, param0->values[0]);
    StringTemplate_SetString(param2, 1, param0->names[0], 0, 1, gGameLanguage);
    StringTemplate_SetNumber(param2, 2, 8 - param0->values[1], 1, 1, 1);

    v0 = MessageLoader_GetNewString(param3, 9);

    StringTemplate_Format(param2, param4, v0);
    String_Free(v0);

    return 1;
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType4(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    String *v0;
    int v1;
    u32 v2;

    for (v1 = 0; v1 < param0->values[0]; v1++) {
        StringTemplate_SetString(param2, v1, param0->names[v1], 0, 1, gGameLanguage);
    }

    if (param0->type == 4) {
        StringTemplate_SetPlazaMinigameName(param2, param0->values[0], WiFiPlazaLobbyActivity_05);
    } else {
        StringTemplate_SetPlazaMinigameName(param2, param0->values[0], WiFiPlazaLobbyActivity_06);
    }

    v0 = MessageLoader_GetNewString(param3, 10 + (4 - param0->values[0]));

    StringTemplate_Format(param2, param4, v0);
    String_Free(v0);

    return 1;
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType6(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    String *v0;
    u32 v1;

    switch (param0->values[1]) {
    case 0:
        StringTemplate_SetPlazaEventName(param2, 0, 0);
        v1 = 15;
        break;
    case 1:
        StringTemplate_SetPlazaEventName(param2, 0, 1);
        v1 = 20;
        break;
    case 2:
        StringTemplate_SetPlazaEventName(param2, 0, 2);
        v1 = 16;
        break;

    case 4:
        v1 = 17;
        break;

    default:
        return 0;
    }

    v0 = MessageLoader_GetNewString(param3, v1);

    StringTemplate_Format(param2, param4, v0);
    String_Free(v0);

    return 1;
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType7(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    if (param0->values[0] >= 20) {
        return 0;
    }

    if (param1->flags[param0->values[0]] == 0) {
        return 0;
    }

    MessageLoader_GetString(param3, 21, param4);

    return 1;
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType8(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    String *v0;
    u32 v1;
    int v2;
    static const u16 v3[4] = {
        0,
        27,
        28,
        23,
    };
    static const u16 v4[4] = {
        22,
        24,
        25,
        26,
    };

    if (WiFiPlazaLobby_News_IsValidMinigameCount(param0->values[0], param0->values[1]) == 0) {
        return 0;
    }

    StringTemplate_SetPlazaMinigameName(param2, 0, param0->values[0]);

    for (v2 = 0; v2 < param0->values[1]; v2++) {
        StringTemplate_SetString(param2, v2 + 1, param0->names[v2], 0, 1, gGameLanguage);
    }

    if ((param0->values[0] == WiFiPlazaLobbyActivity_00) || (param0->values[0] == WiFiPlazaLobbyActivity_01)) {
        v0 = MessageLoader_GetNewString(param3, v4[param0->values[1] - 1]);
    } else {
        v0 = MessageLoader_GetNewString(param3, v3[param0->values[1] - 1]);
    }

    StringTemplate_Format(param2, param4, v0);
    String_Free(v0);

    return 1;
}

static u32 WiFiPlazaLobby_News_GetHeadlineValueType0(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1)
{
    if (param1 >= 2) {
        return 20;
    }

    return param0->extraValues[param1];
}

static u32 WiFiPlazaLobby_News_GetHeadlineValueType1(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1)
{
    if (param1 >= 2) {
        return 20;
    }

    return param0->extraValues[param1];
}

static u32 WiFiPlazaLobby_News_GetHeadlineValueType2(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1)
{
    if (param0->values[1] <= param1) {
        return 20;
    }

    return param0->extraValues[param1];
}

static u32 WiFiPlazaLobby_News_GetHeadlineValueType3(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1)
{
    if (param1 >= 1) {
        return 20;
    }

    return param0->extraValues[param1];
}

static u32 WiFiPlazaLobby_News_GetHeadlineValueType4(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1)
{
    if (param0->values[0] <= param1) {
        return 20;
    }

    return param0->extraValues[param1];
}

static u32 WiFiPlazaLobby_News_GetHeadlineValueType6(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1)
{
    return 20;
}

static u32 WiFiPlazaLobby_News_GetHeadlineValueType7(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1)
{
    return 20;
}

static u32 WiFiPlazaLobby_News_GetHeadlineValueType8(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1)
{
    if (param0->values[1] <= param1) {
        return 20;
    }

    return param0->extraValues[param1];
}

static BOOL WiFiPlazaLobby_News_IsValidMinigameCount(enum PlazaMinigame param0, u32 param1)
{
    if ((param0 == WiFiPlazaLobbyActivity_00) || (param0 == WiFiPlazaLobbyActivity_01)) {
        if ((param1 < 1) || (param1 > 4)) {
            return 0;
        }
    } else {
        if ((param1 < 2) || (param1 > 4)) {
            return 0;
        }
    }

    return 1;
}
