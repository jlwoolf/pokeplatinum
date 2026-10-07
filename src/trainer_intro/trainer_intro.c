#include "trainer_intro/trainer_intro.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/font_oam.h"
#include "struct_decls/struct_02012744_decl.h"
#include "struct_defs/struct_020127E8.h"

#include "applications/party_menu/main.h"
#include "applications/pokemon_summary_screen/main.h"
#include "battle/battle_main.h"

#include "bag.h"
#include "bg_window.h"
#include "camera.h"
#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "font.h"
#include "font_special_chars.h"
#include "g3d_pipeline.h"
#include "game_options.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "item.h"
#include "journal.h"
#include "map_header.h"
#include "math_util.h"
#include "menu.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "palette.h"
#include "particle_system.h"
#include "party.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "render_window.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task_extensions.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "trainer_data.h"
#include "trainer_info.h"
#include "font_oam.h"
#include "g3_buffer.h"
#include "battle_recording.h"
#include "comm_tool.h"
#include "app_graphics.h"
#include "vram_transfer.h"

typedef struct TrainerIntro TrainerIntro;
typedef u8 (*TrainerIntroStepFunc)(TrainerIntro *);

typedef struct TrainerIntroMon {
    u32 iconSpriteIndex;
    u16 species;
    u16 hp;
    u16 maxHp;
    u16 heldItem;
    u8 level;
    u8 gender;
    u8 hasGender;
    u8 isEgg;
    u8 ballCapsule;
    u8 form;
    u32 statusIconAnim;
} TrainerIntroMon;

typedef struct TrainerIntro {
    TrainerIntroData *trainerIntroData;
    const TrainerIntroStepFunc *stepSequence;
    PaletteData *palette;
    BgConfig *bgConfig;
    Window windows[24];
    SpriteSystem *spriteSystem;
    SpriteManager *spriteManager;
    ManagedSprite *sprites[30];
    u32 spriteCount;
    TrainerIntroMon partyMons[6];
    u16 unk_298[96]; // party menu member panel tilemaps
    u16 unk_358[96]; // party menu member panel tilemaps
    u16 unk_418[96]; // party menu member panel tilemaps
    u16 partyPaletteBuffer[48];
    u16 savedPanelTilemaps[2][384];
    FontOAMManager *fontOamManager;
    FontOAM *fontOams[4];
    G3DPipelineBuffers *g3dPipeline;
    ParticleSystem *particleSystem;
    void *particleHeap;
    u8 spriteBaseX[4];
    u8 spriteBaseY[4];
    u8 nameBaseX[4];
    u8 nameBaseY[4];
    s32 scrollStep;
    s16 shakeOffsetX;
    s16 shakeOffsetY;
    s8 shakeRangeX;
    s8 shakeRangeY;
    u8 introOrder;
    u8 taskState;
    u8 stepIndex;
    u8 stepDelay;
    u8 stepCounter;
    u16 recordingState;
    u16 recordingSaveState;
    Window messageWindow;
    Window confirmWindow;
    GXBG0As bg0Mode;
    MessageLoader *messageLoader;
    StringTemplate *stringTemplate;
    String *string;
    int textPrinter;
    int recordingMenuState;
    Menu *yesNoMenu;
    void *waitDial;
    int recordingSystemVersion;
    int recordingIsValid;
    BOOL hasOtherGame;
};

static void TrainerIntro_RunTask(SysTask *param0, void *param1);
static void TrainerIntro_InitGXBanks(void);
static u8 TrainerIntro_Init(TrainerIntro *param0);
static u8 TrainerIntro_WaitForFade(TrainerIntro *param0);
static u8 TrainerIntro_SlidePanelsIn(TrainerIntro *param0);
static u8 TrainerIntro_ShakePanels(TrainerIntro *param0);
static u8 TrainerIntro_SlidePanelsOut(TrainerIntro *param0);
static u8 TrainerIntro_SetShortDelay(TrainerIntro *param0);
static u8 TrainerIntro_ChooseIntroOrder(TrainerIntro *param0);
static u8 TrainerIntro_AnimateIntroPanels(TrainerIntro *param0);
static u8 TrainerIntro_AnimatePanelsForward(TrainerIntro *param0);
static u8 TrainerIntro_AnimatePanelsBackward(TrainerIntro *param0);
static u8 TrainerIntro_Finish(TrainerIntro *param0);
static u8 TrainerIntro_Cleanup(SysTask *param0, TrainerIntro *param1);
static u8 TrainerIntro_SetShortDelayAlt(TrainerIntro *param0);
static u8 TrainerIntro_AnimateWindowWipe(TrainerIntro *param0);
static u8 TrainerIntro_ShowVsSprites(TrainerIntro *param0);
static u8 TrainerIntro_ShowSingleVsSprite(TrainerIntro *param0);
static u8 TrainerIntro_LoadBattleResultPalette(TrainerIntro *param0);
static u8 TrainerIntro_SetupMultiBattle(TrainerIntro *param0);
static u8 TrainerIntro_SetupRecording(TrainerIntro *param0);
static u8 TrainerIntro_SetupSingleBattle(TrainerIntro *param0);
static u8 TrainerIntro_SlideVsIconsOut(TrainerIntro *param0);
static BOOL TrainerIntro_IsPlayerOnLeft(void);
static void TrainerIntro_InitSpriteSystem(TrainerIntro *param0, SpriteResourceCapacities *param1, int param2);
static ManagedSprite *TrainerIntro_CreateSprite(TrainerIntro *param0, const u32 *param1);
static void TrainerIntro_FreeSprites(TrainerIntro *param0);
static void TrainerIntro_UpdateSpriteAnims(TrainerIntro *param0);
static void TrainerIntro_VBlankCallback(void *param0);
static void TrainerIntro_InitBattleBackgrounds(TrainerIntro *param0, GXBG0As param1, int param2);
static void TrainerIntro_FreeBattleBackgrounds(TrainerIntro *param0);
static void TrainerIntro_LoadVsDemoGraphics(TrainerIntro *param0);
static void TrainerIntro_SetPanelBlend(void);
static void TrainerIntro_InitSingleBattleSprites(TrainerIntro *param0);
static void TrainerIntro_SetSpritePositions(TrainerIntro *param0, int param1, int param2);
static void TrainerIntro_LoadVsSpriteResources(TrainerIntro *param0);
static void TrainerIntro_SetVsSpriteX(TrainerIntro *param0, u8 param1, s16 param2, s16 param3);
static void TrainerIntro_InitPartyStatusIcons(TrainerIntro *param0);
static void TrainerIntro_InitTrainerNames(TrainerIntro *param0);
static void TrainerIntro_SetTrainerNameX(TrainerIntro *param0, u32 param1, s16 param2, s16 param3);
static void TrainerIntro_FreeTrainerNames(TrainerIntro *param0);
static void TrainerIntro_InitParticles(TrainerIntro *param0);
static int TrainerIntro_UpdateParticles(TrainerIntro *param0);
static void TrainerIntro_FreeParticles(TrainerIntro *param0);
static void TrainerIntro_InitMultiBattleSprites(TrainerIntro *param0);
static void TrainerIntro_LoadMultiBattleSprites(TrainerIntro *param0);
static void TrainerIntro_PositionResultSprites(TrainerIntro *param0);
static void TrainerIntro_InitSingleBattleBackgrounds(TrainerIntro *param0);
static void TrainerIntro_FreeSingleBattleBackgrounds(TrainerIntro *param0);
static void TrainerIntro_LoadPartyMenuGraphics(TrainerIntro *param0);
static void TrainerIntro_InitPartyPanelSprites(TrainerIntro *param0);
static void TrainerIntro_LoadParties(TrainerIntro *param0);
static void TrainerIntro_DrawPartyPanelTilemaps(TrainerIntro *param0);
static void TrainerIntro_SavePanelTilemaps(TrainerIntro *param0);
static void TrainerIntro_RestorePanelTilemaps(TrainerIntro *param0, u8 param1);
static void TrainerIntro_AddPartyWindows(TrainerIntro *param0);
static void TrainerIntro_RemovePartyWindows(TrainerIntro *param0);
static void TrainerIntro_DrawPartyPanels(TrainerIntro *param0);
static void TrainerIntro_LoadMonIconResources(TrainerIntro *param0);
static void TrainerIntro_LoadBallResources(TrainerIntro *param0);
static void TrainerIntro_LoadStatusConditionResources(TrainerIntro *param0);
static void TrainerIntro_LoadItemResources(TrainerIntro *param0);
static void TrainerIntro_SlideMonIcons(TrainerIntro *param0, s16 param1);
static u32 TrainerIntro_AllocTextureVram(u32 param0, BOOL param1);
static u32 TrainerIntro_AllocPaletteVram(u32 param0, BOOL param1);
static void TrainerIntro_SaveJournalEntry(TrainerIntroData *trainerIntroData);
static u8 TrainerIntro_SaveRecording(TrainerIntro *param0);
static u8 TrainerIntro_WaitCommSync(TrainerIntro *param0);
static void TrainerIntro_LoadMessageBoxGraphics(TrainerIntro *param0);
static void TrainerIntro_FreeMessageWindows(TrainerIntro *param0);
static void TrainerIntro_FreeMessageResources(TrainerIntro *param0);
static void TrainerIntro_ShowMessageBox(TrainerIntro *param0);
static void TrainerIntro_HandleRecordingMenu(TrainerIntro *param0);
static BOOL TrainerIntro_CanSaveRecording(TrainerIntro *param0);
static void TrainerIntro_ShowWaitDial(TrainerIntro *param0);
static void TrainerIntro_HideWaitDial(TrainerIntro *param0);

static const u32 sVsSpriteTemplates[][7] = {
    { 0xB807, 0xB807, 0xB807, 0xB807, 0x2, 0x0, 0x0 },
    { 0xB807, 0xB807, 0xB807, 0xB807, 0x2, 0x0, 0x0 },
    { 0xB807, 0xB807, 0xB807, 0xB807, 0x2, 0x0, 0x0 },
    { 0xB807, 0xB807, 0xB807, 0xB807, 0x2, 0x0, 0x0 },
    { 0xB807, 0xB807, 0xB807, 0xB807, 0x2, 0x0, 0x0 },
    { 0xB807, 0xB807, 0xB807, 0xB807, 0x2, 0x0, 0x0 },
    { 0xB807, 0xB807, 0xB807, 0xB807, 0x2, 0x0, 0x0 },
    { 0xB807, 0xB807, 0xB807, 0xB807, 0x2, 0x0, 0x0 },
    { 0xB807, 0xB807, 0xB807, 0xB807, 0x2, 0x0, 0x0 },
    { 0xB807, 0xB807, 0xB807, 0xB807, 0x2, 0x0, 0x0 },
    { 0xB807, 0xB807, 0xB807, 0xB807, 0x2, 0x0, 0x0 },
    { 0xB807, 0xB807, 0xB807, 0xB807, 0x2, 0x0, 0x0 },
    { 0xB808, 0xB807, 0xB808, 0xB808, 0x1, 0x0, 0x1 },
    { 0xB808, 0xB807, 0xB808, 0xB808, 0x1, 0x0, 0x1 }
};

static const TrainerIntroStepFunc sSingleBattleSequence[] = {
    TrainerIntro_SetupSingleBattle,
    TrainerIntro_WaitForFade,
    TrainerIntro_SlideVsIconsOut,
    TrainerIntro_WaitForFade,
    TrainerIntro_Finish
};

static const TrainerIntroStepFunc sMultiBattleSequence[] = {
    TrainerIntro_SetupMultiBattle,
    TrainerIntro_WaitForFade,
    TrainerIntro_SlidePanelsIn,
    TrainerIntro_ShakePanels,
    TrainerIntro_SlidePanelsOut
};

static const TrainerIntroStepFunc sRecordingSequence[] = {
    TrainerIntro_SetupRecording,
    TrainerIntro_WaitForFade,
    TrainerIntro_SlidePanelsIn,
    TrainerIntro_ShakePanels,
    TrainerIntro_SetShortDelay,
    TrainerIntro_WaitForFade,
    TrainerIntro_ChooseIntroOrder,
    TrainerIntro_AnimateIntroPanels,
    TrainerIntro_SetShortDelayAlt,
    TrainerIntro_AnimateWindowWipe,
    TrainerIntro_WaitForFade,
    TrainerIntro_ShowVsSprites,
    TrainerIntro_WaitForFade,
    TrainerIntro_LoadBattleResultPalette,
    TrainerIntro_WaitForFade,
    TrainerIntro_SaveRecording,
    TrainerIntro_WaitForFade,
    TrainerIntro_WaitCommSync,
    TrainerIntro_Finish
};

