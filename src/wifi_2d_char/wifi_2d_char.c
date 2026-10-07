#include "wifi_2d_char/wifi_2d_char.h"

#include <nitro.h>
#include <string.h>

#include "wifi_note/struct_wifi_note_sprite_params.h"

#include "heap.h"
#include "narc.h"
#include "palette.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"

typedef struct {
    int unk_00;
    SpriteResource *unk_04[2];
    u32 unk_0C;
    int unk_10;
    SpriteResourcesHeader unk_14;
} WiFi2DCharSpriteResources;

typedef struct {
    SpriteResource *unk_00[4];
} WiFi2DCharResourceSet;

typedef struct WiFi2DCharSprite {
    const WiFi2DCharSpriteResources *unk_00;
    Sprite *unk_04;
    Sprite *unk_08;
    int unk_0C;
    int unk_10;
    s16 unk_14;
    u8 padding_16[2];
} WiFi2DCharSprite;

typedef struct {
    SpriteResource *unk_00[4];
    SpriteResourcesHeader unk_10;
} WiFi2DCharShadowResources;

typedef struct WiFi2DCharManager {
    SpriteList *unk_00;
    PaletteData *unk_04;
    WiFi2DCharSprite *unk_08;
    u32 unk_0C;
    WiFi2DCharSpriteResources unk_10[151];
    WiFi2DCharResourceSet unk_2118[3];
    WiFi2DCharResourceSet unk_2148[16];
    WiFi2DCharShadowResources unk_2248;
    u32 unk_227C;
    SpriteResourceCollection *unk_2280[4];
    SpriteResource *unk_2290;
    NARC *unk_2294[2];
} WiFi2DCharManager;

typedef struct {
    u16 unk_00;
    u16 unk_02;
} WiFi2DCharSpeciesEntry;

static void WiFi2DCharManager_LoadPaletteBuffer(WiFi2DCharManager *param0, SpriteResource *param1, u32 param2);
static void WiFi2DCharManager_LoadBaseResources(WiFi2DCharManager *param0, int param1, u32 heapID);
static void WiFi2DCharManager_UnloadBaseResources(WiFi2DCharManager *param0, int param1);
static u32 WiFi2DChar_SpeciesToIndex(u32 param0);
static BOOL WiFi2DChar_SpeciesHasResources(u32 param0, int param1);
static u32 WiFi2DChar_GetResourceID(int param0, u32 param1, BOOL param2);
static void WiFi2DCharManager_LoadSpeciesResources(WiFi2DCharManager *param0, u32 param1, u32 param2, int param3, u32 heapID, int param5);
static void WiFi2DCharManager_LoadSpeciesResourcesNormal(WiFi2DCharManager *param0, u32 param1, u32 param2, int param3, u32 heapID);
static void WiFi2DCharManager_LoadSpeciesResourcesUnion(WiFi2DCharManager *param0, u32 param1, u32 param2, int param3, u32 heapID);
static void WiFi2DCharManager_UnloadSpeciesResources(WiFi2DCharManager *param0, u32 param1);
static void WiFi2DCharManager_UnloadSpeciesResourcesNormal(WiFi2DCharManager *param0, u32 param1);
static void WiFi2DCharManager_UnloadSpeciesResourcesUnion(WiFi2DCharManager *param0, u32 param1);
static BOOL WiFi2DCharManager_IsSpeciesResourceLoaded(const WiFi2DCharManager *param0, u32 param1);
static void WiFi2DCharManager_LoadShadowSprite(WiFi2DCharManager *param0, u32 param1, u32 heapID);
static void WiFi2DCharManager_UnloadShadowSprite(WiFi2DCharManager *param0);
static BOOL WiFi2DCharManager_HasShadowSprite(const WiFi2DCharShadowResources *param0);
static void WiFi2DCharManager_LoadShadowPalette(WiFi2DCharManager *param0, u32 param1, u32 heapID);
static void WiFi2DCharManager_UnloadShadowPalette(WiFi2DCharManager *param0);
static void WiFi2DCharManager_LoadShadowTiles(WiFi2DCharManager *param0, u32 heapID);
static void WiFi2DCharManager_UnloadShadowTiles(WiFi2DCharManager *param0);
static WiFi2DCharSprite *WiFi2DCharManager_AllocSprite(WiFi2DCharManager *param0);
static BOOL WiFi2DCharSprite_IsFree(const WiFi2DCharSprite *param0);
static void WiFi2DCharSprite_AdvanceAnim(WiFi2DCharSprite *param0);
static void WiFi2DCharSprite_SetAnimState0(WiFi2DCharSprite *param0, int param1);
static void WiFi2DCharSprite_SetAnimState1(WiFi2DCharSprite *param0, int param1);
static void WiFi2DCharSprite_SetAnimState2(WiFi2DCharSprite *param0, int param1);
static void WiFi2DCharSprite_SetAnimState3(WiFi2DCharSprite *param0, int param1);
static void WiFi2DCharSprite_SetAnimState4(WiFi2DCharSprite *param0, int param1);
static void WiFi2DCharSprite_SetAnimState5(WiFi2DCharSprite *param0, int param1);
static void WiFi2DCharSprite_SetAnimState6(WiFi2DCharSprite *param0, int param1);
static void WiFi2DCharSprite_SetAnimState7(WiFi2DCharSprite *param0, int param1);
static void WiFi2DCharSprite_SetAnimState8(WiFi2DCharSprite *param0, int param1);
static void WiFi2DCharSprite_UpdateAnimState1(WiFi2DCharSprite *param0);
static void WiFi2DCharSprite_UpdateAnimState2(WiFi2DCharSprite *param0);
static void WiFi2DCharSprite_UpdateAnimState3(WiFi2DCharSprite *param0);
static void WiFi2DCharSprite_UpdateAnimState4(WiFi2DCharSprite *param0);
static void WiFi2DCharSprite_UpdateAnimState5(WiFi2DCharSprite *param0);
static void WiFi2DCharSprite_UpdateAnimState6(WiFi2DCharSprite *param0);
static void WiFi2DCharSprite_UpdateAnimState7(WiFi2DCharSprite *param0);
static void WiFi2DCharSprite_UpdateAnimState8(WiFi2DCharSprite *param0);

