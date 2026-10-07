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
    u16 unk_00;
    u16 unk_02;
} WiFiPlazaLobbyNewsResultSlot;

typedef struct {
    WiFiPlazaLobbyNewsResultSlot unk_00[20];
    u16 unk_50;
    u16 unk_52;
} WiFiPlazaLobbyNewsResult;

typedef struct WiFiPlazaLobbyNewsHeadline_t {
    u8 unk_00;
    u32 unk_04[3];
    String *unk_10[4];
    u16 unk_20[4];
    u16 unk_28;
    s16 unk_2A;
    struct WiFiPlazaLobbyNewsHeadline_t *unk_2C;
    struct WiFiPlazaLobbyNewsHeadline_t *unk_30;
} WiFiPlazaLobbyNewsHeadline;

typedef struct {
    WiFiPlazaLobbyNewsHeadline unk_00[8];
    WiFiPlazaLobbyNewsHeadline unk_188;
} WiFiPlazaLobbyNewsHeadlineQueue;

typedef struct WiFiPlazaLobbyNews_t {
    WiFiPlazaLobbyTime unk_00;
    BOOL unk_04;
    WiFiPlazaLobbyNewsResult unk_08;
    WiFiPlazaLobbyNewsHeadlineQueue unk_5C;
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

    WiFiPlazaLobby_News_InitResult(&v0->unk_08);
    WiFiPlazaLobby_News_InitHeadlineQueue(&v0->unk_5C, heapID);

    return v0;
}

void WiFiPlazaLobby_News_Free(WiFiPlazaLobbyNews *param0)
{
    WiFiPlazaLobby_News_FreeHeadlineQueue(&param0->unk_5C);
    Heap_Free(param0);
}

void WiFiPlazaLobby_News_Reset(WiFiPlazaLobbyNews *param0)
{
    WiFiPlazaLobby_News_AgeHeadlineQueue(&param0->unk_5C);
    WiFiPlazaLobby_News_SetStateValue(&param0->unk_08, WiFiPlazaLobbyNewsState_00);
}

void WiFiPlazaLobby_News_SetPlazaInfo(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyTime *param1)
{
    param0->unk_00 = *param1;
    param0->unk_04 = 1;
}

void WiFiPlazaLobby_News_SetResult(WiFiPlazaLobbyNews *param0, u32 param1, u32 param2, WiFiPlazaLobbyNewsResultFlags param3)
{
    WiFiPlazaLobby_News_SetResultSlotAndSelect(&param0->unk_08, param1, param2, param3);
}

BOOL WiFiPlazaLobby_News_TakeResultFlag(WiFiPlazaLobbyNews *param0, u32 param1)
{
    BOOL v0 = WiFiPlazaLobby_News_ResultSlotHasNewFlag(&param0->unk_08, param1);
    WiFiPlazaLobby_News_ClearResultSlot(&param0->unk_08, param1);

    return v0;
}

void WiFiPlazaLobby_News_SelectResult(WiFiPlazaLobbyNews *param0, u32 param1)
{
    u32 v0;
    int v1;

    for (v1 = 0; v1 < 20; v1++) {
        v0 = WiFiPlazaLobby_News_GetResultSlotFlags(&param0->unk_08, v1);

        if (v0 & WiFiPlazaLobbyNewsResultFlags_02) {
            v0 &= ~WiFiPlazaLobbyNewsResultFlags_02;
            WiFiPlazaLobby_News_SetResultSlotFlags(&param0->unk_08, v1, v0);
        }
    }

    v0 = WiFiPlazaLobby_News_GetResultSlotFlags(&param0->unk_08, param1);
    WiFiPlazaLobby_News_SetResultSlotFlags(&param0->unk_08, param1, v0 | WiFiPlazaLobbyNewsResultFlags_02);
}

void WiFiPlazaLobby_News_AddDuoEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsDuoEntry *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->unk_5C, 8);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, 0, 0, 0, param1->unk_00, param1->unk_04, NULL, NULL, param1->unk_08, param1->unk_0A, 0, 0, 600, 8, 0);
    WiFiPlazaLobby_News_InsertHeadline(&param0->unk_5C, v0);
}

