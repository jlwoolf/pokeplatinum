#ifndef POKEPLATINUM_WORD_COLUMNS_H
#define POKEPLATINUM_WORD_COLUMNS_H

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/struct_easy_chat_word_list_screen_decl.h"
#include "applications/easy_chat/struct_easy_chat_word_columns_decl.h"

#include "easy_chat_word_list.h"
#include "narc.h"

EasyChatWordColumns *EasyChatWordColumns_New(EasyChatWordListScreen *param0, const EasyChatApp *param1, const EasyChatWordList *param2);
void EasyChatWordColumns_Free(EasyChatWordColumns *param0);
void EasyChatWordColumns_LoadGraphics(EasyChatWordColumns *param0, NARC *param1);
void EasyChatWordColumns_SetEdgeAnim(EasyChatWordColumns *param0);
void EasyChatWordColumns_SetDefaultAnim(EasyChatWordColumns *param0);
void EasyChatWordColumns_SetVisible(EasyChatWordColumns *param0, BOOL param1);
BOOL EasyChatWordColumns_IsVisible(EasyChatWordColumns *param0);
void EasyChatWordColumns_SetActiveColumn(EasyChatWordColumns *param0, int param1);
void EasyChatWordColumns_SetRightColumnOffset(EasyChatWordColumns *param0);
void EasyChatWordColumns_SetLeftColumnOffset(EasyChatWordColumns *param0);

#endif // POKEPLATINUM_WORD_COLUMNS_H
