#include "applications/pokedex/pokedex_main.h"

#include <nitro.h>
#include <nnsys.h>
#include <string.h>

#include "applications/pokedex/crysub.h"
#include "applications/pokedex/formmain.h"
#include "applications/pokedex/formsub.h"
#include "applications/pokedex/funcptr_pokedex_screen_init.h"
#include "applications/pokedex/funcptr_pokedex_screen_exit.h"
#include "applications/pokedex/infomain.h"
#include "applications/pokedex/infomain_foreign.h"
#include "applications/pokedex/pokedex_screen_state_set.h"
#include "applications/pokedex/pokedex_screen_transition.h"
#include "applications/pokedex/pokedex_list.h"
#include "applications/pokedex/pokedex_list_controls.h"
#include "applications/pokedex/pokedex_search_screen.h"
#include "applications/pokedex/pokedex_area_map.h"
#include "applications/pokedex/pokedex_area_list.h"
#include "applications/pokedex/pokedex_info_controls.h"
#include "applications/pokedex/pokedex_info_menu.h"
#include "applications/pokedex/pokedex_cry_screen.h"
#include "applications/pokedex/pokedex_size_menu.h"
#include "applications/pokedex/pokedex_size_comparison.h"
#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/pokedex_graphics.h"
#include "applications/pokedex/pokedex_height_check.h"
#include "applications/pokedex/pokedex_search.h"
#include "applications/pokedex/pokedex_sort.h"
#include "applications/pokedex/pokedex_text.h"
#include "applications/pokedex/pokedex_text_manager.h"
#include "applications/pokedex/pokedex_updater.h"
#include "applications/pokedex/species_caught_status.h"

#include "bg_window.h"
#include "brightness_controller.h"
#include "char_transfer.h"
#include "genders.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "overlay_manager.h"
#include "pltt_transfer.h"
#include "pokedex.h"
#include "pokedex_data_index.h"
#include "pokemon.h"
#include "render_oam.h"
#include "screen_fade.h"
#include "sound.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "string_gf.h"
#include "system.h"
#include "text.h"
#include "touch_pad.h"
#include "touch_screen.h"
#include "font_oam.h"
#include "g3_buffer.h"
#include "vram_transfer.h"

#include "res/text/bank/pokedex.h"

enum PokedexState {
    POKEDEX_STATE_TRANSITION_IN,
    POKEDEX_STATE_USE,
    POKEDEX_STATE_TRANSITION_OUT,
    POKEDEX_STATE_WAIT_EXIT
};

static void VBlankCallBack(void *data);
static void EntranceTransition(PokedexApp **appPtr);
static void ExitTransition(PokedexApp **appPtr);
static BOOL TransitionComplete(PokedexApp **appPtr);
static void FreePokedexApp(PokedexApp *pokedexApp);
static void SetGXBanks(void);
static void InitG2(enum HeapID heapID);
static void InitG3(void);
static void ResetFrm(void);
static void PokedexMain_InitScreenStateSet(PokedexApp *pokedexApp);

int PokedexMain_Init(ApplicationManager *appMan, int *state)
{
    PokedexOverlayArgs pokedexOverlayArgs;

    Sound_SetSceneAndPlayBGM(SOUND_SCENE_SUB_54, SEQ_NONE, 0);
    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_POKEDEX, 0x40000);

    PokedexApp **appPtr = ApplicationManager_NewData(appMan, sizeof(PokedexApp **), HEAP_ID_POKEDEX);

    GF_ASSERT(appPtr);
    memset(appPtr, 0, sizeof(PokedexApp **));

    VramTransfer_New(8, HEAP_ID_POKEDEX);

    PokedexOverlayArgs *overlayArgsInput = ApplicationManager_Args(appMan);

    Pokedex_SetupGiratina(Pokedex_GetDisplayForm(overlayArgsInput->pokedex, SPECIES_GIRATINA, 0));

    SetVBlankCallback(VBlankCallBack, appPtr);
    DisableHBlank();
    EnableTouchPad();

    GF_ASSERT(InitializeTouchPad(4) == TRUE);

    PokedexMain_InitGX(HEAP_ID_POKEDEX);

    pokedexOverlayArgs.pokedex = overlayArgsInput->pokedex;
    pokedexOverlayArgs.trainerInfo = overlayArgsInput->trainerInfo;
    pokedexOverlayArgs.timeOfDay = overlayArgsInput->timeOfDay;
    pokedexOverlayArgs.fullmoonIslandVisible = overlayArgsInput->fullmoonIslandVisible;
    pokedexOverlayArgs.seabreakPathVisible = overlayArgsInput->seabreakPathVisible;
    pokedexOverlayArgs.newmoonIslandVisible = overlayArgsInput->newmoonIslandVisible;
    pokedexOverlayArgs.springPathVisible = overlayArgsInput->springPathVisible;
    pokedexOverlayArgs.pokedexMemory = overlayArgsInput->pokedexMemory;

    *appPtr = PokedexMain_NewPokedexApp(HEAP_ID_POKEDEX, &pokedexOverlayArgs);

    Sound_SetPlayerVolume(1, 127 / 3);

    return 1;
}

