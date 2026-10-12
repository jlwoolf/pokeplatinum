#include "contest_competition/contest_competition_0224A0FC.h"

#include <cstdlib>
#include <nitro.h>
#include <string.h>

#include "contest_competition/contest_competition_0223DAD0.h"
#include "contest_competition/contest_competition_0223F118.h"
#include "contest_competition/struct_dance_competition_scene.h"
#include "contest_competition/struct_dance_sprite_task.h"
#include "contest_competition/struct_dance_move_icon_task.h"
#include "contest_competition/struct_dance_note_task.h"
#include "contest_competition/struct_dance_score_task.h"
#include "contest_competition/struct_dance_photo_sprite.h"
#include "contest_competition/struct_dance_contestant.h"
#include "contest_competition/struct_dance_move_data.h"
#include "contest_competition/struct_dance_contestant_sprite.h"
#include "contest_competition/struct_dance_message_args.h"
#include "contest_competition/struct_dance_combo_task.h"
#include "contest_competition/struct_dance_beat_task.h"
#include "contest_competition/struct_dance_camera.h"
#include "contest_competition/struct_dance_saved_data.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_dance_packet.h"
#include "contest_competition/struct_dance_move_definition.h"
#include "contest_competition/struct_dance_message.h"
#include "image_clip_app/image_clip_app_0225AF8C.h"
#include "image_clip_app/struct_image_clip_app_0225AF8C.h"
#include "image_clip_app/struct_image_clip_app_0225B1BC_decl.h"

#include "assert.h"
#include "bg_window.h"
#include "contest.h"
#include "game_options.h"
#include "heap.h"
#include "inlines.h"
#include "math_util.h"
#include "message.h"
#include "narc.h"
#include "palette.h"
#include "particle_system.h"
#include "pokemon.h"
#include "pokemon_sprite.h"
#include "render_window.h"
#include "sound_playback.h"
#include "spl.h"
#include "sprite.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "text.h"
#include "font_oam.h"
#include "contest_util.h"

#include "res/text/bank/contest_dance_competition.h"

typedef struct {
    DanceCompetition *unk_00;
    DancePhotoSprite *unk_04;
    DanceMoveIconTask *unk_08;
    u8 *unk_0C;
    u8 unk_10;
    u8 unk_11;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    fx32 unk_20;
    s32 unk_24;
    s32 unk_28;
} DanceMoveIconMoveTask;

typedef struct {
    PhotoSprite *unk_00;
    u8 *unk_04;
    GXRgb unk_08;
    GXRgb unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u8 unk_10;
} DancePhotoDisplay;

static void contest_competition_0224A8D4(SysTask *param0, void *param1);
static void contest_competition_0224AA68(SysTask *param0, void *param1);
static void contest_competition_0224B528(DanceCompetition *param0, int param1, int param2, int param3, int param4, int param5);
static void contest_competition_0224B5F0(SysTask *param0, void *param1);
void contest_competition_0224BD00(DanceCompetition *param0);
void contest_competition_0224BD28(DanceCompetition *param0, int param1, int param2);
int contest_competition_0224BDF0(DanceCompetition *param0, int param1);
int contest_competition_0224BE24(DanceCompetition *param0, int param1);
static void contest_competition_0224BE50(SysTask *param0, void *param1);
static void contest_competition_0224BE64(DanceContestantSprite *param0);
static void contest_competition_0224BF58(DanceContestantSprite *param0);
static void contest_competition_0224C414(SysTask *param0, void *param1);
static BOOL contest_competition_0224B7BC(DanceMoveData *param0, PokemonSprite *param1, DancePhotoSprite *param2, int param3, int param4, int param5, DanceMoveIconTask *param6, u32 param7);
static BOOL contest_competition_0224B8D0(DanceMoveData *param0, PokemonSprite *param1, DancePhotoSprite *param2, int param3, int param4, int param5, int param6, u32 param7);
static BOOL contest_competition_0224BA50(DanceMoveData *param0, PokemonSprite *param1, DancePhotoSprite *param2, int param3, int param4, int param5, int param6, u32 param7);
static void contest_competition_0224ABFC(SysTask *param0, void *param1);
static int contest_competition_0224B06C(int param0);
static void contest_competition_0224AE84(SysTask *param0, void *param1);
static void contest_competition_0224C718(SysTask *param0, void *param1);
void contest_competition_0224C89C(DanceCompetition *param0, const DancePacket *param1);
static void contest_competition_0224CA28(SysTask *param0, void *param1);
static void contest_competition_0224CAC0(SPLEmitter *param0);
static void contest_competition_0224CB00(DanceCompetition *param0, int param1, int param2);
static void contest_competition_0224CB80(DanceCompetition *param0, int param1);
void contest_competition_0224CD84(DanceCompetition *param0, u32 param1, u32 param2, int param3, int param4, u16 param5);
static void contest_competition_0224CD60(SysTask *param0, void *param1);
static void contest_competition_0224CF4C(SysTask *param0, void *param1);
static void contest_competition_0224C7B8(SysTask *param0, void *param1);

__attribute__((aligned(4))) static const struct {
    u16 unk_00;
    u16 unk_02;
} Unk_contest_competition_022546DC[] = {
    { 0x0, 0x0 },
    { 0x1F, 0x7 },
    { 0x7C00, 0x7 },
    { 0x3E0, 0x7 },
    { 0x27FF, 0x8 },
    { 0x0, 0x7 }
};

__attribute__((aligned(4))) static const u8 Unk_contest_competition_022549C0[] = {
    0x0,
    0x4,
    0x8,
    0xC
};

__attribute__((aligned(4))) static const s16 Unk_contest_competition_022546F4[CONTEST_NUM_PARTICIPANTS][3] = {
    { 0x80, 0x60, 0xFFFFFFFFFFFFFE00 },
    { 0x30, 0x28, 0xFFFFFFFFFFFFFD80 },
    { 0x80, 0x28, 0xFFFFFFFFFFFFFD80 },
    { 0xD0, 0x28, 0xFFFFFFFFFFFFFD80 }
};

__attribute__((aligned(4))) static const s16 Unk_contest_competition_022546CC[4][2] = {
    { 0x80, 0x58 },
    { 0x30, 0x20 },
    { 0x80, 0x20 },
    { 0xD0, 0x20 }
};

__attribute__((aligned(4))) static const u8 Unk_contest_competition_022549BC[] = {
    0xB0,
    0xA8,
    0xB0,
    0xB8
};

static const SpriteTemplate Unk_contest_competition_02254760 = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x2D,
    0x2,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x80EB, 0x80E9, 0x80EB, 0x80EB, 0xFFFFFFFF, 0xFFFFFFFF },
    0x3,
    0x0
};

static const SpriteTemplate Unk_contest_competition_02254794 = {
    0x0,
    0x0,
    0x0,
    0x0,
    0xD,
    0x3,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x80EF, 0x80E9, 0x80EC, 0x80EC, 0xFFFFFFFF, 0xFFFFFFFF },
    0x1,
    0x0
};

static const SpriteTemplate Unk_contest_competition_022547C8 = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x2E,
    0x1,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x80F0, 0x80E9, 0x80ED, 0x80ED, 0xFFFFFFFF, 0xFFFFFFFF },
    0x1,
    0x0
};

static const SpriteTemplate Unk_contest_competition_022547FC = {
    0x0,
    0x90,
    0x0,
    0x0,
    0xB,
    0x5,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x80F1, 0x80E9, 0x80EE, 0x80EE, 0xFFFFFFFF, 0xFFFFFFFF },
    0x1,
    0x0
};

static const SpriteTemplate Unk_contest_competition_02254830 = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x30,
    0x1,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x80F2, 0x80E9, 0x80EF, 0x80EF, 0xFFFFFFFF, 0xFFFFFFFF },
    0x3,
    0x0
};

static const SpriteTemplate Unk_contest_competition_02254864 = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x2F,
    0x3,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x80F4, 0x80E9, 0x80F1, 0x80F1, 0xFFFFFFFF, 0xFFFFFFFF },
    0x3,
    0x0
};

static const SpriteTemplate Unk_contest_competition_0225472C = {
    0x0,
    0x0,
    0x0,
    0x0,
    0xE,
    0x2,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x80F5, 0x80E9, 0x80F2, 0x80F2, 0xFFFFFFFF, 0xFFFFFFFF },
    0x3,
    0x0
};

static const DanceMessage Unk_contest_competition_0225470C[] = {
    { DanceCompetition_Text_Jump, 0x0 },
    { DanceCompetition_Text_CompetitionIsReady, 0x6 },
    { DanceCompetition_Text_EveryoneHereForPracticeContest, 0x1 },
    { DanceCompetition_Text_Unused, 0x0 },
    { DanceCompetition_Text_PerformStepsAsMainDancer, 0x3 },
    { DanceCompetition_Text_CopyPokemonBeforeYou, 0x3 },
    { DanceCompetition_Text_AnnounceLeadingMon, 0x4 },
    { DanceCompetition_Text_ThanksForJoiningPracticeContest, 0x0 }
};

__attribute__((aligned(4))) static const s32 Unk_contest_competition_02254938[(16 * 2) + 1] = {
    0xFFFFFFFFFFFF8A08,
    0xFFFFFFFFFFFF9104,
    0xFFFFFFFFFFFF97FF,
    0xFFFFFFFFFFFF9EFB,
    0xFFFFFFFFFFFFA5F6,
    0xFFFFFFFFFFFFACF2,
    0xFFFFFFFFFFFFB3ED,
    0xFFFFFFFFFFFFBA21,
    0xFFFFFFFFFFFFC1E4,
    0xFFFFFFFFFFFFC8E0,
    0xFFFFFFFFFFFFCFDB,
    0xFFFFFFFFFFFFD6D7,
    0xFFFFFFFFFFFFDDD2,
    0xFFFFFFFFFFFFE4CE,
    0xFFFFFFFFFFFFEBC9,
    0xFFFFFFFFFFFFF2C5,
    0xFFFFFFFFFFFFF9C0,
    0xBB,
    0x7B7,
    0xEB2,
    0x15AE,
    0x1CA9,
    0x23A5,
    0x2AA0,
    0x319C,
    0x3897,
    0x3F93,
    0x468E,
    0x4D8A,
    0x5485,
    0x5B81,
    0x627C,
    0x6978
};

__attribute__((aligned(4))) static const s32 Unk_contest_competition_022548D4[(12 * 2) + 1] = {
    0xFFFFFFFFFFFF9104,
    0xFFFFFFFFFFFF99BE,
    0xFFFFFFFFFFFFA278,
    0xFFFFFFFFFFFFAB32,
    0xFFFFFFFFFFFFB3EC,
    0xFFFFFFFFFFFFBCA6,
    0xFFFFFFFFFFFFC560,
    0xFFFFFFFFFFFFCE1A,
    0xFFFFFFFFFFFFD6D4,
    0xFFFFFFFFFFFFDF8E,
    0xFFFFFFFFFFFFE848,
    0xFFFFFFFFFFFFF102,
    0xFFFFFFFFFFFFF9BC,
    0x276,
    0xB30,
    0x13EA,
    0x1CA4,
    0x255E,
    0x2E18,
    0x36D2,
    0x3F8C,
    0x4846,
    0x5100,
    0x59BA,
    0x6274
};

