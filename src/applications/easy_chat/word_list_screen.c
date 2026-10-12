#include "applications/easy_chat/word_list_screen.h"

#include <nitro.h>
#include <string.h>

#include "applications/easy_chat/categories.h"
#include "applications/easy_chat/main.h"
#include "applications/easy_chat/word_display.h"
#include "applications/easy_chat/word_columns.h"
#include "applications/easy_chat/word_list_view.h"
#include "applications/easy_chat/page_buttons.h"
#include "applications/easy_chat/struct_easy_chat_word_display_decl.h"
#include "applications/easy_chat/struct_easy_chat_word_columns_decl.h"
#include "applications/easy_chat/struct_easy_chat_word_list_view_decl.h"
#include "applications/easy_chat/struct_easy_chat_page_buttons_decl.h"

#include "bg_window.h"
#include "easy_chat_word_list.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "narc.h"
#include "render_oam.h"
#include "screen_fade.h"
#include "sprite.h"
#include "sprite_util.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"

typedef struct EasyChatWordListScreen_t {
    SysTask *unk_00;
    SysTask *unk_04;
    SysTask *unk_08[4];
    const EasyChatApp *unk_18;
    const EasyChatWordList *unk_1C;
    BgConfig *unk_20;
    SpriteList *unk_24;
    G2dRenderer unk_28;
    NNSG2dImageProxy unk_1B4[2];
    NNSG2dImagePaletteProxy unk_1FC[2];
    NNSG2dCellDataBank *unk_224[2];
    NNSG2dCellAnimBankData *unk_22C[2];
    void *unk_234[2];
    void *unk_23C[2];
    EasyChatWordDisplay *unk_244;
    EasyChatWordColumns *unk_248;
    EasyChatCategoriesContext *unk_24C;
    EasyChatWordListView *unk_250;
    EasyChatPageButtons *unk_254;
} EasyChatWordListScreen;

typedef struct {
    EasyChatWordListScreen *unk_00;
    const EasyChatApp *unk_04;
    const EasyChatWordList *unk_08;
    u32 unk_0C;
    int unk_10;
    int unk_14;
} EasyChatWordListScreenTask;

static void EasyChatWordListScreen_DummyTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_RenderTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_FinishTask(EasyChatWordListScreenTask *param0);
static void EasyChatWordListScreen_InitGraphicsTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_LoadGraphics(EasyChatWordListScreenTask *param0, NARC *param1);
static void EasyChatWordListScreen_ExitTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_InitBgLayers(EasyChatWordListScreenTask *param0);
static void EasyChatWordListScreen_FadeInTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_MoveWordDisplayCursorTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_ShowWordListTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_HideWordListTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_ShowCategoriesTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_HideForModeToggleTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_ShowForModeToggleTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_HideCategoriesTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_OpenWordListTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_CloseWordListTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_CloseWordListAndCategoriesTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_OpenWordListAndCategoriesTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_UpdateWordColumnTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_UpdatePageIndicatorTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_UpdateCategoryCursorTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_UpdateWordDisplayTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_ScrollWordListTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_SetPageTextDefaultTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_SetPageTextDownTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_SetPageTextUpTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_SetPageTextNoneTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_UpdatePageArrowTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_ResetPageTextTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_PageUpPressedTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_PageDownPressedTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_PageUpReleasedTask(SysTask *param0, void *param1);
static void EasyChatWordListScreen_PageDownReleasedTask(SysTask *param0, void *param1);

EasyChatWordListScreen *EasyChatWordListScreen_New(const EasyChatApp *param0, const EasyChatWordList *param1)
{
    EasyChatWordListScreen *v0 = Heap_Alloc(HEAP_ID_35, sizeof(EasyChatWordListScreen));

    if (v0) {
        int v1;

        SetVBlankCallback(NULL, NULL);
        DisableHBlank();

        v0->unk_18 = param0;
        v0->unk_1C = param1;

        NNS_G2dInitOamManagerModule();
        RenderOam_Init(0, 128, 0, 32, 0, 128, 0, 32, 35);

        v0->unk_24 = SpriteList_InitRendering(128, &v0->unk_28, HEAP_ID_35);
        v0->unk_20 = BgConfig_New(HEAP_ID_35);
        v0->unk_00 = SysTask_Start(EasyChatWordListScreen_DummyTask, v0, 2);
        v0->unk_04 = EasyChatWordListScreen_StartVBlankTask(EasyChatWordListScreen_RenderTask, v0, 1);

        for (v1 = 0; v1 < 4; v1++) {
            v0->unk_08[v1] = NULL;
        }
    }

    return v0;
}

