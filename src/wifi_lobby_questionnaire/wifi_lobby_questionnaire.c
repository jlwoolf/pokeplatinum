#include "wifi_lobby_questionnaire/wifi_lobby_questionnaire.h"

#include <dwc.h>
#include <nitro.h>
#include <ppwlobby/ppw_lobby.h>
#include <string.h>

#include "constants/graphics.h"

#include "overlay066/ov66_0222DDF0.h"
#include "overlay066/ov66_02231428.h"
#include "overlay066/ov66_022324F0.h"
#include "overlay066/struct_ov66_0222DFF8_decl.h"
#include "overlay066/struct_ov66_0222E908.h"
#include "overlay066/struct_ov66_02231374.h"
#include "wifi_lobby_questionnaire/struct_wifi_lobby_questionnaire_answer_tally.h"

#include "bg_window.h"
#include "char_transfer.h"
#include "font.h"
#include "game_options.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "menu.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "pltt_transfer.h"
#include "render_oam.h"
#include "render_window.h"
#include "save_player.h"
#include "savedata.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "system.h"
#include "text.h"
#include "trainer_info.h"
#include "vram_transfer.h"
#include "wifi_plaza_question_data.h"

typedef struct {
    u32 questionNo;
    u32 questionSerialNo;
    BOOL isSpecialWeek;
    BOOL isFreeQuestion;
    String *questionText;
    String *answerTexts[3];
} WiFiLobbyQuestionnaireQuestion;

typedef struct {
    Window window[1];
    s32 selectedAnswer;
    Sprite *cursorSprite;
    SpriteResource *spriteResources[4];
    u16 state;
    u16 returnState;
    WiFiLobbyQuestionnaireQuestion question;
} WiFiLobbyQuestionnaireAnswerSelection;

typedef struct {
    Window windows[6];
    u16 state;
    u16 returnState;
    s32 animationTimer;
    s32 barPositions[3];
    s32 barTargets[3];
    void *charDataRaw;
    NNSG2dCharacterData *charData;
    WiFiLobbyQuestionnaireQuestion currentQuestion;
    WiFiLobbyQuestionnaireQuestion lastQuestion;
    WiFiLobbyQuestionnaireAnswerTally currentTally;
    WiFiLobbyQuestionnaireAnswerTally lastTally;
} WiFiLobbyQuestionnaireResults;

typedef union {
    WiFiLobbyQuestionnaireAnswerSelection answerSelection;
    WiFiLobbyQuestionnaireResults results;
} WiFiLobbyQuestionnaireScreen;

typedef struct {
    u32 printer;
    s32 textFrameDelay;
    Window window;
    String *string;
    void *waitDial;
    Menu *menu;
} WiFiLobbyQuestionnaireMessageBox;

typedef struct {
    MessageLoader *loaders[9];
    StringTemplate *template;
    String *string1;
    String *string2;
    UnkStruct_ov66_0222DFF8 *profile;
} WiFiLobbyQuestionnaireMessages;

typedef struct {
    BgConfig *bgConfig;
    SpriteList *spriteList;
    G2dRenderer renderer;
    SpriteResourceCollection *spriteResources[4];
    NARC *narc;
} WiFiLobbyQuestionnaireGraphics;

typedef struct {
    WiFiLobbyQuestionnaireGraphics graphics;
    WiFiLobbyQuestionnaireMessages messages;
    WiFiLobbyQuestionnaireScreen screen;
    WiFiLobbyQuestionnaireMessageBox messageBox;
} WiFiLobbyQuestionnaire;

