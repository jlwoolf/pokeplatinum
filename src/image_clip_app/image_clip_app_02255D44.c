#include "image_clip_app/image_clip_app_02255D44.h"

#include <nitro.h>
#include <string.h>

#include "generated/trainer_score_events.h"

#include "struct_defs/dress_up_photo.h"
#include "struct_defs/struct_02029C88.h"
#include "struct_defs/struct_dress_up_app_data.h"
#include "struct_defs/struct_02095C60.h"
#include "struct_defs/visual_competition_app_args.h"

#include "image_clip_app/image_clip_app.h"
#include "image_clip_app/image_clip_app_02255094.h"
#include "image_clip_app/image_clip_app_022578F4.h"
#include "image_clip_app/image_clip_app_02257F50.h"
#include "image_clip_app/image_clip_app_022588F0.h"
#include "image_clip_app/image_clip_app_0225894C.h"
#include "image_clip_app/image_clip_app_022589E0.h"
#include "image_clip_app/image_clip_app_02259098.h"
#include "image_clip_app/image_clip_app_02259484.h"
#include "image_clip_app/image_clip_app_02259560.h"
#include "image_clip_app/image_clip_app_022597BC.h"
#include "image_clip_app/image_clip_app_02259C58.h"
#include "image_clip_app/image_clip_app_0225A428.h"
#include "image_clip_app/image_clip_app_0225AF44.h"
#include "image_clip_app/struct_image_clip_app_02254DE0.h"
#include "image_clip_app/struct_image_clip_app_02255CB8.h"
#include "image_clip_app/struct_image_clip_app_02256BAC.h"
#include "image_clip_app/struct_image_clip_app_02257964.h"
#include "image_clip_app/struct_image_clip_app_02257F50.h"
#include "image_clip_app/struct_image_clip_app_02258470.h"
#include "image_clip_app/struct_image_clip_app_0225899C.h"
#include "image_clip_app/struct_image_clip_app_02258A48.h"
#include "image_clip_app/struct_image_clip_app_02259484.h"
#include "image_clip_app/struct_image_clip_app_02259560.h"
#include "image_clip_app/struct_image_clip_app_022596B0.h"
#include "image_clip_app/struct_image_clip_app_022597BC.h"
#include "image_clip_app/struct_image_clip_app_022599A0.h"
#include "image_clip_app/struct_image_clip_app_02259C58.h"
#include "image_clip_app/struct_image_clip_app_02259D2C.h"
#include "image_clip_app/struct_image_clip_app_0225A0E4.h"
#include "image_clip_app/struct_image_clip_app_0225A428.h"
#include "image_clip_app/struct_image_clip_app_0225AF68.h"
#include "image_clip_app/struct_image_clip_app_0225B388.h"

#include "bg_window.h"
#include "brightness_controller.h"
#include "font.h"
#include "game_options.h"
#include "game_records.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "pokemon.h"
#include "render_text.h"
#include "render_window.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task_extensions.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "touch_pad.h"
#include "trainer_info.h"
#include "image_clips.h"
#include "comm_tool.h"
#include "contest_util.h"
#include "contest_comm.h"
#include "yes_no_touch_menu.h"

typedef struct {
    ImageClipGraphics unk_00;
    FashionCaseCounts unk_1E8;
    ImageClipResourceList unk_3C0;
    ImageClipSpriteManager *unk_3C8;
    PhotoAccessoryRenderer unk_3CC;
    PhotoRenderer unk_458;
    PhotoRendererBg unk_4E0;
    PhotoRendererController unk_4FC;
    ImageClipBg unk_518;
    ImageClipUiMenu unk_544;
    ContestScoreDisplay unk_5C4;
    int unk_70C;
    int unk_710;
    YesNoTouchMenu *unk_714;
    Window *unk_718;
    BOOL unk_71C;
    int unk_720;
    enum PokemonContestRank contestRank;
    int unk_728;
    enum PokemonContestType contestType;
    int unk_730;
    ContestScoringCommState *unk_734;
    const Options *options;
    u32 unk_73C;
    String *unk_740;
    StringTemplate *unk_744;
} VisualCompetitionApp;

typedef struct {
    VisualCompetitionApp *unk_00;
    BOOL *unk_04;
    int unk_08;
    int unk_0C;
} VisualCompetitionAccessoryViewTask;

typedef struct {
    ImageClipSpriteResource *unk_00;
    u32 unk_04;
} VisualCompetitionAccessoryEntry;

typedef struct {
    VisualCompetitionAccessoryEntry unk_00[21];
    int unk_A8;
} VisualCompetitionAccessoryList;

static void VisualCompetition_VBlankCallback(void *param0);
static void VisualCompetition_InitGraphics(VisualCompetitionApp *param0);
static void VisualCompetition_UpdateGraphics(VisualCompetitionApp *param0);
static void VisualCompetition_FreeGraphics(VisualCompetitionApp *param0);
static void VisualCompetition_CreatePhoto(VisualCompetitionApp *param0, Pokemon *param1, int param2, BOOL param3);
static void VisualCompetition_CreatePhotoCentered(VisualCompetitionApp *param0, Pokemon *param1, int param2);
static void VisualCompetition_FreePhoto(VisualCompetitionApp *param0);
static void VisualCompetition_InitAccessoryGrid(VisualCompetitionApp *param0);
static void VisualCompetition_FreeAccessoryGrid(VisualCompetitionApp *param0);
static void VisualCompetition_SetupAccessoryView(VisualCompetitionApp *param0);
static void VisualCompetition_InitImageClip(VisualCompetitionApp *param0, int param1);
static void VisualCompetition_FreeImageClip(VisualCompetitionApp *param0);
static void VisualCompetition_InitPhotoViewerButtons(VisualCompetitionApp *param0);
static void VisualCompetition_InitCompetitionButtons(VisualCompetitionApp *param0);
static void VisualCompetition_ExitButtons(VisualCompetitionApp *param0);
static void VisualCompetition_UpdateButtons(VisualCompetitionApp *param0);
static void VisualCompetition_ResetButtons(VisualCompetitionApp *param0);
static void VisualCompetition_ConfirmAccessorySelection(ImageClipUi *param0, void *param1);
static void VisualCompetition_NextAccessory(ImageClipUi *param0, void *param1);
static void VisualCompetition_PrevAccessory(ImageClipUi *param0, void *param1);
static void VisualCompetition_SelectClothingCategory(ImageClipUi *param0, void *param1);
static void VisualCompetition_SelectAccessoryCategory(ImageClipUi *param0, void *param1);
static void VisualCompetition_InitViewerPanel(VisualCompetitionApp *param0, const Options *options);
static void VisualCompetition_InitContestPanel(VisualCompetitionApp *param0, int param1, int param2, ContestScoringCommState *param3, const Options *options);
static void VisualCompetition_FreePanel(VisualCompetitionApp *param0);
static void VisualCompetition_StartOpenAccessoryView(VisualCompetitionApp *param0, BOOL *param1);
static void VisualCompetition_OpenAccessoryViewTask(SysTask *param0, void *param1);
static void VisualCompetition_StartCloseAccessoryView(VisualCompetitionApp *param0, BOOL *param1);
static void VisualCompetition_CloseAccessoryViewTask(SysTask *param0, void *param1);
static BOOL VisualCompetition_AdvanceSlideAnimation(VisualCompetitionAccessoryViewTask *param0, int param1, int param2, int param3);
static void VisualCompetition_SaveDressUpPhoto(DressUpPhoto *photo, PhotoRenderer *param1, const TrainerInfo *info);
static void VisualCompetition_SaveContestPhoto(ContestPhoto *param0, PhotoRenderer *param1, enum PokemonContestRank contestRank, const TrainerInfo *trainerInfo);
static void VisualCompetition_InitIntroScreen(VisualCompetitionApp *param0);
static void VisualCompetition_ShowStage(VisualCompetitionApp *param0);
static void VisualCompetition_InitConfirmMenu(VisualCompetitionApp *param0);
static void VisualCompetition_ResetConfirmMenu(VisualCompetitionApp *param0);
static u32 VisualCompetition_ProcessConfirmInput(VisualCompetitionApp *param0);
static void VisualCompetition_InitExitConfirmMenu(VisualCompetitionApp *param0);
static u32 VisualCompetition_ProcessExitConfirmInput(VisualCompetitionApp *param0);
static void VisualCompetition_PrintMenuPrompt(VisualCompetitionApp *param0, u32 param1);
static void VisualCompetition_PrintMenuFormattedMessage(VisualCompetitionApp *param0, u32 param1);
static void VisualCompetition_RemoveMenuWindow(VisualCompetitionApp *param0);
static void VisualCompetition_CreateMessageBox(VisualCompetitionApp *param0, u32 param1);
static u32 VisualCompetition_PrintTypedMessage(VisualCompetitionApp *param0, u32 param1);
static void VisualCompetition_SetMessageNumber(VisualCompetitionApp *param0, int param1, int param2);
static void VisualCompetition_FreeMessageString(VisualCompetitionApp *param0);
static void VisualCompetition_DestroyMessageBox(VisualCompetitionApp *param0);
static void VisualCompetition_CreateMessageWindow(VisualCompetitionApp *param0, u32 param1, u8 param2, u8 param3, u8 param4, u8 param5);
static void VisualCompetition_PrintFormattedMessage(VisualCompetitionApp *param0, u32 param1);
static u32 VisualCompetition_PrintMessage(VisualCompetitionApp *param0, u32 param1);
static void VisualCompetition_ClearMessageString(VisualCompetitionApp *param0);
static void VisualCompetition_RemoveMessageWindow(VisualCompetitionApp *param0);
static void VisualCompetition_UpdatePanelFromPhoto(VisualCompetitionApp *param0);
static int VisualCompetition_GetRankValue(enum PokemonContestRank contestRank);
static void VisualCompetition_InitAccessoryList(VisualCompetitionAccessoryList *param0);
static void VisualCompetition_AddAccessoryEntry(VisualCompetitionAccessoryList *param0, ImageClipSpriteResource *param1, u32 param2);
static void VisualCompetition_ResolveAccessoryList(VisualCompetitionAccessoryList *param0);
static ImageClipSpriteResource *VisualCompetition_GetAccessoryEntry(VisualCompetitionAccessoryList *param0, u32 param1);
static BOOL VisualCompetition_IsAccessoryEntryApplied(VisualCompetitionAccessoryList *param0, u32 param1);
static BOOL VisualCompetition_AccessoriesOverlap(VisualCompetitionAccessoryEntry *param0, VisualCompetitionAccessoryEntry *param1);
static void VisualCompetition_AddAccessoriesFromList(VisualCompetitionAccessoryList *param0, ImageClipSpriteResource *param1, u32 param2);
static void VisualCompetition_CheckContestantsReady(VisualCompetitionApp *param0);

