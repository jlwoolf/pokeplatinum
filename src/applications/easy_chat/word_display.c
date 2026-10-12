#include "applications/easy_chat/word_display.h"

#include <nitro.h>
#include <string.h>

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/word_list_screen.h"
#include "applications/easy_chat/struct_easy_chat_word_list_screen_decl.h"

#include "bg_window.h"
#include "charcode.h"
#include "colored_arrow.h"
#include "easy_chat_word_list.h"
#include "easy_chat_words.h"
#include "font.h"
#include "graphics.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "render_window.h"
#include "sprite.h"
#include "string_gf.h"
#include "string_template.h"
#include "text.h"

typedef struct {
    s16 unk_00;
    s16 unk_02;
} EasyChatWordDisplayWordPos;

typedef struct {
    String *unk_00;
    const u16 *unk_04;
    int unk_08;
} EasyChatWordDisplayReader;

typedef struct EasyChatWordDisplay_t {
    EasyChatWordListScreen *unk_00;
    const EasyChatApp *unk_04;
    const EasyChatWordList *unk_08;
    Window unk_0C;
    Window unk_1C;
    Window unk_2C;
    Sprite *unk_3C;
    Sprite *unk_40;
    Sprite *unk_44;
    MessageLoader *unk_48;
    String *unk_4C;
    ColoredArrow *unk_50;
    EasyChatWordDisplayWordPos unk_54[2];
    u32 unk_5C;
    u32 unk_60;
    EasyChatWordDisplayReader unk_64;
    u16 unk_70[10][16];
} EasyChatWordDisplay;

static void EasyChatWordDisplay_LoadPalette(EasyChatWordDisplay *param0, NARC *param1);
static void EasyChatWordDisplay_LoadTextPalette(EasyChatWordDisplay *param0);
static void EasyChatWordDisplay_InitWordSlots(EasyChatWordDisplay *param0);
static void EasyChatWordDisplay_CreateSprites(EasyChatWordDisplay *param0);
static u32 EasyChatWordDisplay_PrintSentence(EasyChatWordDisplay *param0);
static void EasyChatWordDisplayReader_Init(EasyChatWordDisplayReader *param0, EasyChatWordDisplay *param1);
static void EasyChatWordDisplayReader_Free(EasyChatWordDisplayReader *param0);
static int EasyChatWordDisplayReader_Next(EasyChatWordDisplayReader *param0, String *param1);
static void EasyChatWordDisplayWordPos_ToTopLeft(const EasyChatWordDisplayWordPos *param0, EasyChatWordDisplayWordPos *param1);
static void EasyChatWordDisplayWordPos_ToCursor(const EasyChatWordDisplayWordPos *param0, EasyChatWordDisplayWordPos *param1);
static void EasyChatWordDisplay_FillWordSlot(Window *param0, const EasyChatWordDisplayWordPos *param1);
static void EasyChatWordDisplay_PrintWord(EasyChatWordDisplay *param0, Window *param1, const EasyChatWordDisplayWordPos *param2, u16 param3);
static void EasyChatWordDisplay_SetCursorAnim(EasyChatWordDisplay *param0, BOOL param1);

EasyChatWordDisplay *EasyChatWordDisplay_New(EasyChatWordListScreen *param0, const EasyChatApp *param1, const EasyChatWordList *param2)
{
    EasyChatWordDisplay *v0 = Heap_Alloc(HEAP_ID_35, sizeof(EasyChatWordDisplay));

    v0->unk_00 = param0;
    v0->unk_04 = param1;
    v0->unk_08 = param2;
    v0->unk_3C = NULL;
    v0->unk_40 = NULL;
    v0->unk_44 = NULL;
    v0->unk_4C = String_Init(128, HEAP_ID_35);
    v0->unk_48 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_EASY_CHAT, HEAP_ID_35);
    v0->unk_50 = ColoredArrow_New(HEAP_ID_35);

    return v0;
}

