#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02261870.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_minigame/wifi_lobby_minigame.h"
#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_0226432C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226139C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262A8C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226501C.h"

#include "bg_window.h"
#include "camera.h"
#include "easy3d_object.h"
#include "font.h"
#include "graphics.h"
#include "inlines.h"
#include "message.h"
#include "narc.h"
#include "palette.h"
#include "render_window.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "text.h"
#include "trainer_info.h"
#include "g3_buffer.h"

static inline void Draw3DObject(WiFiLobbyMinigameManene3DObject *param0);
static inline void SetupLighting(void);
static void InitSpriteTemplate(SpriteTemplate *param0, s16 param1, s16 param2, int param3, int param4, int param5);
void IncludeGraphicsData(void);

void WiFiLobbyMinigameManene_Draw3DObject(Easy3DObject *param0, MtxFx43 *param1, VecFx32 *param2)
{
    if (param0->visible) {
        NNS_G3dGlbFlush();
        NNS_G3dGeTranslateVec(param2);
        NNS_G3dGeMultMtx43(param1);
        NNS_G3dGlbSetBaseScale(&param0->scale);
        NNS_G3dDraw(&param0->renderObj);
    }
}

static inline void Draw3DObject(WiFiLobbyMinigameManene3DObject *param0)
{
    NNS_G3dGePushMtx();
    WiFiLobbyMinigameManene_Draw3DObject(&param0->object, &param0->matrix, &param0->position);
    NNS_G3dGePopMtx(1);
}

static inline void Draw3DObjectWithParent(WiFiLobbyMinigameManene3DObject *wk, WiFiLobbyMinigameManene3DObject *wk2)
{
    NNS_G3dGePushMtx();
    WiFiLobbyMinigameManene_Draw3DObject(&wk2->object, &wk->matrix, &wk->position);
    NNS_G3dGePopMtx(1);
}

static inline void SetupLighting(void)
{
    VecFx32 v0 = { 0, -FX32_ONE, -FX32_ONE };

    VEC_Normalize(&v0, &v0);

    NNS_G3dGlbLightVector(0, v0.x, v0.y, v0.z);
    NNS_G3dGlbLightColor(0, GX_RGB(31, 31, 31));
    NNS_G3dGlbMaterialColorDiffAmb(GX_RGB(31, 31, 31), GX_RGB(31, 31, 31), 0);
    NNS_G3dGlbMaterialColorSpecEmi(GX_RGB(31, 31, 31), GX_RGB(31, 31, 31), 0);
}

void WiFiLobbyMinigameManene_Load3DModel(WiFiLobbyMinigameManene3DObject *param0, NARC *param1, int param2)
{
    Easy3DModel_LoadFrom(&param0->model, param1, param2, HEAP_ID_106);
}

void WiFiLobbyMinigameManene_Init3DObject(WiFiLobbyMinigameManene3DObject *param0, int param1)
{
    Easy3DObject_Init(&param0->object, &param0->model);
    Easy3DObject_SetPosition(&param0->object, 0 * FX32_ONE, -20 * FX32_ONE, 0 * FX32_ONE );

    if (param1 == 0) {
        Easy3DObject_SetScale(&param0->object, FX32_CONST(1.00f), FX32_CONST(1.00f), FX32_CONST(1.00f));
    } else {
        Easy3DObject_SetScale(&param0->object, FX32_CONST(1.50f), FX32_CONST(1.50f), FX32_CONST(1.50f));
    }

    Easy3DObject_SetVisible(&param0->object, 1);

    param0->position.x = (0 * FX32_ONE);
    param0->position.y = (-20 * FX32_ONE);
    param0->position.z = (0 * FX32_ONE);
    param0->tiltX = 0.0f;
    param0->tiltY = 0.0f;
    param0->animationActive = 0;
    param0->modelLoaded = 1;
}

void WiFiLobbyMinigameManene_Release3DModel(WiFiLobbyMinigameManene3DObject *param0)
{
    param0->modelLoaded = 0;
    Easy3DModel_Release(&param0->model);
}

