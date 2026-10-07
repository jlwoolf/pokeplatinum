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
    FootprintStampAnimInitFunc unk_00; // Advances the animation; returns 1 when it finishes.
    FootprintStampAnimDrawFunc unk_04; // Optional custom draw callback.
    FootprintStampAnimCollideFunc unk_08; // Tests overlap against another model.
} FootprintStampAnimHandler;

typedef struct {
    fx32 unk_00; // Minimum X.
    fx32 unk_04; // Maximum X.
    fx32 unk_08; // Minimum Y.
    fx32 unk_0C; // Maximum Y.
} FootprintStampBounds;

typedef struct {
    s32 unk_00;
    FootprintStampBounds unk_04;
} FootprintStampAnimAppear;

typedef struct {
    int unk_00;
    fx32 unk_04;
    u8 unk_08;
    u8 unk_09;
    FootprintStampBounds unk_0C;
} FootprintStampAnimGrow;

typedef struct {
    Easy3DObject unk_00[3];
    u16 unk_168;
    u8 unk_16A;
    FootprintStampBounds unk_16C[4];
} FootprintStampAnimSplit;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    FootprintStampBounds unk_0C;
} FootprintStampAnimSpin;

typedef struct {
    int unk_00;
    fx32 unk_04;
    int unk_08;
    fx32 unk_0C;
    FootprintStampBounds unk_10;
} FootprintStampAnimBounce;

typedef struct {
    Easy3DObject unk_00[3];
    u16 unk_168;
    u8 unk_16A;
    u8 unk_16B;
    u8 unk_16C;
    u8 unk_16D;
    FootprintStampBounds unk_170;
} FootprintStampAnimTrail;

typedef struct {
    int unk_00;
    fx32 unk_04;
    fx32 unk_08;
    FootprintStampBounds unk_0C;
} FootprintStampAnimSwing;

typedef struct {
    fx32 unk_00;
    u16 unk_04;
    u8 unk_06;
    FootprintStampBounds unk_08;
} FootprintStampAnimPulse;

typedef struct {
    Easy3DObject unk_00[2];
    fx32 unk_F0;
    u16 unk_F4;
    u8 unk_F6;
    u8 unk_F7;
    FootprintStampBounds unk_F8[3];
} FootprintStampAnimSplitX;

typedef struct {
    Easy3DObject unk_00[2];
    fx32 unk_F0;
    u16 unk_F4;
    u8 unk_F6;
    u8 unk_F7;
    FootprintStampBounds unk_F8[3];
} FootprintStampAnimSplitY;

typedef struct {
    fx32 unk_00;
    u16 unk_04;
    u8 unk_06;
    FootprintStampBounds unk_08;
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
    FootprintStampEntry unk_00; // The footprint entry this model represents.
    Easy3DModel unk_0C;
    Easy3DObject unk_1C;
    FootprintStampModelAnimData unk_94; // Per-animation scratch data.
    u32 unk_240_0 : 4; // Whether the model has finished appearing.
    u32 unk_240_4 : 4; // Whether the texture is currently rotated.
    u32 unk_240_8 : 8; // Current animation state index.
    u32 unk_240_16 : 8; // Animation state requested to start.
    u32 unk_240_24 : 8; // Slot index assigned to this model.
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
    fx32 unk_00;
    fx32 unk_04;
    fx32 unk_08;
    fx32 unk_0C;
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
        if (param0->unk_B4[v0] != NULL) {
            FootprintStampModels_FreeModel(param0->unk_B4[v0]);
        }
    }
}