int VisualCompetitionApp_Init(ApplicationManager *appMan, int *param1)
{
    VisualCompetitionApp *v0;
    u32 v1;
    DressUpAppData *v2;

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_13, 0x20000);
    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_14, 0x40000);

    v0 = ApplicationManager_NewData(appMan, sizeof(VisualCompetitionApp), HEAP_ID_13);
    memset(v0, 0, sizeof(VisualCompetitionApp));

    SetVBlankCallback(VisualCompetition_VBlankCallback, v0);
    DisableHBlank();

    v2 = ApplicationManager_Args(appMan);
    v0->options = v2->options;
    EnableTouchPad();
    v1 = InitializeTouchPad(4);

    if (v1 != 1) {
        (void)0;
    }

    FashionCaseCounts_Init(v2->fashionCase, &v0->unk_1E8);
    VisualCompetition_InitGraphics(v0);
    ImageClipResourceList_Init(&v0->unk_3C0, 700 + 1 + 18, HEAP_ID_13);

    v0->unk_3C8 = ImageClipSprite_New(700, HEAP_ID_13);

    VisualCompetition_CreatePhoto(v0, v2->pokemon, 10, 0);
    VisualCompetition_InitAccessoryGrid(v0);
    VisualCompetition_InitImageClip(v0, 0);
    VisualCompetition_InitPhotoViewerButtons(v0);
    VisualCompetition_InitViewerPanel(v0, v2->options);
    PhotoRendererController_New(&v0->unk_4FC, &v0->unk_458, &v0->unk_3CC, &v0->unk_00, &v0->unk_5C4, 1);

    v0->unk_714 = YesNoTouchMenu_New(HEAP_ID_13);
    v0->unk_718 = Window_New(HEAP_ID_13, 1);
    v0->unk_70C = 0;

    Sound_SetSceneAndPlayBGM(SOUND_SCENE_SUB_53, SEQ_NONE, 0);

    return 1;
}

int VisualCompetitionApp_Main(ApplicationManager *appMan, int *param1)
{
    VisualCompetitionApp *v0 = ApplicationManager_Data(appMan);
    int v1 = 0;
    DressUpAppData *v2 = ApplicationManager_Args(appMan);

    switch (*param1) {
    case 0:
    case 1:
        StartScreenFade(FADE_MAIN_THEN_SUB, FADE_TYPE_UNK_5, FADE_TYPE_UNK_5, COLOR_BLACK, 6, 1, HEAP_ID_13);
        (*param1) = 2;
        break;
    case 2:
        if (IsScreenFadeDone()) {
            (*param1)++;
        }
        break;
    case 3:
        if (v2->speedUpOnTouch == 1) {
            RenderControlFlags_SetSpeedUpOnTouch(TRUE);

            v0->unk_73C = ContestScoreDisplay_DrawMessageWithString(&v0->unk_5C4, 26, 385, 47);
            (*param1)++;
        } else {
            (*param1) = 6;
        }
        break;
    case 4:
        if (Text_IsPrinterActive(v0->unk_73C) == 0) {
            ContestScoreDisplay_FreeMessageString(&v0->unk_5C4);
            (*param1)++;
        }
        break;
    case 5:
        if ((gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B)) | (gSystem.touchPressed)) {
            ContestScoreDisplay_DrawMessage(&v0->unk_5C4, 26, 385, 48);
            RenderControlFlags_SetSpeedUpOnTouch(FALSE);
            (*param1)++;
        }
        break;
    case 6:
        if (v0->unk_70C == 3) {
            VisualCompetition_StartOpenAccessoryView(v0, &v0->unk_710);

            (*param1) = 7;
        }

        PhotoRendererController_UpdateInput(&v0->unk_4FC);
        VisualCompetition_UpdatePanelFromPhoto(v0);
        ContestScoreDisplay_CommitScore(&v0->unk_5C4);
        VisualCompetition_UpdateButtons(v0);
        break;
    case 7:
        if (v0->unk_710) {
            v0->unk_710 = 0;
            (*param1) = 8;
            v0->unk_70C = 4;
            PhotoRendererBg_Init(&v0->unk_4E0, &v0->unk_458, 14);
        }
        break;
    case 8:
        if (v0->unk_70C == 9) {
            VisualCompetition_StartCloseAccessoryView(v0, &v0->unk_710);
            (*param1) = 10;
            break;
        }

        if (v0->unk_70C == 8) {
            (*param1) = 9;
            v0->unk_70C = 5;
            VisualCompetition_InitExitConfirmMenu(v0);
            break;
        }

        v0->unk_70C = VisualCompetition_ProcessConfirmInput(v0);
        PhotoRendererBg_Update(&v0->unk_4E0);

        break;
    case 9:
        if (v0->unk_70C == 6) {
            v0->unk_71C = 1;
            (*param1) = 11;
            break;
        }

        if (v0->unk_70C == 7) {
            v0->unk_71C = 0;
            (*param1) = 11;
            break;
        }

        v0->unk_70C = VisualCompetition_ProcessExitConfirmInput(v0);
        PhotoRendererBg_Update(&v0->unk_4E0);
        break;
    case 10:
        if (v0->unk_710) {
            v0->unk_710 = 0;
            (*param1) = 6;
            v0->unk_70C = 0;

            PhotoRendererBg_Free(&v0->unk_4E0);
        }
        break;
    case 11:
        StartScreenFade(FADE_MAIN_THEN_SUB, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_13);
        (*param1)++;
        break;
    case 12:
        if (IsScreenFadeDone()) {
            (*param1) = 0;
            v0->unk_70C = 10;
            v1 = 1;
            PhotoRendererBg_Free(&v0->unk_4E0);
        }
        break;
    }

    VisualCompetition_UpdateGraphics(v0);
    return v1;
}

