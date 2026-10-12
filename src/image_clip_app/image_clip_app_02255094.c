#include "image_clip_app/image_clip_app_02255094.h"

#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"

#include "image_clip_app/struct_image_clip_app_02255CB8.h"
#include "image_clip_app/struct_image_clip_app_0225A0E4.h"

#include "bg_window.h"
#include "char_transfer.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "narc.h"
#include "pltt_transfer.h"
#include "pokemon_sprite.h"
#include "render_oam.h"
#include "resource_collection.h"
#include "software_sprite.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "system.h"
#include "g3_buffer.h"

static void ImageClipGraphics_InitBanks(void);
static void ImageClipGraphics_Init3D(void);
static void ImageClipGraphics_InitDisplayModes(void);
static void ImageClipGraphics_ResetVram(void);
static void ImageClipGraphics_ResetLayers(void);
static void ImageClipGraphics_InitSoftwareSprites(ImageClipGraphics *param0, const SoftwareSpriteManagerTemplate *param1);
static void ImageClipGraphics_FreeSoftwareSprites(ImageClipGraphics *param0);
static void ImageClipGraphics_DrawSoftwareSprites(ImageClipGraphics *param0);
static void ImageClipGraphics_InitPokemonSprites(ImageClipGraphics *param0, enum HeapID heapID, int param2, int param3);
static void ImageClipGraphics_FreePokemonSprites(ImageClipGraphics *param0);
static void ImageClipGraphics_LoadExtraResource(ImageClipGraphics *param0, enum HeapID heapID);
static void ImageClipGraphics_FreeExtraResource(ImageClipGraphics *param0);
static void ImageClipGraphics_InitSpriteSystem(ImageClipGraphics *param0);
static void ImageClipGraphics_FreeSpriteSystem(ImageClipGraphics *param0);
static void ImageClipGraphics_UpdateSpriteList(ImageClipGraphics *param0);
static void ImageClipGraphics_InitCharacterCollection(ImageClipGraphics *param0);
static void ImageClipGraphics_FreeCharacterCollection(ImageClipGraphics *param0);
static void ImageClipGraphics_LoadChars(ImageClipGraphics *param0, SoftwareSpriteCharsTemplate *param1, int param2);
static void ImageClipGraphics_LoadPalettes(ImageClipGraphics *param0, SoftwareSpritePaletteTemplate *param1, int param2);
static void ImageClipGraphics_InitBackgrounds(ImageClipGraphics *param0);
static void ImageClipGraphics_FreeBackgrounds(ImageClipGraphics *param0);
static void ImageClipGraphics_InitTemplateArrays(ImageClipGraphicsTemplates *param0, int param1, int param2, enum HeapID heapID);
static void ImageClipGraphics_FreeTemplateArrays(ImageClipGraphicsTemplates *param0);
static void ImageClipGraphics_LoadAccessoryData(ImageClipGraphics *param0, ImageClipGraphicsTemplates *param1);
static void ImageClipGraphics_LoadBackdropData(ImageClipGraphics *param0, ImageClipGraphicsTemplates *param1);

void ImageClipGraphics_Init(void)
{
    ImageClipGraphics_InitBanks();
    ImageClipGraphics_Init3D();
    ImageClipGraphics_InitDisplayModes();

    gSystem.whichScreenIs3D = DS_SCREEN_SUB;

    GXLayers_SwapDisplay();
}

void ImageClipGraphics_Free(void)
{
    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;

    GXLayers_SwapDisplay();
    ImageClipGraphics_ResetLayers();
    ImageClipGraphics_ResetVram();

    GX_ResetBankForTex();
}

void ImageClipGraphics_InitManager(ImageClipGraphics *param0)
{
    SoftwareSpriteManagerTemplate v0 = {
        .numSprites = 718,
        .numChars = 118,
        .numPalettes = 19,
        .heapID = HEAP_ID_14
    };

    param0->narc = NARC_ctor(NARC_INDEX_GRAPHIC__IMAGECLIP, HEAP_ID_14);

    ImageClipGraphics_InitSoftwareSprites(param0, &v0);
    ImageClipGraphics_InitPokemonSprites(param0, HEAP_ID_14, 0x2800, 0x20);
    ImageClipGraphics_InitCharacterCollection(param0);
    ImageClipGraphics_LoadExtraResource(param0, HEAP_ID_13);
    ImageClipGraphics_InitSpriteSystem(param0);

    param0->bgConfig = BgConfig_New(HEAP_ID_14);

    ImageClipGraphics_InitBackgrounds(param0);
}

