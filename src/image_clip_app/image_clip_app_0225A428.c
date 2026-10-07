#include "image_clip_app/image_clip_app_0225A428.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_02095C60.h"

#include "image_clip_app/image_clip_app_022597BC.h"
#include "image_clip_app/struct_image_clip_app_02256BAC.h"
#include "image_clip_app/struct_image_clip_app_022597BC.h"
#include "image_clip_app/struct_image_clip_app_022599A0.h"
#include "image_clip_app/struct_image_clip_app_0225A428.h"
#include "image_clip_app/struct_image_clip_app_0225A914.h"
#include "image_clip_app/struct_image_clip_app_0225AB54.h"
#include "image_clip_app/struct_image_clip_app_0225AD68.h"
#include "image_clip_app/struct_image_clip_app_0225AE9C.h"

#include "bg_window.h"
#include "font.h"
#include "game_options.h"
#include "message.h"
#include "narc.h"
#include "render_window.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "sys_task.h"
#include "text.h"
#include "contest_comm.h"

static void ContestScoreDisplay_InitBackground(ImageClipBg *param0, BgConfig *param1);
static void ContestScoreDisplay_LoadMessageBox(BgConfig *param0, const Options *options);
static void ContestScoreDisplay_CreateWindow(Window **param0, BgConfig *param1, int param2, int param3, int param4, int param5, int param6, BOOL param7);
static void ContestScoreDisplay_FreeBackground(ImageClipBg *param0);
static void ContestScoreDisplay_DeleteWindow(Window *param0);
static s32 ContestScoreDisplay_PrintCenteredMessage(Window *param0, int param1, int param2, int param3, int param4, int param5, u32 param6);
static s32 ContestScoreDisplay_PrintCenteredMessageWithString(Window *param0, int param1, int param2, int param3, int param4, int param5, u32 param6, String **param7);
static s32 ContestScoreDisplay_PrintMessage(Window *param0, enum NarcID narcID, int param2, int param3, int param4, int param5, TextColor param6, u32 param7);
static s32 ContestScoreDisplay_PrintMessageWithString(Window *param0, enum NarcID narcID, int param2, int param3, int param4, int param5, u32 param6, u32 param7, String **param8);
static void ContestScoreDisplay_AddIcons(ContestScoreDisplayIconRow *param0, SpriteList *param1, SpriteResourceCollection **param2, int param3, NARC *param4);
static void ContestScoreDisplay_SetIconCount(ContestScoreDisplayIconRow *param0, int param1);
static void ContestScoreDisplay_RemoveIcons(ContestScoreDisplayIconRow *param0, SpriteResourceCollection **param1);
static void ContestScoreDisplay_AddScore(ContestScoreDisplayScore *param0, SpriteList *param1, SpriteResourceCollection **param2, int param3, BgConfig *param4, ContestScoringCommState *param5, NARC *param6);
static void ContestScoreDisplay_RemoveScore(ContestScoreDisplayScore *param0, SpriteResourceCollection **param1);
static void ContestScoreDisplay_UpdateScore(ContestScoreDisplayScore *param0);
static void ContestScoreDisplay_DecrementScoreTimer(ContestScoreDisplayScore *param0);
static void ContestScoreDisplay_CheckScoreChanged(ContestScoreDisplayScore *param0);
static void ContestScoreDisplay_UpdateScoreDigits(ContestScoreDisplayScore *param0);
static void ContestScoreDisplay_StartScorePop(ContestScoreDisplayScore *param0, ContestScoreDisplayScoreAnimation *param1);
static void ContestScoreDisplay_UpdateScorePop(ContestScoreDisplayScoreAnimation *param0);
static BOOL ContestScoreDisplay_IsScorePopDone(const ContestScoreDisplayScoreAnimation *param0);
static void ContestScoreDisplay_LoadSpriteResources(SpriteResource **param0, SpriteResourceCollection **param1, int param2, NARC *param3, int param4, int param5, int param6, int param7, int param8, int param9);
static void ContestScoreDisplay_FreeSpriteResources(SpriteResource **param0, SpriteResourceCollection **param1);
static void ContestScoreDisplay_BuildResourcesHeader(SpriteResource **param0, SpriteResourceCollection **param1, SpriteResourcesHeader *param2, int param3);
static void ContestScoreDisplay_InitTween(ContestScoreDisplayTween *param0, fx32 param1, fx32 param2, int param3);
static BOOL ContestScoreDisplay_UpdateTween(ContestScoreDisplayTween *param0);

