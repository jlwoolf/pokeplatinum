#include "field_events/field_events_0223E140.h"

#include <nitro.h>
#include <string.h>

#include "constants/species.h"
#include "constants/versions.h"
#include "generated/movement_actions.h"

#include "struct_decls/map_object.h"

#include "field/field_system.h"
#include "field/field_system_sub2_t.h"
#include "fieldmap/area_light.h"
#include "fieldmap/fieldmap.h"
#include "fieldmap/motion_blur.h"
#include "fieldmap/fieldmap_021D1A94.h"
#include "fieldmap/struct_field_effect_decl.h"
#include "field_events/field_effect_funcptr.h"
#include "field_events/struct_field_effect.h"
#include "field_events/struct_screen_transition_decl.h"

#include "bg_window.h"
#include "camera.h"
#include "easy3d_object.h"
#include "field_system.h"
#include "field_task.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "map_object.h"
#include "math_util.h"
#include "narc.h"
#include "player_avatar.h"
#include "sound_playback.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "map_object_animation.h"

void include_unk_sClimaxAreaLightTemplates();

typedef struct {
    FieldSystem *fieldSystem;
    GXBanks banks;
    MotionBlur *motionBlur;
    int blendCoeffA;
    int blendCoeffB;
    u32 state;
} ClimaxBlur;

typedef struct {
    ScreenTransition *screenTransition;
    int timer;
    u32 lastLoopCount;
    u32 state;
} ScreenTransitionTask;

typedef struct {
    u32 state;
    s32 timer;
    BrightnessFader *brightnessFader;
} ClimaxFade;

typedef struct {
    u32 unk_00;
    s32 unk_04;
    ScreenTransition *unk_08;
    BrightnessFader *unk_0C;
    Camera *camera;
} ClimaxSequence_sub1;

typedef struct {
    u32 state;
    s32 timer;
    int subTimer;
    ClimaxBlur blur;
    ClimaxObject *object;
    ScreenTransition *unk_4C;
    BrightnessFader *unk_50;
    ClimaxFlash *flash;
    ClimaxSequence_sub1 unk_58;
    ClimaxFade fade;
} ClimaxSequence;

typedef struct {
    ClimaxParticles *particles;
} ClimaxObjectEffect;

typedef struct {
    u32 unk_00;
    ClimaxGlow *glow;
    ClimaxParticles *particles;
} ClimaxScene;

typedef struct {
    s32 value;
    s32 start;
    s32 delta;
    s32 duration;
} IntInterpolator;

typedef struct {
    fx32 value;
    fx32 start;
    fx32 delta;
    s32 duration;
} FxInterpolator;

typedef struct {
    u32 state;
    u32 unk_04;
    ClimaxActorManager *manager;
    s16 masterBrightness;
    int variant;
    int animationState;
    int animationStep;
    int facingTimer;
    int timer;
    Easy3DObject object;
    Easy3DModel model;
    Easy3DAnim anim;
    NNSFndAllocator allocator;
    s32 frame;
    fx32 targetX;
    fx32 targetZ;
    fx32 offsetX;
    fx32 offsetZ;
    FxInterpolator interpX;
    FxInterpolator interpZ;
    FieldSystem *fieldSystem;
    MapObject *mapObject1;
    MapObject *mapObject0;
    MapObject *playerMapObject;
    PlayerAvatar *playerAvatar;
} ClimaxActor;

typedef struct ScreenTransition_t {
    Camera *camera1;
    Camera *camera2;
    FxInterpolator interpX;
    FxInterpolator interpY;
    VecFx32 target;
    VecFx32 baseTarget;
    u32 state;
    u32 timer;
    u32 loopCount;
};

typedef struct BrightnessFader_t {
    IntInterpolator interpolator;
    int timer;
    u32 targetValue;
    u32 duration;
    int state;
    SysTask *task;
} BrightnessFader;

typedef struct {
    Easy3DObject object;
    Easy3DModel model;
    Easy3DAnim anims[2];
    BrightnessFader *brightnessFader;
    FxInterpolator interpolator;
    int unk_C4;
    int unk_C8;
    SysTask *task;
    s32 unk_D0;
    u16 unk_D4;
    u16 unk_D6;
    fx32 unk_D8;
} ClimaxActorModel;

typedef struct ClimaxActorManager_t {
    FieldSystem *fieldSystem;
    ClimaxBlur blur;
    ClimaxActorModel actorModel;
    NNSFndAllocator allocator;
    u32 state;
    u32 unk_130;
    fx32 unk_134;
    fx32 unk_138;
    fx32 unk_13C;
} ClimaxActorManager;

typedef struct {
    MapObject *mapObject;
    FxInterpolator unk_04;
    FxInterpolator unk_14;
    int unk_24;
    int unk_28;
} ClimaxObjectAnchor;

typedef struct {
    int blendCoeffA;
    int blendCoeffB;
    Easy3DObject object;
    Easy3DModel model;
    Easy3DAnim anims[2];
    u32 unk_B8;
    FxInterpolator unk_BC;
    int unk_CC;
    int unk_D0;
    int unk_D4;
} ClimaxObjectModel;

typedef struct ClimaxObject_t {
    u32 state;
    FieldSystem *fieldSystem;
    ClimaxObjectAnchor anchor;
    ClimaxObjectModel model;
    NNSFndAllocator allocator;
    enum HeapID heapID;
} ClimaxObject;

typedef struct {
    u32 isActive;
    Easy3DObject object;
    FxInterpolator interpolator;
    int timer;
} ClimaxParticle;

typedef struct ClimaxParticles_t {
    Easy3DModel model;
    ClimaxParticle particles[3];
    u32 isActive;
    s32 spawnTimer;
    s32 spawnInterval;
    fx32 x;
    fx32 y;
    fx32 z;
    u16 rotX;
    u16 rotY;
    u16 rotZ;
} ClimaxParticles;

typedef struct ClimaxGlow_t {
    Easy3DObject object;
    Easy3DModel model;
    Easy3DAnim anims[3];
    NNSFndAllocator allocator;
} ClimaxGlow;

typedef struct ClimaxFlash_t {
    Easy3DObject object;
    Easy3DModel model;
    Easy3DAnim anims[4];
    FieldSystem *fieldSystem;
    NNSFndAllocator allocator;
} ClimaxFlash;

static void ClimaxBlur_Update(ClimaxBlur *param0);
static void ClimaxBlur_BeginFade(ClimaxBlur *param0);
static u32 ClimaxBlur_GetState(const ClimaxBlur *param0);
static void ClimaxBlur_SetBanks(void);
static void ClimaxBlur_InitBackground(BgConfig *param0);
static void ClimaxBlur_RestoreBackground(BgConfig *param0);
static void ClimaxBlur_ResetBackground(BgConfig *param0);
static MotionBlur *ClimaxBlur_CreateMotionBlur(int param0, int param1);
static void ClimaxBlur_BeginDelete(ClimaxBlur *param0);
static void ClimaxBlur_StartInit(ClimaxBlur *param0);
static void ClimaxBlur_StartRestore(ClimaxBlur *param0);
static void ClimaxBlur_DeleteTask(SysTask *param0, void *param1);
static void ClimaxBlur_InitTask(SysTask *param0, void *param1);
static void ClimaxBlur_RestoreTask(SysTask *param0, void *param1);
static BOOL ClimaxFade_Update(ClimaxFade *param0);
static BOOL ClimaxObjectModel_UpdateAnims(ClimaxObject *param0);
static BOOL ClimaxObjectModel_UpdateBlend(ClimaxObject *param0, int param1, int param2);
static void Interpolator_InitInt(IntInterpolator *param0, s32 param1, s32 param2, s32 param3);
static void Interpolator_Init(FxInterpolator *param0, fx32 param1, fx32 param2, s32 param3);
static BOOL Interpolator_Update(FxInterpolator *param0, s32 param1);
static void Climax3D_ModelLoad(Easy3DModel *param0, u32 param1, u32 param2, u32 param3);
static void Climax3D_ModelRelease(Easy3DModel *param0);
static void Climax3D_AnimRelease(Easy3DAnim *param0, NNSFndAllocator *param1);
static BOOL Climax3D_AnimUpdate(Easy3DAnim *param0);
static void Climax3D_AnimUpdateLooped(Easy3DAnim *param0);
static void Climax3D_AnimSetFrame(Easy3DAnim *param0, fx32 param1);
static void Climax3D_ObjectInit(Easy3DObject *param0, Easy3DModel *param1);
static void Climax3D_ObjectAddAnim(Easy3DObject *param0, Easy3DAnim *param1);
static void Climax3D_ObjectDraw(Easy3DObject *param0);
static void Climax3D_ObjectSetVisible(Easy3DObject *param0, BOOL param1);
static void Climax3D_ObjectSetPosition(Easy3DObject *param0, fx32 param1, fx32 param2, fx32 param3);
static void Climax3D_ObjectSetScale(Easy3DObject *param0, fx32 param1, fx32 param2, fx32 param3);
static void Climax3D_ObjectSetRotation(Easy3DObject *param0, u16 param1, u32 param2);
static ScreenTransition *ScreenTransition_New(enum HeapID heapID);
static void ScreenTransition_Reset(ScreenTransition *param0);
static BOOL ScreenTransition_UpdateInterpolators(ScreenTransition *param0);
static void ScreenTransition_ApplyTarget(ScreenTransition *param0, fx32 param1, fx32 param2);
static void BrightnessFader_Task(SysTask *param0, void *param1);
static void ClimaxObjectAnchor_Init(ClimaxObjectAnchor *param0, FieldSystem *fieldSystem, u32 param2);
static void ClimaxObjectModel_Init(ClimaxObjectModel *param0, enum HeapID heapID, NNSFndAllocator *param2);
static void ClimaxObjectModel_Start(ClimaxObjectModel *param0, fx32 param1, fx32 param2, fx32 param3);
static void ClimaxObjectModel_Free(ClimaxObjectModel *param0, NNSFndAllocator *param1);
static void ClimaxObjectModel_Draw(ClimaxObjectModel *param0);
static void ClimaxParticles_Free(ClimaxParticles *param0);
static void ClimaxParticles_Start(ClimaxParticles *param0, fx32 param1, fx32 param2, fx32 param3, s32 param4, u16 param5, u16 param6, u16 param7);
static void ClimaxParticles_Update(ClimaxParticles *param0);
static void ClimaxParticles_Draw(ClimaxParticles *param0);
static void ClimaxParticle_Init(ClimaxParticle *param0, Easy3DModel *param1);
static void ClimaxParticle_Reset(ClimaxParticle *param0);
static void ClimaxParticle_Start(ClimaxParticle *param0, fx32 param1, fx32 param2, int param3, fx32 param4, fx32 param5, fx32 param6, u16 param7, u16 param8, u16 param9);
static void ClimaxParticle_Update(ClimaxParticle *param0);
static void ClimaxParticle_Draw(ClimaxParticle *param0);
static ClimaxParticle *ClimaxParticles_FindFree(ClimaxParticles *param0);
static ClimaxGlow *ClimaxGlow_New(enum HeapID heapID, u32 param1);
static void ClimaxGlow_Free(ClimaxGlow *param0);
static void ClimaxGlow_SetPosition(ClimaxGlow *param0, fx32 param1, fx32 param2, fx32 param3, u16 param4, u16 param5, u16 param6);
static void ClimaxGlow_Update(ClimaxGlow *param0);
static void ClimaxGlow_Draw(ClimaxGlow *param0);

