#include "ilobby/dwci_lobbycallback.h"

BOOL DWCi_LobbyCallbackList::Remove(u32 param0)
{
    DWCi_LobbyCallback v0(param0, NULL);
    CallbackSet::iterator v1 = unk_00.find(&v0);
    if (v1 == unk_00.end()) {
        return FALSE;
    }

    delete *v1;
    unk_00.erase(v1);
    return TRUE;
}

void DWCi_LobbyCallbackList::Clear()
{
    for (CallbackSet::iterator v0 = unk_00.begin(); v0 != unk_00.end();) {
        delete *v0;
        unk_00.erase(v0++);
    }
}
