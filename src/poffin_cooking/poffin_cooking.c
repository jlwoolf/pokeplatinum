#include "poffin_cooking/poffin_cooking.h"

#include <nitro.h>
#include <string.h>

#include "generated/game_records.h"
#include "generated/trainer_score_events.h"

#include "struct_decls/tv_broadcast.h"
#include "struct_decls/wi_fi_list.h"

#include "applications/poffin_berry_selection.h"
#include "nintendo_wfc/main.h"
#include "poffin_cooking/poffin_cooking_0223C958.h"
#include "poffin_cooking/poffin_cooking_0223D150.h"
#include "poffin_cooking/poffin_cooking_0223D4CC.h"
#include "poffin_cooking/poffin_cooking_0223D6A8.h"
#include "poffin_cooking/poffin_cooking_0223F7F4.h"
#include "poffin_cooking/struct_poffin_cooking_app.h"
#include "poffin_cooking/struct_poffin_cooking_blend_state.h"
#include "savedata/save_table.h"

#include "bag.h"
#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "game_options.h"
#include "game_records.h"
#include "gx_layers.h"
#include "heap.h"
#include "journal.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "poffin.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite.h"
#include "system.h"
#include "tv_segment.h"
#include "comm_tool.h"
#include "wifi_friend_registration.h"
#include "vram_transfer.h"
#include "wifi_list.h"

typedef int (*UnkFuncPtr_poffin_cooking_0224024C)(PoffinBerrySelectionData *, PoffinCookingApp *, int *);

typedef struct {
    UnkFuncPtr_poffin_cooking_0224024C func;
    int commDelay;
} PoffinCookingStateEntry;

int PoffinCooking_Init(ApplicationManager *appMan, int *param1);
int PoffinCooking_Main(ApplicationManager *appMan, int *param1);
int PoffinCooking_Exit(ApplicationManager *appMan, int *param1);
static int poffin_cooking_0223C344(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2);
static int poffin_cooking_0223B78C(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2);
static int poffin_cooking_0223B920(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2);
static int poffin_cooking_0223B950(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2);
static int poffin_cooking_0223B964(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2);
static int poffin_cooking_0223B9EC(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2);
static int poffin_cooking_0223BB40(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2);
static int poffin_cooking_0223BCEC(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2);
static int poffin_cooking_0223BF74(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2);
static int poffin_cooking_0223C24C(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2);
static int poffin_cooking_0223C258(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2);
static void poffin_cooking_0223C3E8(PoffinCookingApp *param0);
static void poffin_cooking_0223C480(PoffinCookingApp *param0);
static void poffin_cooking_0223C558(PoffinCookingApp *param0);
static void poffin_cooking_0223C600(PoffinCookingApp *param0);
static void poffin_cooking_0223C6D4(PoffinCookingApp *param0);
static void poffin_cooking_0223C758(PoffinCookingApp *param0);
static void poffin_cooking_0223C7FC(PoffinCookingApp *param0);
static void poffin_cooking_0223C90C(PoffinCookingApp *param0);
static void poffin_cooking_0223C82C(PoffinBerrySelectionData *param0, PoffinCookingApp *param1);
static void poffin_cooking_0223C87C(PoffinBerrySelectionData *param0, PoffinCookingApp *param1);
static BOOL poffin_cooking_0223C8B0(PoffinBerrySelectionData *param0, Poffin *param1, int param2);

static const PoffinCookingStateEntry Unk_poffin_cooking_0224024C[] = {
    { poffin_cooking_0223B78C, 0x1 },
    { poffin_cooking_0223B920, 0x0 },
    { poffin_cooking_0223B950, 0x0 },
    { poffin_cooking_0223B964, 0x0 },
    { poffin_cooking_0223B950, 0x0 },
    { poffin_cooking_0223C24C, 0x2 },
    { poffin_cooking_0223B9EC, 0x0 },
    { poffin_cooking_0223BB40, 0x0 },
    { poffin_cooking_0223BCEC, 0x0 },
    { poffin_cooking_0223B950, 0x0 },
    { poffin_cooking_0223BF74, 0x0 },
    { poffin_cooking_0223B950, 0x0 },
    { poffin_cooking_0223C258, 0x3 },
    { poffin_cooking_0223C344, 0x0 }
};

static void poffin_cooking_0223B5A0(void *param0)
{
    PoffinBerrySelectionData *v0 = (PoffinBerrySelectionData *)param0;
    PoffinCookingApp *v1 = v0->buffer;

    poffin_cooking_0223CBFC(v1);
    VramTransfer_Process();
}

