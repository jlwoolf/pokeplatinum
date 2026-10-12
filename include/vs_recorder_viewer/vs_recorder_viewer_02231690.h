#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_02231690_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_02231690_H

#include "struct_decls/struct_0202F41C_decl.h"
#include "struct_defs/struct_0208B878.h"
#include "struct_defs/struct_vs_recorder_viewer_state.h"

#include "vs_recorder_viewer/struct_vs_recorder_viewer_022312B0.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022323B8.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233310.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223359C.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233F74.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223CAA4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02248CDC.h"

#include "bg_window.h"
#include "message.h"
#include "narc.h"
#include "sprite_system.h"
#include "string_gf.h"

StringTemplate *VsRecorderViewerList_NewStringTemplate(enum HeapID heapID);
int VsRecorderViewerList_GetThemeColorA(VsRecorderViewerState *param0);
int VsRecorderViewerList_GetThemeColorB(VsRecorderViewerState *param0);
int VsRecorderViewerList_GetThemeGraphicsFileIndex(VsRecorderViewerState *param0, int param1);
void VsRecorderViewerList_LoadThemeGraphics(VsRecorderViewerState *param0, int param1);
void VsRecorderViewerList_BlendPalettes(VsRecorderViewerState *param0);
u16 *VsRecorderViewerList_LoadPokedexAlphabetical(enum HeapID heapID, int unused, int *pokedexLength);
void VsRecorderViewerList_SetRecordTransferDone(VsRecorderViewerState *param0, BOOL param1);
BOOL VsRecorderViewerList_IsRecordTransferDone(VsRecorderViewerState *param0);
void VsRecorderViewerList_OpenSubMessage(VsRecorderViewerState *param0, int param1);
void VsRecorderViewerList_CloseSubMessage(VsRecorderViewerState *param0);
void VsRecorderViewerList_RemoveMessageWindow(VsRecorderViewerState *param0);
void VsRecorderViewerList_OpenMainMessage(VsRecorderViewerState *param0, int param1);
void VsRecorderViewerList_UpdateMessageText(VsRecorderViewerState *param0, int param1);
void VsRecorderViewerList_CloseMainMessage(VsRecorderViewerState *param0);
void VsRecorderViewerList_OpenSubMessageWithBlend(VsRecorderViewerState *param0, int param1);
int VsRecorderViewerList_GetAppearanceFileIndex(int param0, int param1);
void VsRecorderViewerList_InitProfile(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1);
void VsRecorderViewerList_FreeProfile(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1);
void VsRecorderViewerList_SetProfileSpritesVisible(VsRecorderViewerProfilePanel *param0, int param1);
void VsRecorderViewerList_InitWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, const VsRecorderViewerListConfig *param2);
void VsRecorderViewerList_InitRecordWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, MessageLoader *param2, const VsRecorderViewerListConfig *param3);
void VsRecorderViewerList_InitRankingWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, MessageLoader *param2, const VsRecorderViewerListConfig *param3, int param4, int param5, String *param6);
void VsRecorderViewerList_InitTwoColumnWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, const VsRecorderViewerListConfig *param2, String *param3[20][2]);
int VsRecorderViewerList_UpdateTwoColumnWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, String *param2[20][2]);
int VsRecorderViewerList_UpdateRankingWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, int param2, int param3, String *param4);
int VsRecorderViewerList_UpdateRecordWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1);
int VsRecorderViewerList_UpdateSpeciesWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1);
void VsRecorderViewerList_MoveSelection(VsRecorderViewerListWindow *param0, s16 param1);
void VsRecorderViewerList_ScrollList(VsRecorderViewerListWindow *param0, s16 param1);
void VsRecorderViewerList_FreeWindow(VsRecorderViewerListWindow *param0);
void VsRecorderViewerList_ResetWindow(VsRecorderViewerListWindow *param0);
void VsRecorderViewerList_LoadArrowSprites(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, int param2);
void VsRecorderViewerList_SetArrowSpritesPosition(VsRecorderViewerListWindow *param0, s16 param1, s16 param2);
void VsRecorderViewerList_UpdateArrowSprites(VsRecorderViewerListWindow *param0);
void VsRecorderViewerList_UpdateArrowSpritesForScroll(VsRecorderViewerListWindow *param0);
void VsRecorderViewerList_FreeArrowSprites(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1);
void VsRecorderViewerList_InitScrollBar(VsRecorderViewerListScrollBar *param0, VsRecorderViewerState *param1);
void VsRecorderViewerList_InitScrollBarWithAnim(VsRecorderViewerListScrollBar *param0, VsRecorderViewerState *param1, int param2);
void VsRecorderViewerList_ResetScrollBar(VsRecorderViewerListScrollBar *param0);
void VsRecorderViewerList_FreeScrollBar(VsRecorderViewerListScrollBar *param0);
void VsRecorderViewerList_UpdateScrollDirection(VsRecorderViewerListScrollBar *param0, u32 param1);
void VsRecorderViewerList_UpdateScrollBarVisibility(VsRecorderViewerListScrollBar *param0, VsRecorderViewerListWindow *param1);
void VsRecorderViewerList_HandleScrollBarInput(VsRecorderViewerListScrollBar *param0);
void VsRecorderViewerList_IncrementTrainerScore(VsRecorderViewerState *param0, u32 param1);
void VsRecorderViewerList_StoreBattleRecording(VsRecorderViewerState *param0);
void VsRecorderViewerList_StartNetworkTask(VsRecorderViewerState *param0, int param1);
BOOL VsRecorderViewerList_IsNetworkTaskDone(VsRecorderViewerState *param0);
void VsRecorderViewerList_StartDrawTask(VsRecorderViewerState *param0);
BOOL VsRecorderViewerList_CheckRecordData(VsRecorderViewerState *param0, int param1, u8 param2);
void VsRecorderViewerList_SetHasPendingRecording(VsRecorderViewerState *param0, BOOL param1);
void VsRecorderViewerList_LoadRecordList(void *param0, const VsRecorderViewerTransferStatus *param1);
void VsRecorderViewerList_LoadBattleRecordings(VsRecorderViewerState *param0);
void VsRecorderViewerList_FreeBattleRecordings(VsRecorderViewerState *param0);
void VsRecorderViewerList_LoadIconResources(VsRecorderViewerState *param0);
void VsRecorderViewerList_FreeIconResources(VsRecorderViewerState *param0);
NARC *VsRecorderViewerList_OpenIconNarc(int param0);
void VsRecorderViewerList_CloseIconNarc(NARC *param0);
ManagedSprite *VsRecorderViewerList_NewPokemonIconSprite(VsRecorderViewerState *param0, NARC *param1, int param2, int param3, int param4, int param5);
void VsRecorderViewerList_FreePokemonIconSprite(VsRecorderViewerState *param0, int param1, ManagedSprite *param2);
void VsRecorderViewerList_DeletePokemonIconSprite(VsRecorderViewerState *param0, int param1, ManagedSprite *param2);
BOOL VsRecorderViewerList_IsSummaryResultSpecial(BattleRecordingSummary *param0);
int VsRecorderViewerList_GetSummaryResultMessageID(VsRecorderViewerSummaryPanel *param0);
void VsRecorderViewerList_InitSummary(VsRecorderViewerSummaryPanel *param0, VsRecorderViewerState *param1);
void VsRecorderViewerList_FreeSummary(VsRecorderViewerSummaryPanel *param0, VsRecorderViewerState *param1);
void VsRecorderViewerList_SetSummarySpritesVisible(VsRecorderViewerSummaryPanel *param0, int param1);
int VsRecorderViewerList_CalcCenteredTextX(Window *param0, String *param1);
void VsRecorderViewerList_ResetRecordState(VsRecorderViewerState *param0);
BOOL VsRecorderViewerList_ClearExtraSaveKey(VsRecorderViewerState *param0);
void VsRecorderViewerList_SetBgPriorities(void);
void VsRecorderViewerList_SetupRing(VsRecorderViewerState *param0, VsRecorderRing *param1, s16 param2, s16 param3);
int VsRecorderViewerList_CountDigits(u64 param0);
void VsRecorderViewerList_LoadBgTilemap(VsRecorderViewerState *param0, int param1, int param2);
void VsRecorderViewerList_PlayRingAnim(VsRecorderViewerState *param0);
BOOL VsRecorderViewerList_IsDrawSuspended(VsRecorderViewerState *param0);
void VsRecorderViewerList_SetDrawSuspended(VsRecorderViewerState *param0, BOOL param1);
void VsRecorderViewerList_InitSpriteWithFont(VsRecorderViewerState *param0, VsRecorderViewerTextSprite *param1, int param2, int param3, s16 param4, s16 param5, s16 param6, s16 param7, int param8, BOOL param9);
void VsRecorderViewerList_FreeSpriteWithFont(VsRecorderViewerTextSprite *param0);
int VsRecorderViewerList_GetMessageIndex(VsRecorderViewerState *param0, int param1, int param2, int param3);
void VsRecorderViewerList_OpenMessage(VsRecorderViewerState *param0, int param1, int param2, int param3);
void VsRecorderViewerList_UpdateMessage(VsRecorderViewerState *param0);
BOOL VsRecorderViewerList_HasRecordingValue(VsRecorderViewerState *param0, u64 param1);
void VsRecorderViewerList_CheckNameChars(VsRecorderViewerState *param0, String *param1);

#endif // POKEPLATINUM_VS_RECORDER_VIEWER_02231690_H
