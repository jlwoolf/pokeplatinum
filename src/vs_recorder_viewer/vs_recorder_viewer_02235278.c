#include "vs_recorder_viewer/vs_recorder_viewer_02235278.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_vs_recorder_state.h"

#include "vs_recorder_viewer/vs_recorder_viewer.h"
#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02234A10.h"
#include "vs_recorder_viewer/vs_recorder_viewer_const_funcptr_tables.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022354A4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02235580.h"

#include "gx_layers.h"
#include "heap.h"
#include "palette.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "touch_screen.h"
#include "font_oam.h"
#include "vs_recorder_ring.h"

static BOOL VsRecorderViewerSlideShow_HandleInput(VsRecorderState *param0);
static BOOL VsRecorderViewerSlideShow_Unused(VsRecorderState *param0);
static BOOL VsRecorderViewerSlideShow_FadeOut(VsRecorderState *param0);
static BOOL VsRecorderViewerSlideShow_HandleMenuExit(VsRecorderState *param0);
static BOOL VsRecorderViewerSlideShow_SlideEntriesIn(VsRecorderState *param0);
static BOOL VsRecorderViewerSlideShow_SlideEntriesOut(VsRecorderState *param0);
static BOOL VsRecorderViewerSlideShow_SelectPrevious(VsRecorderState *param0);
static BOOL VsRecorderViewerSlideShow_SelectNext(VsRecorderState *param0);
static int VsRecorderViewerSlideShow_CheckEdgeTap(void);

static BOOL VsRecorderViewerSlideShow_HandleInput(VsRecorderState *param0)
{
    if (TouchScreen_Tapped() && (param0->touchHandled == 0)) {
        VsRecorderViewerList_CloseSubMessage(param0);
    }

    if (param0->mode == 0) {
        int v0 = VsRecorderViewerSlideShow_CheckEdgeTap();

        switch (v0) {
        case 1:
            Sound_PlayEffect(SEQ_SE_PL_BREC57_sseq);
            VsRecorderViewerMain_SetState(param0, 7);
            return 0;
        case 2:
            Sound_PlayEffect(SEQ_SE_PL_BREC57_sseq);
            VsRecorderViewerMain_SetState(param0, 8);
            return 0;
        default:
            break;
        }
    }

    VsRecorderViewerMain_HandleTouchAction(param0);

    return 0;
}

static int VsRecorderViewerSlideShow_CheckEdgeTap(void)
{
    static const TouchScreenHitTable v0[] = {
        { 0, 192, 0, 8 },
        { 0, 192, 248, 256 },
    };

    if (TouchScreen_LocationHeld(&v0[0])) {
        return 1;
    }

    if (TouchScreen_LocationHeld(&v0[1])) {
        return 2;
    }

    return 0;
}

static BOOL VsRecorderViewerSlideShow_Unused(VsRecorderState *param0)
{
    BOOL v0 = 0;

    GF_ASSERT(FALSE);

    param0->menuContext.returnToMainMenu = 1;
    VsRecorderViewerMain_SetState(param0, 0);

    return VsRecorderViewerSlideShow_HandleInput(param0);
}