void ContestScoreDisplay_Init(ContestScoreDisplay *param0, ContestScoreDisplayTemplate *param1, int param2)
{
    if (param2 & 1) {
        memset(param0, 0, sizeof(ContestScoreDisplay));
    }

    if (param2 & 2) {
        ContestScoreDisplay_InitBackground(&param0->unk_00, param1->unk_00);
    }

    if (param2 & 4) {
        ContestScoreDisplay_CreateWindow(&param0->unk_2C, param1->unk_00, 2, 19, 27, 4, (18 + 12) + 1, 1);
    }

    if (param2 & 8) {
        ContestScoreDisplay_AddIcons(&param0->unk_38, param1->unk_04, param1->unk_08, param1->unk_10, param1->unk_24);
    }

    if (param2 & 16) {
        ContestScoreDisplay_AddScore(&param0->unk_A0, param1->unk_04, param1->unk_08, param1->unk_1C, param1->unk_00, param1->unk_20, param1->unk_24);
    }

    if (param2 & 32) {
        ContestScoreDisplay_CreateWindow(&param0->unk_134, param1->unk_00, 2, 1, 27, 2, (18 + 12) + (1 + (27 * 4)), 1);
        Window_FillTilemap(param0->unk_134, 15);
        ContestScoreDisplay_PrintMessage(param0->unk_134, 26, param1->unk_14, 6, 0, 0, TEXT_COLOR(1, 2, 15), TEXT_SPEED_NO_TRANSFER);
        ContestScoreDisplay_PrintMessage(param0->unk_134, 26, param1->unk_14, param1->unk_18, 72, 0, TEXT_COLOR(1, 2, 15), TEXT_SPEED_NO_TRANSFER);
        Window_DrawMessageBoxWithScrollCursor(param0->unk_134, 0, 1, 1);
    }

    param0->unk_30 = param1->unk_04;
    param0->unk_34 = param1->unk_08;

    ContestScoreDisplay_LoadMessageBox(param1->unk_00, param1->options);

    param0->unk_13C = Options_Frame(param1->options);
    param0->unk_140 = Options_TextFrameDelay(param1->options);
    param0->unk_138 |= param2;
}

void ContestScoreDisplay_Free(ContestScoreDisplay *param0)
{
    if (param0->unk_138 & 2) {
        ContestScoreDisplay_FreeBackground(&param0->unk_00);
        param0->unk_138 &= ~2;
    }

    if (param0->unk_138 & 4) {
        ContestScoreDisplay_DeleteWindow(param0->unk_2C);
        param0->unk_138 &= ~4;
    }

    if (param0->unk_138 & 8) {
        ContestScoreDisplay_RemoveIcons(&param0->unk_38, param0->unk_34);
        param0->unk_138 &= ~8;
    }

    if (param0->unk_138 & 16) {
        ContestScoreDisplay_RemoveScore(&param0->unk_A0, param0->unk_34);
        param0->unk_138 &= ~16;
    }

    if (param0->unk_138 & 32) {
        ContestScoreDisplay_DeleteWindow(param0->unk_134);
        param0->unk_138 &= ~32;
    }

    memset(param0, 0, sizeof(ContestScoreDisplay));
}

void ContestScoreDisplay_CommitScore(ContestScoreDisplay *param0)
{
    if (param0->unk_138 & 16) {
        ContestScoreDisplay_UpdateScore(&param0->unk_A0);
    }
}

void ContestScoreDisplay_DrawMessage(ContestScoreDisplay *param0, int param1, int param2, int param3)
{
    GF_ASSERT(param0->unk_138 & 4);
    ContestScoreDisplay_PrintCenteredMessage(param0->unk_2C, param1, param2, param3, 0, 0, TEXT_SPEED_NO_TRANSFER);
}

s32 ContestScoreDisplay_DrawMessageWithString(ContestScoreDisplay *param0, int param1, int param2, int param3)
{
    GF_ASSERT(param0->unk_138 & 4);
    return ContestScoreDisplay_PrintCenteredMessageWithString(param0->unk_2C, param1, param2, param3, 0, 0, param0->unk_140, &param0->unk_144);
}

void ContestScoreDisplay_FreeMessageString(ContestScoreDisplay *param0)
{
    String_Free(param0->unk_144);
    param0->unk_144 = NULL;
}

void ContestScoreDisplay_SetVisibleIcons(ContestScoreDisplay *param0, int param1)
{
    ContestScoreDisplay_SetIconCount(&param0->unk_38, param1);
}