static const u8 sWiFi2DCharResourceVariant[4] = {
    0x0,
    0x0,
    0x1,
    0x1
};

static const u8 sWiFi2DCharShadowResourceIDs[16] = {
    0x2,
    0x3,
    0x4,
    0x5,
    0x6,
    0x7,
    0x8,
    0x9,
    0xA,
    0xB,
    0xC,
    0xD,
    0xE,
    0xF,
    0x10,
    0x11
};

static const WiFi2DCharSpeciesEntry sWiFi2DCharSpeciesTable[151] = {
    { 0x0, 0x0 },
    { 0x3, 0x2 },
    { 0x5, 0x3 },
    { 0xB, 0x4 },
    { 0x1F, 0x5 },
    { 0x32, 0x6 },
    { 0x33, 0x7 },
    { 0x3E, 0x8 },
    { 0x46, 0x9 },
    { 0x61, 0x1 },
    { 0x6, 0xA },
    { 0x7, 0xB },
    { 0xD, 0xC },
    { 0xE, 0xD },
    { 0x23, 0xE },
    { 0x25, 0xF },
    { 0x2A, 0x10 },
    { 0x3F, 0x11 },
    { 0x4, 0x12 },
    { 0x8, 0x13 },
    { 0x34, 0x14 },
    { 0x35, 0x15 },
    { 0x2, 0x16 },
    { 0xF, 0x17 },
    { 0x10, 0x18 },
    { 0x3B, 0x19 },
    { 0x3C, 0x1A },
    { 0x9, 0x1B },
    { 0xC, 0x1C },
    { 0x17, 0x1D },
    { 0x16, 0x1E },
    { 0x29, 0x1F },
    { 0x26, 0x20 },
    { 0x27, 0x21 },
    { 0x11, 0x22 },
    { 0x44, 0x23 },
    { 0x45, 0x24 },
    { 0x1, 0x25 },
    { 0x2D, 0x26 },
    { 0x36, 0x27 },
    { 0x38, 0x28 },
    { 0x14, 0x29 },
    { 0xA, 0x2A },
    { 0x13, 0x2B },
    { 0x1D, 0x2C },
    { 0x24, 0x2D },
    { 0x28, 0x2E },
    { 0x2B, 0x2F },
    { 0x22, 0x30 },
    { 0x37, 0x31 },
    { 0x47, 0x32 },
    { 0x8D, 0x33 },
    { 0x8E, 0x34 },
    { 0x8F, 0x35 },
    { 0x90, 0x36 },
    { 0x91, 0x37 },
    { 0xA9, 0x38 },
    { 0x4E, 0x39 },
    { 0x2C, 0x3A },
    { 0x1E, 0x3B },
    { 0x51, 0x3C },
    { 0xAE, 0x3D },
    { 0xB9, 0x3E },
    { 0x31, 0x3F },
    { 0x30, 0x40 },
    { 0x86, 0x41 },
    { 0x87, 0x42 },
    { 0x88, 0x43 },
    { 0x89, 0x44 },
    { 0xAD, 0x45 },
    { 0x40, 0x46 },
    { 0x8A, 0x47 },
    { 0x63, 0x48 },
    { 0xC2, 0x49 },
    { 0x4F, 0x4A },
    { 0xBF, 0x4B },
    { 0x78, 0x4C },
    { 0x7C, 0x4D },
    { 0x7D, 0x4E },
    { 0x41, 0x4F },
    { 0x79, 0x50 },
    { 0x7A, 0x51 },
    { 0x7B, 0x52 },
    { 0xCD, 0x53 },
    { 0x4A, 0x54 },
    { 0xC3, 0x55 },
    { 0x7E, 0x56 },
    { 0x7F, 0x57 },
    { 0x80, 0x58 },
    { 0x81, 0x59 },
    { 0x82, 0x5A },
    { 0x83, 0x5B },
    { 0x84, 0x5C },
    { 0x85, 0x5D },
    { 0xAF, 0x5E },
    { 0x8C, 0x5F },
    { 0x52, 0x60 },
    { 0x53, 0x61 },
    { 0xA7, 0x62 },
    { 0xCE, 0x63 },
    { 0x4C, 0x64 },
    { 0xBE, 0x65 },
    { 0xA4, 0x66 },
    { 0x12, 0x67 },
    { 0xA5, 0x68 },
    { 0xA6, 0x69 },
    { 0xCC, 0x6A },
    { 0x1A, 0x6B },
    { 0x1B, 0x6C },
    { 0x1C, 0x6D },
    { 0x48, 0x6E },
    { 0xC0, 0x6F },
    { 0x4B, 0x70 },
    { 0x49, 0x71 },
    { 0x94, 0x72 },
    { 0x54, 0x73 },
    { 0x18, 0x74 },
    { 0x19, 0x75 },
    { 0x20, 0x76 },
    { 0x21, 0x77 },
    { 0x97, 0x78 },
    { 0xA0, 0x79 },
    { 0xA1, 0x7A },
    { 0xB8, 0x7B },
    { 0x98, 0x7C },
    { 0x99, 0x7D },
    { 0x9A, 0x7E },
    { 0x9B, 0x7F },
    { 0x9C, 0x80 },
    { 0x9D, 0x81 },
    { 0x9E, 0x82 },
    { 0x9F, 0x83 },
    { 0xA8, 0x84 },
    { 0x2E, 0x85 },
    { 0x2F, 0x86 },
    { 0x56, 0x87 },
    { 0xB6, 0x88 },
    { 0xD0, 0x89 },
    { 0xA3, 0x8A },
    { 0xD7, 0x8B },
    { 0xD8, 0x8C },
    { 0xD9, 0x8D },
    { 0xDA, 0x8E },
    { 0xDB, 0x8F },
    { 0xE7, 0x90 },
    { 0xE8, 0x91 },
    { 0xE9, 0x92 },
    { 0xEA, 0x93 },
    { 0xEB, 0x94 },
    { 0xFC, 0x95 },
    { 0xFD, 0x96 }
};

