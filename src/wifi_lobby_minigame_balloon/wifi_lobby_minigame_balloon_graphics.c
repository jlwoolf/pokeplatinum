#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_graphics.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/font_oam.h"
#include "struct_decls/struct_02012744_decl.h"
#include "struct_defs/struct_font_oam_template.h"

#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_app.h"
#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_comm_cmd_handlers.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_game.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_score_gauge.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_pop_effect.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_confetti.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_confetti_manager.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_rank_icon.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_score_packet.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_player_balloon_sprites.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_player_balloons.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_player_balloon.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_opponent_balloon.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_opponent_balloons.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_text_oam.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_score_display.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_intro_banner.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_sparkle.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_spawn.h"

#include "bg_window.h"
#include "char_transfer.h"
#include "communication_system.h"
#include "error_handling.h"
#include "font.h"
#include "graphics.h"
#include "math_util.h"
#include "message.h"
#include "narc.h"
#include "palette.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "text.h"
#include "font_oam.h"

typedef struct {
    u16 tilesIndex;
    u16 tilemapIndex;
    fx32 scale;
} WiFiLobbyMinigameBalloonGaugeGraphics;

typedef struct {
    s32 targets[3];
} WiFiLobbyMinigameBalloonGaugeTargets;

typedef struct {
    u8 framesPerStep;
    u8 pauseFrames;
    u8 popFrames;
    u8 unk_03;
} WiFiLobbyMinigameBalloonRotationStep;

static void WiFiLobbyMinigameBalloon_UpdateScoreGauge(BgConfig *param0, WiFiLobbyMinigameBalloonScoreGauge *param1, int param2);
int WiFiLobbyMinigameBalloon_GetGaugePercent(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_CalcGaugeScale(int param0, int param1, int param2, fx32 *param3, fx32 *param4);
static int WiFiLobbyMinigameBalloon_AddScore(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonScoreGauge *param1, int param2, int param3, int param4);
static int WiFiLobbyMinigameBalloon_InitPopEffect(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonScorePacket *param1, WiFiLobbyMinigameBalloonPopEffect *param2);
static BOOL WiFiLobbyMinigameBalloon_UpdatePopEffect(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPopEffect *param1);
static ManagedSprite *WiFiLobbyMinigameBalloon_CreatePopSprite(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonSpawn *param1);
static void WiFiLobbyMinigameBalloon_CreateConfetti(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonConfettiManager *param1, WiFiLobbyMinigameBalloonScoreGauge *param2);
static void WiFiLobbyMinigameBalloon_StopScoreGauge(BgConfig *param0, WiFiLobbyMinigameBalloonScoreGauge *param1);
static ManagedSprite *WiFiLobbyMinigameBalloon_CreateRankIcon(WiFiLobbyMinigameBalloonGame *param0, int param1, int param2);
void WiFiLobbyMinigameBalloon_CreateRankIcons(WiFiLobbyMinigameBalloonGame *param0);
BOOL WiFiLobbyMinigameBalloon_UpdateRankIcons(WiFiLobbyMinigameBalloonGame *param0);
static BOOL WiFiLobbyMinigameBalloon_InitRankIcon(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonRankIcon *param1, int param2, int param3);
static void WiFiLobbyMinigameBalloon_SlideRankIcon(WiFiLobbyMinigameBalloonRankIcon *param0);
static void WiFiLobbyMinigameBalloon_UpdateRankIcon(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonRankIcon *param1);
static int WiFiLobbyMinigameBalloon_GetRankIconAnim(int param0);
static void WiFiLobbyMinigameBalloon_AdvanceRankIcons(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_UpdatePlayerBalloon(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1, WiFiLobbyMinigameBalloonPlayerBalloon *param2);
static void WiFiLobbyMinigameBalloon_SetPlayerBalloonState(WiFiLobbyMinigameBalloonPlayerBalloon *param0, int param1);
static int WiFiLobbyMinigameBalloon_PlayerBalloonStateIdle(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1, WiFiLobbyMinigameBalloonPlayerBalloon *param2);
static int WiFiLobbyMinigameBalloon_PlayerBalloonStateEnter(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1, WiFiLobbyMinigameBalloonPlayerBalloon *param2);
static int WiFiLobbyMinigameBalloon_PlayerBalloonStateOrbit(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1, WiFiLobbyMinigameBalloonPlayerBalloon *param2);
static int WiFiLobbyMinigameBalloon_PlayerBalloonStatePop(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1, WiFiLobbyMinigameBalloonPlayerBalloon *param2);
static int WiFiLobbyMinigameBalloon_GetActivePlayerBalloon(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloon **param1);
static BOOL WiFiLobbyMinigameBalloon_UpdateOpponentBalloon(WiFiLobbyMinigameBalloonOpponentBalloons *param0, WiFiLobbyMinigameBalloonOpponentBalloon *param1);
static void WiFiLobbyMinigameBalloon_StartScoreRoll(WiFiLobbyMinigameBalloonScoreDisplay *param0);
static BOOL WiFiLobbyMinigameBalloon_ScoreRollDone(WiFiLobbyMinigameBalloonScoreDisplay *param0);
static BOOL WiFiLobbyMinigameBalloon_AdvanceScoreRoll(WiFiLobbyMinigameBalloonScoreDisplay *param0);
static void WiFiLobbyMinigameBalloon_CreateSparkles(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonSparkle *param1);
static void WiFiLobbyMinigameBalloon_FreeSparkles(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonSparkle *param1);
static void WiFiLobbyMinigameBalloon_StartSparkles(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloon *param1, WiFiLobbyMinigameBalloonSparkle *param2);
static void WiFiLobbyMinigameBalloon_UpdateSparkles(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloon *param1, WiFiLobbyMinigameBalloonSparkle *param2);

static const u16 sConfettiAnimByPlayerCount[][4] = {
    { 0x16, 0x15, 0x17, 0x18 },
    { 0x16, 0x15, 0x17, 0x18 },
    { 0x16, 0x17 },
    { 0x16, 0x18, 0x17 },
    { 0x16, 0x15, 0x17, 0x18 }
};

__attribute__((aligned(4))) static const u16 sGaugePaletteByLevel[] = {
    0x6,
    0x8,
    0x7
};

static const WiFiLobbyMinigameBalloonSpawn sBalloonSpawns[][4] = {
    {
        { 0x80, 0xD0, 0x7, 0x2, 0x2 },
    },
    {
        { 0x80, 0xD0, 0x7, 0x2, 0x2 },
    },
    {
        { 0x80, 0xD0, 0x7, 0x2, 0x2 },
        { 0x80, 0xFFFFFFFFFFFFFFF0, 0xA, 0x1, 0x0 },
    },
    {
        { 0x80, 0xD0, 0x7, 0x2, 0x2 },
        { 0xFFFFFFFFFFFFFFF0, 0x60, 0x9, 0x3, 0x3 },
        { 0x110, 0x60, 0x8, 0x1, 0x1 },
    },
    {
        { 0x80, 0xD0, 0x7, 0x2, 0x2 },
        { 0xFFFFFFFFFFFFFFF0, 0x60, 0x9, 0x4, 0x3 },
        { 0x80, 0xFFFFFFFFFFFFFFF0, 0xA, 0x1, 0x0 },
        { 0x100, 0x60, 0x8, 0x3, 0x1 },
    },
};

static const SpriteTemplate sPopSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x14,
    0x1,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 0x2714, 0x2716, 0x2714, 0x2714, 0xFFFFFFFF, 0xFFFFFFFF },
    0x3,
    0x0
};

static const SpriteTemplate sConfettiSpriteTemplate = {
    0x80,
    0x60,
    0x0,
    0x0,
    0xC,
    0x5,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 0x2714, 0x2716, 0x2714, 0x2714, 0xFFFFFFFF, 0xFFFFFFFF },
    0x1,
    0x0
};

static const SpriteTemplate sRankIconSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0xB,
    0x0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 0x2714, 0x2716, 0x2714, 0x2714, 0xFFFFFFFF, 0xFFFFFFFF },
    0x1,
    0x0
};

static const SpriteTemplate sPlayerBalloonSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x13,
    0x0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 0x2714, 0x2716, 0x2714, 0x2714, 0xFFFFFFFF, 0xFFFFFFFF },
    0x3,
    0x0
};

static const SpriteTemplate sPlayerBalloonSpriteTemplate2 = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x10,
    0x2,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 0x2714, 0x2716, 0x2714, 0x2714, 0xFFFFFFFF, 0xFFFFFFFF },
    0x3,
    0x0
};

static const SpriteTemplate sBalloonShadowSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0xF,
    0x0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 0x2714, 0x2716, 0x2714, 0x2714, 0xFFFFFFFF, 0xFFFFFFFF },
    0x3,
    0x0
};

static const SpriteTemplate sBalloonHighlightSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x12,
    0x1,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 0x2714, 0x2716, 0x2714, 0x2714, 0xFFFFFFFF, 0xFFFFFFFF },
    0x3,
    0x0
};

static const SpriteTemplate sSparkleSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x11,
    0x0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 0x2714, 0x2716, 0x2714, 0x2714, 0xFFFFFFFF, 0xFFFFFFFF },
    0x3,
    0x0
};

static const SpriteTemplate sScoreSpriteTemplate = {
    0x28,
    0xB0,
    0x0,
    0x0,
    0xD,
    0x0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x2712, 0x2714, 0x2712, 0x2712, 0xFFFFFFFF, 0xFFFFFFFF },
    0x3,
    0x0
};

static const SpriteTemplate sIntroBannerSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0xB,
    0x0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x2711, 0x2712, 0x2711, 0x2711, 0xFFFFFFFF, 0xFFFFFFFF },
    0x0,
    0x0
};

static const u16 sMainPaletteDestByPlayerCount[][4] = {
    { 0x1D, 0x2D, 0xD, 0x3D },
    { 0x1D, 0x2D, 0xD, 0x3D },
    { 0x1D, 0xD },
    { 0x1D, 0x3D, 0xD },
    { 0x1D, 0x2D, 0xD, 0x3D }
};

static const u16 sMainPaletteSrcByPlayer[4] = {
    0x1D,
    0xD,
    0x3D,
    0x2D
};

static const u16 sSubPaletteDestByPlayerCount[][4] = {
    { 0x20, 0x10, 0x30, 0x40 },
    { 0x20, 0x10, 0x30, 0x40 },
    { 0x20, 0x10 },
    { 0x20, 0x30, 0x10 },
    { 0x20, 0x40, 0x10, 0x30 }
};

static const u16 sSubPaletteSrcByPlayer[4] = {
    0x20,
    0x10,
    0x30,
    0x40
};

static const fx32 sPopScaleByType[] = {
    FX32_ONE,
    0x1800,
    0xA00,
    0x2000,
};

static const u16 sSubPalette2DestByPlayerCount[][4] = {
    { 0x52, 0x51, 0x53, 0x54 },
    { 0x52, 0x51, 0x53, 0x54 },
    { 0x52, 0x51 },
    { 0x52, 0x53, 0x51 },
    { 0x52, 0x54, 0x51, 0x53 }
};

