#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"

#include "game_opening/opening_cutscene_sprites.h"
#include "game_opening/opening_cutscene_sparkles.h"
#include "game_opening/opening_cutscene_pokemon_effects.h"
#include "game_opening/struct_opening_cutscene_sprites_decl.h"
#include "game_opening/struct_opening_cutscene_sprite_manager_decl.h"
#include "game_opening/struct_opening_cutscene_sparkle_pool_decl.h"
#include "game_opening/struct_opening_cutscene_pokemon_effects_decl.h"
#include "distortion_world/camera_configuration.h"

#include "bg_window.h"
#include "brightness_controller.h"
#include "camera.h"
#include "easy3d.h"
#include "g3d_pipeline.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "main.h"
#include "math_util.h"
#include "narc.h"
#include "overlay_manager.h"
#include "particle_system.h"
#include "render_oam.h"
#include "screen_fade.h"
#include "sound.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "g3_buffer.h"
#include "vram_transfer.h"

FS_EXTERN_OVERLAY(game_opening);

typedef struct {
    NNSG3dRenderObj unk_00;
    NNSG3dResFileHeader *unk_54;
} OpeningCutscene3dModel;

typedef struct {
    void *unk_00;
    NNSG3dResTex *unk_04;
    Camera *camera;
    OpeningCutscene3dModel unk_0C[6];
    int unk_21C;
} OpeningCutscene3dScene;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} OpeningCutsceneLogoWipe;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    BgConfig *unk_0C;
    SysTask *unk_10;
    OpeningCutsceneSpriteManager *unk_14;
    u8 *unk_18;
} OpeningCutsceneIntroState;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    int unk_0C;
    BgConfig *unk_10;
    OpeningCutsceneSprites *unk_14;
    OpeningCutsceneSparklePool *unk_18;
    OpeningCutscenePokemonEffects *unk_1C;
    OpeningCutscene3dScene unk_20;
    u16 *unk_240;
    u8 unk_244;
    u8 unk_245;
    u8 unk_246;
    u8 unk_247;
    u8 unk_248;
    s16 unk_24A;
    s16 unk_24C;
    s16 unk_24E;
    s16 unk_250;
    s16 unk_252;
    s16 unk_254;
    s16 unk_256;
    s16 unk_258;
    u8 unk_25A;
    u8 unk_25B;
    u8 unk_25C;
    u8 unk_25D;
    fx32 unk_260;
    fx32 unk_264;
} OpeningCutsceneCutsceneState;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    fx32 unk_04;
    BgConfig *unk_08;
    OpeningCutsceneLogoWipe unk_0C;
} OpeningCutsceneLogoState;

typedef struct {
    enum HeapID heapID;
    int unk_04;
    BOOL unk_08;
    BgConfig *unk_0C;
    G3DPipelineBuffers *unk_10;
    u32 unk_14;
    OpeningCutsceneIntroState unk_18;
    OpeningCutsceneCutsceneState unk_34;
    OpeningCutsceneLogoState unk_298;
    u8 unk_2A8;
} OpeningCutsceneAppData;

void EnqueueApplication(FSOverlayID param0, const ApplicationManagerTemplate *param1);
static int OpeningCutscene_Init(ApplicationManager *appMan, int *param1);
static int OpeningCutscene_Main(ApplicationManager *appMan, int *param1);
static int OpeningCutscene_Exit(ApplicationManager *appMan, int *param1);
static BOOL OpeningCutscene_UpdateIntroPhase(OpeningCutsceneAppData *param0);
static BOOL OpeningCutscene_UpdateCutscenePhase(OpeningCutsceneAppData *param0);
static BOOL OpeningCutscene_UpdateLogoPhase(OpeningCutsceneAppData *param0);
static void OpeningCutscene_InitG3d(void);
static void OpeningCutscene_EnableWindow(void);
static void OpeningCutscene_DisableWindow(void);
static void OpeningCutscene_Free3dResources(OpeningCutsceneAppData *param0);
static void OpeningCutscene_FreeBg(OpeningCutsceneAppData *param0, BOOL param1);
static void OpeningCutscene_InitIntro(OpeningCutsceneAppData *param0);
static void OpeningCutscene_LoadIntroGraphics(OpeningCutsceneIntroState *param0);
static BOOL OpeningCutscene_UpdateIntro(OpeningCutsceneIntroState *param0, const int param1);
static void OpeningCutscene_FreeIntro(OpeningCutsceneAppData *param0);
static void OpeningCutscene_FadeInBg1Task(SysTask *param0, void *param1);
static void OpeningCutscene_FadeOutBg1Task(SysTask *param0, void *param1);
static void OpeningCutscene_FadeInBg2Task(SysTask *param0, void *param1);
static void OpeningCutscene_FadeOutBg2Task(SysTask *param0, void *param1);
static void OpeningCutscene_InitCutscene(OpeningCutsceneAppData *param0);
static void OpeningCutscene_LoadCutsceneGraphics(OpeningCutsceneCutsceneState *param0);
static void OpeningCutscene_LoadScene1Graphics(OpeningCutsceneAppData *param0, OpeningCutsceneCutsceneState *param1);
static void OpeningCutscene_SyncScreenLayout(OpeningCutsceneCutsceneState *param0);
static void OpeningCutscene_LoadScene2Graphics(OpeningCutsceneAppData *param0, OpeningCutsceneCutsceneState *param1);
static void OpeningCutscene_Load3dModel(OpeningCutsceneCutsceneState *param0, int param1);
static BOOL OpeningCutscene_Load3dModelProgressive(OpeningCutsceneCutsceneState *param0, int param1);
static void OpeningCutscene_Draw3dScene(OpeningCutsceneCutsceneState *param0);
static BOOL OpeningCutscene_UpdateCutsceneTimeline(OpeningCutsceneAppData *param0, OpeningCutsceneCutsceneState *param1, const int param2);
static void OpeningCutscene_AdvanceBackgrounds(OpeningCutsceneCutsceneState *param0);
static void OpeningCutscene_ScheduleStripeScroll(OpeningCutsceneCutsceneState *param0);
static void OpeningCutscene_UpdateWindowWipe(OpeningCutsceneCutsceneState *param0, int param1);
static void OpeningCutscene_ScrollLayersOut(OpeningCutsceneCutsceneState *param0, int param1);
static void OpeningCutscene_ScrollLayersOutFinal(OpeningCutsceneCutsceneState *param0);
static void OpeningCutscene_UpdateCamera(OpeningCutsceneCutsceneState *param0, const int param1);
static void OpeningCutscene_HandleTimelineEvents(OpeningCutsceneAppData *param0, OpeningCutsceneCutsceneState *param1, int param2);
static void OpeningCutscene_FreeCutscene(OpeningCutsceneAppData *param0);
static void OpeningCutscene_InitLogo(OpeningCutsceneAppData *param0);
static void OpeningCutscene_LoadLogoGraphics(OpeningCutsceneLogoState *param0);
static BOOL OpeningCutscene_UpdateLogo(OpeningCutsceneLogoState *param0, const int param1);
static void OpeningCutscene_FreeLogo(OpeningCutsceneAppData *param0);

extern const ApplicationManagerTemplate gTitleScreenAppTemplate;

const ApplicationManagerTemplate gOpeningCutsceneAppTemplate = {
    OpeningCutscene_Init,
    OpeningCutscene_Main,
    OpeningCutscene_Exit,
    0xffffffff
};

static const int sOpeningCutscene3dTextureMembers[] = {
    0x66,
    0x6D,
    0x70
};

const int sOpeningCutscene3dModelMembers[][6] = {
    { 0x64, 0x65, 0x0, 0x0, 0x0, 0x0 },
    { 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C },
    { 0x6E, 0x6F, 0x0, 0x0, 0x0, 0x0 }
};

static const CameraConfiguration sOpeningCutsceneCameraConfiguration = {
    0x29AEC1,
    { -0x29fe, 0x0, 0x0 },
    0x0,
    0x5C1,
    0x0
};

static const GXRgb sOpeningCutsceneEdgeColorTable[8] = {
    GX_RGB(0, 0, 0),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4)
};

const VecFx32 sOpeningCutsceneLightVectors[4] = {
    { -2043, -3548, 0x6E },
    { 0x0, 0x0, 0x0 },
    { 0x0, 0x0, 0x1000 },
    { 0x0, 0x0, 0x1000 }
};

const GXRgb sOpeningCutsceneLightColors[4] = {
    GX_RGB(24, 24, 18),
    GX_RGB(0, 0, 0),
    GX_RGB(2, 2, 12),
    GX_RGB(31, 31, 31),
};

static void OpeningCutscene_InitVramBanks(void)
{
    GXBanks v0 = {
        GX_VRAM_BG_128_B,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_80_EF,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_0_A,
        GX_VRAM_TEXPLTT_0_G
    };

    GXLayers_SetBanks(&v0);
}

static void OpeningCutscene_InitVramBanksCutscene(void)
{
    GXBanks v0 = {
        GX_VRAM_BG_128_B,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_32_FG,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_0_A,
        GX_VRAM_TEXPLTT_0123_E
    };

    GXLayers_SetBanks(&v0);
}

static void OpeningCutscene_InitVramBanksLogo(void)
{
    GXBanks v0 = {
        GX_VRAM_BG_256_AB,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_NONE,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_NONE,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_NONE,
        GX_VRAM_TEXPLTT_NONE
    };

    GXLayers_SetBanks(&v0);
}

static void OpeningCutscene_InitIntroBg(OpeningCutsceneAppData *param0)
{
    param0->unk_0C = BgConfig_New(param0->heapID);

    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D
        };

        SetAllGraphicsModes(&v0);
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x0000,
            .charBase = GX_BG_CHARBASE_0x04000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_MAIN_1, &v1, 0);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x0800,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_MAIN_2, &v2, 0);
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x1000,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_MAIN_3, &v3, 0);
    }

    {
        BgTemplate v4 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x1000,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_SUB_1, &v4, 0);
    }

    {
        BgTemplate v5 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x0000,
            .charBase = GX_BG_CHARBASE_0x04000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_SUB_2, &v5, 0);
    }

    {
        BgTemplate v6 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x0800,
            .charBase = GX_BG_CHARBASE_0x04000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_SUB_3, &v6, 0);
    }

    Bg_MaskPalette(BG_LAYER_MAIN_0, 0x0);
    Bg_MaskPalette(BG_LAYER_SUB_0, 0x0);
}

