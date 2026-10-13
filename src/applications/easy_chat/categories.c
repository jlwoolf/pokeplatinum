#include "applications/easy_chat/categories.h"

#include <nitro.h>

#include "applications/easy_chat/abc_mode.h"
#include "applications/easy_chat/defs.h"
#include "applications/easy_chat/main.h"
#include "applications/easy_chat/word_list_screen.h"
#include "applications/easy_chat/animations.h"
#include "applications/easy_chat/struct_easy_chat_word_list_screen_decl.h"
#include "applications/easy_chat/struct_easy_chat_scroll_animation.h"
#include "applications/easy_chat/struct_easy_chat_blend_animation.h"

#include "bg_window.h"
#include "easy_chat_word_list.h"
#include "enums.h"
#include "font.h"
#include "graphics.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "sprite.h"
#include "string_gf.h"
#include "sys_task_manager.h"
#include "text.h"

#include "res/text/bank/easy_chat_groups.h"

#define GROUP_MODE_BG_X_OFFSET -4
#define ABC_MODE_BG_X_OFFSET   252

#define GROUP_WINDOW_WIDTH  9
#define GROUP_WINDOW_HEIGHT 2

#define ABC_MODE_WINDOW_WIDTH  25
#define ABC_MODE_WINDOW_HEIGHT 8

#define CANCEL_WINDOW_WIDTH  8
#define CANCEL_WINDOW_HEIGHT 2

static u32 EasyChatCategories_PrintGroups(EasyChatCategoriesContext *ctx, BgConfig *bgConfig, u32 baseTile);
static u32 EasyChatCategories_PrintABCModeSelection(EasyChatCategoriesContext *ctx, BgConfig *bgConfig, u32 baseTile);
static u32 EasyChatCategories_PrintCancelText(EasyChatCategoriesContext *ctx, BgConfig *bgConfig, u32 baseTile);
static void EasyChatCategories_CreateCursorSprite(EasyChatCategoriesContext *ctx);

EasyChatCategoriesContext *EasyChatCategoriesContext_New(EasyChatWordListScreen *param0, const EasyChatApp *easyChatApp, const EasyChatWordList *param2)
{
    EasyChatCategoriesContext *ctx = Heap_Alloc(HEAP_ID_35, sizeof(EasyChatCategoriesContext));

    ctx->wordListScreen = param0;
    ctx->easyChatApp = easyChatApp;
    ctx->wordList = param2;
    ctx->bgConfig = EasyChatWordListScreen_GetBgConfig(param0);
    ctx->unk_10 = 0;
    ctx->dummy = 0;
    ctx->cursorSprite = NULL;

    return ctx;
}

void EasyChatCategoriesContext_Free(EasyChatCategoriesContext *ctx)
{
    if (ctx->cursorSprite) {
        Sprite_Delete(ctx->cursorSprite);
    }

    Heap_Free(ctx);
}

void EasyChatCategories_DrawInterface(EasyChatCategoriesContext *ctx, NARC *narc)
{
    BgConfig *bgConfig = EasyChatWordListScreen_GetBgConfig(ctx->wordListScreen);

    Graphics_LoadTilemapToBgLayerFromOpenNARC(narc, 2, bgConfig, BG_LAYER_MAIN_1, 0, 0, TRUE, HEAP_ID_35);

    u32 baseTile = Graphics_LoadTilesToBgLayerFromOpenNARC(narc, 3, bgConfig, BG_LAYER_MAIN_1, 0, 0, TRUE, HEAP_ID_35);
    baseTile /= TILE_SIZE_4BPP;
    baseTile = EasyChatCategories_PrintGroups(ctx, bgConfig, baseTile);
    baseTile = EasyChatCategories_PrintABCModeSelection(ctx, bgConfig, baseTile);

    EasyChatCategories_PrintCancelText(ctx, bgConfig, baseTile);
    Bg_SetOffset(bgConfig, BG_LAYER_MAIN_1, BG_OFFSET_UPDATE_SET_X, GROUP_MODE_BG_X_OFFSET);
    Bg_SetOffset(bgConfig, BG_LAYER_MAIN_1, BG_OFFSET_UPDATE_SET_Y, 2);
    EasyChatCategories_CreateCursorSprite(ctx);

    G2_SetBlendBrightness(GX_BLEND_PLANEMASK_BG1, -10);
    G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_ALL, TRUE);
    G2_SetWndOutsidePlane(GX_WND_PLANEMASK_ALL ^ GX_WND_PLANEMASK_BG1, TRUE);
    G2_SetWnd0Position(0, 0, 255, 160);
    GX_SetVisibleWnd(GX_WNDMASK_W0);

    Bg_CopyTilemapBufferToVRAM(bgConfig, BG_LAYER_MAIN_1);
}