void WiFiLobbyMinigameManene_Draw3DScene(WiFiLobbyMinigameManeneApp *param0)
{
    G3_ResetG3X();
    Camera_ComputeViewMatrix();

    SetupLighting();

    {
        int v0;

        for (v0 = 0; v0 < 8; v0++) {
            Draw3DObject(&param0->game->decorationObjects[v0]);
            Easy3DAnim_UpdateLooped(&param0->game->decorationObjects[v0].anims[0], FX32_CONST(1));
        }
    }

    switch (param0->game->ballAnimState) {
    case 0:
        Easy3DObject_SetVisible(&param0->game->ballObjects[0].object, 1);
        Easy3DObject_SetVisible(&param0->game->ballObjects[1].object, 0);
        Easy3DObject_SetVisible(&param0->game->ballObjects[2].object, 0);
        Easy3DAnim_UpdateLooped(&param0->game->ballObjects[0].anims[param0->game->ballObjects[0].animIndex], FX32_CONST(1));
        break;
    case 1:
        Easy3DObject_SetVisible(&param0->game->ballObjects[0].object, 0);
        Easy3DObject_SetVisible(&param0->game->ballObjects[1].object, 1);
        Easy3DObject_SetVisible(&param0->game->ballObjects[2].object, 0);
        Easy3DAnim_Update(&param0->game->ballObjects[1].anims[0], FX32_CONST(1));
        break;
    case 2:
        Easy3DObject_SetVisible(&param0->game->ballObjects[0].object, 0);
        Easy3DObject_SetVisible(&param0->game->ballObjects[1].object, 0);
        Easy3DObject_SetVisible(&param0->game->ballObjects[2].object, 1);
        Easy3DAnim_Update(&param0->game->ballObjects[2].anims[0], FX32_CONST(1));
        break;
    }

    Draw3DObjectWithParent(&param0->game->ballObjects[0], &param0->game->ballObjects[param0->game->ballAnimState]);
    Draw3DObject(&param0->game->ballObject);
    Draw3DObject(&param0->game->introBallObject);

    if (param0->game->levelUpObject2.modelLoaded) {
        Draw3DObject(&param0->game->levelUpObject2);
        if (param0->game->levelUpObject2.animationActive) {
            BOOL v1[2];

            v1[0] = Easy3DAnim_Update(&param0->game->levelUpObject2.anims[0], FX32_CONST(1));
            v1[1] = Easy3DAnim_Update(&param0->game->levelUpObject2.anims[1], FX32_CONST(1));

            if (v1[0] && v1[1]) {
                param0->game->levelUpObject2.animationActive = 0;
            }
        }
    }
    if (param0->game->levelUpObject1.modelLoaded) {
        Draw3DObject(&param0->game->levelUpObject1);

        if (param0->game->levelUpObject1.animationActive) {
            Easy3DAnim_UpdateLooped(&param0->game->levelUpObject1.anims[1], FX32_CONST(1));
        }
    }

    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);
    SpriteSystem_DrawSprites(param0->resources.spriteManager);
}

void WiFiLobbyMinigameManene_SetBallAnim(WiFiLobbyMinigameManeneGame *param0, int param1)
{
    int v0 = param0->ballObjects[0].animIndex;
    int v1 = param1;

    if (v1 == v0) {
        return;
    }

    Easy3DObject_RemoveAnim(&param0->ballObjects[0].object, &param0->ballObjects[0].anims[v0]);
    param0->ballObjects[0].animIndex = param1;
    Easy3DObject_AddAnim(&param0->ballObjects[0].object, &param0->ballObjects[0].anims[v1]);
}

void WiFiLobbyMinigameManene_InitCamera(WiFiLobbyMinigameManeneApp *param0)
{
    VecFx32 v0 = { 0, 0, 0 };
    VecFx32 v1 = { 0, 0, FX32_ONE * 160 };

    Camera_InitWithTargetAndPosition(&v0, &v1, 0xb60, 0, 0, param0->resources.camera);
    Camera_SetClipping(FX32_ONE * -1000, FX32_ONE * 1000, param0->resources.camera);
    Camera_SetAsActive(param0->resources.camera);
}

static void InitSpriteTemplate(SpriteTemplate *param0, s16 param1, s16 param2, int param3, int param4, int param5)
{
    param0->x = param1;
    param0->y = param2;
    param0->z = 0;
    param0->animIdx = 0;
    param0->priority = 0;
    param0->vramType = param3;
    param0->bgPriority = 2;
    param0->vramTransfer = FALSE;
    param0->plttIdx = param4;
    param0->resources[0] = param5;
    param0->resources[1] = param5;
    param0->resources[2] = param5;
    param0->resources[3] = param5;
    param0->resources[4] = SPRITE_RESOURCE_NONE;
    param0->resources[5] = SPRITE_RESOURCE_NONE;
}