int PoffinCooking_Init(ApplicationManager *appMan, int *param1)
{
    PoffinBerrySelectionData *v0 = ApplicationManager_Args(appMan);
    PoffinCookingApp *v1;

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_56, 0x20000);
    v1 = ApplicationManager_NewData(appMan, sizeof(PoffinCookingApp), HEAP_ID_56);
    memset(v1, 0, sizeof(PoffinCookingApp));

    v0->buffer = v1;
    v1->heapID = HEAP_ID_56;

    VramTransfer_New(16, v1->heapID);

    v1->isMultiplayer = v0->isInGroup == TRUE;

    poffin_cooking_0223D150(v1, v0->ctx->trainerInfo);

    if (v0->isOnline) {
        CommSys_SetRecvLimitEnabled(1);
    }

    v1->frameType = Options_Frame(v0->ctx->options);
    v1->textFrameDelay = Options_TextFrameDelay(v0->ctx->options);
    v1->updateSpriteList = 1;

    SetVBlankCallback(poffin_cooking_0223B5A0, v0);
    DisableHBlank();
    Sound_SetSceneAndPlayBGM(SOUND_SCENE_12, SEQ_KINOMI1_sseq, 1);

    return 1;
}

int PoffinCooking_Main(ApplicationManager *appMan, int *param1)
{
    int v0, v1;
    PoffinBerrySelectionData *v2 = ApplicationManager_Args(appMan);
    PoffinCookingApp *v3 = (PoffinCookingApp *)ApplicationManager_Data(appMan);
    const PoffinCookingStateEntry *v4;

    v0 = v3->state;
    v4 = &(Unk_poffin_cooking_0224024C[v0]);

    switch (*param1) {
    case 0:
        if (v4->func == NULL) {
            break;
        }

        v1 = v4->commDelay;
        v3->state = (v4->func)(v2, v3, &v3->step);

        if (v3->forceStateChange) {
            v3->state = v3->forcedState;
            v3->forceStateChange = 0;
        }

        if (v0 == v3->state) {
            break;
        }

        v3->step = 0;

        if (!v2->isInGroup) {
            break;
        }

        if (v1 == 0) {
            break;
        }

        v3->syncTimer = v1;
        *param1 = 1;
        break;
    case 1:
        CommTiming_StartSync(v3->syncTimer);
        *param1 = 2;
        break;
    case 2:
        if (!CommTiming_IsSyncState(v3->syncTimer)) {
            break;
        }

        *param1 = 0;
        v3->syncTimer = 0;
        break;
    }

    poffin_cooking_0223CBA4(v3);
    CommManager_Dummy_02038A1C(v3->heapID, v3->bgConfig);

    if (v3->finished) {
        return 1;
    } else {
        return 0;
    }
}

int PoffinCooking_Exit(ApplicationManager *appMan, int *param1)
{
    int heapID;
    PoffinBerrySelectionData *v1 = ApplicationManager_Args(appMan);
    PoffinCookingApp *v2 = (PoffinCookingApp *)ApplicationManager_Data(appMan);

    heapID = v2->heapID;

    if (v1->isOnline) {
        if (CommSys_CurNetId() == 0) {
            NintendoWFC_ResetMatchmakingCancelState();
        }
    }

    poffin_cooking_0223D1EC(v2);

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    VramTransfer_Free();
    MI_CpuClear8(v2, sizeof(PoffinCookingApp));
    ApplicationManager_FreeData(appMan);

    v1->buffer = NULL;

    Heap_Destroy(heapID);
    return 1;
}

void poffin_cooking_0223B774(PoffinCookingApp *param0, int param1)
{
    param0->nextState = param1;
    param0->pendingStateChange = 1;
}

void poffin_cooking_0223B77C(PoffinCookingApp *param0, int param1)
{
    param0->forcedState = param1;
    param0->forceStateChange = 1;
}

void poffin_cooking_0223B784(PoffinCookingApp *param0)
{
    param0->finished = 1;
}