BOOL FootprintStampModels_Add(FootprintStampApp *param0, FootprintStampModelManager *param1, const FootprintStampEntry *param2, NARC *param3, NARC *param4, BOOL param5)
{
    int v0;

    if (param1->unk_73C != 0) {
        return 0;
    }

    for (v0 = 0; v0 < 128; v0++) {
        if (param1->unk_B4[v0] == NULL) {
            param1->unk_B4[v0] = FootprintStampModels_CreateModel(param0, param1, param2, param3, param4, param5);

            if (param1->unk_B4[v0] == NULL) {
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

    if (param0->unk_73D != 0) {
        FootprintStampModels_UpdateFade(param0, &param0->unk_B0, param2, param3);
    }

    if (param0->unk_73C != 0) {
        if (sCameraAnimHandlers[param0->unk_73C](param0, &param0->unk_00, camera) == 1) {
            param0->unk_73C = 0;
        }
    }

    for (v0 = 0; v0 < 128; v0++) {
        v1 = param0->unk_B4[v0];

        if (v1 != NULL) {
            if ((v1->unk_240_8 == 0) && (v1->unk_240_16 != 0)) {
                v1->unk_240_8 = v1->unk_240_16;
            }

            v2 = sAnimHandlers[v1->unk_240_8].unk_00(param0, v1);

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
        v1 = param0->unk_B4[v0];

        if (v1 != NULL) {
            if (sAnimHandlers[v1->unk_240_8].unk_04 != NULL) {
                sAnimHandlers[v1->unk_240_8].unk_04(param0, v1);
            } else {
                Easy3DObject_Draw(&v1->unk_1C);
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
        v5 = param0->unk_B4[v0];

        if (v5 != NULL) {
            if (v5->unk_240_8 != 0) {
                param0->unk_2B4[v1] = v5;
                v1++;
            } else {
                param0->unk_2B4[128 - 1 - v2] = v5;
                v2++;
            }
        }
    }

    for (v4 = 0; v4 < v2; v4++) {
        v6 = param0->unk_2B4[128 - 1 - v4];

        for (v3 = 0; v3 < v1; v3++) {
            v5 = param0->unk_2B4[v3];

            if (sAnimHandlers[v5->unk_240_8].unk_08(param0, v5, v6) == 1) {
                v7 = FootprintStampModels_StartModelAnim(v6, v5->unk_240_8);

                if ((v7 == 1) && (v6->unk_240_24 == 0xff)) {
                    v6->unk_240_24 = v5->unk_240_24;

                    if (FootprintStampModels_CountSlot(param0, v5->unk_240_24, v5->unk_240_8) == 1) {
                        v8++;
                    }

                    break;
                }
            }
        }
    }

    if ((param0->unk_73D != 0) && (param0->unk_73E == 1)) {
        for (v0 = 0; v0 < 128; v0++) {
            v5 = param0->unk_B4[v0];

            if ((v5 != NULL) && (v5->unk_240_8 != param0->unk_73D) && (v5->unk_240_16 != param0->unk_73D)) {
                if (FootprintStampModels_StartModelAnim(v5, param0->unk_73D) == 0) {
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

    v1 = param0->unk_4B4;

    for (v0 = 0; v0 < 32; v0++) {
        if (*v1 != NULL) {
            DC_FlushRange(*v1, (*v1)->header.size);

            NNS_G3dTexLoad(*v1, 1);
            NNS_G3dPlttLoad(*v1, 1);

            *v1 = NULL;
        }

        v1++;
    }

    if (param0->unk_740 && (param1 != 3)) {
        SetScreenMasterBrightness(DS_SCREEN_MAIN, param0->unk_742);
        param0->unk_740 = 0;
    }
}

static FootprintStampModel *FootprintStampModels_CreateModel(FootprintStampApp *param0, FootprintStampModelManager *param1, const FootprintStampEntry *param2, NARC *param3, NARC *param4, BOOL param5)
{
    FootprintStampModel *v0;
    fx32 v1, v2;
    BOOL v3;

    v0 = Heap_Alloc(HEAP_ID_118, sizeof(FootprintStampModel));
    MI_CpuClear8(v0, sizeof(FootprintStampModel));

    v0->unk_240_24 = 0xff;
    v0->unk_00 = *param2;

    if (v0->unk_00.species > NATIONAL_DEX_COUNT) {
        GF_ASSERT(FALSE);
        v0->unk_00.species = 132;
    }

    v3 = FootprintStampModels_LoadModel(param1, &v0->unk_0C, param3, param4, &v0->unk_00, param5);

    if (v3 == 0) {
        return NULL;
    }

    Easy3DObject_Init(&v0->unk_1C, &v0->unk_0C);
    FootprintStampModels_GetBoardPosition(param0, param2->touchX, param2->touchY, &v1, &v2);
    Easy3DObject_SetPosition(&v0->unk_1C, v1, v2, (FX32_ONE * 16));
    Easy3DObject_SetScale(&v0->unk_1C, (FX32_CONST(1.00f)), (FX32_CONST(1.00f)), (FX32_CONST(1.00f)));
    Easy3DObject_SetVisible(&v0->unk_1C, 0);

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
        if (param0->unk_4B4[v0] == NULL) {
            param0->unk_4B4[v0] = param1;
            return 1;
        }
    }

    return 0;
}

static void FootprintStampModels_RemoveTexture(FootprintStampModelManager *param0, NNSG3dResTex *param1)
{
    int v0;

    for (v0 = 0; v0 < 32; v0++) {
        if (param0->unk_4B4[v0] == param1) {
            param0->unk_4B4[v0] = NULL;
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
    Easy3DModel_Release(&param0->unk_0C);
    Heap_Free(param0);
}

static void FootprintStampModels_RemoveModel(FootprintStampModelManager *param0, FootprintStampModel *param1, int param2)
{
    if ((param1->unk_240_0 == 0) || (param1->unk_240_4 == 1)) {
        FootprintStampModels_RemoveTexture(param0, param1->unk_0C.texture);
    }

    FootprintStampModels_ReleaseSlot(param0, param1->unk_240_24);
    FootprintStampModels_FreeModel(param1);

    param0->unk_B4[param2] = NULL;
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
        if ((param0->unk_534[0] & (1 << v0)) == 0) {
            param0->unk_534[0] |= 1 << v0;
            return v0;
        }
    }

    v1 = 0;

    for (; v0 < 63; v0++) {
        if ((param0->unk_534[1] & (1 << v1)) == 0) {
            param0->unk_534[1] |= 1 << v1;
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
        param0->unk_534[0] &= 0xffffffff ^ (1 << param1);
    } else {
        param0->unk_534[1] &= 0xffffffff ^ (1 << (param1 - 32));
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

    param2->unk_00 = v0 + sFootprintSizeBounds[v6].unk_00;
    param2->unk_04 = v0 + sFootprintSizeBounds[v6].unk_04;
    param2->unk_08 = v1 + sFootprintSizeBounds[v6].unk_08;
    param2->unk_0C = v1 + sFootprintSizeBounds[v6].unk_0C;

    if (param3 == 1) {
        Easy3DObject_GetScale(param0, &v3, &v4, &v5);

        v7 = ((fx64)v3) * 100 / FX32_ONE;
        v9 = (param2->unk_04 - param2->unk_00) * v7 / 100 - (param2->unk_04 - param2->unk_00);

        param2->unk_04 += v9 / 2;
        param2->unk_00 += -(v9 / 2);

        v8 = ((fx64)v4) * 100 / FX32_ONE;
        v10 = (param2->unk_08 - param2->unk_0C) * v8 / 100 - (param2->unk_08 - param2->unk_0C);

        param2->unk_08 += v10 / 2;
        param2->unk_0C += -(v10 / 2);
    }
}

static BOOL FootprintStampModels_BoundsOverlap(const FootprintStampBounds *param0, const FootprintStampBounds *param1)
{
    if ((param0->unk_00 <= param1->unk_04) && (param1->unk_00 <= param0->unk_04) && (param0->unk_08 >= param1->unk_0C) && (param1->unk_08 >= param0->unk_0C)) {
        return 1;
    } else {
        return 0;
    }
}

static void FootprintStampModels_AssignSlot(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    int v0;
    FootprintStampSlot *v1 = param0->unk_53C;

    for (v0 = 0; v0 < 128; v0++) {
        if (v1->unk_01 == 0) {
            param1->unk_240_24 = v0;
            v1->unk_00 = 0;
            v1->unk_01++;
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

    param0->unk_53C[param1].unk_00++;
    param0->unk_53C[param1].unk_01++;

    if ((param0->unk_73C == 0) && (param0->unk_73D == 0) && (param0->unk_53C[param1].unk_00 >= sSlotThresholds[param0->unk_73F])) {
        param0->unk_73D = param2;
        MI_CpuClear8(&param0->unk_B0, sizeof(FootprintStampFade));
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

    v0 = param0->unk_53C[param1].unk_01;
    v0--;

    if (v0 < 0) {
        GF_ASSERT(FALSE);
        v0 = 0;
    }

    param0->unk_53C[param1].unk_01 = v0;
}

static void FootprintStampModels_StartCameraAnim(FootprintStampModelManager *param0)
{
    MI_CpuClear8(&param0->unk_00, sizeof(FootprintStampCameraAnimData));

    param0->unk_73C = param0->unk_73D;
    param0->unk_73D = 0;
    param0->unk_73E = 0;
}

static BOOL FootprintStampModels_StartModelAnim(FootprintStampModel *param0, int param1)
{
    if ((param0->unk_240_8 != 0) || (param0->unk_240_16 != 0) || (param0->unk_240_0 == 0)) {
        return 0;
    }

    param0->unk_240_16 = param1;
    MI_CpuClear8(&param0->unk_94, sizeof(FootprintStampModelAnimData));
    return 1;
}

static u8 FootprintStampModels_GetNatureAnim(const FootprintStampEntry *param0)
{
    u8 v0 = Pokemon_GetNatureOf(param0->personality);
    return sNatureToAnim[v0];
}

static int FootprintStampAnim_Appear(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimAppear *v0 = &param1->unk_94.val1;

    v0->unk_00++;

    if (v0->unk_00 == 2) {
        FootprintStampModels_ComputeBounds(&param1->unk_1C, &param1->unk_00, &v0->unk_04, 0);
        Easy3DObject_SetVisible(&param1->unk_1C, 1);
        param1->unk_240_0 = 1;
    }

    if (v0->unk_00 > 40) {
        FootprintStampModels_AssignSlot(param0, param1);
        FootprintStampModels_StartModelAnim(param1, FootprintStampModels_GetNatureAnim(&param1->unk_00));
    }

    return 0;
}

static BOOL FootprintStampAnim_AppearCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    return 0;
}

static int FootprintStampAnim_Grow(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimGrow *v0 = &param1->unk_94.val2;

    switch (v0->unk_08) {
    case 0:
        v0->unk_00 = 31 << 8;
        v0->unk_09 = FootprintStampModels_AllocSlot(param0);
        v0->unk_04 = FX32_ONE;
        v0->unk_08++;
    case 1:
        v0->unk_04 += 0xc0;

        if (v0->unk_00 - 0xc0 < 0x100) {
            Easy3DObject_SetVisible(&param1->unk_1C, 0);
            v0->unk_08++;
            break;
        }

        v0->unk_00 -= 0xc0;
        Easy3DObject_SetScale(&param1->unk_1C, v0->unk_04, v0->unk_04, FX32_ONE);
        break;
    default:
        FootprintStampModels_FreeSlot(param0, v0->unk_09);
        return 1;
    }

    FootprintStampModels_ComputeBounds(&param1->unk_1C, &param1->unk_00, &v0->unk_0C, 1);
    return 0;
}

static void FootprintStampAnim_GrowDraw(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimGrow *v0 = &param1->unk_94.val2;

    if (v0->unk_09 != 0xff) {
        NNS_G3dGlbPolygonAttr(0, 0, 0, v0->unk_09, v0->unk_00 >> 8, 0);
        NNS_G3dMdlUseGlbPolygonID(param1->unk_0C.model);
        NNS_G3dMdlUseGlbAlpha(param1->unk_0C.model);
    }

    Easy3DObject_Draw(&param1->unk_1C);
}

static BOOL FootprintStampAnim_GrowCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimGrow *v0 = &param1->unk_94.val2;
    FootprintStampAnimAppear *v1 = &param2->unk_94.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->unk_0C, &v1->unk_04) == 1) {
        return 1;
    }

    return 0;
}

static int FootprintStampAnim_Split(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSplit *v0 = &param1->unk_94.val3;
    int v1;
    fx32 v2, v3, v4;

    switch (v0->unk_16A) {
    case 0:
        Easy3DObject_GetPosition(&param1->unk_1C, &v2, &v3, &v4);

        for (v1 = 0; v1 < 3; v1++) {
            Easy3DObject_Init(&v0->unk_00[v1], &param1->unk_0C);
            Easy3DObject_SetPosition(&v0->unk_00[v1], v2, v3, v4);
        }

        v0->unk_16A++;
    case 1:
        Easy3DObject_GetPosition(&param1->unk_1C, &v2, &v3, &v4);
        Easy3DObject_SetPosition(&param1->unk_1C, v2 - 0x2000, v3 - 0x2000, v4);
        Easy3DObject_GetPosition(&v0->unk_00[0], &v2, &v3, &v4);
        Easy3DObject_SetPosition(&v0->unk_00[0], v2 + 0x2000, v3 - 0x2000, v4);
        Easy3DObject_GetPosition(&v0->unk_00[1], &v2, &v3, &v4);
        Easy3DObject_SetPosition(&v0->unk_00[1], v2 - 0x2000, v3 + 0x2000, v4);
        Easy3DObject_GetPosition(&v0->unk_00[2], &v2, &v3, &v4);
        Easy3DObject_SetPosition(&v0->unk_00[2], v2 + 0x2000, v3 + 0x2000, v4);

        v0->unk_168++;

        if (v0->unk_168 > 30) {
            return 1;
        }
    }

    FootprintStampModels_ComputeBounds(&param1->unk_1C, &param1->unk_00, &v0->unk_16C[0], 0);

    for (v1 = 0; v1 < 3; v1++) {
        FootprintStampModels_ComputeBounds(&v0->unk_00[v1], &param1->unk_00, &v0->unk_16C[1 + v1], 0);
    }

    return 0;
}

static void FootprintStampAnim_SplitDraw(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSplit *v0 = &param1->unk_94.val3;
    int v1;

    for (v1 = 0; v1 < 3; v1++) {
        Easy3DObject_Draw(&v0->unk_00[v1]);
    }

    Easy3DObject_Draw(&param1->unk_1C);
}

static BOOL FootprintStampAnim_SplitCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimSplit *v0 = &param1->unk_94.val3;
    FootprintStampAnimAppear *v1 = &param2->unk_94.val1;
    int v2;

    for (v2 = 0; v2 < 3 + 1; v2++) {
        if (FootprintStampModels_BoundsOverlap(&v0->unk_16C[v2], &v1->unk_04) == 1) {
            return 1;
        }
    }

    return 0;
}

static int FootprintStampAnim_Spin(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSpin *v0 = &param1->unk_94.val4;
    u16 v1, v2;
    fx32 v3, v4, v5;

    switch (v0->unk_00) {
    case 0:
        v1 = Easy3DObject_GetRotation(&param1->unk_1C, 2);
        v1 -= 65536 / 4 / 6;

        if (v1 <= 65536 / 8 * 7) {
            FootprintStampModels_RotateTexture(param1->unk_0C.texture, param1->unk_240_8);
            FootprintStampModels_AddTexture(param0, param1->unk_0C.texture);
            param1->unk_240_4 = 1;
            v1 += 65536 / 4;
            v0->unk_00++;
        }

        Easy3DObject_SetRotation(&param1->unk_1C, v1, 2);
        break;
    case 1:
        param1->unk_240_4 = 0;

        v1 = Easy3DObject_GetRotation(&param1->unk_1C, 2);
        v1 -= 65536 / 4 / 6;

        if (v1 >= 65536 / 4 * 3) {
            v1 = 0;
            v0->unk_00++;
        }

        Easy3DObject_SetRotation(&param1->unk_1C, v1, 2);
        break;
    case 2:
        v0->unk_04++;

        if (v0->unk_04 < 4) {
            break;
        }

        v0->unk_04 = 0;
        v0->unk_00++;
    case 3:
        Easy3DObject_GetPosition(&param1->unk_1C, &v3, &v4, &v5);

        if ((v3 < sBoardBounds.unk_00) || (v3 > sBoardBounds.unk_04) || (v4 > sBoardBounds.unk_08) || (v4 < sBoardBounds.unk_0C)) {
            return 1;
        }

        if (v0->unk_08 < 5) {
            Easy3DObject_SetPosition(&param1->unk_1C, v3 + 0x3000, v4 - 0x3000, v5);
        } else {
            Easy3DObject_SetPosition(&param1->unk_1C, v3 + 0x3000, v4 + 0x3000, v5);
        }

        v0->unk_08++;

        if (v0->unk_08 >= 5 * 2) {
            v0->unk_08 = 0;
        }

        break;
    }

    FootprintStampModels_ComputeBounds(&param1->unk_1C, &param1->unk_00, &v0->unk_0C, 0);
    return 0;
}

static BOOL FootprintStampAnim_SpinCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimSpin *v0 = &param1->unk_94.val4;
    FootprintStampAnimAppear *v1 = &param2->unk_94.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->unk_0C, &v1->unk_04) == 1) {
        return 1;
    }

    return 0;
}

static int FootprintStampAnim_Bounce(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimBounce *v0 = &param1->unk_94.val5;
    u16 v1;
    fx32 v2, v3, v4;
    fx32 v5;

    switch (v0->unk_00) {
    case 0:
        v1 = Easy3DObject_GetRotation(&param1->unk_1C, 2);
        v1 += 65536 / 4 / 6;

        if (v1 >= 65536 / 4 / 2) {
            FootprintStampModels_RotateTexture(param1->unk_0C.texture, param1->unk_240_8);
            v1 -= 65536 / 4;
            FootprintStampModels_AddTexture(param0, param1->unk_0C.texture);
            param1->unk_240_4 = 1;
            v0->unk_00++;
        }

        Easy3DObject_SetRotation(&param1->unk_1C, v1, 2);
        break;
    case 1:
        param1->unk_240_4 = 0;

        v1 = Easy3DObject_GetRotation(&param1->unk_1C, 2);
        v1 += 65536 / 4 / 6;

        if ((v1 >= 0) && (v1 < 65536 / 4 * 1)) {
            v1 = 0;
            v0->unk_00++;
        }

        Easy3DObject_SetRotation(&param1->unk_1C, v1, 2);
        break;
    case 2:
        v0->unk_08++;

        if (v0->unk_08 < 4) {
            break;
        }

        Easy3DObject_GetPosition(&param1->unk_1C, &v2, &v3, &v4);

        v0->unk_0C = v3;
        v0->unk_08 = 0;
        v0->unk_00++;
    case 3:
        Easy3DObject_GetPosition(&param1->unk_1C, &v2, &v3, &v4);

        if ((v2 < sBoardBounds.unk_00) || (v2 > sBoardBounds.unk_04) || (v3 > sBoardBounds.unk_08) || (v3 < sBoardBounds.unk_0C)) {
            return 1;
        }

        v0->unk_04 += 0x8000;

        if (v0->unk_04 >= (360 << FX32_SHIFT)) {
            v0->unk_04 -= 360 << FX32_SHIFT;
        }

        v5 = FX_Mul(CalcSineDegrees_FX32(v0->unk_04), 0x8000);
        Easy3DObject_SetPosition(&param1->unk_1C, v2 - 0x1000, v0->unk_0C + v5, v4);
        break;
    }

    FootprintStampModels_ComputeBounds(&param1->unk_1C, &param1->unk_00, &v0->unk_10, 0);
    return 0;
}

static BOOL FootprintStampAnim_BounceCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimBounce *v0 = &param1->unk_94.val5;
    FootprintStampAnimAppear *v1 = &param2->unk_94.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->unk_10, &v1->unk_04) == 1) {
        return 1;
    }

    return 0;
}

static int FootprintStampAnim_Trail(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimTrail *v0 = &param1->unk_94.val6;
    fx32 v1, v2, v3;
    int v4;

    switch (v0->unk_16D) {
    case 0:
        v0->unk_16C = FootprintStampModels_AllocSlot(param0);

        Easy3DObject_GetPosition(&param1->unk_1C, &v1, &v2, &v3);

        for (v4 = 0; v4 < 3; v4++) {
            Easy3DObject_Init(&v0->unk_00[v4], &param1->unk_0C);
            Easy3DObject_SetPosition(&v0->unk_00[v4], v1, v2, v3);
            Easy3DObject_SetVisible(&v0->unk_00[v4], 0);
        }

        v0->unk_16D++;
    case 1:
        Easy3DObject_GetPosition(&param1->unk_1C, &v1, &v2, &v3);

        if ((v1 < sBoardBounds.unk_00) || (v1 > sBoardBounds.unk_04) || (v2 > sBoardBounds.unk_08) || (v2 < sBoardBounds.unk_0C) || (v0->unk_16B == 1)) {
            for (v4 = 0; v4 < 3; v4++) {
                Easy3DObject_SetVisible(&v0->unk_00[v4], 0);
            }

            Easy3DObject_SetVisible(&param1->unk_1C, 0);
            v0->unk_16D++;
            break;
        }

        Easy3DObject_SetPosition(&param1->unk_1C, v1, v2 + 0x2800, v3);

        if (v0->unk_168 % 3 == 0) {
            Easy3DObject_SetPosition(&v0->unk_00[v0->unk_16A], v1, v2 + 0x2800, v3);
            Easy3DObject_SetVisible(&v0->unk_00[v0->unk_16A], 1);

            v0->unk_16A++;

            if (v0->unk_16A >= 3) {
                v0->unk_16A = 0;
            }
        }

        v0->unk_168++;
        break;
    default:
        FootprintStampModels_FreeSlot(param0, v0->unk_16C);
        return 1;
    }

    FootprintStampModels_ComputeBounds(&param1->unk_1C, &param1->unk_00, &v0->unk_170, 0);
    return 0;
}

static void FootprintStampAnim_TrailDraw(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimTrail *v0 = &param1->unk_94.val6;
    int v1;

    if (v0->unk_16C != 0xff) {
        NNS_G3dGlbPolygonAttr(0, 0, 0, v0->unk_16C, 8, 0);
        NNS_G3dMdlUseGlbPolygonID(param1->unk_0C.model);
        NNS_G3dMdlUseGlbAlpha(param1->unk_0C.model);
    }

    for (v1 = 0; v1 < 3; v1++) {
        Easy3DObject_Draw(&v0->unk_00[v1]);
    }

    if (v0->unk_16C != 0xff) {
        NNS_G3dGlbPolygonAttr(0, 0, 0, v0->unk_16C, 31, 0);
        NNS_G3dMdlUseGlbPolygonID(param1->unk_0C.model);
        NNS_G3dMdlUseGlbAlpha(param1->unk_0C.model);
    }

    Easy3DObject_Draw(&param1->unk_1C);
}

static BOOL FootprintStampAnim_TrailCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimTrail *v0 = &param1->unk_94.val6;
    FootprintStampAnimAppear *v1 = &param2->unk_94.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->unk_170, &v1->unk_04) == 1) {
        return 1;
    }

    return 0;
}

static int FootprintStampAnim_Swing(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSwing *v0 = &param1->unk_94.val7;
    u16 v1;
    fx32 v2, v3, v4;
    fx32 v5;

    switch (v0->unk_00) {
    case 0:
        Easy3DObject_GetPosition(&param1->unk_1C, &v2, &v3, &v4);

        v0->unk_08 = v2;
        v0->unk_00++;
    case 1:
        Easy3DObject_GetPosition(&param1->unk_1C, &v2, &v3, &v4);

        if ((v2 < sBoardBounds.unk_00) || (v2 > sBoardBounds.unk_04) || (v3 > sBoardBounds.unk_08) || (v3 < sBoardBounds.unk_0C)) {
            return 1;
        }

        v0->unk_04 += 0x8000;

        if (v0->unk_04 >= (360 << FX32_SHIFT)) {
            v0->unk_04 -= 360 << FX32_SHIFT;
        }

        v5 = FX_Mul(CalcSineDegrees_FX32(v0->unk_04), 0x8000);
        Easy3DObject_SetPosition(&param1->unk_1C, v0->unk_08 + v5, v3 - 0x1000, v4);
        break;
    }

    FootprintStampModels_ComputeBounds(&param1->unk_1C, &param1->unk_00, &v0->unk_0C, 0);
    return 0;
}

static BOOL FootprintStampAnim_SwingCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimSwing *v0 = &param1->unk_94.val7;
    FootprintStampAnimAppear *v1 = &param2->unk_94.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->unk_0C, &v1->unk_04) == 1) {
        return 1;
    }

    return 0;
}

