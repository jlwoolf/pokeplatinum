#include "vs_recorder_viewer/vs_recorder_viewer.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/dress_up_photo.h"
#include "struct_defs/struct_0208B284.h"
#include "struct_defs/struct_vs_recorder_viewer_state.h"

#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_0224112C.h"
#include "vs_recorder_viewer/vs_recorder_viewer_const_funcptr_tables.h"

#include "bg_window.h"
#include "g3d_pipeline.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "palette.h"
#include "pokemon_sprite.h"
#include "render_text.h"
#include "savedata_misc.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "sprite_util.h"
#include "sys_task.h"
#include "system.h"
#include "touch_pad.h"
#include "touch_screen_actions.h"
#include "font_oam.h"
#include "g3_buffer.h"
#include "image_clips.h"
#include "vs_recorder_ring.h"
#include "vs_recorder.h"
#include "vs_recorder_graphics.h"
#include "vram_transfer.h"

static void VsRecorderViewerMain_InitGraphics(BgConfig *param0);
static void VsRecorderViewerMain_InitSpriteSystem(VsRecorderViewerState *param0);

void VsRecorderViewerMain_Init(VsRecorderViewerState *param0)
{
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();
    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);
    VramTransfer_New(4, HEAP_ID_102);

    param0->unk_14.unk_00 = NARC_ctor(NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, HEAP_ID_102);
    param0->unk_14.unk_10 = BgConfig_New(HEAP_ID_102);
    param0->unk_14.unk_14 = PaletteData_New(HEAP_ID_102);
    param0->unk_14.unk_4C = G3DPipeline_Init(HEAP_ID_102, TEXTURE_VRAM_SIZE_128K, PALETTE_VRAM_SIZE_64K, NULL);
    param0->unk_14.unk_50 = PokemonSpriteManager_New(HEAP_ID_102);

    NNS_G2dSetupSoftwareSpriteCamera();

    PaletteData_SetAutoTransparent(param0->unk_14.unk_14, TRUE);
    PaletteData_AllocBuffer(param0->unk_14.unk_14, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_102);
    PaletteData_AllocBuffer(param0->unk_14.unk_14, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_102);
    PaletteData_AllocBuffer(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_102);
    PaletteData_AllocBuffer(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_102);
    VsRecorderViewerMain_InitGraphics(param0->unk_14.unk_10);
    VsRecorderViewerMain_InitSpriteSystem(param0);

    {
        EnableTouchPad();
        InitializeTouchPad(4);

        param0->unk_14.unk_30 = 1;

        VsRecorderViewerMain_InitTouchScreenActions(param0);
        RenderControlFlags_SetSpeedUpOnTouch(TRUE);
    }

    SetVBlankCallback(VsRecorderViewerMain_VBlankCallback, param0);

    if (param0->unk_00 != 0) {
        VsRecorderViewerTransfer_Init(param0);
        ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_128K);
        ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);
        ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DSUB, GX_OBJVRAMMODE_CHAR_1D_128K);
        ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DSUB);
        NetworkIcon_Init();
        NetworkIcon_CreateOnSubScreen(1, HEAP_ID_102);

        {
            NNSG2dPaletteData *v0;
            void *v1 = NetworkIcon_GetPalette(HEAP_ID_102);

            NNS_G2dGetUnpackedPaletteData(v1, &v0);
            PaletteData_LoadBuffer(param0->unk_14.unk_14, v0->pRawData, PLTTBUF_MAIN_OBJ, PLTT_DEST(14), PALETTE_SIZE_BYTES);
            PaletteData_LoadBuffer(param0->unk_14.unk_14, v0->pRawData, PLTTBUF_SUB_OBJ, PLTT_DEST(14), PALETTE_SIZE_BYTES);
            Heap_Free(v1);
        }
    }

    {
        VsRecorderRingConfig v2;

        v2.count = 12;
        v2.heapID = HEAP_ID_102;
        v2.vramType = 1;
        v2.mode = param0->unk_00;
        v2.subscreenOffset = (256 * FX32_ONE);

        param0->unk_6F0 = VsRecorderRing_New(v2, param0->unk_14.unk_04, param0->unk_14.unk_08, param0->unk_14.unk_14);
        VsRecorderRing_Init(param0->unk_6F0, param0->unk_14.unk_48);
        VsRecorderRing_SetActive(param0->unk_6F0, 0);
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);

        v2.vramType = 2;
        v2.subscreenOffset = (256 * FX32_ONE);

        param0->unk_6F4 = VsRecorderRing_New(v2, param0->unk_14.unk_04, param0->unk_14.unk_08, param0->unk_14.unk_14);
        VsRecorderRing_Init(param0->unk_6F4, param0->unk_14.unk_48);
        VsRecorderRing_SetActive(param0->unk_6F4, 0);
        VsRecorderRing_SetVisible(param0->unk_6F4, 0);
    }

    {
        param0->unk_14.unk_3C = FontOAMManager_New((5 * 2) + 10, HEAP_ID_102);
        param0->unk_14.unk_34 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0010, HEAP_ID_102);
        param0->unk_14.unk_38 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0020, HEAP_ID_102);
    }

    VsRecorderViewerList_LoadBattleRecordings(param0);
    VsRecorderGraphics_CountEnabledEntries(param0);
    VsRecorderViewerMenu_LoadBackground(param0);
    VsRecorderViewerList_StartDrawTask(param0);
}

