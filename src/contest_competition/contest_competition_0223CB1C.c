#include "contest_competition/contest_competition_0223CB1C.h"

#include <nitro.h>
#include <string.h>

#include "battle_particles/particle_helper.h"
#include "contest_competition/contest_competition_0223F118.h"
#include "contest_competition/contest_competition_022476F8.h"
#include "contest_competition/contest_competition_02247A48.h"
#include "contest_competition/contest_competition_0224F18C.h"
#include "contest_competition/struct_visual_competition_task.h"
#include "contest_competition/struct_visual_competition.h"
#include "image_clip_app/image_clip_app_0225AF8C.h"

#include "bg_window.h"
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
#include "contest_util.h"
#include "vram_transfer.h"

FS_EXTERN_OVERLAY(battle_particles);
FS_EXTERN_OVERLAY(battle_anim);
FS_EXTERN_OVERLAY(image_clip_app);

static void contest_competition_0223D0C8(void *param0);
static void contest_competition_0223D164(SysTask *param0, void *param1);
static void contest_competition_0223D1B8(BgConfig *param0);
static void contest_competition_0223D324(VisualCompetition *param0);
static void contest_competition_0223D390(VisualCompetition *param0);
static void contest_competition_0223D3B8(VisualCompetition *param0, NARC *param1);
static void contest_competition_0223D434(VisualCompetition *param0);
static void contest_competition_0223D468(VisualCompetition *param0, NARC *param1);
static void contest_competition_0223D498(VisualCompetition *param0);
static void contest_competition_0223D4A8(VisualCompetition *param0, NARC *param1);
static void contest_competition_0223D5AC(VisualCompetition *param0);
static void contest_competition_0223D5B0(VisualCompetition *param0, NARC *param1);
static void contest_competition_0223D608(VisualCompetition *param0);
static int contest_competition_0223D60C(VisualCompetition *param0, VisualCompetitionTask *param1);
static int contest_competition_0223D640(VisualCompetition *param0, VisualCompetitionTask *param1);
static int contest_competition_0223D99C(VisualCompetition *param0, VisualCompetitionTask *param1);
static int contest_competition_0223DA78(VisualCompetition *param0, VisualCompetitionTask *param1);
static void contest_competition_0223D350(void);
static int contest_competition_0223D6B8(VisualCompetition *param0, VisualCompetitionTask *param1);
static int contest_competition_0223D7DC(VisualCompetition *param0, VisualCompetitionTask *param1);
static int contest_competition_0223D82C(VisualCompetition *param0, VisualCompetitionTask *param1);
static int contest_competition_0223D8DC(VisualCompetition *param0, VisualCompetitionTask *param1);
static int contest_competition_0223D96C(VisualCompetition *param0, VisualCompetitionTask *param1);
static int contest_competition_0223D71C(VisualCompetition *param0, VisualCompetitionTask *param1);
static int contest_competition_0223D78C(VisualCompetition *param0, VisualCompetitionTask *param1);

static int (*const Unk_contest_competition_02252F44[])(VisualCompetition *, VisualCompetitionTask *) = {
    contest_competition_0223D60C,
    contest_competition_0223D640,
    contest_competition_0223D6B8,
    contest_competition_0223D71C,
    contest_competition_0223D82C,
    contest_competition_0223D7DC,
    contest_competition_0223D78C,
    contest_competition_0223D8DC,
    contest_competition_0223D96C,
    contest_competition_0223D99C,
    contest_competition_0223DA78
};

static const RenderOamTemplate Unk_contest_competition_02252EFC = {
    0x0,
    0x80,
    0x0,
    0x20,
    0x0,
    0x80,
    0x0,
    0x20
};

static const CharTransferTemplateWithModes Unk_contest_competition_02252EB4 = {
    0x60,
    0x10000,
    0x4000,
    GX_OBJVRAMMODE_CHAR_1D_64K,
    GX_OBJVRAMMODE_CHAR_1D_32K
};

static const SpriteResourceCapacities Unk_contest_competition_02252EC8 = {
    0x60,
    0x20,
    0x40,
    0x40,
    0x8,
    0x8
};

