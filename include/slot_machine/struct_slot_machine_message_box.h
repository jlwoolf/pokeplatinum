#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_MESSAGE_BOX_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_MESSAGE_BOX_H

#include "bg_window.h"
#include "message.h"
#include "string_template.h"

typedef struct {
    MessageLoader *unk_00;
    StringTemplate *unk_04;
    Window unk_08[1];
    void *unk_18;
} SlotMachineMessageBox;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_MESSAGE_BOX_H
