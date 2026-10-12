#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene.h"

#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"

#include "nintendo_wfc/main.h"
#include "wifi_lobby_minigame/wifi_lobby_minigame.h"
#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02260440.h"
#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02261870.h"
#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02262A44.h"
#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02262A8C.h"
#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_0226432C.h"
#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02266FEC.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226048C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02260494.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02260498.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226139C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262A8C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226501C.h"

#include "bg_window.h"
#include "camera.h"
#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "easy3d_object.h"
#include "g3d_pipeline.h"
#include "gx_layers.h"
#include "heap.h"
#include "math_util.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "palette.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "sprite_util.h"
#include "system.h"
#include "touch_pad.h"
#include "comm_tool.h"
#include "vram_transfer.h"

static void WiFiLobbyMinigameManene_InitResources(WiFiLobbyMinigameManeneApp *param0);
static void WiFiLobbyMinigameManene_InitBackgrounds(BgConfig *param0);
static void WiFiLobbyMinigameManene_InitSpriteSystem(WiFiLobbyMinigameManeneApp *param0);
static BOOL WiFiLobbyMinigameManene_StartFade(int param0);
static void WiFiLobbyMinigameManene_AdvanceState(WiFiLobbyMinigameManeneApp *param0, BOOL param1, int param2, int *param3);
static void WiFiLobbyMinigameManene_VBlankCallback(void *param0);
static void WiFiLobbyMinigameManene_FreeResources(WiFiLobbyMinigameManeneApp *param0);
static void WiFiLobbyMinigameManene_ResetRound(WiFiLobbyMinigameManeneApp *param0);
static u32 WiFiLobbyMinigameManene_CheckDisconnect(WiFiLobbyMinigameManeneApp *param0);

