#include "footprint_stamp/footprint_stamp_models.h"

#include <nitro.h>
#include <string.h>

#include "constants/species.h"

#include "footprint_stamp/footprint_stamp_players.h"
#include "footprint_stamp/struct_footprint_stamp_app_decl.h"
#include "footprint_stamp/struct_footprint_stamp_model_manager.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_data.h"
#include "footprint_stamp/struct_footprint_stamp_slot.h"
#include "footprint_stamp/struct_footprint_stamp_fade.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_zoom_in.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_shake.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_rotate_left.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_rotate_right.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_tilt_up.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_spin.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_zoom_out.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_sway_x.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_sway_y.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_tilt_down.h"
#include "footprint_stamp/struct_footprint_stamp_entry.h"

#include "camera.h"
#include "easy3d.h"
#include "easy3d_object.h"
#include "graphics.h"
#include "heap.h"
#include "math_util.h"
#include "narc.h"
#include "pokemon.h"
#include "screen_fade.h"
#include "sound_playback.h"

__attribute__((aligned(4))) static const s16 sSlotThresholds[] = {
    0xFF,
    0xA,
    0xA,
    0xA,
    0xA,
    0xA,
    0xA,
    0xA,
    0xA
};

typedef int (*FootprintStampAnimInitFunc)(FootprintStampModelManager *, FootprintStampModel *);
typedef void (*FootprintStampAnimDrawFunc)(FootprintStampModelManager *, FootprintStampModel *);
typedef BOOL (*FootprintStampAnimCollideFunc)(FootprintStampModelManager *, FootprintStampModel *, FootprintStampModel *);
typedef BOOL (*FootprintStampCameraAnimFunc)(FootprintStampModelManager *, FootprintStampCameraAnimData *, Camera *);

typedef struct {
    FootprintStampAnimInitFunc update; // Advances the animation; returns 1 when it finishes.
    FootprintStampAnimDrawFunc draw; // Optional custom draw callback.
    FootprintStampAnimCollideFunc collide; // Tests overlap against another model.
} FootprintStampAnimHandler;

typedef struct {
    fx32 minX; // Minimum X.
    fx32 maxX; // Maximum X.
    fx32 maxY; // Maximum Y.
    fx32 minY; // Minimum Y.
} FootprintStampBounds;

typedef struct {
    s32 timer;
    FootprintStampBounds bounds;
} FootprintStampAnimAppear;

typedef struct {
    int alpha;
    fx32 scale;
    u8 state;
    u8 slot;
    FootprintStampBounds bounds;
} FootprintStampAnimGrow;

typedef struct {
    Easy3DObject pieces[3];
    u16 timer;
    u8 state;
    FootprintStampBounds bounds[4];
} FootprintStampAnimSplit;

typedef struct {
    int state;
    int step;
    int moveStep;
    FootprintStampBounds bounds;
} FootprintStampAnimSpin;

typedef struct {
    int state;
    fx32 angle;
    int step;
    fx32 baseY;
    FootprintStampBounds bounds;
} FootprintStampAnimBounce;

typedef struct {
    Easy3DObject pieces[3];
    u16 timer;
    u8 trailIndex;
    u8 stopFlag;
    u8 slot;
    u8 state;
    FootprintStampBounds bounds;
} FootprintStampAnimTrail;

typedef struct {
    int state;
    fx32 angle;
    fx32 baseX;
    FootprintStampBounds bounds;
} FootprintStampAnimSwing;

typedef struct {
    fx32 scale;
    u16 step;
    u8 state;
    FootprintStampBounds bounds;
} FootprintStampAnimPulse;

typedef struct {
    Easy3DObject pieces[2];
    fx32 angle;
    u16 alpha;
    u8 slot;
    u8 state;
    FootprintStampBounds bounds[3];
} FootprintStampAnimSplitX;

typedef struct {
    Easy3DObject pieces[2];
    fx32 angle;
    u16 alpha;
    u8 slot;
    u8 state;
    FootprintStampBounds bounds[3];
} FootprintStampAnimSplitY;

typedef struct {
    fx32 scale;
    u16 step;
    u8 state;
    FootprintStampBounds bounds;
} FootprintStampAnimStretch;

typedef union {
    FootprintStampAnimAppear val1;
    FootprintStampAnimGrow val2;
    FootprintStampAnimSplit val3;
    FootprintStampAnimSpin val4;
    FootprintStampAnimBounce val5;
    FootprintStampAnimTrail val6;
    FootprintStampAnimSwing val7;
    FootprintStampAnimPulse val8;
    FootprintStampAnimSplitX val9;
    FootprintStampAnimSplitY val10;
    FootprintStampAnimStretch val11;
} FootprintStampModelAnimData;

typedef struct FootprintStampModel_t {
    FootprintStampEntry entry; // The footprint entry this model represents.
    Easy3DModel model;
    Easy3DObject object;
    FootprintStampModelAnimData animData; // Per-animation scratch data.
    u32 appeared : 4; // Whether the model has finished appearing.
    u32 textureRotated : 4; // Whether the texture is currently rotated.
    u32 animState : 8; // Current animation state index.
    u32 requestedAnim : 8; // Animation state requested to start.
    u32 slot : 8; // Slot index assigned to this model.
} FootprintStampModel;

static FootprintStampModel *FootprintStampModels_CreateModel(FootprintStampApp *param0, FootprintStampModelManager *param1, const FootprintStampEntry *param2, NARC *param3, NARC *param4, BOOL param5);
static void FootprintStampModels_FreeModel(FootprintStampModel *param0);
static void FootprintStampModels_RemoveModel(FootprintStampModelManager *param0, FootprintStampModel *param1, int param2);
static void FootprintStampModels_GetBoardPosition(FootprintStampApp *param0, int param1, int param2, fx32 *param3, fx32 *param4);
static BOOL FootprintStampModels_LoadModel(FootprintStampModelManager *param0, Easy3DModel *param1, NARC *param2, NARC *param3, const FootprintStampEntry *param4, BOOL param5);
static void FootprintStampModels_BuildFootprintTexture(NNSG3dResTex *param0, NARC *param1, NARC *param2, const FootprintStampEntry *param3, BOOL param4);
static void FootprintStampModels_RotateTexture(NNSG3dResTex *param0, int param1);
static BOOL FootprintStampModels_AllocTextureVram(NNSG3dResTex *param0);
static BOOL FootprintStampModels_AddTexture(FootprintStampModelManager *param0, NNSG3dResTex *param1);
static void FootprintStampModels_RemoveTexture(FootprintStampModelManager *param0, NNSG3dResTex *param1);
static BOOL FootprintStampModels_StartModelAnim(FootprintStampModel *param0, int param1);
static u8 FootprintStampModels_GetNatureAnim(const FootprintStampEntry *param0);
static int FootprintStampModels_AllocSlot(FootprintStampModelManager *param0);
static void FootprintStampModels_FreeSlot(FootprintStampModelManager *param0, int param1);
static void FootprintStampModels_ComputeBounds(Easy3DObject *param0, const FootprintStampEntry *param1, FootprintStampBounds *param2, int param3);
static BOOL FootprintStampModels_BoundsOverlap(const FootprintStampBounds *param0, const FootprintStampBounds *param1);
static void FootprintStampModels_AssignSlot(FootprintStampModelManager *param0, FootprintStampModel *param1);
static int FootprintStampModels_CountSlot(FootprintStampModelManager *param0, int param1, int param2);
static void FootprintStampModels_ReleaseSlot(FootprintStampModelManager *param0, int param1);
static void FootprintStampModels_StartCameraAnim(FootprintStampModelManager *param0);
static BOOL FootprintStampModels_UpdateFade(FootprintStampModelManager *param0, FootprintStampFade *param1, int param2, int param3);
static int FootprintStampAnim_Appear(FootprintStampModelManager *param0, FootprintStampModel *param1);
static int FootprintStampAnim_Grow(FootprintStampModelManager *param0, FootprintStampModel *param1);
static int FootprintStampAnim_Split(FootprintStampModelManager *param0, FootprintStampModel *param1);
static int FootprintStampAnim_Spin(FootprintStampModelManager *param0, FootprintStampModel *param1);
static int FootprintStampAnim_Bounce(FootprintStampModelManager *param0, FootprintStampModel *param1);
static int FootprintStampAnim_Trail(FootprintStampModelManager *param0, FootprintStampModel *param1);
static int FootprintStampAnim_Swing(FootprintStampModelManager *param0, FootprintStampModel *param1);
static int FootprintStampAnim_Pulse(FootprintStampModelManager *param0, FootprintStampModel *param1);
static int FootprintStampAnim_SplitX(FootprintStampModelManager *param0, FootprintStampModel *param1);
static int FootprintStampAnim_SplitY(FootprintStampModelManager *param0, FootprintStampModel *param1);
static int FootprintStampAnim_Stretch(FootprintStampModelManager *param0, FootprintStampModel *param1);
static void FootprintStampAnim_GrowDraw(FootprintStampModelManager *param0, FootprintStampModel *param1);
static void FootprintStampAnim_SplitDraw(FootprintStampModelManager *param0, FootprintStampModel *param1);
static void FootprintStampAnim_TrailDraw(FootprintStampModelManager *param0, FootprintStampModel *param1);
static void FootprintStampAnim_SplitXDraw(FootprintStampModelManager *param0, FootprintStampModel *param1);
static void FootprintStampAnim_SplitYDraw(FootprintStampModelManager *param0, FootprintStampModel *param1);
static BOOL FootprintStampAnim_AppearCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2);
static BOOL FootprintStampAnim_GrowCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2);
static BOOL FootprintStampAnim_SplitCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2);
static BOOL FootprintStampAnim_SpinCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2);
static BOOL FootprintStampAnim_BounceCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2);
static BOOL FootprintStampAnim_TrailCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2);
static BOOL FootprintStampAnim_SwingCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2);
static BOOL FootprintStampAnim_PulseCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2);
static BOOL FootprintStampAnim_SplitXCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2);
static BOOL FootprintStampAnim_SplitYCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2);
static BOOL FootprintStampAnim_StretchCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2);
static BOOL FootprintStampCameraAnim_ZoomIn(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera);
static BOOL FootprintStampCameraAnim_Shake(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera);
static BOOL FootprintStampCameraAnim_RotateLeft(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera);
static BOOL FootprintStampCameraAnim_RotateRight(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera);
static BOOL FootprintStampCameraAnim_TiltUp(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera);
static BOOL FootprintStampCameraAnim_Spin(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera);
static BOOL FootprintStampCameraAnim_ZoomOut(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera);
static BOOL FootprintStampCameraAnim_SwayX(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera);
static BOOL FootprintStampCameraAnim_SwayY(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera);
static BOOL FootprintStampCameraAnim_TiltDown(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera);