static const u16 sSubPalette2SrcByPlayer[4] = {
    0x52,
    0x51,
    0x53,
    0x54
};

static const struct {
    s16 x;
    s16 y;
} sPlayerPositions[] = {
    { 0x80, 0xA4 },
    { 0x80, 0x1C },
    { 0x34, 0x60 },
    { 0xCC, 0x60 }
};

static const u16 sBalloonAnimByLevel[] = {
    0xC,
    0xC,
    0xF,
    0x12
};

static const u16 sOpponentPaletteByPlayerCount[][4] = {
    { 0x2, 0x4, 0x1, 0x3 },
    { 0x2, 0x4, 0x1, 0x3 },
    { 0x2, 0x1 },
    { 0x2, 0x3, 0x1 },
    { 0x2, 0x4, 0x1, 0x3 }
};

static const u8 sOpponentPositionByPlayerCount[][4] = {
    { 0x0 },
    { 0x0, 0x2, 0x1, 0x3 },
    { 0x0, 0x1 },
    { 0x0, 0x2, 0x3 },
    { 0x0, 0x2, 0x1, 0x3 }
};

static const WiFiLobbyMinigameBalloonGaugeTargets sGaugeTargets[] = {
    { 0xBB8, 0x1770, 0x1F40 },
    { 0x3E8, 0x3E8, 0x3E8 },
    { 0x19A6, 0x20FA, 0x284E },
    { 0x20EC, 0x2A54, 0x33BC },
    { 0x2648, 0x3138, 0x3C28 }
};

static const WiFiLobbyMinigameBalloonGaugeGraphics sGaugeGraphics[] = {
    { 0xB, 0xC, 0x1100 },
    { 0x9, 0xA, 0x1700 },
    { 0x7, 0x8, 0x1D00 }
};

static const WiFiLobbyMinigameBalloonRotationStep sRotationSteps[] = {
    { 0x8, 0x14, 0x7 },
    { 0x8, 0x11, 0x7 },
    { 0x8, 0xE, 0x6 },
    { 0x8, 0xA, 0x6 },
    { 0x8, 0x6, 0x5 }
};

const s32 sScoreMultipliers[] = {
    0x64,
    0x7D,
    0x58
};

static int (*const sPlayerBalloonStateTable[])(WiFiLobbyMinigameBalloonGame *, WiFiLobbyMinigameBalloonPlayerBalloons *, WiFiLobbyMinigameBalloonPlayerBalloon *) = {
    WiFiLobbyMinigameBalloon_PlayerBalloonStateIdle,
    WiFiLobbyMinigameBalloon_PlayerBalloonStateEnter,
    WiFiLobbyMinigameBalloon_PlayerBalloonStateOrbit,
    WiFiLobbyMinigameBalloon_PlayerBalloonStatePop,
};

void WiFiLobbyMinigameBalloon_StartScoreGauge(BgConfig *param0, int param1, int param2, WiFiLobbyMinigameBalloonScoreGauge *param3)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_APPLICATION__BALLOON__GRAPHIC__BALLOON_GRA, HEAP_ID_110);

    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, sGaugeGraphics[param2].tilesIndex, param0, 7, 0, 0, 0, HEAP_ID_110);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, sGaugeGraphics[param2].tilemapIndex, param0, 7, 0, 0, 0, HEAP_ID_110);
    NARC_dtor(v0);

    MI_CpuClear8(param3, sizeof(WiFiLobbyMinigameBalloonScoreGauge));

    param3->targetScore = sGaugeTargets[param1].targets[param2];
    param3->gaugeLevel = param2;
    param3->active = 1;
    param3->showRequest = 1;

    WiFiLobbyMinigameBalloon_UpdateScoreGauge(param0, param3, param1);
    Sound_PlayEffect(SEQ_SE_DP_BOX02_sseq);
}

static void WiFiLobbyMinigameBalloon_StopScoreGauge(BgConfig *param0, WiFiLobbyMinigameBalloonScoreGauge *param1)
{
    Bg_ClearTilemap(param0, BG_LAYER_SUB_3);
    param1->active = 0;
    param1->hideRequest = 1;
}

static void WiFiLobbyMinigameBalloon_UpdateScoreGauge(BgConfig *param0, WiFiLobbyMinigameBalloonScoreGauge *param1, int param2)
{
    fx32 v0, v1;
    int v2, v3;

    if (param1->active == 0) {
        return;
    }

    WiFiLobbyMinigameBalloon_CalcGaugeScale(param2, param1->gaugeLevel, param1->currentScore, &v0, &v1);

    v2 = 0;
    v3 = 0;

    if (v0 == FX32_ONE) {
        v2 = 0;
    } else if (v0 < FX32_ONE) {
        v2 = 128 - (128 * v0 / FX32_ONE);
    } else {
        v2 = -(128 * (v0 - FX32_ONE) / FX32_ONE);
    }

    if (v1 == FX32_ONE) {
        v3 = 0;
    } else if (v1 < FX32_ONE) {
        v3 = 128 - (128 * v1 / FX32_ONE);
    } else {
        v3 = -(128 * (v1 - FX32_ONE) / FX32_ONE);
    }

    {
        MtxFx22 v4;
        fx32 v5, v6;
        int v7;

        if (param1->pendingScore == 0) {
            v7 = 0;
        } else {
            v7 = (LCRNG_Next() & 7) + 1;

            if (param1->scrollFlip & 1) {
                v7 = -v7;
            }

            param1->scrollFlip ^= 1;
        }

        v5 = FX_Inv(v0);
        v6 = FX_Inv(v1);

        Bg_ScheduleAffineScale(param0, 7, 3, v5);
        Bg_ScheduleAffineScale(param0, 7, 6, v6);
        Bg_ScheduleScroll(param0, 7, 0, 0 - v2 + v7);
        Bg_ScheduleScroll(param0, 7, 3, (256 - 192) / 2 + 7 - v3);
    }
}

static void WiFiLobbyMinigameBalloon_CalcGaugeScale(int param0, int param1, int param2, fx32 *param3, fx32 *param4)
{
    fx32 v0;

    v0 = sGaugeGraphics[param1].scale * param2 / sGaugeTargets[param0].targets[param1];
    v0 += 0x300;

    *param3 = v0;
    *param4 = v0;

    if (v0 > (FX32_ONE)) {
        *param3 += FX_Mul((v0 - (FX32_ONE)), (FX32_CONST(1.1)));
    }
}

int WiFiLobbyMinigameBalloon_GetGaugeLevel(int param0)
{
    if (10 <= param0) {
        return 2;
    } else if (5 <= param0) {
        return 1;
    }

    return 0;
}

static int WiFiLobbyMinigameBalloon_AddScore(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonScoreGauge *param1, int param2, int param3, int param4)
{
    param1->pendingScore += param2;
    param1->step = param1->pendingScore / 6;
    param1->playerScores[WiFiLobbyMinigameBalloon_GetPlayerSlot(param0, param3)] += param2;

    if (param3 == CommSys_CurNetId()) {
        param0->localScore += param2;
        WiFiLobbyMinigameBalloon_SetScoreDigits(&param0->scoreDisplay, param0->localScore);
    }

    return param1->pendingScore;
}

static int WiFiLobbyMinigameBalloon_AdvanceGauge(WiFiLobbyMinigameBalloonScoreGauge *param0)
{
    int v0;

    if (param0->pendingScore == 0) {
        return 0;
    }

    if (param0->pendingScore >= param0->step) {
        v0 = param0->step;
    } else {
        v0 = param0->pendingScore;
    }

    param0->pendingScore -= v0;
    param0->currentScore += v0;

    return 1;
}

void WiFiLobbyMinigameBalloon_DrawScoreGauge(WiFiLobbyMinigameBalloonGame *param0, BgConfig *param1, WiFiLobbyMinigameBalloonScoreGauge *param2)
{
    if (param0->gaugeActive == 0) {
        return;
    }

    WiFiLobbyMinigameBalloon_AdvanceGauge(param2);
    WiFiLobbyMinigameBalloon_UpdateScoreGauge(param1, param2, param0->context->playerCount);
}

int WiFiLobbyMinigameBalloon_GetGaugePercent(WiFiLobbyMinigameBalloonGame *param0)
{
    WiFiLobbyMinigameBalloonScoreGauge *v0 = &param0->scoreGauge;
    return 100 * v0->currentScore / v0->targetScore;
}

BOOL WiFiLobbyMinigameBalloon_SpawnPopEffect(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonScorePacket *param1)
{
    int v0, v1;

    if (param0->balloonLevel != param1->balloonLevel) {
        (void)0;
    }

    for (v0 = 0; v0 < 40; v0++) {
        if (param0->popEffects[v0].active == 0) {
            v1 = WiFiLobbyMinigameBalloon_InitPopEffect(param0, param1, &param0->popEffects[v0]);
            WiFiLobbyMinigameBalloon_SpawnOpponentBalloon(param0, &param0->opponentBalloons, param1->multiplier, param1->netId, v1);

            return 1;
        }
    }

    GF_ASSERT(FALSE);
    return 0;
}

static int WiFiLobbyMinigameBalloon_InitPopEffect(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonScorePacket *param1, WiFiLobbyMinigameBalloonPopEffect *param2)
{
    int v0;
    const WiFiLobbyMinigameBalloonSpawn *v1;
    int v2;

    GF_ASSERT(param2->active == 0);

    MI_CpuClear8(param2, sizeof(WiFiLobbyMinigameBalloonPopEffect));

    v0 = WiFiLobbyMinigameBalloon_GetPlayerSlot(param0, param1->netId);
    v1 = &sBalloonSpawns[param0->context->playerCount][v0];

    param2->netId = param1->netId;
    param2->balloonLevel = param1->balloonLevel;
    param2->score = param1->score;
    param2->spawn = v1;
    param2->popType = param1->multiplier;
    param2->sprite = WiFiLobbyMinigameBalloon_CreatePopSprite(param0, v1);

    if (param1->netId == CommSys_CurNetId()) {
        WiFiLobbyMinigameBalloon_SpawnBalloonPop(param0, param1->baseScore);
        param2->delay = 25;
        ManagedSprite_SetDrawFlag(param2->sprite, 0);
    }

    param2->active = 1;

    {
        s16 v3, v4;
        s32 v5 = 0;

        Sprite_GetPositionXYWithSubscreenOffset2(param2->sprite, &v3, &v4, ((192 + 160) << FX32_SHIFT));

        switch (v1->direction) {
        case 0:
            v5 = sPlayerPositions[1].y - v4;
            break;
        case 1:
            v5 = v3 - sPlayerPositions[3].x;
            break;
        case 2:
            v5 = v4 - sPlayerPositions[0].y;
            break;
        case 3:
            v5 = sPlayerPositions[2].x - v3;
            break;
        }

        v2 = (v5 * FX32_ONE) / (FX32_CONST(5.0));
    }
    return v2;
}

