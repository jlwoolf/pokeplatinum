#include "wifi_lobby_minigame/wifi_lobby_minigame.h"

#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"

#include "struct_decls/wi_fi_list.h"

#include "nintendo_wfc/main.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230DBC.h"
#include "wifi_lobby_minigame/wifi_lobby_minigame_comm_cmd_handlers.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_player_context.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_ranking.h"

#include "bg_window.h"
#include "buffer_manager.h"
#include "char_transfer.h"
#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "enums.h"
#include "font.h"
#include "game_options.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "math_util.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "pltt_transfer.h"
#include "render_oam.h"
#include "render_window.h"
#include "save_player.h"
#include "savedata.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "trainer_info.h"
#include "comm_tool.h"
#include "wifi_friend_registration.h"
#include "contest_util.h"
#include "vram_transfer.h"
#include "wifi_list.h"
#include "yes_no_touch_menu.h"

typedef struct {
    fx32 unk_00;
    fx32 unk_04;
    fx32 unk_08;
    fx32 unk_0C;
    int unk_10;
} WiFiLobbyMinigameMotion;

typedef struct {
    BOOL unk_00;
    SpriteResource *unk_04[4];
    SpriteResourcesHeader unk_14;
} WiFiLobbyMinigameSpriteResource;

typedef struct {
    SpriteResourceCollection *unk_00[4];
    WiFiLobbyMinigameSpriteResource *unk_10;
    u32 unk_14;
} WiFiLobbyMinigameSpriteResources;

typedef struct {
    SpriteList *unk_00;
    G2dRenderer unk_04;
} WiFiLobbyMinigameSpriteSystem;

typedef struct {
    u32 unk_00;
    BgTemplate unk_04;
} WiFiLobbyMinigameBgTemplate;

typedef struct {
    BgConfig *unk_00;
    const WiFiLobbyMinigameBgTemplate *unk_04;
    u32 unk_08;
} WiFiLobbyMinigameBackgrounds;

typedef struct {
    MessageLoader *unk_00;
    StringTemplate *unk_04;
    String *unk_08;
    String *unk_0C;
} WiFiLobbyMinigameMessages;

typedef struct {
    Window unk_00[2];
    u16 unk_20[2];
    String *unk_24[2];
    void *unk_2C[2];
    BOOL unk_34;
} WiFiLobbyMinigameMessageBox;

typedef struct {
    u8 unk_00[4];
    u8 unk_04[4];
    u8 unk_08[4];
} WiFiLobbyMinigamePlayerRowLayout;

typedef struct {
    Window unk_00;
    Sprite *unk_10;
    Sprite *unk_14;
    u16 unk_18;
    u8 unk_1A;
    u8 unk_1B;
    WiFiLobbyMinigameMotion unk_1C;
    s16 unk_30;
    s16 unk_32;
    s32 unk_34;
} WiFiLobbyMinigamePlayerRow;

typedef struct {
    u8 unk_00[4];
    u8 unk_04[4];
    const TrainerInfo *unk_08[4];
} WiFiLobbyMinigamePlayerInfo;

typedef struct {
    Window unk_00;
    u32 unk_10;
    String *unk_14;
    WiFiLobbyMinigameMotion unk_18;
    s16 unk_2C;
    s16 unk_2E;
} WiFiLobbyMinigameGameTitle;

typedef struct {
    WiFiLobbyMinigameBackgrounds *unk_00;
    s16 unk_04[2][192];
    BufferManager *bufferManager;
} WiFiLobbyMinigameScrollEffect;

typedef struct WiFiLobbyMinigameIntroScreen_t {
    u8 unk_00;
    u8 unk_01;
    u16 heapID;
    u16 unk_04;
    u8 unk_06;
    u8 unk_07;
    WiFiLobbyMinigamePlayerContext unk_08;
    WiFiLobbyMinigamePlayerInfo unk_18;
    WiFiLobbyMinigameBackgrounds unk_30;
    WiFiLobbyMinigameMessages unk_3C;
    WiFiLobbyMinigameMessageBox unk_4C;
    WiFiLobbyMinigameSpriteSystem unk_84;
    WiFiLobbyMinigameSpriteResources unk_214;
    WiFiLobbyMinigameSpriteResource *unk_22C;
    WiFiLobbyMinigameGameTitle unk_230;
    void *unk_260;
    NNSG2dScreenData *unk_264;
    WiFiLobbyMinigamePlayerRow unk_268[4];
    WiFiLobbyMinigameScrollEffect unk_348;
    SysTask *unk_650;
    SysTask *unk_654;
} WiFiLobbyMinigameIntroScreen;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    YesNoTouchMenu *unk_04;
    YesNoTouchMenuParams unk_08;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 unk_1F;
} WiFiLobbyMinigameReplayMenu;

typedef struct {
    void *unk_00;
    NNSG2dScreenData *unk_04;
    Sprite *unk_08[15];
    WiFiLobbyMinigameSpriteResource *unk_44;
    u8 unk_48;
    u8 unk_49;
    u8 unk_4A;
    u8 unk_4B;
} WiFiLobbyMinigameBalloonGrid;

typedef struct WiFiLobbyMinigameResultsScreen_t {
    u16 unk_00;
    u16 heapID;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A[2];
    WiFiLobbyMinigamePlayerContext unk_0C;
    WiFiLobbyMinigameRanking unk_1C;
    WiFiLobbyMinigamePlayerInfo unk_34;
    WiFiLobbyMinigameBackgrounds unk_4C;
    WiFiLobbyMinigameMessages unk_58;
    WiFiLobbyMinigameMessageBox unk_68;
    WiFiLobbyMinigameSpriteSystem unk_A0;
    WiFiLobbyMinigameSpriteResources unk_230;
    WiFiLobbyMinigameSpriteResource *unk_248;
    WiFiLobbyMinigameReplayMenu unk_24C;
    WiFiLobbyMinigameBalloonGrid unk_26C;
    void *unk_2B8[1];
    NNSG2dScreenData *unk_2BC[1];
    WiFiLobbyMinigamePlayerRow unk_2C0[4];
    WiFiLobbyMinigameScrollEffect unk_3A0;
    SysTask *unk_6A8;
    SysTask *unk_6AC;
    u32 unk_6B0;
    u16 unk_6B4;
    u16 unk_6B6;
    void *unk_6B8;
    NNSG2dPaletteData *unk_6BC;
    u16 unk_6C0;
    u16 unk_6C2;
    BOOL unk_6C4;
} WiFiLobbyMinigameResultsScreen;

typedef struct {
    Sprite *unk_00[2];
    s16 unk_08;
    s16 unk_0A;
    u8 unk_0C[2][192];
    SysTask *unk_18C;
    GXWndPlane unk_190;
    GXWndPlane battlerType;
    int unk_194;
} WiFiLobbyMinigameCurtain;

typedef struct WiFiLobbyMinigameIntroAnimation_t {
    u32 unk_00;
    u16 unk_04;
    s16 unk_06;
    SpriteList *unk_08;
    NARC *unk_0C;
    WiFiLobbyMinigameSpriteResources unk_10;
    WiFiLobbyMinigameSpriteResource *unk_28;
    SysTask *unk_2C;
    Sprite *unk_30;
    WiFiLobbyMinigameCurtain unk_34;
} WiFiLobbyMinigameIntroAnimation;

typedef struct {
    u16 unk_00;
    u16 unk_02;
} WiFiLobbyMinigameMessageIdRemap;

static void WiFiLobbyMinigame_InitMotion(WiFiLobbyMinigameMotion *param0, fx32 param1, fx32 param2, fx32 param3, int param4);
static BOOL WiFiLobbyMinigame_UpdateMotion(WiFiLobbyMinigameMotion *param0, s32 param1);
static void WiFiLobbyMinigame_OffsetScreenData(NNSG2dScreenData *param0, u32 param1);
static void WiFiLobbyMinigame_InitSpriteResources(WiFiLobbyMinigameSpriteResources *param0, u32 param1, u32 heapID);
static void WiFiLobbyMinigame_FreeSpriteResources(WiFiLobbyMinigameSpriteResources *param0);
static WiFiLobbyMinigameSpriteResource *WiFiLobbyMinigame_AllocSpriteResource(WiFiLobbyMinigameSpriteResources *param0, NARC *param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8);
static Sprite *WiFiLobbyMinigame_AddSprite(WiFiLobbyMinigameSpriteResource *param0, SpriteList *param1, s16 param2, s16 param3, u16 param4, u32 param5);
static void WiFiLobbyMinigame_LoadSpriteResource(WiFiLobbyMinigameSpriteResources *param0, WiFiLobbyMinigameSpriteResource *param1, NARC *param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9);
static void WiFiLobbyMinigame_UnloadSpriteResource(WiFiLobbyMinigameSpriteResources *param0, WiFiLobbyMinigameSpriteResource *param1);
static void WiFiLobbyMinigame_FreeBackgrounds(WiFiLobbyMinigameBackgrounds *param0);
static void WiFiLobbyMinigame_RunBackgroundUpdates(WiFiLobbyMinigameBackgrounds *param0);
static void WiFiLobbyMinigame_InitSpriteSystem(WiFiLobbyMinigameSpriteSystem *param0, u32 param1, u32 param2, u32 param3, u32 param4);
static void WiFiLobbyMinigame_FreeSpriteSystem(WiFiLobbyMinigameSpriteSystem *param0);
static void WiFiLobbyMinigame_UpdateSprites(WiFiLobbyMinigameSpriteSystem *param0);
static void WiFiLobbyMinigame_TransferOam(WiFiLobbyMinigameSpriteSystem *param0);
static void WiFiLobbyMinigame_InitMessages(WiFiLobbyMinigameMessages *param0, u32 heapID);
static void WiFiLobbyMinigame_FreeMessages(WiFiLobbyMinigameMessages *param0);
static void WiFiLobbyMinigame_ClearMessageArgs(WiFiLobbyMinigameMessages *param0);
static void WiFiLobbyMinigame_SetMessagePlayerName(WiFiLobbyMinigameMessages *param0, const TrainerInfo *param1);
static void WiFiLobbyMinigame_SetMessageCountryName(WiFiLobbyMinigameMessages *param0, u32 param1);
static void WiFiLobbyMinigame_SetMessageCityName(WiFiLobbyMinigameMessages *param0, u32 param1, u32 param2);
static void WiFiLobbyMinigame_SetMessageNumber(WiFiLobbyMinigameMessages *param0, u32 param1, u32 param2);
static void WiFiLobbyMinigame_SetMessageRankNumber(WiFiLobbyMinigameMessages *param0, u32 param1);
static void WiFiLobbyMinigame_SetMessagePlazaItemName(WiFiLobbyMinigameMessages *param0, u32 param1);
static void WiFiLobbyMinigame_SetMessageMinigameName(WiFiLobbyMinigameMessages *param0, u32 param1);
static void WiFiLobbyMinigame_DrawMessage(WiFiLobbyMinigameMessages *param0, String *param1, u32 param2);
static void WiFiLobbyMinigame_DrawMessageLeft(WiFiLobbyMinigameMessages *param0, u32 param1, Window *param2, u8 param3, u8 param4);
static void WiFiLobbyMinigame_DrawMessageRightAligned(WiFiLobbyMinigameMessages *param0, u32 param1, Window *param2, u8 param3, u8 param4);
static u32 WiFiLobbyMinigame_PrintMessage(WiFiLobbyMinigameMessages *param0, u32 param1, Window *param2, String *param3, u32 param4);
static void WiFiLobbyMinigame_DrawMessageWithColor(WiFiLobbyMinigameMessages *param0, u32 param1, Window *param2, u8 param3, u8 param4, TextColor param5);
static void WiFiLobbyMinigame_InitMessageBox(WiFiLobbyMinigameMessageBox *param0, WiFiLobbyMinigameBackgrounds *param1, SaveData *saveData, BOOL param3, u32 heapID);
static void WiFiLobbyMinigame_FreeMessageBox(WiFiLobbyMinigameMessageBox *param0);
static void WiFiLobbyMinigame_ShowMessage(WiFiLobbyMinigameMessageBox *param0, WiFiLobbyMinigameMessages *param1, u32 param2, u32 param3);
static void WiFiLobbyMinigame_HideMessage(WiFiLobbyMinigameMessageBox *param0, u32 param1);
static BOOL WiFiLobbyMinigame_IsMessageDone(const WiFiLobbyMinigameMessageBox *param0, u32 param1);
static void WiFiLobbyMinigame_ShowWaitDial(WiFiLobbyMinigameMessageBox *param0, u32 param1);
static void WiFiLobbyMinigame_HideWaitDial(WiFiLobbyMinigameMessageBox *param0, u32 param1);
static void WiFiLobbyMinigame_InitPlayerRow(WiFiLobbyMinigamePlayerRow *param0, u32 param1, u32 param2, NNSG2dScreenData *param3, WiFiLobbyMinigameBackgrounds *param4, u32 param5, u32 param6, WiFiLobbyMinigameSpriteSystem *param7, WiFiLobbyMinigameSpriteResource *param8, u32 heapID);
static void WiFiLobbyMinigame_DrawPlayerRowName(WiFiLobbyMinigamePlayerRow *param0, WiFiLobbyMinigameMessages *param1, const TrainerInfo *param2, s16 param3, s16 param4, u32 param5);
static void WiFiLobbyMinigame_DrawPlayerRowLocation(WiFiLobbyMinigamePlayerRow *param0, WiFiLobbyMinigameMessages *param1, BOOL param2, u32 param3, u32 param4, s16 param5);
static void WiFiLobbyMinigame_ShowPlayerRowRankIcon(WiFiLobbyMinigamePlayerRow *param0, u32 param1);
static void WiFiLobbyMinigame_DrawPlayerRowScore(WiFiLobbyMinigamePlayerRow *param0, WiFiLobbyMinigameMessages *param1, u32 param2, s16 param3, s16 param4, u32 param5);
static void WiFiLobbyMinigame_TransferPlayerRow(WiFiLobbyMinigamePlayerRow *param0, WiFiLobbyMinigameBackgrounds *param1);
static void WiFiLobbyMinigame_ShowPlayerRowSprite(WiFiLobbyMinigamePlayerRow *param0);
static void WiFiLobbyMinigame_FreePlayerRow(WiFiLobbyMinigamePlayerRow *param0);
static void WiFiLobbyMinigame_StartPlayerRowSlideIn(WiFiLobbyMinigamePlayerRow *param0, s16 param1, s16 param2);
static void WiFiLobbyMinigame_StartPlayerRowSlideOut(WiFiLobbyMinigamePlayerRow *param0, s16 param1);
static BOOL WiFiLobbyMinigame_UpdatePlayerRowMotion(WiFiLobbyMinigamePlayerRow *param0);
static void WiFiLobbyMinigame_SetPlayerRowSpritePos(WiFiLobbyMinigamePlayerRow *param0, s32 param1);
static u32 WiFiLobbyMinigame_GetPlayerRowOrder(u32 param0, u32 param1, u32 param2);
static void WiFiLobbyMinigame_InitScrollEffect(WiFiLobbyMinigameScrollEffect *param0, WiFiLobbyMinigameBackgrounds *param1, u32 heapID);
static void WiFiLobbyMinigame_FreeScrollEffect(WiFiLobbyMinigameScrollEffect *param0);
static void WiFiLobbyMinigame_UpdateScrollEffect(WiFiLobbyMinigameScrollEffect *param0, const WiFiLobbyMinigamePlayerRow *param1);
static void WiFiLobbyMinigame_SwapScrollBuffers(WiFiLobbyMinigameScrollEffect *param0);
static void WiFiLobbyMinigame_ScrollEffectHBlank(void *param0);
static void WiFiLobbyMinigame_InitPlayerInfo(WiFiLobbyMinigamePlayerInfo *param0, const WiFiLobbyMinigamePlayerContext *param1);
static BOOL WiFiLobbyMinigame_ArePlayersFromDifferentCountries(const WiFiLobbyMinigamePlayerContext *param0, const WiFiLobbyMinigamePlayerInfo *param1);
u32 WiFiLobbyMinigame_GetNextMinigame(u32 param0);
static void WiFiLobbyMinigame_InitGameTitle(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1, WiFiLobbyMinigameMessages *param2, u32 param3, NARC *param4, u32 heapID);
static void WiFiLobbyMinigame_FreeGameTitle(WiFiLobbyMinigameGameTitle *param0);
static void WiFiLobbyMinigame_ShowGameTitle(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1, u32 heapID);
static void WiFiLobbyMinigame_HideGameTitle(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1);
static BOOL WiFiLobbyMinigame_UpdateGameTitleShow(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1);
static BOOL WiFiLobbyMinigame_UpdateGameTitleHide(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1);
static void WiFiLobbyMinigame_SetGameTitleBgOffset(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1, s32 param2);
static void WiFiLobbyMinigame_ScheduleGameTitleBgScroll(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1, s32 param2);
static void WiFiLobbyMinigame_LoadMinigamePalette(NARC *param0, u32 param1, u32 param2);
static WiFiLobbyMinigameIntroScreen *WiFiLobbyMinigame_CreateIntroScreenInternal(const WiFiLobbyMinigamePlayerContext *param0, u32 param1, u32 heapID);
static void WiFiLobbyMinigame_LoadIntroScreenGraphics(WiFiLobbyMinigameIntroScreen *param0, u32 heapID);
static void WiFiLobbyMinigame_FreeIntroScreenGraphics(WiFiLobbyMinigameIntroScreen *param0);
static void WiFiLobbyMinigame_IntroScreenTask(SysTask *param0, void *param1);
static void WiFiLobbyMinigame_IntroScreenVBlankTask(SysTask *param0, void *param1);
static int WiFiLobbyMinigame_RandomWeightedIndex(const u8 *param0, u32 param1);
static BOOL WiFiLobbyMinigame_UpdatePlayerRows(WiFiLobbyMinigameIntroScreen *param0);
static WiFiLobbyMinigameResultsScreen *WiFiLobbyMinigame_CreateResultsScreenInternal(const WiFiLobbyMinigamePlayerContext *param0, const WiFiLobbyMinigameRanking *param1, u32 param2, u32 heapID);
static void WiFiLobbyMinigame_LoadResultsScreenGraphics(WiFiLobbyMinigameResultsScreen *param0, u32 heapID);
static void WiFiLobbyMinigame_FreeResultsScreenGraphics(WiFiLobbyMinigameResultsScreen *param0);
static void WiFiLobbyMinigame_ResultsScreenTask(SysTask *param0, void *param1);
static void WiFiLobbyMinigame_ResultsScreenTaskGame2(SysTask *param0, void *param1);
static void WiFiLobbyMinigame_ResultsScreenVBlankTask(SysTask *param0, void *param1);
static void WiFiLobbyMinigame_LoadResultsPalette(WiFiLobbyMinigameResultsScreen *param0, NARC *param1, u32 param2);
static void WiFiLobbyMinigame_CheckLocalPlayerWon(WiFiLobbyMinigameResultsScreen *param0);
static void WiFiLobbyMinigame_UpdateRankPalette(WiFiLobbyMinigameResultsScreen *param0);
static void WiFiLobbyMinigame_FreeResultsPalette(WiFiLobbyMinigameResultsScreen *param0);
static void WiFiLobbyMinigame_InitReplayMenu(WiFiLobbyMinigameReplayMenu *param0, WiFiLobbyMinigameBackgrounds *param1, u32 param2, u32 heapID);
static void WiFiLobbyMinigame_FreeReplayMenu(WiFiLobbyMinigameReplayMenu *param0);
static BOOL WiFiLobbyMinigame_UpdateReplayMenu(WiFiLobbyMinigameReplayMenu *param0, WiFiLobbyMinigameMessageBox *param1, WiFiLobbyMinigameMessages *param2, u32 param3, u32 heapID);
static BOOL WiFiLobbyMinigame_ReplayMenuGetResult(const WiFiLobbyMinigameReplayMenu *param0);
static void WiFiLobbyMinigame_ReplayMenuSetPlayerReady(WiFiLobbyMinigameReplayMenu *param0, u32 param1, BOOL param2, u32 param3);
static void WiFiLobbyMinigame_ReplayMenuSetAllReady(WiFiLobbyMinigameReplayMenu *param0, BOOL param1);
static void WiFiLobbyMinigame_InitBalloonGrid(WiFiLobbyMinigameBalloonGrid *param0, WiFiLobbyMinigameBackgrounds *param1, WiFiLobbyMinigameSpriteSystem *param2, WiFiLobbyMinigameSpriteResources *param3, NARC *param4, u32 param5);
static void WiFiLobbyMinigame_FreeBalloonGrid(WiFiLobbyMinigameBalloonGrid *param0);
static void WiFiLobbyMinigame_StartBalloonGrid(WiFiLobbyMinigameBalloonGrid *param0, u32 param1);
static BOOL WiFiLobbyMinigame_UpdateBalloonGrid(WiFiLobbyMinigameBalloonGrid *param0, WiFiLobbyMinigameBackgrounds *param1);
static void WiFiLobbyMinigame_InitPlayerRowWithScore(WiFiLobbyMinigameResultsScreen *param0, u32 param1, u32 param2);
static u32 WiFiLobbyMinigame_GetTargetScore(const WiFiLobbyMinigameResultsScreen *param0);
static void WiFiLobbyMinigame_SendGameResults(WiFiLobbyMinigameResultsScreen *param0);
static void WiFiLobbyMinigame_SendGameResultsGame2(WiFiLobbyMinigameResultsScreen *param0);
static BOOL WiFiLobbyMinigame_UpdatePlayerRowsMotion(WiFiLobbyMinigameResultsScreen *param0);
static void WiFiLobbyMinigame_PlayWinFanfare(WiFiLobbyMinigameResultsScreen *param0);
static BOOL WiFiLobbyMinigame_IsWinFanfareDone(WiFiLobbyMinigameResultsScreen *param0);
static void WiFiLobbyMinigame_RecordFriendGameCount(WiFiLobbyMinigameResultsScreen *param0);
static void WiFiLobbyMinigame_InitCurtain(WiFiLobbyMinigameCurtain *param0, WiFiLobbyMinigameSpriteResource *param1, SpriteList *param2, u32 param3);
static BOOL WiFiLobbyMinigame_OpenCurtain(WiFiLobbyMinigameCurtain *param0);
static BOOL WiFiLobbyMinigame_CloseCurtain(WiFiLobbyMinigameCurtain *param0);
static void WiFiLobbyMinigame_SetCurtainPosition(WiFiLobbyMinigameCurtain *param0, s32 param1);
static void WiFiLobbyMinigame_FreeCurtain(WiFiLobbyMinigameCurtain *param0);
static void WiFiLobbyMinigame_UpdateCurtainWindow(WiFiLobbyMinigameCurtain *param0);
static void WiFiLobbyMinigame_CurtainWindowTask(SysTask *param0, void *param1);
static void WiFiLobbyMinigame_CurtainHBlank(void *param0);
static void WiFiLobbyMinigame_IntroAnimationRollTask(SysTask *param0, void *param1);
static void WiFiLobbyMinigame_IntroAnimationPopTask(SysTask *param0, void *param1);

