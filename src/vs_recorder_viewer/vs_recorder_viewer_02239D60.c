#include "vs_recorder_viewer/vs_recorder_viewer_02239D60.h"

#include <nitro.h>
#include <string.h>

#include "constants/narc.h"
#include "constants/species.h"

#include "struct_defs/struct_02030A80.h"
#include "struct_defs/struct_vs_recorder_state.h"

#include "global_terminal/global_terminal_0222AE60.h"
#include "global_terminal/global_terminal_0222B008.h"
#include "global_terminal/global_terminal_0222BC4C.h"
#include "global_terminal/struct_global_terminal_0222BCF8_sub1_sub1.h"
#include "vs_recorder_viewer/vs_recorder_viewer.h"
#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_0224112C.h"
#include "vs_recorder_viewer/vs_recorder_viewer_const_funcptr_tables.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022312B0.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022323B8.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02239DA4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223CAA4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02248CDC.h"
#include "savedata/save_table.h"

#include "bg_window.h"
#include "font.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "palette.h"
#include "pc_boxes.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "pokemon_sprite.h"
#include "savedata.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "string_template.h"
#include "text.h"
#include "touch_screen.h"
#include "touch_screen_actions.h"
#include "font_oam.h"
#include "player_profile.h"
#include "vs_recorder_ring.h"

typedef struct {
    int unk_00;
    PlayerProfile *unk_04;
    int unk_08;
} VsRecorderViewerProfileBoxSelection;

typedef struct {
    PCBoxes *pcBoxes;
    VsRecorderViewerBoxData unk_04;
    int unk_1A0;
    int unk_1A4;
    int unk_1A8;
    int unk_1AC;
    int unk_1B0;
    Window unk_1B4[8];
    Window unk_234[8];
    ManagedSprite *unk_2B4[30];
    PokemonSprite *unk_32C;
    TouchScreenActions *unk_330[5];
    TouchScreenActions *unk_344;
    VsRecorderViewerTextSprite unk_348[2];
    VsRecorderViewerProfileBoxSelection unk_380;
    GlobalTerminalProfileBox *unk_38C[20];
    GlobalTerminalProfileBox unk_3DC[20];
    String *unk_2E0C[20][2];
    VsRecorderViewerListConfig unk_2EAC;
    VsRecorderViewerProfilePanel unk_2ED8;
    int unk_2F64;
    int unk_2F68;
    int unk_2F6C;
} VsRecorderViewerBoxContext;

