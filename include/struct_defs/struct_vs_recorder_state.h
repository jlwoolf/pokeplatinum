#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_STATE_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_STATE_H

#include "struct_decls/struct_0202F41C_decl.h"
#include "struct_decls/struct_02030A80_decl.h"
#include "struct_defs/struct_0208B878.h"
#include "struct_defs/struct_0208BA84.h"
#include "struct_defs/struct_vs_recorder_pending_selection.h"
#include "struct_defs/struct_vs_recorder_ring_anim.h"
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
    int mode;
    int state;
    int subState;
    int timer;
    int *animState;
    VsRecorderViewerMenuContext menuContext;
    VsRecorderViewerListNetworkTask networkTask;
    VsRecorderViewerMenu menu;
    VsRecorderRing *ring;
    VsRecorderRing *backgroundRing;
    VsRecorderViewerMenuAnimatedSprite menuSprites[6];
    const VsRecorderMenuEntry *currentMenu;
    const VsRecorderMenuEntry *menuStack[5];
    SaveData *saveData;
    u16 saveStep;
    u16 saveSubStep;
    VsRecorderPendingSelection pendingSelection;
    void *viewerData;
    u8 padding_864[4];
    VsRecorderPlaybackRequest *playbackRequest;
    int selectedDataIndex;
    BOOL flag;
    u32 subMode;
    u8 *recordFlagPtr;
    BattleRecordingSummary *summaries[4];
    PlayerProfile *profiles[4];
    BOOL touchHandled;
    BOOL unknownFlag;
    Window window;
    VsRecorderViewerListRecordStore recordStore;
    VsRecorderRingAnim ringAnim;
    SysTask *task;
} VsRecorderState;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_STATE_H