static void ClimaxBlur_Update(ClimaxBlur *param0)
{
    switch (param0->state) {
    case 0:
        ClimaxBlur_StartInit(param0);
        param0->state++;
        break;
    case 1:
        param0->motionBlur = ClimaxBlur_CreateMotionBlur(param0->blendCoeffA, param0->blendCoeffB);
        param0->state++;
        break;
    case 2:
        break;
    case 3:
        ClimaxBlur_BeginDelete(param0);
        param0->state++;
        break;
    case 4:
        ClimaxBlur_StartRestore(param0);
        param0->state++;
        break;
    case 5:
        break;
    }
}

static void ClimaxBlur_BeginFade(ClimaxBlur *param0)
{
    GF_ASSERT(param0->state == 2);
    param0->state = 3;
}

static u32 ClimaxBlur_GetState(const ClimaxBlur *param0)
{
    return param0->state;
}

static void ClimaxBlur_SetBanks(void)
{
    GXBanks v0 = {
        GX_VRAM_BG_32_FG,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_32_H,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_NONE,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_01_AB,
        GX_VRAM_TEXPLTT_0123_E
    };

    GXLayers_SetBanks(&v0);
}

static void ClimaxBlur_InitBackground(BgConfig *param0)
{
    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_3D
        };

        SetAllGraphicsModes(&v0);
    }

    GXLayers_EngineAToggleLayers(
        GX_PLANEMASK_BG0, 1);

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x4000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_23,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_3, &v1, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_3, 32, 0, HEAP_ID_FIELD1);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_3);
    }
}

static void ClimaxBlur_StartInit(ClimaxBlur *param0)
{
    SysTask_ExecuteAfterVBlank(ClimaxBlur_InitTask, param0, 1024);
}

static void ClimaxBlur_StartRestore(ClimaxBlur *param0)
{
    SysTask_ExecuteAfterVBlank(ClimaxBlur_RestoreTask, param0, 1024);
}

static void ClimaxBlur_InitTask(SysTask *param0, void *param1)
{
    ClimaxBlur *v0 = param1;

    ClimaxBlur_SetBanks();
    ClimaxBlur_ResetBackground(v0->fieldSystem->bgConfig);
    ClimaxBlur_InitBackground(v0->fieldSystem->bgConfig);

    SysTask_Done(param0);
}

static void ClimaxBlur_RestoreTask(SysTask *param0, void *param1)
{
    ClimaxBlur *v0 = param1;

    GXLayers_SetBanks(&v0->banks);
    ClimaxBlur_ResetBackground(v0->fieldSystem->bgConfig);
    ClimaxBlur_RestoreBackground(v0->fieldSystem->bgConfig);
    SysTask_Done(param0);
}

static void ClimaxBlur_ResetBackground(BgConfig *param0)
{
    FieldMap_021D143C(param0);
}

static void ClimaxBlur_RestoreBackground(BgConfig *param0)
{
    FieldMap_021D1434(param0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
}

static MotionBlur *ClimaxBlur_CreateMotionBlur(int param0, int param1)
{
    MotionBlur *motionBlur;

    {
        MotionBlurParams motionBlurParams = {
            GX_DISPMODE_VRAM_C,
            GX_BGMODE_0,
            GX_BG0_AS_3D,
            GX_CAPTURE_SIZE_256x192,
            GX_CAPTURE_MODE_AB,
            GX_CAPTURE_SRCA_2D3D,
            GX_CAPTURE_SRCB_VRAM_0x00000,
            GX_CAPTURE_DEST_VRAM_C_0x00000,
            0,
            0,
            4
        };

        motionBlurParams.blendCoeffA = param0;
        motionBlurParams.blendCoeffB = param1;

        motionBlur = MotionBlur_New(&motionBlurParams);
    }

    return motionBlur;
}

static void ClimaxBlur_BeginDelete(ClimaxBlur *param0)
{
    SysTask_ExecuteAfterVBlank(ClimaxBlur_DeleteTask, param0, 1024);
}

static void ClimaxBlur_DeleteTask(SysTask *param0, void *param1)
{
    ClimaxBlur *v0 = param1;

    MotionBlur_Delete(&v0->motionBlur, GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_3D);
    SysTask_Done(param0);
}

static void FieldEvents_SetMapObjectShadowHidden(FieldSystem *fieldSystem, u32 param1, BOOL param2)
{
    MapObject *v0 = MapObjMan_LocalMapObjByIndex(fieldSystem->mapObjMan, param1);

    if (param2 == 1) {
        MapObject_SetStatusFlagOn(v0, MAP_OBJ_STATUS_HIDE_SHADOW);
    } else {
        MapObject_SetStatusFlagOff(v0, MAP_OBJ_STATUS_HIDE_SHADOW);
    }
}

static BOOL ScreenTransition_UpdateSimple(FieldTask *taskMan)
{
    FieldSystem *fieldSystem = FieldTask_GetFieldSystem(taskMan);
    ScreenTransitionTask *v1 = FieldTask_GetEnv(taskMan);

    switch (v1->state) {
    case 0:
        ScreenTransition_Update(v1->screenTransition);

        if (ScreenTransition_IsFinished(v1->screenTransition) == 1) {
            v1->state++;
        }
        break;
    case 1:
        ScreenTransition_Free(v1->screenTransition);
        Heap_Free(v1);
        return 1;
    }

    return 0;
}

void ScreenTransition_StartSimple(FieldTask *taskMan)
{
    FieldSystem *fieldSystem = FieldTask_GetFieldSystem(taskMan);
    ScreenTransitionTask *v1 = Heap_Alloc(HEAP_ID_FIELD1, sizeof(ScreenTransitionTask));

    memset(v1, 0, sizeof(ScreenTransitionTask));
    v1->screenTransition = ScreenTransition_New(HEAP_ID_FIELD1);

    ScreenTransition_Init(v1->screenTransition, FX32_CONST(2.0f), 0, 1, 16, fieldSystem->camera);
    FieldTask_InitCall(taskMan, ScreenTransition_UpdateSimple, v1);
}

static void ScreenTransition_DecayAmplitude(ScreenTransitionTask *param0)
{
    fx32 v0 = ScreenTransition_GetAmplitude(param0->screenTransition);
    fx32 v1;
    u32 v2 = ScreenTransition_GetLoopCount(param0->screenTransition);

    if (param0->lastLoopCount != v2) {
        param0->lastLoopCount = v2;

        v1 = FX_Div(v0, 8 * FX32_ONE);
        v1 = v0 - v1;

        ScreenTransition_SetAmplitude(param0->screenTransition, v1);
    }
}

static BOOL ScreenTransition_UpdateWithSound(FieldTask *param0)
{
    FieldSystem *fieldSystem = FieldTask_GetFieldSystem(param0);
    ScreenTransitionTask *v1 = FieldTask_GetEnv(param0);

    switch (v1->state) {
    case 0:
        Sound_FadeOutBGM(0, 1);
        v1->state++;
        break;
    case 1:
        if (Sound_IsFadeActive() == FALSE) {
            v1->state++;
            v1->timer = 16;
        }
        break;
    case 2:
        v1->timer--;

        if (v1->timer <= 0) {
            v1->state++;
            Sound_PlayEffect(SEQ_SE_DP_FW089_sseq);
        }
        break;
    case 3:
        ScreenTransition_Update(v1->screenTransition);
        ScreenTransition_DecayAmplitude(v1);

        if (ScreenTransition_IsFinished(v1->screenTransition) == 1) {
            Sound_StopEffect(1628, 0);
            v1->state++;
            v1->timer = 16;
        }
        break;
    case 4:
        v1->timer--;

        if (v1->timer <= 0) {
            v1->state++;
        }
        break;
    case 5:
        Sound_FadeInBGM(127, 16, BGM_FADE_IN_TYPE_FROM_ZERO);
        v1->state++;
        break;
    case 6:
        if (Sound_IsFadeActive() == FALSE) {
            v1->state++;
        }
        break;
    case 7:
        ScreenTransition_Free(v1->screenTransition);
        Heap_Free(v1);
        return 1;
    }

    return 0;
}

void ScreenTransition_StartWithSound(FieldTask *param0)
{
    FieldSystem *fieldSystem = FieldTask_GetFieldSystem(param0);
    ScreenTransitionTask *v1 = Heap_Alloc(HEAP_ID_FIELD1, sizeof(ScreenTransitionTask));

    memset(v1, 0, sizeof(ScreenTransitionTask));
    v1->screenTransition = ScreenTransition_New(HEAP_ID_FIELD1);

    ScreenTransition_Init(v1->screenTransition, FX32_CONST(4.0f), 0, 1, 24, fieldSystem->camera);

    v1->lastLoopCount = ScreenTransition_GetLoopCount(v1->screenTransition);
    FieldTask_InitCall(param0, ScreenTransition_UpdateWithSound, v1);
}

static void ClimaxSequence_Init(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxSequence *v0 = param2;

    memset(v0, 0, sizeof(ClimaxSequence));

    v0->object = ClimaxObject_New(HEAP_ID_FIELD1, fieldSystem);
    v0->state = 0;
}

static void ClimaxSequence_Free(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxSequence *v0 = param2;
    ClimaxObject_Free(v0->object);
}

static void ClimaxSequence_Update(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxSequence *v0 = param2;
    BOOL v1[2];
    BOOL v2;

    switch (v0->state) {
    case 0:
        v0->state++;
    case 1:
        v0->state++;
    case 2:
        ClimaxObject_Start(v0->object, 0);
        v0->timer = 0;
        v0->subTimer = 0;
        v0->state++;
        break;
    case 3: {
        BOOL v3 = 0;

        if (v0->timer != 12) {
            if ((++v0->subTimer) >= 8) {
                v3 = ClimaxObjectModel_UpdateBlend(v0->object, v0->timer % 2, v0->timer);

                if (v3) {
                    v0->subTimer = 0;
                    v0->timer++;
                }
            }
        } else {
            v3 = 1;
        }

        if (ClimaxObjectModel_UpdateAnims(v0->object) && v3) {
            v0->subTimer = 0;
            v0->state = 4;
        }
    } break;
    case 4:
        if (ClimaxObjectModel_UpdateBlend(v0->object, 0, 60)) {
            v0->subTimer = 0;
            v0->state = 11;
        }
        break;
    case 5:
        v1[0] = ClimaxFade_Update(&v0->fade);

        if (v0->fade.state == 3) {
            if (BrightnessFader_GetValue(v0->fade.brightnessFader) == 13) {
                v0->flash = ClimaxFlash_New(HEAP_ID_FIELD1, fieldSystem);
            }
        }

        if (v1[0] == 1) {
            v0->state++;
        }
        break;
    case 6:
        ClimaxBlur_BeginFade(&v0->blur);
        v0->state++;
        break;
    case 7:
        ClimaxBlur_Update(&v0->blur);

        if (ClimaxBlur_GetState(&v0->blur) == 5) {
            v0->state++;
        }
        break;
    case 8:
        ClimaxFlash_Start(v0->flash, 0);
        v0->timer = 72;
        v0->state++;
        break;
    case 9:
        v0->timer--;

        if (v0->timer <= 0) {
            FieldEvents_SetMapObjectShadowHidden(fieldSystem, 0, 1);
            v0->state++;
        }
    case 10:
        v2 = ClimaxFlash_IsFinished(v0->flash);

        if (v2 == 1) {
            FieldEvents_SetMapObjectShadowHidden(fieldSystem, 0, 0);
            v0->state++;
        }
        break;
    case 11:
        break;
    default:
        break;
    }
}

static void ClimaxSequence_Cleanup(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxSequence *v0 = param2;

    ClimaxObject_Cleanup(v0->object);

    if (v0->flash) {
        ClimaxFlash_Draw(v0->flash);
    }
}

FieldEffect *ClimaxSequence_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024,
        sizeof(ClimaxSequence),
        ClimaxSequence_Init,
        ClimaxSequence_Free,
        ClimaxSequence_Update,
        ClimaxSequence_Cleanup
    };
    FieldEffect *v1 = FieldMap_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