static void OpeningCutscene_InitCutsceneBg(OpeningCutsceneAppData *param0)
{
    param0->unk_0C = BgConfig_New(param0->heapID);

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
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_512x512,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x2000,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_MAIN_1, &v1, 0);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x512,
            .colorMode = GX_BG_COLORMODE_256,
            .screenBase = GX_BG_SCRBASE_0x4000,
            .charBase = GX_BG_CHARBASE_0x18000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_MAIN_2, &v2, 0);
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x512,
            .colorMode = GX_BG_COLORMODE_256,
            .screenBase = GX_BG_SCRBASE_0x0000,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_MAIN_3, &v3, 0);
    }

    {
        BgTemplate v4 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x1000,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_256,
            .screenBase = GX_BG_SCRBASE_0x6000,
            .charBase = GX_BG_CHARBASE_0x14000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_SUB_0, &v4, 0);
    }

    {
        BgTemplate v5[] = {
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_512x512,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x0000,
                .charBase = GX_BG_CHARBASE_0x08000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x512,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x2000,
                .charBase = GX_BG_CHARBASE_0x0c000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x512,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x4000,
                .charBase = GX_BG_CHARBASE_0x10000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_SUB_1, &v5[0], 0);
        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_SUB_2, &v5[1], 0);
        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_SUB_3, &v5[2], 0);
    }

    Bg_MaskPalette(BG_LAYER_MAIN_1, 0x0);
    Bg_MaskPalette(BG_LAYER_SUB_0, 0x0);
}

static void OpeningCutscene_InitSceneBg(OpeningCutsceneAppData *param0)
{
    OpeningCutscene_FreeBg(param0, 0);

    {
        BgTemplate v0 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_512x512,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x0000,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_MAIN_3, &v0, 0);
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_512x512,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x2000,
            .charBase = GX_BG_CHARBASE_0x0c000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_MAIN_1, &v1, 0);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_512x512,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x4000,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_MAIN_2, &v2, 0);
    }

    {
        BgTemplate v3[] = {
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_512x512,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x0000,
                .charBase = GX_BG_CHARBASE_0x08000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_512x512,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x2000,
                .charBase = GX_BG_CHARBASE_0x0c000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_512x512,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x4000,
                .charBase = GX_BG_CHARBASE_0x10000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_SUB_1, &v3[0], 0);
        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_SUB_2, &v3[1], 0);
        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_SUB_3, &v3[2], 0);
    }

    Bg_MaskPalette(BG_LAYER_MAIN_1, 0x0);
    Bg_MaskPalette(BG_LAYER_SUB_0, 0x0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);

    param0->unk_34.unk_25A = 1;
}

static void OpeningCutscene_InitSceneBg2(OpeningCutsceneAppData *param0)
{
    OpeningCutscene_Free3dResources(param0);
    OpeningCutscene_InitSceneBg(param0);

    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D
        };

        SetAllGraphicsModes(&v0);
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x512,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x6000,
            .charBase = GX_BG_CHARBASE_0x14000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_MAIN_0, &v1, 0);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x512,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x6000,
            .charBase = GX_BG_CHARBASE_0x14000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_SUB_0, &v2, 0);
    }

    Bg_SetOffset(param0->unk_0C, BG_LAYER_MAIN_0, 0, 0);
    Bg_SetOffset(param0->unk_0C, BG_LAYER_MAIN_0, 3, 0);
    Bg_SetOffset(param0->unk_0C, BG_LAYER_SUB_0, 0, 0);
    Bg_SetOffset(param0->unk_0C, BG_LAYER_SUB_0, 3, 0);

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);

    param0->unk_34.unk_25A = 2;
}

static void OpeningCutscene_InitLogoBg(OpeningCutsceneAppData *param0)
{
    param0->unk_0C = BgConfig_New(param0->heapID);

    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D
        };

        SetAllGraphicsModes(&v0);
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x1000,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x512,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x0000,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_0C, BG_LAYER_MAIN_2, &v1, 0);
    }

    Bg_MaskPalette(BG_LAYER_MAIN_2, 0x0);
}

static void OpeningCutscene_InitG3dPipeline(OpeningCutsceneAppData *param0)
{
    NNSGfdTexKey v0;
    NNSGfdPlttKey v1;
    u32 v2, v3;

    param0->unk_10 = G3DPipeline_Init(param0->heapID, TEXTURE_VRAM_SIZE_128K, PALETTE_VRAM_SIZE_64K, OpeningCutscene_InitG3d);

    v0 = NNS_GfdAllocTexVram(0x2000 * 4, 0, 0);
    v1 = NNS_GfdAllocPlttVram(0x20 * 4, 0, NNS_GFD_ALLOC_FROM_LOW);
    v2 = NNS_GfdGetTexKeyAddr(v0);
    v3 = NNS_GfdGetPlttKeyAddr(v1);
}

static void OpeningCutscene_InitG3d(void)
{
    NNS_G3dGeFlushBuffer();

    G2_SetBG0Priority(1);
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(1);
    G3X_AlphaTest(0, 0);
    G3X_AlphaBlend(1);
    G3X_EdgeMarking(1);
    G3X_SetEdgeColorTable(sOpeningCutsceneEdgeColorTable);
    G3X_SetFog(0, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0);
    G3X_SetClearColor(GX_RGB(0, 0, 0), 0, 0x7fff, 63, 0);
    G3_ViewPort(0, 0, 255, 191);
}

static void OpeningCutscene_VBlankCallbackIntro(void *param0)
{
    OpeningCutsceneAppData *v0 = param0;
    RenderOam_Transfer();
}

static void OpeningCutscene_VBlankCallback(void *param0)
{
    int v0;
    OpeningCutsceneAppData *v1 = param0;
    OpeningCutsceneCutsceneState *v2 = &v1->unk_34;

    if (v2->unk_25B == 1) {
        gSystem.whichScreenIs3D = DS_SCREEN_SUB;

        GXLayers_SwapDisplay();
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);

        v2->unk_25B = 0;

        Camera_ComputeProjectionMatrix(0, v2->unk_20.camera);
        Camera_SetAsActive(v2->unk_20.camera);
    }

    if (v1->unk_0C != NULL) {
        Bg_RunScheduledUpdates(v1->unk_0C);
    }

    for (v0 = 0; v0 < 7 + 1; v0++) {
        if (v2->unk_247 & 1) {
            Bg_ToggleLayer(v0, 1);
        }

        if (v2->unk_248 & 1) {
            Bg_ToggleLayer(v0, 0);
        }

        v2->unk_247 >>= 1;
        v2->unk_248 >>= 1;
    }

    G2_SetWnd0Position(v2->unk_24A, v2->unk_24E, v2->unk_24C, v2->unk_250);
    G2S_SetWnd0Position(v2->unk_252, v2->unk_256, v2->unk_254, v2->unk_258);

    if (v2->unk_245 == 1) {
        OpeningCutscene_EnableWindow();
        v2->unk_245 = 0;
    }

    if (v2->unk_246 == 1) {
        OpeningCutscene_DisableWindow();
        v2->unk_246 = 0;
    }

    VramTransfer_Process();
    RenderOam_Transfer();
    OpeningCutscenePokemonEffects_UpdateSprites(v1->unk_34.unk_1C);
}

static void OpeningCutscene_EnableWindow(void)
{
    GX_SetVisibleWnd(GX_WNDMASK_W0);
    G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
    G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_OBJ, 1);
    GXS_SetVisibleWnd(GX_WNDMASK_W0);
    G2S_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
    G2S_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_OBJ, 1);
}

static void OpeningCutscene_DisableWindow(void)
{
    GX_SetVisibleWnd(0);
    GXS_SetVisibleWnd(0);
}

static int OpeningCutscene_Init(ApplicationManager *appMan, int *param1)
{
    OpeningCutsceneAppData *v0;

    BrightnessController_ResetAllControllers();
    SetScreenColorBrightness(DS_SCREEN_MAIN, COLOR_WHITE);
    SetScreenColorBrightness(DS_SCREEN_SUB, COLOR_WHITE);
    SetVBlankCallback(NULL, NULL);
    SetHBlankCallback(NULL, NULL);
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();
    SetAutorepeat(4, 8);
    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_76, 0xa0000);

    v0 = ApplicationManager_NewData(appMan, sizeof(OpeningCutsceneAppData), HEAP_ID_76);
    memset(v0, 0, sizeof(OpeningCutsceneAppData));

    v0->heapID = HEAP_ID_76;
    v0->unk_08 = 0;
    v0->unk_2A8 = 0;

    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;
    GXLayers_SwapDisplay();
    v0->unk_14 = LCRNG_GetSeed();

    LCRNG_SetSeed(0);

    return 1;
}