static const s16 sPlayerSpritePositions[][3] = {
    { 0x0, 0x0, 0x0 },
    { 0x80, 0x0, 0x0 },
    { 0x55, 0xAA, 0x0 },
    { 0x40, 0x80, 0xC0 }
};

void WiFiLobbyMinigameManene_CreateBackgroundSprites(WiFiLobbyMinigameManeneGame *param0)
{
    SpriteTemplate v0;
    SpriteSystem *v1 = param0->resources->spriteSystem;
    SpriteManager *v2 = param0->resources->spriteManager;
    PaletteData *v3 = param0->resources->paletteData;
    int v4;

    for (v4 = 0; v4 < (3 * 12); v4++) {
        InitSpriteTemplate(&v0, v4 * 8, 20, 1, 3, 9006);
        param0->backgroundSprites[v4] = SpriteSystem_NewSprite(v1, v2, &v0);
        ManagedSprite_SetExplicitPaletteOffset(param0->backgroundSprites[v4], 3);
        ManagedSprite_SetAnim(param0->backgroundSprites[v4], (v4 % 11) + 1);
    }

    WiFiLobbyMinigameManene_SetBackgroundSpritesVisible(param0, 0, 0);
}

void WiFiLobbyMinigameManene_CreatePlayerSprites(WiFiLobbyMinigameManeneGame *param0)
{
    SpriteTemplate v0;
    SpriteSystem *v1 = param0->resources->spriteSystem;
    SpriteManager *v2 = param0->resources->spriteManager;
    PaletteData *v3 = param0->resources->paletteData;
    int v4;
    s16 v5[] = { 72, 180, 24, 232 };

    for (v4 = 0; v4 < 4; v4++) {
        InitSpriteTemplate(&v0, v5[v4], 192 + 32, 1, 1, 9004);

        v0.bgPriority = 0;
        v0.priority = 1;
        param0->playerSprites[v4] = SpriteSystem_NewSprite(v1, v2, &v0);

        ManagedSprite_TickTwoFrames(param0->playerSprites[v4]);
        ManagedSprite_SetExplicitPaletteOffset(param0->playerSprites[v4], 1);
    }
}

void WiFiLobbyMinigameManene_FreePlayerSprites(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        Sprite_DeleteAndFreeResources(param0->playerSprites[v0]);
    }
}

void WiFiLobbyMinigameManene_SetBackgroundSpritesVisible(WiFiLobbyMinigameManeneGame *param0, BOOL param1, int param2)
{
    int v0;

    for (v0 = 0; v0 < (3 * 12); v0++) {
        ManagedSprite_SetDrawFlag(param0->backgroundSprites[v0], param1);
    }
}

void WiFiLobbyMinigameManene_TickBackgroundSprites(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;

    for (v0 = 0; v0 < (3 * 12); v0++) {
        ManagedSprite_TickTwoFrames(param0->backgroundSprites[v0]);
    }
}

void WiFiLobbyMinigameManene_FreeBackgroundSprites(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;

    for (v0 = 0; v0 < (3 * 12); v0++) {
        Sprite_DeleteAndFreeResources(param0->backgroundSprites[v0]);
    }
}

void IncludeGraphicsData(void)
{
    int dummy[][2] = {
        { 0, 2 },
        { 0, 3 },
        { 0, 4 },
        { 1, 2 },
    };

    dummy[0];
}

void WiFiLobbyMinigameManene_SetPlayerSpriteAnim(WiFiLobbyMinigameManeneGame *param0, int param1, int param2)
{
    int v0[][2] = {
        { 0, 2 },
        { 0, 3 },
        { 0, 4 },
        { 1, 2 },
    };

    int v1 = param0->playerRowIndex[param1];

    ManagedSprite_SetAnim(param0->playerSpritesLayer1[v1], v0[param2][0]);
    ManagedSprite_SetAnim(param0->playerSpritesLayer2[v1], v0[param2][1]);
}

