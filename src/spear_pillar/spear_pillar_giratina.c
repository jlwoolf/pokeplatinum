#include "spear_pillar/spear_pillar_giratina.h"

#include <nitro.h>
#include <string.h>

#include "constants/species.h"

#include "spear_pillar/spear_pillar_sprite.h"
#include "spear_pillar/spear_pillar_object_anim.h"
#include "spear_pillar/spear_pillar_common.h"
#include "spear_pillar/spear_pillar_screen.h"
#include "spear_pillar/struct_spear_pillar_giratina.h"
#include "spear_pillar/struct_spear_pillar.h"
#include "spear_pillar/struct_spear_pillar_object_anim_step.h"

#include "bg_window.h"
#include "camera.h"
#include "easy3d_object.h"
#include "graphics.h"
#include "heap.h"
#include "math_util.h"
#include "narc.h"
#include "palette.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "sys_task.h"
#include "text.h"
#include "trainer_info.h"
#include "g3_buffer.h"

static void SpearPillarGiratina_LoadGraphics(SpearPillarGiratina *param0);
static void SpearPillarGiratina_FreeSprites(SpearPillarGiratina *param0);
static void SpearPillarGiratina_InitSprites(SpearPillarGiratina *param0);
static void SpearPillarGiratina_DrawFrame(SpearPillarGiratina *param0);
static void SpearPillarGiratina_InitCamera(Camera *camera, VecFx32 *param1);

static SpearPillarObjectAnimStep sSpearPillarGiratinaAnim0[] = {
    { 0x6, 0x4, 0x0 },
    { 0x0, 0x1 }
};

static SpearPillarObjectAnimStep sSpearPillarGiratinaAnim1[] = {
    { 0x6, 0x4, 0x0 },
    { 0x5, 0x4, 0x0 },
    { 0x0, 0x1 }
};

static SpearPillarObjectAnimStep sSpearPillarGiratinaAnim2[] = {
    { 0x1, 0x2, -(FX32_HALF >> 1) },
    { 0x0, 0x1 }
};

static SpearPillarObjectAnimStep sSpearPillarGiratinaAnim3[] = {
    { 0x9, 0x2, -(FX32_HALF >> 1) },
    { 0x0, 0x1 }
};

static void SpearPillarGiratina_InitCamera(Camera *camera, VecFx32 *param1)
{
    CameraAngle v0 = { -0x29fe, 0, 0 };

    Camera_InitWithTarget(param1, 0x13c805, &v0, 0xc01, 0, 1, camera);
    Camera_SetAsActive(camera);
    Camera_SetClipping(FX32_ONE * 10, FX32_ONE * 1008, camera);
}