int PokedexMain_Main(ApplicationManager *appMan, int *state)
{
    PokedexApp **appPtr = ApplicationManager_Data(appMan);

    switch (*state) {
    case POKEDEX_STATE_TRANSITION_IN:
        EntranceTransition(appPtr);
        BrightnessController_SetScreenBrightness(-16, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 3);
        (*state)++;
        break;
    case POKEDEX_STATE_USE:
        if (PokedexMain_Update(*appPtr) == TRUE) {
            *appPtr = NULL;
            (*state)++;
        }
        break;
    case POKEDEX_STATE_TRANSITION_OUT:
        ExitTransition(appPtr);
        (*state)++;
        break;
    case POKEDEX_STATE_WAIT_EXIT:
        if (TransitionComplete(appPtr)) {
            ResetVisibleHardwareWindows(DS_SCREEN_MAIN);
            ResetVisibleHardwareWindows(DS_SCREEN_SUB);
            G2_BlendNone();
            G2S_BlendNone();
            return 1;
        }
        break;
    }

    return 0;
}

int PokedexMain_Exit(ApplicationManager *appMan, int *state)
{
    ApplicationManager_Data(appMan);

    SetVBlankCallback(NULL, NULL);

    GF_ASSERT(DisableTouchPad() == TRUE);

    PokedexMain_FreeGraphics();
    VramTransfer_Free();
    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_POKEDEX);
    Sound_SetPlayerVolume(1, 127);

    return 1;
}

static void VBlankCallBack(void *data)
{
    PokedexApp **appPtr = data;

    if (*appPtr) {
        PokedexMain_UpdateSprites(*appPtr);
    }

    VramTransfer_Process();
}

static void EntranceTransition(PokedexApp **appPtr)
{
    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_POKEDEX);
}

static void ExitTransition(PokedexApp **appPtr)
{
    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_POKEDEX);
}

static BOOL TransitionComplete(PokedexApp **appPtr)
{
    return IsScreenFadeDone();
}

const static PokedexScreenInitFunc sScreenInitFunctions[10] = {
    PokedexList_Init,
    PokedexSearch_TransitionFunctions,
    InfoMain_InitScreen,
    FormMain_Init,
    InfoMainForeign_InitScreen,
    PokedexInfoMenu_Init,
    PokedexAreaMap_Init,
    PokedexCryScreen_Init,
    PokedexHeightCheck_Init,
    PokedexSizeComparison_Init
};

const static PokedexScreenInitFunc sSubScreenInitFunctions[8] = {
    PokedexListControls_Init,
    PokedexSearchScreen_Init,
    PokedexInfoControls_Init,
    PokedexInfoMenu_InitSub,
    PokedexAreaList_Init,
    CrySub_Init,
    PokedexSizeMenu_Init,
    FormSub_Init
};

const static PokedexScreenExitFunc sScreenExitFunctions[10] = {
    PokedexList_Free,
    PokedexSearch_FreeData,
    InfoMain_FreeScreen,
    FormMain_Free,
    InfoMainForeign_FreeScreen,
    PokedexInfoMenu_Free,
    PokedexAreaMap_Free,
    PokedexCryScreen_Free,
    PokedexHeightCheck_Free,
    PokedexSizeComparison_Free
};

const static PokedexScreenExitFunc sSubScreenExitFunctions[8] = {
    PokedexListControls_Free,
    PokedexSearchScreen_Free,
    PokedexInfoControls_Free,
    PokedexInfoMenu_FreeSub,
    PokedexAreaList_Free,
    CrySub_Free,
    PokedexSizeMenu_Free,
    FormSub_Free
};

