#include "applications/pokedex/pokedex_screen_transition.h"

#include <nitro.h>
#include <string.h>

#include "constants/heap.h"

#include "applications/pokedex/pokedex_screen_state_set.h"
#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/pokedex_main.h"
#include "applications/pokedex/pokedex_updater.h"
#include "applications/pokedex/struct_pokedex_screen_state_set_decl.h"
#include "applications/pokedex/struct_pokedex_transition_single.h"
#include "applications/pokedex/struct_pokedex_screen_state_data.h"
#include "applications/pokedex/struct_pokedex_transition_quad.h"
#include "applications/pokedex/struct_pokedex_transition_quad_screens.h"
#include "applications/pokedex/struct_pokedex_transition_dual.h"
#include "applications/pokedex/struct_pokedex_screen_state.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "heap.h"

static void PopulateUpdater(PokedexScreenManager *param0, PokedexScreenStateSet *param1, PokedexUpdater *param2);

BOOL PokedexTransitionSingle_Step(PokedexScreenStateData *param0)
{
    PokedexTransitionSingle *v0 = param0->unk_08;

    switch (param0->unk_00) {
    case 0:
        PokedexUpdater_DataExit(v0->unk_04);
        param0->unk_00++;
        break;
    case 1:
        if (PokedexUpdater_IsPageExited(v0->unk_04) == 1) {
            param0->unk_00++;
        }
        break;
    case 2:
        PopulateUpdater(v0->unk_00, v0->unk_08, v0->unk_04);
        param0->unk_00++;
        break;
    case 3:
        if (PokedexUpdater_IsPageDataActive(v0->unk_04) == 1) {
            return 1;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

BOOL PokedexTransitionQuad_Step(PokedexScreenStateData *param0)
{
    PokedexTransitionQuad *v0 = param0->unk_08;
    BOOL v1[4];
    int v2;

    switch (param0->unk_00) {
    case 0:
        PokedexUpdater_DataExit(v0->unk_00);
        PokedexUpdater_DataExit(v0->unk_04);
        PokedexUpdater_DataExit(v0->unk_08);
        PokedexUpdater_DataExit(v0->unk_0C);
        param0->unk_00++;
        break;
    case 1:
        v1[0] = PokedexUpdater_IsPageExited(v0->unk_00);
        v1[1] = PokedexUpdater_IsPageExited(v0->unk_04);
        v1[2] = PokedexUpdater_IsPageExited(v0->unk_08);
        v1[3] = PokedexUpdater_IsPageExited(v0->unk_0C);

        for (v2 = 0; v2 < 4; v2++) {
            if (v1[v2] == 0) {
                break;
            }
        }

        if (v2 >= 4) {
            param0->unk_00++;
        }
        break;
    case 2:
        *v0->unk_10 = 1;
        return 1;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

BOOL PokedexTransitionQuadScreens_Step(PokedexScreenStateData *param0)
{
    PokedexTransitionQuadScreens *v0 = param0->unk_08;
    BOOL v1[4];
    int v2;

    switch (param0->unk_00) {
    case 0:
        PokedexUpdater_DataExit(v0->unk_00);
        PokedexUpdater_DataExit(v0->unk_04);
        PokedexUpdater_DataExit(v0->unk_08);
        PokedexUpdater_DataExit(v0->unk_0C);
        param0->unk_00++;
        break;
    case 1:
        v1[0] = PokedexUpdater_IsPageExited(v0->unk_00);
        v1[1] = PokedexUpdater_IsPageExited(v0->unk_04);
        v1[2] = PokedexUpdater_IsPageExited(v0->unk_08);
        v1[3] = PokedexUpdater_IsPageExited(v0->unk_0C);

        for (v2 = 0; v2 < 4; v2++) {
            if (v1[v2] == 0) {
                break;
            }
        }

        if (v2 >= 4) {
            param0->unk_00++;
        }
        break;
    case 2:
        PopulateUpdater(v0->unk_20, v0->unk_10, v0->unk_00);
        PopulateUpdater(v0->unk_24, v0->unk_14, v0->unk_04);
        PopulateUpdater(v0->unk_28, v0->unk_18, v0->unk_08);
        PopulateUpdater(v0->unk_2C, v0->unk_1C, v0->unk_0C);
        param0->unk_00++;
        break;
    case 3:
        if (v0->unk_20) {
            v1[0] = PokedexUpdater_IsPageDataActive(v0->unk_00);
        } else {
            v1[0] = 1;
        }

        if (v0->unk_24) {
            v1[1] = PokedexUpdater_IsPageDataActive(v0->unk_04);
        }

        if (v0->unk_28) {
            v1[2] = PokedexUpdater_IsPageDataActive(v0->unk_08);
        } else {
            v1[2] = 1;
        }

        if (v0->unk_2C) {
            v1[3] = PokedexUpdater_IsPageDataActive(v0->unk_0C);
        } else {
            v1[3] = 1;
        }

        for (v2 = 0; v2 < 4; v2++) {
            if (v1[v2] == 0) {
                break;
            }
        }

        if (v2 >= 4) {
            return 1;
        }

        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

BOOL PokedexTransitionDual_Step(PokedexScreenStateData *param0)
{
    PokedexTransitionDual *v0 = param0->unk_08;
    BOOL v1[2];
    int v2;

    switch (param0->unk_00) {
    case 0:
        PokedexUpdater_DataExit(v0->unk_00);
        PokedexUpdater_DataExit(v0->unk_04);
        param0->unk_00++;
        break;
    case 1:
        v1[0] = PokedexUpdater_IsPageExited(v0->unk_00);
        v1[1] = PokedexUpdater_IsPageExited(v0->unk_04);

        for (v2 = 0; v2 < 2; v2++) {
            if (v1[v2] == 0) {
                break;
            }
        }

        if (v2 >= 2) {
            param0->unk_00++;
        }
        break;
    case 2:
        PopulateUpdater(v0->unk_10, v0->unk_08, v0->unk_00);
        PopulateUpdater(v0->unk_14, v0->unk_0C, v0->unk_04);
        param0->unk_00++;
        break;
    case 3:
        if (v0->unk_10) {
            v1[0] = PokedexUpdater_IsPageDataActive(v0->unk_00);
        } else {
            v1[0] = 1;
        }

        if (v0->unk_14) {
            v1[1] = PokedexUpdater_IsPageDataActive(v0->unk_04);
        } else {
            v1[1] = 1;
        }

        for (v2 = 0; v2 < 2; v2++) {
            if (v1[v2] == 0) {
                break;
            }
        }

        if (v2 >= 2) {
            return 1;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

static void PopulateUpdater(PokedexScreenManager *param0, PokedexScreenStateSet *param1, PokedexUpdater *pokedexUpdater)
{
    PokedexUpdaterTemplate pokedexUpdaterTemplate;

    if (param0) {
        pokedexUpdaterTemplate.pageData = param0->pageData;
        pokedexUpdaterTemplate.pageGraphics = param0->pageGraphics;
        pokedexUpdaterTemplate.dataFunc = param0->dataFunc;
        pokedexUpdaterTemplate.graphicsFunc = param0->graphicsFunc;

        PokedexUpdater_PopulateUpdater(pokedexUpdater, &pokedexUpdaterTemplate);
        PokedexScreenStateSet_SetStates(param1, param0->screenStates, param0->numStates);
    }
}

void PokedexScreenState_Free(PokedexScreenState *param0)
{
    GF_ASSERT(param0->unk_08.unk_08);

    Heap_Free(param0->unk_08.unk_08);
    param0->unk_08.unk_08 = NULL;
}

void Pokedex_021D467C(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionQuadScreens *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionQuadScreens_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionQuadScreens));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionQuadScreens));

    v0->unk_00 = PokedexMain_GetUpdater1(param2);
    v0->unk_04 = PokedexMain_GetUpdater2(param2);
    v0->unk_08 = PokedexMain_GetUpdater3(param2);
    v0->unk_0C = PokedexMain_GetUpdater4(param2);
    v0->unk_10 = PokedexMain_GetScreenStateSet1(param2);
    v0->unk_14 = PokedexMain_GetScreenStateSet2(param2);
    v0->unk_18 = PokedexMain_GetScreenStateSet3(param2);
    v0->unk_1C = PokedexMain_GetScreenStateSet4(param2);
    v0->unk_20 = PokedexMain_GetScreenManager(param2, 1);
    v0->unk_24 = PokedexMain_GetSubScreenManager(param2, 1);
    v0->unk_28 = NULL;
    v0->unk_2C = NULL;

    param1->unk_08.unk_08 = v0;
}

void Pokedex_021D4704(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionQuad *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionQuad_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionQuad));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionQuad));

    v0->unk_00 = PokedexMain_GetUpdater1(param2);
    v0->unk_04 = PokedexMain_GetUpdater2(param2);
    v0->unk_08 = PokedexMain_GetUpdater3(param2);
    v0->unk_0C = PokedexMain_GetUpdater4(param2);
    v0->unk_10 = PokedexMain_GetExitFlag(param2);

    param1->unk_08.unk_08 = v0;
}

void Pokedex_021D475C(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionQuadScreens *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionQuadScreens_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionQuadScreens));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionQuadScreens));

    v0->unk_00 = PokedexMain_GetUpdater1(param2);
    v0->unk_04 = PokedexMain_GetUpdater2(param2);
    v0->unk_08 = PokedexMain_GetUpdater3(param2);
    v0->unk_0C = PokedexMain_GetUpdater4(param2);
    v0->unk_10 = PokedexMain_GetScreenStateSet1(param2);
    v0->unk_14 = PokedexMain_GetScreenStateSet2(param2);
    v0->unk_18 = PokedexMain_GetScreenStateSet3(param2);
    v0->unk_1C = PokedexMain_GetScreenStateSet4(param2);
    v0->unk_20 = PokedexMain_GetScreenManager(param2, 2);
    v0->unk_24 = PokedexMain_GetSubScreenManager(param2, 2);
    v0->unk_28 = PokedexMain_GetScreenManager(param2, 5);
    v0->unk_2C = PokedexMain_GetSubScreenManager(param2, 3);

    param1->unk_08.unk_08 = v0;
}