static const u8 sWiFi2DCharAnimFrameCount[10] = {
    0x1,
    0xFF,
    0x8,
    0x2,
    0x4,
    0x10,
    0x10,
    0x2,
    0x4,
    0x0
};

WiFi2DCharManager *WiFi2DCharManager_New(SpriteList *param0, PaletteData *param1, u32 param2, u32 heapID)
{
    WiFi2DCharManager *v0;
    int v1;

    v0 = Heap_Alloc(heapID, sizeof(WiFi2DCharManager));
    memset(v0, 0, sizeof(WiFi2DCharManager));

    v0->unk_00 = param0;
    v0->unk_04 = param1;
    v0->unk_2294[0] = NARC_ctor(NARC_INDEX_GRAPHIC__WIFI2DCHAR, heapID);
    v0->unk_2294[1] = NARC_ctor(NARC_INDEX_GRAPHIC__WIFI_UNIONOBJ, heapID);

    for (v1 = 0; v1 < 2; v1++) {
        v0->unk_2280[v1] = SpriteResourceCollection_New((151 + 1), v1, heapID);
    }

    for (v1 = 0; v1 < 2; v1++) {
        v0->unk_2280[v1 + 2] = SpriteResourceCollection_New(((3 * 2) + 16 + 1), v1 + 2, heapID);
    }

    for (v1 = 0; v1 < 3; v1++) {
        WiFi2DCharManager_LoadBaseResources(v0, v1, heapID);
    }

    v0->unk_0C = param2;
    v0->unk_08 = Heap_Alloc(heapID, sizeof(WiFi2DCharSprite) * v0->unk_0C);
    memset(v0->unk_08, 0, sizeof(WiFi2DCharSprite) * v0->unk_0C);

    return v0;
}

void WiFi2DCharManager_Free(WiFi2DCharManager *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_0C; v0++) {
        if (WiFi2DCharSprite_IsFree(&param0->unk_08[v0]) == 0) {
            WiFi2DCharSprite_Delete(&param0->unk_08[v0]);
        }
    }

    for (v0 = 0; v0 < 3; v0++) {
        WiFi2DCharManager_UnloadBaseResources(param0, v0);
    }

    WiFi2DCharManager_UnloadAllSpecies(param0);
    NARC_dtor(param0->unk_2294[0]);
    NARC_dtor(param0->unk_2294[1]);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(param0->unk_2280[v0]);
    }

    Heap_Free(param0->unk_08);
    Heap_Free(param0);
}

void WiFi2DCharManager_LoadSpecies(WiFi2DCharManager *param0, u32 param1, u32 param2, int param3, u32 heapID)
{
    u32 v0;
    BOOL v1 = WiFi2DChar_SpeciesHasResources(param1, param3);
    GF_ASSERT(v1);

    v0 = WiFi2DChar_SpeciesToIndex(param1);
    WiFi2DCharManager_LoadSpeciesResources(param0, v0, param2, param3, heapID, 0);
}

void WiFi2DCharManager_UnloadSpecies(WiFi2DCharManager *param0, u32 param1)
{
    u32 v0 = WiFi2DChar_SpeciesToIndex(param1);
    WiFi2DCharManager_UnloadSpeciesResources(param0, v0);
}

BOOL WiFi2DCharManager_IsSpeciesLoaded(const WiFi2DCharManager *param0, u32 param1)
{
    u32 v0 = WiFi2DChar_SpeciesToIndex(param1);
    return WiFi2DCharManager_IsSpeciesResourceLoaded(param0, v0);
}

void WiFi2DCharManager_UnloadAllSpecies(WiFi2DCharManager *param0)
{
    int v0;

    if (param0->unk_2290 != NULL) {
        WiFi2DCharManager_UnloadShadowResources(param0);
    }

    for (v0 = 0; v0 < 151; v0++) {
        if (WiFi2DCharManager_IsSpeciesResourceLoaded(param0, v0) == 1) {
            WiFi2DCharManager_UnloadSpeciesResources(param0, v0);
        }
    }
}

void WiFi2DCharManager_LoadShadowResources(WiFi2DCharManager *param0, u32 param1, int param2, u32 heapID)
{
    int v0;

    GF_ASSERT(param2 != 0);

    WiFi2DCharManager_LoadShadowPalette(param0, param1, heapID);
    WiFi2DCharManager_LoadShadowTiles(param0, heapID);

    for (v0 = 0; v0 < 16; v0++) {
        WiFi2DCharManager_LoadSpeciesResources(param0, sWiFi2DCharShadowResourceIDs[v0], param1, param2, heapID, 1);
    }
}

void WiFi2DCharManager_UnloadShadowResources(WiFi2DCharManager *param0)
{
    int v0;

    WiFi2DCharManager_UnloadShadowPalette(param0);
    WiFi2DCharManager_UnloadShadowTiles(param0);

    for (v0 = 0; v0 < 16; v0++) {
        WiFi2DCharManager_UnloadSpeciesResources(param0, sWiFi2DCharShadowResourceIDs[v0]);
    }
}

