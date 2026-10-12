#include "contest_competition/contest_competition_0223F118.h"

#include <nitro.h>
#include <nitro/sinit.h>
#include <string.h>

#include "generated/items.h"
#include "generated/pokemon_contest_types.h"

#include "struct_decls/font_oam.h"
#include "struct_decls/struct_02012744_decl.h"
#include "struct_defs/struct_font_oam_template.h"

#include "contest_competition/contest_competition_02252A70.h"
#include "contest_competition/struct_contest_text_label.h"
#include "contest_competition/struct_contest_sprite_group.h"
#include "contest_competition/struct_contest_palette_fade_task.h"

#include "bg_window.h"
#include "brightness_controller.h"
#include "char_transfer.h"
#include "contest.h"
#include "font.h"
#include "g3d_pipeline.h"
#include "game_overlay.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "palette.h"
#include "pokemon.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "text.h"
#include "font_oam.h"

FS_EXTERN_OVERLAY(battle_particles);
FS_EXTERN_OVERLAY(battle_anim);
FS_EXTERN_OVERLAY(image_clip_app);

static void contest_competition_0223F6E8(SysTask *param0, void *param1);
static void contest_competition_0223F15C(void);
static void contest_competition_0223F774(SysTask *param0, void *param1);

static const SpriteTemplate Unk_contest_competition_022531FC = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x0, 0x0, 0x0, 0x0, 0xFFFFFFFF, 0xFFFFFFFF },
    0x3,
    0x0
};

static const struct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    u8 unk_06;
} Unk_contest_competition_022531CC[] = {
    { 0xD, 0xAC, 0xFFFFFFFFFFFFFE80, 0x1 },
    { 0x25, 0xA4, 0x300, 0x1 },
    { 0x40, 0xB0, 0xFFFFFFFFFFFFFF80, 0x0 },
    { 0xC0, 0xB0, 0x80, 0x0 },
    { 0xDB, 0xA4, 0xFFFFFFFFFFFFFD00, 0x1 },
    { 0xF3, 0xAC, 0x180, 0x1 }
};

static void NitroStaticInit(void)
{
    Overlay_LoadByID(FS_OVERLAY_ID(battle_particles), 2);
    Overlay_LoadByID(FS_OVERLAY_ID(battle_anim), 2);
    Overlay_LoadByID(FS_OVERLAY_ID(image_clip_app), 2);
}

G3DPipelineBuffers *contest_competition_0223F140(enum HeapID heapID)
{
    return G3DPipeline_Init(heapID, TEXTURE_VRAM_SIZE_256K, PALETTE_VRAM_SIZE_32K, contest_competition_0223F15C);
}

static void contest_competition_0223F15C(void)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);

    G2_SetBG0Priority(1);
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(1);
    G3X_AlphaTest(0, 0);
    G3X_AlphaBlend(1);
    G3X_EdgeMarking(0);
    G3X_SetFog(0, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0);
    G3X_SetClearColor(GX_RGB(0, 0, 0), 0, 0x7fff, 63, 0);
    G3_ViewPort(0, 0, 255, 191);
}

void contest_competition_0223F1E0(G3DPipelineBuffers *param0)
{
    G3DPipelineBuffers_Free(param0);
}

void contest_competition_0223F1E8(enum HeapID heapID, BgConfig *param1, SpriteManager *param2, FontOAMManager *param3, ContestTextLabel *param4, const String *message, enum Font param6, TextColor param7, int param8, int param9, int param10, int param11, int param12, int param13, int param14)
{
    FontOAMTemplate v0;
    Window v1;
    CharTransferAllocation v2;
    int v3;
    FontOAM *v4;
    int v5, v6;
    int v7 = 0;

    {
        v5 = Font_CalcStringWidth(param6, message, v7);
        v6 = v5 / 8;

        if (FX_ModS32(v5, 8) != 0) {
            v6++;
        }
    }

    {
        Window_Init(&v1);
        Window_AddToTopLeftCorner(param1, &v1, v6, 16 / 8, 0, 0);
        Text_AddPrinterWithParamsColorAndSpacing(&v1, param6, message, 0, 0, TEXT_SPEED_NO_TRANSFER, param7, v7, 0, NULL);
    }

    v3 = FontOAM_GetWindowSize(&v1, NNS_G2D_VRAM_TYPE_2DMAIN, heapID);
    CharTransfer_AllocRange(v3, 1, NNS_G2D_VRAM_TYPE_2DMAIN, &v2);

    if (param12 == 1) {
        param10 -= v5 / 2;
    }

    param11 += 0 - 8;

    v0.unk_00 = param3;
    v0.unk_04 = &v1;
    v0.unk_08 = SpriteManager_GetSpriteList(param2);
    v0.unk_0C = SpriteManager_FindPlttResourceProxy(param2, param9);
    v0.unk_10 = NULL;
    v0.unk_14 = v2.offset;
    v0.unk_18 = param10;
    v0.unk_1C = param11;
    v0.unk_20 = param13;
    v0.unk_24 = param14;
    v0.unk_28 = NNS_G2D_VRAM_TYPE_2DMAIN;
    v0.heapID = heapID;

    v4 = FontOAM_New(&v0);

    if (param8 != 0) {
        FontOAM_SetExplicitPaletteOffset(v4, param8);
    }

    FontOAM_SetXY(v4, param10, param11);
    Window_Remove(&v1);

    param4->fontOAM = v4;
    param4->charTransfer = v2;
    param4->width = v5;
}