static int OpeningCutscene_Main(ApplicationManager *appMan, int *param1)
{
    OpeningCutsceneAppData *v0 = ApplicationManager_Data(appMan);

    if ((v0->unk_2A8) && ((gSystem.pressedKeys & PAD_BUTTON_A) || (gSystem.pressedKeys & PAD_BUTTON_START))) {
        v0->unk_08 = 1;
        gSystem.showTitleScreenIntro = FALSE;
        SetScreenColorBrightness(DS_SCREEN_MAIN, COLOR_BLACK);
        SetScreenColorBrightness(DS_SCREEN_SUB, COLOR_BLACK);
    }

    switch (*param1) {
    case 0:
        v0->unk_18.unk_18 = &v0->unk_2A8;
        (*param1)++;
        break;
    case 1:
        if (OpeningCutscene_UpdateIntroPhase(v0)) {
            (*param1)++;
        }
        break;
    case 2:
        if (OpeningCutscene_UpdateCutscenePhase(v0)) {
            (*param1)++;
        }
        break;
    case 3:
        if (OpeningCutscene_UpdateLogoPhase(v0)) {
            (*param1)++;
        }
        break;
    case 4:
        if (v0->unk_04 >= 2430) {
            return 1;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    if (v0->unk_08) {
        return 1;
    }

    v0->unk_04++;
    return 0;
}

static int OpeningCutscene_Exit(ApplicationManager *appMan, int *param1)
{
    OpeningCutsceneAppData *v0 = ApplicationManager_Data(appMan);

    if (IsScreenFadeDone() == FALSE) {
        FinishScreenFade();
    }

    LCRNG_SetSeed(v0->unk_14);
    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_76);
    EnqueueApplication(FS_OVERLAY_ID(game_opening), &gTitleScreenAppTemplate);

    return 1;
}

static BOOL OpeningCutscene_UpdateIntroPhase(OpeningCutsceneAppData *param0)
{
    u8 *v0 = &(param0->unk_18.unk_00);

    if (param0->unk_08) {
        (*v0) = 3;
    }

    switch (*v0) {
    case 0:
        OpeningCutscene_InitIntro(param0);
        (*v0)++;
        break;
    case 1:
        OpeningCutscene_LoadIntroGraphics(&param0->unk_18);
        (*v0)++;
        break;
    case 2:
        if (OpeningCutscene_UpdateIntro(&param0->unk_18, param0->unk_04)) {
            (*v0)++;
        }
        break;
    case 3:
        OpeningCutscene_FreeIntro(param0);
        return 1;
    }

    return 0;
}

static void OpeningCutscene_InitIntro(OpeningCutsceneAppData *param0)
{
    OpeningCutscene_InitVramBanks();
    OpeningCutscene_InitIntroBg(param0);

    param0->unk_18.unk_0C = param0->unk_0C;
    param0->unk_18.unk_14 = OpeningCutsceneSpriteManager_New();

    SetVBlankCallback(OpeningCutscene_VBlankCallbackIntro, (void *)param0);

    param0->unk_18.unk_02 = 1;
}

static void OpeningCutscene_LoadIntroGraphics(OpeningCutsceneIntroState *param0)
{
    Graphics_LoadTilesToBgLayer(NARC_INDEX_DEMO__TITLE__OP_DEMO, 16, param0->unk_0C, 2, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilesToBgLayer(NARC_INDEX_DEMO__TITLE__OP_DEMO, 16, param0->unk_0C, 6, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__OP_DEMO, 17, param0->unk_0C, 2, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__OP_DEMO, 18, param0->unk_0C, 6, 0, 0, 0, HEAP_ID_76);

    Graphics_LoadPalette(NARC_INDEX_DEMO__TITLE__OP_DEMO, 15, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadPalette(NARC_INDEX_DEMO__TITLE__OP_DEMO, 15, 4, 0, 0, HEAP_ID_76);

    Graphics_LoadTilesToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 15, param0->unk_0C, 1, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 13, param0->unk_0C, 1, 0, 0, 0, HEAP_ID_76);

    Graphics_LoadPalette(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 14, 0, 0, 2 * 16 * 1, HEAP_ID_76);

    Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__OP_DEMO, 19, param0->unk_0C, 3, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__OP_DEMO, 19, param0->unk_0C, 7, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilesToBgLayer(NARC_INDEX_DEMO__TITLE__OP_DEMO, 114, param0->unk_0C, 5, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__OP_DEMO, 113, param0->unk_0C, 5, 0, 0, 0, HEAP_ID_76);

    Graphics_LoadPalette(NARC_INDEX_DEMO__TITLE__OP_DEMO, 115, 4, 0, 2 * 16 * 1, HEAP_ID_76);

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);

    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG3, 0, 16);
    G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG3, 0, 16);

    OS_WaitIrq(1, OS_IE_V_BLANK);

    ResetScreenMasterBrightness(DS_SCREEN_MAIN);
    ResetScreenMasterBrightness(DS_SCREEN_SUB);
    GXLayers_TurnBothDispOn();
}

static BOOL OpeningCutscene_UpdateIntro(OpeningCutsceneIntroState *param0, const int param1)
{
    u8 *v0 = &(param0->unk_01);

    OpeningCutsceneSpriteManager_Update(param0->unk_14, param1);

    switch (*v0) {
    case 0:
        param0->unk_07 = 0;
        param0->unk_06 = 0;
        param0->unk_08 = 0;
        param0->unk_10 = SysTask_Start(OpeningCutscene_FadeInBg1Task, param0, 0);
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_TITLE_SCREEN, SEQ_TITLE00_sseq, 1);
        (*v0)++;
        break;
    case 1:
        if ((param0->unk_08) && (param1 >= 115)) {
            param0->unk_07 = 0;
            param0->unk_06 = 16;
            param0->unk_08 = 0;
            param0->unk_10 = SysTask_Start(OpeningCutscene_FadeOutBg1Task, param0, 0);
            (*v0)++;
        }
        break;
    case 2:
        if ((param0->unk_08) && (param1 >= 265)) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);

            G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, 0, 16);
            G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, 0, 16);

            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);

            param0->unk_07 = 0;
            param0->unk_06 = 0;
            param0->unk_08 = 0;
            param0->unk_10 = SysTask_Start(OpeningCutscene_FadeInBg2Task, param0, 0);
            (*v0)++;
        }
        break;
    case 3:
        if (param0->unk_08) {
            param0->unk_07 = 0;
            param0->unk_06 = 0;
            param0->unk_08 = 0;
            param0->unk_10 = SysTask_Start(OpeningCutscene_FadeOutBg2Task, param0, 0);
            (*v0)++;
        }
        break;
    case 4:
        if ((param0->unk_08) && (param1 >= 490)) {
            StartScreenFade(FADE_SUB_THEN_MAIN, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 18, 1, HEAP_ID_76);
            (*v0)++;
        }
        break;
    case 5:
        if (IsScreenFadeDone()) {
            return 1;
        }
    }

    return 0;
}

static void OpeningCutscene_FreeIntro(OpeningCutsceneAppData *param0)
{
    SetVBlankCallback(NULL, NULL);

    if (param0->unk_18.unk_02) {
        OpeningCutsceneSpriteManager_Free(param0->unk_18.unk_14);

        Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_1);
        Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_2);
        Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_2);
        Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_3);
        Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_3);
        Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_1);
        Heap_Free(param0->unk_0C);

        param0->unk_18.unk_02 = 0;
    }

    if (param0->unk_18.unk_10 != NULL) {
        GF_ASSERT(param0->unk_08);
        SysTask_Done(param0->unk_18.unk_10);
        param0->unk_18.unk_10 = NULL;
    }
}

static void OpeningCutscene_FadeInBg1Task(SysTask *param0, void *param1)
{
    OpeningCutsceneIntroState *v0 = param1;

    v0->unk_07++;

    if (v0->unk_07 >= 6) {
        v0->unk_07 = 0;
        v0->unk_06++;
    }

    if (v0->unk_06 >= 16) {
        SysTask_Done(param0);
        v0->unk_10 = NULL;
        v0->unk_08 = 1;
    }

    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG3, v0->unk_06, 16);
    G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG3, v0->unk_06, 16);
}

static void OpeningCutscene_FadeOutBg1Task(SysTask *param0, void *param1)
{
    OpeningCutsceneIntroState *v0 = param1;

    v0->unk_07++;

    if (v0->unk_07 >= 4) {
        v0->unk_07 = 0;
        v0->unk_06--;
    }

    if (v0->unk_06 == 0) {
        SysTask_Done(param0);
        v0->unk_10 = NULL;
        v0->unk_08 = 1;
        *(v0->unk_18) = 1;
    }

    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG3, v0->unk_06, 16);
    G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG3, v0->unk_06, 16);
}

static void OpeningCutscene_FadeInBg2Task(SysTask *param0, void *param1)
{
    OpeningCutsceneIntroState *v0 = param1;

    v0->unk_07++;

    if (v0->unk_07 >= 4) {
        v0->unk_07 = 0;
        v0->unk_06++;
    }

    if (v0->unk_06 >= 16) {
        SysTask_Done(param0);
        v0->unk_10 = NULL;
        v0->unk_08 = 1;
    }

    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, v0->unk_06, 16);
}

static void OpeningCutscene_FadeOutBg2Task(SysTask *param0, void *param1)
{
    OpeningCutsceneIntroState *v0 = param1;

    v0->unk_07++;

    if (v0->unk_07 >= 4) {
        v0->unk_07 = 0;
        v0->unk_06++;
    }

    if (v0->unk_06 >= 16) {
        SysTask_Done(param0);
        v0->unk_10 = NULL;
        v0->unk_08 = 1;
    }

    G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, v0->unk_06, 16);
}

static BOOL OpeningCutscene_UpdateCutscenePhase(OpeningCutsceneAppData *param0)
{
    u8 *v0 = &(param0->unk_34.unk_00);

    if (param0->unk_08) {
        (*v0) = 4;
    }

    switch (*v0) {
    case 0:
        OpeningCutscene_InitCutscene(param0);
        (*v0)++;
        break;
    case 1:
        OpeningCutscene_LoadCutsceneGraphics(&param0->unk_34);
        (*v0)++;
        break;
    case 2:
        if (OpeningCutscene_Load3dModelProgressive(&param0->unk_34, 0) == 1) {
            param0->unk_34.unk_06 = 1;
            (*v0)++;
        }
        break;
    case 3:
        if (OpeningCutscene_UpdateCutsceneTimeline(param0, &param0->unk_34, param0->unk_04)) {
            (*v0)++;
        }

        OpeningCutsceneSprites_Update(param0->unk_34.unk_14);

        if (param0->unk_34.unk_06) {
            if (param0->unk_34.unk_05 == 0) {
                OpeningCutscene_Draw3dScene(&param0->unk_34);
            }
        } else {
            OpeningCutscenePokemonEffects_Draw(param0->unk_34.unk_1C);
        }
        break;
    case 4:
        OpeningCutscene_FreeCutscene(param0);
        return 1;
    }

    return 0;
}