static void WiFiLobbyQuestionnaire_VBlankCallback(void *param0);
static void WiFiLobbyQuestionnaireGraphics_Init(WiFiLobbyQuestionnaireGraphics *param0, SaveData *saveData, enum HeapID heapID);
static void WiFiLobbyQuestionnaireGraphics_Free(WiFiLobbyQuestionnaireGraphics *param0);
static void WiFiLobbyQuestionnaireGraphics_UpdateSprites(WiFiLobbyQuestionnaireGraphics *param0);
static void WiFiLobbyQuestionnaireGraphics_ProcessVBlank(WiFiLobbyQuestionnaireGraphics *param0);
static void WiFiLobbyQuestionnaireGraphics_InitBackgrounds(WiFiLobbyQuestionnaireGraphics *param0, Options *options, enum HeapID heapID);
static void WiFiLobbyQuestionnaireGraphics_FreeBackgrounds(WiFiLobbyQuestionnaireGraphics *param0);
static void WiFiLobbyQuestionnaireGraphics_InitSpriteSystem(WiFiLobbyQuestionnaireGraphics *param0, enum HeapID heapID);
static void WiFiLobbyQuestionnaireGraphics_FreeSpriteSystem(WiFiLobbyQuestionnaireGraphics *param0);
static void WiFiLobbyQuestionnaireMessages_Init(WiFiLobbyQuestionnaireMessages *param0, UnkStruct_ov66_0222DFF8 *param1, enum HeapID heapID);
static void WiFiLobbyQuestionnaireMessages_Free(WiFiLobbyQuestionnaireMessages *param0);
static String *WiFiLobbyQuestionnaireMessages_GetString(WiFiLobbyQuestionnaireMessages *param0, u32 param1, u32 param2);
static String *WiFiLobbyQuestionnaireMessages_GetQuestionText(WiFiLobbyQuestionnaireMessages *param0, u32 param1);
static String *WiFiLobbyQuestionnaireMessages_GetAnswerText(WiFiLobbyQuestionnaireMessages *param0, u32 param1, u32 param2);
static void WiFiLobbyQuestionnaireMessages_SetPlayerName(WiFiLobbyQuestionnaireMessages *param0, u32 param1, enum HeapID heapID);
static void WiFiLobbyQuestionnaireQuestion_Init(WiFiLobbyQuestionnaireQuestion *param0, BOOL param1, enum HeapID heapID);
static void WiFiLobbyQuestionnaireQuestion_Free(WiFiLobbyQuestionnaireQuestion *param0);
static String *WiFiLobbyQuestionnaireQuestion_GetText(const WiFiLobbyQuestionnaireQuestion *param0, WiFiLobbyQuestionnaireMessages *param1);
static String *WiFiLobbyQuestionnaireQuestion_GetAnswerText(const WiFiLobbyQuestionnaireQuestion *param0, WiFiLobbyQuestionnaireMessages *param1, u32 param2);
static void WiFiLobbyQuestionnaireAnswerTally_Init(WiFiLobbyQuestionnaireAnswerTally *param0);
static u32 WiFiLobbyQuestionnaireAnswerTally_GetBarWidth(const WiFiLobbyQuestionnaireAnswerTally *param0, u32 param1, u32 param2);
static void WiFiLobbyQuestionnaireAnswerTally_CountAnswers(WiFiLobbyQuestionnaireAnswerTally *param0, const UnkStruct_ov66_0222DFF8 *param1);
static void WiFiLobbyQuestionnaireScreen_InitAnswerSelection(WiFiLobbyQuestionnaireScreen *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, UnkStruct_ov66_02231374 *param3, u32 param4);
static BOOL WiFiLobbyQuestionnaireScreen_MainAnswerSelection(WiFiLobbyQuestionnaireScreen *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, WiFiLobbyQuestionnaireMessageBox *param3, UnkStruct_ov66_02231374 *param4, enum HeapID heapID);
static void WiFiLobbyQuestionnaireScreen_FreeAnswerSelection(WiFiLobbyQuestionnaireScreen *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2);
static void WiFiLobbyQuestionnaireAnswerSelection_Init(WiFiLobbyQuestionnaireAnswerSelection *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, u32 param3);
static BOOL WiFiLobbyQuestionnaireAnswerSelection_Main(WiFiLobbyQuestionnaireAnswerSelection *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, WiFiLobbyQuestionnaireMessageBox *param3, UnkStruct_ov66_02231374 *param4, u32 param5);
static void WiFiLobbyQuestionnaireAnswerSelection_Free(WiFiLobbyQuestionnaireAnswerSelection *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2);
static void WiFiLobbyQuestionnaireAnswerSelection_DrawQuestion(WiFiLobbyQuestionnaireAnswerSelection *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2);
static void WiFiLobbyQuestionnaireAnswerSelection_UpdateCursor(WiFiLobbyQuestionnaireAnswerSelection *param0);
static void WiFiLobbyQuestionnaireAnswerSelection_AnimateCursor(WiFiLobbyQuestionnaireAnswerSelection *param0);
static void WiFiLobbyQuestionnaireScreen_InitResults(WiFiLobbyQuestionnaireScreen *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, UnkStruct_ov66_02231374 *param3, u32 param4);
static BOOL WiFiLobbyQuestionnaireScreen_MainResults(WiFiLobbyQuestionnaireScreen *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, WiFiLobbyQuestionnaireMessageBox *param3, UnkStruct_ov66_02231374 *param4, enum HeapID heapID);
static void WiFiLobbyQuestionnaireScreen_FreeResults(WiFiLobbyQuestionnaireScreen *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2);
static void WiFiLobbyQuestionnaireResults_Init(WiFiLobbyQuestionnaireResults *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, UnkStruct_ov66_02231374 *param3, enum HeapID heapID);
static BOOL WiFiLobbyQuestionnaireResults_Main(WiFiLobbyQuestionnaireResults *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, WiFiLobbyQuestionnaireMessageBox *param3, UnkStruct_ov66_02231374 *param4, enum HeapID heapID);
static void WiFiLobbyQuestionnaireResults_Free(WiFiLobbyQuestionnaireResults *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2);
static void WiFiLobbyQuestionnaireResults_DrawHeader(WiFiLobbyQuestionnaireResults *param0, WiFiLobbyQuestionnaireMessages *param1, u32 param2, TextColor param3);
static void WiFiLobbyQuestionnaireResults_DrawQuestion(WiFiLobbyQuestionnaireResults *param0, const WiFiLobbyQuestionnaireQuestion *param1, WiFiLobbyQuestionnaireMessages *param2, WiFiLobbyQuestionnaireGraphics *param3, const UnkStruct_ov66_0222E908 *param4, enum HeapID heapID, u32 param6, u32 param7, BOOL param8);
static void WiFiLobbyQuestionnaireResults_InitBars(WiFiLobbyQuestionnaireResults *param0, const WiFiLobbyQuestionnaireAnswerTally *param1, WiFiLobbyQuestionnaireGraphics *param2, u32 param3);
static BOOL WiFiLobbyQuestionnaireResults_AnimateBars(WiFiLobbyQuestionnaireResults *param0, WiFiLobbyQuestionnaireGraphics *param1);
static void WiFiLobbyQuestionnaireResults_DrawPage(WiFiLobbyQuestionnaireResults *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, u32 param3);
static void WiFiLobbyQuestionnaireMessageBox_Init(WiFiLobbyQuestionnaireMessageBox *param0, WiFiLobbyQuestionnaireGraphics *param1, SaveData *saveData, enum HeapID heapID);
static void WiFiLobbyQuestionnaireMessageBox_Free(WiFiLobbyQuestionnaireMessageBox *param0, u32 param1);
static void WiFiLobbyQuestionnaireMessageBox_Print(WiFiLobbyQuestionnaireMessageBox *param0, const String *param1);
static void WiFiLobbyQuestionnaireMessageBox_PrintInstant(WiFiLobbyQuestionnaireMessageBox *param0, const String *param1);
static void WiFiLobbyQuestionnaireMessageBox_ShowWaitDial(WiFiLobbyQuestionnaireMessageBox *param0);
static void WiFiLobbyQuestionnaireMessageBox_HideWaitDial(WiFiLobbyQuestionnaireMessageBox *param0);
static BOOL WiFiLobbyQuestionnaireMessageBox_IsMessageDone(const WiFiLobbyQuestionnaireMessageBox *param0);
static void WiFiLobbyQuestionnaireMessageBox_Erase(WiFiLobbyQuestionnaireMessageBox *param0);
static void WiFiLobbyQuestionnaireMessageBox_OpenYesNoMenu(WiFiLobbyQuestionnaireMessageBox *param0, WiFiLobbyQuestionnaireGraphics *param1, u32 param2);
static u32 WiFiLobbyQuestionnaireMessageBox_ProcessMenuInput(WiFiLobbyQuestionnaireMessageBox *param0, u32 param1);
static void WiFiLobbyQuestionnaireMessageBox_DestroyMenu(WiFiLobbyQuestionnaireMessageBox *param0, u32 param1);

static const CharTransferTemplate sCharTransferTemplate = {
    0x20,
    0x4000,
    0x0,
    0x7A
};

static const WindowTemplate sYesNoWindowTemplate = {
    0x1,
    0x19,
    0xD,
    0x6,
    0x4,
    0x4,
    0x94
};

static const WindowTemplate sAnswerSelectionWindowTemplate[1] = {
    { 0x2, 0xB, 0x7, 0xF, 0x8, 0x3, 0x1 }
};

static const VecFx32 sCursorPositions[] = {
    { FX32_CONST(72), FX32_CONST(64), 0x0 },
    { FX32_CONST(72), FX32_CONST(88), 0x0 },
    { FX32_CONST(72), FX32_CONST(112), 0x0 }
};

static const WindowTemplate sResultsWindowTemplates[6] = {
    { 0x2, 0x7, 0x1, 0x12, 0x3, 0x3, 0x1 },
    { 0x2, 0x5, 0x5, 0xC, 0x9, 0x3, 0x37 },
    { 0x2, 0x11, 0x5, 0xB, 0x2, 0x4, 0xA3 },
    { 0x2, 0x11, 0x8, 0xB, 0x2, 0x4, 0xB9 },
    { 0x2, 0x11, 0xB, 0xB, 0x2, 0x4, 0xCF },
    { 0x2, 0x3, 0xF, 0x19, 0x2, 0x3, 0xE5 }
};

static const GXBanks sGxBanks = {
    GX_VRAM_BG_256_AB,
    GX_VRAM_BGEXTPLTT_NONE,
    GX_VRAM_SUB_BG_128_C,
    GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_16_G,
    GX_VRAM_OBJEXTPLTT_NONE,
    GX_VRAM_SUB_OBJ_NONE,
    GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE,
    GX_VRAM_TEXPLTT_NONE
};

static const GraphicsModes sGraphicsModes = {
    GX_DISPMODE_GRAPHICS,
    GX_BGMODE_0,
    GX_BGMODE_0,
    GX_BG0_AS_2D
};

static const u32 sBgLayers[4] = {
    0x0,
    0x1,
    0x2,
    0x4
};

static const BgTemplate sBgTemplates[4] = {
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xf800,
        .charBase = GX_BG_CHARBASE_0x08000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x3,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xf000,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x1,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe800,
        .charBase = GX_BG_CHARBASE_0x10000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x2,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xf800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
};

static void (*sScreenInitFuncs[2])(WiFiLobbyQuestionnaireScreen *, WiFiLobbyQuestionnaireMessages *, WiFiLobbyQuestionnaireGraphics *, UnkStruct_ov66_02231374 *, u32) = {
    WiFiLobbyQuestionnaireScreen_InitAnswerSelection,
    WiFiLobbyQuestionnaireScreen_InitResults
};

static BOOL (*sScreenMainFuncs[2])(WiFiLobbyQuestionnaireScreen *, WiFiLobbyQuestionnaireMessages *, WiFiLobbyQuestionnaireGraphics *, WiFiLobbyQuestionnaireMessageBox *, UnkStruct_ov66_02231374 *, enum HeapID) = {
    WiFiLobbyQuestionnaireScreen_MainAnswerSelection,
    WiFiLobbyQuestionnaireScreen_MainResults
};