void VsRecorderViewerMain_Free(VsRecorderViewerState *param0)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
    Bg_FreeTilemapBuffer(param0->unk_14.unk_10, 0);
    Bg_FreeTilemapBuffer(param0->unk_14.unk_10, 1);
    Bg_FreeTilemapBuffer(param0->unk_14.unk_10, 2);
    Bg_FreeTilemapBuffer(param0->unk_14.unk_10, 3);
    Bg_FreeTilemapBuffer(param0->unk_14.unk_10, 4);
    Bg_FreeTilemapBuffer(param0->unk_14.unk_10, 5);
    Bg_FreeTilemapBuffer(param0->unk_14.unk_10, 6);
    Bg_FreeTilemapBuffer(param0->unk_14.unk_10, 7);
    Heap_Free(param0->unk_14.unk_10);
    PaletteData_FreeBuffer(param0->unk_14.unk_14, PLTTBUF_MAIN_BG);
    PaletteData_FreeBuffer(param0->unk_14.unk_14, PLTTBUF_SUB_BG);
    PaletteData_FreeBuffer(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ);
    PaletteData_FreeBuffer(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ);
    PaletteData_Free(param0->unk_14.unk_14);

    if (param0->unk_00 == 0) {
        MiscSaveBlock *v0 = SaveData_MiscSaveBlock(param0->saveData);
        MiscSaveBlock_SetVsRecorderColor(v0, param0->unk_14.unk_48);
    }

    NARC_dtor(param0->unk_14.unk_00);
    SysTask_Done(param0->unk_41E8);
    SpriteSystem_FreeResourcesAndManager(param0->unk_14.unk_04, param0->unk_14.unk_08);
    SpriteSystem_Free(param0->unk_14.unk_04);
    NetworkIcon_Destroy();

    {
        u32 v1;
        v1 = DisableTouchPad();

        TouchScreenActions_Free(param0->unk_14.unk_18);
        RenderControlFlags_SetSpeedUpOnTouch(FALSE);
    }

    {
        int v2;

        for (v2 = 0; v2 < 4; v2++) {
            if (param0->unk_87C[v2] != NULL) {
                Heap_Free(param0->unk_87C[v2]);
            }

            if (param0->unk_88C[v2] != NULL) {
                Heap_Free(param0->unk_88C[v2]);
            }
        }
    }

    {
        FontOAMManager_Free(param0->unk_14.unk_3C);
        MessageLoader_Free(param0->unk_14.unk_34);
        MessageLoader_Free(param0->unk_14.unk_38);
    }

    G3DPipelineBuffers_Free(param0->unk_14.unk_4C);
    PokemonSpriteManager_Free(param0->unk_14.unk_50);

    VsRecorderViewerTransfer_Free(param0);

    SetVBlankCallback(NULL, NULL);
    VramTransfer_Free();
}

static const BgTemplate sVsRecorderViewerMainBgTemplates[] = {
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
        .priority = 0x1,
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
        .screenBase = GX_BG_SCRBASE_0x2800,
        .charBase = GX_BG_CHARBASE_0x14000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x3,
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
        .screenBase = GX_BG_SCRBASE_0x3000,
        .charBase = GX_BG_CHARBASE_0x18000,
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
        .screenBase = GX_BG_SCRBASE_0x3800,
        .charBase = GX_BG_CHARBASE_0x1c000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x1,
        .areaOver = 0x0,
        .mosaic = FALSE,
    }
};

