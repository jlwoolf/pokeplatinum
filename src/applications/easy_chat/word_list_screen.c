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
    SysTask *dummyTask;
    SysTask *renderTask;
    SysTask *tasks[4];
    const EasyChatApp *easyChatApp;
    const EasyChatWordList *wordList;
    BgConfig *bgConfig;
    SpriteList *spriteList;
    G2dRenderer g2dRenderer;
    NNSG2dImageProxy imageProxy[2];
    NNSG2dImagePaletteProxy paletteProxy[2];
    NNSG2dCellDataBank *cellBank[2];
    NNSG2dCellAnimBankData *cellAnimBank[2];
    void *cellBankData[2];
    void *cellAnimBankData[2];
    EasyChatWordDisplay *wordDisplay;
    EasyChatWordColumns *wordColumns;
    EasyChatCategoriesContext *categoriesContext;
    EasyChatWordListView *wordListView;
    EasyChatPageButtons *pageButtons;
} EasyChatWordListScreen;

typedef struct {
    EasyChatWordListScreen *wordListScreen;
    const EasyChatApp *easyChatApp;
    const EasyChatWordList *wordList;
    u32 narc;
    int taskIndex;
    int state;
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

        v0->easyChatApp = param0;
        v0->wordList = param1;

        NNS_G2dInitOamManagerModule();
        RenderOam_Init(0, 128, 0, 32, 0, 128, 0, 32, 35);

        v0->spriteList = SpriteList_InitRendering(128, &v0->g2dRenderer, HEAP_ID_35);
        v0->bgConfig = BgConfig_New(HEAP_ID_35);
        v0->dummyTask = SysTask_Start(EasyChatWordListScreen_DummyTask, v0, 2);
        v0->renderTask = EasyChatWordListScreen_StartVBlankTask(EasyChatWordListScreen_RenderTask, v0, 1);

        for (v1 = 0; v1 < 4; v1++) {
            v0->tasks[v1] = NULL;
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
            if (param0->tasks[v0]) {
                SysTask_Done(param0->tasks[v0]);
            }
        }

        SysTask_Done(param0->dummyTask);
        SysTask_Done(param0->renderTask);

        RenderOam_Free();
        SpriteList_Delete(param0->spriteList);

        Heap_Free(param0->bgConfig);
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

    SpriteList_Update(v0->spriteList);
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

            v1->state = 0;
            v1->narc = param1;
            v1->wordListScreen = param0;
            v1->easyChatApp = param0->easyChatApp;
            v1->wordList = param0->wordList;

            for (v2 = 0; v2 < 4; v2++) {
                if (param0->tasks[v2] == NULL) {
                    v1->taskIndex = v2;
                    param0->tasks[v2] = SysTask_Start(v0[param1], v1, 1);
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
        if (param0->tasks[v0] != NULL) {
            return 0;
        }
    }

    return 1;
}

BOOL EasyChatWordListScreen_IsTaskDone(EasyChatWordListScreen *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->tasks[v0] != NULL) {
            EasyChatWordListScreenTask *v1 = SysTask_GetParam(param0->tasks[v0]);

            if (v1->narc == param1) {
                return 0;
            }
        }
    }

    return 1;
}

