#include "applications/pokedex/pokedex_info_menu.h"

#include <nitro.h>
#include <string.h>

#include "applications/pokedex/infomain.h"
#include "applications/pokedex/infomain_foreign.h"
#include "applications/pokedex/pokedex_screen_transition.h"
#include "applications/pokedex/pokedex_area_map.h"
#include "applications/pokedex/pokedex_cry_screen.h"
#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/pokedex_data_manager.h"
#include "applications/pokedex/pokedex_graphics.h"
#include "applications/pokedex/pokedex_graphics_manager.h"
#include "applications/pokedex/pokedex_main.h"
#include "applications/pokedex/pokedex_panel.h"
#include "applications/pokedex/pokedex_sort.h"
#include "applications/pokedex/pokedex_sort_data.h"
#include "applications/pokedex/pokedex_text_manager.h"
#include "applications/pokedex/struct_pokedex_screen_state.h"
#include "applications/pokedex/struct_pokedex_list_state.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "bg_window.h"
#include "brightness_controller.h"
#include "heap.h"
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
    int *unk_00;
    PokedexSortData *unk_04;
    int unk_08;
    PokedexListState *unk_0C;
    InfoMainState *unk_10;
    PokedexScreenManager *unk_14;
    PokedexScreenManager *unk_18;
    PokedexScreenManager *unk_1C;
    PokedexScreenManager *unk_20;
    PokedexScreenManager *unk_24;
    BOOL unk_28;
    BOOL unk_2C;
    BOOL unk_30;
} PokedexInfoMenuState;

typedef struct {
    int unk_00;
    PokedexTextData *unk_04[5];
    SpriteResource *unk_18[4];
} PokedexInfoMenuGraphics;

typedef struct {
    int *unk_00;
    PokedexInfoMenuState *unk_04;
    PokedexSortData *unk_08;
    int unk_0C[6];
    BOOL unk_24;
    int unk_28;
    BOOL unk_2C;
    BOOL unk_30;
} PokedexInfoMenuData;

typedef struct {
    void *unk_00;
    void *unk_04;
} PokedexInfoMenuTouchHandler;

typedef struct {
    TouchScreenActions *unk_00;
    TouchScreenHitTable *unk_04;
    PokedexInfoMenuTouchHandler unk_08;
    int unk_10;
    PokedexPanelData *unk_14;
    PokedexCursorData *unk_18;
} PokedexInfoMenuPanelData;

typedef struct {
    Sprite *unk_00[6];
    SpriteResource *unk_18[4];
} PokedexInfoMenuSprites;

static PokedexInfoMenuState *AllocState(enum HeapID heapID, PokedexApp *param1);
static PokedexGraphicData **AllocGraphics(enum HeapID heapID, PokedexApp *param1);
static PokedexScreenState *AllocScreenStates(enum HeapID heapID, PokedexApp *param1);
static void FreeState(PokedexInfoMenuState *param0);
static void FreeGraphics(PokedexGraphicData **param0);
static void FreeScreenStates(PokedexScreenState *param0);
static int GetNumScreenStates(void);
static int InitData(PokedexDataManager *dataMan, void *data);
static int UpdateData(PokedexDataManager *dataMan, void *data);
static int ExitData(PokedexDataManager *dataMan, void *data);
static int InitGraphics(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan);
static int UpdateGraphics(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan);
static int ExitGraphics(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan);
static void Pokedex_021E3320(PokedexInfoMenuState *param0);
static BOOL Pokedex_021E2EC0(int param0);
static BOOL Pokedex_021E2EC4(PokedexInfoMenuState *param0, int param1, int param2);
static void Pokedex_021E2E10(PokedexInfoMenuState *param0);
static void Pokedex_021E2E00(PokedexInfoMenuState *param0);
static void Pokedex_021E3080(PokedexGraphicData **param0, PokedexInfoMenuGraphics *param1, const PokedexInfoMenuState *param2, enum HeapID heapID);
static void Pokedex_021E30BC(PokedexGraphicData **param0, PokedexInfoMenuGraphics *param1);
static void Pokedex_021E30E4(PokedexGraphicData **param0, const PokedexInfoMenuState *param1, enum HeapID heapID);
static void Pokedex_021E3178(PokedexGraphicData **param0, PokedexInfoMenuGraphics *param1, int param2);
static void Pokedex_021E3224(PokedexGraphicData **param0, PokedexInfoMenuGraphics *param1);
static void Pokedex_021E3268(PokedexGraphicData **param0, PokedexInfoMenuGraphics *param1, int param2);
static void Pokedex_021E326C(PokedexInfoMenuGraphics *param0);
static void Pokedex_021E331C(PokedexInfoMenuGraphics *param0, int param1);
static void Pokedex_021E3270(PokedexGraphicData **param0, PokedexInfoMenuGraphics *param1, int param2);
static void Pokedex_021E3304(PokedexInfoMenuGraphics *param0);
static void Pokedex_021E3FC0(PokedexInfoMenuGraphics *param0, int param1, int param2);
static void Pokedex_021E3BE0(PokedexInfoMenuGraphics *param0);
static void Pokedex_021E3BFC(PokedexInfoMenuGraphics *param0);
static PokedexInfoMenuData *Pokedex_021E33C4(enum HeapID heapID, PokedexApp *param1);
static PokedexGraphicData **Pokedex_021E3400(enum HeapID heapID, PokedexApp *param1);
static PokedexScreenState *Pokedex_021E3428(enum HeapID heapID, PokedexApp *param1);
static void Pokedex_021E342C(PokedexInfoMenuData *param0);
static void Pokedex_021E3440(PokedexGraphicData **param0);
static void Pokedex_021E3454(PokedexScreenState *param0);
static int Pokedex_021E3458(void);
static int Pokedex_021E345C(PokedexDataManager *dataMan, void *data);
static int Pokedex_021E34AC(PokedexDataManager *dataMan, void *data);
static int Pokedex_021E3520(PokedexDataManager *dataMan, void *data);
static int Pokedex_021E3540(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan);
static int Pokedex_021E35D0(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan);
static int Pokedex_021E3604(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan);
static BOOL Pokedex_021E3C18(PokedexInfoMenuData *param0, int param1, int param2);
static void Pokedex_021E3688(PokedexInfoMenuPanelData *param0, PokedexInfoMenuData *param1, enum HeapID heapID);
static void Pokedex_021E3724(PokedexInfoMenuData *param0);
static void Pokedex_021E3734(PokedexInfoMenuPanelData *param0, PokedexInfoMenuData *param1);
static void Pokedex_021E37B4(PokedexInfoMenuPanelData *param0);
static void Pokedex_021E37CC(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void Pokedex_021E3C6C(PokedexInfoMenuPanelData *param0, PokedexInfoMenuData *param1, enum HeapID heapID);
static void Pokedex_021E3D48(PokedexInfoMenuPanelData *param0, PokedexInfoMenuData *param1);
static void Pokedex_021E3E74(PokedexInfoMenuPanelData *param0);
static void Pokedex_021E3E8C(PokedexInfoMenuPanelData *param0, PokedexInfoMenuData *param1);
static void Pokedex_021E3EEC(PokedexInfoMenuPanelData *param0, PokedexInfoMenuData *param1);
static void Pokedex_021E3F2C(PokedexGraphicData **param0, const PokedexInfoMenuPanelData *param1, const PokedexInfoMenuData *param2);
static void Pokedex_021E3F48(PokedexGraphicData **param0, const PokedexInfoMenuPanelData *param1, const PokedexInfoMenuData *param2);
static void Pokedex_021E3F88(PokedexGraphicData **param0, const PokedexInfoMenuPanelData *param1);
static BOOL Pokedex_021E3F98(PokedexGraphicData **param0, BOOL param1);
static void Pokedex_021E3C2C(PokedexInfoMenuData *param0);
static void Pokedex_021E3C34(PokedexInfoMenuData *param0);
static void Pokedex_021E3C64(PokedexInfoMenuData *param0);
static void Pokedex_021E3900(PokedexInfoMenuSprites *param0, PokedexGraphicData **param1, const PokedexInfoMenuData *param2, enum HeapID heapID);
static void Pokedex_021E393C(PokedexInfoMenuSprites *param0, PokedexGraphicData **param1);
static void Pokedex_021E3960(PokedexGraphicData **param0, const PokedexInfoMenuData *param1, enum HeapID heapID);
static void Pokedex_021E39FC(PokedexInfoMenuSprites *param0, PokedexGraphicData **param1, int param2);
static void Pokedex_021E3AAC(PokedexInfoMenuSprites *param0, PokedexGraphicData **param1);
static void Pokedex_021E3AF0(PokedexInfoMenuSprites *param0, PokedexGraphicData **param1, int param2);
static void Pokedex_021E3BC0(PokedexInfoMenuSprites *param0);
static void Pokedex_021E3FE4(PokedexInfoMenuSprites *param0, const PokedexInfoMenuData *param1);
static void Pokedex_021E3BD8(PokedexInfoMenuSprites *param0, PokedexGraphicData **param1, int param2);
static void Pokedex_021E3BDC(PokedexInfoMenuSprites *param0);

void PokedexInfoMenu_Init(PokedexScreenManager *param0, PokedexApp *param1, enum HeapID heapID)
{
    PokedexInfoMenuState *v0;
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

void PokedexInfoMenu_Free(PokedexScreenManager *param0)
{
    FreeState(param0->pageData);
    FreeGraphics(param0->pageGraphics);
    FreeScreenStates(param0->screenStates);
}

BOOL PokedexInfoMenu_IsActive(const PokedexScreenManager *param0)
{
    const PokedexInfoMenuState *v0 = param0->pageData;
    return v0->unk_28;
}

static PokedexInfoMenuState *AllocState(enum HeapID heapID, PokedexApp *param1)
{
    PokedexInfoMenuState *v0;
    PokedexScreenManager *v1;

    v0 = Heap_Alloc(heapID, sizeof(PokedexInfoMenuState));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexInfoMenuState));

    v0->unk_00 = PokedexMain_GetTransitionRequest3(param1);
    v0->unk_04 = PokedexMain_GetSortData(param1);
    v0->unk_08 = 0;

    v1 = PokedexMain_GetScreenManager(param1, 2);
    v0->unk_10 = v1->pageData;

    v1 = PokedexMain_GetScreenManager(param1, 3);
    v0->unk_14 = v1;

    v1 = PokedexMain_GetScreenManager(param1, 4);
    v0->unk_18 = v1;

    v1 = PokedexMain_GetScreenManager(param1, 6);
    v0->unk_1C = v1;

    v1 = PokedexMain_GetScreenManager(param1, 7);
    v0->unk_20 = v1;

    v1 = PokedexMain_GetSubScreenManager(param1, 6);
    v0->unk_24 = v1;

    v1 = PokedexMain_GetScreenManager(param1, 0);
    v0->unk_0C = v1->pageData;

    v0->unk_2C = 1;
    v0->unk_30 = 1;

    return v0;
}

