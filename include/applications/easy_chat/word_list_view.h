#ifndef POKEPLATINUM_WORD_LIST_H
#define POKEPLATINUM_WORD_LIST_H

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/struct_easy_chat_word_list_screen_decl.h"
#include "applications/easy_chat/struct_easy_chat_word_list_view_decl.h"

#include "easy_chat_word_list.h"

EasyChatWordListView *EasyChatWordListView_New(EasyChatWordListScreen *param0, const EasyChatApp *param1, const EasyChatWordList *param2);
void EasyChatWordListView_Free(EasyChatWordListView *param0);
void EasyChatWordListView_LoadGraphics(EasyChatWordListView *param0);
void EasyChatWordListView_FillPage(EasyChatWordListView *param0);
void EasyChatWordListView_Show(EasyChatWordListView *param0);
BOOL EasyChatWordListView_IsShown(EasyChatWordListView *param0);
void EasyChatWordListView_Hide(EasyChatWordListView *param0);
BOOL EasyChatWordListView_IsHidden(EasyChatWordListView *param0);
void EasyChatWordListView_SetArrowsVisible(EasyChatWordListView *param0, BOOL param1);
void EasyChatWordListView_SetCursorPosition(EasyChatWordListView *param0, u32 param1);
void EasyChatWordListView_Scroll(EasyChatWordListView *param0, int param1);
BOOL EasyChatWordListView_IsScrollDone(EasyChatWordListView *param0);

#endif // POKEPLATINUM_WORD_LIST_H