static void VsRecorderViewerBox_LoadProfileFromBox(VsRecorderState *param0, int param1);
static void VsRecorderViewerBox_FreeLoadedProfile(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_HasAnyPokemon(VsRecorderViewerBoxData *param0);
static void VsRecorderViewerBox_AdvanceToOccupiedSlot(VsRecorderViewerBoxContext *param0);
static void VsRecorderViewerBox_HandleBoxNavInput(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerBox_HandleProfileBoxInput(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerBox_HandleBoxUploadInput(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerBox_HandleProfileBoxMenuInput(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerBox_HandleGridCursorInput(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerBox_CreateHeaderSprites(VsRecorderState *param0);
static void VsRecorderViewerBox_FreeHeaderSprites(VsRecorderState *param0);
static void VsRecorderViewerBox_SetCursorToFirstOccupiedSlot(VsRecorderViewerBoxContext *param0);
static BOOL VsRecorderViewerBox_Init(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_EnterFadeIn(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_OpenProfileBoxView(VsRecorderState *param0);
static void VsRecorderViewerBox_SetHeaderLayout(VsRecorderState *param0, int param1);
static BOOL VsRecorderViewerBox_SetupProfileBoxUpload(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_UpdateProfileBoxUploadInput(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_UploadProfileBox(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_CloseProfileBoxUpload(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_FinishProfileBoxUpload(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_FinishBoxUpload(VsRecorderState *param0);
static void VsRecorderViewerBox_CreateStatusWindows(VsRecorderState *param0);
static void VsRecorderViewerBox_CreateListWindows(VsRecorderState *param0);
static void VsRecorderViewerBox_RemoveListWindows(VsRecorderState *param0);
static void VsRecorderViewerBox_RemoveStatusWindows(VsRecorderState *param0);
static void VsRecorderViewerBox_PrintStatusMessage(VsRecorderState *param0, int param1);
static void VsRecorderViewerBox_PrintTrainerNameMessage(VsRecorderState *param0, int param1);
static void VsRecorderViewerBox_PrintBoxName(VsRecorderState *param0);
static void VsRecorderViewerBox_ClearNameWindows(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_IsBitSet(int param0, int param1);
static void VsRecorderViewerBox_PrintSpeciesName(VsRecorderState *param0, int param1);
static void VsRecorderViewerBox_CreatePokemonIcons(VsRecorderState *param0);
static void VsRecorderViewerBox_SetPokemonIconsVisible(VsRecorderState *param0, int param1);
static void VsRecorderViewerBox_DestroyPokemonIcons(VsRecorderState *param0);
static void VsRecorderViewerBox_CreatePreviewPokemonSprite(VsRecorderState *param0);
static void VsRecorderViewerBox_SetPreviewSpriteVisible(VsRecorderState *param0, int param1);
static void VsRecorderViewerBox_DeletePreviewSprite(VsRecorderState *param0);
static void VsRecorderViewerBox_LoadWallpaperAndRefresh(VsRecorderState *param0);
static void VsRecorderViewerBox_LoadWallpaper(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_SetupBoxView(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_UpdateBoxNavInput(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_Exit(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_SetupBoxListView(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_UpdateBoxListInput(VsRecorderState *param0);
static void VsRecorderViewerBox_CreateProfileBoxWindows(VsRecorderState *param0);
static void VsRecorderViewerBox_PrintProfileBoxMessage(VsRecorderState *param0, int param1);
static void VsRecorderViewerBox_CreateTitleWindow(VsRecorderState *param0);
static void VsRecorderViewerBox_RemoveTitleWindow(VsRecorderState *param0);
static void VsRecorderViewerBox_RemoveTwoWindows(VsRecorderState *param0);
static void VsRecorderViewerBox_CreateProfileBoxStatusWindow(VsRecorderState *param0);
static void VsRecorderViewerBox_RemoveProfileBoxStatusWindow(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_UploadBox(VsRecorderState *param0);
static void VsRecorderViewerBox_InitProfileBoxStrings(VsRecorderState *param0);
static void VsRecorderViewerBox_FreeProfileBoxStrings(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_UpdateProfileBoxGridInput(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_CloseProfileBoxGrid(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_SelectProfileBox(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_UpdateGridInput(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_OpenProfileBoxGrid(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_OpenProfileBoxDetail(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_CloseProfileBoxDetail(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_ExitBoxList(VsRecorderState *param0);
void VsRecorderViewerBox_OnProfileBoxTransferComplete(void *param0, const VsRecorderViewerTransferStatus *param1);
void VsRecorderViewerBox_OnBoxTransferComplete(void *param0, const VsRecorderViewerTransferStatus *param1);
static BOOL VsRecorderViewerBox_SetupBoxView(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_UpdateBoxNavInput(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_Exit(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_SetupBoxListView(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_UpdateBoxListInput(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_ExitBoxList(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_UploadBox(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_UpdateProfileBoxGridInput(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_CloseProfileBoxGrid(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_OpenProfileBoxDetail(VsRecorderState *param0);
static BOOL VsRecorderViewerBox_CloseProfileBoxDetail(VsRecorderState *param0);

static void VsRecorderViewerBox_LoadProfileFromBox(VsRecorderState *param0, int param1)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    v0->unk_2ED8.profile = PlayerProfile_New(HEAP_ID_102);
    GlobalTerminal_DeserializePlayerProfile(&v0->unk_38C[param1]->profile, v0->unk_2ED8.profile);
}

static void VsRecorderViewerBox_FreeLoadedProfile(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    PlayerProfile_Free(v0->unk_2ED8.profile);
}

static BOOL VsRecorderViewerBox_HasAnyPokemon(VsRecorderViewerBoxData *param0)
{
    int v0;
    int v1;

    for (v0 = 0; v0 < 30; v0++) {
        v1 = param0->species[v0];

        if (v1 != 0) {
            return 1;
        }
    }

    return 0;
}

static void VsRecorderViewerBox_AdvanceToOccupiedSlot(VsRecorderViewerBoxContext *param0)
{
    int v0;

    for (v0 = param0->unk_1B0; v0 < 30; v0++) {
        if (param0->unk_04.species[v0] != 0) {
            param0->unk_1B0 = v0;
            return;
        }
    }

    for (v0 = 0; v0 < param0->unk_1B0; v0++) {
        if (param0->unk_04.species[v0] != 0) {
            param0->unk_1B0 = v0;
            return;
        }
    }
}

static const TouchScreenRect sVsRecorderViewerBoxNavTouchRects[] = {
    { 0x20, 0x40, 0x18, 0x48 },
    { 0x20, 0x40, 0xB8, 0xE0 },
    { 0x98, 0xB8, 0x20, 0x80 },
    { 0x98, 0xB8, 0x80, 0xE0 }
};

static const TouchScreenRect sVsRecorderViewerBoxListTouchRects[] = {
    { 0x18, 0x28, 0x18, 0x68 },
    { 0x18, 0x28, 0x90, 0xD0 },
    { 0x40, 0x50, 0x18, 0x68 },
    { 0x40, 0x50, 0x90, 0xD0 },
    { 0x68, 0x78, 0x18, 0x68 },
    { 0x68, 0x78, 0x90, 0xD0 },
    { 0x98, 0xB8, 0x50, 0xB0 }
};

static const TouchScreenRect sVsRecorderViewerProfileBoxMenuTouchRects[] = {
    { 0x10, 0x30, 0x58, 0xA8 },
    { 0x40, 0x70, 0x58, 0xA8 },
    { 0x98, 0xB8, 0x50, 0xB0 }
};

static const TouchScreenRect sVsRecorderViewerGridTouchRects[] = {
    { 0x20, 0x60, 0x48, 0xB8 },
    { 0x98, 0xB8, 0x50, 0xB0 }
};

static void VsRecorderViewerBox_HandleBoxNavInput(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerBoxContext *v1 = v0->unk_860;

    switch (param0) {
    case 0:
        if (param1 != TOUCH_BUTTON_HELD) {
            return;
        }

        VsRecorderViewerList_PlayRingAnim(v0);

        if (v1->unk_1A0 > 0) {
            v1->unk_1A0--;
        } else {
            v1->unk_1A0 = 18 - 1;
        }

        VsRecorderViewerMain_SetState(v0, 4);
        break;
    case 1:
        if (param1 != TOUCH_BUTTON_HELD) {
            return;
        }

        VsRecorderViewerList_PlayRingAnim(v0);
        v1->unk_1A0++;
        v1->unk_1A0 %= 18;
        VsRecorderViewerMain_SetState(v0, 4);
        break;
    case 2:
        if (param1 != TOUCH_BUTTON_PRESSED) {
            return;
        }

        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 9);
        break;
    case 3:
        if (param1 != TOUCH_BUTTON_PRESSED) {
            return;
        }

        VsRecorderViewerList_PlayRingAnim(v0);

        if (VsRecorderViewerBox_HasAnyPokemon(&v1->unk_04)) {
            VsRecorderViewerMain_SetState(v0, 5);
        } else {
            VsRecorderViewerBox_PrintStatusMessage(v0, 271);
        }
        break;
    }
}

static void VsRecorderViewerBox_HandleProfileBoxInput(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerBoxContext *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    default:
        VsRecorderViewerList_PlayRingAnim(v0);
        v1->unk_380.unk_00 = param0;
        VsRecorderViewerMain_SetState(v0, 8);
        break;
    case 6:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 7);
        break;
    }
}

static void VsRecorderViewerBox_HandleBoxUploadInput(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerBoxContext *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    default:
        VsRecorderViewerList_PlayRingAnim(v0);
        v1->unk_380.unk_00 = param0;
        VsRecorderViewerMain_SetState(v0, 4);
        break;
    case 6:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 12);
        break;
    }
}

static void VsRecorderViewerBox_HandleProfileBoxMenuInput(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerBoxContext *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    default:
    case 0:
        VsRecorderViewerList_PlayRingAnim(v0);
        if (v1->unk_2F64 == 0) {
            VsRecorderViewerMain_SetState(v0, 7);
        } else {
            VsRecorderViewerMain_SetState(v0, 8);
        }
        break;
    case 1:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 9);
        break;
    case 2:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 6);
        break;
    }
}

static void VsRecorderViewerBox_HandleGridCursorInput(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerBoxContext *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
        VsRecorderViewerList_PlayRingAnim(v0);

        v1->unk_1B0++;
        v1->unk_1B0 %= 30;

        VsRecorderViewerBox_AdvanceToOccupiedSlot(v1);

        v1->unk_2F68 = v1->unk_1B0 % 6;
        v1->unk_2F6C = v1->unk_1B0 / 6;

        VsRecorderRing_SetTargetPosition(v0->unk_6F0, 110 + (v1->unk_2F68 * 24), 52 + (v1->unk_2F6C * 22));

        VsRecorderViewerList_SetDrawSuspended(v0, 1);
        VsRecorderViewerBox_DeletePreviewSprite(v0);
        VsRecorderViewerBox_CreatePreviewPokemonSprite(v0);
        VsRecorderViewerList_SetDrawSuspended(v0, 0);
        VsRecorderViewerBox_PrintSpeciesName(v0, v1->unk_1B0);

        if ((v1->unk_04.species[v1->unk_1B0] != 0) && (VsRecorderViewerBox_IsBitSet(v1->unk_04.eggFlags, (1 << v1->unk_1B0)) != 1)) {
            Sound_PlayPokemonCry(v1->unk_04.species[v1->unk_1B0], v1->unk_04.form[v1->unk_1B0]);
        }
        break;
    case 1:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderRing_SetVisible(v0->unk_6F0, 0);
        VsRecorderRing_SetOrbitRadii(v0->unk_6F0, 0, 0);
        VsRecorderViewerMain_SetState(v0, 11);
        break;
    }
}

static void VsRecorderViewerBox_CreateHeaderSprites(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    VsRecorderViewerMenu_LoadCursorSpriteResources(param0, NNS_G2D_VRAM_TYPE_2DSUB);
    VsRecorderViewerList_InitSpriteWithFont(param0, &v0->unk_348[0], NNS_G2D_VRAM_TYPE_2DSUB, 3, 32, 232, 36, -8, 0, 1);
    VsRecorderViewerList_InitSpriteWithFont(param0, &v0->unk_348[1], NNS_G2D_VRAM_TYPE_2DSUB, 53, 128, 232, 36, -8, 1, 1);
}

static void VsRecorderViewerBox_FreeHeaderSprites(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    VsRecorderViewerList_FreeSpriteWithFont(&v0->unk_348[0]);
    VsRecorderViewerList_FreeSpriteWithFont(&v0->unk_348[1]);
    VsRecorderViewerMenu_FreeCursorSpriteResources(param0);
}

static void VsRecorderViewerBox_SetCursorToFirstOccupiedSlot(VsRecorderViewerBoxContext *param0)
{
    int v0;

    for (v0 = 0; v0 < 30; v0++) {
        if (param0->unk_04.species[v0] != 0) {
            param0->unk_1B0 = v0;
            break;
        }
    }
}

static void VsRecorderViewerBox_SerializeBoxData(SaveData *saveData, const PCBoxes *pcBoxes, int boxID, VsRecorderViewerBoxData *param3)
{
    memset(param3, 0, sizeof(VsRecorderViewerBoxData));
    GlobalTerminal_SerializePCBox(saveData, pcBoxes, boxID, param3, HEAP_ID_102);
}

static BOOL VsRecorderViewerBox_Init(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerBoxContext));

    memset(v0, 0, sizeof(VsRecorderViewerBoxContext));

    param0->unk_860 = v0;

    Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
    Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
    Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
    Bg_ClearTilemap(param0->unk_14.bgConfig, 7);

    v0->pcBoxes = SaveData_GetPCBoxes(param0->saveData);
    VsRecorderViewerBox_SerializeBoxData(param0->saveData, v0->pcBoxes, v0->unk_1A0, &v0->unk_04);
    VsRecorderViewerBox_SetCursorToFirstOccupiedSlot(v0);
    VsRecorderViewerMenu_SetDefaultBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0);

    v0->unk_330[0] = TouchScreenActions_RegisterHandler(sVsRecorderViewerBoxNavTouchRects, NELEMS(sVsRecorderViewerBoxNavTouchRects), VsRecorderViewerBox_HandleBoxNavInput, param0, HEAP_ID_102);
    v0->unk_330[1] = TouchScreenActions_RegisterHandler(sVsRecorderViewerBoxListTouchRects, NELEMS(sVsRecorderViewerBoxListTouchRects), VsRecorderViewerBox_HandleProfileBoxInput, param0, HEAP_ID_102);
    v0->unk_330[2] = TouchScreenActions_RegisterHandler(sVsRecorderViewerBoxListTouchRects, NELEMS(sVsRecorderViewerBoxListTouchRects), VsRecorderViewerBox_HandleBoxUploadInput, param0, HEAP_ID_102);
    v0->unk_330[3] = TouchScreenActions_RegisterHandler(sVsRecorderViewerProfileBoxMenuTouchRects, NELEMS(sVsRecorderViewerProfileBoxMenuTouchRects), VsRecorderViewerBox_HandleProfileBoxMenuInput, param0, HEAP_ID_102);
    v0->unk_330[4] = TouchScreenActions_RegisterHandler(sVsRecorderViewerGridTouchRects, NELEMS(sVsRecorderViewerGridTouchRects), VsRecorderViewerBox_HandleGridCursorInput, param0, HEAP_ID_102);
    v0->unk_380.unk_04 = PlayerProfile_New(HEAP_ID_102);

    PlayerProfile_Init(v0->unk_380.unk_04, param0->saveData);
    VsRecorderViewerMain_SetState(param0, 1);

    return 0;
}

static BOOL VsRecorderViewerBox_EnterFadeIn(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 1)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    case 1:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_HideAndFreeMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_StartNetworkTask(param0, 0);
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        param0->unk_08++;
        break;
    case 2:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerBox_CreateHeaderSprites(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_SetBgPriorities();
        param0->unk_08++;
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 2);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_OpenProfileBoxView(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerMenu_UpdateBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), 1);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerBox_DeletePreviewSprite(param0);
        VsRecorderViewerBox_DestroyPokemonIcons(param0);
        VsRecorderViewerBox_ClearNameWindows(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->unk_08++;

    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 1)) {
            VsRecorderViewerBox_SerializeBoxData(param0->saveData, v0->pcBoxes, v0->unk_1A0, &v0->unk_04);
            VsRecorderViewerBox_SetCursorToFirstOccupiedSlot(v0);
            param0->unk_08++;
        }
        break;

    case 2: {
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerBox_LoadWallpaper(param0);
        VsRecorderViewerBox_SetPreviewSpriteVisible(param0, 1);
        VsRecorderViewerBox_SetPokemonIconsVisible(param0, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->unk_08++;
    } break;

    case 3:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0, 1)) {
            VsRecorderViewerBox_PrintSpeciesName(param0, v0->unk_1B0);
            VsRecorderViewerBox_PrintBoxName(param0);
            VsRecorderViewerBox_PrintStatusMessage(param0, 270);
            VsRecorderViewerBox_SetPreviewSpriteVisible(param0, 0);
            VsRecorderViewerBox_SetPokemonIconsVisible(param0, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
            G2_BlendNone();
            VsRecorderViewerMain_SetState(param0, 3);
        }
        break;

    default:
        break;
    }

    return 0;
}

static void VsRecorderViewerBox_SetHeaderLayout(VsRecorderState *param0, int param1)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    if (param1 == 0) {
        ManagedSprite_SetDrawFlag(v0->unk_348[1].sprite, 1);
        FontOAM_SetDrawFlag(v0->unk_348[1].fontOAM, 1);
        ManagedSprite_SetPositionXY(v0->unk_348[0].sprite, 32, 232);
    } else {
        ManagedSprite_SetDrawFlag(v0->unk_348[1].sprite, 0);
        FontOAM_SetDrawFlag(v0->unk_348[1].fontOAM, 0);
        ManagedSprite_SetPositionXY(v0->unk_348[0].sprite, 80, 232);
    }

    FontOAM_SetXY(v0->unk_348[0].fontOAM, 36, -8);
    FontOAM_SetXY(v0->unk_348[1].fontOAM, 36, -8);
}

static BOOL VsRecorderViewerBox_SetupProfileBoxUpload(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderRing_SetVisible(param0->unk_6F4, 0);
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 2)) {
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 79, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
            VsRecorderViewerBox_CreateListWindows(param0);
            VsRecorderViewerBox_SetHeaderLayout(param0, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 0);
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0, 2)) {
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            VsRecorderViewerMain_SetState(param0, 6);
            VsRecorderViewerBox_PrintStatusMessage(param0, 272);
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    default:
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_UpdateProfileBoxUploadInput(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    TouchScreenActions_HandleAction(v0->unk_330[1]);

    return 0;
}

static BOOL VsRecorderViewerBox_UploadProfileBox(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    VsRecorderViewerTransferStatus *v1;

    if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerBox_RemoveListWindows(param0);
        VsRecorderRing_SetVisible(param0->unk_6F4, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
    case 1:
        VsRecorderViewerMenu_UpdateBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), 1);
        VsRecorderViewerBox_DeletePreviewSprite(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerBox_DestroyPokemonIcons(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerBox_ClearNameWindows(param0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 2:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 0)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    case 3:
        param0->unk_08++;
    case 4:
        VsRecorderViewerList_SetupRing(param0, param0->unk_6F0, 128, 96);
        VsRecorderRing_SetVisible(param0->unk_6F0, 1);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 24, 24);
        VsRecorderViewerList_OpenMainMessage(param0, 288);
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->unk_08++;
        break;
    case 5:
        if (GlobalTerminalTransfer_UploadProfileBox(VsRecorderViewerTransfer_GetTransfer(param0), v0->unk_380.unk_00, v0->unk_380.unk_04, v0->pcBoxes, v0->unk_1A0) == 1) {
            param0->unk_08++;
        }
        break;
    case 6:
        VsRecorderViewerList_CloseMainMessage(param0);

        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_OpenMessage(param0, 2, v1->index, v1->category);
            param0->unk_08++;
        } else {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_IncrementTrainerScore(param0, 48);
            VsRecorderViewerList_SetRecordTransferDone(param0, 1);
            Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);
            param0->unk_08++;
        }
        break;
    case 7:
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);
        param0->unk_08++;
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 10);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_CloseProfileBoxUpload(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderRing_SetVisible(param0->unk_6F4, 0);
        VsRecorderViewerBox_RemoveListWindows(param0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 2)) {
            VsRecorderViewerBox_SetHeaderLayout(param0, 0);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 77, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    case 2:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0, 2)) {
            VsRecorderViewerBox_PrintStatusMessage(param0, 270);
            VsRecorderViewerMain_SetState(param0, 3);
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    default:
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_FinishProfileBoxUpload(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerMenu_UpdateBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), 1);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerBox_DeletePreviewSprite(param0);
        VsRecorderViewerBox_DestroyPokemonIcons(param0);
        VsRecorderViewerBox_ClearNameWindows(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 0)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    case 2: {
        VsRecorderViewerMain_SetState(param0, 10);
    } break;
    default:
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_FinishBoxUpload(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerBox_RemoveListWindows(param0);
        VsRecorderViewerMenu_UpdateBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 0)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    case 2: {
        VsRecorderViewerMain_SetState(param0, 13);
    } break;
    default:
        break;
    }

    return 0;
}

// clang-format off
BOOL(*const sVsRecorderViewerBoxStateTable[])(VsRecorderState *) = {
    VsRecorderViewerBox_Init,
    VsRecorderViewerBox_EnterFadeIn,
    VsRecorderViewerBox_SetupBoxView,
    VsRecorderViewerBox_UpdateBoxNavInput,
    VsRecorderViewerBox_OpenProfileBoxView,
    VsRecorderViewerBox_SetupProfileBoxUpload,
    VsRecorderViewerBox_UpdateProfileBoxUploadInput,
    VsRecorderViewerBox_CloseProfileBoxUpload,
    VsRecorderViewerBox_UploadProfileBox,
    VsRecorderViewerBox_FinishProfileBoxUpload,
    VsRecorderViewerBox_Exit,
};
// clang-format on

// clang-format off
BOOL(*const sVsRecorderViewerBoxListStateTable[])(VsRecorderState *) = {
    VsRecorderViewerBox_Init,
    VsRecorderViewerBox_EnterFadeIn,
    VsRecorderViewerBox_SetupBoxListView,
    VsRecorderViewerBox_UpdateBoxListInput,
    VsRecorderViewerBox_UploadBox,
    VsRecorderViewerBox_UpdateProfileBoxGridInput,
    VsRecorderViewerBox_CloseProfileBoxGrid,
    VsRecorderViewerBox_OpenProfileBoxDetail,
    VsRecorderViewerBox_CloseProfileBoxDetail,
    VsRecorderViewerBox_SelectProfileBox,
    VsRecorderViewerBox_UpdateGridInput,
    VsRecorderViewerBox_OpenProfileBoxGrid,
    VsRecorderViewerBox_FinishBoxUpload,
    VsRecorderViewerBox_ExitBoxList,
};
// clang-format on

static const u8 sVsRecorderViewerStatusWindowRects[][4] = {
    { 0x1, 0x2, 0x9, 0x3 },
    { 0xF, 0x1, 0xD, 0x3 },
    { 0x1, 0x15, 0x1E, 0x2 }
};

static const TextColor sVsRecorderViewerStatusTextColors[] = {
    TEXT_COLOR(15, 13, 0),
    TEXT_COLOR(15, 1, 0),
    TEXT_COLOR(15, 13, 0),
};

static const u32 sVsRecorderViewerStatusTextYOffsets[] = {
    0x6,
    0x4,
    0x0
};

static const u32 sVsRecorderViewerWindowFillValues[] = {
    0x0,
    0x0,
    0xCC
};

static void VsRecorderViewerBox_CreateStatusWindows(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    Window *v1;
    int v2 = 256 + 1;
    int v3;

    for (v3 = 0; v3 < 3; v3++) {
        v1 = &v0->unk_1B4[v3];

        Window_Init(v1);
        Window_Add(param0->unk_14.bgConfig, v1, 2, sVsRecorderViewerStatusWindowRects[v3][0], sVsRecorderViewerStatusWindowRects[v3][1], sVsRecorderViewerStatusWindowRects[v3][2], sVsRecorderViewerStatusWindowRects[v3][3], 14, v2);
        Window_FillTilemap(v1, sVsRecorderViewerWindowFillValues[v3]);
        Window_ScheduleCopyToVRAM(v1);

        v2 += (sVsRecorderViewerStatusWindowRects[v3][2] * sVsRecorderViewerStatusWindowRects[v3][3]);
    }
}

static const u8 sVsRecorderViewerListWindowRects[][4] = {
    { 0x3, 0x3, 0xB, 0x2 },
    { 0x12, 0x3, 0xB, 0x2 },
    { 0x3, 0x8, 0xB, 0x2 },
    { 0x12, 0x8, 0xB, 0x2 },
    { 0x3, 0xD, 0xB, 0x2 },
    { 0x12, 0xD, 0xB, 0x2 }
};

static void VsRecorderViewerBox_CreateListWindows(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    Window *v1;
    int v2 = 1;
    int v3;
    int v4;
    String *v5;

    for (v3 = 0; v3 < NELEMS(sVsRecorderViewerListWindowRects); v3++) {
        v1 = &v0->unk_234[v3];
        Window_Init(v1);
        Window_Add(param0->unk_14.bgConfig, v1, 6, sVsRecorderViewerListWindowRects[v3][0], sVsRecorderViewerListWindowRects[v3][1], sVsRecorderViewerListWindowRects[v3][2], sVsRecorderViewerListWindowRects[v3][3], 14, v2);

        v5 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 60 + v3);
        v4 = VsRecorderViewerList_CalcCenteredTextX(v1, v5);

        Window_FillTilemap(v1, sVsRecorderViewerWindowFillValues[0]);
        Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v5, v4, 0, TEXT_SPEED_NO_TRANSFER, sVsRecorderViewerStatusTextColors[0], NULL);
        Window_ScheduleCopyToVRAM(v1);
        String_Free(v5);

        v2 += (sVsRecorderViewerListWindowRects[v3][2] * sVsRecorderViewerListWindowRects[v3][3]);
    }
}

static void VsRecorderViewerBox_RemoveListWindows(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    Window *v1;
    int v2;

    for (v2 = 0; v2 < NELEMS(sVsRecorderViewerListWindowRects); v2++) {
        v1 = &v0->unk_234[v2];

        Window_ClearAndCopyToVRAM(v1);
        Window_Remove(v1);
    }
}

static void VsRecorderViewerBox_RemoveStatusWindows(VsRecorderState *param0)
{
    int v0;
    VsRecorderViewerBoxContext *v1 = param0->unk_860;

    for (v0 = 0; v0 < 3; v0++) {
        Window_ClearAndCopyToVRAM(&v1->unk_1B4[v0]);
        Window_Remove(&v1->unk_1B4[v0]);
    }
}

static void VsRecorderViewerBox_PrintStatusMessage(VsRecorderState *param0, int param1)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    Window *v1 = &v0->unk_1B4[2];
    String *v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, param1);

    Window_FillTilemap(v1, sVsRecorderViewerWindowFillValues[2]);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, 0, sVsRecorderViewerStatusTextYOffsets[2], TEXT_SPEED_NO_TRANSFER, sVsRecorderViewerStatusTextColors[2], NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v2);
}

static void VsRecorderViewerBox_PrintTrainerNameMessage(VsRecorderState *param0, int param1)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    String *v3;
    String *v4;
    StringTemplate *v5;
    int v6 = 28 + v0->unk_380.unk_00;

    v1 = &v0->unk_1B4[2];
    v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, v6);
    v3 = String_Init(255, HEAP_ID_102);
    v4 = String_Init(255, HEAP_ID_102);
    v5 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);

    String_CopyChars(v3, v0->unk_38C[param0->unk_14.listWindow.scrollState.selection]->profile.name);
    VsRecorderViewerList_CheckNameChars(param0, v3);
    StringTemplate_SetString(v5, 0, v3, 0, 1, GAME_LANGUAGE);
    StringTemplate_Format(v5, v4, v2);
    Window_FillTilemap(v1, sVsRecorderViewerWindowFillValues[2]);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v4, 0, sVsRecorderViewerStatusTextYOffsets[2], TEXT_SPEED_NO_TRANSFER, sVsRecorderViewerStatusTextColors[2], NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v2);
    String_Free(v3);
    String_Free(v4);
    StringTemplate_Free(v5);
}

static void VsRecorderViewerBox_PrintBoxName(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    int v3;

    v1 = &v0->unk_1B4[1];
    v2 = String_Init(255, HEAP_ID_102);

    String_CopyChars(v2, v0->unk_04.boxName);
    Window_FillTilemap(v1, sVsRecorderViewerWindowFillValues[1]);

    v3 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v3, sVsRecorderViewerStatusTextYOffsets[1], TEXT_SPEED_NO_TRANSFER, sVsRecorderViewerStatusTextColors[1], NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v2);
}

static void VsRecorderViewerBox_ClearNameWindows(VsRecorderState *param0)
{
    int v0;
    Window *v1;
    VsRecorderViewerBoxContext *v2 = param0->unk_860;

    for (v0 = 0; v0 < 2; v0++) {
        v1 = &v2->unk_1B4[v0];

        Window_FillTilemap(v1, sVsRecorderViewerWindowFillValues[v0]);
        Window_ScheduleCopyToVRAM(v1);
    }
}

static BOOL VsRecorderViewerBox_IsBitSet(int param0, int param1)
{
    return (param0 & param1) == param1;
}

static void VsRecorderViewerBox_PrintSpeciesName(VsRecorderState *param0, int param1)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    int v3;
    int v4;
    u16 v5[255];

    v1 = &v0->unk_1B4[0];
    Window_FillTilemap(v1, sVsRecorderViewerWindowFillValues[0]);
    v4 = v0->unk_04.species[param1];

    if (v4 == 0) {
        Window_ScheduleCopyToVRAM(v1);
        return;
    }

    v2 = String_Init(255, HEAP_ID_102);

    if (VsRecorderViewerBox_IsBitSet(v0->unk_04.eggFlags, (1 << v0->unk_1B0)) == 1) {
        v4 = SPECIES_EGG;
    }

    MessageLoader_GetSpeciesName(v4, 102, v5);
    String_CopyChars(v2, v5);

    v3 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v3, sVsRecorderViewerStatusTextYOffsets[0], TEXT_SPEED_NO_TRANSFER, sVsRecorderViewerStatusTextColors[0], NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v2);
}

