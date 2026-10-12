#include <nitro/types.h>

#include "gds.h"
#include "gds_internal.h"

BOOL GlobalTerminalGds_StartConnection(VsRecorderViewerTransferConnection *param0)
{
    return GlobalTerminalGds_StartSession("pkgdsprod.nintendo.co.jp", 12400, param0);
}

void GlobalTerminalGds_EndConnection(void)
{
    GlobalTerminalGds_Reset();
}

int GlobalTerminalGds_GetConnectionState(void)
{
    GlobalTerminalGds_Lock();
    int v0 = GlobalTerminalGds_GetState();
    GlobalTerminalGds_Unlock();
    return v0;
}

int GlobalTerminalGds_GetErrorCode(void)
{
    return GlobalTerminalGds_GetStatus();
}

BOOL GlobalTerminalGds_UploadProfilePhoto(VsRecorderViewerTransferProfileData *param0, void *param1)
{
    VsRecorderViewerTransferProfileData v0 = *param0;
    GlobalTerminalGds_ScrubData(param0, "--");
    GlobalTerminalGds_SubmitRequest(20000, &v0, param1, -1);
}

BOOL GlobalTerminalGds_UploadProfile(long param0, void *param1)
{
    GlobalTerminalGdsValueRequest v0;
    v0.unk_00 = 0;
    v0.unk_02 = 0;
    v0.unk_04 = param0;
    v0.unk_08 = param0 >> 31;

    return GlobalTerminalGds_SubmitRequest(20001, &v0, param1, -1);
}

BOOL GlobalTerminalGds_UploadProfileBox(long param0, VsRecorderViewerTransferBoxData *param1, void *param2)
{
    GlobalTerminalGdsBoxRequest v0;
    v0.unk_00 = param0;
    v0.unk_04 = *param1;

    GlobalTerminalGds_ScrubData(param1, "--");
    return GlobalTerminalGds_SubmitRequest(21000, &v0, param2, -1);
}

BOOL GlobalTerminalGds_UploadBox(long param0, void *param1)
{
    GlobalTerminalGdsValueRequest v0;
    v0.unk_00 = 0;
    v0.unk_02 = 0;
    v0.unk_04 = param0;
    v0.unk_08 = param0 >> 31;

    return GlobalTerminalGds_SubmitRequest(21001, &v0, param1, -1);
}

long GlobalTerminalGds_GetResponseLength(void)
{
    return GlobalTerminalGds_GetReceivedLength();
}

void *GlobalTerminalGds_GetResponseData(void)
{
    return GlobalTerminalGds_GetResponseBuffer();
}

long GlobalTerminalGds_GetMaxResponseAllocSize(long param0)
{
    return GlobalTerminalGds_GetResponseAllocSize(param0);
}

BOOL GlobalTerminalGds_UploadPlayTime(void *param0)
{
    return GlobalTerminalGds_SubmitRequest(22000, NULL, param0, -1);
}

BOOL GlobalTerminalGds_UploadPlayTimeProfile(VsRecorderViewerRankingsUploadProfile *param0, void *param1)
{
    VsRecorderViewerRankingsUploadProfile v0 = *param0;
    return GlobalTerminalGds_SubmitRequest(22001, &v0, param1, -1);
}

BOOL GlobalTerminalGds_UploadBattleRecording(VsRecorderViewerTransferRecordData *param0, void *param1)
{
    VsRecorderViewerTransferRecordData v0 = *param0;
    return GlobalTerminalGds_SubmitRequest(23000, &v0, param1, -1);
}

BOOL GlobalTerminalGds_UploadRecord(VsRecorderViewerTransferPlayTime *param0, void *param1)
{
    GlobalTerminalGdsRecordRequest v0;
    v0.unk_00 = 0;
    v0.unk_04 = *param0;
    v0.unk_00 = 0; // ?
    v0.unk_02 = 0;

    return GlobalTerminalGds_SubmitRequest(23001, &v0, param1, -1);
}

BOOL GlobalTerminalGds_UploadRecordAlt(VsRecorderViewerTransferValue *param0, void *param1)
{
    GlobalTerminalGdsRecordAltRequest v0 = { 0 };
    v0.unk_00 = 1;
    v0.unk_0C = param0->value;

    return GlobalTerminalGds_SubmitRequest(23001, &v0, param1, -1);
}

BOOL GlobalTerminalGds_UploadRecordAlt2(VsRecorderViewerTransferValue *param0, void *param1)
{
    GlobalTerminalGdsRecordAltRequest v0 = { 0 };
    v0.unk_00 = 2;
    v0.unk_0C = param0->value;

    return GlobalTerminalGds_SubmitRequest(23001, &v0, param1, -1);
}

BOOL GlobalTerminalGds_UploadId(u64 param0, u32 param1, void *param2)
{
    GlobalTerminalGdsIdRequest v0;
    v0.unk_00 = param0;
    v0.unk_08 = param1;

    return GlobalTerminalGds_SubmitRequest(23002, &v0, param2, -1);
}

BOOL GlobalTerminalGds_UploadIdAlt(u64 param0, void *param1)
{
    u64 v0 = param0;
    return GlobalTerminalGds_SubmitRequest(23003, &v0, param1, -1);
}