static const struct {
    fx32 minX;
    fx32 maxX;
    fx32 maxY;
    fx32 minY;
} sBoardBounds = {
    -FX32_ONE * 16 * (5 + 0),
    FX32_ONE * 16 * (5 + 0),
    FX32_ONE * 16 * (3 + 0),
    -FX32_ONE * 16 * (3 + 0),
};

static const FootprintStampAnimHandler sAnimHandlers[] = {
    { FootprintStampAnim_Appear, NULL, FootprintStampAnim_AppearCollide },
    { FootprintStampAnim_Grow, FootprintStampAnim_GrowDraw, FootprintStampAnim_GrowCollide },
    { FootprintStampAnim_Split, FootprintStampAnim_SplitDraw, FootprintStampAnim_SplitCollide },
    { FootprintStampAnim_Spin, NULL, FootprintStampAnim_SpinCollide },
    { FootprintStampAnim_Bounce, NULL, FootprintStampAnim_BounceCollide },
    { FootprintStampAnim_Trail, FootprintStampAnim_TrailDraw, FootprintStampAnim_TrailCollide },
    { FootprintStampAnim_Swing, NULL, FootprintStampAnim_SwingCollide },
    { FootprintStampAnim_Pulse, NULL, FootprintStampAnim_PulseCollide },
    { FootprintStampAnim_SplitX, FootprintStampAnim_SplitXDraw, FootprintStampAnim_SplitXCollide },
    { FootprintStampAnim_SplitY, FootprintStampAnim_SplitYDraw, FootprintStampAnim_SplitYCollide },
    { FootprintStampAnim_Stretch, NULL, FootprintStampAnim_StretchCollide }
};

__attribute__((aligned(4))) static const u8 sNatureToAnim[] = {
    0x5,
    0x1,
    0x5,
    0x6,
    0x6,
    0x4,
    0x3,
    0x9,
    0x7,
    0x8,
    0x1,
    0x5,
    0x3,
    0x8,
    0x2,
    0xA,
    0x4,
    0x3,
    0x9,
    0x7,
    0xA,
    0x4,
    0x6,
    0x1,
    0x2
};

static const FootprintStampBounds sFootprintSizeBounds[] = {
    { -(((FX32_ONE * 16 * 1) / 2) / 3),
        ((FX32_ONE * 16 * 1) / 2) / 3,
        ((FX32_ONE * 16 * 1) / 2) / 3,
        -(((FX32_ONE * 16 * 1) / 2) / 3) },
    { -(((FX32_ONE * 16 * 1) / 2) / 2),
        ((FX32_ONE * 16 * 1) / 2) / 2,
        ((FX32_ONE * 16 * 1) / 2) / 2,
        -(((FX32_ONE * 16 * 1) / 2) / 2) },
    { -(((FX32_ONE * 16 * 1) / 2) / 3 * 2),
        ((FX32_ONE * 16 * 1) / 2) / 3 * 2,
        ((FX32_ONE * 16 * 1) / 2) / 3 * 2,
        -(((FX32_ONE * 16 * 1) / 2) / 3 * 2) }
};

static const FootprintStampCameraAnimFunc sCameraAnimHandlers[] = {
    NULL,
    FootprintStampCameraAnim_ZoomIn,
    FootprintStampCameraAnim_Shake,
    FootprintStampCameraAnim_RotateLeft,
    FootprintStampCameraAnim_RotateRight,
    FootprintStampCameraAnim_TiltUp,
    FootprintStampCameraAnim_Spin,
    FootprintStampCameraAnim_ZoomOut,
    FootprintStampCameraAnim_SwayX,
    FootprintStampCameraAnim_SwayY,
    FootprintStampCameraAnim_TiltDown
};

static const s32 sBoardXPositions[] = {
    0xFFFFFFFFFFFC5E04,
    0xFFFFFFFFFFFCCE04,
    0xFFFFFFFFFFFD3E04,
    0xFFFFFFFFFFFDB604,
    0xFFFFFFFFFFFE2604,
    0xFFFFFFFFFFFE9E04,
    0xFFFFFFFFFFFF0E04,
    0xFFFFFFFFFFFF8604,
    0xFFFFFFFFFFFFFC04,
    0x7004,
    0xE004,
    0x15804,
    0x1C804,
    0x24004,
    0x2B004,
    0x32804,
    0x39804
};

static const s32 sBoardYPositions[] = {
    0x23B0F,
    0x1CB0F,
    0x1550F,
    0xE10F,
    0x6D0F,
    0xFFFFFFFFFFFFF70F,
    0xFFFFFFFFFFFF830F,
    0xFFFFFFFFFFFF0F0F,
    0xFFFFFFFFFFFE9B0F,
    0xFFFFFFFFFFFE270F,
    0xFFFFFFFFFFFDB70F
};

void FootprintStampModels_Init(FootprintStampModelManager *param0, BOOL param1)
{
    MI_CpuClear8(param0, sizeof(FootprintStampModelManager));
}

void FootprintStampModels_Free(FootprintStampModelManager *param0)
{
    int v0;

    for (v0 = 0; v0 < 128; v0++) {
        if (param0->models[v0] != NULL) {
            FootprintStampModels_FreeModel(param0->models[v0]);
        }
    }
}

BOOL FootprintStampModels_Add(FootprintStampApp *param0, FootprintStampModelManager *param1, const FootprintStampEntry *param2, NARC *param3, NARC *param4, BOOL param5)
{
    int v0;

    if (param1->cameraAnimState != 0) {
        return 0;
    }

    for (v0 = 0; v0 < 128; v0++) {
        if (param1->models[v0] == NULL) {
            param1->models[v0] = FootprintStampModels_CreateModel(param0, param1, param2, param3, param4, param5);

            if (param1->models[v0] == NULL) {
                return 0;
            }

            return 1;
        }
    }

    return 0;
}