static void VsRecorderViewerBox_CreatePokemonIcons(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    SpriteSystem *v1;
    SpriteManager *v2;
    PaletteData *v3;
    SpriteTemplate v4;

    v1 = param0->unk_14.spriteSystem;
    v2 = param0->unk_14.spriteManager;
    v3 = param0->unk_14.palette;

    SpriteSystem_LoadPaletteBuffer(v3, PLTTBUF_MAIN_OBJ, v1, v2, NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, PokeIconPalettesFileIndex(), FALSE, 3, NNS_G2D_VRAM_TYPE_2DMAIN, 100000);
    SpriteSystem_LoadCellResObj(v1, v2, NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, PokeIcon64KCellsFileIndex(), FALSE, 100000);
    SpriteSystem_LoadAnimResObj(v1, v2, NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, PokeIcon64KAnimationFileIndex(), FALSE, 100000);

    {
        int v5;
        int v6;
        int v7;
        int v8;
        int v9;

        for (v5 = 0; v5 < 30; v5++) {
            v7 = v0->unk_04.species[v5];
            v6 = v0->unk_04.form[v5];
            v9 = VsRecorderViewerBox_IsBitSet(v0->unk_04.eggFlags, (1 << v5));

            if (v7 == 0) {
                continue;
            }

            SpriteSystem_LoadCharResObjAtEndWithHardwareMappingType(v1, v2, NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, PokeIconSpriteIndex(v7, v9, v6), FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 100000 + v5);

            v4.x = 110 + ((v5 % 6) * 24);
            v4.y = 48 + ((v5 / 6) * 22);
            v4.z = 0;
            v4.animIdx = 0;
            v4.priority = 0;
            v4.plttIdx = 0;
            v4.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
            v4.bgPriority = 0;
            v4.vramTransfer = FALSE;
            v4.resources[0] = 100000 + v5;
            v4.resources[1] = 100000;
            v4.resources[2] = 100000;
            v4.resources[3] = 100000;
            v4.resources[4] = SPRITE_RESOURCE_NONE;
            v4.resources[5] = SPRITE_RESOURCE_NONE;

            v0->unk_2B4[v5] = SpriteSystem_NewSprite(v1, v2, &v4);
            v8 = PokeIconPaletteIndex(v7, v6, v9);

            ManagedSprite_SetExplicitPaletteOffset(v0->unk_2B4[v5], 4 + v8);
            ManagedSprite_SetAnim(v0->unk_2B4[v5], 1);
            ManagedSprite_SetPriority(v0->unk_2B4[v5], 30 - v5);
        }
    }
}

