#include "applications/pc_boxes/box_touch_dial_graphics.h"

#include <nitro.h>
#include <string.h>

#include "applications/pc_boxes/box_app_manager.h"
#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics.h"
#include "applications/pc_boxes/box_selection_popup.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_selection_popup.h"
#include "applications/pc_boxes/struct_box_touch_dial_graphics_decl.h"

#include "bg_window.h"
#include "enums.h"
#include "graphics.h"
#include "heap.h"
#include "math_util.h"
#include "narc.h"
#include "pc_boxes.h"
#include "sprite.h"
#include "string_gf.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "text.h"

typedef struct {
    BoxTouchDialGraphics *touchDialGraphics;
    u32 state;
    Sprite *sprite;
    u16 scrollSteps;
    s16 blendStep;
    fx32 offset;
    fx32 offsetDelta;
    int endOffset;
} BoxTouchDialAnim;

typedef struct {
    void *animManager;
    Sprite *sprite;
    fx32 position;
    fx32 targetPosition;
    fx32 positionStep;
    u16 stepCount;
    u16 delayCount;
    BOOL hasChainAnim;
    fx32 chainStartPosition;
    fx32 chainTargetPosition;
    fx32 chainStep;
    u16 chainStepCount;
    u16 chainDelayCount;
} BoxTouchDialIconAnim;

typedef struct {
    BoxTouchDialGraphics *touchDialGraphics;
    Sprite **sprites;
    BoxTouchDialIconAnim iconAnims[10];
    u8 iconFlags[10];
    u8 iconCount;
    u8 activeAnimCount;
    u8 state;
    u8 stepTimer;
} BoxTouchDialAnimManager;

struct BoxTouchDialGraphics_t {
    BoxGraphics *boxGraphics;
    const BoxApplication *boxApp;
    BgConfig *bgConfig;
    SpriteList *spriteList;
    u32 selectedTouchDial;
    SysTask *task;
    NNSG2dImagePaletteProxy paletteProxy;
    Sprite *leftArrowSprite;
    Sprite *rightArrowSprite;
    Sprite *markingSprites[8];
    Sprite *iconSprites[10];
    int scrollDelta;
    int markingsScrollOffset;
    String *boxNameString;
    Window boxNameWindow;
    void *cellBank;
    NNSG2dCellDataBank *cellBankData;
    void *animBank;
    NNSG2dAnimBankData *animBankData;
    void *formCellBank;
    NNSG2dCellDataBank *formCellBankData;
    void *formAnimBank;
    NNSG2dAnimBankData *formAnimBankData;
    BoxTouchDialAnim anim;
    u8 blendTable1[16];
    u8 blendTable2[16];
};

static void BoxTouchDial_InitBlendTable(BoxTouchDialGraphics *param0);
static void BoxTouchDial_LoadDials(BoxTouchDialGraphics *param0, NARC *param1);
static void BoxTouchDial_LoadAssets(BoxTouchDialGraphics *param0, NARC *param1);
static SysTask *BoxTouchDial_StartTask(BoxTouchDialGraphics *param0, SysTaskFunc param1, void *param2);
static void BoxTouchDial_FinishTask(BoxTouchDialGraphics *param0);
static BOOL BoxTouchDial_IsTaskDone(BoxTouchDialGraphics *param0);
static void BoxTouchDial_OpenTask(SysTask *param0, void *param1);
static void BoxTouchDial_SwitchTask(SysTask *param0, void *param1);
static void BoxTouchDial_CloseTask(SysTask *param0, void *param1);
static void BoxTouchDial_ScrollBoxJump(BoxTouchDialGraphics *param0);
static void BoxTouchDial_ScrollMarkings(BoxTouchDialGraphics *param0);
static void BoxTouchDial_CreateBoxJumpIcons(BoxTouchDialGraphics *param0);
static void BoxTouchDial_ScrollBoxJumpIcons(BoxTouchDialGraphics *param0);
static void BoxTouchDial_DeleteBoxJumpIcons(BoxTouchDialGraphics *param0);
static u32 BoxTouchDial_GetMarkingAnim(u32 param0, u32 param1);
static void BoxTouchDial_CreateMarkingIcons(BoxTouchDialGraphics *param0);
static void BoxTouchDial_DeleteMarkingIcons(BoxTouchDialGraphics *param0);
static void BoxTouchDial_IconAnimTaskForward(SysTask *param0, void *param1);
static void BoxTouchDial_IconAnimTaskBackward(SysTask *param0, void *param1);
static void BoxTouchDial_IconAnimDone(SysTask *param0, BoxTouchDialIconAnim *param1);
static void BoxTouchDial_StartIconAnim(BoxTouchDialAnimManager *param0, Sprite *param1, BoxTouchDialIconAnim *param2, u32 param3, u32 param4, u32 param5, u32 param6, BOOL param7);
static void BoxTouchDial_StartIconAnimChain(BoxTouchDialAnimManager *param0, BoxTouchDialIconAnim *param1, u32 param2, u32 param3, u32 param4);
static void BoxTouchDial_ShowIconsTask(SysTask *param0, void *param1);
static void BoxTouchDial_ShowIconsDone(void *param0);
static void BoxTouchDial_StartShowIcons(BoxTouchDialGraphics *param0);
static void BoxTouchDial_ScrollIconsTask(SysTask *param0, void *param1);
static void BoxTouchDial_StartScrollIcons(BoxTouchDialGraphics *param0);
static void BoxTouchDial_ShowMarkingsTask(SysTask *param0, void *param1);
static void BoxTouchDial_StartShowMarkings(BoxTouchDialGraphics *param0);
static void BoxTouchDial_ScrollMarkingsTask(SysTask *param0, void *param1);
static void BoxTouchDial_StartScrollMarkings(BoxTouchDialGraphics *param0);
static void BoxTouchDial_HideLabels(BoxTouchDialGraphics *param0);
static void BoxTouchDial_ShowLabels(BoxTouchDialGraphics *param0);
static void BoxTouchDial_DrawBoxNames(BoxTouchDialGraphics *param0);

static const fx32 sBoxTouchDialOffsets[] = {
    0x0,
    0xFFFFFFFFFFFA0000,
    0x58000
};

static const int sBoxTouchDialBg2Offsets[] = {
    0x0,
    0xFFFFFFFFFFFFFF80,
    0x80
};