static int FootprintStampAnim_Pulse(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimPulse *v0 = &param1->unk_94.val8;

    switch (v0->unk_06) {
    case 0:
        v0->unk_00 = FX32_ONE;
        v0->unk_06++;
    case 1:
        v0->unk_04++;

        if (v0->unk_04 > 8) {
            return 1;
        }

        v0->unk_00 += 0x300;
        Easy3DObject_SetScale(&param1->unk_1C, v0->unk_00, v0->unk_00, FX32_ONE);
        break;
    }

    FootprintStampModels_ComputeBounds(&param1->unk_1C, &param1->unk_00, &v0->unk_08, 1);
    return 0;
}

static BOOL FootprintStampAnim_PulseCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimPulse *v0 = &param1->unk_94.val8;
    FootprintStampAnimAppear *v1 = &param2->unk_94.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->unk_08, &v1->unk_04) == 1) {
        return 1;
    }

    return 0;
}

static int FootprintStampAnim_SplitX(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSplitX *v0 = &param1->unk_94.val9;
    fx32 v1, v2, v3;
    fx32 v4;
    int v5;

    switch (v0->unk_F7) {
    case 0:
        v0->unk_F6 = FootprintStampModels_AllocSlot(param0);
        Easy3DObject_GetPosition(&param1->unk_1C, &v1, &v2, &v3);

        for (v5 = 0; v5 < 2; v5++) {
            Easy3DObject_Init(&v0->unk_00[v5], &param1->unk_0C);
            Easy3DObject_SetPosition(&v0->unk_00[v5], v1, v2, v3);
            Easy3DObject_SetVisible(&v0->unk_00[v5], 1);
        }

        v0->unk_F4 = 31 << 8;
        v0->unk_F7++;
    case 1:
        if (v0->unk_F4 - 0xa0 < 0x100) {
            for (v5 = 0; v5 < 2; v5++) {
                Easy3DObject_SetVisible(&v0->unk_00[v5], 0);
            }

            Easy3DObject_SetVisible(&param1->unk_1C, 0);
            v0->unk_F7++;
            break;
        }

        v0->unk_F4 -= 0xa0;
        v0->unk_F0 += 0x20000;

        if (v0->unk_F0 >= (360 << FX32_SHIFT)) {
            v0->unk_F0 -= 360 << FX32_SHIFT;
        }

        v4 = FX_Mul(CalcSineDegrees_FX32(v0->unk_F0), 0x10000);

        Easy3DObject_GetPosition(&param1->unk_1C, &v1, &v2, &v3);

        for (v5 = 0; v5 < 2; v5++) {
            if (v5 & 1) {
                Easy3DObject_SetPosition(&v0->unk_00[v5], v1 + v4, v2, v3);
            } else {
                Easy3DObject_SetPosition(&v0->unk_00[v5], v1 - v4, v2, v3);
            }
        }
        break;
    default:
        FootprintStampModels_FreeSlot(param0, v0->unk_F6);
        return 1;
    }

    FootprintStampModels_ComputeBounds(&param1->unk_1C, &param1->unk_00, &v0->unk_F8[0], 0);

    for (v5 = 0; v5 < 2; v5++) {
        FootprintStampModels_ComputeBounds(&v0->unk_00[v5], &param1->unk_00, &v0->unk_F8[1 + v5], 0);
    }

    return 0;
}