int WiFiLobbyMinigameManene_GetPlayerSpriteAnim(WiFiLobbyMinigameManeneGame *param0, int param1)
{
    int v0[][2] = {
        { 0, 2 },
        { 0, 3 },
        { 0, 4 },
        { 1, 2 },
    };

    int v1;
    int v2[2];

    v1 = param0->playerRowIndex[param1];
    v2[0] = ManagedSprite_GetActiveAnim(param0->playerSpritesLayer1[v1]);
    v2[1] = ManagedSprite_GetActiveAnim(param0->playerSpritesLayer2[v1]);

    {
        int v3;

        for (v3 = 0; v3 < 4; v3++) {
            if ((v2[0] == v0[v3][0]) && (v2[1] == v0[v3][1])) {
                return v3;
            }
        }
    }

    GF_ASSERT(FALSE);

    return 0;
}

void WiFiLobbyMinigameManene_TickPlayerRowSprites(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;
    int v1 = 0;

    for (v0 = 0; v0 < param0->playerCount; v0++) {
        if (v0 == param0->localPlayerIndex) {
            continue;
        }

        ManagedSprite_TickTwoFrames(param0->playerSpritesLayer1[v1]);
        ManagedSprite_TickTwoFrames(param0->playerSpritesLayer2[v1]);
        ManagedSprite_TickTwoFrames(param0->playerSpritesLayer3[v1]);

        v1++;
    }
}

void WiFiLobbyMinigameManene_FreePlayerRowSprites(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;
    int v1 = 0;

    for (v0 = 0; v0 < param0->playerCount; v0++) {
        if (v0 == param0->localPlayerIndex) {
            continue;
        }

        Sprite_DeleteAndFreeResources(param0->playerSpritesLayer1[v1]);
        Sprite_DeleteAndFreeResources(param0->playerSpritesLayer2[v1]);
        Sprite_DeleteAndFreeResources(param0->playerSpritesLayer3[v1]);

        v1++;
    }
}

void WiFiLobbyMinigameManene_CreateMessageWindow(WiFiLobbyMinigameManeneGame *param0)
{
    Window_Init(&param0->messageWindow);
    Window_Add(param0->resources->bgConfig, &param0->messageWindow, 7, 2, 19, 28, 4, 14, 256 + (16 * 3));
    Window_FillTilemap(&param0->messageWindow, 0xFF);

    {
        MessageLoader *v0;
        String *v1;

        v0 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0410, HEAP_ID_106);
        v1 = MessageLoader_GetNewString(v0, 0);

        Text_AddPrinterWithParams(&param0->messageWindow, FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_INSTANT, NULL);
        String_Free(v1);
        MessageLoader_Free(v0);
    }

    Window_DrawStandardFrame(&param0->messageWindow, 0, 180, 13);
    Window_CopyToVRAM(&param0->messageWindow);
}

void WiFiLobbyMinigameManene_FreeMessageWindow(WiFiLobbyMinigameManeneGame *param0)
{
    if (Window_IsInUse(&param0->messageWindow) == 1) {
        Window_EraseStandardFrame(&param0->messageWindow, 1);
        Window_ClearAndCopyToVRAM(&param0->messageWindow);
        Window_Remove(&param0->messageWindow);
    }
}

void WiFiLobbyMinigameManene_LoadPlayerPalettes(WiFiLobbyMinigameManeneApp *param0, int param1)
{
    PaletteData *v0 = param0->resources.paletteData;
    static int v1[][4][4 + 1] = {
        {
            { 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0 },
        },
        {
            { 1, 2, 0, 0, 0 },
            { 2, 1, 0, 0, 0 },
            { 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0 },
        },
        {
            { 1, 2, 3, 0, 0 },
            { 2, 1, 3, 0, 0 },
            { 3, 1, 2, 0, 0 },
            { 0, 0, 0, 0, 0 },
        },
        {
            { 1, 2, 3, 4, 0 },
            { 2, 1, 3, 4, 0 },
            { 3, 1, 2, 4, 0 },
            { 4, 1, 2, 3, 0 },
        },
    };

    for (int v2 = 0; v2 < 4; v2++) {
        PaletteData_LoadBufferFromFile(v0, NARC_INDEX_ARC__MANENE, 73, HEAP_ID_106, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES, PLTT_DEST(v2 + 1), PLTT_DEST(v1[param0->game->playerCount - 1][param1][v2 + 1]));
    }
}

static int CenterText(Window *param0, String *param1)
{
    int v0 = Font_CalcStringWidth(FONT_SYSTEM, param1, 0);
    int v1 = (Window_GetWidth(param0) * 8 - v0) / 2;

    return v1;
}

