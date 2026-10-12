#include <nitro.h>
#include <string.h>

#include "constants/narc.h"

#include "struct_defs/struct_vs_recorder_viewer_state.h"
#include "struct_defs/wifi_battle_tower_data.h"

#include "vs_recorder_viewer/vs_recorder_viewer.h"
#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_const_funcptr_tables.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022312B0.h"

#include "bg_window.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "math_util.h"
#include "narc.h"
#include "palette.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_system.h"
#include "system_vars.h"
#include "touch_screen.h"
#include "font_oam.h"
#include "player_profile.h"
#include "vs_recorder_ring.h"
#include "vars_flags.h"
#include "wifi_battle_tower_save.h"

typedef struct {
    int unk_00;
    f32 unk_04[5];
    int unk_18[5];
    int unk_2C[5];
    ManagedSprite *unk_40[5];
    ManagedSprite *unk_54[5];
    ManagedSprite *unk_68[5];
    ManagedSprite *unk_7C[5];
    int unk_90;
    ManagedSprite *unk_94[2];
    VsRecorderViewerTextSprite unk_9C[2];
    int unk_D4;
    int unk_D8;
} VsRecorderViewerFrontierPrint;

static void VsRecorderViewerFrontierPrint_SetExitPromptPosition(VsRecorderViewerState *param0, int param1);
static void VsRecorderViewerFrontierPrint_LoadExitPromptResources(VsRecorderViewerState *param0, int param1);
static void VsRecorderViewerFrontierPrint_CreateExitPrompt(VsRecorderViewerState *param0);
static void VsRecorderViewerFrontierPrint_FreeExitPrompt(VsRecorderViewerState *param0);
static void VsRecorderViewerFrontierPrint_LoadGraphics(VsRecorderViewerState *param0);
static void VsRecorderViewerFrontierPrint_GrayscalePaletteRange(u16 *param0, u16 param1, u16 param2);
static void VsRecorderViewerFrontierPrint_CreateSprites(VsRecorderViewerState *param0);
static void VsRecorderViewerFrontierPrint_FreeSprites(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerFrontierPrint_UpdateExpandAnimation(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerFrontierPrint_UpdateCollapseAnimation(VsRecorderViewerState *param0);
static void VsRecorderViewerFrontierPrint_SetSpriteRingPositions(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerFrontierPrint_Update(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerFrontierPrint_HandleTouchInput(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerFrontierPrint_Exit(VsRecorderViewerState *param0);

// clang-format off
BOOL(*const sVsRecorderViewerFrontierPrintStateTable[])(VsRecorderViewerState *) = {
    VsRecorderViewerFrontierPrint_Update,
    VsRecorderViewerFrontierPrint_HandleTouchInput,
    VsRecorderViewerFrontierPrint_Exit,
};
// clang-format on

static void VsRecorderViewerFrontierPrint_SetExitPromptPosition(VsRecorderViewerState *param0, int param1)
{
    VsRecorderViewerFrontierPrint *v0 = param0->unk_860;

    if (param1 == 0) {
        ManagedSprite_SetPositionXY(v0->unk_9C[1].unk_08, 128, 232);
    } else {
        ManagedSprite_SetPositionXY(v0->unk_9C[1].unk_08, 80, 232);
    }

    FontOAM_SetXY(v0->unk_9C[1].unk_0C, 36, -8);
}

static void VsRecorderViewerFrontierPrint_LoadExitPromptResources(VsRecorderViewerState *param0, int param1)
{
    NARC *v0 = param0->unk_14.unk_00;
    BgConfig *v1 = param0->unk_14.unk_10;
    SpriteSystem *v2 = param0->unk_14.unk_04;
    SpriteManager *v3 = param0->unk_14.unk_08;
    PaletteData *v4 = param0->unk_14.unk_14;

    SpriteSystem_LoadCharResObjFromOpenNarc(v2, v3, v0, 50, FALSE, param1, 11924);
    SpriteSystem_LoadCellResObjFromOpenNarc(v2, v3, v0, 28, FALSE, 11924);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v2, v3, v0, 29, FALSE, 11924);
}

static void VsRecorderViewerFrontierPrint_CreateExitPrompt(VsRecorderViewerState *param0)
{
    VsRecorderViewerFrontierPrint *v0 = param0->unk_860;

    VsRecorderViewerFrontierPrint_LoadExitPromptResources(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    v0->unk_9C[1].unk_08 = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    VsRecorderViewerMenu_InitLabelOAM(&v0->unk_9C[1], &param0->unk_14, NNS_G2D_VRAM_TYPE_2DSUB);
    VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_9C[1], &param0->unk_14, 3);

    ManagedSprite_SetPositionXY(v0->unk_9C[1].unk_08, 128, 232);
    FontOAM_SetXY(v0->unk_9C[1].unk_0C, 36, -8);
    FontOAM_SetDrawFlag(v0->unk_9C[1].unk_0C, 1);

    v0->unk_94[1] = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    ManagedSprite_SetPositionXY(v0->unk_94[1], 220, 160 + 64);
    ManagedSprite_SetAnim(v0->unk_94[1], 2);
    ManagedSprite_SetDrawFlag(v0->unk_94[1], 0);

    VsRecorderViewerFrontierPrint_SetExitPromptPosition(param0, 1);
}

static void VsRecorderViewerFrontierPrint_FreeExitPrompt(VsRecorderViewerState *param0)
{
    VsRecorderViewerFrontierPrint *v0 = param0->unk_860;

    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_9C[1]);
    Sprite_DeleteAndFreeResources(v0->unk_9C[1].unk_08);
    Sprite_DeleteAndFreeResources(v0->unk_94[1]);
    VsRecorderViewerMenu_FreeCursorSpriteResources(param0);
}

static void VsRecorderViewerFrontierPrint_LoadGraphics(VsRecorderViewerState *param0)
{
    VsRecorderViewerFrontierPrint *v0 = param0->unk_860;
    NARC *v1 = param0->unk_14.unk_00;
    BgConfig *v2 = param0->unk_14.unk_10;
    SpriteSystem *v3 = param0->unk_14.unk_04;
    SpriteManager *v4 = param0->unk_14.unk_08;
    PaletteData *v5 = param0->unk_14.unk_14;

    Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.unk_00, 62, param0->unk_14.unk_10, 6, 0, 0, 0, HEAP_ID_102);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v1, 68, v2, 6, 0, 0, 0, HEAP_ID_102);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v5, PLTTBUF_SUB_OBJ, v3, v4, v1, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 0), FALSE, 1, NNS_G2D_VRAM_TYPE_2DSUB, 29292);
    SpriteSystem_LoadCharResObjFromOpenNarc(v3, v4, v1, 66, FALSE, NNS_G2D_VRAM_TYPE_2DSUB, 29292);
    SpriteSystem_LoadCellResObjFromOpenNarc(v3, v4, v1, 71, FALSE, 29292);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v3, v4, v1, 72, FALSE, 29292);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v5, PLTTBUF_MAIN_OBJ, v3, v4, v1, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 1), FALSE, 6, NNS_G2D_VRAM_TYPE_2DMAIN, 28282);
    SpriteSystem_LoadCharResObjFromOpenNarc(v3, v4, v1, 64, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 28282);
    SpriteSystem_LoadCellResObjFromOpenNarc(v3, v4, v1, 38, FALSE, 28282);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v3, v4, v1, 39, FALSE, 28282);

    {
        int v6;
        int v7[5] = { 125, 291, 297, 295, 293 };
        int v8[5] = { 126, 292, 298, 296, 294 };
        int v9 = 9;
        int v10 = 10;

        for (v6 = 0; v6 < 5; v6++) {
            if (v6 == 3) {
                SpriteSystem_LoadPaletteBufferFromOpenNarc(v5, PLTTBUF_MAIN_OBJ, v3, v4, v1, 92, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 18181 + v6);
                SpriteSystem_LoadCharResObjFromOpenNarc(v3, v4, v1, 91, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 18181 + v6);
            } else {
                SpriteSystem_LoadPaletteBuffer(v5, PLTTBUF_MAIN_OBJ, v3, v4, NARC_INDEX_GRAPHIC__WIFI2DCHAR, v7[v6], FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 18181 + v6);
                SpriteSystem_LoadCharResObjAtEndWithHardwareMappingType(v3, v4, NARC_INDEX_GRAPHIC__WIFI2DCHAR, v8[v6], FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 18181 + v6);
            }
        }

        SpriteSystem_LoadCellResObj(v3, v4, NARC_INDEX_GRAPHIC__WIFI2DCHAR, v9, FALSE, 18181);
        SpriteSystem_LoadAnimResObj(v3, v4, NARC_INDEX_GRAPHIC__WIFI2DCHAR, v10, FALSE, 18181);
        SpriteSystem_LoadCellResObjFromOpenNarc(v3, v4, v1, 89, FALSE, 18181 + 1);
        SpriteSystem_LoadAnimResObjFromOpenNarc(v3, v4, v1, 90, FALSE, 18181 + 1);
    }

    {
        int v11 = 13;
        int v12 = 14;
        int v13 = 9;
        int v14 = 10;
        int v15 = PlayerProfile_GetGender(param0->unk_88C[0]);

        v3 = param0->unk_14.unk_04;
        v4 = param0->unk_14.unk_08;
        v5 = param0->unk_14.unk_14;

        if (v15 != 0) {
            v11 = 15;
            v12 = 16;
        }

        SpriteSystem_LoadPaletteBuffer(v5, 2, v3, v4, NARC_INDEX_GRAPHIC__WIFI2DCHAR, v11, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 165535);
        SpriteSystem_LoadCellResObj(v3, v4, NARC_INDEX_GRAPHIC__WIFI2DCHAR, v13, FALSE, 165535);
        SpriteSystem_LoadAnimResObj(v3, v4, NARC_INDEX_GRAPHIC__WIFI2DCHAR, v14, FALSE, 165535);
        SpriteSystem_LoadCharResObjAtEndWithHardwareMappingType(v3, v4, NARC_INDEX_GRAPHIC__WIFI2DCHAR, v12, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 165535);
    }
}

