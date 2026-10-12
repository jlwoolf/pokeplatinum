#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_CONST_FUNCPTR_TABLES_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_CONST_FUNCPTR_TABLES_H

#include "struct_defs/struct_vs_recorder_state.h"

extern BOOL (*const sVsRecorderViewerRankingsStateTable[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerRankingStateTable[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerRecord_MainStateTable[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerRecord_ProfileStateTable[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerRecord_RingStateTable[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerEntryHandlers[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerSlideShowStateTable[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerSubMenuStateFuncs[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerBattleVideoStateTable[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerFrontierPrintStateTable[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerProfilePhotoModeTable[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerProfileBrowserModeTable[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerBoxStateTable[])(VsRecorderState *);
extern BOOL (*const sVsRecorderViewerBoxListStateTable[])(VsRecorderState *);

#endif POKEPLATINUM_VS_RECORDER_VIEWER_CONST_FUNCPTR_TABLES_H