static const struct {
    s16 x;
    s16 y;
} sBoxTouchDialIconPositions[] = {
    { 0x6A, 0x248 },
    { 0x6A, 0x242 },
    { 0x6A, 0x23E },
    { 0x69, 0x23A },
    { 0x69, 0x238 },
    { 0x69, 0x236 },
    { 0x69, 0x234 },
    { 0x69, 0x232 },
    { 0x69, 0x230 },
    { 0x68, 0x22E },
    { 0x68, 0x22C },
    { 0x68, 0x22A },
    { 0x68, 0x228 },
    { 0x67, 0x226 },
    { 0x67, 0x224 },
    { 0x67, 0x223 },
    { 0x66, 0x221 },
    { 0x66, 0x21F },
    { 0x65, 0x21D },
    { 0x65, 0x21B },
    { 0x64, 0x219 },
    { 0x64, 0x217 },
    { 0x63, 0x216 },
    { 0x62, 0x214 },
    { 0x62, 0x212 },
    { 0x61, 0x210 },
    { 0x60, 0x20E },
    { 0x60, 0x20D },
    { 0x5F, 0x20B },
    { 0x5E, 0x209 },
    { 0x5E, 0x208 },
    { 0x5D, 0x206 },
    { 0x5C, 0x204 },
    { 0x5B, 0x203 },
    { 0x5A, 0x201 },
    { 0x59, 0x1FF },
    { 0x58, 0x1FE },
    { 0x57, 0x1FC },
    { 0x56, 0x1FB },
    { 0x56, 0x1F9 },
    { 0x55, 0x1F8 },
    { 0x53, 0x1F6 },
    { 0x52, 0x1F5 },
    { 0x51, 0x1F3 },
    { 0x50, 0x1F2 },
    { 0x4F, 0x1F0 },
    { 0x4E, 0x1EF },
    { 0x4D, 0x1EE },
    { 0x4C, 0x1EC },
    { 0x4B, 0x1EB },
    { 0x49, 0x1EA },
    { 0x48, 0x1E8 },
    { 0x47, 0x1E7 },
    { 0x46, 0x1E6 },
    { 0x44, 0x1E5 },
    { 0x43, 0x1E4 },
    { 0x42, 0x1E3 },
    { 0x41, 0x1E2 },
    { 0x3F, 0x1E1 },
    { 0x3E, 0x1DF },
    { 0x3D, 0x1DF },
    { 0x3B, 0x1DE },
    { 0x3A, 0x1DD },
    { 0x38, 0x1DC },
    { 0x37, 0x1DB },
    { 0x36, 0x1DA },
    { 0x34, 0x1D9 },
    { 0x33, 0x1D8 },
    { 0x31, 0x1D8 },
    { 0x30, 0x1D7 },
    { 0x2E, 0x1D6 },
    { 0x2D, 0x1D6 },
    { 0x2B, 0x1D5 },
    { 0x2A, 0x1D4 },
    { 0x28, 0x1D4 },
    { 0x27, 0x1D3 },
    { 0x25, 0x1D3 },
    { 0x24, 0x1D2 },
    { 0x22, 0x1D2 },
    { 0x21, 0x1D2 },
    { 0x1F, 0x1D1 },
    { 0x1E, 0x1D1 },
    { 0x1C, 0x1D1 },
    { 0x1A, 0x1D0 },
    { 0x19, 0x1D0 },
    { 0x17, 0x1D0 },
    { 0x16, 0x1D0 },
    { 0x14, 0x1D0 },
    { 0x13, 0x1D0 },
    { 0x11, 0x1D0 },
    { 0x10, 0x1D0 },
    { 0x10, 0x1CE },
    { 0x10, 0x1CC },
    { 0x10, 0x1CA },
    { 0x10, 0x1C8 },
    { 0x10, 0x1C6 },
    { 0x10, 0x1C4 },
    { 0x10, 0x1C2 },
    { 0x10, 0x1C0 },
    { 0x10, 0x1BF },
    { 0x10, 0x1BD },
    { 0x10, 0x1BC },
    { 0x10, 0x1BA },
    { 0x10, 0x1B9 },
    { 0x10, 0x1B7 },
    { 0x10, 0x1B6 },
    { 0x10, 0x1B4 },
    { 0x10, 0x1B3 },
    { 0x10, 0x1B1 },
    { 0x10, 0x1B0 },
    { 0x10, 0x1AE },
    { 0x10, 0x1AD },
    { 0x10, 0x1AB },
    { 0x10, 0x1AA },
    { 0x10, 0x1A8 },
    { 0x10, 0x1A7 },
    { 0x10, 0x1A6 },
    { 0x10, 0x1A4 },
    { 0x10, 0x1A2 },
    { 0x10, 0x1A0 },
    { 0x10, 0x19E },
    { 0x10, 0x19C },
    { 0x10, 0x19A },
    { 0x10, 0x198 },
    { 0x10, 0x196 },
    { 0x10, 0x194 },
    { 0x10, 0x192 },
    { 0x10, 0x190 },
    { 0x10, 0x18E },
    { 0x10, 0x18C },
    { 0x10, 0x18A },
    { 0x10, 0x188 },
    { 0x10, 0x186 },
    { 0x10, 0x184 },
    { 0x10, 0x182 },
    { 0x10, 0x180 },
    { 0x10, 0x17E },
    { 0x10, 0x17C },
    { 0x10, 0x17A },
    { 0x10, 0x178 },
    { 0x10, 0x176 },
    { 0x10, 0x174 },
    { 0x10, 0x172 },
    { 0x10, 0x170 }
};

static const u16 sBoxTouchDialIconOffsets[] = {
    0x8F,
    0x7F,
    0x6A,
    0x4A,
    0x33,
    0x1F,
    0xC,
    0x0
};

BOOL BoxTouchDial_Load(BoxTouchDialGraphics **param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4)
{
    if (BoxApp_GetBoxMode(param2) == PC_MODE_COMPARE) {
        *param0 = NULL;
        return 1;
    } else {
        BoxTouchDialGraphics *v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxTouchDialGraphics));

        if (v0) {
            int v1;

            v0->bgConfig = param3;
            v0->boxGraphics = param1;
            v0->boxApp = param2;
            v0->spriteList = param4;
            v0->task = NULL;
            v0->boxNameString = String_Init(32, HEAP_ID_BOX_GRAPHICS);
            v0->selectedTouchDial = param2->touchDialHelper.selectedTouchDial;
            v0->cellBank = NULL;
            v0->animBank = NULL;
            v0->formCellBank = NULL;
            v0->formAnimBank = NULL;
            v0->leftArrowSprite = NULL;
            v0->rightArrowSprite = NULL;

            for (v1 = 0; v1 < 8; v1++) {
                v0->markingSprites[v1] = NULL;
            }

            for (v1 = 0; v1 < 10; v1++) {
                v0->iconSprites[v1] = NULL;
            }

            v0->markingsScrollOffset = 0;
            BoxTouchDial_InitBlendTable(v0);
            *param0 = v0;

            return 1;
        }

        return 0;
    }
}

