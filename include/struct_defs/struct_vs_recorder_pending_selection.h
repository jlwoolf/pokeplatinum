#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_PENDING_SELECTION_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_PENDING_SELECTION_H

typedef struct {
    BOOL hasSelection;
    int selection;
    int selectionData[8];
} VsRecorderPendingSelection;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_PENDING_SELECTION_H
