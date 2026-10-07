#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_02246B00_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_02246B00_H

#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246B00.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246BF4.h"

#include "game_options.h"
#include "touch_screen.h"

VsRecorderViewerIdEntryConfig *VsRecorderViewerIdEntry_NewConfig(enum HeapID heapID, int param1, int param2[], Options *options);
void VsRecorderViewerIdEntry_FreeConfig(VsRecorderViewerIdEntryConfig *param0);
void VsRecorderViewerIdEntry_SetCategory(VsRecorderViewerIdEntryState *param0, int param1);
void VsRecorderViewerIdEntry_InitLayout(VsRecorderViewerIdEntryState *param0);
void VsRecorderViewerIdEntry_SetStep(VsRecorderViewerIdEntryState *param0, int param1);
BOOL VsRecorderViewerIdEntry_Init(VsRecorderViewerIdEntryState *param0);
BOOL VsRecorderViewerIdEntry_Exit(VsRecorderViewerIdEntryState *param0);
BOOL VsRecorderViewerIdEntry_UpdateInput(VsRecorderViewerIdEntryState *param0);
BOOL VsRecorderViewerIdEntry_UpdateAnimation(VsRecorderViewerIdEntryState *param0);
BOOL VsRecorderViewerIdEntry_Run(VsRecorderViewerIdEntryState *param0);
void VsRecorderViewerIdEntry_ConfirmId(VsRecorderViewerIdEntryState *param0);
void VsRecorderViewerIdEntry_Backspace(VsRecorderViewerIdEntryState *param0);
void VsRecorderViewerIdEntry_InitTouchInput(VsRecorderViewerIdEntryState *param0);
void VsRecorderViewerIdEntry_TouchCallback(u32 param0, enum TouchScreenButtonState param1, void *param2);
void VsRecorderViewerIdEntry_ProcessSelection(VsRecorderViewerIdEntryState *param0);
void VsRecorderViewerIdEntry_ClearSelection(VsRecorderViewerIdEntryState *param0);
int VsRecorderViewerIdEntry_GetFirstItemIndexInCategory(VsRecorderViewerIdEntryState *param0, int param1);
int VsRecorderViewerIdEntry_GetLastItemIndexInCategory(VsRecorderViewerIdEntryState *param0, int param1);
void VsRecorderViewerIdEntry_LoadGraphics(VsRecorderViewerIdEntryState *param0);
void VsRecorderViewerIdEntry_FreeGraphics(VsRecorderViewerIdEntryState *param0);
void VsRecorderViewerIdEntry_CreateItemSprites(VsRecorderViewerIdEntryState *param0);
void VsRecorderViewerIdEntry_CreateCursorSprites(VsRecorderViewerIdEntryState *param0);
void VsRecorderViewerIdEntry_SetCursorVisible(VsRecorderViewerIdEntryState *param0, int param1, BOOL param2);
void VsRecorderViewerIdEntry_SetSelectorPosition(VsRecorderViewerIdEntryState *param0, int param1);
void VsRecorderViewerIdEntry_SetTouchCursorPosition(VsRecorderViewerIdEntryState *param0, int param1);
void VsRecorderViewerIdEntry_SetCursorPositionForItem(VsRecorderViewerIdEntryState *param0, int param1, int param2);
void VsRecorderViewerIdEntry_UpdateCursors(VsRecorderViewerIdEntryState *param0);
int VsRecorderViewerIdEntry_GetAnimForValue(int param0, BOOL param1);
void VsRecorderViewerIdEntry_UpdateItemSelection(VsRecorderViewerIdEntryState *param0);
void VsRecorderViewerIdEntry_LayoutItems(VsRecorderViewerIdEntryState *param0, int param1);
void VsRecorderViewerIdEntry_UpdateTouchRects(VsRecorderViewerIdEntryState *param0);

#endif // POKEPLATINUM_VS_RECORDER_VIEWER_02246B00_H