static const TrainerIntroStepFunc sRecordingDrawSequence[] = {
    TrainerIntro_SetupRecording,
    TrainerIntro_WaitForFade,
    TrainerIntro_SlidePanelsIn,
    TrainerIntro_ShakePanels,
    TrainerIntro_SetShortDelayAlt,
    TrainerIntro_AnimateWindowWipe,
    TrainerIntro_WaitForFade,
    TrainerIntro_ShowSingleVsSprite,
    TrainerIntro_WaitForFade,
    TrainerIntro_SaveRecording,
    TrainerIntro_WaitForFade,
    TrainerIntro_WaitCommSync,
    TrainerIntro_Finish
};

static const u8 sPanelScrollOffsets[][2] = {
    { 0x6, 0x6 },
    { 0x0, 0x6 },
    { 0x0, 0x6 },
    { 0x4, 0xA },
    { 0x0, 0xA },
    { 0x0, 0xA }
};

static const WindowTemplate sPartyWindowTemplates[] = {
    { 0x1, 0x6, 0x1, 0x9, 0x2, 0x0, 0x1 },
    { 0x1, 0x1, 0x4, 0x5, 0x2, 0x0, 0x13 },
    { 0x1, 0x7, 0x4, 0x8, 0x2, 0x0, 0x1D },
    { 0x1, 0x8, 0x3, 0x6, 0x1, 0x3, 0x2D },
    { 0x1, 0x6, 0x7, 0x9, 0x2, 0x0, 0x33 },
    { 0x1, 0x1, 0xA, 0x5, 0x2, 0x0, 0x45 },
    { 0x1, 0x7, 0xA, 0x8, 0x2, 0x0, 0x4F },
    { 0x1, 0x8, 0x9, 0x6, 0x1, 0x4, 0x5F },
    { 0x1, 0x6, 0xD, 0x9, 0x2, 0x0, 0x65 },
    { 0x1, 0x1, 0x10, 0x5, 0x2, 0x0, 0x77 },
    { 0x1, 0x7, 0x10, 0x8, 0x2, 0x0, 0x81 },
    { 0x1, 0x8, 0xF, 0x6, 0x1, 0x5, 0x91 },
    { 0x1, 0x16, 0x2, 0x9, 0x2, 0x0, 0x97 },
    { 0x1, 0x11, 0x5, 0x5, 0x2, 0x0, 0xA9 },
    { 0x1, 0x17, 0x5, 0x8, 0x2, 0x0, 0xB3 },
    { 0x1, 0x18, 0x4, 0x6, 0x1, 0x6, 0xC3 },
    { 0x1, 0x16, 0x8, 0x9, 0x2, 0x0, 0xC9 },
    { 0x1, 0x11, 0xB, 0x5, 0x2, 0x0, 0xDB },
    { 0x1, 0x17, 0xB, 0x8, 0x2, 0x0, 0xE5 },
    { 0x1, 0x18, 0xA, 0x6, 0x1, 0x7, 0xF5 },
    { 0x1, 0x16, 0xE, 0x9, 0x2, 0x0, 0xFB },
    { 0x1, 0x11, 0x11, 0x5, 0x2, 0x0, 0x10D },
    { 0x1, 0x17, 0x11, 0x8, 0x2, 0x0, 0x117 },
    { 0x1, 0x18, 0x10, 0x6, 0x1, 0x8, 0x127 }
};

static const u8 sPartyPanelTilemapCoords[][2] = {
    { 0x0, 0x0 },
    { 0x0, 0x6 },
    { 0x0, 0xC },
    { 0x10, 0x1 },
    { 0x10, 0x7 },
    { 0x10, 0xD }
};

static const u8 sMonIconPositions[][10] = {
    { 0x1E, 0x10, 0x26, 0x18, 0x2E, 0x18, 0x24, 0x2C, 0x10, 0xE },
    { 0x1E, 0x40, 0x26, 0x48, 0x2E, 0x48, 0x24, 0x5C, 0x10, 0x3E },
    { 0x1E, 0x70, 0x26, 0x78, 0x2E, 0x78, 0x24, 0x8C, 0x10, 0x6E },
    { 0x9E, 0x18, 0xA6, 0x20, 0xAE, 0x20, 0xA4, 0x34, 0x90, 0x16 },
    { 0x9E, 0x48, 0xA6, 0x50, 0xAE, 0x50, 0xA4, 0x64, 0x90, 0x46 },
    { 0x9E, 0x78, 0xA6, 0x80, 0xAE, 0x80, 0xA4, 0x94, 0x90, 0x76 }
};

static const u32 sMonIconTemplates[][7] = {
    { 0xB809, 0xB808, 0xB809, 0xB809, 0x1, 0x1, 0x0 },
    { 0xB80F, 0xB809, 0xB80A, 0xB80A, 0x1, 0x0, 0x0 },
    { 0xB80F, 0xB809, 0xB80A, 0xB80A, 0x1, 0x0, 0x0 },
    { 0xB810, 0xB80A, 0xB80B, 0xB80B, 0x1, 0x0, 0x0 },
    { 0xB811, 0xB80B, 0xB80C, 0xB80C, 0x1, 0x2, 0x0 },
    { 0xB80A, 0xB808, 0xB809, 0xB809, 0x1, 0x1, 0x0 },
    { 0xB80F, 0xB809, 0xB80A, 0xB80A, 0x1, 0x0, 0x0 },
    { 0xB80F, 0xB809, 0xB80A, 0xB80A, 0x1, 0x0, 0x0 },
    { 0xB810, 0xB80A, 0xB80B, 0xB80B, 0x1, 0x0, 0x0 },
    { 0xB811, 0xB80B, 0xB80C, 0xB80C, 0x1, 0x2, 0x0 },
    { 0xB80B, 0xB808, 0xB809, 0xB809, 0x1, 0x1, 0x0 },
    { 0xB80F, 0xB809, 0xB80A, 0xB80A, 0x1, 0x0, 0x0 },
    { 0xB80F, 0xB809, 0xB80A, 0xB80A, 0x1, 0x0, 0x0 },
    { 0xB810, 0xB80A, 0xB80B, 0xB80B, 0x1, 0x0, 0x0 },
    { 0xB811, 0xB80B, 0xB80C, 0xB80C, 0x1, 0x2, 0x0 },
    { 0xB80C, 0xB808, 0xB809, 0xB809, 0x1, 0x1, 0x0 },
    { 0xB80F, 0xB809, 0xB80A, 0xB80A, 0x1, 0x0, 0x0 },
    { 0xB80F, 0xB809, 0xB80A, 0xB80A, 0x1, 0x0, 0x0 },
    { 0xB810, 0xB80A, 0xB80B, 0xB80B, 0x1, 0x0, 0x0 },
    { 0xB811, 0xB80B, 0xB80C, 0xB80C, 0x1, 0x2, 0x0 },
    { 0xB80D, 0xB808, 0xB809, 0xB809, 0x1, 0x1, 0x0 },
    { 0xB80F, 0xB809, 0xB80A, 0xB80A, 0x1, 0x0, 0x0 },
    { 0xB80F, 0xB809, 0xB80A, 0xB80A, 0x1, 0x0, 0x0 },
    { 0xB810, 0xB80A, 0xB80B, 0xB80B, 0x1, 0x0, 0x0 },
    { 0xB811, 0xB80B, 0xB80C, 0xB80C, 0x1, 0x2, 0x0 },
    { 0xB80E, 0xB808, 0xB809, 0xB809, 0x1, 0x1, 0x0 },
    { 0xB80F, 0xB809, 0xB80A, 0xB80A, 0x1, 0x0, 0x0 },
    { 0xB80F, 0xB809, 0xB80A, 0xB80A, 0x1, 0x0, 0x0 },
    { 0xB810, 0xB80A, 0xB80B, 0xB80B, 0x1, 0x0, 0x0 },
    { 0xB811, 0xB80B, 0xB80C, 0xB80C, 0x1, 0x2, 0x0 }
};

static const WindowTemplate sYesNoWindowTemplate = {
    0x0,
    0x19,
    0xD,
    0x6,
    0x4,
    0xD,
    0x94
};

void TrainerIntro_Start(TrainerIntroData *trainerIntroData)
{
    TrainerIntro *v0 = SysTask_GetParam(SysTask_StartAndAllocateParam(TrainerIntro_RunTask, sizeof(TrainerIntro), 100, trainerIntroData->heapID));
    memset(v0, 0, sizeof(TrainerIntro));

    v0->trainerIntroData = trainerIntroData;
    v0->taskState = 0;
    v0->recordingSystemVersion = BattleRecording_CheckSystemVersions();

    if (v0->recordingSystemVersion == 1) {
        if ((v0->trainerIntroData->dto != NULL) && (v0->trainerIntroData->dto->saveData != NULL)) {
            v0->recordingSystemVersion = Bag_CanRemoveItem(SaveData_GetBag(v0->trainerIntroData->dto->saveData), ITEM_VS_RECORDER, 1, trainerIntroData->heapID);
        }
    }
}

static void TrainerIntro_RunTask(SysTask *param0, void *param1)
{
    TrainerIntro *v0 = param1;

    switch (v0->taskState) {
    case 0:
        v0->taskState = TrainerIntro_Init(v0);
        break;
    case 1:
        while (TRUE) {
            u8 v1 = v0->stepSequence[v0->stepIndex](v0);

            if (v1 != 0) {
                v0->stepIndex++;
            }

            if (v1 != 2) {
                break;
            }
        }

        if (v0->trainerIntroData->mode == 2) {
            TrainerIntro_HandleRecordingMenu(v0);
        }
        break;
    case 2:
        if (TrainerIntro_Cleanup(param0, v0) == 1) {
            return;
        }
    }

    if (v0->stepIndex != 0) {
        TrainerIntro_UpdateSpriteAnims(v0);
        SpriteSystem_DrawSprites(v0->spriteManager);
    }

    if (v0->trainerIntroData->mode != 0) {
        G3_SwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
    }
}

static void TrainerIntro_InitGXBanks(void)
{
    GXBanks v0 = {
        GX_VRAM_BG_128_A,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_32_H,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_64_E,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_01_BC,
        GX_VRAM_TEXPLTT_01_FG
    };

    GXLayers_SetBanks(&v0);
    MI_CpuClear32((void *)HW_BG_VRAM, HW_BG_VRAM_SIZE);
}

static void TrainerIntro_HandleRecordingMenu(TrainerIntro *param0)
{
    if (TrainerIntro_CanSaveRecording(param0) == 0) {
        return;
    }

    switch (param0->recordingMenuState) {
    case 0:
        break;
    case 1:
        TrainerIntro_ShowMessageBox(param0);
        MessageLoader_GetString(param0->messageLoader, 0, param0->string);
        param0->textPrinter = Text_AddPrinterWithParams(&param0->messageWindow, FONT_MESSAGE, param0->string, 0, 0, TEXT_SPEED_INSTANT, NULL);
        Bg_ScheduleTilemapTransfer(param0->bgConfig, 0);
        param0->recordingMenuState = 2;
        break;
    case 2:
        if (param0->recordingSystemVersion == 1) {
            if (gSystem.pressedKeys & PAD_BUTTON_A) {
                param0->recordingMenuState = 3;
            }
        }
        break;
    case 3:
        if (param0->recordingIsValid == 1) {
            MessageLoader_GetString(param0->messageLoader, 2, param0->string);
        } else {
            MessageLoader_GetString(param0->messageLoader, 1, param0->string);
        }

        Window_FillRectWithColor(&param0->confirmWindow, 15, 0, 0, 27 * 8, 4 * 8);
        Window_DrawMessageBoxWithScrollCursor(&param0->confirmWindow, 0, 1, 15);

        param0->textPrinter = Text_AddPrinterWithParams(&param0->confirmWindow, FONT_MESSAGE, param0->string, 0, 0, TEXT_SPEED_INSTANT, NULL);
        param0->yesNoMenu = Menu_MakeYesNoChoiceWithCursorAt(param0->bgConfig, &sYesNoWindowTemplate, 1 + (18 + 12), 14, 1, param0->trainerIntroData->heapID);

        Bg_ScheduleTilemapTransfer(param0->bgConfig, 0);
        param0->recordingMenuState = 4;
        break;
    case 4: {
        u32 v0 = Menu_ProcessInputAndHandleExit(param0->yesNoMenu, param0->trainerIntroData->heapID);

        switch (v0) {
        case 0:
            param0->recordingMenuState = 5;
            param0->yesNoMenu = NULL;
            break;
        case 0xfffffffe:
            param0->recordingMenuState = 1;
            param0->yesNoMenu = NULL;
            break;
        }
    } break;
    case 5:
        TrainerIntro_ShowMessageBox(param0);
        MessageLoader_GetString(param0->messageLoader, 5, param0->string);
        param0->textPrinter = Text_AddPrinterWithParams(&param0->messageWindow, FONT_MESSAGE, param0->string, 0, 0, TEXT_SPEED_INSTANT, NULL);
        Bg_ScheduleTilemapTransfer(param0->bgConfig, 0);
        param0->recordingMenuState = 6;
        break;
    case 6:
        break;
    case 7:
        if (param0->yesNoMenu != NULL) {
            Menu_DestroyForExit(param0->yesNoMenu, param0->trainerIntroData->heapID);
            param0->yesNoMenu = NULL;
        }

        Window_EraseMessageBox(&param0->messageWindow, 0);
        Bg_ScheduleTilemapTransfer(param0->bgConfig, 0);
        param0->recordingMenuState = 8;
        break;
    case 8:
        break;
    }
}

