#include "contest_competition/contest_competition_0223DAD0.h"

#include <nitro.h>
#include <string.h>

#include "battle_particles/particle_helper.h"
#include "contest_competition/contest_competition_0223F118.h"
#include "contest_competition/contest_competition_022492DC.h"
#include "contest_competition/contest_competition_0224A0FC.h"
#include "contest_competition/contest_competition_0224CFB8.h"
#include "contest_competition/contest_competition_0224F18C.h"
#include "contest_competition/contest_competition_02250744.h"
#include "contest_competition/struct_dance_competition_task.h"
#include "contest_competition/struct_dance_move_command.h"
#include "contest_competition/struct_dance_saved_data.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_dance_message_config.h"
#include "contest_competition/struct_dance_move_definition.h"
#include "image_clip_app/image_clip_app_0225AF8C.h"

#include "bg_window.h"
#include "camera.h"
#include "comm_manager.h"
#include "contest.h"
#include "font.h"
#include "game_options.h"
#include "game_overlay.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "palette.h"
#include "particle_system.h"
#include "pokemon.h"
#include "pokemon_sprite.h"
#include "render_window.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "touch_pad.h"
#include "font_oam.h"
#include "contest_util.h"
#include "vram_transfer.h"

FS_EXTERN_OVERLAY(battle_particles);
FS_EXTERN_OVERLAY(battle_anim);
FS_EXTERN_OVERLAY(image_clip_app);

static void contest_competition_0223E09C(void *param0);
static void contest_competition_0223E1FC(SysTask *param0, void *param1);
static void contest_competition_0223E250(BgConfig *param0);
static void contest_competition_0223E380(DanceCompetition *param0);
static void contest_competition_0223E458(DanceCompetition *param0);
static void contest_competition_0223E4B0(DanceCompetition *param0, NARC *param1);
static void contest_competition_0223E588(DanceCompetition *param0);
static void contest_competition_0223E60C(DanceCompetition *param0, NARC *param1);
static void contest_competition_0223E678(DanceCompetition *param0);
static void contest_competition_0223E67C(DanceCompetition *param0, NARC *param1);
static void contest_competition_0223E76C(DanceCompetition *param0);
static void contest_competition_0223E770(DanceCompetition *param0, NARC *param1);
static void contest_competition_0223E774(DanceCompetition *param0);
static void contest_competition_0223E778(DanceCompetition *param0);
static void contest_competition_0223E7E0(DanceCompetition *param0);
static int contest_competition_0223E838(DanceCompetition *param0, DanceCompetitionTask *param1);
static int contest_competition_0223E8AC(DanceCompetition *param0, DanceCompetitionTask *param1);
static int contest_competition_0223E954(DanceCompetition *param0, DanceCompetitionTask *param1);
static int contest_competition_0223EE54(DanceCompetition *param0, DanceCompetitionTask *param1);
static int contest_competition_0223EEB8(DanceCompetition *param0, DanceCompetitionTask *param1);
static int contest_competition_0223F03C(DanceCompetition *param0, DanceCompetitionTask *param1);
static int contest_competition_0223E9A4(DanceCompetition *param0, DanceCompetitionTask *param1);
static int contest_competition_0223EBB0(DanceCompetition *param0, DanceCompetitionTask *param1);
static int contest_competition_0223EC20(DanceCompetition *param0, DanceCompetitionTask *param1);
static int contest_competition_0223EC74(DanceCompetition *param0, DanceCompetitionTask *param1);
static int contest_competition_0223ECC8(DanceCompetition *param0, DanceCompetitionTask *param1);
static int contest_competition_0223ED1C(DanceCompetition *param0, DanceCompetitionTask *param1);
static int contest_competition_0223ED9C(DanceCompetition *param0, DanceCompetitionTask *param1);
static BOOL contest_competition_0223E3CC(DanceCompetition *param0, int *param1, int *param2);
static void contest_competition_0223E450(void);
static u32 contest_competition_0223E800(u32 param0, BOOL param1);
static u32 contest_competition_0223E81C(u32 param0, BOOL param1);

static const DanceMoveDefinition Unk_contest_competition_02253084[] = {
    {
        0x499,
        0x78,
        0x2,
        0x3,
        0x4,
        0x4,
        { 0x2, 0x2, 0x3, 0x3 },
    },
    {
        0x49B,
        0x78,
        0x2,
        0x4,
        0x4,
        0x4,
        { 0x2, 0x2, 0x3, 0x3 },
    },
    {
        0x4B5,
        0x64,
        0x2,
        0x4,
        0x3,
        0x3,
        { 0x1, 0x1, 0x2, 0x2 },
    },
    {
        0x4B9,
        0x3C,
        0x2,
        0x4,
        0x3,
        0x3,
        { 0x2, 0x2, 0x3, 0x3 },
    },
    {
        0x4B7,
        0x96,
        0x2,
        0x4,
        0x4,
        0x4,
        { 0x1, 0x1, 0x2, 0x2 },
    },
    {
        0x4B6,
        0x84,
        0x2,
        0x4,
        0x4,
        0x4,
        { 0x1, 0x1, 0x2, 0x2 },
    },
    {
        0x4B8,
        0x8C,
        0x2,
        0x4,
        0x4,
        0x4,
        { 0x1, 0x1, 0x2, 0x2 },
    },
};

