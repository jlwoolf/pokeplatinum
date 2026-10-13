#include "wifi_lobby_map/wifi_lobby_map_02265F38.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_022324F0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222E294.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C9B4.h"
#include "wifi_lobby_map/wifi_lobby_map_0225D9A4.h"
#include "wifi_lobby_map/wifi_lobby_map_02262DA8.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_app_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_task_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_recruit_substate.h"

#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "enums.h"
#include "list_menu.h"
#include "sound_playback.h"
#include "string_gf.h"
#include "system.h"
#include "comm_tool.h"

typedef struct {
    u8 isRecruiting;
    u8 openSlots;
    u8 isAcceptingPlayers;
    u8 activity;
    s16 timeSeconds;
    u8 showTimer;
    u8 redrawFlags;
} WiFiLobbyMapRecruitDisplay;

typedef struct {
    s16 timeLimit;
    u16 recruitInfoUpdated;
    u8 nextState;
    s8 syncDelay;
    u8 syncID;
    u8 unk_07;
    u16 playerCount;
    u16 syncTimer;
    s32 userID;
    s32 countdown;
    BOOL messageDisplayed;
    ListMenuTemplate listTemplate;
    u32 entryCount;
    WiFiLobbyMapRecruitDisplay display;
} WiFiLobbyMapRecruitWork;

typedef struct {
    WiFiLobbyMapRecruitDisplay display;
} WiFiLobbyMapActivityTaskState;

static void wifi_lobby_map_02266AF0(WiFiLobbyMapRecruitWork *param0, WiFiLobbyMapTask *param1, WiFiLobbyMapApp *param2, u32 param3, u32 param4);
static void wifi_lobby_map_02266B18(WiFiLobbyMapRecruitWork *param0, WiFiLobbyMapTask *param1, u32 param2, u32 param3);
static void wifi_lobby_map_02266B30(WiFiLobbyMapRecruitWork *param0, WiFiLobbyMapApp *param1, u32 param2, u32 param3);
static void wifi_lobby_map_02266BA0(WiFiLobbyMapRecruitWork *param0, WiFiLobbyMapApp *param1);
static BOOL wifi_lobby_map_02266BAC(WiFiLobbyMapRecruitWork *param0, WiFiLobbyMapApp *param1, WiFiLobbyMapRecruitSubstate *param2, WiFiLobbyMapTask *param3, u32 param4);
static void wifi_lobby_map_02266C68(WiFiLobbyMapRecruitDisplay *param0, WiFiLobbyMapApp *param1, u32 param2, u32 param3, s32 param4);
static void wifi_lobby_map_02266CB0(WiFiLobbyMapRecruitDisplay *param0, WiFiLobbyMapApp *param1);
static void wifi_lobby_map_02266CCC(WiFiLobbyMapRecruitDisplay *param0, s32 param1);
static void wifi_lobby_map_02266CFC(WiFiLobbyMapRecruitDisplay *param0, WiFiLobbyMapApp *param1, BOOL param2);
static void wifi_lobby_map_02266CF0(WiFiLobbyMapRecruitDisplay *param0, WiFiLobbyMapApp *param1, BOOL param2);
static void wifi_lobby_map_02266D08(WiFiLobbyMapRecruitDisplay *param0, WiFiLobbyMapApp *param1, BOOL param2, BOOL param3);

static const ListMenuTemplate Unk_wifi_lobby_map_0226DC94 = {
    NULL,
    NULL,
    NULL,
    NULL,
    0x0,
    0x3,
    0x0,
    0x8,
    0x0,
    0x0,
    0x1,
    0xF,
    0x2,
    0x0,
    0x10,
    0x0,
    0x0,
    0x0,
    NULL
};