void FootprintStampModels_Update(FootprintStampModelManager *param0, Camera *camera, int param2, int param3)
{
    int v0;
    FootprintStampModel *v1;
    int v2;
    BOOL v3;

    if (param0->pendingCameraAnim != 0) {
        FootprintStampModels_UpdateFade(param0, &param0->fade, param2, param3);
    }

    if (param0->cameraAnimState != 0) {
        if (sCameraAnimHandlers[param0->cameraAnimState](param0, &param0->cameraAnim, camera) == 1) {
            param0->cameraAnimState = 0;
        }
    }

    for (v0 = 0; v0 < 128; v0++) {
        v1 = param0->models[v0];

        if (v1 != NULL) {
            if ((v1->animState == 0) && (v1->requestedAnim != 0)) {
                v1->animState = v1->requestedAnim;
            }

            v2 = sAnimHandlers[v1->animState].update(param0, v1);

            switch (v2) {
            case 1:
                FootprintStampModels_RemoveModel(param0, v1, v0);
                break;
            }
        }

        v1++;
    }
}

void FootprintStampModels_Draw(FootprintStampModelManager *param0)
{
    int v0;
    FootprintStampModel *v1;

    for (v0 = 0; v0 < 128; v0++) {
        v1 = param0->models[v0];

        if (v1 != NULL) {
            if (sAnimHandlers[v1->animState].draw != NULL) {
                sAnimHandlers[v1->animState].draw(param0, v1);
            } else {
                Easy3DObject_Draw(&v1->object);
            }
        }
    }
}

void FootprintStampModels_UpdateAnimations(FootprintStampModelManager *param0)
{
    int v0, v1, v2, v3, v4;
    FootprintStampModel *v5;
    FootprintStampModel *v6;
    BOOL v7;
    int v8 = 0;

    v1 = 0;
    v2 = 0;

    for (v0 = 0; v0 < 128; v0++) {
        v5 = param0->models[v0];

        if (v5 != NULL) {
            if (v5->animState != 0) {
                param0->sortedModels[v1] = v5;
                v1++;
            } else {
                param0->sortedModels[128 - 1 - v2] = v5;
                v2++;
            }
        }
    }

    for (v4 = 0; v4 < v2; v4++) {
        v6 = param0->sortedModels[128 - 1 - v4];

        for (v3 = 0; v3 < v1; v3++) {
            v5 = param0->sortedModels[v3];

            if (sAnimHandlers[v5->animState].collide(param0, v5, v6) == 1) {
                v7 = FootprintStampModels_StartModelAnim(v6, v5->animState);

                if ((v7 == 1) && (v6->slot == 0xff)) {
                    v6->slot = v5->slot;

                    if (FootprintStampModels_CountSlot(param0, v5->slot, v5->animState) == 1) {
                        v8++;
                    }

                    break;
                }
            }
        }
    }

    if ((param0->pendingCameraAnim != 0) && (param0->cameraAnimFinished == 1)) {
        for (v0 = 0; v0 < 128; v0++) {
            v5 = param0->models[v0];

            if ((v5 != NULL) && (v5->animState != param0->pendingCameraAnim) && (v5->requestedAnim != param0->pendingCameraAnim)) {
                if (FootprintStampModels_StartModelAnim(v5, param0->pendingCameraAnim) == 0) {
                    FootprintStampModels_RemoveModel(param0, v5, v0);
                }
            }
        }

        FootprintStampModels_StartCameraAnim(param0);
    }
}

void FootprintStampModels_FlushTextures(FootprintStampModelManager *param0, int param1)
{
    int v0;
    NNSG3dResTex **v1;

    v1 = param0->pendingTextures;

    for (v0 = 0; v0 < 32; v0++) {
        if (*v1 != NULL) {
            DC_FlushRange(*v1, (*v1)->header.size);

            NNS_G3dTexLoad(*v1, 1);
            NNS_G3dPlttLoad(*v1, 1);

            *v1 = NULL;
        }

        v1++;
    }

    if (param0->isBrightnessPending && (param1 != 3)) {
        SetScreenMasterBrightness(DS_SCREEN_MAIN, param0->brightness);
        param0->isBrightnessPending = 0;
    }
}

static FootprintStampModel *FootprintStampModels_CreateModel(FootprintStampApp *param0, FootprintStampModelManager *param1, const FootprintStampEntry *param2, NARC *param3, NARC *param4, BOOL param5)
{
    FootprintStampModel *v0;
    fx32 v1, v2;
    BOOL v3;

    v0 = Heap_Alloc(HEAP_ID_118, sizeof(FootprintStampModel));
    MI_CpuClear8(v0, sizeof(FootprintStampModel));

    v0->slot = 0xff;
    v0->entry = *param2;

    if (v0->entry.species > NATIONAL_DEX_COUNT) {
        GF_ASSERT(FALSE);
        v0->entry.species = 132;
    }

    v3 = FootprintStampModels_LoadModel(param1, &v0->model, param3, param4, &v0->entry, param5);

    if (v3 == 0) {
        return NULL;
    }

    Easy3DObject_Init(&v0->object, &v0->model);
    FootprintStampModels_GetBoardPosition(param0, param2->touchX, param2->touchY, &v1, &v2);
    Easy3DObject_SetPosition(&v0->object, v1, v2, (FX32_ONE * 16));
    Easy3DObject_SetScale(&v0->object, (FX32_CONST(1.00f)), (FX32_CONST(1.00f)), (FX32_CONST(1.00f)));
    Easy3DObject_SetVisible(&v0->object, 0);

    return v0;
}

static BOOL FootprintStampModels_LoadModel(FootprintStampModelManager *param0, Easy3DModel *param1, NARC *param2, NARC *param3, const FootprintStampEntry *param4, BOOL param5)
{
    param1->data = LoadMemberFromOpenNARC(param2, 29, 0, HEAP_ID_118, 0);

    {
        BOOL v0;

        GF_ASSERT(param1->data);

        param1->set = NNS_G3dGetMdlSet(param1->data);
        param1->model = NNS_G3dGetMdlByIdx(param1->set, 0);
        param1->texture = NNS_G3dGetTex(param1->data);

        if (param1->texture) {
            FootprintStampModels_BuildFootprintTexture(param1->texture, param2, param3, param4, param5);
            v0 = FootprintStampModels_AllocTextureVram(param1->texture);

            if ((v0 == 0) || (FootprintStampModels_AddTexture(param0, param1->texture) == 0)) {
                NNSG3dTexKey v1;
                NNSG3dTexKey v2;
                NNSG3dPlttKey v3;

                if (v0 == 1) {
                    NNS_G3dTexReleaseTexKey(param1->texture, &v1, &v2);
                    NNS_GfdFreeTexVram(v1);
                    NNS_GfdFreeTexVram(v2);
                    v3 = NNS_G3dPlttReleasePlttKey(param1->texture);
                    NNS_GfdFreePlttVram(v3);
                }

                if (param1->data) {
                    Heap_Free(param1->data);
                }

                memset(param1, 0, sizeof(Easy3DModel));
                return 0;
            }

            Easy3D_BindTextureToResource(param1->data, param1->texture);
        }
    }

    return 1;
}

static BOOL FootprintStampModels_AddTexture(FootprintStampModelManager *param0, NNSG3dResTex *param1)
{
    int v0;

    for (v0 = 0; v0 < 32; v0++) {
        if (param0->pendingTextures[v0] == NULL) {
            param0->pendingTextures[v0] = param1;
            return 1;
        }
    }

    return 0;
}

static void FootprintStampModels_RemoveTexture(FootprintStampModelManager *param0, NNSG3dResTex *param1)
{
    int v0;

    for (v0 = 0; v0 < 32; v0++) {
        if (param0->pendingTextures[v0] == param1) {
            param0->pendingTextures[v0] = NULL;
            return;
        }
    }
}

static BOOL FootprintStampModels_AllocTextureVram(NNSG3dResTex *param0)
{
    u32 v0, v1;
    NNSG3dTexKey v2;
    NNSG3dPlttKey v3;

    param0->texInfo.vramKey = 0;

    v0 = NNS_G3dTexGetRequiredSize(param0);
    v1 = NNS_G3dPlttGetRequiredSize(param0);
    v2 = NNS_GfdAllocTexVram(v0, 0, 0);

    if (v2 == NNS_GFD_ALLOC_ERROR_TEXKEY) {
        return 0;
    }

    v3 = NNS_GfdAllocPlttVram(v1, param0->tex4x4Info.flag & NNS_G3D_RESPLTT_USEPLTT4, 0);

    if (v3 == NNS_GFD_ALLOC_ERROR_PLTTKEY) {
        NNS_GfdFreeTexVram(v2);
        return 0;
    }

    NNS_G3dTexSetTexKey(param0, v2, 0);
    NNS_G3dPlttSetPlttKey(param0, v3);

    return 1;
}

