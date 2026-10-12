#ifndef POKEPLATINUM_PAGE_BUTTONS_H
#define POKEPLATINUM_PAGE_BUTTONS_H

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/struct_easy_chat_word_list_screen_decl.h"
#include "applications/easy_chat/struct_easy_chat_page_buttons_decl.h"

#include "easy_chat_word_list.h"
#include "narc.h"

EasyChatPageButtons *EasyChatPageButtons_New(EasyChatWordListScreen *param0, const EasyChatApp *param1, const EasyChatWordList *param2);
void EasyChatPageButtons_Free(EasyChatPageButtons *param0);
void EasyChatPageButtons_LoadGraphics(EasyChatPageButtons *param0, NARC *param1);
void EasyChatPageButtons_StartTransition(EasyChatPageButtons *param0);
BOOL EasyChatPageButtons_IsTransitionDone(EasyChatPageButtons *param0);
void EasyChatPageButtons_SetVisible(EasyChatPageButtons *param0, BOOL param1);
void EasyChatPageButtons_SetPressedState(EasyChatPageButtons *param0, int param1, int param2);

#endif // POKEPLATINUM_PAGE_BUTTONS_H