static void OpeningCutscene_InitCutscene(OpeningCutsceneAppData *param0)
{
    u8 v0;
    int v1;
    int v2;

    OpeningCutscene_InitVramBanksCutscene();
    OpeningCutscene_InitCutsceneBg(param0);
    OpeningCutscene_InitG3dPipeline(param0);

    v1 = OpeningCutsceneSprites_GetSize();
    v2 = OpeningCutscenePokemonEffects_GetSize();

    param0->unk_34.unk_14 = Heap_Alloc(HEAP_ID_76, v1);
    param0->unk_34.unk_18 = OpeningCutsceneSparklePool_New(16);
    param0->unk_34.unk_1C = Heap_Alloc(HEAP_ID_76, v2);

    memset(param0->unk_34.unk_14, 0, v1);
    memset(param0->unk_34.unk_1C, 0, v2);

    param0->unk_34.unk_08 = 4;
    OpeningCutscenePokemonEffects_Init(param0->unk_34.unk_1C);
    param0->unk_34.unk_10 = param0->unk_0C;

    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;
    GXLayers_SwapDisplay();

    for (v0 = 0; v0 < 4; v0++) {
        NNS_G3dGlbLightVector(v0, sOpeningCutsceneLightVectors[v0].x, sOpeningCutsceneLightVectors[v0].y, sOpeningCutsceneLightVectors[v0].z);
        NNS_G3dGlbLightColor(v0, sOpeningCutsceneLightColors[v0]);
    }

    NNS_G3dGlbMaterialColorDiffAmb(GX_RGB(16, 16, 16), GX_RGB(10, 12, 12), 0);
    NNS_G3dGlbMaterialColorSpecEmi(GX_RGB(18, 18, 18), GX_RGB(14, 14, 14), 0);
    NNS_G3dGlbPolygonAttr(13, GX_POLYGONMODE_MODULATE, GX_CULL_BACK, 0, 31, GX_POLYGON_ATTR_MISC_FOG);

    SetVBlankCallback(OpeningCutscene_VBlankCallback, (void *)param0);
    BrightnessController_SetScreenBrightness(-16, GX_BLEND_PLANEMASK_BG3, BRIGHTNESS_MAIN_SCREEN);

    param0->unk_34.unk_02 = 1;
}

static void OpeningCutscene_Free3dResources(OpeningCutsceneAppData *param0)
{
    int v0;

    if (param0->unk_34.unk_04 || param0->unk_34.unk_05) {
        Camera_ClearActive();
        Camera_Delete(param0->unk_34.unk_20.camera);

        for (v0 = 0; v0 < param0->unk_34.unk_20.unk_21C; v0++) {
            Heap_Free(param0->unk_34.unk_20.unk_0C[v0].unk_54);
        }

        param0->unk_34.unk_20.unk_21C = 0;

        Heap_Free(param0->unk_34.unk_20.unk_00);

        param0->unk_34.unk_04 = 0;
        param0->unk_34.unk_05 = 0;
    }
}

static void OpeningCutscene_FreeBg(OpeningCutsceneAppData *param0, BOOL param1)
{
    if (param0->unk_34.unk_02 && (param0->unk_0C != NULL)) {
        if (param0->unk_34.unk_25A == 0) {
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_3);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_1);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_2);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_0);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_1);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_2);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_3);
        } else if (param0->unk_34.unk_25A == 1) {
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_3);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_1);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_2);

            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_1);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_2);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_3);
        } else {
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_0);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_3);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_1);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_2);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_0);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_1);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_2);
            Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_SUB_3);
        }

        if (param1 == 1) {
            Heap_Free(param0->unk_0C);
            param0->unk_0C = NULL;
        }
    }
}

static void OpeningCutscene_FreeCutscene(OpeningCutsceneAppData *param0)
{
    u8 v0;

    GX_SetVisibleWnd(GX_WNDMASK_NONE);
    OpeningCutscene_Free3dResources(param0);

    if (param0->unk_34.unk_03) {
        OpeningCutsceneSprites_Free(param0->unk_34.unk_14);
        param0->unk_34.unk_03 = 0;
    }

    if (param0->unk_34.unk_02) {
        if (param0->unk_34.unk_18 != NULL) {
            OpeningCutsceneSparklePool_Free(param0->unk_34.unk_18);
            param0->unk_34.unk_18 = NULL;
        }

        if (param0->unk_34.unk_14 != NULL) {
            Heap_Free(param0->unk_34.unk_14);
            param0->unk_34.unk_14 = NULL;
        }

        if (param0->unk_34.unk_1C != NULL) {
            OpeningCutscenePokemonEffects_Free(param0->unk_34.unk_1C);
            Heap_Free(param0->unk_34.unk_1C);
            param0->unk_34.unk_1C = NULL;
        }

        OpeningCutscene_FreeBg(param0, 1);

        if (param0->unk_34.unk_240 != NULL) {
            Heap_Free(param0->unk_34.unk_240);
            param0->unk_34.unk_240 = NULL;
        }

        G3DPipelineBuffers_Free(param0->unk_10);
        param0->unk_34.unk_02 = 0;
    }

    NNS_G3dGeFlushBuffer();

    G3X_SetFog(0, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0);
    GX_SetVisibleWnd(0);
    GXS_SetVisibleWnd(0);

    SetVBlankCallback(NULL, NULL);
}

static void OpeningCutscene_LoadCutsceneGraphics(OpeningCutsceneCutsceneState *param0)
{
    u8 v0;
    NARC *v1 = NARC_ctor(NARC_INDEX_DEMO__TITLE__OP_DEMO, HEAP_ID_76);

    {
        Graphics_LoadPaletteWithSrcOffsetFromOpenNARC(v1, 96, 0, 0x20 * 0xc, 0x20 * 0xc, 0x20 * 2, HEAP_ID_76);
        Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 95, param0->unk_10, 3, 0, 0, 0, HEAP_ID_76);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 12, param0->unk_10, 3, 0, 0, 0, HEAP_ID_76);

        Graphics_LoadPaletteWithSrcOffsetFromOpenNARC(v1, 13, 0, 0x20 * 0xe, 0x20 * 0xe, 0x20 * 2, HEAP_ID_76);
        Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 14, param0->unk_10, 2, 0, 0, 0, HEAP_ID_76);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 12, param0->unk_10, 2, 0, 0, 0, HEAP_ID_76);

        {
            NARC *v2;

            v2 = NARC_ctor(NARC_INDEX_DATA__WEATHER_SYS, HEAP_ID_76);

            Graphics_LoadTilesToBgLayerFromOpenNARC(v2, 56, param0->unk_10, 1, 0, 0, 0, HEAP_ID_76);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(v2, 57, param0->unk_10, 1, 0, 0, 0, HEAP_ID_76);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(v2, 57, param0->unk_10, 1, 32 * 32, 0, 0, HEAP_ID_76);
            Graphics_LoadPaletteFromOpenNARC(v2, 55, 0, 0x20 * 0, 0x20, HEAP_ID_76);
            NARC_dtor(v2);
        }
    }

    {
        Graphics_LoadPaletteFromOpenNARC(v1, 61, 4, 0, 0, HEAP_ID_76);
        Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 59, param0->unk_10, 5, 0, 0, 0, HEAP_ID_76);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 63, param0->unk_10, 5, 0, 0, 0, HEAP_ID_76);
        Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 58, param0->unk_10, 6, 0, 0, 0, HEAP_ID_76);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 62, param0->unk_10, 6, 0, 0, 0, HEAP_ID_76);
        Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 60, param0->unk_10, 7, 0, 0, 0, HEAP_ID_76);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 64, param0->unk_10, 7, 0, 0, 0, HEAP_ID_76);
    }

    {
        Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 14, param0->unk_10, 4, 0, 0, 0, HEAP_ID_76);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 12, param0->unk_10, 4, 0, 0, 0, HEAP_ID_76);
        Graphics_LoadPaletteWithSrcOffsetFromOpenNARC(v1, 13, 4, 0x20 * 0xe, 0x20 * 0xe, 0x20 * 2, HEAP_ID_76);
    }

    OpeningCutsceneSprites_Init(param0->unk_14);
    OpeningCutsceneSprites_Create(param0->unk_14);
    OpeningCutsceneSprites_CreateForeground(param0->unk_14, param0->unk_18);

    MI_CpuClear16((void *)HW_BG_PLTT, 2);
    MI_CpuClear16((void *)HW_DB_BG_PLTT, 2);

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3, 0);

    ResetScreenMasterBrightness(DS_SCREEN_MAIN);
    ResetScreenMasterBrightness(DS_SCREEN_SUB);
    NARC_dtor(v1);

    param0->unk_03 = 1;
}

static void OpeningCutscene_LoadScene1Graphics(OpeningCutsceneAppData *param0, OpeningCutsceneCutsceneState *param1)
{
    u8 v0;
    NARC *v1;

    Bg_SetControlParam(param1->unk_10, 2, 0, GX_BG_COLORMODE_16);
    Bg_SetControlParam(param1->unk_10, 3, 0, GX_BG_COLORMODE_16);

    G2_SetBG0Priority(0);
    Bg_SetPriority(BG_LAYER_MAIN_1, 3);

    v1 = NARC_ctor(NARC_INDEX_DEMO__TITLE__OP_DEMO, HEAP_ID_76);

    Graphics_LoadPaletteFromOpenNARC(v1, 68, 0, 0, 0, HEAP_ID_76);

    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 66, param1->unk_10, 1, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 70, param1->unk_10, 1, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 65, param1->unk_10, 2, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 69, param1->unk_10, 2, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 67, param1->unk_10, 3, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 71, param1->unk_10, 3, 0, 0, 0, HEAP_ID_76);

    MI_CpuClear16((void *)HW_BG_PLTT, 2);
    MI_CpuClear16((void *)HW_DB_BG_PLTT, 2);

    Bg_SetOffset(param1->unk_10, BG_LAYER_MAIN_1, 0, 0);
    Bg_SetOffset(param1->unk_10, BG_LAYER_MAIN_2, 0, 0);
    Bg_SetOffset(param1->unk_10, BG_LAYER_MAIN_3, 0, 0);
    Bg_SetOffset(param1->unk_10, BG_LAYER_SUB_1, 0, 0);
    Bg_SetOffset(param1->unk_10, BG_LAYER_SUB_2, 0, 0);
    Bg_SetOffset(param1->unk_10, BG_LAYER_SUB_3, 0, 0);

    NARC_dtor(v1);
}