static void VsRecorderViewerFrontierPrint_GrayscalePaletteRange(u16 *param0, u16 param1, u16 param2)
{
    int v0, v1, v2, v3;
    u32 v4;

    for (v0 = 0; v0 < param1; v0++) {
        param0++;
    }

    for (; v0 < param1 + param2; v0++) {
        v1 = ((*param0) & 0x1f);
        v2 = (((*param0) >> 5) & 0x1f);
        v3 = (((*param0) >> 10) & 0x1f);

        v4 = (((v1) * 76 + (v2) * 151 + (v3) * 29) >> 8);

        *param0 = (u16)((v4 << 10) | (v4 << 5) | v4);
        param0++;
    }
}

static void VsRecorderViewerFrontierPrint_ApplyPrintStateGrayscale(VsRecorderViewerState *param0)
{
    VsRecorderViewerFrontierPrint *v0 = param0->unk_860;
    BgConfig *v1 = param0->unk_14.unk_10;
    SpriteSystem *v2 = param0->unk_14.unk_04;
    SpriteManager *v3 = param0->unk_14.unk_08;
    PaletteData *v4 = param0->unk_14.unk_14;
    int v5;
    int v6[5];

    {
        VarsFlags *v7 = SaveData_GetVarsFlags(param0->saveData);

        v6[0] = SystemVars_GetBattleTowerPrintState(v7);
        v6[1] = SystemVars_GetBattleFactoryPrintState(v7);
        v6[2] = SystemVars_GetBattleArcadePrintState(v7);
        v6[3] = SystemVars_GetBattleCastlePrintState(v7);
        v6[4] = SystemVars_GetBattleHallPrintState(v7);
    }

    for (v5 = 0; v5 < 5; v5++) {
        if (v6[v5] != 0) {
            int v8[] = { 0, 1, 4, 3, 2 };

            if (v6[v5] == 2) {
                PaletteData *v9 = param0->unk_14.unk_14;
                u16 *v10;

                v10 = PaletteData_GetFadedBuffer(v9, 2);
                VsRecorderViewerFrontierPrint_GrayscalePaletteRange(v10, (4 + v8[v5]) * 16, 16);
            }
        }
    }

    PaletteData_SetAutoTransparent(v4, TRUE);
}

