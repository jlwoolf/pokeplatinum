#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_02231690_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_02231690_H

#include "struct_decls/struct_0202F41C_decl.h"
#include "struct_defs/struct_0208B878.h"
#include "struct_defs/struct_0208C06C.h"

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
int VsRecorderViewerList_GetThemeColorA(UnkStruct_0208C06C *param0);
int VsRecorderViewerList_GetThemeColorB(UnkStruct_0208C06C *param0);
int VsRecorderViewerList_GetThemeGraphicsFileIndex(UnkStruct_0208C06C *param0, int param1);
void VsRecorderViewerList_LoadThemeGraphics(UnkStruct_0208C06C *param0, int param1);
void VsRecorderViewerList_BlendPalettes(UnkStruct_0208C06C *param0);
u16 *VsRecorderViewerList_LoadPokedexAlphabetical(enum HeapID heapID, int unused, int *pokedexLength);
void VsRecorderViewerList_SetRecordTransferDone(UnkStruct_0208C06C *param0, BOOL param1);
BOOL VsRecorderViewerList_IsRecordTransferDone(UnkStruct_0208C06C *param0);
void VsRecorderViewerList_OpenSubMessage(UnkStruct_0208C06C *param0, int param1);
void VsRecorderViewerList_CloseSubMessage(UnkStruct_0208C06C *param0);
void VsRecorderViewerList_RemoveMessageWindow(UnkStruct_0208C06C *param0);
void VsRecorderViewerList_OpenMainMessage(UnkStruct_0208C06C *param0, int param1);
void VsRecorderViewerList_UpdateMessageText(UnkStruct_0208C06C *param0, int param1);
void VsRecorderViewerList_CloseMainMessage(UnkStruct_0208C06C *param0);
void VsRecorderViewerList_OpenSubMessageWithBlend(UnkStruct_0208C06C *param0, int param1);
int VsRecorderViewerList_GetAppearanceFileIndex(int param0, int param1);
void VsRecorderViewerList_InitProfile(VsRecorderViewerProfilePanel *param0, UnkStruct_0208C06C *param1);
void VsRecorderViewerList_FreeProfile(VsRecorderViewerProfilePanel *param0, UnkStruct_0208C06C *param1);
void VsRecorderViewerList_SetProfileSpritesVisible(VsRecorderViewerProfilePanel *param0, int param1);
void VsRecorderViewerList_InitWindow(VsRecorderViewerListWindow *param0, UnkStruct_0208C06C *param1, const VsRecorderViewerListConfig *param2);
void VsRecorderViewerList_InitRecordWindow(VsRecorderViewerListWindow *param0, UnkStruct_0208C06C *param1, MessageLoader *param2, const VsRecorderViewerListConfig *param3);
void VsRecorderViewerList_InitRankingWindow(VsRecorderViewerListWindow *param0, UnkStruct_0208C06C *param1, MessageLoader *param2, const VsRecorderViewerListConfig *param3, int param4, int param5, String *param6);
void VsRecorderViewerList_InitTwoColumnWindow(VsRecorderViewerListWindow *param0, UnkStruct_0208C06C *param1, const VsRecorderViewerListConfig *param2, String *param3[20][2]);
int VsRecorderViewerList_UpdateTwoColumnWindow(VsRecorderViewerListWindow *param0, UnkStruct_0208C06C *param1, String *param2[20][2]);
int VsRecorderViewerList_UpdateRankingWindow(VsRecorderViewerListWindow *param0, UnkStruct_0208C06C *param1, int param2, int param3, String *param4);
int VsRecorderViewerList_UpdateRecordWindow(VsRecorderViewerListWindow *param0, UnkStruct_0208C06C *param1);
int VsRecorderViewerList_UpdateSpeciesWindow(VsRecorderViewerListWindow *param0, UnkStruct_0208C06C *param1);
void VsRecorderViewerList_MoveSelection(VsRecorderViewerListWindow *param0, s16 param1);
void VsRecorderViewerList_ScrollList(VsRecorderViewerListWindow *param0, s16 param1);
void VsRecorderViewerList_FreeWindow(VsRecorderViewerListWindow *param0);
void VsRecorderViewerList_ResetWindow(VsRecorderViewerListWindow *param0);
void VsRecorderViewerList_LoadArrowSprites(VsRecorderViewerListWindow *param0, UnkStruct_0208C06C *param1, int param2);
void VsRecorderViewerList_SetArrowSpritesPosition(VsRecorderViewerListWindow *param0, s16 param1, s16 param2);
void VsRecorderViewerList_UpdateArrowSprites(VsRecorderViewerListWindow *param0);
void VsRecorderViewerList_UpdateArrowSpritesForScroll(VsRecorderViewerListWindow *param0);
void VsRecorderViewerList_FreeArrowSprites(VsRecorderViewerListWindow *param0, UnkStruct_0208C06C *param1);
void VsRecorderViewerList_InitScrollBar(VsRecorderViewerListScrollBar *param0, UnkStruct_0208C06C *param1);
void VsRecorderViewerList_InitScrollBarWithAnim(VsRecorderViewerListScrollBar *param0, UnkStruct_0208C06C *param1, int param2);
void VsRecorderViewerList_ResetScrollBar(VsRecorderViewerListScrollBar *param0);
void VsRecorderViewerList_FreeScrollBar(VsRecorderViewerListScrollBar *param0);
void VsRecorderViewerList_UpdateScrollDirection(VsRecorderViewerListScrollBar *param0, u32 param1);
void VsRecorderViewerList_UpdateScrollBarVisibility(VsRecorderViewerListScrollBar *param0, VsRecorderViewerListWindow *param1);
void VsRecorderViewerList_HandleScrollBarInput(VsRecorderViewerListScrollBar *param0);
void VsRecorderViewerList_IncrementTrainerScore(UnkStruct_0208C06C *param0, u32 param1);
void VsRecorderViewerList_StoreBattleRecording(UnkStruct_0208C06C *param0);
void VsRecorderViewerList_StartNetworkTask(UnkStruct_0208C06C *param0, int param1);
BOOL VsRecorderViewerList_IsNetworkTaskDone(UnkStruct_0208C06C *param0);
void VsRecorderViewerList_StartDrawTask(UnkStruct_0208C06C *param0);
BOOL VsRecorderViewerList_CheckRecordData(UnkStruct_0208C06C *param0, int param1, u8 param2);
void VsRecorderViewerList_SetHasPendingRecording(UnkStruct_0208C06C *param0, BOOL param1);
void VsRecorderViewerList_LoadRecordList(void *param0, const VsRecorderViewerTransferStatus *param1);
void VsRecorderViewerList_LoadBattleRecordings(UnkStruct_0208C06C *param0);
void VsRecorderViewerList_FreeBattleRecordings(UnkStruct_0208C06C *param0);
void VsRecorderViewerList_LoadIconResources(UnkStruct_0208C06C *param0);
void VsRecorderViewerList_FreeIconResources(UnkStruct_0208C06C *param0);
NARC *VsRecorderViewerList_OpenIconNarc(int param0);
void VsRecorderViewerList_CloseIconNarc(NARC *param0);
ManagedSprite *VsRecorderViewerList_NewPokemonIconSprite(UnkStruct_0208C06C *param0, NARC *param1, int param2, int param3, int param4, int param5);
void VsRecorderViewerList_FreePokemonIconSprite(UnkStruct_0208C06C *param0, int param1, ManagedSprite *param2);
void VsRecorderViewerList_DeletePokemonIconSprite(UnkStruct_0208C06C *param0, int param1, ManagedSprite *param2);
BOOL VsRecorderViewerList_IsSummaryResultSpecial(BattleRecordingSummary *param0);
int VsRecorderViewerList_GetSummaryResultMessageID(VsRecorderViewerSummaryPanel *param0);
void VsRecorderViewerList_InitSummary(VsRecorderViewerSummaryPanel *param0, UnkStruct_0208C06C *param1);
void VsRecorderViewerList_FreeSummary(VsRecorderViewerSummaryPanel *param0, UnkStruct_0208C06C *param1);
void VsRecorderViewerList_SetSummarySpritesVisible(VsRecorderViewerSummaryPanel *param0, int param1);
int VsRecorderViewerList_CalcCenteredTextX(Window *param0, String *param1);
void VsRecorderViewerList_ResetRecordState(UnkStruct_0208C06C *param0);
BOOL VsRecorderViewerList_ClearExtraSaveKey(UnkStruct_0208C06C *param0);
void VsRecorderViewerList_SetBgPriorities(void);
void VsRecorderViewerList_SetupRing(UnkStruct_0208C06C *param0, VsRecorderRing *param1, s16 param2, s16 param3);
int VsRecorderViewerList_CountDigits(u64 param0);
void VsRecorderViewerList_LoadBgTilemap(UnkStruct_0208C06C *param0, int param1, int param2);
void VsRecorderViewerList_PlayRingAnim(UnkStruct_0208C06C *param0);
BOOL VsRecorderViewerList_IsDrawSuspended(UnkStruct_0208C06C *param0);
void VsRecorderViewerList_SetDrawSuspended(UnkStruct_0208C06C *param0, BOOL param1);
void VsRecorderViewerList_InitSpriteWithFont(UnkStruct_0208C06C *param0, VsRecorderViewerTextSprite *param1, int param2, int param3, s16 param4, s16 param5, s16 param6, s16 param7, int param8, BOOL param9);
void VsRecorderViewerList_FreeSpriteWithFont(VsRecorderViewerTextSprite *param0);
int VsRecorderViewerList_GetMessageIndex(UnkStruct_0208C06C *param0, int param1, int param2, int param3);
void VsRecorderViewerList_OpenMessage(UnkStruct_0208C06C *param0, int param1, int param2, int param3);
void VsRecorderViewerList_UpdateMessage(UnkStruct_0208C06C *param0);
BOOL VsRecorderViewerList_HasRecordingValue(UnkStruct_0208C06C *param0, u64 param1);
void VsRecorderViewerList_CheckNameChars(UnkStruct_0208C06C *param0, String *param1);

#endif // POKEPLATINUM_VS_RECORDER_VIEWER_02231690_H
