#include "wifi_lobby_map/wifi_lobby_map_0226C60C.h"

#include <nitro.h>
#include <ppwlobby/ppw_lobby.h>
#include <string.h>

#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C9B4.h"
#include "wifi_lobby_map/wifi_lobby_map_0225D9A4.h"
#include "wifi_lobby_map/wifi_lobby_map_02261E10.h"
#include "wifi_lobby_map/wifi_lobby_map_0226C338.h"
#include "wifi_lobby_map/wifi_lobby_map_0226C8B4.h"
#include "wifi_lobby_map/wifi_lobby_map_0226CE54.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_app_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_object_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_lighting_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_fireworks_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_float_manager_decl.h"

#include "heap.h"

typedef struct WiFiLobbyMapTimeEventManager_t {
    WiFiLobbyMapApp *app;
    WiFiPlazaLobbyState *lobbyState;
    WiFiLobbyMapObjectManager *objectManager;
    WiFiLobbyMapActorManager *actorManager;
    WiFiLobbyMapLighting *lighting;
    WiFiLobbyMapFloatManager *floatManager;
    WiFiLobbyMapFireworks *fireworks;
} WiFiLobbyMapTimeEventManager;

static u32 wifi_lobby_map_0226C81C(PPW_LOBBY_TIME_EVENT param0);
static u32 wifi_lobby_map_0226C848(PPW_LOBBY_TIME_EVENT param0);
static u32 wifi_lobby_map_0226C87C(PPW_LOBBY_TIME_EVENT param0);
static void wifi_lobby_map_0226C8A8(WiFiLobbyMapTimeEventManager *param0);

WiFiLobbyMapTimeEventManager *wifi_lobby_map_0226C60C(u32 heapID, WiFiLobbyMapApp *param1)
{
    WiFiLobbyMapTimeEventManager *v0;
    u32 v1, v2, v3;
    u32 v4, v5, v6, v7, v8, v9;

    v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMapTimeEventManager));
    memset(v0, 0, sizeof(WiFiLobbyMapTimeEventManager));

    v0->app = param1;
    v0->lobbyState = wifi_lobby_map_0225DEE8(param1);
    v0->objectManager = wifi_lobby_map_0225DEF8(param1);
    v0->actorManager = wifi_lobby_map_0225DEF0(param1);

    v1 = wifi_lobby_map_0226C81C(WiFiPlazaLobby_State_GetNeonATimeEvent(v0->lobbyState));
    v2 = wifi_lobby_map_0226C848(WiFiPlazaLobby_State_GetNeonBTimeEvent(v0->lobbyState));
    v3 = wifi_lobby_map_0226C87C(WiFiPlazaLobby_State_GetNeonCTimeEvent(v0->lobbyState));

    v0->lighting = wifi_lobby_map_0226C338(heapID, v1, v2, v3);
    v0->floatManager = wifi_lobby_map_0226CE54(param1, heapID);
    v0->fireworks = wifi_lobby_map_0226C8B4(v0->lobbyState, v0->objectManager, heapID);

    wifi_lobby_map_0225CAEC(v0->actorManager, v1);

    v4 = WiFiPlazaLobby_State_GetFireworksState(v0->lobbyState);
    v5 = WiFiPlazaLobby_State_IsLobbyLocked(v0->lobbyState);
    v6 = WiFiPlazaLobby_State_IsParadeFinished(v0->lobbyState);
    v7 = WiFiPlazaLobby_State_IsNeonTransitionComplete(v0->lobbyState);
    v8 = WiFiPlazaLobby_State_IsLobbyClosed(v0->lobbyState);
    v9 = WiFiPlazaLobby_State_IsMinigameFinished(v0->lobbyState);

    {
        if (v4 == 2) {
            wifi_lobby_map_0226260C(v0->objectManager);
        }
    }

    {
        if (v4 != 1) {
            if ((v4 == 0) && (v7 == 1)) {
                wifi_lobby_map_02262658(v0->objectManager, 3);
            }
        }
    }

    {
        if (v6 == 1) {
            wifi_lobby_map_0226246C(v0->objectManager);
        }
    }

    {
        if (v8 == 1) {
            wifi_lobby_map_0226C8A8(v0);
        }
    }

    return v0;
}

void wifi_lobby_map_0226C6F8(WiFiLobbyMapTimeEventManager *param0)
{
    wifi_lobby_map_0226C914(param0->fireworks);
    wifi_lobby_map_0226CF38(param0->floatManager);
    wifi_lobby_map_0226C39C(param0->lighting);

    Heap_Free(param0);
}

