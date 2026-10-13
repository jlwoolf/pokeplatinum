#include "frontier_facilities/frontier_graphics.h"

#include <nitro.h>

#include "constants/field_base_tiles.h"
#include "constants/graphics.h"

#include "struct_decls/battle_frontier_decl.h"

#include "global/utility.h"
#include "wifi_2d_char/wifi_2d_char_0222BCE8.h"
#include "wifi_2d_char/wifi_2d_char_0222BE18.h"
#include "wifi_2d_char/wifi_2d_char_0222CA88.h"
#include "wifi_2d_char/wifi_2d_char_0222CCE4.h"
#include "wifi_2d_char/wifi_2d_char_0222D160.h"
#include "wifi_2d_char/wifi_2d_char_0222D1C0.h"
#include "wifi_2d_char/wifi_2d_char_0222D77C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CCB8.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CE44.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D894.h"
#include "wifi_2d_char/union_wifi_2d_char_0222BDAC.h"
#include "wifi_menu_app/struct_wifi_menu_app_0223582C.h"
#include "wifi_menu_app/struct_wifi_menu_app_022376D0.h"
#include "frontier_facilities/frontier_opponents.h"
#include "frontier_facilities/frontier_particle_system.h"
#include "frontier_facilities/frontier_scenes.h"
#include "frontier_facilities/frontier_facilities_0223D768.h"
#include "frontier_facilities/struct_frontier_facilities_02230BE4.h"
#include "frontier_facilities/struct_frontier_facilities_0223C634.h"
#include "frontier_facilities/struct_frontier_facilities_0223C688.h"
#include "frontier_facilities/struct_frontier_facilities_0223D3B0.h"
#include "frontier_facilities/struct_frontier_facilities_0223D3B0_1.h"
#include "frontier_facilities/struct_frontier_facilities_0223D570.h"

#include "battle_frontier.h"
#include "bg_window.h"
#include "g3d_pipeline.h"
#include "game_options.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "narc.h"
#include "network_icon.h"
#include "palette.h"
#include "render_text.h"
#include "render_window.h"
#include "save_player.h"
#include "sound.h"
#include "sprite_system.h"
#include "sprite_util.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "touch_pad.h"
#include "trainer_info.h"
#include "g3_buffer.h"
#include "vram_transfer.h"

#include "res/fonts/pl_font.naix"
#include "res/graphics/frontier/backgrounds/frontier_backgrounds.naix"

static void VBlankCallback(void *data);
static void DummyExecuteOnVBlank(SysTask *task, void *data);
static void FrontierFacilities_MainRenderTask(SysTask *param0, void *param1);
static void FrontierFacilities_UpdateObjectManagerTask(SysTask *param0, void *param1);
static void FrontierFacilities_ProcessMoveQueuesTask(SysTask *param0, void *param1);
static void InitBackgrounds(BgConfig *bgConfig, int sceneID);
static void FrontierFacilities_InitObjectSystem(FrontierGraphics *param0, int sceneID, const TrainerInfo *playerInfo);
static void FrontierFacilities_FreeObjectSystem(FrontierGraphics *param0);
static void LoadMessageBoxAndWindowGraphics(FrontierGraphics *graphics);
static void InitSpriteSystem(FrontierGraphics *graphics);
static void FreeSpriteSystem(FrontierGraphics *graphics);
static void FrontierFacilities_ProcessMoveQueues(FrontierGraphics *param0);
static void LoadSubScreenBackground(FrontierGraphics *graphics);
static G3DPipelineBuffers *InitG3DPipeline(enum HeapID heapID);
static void G3DPipelineCallback(void);
static void FreeG3DPipeline(G3DPipelineBuffers *g3dPipeline);
static void FrontierFacilities_SaveSpriteState(FrontierGraphics *param0);
static void FrontierFacilities_LoadSpriteState(FrontierGraphics *param0);
static void FrontierFacilities_CopyObjectParams(FrontierObject *param0, FrontierObjectParams *param1);
static void FrontierFacilities_SetObject(BattleFrontier *param0, int param1, WiFi2DCharObject *param2, WiFi2DCharRenderObject *param3, const FrontierObjectParams *param4);
static void FrontierFacilities_UpdateBackground(FrontierGraphics *param0);
static void FrontierFacilities_UpdateBackgroundScroll(FrontierGraphics *param0);

static const RenderOamTemplate sOamTemplate = {
    .mainOamStart = 0,
    .mainOamCount = 128,
    .mainAffineOamStart = 0,
    .mainAffineOamCount = 32,
    .subOamStart = 0,
    .subOamCount = 128,
    .subAffineOamStart = 0,
    .subAffineOamCount = 32
};

static const CharTransferTemplateWithModes sTransferTemplate = {
    .maxTasks = 0x60,
    .sizeMain = 0x10000,
    .sizeSub = 0x4000,
    .modeMain = GX_OBJVRAMMODE_CHAR_1D_128K,
    .modeSub = GX_OBJVRAMMODE_CHAR_1D_32K
};

static const SpriteResourceCapacities sCapacities = {
    .asStruct = {
        .charCapacity = 96,
        .plttCapacity = 32,
        .cellCapacity = 64,
        .animCapacity = 64,
        .mcellCapacity = 8,
        .manimCapacity = 8,
    }
};

static const WiFi2DCharTile sEmptyGridTiles[256] = { 0 };