static u8 TrainerIntro_Init(TrainerIntro *param0)
{
    G2_BlendNone();

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();

    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);
    G2_BlendNone();
    G2S_BlendNone();

    TrainerIntro_InitGXBanks();

    param0->bgConfig = BgConfig_New(param0->trainerIntroData->heapID);
    param0->palette = PaletteData_New(param0->trainerIntroData->heapID);

    PaletteData_AllocBuffer(param0->palette, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * 16, param0->trainerIntroData->heapID);
    Bg_MaskPalette(BG_LAYER_SUB_0, 0x0);

    param0->stepCounter = 0;
    param0->stepDelay = 8;
    param0->stepIndex = 0;

    switch (param0->trainerIntroData->mode) {
    case 0:
        param0->stepSequence = sSingleBattleSequence;
        break;
    case 1:
        param0->stepSequence = sMultiBattleSequence;
        break;
    case 2:
        if (param0->trainerIntroData->battleResult == 3) {
            param0->stepSequence = sRecordingDrawSequence;
        } else {
            param0->stepSequence = sRecordingSequence;
        }

        TrainerIntro_SaveJournalEntry(param0->trainerIntroData);
        break;
    }

    return 1;
}

static u8 TrainerIntro_SetupSingleBattle(TrainerIntro *param0)
{
    switch (param0->stepCounter) {
    case 0:
        TrainerIntro_InitSingleBattleBackgrounds(param0);
        TrainerIntro_LoadPartyMenuGraphics(param0);
        break;
    case 1:
        TrainerIntro_LoadParties(param0);
        TrainerIntro_InitPartyPanelSprites(param0);
        break;
    case 2:
        param0->stepCounter = 0;
        param0->stepDelay = 32;
        TrainerIntro_DrawPartyPanelTilemaps(param0);
        TrainerIntro_AddPartyWindows(param0);
        TrainerIntro_DrawPartyPanels(param0);
        TrainerIntro_SavePanelTilemaps(param0);
        NetworkIcon_Init();
        App_StartScreenFade(FALSE, param0->trainerIntroData->heapID);
        SetVBlankCallback(TrainerIntro_VBlankCallback, param0);
        return 1;
    }

    param0->stepCounter++;
    return 0;
}

static u8 TrainerIntro_SetupMultiBattle(TrainerIntro *param0)
{
    switch (param0->stepCounter) {
    case 0:
        TrainerIntro_InitBattleBackgrounds(param0, GX_BG0_AS_3D, 0);
        TrainerIntro_LoadVsDemoGraphics(param0);
        TrainerIntro_SetPanelBlend();
        break;
    case 1:
        TrainerIntro_SetSpritePositions(param0, 0, 0);
        TrainerIntro_InitSingleBattleSprites(param0);
        NetworkIcon_Init();
        TrainerIntro_InitParticles(param0);
        break;
    case 2:
        App_StartScreenFade(FALSE, param0->trainerIntroData->heapID);
        SetVBlankCallback(TrainerIntro_VBlankCallback, param0);
        param0->stepCounter = 0;
        param0->shakeRangeX = 8;
        param0->shakeRangeY = 4;
        param0->scrollStep = 16;
        return 1;
    }

    param0->stepCounter++;
    return 0;
}

static u8 TrainerIntro_SetupRecording(TrainerIntro *param0)
{
    switch (param0->stepCounter) {
    case 0:
        TrainerIntro_InitBattleBackgrounds(param0, GX_BG0_AS_2D, 1);
        TrainerIntro_LoadVsDemoGraphics(param0);
        TrainerIntro_LoadMessageBoxGraphics(param0);
        TrainerIntro_SetPanelBlend();
        {
            BOOL v0;
            int v1;

            v0 = BattleRecording_Validate(param0->trainerIntroData->dto->saveData, param0->trainerIntroData->heapID, &v1, 0);
            param0->recordingIsValid = v1;
        }
        {
            int v2;
            TrainerInfo *v3;

            param0->hasOtherGame = 0;

            for (v2 = 0; v2 < (7 + 1); v2++) {
                v3 = CommInfo_TrainerInfo(v2);

                if (v3 != NULL) {
                    if (TrainerInfo_GameCode(v3) == 0) {
                        param0->hasOtherGame = 1;
                        break;
                    }
                }
            }
        }
        break;
    case 1:
        TrainerIntro_SetSpritePositions(param0, -32, -16);
        TrainerIntro_InitMultiBattleSprites(param0);
        NetworkIcon_Init();
        break;
    case 2:
        App_StartScreenFade(FALSE, param0->trainerIntroData->heapID);
        SetVBlankCallback(TrainerIntro_VBlankCallback, param0);
        param0->stepCounter = 0;
        param0->shakeRangeX = 4;
        param0->shakeRangeY = 2;
        param0->scrollStep = 12;
        param0->messageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_BATTLE_VIDEO, param0->trainerIntroData->heapID);
        param0->stringTemplate = StringTemplate_Default(param0->trainerIntroData->heapID);
        param0->string = String_Init(2 * 160, param0->trainerIntroData->heapID);
        param0->recordingMenuState = 1;

        return 1;
    }

    param0->stepCounter++;
    return 0;
}

static u8 TrainerIntro_WaitForFade(TrainerIntro *param0)
{
    if (IsScreenFadeDone() == FALSE) {
        return 0;
    }

    if (param0->stepDelay == param0->stepCounter) {
        param0->stepCounter = 0;
        return 1;
    }

    param0->stepCounter++;
    return 0;
}

static u8 TrainerIntro_SlidePanelsIn(TrainerIntro *param0)
{
    if (Bg_GetXOffset(param0->bgConfig, 3) <= 24) {
        param0->stepCounter = 0;
        param0->shakeOffsetX = 0;
        param0->shakeOffsetY = 0;

        Bg_ScheduleScroll(param0->bgConfig, 3, 0, 24);
        Bg_ScheduleScroll(param0->bgConfig, 2, 0, -24);

        TrainerIntro_SetVsSpriteX(param0, 0, 0, 0);
        TrainerIntro_SetVsSpriteX(param0, 1, 0, 0);
        TrainerIntro_SetVsSpriteX(param0, 2, 0, 0);
        TrainerIntro_SetVsSpriteX(param0, 3, 0, 0);
        TrainerIntro_SetTrainerNameX(param0, 0, 0, 0);
        TrainerIntro_SetTrainerNameX(param0, 1, 0, 0);
        TrainerIntro_SetTrainerNameX(param0, 2, 0, 0);
        TrainerIntro_SetTrainerNameX(param0, 3, 0, 0);

        return 1;
    }

    Bg_ScheduleScroll(param0->bgConfig, 3, 2, param0->scrollStep);
    Bg_ScheduleScroll(param0->bgConfig, 2, 1, param0->scrollStep);

    param0->stepCounter++;

    TrainerIntro_SetVsSpriteX(param0, 0, param0->scrollStep * param0->stepCounter - 256, 0);
    TrainerIntro_SetVsSpriteX(param0, 1, param0->scrollStep * param0->stepCounter - 256, 0);
    TrainerIntro_SetVsSpriteX(param0, 2, 256 - param0->scrollStep * param0->stepCounter, 0);
    TrainerIntro_SetVsSpriteX(param0, 3, 256 - param0->scrollStep * param0->stepCounter, 0);
    TrainerIntro_SetTrainerNameX(param0, 0, param0->scrollStep * param0->stepCounter - 256, 0);
    TrainerIntro_SetTrainerNameX(param0, 1, param0->scrollStep * param0->stepCounter - 256, 0);
    TrainerIntro_SetTrainerNameX(param0, 2, 256 - param0->scrollStep * param0->stepCounter, 0);
    TrainerIntro_SetTrainerNameX(param0, 3, 256 - param0->scrollStep * param0->stepCounter, 0);

    return 0;
}

static u8 TrainerIntro_ShakePanels(TrainerIntro *param0)
{
    s16 v0, v1;

    if ((TrainerIntro_UpdateParticles(param0) == 0) && (param0->stepCounter > 24)) {
        param0->stepCounter = 0;
        return 1;
    }

    if (param0->stepCounter == 0) {
        if (param0->trainerIntroData->mode == 1) {
            Sound_PlayEffect(SEQ_SE_DP_VSDEMO01_sseq);
        } else {
            Sound_PlayEffect(SEQ_SE_DP_GASHIN_sseq);
        }
    }

    if (param0->stepCounter == 24) {
        Bg_ScheduleScroll(param0->bgConfig, 3, 0, 24);
        Bg_ScheduleScroll(param0->bgConfig, 2, 0, -24);
        Bg_ScheduleScroll(param0->bgConfig, 3, 3, 0);
        Bg_ScheduleScroll(param0->bgConfig, 2, 3, 0);

        TrainerIntro_SetVsSpriteX(param0, 0, 0, 0);
        TrainerIntro_SetVsSpriteX(param0, 1, 0, 0);
        TrainerIntro_SetVsSpriteX(param0, 2, 0, 0);
        TrainerIntro_SetVsSpriteX(param0, 3, 0, 0);

        TrainerIntro_SetTrainerNameX(param0, 0, 0, 0);
        TrainerIntro_SetTrainerNameX(param0, 1, 0, 0);
        TrainerIntro_SetTrainerNameX(param0, 2, 0, 0);
        TrainerIntro_SetTrainerNameX(param0, 3, 0, 0);
    } else if (param0->stepCounter < 24) {
        v0 = (LCRNG_Next() % param0->shakeRangeX) - (param0->shakeRangeX / 2);
        v1 = (LCRNG_Next() % param0->shakeRangeY) - (param0->shakeRangeY / 2);

        if (((v0 < 0) && (param0->shakeOffsetX < 0)) || ((v0 > 0) && (param0->shakeOffsetX > 0))) {
            v0 *= -1;
        }

        if (((v1 < 0) && (param0->shakeOffsetY < 0)) || ((v1 > 0) && (param0->shakeOffsetY > 0))) {
            v1 *= -1;
        }

        Bg_ScheduleScroll(param0->bgConfig, 3, 0, 24 + v0);
        Bg_ScheduleScroll(param0->bgConfig, 2, 0, -24 + v0);
        Bg_ScheduleScroll(param0->bgConfig, 3, 3, v1);
        Bg_ScheduleScroll(param0->bgConfig, 2, 3, v1);

        TrainerIntro_SetVsSpriteX(param0, 0, v0, v1);
        TrainerIntro_SetVsSpriteX(param0, 1, v0, v1);
        TrainerIntro_SetVsSpriteX(param0, 2, v0, v1);
        TrainerIntro_SetVsSpriteX(param0, 3, v0, v1);

        TrainerIntro_SetTrainerNameX(param0, 0, v0, v1);
        TrainerIntro_SetTrainerNameX(param0, 1, v0, v1);
        TrainerIntro_SetTrainerNameX(param0, 2, v0, v1);
        TrainerIntro_SetTrainerNameX(param0, 3, v0, v1);

        param0->shakeOffsetX = v0;
        param0->shakeOffsetY = v1;
    }

    param0->stepCounter++;

    return 0;
}