int VisualCompetitionApp_Exit(ApplicationManager *appMan, int *param1)
{
    VisualCompetitionApp *v0 = ApplicationManager_Data(appMan);
    u32 v1;
    DressUpAppData *v2 = ApplicationManager_Args(appMan);

    if (v0->unk_71C == 1) {
        GameRecords_IncrementTrainerScore(v2->records, TRAINER_SCORE_EVENT_UNK_07);
        VisualCompetition_SaveDressUpPhoto(v2->photo, &v0->unk_458, v2->trainerInfo);
    }

    if (v2->appResult != NULL) {
        if (v0->unk_71C == 1) {
            *v2->appResult = 1;
        } else {
            *v2->appResult = 0;
        }
    }

    YesNoTouchMenu_Free(v0->unk_714);
    Windows_Delete(v0->unk_718, 1);

    VisualCompetition_FreePanel(v0);
    PhotoRendererController_Free(&v0->unk_4FC);
    VisualCompetition_ExitButtons(v0);
    VisualCompetition_FreeImageClip(v0);
    VisualCompetition_FreePhoto(v0);
    VisualCompetition_FreeAccessoryGrid(v0);
    ImageClipSprite_Free(v0->unk_3C8);

    v0->unk_3C8 = NULL;

    ImageClipResourceList_Free(&v0->unk_3C0);
    VisualCompetition_FreeGraphics(v0);

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    v1 = DisableTouchPad();
    GF_ASSERT(v1 == 1);

    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_13);
    Heap_Destroy(HEAP_ID_14);

    return 1;
}

int VisualCompetition_Init(ApplicationManager *appMan, int *param1)
{
    VisualCompetitionApp *v0;
    u32 v1;
    VisualCompetitionAppArgs *appArgs;

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_13, 0x20000);
    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_14, 0x40000);

    v0 = ApplicationManager_NewData(appMan, sizeof(VisualCompetitionApp), HEAP_ID_13);
    memset(v0, 0, sizeof(VisualCompetitionApp));

    SetVBlankCallback(VisualCompetition_VBlankCallback, v0);
    DisableHBlank();

    appArgs = ApplicationManager_Args(appMan);

    v0->contestRank = appArgs->contestRank;
    v0->unk_728 = appArgs->competitionType;
    v0->contestType = appArgs->contestType;
    v0->unk_730 = appArgs->npcPhotoPreset;
    v0->unk_734 = appArgs->scoringCommState;

    EnableTouchPad();
    v1 = InitializeTouchPad(4);

    if (v1 != 1) {
        (void)0;
    }

    FashionCaseCounts_Init(appArgs->fashionCase, &v0->unk_1E8);
    VisualCompetition_InitGraphics(v0);

    SpriteList_SetActive(v0->unk_00.unk_44, 0);
    NetworkIcon_Init();
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_32K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    ImageClipResourceList_Init(&v0->unk_3C0, 700 + 1 + 18, HEAP_ID_13);

    v0->unk_3C8 = ImageClipSprite_New(700, HEAP_ID_13);
    v0->options = appArgs->options;

    if (v0->unk_734->isLinkContest == 0) {
        v0->unk_720 = VisualCompetition_GetRankValue(appArgs->contestRank);
    } else {
        v0->unk_720 = 20;
    }

    VisualCompetition_CreatePhotoCentered(v0, appArgs->mon, v0->unk_720);
    VisualCompetition_InitAccessoryGrid(v0);
    VisualCompetition_InitImageClip(v0, 0);
    VisualCompetition_InitCompetitionButtons(v0);
    VisualCompetition_InitContestPanel(v0, v0->unk_720, appArgs->npcPhotoPreset, appArgs->scoringCommState, appArgs->options);
    PhotoRendererController_New(&v0->unk_4FC, &v0->unk_458, &v0->unk_3CC, &v0->unk_00, &v0->unk_5C4, 0);

    v0->unk_714 = YesNoTouchMenu_New(HEAP_ID_13);
    v0->unk_718 = Window_New(HEAP_ID_13, 1);
    v0->unk_70C = 0;

    SetLockTextWithAutoScroll(v0->unk_734->isLinkContest);

    return 1;
}

int VisualCompetition_Main(ApplicationManager *appMan, int *param1)
{
    VisualCompetitionApp *v0 = ApplicationManager_Data(appMan);
    int v1 = 0;
    int v2;

    switch (*param1) {
    case 0:
        Sound_FadeOutBGM(127 / 3, 30);
        (*param1)++;
        break;
    case 1:
        if (Sound_IsFadeActive() == FALSE) {
            (*param1)++;
        }
        break;
    case 2:
        VisualCompetition_InitIntroScreen(v0);
        VisualCompetition_SetMessageNumber(v0, 0, v0->unk_720);

        if (v0->unk_728 != 3) {
            v0->unk_73C = VisualCompetition_PrintTypedMessage(v0, 26);
        } else {
            v0->unk_73C = VisualCompetition_PrintTypedMessage(v0, 28);
        }

        (*param1)++;
        break;
    case 3:

        if (Text_IsPrinterActive(v0->unk_73C) == 0) {
            VisualCompetition_FreeMessageString(v0);
            (*param1)++;
        }
        break;
    case 4:
        v0->unk_73C = VisualCompetition_PrintTypedMessage(v0, 29 + v0->unk_730);
        (*param1)++;
        break;
    case 5:
        if (Text_IsPrinterActive(v0->unk_73C) == 0) {
            VisualCompetition_FreeMessageString(v0);
            (*param1)++;
        }
        break;
    case 6:
        if (v0->unk_728 != 3) {
            v0->unk_73C = VisualCompetition_PrintTypedMessage(v0, 42);
        } else {
            v0->unk_73C = VisualCompetition_PrintTypedMessage(v0, 41);
        }

        (*param1)++;
        break;
    case 7:
        if (Text_IsPrinterActive(v0->unk_73C) == 0) {
            VisualCompetition_FreeMessageString(v0);
            (*param1)++;
        }
        break;
    case 8:
        if (v0->unk_734->isLinkContest) {
            CommTiming_StartSync(2);
        }
        (*param1)++;
        break;
    case 9:
        if (v0->unk_734->isLinkContest) {
            if (CommTiming_IsSyncState(2)) {
                (*param1)++;
            }
        } else {
            (*param1)++;
        }
        break;
    case 10:
        VisualCompetition_ShowStage(v0);
        Sound_PlayEffect(SEQ_SE_DP_CON_016_sseq);
        (*param1)++;
        break;
    case 11:
        StartScreenFade(FADE_MAIN_THEN_SUB, FADE_TYPE_CIRCLE_IN, FADE_TYPE_TOP_HALF_CIRCLE_IN, COLOR_BLACK, 6, 1, HEAP_ID_13);
        (*param1)++;
        break;
    case 12:
        if (IsScreenFadeDone()) {
            Sound_SetSceneAndPlayBGM(SOUND_SCENE_7, SEQ_CO_DRESS_sseq, 0);
            (*param1)++;
        }
        break;
    case 13:
        if (v0->unk_70C == 3) {
            ContestComm_SendFinished(v0->unk_734, 1);

            if (v0->unk_734->isLinkContest) {
                ContestScoreDisplay_DrawMessage(&v0->unk_5C4, 26, 385, 46);
            }

            (*param1) = 14;
            break;
        }

        v2 = ContestScoreDisplay_GetScore(&v0->unk_5C4);

        if (0 == v2) {
            (*param1) = 15;
            Sound_PlayEffect(SEQ_SE_DP_MAZYO_sseq);
        }

        PhotoRendererController_UpdateInput(&v0->unk_4FC);
        VisualCompetition_UpdatePanelFromPhoto(v0);
        ContestScoreDisplay_CommitScore(&v0->unk_5C4);
        VisualCompetition_UpdateButtons(v0);
        break;
    case 14:
        v2 = ContestScoreDisplay_GetScore(&v0->unk_5C4);

        if (0 == v2) {
            (*param1) = 15;
            Sound_PlayEffect(SEQ_SE_DP_MAZYO_sseq);
        }

        VisualCompetition_UpdatePanelFromPhoto(v0);
        ContestScoreDisplay_CommitScore(&v0->unk_5C4);
        VisualCompetition_CheckContestantsReady(v0);
        break;
    case 15:
        ContestScoreDisplay_CommitScore(&v0->unk_5C4);

        if (ContestScoreDisplay_IsScoreAnimationDone(&v0->unk_5C4)) {
            (*param1) = 19;
        }
        break;
    case 19:
        if (Sound_IsEffectPlaying(1664) == 1) {
            break;
        }

        StartScreenFade(FADE_MAIN_THEN_SUB, FADE_TYPE_UNK_26, FADE_TYPE_UNK_26, COLOR_BLACK, 6, 1, HEAP_ID_13);
        Sound_PlayEffect(SEQ_SE_DP_CON_017_sseq);
        (*param1)++;
        break;
    case 20:
        if (IsScreenFadeDone()) {
            (*param1) = 0;
            v0->unk_70C = 10;
            v1 = 1;

            GX_SetVisibleWnd(GX_WNDMASK_NONE);
            PhotoRenderer_MoveSprites(&v0->unk_458, -(8 * 8), 5 * 8);
        }
        break;
    }

    VisualCompetition_UpdateGraphics(v0);

    return v1;
}

