#include "spear_pillar/spear_pillar_dialga_palkia.h"

#include <nitro.h>
#include <string.h>

#include "constants/heap.h"

#include "spear_pillar/spear_pillar_common.h"
#include "spear_pillar/spear_pillar_screen.h"
#include "spear_pillar/struct_spear_pillar_dialga_palkia.h"
#include "spear_pillar/struct_spear_pillar_dialga_palkia_camera_shake.h"
#include "spear_pillar/struct_spear_pillar_dialga_palkia_scale_task.h"
#include "spear_pillar/struct_spear_pillar.h"
#include "spear_pillar/struct_spear_pillar_capture_config.h"

#include "bg_window.h"
#include "camera.h"
#include "easy3d_object.h"
#include "graphics.h"
#include "heap.h"
#include "narc.h"
#include "palette.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "text.h"
#include "trainer_info.h"
#include "g3_buffer.h"

static void SpearPillarDialgaPalkia_LoadGraphics(SpearPillarDialgaPalkia *param0);
static void SpearPillarDialgaPalkia_FreeObjects(SpearPillarDialgaPalkia *param0);
static void SpearPillarDialgaPalkia_FreeSprites(SpearPillarDialgaPalkia *param0);
static void SpearPillarDialgaPalkia_InitCamera(Camera *camera, VecFx32 *param1);
static void SpearPillarDialgaPalkia_DrawFrame(SpearPillarDialgaPalkia *param0);
void *SpearPillarDialgaPalkia_Init(SpearPillar *param0);
BOOL SpearPillarDialgaPalkia_Main(void *param0);
BOOL SpearPillarDialgaPalkia_Exit(void *param0);

static void SpearPillarDialgaPalkia_LoadPoketchGraphics(BgConfig *param0, PaletteData *param1)
{
    Graphics_LoadTilesToBgLayer(NARC_INDEX_GRAPHIC__POKETCH, 10, param0, 4, 0, 0, 1, HEAP_ID_111);
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_GRAPHIC__POKETCH, 11, param0, 4, 0, 0, 1, HEAP_ID_111);
    PaletteData_LoadBufferFromFileStart(param1, NARC_INDEX_GRAPHIC__POKETCH, 12, HEAP_ID_111, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES, 0);
}

static void SpearPillarDialgaPalkia_InitSprites(SpearPillarDialgaPalkia *param0)
{
    NARC *v0 = param0->context->narc;
    BgConfig *v1 = param0->context->bgConfig;
    SpriteSystem *v2 = param0->context->spriteSystem;
    SpriteManager *v3 = param0->context->spriteManager;
    PaletteData *v4 = param0->context->paletteData;

    SpearPillar_LoadObject(&param0->objects.legendaries[0], 84, param0->context->narc);
    SpearPillar_LoadObjectAnim(0, &param0->objects.legendaries[0], 82, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.legendaries[0], 83, param0->context->narc, &param0->context->allocator);
    Easy3DObject_SetPosition(&param0->objects.legendaries[0].object, FX32_CONST(-48), FX32_CONST(-5), FX32_CONST(-70));

    param0->objects.legendaries[0].isAnimating = 0;

    SpearPillar_CloneObject(&param0->objects.legendaries[0], &param0->objects.legendaries[1], 84, param0->context->narc);
    SpearPillar_CloneObjectAnim(0, &param0->objects.legendaries[0], &param0->objects.legendaries[1], 82, param0->context->narc, &param0->context->allocator);
    SpearPillar_CloneObjectAnim(1, &param0->objects.legendaries[0], &param0->objects.legendaries[1], 83, param0->context->narc, &param0->context->allocator);
    Easy3DObject_SetPosition(&param0->objects.legendaries[1].object, FX32_CONST(+48), FX32_CONST(-5), FX32_CONST(-70));

    param0->objects.legendaries[1].isAnimating = 0;
    param0->objects.legendaries[0].scale = FX32_CONST(0.1);
    param0->objects.legendaries[1].scale = FX32_CONST(0.1);

    Easy3DObject_SetScale(&param0->objects.legendaries[0].object, param0->objects.legendaries[0].scale, FX32_CONST(1.0), param0->objects.legendaries[0].scale);
    Easy3DObject_SetScale(&param0->objects.legendaries[1].object, param0->objects.legendaries[1].scale, FX32_CONST(1.0), param0->objects.legendaries[1].scale);
}