static void WiFiLobbyMinigameManene_InitGame(WiFiLobbyMinigameManeneApp *param0)
{
    param0->gameSeed = LCRNG_GetSeed();

    WiFiLobbyMinigameManene_InitResources(param0);
    SetVBlankCallback(WiFiLobbyMinigameManene_VBlankCallback, param0);
    DisableHBlank();
    VramTransfer_New(32, HEAP_ID_106);
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_128K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);
    NetworkIcon_Init();

    NNSG2dPaletteData *v0;
    void *v1 = NetworkIcon_GetPalette(HEAP_ID_106);

    NNS_G2dGetUnpackedPaletteData(v1, &v0);
    PaletteData_LoadBuffer(param0->resources.paletteData, v0->pRawData, PLTTBUF_MAIN_OBJ, PLTT_DEST(14), PALETTE_SIZE_BYTES);
    Heap_Free(v1);

    int v2 = CommInfo_CountReceived();

    param0->netId = CommSys_CurNetId();
    WiFiLobbyMinigameManene_InitCommCmd(param0);

    if (WiFiLobbyMinigameManene_IsHost(param0) == 1) {
        param0->countdown = WiFiLobbyMinigameManene_CreateCountdown(v2, &param0->resources);
    }

    param0->game = WiFiLobbyMinigameManene_CreateGame(v2, param0->netId, &param0->resources);
    param0->game->introScreenResult = param0->seedData.introResult;
    param0->game->gameSeed = param0->gameSeed;

    u32 v3;

    EnableTouchPad();
    v3 = InitializeTouchPad(4);

    WiFiLobbyMinigameManene_LoadBackgroundGraphics(param0);
    WiFiLobbyMinigameManene_LoadSpriteResources(param0);
    WiFiLobbyMinigameManene_CreatePlayerRowSprites(param0, param0->game);
    WiFiLobbyMinigameManene_CreatePlayerSprites(param0->game);
    WiFiLobbyMinigameManene_CreateBackgroundSprites(param0->game);
    WiFiLobbyMinigameManene_CreateResultSprites(param0->game);
    WiFiLobbyMinigameManene_CreateBallSprite(param0->game);
    WiFiLobbyMinigameManene_LoadPlayerPalettes(param0, WiFiLobbyMinigameManene_GetPlayerIndex(param0, param0->netId));

    {
        {
            int v4;
            int v5[][2] = {
                { 44, 43 },
                { 46, 45 },
                { 48, 47 },
                { 50, 49 },
                { 44, 43 },
                { 46, 45 },
                { 48, 47 },
                { 50, 49 },
                { 44, 43 },
                { 46, 45 },
                { 48, 47 },
                { 50, 49 },
                { 44, 43 },
                { 46, 45 },
                { 48, 47 },
                { 50, 49 },
            };

            for (v4 = 0; v4 < 8; v4++) {
                WiFiLobbyMinigameManene_Load3DModel(&param0->game->decorationObjects[v4], param0->resources.maneneNarc, v5[v4][0]);
                WiFiLobbyMinigameManene_Init3DObject(&param0->game->decorationObjects[v4], param0->seedData.introResult);

                Easy3DAnim_LoadFrom(&param0->game->decorationObjects[v4].anims[0], &param0->game->decorationObjects[v4].model, param0->resources.maneneNarc, v5[v4][1], 106, &param0->resources.g3dAllocator);
                Easy3DObject_AddAnim(&param0->game->decorationObjects[v4].object, &param0->game->decorationObjects[v4].anims[0]);
                Easy3DAnim_SetFrame(&param0->game->decorationObjects[v4].anims[0], 0);
                Easy3DObject_SetVisible(&param0->game->decorationObjects[v4].object, 0);

                {
                    int v6 = 5;

                    if (param0->seedData.introResult) {
                        v6 = 5;
                    }

                    if (v4 % 2) {
                        param0->game->decorationObjects[v4].position.x += FX32_CONST(v4 * 5);
                    } else {
                        param0->game->decorationObjects[v4].position.x -= FX32_CONST(v4 * 5);
                    }

                    if (v4 < 8) {
                        param0->game->decorationObjects[v4].position.z += FX32_CONST((v4 + 1) * v6);
                    } else {
                        param0->game->decorationObjects[v4].position.z -= FX32_CONST(v4 * 5);
                    }
                }
            }
        }

        WiFiLobbyMinigameManene_Load3DModel(&param0->game->introBallObject, param0->resources.maneneNarc, 71);
        WiFiLobbyMinigameManene_Init3DObject(&param0->game->introBallObject, param0->seedData.introResult);
        Easy3DObject_SetVisible(&param0->game->introBallObject.object, 0);

        {
            int v7[] = {
                0x3,
                0x1,
                0x4,
                0x2,
            };

            int v8 = v7[WiFiLobbyMinigameManene_GetPlayerIndex(param0, param0->netId)];

            WiFiLobbyMinigameManene_Load3DModel(&param0->game->ballObject, param0->resources.maneneNarc, v8);
            WiFiLobbyMinigameManene_Init3DObject(&param0->game->ballObject, param0->seedData.introResult);
            WiFiLobbyMinigameManene_Load3DModel(&param0->game->ballObjects[0], param0->resources.maneneNarc, 51);
            WiFiLobbyMinigameManene_Load3DModel(&param0->game->ballObjects[1], param0->resources.maneneNarc, 57);
            WiFiLobbyMinigameManene_Load3DModel(&param0->game->ballObjects[2], param0->resources.maneneNarc, 55);
            WiFiLobbyMinigameManene_Init3DObject(&param0->game->ballObjects[0], param0->seedData.introResult);
            WiFiLobbyMinigameManene_Init3DObject(&param0->game->ballObjects[1], param0->seedData.introResult);
            WiFiLobbyMinigameManene_Init3DObject(&param0->game->ballObjects[2], param0->seedData.introResult);

            {
                WiFiLobbyMinigameManene3DObject *v9;
                int v10;

                v9 = &param0->game->ballObjects[0];

                v10 = 53;
                Easy3DAnim_LoadFrom(&v9->anims[0], &v9->model, param0->resources.maneneNarc, v10, 106, &param0->resources.g3dAllocator);
                Easy3DObject_AddAnim(&v9->object, &v9->anims[0]);
                Easy3DAnim_SetFrame(&v9->anims[0], 0);

                v10 = 52;
                Easy3DAnim_LoadFrom(&v9->anims[1], &v9->model, param0->resources.maneneNarc, v10, 106, &param0->resources.g3dAllocator);
                Easy3DAnim_SetFrame(&v9->anims[1], 0);

                v10 = 58;
                Easy3DAnim_LoadFrom(&v9->anims[2], &v9->model, param0->resources.maneneNarc, v10, 106, &param0->resources.g3dAllocator);
                Easy3DAnim_SetFrame(&v9->anims[2], 0);

                v9 = &param0->game->ballObjects[1];
                v10 = 56;
                Easy3DAnim_LoadFrom(&v9->anims[0], &v9->model, param0->resources.maneneNarc, v10, 106, &param0->resources.g3dAllocator);
                Easy3DObject_AddAnim(&v9->object, &v9->anims[0]);
                Easy3DAnim_SetFrame(&v9->anims[0], 0);

                v9 = &param0->game->ballObjects[2];
                v10 = 54;
                Easy3DAnim_LoadFrom(&v9->anims[0], &v9->model, param0->resources.maneneNarc, v10, 106, &param0->resources.g3dAllocator);
                Easy3DObject_AddAnim(&v9->object, &v9->anims[0]);
                Easy3DAnim_SetFrame(&v9->anims[0], 0);
            }
        }

        if (param0->seedData.introResult) {
            param0->game->ballObject.position.y = (-8 * FX32_ONE);
            param0->game->ballObjects[0].position.y = (-8 * FX32_ONE);
            param0->game->ballObjects[1].position.y = (-8 * FX32_ONE);
            param0->game->ballObjects[2].position.y = (-8 * FX32_ONE);
        }
    }

    param0->introAnimation = WiFiLobbyMinigame_CreateIntroAnimation(SpriteManager_GetSpriteList(param0->resources.spriteManager), HEAP_ID_106);
    PaletteData_LoadBufferFromHardware(param0->resources.paletteData, PLTTBUF_MAIN_OBJ, PLTT_DEST(0), 16 * PALETTE_SIZE_BYTES);

    if (param0->args->unk_3C) {
        NintendoWFC_StartVoiceChat(HEAP_ID_106);
    }
}

