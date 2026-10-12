#include "spear_pillar/spear_pillar_lake_trio.h"

#include <nitro.h>
#include <string.h>

#include "spear_pillar/spear_pillar_sprite.h"
#include "spear_pillar/spear_pillar_common.h"
#include "spear_pillar/spear_pillar_screen.h"
#include "spear_pillar/struct_spear_pillar_lake_trio.h"
#include "spear_pillar/struct_spear_pillar.h"
#include "spear_pillar/struct_spear_pillar_capture_config.h"

#include "bg_window.h"
#include "camera.h"
#include "easy3d_object.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "math_util.h"
#include "narc.h"
#include "palette.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "sys_task.h"
#include "g3_buffer.h"

static void SpearPillarLakeTrio_LoadGraphics(SpearPillarLakeTrio *param0);
static void SpearPillarLakeTrio_FreeSprites(SpearPillarLakeTrio *param0);
static void SpearPillarLakeTrio_InitSprites(SpearPillarLakeTrio *param0);
static void SpearPillarLakeTrio_DrawFrame(SpearPillarLakeTrio *param0);
static void SpearPillarLakeTrio_InitCamera(Camera *camera, VecFx32 *param1);

void *SpearPillarLakeTrio_Init(SpearPillar *param0)
{
    SpearPillarLakeTrio *v0 = Heap_Alloc(HEAP_ID_111, sizeof(SpearPillarLakeTrio));

    memset(v0, 0, sizeof(SpearPillarLakeTrio));

    v0->context = &param0->context;
    v0->taskArgs = param0->taskArgs;

    SpearPillarLakeTrio_LoadGraphics(v0);
    SpearPillarLakeTrio_InitSprites(v0);

    {
        SpearPillarScreen_InitScroll(&v0->sprites.screenScroll, HEAP_ID_111);
        SpearPillarScreen_Scroll(&v0->sprites.screenScroll, 0, 191, (0xffff / 192) * 2, FX32_CONST(2), 1 * 100, REG_DB_BG1HOFS_ADDR, 0, 0x1000, 1);
    }
    {
        SpearPillarCaptureConfig v1 = {
            GX_DISPMODE_VRAM_C,
            GX_BGMODE_0,
            GX_BG0_AS_3D,
            GX_CAPTURE_SIZE_256x192,
            GX_CAPTURE_MODE_AB,
            GX_CAPTURE_SRCA_3D,
            GX_CAPTURE_SRCB_VRAM_0x00000,
            GX_CAPTURE_DEST_VRAM_C_0x00000,
            4,
            12,
            111
        };
    }

    SpearPillarLakeTrio_InitCamera(v0->context->camera, &v0->context->cameraTarget);
    v0->context->cameraTarget.y += FX32_CONST(25);

    G2S_BlendNone();
    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 7, 8);

    SpearPillar_Set3DScreen(1);
    Sound_FadeOutBGM(0, 10);

    return v0;
}

BOOL SpearPillarLakeTrio_Main(void *param0)
{
    SpearPillarLakeTrio *v0 = param0;
    static const u16 v1[] = {
        210,
        120,
        120,
    };
    static const u16 v2[] = {
        145,
        119,
        100,
    };
    static const u16 v3[] = {
        100,
        19,
        18,
    };
    static const u32 v4[] = {
        480,
        481,
        482,
    };

    switch (v0->state) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_111);
        v0->state++;
    case 1:
        if (IsScreenFadeDone() == FALSE) {
            break;
        }

        Sound_SetSceneAndPlayBGM(SOUND_SCENE_18, SEQ_D_RYAYHY_sseq, 0);
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_SUB_63, SEQ_NONE, 0);
        v0->state = 2;
        break;
    case 2:
        Easy3DObject_SetVisible(&v0->objects.lakeTrio[v0->index].object, 1);
        v0->objects.lakeTrio[v0->index].isAnimating = 1;
        v0->objects.lakeTrio[v0->index].updateAnim1 = 1;
        v0->state++;
        v0->frameCounter = 0;
        break;
    case 3:
        if (v0->frameCounter == v3[v0->index]) {
            Sound_PlayEffect(SEQ_SE_PL_W392_sseq);
        }

        if (v0->frameCounter == v2[v0->index]) {
            Sound_PlayPokemonCryEx(POKECRY_NORMAL, v4[v0->index], 0, 100, HEAP_ID_111, 0);
        }

        if ((++v0->frameCounter) >= v1[v0->index]) {
            v0->context->blend.brightness = 0;
            v0->frameCounter = 0;
            v0->state++;
        }
        break;
    case 4:
        if ((++v0->context->blend.brightness) != (+16)) {
            G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
        } else {
            v0->sprites.pokemonSprites[v0->index].followTarget = 1;
            Easy3DObject_SetVisible(&v0->objects.lakeTrio[v0->index].object, 0);
            v0->state++;

            v0->index++;

            if (v0->index >= 3) {
                v0->context->blend.brightness = 0;
                v0->state = 6;
            }
        }
        break;
    case 5:
        if ((--v0->context->blend.brightness) > 0) {
            G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
        } else {
            v0->state = 2;
        }
        break;
    case 6:
        if ((++v0->frameCounter) < 30 * 4) {
            break;
        }

        if ((++v0->context->blend.brightness) != (+16)) {
            G2S_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, v0->context->blend.brightness);
        } else {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_WHITE, 1, 1, HEAP_ID_111);
            v0->state = 0;
            return 0;
        }
    }

    SpearPillarLakeTrio_DrawFrame(v0);
    SpearPillar_BlendBgByScene(v0->context, v0->index);

    return 1;
}