void ClimaxSequence_Delete(FieldEffect *param0)
{
    FieldMap_021D1BEC(param0);
}

BOOL ClimaxSequence_IsFinished(FieldEffect *param0)
{
    ClimaxSequence *v0 = FieldMap_021D1C2C(param0);

    if (v0->state == 11) {
        return 1;
    }

    return 0;
}

static BOOL ClimaxFade_Update(ClimaxFade *param0)
{
    switch (param0->state) {
    case 0:
        param0->timer--;

        if (param0->timer < 0) {
            param0->state++;
        }
        break;
    case 1:
        BrightnessFader_Start(param0->brightnessFader, 13, 4, 8);
        param0->state++;
        param0->timer = 16;
        break;
    case 2:
        param0->timer--;

        if (param0->timer < 0) {
            BrightnessFader_Start(param0->brightnessFader, 13, 4, 8);
            param0->state++;
            param0->timer = 16;
        }
        break;
    case 3:
        param0->timer--;

        if (param0->timer < 0) {
            BrightnessFader_Start(param0->brightnessFader, 13, 4, 32);
            param0->state++;
            param0->timer = 40;
        }
        break;
    case 4:
        param0->timer--;

        if (param0->timer < 0) {
            return 1;
        }
        break;
    }

    return 0;
}

static void ClimaxObjectEffect_Init(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxObjectEffect *v0 = param2;
    MapObject *v1;
    u16 v2, v3, v4;

    v1 = MapObjMan_LocalMapObjByIndex(fieldSystem->mapObjMan, 0);
    GF_ASSERT(v1);

    v2 = MapObject_GetX(v1);
    v3 = 0;
    v4 = MapObject_GetZ(v1);

    v0->particles = ClimaxParticles_NewDefault(HEAP_ID_FIELD1);
    ClimaxParticles_SetPosition(v0->particles, v2, v3, v4);
}

static void ClimaxObjectEffect_Free(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxObjectEffect *v0 = param2;
    ClimaxParticles_Delete(v0->particles);
}

static void ClimaxObjectEffect_Update(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxObjectEffect *v0 = param2;
    ClimaxParticles_UpdatePublic(v0->particles);
}

static void ClimaxObjectEffect_Draw(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxObjectEffect *v0 = param2;
    ClimaxParticles_DrawPublic(v0->particles);
}

FieldEffect *ClimaxObjectEffect_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024,
        sizeof(ClimaxObjectEffect),
        ClimaxObjectEffect_Init,
        ClimaxObjectEffect_Free,
        ClimaxObjectEffect_Update,
        ClimaxObjectEffect_Draw
    };
    FieldEffect *v1 = FieldMap_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

void ClimaxObjectEffect_Delete(FieldEffect *param0)
{
    FieldMap_021D1BEC(param0);
}

static void ClimaxScene_InitVariant0(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxScene *v0 = param2;
    VecFx32 v1;
    CameraAngle v2;

#if (GAME_VERSION == VERSION_DIAMOND || GAME_VERSION == VERSION_PLATINUM)
    Camera_SetFOV(0x1701, fieldSystem->camera);
    Camera_SetDistance(0xc8a55, fieldSystem->camera);
    v1.x = 0x2280ef;
    v1.y = 0xca424;
    v1.z = 0x268c50;
    Camera_SetTarget(&v1, fieldSystem->camera);
    v2.x = 0x22a2;
    v2.y = 0xf800;
    v2.z = 0;
    Camera_SetAngleAroundTarget(&v2, fieldSystem->camera);

    Camera_SetClipping(2 * FX32_ONE, 2000 * FX32_ONE, fieldSystem->camera);
#elif (GAME_VERSION == VERSION_PEARL)
    Camera_SetFOV(0x10c1, fieldSystem->camera);
    Camera_SetDistance(0xD5052, fieldSystem->camera);
    v1.x = 0x1bffbd;
    v1.y = 0xaa361;
    v1.z = 0x25dfdc;
    Camera_SetTarget(&v1, fieldSystem->camera);
    v2.unk_00 = 0x19a3;
    v2.unk_02 = 0x90c;
    v2.unk_04 = 0;
    Camera_SetAngleAroundTarget(&v2, fieldSystem->camera);

    Camera_SetClipping(14 * FX32_ONE, 2031 * FX32_ONE, fieldSystem->camera);
#endif

    v0->glow = ClimaxGlow_NewDefault(HEAP_ID_FIELD1);
    v0->particles = ClimaxParticles_NewDefault2(HEAP_ID_FIELD1);

    v1 = Camera_GetTarget(fieldSystem->camera);

    ClimaxGlow_SetPositionVariant0(v0->glow, v1.x, v1.y, v1.z);
    ClimaxParticles_SetPositionVariant0(v0->particles, v1.x, v1.y, v1.z);
}

static void ClimaxScene_InitVariant1(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxScene *v0 = param2;
    VecFx32 v1;
    CameraAngle v2;

    Camera_SetFOV(0xf81, fieldSystem->camera);
    Camera_SetDistance(0x17e532, fieldSystem->camera);

    v1.x = 0xf99d58;
    v1.y = 0xc5502;
    v1.z = 0x28cf549;

    Camera_SetTarget(&v1, fieldSystem->camera);

    v2.x = 0x642;
    v2.y = 0xeda0;
    v2.z = 0;

    Camera_SetAngleAroundTarget(&v2, fieldSystem->camera);
    Camera_SetClipping(88 * FX32_ONE, 2000 * FX32_ONE, fieldSystem->camera);
    AreaLightManager_Free(&fieldSystem->areaLightMan);

    fieldSystem->areaLightMan = AreaLightManager_New(fieldSystem->areaModelAttrs, 3);

    v0->glow = ClimaxGlow_NewDefault(HEAP_ID_FIELD1);
    v0->particles = ClimaxParticles_NewDefault2(HEAP_ID_FIELD1);

    v1 = Camera_GetTarget(fieldSystem->camera);

    ClimaxGlow_SetPositionVariant1(v0->glow, v1.x, v1.y, v1.z);
    ClimaxParticles_SetPositionVariant1(v0->particles, v1.x, v1.y, v1.z);
}

static void ClimaxScene_InitVariant2(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxScene *v0 = param2;
    VecFx32 v1;
    CameraAngle v2;

    Camera_SetFOV(0x4c1, fieldSystem->camera);
    Camera_SetDistance(0x26bec1, fieldSystem->camera);

    v1.x = 0x1df5dfd;
    v1.y = 0x73a0c;
    v1.z = 0x2b9f4a2;

    Camera_SetTarget(&v1, fieldSystem->camera);

    v2.x = 0x4c2;
    v2.y = 0xa40;
    v2.z = 0;

    Camera_SetAngleAroundTarget(&v2, fieldSystem->camera);
    Camera_SetClipping(176 * FX32_ONE, 1480 * FX32_ONE, fieldSystem->camera);
    AreaLightManager_Free(&fieldSystem->areaLightMan);

    fieldSystem->areaLightMan = AreaLightManager_New(fieldSystem->areaModelAttrs, 3);

    v0->glow = ClimaxGlow_NewDefault(HEAP_ID_FIELD1);
    v0->particles = ClimaxParticles_NewDefault2(HEAP_ID_FIELD1);

    v1 = Camera_GetTarget(fieldSystem->camera);

    ClimaxGlow_SetPositionVariant2(v0->glow, v1.x, v1.y, v1.z);
    ClimaxParticles_SetPositionVariant2(v0->particles, v1.x, v1.y, v1.z);
}

static void ClimaxScene_Free(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxScene *v0 = param2;

    ClimaxGlow_Delete(v0->glow);
    ClimaxParticles_Delete2(v0->particles);
}

static void ClimaxScene_Update(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxScene *v0 = param2;

    ClimaxGlow_UpdatePublic(v0->glow);
    ClimaxParticles_Update2(v0->particles);
}

static void ClimaxScene_Draw(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxScene *v0 = param2;

    ClimaxGlow_DrawPublic(v0->glow);
    ClimaxParticles_Draw2(v0->particles);
}

FieldEffect *ClimaxScene_New(FieldSystem *fieldSystem, u32 param1)
{
    static FieldEffectTemplate v0 = {
        1024,
        sizeof(ClimaxScene),
        NULL,
        ClimaxScene_Free,
        ClimaxScene_Update,
        ClimaxScene_Draw
    };
    static const FieldEffectFunc v1[] = {
        ClimaxScene_InitVariant0,
        ClimaxScene_InitVariant1,
        ClimaxScene_InitVariant2
    };
    FieldEffect *v2;

    v0.init = v1[param1];
    v2 = FieldMap_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v2;
}