static const s32 *const Unk_contest_competition_022546C4[] = {
    Unk_contest_competition_02254938,
    Unk_contest_competition_022548D4
};

s16 contest_competition_0224A0FC(int contestantID)
{
    return Unk_contest_competition_022546F4[contestantID][0];
}

s16 contest_competition_0224A10C(int contestantID)
{
    return Unk_contest_competition_022546F4[contestantID][1];
}

s16 contest_competition_0224A120(int contestantID)
{
    return Unk_contest_competition_022546F4[contestantID][2];
}

void contest_competition_0224A134(DanceCompetition *param0)
{
    int i;
    PhotoSpriteConfig v1;
    int v2;

    for (i = 0; i < CONTEST_NUM_PARTICIPANTS; i++) {
        GF_ASSERT(param0->scene.pokemonSpriteDataArray[i].tiles == NULL);
    }

    MI_CpuClear8(&v1, sizeof(PhotoSpriteConfig));
    v1.heapID = HEAP_ID_23;

    for (i = 0; i < CONTEST_NUM_PARTICIPANTS; i++) {
        int v3;

        v3 = param0->scoreState.judgeVotes[i];
        v2 = Pokemon_DPSpriteYOffset(param0->contest->data.contestMons[v3], 2);

        v1.unk_04 = Unk_contest_competition_022546F4[i][0];
        v1.unk_08 = Unk_contest_competition_022546F4[i][1] + v2;

        param0->scene.photoSprites[v3].x = v1.unk_04;
        param0->scene.photoSprites[v3].y = v1.unk_08;
        param0->scene.photoSprites[v3].z = Unk_contest_competition_022546F4[i][2];
        param0->scene.photoSprites[v3].photoSprite = PhotoSprite_CreateForContestNoBackdrop(&v1, param0->contest->data.photos[v3]);

        PhotoSprite_MoveTo(param0->scene.photoSprites[v3].photoSprite, param0->scene.photoSprites[v3].x, param0->scene.photoSprites[v3].y);

        if (i > 0) {
            PhotoSprite_SetVisible(param0->scene.photoSprites[v3].photoSprite, 0);
            PhotoSprite_AdjustPriority(param0->scene.photoSprites[v3].photoSprite, -100);
        }
    }
}

void contest_competition_0224A1EC(DanceCompetitionScene *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        PhotoSprite_Free(param0->photoSprites[v0].photoSprite);

        param0->pokemonSpriteDataArray[v0].tiles = NULL;
    }
}

void contest_competition_0224A20C(SpriteSystem *param0, SpriteManager *param1)
{
    return;
}

void contest_competition_0224A210(SpriteManager *param0)
{
    return;
}

__attribute__((aligned(4))) static const u16 Unk_contest_competition_02254898[] = {
    0x2291,
    0x22B1,
    0x22D1,
    0x22F1,
    0x2311,
    0x2331,
    0x22B1,
    0x2351,
    0x2371,
    0x2311,
    0x2331,
    0x2391,
    0x22D1,
    0x2371,
    0x2311,
    0x2291,
    0x22B1,
    0x22D1,
    0x22F1,
    0x2311,
    0x2331,
    0x22B1,
    0x2351,
    0x2371,
    0x2311,
    0x2331,
    0x2391,
    0x22D1,
    0x2371,
    0x2311
};

void contest_competition_0224A214(DanceCompetitionScene *param0, int param1, int param2)
{
    int v0, v1, v2;
    int v3 = contest_competition_0223F0BC(param2, 2);
    int v4 = contest_competition_0223F0BC(param2, 3);
    int v5 = (256 / 8 - v3) / 2;

    if (param1 > v4) {
        param1 = v4;
    }

    v1 = param1 / 8;
    v2 = param1 % 8;

    {
        u16 *v6;

        v6 = Bg_GetTilemapBuffer(param0->bgConfig, 3);
        v6 = &v6[32 * 0x13 + v5];

        if (param2 == 0) {
            for (v0 = 0; v0 < v1; v0++) {
                if (v0 % 8 == 0) {
                    v6[v0] = (0x200c + 8);
                } else {
                    v6[v0] = (v0 & 1) ? (0x202c + 8) : (0x204c + 8);
                }
            }

            if (v0 < v3) {
                if (v0 % 8 == 0) {
                    v6[v0] = 0x200c + v2;
                } else {
                    v6[v0] = ((v0 & 1) ? 0x202c : 0x204c) + v2;
                }

                v0++;
            }

            for (; v0 < v3; v0++) {
                if (v0 % 8 == 0) {
                    v6[v0] = 0x200c;
                } else {
                    v6[v0] = (v0 & 1) ? 0x202c : 0x204c;
                }
            }
        } else {
            for (v0 = 0; v0 < v1; v0++) {
                v6[v0] = Unk_contest_competition_02254898[v0] + 8;
            }

            if (v0 < v3) {
                v6[v0] = Unk_contest_competition_02254898[v0] + v2;
                v0++;
            }

            for (; v0 < v3; v0++) {
                v6[v0] = Unk_contest_competition_02254898[v0];
            }
        }

        Bg_ScheduleTilemapTransfer(param0->bgConfig, 3);
    }
}

void contest_competition_0224A368(DanceCompetitionScene *param0, int param1, int param2, int param3)
{
    int v0 = param1 * contest_competition_0223F0BC(param3, 3) / param2;
    contest_competition_0224A214(param0, v0, param3);
}

void contest_competition_0224A390(SpriteSystem *param0, SpriteManager *param1, NARC *param2)
{
    SpriteSystem_LoadCharResObjFromOpenNarc(param0, param1, param2, 58, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, 33003);
    SpriteSystem_LoadCharResObjFromOpenNarc(param0, param1, param2, 59, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, 33004);
    SpriteSystem_LoadCharResObjFromOpenNarc(param0, param1, param2, 60, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, 33005);
    SpriteSystem_LoadCharResObjFromOpenNarc(param0, param1, param2, 61, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, 33006);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0, param1, param2, 62, TRUE, 33003);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0, param1, param2, 63, TRUE, 33003);
}

void contest_competition_0224A428(SpriteManager *param0)
{
    SpriteManager_UnloadCharObjById(param0, 33003);
    SpriteManager_UnloadCharObjById(param0, 33004);
    SpriteManager_UnloadCharObjById(param0, 33005);
    SpriteManager_UnloadCharObjById(param0, 33006);
    SpriteManager_UnloadCellObjById(param0, 33003);
    SpriteManager_UnloadAnimObjById(param0, 33003);
}

static int contest_competition_0224A46C(DanceCompetitionScene *param0, SpriteSystem *param1, SpriteManager *param2, int param3, int param4, int param5, int param6, int param7)
{
    ManagedSprite *v0;
    int v1;
    SpriteTemplate v2;

    v2 = Unk_contest_competition_02254760;

    if (param3 == 2) {
        v2.priority += 10;
    } else {
        switch (param7) {
        case 0:
        default:
            break;
        case 1:
            v2.priority += 3;
            break;
        case 2:
            v2.priority += 2;
            break;
        case 3:
            v2.priority += 1;
            break;
        }
    }

    switch (param4) {
    case 3:
        v2.resources[0] = 33004;
        v2.plttIdx = 2;
        break;
    case 4:
        v2.resources[0] = 33006;
        v2.plttIdx = 6;
        break;
    case 1:
        v2.resources[0] = 33005;
        v2.plttIdx = 7;
        break;
    case 2:
    default:
        v2.resources[0] = 33003;
        v2.plttIdx = 2;
        break;
    }

    v0 = SpriteSystem_NewSprite(param1, param2, &v2);

    ManagedSprite_SetAnim(v0, param3);
    Sprite_TickFrame(v0->sprite);
    ManagedSprite_SetPositionXYWithSubscreenOffset(v0, param5, param6, (256 * FX32_ONE));
    ManagedSprite_SetAnimateFlag(v0, 1);

    for (v1 = 0; v1 < (((16 * 2) / 2) * 4 + 4); v1++) {
        if (param0->sprites[v1] == NULL) {
            param0->sprites[v1] = v0;
            return v1;
        }
    }

    GF_ASSERT(FALSE);
    return 0;
}

void contest_competition_0224A580(DanceCompetitionScene *param0)
{
    int v0;

    for (v0 = 0; v0 < (((16 * 2) / 2) * 4 + 4); v0++) {
        if (param0->sprites[v0] != NULL) {
            Sprite_DeleteAndFreeResources(param0->sprites[v0]);
            param0->sprites[v0] = NULL;
        }
    }
}

void contest_competition_0224A5A8(SpriteSystem *param0, SpriteManager *param1, NARC *param2)
{
    SpriteSystem_LoadCharResObjFromOpenNarc(param0, param1, param2, 55, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, 33007);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0, param1, param2, 56, TRUE, 33004);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0, param1, param2, 57, TRUE, 33004);
}

void contest_competition_0224A5F8(SpriteManager *param0)
{
    SpriteManager_UnloadCharObjById(param0, 33007);
    SpriteManager_UnloadCellObjById(param0, 33004);
    SpriteManager_UnloadAnimObjById(param0, 33004);
}

void contest_competition_0224A61C(DanceCompetitionScene *param0, SpriteSystem *param1, SpriteManager *param2)
{
    ManagedSprite *v0;
    int v1;

    for (v1 = 0; v1 < 3; v1++) {
        param0->judgeSprites[v1] = SpriteSystem_NewSprite(param1, param2, &Unk_contest_competition_02254794);
        ManagedSprite_SetDrawFlag(param0->judgeSprites[v1], 0);
    }
}

void contest_competition_0224A650(DanceCompetitionScene *param0)
{
    int v0, v1;

    for (v0 = 0; v0 < 3; v0++) {
        Sprite_DeleteAndFreeResources(param0->judgeSprites[v0]);
        param0->judgeSprites[v0] = NULL;
    }
}