void ImageClipGraphics_FreeManager(ImageClipGraphics *param0)
{
    ImageClipGraphics_FreeExtraResource(param0);
    ImageClipGraphics_FreeSoftwareSprites(param0);
    ImageClipGraphics_FreeBackgrounds(param0);

    Heap_Free(param0->bgConfig);

    ImageClipGraphics_FreePokemonSprites(param0);
    ImageClipGraphics_FreeSpriteSystem(param0);
    ImageClipGraphics_FreeCharacterCollection(param0);

    NARC_dtor(param0->narc);
    Heap_Free(param0->chars);
    param0->chars = NULL;
    Heap_Free(param0->palettes);
    param0->palettes = NULL;
}

void ImageClipGraphics_Render(ImageClipGraphics *param0)
{
    G3_ResetG3X();

    NNS_G2dSetupSoftwareSpriteCamera();

    if (param0->drawSoftwareSprites) {
        ImageClipGraphics_DrawSoftwareSprites(param0);
    }

    if (param0->drawPokemonSprites) {
        PokemonSpriteManager_DrawSprites(param0->pokemonSpriteManager);
    }

    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
    ImageClipGraphics_UpdateSpriteList(param0);
}

void ImageClipGraphics_LoadTemplates(ImageClipGraphics *param0, ImageClipGraphicsTemplates *param1)
{
    ImageClipGraphics_LoadChars(param0, param1->chars, param1->charCount);
    ImageClipGraphics_LoadPalettes(param0, param1->palettes, param1->paletteCount);
}

void ImageClipGraphics_FreeAllSprites(ImageClipGraphics *param0)
{
    SoftwareSpriteManager_FreeAllChars(param0->softSpriteManager);
    SoftwareSpriteManager_FreeAllPalettes(param0->softSpriteManager);
}

Sprite *ImageClipGraphics_AddSprite(ImageClipGraphics *param0, int param1, int param2, int param3, int param4, int param5)
{
    SpriteResourcesHeader v0;
    SpriteListTemplate v1;

    SpriteResourcesHeader_Init(&v0, param1, param1, param1, param1, 0xffffffff, 0xffffffff, 0, 0, param0->spriteResourceCollections[0], param0->spriteResourceCollections[1], param0->spriteResourceCollections[2], param0->spriteResourceCollections[3], NULL, NULL);

    v1.list = param0->spriteList;
    v1.resourceData = &v0;
    v1.position.x = param2 << FX32_SHIFT;
    v1.position.y = param3 << FX32_SHIFT;
    v1.position.z = 0;
    v1.priority = param4;
    v1.vramType = param5;
    v1.heapID = HEAP_ID_14;

    return SpriteList_Add(&v1);
}

void ImageClipGraphics_LoadTiles(ImageClipGraphics *param0, NARC *param1, int param2, BOOL param3, int param4, int param5)
{
    SpriteResource *v0 = SpriteResourceCollection_AddTilesFrom(param0->spriteResourceCollections[0], param1, param2, param3, param5, param4, HEAP_ID_14);
    SpriteTransfer_RequestCharAtEnd(v0);
}

void ImageClipGraphics_LoadPalette(ImageClipGraphics *param0, NARC *param1, int param2, BOOL param3, int param4, int param5, int param6)
{
    SpriteResource *v0 = SpriteResourceCollection_AddPaletteFrom(param0->spriteResourceCollections[1], param1, param2, param3, param6, param4, param5, HEAP_ID_14);
    SpriteTransfer_RequestPlttFreeSpace(v0);
}

void ImageClipGraphics_LoadCell(ImageClipGraphics *param0, NARC *param1, int param2, BOOL param3, int param4)
{
    SpriteResourceCollection_AddFrom(param0->spriteResourceCollections[2], param1, param2, param3, param4, 2, HEAP_ID_14);
}

