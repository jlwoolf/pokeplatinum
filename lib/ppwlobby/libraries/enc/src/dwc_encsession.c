#include "enc/dwc_encsession.h"

#include "nitro/types.h"
#include <dwc.h>

typedef struct DWCi_EncSessionState {
    u32 unk_00;
    u32 unk_04;
    int unk_08;
    int unk_0C;
    char unk_10[32];
    char unk_30[20];
    u32 unk_44;
    u32 unk_48;
    u32 unk_4C;
    u32 unk_50;
    char *unk_54;
    char *unk_58;
    char *unk_5C;
    char *unk_60;
    int unk_64;
    char *unk_68;
    int unk_6C;
    UnkCallback unk_70;
    char unk_74[41];
} DWCi_EncSessionState;

static const char *sEncServerUrl = NULL;

static DWCi_EncSessionState sEncSessionState = {
    .unk_00 = 2
};

static int sRandState;

static void DWCi_EncSessionTrySetError(void);

static int b64size(u32 param0)
{
    return (!!(param0 % 3) + (param0 / 3)) * 4;
}

static void my_randinit(int param0)
{
    sRandState = param0 | (param0 << 16);
}

static u8 my_rand(void)
{
    sRandState = ((sEncSessionState.unk_44 * sRandState) + sEncSessionState.unk_48) % sEncSessionState.unk_4C;
    return sRandState >> 16;
}

static BOOL DWCi_EncValidateKey(char *param0, char *param1, u32 param2, u32 param3, u32 param4, u32 param5)
{
    int i;

    sEncSessionState.unk_0C = 0;

    if (strlen(param0) >= 32) {
        return FALSE;
    }
    if (strlen(param1) != 20) {
        return FALSE;
    }
    if ((param2 - 5) & 7) {
        return FALSE;
    }
    if (!(param3 & 1)) {
        return FALSE;
    }

    int v0 = 0;
    for (i = 0; i < 32; i++) {
        if (((param4 >> i) & 1) == 1) {
            v0++;
        }
    }

    if (v0 != 1) {
        return FALSE;
    }

    strncpy(sEncSessionState.unk_10, param0, 32);
    memcpy(sEncSessionState.unk_30, param1, 20);

    sEncSessionState.unk_44 = param2;
    sEncSessionState.unk_48 = param3;
    sEncSessionState.unk_4C = param4;
    sEncSessionState.unk_50 = param5;
    sEncSessionState.unk_0C = 1;

    return TRUE;
}

static BOOL DWCi_EncSessionValidateResponse(char *param0, int param1)
{
    char v0[41];
    u8 v1[20];
    const char hexDigits[] = "0123456789abcdef";

    if (param1 <= 40) {
        return FALSE;
    }

    u32 v3 = param1 - 40;
    void *v4 = DWC_Alloc(DWC_ALLOCTYPE_ENC, b64size(v3) + 41);
    if (v4 == NULL) {
        return FALSE;
    }

    memcpy(v4, &sEncSessionState.unk_30, 20);

    B64Encode(param0, v4 + 20, v3, 2);

    memcpy(v4 + 20 + b64size(v3), &sEncSessionState.unk_30, 20);

    MATH_CalcSHA1(v1, v4, b64size(v3) + 40);
    DWC_Free(DWC_ALLOCTYPE_ENC, v4, 0);

    for (int i = 0; i < 20; i++) {
        v0[i * 2] = hexDigits[v1[i] >> 4];
        v0[i * 2 + 1] = hexDigits[v1[i] & 0xF];
    }

    v0[40] = '\0';
    if (strncmp(param0 + (param1 - 40), v0, 40) != 0) {
        return FALSE;
    }

    sEncSessionState.unk_68 = param0;
    sEncSessionState.unk_6C = v3;
    return TRUE;
}

static void DWCi_EncSessionProgressCallback(DWCGHTTPState state, const char *buf, int len, int bytesReceived, int totalSize, void *param)
{
    return;
}