int VisualCompetition_Exit(ApplicationManager *appMan, int *param1)
{
    VisualCompetitionApp *v0 = ApplicationManager_Data(appMan);
    u32 v1;
    VisualCompetitionAppArgs *appArgs = ApplicationManager_Args(appMan);

    VisualCompetition_SaveContestPhoto(appArgs->photo, &v0->unk_458, v0->contestRank, appArgs->trainerInfo);

    YesNoTouchMenu_Free(v0->unk_714);
    Windows_Delete(v0->unk_718, 1);

    VisualCompetition_FreePanel(v0);
    PhotoRendererController_Free(&v0->unk_4FC);
    VisualCompetition_ExitButtons(v0);
    VisualCompetition_FreeImageClip(v0);
    VisualCompetition_FreePhoto(v0);
    VisualCompetition_FreeAccessoryGrid(v0);
    ImageClipSprite_Free(v0->unk_3C8);

    v0->unk_3C8 = NULL;

    ImageClipResourceList_Free(&v0->unk_3C0);
    VisualCompetition_FreeGraphics(v0);

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    v1 = DisableTouchPad();
    GF_ASSERT(v1 == 1);

    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_13);
    Heap_Destroy(HEAP_ID_14);
    LockTextSpeed();
    NetworkIcon_Destroy();

    return 1;
}

static void VisualCompetition_InitGraphics(VisualCompetitionApp *param0)
{
    ImageClipGraphicsTemplates v0;

    ImageClipGraphics_Init();
    ImageClipGraphics_InitManager(&param0->unk_00);
    ImageClipGraphics_LoadImageResources(&param0->unk_00, &v0);
    ImageClipGraphics_LoadTemplates(&param0->unk_00, &v0);
    ImageClipGraphics_FreeResourceTemplates(&v0);
}

static void VisualCompetition_UpdateGraphics(VisualCompetitionApp *param0)
{
    ImageClipGraphics_Render(&param0->unk_00);
}

static void VisualCompetition_FreeGraphics(VisualCompetitionApp *param0)
{
    ImageClipGraphics_FreeAllSprites(&param0->unk_00);
    ImageClipGraphics_FreeManager(&param0->unk_00);
    ImageClipGraphics_Free();
}

static void VisualCompetition_CreatePhoto(VisualCompetitionApp *param0, Pokemon *mon, int param2, BOOL param3)
{
    PhotoRendererTemplate v0;

    v0.unk_00 = param0->unk_00.unk_00;
    v0.unk_04 = param0->unk_00.unk_04;
    v0.unk_08 = param0->unk_00.unk_10;
    v0.unk_0C = param0->unk_00.unk_30;
    v0.unk_10 = param0->unk_00.unk_20;
    v0.unk_14 = param0->unk_00.unk_40;
    v0.unk_20 = param2;
    v0.unk_18 = param0->unk_3C8;
    v0.unk_1C = &param0->unk_3C0;

    PhotoRenderer_Init(&param0->unk_458, &v0);

    {
        PokemonSpriteTemplate v1;

        if (param3 == 0) {
            PhotoRenderer_CreatePokemonSprite(&param0->unk_458, mon, &v1, 14);
        } else {
            PhotoRenderer_CreatePokemonSpriteExact(&param0->unk_458, mon, &v1, 14);
        }

        ImageClipPokemonSprite_LoadDecryptedSprite(&param0->unk_00, &v1);
    }

    PhotoRenderer_AssignZOrder(&param0->unk_458);
    PhotoRenderer_LoadBackground(&param0->unk_458, 0, HEAP_ID_14);
}

static void VisualCompetition_CreatePhotoCentered(VisualCompetitionApp *param0, Pokemon *mon, int param2)
{
    int v0, v1;
    ImageClipPixelBounds v2;

    VisualCompetition_CreatePhoto(param0, mon, param2, 1);
    ImageClipPokemonSprite_GetSize(&param0->unk_458.unk_2C.unk_4C, &v0, &v1);
    ImageClipPokemonSprite_GetPixelBounds(&param0->unk_458.unk_2C.unk_4C, &v2);
    ImageClipPokemonSprite_SetPosition(&param0->unk_458.unk_2C.unk_4C, 192, (16 + 129) - ((v1 / 2) - v2.unk_03) + -4);
}

static void VisualCompetition_FreePhoto(VisualCompetitionApp *param0)
{
    PhotoRenderer_FreeBackground(&param0->unk_458);
    PhotoRenderer_ClearSprites(&param0->unk_458);
    PhotoRenderer_Free(&param0->unk_458);
}

static void VisualCompetition_InitAccessoryGrid(VisualCompetitionApp *param0)
{
    PhotoAccessoryRendererResources v0;

    v0.unk_00 = param0->unk_00.unk_00;
    v0.unk_04 = param0->unk_00.unk_04;
    v0.unk_08 = param0->unk_00.unk_10;
    v0.unk_0C = param0->unk_00.unk_30;
    v0.unk_10 = param0->unk_00.unk_40;
    v0.unk_28 = &param0->unk_1E8;
    v0.unk_14 = param0->unk_3C8;
    v0.unk_18 = &param0->unk_3C0;
    v0.unk_1C = 14;
    v0.unk_20 = (18 / 9) + ((18 % 9) ? 1 : 0);
    v0.unk_24 = 1;

    PhotoAccessoryRenderer_Init(&param0->unk_3CC, &v0);
    PhotoAccessoryRenderer_SetSelectionImmediate(&param0->unk_3CC, 0, 0);

    {
        int v3;

        for (int i = 0; i < 100; i++) {
            v3 = FashionCaseCounts_GetAccessoryCount(&param0->unk_1E8, i);

            for (int v2 = 0; v2 < v3; v2++) {
                PhotoAccessoryRenderer_AddItem(&param0->unk_3CC, 0, i);
            }
        }

        for (int i = 0; i < 18; i++) {
            v3 = FashionCaseCounts_GetBackdropCount(&param0->unk_1E8, i);

            if (v3 < 18) {
                PhotoAccessoryRenderer_AddItem(&param0->unk_3CC, 1, v3);
            }
        }

        PhotoAccessoryRenderer_UpdateZOrder(&param0->unk_3CC);
    }
}

static void VisualCompetition_FreeAccessoryGrid(VisualCompetitionApp *param0)
{
    PhotoAccessoryRenderer_FreeBackground(&param0->unk_3CC);
    PhotoAccessoryRenderer_ClearItems(&param0->unk_3CC);
    PhotoAccessoryRenderer_Free(&param0->unk_3CC);
}

