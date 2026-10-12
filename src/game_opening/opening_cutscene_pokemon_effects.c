#include "game_opening/opening_cutscene_pokemon_effects.h"

#include <nitro.h>
#include <string.h>

#include "camera.h"
#include "heap.h"
#include "particle_system.h"
#include "pokemon.h"
#include "pokemon_sprite.h"
#include "rtc.h"
#include "spl.h"
#include "g3_buffer.h"

typedef struct OpeningCutscenePokemonEffects_t {
    PokemonSpriteManager *unk_00;
    PokemonSprite *unk_04[3];
    BOOL unk_10;
    void *unk_14;
    ParticleSystem *unk_18;
    int unk_1C[3];
    u8 unk_28;
    u8 unk_29;
} OpeningCutscenePokemonEffects;

typedef struct {
    int unk_00;
    int unk_04;
} OpeningCutscenePokemonSpriteParams;

typedef BOOL (*OpeningCutscenePokemonAnimFunc)(OpeningCutscenePokemonEffects *, const u8);

typedef struct {
    OpeningCutscenePokemonAnimFunc unk_00;
    OpeningCutscenePokemonAnimFunc unk_04;
} OpeningCutscenePokemonAnimPair;

static void OpeningCutscenePokemonEffects_DrawParticles(void);
static void OpeningCutscenePokemonEffects_EmitterCallback(SPLEmitter *param0);
static BOOL OpeningCutscenePokemon_Anim0(OpeningCutscenePokemonEffects *param0, const u8 param1);
static BOOL OpeningCutscenePokemon_Anim1(OpeningCutscenePokemonEffects *param0, const u8 param1);
static BOOL OpeningCutscenePokemon_Anim2(OpeningCutscenePokemonEffects *param0, const u8 param1);
static BOOL OpeningCutscenePokemon_Anim3(OpeningCutscenePokemonEffects *param0, const u8 param1);
static BOOL OpeningCutscenePokemon_Anim4(OpeningCutscenePokemonEffects *param0, const u8 param1);
static BOOL OpeningCutscenePokemon_Anim5(OpeningCutscenePokemonEffects *param0, const u8 param1);

static const OpeningCutscenePokemonSpriteParams sOpeningCutscenePokemonSpriteParams[3] = {
    { 0x5C, 0xC0 },
    { 0xE0, 0xC0 },
    { 0x50, 0xC0 }
};

static u32 OpeningCutscenePokemon_AllocTexture(u32 param0, BOOL param1)
{
    u32 v0;
    NNSGfdTexKey v1;

    v1 = NNS_GfdAllocTexVram(param0, param1, 0);
    ParticleSystem_RegisterTextureKey(v1);

    GF_ASSERT(v1 != NNS_GFD_ALLOC_ERROR_TEXKEY);

    v0 = NNS_GfdGetTexKeyAddr(v1);

    return v0;
}

static u32 OpeningCutscenePokemon_AllocPalette(u32 param0, BOOL param1)
{
    NNSGfdPlttKey v0;
    u32 v1;

    v0 = NNS_GfdAllocPlttVram(param0, param1, NNS_GFD_ALLOC_FROM_LOW);

    if (v0 == NNS_GFD_ALLOC_ERROR_PLTTKEY) {
        GF_ASSERT(FALSE);
    }

    ParticleSystem_RegisterPaletteKey(v0);

    v1 = NNS_GfdGetPlttKeyAddr(v0);

    return v1;
}

const int OpeningCutscenePokemonEffects_GetSize(void)
{
    return sizeof(OpeningCutscenePokemonEffects);
}

ParticleSystem *OpeningCutscenePokemonEffects_GetParticleSystem(OpeningCutscenePokemonEffects *param0)
{
    GF_ASSERT(param0 != NULL && param0->unk_18 != NULL);
    return param0->unk_18;
}

SPLEmitter *OpeningCutscenePokemonEffects_CreateEmitter(OpeningCutscenePokemonEffects *param0, int param1)
{
    GF_ASSERT(param0 != NULL && param0->unk_18 != NULL);

    ParticleSystem_SetCameraProjection(param0->unk_18, 1);
    return ParticleSystem_CreateEmitterWithCallback(param0->unk_18, param1, NULL, NULL);
}