void WiFiPlazaLobby_News_AddDuoEntryRanked(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsDuoEntryRanked *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0;

    if (param1->unk_0C >= 27) {
        return;
    }

    v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->unk_5C, 7);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, param1->unk_0C, 0, 0, param1->unk_00, param1->unk_04, NULL, NULL, param1->unk_08, param1->unk_0A, 0, 0, 600, 7, 1);
    WiFiPlazaLobby_News_InsertHeadline(&param0->unk_5C, v0);
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

    if ((param1->unk_00 != WiFiPlazaLobbyActivity_00) && (param1->unk_00 != WiFiPlazaLobbyActivity_01) && (param1->unk_00 != WiFiPlazaLobbyActivity_02)) {
        return;
    }

    if (param1->unk_20 == 1) {
        if ((param1->unk_04 < 2) || (param1->unk_04 > 4)) {
            return;
        }
    } else {
        if ((param1->unk_04 < 1) || (param1->unk_04 > 4)) {
            return;
        }
    }

    v1 = param1->unk_00 - WiFiPlazaLobbyActivity_00;
    v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->unk_5C, sc_NEWS_DSET_MINIGAME_PRI[v1]);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, v1, param1->unk_04, param1->unk_20, param1->unk_08, param1->unk_0C, param1->unk_10, param1->unk_14, param1->unk_18, param1->unk_1A, param1->unk_1C, param1->unk_1E, 900, sc_NEWS_DSET_MINIGAME_PRI[v1], 2);
    WiFiPlazaLobby_News_InsertHeadline(&param0->unk_5C, v0);
}

void WiFiPlazaLobby_News_AddMinigameQuickEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsMinigameQuickEntry *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0;

    if ((param1->unk_00 != WiFiPlazaLobbyActivity_03) && (param1->unk_00 != WiFiPlazaLobbyActivity_04)) {
        return;
    }

    v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->unk_5C, 5 + param1->unk_00);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, param1->unk_00, param1->unk_04, 0, param1->unk_08, NULL, NULL, NULL, param1->unk_0C, 0, 0, 0, 900, 5 + param1->unk_00, 3);
    WiFiPlazaLobby_News_InsertHeadline(&param0->unk_5C, v0);
}

void WiFiPlazaLobby_News_AddFourTrainerEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsFourTrainerEntry *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->unk_5C, 12);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, param1->unk_00, 0, 0, param1->unk_04, param1->unk_08, param1->unk_0C, param1->unk_10, param1->unk_14, param1->unk_16, param1->unk_18, param1->unk_1A, 450, 12, 4);
    WiFiPlazaLobby_News_InsertHeadline(&param0->unk_5C, v0);
}

void WiFiPlazaLobby_News_AddFourTrainerEntryB(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsFourTrainerEntryB *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->unk_5C, 13);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, param1->unk_00, 0, 0, param1->unk_04, param1->unk_08, param1->unk_0C, param1->unk_10, param1->unk_14, param1->unk_16, param1->unk_18, param1->unk_1A, 450, 13, 5);
    WiFiPlazaLobby_News_InsertHeadline(&param0->unk_5C, v0);
}

void WiFiPlazaLobby_News_AddEventEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsEventEntry *param1)
{
    WiFiPlazaLobbyNewsHeadline *v0;

    switch (param1->unk_04) {
    case 0:
    case 1:
    case 2:
    case 4:
        break;
    default:
        return;
    }

    v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->unk_5C, 14);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, param1->unk_00->unk_00_val1, param1->unk_04, 0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 900, 14, 6);
    WiFiPlazaLobby_News_InsertHeadline(&param0->unk_5C, v0);
}

