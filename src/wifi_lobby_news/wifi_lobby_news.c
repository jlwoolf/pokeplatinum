#include "wifi_lobby_news/wifi_lobby_news.h"

#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"

#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_0223177C.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230FA0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0223177C_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02232068.h"

#include "bg_window.h"
#include "char_transfer.h"
#include "enums.h"
#include "font.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "palette.h"
#include "pltt_transfer.h"
#include "render_oam.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "system.h"
#include "text.h"
#include "vram_transfer.h"

typedef struct {
    u32 tileIndex;
} WiFiLobbyNewsTileIndex;

typedef struct {
    u8 tilemapLeft;
    u8 tilemapTop;
    u8 width;
    u8 height;
    u16 baseTile;
    u8 palette;
    u8 textX;
    u8 textY;
    u8 alignment;
    TextColor textColor;
} WiFiLobbyNewsLabelTemplate;

typedef struct {
    void *rawData;
    NNSG2dScreenData *screenData;
} WiFiLobbyNewsScreenData;

typedef struct {
    WiFiPlazaLobbyTime time;
    u8 active;
    u8 needsRedraw;
    u16 frame;
    u32 unitsPerTile;
} WiFiLobbyNewsTimer;

typedef struct {
    s16 frame;
    u16 state;
} WiFiLobbyNewsHeadlines;

typedef struct {
    u8 colors[4];
} WiFiLobbyNewsTrainerColors;

typedef struct {
    u8 active;
    u8 paletteOffset;
    u16 scrollProgress;
    u16 duration;
    u16 textWidth;
    String *text;
    Window window;
    WiFiLobbyNewsTrainerColors trainerColors;
} WiFiLobbyNewsTickerEntry;

typedef struct {
    WiFiLobbyNewsTickerEntry entries[3];
    Window windows[3];
    String *text;
    void *paletteRaw;
    NNSG2dPaletteData *palette;
} WiFiLobbyNewsTicker;

typedef struct {
    u16 active;
    u16 frame;
    u16 color;
    u16 paletteOffset;
    u32 soundEffect;
} WiFiLobbyNewsLabelFlash;

typedef struct {
    Window windows[4];
    WiFiLobbyNewsLabelFlash flashes[4];
} WiFiLobbyNewsLabels;

typedef struct {
    BgConfig *bgConfig;
    SpriteList *spriteList;
    G2dRenderer renderer;
    SpriteResourceCollection *spriteResources[4];
    NARC *narc;
} WiFiLobbyNewsGraphics;

typedef struct {
    WiFiPlazaLobbyNews *newsData;
    const WiFiPlazaLobbyTime *time;
    WiFiLobbyNewsGraphics graphics;
    WiFiLobbyNewsScreenData screenData;
    WiFiLobbyNewsTimer timer;
    WiFiLobbyNewsHeadlines headlines;
    WiFiLobbyNewsTicker ticker;
    WiFiLobbyNewsLabels labels;
} WiFiLobbyNews;