int WiFiLobbyMinigameManene_Init(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameManeneApp *v0;

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_106, 0x65000);
    v0 = ApplicationManager_NewData(appMan, sizeof(WiFiLobbyMinigameManeneApp), HEAP_ID_106);
    memset(v0, 0, sizeof(WiFiLobbyMinigameManeneApp));

    v0->args = ApplicationManager_Args(appMan);

    {
        int v1;
        int v2 = 0;

        for (v1 = 0; v1 < 4; v1++) {
            v0->playerNetIds[v1] = 0xFF;

            if (CommInfo_TrainerInfo(v1) != NULL) {
                v0->playerNetIds[v2] = v1;
                v2++;
            }
        }
    }

    WiFiLobbyMinigame_InitPlayerContext(&v0->playerContext, v0->args->unk_38, v0->args->saveData, v0->args->unk_3C, &v0->args->unk_00);
    return 1;
}

static void WiFiLobbyMinigameManene_UpdateBallTilt(WiFiLobbyMinigameManeneGame *param0, u32 param1, u32 param2)
{
    s16 v0, v1;
    BOOL v2;

    if ((param1 == 0) && (param2 == 0)) {
        param0->touchInput.touchX = 0;
        param0->touchInput.touchY = 0;

        if (param0->ballObject.tiltFramesRemaining != 0) {
            v2 = WiFiLobbyMinigameManene_DecayBallTilt(&param0->ballObject, 1.0f);

            if (v2 = 1) {
                VecFx32 v3 = { 0, FX32_CONST(100), 0 };
                VecFx32 v4;
                MTX_MultVec43(&v3, &param0->ballObjects[0].matrix, &param0->ballPosition);
            }
        } else {
            param0->ballObject.tiltX = 0.0f;
            param0->ballObject.tiltY = 0.0f;

            WiFiLobbyMinigameManene_TiltBall(&param0->ballObject, param0->touchInput.touchX, param0->touchInput.touchY, param0->touchInput.touchX, param0->touchInput.touchY, 2.35 * 0.80, 0);
            WiFiLobbyMinigameManene_TiltBall(&param0->ballObjects[0], param0->touchInput.touchX, param0->touchInput.touchY, param0->touchInput.touchX, param0->touchInput.touchY, 0.22, 0);
        }
    } else {
        f32 v5 = ((100 - (param0->ballPosition.y >> FX32_SHIFT)) / 40);

        if ((param0->ballPosition.y >> FX32_SHIFT) >= 95) {
            v5 = 0.1f;
        }

        if (param0->touchInput.touchX == 0) {
            param0->touchInput.touchX = param1;
            param0->touchInput.touchY = param2;
        }

        v2 = WiFiLobbyMinigameManene_TiltBall(&param0->ballObject, param1, param2, param0->touchInput.touchX, param0->touchInput.touchY, 2.50 * 0.80, 1);

        if (v2 = 1) {
            VecFx32 v6 = { 0, FX32_CONST(100), 0 };
            VecFx32 v7;
            MTX_MultVec43(&v6, &param0->ballObjects[0].matrix, &param0->ballPosition);
        }

        if (Sound_IsEffectPlaying(1394) == 0) {
            Sound_PlayEffect(SEQ_SE_PL_KIRAKIRA_sseq);
        }

        param0->touchInput.touchX = param1;
        param0->touchInput.touchY = param2;
    }
}

