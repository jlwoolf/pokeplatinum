#ifndef ILOBBY_LOBBYCALLBACK_H
#define ILOBBY_LOBBYCALLBACK_H

#include <set>

#include "ilobby/dwci_lobbybase.h"

class DWCi_LobbyCallback : public DWCi_LobbyObject {
protected:
    u32 unk_00;
    void *const unk_04;

    DWCi_LobbyCallback(void *param0)
        : unk_00()
        , unk_04(param0)
    {
        static u32 sNextCallbackId = 0;
        unk_00 = sNextCallbackId++;
    }

public:
    DWCi_LobbyCallback(u32 param0, void *param1)
        : unk_00(param0)
        , unk_04(param1)
    {
    }

    virtual ~DWCi_LobbyCallback()
    {
    }

    bool operator<(const DWCi_LobbyCallback &param0) const
    {
        return unk_00 < param0.unk_00;
    }

    virtual u32 GetId() const
    {
        return unk_00;
    }

    virtual void *GetParam() const
    {
        return unk_04;
    }
};

template <class T>
class DWCi_LobbyTypedCallback : public DWCi_LobbyCallback {
    T unk_00;

public:
    DWCi_LobbyTypedCallback(T param0, void *param1)
        : DWCi_LobbyCallback(param1)
        , unk_00(param0)
    {
    }

    virtual ~DWCi_LobbyTypedCallback()
    {
    }

    T Get() const
    {
        return unk_00;
    }
};

class DWCi_LobbyCallbackList : public DWCi_LobbyObject {
    typedef std::set<DWCi_LobbyCallback *, DWCi_LobbyObject::LessComparator<DWCi_LobbyCallback>, PPW_Allocator<DWCi_LobbyCallback *> > CallbackSet;
    CallbackSet unk_00;

public:
    DWCi_LobbyCallbackList()
        : unk_00()
    {
    }

    ~DWCi_LobbyCallbackList()
    {
        Clear();
    }

    template <class T>
    u32 Add(T param0, void *param1)
    {
        DWCi_LobbyTypedCallback<T> *v0 = new DWCi_LobbyTypedCallback<T>(param0, param1);
        unk_00.insert(v0);

        return v0->GetId();
    }

    BOOL Remove(u32 param0);

    template <class T>
    DWCi_LobbyTypedCallback<T> *Find(u32 param0)
    {
        DWCi_LobbyCallback v0(param0, NULL);
        CallbackSet::iterator v1 = unk_00.find(&v0);

        if (v1 == unk_00.end()) {
            return NULL;
        }

        return (DWCi_LobbyTypedCallback<T> *)*v1;
    }

    void Clear();
};

#endif // ILOBBY_LOBBYCALLBACK_H