void EasyChatWordDisplay_Free(EasyChatWordDisplay *param0)
{
    if (param0->unk_50) {
        ColoredArrow_Free(param0->unk_50);
    }

    if (param0->unk_3C) {
        Sprite_Delete(param0->unk_3C);
    }

    if (param0->unk_40) {
        Sprite_Delete(param0->unk_40);
    }

    if (param0->unk_44) {
        Sprite_Delete(param0->unk_44);
    }

    if (param0->unk_48) {
        MessageLoader_Free(param0->unk_48);
    }

    if (param0->unk_4C) {
        String_Free(param0->unk_4C);
    }

    Window_Remove(&param0->unk_0C);
    Window_Remove(&param0->unk_1C);
    Window_Remove(&param0->unk_2C);
    Heap_Free(param0);
}

void EasyChatWordDisplay_LoadGraphics(EasyChatWordDisplay *param0, NARC *param1)
{
    BgConfig *v0;
    u32 v1;

    v0 = EasyChatWordListScreen_GetBgConfig(param0->unk_00);

    EasyChatWordDisplay_LoadPalette(param0, param1);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 0, v0, 0, 0, 0, 1, HEAP_ID_35);

    v1 = Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 1, v0, 0, 0, 0, 1, HEAP_ID_35);
    v1 /= 0x20;

    Window_Add(v0, &param0->unk_0C, 0, 3, 1, 27, 4, 0, v1);
    v1 += 108;

    Window_Add(v0, &param0->unk_1C, 0, 2, 21, 27, 2, 11, v1);
    v1 += 54;

    Window_Add(v0, &param0->unk_2C, 0, 23, 15, 8, 4, 11, v1);
    v1 += 32;

    Graphics_LoadTilesToBgLayer(NARC_INDEX_GRAPHIC__PL_WINFRAME, 0, v0, 0, v1, 0, 0, HEAP_ID_35);
    param0->unk_60 = v1;
    v1 += 9;

    Graphics_LoadPalette(NARC_INDEX_GRAPHIC__PL_WINFRAME, 24, 0, 14 * 0x20, 0x20, HEAP_ID_35);
    LoadMessageBoxGraphics(v0, BG_LAYER_MAIN_0, v1, 15, EasyChat_GetFrame(param0->unk_04), HEAP_ID_35);
    Window_DrawMessageBox(&param0->unk_1C, v1, 15);
    Window_PutToTilemap(&param0->unk_0C);
    Window_PutToTilemap(&param0->unk_1C);

    EasyChatWordDisplay_InitWordSlots(param0);
    EasyChatWordDisplay_Refresh(param0);
    EasyChatWordDisplay_SetInstructionText(param0, 0);
    EasyChatWordDisplay_CreateSprites(param0);

    Bg_CopyTilemapBufferToVRAM(v0, 0);
}

static void EasyChatWordDisplay_LoadPalette(EasyChatWordDisplay *param0, NARC *param1)
{
    NNSG2dPaletteData *v0;
    void *v1;

    Graphics_LoadPaletteFromOpenNARC(param1, 6, 0, 0, 14 * 0x20, HEAP_ID_35);

    v1 = Graphics_GetPlttDataFromOpenNARC(param1, 6, &v0, HEAP_ID_35);

    MI_CpuCopy16(v0->pRawData, param0->unk_70, sizeof(param0->unk_70));
    DC_FlushRange(param0->unk_70, sizeof(param0->unk_70));

    Heap_Free(v1);
}

static void EasyChatWordDisplay_LoadTextPalette(EasyChatWordDisplay *param0)
{
    if (EasyChat_GetType(param0->unk_04) == EASY_CHAT_TYPE_SENTENCE) {
        int v0 = 1 + EasyChat_GetSentenceType(param0->unk_04);
        GX_LoadBGPltt(param0->unk_70[v0], 0 * 0x20, 0x20);
    } else {
        GX_LoadBGPltt(param0->unk_70[0], 0 * 0x20, 0x20);
    }
}