void EasyChatWordListScreen_Free(EasyChatWordListScreen *param0)
{
    if (param0) {
        int v0;

        SetVBlankCallback(NULL, NULL);

        for (v0 = 0; v0 < 4; v0++) {
            if (param0->unk_08[v0]) {
                SysTask_Done(param0->unk_08[v0]);
            }
        }

        SysTask_Done(param0->unk_00);
        SysTask_Done(param0->unk_04);

        RenderOam_Free();
        SpriteList_Delete(param0->unk_24);

        Heap_Free(param0->unk_20);
        Heap_Free(param0);
    }
}

SysTask *EasyChatWordListScreen_StartVBlankTask(SysTaskFunc param0, void *param1, int param2)
{
    return SysTask_ExecuteOnVBlank(param0, param1, param2);
}

static void EasyChatWordListScreen_DummyTask(SysTask *param0, void *param1)
{
    return;
}

static void EasyChatWordListScreen_RenderTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreen *v0 = param1;

    SpriteList_Update(v0->unk_24);
    RenderOam_Transfer();

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

void EasyChatWordListScreen_StartTask(EasyChatWordListScreen *param0, int param1)
{
    static const SysTaskFunc v0[] = {
        [EASY_CHAT_SYSTASK_00] = EasyChatWordListScreen_InitGraphicsTask,
        [EASY_CHAT_SYSTASK_01] = EasyChatWordListScreen_ExitTask,
        [EASY_CHAT_SYSTASK_02] = EasyChatWordListScreen_FadeInTask,
        [EASY_CHAT_SYSTASK_03] = EasyChatWordListScreen_MoveWordDisplayCursorTask,
        [EASY_CHAT_SYSTASK_04] = EasyChatWordListScreen_ShowWordListTask,
        [EASY_CHAT_SYSTASK_05] = EasyChatWordListScreen_HideWordListTask,
        [EASY_CHAT_SYSTASK_06] = EasyChatWordListScreen_ShowCategoriesTask,
        [EASY_CHAT_SYSTASK_07] = EasyChatWordListScreen_HideCategoriesTask,
        [EASY_CHAT_SYSTASK_08] = EasyChatWordListScreen_OpenWordListTask,
        [EASY_CHAT_SYSTASK_09] = EasyChatWordListScreen_CloseWordListTask,
        [EASY_CHAT_SYSTASK_10] = EasyChatWordListScreen_CloseWordListAndCategoriesTask,
        [EASY_CHAT_SYSTASK_11] = EasyChatWordListScreen_OpenWordListAndCategoriesTask,
        [EASY_CHAT_SYSTASK_12] = EasyChatWordListScreen_UpdateWordColumnTask,
        [EASY_CHAT_SYSTASK_13] = EasyChatWordListScreen_UpdatePageIndicatorTask,
        [EASY_CHAT_SYSTASK_14] = EasyChatWordListScreen_UpdateCategoryCursorTask,
        [EASY_CHAT_SYSTASK_15] = EasyChatWordListScreen_UpdateWordDisplayTask,
        [EASY_CHAT_SYSTASK_16] = EasyChatWordListScreen_ScrollWordListTask,
        [EASY_CHAT_SYSTASK_17] = EasyChatWordListScreen_SetPageTextDefaultTask,
        [EASY_CHAT_SYSTASK_18] = EasyChatWordListScreen_SetPageTextDownTask,
        [EASY_CHAT_SYSTASK_19] = EasyChatWordListScreen_SetPageTextUpTask,
        [EASY_CHAT_SYSTASK_20] = EasyChatWordListScreen_SetPageTextNoneTask,
        [EASY_CHAT_SYSTASK_21] = EasyChatWordListScreen_UpdatePageArrowTask,
        [EASY_CHAT_SYSTASK_22] = EasyChatWordListScreen_ResetPageTextTask,
        [EASY_CHAT_SYSTASK_23] = EasyChatWordListScreen_HideForModeToggleTask,
        [EASY_CHAT_SYSTASK_24] = EasyChatWordListScreen_ShowForModeToggleTask,
        [EASY_CHAT_SYSTASK_25] = EasyChatWordListScreen_PageUpPressedTask,
        [EASY_CHAT_SYSTASK_26] = EasyChatWordListScreen_PageDownPressedTask,
        [EASY_CHAT_SYSTASK_27] = EasyChatWordListScreen_PageUpReleasedTask,
        [EASY_CHAT_SYSTASK_28] = EasyChatWordListScreen_PageDownReleasedTask,
    };

    if (param1 < NELEMS(v0)) {
        EasyChatWordListScreenTask *v1 = Heap_Alloc(HEAP_ID_35, sizeof(EasyChatWordListScreenTask));

        if (v1) {
            int v2;

            v1->unk_14 = 0;
            v1->unk_0C = param1;
            v1->unk_00 = param0;
            v1->unk_04 = param0->unk_18;
            v1->unk_08 = param0->unk_1C;

            for (v2 = 0; v2 < 4; v2++) {
                if (param0->unk_08[v2] == NULL) {
                    v1->unk_10 = v2;
                    param0->unk_08[v2] = SysTask_Start(v0[param1], v1, 1);
                    break;
                }
            }
        }
    } else {
        GF_ASSERT(FALSE);
    }
}