static void (*sScreenFreeFuncs[2])(WiFiLobbyQuestionnaireScreen *, WiFiLobbyQuestionnaireMessages *, WiFiLobbyQuestionnaireGraphics *) = {
    WiFiLobbyQuestionnaireScreen_FreeAnswerSelection,
    WiFiLobbyQuestionnaireScreen_FreeResults
};

int WiFiLobbyQuestionnaire_Init(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyQuestionnaire *v0;
    UnkStruct_ov66_02231374 *v1 = ApplicationManager_Args(appMan);

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_PARTY_MENU2, 0x50000);

    v0 = ApplicationManager_NewData(appMan, sizeof(WiFiLobbyQuestionnaire), HEAP_ID_PARTY_MENU2);
    memset(v0, 0, sizeof(WiFiLobbyQuestionnaire));

    WiFiLobbyQuestionnaireGraphics_Init(&v0->graphics, v1->saveData, 122);
    WiFiLobbyQuestionnaireMessages_Init(&v0->messages, v1->unk_04, 122);
    WiFiLobbyQuestionnaireMessageBox_Init(&v0->messageBox, &v0->graphics, v1->saveData, 122);

    GF_ASSERT(v1->unk_08 < 2);
    sScreenInitFuncs[v1->unk_08](&v0->screen, &v0->messages, &v0->graphics, v1, 122);

    SetVBlankCallback(WiFiLobbyQuestionnaire_VBlankCallback, v0);
    DisableHBlank();

    return 1;
}

int WiFiLobbyQuestionnaire_Main(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyQuestionnaire *v0;
    UnkStruct_ov66_02231374 *v1;
    BOOL v2;

    v0 = ApplicationManager_Data(appMan);
    v1 = ApplicationManager_Args(appMan);

    switch (*param1) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_PARTY_MENU2);
        ov66_0222E31C(v1->unk_04, 1);
        (*param1)++;
        break;
    case 1:
        v2 = IsScreenFadeDone();

        if (v2 == 1) {
            (*param1)++;
        }
        break;
    case 2:
        if (IsScreenFadeDone() == TRUE) {
            if (ov66_0222E12C(v1->unk_04) == 1) {
                ov66_0222E2A4(v1->unk_04);
                (*param1)++;
                break;
            }

            if (ov66_02231760() == 1) {
                (*param1)++;
                break;
            }
        }

        v2 = sScreenMainFuncs[v1->unk_08](&v0->screen, &v0->messages, &v0->graphics, &v0->messageBox, v1, 122);

        if (v2 == 1) {
            (*param1)++;
        }
        break;
    case 3:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_PARTY_MENU2);
        (*param1)++;
        break;
    case 4:
        v2 = IsScreenFadeDone();

        if (v2 == 1) {
            WiFiLobbyQuestionnaireMessageBox_HideWaitDial(&v0->messageBox);
            return 1;
        }
        break;
    }

    WiFiLobbyQuestionnaireGraphics_UpdateSprites(&v0->graphics);
    return 0;
}

int WiFiLobbyQuestionnaire_Exit(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyQuestionnaire *v0 = ApplicationManager_Data(appMan);
    UnkStruct_ov66_02231374 *v1 = ApplicationManager_Args(appMan);

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    sScreenFreeFuncs[v1->unk_08](&v0->screen, &v0->messages, &v0->graphics);

    WiFiLobbyQuestionnaireMessageBox_Free(&v0->messageBox, 122);
    WiFiLobbyQuestionnaireMessages_Free(&v0->messages);
    WiFiLobbyQuestionnaireGraphics_Free(&v0->graphics);

    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_PARTY_MENU2);
    Sound_StopAllEffects(0);

    return 1;
}

static void WiFiLobbyQuestionnaire_VBlankCallback(void *param0)
{
    WiFiLobbyQuestionnaire *v0 = param0;
    WiFiLobbyQuestionnaireGraphics_ProcessVBlank(&v0->graphics);
}

static void WiFiLobbyQuestionnaireGraphics_Init(WiFiLobbyQuestionnaireGraphics *param0, SaveData *saveData, enum HeapID heapID)
{
    Options *options = SaveData_GetOptions(saveData);
    param0->narc = NARC_ctor(NARC_INDEX_GRAPHIC__WIFI_LOBBY_OTHER, heapID);

    VramTransfer_New(32, heapID);
    GXLayers_SetBanks(&sGxBanks);
    WiFiLobbyQuestionnaireGraphics_InitBackgrounds(param0, options, heapID);
    WiFiLobbyQuestionnaireGraphics_InitSpriteSystem(param0, heapID);
}

static void WiFiLobbyQuestionnaireGraphics_Free(WiFiLobbyQuestionnaireGraphics *param0)
{
    NARC_dtor(param0->narc);
    VramTransfer_Free();

    WiFiLobbyQuestionnaireGraphics_FreeBackgrounds(param0);
    WiFiLobbyQuestionnaireGraphics_FreeSpriteSystem(param0);
}

static void WiFiLobbyQuestionnaireGraphics_UpdateSprites(WiFiLobbyQuestionnaireGraphics *param0)
{
    SpriteList_Update(param0->spriteList);
}

static void WiFiLobbyQuestionnaireGraphics_ProcessVBlank(WiFiLobbyQuestionnaireGraphics *param0)
{
    Bg_RunScheduledUpdates(param0->bgConfig);
    RenderOam_Transfer();
    VramTransfer_Process();
}

static void WiFiLobbyQuestionnaireGraphics_InitBackgrounds(WiFiLobbyQuestionnaireGraphics *param0, Options *options, enum HeapID heapID)
{
    SetAllGraphicsModes(&sGraphicsModes);

    param0->bgConfig = BgConfig_New(heapID);
    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;

    GXLayers_SwapDisplay();

    int i;

    for (i = 0; i < 4; i++) {
        Bg_InitFromTemplate(param0->bgConfig, sBgLayers[i], &sBgTemplates[i], 0);
        Bg_ClearTilesRange(sBgLayers[i], 32, 0, heapID);
        Bg_ClearTilemap(param0->bgConfig, sBgLayers[i]);
    }

    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(4), heapID);

    LoadMessageBoxGraphics(param0->bgConfig, BG_LAYER_MAIN_1, 1, 5, Options_Frame(options), heapID);
    LoadStandardWindowGraphics(param0->bgConfig, BG_LAYER_MAIN_1, 1 + (18 + 12), 6, 0, heapID);

    Graphics_LoadTilesToBgLayer(NARC_INDEX_GRAPHIC__LOBBY_NEWS, 2, param0->bgConfig, 4, 0, 0, 0, heapID);
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_GRAPHIC__LOBBY_NEWS, 6, param0->bgConfig, 4, 0, 0, 0, heapID);
    Graphics_LoadPalette(NARC_INDEX_GRAPHIC__LOBBY_NEWS, 0, 4, 0, 0, heapID);
}

static void WiFiLobbyQuestionnaireGraphics_FreeBackgrounds(WiFiLobbyQuestionnaireGraphics *param0)
{
    {
        int v0;

        for (v0 = 0; v0 < 4; v0++) {
            Bg_FreeTilemapBuffer(param0->bgConfig, sBgLayers[v0]);
        }
    }

    Heap_Free(param0->bgConfig);
}