static void VsRecorderViewerFrontierPrint_CreateSprites(VsRecorderViewerState *param0)
{
    int v0;
    int v1 = 0;
    int v2[4 + 1];
    int v3[5];
    VsRecorderViewerFrontierPrint *v4 = param0->unk_860;
    BgConfig *v5 = param0->unk_14.unk_10;
    SpriteSystem *v6 = param0->unk_14.unk_04;
    SpriteManager *v7 = param0->unk_14.unk_08;
    PaletteData *v8 = param0->unk_14.unk_14;
    SpriteTemplate v9;

    v9.x = 0;
    v9.y = 256;
    v9.z = 0;
    v9.animIdx = 0;
    v9.priority = 10;
    v9.plttIdx = 0;
    v9.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v9.bgPriority = 0;
    v9.vramTransfer = FALSE;
    v9.resources[4] = SPRITE_RESOURCE_NONE;
    v9.resources[5] = SPRITE_RESOURCE_NONE;
    v9.resources[0] = 165535;
    v9.resources[1] = 165535;
    v9.resources[2] = 165535;
    v9.resources[3] = 165535;

    for (v0 = 0; v0 < 5; v0++) {
        v4->unk_40[v0] = SpriteSystem_NewSprite(param0->unk_14.unk_04, param0->unk_14.unk_08, &v9);
        ManagedSprite_SetAnim(v4->unk_40[v0], 1);
        ManagedSprite_TickFrame(v4->unk_40[v0]);
        ManagedSprite_SetAffineScale(v4->unk_40[v0], v4->unk_04[v0], v4->unk_04[v0]);
    }

    for (v0 = 0; v0 < 5; v0++) {
        v9.resources[0] = 18181 + v0;
        v9.resources[1] = 18181 + v0;

        if (v0 == 3) {
            v9.resources[2] = 18181 + 1;
            v9.resources[3] = 18181 + 1;
        } else {
            v9.resources[2] = 18181;
            v9.resources[3] = 18181;
        }

        v4->unk_54[v0] = SpriteSystem_NewSprite(param0->unk_14.unk_04, param0->unk_14.unk_08, &v9);

        if (v0 == 3) {
            ManagedSprite_SetAnim(v4->unk_54[v0], 0);
        } else {
            ManagedSprite_SetAnim(v4->unk_54[v0], 1);
        }

        ManagedSprite_TickFrame(v4->unk_54[v0]);
        ManagedSprite_SetAffineScale(v4->unk_54[v0], v4->unk_04[v0], v4->unk_04[v0]);
        ManagedSprite_SetExplicitPalette(v4->unk_54[v0], 10 + v0);
    }

    v9.resources[0] = 28282;
    v9.resources[1] = 28282;
    v9.resources[2] = 28282;
    v9.resources[3] = 28282;
    v9.resources[4] = SPRITE_RESOURCE_NONE;
    v9.resources[5] = SPRITE_RESOURCE_NONE;
    v9.priority = 20;

    {
        VarsFlags *v10 = SaveData_GetVarsFlags(param0->saveData);

        v3[0] = SystemVars_GetBattleTowerPrintState(v10);
        v3[1] = SystemVars_GetBattleFactoryPrintState(v10);
        v3[2] = SystemVars_GetBattleArcadePrintState(v10);
        v3[3] = SystemVars_GetBattleCastlePrintState(v10);
        v3[4] = SystemVars_GetBattleHallPrintState(v10);
    }

    for (v0 = 0; v0 < 5; v0++) {
        v4->unk_68[v0] = SpriteSystem_NewSprite(param0->unk_14.unk_04, param0->unk_14.unk_08, &v9);

        if (v3[v0] == 0) {
            ManagedSprite_SetAnim(v4->unk_68[v0], 5);
            ManagedSprite_SetExplicitPalette(v4->unk_68[v0], 4 + 5);
            ManagedSprite_SetDrawFlag(v4->unk_54[v0], 0);
            ManagedSprite_SetDrawFlag(v4->unk_40[v0], 0);
        } else {
            int v11[] = { 0, 1, 4, 3, 2 };

            ManagedSprite_SetAnim(v4->unk_68[v0], v11[v0]);
            ManagedSprite_SetExplicitPalette(v4->unk_68[v0], 4 + v11[v0]);
        }

        ManagedSprite_TickFrame(v4->unk_68[v0]);
        ManagedSprite_SetAffineScale(v4->unk_68[v0], v4->unk_04[v0], v4->unk_04[v0]);
    }

    v9.resources[0] = 29292;
    v9.resources[1] = 29292;
    v9.resources[2] = 29292;
    v9.resources[3] = 29292;
    v9.resources[4] = SPRITE_RESOURCE_NONE;
    v9.resources[5] = SPRITE_RESOURCE_NONE;
    v9.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    v9.priority = 0;

    {
        int v12 = 1000;
        int v13 = v4->unk_90;
        BOOL v14 = 0;

        for (v0 = 0; v0 < 4; v0++) {
            v2[v0] = v13 / v12;
            v13 %= v12;
            v12 /= 10;

            if ((v2[v0] == 0) && (v14 == 0)) {
                v1++;
            } else {
                v14 = 1;
            }
        }

        v2[4] = 10;
    }

    for (v0 = 0; v0 < 4 + 1; v0++) {
        v4->unk_7C[v0] = SpriteSystem_NewSprite(param0->unk_14.unk_04, param0->unk_14.unk_08, &v9);

        if (v2[v0] == 0) {
            if (v0 < v1) {
                ManagedSprite_SetDrawFlag(v4->unk_7C[v0], 0);
            }
        }

        ManagedSprite_SetAnim(v4->unk_7C[v0], v2[v0]);
        VsRecorderViewerMenu_SetSpritePositionWithOffset(v4->unk_7C[v0], 88 + (16 * v0), 72);
        ManagedSprite_TickFrame(v4->unk_7C[v0]);
    }

    ManagedSprite_SetDrawFlag(v4->unk_7C[4 - 1], TRUE);
    ManagedSprite_SetDrawFlag(v4->unk_7C[4 - 0], TRUE);

    for (v0 = 0; v0 < 5; v0++) {
        ManagedSprite_SetAffineOverwriteMode(v4->unk_40[v0], AFFINE_OVERWRITE_MODE_DOUBLE);
        ManagedSprite_SetAffineOverwriteMode(v4->unk_54[v0], AFFINE_OVERWRITE_MODE_DOUBLE);
        ManagedSprite_SetAffineOverwriteMode(v4->unk_68[v0], AFFINE_OVERWRITE_MODE_DOUBLE);
    }
}