static void VisualCompetition_SetupAccessoryView(VisualCompetitionApp *param0)
{
    G2_SetBG0Priority(1);
    G2_SetBG1Priority(0);
    G2_SetBG2Priority(2);
    G2_SetBG3Priority(3);

    Bg_SetOffset(param0->unk_00.unk_40, 3, 3, -16);

    PhotoAccessoryRenderer_LoadBackground(&param0->unk_3CC, 0);
    PhotoAccessoryRenderer_ScrollBackground(&param0->unk_3CC, 0, 2, 0, NULL);
}

static void VisualCompetition_VBlankCallback(void *param0)
{
    VisualCompetitionApp *v0 = param0;
    ImageClipGraphics_Update(&v0->unk_00);
}

static void VisualCompetition_InitImageClip(VisualCompetitionApp *param0, int param1)
{
    ImageClipBgTemplate v0;

    v0.unk_00 = param0->unk_00.unk_40;
    v0.narcID = NARC_INDEX_GRAPHIC__IMAGECLIP;
    v0.unk_08 = (param1) * 2 + 121;
    v0.unk_0C = 133;
    v0.unk_10 = (param1) * 2 + 121 + 1;
    v0.unk_14 = 0;
    v0.unk_18 = 0;
    v0.unk_1C = 1;
    v0.unk_20 = 1;
    v0.unk_24 = 2;
    v0.unk_28 = 0;
    v0.heapID = HEAP_ID_14;

    ImageClipBg_Init(&param0->unk_518, &v0);
}

static void VisualCompetition_FreeImageClip(VisualCompetitionApp *param0)
{
    ImageClipBg_Free(&param0->unk_518);
}

static void VisualCompetition_InitPhotoViewerButtons(VisualCompetitionApp *param0)
{
    ImageClipUi_InitMenu(&param0->unk_544, &param0->unk_00);
    ImageClipUi_SetElementCallback(&param0->unk_544, 0, VisualCompetition_NextAccessory, param0, 0);
    ImageClipUi_SetElementCallback(&param0->unk_544, 1, VisualCompetition_PrevAccessory, param0, 0);
    ImageClipUi_SetElementCallback(&param0->unk_544, 2, VisualCompetition_SelectClothingCategory, param0, 0);
    ImageClipUi_SetElementCallback(&param0->unk_544, 3, VisualCompetition_SelectAccessoryCategory, param0, 0);
    ImageClipUi_SetElementCallback(&param0->unk_544, 4, VisualCompetition_ConfirmAccessorySelection, param0, 0);
}

static void VisualCompetition_InitCompetitionButtons(VisualCompetitionApp *param0)
{
    ImageClipUi_InitMenu(&param0->unk_544, &param0->unk_00);
    ImageClipUi_SetElementCallback(&param0->unk_544, 0, VisualCompetition_NextAccessory, param0, 0);
    ImageClipUi_SetElementCallback(&param0->unk_544, 1, VisualCompetition_PrevAccessory, param0, 0);
    ImageClipUi_SetElementCallback(&param0->unk_544, 2, VisualCompetition_SelectClothingCategory, param0, 0);
    ImageClipUi_SetElementCallback(&param0->unk_544, 3, VisualCompetition_SelectAccessoryCategory, param0, 0);
    ImageClipUi_SetElementCallback(&param0->unk_544, 4, VisualCompetition_ConfirmAccessorySelection, param0, 0);
}

static void VisualCompetition_ExitButtons(VisualCompetitionApp *param0)
{
    ImageClipUi_FreeMenu(&param0->unk_544, &param0->unk_00);
}

static void VisualCompetition_UpdateButtons(VisualCompetitionApp *param0)
{
    ImageClipUi_HandleTouch(&param0->unk_544);
}

static void VisualCompetition_ResetButtons(VisualCompetitionApp *param0)
{
    ImageClipUi_ResetSelection(&param0->unk_544);
}

static void VisualCompetition_ConfirmAccessorySelection(ImageClipUi *param0, void *param1)
{
    VisualCompetitionApp *v0 = param1;

    if (PhotoAccessoryRenderer_IsIdle(&v0->unk_3CC) == 0) {
        return;
    }

    v0->unk_70C = 3;
}

static void VisualCompetition_NextAccessory(ImageClipUi *param0, void *param1)
{
    VisualCompetitionApp *v0 = param1;
    int v1 = PhotoAccessoryRenderer_GetGroup(&v0->unk_3CC);
    PhotoAccessoryRenderer_ScrollSelection(&v0->unk_3CC, v1, 0);
}

static void VisualCompetition_PrevAccessory(ImageClipUi *param0, void *param1)
{
    VisualCompetitionApp *v0 = param1;
    int v1 = PhotoAccessoryRenderer_GetGroup(&v0->unk_3CC);
    PhotoAccessoryRenderer_ScrollSelection(&v0->unk_3CC, v1, 1);
}

static void VisualCompetition_SelectClothingCategory(ImageClipUi *param0, void *param1)
{
    VisualCompetitionApp *v0 = param1;

    if (v0->unk_70C != 0) {
        int v1 = PhotoAccessoryRenderer_GetIndex(&v0->unk_3CC, 0);

        PhotoAccessoryRenderer_SetSelectionImmediate(&v0->unk_3CC, 0, v1);
        v0->unk_70C = 0;
    }
}

static void VisualCompetition_SelectAccessoryCategory(ImageClipUi *param0, void *param1)
{
    VisualCompetitionApp *v0 = param1;
    int v1;
    int v2;

    if (v0->unk_70C != 1) {
        v1 = PhotoAccessoryRenderer_GetIndex(&v0->unk_3CC, 1);
        PhotoAccessoryRenderer_SetSelectionImmediate(&v0->unk_3CC, 1, v1);

        v0->unk_70C = 1;
    }
}

static void VisualCompetition_InitViewerPanel(VisualCompetitionApp *param0, const Options *options)
{
    ContestScoreDisplayTemplate v0;

    memset(&v0, 0, sizeof(ContestScoreDisplayTemplate));

    v0.unk_00 = param0->unk_00.unk_40;
    v0.unk_04 = param0->unk_00.unk_44;
    v0.unk_08 = param0->unk_00.unk_48;
    v0.unk_10 = 10;
    v0.options = options;
    v0.unk_24 = param0->unk_00.unk_5C;

    ContestScoreDisplay_Init(&param0->unk_5C4, &v0, 1 | 2 | 4 | 8);
}

static void VisualCompetition_InitContestPanel(VisualCompetitionApp *param0, int param1, int param2, ContestScoringCommState *param3, const Options *options)
{
    ContestScoreDisplayTemplate v0;
    BOOL v1;

    v0.unk_00 = param0->unk_00.unk_40;
    v0.unk_04 = param0->unk_00.unk_44;
    v0.unk_08 = param0->unk_00.unk_48;
    v0.unk_10 = param1;
    v0.unk_14 = 385;
    v0.unk_18 = 7 + param2;
    v0.unk_1C = 60;
    v0.unk_20 = param3;
    v0.options = options;
    v0.unk_24 = param0->unk_00.unk_5C;

    ContestScoreDisplay_Init(&param0->unk_5C4, &v0, 1 | 2 | 4 | 8 | 16 | 32);
}

static void VisualCompetition_FreePanel(VisualCompetitionApp *param0)
{
    ContestScoreDisplay_Free(&param0->unk_5C4);
}

static void VisualCompetition_StartOpenAccessoryView(VisualCompetitionApp *param0, BOOL *param1)
{
    SysTask *v0 = SysTask_StartAndAllocateParam(VisualCompetition_OpenAccessoryViewTask, sizeof(VisualCompetitionAccessoryViewTask), 10, 13);
    VisualCompetitionAccessoryViewTask *v1 = SysTask_GetParam(v0);
    v1->unk_00 = param0;
    v1->unk_04 = param1;
    v1->unk_08 = 0;
    v1->unk_0C = 0;
}