void WiFiLobbyMinigameManene_CreatePlayerNameWindows(WiFiLobbyMinigameManeneApp *param0, WiFiLobbyMinigameManeneGame *param1)
{
    int v0;
    int v1 = 0;
    int v2 = 256;
    Window *v3;
    s16 v4[][3][4] = {
        {
            { 12, 8, 8, 2 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
        },
        {
            { 4 + 1, 8, 8, 2 },
            { 18 + 1, 8, 8, 2 },
            { 0, 0, 0, 0 },
        },
        {
            { 0 + 1, 8, 8, 2 },
            { 11 + 1, 8, 8, 2 },
            { 22 + 1, 8, 8, 2 },
        },
    };
    int v5, v6, v7, v8;
    TrainerInfo *v9;
    BOOL v10;

    switch (param1->playerCount) {
    case 2:
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1->resources->maneneNarc, 79, param1->resources->bgConfig, 7, 0, 0, 0, HEAP_ID_106);
        break;
    case 3:
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1->resources->maneneNarc, 80, param1->resources->bgConfig, 7, 0, 0, 0, HEAP_ID_106);
        break;
    case 4:
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1->resources->maneneNarc, 81, param1->resources->bgConfig, 7, 0, 0, 0, HEAP_ID_106);
        break;
    default:
        GF_ASSERT(FALSE);
    }

    for (v0 = 0; v0 < param1->playerCount; v0++) {
        if (v0 == param1->localPlayerIndex) {
            continue;
        }

        v10 = WiFiLobbyMinigame_IsPlayerReady(&param0->playerContext, v0);
        v3 = &param1->playerNameWindows[v1];
        v9 = WiFiLobbyMinigame_GetTrainerInfo(&param0->playerContext, v0);

        Window_Init(v3);

        v5 = v4[param1->playerCount - 2][v1][0];
        v6 = v4[param1->playerCount - 2][v1][1];
        v7 = v4[param1->playerCount - 2][v1][2];
        v8 = v4[param1->playerCount - 2][v1][3];

        Window_Add(param1->resources->bgConfig, v3, 7, v5, v6, v7, v8, 14, v2);
        v2 += (v7 * v8);
        Window_FillTilemap(v3, 0xFF);

        {
            String *v11;
            int v12;

            v11 = TrainerInfo_NameNewString(v9, 106);
            v12 = CenterText(v3, v11);

            if (v10) {
                Text_AddPrinterWithParamsColorAndSpacing(v3, FONT_SYSTEM, v11, v12, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(5, 6, 15), 0, 0, NULL);
            } else {
                Text_AddPrinterWithParamsColorAndSpacing(v3, FONT_SYSTEM, v11, v12, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), 0, 0, NULL);
            }

            String_Free(v11);
        }

        Window_CopyToVRAM(v3);
        v1++;
    }
}

void WiFiLobbyMinigameManene_FreePlayerNameWindows(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;
    int v1 = 0;
    Window *v2;

    for (v0 = 0; v0 < param0->playerCount; v0++) {
        if (v0 == param0->localPlayerIndex) {
            continue;
        }

        if (Window_IsInUse(&param0->playerNameWindows[v1]) == 1) {
            Window_EraseStandardFrame(&param0->playerNameWindows[v1], 1);
            Window_ClearAndCopyToVRAM(&param0->playerNameWindows[v1]);
            Window_Remove(&param0->playerNameWindows[v1]);
        }

        v1++;
    }

    Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->resources->maneneNarc, 78, param0->resources->bgConfig, 7, 0, 0, 0, HEAP_ID_106);
}

