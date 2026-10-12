#ifndef POKEPLATINUM_WORD_DISPLAY_H
#define POKEPLATINUM_WORD_DISPLAY_H

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/struct_easy_chat_word_list_screen_decl.h"
#include "applications/easy_chat/struct_easy_chat_word_display_decl.h"

#include "easy_chat_word_list.h"
#include "narc.h"

EasyChatWordDisplay *EasyChatWordDisplay_New(EasyChatWordListScreen *param0, const EasyChatApp *param1, const EasyChatWordList *param2);
void EasyChatWordDisplay_Free(EasyChatWordDisplay *param0);
void EasyChatWordDisplay_LoadGraphics(EasyChatWordDisplay *param0, NARC *param1);
void EasyChatWordDisplay_Refresh(EasyChatWordDisplay *param0);
u32 EasyChatWordDisplay_GetWordSlotCount(const EasyChatWordDisplay *param0);
void EasyChatWordDisplay_SetInstructionText(EasyChatWordDisplay *param0, u32 param1);
void EasyChatWordDisplay_SetCursorIdle(EasyChatWordDisplay *param0);
void EasyChatWordDisplay_SetCursorActive(EasyChatWordDisplay *param0);
void EasyChatWordDisplay_SetCursorVisible(EasyChatWordDisplay *param0, BOOL param1);
void EasyChatWordDisplay_HideSelectionArrows(EasyChatWordDisplay *param0);
void EasyChatWordDisplay_ShowSelectionArrows(EasyChatWordDisplay *param0);
void EasyChatWordDisplay_SetCursorPosition(EasyChatWordDisplay *param0, int param1);
void EasyChatWordDisplay_DrawPageIndicator(EasyChatWordDisplay *param0, int param1);
void EasyChatWordDisplay_MovePageIndicatorArrow(EasyChatWordDisplay *param0, int param1);
void EasyChatWordDisplay_ErasePageIndicator(EasyChatWordDisplay *param0);

#endif // POKEPLATINUM_WORD_DISPLAY_H
