#ifndef GDS_INTERNAL_H
#define GDS_INTERNAL_H
#include <nitro/os/common/mutex.h>
#include <nitro/os/common/thread.h>
#include <nitro/types.h>

#include "gds.h"

typedef struct {
    VsRecorderViewerTransferConnection unk_00;
    int unk_138;
    int unk_13C;
    char unk_140[0x100];
    u16 unk_240;
    int unk_244;
    int unk_248;
    int unk_24C;
    int unk_250;
    int unk_254;
    void *unk_258;
    int unk_25C;
    void *unk_260;
    int unk_264;
    int unk_268;
    int unk_26C;
    int unk_270;
    OSThread unk_274;
    OSMutex unk_334;
} GlobalTerminalGdsSession;

typedef struct {
    u16 unk_00;
    u16 unk_02;
    long unk_04;
    long unk_08;
} GlobalTerminalGdsValueRequest;

typedef struct {
    long unk_00;
    VsRecorderViewerTransferBoxData unk_04;
} GlobalTerminalGdsBoxRequest;

typedef struct {
    u16 unk_00;
    u16 unk_02;
    VsRecorderViewerTransferPlayTime unk_04;
    int unk_14;
    int unk_18;
} GlobalTerminalGdsRecordRequest;

typedef struct {
    u16 unk_00;
    u16 unk_02;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
} GlobalTerminalGdsRecordAltRequest;

typedef struct {
    u64 unk_00;
    u32 unk_08;
} GlobalTerminalGdsIdRequest;

typedef struct {
    u16 unk_00;
    u16 unk_02;
    VsRecorderViewerTransferConnection unk_04;
    void *unk_136;
} GlobalTerminalGdsRequestHeader;

GlobalTerminalGdsSession sGlobalTerminalGdsSession;

void GlobalTerminalGds_Reset(void);
BOOL GlobalTerminalGds_StartSession(char *url, int port, VsRecorderViewerTransferConnection *param2);
void GlobalTerminalGds_ProcessLoop(void);
BOOL GlobalTerminalGds_SubmitRequest(int param0, void *param1, void *param2, int param3);
int GlobalTerminalGds_GetState(void);
void *GlobalTerminalGds_GetResponseBuffer(void);
int GlobalTerminalGds_GetReceivedLength(void);
int GlobalTerminalGds_GetStatus(void);

void *GlobalTerminalGds_Alloc(u32 size);
void GlobalTerminalGds_Free(void *ptr);
void GlobalTerminalGds_Lock(void);
void GlobalTerminalGds_Unlock(void);
int GlobalTerminalGds_InitMutex(void);
int GlobalTerminalGds_InitTiming(void);
int GlobalTerminalGds_InitTick(void);
void GlobalTerminalGds_ShutdownTiming(void);
int GlobalTerminalGds_CreateThread(void);
BOOL GlobalTerminalGds_OpenSocket(void);
void GlobalTerminalGds_CloseSocket(void);
BOOL GlobalTerminalGds_ConnectSocket(void);
BOOL GlobalTerminalGds_SendRequest(void);
BOOL GlobalTerminalGds_ReceiveResponse(void);
void GlobalTerminalGds_Sleep(u32 param0);
BOOL GlobalTerminalGds_FetchToken(void);

void GlobalTerminalGds_Encrypt(u8 *param0, int param1, u8 *param2);
void GlobalTerminalGds_Decrypt(u8 *param0, int param1, u8 *param2);
int GlobalTerminalGds_GetRequestSize(int param0);
int GlobalTerminalGds_GetResponseAllocSize(int param0);

void GlobalTerminalGds_ScrubData(void *param0, char *param1);

#endif // GDS_INTERNAL_H