void WiFiLobbyMinigameManene_LoadSpriteResources(WiFiLobbyMinigameManeneApp *param0)
{
    NARC *v0 = param0->resources.maneneNarc;
    NARC *v1 = param0->resources.bucketNarc;
    BgConfig *v2 = param0->resources.bgConfig;
    SpriteSystem *v3 = param0->resources.spriteSystem;
    SpriteManager *v4 = param0->resources.spriteManager;
    PaletteData *v5 = param0->resources.paletteData;
    NARC *v6;
    int v7;
    int v8;
    int v9;
    int v10;
    int v11;
    int v12;

    v6 = v0;
    v7 = 82;
    v8 = 83;
    v9 = 84;
    v10 = 85;
    v11 = 9000;
    v12 = 13;

    SpriteSystem_LoadCharResObjFromOpenNarc(v3, v4, v6, v9, FALSE, NNS_G2D_VRAM_TYPE_2DSUB, v11);
    SpriteSystem_LoadCellResObjFromOpenNarc(v3, v4, v6, v8, FALSE, v11);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v3, v4, v6, v7, FALSE, v11);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v5, PLTTBUF_SUB_OBJ, v3, v4, v6, v10, FALSE, v12, NNS_G2D_VRAM_TYPE_2DSUB, v11);

    v7 = 27;
    v8 = 28;
    v9 = 29;
    v10 = 30;
    v11 = 9003;
    v12 = 1;

    SpriteSystem_LoadCharResObjFromOpenNarc(v3, v4, v6, v9, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, v11);
    SpriteSystem_LoadCellResObjFromOpenNarc(v3, v4, v6, v8, FALSE, v11);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v3, v4, v6, v7, FALSE, v11);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v5, PLTTBUF_MAIN_OBJ, v3, v4, v6, v10, FALSE, v12, NNS_G2D_VRAM_TYPE_2DMAIN, v11);

    v7 = 11;
    v8 = 12;
    v9 = 13;
    v10 = 14;
    v11 = 9004;
    v12 = 1;

    SpriteSystem_LoadCharResObjFromOpenNarc(v3, v4, v6, v9, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, v11);
    SpriteSystem_LoadCellResObjFromOpenNarc(v3, v4, v6, v8, FALSE, v11);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v3, v4, v6, v7, FALSE, v11);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v5, PLTTBUF_MAIN_OBJ, v3, v4, v6, v10, FALSE, v12, NNS_G2D_VRAM_TYPE_2DMAIN, v11);

    v7 = 19;
    v8 = 20;
    v9 = 21;
    v10 = 22;
    v11 = 9005;
    v12 = 1;

    SpriteSystem_LoadCharResObjFromOpenNarc(v3, v4, v6, v9, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, v11);
    SpriteSystem_LoadCellResObjFromOpenNarc(v3, v4, v6, v8, FALSE, v11);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v3, v4, v6, v7, FALSE, v11);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v5, PLTTBUF_MAIN_OBJ, v3, v4, v6, v10, FALSE, v12, NNS_G2D_VRAM_TYPE_2DMAIN, v11);

    v7 = 15;
    v8 = 16;
    v9 = 17;
    v10 = 18;
    v11 = 9006;
    v12 = 1;

    SpriteSystem_LoadCharResObjFromOpenNarc(v3, v4, v6, v9, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, v11);
    SpriteSystem_LoadCellResObjFromOpenNarc(v3, v4, v6, v8, FALSE, v11);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v3, v4, v6, v7, FALSE, v11);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v5, PLTTBUF_MAIN_OBJ, v3, v4, v6, v10, FALSE, v12, NNS_G2D_VRAM_TYPE_2DMAIN, v11);

    v7 = 23;
    v8 = 24;
    v9 = 25;
    v10 = 26;
    v11 = 9002;
    v12 = 3;

    SpriteSystem_LoadCharResObjFromOpenNarc(v3, v4, v6, v9, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, v11);
    SpriteSystem_LoadCellResObjFromOpenNarc(v3, v4, v6, v8, FALSE, v11);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v3, v4, v6, v7, FALSE, v11);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v5, PLTTBUF_MAIN_OBJ, v3, v4, v6, v10, FALSE, v12, NNS_G2D_VRAM_TYPE_2DMAIN, v11);

    {
        NARC *v13 = NARC_ctor(NARC_INDEX_RESOURCE__ENG__WIFI_LOBBY_MINIGAME__WLMNGM_TOOL, HEAP_ID_106);

        v7 = 23;
        v8 = 22;
        v9 = 21;
        v10 = 20;
        v11 = 9007;
        v12 = 2;

        SpriteSystem_LoadCharResObjFromOpenNarc(v3, v4, v13, v9, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, v11);
        SpriteSystem_LoadCellResObjFromOpenNarc(v3, v4, v13, v8, FALSE, v11);
        SpriteSystem_LoadAnimResObjFromOpenNarc(v3, v4, v13, v7, FALSE, v11);
        SpriteSystem_LoadPaletteBufferFromOpenNarc(v5, PLTTBUF_MAIN_OBJ, v3, v4, v13, v10, FALSE, v12, NNS_G2D_VRAM_TYPE_2DMAIN, v11);
        NARC_dtor(v13);
    }
}