FrontierGraphics *FrontierGraphics_New(BattleFrontier *frontier)
{
    FrontierGraphics *graphics;
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(frontier);
    const TrainerInfo *playerInfo = SaveData_GetTrainerInfo(fieldData->saveData);
    int sceneID = fieldData->sceneID;

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

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_94, 0x90000);

    graphics = Heap_Alloc(HEAP_ID_94, sizeof(FrontierGraphics));
    MI_CpuClear8(graphics, sizeof(FrontierGraphics));

    graphics->frontier = frontier;
    graphics->sceneID = sceneID;

    for (int i = 0; i < 8; i++) {
        graphics->spriteSlots.loadedResourceIDs[i] = 0xffff;
    }

    graphics->g3dPipeline = InitG3DPipeline(HEAP_ID_94);
    graphics->plttData = PaletteData_New(HEAP_ID_94);

    PaletteData_SetAutoTransparent(graphics->plttData, TRUE);
    PaletteData_AllocBuffer(graphics->plttData, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_94);
    PaletteData_AllocBuffer(graphics->plttData, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_94);
    PaletteData_AllocBuffer(graphics->plttData, PLTTBUF_MAIN_OBJ, PALETTE_SIZE_BYTES * 16 - 64, HEAP_ID_94);
    PaletteData_AllocBuffer(graphics->plttData, PLTTBUF_SUB_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_94);

    graphics->bgConfig = BgConfig_New(HEAP_ID_94);

    VramTransfer_New(64, HEAP_ID_94);
    SetAutorepeat(4, 8);

    InitBackgrounds(graphics->bgConfig, sceneID);
    LoadMessageBoxAndWindowGraphics(graphics);
    LoadSubScreenBackground(graphics);

    EnableTouchPad();
    InitializeTouchPad(4);

    InitSpriteSystem(graphics);

    graphics->particleSys = FrontierParticleSystem_New(HEAP_ID_94);

    FrontierFacilities_InitObjectSystem(graphics, sceneID, playerInfo);

    graphics->objectManagerTask = SysTask_Start(FrontierFacilities_UpdateObjectManagerTask, graphics, 60000);
    graphics->moveQueuesTask = SysTask_Start(FrontierFacilities_ProcessMoveQueuesTask, graphics, 61000);
    graphics->renderTask = SysTask_Start(FrontierFacilities_MainRenderTask, graphics, 80000);

    GXLayers_TurnBothDispOn();
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, TRUE);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, TRUE);
    Sound_SetSceneAndPlayBGM(SOUND_SCENE_FIELD, FrontierScene_GetParam(sceneID, FR_SCENE_BGM_ID), 1);

    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_ENABLED);
    RenderControlFlags_SetCanABSpeedUpPrint(FALSE);
    RenderControlFlags_SetSpeedUpOnTouch(FALSE);

    SetVBlankCallback(VBlankCallback, graphics);
    graphics->dummyExecuteOnVBlank = SysTask_ExecuteOnVBlank(DummyExecuteOnVBlank, graphics, 10);
    FrontierScene_CallSetupFunc(graphics, &graphics->sceneData, graphics->sceneID);
    NetworkIcon_Init();

    return graphics;
}

