#include "vs_recorder_viewer/vs_recorder_viewer_02237D24.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/dress_up_photo.h"
#include "struct_defs/struct_02030A80.h"
#include "struct_defs/struct_vs_recorder_state.h"

#include "image_clip_app/image_clip_app_0225AF8C.h"
#include "image_clip_app/struct_image_clip_app_0225AF8C.h"
#include "image_clip_app/struct_image_clip_app_0225B1BC_decl.h"
#include "global_terminal/global_terminal_0222AE60.h"
#include "global_terminal/global_terminal_0222B008.h"
#include "global_terminal/global_terminal_0222BC4C.h"
#include "global_terminal/struct_global_terminal_0222BC90.h"
#include "vs_recorder_viewer/const_vs_recorder_viewer_022491F0.h"
#include "vs_recorder_viewer/vs_recorder_viewer.h"
#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_0224112C.h"
#include "vs_recorder_viewer/vs_recorder_viewer_const_funcptr_tables.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022312B0.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022323B8.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223CAA4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223E01C_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02248CDC.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02249380.h"

#include "bg_window.h"
#include "font.h"
#include "game_overlay.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "palette.h"
#include "pokedex.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "string_template.h"
#include "system.h"
#include "text.h"
#include "touch_screen.h"
#include "touch_screen_actions.h"
#include "font_oam.h"
#include "g3_buffer.h"
#include "image_clips.h"
#include "player_profile.h"
#include "vs_recorder_ring.h"
#include "vram_transfer.h"

FS_EXTERN_OVERLAY(image_clip_app);

typedef struct {
    int unk_00;
    int unk_04;
    DressUpPhoto *photo;
    GlobalTerminalProfilePhoto *unk_0C[5];
} VsRecorderViewerProfilePhotoList;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    Window unk_10[12];
    Window unk_D0[12];
    int unk_190;
    int unk_194;
    VsRecorderViewerTextSprite unk_198[2];
    TouchScreenActions *unk_1D0[1];
    VsRecorderViewerRankingMessageBox unk_1D4;
    VsRecorderViewerListEntry *unk_1E8;
    VsRecorderViewerListConfig unk_1EC;
    PhotoSpriteConfig unk_218;
    PhotoSprite *unk_228;
    DressUpPhoto *photo;
    VsRecorderViewerProfilePhotoList unk_230;
    VsRecorderViewerProfilePanel unk_250;
    PlayerProfile *unk_2DC;
    int unk_2E0;
    int unk_2E4;
} VsRecorderViewerProfile;

