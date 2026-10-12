#include "image_clip_app/image_clip_app_02259C58.h"

#include <nitro.h>
#include <string.h>

#include "constants/narc.h"

#include "struct_decls/struct_02012744_decl.h"
#include "struct_defs/struct_font_oam_template.h"

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

    param0->sprite = SpriteList_AddAffine(param1->spriteTemplate);
    GF_ASSERT(param0->sprite);

    param0->buttonId = param1->buttonId;
    param0->callbackParam = param1->callbackParam;

    if (param1->callback) {
        param0->callback = param1->callback;
    } else {
        param0->callback = ImageClipUi_NoOpCallback;
    }
}

void ImageClipUi_InitTextButton(ImageClipUiTextButton *param0, ImageClipUiTextButtonTemplate *param1)
{
    FontOAMTemplate v0;

    ImageClipUi_Init(&param0->ui, &param1->uiTemplate);

    v0.fontOAMManager = param1->fontManager;
    v0.window = param1->window;
    v0.spriteList = param1->uiTemplate.spriteTemplate->list;
    v0.paletteProxy = param1->paletteProxy;
    v0.parentSprite = param0->ui.sprite;
    v0.charOffset = param1->charOffset;
    v0.x = param1->x;
    v0.y = param1->y;
    v0.resourcePriority = 0;
    v0.spritePriority = 0;
    v0.vramType = param1->uiTemplate.spriteTemplate->vramType;
    v0.heapID = param1->uiTemplate.spriteTemplate->heapID;

    param0->fontOAM = FontOAM_New(&v0);
}

void ImageClipUi_Free(ImageClipUi *param0)
{
    Sprite_Delete(param0->sprite);
    memset(param0, 0, sizeof(ImageClipUi));
}

void ImageClipUi_FreeTextButton(ImageClipUiTextButton *param0)
{
    ImageClipUi_Free(&param0->ui);
    FontOAM_Free(param0->fontOAM);
    memset(param0, 0, sizeof(ImageClipUiTextButton));
}

void ImageClipUi_InvokeCallback(ImageClipUi *param0, int param1)
{
    if (param1 == param0->buttonId) {
        param0->callback(param0, param0->callbackParam);
    }
}

void ImageClipUi_UpdateSelection(ImageClipUiMenu *param0, int param1, int param2)
{
    int v0;
    ImageClipUi *v1;

    for (v0 = 2; v0 <= 3; v0++) {
        v1 = param0->buttons + v0;

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

    param0->buttonId = param3;
    param0->callbackParam = param2;
    param0->callback = param1;
}

static void ImageClipUi_NoOpCallback(ImageClipUi *param0, void *param1)
{
    return;
}

void ImageClipUi_SetButtonHeld(ImageClipUi *param0)
{
    Sprite_SetAnimFrame(param0->sprite, 2);
}

void ImageClipUi_SetButtonIdle(ImageClipUi *param0)
{
    Sprite_SetAnimFrame(param0->sprite, 0);
}

void ImageClipUi_SetButtonPressed(ImageClipUi *param0)
{
    Sprite_SetAnimFrame(param0->sprite, 1);
}

void ImageClipUi_InitMenu(ImageClipUiMenu *param0, ImageClipGraphics *param1)
{
    Window *v0;

    param0->fontManager = FontOAMManager_New(1, HEAP_ID_13);

    ImageClipUi_LoadButtonGraphics(param1);

    ImageClipUi_AddButton(&param0->buttons[0], 0, param1, 48, 144, 40, 32);
    ImageClipUi_SetHitRect(param0->hitTables, 0, 48, 144 + 8, 40, 32 - 8);

    ImageClipUi_AddButton(&param0->buttons[1], 1, param1, 8, 144, 40, 32);
    ImageClipUi_SetHitRect(param0->hitTables, 1, 8, 144 + 8, 40, 32 - 8);

    ImageClipUi_AddButton(&param0->buttons[2], 2, param1, 96, 144, 40, 42);
    ImageClipUi_SetHitRect(param0->hitTables, 2, 96, 144 + 12, 40, 42 - 8);

    ImageClipUi_AddButton(&param0->buttons[3], 3, param1, 136, 144, 40, 42);
    ImageClipUi_SetHitRect(param0->hitTables, 3, 136, 144 + 12, 40, 42 - 8);

    Font_InitManager(FONT_SUBSCREEN, HEAP_ID_14);

    v0 = ImageClipUi_CreateMessageWindow(param1, 26, 385, 0, 72 / 8, 42 / 8);

    ImageClipUi_AddTextButton(&param0->textButton, 4, param1, param0->fontManager, v0, 184, 144, 72, 42);
    ImageClipUi_SetHitRect(param0->hitTables, 4, 184, 144 + 12, 72, 42 - 8);

    ImageClipUi_DeleteWindow(v0);
    Font_Free(FONT_SUBSCREEN);

    param0->textEnabled = 1;

    ImageClipUi_UnloadButtonGraphics(param1);
    ImageClipUi_SetButtonHeld(&param0->buttons[2]);

    param0->touchActions = TouchScreenActions_RegisterHandler(param0->hitTables, 5, ImageClipUi_OnTouch, param0, HEAP_ID_13);
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
        ImageClipUi_Free(&param0->buttons[v0]);
    }

    CharTransfer_ClearRange(&param0->textButton.charAllocation);
    ImageClipUi_FreeTextButton(&param0->textButton);
    FontOAMManager_Free(param0->fontManager);
    TouchScreenActions_Free(param0->touchActions);

    param0->touchActions = NULL;
}

