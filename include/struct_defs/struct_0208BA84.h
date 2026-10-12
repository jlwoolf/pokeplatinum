#ifndef POKEPLATINUM_STRUCT_0208BA84_H
#define POKEPLATINUM_STRUCT_0208BA84_H

// Communication channel between the Vs. Recorder app and the vs_recorder_viewer
// viewer: the viewer sets `requested` when the player chooses to replay a
// recording, and the app reads it once the viewer exits.
typedef struct {
    BOOL requested;
    int playbackMode;
    u8 padding_08[8];
} VsRecorderPlaybackRequest;

#endif // POKEPLATINUM_STRUCT_0208BA84_H
