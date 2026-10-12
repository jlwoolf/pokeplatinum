#ifndef PPWLOBBY_ENCSESSION_H
#define PPWLOBBY_ENCSESSION_H

#include <dwc.h>
#include <enc/dwc_encsession.h>
#include <vector>

#include "ilobby/dwci_lobby_util.h"

typedef void (*PPW_EncCallback)(BOOL, const u8 *, u32, void *);

class PPW_EncSession : public DWCi_LobbyObject {
    static PPW_EncSession *sInstance;
    static PPW_EncSession *sShutdownInstance;

    u32 unk_00;
    enum DWCi_EncServerKind unk_04;
    PPWString unk_08;
    PPWString unk_14;
    s32 unk_20;
    std::vector<u8, PPW_Allocator<u8> > unk_24;
    PPW_EncCallback unk_30;
    void *unk_34;
    BOOL unk_38;

    PPW_EncSession(enum DWCi_EncServerKind param0, const char *param1, const char *param2, s32 param3, const u8 *param4, u32 param5, u32 param6, PPW_EncCallback param7, void *param8, BOOL param9)
        : unk_00(param6)
        , unk_04(param0)
        , unk_08(param1)
        , unk_14(param2)
        , unk_20(param3)
        , unk_24()
        , unk_30(param7)
        , unk_34(param8)
        , unk_38(param9)
    {
        unk_24.assign(param4, param4 + param5);
    }

    virtual ~PPW_EncSession()
    {
    }

    BOOL Start()
    {
        DWCi_EncSessionInitialize(unk_04, unk_08.c_str());

        int v0;
        if (unk_38) {
            v0 = DWCi_EncSessionGetReuseHashAsync(unk_14.c_str(), unk_20, (void *)PPW_GetVectorData(unk_24), unk_24.size(), NULL);
        } else {
            v0 = DWCi_EncSessionGetAsync(unk_14.c_str(), unk_20, (void *)PPW_GetVectorData(unk_24), unk_24.size(), NULL);
        }

        if (v0 != 0) {
            DWCi_EncSessionShutdown();
            return FALSE;
        } else {
            return TRUE;
        }
    }

    BOOL Process()
    {
        u32 v0 = 0;
        int v1 = DWCi_EncSessionProcess();

        switch (v1) {
        case 8: {
            void *v2 = DWCi_EncSessionGetResponse(&v0);
            void *v3 = DWC_Alloc(DWC_ALLOCTYPE_AUTH, v0);

            if (v3) {
                MI_CpuCopy8(v2, v3, v0);
            }

            if (v3) {
                Complete(TRUE, (u8 *)v3, v0, unk_34);
            } else {
                Complete(FALSE, NULL, 0, unk_34);
            }

            if (v3) {
                DWC_Free(DWC_ALLOCTYPE_AUTH, v3, 0);
                v3 = NULL;
            }

            return TRUE;
        }
        case 1:
            DWC_ClearError();

            if (--unk_00 > 0) {
                DWCi_EncSessionShutdown();
                if (Start()) {
                    return FALSE;
                }
            }

            Complete(FALSE, NULL, 0, unk_34);
            return TRUE;
        case 0:
            DWC_ClearError();
            Complete(FALSE, NULL, 0, unk_34);
            return TRUE;
        default:
            return FALSE;
        }
    }

    void Complete(BOOL param0, const u8 *param1, u32 param2, void *param3)
    {
        DWCi_EncSessionShutdown();

        std::swap(sShutdownInstance, sInstance);
        unk_30(param0, param1, param2, param3);
    }

public:
    static BOOL Create(enum DWCi_EncServerKind param0, const char *param1, const char *param2, s32 param3, const u8 *param4, u32 param5, u32 param6, PPW_EncCallback param7, void *param8, BOOL param9 = FALSE)
    {
        if (sInstance) {
            return FALSE;
        }

        sInstance = new PPW_EncSession(param0, param1, param2, param3, param4, param5, param6, param7, param8, param9);

        BOOL v0 = sInstance->Start();
        if (!v0 && sInstance) {
            delete sInstance;
            sInstance = NULL;
        }

        return v0;
    }

    static BOOL ProcessActive()
    {
        if (sInstance) {
            if (sInstance->Process() && sShutdownInstance) {
                delete sShutdownInstance;
                sShutdownInstance = NULL;
            }
            return TRUE;
        } else {
            return FALSE;
        }
    }
};

#endif // PPWLOBBY_ENCSESSION_H
