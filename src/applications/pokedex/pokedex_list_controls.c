#include "applications/pokedex/pokedex_list_controls.h"

#include <nitro.h>
#include <string.h>

#include "applications/pokedex/pokedex_screen_transition.h"
#include "applications/pokedex/pokedex_list.h"
#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/pokedex_data_manager.h"
#include "applications/pokedex/pokedex_graphics.h"
#include "applications/pokedex/pokedex_graphics_manager.h"
#include "applications/pokedex/pokedex_main.h"
#include "applications/pokedex/pokedex_sort.h"
#include "applications/pokedex/pokedex_sort_data.h"
#include "applications/pokedex/pokedex_text_manager.h"
#include "applications/pokedex/struct_pokedex_screen_state.h"
#include "applications/pokedex/struct_pokedex_list_state.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "bg_window.h"
#include "brightness_controller.h"
#include "heap.h"
#include "math_util.h"
#include "narc.h"
#include "pltt_transfer.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "system.h"
#include "touch_screen.h"
#include "touch_screen_actions.h"
#include "font_oam.h"

#include "res/graphics/pokedex/zukan.naix"
#include "res/text/bank/pokedex.h"

typedef struct {
    int unk_00[7];
    PokedexListState *unk_1C;
    int *unk_20;
    enum HeapID heapID;
} PokedexListControls;

typedef struct {
    PokedexGraphicData *unk_00;
} PokedexListControlsUnused;

typedef struct {
    TouchScreenActions *unk_00;
    void *unk_04;
    TouchScreenHitTable *unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    fx32 unk_1C;
    BOOL unk_20;
} PokedexListControlsData;

typedef struct {
    PokedexListControlsData *unk_00;
    PokedexListControls *unk_04;
} PokedexListControlsTouchHandler;

typedef struct {
    Sprite *unk_00[3];
    PokedexTextData *unk_0C[3];
    Sprite *unk_18;
    Sprite *unk_1C;
    Sprite *unk_20;
    PokedexTextData *unk_24;
    u16 unk_28;
    u16 unk_2A;
    SpriteResource *unk_2C[4];
} PokedexListControlsGraphics;

static PokedexListControls *AllocState(enum HeapID heapID, PokedexApp *param1);
static PokedexGraphicData **AllocGraphics(enum HeapID heapID, PokedexApp *param1);
static PokedexScreenState *AllocScreenStates(enum HeapID heapID, PokedexApp *param1);
static void FreeState(PokedexListControls *param0);
static void FreeGraphics(PokedexGraphicData **param0);
static void FreeScreenStates(PokedexScreenState *param0);
static int GetNumScreenStates(void);
static int InitData(PokedexDataManager *dataMan, void *data);
static int UpdateData(PokedexDataManager *dataMan, void *data);
static int ExitData(PokedexDataManager *dataMan, void *data);
static int InitGraphics(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan);
static int UpdateGraphics(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan);
static int ExitGraphics(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan);
static void SetButtonText(Sprite *param0, PokedexTextData *textData, int param2, int param3, int param4);
static void InitTouchControls(PokedexListControlsData *param0, PokedexListControls *param1, enum HeapID heapID);
static void UpdateTouchControls(PokedexListControlsData *param0, PokedexListControls *param1);
static void FreeTouchControls(PokedexListControlsData *param0);
static void TouchButtonCallback(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void UpdateButtonHighlight(PokedexListControls *param0);
static void LoadGraphics(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, const PokedexListControls *param2, enum HeapID heapID);
static void UnloadGraphics(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, enum HeapID heapID);
static void LoadBackground(PokedexGraphicData **param0, const PokedexListControls *param1, enum HeapID heapID);
static void LoadButtonResources(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, int param2);
static void UnloadButtonResources(PokedexListControlsGraphics *param0, PokedexGraphicData **param1);
static void CreateButtonSprites(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, const PokedexListControls *param2, int param3);
static void DeleteButtonSprites(PokedexListControlsGraphics *param0);
static void CreateButtonText(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, const PokedexListControls *param2, int param3);
static void FreeButtonText(PokedexListControlsGraphics *param0);
static void LoadScrollWheel(PokedexGraphicData **param0, enum HeapID heapID);
static void UnloadScrollWheel(PokedexGraphicData **param0, enum HeapID heapID);
static void SelectEntry(PokedexListControls *param0, int param1);
static void UpdateDialScroll(PokedexListControlsData *param0, PokedexListControls *param1);
static void ComputeDialDrag(PokedexListControlsData *param0);
static void RotateScrollWheel(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, int param2, fx32 param3);
static void UpdateScrollWheelRotation(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, const PokedexListControls *param2);
static void UpdateDialDeceleration(PokedexListControlsData *param0, int param1, int param2);
static BOOL CanStepSelection(PokedexListControlsData *param0, PokedexSortData *param1);
static BOOL TryTakeStep(PokedexListControlsData *param0, PokedexSortData *param1);
static void StopDialScroll(PokedexListControlsData *param0, PokedexListControls *param1);
static fx32 UpdateDialSpeed(fx32 param0, s32 param1);

void PokedexListControls_Init(PokedexScreenManager *param0, PokedexApp *param1, enum HeapID heapID)
{
    PokedexListControls *v0;
    PokedexGraphicData **v1;
    PokedexScreenState *v2;

    v0 = AllocState(heapID, param1);
    v1 = AllocGraphics(heapID, param1);
    v2 = AllocScreenStates(heapID, param1);

    param0->pageData = v0;
    param0->pageGraphics = v1;
    param0->screenStates = v2;
    param0->numStates = GetNumScreenStates();

    param0->dataFunc[0] = InitData;
    param0->dataFunc[1] = UpdateData;
    param0->dataFunc[2] = ExitData;
    param0->graphicsFunc[0] = InitGraphics;
    param0->graphicsFunc[1] = UpdateGraphics;
    param0->graphicsFunc[2] = ExitGraphics;
}

void PokedexListControls_Free(PokedexScreenManager *param0)
{
    FreeState(param0->pageData);
    FreeGraphics(param0->pageData); // should be pageGraphics?
    FreeScreenStates(param0->screenStates);
}

static PokedexListControls *AllocState(enum HeapID heapID, PokedexApp *param1)
{
    PokedexListControls *v0;
    PokedexScreenManager *v1;
    int v2;

    v0 = Heap_Alloc(heapID, sizeof(PokedexListControls));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexListControls));

    v1 = PokedexMain_GetScreenManager(param1, 0);
    v0->unk_1C = v1->pageData;

    for (v2 = 0; v2 < 7; v2++) {
        v0->unk_00[v2] = (3 + 1);
    }

    v0->unk_20 = PokedexMain_GetTransitionRequest2(param1);
    v0->heapID = heapID;

    return v0;
}