void WiFi2DCharManager_LoadShadow(WiFi2DCharManager *param0, u32 param1, u32 param2, u32 heapID)
{
    WiFi2DCharManager_LoadShadowSprite(param0, param1, heapID);
    param0->unk_227C = param2;
}

void WiFi2DCharManager_UnloadShadow(WiFi2DCharManager *param0)
{
    WiFi2DCharManager_UnloadShadowSprite(param0);
}

WiFi2DCharSprite *WiFi2DCharSprite_New(WiFi2DCharManager *param0, const WiFiNoteSpriteParams *param1, u32 param2, u32 heapID)
{
    WiFi2DCharSprite *v0;
    AffineSpriteListTemplate v1;
    u32 v2;

    v0 = WiFi2DCharManager_AllocSprite(param0);
    v2 = WiFi2DChar_SpeciesToIndex(param2);

    GF_ASSERT(WiFi2DCharManager_IsSpeciesResourceLoaded(param0, v2) == 1);
    memset(&v1, 0, sizeof(AffineSpriteListTemplate));

    v1.list = param0->unk_00;
    v1.resourceData = &param0->unk_10[v2].unk_14;
    v1.position.x = param1->x << FX32_SHIFT;
    v1.position.y = param1->y << FX32_SHIFT;
    v1.affineScale.x = FX32_ONE;
    v1.affineScale.y = FX32_ONE;
    v1.affineScale.z = FX32_ONE;
    v1.priority = param1->priority;
    v1.heapID = heapID;

    if ((param0->unk_10[v2].unk_0C == NNS_G2D_VRAM_TYPE_2DBOTH) || (param0->unk_10[v2].unk_0C == NNS_G2D_VRAM_TYPE_2DMAIN)) {
        v1.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    } else {
        v1.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    }

    v0->unk_04 = SpriteList_AddAffine(&v1);
    Sprite_SetExplicitPriority(v0->unk_04, param1->explicitPriority);

    if (param0->unk_10[v2].unk_10 == 1) {
        Sprite_SetAnim(v0->unk_04, 5 + 1);
    } else {
        Sprite_SetAnim(v0->unk_04, 1);
    }

    v0->unk_0C = 9;
    v0->unk_14 = 0;
    v0->unk_10 = 1;
    v0->unk_00 = &param0->unk_10[v2];

    if (WiFi2DCharManager_HasShadowSprite(&param0->unk_2248)) {
        memset(&v1, 0, sizeof(AffineSpriteListTemplate));

        v1.list = param0->unk_00;
        v1.resourceData = &param0->unk_2248.unk_10;
        v1.position.x = param1->x << FX32_SHIFT;
        v1.position.y = param1->y << FX32_SHIFT;
        v1.affineScale.x = FX32_ONE;
        v1.affineScale.y = FX32_ONE;
        v1.affineScale.z = FX32_ONE;
        v1.priority = param0->unk_227C;
        v1.heapID = heapID;

        if ((param0->unk_10[v2].unk_0C == NNS_G2D_VRAM_TYPE_2DBOTH) || (param0->unk_10[v2].unk_0C == NNS_G2D_VRAM_TYPE_2DMAIN)) {
            v1.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
        } else {
            v1.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
        }

        v0->unk_08 = SpriteList_AddAffine(&v1);

        Sprite_SetExplicitPriority(v0->unk_08, param1->explicitPriority);
    } else {
        v0->unk_08 = NULL;
    }

    return v0;
}

void WiFi2DCharSprite_Delete(WiFi2DCharSprite *param0)
{
    if (param0->unk_08 != NULL) {
        Sprite_Delete(param0->unk_08);
    }

    Sprite_Delete(param0->unk_04);
    memset(param0, 0, sizeof(WiFi2DCharSprite));
}

const Sprite *WiFi2DCharSprite_GetSprite(const WiFi2DCharSprite *param0)
{
    return param0->unk_04;
}

void WiFi2DCharSprite_SetPosition(WiFi2DCharSprite *param0, s16 param1, s16 param2)
{
    VecFx32 v0;

    v0.x = param1 << FX32_SHIFT;
    v0.y = param2 << FX32_SHIFT;
    v0.z = 0;

    Sprite_SetPosition(param0->unk_04, &v0);

    if (param0->unk_08) {
        v0.x += 8 << FX32_SHIFT;
        v0.y += 14 << FX32_SHIFT;

        Sprite_SetPosition(param0->unk_08, &v0);
    }
}

void WiFi2DCharSprite_SetPriority(WiFi2DCharSprite *param0, u16 param1)
{
    Sprite_SetPriority(param0->unk_04, param1);
}

u16 WiFi2DCharSprite_GetPriority(const WiFi2DCharSprite *param0)
{
    return Sprite_GetPriority(param0->unk_04);
}

void WiFi2DCharSprite_SetVisible(WiFi2DCharSprite *param0, BOOL param1)
{
    Sprite_SetDrawFlag(param0->unk_04, param1);

    if (param0->unk_08) {
        Sprite_SetDrawFlag(param0->unk_08, param1);
    }
}

BOOL WiFi2DCharSprite_IsVisible(const WiFi2DCharSprite *param0)
{
    return Sprite_GetDrawFlag(param0->unk_04);
}

int WiFi2DCharSprite_GetResourceType(const WiFi2DCharSprite *param0)
{
    return param0->unk_00->unk_10;
}

int WiFi2DCharSprite_GetAnimState(const WiFi2DCharSprite *param0)
{
    return param0->unk_0C;
}

void WiFi2DCharSprite_SetAnimFrame(WiFi2DCharSprite *param0, u16 param1)
{
    Sprite_SetAnimFrame(param0->unk_04, param1);
}

u16 WiFi2DCharSprite_GetAnimFrame(const WiFi2DCharSprite *param0)
{
    return Sprite_GetAnimFrame(param0->unk_04);
}