void wifi_lobby_map_0226C718(WiFiLobbyMapTimeEventManager *param0)
{
    if (WiFiPlazaLobby_State_CheckTimeEventFlag(param0->lobbyState, 1)) {
        u32 v0;

        v0 = wifi_lobby_map_0226C81C(WiFiPlazaLobby_State_GetNeonATimeEvent(param0->lobbyState));

        wifi_lobby_map_0226C430(param0->lighting, v0);
        wifi_lobby_map_0225CB08(param0->actorManager, v0);
    }

    if (WiFiPlazaLobby_State_CheckTimeEventFlag(param0->lobbyState, 2)) {
        u32 v1;

        v1 = wifi_lobby_map_0226C848(WiFiPlazaLobby_State_GetNeonBTimeEvent(param0->lobbyState));
        wifi_lobby_map_0226C4A0(param0->lighting, v1);
    }

    if (WiFiPlazaLobby_State_CheckTimeEventFlag(param0->lobbyState, 3)) {
        u32 v2;

        v2 = wifi_lobby_map_0226C87C(WiFiPlazaLobby_State_GetNeonCTimeEvent(param0->lobbyState));
        wifi_lobby_map_0226C4C8(param0->lighting, v2);
    }

    if ((WiFiPlazaLobby_State_IsNeonTransitionComplete(param0->lobbyState) == 1) && (WiFiPlazaLobby_State_GetFireworksState(param0->lobbyState) == 0)) {
        if (wifi_lobby_map_0226271C(param0->objectManager) == 0) {
            wifi_lobby_map_02262658(param0->objectManager, 1);
        }
    }

    if (WiFiPlazaLobby_State_CheckTimeEventFlag(param0->lobbyState, 5)) {
        if (WiFiPlazaLobby_State_GetFireworksState(param0->lobbyState) == 1) {
            wifi_lobby_map_0226260C(param0->objectManager);
            wifi_lobby_map_02262658(param0->objectManager, 2);
        } else {
            (void)0;
        }
    }

    if (WiFiPlazaLobby_State_CheckTimeEventFlag(param0->lobbyState, 6)) {
        if (WiFiPlazaLobby_State_IsParadeFinished(param0->lobbyState) == 1) {
            wifi_lobby_map_0226246C(param0->objectManager);
        }
    }

    if (WiFiPlazaLobby_State_IsLobbyClosed(param0->lobbyState) == 1) {
        wifi_lobby_map_02262478(param0->objectManager);

        wifi_lobby_map_0226C8A8(param0);
    }

    wifi_lobby_map_0226C3A4(param0->lighting);
    wifi_lobby_map_0226CF40(param0->floatManager);
    wifi_lobby_map_0226C924(param0->fireworks);
}

BOOL wifi_lobby_map_0226C810(const WiFiLobbyMapTimeEventManager *param0, u32 param1, int param2)
{
    return wifi_lobby_map_0226CFFC(param0->floatManager, param1, param2);
}

static u32 wifi_lobby_map_0226C81C(PPW_LOBBY_TIME_EVENT param0)
{
    switch (param0) {
    case PPW_LOBBY_TIME_EVENT_NEON_A0:
    case PPW_LOBBY_TIME_EVENT_NEON_A1:
    case PPW_LOBBY_TIME_EVENT_NEON_A2:
    case PPW_LOBBY_TIME_EVENT_NEON_A3:
    case PPW_LOBBY_TIME_EVENT_NEON_A4:
    case PPW_LOBBY_TIME_EVENT_NEON_A5:
        return param0 - PPW_LOBBY_TIME_EVENT_NEON_A0;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

static u32 wifi_lobby_map_0226C848(PPW_LOBBY_TIME_EVENT param0)
{
    switch (param0) {
    case PPW_LOBBY_TIME_EVENT_NEON_B0:
    case PPW_LOBBY_TIME_EVENT_NEON_B1:
    case PPW_LOBBY_TIME_EVENT_NEON_B2:
    case PPW_LOBBY_TIME_EVENT_NEON_B3:
        return param0 - PPW_LOBBY_TIME_EVENT_NEON_B0;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

static u32 wifi_lobby_map_0226C87C(PPW_LOBBY_TIME_EVENT param0)
{
    switch (param0) {
    case PPW_LOBBY_TIME_EVENT_NEON_C0:
    case PPW_LOBBY_TIME_EVENT_NEON_C1:
    case PPW_LOBBY_TIME_EVENT_NEON_C2:
    case PPW_LOBBY_TIME_EVENT_NEON_C3:
        return param0 - PPW_LOBBY_TIME_EVENT_NEON_C0;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

static void wifi_lobby_map_0226C8A8(WiFiLobbyMapTimeEventManager *param0)
{
    NNS_G3dGlbLightColor(2, GX_RGB(0, 0, 0));
}
