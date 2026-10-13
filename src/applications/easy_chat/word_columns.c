#include "applications/easy_chat/word_columns.h"

#include <nitro.h>
#include <string.h>

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/word_list_screen.h"
#include "applications/easy_chat/struct_easy_chat_word_list_screen_decl.h"

#include "bg_window.h"
#include "easy_chat_word_list.h"
#include "font.h"
#include "graphics.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "sprite.h"
#include "string_gf.h"
#include "text.h"

typedef struct EasyChatWordColumns_t {
    EasyChatWordListScreen *wordListScreen;
    const EasyChatApp *easyChatApp;
    const EasyChatWordList *wordList;
    Sprite *cursorSprite;
} EasyChatWordColumns;

static void EasyChatWordColumns_PrintLabel(BgConfig *param0, const WindowTemplate *param1, u32 param2);
static void EasyChatWordColumns_CreateSprite(EasyChatWordColumns *param0);

EasyChatWordColumns *EasyChatWordColumns_New(EasyChatWordListScreen *param0, const EasyChatApp *param1, const EasyChatWordList *param2)
{
    EasyChatWordColumns *v0 = Heap_Alloc(HEAP_ID_35, sizeof(EasyChatWordColumns));

    v0->wordListScreen = param0;
    v0->easyChatApp = param1;
    v0->wordList = param2;
    v0->cursorSprite = NULL;

    return v0;
}

void EasyChatWordColumns_Free(EasyChatWordColumns *param0)
{
    if (param0->cursorSprite) {
        Sprite_Delete(param0->cursorSprite);
    }

    Heap_Free(param0);
}

void EasyChatWordColumns_LoadGraphics(EasyChatWordColumns *param0, NARC *param1)
{
    static const WindowTemplate v0 = {
        3, 3, 6, 10, 2, 13, 64
    };
    static const WindowTemplate v1 = {
        3, 19, 6, 10, 2, 13, 84
    };
    BgConfig *v2 = EasyChatWordListScreen_GetBgConfig(param0->wordListScreen);

    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 4, v2, 3, 0, 0, 1, HEAP_ID_35);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 5, v2, 3, 0, 0, 1, HEAP_ID_35);

    EasyChatWordColumns_PrintLabel(v2, &v0, 0);
    EasyChatWordColumns_PrintLabel(v2, &v1, 1);
    EasyChatWordColumns_CreateSprite(param0);

    Bg_CopyTilemapBufferToVRAM(v2, 3);
}

static void EasyChatWordColumns_PrintLabel(BgConfig *param0, const WindowTemplate *param1, u32 param2)
{
    Window v0;
    String *v1;
    u32 v2;

    Window_AddFromTemplate(param0, &v0, param1);
    Window_PutToTilemap(&v0);
    Window_FillTilemap(&v0, 14);

    v1 = MessageBank_GetNewStringFromNARC(26, 438, param2, 35);
    v2 = ((param1->width * 8) - Font_CalcStringWidth(FONT_SYSTEM, v1, 0)) / 2;

    Text_AddPrinterWithParamsAndColor(&v0, FONT_SYSTEM, v1, v2, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 14), NULL);
    Window_LoadTiles(&v0);
    String_Free(v1);
    Window_Remove(&v0);
}

static void EasyChatWordColumns_CreateSprite(EasyChatWordColumns *param0)
{
    SpriteResourcesHeader v0;

    EasyChatWordListScreen_SetupSpriteResources(param0->wordListScreen, &v0, 0, 3);
    param0->cursorSprite = EasyChatWordListScreen_AddSprite(param0->wordListScreen, &v0, 64, 56, 5, NNS_G2D_VRAM_TYPE_2DMAIN);

    Sprite_SetAnim(param0->cursorSprite, 2);
    Sprite_SetDrawFlag(param0->cursorSprite, FALSE);
}

void EasyChatWordColumns_SetEdgeAnim(EasyChatWordColumns *param0)
{
    Sprite_SetAnim(param0->cursorSprite, 3);
}

void EasyChatWordColumns_SetDefaultAnim(EasyChatWordColumns *param0)
{
    Sprite_SetAnim(param0->cursorSprite, 2);
}

void EasyChatWordColumns_SetVisible(EasyChatWordColumns *param0, BOOL param1)
{
    Sprite_SetDrawFlag(param0->cursorSprite, param1);
}

BOOL EasyChatWordColumns_IsVisible(EasyChatWordColumns *param0)
{
    return Sprite_GetDrawFlag(param0->cursorSprite);
}

void EasyChatWordColumns_SetActiveColumn(EasyChatWordColumns *param0, int param1)
{
    VecFx32 v0;

    v0.z = 0;

    switch (param1) {
    case 0:
    default:
        v0.x = 64 * FX32_ONE;
        v0.y = 56 * FX32_ONE;
        break;
    case 1:
        v0.x = 192 * FX32_ONE;
        v0.y = 56 * FX32_ONE;
        break;
    }

    Sprite_SetPosition(param0->cursorSprite, &v0);
    Sprite_SetAnim(param0->cursorSprite, 2);
}

void EasyChatWordColumns_SetRightColumnOffset(EasyChatWordColumns *param0)
{
    Bg_SetOffset(EasyChatWordListScreen_GetBgConfig(param0->wordListScreen), 3, 3, 64);
}

void EasyChatWordColumns_SetLeftColumnOffset(EasyChatWordColumns *param0)
{
    Bg_SetOffset(EasyChatWordListScreen_GetBgConfig(param0->wordListScreen), 3, 3, 0);
}
