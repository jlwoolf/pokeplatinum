#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_font_oam_template.h"
#include "struct_defs/struct_vs_recorder_state.h"
#include "struct_defs/struct_020F3DCC.h"

#include "vs_recorder_viewer/vs_recorder_viewer.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022307C0.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022307C0_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02230C28.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223118C.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022312B0.h"

#include "bg_window.h"
#include "char_transfer.h"
#include "graphics.h"
#include "math_util.h"
#include "message.h"
#include "narc.h"
#include "palette.h"
#include "sprite.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "text.h"
#include "font_oam.h"
#include "player_profile.h"
#include "vs_recorder_graphics.h"

static const u8 sVsRecorderViewerMenuSpritePriorities[][5] = {
    { 0x5, 0xA, 0xF, 0x14, 0x19 },
    { 0x19, 0x14, 0xF, 0xA, 0x5 }
};

void VsRecorderViewerMenu_LoadBackground(VsRecorderState *param0)
{
    NARC *v0 = param0->menuContext.narc;
    BgConfig *v1 = param0->menuContext.bgConfig;
    SpriteSystem *v2 = param0->menuContext.spriteSystem;
    SpriteManager *v3 = param0->menuContext.spriteManager;
    PaletteData *v4 = param0->menuContext.palette;

    if (param0->mode == 0) {
        Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 67, v1, 1, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 67, v1, 5, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 69, v1, 5, 0, 0, 0, HEAP_ID_102);
        PaletteData_LoadBufferFromFileStart(v4, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 3), HEAP_ID_102, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * (8 + 1), PLTT_DEST(0));
        PaletteData_LoadBufferFromFileStart(v4, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 3), HEAP_ID_102, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * (8 + 1), PLTT_DEST(0));
        PaletteData_LoadBufferFromFileStart(v4, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 0), HEAP_ID_102, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
        PaletteData_LoadBufferFromFileStart(v4, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 0), HEAP_ID_102, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
    } else {
        Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 54, v1, 1, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 54, v1, 5, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 55, v1, 5, 0, 0, 0, HEAP_ID_102);
        PaletteData_LoadBufferFromFileStart(v4, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, 53, HEAP_ID_102, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * (8 + 1), PLTT_DEST(0));
        PaletteData_LoadBufferFromFileStart(v4, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, 53, HEAP_ID_102, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * (8 + 1), PLTT_DEST(0));
        PaletteData_LoadBufferFromFileStart(v4, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, 52, HEAP_ID_102, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
        PaletteData_LoadBufferFromFileStart(v4, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, 52, HEAP_ID_102, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
    }

    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 70, v1, 5, 0, 0, 0, HEAP_ID_102);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 70, v1, 1, 0, 0, 0, HEAP_ID_102);
    PaletteData_BlendMulti(v4, PLTTBUF_SUB_BG, 0x2, 16, param0->menuContext.themeColor);
}

void VsRecorderViewerMenu_LoadBgPanel(VsRecorderState *param0, int param1, BOOL param2)
{
    NARC *v0 = param0->menuContext.narc;
    BgConfig *v1 = param0->menuContext.bgConfig;
    SpriteSystem *v2 = param0->menuContext.spriteSystem;
    SpriteManager *v3 = param0->menuContext.spriteManager;
    PaletteData *v4 = param0->menuContext.palette;
    int v5 = 2;

    if (param2) {
        v5 = 0;
    }

    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 45, v1, param1, 0, 0, 0, HEAP_ID_102);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, v5, v1, param1, 0, 0, 0, HEAP_ID_102);
}

void VsRecorderViewerMenu_LoadBgPanelAlt(VsRecorderState *param0, int param1)
{
    NARC *v0 = param0->menuContext.narc;
    BgConfig *v1 = param0->menuContext.bgConfig;
    SpriteSystem *v2 = param0->menuContext.spriteSystem;
    SpriteManager *v3 = param0->menuContext.spriteManager;
    PaletteData *v4 = param0->menuContext.palette;
    int v5 = 1;

    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 45, v1, param1, 0, 0, 0, HEAP_ID_102);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, v5, v1, param1, 0, 0, 0, HEAP_ID_102);
}

void VsRecorderViewerMenu_LoadEntrySpriteResources(VsRecorderState *param0)
{
    NARC *v0 = param0->menuContext.narc;
    BgConfig *v1 = param0->menuContext.bgConfig;
    SpriteSystem *v2 = param0->menuContext.spriteSystem;
    SpriteManager *v3 = param0->menuContext.spriteManager;
    PaletteData *v4 = param0->menuContext.palette;

    if (param0->mode == 0) {
        SpriteSystem_LoadPaletteBufferFromOpenNarc(v4, PLTTBUF_MAIN_OBJ, v2, v3, v0, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 2), FALSE, 3, NNS_G2D_VRAM_TYPE_2DMAIN, 9999);
        SpriteSystem_LoadPaletteBufferFromOpenNarc(v4, PLTTBUF_SUB_OBJ, v2, v3, v0, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 2), FALSE, 3, NNS_G2D_VRAM_TYPE_2DSUB, 10000);
    } else {
        SpriteSystem_LoadPaletteBufferFromOpenNarc(v4, PLTTBUF_MAIN_OBJ, v2, v3, v0, 51, FALSE, 3, NNS_G2D_VRAM_TYPE_2DMAIN, 9999);
        SpriteSystem_LoadPaletteBufferFromOpenNarc(v4, PLTTBUF_SUB_OBJ, v2, v3, v0, 51, FALSE, 3, NNS_G2D_VRAM_TYPE_2DSUB, 10000);
    }

    SpriteSystem_LoadCharResObjFromOpenNarc(v2, v3, v0, 65, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 9999);
    SpriteSystem_LoadCharResObjFromOpenNarc(v2, v3, v0, 65, FALSE, NNS_G2D_VRAM_TYPE_2DSUB, 10000);
    SpriteSystem_LoadCellResObjFromOpenNarc(v2, v3, v0, 46, FALSE, 9999);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v2, v3, v0, 47, FALSE, 9999);
    SpriteSystem_LoadCellResObjFromOpenNarc(v2, v3, v0, 46, FALSE, 10000);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v2, v3, v0, 47, FALSE, 10000);
}