static const struct {
    u32 unk_00;
    u32 unk_04;
} Unk_contest_competition_0225312C[CONTEST_MAX_RANKS][CONTEST_TYPE_MAX] = {
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0 },
    { 0x2, 0x1, 0x3, 0x1, 0x4, 0x0, 0x5, 0x0, 0x6, 0x0 },
    { 0x2, 0x1, 0x3, 0x1, 0x4, 0x0, 0x5, 0x0, 0x6, 0x0 }
};

static const DanceMessageConfig Unk_contest_competition_02252FC4[] = {
    { 0xE, 0x10, 0x20 },
    { 0xF, 0xC, 0x1E }
};

static int (*const Unk_contest_competition_02253050[])(DanceCompetition *, DanceCompetitionTask *) = {
    contest_competition_0223E838,
    contest_competition_0223E8AC,
    contest_competition_0223E954,
    contest_competition_0223E9A4,
    contest_competition_0223EBB0,
    contest_competition_0223EC20,
    contest_competition_0223EC74,
    contest_competition_0223ECC8,
    contest_competition_0223ED1C,
    contest_competition_0223ED9C,
    contest_competition_0223EE54,
    contest_competition_0223EEB8,
    contest_competition_0223F03C
};

static const RenderOamTemplate Unk_contest_competition_02253008 = {
    0x0,
    0x80,
    0x0,
    0x20,
    0x0,
    0x80,
    0x0,
    0x20
};

static const CharTransferTemplateWithModes Unk_contest_competition_02252FDC = {
    0x60,
    0x10000,
    0x4000,
    GX_OBJVRAMMODE_CHAR_1D_64K,
    GX_OBJVRAMMODE_CHAR_1D_32K
};

static const SpriteResourceCapacities Unk_contest_competition_02252FF0 = {
    0x60,
    0x20,
    0x40,
    0x40,
    0x8,
    0x8
};

int DanceCompetition_Init(ApplicationManager *appMan, int *param1)
{
    DanceCompetition *v0;

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();

    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);
    GX_SetVisibleWnd(GX_WNDMASK_NONE);
    GXS_SetVisibleWnd(GX_WNDMASK_NONE);
    G2_BlendNone();
    G2S_BlendNone();

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_23, 0xa0000);
    v0 = ApplicationManager_NewData(appMan, sizeof(DanceCompetition), HEAP_ID_23);
    MI_CpuClear8(v0, sizeof(DanceCompetition));

    v0->g3dPipeline = contest_competition_0223F140(HEAP_ID_23);
    v0->contest = ApplicationManager_Args(appMan);
    v0->contest->appContext = v0;
    v0->contest->activeAppID = 1;
    v0->scene.contestData = &v0->contest->data;

    contest_competition_0223E458(v0);
    v0->scene.paletteData = PaletteData_New(HEAP_ID_23);

    PaletteData_SetAutoTransparent(v0->scene.paletteData, TRUE);
    PaletteData_AllocBuffer(v0->scene.paletteData, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_23);
    PaletteData_AllocBuffer(v0->scene.paletteData, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_23);
    PaletteData_AllocBuffer(v0->scene.paletteData, PLTTBUF_MAIN_OBJ, PALETTE_SIZE_BYTES * 14, HEAP_ID_23);
    PaletteData_AllocBuffer(v0->scene.paletteData, PLTTBUF_SUB_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_23);

    v0->savedData.data = Heap_Alloc(HEAP_ID_23, 0x200);
    contest_competition_0224CDB4(v0, 1);
    v0->scene.bgConfig = BgConfig_New(HEAP_ID_23);

    VramTransfer_New(64, HEAP_ID_23);
    SetAutorepeat(4, 8);

    v0->moveSelectScreen = contest_competition_02249380(v0->contest, &v0->scene);

    contest_competition_0223E250(v0->scene.bgConfig);

    EnableTouchPad();
    InitializeTouchPad(4);
    Font_InitManager(FONT_SUBSCREEN, HEAP_ID_23);

    v0->scene.spriteSystem = SpriteSystem_Alloc(HEAP_ID_23);

    SpriteSystem_Init(v0->scene.spriteSystem, &Unk_contest_competition_02253008, &Unk_contest_competition_02252FDC, 16 + 16);
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    v0->scene.spriteManager = SpriteManager_New(v0->scene.spriteSystem);

    SpriteSystem_InitSprites(v0->scene.spriteSystem, v0->scene.spriteManager, 64 + 64);
    SpriteSystem_InitManagerWithCapacities(v0->scene.spriteSystem, v0->scene.spriteManager, &Unk_contest_competition_02252FF0);
    SetSubScreenViewRect(SpriteSystem_GetRenderer(v0->scene.spriteSystem), 0, 256 * FX32_ONE);

    v0->scene.pokemonSpriteManager = PokemonSpriteManager_New(HEAP_ID_23);
    contest_competition_0223E450();

    v0->scene.danceMessageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_CONTEST_DANCE_COMPETITION, HEAP_ID_23);
    v0->scene.stringTemplate = StringTemplate_Default(HEAP_ID_23);
    v0->scene.danceMessage = String_Init(2 * 160, HEAP_ID_23);
    v0->scene.fontOAMManager = FontOAMManager_New(3 * 3, HEAP_ID_23);

    {
        NARC *v1;
        NARC *v2;

        v1 = NARC_ctor(NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, HEAP_ID_23);
        v2 = NARC_ctor(NARC_INDEX_CONTEST__GRAPHIC__CONTEST_OBJ, HEAP_ID_23);

        contest_competition_0223E67C(v0, v1);
        contest_competition_0223E770(v0, v1);
        contest_competition_0223E380(v0);
        contest_competition_0223E4B0(v0, v2);
        contest_competition_0223E60C(v0, v2);
        contest_competition_02249640(v0->moveSelectScreen, 0, 1, NULL);

        NARC_dtor(v1);
        NARC_dtor(v2);
    }

    contest_competition_0224A134(v0);
    contest_competition_0224B0CC(&v0->scene);
    contest_competition_0223E778(v0);
    contest_competition_0224AA38(v0);
    contest_competition_0224B59C(v0);

    NetworkIcon_Init();
    StartScreenFade(FADE_MAIN_THEN_SUB, FADE_TYPE_CIRCLE_IN, FADE_TYPE_UNK_37, COLOR_BLACK, 6, 1, HEAP_ID_23);

    v0->task = SysTask_Start(contest_competition_0223E1FC, v0, 80000);
    v0->flag2 = 1;

    GXLayers_TurnBothDispOn();
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
    Sound_SetSceneAndPlayBGM(SOUND_SCENE_CONTEST, CONTEST_DRESSING_ROOM_sseq, 1);
    SetLockTextWithAutoScroll(v0->contest->isLinkContest);

    G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BD | GX_BLEND_PLANEMASK_OBJ, -6);

    Sound_PlayEffect(SEQ_SE_DP_CON_007_sseq);
    SetVBlankCallback(contest_competition_0223E09C, v0);

    return 1;
}