static BOOL VsRecorderViewerProfile_Init(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_InitDisplay(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_ShowLocalPhoto(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_HandlePhotoModeInput(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_UploadPhoto(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_ExitPhotoMode(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_EnterCategoryMenu(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_SelectCategory(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_ShowCategoryRecords(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_CloseCategoryRecords(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_UploadRanking(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_ShowDownloadedPhoto(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_NavigatePhotoList(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_CloseProfileView(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_SwitchToProfileView(VsRecorderState *param0);
static BOOL VsRecorderViewerProfile_SwitchToPhotoView(VsRecorderState *param0);
static void VsRecorderViewerProfile_RemoveMessageWindow(VsRecorderState *param0);
static void VsRecorderViewerProfile_DrawMessageWindow(VsRecorderState *param0, int param1);
static void VsRecorderViewerProfile_CreateMessageWindow(VsRecorderState *param0);
static void VsRecorderViewerProfile_VBlankCallback(void *param0);
static void VsRecorderViewerProfile_SetPhotoClipWindow(void);
static void VsRecorderViewerProfile_ResetClipWindow(void);
static void VsRecorderViewerProfile_SetArrowSpritesVisible(VsRecorderState *param0, int param1);
static void VsRecorderViewerProfile_CreateArrowSprites(VsRecorderState *param0);
static void VsRecorderViewerProfile_FreeArrowSprites(VsRecorderState *param0);
static void VsRecorderViewerProfile_DrawLocalPhotoName(VsRecorderState *param0);
static void VsRecorderViewerProfile_DrawDownloadedPhotoName(VsRecorderState *param0, int param1);
static BOOL VsRecorderViewerProfile_CategoryHasSeenSpecies(VsRecorderState *param0, int param1);
static void VsRecorderViewerProfile_BuildSpeciesList(VsRecorderState *param0, int param1);
static void VsRecorderViewerProfile_FreeSpeciesList(VsRecorderState *param0);
static void VsRecorderViewerProfile_CategoryTouchHandler(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerProfile_DrawCategoryWindows(VsRecorderState *param0);
static void VsRecorderViewerProfile_RemoveCategoryWindows(VsRecorderState *param0);
static void VsRecorderViewerProfile_RemoveNameWindow(VsRecorderState *param0);
void VsRecorderViewerProfile_ProfilePhotoCallback(void *param0, const VsRecorderViewerTransferStatus *param1);
void VsRecorderViewerProfile_ProfileCallback(void *param0, const VsRecorderViewerTransferStatus *param1);

static u16 sVsRecorderViewerProfileCategoryOffsets[] = {
    0x0,
    0x57,
    0x88,
    0xBF,
    0xEB,
    0x12F,
    0x168,
    0x1C9,
    0x1E7,
    0x1ED
};

// clang-format off
BOOL (*const sVsRecorderViewerProfilePhotoModeTable[])(VsRecorderState *) = {
    VsRecorderViewerProfile_Init,
    VsRecorderViewerProfile_InitDisplay,
    VsRecorderViewerProfile_ShowLocalPhoto,
    VsRecorderViewerProfile_HandlePhotoModeInput,
    VsRecorderViewerProfile_UploadPhoto,
    VsRecorderViewerProfile_ExitPhotoMode,
};
// clang-format on

// clang-format off
BOOL (*const sVsRecorderViewerProfileBrowserModeTable[])(VsRecorderState *) = {
    VsRecorderViewerProfile_Init,
    VsRecorderViewerProfile_InitDisplay,
    VsRecorderViewerProfile_EnterCategoryMenu,
    VsRecorderViewerProfile_SelectCategory,
    VsRecorderViewerProfile_ShowCategoryRecords,
    VsRecorderViewerProfile_CloseCategoryRecords,
    VsRecorderViewerProfile_UploadRanking,
    VsRecorderViewerProfile_ShowDownloadedPhoto,
    VsRecorderViewerProfile_NavigatePhotoList,
    VsRecorderViewerProfile_CloseProfileView,
    VsRecorderViewerProfile_SwitchToProfileView,
    VsRecorderViewerProfile_SwitchToPhotoView,
};
// clang-format on

static const TouchScreenRect sVsRecorderViewerProfilePhotoTouchRects[] = {
    { 0x98, 0xB8, 0x20, 0x80 },
    { 0x98, 0xB8, 0x80, 0xE0 }
};

static const TouchScreenRect sVsRecorderViewerProfileBackTouchRect[] = {
    { 0x98, 0xB8, 0x50, 0xB0 }
};

static const TouchScreenRect sVsRecorderViewerProfileCategoryTouchRects[] = {
    { 0x18, 0x28, 0x38, 0xC0 },
    { 0x28, 0x38, 0x38, 0xC0 },
    { 0x38, 0x48, 0x38, 0xC0 },
    { 0x48, 0x58, 0x38, 0xC0 },
    { 0x58, 0x68, 0x38, 0xC0 },
    { 0x68, 0x78, 0x38, 0xC0 }
};

static const TouchScreenRect sVsRecorderViewerProfilePhotoNavTouchRects[] = {
    { 0x10, 0x30, 0x38, 0xC8 },
    { 0x48, 0x68, 0x18, 0x48 },
    { 0x48, 0x68, 0xB8, 0xE8 }
};

static const VsRecorderViewerListConfig sVsRecorderViewerProfileWindowConfig = {
    NULL,
    0x0,
    0x1,
    0x9,
    0x3,
    0xE,
    0xC,
    0x20,
    0x6,
    0x6,
    sVsRecorderViewerProfileCategoryTouchRects
};

static BOOL VsRecorderViewerProfile_Init(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerProfile));

    memset(v0, 0, sizeof(VsRecorderViewerProfile));
    param0->unk_860 = v0;
    Overlay_LoadByID(FS_OVERLAY_ID(image_clip_app), 2);

    {
        v0->unk_218.bgConfig = param0->unk_14.bgConfig;
        v0->unk_218.xPos = (128 - 56);
        v0->unk_218.yPos = (96 - 64 - 16);
        v0->unk_218.heapID = HEAP_ID_102;
    }

    {
        v0->unk_230.photo = DressUpPhoto_New(HEAP_ID_102);
        v0->unk_250.profile = PlayerProfile_New(HEAP_ID_102);
    }

    Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
    Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
    Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
    Bg_ClearTilemap(param0->unk_14.bgConfig, 7);

    VsRecorderViewerMenu_SetDefaultBlendAlpha(&v0->unk_00, &v0->unk_04, 0);
    VsRecorderViewerMain_SetState(param0, 1);

    return 0;
}

static BOOL VsRecorderViewerProfile_InitDisplay(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 1:
        Bg_SetPriority(BG_LAYER_MAIN_0, 0);
        Bg_SetPriority(BG_LAYER_MAIN_2, 0);
        Bg_SetPriority(BG_LAYER_MAIN_1, 3);
        Bg_SetPriority(BG_LAYER_MAIN_3, 2);
        Bg_SetPriority(BG_LAYER_SUB_0, 0);
        Bg_SetPriority(BG_LAYER_SUB_2, 1);
        Bg_SetPriority(BG_LAYER_SUB_1, 3);
        Bg_SetPriority(BG_LAYER_SUB_3, 2);
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        param0->unk_08++;
        break;
    case 2:
        VsRecorderViewerList_StartNetworkTask(param0, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        param0->unk_08++;
        break;
    default:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_HideAndFreeMenu(param0);
        VsRecorderViewerProfile_CreateArrowSprites(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        VsRecorderViewerMain_SetState(param0, 2);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_ShowLocalPhoto(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerProfile_SetPhotoClipWindow();
        VsRecorderViewerList_LoadBgTilemap(param0, 35, 3);
        VsRecorderViewerList_LoadBgTilemap(param0, 37, 7);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        v0->photo = ImageClips_GetDressUpPhoto(SaveData_GetImageClips(param0->saveData), 0);

        if (v0->unk_228 == NULL) {
            v0->unk_228 = PhotoSprite_CreateForDressUp(&v0->unk_218, v0->photo);
            PhotoSprite_SetTransformEnabled(v0->unk_228, 1);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
        SetVBlankCallback(VsRecorderViewerProfile_VBlankCallback, param0);
        param0->unk_08++;
        break;
    case 1:
        PaletteData_LoadBufferFromHardware(param0->unk_14.palette, PLTTBUF_MAIN_BG, PLTT_DEST(0), 16 * PALETTE_SIZE_BYTES);
        param0->unk_08++;
        break;
    case 2:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
            VsRecorderViewerProfile_DrawLocalPhotoName(param0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }
    if (v0->unk_228) {
        G3_ResetG3X();
        PhotoSprite_Update(v0->unk_228);
        G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_HandlePhotoModeInput(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    if (TouchScreen_LocationPressed(&sVsRecorderViewerProfilePhotoTouchRects[0])) {
        VsRecorderViewerList_PlayRingAnim(param0);
        VsRecorderViewerMain_SetState(param0, 5);
    }

    if (TouchScreen_LocationPressed(&sVsRecorderViewerProfilePhotoTouchRects[1])) {
        VsRecorderViewerList_PlayRingAnim(param0);
        VsRecorderViewerMain_SetState(param0, 4);
    }

    if (v0->unk_228) {
        G3_ResetG3X();
        PhotoSprite_Update(v0->unk_228);
        G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_UploadPhoto(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;
    VsRecorderViewerTransferStatus *v1;

    if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    switch (param0->unk_08) {
    case 0:
        Bg_SetPriority(BG_LAYER_MAIN_0, 1);
        Bg_SetPriority(BG_LAYER_MAIN_1, 3);
        Bg_SetPriority(BG_LAYER_MAIN_2, 2);
        Bg_SetPriority(BG_LAYER_MAIN_3, 1);
        Bg_SetPriority(BG_LAYER_SUB_0, 1);
        Bg_SetPriority(BG_LAYER_SUB_1, 3);
        Bg_SetPriority(BG_LAYER_SUB_2, 2);
        Bg_SetPriority(BG_LAYER_SUB_3, 1);

        {
            Heap_Free(v0->unk_230.photo);
            PlayerProfile_Free(v0->unk_250.profile);
        }

        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
        VsRecorderViewerProfile_RemoveNameWindow(param0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerProfile_FreeArrowSprites(param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
            Bg_SetOffset(param0->unk_14.bgConfig, 2, 0, 0);
            Bg_SetPriority(BG_LAYER_MAIN_2, 0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        VsRecorderViewerList_SetupRing(param0, param0->unk_6F0, 128, 96);
        VsRecorderRing_SetVisible(param0->unk_6F0, 1);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 24, 24);
        VsRecorderViewerList_OpenMainMessage(param0, 286);
        v0->unk_2DC = PlayerProfile_New(HEAP_ID_102);
        PlayerProfile_Init(v0->unk_2DC, param0->saveData);
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->unk_08++;
        break;
    case 3:
        if (GlobalTerminalTransfer_UploadProfilePhoto(VsRecorderViewerTransfer_GetTransfer(param0), v0->unk_2DC, v0->photo) == 1) {
            PlayerProfile_Free(v0->unk_2DC);
            param0->unk_08++;
        }
        break;
    case 4:
        VsRecorderViewerList_CloseMainMessage(param0);

        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_OpenMessage(param0, 0, v1->index, v1->category);
            param0->unk_08++;
        } else {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_IncrementTrainerScore(param0, 47);
            Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);

            param0->unk_08++;
        }
        break;
    case 5:
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);
        param0->unk_08++;
        break;
    case 6:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->unk_08++;
        break;
    default:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
            if (v0->unk_228) {
                PhotoSprite_Free(v0->unk_228);
                VsRecorderViewerMain_InitBg2(param0);
                Bg_SetPriority(BG_LAYER_MAIN_2, 0);
                VsRecorderViewerProfile_ResetClipWindow();
            }

            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.themeColor);

            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);

            Heap_Free(v0);
            Overlay_UnloadByID(FS_OVERLAY_ID(image_clip_app));
            SetVBlankCallback(VsRecorderViewerMain_VBlankCallback, param0);
        } else {
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.themeColor);
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_ExitPhotoMode(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        Bg_SetPriority(BG_LAYER_MAIN_0, 1);
        Bg_SetPriority(BG_LAYER_MAIN_1, 3);
        Bg_SetPriority(BG_LAYER_MAIN_2, 2);
        Bg_SetPriority(BG_LAYER_MAIN_3, 1);
        Bg_SetPriority(BG_LAYER_SUB_0, 1);
        Bg_SetPriority(BG_LAYER_SUB_1, 3);
        Bg_SetPriority(BG_LAYER_SUB_2, 2);
        Bg_SetPriority(BG_LAYER_SUB_3, 1);

        {
            Heap_Free(v0->unk_230.photo);
            PlayerProfile_Free(v0->unk_250.profile);
        }

        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
        VsRecorderViewerProfile_RemoveNameWindow(param0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerProfile_FreeArrowSprites(param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->unk_08++;
        break;
    default:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);

            if (v0->unk_228) {
                PhotoSprite_Free(v0->unk_228);
                VsRecorderViewerMain_InitBg2(param0);
                Bg_SetPriority(BG_LAYER_MAIN_2, 0);
                VsRecorderViewerProfile_ResetClipWindow();
            }

            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.themeColor);

            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);

            Heap_Free(v0);
            Overlay_UnloadByID(FS_OVERLAY_ID(image_clip_app));
            SetVBlankCallback(VsRecorderViewerMain_VBlankCallback, param0);
        } else {
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.themeColor);
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        }
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_EnterCategoryMenu(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerProfile_SetArrowSpritesVisible(param0, 1);
        param0->unk_08++;
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_SelectCategory(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_LoadBgTilemap(param0, 60, 7);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
        v0->unk_1D0[0] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsPokedexGrid, NELEMS(sVsRecorderViewerRecord_TouchRectsPokedexGrid), VsRecorderViewerProfile_CategoryTouchHandler, param0, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            VsRecorderViewerList_OpenMainMessage(param0, 114);
            VsRecorderViewerProfile_DrawCategoryWindows(param0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        TouchScreenActions_HandleAction(v0->unk_1D0[0]);

        if (TouchScreen_LocationPressed(&sVsRecorderViewerProfileBackTouchRect[0])
            || (v0->unk_1D4.active == 1)) {
            VsRecorderViewerList_PlayRingAnim(param0);
            param0->unk_08++;
        }
        break;
    case 3:
        VsRecorderViewerProfile_RemoveCategoryWindows(param0);
        TouchScreenActions_Free(v0->unk_1D0[0]);
        VsRecorderViewerList_CloseMainMessage(param0);
        param0->unk_08++;
    case 4:
        if (v0->unk_1D4.active == 1) {
            if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
                param0->unk_08++;
            }
        } else {
            VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

            if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
                param0->unk_08++;
            }

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        }
        break;
    default:
        if (v0->unk_1D4.active == 1) {
            VsRecorderViewerMain_SetState(param0, 4);
        } else {
            VsRecorderViewerMain_SetState(param0, 5);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_ShowCategoryRecords(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerProfile_SetArrowSpritesVisible(param0, 1);
        VsRecorderViewerList_LoadBgTilemap(param0, 58, 7);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 2)) {
            VsRecorderViewerList_OpenMainMessage(param0, 114);
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerList_InitScrollBar(&param0->unk_14.scrollBar, param0);

            v0->unk_1EC = sVsRecorderViewerProfileWindowConfig;
            v0->unk_1EC.entries = v0->unk_1E8;
            v0->unk_1EC.entryCount = v0->unk_1D4.entryCount;

            VsRecorderViewerList_ResetWindow(&param0->unk_14.listWindow);
            VsRecorderViewerList_InitRecordWindow(&param0->unk_14.listWindow, param0, v0->unk_1D4.messageLoader, &v0->unk_1EC);
            VsRecorderViewerList_UpdateScrollBarVisibility(&param0->unk_14.scrollBar, &param0->unk_14.listWindow);
            VsRecorderViewerList_LoadArrowSprites(&param0->unk_14.listWindow, param0, 2);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);

            v0->unk_2E0 = 0;
            param0->unk_08++;
        }
        break;
    case 2:
        VsRecorderViewerList_HandleScrollBarInput(&param0->unk_14.scrollBar);
        VsRecorderViewerList_ScrollList(&param0->unk_14.listWindow, param0->unk_14.scrollBar.direction);

        {
            int v1 = VsRecorderViewerList_UpdateRecordWindow(&param0->unk_14.listWindow, param0);

            if (v1) {
                v0->unk_2E0 = v1;
                VsRecorderViewerList_PlayRingAnim(param0);
                param0->unk_08++;
            }
        }

        if (TouchScreen_LocationPressed(&sVsRecorderViewerProfileBackTouchRect[0])) {
            VsRecorderViewerList_PlayRingAnim(param0);
            param0->unk_08++;
        }
        break;
    case 3:
        VsRecorderViewerList_CloseMainMessage(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_FreeScrollBar(&param0->unk_14.scrollBar);
        VsRecorderViewerList_FreeWindow(&param0->unk_14.listWindow);
        VsRecorderViewerList_FreeArrowSprites(&param0->unk_14.listWindow, param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->unk_08++;
    case 4:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerProfile_FreeSpeciesList(param0);
        if (v0->unk_2E0) {
            VsRecorderViewerMain_SetState(param0, 6);
        } else {
            VsRecorderViewerMain_SetState(param0, 3);
        }
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_CloseCategoryRecords(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        Bg_SetPriority(BG_LAYER_MAIN_0, 1);
        Bg_SetPriority(BG_LAYER_MAIN_1, 3);
        Bg_SetPriority(BG_LAYER_MAIN_2, 2);
        Bg_SetPriority(BG_LAYER_MAIN_3, 1);
        Bg_SetPriority(BG_LAYER_SUB_0, 1);
        Bg_SetPriority(BG_LAYER_SUB_1, 3);
        Bg_SetPriority(BG_LAYER_SUB_2, 2);
        Bg_SetPriority(BG_LAYER_SUB_3, 1);

        {
            Heap_Free(v0->unk_230.photo);
            PlayerProfile_Free(v0->unk_250.profile);
        }

        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerProfile_FreeArrowSprites(param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->unk_08++;
        break;
    default:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);

            if (v0->unk_228) {
                PhotoSprite_Free(v0->unk_228);
                VsRecorderViewerMain_InitBg2(param0);
                Bg_SetPriority(BG_LAYER_MAIN_2, 0);
                VsRecorderViewerProfile_ResetClipWindow();
            }

            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.themeColor);

            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);

            Heap_Free(v0);
            Overlay_UnloadByID(FS_OVERLAY_ID(image_clip_app));
            SetVBlankCallback(VsRecorderViewerMain_VBlankCallback, param0);
        } else {
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.themeColor);
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_UploadRanking(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;
    VsRecorderViewerTransferStatus *v1;

    if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_SetupRing(param0, param0->unk_6F0, 128, 96);
        VsRecorderRing_SetVisible(param0->unk_6F0, 1);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 24, 24);
        VsRecorderViewerList_OpenMainMessage(param0, 287);
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->unk_08++;
        break;
    case 1:
        if (GlobalTerminalTransfer_UploadProfile(VsRecorderViewerTransfer_GetTransfer(param0), v0->unk_2E0) == 1) {
            param0->unk_08++;
        }
        break;
    case 2:
        VsRecorderViewerList_CloseMainMessage(param0);

        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_OpenMessage(param0, 1, v1->index, v1->category);
            v0->unk_2E4 = 0;
            param0->unk_0C = 0;
            VsRecorderRing_SetVisible(param0->unk_6F0, 0);
            VsRecorderViewerMain_SetState(param0, 3);
        } else {
            Sound_StopEffect(1381, 0);
            Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);
            param0->unk_08++;
        }
        break;
    case 3:
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);
        param0->unk_08++;
        break;
    case 4:
        if (v0->unk_2E4) {
            v0->unk_230.unk_04 = 0;
            v0->unk_230.unk_00 = 0;
            VsRecorderViewerMain_SetState(param0, 7);
        } else {
            VsRecorderViewerList_OpenMainMessage(param0, 293);
            param0->unk_08++;
            param0->unk_0C = 0;
        }
        break;
    default:
        if (((++param0->unk_0C) >= (30 * 2)) || (TouchScreen_Tapped() == 1)) {
            param0->unk_0C = 0;
            VsRecorderViewerList_CloseMainMessage(param0);
            VsRecorderViewerMain_SetState(param0, 3);
        }
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_ShowDownloadedPhoto(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:

        v0->unk_0C = 0;
        GlobalTerminal_DeserializeDressUpPhoto(&v0->unk_230.unk_0C[v0->unk_230.unk_04]->photo, v0->unk_230.photo);
        v0->unk_228 = PhotoSprite_CreateForDressUp(&v0->unk_218, v0->unk_230.photo);

        PhotoSprite_SetTransformEnabled(v0->unk_228, 0);
        VsRecorderViewerProfile_SetPhotoClipWindow();
        VsRecorderViewerList_LoadBgTilemap(param0, 35, 3);
        VsRecorderViewerList_LoadBgTilemap(param0, 36, 7);

        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
        SetVBlankCallback(VsRecorderViewerProfile_VBlankCallback, param0);
        param0->unk_08++;
        break;
    case 1:
        PaletteData_LoadBufferFromHardware(param0->unk_14.palette, PLTTBUF_MAIN_BG, PLTT_DEST(0), 16 * PALETTE_SIZE_BYTES);
        param0->unk_08++;
        break;
    case 2:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            PhotoSprite_SetTransformEnabled(v0->unk_228, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
            VsRecorderViewerProfile_DrawDownloadedPhotoName(param0, v0->unk_230.unk_04);
            VsRecorderViewerProfile_CreateMessageWindow(param0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 8);
        break;
    }

    if (v0->unk_228) {
        G3_ResetG3X();
        PhotoSprite_Update(v0->unk_228);
        G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_NavigatePhotoList(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    if (TouchScreen_LocationPressed(&sVsRecorderViewerProfileBackTouchRect[0])) {
        VsRecorderViewerList_PlayRingAnim(param0);
        VsRecorderViewerMain_SetState(param0, 9);
    }

    if (TouchScreen_LocationPressed(&sVsRecorderViewerProfilePhotoNavTouchRects[0])) {
        VsRecorderViewerList_PlayRingAnim(param0);
        VsRecorderViewerMain_SetState(param0, 10);
    }

    if (TouchScreen_LocationPressed(&sVsRecorderViewerProfilePhotoNavTouchRects[1])) {
        if (v0->unk_230.unk_04 != 0) {
            v0->unk_230.unk_04--;
        } else {
            v0->unk_230.unk_04 = v0->unk_2E4 - 1;
        }

        VsRecorderViewerList_PlayRingAnim(param0);
        VsRecorderViewerMain_SetState(param0, 11);
    }

    if (TouchScreen_LocationPressed(&sVsRecorderViewerProfilePhotoNavTouchRects[2])) {
        v0->unk_230.unk_04++;
        v0->unk_230.unk_04 %= v0->unk_2E4;
        VsRecorderViewerList_PlayRingAnim(param0);
        VsRecorderViewerMain_SetState(param0, 11);
    }

    if (v0->unk_228) {
        G3_ResetG3X();
        PhotoSprite_Update(v0->unk_228);
        G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_CloseProfileView(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        if (v0->unk_0C == 0) {
            Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
            VsRecorderViewerProfile_RemoveNameWindow(param0);
        } else {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerList_FreeProfile(&v0->unk_250, param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
        }

        VsRecorderViewerProfile_RemoveMessageWindow(param0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            if (v0->unk_228) {
                PhotoSprite_Free(v0->unk_228);
                VsRecorderViewerMain_InitBg2(param0);
                Bg_SetPriority(BG_LAYER_MAIN_2, 0);
                v0->unk_228 = NULL;
                VsRecorderViewerProfile_ResetClipWindow();
            }

            Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_SwitchToProfileView(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        if (v0->unk_0C == 0) {
            VsRecorderViewerProfile_RemoveNameWindow(param0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        } else {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerList_FreeProfile(&v0->unk_250, param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
        }

        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 1)) {
            if (v0->unk_0C == 0) {
                if (v0->unk_228) {
                    PhotoSprite_Free(v0->unk_228);
                    VsRecorderViewerMain_InitBg2(param0);
                    Bg_SetPriority(BG_LAYER_MAIN_2, 0);
                    v0->unk_228 = NULL;
                    VsRecorderViewerProfile_ResetClipWindow();
                }

                Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
                Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
                GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            }

            param0->unk_08++;
        }
        break;
    case 2:
        if (v0->unk_0C == 0) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            GlobalTerminal_DeserializePlayerProfile(&v0->unk_230.unk_0C[v0->unk_230.unk_04]->profile, v0->unk_250.profile);
            VsRecorderViewerList_InitProfile(&v0->unk_250, param0);
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_250, 0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            VsRecorderViewerList_LoadBgTilemap(param0, 80, 3);
        } else {
            GlobalTerminal_DeserializeDressUpPhoto(&v0->unk_230.unk_0C[v0->unk_230.unk_04]->photo, v0->unk_230.photo);
            v0->unk_228 = PhotoSprite_CreateForDressUp(&v0->unk_218, v0->unk_230.photo);
            PhotoSprite_SetTransformEnabled(v0->unk_228, 0);
            VsRecorderViewerProfile_SetPhotoClipWindow();
            VsRecorderViewerList_LoadBgTilemap(param0, 35, 3);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
        }

        param0->unk_08++;
        break;
    case 3:
        if (v0->unk_0C == 0) {
            (void)0;
        } else {
            PaletteData_LoadBufferFromHardware(param0->unk_14.palette, PLTTBUF_MAIN_BG, PLTT_DEST(0), 16 * PALETTE_SIZE_BYTES);
        }

        param0->unk_08++;
        break;
    case 4:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 1)) {
            if (v0->unk_0C == 0) {
                VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_250, 1);
                GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            } else {
                VsRecorderViewerProfile_DrawDownloadedPhotoName(param0, v0->unk_230.unk_04);
                PhotoSprite_SetTransformEnabled(v0->unk_228, 1);
                GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
                GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
            }

            param0->unk_08++;
        }
        break;
    default:
        v0->unk_0C ^= 1;
        VsRecorderViewerProfile_DrawMessageWindow(param0, 121 + v0->unk_0C);
        VsRecorderViewerMain_SetState(param0, 8);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerProfile_SwitchToPhotoView(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        if (v0->unk_0C == 0) {
            VsRecorderViewerProfile_RemoveNameWindow(param0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        } else {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerList_FreeProfile(&v0->unk_250, param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
        }

        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 1)) {
            if (v0->unk_0C == 0) {
                if (v0->unk_228) {
                    PhotoSprite_Free(v0->unk_228);
                    VsRecorderViewerMain_InitBg2(param0);
                    Bg_SetPriority(BG_LAYER_MAIN_2, 0);
                    v0->unk_228 = NULL;
                    VsRecorderViewerProfile_ResetClipWindow();
                }

                Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
                Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
                GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            }

            param0->unk_08++;
        }
        break;
    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_0C == 0) {
            GlobalTerminal_DeserializeDressUpPhoto(&v0->unk_230.unk_0C[v0->unk_230.unk_04]->photo, v0->unk_230.photo);
            v0->unk_228 = PhotoSprite_CreateForDressUp(&v0->unk_218, v0->unk_230.photo);
            PhotoSprite_SetTransformEnabled(v0->unk_228, 0);
            VsRecorderViewerProfile_SetPhotoClipWindow();
            VsRecorderViewerList_LoadBgTilemap(param0, 35, 3);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
        } else {
            GlobalTerminal_DeserializePlayerProfile(&v0->unk_230.unk_0C[v0->unk_230.unk_04]->profile, v0->unk_250.profile);
            VsRecorderViewerList_InitProfile(&v0->unk_250, param0);
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_250, 0);
            VsRecorderViewerList_LoadBgTilemap(param0, 80, 3);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->unk_08++;
        break;
    case 3:
        if (v0->unk_0C == 0) {
            PaletteData_LoadBufferFromHardware(param0->unk_14.palette, PLTTBUF_MAIN_BG, PLTT_DEST(0), 16 * PALETTE_SIZE_BYTES);
        } else {
            (void)0;
        }

        param0->unk_08++;
        break;
    case 4:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 1)) {
            if (v0->unk_0C == 0) {
                VsRecorderViewerProfile_DrawDownloadedPhotoName(param0, v0->unk_230.unk_04);
                PhotoSprite_SetTransformEnabled(v0->unk_228, 1);
                GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
                GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
            } else {
                VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_250, 1);
                GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            }

            param0->unk_08++;
        }
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 8);
        break;
    }

    return 0;
}

static void VsRecorderViewerProfile_RemoveMessageWindow(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    Window_ClearAndCopyToVRAM(&v0->unk_D0[0]);
    Window_Remove(&v0->unk_D0[0]);
}

static void VsRecorderViewerProfile_DrawMessageWindow(VsRecorderState *param0, int param1)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    int v3;

    v1 = &v0->unk_D0[0];

    Window_FillTilemap(v1, 0x0);

    v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, param1);
    v3 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v3, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);
}

static void VsRecorderViewerProfile_CreateMessageWindow(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;
    Window *v1;
    int v2 = 1;

    v1 = &v0->unk_D0[0];
    Window_Init(v1);
    Window_Add(param0->unk_14.bgConfig, v1, 6, 8, 3, 16, 2, 14, v2);

    VsRecorderViewerProfile_DrawMessageWindow(param0, 121);
}

static void VsRecorderViewerProfile_VBlankCallback(void *param0)
{
    VsRecorderState *v0 = param0;
    VsRecorderViewerProfile *v1 = v0->unk_860;

    if (v1->unk_228) {
        PhotoSprite_UpdateGraphics(v1->unk_228);
    }

    VramTransfer_Process();
    PaletteData_CommitFadedBuffers(v0->unk_14.palette);
    Bg_RunScheduledUpdates(v0->unk_14.bgConfig);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void VsRecorderViewerProfile_SetPhotoClipWindow(void)
{
    GX_SetVisibleWnd(GX_WNDMASK_W0);
    G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
    G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
    G2_SetWnd0Position(9 * 8, 2 * 8, 9 * 8 + 14 * 8, 2 * 8 + 16 * 8);
}

static void VsRecorderViewerProfile_ResetClipWindow(void)
{
    GX_SetVisibleWnd(GX_WNDMASK_NONE);
    GXS_SetVisibleWnd(GX_WNDMASK_NONE);
}

static void VsRecorderViewerProfile_SetArrowSpritesVisible(VsRecorderState *param0, int param1)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    if (param1 == 0) {
        ManagedSprite_SetDrawFlag(v0->unk_198[1].sprite, 1);
        FontOAM_SetDrawFlag(v0->unk_198[1].fontOAM, 1);
        ManagedSprite_SetPositionXY(v0->unk_198[0].sprite, 32, 232);
    } else {
        ManagedSprite_SetDrawFlag(v0->unk_198[1].sprite, 0);
        FontOAM_SetDrawFlag(v0->unk_198[1].fontOAM, 0);
        ManagedSprite_SetPositionXY(v0->unk_198[0].sprite, 80, 232);
    }

    FontOAM_SetXY(v0->unk_198[0].fontOAM, 36, -8);
    FontOAM_SetXY(v0->unk_198[1].fontOAM, 36, -8);
}

static void VsRecorderViewerProfile_CreateArrowSprites(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    VsRecorderViewerMenu_LoadSpriteResourceSetA(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    v0->unk_198[0].sprite = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);
    v0->unk_198[1].sprite = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    VsRecorderViewerMenu_InitLabelOAM(&v0->unk_198[0], &param0->unk_14, NNS_G2D_VRAM_TYPE_2DSUB);
    VsRecorderViewerMenu_InitLabelOAM(&v0->unk_198[1], &param0->unk_14, NNS_G2D_VRAM_TYPE_2DSUB);
    VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_198[0], &param0->unk_14, 3);
    VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_198[1], &param0->unk_14, 53);

    ManagedSprite_SetAnim(v0->unk_198[0].sprite, 0);
    ManagedSprite_SetAnim(v0->unk_198[1].sprite, 4);
    ManagedSprite_SetPositionXY(v0->unk_198[0].sprite, 32, 232);
    ManagedSprite_SetPositionXY(v0->unk_198[1].sprite, 128, 232);
    FontOAM_SetXY(v0->unk_198[0].fontOAM, 36, -8);
    FontOAM_SetXY(v0->unk_198[1].fontOAM, 36, -8);
    FontOAM_SetDrawFlag(v0->unk_198[0].fontOAM, 1);
    FontOAM_SetDrawFlag(v0->unk_198[1].fontOAM, 1);

    VsRecorderViewerProfile_SetArrowSpritesVisible(param0, 0);
}

static void VsRecorderViewerProfile_FreeArrowSprites(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_198[0]);
    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_198[1]);

    Sprite_DeleteAndFreeResources(v0->unk_198[0].sprite);
    Sprite_DeleteAndFreeResources(v0->unk_198[1].sprite);

    VsRecorderViewerMenu_FreeCursorSpriteResources(param0);
}

static void VsRecorderViewerProfile_DrawLocalPhotoName(VsRecorderState *param0)
{
    Window *v0;
    String *v1;
    String *v2;
    String *v3;
    StringTemplate *v4;
    VsRecorderViewerProfile *v5 = param0->unk_860;
    u16 word;
    u32 v7;
    int v8, v9;

    if (Window_IsInUse(&v5->unk_10[0]) == 1) {
        return;
    }

    v0 = &v5->unk_10[0];
    Window_Init(v0);
    Window_Add(param0->unk_14.bgConfig, v0, 2, 16, 19, 16, 4, 14, 300);
    Window_FillTilemap(v0, 0x00);

    v4 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
    v3 = String_Init(255, HEAP_ID_102);
    v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 56);

    v1 = String_Init(255, HEAP_ID_102);
    DressUpPhoto_SetTrainerName(v5->photo, v1);
    VsRecorderViewerList_CheckNameChars(param0, v1);
    word = DressUpPhoto_GetTitleWord(v5->photo);

    StringTemplate_SetString(v4, 0, v1, 0, 1, GAME_LANGUAGE);
    StringTemplate_SetEasyChatWord(v4, 1, word);
    StringTemplate_Format(v4, v3, v2);

    v7 = String_NumLines(v3);
    for (v8 = 0; v8 < v7; v8++) {
        String_CopyLineNum(v1, v3, v8);
        v9 = (128 - Font_CalcStringWidth(0, v1, 0)) / 2;
        Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, v9, 16 * v8, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    }

    Window_ScheduleCopyToVRAM(v0);

    String_Free(v1);
    String_Free(v2);
    String_Free(v3);
    StringTemplate_Free(v4);
}

static void VsRecorderViewerProfile_DrawDownloadedPhotoName(VsRecorderState *param0, int param1)
{
    Window *v0;
    String *v1;
    String *v2;
    String *v3;
    StringTemplate *v4;
    VsRecorderViewerProfile *v5 = param0->unk_860;
    u16 word;
    u32 v7;
    int v8, v9;

    if (Window_IsInUse(&v5->unk_10[0]) == 1) {
        return;
    }

    v0 = &v5->unk_10[0];
    Window_Init(v0);
    Window_Add(param0->unk_14.bgConfig, v0, 2, 16, 19, 16, 4, 14, 300);
    Window_FillTilemap(v0, 0x00);

    v4 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
    v3 = String_Init(255, HEAP_ID_102);
    v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 56);

    v1 = String_Init(255, HEAP_ID_102);
    DressUpPhoto_SetTrainerName(v5->unk_230.photo, v1);
    VsRecorderViewerList_CheckNameChars(param0, v1);
    word = DressUpPhoto_GetTitleWord(v5->unk_230.photo);

    StringTemplate_SetString(v4, 0, v1, 0, 1, GAME_LANGUAGE);
    StringTemplate_SetEasyChatWord(v4, 1, word);
    StringTemplate_Format(v4, v3, v2);

    v7 = String_NumLines(v3);
    for (v8 = 0; v8 < v7; v8++) {
        String_CopyLineNum(v1, v3, v8);
        v9 = (128 - Font_CalcStringWidth(0, v1, 0)) / 2;
        Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, v1, v9, 16 * v8, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    }

    Window_ScheduleCopyToVRAM(v0);

    String_Free(v1);
    String_Free(v2);
    String_Free(v3);
    StringTemplate_Free(v4);
}

static BOOL VsRecorderViewerProfile_CategoryHasSeenSpecies(VsRecorderState *param0, int param1)
{
    BOOL v0 = 0;
    u16 *v1;
    int v2;
    int v3;
    int v4;
    int pokedexLength;
    VsRecorderViewerProfile *v6 = param0->unk_860;

    v4 = sVsRecorderViewerProfileCategoryOffsets[param1 + 1];
    v3 = sVsRecorderViewerProfileCategoryOffsets[param1];
    v2 = v4 - v3;
    v1 = VsRecorderViewerList_LoadPokedexAlphabetical(102, 0, &pokedexLength);

    {
        int v7;
        int v8 = 0;
        BOOL v9;
        Pokedex *pokedex = SaveData_GetPokedex(param0->saveData);

        for (v7 = v3; v7 < v4; v7++) {
            v9 = Pokedex_HasSeenSpecies(pokedex, v1[v7]);

            if (v9 == 0) {
                v1[v7] = 0xFFFF;
            }
        }

        v8 = 0;

        for (v7 = v3; v7 < v4; v7++) {
            if (v1[v7] != 0xFFFF) {
                v0 = 1;
                break;
            }
        }

        Heap_Free(v1);
    }

    return v0;
}

static void VsRecorderViewerProfile_BuildSpeciesList(VsRecorderState *param0, int param1)
{
    u16 *v0;
    int v1;
    int v2;
    int v3;
    VsRecorderViewerProfile *v4 = param0->unk_860;

    v3 = sVsRecorderViewerProfileCategoryOffsets[param1 + 1];
    v2 = sVsRecorderViewerProfileCategoryOffsets[param1];
    v1 = v3 - v2;

    v4->unk_1D4.pokedex = VsRecorderViewerList_LoadPokedexAlphabetical(102, 0, &v4->unk_1D4.pokedexCount);
    v0 = VsRecorderViewerList_LoadPokedexAlphabetical(102, 0, &v4->unk_1D4.pokedexCount);

    {
        int v5;
        int v6 = 0;
        BOOL v7;
        Pokedex *v8 = SaveData_GetPokedex(param0->saveData);

        v4->unk_1D4.entryCount = 0;

        for (v5 = v2; v5 < v3; v5++) {
            v7 = Pokedex_HasSeenSpecies(v8, v0[v5]);

            if (v7 == 0) {
                v0[v5] = 0xFFFF;
            } else {
                v4->unk_1D4.entryCount++;
            }
        }

        v6 = 0;

        for (v5 = v2; v5 < v3; v5++) {
            if (v0[v5] == 0xFFFF) {
                continue;
            }

            v4->unk_1D4.pokedex[v6] = v0[v5];
            v6++;
        }

        for (v5 = v6; v5 < v4->unk_1D4.pokedexCount; v5++) {
            v4->unk_1D4.pokedex[v5] = v0[v5];
        }

        Heap_Free(v0);

        v4->unk_1E8 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerListEntry) * v4->unk_1D4.entryCount);
        MI_CpuFill8(v4->unk_1E8, 0, sizeof(VsRecorderViewerListEntry) * v4->unk_1D4.entryCount);

        for (v5 = 0; v5 < v4->unk_1D4.entryCount; v5++) {
            v4->unk_1E8[v5].messageID = v4->unk_1D4.pokedex[v5];
            v4->unk_1E8[v5].value = v4->unk_1D4.pokedex[v5];
        }
    }
    v4->unk_1D4.messageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_SPECIES_NAME, HEAP_ID_102);
    v4->unk_1D4.active = 1;
}