void ImageClipGraphics_LoadAnim(ImageClipGraphics *param0, NARC *param1, int param2, BOOL param3, int param4)
{
    SpriteResourceCollection_AddFrom(param0->spriteResourceCollections[3], param1, param2, param3, param4, 3, HEAP_ID_14);
}

void ImageClipGraphics_RemoveTiles(ImageClipGraphics *param0, int param1)
{
    SpriteResource *v0 = SpriteResourceCollection_Find(param0->spriteResourceCollections[0], param1);
    SpriteResourceCollection_Remove(param0->spriteResourceCollections[0], v0);
}

void ImageClipGraphics_RemovePalette(ImageClipGraphics *param0, int param1)
{
    SpriteResource *v0 = SpriteResourceCollection_Find(param0->spriteResourceCollections[1], param1);
    SpriteResourceCollection_Remove(param0->spriteResourceCollections[1], v0);
}

void ImageClipGraphics_RemoveCell(ImageClipGraphics *param0, int param1)
{
    SpriteResource *v0 = SpriteResourceCollection_Find(param0->spriteResourceCollections[2], param1);
    SpriteResourceCollection_Remove(param0->spriteResourceCollections[2], v0);
}

void ImageClipGraphics_RemoveAnim(ImageClipGraphics *param0, int param1)
{
    SpriteResource *v0 = SpriteResourceCollection_Find(param0->spriteResourceCollections[3], param1);
    SpriteResourceCollection_Remove(param0->spriteResourceCollections[3], v0);
}

void ImageClipGraphics_LoadImageResources(ImageClipGraphics *param0, ImageClipGraphicsTemplates *param1)
{
    ImageClipGraphics_InitTemplateArrays(param1, 100 + 18, 1 + 18, HEAP_ID_14);
    ImageClipGraphics_LoadAccessoryData(param0, param1);
    ImageClipGraphics_LoadBackdropData(param0, param1);
}

void ImageClipGraphics_FreeResourceTemplates(ImageClipGraphicsTemplates *param0)
{
    ImageClipGraphics_FreeTemplateArrays(param0);
}

NNSG2dCharacterData *ImageClipGraphics_AddCharacterData(ImageClipGraphics *param0, void *param1, int param2)
{
    ResourceCollection_Add(param0->characterCollection, param1, param2);
    NNS_G2dGetUnpackedCharacterData(param1, &param0->characterData[param2]);

    return param0->characterData[param2];
}

void ImageClipGraphics_DisableWindow(void)
{
    GX_SetVisibleWnd(GX_WNDMASK_NONE);
    G2_SetBG0Priority(1);
    G2_SetBG1Priority(0);
}

void ImageClipGraphics_EnableWindow(void)
{
    GX_SetVisibleWnd(GX_WNDMASK_W0);
    G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 0);
    G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_OBJ, 0);
    G2_SetWnd0Position(8 + 2, 16 + 2, (136 + 2) + (112 - (2 * 2)), (16 + 2) + (129 - (2 * 2)));
    G2_SetBG0Priority(0);
    G2_SetBG1Priority(1);
}

void ImageClipGraphics_Update(ImageClipGraphics *param0)
{
    Bg_RunScheduledUpdates(param0->bgConfig);
    PokemonSpriteManager_UpdateCharAndPltt(param0->pokemonSpriteManager);
    RenderOam_Transfer();
}

void ImageClipGraphics_InitResourceTemplates(ImageClipGraphicsTemplates *param0, enum HeapID heapID)
{
    ImageClipGraphics_InitTemplateArrays(param0, 100 + 18, 1 + 18, heapID);
}

int ImageClipGraphics_TestPixel(NNSG2dCharacterData *param0, int param1, int param2, int param3)
{
    u32 *v0;
    int v1, v2;
    int v3;
    int v4;

    v1 = param0->W;
    v2 = param0->H;
    v1 *= 8;
    v2 *= 8;

    if ((param1 < 0) || (param2 < 0) || (param1 >= v1) || (param2 >= v2)) {
        return 2;
    }

    v0 = param0->pRawData;
    v3 = (param2 * v1) + param1;
    v4 = (v3 % 8);
    v3 /= 8;

    if ((v0[v3] & (0xf << (v4 * 4))) == (param3 << (v4 * 4))) {
        return 1;
    }

    return 0;
}

