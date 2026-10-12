#ifndef POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222AE80_H
#define POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222AE80_H

#include "global_terminal/struct_global_terminal_0222AE80_sub1.h"
#include "global_terminal/struct_global_terminal_0222AE80_sub2.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02239DA4_sub1.h"

#include "easy_chat_sentence.h"

typedef struct {
    u32 integrity;
    GlobalTerminalPhotoMon photoMon;
    u32 accessoryFlags;
    EasyChatSentence title;
    GlobalTerminalPhotoAccessory accessories[10];
    u8 backdrop;
    u8 language;
    u8 unused_5A[2];
    VsRecorderViewerBoxChecksum checksum;
} GlobalTerminalDressUpPhoto;

#endif // POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222AE80_H