void contest_competition_0224A674(DanceCompetitionScene *param0)
{
    int v0;

    String *excellent = MessageLoader_GetNewString(param0->danceMessageLoader, DanceCompetition_Text_Excellent);
    String *good = MessageLoader_GetNewString(param0->danceMessageLoader, DanceCompetition_Text_Good);
    String *miss = MessageLoader_GetNewString(param0->danceMessageLoader, DanceCompetition_Text_Miss);

    for (v0 = 0; v0 < 3; v0++) {
        contest_competition_0223F1E8(HEAP_ID_23, param0->bgConfig, param0->spriteManager, param0->fontOAMManager, &param0->textLabels[0][v0], excellent, FONT_SYSTEM, TEXT_COLOR(0xb, 0xc, 0), 0, 33001, 0, 0, 1, 1, 12);
        FontOAM_SetDrawFlag(param0->textLabels[0][v0].fontOAM, 0);

        contest_competition_0223F1E8(HEAP_ID_23, param0->bgConfig, param0->spriteManager, param0->fontOAMManager, &param0->textLabels[1][v0], good, FONT_SYSTEM, TEXT_COLOR(0xb, 0xc, 0), 0, 33001, 0, 0, 1, 1, 12);
        FontOAM_SetDrawFlag(param0->textLabels[1][v0].fontOAM, 0);

        contest_competition_0223F1E8(HEAP_ID_23, param0->bgConfig, param0->spriteManager, param0->fontOAMManager, &param0->textLabels[2][v0], miss, FONT_SYSTEM, TEXT_COLOR(0xb, 0xc, 0), 0, 33001, 0, 0, 1, 1, 12);
        FontOAM_SetDrawFlag(param0->textLabels[2][v0].fontOAM, 0);
    }

    String_Free(excellent);
    String_Free(good);
    String_Free(miss);
}

void contest_competition_0224A7B8(DanceCompetitionScene *param0)
{
    int v0, v1;

    for (v1 = 0; v1 < 3; v1++) {
        for (v0 = 0; v0 < 3; v0++) {
            contest_competition_0223F2E4(&param0->textLabels[v1][v0]);
        }
    }
}

void contest_competition_0224A7E0(DanceCompetitionScene *param0, SpriteSystem *param1, SpriteManager *param2, int param3, int param4, u8 param5)
{
    ManagedSprite *v0;
    int v1, v2, v3, v4;
    DanceSpriteTask *v5;

    v4 = (param5 == 0) ? param5 : (param5 - 1);

    v5 = &param0->spriteTasks[v4];

    if (v5->task != NULL) {
        SysTask_Done(v5->task);
    }

    MI_CpuClear8(v5, sizeof(DanceSpriteTask));

    v2 = Unk_contest_competition_022546CC[param5][0];
    v3 = Unk_contest_competition_022546CC[param5][1];

    v5->sprite = param0->judgeSprites[v4];

    ManagedSprite_SetAnim(v5->sprite, param3);
    ManagedSprite_SetPositionXYWithSubscreenOffset(v5->sprite, v2, v3, (256 * FX32_ONE));
    Sprite_TickFrame(v5->sprite->sprite);
    ManagedSprite_SetDrawFlag(v5->sprite, 1);

    for (v1 = 0; v1 < 3; v1++) {
        FontOAM_SetDrawFlag(param0->textLabels[v1][v4].fontOAM, 0);
    }

    v5->textLabel = &param0->textLabels[param3][v4];

    contest_competition_0223F2F8(v5->textLabel, v2, v3, 1);
    FontOAM_SetDrawFlag(v5->textLabel->fontOAM, 1);

    v5->task = SysTask_Start(contest_competition_0224A8D4, v5, ((30000 + 10000) + 200));
}

static void contest_competition_0224A8D4(SysTask *param0, void *param1)
{
    DanceSpriteTask *v0 = param1;
    int v1, v2;

    switch (v0->state) {
    case 0:
        FontOAM_GetXY(v0->textLabel->fontOAM, &v1, &v2);
        v2 += -4;
        FontOAM_SetXY(v0->textLabel->fontOAM, v1, v2);
        ManagedSprite_OffsetPositionXY(v0->sprite, 0, -4);

        v0->frame++;

        if (v0->frame > 4) {
            v0->frame = 0;

            v0->state++;
        }
        break;
    case 1:
        v0->frame++;

        if (v0->frame > 14) {
            v0->state++;
        }
        break;
    default:
        FontOAM_SetDrawFlag(v0->textLabel->fontOAM, 0);
        ManagedSprite_SetDrawFlag(v0->sprite, 0);
        v0->task = NULL;
        SysTask_Done(param0);
        return;
    }
}

void contest_competition_0224A95C(DanceCompetitionScene *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        if (param0->spriteTasks[v0].task != NULL) {
            SysTask_Done(param0->spriteTasks[v0].task);
            param0->spriteTasks[v0].task = NULL;
        }
    }
}

void contest_competition_0224A984(SpriteSystem *param0, SpriteManager *param1, NARC *param2)
{
    SpriteSystem_LoadCharResObjFromOpenNarc(param0, param1, param2, 64, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, 33008);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0, param1, param2, 65, TRUE, 33005);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0, param1, param2, 66, TRUE, 33005);
}

void contest_competition_0224A9D4(SpriteManager *param0)
{
    SpriteManager_UnloadCharObjById(param0, 33008);
    SpriteManager_UnloadCellObjById(param0, 33005);
    SpriteManager_UnloadAnimObjById(param0, 33005);
}

void contest_competition_0224A9F8(DanceCompetitionScene *param0, SpriteSystem *param1, SpriteManager *param2)
{
    ManagedSprite *v0 = SpriteSystem_NewSprite(param1, param2, &Unk_contest_competition_022547C8);
    Sprite_TickFrame(v0->sprite);

    param0->comboSprite = v0;
}

void contest_competition_0224AA1C(DanceCompetitionScene *param0)
{
    int v0, v1;

    if (param0->comboSprite != NULL) {
        Sprite_DeleteAndFreeResources(param0->comboSprite);
        param0->comboSprite = NULL;
    }
}

void contest_competition_0224AA38(DanceCompetition *param0)
{
    param0->scene.task = SysTask_Start(contest_competition_0224AA68, param0, (((30000 + 10000) + 100) + 10));
}

void contest_competition_0224AA58(DanceCompetition *param0)
{
    SysTask_Done(param0->scene.task);
}

static void contest_competition_0224AA68(SysTask *param0, void *param1)
{
    DanceCompetition *v0 = param1;
    int v1, v2, v3;

    v3 = v0->contest->data.playerContestantID;
    v1 = v0->scene.photoSprites[v3].x;
    v2 = v0->scene.photoSprites[v3].y;

    ManagedSprite_SetPositionXYWithSubscreenOffset(v0->scene.comboSprite, v1, v2 - 8 * 5, (256 * FX32_ONE));
}

void contest_competition_0224AA94(SpriteSystem *param0, SpriteManager *param1, NARC *param2)
{
    SpriteSystem_LoadCharResObjFromOpenNarc(param0, param1, param2, 90, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, 33010);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0, param1, param2, 89, TRUE, 33007);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0, param1, param2, 88, TRUE, 33007);
}

void contest_competition_0224AAE4(SpriteManager *param0)
{
    SpriteManager_UnloadCharObjById(param0, 33010);
    SpriteManager_UnloadCellObjById(param0, 33007);
    SpriteManager_UnloadAnimObjById(param0, 33007);
}

void contest_competition_0224AB08(DanceCompetitionScene *param0, SpriteSystem *param1, SpriteManager *param2)
{
    for (int i = 0; i < CONTEST_NUM_PARTICIPANTS; i++) {
        param0->moveIconTasks[i].sprite = SpriteSystem_NewSprite(param1, param2, &Unk_contest_competition_02254830);
        Sprite_TickFrame(param0->moveIconTasks[i].sprite->sprite);
        ManagedSprite_SetAffineOverwriteMode(param0->moveIconTasks[i].sprite, AFFINE_OVERWRITE_MODE_NORMAL);
        param0->moveIconTasks[i].index = i;
        param0->moveIconTasks[i].photoSprite = &param0->photoSprites[i];
        param0->moveIconTasks[i].yOffset = Pokemon_DPSpriteYOffset(param0->contestData->contestMons[i], 2);
        contest_competition_0224AC78(&param0->moveIconTasks[i], 1, 1);
        param0->moveIconTasks[i].task = SysTask_Start(contest_competition_0224ABFC, &param0->moveIconTasks[i], (((30000 + 10000) + 100) + 1000));
    }

    contest_competition_0224ABDC(param0, 0);
}

void contest_competition_0224ABB0(DanceCompetitionScene *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        Sprite_DeleteAndFreeResources(param0->moveIconTasks[v0].sprite);
        SysTask_Done(param0->moveIconTasks[v0].task);
        param0->moveIconTasks[v0].sprite = NULL;
    }
}

void contest_competition_0224ABDC(DanceCompetitionScene *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        ManagedSprite_SetDrawFlag(param0->moveIconTasks[v0].sprite, param1);
    }
}

static void contest_competition_0224ABFC(SysTask *param0, void *param1)
{
    DanceMoveIconTask *v0 = param1;
    int v1, v2, v3, v4;
    f32 v5;

    v1 = v0->photoSprite->x;
    v2 = v0->photoSprite->y;
    v3 = v0->photoSprite->z;

    {
        int v6;

        v6 = contest_competition_0224B06C(v3);
        v4 = (80 / 2 - v0->yOffset) * v6 / 0x100;
        v2 += v4;
        v5 = (100 * v6 / 0x100);
        v5 /= 100.0f;
    }

    if (v0->state == 0) {
        s16 v7, v8;

        Sprite_GetPositionXYWithSubscreenOffset2(v0->sprite, &v7, &v8, (256 * FX32_ONE));
        v2 = v8;
    }

    ManagedSprite_SetPositionXYWithSubscreenOffset(v0->sprite, v1, v2, (256 * FX32_ONE));
    ManagedSprite_SetAffineScale(v0->sprite, v5, v5);
}

void contest_competition_0224AC78(DanceMoveIconTask *param0, int param1, int param2)
{
    param0->contestantID = param1;
    param0->state = param2;
}

void contest_competition_0224AC80(SpriteSystem *param0, SpriteManager *param1, NARC *param2)
{
    SpriteSystem_LoadCharResObjFromOpenNarc(param0, param1, param2, 93, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, 33011);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0, param1, param2, 92, TRUE, 33008);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0, param1, param2, 91, TRUE, 33008);
}

void contest_competition_0224ACD0(SpriteManager *param0)
{
    SpriteManager_UnloadCharObjById(param0, 33011);
    SpriteManager_UnloadCellObjById(param0, 33008);
    SpriteManager_UnloadAnimObjById(param0, 33008);
}

void contest_competition_0224ACF4(DanceCompetitionScene *param0, SpriteSystem *param1, SpriteManager *param2)
{
    return;
}

void contest_competition_0224ACF8(DanceCompetitionScene *param0)
{
    return;
}

void contest_competition_0224ACFC(SpriteSystem *param0, SpriteManager *param1, NARC *param2)
{
    SpriteSystem_LoadCharResObjFromOpenNarc(param0, param1, param2, 96, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, 33012);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0, param1, param2, 95, TRUE, 33009);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0, param1, param2, 94, TRUE, 33009);
}

void contest_competition_0224AD4C(SpriteManager *param0)
{
    SpriteManager_UnloadCharObjById(param0, 33012);
    SpriteManager_UnloadCellObjById(param0, 33009);
    SpriteManager_UnloadAnimObjById(param0, 33009);
}