void ImageClipGraphics_InitSpriteManager(ImageClipGraphics *param0, const SoftwareSpriteManagerTemplate *param1, enum HeapID heapID)
{
    ImageClipGraphics_InitSoftwareSprites(param0, param1);
    ImageClipGraphics_InitPokemonSprites(param0, heapID, 0x2800, 0x20);
    PokemonSpriteManager_SetExcludeIdentity(param0->pokemonSpriteManager, 1);
    ImageClipGraphics_LoadExtraResource(param0, heapID);
}

void ImageClipGraphics_InitBackground(ImageClipGraphics *param0, BgConfig *param1, int param2)
{
    param0->bgConfig = param1;

    {
        BgTemplate v0 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x04000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_2);
        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_MAIN_2, &v0, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_2, 32, 0, param2);
        Bg_ClearTilemap(param0->bgConfig, BG_LAYER_MAIN_2);
    }
}

void ImageClipGraphics_FreeSprites(ImageClipGraphics *param0)
{
    ImageClipGraphics_FreeExtraResource(param0);
    ImageClipGraphics_FreeSoftwareSprites(param0);
    ImageClipGraphics_FreePokemonSprites(param0);

    Heap_Free(param0->chars);
    param0->chars = NULL;

    Heap_Free(param0->palettes);
    param0->palettes = NULL;
}

void ImageClipGraphics_FreeBackground(ImageClipGraphics *param0)
{
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_2);
}

void ImageClipGraphics_UpdatePokemonSprites(ImageClipGraphics *param0)
{
    PokemonSpriteManager_UpdateCharAndPltt(param0->pokemonSpriteManager);
}

void ImageClipGraphics_DrawTransformed(ImageClipGraphics *param0, int param1, int param2, u16 param3, const VecFx32 *param4)
{
    G3_Identity();
    G3_PushMtx();

    {
        NNS_G2dSetupSoftwareSpriteCamera();
        G3_Translate(param1 * FX32_ONE, param2 * FX32_ONE, 0);

        {
            G3_RotZ(FX_SinIdx(param3), FX_CosIdx(param3));
            G3_Scale(param4->x, param4->y, param4->z);
        }

        G3_Translate(-param1 * FX32_ONE, -param2 * FX32_ONE, 0);
        G3_PushMtx();

        {
            if (param0->drawSoftwareSprites) {
                ImageClipGraphics_DrawSoftwareSprites(param0);
            }

            if (param0->drawPokemonSprites) {
                PokemonSpriteManager_DrawSprites(param0->pokemonSpriteManager);
            }
        }
        G3_PopMtx(1);
    }
    G3_PopMtx(1);
}

void ImageClipGraphics_InitNarc(ImageClipGraphics *param0, int param1)
{
    param0->narc = NARC_ctor(NARC_INDEX_GRAPHIC__IMAGECLIP, HEAP_ID_14);
    ImageClipGraphics_InitSpriteSystem(param0);
    param0->bgConfig = BgConfig_New(HEAP_ID_14);
    ImageClipGraphics_InitBackgrounds(param0);
}

void ImageClipGraphics_FreeNarc(ImageClipGraphics *param0)
{
    ImageClipGraphics_FreeBackgrounds(param0);
    Heap_Free(param0->bgConfig);
    NARC_dtor(param0->narc);
    ImageClipGraphics_FreeSpriteSystem(param0);
}

void ImageClipGraphics_Flush(ImageClipGraphics *param0)
{
    Bg_RunScheduledUpdates(param0->bgConfig);
    RenderOam_Transfer();
}

void ImageClipGraphics_UpdateSprites(ImageClipGraphics *param0)
{
    ImageClipGraphics_UpdateSpriteList(param0);
}

static void ImageClipGraphics_InitBanks(void)
{
    GXBanks v0 = {
        GX_VRAM_BG_128_C,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_32_H,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_32_FG,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_01_AB,
        GX_VRAM_TEXPLTT_0123_E
    };

    GXLayers_SetBanks(&v0);
}