static void WiFiLobbyQuestionnaireGraphics_InitSpriteSystem(WiFiLobbyQuestionnaireGraphics *param0, enum HeapID heapID)
{
    int v0;

    NNS_G2dInitOamManagerModule();

    RenderOam_Init(0, 126, 0, 31, 0, 126, 0, 31, heapID);
    CharTransfer_InitWithVramModes(&sCharTransferTemplate, GX_OBJVRAMMODE_CHAR_1D_32K, GX_OBJVRAMMODE_CHAR_1D_32K);
    PlttTransfer_Init(32, heapID);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_32K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    param0->spriteList = SpriteList_InitRendering(32, &param0->renderer, heapID);

    for (v0 = 0; v0 < 4; v0++) {
        param0->spriteResources[v0] = SpriteResourceCollection_New(32, v0, heapID);
    }

    NetworkIcon_Init();
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void WiFiLobbyQuestionnaireGraphics_FreeSpriteSystem(WiFiLobbyQuestionnaireGraphics *param0)
{
    int v0;

    SpriteList_Delete(param0->spriteList);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(param0->spriteResources[v0]);
    }

    CharTransfer_Free();
    PlttTransfer_Free();
    RenderOam_Free();
}

static void WiFiLobbyQuestionnaireMessages_Init(WiFiLobbyQuestionnaireMessages *param0, UnkStruct_ov66_0222DFF8 *param1, enum HeapID heapID)
{
    int v0;
    static const v1[9] = {
        673,
        657,
        661,
        654,
        655,
        656,
        658,
        659,
        660,
    };

    param0->profile = param1;

    for (v0 = 0; v0 < 9; v0++) {
        param0->loaders[v0] = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, v1[v0], heapID);
    }

    param0->template = StringTemplate_Default(heapID);
    param0->string1 = String_Init(256, heapID);
    param0->string2 = String_Init(256, heapID);
}

static void WiFiLobbyQuestionnaireMessages_Free(WiFiLobbyQuestionnaireMessages *param0)
{
    int v0;

    for (v0 = 0; v0 < 9; v0++) {
        MessageLoader_Free(param0->loaders[v0]);
    }

    StringTemplate_Free(param0->template);
    String_Free(param0->string1);
    String_Free(param0->string2);
}

static String *WiFiLobbyQuestionnaireMessages_GetString(WiFiLobbyQuestionnaireMessages *param0, u32 param1, u32 param2)
{
    GF_ASSERT(param1 < 9);

    MessageLoader_GetString(param0->loaders[param1], param2, param0->string2);
    StringTemplate_Format(param0->template, param0->string1, param0->string2);

    return param0->string1;
}

static String *WiFiLobbyQuestionnaireMessages_GetQuestionText(WiFiLobbyQuestionnaireMessages *param0, u32 param1)
{
    if (param1 >= (50 + 10)) {
        GF_ASSERT(param1 >= (50 + 10));
        param1 = 0;
    }

    if (param1 < 50) {
        return WiFiLobbyQuestionnaireMessages_GetString(param0, 1, param1);
    }

    return WiFiLobbyQuestionnaireMessages_GetString(param0, 2, param1 - 50);
}

static String *WiFiLobbyQuestionnaireMessages_GetAnswerText(WiFiLobbyQuestionnaireMessages *param0, u32 param1, u32 param2)
{
    if (param1 >= (50 + 10)) {
        GF_ASSERT(param1 >= (50 + 10));
        param1 = 0;
    }

    if (param1 < 50) {
        return WiFiLobbyQuestionnaireMessages_GetString(param0, 3 + param2, param1);
    }

    return WiFiLobbyQuestionnaireMessages_GetString(param0, 6 + param2, param1 - 50);
}

static void WiFiLobbyQuestionnaireMessages_SetPlayerName(WiFiLobbyQuestionnaireMessages *param0, u32 param1, enum HeapID heapID)
{
    TrainerInfo *v0 = TrainerInfo_New(heapID);
    const WiFiPlazaProfile *v1 = ov66_0222E3BC(param0->profile);

    ov66_0222E640(v1, v0, heapID);
    StringTemplate_SetPlayerName(param0->template, param1, v0);
    Heap_Free(v0);
}

static void WiFiLobbyQuestionnaireScreen_InitAnswerSelection(WiFiLobbyQuestionnaireScreen *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, UnkStruct_ov66_02231374 *param3, u32 param4)
{
    WiFiLobbyQuestionnaireAnswerSelection_Init(&param0->answerSelection, param1, param2, param4);
}

static BOOL WiFiLobbyQuestionnaireScreen_MainAnswerSelection(WiFiLobbyQuestionnaireScreen *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, WiFiLobbyQuestionnaireMessageBox *param3, UnkStruct_ov66_02231374 *param4, enum HeapID heapID)
{
    return WiFiLobbyQuestionnaireAnswerSelection_Main(&param0->answerSelection, param1, param2, param3, param4, heapID);
}

static void WiFiLobbyQuestionnaireScreen_FreeAnswerSelection(WiFiLobbyQuestionnaireScreen *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2)
{
    WiFiLobbyQuestionnaireAnswerSelection_Free(&param0->answerSelection, param1, param2);
}

static void WiFiLobbyQuestionnaireAnswerSelection_Init(WiFiLobbyQuestionnaireAnswerSelection *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, u32 param3)
{
    {
        Graphics_LoadPaletteFromOpenNARC(param2->narc, 199, 0, 0, 4 * 32, param3);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param2->narc, 200, param2->bgConfig, 0, 0, 0, 0, param3);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param2->narc, 201, param2->bgConfig, 0, 0, 0, 0, param3);
    }

    {
        BOOL v0;

        param0->spriteResources[0] = SpriteResourceCollection_AddTilesFrom(param2->spriteResources[0], param2->narc, 205, 0, 20, NNS_G2D_VRAM_TYPE_2DMAIN, param3);
        param0->spriteResources[1] = SpriteResourceCollection_AddPaletteFrom(param2->spriteResources[1], param2->narc, 204, 0, 20, NNS_G2D_VRAM_TYPE_2DMAIN, 3, param3);

        v0 = SpriteTransfer_RequestCharAtEnd(param0->spriteResources[0]);
        GF_ASSERT(v0);

        v0 = SpriteTransfer_RequestPlttFreeSpace(param0->spriteResources[1]);
        GF_ASSERT(v0);

        SpriteResource_ReleaseData(param0->spriteResources[0]);
        SpriteResource_ReleaseData(param0->spriteResources[1]);

        param0->spriteResources[2] = SpriteResourceCollection_AddFrom(param2->spriteResources[2], param2->narc, 206, 0, 20, 2, param3);
        param0->spriteResources[3] = SpriteResourceCollection_AddFrom(param2->spriteResources[3], param2->narc, 207, 0, 20, 3, param3);
    }

    {
        SpriteResourcesHeader v1;
        SpriteListTemplate v2 = { 0 };

        SpriteResourcesHeader_Init(&v1, 20, 20, 20, 20, 0xffffffff, 0xffffffff, 0, 0, param2->spriteResources[0], param2->spriteResources[1], param2->spriteResources[2], param2->spriteResources[3], NULL, NULL);

        v2.list = param2->spriteList;
        v2.resourceData = &v1;
        v2.priority = 0;
        v2.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
        v2.heapID = param3;

        param0->cursorSprite = SpriteList_Add(&v2);
        Sprite_SetDrawFlag(param0->cursorSprite, FALSE);
    }

    {
        int v3;

        for (v3 = 0; v3 < 1; v3++) {
            Window_AddFromTemplate(param2->bgConfig, &param0->window[v3], &sAnswerSelectionWindowTemplate[v3]);
        }
    }

    WiFiLobbyQuestionnaireQuestion_Init(&param0->question, 1, param3);
}

