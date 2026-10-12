#include <dwc.h>
#include <gs/nonport.h>
#include <nitro/wm/common/wm.h>
#include <nitroWiFi/soc.h>
#include <string.h>

#include "gds.h"
#include "gds_internal.h"

u8 sGlobalTerminalGdsThreadStack[0x800];

void *GlobalTerminalGds_Alloc(u32 size)
{
    return DWC_Alloc(DWC_ALLOCTYPE_AUTH, size);
}

void GlobalTerminalGds_Free(void *ptr)
{
    if (ptr == NULL) {
        return;
    }

    DWC_Free(DWC_ALLOCTYPE_AUTH, ptr, 0);
}

void GlobalTerminalGds_Lock(void)
{
    OS_LockMutex(&sGlobalTerminalGdsSession.unk_334);
}

void GlobalTerminalGds_Unlock(void)
{
    OS_UnlockMutex(&sGlobalTerminalGdsSession.unk_334);
}

int GlobalTerminalGds_InitMutex(void)
{
    OS_InitMutex(&sGlobalTerminalGdsSession.unk_334);
    return 1;
}

int GlobalTerminalGds_InitTiming(void)
{
    return 1;
}

int GlobalTerminalGds_InitTick(void)
{
    if (!OS_IsTickAvailable()) {
        OS_InitTick();
    }

    sGlobalTerminalGdsSession.unk_270 = 16;
    return 1;
}

void GlobalTerminalGds_ShutdownTiming(void)
{
    return;
}

static void GlobalTerminalGds_ProcessEntry(void *param0)
{
    GlobalTerminalGds_ProcessLoop();
}

int GlobalTerminalGds_CreateThread(void)
{
    OS_CreateThread(&sGlobalTerminalGdsSession.unk_274, GlobalTerminalGds_ProcessEntry, 0, &sGlobalTerminalGdsThreadStack[0x800], 0x800, sGlobalTerminalGdsSession.unk_270);
    OS_WakeupThreadDirect(&sGlobalTerminalGdsSession.unk_274);
    return 1;
}

static BOOL GlobalTerminalGds_IsValidIpAddress(char *param0)
{
    int v0 = 0;
    int v1 = 0;

    while (*param0 != 0) {
        if ('0' <= *param0 && *param0 <= '9') {
            v0++;
            if (v0 >= 4) {
                return FALSE;
            }
        } else if (*param0 == '.') {
            if (v0 == 0) {
                return FALSE;
            }
            v1++;
            v0 = 0;
            if (v1 >= 4) {
                return FALSE;
            }
        } else {
            return FALSE;
        }

        param0++;
    }

    return v1 == 3 && v0 != 0;
}

static BOOL GlobalTerminalGds_ResolveHost(char *param0, char *param1)
{
    int v0 = GlobalTerminalGds_IsValidIpAddress(param0);

    if (!v0) {
        SOCHostEnt *v1 = SOC_GetHostByName(param0);
        if (v1) {
            SOCInAddr v2 = { ((u32 *)v1->addrList[0])[0] };
            char *v3 = SOC_InetNtoA(v2);
            strcpy(param1, v3);
        } else {
            return FALSE;
        }
    } else {
        strcpy(param1, param0);
    }

    return TRUE;
}

BOOL GlobalTerminalGds_OpenSocket(void)
{
    int v0 = SOC_Socket(SOC_PF_INET, SOC_SOCK_STREAM, 0);
    sGlobalTerminalGdsSession.unk_26C = v0;

    if (v0 == -1) {
        sGlobalTerminalGdsSession.unk_250 = 3;
        return FALSE;
    }

    int v1 = SOC_Fcntl(v0, SOC_F_GETFL, 0);
    int v2 = SOC_Fcntl(sGlobalTerminalGdsSession.unk_26C, SOC_F_SETFL, v1 | SOC_O_NONBLOCK);

    if (v2 < 0) {
        sGlobalTerminalGdsSession.unk_250 = 4;
        return FALSE;
    }

    char v3[14];
    BOOL v4 = GlobalTerminalGds_ResolveHost(sGlobalTerminalGdsSession.unk_140, v3);

    if (!v4) {
        sGlobalTerminalGdsSession.unk_250 = 5;
        return FALSE;
    }

    int v5 = inet_addr(v3);
    sGlobalTerminalGdsSession.unk_264 = v5;
    return TRUE;
}

void GlobalTerminalGds_CloseSocket(void)
{
    if (sGlobalTerminalGdsSession.unk_26C == -1) {
        return;
    }

    SOC_Shutdown(sGlobalTerminalGdsSession.unk_26C, 2);
    SOC_Close(sGlobalTerminalGdsSession.unk_26C);
    sGlobalTerminalGdsSession.unk_26C = -1;
}

BOOL GlobalTerminalGds_ConnectSocket(void)
{
    SOCSockAddrIn v0;
    v0.len = sizeof(SOCSockAddrIn);
    v0.family = SOC_PF_INET;
    v0.port = ((sGlobalTerminalGdsSession.unk_240 >> 8) & 0xFF) | ((sGlobalTerminalGdsSession.unk_240 << 8) & 0xFF00);
    v0.addr.addr = sGlobalTerminalGdsSession.unk_264;

    u64 v1 = OS_GetTick() / 0x7FD88;

    while (TRUE) {
        int v2 = SOC_Connect(sGlobalTerminalGdsSession.unk_26C, &v0);

        if (v2 < 0) {
            if (v2 == SOC_EINPROGRESS) {
                if (sGlobalTerminalGdsSession.unk_244 != 0) {
                    int v3 = OS_GetTick() / 0x7FD88 - v1;

                    if (v3 >= sGlobalTerminalGdsSession.unk_244) {
                        sGlobalTerminalGdsSession.unk_250 = 10;
                        return FALSE;
                    }
                }
            } else if (v2 != SOC_EISCONN) {
                sGlobalTerminalGdsSession.unk_250 = 7;
                return FALSE;
            } else {
                break;
            }

            GlobalTerminalGds_Lock();

            if (sGlobalTerminalGdsSession.unk_268 == 1) {
                sGlobalTerminalGdsSession.unk_250 = 13;
                GlobalTerminalGds_Unlock();
                return FALSE;
            }
        } else {
            break;
        }

        GlobalTerminalGds_Unlock();
        GlobalTerminalGds_Sleep(1);
    }

    return 1;
}