static int poffin_cooking_0223B78C(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2)
{
    switch (*param2) {
    case 0:

        poffin_cooking_0223C82C(param0, param1);

        if (poffin_cooking_0223D570(param1->comm) == 0) {
            poffin_cooking_0223FDB0(&param1->simulation);
        }

        poffin_cooking_0223DEA0(&param1->playerListDisplay, param1->playerCount, &param1->messages, &param1->session, param1->frameType, param1->heapID);
        poffin_cooking_0223E340(&param1->burstEffect);
        poffin_cooking_0223E6D4(&param1->messageBox, param1->playerCount, &param1->messages, &param1->session, param1->frameType, param1->heapID);
        poffin_cooking_0223E244(&param1->reactionSprite);
        poffin_cooking_0223E244(&param1->reactionSprite2);
        poffin_cooking_0223E244(&param1->reactionSprite3);
        poffin_cooking_0223E5A4(&param1->playerCursor, &param1->session, param1->playerCount, param1->comm);
        poffin_cooking_0223ED3C(&param1->particleManager);
        poffin_cooking_0223F29C(&param1->arrowManager);
        poffin_cooking_0223F494(&param1->sparkleManager, param1->playerCount);
        poffin_cooking_0223F820(&param1->touchTracker);
        poffin_cooking_0223C958(param1);

        NetworkIcon_Init();
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);

        if (param1->playerCount > 1) {
            poffin_cooking_0223DF84(&param1->playerListDisplay);
        }

        poffin_cooking_0223E484(&param1->burstEffect, 3, 1);
        poffin_cooking_0223E484(&param1->burstEffect, 4, 1);
        poffin_cooking_0223E484(&param1->burstEffect, 5, 1);
        poffin_cooking_0223E484(&param1->burstEffect, 6, 1);
        (*param2)++;
        break;
    case 1:
        StartScreenFade(FADE_BOTH_SCREENS, 1, 1, 0xffff, 6, 1, param1->heapID);
        (*param2)++;
        break;
    case 2:
        if (IsScreenFadeDone()) {
            return param1->state + 1;
        }
        break;
    }

    return param1->state;
}

static int poffin_cooking_0223B920(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2)
{
    BOOL v0;

    if (poffin_cooking_0223D570(param1->comm) == 0) {
        v0 = poffin_cooking_0223D508(22, NULL, 0, param1->comm);

        if (v0 == 0) {
            return param1->state;
        }
    }

    return param1->state + 1;
}

static int poffin_cooking_0223B950(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2)
{
    if (param1->pendingStateChange) {
        param1->state = param1->nextState;
        param1->pendingStateChange = 0;
    }

    return param1->state;
}