static u32 EasyChatCategories_PrintGroups(EasyChatCategoriesContext *ctx, BgConfig *bgConfig, u32 baseTile)
{
    int tilemapLeft, tilemapTop;

    MessageLoader *loader = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_EASY_CHAT_GROUPS, HEAP_ID_35);

    tilemapLeft = 1;
    tilemapTop = 9;

    for (int i = 0; i < EASY_CHAT_GROUP_COUNT; i++) {
        if (i != 0 && i % 3 == 0) {
            tilemapLeft = 1;
            tilemapTop += GROUP_WINDOW_HEIGHT + 1;
        }

        String *string;
        TextColor color;

        if (EasyChatWordList_GetGroupWordCount(ctx->wordList, i)) {
            string = MessageLoader_GetNewString(loader, i);
            color = TEXT_COLOR(1, 2, 15);
        } else {
            string = MessageLoader_GetNewString(loader, EasyChatGroups_Text_QuestionMarks);
            color = TEXT_COLOR(3, 4, 15);
        }

        GF_ASSERT(baseTile < 1024 - GROUP_WINDOW_WIDTH * GROUP_WINDOW_HEIGHT);

        Window window;

        Window_Add(bgConfig, &window, BG_LAYER_MAIN_1, tilemapLeft, tilemapTop, GROUP_WINDOW_WIDTH, GROUP_WINDOW_HEIGHT, 11, baseTile);
        Window_FillTilemap(&window, 15);

        u32 xOffset = (GROUP_WINDOW_WIDTH * TILE_WIDTH_PIXELS - Font_CalcStringWidth(FONT_SYSTEM, string, 0)) / 2;

        Text_AddPrinterWithParamsAndColor(&window, FONT_SYSTEM, string, xOffset, 0, TEXT_SPEED_NO_TRANSFER, color, NULL);
        Window_PutToTilemap(&window);
        Window_LoadTiles(&window);
        String_Free(string);
        Window_Remove(&window);

        baseTile += GROUP_WINDOW_WIDTH * GROUP_WINDOW_HEIGHT;
        tilemapLeft += GROUP_WINDOW_WIDTH + 1;
    }

    MessageLoader_Free(loader);

    return baseTile;
}

static u32 EasyChatCategories_PrintABCModeSelection(EasyChatCategoriesContext *ctx, BgConfig *bgConfig, u32 baseTile)
{
    GF_ASSERT(baseTile < 1024 - ABC_MODE_WINDOW_WIDTH * ABC_MODE_WINDOW_HEIGHT);

    Window window;
    Window_Add(bgConfig, &window, BG_LAYER_MAIN_1, 34, 10, ABC_MODE_WINDOW_WIDTH, ABC_MODE_WINDOW_HEIGHT, 11, baseTile);
    baseTile += ABC_MODE_WINDOW_WIDTH * ABC_MODE_WINDOW_HEIGHT;

    String *string = String_Init(4, HEAP_ID_35);

    Window_FillTilemap(&window, 15);

    u32 count = EasyChatABCMode_GetCharCount();

    for (u32 i = 0; i < count; i++) {
        u32 x, y;
        EasyChatABCMode_GetCharCode(i, string);
        EasyChatABCMode_GetCharPos(i, &x, &y);

        TextColor color;
        if (EasyChatWordList_GetLetterWordCount(ctx->wordList, i)) {
            color = TEXT_COLOR(1, 2, 15);
        } else {
            color = TEXT_COLOR(3, 4, 15);
        }

        Text_AddPrinterWithParamsAndColor(&window, FONT_SYSTEM, string, x + 3, y, TEXT_SPEED_NO_TRANSFER, color, NULL);
    }

    Window_LoadTiles(&window);
    Window_PutToTilemap(&window);

    String_Free(string);
    Window_Remove(&window);

    return baseTile;
}