static void BoxTouchDial_InitBlendTable(BoxTouchDialGraphics *param0)
{
    fx32 v0, v1, v2;
    int v3;

    v0 = 0;
    v2 = (90 << FX32_SHIFT) / 16;

    param0->blendTable1[0] = 0;
    param0->blendTable2[0] = 16;

    for (v3 = 1; v3 < (16 - 1); v3++) {
        v0 += v2;
        param0->blendTable1[v3] = (CalcSineDegrees(v0 >> FX32_SHIFT) * 16) >> FX32_SHIFT;
        param0->blendTable2[v3] = 16 - param0->blendTable1[v3];
    }

    param0->blendTable1[v3] = 16;
    param0->blendTable2[v3] = 0;
}

void BoxTouchDial_Free(BoxTouchDialGraphics *param0)
{
    if (param0) {
        int v0;

        Window_Remove(&(param0->boxNameWindow));

        if (param0->cellBank) {
            Heap_Free(param0->cellBank);
        }

        if (param0->animBank) {
            Heap_Free(param0->animBank);
        }

        if (param0->formCellBank) {
            Heap_Free(param0->formCellBank);
        }

        if (param0->formAnimBank) {
            Heap_Free(param0->formAnimBank);
        }

        if (param0->leftArrowSprite) {
            Sprite_Delete(param0->leftArrowSprite);
        }

        if (param0->rightArrowSprite) {
            Sprite_Delete(param0->rightArrowSprite);
        }

        if (param0->boxNameString != NULL) {
            String_Free(param0->boxNameString);
        }

        for (v0 = 0; v0 < 8; v0++) {
            if (param0->markingSprites[v0]) {
                Sprite_Delete(param0->markingSprites[v0]);
            }
        }

        for (v0 = 0; v0 < 10; v0++) {
            if (param0->iconSprites[v0]) {
                Sprite_Delete(param0->iconSprites[v0]);
            }
        }

        Heap_Free(param0);
    }
}

void BoxTouchDial_Init(BoxTouchDialGraphics *param0, NARC *param1)
{
    if (param0) {
        Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 127, param0->bgConfig, 7, 0, 0, 1, HEAP_ID_BOX_GRAPHICS);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 124, param0->bgConfig, 7, 0, 0, 1, HEAP_ID_BOX_GRAPHICS);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 125, param0->bgConfig, 6, 0, 0, 1, HEAP_ID_BOX_GRAPHICS);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 126, param0->bgConfig, 5, 0, 0, 1, HEAP_ID_BOX_GRAPHICS);
        Bg_FillTilesRange(param0->bgConfig, 4, 0x0, 1, 0);
        Bg_FillTilemapRect(param0->bgConfig, 4, 0x0, 0, 0, 32, 32, 17);
        Bg_CopyTilemapBufferToVRAM(param0->bgConfig, 4);
        Bg_SetOffset(param0->bgConfig, BG_LAYER_SUB_1, 0, sBoxTouchDialOffsets[param0->selectedTouchDial]);
        Window_Add(param0->bgConfig, &(param0->boxNameWindow), 4, 0, 0, 32, 24, 2, 0);
        Window_FillTilemap(&(param0->boxNameWindow), 0x0);
        Window_CopyToVRAM(&param0->boxNameWindow);
        BoxTouchDial_HideLabels(param0);
        Graphics_LoadPaletteFromOpenNARC(param1, 128, 4, 0, 0x20 * 3, HEAP_ID_BOX_GRAPHICS);
        BoxTouchDial_LoadDials(param0, param1);
    }
}

static void BoxTouchDial_LoadDials(BoxTouchDialGraphics *param0, NARC *param1)
{
    SpriteResourcesHeader v0;
    NNSG2dImageProxy v1;

    BoxTouchDial_LoadAssets(param0, param1);

    NNS_G2dInitImageProxy(&v1);
    Graphics_LoadImageMappingFromOpenNARC(param1, 138, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DSUB, 0 * 0x20, 10, &(v1));

    BoxGraphics_InitSpriteResources(&v0, &v1, &(param0->paletteProxy), param0->cellBankData, param0->animBankData, 3);

    param0->leftArrowSprite = BoxGraphics_CreateSprite(param0->spriteList, &v0, 0, 568, 49, NNS_G2D_VRAM_TYPE_2DSUB);
    param0->rightArrowSprite = BoxGraphics_CreateSprite(param0->spriteList, &v0, 256, 568, 49, NNS_G2D_VRAM_TYPE_2DSUB);

    Sprite_SetFlipMode(param0->rightArrowSprite, 1);

    if (BoxApp_GetBoxMode(param0->boxApp) == PC_MODE_MOVE_ITEMS) {
        Sprite_SetAnim(param0->rightArrowSprite, 1);
    }
}

static void BoxTouchDial_LoadAssets(BoxTouchDialGraphics *param0, NARC *param1)
{
    param0->cellBank = Graphics_GetCellBankFromOpenNARC(param1, 139, 1, &(param0->cellBankData), HEAP_ID_BOX_GRAPHICS);
    param0->animBank = Graphics_GetAnimBankFromOpenNARC(param1, 140, 1, &(param0->animBankData), HEAP_ID_BOX_GRAPHICS);
    param0->formCellBank = Graphics_GetCellBankFromOpenNARC(param1, 142, 1, &(param0->formCellBankData), HEAP_ID_BOX_GRAPHICS);
    param0->formAnimBank = Graphics_GetAnimBankFromOpenNARC(param1, 143, 1, &(param0->formAnimBankData), HEAP_ID_BOX_GRAPHICS);

    NNS_G2dInitImagePaletteProxy(&(param0->paletteProxy));
    Graphics_LoadPartialPaletteFromOpenNARC(param1, 144, NNS_G2D_VRAM_TYPE_2DSUB, 0, 10, &(param0->paletteProxy));
}

static SysTask *BoxTouchDial_StartTask(BoxTouchDialGraphics *param0, SysTaskFunc param1, void *param2)
{
    param0->task = BoxGraphics_StartVBlankTask(param1, param2, 0);
    return param0->task;
}

static void BoxTouchDial_FinishTask(BoxTouchDialGraphics *param0)
{
    SysTask_Done(param0->task);
    param0->task = NULL;
}

static BOOL BoxTouchDial_IsTaskDone(BoxTouchDialGraphics *param0)
{
    return param0->task == NULL;
}