static void VsRecorderViewerFrontierPrint_FreeSprites(VsRecorderViewerState *param0)
{
    int v0;
    VsRecorderViewerFrontierPrint *v1 = param0->unk_860;

    for (v0 = 0; v0 < 5; v0++) {
        SpriteManager_UnloadCharObjById(param0->unk_14.unk_08, 18181 + v0);
        SpriteManager_UnloadPlttObjById(param0->unk_14.unk_08, 18181 + v0);
        Sprite_DeleteAndFreeResources(v1->unk_54[v0]);
    }

    SpriteManager_UnloadCellObjById(param0->unk_14.unk_08, 18181);
    SpriteManager_UnloadAnimObjById(param0->unk_14.unk_08, 18181);
    SpriteManager_UnloadCellObjById(param0->unk_14.unk_08, 18181 + 1);
    SpriteManager_UnloadAnimObjById(param0->unk_14.unk_08, 18181 + 1);

    for (v0 = 0; v0 < 5; v0++) {
        Sprite_DeleteAndFreeResources(v1->unk_40[v0]);
    }

    SpriteManager_UnloadCharObjById(param0->unk_14.unk_08, 165535);
    SpriteManager_UnloadPlttObjById(param0->unk_14.unk_08, 165535);
    SpriteManager_UnloadCellObjById(param0->unk_14.unk_08, 165535);
    SpriteManager_UnloadAnimObjById(param0->unk_14.unk_08, 165535);

    for (v0 = 0; v0 < 5; v0++) {
        Sprite_DeleteAndFreeResources(v1->unk_68[v0]);
    }

    SpriteManager_UnloadCharObjById(param0->unk_14.unk_08, 28282);
    SpriteManager_UnloadPlttObjById(param0->unk_14.unk_08, 28282);
    SpriteManager_UnloadCellObjById(param0->unk_14.unk_08, 28282);
    SpriteManager_UnloadAnimObjById(param0->unk_14.unk_08, 28282);

    for (v0 = 0; v0 < 4 + 1; v0++) {
        Sprite_DeleteAndFreeResources(v1->unk_7C[v0]);
    }

    SpriteManager_UnloadCharObjById(param0->unk_14.unk_08, 29292);
    SpriteManager_UnloadPlttObjById(param0->unk_14.unk_08, 29292);
    SpriteManager_UnloadCellObjById(param0->unk_14.unk_08, 29292);
    SpriteManager_UnloadAnimObjById(param0->unk_14.unk_08, 29292);
}