static BOOL VsRecorderViewerSlideShow_FadeOut(VsRecorderState *param0)
{
    switch (param0->subState) {
    case 0:
        param0->menuContext.fadeValue = 0;
        param0->timer = 0;
        VsRecorderRing_SetVisible(param0->ring, 0);
        VsRecorderRing_SetVisible(param0->backgroundRing, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        param0->subState++;
        break;
    case 1:
        if (param0->timer != 16) {
            param0->timer += 2;
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xFFFE, param0->timer, VsRecorderViewerList_GetThemeColorB(param0));
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_BG, 0xFFFF, param0->timer, VsRecorderViewerList_GetThemeColorB(param0));
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0x3FFE, param0->timer, VsRecorderViewerList_GetThemeColorB(param0));
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0xFFFF, param0->timer, VsRecorderViewerList_GetThemeColorB(param0));
        } else {
            param0->timer = 16;
            param0->subState++;
        }

        break;

    case 2:
        if (param0->timer != 0) {
            param0->timer -= 4;
        } else {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_102);
            param0->subState++;
        }
        break;
    default:
        if (IsScreenFadeDone() == TRUE) {
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            return 1;
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerSlideShow_HandleMenuExit(VsRecorderState *param0)
{
    BOOL v0 = VsRecorderViewerEntry_AnimateEntries(param0);

    if (v0) {
        if (param0->menuContext.returnToMainMenu == 1) {
            VsRecorderRing_SetVisible(param0->ring, 0);
            VsRecorderViewerMain_SetState(param0, 0);
        } else {
            VsRecorderViewerMain_SetState(param0, 1);
        }
    }

    return 0;
}

static BOOL VsRecorderViewerSlideShow_HandleMenuAction(VsRecorderState *param0)
{
    BOOL v0;

    switch (param0->currentMenu[param0->menu.selectedIndex].action) {
    default:
        v0 = 1;
        break;
    }

    if (v0) {
        if (param0->menuContext.returnToMainMenu == 1) {
            VsRecorderRing_SetVisible(param0->ring, 0);
            VsRecorderViewerMain_SetState(param0, 0);
        } else {
            VsRecorderViewerMain_SetState(param0, 1);
        }
    }

    return 0;
}

void VsRecorderViewerSlideShow_SlideAnimTask(SysTask *param0, void *param1)
{
    VsRecorderViewerSlideShowSlideAnim *v0 = param1;

    switch (v0->state) {
    case 0:
        v0->stepX = (v0->targetX - v0->startX) / v0->stepCount;
        v0->stepY = (v0->targetY - v0->startY) / v0->stepCount;
        v0->state++;
    case 1: {
        s16 v1, v2;

        VsRecorderViewerMenu_GetSpritePositionWithOffset(v0->sprite, &v1, &v2);

        v0->stepCount--;

        if (v0->stepCount == 0) {
            v1 = v0->targetX;
            v2 = v0->targetY;
            v0->state++;
        } else {
            v1 += v0->stepX;
            v2 += v0->stepY;
        }

        if (v0->ring) {
            VsRecorderRing_SetTargetPosition(v0->ring, v1 + (15 + 1), v2);
            if (v0->stepCount == 2) {
                *(v0->ringDone) = 1;
            }
        }

        VsRecorderViewerMenu_SetSpritePositionWithOffset(v0->sprite, v1, v2);
        FontOAM_SetXY(v0->fontOAM, 36, -8);

        *(v0->done) = 1;
    } break;
    default:
        Heap_Free(v0);
        SysTask_Done(param0);
        break;
    }
}

static BOOL VsRecorderViewerSlideShow_SlideEntriesIn(VsRecorderState *param0)
{
    VsRecorderViewerSlideShowTransition *v0;

    switch (param0->subState) {
    case 0: {
        int v1;
        VsRecorderViewerSlideShowSlideAnim *v2;
        VsRecorderViewerSlideShowTransition *v3 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerSlideShowTransition));

        MI_CpuFill8(v3, 0, sizeof(VsRecorderViewerSlideShowTransition));
        param0->viewerData = v3;
        v3->mainDone = 0;

        for (v1 = 0; v1 < param0->menu.subEntryCount; v1++) {
            v2 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerSlideShowSlideAnim));
            memset(v2, 0, sizeof(VsRecorderViewerSlideShowSlideAnim));
            VsRecorderViewerMenu_GetSpritePositionWithOffset(param0->menu.subEntries[v1].sprite, &v2->startX, &v2->startY);

            v2->sprite = param0->menu.subEntries[v1].sprite;
            v2->fontOAM = param0->menu.subEntries[v1].fontOAM;
            v2->done = &v3->slideDone;
            v2->ringDone = &v3->ringDone;

            if (v1 == param0->menu.selectedIndex) {
                v2->ring = param0->ring;
                v2->targetX = v2->startX;
                v2->targetY = -48;
                v2->stepCount = 8;
            } else {
                v2->ring = NULL;
                v2->targetX = v2->startX;
                v2->targetY = (25 + (36 * 5) + (16 * (5 - (param0->menu.subEntryCount))));

                if (v2->targetY >= (25 + (36 * 5) + (16 * (4 - 3)))) {
                    v2->targetY = (25 + (36 * 5) + (16 * (4 - 3)));
                }

                v2->stepCount = 8;
            }

            SysTask_Start(VsRecorderViewerSlideShow_SlideAnimTask, v2, 8192);
        }

        v3->fadeValue = 0;
    }
        param0->subState++;
        break;
    case 1:
        v0 = param0->viewerData;

        if (v0->fadeValue != 16) {
            v0->fadeValue += 2;
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->fadeValue, param0->menuContext.themeColor);
        }

        {
            int v4;
            VsRecorderViewerSlideShowSlideAnim *v5;

            if (v0->ringDone == 1) {
                v4 = 0;

                if (v0->mainDone == 0) {
                    v0->mainDone = 1;

                    do {
                        v5 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerSlideShowSlideAnim));
                        memset(v5, 0, sizeof(VsRecorderViewerSlideShowSlideAnim));
                        VsRecorderViewerMenu_GetSpritePositionWithOffset(param0->menu.mainEntries[v4].sprite, &v5->startX, &v5->startY);

                        v5->sprite = param0->menu.mainEntries[v4].sprite;
                        v5->fontOAM = param0->menu.mainEntries[v4].fontOAM;
                        v5->done = &v0->slideDone;
                        v5->ring = NULL;
                        v5->targetX = v5->startX;

                        if (param0->menu.mainEntryCount == v4) {
                            v5->targetX = v5->startX;
                            v5->targetY = (25 + (36 * (5 - 1)));

                            ManagedSprite_SetAnim(param0->menu.mainEntries[v4].sprite, param0->currentMenu[param0->menu.selectedIndex].spriteAnimID);
                            VsRecorderViewerMenu_RenderEntryLabel(param0, &param0->menu.mainEntries[param0->menu.mainEntryCount], param0->currentMenu[param0->menu.selectedIndex].labelMessageID, &param0->currentMenu[param0->menu.selectedIndex]);
                            FontOAM_SetDrawFlag(param0->menu.mainEntries[param0->menu.mainEntryCount].fontOAM, 1);
                            ManagedSprite_SetDrawFlag(param0->menu.mainEntries[v4].sprite, 1);
                        } else {
                            v5->targetX = v5->startX - 4;
                            v5->targetY = (16 * (param0->menu.mainEntryCount - v4)) + (25 + (36 * (5 - (param0->menu.mainEntryCount - v4) - 1)));
                        }

                        v5->stepCount = 4;
                        SysTask_Start(VsRecorderViewerSlideShow_SlideAnimTask, v5, 8192);
                        v4++;
                    } while (v4 <= param0->menu.mainEntryCount);
                }

                v0->slideDone = v0->ringDone;
                v0->ringDone = 0;
            }

            for (v4 = 0; v4 < param0->menu.mainEntryCount; v4++) {
                if (v4 == param0->menu.mainEntryCount) {
                    ManagedSprite_SetExplicitPaletteOffset(param0->menu.mainEntries[v4].sprite, (2 - 1));
                } else {
                    ManagedSprite_SetExplicitPaletteOffset(param0->menu.mainEntries[v4].sprite, (3 - 1));
                }
            }
        }

        if (v0->slideDone == 0) {
            param0->subState++;
        }

        v0->slideDone = 0;
        break;
    case 2: {
        if (param0->currentMenu[param0->menu.selectedIndex].children == NULL) {
            VsRecorderViewerMain_ExecuteMenuAction(param0);
        } else {
            VsRecorderViewerMain_SetState(param0, 5);
        }

        VsRecorderViewerMain_PushMenu(param0);
        v0 = param0->viewerData;
        Heap_Free(v0);
    } break;
    default:
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerSlideShow_SlideEntriesOut(VsRecorderState *param0)
{
    VsRecorderViewerSlideShowTransition *v0;

    switch (param0->subState) {
    case 0: {
        int v1;
        VsRecorderViewerSlideShowSlideAnim *v2;

        v0 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerSlideShowTransition));
        MI_CpuFill8(v0, 0, sizeof(VsRecorderViewerSlideShowTransition));
        param0->viewerData = v0;
        v1 = 0;

        do {
            v2 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerSlideShowSlideAnim));

            memset(v2, 0, sizeof(VsRecorderViewerSlideShowSlideAnim));
            VsRecorderViewerMenu_GetSpritePositionWithOffset(param0->menu.mainEntries[v1].sprite, &v2->startX, &v2->startY);

            v2->sprite = param0->menu.mainEntries[v1].sprite;
            v2->fontOAM = param0->menu.mainEntries[v1].fontOAM;
            v2->done = &v0->slideDone;
            v2->ringDone = &v0->ringDone;
            v2->ring = NULL;
            v2->targetX = v2->startX;

            if (param0->menu.mainEntryCount - 1 == v1) {
                v2->ring = param0->ring;
                v2->targetX = v2->startX;
                v2->targetY = (25 + (36 * (5 - 1))) + 48;
            } else {
                v2->targetX = v2->startX + 4;
                v2->targetY = (25 + (36 * (5 - (param0->menu.mainEntryCount - v1)))) + (16 * (param0->menu.mainEntryCount - v1)) + 4;
            }

            v2->stepCount = 4;
            SysTask_Start(VsRecorderViewerSlideShow_SlideAnimTask, v2, 8192);
            v1++;
        } while (v1 <= (param0->menu.mainEntryCount - 1));
    }
        param0->subState++;
        break;
    case 1:
        v0 = param0->viewerData;
        {
            int v3;
            VsRecorderViewerSlideShowSlideAnim *v4;

            if (v0->ringDone == 1) {
                for (v3 = 0; v3 < param0->menu.subEntryCount; v3++) {
                    v4 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerSlideShowSlideAnim));
                    memset(v4, 0, sizeof(VsRecorderViewerSlideShowSlideAnim));
                    VsRecorderViewerMenu_GetSpritePositionWithOffset(param0->menu.subEntries[v3].sprite, &v4->startX, &v4->startY);

                    v4->sprite = param0->menu.subEntries[v3].sprite;
                    v4->fontOAM = param0->menu.subEntries[v3].fontOAM;
                    v4->done = &v0->slideDone;
                    v4->ringDone = &v0->ringDone;
                    v4->ring = NULL;
                    v4->targetX = v4->startX;
                    v4->targetY = (25 + (36 * 5) + (16 * (5 - (param0->menu.subEntryCount))));

                    if (v4->targetY >= (25 + (36 * 5) + (16 * (4 - 3)))) {
                        v4->targetY = (25 + (36 * 5) + (16 * (4 - 3)));
                    }

                    v4->stepCount = 8;
                    SysTask_Start(VsRecorderViewerSlideShow_SlideAnimTask, v4, 8192);
                }

                v0->fadeValue = 0;
                param0->subState++;
                param0->menu.mainEntryCount--;

                for (v3 = 0; v3 < param0->menu.mainEntryCount; v3++) {
                    if (v3 == param0->menu.mainEntryCount - 1) {
                        ManagedSprite_SetExplicitPaletteOffset(param0->menu.mainEntries[v3].sprite, (2 - 1));
                    } else {
                        ManagedSprite_SetExplicitPaletteOffset(param0->menu.mainEntries[v3].sprite, (3 - 1));
                    }
                }
            }
        }
        break;

    case 2:
        v0 = param0->viewerData;

        if (v0->fadeValue != 16) {
            v0->fadeValue += 2;
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->fadeValue, param0->menuContext.themeColor);
        }

        if (v0->slideDone == 0) {
            param0->subState++;
        }

        v0->slideDone = 0;
        break;
    default: {
        BOOL v5;

        v5 = VsRecorderViewerMain_PopMenu(param0);
        v0 = param0->viewerData;

        Heap_Free(v0);
        VsRecorderViewerMain_SetState(param0, 5);
    } break;
    }

    return 0;
}