static void SpearPillarGiratina_LoadGraphics(SpearPillarGiratina *param0)
{
    NARC *v0 = param0->context->narc;
    BgConfig *v1 = param0->context->bgConfig;
    SpriteSystem *v2 = param0->context->spriteSystem;
    SpriteManager *v3 = param0->context->spriteManager;
    PaletteData *v4 = param0->context->paletteData;
    int v5 = 50000;

    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 18, v1, 5, 0, 0, 0, HEAP_ID_111);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 20, v1, 5, 0, 0, 0, HEAP_ID_111);
    PaletteData_LoadBufferFromFileStart(v4, NARC_INDEX_ARC__DEMO_TENGAN_GRA, 19, HEAP_ID_111, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 2, 0);
    PaletteData_LoadBufferFromFileStart(v4, NARC_INDEX_ARC__DEMO_TENGAN_GRA, 19, HEAP_ID_111, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * 2, 0);

    SpriteSystem_LoadPaletteBufferFromOpenNarc(v4, PLTTBUF_SUB_OBJ, v2, v3, v0, 50, FALSE, 3, NNS_G2D_VRAM_TYPE_2DSUB, v5);
    SpriteSystem_LoadCellResObjFromOpenNarc(v2, v3, v0, 48, FALSE, v5);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v2, v3, v0, 47, FALSE, v5);
    SpriteSystem_LoadCharResObjFromOpenNarc(v2, v3, v0, 49, FALSE, NNS_G2D_VRAM_TYPE_2DSUB, v5);

    SpearPillar_LoadObject(&param0->objects.background, 46, param0->context->narc);

    {
        int v6;

        for (v6 = 0; v6 < 4; v6++) {
            SpearPillar_LoadObject(&param0->objects.shadows[v6], 65, param0->context->narc);
            Easy3DObject_SetScale(&param0->objects.shadows[v6].object, FX32_CONST(1.2), FX32_CONST(1.0), FX32_CONST(1.2));
        }
    }

    SpearPillar_LoadObject(&param0->objects.rift, 24, param0->context->narc);
    SpearPillar_LoadObjectAnim(0, &param0->objects.rift, 22, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.rift, 23, param0->context->narc, &param0->context->allocator);

    SpearPillar_LoadObject(&param0->objects.portal, 53, param0->context->narc);
    SpearPillar_LoadObjectAnim(0, &param0->objects.portal, 51, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.portal, 52, param0->context->narc, &param0->context->allocator);

    SpearPillar_LoadObject(&param0->objects.shadowRift, 55, param0->context->narc);
    SpearPillar_LoadObjectAnim(0, &param0->objects.shadowRift, 54, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.shadowRift, 56, param0->context->narc, &param0->context->allocator);

    SpearPillar_LoadObject(&param0->objects.dialgaPalkia[0], 66, param0->context->narc);
    Easy3DObject_SetPosition(&param0->objects.dialgaPalkia[0].object, FX32_CONST(-50), FX32_CONST(+0), FX32_CONST(-50));
    SpearPillar_LoadObjectAnim(0, &param0->objects.dialgaPalkia[0], 67, param0->context->narc, &param0->context->allocator);

    param0->objects.dialgaPalkia[0].isAnimating = 1;
    param0->objects.dialgaPalkia[0].useAnimation = 1;
    param0->objects.dialgaPalkia[0].animSpeed = FX32_HALF;

    SpearPillar_LoadObject(&param0->objects.dialgaPalkia[1], 68, param0->context->narc);
    Easy3DObject_SetPosition(&param0->objects.dialgaPalkia[1].object, FX32_CONST(+50), FX32_CONST(+0), FX32_CONST(-50));
    SpearPillar_LoadObjectAnim(0, &param0->objects.dialgaPalkia[1], 69, param0->context->narc, &param0->context->allocator);

    param0->objects.dialgaPalkia[1].isAnimating = 1;
    param0->objects.dialgaPalkia[1].useAnimation = 1;
    param0->objects.dialgaPalkia[1].animSpeed = FX32_HALF;

    SpearPillar_LoadObject(&param0->objects.legendaries[0], 26, param0->context->narc);
    Easy3DObject_SetPosition(&param0->objects.legendaries[0].object, FX32_CONST(0), FX32_CONST(-90), FX32_CONST(0));
    Easy3DObject_SetVisible(&param0->objects.legendaries[0].object, 0);
    SpearPillar_LoadObjectAnim(0, &param0->objects.legendaries[0], 25, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.legendaries[0], 27, param0->context->narc, &param0->context->allocator);

    param0->objects.legendaries[0].loopAnim1 = 1;

    SpearPillar_LoadObject(&param0->objects.legendaries[1], 29, param0->context->narc);
    Easy3DObject_SetVisible(&param0->objects.legendaries[1].object, 0);
    SpearPillar_LoadObjectAnim(0, &param0->objects.legendaries[1], 28, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.legendaries[1], 30, param0->context->narc, &param0->context->allocator);

    param0->objects.legendaries[1].loopAnim1 = 1;

    SpearPillar_LoadObject(&param0->objects.legendaries[2], 32, param0->context->narc);
    Easy3DObject_SetVisible(&param0->objects.legendaries[2].object, 0);
    SpearPillar_LoadObjectAnim(0, &param0->objects.legendaries[2], 31, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.legendaries[2], 33, param0->context->narc, &param0->context->allocator);

    param0->objects.legendaries[2].loopAnim1 = 1;

    SpearPillar_LoadObject(&param0->objects.legendaries[3], 35, param0->context->narc);
    Easy3DObject_SetVisible(&param0->objects.legendaries[3].object, 0);
    SpearPillar_LoadObjectAnim(0, &param0->objects.legendaries[3], 34, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.legendaries[3], 36, param0->context->narc, &param0->context->allocator);

    param0->objects.legendaries[3].loopAnim1 = 1;

    SpearPillar_LoadObject(&param0->objects.legendaries[4], 38, param0->context->narc);
    Easy3DObject_SetVisible(&param0->objects.legendaries[4].object, 0);
    SpearPillar_LoadObjectAnim(0, &param0->objects.legendaries[4], 37, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.legendaries[4], 39, param0->context->narc, &param0->context->allocator);

    param0->objects.legendaries[4].loopAnim1 = 1;

    SpearPillar_LoadObject(&param0->objects.portals[0], 41, param0->context->narc);
    Easy3DObject_SetVisible(&param0->objects.portals[0].object, 0);
    SpearPillar_LoadObjectAnim(0, &param0->objects.portals[0], 40, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObject(&param0->objects.portals[1], 42, param0->context->narc);
    Easy3DObject_SetVisible(&param0->objects.portals[1].object, 0);

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

static void SpearPillarGiratina_InitSprites(SpearPillarGiratina *param0)
{
    int v0;
    NARC *v1 = param0->context->narc;
    BgConfig *v2 = param0->context->bgConfig;
    SpriteSystem *v3 = param0->context->spriteSystem;
    SpriteManager *v4 = param0->context->spriteManager;
    PaletteData *v5 = param0->context->paletteData;
    SpriteTemplate v6;

    v6.x = 0;
    v6.y = 0;
    v6.z = 0;
    v6.animIdx = 0;
    v6.priority = 0;
    v6.plttIdx = 0;
    v6.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    v6.bgPriority = 0;
    v6.vramTransfer = FALSE;

    v6.resources[4] = SPRITE_RESOURCE_NONE;
    v6.resources[5] = SPRITE_RESOURCE_NONE;

    v6.resources[0] = 50000;
    v6.resources[1] = 50000;
    v6.resources[2] = 50000;
    v6.resources[3] = 50000;

    for (v0 = 0; v0 < 3; v0++) {
        param0->sprites.pokemonSprites[v0].sprite = SpriteSystem_NewSprite(v3, v4, &v6);

        ManagedSprite_TickFrame(param0->sprites.pokemonSprites[v0].sprite);
        ManagedSprite_SetAffineOverwriteMode(param0->sprites.pokemonSprites[v0].sprite, AFFINE_OVERWRITE_MODE_DOUBLE);
        ManagedSprite_SetAffineScale(param0->sprites.pokemonSprites[v0].sprite, 0.5f, 0.5f);
        ManagedSprite_SetExplicitPaletteOffset(param0->sprites.pokemonSprites[v0].sprite, v0);
        ManagedSprite_SetPositionXY(param0->sprites.pokemonSprites[v0].sprite, 16 + (v0 * 64), 64);

        param0->sprites.pokemonSprites[v0].state = 1;
        param0->sprites.pokemonSprites[v0].index = v0;
        param0->sprites.pokemonSprites[v0].yPos = 50;
        param0->sprites.pokemonSprites[v0].orbitAngle = v0 * 120;
        param0->sprites.pokemonSprites[v0].wobbleAngle = param0->sprites.pokemonSprites[v0].orbitAngle;
        param0->sprites.pokemonSprites[v0].jitterRange = v0;
        param0->sprites.pokemonSprites[v0].params[0] = 1;
        param0->sprites.pokemonSprites[v0].params[1] = 1;
        param0->sprites.pokemonSprites[v0].params[2] = LCRNG_Next() % 10;
        param0->sprites.pokemonSprites[v0].params[3] = 0;
        param0->sprites.pokemonSprites[v0].task = SysTask_Start(SpearPillarSprite_Task, &param0->sprites.pokemonSprites[v0], 4096);
    }
}

static void SpearPillarGiratina_FreeSprites(SpearPillarGiratina *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        SysTask_Done(param0->sprites.pokemonSprites[v0].task);
        Sprite_DeleteAndFreeResources(param0->sprites.pokemonSprites[v0].sprite);
    }
}