static BOOL WiFiLobbyMinigameManene_UpdateBallRoll(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;
    int v1;
    int v2, v3;
    s16 v4[][2] = {
        { 0, 0 },
        { 0, -40 },
        { 0, -30 },
        { 0, -20 },
        { 0, -10 },
        { 0, 0 },
        { 0, 10 },
        { 0, 20 },
        { 0, 30 },
        { 0, 40 },
        { 0, 00 },
        { 0, 0 },
        { 0, 0 },
        { 0, -40 },
        { 0, -30 },
        { 0, -20 },
        { 0, -10 },
        { 0, 0 },
        { 0, 10 },
        { 0, 20 },
        { 0, 30 },
        { 0, 40 },
        { 0, 00 },
        { 0, 0 },
        { 0, 0 },
        { 10, 0 },
        { 20, 0 },
        { 30, 0 },
        { 40, 0 },
        { 50, 0 },
        { 60, 0 },
        { 70, 0 },
        { 80, 0 },
        { 90, 0 },
        { 0, 0 },
        { 0, 0 },
        { 0, 0 },
        { 10, 0 },
        { 20, 0 },
        { 30, 0 },
        { 40, 0 },
        { 50, 0 },
        { 60, 0 },
        { 70, 0 },
        { 80, 0 },
        { 90, 0 },
        { 0, 0 },
        { 0, 0 },
    };

    v0 = ManagedSprite_GetAnimationFrame(param0->ballSprite);
    v1 = (param0->ballAnimCycle * 12) + v0;
    v2 = v4[v1][0];
    v3 = v4[v1][1];

    if ((v2 == 0) && (v3 == 0)) {
        WiFiLobbyMinigameManene_UpdateBallTilt(param0, 0, 0);
    } else {
        WiFiLobbyMinigameManene_UpdateBallTilt(param0, 128 + v2, 128 + v3);

        if (v2 != 0) {
            WiFiLobbyMinigameManene_SpawnSparkle(param0, 88 + v2, 128 + v3);
        } else {
            WiFiLobbyMinigameManene_SpawnSparkle(param0, 128 + v2, 128 + v3);
        }
    }

    if (v0 == 0) {
        if (param0->previousBallFrame != v0) {
            param0->ballAnimCycle++;
        }
    }

    param0->previousBallFrame = v0;

    if (param0->ballAnimCycle == 2) {
        if (ManagedSprite_GetActiveAnim(param0->ballSprite) != 2) {
            ManagedSprite_SetPositionXY(param0->ballSprite, 128, 100);
            ManagedSprite_SetAnimNoRestart(param0->ballSprite, 2);

            WiFiLobbyMinigameManene_QuaternionIdentity(&param0->ballObject.rotation);
            WiFiLobbyMinigameManene_QuaternionIdentity(&param0->ballObject.previousRotation);
            WiFiLobbyMinigameManene_TiltBall(&param0->ballObject, 0, 0, +5, +5, 0.80, 0);
            WiFiLobbyMinigameManene_TiltBall(&param0->ballObject, 0, 0, -5, -5, 0.80, 0);
        }
    }

    if ((param0->ballAnimCycle == 3) && (v0 == 11)) {
        param0->previousBallFrame = 0;
        param0->ballAnimCycle = 0;

        ManagedSprite_SetDrawFlag(param0->ballSprite, 0);

        WiFiLobbyMinigameManene_QuaternionIdentity(&param0->ballObject.rotation);
        WiFiLobbyMinigameManene_QuaternionIdentity(&param0->ballObject.previousRotation);
        WiFiLobbyMinigameManene_TiltBall(&param0->ballObject, 0, 0, +5, +5, 0.80, 0);
        WiFiLobbyMinigameManene_TiltBall(&param0->ballObject, 0, 0, -5, -5, 0.80, 0);

        return 1;
    }

    ManagedSprite_TickTwoFrames(param0->ballSprite);

    return 0;
}