PokedexApp *PokedexMain_NewPokedexApp(enum HeapID heapID, const PokedexOverlayArgs *pokedexOverlayArgs)
{
    int i;
    PokedexDefaultSortParams sortParams;

    PokedexApp *pokedexApp = Heap_Alloc(heapID, sizeof(PokedexApp));

    GF_ASSERT(pokedexApp);
    memset(pokedexApp, 0, sizeof(PokedexApp));

    pokedexApp->heapID = heapID;
    pokedexApp->pokedexMemory = pokedexOverlayArgs->pokedexMemory;
    pokedexApp->screenStateSet1 = PokedexScreenStateSet_New(heapID);
    pokedexApp->screenStateSet2 = PokedexScreenStateSet_New(heapID);
    pokedexApp->screenStateSet3 = PokedexScreenStateSet_New(heapID);
    pokedexApp->screenStateSet4 = PokedexScreenStateSet_New(heapID);
    pokedexApp->updater1 = PokedexUpdater_New(heapID);
    pokedexApp->updater2 = PokedexUpdater_New(heapID);
    pokedexApp->updater3 = PokedexUpdater_New(heapID);
    pokedexApp->updater4 = PokedexUpdater_New(heapID);

    sortParams.pokedex = pokedexOverlayArgs->pokedex;
    sortParams.trainerInfo = pokedexOverlayArgs->trainerInfo;
    sortParams.timeOfDay = pokedexOverlayArgs->timeOfDay;
    sortParams.fullmoonIslandVisible = pokedexOverlayArgs->fullmoonIslandVisible;
    sortParams.newmoonIslandVisible = pokedexOverlayArgs->newmoonIslandVisible;
    sortParams.springPathVisible = pokedexOverlayArgs->springPathVisible;
    sortParams.seabreakPathVisible = pokedexOverlayArgs->seabreakPathVisible;
    sortParams.currentSpecies = PokedexMemory_GetCurrentSpecies(pokedexOverlayArgs->pokedexMemory);
    sortParams.bootMode = PokedexMemory_GetBootMode(pokedexOverlayArgs->pokedexMemory);

    PokedexSort_DefaultPokedexSort(&pokedexApp->sortData, &sortParams, heapID);
    PokedexGraphics_Init(&pokedexApp->graphicData, heapID);

    for (i = 0; i < 10; i++) {
        if (sScreenInitFunctions[i]) {
            sScreenInitFunctions[i](&pokedexApp->screenManagers[i], pokedexApp, heapID);
        }
    }

    for (i = 0; i < 8; i++) {
        if (sSubScreenInitFunctions[i]) {
            sSubScreenInitFunctions[i](&pokedexApp->subScreenManagers[i], pokedexApp, heapID);
        }
    }

    Pokedex_021D47F0(heapID, &pokedexApp->baseScreenState, pokedexApp, 1);
    PokedexMain_InitScreenStateSet(pokedexApp);

    return pokedexApp;
}

BOOL PokedexMain_Update(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);

    PokedexSort_UpdateInputState(&pokedexApp->sortData);

    if ((PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet3) == 0) && (PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet1) == 0) && (PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet4) == 0) && (PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet2) == 0)) {
        PokedexUpdater_SetDataUnchanged(pokedexApp->updater3, 0);
        PokedexUpdater_SetDataUnchanged(pokedexApp->updater4, 0);
        PokedexUpdater_SetDataUnchanged(pokedexApp->updater1, 0);
        PokedexUpdater_SetDataUnchanged(pokedexApp->updater2, 0);
    } else {
        PokedexUpdater_SetDataUnchanged(pokedexApp->updater3, 1);
        PokedexUpdater_SetDataUnchanged(pokedexApp->updater4, 1);
        PokedexUpdater_SetDataUnchanged(pokedexApp->updater1, 1);
        PokedexUpdater_SetDataUnchanged(pokedexApp->updater2, 1);
    }

    PokedexUpdater_UpdateData(pokedexApp->updater3);
    PokedexUpdater_UpdateData(pokedexApp->updater4);
    PokedexUpdater_UpdateData(pokedexApp->updater1);
    PokedexUpdater_UpdateData(pokedexApp->updater2);

    PokedexUpdater_UpdateGraphics(pokedexApp->updater3);
    PokedexUpdater_UpdateGraphics(pokedexApp->updater4);
    PokedexUpdater_UpdateGraphics(pokedexApp->updater1);
    PokedexUpdater_UpdateGraphics(pokedexApp->updater2);

    if ((PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet1) == 0) && (PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet4) == 0) && (PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet2) == 0)) {
        PokedexScreenStateSet_Update(pokedexApp->screenStateSet3, pokedexApp->transitionRequest3);
    }

    if ((PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet3) == 0) && (PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet4) == 0) && (PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet2) == 0)) {
        PokedexScreenStateSet_Update(pokedexApp->screenStateSet1, pokedexApp->transitionRequest1);
    }

    if ((PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet3) == 0) && (PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet1) == 0) && (PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet2) == 0)) {
        PokedexScreenStateSet_Update(pokedexApp->screenStateSet4, pokedexApp->transitionRequest4);
    }

    if ((PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet3) == 0) && (PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet1) == 0) && (PokedexScreenStateSet_IsActive(pokedexApp->screenStateSet4) == 0)) {
        PokedexScreenStateSet_Update(pokedexApp->screenStateSet2, pokedexApp->transitionRequest2);
    }

    G3_ResetG3X();
    PokemonGraphics_UpdateSprites(&pokedexApp->graphicData);
    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);

    pokedexApp->transitionRequest3 = 0;
    pokedexApp->transitionRequest4 = 0;
    pokedexApp->transitionRequest1 = 0;
    pokedexApp->transitionRequest2 = 0;

    if (pokedexApp->exitFlag == 1) {
        FreePokedexApp(pokedexApp);
        pokedexApp = NULL;
        return 1;
    }

    return 0;
}