void WiFi2DCharSprite_SetShadowPosition(WiFi2DCharSprite *param0, s16 param1, s16 param2)
{
    VecFx32 v0;

    if (param0->unk_08 != NULL) {
        v0.x = param1 + 8 << FX32_SHIFT;
        v0.y = param2 + 14 << FX32_SHIFT;
        v0.z = 0;

        Sprite_SetPosition(param0->unk_08, &v0);
    }
}

void WiFi2DCharSprite_SetAnim(WiFi2DCharSprite *param0, int param1, int param2)
{
    static void (*const v0[])(WiFi2DCharSprite *, int) = {
        WiFi2DCharSprite_SetAnimState0,
        WiFi2DCharSprite_SetAnimState1,
        WiFi2DCharSprite_SetAnimState2,
        WiFi2DCharSprite_SetAnimState3,
        WiFi2DCharSprite_SetAnimState4,
        WiFi2DCharSprite_SetAnimState5,
        WiFi2DCharSprite_SetAnimState6,
        WiFi2DCharSprite_SetAnimState7,
        WiFi2DCharSprite_SetAnimState8,
        NULL
    };

    GF_ASSERT(param1 < 10);
    GF_ASSERT(param2 < 4);

    param0->unk_0C = param1;
    param0->unk_14 = 0;

    if (v0[param1] != NULL) {
        v0[param1](param0, param2);
    }
}

void WiFi2DCharSprite_UpdateAnim(WiFi2DCharSprite *param0)
{
    BOOL v0 = 0;

    if (sWiFi2DCharAnimFrameCount[param0->unk_0C] == 0xff) {
        v0 = 1;
    } else {
        if (sWiFi2DCharAnimFrameCount[param0->unk_0C] >= param0->unk_14 + 1) {
            v0 = 1;
        }
    }

    if (v0 == 1) {
        WiFi2DCharSprite_AdvanceAnim(param0);
        param0->unk_14++;
    }
}

static void WiFi2DCharManager_LoadBaseResources(WiFi2DCharManager *param0, int param1, u32 heapID)
{
    int v0;
    u32 v1;
    u32 v2;
    static const u32 v3[3][4] = {
        {
            3,
            4,
            3,
            4,
        },
        {
            5,
            6,
            7,
            8,
        },
        { 9, 10, 11, 12 }
    };

    GF_ASSERT(param0->unk_2118[param1].unk_00[0] == NULL);

    for (v0 = 0; v0 < 4; v0++) {
        v1 = 2 + (v0 % 2);
        v2 = 0x100 + (param1 * 2) + sWiFi2DCharResourceVariant[v0];
        param0->unk_2118[param1].unk_00[v0] = SpriteResourceCollection_AddFrom(param0->unk_2280[v1], param0->unk_2294[0], v3[param1][v0], 0, v2, v1, heapID);
    }
}

static void WiFi2DCharManager_UnloadBaseResources(WiFi2DCharManager *param0, int param1)
{
    int v0;
    u32 v1;

    GF_ASSERT(param0->unk_2118[param1].unk_00[0] != NULL);

    for (v0 = 0; v0 < 4; v0++) {
        v1 = 2 + (v0 % 2);

        SpriteResourceCollection_Remove(param0->unk_2280[v1], param0->unk_2118[param1].unk_00[v0]);
        param0->unk_2118[param1].unk_00[v0] = NULL;
    }
}

static u32 WiFi2DChar_SpeciesToIndex(u32 param0)
{
    int v0;

    for (v0 = 0; v0 < 151; v0++) {
        if (param0 == sWiFi2DCharSpeciesTable[v0].unk_00) {
            return sWiFi2DCharSpeciesTable[v0].unk_02;
        }
    }

    GF_ASSERT(FALSE);
    return 0;
}

static BOOL WiFi2DChar_SpeciesHasResources(u32 param0, int param1)
{
    if (param1 == 0) {
        if ((param0 == 0x0) || (param0 == 0x61) || (param0 == 0xfc) || (param0 == 0xfd)) {
            return 1;
        } else {
            return 0;
        }
    }

    return 1;
}

u32 WiFi2DChar_GetResourceID(int param0, u32 param1, BOOL param2)
{
    u32 v0;

    GF_ASSERT((param1 == 2) || (param1 == 3));
    v0 = param1 - 2;

    if (param2 == 0) {
        v0 += 2;
    }

    return 0x100 + (param0 * 2) + sWiFi2DCharResourceVariant[v0];
}

static void WiFi2DCharManager_LoadSpeciesResources(WiFi2DCharManager *param0, u32 param1, u32 param2, int param3, u32 heapID, int param5)
{
    GF_ASSERT(param0->unk_10[param1].unk_04[0] == NULL);

    if (param5 == 0) {
        WiFi2DCharManager_LoadSpeciesResourcesNormal(param0, param1, param2, param3, heapID);
    } else {
        WiFi2DCharManager_LoadSpeciesResourcesUnion(param0, param1, param2, param3, heapID);
    }
}