static void ImageClipGraphics_Init3D(void)
{
    NNS_G3dInit();
    G3X_InitMtxStack();

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);

    G2_SetBG0Priority(1);
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(1);
    G3X_AlphaTest(0, 0);
    G3X_AlphaBlend(1);
    G3X_SetClearColor(GX_RGB(0, 0, 0), 0, 0x7fff, 63, 0);
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);
    G3_ViewPort(0, 0, 255, 191);

    NNS_GfdInitFrmTexVramManager(2, 1);
    NNS_GfdInitFrmPlttVramManager(0x4000, 1);
}

static void ImageClipGraphics_InitDisplayModes(void)
{
    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_3D
        };

        SetAllGraphicsModes(&v0);
    }

    GX_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);
    NNS_G2dInitOamManagerModule();

    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_OBJ, 1);
}

static void ImageClipGraphics_ResetVram(void)
{
    NNS_GfdResetFrmTexVramState();
    NNS_GfdResetFrmPlttVramState();
}

static void ImageClipGraphics_ResetLayers(void)
{
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();

    NNS_G2dInitOamManagerModule();
}

static void ImageClipGraphics_InitSoftwareSprites(ImageClipGraphics *param0, const SoftwareSpriteManagerTemplate *param1)
{
    param0->softSpriteManager = SoftwareSpriteManager_New(param1);
    param0->chars = Heap_Alloc(param1->heapID, sizeof(SoftwareSpriteChars *) * (100 + 18));
    param0->charsCapacity = (100 + 18);
    param0->charsCount = 0;
    param0->palettes = Heap_Alloc(param1->heapID, sizeof(SoftwareSpritePalette *) * (1 + 18));
    param0->palettesCapacity = (1 + 18);
    param0->palettesCount = 0;
    param0->drawSoftwareSprites = 1;
}

static void ImageClipGraphics_FreeSoftwareSprites(ImageClipGraphics *param0)
{
    SoftwareSpriteManager_Free(param0->softSpriteManager);
    param0->softSpriteManager = NULL;
}

static void ImageClipGraphics_DrawSoftwareSprites(ImageClipGraphics *param0)
{
    SoftwareSpriteManager_DrawVisible(param0->softSpriteManager);
}

static void ImageClipGraphics_LoadChars(ImageClipGraphics *param0, SoftwareSpriteCharsTemplate *param1, int param2)
{
    int v0;

    for (v0 = 0; v0 < param2; v0++) {
        GF_ASSERT(param0->charsCount < param0->charsCapacity);

        if (param1[v0].charsData != NULL) {
            param0->chars[param0->charsCount] = SoftwareSprite_LoadChars(param1 + v0);
        } else {
            param0->chars[param0->charsCount] = NULL;
        }

        param0->charsCount++;
    }
}

static void ImageClipGraphics_LoadPalettes(ImageClipGraphics *param0, SoftwareSpritePaletteTemplate *param1, int param2)
{
    int v0;

    for (v0 = 0; v0 < param2; v0++) {
        GF_ASSERT(param0->palettesCount < param0->palettesCapacity);

        if (param1[v0].paletteData != NULL) {
            param0->palettes[param0->palettesCount] = SoftwareSprite_LoadPalette(param1 + v0);
        } else {
            param0->palettes[param0->palettesCount] = NULL;
        }

        param0->palettesCount++;
    }
}

static void ImageClipGraphics_InitBackgrounds(ImageClipGraphics *param0)
{
    {
        BgTemplate v0 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_MAIN_1, &v0, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_1, 32, 0, HEAP_ID_14);
        Bg_ClearTilemap(param0->bgConfig, BG_LAYER_MAIN_1);
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x04000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_MAIN_2, &v1, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_2, 32, 0, HEAP_ID_14);
        Bg_ClearTilemap(param0->bgConfig, BG_LAYER_MAIN_2);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = -(16 + 129),
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe800,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_MAIN_3, &v2, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_3, 32, 0, HEAP_ID_14);
        Bg_ClearTilemap(param0->bgConfig, BG_LAYER_MAIN_3);
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x7800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_SUB_0, &v3, 0);
        Bg_ClearTilesRange(4, 32, 0, HEAP_ID_14);
        Bg_ClearTilemap(param0->bgConfig, BG_LAYER_SUB_0);
    }

    {
        BgTemplate v4 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x7000,
            .charBase = GX_BG_CHARBASE_0x04000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->bgConfig, BG_LAYER_SUB_1, &v4, 0);
        Bg_ClearTilesRange(5, 32, 0, HEAP_ID_14);
        Bg_ClearTilemap(param0->bgConfig, BG_LAYER_SUB_1);
    }
}