void ImageClipUi_HandleTouch(ImageClipUiMenu *param0)
{
    GF_ASSERT(param0->touchActions);
    TouchScreenActions_HandleAction(param0->touchActions);
}

void ImageClipUi_ResetSelection(ImageClipUiMenu *param0)
{
    ImageClipUi_ApplyButtonState(&param0->textButton.ui, 3);
    ImageClipUi_ApplyTextButtonState(&param0->textButton, 3);
    ImageClipUi_UpdateSelection(param0, 2, 3);
}

void ImageClipUi_MoveMenu(ImageClipUiMenu *param0, int param1, int param2)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        ImageClipUi_MoveButton(param0->buttons + v0, param1, param2);
    }

    ImageClipUi_MoveTextButton(&param0->textButton, param1, param2);
}

void ImageClipUi_SetElementCallback(ImageClipUiMenu *param0, int param1, ImageClipUiCallback param2, void *param3, int param4)
{
    GF_ASSERT(param0);

    if (param1 < 4) {
        ImageClipUi_SetCallback(
            &param0->buttons[param1], param2, param3, param4);
    } else {
        ImageClipUi_SetCallback(
            &param0->textButton.ui, param2, param3, param4);
    }
}

static void ImageClipUi_OnTouch(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    ImageClipUiMenu *v0 = param2;

    switch (param0) {
    case 0:
        ImageClipUi_ApplyButtonState(&v0->buttons[0], param1);
        ImageClipUi_PlayPressedSound(&v0->buttons[0], 1665, 0, param1);
        ImageClipUi_InvokeCallback(&v0->buttons[0], param1);
        break;
    case 1:
        ImageClipUi_ApplyButtonState(&v0->buttons[1], param1);
        ImageClipUi_PlayPressedSound(&v0->buttons[1], 1665, 0, param1);
        ImageClipUi_InvokeCallback(&v0->buttons[1], param1);
        break;
    case 2:
    case 3:
        ImageClipUi_UpdateSelection(v0, param0, param1);
        ImageClipUi_InvokeCallback(&v0->buttons[param0], param1);
        break;
    case 4:
        if (v0->textEnabled == 1) {
            ImageClipUi_ApplyButtonState(&v0->textButton.ui, param1);
            ImageClipUi_ApplyTextButtonState(&v0->textButton, param1);
            ImageClipUi_PlayPressedSound(&v0->textButton.ui, 1506, 0, param1);
            ImageClipUi_InvokeCallback(&v0->textButton.ui, param1);
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

    SpriteResourcesHeader_Init(&v1, param1, 0, param1, param1, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, param2->spriteResourceCollections[0], param2->spriteResourceCollections[1], param2->spriteResourceCollections[2], param2->spriteResourceCollections[3], NULL, NULL);

    v2.list = param2->spriteList;
    v2.resourceData = &v1;
    v2.position.x = param3 << 12;
    v2.position.y = param4 << 12;
    v2.position.z = 0;
    v2.priority = 2;
    v2.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v2.heapID = HEAP_ID_14;

    v0.spriteTemplate = &v2;
    v0.callback = NULL;
    v0.callbackParam = NULL;
    v0.buttonId = 1;

    ImageClipUi_Init(param0, &v0);
}

static void ImageClipUi_AddTextButton(ImageClipUiTextButton *param0, int param1, ImageClipGraphics *param2, const FontOAMManager *param3, const Window *param4, int param5, int param6, int param7, int param8)
{
    ImageClipUiTextButtonTemplate v0;
    SpriteResourcesHeader v1;
    AffineSpriteListTemplate v2;
    SpriteResource *v3;

    SpriteResourcesHeader_Init(&v1, param1, 0, param1, param1, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, param2->spriteResourceCollections[0], param2->spriteResourceCollections[1], param2->spriteResourceCollections[2], param2->spriteResourceCollections[3], NULL, NULL);

    v2.list = param2->spriteList;
    v2.resourceData = &v1;
    v2.position.x = param5 << 12;
    v2.position.y = param6 << 12;
    v2.position.z = 0;
    v2.priority = 2;
    v2.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v2.heapID = HEAP_ID_14;

    v0.uiTemplate.spriteTemplate = &v2;
    v0.uiTemplate.callback = NULL;
    v0.uiTemplate.callbackParam = NULL;
    v0.uiTemplate.buttonId = 1;
    v0.fontManager = param3;
    v0.window = param4;
    v0.x = 0;
    v0.y = 19;

    v3 = SpriteResourceCollection_Find(param2->spriteResourceCollections[1], 1);
    v0.paletteProxy = SpriteTransfer_GetPaletteProxy(v3, NULL);

    GF_ASSERT(CharTransfer_AllocRange(FontOAM_GetWindowSize(param4, NNS_G2D_VRAM_TYPE_2DMAIN, HEAP_ID_13), 1, NNS_G2D_VRAM_TYPE_2DMAIN, &param0->charAllocation));

    v0.charOffset = param0->charAllocation.offset;

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
        ImageClipGraphics_LoadTiles(param0, param0->narc, (v0) * 3 + 105 + 2, 0, NNS_G2D_VRAM_TYPE_2DMAIN, v0);
        ImageClipGraphics_LoadCell(param0, param0->narc, (v0) * 3 + 105 + 1, 0, v0);
        ImageClipGraphics_LoadAnim(param0, param0->narc, (v0) * 3 + 105 + 0, 0, v0);
    }

    ImageClipGraphics_LoadPalette(param0, param0->narc, 104, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 3, 0);
    ImageClipGraphics_LoadPalette(param0, param0->narc, 120, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 2, 1);
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
        FontOAM_SetXY(param0->fontOAM, 0, 15);
        FontOAM_SetExplicitPalette(param0->fontOAM, 4);
    } else {
        if (param1 == 1) {
            FontOAM_SetXY(param0->fontOAM, 0, 19);
        }

        if (param1 == 3) {
            FontOAM_SetXY(param0->fontOAM, 0, 19);
            FontOAM_SetExplicitPalette(param0->fontOAM, 3);
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
    Window_AddToTopLeftCorner(param0->bgConfig, v2, param4, param5, 0, 0);

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

    v0 = Sprite_GetPosition(param0->sprite);
    v1 = *v0;
    v1.x += param1 << FX32_SHIFT;
    v1.y += param2 << FX32_SHIFT;
    Sprite_SetPosition(param0->sprite, &v1);
}

static void ImageClipUi_MoveTextButton(ImageClipUiTextButton *param0, int param1, int param2)
{
    ImageClipUi_MoveButton(&param0->ui, param1, param2);
    FontOAM_UpdatePosition(param0->fontOAM);
}