void PokedexMain_InitGX(enum HeapID heapID)
{
    SetGXBanks();
    InitG2(heapID);
    InitG3();
}

void PokedexMain_FreeGraphics(void)
{
    RenderOam_Free();
    CharTransfer_Free();
    PlttTransfer_Free();
    ResetFrm();
}

void PokedexMain_UpdateSprites(PokedexApp *pokedexApp)
{
    PokemonGraphics_UpdateCharAndPltt(&pokedexApp->graphicData);
    RenderOam_Transfer();
}

PokedexUpdater *PokedexMain_GetUpdater1(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return pokedexApp->updater1;
}

PokedexUpdater *PokedexMain_GetUpdater2(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return pokedexApp->updater2;
}

PokedexUpdater *PokedexMain_GetUpdater3(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return pokedexApp->updater3;
}

PokedexUpdater *PokedexMain_GetUpdater4(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return pokedexApp->updater4;
}

PokedexScreenStateSet *PokedexMain_GetScreenStateSet1(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return pokedexApp->screenStateSet1;
}

PokedexScreenStateSet *PokedexMain_GetScreenStateSet2(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return pokedexApp->screenStateSet2;
}

PokedexScreenStateSet *PokedexMain_GetScreenStateSet3(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return pokedexApp->screenStateSet3;
}

PokedexScreenStateSet *PokedexMain_GetScreenStateSet4(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return pokedexApp->screenStateSet4;
}

int *PokedexMain_GetTransitionRequest1(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return &pokedexApp->transitionRequest1;
}

int *PokedexMain_GetTransitionRequest2(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return &pokedexApp->transitionRequest2;
}

int *PokedexMain_GetTransitionRequest3(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return &pokedexApp->transitionRequest3;
}

int *PokedexMain_GetTransitionRequest4(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return &pokedexApp->transitionRequest4;
}

BOOL *PokedexMain_GetExitFlag(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return &pokedexApp->exitFlag;
}

PokedexSortData *PokedexMain_GetSortData(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return &pokedexApp->sortData;
}

PokedexGraphicData *PokedexMain_GetGraphicData(PokedexApp *pokedexApp)
{
    GF_ASSERT(pokedexApp);
    return &pokedexApp->graphicData;
}

PokedexScreenManager *PokedexMain_GetScreenManager(PokedexApp *pokedexApp, int param1)
{
    GF_ASSERT(param1 < 10);
    return &pokedexApp->screenManagers[param1];
}

PokedexScreenManager *PokedexMain_GetSubScreenManager(PokedexApp *pokedexApp, int param1)
{
    GF_ASSERT(param1 < 8);
    return &pokedexApp->subScreenManagers[param1];
}

void PokedexMain_SetCursorAnimFrame(Sprite *param0, int param1)
{
    switch (param1) {
    case 0:
        Sprite_SetAnimFrame(param0, 1);
        break;
    case 2:
        Sprite_SetAnimFrame(param0, 2);
        break;
    case 1:
        Sprite_SetAnimFrame(param0, 3);
        break;
    case 3:
    case (3 + 1):
        if (Sprite_GetAnimFrame(param0) > 0) {
            Sprite_UpdateAnim(param0, -(FX32_ONE * 2));
        }
        break;
    default:
        break;
    }
}

void PokedexMain_SetButtonY(Sprite *sprite, PokedexTextData *textData, int setY)
{
    int frame = Sprite_GetAnimFrame(sprite);
    int x, y;

    switch (frame) {
    case 0:
        FontOAM_GetXY(textData->fontOAM, &x, &y);
        y = setY;
        FontOAM_SetXY(textData->fontOAM, x, y);
        break;
    case 1:
        FontOAM_GetXY(textData->fontOAM, &x, &y);
        y = setY + -2;
        FontOAM_SetXY(textData->fontOAM, x, y);
        break;
    case 2:
        FontOAM_GetXY(textData->fontOAM, &x, &y);
        y = setY + -4;
        FontOAM_SetXY(textData->fontOAM, x, y);
        break;
    case 3:
        FontOAM_GetXY(textData->fontOAM, &x, &y);
        y = setY + -2;
        FontOAM_SetXY(textData->fontOAM, x, y);
        break;
    }
}

void PokedexMain_SetTextSprite(Sprite *param0, PokedexTextData *textData, int param2, int param3, int param4)
{
    int v0;

    PokedexMain_SetButtonY(param0, textData, param2);
    v0 = Sprite_GetAnimFrame(param0);

    if (v0 < 2) {
        FontOAM_SetExplicitPaletteOffsetAutoAdjust(textData->fontOAM, param3);
    } else {
        FontOAM_SetExplicitPaletteOffsetAutoAdjust(textData->fontOAM, param4);
    }
}