static void FootprintStampModels_BuildFootprintTexture(NNSG3dResTex *param0, NARC *param1, NARC *param2, const FootprintStampEntry *param3, BOOL param4)
{
    u16 *v0;
    u8 *v1, *v2;
    NNSG2dCharacterData *v3;
    int v4 = PokemonHasOverworldFootprint(param3->species, param3->form, param4);
    v1 = (u8 *)((u8 *)param0 + param0->texInfo.ofsTex);

    if (v4 == 1) {
        v2 = LoadMemberFromOpenNARC(param2, 3 + param3->species, 1, HEAP_ID_118, 1);
        NNS_G2dGetUnpackedCharacterData(v2, &v3);
    } else {
        v2 = LoadMemberFromOpenNARC(param1, 16, 0, HEAP_ID_118, 1);
        NNS_G2dGetUnpackedCharacterData(v2, &v3);
    }

    MI_CpuClear16(v1, (16 * 16 / 4));

    {
        int v5, v6, v7, v8, v9, v10;
        u8 *v11, *v12;
        u16 *v13;

        v11 = v3->pRawData;
        v12 = v11;
        v13 = (u16 *)v1;

        for (v9 = 0; v9 < 4; v9++) {
            switch (v9) {
            case 0:
                if (v4 == 1) {
                    v12 = &v11[0x20 * 4];
                } else {
                    v12 = &v11[0x20 * 0];
                }

                v13 = (u16 *)v1;
                break;
            case 1:
                if (v4 == 1) {
                    v12 = &v11[0x20 * 5];
                } else {
                    v12 = &v11[0x20 * 1];
                }

                v13 = (u16 *)v1;
                v13++;
                break;
            case 2:
                if (v4 == 1) {
                    v12 = v11;
                } else {
                    v12 = &v11[0x20 * 2];
                }

                v13 = (u16 *)v1;
                v13 = &v13[2 * 8];
                break;
            case 3:
                if (v4 == 1) {
                    v12 = &v11[0x20 * 1];
                } else {
                    v12 = &v11[0x20 * 3];
                }

                v13 = (u16 *)v1;
                v13 = &v13[2 * 8 + 1];

                break;
            }

            v7 = 0;

            for (v6 = 0; v6 < 8; v6++) {
                v10 = 0;

                for (v8 = 0; v8 < 4; v8++) {
                    if (v12[v7] & 0xf) {
                        *v13 |= 1 << v10;
                    }

                    v10 += 2;

                    if (v12[v7] & 0xf0) {
                        *v13 |= 1 << v10;
                    }

                    v10 += 2;
                    v7++;
                }

                v13++;
                v13++;
            }
        }
    }

    v0 = (u16 *)((u8 *)param0 + param0->plttInfo.ofsPlttData);
    v0[1] = param3->stampColor;

    Heap_Free(v2);
}

static void FootprintStampModels_RotateTexture(NNSG3dResTex *param0, int param1)
{
    u32 *v0;
    u32 *v1;
    int v2, v3, v4, v5, v6;

    v0 = (u32 *)((u8 *)param0 + param0->texInfo.ofsTex);
    v1 = Heap_Alloc(HEAP_ID_118, (16 * 16 / 4));

    MI_CpuCopy16(v0, v1, (16 * 16 / 4));
    MI_CpuClear16(v0, (16 * 16 / 4));

    switch (param1) {
    case 3:
        v4 = 30;

        for (v3 = 0; v3 < 16; v3++) {
            v5 = 0;

            for (v2 = 0; v2 < 32; v2 += 2) {
                v6 = (v1[v3] >> v2) & 3;
                v0[v5] |= v6 << v4;
                v5++;
            }

            v4 -= 2;
        }
        break;
    case 4:
        v4 = 0;

        for (v3 = 0; v3 < 16; v3++) {
            v5 = 15;

            for (v2 = 0; v2 < 32; v2 += 2) {
                v6 = (v1[v3] >> v2) & 3;
                v0[v5] |= v6 << v4;
                v5--;
            }

            v4 += 2;
        }
        break;
    }

    Heap_Free(v1);
}

static void FootprintStampModels_FreeModel(FootprintStampModel *param0)
{
    Easy3DModel_Release(&param0->model);
    Heap_Free(param0);
}

static void FootprintStampModels_RemoveModel(FootprintStampModelManager *param0, FootprintStampModel *param1, int param2)
{
    if ((param1->appeared == 0) || (param1->textureRotated == 1)) {
        FootprintStampModels_RemoveTexture(param0, param1->model.texture);
    }

    FootprintStampModels_ReleaseSlot(param0, param1->slot);
    FootprintStampModels_FreeModel(param1);

    param0->models[param2] = NULL;
}

static void FootprintStampModels_GetBoardPosition(FootprintStampApp *param0, int param1, int param2, fx32 *param3, fx32 *param4)
{
    int v0 = param1 / 16;

    if (v0 >= NELEMS(sBoardXPositions)) {
        v0 = NELEMS(sBoardXPositions) - 1;
    }

    *param3 = sBoardXPositions[v0];

    if (v0 < NELEMS(sBoardXPositions) - 1) {
        *param3 += (sBoardXPositions[v0 + 1] - sBoardXPositions[v0]) / 16 * (param1 % 16);
    }

    v0 = param2 / 16;

    if (v0 >= NELEMS(sBoardYPositions)) {
        v0 = NELEMS(sBoardYPositions) - 1;
    }

    *param4 = sBoardYPositions[v0];

    if (v0 < NELEMS(sBoardYPositions) - 1) {
        *param4 += (sBoardYPositions[v0 + 1] - sBoardYPositions[v0]) / 16 * (param2 % 16);
    }
}

static int FootprintStampModels_AllocSlot(FootprintStampModelManager *param0)
{
    int v0, v1;

    for (v0 = 1; v0 < 32; v0++) {
        if ((param0->slotBitmap[0] & (1 << v0)) == 0) {
            param0->slotBitmap[0] |= 1 << v0;
            return v0;
        }
    }

    v1 = 0;

    for (; v0 < 63; v0++) {
        if ((param0->slotBitmap[1] & (1 << v1)) == 0) {
            param0->slotBitmap[1] |= 1 << v1;
            return v0;
        }

        v1++;
    }

    return 0xff;
}

static void FootprintStampModels_FreeSlot(FootprintStampModelManager *param0, int param1)
{
    if (param1 == 0xff) {
        return;
    }

    if (param1 < 32) {
        param0->slotBitmap[0] &= 0xffffffff ^ (1 << param1);
    } else {
        param0->slotBitmap[1] &= 0xffffffff ^ (1 << (param1 - 32));
    }
}

static void FootprintStampModels_ComputeBounds(Easy3DObject *param0, const FootprintStampEntry *param1, FootprintStampBounds *param2, int param3)
{
    fx32 v0, v1, v2;
    fx32 v3, v4, v5;
    int v6;
    fx64 v7, v8, v9, v10;

    v6 = PokemonOverworldFootprintSize(param1->species, param1->form);
    GF_ASSERT(v6 < NELEMS(sFootprintSizeBounds));

    Easy3DObject_GetPosition(param0, &v0, &v1, &v2);

    param2->minX = v0 + sFootprintSizeBounds[v6].minX;
    param2->maxX = v0 + sFootprintSizeBounds[v6].maxX;
    param2->maxY = v1 + sFootprintSizeBounds[v6].maxY;
    param2->minY = v1 + sFootprintSizeBounds[v6].minY;

    if (param3 == 1) {
        Easy3DObject_GetScale(param0, &v3, &v4, &v5);

        v7 = ((fx64)v3) * 100 / FX32_ONE;
        v9 = (param2->maxX - param2->minX) * v7 / 100 - (param2->maxX - param2->minX);

        param2->maxX += v9 / 2;
        param2->minX += -(v9 / 2);

        v8 = ((fx64)v4) * 100 / FX32_ONE;
        v10 = (param2->maxY - param2->minY) * v8 / 100 - (param2->maxY - param2->minY);

        param2->maxY += v10 / 2;
        param2->minY += -(v10 / 2);
    }
}

static BOOL FootprintStampModels_BoundsOverlap(const FootprintStampBounds *param0, const FootprintStampBounds *param1)
{
    if ((param0->minX <= param1->maxX) && (param1->minX <= param0->maxX) && (param0->maxY >= param1->minY) && (param1->maxY >= param0->minY)) {
        return 1;
    } else {
        return 0;
    }
}

static void FootprintStampModels_AssignSlot(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    int v0;
    FootprintStampSlot *v1 = param0->slots;

    for (v0 = 0; v0 < 128; v0++) {
        if (v1->refCount == 0) {
            param1->slot = v0;
            v1->count = 0;
            v1->refCount++;
            return;
        }

        v1++;
    }

    GF_ASSERT(FALSE);
}