BOOL wifi_lobby_map_02265F38(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapRecruitWork *v0;
    WiFiLobbyMapRecruitSubstate *v1;
    WiFiPlazaLobbyState *v2;

    v1 = wifi_lobby_map_02262E38(param0);
    v0 = wifi_lobby_map_02262E80(param0);
    v2 = wifi_lobby_map_0225DEE8(param1);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 26:
    case 27:
        if (v0->playerCount > WiFiPlazaLobby_Network_GetRecruitPlayerCount(v1->network)) {
            v1->state = 4;
            wifi_lobby_map_02262E88(param0, 23);
            break;
        }

        if (v0->playerCount > CommSys_ConnectedCount()) {
            v1->state = 4;
            wifi_lobby_map_02262E88(param0, 23);
            break;
        }

        if (CommManager_GetWifiP2PConnectState() == 0) {
            v1->state = 4;
            wifi_lobby_map_02262E88(param0, 23);
            break;
        }
    case 8:
        if (WiFiPlazaLobby_Network_IsRecruiting() == 1) {
            if (WiFiPlazaLobby_Network_GetRecruitPlayerCount(v1->network) <= 1) {
                v1->state = 4;
                wifi_lobby_map_02262E88(param0, 23);
                break;
            }
        }

        v0->countdown--;

        if (v0->countdown < 0) {
            v1->state = 4;
            wifi_lobby_map_02262E88(param0, 23);
            break;
        }
    case 7:
    case 18:
    case 17:
    case 19:
    case 20:
    case 21:
    case 22:
        switch (CommManager_GetMatchmakingState()) {
        case 2:
        case 3:
        case 4:
        case 5:
            v1->state = 4;
            wifi_lobby_map_02262E88(param0, 23);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        v0 = wifi_lobby_map_02262E3C(param0, sizeof(WiFiLobbyMapRecruitWork));
        wifi_lobby_map_02262E8C(param0);
        break;
    case 1:
        if (WiFiPlazaLobby_State_IsWarpTimerActive(v2)) {
            v1->state = 7;
            wifi_lobby_map_02262E88(param0, 28);
            break;
        }

        if (WiFiPlazaLobby_State_IsMinigameFinished(v2)) {
            v1->state = 2;
            wifi_lobby_map_02262E88(param0, 28);
            break;
        }

        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        wifi_lobby_map_02262E8C(param0);
        break;
    case 2:
        wifi_lobby_map_0225E27C(param1, v1->activity, 0);
        wifi_lobby_map_02266AF0(v0, param0, param1, 0, 3);
        break;
    case 3:
        wifi_lobby_map_02266B30(v0, param1, 3, 1);
        wifi_lobby_map_0225E074(param1, &v0->listTemplate, 0, 0);
        wifi_lobby_map_02262E88(param0, 4);
        break;
    case 4: {
        u32 v3;
        BOOL v4 = 0;

        v3 = wifi_lobby_map_0225E0D4(param1);

        switch (v3) {
        case 0xfffffffe:
        case 2:
            v1->state = 5;
            wifi_lobby_map_02262E88(param0, 28);
            v4 = 1;
            break;
        case 1:
            wifi_lobby_map_02262E88(param0, 5);
            v4 = 1;
            break;
        case 0:
            wifi_lobby_map_02262E88(param0, 6);
            v4 = 1;
            break;
        default:
            break;
        }

        if (v4 == 1) {
            wifi_lobby_map_0225E0E4(param1, NULL, NULL);
            wifi_lobby_map_02266BA0(v0, param1);
        }
    } break;
    case 5:
        wifi_lobby_map_0225E27C(param1, v1->activity, 0);
        wifi_lobby_map_02266AF0(v0, param0, param1, v1->activity + 34, 2);
        break;
    case 6:
        if (WiFiPlazaLobby_State_IsMinigameFinished(v2)) {
            v1->state = 2;
            wifi_lobby_map_02262E88(param0, 28);
            break;
        }

        if (WiFiPlazaLobby_Network_IsGameRecruiting(v1->network) == 1) {
            if ((WiFiPlazaLobby_Network_GetRecruitOpenSlots(v1->network) == 0) || (WiFiPlazaLobby_Network_IsRecruitAcceptingPlayers(v1->network) == 0)) {
                v1->state = 1;
                wifi_lobby_map_02262E88(param0, 28);
                break;
            }

            if (WiFiPlazaLobby_Network_GetRecruitTimeLimit(v1->network) == 0) {
                v1->state = 7;
                wifi_lobby_map_02262E88(param0, 28);
                break;
            }
        }

        v0->timeLimit = WiFiPlazaLobby_Network_GetRecruitTimeLimit(v1->network);
        v0->countdown = (30 * 30);

        {
            String *v5;

            if (v0->timeLimit > (11 * 30)) {
                v5 = wifi_lobby_map_0225E20C(param1, 0, 10);
            } else {
                v0->messageDisplayed = 1;
                v5 = wifi_lobby_map_0225E20C(param1, 0, 11);
            }

            wifi_lobby_map_0225DF9C(param1, v5);
            wifi_lobby_map_0225DFBC(param1);
        }

        CommManager_StartWifiP2P(v1->network);

        if (WiFiPlazaLobby_Network_IsRecruiting() == 1) {
            WiFiPlazaLobby_State_SendMinigameProfileViewMessage(v2, v1->activity, 1, param2, 0, 0, 0, 0);
            v0->unk_07 = 1;
        }

        wifi_lobby_map_02266C68(&v0->display, param1, v1->activity, 1, v0->timeLimit);
        wifi_lobby_map_02266CFC(&v0->display, param1, 1);
        wifi_lobby_map_02262E88(param0, 7);
        break;
    case 7: {
        u32 v6;
        u32 v7;

        v6 = CommManager_GetWifiP2PConnectState();
        v7 = WiFiPlazaLobby_Network_GetRecruitPlayerCount(v1->network);
        v0->timeLimit = WiFiPlazaLobby_Network_GetRecruitTimeLimit(v1->network);

        wifi_lobby_map_02266CCC(&v0->display, v0->timeLimit);

        if ((v0->timeLimit <= (11 * 30)) && (v0->messageDisplayed == 0)) {
            String *v8;

            wifi_lobby_map_0225DFCC(param1);

            v0->messageDisplayed = 1;
            v8 = wifi_lobby_map_0225E20C(param1, 0, 11);

            wifi_lobby_map_0225DF9C(param1, v8);
            wifi_lobby_map_0225DFBC(param1);
        }

        wifi_lobby_map_02266CF0(&v0->display, param1, 0);

        if (v6 == 0) {
            v1->state = 4;
            wifi_lobby_map_02262E88(param0, 23);
            break;
        }

        if (v6 == 2) {
            v1->state = 8;

            {
                u32 v9;
                String *v10;

                if (v7 == 4) {
                    v9 = 16;
                } else {
                    v9 = 18;
                }

                wifi_lobby_map_0225DFCC(param1);

                v10 = wifi_lobby_map_0225E20C(param1, 0, v9);

                wifi_lobby_map_0225DF9C(param1, v10);
                wifi_lobby_map_0225DFBC(param1);
                wifi_lobby_map_02262E88(param0, 9);

                v0->playerCount = v7;
            }

            wifi_lobby_map_02266CCC(&v0->display, 0);
            wifi_lobby_map_02266CF0(&v0->display, param1, 0);
            break;
        }

        if (v0->messageDisplayed == 0) {
            if (gSystem.pressedKeys & PAD_BUTTON_B) {
                Sound_PlayEffect(SE_CONFIRM_sseq_3);

                if (WiFiPlazaLobby_Network_IsRecruiting() == 0) {
                    v1->state = 6;
                    wifi_lobby_map_0225DFCC(param1);
                    wifi_lobby_map_02262E88(param0, 23);
                } else {
                    v1->state = 6;
                    wifi_lobby_map_0225DFCC(param1);
                    wifi_lobby_map_02262E88(param0, 16);
                }
                break;
            }
        }

        if (WiFiPlazaLobby_Network_IsRecruiting() == 1) {
            if (v0->unk_07 != v7) {
                v0->unk_07 = v7;

                if (v7 != 4) {
                    WiFiPlazaLobby_State_SendMinigameProfileViewMessage(v2, v1->activity, v7, param2, 0, 0, 0, 0);
                }
            }

            if (v0->timeLimit == 0) {
                if (WiFiPlazaLobby_Network_GetRecruitPlayerCount(v1->network) <= 1) {
                    v1->state = 3;
                    wifi_lobby_map_02262E88(param0, 23);
                    break;
                }
            }
        }

        if ((WiFiPlazaLobby_Network_IsGameRecruiting(v1->network) == 1) && (WiFiPlazaLobby_Network_IsRecruitAcceptingPlayers(v1->network) == 0)) {
            v1->state = 0;
            wifi_lobby_map_02262E88(param0, 23);
            break;
        }

        if (v0->timeLimit == 0) {
            wifi_lobby_map_02262E88(param0, 8);
            {
                String *v11;

                wifi_lobby_map_0225DFCC(param1);
                v11 = wifi_lobby_map_0225E20C(param1, 0, 18);
                wifi_lobby_map_0225DF9C(param1, v11);
                wifi_lobby_map_0225DFBC(param1);
            }
            break;
        }
    } break;

    case 8: {
        u32 v12;
        u32 v13;

        wifi_lobby_map_02266CCC(&v0->display, 0);
        wifi_lobby_map_02266CF0(&v0->display, param1, 0);

        v12 = CommManager_GetWifiP2PConnectState();
        v13 = WiFiPlazaLobby_Network_GetRecruitPlayerCount(v1->network);

        switch (CommManager_GetMatchmakingState()) {
        case 3:
        case 4:
            v1->state = 4;
            wifi_lobby_map_02262E88(param0, 23);
            break;
        default:
            break;
        }

        if (v12 == 0) {
            v1->state = 4;
            wifi_lobby_map_02262E88(param0, 23);
            break;
        }

        if (v12 == 2) {
            v1->state = 8;
            wifi_lobby_map_02262E88(param0, 9);
            v0->playerCount = v13;
            break;
        }

        if ((WiFiPlazaLobby_Network_IsGameRecruiting(v1->network) == 1) && (WiFiPlazaLobby_Network_IsRecruitAcceptingPlayers(v1->network) == 0)) {
            v1->state = 0;
            wifi_lobby_map_02262E88(param0, 23);
            break;
        }
    } break;
    case 9:
        wifi_lobby_map_02266CCC(&v0->display, 0);
        wifi_lobby_map_02266CF0(&v0->display, param1, 0);
        WiFiPlazaLobby_State_SetCurrentVenue(wifi_lobby_map_0225DEE8(param1), v1->venue);

        CommManager_SetState_WifiPlaza();
        CommInfo_Init(WiFiPlazaLobby_State_GetSaveData(wifi_lobby_map_0225DEE8(param1)), NULL);
        CommInfo_SetPersonalTrainerInfo(WiFiPlazaLobby_State_GetLocalTrainerInfo(v2));
        CommSys_SetRecvLimitEnabled(0);
        wifi_lobby_map_02266B18(v0, param0, 10, 17);
        break;
    case 10:
        wifi_lobby_map_02266CCC(&v0->display, 0);
        wifi_lobby_map_02266CF0(&v0->display, param1, 0);

        CommInfo_SendPlayerInfo();
        CommInfo_MarkDataRead(CommSys_CurNetId());

        wifi_lobby_map_02262E88(param0, 11);
        break;
    case 11:

        wifi_lobby_map_02266CCC(&v0->display, 0);
        wifi_lobby_map_02266CF0(&v0->display, param1, 0);

        {
            int v14;

            while ((v14 = CommInfo_NewNetworkId()) != 0xff) {
                CommInfo_MarkDataRead(v14);
            }
        }

        if (CommInfo_CountReceived() >= WiFiPlazaLobby_Network_GetRecruitPlayerCount(v1->network)) {
            if (WiFiPlazaLobby_Network_IsRecruiting() == 1) {
                if (v0->recruitInfoUpdated == 0) {
                    WiFiPlazaLobby_Network_UpdateRecruitInfo();
                    v0->recruitInfoUpdated = 1;
                }
            }

            if (WiFiPlazaLobby_Network_IsCurrentRecruitUpdated() == 1) {
                wifi_lobby_map_02262E88(param0, 12);
            }
        } else {
            if (WiFiPlazaLobby_Network_IsCurrentRecruitUpdated() == 1) {
                v1->state = 4;
                wifi_lobby_map_02262E88(param0, 23);
            }
        }
        break;
    case 12:
        wifi_lobby_map_02266CCC(&v0->display, 0);
        wifi_lobby_map_02266CF0(&v0->display, param1, 0);

        CommTool_ClearReceivedTempDataAllPlayers();

        WiFiPlazaLobby_State_ClearUserIDTable(v2);
        wifi_lobby_map_02266B18(v0, param0, 13, 14);
        break;
    case 13: {
        BOOL v15;

        wifi_lobby_map_02266CCC(&v0->display, 0);
        wifi_lobby_map_02266CF0(&v0->display, param1, 0);

        v0->userID = WiFiPlazaLobby_State_GetMyUserID(v2);
        v15 = CommTool_SendTempData(CommSys_CurNetId(), &v0->userID);

        if (v15 == 1) {
            wifi_lobby_map_02262E88(param0, 14);
        }
    } break;
    case 14:
        wifi_lobby_map_02266CCC(&v0->display, 0);
        wifi_lobby_map_02266CF0(&v0->display, param1, 0);

        {
            int v16;
            int v17;
            int v18;
            const s32 *v19;
            int v20;
            BOOL v21;
            s32 v22;

            v17 = CommInfo_CountReceived();
            v18 = CommSys_CurNetId();
            v20 = 0;
            v21 = 0;
            v22 = WiFiPlazaLobby_Network_GetRecruitHostUserId();

            for (v16 = 0; v16 < v17; v16++) {
                if (v18 != v16) {
                    v19 = CommTool_GetReceivedTempData(v16);

                    if (v19 != NULL) {
                        WiFiPlazaLobby_State_SetPlayerSlotUserID(v2, v19[0], v16);

                        if (v19[0] == v22) {
                            v21 = 1;
                        }

                        v20++;
                    }
                } else {
                    WiFiPlazaLobby_State_SetMyPlayerSlot(v2, v16);

                    if (WiFiPlazaLobby_Network_IsRecruiting() == 1) {
                        v21 = 1;
                    }

                    v20++;
                }
            }

            if (v20 == v17) {
                if (v21 == 1) {
                    wifi_lobby_map_02262E88(param0, 15);
                } else {
                    v1->state = 4;
                    wifi_lobby_map_02262E88(param0, 23);
                }
            }
        }
        break;
    case 15:
        CommManager_SetErrorHandling(0, 1);

        if (WiFiPlazaLobby_Network_IsRecruiting() == 1) {
            int v23;
            WiFiPlazaLobbyQuestionnaireData v24;

            WiFiPlazaLobby_State_GetUserIDTable(v2, &v24);
            v23 = WiFiPlazaLobby_Network_GetRecruitPlayerCount(v1->network);
            WiFiPlazaLobby_State_SendMinigameProfileViewMessage(v2, v1->activity, v23, v24.unk_00[0], v24.unk_00[1], v24.unk_00[2], v24.unk_00[3], 1);
        }

        wifi_lobby_map_0225DFCC(param1);
        wifi_lobby_map_02266B18(v0, param0, 28, 18);
        break;
    case 16: {
        String *v25;

        v25 = wifi_lobby_map_0225E20C(param1, 0, 26);
        wifi_lobby_map_0225DF8C(param1, v25);
    }

        wifi_lobby_map_02262E88(param0, 17);
        wifi_lobby_map_02266CB0(&v0->display, param1);
        break;
    case 17: {
        BOOL v26;

        v26 = wifi_lobby_map_02266BAC(v0, param1, v1, param0, param2);

        if (v26 == 0) {
            if (wifi_lobby_map_0225DFAC(param1) == 1) {
                wifi_lobby_map_02262E88(param0, 18);
            }
        }
    } break;
    case 18:
        wifi_lobby_map_0225E194(param1);
        wifi_lobby_map_02262E88(param0, 19);
        break;
    case 19: {
        int v27;

        v27 = wifi_lobby_map_0225E1C4(param1);

        switch (v27) {
        case 0:
            wifi_lobby_map_0225E1F8(param1);
            wifi_lobby_map_02262E88(param0, 23);
            WiFiPlazaLobby_State_StartWarpTimer(v2);
            break;
        case 1:
            wifi_lobby_map_0225E1F8(param1);
            wifi_lobby_map_02262E88(param0, 20);
            break;
        case 2: {
            BOOL v28;

            v28 = wifi_lobby_map_02266BAC(v0, param1, v1, param0, param2);

            if (v28 == 1) {
                wifi_lobby_map_0225E1F8(param1);
            }
        } break;
        }
    } break;
    case 20:
        v0->timeLimit = WiFiPlazaLobby_Network_GetRecruitTimeLimit(v1->network);

        wifi_lobby_map_02266C68(&v0->display, param1, v1->activity, 1, v0->timeLimit);
        wifi_lobby_map_02266CFC(&v0->display, param1, 1);

        {
            String *v29;

            if (v0->timeLimit > (11 * 30)) {
                v29 = wifi_lobby_map_0225E20C(param1, 0, 10);
            } else {
                v0->messageDisplayed = 1;
                v29 = wifi_lobby_map_0225E20C(param1, 0, 11);
            }

            wifi_lobby_map_0225DF9C(param1, v29);
            wifi_lobby_map_0225DFBC(param1);
        }
        wifi_lobby_map_02262E88(param0, 7);
        break;
    case 21: {
        u32 v30;

        v30 = WiFiPlazaLobby_Network_GetRecruitPlayerCount(v1->network);
        v1->state = 8;

        {
            u32 v31;
            String *v32;

            if (v30 == 4) {
                v31 = 16;
            } else {
                v31 = 18;
            }

            v32 = wifi_lobby_map_0225E20C(param1, 0, v31);

            wifi_lobby_map_0225DF9C(param1, v32);
            wifi_lobby_map_0225DFBC(param1);
            wifi_lobby_map_02262E88(param0, 9);
        }

        wifi_lobby_map_02266C68(&v0->display, param1, v1->activity, 1, 0);
        wifi_lobby_map_02266CFC(&v0->display, param1, 1);
    } break;
    case 22: {
        String *v33;

        v33 = wifi_lobby_map_0225E20C(param1, 0, 18);

        wifi_lobby_map_0225DF9C(param1, v33);
        wifi_lobby_map_0225DFBC(param1);
        wifi_lobby_map_02266C68(&v0->display, param1, v1->activity, 1, 0);
        wifi_lobby_map_02266CCC(&v0->display, 0);
        wifi_lobby_map_02266CF0(&v0->display, param1, 1);
        wifi_lobby_map_02262E88(param0, 8);
    } break;
    case 23:
        CommInfo_Delete();
        CommManager_EndWifiP2P();
        wifi_lobby_map_02262E88(param0, 24);
        break;
    case 24: {
        u32 v34;

        v34 = CommManager_GetWifiP2PConnectState();

        if (v34 == 0) {
            wifi_lobby_map_02262E88(param0, 28);
        }
    } break;
    case 25:
        if (wifi_lobby_map_0225DFAC(param1) == 1) {
            wifi_lobby_map_02262E88(param0, v0->nextState);
        }
        break;
    case 26:
        if (v0->syncDelay > 0) {
            v0->syncDelay--;
        }

        if (v0->syncDelay == 0) {
            CommTiming_StartSync(v0->syncID);
            wifi_lobby_map_02262E88(param0, 27);
        }
        break;
    case 27:
        v0->syncTimer++;

        if (v0->syncTimer >= (5 * 30)) {
            CommTiming_StartSync(v0->syncID);
            v0->syncTimer = 0;
        }

        if (CommTiming_IsSyncState(v0->syncID)) {
            wifi_lobby_map_02262E88(param0, v0->nextState);
        }
        break;
    case 28: {
        wifi_lobby_map_0225DFEC(param1);
        wifi_lobby_map_02266BA0(v0, param1);
        wifi_lobby_map_02266CB0(&v0->display, param1);
    }

        wifi_lobby_map_02262E64(param0);
        return 1;
    }

    return 0;
}

