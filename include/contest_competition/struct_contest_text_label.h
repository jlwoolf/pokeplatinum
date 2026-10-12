#ifndef POKEPLATINUM_STRUCT_CONTEST_TEXT_LABEL_H
#define POKEPLATINUM_STRUCT_CONTEST_TEXT_LABEL_H

#include "struct_decls/font_oam.h"

#include "char_transfer.h"

typedef struct {
    FontOAM *unk_00;
    CharTransferAllocation unk_04;
    u16 unk_10;
} ContestTextLabel;

#endif // POKEPLATINUM_STRUCT_CONTEST_TEXT_LABEL_H