static u8 TrainerIntro_SlidePanelsOut(TrainerIntro *param0)
{
    if (param0->stepCounter == 8) {
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_WHITE, 6, 1, param0->trainerIntroData->heapID);
    }

    if ((param0->stepCounter >= 8) && (IsScreenFadeDone() == TRUE)) {
        param0->taskState = 2;
        return 1;
    }

    if (param0->stepCounter == 0) {
        Sound_PlayEffect(SEQ_SE_DP_VSDEMO05_sseq);
    }

    Bg_ScheduleScroll(param0->bgConfig, 3, 1, 16);
    Bg_ScheduleScroll(param0->bgConfig, 2, 2, 16);

    param0->stepCounter++;

    TrainerIntro_SetVsSpriteX(param0, 0, -16 * param0->stepCounter, 0);
    TrainerIntro_SetVsSpriteX(param0, 1, -16 * param0->stepCounter, 0);
    TrainerIntro_SetVsSpriteX(param0, 2, 16 * param0->stepCounter, 0);
    TrainerIntro_SetVsSpriteX(param0, 3, 16 * param0->stepCounter, 0);

    TrainerIntro_SetTrainerNameX(param0, 0, -16 * param0->stepCounter, 0);
    TrainerIntro_SetTrainerNameX(param0, 1, -16 * param0->stepCounter, 0);
    TrainerIntro_SetTrainerNameX(param0, 2, 16 * param0->stepCounter, 0);
    TrainerIntro_SetTrainerNameX(param0, 3, 16 * param0->stepCounter, 0);

    return 0;
}

static u8 TrainerIntro_SetShortDelay(TrainerIntro *param0)
{
    param0->stepDelay = 16;
    return 2;
}

static u8 TrainerIntro_ChooseIntroOrder(TrainerIntro *param0)
{
    if (TrainerIntro_IsPlayerOnLeft() == 1) {
        if (param0->trainerIntroData->battleResult == 1) {
            param0->introOrder = 0;
        } else {
            param0->introOrder = 1;
        }
    } else {
        if (param0->trainerIntroData->battleResult == 1) {
            param0->introOrder = 1;
        } else {
            param0->introOrder = 0;
        }
    }

    return 2;
}

static u8 TrainerIntro_AnimateIntroPanels(TrainerIntro *param0)
{
    if (param0->introOrder == 0) {
        return TrainerIntro_AnimatePanelsForward(param0);
    }

    return TrainerIntro_AnimatePanelsBackward(param0);
}

static u8 TrainerIntro_AnimatePanelsForward(TrainerIntro *param0)
{
    Bg_ScheduleScroll(param0->bgConfig, 2, 2, sPanelScrollOffsets[param0->stepCounter][0]);
    Bg_ScheduleScroll(param0->bgConfig, 3, 2, sPanelScrollOffsets[param0->stepCounter][0]);
    TrainerIntro_SetVsSpriteX(param0, 0, sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetVsSpriteX(param0, 1, sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetVsSpriteX(param0, 2, sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetVsSpriteX(param0, 3, sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetTrainerNameX(param0, 0, sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetTrainerNameX(param0, 1, sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetTrainerNameX(param0, 2, sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetTrainerNameX(param0, 3, sPanelScrollOffsets[param0->stepCounter][1], 0);

    if (param0->stepCounter == 0) {
        Sound_PlayEffect(SEQ_SE_DP_DODON_sseq);
    }

    if (param0->stepCounter == 5) {
        param0->stepCounter = 0;
        return 1;
    } else {
        param0->stepCounter++;
    }

    return 0;
}

static u8 TrainerIntro_AnimatePanelsBackward(TrainerIntro *param0)
{
    Bg_ScheduleScroll(param0->bgConfig, 2, 1, sPanelScrollOffsets[param0->stepCounter][0]);
    Bg_ScheduleScroll(param0->bgConfig, 3, 1, sPanelScrollOffsets[param0->stepCounter][0]);

    TrainerIntro_SetVsSpriteX(param0, 0, -sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetVsSpriteX(param0, 1, -sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetVsSpriteX(param0, 2, -sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetVsSpriteX(param0, 3, -sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetTrainerNameX(param0, 0, -sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetTrainerNameX(param0, 1, -sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetTrainerNameX(param0, 2, -sPanelScrollOffsets[param0->stepCounter][1], 0);
    TrainerIntro_SetTrainerNameX(param0, 3, -sPanelScrollOffsets[param0->stepCounter][1], 0);

    if (param0->stepCounter == 0) {
        Sound_PlayEffect(SEQ_SE_DP_DODON_sseq);
    }

    if (param0->stepCounter == 5) {
        param0->stepCounter = 0;
        return 1;
    } else {
        param0->stepCounter++;
    }

    return 0;
}

static u8 TrainerIntro_SetShortDelayAlt(TrainerIntro *param0)
{
    param0->stepDelay = 16;
    return 2;
}

static u8 TrainerIntro_AnimateWindowWipe(TrainerIntro *param0)
{
    if (param0->stepCounter == 0) {
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);

        GX_SetVisibleWnd(GX_WNDMASK_W0);
        G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
        G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 0);
    }

    if (param0->stepCounter == 16) {
        param0->stepCounter = 0;
        param0->stepDelay = 32;
        GX_SetVisibleWnd(GX_WNDMASK_NONE);
        return 1;
    } else {
        G2_SetWnd0Position(0, 95 - param0->stepCounter - 24, 255, 96 + param0->stepCounter - 24);
        param0->stepCounter++;
    }

    return 0;
}

static u8 TrainerIntro_ShowVsSprites(TrainerIntro *param0)
{
    Sound_PlayEffect(SEQ_SE_DP_VSDEMO06_sseq);
    ManagedSprite_SetDrawFlag(param0->sprites[12], 1);
    ManagedSprite_SetDrawFlag(param0->sprites[13], 1);
    ManagedSprite_SetAnim(param0->sprites[12], 0);
    param0->stepDelay = 32;
    return 1;
}

static u8 TrainerIntro_ShowSingleVsSprite(TrainerIntro *param0)
{
    Sound_PlayEffect(SEQ_SE_DP_VSDEMO06_sseq);
    ManagedSprite_SetDrawFlag(param0->sprites[12], 1);
    param0->stepDelay = 64;
    return 1;
}

static u8 TrainerIntro_SaveRecording(TrainerIntro *param0)
{
    if (TrainerIntro_CanSaveRecording(param0) == 0) {
        param0->stepDelay = 1;
        return 1;
    }

    if ((param0->hasOtherGame == 0) && (param0->yesNoMenu != NULL)) {
        return 0;
    }

    if (param0->recordingMenuState == 5) {
        return 0;
    }

    if ((param0->recordingMenuState != 6) && (param0->recordingMenuState != 5) && (param0->recordingMenuState != 7) && (param0->recordingMenuState != 8)) {
        param0->recordingMenuState = 7;
        param0->stepCounter = 0xff;
    }

    switch (param0->stepCounter) {
    case 0:
        TrainerIntro_ShowMessageBox(param0);
        MessageLoader_GetString(param0->messageLoader, 8, param0->string);
        param0->textPrinter = Text_AddPrinterWithParams(&param0->messageWindow, FONT_MESSAGE, param0->string, 0, 0, TEXT_SPEED_INSTANT, NULL);
        TrainerIntro_ShowWaitDial(param0);
        param0->stepCounter++;
        break;
    case 1: {
        int v0;

        v0 = BattleRecording_SaveWithSummary(param0->trainerIntroData->dto->saveData, param0->trainerIntroData->recordingType, 0, 0, &param0->recordingState, &param0->recordingSaveState);

        if (v0 == 2) {
            MessageLoader_GetString(param0->messageLoader, 6, param0->string);
            Sound_PlayEffect(SEQ_SE_DP_SAVE_sseq);
        } else if (v0 == 3) {
            MessageLoader_GetString(param0->messageLoader, 7, param0->string);
        } else {
            break;
        }

        TrainerIntro_HideWaitDial(param0);
        Window_FillRectWithColor(&param0->messageWindow, 15, 0, 0, 27 * 8, 4 * 8);

        param0->textPrinter = Text_AddPrinterWithParams(&param0->messageWindow, FONT_MESSAGE, param0->string, 0, 0, TEXT_SPEED_INSTANT, NULL);
    }

        param0->stepDelay = 0;
        param0->stepCounter++;
        break;
    case 2:
        param0->stepDelay++;

        if (param0->stepDelay > 30) {
            param0->stepDelay = 0;
            param0->stepCounter++;
        }
        break;
    default:
        Window_EraseMessageBox(&param0->messageWindow, 0);
        Bg_ScheduleTilemapTransfer(param0->bgConfig, 0);
        param0->stepCounter = 0;
        param0->stepDelay = 64 / 3;
        return 1;
    }

    Bg_ScheduleTilemapTransfer(param0->bgConfig, 0);
    return 0;
}

static u8 TrainerIntro_WaitCommSync(TrainerIntro *param0)
{
    switch (param0->stepCounter) {
    case 0:
        TrainerIntro_ShowMessageBox(param0);
        MessageLoader_GetString(param0->messageLoader, 9, param0->string);
        param0->textPrinter = Text_AddPrinterWithParams(&param0->messageWindow, FONT_MESSAGE, param0->string, 0, 0, TEXT_SPEED_INSTANT, NULL);
        CommTiming_StartSync(62);

        if (param0->recordingSystemVersion == 0) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
        }

        param0->stepCounter++;
        break;
    case 1:
        if (CommTiming_IsSyncState(62)) {
            param0->stepCounter = 0;
            return 1;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    Bg_ScheduleTilemapTransfer(param0->bgConfig, 0);
    return 0;
}

static u8 TrainerIntro_LoadBattleResultPalette(TrainerIntro *param0)
{
    if (TrainerIntro_IsPlayerOnLeft() == 1) {
        if (param0->trainerIntroData->battleResult == 1) {
            PaletteData_CopyBuffer(param0->palette, 0, 4 * 16, 0, 3 * 16, 0x20);
        } else {
            PaletteData_CopyBuffer(param0->palette, 0, 4 * 16, 0, 0 * 16, 0x20);
        }
    } else {
        if (param0->trainerIntroData->battleResult == 1) {
            PaletteData_CopyBuffer(param0->palette, 0, 4 * 16, 0, 0 * 16, 0x20);
        } else {
            PaletteData_CopyBuffer(param0->palette, 0, 4 * 16, 0, 3 * 16, 0x20);
        }
    }

    PaletteData_SelectAll(param0->palette, 1);
    Sound_PlayEffect(SEQ_SE_DP_VSDEMO07_sseq);
    param0->stepDelay = 64;
    return 1;
}

static u8 TrainerIntro_SlideVsIconsOut(TrainerIntro *param0)
{
    if (param0->stepCounter == 0) {
        Sound_PlayEffect(SEQ_SE_DP_VSDEMO05_sseq);
    }

    if (param0->stepCounter == 16) {
        param0->stepCounter = 0;
        param0->stepDelay = 64;
        return 1;
    }

    param0->stepCounter++;

    TrainerIntro_SlideMonIcons(param0, 16 - param0->stepCounter);
    TrainerIntro_RestorePanelTilemaps(param0, param0->stepCounter);

    return 0;
}

static u8 TrainerIntro_Finish(TrainerIntro *param0)
{
    App_StartScreenFade(TRUE, param0->trainerIntroData->heapID);
    param0->taskState = 2;
    return 1;
}

static u8 TrainerIntro_Cleanup(SysTask *param0, TrainerIntro *param1)
{
    if (IsScreenFadeDone() == FALSE) {
        return 0;
    }

    SetVBlankCallback(NULL, NULL);
    TrainerIntro_HideWaitDial(param1);

    if (param1->trainerIntroData->mode != 0) {
        TrainerIntro_FreeMessageWindows(param1);
        TrainerIntro_FreeMessageResources(param1);
        TrainerIntro_FreeBattleBackgrounds(param1);
        TrainerIntro_FreeParticles(param1);
        TrainerIntro_FreeTrainerNames(param1);
    } else {
        TrainerIntro_FreeSingleBattleBackgrounds(param1);
        TrainerIntro_RemovePartyWindows(param1);
    }

    TrainerIntro_FreeSprites(param1);

    VramTransfer_Free();
    PaletteData_FreeBuffer(param1->palette, PLTTBUF_MAIN_BG);
    PaletteData_Free(param1->palette);

    param1->trainerIntroData->isDone = 1;
    SysTask_FinishAndFreeParam(param0);

    return 1;
}

static BOOL TrainerIntro_IsPlayerOnLeft(void)
{
    switch (CommSys_GetBattlePosition(CommSys_CurNetId())) {
    case 0:
    case 2:
        return 1;
    case 1:
    case 3:
        return 0;
    }

    return 0;
}

static void TrainerIntro_InitSpriteSystem(TrainerIntro *param0, SpriteResourceCapacities *param1, int param2)
{
    VramTransfer_New(64, param0->trainerIntroData->heapID);

    param0->spriteSystem = SpriteSystem_Alloc(param0->trainerIntroData->heapID);
    param0->spriteManager = SpriteManager_New(param0->spriteSystem);
    {
        RenderOamTemplate v0 = {
            0,
            128,
            0,
            32,
            0,
            128,
            0,
            32,
        };
        CharTransferTemplateWithModes v1 = {
            0, 1024 * 64, 1024 * 16, GX_OBJVRAMMODE_CHAR_1D_32K, GX_OBJVRAMMODE_CHAR_1D_32K
        };

        v1.maxTasks = param2;
        SpriteSystem_Init(param0->spriteSystem, &v0, &v1, 16);
    }

    SpriteSystem_InitSprites(param0->spriteSystem, param0->spriteManager, param2);
    SpriteSystem_InitManagerWithCapacities(param0->spriteSystem, param0->spriteManager, param1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static ManagedSprite *TrainerIntro_CreateSprite(TrainerIntro *param0, const u32 *param1)
{
    SpriteTemplate v0;

    v0.x = 0;
    v0.y = 0;
    v0.z = 0;
    v0.animIdx = 0;
    v0.priority = param1[5];
    v0.plttIdx = param1[6];
    v0.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v0.resources[0] = param1[0];
    v0.resources[1] = param1[1];
    v0.resources[2] = param1[2];
    v0.resources[3] = param1[3];
    v0.bgPriority = param1[4];
    v0.vramTransfer = FALSE;

    return SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v0);
}

static void TrainerIntro_FreeSprites(TrainerIntro *param0)
{
    u32 v0;

    for (v0 = 0; v0 < param0->spriteCount; v0++) {
        Sprite_DeleteAndFreeResources(param0->sprites[v0]);
    }

    SpriteSystem_FreeResourcesAndManager(param0->spriteSystem, param0->spriteManager);
    SpriteSystem_Free(param0->spriteSystem);
}

static void TrainerIntro_UpdateSpriteAnims(TrainerIntro *param0)
{
    u16 v0;

    for (v0 = 0; v0 < param0->spriteCount; v0++) {
        Sprite_UpdateAnim(param0->sprites[v0]->sprite, FX32_ONE);
    }
}

static void TrainerIntro_VBlankCallback(void *param0)
{
    TrainerIntro *v0 = param0;

    Bg_RunScheduledUpdates(v0->bgConfig);
    PaletteData_CommitFadedBuffers(v0->palette);
    VramTransfer_Process();
    SpriteSystem_TransferOam();

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void TrainerIntro_InitBattleBackgrounds(TrainerIntro *param0, GXBG0As param1, int param2)
{
    param0->bg0Mode = param1;

    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_3D,
        };

        v0.bg0As2DOr3D = param1;
        SetAllGraphicsModes(&v0);
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x1000,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_512x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_23,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_MAIN_3, &v1, 0);
        Bg_ClearTilemap(param0->bgConfig, BG_LAYER_MAIN_3);
        Bg_ScheduleScroll(param0->bgConfig, 3, 0, 256);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x1000,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_512x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe000,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_23,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_MAIN_2, &v2, 0);
        Bg_ClearTilemap(param0->bgConfig, BG_LAYER_MAIN_2);
        Bg_ScheduleScroll(param0->bgConfig, 2, 0, -256);
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xd800,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_MAIN_1, &v3, 0);
        Bg_ClearTilemap(param0->bgConfig, BG_LAYER_MAIN_1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);

        if (param2 == 1) {
            Bg_SetOffset(param0->bgConfig, BG_LAYER_MAIN_1, 3, 24);
        }
    }

    if (param1 == GX_BG0_AS_2D) {
        BgTemplate v4 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x0000,
            .charBase = GX_BG_CHARBASE_0x18000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_MAIN_0, &v4, 0);
        Bg_ClearTilemap(param0->bgConfig, BG_LAYER_MAIN_0);

        if (param0->recordingSystemVersion == 1) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
        } else {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
        }
    }
}

static void TrainerIntro_FreeMessageWindows(TrainerIntro *param0)
{
    if (param0->messageWindow.pixels != NULL) {
        Window_Remove(&param0->messageWindow);
    }

    if (param0->confirmWindow.pixels != NULL) {
        Window_Remove(&param0->confirmWindow);
    }
}

static void TrainerIntro_FreeMessageResources(TrainerIntro *param0)
{
    if (param0->string != NULL) {
        String_Free(param0->string);
    }

    if (param0->stringTemplate != NULL) {
        StringTemplate_Free(param0->stringTemplate);
    }

    if (param0->messageLoader != NULL) {
        MessageLoader_Free(param0->messageLoader);
    }
}

static void TrainerIntro_FreeBattleBackgrounds(TrainerIntro *param0)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, 0);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_1);

    if (param0->bg0Mode == GX_BG0_AS_2D) {
        Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_0);
    }

    Heap_Free(param0->bgConfig);
}

static void TrainerIntro_LoadVsDemoGraphics(TrainerIntro *param0)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_BATTLE__GRAPHIC__VS_DEMO_GRA, param0->trainerIntroData->heapID);

    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 0, param0->bgConfig, 1, 0, 0, 0, param0->trainerIntroData->heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 4, param0->bgConfig, 1, 0, 0, 0, param0->trainerIntroData->heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 2, param0->bgConfig, 2, 0, 0, 0, param0->trainerIntroData->heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 3, param0->bgConfig, 3, 0, 0, 0, param0->trainerIntroData->heapID);
    Graphics_LoadPaletteFromOpenNARC(v0, 1, 0, 0, 0, param0->trainerIntroData->heapID);
    PaletteData_LoadBufferFromHardware(param0->palette, PLTTBUF_MAIN_BG, 0, PALETTE_SIZE_BYTES * 5);
    Bg_MaskPalette(BG_LAYER_MAIN_1, 0x18c6);
    NARC_dtor(v0);
}