static void FootprintStampAnim_SplitXDraw(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSplitX *v0 = &param1->unk_94.val9;
    int v1;

    if (v0->unk_F6 != 0xff) {
        NNS_G3dGlbPolygonAttr(0, 0, 0, v0->unk_F6, v0->unk_F4 >> 8, 0);
        NNS_G3dMdlUseGlbPolygonID(param1->unk_0C.model);
        NNS_G3dMdlUseGlbAlpha(param1->unk_0C.model);
    }

    for (v1 = 0; v1 < 2; v1++) {
        Easy3DObject_Draw(&v0->unk_00[v1]);
    }

    Easy3DObject_Draw(&param1->unk_1C);
}

static BOOL FootprintStampAnim_SplitXCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimSplitX *v0 = &param1->unk_94.val9;
    FootprintStampAnimAppear *v1 = &param2->unk_94.val1;
    int v2;

    for (v2 = 0; v2 < 2 + 1; v2++) {
        if (FootprintStampModels_BoundsOverlap(&v0->unk_F8[v2], &v1->unk_04) == 1) {
            return 1;
        }
    }

    return 0;
}

static int FootprintStampAnim_SplitY(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSplitY *v0 = &param1->unk_94.val10;
    fx32 v1, v2, v3;
    fx32 v4;
    int v5;

    switch (v0->unk_F7) {
    case 0:
        v0->unk_F6 = FootprintStampModels_AllocSlot(param0);

        Easy3DObject_GetPosition(&param1->unk_1C, &v1, &v2, &v3);

        for (v5 = 0; v5 < 2; v5++) {
            Easy3DObject_Init(&v0->unk_00[v5], &param1->unk_0C);
            Easy3DObject_SetPosition(&v0->unk_00[v5], v1, v2, v3);
            Easy3DObject_SetVisible(&v0->unk_00[v5], 1);
        }

        v0->unk_F4 = 31 << 8;
        v0->unk_F7++;
    case 1:
        if (v0->unk_F4 - 0xa0 < 0x100) {
            for (v5 = 0; v5 < 2; v5++) {
                Easy3DObject_SetVisible(&v0->unk_00[v5], 0);
            }

            Easy3DObject_SetVisible(&param1->unk_1C, 0);
            v0->unk_F7++;
            break;
        }

        v0->unk_F4 -= 0xa0;
        v0->unk_F0 += 0x20000;

        if (v0->unk_F0 >= (360 << FX32_SHIFT)) {
            v0->unk_F0 -= 360 << FX32_SHIFT;
        }

        v4 = FX_Mul(CalcSineDegrees_FX32(v0->unk_F0), 0x10000);

        Easy3DObject_GetPosition(&param1->unk_1C, &v1, &v2, &v3);

        for (v5 = 0; v5 < 2; v5++) {
            if (v5 & 1) {
                Easy3DObject_SetPosition(&v0->unk_00[v5], v1, v2 + v4, v3);
            } else {
                Easy3DObject_SetPosition(&v0->unk_00[v5], v1, v2 - v4, v3);
            }
        }
        break;
    default:
        FootprintStampModels_FreeSlot(param0, v0->unk_F6);
        return 1;
    }

    FootprintStampModels_ComputeBounds(&param1->unk_1C, &param1->unk_00, &v0->unk_F8[0], 0);

    for (v5 = 0; v5 < 2; v5++) {
        FootprintStampModels_ComputeBounds(&v0->unk_00[v5], &param1->unk_00, &v0->unk_F8[1 + v5], 0);
    }

    return 0;
}