static void OpeningCutscene_LoadScene2Graphics(OpeningCutsceneAppData *param0, OpeningCutsceneCutsceneState *param1)
{
    u8 v0;
    NARC *v1;

    OpeningCutscene_InitSceneBg(param0);

    v1 = NARC_ctor(NARC_INDEX_DEMO__TITLE__OP_DEMO, HEAP_ID_76);

    Graphics_LoadPaletteFromOpenNARC(v1, 72, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadPaletteFromOpenNARC(v1, 72, 4, 0, 0, HEAP_ID_76);

    param1->unk_240 = Heap_Alloc(HEAP_ID_76, 0x200);

    MI_CpuCopy16((void *)HW_BG_PLTT, param1->unk_240, 0x200);
    MI_CpuClear16(param1->unk_240, 2);

    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 73, param1->unk_10, 1, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 76, param1->unk_10, 1, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 73, param1->unk_10, 5, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 76, param1->unk_10, 5, 0, 0, 0, HEAP_ID_76);

    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 74, param1->unk_10, 2, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 77, param1->unk_10, 2, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 74, param1->unk_10, 6, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 77, param1->unk_10, 6, 0, 0, 0, HEAP_ID_76);

    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 75, param1->unk_10, 3, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 78, param1->unk_10, 3, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 75, param1->unk_10, 7, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 78, param1->unk_10, 7, 0, 0, 0, HEAP_ID_76);

    MI_CpuClear16((void *)HW_BG_PLTT, 2);
    MI_CpuClear16((void *)HW_DB_BG_PLTT, 2);

    Bg_SetOffset(param1->unk_10, BG_LAYER_MAIN_1, 0, -128);
    Bg_SetOffset(param1->unk_10, BG_LAYER_MAIN_2, 0, -200);
    Bg_SetOffset(param1->unk_10, BG_LAYER_MAIN_3, 0, -152);
    Bg_SetOffset(param1->unk_10, BG_LAYER_SUB_1, 0, 128);
    Bg_SetOffset(param1->unk_10, BG_LAYER_SUB_2, 0, 0x18 * 8);
    Bg_SetOffset(param1->unk_10, BG_LAYER_SUB_3, 0, 0x16 * 8);

    NARC_dtor(v1);
}

static void OpeningCutscene_LoadScene3Graphics(OpeningCutsceneAppData *param0, OpeningCutsceneCutsceneState *param1)
{
    u8 v0;
    NARC *v1;

    OpeningCutscene_InitSceneBg2(param0);

    v1 = NARC_ctor(NARC_INDEX_DEMO__TITLE__OP_DEMO, HEAP_ID_76);

    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 79, param1->unk_10, 0, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 80, param1->unk_10, 0, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v1, 81, param1->unk_10, 4, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 82, param1->unk_10, 4, 0, 0, 0, HEAP_ID_76);

    NARC_dtor(v1);
}

static void OpeningCutscene_SyncScreenLayout(OpeningCutsceneCutsceneState *param0)
{
    if (gSystem.whichScreenIs3D == DS_SCREEN_MAIN) {
        Bg_SetOffset(param0->unk_10, BG_LAYER_MAIN_1, 3, 0);
        Bg_SetOffset(param0->unk_10, BG_LAYER_MAIN_2, 3, 0);
        Bg_SetOffset(param0->unk_10, BG_LAYER_MAIN_3, 3, 0);
        Bg_SetOffset(param0->unk_10, BG_LAYER_SUB_1, 3, 256);
        Bg_SetOffset(param0->unk_10, BG_LAYER_SUB_2, 3, 256);
        Bg_SetOffset(param0->unk_10, BG_LAYER_SUB_3, 3, 256);

        Bg_SetPriority(BG_LAYER_MAIN_1, 1);
        Bg_SetPriority(BG_LAYER_MAIN_2, 2);
        Bg_SetPriority(BG_LAYER_MAIN_3, 0);
        Bg_SetPriority(BG_LAYER_SUB_1, 1);
        Bg_SetPriority(BG_LAYER_SUB_2, 2);
        Bg_SetPriority(BG_LAYER_SUB_3, 0);
    } else {
        Bg_SetOffset(param0->unk_10, BG_LAYER_MAIN_1, 3, 256);
        Bg_SetOffset(param0->unk_10, BG_LAYER_MAIN_2, 3, 256);
        Bg_SetOffset(param0->unk_10, BG_LAYER_MAIN_3, 3, 256);
        Bg_SetOffset(param0->unk_10, BG_LAYER_SUB_1, 3, 0);
        Bg_SetOffset(param0->unk_10, BG_LAYER_SUB_2, 3, 0);
        Bg_SetOffset(param0->unk_10, BG_LAYER_SUB_3, 3, 0);

        Bg_SetPriority(BG_LAYER_MAIN_1, 1);
        Bg_SetPriority(BG_LAYER_MAIN_2, 2);
        Bg_SetPriority(BG_LAYER_MAIN_3, 0);
        Bg_SetPriority(BG_LAYER_SUB_1, 1);
        Bg_SetPriority(BG_LAYER_SUB_2, 2);
        Bg_SetPriority(BG_LAYER_SUB_3, 0);
    }

    OpeningCutsceneSprites_SetStripePalette(param0->unk_14, 0);
}

static void OpeningCutscene_Load3dTexture(OpeningCutsceneCutsceneState *param0, int param1)
{
    param0->unk_20.unk_00 = NARC_AllocAndReadWholeMemberByIndexPair(NARC_INDEX_DEMO__TITLE__OP_DEMO, sOpeningCutscene3dTextureMembers[param1], 76);
    param0->unk_20.unk_04 = NNS_G3dGetTex((NNSG3dResFileHeader *)param0->unk_20.unk_00);

    {
        BOOL v0;

        v0 = Easy3D_UploadTextureToVRAM(param0->unk_20.unk_04);
        GF_ASSERT(v0);
    }

    {
        u8 *v1;
        u32 v2;

        GF_ASSERT(param0->unk_20.unk_04->texInfo.ofsTex != 0);

        v1 = (u8 *)param0->unk_20.unk_04 + param0->unk_20.unk_04->texInfo.ofsTex;
        v2 = (u32)(v1 - (u8 *)param0->unk_20.unk_00);

        Heap_Realloc(param0->unk_20.unk_00, v2);
    }
}

static void OpeningCutscene_Load3dModels(OpeningCutsceneCutsceneState *param0, int param1, int param2, int param3)
{
    u8 v0;
    NARC *v1;
    BOOL v2;
    NNSG3dResMdlSet *v3;
    NNSG3dResMdl *v4;

    if (param3 > 6) {
        param3 = 6;
    }

    v1 = NARC_ctor(NARC_INDEX_DEMO__TITLE__OP_DEMO, HEAP_ID_76);

    for (v0 = param2; v0 < param3; v0++) {
        if (sOpeningCutscene3dModelMembers[param1][v0] == 0) {
            break;
        }

        param0->unk_20.unk_0C[v0].unk_54 = NARC_AllocAndReadWholeMember(v1, sOpeningCutscene3dModelMembers[param1][v0], 76);

        v2 = Easy3D_BindTextureToResource(param0->unk_20.unk_0C[v0].unk_54, param0->unk_20.unk_04);
        GF_ASSERT(v2);

        v3 = NNS_G3dGetMdlSet(param0->unk_20.unk_0C[v0].unk_54);
        GF_ASSERT(v3->dict.numEntry == 1);

        v4 = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(param0->unk_20.unk_0C[v0].unk_54), 0);
        GF_ASSERT(v4);

        NNS_G3dRenderObjInit(&param0->unk_20.unk_0C[v0].unk_00, v4);
        NNS_G3dMdlUseGlbDiff(v4);
        NNS_G3dMdlUseGlbAmb(v4);
        NNS_G3dMdlUseGlbSpec(v4);
        NNS_G3dMdlUseGlbEmi(v4);
        NNS_G3dMdlUseGlbLightEnableFlag(v4);

        param0->unk_20.unk_21C++;
    }

    NARC_dtor(v1);
}

static void OpeningCutscene_Init3dCamera(OpeningCutsceneCutsceneState *param0, int param1)
{
    param0->unk_20.camera = Camera_Alloc(HEAP_ID_76);

    {
        VecFx32 v0 = { 0, 0, FX32_ONE * 16 * 6 };

        Camera_InitWithTarget(&v0, sOpeningCutsceneCameraConfiguration.distance, &sOpeningCutsceneCameraConfiguration.cameraAngle, sOpeningCutsceneCameraConfiguration.fovY, sOpeningCutsceneCameraConfiguration.projectionMtx, 0, param0->unk_20.camera);
        Camera_SetFOV(0x981, param0->unk_20.camera);

        {
            VecFx32 v1 = { 0, FX32_ONE * 16 * 5, 0 };
            Camera_Move(&v1, param0->unk_20.camera);
        }

        Camera_SetAsActive(param0->unk_20.camera);
    }
}

static void OpeningCutscene_Load3dModel(OpeningCutsceneCutsceneState *param0, int param1)
{
    OpeningCutscene_Load3dTexture(param0, param1);
    OpeningCutscene_Load3dModels(param0, param1, 0, 6);
    OpeningCutscene_Init3dCamera(param0, param1);

    param0->unk_04 = 1;
}

static BOOL OpeningCutscene_Load3dModelProgressive(OpeningCutsceneCutsceneState *param0, int param1)
{
    if (param1 == 0) {
        switch (param0->unk_09) {
        case 0:
            param0->unk_05 = 1;
            OpeningCutscene_Load3dTexture(param0, param1);
            OpeningCutscene_Init3dCamera(param0, param1);
            break;
        case 1:
            OpeningCutscene_Load3dModels(param0, param1, 0, 1);
            break;
        case 2:
        default:
            OpeningCutscene_Load3dModels(param0, param1, 1, 6);
            param0->unk_09 = 0;
            param0->unk_05 = 0;
            param0->unk_04 = 1;
            return 1;
        }
    } else {
        switch (param0->unk_09) {
        case 0:
            param0->unk_05 = 1;
            OpeningCutscene_Load3dTexture(param0, param1);
            OpeningCutscene_Init3dCamera(param0, param1);
            break;
        case 1:
            OpeningCutscene_Load3dModels(param0, param1, 0, 2);
            break;
        case 2:
            OpeningCutscene_Load3dModels(param0, param1, 2, 4);
            break;
        case 3:
        default:
            OpeningCutscene_Load3dModels(param0, param1, 4, 6);
            param0->unk_09 = 0;
            param0->unk_05 = 0;
            param0->unk_04 = 1;
            return 1;
        }
    }

    param0->unk_09++;
    return 0;
}

