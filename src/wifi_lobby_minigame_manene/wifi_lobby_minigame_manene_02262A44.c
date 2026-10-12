#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02262A44.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262A44.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"

#include "heap.h"

WiFiLobbyMinigameManeneCountdown *WiFiLobbyMinigameManene_CreateCountdown(int param0, WiFiLobbyMinigameManeneResources *param1)
{
    WiFiLobbyMinigameManeneCountdown *v0 = Heap_Alloc(HEAP_ID_106, sizeof(WiFiLobbyMinigameManeneCountdown));

    memset(v0, 0, sizeof(WiFiLobbyMinigameManeneCountdown));

    v0->playerCount = param0;
    v0->remainingFrames = ((30 * 40) - 0);
    v0->resources = param1;

    return v0;
}

void WiFiLobbyMinigameManene_FreeCountdown(WiFiLobbyMinigameManeneCountdown *param0)
{
    Heap_Free(param0);
}

BOOL WiFiLobbyMinigameManene_TickCountdown(WiFiLobbyMinigameManeneCountdown *param0)
{
    if ((--param0->remainingFrames) <= 0) {
        return 0;
    }

    return 1;
}