BOOL contest_competition_0224AD70(DanceCompetition *param0, int param1, int param2)
{
    ManagedSprite *v0;
    u32 v1, v2;
    DanceNoteTask *v3;
    int v4, v5, v6;

    v3 = param0->scene.noteTasks[param1];

    for (v4 = 0; v4 < 16; v4++) {
        if (v3->task == NULL) {
            break;
        }

        v3++;
    }

    if (v4 == 16) {
        return 0;
    }

    v0 = SpriteSystem_NewSprite(param0->scene.spriteSystem, param0->scene.spriteManager, &Unk_contest_competition_02254864);

    if (v0 == NULL) {
        return 0;
    }

    v5 = param0->scene.photoSprites[param1].x;
    v6 = param0->scene.photoSprites[param1].y;

    ManagedSprite_SetAnim(v0, param2);
    ManagedSprite_SetPositionXYWithSubscreenOffset(v0, v5, v6, (256 * FX32_ONE));
    Sprite_SetAnimateFlag(v0->sprite, 1);
    Sprite_TickFrame(v0->sprite);

    v1 = Contest_GetRNGNext(param0->contest);
    v2 = 0x500;

    CP_SetDiv32_32(v1, v2);
    MI_CpuClear8(v3, sizeof(DanceNoteTask));

    v3->sprite = v0;
    v3->x = v5 << 8;
    v3->y = v6 << 8;
    v3->velocityX = CP_GetDivRemainder32() + 0x0;

    if (v3->velocityX & 1) {
        v3->velocityX = -v3->velocityX;
    }

    v1 = Contest_GetRNGNext(param0->contest);
    v2 = 0xf00;

    CP_SetDivImm32_32(v1, v2);

    v3->velocityY = -(0x400 + CP_GetDivRemainder32());
    v3->task = SysTask_Start(contest_competition_0224AE84, v3, (30000 + 10000));

    return 1;
}

static void contest_competition_0224AE84(SysTask *param0, void *param1)
{
    DanceNoteTask *v0 = param1;
    s32 v1, v2;

    v0->x += v0->velocityX;
    v0->y += v0->velocityY;
    v0->velocityY += 0x200;
    v0->frame++;

    if ((v0->frame > 10) || (v0->x > ((256 + 16) << 8)) || (v0->x < ((-256 - 16) * 0x100)) || (v0->y > ((192 + 16) << 8))) {
        Sprite_DeleteAndFreeResources(v0->sprite);
        SysTask_Done(param0);
        v0->sprite = NULL;
        v0->task = NULL;
        return;
    }

    CP_SetDiv32_32(v0->x, 0x100);
    v1 = CP_GetDivResult32();

    CP_SetDivImm32_32(v0->y, 0x100);
    v2 = CP_GetDivResult32();

    ManagedSprite_SetPositionXYWithSubscreenOffset(v0->sprite, v1, v2, (256 * FX32_ONE));
}

static void contest_competition_0224AF3C(DanceCompetition *param0, int param1, int param2, int param3)
{
    int v0, v1, v2, v3, v4;

    if ((param2 == 2) || (param0->scoreState.scores[param1] == 0)) {
        return;
    }

    v3 = param0->scoreState.scores[param1];
    CP_SetDiv32_32(v3, 2);

    if (param3 == 0) {
        v1 = 0;
    } else {
        v1 = 1;
    }

    v4 = CP_GetDivResult32();

    if (v4 > 16) {
        v4 = 16;
    }

    for (v0 = 0; v0 < v4; v0++) {
        v2 = contest_competition_0224AD70(param0, param1, v1);

        if (v2 == 0) {
            break;
        }
    }
}

void contest_competition_0224AFA8(SpriteSystem *param0, SpriteManager *param1, NARC *param2)
{
    SpriteSystem_LoadCharResObjFromOpenNarc(param0, param1, param2, 99, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, 33013);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0, param1, param2, 98, TRUE, 33010);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0, param1, param2, 97, TRUE, 33010);
}

void contest_competition_0224AFF8(SpriteManager *param0)
{
    SpriteManager_UnloadCharObjById(param0, 33013);
    SpriteManager_UnloadCellObjById(param0, 33010);
    SpriteManager_UnloadAnimObjById(param0, 33010);
}

BOOL contest_competition_0224B01C(DanceCompetition *param0)
{
    DanceScoreTask *v1 = &param0->scene.scoreTask;
    ManagedSprite *v0 = SpriteSystem_NewSprite(param0->scene.spriteSystem, param0->scene.spriteManager, &Unk_contest_competition_0225472C);

    ManagedSprite_SetPositionXYWithSubscreenOffset(v0, -1, (0x16 * 8), (256 * FX32_ONE));
    Sprite_TickFrame(v0->sprite);
    ManagedSprite_SetDrawFlag(v0, 0);

    v1->sprite = v0;
    return 1;
}

void contest_competition_0224B058(DanceCompetition *param0)
{
    DanceScoreTask *v0 = &param0->scene.scoreTask;
    Sprite_DeleteAndFreeResources(v0->sprite);
}

void contest_competition_0224B068(DanceCompetitionScene *param0, int param1)
{
    return;
}

static int contest_competition_0224B06C(int param0)
{
    int v0;

    if (param0 == (-0x200 - 0x80)) {
        v0 = 0xc0;
    } else if (param0 == -0x200) {
        v0 = 0x100;
    } else {
        v0 = (param0 - (-0x200 - 0x80)) * (0x100 - 0xc0) / (-0x200 - (-0x200 - 0x80));
        v0 += 0xc0;
    }

    return v0;
}

void contest_competition_0224B09C(PokemonSprite *param0, DancePhotoSprite *param1)
{
    s32 v0 = param1->z;
    s32 v1 = contest_competition_0224B06C(v0);

    {
        fx32 v2;

        if (v1 == 0x100) {
            v2 = FX32_ONE;
        } else {
            v2 = FX32_ONE * v1 / 0x100;
        }

        PhotoSprite_SetScale(param1->photoSprite, v2, v2, FX32_ONE);
    }
}

void contest_competition_0224B0CC(DanceCompetitionScene *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        contest_competition_0224B09C(param0->pokemonSprites[v0], &param0->photoSprites[v0]);
    }
}

static BOOL contest_competition_0224B0E8(DanceCompetition *param0, int param1, const DancePacket *param2)
{
    int v0;
    int v1, v2, v3;
    int v4, v5;

    v4 = contest_competition_0223F0BC(param0->scoreState.contestRank, 3);
    v0 = (param2->contestantID == param1) ? 0 : 1;
    v1 = 256 / contest_competition_0223F0BC(param0->scoreState.contestRank, 4) * param2->moveSlot;
    v5 = (256 - v4) / 2;
    v1 += v5;
    v2 = Unk_contest_competition_022549BC[param2->contestantOrder];

    {
        s16 v6, v7;
        int v8;

        for (v8 = 0; v8 < (((16 * 2) / 2) * 4 + 4); v8++) {
            if (param0->scene.sprites[v8] != NULL) {
                Sprite_GetPositionXYWithSubscreenOffset2(param0->scene.sprites[v8], &v6, &v7, (256 * FX32_ONE));

                if ((v6 == v1) && (v7 == v2) && (ManagedSprite_GetActiveAnim(param0->scene.sprites[v8]) != 2)) {
                    return 0;
                }
            }
        }
    }

    contest_competition_0224A46C(&param0->scene, param0->scene.spriteSystem, param0->scene.spriteManager, v0, param2->judgeID, v1, v2, param2->contestantOrder);

    if ((param2->contestantOrder == 0) && (v0 == 1)) {
        v1 += 256 / 2 - v5;
        v2 = Unk_contest_competition_022549BC[param0->scoreState.judgeVotes[param0->contest->data.playerContestantID]];

        contest_competition_0224A46C(&param0->scene, param0->scene.spriteSystem, param0->scene.spriteManager, 2, param2->judgeID, v1, v2, param0->scoreState.judgeVotes[param0->contest->data.playerContestantID]);
    }

    return 1;
}

void contest_competition_0224B20C(DanceCompetition *param0, const DancePacket *param1)
{
    int v0, v1, v2;

    v1 = param1->contestantID;

    if (param0->contest->data.playerContestantID == param0->contest->data.leaderContestantID) {
        (void)0;
    }

    {
        switch (param1->turn) {
        case 0:
            v2 = 2;
            break;
        case 1:
            v2 = 2;
            break;
        case 2:
            v2 = 1;
            break;
        case 3:
            v2 = 1;
            break;
        default:
            v2 = 0;
            break;
        }

        param0->scoreState.scores[v1] += v2;
    }

    if (param1->contestantOrder == 0) {
        for (v0 = 0; v0 < 8; v0++) {
            if (param0->movePackets[v0].isValid == 0) {
                param0->movePackets[v0] = *param1;
                break;
            } else if (param0->movePackets[v0].moveSlot == param1->moveSlot) {
                break;
            }
        }

        if (v0 >= 8) {
            (void)0;
        }
    }

    if (param1->score == 0) {
        param0->scene.comboCount[param1->contestantID]++;
        param0->scene.noteCount[param1->contestantID]++;
    } else {
        param0->scene.comboCount[param1->contestantID] = 0;
        param0->scene.noteCount[param1->contestantID] = 0;
    }

    if (param1->score != 2) {
        param0->scene.hitCount[param1->contestantID]++;
    } else {
        param0->scene.missCount[param1->contestantID]++;
        param0->scene.hitCount[param1->contestantID] = 0;
    }

    if (param1->contestantOrder > 0) {
        switch (param1->score) {
        case 0:
            param0->scene.perfectCount++;
            break;
        case 1:
            param0->scene.goodCount++;
            break;
        case 2:
            param0->scene.badCount++;
            break;
        }
    }

    contest_competition_0224A7E0(&param0->scene, param0->scene.spriteSystem, param0->scene.spriteManager, param1->score, param1->contestantID, param1->contestantOrder);
    contest_competition_0224B0E8(param0, param0->contest->data.playerContestantID, param1);
    contest_competition_0224B528(param0, param1->contestantID, param1->contestantOrder, param1->judgeID, param1->isLastMove, param0->scoreState.scores[v1]);
    contest_competition_0224AF3C(param0, param1->contestantID, param1->score, param1->contestantOrder);
    contest_competition_0224C89C(param0, param1);

    if (param1->contestantID == param0->contest->data.playerContestantID) {
        if (param1->score == 0) {
            contest_competition_0224CB00(param0, param1->moveSlot, 1);
        } else if (param1->score == 1) {
            contest_competition_0224CB00(param0, param1->moveSlot, 0);
        }
    }

    if ((param1->contestantOrder == 0) && (param1->isLastMove == 1)) {
        if (param0->scene.noteCount[param1->contestantID] == param0->scoreState.roundCount) {
            contest_competition_0224CB80(param0, 1);
        } else if (param0->scene.missCount[param1->contestantID] == 0) {
            contest_competition_0224CB80(param0, 0);
        }
    } else if ((param1->contestantOrder > 0) && (param1->isLastMove == 1)) {
        if (param0->scoreState.roundCount * (4 - 1) == param0->scene.perfectCount + param0->scene.goodCount + param0->scene.badCount) {
            if (param0->scoreState.roundCount * (4 - 1) == param0->scene.perfectCount) {
                contest_competition_0224CB80(param0, 1);
            } else if (param0->scene.badCount == 0) {
                contest_competition_0224CB80(param0, 0);
            }
        }
    }

    if (param1->isLastMove == 1) {
        Sound_PlayEffect(SEQ_SE_DP_CON_028_sseq);
    } else {
        Sound_PlayEffect(SEQ_SE_DP_CON_027_3_sseq);
    }

    if ((param0->scene.playerContestantID == 0) || ((param0->scene.playerContestantID > 0) && ((param1->contestantOrder == 0) || (param1->contestantID == param0->contest->data.playerContestantID)))) {
        switch (param1->score) {
        case 0:
            if (param0->scene.noteCount[param1->contestantID] == param0->scoreState.roundCount) {
                Sound_PlayEffect(SEQ_SE_DP_CON_023_sseq);
            } else if (param0->scene.noteCount[param1->contestantID] == param0->scoreState.roundCount - 1) {
                Sound_PlayEffect(SEQ_SE_DP_CON_022_sseq);
            } else {
                Sound_PlayEffect(SEQ_SE_DP_CON_021_sseq);
            }
            break;
        case 1:
            Sound_PlayEffect(SEQ_SE_DP_CON_024_sseq);
            break;
        case 2:
            if (param1->isCombo == 1) {
                Sound_PlayEffect(SEQ_SE_DP_CON_026_sseq);
            } else {
                Sound_PlayEffect(SEQ_SE_DP_CARD10_sseq);
            }
            break;
        }
    }
}