int DanceCompetition_Main(ApplicationManager *appMan, int *param1)
{
    DanceCompetition *v0 = ApplicationManager_Data(appMan);
    int v1;

    Contest_GetRNGNext(v0->contest);

    switch (*param1) {
    case 0:
        if (IsScreenFadeDone() == TRUE) {
            *param1 = 1;
        }
        break;
    case 1:
        if (Contest_IsPlayerLeader(v0->contest) == TRUE) {
            v1 = Unk_contest_competition_02253050[v0->handlerIndex](v0, &v0->competitionTask);

            if ((v1 == 1) || (v1 == 2)) {
                if (v1 == 1) {
                    v0->handlerIndex++;
                } else {
                    v0->handlerIndex = v0->competitionTask.nextState;
                }

                MI_CpuClear8(&v0->competitionTask, sizeof(DanceCompetitionTask));
            } else if ((v1 == 3) && (v0->initialized == 1)) {
                *param1 = 2;
                MI_CpuClear8(&v0->competitionTask, sizeof(DanceCompetitionTask));
                StartScreenFade(FADE_SUB_THEN_MAIN, FADE_TYPE_UNK_30, FADE_TYPE_UNK_30, COLOR_BLACK, 6, 1, HEAP_ID_23);
                break;
            }
        }

        contest_competition_0224F35C(&v0->packetQueue);
        contest_competition_0224F3D8(&v0->packetQueue, v0);

        if ((v0->initialized == 1) && (contest_competition_0224F3D0(&v0->packetQueue) == 0) && (Contest_IsPlayerLeader(v0->contest) == FALSE)) {
            *param1 = 2;
            MI_CpuClear8(&v0->competitionTask, sizeof(DanceCompetitionTask));
            StartScreenFade(FADE_SUB_THEN_MAIN, FADE_TYPE_UNK_30, FADE_TYPE_UNK_30, COLOR_BLACK, 6, 1, HEAP_ID_23);
        }
        break;
    case 2:
        if (v0->initialized == 1) {
            if (IsScreenFadeDone() == TRUE) {
                return 1;
            }
        }
        break;
    }

    return 0;
}