static void VsRecorderViewerProfile_FreeSpeciesList(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    MessageLoader_Free(v0->unk_1D4.messageLoader);
    Heap_Free(v0->unk_1E8);
    Heap_Free(v0->unk_1D4.pokedex);

    v0->unk_1D4.active = 0;
}

static void VsRecorderViewerProfile_CategoryTouchHandler(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerProfile *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }
    if (VsRecorderViewerProfile_CategoryHasSeenSpecies(v0, param0) == 0) {
        Sound_PlayEffect(SEQ_SE_PL_BREC58_sseq);
        return;
    }

    VsRecorderViewerProfile_BuildSpeciesList(v0, param0);
}

static void VsRecorderViewerProfile_DrawCategoryWindows(VsRecorderState *param0)
{
    String *v0;
    Window *v1;
    VsRecorderViewerProfile *v2 = param0->unk_860;

    int v3;
    int v4 = 1;
    u8 v5, v6, v7, v8;
    int v9, v10;

    for (v3 = 0; v3 < 9u; v3++) {
        v1 = &v2->unk_D0[v3];
        v5 = sVsRecorderViewerRecord_TouchRectsPokedexGrid[v3].rect.left / 8;
        v6 = sVsRecorderViewerRecord_TouchRectsPokedexGrid[v3].rect.top / 8;
        v7 = sVsRecorderViewerRecord_TouchRectsPokedexGrid[v3].rect.right / 8 - v5;
        v8 = sVsRecorderViewerRecord_TouchRectsPokedexGrid[v3].rect.bottom / 8 - v6;
        Window_Init(v1);
        Window_Add(param0->unk_14.bgConfig, v1, 6, v5, v6, v7, v8, 14, v4);
        Window_FillTilemap(v1, 0x00);
        v0 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 68 + v3);
        v9 = VsRecorderViewerList_CalcCenteredTextX(v1, v0);
        v10 = (8 * v8 - 16) / 2;
        if (VsRecorderViewerProfile_CategoryHasSeenSpecies(param0, v3) == 1) {
            Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v0, v9, v10, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        } else {
            Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v0, v9, v10, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(12, 11, 0), NULL);
        }

        Window_ScheduleCopyToVRAM(v1);
        String_Free(v0);
        v4 += v7 * v8;
    }
}