void Pokedex_021D47F0(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionQuadScreens *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionQuadScreens_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionQuadScreens));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionQuadScreens));

    v0->unk_00 = PokedexMain_GetUpdater1(param2);
    v0->unk_04 = PokedexMain_GetUpdater2(param2);
    v0->unk_08 = PokedexMain_GetUpdater3(param2);
    v0->unk_0C = PokedexMain_GetUpdater4(param2);
    v0->unk_10 = PokedexMain_GetScreenStateSet1(param2);
    v0->unk_14 = PokedexMain_GetScreenStateSet2(param2);
    v0->unk_18 = PokedexMain_GetScreenStateSet3(param2);
    v0->unk_1C = PokedexMain_GetScreenStateSet4(param2);
    v0->unk_20 = PokedexMain_GetScreenManager(param2, 0);
    v0->unk_24 = PokedexMain_GetSubScreenManager(param2, 0);
    v0->unk_28 = NULL;
    v0->unk_2C = NULL;

    param1->unk_08.unk_08 = v0;
}

void Pokedex_021D4878(PokedexScreenState *param0, PokedexApp *param1, enum HeapID heapID, int param3)
{
    PokedexTransitionSingle *v0;

    param0->unk_00 = param3;
    param0->unk_04 = PokedexTransitionSingle_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionSingle));
    GF_ASSERT(v0);

    v0->unk_00 = PokedexMain_GetScreenManager(param1, 0);
    v0->unk_04 = PokedexMain_GetUpdater1(param1);
    v0->unk_08 = PokedexMain_GetScreenStateSet1(param1);

    param0->unk_08.unk_08 = v0;
}