static PokedexGraphicData **AllocGraphics(enum HeapID heapID, PokedexApp *param1)
{
    PokedexGraphicData **v0;
    PokedexScreenManager *v1;

    v0 = Heap_Alloc(heapID, sizeof(PokedexGraphicData **));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexGraphicData **));

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

    Pokedex_021D47F0(heapID, &v0[0], param1, (0x1 << 1));
    Pokedex_021D4A94(heapID, &v0[1], param1, (0x1 << 2));
    Pokedex_021D48B8(heapID, &v0[2], param1, (0x1 << 3));
    Pokedex_021D491C(heapID, &v0[3], param1, (0x1 << 4));
    Pokedex_021D4980(heapID, &v0[4], param1, (0x1 << 5));
    Pokedex_021D49E4(heapID, &v0[5], param1, (0x1 << 6));
    Pokedex_021D4A3C(heapID, &v0[6], param1, (0x1 << 7));
    Pokedex_021D4B50(heapID, &v0[7], param1, (0x1 << 8));

    return v0;
}

static void FreeState(PokedexInfoMenuState *param0)
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
    PokedexScreenState_Free(&param0[1]);
    PokedexScreenState_Free(&param0[2]);
    PokedexScreenState_Free(&param0[3]);
    PokedexScreenState_Free(&param0[4]);
    PokedexScreenState_Free(&param0[5]);
    PokedexScreenState_Free(&param0[6]);
    PokedexScreenState_Free(&param0[7]);

    Heap_Free(param0);
}

static int GetNumScreenStates(void)
{
    return 8;
}

static int InitData(PokedexDataManager *dataMan, void *data)
{
    PokedexInfoMenuState *v0 = data;

    v0->unk_10->playCry = 1;

    return 1;
}

static int UpdateData(PokedexDataManager *dataMan, void *data)
{
    PokedexInfoMenuState *v0 = data;

    if (dataMan->exit == 1) {
        return 1;
    }

    if (dataMan->unchanged == 1) {
        return 0;
    }

    if (dataMan->state == 0) {
        Pokedex_021E3320(v0);
        dataMan->state++;
    }

    return 0;
}

static int ExitData(PokedexDataManager *dataMan, void *data)
{
    PokedexInfoMenuState *v0 = data;

    v0->unk_08 = 0;
    return 1;
}