static void VsRecorderViewerProfile_RemoveCategoryWindows(VsRecorderState *param0)
{
    u32 v0;
    Window *v1;
    VsRecorderViewerProfile *v2 = param0->unk_860;

    for (v0 = 0; v0 < 9; v0++) {
        v1 = &v2->unk_D0[v0];
        Window_ClearAndCopyToVRAM(v1);
        Window_Remove(v1);
    }
}

static void VsRecorderViewerProfile_RemoveNameWindow(VsRecorderState *param0)
{
    VsRecorderViewerProfile *v0 = param0->unk_860;

    if (Window_IsInUse(&v0->unk_10[0]) == 1) {
        Window_ClearAndCopyToVRAM(&v0->unk_10[0]);
        Window_Remove(&v0->unk_10[0]);
    }
}

void VsRecorderViewerProfile_ProfilePhotoCallback(void *param0, const VsRecorderViewerTransferStatus *param1)
{
    VsRecorderState *v0 = param0;
    VsRecorderViewerProfile *v1 = v0->unk_860;

    if (param1->done == 1) {
        (void)0;
    } else {
        (void)0;
    }
}

void VsRecorderViewerProfile_ProfileCallback(void *param0, const VsRecorderViewerTransferStatus *param1)
{
    VsRecorderState *v0 = param0;
    VsRecorderViewerProfile *v1 = v0->unk_860;

    if (param1->done == 1) {
        (void)0;
    } else {
        v1->unk_2E4 = GlobalTerminalGds_GetProfilePhotoList(VsRecorderViewerTransfer_GetTransfer(v0), v1->unk_230.unk_0C, 5);
    }
}