static const s16 sPlayerRowSpriteOffsets[4][2] = {
    { 0x80, 0x2C },
    { 0xEC, 0x18 },
    { 0x4, 0x18 },
    { 0x80, 0x4 }
};

static const u8 sPlayerRowPaletteOrder[4] = {
    0x0,
    0x1,
    0x3,
    0x2
};

static const s16 sPlayerRowSlideOffsets[4] = {
    0x0,
    0xFFFFFFFFFFFFFFF6,
    0xFFFFFFFFFFFFFFF0,
    0xFFFFFFFFFFFFFFE8
};

static const VecFx32 sCurtainSpritePositions[2] = {
    { FX32_CONST(128), FX32_CONST(96), 0x0 },
    { FX32_CONST(128), FX32_CONST(96 + 2), 0x0 }
};

static const TextColor sGameTitleTextColors[WiFiPlazaLobbyActivity_12] = {
    TEXT_COLOR(7, 8, 9),
    TEXT_COLOR(4, 5, 6),
    TEXT_COLOR(1, 2, 3),
};

static const fx32 sGameTitleSlideInStart[WiFiPlazaLobbyActivity_12] = {
    -FX32_CONST(200),
    FX32_CONST(200),
    FX32_CONST(160)
};

static const fx32 sGameTitleSlideInEnd[WiFiPlazaLobbyActivity_12] = {
    FX32_CONST(0),
    FX32_CONST(0),
    FX32_CONST(0)
};

static const fx32 sGameTitleSlideInAccel[WiFiPlazaLobbyActivity_12] = {
    FX32_CONST(0),
    FX32_CONST(0),
    FX32_CONST(0)
};

static const fx32 sGameTitleSlideOutStart[WiFiPlazaLobbyActivity_12] = {
    -FX32_CONST(18),
    FX32_CONST(18),
    FX32_CONST(16)
};

static const fx32 sGameTitleSlideOutEnd[WiFiPlazaLobbyActivity_12] = {
    -FX32_CONST(9),
    FX32_CONST(9),
    FX32_CONST(8)
};

static const fx32 sGameTitleSlideOutAccel[WiFiPlazaLobbyActivity_12] = {
    FX32_CONST(0),
    FX32_CONST(0),
    FX32_CONST(0)
};

static const fx32 sGameTitleHideStart[WiFiPlazaLobbyActivity_12] = {
    FX32_CONST(200),
    -FX32_CONST(200),
    -FX32_CONST(160)
};

static const fx32 sGameTitleHideEnd[WiFiPlazaLobbyActivity_12] = {
    FX32_CONST(0),
    FX32_CONST(0),
    FX32_CONST(0)
};

static const u8 sRandomWeightsGame0[3] = {
    0x4B,
    0xF,
    0xA
};
static const u8 sRandomWeightsGame1[2] = {
    0x55,
    0xF
};
static const u8 sRandomWeightsGame2[3] = {
    0x55,
    0xF,
    0x0
};

static const CharTransferTemplate sCharTransferTemplate = {
    0x0,
    0x4000,
    0x4000,
    0x0
};

static const GXBanks sIntroScreenGXBanks = {
    GX_VRAM_BG_256_AB,
    GX_VRAM_BGEXTPLTT_NONE,
    GX_VRAM_SUB_BG_32_H,
    GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_16_G,
    GX_VRAM_OBJEXTPLTT_NONE,
    GX_VRAM_SUB_OBJ_16_I,
    GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE,
    GX_VRAM_TEXPLTT_NONE
};

static const GraphicsModes sIntroScreenGraphicsModes = {
    GX_DISPMODE_GRAPHICS,
    GX_BGMODE_0,
    GX_BGMODE_0,
    GX_BG0_AS_2D
};

static const WiFiLobbyMinigameBgTemplate sIntroScreenBgTemplates[5] = {
    {
        0x3,
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
            .priority = 0x3,
            .areaOver = 0x0,
            .mosaic = FALSE,
        },
    },
    {
        0x1,
        {
            .x = 0x0,
            .y = 0x0,
            .bufferSize = 0x2000,
            .baseTile = 0x0,
            .screenSize = BG_SCREEN_SIZE_512x512,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xc800,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0x1,
            .areaOver = 0x0,
            .mosaic = FALSE,
        },
    },
    {
        0x2,
        {
            .x = 0x0,
            .y = 0x0,
            .bufferSize = 0x800,
            .baseTile = 0x0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xc000,
            .charBase = GX_BG_CHARBASE_0x18000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0x0,
            .areaOver = 0x0,
            .mosaic = FALSE,
        },
    },
    {
        0x0,
        {
            .x = 0x0,
            .y = 0x0,
            .bufferSize = 0x2000,
            .baseTile = 0x0,
            .screenSize = BG_SCREEN_SIZE_512x512,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xa000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0x2,
            .areaOver = 0x0,
            .mosaic = FALSE,
        },
    },
    {
        0x4,
        {
            .x = 0x0,
            .y = 0x0,
            .bufferSize = 0x800,
            .baseTile = 0x0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x7800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0x0,
            .areaOver = 0x0,
            .mosaic = FALSE,
        },
    },
};

static const WiFiLobbyMinigamePlayerRowLayout sPlayerRowLayouts[4] = {
    {
        { 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0, 0x0 },
    },
    {
        { 0xE, 0x4, 0x0, 0x0 },
        { 0x12, 0x0, 0x0, 0x0 },
        { 0x0, 0x3, 0x0, 0x0 },
    },
    {
        { 0xE, 0x8, 0x2, 0x0 },
        { 0x12, 0x0, 0x6, 0x0 },
        { 0x0, 0x2, 0x1, 0x0 },
    },
    {
        { 0x12, 0xC, 0x0, 0x6 },
        { 0x12, 0x0, 0x6, 0xC },
        { 0x0, 0x2, 0x3, 0x1 },
    },
};

static const u8 sPlayerRowOrder[4][4] = {
    { 0x0, 0x0, 0x0, 0x0 },
    { 0x0, 0x1, 0x0, 0x0 },
    { 0x0, 0x2, 0x1, 0x0 },
    { 0x0, 0x3, 0x1, 0x2 }
};

static const GXBanks sResultsScreenGXBanks = {
    GX_VRAM_BG_256_AB,
    GX_VRAM_BGEXTPLTT_NONE,
    GX_VRAM_SUB_BG_32_H,
    GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_16_G,
    GX_VRAM_OBJEXTPLTT_NONE,
    GX_VRAM_SUB_OBJ_16_I,
    GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE,
    GX_VRAM_TEXPLTT_NONE
};

static const GraphicsModes sResultsScreenGraphicsModes = {
    GX_DISPMODE_GRAPHICS,
    GX_BGMODE_0,
    GX_BGMODE_0,
    GX_BG0_AS_2D
};

static const WiFiLobbyMinigameBgTemplate sResultsScreenBgTemplates[6] = {
    {
        0x3,
        {
            .x = 0x0,
            .y = 0x0,
            .bufferSize = 0x800,
            .baseTile = 0x0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0x3,
            .areaOver = 0x0,
            .mosaic = FALSE,
        },
    },
    {
        0x1,
        {
            .x = 0x0,
            .y = 0x0,
            .bufferSize = 0x1000,
            .baseTile = 0x0,
            .screenSize = BG_SCREEN_SIZE_512x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xd800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0x2,
            .areaOver = 0x0,
            .mosaic = FALSE,
        },
    },
    {
        0x2,
        {
            .x = 0x0,
            .y = 0x0,
            .bufferSize = 0x800,
            .baseTile = 0x0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xd000,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0x0,
            .areaOver = 0x0,
            .mosaic = FALSE,
        },
    },
    {
        0x0,
        {
            .x = 0x0,
            .y = 0x0,
            .bufferSize = 0x1000,
            .baseTile = 0x0,
            .screenSize = BG_SCREEN_SIZE_512x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xc000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0x1,
            .areaOver = 0x0,
            .mosaic = FALSE,
        },
    },
    {
        0x4,
        {
            .x = 0x0,
            .y = 0x0,
            .bufferSize = 0x800,
            .baseTile = 0x0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x7800,
            .charBase = GX_BG_CHARBASE_0x04000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0x0,
            .areaOver = 0x0,
            .mosaic = FALSE,
        },
    },
    {
        0x5,
        {
            .x = 0x0,
            .y = 0x0,
            .bufferSize = 0x800,
            .baseTile = 0x0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x7000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0x0,
            .areaOver = 0x0,
            .mosaic = FALSE,
        },
    },
};

static const WiFiLobbyMinigameMessageIdRemap sMessageIdRemap[] = {
    { 0x0, 0x0 },
    { 0x1, 0x1 },
    { 0x2, 0x14 },
    { 0x3, 0x3 },
    { 0x4, 0x4 },
    { 0x5, 0x5 },
    { 0x6, 0x6 },
    { 0x7, 0x7 },
    { 0x8, 0x8 },
    { 0x9, 0x9 },
    { 0xA, 0x15 },
    { 0xB, 0xB },
    { 0xC, 0xC },
    { 0xD, 0xD },
    { 0xE, 0xE },
    { 0xF, 0xF },
    { 0x10, 0x10 },
    { 0x11, 0x16 },
    { 0x12, 0x17 },
    { 0x13, 0x13 },
};

void WiFiLobbyMinigame_InitPlayerContext(WiFiLobbyMinigamePlayerContext *param0, BOOL param1, SaveData *saveData, BOOL param3, WiFiPlazaLobbyMinigameParticipants *param4)
{
    int v0;
    int v1;
    u32 v2;
    TrainerInfo *v3;

    memset(param0, 0, sizeof(WiFiLobbyMinigamePlayerContext));

    param0->unk_08 = CommInfo_CountReceived();
    v2 = CommSys_CurNetId();
    v1 = 0;

    for (v0 = 0; v0 < 4; v0++) {
        v3 = CommInfo_TrainerInfo(v0);

        if (v3 != NULL) {
            if (v2 == v0) {
                param0->unk_09 = v1;
            }

            param0->unk_04[v1] = v0;
            v1++;
        }
    }

    GF_ASSERT(v1 == param0->unk_08);

    if (param1 == 0) {
        param0->unk_0B = 1;
    }

    param0->saveData = saveData;
    param0->unk_0A = param3;
    param0->unk_0C = param4;
}

u32 WiFiLobbyMinigame_GetPlayerIndex(const WiFiLobbyMinigamePlayerContext *param0, u32 param1)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_08; v0++) {
        if (param0->unk_04[v0] == param1) {
            return v0;
        }
    }

    return 4;
}

u32 WiFiLobbyMinigame_GetNetIdByIndex(const WiFiLobbyMinigamePlayerContext *param0, u32 param1)
{
    GF_ASSERT(param1 < param0->unk_08);

    return param0->unk_04[param1];
}

BOOL WiFiLobbyMinigame_IsPlayerReady(const WiFiLobbyMinigamePlayerContext *param0, u32 param1)
{
    u32 v0;
    BOOL v1;

    if (param1 >= 4) {
        GF_ASSERT(param1 < 4);
        return 0;
    }

    v0 = param0->unk_0C->userIDs.playerIndices[param1];

    if (v0 == 0xffffffff) {
        return 0;
    }

    v1 = param0->unk_0C->presentFlags.flags[v0];

    return v1;
}

TrainerInfo *WiFiLobbyMinigame_GetTrainerInfo(const WiFiLobbyMinigamePlayerContext *param0, u32 param1)
{
    u32 v0;

    if (param1 >= 4) {
        GF_ASSERT(param1 < 4);
        return NULL;
    }

    if (param0->unk_0B == 1) {
        v0 = WiFiLobbyMinigame_GetPlayerIndex(param0, param1);

        if (v0 == param0->unk_09) {
            return SaveData_GetTrainerInfo(param0->saveData);
        }

        return CommInfo_TrainerInfo(param1);
    }

    GF_ASSERT(param0->unk_0C != NULL);
    return param0->unk_0C->trainerInfos[param1];
}

WiFiLobbyMinigameIntroScreen *WiFiLobbyMinigame_CreateIntroScreen0(const WiFiLobbyMinigamePlayerContext *param0, u32 heapID)
{
    return WiFiLobbyMinigame_CreateIntroScreenInternal(param0, WiFiPlazaLobbyActivity_00, heapID);
}

WiFiLobbyMinigameIntroScreen *WiFiLobbyMinigame_CreateIntroScreen1(const WiFiLobbyMinigamePlayerContext *param0, u32 heapID)
{
    return WiFiLobbyMinigame_CreateIntroScreenInternal(param0, WiFiPlazaLobbyActivity_01, heapID);
}

WiFiLobbyMinigameIntroScreen *WiFiLobbyMinigame_CreateIntroScreen2(const WiFiLobbyMinigamePlayerContext *param0, u32 heapID)
{
    return WiFiLobbyMinigame_CreateIntroScreenInternal(param0, WiFiPlazaLobbyActivity_02, heapID);
}

void WiFiLobbyMinigame_FreeIntroScreen(WiFiLobbyMinigameIntroScreen *param0)
{
    SysTask_Done(param0->unk_650);
    SysTask_Done(param0->unk_654);

    WiFiLobbyMinigame_FreeScrollEffect(&param0->unk_348);
    WiFiLobbyMinigame_FreeGameTitle(&param0->unk_230);

    {
        int v0;

        for (v0 = 0; v0 < param0->unk_08.unk_08; v0++) {
            WiFiLobbyMinigame_FreePlayerRow(&param0->unk_268[v0]);
        }
    }

    WiFiLobbyMinigame_FreeMessageBox(&param0->unk_4C);
    WiFiLobbyMinigame_FreeIntroScreenGraphics(param0);
    WiFiLobbyMinigame_FreeMessages(&param0->unk_3C);
    WiFiLobbyMinigame_FreeSpriteResources(&param0->unk_214);
    WiFiLobbyMinigame_FreeSpriteSystem(&param0->unk_84);
    WiFiLobbyMinigame_FreeBackgrounds(&param0->unk_30);

    Heap_Free(param0);
}

