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
#include "frontier_facilities/frontier_particle_system.h"
#include "frontier_facilities/struct_frontier_facilities_0223319C.h"
#include "frontier_facilities/struct_frontier_facilities_022331E8.h"
#include "frontier_facilities/struct_frontier_facilities_0223C634.h"
#include "frontier_facilities/struct_frontier_facilities_0223C688.h"
#include "frontier_facilities/struct_frontier_facilities_0223D3B0_1.h"
#include "frontier_facilities/struct_frontier_facilities_0223D570.h"

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
    FrontierFacilitiesSpriteSlots unk_3C;
    ManagedSprite *unk_80[4];
    void *unk_90;
    SysTask *unk_94;
    SysTask *unk_98;
    SysTask *unk_9C;
    SysTask *dummyExecuteOnVBlank;
    FrontierFacilitiesShakeState unk_A4;
    FrontierFacilitiesWindowEffectState unk_B0;
    u16 unk_BC;
    u16 unk_BE;
    u8 unk_C0;
    u8 sceneID;
    u8 unk_C2;
} FrontierGraphics;

FrontierGraphics *FrontierGraphics_New(BattleFrontier *frontier);
void FrontierGraphics_Free(FrontierGraphics *graphics);

void FrontierFacilities_SaveObjectState(FrontierGraphics *param0);
void FrontierFacilities_RestoreObjectState(FrontierGraphics *param0);
void FrontierFacilities_AddObjectGfx(FrontierGraphics *param0, const FrontierObjectGfx *param1);
void FrontierFacilities_RemoveObjectGfx(FrontierGraphics *param0, int param1);
WiFi2DCharObject *FrontierFacilities_AddObject(FrontierGraphics *param0, const FrontierObjectParams *param1, int param2);
void FrontierFacilities_RemoveObject(FrontierGraphics *param0, WiFi2DCharObject *param1);
void FrontierFacilities_GetObjectAndSprite(FrontierGraphics *param0, u16 param1, WiFi2DCharObject **param2, WiFi2DCharRenderObject **param3);
void FrontierFacilities_AddSpriteID(FrontierGraphics *param0, u16 param1);
void FrontierFacilities_RemoveSpriteID(FrontierGraphics *param0, u16 param1);
ManagedSprite *FrontierFacilities_AddManagedSprite(FrontierGraphics *param0, u16 param1, u16 param2);
void FrontierFacilities_RemoveManagedSprite(FrontierGraphics *param0, u16 param1);
ManagedSprite *FrontierFacilities_GetManagedSprite(FrontierGraphics *param0, u16 param1);
void FrontierFacilities_SetSpriteVisible(FrontierGraphics *param0, u16 param1, int param2);
u32 FrontierFacilities_IsSpriteVisible(FrontierGraphics *param0, u16 param1);
void FrontierFacilities_GetViewOffset(FrontierGraphics *param0, s16 *param1, s16 *param2);
FrontierObject *FrontierFacilities_GetObject(BattleFrontier *param0, int param1);

#endif // POKEPLATINUM_FRONTIER_GRAPHICS_H