static PokedexGraphicData **AllocGraphics(enum HeapID heapID, PokedexApp *param1)
{
    PokedexGraphicData **v0;
    PokedexScreenManager *v1;

    v0 = Heap_Alloc(heapID, sizeof(PokedexGraphicData *));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexGraphicData *));

    *v0 = PokedexMain_GetGraphicData(param1);

    return v0;
}

static PokedexScreenState *AllocScreenStates(enum HeapID heapID, PokedexApp *param1)
{
    PokedexScreenState *v0;
    int v1 = GetNumScreenStates();

    v0 = Heap_Alloc(heapID, sizeof(PokedexScreenState) * v1);

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexScreenState) * v1);

    Pokedex_021D4878(&v0[0], param1, heapID, (0x1 << 0));

    return v0;
}

static void FreeState(PokedexListControls *param0)
{
    GF_ASSERT(param0);
    Heap_Free(param0);
}

static void FreeGraphics(PokedexGraphicData **param0)
{
    GF_ASSERT(param0);
    Heap_Free(param0);
}

static void FreeScreenStates(PokedexScreenState *param0)
{
    GF_ASSERT(param0);

    PokedexScreenState_Free(&param0[0]);
    Heap_Free(param0);
}

static int GetNumScreenStates(void)
{
    return 1;
}

static int InitData(PokedexDataManager *dataMan, void *data)
{
    PokedexListControls *v0 = data;
    PokedexListControlsData *v1;
    int v2;

    dataMan->pageData = Heap_Alloc(dataMan->heapID, sizeof(PokedexListControlsData));

    GF_ASSERT(dataMan->pageData);
    memset(dataMan->pageData, 0, sizeof(PokedexListControlsData));

    v1 = dataMan->pageData;
    v1->unk_1C = (FX32_CONST(0.30f));

    for (v2 = 0; v2 < 7; v2++) {
        v0->unk_00[v2] = (3 + 1);
    }

    InitTouchControls(dataMan->pageData, v0, dataMan->heapID);
    return 1;
}

static int UpdateData(PokedexDataManager *dataMan, void *data)
{
    PokedexListControls *v0 = data;
    PokedexListControlsData *v1 = dataMan->pageData;

    if (dataMan->exit == 1) {
        return 1;
    }

    if (dataMan->unchanged == 1) {
        return 0;
    }

    UpdateDialDeceleration(v1, v0->unk_1C->unk_0C, v0->unk_1C->unk_08);
    UpdateTouchControls(v1, v0);

    if (v0->unk_1C->unk_20 == 0) {
        UpdateDialScroll(v1, v0);
    } else {
        v1->unk_0C = 0;
        v1->unk_10 = 0;
    }

    return 0;
}

static int ExitData(PokedexDataManager *dataMan, void *data)
{
    FreeTouchControls(dataMan->pageData);
    Heap_Free(dataMan->pageData);

    return 1;
}