BOOL wifi_lobby_map_022669B8(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        CommManager_SetErrorHandling(0, 0);

        if (CommManager_IsLoginBattleMatchWifi() == 0) {
            CommInfo_Delete();
            CommManager_EndWifiP2P();
        }

        wifi_lobby_map_02262E88(param0, 1);
        break;
    case 1:
        if (CommManager_IsLoginBattleMatchWifi() == 1) {
            return 1;
        }
        break;
    }

    return 0;
}

BOOL wifi_lobby_map_022669FC(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapActivityTaskState *v0 = wifi_lobby_map_02262E80(param0);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0: {
        String *v1;
        u32 v2;
        u32 v3;
        u32 v4;

        v0 = wifi_lobby_map_02262E3C(param0, sizeof(WiFiLobbyMapActivityTaskState));
        v2 = wifi_lobby_map_0225DF40(param1);

        switch (v2) {
        case 39:
            v3 = 42;
            v4 = WiFiPlazaLobbyActivity_00;
            break;
        case 40:
            v3 = 41;
            v4 = WiFiPlazaLobbyActivity_01;
            break;
        case 41:
            v3 = 43;
            v4 = WiFiPlazaLobbyActivity_02;
            break;
        default:
            GF_ASSERT(FALSE);
            return 1;
        }

        wifi_lobby_map_0225E27C(param1, v4, 0);

        v1 = wifi_lobby_map_0225E20C(param1, 1, v3);

        wifi_lobby_map_0225DFFC(param1, v1);
        wifi_lobby_map_02266C68(&v0->display, param1, v4, 0, 0);
        wifi_lobby_map_02266CFC(&v0->display, param1, 1);
        wifi_lobby_map_02262E8C(param0);
    } break;
    case 1:
        if ((gSystem.pressedKeys & PAD_BUTTON_A) || (gSystem.pressedKeys & PAD_KEY_RIGHT) || (gSystem.pressedKeys & PAD_KEY_LEFT) || (gSystem.pressedKeys & PAD_KEY_DOWN)) {
            wifi_lobby_map_02266CB0(&v0->display, param1);
            wifi_lobby_map_0225DFEC(param1);

            {
                WiFiLobbyMapActorManager *v5;
                WiFiLobbyMapActor *v6;

                v5 = wifi_lobby_map_0225DEF0(param1);
                v6 = wifi_lobby_map_0225CCAC(v5);

                wifi_lobby_map_0225CDEC(v5, v6, 1);
            }

            wifi_lobby_map_02262E64(param0);
            return 1;
        } else {
            wifi_lobby_map_02266CFC(&v0->display, param1, 0);
        }
        break;
    }

    return 0;
}

