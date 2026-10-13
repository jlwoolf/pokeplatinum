#include "applications/pokedex/pokedex_screen_state_set.h"

#include <nitro.h>
#include <string.h>

#include "constants/heap.h"

#include "applications/pokedex/struct_pokedex_screen_state.h"

#include "heap.h"

typedef struct PokedexScreenStateSet_t {
    PokedexScreenState *screenStates;
    int numStates;
    PokedexScreenState *currentState;
} PokedexScreenStateSet;

static BOOL IsStateActive(PokedexScreenStateSet *param0);
static PokedexScreenState *FindMatchingState(PokedexScreenStateSet *param0, int param1);
static void SetCurrentState(PokedexScreenStateSet *param0, PokedexScreenState *param1);

PokedexScreenStateSet *PokedexScreenStateSet_New(enum HeapID heapID)
{
    PokedexScreenStateSet *v0 = Heap_Alloc(heapID, sizeof(PokedexScreenStateSet));
    GF_ASSERT(v0);
    memset(v0, 0, sizeof(PokedexScreenStateSet));

    return v0;
}

void PokedexScreenStateSet_SetStates(PokedexScreenStateSet *param0, PokedexScreenState *param1, int param2)
{
    GF_ASSERT(param0);

    param0->screenStates = param1;
    param0->numStates = param2;
}

const PokedexScreenState *PokedexScreenStateSet_Update(PokedexScreenStateSet *param0, int param1)
{
    PokedexScreenState *v0;
    BOOL v1;

    GF_ASSERT(param0);

    if (IsStateActive(param0) == 0) {
        v0 = FindMatchingState(param0, param1);

        if (v0) {
            SetCurrentState(param0, v0);
        }
    }

    if (IsStateActive(param0) == 1) {
        v1 = param0->currentState->stepFunc(&param0->currentState->stepData);

        if (v1 == 1) {
            SetCurrentState(param0, NULL);
        }
    }

    return param0->currentState;
}

BOOL PokedexScreenStateSet_IsActive(PokedexScreenStateSet *param0)
{
    GF_ASSERT(param0);

    if (param0->currentState) {
        return 1;
    }

    return 0;
}

static BOOL IsStateActive(PokedexScreenStateSet *param0)
{
    if (param0->currentState) {
        return 1;
    }

    return 0;
}

static PokedexScreenState *FindMatchingState(PokedexScreenStateSet *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < param0->numStates; v0++) {
        GF_ASSERT(param0->screenStates);

        if (param0->screenStates[v0].transitionMask & param1) {
            return param0->screenStates + v0;
        }
    }

    return NULL;
}

static void SetCurrentState(PokedexScreenStateSet *param0, PokedexScreenState *param1)
{
    param0->currentState = param1;

    if (param0->currentState) {
        param0->currentState->stepData.state = 0;
    }
}