void PokedexMain_SetHitTableRect(TouchScreenHitTable *hitTable, int top, int bottom, int left, int right)
{
    hitTable->rect.top = top;
    hitTable->rect.bottom = bottom;
    hitTable->rect.left = left;
    hitTable->rect.right = right;
}

void PokedexMain_SetLoadingScreenParams(PokedexLoadingScreen *pokedexLoadingScreen, BgConfig *bgConfig, int layer, NNSG2dScreenData *screenData, int topStart, int topEnd, int bottomStart, int bottomEnd, int duration)
{
    pokedexLoadingScreen->bgConfig = bgConfig;
    pokedexLoadingScreen->layer = layer;
    pokedexLoadingScreen->screenData = screenData;
    pokedexLoadingScreen->topStart = topStart;
    pokedexLoadingScreen->topDist = topEnd - topStart;
    pokedexLoadingScreen->bottomStart = bottomStart;
    pokedexLoadingScreen->bottomDist = bottomEnd - bottomStart;
    pokedexLoadingScreen->duration = duration;
    pokedexLoadingScreen->counter = 0;
}

BOOL PokedexMain_LoadingScreenMove(PokedexLoadingScreen *loadingScreen)
{
    int topPos;
    int bottomPos;

    if (loadingScreen->counter <= loadingScreen->duration) {
        Bg_FillTilemapRect(loadingScreen->bgConfig, loadingScreen->layer, 0, 0, 0, 32, 24, 16);

        topPos = (loadingScreen->topDist * loadingScreen->counter) / loadingScreen->duration;
        bottomPos = (loadingScreen->bottomDist * loadingScreen->counter) / loadingScreen->duration;
        topPos += loadingScreen->topStart;
        bottomPos += loadingScreen->bottomStart;

        if (topPos > 0) {
            Bg_CopyToTilemapRect(loadingScreen->bgConfig, loadingScreen->layer, 0, 0, 32, topPos, loadingScreen->screenData->rawData, 0, 32 - topPos, 32, 32);
        }

        if ((32 - bottomPos) > 0) {
            Bg_CopyToTilemapRect(loadingScreen->bgConfig, loadingScreen->layer, 0, 32 - bottomPos, 32, bottomPos, loadingScreen->screenData->rawData, 0, 0, 32, 32);
        }

        Bg_ScheduleTilemapTransfer(loadingScreen->bgConfig, loadingScreen->layer);
        loadingScreen->counter++;

        return FALSE;
    }

    return TRUE;
}

void PokedexMain_DisplayNameNumberText(Window *window, int dexNumber, int species, enum HeapID heapID)
{
    String *numStr;
    String *nameNumber;

    if (dexNumber > 0) {
        numStr = String_Init(4, heapID);
        String_FormatInt(numStr, dexNumber, 3, 2, 1);
    } else {
        numStr = PokedexMain_GetMessage(pl_msg_pokedex_none, heapID);
    }

    nameNumber = PokedexText_NameNumber(species, GAME_LANGUAGE, heapID);

    Text_AddPrinterWithParamsAndColor(window, FONT_SUBSCREEN, numStr, 22, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(3, 2, 1), NULL);
    Text_AddPrinterWithParamsAndColor(window, FONT_SUBSCREEN, nameNumber, 49, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(3, 2, 1), NULL);
    String_Free(numStr);

    PokedexText_Free(nameNumber);
}

Window *PokedexMain_DisplayNameNumber(PokedexGraphicData *pokedexgraphicData, const PokedexSortData *pokedexSortData, enum HeapID heapID, int species)
{
    Window *window;

    if (PokedexSort_IsNationalDex(pokedexSortData) == FALSE) {
        window = PokedexMain_DisplayNameNumberLocal(pokedexgraphicData->textMan, heapID, species);
    } else {
        window = PokedexMain_DisplayNameNumberNational(pokedexgraphicData->textMan, heapID, species);
    }

    return window;
}

Window *PokedexMain_DisplayNameNumberNational(PokedexTextManager *textMan, enum HeapID heapID, int species)
{
    Window *window = PokedexTextManager_NewWindow(textMan, 15, 2);
    PokedexMain_DisplayNameNumberText(window, species, species, heapID);

    return window;
}

Window *PokedexMain_DisplayNameNumberLocal(PokedexTextManager *textMan, enum HeapID heapID, int species)
{
    int dexNumber = Pokemon_SinnohDexNumber(species);

    if ((species != SPECIES_REGIROCK) && (species != SPECIES_REGICE) && (species != SPECIES_REGISTEEL)) {
        GF_ASSERT(dexNumber > 0);
    }

    Window *window = PokedexTextManager_NewWindow(textMan, 15, 2);
    PokedexMain_DisplayNameNumberText(window, dexNumber, species, heapID);

    return window;
}