BOOL WiFiLobbyMinigame_IntroScreenIsDone(const WiFiLobbyMinigameIntroScreen *param0)
{
    if (param0->unk_00 >= 16) {
        return 1;
    }

    return 0;
}

int WiFiLobbyMinigame_IntroScreenGetResult(const WiFiLobbyMinigameIntroScreen *param0)
{
    GF_ASSERT(param0->unk_07 == 1);
    return param0->unk_06;
}

WiFiLobbyMinigameResultsScreen *WiFiLobbyMinigame_CreateResultsScreen0(const WiFiLobbyMinigamePlayerContext *param0, const WiFiLobbyMinigameRanking *param1, u32 heapID)
{
    return WiFiLobbyMinigame_CreateResultsScreenInternal(param0, param1, WiFiPlazaLobbyActivity_00, heapID);
}

WiFiLobbyMinigameResultsScreen *WiFiLobbyMinigame_CreateResultsScreen1(const WiFiLobbyMinigamePlayerContext *param0, const WiFiLobbyMinigameRanking *param1, u32 heapID)
{
    return WiFiLobbyMinigame_CreateResultsScreenInternal(param0, param1, WiFiPlazaLobbyActivity_01, heapID);
}

WiFiLobbyMinigameResultsScreen *WiFiLobbyMinigame_CreateResultsScreen2(const WiFiLobbyMinigamePlayerContext *param0, const WiFiLobbyMinigameRanking *param1, u32 heapID)
{
    return WiFiLobbyMinigame_CreateResultsScreenInternal(param0, param1, WiFiPlazaLobbyActivity_02, heapID);
}

void WiFiLobbyMinigame_FreeResultsScreen(WiFiLobbyMinigameResultsScreen *param0)
{
    SysTask_Done(param0->unk_6A8);
    SysTask_Done(param0->unk_6AC);

    WiFiLobbyMinigame_FreeScrollEffect(&param0->unk_3A0);

    {
        int v0;

        for (v0 = 0; v0 < param0->unk_0C.unk_08; v0++) {
            WiFiLobbyMinigame_FreePlayerRow(&param0->unk_2C0[v0]);
        }
    }

    WiFiLobbyMinigame_FreeReplayMenu(&param0->unk_24C);
    WiFiLobbyMinigame_FreeResultsScreenGraphics(param0);
    WiFiLobbyMinigame_FreeMessageBox(&param0->unk_68);
    WiFiLobbyMinigame_FreeMessages(&param0->unk_58);
    WiFiLobbyMinigame_FreeSpriteResources(&param0->unk_230);
    WiFiLobbyMinigame_FreeSpriteSystem(&param0->unk_A0);
    WiFiLobbyMinigame_FreeBackgrounds(&param0->unk_4C);

    G2_BlendNone();
    G2S_BlendNone();

    VramTransfer_Free();
    Heap_Free(param0);
}

BOOL WiFiLobbyMinigame_ResultsScreenIsDone(const WiFiLobbyMinigameResultsScreen *param0)
{
    return param0->unk_06;
}

BOOL WiFiLobbyMinigame_ResultsScreenGetResult(const WiFiLobbyMinigameResultsScreen *param0)
{
    return param0->unk_08;
}

void WiFiLobbyMinigame_InitRanking(WiFiLobbyMinigameRanking *param0, u32 param1)
{
    u8 v0[4];
    int v1, v2;

    for (v1 = 0; v1 < param1; v1++) {
        for (v2 = v1; v2 > 0; v2--) {
            if (param0->unk_00[v1] <= param0->unk_00[v0[v2 - 1]]) {
                break;
            } else {
                v0[v2] = v0[v2 - 1];
            }
        }

        v0[v2] = v1;
    }

    {
        for (v1 = 0; v1 < param1; v1++) {
            (void)0;
        }
    }

    {
        u32 v3;

        for (v1 = 0; v1 < param1; v1++) {
            v3 = v1;

            if (v1 > 0) {
                if (param0->unk_00[v0[v1]] == param0->unk_00[v0[v1 - 1]]) {
                    v3 = param0->unk_10[v0[v1 - 1]];
                }
            }

            param0->unk_10[v0[v1]] = v3;
        }
    }
}

void WiFiLobbyMinigame_IntroScreenSetResult(WiFiLobbyMinigameIntroScreen *param0, int param1)
{
    param0->unk_06 = param1;
    param0->unk_07 = 1;
}

void WiFiLobbyMinigame_ResultsScreenSetPlayerReady(WiFiLobbyMinigameResultsScreen *param0, u32 param1, BOOL param2)
{
    if (param0->unk_0C.unk_09 == 0) {
        WiFiLobbyMinigame_ReplayMenuSetPlayerReady(&param0->unk_24C, param1, param2, param0->unk_0C.unk_08);
    }
}

void WiFiLobbyMinigame_ResultsScreenSetAllReady(WiFiLobbyMinigameResultsScreen *param0, BOOL param1)
{
    WiFiLobbyMinigame_ReplayMenuSetAllReady(&param0->unk_24C, param1);
}

BOOL WiFiLobbyMinigame_CheckDisconnected(WiFiLobbyMinigamePlayerContext *param0)
{
    BOOL v0 = 0;

    if (param0->unk_0C != NULL) {
        if (param0->unk_08 != CommSys_ConnectedCount()) {
            v0 = 1;
        }

        if (CommManager_GetDisconnectedWifi() == 1) {
            v0 = 1;
        }

        if (CommManager_GetMatchmakingState() >= 2) {
            v0 = 1;
        }

        if (v0 == 1) {
            param0->unk_0C->trainerInfoValid = 1;
        }

        if (param0->unk_0C->trainerInfoValid == 1) {
            v0 = 1;
        }
    }

    return v0;
}

BOOL WiFiLobbyMinigame_HandleDisconnect(const WiFiLobbyMinigamePlayerContext *param0)
{
    GF_ASSERT(param0->unk_0C != NULL);
    GF_ASSERT(param0->unk_0C->trainerInfoValid == 1);

    if (CommInfo_IsInitialized() == 1) {
        CommInfo_Delete();
        CommManager_EndWifiP2P();
    } else {
        if (CommManager_IsLoginBattleMatchWifi() == 1) {
            return 1;
        }
    }

    return 0;
}

WiFiLobbyMinigameIntroAnimation *WiFiLobbyMinigame_CreateIntroAnimation(SpriteList *param0, u32 heapID)
{
    WiFiLobbyMinigameIntroAnimation *v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMinigameIntroAnimation));
    memset(v0, 0, sizeof(WiFiLobbyMinigameIntroAnimation));

    v0->unk_08 = param0;
    v0->unk_0C = NARC_ctor(NARC_INDEX_RESOURCE__ENG__WIFI_LOBBY_MINIGAME__WLMNGM_TOOL, heapID);

    WiFiLobbyMinigame_InitSpriteResources(&v0->unk_10, 1, heapID);

    v0->unk_28 = WiFiLobbyMinigame_AllocSpriteResource(&v0->unk_10, v0->unk_0C, 3, 3, 2, 1, 0, 5000, heapID);

    return v0;
}

void WiFiLobbyMinigame_FreeIntroAnimation(WiFiLobbyMinigameIntroAnimation *param0)
{
    if (param0->unk_2C != NULL) {
        SysTask_Done(param0->unk_2C);
        param0->unk_2C = NULL;
    }

    if (param0->unk_30 != NULL) {
        Sprite_Delete(param0->unk_30);
    }

    WiFiLobbyMinigame_FreeCurtain(&param0->unk_34);
    WiFiLobbyMinigame_FreeSpriteResources(&param0->unk_10);

    NARC_dtor(param0->unk_0C);
    Heap_Free(param0);
}

int WiFiLobbyMinigame_GetIntroAnimationPaletteOffset(WiFiLobbyMinigameIntroAnimation *param0)
{
    SpriteResource *v0 = SpriteResourceCollection_Find(param0->unk_10.unk_00[1], 5000);
    return SpriteTransfer_GetPlttOffset(v0, NNS_G2D_VRAM_TYPE_2DMAIN);
}

void WiFiLobbyMinigame_StartIntroAnimationRoll(WiFiLobbyMinigameIntroAnimation *param0)
{
    GF_ASSERT(param0->unk_2C == NULL);
    param0->unk_2C = SysTask_Start(WiFiLobbyMinigame_IntroAnimationRollTask, param0, 0);
    param0->unk_04 = 1;
}

void WiFiLobbyMinigame_StartIntroAnimationPop(WiFiLobbyMinigameIntroAnimation *param0)
{
    GF_ASSERT(param0->unk_2C == NULL);
    param0->unk_2C = SysTask_Start(WiFiLobbyMinigame_IntroAnimationPopTask, param0, 0);
    param0->unk_04 = 1;

    Sound_PlayEffect(SEQ_SE_DP_PINPON_sseq);
}

BOOL WiFiLobbyMinigame_IntroAnimationIsDone(const WiFiLobbyMinigameIntroAnimation *param0)
{
    if (param0->unk_04 == 0) {
        return 1;
    }

    return 0;
}

static void WiFiLobbyMinigame_InitMotion(WiFiLobbyMinigameMotion *param0, fx32 param1, fx32 param2, fx32 param3, int param4)
{
    fx32 v0;
    fx32 v1;
    fx32 v2;
    fx32 v3;

    v2 = param2 - param1;
    v0 = (param4 * param4) << FX32_SHIFT;
    v1 = FX_Mul(param3, param4 * FX32_ONE);
    v1 = v2 - v1;
    v1 = FX_Mul(v1, 2 * FX32_ONE);
    v3 = FX_Div(v1, v0);

    param0->unk_00 = param1;
    param0->unk_04 = param1;
    param0->unk_08 = param3;
    param0->unk_0C = v3;
    param0->unk_10 = param4;
}

static BOOL WiFiLobbyMinigame_UpdateMotion(WiFiLobbyMinigameMotion *param0, s32 param1)
{
    fx32 v0;
    fx32 v1;
    fx32 v2;
    fx32 v3;
    BOOL v4;

    if (param1 >= param0->unk_10) {
        param1 = param0->unk_10;
        v4 = 1;
    } else {
        v4 = 0;
    }

    v3 = FX_Mul(param0->unk_08, param1 << FX32_SHIFT);
    v1 = (param1 * param1) << FX32_SHIFT;
    v2 = FX_Mul(param0->unk_0C, v1);
    v2 = FX_Div(v2, 2 * FX32_ONE);
    v0 = v3 + v2;

    param0->unk_00 = param0->unk_04 + v0;

    return v4;
}

static void WiFiLobbyMinigame_OffsetScreenData(NNSG2dScreenData *param0, u32 param1)
{
    int v0;
    u16 *v1;
    int v2 = param0->szByte / 2;
    v1 = (u16 *)param0->rawData;

    for (v0 = 0; v0 < v2; v0++) {
        v1[v0] += param1;
    }
}

static void WiFiLobbyMinigame_InitSpriteResources(WiFiLobbyMinigameSpriteResources *param0, u32 param1, u32 heapID)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        param0->unk_00[v0] = SpriteResourceCollection_New(param1, v0, heapID);
    }

    param0->unk_10 = Heap_Alloc(heapID, sizeof(WiFiLobbyMinigameSpriteResource) * param1);
    memset(param0->unk_10, 0, sizeof(WiFiLobbyMinigameSpriteResource) * param1);
    param0->unk_14 = param1;
}

static void WiFiLobbyMinigame_FreeSpriteResources(WiFiLobbyMinigameSpriteResources *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_14; v0++) {
        if (param0->unk_10[v0].unk_00 == 1) {
            WiFiLobbyMinigame_UnloadSpriteResource(param0, &param0->unk_10[v0]);
        }
    }

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(param0->unk_00[v0]);
    }

    Heap_Free(param0->unk_10);
}

static WiFiLobbyMinigameSpriteResource *WiFiLobbyMinigame_AllocSpriteResource(WiFiLobbyMinigameSpriteResources *param0, NARC *param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8)
{
    int v0;
    WiFiLobbyMinigameSpriteResource *v1 = NULL;

    for (v0 = 0; v0 < param0->unk_14; v0++) {
        if (param0->unk_10[v0].unk_00 == 0) {
            v1 = &param0->unk_10[v0];
            break;
        }
    }

    GF_ASSERT(v1);

    WiFiLobbyMinigame_LoadSpriteResource(param0, v1, param1, param2, param3, param4, param5, param6, param7, param8);

    return v1;
}

static Sprite *WiFiLobbyMinigame_AddSprite(WiFiLobbyMinigameSpriteResource *param0, SpriteList *param1, s16 param2, s16 param3, u16 param4, u32 param5)
{
    SpriteListTemplate v0;

    v0.list = param1;
    v0.resourceData = &param0->unk_14;
    v0.position.x = param2 << FX32_SHIFT;
    v0.position.y = param3 << FX32_SHIFT;
    v0.priority = param4;
    v0.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v0.heapID = param5;

    return SpriteList_Add(&v0);
}

static void WiFiLobbyMinigame_LoadSpriteResource(WiFiLobbyMinigameSpriteResources *param0, WiFiLobbyMinigameSpriteResource *param1, NARC *param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9)
{
    BOOL v0;

    GF_ASSERT(param1->unk_00 == 0);

    param1->unk_00 = 1;
    param1->unk_04[0] = SpriteResourceCollection_AddTilesFrom(param0->unk_00[0], param2, param5, 0, param8, NNS_G2D_VRAM_TYPE_2DMAIN, param9);
    param1->unk_04[1] = SpriteResourceCollection_AddPaletteFrom(param0->unk_00[1], param2, param3, 0, param8, NNS_G2D_VRAM_TYPE_2DMAIN, param4, param9);
    param1->unk_04[2] = SpriteResourceCollection_AddFrom(param0->unk_00[2], param2, param6, 0, param8, 2, param9);
    param1->unk_04[3] = SpriteResourceCollection_AddFrom(param0->unk_00[3], param2, param7, 0, param8, 3, param9);

    v0 = SpriteTransfer_RequestCharAtEnd(param1->unk_04[0]);
    GF_ASSERT(v0);

    SpriteResource_ReleaseData(param1->unk_04[0]);

    v0 = SpriteTransfer_RequestPlttFreeSpace(param1->unk_04[1]);
    GF_ASSERT(v0);

    SpriteResource_ReleaseData(param1->unk_04[1]);
    SpriteResourcesHeader_Init(&param1->unk_14, param8, param8, param8, param8, 0xffffffff, 0xffffffff, 0, 1, param0->unk_00[0], param0->unk_00[1], param0->unk_00[2], param0->unk_00[3], NULL, NULL);
}

static void WiFiLobbyMinigame_UnloadSpriteResource(WiFiLobbyMinigameSpriteResources *param0, WiFiLobbyMinigameSpriteResource *param1)
{
    int v0;

    GF_ASSERT(param1->unk_00 == 1);

    param1->unk_00 = 0;

    SpriteTransfer_ResetCharTransfer(param1->unk_04[0]);
    SpriteTransfer_ResetPlttTransfer(param1->unk_04[1]);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Remove(param0->unk_00[v0], param1->unk_04[v0]);
    }
}

static void WiFiLobbyMinigame_InitBackgrounds(WiFiLobbyMinigameBackgrounds *param0, const GraphicsModes *param1, const WiFiLobbyMinigameBgTemplate *param2, u32 param3, enum HeapID heapID)
{
    SetAllGraphicsModes(param1);

    param0->unk_00 = BgConfig_New(heapID);
    param0->unk_04 = param2;
    param0->unk_08 = param3;

    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;
    GXLayers_SwapDisplay();

    {
        int v0;

        for (v0 = 0; v0 < param3; v0++) {
            Bg_InitFromTemplate(param0->unk_00, param2[v0].unk_00, &param2[v0].unk_04, 0);
            Bg_ClearTilesRange(param2[v0].unk_00, 32, 0, heapID);
            Bg_ClearTilemap(param0->unk_00, param2[v0].unk_00);
            Bg_SetOffset(param0->unk_00, param2[v0].unk_00, 0, 0);
            Bg_SetOffset(param0->unk_00, param2[v0].unk_00, 3, 0);
        }
    }
}

static void WiFiLobbyMinigame_FreeBackgrounds(WiFiLobbyMinigameBackgrounds *param0)
{
    Bg_SetOffset(param0->unk_00, BG_LAYER_MAIN_3, 3, 0);

    {
        int v0;

        for (v0 = 0; v0 < param0->unk_08; v0++) {
            Bg_FreeTilemapBuffer(param0->unk_00, param0->unk_04[v0].unk_00);
        }
    }

    Heap_Free(param0->unk_00);
}

static void WiFiLobbyMinigame_RunBackgroundUpdates(WiFiLobbyMinigameBackgrounds *param0)
{
    Bg_RunScheduledUpdates(param0->unk_00);
}

static void WiFiLobbyMinigame_InitSpriteSystem(WiFiLobbyMinigameSpriteSystem *param0, u32 param1, u32 param2, u32 param3, u32 param4)
{
    int v0;

    NNS_G2dInitOamManagerModule();
    RenderOam_Init(0, 126, 0, 31, 0, 126, 0, 31, param4);

    {
        CharTransferTemplate v1 = sCharTransferTemplate;

        v1.maxTasks = param2;
        v1.heapID = param4;

        CharTransfer_InitWithVramModes(&v1, GX_OBJVRAMMODE_CHAR_1D_32K, GX_OBJVRAMMODE_CHAR_1D_32K);
    }

    PlttTransfer_Init(param3, param4);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_32K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    param0->unk_00 = SpriteList_InitRendering(param1, &param0->unk_04, param4);

    NetworkIcon_Init();
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void WiFiLobbyMinigame_FreeSpriteSystem(WiFiLobbyMinigameSpriteSystem *param0)
{
    SpriteList_Delete(param0->unk_00);
    CharTransfer_Free();
    PlttTransfer_Free();
    RenderOam_Free();
}

static void WiFiLobbyMinigame_UpdateSprites(WiFiLobbyMinigameSpriteSystem *param0)
{
    SpriteList_Update(param0->unk_00);
}

static void WiFiLobbyMinigame_TransferOam(WiFiLobbyMinigameSpriteSystem *param0)
{
    RenderOam_Transfer();
}

static void WiFiLobbyMinigame_InitMessages(WiFiLobbyMinigameMessages *param0, u32 heapID)
{
    param0->unk_00 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0411, heapID);
    param0->unk_04 = StringTemplate_New(8, 64, heapID);
    param0->unk_08 = String_Init(128, heapID);
    param0->unk_0C = String_Init(128, heapID);

    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(12), heapID);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_SUB_BG, PLTT_OFFSET(12), heapID);
}

