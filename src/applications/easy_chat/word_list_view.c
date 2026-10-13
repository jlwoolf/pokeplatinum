#include "applications/easy_chat/word_list_view.h"

#include <nitro.h>
#include <string.h>

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/word_list_screen.h"
#include "applications/easy_chat/animations.h"
#include "applications/easy_chat/struct_easy_chat_word_list_screen_decl.h"
#include "applications/easy_chat/struct_easy_chat_scroll_animation.h"
#include "applications/easy_chat/struct_easy_chat_blend_animation.h"

#include "bg_window.h"
#include "easy_chat_word_list.h"
#include "enums.h"
#include "heap.h"
#include "sprite.h"
#include "string_gf.h"
#include "text.h"

typedef struct EasyChatWordListView_t {
    EasyChatWordListScreen *wordListScreen;
    const EasyChatApp *easyChatApp;
    const EasyChatWordList *wordList;
    BgConfig *bgConfig;
    Window listWindow;
    Window entryWindow;
    Sprite *cursorSprite;
    Sprite *upArrowSprite;
    Sprite *downArrowSprite;
    String *string;
    EasyChatBlendAnimation blendAnimation;
    EasyChatScrollAnimation scrollAnimation;
    u32 animState;
    GXWndPlane windowPlane;
    int wndMask;
    int scrollOffset;
    int scrollRow;
} EasyChatWordListView;

static void EasyChatWordListView_CreateSprites(EasyChatWordListView *param0);
static void EasyChatWordListView_ClearScrollArea(EasyChatWordListView *param0, int param1);
static void EasyChatWordListView_ResetScroll(EasyChatWordListView *param0);
static void EasyChatWordListView_PrintEntry(EasyChatWordListView *param0, u32 param1, u32 param2);

EasyChatWordListView *EasyChatWordListView_New(EasyChatWordListScreen *param0, const EasyChatApp *param1, const EasyChatWordList *param2)
{
    EasyChatWordListView *v0 = Heap_Alloc(HEAP_ID_35, sizeof(EasyChatWordListView));

    v0->wordListScreen = param0;
    v0->easyChatApp = param1;
    v0->wordList = param2;
    v0->bgConfig = EasyChatWordListScreen_GetBgConfig(param0);
    v0->string = String_Init(32, HEAP_ID_35);

    Window_Add(v0->bgConfig, &v0->listWindow, 2, 4, 0, 26, 32, 12, 1);
    Window_Add(v0->bgConfig, &v0->entryWindow, 2, 0, 0, 12, 4, 12, 1);

    v0->cursorSprite = NULL;
    v0->upArrowSprite = NULL;
    v0->downArrowSprite = NULL;

    return v0;
}

void EasyChatWordListView_Free(EasyChatWordListView *param0)
{
    if (param0->cursorSprite) {
        Sprite_Delete(param0->cursorSprite);
    }

    if (param0->upArrowSprite) {
        Sprite_Delete(param0->upArrowSprite);
    }

    if (param0->downArrowSprite) {
        Sprite_Delete(param0->downArrowSprite);
    }

    if (param0->string) {
        String_Free(param0->string);
    }

    Window_Remove(&(param0->entryWindow));
    Window_Remove(&(param0->listWindow));
    Heap_Free(param0);
}

void EasyChatWordListView_LoadGraphics(EasyChatWordListView *param0)
{
    BgConfig *v0;
    u32 v1;

    v0 = EasyChatWordListScreen_GetBgConfig(param0->wordListScreen);

    Bg_ClearTilesRange(BG_LAYER_MAIN_2, 0x20, 0 * 0x20, HEAP_ID_35);
    Bg_FillTilemapRect(v0, 2, 0, 0, 0, 32, 32, 12);

    Window_FillTilemap(&param0->listWindow, 0);
    Window_PutToTilemap(&param0->listWindow);
    Window_LoadTiles(&param0->listWindow);
    Bg_CopyTilemapBufferToVRAM(v0, 2);

    EasyChatWordListView_CreateSprites(param0);

    Bg_ToggleLayer(BG_LAYER_MAIN_2, 0);
}