static void DWCi_EncSessionCompleteCallback(const char *buf, int len, DWCGHTTPResult result, void *param)
{
    char v0[32];
    char v1[20];

    sEncSessionState.unk_08 = -1;
    if (sEncSessionState.unk_00 == 1) {
        return;
    }

    if (result == DWC_GHTTP_SUCCESS) {
        switch (sEncSessionState.unk_00) {
        case 5:
            if (len == 32) {
                u8 *v2 = sEncSessionState.unk_58 + 20;
                const char hexDigits[] = "0123456789abcdef";

                memcpy(v1, &sEncSessionState.unk_30, 20);
                memcpy(&v0, buf, 32);
                MATH_CalcSHA1(v2, &v1, 52);

                for (int i = 0; i < 20; i++) {
                    sEncSessionState.unk_58[i * 2] = hexDigits[v2[i] >> 4];
                    sEncSessionState.unk_58[i * 2 + 1] = hexDigits[v2[i] & 0xF];
                }

                sEncSessionState.unk_58[-strlen("&hash=")] = '&';
                strncpy(sEncSessionState.unk_74, sEncSessionState.unk_58, 41);
                sEncSessionState.unk_00 = 6;
            } else {
                DWCi_EncSessionTrySetError();
            }

            DWCi_GsFree(buf);
            break;
        case 7:
            if (strncmp(buf, "error:", strlen("error:")) == 0) {
                DWCi_GsFree(buf);
                DWCi_EncSessionTrySetError();
                break;
            }

            if (sEncSessionState.unk_60 != NULL) {
                DWCi_GsFree(sEncSessionState.unk_60);
                sEncSessionState.unk_60 = NULL;
            }

            if (!DWCi_EncSessionValidateResponse(buf, len)) {
                DWCi_GsFree(buf);
                DWCi_EncSessionTrySetError();
                break;
            }

            if (sEncSessionState.unk_70 != NULL && !sEncSessionState.unk_70(buf, len)) {
                DWCi_GsFree(buf);
                DWCi_EncSessionTrySetError();
                break;
            }

            sEncSessionState.unk_60 = buf;
            sEncSessionState.unk_64 = len;
            sEncSessionState.unk_00 = 8;
            break;
        default:
            break;
        }
    } else {
        DWCi_EncSessionTrySetError();
    }
}

static int DWCi_EncSessionEncrypt(u8 *param0, u8 *param1, int param2, u8 *param3, int param4)
{
    u8 *v0;
    u32 v1;
    s32 i;

    int v2 = param4 + param2;
    v1 = 0;
    v0 = DWC_Alloc(DWC_ALLOCTYPE_ENC, sizeof(u32) + v2);
    if (v0 == NULL) {
        return 2;
    }

    for (i = 0; i < param2; i++) {
        v0[sizeof(u32) + i] = param1[i];
    }

    for (i = 0; i < param4; i++) {
        v0[sizeof(u32) + param2 + i] = param3[i];
    }

    for (i = 0; i < v2; i++) {
        v1 += v0[sizeof(u32) + i];
    }

    my_randinit(v1);
    for (i = 0; i < v2; i++) {
        v0[sizeof(u32) + i] ^= my_rand();
    }

    v1 ^= sEncSessionState.unk_50;
    v0[0] = (v1 >> 24);
    v0[1] = (v1 >> 16);
    v0[2] = (v1 >> 8);
    v0[3] = v1;
    B64Encode(v0, param0, sizeof(u32) + v2, 2);
    DWC_Free(DWC_ALLOCTYPE_ENC, v0, 0);
    param0[b64size(sizeof(u32) + v2)] = 0;
    return 0;
}

void DWCi_EncSessionInitialize(enum DWCi_EncServerKind param0, const char *param1)
{
    char v0[21];
    char v1[9];

    memset(v1, 0, 9);
    sEncSessionState.unk_08 = -1;
    sEncSessionState.unk_54 = NULL;
    sEncSessionState.unk_58 = NULL;
    sEncSessionState.unk_5C = NULL;
    sEncSessionState.unk_60 = NULL;
    sEncSessionState.unk_64 = 0;

    switch (param0) {
    case 0:
        sEncServerUrl = "http://gamestats2.gs.nintendowifi.net/";
        break;
    case 1:
        sEncServerUrl = "http://sdkdev.gamespy.com/games/";
        break;
    case 2:
        sEncServerUrl = "http://ishikawa.servebeer.com/games/";
        break;
    }

    strncpy(v0, param1, 20);
    v0[20] = '\0';
    u32 v2 = strtoul(strncpy(v1, param1 + 20, 8), 0, 16);
    u32 v3 = strtoul(strncpy(v1, param1 + 28, 8), 0, 16);
    u32 v4 = strtoul(strncpy(v1, param1 + 36, 8), 0, 16);
    u32 v5 = strtoul(strncpy(v1, param1 + 44, 8), 0, 16);
    DWCi_EncValidateKey(param1 + 52, v0, v2, v3, v4, v5);
    DWC_InitGHTTP(0);
    sEncSessionState.unk_00 = 3;
    sEncSessionState.unk_04 = 1;
}

static void DWCi_EncSessionTrySetError(void)
{
    if (!DWCi_IsError()) {
        DWCi_SetError(DWC_ERROR_NETWORK, -90040);
    }

    sEncSessionState.unk_00 = 1;
}