static const BgTemplate sVsRecorderViewerMainSubBgTemplates[] = {
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xc000,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x1,
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
        .screenBase = GX_BG_SCRBASE_0xc800,
        .charBase = GX_BG_CHARBASE_0x04000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x3,
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
        .screenBase = GX_BG_SCRBASE_0xd000,
        .charBase = GX_BG_CHARBASE_0x08000,
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
        .screenBase = GX_BG_SCRBASE_0xd800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x1,
        .areaOver = 0x0,
        .mosaic = FALSE,
    }
};

static void VsRecorderViewerMain_InitGraphics(BgConfig *param0)
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
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_0, &sVsRecorderViewerMainBgTemplates[0], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_1, &sVsRecorderViewerMainBgTemplates[1], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_2, &sVsRecorderViewerMainBgTemplates[2], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_3, &sVsRecorderViewerMainBgTemplates[3], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_1);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_2);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_3);
    }

    {
        Bg_InitFromTemplate(param0, BG_LAYER_SUB_0, &sVsRecorderViewerMainSubBgTemplates[0], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_SUB_1, &sVsRecorderViewerMainSubBgTemplates[1], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_SUB_2, &sVsRecorderViewerMainSubBgTemplates[2], 0);
        Bg_InitFromTemplate(param0, BG_LAYER_SUB_3, &sVsRecorderViewerMainSubBgTemplates[3], 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_1);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_2);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_3);
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);

    VsRecorderViewerMain_SetWhichScreenIs3D(1);

    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, 7, 8);
    G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, 7, 8);
}

void VsRecorderViewerMain_SetWhichScreenIs3D(int param0)
{
    gSystem.whichScreenIs3D = param0;
    GXLayers_SwapDisplay();
}

void VsRecorderViewerMain_InitBg2(VsRecorderViewerState *param0)
{
    Bg_InitFromTemplate(param0->unk_14.unk_10, 2, &sVsRecorderViewerMainBgTemplates[2], 0);
}

static void VsRecorderViewerMain_InitSpriteSystem(VsRecorderViewerState *param0)
{
    param0->unk_14.unk_04 = SpriteSystem_Alloc(HEAP_ID_102);
    {
        const RenderOamTemplate v0 = {
            0,
            128,
            0,
            32,
            4,
            124,
            0,
            32,
        };

        const CharTransferTemplateWithModes v1 = {
            128, 0x10000, 0x4000, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_128K
        };

        SpriteSystem_Init(param0->unk_14.unk_04, &v0, &v1, 16 + 16);
    }

    {
        BOOL v2;
        const SpriteResourceCapacities v3 = {
            128,
            32,
            128,
            128,
            16,
            16,
        };

        param0->unk_14.unk_08 = SpriteManager_New(param0->unk_14.unk_04);

        v2 = SpriteSystem_InitSprites(param0->unk_14.unk_04, param0->unk_14.unk_08, 64 + 64 + 64);
        GF_ASSERT(v2);

        v2 = SpriteSystem_InitManagerWithCapacities(param0->unk_14.unk_04, param0->unk_14.unk_08, &v3);
        GF_ASSERT(v2);
    }

    SetSubScreenViewRect(SpriteSystem_GetRenderer(param0->unk_14.unk_04), 0, 256 * FX32_ONE);
}