static BOOL VsRecorderViewerFrontierPrint_UpdateExpandAnimation(VsRecorderViewerState *param0)
{
    VsRecorderViewerFrontierPrint *v0 = param0->unk_860;
    int v1;
    s16 v2, v3;
    fx32 v4, v5;

    for (v1 = 0; v1 < 5; v1++) {
        v0->unk_2C[v1] += 20;
        v0->unk_2C[v1] %= 360;
    }

    VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_D4, &v0->unk_D8, 0, 0);

    for (v1 = 0; v1 < 5; v1++) {
        if (v0->unk_2C[0] != 0) {
            v0->unk_04[v1] += 0.05f;
        } else {
            ManagedSprite_SetAffineOverwriteMode(v0->unk_40[v1], AFFINE_OVERWRITE_MODE_NONE);
            ManagedSprite_SetAffineOverwriteMode(v0->unk_54[v1], AFFINE_OVERWRITE_MODE_NONE);
            ManagedSprite_SetAffineOverwriteMode(v0->unk_68[v1], AFFINE_OVERWRITE_MODE_NONE);
            v0->unk_04[v1] = 1.0f;
        }

        v4 = (128 << FX32_SHIFT) + CalcSineDegrees_Wraparound(v0->unk_2C[v1]) * v0->unk_18[v1];
        v5 = (106 << FX32_SHIFT) - CalcCosineDegrees_Wraparound(v0->unk_2C[v1]) * v0->unk_18[v1];

        ManagedSprite_SetPositionFxXY(v0->unk_68[v1], v4, v5);
        ManagedSprite_GetPositionXY(v0->unk_68[v1], &v2, &v3);
        ManagedSprite_SetPositionXY(v0->unk_40[v1], v2 - 32, v3 - 2);
        ManagedSprite_SetPositionXY(v0->unk_54[v1], v2 + 16, v3 - 2);
        ManagedSprite_SetAffineScale(v0->unk_68[v1], v0->unk_04[v1], v0->unk_04[v1]);
        ManagedSprite_SetAffineScale(v0->unk_40[v1], v0->unk_04[v1], v0->unk_04[v1]);
        ManagedSprite_SetAffineScale(v0->unk_54[v1], v0->unk_04[v1], v0->unk_04[v1]);
    }

    if (v0->unk_2C[0] == 0) {
        return 0;
    }

    return 1;
}