static int poffin_cooking_0223B964(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2)
{
    BOOL v0;

    switch (*param2) {
    case 0:
        poffin_cooking_0223DB18(&param1->poffinAnim, param1->playerCount);
        (*param2)++;
        break;
    case 1:
        param1->session.localBerry.itemID = param0->item;
        {
            int v1;

            for (v1 = 0; v1 < 5; v1++) {
                param1->syncCounters[v1] = 2;
            }

            param1->syncCounter = 2;
        }
        (*param2)++;
        break;

    case 2:
        v0 = poffin_cooking_0223D508(25, &param1->session.localBerry, poffin_cooking_0223D4B8(), param1->comm);

        if (v0 == 1) {
            return param1->state + 1;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return param1->state;
}

static int poffin_cooking_0223B9EC(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2)
{
    u32 v0;
    int v1;
    BOOL v2;

    switch (*param2) {
    case 0:
        poffin_cooking_0223F790(&param1->yesNoMenu, param1->heapID, param1->bgConfig);
        (*param2)++;
        break;
    case 1:
        poffin_cooking_0223DC68(&param1->poffinAnim);
        (*param2)++;
        break;
    case 2:
        v0 = poffin_cooking_0223DD30(&param1->poffinAnim);

        if (v0 == 1) {
            (*param2)++;
            poffin_cooking_0223DF70(&param1->playerListDisplay);
            param1->timer = 24;
        } else if (v0 != 0) {
            v1 = param1->session.playerNetIDs[v0 - 2];
            poffin_cooking_0223DF30(&param1->playerListDisplay, param1->session.receivedBerryPacket.berries[v1].itemID);
        }
        break;
    case 3:
        if (param1->timer > 0) {
            param1->timer--;
            break;
        }

        poffin_cooking_0223E2FC(&param1->reactionSprite3);
        (*param2)++;
        break;
    case 4:
        if (poffin_cooking_0223E32C(&param1->reactionSprite3) == 0) {
            break;
        }

        poffin_cooking_0223DFAC(&param1->playerListDisplay);
        poffin_cooking_0223E2E4(&param1->reactionSprite);
        (*param2)++;
        break;
    case 5:
        v2 = poffin_cooking_0223E32C(&param1->reactionSprite);
        {
            int v3 = Sprite_GetAnimFrame(param1->reactionSprite.sprite);

            if (param1->lastReactionFrame != (v3 + 1) / 3) {
                if (v3 < 10) {
                    Sound_PlayEffect(SEQ_SE_DP_NM10_sseq);
                } else {
                    Sound_PlayEffect(SEQ_SE_DP_NM10_2_sseq);
                }

                param1->lastReactionFrame = (v3 + 1) / 3;
            }
        }

        if (v2) {
            poffin_cooking_0223E69C(&param1->playerCursor, 1);
            poffin_cooking_0223E500(&param1->burstEffect);

            return param1->state + 1;
        }
        break;
    }

    return param1->state;
}

static int poffin_cooking_0223BB40(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2)
{
    BOOL v0;

    poffin_cooking_0223F83C(&param1->touchTracker);
    poffin_cooking_0223F88C(&param1->session.localParticipant.touchInput, &param1->touchTracker);

    if (poffin_cooking_0223D570(param1->comm) == 0) {
        v0 = poffin_cooking_0223FDD8(&param1->simulation, &param1->session, param1->playerCount);

        if (v0 == 1) {
            v0 = poffin_cooking_0223D508(23, NULL, 0, param1->comm);
            return param1->state;
        } else {
            poffin_cooking_0223FFA0(&param1->simulation);

            if (param1->participantDataSent == 0) {
                poffin_cooking_0223FE50(&param1->simulation, &param1->session, param1->playerCount);
                param1->participantDataSent = 1;
            } else {
                poffin_cooking_0223FEC0(&param1->simulation, &param1->session, param1->playerCount);
            }
        }
    }

    if (param0->isOnline) {
        param1->touchSendTimer++;

        if ((param1->touchSendTimer % 2) == 0) {
            param1->touchSendTimer = 0;

            if (poffin_cooking_0223D570(param1->comm) == 0) {
                {
                    BOOL v1 = 1;
                    int v2;

                    for (v2 = 1; v2 < (7 + 1); v2++) {
                        if (CommSys_IsPlayerConnected(v2)) {
                            if (param1->syncCounters[v2] == 0) {
                                v1 = 0;
                            }
                        }
                    }

                    if (v1) {
                        v0 = poffin_cooking_0223D508(26, &param1->session.localParticipant, poffin_cooking_0223D4BC(), param1->comm);
                        param1->participantDataSent = 0;

                        for (v2 = 1; v2 < (7 + 1); v2++) {
                            if (CommSys_IsPlayerConnected(v2)) {
                                param1->syncCounters[v2]--;
                            }
                        }
                    }
                }
            } else {
                if (param1->syncCounter) {
                    v0 = poffin_cooking_0223D508(32, &param1->session.localParticipant.touchInput, poffin_cooking_0223D4C8(), param1->comm);
                    param1->syncCounter--;
                }
            }
        }
    } else {
        v0 = poffin_cooking_0223D508(26, &param1->session.localParticipant, poffin_cooking_0223D4BC(), param1->comm);
        param1->participantDataSent = 0;
    }

    if (v0 == 0) {
        (void)0;
    }

    poffin_cooking_0223C3E8(param1);
    poffin_cooking_0223EDA4(&param1->particleManager, &param1->session);
    poffin_cooking_0223F378(&param1->arrowManager);
    poffin_cooking_0223F52C(&param1->sparkleManager);

    return param1->state;
}

static int poffin_cooking_0223BCEC(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2)
{
    Poffin *v0;
    BOOL v1;

    poffin_cooking_0223EDA4(&param1->particleManager, &param1->session);

    switch (*param2) {
    case 0:
        poffin_cooking_0223E994(&param1->messageBox);
        poffin_cooking_0223F3D0(&param1->arrowManager, 0);
        poffin_cooking_0223F3D0(&param1->arrowManager, 1);
        poffin_cooking_0223F3D0(&param1->arrowManager, 2);
        poffin_cooking_0223F3D0(&param1->arrowManager, 3);
        poffin_cooking_0223E2E4(&param1->reactionSprite2);

        Sound_StopEffect(1722, 0);
        Sound_StopEffect(1723, 0);
        Sound_StopEffect(1727, 0);
        Sound_StopEffect(1729, 0);
        Sound_PlayEffect(SEQ_SE_DP_NM13_sseq);

        poffin_cooking_0223E484(&param1->burstEffect, 0, 0);
        poffin_cooking_0223E484(&param1->burstEffect, 1, 0);
        poffin_cooking_0223E484(&param1->burstEffect, 2, 0);
        (*param2)++;
        break;
    case 1:
        if (poffin_cooking_0223E32C(&param1->reactionSprite2) == 0) {
            break;
        }

        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, param1->heapID);
        (*param2)++;
        break;
    case 2:
        if (IsScreenFadeDone()) {
            if (param0->isOnline) {
                CommSys_SetRecvLimitEnabled(0);
            }
            (*param2)++;
        }
        break;
    case 3: {
        GameRecords *v2 = SaveData_GetGameRecords(param0->ctx->saveData);

        if (param1->isMultiplayer == 0) {
            GameRecords_IncrementTrainerScore(v2, TRAINER_SCORE_EVENT_UNK_12);
            GameRecords_IncrementRecordValue(v2, RECORD_UNK_052);
        } else {
            GameRecords_IncrementTrainerScore(v2, TRAINER_SCORE_EVENT_UNK_18);
            GameRecords_IncrementRecordValue(v2, RECORD_UNK_053);
        }
    }

        if (param1->isMultiplayer != 0) {
            WiFiList *v3 = SaveData_GetWiFiList(param0->ctx->saveData);
            int v4;
            int v5, v6;
            int v7;
            DWCFriendData *v8;

            for (v4 = 0; v4 < param1->playerCount; v4++) {
                v5 = param1->session.playerNetIDs[v4];
                v8 = CommInfo_DWCFriendData(v5);
                v6 = WiFiFriend_FindSlot(param0->ctx->saveData, v8, &v7);

                switch (v6) {
                case 0:
                case 1:
                    WiFiList_AddFriendPoffinSessions(v3, v7, 1);
                    break;
                default:
                    break;
                }
            }
        }

        (*param2)++;
        break;
    case 4:
        if (poffin_cooking_0223D570(param1->comm) == 0) {
            v0 = Poffin_New(param1->heapID);
            poffin_cooking_0223FFD4(&param1->simulation, v0, &param1->session, param1->playerCount, param1->heapID);
            v1 = poffin_cooking_0223D508(28, v0, Poffin_SizeOf(), param1->comm);
            Heap_Free(v0);

            if (v1 == 1) {
                (*param2)++;
            }
        } else {
            (*param2)++;
        }
        break;
    case 5:
        if (poffin_cooking_0223D570(param1->comm) == 0) {
            poffin_cooking_022401AC(&param1->simulation, &param1->session, param1->playerCount);
            v1 = poffin_cooking_0223D508(27, &param1->session.result, poffin_cooking_0223D4C0(), param1->comm);

            if (v1 == 1) {
                (*param2)++;
            }
        } else {
            (*param2)++;
        }
        break;
    case 6:
        return param1->state + 1;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return param1->state;
}

static int poffin_cooking_0223BF74(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2)
{
    u32 v0;
    BOOL v1;
    u8 v2;

    switch (*param2) {
    case 0:
        poffin_cooking_0223EC4C(&param1->messageBox, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);

        param1->updateSpriteList = 0;

        poffin_cooking_0223F730(&param1->poffinSprite, 128, 144, param1->session.receivedResult.poffinSpecies, param1->heapID);
        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, param1->heapID);
        (*param2)++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            (*param2)++;
            param1->timer = (30 * 1);
        }
        break;
    case 2:
        param1->timer--;

        if (param1->timer < 0) {
            poffin_cooking_0223EC4C(&param1->messageBox, 1);
            Sound_PlayEffect(SEQ_SE_DP_NM14_sseq);
            (*param2)++;
            param1->timer = (30 * 1);
        }
        break;
    case 3:
        param1->timer--;

        if (param1->timer < 0) {
            poffin_cooking_0223EC4C(&param1->messageBox, 2);
            poffin_cooking_0223F784(&param1->poffinSprite);
            Sound_PlayEffect(SEQ_SE_DP_NM14_sseq);
            (*param2)++;
            param1->timer = (30 * 20);
        }
        break;
    case 4:
        param1->timer--;

        if ((param1->timer < 0) || (gSystem.touchPressed) || (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B))) {
            (*param2)++;
            break;
        }

        poffin_cooking_0223F784(&param1->poffinSprite);
        break;
    case 5:
        poffin_cooking_0223F770(&param1->poffinSprite);
        poffin_cooking_0223EC70(&param1->messageBox);
        poffin_cooking_0223C8B0(param0, param1->session.poffin, param1->playerCount);
        poffin_cooking_0223EC8C(&param1->messageBox, 0);
        param1->timer = (30 * 5);
        (*param2)++;
        break;
    case 6:
        param1->timer--;

        if ((gSystem.touchPressed) || (param1->timer < 0) || (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B))) {
            (*param2)++;
        }
        break;
    case 7:
        poffin_cooking_0223EC8C(&param1->messageBox, 1);
        poffin_cooking_0223F7B0(&param1->yesNoMenu);
        (*param2)++;
        break;
    case 8:
        v0 = poffin_cooking_0223F7DC(&param1->yesNoMenu);

        if (v0 == YES_NO_TOUCH_MENU_YES || v0 == YES_NO_TOUCH_MENU_NO) {
            if (v0 == YES_NO_TOUCH_MENU_YES) {
                if (PoffinCase_CountFilledSlots(param0->ctx->poffinCase) >= MAX_POFFINS) {
                    poffin_cooking_0223EC8C(&param1->messageBox, 2);
                    (*param2) = 10;
                    param1->timer = (30 * 5);
                    break;
                }

                if (Bag_HasItemsInPocket(param0->ctx->bag, POCKET_BERRIES) == FALSE) {
                    poffin_cooking_0223EC8C(&param1->messageBox, 5);
                    (*param2) = 10;
                    param1->timer = (30 * 5);
                    break;
                }

                (*param2) = 9;
            } else {
                (*param2) = 11;
            }

            if (param1->playerCount > 1) {
                poffin_cooking_0223EC8C(&param1->messageBox, 6);
                poffin_cooking_0223E9BC(&param1->messageBox);
            }
        }
        break;
    case 9:
        param1->leaveRequest = 1;
        v1 = poffin_cooking_0223D508(30, &param1->leaveRequest, poffin_cooking_0223D4B0(), param1->comm);

        if (v1 == 1) {
            return param1->state + 1;
        }
        break;
    case 10:
        param1->timer--;

        if ((gSystem.touchPressed) || (param1->timer < 0) || (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B))) {
            if (param1->playerCount > 1) {
                poffin_cooking_0223EC8C(&param1->messageBox, 6);
                poffin_cooking_0223E9BC(&param1->messageBox);
            }
            (*param2) = 11;
        }
        break;
    case 11:
        param1->leaveRequest = 0;
        v1 = poffin_cooking_0223D508(30, &param1->leaveRequest, poffin_cooking_0223D4B0(), param1->comm);

        if (v1 == 1) {
            return param1->state + 1;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return param1->state;
}