static void VisualCompetition_OpenAccessoryViewTask(SysTask *param0, void *param1)
{
    VisualCompetitionAccessoryViewTask *v0 = param1;
    BOOL v1;

    switch (v0->unk_0C) {
    case 0:
        v1 = PhotoAccessoryRenderer_SetSelection(&v0->unk_00->unk_3CC, 3, 0);
        GF_ASSERT(v1);
        v0->unk_0C++;
        break;
    case 1:
        v1 = PhotoAccessoryRenderer_IsIdle(&v0->unk_00->unk_3CC);

        if (v1) {
            v0->unk_0C++;
        }
        break;
    case 2:
        BrightnessController_StartTransition(8, -16, 0, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG3, BRIGHTNESS_MAIN_SCREEN);
        v0->unk_0C++;
        break;
    case 3:
        v1 = BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN);

        if (v1) {
            v0->unk_0C++;
        }
        break;
    case 4:
        ImageClipUi_MoveMenu(&v0->unk_00->unk_544, 0, 8);
        v0->unk_08++;

        if (v0->unk_08 >= 8) {
            v0->unk_08 = 0;
            v0->unk_0C++;
        }
        break;
    case 5:
        if (VisualCompetition_AdvanceSlideAnimation(v0, -8, 5, 8)) {
            v0->unk_08 = 0;
            v0->unk_0C++;
        }
        break;
    case 6:
        VisualCompetition_InitImageClip(v0->unk_00, 1);
        Bg_ScheduleScroll(v0->unk_00->unk_00.unk_40, 1, 3, 0);
        VisualCompetition_InitConfirmMenu(v0->unk_00);
        v0->unk_0C++;
        break;
    case 7:
        BrightnessController_StartTransition(8, 0, -16, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG3, BRIGHTNESS_MAIN_SCREEN);
        v0->unk_0C++;
        break;
    case 8:
        v1 = BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN);

        if (v1) {
            v0->unk_0C++;
        }
        break;
    case 9:
        *v0->unk_04 = 1;
        SysTask_FinishAndFreeParam(param0);
        break;
    default:
        break;
    }
}

static void VisualCompetition_StartCloseAccessoryView(VisualCompetitionApp *param0, BOOL *param1)
{
    SysTask *v0 = SysTask_StartAndAllocateParam(VisualCompetition_CloseAccessoryViewTask, sizeof(VisualCompetitionAccessoryViewTask), 10, 13);
    VisualCompetitionAccessoryViewTask *v1 = SysTask_GetParam(v0);

    v1->unk_00 = param0;
    v1->unk_04 = param1;
    v1->unk_08 = 0;
    v1->unk_0C = 0;
}

static void VisualCompetition_CloseAccessoryViewTask(SysTask *param0, void *param1)
{
    VisualCompetitionAccessoryViewTask *v0 = param1;
    BOOL v1;

    switch (v0->unk_0C) {
    case 0:
        BrightnessController_StartTransition(8, -16, 0, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG3, BRIGHTNESS_MAIN_SCREEN);
        v0->unk_0C++;
        break;
    case 1:
        v1 = BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN);

        if (v1) {
            v0->unk_0C++;
        }
        break;
    case 2:
        VisualCompetition_ResetConfirmMenu(v0->unk_00);
        VisualCompetition_SetupAccessoryView(v0->unk_00);
        VisualCompetition_ResetButtons(v0->unk_00);
        VisualCompetition_InitImageClip(v0->unk_00, 0);
        Bg_ScheduleScroll(v0->unk_00->unk_00.unk_40, 1, 3, -(5 * 8));
        v0->unk_0C++;
        break;
    case 3:
        if (VisualCompetition_AdvanceSlideAnimation(v0, 8, -5, 8)) {
            v0->unk_08 = 0;
            v0->unk_0C++;
        }
        break;
    case 4:
        ImageClipUi_MoveMenu(&v0->unk_00->unk_544, 0, -8);
        v0->unk_08++;

        if (v0->unk_08 >= 8) {
            v0->unk_08 = 0;
            v0->unk_0C++;
        }
        break;
    case 5:
        BrightnessController_StartTransition(8, 0, -16, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG3, BRIGHTNESS_MAIN_SCREEN);
        v0->unk_0C++;
        break;
    case 6:
        v1 = BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN);

        if (v1) {
            v0->unk_0C++;
        }
        break;
    case 7:
        v1 = PhotoAccessoryRenderer_SetSelection(&v0->unk_00->unk_3CC, 0, 0);
        GF_ASSERT(v1);
        v0->unk_0C++;
        break;
    case 8:
        v1 = PhotoAccessoryRenderer_IsIdle(&v0->unk_00->unk_3CC);

        if (v1) {
            v0->unk_0C++;
        }
        break;
    case 9:
        *v0->unk_04 = 1;
        SysTask_FinishAndFreeParam(param0);
        break;
    default:
        break;
    }
}

static void VisualCompetition_SaveDressUpPhoto(DressUpPhoto *photo, PhotoRenderer *param1, const TrainerInfo *info)
{
    ImageClipSpriteResource *v0;
    int v1;
    String *name;
    int gender;

    DressUpPhoto_Init(photo);
    DressUpPhoto_SetPhotoMonFromSprite(photo, param1->unk_2C.unk_4C.unk_0C, &param1->unk_2C.unk_4C);

    if (info != NULL) {
        name = TrainerInfo_NameNewString(info, HEAP_ID_13);
        gender = TrainerInfo_Gender(info);
        DressUpPhoto_SetTrainerNameAndGender(photo, name, gender);
        String_Free(name);
    }

    v1 = 0;
    v0 = param1->unk_00.unk_14.unk_08;

    while (v0 != &param1->unk_00.unk_14) {
        if (v0->unk_04 == 0) {
            DressUpPhoto_AddAccessory(photo, v0->unk_00, v1);
            v1++;
        }

        v0 = v0->unk_08;
    }

    v0 = param1->unk_00.unk_04.unk_08;

    while (v0 != &param1->unk_00.unk_04) {
        if (v0->unk_04 == 0) {
            DressUpPhoto_AddAccessory(photo, v0->unk_00, v1);
            v1++;
        }

        v0 = v0->unk_08;
    }

    DressUpPhoto_SetBackdrop(photo, param1->unk_2C.unk_48);
    DressUpPhoto_SetLanguageAndMagic(photo);
}

static void VisualCompetition_SaveContestPhoto(ContestPhoto *param0, PhotoRenderer *param1, enum PokemonContestRank contestRank, const TrainerInfo *trainerInfo)
{
    int v0;
    int v1;
    VisualCompetitionAccessoryList *v2;
    ImageClipSpriteResource *v3;
    String *name;
    int gender;

    v2 = Heap_Alloc(HEAP_ID_13, sizeof(VisualCompetitionAccessoryList));
    VisualCompetition_InitAccessoryList(v2);

    ContestPhoto_SetPhotoMonFromSprite(param0, param1->unk_2C.unk_4C.unk_0C, &param1->unk_2C.unk_4C);

    if (trainerInfo) {
        name = TrainerInfo_NameNewString(trainerInfo, 13);
        gender = TrainerInfo_Gender(trainerInfo);
        ContestPhoto_SetTrainerNameAndGender(param0, name, gender);
        String_Free(name);
    }

    VisualCompetition_AddAccessoriesFromList(v2, &param1->unk_00.unk_14, 1);
    VisualCompetition_AddAccessoriesFromList(v2, &param1->unk_00.unk_04, 0);
    VisualCompetition_ResolveAccessoryList(v2);

    v0 = 0;

    for (v1 = 0; v1 < 21; v1++) {
        if (VisualCompetition_IsAccessoryEntryApplied(v2, v1) == 1) {
            v3 = VisualCompetition_GetAccessoryEntry(v2, v1);
            ContestPhoto_AddAccessory(param0, v3->unk_00, v0);
            v0++;
        }
    }

    ContestPhoto_SetBackdrop(param0, param1->unk_2C.unk_48);
    ContestPhoto_SetContestRank(param0, contestRank);
    ContestPhoto_SetFullMagic(param0);
    Heap_Free(v2);
}