static void EasyChatWordListScreen_FinishTask(EasyChatWordListScreenTask *param0)
{
    SysTask_Done(param0->wordListScreen->tasks[param0->taskIndex]);
    param0->wordListScreen->tasks[param0->taskIndex] = NULL;
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

    v0->wordListScreen->wordDisplay = EasyChatWordDisplay_New(v0->wordListScreen, v0->easyChatApp, v0->wordList);
    EasyChatWordDisplay_LoadGraphics(v0->wordListScreen->wordDisplay, narc);

    v0->wordListScreen->wordColumns = EasyChatWordColumns_New(v0->wordListScreen, v0->easyChatApp, v0->wordList);
    EasyChatWordColumns_LoadGraphics(v0->wordListScreen->wordColumns, narc);

    v0->wordListScreen->categoriesContext = EasyChatCategoriesContext_New(v0->wordListScreen, v0->easyChatApp, v0->wordList);
    EasyChatCategories_DrawInterface(v0->wordListScreen->categoriesContext, narc);

    v0->wordListScreen->wordListView = EasyChatWordListView_New(v0->wordListScreen, v0->easyChatApp, v0->wordList);
    EasyChatWordListView_LoadGraphics(v0->wordListScreen->wordListView);

    v0->wordListScreen->pageButtons = EasyChatPageButtons_New(v0->wordListScreen, v0->easyChatApp, v0->wordList);
    EasyChatPageButtons_LoadGraphics(v0->wordListScreen->pageButtons, narc);

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, TRUE);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, TRUE);
    GX_DispOn();

    NARC_dtor(narc);

    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_LoadGraphics(EasyChatWordListScreenTask *param0, NARC *param1)
{
    EasyChatWordListScreen *v0 = param0->wordListScreen;

    NNS_G2dInitImagePaletteProxy(&(v0->paletteProxy[0]));
    NNS_G2dInitImagePaletteProxy(&(v0->paletteProxy[1]));

    NNS_G2dInitImageProxy(&(v0->imageProxy[0]));
    NNS_G2dInitImageProxy(&(v0->imageProxy[1]));

    Graphics_LoadImageMappingFromOpenNARC(param1, 9, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 35, &(v0->imageProxy[0]));
    Graphics_LoadPartialPaletteFromOpenNARC(param1, 10, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 35, &(v0->paletteProxy[0]));

    v0->cellBankData[0] = Graphics_GetCellBankFromOpenNARC(param1, 7, 1, &(v0->cellBank[0]), HEAP_ID_35);
    v0->cellAnimBankData[0] = Graphics_GetAnimBankFromOpenNARC(param1, 8, 1, &(v0->cellAnimBank[0]), HEAP_ID_35);
    v0->cellBankData[1] = NULL;
    v0->cellAnimBankData[1] = NULL;
}

static void EasyChatWordListScreen_ExitTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    switch (v0->state) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 5, 1, HEAP_ID_35);
        v0->state++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            int v2;

            EasyChatWordDisplay_Free(v0->wordListScreen->wordDisplay);
            EasyChatWordColumns_Free(v0->wordListScreen->wordColumns);
            EasyChatCategoriesContext_Free(v0->wordListScreen->categoriesContext);
            EasyChatWordListView_Free(v0->wordListScreen->wordListView);
            EasyChatPageButtons_Free(v0->wordListScreen->pageButtons);

            for (v2 = 0; v2 < 2; v2++) {
                if (v1->cellBankData[v2] != NULL) {
                    Heap_Free(v1->cellBankData[v2]);
                }

                if (v1->cellAnimBankData[v2] != NULL) {
                    Heap_Free(v1->cellAnimBankData[v2]);
                }
            }

            Bg_FreeTilemapBuffer(v1->bgConfig, BG_LAYER_MAIN_0);
            Bg_FreeTilemapBuffer(v1->bgConfig, BG_LAYER_MAIN_1);
            Bg_FreeTilemapBuffer(v1->bgConfig, BG_LAYER_MAIN_2);
            Bg_FreeTilemapBuffer(v1->bgConfig, BG_LAYER_MAIN_3);
            Bg_FreeTilemapBuffer(v1->bgConfig, BG_LAYER_SUB_0);

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
    EasyChatWordListScreen *v7 = param0->wordListScreen;

    GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
    GX_SetGraphicsMode(GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_3D);

    GXLayers_SetBanks(&v0);
    SetAllGraphicsModes(&v1);

    Bg_InitFromTemplate(v7->bgConfig, BG_LAYER_MAIN_0, &v2, 0);
    Bg_InitFromTemplate(v7->bgConfig, BG_LAYER_MAIN_1, &v3, 0);
    Bg_InitFromTemplate(v7->bgConfig, BG_LAYER_MAIN_2, &v4, 0);
    Bg_InitFromTemplate(v7->bgConfig, BG_LAYER_MAIN_3, &v5, 0);

    Bg_InitFromTemplate(v7->bgConfig, BG_LAYER_SUB_0, &v6, 0);
}

