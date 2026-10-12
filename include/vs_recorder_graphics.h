#ifndef POKEPLATINUM_VS_RECORDER_GRAPHICS_H
#define POKEPLATINUM_VS_RECORDER_GRAPHICS_H

#include "struct_decls/struct_020F3DCC_decl.h"
#include "struct_defs/struct_vs_recorder_state.h"

const VsRecorderMenuEntry *VsRecorderGraphics_GetSubmenu(int menuIndex);
const VsRecorderMenuEntry *VsRecorderGraphics_GetMenuForMode(VsRecorderState *state, int mode);
void VsRecorderGraphics_CountEnabledEntries(VsRecorderState *state);

#endif // POKEPLATINUM_VS_RECORDER_GRAPHICS_H