static int FootprintStampModels_CountSlot(FootprintStampModelManager *param0, int param1, int param2)
{
    if (param1 == 0xff) {
        return 0;
    }

    param0->slots[param1].count++;
    param0->slots[param1].refCount++;

    if ((param0->cameraAnimState == 0) && (param0->pendingCameraAnim == 0) && (param0->slots[param1].count >= sSlotThresholds[param0->playerCount])) {
        param0->pendingCameraAnim = param2;
        MI_CpuClear8(&param0->fade, sizeof(FootprintStampFade));
        return 1;
    }

    return 0;
}

static void FootprintStampModels_ReleaseSlot(FootprintStampModelManager *param0, int param1)
{
    int v0;

    if (param1 == 0xff) {
        return;
    }

    v0 = param0->slots[param1].refCount;
    v0--;

    if (v0 < 0) {
        GF_ASSERT(FALSE);
        v0 = 0;
    }

    param0->slots[param1].refCount = v0;
}

static void FootprintStampModels_StartCameraAnim(FootprintStampModelManager *param0)
{
    MI_CpuClear8(&param0->cameraAnim, sizeof(FootprintStampCameraAnimData));

    param0->cameraAnimState = param0->pendingCameraAnim;
    param0->pendingCameraAnim = 0;
    param0->cameraAnimFinished = 0;
}

static BOOL FootprintStampModels_StartModelAnim(FootprintStampModel *param0, int param1)
{
    if ((param0->animState != 0) || (param0->requestedAnim != 0) || (param0->appeared == 0)) {
        return 0;
    }

    param0->requestedAnim = param1;
    MI_CpuClear8(&param0->animData, sizeof(FootprintStampModelAnimData));
    return 1;
}

static u8 FootprintStampModels_GetNatureAnim(const FootprintStampEntry *param0)
{
    u8 v0 = Pokemon_GetNatureOf(param0->personality);
    return sNatureToAnim[v0];
}

static int FootprintStampAnim_Appear(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimAppear *v0 = &param1->animData.val1;

    v0->timer++;

    if (v0->timer == 2) {
        FootprintStampModels_ComputeBounds(&param1->object, &param1->entry, &v0->bounds, 0);
        Easy3DObject_SetVisible(&param1->object, 1);
        param1->appeared = 1;
    }

    if (v0->timer > 40) {
        FootprintStampModels_AssignSlot(param0, param1);
        FootprintStampModels_StartModelAnim(param1, FootprintStampModels_GetNatureAnim(&param1->entry));
    }

    return 0;
}

static BOOL FootprintStampAnim_AppearCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    return 0;
}

static int FootprintStampAnim_Grow(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimGrow *v0 = &param1->animData.val2;

    switch (v0->state) {
    case 0:
        v0->alpha = 31 << 8;
        v0->slot = FootprintStampModels_AllocSlot(param0);
        v0->scale = FX32_ONE;
        v0->state++;
    case 1:
        v0->scale += 0xc0;

        if (v0->alpha - 0xc0 < 0x100) {
            Easy3DObject_SetVisible(&param1->object, 0);
            v0->state++;
            break;
        }

        v0->alpha -= 0xc0;
        Easy3DObject_SetScale(&param1->object, v0->scale, v0->scale, FX32_ONE);
        break;
    default:
        FootprintStampModels_FreeSlot(param0, v0->slot);
        return 1;
    }

    FootprintStampModels_ComputeBounds(&param1->object, &param1->entry, &v0->bounds, 1);
    return 0;
}

static void FootprintStampAnim_GrowDraw(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimGrow *v0 = &param1->animData.val2;

    if (v0->slot != 0xff) {
        NNS_G3dGlbPolygonAttr(0, 0, 0, v0->slot, v0->alpha >> 8, 0);
        NNS_G3dMdlUseGlbPolygonID(param1->model.model);
        NNS_G3dMdlUseGlbAlpha(param1->model.model);
    }

    Easy3DObject_Draw(&param1->object);
}

static BOOL FootprintStampAnim_GrowCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimGrow *v0 = &param1->animData.val2;
    FootprintStampAnimAppear *v1 = &param2->animData.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->bounds, &v1->bounds) == 1) {
        return 1;
    }

    return 0;
}

static int FootprintStampAnim_Split(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSplit *v0 = &param1->animData.val3;
    int v1;
    fx32 v2, v3, v4;

    switch (v0->state) {
    case 0:
        Easy3DObject_GetPosition(&param1->object, &v2, &v3, &v4);

        for (v1 = 0; v1 < 3; v1++) {
            Easy3DObject_Init(&v0->pieces[v1], &param1->model);
            Easy3DObject_SetPosition(&v0->pieces[v1], v2, v3, v4);
        }

        v0->state++;
    case 1:
        Easy3DObject_GetPosition(&param1->object, &v2, &v3, &v4);
        Easy3DObject_SetPosition(&param1->object, v2 - 0x2000, v3 - 0x2000, v4);
        Easy3DObject_GetPosition(&v0->pieces[0], &v2, &v3, &v4);
        Easy3DObject_SetPosition(&v0->pieces[0], v2 + 0x2000, v3 - 0x2000, v4);
        Easy3DObject_GetPosition(&v0->pieces[1], &v2, &v3, &v4);
        Easy3DObject_SetPosition(&v0->pieces[1], v2 - 0x2000, v3 + 0x2000, v4);
        Easy3DObject_GetPosition(&v0->pieces[2], &v2, &v3, &v4);
        Easy3DObject_SetPosition(&v0->pieces[2], v2 + 0x2000, v3 + 0x2000, v4);

        v0->timer++;

        if (v0->timer > 30) {
            return 1;
        }
    }

    FootprintStampModels_ComputeBounds(&param1->object, &param1->entry, &v0->bounds[0], 0);

    for (v1 = 0; v1 < 3; v1++) {
        FootprintStampModels_ComputeBounds(&v0->pieces[v1], &param1->entry, &v0->bounds[1 + v1], 0);
    }

    return 0;
}

static void FootprintStampAnim_SplitDraw(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSplit *v0 = &param1->animData.val3;
    int v1;

    for (v1 = 0; v1 < 3; v1++) {
        Easy3DObject_Draw(&v0->pieces[v1]);
    }

    Easy3DObject_Draw(&param1->object);
}

static BOOL FootprintStampAnim_SplitCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimSplit *v0 = &param1->animData.val3;
    FootprintStampAnimAppear *v1 = &param2->animData.val1;
    int v2;

    for (v2 = 0; v2 < 3 + 1; v2++) {
        if (FootprintStampModels_BoundsOverlap(&v0->bounds[v2], &v1->bounds) == 1) {
            return 1;
        }
    }

    return 0;
}

static int FootprintStampAnim_Spin(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSpin *v0 = &param1->animData.val4;
    u16 v1, v2;
    fx32 v3, v4, v5;

    switch (v0->state) {
    case 0:
        v1 = Easy3DObject_GetRotation(&param1->object, 2);
        v1 -= 65536 / 4 / 6;

        if (v1 <= 65536 / 8 * 7) {
            FootprintStampModels_RotateTexture(param1->model.texture, param1->animState);
            FootprintStampModels_AddTexture(param0, param1->model.texture);
            param1->textureRotated = 1;
            v1 += 65536 / 4;
            v0->state++;
        }

        Easy3DObject_SetRotation(&param1->object, v1, 2);
        break;
    case 1:
        param1->textureRotated = 0;

        v1 = Easy3DObject_GetRotation(&param1->object, 2);
        v1 -= 65536 / 4 / 6;

        if (v1 >= 65536 / 4 * 3) {
            v1 = 0;
            v0->state++;
        }

        Easy3DObject_SetRotation(&param1->object, v1, 2);
        break;
    case 2:
        v0->step++;

        if (v0->step < 4) {
            break;
        }

        v0->step = 0;
        v0->state++;
    case 3:
        Easy3DObject_GetPosition(&param1->object, &v3, &v4, &v5);

        if ((v3 < sBoardBounds.minX) || (v3 > sBoardBounds.maxX) || (v4 > sBoardBounds.maxY) || (v4 < sBoardBounds.minY)) {
            return 1;
        }

        if (v0->moveStep < 5) {
            Easy3DObject_SetPosition(&param1->object, v3 + 0x3000, v4 - 0x3000, v5);
        } else {
            Easy3DObject_SetPosition(&param1->object, v3 + 0x3000, v4 + 0x3000, v5);
        }

        v0->moveStep++;

        if (v0->moveStep >= 5 * 2) {
            v0->moveStep = 0;
        }

        break;
    }

    FootprintStampModels_ComputeBounds(&param1->object, &param1->entry, &v0->bounds, 0);
    return 0;
}