static int poffin_cooking_0223C24C(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2)
{
    return poffin_cooking_0223CB5C(param1, param2);
}

static int poffin_cooking_0223C258(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2)
{
    switch (*param2) {
    case 0:
        if (param1->session.leaveResult == 1) {
            poffin_cooking_0223EC8C(&param1->messageBox, 3);
            param0->returnToBerrySelection = TRUE;
        } else {
            param0->returnToBerrySelection = FALSE;

            if (param1->playerCount <= 1) {
                (*param2) = 2;
                break;
            } else {
                poffin_cooking_0223EC8C(&param1->messageBox, 4);
            }

            void *journalEntryOnlineEvent;

            if (param1->isMultiplayer == 1) {
                journalEntryOnlineEvent = JournalEntry_CreateEventMadePoffins(param1->heapID);
                JournalEntry_SaveData(param0->ctx->journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
            }
        }

        param1->timer = (30 * 2);
        (*param2)++;
        break;
    case 1:
        param1->timer--;

        if (param1->timer < 0) {
            (*param2)++;
        }
        break;
    case 2:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, param1->heapID);
        (*param2)++;
        break;
    case 3:
        if (IsScreenFadeDone()) {
            (*param2)++;
        }
        break;
    case 4:
        poffin_cooking_0223CB8C(param1, param2);
        poffin_cooking_0223CAA4(param1);

        return param1->state + 1;
    }

    return param1->state;
}