static void OpeningCutscene_Draw3dScene(OpeningCutsceneCutsceneState *param0)
{
    u8 v0;
    MtxFx33 v1 = { FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0, FX32_ONE };
    VecFx32 v2 = { FX32_ONE, FX32_ONE, FX32_ONE };
    VecFx32 v3 = { 0, 0, 0 };

    NNS_G3dGeFlushBuffer();

    G3_ResetG3X();
    Camera_ComputeViewMatrix();

    if (param0->unk_25C == 1) {
        for (v0 = 0; v0 < param0->unk_20.unk_21C; v0++) {
            DC_FlushAll();
            Easy3D_DrawRenderObj(&param0->unk_20.unk_0C[v0].unk_00, &v3, &v1, &v2);
        }
    }

    if (param0->unk_25D == 1) {
        NNS_G3dGeFlushBuffer();
        G3_ResetG3X();
        ParticleSystem_DrawAll();
        ParticleSystem_UpdateAll();
    }

    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);
}

static BOOL OpeningCutscene_UpdateCutsceneTimeline(OpeningCutsceneAppData *param0, OpeningCutsceneCutsceneState *param1, const int param2)
{
    u8 *v0 = &(param1->unk_01);

    if (!param1->unk_07) {
        OpeningCutsceneSparklePool_StartSpawning(param1->unk_18, param1->unk_244);
    }

    param1->unk_07 = (param1->unk_07 + 1) % param1->unk_08;

    switch (*v0) {
    case 0:
        if (param2 == 640 - 1) {
            (void)0;
        }

        if (param2 >= 640) {
            Bg_ToggleLayer(BG_LAYER_MAIN_3, 1);
            BrightnessController_StartTransition(8, 0, -16, GX_BLEND_PLANEMASK_BG3, BRIGHTNESS_MAIN_SCREEN);
            (*v0)++;
        }
        break;
    case 1:
        if ((BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN) == TRUE) && (param2 == 700)) {
            Bg_ToggleLayer(BG_LAYER_MAIN_0, 1);
            OpeningCutscenePokemonEffects_CreateEmitter(param1->unk_1C, 9);
            OpeningCutscenePokemonEffects_CreateEmitter(param1->unk_1C, 10);
            OpeningCutscenePokemonEffects_CreateEmitter(param1->unk_1C, 11);
            G2_SetBlendAlpha(0, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3, 0, 0);
            param1->unk_25D = 1;
            OpeningCutsceneSprites_SetAnimate(param1->unk_14, 1);
            (*v0)++;
        }
        break;
    case 2:
        if (param2 == 785) {
            StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_WHITE, 4, 1, HEAP_ID_76);
        }

        if (param2 == (785 + 5)) {
            GF_ASSERT(IsScreenFadeDone() == TRUE);
            param1->unk_247 = (1 << 2);
            param1->unk_248 = (1 << 3);
            StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_WHITE, 4, 1, HEAP_ID_76);
        }

        if (param2 == 945 - 1) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
            param1->unk_25B = 1;
            param1->unk_25D = 0;
            param1->unk_25C = 1;
            GF_ASSERT(ParticleSystem_GetActiveEmitterCount(OpeningCutscenePokemonEffects_GetParticleSystem(param1->unk_1C)) == 0);
        }

        if (param2 == 945) {
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
        }

        if (param2 >= 975) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
            StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_WHITE, 18, 1, HEAP_ID_76);
            param1->unk_08 = 16;
            (*v0)++;
        }
        break;
    case 3:
        if (1) {
            OpeningCutscene_HandleTimelineEvents(param0, param1, param2);
            OpeningCutscene_UpdateCamera(param1, param2);
            OpeningCutsceneSprites_MoveTrio(param1->unk_14, param2);

            if (param2 == ((40 * 30 - 15) + 6)) {
                (void)0;
            }

            if (param2 == (47 * 30 - 15)) {
                (void)0;
            }

            OpeningCutsceneSprites_MoveActorLeft(param1->unk_14, param2);
            OpeningCutsceneSprites_MoveActorRight(param1->unk_14, param2);

            if (param2 >= 1576) {
                StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_WHITE, 18, 1, HEAP_ID_76);
                (*v0)++;
            }
        }

        break;
    case 4:
        OpeningCutscene_UpdateCamera(param1, param2);
        OpeningCutsceneSprites_MoveTrio(param1->unk_14, param2);
        OpeningCutsceneSprites_MoveActorLeft(param1->unk_14, param2);
        OpeningCutsceneSprites_MoveActorRight(param1->unk_14, param2);

        if (IsScreenFadeDone() && (param2 >= 1600)) {
            Bg_ToggleLayer(BG_LAYER_SUB_0, 0);
            OpeningCutsceneSprites_HideForeground(param1->unk_14, param1->unk_18);
            param1->unk_244 = 1;
            OpeningCutscene_LoadScene1Graphics(param0, param1);
            OpeningCutsceneSprites_SetVisible(param1->unk_14, 1, 1);
            OpeningCutsceneSprites_SetVisible(param1->unk_14, 2, 1);

            Bg_ToggleLayer(BG_LAYER_MAIN_1, 1);
            Bg_ToggleLayer(BG_LAYER_MAIN_2, 1);
            Bg_ToggleLayer(BG_LAYER_MAIN_3, 1);
            Bg_ToggleLayer(BG_LAYER_SUB_1, 1);
            Bg_ToggleLayer(BG_LAYER_SUB_2, 1);
            Bg_ToggleLayer(BG_LAYER_SUB_3, 1);
            Bg_SetOffset(param1->unk_10, BG_LAYER_MAIN_1, 0, 256);
            Bg_SetOffset(param1->unk_10, BG_LAYER_MAIN_1, 3, 0);
            Bg_SetOffset(param1->unk_10, BG_LAYER_MAIN_2, 0, 0);
            Bg_SetOffset(param1->unk_10, BG_LAYER_MAIN_2, 3, 256);
            Bg_SetOffset(param1->unk_10, BG_LAYER_MAIN_3, 0, 0);
            Bg_SetOffset(param1->unk_10, BG_LAYER_MAIN_3, 3, 0);
            Bg_SetOffset(param1->unk_10, BG_LAYER_SUB_1, 0, 256);
            Bg_SetOffset(param1->unk_10, BG_LAYER_SUB_1, 3, 0);
            Bg_SetOffset(param1->unk_10, BG_LAYER_SUB_2, 0, 0);
            Bg_SetOffset(param1->unk_10, BG_LAYER_SUB_2, 3, 256);
            Bg_SetOffset(param1->unk_10, BG_LAYER_SUB_3, 0, 0);
            Bg_SetOffset(param1->unk_10, BG_LAYER_SUB_3, 3, 0);

            param1->unk_264 += 0;
            param1->unk_260 = 256 << FX32_SHIFT;
            param1->unk_24A = 0;
            param1->unk_24C = 255;
            param1->unk_24E = 32;
            param1->unk_250 = 159;
            param1->unk_252 = 0;
            param1->unk_254 = 255;
            param1->unk_256 = 32;
            param1->unk_258 = 159;
            param1->unk_245 = 1;
            param1->unk_06 = 0;

            G2_BlendNone();
            G2S_BlendNone();
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_WHITE, 18, 1, HEAP_ID_76);
            (*v0)++;
        }
        break;
    case 5:
        OpeningCutscene_AdvanceBackgrounds(param1);
        OpeningCutsceneSprites_MovePair(param1->unk_14);

        if (IsScreenFadeDone()) {
            if (param2 >= (62 * 30 - 15 - 15)) {
                Bg_ScheduleScroll(param1->unk_10, 3, 0, 0);
                Bg_ScheduleScroll(param1->unk_10, 3, 3, 256);
                Bg_ScheduleScroll(param1->unk_10, 7, 0, 0);
                Bg_ScheduleScroll(param1->unk_10, 7, 3, 256);
                Bg_ScheduleScroll(param1->unk_10, 2, 0, 0);
                Bg_ScheduleScroll(param1->unk_10, 2, 3, 0);
                Bg_ScheduleScroll(param1->unk_10, 6, 0, 0);
                Bg_ScheduleScroll(param1->unk_10, 6, 3, 0);

                param1->unk_248 = (1 << 1) | (1 << 5);
                param1->unk_246 = 1;

                OpeningCutsceneSprites_SetVisible(param1->unk_14, 1, 0);
                OpeningCutsceneSprites_SetVisible(param1->unk_14, 2, 0);
                (*v0)++;
            }
        }
        break;
    case 6:
        OpeningCutscene_ScheduleStripeScroll(param1);
        OpeningCutscene_UpdateWindowWipe(param1, param2);

        if (param2 == (64 * 30 - 15 - 15 - 45)) {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 4, 1, HEAP_ID_76);
            (*v0)++;
        }
        break;
    case 7:
        OpeningCutscene_ScheduleStripeScroll(param1);
        OpeningCutscene_UpdateWindowWipe(param1, param2);

        if (IsScreenFadeDone()) {
            param1->unk_247 = (1 << 1) | (1 << 5);
            param1->unk_248 = (1 << 2) | (1 << 6);
            Bg_ScheduleScroll(param1->unk_10, 1, 0, 0);
            Bg_ScheduleScroll(param1->unk_10, 1, 3, 0);
            Bg_ScheduleScroll(param1->unk_10, 5, 0, 0);
            Bg_ScheduleScroll(param1->unk_10, 5, 3, 0);
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 4, 1, HEAP_ID_76);
            (*v0)++;
        }
        break;
    case 8:
        OpeningCutscene_ScheduleStripeScroll(param1);
        OpeningCutscene_UpdateWindowWipe(param1, param2);
        OpeningCutsceneSprites_RotateStripes(param1->unk_14, param2);

        if (IsScreenFadeDone()) {
            if (param2 == (65 * 30 - 15 - 15 - 45 - 15)) {
                Bg_ScheduleScroll(param1->unk_10, 1, 0, 0);
                Bg_ScheduleScroll(param1->unk_10, 1, 3, 256);
                Bg_ScheduleScroll(param1->unk_10, 5, 0, 0);
                Bg_ScheduleScroll(param1->unk_10, 5, 3, 256);
                OpeningCutsceneSprites_SetVisible(param1->unk_14, 11, 1);
                OpeningCutsceneSprites_SetVisible(param1->unk_14, 12, 1);
            } else if (param2 >= (1935 - 15)) {
                StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_WHITE, 4, 1, HEAP_ID_76);
                (*v0)++;
            }
        }
        break;
    case 9:
        OpeningCutsceneSprites_RotateStripes(param1->unk_14, param2);

        if (IsScreenFadeDone()) {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_WHITE, 64, 1, HEAP_ID_76);
            OpeningCutsceneSprites_SetVisible(param1->unk_14, 11, 0);
            OpeningCutsceneSprites_SetVisible(param1->unk_14, 12, 0);
            OpeningCutsceneSprites_SetVisible(param1->unk_14, 13, 1);
            OpeningCutsceneSprites_SetVisible(param1->unk_14, 14, 1);
            OpeningCutsceneSprites_SetVisible(param1->unk_14, 15, 1);
            OpeningCutsceneSprites_SetVisible(param1->unk_14, 16, 1);
            OpeningCutsceneSprites_SetStripePalette(param1->unk_14, 0);
            OpeningCutscene_LoadScene2Graphics(param0, param1);
            gSystem.whichScreenIs3D = DS_SCREEN_MAIN;
            GXLayers_SwapDisplay();
            OpeningCutscene_SyncScreenLayout(param1);
            param1->unk_246 = 1;
            (*v0)++;
        } else {
            OpeningCutscene_ScheduleStripeScroll(param1);
            OpeningCutscene_UpdateWindowWipe(param1, param2);
        }
        break;
    case 10:
        OpeningCutsceneSprites_ScrollStripes(param1->unk_14, 16 << FX32_SHIFT);
        OpeningCutscene_ScrollLayersOut(param1, param2);

        if (IsScreenFadeDone()) {
            if (param2 >= (1995 + 15)) {
                StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 4, 1, HEAP_ID_76);
                (*v0)++;
            }
        }
        break;
    case 11:
        OpeningCutsceneSprites_ScrollStripes(param1->unk_14, 16 << FX32_SHIFT);

        if (IsScreenFadeDone()) {
            G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE, GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 0, 0);
            MI_CpuClear16((void *)HW_BG_PLTT, 0x200);
            StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 4, 1, HEAP_ID_76);
            (*v0)++;
        }
        break;
    case 12:
        OpeningCutsceneSprites_ScrollStripes(param1->unk_14, 16 << FX32_SHIFT);

        if (IsScreenFadeDone()) {
            if (OpeningCutscenePokemonEffects_RunAnimation(param1->unk_1C, 0, param2)) {
                StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 4, 1, HEAP_ID_76);
                (*v0)++;
            }
        }
        break;
    case 13:
        OpeningCutsceneSprites_ScrollStripes(param1->unk_14, 16 << FX32_SHIFT);

        if (IsScreenFadeDone()) {
            if (1) {
                gSystem.whichScreenIs3D = DS_SCREEN_SUB;
                GXLayers_SwapDisplay();
                OpeningCutscene_SyncScreenLayout(param1);

                StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 4, 1, HEAP_ID_76);
                (*v0)++;
            }
        }
        break;
    case 14:
        OpeningCutsceneSprites_ScrollStripes(param1->unk_14, 16 << FX32_SHIFT);

        if (IsScreenFadeDone()) {
            if (param2 >= (2085 + 15 + 30)) {
                if (OpeningCutscenePokemonEffects_RunAnimation(param1->unk_1C, 1, param2)) {
                    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 4, 1, HEAP_ID_76);
                    param1->unk_0C = 0;
                    (*v0)++;
                }
            }
        }
        break;
    case 15:
        OpeningCutsceneSprites_ScrollStripes(param1->unk_14, 16 << FX32_SHIFT);

        if (IsScreenFadeDone()) {
            MI_CpuCopy16(param1->unk_240, (void *)HW_BG_PLTT, 0x200);

            gSystem.whichScreenIs3D = DS_SCREEN_MAIN;
            GXLayers_SwapDisplay();

            OpeningCutscene_LoadScene3Graphics(param0, param1);
            OpeningCutscene_SyncScreenLayout(param1);
            OpeningCutsceneSprites_SetStripePalette(param1->unk_14, 1);

            Bg_ScheduleScroll(param1->unk_10, 1, 0, -60);
            Bg_ScheduleScroll(param1->unk_10, 2, 0, -60);
            Bg_ScheduleScroll(param1->unk_10, 3, 0, -60);
            Bg_ScheduleScroll(param1->unk_10, 5, 0, 60);
            Bg_ScheduleScroll(param1->unk_10, 6, 0, 60);
            Bg_ScheduleScroll(param1->unk_10, 7, 0, 60);
            StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 16, 1, HEAP_ID_76);
            (*v0)++;
        }
        break;
    case 16:
        OpeningCutsceneSprites_ScrollStripes(param1->unk_14, 16 << FX32_SHIFT);

        if (IsScreenFadeDone()) {
            StartScreenFade(FADE_SUB_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 16, 1, HEAP_ID_76);
            (*v0)++;
        }
        break;
    case 17:
        OpeningCutsceneSprites_ScrollStripes(param1->unk_14, 16 << FX32_SHIFT);

        if (IsScreenFadeDone()) {
            if (param2 >= (2200 + 15)) {
                OpeningCutscene_ScrollLayersOutFinal(param1);
            }

            if (param2 >= ((2200 + 15) + 1)) {
                param1->unk_247 |= (1 << 0) | (1 << 4);

                StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_WHITE, 6, 1, HEAP_ID_76);
                (*v0)++;
            }
        }
        break;
    case 18:
        OpeningCutscene_ScrollLayersOutFinal(param1);
        OpeningCutsceneSprites_ScrollStripes(param1->unk_14, 16 << FX32_SHIFT);

        if (IsScreenFadeDone()) {
            gSystem.whichScreenIs3D = DS_SCREEN_SUB;
            GXLayers_SwapDisplay();
            (*v0)++;
        }
        break;
    case 19:
        return 1;
        break;
    }

    return 0;
}