static BOOL WiFiLobbyQuestionnaireAnswerSelection_Main(WiFiLobbyQuestionnaireAnswerSelection *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, WiFiLobbyQuestionnaireMessageBox *param3, UnkStruct_ov66_02231374 *param4, u32 param5)
{
    u32 v0;
    String *v1;

    switch (param0->state) {
    case 0:
        v1 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, 94);
        WiFiLobbyQuestionnaireMessageBox_Print(param3, v1);
        param0->returnState = 1;
        param0->state = 10;
        break;
    case 1:
        WiFiLobbyQuestionnaireMessageBox_OpenYesNoMenu(param3, param2, param5);
        param0->state = 2;
        break;
    case 2: {
        u32 v2;

        v2 = WiFiLobbyQuestionnaireMessageBox_ProcessMenuInput(param3, param5);

        switch (v2) {
        case 0:
            param0->state = 3;
            break;
        case 0xfffffffe:
            param0->state = 9;
            break;
        }
    } break;
    case 3:
        if (param0->question.isSpecialWeek == 0) {
            v0 = 92;
        } else {
            v0 = 93;
        }

        v1 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, v0);
        WiFiLobbyQuestionnaireMessageBox_Print(param3, v1);

        param0->returnState = 4;
        param0->state = 10;
        break;
    case 4:
        WiFiLobbyQuestionnaireAnswerSelection_DrawQuestion(param0, param1, param2);

        v1 = WiFiLobbyQuestionnaireQuestion_GetText(&param0->question, param1);
        WiFiLobbyQuestionnaireMessageBox_PrintInstant(param3, v1);
        WiFiLobbyQuestionnaireAnswerSelection_UpdateCursor(param0);
        WiFiLobbyQuestionnaireAnswerSelection_AnimateCursor(param0);

        param0->state = 5;
        break;
    case 5:
        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            Sound_PlayEffect(SE_CONFIRM_sseq_3);
            param0->state++;
            break;
        }

        if (gSystem.pressedKeys & PAD_KEY_UP) {
            if ((param0->selectedAnswer - 1) >= 0) {
                Sound_PlayEffect(SEQ_SE_DP_SELECT78_sseq);
                param0->selectedAnswer--;
            }
        } else if (gSystem.pressedKeys & PAD_KEY_DOWN) {
            if ((param0->selectedAnswer + 1) < 3) {
                Sound_PlayEffect(SEQ_SE_DP_SELECT78_sseq);
                param0->selectedAnswer++;
            }
        }

        WiFiLobbyQuestionnaireAnswerSelection_UpdateCursor(param0);
        break;

    case 6:
        ov66_0222E5D8(param4->unk_04, param0->question.questionSerialNo, param0->selectedAnswer);
        ov66_022333E4(param0->selectedAnswer);

        v1 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, 96);

        WiFiLobbyQuestionnaireMessageBox_PrintInstant(param3, v1);
        WiFiLobbyQuestionnaireMessageBox_ShowWaitDial(param3);
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->state = 7;
        break;
    case 7: {
        u32 v3;
        v3 = ov66_02233434();

        if (v3 != UnkEnum_ov66_02233434_01) {
            Sound_PlayEffect(SEQ_SE_DP_BUTTON9_sseq);
            WiFiLobbyQuestionnaireMessageBox_HideWaitDial(param3);

            v1 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, 97);
            WiFiLobbyQuestionnaireMessageBox_Print(param3, v1);

            param0->returnState = 8;
            param0->state = 10;
        }
    } break;
    case 8:
        if (param0->question.isSpecialWeek == 0) {
            v0 = 98;
        } else {
            v0 = 99;
        }

        v1 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, v0);
        WiFiLobbyQuestionnaireMessageBox_Print(param3, v1);
        param0->returnState = 9;
        param0->state = 10;
        break;
    case 9:
        WiFiLobbyQuestionnaireMessageBox_Erase(param3);
        return 1;
    case 10:
        if (WiFiLobbyQuestionnaireMessageBox_IsMessageDone(param3) == 1) {
            param0->state = param0->returnState;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

static void WiFiLobbyQuestionnaireAnswerSelection_Free(WiFiLobbyQuestionnaireAnswerSelection *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2)
{
    WiFiLobbyQuestionnaireQuestion_Free(&param0->question);

    {
        int v0;

        for (v0 = 0; v0 < 1; v0++) {
            Window_Remove(&param0->window[v0]);
        }
    }

    {
        Sprite_Delete(param0->cursorSprite);
    }

    {
        int v1;

        SpriteTransfer_ResetCharTransfer(param0->spriteResources[0]);
        SpriteTransfer_ResetPlttTransfer(param0->spriteResources[1]);

        for (v1 = 0; v1 < 4; v1++) {
            SpriteResourceCollection_Remove(param2->spriteResources[v1], param0->spriteResources[v1]);
        }
    }
}

static void WiFiLobbyQuestionnaireAnswerSelection_DrawQuestion(WiFiLobbyQuestionnaireAnswerSelection *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2)
{
    String *v0;

    Window_FillTilemap(&param0->window[0], 0);

    v0 = WiFiLobbyQuestionnaireQuestion_GetAnswerText(&param0->question, param1, 0);
    Text_AddPrinterWithParamsAndColor(&param0->window[0], FONT_MESSAGE, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    v0 = WiFiLobbyQuestionnaireQuestion_GetAnswerText(&param0->question, param1, 1);
    Text_AddPrinterWithParamsAndColor(&param0->window[0], FONT_MESSAGE, v0, 0, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    v0 = WiFiLobbyQuestionnaireQuestion_GetAnswerText(&param0->question, param1, 2);
    Text_AddPrinterWithParamsAndColor(&param0->window[0], FONT_MESSAGE, v0, 0, 48, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Window_ScheduleCopyToVRAM(&param0->window[0]);
}

static void WiFiLobbyQuestionnaireAnswerSelection_UpdateCursor(WiFiLobbyQuestionnaireAnswerSelection *param0)
{
    Sprite_SetDrawFlag(param0->cursorSprite, TRUE);
    Sprite_SetPosition(param0->cursorSprite, &sCursorPositions[param0->selectedAnswer]);
}

static void WiFiLobbyQuestionnaireAnswerSelection_AnimateCursor(WiFiLobbyQuestionnaireAnswerSelection *param0)
{
    Sprite_SetAnimateFlag(param0->cursorSprite, 1);
}

static void WiFiLobbyQuestionnaireMessageBox_Init(WiFiLobbyQuestionnaireMessageBox *param0, WiFiLobbyQuestionnaireGraphics *param1, SaveData *saveData, enum HeapID heapID)
{
    Window_Add(param1->bgConfig, &param0->window, 1, 2, 19, 27, 4, 4, (1 + (18 + 12)) + 9);
    Window_FillTilemap(&param0->window, 15);

    param0->string = String_Init(256, heapID);
    param0->textFrameDelay = Options_TextFrameDelay(SaveData_GetOptions(saveData));
}

static void WiFiLobbyQuestionnaireMessageBox_Free(WiFiLobbyQuestionnaireMessageBox *param0, u32 param1)
{
    if (Text_IsPrinterActive(param0->printer)) {
        Text_RemovePrinter(param0->printer);
    }

    WiFiLobbyQuestionnaireMessageBox_HideWaitDial(param0);

    String_Free(param0->string);
    Window_Remove(&param0->window);

    WiFiLobbyQuestionnaireMessageBox_DestroyMenu(param0, param1);
}

static void WiFiLobbyQuestionnaireMessageBox_Print(WiFiLobbyQuestionnaireMessageBox *param0, const String *param1)
{
    if (Text_IsPrinterActive(param0->printer)) {
        Text_RemovePrinter(param0->printer);
    }

    Window_FillTilemap(&param0->window, 15);
    String_Copy(param0->string, param1);
    param0->printer = Text_AddPrinterWithParamsAndColor(&param0->window, FONT_MESSAGE, param0->string, 0, 0, param0->textFrameDelay, TEXT_COLOR(1, 2, 15), NULL);
    Window_DrawMessageBoxWithScrollCursor(&param0->window, 1, 1, 5);
}

static void WiFiLobbyQuestionnaireMessageBox_PrintInstant(WiFiLobbyQuestionnaireMessageBox *param0, const String *param1)
{
    if (Text_IsPrinterActive(param0->printer)) {
        Text_RemovePrinter(param0->printer);
    }

    Window_FillTilemap(&param0->window, 15);
    String_Copy(param0->string, param1);
    Text_AddPrinterWithParamsAndColor(&param0->window, FONT_MESSAGE, param0->string, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
    Window_DrawMessageBoxWithScrollCursor(&param0->window, 1, 1, 5);
    Window_ScheduleCopyToVRAM(&param0->window);
}

static void WiFiLobbyQuestionnaireMessageBox_ShowWaitDial(WiFiLobbyQuestionnaireMessageBox *param0)
{
    GF_ASSERT(param0->waitDial == NULL);
    param0->waitDial = Window_AddWaitDial(&param0->window, 1);
}

static void WiFiLobbyQuestionnaireMessageBox_HideWaitDial(WiFiLobbyQuestionnaireMessageBox *param0)
{
    if (param0->waitDial != NULL) {
        DestroyWaitDial(param0->waitDial);
        param0->waitDial = NULL;
    }
}

static BOOL WiFiLobbyQuestionnaireMessageBox_IsMessageDone(const WiFiLobbyQuestionnaireMessageBox *param0)
{
    if (Text_IsPrinterActive(param0->printer) == 0) {
        return 1;
    }

    return 0;
}

static void WiFiLobbyQuestionnaireMessageBox_Erase(WiFiLobbyQuestionnaireMessageBox *param0)
{
    if (Text_IsPrinterActive(param0->printer)) {
        Text_RemovePrinter(param0->printer);
    }

    WiFiLobbyQuestionnaireMessageBox_HideWaitDial(param0);

    Window_EraseMessageBox(&param0->window, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->window);
}

static void WiFiLobbyQuestionnaireMessageBox_OpenYesNoMenu(WiFiLobbyQuestionnaireMessageBox *param0, WiFiLobbyQuestionnaireGraphics *param1, u32 param2)
{
    GF_ASSERT(param0->menu == NULL);
    param0->menu = Menu_MakeYesNoChoice(param1->bgConfig, &sYesNoWindowTemplate, 1 + (18 + 12), 6, param2);
}

static u32 WiFiLobbyQuestionnaireMessageBox_ProcessMenuInput(WiFiLobbyQuestionnaireMessageBox *param0, u32 param1)
{
    u32 v0 = Menu_ProcessInputAndHandleExit(param0->menu, param1);

    if (v0 != 0xffffffff) {
        param0->menu = NULL;
    }

    return v0;
}

static void WiFiLobbyQuestionnaireMessageBox_DestroyMenu(WiFiLobbyQuestionnaireMessageBox *param0, u32 param1)
{
    if (param0->menu != NULL) {
        Menu_DestroyForExit(param0->menu, param1);
        param0->menu = NULL;
    }
}

static void WiFiLobbyQuestionnaireScreen_InitResults(WiFiLobbyQuestionnaireScreen *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, UnkStruct_ov66_02231374 *param3, u32 param4)
{
    WiFiLobbyQuestionnaireResults_Init(&param0->results, param1, param2, param3, param4);
}

static BOOL WiFiLobbyQuestionnaireScreen_MainResults(WiFiLobbyQuestionnaireScreen *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, WiFiLobbyQuestionnaireMessageBox *param3, UnkStruct_ov66_02231374 *param4, enum HeapID heapID)
{
    return WiFiLobbyQuestionnaireResults_Main(&param0->results, param1, param2, param3, param4, heapID);
}

static void WiFiLobbyQuestionnaireScreen_FreeResults(WiFiLobbyQuestionnaireScreen *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2)
{
    WiFiLobbyQuestionnaireResults_Free(&param0->results, param1, param2);
}

static void WiFiLobbyQuestionnaireResults_Init(WiFiLobbyQuestionnaireResults *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, UnkStruct_ov66_02231374 *param3, enum HeapID heapID)
{
    {
        Graphics_LoadPaletteFromOpenNARC(param2->narc, 199, 0, 0, 4 * 32, heapID);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param2->narc, 200, param2->bgConfig, 0, 0, 0, 0, heapID);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param2->narc, 202, param2->bgConfig, 0, 0, 0, 0, heapID);
    }

    {
        int v0;

        for (v0 = 0; v0 < 6; v0++) {
            Window_AddFromTemplate(param2->bgConfig, &param0->windows[v0], &sResultsWindowTemplates[v0]);
        }
    }

    WiFiLobbyQuestionnaireResults_DrawHeader(param0, param1, 109, TEXT_COLOR(3, 4, 0));

    {
        param0->charDataRaw = Graphics_GetCharDataFromOpenNARC(param2->narc, 200, 0, &param0->charData, heapID);
    }

    {
        WiFiLobbyQuestionnaireQuestion_Init(&param0->currentQuestion, 1, heapID);
        WiFiLobbyQuestionnaireQuestion_Init(&param0->lastQuestion, 0, heapID);

        if (ov66_0222F144(param3->unk_04, &param0->currentTally) == 0) {
            WiFiLobbyQuestionnaireAnswerTally_CountAnswers(&param0->currentTally, param3->unk_04);
            ov66_0222F124(param3->unk_04, &param0->currentTally);
        }

        WiFiLobbyQuestionnaireAnswerTally_Init(&param0->lastTally);
    }
}

static BOOL WiFiLobbyQuestionnaireResults_Main(WiFiLobbyQuestionnaireResults *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, WiFiLobbyQuestionnaireMessageBox *param3, UnkStruct_ov66_02231374 *param4, enum HeapID heapID)
{
    String *v0;
    u32 v1;

    switch (param0->state) {
    case 0:
        if (param0->currentQuestion.isSpecialWeek == 0) {
            v1 = 103;
        } else {
            v1 = 105;
        }

        v0 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, v1);
        WiFiLobbyQuestionnaireMessageBox_Print(param3, v0);
        param0->returnState = 1;
        param0->state = 22;
        break;
    case 1:
        v0 = WiFiLobbyQuestionnaireQuestion_GetText(&param0->currentQuestion, param1);
        WiFiLobbyQuestionnaireMessageBox_Print(param3, v0);
        param0->returnState = 2;
        param0->state = 22;
        break;
    case 2:
        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            v0 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, 104);
            WiFiLobbyQuestionnaireMessageBox_Print(param3, v0);
            param0->returnState = 3;
            param0->state = 22;
        }
        break;
    case 3:
        if (param0->currentQuestion.isSpecialWeek == 0) {
            v1 = 107;
        } else {
            v1 = 108;
        }

        v0 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, v1);
        WiFiLobbyQuestionnaireMessageBox_Print(param3, v0);
        param0->returnState = 4;
        param0->state = 22;
        break;
    case 4: {
        UnkStruct_ov66_0222E908 v2;
        const WiFiPlazaProfile *v3;
        BOOL v4;

        v3 = ov66_0222E3BC(param4->unk_04);
        ov66_0222E908(v3, &v2);

        v4 = ov66_0222E924(param4->unk_04, ov66_0222E338(param4->unk_04));
        WiFiLobbyQuestionnaireResults_DrawQuestion(param0, &param0->currentQuestion, param1, param2, &v2, heapID, TEXT_COLOR(9, 10, 0), TEXT_COLOR(13, 14, 0), v4);
        WiFiLobbyQuestionnaireResults_InitBars(param0, &param0->currentTally, param2, 1);

        Sound_PlayEffect(SEQ_SE_PL_PINPON2_sseq);
    }

        param0->state = 5;
        break;
    case 5: {
        BOOL v5;

        v5 = WiFiLobbyQuestionnaireResults_AnimateBars(param0, param2);

        if (v5 == 1) {
            param0->state = 6;
        }
    } break;
    case 6:
        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            if (param0->lastQuestion.questionNo != (PPW_LOBBY_INVALID_QUESTION_NO)) {
                param0->state = 7;
            } else {
                v0 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, 112);
                WiFiLobbyQuestionnaireMessageBox_Print(param3, v0);
                param0->returnState = 20;
                param0->state = 22;
            }
        }
        break;
    case 7:
        v0 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, 111);
        WiFiLobbyQuestionnaireMessageBox_PrintInstant(param3, v0);
        WiFiLobbyQuestionnaireMessageBox_OpenYesNoMenu(param3, param2, heapID);
        param0->state = 8;
        break;
    case 8: {
        u32 v6;

        v6 = WiFiLobbyQuestionnaireMessageBox_ProcessMenuInput(param3, heapID);

        switch (v6) {
        case 0:
            param0->state = 9;
            break;
        case 0xfffffffe:
            param0->state = 20;
            break;
        }
    } break;
    case 9:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, heapID);
        param0->state = 10;
        break;
    case 10:
        if (IsScreenFadeDone() == TRUE) {
            WiFiLobbyQuestionnaireResults_DrawPage(param0, param1, param2, heapID);
            param0->state = 11;
        }
        break;
    case 11:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, heapID);
        param0->state = 12;
        break;
    case 12:
        if (IsScreenFadeDone() == TRUE) {
            param0->state = 13;
        }
        break;
    case 13:
        if (param0->lastQuestion.isSpecialWeek == 0) {
            v1 = 113;
        } else {
            v1 = 115;
        }

        v0 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, v1);
        WiFiLobbyQuestionnaireMessageBox_Print(param3, v0);
        param0->returnState = 14;
        param0->state = 22;
        break;
    case 14:
        v0 = WiFiLobbyQuestionnaireQuestion_GetText(&param0->lastQuestion, param1);
        WiFiLobbyQuestionnaireMessageBox_Print(param3, v0);
        param0->returnState = 15;
        param0->state = 22;
        break;
    case 15:
        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            v0 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, 114);
            WiFiLobbyQuestionnaireMessageBox_Print(param3, v0);
            param0->returnState = 16;
            param0->state = 22;
        }
        break;
    case 16:
        if (param0->lastQuestion.isSpecialWeek == 0) {
            v1 = 117;
        } else {
            v1 = 118;
        }

        v0 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, v1);
        WiFiLobbyQuestionnaireMessageBox_Print(param3, v0);
        param0->returnState = 17;
        param0->state = 22;
        break;
    case 17: {
        UnkStruct_ov66_0222E908 v7;
        WiFiPlazaQuestion *savedWiFiPlazaQuestion;
        BOOL v9;

        savedWiFiPlazaQuestion = SaveData_GetWiFiPlazaQuestion(param4->saveData);
        v7.questionNumber = WiFiPlazaQuestion_GetQuestionNumber(savedWiFiPlazaQuestion);
        v7.selectedAnswer = WiFiPlazaQuestion_GetSelectedAnswer(savedWiFiPlazaQuestion);
        v9 = ov66_0222E924(param4->unk_04, ov66_0222E338(param4->unk_04));

        WiFiLobbyQuestionnaireResults_DrawQuestion(param0, &param0->lastQuestion, param1, param2, &v7, heapID, TEXT_COLOR(11, 12, 0), TEXT_COLOR(15, 14, 0), v9);
        WiFiLobbyQuestionnaireResults_InitBars(param0, &param0->lastTally, param2, 2);
        Sound_PlayEffect(SEQ_SE_PL_PINPON2_sseq);
    }
        param0->state = 18;
        break;
    case 18: {
        BOOL v10;

        v10 = WiFiLobbyQuestionnaireResults_AnimateBars(param0, param2);

        if (v10 == 1) {
            param0->state = 19;
        }
    } break;
    case 19:
        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            param0->state = 20;
        }
        break;
    case 20:
        v0 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, 120);
        WiFiLobbyQuestionnaireMessageBox_Print(param3, v0);
        param0->returnState = 21;
        param0->state = 22;
        break;
    case 21:
        WiFiLobbyQuestionnaireMessageBox_Erase(param3);
        return 1;
    case 22:
        if (WiFiLobbyQuestionnaireMessageBox_IsMessageDone(param3) == 1) {
            param0->state = param0->returnState;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

static void WiFiLobbyQuestionnaireResults_Free(WiFiLobbyQuestionnaireResults *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2)
{
    {
        WiFiLobbyQuestionnaireQuestion_Free(&param0->currentQuestion);
        WiFiLobbyQuestionnaireQuestion_Free(&param0->lastQuestion);
    }

    Heap_Free(param0->charDataRaw);
    param0->charDataRaw = NULL;

    {
        int v0;

        for (v0 = 0; v0 < 6; v0++) {
            Window_Remove(&param0->windows[v0]);
        }
    }
}

static void WiFiLobbyQuestionnaireResults_DrawHeader(WiFiLobbyQuestionnaireResults *param0, WiFiLobbyQuestionnaireMessages *param1, u32 param2, TextColor param3)
{
    String *v0;
    u32 v1;
    s32 v2;

    Window_FillTilemap(&param0->windows[0], 0);

    v0 = WiFiLobbyQuestionnaireMessages_GetString(param1, 0, param2);
    v1 = Font_CalcStringWidth(FONT_MESSAGE, v0, 0);
    v2 = ((18 * 8) - v1) / 2;

    Text_AddPrinterWithParamsAndColor(&param0->windows[0], FONT_MESSAGE, v0, v2, 4, TEXT_SPEED_NO_TRANSFER, param3, NULL);
    Window_ScheduleCopyToVRAM(&param0->windows[0]);
}

static void WiFiLobbyQuestionnaireResults_DrawQuestion(WiFiLobbyQuestionnaireResults *param0, const WiFiLobbyQuestionnaireQuestion *param1, WiFiLobbyQuestionnaireMessages *param2, WiFiLobbyQuestionnaireGraphics *param3, const UnkStruct_ov66_0222E908 *param4, enum HeapID heapID, u32 param6, u32 param7, BOOL param8)
{
    String *v0;

    Window_FillTilemap(&param0->windows[1], 0);
    Window_FillTilemap(&param0->windows[5], 0);

    v0 = WiFiLobbyQuestionnaireQuestion_GetAnswerText(param1, param2, 0);
    Text_AddPrinterWithParamsAndColor(&param0->windows[1], FONT_MESSAGE, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, param6, NULL);

    v0 = WiFiLobbyQuestionnaireQuestion_GetAnswerText(param1, param2, 1);
    Text_AddPrinterWithParamsAndColor(&param0->windows[1], FONT_MESSAGE, v0, 0, 24, TEXT_SPEED_NO_TRANSFER, param6, NULL);

    v0 = WiFiLobbyQuestionnaireQuestion_GetAnswerText(param1, param2, 2);
    Text_AddPrinterWithParamsAndColor(&param0->windows[1], FONT_MESSAGE, v0, 0, 48, TEXT_SPEED_NO_TRANSFER, param6, NULL);

    if ((param4->questionNumber == param1->questionSerialNo) && (param4->selectedAnswer < 3)) {
        s32 v1;
        s32 v2;
        TextColor v3;

        if (param8 == 1) {
            v3 = param7;
        } else {
            v3 = param6;
        }

        WiFiLobbyQuestionnaireMessages_SetPlayerName(param2, 0, heapID);

        v0 = WiFiLobbyQuestionnaireMessages_GetString(param2, 0, 110);
        v1 = Font_CalcStringWidth(FONT_MESSAGE, v0, 0);
        v2 = (((12 * 8) - v1) / 2);

        Text_AddPrinterWithParamsAndColor(&param0->windows[5], FONT_MESSAGE, v0, v2, 0, TEXT_SPEED_NO_TRANSFER, v3, NULL);

        v0 = WiFiLobbyQuestionnaireQuestion_GetAnswerText(param1, param2, param4->selectedAnswer);
        v1 = Font_CalcStringWidth(FONT_MESSAGE, v0, 0);
        v2 = (((13 * 8) - v1) / 2);

        Text_AddPrinterWithParamsAndColor(&param0->windows[5], FONT_MESSAGE, v0, (12 * 8) + v2, 0, TEXT_SPEED_NO_TRANSFER, param6, NULL);
    }

    Window_ScheduleCopyToVRAM(&param0->windows[5]);
    Window_ScheduleCopyToVRAM(&param0->windows[1]);
}

static void WiFiLobbyQuestionnaireResults_InitBars(WiFiLobbyQuestionnaireResults *param0, const WiFiLobbyQuestionnaireAnswerTally *param1, WiFiLobbyQuestionnaireGraphics *param2, u32 param3)
{
    int v0;

    param0->animationTimer = 0;

    for (v0 = 0; v0 < 3; v0++) {
        param0->barPositions[v0] = 0;
        param0->barTargets[v0] = WiFiLobbyQuestionnaireAnswerTally_GetBarWidth(param1, v0, 80);

        Window_SetPalette(&param0->windows[2 + v0], param3);
        Window_FillTilemap(&param0->windows[2 + v0], 0);
    }
}

static BOOL WiFiLobbyQuestionnaireResults_AnimateBars(WiFiLobbyQuestionnaireResults *param0, WiFiLobbyQuestionnaireGraphics *param1)
{
    s32 v0;
    s32 v1;
    s32 v2;
    int v3, v4;
    int v5;

    if (param0->animationTimer >= 20) {
        return 1;
    }

    param0->animationTimer++;

    v0 = (param0->animationTimer * 80) / 20;
    v5 = 0;

    for (v3 = 0; v3 < 3; v3++) {
        if (param0->barPositions[v3] == param0->barTargets[v3]) {
            v5++;
            continue;
        }

        if (param0->barTargets[v3] >= v0) {
            v2 = v0 - param0->barPositions[v3];
            v1 = param0->barPositions[v3];
            param0->barPositions[v3] = v0;
        } else {
            v2 = param0->barTargets[v3] - param0->barPositions[v3];
            v1 = param0->barPositions[v3];
            param0->barPositions[v3] = param0->barTargets[v3];
        }

        for (v4 = 0; v4 < v2; v4++) {
            Window_BlitBitmapRect(&param0->windows[2 + v3], param0->charData->pRawData, 247, 16, 256, 32, 4 + v1 + v4, 0, 1, 16);
        }

        Window_ScheduleCopyToVRAM(&param0->windows[2 + v3]);
    }

    if (v5 == 3) {
        return 1;
    }

    return 0;
}

static void WiFiLobbyQuestionnaireResults_DrawPage(WiFiLobbyQuestionnaireResults *param0, WiFiLobbyQuestionnaireMessages *param1, WiFiLobbyQuestionnaireGraphics *param2, u32 param3)
{
    {
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param2->narc, 203, param2->bgConfig, 0, 0, 0, 0, param3);
    }

    {
        int v0;

        for (v0 = 0; v0 < 6; v0++) {
            Window_FillTilemap(&param0->windows[v0], 0);
            Window_CopyToVRAM(&param0->windows[v0]);
        }
    }

    WiFiLobbyQuestionnaireResults_DrawHeader(param0, param1, 119, TEXT_COLOR(5, 6, 0));
}

