#ifndef POKEPLATINUM_GLOBAL_TERMINAL_0222B008_H
#define POKEPLATINUM_GLOBAL_TERMINAL_0222B008_H

#include "struct_decls/struct_02030A80_decl.h"
#include "struct_defs/dress_up_photo.h"

#include "global_terminal/struct_global_terminal_0222B138.h"
#include "global_terminal/struct_global_terminal_0222B2D8.h"
#include "global_terminal/struct_global_terminal_0222B920.h"
#include "overlay062/funcptr_ov62_022349A8.h"
#include "overlay062/struct_ov62_022349A8_sub2.h"
#include "overlay062/struct_ov62_022349A8_sub3.h"
#include "overlay062/struct_ov62_0223CAA4.h"
#include "overlay062/struct_ov62_02241130.h"

#include "gds.h"
#include "message.h"
#include "pc_boxes.h"
#include "savedata.h"
#include "string_gf.h"
#include "string_template.h"

typedef struct {
    SaveData *saveData;
    UnkFuncPtr_ov62_022349A8 unk_04;
    void *unk_08;
    UnkStruct_ov62_022349A8_sub1 unk_0C;
    enum HeapID heapID;
    int unk_148;
    int unk_14C;
    UnkStruct_ov62_022349A8_sub2 unk_150;
    UnkStruct_ov62_0223CAA4 unk_17C;
    void *unk_18C;
    UnkStruct_ov62_022349A8_sub3 unk_190;
    void *unk_3B4;
    int unk_3B8;
    int unk_3BC;
    int unk_3C0;
    BOOL unk_3C4;
    BOOL unk_3C8;
    GlobalTerminalTaskState unk_3CC;
    int unk_3D8;
    int unk_3DC;
    int unk_3E0;
    int unk_3E4;
    int unk_3E8;
    int unk_3EC;
    int unk_3F0;
    MessageLoader *unk_3F4;
    StringTemplate *unk_3F8;
    String *unk_3FC;
    GlobalTerminalTransferCallback unk_400;
    u8 unk_40D;
    u8 unk_40E;
} UnkStruct_ov62_022349A8;

int GlobalTerminalTransfer_Init(UnkStruct_ov62_022349A8 *param0, const UnkStruct_ov62_02241130 *param1);
void GlobalTerminalTransfer_Free(UnkStruct_ov62_022349A8 *param0);
int GlobalTerminalTransfer_UploadProfilePhoto(UnkStruct_ov62_022349A8 *param0, PlayerProfile *param1, DressUpPhoto *photo);
int GlobalTerminalTransfer_UploadProfile(UnkStruct_ov62_022349A8 *param0, int param1);
int GlobalTerminalTransfer_UploadProfileBox(UnkStruct_ov62_022349A8 *param0, int param1, PlayerProfile *param2, const PCBoxes *pcBoxes, int param4);
int GlobalTerminalTransfer_UploadBox(UnkStruct_ov62_022349A8 *param0, int param1);
int GlobalTerminalTransfer_UploadPlayTime(UnkStruct_ov62_022349A8 *param0);
int GlobalTerminalTransfer_UploadPlayTimeProfile(UnkStruct_ov62_022349A8 *param0, PlayerProfile *param1, GlobalTerminalPlayTimeEntry param2[]);
int GlobalTerminalTransfer_UploadBattleRecording(UnkStruct_ov62_022349A8 *param0, PlayerProfile *param1);
int GlobalTerminalTransfer_UploadRecord(UnkStruct_ov62_022349A8 *param0, u16 param1, u8 param2, u8 param3, u8 param4);
int GlobalTerminalTransfer_UploadRecordDefault(UnkStruct_ov62_022349A8 *param0);
int GlobalTerminalTransfer_UploadEmptyRecord(UnkStruct_ov62_022349A8 *param0);
int GlobalTerminalTransfer_UploadRecordAlt(UnkStruct_ov62_022349A8 *param0);
int GlobalTerminalTransfer_UploadRecordAlt2(UnkStruct_ov62_022349A8 *param0);
int GlobalTerminalTransfer_UploadId(UnkStruct_ov62_022349A8 *param0, u64 param1);
int GlobalTerminalTransfer_UploadId2(UnkStruct_ov62_022349A8 *param0, u64 param1);
int GlobalTerminalTransfer_Main(UnkStruct_ov62_022349A8 *param0);
BOOL GlobalTerminalTransfer_GetState(UnkStruct_ov62_022349A8 *param0, UnkStruct_ov62_0223CAA4 **param1);
BOOL GlobalTerminalTransfer_IsIdle(UnkStruct_ov62_022349A8 *param0);

#endif // POKEPLATINUM_GLOBAL_TERMINAL_0222B008_H