static void EasyChatWordListView_CreateSprites(EasyChatWordListView *param0)
{
    SpriteResourcesHeader v0;

    EasyChatWordListScreen_SetupSpriteResources(param0->wordListScreen, &v0, 0, 2);
    param0->cursorSprite = EasyChatWordListScreen_AddSprite(param0->wordListScreen, &v0, 72, 56, 3, NNS_G2D_VRAM_TYPE_2DMAIN);

    Sprite_SetAnim(param0->cursorSprite, 8);
    Sprite_SetDrawFlag(param0->cursorSprite, FALSE);

    param0->upArrowSprite = EasyChatWordListScreen_AddSprite(param0->wordListScreen, &v0, 240, 64, 4, NNS_G2D_VRAM_TYPE_2DMAIN);
    Sprite_SetAnim(param0->upArrowSprite, 11);
    Sprite_SetDrawFlag(param0->upArrowSprite, FALSE);

    param0->downArrowSprite = EasyChatWordListScreen_AddSprite(param0->wordListScreen, &v0, 240, 144, 4, NNS_G2D_VRAM_TYPE_2DMAIN);
    Sprite_SetAnim(param0->downArrowSprite, 10);
    Sprite_SetDrawFlag(param0->downArrowSprite, FALSE);
}

void EasyChatWordListView_FillPage(EasyChatWordListView *param0)
{
    u32 v0, v1, v2;

    Window_FillTilemap(&param0->listWindow, 0);
    EasyChatWordListView_ResetScroll(param0);

    v0 = EasyChat_GetCategoryWordCount(param0->easyChatApp);

    if (v0 > 10) {
        v0 = 10;
    }

    v1 = param0->scrollOffset;

    for (v2 = 0; v2 < v0; v2++) {
        EasyChatWordListView_PrintEntry(param0, v2, v1);

        if (v2 & 1) {
            v1 += 24;
        }
    }

    Window_LoadTiles(&param0->listWindow);
}

void EasyChatWordListView_Show(EasyChatWordListView *param0)
{
    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_ALL, 0, 16);
    Bg_ToggleLayer(BG_LAYER_MAIN_2, 1);
    G2_SetWnd1InsidePlane(GX_WND_PLANEMASK_ALL, 1);

    param0->windowPlane = G2_GetWndOutsidePlane();
    param0->wndMask = GX_GetVisibleWnd();

    G2_SetWndOutsidePlane(GX_WND_PLANEMASK_ALL ^ GX_WND_PLANEMASK_BG2, 1);
    G2_SetWnd1Position(0, 46, 255, 176);
    GX_SetVisibleWnd(GX_WNDMASK_W1);

    param0->animState = 0;
    EasyChatBlendAnimation_Start(&param0->blendAnimation, GX_BLEND_PLANEMASK_BG2, GX_BLEND_ALL, 0, 124, (6 * 2));
}

