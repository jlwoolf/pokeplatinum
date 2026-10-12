#include "contest_competition/contest_competition.h"

#include <nitro.h>
#include <string.h>

#include "battle_anim/battle_anim_system.h"
#include "battle_particles/particle_helper.h"
#include "contest_competition/const_contest_competition_022536B4.h"
#include "contest_competition/contest_competition_0223F118.h"
#include "contest_competition/contest_competition_0223F7E4.h"
#include "contest_competition/contest_competition_02241270.h"
#include "contest_competition/contest_competition_022413D8.h"
#include "contest_competition/contest_competition_02243AC4.h"
#include "contest_competition/contest_competition_02243C28.h"
#include "contest_competition/contest_competition_02245F14.h"
#include "contest_competition/contest_competition_02246ECC.h"
#include "contest_competition/contest_competition_0224F080.h"
#include "contest_competition/contest_competition_0224F18C.h"
#include "contest_competition/struct_acting_competition_task.h"
#include "contest_competition/struct_acting_mon_moves.h"
#include "contest_competition/struct_acting_competition.h"

#include "bg_window.h"
#include "comm_manager.h"
#include "contest.h"
#include "font.h"
#include "game_overlay.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "move_table.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "palette.h"
#include "particle_system.h"
#include "pokemon.h"
#include "pokemon_sprite.h"
#include "screen_fade.h"
#include "sound.h"
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