void WiFiLobbyMinigameBalloon_UpdatePopEffects(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0;
    WiFiLobbyMinigameBalloonPopEffect *v1 = param0->popEffects;

    for (v0 = 0; v0 < 40; v0++) {
        if (v1->active == 1) {
            if (v1->delay > 0) {
                v1->delay--;

                if (v1->delay == 0) {
                    ManagedSprite_SetDrawFlag(v1->sprite, 1);
                }
            } else if (WiFiLobbyMinigameBalloon_UpdatePopEffect(param0, v1) == 1) {
                if ((param0->gaugeActive == 1) && (param0->gameEnded == 0)) {
                    WiFiLobbyMinigameBalloon_AddScore(param0, &param0->scoreGauge, v1->score, v1->netId, v1->popType);
                }

                Sprite_DeleteAndFreeResources(v1->sprite);
                v1->active = 0;
            }
        }

        v1++;
    }
}

static BOOL WiFiLobbyMinigameBalloon_UpdatePopEffect(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPopEffect *param1)
{
    s16 v0, v1, v2, v3;
    int v4 = 0;
    s32 v5, v6;
    f32 v7;
    fx32 v8;

    Sprite_GetPositionXYWithSubscreenOffset2(param1->sprite, &v2, &v3, ((192 + 160) << FX32_SHIFT));

    switch (param1->spawn->direction) {
    case 0:
        v6 = sPlayerPositions[1].y - v3;

        ManagedSprite_OffsetPositionFxXY(param1->sprite, 0, (FX32_CONST(5.0)));
        Sprite_GetPositionXYWithSubscreenOffset2(param1->sprite, &v0, &v1, ((192 + 160) << FX32_SHIFT));

        v5 = sPlayerPositions[1].y - v1;

        if (v1 > (98 - 24)) {
            v4 = 1;
        }
        break;
    case 1:
        v6 = v2 - sPlayerPositions[3].x;

        ManagedSprite_OffsetPositionFxXY(param1->sprite, -(FX32_CONST(5.0)), 0);
        Sprite_GetPositionXYWithSubscreenOffset2(param1->sprite, &v0, &v1, ((192 + 160) << FX32_SHIFT));

        v5 = v0 - sPlayerPositions[3].x;

        if (v0 < (128 + 24)) {
            v4 = 1;
        }
        break;
    case 2:
        v6 = v3 - sPlayerPositions[0].y;

        ManagedSprite_OffsetPositionFxXY(param1->sprite, 0, -(FX32_CONST(5.0)));
        Sprite_GetPositionXYWithSubscreenOffset2(param1->sprite, &v0, &v1, ((192 + 160) << FX32_SHIFT));

        v5 = v1 - sPlayerPositions[0].y;

        if (v1 < (98 + 16)) {
            v4 = 1;
        }
        break;
    case 3:
        v6 = sPlayerPositions[2].x - v2;

        ManagedSprite_OffsetPositionFxXY(param1->sprite, (FX32_CONST(5.0)), 0);
        Sprite_GetPositionXYWithSubscreenOffset2(param1->sprite, &v0, &v1, ((192 + 160) << FX32_SHIFT));

        v5 = sPlayerPositions[2].x - v0;

        if (v0 > (128 - 24)) {
            v4 = 1;
        }
        break;
    }
    if (v5 >= 0) {
        if (v5 < (24 / 2 + 2)) {
            v8 = FX32_ONE * v5 / (24 / 2 + 2);

            if (v8 < 0x400) {
                v8 = 0x400;
            }

            v7 = FX_FX32_TO_F32(v8);
            ManagedSprite_SetAffineScale(param1->sprite, v7, v7);
        }
    } else {
        if (v5 > -(24 / 2 + 2)) {
            v8 = sPopScaleByType[param1->popType] * (-v5) / (24 / 2 + 2);

            if (v8 < 0x400) {
                v8 = 0x400;
            }

            v7 = FX_FX32_TO_F32(v8);
            ManagedSprite_SetAffineScale(param1->sprite, v7, v7);
        }
    }
    if ((param1->netId == CommSys_CurNetId()) && (v6 >= 0) && (v5 <= 0)) {
        WiFiLobbyMinigameBalloonPlayerBalloon *v9;

        param1->popType = WiFiLobbyMinigameBalloon_GetActivePlayerBalloon(param0, &v9);

        switch (param1->popType) {
        case 1:
            param1->score *= 2;
            break;
        case 2:
            param1->score /= 2;
            break;
        case 3:
            param1->score *= 3;
            break;
        }

        WiFiLobbyMinigameBalloon_ApplyScoreMultiplier(param0, param1->popType);

        if (param1->popType != 0) {
            WiFiLobbyMinigameBalloon_SetPlayerBalloonState(v9, 3);
        }

        {
            WiFiLobbyMinigameBalloonScorePacket *v10;

            v10 = WiFiLobbyMinigameBalloon_DequeueScorePacket(param0);

            if (v10 != NULL) {
                WiFiLobbyMinigameBalloon_SendScorePacket(param0, v10);
            } else {
                (void)0;
            }
        }
    }

    if (v4 == 1) {
        return 1;
    }

    return 0;
}

static ManagedSprite *WiFiLobbyMinigameBalloon_CreatePopSprite(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonSpawn *param1)
{
    ManagedSprite *v0;
    SpriteTemplate v1;

    v1 = sPopSpriteTemplate;
    v1.x = param1->x;
    v1.y = param1->y;
    v1.plttIdx = param1->palette;
    v0 = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v1);

    ManagedSprite_SetPositionXYWithSubscreenOffset(v0, param1->x, param1->y, ((192 + 160) << FX32_SHIFT));
    ManagedSprite_SetAnim(v0, param1->anim);
    ManagedSprite_SetAffineOverwriteMode(v0, AFFINE_OVERWRITE_MODE_DOUBLE);
    Sprite_TickFrame(v0->sprite);

    return v0;
}

void WiFiLobbyMinigameBalloon_FreePopEffects(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0;

    for (v0 = 0; v0 < 40; v0++) {
        if (param0->popEffects[v0].active == 1) {
            Sprite_DeleteAndFreeResources(param0->popEffects[v0].sprite);
            param0->popEffects[v0].active = 0;
        }
    }
}

static void WiFiLobbyMinigameBalloon_CreateConfetti(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonConfettiManager *param1, WiFiLobbyMinigameBalloonScoreGauge *param2)
{
    SpriteTemplate v0;
    ManagedSprite *v1;
    int v2;
    int v3[4];
    int v4, v5, v6;
    int v7 = 0;
    int v8, v9;

    v0 = sConfettiSpriteTemplate;
    v4 = param2->currentScore + param2->pendingScore;

    for (v8 = 0; v8 < param0->context->playerCount; v8++) {
        v2 = WiFiLobbyMinigameBalloon_GetPlayerSlot(param0, param0->context->netIds[v8]);
        v3[v8] = param2->playerScores[v2] * 36 / v4;
        v6 = sConfettiAnimByPlayerCount[param0->context->playerCount][v2];

        for (v9 = 0; v9 < v3[v8]; v9++) {
            WiFiLobbyMinigameBalloonConfetti *v10 = &param1->confetti[v7];

            v1 = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v0);

            if (v1 == NULL) {
                break;
            }

            ManagedSprite_SetPositionXYWithSubscreenOffset(v1, 128, 96, ((192 + 160) << FX32_SHIFT));
            ManagedSprite_SetAnim(v1, v6);
            Sprite_TickFrame(v1->sprite);

            v10->radius = LCRNG_Next() % 0x2000 + 0x2000;
            v10->radiusVelocity = LCRNG_Next() % 0x4000 + 0x2000;
            v10->angle = (LCRNG_Next() % 360) << FX32_SHIFT;
            v10->angleVelocity = LCRNG_Next() % 0x14000 + 0xa000;
            v10->lifetime = LCRNG_Next() % 15 + 20;

            param1->confetti[v7].sprite = v1;

            v7++;
        }
    }

    v0.priority = 14;
    v0.plttIdx = 0;

    for (v8 = 0; v8 < 8; v8++) {
        WiFiLobbyMinigameBalloonConfetti *v11 = &param1->bursts[v8];

        v1 = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v0);

        if (v1 == NULL) {
            break;
        }

        ManagedSprite_SetPositionXYWithSubscreenOffset(v1, 128, 96, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetAnim(v1, 28 + LCRNG_Next() % 3);
        Sprite_TickFrame(v1->sprite);

        v11->radius = LCRNG_Next() % 0x2000 + 0x2000;
        v11->radiusVelocity = LCRNG_Next() % 0x4000 + 0x2000;
        v11->angle = (LCRNG_Next() % 360) << FX32_SHIFT;
        v11->angleVelocity = LCRNG_Next() % 0x14000 + 0x10000;
        v11->lifetime = LCRNG_Next() % 15 + 20;

        param1->bursts[v8].sprite = v1;
    }

    v0.priority = 13;
    v0.plttIdx = sGaugePaletteByLevel[param2->gaugeLevel];

    for (v8 = 0; v8 < 3; v8++) {
        WiFiLobbyMinigameBalloonConfetti *v12 = &param1->gaugeBursts[v8];

        v1 = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v0);

        if (v1 == NULL) {
            break;
        }

        ManagedSprite_SetPositionXYWithSubscreenOffset(v1, 128, 96, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetAnim(v1, 11);
        Sprite_TickFrame(v1->sprite);

        v12->radius = LCRNG_Next() % 0x2000 + 0x2000;
        v12->radiusVelocity = LCRNG_Next() % 0x4000 + 0x2000;
        v12->angle = (LCRNG_Next() % 360) << FX32_SHIFT;
        v12->angleVelocity = LCRNG_Next() % 0x14000 + 0x10000;
        v12->lifetime = LCRNG_Next() % 15 + 20;

        param1->gaugeBursts[v8].sprite = v1;
    }
}

void WiFiLobbyMinigameBalloon_FreeConfetti(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0;
    WiFiLobbyMinigameBalloonConfetti *v1, *v2, *v3;

    for (v0 = 0; v0 < 36; v0++) {
        v1 = &param0->confetti.confetti[v0];

        if (v1->sprite != NULL) {
            Sprite_DeleteAndFreeResources(v1->sprite);
        }
    }

    for (v0 = 0; v0 < 8; v0++) {
        v2 = &param0->confetti.bursts[v0];

        if (v2->sprite != NULL) {
            Sprite_DeleteAndFreeResources(v2->sprite);
        }
    }

    for (v0 = 0; v0 < 3; v0++) {
        v3 = &param0->confetti.gaugeBursts[v0];

        if (v3->sprite != NULL) {
            Sprite_DeleteAndFreeResources(v3->sprite);
        }
    }
}