static void WiFiLobbyMinigame_FreeMessages(WiFiLobbyMinigameMessages *param0)
{
    String_Free(param0->unk_0C);
    String_Free(param0->unk_08);
    StringTemplate_Free(param0->unk_04);
    MessageLoader_Free(param0->unk_00);
}

static void WiFiLobbyMinigame_ClearMessageArgs(WiFiLobbyMinigameMessages *param0)
{
    StringTemplate_ClearArgs(param0->unk_04);
}

static void WiFiLobbyMinigame_SetMessagePlayerName(WiFiLobbyMinigameMessages *param0, const TrainerInfo *param1)
{
    StringTemplate_SetPlayerName(param0->unk_04, 0, param1);
}

static void WiFiLobbyMinigame_SetMessageCountryName(WiFiLobbyMinigameMessages *param0, u32 param1)
{
    StringTemplate_SetCountryName(param0->unk_04, 0, param1);
}

static void WiFiLobbyMinigame_SetMessageCityName(WiFiLobbyMinigameMessages *param0, u32 param1, u32 param2)
{
    StringTemplate_SetCityName(param0->unk_04, 0, param1, param2);
}

static void WiFiLobbyMinigame_SetMessageNumber(WiFiLobbyMinigameMessages *param0, u32 param1, u32 param2)
{
    StringTemplate_SetNumber(param0->unk_04, 0, param1, param2, 1, 1);
}

static void WiFiLobbyMinigame_SetMessageRankNumber(WiFiLobbyMinigameMessages *param0, u32 param1)
{
    StringTemplate_SetNumber(param0->unk_04, 0, param1, 2, 1, 1);
}

static void WiFiLobbyMinigame_SetMessagePlazaItemName(WiFiLobbyMinigameMessages *param0, u32 param1)
{
    StringTemplate_SetPlazaItemName(param0->unk_04, 1, param1);
}

static void WiFiLobbyMinigame_SetMessageMinigameName(WiFiLobbyMinigameMessages *param0, u32 param1)
{
    StringTemplate_SetPlazaMinigameName(param0->unk_04, 0, param1);
}

static void WiFiLobbyMinigame_DrawMessage(WiFiLobbyMinigameMessages *param0, String *param1, u32 param2)
{
    MessageLoader_GetString(param0->unk_00, param2, param0->unk_0C);
    StringTemplate_Format(param0->unk_04, param1, param0->unk_0C);
}

static void WiFiLobbyMinigame_DrawMessageLeft(WiFiLobbyMinigameMessages *param0, u32 param1, Window *param2, u8 param3, u8 param4)
{
    WiFiLobbyMinigame_DrawMessageWithColor(param0, param1, param2, param3, param4, TEXT_COLOR(15, 14, 0));
}

static void WiFiLobbyMinigame_DrawMessageRightAligned(WiFiLobbyMinigameMessages *param0, u32 param1, Window *param2, u8 param3, u8 param4)
{
    u32 v0;
    s32 v1;

    MessageLoader_GetString(param0->unk_00, param1, param0->unk_0C);
    StringTemplate_Format(param0->unk_04, param0->unk_08, param0->unk_0C);

    v0 = Font_CalcStringWidth(FONT_SYSTEM, param0->unk_08, 0);
    v1 = param3 - v0;

    if (v1 < 0) {
        v1 = 0;
    }

    Text_AddPrinterWithParamsAndColor(param2, FONT_SYSTEM, param0->unk_08, v1, param4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
}

static u32 WiFiLobbyMinigame_PrintMessage(WiFiLobbyMinigameMessages *param0, u32 param1, Window *param2, String *param3, u32 param4)
{
    MessageLoader_GetString(param0->unk_00, param1, param0->unk_0C);
    StringTemplate_Format(param0->unk_04, param3, param0->unk_0C);

    return Text_AddPrinterWithParamsAndColor(param2, FONT_MESSAGE, param3, 0, 0, param4, TEXT_COLOR(1, 2, 15), NULL);
}

static void WiFiLobbyMinigame_DrawMessageWithColor(WiFiLobbyMinigameMessages *param0, u32 param1, Window *param2, u8 param3, u8 param4, TextColor param5)
{
    MessageLoader_GetString(param0->unk_00, param1, param0->unk_0C);
    StringTemplate_Format(param0->unk_04, param0->unk_08, param0->unk_0C);
    Text_AddPrinterWithParamsAndColor(param2, FONT_SYSTEM, param0->unk_08, param3, param4, TEXT_SPEED_NO_TRANSFER, param5, NULL);
}

static void WiFiLobbyMinigame_InitMessageBox(WiFiLobbyMinigameMessageBox *param0, WiFiLobbyMinigameBackgrounds *param1, SaveData *saveData, BOOL param3, u32 heapID)
{
    u32 v0 = Options_Frame(SaveData_GetOptions(saveData));
    u32 v1;
    int v2;
    u8 v3;

    SetLockTextWithAutoScroll(TRUE);
    LoadMessageBoxGraphics(param1->unk_00, BG_LAYER_MAIN_2, 1, 13, v0, heapID);
    LoadMessageBoxGraphics(param1->unk_00, BG_LAYER_SUB_0, 1, 13, v0, heapID);

    for (v2 = 0; v2 < 2; v2++) {
        if (v2 == 0) {
            v1 = 2;
            v3 = 19;
        } else {
            v1 = 4;
            v3 = 1;
        }

        Window_Add(param1->unk_00, &param0->unk_00[v2], v1, 2, v3, 27, 4, 12, 1 + (18 + 12));
        Window_FillTilemap(&param0->unk_00[v2], 0);

        param0->unk_24[v2] = String_Init(128, heapID);
    }

    param0->unk_34 = param3;
}

static void WiFiLobbyMinigame_FreeMessageBox(WiFiLobbyMinigameMessageBox *param0)
{
    int v0;

    for (v0 = 0; v0 < 2; v0++) {
        WiFiLobbyMinigame_HideMessage(param0, v0);
        String_Free(param0->unk_24[v0]);
        Window_Remove(&param0->unk_00[v0]);
    }

    LockTextSpeed();
}

static void WiFiLobbyMinigame_ShowMessage(WiFiLobbyMinigameMessageBox *param0, WiFiLobbyMinigameMessages *param1, u32 param2, u32 param3)
{
    int v0;

    if (param0->unk_34 == 1) {
        for (v0 = 0; v0 < NELEMS(sMessageIdRemap); v0++) {
            if (sMessageIdRemap[v0].unk_00 == param2) {
                param2 = sMessageIdRemap[v0].unk_02;
            }
        }
    }

    if (Text_IsPrinterActive(param0->unk_20[param3])) {
        Text_RemovePrinter(param0->unk_20[param3]);
    }

    WiFiLobbyMinigame_HideWaitDial(param0, param3);
    Window_FillTilemap(&param0->unk_00[param3], 15);
    param0->unk_20[param3] = WiFiLobbyMinigame_PrintMessage(param1, param2, &param0->unk_00[param3], param0->unk_24[param3], TEXT_SPEED_FAST);
    Window_DrawMessageBoxWithScrollCursor(&param0->unk_00[param3], 1, 1, 13);
    Window_ScheduleCopyToVRAM(&param0->unk_00[param3]);
}

static void WiFiLobbyMinigame_HideMessage(WiFiLobbyMinigameMessageBox *param0, u32 param1)
{
    WiFiLobbyMinigame_HideWaitDial(param0, param1);

    if (Text_IsPrinterActive(param0->unk_20[param1])) {
        Text_RemovePrinter(param0->unk_20[param1]);
    }

    Window_EraseMessageBox(&param0->unk_00[param1], 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->unk_00[param1]);
}

static BOOL WiFiLobbyMinigame_IsMessageDone(const WiFiLobbyMinigameMessageBox *param0, u32 param1)
{
    u32 v0 = Text_IsPrinterActive(param0->unk_20[param1]);

    if (v0 == 0) {
        return 1;
    }

    return 0;
}

static void WiFiLobbyMinigame_ShowWaitDial(WiFiLobbyMinigameMessageBox *param0, u32 param1)
{
    if (param0->unk_2C[param1] == NULL) {
        param0->unk_2C[param1] = Window_AddWaitDial(&param0->unk_00[param1], 1);
    }
}

static void WiFiLobbyMinigame_HideWaitDial(WiFiLobbyMinigameMessageBox *param0, u32 param1)
{
    if (param0->unk_2C[param1]) {
        DestroyWaitDialTaskOnly(param0->unk_2C[param1]);
        param0->unk_2C[param1] = NULL;
    }
}

static WiFiLobbyMinigameIntroScreen *WiFiLobbyMinigame_CreateIntroScreenInternal(const WiFiLobbyMinigamePlayerContext *param0, u32 param1, u32 heapID)
{
    WiFiLobbyMinigameIntroScreen *v0;
    int v1;

    Sound_SetSceneAndPlayBGM(SOUND_SCENE_19, SEQ_PL_WIFIGAME_sseq, 0);

    v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMinigameIntroScreen));
    memset(v0, 0, sizeof(WiFiLobbyMinigameIntroScreen));
    memcpy(&v0->unk_08, param0, sizeof(WiFiLobbyMinigamePlayerContext));

    v0->unk_04 = param1;

    G2_BlendNone();
    G2S_BlendNone();
    GX_SetVisibleWnd(0);
    GXS_SetVisibleWnd(0);

    GXLayers_SetBanks(&sIntroScreenGXBanks);

    v0->heapID = heapID;

    WiFiLobbyMinigame_InitCommCmdIntro(v0);
    WiFiLobbyMinigame_InitPlayerInfo(&v0->unk_18, &v0->unk_08);
    WiFiLobbyMinigame_InitBackgrounds(&v0->unk_30, &sIntroScreenGraphicsModes, sIntroScreenBgTemplates, 5, heapID);
    WiFiLobbyMinigame_InitSpriteSystem(&v0->unk_84, 16, 1, 1, heapID);
    WiFiLobbyMinigame_InitSpriteResources(&v0->unk_214, 1, heapID);
    WiFiLobbyMinigame_InitMessages(&v0->unk_3C, heapID);
    WiFiLobbyMinigame_LoadIntroScreenGraphics(v0, heapID);

    {
        BOOL v2;
        u32 v3;

        v3 = WiFiLobbyMinigame_GetNetIdByIndex(&v0->unk_08, v0->unk_08.unk_09);
        v2 = WiFiLobbyMinigame_IsPlayerReady(&v0->unk_08, v3);

        WiFiLobbyMinigame_InitMessageBox(&v0->unk_4C, &v0->unk_30, v0->unk_08.saveData, v2, heapID);
    }

    v0->unk_650 = SysTask_Start(WiFiLobbyMinigame_IntroScreenTask, v0, 0);
    v0->unk_654 = SysTask_ExecuteAfterVBlank(WiFiLobbyMinigame_IntroScreenVBlankTask, v0, 0);

    if (v0->unk_08.unk_0A) {
        NintendoWFC_StartVoiceChat(heapID);
    }

    return v0;
}

static void WiFiLobbyMinigame_LoadIntroScreenGraphics(WiFiLobbyMinigameIntroScreen *param0, u32 heapID)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_RESOURCE__ENG__WIFI_LOBBY_MINIGAME__WLMNGM_TOOL, heapID);

    Graphics_LoadPaletteFromOpenNARC(v0, 4, 0, 0, 9 * 32, heapID);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 6, param0->unk_30.unk_00, 1, 0, 0, 0, heapID);

    param0->unk_260 = Graphics_GetScrnDataFromOpenNARC(v0, 9, 0, &param0->unk_264, heapID);

    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 8, param0->unk_30.unk_00, 3, 0, 0, 0, heapID);
    WiFiLobbyMinigame_LoadMinigamePalette(v0, param0->unk_04, heapID);

    param0->unk_22C = WiFiLobbyMinigame_AllocSpriteResource(&param0->unk_214, v0, 11, 5, 12, 13, 14, 5000, heapID);

    WiFiLobbyMinigame_InitGameTitle(&param0->unk_230, &param0->unk_30, &param0->unk_3C, param0->unk_04, v0, heapID);
    NARC_dtor(v0);
}

static void WiFiLobbyMinigame_FreeIntroScreenGraphics(WiFiLobbyMinigameIntroScreen *param0)
{
    Heap_Free(param0->unk_260);
}

static void WiFiLobbyMinigame_IntroScreenTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameIntroScreen *v0 = param1;
    BOOL v1;

    switch (v0->unk_00) {
    case 0:
        StartScreenFade(FADE_MAIN_ONLY, 1, 1, 0xffff, 6, 1, v0->heapID);
        WiFiLobbyMinigame_ShowGameTitle(&v0->unk_230, &v0->unk_30, v0->heapID);
        v0->unk_00++;
        break;
    case 1:
        WiFiLobbyMinigame_UpdateGameTitleShow(&v0->unk_230, &v0->unk_30);
        v1 = IsScreenFadeDone();

        if (v1 == 1) {
            v0->unk_00++;
        }
        break;
    case 2:
        v1 = WiFiLobbyMinigame_UpdateGameTitleShow(&v0->unk_230, &v0->unk_30);

        if (v1 == 1) {
            v0->unk_00++;
        }
        break;
    case 3:
        WiFiLobbyMinigame_ShowMessage(&v0->unk_4C, &v0->unk_3C, 0, 0);
        v0->unk_00++;
        break;
    case 4:
        v1 = WiFiLobbyMinigame_IsMessageDone(&v0->unk_4C, 0);

        if (v1) {
            v0->unk_00++;
            v0->unk_01 = 64;
        }
        break;
    case 5:
        if (v0->unk_01 > 0) {
            v0->unk_01--;

            if (v0->unk_01 == 0) {
                WiFiLobbyMinigame_HideMessage(&v0->unk_4C, 0);
                WiFiLobbyMinigame_HideGameTitle(&v0->unk_230, &v0->unk_30);
                v0->unk_00++;
            }
        }
        break;
    case 6:
        v1 = WiFiLobbyMinigame_UpdateGameTitleHide(&v0->unk_230, &v0->unk_30);

        if (v1 == 1) {
            v0->unk_00++;
        }
        break;
    case 7: {
        int v2;
        BOOL v3;
        BOOL v4;
        u32 v5;

        WiFiLobbyMinigame_InitScrollEffect(&v0->unk_348, &v0->unk_30, v0->heapID);

        v3 = WiFiLobbyMinigame_ArePlayersFromDifferentCountries(&v0->unk_08, &v0->unk_18);

        for (v2 = 0; v2 < v0->unk_08.unk_08; v2++) {
            WiFiLobbyMinigame_InitPlayerRow(&v0->unk_268[v2], v0->unk_08.unk_08, v0->unk_04, v0->unk_264, &v0->unk_30, v2, v0->unk_08.unk_09, &v0->unk_84, v0->unk_22C, v0->heapID);

            v5 = WiFiLobbyMinigame_GetNetIdByIndex(&v0->unk_08, v2);
            v4 = WiFiLobbyMinigame_IsPlayerReady(&v0->unk_08, v5);

            WiFiLobbyMinigame_DrawPlayerRowName(&v0->unk_268[v2], &v0->unk_3C, v0->unk_18.unk_08[v2], 8, 0, v4);
            WiFiLobbyMinigame_DrawPlayerRowLocation(&v0->unk_268[v2], &v0->unk_3C, v3, v0->unk_18.unk_00[v2], v0->unk_18.unk_04[v2], 8);
            WiFiLobbyMinigame_StartPlayerRowSlideIn(&v0->unk_268[v2], -8, 3 * v2);
        }
    }

        {
            int v6;

            for (v6 = 0; v6 < v0->unk_08.unk_08; v6++) {
                WiFiLobbyMinigame_TransferPlayerRow(&v0->unk_268[v6], &v0->unk_30);
                WiFiLobbyMinigame_ShowPlayerRowSprite(&v0->unk_268[v6]);
            }
        }

        v0->unk_01 = 92;
        v0->unk_00++;
        break;
    case 8:
        if (WiFiLobbyMinigame_UpdatePlayerRows(v0) == 1) {
            v0->unk_00++;
        }
        break;
    case 9:
        v0->unk_01--;

        if (v0->unk_01 == 0) {
            v0->unk_00++;
            CommTiming_StartSync(129);

            if (v0->unk_08.unk_0A) {
                NintendoWFC_TerminateVoiceChat();
            }
        }
        break;
    case 10:
        if (CommTiming_IsSyncState(129)) {
            v0->unk_00++;
        }
        break;
    case 11: {
        int v7;

        for (v7 = 0; v7 < v0->unk_08.unk_08; v7++) {
            WiFiLobbyMinigame_StartPlayerRowSlideOut(&v0->unk_268[v7], v7 * 3);
        }

        v0->unk_00++;
        v0->unk_01 = 8;
    } break;
    case 12:
        v0->unk_01--;
        WiFiLobbyMinigame_UpdatePlayerRows(v0);

        if (v0->unk_01 <= 0) {
            v0->unk_00++;
        }
        break;
    case 13:
        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, v0->heapID);
        WiFiLobbyMinigame_UpdatePlayerRows(v0);

        if (v0->unk_08.unk_09 == 0) {
            u32 v8;

            switch (v0->unk_04) {
            case WiFiPlazaLobbyActivity_00:
                v8 = WiFiLobbyMinigame_RandomWeightedIndex(sRandomWeightsGame0, 3);
                break;
            case WiFiPlazaLobbyActivity_01:
                v8 = WiFiLobbyMinigame_RandomWeightedIndex(sRandomWeightsGame1, 2);
                break;
            case WiFiPlazaLobbyActivity_02:
                v8 = WiFiLobbyMinigame_RandomWeightedIndex(sRandomWeightsGame2, 3);
                break;
            }

            CommSys_SendData(26, &v8, sizeof(u32));
        }

        v0->unk_00++;
        break;
    case 14:
        WiFiLobbyMinigame_UpdatePlayerRows(v0);
        v1 = IsScreenFadeDone();

        if (v1 == 1) {
            WiFiLobbyMinigame_FreeScrollEffect(&v0->unk_348);
            v0->unk_00++;
        }
        break;
    case 15:
        if (v0->unk_07 == 1) {
            v0->unk_00++;
        }
        break;
    case 16:
        break;
    }

    WiFiLobbyMinigame_UpdateSprites(&v0->unk_84);

    Bg_ScheduleScroll(v0->unk_30.unk_00, 3, 4, 2);
    Bg_ScheduleScroll(v0->unk_30.unk_00, 5, 4, 2);
}