BOOL SpearPillarLakeTrio_Exit(void *param0)
{
    SpearPillarLakeTrio *v0 = param0;

    switch (v0->state) {
    case 0:
        SpearPillarScreen_FreeScroll(&v0->sprites.screenScroll);
        SpearPillarLakeTrio_FreeSprites(v0);

        v0->state++;
        break;
    case 1:
        SpearPillar_FreeObject(&v0->objects.lakeTrio[0], &v0->context->allocator, 2);
        SpearPillar_FreeObject(&v0->objects.lakeTrio[1], &v0->context->allocator, 2);
        SpearPillar_FreeObject(&v0->objects.lakeTrio[2], &v0->context->allocator, 2);
        SpearPillar_FreeObject(&v0->objects.background, &v0->context->allocator, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
        v0->state++;
        break;
    default:
        Heap_Free(v0);
        return 0;
    }

    return 1;
}

static void SpearPillarLakeTrio_InitCamera(Camera *camera, VecFx32 *param1)
{
    CameraAngle v0 = { 1274, 0, 0 };

    Camera_InitWithTarget(param1, FX32_CONST(200), &v0, 0xa66, 0, 1, camera);
    Camera_ComputeProjectionMatrix(0, camera);
    Camera_SetAsActive(camera);
    Camera_SetClipping(FX32_CONST(0.1), FX32_CONST(2048), camera);
}

static void SpearPillarLakeTrio_DrawFrame(SpearPillarLakeTrio *param0)
{
    G3_ResetG3X();
    Camera_ComputeViewMatrix();

    SpearPillar_SetupLighting(param0->context);
    SpearPillar_UpdateCamera(param0->context);

    SpearPillar_DrawObject(&param0->objects.lakeTrio[0]);
    SpearPillar_DrawObject(&param0->objects.lakeTrio[1]);
    SpearPillar_DrawObject(&param0->objects.lakeTrio[2]);
    SpearPillar_DrawObject(&param0->objects.background);

    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);
}

static void SpearPillarLakeTrio_LoadGraphics(SpearPillarLakeTrio *param0)
{
    NARC *v0 = param0->context->narc;
    BgConfig *v1 = param0->context->bgConfig;
    SpriteSystem *v2 = param0->context->spriteSystem;
    SpriteManager *v3 = param0->context->spriteManager;
    PaletteData *v4 = param0->context->paletteData;
    int v5 = 50000;

    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 70, v1, 5, 0, 0, 0, HEAP_ID_111);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 72, v1, 5, 0, 0, 0, HEAP_ID_111);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 73, v1, 4, 0, 0, 0, HEAP_ID_111);
    PaletteData_LoadBufferFromFileStart(v4, NARC_INDEX_ARC__DEMO_TENGAN_GRA, 71, HEAP_ID_111, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 2, 0);

    {
        const u16 v6[] = { 0x421 };
        PaletteData_LoadBuffer(v4, &v6, 0, 0, 0x2);
    }

    SpriteSystem_LoadPaletteBufferFromOpenNarc(v4, PLTTBUF_SUB_OBJ, v2, v3, v0, 50, FALSE, 3, NNS_G2D_VRAM_TYPE_2DSUB, v5);
    SpriteSystem_LoadCellResObjFromOpenNarc(v2, v3, v0, 48, FALSE, v5);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v2, v3, v0, 47, FALSE, v5);
    SpriteSystem_LoadCharResObjFromOpenNarc(v2, v3, v0, 49, FALSE, NNS_G2D_VRAM_TYPE_2DSUB, v5);

    SpearPillar_LoadObject(&param0->objects.background, 60, param0->context->narc);

    SpearPillar_LoadObject(&param0->objects.lakeTrio[0], 59, param0->context->narc);
    SpearPillar_LoadObjectAnim(0, &param0->objects.lakeTrio[0], 57, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.lakeTrio[0], 58, param0->context->narc, &param0->context->allocator);

    SpearPillar_LoadObject(&param0->objects.lakeTrio[1], 45, param0->context->narc);
    SpearPillar_LoadObjectAnim(0, &param0->objects.lakeTrio[1], 43, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.lakeTrio[1], 44, param0->context->narc, &param0->context->allocator);

    SpearPillar_LoadObject(&param0->objects.lakeTrio[2], 17, param0->context->narc);
    SpearPillar_LoadObjectAnim(0, &param0->objects.lakeTrio[2], 15, param0->context->narc, &param0->context->allocator);
    SpearPillar_LoadObjectAnim(1, &param0->objects.lakeTrio[2], 16, param0->context->narc, &param0->context->allocator);

    Easy3DObject_SetVisible(&param0->objects.lakeTrio[0].object, 1);
    Easy3DObject_SetVisible(&param0->objects.lakeTrio[1].object, 0);
    Easy3DObject_SetVisible(&param0->objects.lakeTrio[2].object, 0);
}