void VsRecorderViewerMenu_CreateDecorativeSprites(VsRecorderState *param0)
{
    SpriteTemplate v0;
    SpriteSystem *v1 = param0->menuContext.spriteSystem;
    SpriteManager *v2 = param0->menuContext.spriteManager;
    PaletteData *v3 = param0->menuContext.palette;

    v0.x = 0;
    v0.y = 0;
    v0.z = 0;
    v0.animIdx = 0;
    v0.priority = 0;
    v0.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v0.bgPriority = 2;
    v0.vramTransfer = FALSE;
    v0.plttIdx = 0;
    v0.resources[0] = 9999;
    v0.resources[1] = 9999;
    v0.resources[2] = 9999;
    v0.resources[3] = 9999;
    v0.resources[4] = SPRITE_RESOURCE_NONE;
    v0.resources[5] = SPRITE_RESOURCE_NONE;

    {
        int v4, v5;
        const s16 v6[] = {
            82,
            178,
            118,
            42,
            150,
            210,
        };
        const f32 v7[] = {
            1.4f,
            1.8f,
            2.0f,
            1.6f,
            1.4f,
            1.6f,
        };
        const s8 v8[] = {
            -1,
            -3,
            +2,
            -1,
            -3,
            +2,
        };

        for (v5 = 0; v5 < (3 * 2); v5++) {
            for (v4 = 0; v4 < 2; v4++) {
                if (v4 == 0) {
                    v0.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
                    v0.resources[0] = 9999;
                    v0.resources[1] = 9999;
                    v0.resources[2] = 9999;
                    v0.resources[3] = 9999;
                } else {
                    v0.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
                    v0.resources[0] = 10000;
                    v0.resources[1] = 10000;
                    v0.resources[2] = 10000;
                    v0.resources[3] = 10000;
                }

                param0->menuSprites[v5].sprites[v4] = SpriteSystem_NewSprite(v1, v2, &v0);

                if (v4 == 0) {
                    VsRecorderViewerMenu_SetSpritePositionWithOffset(param0->menuSprites[v5].sprites[v4], v6[v5], 192 / 2);
                } else {
                    VsRecorderViewerMenu_SetSpritePositionWithOffset(param0->menuSprites[v5].sprites[v4], v6[v5], 192 / 2);
                }

                ManagedSprite_TickFrame(param0->menuSprites[v5].sprites[v4]);
                ManagedSprite_SetAffineOverwriteMode(param0->menuSprites[v5].sprites[v4], AFFINE_OVERWRITE_MODE_DOUBLE);
                ManagedSprite_SetAffineScale(param0->menuSprites[v5].sprites[v4], v7[v5], 1.0f);

                param0->menuSprites[v5].step = 0;
                param0->menuSprites[v5].phase = v5 % 3;
                param0->menuSprites[v5].state = 0;
                param0->menuSprites[v5].scale = v7[v5];
                param0->menuSprites[v5].stepCount = 10 + (v8[v5] * 2);

                if (v5 < 3) {
                    param0->menuSprites[v5].angle = 0;
                    param0->menuSprites[v5].targetX = 0 + (8 + v8[v5]);
                    param0->menuSprites[v5].direction = -1;
                } else {
                    param0->menuSprites[v5].angle = 0;
                    param0->menuSprites[v5].targetX = 255 - (8 + v8[v5]);
                    param0->menuSprites[v5].direction = +1;
                }
            }

            param0->menuSprites[v5].task = SysTask_ExecuteOnVBlank(VsRecorderViewerMenu_AnimatedSpriteTask, &param0->menuSprites[v5], 5);
        }
        if (param0->menu.mainEntryCount != 0) {
            BOOL v9;

            do {
                v9 = 0;

                for (v5 = 0; v5 < (3 * 2); v5++) {
                    if (param0->menuSprites[v5].state == 3) {
                        continue;
                    }

                    VsRecorderViewerMenu_AnimatedSpriteTask(param0->menuSprites[v5].task, &param0->menuSprites[v5]);
                    v9 = 1;
                }
            } while (v9);
        }
    }
}

void VsRecorderViewerMenu_FreeDecorativeSprites(VsRecorderState *param0)
{
    int v0, v1;

    for (v1 = 0; v1 < (3 * 2); v1++) {
        for (v0 = 0; v0 < 2; v0++) {
            Sprite_DeleteAndFreeResources(param0->menuSprites[v1].sprites[v0]);
        }
    }
}

