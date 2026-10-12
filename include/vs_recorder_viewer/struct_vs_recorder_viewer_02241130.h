#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02241130_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02241130_H

#include "vs_recorder_viewer/funcptr_vs_recorder_viewer_022349A8.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub2.h"

#include "savedata.h"

typedef struct {
    int profileId;
    enum HeapID heapID;
    SaveData *saveData;
    VsRecorderViewerTransferCallbacks callbacks;
    VsRecorderViewerTransferStringFunc stringFunc;
    void *userData;
} VsRecorderViewerTransferInitParams;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02241130_H