static int InitGraphics(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan)
{
    const PokedexListControls *v0 = data;
    const PokedexListControlsData *v1 = dataMan->pageData;
    PokedexGraphicData **v2 = graphics;
    PokedexListControlsGraphics *v3 = graphicsMan->pageGraphics;
    BOOL v4;

    switch (graphicsMan->state) {
    case 0:
        graphicsMan->pageGraphics = Heap_Alloc(graphicsMan->heapID, sizeof(PokedexListControlsGraphics));
        GF_ASSERT(graphicsMan->pageGraphics);
        memset(graphicsMan->pageGraphics, 0, sizeof(PokedexListControlsGraphics));
        graphicsMan->state++;
        break;
    case 1:
        LoadGraphics(v3, v2, v0, graphicsMan->heapID);
        graphicsMan->state++;
        break;
    case 2:
        BrightnessController_StartTransition(4, 0, -16, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD), BRIGHTNESS_SUB_SCREEN);
        graphicsMan->state++;
        break;
    case 3:
        if (BrightnessController_IsTransitionComplete(BRIGHTNESS_SUB_SCREEN)) {
            graphicsMan->state++;
        }
        break;
    case 4:
        graphicsMan->state++;
        return 1;
    }

    return 0;
}

static int UpdateGraphics(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan)
{
    const PokedexListControls *v0 = data;
    const PokedexListControlsData *v1 = dataMan->pageData;
    PokedexGraphicData **v2 = graphics;
    PokedexListControlsGraphics *v3 = graphicsMan->pageGraphics;

    PokedexMain_SetCursorAnimFrame(v3->unk_00[0], v0->unk_00[0]);
    PokedexMain_SetCursorAnimFrame(v3->unk_00[1], v0->unk_00[1]);
    PokedexMain_SetCursorAnimFrame(v3->unk_00[2], v0->unk_00[2]);
    PokedexMain_SetCursorAnimFrame(v3->unk_18, v0->unk_00[3]);
    PokedexMain_SetCursorAnimFrame(v3->unk_1C, v0->unk_00[4]);
    SetButtonText(v3->unk_00[0], v3->unk_0C[0], -14, 3, 5);
    SetButtonText(v3->unk_00[1], v3->unk_0C[1], -14, 3, 5);
    SetButtonText(v3->unk_00[2], v3->unk_0C[2], -14, 2, 5);

    if (v0->unk_1C->unk_20 == 0) {
        RotateScrollWheel(v3, v2, CalcRadialAngle(524, v1->unk_0C), v1->unk_1C);
    } else if (v0->unk_1C->unk_20 == 1) {
        UpdateScrollWheelRotation(v3, v2, v0);
    } else {
        (void)0;
    }

    return 0;
}

static int ExitGraphics(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan)
{
    const PokedexListControls *v0 = data;
    const PokedexListControlsData *v1 = dataMan->pageData;
    PokedexGraphicData **v2 = graphics;
    PokedexListControlsGraphics *v3 = graphicsMan->pageGraphics;
    BOOL v4;

    switch (graphicsMan->state) {
    case 0:
        BrightnessController_StartTransition(4, -16, 0, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD), BRIGHTNESS_SUB_SCREEN);
        graphicsMan->state++;
        break;
    case 1:
        if (BrightnessController_IsTransitionComplete(BRIGHTNESS_SUB_SCREEN)) {
            graphicsMan->state++;
        }
        break;
    case 2:
        UnloadGraphics(v3, v2, graphicsMan->heapID);
        graphicsMan->state++;
        break;
    case 3:
        Heap_Free(graphicsMan->pageGraphics);
        graphicsMan->pageGraphics = NULL;
        graphicsMan->state++;
        break;
    case 4:
        return 1;
    }

    return 0;
}

static void InitTouchControls(PokedexListControlsData *param0, PokedexListControls *param1, enum HeapID heapID)
{
    PokedexListControlsTouchHandler *v0;

    param0->unk_08 = Heap_Alloc(heapID, sizeof(TouchScreenHitTable) * 7);

    PokedexMain_SetHitTableRect(&param0->unk_08[0], 40 - (48 / 2), 40 + (48 / 2), 48 - (96 / 2), 48 + (96 / 2));
    PokedexMain_SetHitTableRect(&param0->unk_08[1], 88 - (48 / 2), 88 + (48 / 2), 48 - (96 / 2), 48 + (96 / 2));
    PokedexMain_SetHitTableRect(&param0->unk_08[2], 152 - (80 / 2), 152 + (80 / 2), 48 - (96 / 2), 48 + (96 / 2));
    PokedexMain_SetHitTableRect(&param0->unk_08[3], 64 - (16 / 2), 64 + (16 / 2), 124 - (16 / 2), 124 + (16 / 2));
    PokedexMain_SetHitTableRect(&param0->unk_08[4], 146 - (16 / 2), 146 + (16 / 2), 124 - (16 / 2), 124 + (16 / 2));

    param0->unk_08[5].circle.code = TOUCHSCREEN_USE_CIRCLE;
    param0->unk_08[5].circle.x = (128 + 120);
    param0->unk_08[5].circle.y = (104 + -0);
    param0->unk_08[5].circle.r = 104;

    PokedexMain_SetHitTableRect(&param0->unk_08[6], (8 - 8), (8 - 8) + 16, (124 - 8), (124 - 8) + 64);

    v0 = Heap_Alloc(heapID, sizeof(PokedexListControlsTouchHandler));
    v0->unk_00 = param0;
    v0->unk_04 = param1;

    param0->unk_04 = v0;
    param0->unk_00 = TouchScreenActions_RegisterHandler(param0->unk_08, 7, TouchButtonCallback, v0, heapID);
}