void VsRecorderViewerMenu_StopDecorativeSpriteTasks(VsRecorderState *param0)
{
    int v0;

    for (v0 = 0; v0 < (3 * 2); v0++) {
        SysTask_Done(param0->menuSprites[v0].task);
    }
}

void VsRecorderViewerMenu_LoadEntryIconResources(VsRecorderState *param0)
{
    NARC *v0 = param0->menuContext.narc;
    BgConfig *v1 = param0->menuContext.bgConfig;
    SpriteSystem *v2 = param0->menuContext.spriteSystem;
    SpriteManager *v3 = param0->menuContext.spriteManager;
    PaletteData *v4 = param0->menuContext.palette;
    int v5;
    int v6;
    int v7;

    switch (param0->mode) {
    case 0:
        v5 = 63;
        v6 = 24;
        v7 = 25;
        break;
    case 2:
        v5 = 17;
        v6 = 18;
        v7 = 19;
        break;
    case 5:
    case 6:
        v5 = 8;
        v6 = 9;
        v7 = 10;
        break;
    case 4:
        v5 = 11;
        v6 = 12;
        v7 = 13;
        break;
    case 3:
        v5 = 14;
        v6 = 15;
        v7 = 16;
        break;
    default:
        v5 = 48;
        v6 = 22;
        v7 = 23;
        break;
    }

    SpriteSystem_LoadCharResObjFromOpenNarc(v2, v3, v0, v5, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 10001);
    SpriteSystem_LoadCharResObjFromOpenNarc(v2, v3, v0, v5, FALSE, NNS_G2D_VRAM_TYPE_2DSUB, 10002);
    SpriteSystem_LoadCellResObjFromOpenNarc(v2, v3, v0, v6, FALSE, 10001);
    SpriteSystem_LoadCellResObjFromOpenNarc(v2, v3, v0, v6, FALSE, 10002);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v2, v3, v0, v7, FALSE, 10001);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v2, v3, v0, v7, FALSE, 10002);
}

void VsRecorderViewerMenu_FreeEntryIconResources(VsRecorderState *param0)
{
    SpriteManager_UnloadCharObjById(param0->menuContext.spriteManager, 10001);
    SpriteManager_UnloadCharObjById(param0->menuContext.spriteManager, 10002);
}

void VsRecorderViewerMenu_PositionMenuEntries(VsRecorderState *param0)
{
    int v0;
    VsRecorderViewerMenu *v1 = &param0->menu;

    for (v0 = 0; v0 < 5; v0++) {
        VsRecorderViewerMenu_SetSpritePositionWithOffset(v1->mainEntries[v0].sprite, 42 + 8, (25 + (36 * 4) + (16 * (5 - (param0->menu.subEntryCount)))) + 48);
        FontOAM_SetXY(param0->menu.mainEntries[v0].fontOAM, 36, -8);
    }

    v0 = 0;

    do {
        s16 v2, v3;

        if (param0->menu.mainEntryCount == 0) {
            break;
        }

        VsRecorderViewerMenu_GetSpritePositionWithOffset(param0->menu.mainEntries[v0].sprite, &v2, &v3);

        if (param0->menu.mainEntryCount - 1 == v0) {
            v2 = v2;
            v3 = (25 + (36 * (5 - 1)));
            ManagedSprite_SetExplicitPaletteOffset(param0->menu.mainEntries[v0].sprite, (2 - 1));
        } else {
            v2 = v2 - (4 * (param0->menu.mainEntryCount - v0));
            v3 = (16 * (param0->menu.mainEntryCount - v0 - 1)) + (25 + (36 * (5 - (param0->menu.mainEntryCount - v0))));
            ManagedSprite_SetExplicitPaletteOffset(param0->menu.mainEntries[v0].sprite, (3 - 1));
        }

        VsRecorderViewerMenu_SetSpritePositionWithOffset(param0->menu.mainEntries[v0].sprite, v2, v3);

        v0++;
    } while (v0 < param0->menu.mainEntryCount);
}