static void WiFiLobbyNews_VBlankCallback(void *param0);
static void WiFiLobbyNews_Update(WiFiLobbyNews *param0, const WiFiPlazaLobbyState *param1);
static void WiFiLobbyNews_InitGraphics(WiFiLobbyNewsGraphics *param0, enum HeapID heapID);
static void WiFiLobbyNews_FreeGraphics(WiFiLobbyNewsGraphics *param0);
static void WiFiLobbyNews_UpdateSprites(WiFiLobbyNewsGraphics *param0);
static void WiFiLobbyNews_ProcessVBlank(WiFiLobbyNewsGraphics *param0);
static void WiFiLobbyNews_InitBackgrounds(WiFiLobbyNewsGraphics *param0, enum HeapID heapID);
static void WiFiLobbyNews_FreeBackgrounds(WiFiLobbyNewsGraphics *param0);
static void WiFiLobbyNews_InitSpriteSystem(WiFiLobbyNewsGraphics *param0, enum HeapID heapID);
static void WiFiLobbyNews_FreeSpriteSystem(WiFiLobbyNewsGraphics *param0);
static void WiFiLobbyNews_LoadScreenData(WiFiLobbyNewsScreenData *param0, WiFiLobbyNewsGraphics *param1, enum HeapID heapID);
static void WiFiLobbyNews_FreeScreenData(WiFiLobbyNewsScreenData *param0);
static void WiFiLobbyNews_DrawTimerTile(WiFiLobbyNewsScreenData *param0, WiFiLobbyNewsGraphics *param1, u32 param2, u8 param3, u8 param4);
static void WiFiLobbyNews_DrawHeadlineTile(WiFiLobbyNewsScreenData *param0, WiFiLobbyNewsGraphics *param1, u8 param2, u8 param3, u32 param4, u32 param5, BOOL param6, BOOL param7, BOOL param8);
static void WiFiLobbyNews_InitTimer(WiFiLobbyNewsTimer *param0, WiFiLobbyNewsGraphics *param1, WiFiLobbyNewsScreenData *param2, const WiFiPlazaLobbyNews *param3, const WiFiPlazaLobbyTime *param4, const WiFiPlazaLobbyState *param5, enum HeapID heapID);
static void WiFiLobbyNews_FreeTimer(WiFiLobbyNewsTimer *param0);
static BOOL WiFiLobbyNews_UpdateTimer(WiFiLobbyNewsTimer *param0, const WiFiPlazaLobbyNews *param1, const WiFiPlazaLobbyTime *param2);
static void WiFiLobbyNews_DrawTimer(WiFiLobbyNewsTimer *param0, WiFiLobbyNewsScreenData *param1, WiFiLobbyNewsGraphics *param2);
static void WiFiLobbyNews_AnimateTimer(WiFiLobbyNewsTimer *param0, WiFiLobbyNewsScreenData *param1, WiFiLobbyNewsGraphics *param2);
static void WiFiLobbyNews_DrawTimerGrid(WiFiLobbyNewsTimer *param0, WiFiLobbyNewsScreenData *param1, WiFiLobbyNewsGraphics *param2);
static void WiFiLobbyNews_InitHeadlines(WiFiLobbyNewsHeadlines *param0, WiFiLobbyNewsGraphics *param1, WiFiLobbyNewsScreenData *param2, const WiFiPlazaLobbyNews *param3, const WiFiPlazaLobbyState *param4, enum HeapID heapID);
static void WiFiLobbyNews_FreeHeadlines(WiFiLobbyNewsHeadlines *param0);
static BOOL WiFiLobbyNews_UpdateHeadlines(WiFiLobbyNewsHeadlines *param0, const WiFiPlazaLobbyNews *param1);
static void WiFiLobbyNews_DrawHeadlines(WiFiLobbyNewsHeadlines *param0, WiFiLobbyNewsScreenData *param1, WiFiLobbyNewsGraphics *param2, const WiFiPlazaLobbyNews *param3, const WiFiPlazaLobbyState *param4);
static void WiFiLobbyNews_DrawHeadlineRow(WiFiLobbyNewsScreenData *param0, WiFiLobbyNewsGraphics *param1, const WiFiPlazaLobbyNews *param2, const WiFiPlazaLobbyState *param3, u32 param4);
static void WiFiLobbyNews_AnimateHeadlineRowA(WiFiLobbyNewsScreenData *param0, WiFiLobbyNewsGraphics *param1, const WiFiPlazaLobbyNews *param2, const WiFiPlazaLobbyState *param3, u32 param4);
static void WiFiLobbyNews_AnimateHeadlineRowB(WiFiLobbyNewsScreenData *param0, WiFiLobbyNewsGraphics *param1, const WiFiPlazaLobbyNews *param2, const WiFiPlazaLobbyState *param3, u32 param4);
static void WiFiLobbyNews_SetTrainerColors(WiFiLobbyNewsTrainerColors *param0, const WiFiPlazaLobbyNews *param1, int param2, const WiFiPlazaLobbyState *param3);
static void WiFiLobbyNews_LoadTrainerPalette(const WiFiLobbyNewsTrainerColors *param0, const NNSG2dPaletteData *param1, u32 param2);
static void WiFiLobbyNews_InitTicker(WiFiLobbyNewsTicker *param0, WiFiLobbyNewsGraphics *param1, enum HeapID heapID);
static void WiFiLobbyNews_FreeTicker(WiFiLobbyNewsTicker *param0);
static BOOL WiFiLobbyNews_UpdateTicker(WiFiLobbyNewsTicker *param0, WiFiPlazaLobbyNews *param1, const WiFiPlazaLobbyState *param2, enum HeapID heapID);
static void WiFiLobbyNews_DrawTicker(WiFiLobbyNewsTicker *param0);
static void WiFiLobbyNews_InitTickerEntry(WiFiLobbyNewsTickerEntry *param0, WiFiLobbyNewsGraphics *param1, u32 param2, enum HeapID heapID);
static void WiFiLobbyNews_FreeTickerEntry(WiFiLobbyNewsTickerEntry *param0);
static void WiFiLobbyNews_SetTickerEntry(WiFiLobbyNewsTickerEntry *param0, const String *param1, u32 param2, const WiFiLobbyNewsTrainerColors *param3, const NNSG2dPaletteData *param4);
static void WiFiLobbyNews_ClearTickerEntry(WiFiLobbyNewsTickerEntry *param0);
static BOOL WiFiLobbyNews_AdvanceTickerEntry(WiFiLobbyNewsTickerEntry *param0);
static void WiFiLobbyNews_ScrollTickerEntry(const WiFiLobbyNewsTickerEntry *param0, Window *param1);
static void WiFiLobbyNews_InitLabels(WiFiLobbyNewsLabels *param0, WiFiLobbyNewsGraphics *param1, enum HeapID heapID);
static void WiFiLobbyNews_FreeLabels(WiFiLobbyNewsLabels *param0);
static void WiFiLobbyNews_UpdateLabels(WiFiLobbyNewsLabels *param0);
static void WiFiLobbyNews_FlashLabel(WiFiLobbyNewsLabels *param0, u32 param1);
static void WiFiLobbyNews_InitLabelFlash(WiFiLobbyNewsLabelFlash *param0, u16 param1, u32 param2);
static void WiFiLobbyNews_FreeLabelFlash(WiFiLobbyNewsLabelFlash *param0);
static void WiFiLobbyNews_StartLabelFlash(WiFiLobbyNewsLabelFlash *param0);
static void WiFiLobbyNews_UpdateLabelFlash(WiFiLobbyNewsLabelFlash *param0);

static const CharTransferTemplate sCharTransferTemplate = {
    0x20,
    0x18000,
    0x4000,
    0x6B
};

static const GXBanks sGXBanks = {
    GX_VRAM_BG_256_AB,
    GX_VRAM_BGEXTPLTT_NONE,
    GX_VRAM_SUB_BG_128_C,
    GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_96_EFG,
    GX_VRAM_OBJEXTPLTT_NONE,
    GX_VRAM_SUB_OBJ_16_I,
    GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE,
    GX_VRAM_TEXPLTT_NONE
};

static const GraphicsModes sGraphicsModes = {
    GX_DISPMODE_GRAPHICS,
    GX_BGMODE_0,
    GX_BGMODE_0,
    GX_BG0_AS_2D
};

static const u32 sBgLayers[5] = {
    BG_LAYER_MAIN_0,
    BG_LAYER_MAIN_1,
    BG_LAYER_MAIN_2,
    BG_LAYER_MAIN_3,
    BG_LAYER_SUB_0
};

static const BgTemplate sBgTemplates[5] = {
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
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
        .screenBase = GX_BG_SCRBASE_0xe000,
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
        .screenBase = GX_BG_SCRBASE_0xd800,
        .charBase = GX_BG_CHARBASE_0x10000,
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
        .charBase = GX_BG_CHARBASE_0x10000,
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
        .screenBase = GX_BG_SCRBASE_0xe800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    }
};