static void WiFi2DCharManager_LoadSpeciesResourcesNormal(WiFi2DCharManager *param0, u32 param1, u32 param2, int param3, u32 heapID)
{
    NNSG2dCharacterData *v0;
    BOOL v1;
    BOOL v2;
    u32 v3, v4;

    param0->unk_10[param1].unk_04[0] = SpriteResourceCollection_AddTilesFrom(param0->unk_2280[0], param0->unk_2294[0], ((((param1) * 2) + 13) + 1), 0, 0x200 + param1, param2, heapID);
    param0->unk_10[param1].unk_04[1] = SpriteResourceCollection_AddPaletteFrom(param0->unk_2280[1], param0->unk_2294[0], (((param1) * 2) + 13), 0, 0x200 + param1, param2, 1, heapID);

    v0 = SpriteResource_GetTileData(param0->unk_10[param1].unk_04[0]);

    if (v0->szByte == 0x1800) {
        v2 = 0;
    } else {
        v2 = 1;
    }

    if (param3 == 2) {
        if (v2) {
            v0->szByte = 0x800;
        } else {
            v0->szByte = 0x800;
        }
    } else if (param3 == 1) {
        if (v2) {
            v0->szByte = 0x1400;
        } else {
            v0->szByte = 0x1800;
        }
    }

    v1 = SpriteTransfer_RequestCharAtEndWithHardwareMappingType(param0->unk_10[param1].unk_04[0]);
    GF_ASSERT(v1);

    v1 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_10[param1].unk_04[1]);
    GF_ASSERT(v1);

    if (param0->unk_04) {
        WiFi2DCharManager_LoadPaletteBuffer(param0, param0->unk_10[param1].unk_04[1], 1);
    }

    SpriteResource_ReleaseData(param0->unk_10[param1].unk_04[0]);
    SpriteResource_ReleaseData(param0->unk_10[param1].unk_04[1]);

    param0->unk_10[param1].unk_0C = param2;
    param0->unk_10[param1].unk_10 = param3;
    param0->unk_10[param1].unk_00 = 0;

    v3 = WiFi2DChar_GetResourceID(param3, 2, v2);
    v4 = WiFi2DChar_GetResourceID(param3, 3, v2);

    SpriteResourcesHeader_Init(&param0->unk_10[param1].unk_14, 0x200 + param1, 0x200 + param1, v3, v4, 0xffffffff, 0xffffffff, 0, 0, param0->unk_2280[0], param0->unk_2280[1], param0->unk_2280[2], param0->unk_2280[3], NULL, NULL);
}

static void WiFi2DCharManager_LoadSpeciesResourcesUnion(WiFi2DCharManager *param0, u32 param1, u32 param2, int param3, u32 heapID)
{
    NNSG2dCharacterData *v0;
    BOOL v1;
    u32 v2 = param1 - 2;

    param0->unk_10[param1].unk_04[0] = SpriteResourceCollection_AddTilesFrom(param0->unk_2280[0], param0->unk_2294[1], (1 + ((param1)-2)), 0, 0x200 + param1, param2, heapID);

    if (param3 == 2) {
        v0 = SpriteResource_GetTileData(param0->unk_10[param1].unk_04[0]);
        v0->szByte = 0x800;
    } else if (param3 == 1) {
        v0 = SpriteResource_GetTileData(param0->unk_10[param1].unk_04[0]);
        v0->szByte = 0x1400;
    }

    v1 = SpriteTransfer_RequestCharAtEndWithHardwareMappingType(param0->unk_10[param1].unk_04[0]);
    GF_ASSERT(v1);
    SpriteResource_ReleaseData(param0->unk_10[param1].unk_04[0]);

    param0->unk_10[param1].unk_04[1] = NULL;
    param0->unk_10[param1].unk_0C = param2;
    param0->unk_10[param1].unk_10 = param3;
    param0->unk_10[param1].unk_00 = 1;

    SpriteResourcesHeader_Init(&param0->unk_10[param1].unk_14, 0x200 + param1, 0x402, 0x180 + v2, 0x180 + v2, 0xffffffff, 0xffffffff, 0, 0, param0->unk_2280[0], param0->unk_2280[1], param0->unk_2280[2], param0->unk_2280[3], NULL, NULL);
}

static void WiFi2DCharManager_UnloadSpeciesResources(WiFi2DCharManager *param0, u32 param1)
{
    GF_ASSERT(param0->unk_10[param1].unk_04[0] != NULL);

    if (param0->unk_10[param1].unk_00 == 0) {
        WiFi2DCharManager_UnloadSpeciesResourcesNormal(param0, param1);
    } else {
        WiFi2DCharManager_UnloadSpeciesResourcesUnion(param0, param1);
    }
}

static void WiFi2DCharManager_UnloadSpeciesResourcesNormal(WiFi2DCharManager *param0, u32 param1)
{
    SpriteTransfer_ResetCharTransfer(param0->unk_10[param1].unk_04[0]);
    SpriteTransfer_ResetPlttTransfer(param0->unk_10[param1].unk_04[1]);

    SpriteResourceCollection_Remove(param0->unk_2280[0], param0->unk_10[param1].unk_04[0]);
    SpriteResourceCollection_Remove(param0->unk_2280[1], param0->unk_10[param1].unk_04[1]);

    param0->unk_10[param1].unk_04[0] = NULL;
    param0->unk_10[param1].unk_04[1] = NULL;
}

static void WiFi2DCharManager_UnloadSpeciesResourcesUnion(WiFi2DCharManager *param0, u32 param1)
{
    SpriteTransfer_ResetCharTransfer(param0->unk_10[param1].unk_04[0]);
    SpriteResourceCollection_Remove(param0->unk_2280[0], param0->unk_10[param1].unk_04[0]);

    param0->unk_10[param1].unk_04[0] = NULL;
}

static BOOL WiFi2DCharManager_IsSpeciesResourceLoaded(const WiFi2DCharManager *param0, u32 param1)
{
    if (param0->unk_10[param1].unk_04[0] == NULL) {
        return 0;
    }

    return 1;
}