static void contest_competition_0224B528(DanceCompetition *param0, int param1, int param2, int param3, int param4, int param5)
{
    int v0, v1;
    DanceContestant *v2 = &param0->contestants[param1];
    v1 = -1;

    for (v0 = v2->poseTimer; v0 < (16 * 2); v0++) {
        if (v2->name[v0] == 0) {
            v1 = v0;
            break;
        }
    }

    if (v1 == -1) {
        for (v0 = 0; v0 < v2->poseTimer; v0++) {
            if (v2->name[v0] == 0) {
                v1 = v0;
                break;
            }
        }
    }

    if (v1 == -1) {
        GF_ASSERT(FALSE);
        return;
    }

    v2->name[v1] = param3;
    v2->moveArg1 = param2;
    v2->moveArg2 = param4;
    v2->moveArg3 = param5;
}

void contest_competition_0224B59C(DanceCompetition *param0)
{
    param0->vBlankTask = SysTask_Start(contest_competition_0224B5F0, param0, ((30000 + 9000) + 10));
}

void contest_competition_0224B5B8(DanceCompetition *param0)
{
    SysTask_Done(param0->vBlankTask);
    param0->vBlankTask = NULL;
}

BOOL contest_competition_0224B5C8(DanceCompetition *param0)
{
    DanceContestant *v0;
    int v1;

    for (v1 = 0; v1 < 4; v1++) {
        v0 = &param0->contestants[v1];

        if (v0->name[v0->poseTimer] != 0) {
            return 0;
        }
    }

    return 1;
}

static void contest_competition_0224B5F0(SysTask *param0, void *param1)
{
    DanceCompetition *v0 = param1;
    DanceContestant *v1;
    int v2, v3, v4;
    u32 v5;

    for (v4 = 0; v4 < 4; v4++) {
        v1 = &v0->contestants[v4];
        v2 = v1->name[v1->poseTimer];
        v3 = 0;

        if (v2 == 0) {
            continue;
        }

        contest_competition_0224BD28(v0, v4, 4);

        v5 = v0->scoreState.maxScore / 10000;
        v5--;

        switch (v2) {
        case 1:
            if (v0->scene.contestantIsHuman[v4] == 1) {
                v3 = contest_competition_0224B7BC(&v1->moveData, v0->scene.pokemonSprites[v4], &v0->scene.photoSprites[v4], v1->moveArg1, v1->moveArg2, v1->moveArg3, &v0->scene.moveIconTasks[v4], v5);
            } else {
                v3 = contest_competition_0224B8D0(&v1->moveData, v0->scene.pokemonSprites[v4], &v0->scene.photoSprites[v4], v1->moveArg1, v1->moveArg2, v1->moveArg3, 0, v5);
            }
            break;
        case 2:
            v3 = contest_competition_0224B8D0(&v1->moveData, v0->scene.pokemonSprites[v4], &v0->scene.photoSprites[v4], v1->moveArg1, v1->moveArg2, v1->moveArg3, 1, v5);
            break;
        case 3:
            v3 = contest_competition_0224BA50(&v1->moveData, v0->scene.pokemonSprites[v4], &v0->scene.photoSprites[v4], v1->moveArg1, v1->moveArg2, v1->moveArg3, 1, v5);
            break;
        case 4:
            v3 = contest_competition_0224BA50(&v1->moveData, v0->scene.pokemonSprites[v4], &v0->scene.photoSprites[v4], v1->moveArg1, v1->moveArg2, v1->moveArg3, 0, v5);
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }

        if (v3 == 1) {
            v1->name[v1->poseTimer] = 0;
            v1->poseTimer++;

            if (v1->poseTimer >= (16 * 2)) {
                v1->poseTimer = 0;
            }

            MI_CpuClear8(&v1->moveData, sizeof(DanceMoveData));
            contest_competition_0224BD28(v0, v4, 3);
        }
    }
}

static inline void inline_contest_competition_0224B7BC(DanceMoveData *param0, PokemonSprite *param1, DancePhotoSprite *param2, int param3, int param4, int param5)
{
    s32 v0, v1, v2, v3;
    s32 v4, v5;

    if (param3 == 0) {
        v4 = 100;
    } else {
        v4 = 40;
    }

    if (1) {
        v5 = (2 << 8) * param4;

        if (v5 > (100 << 8)) {
            v5 = (100 << 8);
        }

        v4 += v5 >> 8;
    }

    v0 = param0->savedX - param0->startX;
    v1 = param0->currentY - param0->targetY;

    v0 = v0 * v4 / 100;
    v1 = v1 * v4 / 100;

    v2 = param0->startX + v0;
    v3 = param0->targetY + v1;

    param2->x = v2 / 0x100;
    param2->y = v3 / 0x100;

    PhotoSprite_MoveTo(param2->photoSprite, param2->x, param2->y);
}

static BOOL contest_competition_0224B7BC(DanceMoveData *param0, PokemonSprite *param1, DancePhotoSprite *param2, int param3, int param4, int param5, DanceMoveIconTask *param6, u32 param7)
{
    BOOL v0 = 0;

    switch (param0->state) {
    case 0:
        param0->startX = param2->x * 0x100;
        param0->targetY = param2->y * 0x100;
        param0->savedX = param0->startX;
        param0->currentY = param0->targetY;

        {
            int v1;

            v1 = 0x500 / (param7 / 2);

            if (param4 == 1) {
                param0->bounce.velocity = -0x500 * 200 / 100;
                param0->bounce.acceleration = v1 * 200 / 100;
            } else {
                param0->bounce.velocity = -0x500;
                param0->bounce.acceleration = v1;
            }
        }

        contest_competition_0224AC78(param6, 1, 0);
        param0->state++;

    case 1:
        param0->currentY += param0->bounce.velocity;
        param0->bounce.velocity += param0->bounce.acceleration;

        if (param0->currentY >= param0->targetY) {
            param0->currentY = param0->targetY;
            contest_competition_0224AC78(param6, 1, 1);
            v0 = 1;
            param0->state++;
        }
        break;
    default:
        return 1;
    }

    inline_contest_competition_0224B7BC(param0, param1, param2, param3, param5, param4);
    return v0;
}

static BOOL contest_competition_0224B8D0(DanceMoveData *param0, PokemonSprite *param1, DancePhotoSprite *param2, int param3, int param4, int param5, int param6, u32 param7)
{
    BOOL v0 = 0;
    s32 v1;

    switch (param0->state) {
    case 0:
        param0->startX = param2->x * 0x100;
        param0->targetY = param2->y * 0x100;
        param0->savedX = param0->startX;
        param0->currentY = param0->targetY;

        {
            int v2, v3;

            v2 = param7 * 30 / 100;
            v3 = param7 - v2;

            param0->slide.velocity1 = 16 * 0x100 / v2;
            param0->slide.velocity2 = 16 * 0x100 / v3;

            if (param6 == 0) {
                param0->slide.velocity1 *= -1;
                param0->slide.velocity2 *= -1;
            }
        }

        param0->state++;
    case 1:
        if (param4 == 1) {
            param0->currentY += param0->slide.velocity1 * 200 / 100;
            v1 = 16 * 200 / 100;
        } else {
            param0->currentY += param0->slide.velocity1;
            v1 = 16;
        }

        if (abs(param0->currentY - param0->targetY) >= v1 * 0x100) {
            if (param6 == 1) {
                param0->currentY = param0->targetY + v1 * 0x100;
            } else {
                param0->currentY = param0->targetY - v1 * 0x100;
            }

            param0->state++;
        }
        break;
    case 2:
        if (param4 == 1) {
            param0->currentY -= param0->slide.velocity2 * 200 / 100;
        } else {
            param0->currentY -= param0->slide.velocity2;
        }

        if (((param6 == 1) && (param0->currentY <= param0->targetY)) || ((param6 == 0) && (param0->currentY >= param0->targetY))) {
            param0->currentY = param0->targetY;
            param0->state++;
            v0 = 1;
        }
        break;
    default:
        return 1;
    }

    inline_contest_competition_0224B7BC(param0, param1, param2, param3, param5, param4);
    return v0;
}

static BOOL contest_competition_0224BA50(DanceMoveData *param0, PokemonSprite *param1, DancePhotoSprite *param2, int param3, int param4, int param5, int param6, u32 param7)
{
    BOOL v0 = 0;
    s32 v1;

    switch (param0->state) {
    case 0:
        param0->startX = param2->x * 0x100;
        param0->targetY = param2->y * 0x100;
        param0->savedX = param0->startX;
        param0->currentY = param0->targetY;

        {
            int v2, v3;

            v2 = param7 * 30 / 100;
            v3 = param7 - v2;

            param0->arc.angleVelocity1 = (65536 / 360 * 5 * 0x100) / v2;
            param0->arc.angleVelocity2 = -(65536 / 360 * 5 * 0x100) / v3;
            param0->arc.xVelocity = 16 * 0x100 / v2;
            param0->arc.yVelocity = -(16 * 0x100 / v3);

            if (param6 == 1) {
                param0->arc.angleVelocity1 *= -1;
                param0->arc.angleVelocity2 *= -1;
                param0->arc.xVelocity *= -1;
                param0->arc.yVelocity *= -1;
            }
        }

        param0->state++;
    case 1:
        if (param4 == 1) {
            param0->savedX += param0->arc.xVelocity * 200 / 100;
            v1 = 16 * 200 / 100;
            param0->arc.angle += param0->arc.angleVelocity1 * 200 / 100;
        } else {
            param0->savedX += param0->arc.xVelocity;
            v1 = 16;
            param0->arc.angle += param0->arc.angleVelocity1;
        }

        if (abs(param0->savedX - param0->startX) >= v1 * 0x100) {
            if (param6 == 1) {
                param0->savedX = param0->startX - v1 * 0x100;
            } else {
                param0->savedX = param0->startX + v1 * 0x100;
            }

            param0->currentY = param0->targetY;
            param0->state++;
        }
        break;
    case 2:
        if (param4 == 1) {
            param0->savedX += param0->arc.yVelocity * 200 / 100;
            param0->arc.angle += param0->arc.angleVelocity2 * 200 / 100;
        } else {
            param0->savedX += param0->arc.yVelocity;
            param0->arc.angle += param0->arc.angleVelocity2;
        }

        if (((param6 == 1) && (param0->savedX >= param0->startX)) || ((param6 == 0) && (param0->savedX <= param0->startX))) {
            param0->savedX = param0->startX;
            param0->arc.angle = 0;
            param0->state++;
            v0 = 1;
        }
        break;
    default:
        return 1;
    }

    PhotoSprite_SetRotation(param2->photoSprite, param0->arc.angle / 0x100);
    inline_contest_competition_0224B7BC(param0, param1, param2, param3, param5, param4);
    return v0;
}