void PokedexMain_EntryNameNumber(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, enum HeapID heapID, int statusIndex, fx32 x, fx32 y)
{
    PokedexDisplayBox displayBox;
    VecFx32 position;
    u32 isNationalDex = PokedexSort_IsNationalDex(pokedexSortData);

    const SpeciesCaughtStatus *speciesCaughtStatus = PokedexSort_StatusIndexToCaughtStatus(pokedexSortData, statusIndex);
    Sprite *nameTag = PokedexGraphics_GetNameTag(pokedexGraphicData);
    Sprite *caughtIcon = PokedexGraphics_GetCaughtIcon(pokedexGraphicData);

    position.x = x;
    position.y = y;

    Sprite_SetPosition(nameTag, &position);
    Sprite_SetDrawFlag(nameTag, TRUE);

    if (speciesCaughtStatus->caughtStatus == CS_CAUGHT) {
        position.x = x + (-54 * FX32_ONE);
        position.y = y;

        Sprite_SetPosition(caughtIcon, &position);
        Sprite_SetDrawFlag(caughtIcon, TRUE);
    } else {
        Sprite_SetDrawFlag(caughtIcon, FALSE);
    }

    SpriteResource *v4 = PokedexGraphics_GetSpeciesLabelSpriteResource(pokedexGraphicData, 1);

    displayBox.textMan = pokedexGraphicData->textMan;
    displayBox.paletteProxy = SpriteTransfer_GetPaletteProxy(v4, NULL);
    displayBox.sprite = nameTag;
    displayBox.x = -(128 / 2);
    displayBox.y = -(16 / 2);
    displayBox.spriteResourcePriority = 0;
    displayBox.spriteListPriority = 0;
    displayBox.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    displayBox.heapID = heapID;

    Window *window = PokedexMain_DisplayNameNumber(pokedexGraphicData, pokedexSortData, heapID, speciesCaughtStatus->species);
    displayBox.window = window;

    PokedexGraphics_UpdatePokedexSpeciesLabel(pokedexGraphicData, &displayBox, 0, speciesCaughtStatus->species, isNationalDex);
    PokedexTextManager_FreeWindow(window);
}

void PokedexMain_SetSpeciesLabelPos(PokedexGraphicData *param0, int param1, int param2)
{
    PokedexMain_SetSpeciesLabelXY(&param0->pokedexSpeciesLabel, param1, param2);
}

void PokedexMain_SetSpeciesLabelXY(PokedexSpeciesLabel *pokedexSpeciesLabel, int param1, int param2)
{
    VecFx32 v0;

    v0.x = param1 << FX32_SHIFT;
    v0.y = param2 << FX32_SHIFT;

    Sprite_SetPosition(pokedexSpeciesLabel->nameTag, &v0);
    v0.x += (-54 * FX32_ONE);
    Sprite_SetPosition(pokedexSpeciesLabel->caughtIcon, &v0);

    if (pokedexSpeciesLabel->textData->fontOAM) {
        FontOAM_UpdatePosition(pokedexSpeciesLabel->textData->fontOAM);
    }
}

void PokedexMain_DisplayPokemonSprite(PokedexGraphicData *pokedexGraphicData, PokedexSortData *pokedexSortData, int species, int face, int x, int y)
{
    switch (species) {
    case SPECIES_UNOWN:
        PokedexMain_DisplayUnownSprite(pokedexGraphicData, pokedexSortData, face, x, y, 0, SPRITEINDEX_CURRENT_FRONT);
        break;
    case SPECIES_BURMY:
        PokedexMain_DisplayBurmySprite(pokedexGraphicData, pokedexSortData, face, x, y, 0, SPRITEINDEX_CURRENT_FRONT);
        break;
    case SPECIES_WORMADAM:
        PokedexMain_DisplayWormadamSprite(pokedexGraphicData, pokedexSortData, face, x, y, 0, SPRITEINDEX_CURRENT_FRONT);
        break;
    case SPECIES_SHELLOS:
        PokedexMain_DisplayShellosSprite(pokedexGraphicData, pokedexSortData, face, x, y, 0, SPRITEINDEX_CURRENT_FRONT);
        break;
    case SPECIES_GASTRODON:
        PokedexMain_DisplayGastrodonSprite(pokedexGraphicData, pokedexSortData, face, x, y, 0, SPRITEINDEX_CURRENT_FRONT);
        break;
    case SPECIES_DEOXYS:
        PokedexMain_DisplayDeoxysSprite(pokedexGraphicData, pokedexSortData, face, x, y, 0, SPRITEINDEX_CURRENT_FRONT);
        break;
    case SPECIES_SHAYMIN:
        PokedexMain_DisplayShayminSprite(pokedexGraphicData, pokedexSortData, face, x, y, 0, SPRITEINDEX_CURRENT_FRONT);
        break;
    case SPECIES_GIRATINA:
        PokedexMain_DisplayGiratinaSprite(pokedexGraphicData, pokedexSortData, face, x, y, 0, SPRITEINDEX_CURRENT_FRONT);
        break;
    case SPECIES_ROTOM:
        PokedexMain_DisplayRotomSprite(pokedexGraphicData, pokedexSortData, face, x, y, 0, SPRITEINDEX_CURRENT_FRONT);
        break;
    default:
        PokedexMain_DisplaySpeciesSprite(pokedexGraphicData, pokedexSortData, species, face, x, y, 0, SPRITEINDEX_CURRENT_FRONT);
        break;
    }
}