void BoxTouchDial_ChangeSelected(BoxTouchDialGraphics *param0)
{
    if (param0) {
        u32 selectedTouchDialID = param0->boxApp->touchDialHelper.selectedTouchDial;

        if (param0->selectedTouchDial != selectedTouchDialID) {
            SysTaskFunc v1;
            BoxTouchDialAnim *v2 = &(param0->anim);

            v2->touchDialGraphics = param0;
            v2->sprite = NULL;
            v2->state = 0;

            switch (selectedTouchDialID) {
            case TOUCH_DIALS_NONE:
                v2->scrollSteps = 8;
                v1 = BoxTouchDial_CloseTask;
                BoxTouchDial_DeleteBoxJumpIcons(param0);
                BoxTouchDial_DeleteMarkingIcons(param0);
                BoxTouchDial_HideLabels(param0);
                break;
            case TOUCH_DIALS_BOX_JUMP:
                v2->scrollSteps = 8;

                if (param0->selectedTouchDial == 0) {
                    v1 = BoxTouchDial_OpenTask;
                } else {
                    v1 = BoxTouchDial_SwitchTask;
                    v2->scrollSteps += 8;
                }

                BoxTouchDial_DeleteMarkingIcons(param0);
                v2->sprite = param0->leftArrowSprite;
                break;
            case TOUCH_DIALS_MARKINGS:
                v2->scrollSteps = 8;

                if (param0->selectedTouchDial == 0) {
                    v1 = BoxTouchDial_OpenTask;
                } else {
                    v1 = BoxTouchDial_SwitchTask;
                    v2->scrollSteps += 8;
                }

                v2->sprite = param0->rightArrowSprite;
                BoxTouchDial_DeleteBoxJumpIcons(param0);
                BoxTouchDial_HideLabels(param0);
                break;
            default:
                Heap_Free(v2);
                return;
            }

            param0->selectedTouchDial = selectedTouchDialID;
            v2->offset = (Bg_GetXOffset(param0->bgConfig, 5) * FX32_ONE);
            v2->offsetDelta = (sBoxTouchDialOffsets[selectedTouchDialID] - v2->offset) / v2->scrollSteps;
            v2->endOffset = sBoxTouchDialOffsets[selectedTouchDialID] >> FX32_SHIFT;

            if (v2->sprite != NULL) {
                Sprite_SetAnim(v2->sprite, 1);
            }

            BoxTouchDial_StartTask(param0, v1, v2);
        }
    }
}

BOOL BoxTouchDial_IsChangeDone(BoxTouchDialGraphics *param0)
{
    if (param0) {
        return BoxTouchDial_IsTaskDone(param0);
    } else {
        return 1;
    }
}

static void BoxTouchDial_OpenTask(SysTask *param0, void *param1)
{
    BoxTouchDialAnim *v0 = (BoxTouchDialAnim *)param1;
    BoxTouchDialGraphics *v1 = v0->touchDialGraphics;

    switch (v0->state) {
    case 0:
        if (Sprite_IsAnimated(v0->sprite) == 0) {
            v0->state++;
        }
        break;
    case 1:
        if (v0->scrollSteps) {
            v0->offset += v0->offsetDelta;
            Bg_SetOffset(v1->bgConfig, BG_LAYER_SUB_1, 0, (v0->offset >> FX32_SHIFT));
            v0->scrollSteps--;
        } else {
            Bg_SetOffset(v1->bgConfig, BG_LAYER_SUB_1, 0, v0->endOffset);
            G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, 0, 16);
            v0->state++;
        }
        break;
    case 2:
        Bg_SetOffset(v1->bgConfig, BG_LAYER_SUB_2, 0, sBoxTouchDialBg2Offsets[v1->selectedTouchDial]);
        v0->blendStep = 0;
        v0->state++;
        break;
    case 3:
        G2S_ChangeBlendAlpha(v1->blendTable1[v0->blendStep], v1->blendTable2[v0->blendStep]);

        if (++(v0->blendStep) >= 16) {
            Sprite_SetAnim(v0->sprite, 0);
            BoxTouchDial_FinishTask(v1);
        }
        break;
    }
}

static void BoxTouchDial_SwitchTask(SysTask *param0, void *param1)
{
    BoxTouchDialAnim *v0 = (BoxTouchDialAnim *)param1;
    BoxTouchDialGraphics *v1 = v0->touchDialGraphics;

    switch (v0->state) {
    case 0:
        if (Sprite_IsAnimated(v0->sprite) == 0) {
            G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, 16, 0);
            v0->blendStep = (16 - 1);
            v0->state++;
        }
        break;
    case 1:
        v0->blendStep--;
        G2S_ChangeBlendAlpha(v1->blendTable1[v0->blendStep], v1->blendTable2[v0->blendStep]);

        if (v0->blendStep == 0) {
            Bg_SetOffset(v1->bgConfig, BG_LAYER_SUB_2, 0, sBoxTouchDialBg2Offsets[v1->selectedTouchDial]);
            v0->state++;
        }
        break;
    case 2:
        if (v0->scrollSteps) {
            v0->offset += v0->offsetDelta;
            Bg_SetOffset(v1->bgConfig, BG_LAYER_SUB_1, 0, (v0->offset >> FX32_SHIFT));
            v0->scrollSteps--;
        } else {
            Bg_SetOffset(v1->bgConfig, BG_LAYER_SUB_1, 0, v0->endOffset);
            G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, 0, 16);
            v0->state++;
        }
        break;
    case 3:
        Bg_SetOffset(v1->bgConfig, BG_LAYER_SUB_2, 0, sBoxTouchDialBg2Offsets[v1->selectedTouchDial]);
        v0->blendStep = 0;
        v0->state++;
        break;
    case 4:
        G2S_ChangeBlendAlpha(v1->blendTable1[v0->blendStep], v1->blendTable2[v0->blendStep]);

        if (++(v0->blendStep) >= 16) {
            Sprite_SetAnim(v0->sprite, 0);
            BoxTouchDial_FinishTask(v1);
        }
        break;
    }
}

static void BoxTouchDial_CloseTask(SysTask *param0, void *param1)
{
    BoxTouchDialAnim *v0 = (BoxTouchDialAnim *)param1;
    BoxTouchDialGraphics *v1 = v0->touchDialGraphics;

    switch (v0->state) {
    case 0:
        v0->blendStep = (16 - 1);
        v0->state++;
    case 1:
        v0->blendStep--;
        G2S_ChangeBlendAlpha(v1->blendTable1[v0->blendStep], v1->blendTable2[v0->blendStep]);

        if (v0->blendStep == 0) {
            Bg_SetOffset(v1->bgConfig, BG_LAYER_SUB_2, 0, sBoxTouchDialBg2Offsets[0]);
            v0->state++;
        }
        break;
    case 2:
        if (v0->scrollSteps) {
            v0->offset += v0->offsetDelta;
            Bg_SetOffset(v1->bgConfig, BG_LAYER_SUB_1, 0, (v0->offset >> FX32_SHIFT));
            v0->scrollSteps--;
        } else {
            Bg_SetOffset(v1->bgConfig, BG_LAYER_SUB_1, 0, v0->endOffset);
            v0->state++;
        }
        break;
    case 3:
        BoxTouchDial_FinishTask(v1);
        break;
    }
}