static void WiFi2DCharManager_LoadShadowSprite(WiFi2DCharManager *param0, u32 param1, u32 heapID)
{
    int v0;
    BOOL v1;
    BOOL v2;
    u32 v3;

    GF_ASSERT(param0->unk_2248.unk_00[0] == NULL);

    v2 = 0;

    if (WiFi2DCharManager_IsSpeciesResourceLoaded(param0, 0) == 1) {
        v3 = 0;
        v2 = 1;
    } else if (WiFi2DCharManager_IsSpeciesResourceLoaded(param0, 1) == 1) {
        v3 = 1;
        v2 = 1;
    } else if (WiFi2DCharManager_IsSpeciesResourceLoaded(param0, 149) == 1) {
        v3 = 149;
        v2 = 1;
    } else if (WiFi2DCharManager_IsSpeciesResourceLoaded(param0, 150) == 1) {
        v3 = 150;
        v2 = 1;
    }

    GF_ASSERT(v2 == 1);

    for (v0 = 0; v0 < 2; v0++) {
        param0->unk_2248.unk_00[v0 + 2] = SpriteResourceCollection_AddFrom(param0->unk_2280[v0 + 2], param0->unk_2294[0], 0 + v0, 0, 0x120, 2 + v0, heapID);
    }

    param0->unk_2248.unk_00[0] = SpriteResourceCollection_AddTilesFrom(param0->unk_2280[0], param0->unk_2294[0], 2, 0, 0x120, param1, heapID);

    v1 = SpriteTransfer_RequestCharAtEndWithHardwareMappingType(param0->unk_2248.unk_00[0]);
    GF_ASSERT(v1);

    SpriteResource_ReleaseData(param0->unk_2248.unk_00[0]);
    SpriteResourcesHeader_Init(&param0->unk_2248.unk_10, 0x120, 0x200 + v3, 0x120, 0x120, 0xffffffff, 0xffffffff, 0, 0, param0->unk_2280[0], param0->unk_2280[1], param0->unk_2280[2], param0->unk_2280[3], NULL, NULL);
}

static void WiFi2DCharManager_UnloadShadowSprite(WiFi2DCharManager *param0)
{
    int v0;

    if (WiFi2DCharManager_HasShadowSprite(&param0->unk_2248) == 1) {
        {
            SpriteTransfer_ResetCharTransfer(param0->unk_2248.unk_00[0]);
            SpriteResourceCollection_Remove(param0->unk_2280[0], param0->unk_2248.unk_00[0]);
            param0->unk_2248.unk_00[0] = NULL;
        }

        for (v0 = 0; v0 < 2; v0++) {
            SpriteResourceCollection_Remove(param0->unk_2280[v0 + 2], param0->unk_2248.unk_00[v0 + 2]);
            param0->unk_2248.unk_00[v0 + 2] = NULL;
        }
    }
}

static BOOL WiFi2DCharManager_HasShadowSprite(const WiFi2DCharShadowResources *param0)
{
    if (param0->unk_00[0] != NULL) {
        return 1;
    }

    return 0;
}

static void WiFi2DCharManager_LoadShadowPalette(WiFi2DCharManager *param0, u32 param1, u32 heapID)
{
    BOOL v0;

    GF_ASSERT(param0->unk_2290 == NULL);

    param0->unk_2290 = SpriteResourceCollection_AddPaletteFrom(param0->unk_2280[1], param0->unk_2294[1], 0, 0, 0x402, param1, 8, heapID);

    v0 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_2290);
    GF_ASSERT(v0);

    if (param0->unk_04) {
        WiFi2DCharManager_LoadPaletteBuffer(param0, param0->unk_2290, 8);
    }

    SpriteResource_ReleaseData(param0->unk_2290);
}

static void WiFi2DCharManager_UnloadShadowPalette(WiFi2DCharManager *param0)
{
    GF_ASSERT(param0->unk_2290 != NULL);

    SpriteTransfer_ResetPlttTransfer(param0->unk_2290);
    SpriteResourceCollection_Remove(param0->unk_2280[1], param0->unk_2290);

    param0->unk_2290 = NULL;
}

static void WiFi2DCharManager_LoadShadowTiles(WiFi2DCharManager *param0, u32 heapID)
{
    int v0;

    GF_ASSERT(param0->unk_2148[0].unk_00[0] == NULL);

    for (v0 = 0; v0 < 16; v0++) {
        param0->unk_2148[v0].unk_00[0] = SpriteResourceCollection_AddFrom(param0->unk_2280[2], param0->unk_2294[1], (17 + ((v0) * 2)), 0, 0x180 + v0, 2, heapID);
        param0->unk_2148[v0].unk_00[1] = SpriteResourceCollection_AddFrom(param0->unk_2280[3], param0->unk_2294[1], ((17 + ((v0) * 2)) + 1), 0, 0x180 + v0, 3, heapID);
    }
}

static void WiFi2DCharManager_UnloadShadowTiles(WiFi2DCharManager *param0)
{
    int v0;

    GF_ASSERT(param0->unk_2148[0].unk_00[0] != NULL);

    for (v0 = 0; v0 < 16; v0++) {
        SpriteResourceCollection_Remove(param0->unk_2280[2], param0->unk_2148[v0].unk_00[0]);
        SpriteResourceCollection_Remove(param0->unk_2280[3], param0->unk_2148[v0].unk_00[1]);

        param0->unk_2148[v0].unk_00[0] = NULL;
        param0->unk_2148[v0].unk_00[1] = NULL;
    }
}

static WiFi2DCharSprite *WiFi2DCharManager_AllocSprite(WiFi2DCharManager *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_0C; v0++) {
        if (WiFi2DCharSprite_IsFree(&param0->unk_08[v0]) == 1) {
            return &param0->unk_08[v0];
        }
    }

    GF_ASSERT(FALSE);
    return NULL;
}