void *SpearPillarGiratina_Init(SpearPillar *param0)
{
    SpearPillarGiratina *v0 = Heap_Alloc(HEAP_ID_111, sizeof(SpearPillarGiratina));

    memset(v0, 0, sizeof(SpearPillarGiratina));

    v0->context = &param0->context;
    v0->taskArgs = param0->taskArgs;

    SpearPillarGiratina_LoadGraphics(v0);
    SpearPillarGiratina_InitSprites(v0);

    {
        SpearPillarScreen_InitScroll(&v0->sprites.screenScroll, HEAP_ID_111);
        SpearPillarScreen_Scroll(&v0->sprites.screenScroll, 0, 191, (0xffff / 192) * 2, FX32_CONST(4), 1 * 100, REG_DB_BG1HOFS_ADDR, 0, 0x1000, 1);
    }

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

    SpearPillarGiratina_InitCamera(v0->context->camera, &v0->context->cameraTarget);
    v0->context->cameraTarget.y = FX32_CONST(0);

    SpearPillar_Set3DScreen(1);
    SpearPillar_SetBrightness(param0, +16);

    return v0;
}

BOOL SpearPillarGiratina_Main(void *param0)
{
    SpearPillarGiratina *v0 = (SpearPillarGiratina *)param0;

    switch (v0->state) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_WHITE, 6, 1, HEAP_ID_111);
        v0->context->blend.brightness = 0;
        G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
        G2S_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
        v0->state++;
    case 1:
        if (IsScreenFadeDone() == FALSE) {
            break;
        }
        v0->state++;
        break;
    case 2: {
        v0->context->cameraAnim.angleDeltaX = 20;
        v0->context->cameraAnim.angleDeltaY = 0;
        v0->context->cameraAnim.angleDeltaZ = 0;
        v0->context->cameraAnim.duration = 60;
        v0->context->cameraAnim.camera = v0->context->camera;
        v0->context->cameraAnim.posDeltaX = 0;
        v0->context->cameraAnim.posDeltaY = 0;
        v0->context->cameraAnim.posDeltaZ = 0;
        v0->context->cameraAnim.targetPos = &v0->context->cameraTarget;

        SpearPillar_StartCameraAnim(&v0->context->cameraAnim);
        v0->state++;
    } break;
    case 3:
        if (SpearPillar_UpdateCameraAnim(&v0->context->cameraAnim)) {
            SpearPillar_PrintMessage(v0->context, v0->taskArgs, 20);
            v0->state++;
        }
        break;
    case 4:
        if (Text_IsPrinterActive(v0->context->textPrinter)) {
            break;
        }

        SpearPillar_EraseMessage(v0->context);
        v0->state++;
        break;
    case 5: {
        v0->context->cameraAnim.angleDeltaX = 0;
        v0->context->cameraAnim.angleDeltaY = 0;
        v0->context->cameraAnim.angleDeltaZ = 0;
        v0->context->cameraAnim.duration = 60;
        v0->context->cameraAnim.camera = v0->context->camera;
        v0->context->cameraAnim.posDeltaX = 0;
        v0->context->cameraAnim.posDeltaY = 0;
        v0->context->cameraAnim.posDeltaZ = FX32_CONST(70);
        v0->context->cameraAnim.targetPos = &v0->context->cameraTarget;
        SpearPillar_StartCameraAnim(&v0->context->cameraAnim);
        v0->state++;
    } break;
    case 6:
        if (SpearPillar_UpdateCameraAnim(&v0->context->cameraAnim) == 0) {
            break;
        }

        if (++v0->frameCounter < 10) {
            break;
        }

        SpearPillar_PrintMessage(v0->context, v0->taskArgs, 21);
        SpearPillarObject_StartAnim(&v0->objects.characters[1], sSpearPillarGiratinaAnim0);

        v0->state++;
        v0->frameCounter = 0;
        break;
    case 7:
        if (Text_IsPrinterActive(v0->context->textPrinter)) {
            break;
        }

        SpearPillar_EraseMessage(v0->context);
        SpearPillar_PrintMessage(v0->context, v0->taskArgs, 22);
        Sound_FadeOutBGM(0, 10);
        v0->state++;
        break;
    case 8:
        if (Text_IsPrinterActive(v0->context->textPrinter)) {
            break;
        }

        SpearPillar_EraseMessage(v0->context);
        v0->frameCounter++;

        if (v0->frameCounter == 15) {
            {
                int v1;

                for (v1 = 0; v1 < 3; v1++) {
                    v0->sprites.pokemonSprites[v1].state %= 2;
                    v0->sprites.pokemonSprites[v1].state += 2;
                }
            }
        }

        if (v0->frameCounter < 30) {
            break;
        }

        if (v0->frameCounter == 31) {
            (void)0;
        }

        if (v0->context->blend.brightness > -6) {
            if (v0->frameCounter % 2) {
                v0->context->blend.brightness--;
            }

            G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
            G2S_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
        } else {
            SpearPillar_PrintMessage(v0->context, v0->taskArgs, 23);

            v0->frameCounter = 0;
            v0->state++;
        }
        break;
    case 9:
        if (Text_IsPrinterActive(v0->context->textPrinter)) {
            break;
        }

        SpearPillar_EraseMessage(v0->context);
        SpearPillarObject_StartAnim(&v0->objects.characters[1], sSpearPillarGiratinaAnim1);

        {
            v0->context->cameraAnim.angleDeltaX = 0;
            v0->context->cameraAnim.angleDeltaY = 0;
            v0->context->cameraAnim.angleDeltaZ = 0;
            v0->context->cameraAnim.duration = 90;
            v0->context->cameraAnim.camera = v0->context->camera;
            v0->context->cameraAnim.posDeltaX = 0;
            v0->context->cameraAnim.posDeltaY = 0;
            v0->context->cameraAnim.posDeltaZ = -FX32_CONST(80);
            v0->context->cameraAnim.targetPos = &v0->context->cameraTarget;
            SpearPillar_StartCameraAnim(&v0->context->cameraAnim);
            v0->state++;
        }
        break;
    case 10:
        if (SpearPillar_UpdateCameraAnim(&v0->context->cameraAnim) == 0) {
            break;
        }

        v0->state++;
        v0->frameCounter = 0;
        break;
    case 11:
        v0->objects.portals[0].isAnimating = 1;
        Easy3DObject_SetVisible(&v0->objects.portals[0].object, 1);
        Sound_PlayBGM(SEQ_PL_EV_GIRA_sseq);
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_SUB_63, SEQ_NONE, 0);
        v0->state++;
        break;
    case 12:
        if ((++v0->frameCounter) == 60) {
            SpearPillarObject_StartAnim(&v0->objects.characters[1], sSpearPillarGiratinaAnim2);
        }

        if ((v0->frameCounter == 15) || (v0->frameCounter == 45) || (v0->frameCounter == 75) || (v0->frameCounter == 95) || (v0->frameCounter == 115) || (v0->frameCounter == 130) || (v0->frameCounter == 145)) {
            Sound_PlayEffect(SEQ_SE_PL_W060_sseq);
            Sound_SetPitchForSequence(1477, 0xffff, (v0->frameCounter / 30 * 32) + (v0->frameCounter % 32 * 10));
        }

        if (v0->objects.portals[0].isAnimating == 0) {
            Easy3DObject_SetVisible(&v0->objects.portals[0].object, 0);
            Easy3DObject_SetVisible(&v0->objects.portals[1].object, 1);
            Easy3DObject_SetVisible(&v0->objects.legendaries[0].object, 1);

            v0->objects.legendaries[0].isAnimating = 1;
            v0->frameCounter = 0;
            v0->state++;
        }
        break;
    case 13:
        if (v0->objects.legendaries[0].object.position.y < FX32_CONST(-50)) {
            v0->objects.legendaries[0].object.position.y += FX32_HALF;
        } else {
            v0->frameCounter = 0;
            v0->state++;
        }
        break;
    case 14:
        if (v0->objects.legendaries[0].isAnimating == 0) {
            v0->objects.legendaries[1].object.position.y = v0->objects.legendaries[0].object.position.y;
            v0->objects.legendaries[1].isAnimating = 1;
            v0->objects.legendaries[1].useAnimation = 1;
            v0->objects.rift.isAnimating = 1;
            v0->objects.rift.updateAnim1 = 1;
            v0->objects.shadowRift.isAnimating = 1;
            v0->objects.shadowRift.loopAnim1 = 1;

            Easy3DObject_SetVisible(&v0->objects.legendaries[0].object, 0);
            Easy3DObject_SetVisible(&v0->objects.legendaries[1].object, 1);

            v0->state++;
        }
        break;
    case 15:
        v0->frameCounter++;

        if (v0->frameCounter == 1) {
            Sound_PlayEffect(SEQ_SE_PL_W082C_sseq);
        }

        if (v0->frameCounter == 20) {
            SpearPillarObject_StartAnim(&v0->objects.characters[1], sSpearPillarGiratinaAnim3);
        }

        if (v0->frameCounter == 15 + 25) {
            Sound_PlayPokemonCryEx(POKECRY_NORMAL, SPECIES_DIALGA, -80, 40, HEAP_ID_111, 0);
        }

        if (v0->frameCounter == 40 + 25) {
            Sound_PlayPokemonCryEx(POKECRY_NORMAL, SPECIES_PALKIA, +80, 40, HEAP_ID_111, 0);
        }

        if (v0->frameCounter < 15 + 25) {
            v0->objects.dialgaPalkia[0].object.position.z -= FX32_HALF >> 1;
        } else {
            v0->objects.dialgaPalkia[0].object.position.z -= FX32_HALF;
        }

        if (v0->frameCounter < 40 + 25) {
            v0->objects.dialgaPalkia[1].object.position.z -= FX32_HALF >> 1;
        } else {
            v0->objects.dialgaPalkia[1].object.position.z -= FX32_HALF;
        }

        if (v0->objects.legendaries[1].object.position.y < FX32_CONST(0)) {
            v0->objects.legendaries[1].object.position.y += FX32_HALF;
        } else {
            v0->objects.legendaries[1].object.position.y = FX32_CONST(0);
            v0->frameCounter = 0;
            SpearPillar_PrintMessage(v0->context, v0->taskArgs, 24);
            v0->state++;
        }
        break;
    case 16:
        if (Text_IsPrinterActive(v0->context->textPrinter)) {
            break;
        }

        SpearPillar_EraseMessage(v0->context);

        v0->objects.portal.isAnimating = 1;
        v0->objects.portal.useAnimation = 0;
        v0->objects.portal.updateAnim1 = 1;
        v0->objects.legendaries[2].isAnimating = 1;

        Easy3DObject_SetVisible(&v0->objects.legendaries[1].object, 0);
        Easy3DObject_SetVisible(&v0->objects.legendaries[2].object, 1);
        Sound_PlayPokemonCryEx(POKECRY_FIELD_EVENT, SPECIES_GIRATINA, 0, 127, HEAP_ID_111, 0);

        v0->frameCounter = 0;
        v0->state++;
        break;
    case 17:
        if (v0->objects.legendaries[2].isAnimating == 0) {
            SpearPillar_PrintMessage(v0->context, v0->taskArgs, 25);

            v0->objects.legendaries[3].isAnimating = 1;
            v0->objects.legendaries[3].useAnimation = 1;
            v0->objects.portal.isAnimating = 0;

            Easy3DObject_SetVisible(&v0->objects.portal.object, 0);
            Easy3DObject_SetVisible(&v0->objects.legendaries[2].object, 0);
            Easy3DObject_SetVisible(&v0->objects.legendaries[3].object, 1);

            v0->state++;
        }
        break;
    case 18:
        if (Text_IsPrinterActive(v0->context->textPrinter)) {
            break;
        }

        if (v0->frameCounter == 0) {
            SpearPillar_EraseMessage(v0->context);
        }

        Sound_PlayBGM(SEQ_PL_EV_GIRA2_sseq);

        v0->objects.legendaries[4].isAnimating = 1;

        Easy3DObject_SetVisible(&v0->objects.legendaries[3].object, 0);
        Easy3DObject_SetVisible(&v0->objects.legendaries[4].object, 1);
        v0->frameCounter = 0;
        v0->state++;
        break;
    case 19:
        if ((++v0->frameCounter) == 238) {
            Sound_PlayPokemonCryEx(POKECRY_FIELD_EVENT, SPECIES_GIRATINA, 0, 127, HEAP_ID_111, 0);
        }

        if (v0->frameCounter == 170) {
            SpearPillar_PrintMessage(v0->context, v0->taskArgs, 26);
        }

        if (v0->frameCounter == 180) {
            (void)0;
        }

        if (v0->frameCounter == 210) {
            (void)0;
        }

        if (v0->frameCounter == 220) {
            (void)0;
        }

        if (v0->frameCounter == 230) {
            (void)0;
        }

        if (v0->objects.legendaries[4].isAnimating == 0) {
            if (Text_IsPrinterActive(v0->context->textPrinter)) {
                Text_RemovePrinter(v0->context->textPrinter);
            }

            v0->context->blend.brightness = -16;

            G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
            G2S_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);

            {
                u16 currentBGM = Sound_GetCurrentBGM();

                Sound_StopBGM(currentBGM, 0);
            }

            SpearPillar_EraseMessage(v0->context);

            v0->state++;
            v0->frameCounter = 0;
        }
        break;
    case 20:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 1, 1, HEAP_ID_111);
        v0->state++;
    case 21:
        if (IsScreenFadeDone() == FALSE) {
            break;
        }

        v0->context->blend.brightness = 0;
        G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
        G2S_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
        v0->state++;
        break;
    default:
        if ((++v0->frameCounter) >= 60) {
            v0->state = 0;
            return 0;
        }

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

    SpearPillarGiratina_DrawFrame(v0);
    SpearPillar_BlendBg(v0->context);

    return 1;
}

