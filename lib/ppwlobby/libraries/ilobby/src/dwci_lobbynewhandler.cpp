#include "ilobby/dwci_lobbynewhandler.h"

#include <lobby/dwci_lobby.h>

#include "ilobby/dwci_lobbydata.h"

static DWCi_LobbyManager *sNewHandlerLobby = NULL;
static void *sNewHandlerBuffer = NULL;

static void OnAllocFailureDisconnect()
{
    chatDisconnect(sNewHandlerLobby->GetChatSession());
    DWCi_LobbyObject::ExchangeAllocFailureCallback(0);
}

static void OnAllocFailure()
{
    if (sNewHandlerBuffer) {
        DWC_Free(DWC_ALLOCTYPE_AUTH, sNewHandlerBuffer, 0);
        sNewHandlerBuffer = NULL;
    }
    sNewHandlerLobby->SetError(DWCi_LOBBY_ERROR_ALLOC);
    DWCi_LobbyObject::ExchangeAllocFailureCallback(OnAllocFailureDisconnect);
}

BOOL DWCi_LobbySetupNewHandler(DWCi_LobbyManager *param0)
{
    sNewHandlerLobby = param0;
    if (sNewHandlerBuffer) {
        DWC_Free(DWC_ALLOCTYPE_AUTH, sNewHandlerBuffer, 0);
        sNewHandlerBuffer = NULL;
    }

    sNewHandlerBuffer = DWC_Alloc(DWC_ALLOCTYPE_AUTH, 1024);
    if (!sNewHandlerBuffer) {
        return FALSE;
    }

    DWCi_LobbyObject::ExchangeAllocFailureCallback(OnAllocFailure);
    return TRUE;
}

void DWCi_LobbyShutdownNewHandler()
{
    if (sNewHandlerBuffer) {
        DWC_Free(DWC_ALLOCTYPE_AUTH, sNewHandlerBuffer, 0);
        sNewHandlerBuffer = NULL;
    }
}