static void WiFiLobbyQuestionnaireQuestion_Init(WiFiLobbyQuestionnaireQuestion *param0, BOOL param1, enum HeapID heapID)
{
    u32 v0;
    u32 v1;
    u16 *v2;
    int v3;

    param0->questionText = String_Init(256, heapID);

    for (v3 = 0; v3 < 3; v3++) {
        param0->answerTexts[v3] = String_Init(256, heapID);
    }

    if (param1 == 1) {
        v0 = UnkEnum_ov66_02233454_00;
        v1 = UnkEnum_ov66_02233538_00;
    } else {
        v0 = UnkEnum_ov66_02233454_04;
        v1 = UnkEnum_ov66_02233538_04;
    }

    param0->isSpecialWeek = ov66_02233454(v0 + UnkEnum_ov66_02233454_02);
    param0->questionNo = ov66_02233454(v0 + UnkEnum_ov66_02233454_01);
    param0->questionSerialNo = ov66_02233454(v0 + UnkEnum_ov66_02233454_00);
    param0->isFreeQuestion = ov66_02233454(v0 + UnkEnum_ov66_02233454_03);

    if (param0->isFreeQuestion == 1) {
        v2 = ov66_02233538(v1 + UnkEnum_ov66_02233538_00);
        GF_ASSERT(v2);
        String_CopyChars(param0->questionText, v2);

        for (v3 = 0; v3 < 3; v3++) {
            v2 = ov66_02233538(v1 + UnkEnum_ov66_02233538_01 + v3);
            GF_ASSERT(v2);
            String_CopyChars(param0->answerTexts[v3], v2);
        }
    }
}