void VsRecorderViewerMain_VBlankCallback(void *param0)
{
    VsRecorderViewerState *v0 = param0;

    VramTransfer_Process();
    PaletteData_CommitFadedBuffers(v0->unk_14.unk_14);
    Bg_RunScheduledUpdates(v0->unk_14.unk_10);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

BOOL VsRecorderViewerMain_Update(VsRecorderViewerState *param0, int *param1)
{
    BOOL v0 = 0;

    switch (*param1) {
    case 0:
        v0 = sVsRecorderViewerEntryHandlers[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 1, v0, param1);

        if (v0) {
            if (param0->unk_14.unk_30 == 1) {
                VsRecorderViewerMain_SetState(param0, 0);
            } else {
                VsRecorderViewerMain_SetState(param0, 1);
            }
        }
        break;
    case 1:
        v0 = sVsRecorderViewerSlideShowStateTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 2:
        v0 = sVsRecorderViewerBattleVideoStateTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 3:
        v0 = sVsRecorderViewerFrontierPrintStateTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 4:
        v0 = sVsRecorderViewerProfilePhotoModeTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 5:
        v0 = sVsRecorderViewerProfileBrowserModeTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 6:
        v0 = sVsRecorderViewerBoxStateTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 7:
        v0 = sVsRecorderViewerBoxListStateTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 8:
    case 9:
        v0 = sVsRecorderViewerRankingsStateTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 10:
    case 11:
        v0 = sVsRecorderViewerRankingStateTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 12:
        v0 = sVsRecorderViewerRankingStateTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 13:
        v0 = sVsRecorderViewerRecord_MainStateTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 14:
        v0 = sVsRecorderViewerRecord_ProfileStateTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 15:
        v0 = sVsRecorderViewerRecord_RingStateTable[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 16:
        VsRecorderViewerMain_AdvanceState(param0, 255, 1, param1);
        break;
    case 17:
        v0 = sVsRecorderViewerSubMenuStateFuncs[param0->unk_04](param0);
        VsRecorderViewerMain_AdvanceState(param0, 16, v0, param1);
        break;
    case 18:
        VsRecorderViewerList_UpdateMessage(param0);
        break;
    default:
        return 1;
    }

    G3_ResetG3X();
    PokemonSpriteManager_DrawSprites(param0->unk_14.unk_50);
    G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);

    VsRecorderViewerTransfer_Main(param0);

    return 0;
}

void VsRecorderViewerMain_AdvanceState(VsRecorderViewerState *param0, int param1, BOOL param2, int *param3)
{
    if (param2) {
        (*param3) = param1;
        VsRecorderViewerMain_SetState(param0, 0);
        VsRecorderViewerMain_SetSubState(param0, 0);
    }
}

void VsRecorderViewerMain_SetState(VsRecorderViewerState *param0, int param1)
{
    param0->unk_04 = param1;
    param0->unk_08 = 0;
    param0->unk_0C = 0;
}

void VsRecorderViewerMain_SetSubState(VsRecorderViewerState *param0, int param1)
{
    param0->unk_08 = param1;
    param0->unk_0C = 0;
}

void VsRecorderViewerMain_RefreshMenu(VsRecorderViewerState *param0)
{
    VsRecorderGraphics_CountEnabledEntries(param0);
    VsRecorderViewerMenu_UpdateSubEntryLabels(param0);

    param0->unk_534.unk_1B0 = 0;
}

BOOL VsRecorderViewerMain_PushMenu(VsRecorderViewerState *param0)
{
    param0->unk_81C[param0->unk_534.unk_1A4] = param0->unk_818;
    param0->unk_534.unk_190[param0->unk_534.unk_1A4] = &param0->unk_818[param0->unk_534.unk_1B0];
    param0->unk_818 = param0->unk_818[param0->unk_534.unk_1B0].children;
    param0->unk_534.unk_1A4++;
    param0->unk_534.unk_1B0 = 0;

    if (param0->unk_818 == NULL) {
        return 0;
    }

    VsRecorderViewerMain_RefreshMenu(param0);

    return 1;
}

BOOL VsRecorderViewerMain_PopMenu(VsRecorderViewerState *param0)
{
    param0->unk_818 = param0->unk_81C[param0->unk_534.unk_1A4];

    VsRecorderViewerMain_RefreshMenu(param0);

    return 1;
}

void VsRecorderViewerMain_ExecuteMenuAction(VsRecorderViewerState *param0)
{
    int v0 = param0->unk_818[param0->unk_534.unk_1B0].action;

    switch (v0) {
    case 0:
    case 1:
    case 3:
    case 6:
        break;
    case 2:
        VsRecorder_SetPlaybackRequest(param0->unk_868, 0, 0);
        VsRecorderViewerMain_SetState(param0, 2);
        break;
    case 4:
        VsRecorderViewerMain_AdvanceState(param0, 2, 1, param0->unk_10);
        break;
    case 5:
        VsRecorderViewerMain_AdvanceState(param0, 3, 1, param0->unk_10);
        break;
    case 8:
        VsRecorderViewerMain_AdvanceState(param0, 4, 1, param0->unk_10);
        break;
    case 9:
        VsRecorderViewerMain_AdvanceState(param0, 5, 1, param0->unk_10);
        break;
    case 10:
        VsRecorderViewerMain_AdvanceState(param0, 6, 1, param0->unk_10);
        break;
    case 11:
        VsRecorderViewerMain_AdvanceState(param0, 7, 1, param0->unk_10);
        break;
    case 12:
        VsRecorderViewerMain_AdvanceState(param0, 8, 1, param0->unk_10);
        break;
    case 13:
        VsRecorderViewerMain_AdvanceState(param0, 9, 1, param0->unk_10);
        break;
    case 14:
        VsRecorderViewerMain_AdvanceState(param0, 10, 1, param0->unk_10);
        break;
    case 15:
        VsRecorderViewerMain_AdvanceState(param0, 11, 1, param0->unk_10);
        break;
    case 16:
        VsRecorderViewerMain_AdvanceState(param0, 12, 1, param0->unk_10);
        break;
    case 17:
        VsRecorderViewerMain_AdvanceState(param0, 13, 1, param0->unk_10);
        break;
    case 18:
        VsRecorderViewerMain_AdvanceState(param0, 14, 1, param0->unk_10);
        break;
    case 19:
        VsRecorderViewerMain_AdvanceState(param0, 15, 1, param0->unk_10);
        break;
    case 7:
        VsRecorderViewerMain_AdvanceState(param0, 17, 1, param0->unk_10);
        break;
    }
}

BOOL VsRecorderViewerMain_CanExecuteAction(VsRecorderViewerState *param0)
{
    int v0 = param0->unk_818[param0->unk_534.unk_1B0].dataIndex;
    BOOL v1 = 1;

    switch (param0->unk_00) {
    default:
        if ((v0 == 0) || (v0 == 1) || (v0 == 2) || (v0 == 3)) {
            if (param0->unk_87C[v0] == NULL) {
                VsRecorderViewerList_OpenSubMessage(param0, 269);
                v1 = 0;
            }
        }
        break;
    case 5:
        if (v0 == 0) {
            DressUpPhoto *photo = ImageClips_GetDressUpPhoto(SaveData_GetImageClips(param0->saveData), v0);
            v1 = DressUpPhoto_HasData(photo);

            if (v1 == FALSE) {
                VsRecorderViewerList_OpenSubMessage(param0, 290);
            }
        }
        break;
    case 6:
        if (v0 == 100) {
            if (VsRecorderViewerList_IsRecordTransferDone(param0)) {
                VsRecorderViewerList_OpenSubMessage(param0, 273);
                v1 = 0;
            }
        }
        break;
    case 2:
        if (v0 == 9999) {
            if (param0->unk_87C[0] == NULL) {
                VsRecorderViewerList_OpenSubMessage(param0, 129);
                v1 = 0;
            }
        }
        break;
    case 4:
    case 3:
        break;
    }

    if (v1 == 0) {
        Sound_PlayEffect(SEQ_SE_PL_BREC58_sseq);
    } else {
        Sound_PlayEffect(SEQ_SE_PL_BREC57_sseq);
    }

    return v1;
}

static void VsRecorderViewerMain_TouchHandler(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderViewerState *v0 = param2;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    v0->unk_534.unk_1B0 = param0;

    {
        BOOL v1 = VsRecorderViewerMain_CanExecuteAction(v0);

        if (v1 == 0) {
            return;
        }
    }

    if ((param0 >= 0) && (param0 <= 4)) {
        s16 v2, v3;

        VsRecorderViewerMenu_GetSpritePositionWithOffset(v0->unk_534.unk_C8[param0].unk_00, &v2, &v3);
        VsRecorderRing_SetPosition(v0->unk_6F0, v2 + (15 + 1), v3);
        VsRecorderRing_SetTargetPosition(v0->unk_6F0, v2 + (15 + 1), v3);

        v0->unk_86C = v0->unk_818[v0->unk_534.unk_1B0].dataIndex;
        VsRecorderViewerMain_SetState(v0, v0->unk_818[v0->unk_534.unk_1B0].nextState);

        if (v0->unk_818[v0->unk_534.unk_1B0].nextState == 2) {
            VsRecorder_SetPlaybackRequest(v0->unk_868, 0, 0);
        } else {
            VsRecorderViewerMain_ClearTouchRects(v0);
            VsRecorderRing_SetVisible(v0->unk_6F0, 1);
        }

        if (v0->unk_86C == 999) {
            VsRecorderViewerList_OpenSubMessageWithBlend(v0, 193);
        } else if (v0->unk_86C == 9999) {
            VsRecorderViewerList_OpenSubMessageWithBlend(v0, 301);
        } else {
            if (v0->unk_89C) {
                VsRecorderViewerList_CloseSubMessage(v0);
                v0->unk_89C = 0;
            }
        }
    }
}

void VsRecorderViewerMain_InitTouchScreenActions(VsRecorderViewerState *param0)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        param0->unk_534.unk_C8[v0].unk_10 = &param0->unk_14.unk_1C[v0];
    }

    param0->unk_14.unk_18 = TouchScreenActions_RegisterHandler(param0->unk_14.unk_1C, 5, VsRecorderViewerMain_TouchHandler, param0, HEAP_ID_102);
}

