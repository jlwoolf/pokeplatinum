#ifndef POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222B920_H
#define POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222B920_H

#include "global_terminal/funcptr_global_terminal_0222B920.h"
#include "global_terminal/funcptr_global_terminal_0222B920_1.h"

typedef struct {
    GlobalTerminalTransferCallbackFunc onComplete;
    u16 saveStep;
    u16 saveResult;
    u8 unused_08;
    GlobalTerminalTransferCallbackFunc2 process;
} GlobalTerminalTransferCallback;

#endif // POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222B920_H