void FrontierGraphics_Free(FrontierGraphics *graphics)
{
    UNUSED(BattleFrontier_GetFieldData(graphics->frontier));
    FrontierScene_CallDestroyFunc(graphics, &graphics->sceneData, graphics->sceneID);

    FrontierFacilities_FreeObjectSystem(graphics);

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    Bg_FreeTilemapBuffer(graphics->bgConfig, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(graphics->bgConfig, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(graphics->bgConfig, BG_LAYER_MAIN_3);

    Bg_ToggleLayer(BG_LAYER_SUB_0, 0);
    Bg_FreeTilemapBuffer(graphics->bgConfig, BG_LAYER_SUB_0);

    FreeSpriteSystem(graphics);
    FrontierParticleSystem_Free(graphics->particleSys);

    VramTransfer_Free();

    PaletteData_FreeBuffer(graphics->plttData, PLTTBUF_MAIN_BG);
    PaletteData_FreeBuffer(graphics->plttData, PLTTBUF_SUB_BG);
    PaletteData_FreeBuffer(graphics->plttData, PLTTBUF_MAIN_OBJ);
    PaletteData_FreeBuffer(graphics->plttData, PLTTBUF_SUB_OBJ);
    PaletteData_Free(graphics->plttData);
    Heap_Free(graphics->bgConfig);
    SysTask_Done(graphics->objectManagerTask);
    SysTask_Done(graphics->moveQueuesTask);
    SysTask_Done(graphics->renderTask);
    SysTask_Done(graphics->dummyExecuteOnVBlank);

    FreeG3DPipeline(graphics->g3dPipeline);

    DisableTouchPad();
    Heap_Free(graphics);

    GX_SetVisibleWnd(GX_WNDMASK_NONE);
    GXS_SetVisibleWnd(GX_WNDMASK_NONE);

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    Heap_Destroy(HEAP_ID_94);

    RenderControlFlags_SetCanABSpeedUpPrint(FALSE);
    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_DISABLED);
    RenderControlFlags_SetSpeedUpOnTouch(FALSE);

    NetworkIcon_Destroy();

    MI_CpuFill16((void *)HW_BG_PLTT, COLOR_WHITE, PALETTE_SIZE_BYTES * SLOTS_PER_PALETTE);
    MI_CpuFill16((void *)HW_OBJ_PLTT, COLOR_WHITE, PALETTE_SIZE_BYTES * SLOTS_PER_PALETTE);
    MI_CpuFill16((void *)HW_DB_BG_PLTT, COLOR_WHITE, PALETTE_SIZE_BYTES * SLOTS_PER_PALETTE);
    MI_CpuFill16((void *)HW_DB_OBJ_PLTT, COLOR_WHITE, PALETTE_SIZE_BYTES * SLOTS_PER_PALETTE);

    G2_BlendNone();
    G2S_BlendNone();
}

void FrontierFacilities_SaveObjectState(FrontierGraphics *param0)
{
    int v0;

    {
        FrontierObject *v1;

        for (v0 = 0; v0 < 32; v0++) {
            v1 = BattleFrontier_GetObject(param0->frontier, v0);

            if (v1->object != NULL) {
                v1->params.variant = WiFi2DCharObject_GetField(v1->object, 6);
                v1->params.moveState = WiFi2DCharObject_GetField(v1->object, 5);
                v1->params.x = WiFi2DCharObject_GetField(v1->object, 0);
                v1->params.y = WiFi2DCharObject_GetField(v1->object, 1);
                v1->params.isVisible = WiFi2DCharRenderer_IsObjectVisible(v1->sprite);
            }
        }
    }

    FrontierFacilities_SaveSpriteState(param0);
}

void FrontierFacilities_RestoreObjectState(FrontierGraphics *param0)
{
    int v0;

    {
        FrontierObjectGfx *v1;

        v1 = BattleFrontier_GetObjectGfxList(param0->frontier);

        for (v0 = 0; v0 < 24; v0++) {
            if (v1[v0].gfxID != 0xffff) {
                WiFi2DCharRenderer_LoadSpecies(param0->objectRenderer, v1[v0].gfxID, v1[v0].resourceVariant, HEAP_ID_94);
            }
        }
    }

    {
        FrontierObject *v2;
        FrontierObjectParams v3;

        for (v0 = 0; v0 < 32; v0++) {
            v2 = BattleFrontier_GetObject(param0->frontier, v0);

            if (v2->params.objectID != 0xffff) {
                FrontierFacilities_CopyObjectParams(v2, &v3);
                FrontierFacilities_AddObject(param0, &v3, v0);
            }
        }
    }

    FrontierFacilities_LoadSpriteState(param0);
}

static void VBlankCallback(void *data)
{
    FrontierGraphics *graphics = data;

    VramTransfer_Process();
    SpriteSystem_TransferOam();
    PaletteData_CommitFadedBuffers(graphics->plttData);
    Bg_RunScheduledUpdates(graphics->bgConfig);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void DummyExecuteOnVBlank(SysTask *task, void *data)
{
}

static void FrontierFacilities_UpdateObjectManagerTask(SysTask *param0, void *param1)
{
    FrontierGraphics *v0 = param1;
    WiFi2DCharObjectManager_Update(v0->objectManager);
}

static void FrontierFacilities_ProcessMoveQueuesTask(SysTask *param0, void *param1)
{
    FrontierGraphics *v0 = param1;
    FrontierFacilities_ProcessMoveQueues(v0);
}

static void FrontierFacilities_MainRenderTask(SysTask *param0, void *param1)
{
    FrontierGraphics *v0 = param1;

    {
        FrontierObject *v1;

        v1 = BattleFrontier_GetObject(v0->frontier, 32 - 1);

        if (v1->object != NULL) {
            WiFi2DCharViewOffset_SetFromObject(&v0->viewOffset, v1->object);
        }

        FrontierFacilities_UpdateBackground(v0);
    }

    WiFi2DCharRenderer_UpdateAll(v0->objectRenderer);

    {
        u32 v2 = v0->spriteSlots.visibleMask;
        int v3;

        for (v3 = 0; v3 < 8; v3++) {
            if ((v0->spriteSlots.sprites[v3] != NULL) && (v2 & 1)) {
                ManagedSprite_TickFrame(v0->spriteSlots.sprites[v3]);
            }

            v2 >>= 1;
        }
    }

    SpriteSystem_DrawSprites(v0->spriteMan);
    SpriteSystem_UpdateTransfer();

    FrontierParticleSystem_Update();
    G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
}

static void FrontierFacilities_UpdateBackground(FrontierGraphics *param0)
{
    int v0;
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(param0->frontier);

    v0 = FrontierScene_GetParam(fieldData->sceneID, FR_SCENE_FLAG_1);

    switch (v0) {
    case 0:
    default:
        if (param0->mainBackground != NULL) {
            WiFi2DCharBackground_Update(param0->mainBackground, &param0->viewOffset);
        }

        if ((param0->subBackground != NULL) && (FrontierScene_GetParam(fieldData->sceneID, FR_SCENE_FLAG_2) == 1)) {
            WiFi2DCharBackground_Update(param0->subBackground, &param0->viewOffset);
        }
        break;
    case 1:
        FrontierFacilities_UpdateBackgroundScroll(param0);
        break;
    }
}

static void FrontierFacilities_UpdateBackgroundScroll(FrontierGraphics *param0)
{
    s16 v0;
    s16 v1;
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(param0->frontier);

    v1 = WiFi2DCharViewOffset_GetX(&param0->viewOffset) + param0->shakeState.offsetX;
    v0 = WiFi2DCharViewOffset_GetY(&param0->viewOffset) + param0->shakeState.offsetY;

    SetMainScreenViewRect(SpriteSystem_GetRenderer(param0->spriteSystem), FX32_CONST(v0), FX32_CONST(v1));
    Bg_ScheduleScroll(param0->bgConfig, 3, 0, v0);
    Bg_ScheduleScroll(param0->bgConfig, 3, 3, v1);

    if ((FrontierScene_GetParam(fieldData->sceneID, FR_SCENE_SUB_TILEMAP_IDX) != 0xffff) && (FrontierScene_GetParam(fieldData->sceneID, FR_SCENE_FLAG_2) == 1)) {
        Bg_ScheduleScroll(param0->bgConfig, 2, 0, v0);
        Bg_ScheduleScroll(param0->bgConfig, 2, 3, v1);
    }
}

static void FrontierFacilities_ProcessMoveQueues(FrontierGraphics *param0)
{
    WiFi2DCharEvent v0;
    WiFi2DCharMoveRequest v1;
    BOOL v2;

    while (WiFi2DCharMoveQueue_Pop(param0->moveQueue, &v1) == 1) {
        WiFi2DCharObjectManager_StartMove(param0->objectManager, &v1);
    }

    while (WiFi2DCharEventQueue_Pop(param0->eventQueue, &v0) == 1) {
        v2 = WiFi2DCharAI_ChooseMove(param0->objectGrid, param0->objectManager, &v0, &v1);

        if (v2 == 1) {
            WiFi2DCharObjectManager_StartMove(param0->objectManager, &v1);
        }
    }
}

static void InitBackgrounds(BgConfig *bgConfig, int sceneID)
{
    GXBGMode bgMode = FrontierScene_GetParam(sceneID, FR_SCENE_BGMODE);
    GXLayers_DisableEngineALayers();

    GXBanks banks = {
        GX_VRAM_BG_256_BC,
        GX_VRAM_BGEXTPLTT_23_G,
        GX_VRAM_SUB_BG_32_H,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_64_E,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_0_A,
        GX_VRAM_TEXPLTT_0_F
    };

    GXLayers_SetBanks(&banks);

    MI_CpuClear32((void *)HW_BG_VRAM, HW_BG_VRAM_SIZE);
    MI_CpuClear32((void *)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
    MI_CpuClear32((void *)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    MI_CpuClear32((void *)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);

    GraphicsModes graphicsModes = {
        GX_DISPMODE_GRAPHICS,
        GX_BGMODE_5,
        GX_BGMODE_0,
        GX_BG0_AS_3D
    };

    graphicsModes.mainBgMode = bgMode;
    SetAllGraphicsModes(&graphicsModes);

    BgTemplate bgTemplates[] = {
        {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x0000,
            .charBase = GX_BG_CHARBASE_0x08000,
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
            .colorMode = GX_BG_COLORMODE_256,
            .screenBase = GX_BG_SCRBASE_0x0800,
            .charBase = GX_BG_CHARBASE_0x20000,
            .bgExtPltt = GX_BG_EXTPLTT_23,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        },
        {
            .x = 0,
            .y = 0,
            .bufferSize = 0x2000,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_512x512,
            .colorMode = GX_BG_COLORMODE_256,
            .screenBase = GX_BG_SCRBASE_0x2800,
            .charBase = GX_BG_CHARBASE_0x30000,
            .bgExtPltt = GX_BG_EXTPLTT_23,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        },
    };

    if (bgMode == GX_BGMODE_0) {
        bgTemplates[1].colorMode = GX_BG_COLORMODE_16;
        bgTemplates[2].colorMode = GX_BG_COLORMODE_16;
        bgTemplates[1].bgExtPltt = GX_BG_EXTPLTT_01;
        bgTemplates[2].bgExtPltt = GX_BG_EXTPLTT_01;
    }

    u16 screenSize = FrontierScene_GetParam(sceneID, FR_SCENE_SCREEN_SIZE);
    bgTemplates[2].screenSize = screenSize;

    if (FrontierScene_GetParam(sceneID, FR_SCENE_SUB_TILEMAP_IDX) != 0xffff) {
        bgTemplates[1].screenSize = screenSize;
    }

    if (bgMode == GX_BGMODE_0) {
        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_1, &bgTemplates[0], BG_TYPE_STATIC);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_1);
        Bg_SetOffset(bgConfig, BG_LAYER_MAIN_1, BG_OFFSET_UPDATE_SET_X, 0);
        Bg_SetOffset(bgConfig, BG_LAYER_MAIN_1, BG_OFFSET_UPDATE_SET_Y, 0);
        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_2, &bgTemplates[1], BG_TYPE_STATIC);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_2);
        Bg_SetOffset(bgConfig, BG_LAYER_MAIN_2, BG_OFFSET_UPDATE_SET_X, 0);
        Bg_SetOffset(bgConfig, BG_LAYER_MAIN_2, BG_OFFSET_UPDATE_SET_Y, 0);
        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_3, &bgTemplates[2], BG_TYPE_STATIC);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_3);
        Bg_SetOffset(bgConfig, BG_LAYER_MAIN_3, BG_OFFSET_UPDATE_SET_X, 0);
        Bg_SetOffset(bgConfig, BG_LAYER_MAIN_3, BG_OFFSET_UPDATE_SET_Y, 0);
    } else {
        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_1, &bgTemplates[0], BG_TYPE_STATIC);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_1);
        Bg_SetOffset(bgConfig, BG_LAYER_MAIN_1, BG_OFFSET_UPDATE_SET_X, 0);
        Bg_SetOffset(bgConfig, BG_LAYER_MAIN_1, BG_OFFSET_UPDATE_SET_Y, 0);
        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_2, &bgTemplates[1], BG_TYPE_STATIC_WITH_AFFINE);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_2);
        Bg_SetOffset(bgConfig, BG_LAYER_MAIN_2, BG_OFFSET_UPDATE_SET_X, 0);
        Bg_SetOffset(bgConfig, BG_LAYER_MAIN_2, BG_OFFSET_UPDATE_SET_Y, 0);
        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_3, &bgTemplates[2], BG_TYPE_STATIC_WITH_AFFINE);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_3);
        Bg_SetOffset(bgConfig, BG_LAYER_MAIN_3, BG_OFFSET_UPDATE_SET_X, 0);
        Bg_SetOffset(bgConfig, BG_LAYER_MAIN_3, BG_OFFSET_UPDATE_SET_Y, 0);
    }

    G2_SetBG0Priority(0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, TRUE);

    BgTemplate subBgTemplate[] = {
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

    Bg_InitFromTemplate(bgConfig, BG_LAYER_SUB_0, &subBgTemplate[0], BG_TYPE_STATIC);
    Bg_ClearTilemap(bgConfig, BG_LAYER_SUB_0);
    Bg_SetOffset(bgConfig, BG_LAYER_SUB_0, BG_OFFSET_UPDATE_SET_X, 0);
    Bg_SetOffset(bgConfig, BG_LAYER_SUB_0, BG_OFFSET_UPDATE_SET_Y, 0);
}