static int InitGraphics(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan)
{
    const PokedexInfoMenuState *v0 = data;
    PokedexGraphicData **v2 = graphics;
    PokedexInfoMenuGraphics *v3 = graphicsMan->pageGraphics;
    BOOL v4;

    switch (graphicsMan->state) {
    case 0:
        graphicsMan->pageGraphics = Heap_Alloc(graphicsMan->heapID, sizeof(PokedexInfoMenuGraphics));
        memset(graphicsMan->pageGraphics, 0, sizeof(PokedexInfoMenuGraphics));
        v3 = graphicsMan->pageGraphics;
        v3->unk_00 = v0->unk_08;
        graphicsMan->state++;
        break;
    case 1:
        Pokedex_021E3080(v2, v3, v0, graphicsMan->heapID);
        Pokedex_021E3BE0(v3);
        PokedexGraphics_InitBlendTransition(&(*v2)->blendMain, 4, -16, 0, 0, 16, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BD), (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BD), 0);
        graphicsMan->state++;
        break;
    case 2:
        if (PokedexGraphics_TakeBlendTransitionStep(&(*v2)->blendMain)) {
            graphicsMan->state++;
        }
        break;
    case 3:
        Pokedex_021E3BFC(v3);
        return 1;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

static int UpdateGraphics(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan)
{
    const PokedexInfoMenuState *v0 = data;
    PokedexInfoMenuGraphics *v3 = graphicsMan->pageGraphics;

    if (v3->unk_00 != v0->unk_08) {
        Pokedex_021E331C(v3, v0->unk_08);
        Pokedex_021E3FC0(v3, v0->unk_08, v3->unk_00);
        v3->unk_00 = v0->unk_08;
    }

    return 0;
}

static int ExitGraphics(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan)
{
    const PokedexInfoMenuState *v0 = data;
    PokedexGraphicData **v2 = graphics;
    PokedexInfoMenuGraphics *v3 = graphicsMan->pageGraphics;

    switch (graphicsMan->state) {
    case 0:
        if (v0->unk_2C) {
            Pokedex_021E3BE0(v3);

            PokedexGraphics_InitBlendTransition(&(*v2)->blendMain, 4, 0, -16, 16, 0, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BD), (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BD), 0);
        } else {
            PokedexGraphics_InitBlendTransition(&(*v2)->blendMain, 4, 0, -16, 16, 0, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD), 0, 0);
        }
        graphicsMan->state++;
        break;
    case 1:
        if (PokedexGraphics_TakeBlendTransitionStep(&(*v2)->blendMain)) {
            graphicsMan->state++;
        }
        break;
    case 2:
        Pokedex_021E30BC(v2, v3);
        graphicsMan->state++;
        break;
    case 3:
        Heap_Free(graphicsMan->pageGraphics);
        graphicsMan->pageGraphics = NULL;
        graphicsMan->state++;
        break;
    case 4:
        return 1;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

static void Pokedex_021E2E00(PokedexInfoMenuState *param0)
{
    Pokedex_021E2E10(param0);
    param0->unk_30 = 1;
}

static void Pokedex_021E2E10(PokedexInfoMenuState *param0)
{
    *param0->unk_00 |= (0x1 << 1);
    param0->unk_28 = 0;
    param0->unk_10->animationMode = 0;

    InfoMainForeign_SetAnimationMode(param0->unk_18, ANIM_POSITION_BLEND);

    switch (param0->unk_08) {
    case 0:
        param0->unk_10->displayPositionX = 56;
        param0->unk_10->displayPositionY = 80;
        InfoMainForeign_SetDisplayPosition(param0->unk_18, 56, 80);
        param0->unk_0C->useBlendTransition = 1;
        param0->unk_2C = 1;
        break;
    case 1:
        PokedexAreaMap_SetTransitionType(param0->unk_1C, 1);
        PokedexAreaMap_SetTransitionSpeed(param0->unk_1C, 4);
        PokedexAreaMap_SetTransitionParams(param0->unk_1C, 56, 80);
        param0->unk_0C->useBlendTransition = 1;
        param0->unk_2C = 1;
        break;
    case 2:
        PokedexCryScreen_SetWaveParam2(param0->unk_20, 1);
        PokedexCryScreen_SetWaveParam3(param0->unk_20, 4);
        PokedexCryScreen_SetWaveParams(param0->unk_20, 56, 80);
        param0->unk_0C->useBlendTransition = 1;
        param0->unk_2C = 1;
        break;
    case 3:
        param0->unk_0C->useBlendTransition = 0;
        param0->unk_2C = 0;
        break;
    case 4:
        param0->unk_0C->useBlendTransition = 0;
        param0->unk_2C = 0;
        break;
    default:
        break;
    }
}

static BOOL Pokedex_021E2EC0(int param0)
{
    return 0;
}

static BOOL Pokedex_021E2EC4(PokedexInfoMenuState *param0, int param1, int param2)
{
    int v0, v1;
    BOOL v2 = 1;

    switch (param1) {
    case 0:
        if (Pokedex_021E2EC0(param2)) {
            param0->unk_10->animationMode = 2;
        } else {
            param0->unk_10->animationMode = 1;
        }

        *param0->unk_00 |= (0x1 << 2);
        param0->unk_08 = 0;
        v0 = 48;
        v1 = 72;
        break;
    case 1:
        if (Pokedex_021E2EC0(param2)) {
            PokedexAreaMap_SetTransitionType(param0->unk_1C, 1);
            PokedexAreaMap_SetTransitionSpeed(param0->unk_1C, 1);
        } else {
            PokedexAreaMap_SetTransitionType(param0->unk_1C, 0);
        }

        *param0->unk_00 |= (0x1 << 3);
        param0->unk_08 = 1;
        v0 = 40;
        v1 = 120;
        break;
    case 2:
        if (Pokedex_021E2EC0(param2)) {
            PokedexCryScreen_SetWaveParam2(param0->unk_20, 1);
            PokedexCryScreen_SetWaveParam3(param0->unk_20, 1);
        } else {
            PokedexCryScreen_SetWaveParam2(param0->unk_20, 0);
        }

        *param0->unk_00 |= (0x1 << 4);
        param0->unk_08 = 2;
        v0 = 48;
        v1 = 64;
        break;
    case 3:
        if (PokedexSort_CurrentCaughtStatus(param0->unk_04) == 2) {
            *param0->unk_00 |= (0x1 << 5);
            param0->unk_08 = 3;
        } else {
            v2 = 0;
        }
        break;
    case 4:
        if (PokedexSort_CanDetectForms(param0->unk_04) == 1) {
            *param0->unk_00 |= (0x1 << 8);
            param0->unk_08 = 4;
        } else {
            v2 = 0;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    switch (param2) {
    case 0:
        if (Pokedex_021E2EC0(param1)) {
            param0->unk_10->animationMode = 2;
            InfoMainForeign_SetAnimationMode(param0->unk_18, ANIM_POSITION);
        } else {
            param0->unk_10->animationMode = 1;
            InfoMainForeign_SetAnimationMode(param0->unk_18, ANIM_BLEND);
        }

        param0->unk_10->displayPositionX = v0;
        param0->unk_10->displayPositionY = v1;
        InfoMainForeign_SetDisplayPosition(param0->unk_18, v0, v1);
        break;
    case 1:
        if (Pokedex_021E2EC0(param1)) {
            PokedexAreaMap_SetTransitionType(param0->unk_1C, 1);
            PokedexAreaMap_SetTransitionSpeed(param0->unk_1C, 1);
        } else {
            PokedexAreaMap_SetTransitionType(param0->unk_1C, 0);
        }

        PokedexAreaMap_SetTransitionParams(param0->unk_1C, v0, v1);
        break;
    case 2:
        if (Pokedex_021E2EC0(param1)) {
            PokedexCryScreen_SetWaveParam2(param0->unk_20, 1);
            PokedexCryScreen_SetWaveParam3(param0->unk_20, 1);
        } else {
            PokedexCryScreen_SetWaveParam2(param0->unk_20, 0);
        }

        PokedexCryScreen_SetWaveParams(param0->unk_20, v0, v1);
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return v2;
}

static void Pokedex_021E3080(PokedexGraphicData **param0, PokedexInfoMenuGraphics *param1, const PokedexInfoMenuState *param2, enum HeapID heapID)
{
    Pokedex_021E30E4(param0, param2, heapID);
    Pokedex_021E3178(param0, param1, heapID);
    Pokedex_021E3268(param0, param1, heapID);
    Pokedex_021E3270(param0, param1, heapID);
    Pokedex_021E3FC0(param1, 0, 1);
}

static void Pokedex_021E30BC(PokedexGraphicData **param0, PokedexInfoMenuGraphics *param1)
{
    Pokedex_021E326C(param1);
    Pokedex_021E3224(param0, param1);
    Pokedex_021E3304(param1);

    Bg_ClearTilemap((*param0)->bgConfig, 2);
}

static void Pokedex_021E30E4(PokedexGraphicData **param0, const PokedexInfoMenuState *param1, enum HeapID heapID)
{
    void *v0;
    NNSG2dScreenData *v1;

    PokedexGraphics_LoadGraphicNarcPaletteData(*param0, banner_sinnoh_NCLR, 0, 0, 0, heapID);

    if (PokedexSort_IsNationalDex(param1->unk_04) == 1) {
        PokedexGraphics_LoadGraphicNarcPaletteData(*param0, banner_national_NCLR, 0, 0, 32, heapID);
    }

    PokedexGraphics_LoadGraphicNarcCharacterData(*param0, entry_main_NCGR_lz, (*param0)->bgConfig, 2, 0, 0, TRUE, heapID);

    v0 = PokedexGraphics_GetGraphicNarcTilemapData(*param0, banner_sinnoh_NSCR_lz, TRUE, &v1, heapID);

    Bg_LoadToTilemapRect((*param0)->bgConfig, 2, v1->rawData, 0, 0, v1->screenWidth / 8, v1->screenHeight / 8);
    Heap_Free(v0);
    Bg_ScheduleTilemapTransfer((*param0)->bgConfig, 2);
}

static void Pokedex_021E3178(PokedexGraphicData **param0, PokedexInfoMenuGraphics *param1, int param2)
{
    PokedexGraphicData *v0 = *param0;
    NARC *v1 = PokedexGraphics_GetNARC(*param0);

    param1->unk_18[0] = SpriteResourceCollection_AddTilesFrom(v0->spriteResourceCollection[0], v1, banner_NCGR_lz, TRUE, banner_NCGR_lz + 2000, NNS_G2D_VRAM_TYPE_2DMAIN, param2);

    SpriteTransfer_RequestCharAtEnd(param1->unk_18[0]);
    SpriteResource_ReleaseData(param1->unk_18[0]);

    param1->unk_18[1] = SpriteResourceCollection_AddPaletteFrom(v0->spriteResourceCollection[1], v1, banner_default_NCLR, FALSE, banner_default_NCLR + 2000, NNS_G2D_VRAM_TYPE_2DMAIN, 1, param2);

    SpriteTransfer_RequestPlttFreeSpace(param1->unk_18[1]);
    SpriteResource_ReleaseData(param1->unk_18[1]);

    param1->unk_18[2] = SpriteResourceCollection_AddFrom(v0->spriteResourceCollection[2], v1, banner_cell_NCER_lz, TRUE, banner_cell_NCER_lz + 2000, 2, param2);
    param1->unk_18[3] = SpriteResourceCollection_AddFrom(v0->spriteResourceCollection[3], v1, banner_anim_NANR_lz, TRUE, banner_anim_NANR_lz + 2000, 3, param2);
}

static void Pokedex_021E3224(PokedexGraphicData **param0, PokedexInfoMenuGraphics *param1)
{
    PokedexGraphicData *v0 = *param0;

    SpriteTransfer_ResetCharTransfer(param1->unk_18[0]);
    SpriteTransfer_ResetPlttTransfer(param1->unk_18[1]);

    SpriteResourceCollection_Remove(v0->spriteResourceCollection[0], param1->unk_18[0]);
    SpriteResourceCollection_Remove(v0->spriteResourceCollection[1], param1->unk_18[1]);
    SpriteResourceCollection_Remove(v0->spriteResourceCollection[2], param1->unk_18[2]);
    SpriteResourceCollection_Remove(v0->spriteResourceCollection[3], param1->unk_18[3]);
}

static void Pokedex_021E3268(PokedexGraphicData **param0, PokedexInfoMenuGraphics *param1, int param2)
{
    return;
}

static void Pokedex_021E326C(PokedexInfoMenuGraphics *param0)
{
    return;
}

static void Pokedex_021E3270(PokedexGraphicData **param0, PokedexInfoMenuGraphics *param1, int param2)
{
    Window *v0;
    PokedexDisplayBox displayBox;
    PokedexGraphicData *v2 = *param0;
    int v3;
    int v4;

    displayBox.textMan = v2->textMan;
    displayBox.paletteProxy = SpriteTransfer_GetPaletteProxy(param1->unk_18[1], NULL);
    displayBox.x = 16;
    displayBox.y = 0;
    displayBox.spriteResourcePriority = 0;
    displayBox.spriteListPriority = 0;
    displayBox.sprite = NULL;
    displayBox.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    displayBox.heapID = param2;

    v3 = PlttTransfer_GetPlttOffset(displayBox.paletteProxy, NNS_G2D_VRAM_TYPE_2DMAIN);

    for (v4 = 0; v4 < 5; v4++) {
        v0 = PokedexTextManager_NewWindow(v2->textMan, 8, 2);

        PokedexTextManager_DisplayMessage(v2->textMan, v0, TEXT_BANK_POKEDEX, pl_msg_pokedex_info + v4, 0, 0);

        displayBox.window = v0;
        param1->unk_04[v4] = PokedexTextManager_NextTextData(&displayBox);

        FontOAM_SetExplicitPalette(param1->unk_04[v4]->fontOAM, v3);
        FontOAM_SetDrawFlag(param1->unk_04[v4]->fontOAM, 0);

        PokedexTextManager_FreeWindow(v0);
    }
}

static void Pokedex_021E3304(PokedexInfoMenuGraphics *param0)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        PokedexTextManager_FreeTextData(param0->unk_04[v0]);
    }
}

static void Pokedex_021E331C(PokedexInfoMenuGraphics *param0, int param1)
{
    return;
}

static void Pokedex_021E3320(PokedexInfoMenuState *param0)
{
    param0->unk_28 = 1;
    param0->unk_10->animationMode = 1;
}

void PokedexInfoMenu_InitSub(PokedexScreenManager *screenMan, PokedexApp *param1, enum HeapID heapID)
{
    PokedexInfoMenuData *v0;
    PokedexGraphicData **v1;
    PokedexScreenState *v2;

    v0 = Pokedex_021E33C4(heapID, param1);
    v1 = Pokedex_021E3400(heapID, param1);
    v2 = Pokedex_021E3428(heapID, param1);

    screenMan->pageData = v0;
    screenMan->pageGraphics = v1;
    screenMan->screenStates = v2;
    screenMan->numStates = Pokedex_021E3458();

    screenMan->dataFunc[0] = Pokedex_021E345C;
    screenMan->dataFunc[1] = Pokedex_021E34AC;
    screenMan->dataFunc[2] = Pokedex_021E3520;
    screenMan->graphicsFunc[0] = Pokedex_021E3540;
    screenMan->graphicsFunc[1] = Pokedex_021E35D0;
    screenMan->graphicsFunc[2] = Pokedex_021E3604;
}

void PokedexInfoMenu_FreeSub(PokedexScreenManager *screenMan)
{
    Pokedex_021E342C(screenMan->pageData);
    Pokedex_021E3440(screenMan->pageGraphics);
    Pokedex_021E3454(screenMan->screenStates);
}

BOOL PokedexInfoMenu_IsSubActive1(const PokedexScreenManager *screenMan)
{
    const PokedexInfoMenuData *v0 = screenMan->pageData;
    return v0->unk_24;
}

BOOL PokedexInfoMenu_IsSubActive2(const PokedexScreenManager *screenMan)
{
    const PokedexInfoMenuData *v0 = screenMan->pageData;
    return v0->unk_28;
}

void PokedexInfoMenu_SetSubActive(PokedexScreenManager *screenMan, BOOL param1)
{
    PokedexInfoMenuData *v0 = screenMan->pageData;
    v0->unk_30 = param1;
}

BOOL PokedexInfoMenu_IsSubActive3(const PokedexScreenManager *screenMan)
{
    const PokedexInfoMenuData *v0 = screenMan->pageData;
    return v0->unk_30;
}

static PokedexInfoMenuData *Pokedex_021E33C4(enum HeapID heapID, PokedexApp *param1)
{
    PokedexInfoMenuData *v0;
    PokedexScreenManager *v1;

    v0 = Heap_Alloc(heapID, sizeof(PokedexInfoMenuData));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexInfoMenuData));

    v0->unk_00 = PokedexMain_GetTransitionRequest4(param1);
    v1 = PokedexMain_GetScreenManager(param1, 5);
    v0->unk_04 = v1->pageData;
    v0->unk_08 = PokedexMain_GetSortData(param1);

    return v0;
}