int DWCi_EncSessionProcess(void)
{
    switch (sEncSessionState.unk_00) {
    case 0:
        break;
    case 1:
        DWCi_EncSessionTrySetError();
        break;
    case 2:
    case 3:
        break;
    case 4:
        sEncSessionState.unk_08 = DWC_GetGHTTPDataEx(sEncSessionState.unk_54, 0, FALSE, DWCi_EncSessionProgressCallback, DWCi_EncSessionCompleteCallback, NULL);
        if (sEncSessionState.unk_08 >= 0) {
            sEncSessionState.unk_00 = 5;
        } else {
            DWCi_EncSessionTrySetError();
        }
        break;
    case 5:
        if (!DWC_ProcessGHTTP()) {
            DWCi_EncSessionTrySetError();
        }
        break;
    case 6:
        sEncSessionState.unk_08 = DWC_GetGHTTPDataEx(sEncSessionState.unk_54, 0, 0, DWCi_EncSessionProgressCallback, DWCi_EncSessionCompleteCallback, 0);
        if (sEncSessionState.unk_08 >= 0) {
            sEncSessionState.unk_00 = 7;
        } else {
            DWCi_EncSessionTrySetError();
        }
        break;
    case 7:
        if (!DWC_ProcessGHTTP()) {
            DWCi_EncSessionTrySetError();
        }
        break;
    case 8:
    default:
        break;
    }

    return sEncSessionState.unk_00;
}

void DWCi_EncSessionShutdown(void)
{
    if (sEncSessionState.unk_54 != NULL) {
        DWC_Free(DWC_ALLOCTYPE_ENC, sEncSessionState.unk_54, 0);
        sEncSessionState.unk_54 = NULL;
    }

    if (sEncSessionState.unk_60 != NULL) {
        DWCi_GsFree(sEncSessionState.unk_60);
        sEncSessionState.unk_64 = 0;
        sEncSessionState.unk_60 = NULL;
    }

    DWC_ShutdownGHTTP();
    sEncSessionState.unk_00 = 2;
    sEncSessionState.unk_04 = 0;
}

char *DWCi_EncSessionGetResponse(u32 *param0)
{
    *param0 = sEncSessionState.unk_6C;
    return sEncSessionState.unk_68;
}

static int DWCi_EncSessionGetPrivateAsync(char *param0, int param1, void *param2, int param3, UnkCallback param4, BOOL param5)
{
    char v0[16];

    if (sEncSessionState.unk_0C != 1) {
        return 3;
    }

    if (sEncSessionState.unk_54 != NULL) {
        DWC_Free(DWC_ALLOCTYPE_ENC, sEncSessionState.unk_54, 0);
        sEncSessionState.unk_54 = NULL;
    }

    sEncSessionState.unk_54 = DWC_Alloc(
        DWC_ALLOCTYPE_ENC,
        strlen(sEncServerUrl)
            + strlen(sEncSessionState.unk_10)
            + strlen(param0)
            + strlen("?pid=") + snprintf(v0, 16, "%d", param1)
            + strlen("&hash=") + 41
            + strlen("&data=") + b64size(param3 + 12));

    if (sEncSessionState.unk_54 == NULL) {
        return 2;
    }

    sprintf(sEncSessionState.unk_54, "%s%s%s?pid=%d&hash=%s&data=", sEncServerUrl, sEncSessionState.unk_10, param0, param1, "0000000000000000000000000000000000000000", "");
    char *v1 = sEncSessionState.unk_54;
    sEncSessionState.unk_5C = v1 + strlen(v1);

    sEncSessionState.unk_58 = ((sEncSessionState.unk_5C - strlen("&data=")) - 40);

    int v2[2] = { param1, param3 };
    if (DWCi_EncSessionEncrypt(sEncSessionState.unk_5C, (u8 *)v2, 8, param2, param3) == 2) {
        DWC_Free(DWC_ALLOCTYPE_ENC, sEncSessionState.unk_54, 0);
        sEncSessionState.unk_54 = NULL;
        return 2;
    }

    if (param5) {
        memcpy(sEncSessionState.unk_58, sEncSessionState.unk_74, 40);
        sEncSessionState.unk_00 = 6;
    } else {
        sEncSessionState.unk_58[-strlen("&hash=")] = '\0';
        sEncSessionState.unk_00 = 4;
    }

    sEncSessionState.unk_70 = param4;
    return 0;
}

int DWCi_EncSessionGetAsync(const char *param0, int param1, void *param2, u32 param3, UnkCallback param4)
{
    return DWCi_EncSessionGetPrivateAsync(param0, param1, param2, param3, param4, FALSE);
}

int DWCi_EncSessionGetReuseHashAsync(const char *param0, int param1, void *param2, u32 param3, UnkCallback param4)
{
    return DWCi_EncSessionGetPrivateAsync(param0, param1, param2, param3, param4, TRUE);
}