BOOL WiFiLobbyMinigameBalloon_UpdateConfetti(WiFiLobbyMinigameBalloonGame *param0)
{
    WiFiLobbyMinigameBalloonConfettiManager *v0 = &param0->confetti;
    WiFiLobbyMinigameBalloonConfetti *v1, *v2, *v3;
    s16 v4, v5;
    int v6 = 0;
    int v7;

    if (v0->active == 0) {
        return 0;
    }

    for (v7 = 0; v7 < 36; v7++) {
        v1 = &v0->confetti[v7];

        if (v1->sprite != NULL) {
            if (v1->lifetime == 0) {
                Sprite_DeleteAndFreeResources(v1->sprite);
                v1->sprite = NULL;
                continue;
            }

            v1->angle += v1->angleVelocity;
            v1->radius += v1->radiusVelocity;

            if (v1->radius >= (128 + 32) << FX32_SHIFT) {
                v1->radius = (128 + 32) << FX32_SHIFT;
            }

            v4 = 128 + (FX_Mul(CalcSineDegrees_FX32(v1->angle), v1->radius)) / FX32_ONE;
            v5 = 96 + (-FX_Mul(CalcCosineDegrees_FX32(v1->angle), v1->radius)) / FX32_ONE;

            ManagedSprite_SetPositionXYWithSubscreenOffset(v1->sprite, v4, v5, ((192 + 160) << FX32_SHIFT));

            v1->lifetime--;
            v6++;
        }
    }

    for (v7 = 0; v7 < 8; v7++) {
        v2 = &v0->bursts[v7];

        if (v2->sprite != NULL) {
            if (v2->lifetime == 0) {
                Sprite_DeleteAndFreeResources(v2->sprite);
                v2->sprite = NULL;
                continue;
            }

            v2->angle += v2->angleVelocity;
            v2->radius += v2->radiusVelocity;

            if (v2->radius >= (128 + 32) << FX32_SHIFT) {
                v2->radius = (128 + 32) << FX32_SHIFT;
            }

            v4 = 128 + (FX_Mul(CalcSineDegrees_FX32(v2->angle), v2->radius)) / FX32_ONE;
            v5 = 96 + (-FX_Mul(CalcCosineDegrees_FX32(v2->angle), v2->radius)) / FX32_ONE;

            ManagedSprite_SetPositionXYWithSubscreenOffset(v2->sprite, v4, v5, ((192 + 160) << FX32_SHIFT));

            v2->lifetime--;
            v6++;
        }
    }

    for (v7 = 0; v7 < 3; v7++) {
        v3 = &v0->gaugeBursts[v7];

        if (v3->sprite != NULL) {
            if (v3->lifetime == 0) {
                Sprite_DeleteAndFreeResources(v3->sprite);
                v3->sprite = NULL;
                continue;
            }

            v3->angle += v3->angleVelocity;
            v3->radius += v3->radiusVelocity;

            if (v3->radius >= (128 + 32) << FX32_SHIFT) {
                v3->radius = (128 + 32) << FX32_SHIFT;
            }

            v4 = 128 + (FX_Mul(CalcSineDegrees_FX32(v3->angle), v3->radius)) / FX32_ONE;
            v5 = 96 + (-FX_Mul(CalcCosineDegrees_FX32(v3->angle), v3->radius)) / FX32_ONE;

            ManagedSprite_SetPositionXYWithSubscreenOffset(v3->sprite, v4, v5, ((192 + 160) << FX32_SHIFT));

            v3->lifetime--;
            v6++;
        }
    }

    if (v6 == 0) {
        v0->active = 0;
    }

    return 1;
}

BOOL WiFiLobbyMinigameBalloon_StartConfetti(WiFiLobbyMinigameBalloonGame *param0)
{
    WiFiLobbyMinigameBalloonConfettiManager *v0 = &param0->confetti;
    int v1;

    if (v0->active == 1) {
        return 0;
    }

    MI_CpuClear8(v0, sizeof(WiFiLobbyMinigameBalloonConfettiManager));

    WiFiLobbyMinigameBalloon_CreateConfetti(param0, &param0->confetti, &param0->scoreGauge);
    WiFiLobbyMinigameBalloon_StopScoreGauge(param0->bgConfig, &param0->scoreGauge);
    WiFiLobbyMinigameBalloon_AdvanceRankIcons(param0);

    param0->gaugeActive = 0;
    param0->scoreGauge.currentScore = 0;
    param0->scoreGauge.pendingScore = 0;

    for (v1 = 0; v1 < 4; v1++) {
        param0->scoreGauge.playerScores[v1] = 0;
    }

    Sound_PlayEffect(SEQ_SE_PL_BALLOON07_sseq);
    v0->active = 1;
    return 1;
}

static ManagedSprite *WiFiLobbyMinigameBalloon_CreateRankIcon(WiFiLobbyMinigameBalloonGame *param0, int param1, int param2)
{
    ManagedSprite *v0;
    SpriteTemplate v1;

    v1 = sRankIconSpriteTemplate;
    v0 = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v1);

    ManagedSprite_SetPositionXYWithSubscreenOffset(v0, (9 * 8) - param2 * 16, (4 * 8), ((192 + 160) << FX32_SHIFT));
    ManagedSprite_SetAnim(v0, 0 + param1);
    Sprite_TickFrame(v0->sprite);
    ManagedSprite_SetAnimateFlag(v0, 1);

    return v0;
}

void WiFiLobbyMinigameBalloon_CreateRankIcons(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0;
    WiFiLobbyMinigameBalloonRankIcon *v1;

    for (v0 = 0; v0 < 5; v0++) {
        v1 = &param0->rankIcons[v0];
        WiFiLobbyMinigameBalloon_InitRankIcon(param0, v1, v0, v0);
        ManagedSprite_TickNFrames(v1->sprite, FX32_ONE * 4 * v0);
    }
}

void WiFiLobbyMinigameBalloon_FreeRankIcons(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0;
    WiFiLobbyMinigameBalloonRankIcon *v1;

    for (v0 = 0; v0 < 5; v0++) {
        v1 = &param0->rankIcons[v0];
        Sprite_DeleteAndFreeResources(v1->sprite);
    }
}

BOOL WiFiLobbyMinigameBalloon_UpdateRankIcons(WiFiLobbyMinigameBalloonGame *param0)
{
    WiFiLobbyMinigameBalloonRankIcon *v0;
    int v1;

    for (v1 = 0; v1 < 5; v1++) {
        v0 = &param0->rankIcons[v1];
        WiFiLobbyMinigameBalloon_SlideRankIcon(v0);
        WiFiLobbyMinigameBalloon_UpdateRankIcon(param0, v0);
    }

    return 1;
}

static BOOL WiFiLobbyMinigameBalloon_InitRankIcon(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonRankIcon *param1, int param2, int param3)
{
    MI_CpuClear8(param1, sizeof(WiFiLobbyMinigameBalloonRankIcon));

    param1->anim = WiFiLobbyMinigameBalloon_GetRankIconAnim(param3);
    param1->state = 1;
    param1->sprite = WiFiLobbyMinigameBalloon_CreateRankIcon(param0, param1->anim, param2);
    param1->slot = param2;
    param1->progress = param3;

    return 1;
}

static void WiFiLobbyMinigameBalloon_SlideRankIcon(WiFiLobbyMinigameBalloonRankIcon *param0)
{
    s16 v0, v1, v2;

    v0 = (9 * 8) - param0->slot * 16;

    Sprite_GetPositionXYWithSubscreenOffset2(param0->sprite, &v1, &v2, ((192 + 160) << FX32_SHIFT));

    if (v0 > v1) {
        v1 += 2;
        if (v1 > v0) {
            v1 = v0;
        }

        ManagedSprite_SetPositionXYWithSubscreenOffset(param0->sprite, v1, v2, ((192 + 160) << FX32_SHIFT));
    }
}

static void WiFiLobbyMinigameBalloon_UpdateRankIcon(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonRankIcon *param1)
{
    int v0, v1;
    WiFiLobbyMinigameBalloonRankIcon *v2;

    if (param1->slot != 0) {
        return;
    }

    switch (param1->state) {
    case 3:
        if (ManagedSprite_IsAnimated(param1->sprite) == 0) {
            param1->progress += 5;
            param1->anim = WiFiLobbyMinigameBalloon_GetRankIconAnim(param1->progress);
            param1->state = 1;

            ManagedSprite_SetAnim(param1->sprite, 0 + param1->anim);
            ManagedSprite_SetPositionXYWithSubscreenOffset(param1->sprite, (9 * 8) - 5 * 16, (4 * 8), ((192 + 160) << FX32_SHIFT));

            for (v1 = 0; v1 < 5; v1++) {
                v2 = &param0->rankIcons[v1];

                if (v2->slot == 0) {
                    v2->slot = 5 - 1;
                } else {
                    v2->slot--;
                }
            }
        }
        break;

    case 1:
        v0 = WiFiLobbyMinigameBalloon_GetGaugePercent(param0);

        if ((param1->state == 1) && (v0 > 75)) {
            param1->state = 2;
            ManagedSprite_SetAnim(param1->sprite, 3 + param1->anim);
            Sound_PlayEffect(SEQ_SE_PL_ALERT4_sseq);
        }

        break;
    }
}

static int WiFiLobbyMinigameBalloon_GetRankIconAnim(int param0)
{
    if (param0 >= 10) {
        return 2;
    }

    if (param0 >= 5) {
        return 1;
    }

    return 0;
}

static void WiFiLobbyMinigameBalloon_AdvanceRankIcons(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0;
    WiFiLobbyMinigameBalloonRankIcon *v1;

    for (v0 = 0; v0 < 5; v0++) {
        v1 = &param0->rankIcons[v0];

        if (v1->slot == 0) {
            v1->state = 3;
            ManagedSprite_SetAnim(v1->sprite, 6);
            return;
        }
    }
}

void WiFiLobbyMinigameBalloon_ApplyPlayerPalettes(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0;

    switch (param0->context->playerCount) {
    case 3:
        Bg_ChangeTilemapRectPalette(param0->bgConfig, 4, 0, 13, 12, 4, 3);
        Bg_ChangeTilemapRectPalette(param0->bgConfig, 4, 0x14, 13, 12, 4, 0);
        break;
    }
}

void WiFiLobbyMinigameBalloon_ApplyMainPlayerPalettes(WiFiLobbyMinigameBalloonGame *param0)
{
    u16 v0[4][3];
    int v1, v2;
    int v3 = 0;
    int v4, v5, v6, v7;
    u16 *v8, *v9;

    for (v2 = 0; v2 < param0->context->playerCount; v2++) {
        v4 = sMainPaletteSrcByPlayer[v2];

        for (v1 = 0; v1 < 3; v1++) {
            v0[v2][v1] = PaletteData_GetBufferIndexColor(param0->paletteData, 1, 1, v4 + v1);
        }
    }

    v7 = CommSys_CurNetId();

    for (v3 = 0; v3 < param0->context->playerCount; v3++) {
        if (param0->context->netIds[v3] == v7) {
            break;
        }
    }

    v8 = PaletteData_GetUnfadedBuffer(param0->paletteData, 1);
    v9 = PaletteData_GetFadedBuffer(param0->paletteData, 1);

    for (v1 = 0; v1 < param0->context->playerCount; v1++) {
        v4 = v1;
        v5 = sMainPaletteDestByPlayerCount[param0->context->playerCount][WiFiLobbyMinigameBalloon_GetPlayerSlot(param0, param0->context->netIds[v1])];

        for (v6 = 0; v6 < 3; v6++) {
            v8[v5 + v6] = v0[v4][v6];
            v9[v5 + v6] = v0[v4][v6];
        }
    }
}