int VisualCompetitionScoring_Init(ApplicationManager *appMan, int *param1)
{
    VisualCompetition *v0;

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

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_22, 0x70000);

    v0 = ApplicationManager_NewData(appMan, sizeof(VisualCompetition), HEAP_ID_22);
    MI_CpuClear8(v0, sizeof(VisualCompetition));

    v0->g3dPipeline = contest_competition_0223F140(HEAP_ID_22);
    v0->contest = ApplicationManager_Args(appMan);
    v0->contest->appContext = v0;
    v0->contest->activeAppID = 0;
    v0->scene.contestData = &v0->contest->data;

    contest_competition_0223D390(v0);
    v0->scene.paletteData = PaletteData_New(HEAP_ID_22);

    PaletteData_SetAutoTransparent(v0->scene.paletteData, TRUE);
    PaletteData_AllocBuffer(v0->scene.paletteData, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_22);
    PaletteData_AllocBuffer(v0->scene.paletteData, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_22);
    PaletteData_AllocBuffer(v0->scene.paletteData, PLTTBUF_MAIN_OBJ, PALETTE_SIZE_BYTES * 14, HEAP_ID_22);
    PaletteData_AllocBuffer(v0->scene.paletteData, PLTTBUF_SUB_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_22);

    v0->scene.bgConfig = BgConfig_New(HEAP_ID_22);

    VramTransfer_New(64, HEAP_ID_22);
    SetAutorepeat(4, 8);

    contest_competition_0223D1B8(v0->scene.bgConfig);

    EnableTouchPad();
    InitializeTouchPad(4);
    Font_InitManager(FONT_SUBSCREEN, HEAP_ID_22);

    v0->scene.spriteSystem = SpriteSystem_Alloc(HEAP_ID_22);

    SpriteSystem_Init(v0->scene.spriteSystem, &Unk_contest_competition_02252EFC, &Unk_contest_competition_02252EB4, 16 + 16);
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    v0->scene.spriteManager = SpriteManager_New(v0->scene.spriteSystem);

    SpriteSystem_InitSprites(v0->scene.spriteSystem, v0->scene.spriteManager, 64 + 64);
    SpriteSystem_InitManagerWithCapacities(v0->scene.spriteSystem, v0->scene.spriteManager, &Unk_contest_competition_02252EC8);
    SetSubScreenViewRect(SpriteSystem_GetRenderer(v0->scene.spriteSystem), 0, 256 * FX32_ONE);

    v0->scene.pokemonSpriteManager = PokemonSpriteManager_New(HEAP_ID_22);
    contest_competition_0223D350();

    v0->scene.visualCompetitionMessages = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_CONTEST_VISUAL_COMPETITION, HEAP_ID_22);
    v0->scene.stringTemplate = StringTemplate_Default(HEAP_ID_22);
    v0->scene.string = String_Init(2 * 160, HEAP_ID_22);

    {
        NARC *v1;
        NARC *v2;

        v1 = NARC_ctor(NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, HEAP_ID_22);
        v2 = NARC_ctor(NARC_INDEX_CONTEST__GRAPHIC__CONTEST_OBJ, HEAP_ID_22);

        contest_competition_0223D4A8(v0, v1);
        contest_competition_0223D5B0(v0, v1);
        contest_competition_0223D324(v0);
        contest_competition_0223D3B8(v0, v2);
        contest_competition_0223D468(v0, v2);

        NARC_dtor(v1);
        NARC_dtor(v2);
    }

    PaletteData_FillBufferRange(v0->scene.paletteData, PLTTBUF_MAIN_BG, PLTTSEL_FADED, 0x7fff, 1, 16 * 16);
    PaletteData_FillBufferRange(v0->scene.paletteData, PLTTBUF_SUB_BG, PLTTSEL_FADED, 0x7fff, 1, 16 * 16);
    PaletteData_FillBufferRange(v0->scene.paletteData, PLTTBUF_MAIN_OBJ, PLTTSEL_FADED, 0x7fff, 0, (16 - 2) * 16);
    PaletteData_FillBufferRange(v0->scene.paletteData, PLTTBUF_SUB_OBJ, PLTTSEL_FADED, 0x7fff, 0, 16 * 16);
    NetworkIcon_Init();
    StartScreenFade(FADE_MAIN_THEN_SUB, FADE_TYPE_UNK_27, FADE_TYPE_UNK_27, COLOR_BLACK, 6, 1, HEAP_ID_22);

    v0->task = SysTask_Start(contest_competition_0223D164, v0, 60000);
    v0->flag = 1;

    GXLayers_TurnBothDispOn();
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
    Sound_SetScene(SOUND_SCENE_NONE);
    Sound_SetSceneAndPlayBGM(SOUND_SCENE_CONTEST, CONTEST_DRESSING_ROOM_sseq, 1);
    SetLockTextWithAutoScroll(v0->contest->isLinkContest);
    SetVBlankCallback(contest_competition_0223D0C8, v0);
    Sound_PlayEffect(SEQ_SE_DP_DOOR_OPEN_sseq);

    return 1;
}