BOOL EasyChatWordListScreen_AreTasksDone(EasyChatWordListScreen *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->unk_08[v0] != NULL) {
            return 0;
        }
    }

    return 1;
}

BOOL EasyChatWordListScreen_IsTaskDone(EasyChatWordListScreen *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->unk_08[v0] != NULL) {
            EasyChatWordListScreenTask *v1 = SysTask_GetParam(param0->unk_08[v0]);

            if (v1->unk_0C == param1) {
                return 0;
            }
        }
    }

    return 1;
}

static void EasyChatWordListScreen_FinishTask(EasyChatWordListScreenTask *param0)
{
    SysTask_Done(param0->unk_00->unk_08[param0->unk_10]);
    param0->unk_00->unk_08[param0->unk_10] = NULL;
    Heap_Free(param0);
}

static void EasyChatWordListScreen_InitGraphicsTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;

    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();
    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);

    GX_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_64K);
    GXS_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);

    NARC *narc = NARC_ctor(NARC_INDEX_GRAPHIC__PMSI, HEAP_ID_35);

    EasyChatWordListScreen_InitBgLayers(v0);
    EasyChatWordListScreen_LoadGraphics(v0, narc);

    v0->unk_00->unk_244 = EasyChatWordDisplay_New(v0->unk_00, v0->unk_04, v0->unk_08);
    EasyChatWordDisplay_LoadGraphics(v0->unk_00->unk_244, narc);

    v0->unk_00->unk_248 = EasyChatWordColumns_New(v0->unk_00, v0->unk_04, v0->unk_08);
    EasyChatWordColumns_LoadGraphics(v0->unk_00->unk_248, narc);

    v0->unk_00->unk_24C = EasyChatCategoriesContext_New(v0->unk_00, v0->unk_04, v0->unk_08);
    EasyChatCategories_DrawInterface(v0->unk_00->unk_24C, narc);

    v0->unk_00->unk_250 = EasyChatWordListView_New(v0->unk_00, v0->unk_04, v0->unk_08);
    EasyChatWordListView_LoadGraphics(v0->unk_00->unk_250);

    v0->unk_00->unk_254 = EasyChatPageButtons_New(v0->unk_00, v0->unk_04, v0->unk_08);
    EasyChatPageButtons_LoadGraphics(v0->unk_00->unk_254, narc);

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, TRUE);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, TRUE);
    GX_DispOn();

    NARC_dtor(narc);

    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_LoadGraphics(EasyChatWordListScreenTask *param0, NARC *param1)
{
    EasyChatWordListScreen *v0 = param0->unk_00;

    NNS_G2dInitImagePaletteProxy(&(v0->unk_1FC[0]));
    NNS_G2dInitImagePaletteProxy(&(v0->unk_1FC[1]));

    NNS_G2dInitImageProxy(&(v0->unk_1B4[0]));
    NNS_G2dInitImageProxy(&(v0->unk_1B4[1]));

    Graphics_LoadImageMappingFromOpenNARC(param1, 9, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 35, &(v0->unk_1B4[0]));
    Graphics_LoadPartialPaletteFromOpenNARC(param1, 10, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 35, &(v0->unk_1FC[0]));

    v0->unk_234[0] = Graphics_GetCellBankFromOpenNARC(param1, 7, 1, &(v0->unk_224[0]), HEAP_ID_35);
    v0->unk_23C[0] = Graphics_GetAnimBankFromOpenNARC(param1, 8, 1, &(v0->unk_22C[0]), HEAP_ID_35);
    v0->unk_234[1] = NULL;
    v0->unk_23C[1] = NULL;
}

