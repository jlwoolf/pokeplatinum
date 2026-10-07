#include "image_clip_app/image_clip_app_02259C58.h"

#include <nitro.h>
#include <string.h>

#include "constants/narc.h"

#include "struct_decls/struct_02012744_decl.h"
#include "struct_defs/struct_020127E8.h"

#include "image_clip_app/funcptr_image_clip_app_02259D78.h"
#include "image_clip_app/image_clip_app_02255094.h"
#include "image_clip_app/struct_image_clip_app_02259C58.h"
#include "image_clip_app/struct_image_clip_app_02259C58_1.h"
#include "image_clip_app/struct_image_clip_app_02259C9C.h"
#include "image_clip_app/struct_image_clip_app_02259D2C.h"
#include "image_clip_app/struct_image_clip_app_0225A0E4.h"
#include "image_clip_app/struct_image_clip_app_0225A154.h"

#include "bg_window.h"
#include "char_transfer.h"
#include "error_handling.h"
#include "font.h"
#include "message.h"
#include "pltt_transfer.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "text.h"
#include "touch_screen.h"
#include "touch_screen_actions.h"
#include "font_oam.h"

static void ImageClipUi_NoOpCallback(ImageClipUi *param0, void *param1);
static void ImageClipUi_AddButton(ImageClipUi *param0, int param1, ImageClipGraphics *param2, int param3, int param4, int param5, int param6);
static void ImageClipUi_AddTextButton(ImageClipUiTextButton *param0, int param1, ImageClipGraphics *param2, const FontOAMManager *param3, const Window *param4, int param5, int param6, int param7, int param8);
static void ImageClipUi_SetHitRect(TouchScreenHitTable *hitTable, int param1, int param2, int param3, int param4, int param5);
static void ImageClipUi_LoadButtonGraphics(ImageClipGraphics *param0);
static void ImageClipUi_UnloadButtonGraphics(ImageClipGraphics *param0);
static Window *ImageClipUi_CreateMessageWindow(ImageClipGraphics *param0, enum NarcID narcID, u32 param2, u32 param3, int param4, int param5);
static void ImageClipUi_DeleteWindow(Window *param0);
static void ImageClipUi_ApplyButtonState(ImageClipUi *param0, int param1);
static void ImageClipUi_PlayPressedSound(ImageClipUi *param0, int param1, int param2, int param3);
static void ImageClipUi_ApplyTextButtonState(ImageClipUiTextButton *param0, int param1);
static void ImageClipUi_MoveButton(ImageClipUi *param0, int param1, int param2);
static void ImageClipUi_MoveTextButton(ImageClipUiTextButton *param0, int param1, int param2);
static void ImageClipUi_OnTouch(u32 param0, enum TouchScreenButtonState param1, void *param2);

void ImageClipUi_Init(ImageClipUi *param0, ImageClipUiTemplate *param1)
{
    GF_ASSERT(param0);
    GF_ASSERT(param1);

    param0->unk_00 = SpriteList_AddAffine(param1->unk_00);
    GF_ASSERT(param0->unk_00);

    param0->unk_04 = param1->unk_0C;
    param0->unk_08 = param1->unk_08;

    if (param1->unk_04) {
        param0->unk_0C = param1->unk_04;
    } else {
        param0->unk_0C = ImageClipUi_NoOpCallback;
    }
}

void ImageClipUi_InitTextButton(ImageClipUiTextButton *param0, ImageClipUiTextButtonTemplate *param1)
{
    UnkStruct_020127E8 v0;

    ImageClipUi_Init(&param0->unk_00, &param1->unk_00);

    v0.unk_00 = param1->unk_14;
    v0.unk_04 = param1->unk_10;
    v0.unk_08 = param1->unk_00.unk_00->list;
    v0.unk_0C = param1->unk_18;
    v0.unk_10 = param0->unk_00.unk_00;
    v0.unk_14 = param1->unk_24;
    v0.unk_18 = param1->unk_1C;
    v0.unk_1C = param1->unk_20;
    v0.unk_20 = 0;
    v0.unk_24 = 0;
    v0.unk_28 = param1->unk_00.unk_00->vramType;
    v0.heapID = param1->unk_00.unk_00->heapID;

    param0->unk_10 = FontOAM_New(&v0);
}

void ImageClipUi_Free(ImageClipUi *param0)
{
    Sprite_Delete(param0->unk_00);
    memset(param0, 0, sizeof(ImageClipUi));
}

void ImageClipUi_FreeTextButton(ImageClipUiTextButton *param0)
{
    ImageClipUi_Free(&param0->unk_00);
    FontOAM_Free(param0->unk_10);
    memset(param0, 0, sizeof(ImageClipUiTextButton));
}