static void WiFi2DCharSprite_AdvanceAnim(WiFi2DCharSprite *param0)
{
    static void (*const v0[])(WiFi2DCharSprite *) = {
        NULL,
        WiFi2DCharSprite_UpdateAnimState1,
        WiFi2DCharSprite_UpdateAnimState2,
        WiFi2DCharSprite_UpdateAnimState3,
        WiFi2DCharSprite_UpdateAnimState4,
        WiFi2DCharSprite_UpdateAnimState5,
        WiFi2DCharSprite_UpdateAnimState6,
        WiFi2DCharSprite_UpdateAnimState7,
        WiFi2DCharSprite_UpdateAnimState8,
        NULL
    };

    if (v0[param0->unk_0C] != NULL) {
        v0[param0->unk_0C](param0);
    }
}

static void WiFi2DCharSprite_SetAnimState0(WiFi2DCharSprite *param0, int param1)
{
    param0->unk_10 = param1;
    Sprite_SetAnimNoRestart(param0->unk_04, param0->unk_10);
}

static void WiFi2DCharSprite_SetAnimState1(WiFi2DCharSprite *param0, int param1)
{
    param0->unk_10 = param1;
    Sprite_SetAnimNoRestart(param0->unk_04, 4);
}

static void WiFi2DCharSprite_SetAnimState2(WiFi2DCharSprite *param0, int param1)
{
    param0->unk_10 = param1;
    Sprite_SetAnimNoRestart(param0->unk_04, 5 + param0->unk_10);
}

static void WiFi2DCharSprite_SetAnimState3(WiFi2DCharSprite *param0, int param1)
{
    Sprite_SetAnimNoRestart(param0->unk_04, 5 + param0->unk_10);
    param0->unk_10 = param1;
}

static void WiFi2DCharSprite_SetAnimState4(WiFi2DCharSprite *param0, int param1)
{
    param0->unk_10 = param1;
    Sprite_SetAnimNoRestart(param0->unk_04, 9 + param0->unk_10);
}

static void WiFi2DCharSprite_SetAnimState5(WiFi2DCharSprite *param0, int param1)
{
    param0->unk_10 = param1;
    Sprite_SetAnimNoRestart(param0->unk_04, 5 + param0->unk_10);
}

static void WiFi2DCharSprite_SetAnimState6(WiFi2DCharSprite *param0, int param1)
{
    param0->unk_10 = param1;
    Sprite_SetAnimNoRestart(param0->unk_04, 5 + param0->unk_10);
}

static void WiFi2DCharSprite_SetAnimState7(WiFi2DCharSprite *param0, int param1)
{
    param0->unk_10 = param1;
    Sprite_SetAnimNoRestart(param0->unk_04, 5 + param0->unk_10);
}

static void WiFi2DCharSprite_SetAnimState8(WiFi2DCharSprite *param0, int param1)
{
    param0->unk_10 = param1;
    Sprite_SetAnimNoRestart(param0->unk_04, 5 + param0->unk_10);
}

static void WiFi2DCharSprite_UpdateAnimState1(WiFi2DCharSprite *param0)
{
    Sprite_UpdateAnim(param0->unk_04, (2 * FX32_ONE));
}

static void WiFi2DCharSprite_UpdateAnimState2(WiFi2DCharSprite *param0)
{
    Sprite_UpdateAnim(param0->unk_04, (2 * FX32_ONE));
}

static void WiFi2DCharSprite_UpdateAnimState3(WiFi2DCharSprite *param0)
{
    if (param0->unk_14 == 0) {
        Sprite_SetAnimFrame(param0->unk_04, 1);
    } else {
        Sprite_SetAnim(param0->unk_04, 5 + param0->unk_10);
    }
}

static void WiFi2DCharSprite_UpdateAnimState4(WiFi2DCharSprite *param0)
{
    Sprite_UpdateAnim(param0->unk_04, (2 * FX32_ONE));
}

static void WiFi2DCharSprite_UpdateAnimState5(WiFi2DCharSprite *param0)
{
    Sprite_UpdateAnim(param0->unk_04, (FX32_ONE));
}

static void WiFi2DCharSprite_UpdateAnimState6(WiFi2DCharSprite *param0)
{
    Sprite_UpdateAnim(param0->unk_04, (FX32_ONE));
}

static void WiFi2DCharSprite_UpdateAnimState7(WiFi2DCharSprite *param0)
{
    Sprite_UpdateAnim(param0->unk_04, (8 * FX32_ONE));
}

static void WiFi2DCharSprite_UpdateAnimState8(WiFi2DCharSprite *param0)
{
    Sprite_UpdateAnim(param0->unk_04, (6 * FX32_ONE));
}

static BOOL WiFi2DCharSprite_IsFree(const WiFi2DCharSprite *param0)
{
    if (param0->unk_04 == NULL) {
        return 1;
    }

    return 0;
}

static void WiFi2DCharManager_LoadPaletteBuffer(WiFi2DCharManager *param0, SpriteResource *param1, u32 param2)
{
    NNSG2dPaletteData *v0;
    u32 v1[2];

    v0 = SpriteResource_GetPaletteFade(param1);
    v1[0] = SpriteTransfer_GetPlttOffset(param1, NNS_G2D_VRAM_TYPE_2DMAIN);
    v1[1] = SpriteTransfer_GetPlttOffset(param1, NNS_G2D_VRAM_TYPE_2DSUB);

    if (v1[0] != (NNS_G2D_VRAM_ADDR_NOT_INITIALIZED)) {
        PaletteData_LoadBuffer(param0->unk_04, v0->pRawData, PLTTBUF_MAIN_OBJ, PLTT_DEST(v1[0]), param2 * PALETTE_SIZE_BYTES);
    }

    if (v1[1] != (NNS_G2D_VRAM_ADDR_NOT_INITIALIZED)) {
        PaletteData_LoadBuffer(param0->unk_04, v0->pRawData, PLTTBUF_SUB_OBJ, PLTT_DEST(v1[1]), param2 * PALETTE_SIZE_BYTES);
    }
}
