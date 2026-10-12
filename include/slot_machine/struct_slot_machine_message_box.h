#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_MESSAGE_BOX_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_MESSAGE_BOX_H

#include "bg_window.h"
#include "message.h"
#include "string_template.h"

typedef struct {
    MessageLoader *messageLoader;
    StringTemplate *stringTemplate;
    Window window[1];
    void *string;
} SlotMachineMessageBox;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_MESSAGE_BOX_H
