#ifndef POKEPLATINUM_ANIMATIONS_H
#define POKEPLATINUM_ANIMATIONS_H

#include "applications/easy_chat/struct_easy_chat_scroll_animation.h"
#include "applications/easy_chat/struct_easy_chat_blend_animation.h"

#include "bg_window.h"

void EasyChatScrollAnimation_Start(EasyChatScrollAnimation *param0, BgConfig *param1, u32 param2, int param3, int param4, int param5);
BOOL EasyChatScrollAnimation_Update(EasyChatScrollAnimation *param0);
void EasyChatBlendAnimation_Start(EasyChatBlendAnimation *param0, int param1, int param2, int param3, int param4, int param5);
BOOL EasyChatBlendAnimation_Update(EasyChatBlendAnimation *param0);
void EasyChatBlendAnimation_StartBrightness(EasyChatBlendAnimation *param0, int param1, int param2, int param3, int param4);
BOOL EasyChatBlendAnimation_UpdateBrightness(EasyChatBlendAnimation *param0);

#endif // POKEPLATINUM_ANIMATIONS_H