void Pokedex_021D48B8(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionDual *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionDual_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionDual));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionDual));

    v0->unk_00 = PokedexMain_GetUpdater1(param2);
    v0->unk_04 = PokedexMain_GetUpdater2(param2);
    v0->unk_08 = PokedexMain_GetScreenStateSet1(param2);
    v0->unk_0C = PokedexMain_GetScreenStateSet2(param2);
    v0->unk_10 = PokedexMain_GetScreenManager(param2, 6);
    v0->unk_14 = PokedexMain_GetSubScreenManager(param2, 4);

    param1->unk_08.unk_08 = v0;
}

void Pokedex_021D491C(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionDual *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionDual_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionDual));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionDual));

    v0->unk_00 = PokedexMain_GetUpdater1(param2);
    v0->unk_04 = PokedexMain_GetUpdater2(param2);
    v0->unk_08 = PokedexMain_GetScreenStateSet1(param2);
    v0->unk_0C = PokedexMain_GetScreenStateSet2(param2);
    v0->unk_10 = PokedexMain_GetScreenManager(param2, 7);
    v0->unk_14 = PokedexMain_GetSubScreenManager(param2, 5);

    param1->unk_08.unk_08 = v0;
}

void Pokedex_021D4980(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionDual *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionDual_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionDual));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionDual));

    v0->unk_00 = PokedexMain_GetUpdater1(param2);
    v0->unk_04 = PokedexMain_GetUpdater2(param2);
    v0->unk_08 = PokedexMain_GetScreenStateSet1(param2);
    v0->unk_0C = PokedexMain_GetScreenStateSet2(param2);
    v0->unk_10 = PokedexMain_GetScreenManager(param2, 8);
    v0->unk_14 = PokedexMain_GetSubScreenManager(param2, 6);

    param1->unk_08.unk_08 = v0;
}