void WiFiLobbyMinigameManene_CreatePlayerRowSprites(WiFiLobbyMinigameManeneApp *param0, WiFiLobbyMinigameManeneGame *param1)
{
    SpriteTemplate v0;
    SpriteSystem *v1 = param1->resources->spriteSystem;
    SpriteManager *v2 = param1->resources->spriteManager;
    PaletteData *v3 = param1->resources->paletteData;
    int v4;
    int v5 = 0;

    for (v4 = 0; v4 < param1->playerCount; v4++) {
        param1->playerRowIndex[v4] = 0xFF;
        if (v4 == param1->localPlayerIndex) {
            continue;
        }

        param1->playerRowIndex[v4] = v5;
        InitSpriteTemplate(&v0, sPlayerSpritePositions[param1->playerCount - 1][v5] + 0, 176 + 64, 2, 0, 9000);
        v0.priority = 1;

        param1->playerSpritesLayer1[v5] = SpriteSystem_NewSprite(v1, v2, &v0);
        InitSpriteTemplate(&v0, sPlayerSpritePositions[param1->playerCount - 1][v5] + 0, (176 + 64) + 0, 2, 0, 9000);
        v0.priority = 2;

        param1->playerSpritesLayer2[v5] = SpriteSystem_NewSprite(v1, v2, &v0);
        ManagedSprite_SetExplicitPaletteOffset(param1->playerSpritesLayer2[v5], 0 + WiFiLobbyMinigameManene_GetPlayerIndex(param0, v4));
        InitSpriteTemplate(&v0, sPlayerSpritePositions[param1->playerCount - 1][v5] + 0, (176 + 64) + 0, 2, 0, 9000);
        v0.priority = 3;

        param1->playerSpritesLayer3[v5] = SpriteSystem_NewSprite(v1, v2, &v0);
        ManagedSprite_SetExplicitPaletteOffset(param1->playerSpritesLayer3[v5], 0 + WiFiLobbyMinigameManene_GetPlayerIndex(param0, v4));
        ManagedSprite_SetAnim(param1->playerSpritesLayer3[v5], 5);
        ManagedSprite_TickTwoFrames(param1->playerSpritesLayer1[v5]);
        ManagedSprite_TickTwoFrames(param1->playerSpritesLayer2[v5]);
        ManagedSprite_TickTwoFrames(param1->playerSpritesLayer3[v5]);
        WiFiLobbyMinigameManene_SetPlayerSpriteAnim(param1, v4, 0);

        v5++;
    }
}

ManagedSprite *WiFiLobbyMinigameManene_CreateSparkleSprite(WiFiLobbyMinigameManeneGame *param0, s16 param1, s16 param2)
{
    ManagedSprite *v0;
    SpriteTemplate v1;
    SpriteSystem *v2 = param0->resources->spriteSystem;
    SpriteManager *v3 = param0->resources->spriteManager;
    PaletteData *v4 = param0->resources->paletteData;

    InitSpriteTemplate(&v1, param1, param2, 1, 0, 9003);

    v1.bgPriority = 0;
    v1.priority = 0;
    v0 = SpriteSystem_NewSprite(v2, v3, &v1);

    ManagedSprite_TickTwoFrames(v0);

    return v0;
}

void WiFiLobbyMinigameManene_CreateResultSprites(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;
    ManagedSprite *v1;
    SpriteTemplate v2;
    SpriteSystem *v3 = param0->resources->spriteSystem;
    SpriteManager *v4 = param0->resources->spriteManager;
    PaletteData *v5 = param0->resources->paletteData;

    for (v0 = 0; v0 < 2; v0++) {
        InitSpriteTemplate(&v2, 0, 0, 1, 4, 9002);

        v2.bgPriority = 2;
        v2.priority = 20;
        param0->resultSprites1[v0] = SpriteSystem_NewSprite(v3, v4, &v2);

        ManagedSprite_SetAnim(param0->resultSprites1[v0], 0);
        ManagedSprite_TickFrame(param0->resultSprites1[v0]);
        ManagedSprite_SetExplicitPaletteOffset(param0->resultSprites1[v0], 4);
        ManagedSprite_SetExplicitOamMode(param0->resultSprites1[v0], GX_OAM_MODE_XLU);
        ManagedSprite_SetDrawFlag(param0->resultSprites1[v0], 0);

        InitSpriteTemplate(&v2, 0, 0, 2, 0, 9000);

        v2.bgPriority = 2;
        v2.priority = 20;
        param0->resultSprites2[v0] = SpriteSystem_NewSprite(v3, v4, &v2);

        ManagedSprite_SetAnim(param0->resultSprites2[v0], 6);
        ManagedSprite_TickFrame(param0->resultSprites2[v0]);
        ManagedSprite_SetExplicitPaletteOffset(param0->resultSprites2[v0], 0);
        ManagedSprite_SetExplicitOamMode(param0->resultSprites2[v0], GX_OAM_MODE_XLU);
        ManagedSprite_SetDrawFlag(param0->resultSprites2[v0], 0);
    }
}