BOOL SpearPillarGiratina_Exit(void *param0)
{
    SpearPillarGiratina *v0 = (SpearPillarGiratina *)param0;

    switch (v0->state) {
    case 0:
        SpearPillarGiratina_FreeSprites(v0);
        SpearPillarScreen_FreeScroll(&v0->sprites.screenScroll);
        v0->state++;
        break;
    case 1:
        SpearPillar_FreeObject(&v0->objects.background, &v0->context->allocator, 0);

        {
            int v1;

            for (v1 = 0; v1 < 4; v1++) {
                SpearPillar_FreeObject(&v0->objects.shadows[v1], &v0->context->allocator, 0);
            }
        }

        SpearPillar_FreeObject(&v0->objects.rift, &v0->context->allocator, 2);
        SpearPillar_FreeObject(&v0->objects.portal, &v0->context->allocator, 2);
        SpearPillar_FreeObject(&v0->objects.shadowRift, &v0->context->allocator, 2);

        SpearPillar_FreeObject(&v0->objects.dialgaPalkia[0], &v0->context->allocator, 1);
        SpearPillar_FreeObject(&v0->objects.dialgaPalkia[1], &v0->context->allocator, 1);

        SpearPillar_FreeObject(&v0->objects.legendaries[0], &v0->context->allocator, 2);
        SpearPillar_FreeObject(&v0->objects.legendaries[1], &v0->context->allocator, 2);
        SpearPillar_FreeObject(&v0->objects.legendaries[2], &v0->context->allocator, 2);
        SpearPillar_FreeObject(&v0->objects.legendaries[3], &v0->context->allocator, 2);
        SpearPillar_FreeObject(&v0->objects.legendaries[4], &v0->context->allocator, 2);

        SpearPillar_FreeObject(&v0->objects.portals[0], &v0->context->allocator, 1);
        SpearPillar_FreeObject(&v0->objects.portals[1], &v0->context->allocator, 0);

        SpearPillar_FreeObject(&v0->objects.characters[0], &v0->context->allocator, 1);
        SpearPillar_FreeObject(&v0->objects.characters[1], &v0->context->allocator, 1);

        v0->state++;
        break;
    default:
        Heap_Free(v0);
        return 0;
    }

    return 1;
}