void WiFiPlazaLobby_News_AddTrainerEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsTrainerEntry *param1, const WiFiPlazaLobbyNewsPlayerFlags *param2)
{
    WiFiPlazaLobbyNewsHeadline *v0;
    int v1;

    if (param1->unk_00 >= 20) {
        return;
    }

    if (param2->unk_00[param1->unk_00] == 0) {
        return;
    }

    v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->unk_5C, 1);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, param1->unk_00, 0, 0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 1800, 1, 7);
    WiFiPlazaLobby_News_InsertHeadline(&param0->unk_5C, v0);
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

    if ((param1->unk_00 != WiFiPlazaLobbyActivity_00) && (param1->unk_00 != WiFiPlazaLobbyActivity_01) && (param1->unk_00 != WiFiPlazaLobbyActivity_02)) {
        return;
    }

    if (WiFiPlazaLobby_News_IsValidMinigameCount(param1->unk_00, param1->unk_04) == 0) {
        return;
    }

    v1 = param1->unk_00 - WiFiPlazaLobbyActivity_00;
    v0 = WiFiPlazaLobby_News_AllocHeadline(&param0->unk_5C, v2[v1]);

    if (v0 == NULL) {
        return;
    }

    WiFiPlazaLobby_News_SetHeadlineData(v0, v1, param1->unk_04, 0, param1->unk_08, param1->unk_0C, param1->unk_10, param1->unk_14, param1->unk_18, param1->unk_1A, param1->unk_1C, param1->unk_1E, 450, v2[v1], 8);
    WiFiPlazaLobby_News_InsertHeadline(&param0->unk_5C, v0);
}

void WiFiPlazaLobby_News_ClearQueue(WiFiPlazaLobbyNews *param0)
{
    WiFiPlazaLobby_News_RemoveFrontHeadline(&param0->unk_5C);
}

BOOL WiFiPlazaLobby_News_GetPlazaInfo(const WiFiPlazaLobbyNews *param0, WiFiPlazaLobbyTime *param1)
{
    *param1 = param0->unk_00;
    return param0->unk_04;
}

BOOL WiFiPlazaLobby_News_IsResultSet(const WiFiPlazaLobbyNews *param0, u32 param1)
{
    return WiFiPlazaLobby_News_ResultSlotIsSet(&param0->unk_08, param1);
}

u32 WiFiPlazaLobby_News_GetResult(const WiFiPlazaLobbyNews *param0, u32 param1)
{
    return WiFiPlazaLobby_News_GetResultSlotValue(&param0->unk_08, param1);
}

BOOL WiFiPlazaLobby_News_HasResultFlag(const WiFiPlazaLobbyNews *param0, u32 param1)
{
    return WiFiPlazaLobby_News_ResultSlotHasFlag(&param0->unk_08, param1);
}

BOOL WiFiPlazaLobby_News_HasNewResultFlag(const WiFiPlazaLobbyNews *param0, u32 param1)
{
    return WiFiPlazaLobby_News_ResultSlotHasNewFlag(&param0->unk_08, param1);
}

BOOL WiFiPlazaLobby_News_IsCurrentResult(const WiFiPlazaLobbyNews *param0, u32 param1)
{
    return WiFiPlazaLobby_News_ResultSlotIsCurrent(&param0->unk_08, param1);
}

WiFiPlazaLobbyNewsState WiFiPlazaLobby_News_GetState(const WiFiPlazaLobbyNews *param0)
{
    return WiFiPlazaLobby_News_GetStateValue(&param0->unk_08);
}

BOOL WiFiPlazaLobby_News_HasHeadline(const WiFiPlazaLobbyNews *param0)
{
    if (param0->unk_5C.unk_188.unk_2C != &param0->unk_5C.unk_188) {
        return 1;
    }

    return 0;
}

int WiFiPlazaLobby_News_GetHeadlineType(const WiFiPlazaLobbyNews *param0)
{
    GF_ASSERT(WiFiPlazaLobby_News_HasHeadline(param0));
    return param0->unk_5C.unk_188.unk_2C->unk_00;
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

    v2 = param0->unk_5C.unk_188.unk_2C;
    v1 = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0653, heapID);
    v0 = StringTemplate_Default(heapID);

    if (v2->unk_00 < 9) {
        v3 = v4[v2->unk_00](v2, param1, v0, v1, param3, heapID);
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

    v0 = param0->unk_5C.unk_188.unk_2C;

    if (v0->unk_00 < 9) {
        v1 = v2[v0->unk_00](v0, param2);
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
    param0->unk_00[param1].unk_00 = param2;
    param0->unk_00[param1].unk_02 = param3;
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
    param0->unk_00[param1].unk_02 = param2;
}

static void WiFiPlazaLobby_News_SetStateValue(WiFiPlazaLobbyNewsResult *param0, WiFiPlazaLobbyNewsState param1)
{
    GF_ASSERT(param1 <= WiFiPlazaLobbyNewsResultFlags_02);
    param0->unk_50 = param1;
}

static void WiFiPlazaLobby_News_SetCurrentIndex(WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    param0->unk_52 = param1;
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
    return param0->unk_00[param1].unk_00;
}

static BOOL WiFiPlazaLobby_News_ResultSlotHasFlag(const WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param0->unk_00[param1].unk_02 & WiFiPlazaLobbyNewsResultFlags_01) {
        return 1;
    }

    return 0;
}