void Pokedex_021D49E4(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionSingle *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionSingle_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionSingle));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionSingle));

    v0->unk_04 = PokedexMain_GetUpdater1(param2);
    v0->unk_08 = PokedexMain_GetScreenStateSet1(param2);
    v0->unk_00 = PokedexMain_GetScreenManager(param2, 8);

    param1->unk_08.unk_08 = v0;
}

void Pokedex_021D4A3C(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionSingle *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionSingle_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionSingle));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionSingle));

    v0->unk_04 = PokedexMain_GetUpdater1(param2);
    v0->unk_08 = PokedexMain_GetScreenStateSet1(param2);
    v0->unk_00 = PokedexMain_GetScreenManager(param2, 9);

    param1->unk_08.unk_08 = v0;
}

void Pokedex_021D4A94(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionDual *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionDual_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionDual));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionDual));

    v0->unk_00 = PokedexMain_GetUpdater1(param2);
    v0->unk_04 = PokedexMain_GetUpdater2(param2);
    v0->unk_08 = PokedexMain_GetScreenStateSet1(param2);
    v0->unk_0C = PokedexMain_GetScreenStateSet2(param2);
    v0->unk_10 = PokedexMain_GetScreenManager(param2, 2);
    v0->unk_14 = PokedexMain_GetSubScreenManager(param2, 2);

    param1->unk_08.unk_08 = v0;
}

void Pokedex_021D4AF8(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionSingle *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionSingle_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionSingle));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionSingle));

    v0->unk_04 = PokedexMain_GetUpdater1(param2);
    v0->unk_08 = PokedexMain_GetScreenStateSet1(param2);
    v0->unk_00 = PokedexMain_GetScreenManager(param2, 2);

    param1->unk_08.unk_08 = v0;
}

void Pokedex_021D4B50(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionDual *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionDual_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionDual));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionDual));

    v0->unk_00 = PokedexMain_GetUpdater1(param2);
    v0->unk_04 = PokedexMain_GetUpdater2(param2);
    v0->unk_08 = PokedexMain_GetScreenStateSet1(param2);
    v0->unk_0C = PokedexMain_GetScreenStateSet2(param2);
    v0->unk_10 = PokedexMain_GetScreenManager(param2, 3);
    v0->unk_14 = PokedexMain_GetSubScreenManager(param2, 7);

    param1->unk_08.unk_08 = v0;
}

void Pokedex_021D4BB4(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3)
{
    PokedexTransitionSingle *v0;

    param1->unk_00 = param3;
    param1->unk_04 = PokedexTransitionSingle_Step;

    v0 = Heap_Alloc(heapID, sizeof(PokedexTransitionSingle));

    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexTransitionSingle));

    v0->unk_04 = PokedexMain_GetUpdater1(param2);
    v0->unk_08 = PokedexMain_GetScreenStateSet1(param2);
    v0->unk_00 = PokedexMain_GetScreenManager(param2, 4);

    param1->unk_08.unk_08 = v0;
}