void BoxTouchDial_Update(BoxTouchDialGraphics *param0)
{
    if (param0) {
        switch (param0->selectedTouchDial) {
        case 1:
            BoxTouchDial_CreateBoxJumpIcons(param0);
            BoxTouchDial_StartShowIcons(param0);
            break;
        case 2:
            BoxTouchDial_CreateMarkingIcons(param0);
            BoxTouchDial_StartShowMarkings(param0);
            break;
        }
    }
}

BOOL BoxTouchDial_IsUpdateDone(BoxTouchDialGraphics *param0)
{
    if (param0) {
        if (BoxTouchDial_IsTaskDone(param0)) {
            if (param0->selectedTouchDial == 1) {
                BoxTouchDial_DrawBoxNames(param0);
            }

            return 1;
        }

        return 0;
    } else {
        return 1;
    }
}

void BoxTouchDial_Scroll(BoxTouchDialGraphics *param0)
{
    if (param0) {
        switch (param0->selectedTouchDial) {
        case 1:
            BoxTouchDial_HideLabels(param0);
            BoxTouchDial_ScrollBoxJumpIcons(param0);
            BoxTouchDial_StartScrollIcons(param0);
            break;
        case 2:
            BoxTouchDial_StartScrollMarkings(param0);
            break;
        }
    }
}

static void BoxTouchDial_ScrollBoxJump(BoxTouchDialGraphics *param0)
{
    int v0, v1, v2, v3;

    v3 = BoxApp_GetTouchDialScrollDelta(param0->boxApp);

    if (v3 > 0) {
        v0 = param0->markingsScrollOffset + (6 - 1);

        if (v0 >= 10) {
            v0 -= 10;
        }

        v1 = -1;

        param0->markingsScrollOffset -= v3;

        if (param0->markingsScrollOffset < 0) {
            param0->markingsScrollOffset += 10;
        }
    } else {
        v0 = param0->markingsScrollOffset;
        v1 = 1;

        param0->markingsScrollOffset -= v3;

        if (param0->markingsScrollOffset >= 10) {
            param0->markingsScrollOffset -= 10;
        }
    }
}

static void BoxTouchDial_ScrollMarkings(BoxTouchDialGraphics *param0)
{
    int v0 = BoxApp_GetTouchDialScrollDelta(param0->boxApp);
    param0->markingsScrollOffset += v0;

    if (param0->markingsScrollOffset < 0) {
        param0->markingsScrollOffset += 8;
    } else if (param0->markingsScrollOffset >= 8) {
        param0->markingsScrollOffset -= 8;
    }
}

BOOL BoxTouchDial_IsScrollDone(BoxTouchDialGraphics *param0)
{
    if (param0) {
        if (BoxTouchDial_IsTaskDone(param0)) {
            if (param0->selectedTouchDial == 1) {
                BoxTouchDial_DrawBoxNames(param0);
                BoxTouchDial_ScrollBoxJump(param0);
            } else {
                BoxTouchDial_ScrollMarkings(param0);
            }

            return 1;
        }

        return 0;
    } else {
        return 1;
    }
}

static void BoxTouchDial_CreateBoxJumpIcons(BoxTouchDialGraphics *param0)
{
    SpriteResourcesHeader v0;
    BoxSelectionPopup *v1;
    NNSG2dImageProxy v2;
    int v3, v4;

    v1 = BoxGraphics_GetBoxSelectionPopup(param0->boxGraphics);
    v4 = BoxApp_GetTouchDialOffset(param0->boxApp) + 3;

    if (v4 >= 18) {
        v4 -= 18;
    }

    for (v3 = 0; v3 < 10; v3++) {
        NNS_G2dInitImageProxy(&v2);
        BoxSelectionPopup_DrawBoxIcon(v1, v4, 192 + v3 * 32, NNS_G2D_VRAM_TYPE_2DSUB, &v2);
        BoxGraphics_InitSpriteResources(&v0, &v2, &(param0->paletteProxy), BoxSelectionPopup_GetCellBank(v1), NULL, 2);

        param0->iconSprites[v3] = BoxGraphics_CreateSprite(param0->spriteList, &v0, 16, 368, 48, NNS_G2D_VRAM_TYPE_2DSUB);

        GF_ASSERT(param0->iconSprites[v3] != NULL);

        v4--;

        if (v4 < 0) {
            v4 = 18 - 1;
        }
    }

    param0->markingsScrollOffset = 0;
}

static void BoxTouchDial_ScrollBoxJumpIcons(BoxTouchDialGraphics *param0)
{
    SpriteResourcesHeader v0;
    BoxSelectionPopup *v1;
    int v2, v3, v4, v5, v6, v7, v8;

    v1 = BoxGraphics_GetBoxSelectionPopup(param0->boxGraphics);
    v4 = BoxApp_GetTouchDialOffset(param0->boxApp);

    if (param0->boxApp->touchDialHelper.scrollDelta > 0) {
        v4 = (v4 - param0->boxApp->touchDialHelper.scrollDelta) + (3 + 1);

        if (v4 >= 18) {
            v4 -= 18;
        }

        v5 = 1;
        v8 = param0->markingsScrollOffset - 1;

        if (v8 < 0) {
            v8 += 10;
        }

        v3 = param0->boxApp->touchDialHelper.scrollDelta;
        v6 = 16;
        v7 = 368;
    } else {
        v4 = (v4 - param0->boxApp->touchDialHelper.scrollDelta) - (2 + 1);

        if (v4 < 0) {
            v4 += 18;
        }

        v5 = -1;
        v8 = param0->markingsScrollOffset + 6;

        if (v8 >= 10) {
            v8 -= 10;
        }

        v3 = param0->boxApp->touchDialHelper.scrollDelta * -1;
        v6 = 106;
        v7 = 592;
    }

    param0->scrollDelta = v3;

    for (v2 = 0; v2 < v3; v2++) {
        BoxSelectionPopup_DrawBoxIcon(v1, v4, 192 + v8 * 32, NNS_G2D_VRAM_TYPE_2DSUB, NULL);

        v4 += v5;

        if (v4 < 0) {
            v4 = 18 - 1;
        } else if (v4 >= 18) {
            v4 = 0;
        }

        v8 -= v5;

        if (v8 < 0) {
            v8 = (10 - 1);
        } else if (v8 >= 10) {
            v8 = 0;
        }
    }
}