static void TrainerIntro_LoadMessageBoxGraphics(TrainerIntro *param0)
{
    int v0;

    GF_ASSERT(param0->bg0Mode == GX_BG0_AS_2D && param0->trainerIntroData != NULL && param0->trainerIntroData->dto != NULL && param0->trainerIntroData->dto->options != NULL);
    v0 = Options_Frame(param0->trainerIntroData->dto->options);

    LoadMessageBoxGraphics(param0->bgConfig, BG_LAYER_MAIN_0, 1, 15, v0, param0->trainerIntroData->heapID);
    PaletteData_LoadBufferFromHardware(param0->palette, PLTTBUF_MAIN_BG, PLTT_DEST(15), PALETTE_SIZE_BYTES * 1);
    LoadStandardWindowGraphics(param0->bgConfig, BG_LAYER_MAIN_0, 1 + (18 + 12), 14, 0, param0->trainerIntroData->heapID);
    PaletteData_LoadBufferFromHardware(param0->palette, PLTTBUF_MAIN_BG, PLTT_DEST(14), PALETTE_SIZE_BYTES * 1);
    Font_LoadTextPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(13), param0->trainerIntroData->heapID);
    PaletteData_LoadBufferFromHardware(param0->palette, PLTTBUF_MAIN_BG, PLTT_DEST(13), PALETTE_SIZE_BYTES * 1);
    Window_Add(param0->bgConfig, &param0->messageWindow, 0, 0x2, 0x13, 27, 4, 13, (1 + (18 + 12)) + 9);
    Window_Add(param0->bgConfig, &param0->confirmWindow, 0, 0x2, 0x13, 27, 4, 13, (1 + (18 + 12)) + 9);
}

static void TrainerIntro_SetPanelBlend(void)
{
    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ, 8, 8);
}

static void TrainerIntro_InitSingleBattleSprites(TrainerIntro *param0)
{
    SpriteResourceCapacities v0 = {
        2, 1, 2, 2, 0, 0
    };
    u32 v1;

    TrainerIntro_InitSpriteSystem(param0, &v0, 12 + 8 + 1);
    TrainerIntro_LoadVsSpriteResources(param0);

    for (v1 = 0; v1 < 12; v1++) {
        param0->sprites[v1] = TrainerIntro_CreateSprite(param0, &sVsSpriteTemplates[v1][0]);
    }

    TrainerIntro_SetVsSpriteX(param0, 0, -256, 0);
    TrainerIntro_SetVsSpriteX(param0, 1, -256, 0);
    TrainerIntro_SetVsSpriteX(param0, 2, 256, 0);
    TrainerIntro_SetVsSpriteX(param0, 3, 256, 0);
    TrainerIntro_InitPartyStatusIcons(param0);

    param0->spriteCount = 12;

    TrainerIntro_InitTrainerNames(param0);
    TrainerIntro_SetTrainerNameX(param0, 0, -256, 0);
    TrainerIntro_SetTrainerNameX(param0, 1, -256, 0);
    TrainerIntro_SetTrainerNameX(param0, 2, 256, 0);
    TrainerIntro_SetTrainerNameX(param0, 3, 256, 0);
}

static void TrainerIntro_LoadVsSpriteResources(TrainerIntro *param0)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_BATTLE__GRAPHIC__PL_BATT_OBJ, param0->trainerIntroData->heapID);

    SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 208, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, 47111);
    SpriteSystem_LoadPlttResObj(param0->spriteSystem, param0->spriteManager, NARC_INDEX_BATTLE__GRAPHIC__VS_DEMO_GRA, 8, FALSE, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 47111);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 207, TRUE, 47111);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 209, TRUE, 47111);
    NARC_dtor(v0);
}

static void TrainerIntro_SetVsSpriteX(TrainerIntro *param0, u8 param1, s16 param2, s16 param3)
{
    u32 v0;
    u8 v1[] = { 0, 3, 6, 9 };

    for (v0 = 0; v0 < 3; v0++) {
        ManagedSprite_SetPositionXY(param0->sprites[v1[param1] + v0], param0->spriteBaseX[param1] + v0 * 19 + param2, param0->spriteBaseY[param1] + param3);
    }
}

static void TrainerIntro_SetPartyStatusIcons(TrainerIntro *param0, Party *param1, u16 param2, u16 param3)
{
    Pokemon *v0;
    u8 v1;
    u8 v2, v3, v4;

    v3 = (u8)Party_GetCurrentCount(param1);
    v4 = 0;

    for (v1 = 0; v1 < param2; v1++) {
        ManagedSprite_SetAnim(param0->sprites[v1 + param3], 0);

        if (v3 > v1) {
            v0 = Party_GetPokemonBySlotIndex(param1, v1);

            if ((Pokemon_GetValue(v0, MON_DATA_SPECIES, NULL) == 0) || (Pokemon_GetValue(v0, MON_DATA_IS_EGG, NULL) != 0)) {
                continue;
            }

            v2 = PokemonSummaryScreen_StatusIconAnimIdx(v0);

            if (v2 == 6) {
                ManagedSprite_SetAnim(param0->sprites[v4 + param3], 3);
            } else if (v2 != 7) {
                ManagedSprite_SetAnim(param0->sprites[v4 + param3], 2);
            } else {
                ManagedSprite_SetAnim(param0->sprites[v4 + param3], 1);
            }

            v4++;
        }
    }
}

static void TrainerIntro_InitPartyStatusIcons(TrainerIntro *param0)
{
    if (param0->trainerIntroData->playerSide == 0) {
        TrainerIntro_SetPartyStatusIcons(param0, param0->trainerIntroData->party[0], 6, 0);
        TrainerIntro_SetPartyStatusIcons(param0, param0->trainerIntroData->party[1], 6, 6);
    } else {
        TrainerIntro_SetPartyStatusIcons(param0, param0->trainerIntroData->party[0], 3, 0);
        TrainerIntro_SetPartyStatusIcons(param0, param0->trainerIntroData->party[2], 3, 3);
        TrainerIntro_SetPartyStatusIcons(param0, param0->trainerIntroData->party[1], 3, 6);
        TrainerIntro_SetPartyStatusIcons(param0, param0->trainerIntroData->party[3], 3, 9);
    }
}

static void TrainerIntro_CreateTrainerNameOAM(TrainerIntro *param0, u32 param1, String *param2)
{
    Window *v0;
    UnkStruct_020127E8 v1;

    v0 = &param0->windows[0];

    Window_AddToTopLeftCorner(param0->bgConfig, v0, 8, 2, 0, 0);
    Text_AddPrinterWithParamsAndColor(v0, FONT_SYSTEM, param2, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(3, 4, 0), NULL);

    v1.unk_00 = param0->fontOamManager;
    v1.unk_04 = v0;
    v1.unk_08 = SpriteManager_GetSpriteList(param0->spriteManager);
    v1.unk_0C = SpriteManager_FindPlttResourceProxy(param0->spriteManager, 47111);
    v1.unk_10 = NULL;
    v1.unk_14 = ((1024 - (8 * 2) - (4 * 4)) - (8 * 2) * param1) * 0x20;
    v1.unk_18 = 0;
    v1.unk_1C = 0;
    v1.unk_20 = 2;
    v1.unk_24 = 0;
    v1.unk_28 = NNS_G2D_VRAM_TYPE_2DMAIN;
    v1.heapID = param0->trainerIntroData->heapID;

    param0->fontOams[param1] = FontOAM_New(&v1);

    FontOAM_SetExplicitPalette(param0->fontOams[param1], 0);
    Window_Remove(v0);
}