static u32 EasyChatCategories_PrintCancelText(EasyChatCategoriesContext *ctx, BgConfig *bgConfig, u32 baseTile)
{
    static const struct {
        u16 tilemapLeft;
        u16 tilemapTop;
    } windowPositions[] = {
        { .tilemapLeft = 12, .tilemapTop = 21 },
        { .tilemapLeft = 44, .tilemapTop = 21 },
    };

    MessageLoader *loader = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_EASY_CHAT_GROUPS, HEAP_ID_35);
    String *string = MessageLoader_GetNewString(loader, EasyChatGroups_Text_Cancel);
    int xOffset = (8 * TILE_WIDTH_PIXELS - Font_CalcStringWidth(FONT_SYSTEM, string, 0)) / 2;

    for (int i = 0; i < NELEMS(windowPositions); i++) {
        GF_ASSERT(baseTile < 1024 - CANCEL_WINDOW_WIDTH * CANCEL_WINDOW_HEIGHT);

        Window window;

        Window_Add(bgConfig, &window, BG_LAYER_MAIN_1, windowPositions[i].tilemapLeft, windowPositions[i].tilemapTop, CANCEL_WINDOW_WIDTH, CANCEL_WINDOW_HEIGHT, 11, baseTile);
        Window_FillTilemap(&window, 15);
        Text_AddPrinterWithParamsAndColor(&window, FONT_SYSTEM, string, xOffset, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
        Window_PutToTilemap(&window);
        Window_LoadTiles(&window);
        Window_Remove(&window);

        baseTile += CANCEL_WINDOW_WIDTH * CANCEL_WINDOW_HEIGHT;
    }

    String_Free(string);
    MessageLoader_Free(loader);

    return baseTile;
}

static void EasyChatCategories_CreateCursorSprite(EasyChatCategoriesContext *ctx)
{
    SpriteResourcesHeader v0;

    EasyChatWordListScreen_SetupSpriteResources(ctx->wordListScreen, &v0, 0, 1);
    ctx->cursorSprite = EasyChatWordListScreen_AddSprite(ctx->wordListScreen, &v0, 48, 54, 2, NNS_G2D_VRAM_TYPE_2DMAIN);
    Sprite_SetAnim(ctx->cursorSprite, 4);
    Sprite_SetDrawFlag(ctx->cursorSprite, FALSE);
}

void EasyChatCategories_SetCursorVisible(EasyChatCategoriesContext *ctx, BOOL param1)
{
    Sprite_SetDrawFlag(ctx->cursorSprite, param1);

    if (param1) {
        if (EasyChat_GetMode(ctx->easyChatApp) == GROUP_MODE) {
            Sprite_SetAnim(ctx->cursorSprite, 4);
        } else {
            Sprite_SetAnim(ctx->cursorSprite, 6);
        }
    }
}

void EasyChatCategories_DrawCursor(EasyChatCategoriesContext *ctx, u32 selectedIndex)
{
    u32 mode = EasyChat_GetMode(ctx->easyChatApp);

    VecFx32 position;
    position.z = 0;

    u32 animID;

    if (selectedIndex == EASY_CHAT_CANCEL) {
        position.x = 132;
        position.y = 150;
        animID = 16;
    } else {
        if (mode == GROUP_MODE) {
            position.x = 48 + 80 * (selectedIndex % 3);
            position.y = 54 + 24 * (selectedIndex / 3);
            animID = 4;
        } else {
            u32 x, y;
            EasyChatABCMode_GetCharPos(selectedIndex, &x, &y);

            position.x = 26 + x;
            position.y = 62 + y;
            animID = 6;
        }
    }

    position.x *= FX32_ONE;
    position.y *= FX32_ONE;

    Sprite_SetPosition(ctx->cursorSprite, &position);
    Sprite_SetAnim(ctx->cursorSprite, animID);
}

void EasyChatCategories_StartShowAnimation(EasyChatCategoriesContext *ctx)
{
    ctx->animStage = 0;
    EasyChatBlendAnimation_StartBrightness(&(ctx->blendAnimation), GX_BLEND_PLANEMASK_BG1, -10, 0, 16);
}

BOOL EasyChatCategories_UpdateShowAnimation(EasyChatCategoriesContext *ctx)
{
    switch (ctx->animStage) {
    case 0:
        if (EasyChatBlendAnimation_UpdateBrightness(&ctx->blendAnimation)) {
            EasyChatScrollAnimation_Start(&(ctx->scrollAnimation), ctx->bgConfig, 1, 1, 24, 6);
            ctx->animStage++;
        }
        break;
    case 1:
        return EasyChatScrollAnimation_Update(&(ctx->scrollAnimation));
    }

    return 0;
}

