#include "image_clip_app/image_clip_app_0225AF8C.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/dress_up_photo.h"
#include "struct_defs/photo_accessory.h"
#include "struct_defs/photo_pokemon.h"
#include "struct_defs/struct_02029C88.h"

#include "image_clip_app/image_clip_app.h"
#include "image_clip_app/image_clip_app_02255094.h"
#include "image_clip_app/image_clip_app_022578F4.h"
#include "image_clip_app/image_clip_app_02259098.h"
#include "image_clip_app/image_clip_app_02259484.h"
#include "image_clip_app/image_clip_app_0225AF44.h"
#include "image_clip_app/struct_image_clip_app_02254DE0.h"
#include "image_clip_app/struct_image_clip_app_02255CB8.h"
#include "image_clip_app/struct_image_clip_app_02257964.h"
#include "image_clip_app/struct_image_clip_app_02259484.h"
#include "image_clip_app/struct_image_clip_app_0225A0E4.h"
#include "image_clip_app/struct_image_clip_app_0225AF68.h"
#include "image_clip_app/struct_image_clip_app_0225AF8C.h"
#include "image_clip_app/struct_image_clip_app_0225B388.h"

#include "bg_window.h"
#include "graphics.h"
#include "heap.h"
#include "narc.h"
#include "pokemon.h"
#include "resource_collection.h"
#include "software_sprite.h"
#include "image_clips.h"

typedef struct PhotoSprite {
    ImageClipGraphics graphics;
    ImageClipResourceList resourceList;
    ImageClipSpriteManager *spriteManager;
    PhotoRenderer renderer;
    PhotoRendererBg bgRenderer;
    Pokemon *pokemon;
    int heapID;
    int xPos;
    int yPos;
    int xOffset;
    int yOffset;
    u16 rotation;
    VecFx32 scale;
    GXRgb tint;
    BOOL hasBackdrop;
    BOOL transformEnabled;
} PhotoSprite;

typedef struct {
    const PhotoPokemon *photoMon;
    const PhotoAccessory *accessories[20];
    int accessoryCount;
    BgConfig *bgConfig;
    int backdropIndex;
    int xPos;
    int yPos;
    enum HeapID heapID;
} PhotoSpriteSource;

static PhotoSprite *PhotoSprite_Create(const PhotoSpriteSource *param0);
static PhotoSprite *PhotoSprite_CreateWithoutBackdrop(const PhotoSpriteSource *param0);
static void PhotoSprite_InitGraphics(PhotoSprite *param0, const PhotoSpriteSource *param1);
static void PhotoSprite_UpdateTransform(PhotoSprite *param0);
static void PhotoSprite_FreeGraphics(PhotoSprite *param0);
static void PhotoSprite_InitRenderer(PhotoSprite *param0, const PhotoSpriteSource *param1);
static void PhotoSprite_LoadBackdrop(PhotoSprite *param0, const PhotoSpriteSource *param1);
static void PhotoSprite_FreeRenderer(PhotoSprite *param0);
static void PhotoSprite_FreeBackdrop(PhotoSprite *param0);
static void PhotoSprite_ResetTransform(PhotoSprite *param0, const PhotoSpriteSource *param1);
static void PhotoSprite_InitSource(PhotoSpriteSource *param0, const PhotoSpriteConfig *param1);
static void PhotoSprite_LoadDressUpPhoto(PhotoSpriteSource *param0, const DressUpPhoto *photo);
static void PhotoSprite_LoadContestPhoto(PhotoSpriteSource *param0, const ContestPhoto *param1);
static void PhotoSprite_InitSprites(ImageClipGraphics *param0, ImageClipGraphicsTemplates *param1, const PhotoSpriteSource *param2, enum HeapID heapID);
static void PhotoSprite_LoadAccessorySprites(ImageClipGraphics *param0, ImageClipGraphicsTemplates *param1, const PhotoSpriteSource *param2, enum HeapID heapID);

PhotoSprite *PhotoSprite_CreateForDressUp(const PhotoSpriteConfig *param0, const DressUpPhoto *photo)
{
    PhotoSpriteSource v0;

    PhotoSprite_InitSource(&v0, param0);
    PhotoSprite_LoadDressUpPhoto(&v0, photo);

    return PhotoSprite_Create(&v0);
}

PhotoSprite *PhotoSprite_CreateForContest(const PhotoSpriteConfig *param0, const ContestPhoto *param1)
{
    PhotoSpriteSource v0;

    PhotoSprite_InitSource(&v0, param0);
    PhotoSprite_LoadContestPhoto(&v0, param1);

    return PhotoSprite_Create(&v0);
}