static void wifi_lobby_map_02266AF0(WiFiLobbyMapRecruitWork *param0, WiFiLobbyMapTask *param1, WiFiLobbyMapApp *param2, u32 param3, u32 param4)
{
    String *v0 = wifi_lobby_map_0225E20C(param2, 0, param3);
    wifi_lobby_map_0225DF8C(param2, v0);
    param0->nextState = param4;
    wifi_lobby_map_02262E88(param1, 25);
}

static void wifi_lobby_map_02266B18(WiFiLobbyMapRecruitWork *param0, WiFiLobbyMapTask *param1, u32 param2, u32 param3)
{
    param0->nextState = param2;
    param0->syncID = param3;
    param0->syncDelay = 0;
    param0->syncTimer = 0;

    wifi_lobby_map_02262E88(param1, 26);
}

static void wifi_lobby_map_02266B30(WiFiLobbyMapRecruitWork *param0, WiFiLobbyMapApp *param1, u32 param2, u32 param3)
{
    int v0;
    String *v1;

    wifi_lobby_map_0225E00C(param1, param2);

    param0->entryCount = param2;

    for (v0 = 0; v0 < param2; v0++) {
        v1 = wifi_lobby_map_0225E20C(param1, 0, param3 + v0);
        wifi_lobby_map_0225E044(param1, v1, v0);
    }

    param0->listTemplate = Unk_wifi_lobby_map_0226DC94;
    param0->listTemplate.count = param0->entryCount;

    if (param0->listTemplate.maxDisplay > param0->unk_38) {
        param0->listTemplate.maxDisplay = param0->entryCount;
    }

    param0->listTemplate.choices = wifi_lobby_map_0225E054(param1);
}