void ImageClipUi_InvokeCallback(ImageClipUi *param0, int param1)
{
    if (param1 == param0->unk_04) {
        param0->unk_0C(param0, param0->unk_08);
    }
}

void ImageClipUi_UpdateSelection(ImageClipUiMenu *param0, int param1, int param2)
{
    int v0;
    ImageClipUi *v1;

    for (v0 = 2; v0 <= 3; v0++) {
        v1 = param0->unk_00 + v0;

        if (v0 != param1) {
            ImageClipUi_SetButtonIdle(v1);
        } else {
            if (param2 == 0) {
                ImageClipUi_SetButtonPressed(v1);

                Sound_PlayEffect(SEQ_SE_DP_PASO_sseq);
            } else if (param2 == 2) {
                ImageClipUi_SetButtonHeld(v1);
            } else {
                ImageClipUi_SetButtonPressed(v1);
            }
        }
    }
}

void ImageClipUi_SetCallback(ImageClipUi *param0, ImageClipUiCallback param1, void *param2, int param3)
{
    GF_ASSERT(param0);

    param0->unk_04 = param3;
    param0->unk_08 = param2;
    param0->unk_0C = param1;
}

static void ImageClipUi_NoOpCallback(ImageClipUi *param0, void *param1)
{
    return;
}

void ImageClipUi_SetButtonHeld(ImageClipUi *param0)
{
    Sprite_SetAnimFrame(param0->unk_00, 2);
}

void ImageClipUi_SetButtonIdle(ImageClipUi *param0)
{
    Sprite_SetAnimFrame(param0->unk_00, 0);
}

void ImageClipUi_SetButtonPressed(ImageClipUi *param0)
{
    Sprite_SetAnimFrame(param0->unk_00, 1);
}

void ImageClipUi_InitMenu(ImageClipUiMenu *param0, ImageClipGraphics *param1)
{
    Window *v0;

    param0->unk_64 = FontOAMManager_New(1, HEAP_ID_13);

    ImageClipUi_LoadButtonGraphics(param1);

    ImageClipUi_AddButton(&param0->unk_00[0], 0, param1, 48, 144, 40, 32);
    ImageClipUi_SetHitRect(param0->unk_6C, 0, 48, 144 + 8, 40, 32 - 8);

    ImageClipUi_AddButton(&param0->unk_00[1], 1, param1, 8, 144, 40, 32);
    ImageClipUi_SetHitRect(param0->unk_6C, 1, 8, 144 + 8, 40, 32 - 8);

    ImageClipUi_AddButton(&param0->unk_00[2], 2, param1, 96, 144, 40, 42);
    ImageClipUi_SetHitRect(param0->unk_6C, 2, 96, 144 + 12, 40, 42 - 8);

    ImageClipUi_AddButton(&param0->unk_00[3], 3, param1, 136, 144, 40, 42);
    ImageClipUi_SetHitRect(param0->unk_6C, 3, 136, 144 + 12, 40, 42 - 8);

    Font_InitManager(FONT_SUBSCREEN, HEAP_ID_14);

    v0 = ImageClipUi_CreateMessageWindow(param1, 26, 385, 0, 72 / 8, 42 / 8);

    ImageClipUi_AddTextButton(&param0->unk_40, 4, param1, param0->unk_64, v0, 184, 144, 72, 42);
    ImageClipUi_SetHitRect(param0->unk_6C, 4, 184, 144 + 12, 72, 42 - 8);

    ImageClipUi_DeleteWindow(v0);
    Font_Free(FONT_SUBSCREEN);

    param0->unk_60 = 1;

    ImageClipUi_UnloadButtonGraphics(param1);
    ImageClipUi_SetButtonHeld(&param0->unk_00[2]);

    param0->unk_68 = TouchScreenActions_RegisterHandler(param0->unk_6C, 5, ImageClipUi_OnTouch, param0, HEAP_ID_13);
}

void ImageClipUi_FreeMenu(ImageClipUiMenu *param0, ImageClipGraphics *param1)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        ImageClipGraphics_RemoveCell(param1, v0);
        ImageClipGraphics_RemoveAnim(param1, v0);
        CharTransfer_ResetTask(v0);
    }

    PlttTransfer_ResetTask(0);
    PlttTransfer_ResetTask(1);

    for (v0 = 0; v0 < 4; v0++) {
        ImageClipUi_Free(&param0->unk_00[v0]);
    }

    CharTransfer_ClearRange(&param0->unk_40.unk_14);
    ImageClipUi_FreeTextButton(&param0->unk_40);
    FontOAMManager_Free(param0->unk_64);
    TouchScreenActions_Free(param0->unk_68);

    param0->unk_68 = NULL;
}

void ImageClipUi_HandleTouch(ImageClipUiMenu *param0)
{
    GF_ASSERT(param0->unk_68);
    TouchScreenActions_HandleAction(param0->unk_68);
}