static void ClimaxActor_LoadModel(ClimaxActor *param0)
{
    int v0;
    int v1;
    NARC *v2;
    static const int v3[][2] = {
        { 12, 11 },
        { 8, 7 },
        { 10, 9 }
    };

    v2 = NARC_ctor(NARC_INDEX_ARC__DEMO_TENGAN_GRA, HEAP_ID_FIELD1);
    v0 = v3[param0->variant][0];
    v1 = v3[param0->variant][1];

    Easy3DModel_LoadFrom(&param0->model, v2, v0, HEAP_ID_FIELD1);
    Easy3DObject_Init(&param0->object, &param0->model);
    Easy3DObject_SetPosition(&param0->object, 0, 0, 0);
    Easy3DObject_SetScale(&param0->object, FX32_CONST(1.00f), FX32_CONST(1.00f), FX32_CONST(1.00f));
    Easy3DObject_SetVisible(&param0->object, 1);
    Easy3DAnim_LoadFrom(&param0->anim, &param0->model, v2, v1, 4, &param0->allocator);
    Easy3DAnim_SetFrame(&param0->anim, 0);
    Easy3DObject_AddAnim(&param0->object, &param0->anim);
    NARC_dtor(v2);
}

static void ClimaxActor_UnloadModel(ClimaxActor *param0)
{
    Easy3DModel_Release(&param0->model);
    Easy3DAnim_Release(&param0->anim, &param0->allocator);
}

static void ClimaxActor_Init(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxActor *v0 = param2;

    v0->manager = ClimaxActorManager_New(fieldSystem);
    v0->masterBrightness = 0;
    v0->variant = 0;
    v0->facingTimer = 0;
    v0->animationState = 0;
    v0->animationStep = 0;
    v0->frame = 30;
    v0->fieldSystem = fieldSystem;
    v0->mapObject1 = MapObjMan_LocalMapObjByIndex(v0->fieldSystem->mapObjMan, 1);
    v0->mapObject0 = MapObjMan_LocalMapObjByIndex(v0->fieldSystem->mapObjMan, 0);
    v0->playerMapObject = PlayerAvatar_GetMapObject(FieldSystem_GetPlayerAvatar(v0->fieldSystem));

    HeapExp_FndInitAllocator(&v0->allocator, HEAP_ID_FIELD1, 32);
    ClimaxActor_LoadModel(v0);
    GX_SetMasterBrightness(v0->masterBrightness);

    v0->state = 0;
}

static void ClimaxActor_Free(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxActor *v0 = param2;
    ClimaxActorManager_Free(v0->manager);
}

static const fx32 sClimaxActorStartTiles[][2] = {
    { 0x1F8, 0x14A },
    { 0x243, 0x14A },
    { 0x1F8, 0x14A }
};

static BOOL ClimaxActor_AnimateVariant0(ClimaxActor *param0)
{
    BOOL v0[2];
    fx32 v1, v2, v3;

    switch (param0->animationStep) {
    case 0:
        param0->frame = 0;
        param0->targetX = FX32_CONST(573);
        param0->targetZ = FX32_CONST(330 + 30);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 20);
        Interpolator_Init(&param0->interpZ, v3, param0->targetZ, 20);
        param0->animationStep++;
        break;
    case 1:
        param0->frame++;
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        v0[1] = Interpolator_Update(&param0->interpZ, param0->frame);
        Easy3DObject_SetPosition(&param0->object, param0->interpX.value, v2, param0->interpZ.value);

        if (v0[0] && v0[1]) {
            Sound_PlayPokemonCryEx(POKECRY_NORMAL, SPECIES_UXIE, 0, 100, HEAP_ID_FIELD1, 0);
            param0->animationStep++;
        }
        break;
    case 2:
        param0->frame = 0;
        param0->targetX = FX32_CONST(444);
        param0->targetZ = FX32_CONST(330 + 30);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 20);
        param0->animationStep++;
        break;
    case 3:
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        param0->targetZ += (CalcCosineDegrees_Wraparound(param0->frame * (180 / 20)) * 3);
        param0->frame++;
        Easy3DObject_SetPosition(&param0->object, param0->interpX.value, v2, param0->targetZ);

        if (v0[0]) {
            param0->animationStep++;
        }
        break;
    case 4:
        param0->frame = 0;
        param0->targetX = FX32_CONST(507);
        param0->targetZ = FX32_CONST(330 + 30);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 20);
        param0->animationStep++;
        break;
    case 5:
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        param0->targetZ -= (CalcCosineDegrees_Wraparound(param0->frame * (90 / 20)) * 3);
        param0->frame++;
        Easy3DObject_SetPosition(&param0->object, param0->interpX.value, v2, param0->targetZ);

        if (v0[0]) {
            param0->animationStep = 99;
        }
        break;
    case 99:
        param0->animationStep++;
    default:
        param0->animationStep = 0;
        return 1;
        break;
    }

    return 0;
}

static BOOL ClimaxActor_AnimateVariant2(ClimaxActor *param0)
{
    BOOL v0[2];
    fx32 v1, v2, v3;

    switch (param0->animationStep) {
    case 0:
        param0->frame = 0;
        param0->targetX = FX32_CONST(555);
        param0->targetZ = FX32_CONST(317 + 30);
        param0->offsetZ = FX32_CONST(0);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 32);
        Interpolator_Init(&param0->interpZ, v3, param0->targetZ, 32);
        param0->animationStep++;
        break;
    case 1:
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        v0[1] = Interpolator_Update(&param0->interpZ, param0->frame);
        param0->frame++;
        Easy3DObject_SetPosition(&param0->object, param0->interpX.value, v2, param0->interpZ.value + param0->offsetZ);

        if (v0[0] && v0[1]) {
            param0->animationStep++;
        }
        break;
    case 2:
        param0->frame = 0;
        param0->targetX = FX32_CONST(507);
        param0->targetZ = FX32_CONST(317 + 30);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 32);
        param0->animationStep++;
        break;
    case 3:
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        param0->targetZ += (CalcCosineDegrees_Wraparound(param0->frame * (180 / 32)) * 3);
        param0->frame++;
        Easy3DObject_SetPosition(&param0->object, param0->interpX.value, v2, param0->targetZ);

        if (v0[0]) {
            param0->animationStep++;
        }
        break;
    case 4:
        param0->frame = 0;
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &param0->targetZ);
        param0->animationStep++;
    case 5:
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        param0->targetZ -= (CalcCosineDegrees_Wraparound(param0->frame * (360 / 32)) * 2);
        param0->frame++;
        Easy3DObject_SetPosition(&param0->object, v1, v2, param0->targetZ);

        if (param0->frame >= (32 * 2)) {
            param0->frame = 0;
            param0->animationStep++;
        }
        break;
    case 6:
        param0->frame = 0;
        param0->targetX = FX32_CONST(465);
        param0->targetZ = FX32_CONST(468 + 30);
        param0->offsetX = FX32_CONST(0);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 32);
        Interpolator_Init(&param0->interpZ, v3, param0->targetZ, 32);
        param0->animationStep++;
        break;
    case 7:
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        v0[1] = Interpolator_Update(&param0->interpZ, param0->frame);
        param0->frame++;
        param0->offsetX -= (CalcCosineDegrees_Wraparound((param0->frame + 1) * (180 / 32)) * 4);
        Easy3DObject_SetPosition(&param0->object, param0->interpX.value + param0->offsetX, v2, param0->interpZ.value);

        if (v0[0] && v0[1]) {
            param0->animationStep++;
        }
        break;
    case 8:
        param0->frame = 0;
        MapObject_Face(param0->mapObject0, 2);
        LocalMapObj_SetAnimationCode(param0->playerMapObject, MOVEMENT_ACTION_FACE_WEST);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &param0->targetZ);
        param0->animationStep++;
    case 9:
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        param0->targetZ += (CalcCosineDegrees_Wraparound(param0->frame * (360 / 32)) * 1);
        param0->frame++;
        Easy3DObject_SetPosition(&param0->object, v1, v2, param0->targetZ);

        if (param0->frame >= (32 * 1)) {
            param0->facingTimer = 1;
            param0->frame = 0;
            param0->animationStep++;
        }
        break;
    case 10:
        param0->frame = 0;
        param0->targetX = FX32_CONST(503);
        param0->targetZ = FX32_CONST(475 + 30);
        param0->offsetZ = FX32_CONST(0);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 32);
        Interpolator_Init(&param0->interpZ, v3, param0->targetZ, 32);
        param0->animationStep++;
        break;
    case 11:
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        v0[1] = Interpolator_Update(&param0->interpZ, param0->frame);
        param0->offsetZ += (CalcCosineDegrees_Wraparound(param0->frame * (180 / 32)) * 2);
        param0->frame++;
        Easy3DObject_SetPosition(&param0->object, param0->interpX.value, v2, param0->interpZ.value + param0->offsetZ);

        if (v0[0] && v0[1]) {
            param0->animationStep++;
        }
        break;
    case 12:
        param0->frame = 0;
        param0->targetX = FX32_CONST(503);
        param0->targetZ = FX32_CONST(454 + 30);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 32 / 4);
        Interpolator_Init(&param0->interpZ, v3, param0->targetZ, 32 / 4);
        param0->animationStep++;
        break;
    case 13:
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        v0[1] = Interpolator_Update(&param0->interpZ, param0->frame);
        param0->frame++;

        if (param0->frame >= 4) {
            if (param0->masterBrightness < 16) {
                param0->masterBrightness += 2;
                GX_SetMasterBrightness(param0->masterBrightness);
            }
        }

        Easy3DObject_SetPosition(&param0->object, param0->interpX.value, v2, param0->interpZ.value);

        if (v0[0] && v0[1]) {
            param0->animationStep++;
        }
        break;
    case 14:
        if (param0->masterBrightness < 16) {
            param0->masterBrightness += 2;
            GX_SetMasterBrightness(param0->masterBrightness);
            break;
        }

        MapObject_SetHidden(param0->mapObject1, 0);
        Easy3DObject_SetVisible(&param0->object, 0);
        param0->animationStep++;
        break;
    case 15:
        if (param0->masterBrightness > 0) {
            param0->masterBrightness -= 1;
            GX_SetMasterBrightness(param0->masterBrightness);
            break;
        }

        param0->frame = 0;
        Sound_PlayPokemonCryEx(POKECRY_NORMAL, SPECIES_MESPRIT, 0, 100, HEAP_ID_FIELD1, 0);
        param0->animationStep++;
        break;
    case 16:
        if ((++param0->frame) < 60) {
            break;
        }

        param0->animationStep++;
        break;
    case 17:
        if (param0->masterBrightness < 16) {
            param0->masterBrightness += 2;
            GX_SetMasterBrightness(param0->masterBrightness);
            break;
        }

        MapObject_SetHidden(param0->mapObject1, 1);
        Easy3DObject_SetVisible(&param0->object, 1);

        param0->animationStep++;
    case 18:
        param0->animationStep++;
        break;
    case 19:
        param0->frame = 0;
        param0->targetZ = FX32_CONST(319 + 30);
        param0->offsetX = FX32_CONST(0);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        param0->targetX = v1;
        Interpolator_Init(&param0->interpZ, v3, param0->targetZ, 32);
        param0->animationStep++;
        break;
    case 20:
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpZ, param0->frame);
        param0->frame++;

        if (param0->masterBrightness > 0) {
            param0->masterBrightness -= 1;
            GX_SetMasterBrightness(param0->masterBrightness);
        }

        param0->offsetX += (CalcCosineDegrees_Wraparound((param0->frame + 1) * (180 / 32)) * 8);
        Easy3DObject_SetPosition(&param0->object, param0->targetX + param0->offsetX, v2, param0->interpZ.value);

        if (v0[0]) {
            param0->animationStep = 99;
        }
        break;
    case 99:
        param0->frame = 0;
        param0->targetX = FX32_CONST(sClimaxActorStartTiles[param0->variant][0]);
        param0->targetZ = FX32_CONST(sClimaxActorStartTiles[param0->variant][1]);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 20);
        Interpolator_Init(&param0->interpZ, v3, param0->targetZ, 20);
        param0->animationStep++;
        break;
    case 100:
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        v0[1] = Interpolator_Update(&param0->interpZ, param0->frame);
        param0->frame++;
        Easy3DObject_SetPosition(&param0->object, param0->interpX.value, v2, param0->interpZ.value);

        if (v0[0] && v0[1]) {
            param0->animationStep++;
        }
        break;
    default:
        param0->animationStep = 0;
        return 1;
        break;
    }

    if (param0->facingTimer != 0) {
        if (param0->facingTimer == 20) {
            MapObject_Face(param0->mapObject0, 1);
            LocalMapObj_SetAnimationCode(param0->playerMapObject, MOVEMENT_ACTION_FACE_SOUTH);
        }

        if (param0->facingTimer == 40) {
            MapObject_Face(param0->mapObject0, 2);
            LocalMapObj_SetAnimationCode(param0->playerMapObject, MOVEMENT_ACTION_FACE_EAST);
        }

        if (param0->facingTimer == 50) {
            MapObject_Face(param0->mapObject0, 0);
            LocalMapObj_SetAnimationCode(param0->playerMapObject, MOVEMENT_ACTION_FACE_NORTH);
        }

        param0->facingTimer++;
    }

    return 0;
}