static const u8 sTickerWindowTops[3] = {
    0xF,
    0x12,
    0x15
};

static const u32 sTickerDurations[3] = {
    0x150,
    0x120,
    0xF0
};

static const WiFiLobbyNewsTileIndex sTileIndices[4] = {
    { 0x1 },
    { 0x4 },
    { 0x5 },
    { 0x6 }
};

static const WiFiLobbyNewsLabelTemplate sLabelTemplates[4] = {
    { 0x6, 0x0, 0x14, 0x8, 0x1, 0xA, 0x50, 0x6, 0x1, TEXT_COLOR(3, 4, 0) },
    { 0x0, 0x6, 0x6, 0x3, 0xA1, 0x7, 0x10, 0x4, 0x1, TEXT_COLOR(13, 14, 0) },
    { 0xF, 0x6, 0x6, 0x5, 0xB3, 0x7, 0x18, 0x4, 0x1, TEXT_COLOR(13, 14, 0) },
    { 0x4, 0xC, 0x12, 0x3, 0xD1, 0x7, 0x4, 0x4, 0x0, TEXT_COLOR(13, 14, 0) }
};

static u16 sLabelPaletteOffsets[4] = {
    0x0,
    0x18,
    0x1A,
    0x1E
};

static u32 sLabelSoundEffects[4] = {
    0x0,
    0x5DD,
    0x5E4,
    0x5E3
};

int WiFiLobbyNews_Init(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyNews *v0;
    WiFiPlazaLobbyNewsAppArgs *v1 = ApplicationManager_Args(appMan);
    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_107, 0x50000);

    v0 = ApplicationManager_NewData(appMan, sizeof(WiFiLobbyNews), HEAP_ID_107);
    memset(v0, 0, sizeof(WiFiLobbyNews));

    v0->newsData = v1->news;
    v0->time = v1->currentTime;

    WiFiLobbyNews_InitGraphics(&v0->graphics, HEAP_ID_107);
    WiFiLobbyNews_LoadScreenData(&v0->screenData, &v0->graphics, HEAP_ID_107);
    WiFiLobbyNews_InitTimer(&v0->timer, &v0->graphics, &v0->screenData, v0->newsData, v0->time, v1->state, HEAP_ID_107);
    WiFiLobbyNews_InitHeadlines(&v0->headlines, &v0->graphics, &v0->screenData, v0->newsData, v1->state, HEAP_ID_107);
    WiFiLobbyNews_InitTicker(&v0->ticker, &v0->graphics, HEAP_ID_107);
    WiFiLobbyNews_InitLabels(&v0->labels, &v0->graphics, HEAP_ID_107);

    SetVBlankCallback(WiFiLobbyNews_VBlankCallback, v0);
    DisableHBlank();

    return 1;
}

int WiFiLobbyNews_Main(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyNews *v0;
    WiFiPlazaLobbyNewsAppArgs *v1;
    BOOL v2;

    v0 = ApplicationManager_Data(appMan);
    v1 = ApplicationManager_Args(appMan);

    switch (*param1) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_107);
        WiFiPlazaLobby_State_SetBGMVolumeDucked(v1->state, 1);
        (*param1)++;
        break;
    case 1:
        v2 = IsScreenFadeDone();

        if (v2 == 1) {
            (*param1)++;
        }
        break;
    case 2:
        if ((gSystem.pressedKeys & PAD_BUTTON_B) || (WiFiPlazaLobby_State_IsLobbyClosed(v1->state) == 1) || (WiFiPlazaLobby_Time_HasWifiError() == 1)) {
            if (WiFiPlazaLobby_State_IsLobbyClosed(v1->state) == 1) {
                WiFiPlazaLobby_State_SetPlayerWarpPending(v1->state);
            }
            (*param1) = 3;
        } else {
            v2 = WiFiLobbyNews_UpdateTimer(&v0->timer, v0->newsData, v0->time);

            if (v2 == 1) {
                WiFiLobbyNews_FlashLabel(&v0->labels, 1);
            }

            v2 = WiFiLobbyNews_UpdateHeadlines(&v0->headlines, v0->newsData);

            if (v2 == 1) {
                WiFiLobbyNews_FlashLabel(&v0->labels, 2);
            }

            v2 = WiFiLobbyNews_UpdateTicker(&v0->ticker, v0->newsData, v1->state, HEAP_ID_107);

            if (v2 == 1) {
                WiFiLobbyNews_FlashLabel(&v0->labels, 3);
            }
        }
        break;
    case 3:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_107);
        (*param1)++;
        break;
    case 4:
        v2 = IsScreenFadeDone();

        if (v2 == 1) {
            return 1;
        }
        break;
    }

    WiFiLobbyNews_Update(v0, v1->state);

    return 0;
}

int WiFiLobbyNews_Exit(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyNews *v0 = ApplicationManager_Data(appMan);
    WiFiPlazaLobbyNewsAppArgs *v1 = ApplicationManager_Args(appMan);

    WiFiLobbyNews_FreeLabels(&v0->labels);
    WiFiLobbyNews_FreeTimer(&v0->timer);
    WiFiLobbyNews_FreeHeadlines(&v0->headlines);
    WiFiLobbyNews_FreeTicker(&v0->ticker);
    WiFiLobbyNews_FreeScreenData(&v0->screenData);

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    WiFiLobbyNews_FreeGraphics(&v0->graphics);

    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_107);

    return 1;
}

static void WiFiLobbyNews_VBlankCallback(void *param0)
{
    WiFiLobbyNews *v0 = param0;
    WiFiLobbyNews_ProcessVBlank(&v0->graphics);
}