void OpeningCutscenePokemonEffects_Init(OpeningCutscenePokemonEffects *param0)
{
    u8 v0;
    PokemonSpriteTemplate v1;
    Camera *camera;
    void *v3;
    int v4[3] = { 389, 392, 395 };
    int v5[3];
    int v6, v7;
    RTCTime v8;

    RTC_GetCurrentTime(&v8);

    v6 = (v8.hour * v8.minute + v8.second) & 1;
    v7 = v8.second % 3;

    for (v0 = 0; v0 < 3; v0++) {
        v5[v0] = v4[v7];
        param0->unk_1C[v0] = v7;

        if (v6) {
            v7++;
        } else {
            v7--;
        }

        if (v7 >= 3) {
            v7 = 0;
        } else if (v7 < 0) {
            v7 = 3 - 1;
        }
    }

    param0->unk_00 = PokemonSpriteManager_New(HEAP_ID_76);

    for (v0 = 0; v0 < 3; v0++) {
        BuildPokemonSpriteTemplate(&v1, v5[v0], 0, 2, 0, NULL, NULL);
        param0->unk_04[v0] = PokemonSpriteManager_CreateSprite(param0->unk_00, &v1, sOpeningCutscenePokemonSpriteParams[param0->unk_1C[v0]].unk_00, sOpeningCutscenePokemonSpriteParams[param0->unk_1C[v0]].unk_04, 1023, v0, NULL, NULL);
        PokemonSprite_SetAttribute(param0->unk_04[v0], MON_SPRITE_HIDE, 1);
    }

    param0->unk_10 = 1;

    ParticleSystem_ZeroAll();

    param0->unk_14 = Heap_Alloc(HEAP_ID_76, 0x4800);
    param0->unk_18 = ParticleSystem_New(OpeningCutscenePokemon_AllocTexture, OpeningCutscenePokemon_AllocPalette, param0->unk_14, 0x4800, 1, HEAP_ID_76);
    camera = ParticleSystem_GetCamera(param0->unk_18);

    Camera_SetClipping(FX32_ONE, FX32_ONE * 900, camera);

    v3 = ParticleSystem_LoadResourceFromNARC(NARC_INDEX_PARTICLEDATA__PARTICLEDATA, 4, HEAP_ID_76);
    ParticleSystem_SetResource(param0->unk_18, v3, (1 << 1) | (1 << 3), 1);
}

void OpeningCutscenePokemonEffects_Free(OpeningCutscenePokemonEffects *param0)
{
    ParticleSystem_Free(param0->unk_18);
    Heap_Free(param0->unk_14);
    PokemonSpriteManager_Free(param0->unk_00);
}

void OpeningCutscenePokemonEffects_UpdateSprites(OpeningCutscenePokemonEffects *param0)
{
    if (param0 != NULL) {
        PokemonSpriteManager_UpdateCharAndPltt(param0->unk_00);
    }
}

void OpeningCutscenePokemonEffects_Draw(OpeningCutscenePokemonEffects *param0)
{
    if (param0 != NULL) {
        NNS_G3dGeFlushBuffer();
        G3_ResetG3X();
        NNS_G2dSetupSoftwareSpriteCamera();
        PokemonSpriteManager_DrawSprites(param0->unk_00);
        OpeningCutscenePokemonEffects_DrawParticles();
        G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
    }
}

static const OpeningCutscenePokemonAnimPair sOpeningCutscenePokemonAnimPairs[3] = {
    { OpeningCutscenePokemon_Anim0, OpeningCutscenePokemon_Anim1 },
    { OpeningCutscenePokemon_Anim2, OpeningCutscenePokemon_Anim3 },
    { OpeningCutscenePokemon_Anim4, OpeningCutscenePokemon_Anim5 }
};

static const int sOpeningCutscenePokemonEmitterIds[3][3] = {
    { 0x6, 0x7, 0x8 },
    { 0x3, 0x4, 0x5 },
    { 0x0, 0x1, 0x2 }
};