void WiFiLobbyMinigameBalloon_ApplySubPlayerPalettes(WiFiLobbyMinigameBalloonGame *param0)
{
    u16 v0[4][16];
    int v1, v2;
    int v3 = 0;
    int v4, v5, v6, v7;
    u16 *v8, *v9;
    int v10 = SpriteManager_FindPlttResourceOffset(param0->spriteManager, 10006, NNS_G2D_VRAM_TYPE_2DSUB);

    for (v2 = 0; v2 < param0->context->playerCount; v2++) {
        v4 = sSubPaletteSrcByPlayer[v2];

        for (v1 = 0; v1 < 16; v1++) {
            v0[v2][v1] = PaletteData_GetBufferIndexColor(param0->paletteData, 3, 1, v10 * 16 + v4 + v1);
        }
    }

    v7 = CommSys_CurNetId();

    for (v3 = 0; v3 < param0->context->playerCount; v3++) {
        if (param0->context->netIds[v3] == v7) {
            break;
        }
    }

    v8 = PaletteData_GetUnfadedBuffer(param0->paletteData, 3);
    v9 = PaletteData_GetFadedBuffer(param0->paletteData, 3);

    for (v1 = 0; v1 < param0->context->playerCount; v1++) {
        v4 = v1;
        v5 = sSubPaletteDestByPlayerCount[param0->context->playerCount][WiFiLobbyMinigameBalloon_GetPlayerSlot(param0, param0->context->netIds[v1])] + v10 * 16;

        for (v6 = 0; v6 < 16; v6++) {
            v8[v5 + v6] = v0[v4][v6];
            v9[v5 + v6] = v0[v4][v6];
        }
    }
}

void WiFiLobbyMinigameBalloon_ApplySubPlayerPalettes2(WiFiLobbyMinigameBalloonGame *param0)
{
    u16 v0[4][1];
    int v1, v2;
    int v3 = 0;
    int v4, v5, v6, v7;
    u16 *v8, *v9;
    int v10 = SpriteManager_FindPlttResourceOffset(param0->spriteManager, 10006, NNS_G2D_VRAM_TYPE_2DSUB);

    for (v2 = 0; v2 < param0->context->playerCount; v2++) {
        v4 = sSubPalette2SrcByPlayer[v2];

        for (v1 = 0; v1 < 1; v1++) {
            v0[v2][v1] = PaletteData_GetBufferIndexColor(param0->paletteData, 3, 1, v10 * 16 + v4 + v1);
        }
    }

    v7 = CommSys_CurNetId();

    for (v3 = 0; v3 < param0->context->playerCount; v3++) {
        if (param0->context->netIds[v3] == v7) {
            break;
        }
    }

    v8 = PaletteData_GetUnfadedBuffer(param0->paletteData, 3);
    v9 = PaletteData_GetFadedBuffer(param0->paletteData, 3);

    for (v1 = 0; v1 < param0->context->playerCount; v1++) {
        v4 = v1;
        v5 = sSubPalette2DestByPlayerCount[param0->context->playerCount][WiFiLobbyMinigameBalloon_GetPlayerSlot(param0, param0->context->netIds[v1])] + v10 * 16;

        for (v6 = 0; v6 < 1; v6++) {
            v8[v5 + v6] = v0[v4][v6];
            v9[v5 + v6] = v0[v4][v6];
        }
    }
}

void WiFiLobbyMinigameBalloon_InitScorePacket(WiFiLobbyMinigameBalloonGame *param0, int param1, s32 param2, WiFiLobbyMinigameBalloonScorePacket *param3)
{
    MI_CpuClear8(param3, sizeof(WiFiLobbyMinigameBalloonScorePacket));

    param3->netId = CommSys_CurNetId();
    param3->balloonLevel = param1;
    param3->baseScore = param2;
    param3->score = param2;
    param3->multiplier = 0;
    param3->applied = 0;
}

BOOL WiFiLobbyMinigameBalloon_QueueScorePacket(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonScorePacket *param1)
{
    if (param0->scorePacketWriteIndex - param0->scorePacketReadIndex >= 8) {
        return 0;
    }

    param0->scorePackets[param0->scorePacketWriteIndex % 8] = *param1;
    param0->scorePacketWriteIndex++;
    return 1;
}

WiFiLobbyMinigameBalloonScorePacket *WiFiLobbyMinigameBalloon_DequeueScorePacket(WiFiLobbyMinigameBalloonGame *param0)
{
    WiFiLobbyMinigameBalloonScorePacket *v0;

    if (param0->scorePacketReadIndex >= param0->scorePacketWriteIndex) {
        return NULL;
    }

    v0 = &param0->scorePackets[param0->scorePacketReadIndex % 8];
    param0->scorePacketReadIndex++;
    return v0;
}

BOOL WiFiLobbyMinigameBalloon_ApplyScoreMultiplier(WiFiLobbyMinigameBalloonGame *param0, int param1)
{
    WiFiLobbyMinigameBalloonScorePacket *v0 = NULL;
    int v1, v2, v3;

    if ((param0->scorePacketReadIndex == param0->scorePacketWriteIndex) || (param1 == 0)) {
        return 0;
    }

    v2 = param0->scorePacketReadIndex % 8;
    v3 = param0->scorePacketWriteIndex % 8;

    if (v2 < v3) {
        for (v1 = v2; v1 < v3; v1++) {
            if (param0->scorePackets[v1].applied == 0) {
                v0 = &param0->scorePackets[v1];
                break;
            }
        }
    } else {
        for (v1 = v2; v1 < 8; v1++) {
            if (param0->scorePackets[v1].applied == 0) {
                v0 = &param0->scorePackets[v1];
                break;
            }
        }

        if (v0 == NULL) {
            for (v1 = 0; v1 < v3; v1++) {
                if (param0->scorePackets[v1].applied == 0) {
                    v0 = &param0->scorePackets[v1];
                    break;
                }
            }
        }
    }

    if (v0 == NULL) {
        GF_ASSERT(FALSE);
        return 0;
    }

    GF_ASSERT(v0->multiplier == 0);

    v0->multiplier = param1;
    v0->applied = 1;

    switch (param1) {
    case 1:
        v0->score = v0->baseScore * 2;
        break;
    case 2:
        v0->score = v0->baseScore / 2;
        break;
    case 3:
        v0->score = v0->baseScore * 3;
        break;
    }

    return 1;
}

void WiFiLobbyMinigameBalloon_CreatePlayerBalloonSprites(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloonSprites *param1)
{
    ManagedSprite *v0;
    SpriteTemplate v1;
    int v2;

    v1 = sPlayerBalloonSpriteTemplate;

    for (v2 = 0; v2 < 4; v2++) {
        param1->sprites[v2] = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v1);
        ManagedSprite_SetPositionXYWithSubscreenOffset(param1->sprites[v2], sPlayerPositions[v2].x, sPlayerPositions[v2].y, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetAnim(param1->sprites[v2], 31 + v2 / 2);
        Sprite_TickFrame(param1->sprites[v2]->sprite);
    }

    switch (param0->context->playerCount) {
    case 2:
        ManagedSprite_SetDrawFlag(param1->sprites[2], 0);
        ManagedSprite_SetDrawFlag(param1->sprites[3], 0);
        break;
    case 3:
        ManagedSprite_SetDrawFlag(param1->sprites[1], 0);
        break;
    }
}

void WiFiLobbyMinigameBalloon_FreePlayerBalloonSprites(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloonSprites *param1)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        Sprite_DeleteAndFreeResources(param1->sprites[v0]);
    }
}

void WiFiLobbyMinigameBalloon_CreatePlayerBalloons(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1)
{
    SpriteTemplate v0;
    int v1, v2;
    fx32 v3, v4;

    v0 = sPlayerBalloonSpriteTemplate2;

    for (v1 = 0; v1 < 3; v1++) {
        v3 = 256 / 2 + FX_Mul(CalcSineDegrees_FX32(param1->angle + param1->balloons[v1].angleOffset), 76);
        v4 = 196 / 2 + (-FX_Mul(CalcCosineDegrees_FX32(param1->angle + param1->balloons[v1].angleOffset), (64 + 4)));

        param1->balloons[v1].balloonSprite = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v0);
        ManagedSprite_SetPositionXYWithSubscreenOffset(param1->balloons[v1].balloonSprite, v3, v4 + -24, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetAnim(param1->balloons[v1].balloonSprite, sBalloonAnimByLevel[v1 + 1]);
        Sprite_TickFrame(param1->balloons[v1].balloonSprite->sprite);
        ManagedSprite_SetDrawFlag(param1->balloons[v1].balloonSprite, 0);

        param1->balloons[v1].shadowSprite = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &sBalloonShadowSpriteTemplate);
        ManagedSprite_SetPositionXYWithSubscreenOffset(param1->balloons[v1].shadowSprite, 0, 0, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetAnim(param1->balloons[v1].shadowSprite, 33);
        Sprite_TickFrame(param1->balloons[v1].shadowSprite->sprite);
        ManagedSprite_SetDrawFlag(param1->balloons[v1].shadowSprite, 0);

        param1->balloons[v1].highlightSprite = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &sBalloonHighlightSpriteTemplate);
        ManagedSprite_SetPositionXYWithSubscreenOffset(param1->balloons[v1].highlightSprite, v3, v4 + -24 + 24, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetExplicitOamMode(param1->balloons[v1].highlightSprite, GX_OAM_MODE_XLU);
        ManagedSprite_SetAffineOverwriteMode(param1->balloons[v1].highlightSprite, AFFINE_OVERWRITE_MODE_NORMAL);
        ManagedSprite_SetAffineScale(param1->balloons[v1].highlightSprite, 1.0f, 1.0f);
        ManagedSprite_SetAnim(param1->balloons[v1].highlightSprite, 34 + v1);
        Sprite_TickFrame(param1->balloons[v1].highlightSprite->sprite);
        ManagedSprite_SetDrawFlag(param1->balloons[v1].highlightSprite, 0);

        WiFiLobbyMinigameBalloon_CreateSparkles(param0, &param1->balloons[v1].sparkle);
    }

    ManagedSprite_SetDrawFlag(param1->balloons[0].balloonSprite, 1);
    ManagedSprite_SetDrawFlag(param1->balloons[0].highlightSprite, 1);
}

void WiFiLobbyMinigameBalloon_FreePlayerBalloons(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Sprite_DeleteAndFreeResources(param1->balloons[v0].balloonSprite);
        Sprite_DeleteAndFreeResources(param1->balloons[v0].shadowSprite);
        Sprite_DeleteAndFreeResources(param1->balloons[v0].highlightSprite);
        WiFiLobbyMinigameBalloon_FreeSparkles(param0, &param1->balloons[v0].sparkle);
    }
}

void WiFiLobbyMinigameBalloon_InitPlayerBalloons(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1)
{
    int v0;

    param1->angleStep = (360 << FX32_SHIFT) / 12 / sRotationSteps[param1->speedStage].framesPerStep;

    for (v0 = 0; v0 < 3; v0++) {
        param1->balloons[v0].angleOffset = (v0 * 90) << FX32_SHIFT;
        param1->balloons[v0].balloonLevel = 1 + v0;
    }

    param1->balloons[0].state = 2;
    param1->idle = 1;
}