static void UpdateTouchControls(PokedexListControlsData *param0, PokedexListControls *param1)
{
    int v0;

    for (v0 = 0; v0 < 7; v0++) {
        param1->unk_00[v0] = (3 + 1);
    }

    UpdateButtonHighlight(param1);
    TouchScreenActions_HandleAction(param0->unk_00);

    if (CanStepSelection(param0, param1->unk_1C->unk_04) == 0) {
        param0->unk_0C = 0;
    }

    if (param1->unk_00[5] != (3 + 1)) {
        param0->unk_1C = UpdateDialSpeed(param0->unk_1C, param0->unk_0C);
    } else {
        param0->unk_1C = UpdateDialSpeed(param0->unk_1C, 0);
    }
}

static void FreeTouchControls(PokedexListControlsData *param0)
{
    TouchScreenActions_Free(param0->unk_00);
    Heap_Free(param0->unk_04);
    Heap_Free(param0->unk_08);

    param0->unk_08 = NULL;
}

static void TouchButtonCallback(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    PokedexListControlsTouchHandler *v0 = param2;
    PokedexListControls *v1 = v0->unk_04;
    PokedexListControlsData *v2 = v0->unk_00;
    PokedexSortData *v3 = v1->unk_1C->unk_04;
    int v4;
    int v5;

    v1->unk_00[param0] = param1;

    switch (param1) {
    case TOUCH_BUTTON_PRESSED:
        v2->unk_14 = gSystem.touchX;
        v2->unk_18 = gSystem.touchY;
        break;
    case TOUCH_BUTTON_HELD:
        switch (param0) {
        case 0:
            v1->unk_1C->unk_34 = 1;
            break;
        case 1:
            v1->unk_1C->unk_30 = 1;
            break;
        case 2:
            v1->unk_1C->unk_2C = 1;
            break;
        case 3:
            if (v2->unk_20 == 0) {
                SelectEntry(v1, 0);
            }
            break;
        case 4:
            if (v2->unk_20 == 0) {
                v4 = PokedexSort_CaughtStatusLength(v3);
                SelectEntry(v1, v4 - 1);
            }
            break;
        case 6:
            if (v1->unk_1C->unk_04->unk_1740 == 0) {
                v1->unk_1C->unk_28 = 1;
            } else {
                v1->unk_1C->unk_24 = 1;
            }
            break;
        default:
            break;
        }

        if (param0 == 5) {
            if (v1->unk_1C->unk_20 == 0) {
                ComputeDialDrag(v2);

                if ((v2->unk_0C <= 16) && (v2->unk_0C >= -16)) {
                    v2->unk_0C = 0;
                }
            }

            v2->unk_14 = gSystem.touchX;
            v2->unk_18 = gSystem.touchY;
        }

        v2->unk_20 = 1;
        break;
    default:
        v2->unk_20 = 0;
        break;
    }
}

static void LoadGraphics(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, const PokedexListControls *param2, enum HeapID heapID)
{
    LoadBackground(param1, param2, heapID);
    LoadScrollWheel(param1, heapID);
    LoadButtonResources(param0, param1, heapID);
    CreateButtonSprites(param0, param1, param2, heapID);
    CreateButtonText(param0, param1, param2, heapID);

    Bg_SetPriority(BG_LAYER_SUB_3, 3);
}

static void UnloadGraphics(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, enum HeapID heapID)
{
    FreeButtonText(param0);
    DeleteButtonSprites(param0);
    UnloadButtonResources(param0, param1);
    UnloadScrollWheel(param1, heapID);

    Bg_SetPriority(BG_LAYER_SUB_3, 1);
}