static void WiFiLobbyMinigame_IntroScreenVBlankTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameIntroScreen *v0 = param1;

    WiFiLobbyMinigame_RunBackgroundUpdates(&v0->unk_30);
    WiFiLobbyMinigame_TransferOam(&v0->unk_84);
    WiFiLobbyMinigame_SwapScrollBuffers(&v0->unk_348);
}

static int WiFiLobbyMinigame_RandomWeightedIndex(const u8 *param0, u32 param1)
{
    u32 v0;
    u32 v1;
    int v2;

    v0 = MTRNG_Next() % 100;
    v1 = 0;

    for (v2 = 0; v2 < param1; v2++) {
        v1 += param0[v2];

        if (v1 > v0) {
            return v2;
        }
    }

    GF_ASSERT(FALSE);
    return param1 - 1;
}

static BOOL WiFiLobbyMinigame_UpdatePlayerRows(WiFiLobbyMinigameIntroScreen *param0)
{
    int v0;
    BOOL v1;
    BOOL v2 = 1;

    for (v0 = 0; v0 < param0->unk_08.unk_08; v0++) {
        if (param0->unk_268[v0].unk_10 != NULL) {
            v1 = WiFiLobbyMinigame_UpdatePlayerRowMotion(&param0->unk_268[v0]);
            WiFiLobbyMinigame_UpdateScrollEffect(&param0->unk_348, &param0->unk_268[v0]);

            if (v1 == 0) {
                v2 = 0;
            }
        } else {
            v2 = 0;
        }
    }

    return v2;
}

static void WiFiLobbyMinigame_InitPlayerRow(WiFiLobbyMinigamePlayerRow *param0, u32 param1, u32 param2, NNSG2dScreenData *param3, WiFiLobbyMinigameBackgrounds *param4, u32 param5, u32 param6, WiFiLobbyMinigameSpriteSystem *param7, WiFiLobbyMinigameSpriteResource *param8, u32 heapID)
{
    s32 v0;

    switch (param2) {
    case WiFiPlazaLobbyActivity_00:
    case WiFiPlazaLobbyActivity_02:
        v0 = WiFiLobbyMinigame_GetPlayerRowOrder(param1, param5, param6);
        break;
    case WiFiPlazaLobbyActivity_01:
        if (param6 > param5) {
            v0 = param5 + 1;
        } else if (param6 == param5) {
            v0 = 0;
        } else {
            v0 = param5;
        }
        break;
    default:
        v0 = param5;
        break;
    }

    Bg_SetPriority(BG_LAYER_MAIN_1, 2);
    Bg_SetPriority(BG_LAYER_MAIN_0, 1);
    Window_Add(param4->unk_00, &param0->unk_00, 0, 5, 1 + sPlayerRowLayouts[param1 - 1].unk_00[v0], 26, 4, 12, 513 + ((26 * 4) * param5));
    Window_FillTilemap(&param0->unk_00, 0);
    Bg_CopyToTilemapRect(param4->unk_00, 1, 0, sPlayerRowLayouts[param1 - 1].unk_00[v0], 32, 6, param3->rawData, 0, sPlayerRowLayouts[param1 - 1].unk_04[param5], param3->screenWidth / 8, param3->screenHeight / 8);

    {
        u8 v1;
        u8 v2, v3;

        v1 = sPlayerRowLayouts[param1 - 1].unk_08[v0];
        v2 = sPlayerRowSpriteOffsets[v1][0];
        v3 = (sPlayerRowLayouts[param1 - 1].unk_00[v0] * 8) + sPlayerRowSpriteOffsets[v1][1];

        param0->unk_10 = WiFiLobbyMinigame_AddSprite(param8, param7->unk_00, v2, v3, 0, heapID);

        Sprite_SetAnim(param0->unk_10, v1);
        Sprite_SetExplicitPaletteOffset(param0->unk_10, param5);
        Sprite_SetDrawFlag(param0->unk_10, FALSE);
        Sprite_SetAnimateFlag(param0->unk_10, 1);
    }

    {
        u8 v4, v5;

        v4 = 24;
        v5 = (sPlayerRowLayouts[param1 - 1].unk_00[v0] * 8) + 21;

        param0->unk_14 = WiFiLobbyMinigame_AddSprite(param8, param7->unk_00, v4, v5, 0, heapID);

        Sprite_SetAnim(param0->unk_14, 0);
        Sprite_SetDrawFlag(param0->unk_14, FALSE);
    }

    param0->unk_1A = param5;
    param0->unk_1B = v0;
    param0->unk_18 = param1;
}

static void WiFiLobbyMinigame_DrawPlayerRowName(WiFiLobbyMinigamePlayerRow *param0, WiFiLobbyMinigameMessages *param1, const TrainerInfo *param2, s16 param3, s16 param4, u32 param5)
{
    WiFiLobbyMinigame_SetMessagePlayerName(param1, param2);

    if (param5 == 1) {
        WiFiLobbyMinigame_DrawMessageWithColor(param1, 10, &param0->unk_00, param3, param4, TEXT_COLOR(5, 6, 0));
    } else {
        WiFiLobbyMinigame_DrawMessageLeft(param1, 10, &param0->unk_00, param3, param4);
    }
}

static void WiFiLobbyMinigame_DrawPlayerRowLocation(WiFiLobbyMinigamePlayerRow *param0, WiFiLobbyMinigameMessages *param1, BOOL param2, u32 param3, u32 param4, s16 param5)
{
    if (param2) {
        if (param3 != 0) {
            WiFiLobbyMinigame_ClearMessageArgs(param1);
            WiFiLobbyMinigame_SetMessageCountryName(param1, param3);
            WiFiLobbyMinigame_DrawMessageLeft(param1, 11, &param0->unk_00, param5, 16);
        }
    } else {
        if (param3 != 0) {
            WiFiLobbyMinigame_ClearMessageArgs(param1);
            WiFiLobbyMinigame_SetMessageCityName(param1, param3, param4);
            WiFiLobbyMinigame_DrawMessageLeft(param1, 12, &param0->unk_00, param5, 16);
        }
    }
}

static void WiFiLobbyMinigame_ShowPlayerRowRankIcon(WiFiLobbyMinigamePlayerRow *param0, u32 param1)
{
    Sprite_SetDrawFlag(param0->unk_14, TRUE);
    Sprite_SetAnim(param0->unk_14, 4 + param1);
    Sprite_SetAnimateFlag(param0->unk_14, 1);
}

static void WiFiLobbyMinigame_DrawPlayerRowScore(WiFiLobbyMinigamePlayerRow *param0, WiFiLobbyMinigameMessages *param1, u32 param2, s16 param3, s16 param4, u32 param5)
{
    WiFiLobbyMinigame_SetMessageNumber(param1, param2, param5);

    if (param5 == 5) {
        WiFiLobbyMinigame_DrawMessageRightAligned(param1, 14, &param0->unk_00, param3, param4);
    } else {
        WiFiLobbyMinigame_DrawMessageRightAligned(param1, 13, &param0->unk_00, param3, param4);
    }
}

static void WiFiLobbyMinigame_TransferPlayerRow(WiFiLobbyMinigamePlayerRow *param0, WiFiLobbyMinigameBackgrounds *param1)
{
    Window_ScheduleCopyToVRAM(&param0->unk_00);
    Bg_ScheduleTilemapTransfer(param1->unk_00, 1);
}

static void WiFiLobbyMinigame_ShowPlayerRowSprite(WiFiLobbyMinigamePlayerRow *param0)
{
    Sprite_SetDrawFlag(param0->unk_10, TRUE);
}

static void WiFiLobbyMinigame_FreePlayerRow(WiFiLobbyMinigamePlayerRow *param0)
{
    if (param0->unk_10) {
        Sprite_Delete(param0->unk_10);
        param0->unk_10 = NULL;
    }

    if (param0->unk_14) {
        Sprite_Delete(param0->unk_14);
        param0->unk_14 = NULL;
    }

    if (Window_IsInUse(&param0->unk_00) == 1) {
        Window_Remove(&param0->unk_00);
    }
}

static void WiFiLobbyMinigame_StartPlayerRowSlideIn(WiFiLobbyMinigamePlayerRow *param0, s16 param1, s16 param2)
{
    WiFiLobbyMinigame_InitMotion(&param0->unk_1C, FX32_CONST(-255), FX32_CONST(param1), FX32_CONST(28), 8);

    param0->unk_30 = 0;
    param0->unk_32 = param2;
    param0->unk_34 = 1382;

    WiFiLobbyMinigame_SetPlayerRowSpritePos(param0, -(param0->unk_1C.unk_00 >> FX32_SHIFT));
}

static void WiFiLobbyMinigame_StartPlayerRowSlideOut(WiFiLobbyMinigamePlayerRow *param0, s16 param1)
{
    WiFiLobbyMinigame_InitMotion(&param0->unk_1C, param0->unk_1C.unk_00, FX32_CONST(-255), 0, 8);

    param0->unk_30 = 0;
    param0->unk_32 = param1;
    param0->unk_34 = 1383;

    WiFiLobbyMinigame_SetPlayerRowSpritePos(param0, -(param0->unk_1C.unk_00 >> FX32_SHIFT));
}

static BOOL WiFiLobbyMinigame_UpdatePlayerRowMotion(WiFiLobbyMinigamePlayerRow *param0)
{
    BOOL v0;
    u8 v1, v2;

    if (param0->unk_32 <= 0) {
        if (param0->unk_30 == 0) {
            Sound_PlayEffect(param0->unk_34);
        }

        param0->unk_30++;
        v0 = WiFiLobbyMinigame_UpdateMotion(&param0->unk_1C, param0->unk_30);

        WiFiLobbyMinigame_SetPlayerRowSpritePos(param0, -(param0->unk_1C.unk_00 >> FX32_SHIFT));
        return v0;
    }

    param0->unk_32--;
    return 0;
}

static void WiFiLobbyMinigame_SetPlayerRowSpritePos(WiFiLobbyMinigamePlayerRow *param0, s32 param1)
{
    u8 v0;
    u8 v1, v2;
    VecFx32 v3;

    v0 = sPlayerRowLayouts[param0->unk_18 - 1].unk_08[param0->unk_1B];
    v1 = sPlayerRowSpriteOffsets[v0][0];
    v2 = (sPlayerRowLayouts[param0->unk_18 - 1].unk_00[param0->unk_1B] * 8) + sPlayerRowSpriteOffsets[v0][1];

    v3.x = (v1 + param1) << FX32_SHIFT;
    v3.y = v2 << FX32_SHIFT;

    Sprite_SetPosition(param0->unk_10, &v3);

    v1 = 24;
    v2 = (sPlayerRowLayouts[param0->unk_18 - 1].unk_00[param0->unk_1B] * 8) + 21;

    v3.x = (v1 + param1) << FX32_SHIFT;
    v3.y = v2 << FX32_SHIFT;

    Sprite_SetPosition(param0->unk_14, &v3);
}

static u32 WiFiLobbyMinigame_GetPlayerRowOrder(u32 param0, u32 param1, u32 param2)
{
    s32 v0, v1, v2;
    int v3;

    for (v3 = 0; v3 < param0; v3++) {
        if (sPlayerRowOrder[param0 - 1][v3] == param1) {
            v1 = v3;
        }

        if (sPlayerRowOrder[param0 - 1][v3] == param2) {
            v0 = v3;
        }
    }

    v2 = v1 - v0;

    if (v2 < 0) {
        v2 += param0;
    }

    return v2;
}

static void WiFiLobbyMinigame_InitScrollEffect(WiFiLobbyMinigameScrollEffect *param0, WiFiLobbyMinigameBackgrounds *param1, u32 heapID)
{
    int v0, v1;

    GF_ASSERT(param0->bufferManager == NULL);

    param0->unk_00 = param1;

    Bg_SetOffset(param0->unk_00->unk_00, 0, 0, -255);
    Bg_SetOffset(param0->unk_00->unk_00, 1, 0, -255);

    for (v0 = 0; v0 < 2; v0++) {
        MI_CpuFill16(&param0->unk_04[v0], -255, sizeof(s16) * 192);
    }

    param0->bufferManager = BufferManager_New(heapID, &param0->unk_04[0], &param0->unk_04[1]);

    BufferManager_SetMode(param0->bufferManager, 0);
    SetHBlankCallback(WiFiLobbyMinigame_ScrollEffectHBlank, param0);
}

static void WiFiLobbyMinigame_FreeScrollEffect(WiFiLobbyMinigameScrollEffect *param0)
{
    if (param0->bufferManager != NULL) {
        SetHBlankCallback(NULL, NULL);
        BufferManager_Delete(param0->bufferManager);
        param0->bufferManager = NULL;
    }
}

static void WiFiLobbyMinigame_UpdateScrollEffect(WiFiLobbyMinigameScrollEffect *param0, const WiFiLobbyMinigamePlayerRow *param1)
{
    s16 *v0;
    int v1;
    int v2;

    GF_ASSERT(param0->bufferManager != NULL);

    v0 = BufferManager_GetWriteBuffer(param0->bufferManager);

    for (v1 = 0; v1 < 6 * 8; v1++) {
        v2 = v1 - 1;
        v2 += sPlayerRowLayouts[param1->unk_18 - 1].unk_00[param1->unk_1B] * 8;

        if (v2 < 0) {
            v2 += 192;
        }

        v0[v2] = param1->unk_1C.unk_00 >> FX32_SHIFT;
    }

    BufferManager_SetMode(param0->bufferManager, 1);
}

static void WiFiLobbyMinigame_SwapScrollBuffers(WiFiLobbyMinigameScrollEffect *param0)
{
    if (param0->bufferManager == NULL) {
        return;
    }

    BufferManager_SwapBuffers(param0->bufferManager);
    BufferManager_SetMode(param0->bufferManager, 0);
}

static void WiFiLobbyMinigame_ScrollEffectHBlank(void *param0)
{
    WiFiLobbyMinigameScrollEffect *v0 = param0;
    int v1;
    const s16 *v2;

    v1 = GX_GetVCount();

    if (v1 >= 192) {
        return;
    }

    v2 = BufferManager_GetReadBuffer(v0->bufferManager);

    if (GX_IsHBlank()) {
        Bg_SetOffset(v0->unk_00->unk_00, 0, 0, v2[v1]);
        Bg_SetOffset(v0->unk_00->unk_00, 1, 0, v2[v1]);
    }
}

static void WiFiLobbyMinigame_InitPlayerInfo(WiFiLobbyMinigamePlayerInfo *param0, const WiFiLobbyMinigamePlayerContext *param1)
{
    int v0;

    for (v0 = 0; v0 < param1->unk_08; v0++) {
        param0->unk_08[v0] = WiFiLobbyMinigame_GetTrainerInfo(param1, param1->unk_04[v0]);
        GF_ASSERT(param0->unk_08[v0]);
        param0->unk_00[v0] = CommInfo_PlayerCountry(param1->unk_04[v0]);
        param0->unk_04[v0] = CommInfo_PlayerRegion(param1->unk_04[v0]);
    }
}

static BOOL WiFiLobbyMinigame_ArePlayersFromDifferentCountries(const WiFiLobbyMinigamePlayerContext *param0, const WiFiLobbyMinigamePlayerInfo *param1)
{
    int v0;
    BOOL v1 = 0;

    for (v0 = 0; v0 < param0->unk_08 - 1; v0++) {
        if ((param1->unk_00[v0] != param1->unk_00[v0 + 1]) || (param1->unk_00[v0] == 0) || (param1->unk_00[v0 + 1] == 0)) {
            v1 = 1;
        }
    }

    return v1;
}

u32 WiFiLobbyMinigame_GetNextMinigame(u32 param0)
{
    u32 v0;
    u32 v1;
    u32 v2;

    v1 = param0 % 3;
    v0 = param0 / 3;

    if ((v1 + 1) < 3) {
        v1++;
    }

    v2 = v0 * 3;
    v2 += v1;

    return v2;
}

static void WiFiLobbyMinigame_InitGameTitle(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1, WiFiLobbyMinigameMessages *param2, u32 param3, NARC *param4, u32 heapID)
{
    Window_Add(param1->unk_00, &param0->unk_00, 1, 6, 11, 20, 10, 8, 513);
    Window_FillTilemap(&param0->unk_00, 0);

    param0->unk_14 = String_Init(128, heapID);
    WiFiLobbyMinigame_SetMessageMinigameName(param2, param3);
    WiFiLobbyMinigame_DrawMessage(param2, param0->unk_14, 16);
    param0->unk_10 = param3;

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param4, 7, param1->unk_00, 0, 0, 0, 0, heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param4, 10, param1->unk_00, 0, 0, 0, 0, heapID);
}

static void WiFiLobbyMinigame_FreeGameTitle(WiFiLobbyMinigameGameTitle *param0)
{
    Window_Remove(&param0->unk_00);
    String_Free(param0->unk_14);
}

static void WiFiLobbyMinigame_ShowGameTitle(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1, u32 heapID)
{
    u32 v0;
    u32 v1;

    param0->unk_2C = 0;
    param0->unk_2E = 0;

    WiFiLobbyMinigame_InitMotion(&param0->unk_18, sGameTitleSlideInStart[param0->unk_10], sGameTitleSlideInEnd[param0->unk_10], sGameTitleSlideInAccel[param0->unk_10], 16);
    WiFiLobbyMinigame_SetGameTitleBgOffset(param0, param1, param0->unk_18.unk_00 >> FX32_SHIFT);
    Font_InitManager(FONT_SUBSCREEN, heapID);

    v0 = Font_CalcStringWidth(FONT_SUBSCREEN, param0->unk_14, 0);
    v1 = ((20 * 8) / 2) - (v0 / 2);

    Text_AddPrinterWithParamsAndColor(&param0->unk_00, FONT_SUBSCREEN, param0->unk_14, v1, 0, TEXT_SPEED_INSTANT, sGameTitleTextColors[param0->unk_10], NULL);
    Font_Free(FONT_SUBSCREEN);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
}

static void WiFiLobbyMinigame_HideGameTitle(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1)
{
    param0->unk_2C = 0;
    param0->unk_2E = 0;

    WiFiLobbyMinigame_InitMotion(&param0->unk_18, sGameTitleSlideInEnd[param0->unk_10], sGameTitleHideStart[param0->unk_10], sGameTitleHideEnd[param0->unk_10], 8);
    WiFiLobbyMinigame_ScheduleGameTitleBgScroll(param0, param1, param0->unk_18.unk_00 >> FX32_SHIFT);
}