static void FootprintStampAnim_SplitYDraw(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimSplitY *v0 = &param1->unk_94.val10;
    int v1;

    if (v0->unk_F6 != 0xff) {
        NNS_G3dGlbPolygonAttr(0, 0, 0, v0->unk_F6, v0->unk_F4 >> 8, 0);
        NNS_G3dMdlUseGlbPolygonID(param1->unk_0C.model);
        NNS_G3dMdlUseGlbAlpha(param1->unk_0C.model);
    }

    for (v1 = 0; v1 < 2; v1++) {
        Easy3DObject_Draw(&v0->unk_00[v1]);
    }

    Easy3DObject_Draw(&param1->unk_1C);
}

static BOOL FootprintStampAnim_SplitYCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimSplitY *v0 = &param1->unk_94.val10;
    FootprintStampAnimAppear *v1 = &param2->unk_94.val1;
    int v2;

    for (v2 = 0; v2 < 2 + 1; v2++) {
        if (FootprintStampModels_BoundsOverlap(&v0->unk_F8[v2], &v1->unk_04) == 1) {
            return 1;
        }
    }

    return 0;
}

static int FootprintStampAnim_Stretch(FootprintStampModelManager *param0, FootprintStampModel *param1)
{
    FootprintStampAnimStretch *v0 = &param1->unk_94.val11;
    fx32 v1, v2, v3;
    fx32 v4;

    switch (v0->unk_06) {
    case 0:
        v0->unk_00 = FX32_ONE;
        v0->unk_06++;
    case 1:
        v0->unk_04++;

        if (v0->unk_04 > 30) {
            return 1;
        }

        v0->unk_00 += 0x180;
        Easy3DObject_SetScale(&param1->unk_1C, FX32_ONE, v0->unk_00, FX32_ONE);

        v4 = -(FX32_ONE * 2 / 2 * (v0->unk_00 - FX32_ONE) / FX32_ONE);
        Easy3DObject_GetPosition(&param1->unk_1C, &v1, &v2, &v3);
        Easy3DObject_SetPosition(&param1->unk_1C, v1, v2 + v4, v3);

        break;
    }

    FootprintStampModels_ComputeBounds(&param1->unk_1C, &param1->unk_00, &v0->unk_08, 1);
    return 0;
}

