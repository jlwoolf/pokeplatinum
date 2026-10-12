#include "contest_competition/contest_competition_02247A48.h"

#include <nitro.h>
#include <string.h>

#include "battle_anim/ball_throw.h"
#include "battle_anim/struct_ball_throw.h"
#include "contest_competition/contest_competition_022476F8.h"
#include "contest_competition/contest_competition_0224F18C.h"
#include "contest_competition/struct_contest_packet_queue_config.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_visual_competition.h"
#include "contest_competition/struct_visual_photo_reveal_task.h"
#include "contest_competition/struct_visual_photo_drop_task.h"
#include "contest_competition/struct_visual_photo_judging_task.h"
#include "contest_competition/struct_visual_photo_exit_task.h"
#include "contest_competition/struct_visual_ball_capsule_task.h"
#include "contest_competition/struct_visual_ball_seal_task.h"
#include "contest_competition/struct_visual_ball_throw_task.h"
#include "contest_competition/struct_visual_ball_capsule_show_task.h"
#include "contest_competition/struct_visual_ball_capsule.h"
#include "contest_competition/struct_visual_ball_rotation.h"
#include "contest_competition/struct_visual_ball_movement.h"
#include "contest_competition/struct_visual_ball_appeal.h"
#include "contest_competition/struct_visual_contestant_reveal_task.h"
#include "contest_competition/struct_visual_contestant_score_task.h"
#include "contest_competition/struct_visual_contestant_result_task.h"
#include "contest_competition/struct_visual_contestant_info.h"
#include "contest_competition/struct_visual_contestant_done_task.h"
#include "contest_competition/struct_contest_packet_queue.h"
#include "contest_competition/struct_contest_packet_payloads.h"
#include "contest_competition/struct_contest_packet_handler.h"
#include "image_clip_app/image_clip_app_0225AF8C.h"
#include "image_clip_app/struct_image_clip_app_0225AF8C.h"

#include "assert.h"
#include "bg_window.h"
#include "brightness_controller.h"
#include "contest.h"
#include "graphics.h"
#include "heap.h"
#include "palette.h"
#include "pokemon.h"
#include "pokemon_sprite.h"
#include "render_window.h"
#include "sound_playback.h"
#include "spl.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "contest_util.h"