static void WiFiLobbyNews_Update(WiFiLobbyNews *param0, const WiFiPlazaLobbyState *param1)
{
    WiFiLobbyNews_DrawTimer(&param0->timer, &param0->screenData, &param0->graphics);
    WiFiLobbyNews_DrawHeadlines(&param0->headlines, &param0->screenData, &param0->graphics, param0->newsData, param1);
    WiFiLobbyNews_DrawTicker(&param0->ticker);
    WiFiLobbyNews_UpdateLabels(&param0->labels);
    WiFiLobbyNews_UpdateSprites(&param0->graphics);
}

static void WiFiLobbyNews_InitGraphics(WiFiLobbyNewsGraphics *param0, enum HeapID heapID)
{
    param0->narc = NARC_ctor(NARC_INDEX_GRAPHIC__LOBBY_NEWS, heapID);

    VramTransfer_New(48, heapID);
    GXLayers_SetBanks(&sGXBanks);

    WiFiLobbyNews_InitBackgrounds(param0, heapID);
    WiFiLobbyNews_InitSpriteSystem(param0, heapID);
}

static void WiFiLobbyNews_FreeGraphics(WiFiLobbyNewsGraphics *param0)
{
    NARC_dtor(param0->narc);
    VramTransfer_Free();

    WiFiLobbyNews_FreeBackgrounds(param0);
    WiFiLobbyNews_FreeSpriteSystem(param0);
}

static void WiFiLobbyNews_UpdateSprites(WiFiLobbyNewsGraphics *param0)
{
    SpriteList_Update(param0->spriteList);
}

static void WiFiLobbyNews_ProcessVBlank(WiFiLobbyNewsGraphics *param0)
{
    Bg_RunScheduledUpdates(param0->bgConfig);
    RenderOam_Transfer();
    VramTransfer_Process();
}

static void WiFiLobbyNews_InitBackgrounds(WiFiLobbyNewsGraphics *param0, enum HeapID heapID)
{
    SetAllGraphicsModes(&sGraphicsModes);

    param0->bgConfig = BgConfig_New(heapID);
    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;

    GXLayers_SwapDisplay();

    {
        int v0;

        for (v0 = 0; v0 < 5; v0++) {
            Bg_InitFromTemplate(param0->bgConfig, sBgLayers[v0], &sBgTemplates[v0], 0);
            Bg_ClearTilesRange(sBgLayers[v0], 32, 0, heapID);
            Bg_ClearTilemap(param0->bgConfig, sBgLayers[v0]);
        }
    }

    {
        Graphics_LoadPaletteFromOpenNARC(param0->narc, 0, 0, 0, 0, heapID);
        Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(10), heapID);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->narc, 1, param0->bgConfig, 1, 0, 0, 0, heapID);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->narc, 3, param0->bgConfig, 1, 0, 0, 0, heapID);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->narc, 4, param0->bgConfig, 2, 0, 0, 0, heapID);
    }

    {
        Graphics_LoadPaletteFromOpenNARC(param0->narc, 0, 4, 0, 0, heapID);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->narc, 2, param0->bgConfig, 4, 0, 0, 0, heapID);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->narc, 6, param0->bgConfig, 4, 0, 0, 0, heapID);
    }
}

static void WiFiLobbyNews_FreeBackgrounds(WiFiLobbyNewsGraphics *param0)
{
    {
        int v0;

        for (v0 = 0; v0 < 5; v0++) {
            Bg_FreeTilemapBuffer(param0->bgConfig, sBgLayers[v0]);
        }
    }

    Heap_Free(param0->bgConfig);
    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;
    GXLayers_SwapDisplay();
}

static void WiFiLobbyNews_InitSpriteSystem(WiFiLobbyNewsGraphics *param0, enum HeapID heapID)
{
    int i;

    NNS_G2dInitOamManagerModule();

    RenderOam_Init(0, 126, 0, 31, 0, 126, 0, 31, heapID);
    CharTransfer_InitWithVramModes(&sCharTransferTemplate, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_32K);
    PlttTransfer_Init(32, heapID);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_128K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    param0->spriteList = SpriteList_InitRendering(32, &param0->renderer, heapID);

    SetSubScreenViewRect(&param0->renderer, 0, FX32_CONST(256));

    for (i = 0; i < 4; i++) {
        param0->spriteResources[i] = SpriteResourceCollection_New(32, i, heapID);
    }

    NetworkIcon_Init();
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void WiFiLobbyNews_FreeSpriteSystem(WiFiLobbyNewsGraphics *param0)
{
    int v0;

    SpriteList_Delete(param0->spriteList);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(param0->spriteResources[v0]);
    }

    CharTransfer_Free();
    PlttTransfer_Free();
    RenderOam_Free();
}

static void WiFiLobbyNews_LoadScreenData(WiFiLobbyNewsScreenData *param0, WiFiLobbyNewsGraphics *param1, enum HeapID heapID)
{
    param0->rawData = Graphics_GetScrnDataFromOpenNARC(param1->narc, 5, 0, &param0->screenData, heapID);
}

static void WiFiLobbyNews_FreeScreenData(WiFiLobbyNewsScreenData *param0)
{
    Heap_Free(param0->rawData);
}

static void WiFiLobbyNews_DrawTimerTile(WiFiLobbyNewsScreenData *param0, WiFiLobbyNewsGraphics *param1, u32 param2, u8 param3, u8 param4)
{
    Bg_CopyToTilemapRect(param1->bgConfig, 3, 5 + (param3 * 1), 4 + (param4 * 2), 1, 2, param0->screenData->rawData, 6 + param2, 0, param0->screenData->screenWidth / 8, param0->screenData->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, 3);
}

