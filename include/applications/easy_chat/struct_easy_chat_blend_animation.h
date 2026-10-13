#ifndef POKEPLATINUM_STRUCT_EASY_CHAT_BLEND_ANIMATION_H
#define POKEPLATINUM_STRUCT_EASY_CHAT_BLEND_ANIMATION_H

#include "sys_task_manager.h"

typedef struct {
    int plane1;
    int plane2;
    int currentValue;
    int targetValue;
    int step;
    int remainingFrames;
    int state;
    SysTask *sysTask;
} EasyChatBlendAnimation;

#endif // POKEPLATINUM_STRUCT_EASY_CHAT_BLEND_ANIMATION_H