void VsRecorderViewerMenu_CreateMenuEntries(VsRecorderState *param0)
{
    int v0;
    VsRecorderViewerMenu *v1 = &param0->menu;
    SpriteTemplate v2;
    SpriteSystem *v3 = param0->menuContext.spriteSystem;
    SpriteManager *v4 = param0->menuContext.spriteManager;
    PaletteData *v5 = param0->menuContext.palette;

    v2.x = 42;
    v2.y = (25 + (36 * 4) + (16 * (5 - (param0->menu.subEntryCount)))) + 32;

    if (param0->menu.subEntryCount == 2) {
        v2.y = (25 + (36 * 4) + (16 * (4 - (param0->menu.subEntryCount)))) + 32;
    }

    v2.z = 0;
    v2.animIdx = 0;
    v2.priority = 0;
    v2.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v2.bgPriority = 3;
    v2.vramTransfer = FALSE;
    v2.plttIdx = (2 - 1);
    v2.resources[0] = 10001;
    v2.resources[1] = 9999;
    v2.resources[2] = 10001;
    v2.resources[3] = 10001;
    v2.resources[4] = SPRITE_RESOURCE_NONE;
    v2.resources[5] = SPRITE_RESOURCE_NONE;

    for (v0 = 0; v0 < 5; v0++) {
        v2.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
        v2.resources[0] = 10002;
        v2.resources[1] = 10000;
        v2.resources[2] = 10002;
        v2.resources[3] = 10002;
        v2.priority = sVsRecorderViewerMenuSpritePriorities[1][v0];
        v1->mainEntries[v0].sprite = SpriteSystem_NewSprite(v3, v4, &v2);

        ManagedSprite_TickFrame(v1->mainEntries[v0].sprite);
        ManagedSprite_SetDrawFlag(v1->mainEntries[v0].sprite, 1);
        VsRecorderViewerMenu_SetSpritePositionWithOffset(v1->mainEntries[v0].sprite, v2.x + 8, v2.y);

        v2.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
        v2.resources[0] = 10001;
        v2.resources[1] = 9999;
        v2.resources[2] = 10001;
        v2.resources[3] = 10001;
        v2.priority = sVsRecorderViewerMenuSpritePriorities[0][v0];
        v1->subEntries[v0].sprite = SpriteSystem_NewSprite(v3, v4, &v2);

        ManagedSprite_TickFrame(v1->subEntries[v0].sprite);
        VsRecorderViewerMenu_SetSpritePositionWithOffset(v1->subEntries[v0].sprite, v2.x, v2.y);
        ManagedSprite_SetDrawFlag(v1->subEntries[v0].sprite, param0->currentMenu[v0].enabled);
    }

    v0 = 0;

    do {
        s16 v6, v7;

        if (param0->menu.mainEntryCount == 0) {
            break;
        }

        VsRecorderViewerMenu_GetSpritePositionWithOffset(param0->menu.mainEntries[v0].sprite, &v6, &v7);

        if (param0->menu.mainEntryCount - 1 == v0) {
            v6 = v6;
            v7 = (25 + (36 * (5 - 1)));
            ManagedSprite_SetExplicitPaletteOffset(param0->menu.mainEntries[v0].sprite, 2 - 1);
        } else {
            v6 = v6 - (4 * (param0->menu.mainEntryCount - v0));
            v7 = (16 * (param0->menu.mainEntryCount - v0 - 1)) + (25 + (36 * (5 - (param0->menu.mainEntryCount - v0))));
            ManagedSprite_SetExplicitPaletteOffset(param0->menu.mainEntries[v0].sprite, (3 - 1));
        }

        VsRecorderViewerMenu_SetSpritePositionWithOffset(param0->menu.mainEntries[v0].sprite, v6, v7);

        v0++;
    } while (v0 < param0->menu.mainEntryCount);

    PaletteData_BlendMulti(v5, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->menuContext.themeColor);
}

void VsRecorderViewerMenu_UpdateSubEntryLabels(VsRecorderState *param0)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        ManagedSprite_SetDrawFlag(param0->menu.subEntries[v0].sprite, param0->currentMenu[v0].enabled);

        if (param0->currentMenu[v0].enabled == 0) {
            continue;
        }

        ManagedSprite_SetAnim(param0->menu.subEntries[v0].sprite, param0->currentMenu[v0].spriteAnimID);
        VsRecorderViewerMenu_RenderEntryLabel(param0, &param0->menu.subEntries[v0], param0->currentMenu[v0].labelMessageID, &param0->currentMenu[v0]);
    }
}

void VsRecorderViewerMenu_AttachEntryLabelSprites(VsRecorderState *param0)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        FontOAM_SetParentSprite(param0->menu.subEntries[v0].fontOAM, param0->menu.subEntries[v0].sprite->sprite);
        FontOAM_SetParentSprite(param0->menu.mainEntries[v0].fontOAM, param0->menu.mainEntries[v0].sprite->sprite);
    }
}

void VsRecorderViewerMenu_UpdateMainEntryLabels(VsRecorderState *param0)
{
    int v0;

    if (param0->menu.mainEntryCount == 0) {
        return;
    }

    for (v0 = 0; v0 < param0->menu.mainEntryCount; v0++) {
        ManagedSprite_SetAnim(param0->menu.mainEntries[v0].sprite, param0->menu.entryConfigs[v0]->spriteAnimID);
        VsRecorderViewerMenu_RenderEntryLabel(param0, &param0->menu.mainEntries[v0], param0->menu.entryConfigs[v0]->labelMessageID, param0->menu.entryConfigs[v0]);
        FontOAM_SetXY(param0->menu.mainEntries[v0].fontOAM, 36, -8);
        FontOAM_SetDrawFlag(param0->menu.mainEntries[v0].fontOAM, 1);
        ManagedSprite_SetDrawFlag(param0->menu.mainEntries[v0].sprite, 1);
    }
}

void VsRecorderViewerMenu_FreeMenuEntries(VsRecorderState *param0)
{
    int v0;
    VsRecorderViewerMenu *v1 = &param0->menu;

    for (v0 = 0; v0 < 5; v0++) {
        Sprite_DeleteAndFreeResources(v1->mainEntries[v0].sprite);
        Sprite_DeleteAndFreeResources(v1->subEntries[v0].sprite);
    }
}

void VsRecorderViewerMenu_SetMenuEntriesVisible(VsRecorderState *param0, BOOL param1)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        if (param0->menu.mainEntries[v0].visible == 0) {
            FontOAM_SetDrawFlag(param0->menu.mainEntries[v0].fontOAM, 0);
            ManagedSprite_SetDrawFlag(param0->menu.mainEntries[v0].sprite, 0);
        } else {
            FontOAM_SetDrawFlag(param0->menu.mainEntries[v0].fontOAM, param1);
            ManagedSprite_SetDrawFlag(param0->menu.mainEntries[v0].sprite, param1);
        }

        if (param0->menu.subEntries[v0].visible == 0) {
            FontOAM_SetDrawFlag(param0->menu.subEntries[v0].fontOAM, 0);
            ManagedSprite_SetDrawFlag(param0->menu.subEntries[v0].sprite, 0);
        } else {
            FontOAM_SetDrawFlag(param0->menu.subEntries[v0].fontOAM, param1);
            ManagedSprite_SetDrawFlag(param0->menu.subEntries[v0].sprite, param1);
        }
    }
}