void contest_competition_0223F2E4(ContestTextLabel *param0)
{
    FontOAM_Free(param0->fontOAM);
    CharTransfer_ClearRange(&param0->charTransfer);
}

void contest_competition_0223F2F8(ContestTextLabel *param0, int param1, int param2, int param3)
{
    if (param3 == 1) {
        param1 -= param0->width / 2;
    }

    param2 += 0 - 8;
    FontOAM_SetXY(param0->fontOAM, param1, param2);
}

String *Contest_GetJudgeName(u32 judgeNameMessageID, enum HeapID heapID)
{
    MessageLoader *judgeNames = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_CONTEST_JUDGE_NAMES, heapID);
    String *judgeName = MessageLoader_GetNewString(judgeNames, judgeNameMessageID);

    MessageLoader_Free(judgeNames);
    return judgeName;
}

void contest_competition_0223F334(Contest *param0, int param1)
{
    u8 *v0;
    int v1;

    v0 = contest_competition_02252A9C(param1, param0->data.npcPhotoPreset);

    for (v1 = 0; v1 < 4; v1++) {
        param0->data.results[v1].danceScore = contest_competition_02252A70(param0->data.photos[v1], v0);
    }

    Heap_Free(v0);
}

void contest_competition_0223F374(Contest *contest)
{
    int i, primaryContestStat, secondayContestStat1, secondayContestStat2, sheen;
    u32 item;
    s32 itemModifier, contestStatScore;

    for (i = 0; i < CONTEST_NUM_PARTICIPANTS; i++) {
        item = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_HELD_ITEM, NULL);
        itemModifier = 100;

        switch (contest->data.contestType) {
        case CONTEST_TYPE_COOL:
            primaryContestStat = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_COOL, NULL);
            secondayContestStat1 = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_TOUGH, NULL);
            secondayContestStat2 = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_BEAUTY, NULL);

            switch (item) {
            case ITEM_RED_SCARF:
                itemModifier = 110;
                break;
            case ITEM_BLUE_SCARF:
            case ITEM_YELLOW_SCARF:
                itemModifier = 105;
                break;
            }
            break;
        case CONTEST_TYPE_BEAUTY:
            primaryContestStat = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_BEAUTY, NULL);
            secondayContestStat1 = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_COOL, NULL);
            secondayContestStat2 = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_CUTE, NULL);

            switch (item) {
            case ITEM_BLUE_SCARF:
                itemModifier = 110;
                break;
            case ITEM_RED_SCARF:
            case ITEM_PINK_SCARF:
                itemModifier = 105;
                break;
            }
            break;
        case CONTEST_TYPE_CUTE:
            primaryContestStat = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_CUTE, NULL);
            secondayContestStat1 = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_BEAUTY, NULL);
            secondayContestStat2 = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_SMART, NULL);

            switch (item) {
            case ITEM_PINK_SCARF:
                itemModifier = 110;
                break;
            case ITEM_BLUE_SCARF:
            case ITEM_GREEN_SCARF:
                itemModifier = 105;
                break;
            }
            break;
        case CONTEST_TYPE_SMART:
            primaryContestStat = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_SMART, NULL);
            secondayContestStat1 = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_CUTE, NULL);
            secondayContestStat2 = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_TOUGH, NULL);

            switch (item) {
            case ITEM_GREEN_SCARF:
                itemModifier = 110;
                break;
            case ITEM_PINK_SCARF:
            case ITEM_YELLOW_SCARF:
                itemModifier = 105;
                break;
            }
            break;
        case CONTEST_TYPE_TOUGH:
            primaryContestStat = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_TOUGH, NULL);
            secondayContestStat1 = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_SMART, NULL);
            secondayContestStat2 = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_COOL, NULL);

            switch (item) {
            case ITEM_YELLOW_SCARF:
                itemModifier = 110;
                break;
            case ITEM_GREEN_SCARF:
            case ITEM_RED_SCARF:
                itemModifier = 105;
                break;
            }

            break;
        default:
            GF_ASSERT(FALSE);
            return;
        }

        sheen = Pokemon_GetValue(contest->data.contestMons[i], MON_DATA_SHEEN, NULL);
        contestStatScore = primaryContestStat + ((secondayContestStat1 + secondayContestStat2 + sheen) / 2);
        contestStatScore = contestStatScore * itemModifier / 100;

        contest->data.results[i].visualScore = contestStatScore;
    }
}