static PokedexGraphicData **Pokedex_021E3400(enum HeapID heapID, PokedexApp *param1)
{
    PokedexGraphicData **v0;
    PokedexScreenManager *v1;

    v0 = Heap_Alloc(heapID, sizeof(PokedexGraphicData **));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexGraphicData **));

    *v0 = PokedexMain_GetGraphicData(param1);

    return v0;
}

static PokedexScreenState *Pokedex_021E3428(enum HeapID heapID, PokedexApp *param1)
{
    return NULL;
}

static void Pokedex_021E342C(PokedexInfoMenuData *param0)
{
    GF_ASSERT(param0);
    Heap_Free(param0);
}

static void Pokedex_021E3440(PokedexGraphicData **param0)
{
    GF_ASSERT(param0);
    Heap_Free(param0);
}

static void Pokedex_021E3454(PokedexScreenState *param0)
{
    return;
}

static int Pokedex_021E3458(void)
{
    return 0;
}

static int Pokedex_021E345C(PokedexDataManager *dataMan, void *data)
{
    PokedexInfoMenuData *v0 = data;
    PokedexInfoMenuPanelData *v1 = dataMan->pageData;
    int v2;

    v1 = Heap_Alloc(dataMan->heapID, sizeof(PokedexInfoMenuPanelData));
    memset(v1, 0, sizeof(PokedexInfoMenuPanelData));

    Pokedex_021E3688(v1, v0, dataMan->heapID);
    Pokedex_021E3C6C(v1, v0, dataMan->heapID);
    Pokedex_021E3E8C(v1, v0);

    for (v2 = 0; v2 < 6; v2++) {
        v0->unk_0C[v2] = (3 + 1);
    }

    dataMan->pageData = v1;

    return 1;
}

