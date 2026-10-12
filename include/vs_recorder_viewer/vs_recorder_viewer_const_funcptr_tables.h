#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_CONST_FUNCPTR_TABLES_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_CONST_FUNCPTR_TABLES_H

#include "struct_defs/struct_vs_recorder_viewer_state.h"

extern BOOL (*const sVsRecorderViewerRankingsStateTable[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerRankingStateTable[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerRecord_MainStateTable[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerRecord_ProfileStateTable[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerRecord_RingStateTable[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerEntryHandlers[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerSlideShowStateTable[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerSubMenuStateFuncs[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerBattleVideoStateTable[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerFrontierPrintStateTable[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerProfilePhotoModeTable[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerProfileBrowserModeTable[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerBoxStateTable[])(VsRecorderViewerState *);
extern BOOL (*const sVsRecorderViewerBoxListStateTable[])(VsRecorderViewerState *);

#endif POKEPLATINUM_VS_RECORDER_VIEWER_CONST_FUNCPTR_TABLES_H