u32 PokedexMain_DisplaySpeciesSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int species, int face, int x, int y, int formIndex, int spriteIndex)
{
    u32 personality = 0;

    if (species == SPECIES_SPINDA) {
        personality = PokedexSort_SpindaForm(pokedexSortData);
    }

    int gender = PokedexSort_Gender(pokedexSortData, species, formIndex);

    if (gender != -1) {
        PokedexGraphics_LoadPokemonSprite(pokedexGraphicData, species, gender, face, FALSE, 0, personality, x, y, spriteIndex);
    }

    return gender;
}

u32 PokedexMain_DisplayUnownSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex)
{
    int form = PokedexSort_UnownForm(pokedexSortData, formIndex);

    if (form != -1) {
        PokedexGraphics_LoadPokemonSprite(pokedexGraphicData, SPECIES_UNOWN, GENDER_NONE, face, FALSE, form, 0, x, y, spriteIndex);
    }

    return form;
}

u32 PokedexMain_DisplayShellosSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex)
{
    int form = PokedexSort_ShellosForm(pokedexSortData, formIndex);

    if (form != -1) {
        PokedexGraphics_LoadPokemonSprite(pokedexGraphicData, SPECIES_SHELLOS, GENDER_MALE, face, FALSE, form, 0, x, y, spriteIndex);
    }

    return form;
}

u32 PokedexMain_DisplayGastrodonSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex)
{
    int form = PokedexSort_GastrodonForm(pokedexSortData, formIndex);

    if (form != -1) {
        PokedexGraphics_LoadPokemonSprite(pokedexGraphicData, SPECIES_GASTRODON, GENDER_MALE, face, FALSE, form, 0, x, y, spriteIndex);
    }

    return form;
}

u32 PokedexMain_DisplayBurmySprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex)
{
    int form = PokedexSort_BurmyForm(pokedexSortData, formIndex);

    if (form != -1) {
        PokedexGraphics_LoadPokemonSprite(pokedexGraphicData, SPECIES_BURMY, GENDER_MALE, face, FALSE, form, 0, x, y, spriteIndex);
    }

    return form;
}

u32 PokedexMain_DisplayWormadamSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex)
{
    int form = PokedexSort_WormadamForm(pokedexSortData, formIndex);

    if (form != -1) {
        PokedexGraphics_LoadPokemonSprite(pokedexGraphicData, SPECIES_WORMADAM, GENDER_FEMALE, face, FALSE, form, 0, x, y, spriteIndex);
    }

    return form;
}

u32 PokedexMain_DisplayDeoxysSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex)
{
    int form = PokedexSort_DeoxysForm(pokedexSortData, formIndex);

    if (form != 15) {
        PokedexGraphics_LoadPokemonSprite(pokedexGraphicData, SPECIES_DEOXYS, GENDER_FEMALE, face, FALSE, form, 0, x, y, spriteIndex);
    }

    return form;
}

u32 PokedexMain_DisplayShayminSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex)
{
    int form;
    int numFormsSeen = PokedexSort_NumFormsSeen(pokedexSortData, SPECIES_SHAYMIN);

    if (numFormsSeen > formIndex) {
        form = PokedexSort_Form(pokedexSortData, SPECIES_SHAYMIN, formIndex);
        PokedexGraphics_LoadPokemonSprite(pokedexGraphicData, SPECIES_SHAYMIN, GENDER_FEMALE, face, FALSE, form, 0, x, y, spriteIndex);
    } else {
        form = -1;
    }

    return form;
}

u32 PokedexMain_DisplayGiratinaSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex)
{
    int form;
    int numFormsSeen = PokedexSort_NumFormsSeen(pokedexSortData, SPECIES_GIRATINA);

    if (numFormsSeen > formIndex) {
        form = PokedexSort_Form(pokedexSortData, SPECIES_GIRATINA, formIndex);
        PokedexGraphics_LoadPokemonSprite(pokedexGraphicData, SPECIES_GIRATINA, GENDER_FEMALE, face, FALSE, form, 0, x, y, spriteIndex);
    } else {
        form = -1;
    }

    return form;
}