int ContestScoreDisplay_GetScore(const ContestScoreDisplay *param0)
{
    return param0->unk_A0.unk_1C;
}

void ContestScoreDisplay_SetScoreTimer(ContestScoreDisplay *param0, int param1)
{
    param0->unk_A0.unk_20 = param1;
}

BOOL ContestScoreDisplay_IsScoreAnimationDone(const ContestScoreDisplay *param0)
{
    return ContestScoreDisplay_IsScorePopDone(&param0->unk_A0.unk_30);
}

static void ContestScoreDisplay_InitBackground(ImageClipBg *param0, BgConfig *param1)
{
    ImageClipBgTemplate v0;

    v0.unk_00 = param1;
    v0.narcID = NARC_INDEX_GRAPHIC__IMAGECLIP;
    v0.unk_08 = 224;
    v0.unk_0C = 225;
    v0.unk_10 = 226;
    v0.unk_14 = 0;
    v0.unk_18 = 0;
    v0.unk_1C = 4;
    v0.unk_20 = 1;
    v0.unk_24 = 0;
    v0.unk_28 = 0;
    v0.heapID = HEAP_ID_14;

    ImageClipBg_Init(param0, &v0);
}

static void ContestScoreDisplay_LoadMessageBox(BgConfig *param0, const Options *options)
{
    int frame = Options_Frame(options);

    LoadMessageBoxGraphics(param0, BG_LAYER_SUB_1, 1, 1, frame, HEAP_ID_14);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_SUB_BG, PLTT_OFFSET(2), HEAP_ID_14);
}

static void ContestScoreDisplay_CreateWindow(Window **param0, BgConfig *param1, int param2, int param3, int param4, int param5, int param6, BOOL param7)
{
    *param0 = Window_New(HEAP_ID_14, 1);

    Window_Init(*param0);
    Window_Add(param1, *param0, 5, param2, param3, param4, param5, 2, param6);
    Window_FillTilemap(*param0, 15);

    if (param7) {
        Window_DrawMessageBoxWithScrollCursor(*param0, 0, 1, 1);
    }

    Window_CopyToVRAM(*param0);
}

static void ContestScoreDisplay_FreeBackground(ImageClipBg *param0)
{
    ImageClipBg_Free(param0);
}

static void ContestScoreDisplay_DeleteWindow(Window *param0)
{
    Windows_Delete(param0, 1);
}

static s32 ContestScoreDisplay_PrintCenteredMessage(Window *param0, int param1, int param2, int param3, int param4, int param5, u32 param6)
{
    s32 v0;

    Window_FillTilemap(param0, 15);
    v0 = ContestScoreDisplay_PrintMessage(param0, param1, param2, param3, param4, param5, TEXT_COLOR(1, 2, 15), param6);
    Window_DrawMessageBoxWithScrollCursor(param0, 0, 1, 1);

    return v0;
}

static s32 ContestScoreDisplay_PrintCenteredMessageWithString(Window *param0, int param1, int param2, int param3, int param4, int param5, u32 param6, String **param7)
{
    s32 v0;

    Window_FillTilemap(param0, 15);
    v0 = ContestScoreDisplay_PrintMessageWithString(param0, param1, param2, param3, param4, param5, TEXT_COLOR(1, 2, 15), param6, param7);
    Window_DrawMessageBoxWithScrollCursor(param0, 0, 1, 1);

    return v0;
}

static s32 ContestScoreDisplay_PrintMessage(Window *window, enum NarcID narcID, int bankID, int param3, int param4, int param5, TextColor param6, u32 param7)
{
    MessageLoader *msgLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, narcID, bankID, HEAP_ID_13);
    GF_ASSERT(msgLoader);

    String *v1 = MessageLoader_GetNewString(msgLoader, param3);
    s32 v2 = Text_AddPrinterWithParamsAndColor(window, FONT_MESSAGE, v1, param4, param5, param7, param6, NULL);

    String_Free(v1);
    MessageLoader_Free(msgLoader);

    return v2;
}

static s32 ContestScoreDisplay_PrintMessageWithString(Window *param0, enum NarcID narcID, int bankID, int param3, int param4, int param5, u32 param6, u32 param7, String **param8)
{
    GF_ASSERT(*param8 == NULL);

    MessageLoader *v0 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, narcID, bankID, HEAP_ID_13);
    GF_ASSERT(v0);
    *param8 = MessageLoader_GetNewString(v0, param3);
    s32 v1 = Text_AddPrinterWithParamsAndColor(param0, FONT_MESSAGE, *param8, param4, param5, param7, param6, NULL);

    MessageLoader_Free(v0);

    return v1;
}