static void WiFiLobbyNews_DrawHeadlineTile(WiFiLobbyNewsScreenData *param0, WiFiLobbyNewsGraphics *param1, u8 param2, u8 param3, u32 param4, u32 param5, BOOL param6, BOOL param7, BOOL param8)
{
    u32 v0 = param4 % 3;
    u32 v1 = param4 / 3;

    if (param7) {
        v1 += 2;
    }

    if (param5 == 1) {
        v1++;
    }

    Bg_CopyToTilemapRect(param1->bgConfig, 3, 21 + (param2 * 2), 4 + (param3 * 2), 2, 2, param0->screenData->rawData, 0 + (v0 * 2), 0 + (v1 * 2), param0->screenData->screenWidth / 8, param0->screenData->screenHeight / 8);

    if (param8) {
        Bg_ChangeTilemapRectPalette(param1->bgConfig, 3, 21 + (param2 * 2), 4 + (param3 * 2), 2, 2, 4);
    } else {
        if (param6) {
            Bg_ChangeTilemapRectPalette(param1->bgConfig, 3, 21 + (param2 * 2), 4 + (param3 * 2), 2, 2, 3);
        }
    }

    Bg_ScheduleTilemapTransfer(param1->bgConfig, 3);
}

static void WiFiLobbyNews_InitTimer(WiFiLobbyNewsTimer *param0, WiFiLobbyNewsGraphics *param1, WiFiLobbyNewsScreenData *param2, const WiFiPlazaLobbyNews *param3, const WiFiPlazaLobbyTime *param4, const WiFiPlazaLobbyState *param5, enum HeapID heapID)
{
    u32 v0;
    u32 v1;

    v0 = WiFiPlazaLobby_State_GetLobbyCloseTime(param5);
    v1 = v0 / 60;

    param0->time.hour = 0;
    param0->time.minute = v1 + 1;
    param0->time.second = 0;
    param0->unitsPerTile = v0 / (4 * 10);
    param0->active = 1;
    param0->frame = 0;
    param0->needsRedraw = 0;

    WiFiLobbyNews_UpdateTimer(param0, param3, param4);
    WiFiLobbyNews_DrawTimer(param0, param2, param1);
}

static void WiFiLobbyNews_FreeTimer(WiFiLobbyNewsTimer *param0)
{
    return;
}

static BOOL WiFiLobbyNews_UpdateTimer(WiFiLobbyNewsTimer *param0, const WiFiPlazaLobbyNews *param1, const WiFiPlazaLobbyTime *param2)
{
    BOOL v0;
    WiFiPlazaLobbyTime v1;
    WiFiPlazaLobbyTime v2;
    WiFiPlazaLobbyTime v3;
    BOOL v4 = 0;

    v0 = WiFiPlazaLobby_News_GetPlazaInfo(param1, &v1);

    if (v0 == 0) {
        return v4;
    }

    if (param0->active == 1) {
        param0->active = 0;
        param0->needsRedraw = 1;
        v4 = 1;
    }

    WiFiPlazaLobby_Time_Subtract(param2, &v1, &v2);
    WiFiPlazaLobby_Time_Subtract(&v2, &param0->time, &v3);

    if ((v3.second >= param0->unitsPerTile) || (v3.minute > 0) || (v3.hour > 0)) {
        param0->needsRedraw = 1;
        param0->time = v2;

        v4 = 1;
    }

    return v4;
}

static void WiFiLobbyNews_DrawTimer(WiFiLobbyNewsTimer *param0, WiFiLobbyNewsScreenData *param1, WiFiLobbyNewsGraphics *param2)
{
    if (param0->active == 1) {
        WiFiLobbyNews_AnimateTimer(param0, param1, param2);
    } else {
        WiFiLobbyNews_DrawTimerGrid(param0, param1, param2);
    }
}

static void WiFiLobbyNews_AnimateTimer(WiFiLobbyNewsTimer *param0, WiFiLobbyNewsScreenData *param1, WiFiLobbyNewsGraphics *param2)
{
    param0->frame++;

    if (16 < param0->frame) {
        param0->frame = 0;
    }
}

static void WiFiLobbyNews_DrawTimerGrid(WiFiLobbyNewsTimer *param0, WiFiLobbyNewsScreenData *param1, WiFiLobbyNewsGraphics *param2)
{
    int v0, v1;
    u32 v2;
    u16 v3;
    s32 v4, v5;
    s32 v6;

    v2 = param0->time.second;
    v2 += param0->time.minute * 60;
    v2 += param0->time.hour * 3600;
    v2 /= param0->unitsPerTile;

    if (param0->needsRedraw) {
        param0->frame = 0;
        param0->needsRedraw = 0;

        Bg_FillTilemapRect(param2->bgConfig, 3, 0, 5, 4, 10 * 1, 4 * 2, 0);
        Bg_ScheduleTilemapTransfer(param2->bgConfig, 3);

        for (v0 = 0; v0 < 4; v0++) {
            v5 = (4 - 1) - v0;

            for (v1 = 0; v1 < 10; v1++) {
                v4 = (10 - 1) - v1;
                v6 = ((v5 * 10) + v4);

                if (v6 >= v2) {
                    if (v6 == v2) {
                        v3 = 1;
                    } else if (v5 == (4 - 1)) {
                        v3 = 2;
                    } else {
                        v3 = 0;
                    }

                    WiFiLobbyNews_DrawTimerTile(param1, param2, v3, v4, v5);
                }
            }
        }
    } else {
        if (v2 < (4 * 10)) {
            u32 v7;
            u32 v8;
            u32 v9;

            param0->frame++;

            v7 = param0->frame % 32;
            v4 = v2 % 10;
            v5 = v2 / 10;

            if (v7 == 0) {
                v9 = (param0->unitsPerTile * 30) / 4;
                v8 = 6;

                for (v0 = 0; v0 < 4; v0++) {
                    if (v9 * (v0 + 1) > param0->frame) {
                        v8 = sTileIndices[v0].tileIndex;
                        break;
                    }
                }

                WiFiLobbyNews_DrawTimerTile(param1, param2, v8, v4, v5);
            } else if (v7 == (32 / 2)) {
                WiFiLobbyNews_DrawTimerTile(param1, param2, 3, v4, v5);
            }
        }
    }
}

