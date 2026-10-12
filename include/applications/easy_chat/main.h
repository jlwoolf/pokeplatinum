#ifndef POKEPLATINUM_APPLICATIONS_EASY_CHAT_MAIN_H
#define POKEPLATINUM_APPLICATIONS_EASY_CHAT_MAIN_H

#include "applications/easy_chat/defs.h"
#include "applications/easy_chat/struct_easy_chat_word_list_screen_decl.h"

#include "easy_chat_args.h"
#include "easy_chat_sentence.h"
#include "easy_chat_word_list.h"
#include "overlay_manager.h"
#include "string_gf.h"
#include "touch_screen_actions.h"

typedef struct EasyChatApp EasyChatApp;

typedef int (*EasyChatMainFunc)(EasyChatApp *easyChatApp, int *state);
typedef void (*EasyChatTaskFunc)(EasyChatApp *easyChatApp, int *state);

typedef struct {
    u8 unk_00;
    u8 unk_01;
} EasyChatMenuCursor;

typedef struct {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 unk_06;
    u8 unk_07;
    int unk_08;
} EasyChatWordSelectCursor;

typedef struct {
    s16 unk_00;
    s8 unk_02;
    s8 unk_03;
} EasyChatSentenceState;

typedef struct EasyChatApp {
    EasyChatArgs *args;
    u32 type;
    EasyChatSentence sentence;
    u16 words[MAX_EASY_CHAT_WORDS];
    EasyChatWordListScreen *unk_14;
    EasyChatWordList *unk_18;
    int state;
    EasyChatMainFunc mainFunc;
    EasyChatMainFunc nextMainFunc;
    int taskFuncState;
    EasyChatTaskFunc taskFunc;
    u16 pressedKeys;
    u16 heldKeysUnused;
    u16 pressedKeysRepeatable;
    int touchedButtonIndex;
    int unk_3C;
    TouchScreenActions *buttonAction;
    BOOL unk_44;
    BOOL unk_48;
    u16 unk_4C;
    u16 currentWordSlot;
    u16 categoryCursorPos;
    u16 prevCategoryCursorPos;
    EasyChatWordSelectCursor unk_54;
    EasyChatSentenceState unk_60;
    u8 unk_64;
    u8 mode;
    EasyChatMenuCursor unk_66;
} EasyChatApp;

BOOL EasyChat_Init(ApplicationManager *appMan, int *state);
BOOL EasyChat_Main(ApplicationManager *appMan, int *state);
BOOL EasyChat_Exit(ApplicationManager *appMan, int *state);
u32 EasyChat_GetType(const EasyChatApp *easyChatApp);
u32 EasyChat_GetInstructionBankEntry(const EasyChatApp *easyChatApp);
u32 EasyChat_GetMode(const EasyChatApp *easyChatApp);
u32 EasyChat_GetSentenceType(const EasyChatApp *easyChatApp);
u16 EasyChat_GetWordAtSlot(const EasyChatApp *easyChatApp, int param1);
String *EasyChat_GetTemplateString(const EasyChatApp *easyChatApp, u32 param1);
u32 EasyChat_GetCurrentWordSlot(const EasyChatApp *easyChatApp);
u32 EasyChat_GetWordColumn(const EasyChatApp *easyChatApp);
u32 EasyChat_GetCategoryCursorPos(const EasyChatApp *easyChatApp);
u32 EasyChat_GetCategoryWordCount(const EasyChatApp *easyChatApp);
void EasyChat_GetWordString(const EasyChatApp *easyChatApp, u32 param1, String *param2);
u32 EasyChat_GetWordSelectCursorIndex(const EasyChatApp *easyChatApp);
int EasyChat_GetWordSelectScrollDirection(const EasyChatApp *easyChatApp);
BOOL EasyChat_IsWordSelectRowBelowFirst(const EasyChatApp *easyChatApp);
BOOL EasyChat_IsWordSelectRowAboveLast(const EasyChatApp *easyChatApp);
int EasyChat_GetFrame(const EasyChatApp *easyChatApp);
u32 EasyChat_GetMenuCursorIndex(const EasyChatApp *easyChatApp);

#endif // POKEPLATINUM_APPLICATIONS_EASY_CHAT_MAIN_H