static int poffin_cooking_0223C344(PoffinBerrySelectionData *param0, PoffinCookingApp *param1, int *param2)
{
    poffin_cooking_0223DB30(&param1->poffinAnim);
    poffin_cooking_0223DEC4(&param1->playerListDisplay);
    poffin_cooking_0223E260(&param1->reactionSprite);
    poffin_cooking_0223E260(&param1->reactionSprite2);
    poffin_cooking_0223E260(&param1->reactionSprite3);
    poffin_cooking_0223E34C(&param1->burstEffect);
    poffin_cooking_0223E5C0(&param1->playerCursor);
    poffin_cooking_0223E6F8(&param1->messageBox);
    poffin_cooking_0223ED4C(&param1->particleManager);
    poffin_cooking_0223F2A8(&param1->arrowManager);
    poffin_cooking_0223F4AC(&param1->sparkleManager);
    poffin_cooking_0223F7A4(&param1->yesNoMenu);
    poffin_cooking_0223C87C(param0, param1);
    poffin_cooking_0223B784(param1);

    return param1->state;
}

static void poffin_cooking_0223C3E8(PoffinCookingApp *param0)
{
    PoffinCookingBlendState *v0 = &param0->session.participants[0].blendState;
    fx32 v1;

    if (v0->direction == 0) {
        param0->stirRotation += v0->stirSpeed;
    } else {
        param0->stirRotation -= v0->stirSpeed;
    }

    poffin_cooking_0223E4A4(&param0->burstEffect, param0->stirRotation);
    poffin_cooking_0223C90C(param0);

    v1 = poffin_cooking_0223FB68(v0->stirSpeed, v0->stirLevel);

    poffin_cooking_0223E4C0(&param0->burstEffect, v1);
    poffin_cooking_0223E51C(&param0->burstEffect, v0->stirLevel);
    poffin_cooking_0223E658(&param0->playerCursor);
    poffin_cooking_0223C480(param0);
    poffin_cooking_0223C758(param0);
    poffin_cooking_0223C558(param0);
    poffin_cooking_0223C600(param0);
    poffin_cooking_0223C6D4(param0);
    poffin_cooking_0223C7FC(param0);

    {
        v0->perfectStir = 0;
        v0->stirChain = 0;
        v0->sparkleTrigger = 0;
        v0->releaseFlag = 0;
    }
}

