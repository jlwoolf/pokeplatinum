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
    NARC *narc;
    SpriteSystem *spriteSystem;
    SpriteManager *spriteManager;
    BgConfig *bgConfig;
    PaletteData *paletteData;
    G3DPipelineBuffers *pipelineBuffers;
    Camera *camera;
    NNSFndAllocator allocator;
    MessageLoader *messageLoader;
    Window window;
    int textPrinter;
    VecFx32 cameraTarget;
    SpearPillarBlend blend;
    SpearPillarCapture *capture;
    SpearPillarCameraAnim cameraAnim;
    SpearPillarDialgaPalkiaCameraShake cameraShake;
    u8 blendPhase;
    u8 blendLevel;
    u8 blendTimer;
} SpearPillarContext;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_CONTEXT_H