static BOOL ClimaxActor_AnimateVariant1(ClimaxActor *param0)
{
    BOOL v0[2];
    fx32 v1, v2, v3;

    switch (param0->animationStep) {
    case 0:
        param0->frame = 0;
        param0->targetX = FX32_CONST(606);
        param0->targetZ = FX32_CONST(340 + 30);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 8);
        Interpolator_Init(&param0->interpZ, v3, param0->targetZ, 8);
        param0->animationStep++;
        break;
    case 1:
        param0->frame++;
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        v0[1] = Interpolator_Update(&param0->interpZ, param0->frame);
        Easy3DObject_SetPosition(&param0->object, param0->interpX.value, v2, param0->interpZ.value);

        if (v0[0] && v0[1]) {
            param0->animationStep++;
        }
        break;
    case 2:
        param0->frame = 0;
        param0->targetX = FX32_CONST(438);
        param0->targetZ = FX32_CONST(412 + 30);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 8);
        Interpolator_Init(&param0->interpZ, v3, param0->targetZ, 8);
        param0->animationStep++;
        break;
    case 3:
        param0->frame++;
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        v0[1] = Interpolator_Update(&param0->interpZ, param0->frame);
        Easy3DObject_SetPosition(&param0->object, param0->interpX.value, v2, param0->interpZ.value);

        if (v0[0] && v0[1]) {
            Sound_PlayPokemonCryEx(POKECRY_NORMAL, SPECIES_AZELF, 0, 100, HEAP_ID_FIELD1, 0);
            param0->animationStep++;
        }

        break;
    case 4:
        param0->frame = 0;
        param0->targetX = FX32_CONST(504);
        param0->targetZ = FX32_CONST(307 + 30);
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 8);
        Interpolator_Init(&param0->interpZ, v3, param0->targetZ, 8);
        param0->animationStep++;
        break;
    case 5:
        param0->frame++;
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        v0[1] = Interpolator_Update(&param0->interpZ, param0->frame);
        Easy3DObject_SetPosition(&param0->object, param0->interpX.value, v2, param0->interpZ.value);

        if (v0[0] && v0[1]) {
            param0->animationStep++;
        }
        break;
    case 6:
        if ((++param0->frame) > 15) {
            param0->animationStep = 99;
        }
        break;
    case 99:
        param0->animationStep++;
    default:
        param0->animationStep = 0;
        return 1;
        break;
    }

    return 0;
}

static BOOL ClimaxActor_UpdateAnimation(ClimaxActor *param0)
{
    BOOL v0[2];
    fx32 v1, v2, v3;

    switch (param0->animationState) {
    case 0:
        switch (param0->variant) {
        case 0:
            v0[0] = ClimaxActor_AnimateVariant0(param0);
            break;
        case 1:
            v0[0] = ClimaxActor_AnimateVariant1(param0);
            break;
        case 2:
            v0[0] = ClimaxActor_AnimateVariant2(param0);
            break;
        }

        if (v0[0]) {
            param0->animationState++;
        }
        break;
    case 1: {
        param0->targetX = FX32_CONST(504);
        param0->targetZ = FX32_CONST(439);
        param0->frame = 0;
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);
        Interpolator_Init(&param0->interpX, v1, param0->targetX, 6);
        Interpolator_Init(&param0->interpZ, v3, param0->targetZ, 6);
        param0->animationState++;
    } break;
    case 2: {
        Easy3DObject_GetPosition(&param0->object, &v1, &v2, &v3);

        v0[0] = Interpolator_Update(&param0->interpX, param0->frame);
        v0[1] = Interpolator_Update(&param0->interpZ, param0->frame);
        param0->frame++;

        Easy3DObject_SetPosition(&param0->object, param0->interpX.value, v2, param0->interpZ.value);

        if (v0[0] && v0[1]) {
            param0->animationState++;
        }
    } break;
    default:
        return 1;
        break;
    }

    return 0;
}

static void ClimaxActor_Update(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxActor *v0 = param2;
    u32 v1[2];
    VecFx32 v2;
    int v3[] = { 68, 38, 390 };

    switch (v0->state) {
    case 0:
        if (v0->frame != 0) {
            v0->frame--;
            break;
        }

        if (v0->masterBrightness > 0) {
            v0->masterBrightness -= 1;
            GX_SetMasterBrightness(v0->masterBrightness);
            break;
        }

        v2 = Camera_GetTarget(fieldSystem->camera);
        {
            int v4[] = {
                504, 504, 435
            };

            Easy3DObject_SetPosition(&v0->object, FX32_CONST(v4[v0->variant]), FX32_CONST(99), FX32_CONST(290 + 30));
        }

        v0->timer = 0;
        v0->state++;
        break;
    case 1:
        if (ClimaxActor_UpdateAnimation(v0)) {
            Sound_PlayEffect(SEQ_SE_DP_CLIMAX10_sseq);
            v0->timer = 0;
            v0->state++;
        } else {
            v0->timer++;

            if (v3[v0->variant] < v0->timer) {
                if (v0->masterBrightness != 16) {
                    v0->masterBrightness += 2;
                    GX_SetMasterBrightness(v0->masterBrightness);
                } else {
                    v0->timer = 0;
                }
            }
            break;
        }
    case 2:
        if (v0->masterBrightness != 16) {
            v0->masterBrightness += 2;
            GX_SetMasterBrightness(v0->masterBrightness);
            break;
        }

        v0->variant++;
        v0->animationState = 0;
        v0->frame = 30;

        ClimaxActor_UnloadModel(v0);

        if (v0->variant != 3) {
            ClimaxActor_LoadModel(v0);
            v0->state = 0;
        } else {
            v0->state++;
        }
        break;
    default:
        if (v0->frame != 0) {
            v0->frame--;
            break;
        }

        if (v0->masterBrightness > 0) {
            v0->masterBrightness -= 1;
            GX_SetMasterBrightness(v0->masterBrightness);
            break;
        }

        v0->state = 6;
        break;
    }

    if (v0->variant != 3) {
        G3_Identity();
        Easy3DAnim_UpdateLooped(&v0->anim, FX32_ONE);
        NNS_G3dGePushMtx();
        Easy3DObject_Draw(&v0->object);
        NNS_G3dGePopMtx(1);
    }
}

static void ClimaxActor_Draw(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    ClimaxActor *v0 = param2;
    ClimaxActorManager_Draw(v0->manager);
}

FieldEffect *ClimaxActor_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024, sizeof(ClimaxActor), ClimaxActor_Init, ClimaxActor_Free, ClimaxActor_Update, ClimaxActor_Draw
    };
    FieldEffect *v1 = FieldMap_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

void ClimaxActor_Delete(FieldEffect *param0)
{
    FieldMap_021D1BEC(param0);
}

void ClimaxActor_Finish(FieldEffect *param0)
{
    ClimaxActor *v0 = FieldMap_021D1C2C(param0);
    v0->state = 3;
}

u32 ClimaxActor_GetState(FieldEffect *param0)
{
    ClimaxActor *v0 = FieldMap_021D1C2C(param0);

    return v0->state;
}

static void Interpolator_InitInt(IntInterpolator *param0, s32 param1, s32 param2, s32 param3)
{
    param0->value = param1;
    param0->start = param1;
    param0->delta = param2 - param1;
    param0->duration = param3;
}

static void Interpolator_Init(FxInterpolator *param0, fx32 param1, fx32 param2, s32 param3)
{
    param0->value = param1;
    param0->start = param1;
    param0->delta = param2 - param1;
    param0->duration = param3;
}

static BOOL Interpolator_Update(FxInterpolator *param0, s32 param1)
{
    s32 v0;
    BOOL v1;
    fx32 v2;

    if (param1 >= param0->duration) {
        v0 = param0->duration;
        v1 = 1;
    } else {
        v0 = param1;
        v1 = 0;
    }

    v2 = FX_Mul(param0->delta, v0 << FX32_SHIFT);
    v2 = FX_Div(v2, param0->duration << FX32_SHIFT);
    v2 += param0->start;

    param0->value = v2;

    return v1;
}

static void Climax3D_ModelLoad(Easy3DModel *param0, u32 param1, u32 param2, u32 param3)
{
    Easy3DModel_Load(param0, param1, param2, param3);
}

static void Climax3D_ModelLoadFrom(Easy3DModel *param0, NARC *param1, u32 param2, enum HeapID heapID)
{
    Easy3DModel_LoadFrom(param0, param1, param2, heapID);
}