static void LoadMessageBoxAndWindowGraphics(FrontierGraphics *graphics)
{
    PaletteData_LoadBufferFromFileStart(graphics->plttData, NARC_INDEX_GRAPHIC__PL_FONT, font_NCLR, HEAP_ID_94, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
    PaletteData_LoadBufferFromFileStart(graphics->plttData, NARC_INDEX_GRAPHIC__PL_FONT, screen_indicators_NCLR, HEAP_ID_94, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(13));

    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(graphics->frontier);

    LoadMessageBoxGraphics(graphics->bgConfig, BG_LAYER_MAIN_1, BASE_TILE_SCROLLING_MESSAGE_BOX, 11, Options_Frame(fieldData->options), HEAP_ID_94);
    PaletteData_LoadBufferFromHardware(graphics->plttData, PLTTBUF_MAIN_BG, 11 * SLOTS_PER_PALETTE, PALETTE_SIZE_BYTES);

    LoadStandardWindowGraphics(graphics->bgConfig, BG_LAYER_MAIN_1, BASE_TILE_STANDARD_WINDOW_FRAME, 12, STANDARD_WINDOW_SYSTEM, HEAP_ID_94);
    PaletteData_LoadBufferFromHardware(graphics->plttData, PLTTBUF_MAIN_BG, 12 * SLOTS_PER_PALETTE, PALETTE_SIZE_BYTES);
}

static void LoadSubScreenBackground(FrontierGraphics *graphics)
{
    NARC *narc = NARC_ctor(NARC_INDEX_FRONTIER_BACKGROUNDS, HEAP_ID_94);

    Graphics_LoadTilesToBgLayerFromOpenNARC(narc, battle_frontier_app_sub_NCGR_lz, graphics->bgConfig, BG_LAYER_SUB_0, 0, 0, TRUE, HEAP_ID_94);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(narc, battle_frontier_app_sub_NSCR_lz, graphics->bgConfig, BG_LAYER_SUB_0, 0, 0, TRUE, HEAP_ID_94);
    PaletteData_LoadBufferFromFileStart(graphics->plttData, NARC_INDEX_FRONTIER_BACKGROUNDS, battle_frontier_app_sub_NCLR, HEAP_ID_94, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES, 0);
    NARC_dtor(narc);
}

static void FrontierFacilities_InitObjectSystem(FrontierGraphics *param0, int sceneID, const TrainerInfo *playerInfo)
{
    param0->objectManager = WiFi2DCharObjectManager_New(32, HEAP_ID_94);
    param0->objectGrid = WiFi2DCharGrid_New(256 / 16, 256 / 16, HEAP_ID_94);

    WiFi2DCharViewOffset_Reset(&param0->viewOffset);

    param0->objectRenderer = WiFi2DCharRenderer_NewWithShadow(SpriteManager_GetSpriteList(param0->spriteMan), param0->plttData, 32, BattleFrontier_GetPlayerObjEventGfx(playerInfo), 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAP_ID_94);

    {
        WiFiMenuAppSpriteParams v0 = {
            0,
            3,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0x2800,
            GX_BG_CHARBASE_0x30000,
            GX_BG_EXTPLTT_01,
            3,
            0,
            0,
            0,
            1
        };
        int v1;

        v0.narcID = FrontierScene_GetParam(sceneID, FR_SCENE_NARC_ID);
        v0.tilemapNarcMember = FrontierScene_GetParam(sceneID, FR_SCENE_TILEMAP_IDX);
        v1 = FrontierScene_GetParam(sceneID, FR_SCENE_FLAG_1);

        if (v1 == 0) {
            param0->mainBackground = WiFi2DCharBackground_New(SpriteSystem_GetRenderer(param0->spriteSystem), param0->bgConfig, &v0, HEAP_ID_94);
        }

        if (FrontierScene_GetParam(sceneID, FR_SCENE_SUB_TILEMAP_IDX) != 0xffff) {
            v0.tilemapNarcMember = FrontierScene_GetParam(sceneID, FR_SCENE_SUB_TILEMAP_IDX);
            v0.bgLayer = 2;
            v0.screenBase = (GX_BG_SCRBASE_0x0800);
            v0.charBase = (GX_BG_CHARBASE_0x20000);
            v0.priority = 1;

            if (v1 == 0) {
                param0->subBackground = WiFi2DCharBackground_New(SpriteSystem_GetRenderer(param0->spriteSystem), param0->bgConfig, &v0, HEAP_ID_94);
            }
        }
    }

    param0->eventQueue = WiFi2DCharEventQueue_New(128, HEAP_ID_94);
    param0->moveQueue = WiFi2DCharMoveQueue_New(128, HEAP_ID_94);

    WiFi2DCharGrid_SetTiles(param0->objectGrid, sEmptyGridTiles);

    {
        GXBGMode bgMode = FrontierScene_GetParam(sceneID, FR_SCENE_BGMODE);

        u32 narcID = FrontierScene_GetParam(sceneID, FR_SCENE_NARC_ID);
        NARC *narc = NARC_ctor(narcID, HEAP_ID_94);

        Graphics_LoadTilesToBgLayerFromOpenNARC(narc, FrontierScene_GetParam(sceneID, FR_SCENE_TILES_IDX), param0->bgConfig, 3, 0, 0, 1, HEAP_ID_94);

        if (bgMode == GX_BGMODE_0) {
            PaletteData_LoadBufferFromFileStart(param0->plttData, narcID, FrontierScene_GetParam(sceneID, FR_SCENE_PLTT_IDX), HEAP_ID_94, 0, (10 - 0 + 1) * PALETTE_SIZE_BYTES, PLTT_DEST(0));
        } else {
            NNSG2dPaletteData *plttData;

            void *pltt = Graphics_GetPlttDataFromOpenNARC(narc, FrontierScene_GetParam(sceneID, FR_SCENE_PLTT_IDX), &plttData, HEAP_ID_94);
            DC_FlushRange(plttData->pRawData, plttData->szByte);

            GX_BeginLoadBGExtPltt();
            GX_LoadBGExtPltt(plttData->pRawData, 0x6000, 0x2000);
            GX_EndLoadBGExtPltt();

            Heap_Free(pltt);
        }

        PaletteData_FillBufferRange(param0->plttData, PLTTBUF_MAIN_BG, PLTTSEL_BOTH, 0x0, 0, 1);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(narc, FrontierScene_GetParam(sceneID, FR_SCENE_TILEMAP_IDX), param0->bgConfig, 3, 0, 0, 1, HEAP_ID_94);

        if (FrontierScene_GetParam(sceneID, FR_SCENE_SUB_TILEMAP_IDX) != 0xffff) {
            Graphics_LoadTilesToBgLayerFromOpenNARC(narc, FrontierScene_GetParam(sceneID, FR_SCENE_SUB_TILES_IDX), param0->bgConfig, 2, 0, 0, 1, HEAP_ID_94);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(narc, FrontierScene_GetParam(sceneID, FR_SCENE_SUB_TILEMAP_IDX), param0->bgConfig, 2, 0, 0, 1, HEAP_ID_94);

            if (bgMode != GX_BGMODE_0) {
                NNSG2dPaletteData *plttData;

                void *pltt = Graphics_GetPlttDataFromOpenNARC(narc, FrontierScene_GetParam(sceneID, FR_SCENE_SUB_PLTT_IDX), &plttData, HEAP_ID_94);
                DC_FlushRange(plttData->pRawData, plttData->szByte);

                GX_BeginLoadBGExtPltt();
                GX_LoadBGExtPltt(plttData->pRawData, 0x4000, 0x2000);
                GX_EndLoadBGExtPltt();

                Heap_Free(pltt);
            }
        }

        Bg_ScheduleTilemapTransfer(param0->bgConfig, 3);
        NARC_dtor(narc);
    }
}

static void FrontierFacilities_FreeObjectSystem(FrontierGraphics *param0)
{
    int v0;

    {
        FrontierObject *v1;

        v1 = BattleFrontier_GetObjects(param0->frontier);

        for (v0 = 0; v0 < 32; v0++) {
            if (v1[v0].object != NULL) {
                WiFi2DCharObject_Reset(v1[v0].object);
                GF_ASSERT(v1[v0].movementTask == NULL);
            }
        }
    }

    WiFi2DCharObjectManager_Free(param0->objectManager);
    WiFi2DCharGrid_Free(param0->objectGrid);
    WiFi2DCharRenderer_Free(param0->objectRenderer);

    if (param0->mainBackground != NULL) {
        WiFi2DCharBackground_Free(param0->mainBackground);
    }

    if (param0->subBackground != NULL) {
        WiFi2DCharBackground_Free(param0->subBackground);
    }

    WiFi2DCharEventQueue_Free(param0->eventQueue);
    WiFi2DCharMoveQueue_Free(param0->moveQueue);
}

static G3DPipelineBuffers *InitG3DPipeline(enum HeapID heapID)
{
    return G3DPipeline_Init(heapID, TEXTURE_VRAM_SIZE_128K, PALETTE_VRAM_SIZE_16K, G3DPipelineCallback);
}

static void G3DPipelineCallback(void)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, TRUE);

    G2_SetBG0Priority(1);
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
    G3X_AlphaTest(FALSE, 0);
    G3X_AlphaBlend(TRUE);
    G3X_EdgeMarking(FALSE);
    G3X_SetFog(FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0);
    G3X_SetClearColor(COLOR_BLACK, 0, G3X_DEPTH_MAX, 63, FALSE);
    G3_ViewPort(0, 0, 255, 191);
}