BOOL OpeningCutscenePokemonEffects_RunAnimation(OpeningCutscenePokemonEffects *param0, const u8 param1, const int param2)
{
    u8 *v0 = &param0->unk_28;

    switch (*v0) {
    case 0:
        G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_OBJ, 1);
        PokemonSprite_SetAttribute(param0->unk_04[param1], MON_SPRITE_SCALE_X, 0x400);
        PokemonSprite_SetAttribute(param0->unk_04[param1], MON_SPRITE_SCALE_Y, 0x400);
        PokemonSprite_SetAttribute(param0->unk_04[param1], MON_SPRITE_HIDE, 0);
        (*v0)++;
    case 1:
        if (sOpeningCutscenePokemonAnimPairs[param0->unk_1C[param1]].unk_00(param0, param1)) {
            param0->unk_29 = 0;
            (*v0)++;
        }
        break;
    case 2:
        ParticleSystem_SetCameraProjection(param0->unk_18, 1);
        ParticleSystem_CreateEmitterWithCallback(param0->unk_18, sOpeningCutscenePokemonEmitterIds[param0->unk_1C[param1]][0], OpeningCutscenePokemonEffects_EmitterCallback, param0->unk_04[param1]);
        ParticleSystem_CreateEmitterWithCallback(param0->unk_18, sOpeningCutscenePokemonEmitterIds[param0->unk_1C[param1]][1], OpeningCutscenePokemonEffects_EmitterCallback, param0->unk_04[param1]);
        ParticleSystem_CreateEmitterWithCallback(param0->unk_18, sOpeningCutscenePokemonEmitterIds[param0->unk_1C[param1]][2], OpeningCutscenePokemonEffects_EmitterCallback, param0->unk_04[param1]);
        (*v0)++;
        break;
    case 3:
        if (ParticleSystem_GetActiveEmitterCount(param0->unk_18) == 0) {
            G2_SetWndOutsidePlane(GX_WND_PLANEMASK_OBJ, 1);
            (*v0)++;
        }
        break;
    case 4:
        if (sOpeningCutscenePokemonAnimPairs[param0->unk_1C[param1]].unk_04(param0, param1)) {
            PokemonSprite_SetAttribute(param0->unk_04[param1], MON_SPRITE_HIDE, 1);
            param0->unk_29 = 0;
            (*v0)++;
        }
        break;
    case 5:
        param0->unk_29++;

        if (param0->unk_29 >= 20) {
            param0->unk_29 = 0;
            (*v0) = 0;
            return 1;
        }
    }

    return 0;
}

static BOOL OpeningCutscenePokemon_Anim0(OpeningCutscenePokemonEffects *param0, const u8 param1)
{
    PokemonSprite *v0 = param0->unk_04[param1];

    PokemonSprite_AddAttribute(v0, MON_SPRITE_X_CENTER, 6);
    PokemonSprite_AddAttribute(v0, MON_SPRITE_Y_CENTER, -16);

    PokemonSprite_AddAttribute(v0, MON_SPRITE_SCALE_X, -0x80);
    PokemonSprite_AddAttribute(v0, MON_SPRITE_SCALE_Y, -0x80);

    param0->unk_29++;

    if (param0->unk_29 >= 6) {
        PokemonSprite_SetAttribute(v0, MON_SPRITE_SCALE_X, 0x100);
        PokemonSprite_SetAttribute(v0, MON_SPRITE_SCALE_Y, 0x100);
        return 1;
    }

    return 0;
}

static BOOL OpeningCutscenePokemon_Anim1(OpeningCutscenePokemonEffects *param0, const u8 param1)
{
    PokemonSprite *v0 = param0->unk_04[param1];

    PokemonSprite_AddAttribute(v0, MON_SPRITE_X_CENTER, -3);
    PokemonSprite_AddAttribute(v0, MON_SPRITE_Y_CENTER, -18);

    param0->unk_29++;

    if (param0->unk_29 >= 6) {
        PokemonSprite_SetAttribute(v0, MON_SPRITE_SCALE_X, 0x100);
        PokemonSprite_SetAttribute(v0, MON_SPRITE_SCALE_Y, 0x100);
        return 1;
    }

    return 0;
}