void WiFiLobbyMinigameBalloon_UpdatePlayerBalloons(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1)
{
    int v0, v1, v2 = 0;

    if (param1->idle == 1) {
        return;
    }

    param1->frameCounter++;

    if (param1->pauseTimer == 0) {
        param1->angle += param1->angleStep;
        param1->rotationStep++;

        if (param1->rotationStep >= sRotationSteps[param1->speedStage].framesPerStep) {
            param1->rotationStep = 0;
            param1->slot++;
            param1->angle = (360 << FX32_SHIFT) / 12 * param1->slot;
            param1->pauseTimer = sRotationSteps[param1->speedStage].pauseFrames;
        }
    } else {
        param1->pauseTimer--;

        if (param1->pauseTimer == 0) {
            if (param1->slot >= 12) {
                param1->slot = 0;
                param1->speedStage++;

                if (param1->speedStage >= NELEMS(sRotationSteps)) {
                    param1->speedStage = NELEMS(sRotationSteps) - 1;
                }

                param1->angleStep = (360 << FX32_SHIFT) / 12 / sRotationSteps[param1->speedStage].framesPerStep;
            }
        }
    }

    if (param1->speedStage == 2 - 1) {
        for (v0 = 0; v0 < 2; v0++) {
            v2 += sRotationSteps[v0].framesPerStep * 12 + sRotationSteps[v0].pauseFrames * 12;
        }

        if (v2 - 15 == param1->frameCounter) {
            WiFiLobbyMinigameBalloon_SetPlayerBalloonState(&param1->balloons[1], 1);
        }
    } else if (param1->speedStage == 3 - 1) {
        for (v0 = 0; v0 < 3; v0++) {
            v2 += sRotationSteps[v0].framesPerStep * 12 + sRotationSteps[v0].pauseFrames * 12;
        }

        if (v2 - 15 == param1->frameCounter) {
            WiFiLobbyMinigameBalloon_SetPlayerBalloonState(&param1->balloons[2], 1);
        }
    }

    for (v0 = 0; v0 < 3; v0++) {
        WiFiLobbyMinigameBalloon_UpdatePlayerBalloon(param0, param1, &param1->balloons[v0]);
        WiFiLobbyMinigameBalloon_UpdateSparkles(param0, &param1->balloons[v0], &param1->balloons[v0].sparkle);
    }
}

static int WiFiLobbyMinigameBalloon_GetActivePlayerBalloon(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloon **param1)
{
    WiFiLobbyMinigameBalloonPlayerBalloons *v0 = &param0->playerBalloons;
    int v1;

    for (v1 = 0; v1 < 3; v1++) {
        if (v0->balloons[v1].active == 1) {
            *param1 = &v0->balloons[v1];
            return v0->balloons[v1].balloonLevel;
        }
    }

    *param1 = NULL;
    return 0;
}

static void WiFiLobbyMinigameBalloon_SetPlayerBalloonState(WiFiLobbyMinigameBalloonPlayerBalloon *param0, int param1)
{
    param0->state = param1;
    param0->phase = 0;
    param0->timer = 0;
    param0->popDuration = 0;
    param0->active = 0;
}

static void WiFiLobbyMinigameBalloon_UpdatePlayerBalloon(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1, WiFiLobbyMinigameBalloonPlayerBalloon *param2)
{
    sPlayerBalloonStateTable[param2->state](param0, param1, param2);
}

static int WiFiLobbyMinigameBalloon_PlayerBalloonStateIdle(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1, WiFiLobbyMinigameBalloonPlayerBalloon *param2)
{
    param2->active = 0;
    return 1;
}