static void TrainerIntro_InitTrainerNames(TrainerIntro *param0)
{
    param0->fontOamManager = FontOAMManager_New(8, param0->trainerIntroData->heapID);

    TrainerIntro_CreateTrainerNameOAM(param0, 0, param0->trainerIntroData->trainerNames[0]);
    TrainerIntro_CreateTrainerNameOAM(param0, 2, param0->trainerIntroData->trainerNames[1]);

    if (param0->trainerIntroData->playerSide == 1) {
        TrainerIntro_CreateTrainerNameOAM(param0, 1, param0->trainerIntroData->trainerNames[2]);
        TrainerIntro_CreateTrainerNameOAM(param0, 3, param0->trainerIntroData->trainerNames[3]);
    } else {
        TrainerIntro_CreateTrainerNameOAM(param0, 1, param0->trainerIntroData->trainerNames[0]);
        TrainerIntro_CreateTrainerNameOAM(param0, 3, param0->trainerIntroData->trainerNames[1]);

        FontOAM_SetDrawFlag(param0->fontOams[1], 0);
        FontOAM_SetDrawFlag(param0->fontOams[3], 0);
    }
}

static void TrainerIntro_SetTrainerNameX(TrainerIntro *param0, u32 param1, s16 param2, s16 param3)
{
    FontOAM_SetXY(param0->fontOams[param1], param0->nameBaseX[param1] + param2, param0->nameBaseY[param1] + param3);
}

static void TrainerIntro_FreeTrainerNames(TrainerIntro *param0)
{
    u32 v0;

    if (param0->trainerIntroData->mode == 0) {
        return;
    }

    for (v0 = 0; v0 < 4; v0++) {
        FontOAM_Free(param0->fontOams[v0]);
    }

    FontOAMManager_Free(param0->fontOamManager);
}

static void TrainerIntro_SetSpritePositions(TrainerIntro *param0, int param1, int param2)
{
    if (param0->trainerIntroData->playerSide == 1) {
        param0->spriteBaseX[0] = (24 - 4);
        param0->spriteBaseY[0] = (140 + 6) + param1;
        param0->spriteBaseX[1] = ((24 - 4) + 19 * 3 + 4);
        param0->spriteBaseY[1] = ((140 + 6) + 16) + param1;
        param0->spriteBaseX[2] = (136 - 4 - 4);
        param0->spriteBaseY[2] = 44 + param2;
        param0->spriteBaseX[3] = ((136 - 4 - 4) + 19 * 3 + 4);
        param0->spriteBaseY[3] = (44 + 16) + param2;
        param0->nameBaseX[0] = (15 - 4);
        param0->nameBaseY[0] = (114 + 6) + param1;
        param0->nameBaseX[1] = 76;
        param0->nameBaseY[1] = (130 + 6) + param1;
        param0->nameBaseX[2] = (123 - 4);
        param0->nameBaseY[2] = 18 + param2;
        param0->nameBaseX[3] = 184;
        param0->nameBaseY[3] = 34 + param2;
    } else {
        param0->spriteBaseX[0] = 24;
        param0->spriteBaseY[0] = 160 + param1;
        param0->spriteBaseX[1] = (24 + 19 * 3);
        param0->spriteBaseY[1] = 160 + param1;
        param0->spriteBaseX[2] = 136;
        param0->spriteBaseY[2] = 48 + param2;
        param0->spriteBaseX[3] = (136 + 19 * 3);
        param0->spriteBaseY[3] = 48 + param2;
        param0->nameBaseX[0] = 15;
        param0->nameBaseY[0] = 134 + param1;
        param0->nameBaseX[2] = 128;
        param0->nameBaseY[2] = 22 + param2;
    }
}

static void TrainerIntro_InitMultiBattleSprites(TrainerIntro *param0)
{
    SpriteResourceCapacities v0 = {
        2, 1, 2, 2, 0, 0
    };
    u32 v1;

    TrainerIntro_InitSpriteSystem(param0, &v0, 14 + 8 + 1);
    TrainerIntro_LoadVsSpriteResources(param0);
    TrainerIntro_LoadMultiBattleSprites(param0);

    for (v1 = 0; v1 < 14; v1++) {
        param0->sprites[v1] = TrainerIntro_CreateSprite(param0, &sVsSpriteTemplates[v1][0]);
    }

    TrainerIntro_SetVsSpriteX(param0, 0, -256, 0);
    TrainerIntro_SetVsSpriteX(param0, 1, -256, 0);
    TrainerIntro_SetVsSpriteX(param0, 2, 256, 0);
    TrainerIntro_SetVsSpriteX(param0, 3, 256, 0);
    TrainerIntro_InitPartyStatusIcons(param0);
    TrainerIntro_PositionResultSprites(param0);
    TrainerIntro_InitTrainerNames(param0);
    TrainerIntro_SetTrainerNameX(param0, 0, -256, 0);
    TrainerIntro_SetTrainerNameX(param0, 1, -256, 0);
    TrainerIntro_SetTrainerNameX(param0, 2, 256, 0);
    TrainerIntro_SetTrainerNameX(param0, 3, 256, 0);

    param0->spriteCount = 14;
}

static void TrainerIntro_LoadMultiBattleSprites(TrainerIntro *param0)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_BATTLE__GRAPHIC__VS_DEMO_GRA, param0->trainerIntroData->heapID);

    SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 5, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 47112);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 6, FALSE, 47112);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 7, FALSE, 47112);
    NARC_dtor(v0);
}

static void TrainerIntro_PositionResultSprites(TrainerIntro *param0)
{
    ManagedSprite_SetDrawFlag(param0->sprites[12], 0);
    ManagedSprite_SetDrawFlag(param0->sprites[13], 0);

    if (param0->trainerIntroData->battleResult == 3) {
        ManagedSprite_SetPositionXY(param0->sprites[12], 128, 96 - 24);
        ManagedSprite_SetAnim(param0->sprites[12], 3 - 1);
        return;
    }

    if (TrainerIntro_IsPlayerOnLeft() == 1) {
        if (param0->trainerIntroData->battleResult == 1) {
            ManagedSprite_SetPositionXY(param0->sprites[12], 48, 96 - 24);
            ManagedSprite_SetPositionXY(param0->sprites[13], 208, 96 - 24);
        } else {
            ManagedSprite_SetPositionXY(param0->sprites[12], 208, 96 - 24);
            ManagedSprite_SetPositionXY(param0->sprites[13], 48, 96 - 24);
        }
    } else {
        if (param0->trainerIntroData->battleResult == 1) {
            ManagedSprite_SetPositionXY(param0->sprites[12], 208, 96 - 24);
            ManagedSprite_SetPositionXY(param0->sprites[13], 48, 96 - 24);
        } else {
            ManagedSprite_SetPositionXY(param0->sprites[12], 48, 96 - 24);
            ManagedSprite_SetPositionXY(param0->sprites[13], 208, 96 - 24);
        }
    }

    ManagedSprite_SetAnim(param0->sprites[12], 1 - 1);
    ManagedSprite_SetAnim(param0->sprites[13], 2 - 1);
}

static void TrainerIntro_InitParticles(TrainerIntro *param0)
{
    Camera *camera;
    void *v1;

    param0->g3dPipeline = G3DPipeline_Init(param0->trainerIntroData->heapID, TEXTURE_VRAM_SIZE_512K, PALETTE_VRAM_SIZE_32K, NULL);

    G3X_AlphaBlend(1);
    ParticleSystem_ZeroAll();

    param0->particleHeap = Heap_Alloc(param0->trainerIntroData->heapID, 0x4800);
    param0->particleSystem = ParticleSystem_New(TrainerIntro_AllocTextureVram, TrainerIntro_AllocPaletteVram, param0->particleHeap, 0x4800, 1, param0->trainerIntroData->heapID);

    camera = ParticleSystem_GetCamera(param0->particleSystem);
    Camera_SetClipping(FX32_ONE, FX32_ONE * 900, camera);

    v1 = ParticleSystem_LoadResourceFromNARC(NARC_INDEX_PARTICLEDATA__PARTICLEDATA, 2, param0->trainerIntroData->heapID);
    ParticleSystem_SetResource(param0->particleSystem, v1, (1 << 1) | (1 << 3), 1);

    ParticleSystem_CreateEmitterWithCallback(param0->particleSystem, 0, NULL, NULL);
    ParticleSystem_CreateEmitterWithCallback(param0->particleSystem, 1, NULL, NULL);
    ParticleSystem_CreateEmitterWithCallback(param0->particleSystem, 2, NULL, NULL);
    ParticleSystem_CreateEmitterWithCallback(param0->particleSystem, 3, NULL, NULL);
    ParticleSystem_CreateEmitterWithCallback(param0->particleSystem, 4, NULL, NULL);
}

static int TrainerIntro_UpdateParticles(TrainerIntro *param0)
{
    const MtxFx43 *v0;
    int v1;

    if (param0->trainerIntroData->mode != 1) {
        return 0;
    }

    G3_ResetG3X();

    if (ParticleSystem_GetActiveEmitterCount(param0->particleSystem) == 0) {
        return 0;
    }

    ParticleSystem_DrawAll();
    ParticleSystem_UpdateAll();

    return 1;
}

static void TrainerIntro_FreeParticles(TrainerIntro *param0)
{
    if (param0->trainerIntroData->mode != 1) {
        return;
    }

    ParticleSystem_Free(param0->particleSystem);
    Heap_Free(param0->particleHeap);
    G3DPipelineBuffers_Free(param0->g3dPipeline);
}

static u32 TrainerIntro_AllocTextureVram(u32 param0, BOOL param1)
{
    u32 v0;
    NNSGfdTexKey v1;

    v1 = NNS_GfdAllocTexVram(param0, param1, 0);
    ParticleSystem_RegisterTextureKey(v1);

    GF_ASSERT(v1 != NNS_GFD_ALLOC_ERROR_TEXKEY);
    v0 = NNS_GfdGetTexKeyAddr(v1);

    return v0;
}

static u32 TrainerIntro_AllocPaletteVram(u32 param0, BOOL param1)
{
    NNSGfdPlttKey v0;
    u32 v1;

    v0 = NNS_GfdAllocPlttVram(param0, param1, NNS_GFD_ALLOC_FROM_LOW);
    ParticleSystem_RegisterPaletteKey(v0);

    if (v0 == NNS_GFD_ALLOC_ERROR_PLTTKEY) {
        GF_ASSERT(FALSE);
    }

    v1 = NNS_GfdGetPlttKeyAddr(v0);

    return v1;
}

static void TrainerIntro_InitSingleBattleBackgrounds(TrainerIntro *param0)
{
    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D
        };

        SetAllGraphicsModes(&v0);
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_MAIN_1, &v1, 0);
        Bg_ClearTilemap(param0->bgConfig, BG_LAYER_MAIN_1);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_MAIN_2, &v2, 0);
        Bg_ClearTilemap(param0->bgConfig, BG_LAYER_MAIN_2);
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe800,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_MAIN_3, &v3, 0);
    }
}

static void TrainerIntro_FreeSingleBattleBackgrounds(TrainerIntro *param0)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, 0);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_1);
    Heap_Free(param0->bgConfig);
}

static void TrainerIntro_LoadPartyMenuGraphics(TrainerIntro *param0)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_GRAPHIC__PL_PLIST_GRA, param0->trainerIntroData->heapID);

    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 15, param0->bgConfig, 3, 0, 0, 0, param0->trainerIntroData->heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 17, param0->bgConfig, 3, 0, 0, 0, param0->trainerIntroData->heapID);

    {
        NNSG2dPaletteData *v1;
        void *v2;
        u16 *v3;

        v2 = NARC_AllocAndReadWholeMember(v0, 16, param0->trainerIntroData->heapID);
        NNS_G2dGetUnpackedPaletteData(v2, &v1);
        Bg_LoadPalette(BG_LAYER_MAIN_3, (void *)v1->pRawData, v1->szByte, 0);

        v3 = (u16 *)v1->pRawData;
        memcpy(param0->partyPaletteBuffer, &v3[3 * 16], 32 * 3);
        Heap_Free(v2);
    }

    PartyMenu_LoadMemberPanelTilemaps(param0->trainerIntroData->heapID, param0->unk_298, param0->unk_358, param0->unk_418);
    NARC_dtor(v0);
}