void VsRecorderViewerMenu_AnimatedSpriteTask(SysTask *param0, void *param1)
{
    VsRecorderViewerMenuAnimatedSprite *v0 = param1;

    v0->tick++;
    v0->tick %= 2;

    if (v0->tick) {
        return;
    }

    switch (v0->state) {
    case 0: {
        if (v0->step == 3) {
            v0->state++;
            v0->step = 0;
        } else {
            v0->step++;
        }
    } break;
    case 1: {
        fx32 v1, v2;
        fx32 v3, v4;

        if (v0->step == 4) {
            v0->state++;
            v0->step = 0;
        } else {
            ManagedSprite_GetPositionFxXY(v0->sprites[0], &v1, &v2);
            ManagedSprite_GetPositionFxXY(v0->sprites[1], &v3, &v4);

            v1 = v1 + ((CalcSineDegrees_Wraparound((v0->angle * 0xffff) / 360) * 1) * (v0->direction * -1));
            v3 = v1;

            v0->angle += 32;
            v0->angle %= 360;

            ManagedSprite_SetPositionFxXY(v0->sprites[0], v1, v2);
            ManagedSprite_SetPositionFxXY(v0->sprites[1], v3, v4);

            v0->step++;
        }
    } break;

    case 2: {
        s16 v5, v6, v7;
        int v8[] = {
            90,
            135,
            270,
            45,
            225,
            0,
        };

        ManagedSprite_GetPositionXY(v0->sprites[0], &v5, &v6);
        ManagedSprite_GetPositionXY(v0->sprites[1], &v5, &v7);

        if (v0->step == 0) {
            v0->xStep = v0->targetX - v5;
            v0->xStep /= v0->stepCount;
            v0->step++;
        } else if (v0->step == v0->stepCount + 1) {
            v5 = v0->targetX;
            v0->angle = v8[v0->phase];
            v0->state++;
            v0->step = 0;
        } else {
            v5 += v0->xStep;
            v0->step++;
        }

        ManagedSprite_SetPositionXY(v0->sprites[0], v5, v6);
        ManagedSprite_SetPositionXY(v0->sprites[1], v5, v7);
    } break;
    case 3: {
        fx32 v9, v10;
        fx32 v11, v12;

        if (v0->step == 0) {
            ManagedSprite_GetPositionFxXY(v0->sprites[0], &v0->baseX, &v10);
            v0->step++;
        }

        ManagedSprite_GetPositionFxXY(v0->sprites[0], &v9, &v10);
        ManagedSprite_GetPositionFxXY(v0->sprites[1], &v11, &v12);

        v9 = v0->baseX + ((CalcSineDegrees_Wraparound((v0->angle * 0xffff) / 360) * 3) * (v0->direction * -1));
        v11 = v9;

        if (v0->phase % 2) {
            v0->angle -= 4;
        } else {
            v0->angle += 4;
        }

        v0->angle %= 360;

        ManagedSprite_SetPositionFxXY(v0->sprites[0], v9, v10);
        ManagedSprite_SetPositionFxXY(v0->sprites[1], v11, v12);
    } break;
    }

    if ((v0->state >= 2) && (v0->scale > 0.1f)) {
        v0->scale -= 0.10f;

        ManagedSprite_SetAffineScale(v0->sprites[0], v0->scale, 1.0f);
        ManagedSprite_SetAffineScale(v0->sprites[1], v0->scale, 1.0f);
    }
}

void VsRecorderViewerMenu_SetSpritePositionWithOffset(ManagedSprite *param0, s16 param1, s16 param2)
{
    ManagedSprite_SetPositionXYWithSubscreenOffset(param0, param1, param2, (256 * FX32_ONE));
}

void VsRecorderViewerMenu_GetSpritePositionWithOffset(ManagedSprite *param0, s16 *param1, s16 *param2)
{
    Sprite_GetPositionXYWithSubscreenOffset2(param0, param1, param2, (256 * FX32_ONE));
}