static void contest_competition_0223B728(BgConfig *param0);
static void contest_competition_0223B858(ActingCompetition *param0);
static void contest_competition_0223B884(void);
static void contest_competition_0223B6F0(SysTask *param0, void *param1);
static void contest_competition_0223B6BC(void *param0);
static void contest_competition_0223B8C4(ActingCompetition *param0);
static int contest_competition_0223BCE8(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223BD58(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223BDCC(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223BE58(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223BF1C(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223BFB0(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223C004(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223C068(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223C100(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223C2DC(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223C330(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223C350(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223BE54(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223C81C(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223C888(ActingCompetition *param0, ActingCompetitionTask *param1);
static int contest_competition_0223CA30(ActingCompetition *param0, ActingCompetitionTask *param1);
static void contest_competition_0223B8F8(ActingCompetition *param0, NARC *param1);
static void contest_competition_0223B9A4(ActingCompetition *param0);
static void contest_competition_0223BA10(ActingCompetition *param0, NARC *param1);
static void contest_competition_0223BAD0(ActingCompetition *param0);
static void contest_competition_0223BBA8(ActingCompetition *param0, NARC *param1);
static void contest_competition_0223BCDC(ActingCompetition *param0);
static void contest_competition_0223BCE0(ActingCompetition *param0, NARC *param1);
static void contest_competition_0223BCE4(ActingCompetition *param0);
void contest_competition_0223BB14(ActingCompetition *param0, int param1, int param2);

static int (*const Unk_contest_competition_02252E10[])(ActingCompetition *, ActingCompetitionTask *) = {
    contest_competition_0223BCE8,
    contest_competition_0223BD58,
    contest_competition_0223BDCC,
    contest_competition_0223BE54,
    contest_competition_0223BE58,
    contest_competition_0223BF1C,
    contest_competition_0223BFB0,
    contest_competition_0223C004,
    contest_competition_0223C068,
    contest_competition_0223C100,
    contest_competition_0223C2DC,
    contest_competition_0223C330,
    contest_competition_0223C350,
    contest_competition_0223C81C,
    contest_competition_0223C888,
    contest_competition_0223CA30
};

static const RenderOamTemplate Unk_contest_competition_02252DC8 = {
    0x0,
    0x80,
    0x0,
    0x20,
    0x0,
    0x80,
    0x0,
    0x20
};

static const CharTransferTemplateWithModes Unk_contest_competition_02252D9C = {
    0x60,
    0x10000,
    0x4000,
    GX_OBJVRAMMODE_CHAR_1D_64K,
    GX_OBJVRAMMODE_CHAR_1D_32K
};

static const SpriteResourceCapacities Unk_contest_competition_02252DB0 = {
    0x60,
    0x20,
    0x40,
    0x40,
    0x8,
    0x8
};

int ActingCompetition_Init(ApplicationManager *appMan, int *param1)
{
    ActingCompetition *v0;

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

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_21, 0x70000);

    v0 = ApplicationManager_NewData(appMan, sizeof(ActingCompetition), HEAP_ID_21);
    MI_CpuClear8(v0, sizeof(ActingCompetition));

    v0->g3dPipeline = contest_competition_0223F140(HEAP_ID_21);
    v0->contest = ApplicationManager_Args(appMan);
    v0->contest->appContext = v0;
    v0->contest->activeAppID = 2;
    v0->scene.contestData = &v0->contest->data;

    contest_competition_0223B8C4(v0);

    v0->scene.paletteData = PaletteData_New(HEAP_ID_21);

    PaletteData_SetAutoTransparent(v0->scene.paletteData, TRUE);
    PaletteData_AllocBuffer(v0->scene.paletteData, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_21);
    PaletteData_AllocBuffer(v0->scene.paletteData, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_21);
    PaletteData_AllocBuffer(v0->scene.paletteData, PLTTBUF_MAIN_OBJ, PALETTE_SIZE_BYTES * 14, HEAP_ID_21);
    PaletteData_AllocBuffer(v0->scene.paletteData, PLTTBUF_SUB_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_21);

    v0->scene.bgConfig = BgConfig_New(HEAP_ID_21);

    VramTransfer_New(64, HEAP_ID_21);
    SetAutorepeat(4, 8);

    v0->moveMenu = contest_competition_0223F88C(v0->contest, &v0->scene, &v0->matchState);

    contest_competition_0223B728(v0->scene.bgConfig);

    EnableTouchPad();
    InitializeTouchPad(4);
    Font_InitManager(FONT_SUBSCREEN, HEAP_ID_21);

    v0->scene.spriteSystem = SpriteSystem_Alloc(HEAP_ID_21);
    SpriteSystem_Init(v0->scene.spriteSystem, &Unk_contest_competition_02252DC8, &Unk_contest_competition_02252D9C, 16 + 16);
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    v0->scene.spriteManager = SpriteManager_New(v0->scene.spriteSystem);

    SpriteSystem_InitSprites(v0->scene.spriteSystem, v0->scene.spriteManager, 64 + 64);
    SpriteSystem_InitManagerWithCapacities(v0->scene.spriteSystem, v0->scene.spriteManager, &Unk_contest_competition_02252DB0);
    SetSubScreenViewRect(SpriteSystem_GetRenderer(v0->scene.spriteSystem), 0, (192 + 80) << FX32_SHIFT);

    v0->scene.pokemonSpriteManager = PokemonSpriteManager_New(HEAP_ID_21);
    contest_competition_0223B884();

    v0->scene.battleAnimSystem = BattleAnimSystem_New(HEAP_ID_21);
    BattleAnimSystem_SetIsContest(v0->scene.battleAnimSystem, 1);

    v0->scene.contestTextMessageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_CONTEST_TEXT, HEAP_ID_21);
    v0->scene.contestOpponentNames = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_CONTEST_OPPONENT_NAMES, HEAP_ID_21);
    v0->scene.contestEffectMessages = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_CONTEST_EFFECTS, HEAP_ID_21);
    v0->scene.contestActingCompetitionMessages = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_CONTEST_ACTING_COMPETITION, HEAP_ID_21);
    v0->scene.fontOAMManager = FontOAMManager_New(2 * 4, HEAP_ID_21);
    v0->scene.stringTemplate = StringTemplate_Default(HEAP_ID_21);
    v0->scene.string = String_Init(3 * 160, HEAP_ID_21);

    {
        NARC *v1;
        NARC *v2;

        v1 = NARC_ctor(NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, HEAP_ID_21);
        v2 = NARC_ctor(NARC_INDEX_CONTEST__GRAPHIC__CONTEST_OBJ, HEAP_ID_21);

        contest_competition_0223BBA8(v0, v1);
        contest_competition_0223BCE0(v0, v1);
        contest_competition_0223B858(v0);
        contest_competition_02241428(v0);
        contest_competition_0223B8F8(v0, v2);
        contest_competition_0223BA10(v0, v2);

        NARC_dtor(v1);
        NARC_dtor(v2);
    }

    {
        u16 moves[4];

        for (int i = 0; i < LEARNED_MOVES_MAX; i++) {
            moves[i] = Pokemon_GetValue(v0->contest->data.contestMons[v0->contest->data.playerContestantID], MON_DATA_MOVE1 + i, NULL);
        }

        contest_competition_02240A80(v0->moveMenu, moves);
    }

    contest_competition_0223F9C4(v0->moveMenu, 0, 1, NULL);
    contest_competition_022415E4(&v0->scene);

    NetworkIcon_Init();
    StartScreenFade(FADE_MAIN_THEN_SUB, FADE_TYPE_UNK_31, FADE_TYPE_UNK_31, COLOR_BLACK, 6, 1, HEAP_ID_21);

    v0->task = SysTask_Start(contest_competition_0223B6F0, v0, 60000);
    v0->initialized = 1;

    GXLayers_TurnBothDispOn();
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
    Sound_SetSceneAndPlayBGM(SOUND_SCENE_CONTEST, CONTEST_DRESSING_ROOM_sseq, 1);
    SetLockTextWithAutoScroll(v0->contest->isLinkContest);
    SetVBlankCallback(contest_competition_0223B6BC, v0);

    return 1;
}

int ActingCompetition_Main(ApplicationManager *appMan, int *param1)
{
    ActingCompetition *v0 = ApplicationManager_Data(appMan);
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
            v1 = Unk_contest_competition_02252E10[v0->handlerIndex](v0, &v0->competitionTask);

            if ((v1 == 1) || (v1 == 2)) {
                if (v1 == 1) {
                    v0->handlerIndex++;
                } else {
                    v0->handlerIndex = v0->competitionTask.nextState;
                }

                MI_CpuClear8(&v0->competitionTask, sizeof(ActingCompetitionTask));
            } else if ((v1 == 3) && (v0->initialized2 == 1)) {
                *param1 = 2;
                MI_CpuClear8(&v0->competitionTask, sizeof(ActingCompetitionTask));
                StartScreenFade(FADE_SUB_THEN_MAIN, FADE_TYPE_UNK_32, FADE_TYPE_UNK_32, COLOR_BLACK, 6, 1, HEAP_ID_21);
                break;
            }
        }

        contest_competition_0224F35C(&v0->packetQueue);
        contest_competition_0224F3D8(&v0->packetQueue, v0);

        if ((v0->initialized2 == 1) && (contest_competition_0224F3D0(&v0->packetQueue) == 0) && (Contest_IsPlayerLeader(v0->contest) == FALSE)) {
            *param1 = 2;
            MI_CpuClear8(&v0->competitionTask, sizeof(ActingCompetitionTask));
            StartScreenFade(FADE_SUB_THEN_MAIN, FADE_TYPE_UNK_32, FADE_TYPE_UNK_32, COLOR_BLACK, 6, 1, HEAP_ID_21);
        }
        break;
    case 2:
        if (v0->initialized2 == 1) {
            if (IsScreenFadeDone() == TRUE) {
                return 1;
            }
        }
        break;
    }

    return 0;
}

int ActingCompetition_Exit(ApplicationManager *appMan, int *param1)
{
    ActingCompetition *v0 = ApplicationManager_Data(appMan);
    int v1;

    ParticleSystem_FreeAll();

    BattleAnimSystem_Delete(v0->scene.battleAnimSystem);
    contest_competition_0223B9A4(v0);
    contest_competition_0223BAD0(v0);
    contest_competition_0223BCDC(v0);
    contest_competition_0223BCE4(v0);

    for (v1 = 0; v1 < 1; v1++) {
        Window_Remove(&v0->scene.windows[v1]);
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    Bg_FreeTilemapBuffer(v0->scene.bgConfig, 1);
    Bg_FreeTilemapBuffer(v0->scene.bgConfig, 2);
    Bg_FreeTilemapBuffer(v0->scene.bgConfig, 3);

    contest_competition_0223F864(v0->scene.bgConfig);
    contest_competition_0223F960(v0->moveMenu);

    SpriteSystem_FreeResourcesAndManager(v0->scene.spriteSystem, v0->scene.spriteManager);
    SpriteSystem_Free(v0->scene.spriteSystem);
    VramTransfer_Free();

    contest_competition_022416E4(&v0->scene);

    PokemonSpriteManager_Free(v0->scene.pokemonSpriteManager);
    Font_Free(FONT_SUBSCREEN);
    FontOAMManager_Free(v0->scene.fontOAMManager);

    PaletteData_FreeBuffer(v0->scene.paletteData, PLTTBUF_MAIN_BG);
    PaletteData_FreeBuffer(v0->scene.paletteData, PLTTBUF_SUB_BG);
    PaletteData_FreeBuffer(v0->scene.paletteData, PLTTBUF_MAIN_OBJ);
    PaletteData_FreeBuffer(v0->scene.paletteData, PLTTBUF_SUB_OBJ);
    PaletteData_Free(v0->scene.paletteData);

    String_Free(v0->scene.string);
    StringTemplate_Free(v0->scene.stringTemplate);
    MessageLoader_Free(v0->scene.contestTextMessageLoader);
    MessageLoader_Free(v0->scene.contestOpponentNames);
    MessageLoader_Free(v0->scene.contestEffectMessages);
    MessageLoader_Free(v0->scene.contestActingCompetitionMessages);

    Heap_Free(v0->scene.bgConfig);
    SysTask_Done(v0->task);

    contest_competition_0223F1E0(v0->g3dPipeline);

    DisableTouchPad();
    ApplicationManager_FreeData(appMan);
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    Heap_Destroy(HEAP_ID_21);
    LockTextSpeed();
    NetworkIcon_Destroy();
    Overlay_UnloadByID(FS_OVERLAY_ID(battle_particles));
    Overlay_UnloadByID(FS_OVERLAY_ID(battle_anim));
    Overlay_UnloadByID(FS_OVERLAY_ID(image_clip_app));

    return 1;
}

static void contest_competition_0223B6BC(void *param0)
{
    ActingCompetition *v0 = param0;

    PokemonSpriteManager_UpdateCharAndPltt(v0->scene.pokemonSpriteManager);
    VramTransfer_Process();
    SpriteSystem_TransferOam();
    PaletteData_CommitFadedBuffers(v0->scene.paletteData);
    Bg_RunScheduledUpdates(v0->scene.bgConfig);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void contest_competition_0223B6F0(SysTask *param0, void *param1)
{
    ActingCompetition *v0 = param1;

    if (v0->initialized == 1) {
        PokemonSpriteManager_DrawSprites(v0->scene.pokemonSpriteManager);
        ParticleHelper_DrawParticleSystems();
        SpriteSystem_DrawSprites(v0->scene.spriteManager);
        SpriteSystem_UpdateTransfer();
        G3_SwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
    }

    CommManager_Dummy_02038A1C(21, v0->scene.bgConfig);
}

static void contest_competition_0223B728(BgConfig *param0)
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
                .charBase = GX_BG_CHARBASE_0x04000,
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
                .screenBase = GX_BG_SCRBASE_0x3000,
                .charBase = GX_BG_CHARBASE_0x10000,
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
        contest_competition_0223F80C(param0);
    }
}

static void contest_competition_0223B858(ActingCompetition *param0)
{
    Window_Add(param0->scene.bgConfig, &param0->scene.windows[0], 1, 11, 0x13, 20, 4, 0xd, (0x8000 - 0x2000) / 32);
}

static void contest_competition_0223B884(void)
{
    NNSGfdTexKey v0;
    NNSGfdPlttKey v1;
    u32 v2, v3;

    v0 = NNS_GfdAllocTexVram(0x2000 * 4, 0, 0);
    v1 = NNS_GfdAllocPlttVram(0x20 * 4, 0, 0);

    GF_ASSERT(v0 != NNS_GFD_ALLOC_ERROR_TEXKEY);
    GF_ASSERT(v1 != NNS_GFD_ALLOC_ERROR_PLTTKEY);

    v2 = NNS_GfdGetTexKeyAddr(v0);
    v3 = NNS_GfdGetPlttKeyAddr(v1);

    ParticleSystem_ZeroAll();
}

static void contest_competition_0223B8C4(ActingCompetition *param0)
{
    int v0;

    GF_ASSERT(param0->contest != NULL);

    for (v0 = 0; v0 < 4; v0++) {
        param0->matchState.contestantOrder[v0] = param0->contest->contestantOrder[v0];
    }

    contest_competition_02243C28(param0);
}

static void contest_competition_0223B8F8(ActingCompetition *param0, NARC *param1)
{
    SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->scene.paletteData, 2, param0->scene.spriteSystem, param0->scene.spriteManager, param1, 0, 0, 6, NNS_G2D_VRAM_TYPE_2DMAIN, 33001);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->scene.paletteData, 2, param0->scene.spriteSystem, param0->scene.spriteManager, param1, 9, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 33005);

    contest_competition_02243040(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_02242FA4(param0);
    contest_competition_02241928(&param0->scene, param0->contest, param1);
    contest_competition_02241D94(&param0->scene, param0->contest->data.bonusJudgeIndex, param1);
    contest_competition_022419AC(param0->scene.paletteData, param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_02241A24(&param0->scene);
    contest_competition_02241E58(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_02242154(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
}

static void contest_competition_0223B9A4(ActingCompetition *param0)
{
    contest_competition_02241E24(&param0->scene);
    contest_competition_0224197C(&param0->scene);
    contest_competition_02242FC0(param0);
    contest_competition_022430F8(&param0->scene);
    contest_competition_0224308C(param0->scene.spriteManager);

    SpriteManager_UnloadPlttObjById(param0->scene.spriteManager, 33001);
    SpriteManager_UnloadPlttObjById(param0->scene.spriteManager, 33005);

    contest_competition_02241A64(&param0->scene);
    contest_competition_02241A00(param0->scene.spriteManager);

    contest_competition_02241EA4(param0->scene.spriteManager);
    contest_competition_02241EF0(&param0->scene);
    contest_competition_022421E0(param0->scene.spriteManager);
    contest_competition_02242248(&param0->scene);
}

static void contest_competition_0223BA10(ActingCompetition *param0, NARC *param1)
{
    SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->scene.paletteData, 3, param0->scene.spriteSystem, param0->scene.spriteManager, param1, 4, 0, 3, NNS_G2D_VRAM_TYPE_2DSUB, 33007);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->scene.paletteData, 3, param0->scene.spriteSystem, param0->scene.spriteManager, param1, 9, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 33008);

    contest_competition_0224131C(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_02241270(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_0224F0F0(param0->scene.spriteSystem, param0->scene.spriteManager, 33012, 33012);

    {
        int v0, moveContestType, v2;

        for (v0 = 0; v0 < LEARNED_MOVES_MAX; v0++) {
            v2 = Pokemon_GetValue(param0->contest->data.contestMons[param0->contest->data.playerContestantID], MON_DATA_MOVE1 + v0, NULL);

            if (v2 != 0) {
                moveContestType = MoveTable_LoadParam(v2, MOVEATTRIBUTE_CONTEST_TYPE);
            } else {
                moveContestType = 0;
            }

            contest_competition_0224F0BC(param0->scene.spriteSystem, param0->scene.spriteManager, NNS_G2D_VRAM_TYPE_2DSUB, moveContestType, 33014 + v0);
        }
    }
}

static void contest_competition_0223BAD0(ActingCompetition *param0)
{
    SpriteManager_UnloadPlttObjById(param0->scene.spriteManager, 33007);

    contest_competition_022413B4(param0->scene.spriteManager);
    contest_competition_022412F0(param0->scene.spriteManager);
    contest_competition_0224F140(param0->scene.spriteManager, 33012, 33012);

    {
        int v0;

        for (v0 = 0; v0 < 4; v0++) {
            contest_competition_0224F138(param0->scene.spriteManager, 33014 + v0);
        }
    }
}

void contest_competition_0223BB14(ActingCompetition *param0, int param1, int param2)
{
    if (param1 == 0) {
        Graphics_LoadTilesToBgLayer(NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, 3, param0->scene.bgConfig, 2, 0, 0x4000, 1, HEAP_ID_21);
        Graphics_LoadTilemapToBgLayer(NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, 5, param0->scene.bgConfig, 2, 0, 0, 1, HEAP_ID_21);
        Bg_SetPriority(BG_LAYER_MAIN_1, 1);
        Bg_SetPriority(BG_LAYER_MAIN_2, 0);

        contest_competition_02241428(param0);

        if (param2 == 1) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
        }
    } else {
        Bg_ClearTilesRange(BG_LAYER_MAIN_2, 0x4000, 0, HEAP_ID_21);
        Bg_ClearTilemap(param0->scene.bgConfig, 2);
        Bg_SetPriority(BG_LAYER_MAIN_1, 0);
        Bg_SetPriority(BG_LAYER_MAIN_2, 1);
    }
}

static void contest_competition_0223BBA8(ActingCompetition *param0, NARC *param1)
{
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 1, param0->scene.bgConfig, 3, 0, 0, 1, HEAP_ID_21);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 2, param0->scene.bgConfig, 3, 0, 0, 1, HEAP_ID_21);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 3, param0->scene.bgConfig, 1, 0, 0, 1, HEAP_ID_21);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 4, param0->scene.bgConfig, 1, 0, 0, 1, HEAP_ID_21);

    contest_competition_0223BB14(param0, 0, 0);

    PaletteData_LoadBufferFromFileStart(param0->scene.paletteData, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, 30, HEAP_ID_21, PLTTBUF_MAIN_BG, 0, PLTT_DEST(0));

    u16 *v0, *v1, *v2, *v3;

    v0 = Heap_Alloc(HEAP_ID_21, PALETTE_SIZE_BYTES);
    v1 = Heap_Alloc(HEAP_ID_21, PALETTE_SIZE_BYTES);
    v2 = PaletteData_GetUnfadedBuffer(param0->scene.paletteData, PLTTBUF_MAIN_BG);
    v3 = PaletteData_GetFadedBuffer(param0->scene.paletteData, PLTTBUF_MAIN_BG);

    MI_CpuCopy16(&v2[Unk_contest_competition_022536B4[0] * 16], v0, PALETTE_SIZE_BYTES);
    MI_CpuCopy16(&v2[Unk_contest_competition_022536B4[param0->contest->data.playerContestantID] * 16], v1, PALETTE_SIZE_BYTES);
    MI_CpuCopy16(v0, &v2[Unk_contest_competition_022536B4[param0->contest->data.playerContestantID] * 16], PALETTE_SIZE_BYTES);
    MI_CpuCopy16(v1, &v2[Unk_contest_competition_022536B4[0] * 16], PALETTE_SIZE_BYTES);
    MI_CpuCopy16(v0, &v3[Unk_contest_competition_022536B4[param0->contest->data.playerContestantID] * 16], PALETTE_SIZE_BYTES);
    MI_CpuCopy16(v1, &v3[Unk_contest_competition_022536B4[0] * 16], PALETTE_SIZE_BYTES);

    Heap_Free(v0);
    Heap_Free(v1);
}

static void contest_competition_0223BCDC(ActingCompetition *param0)
{
    return;
}

static void contest_competition_0223BCE0(ActingCompetition *param0, NARC *param1)
{
    return;
}

static void contest_competition_0223BCE4(ActingCompetition *param0)
{
    return;
}

static int contest_competition_0223BCE8(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (param0->contest->gameCodeMismatchCount > 0) {
            if (param1->timer < 120) {
                param1->timer++;
                break;
            }
        }

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 2, NULL) == 1) {
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

static int contest_competition_0223BD58(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    if (Contest_IsPracticeCompetition(param0->contest) == FALSE) {
        return 1;
    }

    switch (param1->state) {
    case 0:
        param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_NONE;
        param0->syncPacket.messages.delay = 0;
        param0->syncPacket.messages.messageFlag = 0;

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 20, &param0->syncPacket) == 1) {
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

static int contest_competition_0223BDCC(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:

        if (Contest_IsPracticeCompetition(param0->contest) == TRUE) {
            param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_BEGIN_PRACTICE;
        } else {
            param0->syncPacket.messages.actingMessagesID = Contest_GetActingCompetitionMessageIntroAnnouncement(param0->contest->data.contestType);
        }

        param0->syncPacket.messages.delay = 0;
        param0->syncPacket.messages.messageFlag = 0;

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 20, &param0->syncPacket) == 1) {
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

static int contest_competition_0223BE54(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
    default:
        return 1;
    }

    return 0;
}

static int contest_competition_0223BE58(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 8, NULL) == 1) {
            param1->state++;
        }
        break;
    case 1:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    case 2: {
        ActingMonMoves v0;

        contest_competition_02246ECC(param0, &v0);

        for (int contestantID = param0->contest->data.connectionCount; contestantID < CONTEST_NUM_PARTICIPANTS; contestantID++) {
            param0->matchState.moveIDs[contestantID] = v0.moveIDs[contestantID];
            param0->matchState.contestantIDs[contestantID] = v0.moveSlots[contestantID];
        }
    }
        param1->state++;
        break;
    default:
        contest_competition_02245F44(param0, &param0->syncPacket.turnState);
        return 1;
    }

    return 0;
}

static int contest_competition_0223BF1C(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    int v1, v2;

    int contestantID = param0->matchState.contestantOrder[param0->matchState.contestantCount];

    param0->syncPacket.contestantID = contestantID;
    param0->syncPacket.contestantCount = param0->matchState.contestantCount;
    param0->syncPacket.judgeContestantID = param0->matchState.contestantIDs[contestantID];
    param0->syncPacket.isSameJudge = 0;

    for (v1 = 0; v1 < param0->matchState.contestantCount; v1++) {
        v2 = param0->matchState.contestantOrder[v1];

        if (param0->matchState.contestantIDs[v2] == param0->matchState.contestantIDs[contestantID]) {
            param0->syncPacket.isSameJudge = 1;
        }
    }

    contest_competition_02243120(param0, &param0->syncPacket.messages.messageParams, contestantID);
    contest_competition_02243120(param0, &param0->syncPacket.messages.messageParams2, contestantID);

    return 1;
}

static int contest_competition_0223BFB0(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 4, &param0->syncPacket) == 1) {
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

static int contest_competition_0223C004(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_NONE;

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 6, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    default:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_NONE;
            return 1;
        }
        break;
    }

    return 0;
}

