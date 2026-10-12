#include "spear_pillar/spear_pillar.h"

#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"

#include "spear_pillar/spear_pillar_lake_trio.h"
#include "spear_pillar/spear_pillar_giratina.h"
#include "spear_pillar/spear_pillar_dialga_palkia.h"
#include "spear_pillar/spear_pillar_common.h"
#include "spear_pillar/struct_spear_pillar_context.h"
#include "spear_pillar/struct_spear_pillar.h"

#include "bg_window.h"
#include "camera.h"
#include "g3d_pipeline.h"
#include "game_options.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "overlay_manager.h"
#include "palette.h"
#include "render_window.h"
#include "screen_fade.h"
#include "sound.h"
#include "sprite_system.h"
#include "system.h"
#include "vram_transfer.h"

FS_EXTERN_OVERLAY(spear_pillar);

typedef void *(*SpearPillarSceneInitFunc)(SpearPillar *);
typedef BOOL (*SpearPillarSceneMainFunc)(void *);
typedef BOOL (*SpearPillarSceneExitFunc)(void *);

static void SpearPillar_InitSpriteSystem(SpearPillarContext *param0);
static void SpearPillar_InitContext(SpearPillarContext *param0);
static void SpearPillar_FreeContext(SpearPillarContext *param0);
static void SpearPillar_InitBg(BgConfig *param0);
static void SpearPillar_VBlankCallback(void *param0);

int SpearPillar_Init(ApplicationManager *appMan, int *param1)
{
    SpearPillar *v0;

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_111, 0xC0000);

    v0 = ApplicationManager_NewData(appMan, sizeof(SpearPillar), HEAP_ID_111);
    memset(v0, 0, sizeof(SpearPillar));
    v0->taskArgs = ApplicationManager_Args(appMan);

    SpearPillar_InitContext(&v0->context);
    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6 * 2, 1, HEAP_ID_111);
    SetVBlankCallback(SpearPillar_VBlankCallback, v0);

    v0->context.blend.unk_00 = 31;
    v0->context.blend.unk_01 = 31;
    v0->context.blend.unk_02 = 31;
    v0->context.blendLevel = 31;

    Sound_Set2PokemonCriesAllowed(1);

    {
        Window *v1 = &v0->context.window;
        int v2 = Options_Frame(v0->taskArgs->options);

        Window_Init(v1);
        Window_Add(v0->context.bgConfig, v1, 1, 2, 19, 27, 4, 14, 1);
        Window_FillTilemap(v1, 0xFF);
        Window_CopyToVRAM(v1);

        LoadMessageBoxGraphics(v0->context.bgConfig, 1, 500, 15, v2, HEAP_ID_111);
        PaletteData_LoadBufferFromFileStart(v0->context.paletteData, NARC_INDEX_GRAPHIC__PL_WINFRAME, GetMessageBoxPaletteNARCMember(v2), HEAP_ID_111, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(15));
        PaletteData_LoadBufferFromFileStart(v0->context.paletteData, NARC_INDEX_GRAPHIC__PL_FONT, 7, HEAP_ID_111, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
        Window_DrawMessageBoxWithScrollCursor(v1, 0, 500, 15);

        SpearPillar_EraseMessage(&v0->context);
    }

    return 1;
}

static const struct {
    SpearPillarSceneInitFunc initFunc;
    SpearPillarSceneMainFunc mainFunc;
    SpearPillarSceneExitFunc exitFunc;
} sSpearPillarScenes[] = {
    { SpearPillarDialgaPalkia_Init, SpearPillarDialgaPalkia_Main, SpearPillarDialgaPalkia_Exit },
    { SpearPillarLakeTrio_Init, SpearPillarLakeTrio_Main, SpearPillarLakeTrio_Exit },
    { SpearPillarGiratina_Init, SpearPillarGiratina_Main, SpearPillarGiratina_Exit },
};

