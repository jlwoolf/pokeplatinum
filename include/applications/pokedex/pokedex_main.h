#ifndef POKEPLATINUM_POKEDEX_MAIN_H
#define POKEPLATINUM_POKEDEX_MAIN_H

#include <nnsys.h>

#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/pokedex_graphics.h"
#include "applications/pokedex/pokedex_sort_data.h"
#include "applications/pokedex/pokedex_text_manager.h"
#include "applications/pokedex/pokedex_updater.h"
#include "applications/pokedex/struct_pokedex_screen_state_set_decl.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "bg_window.h"
#include "heap.h"
#include "overlay_manager.h"
#include "pokedex.h"
#include "pokedex_memory.h"
#include "sprite.h"
#include "string_gf.h"
#include "touch_screen.h"
#include "trainer_info.h"

typedef struct PokedexLoadingScreen {
    BgConfig *bgConfig;
    NNSG2dScreenData *screenData;
    int layer;
    int topStart;
    int bottomStart;
    int topDist;
    int bottomDist;
    int counter;
    int duration;
} PokedexLoadingScreen;

typedef struct {
    const Pokedex *pokedex;
    const TrainerInfo *trainerInfo;
    int timeOfDay;
    BOOL fullmoonIslandVisible;
    BOOL newmoonIslandVisible;
    BOOL springPathVisible;
    BOOL seabreakPathVisible;
    PokedexMemory *pokedexMemory;
} PokedexOverlayArgs;

int PokedexMain_Init(ApplicationManager *appMan, int *state);
int PokedexMain_Main(ApplicationManager *appMan, int *state);
int PokedexMain_Exit(ApplicationManager *appMan, int *state);
PokedexApp *PokedexMain_NewPokedexApp(enum HeapID heapID, const PokedexOverlayArgs *pokedexOverlayArgs);
BOOL PokedexMain_Update(PokedexApp *pokedexApp);
void PokedexMain_InitGX(enum HeapID heapID);
void PokedexMain_FreeGraphics(void);
void PokedexMain_UpdateSprites(PokedexApp *pokedexApp);
PokedexUpdater *PokedexMain_GetUpdater1(PokedexApp *pokedexApp);
PokedexUpdater *PokedexMain_GetUpdater2(PokedexApp *pokedexApp);
PokedexUpdater *PokedexMain_GetUpdater3(PokedexApp *pokedexApp);
PokedexUpdater *PokedexMain_GetUpdater4(PokedexApp *pokedexApp);
PokedexScreenStateSet *PokedexMain_GetScreenStateSet1(PokedexApp *pokedexApp);
PokedexScreenStateSet *PokedexMain_GetScreenStateSet2(PokedexApp *pokedexApp);
PokedexScreenStateSet *PokedexMain_GetScreenStateSet3(PokedexApp *pokedexApp);
PokedexScreenStateSet *PokedexMain_GetScreenStateSet4(PokedexApp *pokedexApp);
int *PokedexMain_GetTransitionRequest1(PokedexApp *pokedexApp);
int *PokedexMain_GetTransitionRequest2(PokedexApp *pokedexApp);
int *PokedexMain_GetTransitionRequest3(PokedexApp *pokedexApp);
int *PokedexMain_GetTransitionRequest4(PokedexApp *pokedexApp);
BOOL *PokedexMain_GetExitFlag(PokedexApp *pokedexApp);
PokedexSortData *PokedexMain_GetSortData(PokedexApp *pokedexApp);
PokedexGraphicData *PokedexMain_GetGraphicData(PokedexApp *pokedexApp);
PokedexScreenManager *PokedexMain_GetScreenManager(PokedexApp *pokedexApp, int param1);
PokedexScreenManager *PokedexMain_GetSubScreenManager(PokedexApp *pokedexApp, int param1);
void PokedexMain_SetCursorAnimFrame(Sprite *param0, int param1);
void PokedexMain_SetButtonY(Sprite *param0, PokedexTextData *textData, int setY);
void PokedexMain_SetTextSprite(Sprite *param0, PokedexTextData *textData, int param2, int param3, int param4);
void PokedexMain_SetHitTableRect(TouchScreenHitTable *hitTable, int top, int bottom, int left, int right);
void PokedexMain_SetLoadingScreenParams(PokedexLoadingScreen *pokedexLoadingScreen, BgConfig *bgConfig, int layer, NNSG2dScreenData *screenData, int topStart, int topEnd, int bottomStart, int bottomEnd, int duration);
BOOL PokedexMain_LoadingScreenMove(PokedexLoadingScreen *pokedexLoadingScreen);
void PokedexMain_DisplayNameNumberText(Window *window, int dexNumber, int species, enum HeapID heapID);
Window *PokedexMain_DisplayNameNumber(PokedexGraphicData *pokedexgraphicData, const PokedexSortData *pokedexSortData, enum HeapID heapID, int species);
Window *PokedexMain_DisplayNameNumberNational(PokedexTextManager *textMan, enum HeapID heapID, int species);
Window *PokedexMain_DisplayNameNumberLocal(PokedexTextManager *textMan, enum HeapID heapID, int species);
void PokedexMain_EntryNameNumber(PokedexGraphicData *param0, const PokedexSortData *pokedexSortData, enum HeapID heapID, int statusIndex, fx32 x, fx32 y);
void PokedexMain_SetSpeciesLabelPos(PokedexGraphicData *pokedexGraphicData, int param1, int param2);
void PokedexMain_SetSpeciesLabelXY(PokedexSpeciesLabel *param0, int param1, int param2);
void PokedexMain_DisplayPokemonSprite(PokedexGraphicData *pokedexGraphicData, PokedexSortData *pokedexSortData, int species, int face, int x, int y);
u32 PokedexMain_DisplaySpeciesSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int species, int face, int x, int y, int formIndex, int spriteIndex);
u32 PokedexMain_DisplayUnownSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex);
u32 PokedexMain_DisplayShellosSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex);
u32 PokedexMain_DisplayGastrodonSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex);
u32 PokedexMain_DisplayBurmySprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex);
u32 PokedexMain_DisplayWormadamSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex);
u32 PokedexMain_DisplayDeoxysSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex);
u32 PokedexMain_DisplayShayminSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex);
u32 PokedexMain_DisplayGiratinaSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex);
u32 PokedexMain_DisplayRotomSprite(PokedexGraphicData *pokedexGraphicData, const PokedexSortData *pokedexSortData, int face, int x, int y, int formIndex, int spriteIndex);
String *PokedexMain_GetMessage(int entryID, enum HeapID heapID);

#endif // POKEPLATINUM_POKEDEX_MAIN_H