static void EasyChatWordListScreen_ExitTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 5, 1, HEAP_ID_35);
        v0->unk_14++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            int v2;

            EasyChatWordDisplay_Free(v0->unk_00->unk_244);
            EasyChatWordColumns_Free(v0->unk_00->unk_248);
            EasyChatCategoriesContext_Free(v0->unk_00->unk_24C);
            EasyChatWordListView_Free(v0->unk_00->unk_250);
            EasyChatPageButtons_Free(v0->unk_00->unk_254);

            for (v2 = 0; v2 < 2; v2++) {
                if (v1->unk_234[v2] != NULL) {
                    Heap_Free(v1->unk_234[v2]);
                }

                if (v1->unk_23C[v2] != NULL) {
                    Heap_Free(v1->unk_23C[v2]);
                }
            }

            Bg_FreeTilemapBuffer(v1->unk_20, BG_LAYER_MAIN_0);
            Bg_FreeTilemapBuffer(v1->unk_20, BG_LAYER_MAIN_1);
            Bg_FreeTilemapBuffer(v1->unk_20, BG_LAYER_MAIN_2);
            Bg_FreeTilemapBuffer(v1->unk_20, BG_LAYER_MAIN_3);
            Bg_FreeTilemapBuffer(v1->unk_20, BG_LAYER_SUB_0);

            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_InitBgLayers(EasyChatWordListScreenTask *param0)
{
    static const GXBanks v0 = {
        GX_VRAM_BG_128_B,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_64_E,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_0_A,
        GX_VRAM_TEXPLTT_01_FG
    };
    static const GraphicsModes v1 = {
        GX_DISPMODE_GRAPHICS,
        GX_BGMODE_0,
        GX_BGMODE_0,
        GX_BG0_AS_2D,
    };
    static const BgTemplate v2 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xd800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0,
        .areaOver = 0,
        .mosaic = FALSE,
    };
    static const BgTemplate v3 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x1000,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_512x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe000,
        .charBase = GX_BG_CHARBASE_0x10000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 1,
        .areaOver = 0,
        .mosaic = FALSE,
    };
    static const BgTemplate v4 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xf000,
        .charBase = GX_BG_CHARBASE_0x18000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 2,
        .areaOver = 0,
        .mosaic = FALSE,
    };
    static const BgTemplate v5 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xf800,
        .charBase = GX_BG_CHARBASE_0x08000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 3,
        .areaOver = 0,
        .mosaic = FALSE,
    };
    static const BgTemplate v6 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe000,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0,
        .areaOver = 0,
        .mosaic = FALSE,
    };
    EasyChatWordListScreen *v7 = param0->unk_00;

    GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
    GX_SetGraphicsMode(GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_3D);

    GXLayers_SetBanks(&v0);
    SetAllGraphicsModes(&v1);

    Bg_InitFromTemplate(v7->unk_20, BG_LAYER_MAIN_0, &v2, 0);
    Bg_InitFromTemplate(v7->unk_20, BG_LAYER_MAIN_1, &v3, 0);
    Bg_InitFromTemplate(v7->unk_20, BG_LAYER_MAIN_2, &v4, 0);
    Bg_InitFromTemplate(v7->unk_20, BG_LAYER_MAIN_3, &v5, 0);

    Bg_InitFromTemplate(v7->unk_20, BG_LAYER_SUB_0, &v6, 0);
}

static void EasyChatWordListScreen_FadeInTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 5, 1, HEAP_ID_35);
        v0->unk_14++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            v0->unk_14++;
        }
        break;
    default:
        EasyChatWordListScreen_FinishTask(v0);
        break;
    }
}