static void LoadBackground(PokedexGraphicData **param0, const PokedexListControls *param1, enum HeapID heapID)
{
    void *v0;
    NNSG2dScreenData *v1;
    BgConfig *v2 = (*param0)->bgConfig;

    PokedexGraphics_LoadGraphicNarcPaletteData(*param0, background_scroll_default_NCLR, 4, 0, 0, heapID);

    if (param1->unk_1C->unk_04->unk_1740 == 1) {
        PokedexGraphics_LoadGraphicNarcPaletteData(*param0, background_scroll_sinnoh_NCLR, 4, 3 * 32, 32, heapID);
    } else {
        if (PokedexSort_IsNationalDex(param1->unk_1C->unk_04) == 1) {
            PokedexGraphics_LoadGraphicNarcPaletteData(*param0, background_scroll_national_NCLR, 4, 3 * 32, 32, heapID);
        }
    }

    PokedexGraphics_LoadGraphicNarcCharacterData(*param0, scroll_sub_background_NCGR_lz, v2, 6, 0, 0, TRUE, heapID);

    v0 = PokedexGraphics_GetGraphicNarcTilemapData(*param0, scroll_sub_NSCR_lz, TRUE, &v1, heapID);

    Bg_LoadToTilemapRect(v2, 6, v1->rawData, 0, 0, v1->screenWidth / 8, v1->screenHeight / 8);
    Heap_Free(v0);
    Bg_ScheduleTilemapTransfer(v2, 6);
}

static void LoadButtonResources(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, int param2)
{
    PokedexGraphicData *v0 = *param1;
    NARC *v1 = PokedexGraphics_GetNARC(*param1);

    param0->unk_2C[0] = SpriteResourceCollection_AddTilesFrom(v0->spriteResourceCollection[0], v1, scroll_buttons_NCGR_lz, TRUE, scroll_buttons_NCGR_lz + 1000, NNS_G2D_VRAM_TYPE_2DSUB, param2);

    SpriteTransfer_RequestCharAtEnd(param0->unk_2C[0]);
    SpriteResource_ReleaseData(param0->unk_2C[0]);

    param0->unk_2C[1] = SpriteResourceCollection_AddPaletteFrom(v0->spriteResourceCollection[1], v1, buttons_NCLR, FALSE, buttons_NCLR + 1000, NNS_G2D_VRAM_TYPE_2DSUB, 12, param2);

    SpriteTransfer_RequestPlttFreeSpace(param0->unk_2C[1]);
    SpriteResource_ReleaseData(param0->unk_2C[1]);

    param0->unk_2C[2] = SpriteResourceCollection_AddFrom(v0->spriteResourceCollection[2], v1, scroll_buttons_cell_NCER_lz, TRUE, scroll_buttons_cell_NCER_lz + 1000, 2, param2);
    param0->unk_2C[3] = SpriteResourceCollection_AddFrom(v0->spriteResourceCollection[3], v1, scroll_buttons_anim_NANR_lz, TRUE, scroll_buttons_anim_NANR_lz + 1000, 3, param2);
}

static void UnloadButtonResources(PokedexListControlsGraphics *param0, PokedexGraphicData **param1)
{
    PokedexGraphicData *v0 = *param1;

    SpriteTransfer_ResetCharTransfer(param0->unk_2C[0]);
    SpriteTransfer_ResetPlttTransfer(param0->unk_2C[1]);
    SpriteResourceCollection_Remove(v0->spriteResourceCollection[0], param0->unk_2C[0]);
    SpriteResourceCollection_Remove(v0->spriteResourceCollection[1], param0->unk_2C[1]);
    SpriteResourceCollection_Remove(v0->spriteResourceCollection[2], param0->unk_2C[2]);
    SpriteResourceCollection_Remove(v0->spriteResourceCollection[3], param0->unk_2C[3]);
}

static void CreateButtonSprites(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, const PokedexListControls *param2, int param3)
{
    SpriteResourcesHeader v0;
    SpriteListTemplate v1;
    PokedexGraphicData *v2 = *param1;

    SpriteResourcesHeader_Init(&v0, scroll_buttons_NCGR_lz + 1000, buttons_NCLR + 1000, scroll_buttons_cell_NCER_lz + 1000, scroll_buttons_anim_NANR_lz + 1000, 0xffffffff, 0xffffffff, FALSE, 0, v2->spriteResourceCollection[0], v2->spriteResourceCollection[1], v2->spriteResourceCollection[2], v2->spriteResourceCollection[3], NULL, NULL);

    v1.list = v2->spriteList;
    v1.resourceData = &v0;
    v1.priority = 8;
    v1.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    v1.heapID = param3;

    v1.position.x = 48 << FX32_SHIFT;
    v1.position.y = 40 << FX32_SHIFT;
    v1.position.y += (192 << FX32_SHIFT);

    param0->unk_00[0] = SpriteList_Add(&v1);

    Sprite_SetAnim(param0->unk_00[0], 2);

    if (param2->unk_1C->unk_04->unk_1740 == 1) {
        Sprite_SetDrawFlag(param0->unk_00[0], FALSE);
    }

    v1.position.x = 48 << FX32_SHIFT;
    v1.position.y = 88 << FX32_SHIFT;
    v1.position.y += (192 << FX32_SHIFT);

    param0->unk_00[1] = SpriteList_Add(&v1);

    Sprite_SetAnim(param0->unk_00[1], 0);

    if ((PokedexSort_CanSetNationalDex(param2->unk_1C->unk_04, 1) == 0) || (param2->unk_1C->unk_04->unk_1740 == 1)) {
        Sprite_SetDrawFlag(param0->unk_00[1], FALSE);
    }

    v1.position.x = 48 << FX32_SHIFT;
    v1.position.y = 152 << FX32_SHIFT;
    v1.position.y += (192 << FX32_SHIFT);

    param0->unk_00[2] = SpriteList_Add(&v1);

    Sprite_SetAnim(param0->unk_00[2], 1);

    v1.position.x = 124 << FX32_SHIFT;
    v1.position.y = 64 << FX32_SHIFT;
    v1.position.y += (192 << FX32_SHIFT);

    param0->unk_18 = SpriteList_Add(&v1);

    Sprite_SetAnim(param0->unk_18, 3);

    v1.position.x = 124 << FX32_SHIFT;
    v1.position.y = 146 << FX32_SHIFT;
    v1.position.y += (192 << FX32_SHIFT);

    param0->unk_1C = SpriteList_Add(&v1);

    Sprite_SetAnim(param0->unk_1C, 4);

    v1.position.x = 124 << FX32_SHIFT;
    v1.position.y = 8 << FX32_SHIFT;
    v1.position.y += (192 << FX32_SHIFT);

    param0->unk_20 = SpriteList_Add(&v1);

    Sprite_SetAnim(param0->unk_20, 5);
}