static void Climax3D_ModelRelease(Easy3DModel *param0)
{
    Easy3DModel_Release(param0);
}

static void Climax3D_AnimLoadFrom(Easy3DAnim *param0, const Easy3DModel *param1, NARC *param2, u32 param3, u32 param4, NNSFndAllocator *param5)
{
    Easy3DAnim_LoadFrom(param0, param1, param2, param3, param4, param5);
}

static void Climax3D_AnimRelease(Easy3DAnim *param0, NNSFndAllocator *param1)
{
    Easy3DAnim_Release(param0, param1);
}

static void Climax3D_AnimUpdateLooped(Easy3DAnim *param0)
{
    Easy3DAnim_UpdateLooped(param0, FX32_ONE);
}

static BOOL Climax3D_AnimUpdate(Easy3DAnim *param0)
{
    return Easy3DAnim_Update(param0, FX32_ONE);
}

static void Climax3D_AnimSetFrame(Easy3DAnim *param0, fx32 param1)
{
    Easy3DAnim_SetFrame(param0, param1);
}

static void Climax3D_ObjectInit(Easy3DObject *param0, Easy3DModel *param1)
{
    Easy3DObject_Init(param0, param1);
}

static void Climax3D_ObjectAddAnim(Easy3DObject *param0, Easy3DAnim *param1)
{
    Easy3DObject_AddAnim(param0, param1);
}

static void Climax3D_ObjectDraw(Easy3DObject *param0)
{
    Easy3DObject_Draw(param0);
}

static void Climax3D_ObjectSetVisible(Easy3DObject *param0, BOOL param1)
{
    Easy3DObject_SetVisible(param0, param1);
}

static void Climax3D_ObjectSetPosition(Easy3DObject *param0, fx32 param1, fx32 param2, fx32 param3)
{
    Easy3DObject_SetPosition(param0, param1, param2, param3);
}

static void Climax3D_ObjectSetScale(Easy3DObject *param0, fx32 param1, fx32 param2, fx32 param3)
{
    Easy3DObject_SetScale(param0, param1, param2, param3);
}

static void Climax3D_ObjectSetRotation(Easy3DObject *param0, u16 param1, u32 param2)
{
    Easy3DObject_SetRotation(param0, param1, param2);
}

ScreenTransition *ScreenTransition_New(enum HeapID heapID)
{
    ScreenTransition *v0 = Heap_Alloc(heapID, sizeof(ScreenTransition));
    memset(v0, 0, sizeof(ScreenTransition));
    v0->camera1 = Camera_Alloc(heapID);
    v0->state = 5;

    return v0;
}

void ScreenTransition_Free(ScreenTransition *param0)
{
    Camera_Delete(param0->camera1);
    Heap_Free(param0);
}

void ScreenTransition_Init(ScreenTransition *param0, fx32 param1, fx32 param2, u32 param3, u32 param4, Camera *camera)
{
    ScreenTransition_Reset(param0);
    Camera_Copy(camera, param0->camera1);

    param0->target = Camera_GetTarget(camera);
    param0->baseTarget = param0->target;

    Camera_TrackTarget(&param0->target, param0->camera1);
    Camera_SetAsActive(param0->camera1);

    param0->camera2 = camera;

    Interpolator_Init(&param0->interpX, 0, param1, param3);
    Interpolator_Init(&param0->interpY, 0, param2, param3);

    param0->loopCount = param4;

    Sound_PlayEffect(SEQ_SE_DP_CLIMAX09_sseq);
}

void ScreenTransition_Update(ScreenTransition *param0)
{
    BOOL v0;

    switch (param0->state) {
    case 0:
        param0->timer++;
        v0 = ScreenTransition_UpdateInterpolators(param0);
        ScreenTransition_ApplyTarget(param0, param0->interpX.value, param0->interpY.value);

        if (v0 == 1) {
            param0->state++;
        }
        break;
    case 1:
        param0->timer--;
        ScreenTransition_UpdateInterpolators(param0);
        ScreenTransition_ApplyTarget(param0, param0->interpX.value, param0->interpY.value);

        if (param0->timer <= 0) {
            param0->state++;
        }
        break;
    case 2:
        param0->timer++;
        v0 = ScreenTransition_UpdateInterpolators(param0);
        ScreenTransition_ApplyTarget(param0, -param0->interpX.value, -param0->interpY.value);

        if (v0 == 1) {
            param0->state++;
        }
        break;
    case 3:
        param0->timer--;
        ScreenTransition_UpdateInterpolators(param0);
        ScreenTransition_ApplyTarget(param0, -param0->interpX.value, -param0->interpY.value);

        if (param0->timer <= 0) {
            param0->loopCount--;

            if (param0->loopCount > 0) {
                param0->state = 0;
            } else {
                param0->state++;
            }
        }
        break;
    case 4:
        Camera_SetAsActive(param0->camera2);
        param0->state++;
        break;
    case 5:
        break;

    default:
        break;
    }
}

BOOL ScreenTransition_IsFinished(ScreenTransition *param0)
{
    if (param0->state == 5) {
        return 1;
    }

    return 0;
}

static void ScreenTransition_Reset(ScreenTransition *param0)
{
    memset(&param0->interpX, 0, sizeof(FxInterpolator));
    memset(&param0->interpY, 0, sizeof(FxInterpolator));
    memset(&param0->target, 0, sizeof(VecFx32));

    param0->state = 0;
    param0->timer = 0;
    param0->loopCount = 0;
}

static BOOL ScreenTransition_UpdateInterpolators(ScreenTransition *param0)
{
    BOOL v0 = Interpolator_Update(&param0->interpX, param0->timer);
    Interpolator_Update(&param0->interpY, param0->timer);

    return v0;
}

static void ScreenTransition_ApplyTarget(ScreenTransition *param0, fx32 param1, fx32 param2)
{
    param0->target.x = param0->baseTarget.x + param1;
    param0->target.y = param0->baseTarget.y + param2;
}

u32 ScreenTransition_GetLoopCount(const ScreenTransition *param0)
{
    return param0->loopCount;
}

fx32 ScreenTransition_GetAmplitude(const ScreenTransition *param0)
{
    return param0->interpX.delta;
}

void ScreenTransition_SetAmplitude(ScreenTransition *param0, fx32 param1)
{
    param0->interpX.delta = param1;
}

void BrightnessFader_Start(BrightnessFader *param0, u32 param1, u32 param2, u32 param3)
{
    if (param0->state != 3) {
        if (param0->task != NULL) {
            SysTask_Done(param0->task);
            param0->task = NULL;
        }
    }

    Interpolator_InitInt(&param0->interpolator, 0, param1, param2);

    param0->timer = 0;
    param0->state = 0;
    param0->duration = param3;
    param0->targetValue = param1;

    GX_SetMasterBrightness(param0->interpolator.value);

    param0->task = SysTask_ExecuteAfterVBlank(BrightnessFader_Task, param0, 1024);
    Sound_PlayEffect(SEQ_SE_DP_CLIMAX06_sseq);
}

int BrightnessFader_GetValue(const BrightnessFader *param0)
{
    return param0->interpolator.value;
}

static void BrightnessFader_Task(SysTask *param0, void *param1)
{
    BrightnessFader *v0 = param1;
    GX_SetMasterBrightness(v0->interpolator.value);
}

ClimaxActorManager *ClimaxActorManager_New(FieldSystem *fieldSystem)
{
    ClimaxActorManager *v0 = Heap_Alloc(HEAP_ID_FIELD1, sizeof(ClimaxActorManager));
    memset(v0, 0, sizeof(ClimaxActorManager));
    v0->fieldSystem = fieldSystem;
    v0->state = 5;

    HeapExp_FndInitAllocator(&v0->allocator, HEAP_ID_FIELD1, 32);

    return v0;
}

void ClimaxActorManager_Free(ClimaxActorManager *param0)
{
    GF_ASSERT(param0->state == 5);
    Heap_Free(param0);
}

void ClimaxActorManager_Draw(ClimaxActorManager *param0)
{
    if ((param0->state == 0) || (param0->state == 4) || (param0->state == 5)) {
        return;
    }

    G3_Identity();
    NNS_G3dGePushMtx();

    {
        Climax3D_ObjectDraw(&param0->actorModel.object);
    }

    NNS_G3dGePopMtx(1);
}

ClimaxObject *ClimaxObject_New(enum HeapID heapID, FieldSystem *fieldSystem)
{
    ClimaxObject *v0 = Heap_Alloc(heapID, sizeof(ClimaxObject));
    memset(v0, 0, sizeof(ClimaxObject));
    v0->fieldSystem = fieldSystem;
    v0->state = 0;
    v0->heapID = heapID;

    HeapExp_FndInitAllocator(&v0->allocator, heapID, 32);
    ClimaxObjectModel_Init(&v0->model, v0->heapID, &v0->allocator);

    {
        BgConfig *v1 = FieldSystem_GetBgConfig(v0->fieldSystem);

        Graphics_LoadTilesToBgLayer(NARC_INDEX_ARC__DEMO_TENGAN_GRA, 74, v1, 2, 0, 0, 0, heapID);
        Graphics_LoadTilemapToBgLayer(NARC_INDEX_ARC__DEMO_TENGAN_GRA, 76, v1, 2, 0, 0, 0, heapID);
        Graphics_LoadPalette(NARC_INDEX_ARC__DEMO_TENGAN_GRA, 75, 0, 0x20 * 6, 0x20, heapID);
        Bg_SetPriority(BG_LAYER_MAIN_2, 1);

        v0->model.blendCoeffA = 0;
        v0->model.blendCoeffB = 31;

        G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, v0->model.blendCoeffA, v0->model.blendCoeffB);
    }

    return v0;
}

void ClimaxObject_Free(ClimaxObject *param0)
{
    ClimaxObjectModel_Free(&param0->model, &param0->allocator);
    Heap_Free(param0);
}

void ClimaxObject_Start(ClimaxObject *param0, u32 param1)
{
    VecFx32 v0;

    ClimaxObjectAnchor_Init(&param0->anchor, param0->fieldSystem, 1);
    MapObject_GetPosPtr(param0->anchor.mapObject, &v0);
    ClimaxObjectModel_Start(&param0->model, v0.x, v0.y, v0.z);
    ClimaxObjectAnchor_Init(&param0->anchor, param0->fieldSystem, param1);
    MapObject_GetPosPtr(param0->anchor.mapObject, &v0);

    param0->state = 1;
}

BOOL ClimaxObject_IsIdle(ClimaxObject *param0)
{
    if ((param0->state == 0) || (param0->state == 5)) {
        return 1;
    }

    return 0;
}

void ClimaxObject_Cleanup(ClimaxObject *param0)
{
    if (ClimaxObject_IsIdle(param0) == 1) {
        return;
    }

    ClimaxObjectModel_Draw(&param0->model);
}