int DanceCompetition_Exit(ApplicationManager *appMan, int *param1)
{
    DanceCompetition *v0 = ApplicationManager_Data(appMan);
    int v1;

    GF_ASSERT(ParticleSystem_GetActiveEmitterCount(v0->particleSystem) == 0);

    contest_competition_0223E7E0(v0);
    ParticleSystem_FreeAll();

    contest_competition_0224A95C(&v0->scene);
    contest_competition_0224AA58(v0);
    contest_competition_0224B5B8(v0);
    contest_competition_0224BD00(v0);
    contest_competition_0223E588(v0);
    contest_competition_0223E678(v0);
    contest_competition_0223E76C(v0);
    contest_competition_0223E774(v0);

    for (v1 = 0; v1 < 2; v1++) {
        Window_Remove(&v0->scene.windows[v1]);
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    Bg_FreeTilemapBuffer(v0->scene.bgConfig, 1);
    Bg_FreeTilemapBuffer(v0->scene.bgConfig, 2);
    Bg_FreeTilemapBuffer(v0->scene.bgConfig, 3);

    contest_competition_02249358(v0->scene.bgConfig);
    contest_competition_022493A4(v0->moveSelectScreen);

    SpriteSystem_FreeResourcesAndManager(v0->scene.spriteSystem, v0->scene.spriteManager);
    SpriteSystem_Free(v0->scene.spriteSystem);
    VramTransfer_Free();

    contest_competition_0224A1EC(&v0->scene);

    PokemonSpriteManager_Free(v0->scene.pokemonSpriteManager);
    FontOAMManager_Free(v0->scene.fontOAMManager);
    Font_Free(FONT_SUBSCREEN);
    Heap_Free(v0->savedData.data);
    PaletteData_FreeBuffer(v0->scene.paletteData, PLTTBUF_MAIN_BG);
    PaletteData_FreeBuffer(v0->scene.paletteData, PLTTBUF_SUB_BG);
    PaletteData_FreeBuffer(v0->scene.paletteData, PLTTBUF_MAIN_OBJ);
    PaletteData_FreeBuffer(v0->scene.paletteData, PLTTBUF_SUB_OBJ);
    PaletteData_Free(v0->scene.paletteData);
    String_Free(v0->scene.danceMessage);
    StringTemplate_Free(v0->scene.stringTemplate);
    MessageLoader_Free(v0->scene.danceMessageLoader);
    Heap_Free(v0->scene.bgConfig);
    SysTask_Done(v0->task);

    contest_competition_0223F1E0(v0->g3dPipeline);

    DisableTouchPad();
    ApplicationManager_FreeData(appMan);
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    Heap_Destroy(HEAP_ID_23);
    LockTextSpeed();
    NetworkIcon_Destroy();
    Overlay_UnloadByID(FS_OVERLAY_ID(battle_particles));
    Overlay_UnloadByID(FS_OVERLAY_ID(battle_anim));
    Overlay_UnloadByID(FS_OVERLAY_ID(image_clip_app));

    return 1;
}

static void contest_competition_0223E09C(void *param0)
{
    DanceCompetition *v0 = param0;

    if (v0->flag) {
        u32 v1, v2;

        v0->timestamp++;
        v1 = Sound_GetTicksForHandle(7);
        v2 = v0->scoreState.beatDuration * v1;
        v2 += 10000 / 2;
        v2 /= 10000;
        v0->lastTick = v2;
        v2 += 1;

        if (v2 != v0->timestamp) {
            if ((v0->frameCounter > 18) || ((v2 - v0->timestamp) > 1)) {
                v0->timestamp = v2;
                v0->frameCounter = 0;
            } else {
                v0->frameCounter++;
            }
        } else {
            v0->frameCounter = 0;
        }
    }

    PokemonSpriteManager_UpdateCharAndPltt(v0->scene.pokemonSpriteManager);

    {
        int v3;

        for (v3 = 0; v3 < 4; v3++) {
            if (v0->scene.photoSprites[v3].photoSprite != NULL) {
                PhotoSprite_UpdateGraphics(v0->scene.photoSprites[v3].photoSprite);
            }
        }
    }

    VramTransfer_Process();
    SpriteSystem_TransferOam();
    PaletteData_CommitFadedBuffers(v0->scene.paletteData);
    Bg_RunScheduledUpdates(v0->scene.bgConfig);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void contest_competition_0223E18C(DanceCompetition *param0)
{
    u16 *v0;
    DanceSavedData *v1;
    s32 v2;

    v1 = &param0->savedData;

    if (v1->state == 0) {
        return;
    }

    v0 = PaletteData_GetFadedBuffer(param0->scene.paletteData, 0);

    MI_CpuCopy16(v1->data, v0, 0x200);

    if (v1->active == 1) {
        BlendPalettes(v1->data, v0, v1->blendMode, v1->current >> 8, v1->duration);

        if (v1->current == v1->target) {
            v1->active = 0;
        } else {
            v2 = v1->current;
            v2 += v1->step;

            if (((v1->step > 0) && (v2 >= v1->target)) || ((v1->step < 0) && (v2 <= v1->target))) {
                v2 = v1->target;
            }

            v1->current = v2;
        }
    }
}

static void contest_competition_0223E1FC(SysTask *param0, void *param1)
{
    DanceCompetition *v0 = param1;

    contest_competition_0223E18C(v0);

    if (v0->flag2 == 1) {
        PokemonSpriteManager_DrawSprites(v0->scene.pokemonSpriteManager);
        {
            int v1;

            for (v1 = 0; v1 < 4; v1++) {
                if (v0->scene.photoSprites[v1].photoSprite != NULL) {
                    PhotoSprite_Update(v0->scene.photoSprites[v1].photoSprite);
                }
            }
        }

        ParticleHelper_DrawParticleSystems();
        SpriteSystem_DrawSprites(v0->scene.spriteManager);
        SpriteSystem_UpdateTransfer();

        G3_SwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
    }

    CommManager_Dummy_02038A1C(23, v0->scene.bgConfig);
}

static void contest_competition_0223E250(BgConfig *param0)
{
    GXLayers_DisableEngineALayers();

    {
        GXBanks v0 = {
            GX_VRAM_BG_128_C,
            GX_VRAM_BGEXTPLTT_NONE,
            GX_VRAM_SUB_BG_32_H,
            GX_VRAM_SUB_BGEXTPLTT_NONE,
            GX_VRAM_OBJ_64_E,
            GX_VRAM_OBJEXTPLTT_NONE,
            GX_VRAM_SUB_OBJ_16_I,
            GX_VRAM_SUB_OBJEXTPLTT_NONE,
            GX_VRAM_TEX_01_AB,
            GX_VRAM_TEXPLTT_01_FG
        };

        GXLayers_SetBanks(&v0);

        MI_CpuClear32((void *)HW_BG_VRAM, HW_BG_VRAM_SIZE);
        MI_CpuClear32((void *)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
        MI_CpuClear32((void *)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
        MI_CpuClear32((void *)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    }

    {
        GraphicsModes v1 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_3D
        };

        SetAllGraphicsModes(&v1);
    }

    {
        BgTemplate v2[] = {
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x1000,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_512x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x0000,
                .charBase = GX_BG_CHARBASE_0x14000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x2000,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_512x512,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x1000,
                .charBase = GX_BG_CHARBASE_0x0c000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0,
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
                .screenBase = GX_BG_SCRBASE_0x3000,
                .charBase = GX_BG_CHARBASE_0x04000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_1, &v2[0], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_1);
        Bg_SetOffset(param0, BG_LAYER_MAIN_1, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_1, 3, 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_2, &v2[1], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_2);
        Bg_SetOffset(param0, BG_LAYER_MAIN_2, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_2, 3, 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_3, &v2[2], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_3);
        Bg_SetOffset(param0, BG_LAYER_MAIN_3, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_3, 3, 0);

        G2_SetBG0Priority(2);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    }

    {
        contest_competition_02249300(param0);
    }
}

static void contest_competition_0223E380(DanceCompetition *param0)
{
    Window_Add(param0->scene.bgConfig, &param0->scene.windows[0], 1, 0x2, 0x13, 27, 4, 13, (18 + 12) + 1);
    Window_Add(param0->scene.bgConfig, &param0->scene.windows[1], 1, 0x2, 0xb, 27, 2, 13, (18 + 12) + 1);
}

static BOOL contest_competition_0223E3CC(DanceCompetition *param0, int *param1, int *param2)
{
    if ((param0->contest->isLinkContest == TRUE) && (param0->contest->gameCodeMismatchCount > 0)) {
        param0->contestRank = 1;
    } else {
        param0->contestRank = 0;
    }

    if (param0->contestRank == 1) {
        *param1 = 1;
        *param2 = 0;
        return 1;
    } else {
        *param1 = Unk_contest_competition_0225312C[param0->contest->data.contestRank][param0->contest->data.contestType].unk_00;
        *param2 = Unk_contest_competition_0225312C[param0->contest->data.contestRank][param0->contest->data.contestType].unk_04;
        return 0;
    }
}

static void contest_competition_0223E450(void)
{
    ParticleSystem_ZeroAll();
}

static void contest_competition_0223E458(DanceCompetition *param0)
{
    int i;

    GF_ASSERT(param0->contest != NULL);

    for (i = 0; i < CONTEST_NUM_PARTICIPANTS; i++) {
        param0->scoreState.contestantIDs[i] = 4 - 1 - i;
        param0->scoreState.judgeVotes[i] = 4 - 1 - i;
    }

    contest_competition_0224CFB8(param0);

    for (i = 0; i < CONTEST_NUM_PARTICIPANTS; i++) {
        param0->scene.contestantIsHuman[i] = contest_competition_0224CFA8(Pokemon_GetValue(param0->contest->data.contestMons[i], MON_DATA_SPECIES, NULL));
    }
}

static void contest_competition_0223E4B0(DanceCompetition *param0, NARC *param1)
{
    SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->scene.paletteData, 2, param0->scene.spriteSystem, param0->scene.spriteManager, param1, 6, 0, 8, NNS_G2D_VRAM_TYPE_2DMAIN, 33001);

    contest_competition_0224A20C(param0->scene.spriteSystem, param0->scene.spriteManager);
    contest_competition_0224A390(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_0224A5A8(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_0224A61C(&param0->scene, param0->scene.spriteSystem, param0->scene.spriteManager);
    contest_competition_0224A674(&param0->scene);
    contest_competition_0224A984(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_0224A9F8(&param0->scene, param0->scene.spriteSystem, param0->scene.spriteManager);
    contest_competition_0224C310(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_0224C384(param0, param0->scene.spriteSystem, param0->scene.spriteManager);
    contest_competition_0224AA94(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_0224AB08(&param0->scene, param0->scene.spriteSystem, param0->scene.spriteManager);
    contest_competition_0224AC80(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_0224ACF4(&param0->scene, param0->scene.spriteSystem, param0->scene.spriteManager);
    contest_competition_0224ACFC(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_0224AFA8(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_0224B01C(param0);
}

static void contest_competition_0223E588(DanceCompetition *param0)
{
    contest_competition_0224A210(param0->scene.spriteManager);
    contest_competition_0224A428(param0->scene.spriteManager);
    contest_competition_0224A580(&param0->scene);
    contest_competition_0224A5F8(param0->scene.spriteManager);
    contest_competition_0224A650(&param0->scene);
    contest_competition_0224A7B8(&param0->scene);
    contest_competition_0224A9D4(param0->scene.spriteManager);
    contest_competition_0224AA1C(&param0->scene);
    contest_competition_0224C3E4(param0);
    contest_competition_0224C360(param0->scene.spriteManager);
    contest_competition_0224AAE4(param0->scene.spriteManager);
    contest_competition_0224ABB0(&param0->scene);
    contest_competition_0224ACD0(param0->scene.spriteManager);
    contest_competition_0224ACF8(&param0->scene);
    contest_competition_0224AD4C(param0->scene.spriteManager);
    contest_competition_0224AFF8(param0->scene.spriteManager);
    contest_competition_0224B058(param0);

    SpriteManager_UnloadPlttObjById(param0->scene.spriteManager, 33001);
}

static void contest_competition_0223E60C(DanceCompetition *param0, NARC *param1)
{
    SpriteSystem_LoadPaletteBuffer(param0->scene.paletteData, 3, param0->scene.spriteSystem, param0->scene.spriteManager, 46, 6, 0, 2, NNS_G2D_VRAM_TYPE_2DSUB, 33002);
    SpriteSystem_LoadPaletteBuffer(param0->scene.paletteData, 3, param0->scene.spriteSystem, param0->scene.spriteManager, 46, 9, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 33003);

    contest_competition_022493C4(param0->moveSelectScreen);
}

static void contest_competition_0223E678(DanceCompetition *param0)
{
    return;
}

static void contest_competition_0223E67C(DanceCompetition *param0, NARC *param1)
{
    int v0;

    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 13, param0->scene.bgConfig, 3, 0, 0, 1, HEAP_ID_23);

    {
        int v1, v2;
        int v3;

        contest_competition_0223E3CC(param0, &v1, &v2);
        v3 = contest_competition_0223F0BC(v2, 0);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, v3, param0->scene.bgConfig, 3, 0, 0, 1, HEAP_ID_23);
    }

    PaletteData_LoadBufferFromFileStart(param0->scene.paletteData, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, 32, HEAP_ID_23, PLTTBUF_MAIN_BG, 0, 0);
    PaletteData_LoadBufferFromFileStart(param0->scene.paletteData, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, 36, HEAP_ID_23, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(13));

    v0 = Options_Frame(param0->contest->options);
    LoadMessageBoxGraphics(param0->scene.bgConfig, 1, 1, 15, v0, HEAP_ID_23);
    PaletteData_LoadBufferFromFileStart(param0->scene.paletteData, NARC_INDEX_GRAPHIC__PL_WINFRAME, GetMessageBoxPaletteNARCMember(v0), HEAP_ID_23, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
    contest_competition_0224C848(param0);

    {
        u16 *v4;

        v4 = PaletteData_GetUnfadedBuffer(param0->scene.paletteData, 0);
        MI_CpuCopy16(v4, param0->savedData.data, 0x200);
    }
}

static void contest_competition_0223E76C(DanceCompetition *param0)
{
    return;
}

static void contest_competition_0223E770(DanceCompetition *param0, NARC *param1)
{
    return;
}

static void contest_competition_0223E774(DanceCompetition *param0)
{
    return;
}

static void contest_competition_0223E778(DanceCompetition *param0)
{
    void *v0;
    Camera *camera;
    void *v2;

    GF_ASSERT(param0->particleSystem == NULL);

    v0 = Heap_Alloc(HEAP_ID_23, 0x4800);
    param0->particleSystem = ParticleSystem_New(contest_competition_0223E800, contest_competition_0223E81C, v0, 0x4800, 1, HEAP_ID_23);

    camera = ParticleSystem_GetCamera(param0->particleSystem);
    Camera_SetClipping(FX32_ONE, FX32_ONE * 900, camera);

    v2 = ParticleSystem_LoadResourceFromNARC(NARC_INDEX_PARTICLEDATA__PARTICLEDATA, 3, HEAP_ID_23);
    ParticleSystem_SetResource(param0->particleSystem, v2, (1 << 1) | (1 << 3), 1);
}

static void contest_competition_0223E7E0(DanceCompetition *param0)
{
    void *v0 = ParticleSystem_GetHeapStart(param0->particleSystem);
    ParticleSystem_Free(param0->particleSystem);
    Heap_Free(v0);

    param0->particleSystem = NULL;
}

static u32 contest_competition_0223E800(u32 param0, BOOL param1)
{
    NNSGfdTexKey v0;
    u32 v1;

    v0 = NNS_GfdAllocTexVram(param0, param1, 0);
    ParticleSystem_RegisterTextureKey(v0);

    v1 = NNS_GfdGetTexKeyAddr(v0);
    return v1;
}

static u32 contest_competition_0223E81C(u32 param0, BOOL param1)
{
    NNSGfdPlttKey v0;
    u32 v1;

    v0 = NNS_GfdAllocPlttVram(param0, param1, 0);
    ParticleSystem_RegisterPaletteKey(v0);

    v1 = NNS_GfdGetPlttKeyAddr(v0);
    return v1;
}

static int contest_competition_0223E838(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    int v0;

    switch (param1->state) {
    case 0:
        if (param0->contest->gameCodeMismatchCount > 0) {
            if (param1->timer < 120) {
                param1->timer++;
                break;
            }
        }

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 10, &param0->scoreState) == 1) {
            param1->timer = 0;
            param1->state++;
        }
        break;
    default:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            return 1;
        }
        break;
    }

    return 0;
}

static int contest_competition_0223E8AC(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        param0->moveState.delay = 0;
        param0->moveState.flag = 0;
        param0->moveState.messageArgs.contestantID = param0->contest->data.playerContestantID;
        param0->moveState.messageArgs.moveSlot = contest_competition_0224C57C(param0->contest->data.contestRank);

        if (Contest_IsPracticeCompetition(param0->contest) == TRUE) {
            param0->moveState.messageID = 2;
        } else {
            param0->moveState.messageID = 1;
        }

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 9, &param0->moveState) == 1) {
            param1->state++;
        }
        break;
    case 1:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

static int contest_competition_0223E954(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 3, NULL) == 1) {
            param1->state++;
        }
        break;
    default:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            return 1;
        }
        break;
    }

    return 0;
}

static int contest_competition_0223E9A4(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    int v0, v1;
    u64 v2;

    switch (param1->state) {
    case 0:
        contest_competition_0223E3CC(param0, &v0, &v1);

        param0->scene.moveDefinitions = &Unk_contest_competition_02253084[v0];
        param0->scoreState.maxScore = (60 * 30) * 10000 / Unk_contest_competition_02253084[v0].unk_02;

        v2 = param0->scoreState.maxScore * contest_competition_0223F0BC(v1, 1);
        v2 = (v2 + 10000 / 2) / 10000;

        param0->scoreState.scorePerBeat = v2;
        param0->scoreState.maxBeats = Unk_contest_competition_02253084[v0].unk_02;
        param0->scoreState.bonus1 = param0->scoreState.maxScore * Unk_contest_competition_02253084[v0].unk_06;
        param0->scoreState.bonus2 = param0->scoreState.maxScore * Unk_contest_competition_02253084[v0].unk_07;
        param0->scoreState.beatDuration = param0->scoreState.maxScore / 48;

        param0->scoreState.roundCount = Unk_contest_competition_02253084[v0].unk_05;
        param0->scoreState.difficulty = Unk_contest_competition_02253084[v0].unk_00;
        param0->scoreState.contestRank = v1;

        param0->moveState.moveDefinition = *(param0->scene.moveDefinitions);
        param0->moveState.duration = param0->scoreState.maxScore;
        param0->moveState.beatInterval = param0->scoreState.scorePerBeat;
        param0->moveState.beat = param0->scoreState.maxBeats;
        param1->state++;
        break;
    case 1:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 10, &param0->scoreState) == 1) {
            param1->state++;
        }
        break;
    case 2:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    case 3:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 11, &param0->moveState) == 1) {
            param1->state++;
        }
        break;
    case 4:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

