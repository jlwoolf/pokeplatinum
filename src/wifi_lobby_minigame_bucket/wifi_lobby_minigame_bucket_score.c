#include "wifi_lobby_minigame_bucket/wifi_lobby_minigame_bucket_score.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_stage.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_throw_data.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_final_scores.h"

#include "heap.h"

typedef struct WiFiLobbyMinigameBucketScore_t {
    s32 unk_00;
    BOOL unk_04;
    u32 unk_08;
    WiFiLobbyMinigameBucketFinalScores unk_0C;
    u32 unk_1C;
    u32 unk_20[4];
    const WiFiLobbyMinigameBucketStage *unk_30;
    u16 unk_34;
    u8 unk_36;
    u8 unk_37;
} WiFiLobbyMinigameBucketScore;

static u32 WiFiLobbyMinigameBucket_CountScoredPlayers(const WiFiLobbyMinigameBucketScore *param0);

WiFiLobbyMinigameBucketScore *WiFiLobbyMinigameBucket_CreateScore(enum HeapID heapID, u32 param1, u32 param2, const WiFiLobbyMinigameBucketStage *param3)
{
    WiFiLobbyMinigameBucketScore *v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMinigameBucketScore));
    memset(v0, 0, sizeof(WiFiLobbyMinigameBucketScore));

    v0->unk_00 = param1;
    v0->unk_08 = param2;
    v0->unk_30 = param3;
    v0->unk_04 = 1;

    return v0;
}

void WiFiLobbyMinigameBucket_FreeScore(WiFiLobbyMinigameBucketScore *param0)
{
    Heap_Free(param0);
}

BOOL WiFiLobbyMinigameBucket_UpdateScoreTracker(WiFiLobbyMinigameBucketScore *param0)
{
    int v0;

    if ((param0->unk_00 > 0) && (param0->unk_04 == 1)) {
        param0->unk_00--;
    }

    if (param0->unk_00 <= 0) {
        return 0;
    }

    for (v0 = param0->unk_36; v0 < param0->unk_30->unk_00; v0++) {
        if (param0->unk_30->unk_04[v0].unk_00 >= param0->unk_34) {
            break;
        }
    }

    if (v0 == param0->unk_30->unk_00) {
        v0--;
    }

    if (v0 != param0->unk_36) {
        param0->unk_36 = v0;
        param0->unk_37 = 1;
    }

    return 1;
}

BOOL WiFiLobbyMinigameBucket_ScoreChanged(const WiFiLobbyMinigameBucketScore *param0)
{
    return param0->unk_37;
}

void WiFiLobbyMinigameBucket_ClearScoreChanged(WiFiLobbyMinigameBucketScore *param0)
{
    param0->unk_37 = 0;
}

u32 WiFiLobbyMinigameBucket_GetScoreStage(const WiFiLobbyMinigameBucketScore *param0)
{
    return param0->unk_36;
}

void WiFiLobbyMinigameBucket_AdvanceScoreThreshold(WiFiLobbyMinigameBucketScore *param0, const WiFiLobbyMinigameBucketThrowData *param1, u32 param2)
{
    if (param1->unk_02) {
        param0->unk_34++;
    }
}

void WiFiLobbyMinigameBucket_SetPlayerScore(WiFiLobbyMinigameBucketScore *param0, u32 param1, u32 param2)
{
    int v0;
    int v1;

    if (param1 > 99999) {
        param1 = 99999;
    }

    if ((param0->unk_1C & (1 << param2)) == 0) {
        param0->unk_0C.scores[param2] = param1;
        param0->unk_1C |= (1 << param2);
    }
}

BOOL WiFiLobbyMinigameBucket_AllPlayersScored(const WiFiLobbyMinigameBucketScore *param0)
{
    int v0 = WiFiLobbyMinigameBucket_CountScoredPlayers(param0);

    if (v0 >= param0->unk_08) {
        return 1;
    }

    return 0;
}

void WiFiLobbyMinigameBucket_GetFinalScores(WiFiLobbyMinigameBucketScore *param0, WiFiLobbyMinigameBucketFinalScores *param1)
{
    *param1 = param0->unk_0C;
}

static u32 WiFiLobbyMinigameBucket_CountScoredPlayers(const WiFiLobbyMinigameBucketScore *param0)
{
    int v0;
    int v1 = 0;

    for (v0 = 0; v0 < 4; v0++) {
        if ((param0->unk_1C & (1 << v0)) != 0) {
            v1++;
        }
    }

    return v1;
}
