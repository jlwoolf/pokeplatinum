#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02241130_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02241130_H

#include "vs_recorder_viewer/funcptr_vs_recorder_viewer_022349A8.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub2.h"

#include "savedata.h"

typedef struct {
    int unk_00;
    enum HeapID heapID;
    SaveData *saveData;
    VsRecorderViewerTransferCallbacks unk_0C;
    VsRecorderViewerTransferStringFunc unk_38;
    void *unk_3C;
} VsRecorderViewerTransferInitParams;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02241130_H