static void WiFiLobbyNews_InitHeadlines(WiFiLobbyNewsHeadlines *param0, WiFiLobbyNewsGraphics *param1, WiFiLobbyNewsScreenData *param2, const WiFiPlazaLobbyNews *param3, const WiFiPlazaLobbyState *param4, enum HeapID heapID)
{
    WiFiLobbyNews_DrawHeadlineRow(param2, param1, param3, param4, 0);
}

static void WiFiLobbyNews_FreeHeadlines(WiFiLobbyNewsHeadlines *param0)
{
    return;
}

static BOOL WiFiLobbyNews_UpdateHeadlines(WiFiLobbyNewsHeadlines *param0, const WiFiPlazaLobbyNews *param1)
{
    u32 v0;
    BOOL v1 = 0;

    v0 = WiFiPlazaLobby_News_GetState(param1);

    switch (v0) {
    case WiFiPlazaLobbyNewsState_00:
        break;
    case WiFiPlazaLobbyNewsState_01:
        param0->state = 1;
        v1 = 1;
        break;
    case WiFiPlazaLobbyNewsState_02:
        param0->state = 3;
        v1 = 1;
        break;
    }

    return v1;
}

static void WiFiLobbyNews_DrawHeadlines(WiFiLobbyNewsHeadlines *param0, WiFiLobbyNewsScreenData *param1, WiFiLobbyNewsGraphics *param2, const WiFiPlazaLobbyNews *param3, const WiFiPlazaLobbyState *param4)
{
    switch (param0->state) {
    case 0:
        break;
    case 1:
        param0->state = 2;
        param0->frame = 0;
        break;
    case 2:
        WiFiLobbyNews_AnimateHeadlineRowA(param1, param2, param3, param4, param0->frame);
        param0->frame++;

        if (param0->frame >= 32) {
            param0->state = 0;
        }
        break;
    case 3:
        param0->state = 4;
        param0->frame = 0;
        break;
    case 4:
        WiFiLobbyNews_AnimateHeadlineRowB(param1, param2, param3, param4, param0->frame);
        param0->frame++;

        if (param0->frame >= 32) {
            param0->state = 0;
        }

        break;
    }
}

static void WiFiLobbyNews_DrawHeadlineRow(WiFiLobbyNewsScreenData *param0, WiFiLobbyNewsGraphics *param1, const WiFiPlazaLobbyNews *param2, const WiFiPlazaLobbyState *param3, u32 param4)
{
    int v0, v1;
    u32 v2;
    BOOL v3;
    BOOL v4;
    BOOL v5;
    BOOL v6;
    BOOL v7;
    u32 v8;
    u32 v9;

    Bg_FillTilemapRect(param1->bgConfig, 3, 0, 21, 4, 5 * 2, 4 * 2, 0);

    for (v0 = 0; v0 < 4; v0++) {
        for (v1 = 0; v1 < 5; v1++) {
            v8 = (v0 * 5) + v1;
            v6 = WiFiPlazaLobby_News_IsResultSet(param2, v8);

            if (v6) {
                v2 = WiFiPlazaLobby_News_GetResult(param2, v8);
                v3 = WiFiPlazaLobby_News_HasResultFlag(param2, v8);
                v4 = WiFiPlazaLobby_News_HasNewResultFlag(param2, v8);
                v5 = WiFiPlazaLobby_News_IsCurrentResult(param2, v8);
                v7 = WiFiPlazaLobby_State_IsMemberPresent(param3, v8);

                if ((param4 == 2) && (v5 == 1)) {
                    v9 = 0;
                } else {
                    v9 = param4;
                }

                WiFiLobbyNews_DrawHeadlineTile(param0, param1, v1, v0, v9, v2, v3, v4, v7);
            }
        }
    }
}

static void WiFiLobbyNews_AnimateHeadlineRowA(WiFiLobbyNewsScreenData *param0, WiFiLobbyNewsGraphics *param1, const WiFiPlazaLobbyNews *param2, const WiFiPlazaLobbyState *param3, u32 param4)
{
    u32 v0;

    if ((param4 % (32 / 4)) == 0) {
        v0 = param4 / (32 / 4);

        if ((v0 % 2) == 0) {
            v0 = 2;
        } else {
            v0 = 0;
        }

        WiFiLobbyNews_DrawHeadlineRow(param0, param1, param2, param3, v0);
    }
}

static void WiFiLobbyNews_AnimateHeadlineRowB(WiFiLobbyNewsScreenData *param0, WiFiLobbyNewsGraphics *param1, const WiFiPlazaLobbyNews *param2, const WiFiPlazaLobbyState *param3, u32 param4)
{
    u32 v0;

    if ((param4 % (32 / 4)) == 0) {
        v0 = param4 / (32 / 4);

        if ((v0 % 2) == 0) {
            v0 = 1;
        } else {
            v0 = 0;
        }

        WiFiLobbyNews_DrawHeadlineRow(param0, param1, param2, param3, v0);
    }
}

static void WiFiLobbyNews_SetTrainerColors(WiFiLobbyNewsTrainerColors *param0, const WiFiPlazaLobbyNews *param1, int param2, const WiFiPlazaLobbyState *param3)
{
    int v0;
    u32 v1;
    BOOL v2;

    for (v0 = 0; v0 < 4; v0++) {
        v1 = WiFiPlazaLobby_News_GetHeadlineValue(param1, param2, v0);

        if (v1 != 20) {
            v2 = WiFiPlazaLobby_State_IsMemberPresent(param3, v1);

            if (v2 == 1) {
                param0->colors[v0] = 9;
            } else {
                param0->colors[v0] = 5;
            }
        }
    }
}

static void WiFiLobbyNews_LoadTrainerPalette(const WiFiLobbyNewsTrainerColors *param0, const NNSG2dPaletteData *param1, u32 param2)
{
    BOOL v0;
    int v1;
    const u8 *v2 = param1->pRawData;

    for (v1 = 0; v1 < 4; v1++) {
        v0 = VramTransfer_Request(NNS_GFD_DST_2D_BG_PLTT_MAIN, (param2 * 0x20) + (5 * 2) + (v1 * 0x4), (void *)(&v2[(7 * 0x20) + (param0->colors[v1] * 2)]), 0x4);
        GF_ASSERT(v0);
    }
}