static BOOL FootprintStampAnim_StretchCollide(FootprintStampModelManager *param0, FootprintStampModel *param1, FootprintStampModel *param2)
{
    FootprintStampAnimStretch *v0 = &param1->unk_94.val11;
    FootprintStampAnimAppear *v1 = &param2->unk_94.val1;

    if (FootprintStampModels_BoundsOverlap(&v0->unk_08, &v1->unk_04) == 1) {
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

    switch (param1->unk_00) {
    case 0:
        param1->unk_02 += 0x200;

        if (param1->unk_02 >= 0x800) {
            param1->unk_02 = 0x800;
            param1->unk_00++;
        }

        param0->unk_740 = 1;
        param0->unk_742 = (param1->unk_02 >> 8) * v0;
        break;
    case 1:
        param1->unk_02 -= 0x200;

        if (param1->unk_02 <= 0) {
            param1->unk_02 = 0;
            param1->unk_01++;

            if (param1->unk_01 < 2) {
                param1->unk_00 = 0;
            } else {
                param1->unk_00++;
            }
        }

        param0->unk_740 = 1;
        param0->unk_742 = (param1->unk_02 >> 8) * v0;
        break;
    default:
        param0->unk_73E = 1;
        return 1;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_ZoomIn(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimZoomIn *v0 = &param1->unk_00;

    switch (v0->unk_06) {
    case 0:
        v0->unk_00 = Camera_GetDistance(camera);
        v0->unk_06++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        Camera_AdjustDistance(((-FX32_ONE * 50) / 30), camera);
        v0->unk_04++;

        if (v0->unk_04 >= 30) {
            v0->unk_04 = 0;
            v0->unk_06++;
        }
        break;
    case 2:
        v0->unk_04++;

        if (v0->unk_04 > 4) {
            v0->unk_04 = 0;
            v0->unk_06++;
        }
        break;
    case 3:
        Camera_AdjustDistance((-(-FX32_ONE * 50) / 6), camera);
        v0->unk_04++;

        if ((v0->unk_04 >= 6) || (Camera_GetDistance(camera) >= v0->unk_00)) {
            Camera_SetDistance(v0->unk_00, camera);
            return 1;
        }

        break;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_Shake(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimShake *v0 = &param1->unk_08;
    fx32 v1;

    switch (v0->unk_0C) {
    case 0:
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
        v0->unk_0C++;
    case 1:
        v0->unk_0D++;
        v1 = FX32_ONE * 4 / 16 * v0->unk_0D;

        if (v1 < FX32_ONE * 2) {
            v0->unk_00.y = FX32_ONE - v1;
        } else {
            v0->unk_00.y = -FX32_ONE + (v1 - FX32_ONE * 2);
        }

        if (v1 < FX32_ONE * 1) {
            v0->unk_00.x = v1;
        } else if (v1 < FX32_ONE * 2) {
            v0->unk_00.x = FX32_ONE - (v1 - FX32_ONE);
        } else if (v1 < FX32_ONE * 3) {
            v0->unk_00.x = -(v1 - FX32_ONE * 2);
        } else {
            v0->unk_00.x = -FX32_ONE + (v1 - FX32_ONE * 3);
        }

        if (v0->unk_0D >= 16) {
            v0->unk_00.y = FX32_ONE;
            v0->unk_00.x = 0;
            v0->unk_0D = 0;
            v0->unk_0E++;

            if (v0->unk_0E >= 2) {
                v0->unk_0C++;
            }
        }

        Camera_SetUp(&v0->unk_00, camera);
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_RotateLeft(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimRotateLeft *v0 = &param1->unk_18;
    CameraAngle v1 = { 0, 0, 0, 0 };

    switch (v0->unk_0E) {
    case 0:
        v0->cameraAngle = Camera_GetAngle(camera);
        v0->unk_08 = v0->cameraAngle.y;
        v0->unk_0E++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        v1.y += (-0x2000 / 2);
        v0->unk_08 += (-0x2000 / 2);
        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->unk_08 <= v0->cameraAngle.y - 0x2000) {
            v0->unk_0E++;
        }
        break;
    case 2:
        v0->unk_0C++;

        if (v0->unk_0C >= 16) {
            v0->unk_0E++;
        }
        break;
    case 3:
        v1.y += (0x2000 / 16);
        v0->unk_08 += (0x2000 / 16);

        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->unk_08 >= v0->cameraAngle.y) {
            Camera_SetAngleAroundTarget(&v0->cameraAngle, camera);
            return 1;
        }
        break;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_RotateRight(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimRotateRight *v0 = &param1->unk_28;
    CameraAngle v1 = { 0, 0, 0, 0 };

    switch (v0->unk_0E) {
    case 0:
        v0->cameraAngle = Camera_GetAngle(camera);
        v0->unk_08 = v0->cameraAngle.y;
        v0->unk_0E++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        v1.y += (0x2000 / 2);
        v0->unk_08 += (0x2000 / 2);
        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->unk_08 >= v0->cameraAngle.y + 0x2000) {
            v0->unk_0E++;
        }
        break;
    case 2:
        v0->unk_0C++;

        if (v0->unk_0C >= 16) {
            v0->unk_0E++;
        }
        break;
    case 3:
        v1.y += (-0x2000 / 16);
        v0->unk_08 += (-0x2000 / 16);

        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->unk_08 <= v0->cameraAngle.y) {
            Camera_SetAngleAroundTarget(&v0->cameraAngle, camera);
            return 1;
        }
        break;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_TiltUp(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimTiltUp *v0 = &param1->unk_38;
    CameraAngle v1 = { 0, 0, 0, 0 };

    switch (v0->unk_0E) {
    case 0:
        v0->cameraAngle = Camera_GetAngle(camera);
        v0->unk_08 = v0->cameraAngle.x;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
        v0->unk_0E++;
    case 1:
        v1.x += (0x2000 / 3);
        v0->unk_08 += (0x2000 / 3);

        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->unk_08 >= v0->cameraAngle.x + 0x2000) {
            v0->unk_0E++;
        }

        break;
    case 2:
        v0->unk_0C++;

        if (v0->unk_0C >= 16) {
            v0->unk_0E++;
        }
        break;
    case 3:
        v1.x += (-0x2000 / 16);
        v0->unk_08 += (-0x2000 / 16);

        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->unk_08 <= v0->cameraAngle.x) {
            Camera_SetAngleAroundTarget(&v0->cameraAngle, camera);
            return 1;
        }

        break;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_Spin(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimSpin *v0 = &param1->unk_48;
    fx32 v1;
    CameraAngle v2 = { 0, 0, 0, 0 };

    switch (v0->unk_0D) {
    case 0:
        v0->cameraAngle = Camera_GetAngle(camera);
        v0->unk_0D++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        v0->unk_08 += 0x18000;

        if (v0->unk_08 >= (360 << FX32_SHIFT)) {
            v0->unk_08 -= 360 << FX32_SHIFT;
            v0->unk_0C++;

            if (v0->unk_0C >= 2) {
                v0->unk_0D++;
                v0->unk_08 = 0;
            }
        }

        v1 = FX_Mul(CalcSineDegrees_FX32(v0->unk_08), 0x1000);
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
    FootprintStampCameraAnimZoomOut *v0 = &param1->unk_58;

    switch (v0->unk_06) {
    case 0:
        v0->unk_00 = Camera_GetDistance(camera);
        v0->unk_06++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        Camera_AdjustDistance(((FX32_ONE * 50) / 30), camera);
        v0->unk_04++;

        if (v0->unk_04 >= 30) {
            v0->unk_04 = 0;
            v0->unk_06++;
        }
        break;
    case 2:
        v0->unk_04++;

        if (v0->unk_04 > 4) {
            v0->unk_04 = 0;
            v0->unk_06++;
        }
        break;
    case 3:
        Camera_AdjustDistance((-(FX32_ONE * 50) / 6), camera);
        v0->unk_04++;

        if ((v0->unk_04 >= 6) || (Camera_GetDistance(camera) <= v0->unk_00)) {
            Camera_SetDistance(v0->unk_00, camera);
            return 1;
        }

        break;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_SwayX(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimSwayX *v0 = &param1->unk_60;
    VecFx32 v1 = { 0, 0, 0 };
    fx32 v2;

    switch (v0->unk_1D) {
    case 0:
        v0->unk_0C = Camera_GetPosition(camera);
        v0->unk_00 = Camera_GetTarget(camera);
        v0->unk_1D++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        v0->unk_18 += 0x20000;

        if (v0->unk_18 >= (360 << FX32_SHIFT)) {
            v0->unk_18 -= 360 << FX32_SHIFT;
            v0->unk_1C++;

            if (v0->unk_1C >= 4) {
                v0->unk_1D++;
                v0->unk_18 = 0;
            }
        }

        v2 = FX_Mul(CalcSineDegrees_FX32(v0->unk_18), 0x10000);
        v1.x = v2;

        Camera_SetTarget(&v0->unk_00, camera);
        Camera_SetPosition(&v0->unk_0C, camera);
        Camera_Move(&v1, camera);
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_SwayY(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimSwayY *v0 = &param1->unk_80;
    VecFx32 v1 = { 0, 0, 0 };
    fx32 v2;

    switch (v0->unk_1D) {
    case 0:
        v0->unk_0C = Camera_GetPosition(camera);
        v0->unk_00 = Camera_GetTarget(camera);
        v0->unk_1D++;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        v0->unk_18 += 0x20000;

        if (v0->unk_18 >= (360 << FX32_SHIFT)) {
            v0->unk_18 -= 360 << FX32_SHIFT;
            v0->unk_1C++;

            if (v0->unk_1C >= 4) {
                v0->unk_1D++;
                v0->unk_18 = 0;
            }
        }

        v2 = FX_Mul(CalcSineDegrees_FX32(v0->unk_18), 0x8000);
        v1.y = v2;

        Camera_SetTarget(&v0->unk_00, camera);
        Camera_SetPosition(&v0->unk_0C, camera);
        Camera_Move(&v1, camera);
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL FootprintStampCameraAnim_TiltDown(FootprintStampModelManager *param0, FootprintStampCameraAnimData *param1, Camera *camera)
{
    FootprintStampCameraAnimTiltDown *v0 = &param1->unk_A0;
    CameraAngle v1 = { 0, 0, 0, 0 };

    switch (v0->unk_0E) {
    case 0:
        v0->cameraAngle = Camera_GetAngle(camera);
        v0->unk_08 = v0->cameraAngle.x;
        v0->unk_0E++;

        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    case 1:
        v1.x += (-0x2000 / 3);
        v0->unk_08 += (-0x2000 / 3);

        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->unk_08 <= v0->cameraAngle.x - 0x2000) {
            v0->unk_0E++;
        }
        break;
    case 2:
        v0->unk_0C++;

        if (v0->unk_0C >= 16) {
            v0->unk_0E++;
        }
        break;
    case 3:
        v1.x += (0x2000 / 16);
        v0->unk_08 += (0x2000 / 16);

        Camera_AdjustAngleAroundTarget(&v1, camera);

        if (v0->unk_08 >= v0->cameraAngle.x) {
            Camera_SetAngleAroundTarget(&v0->cameraAngle, camera);
            return 1;
        }

        break;
    }

    return 0;
}