static void ContestScoreDisplay_AddIcons(ContestScoreDisplayIconRow *param0, SpriteList *param1, SpriteResourceCollection **param2, int param3, NARC *param4)
{
    SpriteResourcesHeader v0;
    SpriteListTemplate v1;
    int v2, v3;

    ContestScoreDisplay_LoadSpriteResources(param0->unk_00, param2, 14, param4, 103, 225, 102, 101, 2, 2000);
    ContestScoreDisplay_BuildResourcesHeader(param0->unk_00, param2, &v0, 0);

    v1.list = param1;
    v1.resourceData = &v0;
    v1.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    v1.priority = 0;
    v1.heapID = HEAP_ID_14;

    for (v2 = 0; v2 < (20 / 10); v2++) {
        v1.position.y = 104 + (18 * v2);
        v1.position.y *= FX32_ONE;
        v1.position.y += (512 * FX32_ONE);

        for (v3 = 0; v3 < 10; v3++) {
            v1.position.x = 38 + (18 * v3);
            v1.position.x *= FX32_ONE;

            param0->unk_10[(v2 * 10) + v3] = SpriteList_Add(&v1);
            Sprite_SetAnim(param0->unk_10[(v2 * 10) + v3], 1);

            if (((v2 * 10) + v3) >= param3) {
                Sprite_SetDrawFlag(param0->unk_10[(v2 * 10) + v3], FALSE);
            }
        }
    }
}

static void ContestScoreDisplay_SetIconCount(ContestScoreDisplayIconRow *param0, int param1)
{
    int v0;

    if (param0->unk_60 < param1) {
        for (v0 = param0->unk_60; v0 < param1; v0++) {
            Sprite_SetAnim(param0->unk_10[v0], 0);
        }
    } else if (param0->unk_60 > param1) {
        for (v0 = param0->unk_60 - 1; v0 >= param1; v0--) {
            Sprite_SetAnim(param0->unk_10[v0], 1);
        }
    }

    param0->unk_60 = param1;
}

static void ContestScoreDisplay_RemoveIcons(ContestScoreDisplayIconRow *param0, SpriteResourceCollection **param1)
{
    int v0;

    for (v0 = 0; v0 < 20; v0++) {
        Sprite_Delete(param0->unk_10[v0]);
    }

    ContestScoreDisplay_FreeSpriteResources(param0->unk_00, param1);
}

static void ContestScoreDisplay_LoadSpriteResources(SpriteResource **param0, SpriteResourceCollection **param1, int param2, NARC *param3, int param4, int param5, int param6, int param7, int param8, int param9)
{
    param0[0] = SpriteResourceCollection_AddTilesFrom(param1[0], param3, param4, 0, param9 + param4, NNS_G2D_VRAM_TYPE_2DSUB, param2);

    SpriteTransfer_RequestCharAtEnd(param0[0]);
    SpriteResource_ReleaseData(param0[0]);

    param0[1] = SpriteResourceCollection_AddPaletteFrom(param1[1], param3, param5, 0, param9 + param5, NNS_G2D_VRAM_TYPE_2DSUB, param8, param2);

    SpriteTransfer_RequestPlttFreeSpace(param0[1]);
    SpriteResource_ReleaseData(param0[1]);

    param0[2] = SpriteResourceCollection_AddFrom(param1[2], param3, param6, 0, param9 + param6, 2, param2);
    param0[3] = SpriteResourceCollection_AddFrom(param1[3], param3, param7, 0, param9 + param7, 3, param2);
}

static void ContestScoreDisplay_FreeSpriteResources(SpriteResource **param0, SpriteResourceCollection **param1)
{
    SpriteTransfer_ResetCharTransfer(param0[0]);
    SpriteTransfer_ResetPlttTransfer(param0[1]);
    SpriteResourceCollection_Remove(param1[0], param0[0]);
    SpriteResourceCollection_Remove(param1[1], param0[1]);
    SpriteResourceCollection_Remove(param1[2], param0[2]);
    SpriteResourceCollection_Remove(param1[3], param0[3]);
}