static void TrainerIntro_DrawPartyPanelTilemaps(TrainerIntro *param0)
{
    u16 *v0;
    u32 v1;

    for (v1 = 0; v1 < 6; v1++) {
        if ((v1 == 0) || (v1 == 3)) {
            v0 = param0->unk_298;
        } else if (param0->partyMons[v1].species == 0) {
            v0 = param0->unk_418;
        } else {
            v0 = param0->unk_358;
        }

        Bg_CopyToTilemapRect(param0->bgConfig, 2, sPartyPanelTilemapCoords[v1][0], sPartyPanelTilemapCoords[v1][1], 16, 6, (const void *)v0, 0, 0, 16, 6);

        if (param0->partyMons[v1].species != 0) {
            Bg_ChangeTilemapRectPalette(
                param0->bgConfig, 2, sPartyPanelTilemapCoords[v1][0], sPartyPanelTilemapCoords[v1][1], 16, 6, 3 + v1);

            if (((v1 < 3) && (param0->trainerIntroData->playerSide == 1)) || ((v1 >= 3) && (param0->trainerIntroData->playerSide == 0))) {
                Bg_LoadPalette(BG_LAYER_MAIN_2, (void *)&param0->partyPaletteBuffer[16 * 1], PALETTE_SIZE_BYTES, PLTT_OFFSET(3 + v1));
            } else {
                Bg_LoadPalette(BG_LAYER_MAIN_2, (void *)&param0->partyPaletteBuffer[0], PALETTE_SIZE_BYTES, PLTT_OFFSET(3 + v1));
            }
        }
    }

    Bg_ScheduleTilemapTransfer(param0->bgConfig, 2);
}

static void TrainerIntro_CopyPanelTilemap(TrainerIntro *param0, u16 *param1, u8 param2)
{
    u16 *v0;
    u16 v1, v2;

    v0 = Bg_GetTilemapBuffer(param0->bgConfig, param2);

    if (param0->trainerIntroData->playerSide == 0) {
        v1 = 16;
    } else {
        v1 = 0;
    }

    for (v2 = 0; v2 < 24; v2++) {
        memcpy(&param1[v2 * 16], &v0[v2 * 32 + v1], 16 * 2);
        memset(&v0[v2 * 32 + v1], 0, 16 * 2);
    }
}

static void TrainerIntro_SavePanelTilemaps(TrainerIntro *param0)
{
    TrainerIntro_CopyPanelTilemap(param0, &param0->savedPanelTilemaps[0][0], 1);
    TrainerIntro_CopyPanelTilemap(param0, &param0->savedPanelTilemaps[1][0], 2);

    Bg_ScheduleTilemapTransfer(param0->bgConfig, 1);
    Bg_ScheduleTilemapTransfer(param0->bgConfig, 2);
}

static void TrainerIntro_RestorePanelTilemaps(TrainerIntro *param0, u8 param1)
{
    if (param0->trainerIntroData->playerSide == 0) {
        Bg_CopyToTilemapRect(param0->bgConfig, 1, 16 + 16 - param1, 0, param1, 24, (const void *)&param0->savedPanelTilemaps[0][0], 0, 0, 16, 24);
        Bg_CopyToTilemapRect(param0->bgConfig, 2, 16 + 16 - param1, 0, param1, 24, (const void *)&param0->savedPanelTilemaps[1][0], 0, 0, 16, 24);
    } else {
        Bg_CopyToTilemapRect(param0->bgConfig, 1, 0, 0, param1, 24, (const void *)&param0->savedPanelTilemaps[0][0], 16 - param1, 0, 16, 24);
        Bg_CopyToTilemapRect(param0->bgConfig, 2, 0, 0, param1, 24, (const void *)&param0->savedPanelTilemaps[1][0], 16 - param1, 0, 16, 24);
    }

    Bg_ScheduleTilemapTransfer(param0->bgConfig, 1);
    Bg_ScheduleTilemapTransfer(param0->bgConfig, 2);
}

static void TrainerIntro_LoadPartyMonData(TrainerIntro *param0, Party *param1, u8 param2)
{
    Pokemon *v0;
    u16 v1;
    u16 v2 = (u16)Party_GetCurrentCount(param1);

    for (v1 = 0; v1 < 3; v1++) {
        if (v2 <= v1) {
            param0->partyMons[v1 + param2].iconSpriteIndex = PokeIconSpriteIndex(0, 0, 0);
            continue;
        }

        v0 = Party_GetPokemonBySlotIndex(param1, v1);

        param0->partyMons[v1 + param2].iconSpriteIndex = Pokemon_IconSpriteIndex(v0);
        param0->partyMons[v1 + param2].species = (u16)Pokemon_GetValue(v0, MON_DATA_SPECIES, NULL);

        if (param0->partyMons[v1 + param2].species == 0) {
            continue;
        }

        param0->partyMons[v1 + param2].isEgg = (u16)Pokemon_GetValue(v0, MON_DATA_IS_EGG, NULL);
        param0->partyMons[v1 + param2].hp = (u16)Pokemon_GetValue(v0, MON_DATA_HP, NULL);
        param0->partyMons[v1 + param2].maxHp = (u16)Pokemon_GetValue(v0, MON_DATA_MAX_HP, NULL);
        param0->partyMons[v1 + param2].level = (u16)Pokemon_GetValue(v0, MON_DATA_LEVEL, NULL);
        param0->partyMons[v1 + param2].heldItem = (u16)Pokemon_GetValue(v0, MON_DATA_HELD_ITEM, NULL);
        param0->partyMons[v1 + param2].ballCapsule = (u8)Pokemon_GetValue(v0, MON_DATA_BALL_CAPSULE_ID, NULL);
        param0->partyMons[v1 + param2].form = (u8)Pokemon_GetValue(v0, MON_DATA_FORM, NULL);

        if (Pokemon_GetValue(v0, MON_DATA_NO_PRINT_GENDER, NULL) == 1) {
            param0->partyMons[v1 + param2].hasGender = 0;
        } else {
            param0->partyMons[v1 + param2].hasGender = 1;
        }

        param0->partyMons[v1 + param2].gender = Pokemon_GetGender(v0);
        param0->partyMons[v1 + param2].statusIconAnim = (u8)PokemonSummaryScreen_StatusIconAnimIdx(v0);
    }
}

static void TrainerIntro_LoadParties(TrainerIntro *param0)
{
    memset(param0->partyMons, 0, sizeof(TrainerIntroMon) * 6);

    TrainerIntro_LoadPartyMonData(param0, param0->trainerIntroData->party[0], 0);
    TrainerIntro_LoadPartyMonData(param0, param0->trainerIntroData->party[2], 3);
}

static u8 TrainerIntro_GetHealthBarAnim(TrainerIntro *param0, u32 param1)
{
    if (param0->partyMons[param1].hp == 0) {
        return 0;
    }

    if ((param0->partyMons[param1].statusIconAnim != 7) && (param0->partyMons[param1].statusIconAnim != 0)) {
        return 5;
    }

    switch (HealthBar_Color(param0->partyMons[param1].hp, param0->partyMons[param1].maxHp, 48)) {
    case 4:
        return 1;
    case 3:
        return 2;
    case 2:
        return 3;
    case 1:
        return 4;
    }

    return 0;
}

static void TrainerIntro_CreateMonIconSprites(TrainerIntro *param0, u32 param1)
{
    u32 v0;

    for (v0 = 0; v0 < 5; v0++) {
        param0->sprites[param1 * 5 + v0] = TrainerIntro_CreateSprite(param0, &sMonIconTemplates[param1 * 5 + v0][0]);
        ManagedSprite_SetPositionXY(param0->sprites[param1 * 5 + v0], sMonIconPositions[param1][v0 * 2], sMonIconPositions[param1][v0 * 2 + 1]);
    }

    if (param0->partyMons[param1].species == 0) {
        for (v0 = 0; v0 < 5; v0++) {
            ManagedSprite_SetDrawFlag(param0->sprites[param1 * 5 + v0], 0);
        }
    } else {
        ManagedSprite_SetExplicitPalette(param0->sprites[param1 * 5 + 0], PokeIconPaletteIndex(param0->partyMons[param1].species, param0->partyMons[param1].form, param0->partyMons[param1].isEgg));
        ManagedSprite_SetAnim(param0->sprites[param1 * 5 + 0], TrainerIntro_GetHealthBarAnim(param0, param1));

        if (param0->partyMons[param1].heldItem == 0) {
            ManagedSprite_SetDrawFlag(param0->sprites[param1 * 5 + 1], 0);
        } else if (Item_IsMail(param0->partyMons[param1].heldItem) == 1) {
            ManagedSprite_SetAnim(param0->sprites[param1 * 5 + 1], 1);
        } else {
            ManagedSprite_SetAnim(param0->sprites[param1 * 5 + 1], 0);
        }

        if (param0->partyMons[param1].ballCapsule == 0) {
            ManagedSprite_SetDrawFlag(param0->sprites[param1 * 5 + 2], 0);
        } else {
            ManagedSprite_SetAnim(param0->sprites[param1 * 5 + 2], 2);
        }

        if (param0->partyMons[param1].statusIconAnim == 7) {
            ManagedSprite_SetDrawFlag(param0->sprites[param1 * 5 + 3], 0);
        } else {
            ManagedSprite_SetAnim(param0->sprites[param1 * 5 + 3], param0->partyMons[v0].statusIconAnim);
        }
    }
}

static void TrainerIntro_InitPartyPanelSprites(TrainerIntro *param0)
{
    SpriteResourceCapacities v0 = {
        9, 4, 4, 4, 0, 0
    };
    u32 v1;

    TrainerIntro_InitSpriteSystem(param0, &v0, 30 + 1);
    TrainerIntro_LoadMonIconResources(param0);
    TrainerIntro_LoadBallResources(param0);
    TrainerIntro_LoadStatusConditionResources(param0);
    TrainerIntro_LoadItemResources(param0);

    for (v1 = 0; v1 < 6; v1++) {
        TrainerIntro_CreateMonIconSprites(param0, v1);
    }

    TrainerIntro_SlideMonIcons(param0, 16);

    param0->spriteCount = 30;
}

static void TrainerIntro_LoadMonIconResources(TrainerIntro *param0)
{
    u32 v0;
    NARC *v1 = NARC_ctor(NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, param0->trainerIntroData->heapID);

    SpriteSystem_LoadPlttResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v1, PokeIconPalettesFileIndex(), FALSE, 3, NNS_G2D_VRAM_TYPE_2DMAIN, 47112);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v1, PokeIcon32KCellsFileIndex(), FALSE, 47113);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v1, PokeIcon32KAnimationFileIndex(), FALSE, 47113);

    for (v0 = 0; v0 < 6; v0++) {
        SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v1, param0->partyMons[v0].iconSpriteIndex, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 47113 + v0);
    }

    NARC_dtor(v1);
}

static void TrainerIntro_LoadBallResources(TrainerIntro *param0)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_GRAPHIC__PL_PLIST_GRA, param0->trainerIntroData->heapID);

    SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 20, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 47119);
    SpriteSystem_LoadPlttResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 21, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 47113);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 19, FALSE, 47114);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 18, FALSE, 47114);
    NARC_dtor(v0);
}

static void TrainerIntro_LoadStatusConditionResources(TrainerIntro *param0)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_GRAPHIC__PL_PST_GRA, param0->trainerIntroData->heapID);

    SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 64, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 47120);
    SpriteSystem_LoadPlttResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 65, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 47114);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 63, FALSE, 47115);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 62, FALSE, 47115);
    NARC_dtor(v0);
}

static void TrainerIntro_LoadItemResources(TrainerIntro *param0)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_GRAPHIC__PL_PLIST_GRA, param0->trainerIntroData->heapID);

    SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 2, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 47121);
    SpriteSystem_LoadPlttResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 8, FALSE, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 47115);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 1, FALSE, 47116);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 0, FALSE, 47116);
    NARC_dtor(v0);
}

static void TrainerIntro_SlideMonIcons(TrainerIntro *param0, s16 param1)
{
    s32 v0, v1, v2;

    if (param0->trainerIntroData->playerSide == 0) {
        v2 = 3;
        param1 *= 8;
    } else {
        v2 = 0;
        param1 *= -8;
    }

    for (v0 = 0; v0 < 3; v0++) {
        for (v1 = 0; v1 < 5; v1++) {
            ManagedSprite_SetPositionXY(
                param0->sprites[(v2 + v0) * 5 + v1], sMonIconPositions[v2 + v0][v1 * 2] + param1, sMonIconPositions[v2 + v0][v1 * 2 + 1]);
        }
    }
}