void contest_competition_0224BC4C(DanceCompetition *param0)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        param0->movePackets[v0].isValid = 0;
    }
}

void contest_competition_0224BC68(DanceCompetition *param0, int param1, int param2)
{
    GF_ASSERT(param0->contestantSprites[param1].task == NULL);
    MI_CpuClear8(&param0->contestantSprites[param1], sizeof(DanceContestantSprite));

    param0->contestantSprites[param1].competition = param0;
    param0->contestantSprites[param1].contestantID = param1;
    param0->contestantSprites[param1].param = param2;
    param0->contestantSprites[param1].sprite = param0->scene.pokemonSprites[param1];
    param0->contestantSprites[param1].photoSprite = &param0->scene.photoSprites[param1];
    param0->contestantSprites[param1].flag2 = 1;
    param0->contestantSprites[param1].flag3 = 1;
    param0->contestantSprites[param1].task = SysTask_Start(contest_competition_0224BE50, &param0->contestantSprites[param1], (30000 + 9000));
}

void contest_competition_0224BD00(DanceCompetition *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->contestantSprites[v0].task != NULL) {
            SysTask_Done(param0->contestantSprites[v0].task);
            param0->contestantSprites[v0].task = NULL;
        }
    }
}

void contest_competition_0224BD28(DanceCompetition *param0, int param1, int param2)
{
    if (param0->contestantSprites[param1].task == NULL) {
        return;
    }

    switch (param2) {
    case 0:
        param0->contestantSprites[param1].flag5 = 0;
        param0->contestantSprites[param1].flag4 = 0;
        break;
    case 1:
        param0->contestantSprites[param1].flag5 = 1;
        break;
    case 2:
        param0->contestantSprites[param1].flag4 = 1;
        break;
    case 3:
        param0->contestantSprites[param1].flag1 = 0;
        param0->contestantSprites[param1].flag0 = 0;
        param0->contestantSprites[param1].flag2 = 1;
        break;
    case 4:
        if (param0->contestantSprites[param1].flag1 == 0) {
            param0->contestantSprites[param1].flag1 = 1;

            if (param0->contestantSprites[param1].flag2 == 0) {
                param0->contestantSprites[param1].prevRotation = param0->contestantSprites[param1].rotation;
            }
        }
        break;
    case 5:
        param0->contestantSprites[param1].flag0 = 1;
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

int contest_competition_0224BDF0(DanceCompetition *param0, int param1)
{
    if (param0->contestantSprites[param1].task == NULL) {
        return 1;
    }

    if ((param0->contestantSprites[param1].flag5 == 1) || (param0->contestantSprites[param1].param == 0)) {
        return 1;
    }

    return 0;
}

int contest_competition_0224BE24(DanceCompetition *param0, int param1)
{
    if (param0->contestantSprites[param1].task == NULL) {
        return 1;
    }

    if (param0->contestantSprites[param1].flag1 == 1) {
        return 1;
    }

    return 0;
}

static void contest_competition_0224BE50(SysTask *param0, void *param1)
{
    DanceContestantSprite *v0 = param1;

    contest_competition_0224BE64(v0);
    contest_competition_0224BF58(v0);
}

static void contest_competition_0224BE64(DanceContestantSprite *param0)
{
    u64 v0, v1;
    u32 v2;
    int v3, v4;

    if ((param0->flag5 == 1) || (param0->param == 0)) {
        return;
    }

    v0 = param0->competition->timestamp;
    v0 *= 10000;
    v0 %= param0->competition->scoreState.maxScore;
    v1 = v0 * 0x2000 / (param0->competition->scoreState.maxScore / 2);
    v3 = 1;

    if (v0 >= (param0->competition->scoreState.maxScore / 2)) {
        v1 = 0x2000 - (v1 - 0x2000);
        v3 = 0;
    }

    v2 = param0->moveOffsetX;
    v4 = param0->flag6;

    param0->moveOffsetX = (-0x200 - 0x80) * 0x100 + v1;
    param0->flag6 = v3;

    if (param0->flag4 == 1) {
        if ((param0->moveOffsetX == (-0x200 - 0x80) * 0x100) || (v4 == 0) && (v3 == 1)) {
            param0->moveOffsetX = (-0x200 - 0x80) * 0x100;
            param0->flag4 = 0;
            param0->flag5 = 1;
        }
    }

    param0->photoSprite->z = param0->moveOffsetX / 0x100;
    contest_competition_0224B09C(param0->sprite, param0->photoSprite);
}

static void contest_competition_0224BF58(DanceContestantSprite *param0)
{
    u32 v0;
    s32 v1, v2;
    u64 v3, v4;

    v0 = param0->rotation;
    v3 = param0->competition->timestamp;
    v3 *= 10000;
    v3 %= param0->competition->scoreState.maxScore * 2;
    v4 = v3 * 360 / (param0->competition->scoreState.maxScore * 2);
    v4 <<= 8;

    param0->rotation = v4;

    if (param0->flag1 > 0) {
        return;
    }

    if (param0->flag3 == 1) {
        v0 = v4;
        param0->flag3 = 0;
    }

    if (param0->flag2 == 1) {
        u32 v5;
        u32 v6, v7;

        if (v0 > v4) {
            v5 = v0 + v4;
        } else {
            v5 = v4;
        }

        v6 = param0->prevRotation;
        v7 = v0;

        if ((param0->prevRotation == v4) || ((v7 <= v6) && (v6 <= v5)) || ((param0->prevRotation <= v4) && (v0 > v4))) {
            param0->flag2 = 0;
        } else {
            return;
        }
    }

    if (param0->flag0 == 1) {
        if ((v4 == 0) || (v0 > v4)) {
            v4 = 0;
            param0->flag0 = 0;
            param0->flag1 = 1;
            param0->prevRotation = v4;
        }
    }

    v2 = (param0->param == 0) ? 3 : 3;
    v1 = CalcCosineDegrees(param0->rotation >> 8) * v2 / FX32_ONE;

    param0->photoSprite->x = v1 + Unk_contest_competition_022546F4[param0->param][0] - v2;
    PhotoSprite_MoveTo(param0->photoSprite->photoSprite, param0->photoSprite->x, param0->photoSprite->y);
}

static void contest_competition_0224C0C0(DanceCompetition *param0, int param1, const DanceMessageArgs *param2)
{
    u32 messageID;

    if (param1 != 0) {
        GF_ASSERT(param2 != NULL);
    }

    switch (param1) {
    case 0:
        break;
    case 1:
        StringTemplate_SetNickname(param0->scene.stringTemplate, 0, Pokemon_GetBoxPokemon(param0->scene.contestData->contestMons[param2->contestantID]));
        break;
    case 2:
        messageID = Contest_GetContestRankTitleMessageID(param0->contest->data.contestRank, param0->contest->data.competitionType, param0->contest->isLinkContest);
        StringTemplate_SetContestRankName(param0->scene.stringTemplate, 0, messageID);
        break;
    case 3:
        StringTemplate_SetNumber(param0->scene.stringTemplate, 0, param2->moveSlot, 1, 0, 1);
        break;
    case 4:
        StringTemplate_SetString(param0->scene.stringTemplate, 0, param0->contest->data.trainerNames[param2->contestantID], param0->contest->data.trainerGenders[param2->contestantID], 1, GAME_LANGUAGE);
        StringTemplate_SetNickname(param0->scene.stringTemplate, 1, Pokemon_GetBoxPokemon(param0->scene.contestData->contestMons[param2->contestantID]));
        break;
    case 5:
        StringTemplate_SetNickname(param0->scene.stringTemplate, 0, Pokemon_GetBoxPokemon(param0->scene.contestData->contestMons[param2->contestantID]));
        StringTemplate_SetNumber(param0->scene.stringTemplate, 1, param2->moveSlot, 1, 0, 1);
        break;
    case 6:
        messageID = Contest_GetContestRankTitleMessageID(param0->contest->data.contestRank, param0->contest->data.competitionType, param0->contest->isLinkContest);
        StringTemplate_SetContestRankName(param0->scene.stringTemplate, 0, messageID);
        StringTemplate_SetNumber(param0->scene.stringTemplate, 1, param2->moveSlot, 1, 0, 1);
        StringTemplate_SetString(param0->scene.stringTemplate, 2, param0->contest->data.trainerNames[param2->contestantID], param0->contest->data.trainerGenders[param2->contestantID], 1, GAME_LANGUAGE);
        StringTemplate_SetNickname(param0->scene.stringTemplate, 3, Pokemon_GetBoxPokemon(param0->scene.contestData->contestMons[param2->contestantID]));
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

static void contest_competition_0224C244(DanceCompetition *param0, MessageLoader *messageLoader, u32 messageID, int param3, const DanceMessageArgs *param4)
{
    String *message;
    int textDelay;

    if (param0->contest->isLinkContest == FALSE) {
        textDelay = Options_TextFrameDelay(param0->contest->options);
    } else {
        textDelay = TEXT_SPEED_FAST;
    }

    message = MessageLoader_GetNewString(messageLoader, messageID);
    contest_competition_0224C0C0(param0, param3, param4);

    StringTemplate_Format(param0->scene.stringTemplate, param0->scene.danceMessage, message);
    Window_FillTilemap(&param0->scene.windows[0], 0xff);

    param0->scene.printerID = Text_AddPrinterWithParams(&param0->scene.windows[0], FONT_MESSAGE, param0->scene.danceMessage, 0, 0, textDelay, NULL);
    String_Free(message);
}

void contest_competition_0224C2CC(DanceCompetition *param0, u32 param1, const DanceMessageArgs *param2)
{
    u32 messageID, v1;

    GF_ASSERT(param1 < NELEMS(Unk_contest_competition_0225470C));

    messageID = Unk_contest_competition_0225470C[param1].danceMessageID;
    v1 = Unk_contest_competition_0225470C[param1].unused_02;

    contest_competition_0224C244(param0, param0->scene.danceMessageLoader, messageID, v1, param2);
}

int contest_competition_0224C300(DanceCompetition *param0)
{
    return Text_IsPrinterActive(param0->scene.printerID);
}

void contest_competition_0224C310(SpriteSystem *param0, SpriteManager *param1, NARC *param2)
{
    SpriteSystem_LoadCharResObjFromOpenNarc(param0, param1, param2, 76, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, 33009);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0, param1, param2, 77, TRUE, 33006);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0, param1, param2, 78, TRUE, 33006);
}

void contest_competition_0224C360(SpriteManager *param0)
{
    SpriteManager_UnloadCharObjById(param0, 33009);
    SpriteManager_UnloadCellObjById(param0, 33006);
    SpriteManager_UnloadAnimObjById(param0, 33006);
}

void contest_competition_0224C384(DanceCompetition *param0, SpriteSystem *param1, SpriteManager *param2)
{
    DanceComboTask *v0;

    GF_ASSERT(param0->scene.comboTask == NULL);

    v0 = Heap_Alloc(HEAP_ID_23, sizeof(DanceComboTask));
    MI_CpuClear8(v0, sizeof(DanceComboTask));

    param0->scene.comboTask = v0;

    v0->competition = param0;
    v0->sprite = SpriteSystem_NewSprite(param0->scene.spriteSystem, param0->scene.spriteManager, &Unk_contest_competition_022547FC);

    Sprite_TickFrame(v0->sprite->sprite);
    ManagedSprite_SetDrawFlag(v0->sprite, 0);

    v0->task = SysTask_Start(contest_competition_0224C414, v0, ((30000 + 10000) + 15));
}

void contest_competition_0224C3E4(DanceCompetition *param0)
{
    SysTask_Done(param0->scene.comboTask->task);
    Sprite_DeleteAndFreeResources(param0->scene.comboTask->sprite);
    Heap_Free(param0->scene.comboTask);

    param0->scene.comboTask = NULL;
}

static void contest_competition_0224C414(SysTask *param0, void *param1)
{
    DanceComboTask *v0 = param1;

    switch (v0->state) {
    case 0:
        v0->state++;
        break;
    case 1:
        break;
    case 2:
        break;
    }

    Sprite_TickFrame(v0->sprite->sprite);
}

void contest_competition_0224C434(DanceScoreTask *param0, u32 param1, u32 param2, int param3)
{
    u32 v0;
    int v1 = contest_competition_0223F0BC(param3, 3);
    int v2 = (256 - v1) / 2;
    v0 = param1 * v1 / param2;

    ManagedSprite_SetPositionXYWithSubscreenOffset(param0->sprite, v0 - 1 + v2, (0x16 * 8), (256 * FX32_ONE));
    ManagedSprite_SetDrawFlag(param0->sprite, 1);
}

void contest_competition_0224C47C(DanceScoreTask *param0, int param1)
{
    ManagedSprite_SetPositionXYWithSubscreenOffset(param0->sprite, -1, (0x16 * 8), (256 * FX32_ONE));
    ManagedSprite_SetDrawFlag(param0->sprite, param1);
}

void contest_competition_0224C49C(DanceComboTask *param0, u32 param1, u32 param2, int param3)
{
    u32 v0, v1, v2;
    int v3, v4, v5;
    int v6, v7;

    v6 = contest_competition_0223F0BC(param3, 3);
    v0 = param1 * v6 / param2;

    if (param3 == 0) {
        v1 = (v6 * 10000) / contest_competition_0223F0BC(param3, 1);
    } else {
        v1 = (v6 * 10000) / 8;
    }

    v2 = (v0 * 10000) % v1;
    v5 = 180 * v2 / v1;
    v7 = (256 - v6) / 2;
    v3 = v0 + v7;
    v4 = (0x12 * 8);
    v4 -= CalcSineDegrees(v5) * 10 / FX32_ONE;

    ManagedSprite_SetPositionXYWithSubscreenOffset(param0->sprite, v3, v4, (256 * FX32_ONE));
    ManagedSprite_SetDrawFlag(param0->sprite, 1);
}

void contest_competition_0224C540(DanceComboTask *param0)
{
    ManagedSprite_SetDrawFlag(param0->sprite, 0);
}

void contest_competition_0224C54C(DanceComboTask *param0, int param1)
{
    int v0 = contest_competition_0223F0BC(param1, 3);
    int v1 = (256 - v0) / 2;

    ManagedSprite_SetDrawFlag(param0->sprite, 1);
    ManagedSprite_SetPositionXYWithSubscreenOffset(param0->sprite, v1, (0x12 * 8), (256 * FX32_ONE));
}

int contest_competition_0224C57C(enum PokemonContestRank contestRank)
{
    const u8 v0[] = { 3, 3, 4, 4 };

    GF_ASSERT(NELEMS(v0) - 1 == 3);
    return v0[contestRank];
}

void contest_competition_0224C5A0(DanceCompetition *param0, u32 param1, const DanceMessageArgs *param2)
{
    u32 v1;

    GF_ASSERT(param1 < NELEMS(Unk_contest_competition_0225470C));

    if (param0->isReady == 1) {
        return;
    }

    Window_DrawMessageBoxWithScrollCursor(&param0->scene.windows[1], 1, 1, 14);
    Bg_ScheduleTilemapTransfer(param0->scene.bgConfig, 1);

    u32 messageID = Unk_contest_competition_0225470C[param1].danceMessageID;
    v1 = Unk_contest_competition_0225470C[param1].unused_02;
    String *message = MessageLoader_GetNewString(param0->scene.danceMessageLoader, messageID);

    contest_competition_0224C0C0(param0, v1, param2);

    StringTemplate_Format(param0->scene.stringTemplate, param0->scene.danceMessage, message);
    Window_FillTilemap(&param0->scene.windows[1], 0xff);
    Text_AddPrinterWithParams(&param0->scene.windows[1], FONT_MESSAGE, param0->scene.danceMessage, 0, 0, TEXT_SPEED_INSTANT, NULL);
    String_Free(message);

    param0->isReady = 1;
}

void contest_competition_0224C640(DanceCompetition *param0)
{
    Window_EraseMessageBox(&param0->scene.windows[1], 1);
    Bg_ScheduleTilemapTransfer(param0->scene.bgConfig, 1);
    param0->isReady = 0;
}

s64 contest_competition_0224C660(DanceCompetition *param0, const DanceMoveDefinition *param1, int param2)
{
    s64 v0;

    v0 = (param0->scoreState.scorePerBeat * param1->duration) * param2;
    v0 += ((param0->scoreState.bonus1 + param0->scoreState.bonus2) * param2 + param0->scoreState.bonus1) / 10000;

    return v0 - param0->timestamp;
}

s64 contest_competition_0224C6A8(DanceCompetition *param0, const DanceMoveDefinition *param1, int param2)
{
    s64 v0;

    v0 = contest_competition_0224C660(param0, param1, param2);
    return v0;
}

void contest_competition_0224C6B0(DanceCompetition *param0, int param1, u8 *param2)
{
    DanceMoveIconMoveTask *v0;

    *param2 = 0;

    v0 = Heap_Alloc(HEAP_ID_23, sizeof(DanceMoveIconMoveTask));
    MI_CpuClear8(v0, sizeof(DanceMoveIconMoveTask));

    v0->unk_00 = param0;
    v0->unk_04 = &param0->scene.photoSprites[param1];
    v0->unk_08 = &param0->scene.moveIconTasks[param1];
    v0->unk_0C = param2;

    if (param0->scene.contestantIsHuman[param1] == 1) {
        SysTask_Start(contest_competition_0224C718, v0, (30000 + 10000));
    } else {
        SysTask_Start(contest_competition_0224C7B8, v0, (30000 + 10000));
    }
}

static void contest_competition_0224C718(SysTask *param0, void *param1)
{
    DanceMoveIconMoveTask *v0 = param1;

    switch (v0->unk_10) {
    case 0:
        contest_competition_0224AC78(v0->unk_08, 1, 0);
        v0->unk_1C = v0->unk_04->y * 0x100;
        v0->unk_18 = v0->unk_1C;
        v0->unk_14 = 0x500;
        v0->unk_10++;
    case 1:
        v0->unk_18 -= v0->unk_14;
        v0->unk_14 -= 0x200;

        if (v0->unk_18 >= v0->unk_1C) {
            v0->unk_18 = v0->unk_1C;
            v0->unk_11++;

            if (v0->unk_11 > 1) {
                v0->unk_10++;
            } else {
                v0->unk_10 = 0;
            }
        }

        v0->unk_04->y = v0->unk_18 / 0x100;
        PhotoSprite_MoveTo(v0->unk_04->photoSprite, v0->unk_04->x, v0->unk_04->y);
        break;
    default:
        *(v0->unk_0C) = 1;
        contest_competition_0224AC78(v0->unk_08, 1, 1);
        Heap_Free(param1);
        SysTask_Done(param0);
        return;
    }
}

static void contest_competition_0224C7B8(SysTask *param0, void *param1)
{
    DanceMoveIconMoveTask *v0 = param1;
    s32 v1;
    fx32 v2;

    switch (v0->unk_10) {
    case 0:
        v0->unk_28 = v0->unk_04->x * 0x100;
        v0->unk_24 = v0->unk_28;
        v0->unk_10++;
    case 1:
        v1 = CalcSineDegrees_FX32(v0->unk_20) * 4 / FX32_ONE;
        v2 = v0->unk_20;
        v0->unk_20 += (50 << FX32_SHIFT);

        if ((v0->unk_20 >> FX32_SHIFT) >= 360) {
            v0->unk_11++;

            if (v0->unk_11 > 5) {
                v0->unk_24 = v0->unk_28;
                v1 = 0;
                v0->unk_10++;
            }
        }

        v0->unk_04->x = v0->unk_24 / 0x100 + v1;
        PhotoSprite_MoveTo(v0->unk_04->photoSprite, v0->unk_04->x, v0->unk_04->y);
        break;
    default:
        *(v0->unk_0C) = 1;
        Heap_Free(param1);
        SysTask_Done(param0);
        return;
    }
}

void contest_competition_0224C848(DanceCompetition *param0)
{
    return;
}

void contest_competition_0224C84C(void)
{
    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG0, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 0, 0);
}

void contest_competition_0224C864(DanceCompetition *param0, int param1)
{
    u16 *v0 = PaletteData_GetUnfadedBuffer(param0->scene.paletteData, 0);
    BlendPalettes(v0, param0->savedData.data, (0x1fff ^ ((1 << 4) | (1 << 3) | (1 << 2))), Unk_contest_competition_022546DC[param1].unk_02, Unk_contest_competition_022546DC[param1].unk_00);
}

void contest_competition_0224C89C(DanceCompetition *param0, const DancePacket *param1)
{
    int v0;

    if (param1->contestantOrder != 0) {
        return;
    }

    switch (param1->score) {
    case 0:
    case 1:
        switch (param1->judgeID) {
        case 1:
            v0 = 1;
            break;
        case 2:
            v0 = 2;
            break;
        case 3:
            v0 = 3;
            break;
        case 4:
            v0 = 4;
            break;
        }
        break;
    case 2:
    default:
        v0 = 5;
        break;
    }

    contest_competition_0224C864(param0, v0);
}

void contest_competition_0224C8E8(DanceCompetition *param0, u32 param1)
{
    int v0;
    u32 v1;
    u32 v2 = param0->scoreState.maxScore >> 1;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->movePackets[v0].isValid == 1) {
            v1 = (param0->movePackets[v0].moveSlot + contest_competition_0223F0BC(param0->scoreState.contestRank, 4) / 2) * v2;
            CP_SetDiv32_32(v1, 10000);
            v1 = CP_GetDivResult32();

            if (v1 == param1) {
                contest_competition_0224C89C(param0, &param0->movePackets[v0]);
                return;
            }
        }
    }
}