int WiFiLobbyMinigameManene_Main(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameManeneApp *v0 = ApplicationManager_Data(appMan);
    BOOL v1 = 0;
    u32 v2 = WiFiLobbyMinigameManene_CheckDisconnect(v0);

    switch (v2) {
    case 1:
        return 0;
    case 2:
        return 1;
    case 0:
    default:
        break;
    }

    switch (*param1) {
    case 0:
        v1 = 1;
        v0->introScreen = WiFiLobbyMinigame_CreateIntroScreen1(&v0->playerContext, HEAP_ID_106);
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 1, param1);
        break;
    case 1:
        v1 = WiFiLobbyMinigame_IntroScreenIsDone(v0->introScreen);
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 2, param1);
        break;
    case 2:
        v1 = 1;
        v0->seedData.introResult = WiFiLobbyMinigame_IntroScreenGetResult(v0->introScreen);
        WiFiLobbyMinigame_FreeIntroScreen(v0->introScreen);
        v0->introScreen = NULL;
        WiFiLobbyMinigameManene_InitGame(v0);
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 3, param1);
        break;
    case 3:
        v1 = WiFiLobbyMinigameManene_StartFade(27);
        WiFiLobbyMinigameManene_CreatePlayerNameWindows(v0, v0->game);
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 4, param1);
        break;
    case 4:
        v1 = IsScreenFadeDone();
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 5, param1);
        break;
    case 5:
        v1 = 1;

        if (v1 == 0) {
            break;
        }

        WiFiLobbyMinigameManene_CreateMessageWindow(v0->game);
        WiFiLobbyMinigameManene_SetupIntroSequence(v0->game);
        WiFiLobbyMinigameManene_SetupResultsAnimation(v0->game);
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 6, param1);
        break;
    case 6:
        v1 = WiFiLobbyMinigameManene_UpdateBallRoll(v0->game);

        if (v1) {
            if (WiFiLobbyMinigameManene_IsHost(v0) == 1) {
                v0->seedData.seed = v0->gameSeed;
                CommSys_SendData(22, &v0->seedData, sizeof(WiFiLobbyMinigameManeneSeed));
            }
        }

        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 7, param1);
        break;
    case 7:
        v1 = v0->started;
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 8, param1);
        break;
    case 8:
        v1 = 1;
        WiFiLobbyMinigame_StartIntroAnimationRoll(v0->introAnimation);
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 9, param1);
        break;
    case 9:
        v1 = 1;
        v1 = WiFiLobbyMinigame_IntroAnimationIsDone(v0->introAnimation);

        if (v1) {
            WiFiLobbyMinigameManene_FreePlayerNameWindows(v0->game);
            WiFiLobbyMinigameManene_FreeMessageWindow(v0->game);
        }

        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 10, param1);
        break;
    case 10:
        v1 = v0->roundStarted;

        if (v0->roundStarted) {
            if (v0->game->roundState.elapsedFrames < ((30 * 40) - 0)) {
                v1 = 0;
            }
        }

        if (v1 == 0) {
            if (WiFiLobbyMinigameManene_IsHost(v0) == 1) {
                if (WiFiLobbyMinigameManene_TickCountdown(v0->countdown) == 0) {
                    Sound_StopEffect(1393, 0);
                    CommSys_SendData(23, NULL, 0);
                }
            }
            WiFiLobbyMinigameManene_UpdateGame(v0->game);
        }
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 11, param1);
        break;
    case 11:
        v1 = 1;
        Sound_StopEffect(1395, 0);
        Sound_StopEffect(1393, 0);
        WiFiLobbyMinigame_StartIntroAnimationPop(v0->introAnimation);
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 12, param1);
        break;
    case 12:
        v1 = WiFiLobbyMinigame_IntroAnimationIsDone(v0->introAnimation);
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 13, param1);
        break;
    case 13:
        v1 = 1;
        v0->score.score = (v0->game->roundState.score / 10) * 100;

        if (v0->score.score >= 100000) {
            v0->score.score = 100000;
        }

        if (v0->game->roundState.ballTouched == 0) {
            v0->score.score = 1;
        }

        CommSys_SendData(25, &v0->score, sizeof(WiFiLobbyMinigameManeneScore));
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 14, param1);
        break;
    case 14:
        v1 = 0;
        {
            int v3;
            int v4 = 0;

            for (v3 = 0; v3 < 4; v3++) {
                if (v0->scores.scores[v3].score != 0) {
                    v4++;
                }
            }

            if (v4 == v0->game->playerCount) {
                v1 = 1;
            }
        }
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 15, param1);
        break;
    case 15:
        v1 = WiFiLobbyMinigameManene_StartFade(26);
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 16, param1);
        break;
    case 16:
        v1 = IsScreenFadeDone();

        if (v1) {
            WiFiLobbyMinigameManene_FreeResources(v0);
        }

        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 17, param1);
        break;
    case 17:
        v1 = 1;
        {
            int v5;
            int v6;

            for (v5 = 0; v5 < 4; v5++) {
                v6 = WiFiLobbyMinigameManene_GetPlayerIndex(v0, v5);

                if (v6 == 0xFF) {
                    continue;
                }

                v0->ranking.unk_00[v6] = v0->scores.scores[v5].score;

                if (v0->ranking.unk_00[v6] <= 1) {
                    v0->ranking.unk_00[v6] = 0;
                }
            }

            WiFiLobbyMinigame_InitRanking(&v0->ranking, v0->playerContext.unk_08);
        }
        v0->resultsScreen = WiFiLobbyMinigame_CreateResultsScreen1(&v0->playerContext, &v0->ranking, HEAP_ID_106);
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 18, param1);
        break;
    case 18:
        v1 = WiFiLobbyMinigame_ResultsScreenIsDone(v0->resultsScreen);

        if (v1) {
            BOOL v7 = WiFiLobbyMinigame_ResultsScreenGetResult(v0->resultsScreen);

            WiFiLobbyMinigame_FreeResultsScreen(v0->resultsScreen);
            v0->resultsScreen = NULL;

            if (v7) {
                v0->replayRequested = 1;
                WiFiLobbyMinigameManene_ResetRound(v0);
                WiFiLobbyMinigameManene_AdvanceState(v0, v1, 0, param1);

                if (v0->args->unk_3C) {
                    NintendoWFC_TerminateVoiceChat();
                }
                break;
            }
        }
        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 19, param1);
        break;
    case 19:
        v1 = 1;
        CommTiming_StartSync(27);

        if (v0->args->unk_3C) {
            NintendoWFC_TerminateVoiceChat();
        }

        WiFiLobbyMinigameManene_AdvanceState(v0, v1, 20, param1);
        break;
    case 20:
    default:
        v1 = CommTiming_IsSyncState(27);
        return (v1 == 1) ? 1 : 0;
        break;
    }

    if ((*param1 >= 3) && (*param1 < 16)) {
        WiFiLobbyMinigameManene_TickPlayerRowSprites(v0->game);
        WiFiLobbyMinigameManene_Draw3DScene(v0);
    }

    return 0;
}