static void EasyChatWordListScreen_FadeInTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    switch (v0->state) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 5, 1, HEAP_ID_35);
        v0->state++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            v0->state++;
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
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatWordDisplay_Refresh(v1->wordDisplay);
    EasyChatWordDisplay_SetCursorPosition(v1->wordDisplay, EasyChat_GetCurrentWordSlot(v0->easyChatApp));

    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_ShowWordListTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatWordDisplay_SetCursorVisible(v1->wordDisplay, 0);
    EasyChatWordDisplay_HideSelectionArrows(v1->wordDisplay);

    EasyChatWordColumns_SetVisible(v1->wordColumns, 1);
    EasyChatWordColumns_SetActiveColumn(v1->wordColumns, EasyChat_GetWordColumn(v1->easyChatApp));

    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_HideWordListTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatWordColumns_SetVisible(v1->wordColumns, 0);
    EasyChatWordDisplay_ShowSelectionArrows(v1->wordDisplay);
    EasyChatWordDisplay_SetCursorVisible(v1->wordDisplay, 1);
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_ShowCategoriesTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    switch (v0->state) {
    case 0:
        EasyChatWordDisplay_SetCursorIdle(v1->wordDisplay);
        EasyChatWordDisplay_HideSelectionArrows(v1->wordDisplay);
        EasyChatCategories_StartShowAnimation(v1->categoriesContext);
        v0->state++;
        break;
    case 1:
        if (EasyChatCategories_UpdateShowAnimation(v1->categoriesContext)) {
            EasyChatWordColumns_SetRightColumnOffset(v1->wordColumns);
            EasyChatCategories_DrawCursor(v1->categoriesContext, EasyChat_GetCategoryCursorPos(v1->easyChatApp));
            EasyChatCategories_SetCursorVisible(v1->categoriesContext, 1);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_HideForModeToggleTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    switch (v0->state) {
    case 0:
        EasyChatPageButtons_StartTransition(v1->pageButtons);
        v0->state++;
        break;
    case 1:
        EasyChatCategories_StartModeTransition(v1->categoriesContext);
        v0->state++;
        break;
    case 2:
        if (EasyChatCategories_UpdateModeTransition(v1->categoriesContext)
            && EasyChatPageButtons_IsTransitionDone(v1->pageButtons)) {
            EasyChatCategories_SetModeOffset(v1->categoriesContext);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_ShowForModeToggleTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    switch (v0->state) {
    case 0:
        EasyChatPageButtons_StartTransition(v1->pageButtons);
        v0->state++;
        break;
    case 1:
        EasyChatCategories_SetCursorVisible(v1->categoriesContext, 0);
        EasyChatCategories_StartModeTransition(v1->categoriesContext);
        v0->state++;
        break;
    case 2:
        if (EasyChatCategories_UpdateModeTransition(v1->categoriesContext)) {
            EasyChatCategories_SetModeOffset(v1->categoriesContext);
            v0->state++;
        }
        break;
    case 3:
        if (EasyChatPageButtons_IsTransitionDone(v1->pageButtons)) {
            EasyChatCategories_DrawCursor(v1->categoriesContext, EasyChat_GetCategoryCursorPos(v1->easyChatApp));
            EasyChatCategories_SetCursorVisible(v1->categoriesContext, 1);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_HideCategoriesTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    switch (v0->state) {
    case 0:
        EasyChatWordColumns_SetLeftColumnOffset(v1->wordColumns);
        EasyChatCategories_SetCursorVisible(v1->categoriesContext, 0);
        EasyChatCategories_StartSlideOutAnimation(v1->categoriesContext);
        v0->state++;
        break;
    case 1:
        if (EasyChatCategories_UpdateSlideOutAnimation(v1->categoriesContext)) {
            EasyChatWordDisplay_ShowSelectionArrows(v1->wordDisplay);
            EasyChatWordDisplay_SetCursorActive(v1->wordDisplay);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_OpenWordListTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    switch (v0->state) {
    case 0:
        EasyChatWordListView_FillPage(v1->wordListView);
        EasyChatCategories_SetCursorVisible(v1->categoriesContext, 0);
        EasyChatCategories_StartSlideInAnimation(v1->categoriesContext);
        v0->state++;
        break;
    case 1:
        if (EasyChatCategories_UpdateSlideInAnimation(v1->categoriesContext)) {
            EasyChatWordListView_Show(v1->wordListView);
            v0->state++;
        }
        break;
    case 2:
        if (EasyChatWordListView_IsShown(v1->wordListView)) {
            EasyChatWordListView_SetCursorPosition(v1->wordListView, EasyChat_GetWordSelectCursorIndex(v1->easyChatApp));
            EasyChatWordListView_SetArrowsVisible(v1->wordListView, 1);
            EasyChatPageButtons_SetVisible(v1->pageButtons, 1);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_CloseWordListTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    switch (v0->state) {
    case 0:
        EasyChatPageButtons_StartTransition(v1->pageButtons);
        v0->state++;
        break;
    case 1:
        EasyChatWordListView_SetArrowsVisible(v1->wordListView, 0);
        EasyChatPageButtons_SetVisible(v1->pageButtons, 0);
        EasyChatWordListView_Hide(v1->wordListView);
        v0->state++;
        break;
    case 2:
        if (EasyChatWordListView_IsHidden(v1->wordListView)) {
            EasyChatCategories_SetModeOffset(v1->categoriesContext);
            v0->state++;
        }
        break;
    case 3:
        EasyChatCategories_StartSlideOutAndDim(v1->categoriesContext);
        v0->state++;
        break;
    case 4:
        if (EasyChatCategories_UpdateSlideOutAndDim(v1->categoriesContext)
            && EasyChatPageButtons_IsTransitionDone(v1->pageButtons)) {
            EasyChatCategories_DrawCursor(v1->categoriesContext, EasyChat_GetCategoryCursorPos(v1->easyChatApp));
            EasyChatCategories_SetCursorVisible(v1->categoriesContext, 1);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_CloseWordListAndCategoriesTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    switch (v0->state) {
    case 0:
        EasyChatWordColumns_SetLeftColumnOffset(v1->wordColumns);
        EasyChatWordListView_SetArrowsVisible(v1->wordListView, 0);
        EasyChatPageButtons_SetVisible(v1->pageButtons, 0);
        EasyChatWordListView_Hide(v1->wordListView);
        v0->state++;
        break;
    case 1:
        if (EasyChatWordListView_IsHidden(v1->wordListView)) {
            EasyChatCategories_ResetVerticalOffset(v1->categoriesContext);
            EasyChatCategories_StartSlideOutAndDim(v1->categoriesContext);
            v0->state++;
        }
        break;
    case 2:
        if (EasyChatCategories_UpdateSlideOutAndDim(v1->categoriesContext)) {
            EasyChatCategories_StartBrightnessRestore(v1->categoriesContext);
            v0->state++;
        }
        break;
    case 3:
        if (EasyChatCategories_UpdateBrightnessRestore(v1->categoriesContext)) {
            EasyChatWordDisplay_Refresh(v1->wordDisplay);
            EasyChatWordDisplay_SetCursorVisible(v1->wordDisplay, 1);
            EasyChatWordDisplay_ShowSelectionArrows(v1->wordDisplay);
            EasyChatWordDisplay_SetCursorActive(v1->wordDisplay);
            EasyChatWordListScreen_FinishTask(v0);
        }
    }
}

static void EasyChatWordListScreen_OpenWordListAndCategoriesTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    switch (v0->state) {
    case 0:
        EasyChatWordColumns_SetLeftColumnOffset(v1->wordColumns);
        EasyChatWordListView_SetArrowsVisible(v1->wordListView, 0);
        EasyChatPageButtons_SetVisible(v1->pageButtons, 0);
        EasyChatWordListView_Hide(v1->wordListView);
        v0->state++;
        break;
    case 1:
        if (EasyChatWordListView_IsHidden(v1->wordListView)) {
            EasyChatCategories_ResetVerticalOffset(v1->categoriesContext);
            EasyChatCategories_StartSlideOutAndDim(v1->categoriesContext);
            v0->state++;
        }
        break;
    case 2:
        if (EasyChatCategories_UpdateSlideOutAndDim(v1->categoriesContext)) {
            EasyChatCategories_StartBrightnessRestore(v1->categoriesContext);
            v0->state++;
        }
        break;
    case 3:
        if (EasyChatCategories_UpdateBrightnessRestore(v1->categoriesContext)) {
            EasyChatWordDisplay_Refresh(v1->wordDisplay);
            EasyChatWordDisplay_SetCursorVisible(v1->wordDisplay, 0);
            EasyChatWordColumns_SetVisible(v1->wordColumns, 1);
            EasyChatWordListScreen_FinishTask(v0);
        }
    }
}

static void EasyChatWordListScreen_UpdateWordColumnTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatWordDisplay_SetCursorPosition(v1->wordDisplay, EasyChat_GetCurrentWordSlot(v1->easyChatApp));
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_UpdatePageIndicatorTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatWordColumns_SetActiveColumn(v1->wordColumns, EasyChat_GetWordColumn(v1->easyChatApp));
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_UpdateCategoryCursorTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatCategories_DrawCursor(v1->categoriesContext, EasyChat_GetCategoryCursorPos(v1->easyChatApp));
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_UpdateWordDisplayTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatWordListView_SetCursorPosition(v1->wordListView, EasyChat_GetWordSelectCursorIndex(v1->easyChatApp));
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_ScrollWordListTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    switch (v0->state) {
    case 0:
        EasyChatWordListView_Scroll(v1->wordListView, EasyChat_GetWordSelectScrollDirection(v1->easyChatApp));
        v0->state++;
        break;
    case 1:
        if (EasyChatWordListView_IsScrollDone(v1->wordListView)) {
            EasyChatPageButtons_SetVisible(v1->pageButtons, 1);
            EasyChatWordListScreen_FinishTask(v0);
        }
        break;
    }
}

static void EasyChatWordListScreen_SetPageTextDefaultTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatWordDisplay_SetInstructionText(v1->wordDisplay, 0);
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_SetPageTextDownTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatWordDisplay_SetInstructionText(v1->wordDisplay, 2);
    EasyChatWordDisplay_DrawPageIndicator(v1->wordDisplay, EasyChat_GetMenuCursorIndex(v0->easyChatApp));

    if (EasyChatWordColumns_IsVisible(v1->wordColumns)) {
        EasyChatWordColumns_SetEdgeAnim(v1->wordColumns);
    } else {
        EasyChatWordDisplay_SetCursorIdle(v1->wordDisplay);
    }

    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_SetPageTextUpTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatWordDisplay_SetInstructionText(v1->wordDisplay, 3);
    EasyChatWordDisplay_DrawPageIndicator(v1->wordDisplay, EasyChat_GetMenuCursorIndex(v0->easyChatApp));

    if (EasyChatWordColumns_IsVisible(v1->wordColumns)) {
        EasyChatWordColumns_SetEdgeAnim(v1->wordColumns);
    } else {
        EasyChatWordDisplay_SetCursorIdle(v1->wordDisplay);
    }

    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_SetPageTextNoneTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatWordDisplay_SetInstructionText(v1->wordDisplay, 1);
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_UpdatePageArrowTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatWordDisplay_MovePageIndicatorArrow(v1->wordDisplay, EasyChat_GetMenuCursorIndex(v0->easyChatApp));
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_ResetPageTextTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatWordDisplay_SetInstructionText(v1->wordDisplay, 0);
    EasyChatWordDisplay_ErasePageIndicator(v1->wordDisplay);

    if (EasyChatWordColumns_IsVisible(v1->wordColumns)) {
        EasyChatWordColumns_SetDefaultAnim(v1->wordColumns);
    } else {
        EasyChatWordDisplay_SetCursorActive(v1->wordDisplay);
    }

    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_PageUpPressedTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatPageButtons_SetPressedState(v1->pageButtons, 0, 1);
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_PageDownPressedTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatPageButtons_SetPressedState(v1->pageButtons, 1, 1);
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_PageUpReleasedTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatPageButtons_SetPressedState(v1->pageButtons, 0, 0);
    EasyChatWordListScreen_FinishTask(v0);
}

static void EasyChatWordListScreen_PageDownReleasedTask(SysTask *param0, void *param1)
{
    EasyChatWordListScreenTask *v0 = param1;
    EasyChatWordListScreen *v1 = v0->wordListScreen;

    EasyChatPageButtons_SetPressedState(v1->pageButtons, 1, 0);
    EasyChatWordListScreen_FinishTask(v0);
}

u32 EasyChatWordListScreen_GetWordSlotCount(EasyChatWordListScreen *param0)
{
    return EasyChatWordDisplay_GetWordSlotCount(param0->wordDisplay);
}

BgConfig *EasyChatWordListScreen_GetBgConfig(EasyChatWordListScreen *param0)
{
    return param0->bgConfig;
}

SpriteList *EasyChatWordListScreen_GetSpriteList(EasyChatWordListScreen *param0)
{
    return param0->spriteList;
}

void EasyChatWordListScreen_SetupSpriteResources(EasyChatWordListScreen *param0, SpriteResourcesHeader *param1, u32 param2, u32 param3)
{
    param1->imageProxy = &param0->imageProxy[param2];
    param1->paletteProxy = &param0->paletteProxy[param2];
    param1->cellBank = param0->cellBank[param2];
    param1->cellAnimBank = param0->cellAnimBank[param2];
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

    v0.list = param0->spriteList;
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