static int contest_competition_0223C068(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_TO_JUDGE_MON_PERFORMED_MOVE;

        if (param0->syncPacket.isSameJudge == 1) {
            param0->syncPacket.messages.actingMessagesID2 = ACTING_COMPETITION_MESSAGE_SOMEONE_ALREADY_PERFORMED_FOR_JUDGE;
        } else {
            param0->syncPacket.messages.actingMessagesID2 = ACTING_COMPETITION_MESSAGE_NONE;
        }

        contest_competition_022460DC(param0, &param0->syncPacket.turnState, param0->syncPacket.contestantID);
        param1->state++;
    case 1:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 7, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    default:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_NONE;
            param0->syncPacket.messages.actingMessagesID2 = ACTING_COMPETITION_MESSAGE_NONE;
            return 1;
        }
        break;
    }

    return 0;
}

static int contest_competition_0223C100(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        contest_competition_02245FB4(param0, &param0->syncPacket.turnState, param0->syncPacket.contestantID);
        param1->state++;
        break;
    case 1:
        contest_competition_02246138(param0, &param0->syncPacket.turnState, param0->syncPacket.contestantID);
        param1->state++;
    case 2:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 10, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    case 3:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    case 4:
        contest_competition_02246160(param0, &param0->syncPacket.turnState, param0->syncPacket.contestantID, param0->syncPacket.contestantCount);
        param1->state++;
    case 5:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 11, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    case 6:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    case 7:
        contest_competition_02246228(param0, &param0->syncPacket.turnState, param0->syncPacket.contestantID, param0->syncPacket.contestantCount);
        param1->state++;
    case 8:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 12, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    case 9:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    case 10:
        contest_competition_022463C4(param0, &param0->syncPacket.turnState, param0->syncPacket.contestantID, &param0->syncPacket.messages);
        param1->state++;
    case 11:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 13, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    case 12:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    default:
        contest_competition_02246018(param0, &param0->syncPacket.turnState, param0->syncPacket.contestantID);
        return 1;
    }

    return 0;
}