static void ClimaxObjectAnchor_Init(ClimaxObjectAnchor *param0, FieldSystem *fieldSystem, u32 param2)
{
    param0->mapObject = MapObjMan_LocalMapObjByIndex(fieldSystem->mapObjMan, param2);
    GF_ASSERT(param0->mapObject);
    param0->unk_24 = 0;
    param0->unk_28 = 0;
}

static void ClimaxObjectModel_Init(ClimaxObjectModel *param0, enum HeapID heapID, NNSFndAllocator *param2)
{
    int v0;
    NARC *v1 = NARC_ctor(NARC_INDEX_ARC__DEMO_TENGAN_GRA, heapID);

    Climax3D_ModelLoadFrom(&param0->model, v1, 6, heapID);

    for (v0 = 0; v0 < 2; v0++) {
        Climax3D_AnimLoadFrom(&param0->anims[v0], &param0->model, v1, 4 + v0, heapID, param2);
    }

    Climax3D_ObjectInit(&param0->object, &param0->model);

    for (v0 = 0; v0 < 2; v0++) {
        Climax3D_ObjectAddAnim(&param0->object, &param0->anims[v0]);
    }

    Climax3D_ObjectSetVisible(&param0->object, 0);
    NARC_dtor(v1);
}

static void ClimaxObjectModel_Start(ClimaxObjectModel *param0, fx32 param1, fx32 param2, fx32 param3)
{
    int v0;

    Climax3D_ObjectSetPosition(&param0->object, param1, param2, param3);
    Climax3D_ObjectSetScale(&param0->object, FX32_ONE, FX32_ONE, FX32_ONE);

    for (v0 = 0; v0 < 2; v0++) {
        Climax3D_AnimSetFrame(&param0->anims[v0], 0);
    }

    param0->unk_CC = 0;
    param0->unk_B8 = 0;
    param0->unk_D0 = 82;
    param0->unk_D4 = 0;

    Climax3D_ObjectSetVisible(&param0->object, 1);
}

static void ClimaxObjectModel_Free(ClimaxObjectModel *param0, NNSFndAllocator *param1)
{
    int v0;

    Climax3D_ModelRelease(&param0->model);

    for (v0 = 0; v0 < 2; v0++) {
        Climax3D_AnimRelease(&param0->anims[v0], param1);
    }
}

static BOOL ClimaxObjectModel_UpdateBlend(ClimaxObject *param0, int param1, int param2)
{
    BOOL v0 = 0;
    BOOL v1[2] = { 0, 0 };
    ClimaxObjectModel *v2 = &param0->model;

    if (gSystem.pressedKeys & PAD_KEY_UP) {
        v2->blendCoeffA++;
        v2->blendCoeffA %= 32;
    }

    if (gSystem.pressedKeys & PAD_KEY_DOWN) {
        if (v2->blendCoeffA) {
            v2->blendCoeffA--;
        } else {
            v2->blendCoeffA = 31;
        }
    }

    if (gSystem.pressedKeys & PAD_KEY_RIGHT) {
        v2->blendCoeffB++;
        v2->blendCoeffB %= 32;
    }

    if (gSystem.pressedKeys & PAD_KEY_LEFT) {
        if (v2->blendCoeffB) {
            v2->blendCoeffB--;
        } else {
            v2->blendCoeffB = 31;
        }
    }

    switch (param2) {
    case 0:
        if (v2->blendCoeffB > 16) {
            v2->blendCoeffB--;
        } else {
            v1[0] = v1[1] = 1;
        }
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        if (param1) {
            if (v2->blendCoeffA < 8) {
                v2->blendCoeffA++;
            } else {
                v1[0] = 1;
            }

            if (v2->blendCoeffB > 8) {
                v2->blendCoeffB--;
            } else {
                v1[1] = 1;
            }
        } else {
            if (v2->blendCoeffA > 2) {
                v2->blendCoeffA--;
            } else {
                v1[0] = 1;
            }

            if (v2->blendCoeffB < 14) {
                v2->blendCoeffB++;
            } else {
                v1[1] = 1;
            }
        }
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        if (param1) {
            if (v2->blendCoeffA < 8) {
                v2->blendCoeffA++;
            } else {
                v1[0] = 1;
            }

            if (v2->blendCoeffB > 8) {
                v2->blendCoeffB--;
            } else {
                v1[1] = 1;
            }
        } else {
            if (v2->blendCoeffA > 3) {
                v2->blendCoeffA--;
            } else {
                v1[0] = 1;
            }

            if (v2->blendCoeffB < 13) {
                v2->blendCoeffB++;
            } else {
                v1[1] = 1;
            }
        }
        break;
    case 9:
    case 10:
        if (param1) {
            if (v2->blendCoeffA < 8) {
                v2->blendCoeffA++;
            } else {
                v1[0] = 1;
            }

            if (v2->blendCoeffB > 8) {
                v2->blendCoeffB--;
            } else {
                v1[1] = 1;
            }
        } else {
            if (v2->blendCoeffA > 4) {
                v2->blendCoeffA--;
            } else {
                v1[0] = 1;
            }

            if (v2->blendCoeffB < 12) {
                v2->blendCoeffB++;
            } else {
                v1[1] = 1;
            }
        }
        break;
    case 11:
    case 12:
        if (param1) {
            if (v2->blendCoeffA < 8) {
                v2->blendCoeffA++;
            } else {
                v1[0] = 1;
            }

            if (v2->blendCoeffB > 8) {
                v2->blendCoeffB--;
            } else {
                v1[1] = 1;
            }
        } else {
            if (v2->blendCoeffA > 5) {
                v2->blendCoeffA--;
            } else {
                v1[0] = 1;
            }

            if (v2->blendCoeffB < 11) {
                v2->blendCoeffB++;
            } else {
                v1[1] = 1;
            }
        }
        break;
    case 13:
    case 14:
        if (param1) {
            if (v2->blendCoeffA < 8) {
                v2->blendCoeffA++;
            } else {
                v1[0] = 1;
            }

            if (v2->blendCoeffB > 8) {
                v2->blendCoeffB--;
            } else {
                v1[1] = 1;
            }
        } else {
            if (v2->blendCoeffA > 6) {
                v2->blendCoeffA--;
            } else {
                v1[0] = 1;
            }

            if (v2->blendCoeffB < 10) {
                v2->blendCoeffB++;
            } else {
                v1[1] = 1;
            }
        }
        break;
    default:
        if (v2->blendCoeffA > 0) {
            v2->blendCoeffA--;
        } else {
            v1[0] = 1;
        }

        if (v2->blendCoeffB > 0) {
            v2->blendCoeffB--;
        } else {
            v1[1] = 1;
        }
        break;
    }

    G2_ChangeBlendAlpha(v2->blendCoeffA, v2->blendCoeffB);

    if (v1[0] && v1[1]) {
        v0 = 1;
    }

    return v0;
}

static BOOL ClimaxObjectModel_UpdateAnims(ClimaxObject *param0)
{
    int v0;
    BOOL v1;
    ClimaxObjectModel *v2 = &param0->model;

    for (v0 = 0; v0 < 2; v0++) {
        v1 = Climax3D_AnimUpdate(&v2->anims[v0]);
    }

    if (v1) {
        Climax3D_ObjectSetVisible(&v2->object, 0);
    }

    return v1;
}

static void ClimaxObjectModel_Draw(ClimaxObjectModel *param0)
{
    Climax3D_ObjectDraw(&param0->object);
}

static ClimaxParticles *ClimaxParticles_New(enum HeapID heapID, u32 param1)
{
    ClimaxParticles *v0 = Heap_Alloc(heapID, sizeof(ClimaxParticles));
    memset(v0, 0, sizeof(ClimaxParticles));

    Climax3D_ModelLoad(&v0->model, 98, param1, heapID);

    for (int i = 0; i < 3; i++) {
        ClimaxParticle_Init(&v0->particles[i], &v0->model);
    }

    v0->isActive = 0;

    return v0;
}

static void ClimaxParticles_Free(ClimaxParticles *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        ClimaxParticle_Reset(&param0->particles[v0]);
    }

    Climax3D_ModelRelease(&param0->model);
    Heap_Free(param0);
}

static void ClimaxParticles_Start(ClimaxParticles *param0, fx32 param1, fx32 param2, fx32 param3, s32 param4, u16 param5, u16 param6, u16 param7)
{
    GF_ASSERT(param0->isActive == 0);

    param0->spawnTimer = 0;
    param0->x = param1;
    param0->y = param2;
    param0->z = param3;
    param0->rotX = param5;
    param0->rotY = param6;
    param0->rotZ = param7;
    param0->spawnInterval = param4;
    param0->isActive = 1;
}

static void ClimaxParticles_Update(ClimaxParticles *param0)
{
    int v0;
    ClimaxParticle *v1;

    param0->spawnTimer--;

    if (param0->spawnTimer < 0) {
        param0->spawnTimer = param0->spawnInterval;

        v1 = ClimaxParticles_FindFree(param0);
        GF_ASSERT(v1);

        ClimaxParticle_Start(v1, 0, FX32_CONST(16), 96, param0->x, param0->y, param0->z, param0->rotX, param0->rotY, param0->rotZ);
    }

    for (v0 = 0; v0 < 3; v0++) {
        ClimaxParticle_Update(&param0->particles[v0]);
    }
}

static void ClimaxParticles_Draw(ClimaxParticles *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        ClimaxParticle_Draw(&param0->particles[v0]);
    }
}

ClimaxParticles *ClimaxParticles_NewDefault(enum HeapID heapID)
{
    return ClimaxParticles_New(heapID, 6);
}

void ClimaxParticles_Delete(ClimaxParticles *param0)
{
    ClimaxParticles_Free(param0);
}

void ClimaxParticles_SetPosition(ClimaxParticles *param0, u16 param1, u16 param2, u16 param3)
{
    ClimaxParticles_Start(param0, (((param1) << 4) * FX32_ONE) + ((16 * FX32_ONE) >> 1), (((param2) << 4) * FX32_ONE) + ((10 << 4) * FX32_ONE), (((param3) << 4) * FX32_ONE) + ((1 << 4) * FX32_ONE), 64, 0, 0, 0);
}

void ClimaxParticles_UpdatePublic(ClimaxParticles *param0)
{
    ClimaxParticles_Update(param0);
}

void ClimaxParticles_DrawPublic(ClimaxParticles *param0)
{
    ClimaxParticles_Draw(param0);
}

static void ClimaxParticle_Init(ClimaxParticle *param0, Easy3DModel *param1)
{
    memset(param0, 0, sizeof(ClimaxParticle));

    Climax3D_ObjectInit(&param0->object, param1);
    Climax3D_ObjectSetVisible(&param0->object, 0);

    param0->isActive = 0;
}

static void ClimaxParticle_Reset(ClimaxParticle *param0)
{
    memset(param0, 0, sizeof(ClimaxParticle));
}