void contest_competition_0224C9A4(DanceCompetition *param0)
{
    DanceBeatTask *v0;

    GF_ASSERT(param0->scene.beatTask.task == NULL);

    v0 = &param0->scene.beatTask;
    v0->competition = param0;
    v0->task = SysTask_Start(contest_competition_0224CA28, v0, (30000 + 10000));
}

void contest_competition_0224C9D4(DanceCompetition *param0)
{
    if (param0->scene.beatTask.task == NULL) {
        return;
    }

    SysTask_Done(param0->scene.beatTask.task);
    param0->scene.beatTask.task = NULL;
}

void contest_competition_0224C9F0(DanceCompetition *param0, int param1)
{
    DanceBeatTask *v0 = &param0->scene.beatTask;
    GF_ASSERT(v0->task != NULL);

    if (param1 == 0) {
        v0->state = 4 * 16;
    } else {
        v0->state = 3 * 16;
    }

    v0->flag = 1;
    v0->beat = (10 << 8);

    Sound_PlayEffect(SEQ_SE_DP_CON_031_sseq);
}

static void contest_competition_0224CA28(SysTask *param0, void *param1)
{
    DanceBeatTask *v0 = param1;

    if (v0->flag == 0) {
        return;
    }

    {
        u16 *v1;

        v1 = PaletteData_GetUnfadedBuffer(v0->competition->scene.paletteData, 0);
        BlendPalette(&v1[v0->state], &v0->competition->savedData.data[v0->state], 16, v0->beat >> 8, 0x7fff);
    }

    if (v0->beat == 0) {
        v0->flag = 0;
    } else if (v0->beat > 0x100) {
        v0->beat -= 0x100;
    } else {
        v0->beat = 0;
    }
}