void VsRecorderViewerMain_UpdateTouchRects(VsRecorderViewerState *param0)
{
    int v0;
    s16 v1, v2;

    if (param0->unk_818 == NULL) {
        return;
    }

    for (v0 = 0; v0 < 5; v0++) {
        if (param0->unk_818[v0].enabled == 0) {
            param0->unk_534.unk_C8[v0].unk_10->rect.top = 0;
            param0->unk_534.unk_C8[v0].unk_10->rect.bottom = 0;
            param0->unk_534.unk_C8[v0].unk_10->rect.left = 0;
            param0->unk_534.unk_C8[v0].unk_10->rect.right = 0;
            continue;
        }

        ManagedSprite_GetPositionXY(param0->unk_534.unk_C8[v0].unk_00, &v1, &v2);

        param0->unk_534.unk_C8[v0].unk_10->rect.top = v2 - 16;
        param0->unk_534.unk_C8[v0].unk_10->rect.bottom = v2 + 16;
        param0->unk_534.unk_C8[v0].unk_10->rect.left = v1 - 0;
        param0->unk_534.unk_C8[v0].unk_10->rect.right = v1 + 160;
    }
}

void VsRecorderViewerMain_ClearTouchRects(VsRecorderViewerState *param0)
{
    int v0;
    s16 v1, v2;

    for (v0 = 0; v0 < 5; v0++) {
        ManagedSprite_GetPositionXY(param0->unk_534.unk_C8[v0].unk_00, &v1, &v2);
        param0->unk_534.unk_C8[v0].unk_10->rect.top = 0;
        param0->unk_534.unk_C8[v0].unk_10->rect.bottom = 0;
        param0->unk_534.unk_C8[v0].unk_10->rect.left = 0;
        param0->unk_534.unk_C8[v0].unk_10->rect.right = 0;
    }
}