static void WiFiLobbyQuestionnaireQuestion_Free(WiFiLobbyQuestionnaireQuestion *param0)
{
    int v0;

    String_Free(param0->questionText);

    for (v0 = 0; v0 < 3; v0++) {
        String_Free(param0->answerTexts[v0]);
    }
}

static String *WiFiLobbyQuestionnaireQuestion_GetText(const WiFiLobbyQuestionnaireQuestion *param0, WiFiLobbyQuestionnaireMessages *param1)
{
    if (param0->isFreeQuestion == 0) {
        return WiFiLobbyQuestionnaireMessages_GetQuestionText(param1, param0->questionNo);
    }

    return param0->questionText;
}

static String *WiFiLobbyQuestionnaireQuestion_GetAnswerText(const WiFiLobbyQuestionnaireQuestion *param0, WiFiLobbyQuestionnaireMessages *param1, u32 param2)
{
    if (param0->isFreeQuestion == 0) {
        return WiFiLobbyQuestionnaireMessages_GetAnswerText(param1, param0->questionNo, param2);
    }

    return param0->answerTexts[param2];
}

static void WiFiLobbyQuestionnaireAnswerTally_Init(WiFiLobbyQuestionnaireAnswerTally *param0)
{
    int v0;

    param0->totalCount = 0;

    for (v0 = 0; v0 < 3; v0++) {
        param0->answerCounts[v0] = ov66_02233454(UnkEnum_ov66_02233454_08 + v0);
        param0->totalCount += param0->answerCounts[v0];
    }
}