void VsRecorderViewerMenu_CreateEntryLabels(VsRecorderState *param0)
{
    s16 v0, v1;
    FontOAMTemplate v2;
    String *v3;
    int v4;
    MessageLoader *v5;
    Window v6;
    VsRecorderViewerMenuEntry *v7[2];
    int v8[2] = { NNS_G2D_VRAM_TYPE_2DMAIN, NNS_G2D_VRAM_TYPE_2DSUB };
    int v9[2] = { 9999, 10000 };
    int v10, v11;

    for (v10 = 0; v10 < 5; v10++) {
        v7[0] = &param0->menu.subEntries[v10];
        v7[1] = &param0->menu.mainEntries[v10];

        for (v11 = 0; v11 < 2; v11++) {
            Window_Init(&v6);
            Window_AddToTopLeftCorner(param0->menuContext.bgConfig, &v6, 20, 2, 0, 0);

            v7[v11]->fontOAMWindow = FontOAMWindow_New(&v6, HEAP_ID_102);
            v4 = FontOAM_GetWindowSize(&v6, v8[v11], HEAP_ID_102);

            CharTransfer_AllocRange(v4, 1, v8[v11], &v7[v11]->charTransfer);
            ManagedSprite_GetPositionXY(v7[v11]->sprite, &v0, &v1);

            v2.fontOAMManager = param0->menuContext.fontOAMManager;
            v2.window = &v6;
            v2.spriteList = SpriteManager_GetSpriteList(param0->menuContext.spriteManager);
            v2.paletteProxy = SpriteManager_FindPlttResourceProxy(param0->menuContext.spriteManager, v9[v11]);
            v2.parentSprite = v7[v11]->sprite->sprite;
            v2.charOffset = v7[v11]->charTransfer.offset;
            v2.x = v0 + 36;
            v2.y = v1 + -8;
            v2.resourcePriority = 3;
            v2.spritePriority = sVsRecorderViewerMenuSpritePriorities[v11][v10] - 1;
            v2.vramType = v8[v11];
            v2.heapID = HEAP_ID_102;
            v7[v11]->fontOAM = FontOAM_NewFromWindow(&v2, v7[v11]->fontOAMWindow);

            FontOAM_SetExplicitPaletteOffsetAutoAdjust(v7[v11]->fontOAM, (2 - 1));
            Window_Remove(&v6);
            FontOAM_SetDrawFlag(v7[v11]->fontOAM, 0);
        }
    }
}

void VsRecorderViewerMenu_RenderEntryLabel(VsRecorderState *param0, VsRecorderViewerMenuEntry *param1, int param2, const VsRecorderMenuEntry *param3)
{
    String *v0;
    MessageLoader *v1;
    Window v2;
    StringTemplate *v3;
    String *v4;
    String *v5;

    v1 = param0->menuContext.messageLoader;

    if (param2 == 8) {
        if (param0->profiles[param3->dataIndex] == NULL) {
            v0 = MessageLoader_GetNewString(v1, param2);
        } else {
            v3 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
            v4 = MessageLoader_GetNewString(param0->menuContext.messageLoader, 7);
            v5 = PlayerProfile_GetName(param0->profiles[param3->dataIndex], HEAP_ID_102);
            VsRecorderViewerList_CheckNameChars(param0, v5);
            v0 = String_Init(255, HEAP_ID_102);

            StringTemplate_SetString(v3, 0, v5, 0, 1, GAME_LANGUAGE);
            StringTemplate_Format(v3, v0, v4);
            String_Free(v4);
            String_Free(v5);
            StringTemplate_Free(v3);
        }
    } else if (param2 == 41) {
        if (param0->profiles[param3->dataIndex] == NULL) {
            v0 = MessageLoader_GetNewString(v1, param2);
        } else {
            v3 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
            v4 = MessageLoader_GetNewString(param0->menuContext.messageLoader, 7);
            v5 = PlayerProfile_GetName(param0->profiles[param3->dataIndex], HEAP_ID_102);
            VsRecorderViewerList_CheckNameChars(param0, v5);
            v0 = String_Init(255, HEAP_ID_102);

            StringTemplate_SetString(v3, 0, v5, 0, 1, GAME_LANGUAGE);
            StringTemplate_Format(v3, v0, v4);
            String_Free(v4);
            String_Free(v5);
            StringTemplate_Free(v3);
        }
    } else {
        v0 = MessageLoader_GetNewString(v1, param2);
    }

    Window_Init(&v2);
    Window_AddToTopLeftCorner(param0->menuContext.bgConfig, &v2, 20, 2, 0, 0);
    Text_AddPrinterWithParamsAndColor(&v2, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(14, 13, 0), NULL);
    FontOAMWindow_UploadToVRAM(param1->fontOAM, param1->fontOAMWindow, &v2, HEAP_ID_102);
    String_Free(v0);
    Window_Remove(&v2);
}

void VsRecorderViewerMenu_FreeEntryLabels(VsRecorderState *param0)
{
    int v0, v1;
    VsRecorderViewerMenuEntry *v2[2];

    for (v0 = 0; v0 < 5; v0++) {
        v2[0] = &param0->menu.subEntries[v0];
        v2[1] = &param0->menu.mainEntries[v0];

        for (v1 = 0; v1 < 2; v1++) {
            FontOAMWindow_Free(v2[v1]->fontOAMWindow);
            FontOAM_Delete(v2[v1]->fontOAM);
            CharTransfer_ClearRange(&v2[v1]->charTransfer);
        }
    }
}

