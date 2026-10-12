#ifndef POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222AFCC_H
#define POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222AFCC_H

typedef struct {
    u8 version;
    u8 language;
    u8 month;
    u8 appearance;
    u16 species;
    u8 isEgg : 1;
    u8 form : 7;
    u8 unused_07;
} GlobalTerminalProfileSummary;

#endif // POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222AFCC_H