static BOOL VisualCompetition_AdvanceSlideAnimation(VisualCompetitionAccessoryViewTask *param0, int param1, int param2, int param3)
{
    if (param0->unk_08 < 8) {
        PhotoRenderer_MoveSprites(&param0->unk_00->unk_458, param1, param2);
    }

    if (param0->unk_08 >= 1) {
        Bg_ScheduleScroll(param0->unk_00->unk_00.unk_40, 2, 2, param1);
        Bg_ScheduleScroll(param0->unk_00->unk_00.unk_40, 1, 2, param1);
        Bg_ScheduleScroll(param0->unk_00->unk_00.unk_40, 2, 5, param2);
        Bg_ScheduleScroll(param0->unk_00->unk_00.unk_40, 1, 5, param2);
    }

    param0->unk_08++;

    if (param0->unk_08 > param3) {
        return 1;
    }

    return 0;
}

static void VisualCompetition_InitIntroScreen(VisualCompetitionApp *param0)
{
    Bg_ClearTilemap(param0->unk_00.unk_40, 3);
    Bg_SetOffset(param0->unk_00.unk_40, 3, 0, 0);
    Bg_SetOffset(param0->unk_00.unk_40, 3, 3, 0);

    VisualCompetition_CreateMessageBox(param0, 0);

    G2_SetBG0Priority(2);
    G2_SetBG1Priority(1);
    G2_SetBG2Priority(3);
    G2_SetBG3Priority(0);

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    ResetScreenMasterBrightness(DS_SCREEN_MAIN);
}

static void VisualCompetition_ShowStage(VisualCompetitionApp *param0)
{
    VisualCompetition_DestroyMessageBox(param0);

    Bg_ClearTilemap(param0->unk_00.unk_40, 3);

    VisualCompetition_SetupAccessoryView(param0);

    SetScreenColorBrightness(DS_SCREEN_MAIN, COLOR_BLACK);
    SpriteList_SetActive(param0->unk_00.unk_44, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void VisualCompetition_InitConfirmMenu(VisualCompetitionApp *param0)
{
    YesNoTouchMenuParams v0;

    Bg_ClearTilemap(param0->unk_00.unk_40, 3);
    Bg_SetOffset(param0->unk_00.unk_40, 3, 0, 0);
    Bg_SetOffset(param0->unk_00.unk_40, 3, 3, 0);

    v0.bgConfig = param0->unk_00.unk_40;
    v0.bgLayer = BG_LAYER_MAIN_3;
    v0.baseTile = 0;
    v0.palette = 5;
    v0.tilemapLeft = 25;
    v0.tilemapTop = 4;

    YesNoTouchMenu_InitWithParams(param0->unk_714, &v0);
    VisualCompetition_PrintMenuPrompt(param0, 1);

    G2_SetBG0Priority(2);
    G2_SetBG1Priority(1);
    G2_SetBG2Priority(3);
    G2_SetBG3Priority(0);
}

static void VisualCompetition_ResetConfirmMenu(VisualCompetitionApp *param0)
{
    YesNoTouchMenu_Reset(param0->unk_714);
    VisualCompetition_RemoveMenuWindow(param0);
    Bg_ClearTilemap(param0->unk_00.unk_40, 3);
}

static u32 VisualCompetition_ProcessConfirmInput(VisualCompetitionApp *param0)
{
    u32 v0 = YesNoTouchMenu_ProcessInput(param0->unk_714);

    switch (v0) {
    case YES_NO_TOUCH_MENU_NOTHING_CHOSEN:
        v0 = 4;
        break;
    case YES_NO_TOUCH_MENU_YES:
        v0 = 8;
        break;
    case YES_NO_TOUCH_MENU_NO:
        v0 = 9;
        break;
    }

    return v0;
}

static void VisualCompetition_CreateMessageWindow(VisualCompetitionApp *param0, u32 param1, u8 param2, u8 param3, u8 param4, u8 param5)
{
    MessageLoader *v0;
    String *v1;
    int v2 = Options_Frame(param0->options);

    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(7), HEAP_ID_14);
    Window_Add(param0->unk_00.unk_40, param0->unk_718, 3, param2, param3, param4, param5, 7, 0 + (29 * 4) + (18 + 12));
    Window_FillTilemap(param0->unk_718, 15);
    LoadMessageBoxGraphics(param0->unk_00.unk_40, 3, 0 + (29 * 4), 8, v2, HEAP_ID_14);
    Window_DrawMessageBoxWithScrollCursor(param0->unk_718, 0, 0 + (29 * 4), 8);

    v0 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0385, HEAP_ID_13);
    v1 = MessageLoader_GetNewString(v0, param1);

    Text_AddPrinterWithParamsAndColor(param0->unk_718, FONT_MESSAGE, v1, 0, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    String_Free(v1);
    MessageLoader_Free(v0);
    Window_CopyToVRAM(param0->unk_718);
}

static void VisualCompetition_PrintFormattedMessage(VisualCompetitionApp *param0, u32 param1)
{
    MessageLoader *v0;
    String *v1;
    String *v2;

    Window_FillTilemap(param0->unk_718, 15);

    v0 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0385, HEAP_ID_13);
    v2 = MessageLoader_GetNewString(v0, param1);
    v1 = String_Init(256, HEAP_ID_13);

    StringTemplate_Format(param0->unk_744, v1, v2);
    Text_AddPrinterWithParamsAndColor(param0->unk_718, FONT_MESSAGE, v1, 0, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    String_Free(v1);
    String_Free(v2);
    MessageLoader_Free(v0);
    Window_CopyToVRAM(param0->unk_718);
}

static u32 VisualCompetition_PrintMessage(VisualCompetitionApp *param0, u32 param1)
{
    u32 v0;
    MessageLoader *v1;
    u32 v2;
    String *v3;

    GF_ASSERT(param0->unk_740 == NULL);

    Window_FillTilemap(param0->unk_718, 15);

    v1 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0385, HEAP_ID_13);
    v3 = MessageLoader_GetNewString(v1, param1);
    param0->unk_740 = String_Init(256, HEAP_ID_13);

    StringTemplate_Format(param0->unk_744, param0->unk_740, v3);

    if (param0->unk_734->isLinkContest == 0) {
        v2 = Options_TextFrameDelay(param0->options);
    } else {
        v2 = TEXT_SPEED_FAST;
    }

    v0 = Text_AddPrinterWithParamsAndColor(param0->unk_718, FONT_MESSAGE, param0->unk_740, 0, 0, v2, TEXT_COLOR(1, 2, 15), NULL);

    String_Free(v3);
    MessageLoader_Free(v1);
    Window_CopyToVRAM(param0->unk_718);

    return v0;
}

static void VisualCompetition_ClearMessageString(VisualCompetitionApp *param0)
{
    String_Free(param0->unk_740);
    param0->unk_740 = NULL;
}

static void VisualCompetition_RemoveMessageWindow(VisualCompetitionApp *param0)
{
    Window_ClearAndCopyToVRAM(param0->unk_718);
    Window_Remove(param0->unk_718);
}

static void VisualCompetition_PrintMenuPrompt(VisualCompetitionApp *param0, u32 param1)
{
    VisualCompetition_CreateMessageWindow(param0, param1, 2, 1, 27, 2);
}

static void VisualCompetition_PrintMenuFormattedMessage(VisualCompetitionApp *param0, u32 param1)
{
    VisualCompetition_PrintFormattedMessage(param0, param1);
}

static void VisualCompetition_RemoveMenuWindow(VisualCompetitionApp *param0)
{
    VisualCompetition_RemoveMessageWindow(param0);
}

static void VisualCompetition_CreateMessageBox(VisualCompetitionApp *param0, u32 param1)
{
    VisualCompetition_CreateMessageWindow(param0, param1, 2, 19, 27, 4);
    param0->unk_744 = StringTemplate_Default(HEAP_ID_13);
}

static u32 VisualCompetition_PrintTypedMessage(VisualCompetitionApp *param0, u32 param1)
{
    return VisualCompetition_PrintMessage(param0, param1);
}