static void WiFiLobbyMinigameManene_FreeResources(WiFiLobbyMinigameManeneApp *param0)
{
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    VramTransfer_Free();

    {
        u32 v0;
        v0 = DisableTouchPad();
    }

    LCRNG_SetSeed(param0->gameSeed);

    WiFiLobbyMinigameManene_FreePlayerRowSprites(param0->game);
    WiFiLobbyMinigameManene_FreePlayerSprites(param0->game);
    WiFiLobbyMinigameManene_FreeBackgroundSprites(param0->game);
    WiFiLobbyMinigameManene_FreeResultSprites(param0->game);
    WiFiLobbyMinigameManene_FreeBallSprite(param0->game);
    WiFiLobbyMinigameManene_Release3DModel(&param0->game->ballObject);
    WiFiLobbyMinigameManene_Release3DModel(&param0->game->ballObjects[0]);
    WiFiLobbyMinigameManene_Release3DModel(&param0->game->ballObjects[1]);
    WiFiLobbyMinigameManene_Release3DModel(&param0->game->ballObjects[2]);
    WiFiLobbyMinigameManene_Release3DModel(&param0->game->introBallObject);

    Easy3DAnim_Release(&param0->game->ballObjects[0].anims[0], &param0->resources.g3dAllocator);
    Easy3DAnim_Release(&param0->game->ballObjects[0].anims[1], &param0->resources.g3dAllocator);
    Easy3DAnim_Release(&param0->game->ballObjects[0].anims[2], &param0->resources.g3dAllocator);
    Easy3DAnim_Release(&param0->game->ballObjects[1].anims[0], &param0->resources.g3dAllocator);
    Easy3DAnim_Release(&param0->game->ballObjects[2].anims[0], &param0->resources.g3dAllocator);

    {
        int v1;

        for (v1 = 0; v1 < 8; v1++) {
            WiFiLobbyMinigameManene_Release3DModel(&param0->game->decorationObjects[v1]);
            Easy3DAnim_Release(&param0->game->decorationObjects[v1].anims[0], &param0->resources.g3dAllocator);
            Easy3DAnim_Release(&param0->game->decorationObjects[v1].anims[1], &param0->resources.g3dAllocator);
        }
    }

    WiFiLobbyMinigame_FreeIntroAnimation(param0->introAnimation);
    WiFiLobbyMinigameManene_FreeGraphics(param0);

    if (WiFiLobbyMinigameManene_IsHost(param0) == 1) {
        WiFiLobbyMinigameManene_FreeCountdown(param0->countdown);
    }

    WiFiLobbyMinigameManene_FreeGame(param0->game);

    param0->countdown = NULL;
    param0->game = NULL;
}

static void WiFiLobbyMinigameManene_ResetRound(WiFiLobbyMinigameManeneApp *param0)
{
    param0->roundStarted = 0;
    param0->started = 0;
    param0->roundEnded = 0;

    memset(&param0->score, 0, sizeof(WiFiLobbyMinigameManeneScore));
    memset(&param0->scores, 0, sizeof(WiFiLobbyMinigameManeneScores));
}

int WiFiLobbyMinigameManene_Exit(ApplicationManager *appMan, int *param1)
{
    switch (*param1) {
    case 0: {
        u32 v0;
        WiFiLobbyMinigameManeneApp *v1 = ApplicationManager_Data(appMan);

        v0 = WiFiLobbyMinigameManene_CheckDisconnect(v1);

        ApplicationManager_FreeData(appMan);
        Heap_Destroy(HEAP_ID_106);
        CommManager_SetErrorHandling(0, 1);

        if (v0 != 0) {
            return 1;
        }

        CommTiming_StartSync(999);
        (*param1)++;
    } break;
    default:
        if ((CommTiming_IsSyncState(999) == 1) || (CommSys_ConnectedCount() < CommInfo_CountReceived())) {
            return 1;
        }
        break;
    }

    return 0;
}

static void WiFiLobbyMinigameManene_InitResources(WiFiLobbyMinigameManeneApp *param0)
{
    param0->resources.maneneNarc = NARC_ctor(NARC_INDEX_ARC__MANENE, HEAP_ID_106);
    param0->resources.bucketNarc = NARC_ctor(NARC_INDEX_GRAPHIC__BUCKET, HEAP_ID_106);
    param0->resources.bgConfig = BgConfig_New(HEAP_ID_106);
    param0->resources.paletteData = PaletteData_New(HEAP_ID_106);
    param0->resources.g3dPipeline = G3DPipeline_Init(HEAP_ID_106, TEXTURE_VRAM_SIZE_128K, PALETTE_VRAM_SIZE_64K, NULL);
    param0->resources.camera = Camera_Alloc(HEAP_ID_106);

    WiFiLobbyMinigameManene_InitCamera(param0);

    PaletteData_SetAutoTransparent(param0->resources.paletteData, TRUE);
    PaletteData_AllocBuffer(param0->resources.paletteData, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_106);
    PaletteData_AllocBuffer(param0->resources.paletteData, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_106);
    PaletteData_AllocBuffer(param0->resources.paletteData, PLTTBUF_MAIN_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_106);
    PaletteData_AllocBuffer(param0->resources.paletteData, PLTTBUF_SUB_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_106);

    WiFiLobbyMinigameManene_InitBackgrounds(param0->resources.bgConfig);
    WiFiLobbyMinigameManene_InitSpriteSystem(param0);

    G3X_AlphaBlend(1);

    {
        static const GXRgb v0[8] = {
            GX_RGB(0, 0, 0),
            GX_RGB(4, 4, 4),
            GX_RGB(4, 4, 4),
            GX_RGB(4, 4, 4),
            GX_RGB(4, 4, 4),
            GX_RGB(4, 4, 4),
            GX_RGB(4, 4, 4),
            GX_RGB(4, 4, 4),
        };

        G3X_EdgeMarking(1);
        G3X_SetEdgeColorTable(v0);
    }

    HeapExp_FndInitAllocator(&param0->resources.g3dAllocator, HEAP_ID_106, 32);
}

