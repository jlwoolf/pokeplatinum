#ifndef POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222AFC0_H
#define POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222AFC0_H

#include "vs_recorder_viewer/struct_vs_recorder_viewer_02239DA4_sub1.h"

#include "easy_chat_sentence.h"

typedef struct {
    u16 name[8];
    u32 id;
    u8 gender;
    u8 month;
    u8 appearance;
    u8 country;
    u8 region;
    u8 version;
    u8 language;
    u8 isEgg : 1;
    u8 form : 7;
    u16 species;
    u8 introMessageIsString;
    u8 unused_1F;
    union {
        EasyChatSentence introSentence;
        u16 introMessage[40];
    };
    u8 unused_70[12];
    VsRecorderViewerBoxChecksum checksum;
} GlobalTerminalPlayerProfile;

#endif // POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222AFC0_H
