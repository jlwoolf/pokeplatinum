#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_STATE_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_STATE_H

#include "struct_decls/struct_0202F41C_decl.h"
#include "struct_decls/struct_02030A80_decl.h"
#include "struct_defs/struct_0208B878.h"
#include "struct_defs/struct_0208BA84.h"
#include "struct_defs/struct_vs_recorder_viewer_pending_selection.h"
#include "struct_defs/struct_vs_recorder_viewer_ring_anim_state.h"
#include "struct_defs/struct_020F3DCC.h"

#include "vs_recorder_viewer/struct_vs_recorder_viewer_022307C0.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02230C28.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223118C.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233750.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233828.h"

#include "bg_window.h"
#include "savedata.h"
#include "sys_task_manager.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int *unk_10;
    VsRecorderViewerMenuContext unk_14;
    VsRecorderViewerListNetworkTask unk_52C;
    VsRecorderViewerMenu unk_534;
    VsRecorderRing *unk_6F0;
    VsRecorderRing *unk_6F4;
    VsRecorderViewerMenuAnimatedSprite unk_6F8[6];
    const VsRecorderMenuEntry *unk_818;
    const VsRecorderMenuEntry *unk_81C[5];
    SaveData *saveData;
    u16 unk_834;
    u16 unk_836;
    VsRecorderViewerPendingSelection unk_838;
    void *unk_860;
    u8 padding_864[4];
    VsRecorderPlaybackRequest *unk_868;
    int unk_86C;
    BOOL unk_870;
    u32 unk_874;
    u8 *unk_878;
    BattleRecordingSummary *unk_87C[4];
    PlayerProfile *unk_88C[4];
    BOOL unk_89C;
    BOOL unk_8A0;
    Window unk_8A4;
    VsRecorderViewerListRecordStore unk_8B4;
    VsRecorderViewerRingAnimState unk_41D8;
    SysTask *unk_41E8;
} VsRecorderViewerState;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_STATE_H