static void OpeningCutscene_AdvanceBackgrounds(OpeningCutsceneCutsceneState *param0)
{
    param0->unk_260 += 0x280;
    param0->unk_264 += 0x110;

    Bg_SetOffset(param0->unk_10, BG_LAYER_MAIN_1, 3, -(param0->unk_264 >> FX32_SHIFT));
    Bg_SetOffset(param0->unk_10, BG_LAYER_MAIN_2, 3, -(param0->unk_260 >> FX32_SHIFT));

    Bg_SetOffset(param0->unk_10, BG_LAYER_SUB_1, 3, -(param0->unk_264 >> FX32_SHIFT));
    Bg_SetOffset(param0->unk_10, BG_LAYER_SUB_2, 3, -(param0->unk_260 >> FX32_SHIFT));

    param0->unk_0C = 0;
}

static void OpeningCutscene_ScheduleStripeScroll(OpeningCutsceneCutsceneState *param0)
{
    Bg_ScheduleScroll(param0->unk_10, 3, 1, 16);
    Bg_ScheduleScroll(param0->unk_10, 7, 1, -16);
}

static void OpeningCutscene_UpdateWindowWipe(OpeningCutsceneCutsceneState *param0, int param1)
{
    if (param1 == (65 * 30 - 15 - 15 - 45 - 15)) {
        G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
        G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);

        param0->unk_24A = 0;
        param0->unk_24C = 255;
        param0->unk_24E = 0;
        param0->unk_250 = 8 * 0x11;

        G2_SetWnd0Position(param0->unk_24A, param0->unk_24E, param0->unk_24C, param0->unk_250);
        GX_SetVisibleWnd(GX_WNDMASK_W0);
        G2S_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
        G2S_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
        G2S_SetWnd1InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);

        param0->unk_252 = 0;
        param0->unk_254 = 255;
        param0->unk_256 = 0;
        param0->unk_258 = 8 * 0x11;

        G2S_SetWnd0Position(param0->unk_252, param0->unk_256, param0->unk_254, param0->unk_258);
        G2S_SetWnd1Position(1, param0->unk_256, 0, param0->unk_258);
        GXS_SetVisibleWnd(GX_WNDMASK_W0 | GX_WNDMASK_W1);
    } else if (param1 > (65 * 30 - 15 - 15 - 45 - 15)) {
        if (Bg_GetXOffset2(param0->unk_10, 1) >= 256) {
            param0->unk_248 |= (1 << 1);
        }

        if (Bg_GetXOffset2(param0->unk_10, 5) <= -256) {
            param0->unk_248 |= (1 << 5);
        }

        Bg_ScheduleScroll(param0->unk_10, 1, 1, 12);
        Bg_ScheduleScroll(param0->unk_10, 1, 4, -1);
        Bg_ScheduleScroll(param0->unk_10, 5, 1, -12);
        Bg_ScheduleScroll(param0->unk_10, 5, 4, -1);
    }
}

static void OpeningCutscene_ScrollLayersOut(OpeningCutsceneCutsceneState *param0, int param1)
{
    int v0, v1;

    if (param1 > ((1935 - 15) + 8)) {
        v0 = Bg_GetXOffset(param0->unk_10, 1) + 20;

        if (v0 > 0) {
            v0 = 0;
        }

        Bg_ScheduleScroll(param0->unk_10, 1, 0, v0);
        v0 = Bg_GetXOffset(param0->unk_10, 5) - 20;

        if (v0 < 0) {
            v0 = 0;
        }

        Bg_ScheduleScroll(param0->unk_10, 5, 0, v0);
    }

    if (param1 >= ((1935 - 15) + 14)) {
        v0 = Bg_GetXOffset(param0->unk_10, 2) + 20;

        if (v0 > 0) {
            v0 = 0;
        }

        Bg_ScheduleScroll(param0->unk_10, 2, 0, v0);
        v0 = Bg_GetXOffset(param0->unk_10, 6) - 20;

        if (v0 < 0) {
            v0 = 0;
        }

        Bg_ScheduleScroll(param0->unk_10, 6, 0, v0);
    }

    if (param1 >= ((1935 - 15) + 20)) {
        v0 = Bg_GetXOffset(param0->unk_10, 3) + 20;

        if (v0 > 0) {
            v0 = 0;
        }

        Bg_ScheduleScroll(param0->unk_10, 3, 0, v0);
        v0 = Bg_GetXOffset(param0->unk_10, 7) - 20;

        if (v0 < 0) {
            v0 = 0;
        }

        Bg_ScheduleScroll(param0->unk_10, 7, 0, v0);
    }
}