static void EasyChatWordListScreen_MoveWordDisplayCursorTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatWordDisplay_Refresh(v1->unk_244);
    EasyChatWordDisplay_SetCursorPosition(v1->unk_244, EasyChat_GetCurrentWordSlot(v0->unk_04));

    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_ShowWordListTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatWordDisplay_SetCursorVisible(v1->unk_244, 0);
    EasyChatWordDisplay_HideSelectionArrows(v1->unk_244);

    EasyChatWordColumns_SetVisible(v1->unk_248, 1);
    EasyChatWordColumns_SetActiveColumn(v1->unk_248, EasyChat_GetWordColumn(v1->unk_18));

    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_HideWordListTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatWordColumns_SetVisible(v1->unk_248, 0);
    EasyChatWordDisplay_ShowSelectionArrows(v1->unk_244);
    EasyChatWordDisplay_SetCursorVisible(v1->unk_244, 1);
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_ShowCategoriesTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatWordDisplay_SetCursorIdle(v1->unk_244);
        EasyChatWordDisplay_HideSelectionArrows(v1->unk_244);
        EasyChatCategories_StartShowAnimation(v1->unk_24C);
        v0->unk_14++;
        break;
    case 1:
        if (EasyChatCategories_UpdateShowAnimation(v1->unk_24C)) {
            EasyChatWordColumns_SetRightColumnOffset(v1->unk_248);
            EasyChatCategories_DrawCursor(v1->unk_24C, EasyChat_GetCategoryCursorPos(v1->unk_18));
            EasyChatCategories_SetCursorVisible(v1->unk_24C, 1);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_HideForModeToggleTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatPageButtons_StartTransition(v1->unk_254);
        v0->unk_14++;
        break;
    case 1:
        EasyChatCategories_StartModeTransition(v1->unk_24C);
        v0->unk_14++;
        break;
    case 2:
        if (EasyChatCategories_UpdateModeTransition(v1->unk_24C)
            && EasyChatPageButtons_IsTransitionDone(v1->unk_254)) {
            EasyChatCategories_SetModeOffset(v1->unk_24C);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_ShowForModeToggleTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatPageButtons_StartTransition(v1->unk_254);
        v0->unk_14++;
        break;
    case 1:
        EasyChatCategories_SetCursorVisible(v1->unk_24C, 0);
        EasyChatCategories_StartModeTransition(v1->unk_24C);
        v0->unk_14++;
        break;
    case 2:
        if (EasyChatCategories_UpdateModeTransition(v1->unk_24C)) {
            EasyChatCategories_SetModeOffset(v1->unk_24C);
            v0->unk_14++;
        }
        break;
    case 3:
        if (EasyChatPageButtons_IsTransitionDone(v1->unk_254)) {
            EasyChatCategories_DrawCursor(v1->unk_24C, EasyChat_GetCategoryCursorPos(v1->unk_18));
            EasyChatCategories_SetCursorVisible(v1->unk_24C, 1);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_HideCategoriesTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatWordColumns_SetLeftColumnOffset(v1->unk_248);
        EasyChatCategories_SetCursorVisible(v1->unk_24C, 0);
        EasyChatCategories_StartSlideOutAnimation(v1->unk_24C);
        v0->unk_14++;
        break;
    case 1:
        if (EasyChatCategories_UpdateSlideOutAnimation(v1->unk_24C)) {
            EasyChatWordDisplay_ShowSelectionArrows(v1->unk_244);
            EasyChatWordDisplay_SetCursorActive(v1->unk_244);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_OpenWordListTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatWordListView_FillPage(v1->unk_250);
        EasyChatCategories_SetCursorVisible(v1->unk_24C, 0);
        EasyChatCategories_StartSlideInAnimation(v1->unk_24C);
        v0->unk_14++;
        break;
    case 1:
        if (EasyChatCategories_UpdateSlideInAnimation(v1->unk_24C)) {
            EasyChatWordListView_Show(v1->unk_250);
            v0->unk_14++;
        }
        break;
    case 2:
        if (EasyChatWordListView_IsShown(v1->unk_250)) {
            EasyChatWordListView_SetCursorPosition(v1->unk_250, EasyChat_GetWordSelectCursorIndex(v1->unk_18));
            EasyChatWordListView_SetArrowsVisible(v1->unk_250, 1);
            EasyChatPageButtons_SetVisible(v1->unk_254, 1);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_CloseWordListTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatPageButtons_StartTransition(v1->unk_254);
        v0->unk_14++;
        break;
    case 1:
        EasyChatWordListView_SetArrowsVisible(v1->unk_250, 0);
        EasyChatPageButtons_SetVisible(v1->unk_254, 0);
        EasyChatWordListView_Hide(v1->unk_250);
        v0->unk_14++;
        break;
    case 2:
        if (EasyChatWordListView_IsHidden(v1->unk_250)) {
            EasyChatCategories_SetModeOffset(v1->unk_24C);
            v0->unk_14++;
        }
        break;
    case 3:
        EasyChatCategories_StartSlideOutAndDim(v1->unk_24C);
        v0->unk_14++;
        break;
    case 4:
        if (EasyChatCategories_UpdateSlideOutAndDim(v1->unk_24C)
            && EasyChatPageButtons_IsTransitionDone(v1->unk_254)) {
            EasyChatCategories_DrawCursor(v1->unk_24C, EasyChat_GetCategoryCursorPos(v1->unk_18));
            EasyChatCategories_SetCursorVisible(v1->unk_24C, 1);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_CloseWordListAndCategoriesTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatWordColumns_SetLeftColumnOffset(v1->unk_248);
        EasyChatWordListView_SetArrowsVisible(v1->unk_250, 0);
        EasyChatPageButtons_SetVisible(v1->unk_254, 0);
        EasyChatWordListView_Hide(v1->unk_250);
        v0->unk_14++;
        break;
    case 1:
        if (EasyChatWordListView_IsHidden(v1->unk_250)) {
            EasyChatCategories_ResetVerticalOffset(v1->unk_24C);
            EasyChatCategories_StartSlideOutAndDim(v1->unk_24C);
            v0->unk_14++;
        }
        break;
    case 2:
        if (EasyChatCategories_UpdateSlideOutAndDim(v1->unk_24C)) {
            EasyChatCategories_StartBrightnessRestore(v1->unk_24C);
            v0->unk_14++;
        }
        break;
    case 3:
        if (EasyChatCategories_UpdateBrightnessRestore(v1->unk_24C)) {
            EasyChatWordDisplay_Refresh(v1->unk_244);
            EasyChatWordDisplay_SetCursorVisible(v1->unk_244, 1);
            EasyChatWordDisplay_ShowSelectionArrows(v1->unk_244);
            EasyChatWordDisplay_SetCursorActive(v1->unk_244);
            EasyChatWordListScreen_FinishTask(v0);
        }
    }
}

static void EasyChatWordListScreen_OpenWordListAndCategoriesTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatWordColumns_SetLeftColumnOffset(v1->unk_248);
        EasyChatWordListView_SetArrowsVisible(v1->unk_250, 0);
        EasyChatPageButtons_SetVisible(v1->unk_254, 0);
        EasyChatWordListView_Hide(v1->unk_250);
        v0->unk_14++;
        break;
    case 1:
        if (EasyChatWordListView_IsHidden(v1->unk_250)) {
            EasyChatCategories_ResetVerticalOffset(v1->unk_24C);
            EasyChatCategories_StartSlideOutAndDim(v1->unk_24C);
            v0->unk_14++;
        }
        break;
    case 2:
        if (EasyChatCategories_UpdateSlideOutAndDim(v1->unk_24C)) {
            EasyChatCategories_StartBrightnessRestore(v1->unk_24C);
            v0->unk_14++;
        }
        break;
    case 3:
        if (EasyChatCategories_UpdateBrightnessRestore(v1->unk_24C)) {
            EasyChatWordDisplay_Refresh(v1->unk_244);
            EasyChatWordDisplay_SetCursorVisible(v1->unk_244, 0);
            EasyChatWordColumns_SetVisible(v1->unk_248, 1);
            EasyChatWordListScreen_FinishTask(v0);
        }
    }
}

static void EasyChatWordListScreen_UpdateWordColumnTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatWordDisplay_SetCursorPosition(v1->unk_244, EasyChat_GetCurrentWordSlot(v1->unk_18));
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_UpdatePageIndicatorTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatWordColumns_SetActiveColumn(v1->unk_248, EasyChat_GetWordColumn(v1->unk_18));
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_UpdateCategoryCursorTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatCategories_DrawCursor(v1->unk_24C, EasyChat_GetCategoryCursorPos(v1->unk_18));
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_UpdateWordDisplayTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatWordListView_SetCursorPosition(v1->unk_250, EasyChat_GetWordSelectCursorIndex(v1->unk_18));
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_ScrollWordListTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatWordListView_Scroll(v1->unk_250, EasyChat_GetWordSelectScrollDirection(v1->unk_18));
        v0->unk_14++;
        break;
    case 1:
        if (EasyChatWordListView_IsScrollDone(v1->unk_250)) {
            EasyChatPageButtons_SetVisible(v1->unk_254, 1);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_SetPageTextDefaultTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatWordDisplay_SetInstructionText(v1->unk_244, 0);
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_SetPageTextDownTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatWordDisplay_SetInstructionText(v1->unk_244, 2);
    EasyChatWordDisplay_DrawPageIndicator(v1->unk_244, EasyChat_GetMenuCursorIndex(v0->unk_04));

    if (EasyChatWordColumns_IsVisible(v1->unk_248)) {
        EasyChatWordColumns_SetEdgeAnim(v1->unk_248);
    } else {
        EasyChatWordDisplay_SetCursorIdle(v1->unk_244);
    }

    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_SetPageTextUpTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatWordDisplay_SetInstructionText(v1->unk_244, 3);
    EasyChatWordDisplay_DrawPageIndicator(v1->unk_244, EasyChat_GetMenuCursorIndex(v0->unk_04));

    if (EasyChatWordColumns_IsVisible(v1->unk_248)) {
        EasyChatWordColumns_SetEdgeAnim(v1->unk_248);
    } else {
        EasyChatWordDisplay_SetCursorIdle(v1->unk_244);
    }

    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_SetPageTextNoneTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatWordDisplay_SetInstructionText(v1->unk_244, 1);
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_UpdatePageArrowTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatWordDisplay_MovePageIndicatorArrow(v1->unk_244, EasyChat_GetMenuCursorIndex(v0->unk_04));
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_ResetPageTextTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatWordDisplay_SetInstructionText(v1->unk_244, 0);
    EasyChatWordDisplay_ErasePageIndicator(v1->unk_244);

    if (EasyChatWordColumns_IsVisible(v1->unk_248)) {
        EasyChatWordColumns_SetDefaultAnim(v1->unk_248);
    } else {
        EasyChatWordDisplay_SetCursorActive(v1->unk_244);
    }

    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_PageUpPressedTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatPageButtons_SetPressedState(v1->unk_254, 0, 1);
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_PageDownPressedTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatPageButtons_SetPressedState(v1->unk_254, 1, 1);
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_PageUpReleasedTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatPageButtons_SetPressedState(v1->unk_254, 0, 0);
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_PageDownReleasedTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->unk_00;

    EasyChatPageButtons_SetPressedState(v1->unk_254, 1, 0);
    EasyChatWordListScreen_FinishTask(v0);
}

u32 EasyChatWordListScreen_GetWordSlotCount(EasyChatWordListScreen *param0)
{
    return EasyChatWordDisplay_GetWordSlotCount(param0->unk_244);
}

BgConfig *EasyChatWordListScreen_GetBgConfig(EasyChatWordListScreen *param0)
{
    return param0->unk_20;
}

SpriteList *EasyChatWordListScreen_GetSpriteList(EasyChatWordListScreen *param0)
{
    return param0->unk_24;
}

void EasyChatWordListScreen_SetupSpriteResources(EasyChatWordListScreen *param0, SpriteResourcesHeader *param1, u32 param2, u32 param3)
{
    param1->imageProxy = &param0->unk_1B4[param2];
    param1->paletteProxy = &param0->unk_1FC[param2];
    param1->cellBank = param0->unk_224[param2];
    param1->cellAnimBank = param0->unk_22C[param2];
    param1->priority = param3;
    param1->charData = NULL;
    param1->multiCellBank = NULL;
    param1->multiCellAnimBank = NULL;
    param1->isVRamTransfer = 0;
}

Sprite *EasyChatWordListScreen_AddSprite(EasyChatWordListScreen *param0, SpriteResourcesHeader *param1, u32 param2, u32 param3, u32 param4, int param5)
{
    SpriteListTemplate v0;
    Sprite *v1;
    OSIntrMode v2;

    v0.list = param0->unk_24;
    v0.resourceData = param1;
    v0.position.x = param2 * FX32_ONE;
    v0.position.y = param3 * FX32_ONE;
    v0.position.z = 0;
    v0.priority = param4;
    v0.vramType = param5;
    v0.heapID = HEAP_ID_35;

    v2 = OS_DisableInterrupts();
    v1 = SpriteList_Add(&v0);

    OS_RestoreInterrupts(v2);

    if (v1) {
        Sprite_SetAnimateFlag(v1, 1);
        Sprite_SetAnimSpeed(v1, (FX32_ONE * 2) / 2);
    }

    return v1;
}