static void EasyChatWordDisplay_InitWordSlots(EasyChatWordDisplay *param0)
{
    switch (EasyChat_GetType(param0->unk_04)) {
    case EASY_CHAT_TYPE_ONE_WORD:
        param0->unk_54[0].unk_00 = 104;
        param0->unk_54[0].unk_02 = 16;
        param0->unk_5C = 1;
        break;
    case EASY_CHAT_TYPE_TWO_WORDS:
        param0->unk_54[0].unk_00 = 48;
        param0->unk_54[0].unk_02 = 16;
        param0->unk_54[1].unk_00 = 160;
        param0->unk_54[1].unk_02 = 16;
        param0->unk_5C = 2;
        break;
    case EASY_CHAT_TYPE_SENTENCE:
        param0->unk_5C = 0;
        break;
    }
}

static void EasyChatWordDisplay_CreateSprites(EasyChatWordDisplay *param0)
{
    SpriteResourcesHeader v0;
    EasyChatWordDisplayWordPos v1;

    if (param0->unk_5C) {
        EasyChatWordDisplayWordPos_ToCursor(&param0->unk_54[0], &v1);
    } else {
        v1.unk_00 = 128;
        v1.unk_02 = 24;
    }

    EasyChatWordListScreen_SetupSpriteResources(param0->unk_00, &v0, 0, 0);
    param0->unk_3C = EasyChatWordListScreen_AddSprite(param0->unk_00, &v0, v1.unk_00, v1.unk_02, 0, NNS_G2D_VRAM_TYPE_2DMAIN);

    EasyChatWordDisplay_SetCursorAnim(param0, 1);
    param0->unk_40 = EasyChatWordListScreen_AddSprite(param0->unk_00, &v0, 6, 24, 1, NNS_G2D_VRAM_TYPE_2DMAIN);

    Sprite_SetAnim(param0->unk_40, 13);
    param0->unk_44 = EasyChatWordListScreen_AddSprite(param0->unk_00, &v0, 250, 24, 1, NNS_G2D_VRAM_TYPE_2DMAIN);

    Sprite_SetAnim(param0->unk_44, 12);

    if (EasyChat_GetType(param0->unk_04) != EASY_CHAT_TYPE_SENTENCE) {
        Sprite_SetDrawFlag(param0->unk_44, FALSE);
        Sprite_SetDrawFlag(param0->unk_40, FALSE);
    }
}

void EasyChatWordDisplay_Refresh(EasyChatWordDisplay *param0)
{
    EasyChatWordDisplay_LoadTextPalette(param0);
    Window_FillTilemap(&param0->unk_0C, 13);

    switch (EasyChat_GetType(param0->unk_04)) {
    case EASY_CHAT_TYPE_ONE_WORD:
        EasyChatWordDisplay_FillWordSlot(&param0->unk_0C, &param0->unk_54[0]);
        EasyChatWordDisplay_PrintWord(param0, &param0->unk_0C, &(param0->unk_54[0]), EasyChat_GetWordAtSlot(param0->unk_04, 0));
        break;
    case EASY_CHAT_TYPE_TWO_WORDS:
        EasyChatWordDisplay_FillWordSlot(&param0->unk_0C, &param0->unk_54[0]);
        EasyChatWordDisplay_FillWordSlot(&param0->unk_0C, &param0->unk_54[1]);
        EasyChatWordDisplay_PrintWord(param0, &param0->unk_0C, &(param0->unk_54[0]), EasyChat_GetWordAtSlot(param0->unk_04, 0));
        EasyChatWordDisplay_PrintWord(param0, &param0->unk_0C, &(param0->unk_54[1]), EasyChat_GetWordAtSlot(param0->unk_04, 1));
        break;
    case EASY_CHAT_TYPE_SENTENCE:
        param0->unk_5C = EasyChatWordDisplay_PrintSentence(param0);
        break;
    }

    Window_LoadTiles(&param0->unk_0C);
}

