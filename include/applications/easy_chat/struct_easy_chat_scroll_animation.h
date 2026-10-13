#ifndef POKEPLATINUM_STRUCT_EASY_CHAT_SCROLL_ANIMATION_H
#define POKEPLATINUM_STRUCT_EASY_CHAT_SCROLL_ANIMATION_H

#include "bg_window.h"
#include "sys_task_manager.h"

typedef struct {
    BgConfig *bgConfig;
    u32 bgLayer;
    int direction;
    fx32 currentOffset;
    fx32 targetOffset;
    fx32 offsetStep;
    u16 remainingFrames;
    u16 state;
    SysTask *sysTask;
} EasyChatScrollAnimation;

#endif // POKEPLATINUM_STRUCT_EASY_CHAT_SCROLL_ANIMATION_H