void VsRecorderViewerMenu_InitLabelOAM(VsRecorderViewerTextSprite *param0, VsRecorderViewerMenuContext *param1, int param2)
{
    s16 v0, v1;
    FontOAMTemplate v2;
    String *v3;
    int v4;
    MessageLoader *v5;
    Window v6;
    int v7 = 9999;

    if (param2 == NNS_G2D_VRAM_TYPE_2DSUB) {
        v7 = 10000;
    }

    Window_Init(&v6);
    Window_AddToTopLeftCorner(param1->bgConfig, &v6, 20, 2, 0, 0);

    param0->fontOAMWindow = FontOAMWindow_New(&v6, HEAP_ID_102);
    v4 = FontOAM_GetWindowSize(&v6, param2, HEAP_ID_102);

    CharTransfer_AllocRange(v4, 1, param2, &param0->charTransfer);
    ManagedSprite_GetPositionXY(param0->sprite, &v0, &v1);

    v2.fontOAMManager = param1->fontOAMManager;
    v2.window = &v6;
    v2.spriteList = SpriteManager_GetSpriteList(param1->spriteManager);
    v2.paletteProxy = SpriteManager_FindPlttResourceProxy(param1->spriteManager, v7);
    v2.parentSprite = param0->sprite->sprite;
    v2.charOffset = param0->charTransfer.offset;
    v2.x = v0 + 36;
    v2.y = v1 + -8;
    v2.resourcePriority = 3;
    v2.spritePriority = 0;
    v2.vramType = param2;
    v2.heapID = HEAP_ID_102;

    param0->fontOAM = FontOAM_NewFromWindow(&v2, param0->fontOAMWindow);

    FontOAM_SetExplicitPaletteOffsetAutoAdjust(param0->fontOAM, (2 - 1));
    Window_Remove(&v6);
    FontOAM_SetDrawFlag(param0->fontOAM, 0);
}

void VsRecorderViewerMenu_SetLabelOAMText(VsRecorderViewerTextSprite *param0, VsRecorderViewerMenuContext *param1, int param2)
{
    String *v0;
    MessageLoader *v1;
    Window v2;

    v1 = param1->messageLoader;
    v0 = MessageLoader_GetNewString(v1, param2);

    Window_Init(&v2);
    Window_AddToTopLeftCorner(param1->bgConfig, &v2, 20, 2, 0, 0);
    Text_AddPrinterWithParamsAndColor(&v2, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(14, 13, 0), NULL);
    FontOAMWindow_UploadToVRAM(param0->fontOAM, param0->fontOAMWindow, &v2, HEAP_ID_102);
    String_Free(v0);
    Window_Remove(&v2);
}

void VsRecorderViewerMenu_FreeLabelOAM(VsRecorderViewerTextSprite *param0)
{
    FontOAMWindow_Free(param0->fontOAMWindow);
    FontOAM_Delete(param0->fontOAM);
    CharTransfer_ClearRange(&param0->charTransfer);
}

void VsRecorderViewerMenu_LoadSpriteResourceSetA(VsRecorderState *param0, int param1)
{
    NARC *v0 = param0->menuContext.narc;
    BgConfig *v1 = param0->menuContext.bgConfig;
    SpriteSystem *v2 = param0->menuContext.spriteSystem;
    SpriteManager *v3 = param0->menuContext.spriteManager;
    PaletteData *v4 = param0->menuContext.palette;

    SpriteSystem_LoadCharResObjFromOpenNarc(v2, v3, v0, 49, FALSE, param1, 11924);
    SpriteSystem_LoadCellResObjFromOpenNarc(v2, v3, v0, 26, FALSE, 11924);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v2, v3, v0, 27, FALSE, 11924);
}

void VsRecorderViewerMenu_LoadCursorSpriteResources(VsRecorderState *param0, int param1)
{
    NARC *v0 = param0->menuContext.narc;
    BgConfig *v1 = param0->menuContext.bgConfig;
    SpriteSystem *v2 = param0->menuContext.spriteSystem;
    SpriteManager *v3 = param0->menuContext.spriteManager;
    PaletteData *v4 = param0->menuContext.palette;

    SpriteSystem_LoadCharResObjFromOpenNarc(v2, v3, v0, 122, FALSE, param1, 11924);
    SpriteSystem_LoadCellResObjFromOpenNarc(v2, v3, v0, 123, FALSE, 11924);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v2, v3, v0, 124, FALSE, 11924);
}

void VsRecorderViewerMenu_LoadSpriteResourceSetB(VsRecorderState *param0, int param1)
{
    NARC *v0 = param0->menuContext.narc;
    BgConfig *v1 = param0->menuContext.bgConfig;
    SpriteSystem *v2 = param0->menuContext.spriteSystem;
    SpriteManager *v3 = param0->menuContext.spriteManager;
    PaletteData *v4 = param0->menuContext.palette;
    int v5 = 30;
    int v6 = 32;
    int v7 = 31;

    SpriteSystem_LoadCharResObjFromOpenNarc(v2, v3, v0, v5, FALSE, param1, 11924);
    SpriteSystem_LoadCellResObjFromOpenNarc(v2, v3, v0, v6, FALSE, 11924);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v2, v3, v0, v7, FALSE, 11924);
}

void VsRecorderViewerMenu_FreeCursorSpriteResources(VsRecorderState *param0)
{
    SpriteManager_UnloadCharObjById(param0->menuContext.spriteManager, 11924);
    SpriteManager_UnloadCellObjById(param0->menuContext.spriteManager, 11924);
    SpriteManager_UnloadAnimObjById(param0->menuContext.spriteManager, 11924);
}