static void VsRecorderViewerBox_SetPokemonIconsVisible(VsRecorderState *param0, int param1)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    int v1;
    int v2;

    for (v1 = 0; v1 < 30; v1++) {
        v2 = v0->unk_04.species[v1];

        if (v2 == 0) {
            continue;
        }

        ManagedSprite_SetDrawFlag(v0->unk_2B4[v1], param1);
    }
}

static void VsRecorderViewerBox_DestroyPokemonIcons(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    int v1;
    int v2;

    SpriteManager_UnloadPlttObjById(param0->unk_14.spriteManager, 100000);
    SpriteManager_UnloadCellObjById(param0->unk_14.spriteManager, 100000);
    SpriteManager_UnloadAnimObjById(param0->unk_14.spriteManager, 100000);

    for (v1 = 0; v1 < 30; v1++) {
        v2 = v0->unk_04.species[v1];

        if (v2 == 0) {
            continue;
        }

        if (v0->unk_2B4[v1] == NULL) {
            continue;
        }

        SpriteManager_UnloadCharObjById(param0->unk_14.spriteManager, 100000 + v1);
        Sprite_DeleteAndFreeResources(v0->unk_2B4[v1]);
        v0->unk_2B4[v1] = NULL;
    }
}

static void VsRecorderViewerBox_CreatePreviewPokemonSprite(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    SpeciesData *speciesData;
    PokemonSpriteTemplate v2;
    u8 gender;
    u8 isShiny;
    u32 otID = v0->unk_04.otId[v0->unk_1B0];
    u32 form = v0->unk_04.form[v0->unk_1B0];
    u16 species = v0->unk_04.species[v0->unk_1B0];
    u32 personality = v0->unk_04.personality[v0->unk_1B0];
    u32 v9;
    int v10 = 2;

    if (species == SPECIES_NONE) {
        v0->unk_32C = NULL;
        return;
    }

    if (VsRecorderViewerBox_IsBitSet(v0->unk_04.eggFlags, (1 << v0->unk_1B0)) == 1) {
        if (species == SPECIES_MANAPHY) {
            form = EGG_FORM_MANAPHY;
        } else {
            form = EGG_FORM_BASE;
        }

        species = SPECIES_EGG;
    }

    speciesData = SpeciesData_FromMonSpecies(species, HEAP_ID_102);
    gender = Pokemon_GetGenderOf(species, personality);
    isShiny = Pokemon_IsPersonalityShiny(otID, personality);
    v9 = LoadPokemonSpriteYOffset(species, gender, v10, form, personality);
    v9 = 0;

    BuildPokemonSpriteTemplate(&v2, species, gender, v10, isShiny, form, personality);
    v0->unk_32C = PokemonSpriteManager_CreateSprite(param0->unk_14.pokemonSpriteManager, &v2, 42, 91 + v9, 0, 0, NULL, NULL);
    SpeciesData_Free(speciesData);
}