static void poffin_cooking_0223C480(PoffinCookingApp *param0)
{
    PoffinCookingBlendState *v0 = &param0->session.participants[0].blendState;
    static const u8 v1[3][7] = {
        { 1, 1, 0, 1, 0, 0, 5 },
        { 0, 1, 1, 0, 1, 0, 6 },
        { 0, 0, 1, 0, 0, 1, 8 },
    };

    poffin_cooking_0223E484(&param0->burstEffect, 5, v1[v0->stirLevel][0]);
    poffin_cooking_0223E484(&param0->burstEffect, 6, v1[v0->stirLevel][1]);
    poffin_cooking_0223E484(&param0->burstEffect, 7, v1[v0->stirLevel][2]);
    poffin_cooking_0223E484(&param0->burstEffect, 0, v1[v0->stirLevel][3]);
    poffin_cooking_0223E484(&param0->burstEffect, 1, v1[v0->stirLevel][4]);
    poffin_cooking_0223E484(&param0->burstEffect, 2, v1[v0->stirLevel][5]);

    if (v1[v0->stirLevel][6] != 8) {
        if (v0->alpha > 0) {
            poffin_cooking_0223E4E0(&param0->burstEffect, v1[v0->stirLevel][6], v0->alpha);
        } else {
            poffin_cooking_0223E484(&param0->burstEffect, v1[v0->stirLevel][6], 0);
        }
    }
}

static void poffin_cooking_0223C558(PoffinCookingApp *param0)
{
    PoffinCookingBlendState *v0 = &param0->session.participants[0].blendState;

    if ((v0->arrowSide == v0->direction) || (v0->stirSpeed == 0) || (param0->arrowAnimState != 0)) {
        poffin_cooking_0223F3D0(&param0->arrowManager, 1);
        poffin_cooking_0223F3D0(&param0->arrowManager, 3);
        param0->arrowFacing = 0;
    } else {
        if (v0->arrowSide == 0) {
            if (param0->arrowFacing != 1) {
                poffin_cooking_0223F3A0(&param0->arrowManager, 1);
                param0->arrowFacing = 1;
                poffin_cooking_0223F3D0(&param0->arrowManager, 3);
                Sound_PlayEffect(SEQ_SE_DP_NM12_2_sseq);
            }
        } else {
            if (param0->arrowFacing != 2) {
                poffin_cooking_0223F3A0(&param0->arrowManager, 3);
                param0->arrowFacing = 2;
                poffin_cooking_0223F3D0(&param0->arrowManager, 1);
                Sound_PlayEffect(SEQ_SE_DP_NM12_2_sseq);
            }
        }
    }
}

static void poffin_cooking_0223C600(PoffinCookingApp *param0)
{
    PoffinCookingBlendState *v0 = &param0->session.participants[0].blendState;
    static const u8 v1[3] = {
        1, 3, 0
    };
    static const u8 v2[3] = {
        0, 2, 4
    };

    if ((param0->arrowFacing != 0) || (param0->arrowAnimState != 0)) {
        poffin_cooking_0223E994(&param0->messageBox);
        param0->extraStirMessageShown = 0;
        param0->stirMessageShown = 0;
    } else {
        if (param0->extraStirMessageShown == 0) {
            if (v0->perfectStir) {
                poffin_cooking_0223E994(&param0->messageBox);
                poffin_cooking_0223E908(&param0->messageBox, v1[v0->stirLevel]);
                param0->extraStirMessageShown = 1;
                param0->stirMessageShown = 0;
            }
        } else {
            if (poffin_cooking_0223E984(&param0->messageBox)) {
                param0->extraStirMessageShown = 0;
            }
        }

        if (param0->stirMessageShown == 0) {
            if (v0->stirChain) {
                poffin_cooking_0223E994(&param0->messageBox);
                poffin_cooking_0223E908(&param0->messageBox, v2[v0->stirLevel]);
                param0->stirMessageShown = 1;
                param0->extraStirMessageShown = 0;
            }
        } else {
            if (poffin_cooking_0223E984(&param0->messageBox)) {
                param0->stirMessageShown = 0;
            }
        }
    }
}