void EasyChatCategories_StartSlideOutAnimation(EasyChatCategoriesContext *ctx)
{
    ctx->animStage = 0;
    EasyChatScrollAnimation_Start(&(ctx->scrollAnimation), ctx->bgConfig, 1, 1, -24, 6);
}

BOOL EasyChatCategories_UpdateSlideOutAnimation(EasyChatCategoriesContext *ctx)
{
    switch (ctx->animStage) {
    case 0:
        if (EasyChatScrollAnimation_Update(&(ctx->scrollAnimation))) {
            EasyChatBlendAnimation_StartBrightness(&(ctx->blendAnimation), GX_BLEND_PLANEMASK_BG1, 0, -10, 16);
            ctx->animStage++;
        }
        break;
    case 1:
        return EasyChatBlendAnimation_UpdateBrightness(&ctx->blendAnimation);
    }

    return 0;
}

void EasyChatCategories_ResetVerticalOffset(EasyChatCategoriesContext *ctx)
{
    Bg_SetOffset(ctx->bgConfig, BG_LAYER_MAIN_1, BG_OFFSET_UPDATE_SET_Y, 2);
}

void EasyChatCategories_StartBrightnessRestore(EasyChatCategoriesContext *ctx)
{
    EasyChatBlendAnimation_StartBrightness(&ctx->blendAnimation, GX_BLEND_PLANEMASK_BG1, 0, -10, 16);
}

BOOL EasyChatCategories_UpdateBrightnessRestore(EasyChatCategoriesContext *ctx)
{
    return EasyChatBlendAnimation_UpdateBrightness(&ctx->blendAnimation);
}

void EasyChatCategories_StartSlideInAnimation(EasyChatCategoriesContext *ctx)
{
    EasyChatBlendAnimation_Start(&ctx->blendAnimation, GX_BLEND_PLANEMASK_BG1, GX_BLEND_ALL, 124, 0, (6 * 2));
}

BOOL EasyChatCategories_UpdateSlideInAnimation(EasyChatCategoriesContext *ctx)
{
    if (EasyChatBlendAnimation_Update(&ctx->blendAnimation)) {
        Bg_ToggleLayer(BG_LAYER_MAIN_1, FALSE);
        return TRUE;
    }

    return FALSE;
}

void EasyChatCategories_StartSlideOutAndDim(EasyChatCategoriesContext *ctx)
{
    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, GX_BLEND_ALL, 0, 16);
    Bg_ToggleLayer(BG_LAYER_MAIN_1, TRUE);
    EasyChatBlendAnimation_Start(&ctx->blendAnimation, GX_BLEND_PLANEMASK_BG1, GX_BLEND_ALL, 0, 124, (6 * 2));
}

BOOL EasyChatCategories_UpdateSlideOutAndDim(EasyChatCategoriesContext *ctx)
{
    return EasyChatBlendAnimation_Update(&ctx->blendAnimation);
}

void EasyChatCategories_SetModeOffset(EasyChatCategoriesContext *ctx)
{
    int val;

    if (EasyChat_GetMode(ctx->easyChatApp) == GROUP_MODE) {
        val = GROUP_MODE_BG_X_OFFSET;
    } else {
        val = ABC_MODE_BG_X_OFFSET;
    }

    Bg_SetOffset(ctx->bgConfig, BG_LAYER_MAIN_1, BG_OFFSET_UPDATE_SET_X, val);
}

void EasyChatCategories_StartModeTransition(EasyChatCategoriesContext *ctx)
{
    int v0;

    if (EasyChat_GetMode(ctx->easyChatApp) == GROUP_MODE) {
        v0 = GROUP_MODE_BG_X_OFFSET - ABC_MODE_BG_X_OFFSET;
    } else {
        v0 = ABC_MODE_BG_X_OFFSET - GROUP_MODE_BG_X_OFFSET;
    }

    EasyChatScrollAnimation_Start(&ctx->scrollAnimation, ctx->bgConfig, 1, 0, v0, 16);
}

BOOL EasyChatCategories_UpdateModeTransition(EasyChatCategoriesContext *ctx)
{
    return EasyChatScrollAnimation_Update(&ctx->scrollAnimation);
}