void ImageClipUi_ResetSelection(ImageClipUiMenu *param0)
{
    ImageClipUi_ApplyButtonState(&param0->unk_40.unk_00, 3);
    ImageClipUi_ApplyTextButtonState(&param0->unk_40, 3);
    ImageClipUi_UpdateSelection(param0, 2, 3);
}

void ImageClipUi_MoveMenu(ImageClipUiMenu *param0, int param1, int param2)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        ImageClipUi_MoveButton(param0->unk_00 + v0, param1, param2);
    }

    ImageClipUi_MoveTextButton(&param0->unk_40, param1, param2);
}

void ImageClipUi_SetElementCallback(ImageClipUiMenu *param0, int param1, ImageClipUiCallback param2, void *param3, int param4)
{
    GF_ASSERT(param0);

    if (param1 < 4) {
        ImageClipUi_SetCallback(
            &param0->unk_00[param1], param2, param3, param4);
    } else {
        ImageClipUi_SetCallback(
            &param0->unk_40.unk_00, param2, param3, param4);
    }
}

static void ImageClipUi_OnTouch(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    ImageClipUiMenu *v0 = param2;

    switch (param0) {
    case 0:
        ImageClipUi_ApplyButtonState(&v0->unk_00[0], param1);
        ImageClipUi_PlayPressedSound(&v0->unk_00[0], 1665, 0, param1);
        ImageClipUi_InvokeCallback(&v0->unk_00[0], param1);
        break;
    case 1:
        ImageClipUi_ApplyButtonState(&v0->unk_00[1], param1);
        ImageClipUi_PlayPressedSound(&v0->unk_00[1], 1665, 0, param1);
        ImageClipUi_InvokeCallback(&v0->unk_00[1], param1);
        break;
    case 2:
    case 3:
        ImageClipUi_UpdateSelection(v0, param0, param1);
        ImageClipUi_InvokeCallback(&v0->unk_00[param0], param1);
        break;
    case 4:
        if (v0->unk_60 == 1) {
            ImageClipUi_ApplyButtonState(&v0->unk_40.unk_00, param1);
            ImageClipUi_ApplyTextButtonState(&v0->unk_40, param1);
            ImageClipUi_PlayPressedSound(&v0->unk_40.unk_00, 1506, 0, param1);
            ImageClipUi_InvokeCallback(&v0->unk_40.unk_00, param1);
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

static void ImageClipUi_AddButton(ImageClipUi *param0, int param1, ImageClipGraphics *param2, int param3, int param4, int param5, int param6)
{
    ImageClipUiTemplate v0;
    SpriteResourcesHeader v1;
    AffineSpriteListTemplate v2;

    SpriteResourcesHeader_Init(&v1, param1, 0, param1, param1, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, param2->unk_48[0], param2->unk_48[1], param2->unk_48[2], param2->unk_48[3], NULL, NULL);

    v2.list = param2->unk_44;
    v2.resourceData = &v1;
    v2.position.x = param3 << 12;
    v2.position.y = param4 << 12;
    v2.position.z = 0;
    v2.priority = 2;
    v2.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v2.heapID = HEAP_ID_14;

    v0.unk_00 = &v2;
    v0.unk_04 = NULL;
    v0.unk_08 = NULL;
    v0.unk_0C = 1;

    ImageClipUi_Init(param0, &v0);
}

static void ImageClipUi_AddTextButton(ImageClipUiTextButton *param0, int param1, ImageClipGraphics *param2, const FontOAMManager *param3, const Window *param4, int param5, int param6, int param7, int param8)
{
    ImageClipUiTextButtonTemplate v0;
    SpriteResourcesHeader v1;
    AffineSpriteListTemplate v2;
    SpriteResource *v3;

    SpriteResourcesHeader_Init(&v1, param1, 0, param1, param1, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, param2->unk_48[0], param2->unk_48[1], param2->unk_48[2], param2->unk_48[3], NULL, NULL);

    v2.list = param2->unk_44;
    v2.resourceData = &v1;
    v2.position.x = param5 << 12;
    v2.position.y = param6 << 12;
    v2.position.z = 0;
    v2.priority = 2;
    v2.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v2.heapID = HEAP_ID_14;

    v0.unk_00.unk_00 = &v2;
    v0.unk_00.unk_04 = NULL;
    v0.unk_00.unk_08 = NULL;
    v0.unk_00.unk_0C = 1;
    v0.unk_14 = param3;
    v0.unk_10 = param4;
    v0.unk_1C = 0;
    v0.unk_20 = 19;

    v3 = SpriteResourceCollection_Find(param2->unk_48[1], 1);
    v0.unk_18 = SpriteTransfer_GetPaletteProxy(v3, NULL);

    GF_ASSERT(CharTransfer_AllocRange(FontOAM_GetWindowSize(param4, NNS_G2D_VRAM_TYPE_2DMAIN, HEAP_ID_13), 1, NNS_G2D_VRAM_TYPE_2DMAIN, &param0->unk_14));

    v0.unk_24 = param0->unk_14.offset;

    ImageClipUi_InitTextButton(param0, &v0);
}

static void ImageClipUi_SetHitRect(TouchScreenHitTable *hitTable, int param1, int param2, int param3, int param4, int param5)
{
    hitTable[param1].rect.top = param3;
    hitTable[param1].rect.left = param2;
    hitTable[param1].rect.bottom = param3 + param5;
    hitTable[param1].rect.right = param2 + param4;
}

static void ImageClipUi_LoadButtonGraphics(ImageClipGraphics *param0)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        ImageClipGraphics_LoadTiles(param0, param0->unk_5C, (v0) * 3 + 105 + 2, 0, NNS_G2D_VRAM_TYPE_2DMAIN, v0);
        ImageClipGraphics_LoadCell(param0, param0->unk_5C, (v0) * 3 + 105 + 1, 0, v0);
        ImageClipGraphics_LoadAnim(param0, param0->unk_5C, (v0) * 3 + 105 + 0, 0, v0);
    }

    ImageClipGraphics_LoadPalette(param0, param0->unk_5C, 104, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 3, 0);
    ImageClipGraphics_LoadPalette(param0, param0->unk_5C, 120, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 2, 1);
}

static void ImageClipUi_UnloadButtonGraphics(ImageClipGraphics *param0)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        ImageClipGraphics_RemoveTiles(param0, v0);
    }

    ImageClipGraphics_RemovePalette(param0, 0);
    ImageClipGraphics_RemovePalette(param0, 1);
}