static void FreeG3DPipeline(G3DPipelineBuffers *g3dPipeline)
{
    G3DPipelineBuffers_Free(g3dPipeline);
}

static void InitSpriteSystem(FrontierGraphics *graphics)
{
    graphics->spriteSystem = SpriteSystem_Alloc(HEAP_ID_94);

    SpriteSystem_Init(graphics->spriteSystem, &sOamTemplate, &sTransferTemplate, 32);
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_128K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    graphics->spriteMan = SpriteManager_New(graphics->spriteSystem);

    SpriteSystem_InitSprites(graphics->spriteSystem, graphics->spriteMan, 128);
    SpriteSystem_InitManagerWithCapacities(graphics->spriteSystem, graphics->spriteMan, &sCapacities);
    SetSubScreenViewRect(SpriteSystem_GetRenderer(graphics->spriteSystem), 0, FX32_CONST(512));
}

static void FreeSpriteSystem(FrontierGraphics *graphics)
{
    for (int i = 0; i < 8; i++) {
        if (graphics->spriteSlots.sprites[i] != NULL) {
            FrontierFacilities_DeleteObjectSprite(graphics->spriteSlots.sprites[i]);
        }
    }

    for (int i = 0; i < 8; i++) {
        if (graphics->spriteSlots.loadedResourceIDs[i] != 0xffff) {
            FrontierFacilities_UnloadObjectSpriteResources(graphics->spriteMan, graphics->spriteSlots.loadedResourceIDs[i]);
        }
    }

    for (int i = 0; i < ((50000 + 3) - 50000 + 1); i++) {
        if (graphics->fieldSprites[i] != NULL) {
            Sprite_DeleteAndFreeResources(graphics->fieldSprites[i]);

            SpriteManager_UnloadCharObjById(graphics->spriteMan, 50000 + i);
            SpriteManager_UnloadPlttObjById(graphics->spriteMan, 50000 + i);
            SpriteManager_UnloadCellObjById(graphics->spriteMan, 50000 + i);
            SpriteManager_UnloadAnimObjById(graphics->spriteMan, 50000 + i);
        }
    }

    SpriteSystem_FreeResourcesAndManager(graphics->spriteSystem, graphics->spriteMan);
    SpriteSystem_Free(graphics->spriteSystem);
}