static void wifi_lobby_map_02266BA0(WiFiLobbyMapRecruitWork *param0, WiFiLobbyMapApp *param1)
{
    wifi_lobby_map_0225E034(param1);
}

static BOOL wifi_lobby_map_02266BAC(WiFiLobbyMapRecruitWork *param0, WiFiLobbyMapApp *param1, WiFiLobbyMapRecruitSubstate *param2, WiFiLobbyMapTask *param3, u32 param4)
{
    u32 v0;
    u32 v1;
    WiFiPlazaLobbyState *v2 = wifi_lobby_map_0225DEE8(param1);
    v0 = CommManager_GetWifiP2PConnectState();
    v1 = WiFiPlazaLobby_Network_GetRecruitPlayerCount(param2->network);

    if (v0 == 0) {
        param2->state = 4;
        wifi_lobby_map_02262E88(param3, 23);
        return 1;
    }

    if (v0 == 2) {
        param0->playerCount = v1;
        wifi_lobby_map_02262E88(param3, 21);
        return 1;
    }

    if (param0->unk_07 != v1) {
        param0->unk_07 = v1;

        if (v1 != 4) {
            WiFiPlazaLobby_State_SendMinigameProfileViewMessage(v2, param2->activity, v1, param4, 0, 0, 0, 0);
        }
    }

    param0->timeLimit = WiFiPlazaLobby_Network_GetRecruitTimeLimit(param2->network);

    if (param0->timeLimit == 0) {
        if (WiFiPlazaLobby_Network_GetRecruitPlayerCount(param2->network) <= 1) {
            param2->state = 3;
            wifi_lobby_map_02262E88(param3, 23);
            return 1;
        }

        wifi_lobby_map_02262E88(param3, 22);
        return 1;
    } else {
        if (param0->timeLimit <= (11 * 30)) {
            wifi_lobby_map_02262E88(param3, 20);
            return 1;
        }
    }

    return 0;
}