static int Pokedex_021E34AC(PokedexDataManager *dataMan, void *data)
{
    PokedexInfoMenuData *v0 = data;
    PokedexInfoMenuPanelData *v1 = dataMan->pageData;

    if (dataMan->exit == 1) {
        v0->unk_24 = 0;
        return 1;
    }

    if (dataMan->unchanged == 1) {
        return 0;
    }

    if (dataMan->state == 0) {
        v0->unk_24 = 1;
        v0->unk_04->unk_30 = 0;
        v0->unk_28 = 1;
        dataMan->state++;
    } else {
        v0->unk_28 = 1;

        Pokedex_021E3C2C(v0);
        Pokedex_021E3EEC(v1, v0);
        Pokedex_021E3724(v0);

        if ((PokedexSort_GetInputState(v0->unk_08) == 2) && (v0->unk_30 == 0)) {
            Pokedex_021E3D48(v1, v0);
        }

        Pokedex_021E3734(v1, v0);
    }

    return 0;
}

static int Pokedex_021E3520(PokedexDataManager *dataMan, void *data)
{
    PokedexInfoMenuPanelData *v1 = dataMan->pageData;

    Pokedex_021E37B4(v1);
    Pokedex_021E3E74(v1);

    Heap_Free(dataMan->pageData);
    dataMan->pageData = NULL;

    return 1;
}

static int Pokedex_021E3540(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan)
{
    const PokedexInfoMenuData *v0 = data;
    const PokedexInfoMenuPanelData *v1 = dataMan->pageData;
    PokedexGraphicData **v2 = graphics;
    PokedexInfoMenuSprites *v3 = graphicsMan->pageGraphics;

    switch (graphicsMan->state) {
    case 0:
        graphicsMan->pageGraphics = Heap_Alloc(graphicsMan->heapID, sizeof(PokedexInfoMenuSprites));
        memset(graphicsMan->pageGraphics, 0, sizeof(PokedexInfoMenuSprites));
        graphicsMan->state++;
        break;
    case 1:
        Pokedex_021E3900(v3, v2, v0, graphicsMan->heapID);
        graphicsMan->state++;
        break;
    case 2:
        BrightnessController_StartTransition(4, 0, -16, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD), BRIGHTNESS_SUB_SCREEN);
        Pokedex_021E3F2C(v2, v1, v0);
        graphicsMan->state++;
        break;
    case 3:
        if (BrightnessController_IsTransitionComplete(BRIGHTNESS_SUB_SCREEN)) {
            graphicsMan->state++;
        }
        break;
    case 4:
        return 1;
    default:
        break;
    }

    return 0;
}

static int Pokedex_021E35D0(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan)
{
    const PokedexInfoMenuData *v0 = data;
    const PokedexInfoMenuPanelData *v1 = dataMan->pageData;
    PokedexGraphicData **v2 = graphics;
    PokedexInfoMenuSprites *v3 = graphicsMan->pageGraphics;
    int v4;

    for (v4 = 0; v4 < 6; v4++) {
        PokedexMain_SetCursorAnimFrame(v3->unk_00[v4], v0->unk_0C[v4]);
    }

    Pokedex_021E3F48(v2, v1, v0);

    return 0;
}