static BOOL VsRecorderViewerFrontierPrint_UpdateCollapseAnimation(VsRecorderViewerState *param0)
{
    VsRecorderViewerFrontierPrint *v0 = param0->unk_860;
    int v1;
    s16 v2, v3;
    fx32 v4, v5;

    for (v1 = 0; v1 < 5; v1++) {
        v0->unk_2C[v1] += 20;
        v0->unk_2C[v1] %= 360;
    }

    if (v0->unk_2C[0] == 20) {
        for (v1 = 0; v1 < 5; v1++) {
            ManagedSprite_SetAffineOverwriteMode(v0->unk_40[v1], AFFINE_OVERWRITE_MODE_DOUBLE);
            ManagedSprite_SetAffineOverwriteMode(v0->unk_54[v1], AFFINE_OVERWRITE_MODE_DOUBLE);
            ManagedSprite_SetAffineOverwriteMode(v0->unk_68[v1], AFFINE_OVERWRITE_MODE_DOUBLE);
        }
    }

    VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_D4, &v0->unk_D8, 1, 0);

    for (v1 = 0; v1 < 5; v1++) {
        if (v0->unk_2C[0] != 0) {
            v0->unk_04[v1] -= 0.05f;
        } else {
            ManagedSprite_SetDrawFlag(v0->unk_68[v1], 0);
            ManagedSprite_SetDrawFlag(v0->unk_40[v1], 0);
            ManagedSprite_SetDrawFlag(v0->unk_54[v1], 0);
        }

        v4 = (128 << FX32_SHIFT) - CalcSineDegrees_Wraparound(v0->unk_2C[v1]) * v0->unk_18[v1];
        v5 = (106 << FX32_SHIFT) - CalcCosineDegrees_Wraparound(v0->unk_2C[v1]) * v0->unk_18[v1];

        ManagedSprite_SetPositionFxXY(v0->unk_68[v1], v4, v5);
        ManagedSprite_GetPositionXY(v0->unk_68[v1], &v2, &v3);
        ManagedSprite_SetPositionXY(v0->unk_40[v1], v2 - 32, v3 - 2);
        ManagedSprite_SetPositionXY(v0->unk_54[v1], v2 + 16, v3 - 2);
        ManagedSprite_SetAffineScale(v0->unk_68[v1], v0->unk_04[v1], v0->unk_04[v1]);
        ManagedSprite_SetAffineScale(v0->unk_40[v1], v0->unk_04[v1], v0->unk_04[v1]);
        ManagedSprite_SetAffineScale(v0->unk_54[v1], v0->unk_04[v1], v0->unk_04[v1]);
    }

    if (v0->unk_2C[0] == 0) {
        return 0;
    }

    return 1;
}