static BOOL WiFiLobbyMinigame_UpdateGameTitleShow(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1)
{
    BOOL v0;

    switch (param0->unk_2E) {
    case 0:
        v0 = WiFiLobbyMinigame_UpdateMotion(&param0->unk_18, param0->unk_2C);
        WiFiLobbyMinigame_ScheduleGameTitleBgScroll(param0, param1, param0->unk_18.unk_00 >> FX32_SHIFT);
        param0->unk_2C++;

        if (v0 == 1) {
            Sound_PlayEffect(SEQ_SE_PL_FCALL_sseq);

            WiFiLobbyMinigame_InitMotion(&param0->unk_18, sGameTitleSlideInEnd[param0->unk_10], sGameTitleSlideOutStart[param0->unk_10], sGameTitleSlideOutEnd[param0->unk_10], 4);
            param0->unk_2E++;
            param0->unk_2C = 0;
        }
        break;
    case 1:
        v0 = WiFiLobbyMinigame_UpdateMotion(&param0->unk_18, param0->unk_2C);
        WiFiLobbyMinigame_ScheduleGameTitleBgScroll(param0, param1, param0->unk_18.unk_00 >> FX32_SHIFT);
        param0->unk_2C++;

        if (v0 == 1) {
            WiFiLobbyMinigame_InitMotion(&param0->unk_18, sGameTitleSlideOutStart[param0->unk_10], sGameTitleSlideInEnd[param0->unk_10], sGameTitleSlideOutAccel[param0->unk_10], 4);
            param0->unk_2E++;
            param0->unk_2C = 0;
        }
        break;
    case 2:
        v0 = WiFiLobbyMinigame_UpdateMotion(&param0->unk_18, param0->unk_2C);
        WiFiLobbyMinigame_ScheduleGameTitleBgScroll(param0, param1, param0->unk_18.unk_00 >> FX32_SHIFT);
        param0->unk_2C++;

        if (v0 == 1) {
            param0->unk_2E++;
        }
        break;
    case 3:
        return 1;
    }

    return 0;
}

static BOOL WiFiLobbyMinigame_UpdateGameTitleHide(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1)
{
    BOOL v0;

    switch (param0->unk_2E) {
    case 0:
        v0 = WiFiLobbyMinigame_UpdateMotion(&param0->unk_18, param0->unk_2C);
        WiFiLobbyMinigame_ScheduleGameTitleBgScroll(param0, param1, param0->unk_18.unk_00 >> FX32_SHIFT);
        param0->unk_2C++;

        if (v0 == 1) {
            param0->unk_2E++;
        }
        break;
    case 1:
        Window_ClearAndCopyToVRAM(&param0->unk_00);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);

        WiFiLobbyMinigame_SetGameTitleBgOffset(param0, param1, 0);

        Bg_ClearTilemap(param1->unk_00, BG_LAYER_MAIN_0);
        Bg_ClearTilemap(param1->unk_00, BG_LAYER_MAIN_1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
        return 1;
    }

    return 0;
}

static void WiFiLobbyMinigame_SetGameTitleBgOffset(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1, s32 param2)
{
    switch (param0->unk_10) {
    case WiFiPlazaLobbyActivity_00:
    case WiFiPlazaLobbyActivity_01:
        Bg_SetOffset(param1->unk_00, BG_LAYER_MAIN_0, 0, param2);
        Bg_SetOffset(param1->unk_00, BG_LAYER_MAIN_1, 0, param2);
        break;
    case WiFiPlazaLobbyActivity_02:
        Bg_SetOffset(param1->unk_00, BG_LAYER_MAIN_0, 3, param2);
        Bg_SetOffset(param1->unk_00, BG_LAYER_MAIN_1, 3, param2);
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

static void WiFiLobbyMinigame_ScheduleGameTitleBgScroll(WiFiLobbyMinigameGameTitle *param0, WiFiLobbyMinigameBackgrounds *param1, s32 param2)
{
    switch (param0->unk_10) {
    case WiFiPlazaLobbyActivity_00:
    case WiFiPlazaLobbyActivity_01:
        Bg_ScheduleScroll(param1->unk_00, 0, 0, param2);
        Bg_ScheduleScroll(param1->unk_00, 1, 0, param2);
        break;
    case WiFiPlazaLobbyActivity_02:
        Bg_ScheduleScroll(param1->unk_00, 0, 3, param2);
        Bg_ScheduleScroll(param1->unk_00, 1, 3, param2);
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

static void WiFiLobbyMinigame_LoadMinigamePalette(NARC *param0, u32 param1, u32 param2)
{
    u32 v0;

    switch (param1) {
    case WiFiPlazaLobbyActivity_00:
        v0 = 1;
        break;
    case WiFiPlazaLobbyActivity_01:
        v0 = 2;
        break;
    case WiFiPlazaLobbyActivity_02:
        v0 = 0;
        break;
    default:
        v0 = 1;
        break;
    }

    Graphics_LoadPaletteWithSrcOffsetFromOpenNARC(param0, 5, 0, v0 * 32, 5 * 32, 32, param2);
    Graphics_LoadPaletteWithSrcOffsetFromOpenNARC(param0, 5, 4, v0 * 32, 5 * 32, 32, param2);
}

static WiFiLobbyMinigameResultsScreen *WiFiLobbyMinigame_CreateResultsScreenInternal(const WiFiLobbyMinigamePlayerContext *param0, const WiFiLobbyMinigameRanking *param1, u32 param2, u32 heapID)
{
    WiFiLobbyMinigameResultsScreen *v0;
    int v1;

    v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMinigameResultsScreen));
    memset(v0, 0, sizeof(WiFiLobbyMinigameResultsScreen));
    memcpy(&v0->unk_1C, param1, sizeof(WiFiLobbyMinigameRanking));
    memcpy(&v0->unk_0C, param0, sizeof(WiFiLobbyMinigamePlayerContext));

    v0->unk_07 = param2;

    WiFiLobbyMinigame_InitCommCmdResults(v0);

    G2_BlendNone();
    G2S_BlendNone();
    GX_SetVisibleWnd(0);
    GXS_SetVisibleWnd(0);

    GXLayers_SetBanks(&sResultsScreenGXBanks);

    v0->heapID = heapID;

    WiFiLobbyMinigame_InitPlayerInfo(&v0->unk_34, &v0->unk_0C);
    VramTransfer_New(16, heapID);

    WiFiLobbyMinigame_InitBackgrounds(&v0->unk_4C, &sResultsScreenGraphicsModes, sResultsScreenBgTemplates, 6, heapID);
    WiFiLobbyMinigame_InitSpriteSystem(&v0->unk_A0, 32, 2, 2, heapID);
    WiFiLobbyMinigame_InitSpriteResources(&v0->unk_230, 2, heapID);
    WiFiLobbyMinigame_InitMessages(&v0->unk_58, heapID);
    WiFiLobbyMinigame_LoadResultsScreenGraphics(v0, heapID);

    {
        BOOL v2;
        u32 v3;

        v3 = WiFiLobbyMinigame_GetNetIdByIndex(&v0->unk_0C, v0->unk_0C.unk_09);
        v2 = WiFiLobbyMinigame_IsPlayerReady(&v0->unk_0C, v3);
        WiFiLobbyMinigame_InitMessageBox(&v0->unk_68, &v0->unk_4C, v0->unk_0C.saveData, v2, heapID);
    }

    WiFiLobbyMinigame_InitReplayMenu(&v0->unk_24C, &v0->unk_4C, v0->unk_0C.unk_0A, heapID);

    {
        int v4;

        v0->unk_05 = WiFiLobbyMinigame_ArePlayersFromDifferentCountries(&v0->unk_0C, &v0->unk_34);
    }

    switch (v0->unk_07) {
    case WiFiPlazaLobbyActivity_00:
    case WiFiPlazaLobbyActivity_01:
        v0->unk_6A8 = SysTask_Start(WiFiLobbyMinigame_ResultsScreenTask, v0, 0);
        break;
    case WiFiPlazaLobbyActivity_02:
        v0->unk_6A8 = SysTask_Start(WiFiLobbyMinigame_ResultsScreenTaskGame2, v0, 0);
        break;
    default:
        GF_ASSERT(FALSE);
        v0->unk_6A8 = SysTask_Start(WiFiLobbyMinigame_ResultsScreenTask, v0, 0);
        break;
    }

    v0->unk_6AC = SysTask_ExecuteAfterVBlank(WiFiLobbyMinigame_ResultsScreenVBlankTask, v0, 0);

    if (v0->unk_0C.unk_0A) {
        NintendoWFC_StartVoiceChat(heapID);
    }

    return v0;
}

static void WiFiLobbyMinigame_LoadResultsScreenGraphics(WiFiLobbyMinigameResultsScreen *param0, u32 heapID)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_RESOURCE__ENG__WIFI_LOBBY_MINIGAME__WLMNGM_TOOL, heapID);

    Graphics_LoadPaletteFromOpenNARC(v0, 4, 0, 0, 9 * 32, heapID);
    Graphics_LoadPaletteFromOpenNARC(v0, 4, 4, 0, 9 * 32, heapID);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 6, param0->unk_4C.unk_00, 1, 0, 0, 0, heapID);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 6, param0->unk_4C.unk_00, 5, 0, 0x4000, 0, heapID);

    {
        int v1;

        for (v1 = 0; v1 < 1; v1++) {
            param0->unk_2B8[v1] = Graphics_GetScrnDataFromOpenNARC(v0, 9 + v1, 0, &param0->unk_2BC[v1], heapID);
        }
    }

    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 8, param0->unk_4C.unk_00, 3, 0, 0, 0, heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 8, param0->unk_4C.unk_00, 5, 0, 0, 0, heapID);

    WiFiLobbyMinigame_LoadMinigamePalette(v0, param0->unk_07, heapID);

    param0->unk_248 = WiFiLobbyMinigame_AllocSpriteResource(&param0->unk_230, v0, 11, 5, 12, 13, 14, 5000, heapID);

    WiFiLobbyMinigame_LoadResultsPalette(param0, v0, heapID);
    WiFiLobbyMinigame_InitBalloonGrid(&param0->unk_26C, &param0->unk_4C, &param0->unk_A0, &param0->unk_230, v0, heapID);

    NARC_dtor(v0);
}

static void WiFiLobbyMinigame_FreeResultsScreenGraphics(WiFiLobbyMinigameResultsScreen *param0)
{
    WiFiLobbyMinigame_FreeBalloonGrid(&param0->unk_26C);

    {
        int v0;

        for (v0 = 0; v0 < 1; v0++) {
            Heap_Free(param0->unk_2B8[v0]);
        }
    }

    WiFiLobbyMinigame_FreeResultsPalette(param0);
}

static void WiFiLobbyMinigame_ResultsScreenTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameResultsScreen *v0 = param1;
    BOOL v1;

    switch (v0->unk_04) {
    case 0:

        v0->unk_6B0 = v0->unk_0C.unk_0C->appearanceRank;

        if (v0->unk_0C.unk_0B == 1) {
            v0->unk_09 = 0;
        } else {
            u32 v2;

            v2 = WiFiLobbyMinigame_GetTargetScore(v0);

            if ((v0->unk_1C.unk_10[v0->unk_0C.unk_09] == 0) && (v0->unk_1C.unk_00[v0->unk_0C.unk_09] > v2)) {
                v0->unk_0C.unk_0C->appearanceRank = WiFiLobbyMinigame_GetNextMinigame(v0->unk_0C.unk_0C->appearanceRank);
                v0->unk_09 = 1;
            } else {
                v0->unk_09 = 0;
            }

            if (v0->unk_0C.unk_09 == 0) {
                WiFiLobbyMinigame_SendGameResults(v0);
            }
        }

        StartScreenFade(FADE_MAIN_ONLY, 1, 1, 0xffff, 6, 1, v0->heapID);
        v0->unk_04++;
        break;
    case 1:
        v1 = IsScreenFadeDone();

        if (v1) {
            v0->unk_04++;
        }
        break;
    case 2:
        WiFiLobbyMinigame_ShowMessage(&v0->unk_68, &v0->unk_58, 1, 0);
        v0->unk_04++;
        break;
    case 3:
        v1 = WiFiLobbyMinigame_IsMessageDone(&v0->unk_68, 0);

        if (v1) {
            v0->unk_00 = 64;
            v0->unk_04++;
        }
        break;
    case 4:
        if (v0->unk_00 > 0) {
            v0->unk_00--;

            if (v0->unk_00 == 0) {
                int v3;
                BOOL v4 = 1;
                u32 v5;

                WiFiLobbyMinigame_HideMessage(&v0->unk_68, 0);
                WiFiLobbyMinigame_InitScrollEffect(&v0->unk_3A0, &v0->unk_4C, v0->heapID);

                v5 = WiFiLobbyMinigame_GetTargetScore(v0);

                for (v3 = 0; v3 < v0->unk_0C.unk_08; v3++) {
                    if (v0->unk_1C.unk_00[v3] > v5) {
                        v4 = 0;
                    }
                }

                if (v4 == 1) {
                    v0->unk_6B6 = 16;
                    v0->unk_04 = 22;
                } else {
                    v0->unk_04++;
                    v0->unk_6B4 = 4;
                }
            }
        }
        break;
    case 5: {
        int v6;
        BOOL v7;

        v7 = 0;

        do {
            v0->unk_6B4--;

            for (v6 = 0; v6 < v0->unk_0C.unk_08; v6++) {
                if (v0->unk_1C.unk_10[v6] == v0->unk_6B4) {
                    v7 = 1;
                }
            }
        } while (v7 == 0);

        switch (v0->unk_6B4) {
        case 3:
        case 2:
            v0->unk_6B6 = 16;
            break;
        case 1:
        case 0:
            v0->unk_6B6 = 32;
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }

        WiFiLobbyMinigame_UpdatePlayerRowsMotion(v0);
        v0->unk_04++;
    } break;
    case 6:
        v0->unk_6B6--;
        WiFiLobbyMinigame_UpdatePlayerRowsMotion(v0);

        if (v0->unk_6B6 > 0) {
            break;
        }

        {
            int v8;
            BOOL v9;

            for (v8 = 0; v8 < v0->unk_0C.unk_08; v8++) {
                v9 = 0;

                if (v0->unk_1C.unk_10[v8] == v0->unk_6B4) {
                    v9 = 1;
                } else {
                    if ((v0->unk_6B4 == 1) && (v0->unk_1C.unk_10[v8] == 0)) {
                        v9 = 1;
                    }
                }

                if (v9) {
                    WiFiLobbyMinigame_InitPlayerRowWithScore(v0, v8, v0->unk_1C.unk_10[v8]);
                }
            }
        }

        if (v0->unk_6B4 > 1) {
            v0->unk_04 = 5;
        } else {
            v0->unk_04++;
        }
        break;
    case 7:
        if (WiFiLobbyMinigame_UpdatePlayerRowsMotion(v0)) {
            v0->unk_04++;
        }
        break;
    case 8:
        v0->unk_04++;
        WiFiLobbyMinigame_CheckLocalPlayerWon(v0);
        v0->unk_00 = 30;
        break;
    case 9:
        if (v0->unk_00 > 0) {
            v0->unk_00--;
        }

        if (v0->unk_00 == 0) {
            v0->unk_04 = 10;
            v0->unk_00 = 0;
        }
        break;
    case 10: {
        u32 v10;

        if (v0->unk_1C.unk_10[v0->unk_0C.unk_09] == 0) {
            v10 = 17;
        } else {
            v10 = 18;
        }

        WiFiLobbyMinigame_SetMessagePlayerName(&v0->unk_58, v0->unk_34.unk_08[v0->unk_0C.unk_09]);
        WiFiLobbyMinigame_ShowMessage(&v0->unk_68, &v0->unk_58, v10, 0);
    }
        v0->unk_04++;
        break;
    case 11:
        v1 = WiFiLobbyMinigame_IsMessageDone(&v0->unk_68, 0);

        if (v1) {
            if (WiFiLobbyMinigame_IsWinFanfareDone(v0) == 1) {
                if (v0->unk_0C.unk_0B == 1) {
                    v0->unk_00 = 102;
                    v0->unk_04 = 14;
                } else {
                    v0->unk_00 = 102;
                    v0->unk_04++;
                }
            }
        }
        break;
    case 12:
        if (v0->unk_00 > 0) {
            v0->unk_00--;
            break;
        }

        {
            u32 v11;

            if (v0->unk_09) {
                WiFiLobbyMinigame_SetMessagePlazaItemName(&v0->unk_58, v0->unk_0C.unk_0C->appearanceRank);

                if (v0->unk_6B0 == v0->unk_0C.unk_0C->appearanceRank) {
                    v11 = 19;
                } else {
                    v11 = 2;
                }
            } else {
                v11 = 9;
            }

            WiFiLobbyMinigame_SetMessagePlayerName(&v0->unk_58, v0->unk_34.unk_08[v0->unk_0C.unk_09]);
            WiFiLobbyMinigame_ShowMessage(&v0->unk_68, &v0->unk_58, v11, 0);
        }
        v0->unk_04 = 13;
        break;
    case 13:
        v1 = WiFiLobbyMinigame_IsMessageDone(&v0->unk_68, 0);

        if (v1) {
            v0->unk_00 = 102;
            v0->unk_04++;
        }
        break;
    case 14:
        if (v0->unk_00 > 0) {
            v0->unk_00--;

            if (v0->unk_00 == 0) {
                WiFiLobbyMinigame_HideMessage(&v0->unk_68, 0);
                v0->unk_00 = 30;
                v0->unk_04++;
            }
        }
        break;
    case 15:
        if (v0->unk_00 > 0) {
            v0->unk_00--;
        } else {
            CommTiming_StartSync(130);

            if (v0->unk_0C.unk_0A) {
                NintendoWFC_TerminateVoiceChat();
            }

            v0->unk_04++;
        }
        break;
    case 16:
        if (CommTiming_IsSyncState(130)) {
            if (v0->unk_0C.unk_0B) {
                v0->unk_04 = 19;
            } else {
                v0->unk_04++;
            }
        }
        break;
    case 17:
        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, v0->heapID);
        v0->unk_04++;
        break;
    case 18:
        v1 = IsScreenFadeDone();

        if (v1) {
            v0->unk_04 = 21;
        }
        break;
    case 19:
        WiFiLobbyMinigame_RecordFriendGameCount(v0);
        v0->unk_04++;
        break;
    case 20:
        v1 = WiFiLobbyMinigame_UpdateReplayMenu(&v0->unk_24C, &v0->unk_68, &v0->unk_58, v0->unk_07, v0->heapID);

        if (v1) {
            v0->unk_08 = WiFiLobbyMinigame_ReplayMenuGetResult(&v0->unk_24C);
            v0->unk_04++;
        }
        break;
    case 21:
        WiFiLobbyMinigame_FreeScrollEffect(&v0->unk_3A0);
        v0->unk_06 = 1;
        break;
    case 22:
        v0->unk_6B6--;

        if (v0->unk_6B6 <= 0) {
            v0->unk_04++;
        }
        break;
    case 23: {
        int v12;

        for (v12 = 0; v12 < v0->unk_0C.unk_08; v12++) {
            v0->unk_1C.unk_10[v12] = v0->unk_0C.unk_08 - 1;
            WiFiLobbyMinigame_InitPlayerRowWithScore(v0, v12, v0->unk_1C.unk_10[v12]);
        }

        v0->unk_04 = 7;
    } break;
    }

    WiFiLobbyMinigame_UpdateRankPalette(v0);
    WiFiLobbyMinigame_UpdateSprites(&v0->unk_A0);

    Bg_ScheduleScroll(v0->unk_4C.unk_00, 3, 4, 2);
    Bg_ScheduleScroll(v0->unk_4C.unk_00, 5, 4, 2);
}

