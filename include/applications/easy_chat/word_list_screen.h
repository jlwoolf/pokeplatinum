#ifndef POKEPLATINUM_WORD_LIST_SCREEN_H
#define POKEPLATINUM_WORD_LIST_SCREEN_H

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/struct_easy_chat_word_list_screen_decl.h"

#include "bg_window.h"
#include "easy_chat_word_list.h"
#include "sprite.h"
#include "sys_task_manager.h"

enum EasyChatTask {
    EASY_CHAT_SYSTASK_00 = 0,
    EASY_CHAT_SYSTASK_01,
    EASY_CHAT_SYSTASK_02,
    EASY_CHAT_SYSTASK_03,
    EASY_CHAT_SYSTASK_04,
    EASY_CHAT_SYSTASK_05,
    EASY_CHAT_SYSTASK_06,
    EASY_CHAT_SYSTASK_07,
    EASY_CHAT_SYSTASK_08,
    EASY_CHAT_SYSTASK_09,
    EASY_CHAT_SYSTASK_10,
    EASY_CHAT_SYSTASK_11,
    EASY_CHAT_SYSTASK_12,
    EASY_CHAT_SYSTASK_13,
    EASY_CHAT_SYSTASK_14,
    EASY_CHAT_SYSTASK_15,
    EASY_CHAT_SYSTASK_16,
    EASY_CHAT_SYSTASK_17,
    EASY_CHAT_SYSTASK_18,
    EASY_CHAT_SYSTASK_19,
    EASY_CHAT_SYSTASK_20,
    EASY_CHAT_SYSTASK_21,
    EASY_CHAT_SYSTASK_22,
    EASY_CHAT_SYSTASK_23,
    EASY_CHAT_SYSTASK_24,
    EASY_CHAT_SYSTASK_25,
    EASY_CHAT_SYSTASK_26,
    EASY_CHAT_SYSTASK_27,
    EASY_CHAT_SYSTASK_28,
};

EasyChatWordListScreen *EasyChatWordListScreen_New(const EasyChatApp *param0, const EasyChatWordList *param1);
void EasyChatWordListScreen_Free(EasyChatWordListScreen *param0);
SysTask *EasyChatWordListScreen_StartVBlankTask(SysTaskFunc param0, void *param1, int param2);
void EasyChatWordListScreen_StartTask(EasyChatWordListScreen *param0, int param1);
BOOL EasyChatWordListScreen_AreTasksDone(EasyChatWordListScreen *param0);
BOOL EasyChatWordListScreen_IsTaskDone(EasyChatWordListScreen *param0, int param1);
u32 EasyChatWordListScreen_GetWordSlotCount(EasyChatWordListScreen *param0);
BgConfig *EasyChatWordListScreen_GetBgConfig(EasyChatWordListScreen *param0);
SpriteList *EasyChatWordListScreen_GetSpriteList(EasyChatWordListScreen *param0);
void EasyChatWordListScreen_SetupSpriteResources(EasyChatWordListScreen *param0, SpriteResourcesHeader *param1, u32 param2, u32 param3);
Sprite *EasyChatWordListScreen_AddSprite(EasyChatWordListScreen *param0, SpriteResourcesHeader *param1, u32 param2, u32 param3, u32 param4, int param5);

#endif // POKEPLATINUM_WORD_LIST_SCREEN_H