static void ClimaxParticle_Start(ClimaxParticle *param0, fx32 param1, fx32 param2, int param3, fx32 param4, fx32 param5, fx32 param6, u16 param7, u16 param8, u16 param9)
{
    GF_ASSERT(param0->isActive == 0);

    Interpolator_Init(&param0->interpolator, param1, param2, param3);
    Climax3D_ObjectSetVisible(&param0->object, 1);
    Climax3D_ObjectSetPosition(&param0->object, param4, param5, param6);
    Climax3D_ObjectSetScale(&param0->object, param1, FX32_ONE, param1);
    Climax3D_ObjectSetRotation(&param0->object, param7, 0);
    Climax3D_ObjectSetRotation(&param0->object, param8, 1);
    Climax3D_ObjectSetRotation(&param0->object, param9, 2);

    param0->isActive = 1;
    param0->timer = 0;
}

static void ClimaxParticle_Update(ClimaxParticle *param0)
{
    BOOL v0;

    if (param0->isActive == 0) {
        return;
    }

    param0->timer++;
    v0 = Interpolator_Update(&param0->interpolator, param0->timer);

    Climax3D_ObjectSetScale(&param0->object, param0->interpolator.value, FX32_ONE, param0->interpolator.value);

    if (v0 == 1) {
        param0->isActive = 0;
    }
}

static void ClimaxParticle_Draw(ClimaxParticle *param0)
{
    Climax3D_ObjectDraw(&param0->object);
}

static ClimaxParticle *ClimaxParticles_FindFree(ClimaxParticles *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        if (param0->particles[v0].isActive == 0) {
            return &param0->particles[v0];
        }
    }

    return NULL;
}

static ClimaxGlow *ClimaxGlow_New(enum HeapID heapID, u32 param1)
{
    ClimaxGlow *v0;
    int v1;
    NARC *v2;

    v0 = Heap_Alloc(heapID, sizeof(ClimaxGlow));
    memset(v0, 0, sizeof(ClimaxGlow));

    HeapExp_FndInitAllocator(&v0->allocator, heapID, 32);
    v2 = NARC_ctor(NARC_INDEX_DATA__DEMO_CLIMAX, heapID);
    Climax3D_ModelLoadFrom(&v0->model, v2, param1, heapID);

    for (v1 = 0; v1 < 3; v1++) {
        Climax3D_AnimLoadFrom(&v0->anims[v1], &v0->model, v2, 1 + v1, heapID, &v0->allocator);
    }

    Climax3D_ObjectInit(&v0->object, &v0->model);

    for (v1 = 0; v1 < 3; v1++) {
        Climax3D_ObjectAddAnim(&v0->object, &v0->anims[v1]);
    }

    Climax3D_ObjectSetVisible(&v0->object, 0);
    NARC_dtor(v2);

    return v0;
}

static void ClimaxGlow_Free(ClimaxGlow *param0)
{
    int v0;

    Climax3D_ModelRelease(&param0->model);

    for (v0 = 0; v0 < 3; v0++) {
        Climax3D_AnimRelease(&param0->anims[v0], &param0->allocator);
    }

    Heap_Free(param0);
}

static void ClimaxGlow_SetPosition(ClimaxGlow *param0, fx32 param1, fx32 param2, fx32 param3, u16 param4, u16 param5, u16 param6)
{
    Climax3D_ObjectSetPosition(&param0->object, param1, param2, param3);
    Climax3D_ObjectSetRotation(&param0->object, param4, 0);
    Climax3D_ObjectSetRotation(&param0->object, param6, 2);
    Climax3D_ObjectSetRotation(&param0->object, param5, 1);
    Climax3D_ObjectSetVisible(&param0->object, 1);
}

static void ClimaxGlow_Update(ClimaxGlow *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Climax3D_AnimUpdateLooped(&param0->anims[v0]);
    }
}

static void ClimaxGlow_Draw(ClimaxGlow *param0)
{
    Climax3D_ObjectDraw(&param0->object);
}

ClimaxGlow *ClimaxGlow_NewDefault(enum HeapID heapID)
{
    return ClimaxGlow_New(heapID, 0);
}

void ClimaxGlow_Delete(ClimaxGlow *param0)
{
    ClimaxGlow_Free(param0);
}

void ClimaxGlow_UpdatePublic(ClimaxGlow *param0)
{
    VecFx32 v0;
    ClimaxGlow_Update(param0);
}

void ClimaxGlow_DrawPublic(ClimaxGlow *param0)
{
    ClimaxGlow_Draw(param0);
}

void ClimaxGlow_SetPositionVariant0(ClimaxGlow *param0, fx32 param1, fx32 param2, fx32 param3)
{
    ClimaxGlow_SetPosition(param0, param1 + 170920, param2 + -225940, param3 + -747638, 62623, 32949, 32942);
}

void ClimaxGlow_SetPositionVariant1(ClimaxGlow *param0, fx32 param1, fx32 param2, fx32 param3)
{
    ClimaxGlow_SetPosition(param0, param1 + 1141327, param2 + 323947, param3 + -598296, 58801, 49507, 32760);
}

void ClimaxGlow_SetPositionVariant2(ClimaxGlow *param0, fx32 param1, fx32 param2, fx32 param3)
{
    ClimaxGlow_SetPosition(param0, param1 + -811008, param2 + 356351, param3 + -2162696, 59165, 21301, 31122);
}

ClimaxParticles *ClimaxParticles_NewDefault2(enum HeapID heapID)
{
    return ClimaxParticles_New(heapID, 6);
}

void ClimaxParticles_Delete2(ClimaxParticles *param0)
{
    ClimaxParticles_Free(param0);
}

void ClimaxParticles_Update2(ClimaxParticles *param0)
{
    ClimaxParticles_Update(param0);
}

void ClimaxParticles_Draw2(ClimaxParticles *param0)
{
    ClimaxParticles_Draw(param0);
}

void ClimaxParticles_SetPositionVariant0(ClimaxParticles *param0, fx32 param1, fx32 param2, fx32 param3)
{
    ClimaxParticles_Start(param0, param1 + 0x11000, param2 + 0xfff91000, param3 + 0xfff35000, 64, 62623, 32949, 32942);
}

void ClimaxParticles_SetPositionVariant1(ClimaxParticles *param0, fx32 param1, fx32 param2, fx32 param3)
{
    ClimaxParticles_Start(param0, param1 + 0x252000, param2 + 0x43000, param3 + 0xfffc8000, 64, 58801, 49507, 32760);
}

void ClimaxParticles_SetPositionVariant2(ClimaxParticles *param0, fx32 param1, fx32 param2, fx32 param3)
{
    ClimaxParticles_Start(param0, param1 + 0xffeb4000, param2 + 0xffff3000, param3 + 0xffe3c000, 64, 59165, 21301, 31122);
}

static const AreaLightTemplate sClimaxAreaLightTemplates[3] = {
    {
        8,
        0xD,
        {
            GX_RGB(13, 11, 11),
            GX_RGB(0, 0, 0),
            GX_RGB(10, 3, 0),
            GX_RGB(31, 31, 31),
        },
        {
            { -2022, -3561, 93 },
            { 0, 0, 4096 },
            { 0, 0, 4096 },
            { 0, 0, 4096 },
        },
        GX_RGB(13, 13, 14),
        GX_RGB(13, 12, 12),
        GX_RGB(13, 11, 14),
        GX_RGB(11, 9, 10),
    },
    {
        16,
        0xD,
        {
            GX_RGB(11, 9, 9),
            GX_RGB(0, 0, 0),
            GX_RGB(10, 3, 0),
            GX_RGB(31, 31, 31),
        },
        {
            { -2022, -3561, 93 },
            { 0, 0, 4096 },
            { 0, 0, 4096 },
            { 0, 0, 4096 },
        },
        GX_RGB(11, 11, 12),
        GX_RGB(13, 12, 12),
        GX_RGB(13, 11, 14),
        GX_RGB(11, 9, 10),
    },
    {
        24,
        0xD,
        {
            GX_RGB(9, 8, 8),
            GX_RGB(0, 0, 0),
            GX_RGB(10, 3, 0),
            GX_RGB(31, 31, 31),
        },
        {
            { -2022, -3561, 93 },
            { 0, 0, 4096 },
            { 0, 0, 4096 },
            { 0, 0, 4096 },
        },
        GX_RGB(10, 9, 9),
        GX_RGB(11, 10, 10),
        GX_RGB(13, 11, 14),
        GX_RGB(11, 9, 10),
    },
};

void include_unk_sClimaxAreaLightTemplates(void)
{
    sClimaxAreaLightTemplates[0];
}

ClimaxFlash *ClimaxFlash_New(enum HeapID heapID, FieldSystem *fieldSystem)
{
    ClimaxFlash *v0;
    int v1;
    NARC *v2;

    v0 = Heap_Alloc(heapID, sizeof(ClimaxFlash));
    memset(v0, 0, sizeof(ClimaxFlash));

    v2 = NARC_ctor(NARC_INDEX_DATA__DEMO_CLIMAX, heapID);
    v0->fieldSystem = fieldSystem;

    HeapExp_FndInitAllocator(&v0->allocator, heapID, 32);
    Climax3D_ModelLoadFrom(&v0->model, v2, 15, heapID);

    for (v1 = 0; v1 < 4; v1++) {
        Climax3D_AnimLoadFrom(&v0->anims[v1], &v0->model, v2, 16 + v1, heapID, &v0->allocator);
    }

    Climax3D_ObjectInit(&v0->object, &v0->model);

    for (v1 = 0; v1 < 4; v1++) {
        Climax3D_ObjectAddAnim(&v0->object, &v0->anims[v1]);
    }

    Climax3D_ObjectSetVisible(&v0->object, 0);
    NARC_dtor(v2);

    return v0;
}

void ClimaxFlash_Start(ClimaxFlash *param0, u32 param1)
{
    VecFx32 v0;
    MapObject *v1 = MapObjMan_LocalMapObjByIndex(param0->fieldSystem->mapObjMan, param1);

    MapObject_GetPosPtr(v1, &v0);

    Climax3D_ObjectSetPosition(&param0->object, v0.x, v0.y, v0.z);
    Climax3D_ObjectSetVisible(&param0->object, 1);

    Sound_PlayEffect(SEQ_SE_DP_CLIMAX15_sseq);
}

BOOL ClimaxFlash_IsFinished(ClimaxFlash *param0)
{
    int v0;
    BOOL v1;

    for (v0 = 0; v0 < 4; v0++) {
        v1 = Climax3D_AnimUpdate(&param0->anims[v0]);
    }

    return v1;
}

void ClimaxFlash_Draw(ClimaxFlash *param0)
{
    Climax3D_ObjectDraw(&param0->object);
}
