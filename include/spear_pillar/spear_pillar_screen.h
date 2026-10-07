#ifndef POKEPLATINUM_SPEAR_PILLAR_SCREEN_H
#define POKEPLATINUM_SPEAR_PILLAR_SCREEN_H

#include <nitro/gx.h>

#include "spear_pillar/struct_spear_pillar_screen_scroll.h"
#include "spear_pillar/struct_spear_pillar_capture_config.h"
#include "spear_pillar/struct_spear_pillar_capture_decl.h"

void SpearPillarScreen_InitScroll(SpearPillarScreenScroll *param0, u32 heapID);
void SpearPillarScreen_FreeScroll(SpearPillarScreenScroll *param0);
void SpearPillarScreen_Scroll(SpearPillarScreenScroll *param0, u8 param1, u8 param2, u16 param3, fx32 param4, s16 param5, u32 param6, u32 param7, u32 param8, int param9);
SpearPillarCapture *SpearPillarScreen_StartCapture(SpearPillarCaptureConfig *param0);
void SpearPillarScreen_StopCapture(SpearPillarCapture **param0, GXDispMode param1, GXBGMode param2, GXBG0As param3);

#endif // POKEPLATINUM_SPEAR_PILLAR_SCREEN_H