void VsRecorderViewerMain_HandleTouchAction(VsRecorderViewerState *param0)
{
    TouchScreenActions_HandleAction(param0->unk_14.unk_18);
}

void VsRecorderViewerMain_ReturnToParentMenu(VsRecorderViewerState *param0)
{
    if (param0->unk_534.unk_1A4 > 0) {
        param0->unk_534.unk_1A4--;
    } else {
        if (param0->unk_534.unk_1A4 != 0) {
            param0->unk_534.unk_1A4 = 0;
            GF_ASSERT(FALSE);
        }
    }

    param0->unk_818 = param0->unk_81C[param0->unk_534.unk_1A4];
}

void VsRecorderViewerMain_ResetSelection(VsRecorderViewerState *param0)
{
    param0->unk_838.unk_00 = 0;
    param0->unk_838.unk_04 = 0xFF;

    {
        int v0;

        for (v0 = 0; v0 < 8; v0++) {
            param0->unk_838.unk_08[v0] = 0;
        }
    }
}

BOOL VsRecorderViewerMain_HasPendingSelection(VsRecorderViewerState *param0)
{
    return param0->unk_838.unk_00;
}

void VsRecorderViewerMain_SetPendingSelection(VsRecorderViewerState *param0, int param1)
{
    param0->unk_838.unk_00 = 1;
    param0->unk_838.unk_04 = param1;
}