static void ImageClipGraphics_FreeBackgrounds(ImageClipGraphics *param0)
{
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(param0->bgConfig, BG_LAYER_SUB_1);
}

static void ImageClipGraphics_InitCharacterCollection(ImageClipGraphics *param0)
{
    param0->characterCollection = ResourceCollection_New((100 + 18) + 1, HEAP_ID_14);
    param0->characterData = Heap_Alloc(HEAP_ID_14, sizeof(NNSG2dCharacterData *) * ((100 + 18) + 1));
    memset(param0->characterData, 0, sizeof(NNSG2dCharacterData *) * ((100 + 18) + 1));
    param0->characterCount = ((100 + 18) + 1);
}

static void ImageClipGraphics_FreeCharacterCollection(ImageClipGraphics *param0)
{
    Heap_Free(param0->characterData);
    ResourceCollection_Delete(param0->characterCollection);
    param0->characterCount = 0;
}

static void ImageClipGraphics_InitSpriteSystem(ImageClipGraphics *param0)
{
    {
        CharTransferTemplate v0 = {
            8,
            0x8000,
            0x4000,
            14
        };

        CharTransfer_InitWithVramModes(&v0, GX_OBJVRAMMODE_CHAR_1D_32K, GX_OBJVRAMMODE_CHAR_1D_32K);
    }

    PlttTransfer_Init(5, HEAP_ID_14);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();

    NNS_G2dInitOamManagerModule();

    RenderOam_Init(0, 124, 0, 31, 0, 124, 0, 31, 14);
    param0->spriteList = SpriteList_InitRendering(48, &param0->renderer, HEAP_ID_14);
    SetSubScreenViewRect(&param0->renderer, 0, 512 * FX32_ONE);

    param0->spriteResourceCollections[0] = SpriteResourceCollection_New(8, 0, HEAP_ID_14);
    param0->spriteResourceCollections[1] = SpriteResourceCollection_New(5, 1, HEAP_ID_14);
    param0->spriteResourceCollections[2] = SpriteResourceCollection_New(48, 2, HEAP_ID_14);
    param0->spriteResourceCollections[3] = SpriteResourceCollection_New(48, 3, HEAP_ID_14);
}

static void ImageClipGraphics_FreeSpriteSystem(ImageClipGraphics *param0)
{
    SpriteList_Delete(param0->spriteList);

    {
        int v0;

        for (v0 = 0; v0 < 4; v0++) {
            SpriteResourceCollection_Delete(param0->spriteResourceCollections[v0]);
        }
    }

    CharTransfer_Free();
    PlttTransfer_Free();
    RenderOam_Free();
}

static void ImageClipGraphics_UpdateSpriteList(ImageClipGraphics *param0)
{
    SpriteList_Update(param0->spriteList);
}

static void ImageClipGraphics_LoadAccessoryData(ImageClipGraphics *param0, ImageClipGraphicsTemplates *param1)
{
    int v0;
    int v1;
    void *v2;

    for (v0 = 0; v0 < 100; v0++) {
        v2 = LoadMemberFromOpenNARC(param0->narc, v0 + 1, 0, HEAP_ID_14, 1);

        GF_ASSERT(v2);

        v1 = v0;

        param1->chars[v1].charsData = ImageClipGraphics_AddCharacterData(param0, v2, v0);
        param1->chars[v1].softSpriteMan = param0->softSpriteManager;
    }

    v2 = LoadMemberFromOpenNARC(param0->narc, 0, 0, HEAP_ID_14, 1);

    ResourceCollection_Add(param1->paletteCollection, v2, 0);
    NNS_G2dGetUnpackedPaletteData(v2, &param1->palettes[0].paletteData);

    param1->palettes[0].softSpriteMan = param0->softSpriteManager;
    param1->palettes[0].paletteSlot = 3;
}

