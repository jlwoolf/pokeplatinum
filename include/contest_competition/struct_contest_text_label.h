#ifndef POKEPLATINUM_STRUCT_CONTEST_TEXT_LABEL_H
#define POKEPLATINUM_STRUCT_CONTEST_TEXT_LABEL_H

#include "struct_decls/font_oam.h"

#include "char_transfer.h"

typedef struct {
    FontOAM *fontOAM;
    CharTransferAllocation charTransfer;
    u16 width;
} ContestTextLabel;

#endif // POKEPLATINUM_STRUCT_CONTEST_TEXT_LABEL_H