ManagedSprite *VsRecorderViewerMenu_CreateCursorSprite(VsRecorderState *param0, int param1)
{
    ManagedSprite *v0;
    SpriteTemplate v1;

    v1.x = 128;
    v1.y = 96;
    v1.z = 0;
    v1.animIdx = 0;
    v1.priority = 1;
    v1.plttIdx = 0;
    v1.vramType = param1;
    v1.bgPriority = 3;
    v1.vramTransfer = FALSE;
    v1.resources[4] = SPRITE_RESOURCE_NONE;
    v1.resources[5] = SPRITE_RESOURCE_NONE;
    v1.resources[0] = 11924;
    v1.resources[2] = 11924;
    v1.resources[3] = 11924;

    if (param1 == NNS_G2D_VRAM_TYPE_2DMAIN) {
        v1.resources[1] = 9999;
    } else {
        v1.resources[1] = 10000;
    }

    v0 = SpriteSystem_NewSprite(param0->menuContext.spriteSystem, param0->menuContext.spriteManager, &v1);

    ManagedSprite_SetExplicitPalette(v0, 2);
    ManagedSprite_SetAnim(v0, 0);
    ManagedSprite_TickFrame(v0);

    return v0;
}

void VsRecorderViewerMenu_HideAndFreeMenu(VsRecorderState *param0)
{
    VsRecorderViewerMenu_SetMenuEntriesVisible(param0, 0);
    VsRecorderViewerMenu_FreeMenuEntries(param0);
    VsRecorderViewerMenu_FreeEntryIconResources(param0);
}

void VsRecorderViewerMenu_InitMenu(VsRecorderState *param0)
{
    VsRecorderViewerMenu_LoadEntryIconResources(param0);
    VsRecorderViewerMain_ReturnToParentMenu(param0);
    VsRecorderGraphics_CountEnabledEntries(param0);
    VsRecorderViewerMenu_CreateMenuEntries(param0);
    VsRecorderViewerMenu_SetMenuEntriesVisible(param0, 1);
    VsRecorderViewerMenu_UpdateSubEntryLabels(param0);
    VsRecorderViewerMenu_AttachEntryLabelSprites(param0);
    VsRecorderViewerMenu_PositionMenuEntries(param0);
    VsRecorderViewerMenu_UpdateMainEntryLabels(param0);
}

void VsRecorderViewerMenu_InitMenuWithExtraEntry(VsRecorderState *param0)
{
    VsRecorderViewerMenu_LoadEntryIconResources(param0);
    VsRecorderViewerMain_ReturnToParentMenu(param0);
    VsRecorderGraphics_CountEnabledEntries(param0);
    VsRecorderViewerMenu_CreateMenuEntries(param0);
    VsRecorderViewerMenu_SetMenuEntriesVisible(param0, 1);
    VsRecorderViewerMenu_UpdateSubEntryLabels(param0);
    VsRecorderViewerMenu_AttachEntryLabelSprites(param0);
    VsRecorderViewerMenu_PositionMenuEntries(param0);
    VsRecorderViewerMenu_UpdateMainEntryLabels(param0);

    param0->menu.mainEntryCount += 1;
}

void VsRecorderViewerMenu_SetBlendAlpha(int *param0, int *param1, int param2, int param3, int param4, int param5, int param6)
{
    *param0 = 0;
    *param1 = 31;

    if (param6 == 0) {
        G2_SetBlendAlpha(param2, param3, *param0, *param1);
        G2S_SetBlendAlpha(param4, param5, *param0, *param1);
    }

    if (param6 == 1) {
        G2_SetBlendAlpha(param2, param3, *param0, *param1);
    }

    if (param6 == 2) {
        G2S_SetBlendAlpha(param4, param5, *param0, *param1);
    }
}

void VsRecorderViewerMenu_UpdateBlendAlpha(int *param0, int *param1, int param2, int param3, int param4, int param5, int param6)
{
    if (param6 == 0) {
        G2_SetBlendAlpha(param2, param3, *param0, *param1);
        G2S_SetBlendAlpha(param4, param5, *param0, *param1);
    }

    if (param6 == 1) {
        G2_SetBlendAlpha(param2, param3, *param0, *param1);
    }

    if (param6 == 2) {
        G2S_SetBlendAlpha(param4, param5, *param0, *param1);
    }
}

void VsRecorderViewerMenu_SetDefaultBlendAlpha(int *param0, int *param1, int param2)
{
    VsRecorderViewerMenu_SetBlendAlpha(param0, param1, (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), (GX_BLEND_PLANEMASK_BG3), (GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ), param2);
}

BOOL VsRecorderViewerMenu_StepBlendAlpha(int *param0, int *param1, int param2, int param3)
{
    BOOL v0 = 1;

    if (param2 == 0) {
        if (*param0 < 8) {
            *param0 += 1;
            v0 = 0;
        }
        if (*param1 > 7) {
            *param1 -= 3;
            v0 = 0;
        }
    } else {
        if (*param0 > 0) {
            *param0 -= 1;
            v0 = 0;
        }
        if (*param1 < 31) {
            *param1 += 3;
            v0 = 0;
        }
    }

    if (param3 == 0) {
        G2_ChangeBlendAlpha(*param0, *param1);
        G2S_ChangeBlendAlpha(*param0, *param1);
    }

    if (param3 == 1) {
        G2_ChangeBlendAlpha(*param0, *param1);
    }

    if (param3 == 2) {
        G2S_ChangeBlendAlpha(*param0, *param1);
    }

    return v0;
}

BOOL VsRecorderViewerMenu_StepFadeValue(int *param0, int param1)
{
    BOOL v0 = 1;

    if (param1 == 1) {
        if (*param0 < 16) {
            *param0 += 2;
            v0 = 0;
        }
    } else {
        if (*param0 > 0) {
            *param0 -= 2;
            v0 = 0;
        }
    }

    return v0;
}

void VsRecorderViewerMenu_ResetFadeValue(int *param0)
{
    *param0 = 16;
}