static int contest_competition_02247A88(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02247A9C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02247AAC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int param4);
static int contest_competition_02247AEC(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02247B00(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02247C5C(SysTask *param0, void *param1);
static int contest_competition_02247D68(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02247D7C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02247DC8(SysTask *param0, void *param1);
static int contest_competition_02247E78(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02247E8C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02247EDC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02247F2C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02247F8C(SysTask *param0, void *param1);
static int contest_competition_02248138(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224814C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02248198(SysTask *param0, void *param1);
static int contest_competition_02247AB0(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02247AC4(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static int contest_competition_02248258(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224826C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_022482B0(SysTask *param0, void *param1);
static int contest_competition_0224840C(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02248420(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02248464(SysTask *param0, void *param1);
static int contest_competition_022485E8(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_022485FC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02248648(SysTask *param0, void *param1);
static int contest_competition_022486E4(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_022486F8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02248744(SysTask *param0, void *param1);
static int contest_competition_022487E8(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_022487FC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02248860(SysTask *param0, void *param1);
static void contest_competition_022489C8(SysTask *param0, void *param1);
static void contest_competition_02248A24(SysTask *param0, void *param1);
static void contest_competition_02248AA4(SysTask *param0, void *param1);
static void contest_competition_02248BE0(SysTask *param0, void *param1);
static int contest_competition_02248D28(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02248D3C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02248DA4(SysTask *param0, void *param1);
static int contest_competition_02248FBC(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02248FD0(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02249014(SysTask *param0, void *param1);
static int contest_competition_02248E58(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02248E6C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02248EC4(SysTask *param0, void *param1);
static int contest_competition_0224924C(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02249260(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_022492AC(SysTask *param0, void *param1);

static const ContestPacketHandler Unk_contest_competition_02254488[] = {
    { contest_competition_02247A88, contest_competition_02247A9C, contest_competition_02247AAC },
    { contest_competition_02247AB0, contest_competition_02247AC4, NULL },
    { contest_competition_02247AEC, contest_competition_02247B00, NULL },
    { contest_competition_02247D68, contest_competition_02247D7C, NULL },
    { contest_competition_02247E78, contest_competition_02247E8C, NULL },
    { contest_competition_02247E78, contest_competition_02247EDC, NULL },
    { contest_competition_02247E78, contest_competition_02247F2C, NULL },
    { contest_competition_02248138, contest_competition_0224814C, NULL },
    { contest_competition_02248258, contest_competition_0224826C, NULL },
    { contest_competition_0224840C, contest_competition_02248420, NULL },
    { contest_competition_022485E8, contest_competition_022485FC, NULL },
    { contest_competition_022486E4, contest_competition_022486F8, NULL },
    { contest_competition_022487E8, contest_competition_022487FC, NULL },
    { contest_competition_02248D28, contest_competition_02248D3C, NULL },
    { contest_competition_02248E58, contest_competition_02248E6C, NULL },
    { contest_competition_02248FBC, contest_competition_02248FD0, NULL },
    { contest_competition_0224924C, contest_competition_02249260, NULL }
};

__attribute__((aligned(4))) static const s8 Unk_contest_competition_02254468[] = {
    0xD,
    0x9,
    0x5,
    0x1,
    0xFFFFFFFFFFFFFFFD
};

__attribute__((aligned(4))) static const u16 Unk_contest_competition_02254470[] = {
    0x20,
    0x28,
    0x30,
    0x38,
    0xA0,
    0xA8,
    0xB0,
    0xB8,
    0x120,
    0x128,
    0x130,
    0x138
};

void contest_competition_02247A48(VisualCompetition *param0)
{
    ContestPacketQueueConfig v0;

    v0.handlers = Unk_contest_competition_02254488;
    v0.handlerCount = NELEMS(Unk_contest_competition_02254488);
    v0.playerContestantID = param0->contest->data.playerContestantID;
    v0.selfContestantID = param0->contest->data.leaderContestantID;
    v0.isLinkContest = param0->contest->isLinkContest;

    contest_competition_0224F18C(&param0->packetQueue, &v0);
}

static int contest_competition_02247A88(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02247A9C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    contest_competition_0224F26C(param0, param2, NULL, 0);
}

static void contest_competition_02247AAC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int param4)
{
    VisualCompetition *v0 = param1;
    return;
}

static int contest_competition_02247AB0(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02247AC4(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;

    v0->initialized = 1;

    if (Contest_IsPlayerLeader(v0->contest) == FALSE) {
        contest_competition_0224F26C(param0, param2, NULL, 0);
    }
}

static int contest_competition_02247AEC(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(VisualContestantInfo));
    return v1;
}

static void contest_competition_02247B00(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantInfo *v1 = param3;
    VisualPhotoDropTask *v2;
    s32 v3;
    int v4;

    v2 = Heap_Alloc(HEAP_ID_22, sizeof(VisualPhotoDropTask));
    MI_CpuClear8(v2, sizeof(VisualPhotoDropTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->contestantID = v1->contestantID;

    for (v4 = 0; v4 < 4; v4++) {
        if (v2->competition->photoSprites[v4].photoSprite != NULL) {
            PhotoSprite_Free(v2->competition->photoSprites[v4].photoSprite);
            v2->competition->photoSprites[v4].photoSprite = NULL;
        }
    }

    v3 = Pokemon_DPSpriteYOffset(v0->scene.contestData->contestMons[v1->contestantID], 2);

    {
        PhotoSpriteConfig v5;

        MI_CpuClear8(&v5, sizeof(PhotoSpriteConfig));

        v5.heapID = HEAP_ID_22;
        v5.unk_04 = 128;
        v5.unk_08 = (96 - 32) + 80 / 2;
        v0->photoSprites[v1->contestantID].x = 128;
        v0->photoSprites[v1->contestantID].y = (96 - 32) + 80 / 2;
        v0->photoSprites[v1->contestantID].photoSprite = PhotoSprite_CreateForContestNoBackdrop(&v5, v0->contest->data.photos[v1->contestantID]);

        PhotoSprite_SetTransformEnabled(v0->photoSprites[v1->contestantID].photoSprite, 0);
    }

    {
        G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
        G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 0);
        G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0, -16);
        GX_SetVisibleWnd(GX_WNDMASK_W0);

        v0->window0Left = 0;
        v0->window0Top = 0;
        v0->window0Right = 255;
        v0->window0Bottom = (Unk_contest_competition_02254468[0] + 4) * 8;
    }

    Graphics_LoadTilemapToBgLayer(NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, 21, v0->scene.bgConfig, 2, 0, 0, 1, HEAP_ID_22);
    SysTask_Start(contest_competition_02247C5C, v2, 30000);
}

static void contest_competition_02247C5C(SysTask *param0, void *param1)
{
    VisualPhotoRevealTask *v0 = param1;
    int v1;

    switch (v0->state) {
    case 0:
        v0->state++;
        break;
    case 1:
        G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
        v1 = Pokemon_DPSpriteYOffset(v0->competition->scene.contestData->contestMons[v0->contestantID], 2);
        PhotoSprite_MoveToWithOffset(v0->competition->photoSprites[v0->contestantID].photoSprite, v0->competition->photoSprites[v0->contestantID].x, v0->competition->photoSprites[v0->contestantID].y, v1);
        PhotoSprite_SetTransformEnabled(v0->competition->photoSprites[v0->contestantID].photoSprite, 1);
        v0->state++;
        break;
    case 2:
        v0->state++;
        break;
    case 3:
        G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
        PaletteData_BlendMulti(v0->competition->scene.paletteData, PLTTBUF_MAIN_BG, 0x1fff, 0, 0x0);
        PaletteData_BlendMulti(v0->competition->scene.paletteData, PLTTBUF_MAIN_OBJ, 0x3fff, 0, 0x0);
        Sound_PlayEffect(SEQ_SE_DP_CON_019_sseq);
        v0->state++;
        break;
    case 4:
        v0->timer++;

        if (v0->timer > 10) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02247D68(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(VisualContestantInfo));
    return v1;
}

static void contest_competition_02247D7C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantInfo *v1 = param3;
    VisualPhotoDropTask *v2 = Heap_Alloc(HEAP_ID_22, sizeof(VisualPhotoDropTask));
    MI_CpuClear8(v2, sizeof(VisualPhotoDropTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->contestantID = v1->contestantID;

    SysTask_Start(contest_competition_02247DC8, v2, 30000);
}

static void contest_competition_02247DC8(SysTask *param0, void *param1)
{
    VisualPhotoDropTask *v0 = param1;
    int v1;

    switch (v0->state) {
    case 0:
        v0->x = PokemonSprite_GetAttribute(v0->competition->scene.pokemonSprites[v0->contestantID], MON_SPRITE_X_CENTER) << 8;
        v0->y = PokemonSprite_GetAttribute(v0->competition->scene.pokemonSprites[v0->contestantID], MON_SPRITE_Y_CENTER) << 8;
        v0->state++;
        break;
    case 1:
        v1 = Pokemon_DPSpriteYOffset(v0->competition->scene.contestData->contestMons[v0->contestantID], 2);
        v0->y += 0x100;

        if (v0->y >= ((96 - 32) << 8)) {
            v0->y = (96 - 32) << 8;
            v0->state++;
        }

        PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v0->contestantID], MON_SPRITE_X_CENTER, v0->x >> 8);
        PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v0->contestantID], MON_SPRITE_Y_CENTER, v0->y >> 8);
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02247E78(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(VisualContestantInfo));
    return v1;
}

static void contest_competition_02247E8C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantInfo *v1 = param3;
    VisualPhotoJudgingTask *v2 = Heap_Alloc(HEAP_ID_22, sizeof(VisualPhotoJudgingTask));
    MI_CpuClear8(v2, sizeof(VisualPhotoJudgingTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->threshold1 = v1->visualRank;
    v2->judgingState = 0;

    SysTask_Start(contest_competition_02247F8C, v2, 30000);
}

static void contest_competition_02247EDC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantInfo *v1 = param3;
    VisualPhotoJudgingTask *v2 = Heap_Alloc(HEAP_ID_22, sizeof(VisualPhotoJudgingTask));
    MI_CpuClear8(v2, sizeof(VisualPhotoJudgingTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->threshold1 = v1->danceRank;
    v2->judgingState = 1;

    SysTask_Start(contest_competition_02247F8C, v2, 30000);
}

static void contest_competition_02247F2C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantInfo *v1 = param3;
    VisualPhotoJudgingTask *v2 = Heap_Alloc(HEAP_ID_22, sizeof(VisualPhotoJudgingTask));
    MI_CpuClear8(v2, sizeof(VisualPhotoJudgingTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->threshold1 = v1->visualRank + v1->danceRank;
    v2->threshold2 = v1->visualRank;
    v2->param = v1->danceRank;
    v2->judgingState = 0;
    v2->flag = 1;

    SysTask_Start(contest_competition_02247F8C, v2, 30000);
}

static void contest_competition_02247F8C(SysTask *param0, void *param1)
{
    VisualPhotoJudgingTask *v0 = param1;
    int v1;

    switch (v0->state) {
    case 0:
        Sound_PlayEffect(SEQ_SE_DP_CON_007_sseq);
        v0->contestantID = 15;
        v0->state++;
    case 1:
        if (v0->timer >= v0->threshold1) {
            v0->contestantID = 0;
            Sound_PlayEffect(SEQ_SE_DP_CON_007_sseq);
            v0->state++;
            break;
        } else if (v0->flag == 1) {
            if (v0->timer >= v0->threshold2) {
                v0->judgingState = 1;
            }
        }

        if (v0->contestantID > 0) {
            v0->contestantID--;
            break;
        }

        v0->contestantID = 3;

        {
            s16 v2, v3, v4, v5;

            v4 = Contest_GetRNGNext(v0->competition->contest) % ((256 - 32 - 32) / 2);
            v5 = Contest_GetRNGNext(v0->competition->contest) % ((192 - 32 - 32) / 2);

            if (Contest_GetRNGNext(v0->competition->contest) & 1) {
                v2 = 128 + v4;
            } else {
                v2 = 128 - v4;
            }

            if (Contest_GetRNGNext(v0->competition->contest) & 1) {
                v3 = 96 + v5;
            } else {
                v3 = 96 - v5;
            }

            if (v0->timer > 0) {
                if ((((v0->prevX < 128) && (v2 < 128)) || ((v0->prevX > 128) && (v2 > 128))) && (((v0->prevY < 96) && (v3 < 96)) || ((v0->prevY > 96) && (v3 > 96)))) {
                    if (Contest_GetRNGNext(v0->competition->contest) & 1) {
                        if (v2 < 128) {
                            v2 = 128 + v4;
                        } else {
                            v2 = 128 - v4;
                        }
                    } else {
                        if (v3 < 96) {
                            v3 = 96 + v5;
                        } else {
                            v3 = 96 - v5;
                        }
                    }
                }
            }

            if (v0->timer & 1) {
                contest_competition_022477B8(v0->competition, v2, v3, 180 << FX32_SHIFT, v0->judgingState);
            } else {
                contest_competition_022477B8(v0->competition, v2, v3, 0, v0->judgingState);
            }

            v0->prevX = v2;
            v0->prevY = v3;
        }
        v0->timer++;
        break;
    case 2:
        v0->contestantID++;

        if (v0->contestantID > 30) {
            v0->contestantID = 0;
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02248138(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(VisualContestantInfo));
    return v1;
}

static void contest_competition_0224814C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantInfo *v1 = param3;
    VisualPhotoExitTask *v2 = Heap_Alloc(HEAP_ID_22, sizeof(VisualPhotoExitTask));
    MI_CpuClear8(v2, sizeof(VisualPhotoExitTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->contestantID = v1->contestantID;

    SysTask_Start(contest_competition_02248198, v2, 30000);
}

static void contest_competition_02248198(SysTask *param0, void *param1)
{
    VisualPhotoExitTask *v0 = param1;
    int monYOffset = Pokemon_DPSpriteYOffset(v0->competition->scene.contestData->contestMons[v0->contestantID], 2);

    switch (v0->state) {
    case 0:
        v0->x = v0->competition->photoSprites[v0->contestantID].x << 8;
        v0->y = v0->competition->photoSprites[v0->contestantID].y << 8;
        v0->state++;
        break;
    case 1:
        v0->x += 0x300;

        if (v0->x >= (300 << 8)) {
            v0->state++;
        }

        PhotoSprite_MoveToWithOffset(v0->competition->photoSprites[v0->contestantID].photoSprite, v0->x >> 8, v0->y >> 8, monYOffset);
        break;
    default:
        PhotoSprite_Free(v0->competition->photoSprites[v0->contestantID].photoSprite);
        v0->competition->photoSprites[v0->contestantID].photoSprite = NULL;
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02248258(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_0224826C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualBallCapsuleTask *v1 = Heap_Alloc(HEAP_ID_22, sizeof(VisualBallCapsuleTask));
    MI_CpuClear8(v1, sizeof(VisualBallCapsuleTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->packetQueue = param0;

    SysTask_Start(contest_competition_022482B0, v1, 30000);
}

static void contest_competition_022482B0(SysTask *param0, void *param1)
{
    VisualBallCapsuleTask *v0 = param1;

    switch (v0->state) {
    case 0:

        if (v0->holdDelay > 0) {
            v0->holdDelay--;
            break;
        }

        if (v0->stepDelay > 0) {
            v0->stepDelay--;
            break;
        }

        v0->stepDelay = 1;

        {
            u16 *v1, *v2;
            int v3, v4, v5, v6, v7;

            v1 = Bg_GetTilemapBuffer(v0->competition->scene.bgConfig, 2);

            for (v4 = 0; v4 < 4; v4++) {
                if (Unk_contest_competition_02254468[v0->row] + v4 < 0) {
                    continue;
                }

                v2 = &v1[32 * (Unk_contest_competition_02254468[v0->row] + v4)];
                v7 = Unk_contest_competition_02254470[v0->column] + 32 * v4;
                v5 = 0;

                for (v6 = 0; v6 < 32 / 8; v6++) {
                    for (v3 = 0; v3 < 8; v3++) {
                        v2[v5 + v3] &= 0xfc00;
                        v2[v5 + v3] |= v7 + v3;
                    }

                    v5 += 8;
                }
            }

            {
                if ((v0->row > 0) && (v0->column == 0)) {
                    v2 = &v1[32 * Unk_contest_competition_02254468[v0->row - 1]];

                    for (v6 = 0; v6 < 32; v6++) {
                        v2[v6] &= 0xfc00;
                    }
                }
            }

            Bg_ScheduleTilemapTransfer(v0->competition->scene.bgConfig, 2);
        }

        v0->column++;

        if (v0->column >= NELEMS(Unk_contest_competition_02254470)) {
            v0->column = 0;
            v0->row++;
            v0->holdDelay = 0;

            if (v0->row >= NELEMS(Unk_contest_competition_02254468)) {
                v0->state++;
            }
        }
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_0224840C(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02248420(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualBallSealTask *v1 = Heap_Alloc(HEAP_ID_22, sizeof(VisualBallSealTask));
    MI_CpuClear8(v1, sizeof(VisualBallSealTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->packetQueue = param0;

    SysTask_Start(contest_competition_02248464, v1, 30000);
}

static void contest_competition_02248464(SysTask *param0, void *param1)
{
    VisualBallSealTask *v0 = param1;

    switch (v0->state) {
    case 0:

        if (v0->holdDelay > 0) {
            v0->holdDelay--;
            break;
        }

        if (v0->stepDelay > 0) {
            v0->stepDelay--;
            break;
        }

        v0->stepDelay = 1;

        {
            u16 *v1, *v2;
            int v3, v4, v5, v6, v7;
            int v8;

            v1 = Bg_GetTilemapBuffer(v0->competition->scene.bgConfig, 2);

            for (v4 = 0; v4 < 4; v4++) {
                v8 = Unk_contest_competition_02254468[NELEMS(Unk_contest_competition_02254468) - 1 - v0->row];

                if (v8 + v4 < 0) {
                    continue;
                }

                v2 = &v1[32 * (v8 + v4)];
                v7 = Unk_contest_competition_02254470[NELEMS(Unk_contest_competition_02254470) - 1 - v0->column] + 32 * v4;
                v5 = 0;

                for (v6 = 0; v6 < 32 / 8; v6++) {
                    for (v3 = 0; v3 < 8; v3++) {
                        v2[v5 + v3] &= 0xfc00;
                        v2[v5 + v3] |= v7 + v3;
                    }

                    v5 += 8;
                }
            }

            {
                if ((v0->row > 0) && (v0->column == 0)) {
                    v8 = Unk_contest_competition_02254468[NELEMS(Unk_contest_competition_02254468) - 1 - v0->row + 1];
                    v8 += 4 - 1;
                    v2 = &v1[v8 * 32];

                    for (v6 = 0; v6 < 32; v6++) {
                        v2[v6] &= 0xfc00;
                        v2[v6] |= 0x200 + (v6 % 8);
                    }
                }
            }

            Bg_ScheduleTilemapTransfer(v0->competition->scene.bgConfig, 2);
        }

        v0->column++;

        if (v0->column >= NELEMS(Unk_contest_competition_02254470)) {
            v0->column = 0;
            v0->row++;
            v0->holdDelay = 0;

            if (v0->row >= NELEMS(Unk_contest_competition_02254468)) {
                v0->state++;
            }
        }

        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_022485E8(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(VisualContestantInfo));
    return v1;
}

static void contest_competition_022485FC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantInfo *v1 = param3;
    VisualBallThrowTask *v2 = Heap_Alloc(HEAP_ID_22, sizeof(VisualBallThrowTask));
    MI_CpuClear8(v2, sizeof(VisualBallThrowTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->unused_11 = v1->contestantID;

    SysTask_Start(contest_competition_02248648, v2, 30000);
}

static void contest_competition_02248648(SysTask *param0, void *param1)
{
    VisualBallThrowTask *v0 = param1;

    switch (v0->state) {
    case 0:
        contest_competition_022478D0(v0->competition, v0->unused_11);
        v0->x = PokemonSprite_GetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_X_CENTER) * 0x100;
        v0->y = PokemonSprite_GetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_Y_CENTER) * 0x100;
        v0->state++;
    case 1:
        v0->x -= 0x400;

        if (v0->x <= (230 * 0x100)) {
            v0->x = 230 * 0x100;
            v0->state++;
        }

        PokemonSprite_SetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_X_CENTER, v0->x / 0x100);
        PokemonSprite_SetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_Y_CENTER, v0->y / 0x100);
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_022486E4(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(VisualContestantInfo));
    return v1;
}

static void contest_competition_022486F8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantInfo *v1 = param3;
    VisualBallThrowTask *v2 = Heap_Alloc(HEAP_ID_22, sizeof(VisualBallThrowTask));
    MI_CpuClear8(v2, sizeof(VisualBallThrowTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->unused_11 = v1->contestantID;

    SysTask_Start(contest_competition_02248744, v2, 30000);
}

static void contest_competition_02248744(SysTask *param0, void *param1)
{
    VisualBallThrowTask *v0 = param1;

    switch (v0->state) {
    case 0:
        GF_ASSERT(v0->competition->scene.trainerSprite != NULL);
        v0->x = PokemonSprite_GetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_X_CENTER) * 0x100;
        v0->y = PokemonSprite_GetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_Y_CENTER) * 0x100;
        v0->state++;
    case 1:
        v0->x += 0x400;

        if (v0->x >= (320 * 0x100)) {
            v0->x = 320 * 0x100;
            v0->state++;
        }

        PokemonSprite_SetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_X_CENTER, v0->x / 0x100);
        PokemonSprite_SetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_Y_CENTER, v0->y / 0x100);
        break;
    default:
        contest_competition_02247918(v0->competition);
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_022487E8(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(VisualContestantInfo));
    return v1;
}

static void contest_competition_022487FC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantInfo *v1 = param3;
    VisualBallCapsuleShowTask *v2 = Heap_Alloc(HEAP_ID_22, sizeof(VisualBallCapsuleShowTask));
    MI_CpuClear8(v2, sizeof(VisualBallCapsuleShowTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->contestantID = v1->contestantID;
    v2->rotation.competition = v0;
    v2->movement.competition = v0;
    v2->movement.contestantID = v1->contestantID;
    v2->appeal.competition = v0;
    v2->capsule.mon = v0->scene.contestData->contestMons[v1->contestantID];

    SysTask_Start(contest_competition_02248860, v2, 30000);
}

static void contest_competition_02248860(SysTask *param0, void *param1)
{
    VisualBallCapsuleShowTask *v0 = param1;

    switch (v0->state) {
    case 0:
        SysTask_Start(contest_competition_02248A24, &v0->rotation, (30000 + 10));
        SysTask_Start(contest_competition_02248BE0, &v0->appeal, (30000 + 10));

        {
            PhotoSpriteConfig v1;
            int v2;

            v2 = Pokemon_DPSpriteYOffset(v0->movement.competition->scene.contestData->contestMons[v0->movement.contestantID], 2);
            MI_CpuClear8(&v1, sizeof(PhotoSpriteConfig));

            v1.heapID = HEAP_ID_22;
            v1.unk_04 = 128;
            v1.unk_08 = (96 - 32) + v2;
            v0->movement.competition->photoSprites[v0->movement.contestantID].photoSprite = PhotoSprite_CreateForContestNoBackdrop(&v1, v0->movement.competition->contest->data.photos[v0->movement.contestantID]);

            PhotoSprite_SetTransformEnabled(v0->movement.competition->photoSprites[v0->movement.contestantID].photoSprite, 0);
        }

        v0->state++;
        break;
    case 1:
        if (v0->rotation.done == 1) {
            SysTask_Start(contest_competition_022489C8, &v0->capsule, (30000 + 10));
            SysTask_Start(contest_competition_02248AA4, &v0->movement, (30000 + 10));
            v0->state++;
        }
        break;
    case 2:
        if ((v0->capsule.done == 1) && (v0->movement.done == 1) && (v0->appeal.done == 1)) {
            Sound_PlayEffect(SEQ_SE_DP_CON_007_sseq);
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(param1);
        SysTask_Done(param0);
        return;
    }
}

static void Contest_SetEmitterPos(SPLEmitter *emitter)
{
    VecFx32 v0 = { 0, 0, 0 };
    SPLEmitter_SetPos(emitter, &v0);
}

static void contest_competition_022489C8(SysTask *param0, void *param1)
{
    VisualBallCapsule *v0 = param1;

    switch (v0->state) {
    case 0:
        v0->config.battlerType = 0;
        v0->config.mon = v0->mon;
        v0->sealEffect = BallCapsuleSealEffect_New(HEAP_ID_22, &v0->config);
        BallCapsuleSealEffect_Start(v0->sealEffect);
        BallCapsuleSealEffect_Play(v0->sealEffect, Contest_SetEmitterPos);
        v0->state++;
        break;
    case 1:
        if (BallCapsuleSealEffect_IsActive(v0->sealEffect) == 0) {
            BallCapsuleSealEffect_Free(v0->sealEffect);
            v0->state++;
        }
        break;
    default:
        v0->done = 1;
        SysTask_Done(param0);
        return;
    }
}

static void contest_competition_02248A24(SysTask *param0, void *param1)
{
    VisualBallRotation *v0 = param1;

    switch (v0->state) {
    case 0:
        v0->counter++;

        if (v0->counter >= 1) {
            v0->counter = 0;
            v0->state++;
        }
        break;
    case 1: {
        BallThrow v1;

        v1.type = 14;
        v1.heapID = HEAP_ID_22;
        v1.mode = 0;
        v1.target = 0;
        v1.cellActorSys = v0->competition->scene.spriteSystem;
        v1.paletteSys = v0->competition->scene.paletteData;
        v1.bgPrio = 1;

        v0->ballRotation = BallRotation_New(&v1);
    }
        v0->state++;
        break;
    case 2:
        if (BallRotation_IsActive(v0->ballRotation) == 1) {
            break;
        }
    default:
        BallRotation_Free(v0->ballRotation);
        v0->done = 1;
        SysTask_Done(param0);
        return;
    }
}

static void contest_competition_02248AA4(SysTask *param0, void *param1)
{
    VisualBallMovement *v0 = param1;
    s32 v1;

    v1 = Pokemon_DPSpriteYOffset(v0->competition->scene.contestData->contestMons[v0->contestantID], 2);

    switch (v0->state) {
    case 0: {
        v0->scaleX = 0;
        v0->scaleY = 0;
        PhotoSprite_SetScale(v0->competition->photoSprites[v0->contestantID].photoSprite, 0, 0, FX32_ONE);

        v0->competition->photoSprites[v0->contestantID].x = 128;
        v0->competition->photoSprites[v0->contestantID].y = (96 - 32) + 80 / 2;
        PhotoSprite_SetTransformEnabled(v0->competition->photoSprites[v0->contestantID].photoSprite, 1);
    }
        v0->state++;
    case 1:
        v0->scaleX += (FX32_ONE / (0x100 / 0x20));
        v0->scaleY += (FX32_ONE / (0x100 / 0x20));

        if (v0->scaleX >= FX32_ONE) {
            v0->scaleX = FX32_ONE;
            v0->scaleY = FX32_ONE;
        }

        PhotoSprite_SetScale(v0->competition->photoSprites[v0->contestantID].photoSprite, v0->scaleX, v0->scaleY, FX32_ONE);
        PhotoSprite_MoveToWithOffset(v0->competition->photoSprites[v0->contestantID].photoSprite, v0->competition->photoSprites[v0->contestantID].x, v0->competition->photoSprites[v0->contestantID].y, v1);

        if (v0->scaleX >= FX32_ONE) {
            s32 species = Pokemon_GetValue(v0->competition->scene.contestData->contestMons[v0->contestantID], MON_DATA_SPECIES, NULL);
            s32 form = Pokemon_GetValue(v0->competition->scene.contestData->contestMons[v0->contestantID], MON_DATA_FORM, NULL);
            PlayCryWithParams(v0->competition->contest->chatotCry[v0->contestantID], POKECRY_NORMAL, species, form, 0, 127, NULL, HEAP_ID_22);
            v0->state++;
        }
        break;
    default:
        v0->done = 1;
        SysTask_Done(param0);
        return;
    }
}

static void contest_competition_02248BE0(SysTask *param0, void *param1)
{
    VisualBallAppeal *v0 = param1;

    switch (v0->state) {
    case 0:
        GF_ASSERT(v0->competition->scene.trainerSprite != NULL);

        v0->timer++;

        if (v0->timer > 1) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 1:
        v0->x = PokemonSprite_GetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_X_CENTER) * 0x100;
        v0->y = PokemonSprite_GetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_Y_CENTER) * 0x100;
        v0->state++;
    case 2:
        if (v0->counter & 1) {
            PokemonSprite_SetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_X_CENTER, v0->x / 0x100);
            PokemonSprite_SetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_Y_CENTER, v0->y / 0x100);
        } else {
            PokemonSprite_SetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_X_CENTER, v0->x / 0x100);
            PokemonSprite_SetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_Y_CENTER, v0->y / 0x100 - 3);
        }

        v0->counter++;

        if (v0->counter >= 3) {
            v0->state++;
        }
        break;
    case 3:
        v0->timer++;

        if (v0->timer >= 7) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 4:
        v0->x += 0x400;

        if (v0->x >= (320 * 0x100)) {
            v0->x = 320 * 0x100;
            v0->state++;
        }

        PokemonSprite_SetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_X_CENTER, v0->x / 0x100);
        PokemonSprite_SetAttribute(v0->competition->scene.trainerSprite, MON_SPRITE_Y_CENTER, v0->y / 0x100);
        break;
    default:
        contest_competition_02247918(v0->competition);
        v0->done = 1;
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02248D28(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(VisualContestantInfo));
    return v1;
}

static void contest_competition_02248D3C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantInfo *v1 = param3;
    VisualContestantRevealTask *v2 = Heap_Alloc(HEAP_ID_22, sizeof(VisualContestantRevealTask));
    MI_CpuClear8(v2, sizeof(VisualContestantRevealTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->contestantID = v1->contestantID;
    v2->messageArgs = v1->messageArgs;
    v2->messageID = v1->state;
    v2->flag = v1->messageArg2;
    v2->delay = v1->messageArg1;

    SysTask_Start(contest_competition_02248DA4, v2, 30000);
}

static void contest_competition_02248DA4(SysTask *param0, void *param1)
{
    VisualContestantRevealTask *v0 = param1;

    switch (v0->state) {
    case 0:
        if (v0->messageID != 0) {
            Window_DrawMessageBoxWithScrollCursor(&v0->competition->scene.windows[0], 1, 1, 14);
            Bg_ScheduleTilemapTransfer(v0->competition->scene.bgConfig, 1);
            contest_competition_02247A08(v0->competition, v0->messageID, &v0->messageArgs);
            v0->state++;
        } else {
            v0->state = 100;
        }
        break;
    case 1:
        if (contest_competition_02247A3C(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 2:
        v0->timer++;

        if (v0->flag == 1) {
            v0->state++;
        } else if (v0->timer >= v0->delay) {
            Window_EraseMessageBox(&v0->competition->scene.windows[0], 1);
            Bg_ScheduleTilemapTransfer(v0->competition->scene.bgConfig, 1);
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02248E58(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(VisualContestantInfo));
    return v1;
}

static void contest_competition_02248E6C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantScoreTask *v1;
    VisualContestantInfo *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_22, sizeof(VisualContestantScoreTask));
    MI_CpuClear8(v1, sizeof(VisualContestantScoreTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->packetQueue = param0;
    v1->x = v2->x;
    v1->y = v2->y;
    v1->z = v2->z;
    v1->score = v1->score;

    SysTask_Start(contest_competition_02248EC4, v1, 30000);
}

static void contest_competition_02248EC4(SysTask *param0, void *param1)
{
    VisualContestantScoreTask *v0 = param1;
    int v1;

    switch (v0->state) {
    case 0:
        if (v0->competition->contest->isLinkContest == TRUE) {
            G2_SetWnd1InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 0);
            G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
            GX_SetVisibleWnd(GX_WNDMASK_W1);

            v0->competition->window1Left = 256 - 16;
            v0->competition->window1Top = 0;
            v0->competition->window1Right = 255;
            v0->competition->window1Bottom = 16;
        }

        BrightnessController_StartTransition(v0->z, v0->y, v0->x, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD) ^ GX_BLEND_PLANEMASK_BG1, BRIGHTNESS_MAIN_SCREEN);

        v0->state++;
        break;
    case 1:
        if (BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN) == TRUE) {
            PaletteData_FillBufferRange(v0->competition->scene.paletteData, PLTTBUF_MAIN_BG, PLTTSEL_FADED, 0x0, 0, (13 * 16));
            PaletteData_FillBufferRange(v0->competition->scene.paletteData, PLTTBUF_MAIN_OBJ, PLTTSEL_FADED, 0x0, 0, ((16 - 2) * 16));
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02248FBC(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02248FD0(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantResultTask *v1 = Heap_Alloc(HEAP_ID_22, sizeof(VisualContestantResultTask));
    MI_CpuClear8(v1, sizeof(VisualContestantResultTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->packetQueue = param0;

    SysTask_Start(contest_competition_02249014, v1, 30000);
}

static void contest_competition_02249014(SysTask *param0, void *param1)
{
    VisualContestantResultTask *v0 = param1;
    int v1;

    v0->timer++;

    if (v0->timer == 30) {
        v1 = 0;
        v0->stepDelay = 30;
        v0->flag = 1;
    }

    if (v0->competition->contest->isLinkContest == FALSE && v0->timer < 30 && (JOY_NEW(PAD_BUTTON_A) || gSystem.touchPressed)) {
        v0->timer = 30;
        v1 = 0;
        v0->stepDelay = 0;
        v0->flag = 1;
    } else if (v0->timer > 30) {
        v1 = 0;
    } else {
        v1 = 1;
    }

    switch (v0->state) {
    case 0:
        if (v0->holdDelay > 0) {
            v0->holdDelay--;
            break;
        }

        if (v0->stepDelay > 0) {
            v0->stepDelay--;
            break;
        }

        v0->stepDelay = v1;

        if (v0->flag == 1) {
            Sound_PlayEffect(SEQ_SE_DP_CON_020_sseq);
            v0->flag = 0;
        }

        {
            u16 *v2, *v3;
            int v4, v5, v6, v7, v8;

            v2 = Bg_GetTilemapBuffer(v0->competition->scene.bgConfig, 2);

            for (v5 = 0; v5 < 4; v5++) {
                if (Unk_contest_competition_02254468[v0->row] + v5 < 0) {
                    continue;
                }

                v3 = &v2[32 * (Unk_contest_competition_02254468[v0->row] + v5)];
                v8 = Unk_contest_competition_02254470[v0->column] + 32 * v5;
                v6 = 0;

                for (v7 = 0; v7 < 32 / 8; v7++) {
                    for (v4 = 0; v4 < 8; v4++) {
                        v3[v6 + v4] &= 0xfc00;
                        v3[v6 + v4] |= v8 + v4;
                    }

                    v6 += 8;
                }
            }

            {
                if ((v0->row > 0) && (v0->column == 0)) {
                    v3 = &v2[32 * Unk_contest_competition_02254468[v0->row - 1]];

                    for (v7 = 0; v7 < 32; v7++) {
                        v3[v7] &= 0xfc00;
                    }
                }
            }

            Bg_ScheduleTilemapTransfer(v0->competition->scene.bgConfig, 2);
        }

        {
            v0->competition->window0Bottom = (Unk_contest_competition_02254468[v0->row] + 4) * 8 - (v0->column * (4 * 8) / NELEMS(Unk_contest_competition_02254470));

            if (v0->competition->window0Bottom == 0) {
                G2_BlendNone();
                GX_SetVisibleWnd(GX_WNDMASK_NONE);
            }
        }

        v0->column++;

        if (v0->column >= NELEMS(Unk_contest_competition_02254470)) {
            v0->column = 0;
            v0->row++;
            v0->holdDelay = 0;

            if (v0->row >= NELEMS(Unk_contest_competition_02254468)) {
                v0->state++;
            }
        }
        break;
    default:
        G2_BlendNone();
        GX_SetVisibleWnd(GX_WNDMASK_NONE);

        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_0224924C(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    VisualCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(VisualContestantInfo));
    return v1;
}

static void contest_competition_02249260(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    VisualCompetition *v0 = param1;
    VisualContestantInfo *v1 = param3;
    VisualContestantDoneTask *v2 = Heap_Alloc(HEAP_ID_22, sizeof(VisualContestantDoneTask));
    MI_CpuClear8(v2, sizeof(VisualContestantDoneTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;

    Sound_PlayEffect(v1->score);
    SysTask_Start(contest_competition_022492AC, v2, 30000);
}

static void contest_competition_022492AC(SysTask *param0, void *param1)
{
    VisualContestantDoneTask *v0 = param1;

    switch (v0->state) {
    case 0:
    default:
        if (v0->competition->counter == 0) {
            contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
            Heap_Free(v0);
            SysTask_Done(param0);
            return;
        }
        break;
    }
}