void FrontierFacilities_AddObjectGfx(FrontierGraphics *param0, const FrontierObjectGfx *param1)
{
    FrontierObjectGfx *v0;
    int v1, v2;

    v0 = BattleFrontier_GetObjectGfxList(param0->frontier);

    for (v1 = 0; v1 < 24; v1++) {
        if (v0[v1].gfxID == param1->gfxID) {
            return;
        }
    }

    for (v1 = 0; v1 < 24; v1++) {
        if (v0[v1].gfxID == 0xffff) {
            break;
        }
    }

    GF_ASSERT(v1 != 24);

    v2 = v1;
    v0[v2] = *param1;

    WiFi2DCharRenderer_LoadSpecies(param0->objectRenderer, param1->gfxID, param1->resourceVariant, HEAP_ID_94);
}

void FrontierFacilities_RemoveObjectGfx(FrontierGraphics *param0, int param1)
{
    int v0;
    FrontierObjectGfx *v1 = BattleFrontier_GetObjectGfxList(param0->frontier);

    for (v0 = 0; v0 < 24; v0++) {
        if (v1[v0].gfxID == param1) {
            WiFi2DCharRenderer_UnloadSpecies(param0->objectRenderer, param1);
            v1[v0].gfxID = 0xffff;
            return;
        }
    }
}