static void BoxTouchDial_DeleteBoxJumpIcons(BoxTouchDialGraphics *param0)
{
    int v0;

    for (v0 = 0; v0 < 10; v0++) {
        if (param0->iconSprites[v0]) {
            Sprite_Delete(param0->iconSprites[v0]);
            param0->iconSprites[v0] = NULL;
        }
    }
}

static u32 BoxTouchDial_GetMarkingAnim(u32 param0, u32 param1)
{
    if (param0 == 0) {
        return (param1 == 0) ? 1 : 0;
    }

    if (param1 & (1 << (param0 - 1))) {
        return param0 * 2 + 1;
    } else {
        return param0 * 2;
    }
}

static void BoxTouchDial_CreateMarkingIcons(BoxTouchDialGraphics *param0)
{
    SpriteResourcesHeader v0;
    NNSG2dImageProxy v1;
    u32 v2;
    int v3;

    v2 = BoxApp_GetMonSpriteTransparencyMask(param0->boxApp);

    NNS_G2dInitImageProxy(&v1);
    Graphics_LoadImageMapping(18, 141, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DSUB, 192 * 0x20, 10, &v1);

    for (v3 = 0; v3 < 8; v3++) {
        BoxGraphics_InitSpriteResources(&v0, &v1, &(param0->paletteProxy), param0->formCellBankData, param0->formAnimBankData, 2);

        param0->markingSprites[v3] = BoxGraphics_CreateSprite(param0->spriteList, &v0, 240, 368, 48, NNS_G2D_VRAM_TYPE_2DSUB);
        GF_ASSERT(param0->markingSprites[v3] != NULL);

        Sprite_SetAnim(param0->markingSprites[v3], BoxTouchDial_GetMarkingAnim(v3, v2));
    }

    param0->markingsScrollOffset = BoxApp_GetMarkingsButtonsScrollOffset(param0->boxApp);
}

static void BoxTouchDial_DeleteMarkingIcons(BoxTouchDialGraphics *param0)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->markingSprites[v0]) {
            Sprite_Delete(param0->markingSprites[v0]);
            param0->markingSprites[v0] = NULL;
        }
    }
}

static void BoxTouchDial_IconAnimTaskForward(SysTask *param0, void *param1)
{
    BoxTouchDialIconAnim *v0 = (BoxTouchDialIconAnim *)param1;
    VecFx32 v1;

    if (v0->delayCount) {
        v0->delayCount--;
        return;
    }

    if (v0->stepCount) {
        u32 v2;

        v0->stepCount--;
        v0->position += v0->positionStep;
        v2 = v0->position >> FX32_SHIFT;
        v1.x = sBoxTouchDialIconPositions[v2].x << FX32_SHIFT;
        v1.y = sBoxTouchDialIconPositions[v2].y << FX32_SHIFT;
        v1.z = 0;
        Sprite_SetPosition(v0->sprite, &v1);
    } else {
        u32 v3 = v0->targetPosition >> FX32_SHIFT;

        v1.x = sBoxTouchDialIconPositions[v3].x << FX32_SHIFT;
        v1.y = sBoxTouchDialIconPositions[v3].y << FX32_SHIFT;
        v1.z = 0;

        Sprite_SetPosition(v0->sprite, &v1);
        BoxTouchDial_IconAnimDone(param0, v0);
    }
}

static void BoxTouchDial_IconAnimTaskBackward(SysTask *param0, void *param1)
{
    BoxTouchDialIconAnim *v0 = (BoxTouchDialIconAnim *)param1;
    VecFx32 v1;

    if (v0->delayCount) {
        v0->delayCount--;
        return;
    }

    if (v0->stepCount) {
        u32 v2;

        v0->stepCount--;
        v0->position += v0->positionStep;
        v2 = v0->position >> FX32_SHIFT;
        v1.x = (256 - sBoxTouchDialIconPositions[v2].x) << FX32_SHIFT;
        v1.y = sBoxTouchDialIconPositions[v2].y << FX32_SHIFT;
        v1.z = 0;

        Sprite_SetPosition(v0->sprite, &v1);
    } else {
        u32 v3 = v0->targetPosition >> FX32_SHIFT;

        v1.x = (256 - sBoxTouchDialIconPositions[v3].x) << FX32_SHIFT;
        v1.y = sBoxTouchDialIconPositions[v3].y << FX32_SHIFT;
        v1.z = 0;

        Sprite_SetPosition(v0->sprite, &v1);

        if (v0->hasChainAnim) {
            v0->stepCount = v0->chainStepCount;
            v0->position = v0->chainStartPosition;
            v0->positionStep = v0->chainStep;
            v0->targetPosition = v0->chainTargetPosition;
            v0->delayCount = v0->chainDelayCount;
            v0->hasChainAnim = 0;
        } else {
            BoxTouchDial_IconAnimDone(param0, v0);
        }
    }
}

static void BoxTouchDial_IconAnimDone(SysTask *param0, BoxTouchDialIconAnim *param1)
{
    BoxTouchDialAnimManager *v0 = param1->animManager;

    GF_ASSERT(v0->activeAnimCount);
    v0->activeAnimCount--;
    SysTask_Done(param0);
}

static void BoxTouchDial_StartIconAnim(BoxTouchDialAnimManager *param0, Sprite *param1, BoxTouchDialIconAnim *param2, u32 param3, u32 param4, u32 param5, u32 param6, BOOL param7)
{
    SysTaskFunc v0;

    GF_ASSERT(param1 != NULL);

    if (param6) {
        param6--;
    }

    param2->animManager = param0;
    param2->sprite = param1;
    param2->stepCount = param5;
    param2->delayCount = param6;

    v0 = (param7) ? BoxTouchDial_IconAnimTaskBackward : BoxTouchDial_IconAnimTaskForward;

    param2->position = sBoxTouchDialIconOffsets[param3] << FX32_SHIFT;
    param2->targetPosition = sBoxTouchDialIconOffsets[param4] << FX32_SHIFT;
    param2->positionStep = (param2->targetPosition - param2->position) / (s32)param5;
    param2->hasChainAnim = 0;

    if (BoxGraphics_StartVBlankTask(v0, param2, 0) != NULL) {
        param0->activeAnimCount++;
    }
}