int SpearPillar_Main(ApplicationManager *appMan, int *param1)
{
    SpearPillar *v0 = ApplicationManager_Data(appMan);

    switch (*param1) {
    case 0: {
        v0->sceneData = sSpearPillarScenes[v0->sceneIndex].initFunc(v0);
        *param1 = 1;
    } break;
    case 1: {
        BOOL v1 = sSpearPillarScenes[v0->sceneIndex].mainFunc(v0->sceneData);

        if (v1 == 0) {
            *param1 = 2;
        }
    } break;
    case 2: {
        BOOL v2 = sSpearPillarScenes[v0->sceneIndex].exitFunc(v0->sceneData);

        if (v2 == 0) {
            if ((++v0->sceneIndex) != NELEMS(sSpearPillarScenes)) {
                *param1 = 0;
            } else {
                *param1 = 3;
            }
        }
    } break;
    case 3: {
        return 1;
    } break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    SpriteSystem_DrawSprites(v0->context.spriteManager);

    return 0;
}

int SpearPillar_Exit(ApplicationManager *appMan, int *param1)
{
    SpearPillar *v0 = ApplicationManager_Data(appMan);

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    Window_EraseMessageBox(&v0->context.window, 1);
    Window_ClearAndCopyToVRAM(&v0->context.window);
    Window_Remove(&v0->context.window);

    SpearPillar_FreeContext(&v0->context);
    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;

    GXLayers_SwapDisplay();
    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_111);
    Sound_Set2PokemonCriesAllowed(0);

    return 1;
}

static void SpearPillar_InitSpriteSystem(SpearPillarContext *param0)
{
    param0->spriteSystem = SpriteSystem_Alloc(HEAP_ID_111);

    {
        const RenderOamTemplate v0 = {
            0,
            128,
            0,
            32,
            0,
            128,
            0,
            32,
        };
        const CharTransferTemplateWithModes v1 = {
            48 + 48,
            1024 * 0x40,
            512 * 0x20,
            GX_OBJVRAMMODE_CHAR_1D_64K,
            GX_OBJVRAMMODE_CHAR_1D_32K
        };
        BOOL v2 = SpriteSystem_Init(param0->spriteSystem, &v0, &v1, 16 + 16);

        GF_ASSERT(v2);
    }

    {
        BOOL v3;
        const SpriteResourceCapacities v4 = {
            48 + 48,
            16 + 16,
            64,
            64,
            16,
            16,
        };

        param0->spriteManager = SpriteManager_New(param0->spriteSystem);

        v3 = SpriteSystem_InitSprites(param0->spriteSystem, param0->spriteManager, 64 + 64);
        GF_ASSERT(v3);

        v3 = SpriteSystem_InitManagerWithCapacities(param0->spriteSystem, param0->spriteManager, &v4);
        GF_ASSERT(v3);
    }
}

static void SpearPillar_InitContext(SpearPillarContext *param0)
{
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();
    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);

    param0->narc = NARC_ctor(NARC_INDEX_ARC__DEMO_TENGAN_GRA, HEAP_ID_111);
    param0->bgConfig = BgConfig_New(HEAP_ID_111);
    param0->paletteData = PaletteData_New(HEAP_ID_111);
    param0->pipelineBuffers = G3DPipeline_Init(HEAP_ID_111, TEXTURE_VRAM_SIZE_128K, PALETTE_VRAM_SIZE_64K, NULL);
    param0->camera = Camera_Alloc(HEAP_ID_111);
    param0->messageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_SPEAR_PILLAR, HEAP_ID_111);

    PaletteData_SetAutoTransparent(param0->paletteData, TRUE);
    PaletteData_AllocBuffer(param0->paletteData, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_111);
    PaletteData_AllocBuffer(param0->paletteData, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_111);
    PaletteData_AllocBuffer(param0->paletteData, PLTTBUF_MAIN_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_111);
    PaletteData_AllocBuffer(param0->paletteData, PLTTBUF_SUB_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_111);

    SpearPillar_InitBg(param0->bgConfig);
    SpearPillar_InitSpriteSystem(param0);

    G3X_AlphaBlend(1);
    HeapExp_FndInitAllocator(&param0->allocator, HEAP_ID_111, 32);
}