static void DeleteButtonSprites(PokedexListControlsGraphics *param0)
{
    Sprite_Delete(param0->unk_00[0]);
    Sprite_Delete(param0->unk_00[1]);
    Sprite_Delete(param0->unk_00[2]);
    Sprite_Delete(param0->unk_18);
    Sprite_Delete(param0->unk_1C);
    Sprite_Delete(param0->unk_20);
}

static void CreateButtonText(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, const PokedexListControls *param2, int param3)
{
    Window *v0;
    PokedexDisplayBox displayBox;
    SpriteResource *v2;
    PokedexGraphicData *v3 = *param1;
    int v4;

    GF_ASSERT(param0->unk_00[0]);

    v2 = SpriteResourceCollection_Find(v3->spriteResourceCollection[1], buttons_NCLR + 1000);

    displayBox.textMan = v3->textMan;
    displayBox.paletteProxy = SpriteTransfer_GetPaletteProxy(v2, NULL);
    displayBox.x = -40;
    displayBox.y = -14;
    displayBox.spriteResourcePriority = 0;
    displayBox.spriteListPriority = 0;
    displayBox.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    displayBox.heapID = param3;

    v4 = PlttTransfer_GetPlttOffset(displayBox.paletteProxy, NNS_G2D_VRAM_TYPE_2DSUB);
    v0 = PokedexTextManager_NewWindow(v3->textMan, 10, 4);

    PokedexTextManager_DisplayMessage(v3->textMan, v0, TEXT_BANK_POKEDEX, pl_msg_pokedex_search, 0, 0);

    displayBox.window = v0;
    displayBox.sprite = param0->unk_00[0];
    param0->unk_0C[0] = PokedexTextManager_NextTextData(&displayBox);

    FontOAM_SetExplicitPalette(param0->unk_0C[0]->fontOAM, v4 + 3);

    if (param2->unk_1C->unk_04->unk_1740 == 1) {
        FontOAM_SetDrawFlag(param0->unk_0C[0]->fontOAM, 0);
    }

    PokedexTextManager_FreeWindow(v0);
    v0 = PokedexTextManager_NewWindow(v3->textMan, 10, 4);
    PokedexTextManager_DisplayMessage(v3->textMan, v0, TEXT_BANK_POKEDEX, pl_msg_pokedex_switch, 0, 0);

    displayBox.window = v0;
    displayBox.sprite = param0->unk_00[1];
    param0->unk_0C[1] = PokedexTextManager_NextTextData(&displayBox);

    FontOAM_SetExplicitPalette(param0->unk_0C[1]->fontOAM, v4 + 3);

    if ((PokedexSort_CanSetNationalDex(param2->unk_1C->unk_04, 1) == 0) || (param2->unk_1C->unk_04->unk_1740 == 1)) {
        FontOAM_SetDrawFlag(param0->unk_0C[1]->fontOAM, 0);
    }

    PokedexTextManager_FreeWindow(v0);
    v0 = PokedexTextManager_NewWindow(v3->textMan, 10, 4);
    PokedexTextManager_DisplayMessage(v3->textMan, v0, TEXT_BANK_POKEDEX, pl_msg_pokedex_check, 0, 0);

    displayBox.window = v0;
    displayBox.sprite = param0->unk_00[2];
    param0->unk_0C[2] = PokedexTextManager_NextTextData(&displayBox);

    FontOAM_SetExplicitPalette(param0->unk_0C[2]->fontOAM, v4 + 2);
    PokedexTextManager_FreeWindow(v0);

    v0 = PokedexTextManager_NewWindow(v3->textMan, 14, 2);

    if (param2->unk_1C->unk_04->unk_1740 == 0) {
        PokedexTextManager_DisplayMessage(v3->textMan, v0, TEXT_BANK_POKEDEX, pl_msg_pokedex_quit, 0, 0);
    } else {
        PokedexTextManager_DisplayMessage(v3->textMan, v0, TEXT_BANK_POKEDEX, pl_msg_pokedex_cancel, 0, 0);
    }

    displayBox.window = v0;
    displayBox.sprite = param0->unk_20;
    displayBox.x = 10;
    displayBox.y = -8;
    param0->unk_24 = PokedexTextManager_NextTextData(&displayBox);

    FontOAM_SetExplicitPalette(param0->unk_24->fontOAM, v4 + 1);
    PokedexTextManager_FreeWindow(v0);
}