static void poffin_cooking_0223C6D4(PoffinCookingApp *param0)
{
    PoffinCookingBlendState *v0 = &param0->session.participants[0].blendState;
    static const u32 v1[3] = {
        1714, 1720, 1720
    };
    static const u32 v2[3] = {
        1715, 1715, 1723
    };

    if (v0->perfectStir) {
        poffin_cooking_0223EDDC(&param0->particleManager, v0->stirLevel, 2);
        Sound_PlayEffect(v1[v0->stirLevel]);
    }

    if (v0->stirChain == 1) {
        poffin_cooking_0223EDDC(&param0->particleManager, v0->stirLevel, 1);
        Sound_PlayEffect(v2[v0->stirLevel]);
    } else if (v0->stirChain == 2) {
        poffin_cooking_0223EDDC(&param0->particleManager, v0->stirLevel, 0);
    }

    if (poffin_cooking_0223FB50(v0->stirSpeed, v0->stirLevel) == 0) {
        poffin_cooking_0223EFCC(&param0->particleManager);
    }
}

static void poffin_cooking_0223C758(PoffinCookingApp *param0)
{
    PoffinCookingBlendState *v0 = &param0->session.participants[0].blendState;
    BOOL v1;

    if (v0->releaseFlag) {
        if (v0->arrowSide == 0) {
            poffin_cooking_0223F3A0(&param0->arrowManager, 0);
            poffin_cooking_0223F3D0(&param0->arrowManager, 2);
            Sound_PlayEffect(SEQ_SE_DP_NM12_2_sseq);
            param0->arrowAnimState = 1;
        } else {
            poffin_cooking_0223F3A0(&param0->arrowManager, 2);
            poffin_cooking_0223F3D0(&param0->arrowManager, 0);
            Sound_PlayEffect(SEQ_SE_DP_NM12_2_sseq);
            param0->arrowAnimState = 2;
        }
    }

    if (param0->arrowAnimState == 1) {
        v1 = poffin_cooking_0223F3F0(&param0->arrowManager, 0);

        if (v1 == 1) {
            param0->arrowAnimState = 0;
        }
    } else if (param0->arrowAnimState == 2) {
        v1 = poffin_cooking_0223F3F0(&param0->arrowManager, 2);

        if (v1 == 1) {
            param0->arrowAnimState = 0;
        }
    }
}

static void poffin_cooking_0223C7FC(PoffinCookingApp *param0)
{
    PoffinCookingBlendState *v0 = &param0->session.participants[0].blendState;
    int v1 = param0->session.localParticipant.touchInput.x;
    int v2 = param0->session.localParticipant.touchInput.y;

    if (v0->sparkleTrigger == 1) {
        poffin_cooking_0223F544(&param0->sparkleManager, v1, v2);
        Sound_PlayEffect(SEQ_SE_DP_NM11_sseq);
    }
}

static void poffin_cooking_0223C82C(PoffinBerrySelectionData *param0, PoffinCookingApp *param1)
{
    int v0;

    param1->session.poffin = Poffin_New(param1->heapID);
    param1->session.localPlayerIndex = poffin_cooking_0223D570(param1->comm);

    for (v0 = 0; v0 < 4; v0++) {
        param1->session.participants[v0].touchInput.x = 128;
        param1->session.participants[v0].touchInput.y = 96;
    }

    if (param0->isOnline) {
        CommSys_SetSendInterval(2);
    }
}

static void poffin_cooking_0223C87C(PoffinBerrySelectionData *param0, PoffinCookingApp *param1)
{
    GF_ASSERT(param1->session.poffin);

    Heap_Free(param1->session.poffin);
    param1->session.poffin = NULL;

    if (param0->isOnline) {
        CommSys_SetSendInterval(0);
    }
}

static BOOL poffin_cooking_0223C8B0(PoffinBerrySelectionData *param0, Poffin *param1, int param2)
{
    int v0;
    u16 v1;
    int v2;
    BOOL v3 = 1;
    TVBroadcast *broadcast = SaveData_GetTVBroadcast(param0->ctx->saveData);

    for (v0 = 0; v0 < param2; v0++) {
        v1 = PoffinCase_AddPoffin(param0->ctx->poffinCase, param1);

        if (v1 == POFFIN_NONE) {
            v3 = 0;
            break;
        }
    }

    if (param0->isOnline == 0) {
        v2 = Poffin_GetAttribute(param1, 0);
        TVBroadcast_SetPoffinCornerInfo(broadcast, v2);
    }

    return v3;
}

static void poffin_cooking_0223C90C(PoffinCookingApp *param0)
{
    PoffinCookingBlendState *v0 = &param0->session.participants[0].blendState;
    static const u32 v1[3] = {
        1713,
        1718,
        1722,
    };

    if (((v0->direction == 0) && (param0->lastStirAngle > v0->angle)) || ((v0->direction == 1) && (param0->lastStirAngle < v0->angle))) {
        Sound_PlayEffect(v1[v0->stirLevel]);
    }

    param0->lastStirAngle = v0->angle;
}