u32 PokedexMain_DisplayRotomSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex)
{
    int form;
    int numFormsSeen = PokedexSort_NumFormsSeen(pokedexSortData, SPECIES_ROTOM);

    if (numFormsSeen > formIndex) {
        form = PokedexSort_Form(pokedexSortData, SPECIES_ROTOM, formIndex);

        PokedexGraphics_LoadPokemonSprite(pokedexGraphicData, SPECIES_ROTOM, GENDER_FEMALE, face, FALSE, form, 0, x, y, spriteIndex);
    } else {
        form = -1;
    }

    return form;
}

String *PokedexMain_GetMessage(int entryID, enum HeapID heapID)
{
    MessageLoader *pokedexMessageBank = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_POKEDEX, heapID);

    String *pokedexMessage = MessageLoader_GetNewString(pokedexMessageBank, entryID);
    MessageLoader_Free(pokedexMessageBank);

    return pokedexMessage;
}

static void FreePokedexApp(PokedexApp *pokedexApp)
{
    int i;

    PokedexScreenState_Free(&pokedexApp->baseScreenState);

    GF_ASSERT(pokedexApp->screenStateSet1);
    Heap_Free(pokedexApp->screenStateSet1);

    GF_ASSERT(pokedexApp->screenStateSet2);
    Heap_Free(pokedexApp->screenStateSet2);

    GF_ASSERT(pokedexApp->screenStateSet3);
    Heap_Free(pokedexApp->screenStateSet3);

    GF_ASSERT(pokedexApp->screenStateSet4);
    Heap_Free(pokedexApp->screenStateSet4);

    GF_ASSERT(pokedexApp->updater1);
    Heap_Free(pokedexApp->updater1);

    GF_ASSERT(pokedexApp->updater2);
    Heap_Free(pokedexApp->updater2);

    GF_ASSERT(pokedexApp->updater3);
    Heap_Free(pokedexApp->updater3);

    GF_ASSERT(pokedexApp->updater4);
    Heap_Free(pokedexApp->updater4);

    for (i = 0; i < 10; i++) {
        if (sScreenExitFunctions[i]) {
            sScreenExitFunctions[i](&pokedexApp->screenManagers[i]);
        }
    }

    for (i = 0; i < 8; i++) {
        if (sSubScreenExitFunctions[i]) {
            sSubScreenExitFunctions[i](&pokedexApp->subScreenManagers[i]);
        }
    }

    PokedexMemory_SetCurrentSpecies(pokedexApp->pokedexMemory, PokedexSort_GetCurrentSpecies(&pokedexApp->sortData));

    if (PokedexSort_CanSetNationalDex(&pokedexApp->sortData, 1) == 1) {
        PokedexMemory_SetBootMode(pokedexApp->pokedexMemory, PokedexSort_GetBootMode(&pokedexApp->sortData));
    } else {
        PokedexMemory_SetBootMode(pokedexApp->pokedexMemory, POKEDEX_BOOT_DEFAULT);
    }

    PokedexSort_PokedexStatusFreeHWData(&pokedexApp->sortData);
    PokedexGraphics_Free(&pokedexApp->graphicData);
    Heap_Free(pokedexApp);
}

static void SetGXBanks(void)
{
    GXBanks banks = {
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

    GXLayers_SetBanks(&banks);
}

static void InitG2(enum HeapID heapID)
{
    NNS_G2dInitOamManagerModule();
    RenderOam_Init(0, 128, 0, 32, 0, 128, 0, 32, heapID);

    {
        CharTransferTemplate charTransferTemplate = {
            32,
            0x14000,
            0x4000,
        };

        charTransferTemplate.heapID = heapID;
        CharTransfer_InitWithVramModes(&charTransferTemplate, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_32K);
    }

    PlttTransfer_Init(32, heapID);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
}

static void PokedexMain_InitScreenStateSet(PokedexApp *pokedexApp)
{
    PokedexScreenStateSet_SetStates(pokedexApp->screenStateSet1, &pokedexApp->baseScreenState, 1);
    pokedexApp->transitionRequest1 = 1;
}

static void InitG3(void)
{
    NNS_G3dInit();

    G3X_InitMtxStack();
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(1);
    G3X_AlphaTest(0, 0);
    G3X_AlphaBlend(1);
    G3X_SetClearColor(GX_RGB(0, 0, 0), 0, 0x7fff, 63, 0);
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);
    G3_ViewPort(0, 0, 255, 191);

    NNS_GfdInitFrmTexVramManager(1, 1);
    NNS_GfdInitFrmPlttVramManager(0x4000, 1);
}

static void ResetFrm(void)
{
    NNS_GfdResetFrmTexVramState();
    NNS_GfdResetFrmPlttVramState();
}