BOOL GlobalTerminalGds_SendRequest(void)
{
    int v0 = 0;
    u64 v1 = OS_GetTick() / 0x7FD88;

    while (TRUE) {
        int v2 = sGlobalTerminalGdsSession.unk_254 - v0;
        if (v2 > sGlobalTerminalGdsSession.unk_254) {
            v2 = sGlobalTerminalGdsSession.unk_254;
        }

        int v3 = SOC_Send(sGlobalTerminalGdsSession.unk_26C, sGlobalTerminalGdsSession.unk_258 + v0, v2, 0);
        if (v3 != -6) {
            if (v3 < 0) {
                sGlobalTerminalGdsSession.unk_250 = 11;
                return FALSE;
            }

            v0 += v3;
            if (v0 == sGlobalTerminalGdsSession.unk_254) {
                break;
            }
        }

        if (sGlobalTerminalGdsSession.unk_248 != 0) {
            int v4 = OS_GetTick() / 0x7FD88 - v1;
            if (v4 >= sGlobalTerminalGdsSession.unk_248) {
                sGlobalTerminalGdsSession.unk_250 = 11;
                return FALSE;
            }
        }

        GlobalTerminalGds_Lock();

        if (sGlobalTerminalGdsSession.unk_268 == 1) {
            sGlobalTerminalGdsSession.unk_250 = 13;
            GlobalTerminalGds_Unlock();
            return FALSE;
        }

        GlobalTerminalGds_Unlock();
        GlobalTerminalGds_Sleep(1);
    }

    return TRUE;
}

BOOL GlobalTerminalGds_ReceiveResponse(void)
{
    u64 v1;
    u32 v0 = 0;
    int v6 = -1;

    v1 = OS_GetTick() / 0x7FD88;
    while (TRUE) {
        int v3 = SOC_Recv(sGlobalTerminalGdsSession.unk_26C, sGlobalTerminalGdsSession.unk_260 + v0, sGlobalTerminalGdsSession.unk_25C - v0, 0);
        if (v3 != SOC_EWOULDBLOCK) {
            if (v3 <= 0) {
                sGlobalTerminalGdsSession.unk_250 = 9;
                return FALSE;
            }

            v0 += v3;

            if (v0 >= 4 && v6 == -1) {
                memcpy(&v6, sGlobalTerminalGdsSession.unk_260, sizeof(int));
            }

            if (v0 == v6 && v6 != -1) {
                GlobalTerminalGds_Decrypt(sGlobalTerminalGdsSession.unk_260 + 4, v0 - 4, sGlobalTerminalGdsSession.unk_260 + 4);
                sGlobalTerminalGdsSession.unk_25C = v6 - 4;
                break;
            }
        }

        if (sGlobalTerminalGdsSession.unk_24C != 0) {
            int v4 = OS_GetTick() / 0x7FD88 - v1;
            if (v4 >= sGlobalTerminalGdsSession.unk_24C) {
                sGlobalTerminalGdsSession.unk_250 = 12;
                return FALSE;
            }
        }

        GlobalTerminalGds_Lock();

        if (sGlobalTerminalGdsSession.unk_268 == 1) {
            sGlobalTerminalGdsSession.unk_250 = 13;
            GlobalTerminalGds_Unlock();
            return FALSE;
        }

        GlobalTerminalGds_Unlock();
        GlobalTerminalGds_Sleep(1);
    }

    return TRUE;
}

void GlobalTerminalGds_Sleep(u32 param0)
{
    OS_Sleep(param0);
}

BOOL GlobalTerminalGds_FetchToken(void)
{
    if (sGlobalTerminalGdsSession.unk_138 == 1) {
        return TRUE;
    }

    DWCSvlResult v0;
    if (!DWC_SVLGetTokenAsync("", &v0)) {
        sGlobalTerminalGdsSession.unk_250 = 14;
        return FALSE;
    }

    while (TRUE) {
        DWCSvlState v1 = DWC_SVLProcess();

        if (v1 == DWC_ETYPE_SHUTDOWN_FM) {
            memcpy(&sGlobalTerminalGdsSession.unk_00.unk_06, &v0.svltoken, DWC_SVL_TOKEN_LENGTH + 1);
            sGlobalTerminalGdsSession.unk_138 = 1;
            return TRUE;
        } else if (v1 == DWC_ETYPE_SHUTDOWN_GHTTP) {
            DWCErrorType v3;
            int v2;
            DWC_GetLastErrorEx(&v2, &v3);
            sGlobalTerminalGdsSession.unk_250 = 14;
            return FALSE;
        } else if (v1 == DWC_ETYPE_SHUTDOWN_ND) {
            sGlobalTerminalGdsSession.unk_250 = 14;
            return FALSE;
        } else {
            GlobalTerminalGds_Lock();
            if (sGlobalTerminalGdsSession.unk_268 == 1) {
                sGlobalTerminalGdsSession.unk_250 = 13;
                GlobalTerminalGds_Unlock();
                return FALSE;
            }
        }

        GlobalTerminalGds_Unlock();
        GlobalTerminalGds_Sleep(1);
    }
}