void WiFiLobbyMinigameManene_FreeResultSprites(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;

    for (v0 = 0; v0 < 2; v0++) {
        Sprite_DeleteAndFreeResources(param0->resultSprites1[v0]);
        Sprite_DeleteAndFreeResources(param0->resultSprites2[v0]);
    }
}

void WiFiLobbyMinigameManene_CreateBallSprite(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;
    ManagedSprite *v1;
    SpriteTemplate v2;
    SpriteSystem *v3 = param0->resources->spriteSystem;
    SpriteManager *v4 = param0->resources->spriteManager;
    PaletteData *v5 = param0->resources->paletteData;

    InitSpriteTemplate(&v2, 128, 128, 1, 7, 9007);

    v2.bgPriority = 0;
    v2.priority = 0;
    param0->ballSprite = SpriteSystem_NewSprite(v3, v4, &v2);

    ManagedSprite_SetAnim(param0->ballSprite, 1);
    ManagedSprite_SetDrawFlag(param0->ballSprite, 1);
    ManagedSprite_TickFrame(param0->ballSprite);
    ManagedSprite_SetExplicitPaletteOffset(param0->ballSprite, 7);
}

void WiFiLobbyMinigameManene_FreeBallSprite(WiFiLobbyMinigameManeneGame *param0)
{
    Sprite_DeleteAndFreeResources(param0->ballSprite);
}

void WiFiLobbyMinigameManene_LoadBackgroundGraphics(WiFiLobbyMinigameManeneApp *param0)
{
    NARC *v0 = param0->resources.maneneNarc;
    NARC *v1 = param0->resources.bucketNarc;
    BgConfig *v2 = param0->resources.bgConfig;
    SpriteSystem *v3 = param0->resources.spriteSystem;
    SpriteManager *v4 = param0->resources.spriteManager;
    PaletteData *v5 = param0->resources.paletteData;

    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 72, v2, 4, 0, 0, 0, HEAP_ID_106);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 75, v2, 5, 0, 0, 0, HEAP_ID_106);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 74, v2, 4, 0, 0, 0, HEAP_ID_106);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 76, v2, 5, 0, 0, 0, HEAP_ID_106);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 77, v2, 6, 0, 0, 0, HEAP_ID_106);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 78, v2, 7, 0, 0, 0, HEAP_ID_106);
    PaletteData_LoadBufferFromFileStart(v5, NARC_INDEX_ARC__MANENE, 73, HEAP_ID_106, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 5, 0);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 5, v2, 3, 0, 0, 0, HEAP_ID_106);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 8, v2, 1, 0, 0, 0, HEAP_ID_106);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 7, v2, 3, 0, 0, 0, HEAP_ID_106);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 9, v2, 1, 0, 0, 0, HEAP_ID_106);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 10, v2, 2, 0, 0, 0, HEAP_ID_106);
    PaletteData_LoadBufferFromFileStart(v5, NARC_INDEX_ARC__MANENE, 6, HEAP_ID_106, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(0));
    PaletteData_LoadBufferFromFileStart(v5, NARC_INDEX_GRAPHIC__PL_FONT, 7, HEAP_ID_106, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
    PaletteData_LoadBufferFromFileStart(v5, NARC_INDEX_GRAPHIC__PL_WINFRAME, GetStandardWindowPaletteNARCMember(), HEAP_ID_106, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES, PLTT_DEST(13));
    LoadStandardWindowGraphics(v2, BG_LAYER_SUB_3, 180, 13, 0, HEAP_ID_106);
}