static void VsRecorderViewerBox_SetPreviewSpriteVisible(VsRecorderState *param0, int param1)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    if (v0->unk_32C) {
        PokemonSprite_SetAttribute(v0->unk_32C, MON_SPRITE_HIDE, param1);
    }
}

static void VsRecorderViewerBox_DeletePreviewSprite(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    if (v0->unk_32C) {
        PokemonSprite_Delete(v0->unk_32C);
    }
}

static void VsRecorderViewerBox_LoadWallpaperAndRefresh(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    {
        PCBoxes *pcBoxes = SaveData_GetPCBoxes(param0->saveData);

        if ((v0->unk_04.wallpaper >= 16) && (v0->unk_04.wallpaper < (16 + 8))) {
            v0->unk_04.wallpaper = 0;
        }
        if ((v0->unk_04.wallpaper >= (16 + 8)) && (v0->unk_04.wallpaper < (16 + 8 + 8))) {
            if (PCBoxes_CheckHasUnlockedWallpaper(pcBoxes, v0->unk_04.wallpaper - (16 + 8)) == 0) {
                (void)0;
            }
        }
    }

    if (v0->unk_04.wallpaper >= (16 + 8 + 8)) {
        v0->unk_04.wallpaper = 0;
    }

    Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, (138 + (v0->unk_04.wallpaper * 3)), param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, (140 + (v0->unk_04.wallpaper * 3)), param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
    PaletteData_LoadBufferFromFile(param0->unk_14.palette, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, (139 + (v0->unk_04.wallpaper * 3)), HEAP_ID_102, 0, PALETTE_SIZE_BYTES * 2, PLTT_DEST(12), PLTT_DEST(12));

    VsRecorderViewerBox_CreatePreviewPokemonSprite(param0);
    VsRecorderViewerBox_CreatePokemonIcons(param0);
    VsRecorderViewerBox_PrintSpeciesName(param0, v0->unk_1B0);
    VsRecorderViewerBox_PrintBoxName(param0);
    VsRecorderViewerBox_PrintStatusMessage(param0, 270);
}

static void VsRecorderViewerBox_LoadWallpaper(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    {
        PCBoxes *pcBoxes = SaveData_GetPCBoxes(param0->saveData);

        if ((v0->unk_04.wallpaper >= 16) && (v0->unk_04.wallpaper < (16 + 8))) {
            v0->unk_04.wallpaper = 0;
        }

        if ((v0->unk_04.wallpaper >= (16 + 8)) && (v0->unk_04.wallpaper < (16 + 8 + 8))) {
            if (PCBoxes_CheckHasUnlockedWallpaper(pcBoxes, v0->unk_04.wallpaper - (16 + 8)) == 0) {
                v0->unk_04.wallpaper = 0;
            }
        }
    }

    Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, (138 + (v0->unk_04.wallpaper * 3)), param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, (140 + (v0->unk_04.wallpaper * 3)), param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
    PaletteData_LoadBufferFromFile(param0->unk_14.palette, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, (139 + (v0->unk_04.wallpaper * 3)), HEAP_ID_102, 0, PALETTE_SIZE_BYTES * 2, PLTT_DEST(12), PLTT_DEST(12));

    VsRecorderViewerBox_CreatePreviewPokemonSprite(param0);
    VsRecorderViewerBox_CreatePokemonIcons(param0);
}