static void WiFiLobbyNews_InitTicker(WiFiLobbyNewsTicker *param0, WiFiLobbyNewsGraphics *param1, enum HeapID heapID)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        WiFiLobbyNews_InitTickerEntry(&param0->entries[v0], param1, v0, heapID);

        Window_Add(param1->bgConfig, &param0->windows[v0], 3, 1, sTickerWindowTops[v0], 30, 2, 7 + v0, 0x300 + ((30 * 2) * v0));
        Window_FillTilemap(&param0->windows[v0], 0);
        Window_ScheduleCopyToVRAM(&param0->windows[v0]);
    }

    param0->text = String_Init(256, heapID);
    param0->paletteRaw = Graphics_GetPlttDataFromOpenNARC(param1->narc, 0, &param0->palette, heapID);

    Bg_LoadPalette(BG_LAYER_MAIN_0, &((u8 *)param0->palette->pRawData)[(7 * 0x20) + (7 * 2)], 0x4, (7 * 0x20) + (13 * 2));
    Bg_LoadPalette(BG_LAYER_MAIN_0, &((u8 *)param0->palette->pRawData)[(7 * 0x20) + (7 * 2)], 0x4, (8 * 0x20) + (13 * 2));
    Bg_LoadPalette(BG_LAYER_MAIN_0, &((u8 *)param0->palette->pRawData)[(7 * 0x20) + (7 * 2)], 0x4, (9 * 0x20) + (13 * 2));
}

static void WiFiLobbyNews_FreeTicker(WiFiLobbyNewsTicker *param0)
{
    int v0;

    Heap_Free(param0->paletteRaw);
    String_Free(param0->text);

    for (v0 = 0; v0 < 3; v0++) {
        Window_Remove(&param0->windows[v0]);
        WiFiLobbyNews_FreeTickerEntry(&param0->entries[v0]);
    }
}

static BOOL WiFiLobbyNews_UpdateTicker(WiFiLobbyNewsTicker *param0, WiFiPlazaLobbyNews *param1, const WiFiPlazaLobbyState *param2, enum HeapID heapID)
{
    int v0;
    BOOL v1;
    int v2;
    WiFiLobbyNewsTrainerColors v3;
    WiFiPlazaLobbyNewsPlayerFlags v4;

    WiFiPlazaLobby_State_GetMemberPresentBitmap(param2, &v4);

    for (v0 = 3 - 1; v0 >= 0; v0--) {
        if (param0->entries[v0].active) {
            v1 = WiFiLobbyNews_AdvanceTickerEntry(&param0->entries[v0]);

            if (v1 == 1) {
                if ((v0 + 1) < 3) {
                    WiFiLobbyNews_SetTickerEntry(&param0->entries[v0 + 1], param0->entries[v0].text, sTickerDurations[v0 + 1], &param0->entries[v0].trainerColors, param0->palette);
                }

                WiFiLobbyNews_ClearTickerEntry(&param0->entries[v0]);
            }
        }
    }

    if (param0->entries[0].active == 0) {
        while (WiFiPlazaLobby_News_HasHeadline(param1) == 1) {
            v2 = WiFiPlazaLobby_News_GetHeadlineType(param1);
            v1 = WiFiPlazaLobby_News_FormatHeadline(param1, &v4, v2, param0->text, heapID);

            if (v1 == 1) {
                WiFiLobbyNews_SetTrainerColors(&v3, param1, v2, param2);
                WiFiLobbyNews_SetTickerEntry(&param0->entries[0], param0->text, sTickerDurations[0], &v3, param0->palette);
                WiFiPlazaLobby_News_ClearQueue(param1);
                return 1;
            }

            WiFiPlazaLobby_News_ClearQueue(param1);
        }
    }

    return 0;
}

static void WiFiLobbyNews_DrawTicker(WiFiLobbyNewsTicker *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        if (param0->entries[v0].active == 1) {
            WiFiLobbyNews_ScrollTickerEntry(&param0->entries[v0], &param0->windows[v0]);
        }
    }
}

static void WiFiLobbyNews_InitTickerEntry(WiFiLobbyNewsTickerEntry *param0, WiFiLobbyNewsGraphics *param1, u32 param2, enum HeapID heapID)
{
    param0->active = 0;
    param0->scrollProgress = 0;
    param0->text = String_Init(256, heapID);
    param0->paletteOffset = 7 + param2;

    Window_Add(param1->bgConfig, &param0->window, 3, 0, 0, 180, 2, 7, 0);
}

static void WiFiLobbyNews_FreeTickerEntry(WiFiLobbyNewsTickerEntry *param0)
{
    String_Free(param0->text);
    Window_Remove(&param0->window);
}

static void WiFiLobbyNews_SetTickerEntry(WiFiLobbyNewsTickerEntry *param0, const String *param1, u32 param2, const WiFiLobbyNewsTrainerColors *param3, const NNSG2dPaletteData *param4)
{
    String_Copy(param0->text, param1);

    param0->active = 1;
    param0->scrollProgress = 0;
    param0->duration = param2;
    param0->textWidth = Font_CalcStringWidth(FONT_MESSAGE, param1, 0);
    param0->textWidth += 256;

    GF_ASSERT((180 * 8) >= param0->textWidth);

    Window_FillTilemap(&param0->window, 0);
    Text_AddPrinterWithParams(&param0->window, FONT_MESSAGE, param0->text, 0, 0, TEXT_SPEED_NO_TRANSFER, NULL);

    param0->trainerColors = *param3;

    WiFiLobbyNews_LoadTrainerPalette(&param0->trainerColors, param4, param0->paletteOffset);
}

static void WiFiLobbyNews_ClearTickerEntry(WiFiLobbyNewsTickerEntry *param0)
{
    param0->active = 0;
}

