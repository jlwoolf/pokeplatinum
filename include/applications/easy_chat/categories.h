#ifndef POKEPLATINUM_APPLICATIONS_EASY_CHAT_CATEGORIES_H
#define POKEPLATINUM_APPLICATIONS_EASY_CHAT_CATEGORIES_H

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/struct_easy_chat_word_list_screen_decl.h"
#include "applications/easy_chat/struct_easy_chat_scroll_animation.h"
#include "applications/easy_chat/struct_easy_chat_blend_animation.h"

#include "easy_chat_word_list.h"
#include "narc.h"
#include "sprite.h"

typedef struct {
    EasyChatWordListScreen *unk_00;
    const EasyChatApp *easyChatApp;
    const EasyChatWordList *unk_08;
    BgConfig *bgConfig;
    u32 unk_10;
    u32 unk_14;
    int dummy;
    EasyChatBlendAnimation unk_1C;
    EasyChatScrollAnimation unk_3C;
    Sprite *cursorSprite;
} EasyChatCategoriesContext;

EasyChatCategoriesContext *EasyChatCategoriesContext_New(EasyChatWordListScreen *param0, const EasyChatApp *easyChatApp, const EasyChatWordList *param2);
void EasyChatCategoriesContext_Free(EasyChatCategoriesContext *ctx);
void EasyChatCategories_DrawInterface(EasyChatCategoriesContext *ctx, NARC *narc);
void EasyChatCategories_SetCursorVisible(EasyChatCategoriesContext *ctx, BOOL param1);
void EasyChatCategories_DrawCursor(EasyChatCategoriesContext *ctx, u32 selectedIndex);
void EasyChatCategories_StartShowAnimation(EasyChatCategoriesContext *ctx);
BOOL EasyChatCategories_UpdateShowAnimation(EasyChatCategoriesContext *ctx);
void EasyChatCategories_StartSlideOutAnimation(EasyChatCategoriesContext *ctx);
BOOL EasyChatCategories_UpdateSlideOutAnimation(EasyChatCategoriesContext *ctx);
void EasyChatCategories_ResetVerticalOffset(EasyChatCategoriesContext *ctx);
void EasyChatCategories_StartBrightnessRestore(EasyChatCategoriesContext *ctx);
BOOL EasyChatCategories_UpdateBrightnessRestore(EasyChatCategoriesContext *ctx);
void EasyChatCategories_StartSlideInAnimation(EasyChatCategoriesContext *ctx);
BOOL EasyChatCategories_UpdateSlideInAnimation(EasyChatCategoriesContext *ctx);
void EasyChatCategories_StartSlideOutAndDim(EasyChatCategoriesContext *ctx);
BOOL EasyChatCategories_UpdateSlideOutAndDim(EasyChatCategoriesContext *ctx);
void EasyChatCategories_SetModeOffset(EasyChatCategoriesContext *ctx);
void EasyChatCategories_StartModeTransition(EasyChatCategoriesContext *ctx);
BOOL EasyChatCategories_UpdateModeTransition(EasyChatCategoriesContext *ctx);

#endif // POKEPLATINUM_APPLICATIONS_EASY_CHAT_CATEGORIES_H