static int contest_competition_0223C2DC(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    int v0;

    switch (param1->state) {
    case 0:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 5, &param0->syncPacket) == 1) {
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

static int contest_competition_0223C330(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    param0->matchState.contestantCount++;

    if (param0->matchState.contestantCount >= 4) {
        return 1;
    } else {
        param1->nextState = 5;
        return 2;
    }
}

static int contest_competition_0223C350(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    BOOL v0;

    switch (param1->state) {
    case 0:
        param1->state++;
        break;
    case 1:
        param0->syncPacket.contestantID = param0->matchState.contestantOrder[param1->timer];
        param0->syncPacket.contestantCount = param1->timer;
        param1->state++;
    case 2:
        v0 = contest_competition_022462A4(param0, &param0->syncPacket.turnState, param0->syncPacket.contestantID, param0->syncPacket.contestantCount);

        if (v0 == 1) {
            param1->state++;
        } else {
            param1->state = 5;
        }
        break;
    case 3:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 14, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    case 4:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    case 5:
        param1->timer++;

        if (param1->timer >= 4) {
            param1->timer = 0;
            param1->state++;
        } else {
            param1->state = 1;
        }
        break;
    case 6: {
        int v1;

        for (v1 = 0; v1 < 4; v1++) {
            contest_competition_02246518(param0, &param0->syncPacket.turnState, v1, &param0->syncPacket.messages);
        }
    }
        param1->state++;
        break;
    case 7: {
        int v2[(1 + 2)];
        int v3[(1 + 2)];
        int v4[(1 + 2)][4];
        int v5, v6, v7, v8;

        for (v5 = 0; v5 < (1 + 2); v5++) {
            v2[v5] = 0;
            v3[v5] = v5;

            for (v6 = 0; v6 < 4; v6++) {
                v4[v5][v6] = 4;
            }
        }

        for (v5 = 0; v5 < 4; v5++) {
            v8 = param0->matchState.contestantOrder[v5];
            v2[param0->matchState.contestantIDs[v8]]++;

            for (v6 = 0; v6 < 4; v6++) {
                if (v4[param0->matchState.contestantIDs[v8]][v6] == 4) {
                    v4[param0->matchState.contestantIDs[v8]][v6] = v8;
                    break;
                }
            }
        }

        for (v5 = 0; v5 < (1 + 2) - 1; v5++) {
            for (v6 = (1 + 2) - 1; v6 > v5; v6--) {
                if (v2[v6 - 1] < v2[v6]) {
                    v7 = v2[v6];
                    v2[v6] = v2[v6 - 1];
                    v2[v6 - 1] = v7;

                    v7 = v3[v6];
                    v3[v6] = v3[v6 - 1];
                    v3[v6 - 1] = v7;
                }
            }
        }

        param0->syncPacket.performanceOrder.contestantID = v3[param1->timer];

        for (v5 = 0; v5 < 4; v5++) {
            param0->syncPacket.performanceOrder.order[v5] = v4[v3[param1->timer]][v5];
        }

        // how many mons selected each judge
        switch (v2[param1->timer]) {
        case 1:
            param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_JUDGE_VERY_IMPRESSED;
            break;
        case 2:
            param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_JUDGE_STRONGLY_IMPRESSED;
            break;
        case 3:
            param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_JUDGE_WAS_IMPRESSED;
            break;
        case 4:
            param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_EVERYONE_PERFORMED_FOR_SAME_JUDGE;
            break;
        default:
            param1->state = 12;
            return 0;
        }
    }

        param0->syncPacket.messages.actingMessagesID2 = ACTING_COMPETITION_MESSAGE_NONE;

        contest_competition_02243120(param0, &param0->syncPacket.messages.messageParams, param0->syncPacket.contestantID);
        contest_competition_02243120(param0, &param0->syncPacket.messages.messageParams2, param0->syncPacket.contestantID);

        param1->state++;
    case 8:
        param1->state++;
        break;
    case 9:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 16, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    case 10:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_NONE;
            param0->syncPacket.messages.actingMessagesID2 = ACTING_COMPETITION_MESSAGE_NONE;
            param1->state++;
        }
        break;
    case 11:
        param1->timer++;

        if (param1->timer < (1 + 2)) {
            param1->state = 7;
        } else {
            param1->state++;
        }
        break;
    case 12:
        param1->timer = 0;
        param1->state++;
        break;
    case 13:
        param0->syncPacket.contestantID = param0->matchState.contestantOrder[param1->timer];
        param0->syncPacket.contestantCount = param1->timer;
        param1->state++;
    case 14:
        v0 = contest_competition_02246304(param0, &param0->syncPacket.turnState, param0->syncPacket.contestantID, param0->syncPacket.contestantCount);

        if (v0 == 0) {
            param1->state = 17;
        } else {
            param1->state++;
        }
        break;
    case 15:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 17, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    case 16:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_NONE;
            param0->syncPacket.messages.actingMessagesID2 = ACTING_COMPETITION_MESSAGE_NONE;
            param1->state++;
        }
        break;
    case 17:
        param1->timer++;

        if (param1->timer < 4) {
            param1->state = 13;
        } else {
            param1->state++;
        }
        break;
    case 18:
        param1->timer = 0;
        param1->state++;
        break;
    case 19:
        contest_competition_022460C8(&param0->syncPacket.turnState);
        param1->state++;
    case 20:
        param0->syncPacket.contestantID = param0->matchState.contestantOrder[param1->timer];
        param0->syncPacket.contestantCount = param1->timer;
        param1->state++;
    case 21:
        v0 = contest_competition_02246364(param0, &param0->syncPacket.turnState, param0->syncPacket.contestantID, param0->syncPacket.contestantCount);

        if (v0 == 1) {
            param1->state++;
        } else {
            param1->state = 24;
        }
        break;
    case 22:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 15, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    case 23:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    case 24:
        param1->timer++;

        if (param1->timer >= 4) {
            param1->timer = 0;
            param1->state++;
        } else {
            param1->state = 20;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

static int contest_competition_0223C81C(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        param1->state++;
        break;
    case 1:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 18, &param0->syncPacket) == 1) {
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

static int contest_competition_0223C888(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    int v0;

    switch (param1->state) {
    case 0:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 21, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    case 1:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    case 2: {
        int v1;

        v1 = 0;

        for (v0 = 0; v0 < CONTEST_NUM_PARTICIPANTS; v0++) {
            if (param0->syncPacket.turnState.performances[v0].judgeAppealState != 0) {
                v1++;
            }
        }

        if ((param0->matchState.turn < 4 - 1) && (v1 < 4)) {
            param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_NEXT_TURN_LOWEST_SCORING_PERFORM_FIRST;
        } else {
            param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_NONE;
        }
    }
        param0->syncPacket.messages.delay = 0;
        param0->syncPacket.messages.messageFlag = 0;

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 20, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    case 3:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    case 4:
        contest_competition_02246044(param0, &param0->syncPacket.turnState);
        contest_competition_02243B0C(&param0->matchState);

        for (v0 = 0; v0 < CONTEST_NUM_PARTICIPANTS; v0++) {
            param0->matchState.previousMoveIDs[v0] = param0->matchState.moveIDs[v0];
        }

        param0->matchState.turn++;
        param1->state++;
        break;
    case 5:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 19, &param0->matchState) == 1) {
            param1->state++;
        }
        break;
    case 6:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    default:
        if (param0->matchState.turn >= 4) {
            param1->nextState = 15;
            return 2;
        } else {
            param0->matchState.contestantCount = 0;
            param1->nextState = 3;
            return 2;
        }
        break;
    }

    return 0;
}

static int contest_competition_0223CA30(ActingCompetition *param0, ActingCompetitionTask *param1)
{
    switch (param1->state) {
    case 0: {
        int v0;

        for (v0 = 0; v0 < 4; v0++) {
            param0->contest->data.results[v0].actingScore = param0->matchState.scores[v0];
        }
    }
        param1->state++;

    case 1:
        param0->syncPacket.messages.actingMessagesID = ACTING_COMPETITION_MESSAGE_JUDGING_IS_OVER;
        param0->syncPacket.messages.actingMessagesID2 = ACTING_COMPETITION_MESSAGE_NONE;

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 3, &param0->syncPacket) == 1) {
            param1->state++;
        }
        break;
    case 2:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    case 3:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 1, NULL) == 1) {
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