static void VisualCompetition_SetMessageNumber(VisualCompetitionApp *param0, int param1, int param2)
{
    StringTemplate_SetNumber(param0->unk_744, param1, param2, 2, 0, 1);
}

static void VisualCompetition_FreeMessageString(VisualCompetitionApp *param0)
{
    VisualCompetition_ClearMessageString(param0);
}

static void VisualCompetition_DestroyMessageBox(VisualCompetitionApp *param0)
{
    VisualCompetition_RemoveMessageWindow(param0);

    StringTemplate_Free(param0->unk_744);
    param0->unk_744 = NULL;
}

static void VisualCompetition_UpdatePanelFromPhoto(VisualCompetitionApp *param0)
{
    int v0 = PhotoRenderer_GetSpriteCount(&param0->unk_458);
    ContestScoreDisplay_SetVisibleIcons(&param0->unk_5C4, v0);
}

static int VisualCompetition_GetRankValue(enum PokemonContestRank contestRank)
{
    int v0;

    switch (contestRank) {
    case CONTEST_RANK_NORMAL:
        v0 = 5;
        break;
    case CONTEST_RANK_GREAT:
        v0 = 10;
        break;
    case CONTEST_RANK_ULTRA:
        v0 = 15;
        break;
    case CONTEST_RANK_MASTER:
        v0 = 20;
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return v0;
}

static void VisualCompetition_InitExitConfirmMenu(VisualCompetitionApp *param0)
{
    YesNoTouchMenuParams v0;

    v0.bgConfig = param0->unk_00.unk_40;
    v0.bgLayer = BG_LAYER_MAIN_3;
    v0.baseTile = 0;
    v0.palette = 5;
    v0.tilemapLeft = 25;
    v0.tilemapTop = 4;

    YesNoTouchMenu_Reset(param0->unk_714);
    YesNoTouchMenu_InitWithParams(param0->unk_714, &v0);

    VisualCompetition_PrintMenuFormattedMessage(param0, 2);

    G2_SetBG0Priority(2);
    G2_SetBG1Priority(1);
    G2_SetBG2Priority(3);
    G2_SetBG3Priority(0);
}

static u32 VisualCompetition_ProcessExitConfirmInput(VisualCompetitionApp *param0)
{
    u32 v0 = YesNoTouchMenu_ProcessInput(param0->unk_714);

    switch (v0) {
    case YES_NO_TOUCH_MENU_NOTHING_CHOSEN:
        v0 = 5;
        break;
    case YES_NO_TOUCH_MENU_YES:
        v0 = 6;
        break;
    case YES_NO_TOUCH_MENU_NO:
        v0 = 7;
        break;
    }

    return v0;
}

static void VisualCompetition_InitAccessoryList(VisualCompetitionAccessoryList *param0)
{
    memset(param0, 0, sizeof(VisualCompetitionAccessoryList));
}

static void VisualCompetition_AddAccessoryEntry(VisualCompetitionAccessoryList *param0, ImageClipSpriteResource *param1, u32 param2)
{
    GF_ASSERT(param1);
    param0->unk_00[param0->unk_A8].unk_00 = param1;
    param0->unk_00[param0->unk_A8].unk_04 = param2;
    param0->unk_A8++;
}

static void VisualCompetition_ResolveAccessoryList(VisualCompetitionAccessoryList *param0)
{
    int v0, v1;
    BOOL v2;

    v0 = 0;

    while (v0 < param0->unk_A8) {
        if (param0->unk_00[v0].unk_04 == 1) {
            for (v1 = 0; v1 < param0->unk_A8; v1++) {
                if (param0->unk_00[v1].unk_04 == 0) {
                    v2 = VisualCompetition_AccessoriesOverlap(
                        &param0->unk_00[v0], &param0->unk_00[v1]);

                    if (v2 == 1) {
                        param0->unk_00[v1].unk_04 = 1;
                    }
                }
            }

            param0->unk_00[v0].unk_04 = 2;

            v0 = 0;
        } else {
            v0++;
        }
    }
}

static ImageClipSpriteResource *VisualCompetition_GetAccessoryEntry(VisualCompetitionAccessoryList *param0, u32 param1)
{
    GF_ASSERT(param1 < 21);
    return param0->unk_00[param1].unk_00;
}

static BOOL VisualCompetition_IsAccessoryEntryApplied(VisualCompetitionAccessoryList *param0, u32 param1)
{
    GF_ASSERT(param1 < 21);

    if (param0->unk_00[param1].unk_04) {
        return 1;
    }

    return 0;
}

static BOOL VisualCompetition_AccessoriesOverlap(VisualCompetitionAccessoryEntry *param0, VisualCompetitionAccessoryEntry *param1)
{
    int v0[6];
    BOOL v1;
    int v2;
    int v3, v4;

    ImageClipSpriteResource_GetCenter(param0->unk_00, &v0[5], &v0[4]);
    ImageClipSpriteResource_GetBoundingBox(param0->unk_00, &v0[0], &v0[1], &v0[2], &v0[3]);

    for (v2 = 0; v2 < 16; v2++) {
        VisualCompetition_GetGridPoint(v0[0], v0[1], v0[2], v0[3], v2, &v3, &v4);

        v1 = ImageClipSpriteResource_IsHit(param1->unk_00, v3, v4);

        if (v1 == 1) {
            return 1;
        }
    }

    return 0;
}

static void VisualCompetition_AddAccessoriesFromList(VisualCompetitionAccessoryList *param0, ImageClipSpriteResource *param1, u32 param2)
{
    ImageClipSpriteResource *v0 = param1->unk_08;

    while (v0 != param1) {
        if (v0->unk_04 == 0) {
            VisualCompetition_AddAccessoryEntry(param0, v0, param2);
        }

        v0 = v0->unk_08;
    }
}

static void VisualCompetition_CheckContestantsReady(VisualCompetitionApp *param0)
{
    int v0;
    int v1 = 0;

    if (param0->unk_734->isLinkContest == 0) {
        ContestScoreDisplay_SetScoreTimer(&param0->unk_5C4, 0);
        return;
    }

    if (param0->unk_734->leaderContestantID == param0->unk_734->netID) {
        for (v0 = 0; v0 < 4; v0++) {
            if (param0->unk_734->receivedValues[v0] == 1) {
                v1++;
            }
        }

        if (param0->unk_734->connectionCount <= v1) {
            ContestScoreDisplay_SetScoreTimer(&param0->unk_5C4, 0);
        }
    }
}

void VisualCompetition_GetGridPoint(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, int *param5, int *param6)
{
    u32 v0, v1;
    u32 v2, v3;

    v0 = param2 + ((param3 - param2) / 3);
    v1 = param2 + ((param3 - param2) / 3) * 2;
    v2 = param0 + ((param1 - param0) / 3);
    v3 = param0 + ((param1 - param0) / 3) * 2;

    switch (param4) {
    case 0:
        *param5 = param2;
        *param6 = param0;
        break;
    case 1:
        *param5 = param2;
        *param6 = v2;
        break;
    case 2:
        *param5 = param2;
        *param6 = v3;
        break;
    case 3:
        *param5 = param2;
        *param6 = param1;
        break;
    case 4:
        *param5 = v0;
        *param6 = param0;
        break;
    case 5:
        *param5 = v0;
        *param6 = v2;
        break;
    case 6:
        *param5 = v0;
        *param6 = v3;
        break;
    case 7:
        *param5 = v0;
        *param6 = param1;
        break;
    case 8:
        *param5 = v1;
        *param6 = param0;
        break;
    case 9:
        *param5 = v1;
        *param6 = v2;
        break;
    case 10:
        *param5 = v1;
        *param6 = v3;
        break;
    case 11:
        *param5 = v1;
        *param6 = param1;
        break;
    case 12:
        *param5 = param3;
        *param6 = param0;
        break;
    case 13:
        *param5 = param3;
        *param6 = v2;
        break;
    case 14:
        *param5 = param3;
        *param6 = v3;
        break;
    case 15:
        *param5 = param3;
        *param6 = param1;
        break;
    }
}