static void ContestScoreDisplay_BuildResourcesHeader(SpriteResource **param0, SpriteResourceCollection **param1, SpriteResourcesHeader *param2, int param3)
{
    SpriteResourcesHeader_Init(param2, SpriteResource_GetID(param0[0]), SpriteResource_GetID(param0[1]), SpriteResource_GetID(param0[2]), SpriteResource_GetID(param0[3]), 0xffffffff, 0xffffffff, 0, param3, param1[0], param1[1], param1[2], param1[3], NULL, NULL);
}

static void ContestScoreDisplay_AddScore(ContestScoreDisplayScore *param0, SpriteList *param1, SpriteResourceCollection **param2, int param3, BgConfig *param4, ContestScoringCommState *param5, NARC *param6)
{
    SpriteResourcesHeader v0;
    SpriteListTemplate v1;
    int v2;

    ContestScoreDisplay_LoadSpriteResources(param0->unk_00, param2, 14, param6, 229, 230, 228, 227, 2, 3000);
    ContestScoreDisplay_BuildResourcesHeader(param0->unk_00, param2, &v0, 0);

    v1.list = param1;
    v1.resourceData = &v0;
    v1.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    v1.priority = 0;
    v1.heapID = HEAP_ID_14;
    v1.position.y = 58 * FX32_ONE;
    v1.position.y += (512 * FX32_ONE);

    for (v2 = 0; v2 < 2; v2++) {
        v1.position.x = 103 + (v2 * 24);
        v1.position.x *= FX32_ONE;
        param0->unk_10[v2] = SpriteList_Add(&v1);
    }

    param0->unk_1C = param3;
    param0->unk_20 = param3 * 30;
    param0->unk_2C = param5;
    param0->unk_2C->localValue.value = param3;
    param0->unk_2C->sendValue.value = param3;
    param0->unk_90 = 0;

    ContestScoreDisplay_UpdateScoreDigits(param0);
    ContestScoreDisplay_CreateWindow(&param0->unk_18, param4, 10, 8, 14, 4, (18 + 12) + ((1 + (27 * 4)) + (27 * 2)), 0);

    Window_FillTilemap(param0->unk_18, 0);

    ContestScoreDisplay_PrintMessage(param0->unk_18, 26, 385, 4, 0, 4, TEXT_COLOR(1, 2, 0), TEXT_SPEED_NO_TRANSFER);
    ContestScoreDisplay_PrintMessage(param0->unk_18, 26, 385, 5, 0 + 72, 4, TEXT_COLOR(1, 2, 0), TEXT_SPEED_NO_TRANSFER);

    Window_CopyToVRAM(param0->unk_18);
}

static void ContestScoreDisplay_RemoveScore(ContestScoreDisplayScore *param0, SpriteResourceCollection **param1)
{
    if (param0->unk_24) {
        SysTask_Done(param0->unk_24);
    }

    if (param0->unk_28) {
        SysTask_Done(param0->unk_28);
    }

    ContestScoreDisplay_FreeSpriteResources(param0->unk_00, param1);
    ContestScoreDisplay_DeleteWindow(param0->unk_18);

    memset(param0, 0, sizeof(ContestScoreDisplayScore));
}

static void ContestScoreDisplay_UpdateScore(ContestScoreDisplayScore *param0)
{
    u32 v0;

    ContestScoreDisplay_DecrementScoreTimer(param0);
    v0 = param0->unk_20 / 30;
    ContestComm_SendScore(param0->unk_2C, v0);

    ContestScoreDisplay_CheckScoreChanged(param0);
    ContestScoreDisplay_UpdateScoreDigits(param0);
    ContestScoreDisplay_UpdateScorePop(&param0->unk_30);
}

static void ContestScoreDisplay_CheckScoreChanged(ContestScoreDisplayScore *param0)
{
    if (param0->unk_1C != param0->unk_2C->localValue.value) {
        param0->unk_1C = param0->unk_2C->localValue.value;

        if (param0->unk_1C <= 10) {
            ContestScoreDisplay_StartScorePop(param0, &param0->unk_30);
            Sound_PlayEffect(SEQ_SE_DP_HYUN2_sseq);
        }
    }
}

static void ContestScoreDisplay_UpdateScoreDigits(ContestScoreDisplayScore *param0)
{
    int v0;
    int v1;
    int v2 = param0->unk_1C;
    int v3 = 1;

    for (v0 = 1; v0 < 2; v0++) {
        v3 *= 10;
    }

    for (v0 = 0; v0 < 2; v0++) {
        v1 = v2 / v3;

        GF_ASSERT(v1 <= 10);
        Sprite_SetAnim(param0->unk_10[v0], 0 + v1);

        v2 -= v1 * v3;
        v3 /= 10;

        if (param0->unk_90 == 0) {
            if (param0->unk_1C <= 10) {
                Sprite_SetExplicitPaletteWithOffset(param0->unk_10[v0], 1);

                if (v0 == 2 - 1) {
                    param0->unk_90 = 1;
                }
            }
        }
    }
}