static void ImageClipUi_ApplyButtonState(ImageClipUi *param0, int param1)
{
    if (param1 == 0) {
        ImageClipUi_SetButtonPressed(param0);
    } else if (param1 == 2) {
        ImageClipUi_SetButtonHeld(param0);
    } else if ((param1 == 1) || (param1 == 3)) {
        ImageClipUi_SetButtonIdle(param0);
    }
}

static void ImageClipUi_ApplyTextButtonState(ImageClipUiTextButton *param0, int param1)
{
    if (param1 == 0) {
        FontOAM_SetXY(param0->unk_10, 0, 15);
        FontOAM_SetExplicitPalette(param0->unk_10, 4);
    } else {
        if (param1 == 1) {
            FontOAM_SetXY(param0->unk_10, 0, 19);
        }

        if (param1 == 3) {
            FontOAM_SetXY(param0->unk_10, 0, 19);
            FontOAM_SetExplicitPalette(param0->unk_10, 3);
        }
    }
}

static void ImageClipUi_PlayPressedSound(ImageClipUi *param0, int param1, int param2, int param3)
{
    if (param3 == param2) {
        Sound_PlayEffect(param1);
    }
}

static Window *ImageClipUi_CreateMessageWindow(ImageClipGraphics *param0, enum NarcID narcID, u32 bankID, u32 param3, int param4, int param5)
{
    MessageLoader *v0;
    String *v1;
    Window *v2;

    v0 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, narcID, bankID, HEAP_ID_13);
    GF_ASSERT(v0);
    v1 = MessageLoader_GetNewString(v0, param3);

    v2 = Window_New(HEAP_ID_14, 1);
    Window_Init(v2);
    Window_AddToTopLeftCorner(param0->unk_40, v2, param4, param5, 0, 0);

    {
        u32 v3 = Font_CalcCenterAlignment(FONT_SUBSCREEN, v1, 0, param4 * 8);
        Text_AddPrinterWithParamsAndColor(v2, FONT_SUBSCREEN, v1, v3, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 3), NULL);
    }

    String_Free(v1);
    MessageLoader_Free(v0);

    return v2;
}

static void ImageClipUi_DeleteWindow(Window *param0)
{
    Windows_Delete(param0, 1);
}

static void ImageClipUi_MoveButton(ImageClipUi *param0, int param1, int param2)
{
    const VecFx32 *v0;
    VecFx32 v1;

    v0 = Sprite_GetPosition(param0->unk_00);
    v1 = *v0;
    v1.x += param1 << FX32_SHIFT;
    v1.y += param2 << FX32_SHIFT;
    Sprite_SetPosition(param0->unk_00, &v1);
}

static void ImageClipUi_MoveTextButton(ImageClipUiTextButton *param0, int param1, int param2)
{
    ImageClipUi_MoveButton(&param0->unk_00, param1, param2);
    FontOAM_UpdatePosition(param0->unk_10);
}