void contest_competition_0224CA90(DanceCompetition *param0, u32 param1, s32 param2, s32 param3, s32 param4, fx32 param5)
{
    param0->camera.x = param2;
    param0->camera.y = param3;
    param0->camera.z = param4;
    param0->camera.angle = param5;

    ParticleSystem_CreateEmitterWithCallback(param0->particleSystem, param1, contest_competition_0224CAC0, param0);
}

static void contest_competition_0224CAC0(SPLEmitter *param0)
{
    DanceCompetition *v0 = ParticleSystem_GetEmitterCallbackParam();
    DanceCamera *v1 = &v0->camera;

    SPLEmitter_SetPosX(param0, v1->x);
    SPLEmitter_SetPosY(param0, v1->y);
    SPLEmitter_SetPosZ(param0, v1->z);

    ParticleSystem_SetEmitterEmissionCount(param0, v1->angle);
}

static void contest_competition_0224CB00(DanceCompetition *param0, int param1, int param2)
{
    s32 v0 = Unk_contest_competition_022546C4[param0->scoreState.contestRank][param1];

    if (param2 == 0) {
        contest_competition_0224CA90(param0, 0, v0, -17700, -5248, FX32_ONE);
        contest_competition_0224CA90(param0, 1, v0, -17700, -5248, FX32_ONE);
    } else {
        contest_competition_0224CA90(param0, 2, v0, -17700, -5248, FX32_ONE);
        contest_competition_0224CA90(param0, 3, v0, -17700, -5248, FX32_ONE);
    }
}

static void contest_competition_0224CB80(DanceCompetition *param0, int param1)
{
    fx32 v0 = FX32_ONE;

    if (param1 == 0) {
        contest_competition_0224CA90(param0, 5, -13000, -6300, -5248, v0);
        contest_competition_0224CA90(param0, 6, -13000, -6300, -5248, v0);
        contest_competition_0224CA90(param0, 7, -13000, -6300, -5248, v0);

        contest_competition_0224CA90(param0, 5, (13000 + 7500), -6300, -5248, v0);
        contest_competition_0224CA90(param0, 6, (13000 + 7500), -6300, -5248, v0);
        contest_competition_0224CA90(param0, 7, (13000 + 7500), -6300, -5248, v0);
    } else {
        contest_competition_0224CA90(param0, 8, (-13000 - 4000), -6300, -5248, v0);
        contest_competition_0224CA90(param0, 9, (-13000 - 4000), -6300, -5248, v0);
        contest_competition_0224CA90(param0, 10, (-13000 - 4000), -6300, -5248, v0);
        contest_competition_0224CA90(param0, 11, (-13000 - 4000), -6300, -5248, v0);
        contest_competition_0224CA90(param0, 12, (-13000 - 4000), -6300, -5248, v0);

        contest_competition_0224CA90(param0, 8, ((13000 + 7500) - 4000), -6300, -5248, v0);
        contest_competition_0224CA90(param0, 9, ((13000 + 7500) - 4000), -6300, -5248, v0);
        contest_competition_0224CA90(param0, 10, ((13000 + 7500) - 4000), -6300, -5248, v0);
        contest_competition_0224CA90(param0, 11, ((13000 + 7500) - 4000), -6300, -5248, v0);
        contest_competition_0224CA90(param0, 12, ((13000 + 7500) - 4000), -6300, -5248, v0);
    }

    contest_competition_0224CD84(param0, (0x1fff ^ ((1 << 4) | (1 << 3) | (1 << 2))), 8, 16, 0, 0x7fff);
    PaletteData_StartFade(param0->scene.paletteData, 0x4, 0x3fff, -1, 16, 0, 0x7fff);

    G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 16);

    SysTask_Start(contest_competition_0224CD60, param0, 1000);
    Sound_PlayEffect(SEQ_SE_DP_CON_007_sseq);
}

static void contest_competition_0224CD60(SysTask *param0, void *param1)
{
    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG0, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 0, 0);
    SysTask_Done(param0);
}

void contest_competition_0224CD84(DanceCompetition *param0, u32 param1, u32 param2, int param3, int param4, u16 param5)
{
    DanceSavedData *v0 = &param0->savedData;
    v0->current = param3 << 8;
    v0->target = param4 << 8;
    v0->duration = param5;
    v0->blendMode = param1;
    v0->step = ((param4 - param3) * 0x100) / param2;
    v0->active = 1;
}

void contest_competition_0224CDB4(DanceCompetition *param0, int param1)
{
    param0->savedData.state = param1;
}

void contest_competition_0224CDC0(DanceCompetition *param0, int param1, int param2)
{
    int v0;
    GXRgb v1, v2;

    if (param2 == 0) {
        v1 = 0x7fff;
        v2 = 0x254a;
    } else {
        v1 = 0x254a;
        v2 = 0x7fff;
    }

    for (v0 = 0; v0 < 4; v0++) {
        if (v0 == param1) {
            PhotoSprite_SetTint(param0->scene.photoSprites[v0].photoSprite, v1);
        } else {
            PhotoSprite_SetTint(param0->scene.photoSprites[v0].photoSprite, v2);
        }
    }

    Sound_PlayEffect(SEQ_SE_DP_CON_019_sseq);
}

void contest_competition_0224CE08(DanceCompetition *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        PhotoSprite_SetTint(param0->scene.photoSprites[v0].photoSprite, 0x7fff);
    }
}

void contest_competition_0224CE28(DanceCompetition *param0)
{
    int v0, v1, v2;
    s16 v3[4];
    u8 v4[4];
    u8 v5[4];

    for (v0 = 0; v0 < 4; v0++) {
        v3[v0] = param0->scoreState.scores[v0];
        v4[v0] = v0;
    }

    for (v0 = 0; v0 < 4 - 1; v0++) {
        for (v1 = 4 - 1; v1 > v0; v1--) {
            if (v3[v1 - 1] < v3[v1]) {
                v2 = v3[v1];
                v3[v1] = v3[v1 - 1];
                v3[v1 - 1] = v2;

                v2 = v4[v1];
                v4[v1] = v4[v1 - 1];
                v4[v1 - 1] = v2;
            }
        }
    }

    v5[0] = Unk_contest_competition_022549C0[0];

    for (v0 = 1; v0 < 4; v0++) {
        v5[v0] = Unk_contest_competition_022549C0[v0];

        if (v3[v0] == v3[v0 - 1]) {
            v5[v0] = v5[v0 - 1];
        }
    }

    for (v0 = 0; v0 < 4; v0++) {
        contest_competition_0224CEE4(param0, v4[v0], 0x7fff, 0x254a, v5[v0], 30, NULL);
    }
}

void contest_competition_0224CEE4(DanceCompetition *param0, int param1, GXRgb param2, GXRgb param3, int param4, int param5, u8 *param6)
{
    DancePhotoDisplay *v0 = Heap_Alloc(HEAP_ID_23, sizeof(DancePhotoDisplay));
    MI_CpuClear8(v0, sizeof(DancePhotoDisplay));

    v0->unk_00 = param0->scene.photoSprites[param1].photoSprite;
    v0->unk_08 = param2;
    v0->unk_0A = param3;
    v0->unk_10 = param4;
    v0->unk_0C = (param4 << 8) / param5;
    v0->unk_04 = param6;

    if (param6 != NULL) {
        *param6 = 0;
    }

    PhotoSprite_SetTint(v0->unk_00, param2);
    SysTask_Start(contest_competition_0224CF4C, v0, (30000 + 10000));
}

static void contest_competition_0224CF4C(SysTask *param0, void *param1)
{
    DancePhotoDisplay *v0 = param1;
    u16 v1;
    int v2;

    v0->unk_0E += v0->unk_0C;
    v2 = v0->unk_0E >> 8;

    if (v2 > v0->unk_10) {
        v2 = v0->unk_10;
    }

    BlendPalette(&v0->unk_08, &v1, 1, v2, v0->unk_0A);
    PhotoSprite_SetTint(v0->unk_00, v1);

    if (v2 >= v0->unk_10) {
        if (v0->unk_04 != NULL) {
            *(v0->unk_04) = 1;
        }

        Heap_Free(param1);
        SysTask_Done(param0);
        return;
    }
}

BOOL contest_competition_0224CFA8(u32 param0)
{
    switch (param0) {
    case 50:
    case 51:
        return 0;
    }

    return 1;
}