static void WiFiLobbyMinigame_ResultsScreenTaskGame2(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameResultsScreen *v0 = param1;
    BOOL v1;

    switch (v0->unk_04) {
    case 0:
        if (v0->unk_0C.unk_0B == 1) {
            v0->unk_09 = 0;
        } else {
            if (v0->unk_1C.unk_14 >= 10) {
                v0->unk_0C.unk_0C->appearanceRank = WiFiLobbyMinigame_GetNextMinigame(v0->unk_0C.unk_0C->appearanceRank);
                v0->unk_09 = 1;
            } else {
                v0->unk_09 = 0;
            }

            if (v0->unk_0C.unk_09 == 0) {
                WiFiLobbyMinigame_SendGameResultsGame2(v0);
            }
        }

        StartScreenFade(FADE_MAIN_ONLY, 1, 1, 0xffff, 6, 1, v0->heapID);
        v0->unk_04++;
        break;
    case 1:
        v1 = IsScreenFadeDone();

        if (v1) {
            v0->unk_04++;

            v0->unk_6B4 = 4;
        }
        break;
    case 2:
        WiFiLobbyMinigame_ShowMessage(&v0->unk_68, &v0->unk_58, 1, 0);
        v0->unk_04++;
        break;
    case 3:
        v1 = WiFiLobbyMinigame_IsMessageDone(&v0->unk_68, 0);

        if (v1) {
            v0->unk_00 = 102;
            v0->unk_04++;
        }
        break;
    case 4:
        if (v0->unk_00 > 0) {
            v0->unk_00--;

            if (v0->unk_00 == 0) {
                WiFiLobbyMinigame_HideMessage(&v0->unk_68, 0);
                v0->unk_04++;
            }
        }
        break;
    case 5: {
        int v2;
        BOOL v3;
        u32 v4;

        WiFiLobbyMinigame_InitScrollEffect(&v0->unk_3A0, &v0->unk_4C, v0->heapID);

        for (v2 = 0; v2 < v0->unk_0C.unk_08; v2++) {
            WiFiLobbyMinigame_InitPlayerRow(&v0->unk_2C0[v2], v0->unk_0C.unk_08, v0->unk_07, v0->unk_2BC[0], &v0->unk_4C, v2, v0->unk_0C.unk_09, &v0->unk_A0, v0->unk_248, v0->heapID);

            v4 = WiFiLobbyMinigame_GetNetIdByIndex(&v0->unk_0C, v2);
            v3 = WiFiLobbyMinigame_IsPlayerReady(&v0->unk_0C, v4);

            WiFiLobbyMinigame_DrawPlayerRowName(&v0->unk_2C0[v2], &v0->unk_58, v0->unk_34.unk_08[v2], 8, 0, v3);
            WiFiLobbyMinigame_DrawPlayerRowLocation(&v0->unk_2C0[v2], &v0->unk_58, v0->unk_05, v0->unk_34.unk_00[v2], v0->unk_34.unk_04[v2], 8);
            WiFiLobbyMinigame_TransferPlayerRow(&v0->unk_2C0[v2], &v0->unk_4C);
            WiFiLobbyMinigame_ShowPlayerRowSprite(&v0->unk_2C0[v2]);
            WiFiLobbyMinigame_StartPlayerRowSlideIn(&v0->unk_2C0[v2], -8, 3 * v2);
        }
    }
        v0->unk_04++;
        v0->unk_00 = 16;
        break;
    case 6:
        v1 = WiFiLobbyMinigame_UpdatePlayerRowsMotion(v0);

        if (v1 == 1) {
            v0->unk_00--;

            if (v0->unk_00 <= 0) {
                WiFiLobbyMinigame_StartBalloonGrid(&v0->unk_26C, v0->unk_1C.unk_14);
                v0->unk_04++;
            }
        }
        break;
    case 7:
        v1 = WiFiLobbyMinigame_UpdateBalloonGrid(&v0->unk_26C, &v0->unk_4C);

        if (v1 == 1) {
            if (v0->unk_09 == 1) {
                WiFiLobbyMinigame_PlayWinFanfare(v0);
            }

            v0->unk_04++;
        }
        break;
    case 8:
        WiFiLobbyMinigame_SetMessageRankNumber(&v0->unk_58, v0->unk_1C.unk_14);
        WiFiLobbyMinigame_ShowMessage(&v0->unk_68, &v0->unk_58, 7, 0);
        v0->unk_00 = 102;
        v0->unk_04++;
        break;
    case 9:
        v1 = WiFiLobbyMinigame_IsMessageDone(&v0->unk_68, 0);

        if (v1 == 1) {
            if (v0->unk_00 <= 0) {
                if (WiFiLobbyMinigame_IsWinFanfareDone(v0) == 1) {
                    if (v0->unk_0C.unk_0B == 1) {
                        v0->unk_00 = 102;
                        v0->unk_04 = 12;
                    } else {
                        v0->unk_04++;
                    }
                }
            } else {
                v0->unk_00--;
            }
        }
        break;
    case 10: {
        u32 v5;

        if (v0->unk_09) {
            v5 = 8;
        } else {
            v5 = 9;
        }

        WiFiLobbyMinigame_ShowMessage(&v0->unk_68, &v0->unk_58, v5, 0);
    }
        v0->unk_04++;
        break;
    case 11:
        v1 = WiFiLobbyMinigame_IsMessageDone(&v0->unk_68, 0);

        if (v1) {
            v0->unk_00 = 102;

            if (v0->unk_09) {
                v0->unk_04 = 13;
            } else {
                v0->unk_04++;
            }
        }
        break;
    case 12:
        if (v0->unk_00 > 0) {
            v0->unk_00--;

            if (v0->unk_00 == 0) {
                v0->unk_04 = 14;
            }
        }
        break;
    case 13:
        if (v0->unk_00 > 0) {
            v0->unk_00--;
        }

        if (v0->unk_00 == 0) {
            v0->unk_04 = 14;
        }
        break;
    case 14:
        if (v0->unk_0C.unk_0A) {
            NintendoWFC_TerminateVoiceChat();
        }

        CommTiming_StartSync(130);
        v0->unk_04++;
        break;
    case 15:
        if (CommTiming_IsSyncState(130)) {
            if (v0->unk_0C.unk_0B) {
                v0->unk_04 = 18;
            } else {
                v0->unk_04++;
            }
        }
        break;
    case 16:
        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, v0->heapID);
        v0->unk_04++;
        break;
    case 17:
        v1 = IsScreenFadeDone();

        if (v1) {
            v0->unk_04 = 20;
        }
        break;
    case 18:
        WiFiLobbyMinigame_RecordFriendGameCount(v0);
        v0->unk_04++;
        break;
    case 19:
        v1 = WiFiLobbyMinigame_UpdateReplayMenu(&v0->unk_24C, &v0->unk_68, &v0->unk_58, v0->unk_07, v0->heapID);

        if (v1) {
            v0->unk_08 = WiFiLobbyMinigame_ReplayMenuGetResult(&v0->unk_24C);
            v0->unk_04++;
        }
        break;
    case 20:
        WiFiLobbyMinigame_FreeScrollEffect(&v0->unk_3A0);
        v0->unk_06 = 1;
        break;
    }

    WiFiLobbyMinigame_UpdateRankPalette(v0);
    WiFiLobbyMinigame_UpdateSprites(&v0->unk_A0);

    Bg_ScheduleScroll(v0->unk_4C.unk_00, 3, 4, 2);
    Bg_ScheduleScroll(v0->unk_4C.unk_00, 5, 4, 2);
}

static void WiFiLobbyMinigame_ResultsScreenVBlankTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameResultsScreen *v0 = param1;

    VramTransfer_Process();

    WiFiLobbyMinigame_RunBackgroundUpdates(&v0->unk_4C);
    WiFiLobbyMinigame_TransferOam(&v0->unk_A0);
    WiFiLobbyMinigame_SwapScrollBuffers(&v0->unk_3A0);
}

static void WiFiLobbyMinigame_LoadResultsPalette(WiFiLobbyMinigameResultsScreen *param0, NARC *param1, u32 param2)
{
    param0->unk_6B8 = Graphics_GetPlttDataFromOpenNARC(param1, 5, &param0->unk_6BC, param2);
}

static void WiFiLobbyMinigame_CheckLocalPlayerWon(WiFiLobbyMinigameResultsScreen *param0)
{
    int v0;

    param0->unk_6C2 = 1;

    for (v0 = 0; v0 < param0->unk_0C.unk_08; v0++) {
        if (param0->unk_1C.unk_10[v0] == 0) {
            if (param0->unk_0C.unk_09 == v0) {
                WiFiLobbyMinigame_PlayWinFanfare(param0);
                break;
            }
        }
    }
}

static void WiFiLobbyMinigame_UpdateRankPalette(WiFiLobbyMinigameResultsScreen *param0)
{
    int v0;
    u32 v1;
    u8 *v2;
    BOOL v3;

    if (param0->unk_6C2 == 0) {
        return;
    }

    if ((param0->unk_6C0 == 0) || (param0->unk_6C0 == 8)) {
        for (v0 = 0; v0 < param0->unk_0C.unk_08; v0++) {
            if (param0->unk_1C.unk_10[v0] == 0) {
                v1 = (sPlayerRowPaletteOrder[v0] * 32);
                v2 = param0->unk_6BC->pRawData;

                if (param0->unk_6C0 == 0) {
                    v2 += ((3 + sPlayerRowPaletteOrder[v0]) * 32);
                } else {
                    v2 += ((7 + sPlayerRowPaletteOrder[v0]) * 32);
                }

                v3 = VramTransfer_Request(NNS_GFD_DST_2D_BG_PLTT_MAIN, v1, v2, 32);
                GF_ASSERT(v3);
            }
        }
    }

    param0->unk_6C0 = (param0->unk_6C0 + 1) % (8 * 2);
}

static void WiFiLobbyMinigame_FreeResultsPalette(WiFiLobbyMinigameResultsScreen *param0)
{
    Heap_Free(param0->unk_6B8);
}

static void WiFiLobbyMinigame_InitReplayMenu(WiFiLobbyMinigameReplayMenu *param0, WiFiLobbyMinigameBackgrounds *param1, u32 param2, u32 heapID)
{
    memset(param0, 0, sizeof(WiFiLobbyMinigameReplayMenu));

    param0->unk_08.bgConfig = param1->unk_00;
    param0->unk_08.bgLayer = BG_LAYER_SUB_0;
    param0->unk_08.baseTile = ((1 + (18 + 12)) + (27 * 4));
    param0->unk_08.palette = 2;
    param0->unk_08.tilemapLeft = 24;
    param0->unk_08.tilemapTop = 8;
    param0->unk_04 = YesNoTouchMenu_New(heapID);
    param0->unk_01 = param2;
    param0->unk_1D = 1;
}

static void WiFiLobbyMinigame_FreeReplayMenu(WiFiLobbyMinigameReplayMenu *param0)
{
    YesNoTouchMenu_Free(param0->unk_04);
}

static BOOL WiFiLobbyMinigame_UpdateReplayMenu(WiFiLobbyMinigameReplayMenu *param0, WiFiLobbyMinigameMessageBox *param1, WiFiLobbyMinigameMessages *param2, u32 param3, u32 heapID)
{
    u32 v0;

    switch (param0->unk_00) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, heapID);
        NetworkIcon_CreateOnSubScreen(0, heapID);

        if (param0->unk_01) {
            NintendoWFC_StartVoiceChat(heapID);
        }

        param0->unk_00++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            param0->unk_00++;
        }
        break;
    case 2:
        WiFiLobbyMinigame_SetMessageMinigameName(param2, param3);
        WiFiLobbyMinigame_ShowMessage(param1, param2, 3, 1);
        param0->unk_00++;
        break;
    case 3:
        v0 = WiFiLobbyMinigame_IsMessageDone(param1, 1);

        if (v0 == 1) {
            param0->unk_00++;
        }
        break;
    case 4:
        YesNoTouchMenu_InitWithParams(param0->unk_04, &param0->unk_08);
        param0->unk_00++;
        break;
    case 5:
        v0 = YesNoTouchMenu_ProcessInput(param0->unk_04);

        if (v0 == YES_NO_TOUCH_MENU_YES || v0 == YES_NO_TOUCH_MENU_NO) {
            if (v0 == YES_NO_TOUCH_MENU_YES) {
                CommSys_SendData(22, NULL, 0);
            } else if (v0 == YES_NO_TOUCH_MENU_NO) {
                CommSys_SendData(23, NULL, 0);
            }

            WiFiLobbyMinigame_ShowMessage(param1, param2, 15, 1);
            WiFiLobbyMinigame_ShowWaitDial(param1, 1);

            param0->unk_00++;
        }

        break;
    case 6:
        if (param0->unk_1E) {
            if (param0->unk_1F) {
                param0->unk_00 = 10;
            } else {
                param0->unk_00++;
            }
        }
        break;
    case 7:
        WiFiLobbyMinigame_ShowMessage(param1, param2, 6, 1);
        param0->unk_00++;
        break;
    case 8:
        v0 = WiFiLobbyMinigame_IsMessageDone(param1, 1);

        if (v0 == 1) {
            param0->unk_00++;
            param0->unk_02 = 102;
        }
        break;
    case 9:
        param0->unk_02--;

        if (param0->unk_02 == 0) {
            param0->unk_00++;
        }
        break;
    case 10:
        StartScreenFade(FADE_SUB_ONLY, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, heapID);
        param0->unk_00++;
        break;
    case 11:
        if (IsScreenFadeDone()) {
            NetworkIcon_Destroy();

            if (param0->unk_01) {
                NintendoWFC_TerminateVoiceChat();
            }

            param0->unk_00++;
        }
        break;
    case 12:
        return 1;
    }

    return 0;
}

static BOOL WiFiLobbyMinigame_ReplayMenuGetResult(const WiFiLobbyMinigameReplayMenu *param0)
{
    return param0->unk_1F;
}

static void WiFiLobbyMinigame_ReplayMenuSetPlayerReady(WiFiLobbyMinigameReplayMenu *param0, u32 param1, BOOL param2, u32 param3)
{
    if ((param0->unk_1C & (1 << param1)) == 0) {
        if (param2 == 0) {
            param0->unk_1D = 0;
        }

        param0->unk_1C |= (1 << param1);
    }

    {
        int v0;
        int v1;

        v1 = 0;

        for (v0 = 0; v0 < 4; v0++) {
            if (param0->unk_1C & (1 << v0)) {
                v1++;
            }
        }

        if (v1 == param3) {
            if (param0->unk_1D) {
                CommSys_SendData(24, NULL, 0);
            } else {
                CommSys_SendData(25, NULL, 0);
            }
        }
    }
}

static void WiFiLobbyMinigame_ReplayMenuSetAllReady(WiFiLobbyMinigameReplayMenu *param0, BOOL param1)
{
    param0->unk_1E = 1;
    param0->unk_1F = param1;
}

static void WiFiLobbyMinigame_InitBalloonGrid(WiFiLobbyMinigameBalloonGrid *param0, WiFiLobbyMinigameBackgrounds *param1, WiFiLobbyMinigameSpriteSystem *param2, WiFiLobbyMinigameSpriteResources *param3, NARC *param4, u32 param5)
{
    memset(param0, 0, sizeof(WiFiLobbyMinigameBalloonGrid));

    {
        Graphics_LoadPaletteFromOpenNARC(param4, 24, 0, (13 + 1) * 32, 32, param5);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param4, 25, param1->unk_00, 2, (1 + (18 + 12)) + (27 * 4), 0, 0, param5);
        param0->unk_00 = Graphics_GetScrnDataFromOpenNARC(param4, 26, 0, &param0->unk_04, param5);
    }

    {
        int v0, v1;
        int v2;
        int v3, v4;

        param0->unk_44 = WiFiLobbyMinigame_AllocSpriteResource(param3, param4, 15, 1, 16, 17, 18, 5000 + 1, param5);

        v4 = 40;

        for (v0 = 0; v0 < 3; v0++) {
            v3 = 74;

            for (v1 = 0; v1 < 5; v1++) {
                v2 = (v0 * 5) + v1;
                param0->unk_08[v2] = WiFiLobbyMinigame_AddSprite(param0->unk_44, param2->unk_00, v3, v4, 0, param5);
                Sprite_SetDrawFlag(param0->unk_08[v2], FALSE);
                Sprite_SetAnim(param0->unk_08[v2], v0);
                Sprite_SetExplicitPriority(param0->unk_08[v2], 0);

                v3 += 24;
            }

            v4 += 36;
        }
    }
}

static void WiFiLobbyMinigame_FreeBalloonGrid(WiFiLobbyMinigameBalloonGrid *param0)
{
    {
        int v0;

        for (v0 = 0; v0 < (5 * 3); v0++) {
            Sprite_Delete(param0->unk_08[v0]);
        }
    }

    {
        Heap_Free(param0->unk_00);
    }
}

static void WiFiLobbyMinigame_StartBalloonGrid(WiFiLobbyMinigameBalloonGrid *param0, u32 param1)
{
    param0->unk_4B = param1;
    param0->unk_48 = 0;
    param0->unk_4A = 0;
}

