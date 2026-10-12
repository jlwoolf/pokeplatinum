#ifndef POKEPLATINUM_ENCOUNTER_EFFECT_H
#define POKEPLATINUM_ENCOUNTER_EFFECT_H

#include <nitro/fx/fx.h>

#include "field/field_system_decl.h"
#include "fieldmap/encounter_effect.h"
#include "fieldmap/hblank_system.h"
#include "fieldmap/linear_interpolation_task_fx32.h"
#include "fieldmap/linear_interpolation_task_s32.h"
#include "fieldmap/quadratic_interpolation_task_fx32.h"
#include "fieldmap/struct_brightness_fade_task.h"
#include "fieldmap/struct_encounter_sprite_renderer.h"
#include "fieldmap/struct_encounter_sprite_resources.h"

#include "bg_window.h"
#include "enc_effects.h"
#include "field_battle_data_transfer.h"
#include "narc.h"
#include "sprite.h"
#include "sys_task_manager.h"

typedef struct EncounterEffect {
    int state;
    BOOL effectComplete;
    int unk_08;
    void *param;
    FieldSystem *fieldSystem;
    BOOL *done;
    BOOL hBlankFlag;
    BOOL unk_1C;
    NARC *narc;
} EncounterEffect;

typedef struct EncounterTextFade {
    LinearInterpolationTaskS32 unk_00;
    LinearInterpolationTaskS32 unk_14;
    Window *unk_28;
    u8 unk_2C;
    u8 unk_2D;
    u8 unk_2E;
    u8 unk_2F;
} EncounterTextFade;

typedef struct EncounterTextChar {
    LinearInterpolationTaskS32 unk_00;
    LinearInterpolationTaskS32 unk_14;
    Window *unk_28;
    u8 unk_2C;
    u8 unk_2D;
    u8 unk_2E;
    u8 unk_2F;
} EncounterTextChar;

typedef struct EncounterTextScroll {
    Window *unk_00;
    EncounterTextChar *unk_04[48];
    u8 unk_C4;
    u8 unk_C5;
    u8 unk_C6;
    u8 unk_C7;
    s8 unk_C8;
    u8 unk_C9;
    u8 unk_CA;
    u8 unk_CB[1];
} EncounterTextScroll;

typedef struct EncounterTextLine {
    Window *unk_00;
    LinearInterpolationTaskS32 unk_04;
    u8 unk_18;
    u8 unk_19;
    u8 unk_1A[2];
} EncounterTextLine;

typedef struct EncounterTextLines {
    EncounterTextLine *unk_00[8];
    u8 unk_20;
    u8 unk_21[3];
} EncounterTextLines;

typedef struct ScreenSplitEffect {
    QuadraticInterpolationTaskFX32 xInterpolationTask;
    QuadraticInterpolationTaskFX32 yInterpolationTask;
    u32 splitHeight;
    u32 state;
    HBlankSystem *hBlankSystem;
    HBlankTask *hBlankTask;
    SysTask *vBlankTask;
    BOOL *done;
} ScreenSplitEffect;

typedef struct ScreenSliceEffect {
    QuadraticInterpolationTaskFX32 interpolationTask;
    u32 pixelsPerSlice;
    u32 state;
    HBlankSystem *hBlankSystem;
    HBlankTask *hBlankTask;
    SysTask *vBlankTask;
    BOOL *done;
} ScreenSliceEffect;

typedef struct EncounterScreenWave {
    LinearInterpolationTaskS32 unk_00;
    u32 unk_14;
    u8 unk_18[192];
    HBlankSystem *unk_D8;
    HBlankTask *unk_DC;
    SysTask *unk_E0;
    BOOL *unk_E4;
} EncounterScreenWave;

enum Screen {
    SCREEN_TOP = 1,
    SCREEN_BOTTOM,
};