PhotoSprite *PhotoSprite_CreateForContestNoBackdrop(const PhotoSpriteConfig *param0, const ContestPhoto *param1)
{
    PhotoSpriteSource v0;

    PhotoSprite_InitSource(&v0, param0);
    PhotoSprite_LoadContestPhoto(&v0, param1);

    return PhotoSprite_CreateWithoutBackdrop(&v0);
}

void PhotoSprite_Update(PhotoSprite *param0)
{
    if (param0->hasBackdrop == 1) {
        PhotoRendererBg_Update(&param0->bgRenderer);
    }

    if (param0->transformEnabled == 1) {
        PhotoSprite_UpdateTransform(param0);
    }
}

void PhotoSprite_Free(PhotoSprite *param0)
{
    if (param0->hasBackdrop) {
        PhotoSprite_FreeBackdrop(param0);
    }

    PhotoSprite_FreeRenderer(param0);
    ImageClipSprite_Free(param0->spriteManager);

    param0->spriteManager = NULL;

    ImageClipResourceList_Free(&param0->resourceList);
    PhotoSprite_FreeGraphics(param0);

    Heap_Free(param0->pokemon);
    Heap_Free(param0);
}

void PhotoSprite_UpdateGraphics(PhotoSprite *param0)
{
    ImageClipGraphics_UpdatePokemonSprites(&param0->graphics);
}

void PhotoSprite_SetTransformEnabled(PhotoSprite *param0, BOOL param1)
{
    param0->transformEnabled = param1;
}

void PhotoSprite_SetVisible(PhotoSprite *param0, BOOL param1)
{
    param0->graphics.drawSoftwareSprites = param1;
}

void PhotoSprite_SetPosition(PhotoSprite *param0, int param1, int param2)
{
    PhotoRenderer_PanSprites(&param0->renderer, param0->xPos, param0->yPos, param1, param2);

    if (param0->hasBackdrop) {
        Bg_SetOffset(param0->graphics.bgConfig, 2, 0, 136 - param1);
        Bg_SetOffset(param0->graphics.bgConfig, 2, 3, 16 - param2);
    }

    param0->xPos = param1;
    param0->yPos = param2;
}

void PhotoSprite_SetOffset(PhotoSprite *param0, int param1, int param2)
{
    param0->xOffset = param1;
    param0->yOffset = param2;
}

void PhotoSprite_SetRotation(PhotoSprite *param0, u16 param1)
{
    param0->rotation = param1;
}

void PhotoSprite_SetScale(PhotoSprite *param0, fx32 param1, fx32 param2, fx32 param3)
{
    param0->scale.x = param1;
    param0->scale.y = param2;
    param0->scale.z = param3;
}

void PhotoSprite_MoveTo(PhotoSprite *param0, int param1, int param2)
{
    int v0, v1;
    int v2, v3;
    int v4, v5;
    int v6, v7;
    int v8, v9;

    ImageClipPokemonSprite_GetSize(&param0->renderer.context.pokemonSprite, &v4, &v5);
    PhotoRenderer_GetPokemonSpriteCenter(&param0->renderer, &v0, &v1);

    v2 = param1 - v0;
    v3 = param2 - v1;

    v6 = param0->xPos + v2;
    v7 = param0->yPos + v3;

    PhotoSprite_SetPosition(param0, v6, v7);

    v8 = param1 - v6;
    v9 = param2 - v7;

    PhotoSprite_SetOffset(param0, v8, v9);
}

void PhotoSprite_MoveToWithOffset(PhotoSprite *param0, int param1, int param2, int param3)
{
    int v0;
    fx32 v1;

    param3 = (80 / 2) - param3;

    v1 = FX_Mul(param3 * FX32_ONE, param0->scale.y);
    v0 = v1 >> FX32_SHIFT;

    PhotoSprite_MoveTo(param0, param1, param2 - v0);
}

void PhotoSprite_SetTint(PhotoSprite *param0, GXRgb param1)
{
    param0->tint = param1;
    PhotoRenderer_SetSpriteDiffuse(&param0->renderer, param1);
}

void PhotoSprite_AdjustPriority(PhotoSprite *param0, int param1)
{
    PhotoRenderer_OffsetZ(&param0->renderer, param1);
}