int VisualCompetitionScoring_Main(ApplicationManager *appMan, int *param1)
{
    VisualCompetition *v0 = ApplicationManager_Data(appMan);
    int v1;

    Contest_GetRNGNext(v0->contest);

    switch (*param1) {
    case 0:
        if (IsScreenFadeDone() == TRUE) {
            PaletteData_StartFade(v0->scene.paletteData, 0x1, 0xffff, 6, 16, 0, 0x7fff);
            PaletteData_StartFade(v0->scene.paletteData, 0x2, 0xffff, 6, 16, 0, 0x7fff);
            PaletteData_StartFade(v0->scene.paletteData, 0x4, 0x3fff, 6, 16, 0, 0x7fff);
            PaletteData_StartFade(v0->scene.paletteData, 0x8, 0xffff, 6, 16, 0, 0x7fff);
            Sound_PlayEffect(SEQ_SE_DP_CON_007_sseq);
            *param1 = 1;
        }
        break;
    case 1:
        if (Contest_IsPlayerLeader(v0->contest) == TRUE) {
            v1 = Unk_contest_competition_02252F44[v0->handlerIndex](v0, &v0->competitionTask);

            if ((v1 == 1) || (v1 == 2)) {
                if (v1 == 1) {
                    v0->handlerIndex++;
                } else {
                    v0->handlerIndex = v0->competitionTask.nextState;
                }

                MI_CpuClear8(&v0->competitionTask, sizeof(VisualCompetitionTask));
            } else if ((v1 == 3) && (v0->initialized == 1)) {
                *param1 = 2;
                MI_CpuClear8(&v0->competitionTask, sizeof(VisualCompetitionTask));
                StartScreenFade(FADE_SUB_THEN_MAIN, FADE_TYPE_CIRCLE_OUT, FADE_TYPE_UNK_36, COLOR_BLACK, 6, 1, HEAP_ID_22);
                break;
            }
        }

        contest_competition_0224F35C(&v0->packetQueue);
        contest_competition_0224F3D8(&v0->packetQueue, v0);

        if ((v0->initialized == 1) && (contest_competition_0224F3D0(&v0->packetQueue) == 0) && (Contest_IsPlayerLeader(v0->contest) == FALSE)) {
            *param1 = 2;
            MI_CpuClear8(&v0->competitionTask, sizeof(VisualCompetitionTask));
            StartScreenFade(FADE_SUB_THEN_MAIN, FADE_TYPE_CIRCLE_OUT, FADE_TYPE_UNK_36, COLOR_BLACK, 6, 1, HEAP_ID_22);
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

int VisualCompetitionScoring_Exit(ApplicationManager *appMan, int *param1)
{
    VisualCompetition *v0 = ApplicationManager_Data(appMan);
    int v1;

    ParticleSystem_FreeAll();

    contest_competition_0223D434(v0);
    contest_competition_0223D498(v0);
    contest_competition_0223D5AC(v0);
    contest_competition_0223D608(v0);

    for (v1 = 0; v1 < 1; v1++) {
        Window_Remove(&v0->scene.windows[v1]);
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    Bg_FreeTilemapBuffer(v0->scene.bgConfig, 1);
    Bg_FreeTilemapBuffer(v0->scene.bgConfig, 2);
    Bg_FreeTilemapBuffer(v0->scene.bgConfig, 3);
    Bg_ToggleLayer(BG_LAYER_SUB_0, 0);
    Bg_FreeTilemapBuffer(v0->scene.bgConfig, 4);
    SpriteSystem_FreeResourcesAndManager(v0->scene.spriteSystem, v0->scene.spriteManager);
    SpriteSystem_Free(v0->scene.spriteSystem);
    VramTransfer_Free();

    for (v1 = 0; v1 < 4; v1++) {
        if (v0->photoSprites[v1].photoSprite != NULL) {
            PhotoSprite_Free(v0->photoSprites[v1].photoSprite);
        }
    }

    contest_competition_02247734(&v0->scene);
    contest_competition_02247918(v0);

    PokemonSpriteManager_Free(v0->scene.pokemonSpriteManager);
    Font_Free(FONT_SUBSCREEN);
    PaletteData_FreeBuffer(v0->scene.paletteData, PLTTBUF_MAIN_BG);
    PaletteData_FreeBuffer(v0->scene.paletteData, PLTTBUF_SUB_BG);
    PaletteData_FreeBuffer(v0->scene.paletteData, PLTTBUF_MAIN_OBJ);
    PaletteData_FreeBuffer(v0->scene.paletteData, PLTTBUF_SUB_OBJ);
    PaletteData_Free(v0->scene.paletteData);
    StringTemplate_Free(v0->scene.stringTemplate);
    String_Free(v0->scene.string);
    MessageLoader_Free(v0->scene.visualCompetitionMessages);
    Heap_Free(v0->scene.bgConfig);
    SysTask_Done(v0->task);

    contest_competition_0223F1E0(v0->g3dPipeline);

    DisableTouchPad();
    ApplicationManager_FreeData(appMan);
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    Heap_Destroy(HEAP_ID_22);
    LockTextSpeed();
    NetworkIcon_Destroy();
    Overlay_UnloadByID(FS_OVERLAY_ID(battle_particles));
    Overlay_UnloadByID(FS_OVERLAY_ID(battle_anim));
    Overlay_UnloadByID(FS_OVERLAY_ID(image_clip_app));

    return 1;
}

static void contest_competition_0223D0C8(void *param0)
{
    VisualCompetition *v0 = param0;

    {
        G2_SetWnd0Position(v0->window0Left, v0->window0Top, v0->window0Right, v0->window0Bottom);
        G2_SetWnd1Position(v0->window1Left, v0->window1Top, v0->window1Right, v0->window1Bottom);
    }

    PokemonSpriteManager_UpdateCharAndPltt(v0->scene.pokemonSpriteManager);

    {
        int v1;

        for (v1 = 0; v1 < 4; v1++) {
            if (v0->photoSprites[v1].photoSprite != NULL) {
                PhotoSprite_UpdateGraphics(v0->photoSprites[v1].photoSprite);
            }
        }
    }

    VramTransfer_Process();
    SpriteSystem_TransferOam();
    PaletteData_CommitFadedBuffers(v0->scene.paletteData);
    Bg_RunScheduledUpdates(v0->scene.bgConfig);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void contest_competition_0223D164(SysTask *param0, void *param1)
{
    VisualCompetition *v0 = param1;

    if (v0->flag == 1) {
        PokemonSpriteManager_DrawSprites(v0->scene.pokemonSpriteManager);

        {
            int v1;

            for (v1 = 0; v1 < 4; v1++) {
                if (v0->photoSprites[v1].photoSprite != NULL) {
                    PhotoSprite_Update(v0->photoSprites[v1].photoSprite);
                }
            }
        }

        ParticleHelper_DrawParticleSystems();
        SpriteSystem_DrawSprites(v0->scene.spriteManager);
        SpriteSystem_UpdateTransfer();

        G3_SwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
    }

    CommManager_Dummy_02038A1C(22, v0->scene.bgConfig);
}

static void contest_competition_0223D1B8(BgConfig *param0)
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
                .charBase = GX_BG_CHARBASE_0x0c000,
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
                .charBase = GX_BG_CHARBASE_0x14000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 2,
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

        G2_SetBG0Priority(1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
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
                .screenBase = GX_BG_SCRBASE_0x7800,
                .charBase = GX_BG_CHARBASE_0x00000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_0, &v3[0], 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_0);
        Bg_SetOffset(param0, BG_LAYER_SUB_0, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_SUB_0, 3, 0);
    }
}

static void contest_competition_0223D324(VisualCompetition *param0)
{
    Window_Add(param0->scene.bgConfig, &param0->scene.windows[0], 1, 0x2, 0x13, 27, 4, 13, (18 + 12) + 1);
}

static void contest_competition_0223D350(void)
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

static void contest_competition_0223D390(VisualCompetition *param0)
{
    int v0;

    GF_ASSERT(param0->contest != NULL);

    for (v0 = 0; v0 < 4; v0++) {
        param0->scores.contestantIDs[v0] = 4 - 1 - v0;
    }

    contest_competition_02247A48(param0);
}

static void contest_competition_0223D3B8(VisualCompetition *param0, NARC *param1)
{
    SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->scene.paletteData, 2, param0->scene.spriteSystem, param0->scene.spriteManager, param1, 7, 0, 3, NNS_G2D_VRAM_TYPE_2DMAIN, 33001);

    contest_competition_0224774C(param0->scene.spriteSystem, param0->scene.spriteManager, param1);
    contest_competition_0223F560(param0->scene.spriteSystem, param0->scene.spriteManager, param0->scene.paletteData, 33001, -1, 33001, 33001);
    contest_competition_0223F630(&param0->scene.spriteGroup, param0->scene.spriteSystem, param0->scene.spriteManager, 33001, 33001, 33001, 33001, 0, 200, 3, 50000);
}

static void contest_competition_0223D434(VisualCompetition *param0)
{
    contest_competition_02247798(param0->scene.spriteManager);
    contest_competition_0223F6C4(&param0->scene.spriteGroup);
    contest_competition_0223F5E8(param0->scene.spriteManager, 33001, -1, 33001, 33001);

    SpriteManager_UnloadPlttObjById(param0->scene.spriteManager, 33001);
}

static void contest_competition_0223D468(VisualCompetition *param0, NARC *param1)
{
    SpriteSystem_LoadPaletteBuffer(param0->scene.paletteData, 3, param0->scene.spriteSystem, param0->scene.spriteManager, 46, 8, 0, 2, NNS_G2D_VRAM_TYPE_2DSUB, 33002);
}

static void contest_competition_0223D498(VisualCompetition *param0)
{
    SpriteManager_UnloadPlttObjById(param0->scene.spriteManager, 33002);
}

static void contest_competition_0223D4A8(VisualCompetition *param0, NARC *param1)
{
    int v0;

    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 23, param0->scene.bgConfig, 3, 0, 0, TRUE, HEAP_ID_22);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 22, param0->scene.bgConfig, 3, 0, 0, TRUE, HEAP_ID_22);
    Bg_ClearTilemap(param0->scene.bgConfig, 1);
    PaletteData_LoadBufferFromFileStart(param0->scene.paletteData, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, 35, HEAP_ID_22, PLTTBUF_MAIN_BG, 0, PLTT_DEST(0));
    PaletteData_LoadBufferFromFileStart(param0->scene.paletteData, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, 36, HEAP_ID_22, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(13));

    v0 = Options_Frame(param0->contest->options);

    LoadMessageBoxGraphics(param0->scene.bgConfig, 1, 1, 15, v0, HEAP_ID_22);
    PaletteData_LoadBufferFromFileStart(param0->scene.paletteData, NARC_INDEX_GRAPHIC__PL_WINFRAME, GetMessageBoxPaletteNARCMember(v0), HEAP_ID_22, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 24, param0->scene.bgConfig, 2, 0, 0, 1, HEAP_ID_22);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 21, param0->scene.bgConfig, 2, 0, 0, 1, HEAP_ID_22);
    PaletteData_LoadBufferFromFileStart(param0->scene.paletteData, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, 37, HEAP_ID_22, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(12));
}