static int contest_competition_0223EBB0(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    int contestantID;

    switch (param1->state) {
    case 0:
        param0->moveState.state = param0->scoreState.contestantIDs[param0->scoreState.round];

        for (contestantID = 0; contestantID < CONTEST_NUM_PARTICIPANTS; contestantID++) {
            param0->moveState.contestantIDs[contestantID] = param0->scoreState.judgeVotes[contestantID];
        }

        for (contestantID = param0->contest->data.connectionCount; contestantID < CONTEST_NUM_PARTICIPANTS; contestantID++) {
            param0->moveState.moveIDs[contestantID] = Contest_GetRNGNext(param0->contest);
        }

        param1->state++;
        break;
    default:
        return 1;
    }

    return 0;
}

static int contest_competition_0223EC20(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 7, &param0->moveState) == 1) {
            param1->state++;
        }
        break;
    default:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            return 1;
        }
        break;
    }

    return 0;
}

static int contest_competition_0223EC74(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 5, &param0->moveState) == 1) {
            param1->state++;
        }
        break;
    default:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            return 1;
        }
        break;
    }

    return 0;
}

static int contest_competition_0223ECC8(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 8, &param0->moveState) == 1) {
            param1->state++;
        }
        break;
    default:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            return 1;
        }
        break;
    }

    return 0;
}