static void BoxTouchDial_StartIconAnimChain(BoxTouchDialAnimManager *param0, BoxTouchDialIconAnim *param1, u32 param2, u32 param3, u32 param4)
{
    int v0;

    param1->hasChainAnim = 1;
    param1->chainDelayCount = param2;

    if (param2) {
        param1->chainDelayCount--;
    }

    v0 = param4 - param3;

    if (v0 < 0) {
        v0 *= -1;
    }

    v0 *= 6;

    param1->chainStepCount = v0;
    param1->chainStartPosition = sBoxTouchDialIconOffsets[param3] << FX32_SHIFT;
    param1->chainTargetPosition = sBoxTouchDialIconOffsets[param4] << FX32_SHIFT;
    param1->chainStep = (param1->chainTargetPosition - param1->chainStartPosition) / (s32)v0;
}

static void BoxTouchDial_ShowIconsTask(SysTask *param0, void *param1)
{
    BoxTouchDialAnimManager *v0 = (BoxTouchDialAnimManager *)param1;
    BoxTouchDialGraphics *v1 = v0->touchDialGraphics;

    switch (v0->state) {
    case 0: {
        int v2;

        v0->iconCount++;
        v2 = 6 - v0->iconCount;
        BoxTouchDial_StartIconAnim(v0, v1->iconSprites[v2], &v0->iconAnims[v2], 0, 7 - v0->iconCount, (v2 + 1) * 6, 0, 0);
        v0->stepTimer = 6 - (1 * 2);

        if (v0->iconCount >= 6) {
            v0->state = 2;
        } else {
            if (v0->stepTimer) {
                v0->state = 1;
            }
        }
    } break;
    case 1:
        v0->stepTimer -= (1 * 2);

        if (v0->stepTimer == 0) {
            v0->state = 0;
        }
        break;
    case 2:
        if (v0->activeAnimCount == 0) {
            v0->state++;
            BoxGraphics_DeferFree(v0, BoxTouchDial_ShowIconsDone, v1);
        }
        break;
    }
}

static void BoxTouchDial_ShowIconsDone(void *param0)
{
    BoxTouchDialGraphics *v0 = param0;
    BoxTouchDial_FinishTask(v0);
}

static void BoxTouchDial_StartShowIcons(BoxTouchDialGraphics *param0)
{
    BoxTouchDialAnimManager *v0;
    int v1;

    v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxTouchDialAnimManager));

    if (v0) {
        SysTask *v2;

        v0->touchDialGraphics = param0;
        v0->state = 0;
        v0->iconCount = 0;
        v0->activeAnimCount = 0;

        for (v1 = 0; v1 < 8; v1++) {
            v0->iconFlags[v1] = 0;
        }

        if (BoxTouchDial_StartTask(param0, BoxTouchDial_ShowIconsTask, v0) == NULL) {
            Heap_Free(v0);
        }
    }
}

static void BoxTouchDial_ScrollIconsTask(SysTask *param0, void *param1)
{
    BoxTouchDialAnimManager *v0 = (BoxTouchDialAnimManager *)param1;
    BoxTouchDialGraphics *v1 = v0->touchDialGraphics;

    switch (v0->state) {
    case 0: {
        int v2, v3, v4, v5, v6, v7, v8;

        if (v1->boxApp->touchDialHelper.scrollDelta > 0) {
            v4 = v1->markingsScrollOffset + 6 - 1;

            if (v4 >= 10) {
                v4 -= 10;
            }

            v5 = -1;
            v7 = 6;
            v8 = 7;
        } else {
            v4 = v1->markingsScrollOffset;
            v5 = 1;
            v7 = 1;
            v8 = 0;
        }

        for (v2 = 0; v2 < v1->scrollDelta; v2++) {
            BoxTouchDial_StartIconAnim(v0, v0->sprites[v4], &v0->iconAnims[v4], v7, v8, (v2 + 1) * 6, 0, 0);

            v7 += v5;
            v4 += v5;

            if (v4 >= 10) {
                v4 = 0;
            } else if (v4 < 0) {
                v4 = 10 - 1;
            }
        }

        v3 = (6 - v1->scrollDelta);

        for (v2 = 0; v2 < v3; v2++) {
            v8 = v7 - (v5 * v1->scrollDelta);

            BoxTouchDial_StartIconAnim(v0, v0->sprites[v4], &v0->iconAnims[v4], v7, v8, v1->scrollDelta * 6, 0, 0);

            v7 += v5;
            v4 += v5;

            if (v4 >= 10) {
                v4 = 0;
            } else if (v4 < 0) {
                v4 = 10 - 1;
            }
        }

        if (v1->boxApp->touchDialHelper.scrollDelta > 0) {
            v7 = 0;
            v8 = v1->scrollDelta;
        } else {
            v7 = 7;
            v8 = v7 - v1->scrollDelta;
        }

        v3 = v1->scrollDelta;

        for (v2 = 0; v2 < v3; v2++) {
            BoxTouchDial_StartIconAnim(v0, v0->sprites[v4], &v0->iconAnims[v4], v7, v8, (v1->scrollDelta - v2) * 6, (v2 + 1) * 6, 0);

            v8 += v5;
            v4 += v5;

            if (v4 >= 10) {
                v4 -= 10;
            } else if (v4 < 0) {
                v4 += 10;
            }
        }

        v0->state++;
    } break;
    case 1:
        if (v0->activeAnimCount == 0) {
            v0->state++;
            BoxGraphics_DeferFree(v0, BoxTouchDial_ShowIconsDone, v1);
        }
        break;
    }
}

static void BoxTouchDial_StartScrollIcons(BoxTouchDialGraphics *param0)
{
    BoxTouchDialAnimManager *v0;
    int v1;

    v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxTouchDialAnimManager));

    if (v0) {
        SysTask *v2;

        v0->touchDialGraphics = param0;
        v0->sprites = param0->iconSprites;
        v0->state = 0;
        v0->iconCount = 0;
        v0->activeAnimCount = 0;

        for (v1 = 0; v1 < 10; v1++) {
            v0->iconFlags[v1] = 0;
        }

        if (BoxTouchDial_StartTask(param0, BoxTouchDial_ScrollIconsTask, v0) == NULL) {
            Heap_Free(v0);
        }
    }
}