static void VsRecorderViewerFrontierPrint_SetSpriteRingPositions(VsRecorderViewerState *param0)
{
    VsRecorderViewerFrontierPrint *v0 = param0->unk_860;
    int v1;
    int v2 = 0;
    s16 v3, v4;
    fx32 v5, v6;
    static s16 v7[][2] = {
        { 128, 32 + 10 },
        { 189, 77 + 10 },
        { 172, 124 + 10 },
        { 83, 124 + 10 },
        { 66, 77 + 10 },
    };

    for (v1 = 0; v1 < 5; v1++) {
        v5 = v7[v1][0] << FX32_SHIFT;
        v6 = v7[v1][1] << FX32_SHIFT;

        ManagedSprite_SetPositionFxXY(v0->unk_68[v1], v5, v6);
        ManagedSprite_GetPositionXY(v0->unk_68[v1], &v3, &v4);
        ManagedSprite_SetPositionXY(v0->unk_40[v1], v3 - 32, v4 - 2);
        ManagedSprite_SetPositionXY(v0->unk_54[v1], v3 + 16, v4 - 2);
    }
}

static BOOL VsRecorderViewerFrontierPrint_Update(VsRecorderViewerState *param0)
{
    VsRecorderViewerFrontierPrint *v0;

    if (param0->unk_08 == 0) {
        v0 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerFrontierPrint));
        MI_CpuFill8(v0, 0, sizeof(VsRecorderViewerFrontierPrint));
        param0->unk_860 = v0;
        v0->unk_00 = 0;

        {
            int v1;

            for (v1 = 0; v1 < 5; v1++) {
                if ((v1 == 2) || (v1 == 3)) {
                    v0->unk_18[v1] = 52;
                } else {
                    v0->unk_18[v1] = 64;
                }

                v0->unk_2C[v1] = v1 * (360 / 5);
                v0->unk_04[v1] = 0.2f;
            }
        }
        Bg_ClearTilemap(param0->unk_14.unk_10, 3);
        Bg_ClearTilemap(param0->unk_14.unk_10, 2);
        Bg_ClearTilemap(param0->unk_14.unk_10, 7);
        Bg_ClearTilemap(param0->unk_14.unk_10, 6);
        VsRecorderViewerMenu_SetDefaultBlendAlpha(&v0->unk_D4, &v0->unk_D8, 0);
        VsRecorderViewerMenu_UpdateBlendAlpha(&v0->unk_D4, &v0->unk_D8, 0, 0, GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG1, 0);
        Sound_PlayEffect(SEQ_SE_PL_BREC20_sseq);
        param0->unk_08++;
    } else {
        v0 = param0->unk_860;
    }

    switch (param0->unk_08) {
    case 1:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_00, 1)) {
            WifiBattleTowerRecord *record = SaveData_GetWifiBattleTowerRecord(param0->saveData);

            v0->unk_90 = WifiBattleTowerRecord_UpdateBattlePoints(record, 0, BATTLE_POINTS_FUNC_NONE);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_00, param0->unk_14.unk_44);
        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_00, param0->unk_14.unk_44);
        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_BG, 0x2, v0->unk_00, param0->unk_14.unk_44);
        break;

    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_HideAndFreeMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_StartNetworkTask(param0, 0);
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        VsRecorderViewerList_SetBgPriorities();
        Bg_SetPriority(BG_LAYER_SUB_2, 2);
        VsRecorderViewerFrontierPrint_LoadGraphics(param0);
        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC | 0x10, v0->unk_00, param0->unk_14.unk_44);
        param0->unk_08++;
        break;
    case 3:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerFrontierPrint_CreateExitPrompt(param0);
        VsRecorderViewerFrontierPrint_CreateSprites(param0);
        VsRecorderViewerFrontierPrint_ApplyPrintStateGrayscale(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
        param0->unk_08++;
        break;
    case 4: {
        BOOL v3 = VsRecorderViewerFrontierPrint_UpdateExpandAnimation(param0);

        VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_D4, &v0->unk_D8, 0, 0);
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_00, 0);

        if (v3 == 0) {
            param0->unk_08++;
            VsRecorderViewerFrontierPrint_SetSpriteRingPositions(param0);
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC | 0x10, v0->unk_00, param0->unk_14.unk_44);
    } break;
    default:
        VsRecorderViewerMain_SetState(param0, 1);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerFrontierPrint_HandleTouchInput(VsRecorderViewerState *param0)
{
    VsRecorderViewerFrontierPrint *v0 = param0->unk_860;

    {
        u32 v1, v2;
        BOOL v3 = 0;

        v3 = TouchScreen_GetTapState(&v1, &v2);

        if (v3) {
            if ((v1 > 10 * 8) && (v1 < 22 * 8) && (v2 > 19 * 8) && (v2 < 22 * 8)) {
                Sound_PlayEffect(SEQ_SE_PL_BREC57_sseq);
                VsRecorderViewerMain_SetState(param0, 2);
            }
        }
    }

    return 0;
}