// clang-format off
BOOL(*const sVsRecorderViewerSlideShowStateTable[])(VsRecorderState * wk) = {
    VsRecorderViewerSlideShow_HandleInput,
    VsRecorderViewerSlideShow_Unused,
    VsRecorderViewerSlideShow_FadeOut,
    VsRecorderViewerSlideShow_SlideEntriesIn,
    VsRecorderViewerSlideShow_SlideEntriesOut,
    VsRecorderViewerSlideShow_HandleMenuExit,
    VsRecorderViewerSlideShow_HandleMenuAction,
    VsRecorderViewerSlideShow_SelectPrevious,
    VsRecorderViewerSlideShow_SelectNext,
};
// clang-format on

static BOOL VsRecorderViewerSlideShow_SelectPrevious(VsRecorderState *param0)
{
    switch (param0->subState) {
    case 0:
        param0->menuContext.fadeValue = 0;

        if (param0->menuContext.theme > 0) {
            param0->menuContext.theme--;
        } else {
            param0->menuContext.theme = 7 - 1;
        }

        param0->menuContext.themeColor = VsRecorderViewerList_GetThemeColorA(param0);
        param0->subState++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepFadeValue(&param0->menuContext.fadeValue, 1)) {
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_BG, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        break;
    case 2:
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 0);
        VsRecorderViewerList_LoadThemeGraphics(param0, param0->menuContext.theme);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_BG, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        param0->subState++;
        break;
    case 3:
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
        param0->subState++;
        break;
    case 4:
        if (VsRecorderViewerMenu_StepFadeValue(&param0->menuContext.fadeValue, 0)) {
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_BG, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 0);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerSlideShow_SelectNext(VsRecorderState *param0)
{
    switch (param0->subState) {
    case 0:
        param0->menuContext.fadeValue = 0;
        param0->menuContext.theme++;
        param0->menuContext.theme %= 7;
        param0->menuContext.themeColor = VsRecorderViewerList_GetThemeColorA(param0);
        param0->subState++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepFadeValue(&param0->menuContext.fadeValue, 1)) {
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_BG, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        break;
    case 2:
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 0);
        VsRecorderViewerList_LoadThemeGraphics(param0, param0->menuContext.theme);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_BG, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        param0->subState++;
        break;
    case 3:
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
        param0->subState++;
        break;
    case 4:
        if (VsRecorderViewerMenu_StepFadeValue(&param0->menuContext.fadeValue, 0)) {
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_BG, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0xFFFF, param0->menuContext.fadeValue, param0->menuContext.themeColor);
        break;
    default:
        param0->menuContext.fadeValue = 0;
        VsRecorderViewerMain_SetState(param0, 0);
        break;
    }

    return 0;
}