void WiFiLobbyMinigameManene_FreeGraphics(WiFiLobbyMinigameManeneApp *param0)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
    Bg_FreeTilemapBuffer(param0->resources.bgConfig, 0);
    Bg_FreeTilemapBuffer(param0->resources.bgConfig, 1);
    Bg_FreeTilemapBuffer(param0->resources.bgConfig, 2);
    Bg_FreeTilemapBuffer(param0->resources.bgConfig, 3);
    Bg_FreeTilemapBuffer(param0->resources.bgConfig, 4);
    Bg_FreeTilemapBuffer(param0->resources.bgConfig, 5);
    Bg_FreeTilemapBuffer(param0->resources.bgConfig, 6);
    Bg_FreeTilemapBuffer(param0->resources.bgConfig, 7);
    Heap_Free(param0->resources.bgConfig);
    PaletteData_FreeBuffer(param0->resources.paletteData, PLTTBUF_MAIN_BG);
    PaletteData_FreeBuffer(param0->resources.paletteData, PLTTBUF_SUB_BG);
    PaletteData_FreeBuffer(param0->resources.paletteData, PLTTBUF_MAIN_OBJ);
    PaletteData_FreeBuffer(param0->resources.paletteData, PLTTBUF_SUB_OBJ);
    PaletteData_Free(param0->resources.paletteData);
    NARC_dtor(param0->resources.maneneNarc);
    NARC_dtor(param0->resources.bucketNarc);
    G3DPipelineBuffers_Free(param0->resources.g3dPipeline);
    Camera_Delete(param0->resources.camera);
    SpriteSystem_FreeResourcesAndManager(param0->resources.spriteSystem, param0->resources.spriteManager);
    SpriteSystem_Free(param0->resources.spriteSystem);

    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;

    GXLayers_SwapDisplay();
    G3X_AlphaBlend(0);
}

static void WiFiLobbyMinigameManene_InitBackgrounds(BgConfig *param0)
{
    GXLayers_DisableEngineALayers();
    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_3D,
        };
        SetAllGraphicsModes(&v0);
    }
    {
        GXBanks v1 = {
            GX_VRAM_BG_128_A,
            GX_VRAM_BGEXTPLTT_NONE,
            GX_VRAM_SUB_BG_128_C,
            GX_VRAM_SUB_BGEXTPLTT_NONE,
            GX_VRAM_OBJ_64_E,
            GX_VRAM_OBJEXTPLTT_NONE,
            GX_VRAM_SUB_OBJ_16_I,
            GX_VRAM_SUB_OBJEXTPLTT_NONE,
            GX_VRAM_TEX_0_B,
            GX_VRAM_TEXPLTT_01_FG
        };

        GXLayers_SetBanks(&v1);
        MI_CpuClear32((void *)HW_BG_VRAM, HW_BG_VRAM_SIZE);
        MI_CpuClear32((void *)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
        MI_CpuClear32((void *)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
        MI_CpuClear32((void *)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    }
    {
        BgTemplate v2[] = {
            {
                .x = 0x0,
                .y = 0x0,
                .bufferSize = 0x800,
                .baseTile = 0x0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x2000,
                .charBase = GX_BG_CHARBASE_0x10000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0x3,
                .areaOver = 0x0,
                .mosaic = FALSE,
            },
            {
                .x = 0x0,
                .y = 0x0,
                .bufferSize = 0x1000,
                .baseTile = 0x0,
                .screenSize = BG_SCREEN_SIZE_512x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x2800,
                .charBase = GX_BG_CHARBASE_0x14000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0x2,
                .areaOver = 0x0,
                .mosaic = FALSE,
            },
            {
                .x = 0x0,
                .y = 0x0,
                .bufferSize = 0x1000,
                .baseTile = 0x0,
                .screenSize = BG_SCREEN_SIZE_512x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x3800,
                .charBase = GX_BG_CHARBASE_0x14000,
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
                .screenBase = GX_BG_SCRBASE_0x4800,
                .charBase = GX_BG_CHARBASE_0x10000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0x3,
                .areaOver = 0x0,
                .mosaic = FALSE,
            },
        };

        Bg_ClearTilesRange(BG_LAYER_MAIN_1, 32, 0, HEAP_ID_106);
        Bg_ClearTilesRange(BG_LAYER_MAIN_2, 32, 0, HEAP_ID_106);
        Bg_ClearTilesRange(BG_LAYER_MAIN_3, 32, 0, HEAP_ID_106);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_1, &v2[1], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_2, &v2[2], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_3, &v2[3], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_1);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_2);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_3);
    }
    {
        BgTemplate v3[] = {
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0xb000,
                .charBase = GX_BG_CHARBASE_0x00000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x1000,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_512x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0xb800,
                .charBase = GX_BG_CHARBASE_0x04000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 1,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x1000,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_512x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0xc800,
                .charBase = GX_BG_CHARBASE_0x04000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 1,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x1000,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x512,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0xd800,
                .charBase = GX_BG_CHARBASE_0x04000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        Bg_ClearTilesRange(4, 32, 0, HEAP_ID_106);
        Bg_ClearTilesRange(5, 32, 0, HEAP_ID_106);
        Bg_ClearTilesRange(6, 32, 0, HEAP_ID_106);
        Bg_ClearTilesRange(7, 32, 0, HEAP_ID_106);
        Bg_InitFromTemplate(param0, BG_LAYER_SUB_0, &v3[0], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_SUB_1, &v3[1], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_SUB_2, &v3[2], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_SUB_3, &v3[3], 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_1);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_2);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_3);
    }

    Bg_ClearTilesRange(4, 32, 0, HEAP_ID_106);
    Bg_ClearTilesRange(5, 32, 0, HEAP_ID_106);
    Bg_ClearTilesRange(6, 32, 0, HEAP_ID_106);
    Bg_ClearTilesRange(7, 32, 0, HEAP_ID_106);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);

    gSystem.whichScreenIs3D = DS_SCREEN_SUB;

    GXLayers_SwapDisplay();
    G2_SetBlendAlpha(0, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ, 7, 10);
    G2S_SetBlendAlpha(0, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ, 7, 10);
}

