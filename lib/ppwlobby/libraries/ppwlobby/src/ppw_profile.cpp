#include "ppwlobby/ppw_profile.h"

#include <lobby/dwci_lobby.h>

#include "ilobby/dwci_lobbybase.h"
#include "ilobby/dwci_lobby_util.h"
#include "ppwlobby/ppw_lobby_impl.h"
#include "ppwlobby/ppw_parser.h"

void PPW_PlayerProfile::Update()
{
    switch (unk_24) {
    case 0:
        unk_24 = (unk_2C && unk_30) ? 1 : 0;
        if (unk_24 == 0) {
            break;
        }
    case 1:
        if (unk_00.Get().unk_0C) {
            unk_24 = 2;
        }
        break;
    case 2:
        if (unk_34) {
            unk_24 = 3;
        }
        break;
    case 3:
    default:
        break;
    }
}

BOOL PPW_PlayerManager::AddPlayer(int param0)
{
    std::pair<PlayerSet::iterator, bool> v0;
    PPW_PlayerProfile *v1 = new PPW_PlayerProfile(param0);

    v0 = unk_00.insert(v1);
    if (!v0.second) {
        delete v1;
        return TRUE;
    }

    return TRUE;
}

BOOL PPW_PlayerManager::RemovePlayer(int param0)
{
    for (PlayerSet::iterator v0 = unk_00.begin(); v0 != unk_00.end(); v0++) {
        if ((*v0)->GetPid() == param0) {
            delete *v0;
            unk_00.erase(v0);
            return TRUE;
        }
    }
    return FALSE;
}

PPW_PlayerProfile *PPW_PlayerManager::FindPlayer(int param0)
{
    if (param0 == unk_0C.GetPid()) {
        return &unk_0C;
    }
    PlayerSet::const_iterator v0 = std::find_if(unk_00.begin(), unk_00.end(), PPW_PlayerProfile::PidMatcher(param0));
    return v0 == unk_00.end() ? NULL : *v0;
}

void PPW_PlayerManager::ClearPlayers()
{
    for (PlayerSet::iterator v0 = unk_00.begin(); v0 != unk_00.end();) {
        delete *v0;
        unk_00.erase(v0++);
    }
}

BOOL PPW_PlayerManager::IsFull() const
{
    return unk_00.size() + 1 == PPW_LOBBY_MAX_PLAYER_NUM_MAIN && GetConnectedPids().size() + 1 == PPW_LOBBY_MAX_PLAYER_NUM_MAIN;
}

std::vector<s32, PPW_Allocator<s32> > PPW_PlayerManager::GetConnectedPids() const
{
    std::vector<s32, PPW_Allocator<s32> > v0;
    v0.reserve(unk_00.size());
    for (PlayerSet::const_iterator v1 = unk_00.begin(); v1 != unk_00.end(); v1++) {
        if ((*v1)->IsUpdated()) {
            v0.push_back((*v1)->GetPid());
        }
    }
    return v0;
}

void PPW_PlayerManager::SetMyProfile(s32 param0, const u8 *param1, u32 param2)
{
    unk_0C = PPW_PlayerProfile(param0);
    unk_0C.SetSystemData(PPW_PlayerProfile::SystemData());
    unk_0C.SetUserData(param1, param2, FALSE);
    unk_0C.SetUpdated();
}

BOOL PPW_PlayerManager::AllPlayersComplete() const
{
    PlayerSet::const_iterator v0 = std::find_if(unk_00.begin(), unk_00.end(), std::not1(std::mem_fun(&PPW_PlayerProfile::IsComplete)));
    return v0 == unk_00.end();
}

void PPW_PlayerManager::UpdatePlayers()
{
    for (PlayerSet::iterator v0 = unk_00.begin(); v0 != unk_00.end(); v0++) {
        (*v0)->Update();
        switch ((*v0)->GetState()) {
        case 0:
        case 1:
            break;
        case 2: {
            const PPW_PlayerProfile::SystemData &v1 = (*v0)->TakeSystemData();
            const PPW_PlayerProfile::UserData &v2 = (*v0)->TakeUserData();

            PPW_LobbySystemProfile v3 = v1.ToSystemProfile();

            PPW_LobbyGetImpl()->GetCallbacks().lobbyPlayerConnectedCallback((*v0)->GetPid(), &v3, PPW_GetVectorData(v2.unk_00), v2.unk_00.size());
            (*v0)->SetUpdated();
            break;
        }
        case 3:
        default:
            break;
        }
    }
}