void contest_competition_0223F560(SpriteSystem *param0, SpriteManager *param1, PaletteData *param2, int param3, int param4, int param5, int param6)
{
    if (param3 != -1) {
        SpriteSystem_LoadCharResObj(param0, param1, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_OBJ, 73, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, param3);
    }

    if (param4 != -1) {
        SpriteSystem_LoadPaletteBuffer(param2, PLTTBUF_MAIN_OBJ, param0, param1, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_OBJ, 7, 0, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, param4);
    }

    if (param5 != -1) {
        SpriteSystem_LoadCellResObj(param0, param1, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_OBJ, 74, TRUE, param5);
    }

    if (param6 != -1) {
        SpriteSystem_LoadAnimResObj(param0, param1, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_OBJ, 75, TRUE, param6);
    }
}

void contest_competition_0223F5E8(SpriteManager *param0, int param1, int param2, int param3, int param4)
{
    if (param1 != -1) {
        SpriteManager_UnloadCharObjById(param0, param1);
    }

    if (param2 != -1) {
        SpriteManager_UnloadPlttObjById(param0, param2);
    }

    if (param3 != -1) {
        SpriteManager_UnloadCellObjById(param0, param3);
    }

    if (param4 != -1) {
        SpriteManager_UnloadAnimObjById(param0, param4);
    }
}

void contest_competition_0223F630(ContestSpriteGroup *param0, SpriteSystem *param1, SpriteManager *param2, int param3, int param4, int param5, int param6, int param7, int param8, int param9, u32 param10)
{
    int v0;
    SpriteTemplate v1;

    GF_ASSERT(NELEMS(Unk_contest_competition_022531CC) == 6);

    v1 = Unk_contest_competition_022531FC;

    v1.resources[0] = param3;
    v1.resources[1] = param4;
    v1.resources[2] = param5;
    v1.resources[3] = param6;
    v1.plttIdx = param7;
    v1.priority = param8;
    v1.bgPriority = param9;

    for (v0 = 0; v0 < 6; v0++) {
        param0->sprites[v0] = SpriteSystem_NewSprite(param1, param2, &v1);

        ManagedSprite_SetPositionXY(param0->sprites[v0], Unk_contest_competition_022531CC[v0].unk_00, Unk_contest_competition_022531CC[v0].unk_02);
        ManagedSprite_SetAnim(param0->sprites[v0], Unk_contest_competition_022531CC[v0].unk_06);
        ManagedSprite_SetAffineOverwriteMode(param0->sprites[v0], AFFINE_OVERWRITE_MODE_NORMAL);
        Sprite_TickFrame(param0->sprites[v0]->sprite);
    }

    param0->task = SysTask_Start(contest_competition_0223F6E8, param0, param10);
}

void contest_competition_0223F6C4(ContestSpriteGroup *param0)
{
    int v0;

    for (v0 = 0; v0 < 6; v0++) {
        Sprite_DeleteAndFreeResources(param0->sprites[v0]);
    }

    SysTask_Done(param0->task);
    param0->task = NULL;
}

static void contest_competition_0223F6E8(SysTask *param0, void *param1)
{
    ContestSpriteGroup *v0 = param1;
    int v1;

    for (v1 = 0; v1 < 6; v1++) {
        ManagedSprite_OffsetAffineZRotation(v0->sprites[v1], Unk_contest_competition_022531CC[v1].unk_04);
    }
}

ContestPaletteFadeTask *contest_competition_0223F70C(enum HeapID heapID, PaletteData *param1, const u16 *param2, int param3, int param4, u32 param5)
{
    ContestPaletteFadeTask *v0 = Heap_Alloc(heapID, sizeof(ContestPaletteFadeTask));
    MI_CpuClear8(v0, sizeof(ContestPaletteFadeTask));

    v0->paletteData = param1;
    v0->durations = param2;
    v0->stepCount = param3;
    v0->repeatCount = param4;
    v0->task = SysTask_Start(contest_competition_0223F774, v0, param5);

    return v0;
}

void contest_competition_0223F744(ContestPaletteFadeTask *param0)
{
    GF_ASSERT(param0->task != NULL);

    SysTask_Done(param0->task);
    Heap_Free(param0);
}

BOOL contest_competition_0223F760(void)
{
    if (BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN) == TRUE) {
        return 1;
    }

    return 0;
}

static void contest_competition_0223F774(SysTask *param0, void *param1)
{
    ContestPaletteFadeTask *v0 = param1;

    if (BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN) == FALSE) {
        return;
    }

    v0->timer++;

    if (v0->timer > v0->durations[v0->currentStep]) {
        BrightnessController_StartTransition(6, 0, 4, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD), BRIGHTNESS_MAIN_SCREEN);
        Sound_PlayEffect(SEQ_SE_DP_KATI_sseq_1);

        v0->timer = 0;
        v0->currentStep++;

        if (v0->currentStep >= v0->stepCount) {
            if (v0->repeatCount == 0) {
                contest_competition_0223F744(v0);
                return;
            } else if (v0->repeatCount != 0xff) {
                v0->repeatCount--;
            }

            v0->currentStep = 0;
        }
    }
}