static int Pokedex_021E3604(void *graphics, PokedexGraphicsManager *graphicsMan, const void *data, const PokedexDataManager *dataMan)
{
    const PokedexInfoMenuData *v0 = data;
    const PokedexInfoMenuPanelData *v1 = dataMan->pageData;
    PokedexGraphicData **v2 = graphics;
    PokedexInfoMenuSprites *v3 = graphicsMan->pageGraphics;

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
        Pokedex_021E393C(v3, v2);
        PokedexGraphics_SetDrawCursor(&(*v2)->cursorGraphics, 0);
        graphicsMan->state++;
        break;
    case 3:
        Heap_Free(graphicsMan->pageGraphics);
        graphicsMan->pageGraphics = NULL;
        graphicsMan->state++;
        break;
    case 4:
        return 1;
    default:
        break;
    }

    return 0;
}

static void Pokedex_021E3688(PokedexInfoMenuPanelData *param0, PokedexInfoMenuData *param1, enum HeapID heapID)
{
    param0->unk_04 = Heap_Alloc(heapID, sizeof(TouchScreenHitTable) * 6);

    PokedexMain_SetHitTableRect(&param0->unk_04[0], 24 - (32 / 2), 24 + (32 / 2), 28 - (40 / 2), 28 + (40 / 2));
    PokedexMain_SetHitTableRect(&param0->unk_04[5], 24 - (32 / 2), 24 + (32 / 2), 228 - (40 / 2), 228 + (40 / 2));
    PokedexMain_SetHitTableRect(&param0->unk_04[1], 24 - (32 / 2), 24 + (32 / 2), 68 - (40 / 2), 68 + (40 / 2));
    PokedexMain_SetHitTableRect(&param0->unk_04[2], 24 - (32 / 2), 24 + (32 / 2), 108 - (40 / 2), 108 + (40 / 2));
    PokedexMain_SetHitTableRect(&param0->unk_04[3], 24 - (32 / 2), 24 + (32 / 2), 148 - (40 / 2), 148 + (40 / 2));
    PokedexMain_SetHitTableRect(&param0->unk_04[4], 24 - (32 / 2), 24 + (32 / 2), 188 - (40 / 2), 188 + (40 / 2));

    param0->unk_08.unk_00 = param1;
    param0->unk_08.unk_04 = param0;
    param0->unk_00 = TouchScreenActions_RegisterHandler(param0->unk_04, 6, Pokedex_021E37CC, &param0->unk_08, heapID);
}

static void Pokedex_021E3724(PokedexInfoMenuData *param0)
{
    int v0;

    for (v0 = 0; v0 < 6; v0++) {
        param0->unk_0C[v0] = 3;
    }
}