static void ContestScoreDisplay_DecrementScoreTimer(ContestScoreDisplayScore *param0)
{
    if ((param0->unk_20 - 1) >= 0) {
        param0->unk_20--;
    }
}

static void ContestScoreDisplay_InitTween(ContestScoreDisplayTween *param0, fx32 param1, fx32 param2, int param3)
{
    param0->unk_00 = param1;
    param0->unk_04 = param1;
    param0->unk_08 = param2 - param1;
    param0->unk_10 = param3;
    param0->unk_0C = 0;
}

static BOOL ContestScoreDisplay_UpdateTween(ContestScoreDisplayTween *param0)
{
    fx32 v0;

    v0 = FX_Mul(param0->unk_08, param0->unk_0C << FX32_SHIFT);
    v0 = FX_Div(v0, param0->unk_10 << FX32_SHIFT);

    param0->unk_00 = v0 + param0->unk_04;

    if ((param0->unk_0C + 1) <= param0->unk_10) {
        param0->unk_0C++;
        return 0;
    }

    param0->unk_0C = param0->unk_10;

    return 1;
}

static void ContestScoreDisplay_StartScorePop(ContestScoreDisplayScore *param0, ContestScoreDisplayScoreAnimation *param1)
{
    int v0;
    fx32 v1;
    fx32 v2, v3;
    VecFx32 v4;
    int v5;

    v4.y = 58 * FX32_ONE;
    v4.y += (512 * FX32_ONE);

    for (v0 = 0; v0 < 2; v0++) {
        param1->unk_04[v0] = param0->unk_10[v0];
        Sprite_SetAffineOverwriteMode(param1->unk_04[v0], 2);
        v4.x = 103 + (v0 * 24);
        v4.x *= FX32_ONE;
        param1->unk_0C[v0] = v4;
    }

    v5 = 10 - param0->unk_1C;

    if (v5 > 0) {
        v1 = (FX32_CONST(1.0f)) + FX_Mul(v5 << FX32_SHIFT, (FX32_CONST(0.150f)));
    } else {
        v1 = (FX32_CONST(1.0f));
    }

    ContestScoreDisplay_InitTween(&param1->unk_24, v1, (FX32_CONST(1.0f)), 16);

    v2 = FX_Mul((FX32_CONST(24)), v1);
    v3 = FX_Mul((FX32_CONST(24)), v1);
    v2 = v2 - (FX32_CONST(24));
    v3 = v3 - (FX32_CONST(24));

    ContestScoreDisplay_InitTween(&param1->unk_38, v2, 0, 16);
    ContestScoreDisplay_InitTween(&param1->unk_4C, v3, 0, 16);

    param1->unk_00 = 1;
}

static void ContestScoreDisplay_UpdateScorePop(ContestScoreDisplayScoreAnimation *param0)
{
    VecFx32 v0;
    VecFx32 v1;
    BOOL v2;

    if (param0->unk_00 == 0) {
        return;
    }

    v2 = ContestScoreDisplay_UpdateTween(&param0->unk_24);

    ContestScoreDisplay_UpdateTween(&param0->unk_38);
    ContestScoreDisplay_UpdateTween(&param0->unk_4C);

    v0.x = param0->unk_24.unk_00;
    v0.y = param0->unk_24.unk_00;
    v0.z = param0->unk_24.unk_00;

    Sprite_SetAffineScale(param0->unk_04[0], &v0);
    Sprite_SetAffineScale(param0->unk_04[1], &v0);

    v1 = param0->unk_0C[0];
    v1.x -= param0->unk_38.unk_00;
    v1.y -= param0->unk_4C.unk_00;

    Sprite_SetPosition(param0->unk_04[0], &v1);

    v1 = param0->unk_0C[1];
    v1.y -= param0->unk_4C.unk_00;

    Sprite_SetPosition(param0->unk_04[1], &v1);

    if (v2) {
        param0->unk_00 = 0;
    }
}

static BOOL ContestScoreDisplay_IsScorePopDone(const ContestScoreDisplayScoreAnimation *param0)
{
    if (param0->unk_00 == 1) {
        return 0;
    }

    return 1;
}