static void SpearPillarLakeTrio_FreeSprites(SpearPillarLakeTrio *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        SysTask_Done(param0->sprites.pokemonSprites[v0].task);
        SysTask_Done(param0->sprites.shadowSprites[v0].task);
        Sprite_DeleteAndFreeResources(param0->sprites.pokemonSprites[v0].sprite);
        Sprite_DeleteAndFreeResources(param0->sprites.shadowSprites[v0].sprite);
    }
}

static void SpearPillarLakeTrio_InitSprites(SpearPillarLakeTrio *param0)
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
    v6.bgPriority = 2;
    v6.vramTransfer = FALSE;

    v6.resources[4] = SPRITE_RESOURCE_NONE;
    v6.resources[5] = SPRITE_RESOURCE_NONE;

    v6.resources[0] = 50000;
    v6.resources[1] = 50000;
    v6.resources[2] = 50000;
    v6.resources[3] = 50000;

    for (v0 = 0; v0 < 3; v0++) {
        param0->sprites.shadowSprites[v0].sprite = SpriteSystem_NewSprite(v3, v4, &v6);

        ManagedSprite_TickFrame(param0->sprites.shadowSprites[v0].sprite);
        ManagedSprite_SetDrawFlag(param0->sprites.shadowSprites[v0].sprite, 0);
        ManagedSprite_SetExplicitPaletteOffset(param0->sprites.shadowSprites[v0].sprite, v0);
        ManagedSprite_SetPositionXY(param0->sprites.shadowSprites[v0].sprite, 0, 0);

        param0->sprites.shadowSprites[v0].state = 1;
        param0->sprites.shadowSprites[v0].index = v0;
        param0->sprites.shadowSprites[v0].yPos = 50;
        param0->sprites.shadowSprites[v0].orbitAngle = v0 * 120;
        param0->sprites.shadowSprites[v0].wobbleAngle = param0->sprites.shadowSprites[v0].orbitAngle;
        param0->sprites.shadowSprites[v0].jitterRange = 0;
        param0->sprites.shadowSprites[v0].params[0] = 1;
        param0->sprites.shadowSprites[v0].params[1] = 1;
        param0->sprites.shadowSprites[v0].params[2] = LCRNG_Next() % 10;
        param0->sprites.shadowSprites[v0].params[3] = 0;
        param0->sprites.shadowSprites[v0].task = SysTask_Start(SpearPillarSprite_ShadowTask, &param0->sprites.shadowSprites[v0], 4096 - 1);
    }

    for (v0 = 0; v0 < 3; v0++) {
        s16 v7[] = { 180, -20, 280 };
        s16 v8[] = { 128, 190, 150 };
        f32 v9[] = { 0.1f, 0.3f, 0.2f };

        if (v0 == 1) {
            v6.bgPriority = 0;
        } else {
            v6.bgPriority = 2;
        }

        param0->sprites.pokemonSprites[v0].sprite = SpriteSystem_NewSprite(v3, v4, &v6);
        param0->sprites.pokemonSprites[v0].targetSprite = param0->sprites.shadowSprites[v0].sprite;

        ManagedSprite_TickFrame(param0->sprites.pokemonSprites[v0].sprite);
        ManagedSprite_SetAffineOverwriteMode(param0->sprites.pokemonSprites[v0].sprite, AFFINE_OVERWRITE_MODE_DOUBLE);
        ManagedSprite_SetAffineScale(param0->sprites.pokemonSprites[v0].sprite, v9[v0], v9[v0]);
        ManagedSprite_SetExplicitPaletteOffset(param0->sprites.pokemonSprites[v0].sprite, v0);
        ManagedSprite_SetPositionXY(param0->sprites.pokemonSprites[v0].sprite, v7[v0], v8[v0]);

        param0->sprites.pokemonSprites[v0].state = 0;
        param0->sprites.pokemonSprites[v0].index = v0;
        param0->sprites.pokemonSprites[v0].yPos = 50;
        param0->sprites.pokemonSprites[v0].orbitAngle = v0 * 120;
        param0->sprites.pokemonSprites[v0].wobbleAngle = param0->sprites.pokemonSprites[v0].orbitAngle;
        param0->sprites.pokemonSprites[v0].jitterRange = 0;
        param0->sprites.pokemonSprites[v0].params[0] = 1;
        param0->sprites.pokemonSprites[v0].params[1] = 1;
        param0->sprites.pokemonSprites[v0].params[2] = LCRNG_Next() % 10;
        param0->sprites.pokemonSprites[v0].params[3] = 0;
        param0->sprites.pokemonSprites[v0].task = SysTask_Start(SpearPillarSprite_ShadowTask, &param0->sprites.pokemonSprites[v0], 4096);
    }
}
