#ifndef ILOBBY_DWCI_LOBBY_TIMER_H
#define ILOBBY_DWCI_LOBBY_TIMER_H

#include <map>

#include "ilobby/dwci_lobbybase.h"
#include "ilobby/dwci_lobby_util.h"

class DWCi_LobbyTimer : public DWCi_LobbyObject {
public:
    typedef BOOL (*Callback)(void *);

private:
    s64 unk_00;
    s64 unk_08;
    void *unk_10;
    Callback unk_14;

public:
    DWCi_LobbyTimer()
    {
    }

    DWCi_LobbyTimer(s64 param0, s64 param1, Callback param2, void *param3, BOOL param4)
        : unk_00(param0)
        , unk_08(param1)
        , unk_10(param3)
        , unk_14(param2)
    {
        if (param4) {
            unk_00 -= unk_08;
        }
    }

    BOOL Update(s64 param0)
    {
        if (param0 - unk_00 > unk_08) {
            unk_00 = param0;
            if (!unk_14(unk_10)) {
                return FALSE;
            }
        }

        return TRUE;
    }
};

class DWCi_LobbyTimerManager : public DWCi_LobbyObject {
    typedef std::map<u32, DWCi_LobbyTimer, std::less<u32>, PPW_Allocator<std::pair<u32, DWCi_LobbyTimer> > > TimerMap;
    TimerMap unk_00;

public:
    DWCi_LobbyTimerManager()
        : unk_00()
    {
    }

    ~DWCi_LobbyTimerManager()
    {
        Clear();
    }

    void Add(u32 param0, s64 param1, DWCi_LobbyTimer::Callback param2, void *param3, BOOL param4 = FALSE)
    {
        unk_00.insert(std::make_pair(param0, DWCi_LobbyTimer(PPW_GetCurrentTimeSeconds(), param1, param2, param3, param4)));
    }

    void Update()
    {
        s64 v0 = PPW_GetCurrentTimeSeconds();

        for (TimerMap::iterator v1 = unk_00.begin(); v1 != unk_00.end();) {
            if (!v1->second.Update(v0)) {
                unk_00.erase(v1++);
                continue;
            }

            v1++;
        }
    }

    void Remove(u32 param0)
    {
        unk_00.erase(param0);
    }

    void Clear()
    {
        unk_00.clear();
    }
};

#endif // ILOBBY_DWCI_LOBBY_TIMER_H