static void Pokedex_021E3734(PokedexInfoMenuPanelData *param0, PokedexInfoMenuData *param1)
{
    if (param1->unk_2C == 0) {
        TouchScreenActions_HandleAction(param0->unk_00);
    }

    if (param1->unk_2C) {
        if (param1->unk_0C[5] != 2) {
            param1->unk_0C[5] = 1;
        }
    }

    switch (param1->unk_04->unk_08) {
    case 0:
        if (param1->unk_0C[0] != 2) {
            param1->unk_0C[0] = 1;
        }
        break;
    case 1:
        if (param1->unk_0C[1] != 2) {
            param1->unk_0C[1] = 1;
        }
        break;
    case 2:
        if (param1->unk_0C[2] != 2) {
            param1->unk_0C[2] = 1;
        }
        break;
    case 3:
        if (param1->unk_0C[3] != 2) {
            param1->unk_0C[3] = 1;
        }
        break;
    case 4:
        if (param1->unk_0C[4] != 2) {
            param1->unk_0C[4] = 1;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

static void Pokedex_021E37B4(PokedexInfoMenuPanelData *param0)
{
    TouchScreenActions_Free(param0->unk_00);
    Heap_Free(param0->unk_04);
    param0->unk_04 = NULL;
}

static void Pokedex_021E37CC(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    PokedexInfoMenuTouchHandler *v0 = param2;
    PokedexInfoMenuData *v1 = v0->unk_00;
    PokedexInfoMenuPanelData *v2 = v0->unk_04;
    PokedexInfoMenuState *v3 = v1->unk_04;

    v1->unk_0C[param0] = param1;

    switch (param1) {
    case TOUCH_BUTTON_PRESSED:
        v2->unk_10 = 0;
        break;
    case TOUCH_BUTTON_HELD:
        PokedexPanel_Move(v2->unk_14, 2, param0);

        switch (param0) {
        case 5:
            Pokedex_021E2E00(v3);
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
            break;
        case 0:
            if (v3->unk_08 != 0) {
                Pokedex_021E3C18(v1, 0, v3->unk_08);
                Pokedex_021E3E8C(v2, v1);
                Sound_PlayEffect(SEQ_SE_DP_DENSI06_sseq);
            }
            break;
        case 1:
            if (v3->unk_08 != 1) {
                Pokedex_021E3C18(v1, 1, v3->unk_08);
                Pokedex_021E3E8C(v2, v1);
                Sound_PlayEffect(SEQ_SE_DP_DENSI06_sseq);
            }
            break;
        case 2:
            if (v3->unk_08 != 2) {
                Pokedex_021E3C18(v1, 2, v3->unk_08);
                Pokedex_021E3E8C(v2, v1);
                Sound_PlayEffect(SEQ_SE_DP_DENSI06_sseq);
            }
            break;
        case 3:
            if (v3->unk_08 != 3) {
                if (Pokedex_021E3C18(v1, 3, v3->unk_08)) {
                    Pokedex_021E3E8C(v2, v1);
                    Sound_PlayEffect(SEQ_SE_DP_DENSI06_sseq);
                } else {
                    if (v2->unk_10 == 0) {
                        if (v3->unk_08 != 2) {
                            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
                        }

                        v2->unk_10 = 1;
                    }
                }
            }
            break;
        case 4:
            if (v3->unk_08 != 4) {
                if (Pokedex_021E3C18(v1, 4, v3->unk_08)) {
                    Pokedex_021E3E8C(v2, v1);
                    Sound_PlayEffect(SEQ_SE_DP_DENSI06_sseq);
                } else {
                    if (v2->unk_10 == 0) {
                        if (PokedexSort_CanDetectForms(v3->unk_04) == 1) {
                            if (v3->unk_08 != 2) {
                                Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
                            }
                        }

                        v2->unk_10 = 0;
                    }
                }
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

static void Pokedex_021E3900(PokedexInfoMenuSprites *param0, PokedexGraphicData **param1, const PokedexInfoMenuData *param2, enum HeapID heapID)
{
    Pokedex_021E3960(param1, param2, heapID);
    Pokedex_021E39FC(param0, param1, heapID);
    Pokedex_021E3AF0(param0, param1, heapID);
    Pokedex_021E3BD8(param0, param1, heapID);
    Pokedex_021E3FE4(param0, param2);
}

static void Pokedex_021E393C(PokedexInfoMenuSprites *param0, PokedexGraphicData **param1)
{
    Pokedex_021E3BDC(param0);
    Pokedex_021E3BC0(param0);
    Pokedex_021E3AAC(param0, param1);
    Bg_ClearTilemap((*param1)->bgConfig, 5);
}

static void Pokedex_021E3960(PokedexGraphicData **param0, const PokedexInfoMenuData *param1, enum HeapID heapID)
{
    void *v0;
    NNSG2dScreenData *v1;

    if (param1->unk_04->unk_30) {
        PokedexGraphics_LoadGraphicNarcPaletteData(*param0, banner_sinnoh_NCLR, 4, 0, 0, heapID);

        if (PokedexSort_IsNationalDex(param1->unk_08) == 1) {
            PokedexGraphics_LoadGraphicNarcPaletteData(*param0, banner_national_NCLR, 4, 0, 32, heapID);
        }
    }

    PokedexGraphics_LoadGraphicNarcCharacterData(*param0, entry_sub_NCGR_lz, (*param0)->bgConfig, 5, 0, 0, TRUE, heapID);

    v0 = PokedexGraphics_GetGraphicNarcTilemapData(*param0, page_panel_NSCR_lz, TRUE, &v1, heapID);

    Bg_LoadToTilemapRect((*param0)->bgConfig, 5, v1->rawData, 0, 0, v1->screenWidth / 8, v1->screenHeight / 8);
    Heap_Free(v0);
    Bg_ScheduleTilemapTransfer((*param0)->bgConfig, 5);
}

static void Pokedex_021E39FC(PokedexInfoMenuSprites *param0, PokedexGraphicData **param1, int param2)
{
    PokedexGraphicData *v0 = *param1;
    NARC *v1 = PokedexGraphics_GetNARC(*param1);

    param0->unk_18[0] = SpriteResourceCollection_AddTilesFrom(v0->spriteResourceCollection[0], v1, page_buttons_NCGR_lz, TRUE, page_buttons_NCGR_lz + 2100, NNS_G2D_VRAM_TYPE_2DSUB, param2);

    SpriteTransfer_RequestCharAtEnd(param0->unk_18[0]);
    SpriteResource_ReleaseData(param0->unk_18[0]);

    param0->unk_18[1] = SpriteResourceCollection_AddPaletteFrom(v0->spriteResourceCollection[1], v1, info_NCLR, FALSE, info_NCLR + 2100, NNS_G2D_VRAM_TYPE_2DSUB, 6, param2);

    SpriteTransfer_RequestPlttFreeSpace(param0->unk_18[1]);
    SpriteResource_ReleaseData(param0->unk_18[1]);

    param0->unk_18[2] = SpriteResourceCollection_AddFrom(v0->spriteResourceCollection[2], v1, page_buttons_cell_NCER_lz, TRUE, page_buttons_cell_NCER_lz + 2100, 2, param2);
    param0->unk_18[3] = SpriteResourceCollection_AddFrom(v0->spriteResourceCollection[3], v1, page_buttons_anim_NANR_lz, TRUE, page_buttons_anim_NANR_lz + 2100, 3, param2);
}

static void Pokedex_021E3AAC(PokedexInfoMenuSprites *param0, PokedexGraphicData **param1)
{
    PokedexGraphicData *v0 = *param1;

    SpriteTransfer_ResetCharTransfer(param0->unk_18[0]);
    SpriteTransfer_ResetPlttTransfer(param0->unk_18[1]);

    SpriteResourceCollection_Remove(v0->spriteResourceCollection[0], param0->unk_18[0]);
    SpriteResourceCollection_Remove(v0->spriteResourceCollection[1], param0->unk_18[1]);
    SpriteResourceCollection_Remove(v0->spriteResourceCollection[2], param0->unk_18[2]);
    SpriteResourceCollection_Remove(v0->spriteResourceCollection[3], param0->unk_18[3]);
}

static void Pokedex_021E3AF0(PokedexInfoMenuSprites *param0, PokedexGraphicData **param1, int param2)
{
    SpriteResourcesHeader v0;
    SpriteListTemplate v1;
    PokedexGraphicData *v2 = *param1;
    int v3;

    SpriteResourcesHeader_Init(&v0, page_buttons_NCGR_lz + 2100, info_NCLR + 2100, page_buttons_cell_NCER_lz + 2100, page_buttons_anim_NANR_lz + 2100, 0xffffffff, 0xffffffff, FALSE, 0, v2->spriteResourceCollection[0], v2->spriteResourceCollection[1], v2->spriteResourceCollection[2], v2->spriteResourceCollection[3], NULL, NULL);

    v1.list = v2->spriteList;
    v1.resourceData = &v0;
    v1.priority = 32;
    v1.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    v1.heapID = param2;
    v1.position.y = (24 * FX32_ONE) + (192 << FX32_SHIFT);

    for (v3 = 0; v3 < 6; v3++) {
        switch (v3) {
        case 5:
            v1.position.x = 228 * FX32_ONE;
            break;
        case 0:
            v1.position.x = 28 * FX32_ONE;
            break;
        case 1:
            v1.position.x = 68 * FX32_ONE;
            break;
        case 2:
            v1.position.x = 108 * FX32_ONE;
            break;
        case 3:
            v1.position.x = 148 * FX32_ONE;
            break;
        case 4:
            v1.position.x = 188 * FX32_ONE;
            break;
        }

        param0->unk_00[v3] = SpriteList_Add(&v1);
        Sprite_SetAnim(param0->unk_00[v3], v3);
    }
}

static void Pokedex_021E3BC0(PokedexInfoMenuSprites *param0)
{
    int v0;

    for (v0 = 0; v0 < 6; v0++) {
        Sprite_Delete(param0->unk_00[v0]);
    }
}

static void Pokedex_021E3BD8(PokedexInfoMenuSprites *param0, PokedexGraphicData **param1, int param2)
{
    return;
}

static void Pokedex_021E3BDC(PokedexInfoMenuSprites *param0)
{
    return;
}

static void Pokedex_021E3BE0(PokedexInfoMenuGraphics *param0)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        FontOAM_SetExplicitOAMMode(param0->unk_04[v0]->fontOAM, GX_OAM_MODE_XLU);
    }
}

static void Pokedex_021E3BFC(PokedexInfoMenuGraphics *param0)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        FontOAM_SetExplicitOAMMode(param0->unk_04[v0]->fontOAM, GX_OAM_MODE_NORMAL);
    }
}

static BOOL Pokedex_021E3C18(PokedexInfoMenuData *param0, int param1, int param2)
{
    PokedexInfoMenuState *v0 = param0->unk_04;
    BOOL v1 = Pokedex_021E2EC4(v0, param1, param2);

    if (v1 == 1) {
        param0->unk_28 = 0;
    }

    return v1;
}

static void Pokedex_021E3C2C(PokedexInfoMenuData *param0)
{
    PokedexInfoMenuState *v0 = param0->unk_04;
    Pokedex_021E3C34(param0);
}

static void Pokedex_021E3C34(PokedexInfoMenuData *param0)
{
    PokedexInfoMenuState *v0 = param0->unk_04;
    int v1;
    int v2;

    Pokedex_021E3C64(param0);

    if (gSystem.pressedKeys & PAD_BUTTON_B) {
        Pokedex_021E2E00(v0);
        param0->unk_2C = 1;
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        return;
    }
}

static void Pokedex_021E3C64(PokedexInfoMenuData *param0)
{
    param0->unk_2C = 0;
}

static void Pokedex_021E3C6C(PokedexInfoMenuPanelData *param0, PokedexInfoMenuData *param1, enum HeapID heapID)
{
    int v0;

    param0->unk_18 = Heap_Alloc(heapID, sizeof(PokedexCursorData) * 6);

    PokedexPanel_InitCursorData(&param0->unk_18[0], 28, 24, 24, 16, 0, 0, 0);
    PokedexPanel_InitCursorData(&param0->unk_18[1], 68, 24, 24, 16, 0, 0, 1);
    PokedexPanel_InitCursorData(&param0->unk_18[2], 108, 24, 24, 16, 0, 0, 2);
    PokedexPanel_InitCursorData(&param0->unk_18[3], 148, 24, 24, 16, 0, 0, 3);

    if (PokedexSort_CanDetectForms(param1->unk_08) == 1) {
        v0 = 0;
    } else {
        v0 = 2;
    }

    PokedexPanel_InitCursorData(&param0->unk_18[4], 188, 24, 24, 16, v0, v0, 4);
    PokedexPanel_InitCursorData(&param0->unk_18[5], 228, 24, 24, 16, 0, 0, 5);

    param0->unk_14 = PokedexPanel_Alloc(heapID);
    PokedexPanel_New(param0->unk_14, param0->unk_18, 6, 1);
}

static void Pokedex_021E3D48(PokedexInfoMenuPanelData *param0, PokedexInfoMenuData *param1)
{
    PokedexInfoMenuState *v0 = param1->unk_04;

    if (param1->unk_2C) {
        return;
    }

    if (gSystem.pressedKeys & PAD_KEY_RIGHT) {
        PokedexPanel_Move(param0->unk_14, 0, 1);
    }

    if (gSystem.pressedKeys & PAD_KEY_LEFT) {
        PokedexPanel_Move(param0->unk_14, 0, -1);
    }

    if (gSystem.pressedKeys & PAD_BUTTON_A) {
        switch (PokedexPanel_GetCurrentButton(param0->unk_14)) {
        case 0:
            if (v0->unk_08 != 0) {
                Pokedex_021E3C18(param1, 0, v0->unk_08);
                param1->unk_0C[0] = 2;
                Sound_PlayEffect(SEQ_SE_DP_DENSI06_sseq);
            }
            break;
        case 1:
            if (v0->unk_08 != 1) {
                Pokedex_021E3C18(param1, 1, v0->unk_08);
                param1->unk_0C[1] = 2;
                Sound_PlayEffect(SEQ_SE_DP_DENSI06_sseq);
            }
            break;
        case 2:
            if (v0->unk_08 != 2) {
                Pokedex_021E3C18(param1, 2, v0->unk_08);
                param1->unk_0C[2] = 2;
                Sound_PlayEffect(SEQ_SE_DP_DENSI06_sseq);
            }
            break;
        case 3:
            if (v0->unk_08 != 3) {
                if (Pokedex_021E3C18(param1, 3, v0->unk_08)) {
                    param1->unk_0C[3] = 2;
                    Sound_PlayEffect(SEQ_SE_DP_DENSI06_sseq);
                } else {
                    if (v0->unk_08 != 2) {
                        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
                    }
                }
            }
            break;
        case 4:
            if (v0->unk_08 != 4) {
                if (Pokedex_021E3C18(param1, 4, v0->unk_08)) {
                    param1->unk_0C[4] = 2;
                    Sound_PlayEffect(SEQ_SE_DP_DENSI06_sseq);
                } else {
                    if (v0->unk_08 != 2) {
                        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
                    }
                }
            }
            break;
        case 5:
            Pokedex_021E2E00(v0);
            param1->unk_2C = 1;
            param1->unk_0C[5] = 2;
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
            break;
        }
    }
}

static void Pokedex_021E3E74(PokedexInfoMenuPanelData *param0)
{
    Heap_Free(param0->unk_18);
    PokedexPanel_Free(param0->unk_14);
    param0->unk_14 = NULL;
    param0->unk_18 = NULL;
}

static void Pokedex_021E3E8C(PokedexInfoMenuPanelData *param0, PokedexInfoMenuData *param1)
{
    PokedexInfoMenuState *v0 = param1->unk_04;

    param1->unk_30 = 0;

    switch (v0->unk_08) {
    case 0:
        PokedexPanel_Move(param0->unk_14, 4, 0);
        break;
    case 1:
        PokedexPanel_Move(param0->unk_14, 4, 1);
        break;
    case 2:
        PokedexPanel_Move(param0->unk_14, 4, 2);
        break;
    case 3:
        PokedexPanel_Move(param0->unk_14, 4, 3);
        break;
    case 4:
        PokedexPanel_Move(param0->unk_14, 4, 4);
        break;
    default:
        break;
    }
}

static void Pokedex_021E3EEC(PokedexInfoMenuPanelData *param0, PokedexInfoMenuData *param1)
{
    PokedexInfoMenuState *v0 = param1->unk_04;

    if (v0->unk_08 == 0) {
        return;
    }

    if (PokedexSort_GetInputState(param1->unk_08) != 2) {
        return;
    }

    if (param1->unk_30 == 0) {
        if (gSystem.pressedKeys & PAD_KEY_DOWN) {
            param1->unk_30 = 1;
        }
    } else {
        if (gSystem.pressedKeys & PAD_KEY_UP) {
            param1->unk_30 = 0;
        }
    }
}

static void Pokedex_021E3F2C(PokedexGraphicData **param0, const PokedexInfoMenuPanelData *param1, const PokedexInfoMenuData *param2)
{
    PokedexGraphics_GoToCurrentButton(param1->unk_14, *param0);
    Pokedex_021E3F48(param0, param1, param2);
}

static void Pokedex_021E3F48(PokedexGraphicData **param0, const PokedexInfoMenuPanelData *param1, const PokedexInfoMenuData *param2)
{
    BOOL v0;

    if (PokedexSort_GetInputState(param2->unk_08) != 0) {
        v0 = Pokedex_021E3F98(param0, 1);

        if (param2->unk_30 == 0) {
            if (v0) {
                PokedexGraphics_GoToCurrentButton(param1->unk_14, *param0);
            }

            Pokedex_021E3F88(param0, param1);
        }
    } else {
        Pokedex_021E3F98(param0, 0);
    }
}

static void Pokedex_021E3F88(PokedexGraphicData **param0, const PokedexInfoMenuPanelData *param1)
{
    PokedexGraphicData *v0 = *param0;
    PokedexGraphics_CurrentButtonTransformation(param1->unk_14, v0);
}

static BOOL Pokedex_021E3F98(PokedexGraphicData **param0, BOOL param1)
{
    PokedexGraphicData *v0 = *param0;

    if (PokedexGraphics_GetDrawCursor(&v0->cursorGraphics) != param1) {
        PokedexGraphics_SetDrawCursor(&v0->cursorGraphics, param1);
        return 1;
    }

    return 0;
}

static void Pokedex_021E3FC0(PokedexInfoMenuGraphics *param0, int param1, int param2)
{
    FontOAM_SetDrawFlag(param0->unk_04[param2]->fontOAM, 0);
    FontOAM_SetDrawFlag(param0->unk_04[param1]->fontOAM, 1);
}

static void Pokedex_021E3FE4(PokedexInfoMenuSprites *param0, const PokedexInfoMenuData *param1)
{
    if (PokedexSort_CanDetectForms(param1->unk_08) == 0) {
        Sprite_SetDrawFlag(param0->unk_00[4], FALSE);
    }
}