static void SpearPillarDialgaPalkia_LoadGraphics(SpearPillarDialgaPalkia *param0)
{
    NARC *v0 = param0->context->narc;
    BgConfig *v1 = param0->context->bgConfig;
    SpriteSystem *v2 = param0->context->spriteSystem;
    SpriteManager *v3 = param0->context->spriteManager;
    PaletteData *v4 = param0->context->paletteData;

    SpearPillar_LoadObject(&param0->objects.background, 46, param0->context->narc);
    SpearPillar_LoadObject(&param0->objects.rift, 24, param0->context->narc);
    SpearPillar_LoadObjectAnim(0, &param0->objects.rift, 22, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.rift, 23, param0->context->narc, &param0->context->allocator);

    SpearPillar_LoadObject(&param0->objects.portals[0], 79, param0->context->narc);
    SpearPillar_LoadObjectAnim(0, &param0->objects.portals[0], 77, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.portals[0], 78, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(2, &param0->objects.portals[0], 80, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(3, &param0->objects.portals[0], 81, param0->context->narc, &param0->context->allocator);
    Easy3DObject_SetPosition(&param0->objects.portals[0].object, FX32_CONST(-48), FX32_CONST(-10), FX32_CONST(-70));

    param0->objects.portals[0].isAnimating = 0;
    param0->objects.portals[0].updateAllAnims = 0;

    SpearPillar_LoadObject(&param0->objects.portals[1], 79, param0->context->narc);
    SpearPillar_LoadObjectAnim(0, &param0->objects.portals[1], 77, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.portals[1], 78, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(2, &param0->objects.portals[1], 80, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(3, &param0->objects.portals[1], 81, param0->context->narc, &param0->context->allocator);
    Easy3DObject_SetPosition(&param0->objects.portals[1].object, FX32_CONST(+48), FX32_CONST(-10), FX32_CONST(-70));

    param0->objects.portals[1].isAnimating = 0;
    param0->objects.portals[1].updateAllAnims = 0;

    {
        int v5;

        for (v5 = 0; v5 < 4; v5++) {
            SpearPillar_LoadObject(&param0->objects.shadows[v5], 65, param0->context->narc);

            Easy3DObject_SetScale(&param0->objects.shadows[v5].object, FX32_CONST(1.2), FX32_CONST(1.0), FX32_CONST(1.2));
        }
    }

    SpearPillar_LoadObject(&param0->objects.dialgaPalkia[0], 66, param0->context->narc);
    Easy3DObject_SetPosition(&param0->objects.dialgaPalkia[0].object, FX32_CONST(-50), FX32_CONST(+0), FX32_CONST(-50));
    SpearPillar_LoadObjectAnim(0, &param0->objects.dialgaPalkia[0], 67, param0->context->narc, &param0->context->allocator);

    param0->objects.dialgaPalkia[0].isAnimating = 1;
    param0->objects.dialgaPalkia[0].useAnimation = 1;
    param0->objects.dialgaPalkia[0].animSpeed = FX32_HALF;

    Easy3DObject_SetVisible(&param0->objects.dialgaPalkia[0].object, 0);
    Easy3DObject_SetVisible(&param0->objects.shadows[0].object, 0);

    SpearPillar_LoadObject(&param0->objects.dialgaPalkia[1], 68, param0->context->narc);
    Easy3DObject_SetPosition(&param0->objects.dialgaPalkia[1].object, FX32_CONST(+50), FX32_CONST(+0), FX32_CONST(-50));
    SpearPillar_LoadObjectAnim(0, &param0->objects.dialgaPalkia[1], 69, param0->context->narc, &param0->context->allocator);

    param0->objects.dialgaPalkia[1].isAnimating = 1;
    param0->objects.dialgaPalkia[1].useAnimation = 1;
    param0->objects.dialgaPalkia[1].animSpeed = FX32_HALF;

    Easy3DObject_SetVisible(&param0->objects.dialgaPalkia[1].object, 0);
    Easy3DObject_SetVisible(&param0->objects.shadows[1].object, 0);

    if (TrainerInfo_Gender(param0->taskArgs->trainerInfo) != 1) {
        SpearPillar_LoadObject(&param0->objects.characters[0], 61, param0->context->narc);
        SpearPillar_LoadObjectAnim(0, &param0->objects.characters[0], 62, param0->context->narc, &param0->context->allocator);
    } else {
        SpearPillar_LoadObject(&param0->objects.characters[0], 63, param0->context->narc);
        SpearPillar_LoadObjectAnim(0, &param0->objects.characters[0], 64, param0->context->narc, &param0->context->allocator);
    }

    Easy3DObject_SetPosition(&param0->objects.characters[0].object, FX32_CONST(1), FX32_CONST(+0), FX32_CONST(+140));

    param0->objects.characters[0].useAnimation = 1;
    param0->objects.characters[0].animSpeed = (FX32_HALF >> 1);
    param0->objects.characters[0].animID = 2;

    SpearPillar_LoadObject(&param0->objects.characters[1], 13, param0->context->narc);
    Easy3DObject_SetPosition(&param0->objects.characters[1].object, FX32_CONST(1), FX32_CONST(+0), FX32_CONST(+60));
    SpearPillar_LoadObjectAnim(0, &param0->objects.characters[1], 14, param0->context->narc, &param0->context->allocator);

    param0->objects.characters[1].useAnimation = 1;
    param0->objects.characters[1].animSpeed = (FX32_HALF >> 1);
    param0->objects.characters[1].animID = 2;
}

static void SpearPillarDialgaPalkia_FreeObjects(SpearPillarDialgaPalkia *param0)
{
    SpearPillar_FreeObject(&param0->objects.background, &param0->context->allocator, 0);

    {
        int v0;

        for (v0 = 0; v0 < 4; v0++) {
            SpearPillar_FreeObject(&param0->objects.shadows[v0], &param0->context->allocator, 0);
        }
    }

    SpearPillar_FreeObject(&param0->objects.rift, &param0->context->allocator, 2);

    SpearPillar_FreeObject(&param0->objects.dialgaPalkia[0], &param0->context->allocator, 1);
    SpearPillar_FreeObject(&param0->objects.dialgaPalkia[1], &param0->context->allocator, 1);

    SpearPillar_FreeObject(&param0->objects.legendaries[0], &param0->context->allocator, 2);
    SpearPillar_FreeObject(&param0->objects.legendaries[1], &param0->context->allocator, 2);

    SpearPillar_FreeObject(&param0->objects.characters[0], &param0->context->allocator, 1);
    SpearPillar_FreeObject(&param0->objects.characters[1], &param0->context->allocator, 1);
}

static void SpearPillarDialgaPalkia_FreeSprites(SpearPillarDialgaPalkia *param0)
{
    SpearPillar_FreeObject(&param0->objects.portals[0], &param0->context->allocator, 4);
    SpearPillar_FreeObject(&param0->objects.portals[1], &param0->context->allocator, 4);

    param0->objects.portals[0].isLoaded = 0;
    param0->objects.portals[1].isLoaded = 0;
}

static void SpearPillarDialgaPalkia_InitCamera(Camera *camera, VecFx32 *param1)
{
    CameraAngle v0 = { -0x29fe, 0, 0 };

    Camera_InitWithTarget(param1, 0x13c805, &v0, 0xc01, 0, 1, camera);
    Camera_SetAsActive(camera);
    Camera_SetClipping(FX32_ONE * 10, FX32_ONE * 1008, camera);
}

static void SpearPillarDialgaPalkia_DrawFrame(SpearPillarDialgaPalkia *param0)
{
    G3_ResetG3X();
    Camera_ComputeViewMatrix();

    SpearPillar_SetupLighting(param0->context);
    SpearPillar_UpdateCamera(param0->context);

    SpearPillar_DrawObject(&param0->objects.background);
    SpearPillar_DrawObject(&param0->objects.rift);

    SpearPillar_DrawObject(&param0->objects.dialgaPalkia[0]);
    SpearPillar_DrawObject(&param0->objects.dialgaPalkia[1]);

    SpearPillar_DrawObject(&param0->objects.portals[0]);
    SpearPillar_DrawObject(&param0->objects.portals[1]);

    SpearPillar_DrawObject(&param0->objects.legendaries[0]);
    SpearPillar_DrawObject(&param0->objects.legendaries[1]);

    SpearPillar_DrawObject(&param0->objects.characters[0]);
    SpearPillar_DrawObject(&param0->objects.characters[1]);

    SpearPillar_DrawObject(&param0->objects.shadows[0]);
    SpearPillar_DrawObject(&param0->objects.shadows[1]);
    SpearPillar_DrawObject(&param0->objects.shadows[2]);
    SpearPillar_DrawObject(&param0->objects.shadows[3]);

    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);
}

void *SpearPillarDialgaPalkia_Init(SpearPillar *param0)
{
    SpearPillarDialgaPalkia *v0 = Heap_Alloc(HEAP_ID_111, sizeof(SpearPillarDialgaPalkia));

    memset(v0, 0, sizeof(SpearPillarDialgaPalkia));

    v0->context = &param0->context;
    v0->taskArgs = param0->taskArgs;

    SpearPillarDialgaPalkia_LoadGraphics(v0);
    SpearPillarDialgaPalkia_LoadPoketchGraphics(v0->context->bgConfig, v0->context->paletteData);

    {
        G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 7, 8);
        G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, 7, 10);

        {
            static const GXRgb v1[8] = {
                GX_RGB(2, 2, 2),
                GX_RGB(10, 10, 10),
                GX_RGB(10, 10, 10),
                GX_RGB(10, 10, 10),
                GX_RGB(10, 10, 10),
                GX_RGB(10, 10, 10),
                GX_RGB(10, 10, 10),
                GX_RGB(10, 10, 10),
            };

            G3X_EdgeMarking(1);
            G3X_SetEdgeColorTable(v1);
        }
    }

    v0->context->cameraTarget.z = FX32_CONST(34);

    SpearPillarDialgaPalkia_InitCamera(v0->context->camera, &v0->context->cameraTarget);
    Sound_SetSceneAndPlayBGM(SOUND_SCENE_SUB_63, SEQ_NONE, 0);

    return v0;
}

static void SpearPillarDialgaPalkia_CameraShakeTask(SysTask *param0, void *param1)
{
    SpearPillarDialgaPalkiaCameraShake *v0 = param1;

    switch (v0->state) {
    case 0:
        v0->cameraAnim->duration = 2;

        if (v0->direction) {
            if ((v0->intensity == 4) || (v0->intensity == 6)) {
                v0->cameraAnim->posDeltaX = +FX32_CONST(2);
            } else if (v0->intensity == 5) {
                v0->cameraAnim->posDeltaX = +FX32_CONST(4);
            } else if (v0->intensity == 0xFF) {
                v0->cameraAnim->posDeltaX = +FX32_CONST(6);
            } else if (v0->intensity == 7) {
                v0->cameraAnim->posDeltaX = +FX32_CONST(2);
                v0->cameraAnim->duration = 4;
            }
        } else {
            if ((v0->intensity == 4) || (v0->intensity == 6)) {
                v0->cameraAnim->posDeltaX = -FX32_CONST(2);
            } else if (v0->intensity == 5) {
                v0->cameraAnim->posDeltaX = -FX32_CONST(4);
            } else if (v0->intensity == 0xFF) {
                v0->cameraAnim->posDeltaX = -FX32_CONST(6);
            } else if (v0->intensity == 7) {
                v0->cameraAnim->posDeltaX = -FX32_CONST(2);
                v0->cameraAnim->duration = 4;
            }
        }

        v0->direction ^= 1;
        v0->cameraAnim->posDeltaY = 0;
        v0->cameraAnim->posDeltaZ = 0;
        SpearPillar_StartCameraAnim(v0->cameraAnim);
        v0->state++;
    case 1:
        if (SpearPillar_UpdateCameraAnim(v0->cameraAnim)) {
            if (v0->intensity == 8) {
                v0->state++;
            } else {
                v0->state--;
            }
        }
        break;
    default:
        SysTask_Done(param0);
        break;
    }
}

static void SpearPillarDialgaPalkia_StartCameraShake(SpearPillarDialgaPalkia *param0)
{
    param0->context->cameraAnim.angleDeltaX = 0;
    param0->context->cameraAnim.angleDeltaY = 0;
    param0->context->cameraAnim.angleDeltaZ = 0;
    param0->context->cameraAnim.targetPos = &param0->context->cameraTarget;
    param0->context->cameraShake.cameraAnim = &param0->context->cameraAnim;
    param0->context->cameraShake.intensity = 0;

    SysTask_Start(SpearPillarDialgaPalkia_CameraShakeTask, &param0->context->cameraShake, 0x1000);
}

static void SpearPillarDialgaPalkia_ScaleTask(SysTask *param0, void *param1)
{
    SpearPillarDialgaPalkiaScaleTask *v0 = param1;
    f32 v1[] = {
        0.0f,
        0.3f,
        0.6f,
        1.0f,
        1.2f,
        1.1f,
        1.0f,
    };

    switch (v0->state) {
    case 0:
        Easy3DObject_SetScale(&v0->object->object, FX32_CONST(v1[v0->frameIndex]), FX32_CONST(1.00f), FX32_CONST(1.00f));
        Easy3DObject_SetScale(&v0->shadowObject->object, FX32_CONST(v1[v0->frameIndex]), FX32_CONST(1.00f), FX32_CONST(1.00f));

        v0->frameIndex++;

        Easy3DObject_SetVisible(&v0->object->object, 1);
        Easy3DObject_SetVisible(&v0->shadowObject->object, 1);

        v0->state++;
        break;
    case 1:
        if ((++v0->frameIndex) >= NELEMS(v1)) {
            Sound_PlayPokemonCryEx(POKECRY_NORMAL, v0->species, v0->pan, 80, HEAP_ID_111, 0);
            v0->state++;
        } else {
            Easy3DObject_SetScale(&v0->object->object, FX32_CONST(v1[v0->frameIndex]), FX32_CONST(1.00f), FX32_CONST(1.00f));
            Easy3DObject_SetScale(&v0->shadowObject->object, FX32_CONST(v1[v0->frameIndex]), FX32_CONST(1.00f), FX32_CONST(1.00f));
        }
        break;
    default:
        SysTask_Done(param0);
        break;
    }
}

static void SpearPillarDialgaPalkia_StartScaleTask(SpearPillarDialgaPalkia *param0, int param1, int param2)
{
    SpearPillarDialgaPalkiaScaleTask *v0 = &param0->scaleTasks[param1];

    v0->state = 0;
    v0->frameIndex = 0;
    v0->species = param2;
    v0->object = &param0->objects.dialgaPalkia[param1];
    v0->shadowObject = &param0->objects.shadows[param1];

    if (param1 == 0) {
        v0->pan = -80;
    } else {
        v0->pan = +80;
    }

    SysTask_Start(SpearPillarDialgaPalkia_ScaleTask, v0, 0x1000);
}

BOOL SpearPillarDialgaPalkia_Main(void *param0)
{
    SpearPillarDialgaPalkia *v0 = param0;

    switch (v0->state) {
    case 0:
        if (IsScreenFadeDone() == FALSE) {
            break;
        }

        v0->state++;
    case 1: {
        v0->context->cameraAnim.angleDeltaX = 0;
        v0->context->cameraAnim.angleDeltaY = 0;
        v0->context->cameraAnim.angleDeltaZ = 0;
        v0->context->cameraAnim.duration = 60;
        v0->context->cameraAnim.camera = v0->context->camera;
        v0->context->cameraAnim.posDeltaX = 0;
        v0->context->cameraAnim.posDeltaY = 0;
        v0->context->cameraAnim.posDeltaZ = -FX32_CONST(80 - 34);
        v0->context->cameraAnim.targetPos = &v0->context->cameraTarget;
        SpearPillar_StartCameraAnim(&v0->context->cameraAnim);
        v0->state++;
    }
    case 2:
        if (SpearPillar_UpdateCameraAnim(&v0->context->cameraAnim)) {
            v0->frameCounter = 0;
            v0->state++;
            SpearPillar_PrintMessage(v0->context, v0->taskArgs, 14);
        }
        break;
    case 3:
        if (Text_IsPrinterActive(v0->context->textPrinter)) {
            break;
        }

        SpearPillar_EraseMessage(v0->context);
        SpearPillar_PrintMessage(v0->context, v0->taskArgs, 16);
        v0->state++;
    case 4:
        if (Text_IsPrinterActive(v0->context->textPrinter)) {
            break;
        }

        {
            SpearPillarCaptureConfig v1 = {
                GX_DISPMODE_VRAM_C,
                GX_BGMODE_0,
                GX_BG0_AS_3D,
                GX_CAPTURE_SIZE_256x192,
                GX_CAPTURE_MODE_AB,
                GX_CAPTURE_SRCA_2D3D,
                GX_CAPTURE_SRCB_VRAM_0x00000,
                GX_CAPTURE_DEST_VRAM_C_0x00000,
                4,
                12,
                111
            };

            v0->context->capture = SpearPillarScreen_StartCapture(&v1);
        }

        SpearPillarDialgaPalkia_StartCameraShake(v0);
        SpearPillar_EraseMessage(v0->context);

        v0->objects.portals[0].isAnimating = 1;
        v0->objects.portals[0].updateAllAnims = 1;
        v0->state++;
    case 5:
        if ((++v0->frameCounter) >= 60) {
            v0->context->cameraShake.intensity = 4;
            v0->objects.portals[1].isAnimating = 1;
            v0->objects.portals[1].updateAllAnims = 1;
            v0->state++;
        }
        break;
    case 6:
        v0->frameCounter++;

        if (v0->frameCounter == 80) {
            Sound_PlayPannedEffect(SEQ_SE_DP_CLIMAX01_sseq, -70);
        }

        if (v0->frameCounter == 135) {
            Sound_PlayPannedEffect(SEQ_SE_DP_CLIMAX01_sseq, +70);
        }

        if ((v0->frameCounter == 310) || (v0->frameCounter == 375) || (v0->frameCounter == 432)) {
            Sound_PlayEffect(SEQ_SE_DP_CLIMAX06_sseq);
        }

        if ((v0->frameCounter == 284) || (v0->frameCounter == 338) || (v0->frameCounter == 406)) {
            Sound_PlayEffect(SEQ_SE_DP_CLIMAX09_sseq);
        }

        if (v0->frameCounter == 165) {
            Sound_PlayPannedEffect(SEQ_SE_DP_CLIMAX03_sseq, -70);
        }

        if (v0->frameCounter == 220) {
            Sound_PlayPannedEffect(SEQ_SE_DP_CLIMAX03_sseq, +70);
        }

        if (v0->frameCounter == 470) {
            Sound_PlayPannedEffect(SEQ_SE_DP_CLIMAX10_sseq, -70);
        }

        if (v0->frameCounter == 520) {
            Sound_PlayPannedEffect(SEQ_SE_DP_CLIMAX10_sseq, +70);
        }

        if (v0->frameCounter == 120) {
            v0->context->cameraShake.intensity = 5;
        }

        if (v0->frameCounter == 210) {
            v0->context->cameraShake.intensity = 0xFF;
        }

        if (v0->objects.portals[0].isAnimating == 0) {
            v0->context->cameraShake.intensity = 6;
            SpearPillarDialgaPalkia_StartScaleTask(v0, 0, 483);
            Sound_PlayPannedEffect(SEQ_SE_DP_CLIMAX12_sseq, -70);
            v0->state++;
        }
        break;
    case 7:
        if (v0->objects.portals[1].isAnimating == 0) {
            v0->context->cameraShake.intensity = 7;
            SpearPillarDialgaPalkia_StartScaleTask(v0, 1, 484);
            Sound_PlayPannedEffect(SEQ_SE_DP_CLIMAX12_sseq, +70);
            v0->state++;
            v0->frameCounter = 0;
        }
        break;
    case 8:
        if ((++v0->frameCounter) >= 30) {
            v0->frameCounter = 0;
            v0->state++;
        }
        break;
    case 9:
        v0->context->cameraShake.intensity = 8;

        if (v0->fadeUp == 0) {
            if (v0->context->blend.brightness < 8) {
                v0->context->blend.brightness += 1;
                G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
            } else {
                v0->fadeUp = 1;
            }
        } else {
            if (v0->context->blend.brightness > 0) {
                v0->context->blend.brightness -= 2;
                G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
            } else {
                v0->state++;
                v0->fadeUp = 0;
            }
        }
        break;
    case 10:
        if (v0->fadeUp == 0) {
            if (v0->context->blend.brightness < 12) {
                v0->context->blend.brightness += 1;
                G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
            } else {
                v0->fadeUp = 1;
            }
        } else {
            if (v0->context->blend.brightness > 0) {
                v0->context->blend.brightness -= 2;
                G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
            } else {
                v0->state++;
                v0->fadeUp = 0;
            }
        }
        break;
    case 11:
        if (v0->context->blend.brightness < (+16)) {
            v0->context->blend.brightness += 2;
            G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
        } else {
            SpearPillarDialgaPalkia_FreeSprites(v0);
            SpearPillarDialgaPalkia_InitSprites(v0);
            v0->state++;
        }
        break;
    case 12:
        if (v0->context->blend.brightness != 0) {
            v0->context->blend.brightness--;
            G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
        } else {
            {
                SpearPillarCaptureConfig v2 = {
                    GX_DISPMODE_VRAM_C, GX_BGMODE_0, GX_BG0_AS_3D, GX_CAPTURE_SIZE_256x192, GX_CAPTURE_MODE_AB, GX_CAPTURE_SRCA_2D3D, GX_CAPTURE_SRCB_VRAM_0x00000, GX_CAPTURE_DEST_VRAM_C_0x00000, 4, 12, 111
                };
            }

            v0->objects.legendaries[0].isAnimating = 1;
            v0->objects.legendaries[0].useAnimation = 1;
            v0->objects.legendaries[0].updateAnim1 = 1;
            v0->objects.legendaries[1].isAnimating = 1;
            v0->objects.legendaries[1].useAnimation = 1;
            v0->objects.legendaries[1].updateAnim1 = 1;
            v0->state++;
        }
        break;
    case 13:
        if (v0->objects.legendaries[0].scale < FX32_CONST(0.80)) {
            v0->objects.legendaries[0].scale += FX32_CONST(0.02);
            v0->objects.legendaries[1].scale += FX32_CONST(0.02);
            Easy3DObject_SetScale(&v0->objects.legendaries[0].object, v0->objects.legendaries[0].scale, FX32_CONST(1.0), v0->objects.legendaries[0].scale);
            Easy3DObject_SetScale(&v0->objects.legendaries[1].object, v0->objects.legendaries[1].scale, FX32_CONST(1.0), v0->objects.legendaries[1].scale);
        } else {
            SpearPillar_PrintMessage(v0->context, v0->taskArgs, 18);
            v0->state++;
        }
        break;
    case 14:
        if (Text_IsPrinterActive(v0->context->textPrinter)) {
            break;
        }

        SpearPillar_EraseMessage(v0->context);
        SpearPillar_PrintMessage(v0->context, v0->taskArgs, 19);

        v0->state++;
        break;
    case 15:
        if (Text_IsPrinterActive(v0->context->textPrinter)) {
            break;
        }

        if (v0->objects.legendaries[0].scale > FX32_CONST(0.10)) {
            v0->objects.legendaries[0].scale -= FX32_CONST(0.02);
            v0->objects.legendaries[1].scale -= FX32_CONST(0.02);
            Easy3DObject_SetScale(&v0->objects.legendaries[0].object, v0->objects.legendaries[0].scale, FX32_CONST(1.0), v0->objects.legendaries[0].scale);
            Easy3DObject_SetScale(&v0->objects.legendaries[1].object, v0->objects.legendaries[1].scale, FX32_CONST(1.0), v0->objects.legendaries[1].scale);
        } else {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_111);
            v0->state++;
        }
        break;
    case 16:
        if (IsScreenFadeDone() == FALSE) {
            break;
        }

        SpearPillar_EraseMessage(v0->context);
        v0->state++;
        break;
    case 17:
        v0->state = 0;
        v0->frameCounter = 0;
        return 0;
        break;
    }

    v0->objects.shadows[0].object.position = v0->objects.dialgaPalkia[0].object.position;
    v0->objects.shadows[1].object.position = v0->objects.dialgaPalkia[1].object.position;
    v0->objects.shadows[2].object.position = v0->objects.characters[0].object.position;
    v0->objects.shadows[3].object.position = v0->objects.characters[1].object.position;

    v0->objects.shadows[0].object.position.z -= (FX32_ONE * 2);
    v0->objects.shadows[1].object.position.z -= (FX32_ONE * 2);
    v0->objects.shadows[2].object.position.z -= (FX32_ONE * 2);
    v0->objects.shadows[3].object.position.z -= (FX32_ONE * 2);

    v0->objects.shadows[2].object.position.x -= FX32_ONE;
    v0->objects.shadows[3].object.position.x -= FX32_ONE;

    SpearPillarDialgaPalkia_DrawFrame(v0);

    return 1;
}

BOOL SpearPillarDialgaPalkia_Exit(void *param0)
{
    SpearPillarDialgaPalkia *v0 = param0;

    switch (v0->state) {
    case 0:
        SpearPillarDialgaPalkia_FreeObjects(v0);
        SpearPillarScreen_StopCapture(&v0->context->capture, GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_3D);
        v0->state++;
        break;
    default:
        Heap_Free(v0);
        return 0;
    }

    return 1;
}