WiFi2DCharObject *FrontierFacilities_AddObject(FrontierGraphics *param0, const FrontierObjectParams *param1, int param2)
{
    FrontierObject *v0;
    int v1, v2;
    WiFiMenuAppRect v3;
    WiFi2DCharObject *v4;
    WiFi2DCharRenderObject *v5;

    v0 = BattleFrontier_GetObjects(param0->frontier);

    if (param2 == -1) {
        for (v1 = 0; v1 < 32; v1++) {
            if (v0[v1].object == NULL) {
                break;
            }
        }

        GF_ASSERT(v1 != 32);
        v2 = v1;
    } else {
        v2 = param2;
    }

    v3.x = param1->x;
    v3.y = param1->y;
    v3.objectID = param1->objectID;
    v3.moveState = param1->moveState;
    v3.variant = param1->variant;
    v3.gfxID = param1->gfxID;

    v4 = WiFi2DCharObjectManager_AddObject(param0->objectManager, &v3);
    v5 = WiFi2DCharRenderer_AddObject(param0->objectRenderer, v4, 0, HEAP_ID_94);

    WiFi2DCharRenderer_SetObjectVisible(v5, param1->isVisible);
    FrontierFacilities_SetObject(param0->frontier, v2, v4, v5, param1);

    return v4;
}

void FrontierFacilities_RemoveObject(FrontierGraphics *param0, WiFi2DCharObject *param1)
{
    int v0;
    FrontierObject *v1 = BattleFrontier_GetObjects(param0->frontier);

    for (v0 = 0; v0 < 32; v0++) {
        if (v1[v0].object == param1) {
            WiFi2DCharObject_Reset(v1[v0].object);
            WiFi2DCharRenderer_RemoveObject(v1[v0].sprite);

            GF_ASSERT(v1[v0].movementTask == NULL);
            MI_CpuClear8(&v1[v0], sizeof(FrontierObject));

            v1[v0].params.objectID = 0xffff;
            return;
        }
    }
}

void FrontierFacilities_GetObjectAndSprite(FrontierGraphics *param0, u16 param1, WiFi2DCharObject **param2, WiFi2DCharRenderObject **param3)
{
    int v0;
    FrontierObject *v1 = BattleFrontier_GetObjects(param0->frontier);

    for (v0 = 0; v0 < 32; v0++) {
        if (v1[v0].params.objectID == param1) {
            if (param2 != NULL) {
                *param2 = v1[v0].object;
            }

            if (param3 != NULL) {
                *param3 = v1[v0].sprite;
            }

            return;
        }
    }

    GF_ASSERT(FALSE);
}

void FrontierFacilities_AddSpriteID(FrontierGraphics *param0, u16 param1)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->spriteSlots.loadedResourceIDs[v0] == 0xffff) {
            param0->spriteSlots.loadedResourceIDs[v0] = param1;
            return;
        }
    }

    GF_ASSERT(FALSE);
}

void FrontierFacilities_RemoveSpriteID(FrontierGraphics *param0, u16 param1)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->spriteSlots.loadedResourceIDs[v0] == param1) {
            param0->spriteSlots.loadedResourceIDs[v0] = 0xffff;
            return;
        }
    }
}