static BOOL WiFiLobbyNews_AdvanceTickerEntry(WiFiLobbyNewsTickerEntry *param0)
{
    BOOL v0 = 1;

    if ((param0->scrollProgress + 1) <= param0->duration) {
        param0->scrollProgress++;
        v0 = 0;
    }

    return v0;
}

static void WiFiLobbyNews_ScrollTickerEntry(const WiFiLobbyNewsTickerEntry *param0, Window *param1)
{
    s32 v0;
    s32 v1;
    s32 v2;
    s32 v3;

    v0 = (param0->scrollProgress * param0->textWidth) / param0->duration;

    if (v0 < 256) {
        v1 = 255 - v0;
        v2 = 0;
        v3 = v0;
    } else {
        v1 = 0;
        v2 = v0 - 256;
        v3 = (param0->textWidth - v0);

        if (v3 > 255) {
            v3 = 255;
        }
    }

    Window_FillRectWithColor(param1, 0, 0, 0, 255, 2 * 8);
    Window_BlitBitmapRectWithTransparency(param1, param0->window.pixels, v2, 0, 180 * 8, 2 * 8, v1, 0, v3, 2 * 8, 15);
    Window_ScheduleCopyToVRAM(param1);
}

static void WiFiLobbyNews_InitLabels(WiFiLobbyNewsLabels *param0, WiFiLobbyNewsGraphics *param1, enum HeapID heapID)
{
    int v0;
    MessageLoader *v1;
    String *v2;
    u32 v3;
    String *v4;
    u32 v5;
    u32 v6, v7;

    memset(param0, 0, sizeof(WiFiLobbyNewsLabels));

    v1 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0653, heapID);
    v2 = String_Init(128, heapID);

    for (v0 = 0; v0 < 4; v0++) {
        WiFiLobbyNews_InitLabelFlash(&param0->flashes[v0], sLabelPaletteOffsets[v0], sLabelSoundEffects[v0]);

        Window_Add(param1->bgConfig, &param0->windows[v0], 0, sLabelTemplates[v0].tilemapLeft, sLabelTemplates[v0].tilemapTop, sLabelTemplates[v0].width, sLabelTemplates[v0].height, sLabelTemplates[v0].palette, sLabelTemplates[v0].baseTile);

        Window_FillTilemap(&param0->windows[v0], 0);

        MessageLoader_GetString(v1, 0 + v0, v2);

        v3 = String_NumLines(v2);
        v7 = sLabelTemplates[v0].textY;
        v4 = String_Init(String_Length(v2) + 1, heapID);
        for (v5 = 0; v5 < v3; v5++) {
            String_CopyLineNum(v4, v2, v5);
            switch (sLabelTemplates[v0].alignment) {
            case 0:
                v6 = sLabelTemplates[v0].textX;
                break;
            case 1:
                v6 = sLabelTemplates[v0].textX - (Font_CalcMaxLineWidth(0, v4, 0) + 1) / 2;
                break;
            case 2:
                v6 = sLabelTemplates[v0].textX - Font_CalcMaxLineWidth(0, v4, 0);
                break;
            }
            Text_AddPrinterWithParamsAndColor(&param0->windows[v0], FONT_SYSTEM, v4, v6, v7, TEXT_SPEED_NO_TRANSFER, sLabelTemplates[v0].textColor, NULL);
            v7 += 16;
        }
        String_Free(v4);

        Window_ScheduleCopyToVRAM(&param0->windows[v0]);
    }
    String_Free(v2);
    MessageLoader_Free(v1);
}

static void WiFiLobbyNews_FreeLabels(WiFiLobbyNewsLabels *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        Window_Remove(&param0->windows[v0]);
        WiFiLobbyNews_FreeLabelFlash(&param0->flashes[v0]);
    }
}

static void WiFiLobbyNews_UpdateLabels(WiFiLobbyNewsLabels *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        WiFiLobbyNews_UpdateLabelFlash(&param0->flashes[v0]);
    }
}

static void WiFiLobbyNews_FlashLabel(WiFiLobbyNewsLabels *param0, u32 param1)
{
    GF_ASSERT(param1 < 4);
    GF_ASSERT(param1 != 0);

    WiFiLobbyNews_StartLabelFlash(&param0->flashes[param1]);
}

static void WiFiLobbyNews_InitLabelFlash(WiFiLobbyNewsLabelFlash *param0, u16 param1, u32 param2)
{
    memset(param0, 0, sizeof(WiFiLobbyNewsLabelFlash));
    param0->paletteOffset = param1;
    param0->soundEffect = param2;
}

static void WiFiLobbyNews_FreeLabelFlash(WiFiLobbyNewsLabelFlash *param0)
{
    memset(param0, 0, sizeof(WiFiLobbyNewsLabelFlash));
}

static void WiFiLobbyNews_StartLabelFlash(WiFiLobbyNewsLabelFlash *param0)
{
    param0->active = 1;
    param0->frame = 0;
}

static void WiFiLobbyNews_UpdateLabelFlash(WiFiLobbyNewsLabelFlash *param0)
{
    u32 v0;
    u16 v1;

    if (param0->frame > 28) {
        param0->active = 0;
    }

    if (param0->active == 0) {
        return;
    }

    if (param0->frame == 0) {
        Sound_PlayEffect(param0->soundEffect);
    }

    if (param0->frame < 2) {
        v0 = (param0->frame * 16) / 2;
    } else if (param0->frame < 2 + 12) {
        v0 = 16;
    } else {
        v0 = ((param0->frame - (2 + 12)) * 16) / (28 - (2 + 12));
        v0 = 16 - v0;
    }

    v1 = 0xe;

    BlendPalette(&v1, &param0->color, 1, v0, 0x19);
    DC_FlushRange(&param0->color, 2);
    GX_LoadBGPltt(&param0->color, param0->paletteOffset, 2);

    param0->frame++;
}
