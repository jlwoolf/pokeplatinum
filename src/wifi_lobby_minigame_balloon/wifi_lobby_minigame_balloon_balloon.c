#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_balloon.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_app.h"
#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_graphics.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_game.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_score_packet.h"

#include "easy3d.h"
#include "heap.h"
#include "inlines.h"
#include "narc.h"
#include "palette.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "system.h"

typedef struct {
    fx32 x;
    fx32 y;
} WiFiLobbyMinigameBalloonMeshVertex;

typedef struct {
    WiFiLobbyMinigameBalloonMeshVertex topLeft;
    WiFiLobbyMinigameBalloonMeshVertex bottomLeft;
    WiFiLobbyMinigameBalloonMeshVertex topRight;
    WiFiLobbyMinigameBalloonMeshVertex bottomRight;
} WiFiLobbyMinigameBalloonMeshQuad;

typedef struct {
    WiFiLobbyMinigameBalloonMeshVertex topLeft;
    WiFiLobbyMinigameBalloonMeshVertex bottomLeft;
    WiFiLobbyMinigameBalloonMeshVertex topRight;
    WiFiLobbyMinigameBalloonMeshVertex bottomRight;
} WiFiLobbyMinigameBalloonMeshTexCoord;

typedef struct WiFiLobbyMinigameBalloonBalloon_t {
    NNSG3dResFileHeader *textureFile;
    NNSG3dResTex *texture;
    u16 angle;
    WiFiLobbyMinigameBalloonMeshQuad meshQuads[8];
    WiFiLobbyMinigameBalloonMeshTexCoord texCoords[8];
    int touchX;
    int touchY;
    int touchHeld;
    int touchPressed;
    int centerX;
    int unk_220;
    int touchStartX;
    int touchStartY;
    int touchOffsetY;
    fx32 baselineY;
    ManagedSprite *sprite;
    int held;
    int lastTouchY;
    int grabStretch;
    int stretch;
    fx32 springback;
    u16 *basePalette;
    u16 *paletteBuffer;
    u32 paletteSize;
    u32 paletteVramAddr;
    s32 stretchLevel;
    fx32 scaleX;
    fx32 scaleY;
    s16 flashTimer;
    s16 bumpY;
    s16 bumpX;
    int balloonLevel;
    u8 released;
    u8 flashPhase;
    u8 paletteDirty;
} WiFiLobbyMinigameBalloonBalloon;