BOOL EasyChatWordListView_IsShown(EasyChatWordListView *param0)
{
    switch (param0->animState) {
    case 0:
        if (EasyChatBlendAnimation_Update(&param0->blendAnimation)) {
            return 1;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

void EasyChatWordListView_Hide(EasyChatWordListView *param0)
{
    param0->animState = 0;
    EasyChatBlendAnimation_Start(&param0->blendAnimation, GX_BLEND_PLANEMASK_BG2, GX_BLEND_ALL, 124, 0, (6 * 2));
}

BOOL EasyChatWordListView_IsHidden(EasyChatWordListView *param0)
{
    switch (param0->animState) {
    case 0:
        if (EasyChatBlendAnimation_Update(&param0->blendAnimation)) {
            Bg_ToggleLayer(BG_LAYER_MAIN_2, 0);
            G2_SetWndOutsidePlane(param0->windowPlane.planeMask, param0->windowPlane.effect);
            GX_SetVisibleWnd(param0->wndMask);
            return 1;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

void EasyChatWordListView_SetArrowsVisible(EasyChatWordListView *param0, BOOL param1)
{
    Sprite_SetDrawFlag(param0->cursorSprite, param1);

    if (param1) {
        Sprite_SetDrawFlag(param0->upArrowSprite, EasyChat_IsWordSelectRowBelowFirst(param0->easyChatApp));
        Sprite_SetDrawFlag(param0->downArrowSprite, EasyChat_IsWordSelectRowAboveLast(param0->easyChatApp));
    } else {
        Sprite_SetDrawFlag(param0->upArrowSprite, FALSE);
        Sprite_SetDrawFlag(param0->downArrowSprite, FALSE);
    }
}

void EasyChatWordListView_SetCursorPosition(EasyChatWordListView *param0, u32 param1)
{
    VecFx32 v0;
    u32 v1 = param1 & 1;
    u32 v2 = param1 / 2;

    v0.x = (72 + 112 * v1) * FX32_ONE;
    v0.y = (56 + 24 * v2) * FX32_ONE;
    v0.z = 0;

    Sprite_SetPosition(param0->cursorSprite, &v0);
    Sprite_SetAnim(param0->cursorSprite, 8);
}

void EasyChatWordListView_Scroll(EasyChatWordListView *param0, int param1)
{
    int v0, v1, v2, v3, v4, v5, v6;

    EasyChatWordListView_ClearScrollArea(param0, param1);

    v1 = param0->scrollRow + (param1 * 2);
    v0 = (param0->scrollOffset + (param1 * 24)) & 255;

    if (param1 < 0) {
        v3 = v0;
        v4 = v1;
        v5 = -(param1 * 2);
        v6 = -(4 * param1);
    } else {
        v3 = (param0->scrollOffset + 120) & 255;
        v4 = param0->scrollRow + 10;
        v5 = param1 * 2;

        if ((v5 + v4) > EasyChat_GetCategoryWordCount(param0->easyChatApp)) {
            v5--;
        }

        v6 = 4 * param1;
    }

    for (v2 = 0; v2 < v5; v2++) {
        EasyChatWordListView_PrintEntry(param0, v4 + v2, v3);

        if (v2 & 1) {
            v3 = (v3 + 24) & 255;
        }
    }

    param0->scrollOffset = v0;
    param0->scrollRow = v1;

    Window_LoadTiles(&param0->listWindow);
    EasyChatScrollAnimation_Start(&(param0->scrollAnimation), param0->bgConfig, 2, 1, param1 * 24, v6);
}

BOOL EasyChatWordListView_IsScrollDone(EasyChatWordListView *param0)
{
    if (EasyChatScrollAnimation_Update(&param0->scrollAnimation)) {
        Sprite_SetDrawFlag(param0->upArrowSprite, EasyChat_IsWordSelectRowBelowFirst(param0->easyChatApp));
        Sprite_SetDrawFlag(param0->downArrowSprite, EasyChat_IsWordSelectRowAboveLast(param0->easyChatApp));
        return 1;
    }

    return 0;
}

static void EasyChatWordListView_ClearScrollArea(EasyChatWordListView *param0, int param1)
{
    int v0, v1;

    if (param1 > 0) {
        v0 = (param0->scrollOffset + 120) & 0xff;
        v1 = (v0 + (param1 * 24)) & 0xff;
    } else {
        v1 = param0->scrollOffset;
        v0 = (v1 + (param1 * 24)) & 0xff;
    }

    if (v0 < v1) {
        Window_FillRectWithColor(&param0->listWindow, 0, 0, v0, 26 * 8, (v1 - v0));
    } else {
        Window_FillRectWithColor(&param0->listWindow, 0, 0, v0, 26 * 8, 256 - v0);
        Window_FillRectWithColor(&param0->listWindow, 0, 0, 0, 26 * 8, v1);
    }
}

static void EasyChatWordListView_ResetScroll(EasyChatWordListView *param0)
{
    param0->scrollOffset = 48;
    param0->scrollRow = 0;

    Bg_SetOffset(param0->bgConfig, BG_LAYER_MAIN_2, 3, 0);
}

static void EasyChatWordListView_PrintEntry(EasyChatWordListView *param0, u32 param1, u32 param2)
{
    EasyChat_GetWordString(param0->easyChatApp, param1, param0->string);

    if (param2 <= 240) {
        Text_AddPrinterWithParamsAndColor(&param0->listWindow, FONT_SYSTEM, param0->string, 0 + (param1 & 1) * 112, param2, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    } else {
        u32 v0 = 256 - param2;

        Window_FillTilemap(&param0->entryWindow, 0);
        Text_AddPrinterWithParamsAndColor(&param0->entryWindow, FONT_SYSTEM, param0->string, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        Window_BlitBitmapRect(&param0->listWindow, param0->entryWindow.pixels, 0, 0, 12 * 8, 2 * 8, 0 + (param1 & 1) * 112, param2, 12 * 8, v0);
        Window_BlitBitmapRect(&param0->listWindow, param0->entryWindow.pixels, 0, v0, 12 * 8, 2 * 8, 0 + (param1 & 1) * 112, 0, 12 * 8, (2 * 8) - v0);
    }
}