static PhotoSprite *PhotoSprite_Create(const PhotoSpriteSource *param0)
{
    PhotoSprite *v0;
    BOOL v1;

    v0 = Heap_Alloc(param0->heapID, sizeof(PhotoSprite));
    memset(v0, 0, sizeof(PhotoSprite));

    v0->heapID = param0->heapID;
    v0->pokemon = Pokemon_New(param0->heapID);
    PhotoPokemon_CopyToPokemon(param0->photoMon, v0->pokemon);

    PhotoSprite_InitGraphics(v0, param0);
    ImageClipGraphics_InitBackground(&v0->graphics, param0->bgConfig, param0->heapID);
    ImageClipResourceList_Init(&v0->resourceList, 21, param0->heapID);

    v0->spriteManager = ImageClipSprite_New(20, param0->heapID);

    PhotoSprite_InitRenderer(v0, param0);
    PhotoSprite_LoadBackdrop(v0, param0);
    PhotoRendererBg_Init(&v0->bgRenderer, &v0->renderer, param0->heapID);

    v0->hasBackdrop = 1;
    v0->transformEnabled = 1;

    PhotoSprite_ResetTransform(v0, param0);

    return v0;
}

static PhotoSprite *PhotoSprite_CreateWithoutBackdrop(const PhotoSpriteSource *param0)
{
    PhotoSprite *v0;
    BOOL v1;

    v0 = Heap_Alloc(param0->heapID, sizeof(PhotoSprite));
    memset(v0, 0, sizeof(PhotoSprite));

    v0->heapID = param0->heapID;
    v0->pokemon = Pokemon_New(param0->heapID);

    PhotoPokemon_CopyToPokemon(param0->photoMon, v0->pokemon);

    PhotoSprite_InitGraphics(v0, param0);
    ImageClipResourceList_Init(&v0->resourceList, 21, param0->heapID);

    v0->spriteManager = ImageClipSprite_New(20, param0->heapID);

    PhotoSprite_InitRenderer(v0, param0);

    v0->hasBackdrop = 0;
    v0->transformEnabled = 1;

    PhotoSprite_ResetTransform(v0, param0);

    return v0;
}

static void PhotoSprite_InitGraphics(PhotoSprite *param0, const PhotoSpriteSource *param1)
{
    ImageClipGraphicsTemplates v0;
    SoftwareSpriteManagerTemplate v1;

    param0->graphics.narc = NARC_ctor(NARC_INDEX_GRAPHIC__IMAGECLIP, param1->heapID);

    v1.numSprites = (700 + 18);
    v1.numChars = (100 + 18);
    v1.numPalettes = (1 + 18);
    v1.heapID = param1->heapID;

    ImageClipGraphics_InitSpriteManager(&param0->graphics, &v1, param1->heapID);
    PhotoSprite_InitSprites(&param0->graphics, &v0, param1, param1->heapID);
    ImageClipGraphics_LoadTemplates(&param0->graphics, &v0);
    ImageClipGraphics_FreeResourceTemplates(&v0);
}

static void PhotoSprite_UpdateTransform(PhotoSprite *param0)
{
    ImageClipGraphics_DrawTransformed(&param0->graphics, param0->xPos + param0->xOffset, param0->yPos + param0->yOffset, param0->rotation, &param0->scale);
}

static void PhotoSprite_FreeGraphics(PhotoSprite *param0)
{
    ImageClipGraphics_FreeAllSprites(&param0->graphics);
    ImageClipGraphics_FreeSprites(&param0->graphics);

    if (param0->hasBackdrop) {
        ImageClipGraphics_FreeBackground(&param0->graphics);
    }

    NARC_dtor(param0->graphics.narc);
}

static void PhotoSprite_InitRenderer(PhotoSprite *param0, const PhotoSpriteSource *param1)
{
    PhotoRendererTemplate v0;
    int xPos, yPos, priority;

    memset(&v0, 0, sizeof(PhotoRendererTemplate));

    v0.softSpriteManager = param0->graphics.softSpriteManager;
    v0.chars = param0->graphics.chars;
    v0.palettes = param0->graphics.palettes;
    v0.extraResource = param0->graphics.extraResource;
    v0.pokemonSpriteManager = param0->graphics.pokemonSpriteManager;
    v0.bgConfig = param0->graphics.bgConfig;
    v0.spriteManager = param0->spriteManager;
    v0.resourceList = &param0->resourceList;
    v0.maxSpriteCount = 21;

    PhotoRenderer_Init(&param0->renderer, &v0);

    PokemonSpriteTemplate v4;

    xPos = PhotoPokemon_GetXPos(param1->photoMon);
    yPos = PhotoPokemon_GetYPos(param1->photoMon);
    priority = PhotoPokemon_GetPriority(param1->photoMon);

    PhotoRenderer_SetupPokemonSprite(&param0->renderer, param0->pokemon, &v4, xPos, yPos, priority, param1->heapID);

    {
        int v5;
        int v6, v7;
        int v8;
        s8 v9;

        for (v5 = 0; v5 < param1->accessoryCount; v5++) {
            v8 = PhotoAccessory_GetID(param1->accessories[v5]);
            v6 = PhotoAccessory_GetXPos(param1->accessories[v5]);
            v7 = PhotoAccessory_GetYPos(param1->accessories[v5]);
            v9 = PhotoAccessory_GetPriority(param1->accessories[v5]);

            PhotoRenderer_CreateAccessorySprite(&param0->renderer, v8, v6, v7, v9);
        }
    }
}