static BOOL VsRecorderViewerFrontierPrint_Exit(VsRecorderViewerState *param0)
{
    VsRecorderViewerFrontierPrint *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        if (v0->unk_00 == 0) {
            Sound_PlayEffect(SEQ_SE_PL_BREC21_sseq);
        }
        if (v0->unk_00 != 16) {
            v0->unk_00 += 2;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC | 0x10, v0->unk_00, param0->unk_14.unk_44);
        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_BG, 0x4018, v0->unk_00, param0->unk_14.unk_44);

        if (VsRecorderViewerFrontierPrint_UpdateCollapseAnimation(param0) == 0) {
            v0->unk_00 = 0;
            param0->unk_08++;
        }
        break;
    case 1:
        param0->unk_08++;
    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerFrontierPrint_FreeSprites(param0);
        VsRecorderViewerFrontierPrint_FreeExitPrompt(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);

        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);

        v0->unk_00 = 16;
        v0->unk_00 = 0;
        param0->unk_08++;
        break;
    case 3:
        VsRecorderViewerMain_SetWhichScreenIs3D(1);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Bg_ClearTilemap(param0->unk_14.unk_10, 2);
        Bg_ClearTilemap(param0->unk_14.unk_10, 6);
        Bg_ClearTilemap(param0->unk_14.unk_10, 3);
        Bg_ClearTilemap(param0->unk_14.unk_10, 7);
        param0->unk_08++;
        break;
    case 4:
        if (v0->unk_00 != 0) {
            v0->unk_00 -= 2;
        } else {
            param0->unk_08++;
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_00);
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_00, param0->unk_14.unk_44);
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC | 0x10, v0->unk_00, param0->unk_14.unk_44);
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_BG, 0x2, v0->unk_00, param0->unk_14.unk_44);
        }

        break;
    default:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_00, 0)) {
            G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, 7, 8);
            G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, 7, 8);
            Heap_Free(v0);
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_00);
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.unk_44);
            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);
        } else {
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_00, param0->unk_14.unk_44);
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_BG, 0x2, v0->unk_00, param0->unk_14.unk_44);
        }

        break;
    }

    return 0;
}