static void WiFiLobbyMinigameManene_InitSpriteSystem(WiFiLobbyMinigameManeneApp *param0)
{
    param0->resources.spriteSystem = SpriteSystem_Alloc(HEAP_ID_106);
    {
        const RenderOamTemplate v0 = {
            0,
            128,
            0,
            32,
            0,
            128,
            0,
            32,
        };

        const CharTransferTemplateWithModes v1 = {
            64 + 64,
            1024 * 0x40,
            512 * 0x20,
            GX_OBJVRAMMODE_CHAR_1D_128K,
            GX_OBJVRAMMODE_CHAR_1D_32K
        };

        SpriteSystem_Init(param0->resources.spriteSystem, &v0, &v1, 16 + 16);
    }
    {
        BOOL v2;
        const SpriteResourceCapacities v3 = {
            64 + 64,
            16 + 16,
            128,
            128,
            16,
            16,
        };

        param0->resources.spriteManager = SpriteManager_New(param0->resources.spriteSystem);

        v2 = SpriteSystem_InitSprites(param0->resources.spriteSystem, param0->resources.spriteManager, 255);
        GF_ASSERT(v2);

        v2 = SpriteSystem_InitManagerWithCapacities(param0->resources.spriteSystem, param0->resources.spriteManager, &v3);
        GF_ASSERT(v2);
    }
    SetSubScreenViewRect(SpriteSystem_GetRenderer(param0->resources.spriteSystem), 0, (192 + 64) << FX32_SHIFT);
}

static BOOL WiFiLobbyMinigameManene_StartFade(int param0)
{
    StartScreenFade(FADE_BOTH_SCREENS, param0, param0, 0, 6, 1, HEAP_ID_106);
    return 1;
}

static void WiFiLobbyMinigameManene_AdvanceState(WiFiLobbyMinigameManeneApp *param0, BOOL param1, int param2, int *param3)
{
    if (param1) {
        *param3 = param2;
    }
}

static void WiFiLobbyMinigameManene_VBlankCallback(void *param0)
{
    WiFiLobbyMinigameManeneApp *v0 = param0;

    VramTransfer_Process();
    SpriteSystem_TransferOam();
    PaletteData_CommitFadedBuffers(v0->resources.paletteData);
    Bg_RunScheduledUpdates(v0->resources.bgConfig);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

BOOL WiFiLobbyMinigameManene_IsHost(WiFiLobbyMinigameManeneApp *param0)
{
    return (param0->netId == 0) ? 1 : 0;
}

void WiFiLobbyMinigameManene_SetStarted(WiFiLobbyMinigameManeneApp *param0)
{
    param0->started = 1;
}

void WiFiLobbyMinigameManene_SetRoundStarted(WiFiLobbyMinigameManeneApp *param0)
{
    param0->roundStarted = 1;
}

static u32 WiFiLobbyMinigameManene_CheckDisconnect(WiFiLobbyMinigameManeneApp *param0)
{
    if (WiFiLobbyMinigame_CheckDisconnected(&param0->playerContext) == 1) {
        if (param0->resources.disconnectState.disconnected == 0) {
            if (IsScreenFadeDone() == TRUE) {
                FinishScreenFade();
            }

            SetColorBrightness(COLOR_BLACK);
            param0->resources.disconnectState.disconnected = 1;

            return 1;
        } else {
            if (WiFiLobbyMinigame_HandleDisconnect(&param0->playerContext) == 0) {
                return 1;
            }

            if (param0->game != NULL) {
                WiFiLobbyMinigameManene_FreePlayerNameWindows(param0->game);
                WiFiLobbyMinigameManene_FreeMessageWindow(param0->game);
                WiFiLobbyMinigameManene_FreeResources(param0);
            }

            if (param0->resultsScreen != NULL) {
                WiFiLobbyMinigame_FreeResultsScreen(param0->resultsScreen);
                param0->resultsScreen = NULL;
            }

            if (param0->introScreen != NULL) {
                WiFiLobbyMinigame_FreeIntroScreen(param0->introScreen);
                param0->introScreen = NULL;
            }

            return 2;
        }
    }

    return 0;
}