static void WiFiLobbyMinigameBalloonBalloon_LoadTexture(WiFiLobbyMinigameBalloonBalloon *param0);
static void WiFiLobbyMinigameBalloonBalloon_InitMesh(WiFiLobbyMinigameBalloonBalloon *param0);
static void WiFiLobbyMinigameBalloonBalloon_InitTexCoords(WiFiLobbyMinigameBalloonBalloon *param0);
static void WiFiLobbyMinigameBalloonBalloon_DrawMesh(WiFiLobbyMinigameBalloonBalloon *param0);
static void WiFiLobbyMinigameBalloonBalloon_Draw(WiFiLobbyMinigameBalloonBalloon *param0);
static BOOL WiFiLobbyMinigameBalloonBalloon_CheckTouch(WiFiLobbyMinigameBalloonBalloon *param0);
static int WiFiLobbyMinigameBalloonBalloon_UpdatePhysics(WiFiLobbyMinigameBalloonBalloon *param0);
static int WiFiLobbyMinigameBalloonBalloon_DeformMesh(WiFiLobbyMinigameBalloonBalloon *param0, int param1, fx32 param2);
static int WiFiLobbyMinigameBalloonBalloon_GetTouchZone(WiFiLobbyMinigameBalloonBalloon *param0, int param1);
static int WiFiLobbyMinigameBalloonBalloon_ClampDeform(WiFiLobbyMinigameBalloonBalloon *param0, fx32 param1, fx32 param2, fx32 param3, fx32 *param4, fx32 *param5);
static fx32 WiFiLobbyMinigameBalloonBalloon_CalcArea(WiFiLobbyMinigameBalloonBalloon *param0);
static int WiFiLobbyMinigameBalloonBalloon_CalcStretchPercent(WiFiLobbyMinigameBalloonBalloon *param0);
static void WiFiLobbyMinigameBalloonBalloon_MeshToTexCoord(fx32 param0, fx32 param1, fx16 *param2, fx16 *param3);
static void WiFiLobbyMinigameBalloonBalloon_Release(WiFiLobbyMinigameBalloonBalloon *param0);
static int WiFiLobbyMinigameBalloonBalloon_CalcScore(WiFiLobbyMinigameBalloonBalloon *param0, int param1);
static void WiFiLobbyMinigameBalloonBalloon_UpdateStretch(WiFiLobbyMinigameBalloonBalloon *param0, int param1);
static void WiFiLobbyMinigameBalloonBalloon_UploadPalette(WiFiLobbyMinigameBalloonBalloon *param0);
static void WiFiLobbyMinigameBalloonBalloon_BlendPalette(WiFiLobbyMinigameBalloonBalloon *param0, int param1);
static BOOL WiFiLobbyMinigameBalloonBalloon_AddStretch(WiFiLobbyMinigameBalloonBalloon *param0, int param1);
static void WiFiLobbyMinigameBalloonBalloon_ResetStretch(WiFiLobbyMinigameBalloonBalloon *param0);
static void WiFiLobbyMinigameBalloonBalloon_UpdatePopFlash(WiFiLobbyMinigameBalloonBalloon *param0);
static void WiFiLobbyMinigameBalloonBalloon_PlayPopEffects(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonBalloon *param1, int param2, int param3);
void WiFiLobbyMinigameBalloonBalloon_SetMaterialColors(BOOL param0, BOOL param1);
void WiFiLobbyMinigameBalloonBalloon_SetShininess();
static void WiFiLobbyMinigameBalloonBalloon_LoadSpriteGraphics(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloonBalloon_FreeSpriteGraphics(WiFiLobbyMinigameBalloonGame *param0);
static ManagedSprite *WiFiLobbyMinigameBalloonBalloon_CreateSprite(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloonBalloon_UpdateSprite(WiFiLobbyMinigameBalloonBalloon *param0, ManagedSprite *param1);
static void WiFiLobbyMinigameBalloonBalloon_FreeSprite(ManagedSprite *param0);

static const fx16 sMeshNormals[3 * 6] = {
    0x0,
    0x0,
    FX16_ONE - 1,
    0x0,
    FX16_ONE - 1,
    0x0,
    FX16_ONE - 1,
    0x0,
    0x0,
    0x0,
    0x0,
    -FX16_ONE + 1,
    0x0,
    -FX16_ONE + 1,
    0x0,
    -FX16_ONE + 1,
    0x0,
    0x0
};

static const SpriteTemplate sBalloonSpriteTemplate = {
    0x0,
    0x0,
    0x0,
    0x0,
    0xE,
    0x0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0x2713, 0x2715, 0x2713, 0x2713, 0xFFFFFFFF, 0xFFFFFFFF },
    0x1,
    0x0
};

static const struct {
    u8 minX;
    u8 maxX;
    u8 yOffset;
    u8 maxY;
} sTouchZones[] = {
    { 0x40, 0xC0, 0x10, 0xA8 },
    { 0x28, 0xD8, 0x0, 0xA8 },
    { 0x54, 0xAC, 0x8, 0xA8 }
};

extern const s32 sScoreMultipliers[];

inline void inline_WiFiLobbyMinigameBalloonBalloon_SetNormal(int param0)
{
    NNS_G3dGeNormal(sMeshNormals[param0 * 3], sMeshNormals[param0 * 3 + 1], sMeshNormals[param0 * 3 + 2]);
}

WiFiLobbyMinigameBalloonBalloon *WiFiLobbyMinigameBalloonBalloon_New(WiFiLobbyMinigameBalloonGame *param0)
{
    WiFiLobbyMinigameBalloonBalloon *v0 = Heap_Alloc(HEAP_ID_110, sizeof(WiFiLobbyMinigameBalloonBalloon));
    MI_CpuClear8(v0, sizeof(WiFiLobbyMinigameBalloonBalloon));
    v0->balloonLevel = param0->context->balloonLevel;

    WiFiLobbyMinigameBalloonBalloon_LoadTexture(v0);
    WiFiLobbyMinigameBalloonBalloon_InitMesh(v0);
    WiFiLobbyMinigameBalloonBalloon_InitTexCoords(v0);

    switch (param0->context->balloonLevel) {
    case 2:
        v0->scaleX = ((6 * 16 * FX32_ONE) - 2 * 16 * FX32_ONE);
        v0->scaleY = ((6 * 16 * FX32_ONE) + 1 * 16 * FX32_ONE / 2);
        break;
    case 1:
        v0->scaleX = ((6 * 16 * FX32_ONE) + 3 * 16 * FX32_ONE);
        v0->scaleY = ((6 * 16 * FX32_ONE) + 1 * 16 * FX32_ONE);
        break;
    default:
        v0->scaleX = (6 * 16 * FX32_ONE);
        v0->scaleY = (6 * 16 * FX32_ONE);
        break;
    }

    v0->centerX = 128;
    v0->unk_220 = 40;

    WiFiLobbyMinigameBalloonBalloon_LoadSpriteGraphics(param0);
    v0->sprite = WiFiLobbyMinigameBalloonBalloon_CreateSprite(param0);
    WiFiLobbyMinigameBalloonBalloon_UpdateSprite(v0, v0->sprite);

    v0->springback = 0x2000;

    return v0;
}

void WiFiLobbyMinigameBalloonBalloon_Free(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonBalloon *param1)
{
    WiFiLobbyMinigameBalloonBalloon_FreeSprite(param1->sprite);
    WiFiLobbyMinigameBalloonBalloon_FreeSpriteGraphics(param0);

    Heap_Free(param1->textureFile);
    Heap_Free(param1->basePalette);
    Heap_Free(param1->paletteBuffer);
    Heap_Free(param1);
}

void WiFiLobbyMinigameBalloonBalloon_Update(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonBalloon *param1)
{
    param1->stretch = 0;

    if (param0->phase == 2) {
        param1->touchX = param0->introBanner.x;
        param1->touchY = param0->introBanner.y;
        param1->touchHeld = param0->introBanner.touchHeld;
        param1->touchPressed = param0->introBanner.touchPressed;
    } else if ((param0->gameStarted == 0) || (param0->gameEnded == 1)) {
        param1->touchX = 0;
        param1->touchY = 0;
        param1->touchHeld = 0;
        param1->touchPressed = 0;
    } else {
        param1->touchX = gSystem.touchX;
        param1->touchY = gSystem.touchY;
        param1->touchHeld = gSystem.touchHeld;
        param1->touchPressed = gSystem.touchPressed;
    }

    WiFiLobbyMinigameBalloonBalloon_CheckTouch(param1);

    if (param1->touchHeld == 0) {
        WiFiLobbyMinigameBalloonBalloon_Release(param1);
        if ((param1->meshQuads[0].topRight.y == 0) && (param1->meshQuads[0].topRight.y == 0)) {
            param1->released = 0;
        }
    }

    WiFiLobbyMinigameBalloonBalloon_UpdatePhysics(param1);
    WiFiLobbyMinigameBalloonBalloon_Draw(param1);
    WiFiLobbyMinigameBalloonBalloon_UpdateSprite(param1, param1->sprite);

    if (param1->flashTimer > 0) {
        param1->flashTimer += 8;

        if (param1->flashTimer > 30) {
            param1->flashTimer = 30;
        }

        WiFiLobbyMinigameBalloonBalloon_UpdatePopFlash(param1);
    }

    if ((param0->gameEnded == 0) && (param0->gameStarted == 1)) {
        if (param1->stretch > 0) {
            WiFiLobbyMinigameBalloonScorePacket v0;
            int v1 = 0, v2 = 0;
            s32 v3;

            if (param1->stretchLevel < 800) {
                v1 = WiFiLobbyMinigameBalloonBalloon_AddStretch(param1, param1->stretch);

                if (v1 == 1) {
                    param1->flashTimer = 8;
                    param1->flashPhase = 0;
                    Sound_PlayEffect(SEQ_SE_PL_BALLOON01_sseq);
                }
            } else {
                WiFiLobbyMinigameBalloonBalloon_ResetStretch(param1);
                param1->flashTimer = 0;
                v2 = 1;
            }

            v3 = WiFiLobbyMinigameBalloonBalloon_CalcScore(param1, param1->stretch);

            if (v2 == 1) {
                v3 += v3 * 25 / 100;
            }

            WiFiLobbyMinigameBalloon_InitScorePacket(param0, param0->balloonLevel, v3, &v0);
            WiFiLobbyMinigameBalloon_QueueScorePacket(param0, &v0);
            WiFiLobbyMinigameBalloon_SpawnPopEffect(param0, &v0);
            WiFiLobbyMinigameBalloonBalloon_UpdateStretch(param1, param1->stretch);
            WiFiLobbyMinigameBalloonBalloon_PlayPopEffects(param0, param1, param1->stretch, v2);
            param1->stretch = 0;
        }
    }
}

void WiFiLobbyMinigameBalloonBalloon_CommitPalette(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonBalloon *param1)
{
    if (param1->paletteDirty == 1) {
        param1->paletteDirty = 0;
        WiFiLobbyMinigameBalloonBalloon_UploadPalette(param1);
    }
}

static int WiFiLobbyMinigameBalloonBalloon_CalcScore(WiFiLobbyMinigameBalloonBalloon *param0, int param1)
{
    int v0;

    if (param1 >= 98) {
        v0 = 1200;
    } else {
        v0 = param1 * 10;
    }

    v0 = v0 * sScoreMultipliers[param0->balloonLevel] / 100;
    return v0;
}

static void WiFiLobbyMinigameBalloonBalloon_UpdateStretch(WiFiLobbyMinigameBalloonBalloon *param0, int param1)
{
    if (param0->stretch >= 98) {
        param0->springback += 0x1000;
    } else if (param0->stretch >= 98) {
        param0->springback += 0x1000;
    } else {
        param0->springback = 0x2000;
    }

    if (param0->springback > 0x11000) {
        param0->springback = 0x11000;
    }
}

static void WiFiLobbyMinigameBalloonBalloon_PlayPopEffects(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonBalloon *param1, int param2, int param3)
{
    if ((param3 == 1) && (param1->stretch >= 98)) {
        WiFiLobbyMinigameBalloon_CreateParticleEmitter(param0, 0);
        Sound_PlayEffect(SEQ_SE_PL_BALLOON04_sseq);
    } else if (param1->stretch >= 98) {
        (void)0;
    } else {
        if (param1->meshQuads[0].topLeft.y < param1->meshQuads[0].topRight.y) {
            WiFiLobbyMinigameBalloon_CreateParticleEmitter(param0, 2);
            Sound_PlayEffect(SEQ_SE_PL_BALLOON03_sseq);
        } else if (param1->meshQuads[0].topLeft.y > param1->meshQuads[0].topRight.y) {
            WiFiLobbyMinigameBalloon_CreateParticleEmitter(param0, 1);
            Sound_PlayEffect(SEQ_SE_PL_BALLOON03_sseq);
        }
    }
}

static void WiFiLobbyMinigameBalloonBalloon_Release(WiFiLobbyMinigameBalloonBalloon *param0)
{
    if (param0->held == 0) {
        return;
    }

    param0->held = 0;
    param0->lastTouchY = -1;

    {
        int v0;

        v0 = WiFiLobbyMinigameBalloonBalloon_CalcStretchPercent(param0);
        param0->stretch = param0->grabStretch - v0;

        if (param0->stretch < 25) {
            param0->stretch = 0;
        }
    }
}

static void WiFiLobbyMinigameBalloonBalloon_Draw(WiFiLobbyMinigameBalloonBalloon *param0)
{
    u32 v0, v1;

    NNS_G3dGeLightVector(GX_LIGHTID_0, FX16_SQRT1_3, -FX16_SQRT1_3, -FX16_SQRT1_3);
    NNS_G3dGeLightColor(GX_LIGHTID_0, GX_RGB(31, 31, 31));
    NNS_G3dGePushMtx();

    {
        fx16 v2 = FX_SinIdx(param0->angle);
        fx16 v3 = FX_CosIdx(param0->angle);

        NNS_G3dGeTranslate(0, (9 + 10) * FX32_ONE, -5 * FX32_ONE);
        NNS_G3dGeScale(param0->scaleX + param0->scaleX * (param0->flashTimer + param0->bumpX) / 100, param0->scaleY + param0->scaleY * param0->bumpY / 100, (FX32_ONE));
    }

    {
        NNS_G3dGeMtxMode(GX_MTXMODE_TEXTURE);
        NNS_G3dGeIdentity();
        NNS_G3dGeMtxMode(GX_MTXMODE_POSITION_VECTOR);
    }

    WiFiLobbyMinigameBalloonBalloon_SetMaterialColors(1, 1);
    WiFiLobbyMinigameBalloonBalloon_SetShininess();

    v0 = NNS_GfdGetTexKeyAddr(param0->texture->texInfo.vramKey);
    v1 = NNS_GfdGetPlttKeyAddr(param0->texture->plttInfo.vramKey);

    NNS_G3dGeTexImageParam(GX_TEXFMT_PLTT256, GX_TEXGEN_TEXCOORD, GX_TEXSIZE_S128, GX_TEXSIZE_T128, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_TRNS, v0);
    NNS_G3dGeTexPlttBase(v1, GX_TEXFMT_PLTT256);
    NNS_G3dGePolygonAttr(GX_LIGHTMASK_0, GX_POLYGONMODE_MODULATE, GX_CULL_NONE, 0, 31, GX_POLYGON_ATTR_MISC_NONE);

    WiFiLobbyMinigameBalloonBalloon_DrawMesh(param0);

    NNS_G3dGePopMtx(1);
    NNS_G3dGeFlushBuffer();
}

static void WiFiLobbyMinigameBalloonBalloon_LoadTexture(WiFiLobbyMinigameBalloonBalloon *param0)
{
    param0->textureFile = NARC_AllocAndReadWholeMemberByIndexPair(NARC_INDEX_APPLICATION__BALLOON__GRAPHIC__BALLOON_GRA, 29, 110);
    param0->texture = NNS_G3dGetTex(param0->textureFile);

    Easy3D_UploadTextureToVRAM(param0->texture);

    {
        u32 v0;
        void *v1;
        u32 v2;

        v0 = (u32)param0->texture->plttInfo.sizePltt << 3;
        v1 = (u8 *)param0->texture + param0->texture->plttInfo.ofsPlttData;
        v2 = (param0->texture->plttInfo.vramKey & 0xffff) << 3;

        GF_ASSERT(param0->basePalette == NULL);

        param0->basePalette = Heap_Alloc(HEAP_ID_110, v0);
        param0->paletteBuffer = Heap_Alloc(HEAP_ID_110, v0);

        MI_CpuCopy8(v1, param0->basePalette, v0);
        MI_CpuCopy8(v1, param0->paletteBuffer, v0);

        DC_FlushRange(param0->paletteBuffer, v0);

        param0->paletteVramAddr = v2;
        param0->paletteSize = v0;
    }

    {
        u8 *v3;
        u32 v4;

        GF_ASSERT(param0->texture->texInfo.ofsTex != 0);

        v3 = (u8 *)param0->texture + param0->texture->texInfo.ofsTex;
        v4 = (u32)(v3 - (u8 *)param0->textureFile);

        Heap_Realloc(param0->textureFile, v4);
    }
}

static void WiFiLobbyMinigameBalloonBalloon_UploadPalette(WiFiLobbyMinigameBalloonBalloon *param0)
{
    GX_BeginLoadTexPltt();
    GX_LoadTexPltt(param0->paletteBuffer, param0->paletteVramAddr, param0->paletteSize);
    GX_EndLoadTexPltt();
}

static void WiFiLobbyMinigameBalloonBalloon_BlendPalette(WiFiLobbyMinigameBalloonBalloon *param0, int param1)
{
    int v0 = (12 << 8) * param1 / 800;
    v0 = (v0 + 0x80) >> 8;

    if (v0 > 16) {
        v0 = 16;
    }

    BlendPalette(param0->basePalette, param0->paletteBuffer, param0->paletteSize / 2, v0, 0x1f);
    DC_FlushRange(param0->paletteBuffer, param0->paletteSize);

    param0->paletteDirty = 1;
}

static BOOL WiFiLobbyMinigameBalloonBalloon_AddStretch(WiFiLobbyMinigameBalloonBalloon *param0, int param1)
{
    BOOL v0 = 0;

    param0->stretchLevel += param1;

    if (param0->stretchLevel >= 800) {
        param0->stretchLevel = 800;
        v0 = 1;
    }

    WiFiLobbyMinigameBalloonBalloon_BlendPalette(param0, param0->stretchLevel);

    return v0;
}

static void WiFiLobbyMinigameBalloonBalloon_ResetStretch(WiFiLobbyMinigameBalloonBalloon *param0)
{
    param0->stretchLevel = 0;
    WiFiLobbyMinigameBalloonBalloon_BlendPalette(param0, param0->stretchLevel);
}

static void WiFiLobbyMinigameBalloonBalloon_UpdatePopFlash(WiFiLobbyMinigameBalloonBalloon *param0)
{
    if (param0->flashTimer == 0) {
        return;
    }

    param0->flashPhase++;

    if (param0->flashPhase == 4) {
        WiFiLobbyMinigameBalloonBalloon_BlendPalette(param0, param0->stretchLevel / 2);
    } else if (param0->flashPhase == 4 * 2) {
        WiFiLobbyMinigameBalloonBalloon_BlendPalette(param0, param0->stretchLevel);
        param0->flashPhase = 0;
    }
}

static const GXRgb DEMO_DIFFUSE_COL = GX_RGB(23, 23, 23);
static const GXRgb DEMO_AMBIENT_COL = GX_RGB(8, 8, 8);
static const GXRgb DEMO_SPECULAR_COL = GX_RGB(31, 31, 31);
static const GXRgb DEMO_EMISSION_COL = GX_RGB(0, 0, 0);
static const u32 LIGHTING_L_DOT_S_SHIFT = 8;

void WiFiLobbyMinigameBalloonBalloon_SetMaterialColors(BOOL param0, BOOL param1)
{
    NNS_G3dGeMaterialColorDiffAmb(DEMO_DIFFUSE_COL, DEMO_AMBIENT_COL, param0);
    NNS_G3dGeMaterialColorSpecEmi(DEMO_SPECULAR_COL, DEMO_EMISSION_COL, param1);
}

#include <nitro/code32.h>
void WiFiLobbyMinigameBalloonBalloon_SetShininess()
{
    u8 i;
    u32 v0[32];
    u8 *v1 = (u8 *)&v0[0];
    const u8 v2 = 32 * sizeof(u32);

    for (i = 0; i < v2 - 1; i++) {
        v1[i] = (u8)(((s64)(i * 2 + 1) * (i * 2 + 1) * (i * 2 + 1) * (i * 2 + 1)) >> (LIGHTING_L_DOT_S_SHIFT * (4 - 1)));
    }

    v1[v2 - 1] = 0xFF;

    NNS_G3dGeShininess(&v0[0]);
}

#include <nitro/codereset.h>
static void WiFiLobbyMinigameBalloonBalloon_InitMesh(WiFiLobbyMinigameBalloonBalloon *param0)
{
    int v0;
    fx32 v1;
    fx32 v2;

    v2 = ((-(128 * FX32_ONE)) - 0) / 8;

    for (v0 = 0; v0 < 8; v0++) {
        v1 = 0 + v0 * v2;

        param0->meshQuads[v0].topLeft.x = 0;
        param0->meshQuads[v0].topLeft.y = v1;
        param0->meshQuads[v0].bottomLeft.x = 0;
        param0->meshQuads[v0].bottomLeft.y = v1 + v2;
        param0->meshQuads[v0].topRight.x = (128 * FX32_ONE);
        param0->meshQuads[v0].topRight.y = v1;
        param0->meshQuads[v0].bottomRight.x = (128 * FX32_ONE);
        param0->meshQuads[v0].bottomRight.y = v1 + v2;
    }
}

static void WiFiLobbyMinigameBalloonBalloon_InitTexCoords(WiFiLobbyMinigameBalloonBalloon *param0)
{
    int v0;
    fx32 v1;
    fx32 v2;

    v2 = 128 * FX32_ONE / 8;

    for (v0 = 0; v0 < 8; v0++) {
        v1 = v0 * v2;

        param0->texCoords[v0].topLeft.x = 0;
        param0->texCoords[v0].topLeft.y = v1;
        param0->texCoords[v0].bottomLeft.x = 0;
        param0->texCoords[v0].bottomLeft.y = v1 + v2;
        param0->texCoords[v0].topRight.x = 128 * FX32_ONE;
        param0->texCoords[v0].topRight.y = v1;
        param0->texCoords[v0].bottomRight.x = 128 * FX32_ONE;
        param0->texCoords[v0].bottomRight.y = v1 + v2;
    }
}

static void WiFiLobbyMinigameBalloonBalloon_DrawMesh(WiFiLobbyMinigameBalloonBalloon *param0)
{
    int v0;
    fx64 v1, v2;
    fx16 v3, v4;

    for (v0 = 0; v0 < 8; v0++) {
        NNS_G3dGeBegin(GX_BEGIN_QUADS);

        WiFiLobbyMinigameBalloonBalloon_MeshToTexCoord(param0->meshQuads[v0].topLeft.x, param0->meshQuads[v0].topLeft.y, &v3, &v4);
        NNS_G3dGeTexCoord(param0->texCoords[v0].topLeft.x, param0->texCoords[v0].topLeft.y);
        inline_WiFiLobbyMinigameBalloonBalloon_SetNormal(0);
        NNS_G3dGeVtx(v3, v4, 0);

        WiFiLobbyMinigameBalloonBalloon_MeshToTexCoord(param0->meshQuads[v0].bottomLeft.x, param0->meshQuads[v0].bottomLeft.y, &v3, &v4);
        NNS_G3dGeTexCoord(param0->texCoords[v0].bottomLeft.x, param0->texCoords[v0].bottomLeft.y);
        inline_WiFiLobbyMinigameBalloonBalloon_SetNormal(0);
        NNS_G3dGeVtx(v3, v4, 0);

        WiFiLobbyMinigameBalloonBalloon_MeshToTexCoord(param0->meshQuads[v0].bottomRight.x, param0->meshQuads[v0].bottomRight.y, &v3, &v4);
        NNS_G3dGeTexCoord(param0->texCoords[v0].bottomRight.x, param0->texCoords[v0].bottomRight.y);
        inline_WiFiLobbyMinigameBalloonBalloon_SetNormal(0);
        NNS_G3dGeVtx(v3, v4, 0);

        WiFiLobbyMinigameBalloonBalloon_MeshToTexCoord(param0->meshQuads[v0].topRight.x, param0->meshQuads[v0].topRight.y, &v3, &v4);
        NNS_G3dGeTexCoord(param0->texCoords[v0].topRight.x, param0->texCoords[v0].topRight.y);
        inline_WiFiLobbyMinigameBalloonBalloon_SetNormal(0);
        NNS_G3dGeVtx(v3, v4, 0);

        NNS_G3dGeEnd();
    }
}

static void WiFiLobbyMinigameBalloonBalloon_MeshToTexCoord(fx32 param0, fx32 param1, fx16 *param2, fx16 *param3)
{
    fx32 v0, v1;

    v0 = (FX16_ONE) * (fx64)param0 / (128 * FX32_ONE);
    v1 = (FX16_ONE) * (fx64)param1 / (128 * FX32_ONE);

    GF_ASSERT(v0 <= FX16_MAX);
    GF_ASSERT(v0 >= FX16_MIN);
    GF_ASSERT(v1 <= FX16_MAX);
    GF_ASSERT(v1 >= FX16_MIN);

    v0 -= ((FX16_ONE) / 2);
    v1 += ((FX16_ONE) / 2);

    GF_ASSERT(v0 <= FX16_MAX);
    GF_ASSERT(v0 >= FX16_MIN);
    GF_ASSERT(v1 <= FX16_MAX);
    GF_ASSERT(v1 >= FX16_MIN);

    *param2 = v0;
    *param3 = v1;
}

static BOOL WiFiLobbyMinigameBalloonBalloon_CheckTouch(WiFiLobbyMinigameBalloonBalloon *param0)
{
    int v0;

    if ((param0->held == 1) || (param0->touchPressed == 0)) {
        return 0;
    }

    v0 = (param0->baselineY >> FX32_SHIFT) + sTouchZones[param0->balloonLevel].yOffset;

    if ((param0->touchX < sTouchZones[param0->balloonLevel].minX) || (param0->touchX > sTouchZones[param0->balloonLevel].maxX) || (param0->touchY < v0) || (param0->touchY > sTouchZones[param0->balloonLevel].maxY)) {
        return 0;
    }

    param0->held = 1;
    param0->touchStartX = param0->touchX;
    param0->touchStartY = param0->touchY;
    param0->touchOffsetY = param0->touchY - v0;
    param0->baselineY = -(param0->meshQuads[0].topRight.y + (param0->meshQuads[0].topLeft.y - param0->meshQuads[0].topRight.y) / 2);
    param0->grabStretch = WiFiLobbyMinigameBalloonBalloon_CalcStretchPercent(param0);

    return 1;
}

static int WiFiLobbyMinigameBalloonBalloon_UpdatePhysics(WiFiLobbyMinigameBalloonBalloon *param0)
{
    int v0 = 0;
    fx32 v1;
    int v2;
    int v3;

    if (param0->held == 1) {
        if (param0->touchY < param0->lastTouchY) {
            param0->released = 0;
            return 0;
        } else if (param0->touchY == param0->lastTouchY) {
            param0->released = 0;
            return 1;
        }

        if ((param0->lastTouchY != -1) && (param0->touchY > param0->lastTouchY) && (Sound_IsEffectPlaying(1399) == 0)) {
            Sound_PlayEffect(SEQ_SE_PL_BALLOON02_sseq);
            param0->released = 1;
        }

        v3 = param0->touchY - param0->touchOffsetY;
        v1 = (v3 << FX32_SHIFT) - (param0->baselineY + (sTouchZones[param0->balloonLevel].yOffset << FX32_SHIFT));
        param0->lastTouchY = param0->touchY;
    } else {
        v0 = 1;
        v1 = -param0->springback;
    }

    v2 = WiFiLobbyMinigameBalloonBalloon_DeformMesh(param0, v0, v1);

    switch (v2) {
    case 0:
    default:
        break;
    case 1:
    case 2:
        WiFiLobbyMinigameBalloonBalloon_Release(param0);
        break;
    }

    param0->baselineY = -(param0->meshQuads[0].topRight.y + (param0->meshQuads[0].topLeft.y - param0->meshQuads[0].topRight.y) / 2);
    return 1;
}

static int WiFiLobbyMinigameBalloonBalloon_DeformMesh(WiFiLobbyMinigameBalloonBalloon *param0, int param1, fx32 param2)
{
    fx32 v0, v1, v2, v3, v4, v5, v6;
    fx32 v7, v8;
    fx32 v9, v10;
    u16 v11, v12;
    int v13 = 0;

    if ((param1 == 0) && (param2 < 0)) {
        (void)0;
    }

    v0 = param0->touchY << FX32_SHIFT;
    v3 = -param0->meshQuads[0].topLeft.y;
    v4 = -param0->meshQuads[0].topRight.y;
    v7 = v4 + (v3 - v4) / 2;

    switch (WiFiLobbyMinigameBalloonBalloon_GetTouchZone(param0, param1)) {
    case 0:
        v5 = v3 + param2;
        v6 = v4 + param2;
        break;
    case 1:
        v13 = WiFiLobbyMinigameBalloonBalloon_ClampDeform(param0, param2, v3, v4, &v5, &v6);
        break;
    case 2:
        v13 = WiFiLobbyMinigameBalloonBalloon_ClampDeform(param0, param2, v4, v3, &v6, &v5);
        break;
    }

    v8 = v6 + (v5 - v6) / 2;

    if ((v7 == v8) && (v3 == v5) && (v4 == v6)) {
        return 0;
    }

    if (v8 < 0) {
        v8 = 0;
    }

    if (v5 < 0) {
        v5 = 0;
    }

    if (v6 < 0) {
        v6 = 0;
    }

    if (v8 > (((128 * FX32_ONE) / 8 * (8 - 1)) - 12 * FX32_ONE)) {
        v8 = (((128 * FX32_ONE) / 8 * (8 - 1)) - 12 * FX32_ONE);
        v13 = 1;
    }

    if (v5 > (((128 * FX32_ONE) / 8 * (8 - 1)) - 12 * FX32_ONE)) {
        v5 = (((128 * FX32_ONE) / 8 * (8 - 1)) - 12 * FX32_ONE);
        v13 = 1;
    }

    if (v6 > (((128 * FX32_ONE) / 8 * (8 - 1)) - 12 * FX32_ONE)) {
        v6 = (((128 * FX32_ONE) / 8 * (8 - 1)) - 12 * FX32_ONE);
        v13 = 1;
    }

    {
        fx32 v14, v15;
        int v16;

        v16 = 64;

        switch (WiFiLobbyMinigameBalloonBalloon_GetTouchZone(param0, param1)) {
        case 0:
        default:
            if (v5 < v6) {
                v14 = v16 * FX32_ONE;
            } else if (v5 > v6) {
                v14 = -v16 * FX32_ONE;
            } else {
                v14 = 0;
            }

            v14 = v16 * FX32_ONE;
            v15 = v6 - v8;
            v11 = FX_Atan2Idx(v15, v14);
            v12 = v11 + 0x8000;
            break;
        case 2:
            v14 = v16 * FX32_ONE;
            v15 = (v6 - v8);
            v11 = FX_Atan2Idx(v15, v14);
            v12 = v11 + 0x8000;
            break;
        case 1:
            v14 = -v16 * FX32_ONE;
            v15 = v5 - v8;
            v12 = FX_Atan2Idx(v15, v14);
            v11 = v12 + 0x8000;
            break;
        }
    }

    {
        fx32 v17 = ((128 * FX32_ONE) / 2) / FX32_ONE;

        param0->meshQuads[0].topLeft.x = v17 * FX_CosIdx(v12) + ((128 * FX32_ONE) / 2);
        param0->meshQuads[0].topLeft.y = -(v17 * FX_SinIdx(v12) + v8);
        param0->meshQuads[0].topRight.x = v17 * FX_CosIdx(v11) + ((128 * FX32_ONE) / 2);
        param0->meshQuads[0].topRight.y = -(v17 * FX_SinIdx(v11) + v8);

        {
            int v18;
            fx32 v19;
            s32 v20;

            v19 = (((128 * FX32_ONE) / 8 * (8 - 1)) - v8) / (8 - 1);

            if (v11 > 0x8000) {
                v20 = -(0x10000 - v11) / (8 - 1);
            } else {
                v20 = v11 / (8 - 1);
            }

            for (v18 = 1; v18 < (8 - 1); v18++) {
                param0->meshQuads[v18].topLeft.x = v17 * FX_CosIdx(v12 - v20 * v18) + ((128 * FX32_ONE) / 2);
                param0->meshQuads[v18].topLeft.y = -(v17 * FX_SinIdx(v12 - v20 * v18) + v8 + v19 * v18);
                param0->meshQuads[v18].topRight.x = v17 * FX_CosIdx(v11 - v20 * v18) + ((128 * FX32_ONE) / 2);
                param0->meshQuads[v18].topRight.y = -(v17 * FX_SinIdx(v11 - v20 * v18) + v8 + v19 * v18);
                param0->meshQuads[v18 - 1].bottomLeft.x = param0->meshQuads[v18].topLeft.x;
                param0->meshQuads[v18 - 1].bottomLeft.y = param0->meshQuads[v18].topLeft.y;
                param0->meshQuads[v18 - 1].bottomRight.x = param0->meshQuads[v18].topRight.x;
                param0->meshQuads[v18 - 1].bottomRight.y = param0->meshQuads[v18].topRight.y;
            }
        }
    }
    if (v13 == 1) {
        return 2;
    }

    return 0;
}

static int WiFiLobbyMinigameBalloonBalloon_GetTouchZone(WiFiLobbyMinigameBalloonBalloon *param0, int param1)
{
    if (param1 == 1) {
        return 0;
    }
    if (param0->touchStartX < param0->centerX - 16) {
        return 1;
    }
    if (param0->touchStartX > param0->centerX + 16) {
        return 2;
    }

    return 0;
}

static int WiFiLobbyMinigameBalloonBalloon_ClampDeform(WiFiLobbyMinigameBalloonBalloon *param0, fx32 param1, fx32 param2, fx32 param3, fx32 *param4, fx32 *param5)
{
    int v0 = 0;

    *param4 = param2;
    *param5 = param3;

    if (param2 + param1 > (((128 * FX32_ONE) / 8 * (8 - 1)) - 12 * FX32_ONE)) {
        param1 -= (param2 + param1) - (((128 * FX32_ONE) / 8 * (8 - 1)) - 12 * FX32_ONE);
        v0 = 1;
    }

    *param4 = param2 + param1;

    if (param3 <= param2) {
        *param5 = param3 - (param1 * 25 / 100);
    } else {
        *param5 = param3;
    }

    return v0;
}

static fx32 WiFiLobbyMinigameBalloonBalloon_CalcArea(WiFiLobbyMinigameBalloonBalloon *param0)
{
    fx32 v0, v1, v2;
    fx32 v3, v4, v5;
    fx32 v6;
    int v7 = (8 - 1) - 1;

    v3 = param0->meshQuads[0].topRight.y + (param0->meshQuads[0].topLeft.y - param0->meshQuads[0].topRight.y) / 2;
    v2 = -(param0->meshQuads[v7].bottomLeft.y - v3);
    v4 = param0->meshQuads[0].topRight.x - param0->meshQuads[0].topLeft.x;
    v5 = param0->meshQuads[v7].bottomRight.x - param0->meshQuads[v7].bottomLeft.x;
    v6 = FX_Mul(v4 + v5, v2) / 2;

    return v6;
}

static int WiFiLobbyMinigameBalloonBalloon_CalcStretchPercent(WiFiLobbyMinigameBalloonBalloon *param0)
{
    fx32 v0;
    int v1;

    v0 = WiFiLobbyMinigameBalloonBalloon_CalcArea(param0);
    v1 = 100 * (fx64)v0 / ((((((128 * FX32_ONE) - 0) + ((128 * FX32_ONE) - 0)) * (fx64)(((128 * FX32_ONE) / 8 * (8 - 1)) - 12 * FX32_ONE)) >> FX32_SHIFT) / 2);

    return v1;
}

static void WiFiLobbyMinigameBalloonBalloon_LoadSpriteGraphics(WiFiLobbyMinigameBalloonGame *param0)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_APPLICATION__BALLOON__GRAPHIC__BALLOON_GRA, HEAP_ID_110);

    SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->paletteData, PLTTBUF_MAIN_OBJ, param0->spriteSystem, param0->spriteManager, v0, 58, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 10005);
    SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 55, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 10003);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 57, FALSE, 10003);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, v0, 56, FALSE, 10003);
    NARC_dtor(v0);
}