ManagedSprite *FrontierFacilities_AddManagedSprite(FrontierGraphics *param0, u16 param1, u16 param2)
{
    ManagedSprite *v0;

    GF_ASSERT(param1 < 8);
    GF_ASSERT(param0->spriteSlots.sprites[param1] == NULL);

    v0 = FrontierFacilities_CreateObjectSprite(param0->spriteSystem, param0->spriteMan, param2);

    param0->spriteSlots.sprites[param1] = v0;
    param0->spriteSlots.resourceIDs[param1] = param2;

    FrontierFacilities_SetSpriteVisible(param0, param1, 0);
    return v0;
}

void FrontierFacilities_RemoveManagedSprite(FrontierGraphics *param0, u16 param1)
{
    GF_ASSERT(param1 < 8);
    GF_ASSERT(param0->spriteSlots.sprites[param1] != NULL);

    FrontierFacilities_DeleteObjectSprite(param0->spriteSlots.sprites[param1]);
    param0->spriteSlots.sprites[param1] = NULL;
}

ManagedSprite *FrontierFacilities_GetManagedSprite(FrontierGraphics *param0, u16 param1)
{
    return param0->spriteSlots.sprites[param1];
}

void FrontierFacilities_SetSpriteVisible(FrontierGraphics *param0, u16 param1, int param2)
{
    if (param2 == 1) {
        param0->spriteSlots.visibleMask |= 1 << param1;
    } else {
        param0->spriteSlots.visibleMask &= 0xffffffff ^ (1 << param1);
    }
}

u32 FrontierFacilities_IsSpriteVisible(FrontierGraphics *param0, u16 param1)
{
    return (param0->spriteSlots.visibleMask >> param1) & 1;
}

static void FrontierFacilities_SaveSpriteState(FrontierGraphics *param0)
{
    int v0;
    FrontierSpriteStateBuffer *v1 = BattleFrontier_GetSpriteStateBuffer(param0->frontier);
    FrontierFacilitiesSpriteSlots *v2 = &param0->spriteSlots;

    for (v0 = 0; v0 < 8; v0++) {
        if (v2->loadedResourceIDs[v0] != 0xffff) {
            v1->spriteIDs[v0] = v2->loadedResourceIDs[v0];
            v0++;
        }
    }

    v0 = 0;

    for (v0 = 0; v0 < 8; v0++) {
        if (v2->sprites[v0] != NULL) {
            v1->states[v0].activeAnim = ManagedSprite_GetActiveAnim(v2->sprites[v0]);
            v1->states[v0].animationFrame = ManagedSprite_GetAnimationFrame(v2->sprites[v0]);
            v1->states[v0].visible = FrontierFacilities_IsSpriteVisible(param0, v0);
            v1->states[v0].drawFlag = ManagedSprite_GetDrawFlag(v2->sprites[v0]);
            v1->states[v0].resourceID = v2->resourceIDs[v0];
            ManagedSprite_GetPositionXY(v2->sprites[v0], &v1->states[v0].x, &v1->states[v0].y);
            v1->states[v0].valid = 1;
        }
    }
}

static void FrontierFacilities_LoadSpriteState(FrontierGraphics *param0)
{
    int v0;
    NARC *v1;
    FrontierSpriteStateBuffer *v2;
    ManagedSprite *v3;

    v2 = BattleFrontier_GetSpriteStateBuffer(param0->frontier);
    v1 = NARC_ctor(NARC_INDEX_RESOURCE__ENG__FRONTIER_GRAPHIC__FRONTIER_OBJ, HEAP_ID_94);

    for (v0 = 0; v0 < 8; v0++) {
        if (v2->spriteIDs[v0] != 0xffff) {
            FrontierFacilities_LoadObjectSpriteResources(param0->spriteSystem, param0->spriteMan, v1, param0->plttData, v2->spriteIDs[v0]);
            FrontierFacilities_AddSpriteID(param0, v2->spriteIDs[v0]);
        }
    }

    for (v0 = 0; v0 < 8; v0++) {
        if (v2->states[v0].valid == 1) {
            v3 = FrontierFacilities_AddManagedSprite(param0, v0, v2->states[v0].resourceID);
            ManagedSprite_SetPositionXY(v3, v2->states[v0].x, v2->states[v0].y);
            ManagedSprite_SetDrawFlag(v3, v2->states[v0].drawFlag);

            FrontierFacilities_SetSpriteVisible(param0, v0, v2->states[v0].visible);

            ManagedSprite_SetAnim(v3, v2->states[v0].activeAnim);
            ManagedSprite_SetAnimationFrame(v3, v2->states[v0].animationFrame);
        }
    }

    NARC_dtor(v1);
    BattleFrontier_ClearSpriteStateBuffer(param0->frontier);
}

void FrontierFacilities_GetViewOffset(FrontierGraphics *param0, s16 *param1, s16 *param2)
{
    *param2 = WiFi2DCharViewOffset_GetX(&param0->viewOffset);
    *param1 = WiFi2DCharViewOffset_GetY(&param0->viewOffset);
}

static void FrontierFacilities_CopyObjectParams(FrontierObject *param0, FrontierObjectParams *param1)
{
    *param1 = param0->params;
}

static void FrontierFacilities_SetObject(BattleFrontier *param0, int param1, WiFi2DCharObject *param2, WiFi2DCharRenderObject *param3, const FrontierObjectParams *param4)
{
    FrontierObject *v0 = BattleFrontier_GetObject(param0, param1);

    v0->object = param2;
    v0->sprite = param3;
    v0->params = *param4;
}

FrontierObject *FrontierFacilities_GetObject(BattleFrontier *param0, int param1)
{
    int v0;
    FrontierObject *v1 = BattleFrontier_GetObjects(param0);

    for (v0 = 0; v0 < 32; v0++) {
        if ((v1->object != NULL) && (v1->params.objectID == param1)) {
            return v1;
        }

        v1++;
    }

    GF_ASSERT(FALSE);
    return NULL;
}