void EncounterEffect_Start(enum EncEffectCutIn effect, FieldSystem *fieldSystem, BOOL *param2);
void EncounterEffect_Finish(EncounterEffect *encEffect, SysTask *effectTask);
void EncounterEffect_Flash(enum Screen screen, u32 screenFlashColor, u32 otherScreenFlashColor, BOOL *done, u32 numFlashes);
BOOL EncounterEffect_GetHBlankFlag(EncounterEffect *encEffect);
void LinearInterpolationTaskS32_Init(LinearInterpolationTaskS32 *task, int start, int end, int numSteps);
BOOL LinearInterpolationTaskS32_Update(LinearInterpolationTaskS32 *task);
void LinearInterpolationTaskFX32_Init(LinearInterpolationTaskFX32 *task, fx32 startValue, fx32 endValue, int numSteps);
BOOL LinearInterpolationTaskFX32_Update(LinearInterpolationTaskFX32 *task);
void QuadraticInterpolationTaskFX32_Init(QuadraticInterpolationTaskFX32 *task, fx32 startValue, fx32 endValue, fx32 initialRate, int numSteps);
BOOL QuadraticInterpolationTaskFX32_Update(QuadraticInterpolationTaskFX32 *task);
void BrightnessFadeTask_ApplyBrightnessToScreen(enum Screen screen, int brightness);
void BrightnessFadeTask_Init(BrightnessFadeTask *task, s32 startValue, s32 endValue, s32 screen, s32 sync);
BOOL BrightnessFadeTask_Update(BrightnessFadeTask *task);
ScreenSliceEffect *ScreenSliceEffect_New(void);
void ScreenSliceEffect_Delete(ScreenSliceEffect *efx);
void EncounterEffect_ScreenSlice(EncounterEffect *encEffect, ScreenSliceEffect *screenSliceEfx, u8 pixelsPerSlice, u32 numSteps, fx32 startX, fx32 endX, fx32 initialSpeed);
void ScreenSliceEffect_Modify(EncounterEffect *encEffect, ScreenSliceEffect *screenSliceEfx, u8 pixelsPerSlice, u32 numSteps, fx32 startX, fx32 endX, fx32 initialSpeed);
ScreenSplitEffect *ScreenSplitEffect_New(void);
void ScreenSplitEffect_Delete(ScreenSplitEffect *screenSplitEfx);
void EncounterEffect_ScreenSplit(EncounterEffect *encEffect, ScreenSplitEffect *screenSplitEfx, u32 numSteps, fx32 initialSpeedX, fx32 initialSpeedY);
void FieldMap_021DE3D0(NARC *param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, BgConfig *param6, u32 param7);
void EncounterEffect_InitSpriteCollection(EncounterSpriteRenderer *param0, int param1, int param2);
void FieldMap_021DE4AC(EncounterSpriteRenderer *param0);
void FieldMap_021DE4CC(NARC *param0, EncounterSpriteRenderer *param1, EncounterSpriteResources *param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8);
void FieldMap_021DE5A4(EncounterSpriteRenderer *param0, EncounterSpriteResources *param1);
void EncounterEffect_BlendTrainerSpritePltt(Sprite *mugshotSprite, enum HeapID heapID, enum TrainerClass trainerClass, u8 fraction, u16 target);
Sprite *FieldMap_021DE62C(EncounterSpriteRenderer *param0, EncounterSpriteResources *param1, fx32 param2, fx32 param3, fx32 param4, int param5);
VecFx32 VecFx32_FromXYZ(fx32 param0, fx32 param1, fx32 param2);
EncounterTextFade *FieldMap_021DE6A4(u32 heapID);
void FieldMap_021DE6BC(EncounterTextFade *param0);
void FieldMap_021DE6C4(EncounterTextFade *param0, int param1, int param2, int param3, int param4, int param5, Window *param6, u32 param7, u32 param8, u8 param9);
BOOL FieldMap_021DE71C(EncounterTextFade *param0);
void FieldMap_021DE79C(EncounterTextChar *param0);
void FieldMap_021DE7A4(EncounterTextChar *param0, int param1, int param2, int param3, int param4, int param5, Window *param6, u32 param7, u32 param8, u8 param9);
BOOL FieldMap_021DE7FC(EncounterTextChar *param0);
EncounterTextScroll *FieldMap_021DE8F8(u32 heapID);
void FieldMap_021DE928(EncounterTextScroll *param0);
void FieldMap_021DE948(EncounterTextScroll *param0, u8 param1, u8 param2, Window *param3, u8 param4);
BOOL FieldMap_021DE988(EncounterTextScroll *param0);
void FieldMap_021DEA98(EncounterTextLine *param0);
void FieldMap_021DEAA0(EncounterTextLine *param0, u8 param1, u16 param2, u16 param3, Window *param4, u8 param5);
BOOL FieldMap_021DEAC8(EncounterTextLine *param0);
EncounterTextLines *FieldMap_021DEBEC(u32 heapID);
void FieldMap_021DEC18(EncounterTextLines *param0);
void FieldMap_021DEC38(EncounterTextLines *param0, u8 param1, Window *param2, u8 param3);
BOOL FieldMap_021DECB8(EncounterTextLines *param0);
EncounterScreenWave *FieldMap_021DECEC(void);
void FieldMap_021DED04(EncounterScreenWave *param0);
void FieldMap_021DED20(EncounterEffect *param0, EncounterScreenWave *param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6);
u32 CutInEffects_ForBattle(const FieldBattleDTO *param0);
void FieldMap_021DEF8C(int *param0);
void FieldMap_021DEFA0(FieldSystem *fieldSystem);
void FieldMap_021DF038(void);
BOOL FieldMap_021DF054(void);
void FieldMap_021DF070(void);
void FieldMap_021DF084(void);
void FieldMap_021DF0CC(NARC *param0, u32 param1);
void FieldMap_021DF17C(u32 param0);
BOOL FieldMap_021DF1CC(void);
BOOL FieldMap_021DF208(void);
void FieldMap_021DF224(void);

#endif // POKEPLATINUM_ENCOUNTER_EFFECT_H