static BOOL FootprintStampAnim_SpinCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimSpin *v0 = &param1->animData.val4;
    FootprintStampAnimAppear *v1 = &param2->animData.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->bounds, &v1->bounds) == 1) {
        return 1;
    }

    return 0;
}

static int FootprintStampAnim_Bounce(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimBounce *v0 = &param1->animData.val5;
    u16 v1;
    fx32 v2, v3, v4;
    fx32 v5;

    switch (v0->state) {
    case 0:
        v1 = Easy3DObject_GetRotation(&param1->object, 2);
        v1 += 65536 / 4 / 6;

        if (v1 >= 65536 / 4 / 2) {
            FootprintStampModels_RotateTexture(param1->model.texture, param1->animState);
            v1 -= 65536 / 4;
            FootprintStampModels_AddTexture(param0, param1->model.texture);
            param1->textureRotated = 1;
            v0->state++;
        }

        Easy3DObject_SetRotation(&param1->object, v1, 2);
        break;
    case 1:
        param1->textureRotated = 0;

        v1 = Easy3DObject_GetRotation(&param1->object, 2);
        v1 += 65536 / 4 / 6;

        if ((v1 >= 0) && (v1 < 65536 / 4 * 1)) {
            v1 = 0;
            v0->state++;
        }

        Easy3DObject_SetRotation(&param1->object, v1, 2);
        break;
    case 2:
        v0->step++;

        if (v0->step < 4) {
            break;
        }

        Easy3DObject_GetPosition(&param1->object, &v2, &v3, &v4);

        v0->baseY = v3;
        v0->step = 0;
        v0->state++;
    case 3:
        Easy3DObject_GetPosition(&param1->object, &v2, &v3, &v4);

        if ((v2 < sBoardBounds.minX) || (v2 > sBoardBounds.maxX) || (v3 > sBoardBounds.maxY) || (v3 < sBoardBounds.minY)) {
            return 1;
        }

        v0->angle += 0x8000;

        if (v0->angle >= (360 << FX32_SHIFT)) {
            v0->angle -= 360 << FX32_SHIFT;
        }

        v5 = FX_Mul(CalcSineDegrees_FX32(v0->angle), 0x8000);
        Easy3DObject_SetPosition(&param1->object, v2 - 0x1000, v0->baseY + v5, v4);
        break;
    }

    FootprintStampModels_ComputeBounds(&param1->object, &param1->entry, &v0->bounds, 0);
    return 0;
}

static BOOL FootprintStampAnim_BounceCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimBounce *v0 = &param1->animData.val5;
    FootprintStampAnimAppear *v1 = &param2->animData.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->bounds, &v1->bounds) == 1) {
        return 1;
    }

    return 0;
}

static int FootprintStampAnim_Trail(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimTrail *v0 = &param1->animData.val6;
    fx32 v1, v2, v3;
    int v4;

    switch (v0->state) {
    case 0:
        v0->slot = FootprintStampModels_AllocSlot(param0);

        Easy3DObject_GetPosition(&param1->object, &v1, &v2, &v3);

        for (v4 = 0; v4 < 3; v4++) {
            Easy3DObject_Init(&v0->pieces[v4], &param1->model);
            Easy3DObject_SetPosition(&v0->pieces[v4], v1, v2, v3);
            Easy3DObject_SetVisible(&v0->pieces[v4], 0);
        }

        v0->state++;
    case 1:
        Easy3DObject_GetPosition(&param1->object, &v1, &v2, &v3);

        if ((v1 < sBoardBounds.minX) || (v1 > sBoardBounds.maxX) || (v2 > sBoardBounds.maxY) || (v2 < sBoardBounds.minY) || (v0->stopFlag == 1)) {
            for (v4 = 0; v4 < 3; v4++) {
                Easy3DObject_SetVisible(&v0->pieces[v4], 0);
            }

            Easy3DObject_SetVisible(&param1->object, 0);
            v0->state++;
            break;
        }

        Easy3DObject_SetPosition(&param1->object, v1, v2 + 0x2800, v3);

        if (v0->timer % 3 == 0) {
            Easy3DObject_SetPosition(&v0->pieces[v0->trailIndex], v1, v2 + 0x2800, v3);
            Easy3DObject_SetVisible(&v0->pieces[v0->trailIndex], 1);

            v0->trailIndex++;

            if (v0->trailIndex >= 3) {
                v0->trailIndex = 0;
            }
        }

        v0->timer++;
        break;
    default:
        FootprintStampModels_FreeSlot(param0, v0->slot);
        return 1;
    }

    FootprintStampModels_ComputeBounds(&param1->object, &param1->entry, &v0->bounds, 0);
    return 0;
}

static void FootprintStampAnim_TrailDraw(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimTrail *v0 = &param1->animData.val6;
    int v1;

    if (v0->slot != 0xff) {
        NNS_G3dGlbPolygonAttr(0, 0, 0, v0->slot, 8, 0);
        NNS_G3dMdlUseGlbPolygonID(param1->model.model);
        NNS_G3dMdlUseGlbAlpha(param1->model.model);
    }

    for (v1 = 0; v1 < 3; v1++) {
        Easy3DObject_Draw(&v0->pieces[v1]);
    }

    if (v0->slot != 0xff) {
        NNS_G3dGlbPolygonAttr(0, 0, 0, v0->slot, 31, 0);
        NNS_G3dMdlUseGlbPolygonID(param1->model.model);
        NNS_G3dMdlUseGlbAlpha(param1->model.model);
    }

    Easy3DObject_Draw(&param1->object);
}

static BOOL FootprintStampAnim_TrailCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimTrail *v0 = &param1->animData.val6;
    FootprintStampAnimAppear *v1 = &param2->animData.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->bounds, &v1->bounds) == 1) {
        return 1;
    }

    return 0;
}

static int FootprintStampAnim_Swing(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSwing *v0 = &param1->animData.val7;
    u16 v1;
    fx32 v2, v3, v4;
    fx32 v5;

    switch (v0->state) {
    case 0:
        Easy3DObject_GetPosition(&param1->object, &v2, &v3, &v4);

        v0->baseX = v2;
        v0->state++;
    case 1:
        Easy3DObject_GetPosition(&param1->object, &v2, &v3, &v4);

        if ((v2 < sBoardBounds.minX) || (v2 > sBoardBounds.maxX) || (v3 > sBoardBounds.maxY) || (v3 < sBoardBounds.minY)) {
            return 1;
        }

        v0->angle += 0x8000;

        if (v0->angle >= (360 << FX32_SHIFT)) {
            v0->angle -= 360 << FX32_SHIFT;
        }

        v5 = FX_Mul(CalcSineDegrees_FX32(v0->angle), 0x8000);
        Easy3DObject_SetPosition(&param1->object, v0->baseX + v5, v3 - 0x1000, v4);
        break;
    }

    FootprintStampModels_ComputeBounds(&param1->object, &param1->entry, &v0->bounds, 0);
    return 0;
}

static BOOL FootprintStampAnim_SwingCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimSwing *v0 = &param1->animData.val7;
    FootprintStampAnimAppear *v1 = &param2->animData.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->bounds, &v1->bounds) == 1) {
        return 1;
    }

    return 0;
}

static int FootprintStampAnim_Pulse(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimPulse *v0 = &param1->animData.val8;

    switch (v0->state) {
    case 0:
        v0->scale = FX32_ONE;
        v0->state++;
    case 1:
        v0->step++;

        if (v0->step > 8) {
            return 1;
        }

        v0->scale += 0x300;
        Easy3DObject_SetScale(&param1->object, v0->scale, v0->scale, FX32_ONE);
        break;
    }

    FootprintStampModels_ComputeBounds(&param1->object, &param1->entry, &v0->bounds, 1);
    return 0;
}

static BOOL FootprintStampAnim_PulseCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimPulse *v0 = &param1->animData.val8;
    FootprintStampAnimAppear *v1 = &param2->animData.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->bounds, &v1->bounds) == 1) {
        return 1;
    }

    return 0;
}