static BOOL WiFiPlazaLobby_News_ResultSlotHasNewFlag(const WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param0->unk_00[param1].unk_02 & WiFiPlazaLobbyNewsResultFlags_02) {
        return 1;
    }

    return 0;
}

static WiFiPlazaLobbyNewsResultFlags WiFiPlazaLobby_News_GetResultSlotFlags(const WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    return param0->unk_00[param1].unk_02;
}

static WiFiPlazaLobbyNewsState WiFiPlazaLobby_News_GetStateValue(const WiFiPlazaLobbyNewsResult *param0)
{
    return param0->unk_50;
}

static BOOL WiFiPlazaLobby_News_ResultSlotIsCurrent(const WiFiPlazaLobbyNewsResult *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);

    if (param0->unk_52 == param1) {
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
            param0->unk_00[v0].unk_10[v1] = String_Init((7 + 1), heapID);
        }
    }

    param0->unk_188.unk_2C = &param0->unk_188;
    param0->unk_188.unk_30 = &param0->unk_188;
}

static void WiFiPlazaLobby_News_FreeHeadlineQueue(WiFiPlazaLobbyNewsHeadlineQueue *param0)
{
    int v0, v1;

    for (v0 = 0; v0 < 8; v0++) {
        for (v1 = 0; v1 < 4; v1++) {
            String_Free(param0->unk_00[v0].unk_10[v1]);
        }
    }

    memset(param0, 0, sizeof(WiFiPlazaLobbyNewsHeadlineQueue));
}

static void WiFiPlazaLobby_News_AgeHeadlineQueue(WiFiPlazaLobbyNewsHeadlineQueue *param0)
{
    WiFiPlazaLobbyNewsHeadline *v0;
    WiFiPlazaLobbyNewsHeadline *v1 = param0->unk_188.unk_2C;

    while (v1 != &param0->unk_188) {
        v0 = v1->unk_2C;
        v1->unk_28 = 0;

        if ((v1->unk_2A - 1) > 0) {
            v1->unk_2A--;
        } else {
            WiFiPlazaLobby_News_UnlinkHeadline(param0, v1);
        }

        v1 = v0;
    }
}

static void WiFiPlazaLobby_News_RemoveFrontHeadline(WiFiPlazaLobbyNewsHeadlineQueue *param0)
{
    WiFiPlazaLobby_News_UnlinkHeadline(param0, param0->unk_188.unk_2C);
}

static WiFiPlazaLobbyNewsHeadline *WiFiPlazaLobby_News_AllocHeadline(WiFiPlazaLobbyNewsHeadlineQueue *param0, u16 param1)
{
    int v0;
    WiFiPlazaLobbyNewsHeadline *v1 = NULL;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->unk_00[v0].unk_2C == NULL) {
            v1 = &param0->unk_00[v0];
            break;
        }
    }

    if (v1 == NULL) {
        for (v0 = 0; v0 < 8; v0++) {
            if (param0->unk_00[v0].unk_28 >= param1) {
                WiFiPlazaLobby_News_UnlinkHeadline(param0, &param0->unk_00[v0]);
                v1 = &param0->unk_00[v0];
                break;
            }
        }
    }

    return v1;
}

static void WiFiPlazaLobby_News_InsertHeadlineBefore(WiFiPlazaLobbyNewsHeadline *param0, WiFiPlazaLobbyNewsHeadline *param1)
{
    param1->unk_2C = param0->unk_2C;
    param1->unk_30 = param0;
    param0->unk_2C = param1;
    param1->unk_2C->unk_30 = param1;
}