static u32 EasyChatWordDisplay_PrintSentence(EasyChatWordDisplay *param0)
{
    String *v0 = EasyChat_GetTemplateString(param0->unk_04, 35);
    int v1, v2, v3;
    BOOL v4;
    u16 v5;

    v1 = v2 = v3 = 0;
    v4 = 1;

    EasyChatWordDisplayReader_Init(&param0->unk_64, param0);

    while (v4) {
        switch (EasyChatWordDisplayReader_Next(&(param0->unk_64), v0)) {
        case 0:
            Text_AddPrinterWithParamsAndColor(&param0->unk_0C, FONT_MESSAGE, v0, v1, v2, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(3, 4, 13), NULL);
            v1 += Font_CalcStringWidth(FONT_MESSAGE, v0, 0);
            break;
        case 1:
            v1 += 2;
            param0->unk_54[v3].unk_00 = v1 + (96 / 2);
            param0->unk_54[v3].unk_02 = v2 + (16 / 2);
            EasyChatWordDisplay_FillWordSlot(&param0->unk_0C, &(param0->unk_54[v3]));
            v5 = EasyChat_GetWordAtSlot(param0->unk_04, v3);

            if (v5 != 0xffff) {
                EasyChatWordDisplay_PrintWord(param0, &param0->unk_0C, &(param0->unk_54[v3]), v5);
            }

            v3++;
            v1 += (2 + 96);
            break;
        case 2:
            v2 += 16;
            v1 = 0;
            break;
        case 3:
            v4 = 0;
            break;
        }
    }

    EasyChatWordDisplayReader_Free(&param0->unk_64);
    String_Free(v0);

    return v3;
}

static void EasyChatWordDisplayReader_Init(EasyChatWordDisplayReader *param0, EasyChatWordDisplay *param1)
{
    param0->unk_00 = EasyChat_GetTemplateString(param1->unk_04, 35);
    param0->unk_04 = String_GetData(param0->unk_00);

    if (*(param0->unk_04) == 0xfffe) {
        param0->unk_08 = 1;
    } else {
        param0->unk_08 = 0;
    }
}

static void EasyChatWordDisplayReader_Free(EasyChatWordDisplayReader *param0)
{
    String_Free(param0->unk_00);
}

static int EasyChatWordDisplayReader_Next(EasyChatWordDisplayReader *param0, String *param1)
{
    const u16 *v0 = param0->unk_04;
    int v1;

    switch (param0->unk_08) {
    case 0:
        while (param0->unk_08 == 0) {
            switch (*(param0->unk_04)) {
            case 0xe000:
                param0->unk_08 = 2;
                break;
            case 0xffff:
                param0->unk_08 = 3;
                break;
            case 0xfffe:
                param0->unk_08 = 1;
                break;
            default:
                param0->unk_04++;
                break;
            }
        }

        String_CopyNumChars(param1, v0, (param0->unk_04 - v0) + 1);
        return 0;
    case 1:
        param0->unk_04 = CharCode_SkipFormatArg(param0->unk_04);
        v1 = 1;
        break;
    case 2:
        param0->unk_04++;
        v1 = 2;
        break;
    case 3:
    default:
        return 3;
    }

    switch (*(param0->unk_04)) {
    case 0xe000:
        param0->unk_08 = 2;
        break;
    case 0xffff:
        param0->unk_08 = 3;
        break;
    case 0xfffe:
        param0->unk_08 = 1;
        break;
    default:
        param0->unk_08 = 0;
        break;
    }

    return v1;
}

static void EasyChatWordDisplayWordPos_ToTopLeft(const EasyChatWordDisplayWordPos *param0, EasyChatWordDisplayWordPos *param1)
{
    param1->unk_00 = param0->unk_00 - (96 / 2);
    param1->unk_02 = param0->unk_02 - (16 / 2);
}