static int contest_competition_0223ED1C(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (param0->scoreState.round >= 4 - 1) {
            return 1;
        }

        param0->moveState.messageArgs.contestantID = param0->scoreState.judgeVotes[1];
        param0->moveState.messageArgs.moveSlot = contest_competition_0224C57C(param0->contest->data.contestRank);
        param0->moveState.messageID = 0;

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 6, &param0->moveState) == 1) {
            param1->state++;
        }
        break;
    default:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            return 1;
        }
        break;
    }

    return 0;
}

static int contest_competition_0223ED9C(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    int v0;

    switch (param1->state) {
    case 0:

    {
        int v1;

        v1 = param0->scoreState.judgeVotes[0];

        for (v0 = 0; v0 < 4 - 1; v0++) {
            param0->scoreState.judgeVotes[v0] = param0->scoreState.judgeVotes[v0 + 1];
        }

        param0->scoreState.judgeVotes[4 - 1] = v1;
    }

        param0->scoreState.round++;
        param1->state++;
    case 1:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 10, &param0->scoreState) == 1) {
            param1->state++;
        }
        break;
    case 2:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    default:
        if (param0->scoreState.round < 4) {
            param0->moveState.moveIndex++;
            param1->nextState = 4;
            return 2;
        }

        return 1;
    }

    return 0;
}

