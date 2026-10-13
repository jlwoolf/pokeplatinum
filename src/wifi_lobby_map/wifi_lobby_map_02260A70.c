#include "wifi_lobby_map/wifi_lobby_map_02260A70.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_map/wifi_lobby_map_0225C9B4.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_decl.h"

#include "camera.h"
#include "heap.h"

typedef struct WiFiLobbyMapCamera_t {
    Camera *camera;
    const WiFiLobbyMapActor *targetActor;
    VecFx32 targetPos;
} WiFiLobbyMapCamera;

static const CameraAngle Unk_wifi_lobby_map_0226D904 = {
    0xFFFFFFFFFFFFD602,
    0x0,
    0x0
};

WiFiLobbyMapCamera *wifi_lobby_map_02260A70(u32 heapID)
{
    WiFiLobbyMapCamera *v0;
    VecFx32 v1;

    v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMapCamera));
    memset(v0, 0, sizeof(WiFiLobbyMapCamera));
    v0->camera = Camera_Alloc(heapID);

    Camera_InitWithTarget(&v0->targetPos, 0x29aec1, &Unk_wifi_lobby_map_0226D904, 0x5c1, 0, 1, v0->camera);
    Camera_SetAsActive(v0->camera);
    Camera_SetClipping((FX32_CONST(150)), (FX32_CONST(900)), v0->camera);

    return v0;
}

void wifi_lobby_map_02260AD4(WiFiLobbyMapCamera *param0)
{
    Camera_ClearActive();
    Camera_Delete(param0->camera);
    Heap_Free(param0);
}

void wifi_lobby_map_02260AEC(WiFiLobbyMapCamera *param0)
{
    if (param0->targetActor) {
        wifi_lobby_map_0225D054(param0->targetActor, &param0->targetPos);

        param0->targetPos.x += (FX32_CONST(8));
        param0->targetPos.z += (-FX32_CONST(32));
    }

    Camera_ComputeViewMatrix();
}

void wifi_lobby_map_02260B18(WiFiLobbyMapCamera *param0, fx32 param1, fx32 param2, fx32 param3)
{
    param0->targetPos.x = param1;
    param0->targetPos.y = param2;
    param0->targetPos.z = param3;
}

void wifi_lobby_map_02260B20(WiFiLobbyMapCamera *param0, fx32 param1, fx32 param2, fx32 param3)
{
    param0->targetPos.x = param1 + (FX32_CONST(8));
    param0->targetPos.y = param2;
    param0->targetPos.z = param3 + (-FX32_CONST(32));
}

void wifi_lobby_map_02260B38(WiFiLobbyMapCamera *param0, const WiFiLobbyMapActor *param1)
{
    param0->targetActor = param1;
}

void wifi_lobby_map_02260B3C(WiFiLobbyMapCamera *param0)
{
    param0->targetActor = NULL;
}