static BOOL WiFiLobbyMinigame_UpdateBalloonGrid(WiFiLobbyMinigameBalloonGrid *param0, WiFiLobbyMinigameBackgrounds *param1)
{
    switch (param0->unk_48) {
    case 0:

        WiFiLobbyMinigame_OffsetScreenData(param0->unk_04, (1 + (18 + 12)) + (27 * 4));
        Bg_LoadToTilemapRect(param1->unk_00, 2, param0->unk_04->rawData, 0, 0, 32, 20);
        Bg_ChangeTilemapRectPalette(param1->unk_00, 2, 0, 0, 32, 20, 13 + 1);
        Bg_ScheduleTilemapTransfer(param1->unk_00, 2);
        param0->unk_48++;
        break;
    case 1:
        if (param0->unk_4A == param0->unk_4B) {
            param0->unk_48 = 3;
            break;
        }

        Sound_PlayEffect(SEQ_SE_PL_BALLOON07_sseq);
        Sprite_SetDrawFlag(param0->unk_08[(param0->unk_4A % (5 * 3))], TRUE);
        param0->unk_49 = 8;
        param0->unk_48++;
        break;
    case 2:
        param0->unk_49--;

        if (param0->unk_49 == 0) {
            param0->unk_4A++;

            if ((param0->unk_4A % (5 * 3)) == 0) {
                int v0;

                if (param0->unk_4A != param0->unk_4B) {
                    for (v0 = 0; v0 < (5 * 3); v0++) {
                        Sprite_SetDrawFlag(param0->unk_08[v0], FALSE);
                        Sprite_SetAnim(param0->unk_08[v0], 2);
                    }
                }
            }

            param0->unk_48 = 1;
        }
        break;
    case 3:
        return 1;
    }

    return 0;
}

static void WiFiLobbyMinigame_InitPlayerRowWithScore(WiFiLobbyMinigameResultsScreen *param0, u32 param1, u32 param2)
{
    BOOL v0;
    u32 v1;
    u32 v2;

    WiFiLobbyMinigame_InitPlayerRow(&param0->unk_2C0[param1], param0->unk_0C.unk_08, param0->unk_07, param0->unk_2BC[0], &param0->unk_4C, param1, param0->unk_0C.unk_09, &param0->unk_A0, param0->unk_248, param0->heapID);

    v2 = WiFiLobbyMinigame_GetNetIdByIndex(&param0->unk_0C, param1);
    v0 = WiFiLobbyMinigame_IsPlayerReady(&param0->unk_0C, v2);

    WiFiLobbyMinigame_DrawPlayerRowName(&param0->unk_2C0[param1], &param0->unk_58, param0->unk_34.unk_08[param1], 8, 0, v0);
    WiFiLobbyMinigame_DrawPlayerRowLocation(&param0->unk_2C0[param1], &param0->unk_58, param0->unk_05, param0->unk_34.unk_00[param1], param0->unk_34.unk_04[param1], 8);

    if (param0->unk_07 == WiFiPlazaLobbyActivity_00) {
        v1 = 5;
    } else {
        v1 = 6;
    }

    WiFiLobbyMinigame_DrawPlayerRowScore(&param0->unk_2C0[param1], &param0->unk_58, param0->unk_1C.unk_00[param1], 176 + (-sPlayerRowSlideOffsets[4 - (param2 + 1)]), 0, v1);
    WiFiLobbyMinigame_TransferPlayerRow(&param0->unk_2C0[param1], &param0->unk_4C);
    WiFiLobbyMinigame_ShowPlayerRowRankIcon(&param0->unk_2C0[param1], param2);
    WiFiLobbyMinigame_StartPlayerRowSlideIn(&param0->unk_2C0[param1], sPlayerRowSlideOffsets[param2], 0);
}

static BOOL WiFiLobbyMinigame_UpdatePlayerRowsMotion(WiFiLobbyMinigameResultsScreen *param0)
{
    int v0;
    BOOL v1;
    BOOL v2 = 1;

    for (v0 = 0; v0 < param0->unk_0C.unk_08; v0++) {
        if (param0->unk_2C0[v0].unk_10 != NULL) {
            v1 = WiFiLobbyMinigame_UpdatePlayerRowMotion(&param0->unk_2C0[v0]);
            WiFiLobbyMinigame_UpdateScrollEffect(&param0->unk_3A0, &param0->unk_2C0[v0]);

            if (v1 == 0) {
                v2 = 0;
            }
        } else {
            v2 = 0;
        }
    }

    return v2;
}

static void WiFiLobbyMinigame_PlayWinFanfare(WiFiLobbyMinigameResultsScreen *param0)
{
    if (param0->unk_6C4 == 0) {
        Sound_PlayFanfare(SEQ_PL_WINMINI2_sseq);
        param0->unk_6C4 = 1;
    }
}

static BOOL WiFiLobbyMinigame_IsWinFanfareDone(WiFiLobbyMinigameResultsScreen *param0)
{
    if (param0->unk_6C4 == 1) {
        if (Sound_IsBGMPausedByFanfare() == 0) {
            param0->unk_6C4 = 0;
        }
    }

    if (param0->unk_6C4 == 1) {
        return 0;
    } else {
        return 1;
    }
}

static void WiFiLobbyMinigame_RecordFriendGameCount(WiFiLobbyMinigameResultsScreen *param0)
{
    WiFiList *v0 = SaveData_GetWiFiList(param0->unk_0C.saveData);
    int v1;
    int v2, v3;
    int v4;
    DWCFriendData *v5;

    for (v1 = 0; v1 < param0->unk_0C.unk_08; v1++) {
        v2 = param0->unk_0C.unk_04[v1];
        v5 = CommInfo_DWCFriendData(v2);
        v3 = WiFiFriend_FindSlot(param0->unk_0C.saveData, v5, &v4);

        switch (v3) {
        case 0:
        case 1:
            switch (param0->unk_07) {
            case WiFiPlazaLobbyActivity_00:
                WiFiList_AddFriendPlazaGame0Count(v0, v4, 1);
                break;
            case WiFiPlazaLobbyActivity_01:
                WiFiList_AddFriendPlazaGame1Count(v0, v4, 1);
                break;
            case WiFiPlazaLobbyActivity_02:
                WiFiList_AddFriendPlazaGame2Count(v0, v4, 1);
                break;
            }
            break;
        default:
            break;
        }
    }
}

static u32 WiFiLobbyMinigame_GetTargetScore(const WiFiLobbyMinigameResultsScreen *param0)
{
    u32 v0;

    switch (param0->unk_07) {
    case WiFiPlazaLobbyActivity_00:
        v0 = 0;
        break;
    case WiFiPlazaLobbyActivity_01:
        v0 = 0;
        break;
    case WiFiPlazaLobbyActivity_02:
        GF_ASSERT(FALSE);
        v0 = 0;
        break;
    }

    return v0;
}

static void WiFiLobbyMinigame_SendGameResults(WiFiLobbyMinigameResultsScreen *param0)
{
    int v0;
    u32 v1[4] = { 0 };
    u32 v2;
    u32 v3;

    v2 = 0;
    v3 = WiFiLobbyMinigame_GetTargetScore(param0);

    for (v0 = 0; v0 < param0->unk_0C.unk_08; v0++) {
        if ((param0->unk_1C.unk_10[v0] == 0) && (param0->unk_1C.unk_00[v0] != v3)) {
            v1[v2] = param0->unk_0C.unk_0C->userIDs.playerIndices[v0];
            v2++;
        }
    }

    if (v2 > 0) {
        WiFiPlazaLobby_State_SendMinigameResultMessage(param0->unk_0C.unk_0C->state, param0->unk_07, v2, v1[0], v1[1], v1[2], v1[3]);
    }
}

static void WiFiLobbyMinigame_SendGameResultsGame2(WiFiLobbyMinigameResultsScreen *param0)
{
    if (param0->unk_0C.unk_08 > 0) {
        if (param0->unk_1C.unk_14 >= 10) {
            WiFiPlazaLobby_State_SendMinigameResultMessage(param0->unk_0C.unk_0C->state, param0->unk_07, param0->unk_0C.unk_08, param0->unk_0C.unk_0C->userIDs.playerIndices[0], param0->unk_0C.unk_0C->userIDs.playerIndices[1], param0->unk_0C.unk_0C->userIDs.playerIndices[2], param0->unk_0C.unk_0C->userIDs.playerIndices[3]);
        }
    }
}

static void WiFiLobbyMinigame_InitCurtain(WiFiLobbyMinigameCurtain *param0, WiFiLobbyMinigameSpriteResource *param1, SpriteList *param2, u32 param3)
{
    int v0;
    int v1;

    memset(param0->unk_0C[0], 0, 192);
    memset(param0->unk_0C[1], 0, 192);

    param0->unk_08 = 0;
    param0->unk_0A = 0;
    param0->unk_18C = NULL;

    for (v0 = 0; v0 < 2; v0++) {
        param0->unk_00[v0] = WiFiLobbyMinigame_AddSprite(param1, param2, sCurtainSpritePositions[v0].x >> FX32_SHIFT, sCurtainSpritePositions[v0].y >> FX32_SHIFT, 0, param3);
        Sprite_SetAnim(param0->unk_00[v0], 5);
        Sprite_SetExplicitPriority(param0->unk_00[v0], 0);
    }

    v1 = GX_GetVisibleWnd();
    v1 &= ~GX_WNDMASK_W0;

    GX_SetVisibleWnd(v1);
    G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
    G2_SetWnd0Position(0, 0, 0, 0);

    param0->unk_190 = G2_GetWndOutsidePlane();
    param0->unk_194 = GX_GetVisibleWnd() & GX_WNDMASK_W1;
    param0->battlerType.planeMask = GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3;
    param0->battlerType.effect = 1;

    SetHBlankCallback(WiFiLobbyMinigame_CurtainHBlank, param0);
    Sprite_SetFlipMode(param0->unk_00[1], 2);

    WiFiLobbyMinigame_UpdateCurtainWindow(param0);
}

static BOOL WiFiLobbyMinigame_OpenCurtain(WiFiLobbyMinigameCurtain *param0)
{
    BOOL v0 = 0;

    param0->unk_08++;

    if (param0->unk_08 >= 8) {
        param0->unk_08 = 8;
        v0 = 1;
    }

    WiFiLobbyMinigame_SetCurtainPosition(param0, 1);

    return v0;
}

static BOOL WiFiLobbyMinigame_CloseCurtain(WiFiLobbyMinigameCurtain *param0)
{
    BOOL v0 = 0;

    param0->unk_08--;

    if (param0->unk_08 <= 0) {
        param0->unk_08 = 1;
        v0 = 1;

        Sprite_SetDrawFlag(param0->unk_00[0], FALSE);
        Sprite_SetDrawFlag(param0->unk_00[1], FALSE);
    }

    WiFiLobbyMinigame_SetCurtainPosition(param0, -1);

    return v0;
}

static void WiFiLobbyMinigame_SetCurtainPosition(WiFiLobbyMinigameCurtain *param0, s32 param1)
{
    VecFx32 v0;
    int v1;
    int v2;

    param0->unk_0A = (param0->unk_08 * 23) / 8;

    if (((param0->unk_08 + param1) <= 8) && ((param0->unk_08 + param1) >= 0)) {
        v2 = ((param0->unk_08 + param1) * 23) / 8;
    } else {
        v2 = param0->unk_0A;
    }

    for (v1 = 0; v1 < 2; v1++) {
        v0 = sCurtainSpritePositions[v1];

        if (v1 == 0) {
            v0.y -= FX32_CONST(v2);
        } else {
            v0.y += FX32_CONST(v2);
        }

        Sprite_SetPosition(param0->unk_00[v1], &v0);
    }

    WiFiLobbyMinigame_UpdateCurtainWindow(param0);
}

static void WiFiLobbyMinigame_FreeCurtain(WiFiLobbyMinigameCurtain *param0)
{
    int v0;

    if (param0->unk_18C) {
        SysTask_Done(param0->unk_18C);
        param0->unk_18C = NULL;
    }

    for (v0 = 0; v0 < 2; v0++) {
        if (param0->unk_00[v0] != NULL) {
            Sprite_Delete(param0->unk_00[v0]);
            param0->unk_00[v0] = NULL;
        }
    }

    DisableHBlank();

    GX_SetVisibleWnd(param0->unk_194);
    G2_SetWndOutsidePlane(param0->unk_190.planeMask, param0->unk_190.effect);
}

static void WiFiLobbyMinigame_UpdateCurtainWindow(WiFiLobbyMinigameCurtain *param0)
{
    int v0;

    memset(param0->unk_0C[1], 0, 192);

    for (v0 = 0; v0 < 23 - param0->unk_0A; v0++) {
        param0->unk_0C[1][(96 - 23) + v0] = 1;
        param0->unk_0C[1][((96 + 2) + 23) - v0] = 1;
    }

    if (param0->unk_18C == NULL) {
        param0->unk_18C = SysTask_ExecuteAfterVBlank(WiFiLobbyMinigame_CurtainWindowTask, param0, 0);
    }
}

static void WiFiLobbyMinigame_CurtainWindowTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameCurtain *v0 = param1;

    memcpy(v0->unk_0C[0], v0->unk_0C[1], 192);
    SysTask_Done(v0->unk_18C);

    v0->unk_18C = NULL;
}

static void WiFiLobbyMinigame_CurtainHBlank(void *param0)
{
    WiFiLobbyMinigameCurtain *v0 = param0;
    s32 v1;
    int v2;

    v1 = GX_GetVCount();
    v1 = (v1 + 1) % 256;

    if (v1 < 192) {
        v2 = GX_GetVisibleWnd();

        if (GX_IsHBlank()) {
            if ((v1 < (96 - 23)) || (v1 > ((96 + 2) + 23))) {
                G2_SetWndOutsidePlane(v0->unk_190.planeMask, v0->unk_190.effect);
                v2 |= v0->unk_194;
            } else {
                G2_SetWndOutsidePlane(v0->battlerType.planeMask, v0->battlerType.effect);
                v2 &= ~(GX_WNDMASK_W1 | v0->unk_194);
            }

            if (v0->unk_0C[0][v1] == 1) {
                GX_SetVisibleWnd(v2 | GX_WNDMASK_W0);
            } else {
                v2 &= ~GX_WNDMASK_W0;
                GX_SetVisibleWnd(v2);
            }
        }
    }
}

static void WiFiLobbyMinigame_IntroAnimationRollTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameIntroAnimation *v0 = param1;
    BOOL v1;
    u16 v2;
    u16 v3;

    switch (v0->unk_04) {
    case 0:
        break;
    case 1:
        WiFiLobbyMinigame_InitCurtain(&v0->unk_34, v0->unk_28, v0->unk_08, v0->unk_00);
        v0->unk_30 = WiFiLobbyMinigame_AddSprite(v0->unk_28, v0->unk_08, 128, 97, 64, v0->unk_00);
        Sprite_SetExplicitPriority(v0->unk_30, 0);
        v0->unk_04++;
        break;
    case 2:
        v1 = WiFiLobbyMinigame_OpenCurtain(&v0->unk_34);

        if (v1 == 1) {
            v0->unk_04++;
            v0->unk_06 = 0;
        }
        break;
    case 3:
        v2 = Sprite_GetAnimFrame(v0->unk_30);
        Sprite_UpdateAnim(v0->unk_30, FX32_CONST(2));
        v3 = Sprite_GetAnimFrame(v0->unk_30);

        if (v2 != v3) {
            switch (v3) {
            case 7:
                Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
                break;
            case 9:
                Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
                break;
            case 11:
                Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
                break;
            case 13:
                Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
                break;
            case 15:
                Sound_PlayEffect(SEQ_SE_DP_CON_016_sseq);
                break;
            default:
                break;
            }
        }

        if (v3 == 15) {
            if (v0->unk_06 == 0) {
                Sprite_SetExplicitPaletteOffsetAutoAdjust(v0->unk_30, 0);
            } else if (v0->unk_06 == 4) {
                Sprite_SetExplicitPaletteOffsetAutoAdjust(v0->unk_30, 1);
            }

            v0->unk_06++;

            if (v0->unk_06 >= 4 * 2) {
                v0->unk_06 = 0;
            }
        }

        v1 = Sprite_IsAnimated(v0->unk_30);

        if (v1 == 0) {
            v0->unk_04++;
            Sprite_SetExplicitPaletteOffsetAutoAdjust(v0->unk_30, 0);
        }
        break;
    case 4:
        v1 = WiFiLobbyMinigame_CloseCurtain(&v0->unk_34);

        if (v1 == 1) {
            Sprite_Delete(v0->unk_30);
            v0->unk_30 = NULL;
            v0->unk_04++;
            v0->unk_06 = 0;
        }
        break;
    case 5:
        v0->unk_06++;

        if (v0->unk_06 < 2) {
            break;
        }

        v0->unk_04 = 0;

        WiFiLobbyMinigame_FreeCurtain(&v0->unk_34);
        SysTask_Done(v0->unk_2C);
        v0->unk_2C = NULL;
        break;
    default:
        break;
    }
}

static void WiFiLobbyMinigame_IntroAnimationPopTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameIntroAnimation *v0 = param1;
    BOOL v1;

    switch (v0->unk_04) {
    case 0:
        break;
    case 1:
        WiFiLobbyMinigame_InitCurtain(&v0->unk_34, v0->unk_28, v0->unk_08, v0->unk_00);
        v0->unk_30 = WiFiLobbyMinigame_AddSprite(v0->unk_28, v0->unk_08, 128, 97, 64, v0->unk_00);
        Sprite_SetAnim(v0->unk_30, 1);
        Sprite_SetExplicitPriority(v0->unk_30, 0);
        v0->unk_04++;
        break;
    case 2:
        v1 = WiFiLobbyMinigame_OpenCurtain(&v0->unk_34);

        if (v1 == 1) {
            Sprite_SetAnimateFlag(v0->unk_30, 1);
            v0->unk_04++;
            v0->unk_06 = 0;
        }
        break;
    case 3:
        v0->unk_06++;

        if (v0->unk_06 >= 50) {
            v0->unk_04++;
        }
        break;
    case 4:
        v1 = WiFiLobbyMinigame_CloseCurtain(&v0->unk_34);

        if (v1 == 1) {
            Sprite_Delete(v0->unk_30);
            v0->unk_30 = NULL;
            v0->unk_06 = 0;
            v0->unk_04++;
        }
        break;
    case 5:
        v0->unk_06++;

        if (v0->unk_06 < 2) {
            break;
        }

        v0->unk_04 = 0;

        WiFiLobbyMinigame_FreeCurtain(&v0->unk_34);
        SysTask_Done(v0->unk_2C);
        v0->unk_2C = NULL;
        break;
    default:
        break;
    }
}
