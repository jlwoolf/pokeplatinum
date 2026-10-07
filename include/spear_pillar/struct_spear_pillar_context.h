#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_CONTEXT_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_CONTEXT_H

#include <nitro/fx/fx.h>
#include <nnsys.h>

#include "spear_pillar/struct_spear_pillar_dialga_palkia_camera_shake.h"
#include "spear_pillar/struct_spear_pillar_blend.h"
#include "spear_pillar/struct_spear_pillar_camera_anim.h"
#include "spear_pillar/struct_spear_pillar_capture_decl.h"

#include "bg_window.h"
#include "camera.h"
#include "g3d_pipeline.h"
#include "message.h"
#include "narc.h"
#include "palette.h"
#include "sprite_system.h"

typedef struct {
    NARC *unk_00;
    SpriteSystem *unk_04;
    SpriteManager *unk_08;
    BgConfig *unk_0C;
    PaletteData *unk_10;
    G3DPipelineBuffers *unk_14;
    Camera *camera;
    NNSFndAllocator unk_1C;
    MessageLoader *unk_2C;
    Window unk_30;
    int unk_40;
    VecFx32 unk_44;
    SpearPillarBlend unk_50;
    SpearPillarCapture *unk_54;
    SpearPillarCameraAnim unk_58;
    SpearPillarDialgaPalkiaCameraShake unk_AC;
    u8 unk_C0;
    u8 unk_C1;
    u8 unk_C2;
} SpearPillarContext;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_CONTEXT_H