static void TrainerIntro_AddPartyWindows(TrainerIntro *param0)
{
    u32 v0;

    for (v0 = 0; v0 < 24; v0++) {
        Window_AddFromTemplate(param0->bgConfig, &param0->windows[v0], &sPartyWindowTemplates[v0]);
    }
}

static void TrainerIntro_RemovePartyWindows(TrainerIntro *param0)
{
    u32 v0;

    for (v0 = 0; v0 < 24; v0++) {
        Window_Remove(&param0->windows[v0]);
    }
}

static void TrainerIntro_DrawMonName(TrainerIntro *param0, MessageLoader *param1, FontSpecialCharsContext *param2, StringTemplate *param3, String *param4, u32 param5)
{
    Pokemon *v0;
    Window *v1;
    String *v2;

    v1 = &param0->windows[param5 * 4 + 0];

    if (param5 < 3) {
        v0 = Party_GetPokemonBySlotIndex(param0->trainerIntroData->party[0], param5);
    } else {
        v0 = Party_GetPokemonBySlotIndex(param0->trainerIntroData->party[2], param5 - 3);
    }

    v2 = MessageLoader_GetNewString(param1, 8 + param5);

    StringTemplate_SetNickname(param3, 0, Pokemon_GetBoxPokemon(v0));
    StringTemplate_Format(param3, param4, v2);
    String_Free(v2);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, param4, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);

    if (param0->partyMons[param5].hasGender == 0) {
        if (param0->partyMons[param5].gender == 0) {
            MessageLoader_GetString(param1, 27, param4);
            Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, param4, 64, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(3, 4, 0), NULL);
        } else if (param0->partyMons[param5].gender == 1) {
            MessageLoader_GetString(param1, 28, param4);
            Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, param4, 64, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(5, 6, 0), NULL);
        }
    }
}

static void TrainerIntro_DrawMonLevel(TrainerIntro *param0, MessageLoader *param1, FontSpecialCharsContext *param2, StringTemplate *param3, String *param4, u32 param5)
{
    Window *v0;
    String *v1;

    v0 = &param0->windows[param5 * 4 + 1];

    FontSpecialChars_DrawPartyScreenText(param2, 1, param0->partyMons[param5].level, 3, 0, v0, 0, 5 - 3);
}

static void TrainerIntro_DrawMonHp(TrainerIntro *param0, MessageLoader *param1, FontSpecialCharsContext *param2, StringTemplate *param3, String *param4, u32 param5)
{
    Window *v0;
    String *v1;
    u32 v2;
    int v3 = 28 - 28;
    int v4 = 0 + 2;
    v0 = &param0->windows[param5 * 4 + 2];

    FontSpecialChars_DrawPartyScreenHPText(param2, param0->partyMons[param5].hp, 3, 1, v0, v3, v4);
    FontSpecialChars_DrawPartyScreenLevelText(param2, 0, v0, v3 + 8 * 3, v4);
    FontSpecialChars_DrawPartyScreenHPText(param2, param0->partyMons[param5].maxHp, 3, 0, v0, v3 + (8 * 3) + 8, v4);
}

static void TrainerIntro_DrawMonHealthBar(TrainerIntro *param0, u32 param1)
{
    Window *v0;
    u32 v1;

    v0 = &param0->windows[param1 * 4 + 3];
    v1 = HealthBar_Color(param0->partyMons[param1].hp, param0->partyMons[param1].maxHp, 48);

    switch (v1) {
    case 0:
        break;
    case 4:
    case 3:
        Bg_LoadPalette(BG_LAYER_MAIN_1, &param0->partyPaletteBuffer[9], 2 * 2, (v0->palette * 16 + 9) * 2);
        break;
    case 2:
        Bg_LoadPalette(BG_LAYER_MAIN_1, &param0->partyPaletteBuffer[(9 + 16)], 2 * 2, (v0->palette * 16 + 9) * 2);
        break;
    case 1:
        Bg_LoadPalette(BG_LAYER_MAIN_1, &param0->partyPaletteBuffer[(9 + 32)], 2 * 2, (v0->palette * 16 + 9) * 2);
        break;
    }

    v1 = App_PixelCount(param0->partyMons[param1].hp, param0->partyMons[param1].maxHp, 48);

    Window_FillRectWithColor(v0, 10, 0, 2, v1, 1);
    Window_FillRectWithColor(v0, 9, 0, 3, v1, 2);
    Window_FillRectWithColor(v0, 10, 0, 5, v1, 1);
}

static void TrainerIntro_DrawMonPanel(TrainerIntro *param0, MessageLoader *param1, FontSpecialCharsContext *param2, StringTemplate *param3, String *param4, u32 param5)
{
    Pokemon *v0;
    Window *v1;
    String *v2;
    u32 v3;

    v1 = &param0->windows[param5 * 4];

    Window_FillTilemap(&v1[0], 0);
    Window_FillTilemap(&v1[1], 0);
    Window_FillTilemap(&v1[2], 0);
    Window_FillTilemap(&v1[3], 0);

    TrainerIntro_DrawMonName(param0, param1, param2, param3, param4, param5);
    TrainerIntro_DrawMonLevel(param0, param1, param2, param3, param4, param5);
    TrainerIntro_DrawMonHp(param0, param1, param2, param3, param4, param5);
    TrainerIntro_DrawMonHealthBar(param0, param5);

    Window_ScheduleCopyToVRAM(&v1[0]);
    Window_ScheduleCopyToVRAM(&v1[1]);
    Window_ScheduleCopyToVRAM(&v1[2]);
    Window_ScheduleCopyToVRAM(&v1[3]);
}

static void TrainerIntro_DrawPartyPanels(TrainerIntro *param0)
{
    MessageLoader *v0;
    FontSpecialCharsContext *v1;
    StringTemplate *v2;
    String *v3;
    u32 v4;

    v0 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_PARTY_MENU, param0->trainerIntroData->heapID);
    v1 = FontSpecialChars_Init(15, 14, 0, param0->trainerIntroData->heapID);
    v2 = StringTemplate_Default(param0->trainerIntroData->heapID);
    v3 = String_Init(32, param0->trainerIntroData->heapID);

    for (v4 = 0; v4 < 6; v4++) {
        if (param0->partyMons[v4].species == 0) {
            continue;
        }

        TrainerIntro_DrawMonPanel(param0, v0, v1, v2, v3, v4);
    }

    String_Free(v3);
    MessageLoader_Free(v0);
    FontSpecialChars_Free(v1);
    StringTemplate_Free(v2);
}

static void TrainerIntro_SaveJournalEntry(TrainerIntroData *trainerIntroData)
{
    void *journalEntryOnlineEvent;
    u16 *opponentName1;
    u16 *opponentName2;
    u8 opponentGender1;
    u8 opponentGender2;
    u8 battleResult;
    u8 v6;

    if (trainerIntroData->dto == NULL) {
        return;
    }

    v6 = CommSys_CurNetId();
    battleResult = trainerIntroData->battleResult - 1;

    if (MapHeader_IsUnionRoom(trainerIntroData->dto->mapHeaderID) == 1) {
        opponentGender1 = TrainerClass_Gender(trainerIntroData->dto->trainer[v6 ^ 1].header.trainerType);
        opponentName1 = Heap_Alloc(trainerIntroData->heapID, sizeof(u16) * (TRAINER_NAME_LEN + 1));

        String_ToChars(trainerIntroData->trainerNames[CommSys_GetBattlePosition(v6 ^ 1)], opponentName1, TRAINER_NAME_LEN + 1);
        journalEntryOnlineEvent = JournalEntry_CreateEventUnionBattle(opponentName1, opponentGender1, battleResult, trainerIntroData->heapID);
        Heap_Free(opponentName1);
    } else {
        switch (CommManager_GetCommType()) {
        case 1:
            opponentGender1 = TrainerClass_Gender(trainerIntroData->dto->trainer[v6 ^ 1].header.trainerType);
            opponentName1 = Heap_Alloc(trainerIntroData->heapID, sizeof(u16) * (TRAINER_NAME_LEN + 1));

            String_ToChars(trainerIntroData->trainerNames[CommSys_GetBattlePosition(v6 ^ 1)], opponentName1, TRAINER_NAME_LEN + 1);

            journalEntryOnlineEvent = JournalEntry_CreateEventSingleBattle(opponentName1, opponentGender1, battleResult, trainerIntroData->heapID);
            Heap_Free(opponentName1);
            break;
        case 2:
            opponentGender1 = TrainerClass_Gender(trainerIntroData->dto->trainer[v6 ^ 1].header.trainerType);
            opponentName1 = Heap_Alloc(trainerIntroData->heapID, sizeof(u16) * (TRAINER_NAME_LEN + 1));

            String_ToChars(trainerIntroData->trainerNames[CommSys_GetBattlePosition(v6 ^ 1)], opponentName1, TRAINER_NAME_LEN + 1);

            journalEntryOnlineEvent = JournalEntry_CreateEventDoubleBattle(opponentName1, opponentGender1, battleResult, trainerIntroData->heapID);
            Heap_Free(opponentName1);
            break;
        case 3:
            opponentGender1 = TrainerClass_Gender(trainerIntroData->dto->trainer[v6 ^ 1].header.trainerType);
            opponentName1 = Heap_Alloc(trainerIntroData->heapID, sizeof(u16) * (TRAINER_NAME_LEN + 1));

            String_ToChars(trainerIntroData->trainerNames[CommSys_GetBattlePosition(v6 ^ 1)], opponentName1, TRAINER_NAME_LEN + 1);

            journalEntryOnlineEvent = JournalEntry_CreateEventMixSingleBattle(opponentName1, opponentGender1, battleResult, trainerIntroData->heapID);
            Heap_Free(opponentName1);
            break;
        case 4:
            opponentName1 = Heap_Alloc(trainerIntroData->heapID, sizeof(u16) * (TRAINER_NAME_LEN + 1));
            opponentName2 = Heap_Alloc(trainerIntroData->heapID, sizeof(u16) * (TRAINER_NAME_LEN + 1));

            if (TrainerIntro_IsPlayerOnLeft() == 1) {
                opponentGender1 = TrainerClass_Gender(trainerIntroData->dto->trainer[1].header.trainerType);
                opponentGender2 = TrainerClass_Gender(trainerIntroData->dto->trainer[3].header.trainerType);

                String_ToChars(trainerIntroData->trainerNames[1], opponentName1, TRAINER_NAME_LEN + 1);
                String_ToChars(trainerIntroData->trainerNames[3], opponentName2, TRAINER_NAME_LEN + 1);
            } else {
                opponentGender1 = TrainerClass_Gender(trainerIntroData->dto->trainer[0].header.trainerType);
                opponentGender2 = TrainerClass_Gender(trainerIntroData->dto->trainer[2].header.trainerType);

                String_ToChars(trainerIntroData->trainerNames[0], opponentName1, TRAINER_NAME_LEN + 1);
                String_ToChars(trainerIntroData->trainerNames[2], opponentName2, TRAINER_NAME_LEN + 1);
            }

            journalEntryOnlineEvent = JournalEntry_CreateEventMultiBattle(opponentName1, opponentName2, opponentGender1, opponentGender2, battleResult, trainerIntroData->heapID);

            Heap_Free(opponentName1);
            Heap_Free(opponentName2);
            break;
        default:
            return;
        }
    }

    JournalEntry_SaveData(trainerIntroData->dto->journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
}

static void TrainerIntro_ShowMessageBox(TrainerIntro *param0)
{
    Window_FillRectWithColor(&param0->messageWindow, 15, 0, 0, 27 * 8, 4 * 8);
    Window_DrawMessageBoxWithScrollCursor(&param0->messageWindow, 0, 1, 15);
}

static BOOL TrainerIntro_CanSaveRecording(TrainerIntro *param0)
{
    if ((param0->trainerIntroData->dto->saveData == NULL) || (BattleRecording_Exists() == 0)) {
        return 0;
    }

    return 1;
}

static void TrainerIntro_ShowWaitDial(TrainerIntro *param0)
{
    if (param0->waitDial == NULL) {
        param0->waitDial = Window_AddWaitDial(&param0->messageWindow, 1);
    }
}

static void TrainerIntro_HideWaitDial(TrainerIntro *param0)
{
    if (param0->waitDial != NULL) {
        DestroyWaitDial(param0->waitDial);
        param0->waitDial = NULL;
    }
}
