#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022349A8_SUB2_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022349A8_SUB2_H

#include "global_terminal/funcptr_global_terminal_0222B920.h"

typedef struct {
    void *userData;
    GlobalTerminalTransferCallbackFunc profilePhotoCallback;
    GlobalTerminalTransferCallbackFunc profileCallback;
    GlobalTerminalTransferCallbackFunc profileBoxCompleteCallback;
    GlobalTerminalTransferCallbackFunc boxCompleteCallback;
    GlobalTerminalTransferCallbackFunc loadPlayTimeCallback;
    GlobalTerminalTransferCallbackFunc loadPlayTimeProfileCallback;
    GlobalTerminalTransferCallbackFunc setBattleRecordingIdCallback;
    GlobalTerminalTransferCallbackFunc loadRecordListCallback;
    GlobalTerminalTransferCallbackFunc loadRecordAltCallback;
    GlobalTerminalTransferCallbackFunc noopCallback;
} VsRecorderViewerTransferCallbacks;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022349A8_SUB2_H