static void EasyChatWordDisplayWordPos_ToCursor(const EasyChatWordDisplayWordPos *param0, EasyChatWordDisplayWordPos *param1)
{
    param1->unk_00 = param0->unk_00 + 3 * 8;
    param1->unk_02 = param0->unk_02 + 1 * 8;
}

static void EasyChatWordDisplay_FillWordSlot(Window *param0, const EasyChatWordDisplayWordPos *param1)
{
    EasyChatWordDisplayWordPos v0;

    EasyChatWordDisplayWordPos_ToTopLeft(param1, &v0);
    Window_FillRectWithColor(param0, 14, v0.unk_00, v0.unk_02, 96, 16);
}

static void EasyChatWordDisplay_PrintWord(EasyChatWordDisplay *param0, Window *param1, const EasyChatWordDisplayWordPos *param2, u16 param3)
{
    if (param3 != 0xffff) {
        EasyChatWordDisplayWordPos v0;
        u32 v1;

        EasyChatWordDisplayWordPos_ToTopLeft(param2, &v0);
        EasyChatWord_ToString(param3, param0->unk_4C);

        v1 = (v0.unk_00 + (96 / 2)) - (Font_CalcStringWidth(FONT_MESSAGE, param0->unk_4C, 0) / 2);

        Text_AddPrinterWithParamsAndColor(param1, FONT_MESSAGE, param0->unk_4C, v0.unk_00, v0.unk_02, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(5, 6, 14), NULL);
    }
}

u32 EasyChatWordDisplay_GetWordSlotCount(const EasyChatWordDisplay *param0)
{
    return param0->unk_5C;
}

void EasyChatWordDisplay_SetInstructionText(EasyChatWordDisplay *param0, u32 param1)
{
    Window_FillTilemap(&param0->unk_1C, 9);

    switch (param1) {
    case 0:

    {
        StringTemplate *v0 = StringTemplate_New(2, 60, HEAP_ID_SYSTEM);
        String *v1 = String_Init(300, HEAP_ID_SYSTEM);

        StringTemplate_SetBagPocketName(v0, 0, 0);
        MessageLoader_GetString(param0->unk_48, EasyChat_GetInstructionBankEntry(param0->unk_04), param0->unk_4C);
        StringTemplate_Format(v0, v1, param0->unk_4C);
        Text_AddPrinterWithParamsAndColor(&param0->unk_1C, FONT_MESSAGE, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 9), NULL);

        String_Free(v1);
        StringTemplate_Free(v0);
    } break;
    case 2:
        MessageLoader_GetString(param0->unk_48, 6, param0->unk_4C);
        Text_AddPrinterWithParamsAndColor(&param0->unk_1C, FONT_MESSAGE, param0->unk_4C, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 9), NULL);
        break;
    case 1:
        MessageLoader_GetString(param0->unk_48, 7, param0->unk_4C);
        Text_AddPrinterWithParamsAndColor(&param0->unk_1C, FONT_MESSAGE, param0->unk_4C, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 9), NULL);
        break;
    case 3:
        MessageLoader_GetString(param0->unk_48, 8, param0->unk_4C);
        Text_AddPrinterWithParamsAndColor(&param0->unk_1C, FONT_MESSAGE, param0->unk_4C, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 9), NULL);
        break;
    }

    Window_LoadTiles(&param0->unk_1C);
}

void EasyChatWordDisplay_SetCursorIdle(EasyChatWordDisplay *param0)
{
    EasyChatWordDisplay_SetCursorAnim(param0, 0);
}

void EasyChatWordDisplay_SetCursorActive(EasyChatWordDisplay *param0)
{
    EasyChatWordDisplay_SetCursorAnim(param0, 1);
}

void EasyChatWordDisplay_SetCursorVisible(EasyChatWordDisplay *param0, BOOL param1)
{
    Sprite_SetDrawFlag(param0->unk_3C, param1);
    EasyChatWordDisplay_SetCursorAnim(param0, 1);
}