static int FootprintStampAnim_SplitX(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSplitX *v0 = &param1->animData.val9;
    fx32 v1, v2, v3;
    fx32 v4;
    int v5;

    switch (v0->state) {
    case 0:
        v0->slot = FootprintStampModels_AllocSlot(param0);
        Easy3DObject_GetPosition(&param1->object, &v1, &v2, &v3);

        for (v5 = 0; v5 < 2; v5++) {
            Easy3DObject_Init(&v0->pieces[v5], &param1->model);
            Easy3DObject_SetPosition(&v0->pieces[v5], v1, v2, v3);
            Easy3DObject_SetVisible(&v0->pieces[v5], 1);
        }

        v0->alpha = 31 << 8;
        v0->state++;
    case 1:
        if (v0->alpha - 0xa0 < 0x100) {
            for (v5 = 0; v5 < 2; v5++) {
                Easy3DObject_SetVisible(&v0->pieces[v5], 0);
            }

            Easy3DObject_SetVisible(&param1->object, 0);
            v0->state++;
            break;
        }

        v0->alpha -= 0xa0;
        v0->angle += 0x20000;

        if (v0->angle >= (360 << FX32_SHIFT)) {
            v0->angle -= 360 << FX32_SHIFT;
        }

        v4 = FX_Mul(CalcSineDegrees_FX32(v0->angle), 0x10000);

        Easy3DObject_GetPosition(&param1->object, &v1, &v2, &v3);

        for (v5 = 0; v5 < 2; v5++) {
            if (v5 & 1) {
                Easy3DObject_SetPosition(&v0->pieces[v5], v1 + v4, v2, v3);
            } else {
                Easy3DObject_SetPosition(&v0->pieces[v5], v1 - v4, v2, v3);
            }
        }
        break;
    default:
        FootprintStampModels_FreeSlot(param0, v0->slot);
        return 1;
    }

    FootprintStampModels_ComputeBounds(&param1->object, &param1->entry, &v0->bounds[0], 0);

    for (v5 = 0; v5 < 2; v5++) {
        FootprintStampModels_ComputeBounds(&v0->pieces[v5], &param1->entry, &v0->bounds[1 + v5], 0);
    }

    return 0;
}

static void FootprintStampAnim_SplitXDraw(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSplitX *v0 = &param1->animData.val9;
    int v1;

    if (v0->slot != 0xff) {
        NNS_G3dGlbPolygonAttr(0, 0, 0, v0->slot, v0->alpha >> 8, 0);
        NNS_G3dMdlUseGlbPolygonID(param1->model.model);
        NNS_G3dMdlUseGlbAlpha(param1->model.model);
    }

    for (v1 = 0; v1 < 2; v1++) {
        Easy3DObject_Draw(&v0->pieces[v1]);
    }

    Easy3DObject_Draw(&param1->object);
}

static BOOL FootprintStampAnim_SplitXCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimSplitX *v0 = &param1->animData.val9;
    FootprintStampAnimAppear *v1 = &param2->animData.val1;
    int v2;

    for (v2 = 0; v2 < 2 + 1; v2++) {
        if (FootprintStampModels_BoundsOverlap(&v0->bounds[v2], &v1->bounds) == 1) {
            return 1;
        }
    }

    return 0;
}

static int FootprintStampAnim_SplitY(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSplitY *v0 = &param1->animData.val10;
    fx32 v1, v2, v3;
    fx32 v4;
    int v5;

    switch (v0->state) {
    case 0:
        v0->slot = FootprintStampModels_AllocSlot(param0);

        Easy3DObject_GetPosition(&param1->object, &v1, &v2, &v3);

        for (v5 = 0; v5 < 2; v5++) {
            Easy3DObject_Init(&v0->pieces[v5], &param1->model);
            Easy3DObject_SetPosition(&v0->pieces[v5], v1, v2, v3);
            Easy3DObject_SetVisible(&v0->pieces[v5], 1);
        }

        v0->alpha = 31 << 8;
        v0->state++;
    case 1:
        if (v0->alpha - 0xa0 < 0x100) {
            for (v5 = 0; v5 < 2; v5++) {
                Easy3DObject_SetVisible(&v0->pieces[v5], 0);
            }

            Easy3DObject_SetVisible(&param1->object, 0);
            v0->state++;
            break;
        }

        v0->alpha -= 0xa0;
        v0->angle += 0x20000;

        if (v0->angle >= (360 << FX32_SHIFT)) {
            v0->angle -= 360 << FX32_SHIFT;
        }

        v4 = FX_Mul(CalcSineDegrees_FX32(v0->angle), 0x10000);

        Easy3DObject_GetPosition(&param1->object, &v1, &v2, &v3);

        for (v5 = 0; v5 < 2; v5++) {
            if (v5 & 1) {
                Easy3DObject_SetPosition(&v0->pieces[v5], v1, v2 + v4, v3);
            } else {
                Easy3DObject_SetPosition(&v0->pieces[v5], v1, v2 - v4, v3);
            }
        }
        break;
    default:
        FootprintStampModels_FreeSlot(param0, v0->slot);
        return 1;
    }

    FootprintStampModels_ComputeBounds(&param1->object, &param1->entry, &v0->bounds[0], 0);

    for (v5 = 0; v5 < 2; v5++) {
        FootprintStampModels_ComputeBounds(&v0->pieces[v5], &param1->entry, &v0->bounds[1 + v5], 0);
    }

    return 0;
}

static void FootprintStampAnim_SplitYDraw(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSplitY *v0 = &param1->animData.val10;
    int v1;

    if (v0->slot != 0xff) {
        NNS_G3dGlbPolygonAttr(0, 0, 0, v0->slot, v0->alpha >> 8, 0);
        NNS_G3dMdlUseGlbPolygonID(param1->model.model);
        NNS_G3dMdlUseGlbAlpha(param1->model.model);
    }

    for (v1 = 0; v1 < 2; v1++) {
        Easy3DObject_Draw(&v0->pieces[v1]);
    }

    Easy3DObject_Draw(&param1->object);
}

static BOOL FootprintStampAnim_SplitYCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimSplitY *v0 = &param1->animData.val10;
    FootprintStampAnimAppear *v1 = &param2->animData.val1;
    int v2;

    for (v2 = 0; v2 < 2 + 1; v2++) {
        if (FootprintStampModels_BoundsOverlap(&v0->bounds[v2], &v1->bounds) == 1) {
            return 1;
        }
    }

    return 0;
}

static int FootprintStampAnim_Stretch(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimStretch *v0 = &param1->animData.val11;
    fx32 v1, v2, v3;
    fx32 v4;

    switch (v0->state) {
    case 0:
        v0->scale = FX32_ONE;
        v0->state++;
    case 1:
        v0->step++;

        if (v0->step > 30) {
            return 1;
        }

        v0->scale += 0x180;
        Easy3DObject_SetScale(&param1->object, FX32_ONE, v0->scale, FX32_ONE);

        v4 = -(FX32_ONE * 2 / 2 * (v0->scale - FX32_ONE) / FX32_ONE);
        Easy3DObject_GetPosition(&param1->object, &v1, &v2, &v3);
        Easy3DObject_SetPosition(&param1->object, v1, v2 + v4, v3);

        break;
    }

    FootprintStampModels_ComputeBounds(&param1->object, &param1->entry, &v0->bounds, 1);
    return 0;
}

static BOOL FootprintStampAnim_StretchCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimStretch *v0 = &param1->animData.val11;
    FootprintStampAnimAppear *v1 = &param2->animData.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->bounds, &v1->bounds) == 1) {
        return 1;
    }

    return 0;
}