static void ImageClipGraphics_LoadBackdropData(ImageClipGraphics *param0, ImageClipGraphicsTemplates *param1)
{
    int v0;
    void *v1;
    int v2;

    for (v0 = 0; v0 < 18; v0++) {
        v1 = LoadMemberFromOpenNARC(param0->narc, v0 + 206, 0, HEAP_ID_14, 1);
        v2 = v0 + 100;

        param1->chars[v2].charsData = ImageClipGraphics_AddCharacterData(param0, v1, v2);
        param1->chars[v2].softSpriteMan = param0->softSpriteManager;

        v2 = v0 + 1;
        v1 = LoadMemberFromOpenNARC(param0->narc, (v0) * 4 + 134 + 1, 0, HEAP_ID_14, 1);

        ResourceCollection_Add(param1->paletteCollection, v1, v2);
        NNS_G2dGetUnpackedPaletteData(v1, &param1->palettes[v2].paletteData);
        GF_ASSERT(param1->palettes[v2].paletteData);

        param1->palettes[v2].softSpriteMan = param0->softSpriteManager;
        param1->palettes[v2].paletteSlot = 1;
    }
}

static void ImageClipGraphics_LoadExtraResource(ImageClipGraphics *param0, enum HeapID heapID)
{
    param0->extraResource = LoadMemberFromOpenNARC(param0->narc, 235, 0, heapID, 0);
}

static void ImageClipGraphics_FreeExtraResource(ImageClipGraphics *param0)
{
    Heap_Free(param0->extraResource);
    param0->extraResource = NULL;
}

static void ImageClipGraphics_InitPokemonSprites(ImageClipGraphics *param0, enum HeapID heapID, int param2, int param3)
{
    param0->pokemonSpriteManager = PokemonSpriteManager_New(heapID);
    param0->texKey = NNS_GfdAllocTexVram(param2, 0, 0);
    param0->plttKey = NNS_GfdAllocPlttVram(param3, 0, NNS_GFD_ALLOC_FROM_LOW);

    PokemonSpriteManager_SetCharBaseAddrAndSize(param0->pokemonSpriteManager, NNS_GfdGetTexKeyAddr(param0->texKey), NNS_GfdGetTexKeySize(param0->texKey));
    PokemonSpriteManager_SetPlttBaseAddrAndSize(param0->pokemonSpriteManager, NNS_GfdGetPlttKeyAddr(param0->plttKey), NNS_GfdGetPlttKeySize(param0->plttKey));

    param0->drawPokemonSprites = 1;
}

static void ImageClipGraphics_FreePokemonSprites(ImageClipGraphics *param0)
{
    PokemonSpriteManager_Free(param0->pokemonSpriteManager);

    NNS_GfdFreeTexVram(param0->texKey);
    NNS_GfdFreePlttVram(param0->plttKey);

    param0->drawPokemonSprites = 0;
}

static void ImageClipGraphics_InitTemplateArrays(ImageClipGraphicsTemplates *param0, int param1, int param2, enum HeapID heapID)
{
    param0->chars = Heap_Alloc(heapID, sizeof(SoftwareSpriteCharsTemplate) * param1);
    memset(param0->chars, 0, sizeof(SoftwareSpriteCharsTemplate) * param1);
    param0->charCollection = ResourceCollection_New(param1, heapID);
    param0->charCount = param1;

    param0->palettes = Heap_Alloc(heapID, sizeof(SoftwareSpritePaletteTemplate) * param2);
    memset(param0->palettes, 0, sizeof(SoftwareSpritePaletteTemplate) * param2);
    param0->paletteCollection = ResourceCollection_New(param2, heapID);
    param0->paletteCount = param2;
}

static void ImageClipGraphics_FreeTemplateArrays(ImageClipGraphicsTemplates *param0)
{
    if (param0->charCollection) {
        ResourceCollection_Delete(param0->charCollection);
        param0->charCollection = NULL;
    }

    if (param0->paletteCollection) {
        ResourceCollection_Delete(param0->paletteCollection);
        param0->paletteCollection = NULL;
    }

    Heap_Free(param0->chars);
    param0->chars = NULL;
    Heap_Free(param0->palettes);
    param0->palettes = NULL;
}