void EasyChatWordDisplay_HideSelectionArrows(EasyChatWordDisplay *param0)
{
    if (EasyChat_GetType(param0->unk_04) == EASY_CHAT_TYPE_SENTENCE) {
        Sprite_SetDrawFlag(param0->unk_40, FALSE);
        Sprite_SetDrawFlag(param0->unk_44, FALSE);
    }
}

void EasyChatWordDisplay_ShowSelectionArrows(EasyChatWordDisplay *param0)
{
    if (EasyChat_GetType(param0->unk_04) == EASY_CHAT_TYPE_SENTENCE) {
        Sprite_SetDrawFlag(param0->unk_40, TRUE);
        Sprite_SetDrawFlag(param0->unk_44, TRUE);

        Sprite_SetAnim(param0->unk_40, 13);
        Sprite_SetAnim(param0->unk_44, 12);
    }
}

void EasyChatWordDisplay_SetCursorPosition(EasyChatWordDisplay *param0, int param1)
{
    VecFx32 v0;

    if (param0->unk_5C) {
        EasyChatWordDisplayWordPos v1;

        EasyChatWordDisplayWordPos_ToCursor(&param0->unk_54[param1], &v1);
        v0.x = v1.unk_00 * FX32_ONE;
        v0.y = v1.unk_02 * FX32_ONE;
        v0.z = 0;
    } else {
        v0.x = 128 * FX32_ONE;
        v0.y = 24 * FX32_ONE;
        v0.z = 0;

        Sprite_SetPosition(param0->unk_3C, &v0);
    }

    Sprite_SetPosition(param0->unk_3C, &v0);
    EasyChatWordDisplay_SetCursorAnim(param0, 1);
}

static void EasyChatWordDisplay_SetCursorAnim(EasyChatWordDisplay *param0, BOOL param1)
{
    if (param0->unk_5C != 0) {
        if (param1) {
            Sprite_SetAnim(param0->unk_3C, 0);
        } else {
            Sprite_SetAnim(param0->unk_3C, 1);
        }
    } else {
        if (param1) {
            Sprite_SetAnim(param0->unk_3C, 14);
        } else {
            Sprite_SetAnim(param0->unk_3C, 15);
        }
    }
}

void EasyChatWordDisplay_DrawPageIndicator(EasyChatWordDisplay *param0, int param1)
{
    Window_FillTilemap(&param0->unk_2C, 9);

    MessageLoader_GetString(param0->unk_48, 9, param0->unk_4C);
    Text_AddPrinterWithParamsAndColor(&param0->unk_2C, FONT_SYSTEM, param0->unk_4C, 14, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 9), NULL);

    MessageLoader_GetString(param0->unk_48, 10, param0->unk_4C);
    Text_AddPrinterWithParamsAndColor(&param0->unk_2C, FONT_SYSTEM, param0->unk_4C, 14, 0 + 16, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 9), NULL);

    Window_DrawStandardFrame(&param0->unk_2C, 0, param0->unk_60, 14);
    ColoredArrow_Print(param0->unk_50, &param0->unk_2C, 0, 0 + (param1 * 16));

    Window_CopyToVRAM(&param0->unk_2C);
}

void EasyChatWordDisplay_MovePageIndicatorArrow(EasyChatWordDisplay *param0, int param1)
{
    Window_FillRectWithColor(&param0->unk_2C, 9, 0, 0, 14, 4 * 8);
    ColoredArrow_Print(param0->unk_50, &param0->unk_2C, 0, 0 + (param1 * 16));
}

void EasyChatWordDisplay_ErasePageIndicator(EasyChatWordDisplay *param0)
{
    Window_EraseStandardFrame(&param0->unk_2C, 0);
    Window_ClearAndCopyToVRAM(&param0->unk_2C);
}
