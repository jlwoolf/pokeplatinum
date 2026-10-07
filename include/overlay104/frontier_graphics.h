#ifndef POKEPLATINUM_FRONTIER_GRAPHICS_H
#define POKEPLATINUM_FRONTIER_GRAPHICS_H

#include "struct_decls/battle_frontier_decl.h"

#include "wifi_2d_char/struct_wifi_2d_char_0222BCE8_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BE18_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CD2C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CE44.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D160.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D1C0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D77C_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D848_decl.h"
#include "overlay104/frontier_particle_system.h"
#include "overlay104/struct_ov104_0223319C.h"
#include "overlay104/struct_ov104_022331E8.h"
#include "overlay104/struct_ov104_0223C634.h"
#include "overlay104/struct_ov104_0223C688.h"
#include "overlay104/struct_ov104_0223D3B0_1.h"
#include "overlay104/struct_ov104_0223D570.h"

#include "bg_window.h"
#include "g3d_pipeline.h"
#include "palette.h"
#include "sprite.h"
#include "sprite_system.h"
#include "sys_task_manager.h"

typedef struct FrontierGraphics {
    BgConfig *bgConfig;
    PaletteData *plttData;
    BattleFrontier *frontier;
    G3DPipelineBuffers *g3dPipeline;
    FrontierParticleSystem *particleSys;
    WiFi2DCharObjectManager *unk_14;
    WiFi2DCharGrid *unk_18;
    WiFi2DCharViewOffset unk_1C;
    WiFi2DCharRenderer *unk_20;
    WiFi2DCharBackground *unk_24;
    WiFi2DCharBackground *unk_28;
    WiFi2DCharEventQueue *unk_2C;
    WiFi2DCharMoveQueue *unk_30;
    SpriteSystem *spriteSystem;
    SpriteManager *spriteMan;
    UnkStruct_ov104_0223D3B0_1 unk_3C;
    ManagedSprite *unk_80[4];
    void *unk_90;
    SysTask *unk_94;
    SysTask *unk_98;
    SysTask *unk_9C;
    SysTask *dummyExecuteOnVBlank;
    UnkStruct_ov104_0223319C unk_A4;
    UnkStruct_ov104_022331E8 unk_B0;
    u16 unk_BC;
    u16 unk_BE;
    u8 unk_C0;
    u8 sceneID;
    u8 unk_C2;
} FrontierGraphics;

FrontierGraphics *FrontierGraphics_New(BattleFrontier *frontier);
void FrontierGraphics_Free(FrontierGraphics *graphics);

void ov104_0223C634(FrontierGraphics *param0);
void ov104_0223C688(FrontierGraphics *param0);
void ov104_0223D0EC(FrontierGraphics *param0, const FrontierObjectGfx *param1);
void ov104_0223D148(FrontierGraphics *param0, int param1);
WiFi2DCharObject *ov104_0223D180(FrontierGraphics *param0, const FrontierObjectParams *param1, int param2);
void ov104_0223D200(FrontierGraphics *param0, WiFi2DCharObject *param1);
void ov104_0223D258(FrontierGraphics *param0, u16 param1, WiFi2DCharObject **param2, WiFi2DCharRenderObject **param3);
void ov104_0223D29C(FrontierGraphics *param0, u16 param1);
void ov104_0223D2CC(FrontierGraphics *param0, u16 param1);
ManagedSprite *ov104_0223D2FC(FrontierGraphics *param0, u16 param1, u16 param2);
void ov104_0223D348(FrontierGraphics *param0, u16 param1);
ManagedSprite *ov104_0223D370(FrontierGraphics *param0, u16 param1);
void ov104_0223D378(FrontierGraphics *param0, u16 param1, int param2);
u32 ov104_0223D3A4(FrontierGraphics *param0, u16 param1);
void ov104_0223D554(FrontierGraphics *param0, s16 *param1, s16 *param2);
FrontierObject *ov104_0223D5A8(BattleFrontier *param0, int param1);

#endif // POKEPLATINUM_FRONTIER_GRAPHICS_H