static int WiFiLobbyMinigameBalloon_PlayerBalloonStateEnter(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1, WiFiLobbyMinigameBalloonPlayerBalloon *param2)
{
    s16 v0, v1, v2, v3, v4, v5;
    fx32 v6;
    int v7 = 0;
    fx32 v8;
    f32 v9;

    v2 = 0;
    v3 = 0;
    v0 = param2->startX;
    v1 = param2->startY;

    switch (param2->phase) {
    case 0:
        ManagedSprite_SetDrawFlag(param2->balloonSprite, 1);
        ManagedSprite_SetDrawFlag(param2->highlightSprite, 1);
        Sprite_GetPositionXYWithSubscreenOffset2(param2->balloonSprite, &v0, &v1, ((192 + 160) << FX32_SHIFT));
        param2->startX = v0;
        param2->startY = v1;
        param2->phase++;

    case 1:
        switch (param2->angleOffset) {
        case 0:
            v4 = param2->startY - -32;
            v3 = param2->timer * v4 / 15;
            v1 = -32 + v3;
            break;
        case 90 << FX32_SHIFT:
            v5 = param2->startX - (256 + 32);
            v2 = param2->timer * v5 / 15;
            v0 = (256 + 32) + v2;
            break;
        case 180 << FX32_SHIFT:
            v4 = param2->startY - (196 + 32);
            v3 = param2->timer * v4 / 15;
            v1 = (196 + 32) + v3;
            break;
        case 270 << FX32_SHIFT:
            v5 = param2->startX - -32;
            v2 = param2->timer * v5 / 15;
            v0 = -32 + v2;
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }
        if (param2->timer >= 15) {
            ManagedSprite_SetPositionXYWithSubscreenOffset(param2->balloonSprite, param2->startX, param2->startY, ((192 + 160) << FX32_SHIFT));
            ManagedSprite_SetPositionXYWithSubscreenOffset(param2->highlightSprite, param2->startX, param2->startY + 24, ((192 + 160) << FX32_SHIFT));
            WiFiLobbyMinigameBalloon_SetPlayerBalloonState(param2, 2);
            WiFiLobbyMinigameBalloon_StartSparkles(param0, param2, &param2->sparkle);

            return 1;
        }

        v6 = ((180 * param2->timer) << FX32_SHIFT) / 15;
        v7 = -(FX_Mul(CalcSineDegrees_FX32(v6), (24 << FX32_SHIFT))) / FX32_ONE;

        ManagedSprite_SetPositionXYWithSubscreenOffset(param2->balloonSprite, v0, v1 + v7, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetPositionXYWithSubscreenOffset(param2->highlightSprite, v0, v1 + 24, ((192 + 160) << FX32_SHIFT));

        v8 = FX32_ONE - (FX32_ONE * (-v7 / 3) / ((24 << FX32_SHIFT) >> FX32_SHIFT));
        v9 = FX_FX32_TO_F32(v8);

        ManagedSprite_SetAffineScale(param2->highlightSprite, v9, v9);
        break;
    }

    param2->timer++;
    return 1;
}

static int WiFiLobbyMinigameBalloon_PlayerBalloonStateOrbit(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1, WiFiLobbyMinigameBalloonPlayerBalloon *param2)
{
    fx32 v0, v1;
    fx32 v2;
    int v3 = 0;
    fx32 v4;
    f32 v5;

    if (param1->rotationStep > 0) {
        ManagedSprite_TickNFrames(param2->balloonSprite, ((8 + 8 + 12 + 8 + 8) << FX32_SHIFT) / sRotationSteps[param1->speedStage].framesPerStep);
    } else {
        ManagedSprite_SetAnimationFrame(param2->balloonSprite, 0);
    }

    v2 = ((180 * param1->rotationStep) << FX32_SHIFT) / sRotationSteps[param1->speedStage].framesPerStep;
    v3 = -(FX_Mul(CalcSineDegrees_FX32(v2), (12 << FX32_SHIFT))) / FX32_ONE;
    v0 = 256 / 2 + FX_Mul(CalcSineDegrees_FX32(param1->angle + param2->angleOffset), 76);
    v1 = 196 / 2 + (-FX_Mul(CalcCosineDegrees_FX32(param1->angle + param2->angleOffset), (64 + 4)));

    ManagedSprite_SetPositionXYWithSubscreenOffset(param2->balloonSprite, v0, v1 + -24 + v3, ((192 + 160) << FX32_SHIFT));
    ManagedSprite_SetPositionXYWithSubscreenOffset(param2->highlightSprite, v0, v1 + -24 + 24, ((192 + 160) << FX32_SHIFT));

    v4 = FX32_ONE - (FX32_ONE * (-v3 / 3) / ((12 << FX32_SHIFT) >> FX32_SHIFT));
    v5 = FX_FX32_TO_F32(v4);

    ManagedSprite_SetAffineScale(param2->highlightSprite, v5, v5);

    if (param1->rotationStep == sRotationSteps[param1->speedStage].framesPerStep - 1) {
        WiFiLobbyMinigameBalloon_StartSparkles(param0, param2, &param2->sparkle);
    }

    if (((param1->angle + param2->angleOffset) >> FX32_SHIFT) % 360 == 180) {
        param2->active = 1;
    } else {
        param2->active = 0;
    }

    return 1;
}

static int WiFiLobbyMinigameBalloon_PlayerBalloonStatePop(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloons *param1, WiFiLobbyMinigameBalloonPlayerBalloon *param2)
{
    s16 v0, v1;
    int v2, v3;
    s16 v4, v5, v6, v7;
    fx32 v8;
    int v9 = 0;

    switch (param2->phase) {
    case 0:
        Sound_PlayEffect(SEQ_SE_PL_BALLOON05_sseq);
        Sprite_GetPositionXYWithSubscreenOffset2(param2->balloonSprite, &v0, &v1, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetPositionXYWithSubscreenOffset(param2->shadowSprite, v0, v1 + -32, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetAnim(param2->shadowSprite, 33);
        ManagedSprite_SetDrawFlag(param2->shadowSprite, 1);
        ManagedSprite_SetAnim(param2->balloonSprite, sBalloonAnimByLevel[param2->balloonLevel] + 2);

        param2->timer = sRotationSteps[param1->speedStage].popFrames;
        param2->timerThreshold = sRotationSteps[param1->speedStage].popFrames / 2;
        param2->phase++;
        break;
    case 1:
        if (param2->timer == param2->timerThreshold) {
            ManagedSprite_SetAnim(param2->balloonSprite, sBalloonAnimByLevel[param2->balloonLevel] + 1);
            ManagedSprite_SetDrawFlag(param2->shadowSprite, 0);
            ManagedSprite_TickNFrames(param2->shadowSprite, (4 * FX32_ONE));
        }

        if (param2->timer == 0) {
            ManagedSprite_SetDrawFlag(param2->shadowSprite, 0);
            ManagedSprite_SetAnim(param2->balloonSprite, sBalloonAnimByLevel[param2->balloonLevel] + 0);
            param2->phase++;
            break;
        }
        param2->timer--;
        break;
    case 2:
        v2 = 0;

        if (param1->pauseTimer == 0) {
            v2 += sRotationSteps[param1->speedStage].framesPerStep - param1->rotationStep;
            v2 += sRotationSteps[param1->speedStage].pauseFrames;
            v2 += sRotationSteps[param1->speedStage].framesPerStep;
            v3 = param1->slot + 2;
        } else {
            v2 += param1->pauseTimer;

            if (param1->slot >= 12) {
                v2 += sRotationSteps[param1->speedStage + 1].framesPerStep;
                v3 = 1;
            } else {
                v2 += sRotationSteps[param1->speedStage].framesPerStep;
                v3 = param1->slot + 1;

                if (v3 >= 12) {
                    (void)0;
                }
            }
        }

        v3 += param2->angleOffset / ((360 / 12) << FX32_SHIFT);
        v3 %= 12;
        v4 = 256 / 2 + FX_Mul(CalcSineDegrees_FX32((360 << FX32_SHIFT) / 12 * v3), 76);
        v5 = 196 / 2 + (-FX_Mul(CalcCosineDegrees_FX32((360 << FX32_SHIFT) / 12 * v3), (64 + 4)));

        Sprite_GetPositionXYWithSubscreenOffset2(param2->balloonSprite, &v6, &v7, ((192 + 160) << FX32_SHIFT));

        v7 -= -24;

        param2->velocityX = (v4 - v6) * FX32_ONE / v2;
        param2->velocityY = (v5 - v7) * FX32_ONE / v2;
        param2->x = v6 * FX32_ONE;
        param2->y = v7 * FX32_ONE;
        param2->timer = v2;
        param2->popDuration = v2;
        param2->phase++;

    case 3:
        param2->x += param2->velocityX;
        param2->y += param2->velocityY;

        v8 = ((180 * param2->timer) << FX32_SHIFT) / param2->popDuration;
        v9 = -(FX_Mul(CalcSineDegrees_FX32(v8), (12 << FX32_SHIFT))) / FX32_ONE;

        ManagedSprite_SetPositionXYWithSubscreenOffset(param2->balloonSprite, param2->x / FX32_ONE, param2->y / FX32_ONE + -24 + v9, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_TickNFrames(param2->balloonSprite, ((8 + 8 + 12 + 8 + 8) << FX32_SHIFT) / param2->popDuration);
        ManagedSprite_SetPositionXYWithSubscreenOffset(param2->highlightSprite, param2->x / FX32_ONE, param2->y / FX32_ONE + -24 + 24, ((192 + 160) << FX32_SHIFT));

        param2->timer--;

        if (param2->timer <= 0) {
            ManagedSprite_SetAnim(param2->balloonSprite, sBalloonAnimByLevel[param2->balloonLevel] + 0);
            ManagedSprite_SetAnimationFrame(param2->balloonSprite, 0);
            WiFiLobbyMinigameBalloon_SetPlayerBalloonState(param2, 2);
            return 1;
        }

        break;
    }

    return 1;
}

void WiFiLobbyMinigameBalloon_CreateOpponentBalloons(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonOpponentBalloons *param1)
{
    SpriteTemplate v0;
    int v1;

    v0 = sPlayerBalloonSpriteTemplate2;

    for (v1 = 0; v1 < 3; v1++) {
        param1->balloons[v1].balloonSprite = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v0);

        ManagedSprite_SetPositionXYWithSubscreenOffset(param1->balloons[v1].balloonSprite, 0, 0, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetDrawFlag(param1->balloons[v1].balloonSprite, 0);

        param1->balloons[v1].shadowSprite = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &sBalloonShadowSpriteTemplate);

        ManagedSprite_SetPositionXYWithSubscreenOffset(param1->balloons[v1].shadowSprite, 0, 0, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetAnim(param1->balloons[v1].shadowSprite, 33);
        Sprite_TickFrame(param1->balloons[v1].shadowSprite->sprite);
        ManagedSprite_SetDrawFlag(param1->balloons[v1].shadowSprite, 0);
    }
}

void WiFiLobbyMinigameBalloon_FreeOpponentBalloons(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonOpponentBalloons *param1)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Sprite_DeleteAndFreeResources(param1->balloons[v0].balloonSprite);
        Sprite_DeleteAndFreeResources(param1->balloons[v0].shadowSprite);
    }
}

void WiFiLobbyMinigameBalloon_SpawnOpponentBalloon(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonOpponentBalloons *param1, int param2, int param3, int param4)
{
    int v0, v1, v2, v3;
    WiFiLobbyMinigameBalloonOpponentBalloon *v4 = NULL;

    if ((param2 == 0) || (param3 == CommSys_CurNetId())) {
        return;
    }

    for (v0 = 0; v0 < 3; v0++) {
        if (param1->balloons[v0].active == 0) {
            v4 = &param1->balloons[v0];
            break;
        }
    }

    if (v4 == NULL) {
        return;
    }

    v2 = WiFiLobbyMinigameBalloon_GetPlayerSlot(param0, param3);
    v1 = sOpponentPaletteByPlayerCount[param0->context->playerCount][v2];

    ManagedSprite_SetExplicitPalette(v4->balloonSprite, v1);
    ManagedSprite_SetAnim(v4->balloonSprite, sBalloonAnimByLevel[param2] + 0);

    v3 = sOpponentPositionByPlayerCount[param0->context->playerCount][v2];
    v4->targetY = sPlayerPositions[v3].y + -24;

    ManagedSprite_SetPositionXYWithSubscreenOffset(v4->balloonSprite, sPlayerPositions[v3].x, v4->targetY + -96, ((192 + 160) << FX32_SHIFT));
    Sprite_TickFrame(v4->balloonSprite->sprite);

    v4->balloonLevel = param2;
    v4->delay = param4 - (MATH_ABS(-96) * FX32_ONE) / 0x8000;
    v4->state = 0;
    v4->active = 1;
}

void WiFiLobbyMinigameBalloon_UpdateOpponentBalloons(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonOpponentBalloons *param1)
{
    int v0;
    WiFiLobbyMinigameBalloonOpponentBalloon *v1;

    for (v0 = 0; v0 < 3; v0++) {
        if (param1->balloons[v0].active == 1) {
            v1 = &param1->balloons[v0];
            WiFiLobbyMinigameBalloon_UpdateOpponentBalloon(param1, v1);
        }
    }
}

static BOOL WiFiLobbyMinigameBalloon_UpdateOpponentBalloon(WiFiLobbyMinigameBalloonOpponentBalloons *param0, WiFiLobbyMinigameBalloonOpponentBalloon *param1)
{
    s16 v0, v1;

    switch (param1->state) {
    case 0:
        Sprite_GetPositionXYWithSubscreenOffset2(param1->balloonSprite, &v0, &v1, ((192 + 160) << FX32_SHIFT));
        param1->x = v0 * FX32_ONE;
        param1->y = v1 * FX32_ONE;
        param1->state++;
    case 1:
        if (param1->delay > 0) {
            param1->delay--;
            break;
        }

        ManagedSprite_SetDrawFlag(param1->balloonSprite, 1);
        param1->y += 0x8000;

        if ((param1->y / FX32_ONE) >= param1->targetY) {
            param1->y = param1->targetY * FX32_ONE;
            param1->state++;
        }
        break;
    case 2:
        Sprite_GetPositionXYWithSubscreenOffset2(param1->balloonSprite, &v0, &v1, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetPositionXYWithSubscreenOffset(param1->shadowSprite, v0, v1 + -32, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetAnim(param1->shadowSprite, 33);
        ManagedSprite_SetDrawFlag(param1->shadowSprite, 1);
        Sound_PlayEffect(SEQ_SE_PL_BALLOON05_sseq);
        ManagedSprite_SetAnim(param1->balloonSprite, sBalloonAnimByLevel[param1->balloonLevel] + 2);

        param1->timer = 8;
        param1->state++;
        break;
    case 3:
        param1->timer--;

        if (param1->timer == 3) {
            ManagedSprite_TickNFrames(param1->shadowSprite, (4 * FX32_ONE));
        }

        if (param1->timer == 0) {
            ManagedSprite_SetDrawFlag(param1->shadowSprite, 0);
            ManagedSprite_SetAnim(param1->balloonSprite, sBalloonAnimByLevel[param1->balloonLevel] + 0);
            param1->state++;
        }
        break;
    case 4:
        param1->y -= 0x8000;

        if ((param1->y / FX32_ONE) <= param1->targetY + -96) {
            ManagedSprite_SetDrawFlag(param1->balloonSprite, 0);
            param1->state = 0;
            param1->active = 0;
            return 0;
        }
        break;
    }

    ManagedSprite_SetPositionXYWithSubscreenOffset(param1->balloonSprite, param1->x / FX32_ONE, param1->y / FX32_ONE, ((192 + 160) << FX32_SHIFT));
    return 1;
}

void WiFiLobbyMinigameBalloon_CreateTextOAM(BgConfig *param0, SpriteManager *param1, FontOAMManager *param2, WiFiLobbyMinigameBalloonTextOAM *param3, const String *param4, enum Font param5, TextColor param6, int param7, int param8, int param9, int param10, int param11, int param12, int param13, int param14)
{
    FontOAMTemplate v0;
    Window v1;
    CharTransferAllocation v2;
    int v3;
    FontOAM *v4;
    int v5, v6;
    int v7 = 0;

    {
        v5 = Font_CalcMaxLineWidth(param5, param4, v7);
        v6 = v5 / 8;

        if (FX_ModS32(v5, 8) != 0) {
            v6++;
        }
    }

    {
        Window_Init(&v1);
        Window_AddToTopLeftCorner(param0, &v1, v6, param14, 0, 0);
        Text_AddPrinterWithParamsColorAndSpacing(&v1, param5, param4, 0, 0, TEXT_SPEED_NO_TRANSFER, param6, v7, 0, NULL);
    }

    v3 = FontOAM_GetWindowSize(&v1, NNS_G2D_VRAM_TYPE_2DMAIN, HEAP_ID_110);
    CharTransfer_AllocRange(v3, 1, NNS_G2D_VRAM_TYPE_2DMAIN, &v2);

    if (param11 == 1) {
        param9 -= v5 / 2;
    }

    param10 += 0;

    v0.fontOAMManager = param2;
    v0.window = &v1;
    v0.spriteList = SpriteManager_GetSpriteList(param1);
    v0.paletteProxy = SpriteManager_FindPlttResourceProxy(param1, param8);
    v0.parentSprite = NULL;
    v0.charOffset = v2.offset;
    v0.x = param9;
    v0.y = param10;
    v0.resourcePriority = param12;
    v0.spritePriority = param13;
    v0.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v0.heapID = HEAP_ID_110;

    v4 = FontOAM_New(&v0);

    if (param7 != 0) {
        FontOAM_SetExplicitPaletteOffset(v4, param7);
    }

    FontOAM_SetXY(v4, param9, param10);
    Window_Remove(&v1);

    param3->fontOAM = v4;
    param3->charTransfer = v2;
    param3->width = v5;
}

void WiFiLobbyMinigameBalloon_FreeTextOAM(WiFiLobbyMinigameBalloonTextOAM *param0)
{
    FontOAM_Free(param0->fontOAM);
    CharTransfer_ClearRange(&param0->charTransfer);
    param0->fontOAM = NULL;
}

void WiFiLobbyMinigameBalloon_LayoutScoreDigits(WiFiLobbyMinigameBalloonScoreDisplay *param0)
{
    int v0, v1;
    int v2 = 16 * 5;
    int v3, v4, v5, v6;

    for (v0 = 0; v0 < 6; v0++) {
        v1 = param0->currentDigit[v0];

        if (v1 < v2 - 16) {
            v5 = v2 - 16 - v1;
            v6 = v5 - v2;
        } else if (v1 < 160 - 32) {
            v6 = v2 - 16 - (v1 - v2);
            v5 = v6 - v2;
        } else {
            v5 = v2 - 16 - (v1 - 160);
            v6 = v5 - v2;
        }

        FontOAM_GetXY(param0->digitReel[v0][0].fontOAM, &v3, &v4);
        FontOAM_SetXY(param0->digitReel[v0][0].fontOAM, v3, 168 - v5);
        FontOAM_SetXY(param0->digitReel[v0][1].fontOAM, v3, 168 - v6);
    }
}

void WiFiLobbyMinigameBalloon_UpdateScoreDisplay(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonScoreDisplay *param1)
{
    int v0;
    BOOL v1;

    if (param1->rollPause > 0) {
        param1->rollPause--;
        return;
    }

    switch (param1->rollState) {
    case 0:
        if (WiFiLobbyMinigameBalloon_ScoreRollDone(param1) == 1) {
            WiFiLobbyMinigameBalloon_StartScoreRoll(param1);
            break;
        } else {
            param1->rollState++;
        }

    case 1:
        v1 = WiFiLobbyMinigameBalloon_AdvanceScoreRoll(param1);
        WiFiLobbyMinigameBalloon_LayoutScoreDigits(param1);

        if (v1 == 1) {
            param1->rollPause = 15;
            param1->rollState--;
        }
        break;
    }
}

void WiFiLobbyMinigameBalloon_SetScoreDigits(WiFiLobbyMinigameBalloonScoreDisplay *param0, int param1)
{
    int v0, v1, v2;

    v1 = 100000;
    GF_ASSERT(6 == 6);

    for (v0 = 0; v0 < 6; v0++) {
        v2 = param1 / v1;
        param0->newDigits[v0] = v2 * 16;
        param1 -= v2 * v1;
        v1 /= 10;
    }
}

static void WiFiLobbyMinigameBalloon_StartScoreRoll(WiFiLobbyMinigameBalloonScoreDisplay *param0)
{
    int v0;

    for (v0 = 0; v0 < 6; v0++) {
        param0->targetDigit[v0] = param0->newDigits[v0];
        param0->digitDelay[v0] = 2 * (6 - v0 - 1);
        param0->digitState[v0] = 0;
    }

    param0->settledCount = 0;
}

static BOOL WiFiLobbyMinigameBalloon_ScoreRollDone(WiFiLobbyMinigameBalloonScoreDisplay *param0)
{
    int v0;

    for (v0 = 0; v0 < 6; v0++) {
        if (param0->currentDigit[v0] != param0->targetDigit[v0]) {
            return 0;
        }
    }

    return 1;
}

static BOOL WiFiLobbyMinigameBalloon_AdvanceScoreRoll(WiFiLobbyMinigameBalloonScoreDisplay *param0)
{
    int v0;
    int v1 = 6 - 1;
    int v2, v3, v4, v5;

    if (param0->settledCount > 6) {
        return 1;
    }

    v3 = 0;
    v4 = 0;

    for (v0 = 0; v0 < 6; v0++, v1--) {
        v3 = v4;

        if (param0->digitDelay[v1] > 0) {
            param0->digitDelay[v1]--;
            v4 = 0;
            continue;
        }

        if ((param0->digitState[v1] > 1) && (param0->currentDigit[v1] == param0->targetDigit[v1])) {
            v4 = 1;
            continue;
        }

        v4 = 0;
        v2 = param0->currentDigit[v1];
        param0->currentDigit[v1] += 23;
        v5 = param0->targetDigit[v1] + 16 * 10;

        if (((v2 <= param0->targetDigit[v1]) && (param0->currentDigit[v1] >= param0->targetDigit[v1])) || ((v2 <= v5) && (param0->currentDigit[v1] >= v5))) {
            if (param0->digitState[v1] < 1) {
                param0->digitState[v1]++;
            } else if ((v1 == 6 - 1) || (v3 == 1)) {
                param0->digitState[v1]++;
                param0->currentDigit[v1] = param0->targetDigit[v1];
                param0->settledCount++;

                if (param0->settledCount >= 6) {
                    return 1;
                }
            }
        }

        param0->currentDigit[v1] %= 10 * 16;
    }

    return 0;
}

ManagedSprite *WiFiLobbyMinigameBalloon_CreateScoreSprite(WiFiLobbyMinigameBalloonGame *param0)
{
    ManagedSprite *v0 = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &sScoreSpriteTemplate);
    Sprite_TickFrame(v0->sprite);
    return v0;
}

void WiFiLobbyMinigameBalloon_CreateScoreDigits(WiFiLobbyMinigameBalloonGame *param0)
{
    String *v0;
    int v1, v2, v3;
    u32 v4 = param0->localScore;
    for (v1 = 6 - 1; v1 >= 0; v1--) {
        GF_ASSERT(param0->scoreDisplay.scoreDigits[v1].fontOAM == NULL);
        v0 = MessageLoader_GetNewString(param0->messageLoader, 4 + (v4 % 10));
        v4 /= 10;
        FontOAM_GetXY(param0->scoreDisplay.digitReel[v1][0].fontOAM, &v2, &v3);
        WiFiLobbyMinigameBalloon_CreateTextOAM(param0->bgConfig, param0->spriteManager, param0->fontOAMManager, &param0->scoreDisplay.scoreDigits[v1], v0, FONT_SYSTEM, TEXT_COLOR(14, 15, 0), 0, 10003, v2, 168, 0, 1, 12, 2 * 1);
        String_Free(v0);
    }
}

void WiFiLobbyMinigameBalloon_FreeScoreDigits(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0;

    for (v0 = 0; v0 < 6; v0++) {
        if (param0->scoreDisplay.scoreDigits[v0].fontOAM != NULL) {
            WiFiLobbyMinigameBalloon_FreeTextOAM(&param0->scoreDisplay.scoreDigits[v0]);
        }
    }
}

void WiFiLobbyMinigameBalloon_FreeScoreSprite(WiFiLobbyMinigameBalloonGame *param0, ManagedSprite *param1)
{
    Sprite_DeleteAndFreeResources(param1);
}

ManagedSprite *WiFiLobbyMinigameBalloon_CreateIntroBannerSprite(WiFiLobbyMinigameBalloonGame *param0)
{
    ManagedSprite *v0 = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &sIntroBannerSpriteTemplate);

    ManagedSprite_SetDrawFlag(v0, 0);
    Sprite_TickFrame(v0->sprite);

    return v0;
}

void WiFiLobbyMinigameBalloon_FreeIntroBannerSprite(WiFiLobbyMinigameBalloonGame *param0, ManagedSprite *param1)
{
    Sprite_DeleteAndFreeResources(param1);
}

BOOL WiFiLobbyMinigameBalloon_UpdateIntroBanner(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonIntroBanner *param1)
{
    switch (param1->state) {
    case 0:
    case 5:
        ManagedSprite_SetPositionXYWithSubscreenOffset(param1->sprite, 128, 16, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetDrawFlag(param1->sprite, 1);
        param1->state++;
        break;
    case 1:
    case 6:
        param1->timer++;

        if (param1->timer > 15) {
            param1->timer = 0;
            param1->touchHeld = 1;
            param1->touchPressed = 1;
            param1->x = 128;
            param1->y = 32;
            param1->state++;
        }

        break;
    case 2:
    case 7:
        param1->touchPressed = 0;
        param1->y += 6;

        ManagedSprite_OffsetPositionXY(param1->sprite, 0, 6);

        if (param1->y > 192 - 96) {
            param1->state++;
        }

        break;
    case 3:
    case 8:
        param1->touchHeld = 0;
        ManagedSprite_SetDrawFlag(param1->sprite, 0);
        param1->state++;

    case 4:
    case 9:
        param1->timer++;

        if (param1->timer > 30) {
            param1->timer = 0;
            param1->state++;
        }

        break;
    case 10:
        return 1;
    }

    return 0;
}

static void WiFiLobbyMinigameBalloon_CreateSparkles(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonSparkle *param1)
{
    ManagedSprite *v0;
    int v1;

    for (v1 = 0; v1 < 2; v1++) {
        v0 = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &sSparkleSpriteTemplate);

        ManagedSprite_SetAnim(v0, 27);
        ManagedSprite_SetExplicitOamMode(v0, GX_OAM_MODE_XLU);
        ManagedSprite_SetDrawFlag(v0, 0);
        Sprite_TickFrame(v0->sprite);

        param1->sprites[v1] = v0;
    }
}

static void WiFiLobbyMinigameBalloon_FreeSparkles(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonSparkle *param1)
{
    int v0;

    for (v0 = 0; v0 < 2; v0++) {
        Sprite_DeleteAndFreeResources(param1->sprites[v0]);
    }
}

static void WiFiLobbyMinigameBalloon_StartSparkles(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloon *param1, WiFiLobbyMinigameBalloonSparkle *param2)
{
    s16 v0, v1;
    int v2;

    Sprite_GetPositionXYWithSubscreenOffset2(param1->balloonSprite, &v0, &v1, ((192 + 160) << FX32_SHIFT));

    for (v2 = 0; v2 < 2; v2++) {
        ManagedSprite_SetPositionXYWithSubscreenOffset(param2->sprites[v2], v0, v1 + 28, ((192 + 160) << FX32_SHIFT));
        ManagedSprite_SetAnim(param2->sprites[v2], 27);
        ManagedSprite_SetExplicitOamMode(param2->sprites[v2], GX_OAM_MODE_XLU);
        ManagedSprite_SetDrawFlag(param2->sprites[v2], 1);

        param2->offsetX[v2] = LCRNG_Next() % 0x1000 + 0x1000;
        param2->offsetY[v2] = LCRNG_Next() % 0x400 + 0x400;

        if (v2 & 1) {
            param2->offsetX[v2] *= -1;
        }
    }

    param2->timer = 0;
    param2->state = 1;
}

static void WiFiLobbyMinigameBalloon_UpdateSparkles(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPlayerBalloon *param1, WiFiLobbyMinigameBalloonSparkle *param2)
{
    int v0;

    switch (param2->state) {
    case 0:
        break;
    case 1:
        for (v0 = 0; v0 < 2; v0++) {
            ManagedSprite_OffsetPositionFxXY(param2->sprites[v0], param2->offsetX[v0], -param2->offsetY[v0]);
            Sprite_TickFrame(param2->sprites[v0]->sprite);
        }

        param2->timer++;

        if (param2->timer > 8) {
            for (v0 = 0; v0 < 2; v0++) {
                ManagedSprite_SetDrawFlag(param2->sprites[v0], 0);
            }

            param2->state = 0;
        }

        break;
    }
}