static BOOL VsRecorderViewerBox_SetupBoxView(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:

    {
        VsRecorderViewerMenu_LoadBgPanelAlt(param0, 2);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerBox_CreateStatusWindows(param0);
        VsRecorderViewerBox_LoadWallpaperAndRefresh(param0);
        VsRecorderViewerBox_SetPreviewSpriteVisible(param0, 1);
        VsRecorderViewerBox_SetPokemonIconsVisible(param0, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);

        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 77, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
    }
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0, 0)) {
            VsRecorderViewerBox_SetPreviewSpriteVisible(param0, 0);
            VsRecorderViewerBox_SetPokemonIconsVisible(param0, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            G2_BlendNone();
            param0->unk_08++;
        }
        break;
    case 2:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 0)) {
            v0->unk_344 = v0->unk_330[0];
            VsRecorderViewerMain_SetState(param0, 3);
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    default:
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_UpdateBoxNavInput(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    TouchScreenActions_HandleAction(v0->unk_344);
    return 0;
}

static BOOL VsRecorderViewerBox_Exit(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerBox_DestroyPokemonIcons(param0);
        VsRecorderViewerBox_DeletePreviewSprite(param0);
        VsRecorderViewerBox_RemoveStatusWindows(param0);
        VsRecorderViewerBox_FreeHeaderSprites(param0);
        VsRecorderRing_SetActive(param0->unk_6F4, 0);
        VsRecorderRing_SetVisible(param0->unk_6F4, 0);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        {
            int v1;

            for (v1 = 0; v1 < 5; v1++) {
                TouchScreenActions_Free(v0->unk_330[v1]);
            }
        }

        VsRecorderViewerMenu_ResetFadeValue(&v0->unk_1AC);
        VsRecorderViewerMenu_InitMenu(param0);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
        param0->unk_08++;
        break;

    default:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 0)) {
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_1AC);

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.themeColor);

            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);

            PlayerProfile_Free(v0->unk_380.unk_04);
            Heap_Free(v0);
        } else {
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_1AC, param0->unk_14.themeColor);
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        }
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_SetupBoxListView(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0: {
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_LoadBgPanelAlt(param0, 2);
        VsRecorderViewerBox_CreateStatusWindows(param0);
        VsRecorderViewerBox_PrintStatusMessage(param0, 275);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 79, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);

        VsRecorderViewerBox_CreateListWindows(param0);
        VsRecorderViewerBox_SetHeaderLayout(param0, 1);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
    }
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0, 0)) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            G2_BlendNone();
            param0->unk_08++;
        }
        break;
    case 2:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 0)) {
            v0->unk_344 = v0->unk_330[2];
            VsRecorderViewerMain_SetState(param0, 3);
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;

    default:
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_UpdateBoxListInput(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    TouchScreenActions_HandleAction(v0->unk_330[2]);
    return 0;
}

static const u8 sVsRecorderViewerProfileBoxWindowRects[][4] = {
    { 0x8, 0x3, 0x10, 0x2 },
    { 0x9, 0xA, 0xE, 0x2 }
};

static void VsRecorderViewerBox_CreateProfileBoxWindows(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    Window *v1;
    int v2 = 1;
    int v3;
    int v4;
    int v5[] = { 121, 59 };
    String *v6;

    for (v3 = 0; v3 < 2; v3++) {
        v1 = &v0->unk_234[v3];
        Window_Init(v1);
        Window_Add(param0->unk_14.bgConfig, v1, 6, sVsRecorderViewerProfileBoxWindowRects[v3][0], sVsRecorderViewerProfileBoxWindowRects[v3][1], sVsRecorderViewerProfileBoxWindowRects[v3][2], sVsRecorderViewerProfileBoxWindowRects[v3][3], 14, v2);
        Window_FillTilemap(v1, 0x0);

        v6 = MessageLoader_GetNewString(param0->unk_14.messageLoader, v5[v3]);
        v4 = VsRecorderViewerList_CalcCenteredTextX(v1, v6);

        Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v6, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        Window_ScheduleCopyToVRAM(v1);
        v2 += (sVsRecorderViewerProfileBoxWindowRects[v3][2] * sVsRecorderViewerProfileBoxWindowRects[v3][3]);
        String_Free(v6);
    }
}

static void VsRecorderViewerBox_PrintProfileBoxMessage(VsRecorderState *param0, int param1)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    int v3;

    v1 = &v0->unk_234[0];

    Window_FillTilemap(v1, 0x0);

    v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, param1);
    v3 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v3, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);
}

static void VsRecorderViewerBox_CreateTitleWindow(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    Window *v1;
    int v2 = 1;
    int v3;
    int v4;
    String *v5;

    for (v3 = 0; v3 < 1; v3++) {
        v1 = &v0->unk_234[v3];

        Window_Init(v1);
        Window_Add(param0->unk_14.bgConfig, v1, 6, 12, 6, 8, 4, 14, v2);
        Window_FillTilemap(v1, 0x0);

        v5 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 34);

        {
            u32 v6 = (64 - Font_CalcMaxLineWidth(FONT_SYSTEM, v5, 0)) / 2;
            Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v5, v6, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        }

        Window_ScheduleCopyToVRAM(v1);
        String_Free(v5);
    }
}

static void VsRecorderViewerBox_RemoveTitleWindow(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    Window_ClearAndCopyToVRAM(&v0->unk_234[0]);
    Window_Remove(&v0->unk_234[0]);
}

static void VsRecorderViewerBox_RemoveTwoWindows(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    int v1;

    for (v1 = 0; v1 < 2; v1++) {
        Window_ClearAndCopyToVRAM(&v0->unk_234[v1]);
        Window_Remove(&v0->unk_234[v1]);
    }
}

static const u8 sVsRecorderViewerTitleWindowRect[][4] = {
    { 0x4, 0x3, 0x18, 0x2 }
};

static void VsRecorderViewerBox_CreateProfileBoxStatusWindow(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    Window *v1;
    int v2 = 1;
    int v3;
    int v4;
    int v5;
    int v6[] = { 27, 19, 26 };
    String *v7;

    for (v3 = 0; v3 < NELEMS(sVsRecorderViewerTitleWindowRect); v3++) {
        v1 = &v0->unk_1B4[v3];

        Window_Init(v1);
        Window_Add(param0->unk_14.bgConfig, v1, 2, sVsRecorderViewerTitleWindowRect[v3][0], sVsRecorderViewerTitleWindowRect[v3][1], sVsRecorderViewerTitleWindowRect[v3][2], sVsRecorderViewerTitleWindowRect[v3][3], 14, v2);
        Window_FillTilemap(v1, 0x0);

        if (v3 == 0) {
            v7 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 310 + v0->unk_380.unk_00);
            v4 = VsRecorderViewerList_CalcCenteredTextX(v1, v7);
            v5 = 0;
        }

        if (v7) {
            Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v7, v4, v5, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            String_Free(v7);
        }

        Window_ScheduleCopyToVRAM(v1);
        v2 += (sVsRecorderViewerTitleWindowRect[v3][2] * sVsRecorderViewerTitleWindowRect[v3][3]);
    }
}

static void VsRecorderViewerBox_RemoveProfileBoxStatusWindow(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    Window *v1;
    int v2;

    for (v2 = 0; v2 < NELEMS(sVsRecorderViewerTitleWindowRect); v2++) {
        Window_ClearAndCopyToVRAM(&v0->unk_1B4[v2]);
        Window_Remove(&v0->unk_1B4[v2]);
    }
}

static const VsRecorderViewerListConfig sVsRecorderViewerProfileBoxGridConfig = {
    NULL,
    0x0,
    0x3,
    0x3,
    0x7,
    0x1A,
    0xF,
    0x40,
    0x2,
    0x5,
    NULL
};