static void WiFiLobbyMinigameBalloonBalloon_FreeSpriteGraphics(WiFiLobbyMinigameBalloonGame *param0)
{
    SpriteManager_UnloadCharObjById(param0->spriteManager, 10003);
    SpriteManager_UnloadCellObjById(param0->spriteManager, 10003);
    SpriteManager_UnloadAnimObjById(param0->spriteManager, 10003);
    SpriteManager_UnloadPlttObjById(param0->spriteManager, 10005);
}

static ManagedSprite *WiFiLobbyMinigameBalloonBalloon_CreateSprite(WiFiLobbyMinigameBalloonGame *param0)
{
    ManagedSprite *v0;
    SpriteTemplate v1;

    v1 = sBalloonSpriteTemplate;
    v0 = SpriteSystem_NewSprite(param0->spriteSystem, param0->spriteManager, &v1);

    ManagedSprite_SetDrawFlag(v0, 0);
    Sprite_TickFrame(v0->sprite);

    return v0;
}

static void WiFiLobbyMinigameBalloonBalloon_UpdateSprite(WiFiLobbyMinigameBalloonBalloon *param0, ManagedSprite *param1)
{
    int v0;

    if (param0->held == 0) {
        v0 = 0;
    } else {
        v0 = WiFiLobbyMinigameBalloonBalloon_GetTouchZone(param0, 0) + 1;
    }

    ManagedSprite_SetPositionXYWithSubscreenOffset(param1, param0->centerX, (param0->baselineY >> FX32_SHIFT) + sTouchZones[param0->balloonLevel].yOffset, ((192 + 160) << FX32_SHIFT));
    ManagedSprite_SetAnim(param1, v0);
    Sprite_TickFrame(param1->sprite);
}

static void WiFiLobbyMinigameBalloonBalloon_FreeSprite(ManagedSprite *param0)
{
    Sprite_DeleteAndFreeResources(param0);
}