static void OpeningCutscene_ScrollLayersOutFinal(OpeningCutsceneCutsceneState *param0)
{
    int v0, v1;

    v0 = Bg_GetXOffset(param0->unk_10, 1) + 12;

    if (v0 > 0) {
        v0 = 0;
    }

    Bg_ScheduleScroll(param0->unk_10, 1, 0, v0);
    v0 = Bg_GetXOffset(param0->unk_10, 5) - 12;

    if (v0 < 0) {
        v0 = 0;
    }

    Bg_ScheduleScroll(param0->unk_10, 5, 0, v0);
    v0 = Bg_GetXOffset(param0->unk_10, 2) + 12;

    if (v0 > 0) {
        v0 = 0;
    }

    Bg_ScheduleScroll(param0->unk_10, 2, 0, v0);
    v0 = Bg_GetXOffset(param0->unk_10, 6) - 12;

    if (v0 < 0) {
        v0 = 0;
    }

    Bg_ScheduleScroll(param0->unk_10, 6, 0, v0);
    v0 = Bg_GetXOffset(param0->unk_10, 3) + 12;

    if (v0 > 0) {
        v0 = 0;
    }

    Bg_ScheduleScroll(param0->unk_10, 3, 0, v0);
    v0 = Bg_GetXOffset(param0->unk_10, 7) - 12;

    if (v0 < 0) {
        v0 = 0;
    }

    Bg_ScheduleScroll(param0->unk_10, 7, 0, v0);
}

static void OpeningCutscene_UpdateCamera(OpeningCutsceneCutsceneState *param0, const int param1)
{
    VecFx32 v0 = { 0, 0, 0 };

    if (param1 < ((40 * 30 - 15) + 6)) {
        {
            u16 v1;
            v1 = Camera_GetFOV(param0->unk_20.camera);

            if (v1 - 32 > 0x5c1) {
                Camera_AdjustFOV(-32, param0->unk_20.camera);
            } else {
                Camera_SetFOV(0x5c1, param0->unk_20.camera);
            }
        }

        v0.z -= FX32_ONE * 2;
        Camera_Move(&v0, param0->unk_20.camera);
    } else if (param1 == ((40 * 30 - 15) + 6)) {
        VecFx32 v2 = { -(FX32_ONE * 16 * 4), 0, -FX32_ONE * 16 * 3 };
        Camera_InitWithTarget(&v2, sOpeningCutsceneCameraConfiguration.distance, &sOpeningCutsceneCameraConfiguration.cameraAngle, sOpeningCutsceneCameraConfiguration.fovY, sOpeningCutsceneCameraConfiguration.projectionMtx, 0, param0->unk_20.camera);

        {
            VecFx32 v3 = { 0, FX32_ONE * 16 * 5, 0 };
            Camera_Move(&v3, param0->unk_20.camera);
        }

        {
            NNS_G3dGeFlushBuffer();

            G3X_SetFog(1, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x1000, 4500);
            G3X_SetFogColor(GX_RGB(31, 31, 31), 31);

            {
                int v4;
                u32 v5[8];

                for (v4 = 0; v4 < 8; v4++) {
                    v5[v4] = (u32)(((v4 * 16) << 0) | ((v4 * 16 + 4) << 8) | ((v4 * 16 + 8) << 16) | ((v4 * 16 + 12) << 24));
                }

                G3X_SetFogTable(v5);
            }
        }

        {
            G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BD, 7, 16 - 7);
            Bg_SetPriority(BG_LAYER_MAIN_1, 0);
            Bg_ToggleLayer(BG_LAYER_MAIN_1, 1);
        }
    } else if (param1 < ((47 * 30 - 15) + 6)) {
        v0.x += FX32_ONE * 4;
        Camera_Move(&v0, param0->unk_20.camera);
        Bg_ScheduleScroll(param0->unk_10, 1, 1, 4);
    } else if (param1 == ((47 * 30 - 15) + 6)) {
        VecFx32 v6 = { FX32_ONE * 16 * 30, 0, FX32_ONE * 0 - 0x70000 };
        Camera_InitWithTarget(&v6, sOpeningCutsceneCameraConfiguration.distance, &sOpeningCutsceneCameraConfiguration.cameraAngle, sOpeningCutsceneCameraConfiguration.fovY, sOpeningCutsceneCameraConfiguration.projectionMtx, 0, param0->unk_20.camera);
        {
            VecFx32 v7 = { 0, FX32_ONE * 16 * 5, 0 };
            Camera_Move(&v7, param0->unk_20.camera);
        }

        {
            CameraAngle v8 = { 0, 0x680, 0, 0 };
            Camera_AdjustAngleAroundSelf(&v8, param0->unk_20.camera);
        }

        {
            NNS_G3dGeFlushBuffer();
            G3X_SetFog(0, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0);
        }

        {
            G2_BlendNone();
            Bg_ToggleLayer(BG_LAYER_MAIN_1, 0);
        }
    } else {
        if (param1 >= 1560) {
            u16 v9;

            v9 = Camera_GetFOV(param0->unk_20.camera);

            if (v9 + 24 < 0x4000) {
                Camera_AdjustFOV(24, param0->unk_20.camera);
            }
        }

        v0.x += -0x2000;
        Camera_Move(&v0, param0->unk_20.camera);
    }
}

static void OpeningCutscene_HandleTimelineEvents(OpeningCutsceneAppData *param0, OpeningCutsceneCutsceneState *param1, int param2)
{
    BOOL v0;

    switch (param2) {
    case (40 * 30 - 15):
        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 4, 1, HEAP_ID_76);
        break;
    case ((40 * 30 - 15) + 6):
        GF_ASSERT(IsScreenFadeDone() == TRUE);
        OpeningCutscene_Free3dResources(param0);
        OpeningCutscene_Load3dModelProgressive(param1, 1);
        break;
    case (((40 * 30 - 15) + 6) + 1):
        OpeningCutscene_Load3dModelProgressive(param1, 1);
        break;
    case (((40 * 30 - 15) + 6) + 2):
        OpeningCutscene_Load3dModelProgressive(param1, 1);
        break;
    case (((40 * 30 - 15) + 6) + 3):
        v0 = OpeningCutscene_Load3dModelProgressive(param1, 1);
        GF_ASSERT(v0 == 1);
        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 4, 1, HEAP_ID_76);
        break;
    case (47 * 30 - 15):
        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 4, 1, HEAP_ID_76);
        break;
    case ((47 * 30 - 15) + 6):
        GF_ASSERT(IsScreenFadeDone() == TRUE);
        OpeningCutscene_Free3dResources(param0);
        OpeningCutscene_Load3dModel(param1, 2);
        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 4, 1, HEAP_ID_76);
        break;
    }
}

static BOOL OpeningCutscene_UpdateLogoPhase(OpeningCutsceneAppData *param0)
{
    u8 *v0 = &(param0->unk_298.unk_00);

    if (param0->unk_08) {
        (*v0) = 3;
    }

    switch (*v0) {
    case 0:
        OpeningCutscene_InitLogo(param0);
        (*v0)++;
        break;
    case 1:
        OpeningCutscene_LoadLogoGraphics(&param0->unk_298);
        (*v0)++;
        break;
    case 2:
        if (OpeningCutscene_UpdateLogo(&param0->unk_298, param0->unk_04)) {
            (*v0)++;
        }
        break;
    case 3:
        OpeningCutscene_FreeLogo(param0);
        return 1;
    }

    return 0;
}

static void OpeningCutscene_InitLogo(OpeningCutsceneAppData *param0)
{
    int v0;
    int v1;

    OpeningCutscene_InitVramBanksLogo();
    OpeningCutscene_InitLogoBg(param0);

    param0->unk_298.unk_08 = param0->unk_0C;

    SetScreenColorBrightness(DS_SCREEN_MAIN, COLOR_WHITE);
    SetScreenColorBrightness(DS_SCREEN_SUB, COLOR_WHITE);

    G2_BlendNone();

    param0->unk_298.unk_02 = 1;
}

static void OpeningCutscene_LoadLogoGraphics(OpeningCutsceneLogoState *param0)
{
    Graphics_LoadPalette(NARC_INDEX_DEMO__TITLE__OP_DEMO, 99, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilesToBgLayer(NARC_INDEX_DEMO__TITLE__OP_DEMO, 98, param0->unk_08, 2, 0, 0, 0, HEAP_ID_76);
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__OP_DEMO, 97, param0->unk_08, 2, 0, 0, 0, HEAP_ID_76);

    GXLayers_DisableEngineALayers();
    GXLayers_EngineASetLayers(0);
    GXLayers_EngineBSetLayers(0);

    param0->unk_04 = -24 * FX32_ONE;

    Bg_SetOffset(param0->unk_08, BG_LAYER_MAIN_2, 0, 0);
    Bg_SetOffset(param0->unk_08, BG_LAYER_MAIN_2, 3, param0->unk_04 / FX32_ONE);

    param0->unk_03 = 1;
}

static BOOL OpeningCutscene_UpdateLogo(OpeningCutsceneLogoState *param0, const int param1)
{
    u8 *v0 = &(param0->unk_01);

    switch (*v0) {
    case 0:
        if (param1 >= (2285 - 15 - 65)) {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_WHITE, 30, 1, HEAP_ID_76);
            (*v0)++;
        }
        break;
    case 1:
        if (IsScreenFadeDone()) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 90, 1, HEAP_ID_76);
            (*v0)++;
        }
        break;
    case 2:
        if (IsScreenFadeDone()) {
            (*v0)++;
        }
        break;
    case 3:
        if (param1 >= (2500 - 15 - 65)) {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 8, 1, HEAP_ID_76);

            (*v0)++;
        }
        break;
    case 4:
        if (IsScreenFadeDone()) {
            return 1;
        }
    }

    param0->unk_04 += 0x400;
    Bg_SetOffset(param0->unk_08, BG_LAYER_MAIN_2, 3, param0->unk_04 / FX32_ONE);

    return 0;
}

static void OpeningCutscene_FreeLogo(OpeningCutsceneAppData *param0)
{
    if (param0->unk_298.unk_02) {
        Bg_FreeTilemapBuffer(param0->unk_0C, BG_LAYER_MAIN_2);
        Heap_Free(param0->unk_0C);
        param0->unk_298.unk_02 = 0;
    }

    if (param0->unk_298.unk_03) {
        param0->unk_298.unk_03 = 0;
    }
}