static BOOL VsRecorderViewerBox_UploadBox(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;
    VsRecorderViewerTransferStatus *v1;

    if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    switch (param0->unk_08) {
    case 0:
        VsRecorderRing_SetVisible(param0->unk_6F4, 0);
        VsRecorderViewerBox_RemoveStatusWindows(param0);
        VsRecorderViewerBox_RemoveListWindows(param0);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        VsRecorderViewerMenu_UpdateBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;

    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 0)) {
            Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 3, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 78, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    case 2:
        VsRecorderViewerList_SetupRing(param0, param0->unk_6F0, 128, 96);
        VsRecorderRing_SetVisible(param0->unk_6F0, 1);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 24, 24);
        VsRecorderViewerList_OpenMainMessage(param0, 289);
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->unk_08++;
        break;
    case 3:
        if (GlobalTerminalTransfer_UploadBox(VsRecorderViewerTransfer_GetTransfer(param0), v0->unk_380.unk_00) == 1) {
            param0->unk_08++;
        }
        break;
    case 4:
        VsRecorderViewerList_CloseMainMessage(param0);

        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_OpenMessage(param0, 3, v1->index, v1->category);

            v0->unk_380.unk_08 = 0;
            v0->unk_2F64 = 0;

            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerBox_CreateStatusWindows(param0);

            VsRecorderRing_SetVisible(param0->unk_6F4, 0);
            VsRecorderRing_SetActive(param0->unk_6F0, 0);
            VsRecorderRing_SetVisible(param0->unk_6F0, 0);
            VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 3);

            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            param0->unk_08 = 7;
        } else {
            Sound_StopEffect(1381, 0);
            Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);
            param0->unk_08++;
        }
        break;
    case 5:
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);

        if (v0->unk_380.unk_08 == 0) {
            param0->unk_08++;
            param0->unk_0C = 0;
            VsRecorderViewerList_OpenMainMessage(param0, 294);
        } else {
            param0->unk_08 = 0xFF;
        }
        break;
    case 6:
        if (((++param0->unk_0C) >= (30 * 2)) || (TouchScreen_Tapped() == 1)) {
            param0->unk_0C = 0;
            VsRecorderViewerList_CloseMainMessage(param0);
            v0->unk_2F64 = 0;

            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerBox_CreateStatusWindows(param0);

            VsRecorderRing_SetVisible(param0->unk_6F4, 0);
            VsRecorderRing_SetActive(param0->unk_6F0, 0);
            VsRecorderRing_SetVisible(param0->unk_6F0, 0);
            VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 3);

            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            param0->unk_08++;
        }
        break;
    case 7:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 0)) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 79, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
            param0->unk_08++;
        }
        break;
    case 8:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0, 2)) {
            VsRecorderViewerMenu_LoadBgPanelAlt(param0, 2);
            VsRecorderViewerBox_PrintStatusMessage(param0, 275);
            VsRecorderViewerBox_CreateListWindows(param0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            VsRecorderViewerMain_SetState(param0, 3);
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0, 0)) {
            VsRecorderViewerBox_CreateProfileBoxStatusWindow(param0);
            VsRecorderViewerBox_InitProfileBoxStrings(param0);

            {
                VsRecorderViewerList_SetDrawSuspended(param0, 1);

                v0->unk_2EAC = sVsRecorderViewerProfileBoxGridConfig;
                v0->unk_2EAC.entryCount = v0->unk_380.unk_08;

                VsRecorderViewerList_InitScrollBarWithAnim(&param0->unk_14.scrollBar, param0, 2);
                VsRecorderViewerList_ResetWindow(&param0->unk_14.listWindow);
                VsRecorderViewerList_InitTwoColumnWindow(&param0->unk_14.listWindow, param0, &v0->unk_2EAC, &v0->unk_2E0C[0]);
                VsRecorderViewerList_UpdateScrollBarVisibility(&param0->unk_14.scrollBar, &param0->unk_14.listWindow);
                VsRecorderViewerList_LoadArrowSprites(&param0->unk_14.listWindow, param0, 1);
                VsRecorderViewerList_SetArrowSpritesPosition(&param0->unk_14.listWindow, 56, 176);
                VsRecorderViewerList_SetDrawSuspended(param0, 0);
            }

            VsRecorderViewerBox_CreateProfileBoxWindows(param0);

            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);

            {
                VsRecorderViewerList_SetupRing(param0, param0->unk_6F0, 16, 68 + (param0->unk_14.listWindow.scrollState.scroll * 24));
                VsRecorderRing_SetVisible(param0->unk_6F0, 1);
                VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 12, 12);
            }

            VsRecorderViewerMain_SetState(param0, 5);
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    }

    return 0;
}

static void VsRecorderViewerBox_InitProfileBoxStrings(VsRecorderState *param0)
{
    int v0;
    VsRecorderViewerBoxContext *v1 = param0->unk_860;

    for (v0 = 0; v0 < v1->unk_380.unk_08; v0++) {
        v1->unk_2E0C[v0][1] = String_Init(20, HEAP_ID_102);
        String_CopyChars(v1->unk_2E0C[v0][1], v1->unk_38C[v0]->profile.name);
        VsRecorderViewerList_CheckNameChars(param0, v1->unk_2E0C[v0][1]);

        v1->unk_2E0C[v0][0] = String_Init(30, HEAP_ID_102);
        String_CopyChars(v1->unk_2E0C[v0][0], v1->unk_38C[v0]->boxData.boxName);
    }
}

static void VsRecorderViewerBox_FreeProfileBoxStrings(VsRecorderState *param0)
{
    int v0;
    VsRecorderViewerBoxContext *v1 = param0->unk_860;

    for (v0 = 0; v0 < v1->unk_380.unk_08; v0++) {
        if (v1->unk_2E0C[v0][0]) {
            String_Free(v1->unk_2E0C[v0][0]);
            v1->unk_2E0C[v0][0] = NULL;
        }

        if (v1->unk_2E0C[v0][1]) {
            String_Free(v1->unk_2E0C[v0][1]);
            v1->unk_2E0C[v0][1] = NULL;
        }
    }
}

static BOOL VsRecorderViewerBox_UpdateProfileBoxGridInput(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    if (v0->unk_2F64 == 0) {
        VsRecorderViewerList_HandleScrollBarInput(&param0->unk_14.scrollBar);
        VsRecorderViewerList_MoveSelection(&param0->unk_14.listWindow, param0->unk_14.scrollBar.direction);
        VsRecorderViewerList_UpdateTwoColumnWindow(&param0->unk_14.listWindow, param0, &v0->unk_2E0C[0]);
        VsRecorderRing_TrySetTargetPosition(param0->unk_6F0, 16, 68 + (param0->unk_14.listWindow.scrollState.scroll * 24));
    }

    TouchScreenActions_HandleAction(v0->unk_330[3]);

    return 0;
}

static BOOL VsRecorderViewerBox_CloseProfileBoxGrid(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerBox_FreeProfileBoxStrings(param0);
        VsRecorderViewerBox_RemoveTwoWindows(param0);

        if (v0->unk_2F64 == 0) {
            VsRecorderViewerBox_RemoveProfileBoxStatusWindow(param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerList_FreeScrollBar(&param0->unk_14.scrollBar);
            VsRecorderViewerList_FreeWindow(&param0->unk_14.listWindow);
            VsRecorderViewerList_FreeArrowSprites(&param0->unk_14.listWindow, param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
        } else {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerList_FreeProfile(&v0->unk_2ED8, param0);
            VsRecorderViewerBox_FreeLoadedProfile(param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
        }

        v0->unk_2F64 = 0;

        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerBox_CreateStatusWindows(param0);
        VsRecorderViewerBox_PrintTrainerNameMessage(param0, 0xFF);

        VsRecorderRing_SetVisible(param0->unk_6F4, 0);
        VsRecorderRing_SetActive(param0->unk_6F0, 0);
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->unk_08++;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 0)) {
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 79, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
            param0->unk_08++;
        }
        break;
    case 2:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0, 2)) {
            VsRecorderViewerMenu_LoadBgPanelAlt(param0, 2);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            VsRecorderViewerBox_PrintStatusMessage(param0, 275);
            VsRecorderViewerBox_CreateListWindows(param0);
            VsRecorderViewerMain_SetState(param0, 3);
        }
        break;
    default:
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_SelectProfileBox(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerBox_RemoveTwoWindows(param0);

        if (v0->unk_2F64 == 0) {
            VsRecorderViewerBox_RemoveProfileBoxStatusWindow(param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerList_FreeScrollBar(&param0->unk_14.scrollBar);
            VsRecorderViewerList_FreeWindow(&param0->unk_14.listWindow);
            VsRecorderViewerList_FreeArrowSprites(&param0->unk_14.listWindow, param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
        } else {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerList_FreeProfile(&v0->unk_2ED8, param0);
            VsRecorderViewerBox_FreeLoadedProfile(param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
        }

        VsRecorderRing_SetVisible(param0->unk_6F4, 0);
        VsRecorderRing_SetActive(param0->unk_6F0, 0);
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 0)) {
            param0->unk_08++;
        }
        break;
    case 2: {
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        v0->unk_04 = v0->unk_38C[param0->unk_14.listWindow.scrollState.selection]->boxData;
        VsRecorderViewerBox_SetCursorToFirstOccupiedSlot(v0);
        VsRecorderViewerMenu_LoadBgPanelAlt(param0, 2);
        VsRecorderViewerBox_CreateStatusWindows(param0);
        VsRecorderViewerBox_LoadWallpaperAndRefresh(param0);
        VsRecorderViewerBox_PrintTrainerNameMessage(param0, 0xFF);
        VsRecorderViewerBox_SetPreviewSpriteVisible(param0, 1);
        VsRecorderViewerBox_SetPokemonIconsVisible(param0, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);

        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 75, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
    }
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        param0->unk_08++;
        break;
    case 3:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0, 0)) {
            VsRecorderViewerBox_SetPreviewSpriteVisible(param0, 0);
            VsRecorderViewerBox_SetPokemonIconsVisible(param0, 1);
            VsRecorderViewerBox_CreateTitleWindow(param0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            G2_BlendNone();
            param0->unk_08++;
        }
        break;
    default:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 0)) {
            v0->unk_344 = v0->unk_330[0];

            VsRecorderViewerBox_SetCursorToFirstOccupiedSlot(v0);

            v0->unk_2F68 = v0->unk_1B0 % 6;
            v0->unk_2F6C = v0->unk_1B0 / 6;

            VsRecorderViewerList_SetupRing(param0, param0->unk_6F0, 110 + (v0->unk_2F68 * 24), 52 + (v0->unk_2F6C * 22));

            VsRecorderRing_SetVisible(param0->unk_6F0, 1);
            VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 12, 12);

            if ((v0->unk_04.species[v0->unk_1B0] != 0) && (VsRecorderViewerBox_IsBitSet(v0->unk_04.eggFlags, (1 << v0->unk_1B0)) != 1)) {
                Sound_PlayPokemonCry(v0->unk_04.species[v0->unk_1B0], v0->unk_04.form[v0->unk_1B0]);
            }

            VsRecorderViewerMain_SetState(param0, 10);
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_UpdateGridInput(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    TouchScreenActions_HandleAction(v0->unk_330[4]);
    return 0;
}