static void FreeButtonText(PokedexListControlsGraphics *param0)
{
    PokedexTextManager_FreeTextData(param0->unk_0C[0]);
    PokedexTextManager_FreeTextData(param0->unk_0C[1]);
    PokedexTextManager_FreeTextData(param0->unk_0C[2]);
    PokedexTextManager_FreeTextData(param0->unk_24);
}

static void LoadScrollWheel(PokedexGraphicData **param0, enum HeapID heapID)
{
    void *v0;
    NNSG2dScreenData *v1;
    BgConfig *v2 = (*param0)->bgConfig;

    PokedexGraphics_LoadGraphicNarcCharacterData(*param0, scroll_wheel_NCGR_lz, v2, 7, 0, 0, TRUE, heapID);

    v0 = PokedexGraphics_GetGraphicNarcTilemapData(*param0, scroll_wheel_NSCR_lz, TRUE, &v1, heapID);

    Bg_LoadToTilemapRect(v2, 7, v1->rawData, 0, 0, v1->screenWidth / 8, v1->screenHeight / 8);
    Heap_Free(v0);
    Bg_ScheduleTilemapTransfer(v2, 7);
    Bg_SetOffset(v2, BG_LAYER_SUB_3, 0, -120);
    Bg_SetOffset(v2, BG_LAYER_SUB_3, 3, 0);
}

static void UnloadScrollWheel(PokedexGraphicData **param0, enum HeapID heapID)
{
    BgConfig *v0 = (*param0)->bgConfig;

    Bg_ClearTilesRange(7, 64, 0, heapID);
    Bg_ClearTilemap(v0, BG_LAYER_SUB_3);
}

static void UpdateDialScroll(PokedexListControlsData *param0, PokedexListControls *param1)
{
    int v0;
    PokedexSortData *v1 = param1->unk_1C->unk_04;

    if (param1->unk_1C->unk_0C <= 0) {
        if (param0->unk_10 != 0) {
            if (TryTakeStep(param0, v1) == 0) {
                StopDialScroll(param0, param1);
            } else {
                param1->unk_1C->unk_0C = (64 * 10);
                Sound_PlayEffect(SEQ_SE_DP_DENSI06_sseq);
            }
        } else {
            param1->unk_1C->unk_08 = 0;
        }
    }

    if (param0->unk_10 < 0) {
        param1->unk_1C->unk_08 = 1;
    } else {
        if (param0->unk_10 > 0) {
            param1->unk_1C->unk_08 = 2;
        }
    }

    if (param1->unk_1C->unk_08 != 0) {
        if (param0->unk_10 < 0) {
            v0 = -param0->unk_10;
        } else {
            v0 = param0->unk_10;
        }

        v0 /= (1024 / (64 * 10));
        param1->unk_1C->unk_0C -= v0;

        if (param1->unk_1C->unk_0C < 0) {
            param1->unk_1C->unk_0C = 0;
        }
    }
}

static void ComputeDialDrag(PokedexListControlsData *param0)
{
    int v0, v1;
    int v2, v3;

    v1 = param0->unk_14 - (128 + 120);
    v0 = param0->unk_18 - (104 + -0);
    v3 = gSystem.touchX - (128 + 120);
    v2 = gSystem.touchY - (104 + -0);

    param0->unk_0C = ApproximateArcLength(v1, v0, v3, v2, 524);
    param0->unk_0C *= 10;
}

static void RotateScrollWheel(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, int param2, fx32 param3)
{
    int v0 = FX_Mul(param2 * FX32_ONE, param3) >> FX32_SHIFT;

    param0->unk_28 += v0;
    param0->unk_28 &= 0xffff;

    Bg_ScheduleAffineRotation((*param1)->bgConfig, 7, 0, param0->unk_28 / 182);
    Bg_ScheduleAffineRotationCenter((*param1)->bgConfig, 7, 9, 128);
    Bg_ScheduleAffineRotationCenter((*param1)->bgConfig, 7, 12, 104);

    param0->unk_2A = param0->unk_28;
}