static void wifi_lobby_map_02266C68(WiFiLobbyMapRecruitDisplay *param0, WiFiLobbyMapApp *param1, u32 param2, u32 param3, s32 param4)
{
    static const u8 v0[2] = {
        8,
        10,
    };

    GF_ASSERT(param3 < 2);

    memset(param0, 0, sizeof(WiFiLobbyMapRecruitDisplay));

    param0->showTimer = param3;
    param0->activity = param2;

    wifi_lobby_map_02266CCC(param0, param4);
    wifi_lobby_map_0225E104(param1, 18, 3, 13, v0[param3]);
}

static void wifi_lobby_map_02266CB0(WiFiLobbyMapRecruitDisplay *param0, WiFiLobbyMapApp *param1)
{
    memset(param0, 0, sizeof(WiFiLobbyMapRecruitDisplay));
    wifi_lobby_map_0225E12C(param1);
}

static void wifi_lobby_map_02266CCC(WiFiLobbyMapRecruitDisplay *param0, s32 param1)
{
    s16 v0 = param1 / 30;

    if (v0 != param0->timeSeconds) {
        param0->timeSeconds = v0;
        param0->redrawFlags |= 8;
    }
}

static void wifi_lobby_map_02266CF0(WiFiLobbyMapRecruitDisplay *param0, WiFiLobbyMapApp *param1, BOOL param2)
{
    wifi_lobby_map_02266D08(param0, param1, param2, 0);
}