static void BoxTouchDial_ShowMarkingsTask(SysTask *param0, void *param1)
{
    BoxTouchDialAnimManager *v0 = (BoxTouchDialAnimManager *)param1;
    BoxTouchDialGraphics *v1 = v0->touchDialGraphics;

    switch (v0->state) {
    case 0: {
        int v2, v3, v4;

        v4 = 6;
        v3 = v1->markingsScrollOffset;

        for (v2 = 0; v2 < 6; v2++) {
            BoxTouchDial_StartIconAnim(v0, v1->markingSprites[v3], &(v0->iconAnims[v3]), 0, v4, 6 * v4, 6 * v2, 1);

            v4--;

            if (++v3 >= 8) {
                v3 = 0;
            }
        }

        v0->state++;
    } break;
    case 1:
        if (v0->activeAnimCount == 0) {
            v0->state++;
            BoxGraphics_DeferFree(v0, BoxTouchDial_ShowIconsDone, v1);
        }
        break;
    }
}

static void BoxTouchDial_StartShowMarkings(BoxTouchDialGraphics *param0)
{
    BoxTouchDialAnimManager *v0;
    int v1;

    v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxTouchDialAnimManager));

    if (v0) {
        SysTask *v2;

        v0->touchDialGraphics = param0;
        v0->state = 0;
        v0->iconCount = 0;
        v0->activeAnimCount = 0;

        for (v1 = 0; v1 < 8; v1++) {
            v0->iconFlags[v1] = 0;
        }

        if (BoxTouchDial_StartTask(param0, BoxTouchDial_ShowMarkingsTask, v0) == NULL) {
            Heap_Free(v0);
        }
    }
}

static void BoxTouchDial_ScrollMarkingsTask(SysTask *param0, void *param1)
{
    BoxTouchDialAnimManager *v0 = (BoxTouchDialAnimManager *)param1;
    BoxTouchDialGraphics *v1 = v0->touchDialGraphics;

    switch (v0->state) {
    case 0: {
        int v2, v3, v4, v5, v6, v7, v8, v9, v10;

        v3 = BoxApp_GetTouchDialScrollDelta(v1->boxApp);
        v2 = v1->markingsScrollOffset;

        if (v3 < 0) {
            v2 += (6 - 1);

            if (v2 >= 8) {
                v2 -= 8;
            }

            v4 = -1;
            v9 = -v3;
            v6 = 1;
            v7 = 0;
        } else {
            v4 = 1;
            v9 = v3;
            v6 = 7 - 1;
            v7 = 7;
        }

        v8 = 6 + v9;

        for (v5 = 0; v5 < v9; v5++) {
            BoxTouchDial_StartIconAnim(v0, v1->markingSprites[v2], &(v0->iconAnims[v2]), v6, v7, 6 * (v5 + 1), 0, 1);

            v6 -= v4;
            v2 += v4;

            if (v2 < 0) {
                v2 += 8;
            } else if (v2 >= 8) {
                v2 -= 8;
            }
        }

        v10 = 0;

        for (; v5 < 8; v5++) {
            v7 -= v4;

            BoxTouchDial_StartIconAnim(v0, v1->markingSprites[v2], &(v0->iconAnims[v2]), v6, v7, 6 * (v9), v10, 1);

            if ((v6 != 0) && (v6 != 7)) {
                v6 -= v4;
            } else {
                v10 += 6;
            }

            v2 += v4;

            if (v2 < 0) {
                v2 += 8;
            } else if (v2 >= 8) {
                v2 -= 8;
            }
        }

        if (v3 < 0) {
            v6 = 7;
            v7 = v6 - (v9 - 2);
        } else {
            v6 = 0;
            v7 = v6 + (v9 - 2);
        }

        for (; v5 < v8; v5++) {
            BoxTouchDial_StartIconAnimChain(v0, &(v0->iconAnims[v2]), 6, v6, v7);

            v7 -= v4;
            v2 += v4;

            if (v2 < 0) {
                v2 += 8;
            } else if (v2 >= 8) {
                v2 -= 8;
            }
        }

        v0->state++;
    } break;
    case 1:
        if (v0->activeAnimCount == 0) {
            v0->state++;
            BoxGraphics_DeferFree(v0, BoxTouchDial_ShowIconsDone, v1);
        }
        break;
    }
}

static void BoxTouchDial_StartScrollMarkings(BoxTouchDialGraphics *param0)
{
    BoxTouchDialAnimManager *v0;
    int v1;

    v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxTouchDialAnimManager));

    if (v0) {
        SysTask *v2;

        v0->touchDialGraphics = param0;
        v0->state = 0;
        v0->iconCount = 0;
        v0->activeAnimCount = 0;

        for (v1 = 0; v1 < 8; v1++) {
            v0->iconFlags[v1] = 0;
        }

        if (BoxTouchDial_StartTask(param0, BoxTouchDial_ScrollMarkingsTask, v0) == NULL) {
            Heap_Free(v0);
        }
    }
}

void BoxTouchDial_UpdateMarkingIcons(BoxTouchDialGraphics *param0)
{
    if (param0) {
        if (param0->markingSprites[0] != NULL) {
            int v0;
            u32 v1 = BoxApp_GetMonSpriteTransparencyMask(param0->boxApp);

            for (v0 = 0; v0 < 8; v0++) {
                Sprite_SetAnim(param0->markingSprites[v0], BoxTouchDial_GetMarkingAnim(v0, v1));
            }
        }
    }
}

static void BoxTouchDial_HideLabels(BoxTouchDialGraphics *param0)
{
    Bg_ToggleLayer(BG_LAYER_SUB_0, 0);
}

static void BoxTouchDial_ShowLabels(BoxTouchDialGraphics *param0)
{
    G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG0, GX_BLEND_ALL, 14, 2);
    Bg_ToggleLayer(BG_LAYER_SUB_0, 1);
}

static void BoxTouchDial_DrawBoxNames(BoxTouchDialGraphics *param0)
{
    static const struct {
        s16 x;
        s16 y;
    } v0[] = {
        { 36, 4 },
        { 36, 36 },
        { 50, 69 },
        { 92, 92 },
        { 114, 124 },
        { 124, 156 },
    };
    int v1, v2;

    v2 = BoxApp_GetTouchDialOffset(param0->boxApp) + 3;

    if (v2 >= MAX_PC_BOXES) {
        v2 -= MAX_PC_BOXES;
    }

    for (v1 = 0; v1 < NELEMS(v0); v1++) {
        PCBoxes_BufferBoxName(param0->boxApp->pcBoxes, v2, param0->boxNameString);
        Window_FillRectWithColor(&param0->boxNameWindow, 0, v0[v1].x, v0[v1].y, 104, 17);
        Text_AddPrinterWithParamsAndColor(&param0->boxNameWindow, FONT_SYSTEM, param0->boxNameString, v0[v1].x + 4, v0[v1].y + 2, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

        if (--v2 < 0) {
            v2 = MAX_PC_BOXES - 1;
        }
    }

    Window_LoadTiles(&param0->boxNameWindow);
    BoxTouchDial_ShowLabels(param0);
}