static BOOL FootprintStampModels_UpdateFade(FootprintStampModelManager *param0, FootprintStampFade *param1, int param2, int param3)
{
    int v0;

    if (param2 == 3) {
        return 0;
    }

    if (param3 == 0) {
        v0 = -1;
    } else {
        v0 = 1;
    }

    switch (param1->state) {
    case 0:
        param1->brightness += 0x200;

        if (param1->brightness >= 0x800) {
            param1->brightness = 0x800;
            param1->state++;
        }

        param0->isBrightnessPending = 1;
        param0->brightness = (param1->brightness >> 8) * v0;
        break;
    case 1:
        param1->brightness -= 0x200;

        if (param1->brightness <= 0) {
            param1->brightness = 0;
            param1->cycleCount++;

            if (param1->cycleCount < 2) {
                param1->state = 0;
            } else {
                param1->state++;
            }
        }

        param0->isBrightnessPending = 1;
        param0->brightness = (param1->brightness >> 8) * v0;
        break;
    default:
        param0->cameraAnimFinished = 1;
        return 1;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_ZoomIn(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimZoomIn *v0 = &param1->zoomIn;

    switch (v0->state) {
    case 0:
        v0->distance = Camera_GetDistance(camera);
        v0->state++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        Camera_AdjustDistance(((-FX32_ONE * 50) / 30), camera);
        v0->timer++;

        if (v0->timer >= 30) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 2:
        v0->timer++;

        if (v0->timer > 4) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 3:
        Camera_AdjustDistance((-(-FX32_ONE * 50) / 6), camera);
        v0->timer++;

        if ((v0->timer >= 6) || (Camera_GetDistance(camera) >= v0->distance)) {
            Camera_SetDistance(v0->distance, camera);
            return 1;
        }

        break;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_Shake(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimShake *v0 = &param1->shake;
    fx32 v1;

    switch (v0->state) {
    case 0:
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
        v0->state++;
    case 1:
        v0->step++;
        v1 = FX32_ONE * 4 / 16 * v0->step;

        if (v1 < FX32_ONE * 2) {
            v0->up.y = FX32_ONE - v1;
        } else {
            v0->up.y = -FX32_ONE + (v1 - FX32_ONE * 2);
        }

        if (v1 < FX32_ONE * 1) {
            v0->up.x = v1;
        } else if (v1 < FX32_ONE * 2) {
            v0->up.x = FX32_ONE - (v1 - FX32_ONE);
        } else if (v1 < FX32_ONE * 3) {
            v0->up.x = -(v1 - FX32_ONE * 2);
        } else {
            v0->up.x = -FX32_ONE + (v1 - FX32_ONE * 3);
        }

        if (v0->step >= 16) {
            v0->up.y = FX32_ONE;
            v0->up.x = 0;
            v0->step = 0;
            v0->repeat++;

            if (v0->repeat >= 2) {
                v0->state++;
            }
        }

        Camera_SetUp(&v0->up, camera);
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_RotateLeft(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimRotateLeft *v0 = &param1->rotateLeft;
    CameraAngle v1 = { 0, 0, 0, 0 };

    switch (v0->state) {
    case 0:
        v0->cameraAngle = Camera_GetAngle(camera);
        v0->angle = v0->cameraAngle.y;
        v0->state++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        v1.y += (-0x2000 / 2);
        v0->angle += (-0x2000 / 2);
        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->angle <= v0->cameraAngle.y - 0x2000) {
            v0->state++;
        }
        break;
    case 2:
        v0->step++;

        if (v0->step >= 16) {
            v0->state++;
        }
        break;
    case 3:
        v1.y += (0x2000 / 16);
        v0->angle += (0x2000 / 16);

        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->angle >= v0->cameraAngle.y) {
            Camera_SetAngleAroundTarget(&v0->cameraAngle, camera);
            return 1;
        }
        break;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_RotateRight(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimRotateRight *v0 = &param1->rotateRight;
    CameraAngle v1 = { 0, 0, 0, 0 };

    switch (v0->state) {
    case 0:
        v0->cameraAngle = Camera_GetAngle(camera);
        v0->angle = v0->cameraAngle.y;
        v0->state++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        v1.y += (0x2000 / 2);
        v0->angle += (0x2000 / 2);
        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->angle >= v0->cameraAngle.y + 0x2000) {
            v0->state++;
        }
        break;
    case 2:
        v0->step++;

        if (v0->step >= 16) {
            v0->state++;
        }
        break;
    case 3:
        v1.y += (-0x2000 / 16);
        v0->angle += (-0x2000 / 16);

        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->angle <= v0->cameraAngle.y) {
            Camera_SetAngleAroundTarget(&v0->cameraAngle, camera);
            return 1;
        }
        break;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_TiltUp(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimTiltUp *v0 = &param1->tiltUp;
    CameraAngle v1 = { 0, 0, 0, 0 };

    switch (v0->state) {
    case 0:
        v0->cameraAngle = Camera_GetAngle(camera);
        v0->angle = v0->cameraAngle.x;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
        v0->state++;
    case 1:
        v1.x += (0x2000 / 3);
        v0->angle += (0x2000 / 3);

        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->angle >= v0->cameraAngle.x + 0x2000) {
            v0->state++;
        }

        break;
    case 2:
        v0->step++;

        if (v0->step >= 16) {
            v0->state++;
        }
        break;
    case 3:
        v1.x += (-0x2000 / 16);
        v0->angle += (-0x2000 / 16);

        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->angle <= v0->cameraAngle.x) {
            Camera_SetAngleAroundTarget(&v0->cameraAngle, camera);
            return 1;
        }

        break;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_Spin(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimSpin *v0 = &param1->spin;
    fx32 v1;
    CameraAngle v2 = { 0, 0, 0, 0 };

    switch (v0->state) {
    case 0:
        v0->cameraAngle = Camera_GetAngle(camera);
        v0->state++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        v0->angle += 0x18000;

        if (v0->angle >= (360 << FX32_SHIFT)) {
            v0->angle -= 360 << FX32_SHIFT;
            v0->repeat++;

            if (v0->repeat >= 2) {
                v0->state++;
                v0->angle = 0;
            }
        }

        v1 = FX_Mul(CalcSineDegrees_FX32(v0->angle), 0x1000);
        v2 = v0->cameraAngle;
        v2.y = v1;
        Camera_SetAngleAroundSelf(&v2, camera);
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_ZoomOut(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimZoomOut *v0 = &param1->zoomOut;

    switch (v0->state) {
    case 0:
        v0->distance = Camera_GetDistance(camera);
        v0->state++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        Camera_AdjustDistance(((FX32_ONE * 50) / 30), camera);
        v0->timer++;

        if (v0->timer >= 30) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 2:
        v0->timer++;

        if (v0->timer > 4) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 3:
        Camera_AdjustDistance((-(FX32_ONE * 50) / 6), camera);
        v0->timer++;

        if ((v0->timer >= 6) || (Camera_GetDistance(camera) <= v0->distance)) {
            Camera_SetDistance(v0->distance, camera);
            return 1;
        }

        break;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_SwayX(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimSwayX *v0 = &param1->swayX;
    VecFx32 v1 = { 0, 0, 0 };
    fx32 v2;

    switch (v0->state) {
    case 0:
        v0->position = Camera_GetPosition(camera);
        v0->target = Camera_GetTarget(camera);
        v0->state++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        v0->angle += 0x20000;

        if (v0->angle >= (360 << FX32_SHIFT)) {
            v0->angle -= 360 << FX32_SHIFT;
            v0->repeat++;

            if (v0->repeat >= 4) {
                v0->state++;
                v0->angle = 0;
            }
        }

        v2 = FX_Mul(CalcSineDegrees_FX32(v0->angle), 0x10000);
        v1.x = v2;

        Camera_SetTarget(&v0->target, camera);
        Camera_SetPosition(&v0->position, camera);
        Camera_Move(&v1, camera);
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_SwayY(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimSwayY *v0 = &param1->swayY;
    VecFx32 v1 = { 0, 0, 0 };
    fx32 v2;

    switch (v0->state) {
    case 0:
        v0->position = Camera_GetPosition(camera);
        v0->target = Camera_GetTarget(camera);
        v0->state++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        v0->angle += 0x20000;

        if (v0->angle >= (360 << FX32_SHIFT)) {
            v0->angle -= 360 << FX32_SHIFT;
            v0->repeat++;

            if (v0->repeat >= 4) {
                v0->state++;
                v0->angle = 0;
            }
        }

        v2 = FX_Mul(CalcSineDegrees_FX32(v0->angle), 0x8000);
        v1.y = v2;

        Camera_SetTarget(&v0->target, camera);
        Camera_SetPosition(&v0->position, camera);
        Camera_Move(&v1, camera);
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_TiltDown(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimTiltDown *v0 = &param1->tiltDown;
    CameraAngle v1 = { 0, 0, 0, 0 };

    switch (v0->state) {
    case 0:
        v0->cameraAngle = Camera_GetAngle(camera);
        v0->angle = v0->cameraAngle.x;
        v0->state++;

        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        v1.x += (-0x2000 / 3);
        v0->angle += (-0x2000 / 3);

        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->angle <= v0->cameraAngle.x - 0x2000) {
            v0->state++;
        }
        break;
    case 2:
        v0->step++;

        if (v0->step >= 16) {
            v0->state++;
        }
        break;
    case 3:
        v1.x += (0x2000 / 16);
        v0->angle += (0x2000 / 16);

        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->angle >= v0->cameraAngle.x) {
            Camera_SetAngleAroundTarget(&v0->cameraAngle, camera);
            return 1;
        }

        break;
    }

    return 0;
}