static void UpdateScrollWheelRotation(PokedexListControlsGraphics *param0, PokedexGraphicData **param1, const PokedexListControls *param2)
{
    int v0;
    int v1;
    int v2 = (64 * 10) - param2->unk_1C->unk_0C;

    v1 = ((25 * 0xffff) / 360) * v2;
    v0 = v1 / (64 * 10);

    if (param2->unk_1C->unk_08 == 1) {
        v0 = -v0;
    }

    param0->unk_28 = param0->unk_2A + v0;
    param0->unk_28 &= 0xffff;

    Bg_ScheduleAffineRotation((*param1)->bgConfig, 7, 0, param0->unk_28 / 182);
    Bg_ScheduleAffineRotationCenter((*param1)->bgConfig, 7, 9, 128);
    Bg_ScheduleAffineRotationCenter((*param1)->bgConfig, 7, 12, 104);

    if (param2->unk_1C->unk_0C == 0) {
        param0->unk_2A = param0->unk_28;
    }
}

static void UpdateDialDeceleration(PokedexListControlsData *param0, int param1, int param2)
{
    if (param0->unk_0C > 0) {
        if (param0->unk_0C - 2 >= 4) {
            param0->unk_0C -= 2;
        } else {
            param0->unk_0C = 4;
        }
    } else {
        if (param0->unk_0C + 2 <= -4) {
            param0->unk_0C += 2;
        } else {
            param0->unk_0C = -4;
        }
    }

    param0->unk_10 = param0->unk_0C;

    if ((param0->unk_0C <= ((1024 / (64 * 10)) + 32)) && (param0->unk_0C >= -((1024 / (64 * 10)) + 32))) {
        if (param1 == 0) {
            param0->unk_10 = 0;

            if ((param0->unk_0C <= 4) && (param0->unk_0C >= -4)) {
                param0->unk_0C = 0;
                param0->unk_1C = (FX32_CONST(0.30f));
            }
        } else {
            if (param2 == 1) {
                param0->unk_10 = -((1024 / (64 * 10)) + 32);
                param0->unk_0C = -((1024 / (64 * 10)) + 32);
            } else {
                param0->unk_10 = ((1024 / (64 * 10)) + 32);
                param0->unk_0C = ((1024 / (64 * 10)) + 32);
            }
        }
    }
}

static void SetButtonText(Sprite *param0, PokedexTextData *textData, int param2, int param3, int param4)
{
    PokedexMain_SetTextSprite(param0, textData, param2, param3, param4);
}

static void UpdateButtonHighlight(PokedexListControls *param0)
{
    PokedexListState *v0 = param0->unk_1C;

    if (v0->unk_2C) {
        param0->unk_00[2] = 2;
        return;
    }

    if (v0->unk_34) {
        param0->unk_00[0] = 2;
        return;
    }

    if (v0->unk_30) {
        param0->unk_00[1] = 2;
        return;
    }
}

static BOOL CanStepSelection(PokedexListControlsData *param0, PokedexSortData *param1)
{
    int v0;

    if (param0->unk_0C != 0) {
        if (param0->unk_0C < 0) {
            v0 = 1;
        } else {
            v0 = -1;
        }

        if (PokedexSort_IsValidStep(param1, v0) == 0) {
            return 0;
        }
    }

    return 1;
}

static BOOL TryTakeStep(PokedexListControlsData *param0, PokedexSortData *param1)
{
    int v0;

    if (param0->unk_10 != 0) {
        if (param0->unk_10 < 0) {
            v0 = 1;
        } else {
            v0 = -1;
        }

        if (PokedexSort_TakeStep(param1, v0) == 0) {
            return 0;
        }
    }

    return 1;
}

static void StopDialScroll(PokedexListControlsData *param0, PokedexListControls *param1)
{
    param0->unk_10 = 0;
    param0->unk_0C = 0;
    param1->unk_1C->unk_08 = 0;
}

static void SelectEntry(PokedexListControls *param0, int param1)
{
    if (PokedexList_IsActive(param0->unk_1C) == 0) {
        return;
    }

    PokedexSort_SetCurrentStatusIndex(param0->unk_1C->unk_04, param1);

    (*param0->unk_20) |= (0x1 << 0);

    param0->unk_1C->unk_0C = 0;
    param0->unk_1C->unk_20 = 2;
    param0->unk_1C->unk_10 = 1;
    param0->unk_1C->unk_14 = 0;
    param0->unk_1C->unk_08 = 0;
    param0->unk_1C->unk_1C = 0;
}

static fx32 UpdateDialSpeed(fx32 param0, s32 param1)
{
    int v0 = MATH_ABS(param1);

    if (v0 < 64) {
        if ((param0 - (FX32_CONST(0.01f))) >= (FX32_CONST(0.30f))) {
            param0 -= (FX32_CONST(0.01f));
        }
    } else {
        if ((param0 + (FX32_CONST(0.20f))) <= (FX32_CONST(1.0f))) {
            param0 += (FX32_CONST(0.20f));
        }
    }

    return param0;
}