static void PhotoSprite_LoadBackdrop(PhotoSprite *param0, const PhotoSpriteSource *param1)
{
    PhotoRenderer_LoadBackground(&param0->renderer, param1->backdropIndex, param1->heapID);
}

static void PhotoSprite_FreeRenderer(PhotoSprite *param0)
{
    PhotoRenderer_ClearSprites(&param0->renderer);
    PhotoRenderer_Free(&param0->renderer);
}

static void PhotoSprite_FreeBackdrop(PhotoSprite *param0)
{
    PhotoRenderer_FreeBackground(&param0->renderer);
}

static void PhotoSprite_ResetTransform(PhotoSprite *param0, const PhotoSpriteSource *param1)
{
    param0->xPos = (136 - (8 * 8));
    param0->yPos = (16 + (5 * 8));
    param0->xOffset = (112 / 2);
    param0->yOffset = (129 / 2);
    param0->scale.x = FX32_ONE;
    param0->scale.y = FX32_ONE;
    param0->scale.z = FX32_ONE;
    param0->rotation = 0;

    PhotoSprite_SetPosition(param0, param1->xPos, param1->yPos);

    param0->tint = GX_RGB(31, 31, 31);
}

static void PhotoSprite_InitSource(PhotoSpriteSource *param0, const PhotoSpriteConfig *param1)
{
    param0->bgConfig = param1->bgConfig;
    param0->xPos = param1->xPos;
    param0->yPos = param1->yPos;
    param0->heapID = param1->heapID;
}

static void PhotoSprite_LoadDressUpPhoto(PhotoSpriteSource *param0, const DressUpPhoto *photo)
{
    int i;

    param0->photoMon = DressUpPhoto_GetPhotoMon(photo);
    param0->accessoryCount = 0;

    for (i = 0; i < (11 - 1); i++) {
        if (DressUpPhoto_HasAccessory(photo, i)) {
            param0->accessories[param0->accessoryCount] = DressUpPhoto_GetAccessory(photo, i);
            param0->accessoryCount++;
        }
    }

    param0->backdropIndex = DressUpPhoto_GetBackdrop(photo);
}

static void PhotoSprite_LoadContestPhoto(PhotoSpriteSource *param0, const ContestPhoto *param1)
{
    int v0;

    param0->photoMon = ContestPhoto_GetPhotoMon(param1);
    param0->accessoryCount = 0;

    for (v0 = 0; v0 < (21 - 1); v0++) {
        if (ContestPhoto_HasAccessory(param1, v0)) {
            param0->accessories[param0->accessoryCount] = ContestPhoto_GetAccessory(param1, v0);
            param0->accessoryCount++;
        }
    }

    param0->backdropIndex = ContestPhoto_GetBackdrop(param1);
}

static void PhotoSprite_InitSprites(ImageClipGraphics *param0, ImageClipGraphicsTemplates *param1, const PhotoSpriteSource *param2, enum HeapID heapID)
{
    ImageClipGraphics_InitResourceTemplates(param1, heapID);
    PhotoSprite_LoadAccessorySprites(param0, param1, param2, heapID);
}

static void PhotoSprite_LoadAccessorySprites(ImageClipGraphics *param0, ImageClipGraphicsTemplates *param1, const PhotoSpriteSource *param2, enum HeapID heapID)
{
    int v0;
    int v1;
    void *v2;
    int v3;

    for (v0 = 0; v0 < param2->accessoryCount; v0++) {
        v3 = PhotoAccessory_GetID(param2->accessories[v0]);
        v1 = v3;

        if (ResourceCollection_IsIDUnused(param1->charCollection, v1) == 1) {
            v2 = LoadMemberFromOpenNARC(param0->narc, v3 + 1, 0, heapID, 1);

            ResourceCollection_Add(param1->charCollection, v2, v1);
            NNS_G2dGetUnpackedCharacterData(v2, &param1->chars[v1].charsData);

            param1->chars[v1].softSpriteMan = param0->softSpriteManager;
        }
    }

    v2 = LoadMemberFromOpenNARC(param0->narc, 0, 0, heapID, 1);

    ResourceCollection_Add(param1->paletteCollection, v2, 0);
    NNS_G2dGetUnpackedPaletteData(v2, &param1->palettes[0].paletteData);

    param1->palettes[0].softSpriteMan = param0->softSpriteManager;
    param1->palettes[0].paletteSlot = 3;
}