static void contest_competition_0223D5AC(VisualCompetition *param0)
{
    return;
}

static void contest_competition_0223D5B0(VisualCompetition *param0, NARC *param1)
{
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 19, param0->scene.bgConfig, 4, 0, 0, 1, HEAP_ID_22);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 20, param0->scene.bgConfig, 4, 0, 0, 1, HEAP_ID_22);
    PaletteData_LoadBufferFromFileStart(param0->scene.paletteData, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, 34, HEAP_ID_22, PLTTBUF_SUB_BG, 0, PLTT_DEST(0));
}

static void contest_competition_0223D608(VisualCompetition *param0)
{
    return;
}

static int contest_competition_0223D60C(VisualCompetition *param0, VisualCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (PaletteData_GetSelectedBuffersMask(param0->scene.paletteData) != 0) {
            break;
        }

        contest_competition_0223F334(param0->contest, 22);
        contest_competition_0223F374(param0->contest);
        param1->state++;
        break;
    default:
        return 1;
        break;
    }

    return 0;
}

static int contest_competition_0223D640(VisualCompetition *param0, VisualCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (Contest_IsPracticeCompetition(param0->contest) == TRUE) {
            param0->contestantInfo.state = 2;
        } else {
            param0->contestantInfo.state = 1;
        }

        param0->contestantInfo.messageArg1 = 0;
        param0->contestantInfo.messageArg2 = 0;

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 13, &param0->contestantInfo) == 1) {
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

static int contest_competition_0223D6B8(VisualCompetition *param0, VisualCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        param0->contestantInfo.contestantID = param0->scores.contestantIDs[param0->scores.currentContestant];

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 0, &param0->contestantInfo) == 1) {
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

static int contest_competition_0223D71C(VisualCompetition *param0, VisualCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        param0->contestantInfo.x = 0;
        param0->contestantInfo.y = -16;
        param0->contestantInfo.z = 16;
        param0->contestantInfo.timer = 0x0;

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 14, &param0->contestantInfo) == 1) {
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

static int contest_competition_0223D78C(VisualCompetition *param0, VisualCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 15, NULL) == 1) {
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

static int contest_competition_0223D7DC(VisualCompetition *param0, VisualCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 2, &param0->contestantInfo) == 1) {
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

static int contest_competition_0223D82C(VisualCompetition *param0, VisualCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        switch (param0->scores.currentContestant) {
        case 0:
            param0->contestantInfo.state = 3;
            break;
        case 1:
            param0->contestantInfo.state = 4;
            break;
        case 2:
            param0->contestantInfo.state = 5;
            break;
        default:
            param0->contestantInfo.state = 6;
            break;
        }

        param0->contestantInfo.messageArg1 = 0;
        param0->contestantInfo.messageArg2 = 0;
        param0->contestantInfo.messageArgs.contestantID = param0->contestantInfo.contestantID;
        param1->state++;
    case 1:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 13, &param0->contestantInfo) == 1) {
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

static int contest_competition_0223D8DC(VisualCompetition *param0, VisualCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        param0->contestantInfo.visualRank = Contest_GetVisualScoreRank(param0->contest, param0->contestantInfo.contestantID);
        param0->contestantInfo.danceRank = Contest_GetDanceScoreRank(param0->contest, param0->contestantInfo.contestantID);
        param1->state++;
    case 1:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 6, &param0->contestantInfo) == 1) {
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

static int contest_competition_0223D96C(VisualCompetition *param0, VisualCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        param0->scores.currentContestant++;
        param1->state++;
        break;
    default:
        if (param0->scores.currentContestant >= 4) {
            return 1;
        }

        param1->nextState = 2;
        return 2;
    }

    return 0;
}

static int contest_competition_0223D99C(VisualCompetition *param0, VisualCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
        param0->contestantInfo.score = 1765;

        if (contest_competition_0224F30C(&param0->packetQueue, param0, 16, &param0->contestantInfo) == 1) {
            param1->state++;
        }
        break;
    case 1:
        if (contest_competition_0224F4B8(&param0->packetQueue, param0->contest->data.connectionCount, param0->contest->data.playerContestantID, param0->contest->data.leaderContestantID) == 1) {
            param1->state++;
        }
        break;
    case 2:
        switch (param0->contest->data.competitionType) {
        case CONTEST_COMPETITION_LINK_OR_OFFICIAL:
            param0->contestantInfo.state = 7;
            break;
        default:
            param0->contestantInfo.state = 0;
            break;
        }

        param0->contestantInfo.messageArg1 = 0;
        param0->contestantInfo.messageArg2 = 0;
        param1->state++;
    case 3:
        if (contest_competition_0224F30C(&param0->packetQueue, param0, 13, &param0->contestantInfo) == 1) {
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

static int contest_competition_0223DA78(VisualCompetition *param0, VisualCompetitionTask *param1)
{
    switch (param1->state) {
    case 0:
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