static void WiFiPlazaLobby_News_InsertHeadline(WiFiPlazaLobbyNewsHeadlineQueue *param0, WiFiPlazaLobbyNewsHeadline *param1)
{
    {
        WiFiPlazaLobbyNewsHeadline *v0;

        v0 = param0->unk_188.unk_30;

        while (v0 != &param0->unk_188) {
            if (v0->unk_28 < param1->unk_28) {
                break;
            }

            v0 = v0->unk_30;
        }

        WiFiPlazaLobby_News_InsertHeadlineBefore(v0, param1);
    }
}

static void WiFiPlazaLobby_News_UnlinkHeadline(WiFiPlazaLobbyNewsHeadlineQueue *param0, WiFiPlazaLobbyNewsHeadline *param1)
{
    param1->unk_30->unk_2C = param1->unk_2C;
    param1->unk_2C->unk_30 = param1->unk_30;
    param1->unk_30 = NULL;
    param1->unk_2C = NULL;
}

static void WiFiPlazaLobby_News_SetHeadlineData(WiFiPlazaLobbyNewsHeadline *param0, u32 param1, u32 param2, u32 param3, const TrainerInfo *param4, const TrainerInfo *param5, const TrainerInfo *param6, const TrainerInfo *param7, u16 param8, u16 param9, u16 param10, u16 param11, u32 param12, u32 param13, u32 param14)
{
    GF_ASSERT(param14 < 9);
    param0->unk_00 = param14;
    param0->unk_2A = param12;
    param0->unk_28 = param13;
    param0->unk_04[0] = param1;
    param0->unk_04[1] = param2;
    param0->unk_04[2] = param3;
    param0->unk_20[0] = param8;
    param0->unk_20[1] = param9;
    param0->unk_20[2] = param10;
    param0->unk_20[3] = param11;

    if (param4) {
        TrainerInfo_NameString(param4, param0->unk_10[0]);
    }

    if (param5) {
        TrainerInfo_NameString(param5, param0->unk_10[1]);
    }

    if (param6) {
        TrainerInfo_NameString(param6, param0->unk_10[2]);
    }

    if (param7) {
        TrainerInfo_NameString(param7, param0->unk_10[3]);
    }
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType0(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    String *v0;

    StringTemplate_SetString(param2, 0, param0->unk_10[0], 0, 1, gGameLanguage);
    StringTemplate_SetString(param2, 1, param0->unk_10[1], 0, 1, gGameLanguage);

    v0 = MessageLoader_GetNewString(param3, 7);

    StringTemplate_Format(param2, param4, v0);
    String_Free(v0);

    return 1;
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType1(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    String *v0;

    StringTemplate_SetString(param2, 0, param0->unk_10[0], 0, 1, gGameLanguage);
    StringTemplate_SetString(param2, 1, param0->unk_10[1], 0, 1, gGameLanguage);
    StringTemplate_SetPlazaItemName(param2, 2, param0->unk_04[0]);

    v0 = MessageLoader_GetNewString(param3, 8);

    StringTemplate_Format(param2, param4, v0);
    String_Free(v0);

    return 1;
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType2(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    String *v0;

    StringTemplate_SetPlazaMinigameName(param2, 0, param0->unk_04[0]);

    if (param0->unk_04[2] == 1) {
        u32 v1;

        switch (param0->unk_04[1]) {
        case 3:
            StringTemplate_SetString(param2, 1, param0->unk_10[0], 0, 1, gGameLanguage);
            StringTemplate_SetString(param2, 2, param0->unk_10[1], 0, 1, gGameLanguage);
            StringTemplate_SetString(param2, 3, param0->unk_10[2], 0, 1, gGameLanguage);
            v1 = 18;
            break;
        case 2:
            StringTemplate_SetString(param2, 1, param0->unk_10[0], 0, 1, gGameLanguage);
            StringTemplate_SetString(param2, 2, param0->unk_10[1], 0, 1, gGameLanguage);
            v1 = 19;
            break;
        case 4:
            StringTemplate_SetString(param2, 1, param0->unk_10[0], 0, 1, gGameLanguage);
            StringTemplate_SetString(param2, 2, param0->unk_10[1], 0, 1, gGameLanguage);
            StringTemplate_SetString(param2, 3, param0->unk_10[2], 0, 1, gGameLanguage);
            StringTemplate_SetString(param2, 4, param0->unk_10[3], 0, 1, gGameLanguage);
            v1 = 6;
            break;
        default:
            return 0;
        }

        v0 = MessageLoader_GetNewString(param3, v1);
    } else {
        StringTemplate_SetString(param2, 1, param0->unk_10[0], 0, 1, gGameLanguage);
        StringTemplate_SetNumber(param2, 2, 4 - param0->unk_04[1], 1, 1, 1);

        v0 = MessageLoader_GetNewString(param3, 5);
    }

    StringTemplate_Format(param2, param4, v0);
    String_Free(v0);

    return 1;
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType3(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    String *v0;

    StringTemplate_SetPlazaMinigameName(param2, 0, param0->unk_04[0]);
    StringTemplate_SetString(param2, 1, param0->unk_10[0], 0, 1, gGameLanguage);
    StringTemplate_SetNumber(param2, 2, 8 - param0->unk_04[1], 1, 1, 1);

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

    for (v1 = 0; v1 < param0->unk_04[0]; v1++) {
        StringTemplate_SetString(param2, v1, param0->unk_10[v1], 0, 1, gGameLanguage);
    }

    if (param0->unk_00 == 4) {
        StringTemplate_SetPlazaMinigameName(param2, param0->unk_04[0], WiFiPlazaLobbyActivity_05);
    } else {
        StringTemplate_SetPlazaMinigameName(param2, param0->unk_04[0], WiFiPlazaLobbyActivity_06);
    }

    v0 = MessageLoader_GetNewString(param3, 10 + (4 - param0->unk_04[0]));

    StringTemplate_Format(param2, param4, v0);
    String_Free(v0);

    return 1;
}

static BOOL WiFiPlazaLobby_News_FormatHeadlineType6(WiFiPlazaLobbyNewsHeadline *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, StringTemplate *param2, MessageLoader *param3, String *param4, u32 param5)
{
    String *v0;
    u32 v1;

    switch (param0->unk_04[1]) {
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
    if (param0->unk_04[0] >= 20) {
        return 0;
    }

    if (param1->unk_00[param0->unk_04[0]] == 0) {
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

    if (WiFiPlazaLobby_News_IsValidMinigameCount(param0->unk_04[0], param0->unk_04[1]) == 0) {
        return 0;
    }

    StringTemplate_SetPlazaMinigameName(param2, 0, param0->unk_04[0]);

    for (v2 = 0; v2 < param0->unk_04[1]; v2++) {
        StringTemplate_SetString(param2, v2 + 1, param0->unk_10[v2], 0, 1, gGameLanguage);
    }

    if ((param0->unk_04[0] == WiFiPlazaLobbyActivity_00) || (param0->unk_04[0] == WiFiPlazaLobbyActivity_01)) {
        v0 = MessageLoader_GetNewString(param3, v4[param0->unk_04[1] - 1]);
    } else {
        v0 = MessageLoader_GetNewString(param3, v3[param0->unk_04[1] - 1]);
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

    return param0->unk_20[param1];
}

static u32 WiFiPlazaLobby_News_GetHeadlineValueType1(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1)
{
    if (param1 >= 2) {
        return 20;
    }

    return param0->unk_20[param1];
}

static u32 WiFiPlazaLobby_News_GetHeadlineValueType2(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1)
{
    if (param0->unk_04[1] <= param1) {
        return 20;
    }

    return param0->unk_20[param1];
}

static u32 WiFiPlazaLobby_News_GetHeadlineValueType3(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1)
{
    if (param1 >= 1) {
        return 20;
    }

    return param0->unk_20[param1];
}

static u32 WiFiPlazaLobby_News_GetHeadlineValueType4(const WiFiPlazaLobbyNewsHeadline *param0, u32 param1)
{
    if (param0->unk_04[0] <= param1) {
        return 20;
    }

    return param0->unk_20[param1];
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
    if (param0->unk_04[1] <= param1) {
        return 20;
    }

    return param0->unk_20[param1];
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
