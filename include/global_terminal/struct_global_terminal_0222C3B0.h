#ifndef POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222C3B0_H
#define POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222C3B0_H

#include "sys_task_manager.h"

typedef struct {
    SysTask *task;
    BOOL active;
    u16 sourcePalettes[4][16];
    u16 blendTable[21][16];
    s16 blendIndex;
    s8 blendDirection;
    u8 toggle;
} GlobalTerminalPaletteBlend;

#endif // POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222C3B0_H