static BOOL VsRecorderViewerBox_OpenProfileBoxGrid(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerMenu_UpdateBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), 1);
        VsRecorderViewerBox_DeletePreviewSprite(param0);
        VsRecorderViewerBox_DestroyPokemonIcons(param0);
        VsRecorderViewerBox_ClearNameWindows(param0);

        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);

        VsRecorderViewerBox_RemoveStatusWindows(param0);
        VsRecorderViewerBox_RemoveTitleWindow(param0);
        param0->unk_08++;
    case 1:
        v0->unk_2F64 = 0;
        param0->unk_08++;
    case 2:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 0)) {
            Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 3, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 78, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            param0->unk_08++;
        }
        break;
    default:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0, 0)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderRing_SetVisible(param0->unk_6F0, 1);
            VsRecorderViewerBox_CreateProfileBoxStatusWindow(param0);
            VsRecorderViewerBox_CreateProfileBoxWindows(param0);

            {
                VsRecorderViewerList_InitScrollBarWithAnim(&param0->unk_14.scrollBar, param0, 2);
                VsRecorderViewerList_InitTwoColumnWindow(&param0->unk_14.listWindow, param0, &v0->unk_2EAC, &v0->unk_2E0C[0]);
                VsRecorderViewerList_UpdateScrollBarVisibility(&param0->unk_14.scrollBar, &param0->unk_14.listWindow);
                VsRecorderViewerList_LoadArrowSprites(&param0->unk_14.listWindow, param0, 1);
                VsRecorderViewerList_SetArrowSpritesPosition(&param0->unk_14.listWindow, 56, 176);
            }

            {
                VsRecorderViewerList_SetupRing(param0, param0->unk_6F0, 16, 68 + (param0->unk_14.listWindow.scrollState.scroll * 24));
                VsRecorderRing_SetVisible(param0->unk_6F0, 1);
                VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 12, 12);
            }

            if (v0->unk_2F64 == 0) {
                VsRecorderViewerList_HandleScrollBarInput(&param0->unk_14.scrollBar);
                VsRecorderViewerList_MoveSelection(&param0->unk_14.listWindow, param0->unk_14.scrollBar.direction);
                VsRecorderViewerList_UpdateTwoColumnWindow(&param0->unk_14.listWindow, param0, &v0->unk_2E0C[0]);
                VsRecorderRing_TrySetTargetPosition(param0->unk_6F0, 16, 68 + (param0->unk_14.listWindow.scrollState.scroll * 24));
            }

            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            VsRecorderViewerMain_SetState(param0, 5);
        }
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_OpenProfileBoxDetail(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);

        if (v0->unk_2F64 == 0) {
            VsRecorderViewerBox_RemoveProfileBoxStatusWindow(param0);
        }

        {
            VsRecorderViewerList_FreeScrollBar(&param0->unk_14.scrollBar);
            VsRecorderViewerList_FreeWindow(&param0->unk_14.listWindow);
            VsRecorderViewerList_FreeArrowSprites(&param0->unk_14.listWindow, param0);
        }

        v0->unk_2F64 = 1;

        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        VsRecorderViewerMenu_UpdateBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);

        param0->unk_08++;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 1)) {
            VsRecorderViewerBox_LoadProfileFromBox(param0, param0->unk_14.listWindow.scrollState.selection);
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerList_InitProfile(&v0->unk_2ED8, param0);
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_2ED8, 0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 80, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
            param0->unk_08++;
        }
        break;
    case 2:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0, 1)) {
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_2ED8, 1);
            VsRecorderViewerBox_PrintProfileBoxMessage(param0, 121 + v0->unk_2F64);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            VsRecorderViewerMain_SetState(param0, 5);
        }
        break;
    default:
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_CloseProfileBoxDetail(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        v0->unk_2F64 = 0;
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_FreeProfile(&v0->unk_2ED8, param0);
        VsRecorderViewerBox_FreeLoadedProfile(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->unk_08++;
    case 2:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 1, 1)) {
            Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 3, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
            param0->unk_08++;
        }
        break;
    default:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_1A4, &v0->unk_1A8, 0, 1)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerBox_PrintProfileBoxMessage(param0, 121 + v0->unk_2F64);
            VsRecorderViewerBox_CreateProfileBoxStatusWindow(param0);

            {
                VsRecorderViewerList_InitScrollBarWithAnim(&param0->unk_14.scrollBar, param0, 2);
                VsRecorderViewerList_InitTwoColumnWindow(&param0->unk_14.listWindow, param0, &v0->unk_2EAC, &v0->unk_2E0C[0]);
                VsRecorderViewerList_UpdateScrollBarVisibility(&param0->unk_14.scrollBar, &param0->unk_14.listWindow);
                VsRecorderViewerList_LoadArrowSprites(&param0->unk_14.listWindow, param0, 1);
                VsRecorderViewerList_SetArrowSpritesPosition(&param0->unk_14.listWindow, 56, 176);
            }

            if (v0->unk_2F64 == 0) {
                VsRecorderViewerList_HandleScrollBarInput(&param0->unk_14.scrollBar);
                VsRecorderViewerList_MoveSelection(&param0->unk_14.listWindow, param0->unk_14.scrollBar.direction);
                VsRecorderViewerList_UpdateTwoColumnWindow(&param0->unk_14.listWindow, param0, &v0->unk_2E0C[0]);
                VsRecorderRing_TrySetTargetPosition(param0->unk_6F0, 16, 68 + (param0->unk_14.listWindow.scrollState.scroll * 24));
            }

            VsRecorderRing_SetVisible(param0->unk_6F0, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            VsRecorderViewerMain_SetState(param0, 5);
        }
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBox_ExitBoxList(VsRecorderState *param0)
{
    VsRecorderViewerBoxContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerBox_RemoveStatusWindows(param0);
        VsRecorderViewerBox_FreeHeaderSprites(param0);

        VsRecorderRing_SetActive(param0->unk_6F4, 0);
        VsRecorderRing_SetVisible(param0->unk_6F4, 0);
        VsRecorderRing_SetActive(param0->unk_6F0, 1);
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        {
            int v1;

            for (v1 = 0; v1 < 5; v1++) {
                TouchScreenActions_Free(v0->unk_330[v1]);
            }
        }

        VsRecorderViewerMenu_ResetFadeValue(&v0->unk_1AC);
        VsRecorderViewerMenu_InitMenu(param0);

        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
        param0->unk_08++;
        break;
    default:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_1AC, 0)) {
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_1AC);

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.themeColor);

            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);

            PlayerProfile_Free(v0->unk_380.unk_04);
            Heap_Free(v0);
        } else {
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_1AC, param0->unk_14.themeColor);
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_1AC, param0->unk_14.themeColor);
        }

        break;
    }

    return 0;
}

void VsRecorderViewerBox_OnProfileBoxTransferComplete(void *param0, const VsRecorderViewerTransferStatus *param1)
{
    VsRecorderViewerBoxContext *v0 = param0;

    if (param1->done == 1) {
        (void)0;
    } else {
        (void)0;
    }
}

void VsRecorderViewerBox_OnBoxTransferComplete(void *param0, const VsRecorderViewerTransferStatus *param1)
{
    VsRecorderState *v0 = param0;
    VsRecorderViewerBoxContext *v1 = v0->unk_860;

    if (param1->done == 1) {
        v1->unk_380.unk_08 = 0;
    } else {
        v1->unk_380.unk_08 = GlobalTerminalGds_GetBoxList(VsRecorderViewerTransfer_GetTransfer(v0), v1->unk_38C, 20);
        MI_CpuCopy8(v1->unk_38C, &v1->unk_3DC, sizeof(GlobalTerminalProfileBox) * 20);
    }
}
