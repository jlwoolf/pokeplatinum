#ifndef POKEPLATINUM_VS_RECORDER_H
#define POKEPLATINUM_VS_RECORDER_H

#include "struct_defs/struct_0208BA84.h"
#include "struct_defs/struct_vs_recorder_state.h"

#include "overlay_manager.h"

// Vs. Recorder application. Hosts the vs_recorder_viewer overlay for the Vs. Recorder
// and the Global Terminal's online features (Battle Videos, Rankings,
// Dress-Up Data and Box Data), and replays recorded battles on request.
VsRecorderState *VsRecorder_GetState(ApplicationManager *appMan);
void VsRecorder_SetPlaybackRequest(VsRecorderPlaybackRequest *request, BOOL requested, int param2);
const ApplicationManagerTemplate *VsRecorder_GetAppTemplate(int mode);
BOOL VsRecorder_CheckFirstArrivalBattlePark(VsRecorderState *vsRecorder);

#endif // POKEPLATINUM_VS_RECORDER_H