static u32 WiFiLobbyQuestionnaireAnswerTally_GetBarWidth(const WiFiLobbyQuestionnaireAnswerTally *param0, u32 param1, u32 param2)
{
    u64 v0, v1;

    GF_ASSERT(param1 < 3);

    v0 = param2;
    v1 = param0->answerCounts[param1];

    return (u32)(((u64)(v0 * v1)) / param0->totalCount);
}

static void WiFiLobbyQuestionnaireAnswerTally_CountAnswers(WiFiLobbyQuestionnaireAnswerTally *param0, const UnkStruct_ov66_0222DFF8 *param1)
{
    const WiFiPlazaProfile *v0;
    UnkStruct_ov66_0222E908 v1;
    int v2;
    u32 language;
    BOOL v4;

    memset(param0, 0, sizeof(WiFiLobbyQuestionnaireAnswerTally));

    for (v2 = 0; v2 < 20; v2++) {
        v0 = ov66_0222E374(param1, v2);

        if (v0 != NULL) {
            language = WiFiPlazaProfile_GetLanguage(v0);
            ov66_0222E908(v0, &v1);
            v4 = ov66_022335C0(UnkEnum_ov66_022335C0_00, language);

            if ((v4 == 1) && (v1.selectedAnswer < 3)) {
                param0->answerCounts[v1.selectedAnswer]++;
                param0->totalCount++;
            }
        }
    }
}