static int contest_competition_0223EE54(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 12, &param0->moveState) == 1) {
            param1->state++;
        }
        break;
    case 1:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

static int contest_competition_0223EEB8(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    int v0, v1;

    switch (param1->state) {
    case 0: {
        int v2, v3, v4;
        s16 v5[4], v6[4];
        s16 v7[4];
        u8 v8[4];

        for (v2 = 0; v2 < 4; v2++) {
            param0->contest->data.results[v2].danceCompetitionScore = param0->scoreState.scores[v2];
        }

        contest_competition_02251930(param0->contest, 0, v5);
        contest_competition_02251930(param0->contest, 1, v6);

        for (v2 = 0; v2 < 4; v2++) {
            v7[v2] = v5[v2] + v6[v2];
            v8[v2] = v2;
        }

        for (v2 = 0; v2 < 4 - 1; v2++) {
            for (v3 = 4 - 1; v3 > v2; v3--) {
                if (v7[v3 - 1] < v7[v3]) {
                    v4 = v7[v3];
                    v7[v3] = v7[v3 - 1];
                    v7[v3 - 1] = v4;

                    v4 = v8[v3];
                    v8[v3] = v8[v3 - 1];
                    v8[v3 - 1] = v4;
                }
            }
        }

        for (v2 = 0; v2 < 4; v2++) {
            param0->contest->contestantOrder[v2] = v8[v2];
        }
    }

        param0->moveState.delay = 0;
        param0->moveState.flag = 0;
        v1 = param0->contest->contestantOrder[0];
        param0->moveState.messageArgs.contestantID = v1;

        switch (param0->contest->data.competitionType) {
        case CONTEST_COMPETITION_UNK0:
        case CONTEST_COMPETITION_UNK1:
        case CONTEST_COMPETITION_LINK_OR_OFFICIAL:
            param0->moveState.messageID = 6;
            break;
        default:
            param0->moveState.messageID = 0;
            break;
        }

        param1->state++;
    case 1:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 9, &param0->moveState) == 1) {
            param1->state++;
        }
        break;
    case 2:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

static int contest_competition_0223F03C(DanceCompetition *param0, DanceCompetitionTask *param1)
{
    DanceMoveCommand v0;
    int v1;

    switch (param1->state) {
    case 0:
        param1->state++;
    case 1:
        for (v1 = 0; v1 < 4; v1++) {
            v0.command[v1] = param0->contest->contestantOrder[v1];
        }

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 4, &v0) == 1) {
            param1->state++;
        }
        break;
    default:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount - param0->contest->gameCodeMismatchCount - 1, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            return 3;
        }
        break;
    }

    return 0;
}

int contest_competition_0223F0BC(int param0, int param1)
{
    switch (param1) {
    case 3:
        return Unk_contest_competition_02252FC4[param0].unk_03 * 8;
    case 2:
        return Unk_contest_competition_02252FC4[param0].unk_03;
    case 1:
        return Unk_contest_competition_02252FC4[param0].unk_02;
    case 4:
        return Unk_contest_competition_02252FC4[param0].unk_02 * 2;
    case 0:
        return Unk_contest_competition_02252FC4[param0].unk_00;
    }

    GF_ASSERT(FALSE);
    return 0;
}