static void wifi_lobby_map_02266CFC(WiFiLobbyMapRecruitDisplay *param0, WiFiLobbyMapApp *param1, BOOL param2)
{
    wifi_lobby_map_02266D08(param0, param1, param2, 1);
}

static void wifi_lobby_map_02266D08(WiFiLobbyMapRecruitDisplay *param0, WiFiLobbyMapApp *param1, BOOL param2, BOOL param3)
{
    String *v0;
    u32 v1;
    BOOL v2;
    BOOL v3;
    u32 v4;

    if (param2) {
        param0->redrawFlags = 0xff;
    }

    switch (param0->activity) {
    case WiFiPlazaLobbyActivity_00:
        v1 = WiFiPlazaLobbyNetworkGameKind_00;
        break;
    case WiFiPlazaLobbyActivity_01:
        v1 = WiFiPlazaLobbyNetworkGameKind_01;
        break;
    case WiFiPlazaLobbyActivity_02:
        v1 = WiFiPlazaLobbyNetworkGameKind_02;
        break;
    default:
        GF_ASSERT(FALSE);
        v1 = WiFiPlazaLobbyNetworkGameKind_02;
        break;
    }

    {
        v2 = WiFiPlazaLobby_Network_IsGameRecruiting(v1);

        if (param0->isRecruiting != v2) {
            param0->redrawFlags |= 4;
        }

        param0->isRecruiting = v2;
        v3 = WiFiPlazaLobby_Network_IsRecruitAcceptingPlayers(v1);

        if (param0->isAcceptingPlayers != v3) {
            param0->redrawFlags |= 4;
        }

        param0->isAcceptingPlayers = v3;
    }

    {
        if (v2 == 1) {
            v4 = WiFiPlazaLobby_Network_GetRecruitOpenSlots(v1);
        } else {
            v4 = 4;
        }

        if (param0->openSlots != v4) {
            param0->redrawFlags |= 2;
        }

        param0->openSlots = v4;
    }

    if (param0->redrawFlags & 1) {
        wifi_lobby_map_0225E14C(param1, 0, 0, 13 * 8, 16);
        wifi_lobby_map_0225E27C(param1, param0->activity, 0);
        v0 = wifi_lobby_map_0225E20C(param1, 1, 54);
        wifi_lobby_map_0225E13C(param1, v0, 0, 0);
    }

    if (param0->redrawFlags & 4) {
        wifi_lobby_map_0225E14C(param1, 36, 16, 13 * 8, 16);

        if (param3 == 1) {
            if ((param0->isAcceptingPlayers == 0) && (param0->isRecruiting == 1)) {
                v0 = wifi_lobby_map_0225E20C(param1, 1, 69);
                wifi_lobby_map_0225E13C(param1, v0, 36, 16);
            }
        }
    }

    if (param0->redrawFlags & 2) {
        wifi_lobby_map_0225E14C(param1, 0, 32, 13 * 8, 32);
        wifi_lobby_map_0225E21C(param1, param0->openSlots, 1, 1, 2);
        wifi_lobby_map_0225E21C(param1, 4 - param0->openSlots, 1, 0, 2);

        v0 = wifi_lobby_map_0225E20C(param1, 1, 68);

        wifi_lobby_map_0225E13C(param1, v0, 0, 32);
    }

    if (param0->showTimer == 1) {
        if (param0->redrawFlags & 8) {
            wifi_lobby_map_0225E14C(param1, 0, 64, 13 * 8, 16);
            wifi_lobby_map_0225E21C(param1, param0->timeSeconds, 2, 0, 2);
            v0 = wifi_lobby_map_0225E20C(param1, 0, 15);
            wifi_lobby_map_0225E13C(param1, v0, 0, 64);
        }
    }

    param0->redrawFlags = 0;
}