static void SpearPillar_FreeContext(SpearPillarContext *param0)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_0);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_SUB_2);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_SUB_3);
    Heap_Free(param0->bgConfig);

    PaletteData_FreeBuffer(param0->paletteData, PLTTBUF_MAIN_BG);
    PaletteData_FreeBuffer(param0->paletteData, PLTTBUF_SUB_BG);
    PaletteData_FreeBuffer(param0->paletteData, PLTTBUF_MAIN_OBJ);
    PaletteData_FreeBuffer(param0->paletteData, PLTTBUF_SUB_OBJ);
    PaletteData_Free(param0->paletteData);

    NARC_dtor(param0->narc);
    G3DPipelineBuffers_Free(param0->pipelineBuffers);
    Camera_Delete(param0->camera);
    SpriteSystem_FreeResourcesAndManager(param0->spriteSystem, param0->spriteManager);
    SpriteSystem_Free(param0->spriteSystem);
    MessageLoader_Free(param0->messageLoader);

    G3X_AlphaBlend(0);
}

static void SpearPillar_InitBg(BgConfig *param0)
{
    GXLayers_DisableEngineALayers();

    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_3D
        };

        SetAllGraphicsModes(&v0);
    }

    {
        GXBanks v1 = {
            GX_VRAM_BG_128_A,
            GX_VRAM_BGEXTPLTT_NONE,
            GX_VRAM_SUB_BG_32_H,
            GX_VRAM_SUB_BGEXTPLTT_NONE,
            GX_VRAM_OBJ_64_E,
            GX_VRAM_OBJEXTPLTT_NONE,
            GX_VRAM_SUB_OBJ_16_I,
            GX_VRAM_SUB_OBJEXTPLTT_NONE,
            GX_VRAM_TEX_0_B,
            GX_VRAM_TEXPLTT_01_FG
        };

        GXLayers_SetBanks(&v1);

        MI_CpuClear32((void *)HW_BG_VRAM, HW_BG_VRAM_SIZE);
        MI_CpuClear32((void *)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
        MI_CpuClear32((void *)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
        MI_CpuClear32((void *)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    }

    {
        BgTemplate v2[] = {
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x2000,
                .charBase = GX_BG_CHARBASE_0x10000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 1,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x2800,
                .charBase = GX_BG_CHARBASE_0x14000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x3000,
                .charBase = GX_BG_CHARBASE_0x18000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x3800,
                .charBase = GX_BG_CHARBASE_0x18000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        Bg_ClearTilesRange(BG_LAYER_MAIN_0, 32, 0, HEAP_ID_111);
        Bg_ClearTilesRange(BG_LAYER_MAIN_1, 32, 0, HEAP_ID_111);
        Bg_ClearTilesRange(BG_LAYER_MAIN_2, 32, 0, HEAP_ID_111);
        Bg_ClearTilesRange(BG_LAYER_MAIN_3, 32, 0, HEAP_ID_111);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_0, &v2[0], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_1, &v2[1], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_2, &v2[2], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_3, &v2[3], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_1);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_2);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_3);
    }

    {
        BgTemplate v3[] = {
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x3000,
                .charBase = GX_BG_CHARBASE_0x04000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x3800,
                .charBase = GX_BG_CHARBASE_0x04000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 2,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_0, &v3[0], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_SUB_1, &v3[1], 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_1);
    }

    Bg_ClearTilesRange(4, 32, 0, HEAP_ID_111);
    Bg_ClearTilesRange(5, 32, 0, HEAP_ID_111);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 0);

    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void SpearPillar_VBlankCallback(void *param0)
{
    SpearPillar *v0 = param0;

    VramTransfer_Process();
    SpriteSystem_TransferOam();
    PaletteData_CommitFadedBuffers(v0->context.paletteData);
    Bg_RunScheduledUpdates(v0->context.bgConfig);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}