static void SpearPillarGiratina_DrawFrame(SpearPillarGiratina *param0)
{
    G3_ResetG3X();
    Camera_ComputeViewMatrix();

    SpearPillar_SetupLighting(param0->context);
    SpearPillar_UpdateCamera(param0->context);

    SpearPillar_DrawObject(&param0->objects.background);
    SpearPillar_DrawObject(&param0->objects.rift);
    SpearPillar_DrawObject(&param0->objects.portal);
    SpearPillar_DrawObject(&param0->objects.shadowRift);

    SpearPillar_DrawObject(&param0->objects.portals[0]);
    SpearPillar_DrawObject(&param0->objects.portals[1]);

    SpearPillar_DrawObject(&param0->objects.legendaries[0]);
    SpearPillar_DrawObject(&param0->objects.legendaries[1]);
    SpearPillar_DrawObject(&param0->objects.legendaries[2]);
    SpearPillar_DrawObject(&param0->objects.legendaries[3]);
    SpearPillar_DrawObject(&param0->objects.legendaries[4]);

    SpearPillar_DrawObject(&param0->objects.dialgaPalkia[0]);
    SpearPillar_DrawObject(&param0->objects.dialgaPalkia[1]);

    SpearPillar_DrawObject(&param0->objects.characters[0]);
    SpearPillar_DrawObject(&param0->objects.characters[1]);

    SpearPillar_DrawObject(&param0->objects.shadows[0]);
    SpearPillar_DrawObject(&param0->objects.shadows[1]);
    SpearPillar_DrawObject(&param0->objects.shadows[2]);
    SpearPillar_DrawObject(&param0->objects.shadows[3]);

    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);
}