static BOOL OpeningCutscenePokemon_Anim2(OpeningCutscenePokemonEffects *param0, const u8 param1)
{
    PokemonSprite *v0 = param0->unk_04[param1];

    PokemonSprite_AddAttribute(v0, MON_SPRITE_X_CENTER, -16);
    PokemonSprite_AddAttribute(v0, MON_SPRITE_Y_CENTER, -16);

    PokemonSprite_AddAttribute(v0, MON_SPRITE_SCALE_X, -0x80);
    PokemonSprite_AddAttribute(v0, MON_SPRITE_SCALE_Y, -0x80);

    param0->unk_29++;

    if (param0->unk_29 >= 6) {
        PokemonSprite_SetAttribute(v0, MON_SPRITE_SCALE_X, 0x100);
        PokemonSprite_SetAttribute(v0, MON_SPRITE_SCALE_Y, 0x100);
        return 1;
    }

    return 0;
}

static BOOL OpeningCutscenePokemon_Anim3(OpeningCutscenePokemonEffects *param0, const u8 param1)
{
    PokemonSprite *v0 = param0->unk_04[param1];

    PokemonSprite_AddAttribute(v0, MON_SPRITE_X_CENTER, -6);
    PokemonSprite_AddAttribute(v0, MON_SPRITE_Y_CENTER, -16);

    param0->unk_29++;

    if (param0->unk_29 >= 6) {
        PokemonSprite_SetAttribute(v0, MON_SPRITE_SCALE_X, 0x100);
        PokemonSprite_SetAttribute(v0, MON_SPRITE_SCALE_Y, 0x100);
        return 1;
    }

    return 0;
}

static BOOL OpeningCutscenePokemon_Anim4(OpeningCutscenePokemonEffects *param0, const u8 param1)
{
    PokemonSprite *v0 = param0->unk_04[param1];

    PokemonSprite_AddAttribute(v0, MON_SPRITE_X_CENTER, 8);
    PokemonSprite_AddAttribute(v0, MON_SPRITE_Y_CENTER, -16);

    PokemonSprite_AddAttribute(v0, MON_SPRITE_SCALE_X, -0x80);
    PokemonSprite_AddAttribute(v0, MON_SPRITE_SCALE_Y, -0x80);

    param0->unk_29++;

    if (param0->unk_29 >= 6) {
        PokemonSprite_SetAttribute(v0, MON_SPRITE_SCALE_X, 0x100);
        PokemonSprite_SetAttribute(v0, MON_SPRITE_SCALE_Y, 0x100);
        return 1;
    }

    return 0;
}

static BOOL OpeningCutscenePokemon_Anim5(OpeningCutscenePokemonEffects *param0, const u8 param1)
{
    PokemonSprite *v0 = param0->unk_04[param1];

    PokemonSprite_AddAttribute(v0, MON_SPRITE_X_CENTER, 6);
    PokemonSprite_AddAttribute(v0, MON_SPRITE_Y_CENTER, -20);

    param0->unk_29++;

    if (param0->unk_29 >= 6) {
        PokemonSprite_SetAttribute(v0, MON_SPRITE_SCALE_X, 0x100);
        PokemonSprite_SetAttribute(v0, MON_SPRITE_SCALE_Y, 0x100);
        return 1;
    }

    return 0;
}

static void OpeningCutscenePokemonEffects_DrawParticles(void)
{
    int v0 = ParticleSystem_DrawAll();

    ParticleSystem_UpdateAll();
}

static void OpeningCutscenePokemonEffects_EmitterCallback(SPLEmitter *param0)
{
    PokemonSprite *v0 = ParticleSystem_GetEmitterCallbackParam();
    VecFx32 v1 = { 0, 0, 0 };

    v1.x = 172 * (PokemonSprite_GetAttribute(v0, MON_SPRITE_X_CENTER) - 128);
    v1.y = 172 * (PokemonSprite_GetAttribute(v0, MON_SPRITE_Y_CENTER) - 96);
    v1.z = 0x40;

    SPLEmitter_SetPos(param0, &v1);
}
