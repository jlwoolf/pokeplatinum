#include "slot_machine/slot_machine_anim.h"

#include <nitro.h>
#include <string.h>

#include "constants/species.h"

#include "slot_machine/slot_machine_game.h"
#include "slot_machine/slot_machine_sprite.h"
#include "slot_machine/struct_slot_machine_context.h"
#include "slot_machine/struct_slot_machine_reel_anim_task.h"
#include "slot_machine/struct_slot_machine_sprite.h"
#include "slot_machine/struct_slot_machine_sprite_resources.h"

#include "enums.h"
#include "math_util.h"
#include "overworld_anim_manager.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sys_task.h"
#include "sys_task_manager.h"

typedef struct {
    SlotMachineReelStateEnum state;
    u32 step;
    u32 done;
    vu32 loadState;
    SlotMachineReelType reelType;
    VecFx32 position;
    VecFx32 unk_20;
    u32 rotation;
    u32 timer;
    int stepIndex;
    SlotMachineContext *context;
    SlotMachineSprite sprite;
} SlotMachineReelState;

typedef struct {
    SlotMachineContext *context;
    fx32 offset;
    SlotMachineReelIndex reelIndex;
} SlotMachineReelArgs;

typedef struct {
    SlotMachineReelArgs args;
    SlotMachineSprite sprite;
} SlotMachineReel;

typedef struct {
    SlotMachineContext *context;
    u32 place;
    u32 modulus;
    SlotMachineSprite sprite;
} SlotMachineDigit;

typedef struct {
    SlotMachineContext *context;
    u32 place;
    u32 modulus;
    SlotMachineSprite sprite;
} SlotMachineDigit2;

typedef struct {
    u32 state;
    u32 done;
    u32 timer;
    vu32 loadState;
    SlotMachineContext *context;
    SlotMachineSprite sprite;
} SlotMachineSymbolSprite;

typedef struct {
    u32 unk_00;
    SlotMachineWinSymbolState state;
    u32 step;
    u32 done;
    u32 loadState;
    int timer;
    SlotMachineWinType winType;
    void *unk_1C;
    SlotMachineContext *context;
    SlotMachineSprite sprite;
} SlotMachineWinSymbol;

typedef struct {
    u32 state;
    u32 done;
    u32 timer;
    u32 loopCount;
    vu32 loadState;
    VecFx32 unk_14;
    VecFx32 unk_20;
    SlotMachineContext *context;
    SlotMachineSprite sprite1;
    SlotMachineSprite sprite2;
} SlotMachineBonus;

typedef struct {
    SlotMachineContext *context;
    SlotMachineSprite sprite;
} SlotMachineButton;

typedef struct {
    int timer;
    SlotMachineContext *context;
    SlotMachineSprite sprite;
} SlotMachineButton2;

typedef struct {
    SlotMachineContext *context;
    SlotMachineSprite sprite;
} SlotMachineButton3;

typedef struct {
    int timer;
    SlotMachineContext *context;
    SlotMachineSprite sprite;
} SlotMachineButton4;

typedef struct {
    SlotMachineContext *context;
    SlotMachineSprite sprites[2];
} SlotMachineCreditDigit;

typedef struct {
    SlotMachineContext *context;
    SlotMachineSprite sprites[5];
} SlotMachinePayoutDigit;

typedef struct {
    SlotMachineNumberType numberType;
    u32 value;
    u32 digitCount;
    int timer;
    int spriteCount;
    SlotMachineContext *context;
    SlotMachineSprite sprites[5];
} SlotMachineNumber;

typedef struct {
    int timer;
    int digitCount;
    SlotMachineContext *context;
    SlotMachineSprite sprites[3];
} SlotMachineNumber2;

typedef struct {
    int state;
    int finished;
    int loadState;
    int timer;
    int flashCount;
    int resourcesRemoved;
    SlotMachineSymbol symbol;
    SlotMachinePaletteIndex paletteIndex;
    SlotMachineSprite sprites[3];
    SlotMachineContext *context;
} SlotMachineJackpot;

static void SlotMachine_ReelState_LoadResources(SlotMachineReelState *param0, SlotMachineReelType param1);
static void SlotMachine_ReelState_FreeResources(SlotMachineContext *param0);
static void SlotMachine_ReelState_RequestChar(SysTask *param0, void *param1);
static void SlotMachine_ReelState_ReleaseChar(SysTask *param0, void *param1);
static void SlotMachine_ReelState_CreateSprite2(SlotMachineContext *param0, SlotMachineSprite *param1, const VecFx32 *param2);
static void SlotMachine_Symbol_LoadResources(SlotMachineSymbolSprite *param0);
static void SlotMachine_Jackpot_LoadResources(SlotMachineJackpot *param0);

static const OverworldAnimManagerFuncs sSlotMachineReelFuncs;
static const OverworldAnimManagerFuncs sSlotMachinePayoutDigitFuncs2;
static const int sSlotMachineReelSymbolAnim[6];
static const fx32 sSlotMachinePayoutDigitOffset[10];
static const fx32 sSlotMachineCreditDigitOffset[10];
static const SlotMachineSpriteResources sSlotMachineReelResources[SlotMachineReelType_05];
static const SlotMachineSpriteResources sSlotMachineWinSymbolResources[SlotMachineWinType_03];

void SlotMachine_InitReelSprites(SlotMachineContext *param0)
{
    SlotMachineReelIndex v0;
    fx32 v1, v2;
    OverworldAnimManager *v3;
    SlotMachineReelArgs v4;
    VecFx32 v5 = { 0, 0, 0 };

    v4.context = param0;

    for (v0 = 0, v1 = (FX32_ONE * (40 + 28)); v0 < 3; v0++, v1 += (FX32_ONE * 60)) {
        for (v2 = 0; v2 < (FX32_ONE * 160); v2 += (FX32_ONE * 32)) {
            v5.x = v1;
            v4.reelIndex = v0;
            v4.offset = v2;
            v3 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineReelFuncs, &v5, 0, &v4, 139);
        }
    }
}

static int SlotMachine_Reel_Init(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    SlotMachineReel *v1 = param1;
    const SlotMachineReelArgs *v2 = OverworldAnimManager_GetUserData(param0);

    v1->args = *v2;

    OverworldAnimManager_GetPosition(param0, &v0);
    SlotMachineSprite_CreateSprite(v1->args.context->spriteManager, &v1->sprite, &v0, (NNS_G2D_VRAM_TYPE_2DMAIN), 0, 0, 0, 0, 0, 3, 2);
    Sprite_SetAnimateFlag(v1->sprite.sprite, 1);

    return 1;
}

static void SlotMachine_Reel_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineReel *v0 = param1;
    SlotMachineSprite_DeleteSprite(&v0->sprite);
}

static void SlotMachine_Reel_Update(OverworldAnimManager *param0, void *param1)
{
    int v0;
    u32 v1;
    fx32 v2;
    VecFx32 v3;
    SlotMachineReel *v4 = param1;

    v0 = v4->args.reelIndex;
    v2 = v4->args.context->reelPositions[v0] + v4->args.offset;
    v2 %= (FX32_ONE * 160);

    OverworldAnimManager_GetPosition(param0, &v3);
    v3.y = v2 + (FX32_ONE * 16) + v4->args.context->reelBounce[v0];
    Sprite_SetPosition(v4->sprite.sprite, &v3);

    v2 = ((v2) / 32);
    v1 = sSlotMachineReelSymbolAnim[SlotMachine_GetReelSymbol(v4->args.context, v0, ((v2) / FX32_ONE))];

    if (v1 != Sprite_GetActiveAnim(v4->sprite.sprite)) {
        Sprite_SetAnim(v4->sprite.sprite, v1);
        Sprite_SetAnimFrame(v4->sprite.sprite, 0);
    }
}

static void SlotMachine_Reel_Noop(OverworldAnimManager *param0, void *param1)
{
    SlotMachineReel *v0 = param1;
}

static const OverworldAnimManagerFuncs sSlotMachineReelFuncs = {
    sizeof(SlotMachineReel),
    SlotMachine_Reel_Init,
    SlotMachine_Reel_Exit,
    SlotMachine_Reel_Update,
    SlotMachine_Reel_Noop
};

void SlotMachine_InitPayoutDigits(SlotMachineContext *param0)
{
    u32 v0;
    VecFx32 v1 = { (FX32_ONE * 108), (FX32_ONE * 180), 0 };

    for (v0 = 1; v0 < 100000; v0 *= 10, v1.x -= (FX32_ONE * 8)) {
        OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachinePayoutDigitFuncs2, &v1, v0, param0, 141);
    }
}

static int SlotMachine_Digit_Init(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    SlotMachineDigit *v1 = param1;

    v1->place = OverworldAnimManager_GetUserInt(param0);
    v1->modulus = v1->place * 10;
    v1->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);

    OverworldAnimManager_GetPosition(param0, &v0);
    SlotMachineSprite_CreateSprite(v1->context->spriteManager, &v1->sprite, &v0, (NNS_G2D_VRAM_TYPE_2DMAIN), 0, 1, 1, 1, 1, 1, 1);
    Sprite_SetAnimateFlag(v1->sprite.sprite, 1);

    return 1;
}

static void SlotMachine_Digit_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineDigit *v0 = param1;
    SlotMachineSprite_DeleteSprite(&v0->sprite);
}

static void SlotMachine_Digit_Update(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    SlotMachineDigit *v1 = param1;
    u32 v2 = v1->context->coins;

    if ((v1->place > 1) && (v2 < v1->place)) {
        Sprite_SetDrawFlag(v1->sprite.sprite, FALSE);
        return;
    }

    Sprite_SetDrawFlag(v1->sprite.sprite, TRUE);

    v2 %= v1->modulus;
    v2 /= v1->place;

    if (v2 != Sprite_GetActiveAnim(v1->sprite.sprite)) {
        Sprite_SetAnim(v1->sprite.sprite, v2);
        Sprite_RestartAnim(v1->sprite.sprite);
    }

    OverworldAnimManager_GetPosition(param0, &v0);
    v0.x += sSlotMachinePayoutDigitOffset[v2];
    Sprite_SetPosition(v1->sprite.sprite, &v0);
}

static void SlotMachine_Digit_Noop(OverworldAnimManager *param0, void *param1)
{
    SlotMachineDigit *v0 = param1;
}

static const OverworldAnimManagerFuncs sSlotMachinePayoutDigitFuncs2 = {
    sizeof(SlotMachineDigit),
    SlotMachine_Digit_Init,
    SlotMachine_Digit_Exit,
    SlotMachine_Digit_Update,
    SlotMachine_Digit_Noop
};

static const OverworldAnimManagerFuncs sSlotMachineCreditDigitFuncs2;

void SlotMachine_InitCreditDigits(SlotMachineContext *param0)
{
    u32 v0;
    VecFx32 v1 = { (FX32_ONE * 180), (FX32_ONE * 180), 0 };

    for (v0 = 1; v0 < 100000; v0 *= 10, v1.x -= (FX32_ONE * 8)) {
        OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineCreditDigitFuncs2, &v1, v0, param0, 141);
    }
}

static int SlotMachine_Digit2_Init(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    SlotMachineDigit2 *v1 = param1;

    v1->place = OverworldAnimManager_GetUserInt(param0);
    v1->modulus = v1->place * 10;
    v1->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);

    OverworldAnimManager_GetPosition(param0, &v0);
    SlotMachineSprite_CreateSprite(v1->context->spriteManager, &v1->sprite, &v0, (NNS_G2D_VRAM_TYPE_2DMAIN), 0, 1, 1, 1, 1, 1, 1);
    Sprite_SetAnimateFlag(v1->sprite.sprite, 1);

    return 1;
}

static void SlotMachine_Digit2_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineDigit2 *v0 = param1;
    SlotMachineSprite_DeleteSprite(&v0->sprite);
}

static void SlotMachine_Digit2_Update(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    SlotMachineDigit2 *v1 = param1;
    u32 v2 = v1->context->winAmount;

    if (v2 < v1->place) {
        Sprite_SetDrawFlag(v1->sprite.sprite, FALSE);
        return;
    }

    Sprite_SetDrawFlag(v1->sprite.sprite, TRUE);

    v2 %= v1->modulus;
    v2 /= v1->place;

    if (v2 != Sprite_GetActiveAnim(v1->sprite.sprite)) {
        Sprite_SetAnim(v1->sprite.sprite, v2);
        Sprite_RestartAnim(v1->sprite.sprite);
    }

    OverworldAnimManager_GetPosition(param0, &v0);
    v0.x += sSlotMachineCreditDigitOffset[v2];
    Sprite_SetPosition(v1->sprite.sprite, &v0);
}

static void SlotMachine_Digit2_Noop(OverworldAnimManager *param0, void *param1)
{
    SlotMachineDigit *v0 = param1;
}

static const OverworldAnimManagerFuncs sSlotMachineCreditDigitFuncs2 = {
    sizeof(SlotMachineDigit2),
    SlotMachine_Digit2_Init,
    SlotMachine_Digit2_Exit,
    SlotMachine_Digit2_Update,
    SlotMachine_Digit2_Noop
};

static const OverworldAnimManagerFuncs sSlotMachineReelStateFuncs;
static int (*const *const sSlotMachineReelStateFuncs2[SlotMachineReelStateEnum_07])(SlotMachineReelState *);

OverworldAnimManager *SlotMachine_CreateReel(SlotMachineContext *param0, SlotMachineReelType param1)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { (FX32_ONE * 0), (FX32_ONE * 400), 0 };

    v0 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineReelStateFuncs, &v1, param1, param0, 134);
    return v0;
}

void SlotMachine_SetReelState(OverworldAnimManager *param0, SlotMachineReelStateEnum param1)
{
    SlotMachineReelState *v0 = OverworldAnimManager_GetFuncsContext(param0);

    v0->state = param1;
    v0->step = 0;
    v0->done = 0;
    v0->timer = 0;
}

void SlotMachine_SetReelVisible(OverworldAnimManager *param0, int param1)
{
    SlotMachineReelState *v0 = OverworldAnimManager_GetFuncsContext(param0);

    if (param1 == 1) {
        Sprite_SetDrawFlag(v0->sprite.sprite, FALSE);
    } else {
        Sprite_SetDrawFlag(v0->sprite.sprite, TRUE);
    }
}

int SlotMachine_IsReelDone(OverworldAnimManager *param0)
{
    SlotMachineReelState *v0 = OverworldAnimManager_GetFuncsContext(param0);
    return v0->done;
}

static int SlotMachine_ReelState_Init(OverworldAnimManager *param0, void *param1)
{
    SlotMachineReelState *v0 = param1;

    v0->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);
    v0->reelType = OverworldAnimManager_GetUserInt(param0);

    return 1;
}

static void SlotMachine_ReelState_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineReelState *v0 = param1;

    if (v0->sprite.sprite != NULL) {
        SlotMachine_ReelState_FreeResources(v0->context);
        SlotMachineSprite_DeleteSprite(&v0->sprite);
    }
}

static void SlotMachine_ReelState_Update(OverworldAnimManager *param0, void *param1)
{
    int v0;
    SlotMachineReelState *v1 = param1;

    int (*const *v2)(SlotMachineReelState *);

    do {
        v2 = sSlotMachineReelStateFuncs2[v1->state];
        v0 = v2[v1->step](v1);
    } while (v0 == 1);
}

static void SlotMachine_ReelState_Noop(OverworldAnimManager *param0, void *param1)
{
    SlotMachineReelState *v0 = param1;
}

static const OverworldAnimManagerFuncs sSlotMachineReelStateFuncs = {
    sizeof(SlotMachineReelState),
    SlotMachine_ReelState_Init,
    SlotMachine_ReelState_Exit,
    SlotMachine_ReelState_Update,
    SlotMachine_ReelState_Noop
};

static int SlotMachine_ReelState_Load(SlotMachineReelState *param0)
{
    SlotMachine_ReelState_LoadResources(param0, param0->reelType);
    param0->step++;
    return 0;
}

static int SlotMachine_ReelState_WaitLoad(SlotMachineReelState *param0)
{
    if (param0->loadState == 2) {
        param0->step++;
    }

    return 0;
}

static int SlotMachine_ReelState_CreateSprite(SlotMachineReelState *param0)
{
    VecFx32 v0 = { (FX32_ONE * 0), (FX32_ONE * (192 + 224)), 0 };

    SlotMachine_ReelState_CreateSprite2(param0->context, &param0->sprite, &v0);

    param0->done = 1;
    param0->step++;

    return 0;
}

static int SlotMachine_ReelState_Done(SlotMachineReelState *param0)
{
    return 0;
}

static int (*const sSlotMachineReelState_Load[])(SlotMachineReelState *work) = {
    SlotMachine_ReelState_Load,
    SlotMachine_ReelState_WaitLoad,
    SlotMachine_ReelState_CreateSprite,
    SlotMachine_ReelState_Done,
};

static int SlotMachine_ReelState_Spin(SlotMachineReelState *param0)
{
    VecFx32 v0 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * 192)), 0 };
    VecFx32 v1 = { 0x2000, 0x2000, 0 };

    Sprite_SetAffineScale(param0->sprite.sprite, &v1);
    Sprite_SetAffineZRotation(param0->sprite.sprite, 0);
    Sprite_SetPosition(param0->sprite.sprite, &v0);
    Sprite_SetAnim(param0->sprite.sprite, 0);
    Sprite_SetAnimFrame(param0->sprite.sprite, 0);
    Sound_PlayEffect(SEQ_SE_DP_UG_020_sseq);

    param0->step++;
    return 0;
}

static int SlotMachine_ReelState_SpinUpdate(SlotMachineReelState *param0)
{
    VecFx32 v0, v1;

    SlotMachineSprite_GetPosition(param0->sprite.sprite, &v0);
    SlotMachineSprite_GetScale(param0->sprite.sprite, &v1);

    v0.y -= (FX32_ONE * 3) + (FX32_ONE / 1);
    v1.x -= 0x1c7;
    v1.y -= 0x1c7;

    param0->timer++;

    if (param0->timer >= 9) {
        v0.y = ((FX32_ONE * 192) + (FX32_ONE * 160));
        v1.x = 0x1000;
        v1.y = 0x1000;
        param0->timer = 0;
        param0->step++;
    }

    Sprite_SetPosition(param0->sprite.sprite, &v0);
    Sprite_SetAffineScale(param0->sprite.sprite, &v1);

    return 0;
}

static int SlotMachine_ReelState_SpinEnd(SlotMachineReelState *param0)
{
    param0->timer++;

    if (param0->timer >= 3) {
        param0->timer = 0;
        param0->done = 1;
        param0->step++;
    }

    return 0;
}

static int (*const sSlotMachineReelState_Spin[])(SlotMachineReelState *) = {
    SlotMachine_ReelState_Spin, SlotMachine_ReelState_SpinUpdate, SlotMachine_ReelState_SpinEnd, SlotMachine_ReelState_Done
};

static int SlotMachine_ReelState_Stop(SlotMachineReelState *param0)
{
    Sprite_SetAnim(param0->sprite.sprite, 1);
    Sprite_RestartAnim(param0->sprite.sprite);
    Sprite_SetAnimateFlag(param0->sprite.sprite, 1);

    Sound_PlayEffect(SEQ_SE_DP_SLOT01_sseq);
    param0->step++;

    return 0;
}

static int SlotMachine_ReelState_StopEnd(SlotMachineReelState *param0)
{
    param0->timer++;

    if (param0->timer >= 4) {
        param0->timer = 0;
        param0->done = 1;
        param0->step++;
    }

    return 0;
}

static int (*const sSlotMachineReelState_Stop[])(SlotMachineReelState *) = {
    SlotMachine_ReelState_Stop, SlotMachine_ReelState_StopEnd, SlotMachine_ReelState_Done
};

static int SlotMachine_ReelState_Win(SlotMachineReelState *param0)
{
    VecFx32 v0 = { 0x1000, 0x1000, 0 };
    VecFx32 v1 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * 160)), 0 };

    param0->position = v1;

    Sprite_SetPosition(param0->sprite.sprite, &v1);
    Sprite_SetAffineScale(param0->sprite.sprite, &v0);
    Sprite_SetAffineZRotation(param0->sprite.sprite, 0);
    Sprite_SetAnim(param0->sprite.sprite, 3);
    Sprite_RestartAnim(param0->sprite.sprite);

    param0->step++;
    return 1;
}

static int SlotMachine_ReelState_WinUpdate(SlotMachineReelState *param0)
{
    VecFx32 v0;
    fx32 v1[8] = { (FX32_ONE * -8), (FX32_ONE * 0), (FX32_ONE * -6), (FX32_ONE * 0), (FX32_ONE * -4), (FX32_ONE * 0), (FX32_ONE * -2), (FX32_ONE * 0) };

    v0 = param0->position;
    v0.y += v1[param0->timer / 2];

    Sprite_SetPosition(param0->sprite.sprite, &v0);

    param0->timer++;

    if (param0->timer >= 16) {
        param0->timer = 0;
        param0->done = 1;
        param0->step++;
    }

    return 0;
}

static int (*const sSlotMachineReelState_Win[])(SlotMachineReelState *) = {
    SlotMachine_ReelState_Win, SlotMachine_ReelState_WinUpdate, SlotMachine_ReelState_Done
};

static int SlotMachine_ReelState_Lose(SlotMachineReelState *param0)
{
    VecFx32 v0 = { 0x1000, 0x1000, 0 };
    VecFx32 v1 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * 160)), 0 };

    param0->position = v1;

    Sprite_SetPosition(param0->sprite.sprite, &v1);
    Sprite_SetAffineScale(param0->sprite.sprite, &v0);
    Sprite_SetAffineZRotation(param0->sprite.sprite, 0);
    Sprite_SetAnim(param0->sprite.sprite, 4);
    Sprite_RestartAnim(param0->sprite.sprite);

    param0->step++;
    return 1;
}

static int SlotMachine_ReelState_LoseUpdate(SlotMachineReelState *param0)
{
    fx32 v0;
    VecFx32 v1, v2;

    SlotMachineSprite_GetPosition(param0->sprite.sprite, &v1);
    SlotMachineSprite_GetScale(param0->sprite.sprite, &v2);

    v1.y += (FX32_ONE * 4);
    v2.x += 0x1c7;
    v2.y += 0x1c7;

    param0->timer++;

    if (param0->timer >= 10) {
        v1.y = ((FX32_ONE * 192) + (FX32_ONE * 256));
        v2.x = 0x1000;
        v2.y = 0x1000;
        param0->timer = 0;
        param0->done = 1;
        param0->step++;
    }

    Sprite_SetPosition(param0->sprite.sprite, &v1);
    Sprite_SetAffineScale(param0->sprite.sprite, &v2);

    return 0;
}

static int (*const sSlotMachineReelState_Lose[])(SlotMachineReelState *) = {
    SlotMachine_ReelState_Lose, SlotMachine_ReelState_LoseUpdate, SlotMachine_ReelState_Done
};

static int SlotMachine_ReelState_Jackpot(SlotMachineReelState *param0)
{
    VecFx32 v0 = { 0x1000, 0x1000, 0 };
    VecFx32 v1 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * 160)), 0 };
    VecFx32 v2 = { 0, 0, 0 };

    param0->position = v1;
    param0->unk_20 = v2;
    param0->timer = 0;
    param0->stepIndex = 0;
    param0->rotation = 0;
    param0->done = 1;

    Sprite_SetPosition(param0->sprite.sprite, &v1);
    Sprite_SetAffineScale(param0->sprite.sprite, &v0);
    Sprite_SetAffineZRotation(param0->sprite.sprite, 0);
    Sprite_SetAnim(param0->sprite.sprite, 2);
    Sprite_RestartAnim(param0->sprite.sprite);

    param0->step++;
    return 1;
}

static int SlotMachine_ReelState_JackpotUpdate(SlotMachineReelState *param0)
{
    u32 v0[8] = { -16, 0, 16, 0, 16, 0, -16, 0 };
    fx32 v1[8] = { (FX32_ONE * -2), 0, (FX32_ONE * 2), 0, (FX32_ONE * 2), 0, (FX32_ONE * -2), 0 };
    u32 v2[8] = { 4, 1, 4, 8, 4, 1, 4, 8 };

    param0->rotation += v0[param0->stepIndex];
    param0->position.x += v1[param0->stepIndex];
    param0->timer++;

    if (param0->timer >= v2[param0->stepIndex]) {
        param0->stepIndex++;

        if (param0->stepIndex >= 8) {
            param0->stepIndex = 0;
        }

        param0->timer = 0;
    }

    Sprite_SetPosition(param0->sprite.sprite, &param0->position);
    Sprite_SetAffineZRotation(param0->sprite.sprite, param0->rotation);

    return 0;
}

static int (*const sSlotMachineWinSymbol_Jackpot[])(SlotMachineReelState *) = {
    SlotMachine_ReelState_Jackpot, SlotMachine_ReelState_JackpotUpdate, SlotMachine_ReelState_Done
};

static int SlotMachine_ReelState_Bonus(SlotMachineReelState *param0)
{
    VecFx32 v0 = { 0x1000, 0x1000, 0 };
    VecFx32 v1 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * 160)), 0 };
    VecFx32 v2 = { 0, 0, 0 };

    param0->position = v1;
    param0->unk_20 = v2;
    param0->done = 1;

    Sprite_SetPosition(param0->sprite.sprite, &v1);
    Sprite_SetAffineScale(param0->sprite.sprite, &v0);
    Sprite_SetAffineZRotation(param0->sprite.sprite, 0);
    Sprite_SetAnim(param0->sprite.sprite, 2);
    Sprite_RestartAnim(param0->sprite.sprite);

    param0->step++;

    return 1;
}

static int (*const sSlotMachineWinSymbol_Bonus[])(SlotMachineReelState *) = {
    SlotMachine_ReelState_Bonus, SlotMachine_ReelState_Done
};

static int (*const *const sSlotMachineReelStateFuncs2[SlotMachineReelStateEnum_07])(SlotMachineReelState *) = {
    sSlotMachineReelState_Load, sSlotMachineReelState_Spin, sSlotMachineReelState_Stop, sSlotMachineReelState_Win, sSlotMachineReelState_Lose, sSlotMachineWinSymbol_Jackpot, sSlotMachineWinSymbol_Bonus
};

static void SlotMachine_ReelState_LoadResources(SlotMachineReelState *param0, SlotMachineReelType param1)
{
    SysTask *v0;
    SlotMachineContext *v1 = param0->context;
    const SlotMachineSpriteResources *v2;

    GF_ASSERT(param1 < SlotMachineReelType_05);
    v2 = &sSlotMachineReelResources[param1];

    SlotMachineSprite_AddTiles(v1->spriteManager, (NNS_G2D_VRAM_TYPE_2DSUB), v1->narc, v2->tilesID, 2);
    SlotMachineSprite_AddPalette(v1->spriteManager, (NNS_G2D_VRAM_TYPE_2DSUB), v1->narc, v2->paletteID, 2);
    SlotMachineSprite_AddCell(v1->spriteManager, v1->narc, v2->cellID, 2);
    SlotMachineSprite_AddAnim(v1->spriteManager, v1->narc, v2->animID, 2);

    v0 = SysTask_ExecuteOnVBlank(SlotMachine_ReelState_RequestChar, param0, 257);
    GF_ASSERT(v0 != NULL);

    v0 = SysTask_ExecuteAfterVBlank(SlotMachine_ReelState_ReleaseChar, param0, 257);
    GF_ASSERT(v0 != NULL);
}

static void SlotMachine_ReelState_FreeResources(SlotMachineContext *param0)
{
    SlotMachineSprite_RemoveResources(param0->spriteManager, 2, 2, 2, 2);
}

static void SlotMachine_ReelState_RequestChar(SysTask *param0, void *param1)
{
    SlotMachineReelState *v0 = param1;
    SlotMachineContext *v1 = v0->context;

    SlotMachineSprite_RequestChar(v1->spriteManager, 2);
    SlotMachineSprite_RequestPltt(v1->spriteManager, 2);

    v0->loadState = 1;

    SysTask_Done(param0);
}

static void SlotMachine_ReelState_ReleaseChar(SysTask *param0, void *param1)
{
    SlotMachineReelState *v0 = param1;
    SlotMachineContext *v1 = v0->context;

    if (v0->loadState == 1) {
        SlotMachineSprite_ReleasePltt(v1->spriteManager, 2);
        v0->loadState = 2;
        SysTask_Done(param0);
    }
}

static void SlotMachine_ReelState_CreateSprite2(SlotMachineContext *param0, SlotMachineSprite *param1, const VecFx32 *param2)
{
    VecFx32 v0 = { 0, 0, 0 };
    VecFx32 v1 = { 0x1000, 0x1000, 0 };

    SlotMachineSprite_CreateSprite(param0->spriteManager, param1, param2, (NNS_G2D_VRAM_TYPE_2DSUB), 1, 2, 2, 2, 2, 2, 7);

    Sprite_SetAffineOverwriteMode(param1->sprite, 2);
    Sprite_SetAffineTranslation(param1->sprite, &v0);
    Sprite_SetAffineScale(param1->sprite, &v1);
    Sprite_SetAffineZRotation(param1->sprite, CalcAngleRotationIdx_Wraparound(0));
    Sprite_SetAnimateFlag(param1->sprite, 1);
}

static const OverworldAnimManagerFuncs sSlotMachineSymbolFuncs;

OverworldAnimManager *SlotMachine_CreateSymbol(SlotMachineContext *param0)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * (160 - 16))), 0 };

    v0 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineSymbolFuncs, &v1, 0, param0, 135);
    return v0;
}

static int SlotMachine_Symbol_Init(OverworldAnimManager *param0, void *param1)
{
    SlotMachineSymbolSprite *v0 = param1;

    v0->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);
    SlotMachine_Symbol_LoadResources(v0);

    return 1;
}

static void SlotMachine_Symbol_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineSymbolSprite *v0 = param1;

    if (v0->sprite.sprite != NULL) {
        SlotMachineSprite_RemoveResources(v0->context->spriteManager, 3, 3, 3, 3);
        SlotMachineSprite_DeleteSprite(&v0->sprite);
    }
}

static void SlotMachine_Symbol_Update(OverworldAnimManager *param0, void *param1)
{
    SlotMachineSymbolSprite *v0 = param1;

    switch (v0->state) {
    case 0:
        if (v0->loadState != 2) {
            return;
        }

        {
            VecFx32 v1;

            OverworldAnimManager_GetPosition(param0, &v1);
            SlotMachineSprite_CreateSprite(v0->context->spriteManager, &v0->sprite, &v1, (NNS_G2D_VRAM_TYPE_2DSUB), 1, 3, 3, 3, 3, 2, 5);
            Sprite_SetAnimateFlag(v0->sprite.sprite, 1);

            v0->state++;
        }
    case 1:
        v0->timer++;

        if (v0->timer < 15) {
            return;
        }

        v0->state++;
        v0->done = 1;
        break;
    case 2:
        SlotMachineSprite_RemoveResources(v0->context->spriteManager, 3, 3, 3, 3);
        SlotMachineSprite_DeleteSprite(&v0->sprite);
        v0->state++;
    case 3:
        break;
    }
}

static void SlotMachine_Symbol_Noop(OverworldAnimManager *param0, void *param1)
{
    SlotMachineSymbolSprite *v0 = param1;
}

static const OverworldAnimManagerFuncs sSlotMachineSymbolFuncs = {
    sizeof(SlotMachineSymbolSprite),
    SlotMachine_Symbol_Init,
    SlotMachine_Symbol_Exit,
    SlotMachine_Symbol_Update,
    SlotMachine_Symbol_Noop
};

static void SlotMachine_Symbol_RequestChar(SysTask *param0, void *param1)
{
    SlotMachineSymbolSprite *v0 = param1;
    SlotMachineContext *v1 = v0->context;

    SlotMachineSprite_RequestChar(v1->spriteManager, 3);
    SlotMachineSprite_RequestPltt(v1->spriteManager, 3);

    v0->loadState = 1;

    SysTask_Done(param0);
}

static void SlotMachine_Symbol_ReleaseChar(SysTask *param0, void *param1)
{
    SlotMachineSymbolSprite *v0 = param1;
    SlotMachineContext *v1 = v0->context;

    if (v0->loadState == 1) {
        SlotMachineSprite_ReleasePltt(v1->spriteManager, 3);
        v0->loadState = 2;
        SysTask_Done(param0);
    }
}

static void SlotMachine_Symbol_LoadResources(SlotMachineSymbolSprite *param0)
{
    SysTask *v0;
    SlotMachineContext *v1 = param0->context;

    SlotMachineSprite_AddTiles(v1->spriteManager, (NNS_G2D_VRAM_TYPE_2DSUB), v1->narc, 44, 3);
    SlotMachineSprite_AddPalette(v1->spriteManager, (NNS_G2D_VRAM_TYPE_2DSUB), v1->narc, 47, 3);
    SlotMachineSprite_AddCell(v1->spriteManager, v1->narc, 45, 3);
    SlotMachineSprite_AddAnim(v1->spriteManager, v1->narc, 46, 3);

    v0 = SysTask_ExecuteOnVBlank(SlotMachine_Symbol_RequestChar, param0, 257);
    GF_ASSERT(v0 != NULL);

    v0 = SysTask_ExecuteAfterVBlank(SlotMachine_Symbol_ReleaseChar, param0, 257);
    GF_ASSERT(v0 != NULL);
}

static const OverworldAnimManagerFuncs sSlotMachineWinSymbolFuncs;
static int (*const *const sSlotMachineWinSymbolStateFuncs[SlotMachineWinSymbolState_09])(SlotMachineWinSymbol *);

static void SlotMachine_WinSymbol_RequestChar(SysTask *param0, void *param1)
{
    SlotMachineWinSymbol *v0 = param1;
    SlotMachineContext *v1 = v0->context;

    SlotMachineSprite_RequestChar(v1->spriteManager, 4);
    SlotMachineSprite_RequestPltt(v1->spriteManager, 4);

    v0->loadState = 1;
    SysTask_Done(param0);
}

static void SlotMachine_WinSymbol_ReleaseChar(SysTask *param0, void *param1)
{
    SlotMachineWinSymbol *v0 = param1;
    SlotMachineContext *v1 = v0->context;

    if (v0->loadState == 1) {
        SlotMachineSprite_ReleasePltt(v1->spriteManager, 4);

        v0->loadState = 2;
        SysTask_Done(param0);
    }
}

static void SlotMachine_WinSymbol_LoadResources(SlotMachineWinSymbol *param0)
{
    SysTask *v0;
    SlotMachineContext *v1 = param0->context;
    const SlotMachineSpriteResources *v2 = &sSlotMachineWinSymbolResources[param0->winType];

    SlotMachineSprite_AddTiles(v1->spriteManager, (NNS_G2D_VRAM_TYPE_2DSUB), v1->narc, v2->tilesID, 4);
    SlotMachineSprite_AddPalette(v1->spriteManager, (NNS_G2D_VRAM_TYPE_2DSUB), v1->narc, v2->paletteID, 4);
    SlotMachineSprite_AddCell(v1->spriteManager, v1->narc, v2->cellID, 4);
    SlotMachineSprite_AddAnim(v1->spriteManager, v1->narc, v2->animID, 4);

    v0 = SysTask_ExecuteOnVBlank(SlotMachine_WinSymbol_RequestChar, param0, 257);
    GF_ASSERT(v0 != NULL);

    v0 = SysTask_ExecuteAfterVBlank(SlotMachine_WinSymbol_ReleaseChar, param0, 257);
    GF_ASSERT(v0 != NULL);
}

OverworldAnimManager *SlotMachine_CreateWinSymbol(SlotMachineContext *param0, SlotMachineWinType param1)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { (FX32_ONE * 128), (FX32_ONE * 160), 0 };

    v0 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineWinSymbolFuncs, &v1, param1, param0, 137);

    return v0;
}

void SlotMachine_SetWinSymbolState(OverworldAnimManager *param0, SlotMachineWinSymbolState param1)
{
    SlotMachineWinSymbol *v0 = OverworldAnimManager_GetFuncsContext(param0);

    v0->state = param1;
    v0->step = 0;
    v0->done = 0;
    v0->timer = 0;
}

int SlotMachine_IsWinSymbolDone(OverworldAnimManager *param0)
{
    SlotMachineWinSymbol *v0 = OverworldAnimManager_GetFuncsContext(param0);
    return v0->done;
}

static int SlotMachine_WinSymbol_Init(OverworldAnimManager *param0, void *param1)
{
    SlotMachineWinSymbol *v0 = param1;

    v0->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);
    v0->winType = OverworldAnimManager_GetUserInt(param0);

    SlotMachine_WinSymbol_LoadResources(v0);

    return 1;
}

static void SlotMachine_WinSymbol_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineWinSymbol *v0 = param1;

    if (v0->sprite.sprite != NULL) {
        SlotMachineContext *v1 = v0->context;

        SlotMachineSprite_RemoveResources(v1->spriteManager, 4, 4, 4, 4);
        SlotMachineSprite_DeleteSprite(&v0->sprite);
    }
}

static void SlotMachine_WinSymbol_Update(OverworldAnimManager *param0, void *param1)
{
    int v0;
    SlotMachineWinSymbol *v1 = param1;

    int (*const *v2)(SlotMachineWinSymbol *);

    do {
        v2 = sSlotMachineWinSymbolStateFuncs[v1->state];
        v0 = v2[v1->step](v1);
    } while (v0 == 1);
}

static void SlotMachine_WinSymbol_Noop(OverworldAnimManager *param0, void *param1)
{
    SlotMachineWinSymbol *v0 = param1;
}

static const OverworldAnimManagerFuncs sSlotMachineWinSymbolFuncs = {
    sizeof(SlotMachineWinSymbol),
    SlotMachine_WinSymbol_Init,
    SlotMachine_WinSymbol_Exit,
    SlotMachine_WinSymbol_Update,
    SlotMachine_WinSymbol_Noop
};

static int SlotMachine_WinSymbol_Show(SlotMachineWinSymbol *param0)
{
    if (param0->loadState == 2) {
        VecFx32 v0 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * 256)), 0 };
        VecFx32 v1 = { 0, 0, 0 };
        VecFx32 v2 = { 0x1000, 0x1000, 0 };

        SlotMachineSprite_CreateSprite(param0->context->spriteManager, &param0->sprite, &v0, (NNS_G2D_VRAM_TYPE_2DSUB), 1, 4, 4, 4, 4, 2, 6);
        Sprite_SetAffineOverwriteMode(param0->sprite.sprite, 2);
        Sprite_SetAffineTranslation(param0->sprite.sprite, &v1);
        Sprite_SetAffineZRotation(param0->sprite.sprite, CalcAngleRotationIdx_Wraparound(0));

        param0->done = 1;
        param0->step++;
    }

    return 0;
}

static int SlotMachine_WinSymbol_Done(SlotMachineWinSymbol *param0)
{
    return 0;
}

static int (*const sSlotMachineWinSymbol_Show[])(SlotMachineWinSymbol *) = {
    SlotMachine_WinSymbol_Show,
    SlotMachine_WinSymbol_Done,
};

static int SlotMachine_WinSymbol_Anim1(SlotMachineWinSymbol *param0)
{
    VecFx32 v0 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * (160 - 32))), 0 };
    VecFx32 v1 = { 0x400, 0x400, 0 };

    Sprite_SetAffineScale(param0->sprite.sprite, &v1);
    Sprite_SetPosition(param0->sprite.sprite, &v0);
    Sprite_SetAnim(param0->sprite.sprite, 1);
    Sprite_SetAnimSpeed(param0->sprite.sprite, 0);
    Sprite_SetAnimateFlag(param0->sprite.sprite, 0);

    param0->step++;
    return 0;
}

static int SlotMachine_WinSymbol_Anim2(SlotMachineWinSymbol *param0)
{
    VecFx32 v0, v1;

    SlotMachineSprite_GetPosition(param0->sprite.sprite, &v0);
    SlotMachineSprite_GetScale(param0->sprite.sprite, &v1);

    v1.x += 0xc0;
    v1.y += 0xc0;

    param0->timer++;

    if (param0->timer >= 16) {
        v0.y = ((FX32_ONE * 192) + (FX32_ONE * (160 - 32)));
        v1.x = 0x1000;
        v1.y = 0x1000;
        param0->timer = 0;
        param0->step++;

        Sound_PlayPokemonCry(SPECIES_CLEFAIRY, 0);
    }

    Sprite_SetAffineScale(param0->sprite.sprite, &v1);
    Sprite_SetPosition(param0->sprite.sprite, &v0);
    return 0;
}

static int SlotMachine_WinSymbol_Anim3(SlotMachineWinSymbol *param0)
{
    Sprite_UpdateAnim(param0->sprite.sprite, (FX32_ONE * 1));
    param0->timer++;

    if (param0->timer >= 9) {
        param0->timer = 0;
        param0->step++;
        param0->done = 1;
    }

    return 0;
}

static int (*const sSlotMachineWinSymbol_Anim1[])(SlotMachineWinSymbol *) = {
    SlotMachine_WinSymbol_Anim1, SlotMachine_WinSymbol_Anim2, SlotMachine_WinSymbol_Anim3, SlotMachine_WinSymbol_Done
};

static int SlotMachine_WinSymbol_Anim4(SlotMachineWinSymbol *param0)
{
    VecFx32 v0 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * (160 - 32))), 0 };
    VecFx32 v1 = { 0x1000, 0x1000, 0 };

    Sprite_SetAffineScale(param0->sprite.sprite, &v1);
    Sprite_SetPosition(param0->sprite.sprite, &v0);
    Sprite_SetAnim(param0->sprite.sprite, 1);
    Sprite_SetAnimSpeed(param0->sprite.sprite, 0);
    Sprite_SetAnimateFlag(param0->sprite.sprite, 0);
    Sound_PlayEffect(SEQ_SE_DP_SLOT02_sseq);

    param0->step++;
    return 0;
}

static int SlotMachine_WinSymbol_Anim5(SlotMachineWinSymbol *param0)
{
    VecFx32 v0, v1;

    SlotMachineSprite_GetPosition(param0->sprite.sprite, &v0);
    SlotMachineSprite_GetScale(param0->sprite.sprite, &v1);

    v1.x -= 0x180;
    v1.y -= 0x180;

    param0->timer++;

    if (param0->timer >= 8) {
        v0.y = ((FX32_ONE * 192) + (FX32_ONE * 272));
        v1.x = 0x1000;
        v1.y = 0x1000;
        param0->timer = 0;
        param0->step++;
        param0->done = 1;
    }

    Sprite_SetAffineScale(param0->sprite.sprite, &v1);
    Sprite_SetPosition(param0->sprite.sprite, &v0);

    return 0;
}

static int (*const sSlotMachineWinSymbol_Anim4[])(SlotMachineWinSymbol *) = {
    SlotMachine_WinSymbol_Anim4, SlotMachine_WinSymbol_Anim5, SlotMachine_WinSymbol_Done
};

static int SlotMachine_WinSymbol_Anim6(SlotMachineWinSymbol *param0)
{
    VecFx32 v0 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * (160 - 32))), 0 };
    VecFx32 v1 = { 0x1000, 0x1000, 0 };

    Sprite_SetAffineScale(param0->sprite.sprite, &v1);
    Sprite_SetPosition(param0->sprite.sprite, &v0);
    Sprite_SetAnim(param0->sprite.sprite, 0);
    Sprite_SetAnimateFlag(param0->sprite.sprite, 0);
    Sprite_SetAnimSpeed(param0->sprite.sprite, 0);
    Sprite_RestartAnim(param0->sprite.sprite);

    param0->done = 1;
    param0->step++;

    return 0;
}

static int (*const sSlotMachineWinSymbol_Anim6[])(SlotMachineWinSymbol *) = {
    SlotMachine_WinSymbol_Anim6, SlotMachine_WinSymbol_Done
};

static int SlotMachine_WinSymbol_Anim7(SlotMachineWinSymbol *param0)
{
    VecFx32 v0 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * (160 - 32))), 0 };
    VecFx32 v1 = { 0x1000, 0x1000, 0 };

    Sprite_SetAffineScale(param0->sprite.sprite, &v1);
    Sprite_SetPosition(param0->sprite.sprite, &v0);
    Sprite_SetAnimateFlag(param0->sprite.sprite, 1);
    Sprite_SetAnimSpeed(param0->sprite.sprite, FX32_ONE / 2);

    if (Sprite_GetActiveAnim(param0->sprite.sprite) != 2) {
        Sprite_SetAnim(param0->sprite.sprite, 2);
        Sprite_RestartAnim(param0->sprite.sprite);
    }

    param0->done = 1;
    param0->step++;

    return 0;
}

static int (*const sSlotMachineWinSymbol_Anim7[])(SlotMachineWinSymbol *) = {
    SlotMachine_WinSymbol_Anim7, SlotMachine_WinSymbol_Done
};

static int SlotMachine_WinSymbol_Anim8(SlotMachineWinSymbol *param0)
{
    VecFx32 v0 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * (160 - 32))), 0 };
    VecFx32 v1 = { 0x1000, 0x1000, 0 };

    Sprite_SetAffineScale(param0->sprite.sprite, &v1);
    Sprite_SetPosition(param0->sprite.sprite, &v0);
    Sprite_SetAnim(param0->sprite.sprite, 5);
    Sprite_SetAnimateFlag(param0->sprite.sprite, 1);
    Sprite_SetAnimSpeed(param0->sprite.sprite, FX32_ONE);
    Sprite_RestartAnim(param0->sprite.sprite);

    param0->done = 1;
    param0->step++;

    return 0;
}

static int (*const sSlotMachineWinSymbol_Anim8[])(SlotMachineWinSymbol *) = {
    SlotMachine_WinSymbol_Anim8, SlotMachine_WinSymbol_Done
};

static int SlotMachine_WinSymbol_Anim9(SlotMachineWinSymbol *param0)
{
    VecFx32 v0 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * (160 - 32))), 0 };
    VecFx32 v1 = { 0x1000, 0x1000, 0 };

    Sprite_SetAffineScale(param0->sprite.sprite, &v1);
    Sprite_SetPosition(param0->sprite.sprite, &v0);
    Sprite_SetAnim(param0->sprite.sprite, 4);
    Sprite_SetAnimateFlag(param0->sprite.sprite, 1);
    Sprite_SetAnimSpeed(param0->sprite.sprite, FX32_ONE);
    Sprite_RestartAnim(param0->sprite.sprite);

    param0->done = 1;
    param0->step++;

    return 0;
}

static int (*const sSlotMachineWinSymbol_Anim9[])(SlotMachineWinSymbol *) = {
    SlotMachine_WinSymbol_Anim9, SlotMachine_WinSymbol_Done
};

static int SlotMachine_WinSymbol_Anim10(SlotMachineWinSymbol *param0)
{
    VecFx32 v0 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * (160 - 32))), 0 };
    VecFx32 v1 = { 0x1000, 0x1000, 0 };

    Sprite_SetAffineScale(param0->sprite.sprite, &v1);
    Sprite_SetPosition(param0->sprite.sprite, &v0);
    Sprite_SetAnim(param0->sprite.sprite, 3);
    Sprite_SetAnimateFlag(param0->sprite.sprite, 1);
    Sprite_SetAnimSpeed(param0->sprite.sprite, FX32_ONE);
    Sprite_RestartAnim(param0->sprite.sprite);

    param0->done = 1;
    param0->step++;

    return 0;
}

static int (*const sSlotMachineWinSymbol_Anim10[])(SlotMachineWinSymbol *) = {
    SlotMachine_WinSymbol_Anim10, SlotMachine_WinSymbol_Done
};

static int SlotMachine_WinSymbol_Anim11(SlotMachineWinSymbol *param0)
{
    VecFx32 v0 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * (160 - 32))), 0 };
    VecFx32 v1 = { 0x1000, 0x1000, 0 };

    Sprite_SetAffineScale(param0->sprite.sprite, &v1);
    Sprite_SetPosition(param0->sprite.sprite, &v0);
    Sprite_SetAnimateFlag(param0->sprite.sprite, 0);
    Sprite_SetAnimSpeed(param0->sprite.sprite, FX32_ONE);

    Sprite_SetAnim(param0->sprite.sprite, 5);
    Sprite_RestartAnim(param0->sprite.sprite);

    param0->timer = 0;
    param0->done = 1;
    param0->step++;

    return 0;
}

static int SlotMachine_WinSymbol_Anim12(SlotMachineWinSymbol *param0)
{
    Sprite_UpdateAnim(param0->sprite.sprite, FX32_ONE);

    if (Sprite_IsAnimated(param0->sprite.sprite) == 0) {
        param0->timer++;

        if (param0->timer >= 8) {
            param0->timer = 0;
            Sprite_RestartAnim(param0->sprite.sprite);
        }
    }

    return 0;
}

static int (*const sSlotMachineWinSymbol_Anim11[])(SlotMachineWinSymbol *) = {
    SlotMachine_WinSymbol_Anim11, SlotMachine_WinSymbol_Anim12, SlotMachine_WinSymbol_Done
};

static int (*const *const sSlotMachineWinSymbolStateFuncs[SlotMachineWinSymbolState_09])(SlotMachineWinSymbol *) = {
    sSlotMachineWinSymbol_Show, sSlotMachineWinSymbol_Anim1, sSlotMachineWinSymbol_Anim4, sSlotMachineWinSymbol_Anim6, sSlotMachineWinSymbol_Anim7, sSlotMachineWinSymbol_Anim8, sSlotMachineWinSymbol_Anim9, sSlotMachineWinSymbol_Anim10, sSlotMachineWinSymbol_Anim11
};

static const OverworldAnimManagerFuncs sSlotMachineBonusFuncs;

static void SlotMachine_Bonus_RequestChar(SysTask *param0, void *param1)
{
    SlotMachineBonus *v0 = param1;
    SlotMachineContext *v1 = v0->context;

    SlotMachineSprite_RequestChar(v1->spriteManager, 5);
    SlotMachineSprite_RequestPltt(v1->spriteManager, 5);

    v0->loadState = 1;

    SysTask_Done(param0);
}

static void SlotMachine_Bonus_ReleaseChar(SysTask *param0, void *param1)
{
    SlotMachineBonus *v0 = param1;
    SlotMachineContext *v1 = v0->context;

    if (v0->loadState = 1) {
        SlotMachineSprite_ReleasePltt(v1->spriteManager, 5);
        v0->loadState = 2;
        SysTask_Done(param0);
    }
}

static void SlotMachine_Bonus_LoadResources(SlotMachineBonus *param0)
{
    SysTask *v0;
    SlotMachineContext *v1 = param0->context;

    SlotMachineSprite_AddTiles(v1->spriteManager, (NNS_G2D_VRAM_TYPE_2DSUB), v1->narc, 56, 5);
    SlotMachineSprite_AddPalette(v1->spriteManager, (NNS_G2D_VRAM_TYPE_2DSUB), v1->narc, 59, 5);
    SlotMachineSprite_AddCell(v1->spriteManager, v1->narc, 57, 5);
    SlotMachineSprite_AddAnim(v1->spriteManager, v1->narc, 58, 5);

    v0 = SysTask_ExecuteOnVBlank(SlotMachine_Bonus_RequestChar, param0, 257);
    GF_ASSERT(v0 != NULL);
    v0 = SysTask_ExecuteAfterVBlank(SlotMachine_Bonus_ReleaseChar, param0, 257);
    GF_ASSERT(v0 != NULL);
}

OverworldAnimManager *SlotMachine_CreateBonus(SlotMachineContext *param0)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { 0, 0, 0 };

    v0 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineBonusFuncs, &v1, 0, param0, 136);
    return v0;
}

int SlotMachine_IsBonusDone(OverworldAnimManager *param0)
{
    SlotMachineBonus *v0 = OverworldAnimManager_GetFuncsContext(param0);

    return v0->done;
}

static int SlotMachine_Bonus_Init(OverworldAnimManager *param0, void *param1)
{
    SlotMachineBonus *v0 = param1;

    v0->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);
    SlotMachine_Bonus_LoadResources(v0);
    return 1;
}

static void SlotMachine_Bonus_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineBonus *v0 = param1;

    if (v0->sprite1.sprite != NULL) {
        SlotMachineSprite_RemoveResources(v0->context->spriteManager, 5, 5, 5, 5);
        SlotMachineSprite_DeleteSprite(&v0->sprite1);

        if (v0->sprite2.sprite != NULL) {
            SlotMachineSprite_DeleteSprite(&v0->sprite2);
        }
    }
}

static void SlotMachine_Bonus_MoveSprite(OverworldAnimManager *param0, fx32 param1, fx32 param2, fx32 param3, fx32 param4, Sprite *param5, int param6)
{
    VecFx32 v0, v1;

    OverworldAnimManager_GetPosition(param0, &v0);
    v0.x += param3;
    v0.y += param4;
    OverworldAnimManager_SetPosition(param0, &v0);

    if (param6 == 0) {
        v1.x = param1 + v0.x;
    } else {
        v1.x = param1 - v0.x;
    }

    v1.y = param2 - v0.y;
    Sprite_SetPosition(param5, &v1);
}

static void SlotMachine_Bonus_Update(OverworldAnimManager *param0, void *param1)
{
    SlotMachineBonus *v0 = param1;

    switch (v0->state) {
    case 0:
        if (v0->loadState != 2) {
            return;
        }

        {
            VecFx32 v1 = { 0, ((FX32_ONE * 192) + (FX32_ONE * 256)), 0 };

            SlotMachineSprite_CreateSprite(v0->context->spriteManager, &v0->sprite1, &v1, (NNS_G2D_VRAM_TYPE_2DSUB), 1, 5, 5, 5, 5, 2, 4);
            SlotMachineSprite_CreateSprite(v0->context->spriteManager, &v0->sprite2, &v1, (NNS_G2D_VRAM_TYPE_2DSUB), 1, 5, 5, 5, 5, 2, 4);
            Sprite_SetFlipMode(v0->sprite2.sprite, 1);
            v0->state++;
        }
    case 1: {
        int v2 = 0;
        VecFx32 v3, v4;

        OverworldAnimManager_GetPosition(param0, &v3);

        v3.x += (FX32_ONE * 8);
        v3.y += (FX32_ONE * 8);

        if (v3.x >= (FX32_ONE * 64)) {
            v3.x = (FX32_ONE * 64);
            v2++;
        }

        if (v3.y >= (FX32_ONE * 56)) {
            v3.y = (FX32_ONE * 64);
            v2++;
        }

        OverworldAnimManager_SetPosition(param0, &v3);

        v4.x = (FX32_ONE * -32) + v3.x;
        v4.y = ((FX32_ONE * 192) + (FX32_ONE * 228)) - v3.y;

        Sprite_SetPosition(v0->sprite1.sprite, &v4);

        v4.x = (FX32_ONE * 288) - v3.x;
        v4.y = ((FX32_ONE * 192) + (FX32_ONE * 228)) - v3.y;

        Sprite_SetPosition(v0->sprite2.sprite, &v4);

        if (v2 == 2) {
            v0->state++;
        }
    } break;
    case 2:
        v0->timer++;

        if (v0->timer < 8) {
            break;
        }

        v0->timer = 0;
        v0->state++;
    case 3:
        SlotMachine_Bonus_MoveSprite(param0, (FX32_ONE * -32), ((FX32_ONE * 192) + (FX32_ONE * 228)), (FX32_ONE * -2), (FX32_ONE * -4), v0->sprite1.sprite, 0);

        v0->timer++;

        if (v0->timer >= 4) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 4:
        SlotMachine_Bonus_MoveSprite(param0, (FX32_ONE * -32), ((FX32_ONE * 192) + (FX32_ONE * 228)), (FX32_ONE * 2), (FX32_ONE * 4), v0->sprite1.sprite, 0);

        v0->timer++;

        if (v0->timer >= 4) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 5:
        SlotMachine_Bonus_MoveSprite(param0, (FX32_ONE * 288), ((FX32_ONE * 192) + (FX32_ONE * 228)), (FX32_ONE * -2), (FX32_ONE * -4), v0->sprite2.sprite, 1);

        v0->timer++;

        if (v0->timer >= 4) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 6:
        SlotMachine_Bonus_MoveSprite(param0, (FX32_ONE * 288), ((FX32_ONE * 192) + (FX32_ONE * 228)), (FX32_ONE * 2), (FX32_ONE * 4), v0->sprite2.sprite, 1);

        v0->timer++;

        if (v0->timer >= 4) {
            v0->timer = 0;

            v0->loopCount++;

            if (v0->loopCount < 2) {
                v0->state = 3;
            } else {
                v0->loopCount = 0;
                v0->state++;
            }
        }
        break;
    case 7:
        v0->timer++;

        if (v0->timer < 8) {
            break;
        }

        v0->timer = 0;
        v0->state++;
    case 8:
        SlotMachine_Bonus_MoveSprite(param0, (FX32_ONE * -32), ((FX32_ONE * 192) + (FX32_ONE * 228)), (FX32_ONE * -2), (FX32_ONE * -4), v0->sprite1.sprite, 0);
        SlotMachine_Bonus_MoveSprite(param0, (FX32_ONE * 288), ((FX32_ONE * 192) + (FX32_ONE * 228)), (FX32_ONE * 0), (FX32_ONE * 0), v0->sprite2.sprite, 1);

        v0->timer++;

        if (v0->timer >= 4) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 9:
        SlotMachine_Bonus_MoveSprite(param0, (FX32_ONE * -32), ((FX32_ONE * 192) + (FX32_ONE * 228)), (FX32_ONE * 2), (FX32_ONE * 4), v0->sprite1.sprite, 0);
        SlotMachine_Bonus_MoveSprite(param0, (FX32_ONE * 288), ((FX32_ONE * 192) + (FX32_ONE * 228)), (FX32_ONE * 0), (FX32_ONE * 0), v0->sprite2.sprite, 1);

        v0->timer++;

        if (v0->timer >= 4) {
            v0->timer = 0;

            v0->loopCount++;

            if (v0->loopCount < 2) {
                v0->state = 8;
            } else {
                v0->loopCount = 0;
                v0->state++;
            }
        }
        break;
    case 10:
        SlotMachine_Bonus_MoveSprite(param0, (FX32_ONE * -32), ((FX32_ONE * 192) + (FX32_ONE * 228)), (FX32_ONE * -8), (FX32_ONE * -8), v0->sprite1.sprite, 0);
        SlotMachine_Bonus_MoveSprite(param0, (FX32_ONE * 288), ((FX32_ONE * 192) + (FX32_ONE * 228)), (FX32_ONE * 0), (FX32_ONE * 0), v0->sprite2.sprite, 1);

        v0->timer++;

        if (v0->timer >= 4) {
            SlotMachineSprite_DeleteSprite(&v0->sprite1);
            SlotMachineSprite_DeleteSprite(&v0->sprite2);
            SlotMachineSprite_RemoveResources(v0->context->spriteManager, 5, 5, 5, 5);
        }

        v0->state++;
        v0->done = 1;
    }
}

static void SlotMachine_Bonus_Noop(OverworldAnimManager *param0, void *param1)
{
    SlotMachineBonus *v0 = param1;
}

static const OverworldAnimManagerFuncs sSlotMachineBonusFuncs = {
    sizeof(SlotMachineBonus),
    SlotMachine_Bonus_Init,
    SlotMachine_Bonus_Exit,
    SlotMachine_Bonus_Update,
    SlotMachine_Bonus_Noop
};

static const OverworldAnimManagerFuncs sSlotMachineButtonFuncs;

OverworldAnimManager *SlotMachine_CreateButton(SlotMachineContext *param0)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { (FX32_ONE * 24), ((FX32_ONE * 192) + (FX32_ONE * 8)), 0 };

    v0 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineButtonFuncs, &v1, 0, param0, 142);
    return v0;
}

static int SlotMachine_Button_Init(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    SlotMachineButton *v1 = param1;

    v1->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);

    OverworldAnimManager_GetPosition(param0, &v0);
    SlotMachineSprite_CreateSprite(v1->context->spriteManager, &v1->sprite, &v0, (NNS_G2D_VRAM_TYPE_2DSUB), 0, 6, 6, 6, 6, 2, 3);
    Sprite_SetAnimateFlag(v1->sprite.sprite, 1);

    return 1;
}

static void SlotMachine_Button_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineButton *v0 = param1;
    SlotMachineSprite_DeleteSprite(&v0->sprite);
}

static void SlotMachine_Button_Update(OverworldAnimManager *param0, void *param1)
{
    int v0 = 1;
    SlotMachineButton *v1 = param1;
    SlotMachineReelAnimTask *v2 = &v1->context->reelAnimTask;

    if (v2->spritesFinished == 1) {
        v0 = 0;
    }

    Sprite_SetDrawFlag(v1->sprite.sprite, v0);
}

static const OverworldAnimManagerFuncs sSlotMachineButtonFuncs = {
    sizeof(SlotMachineButton),
    SlotMachine_Button_Init,
    SlotMachine_Button_Exit,
    SlotMachine_Button_Update,
    OverworldAnimManager_DummyRenderFunc
};

static const OverworldAnimManagerFuncs sSlotMachineButton2Funcs;

OverworldAnimManager *SlotMachine_CreateButton2(SlotMachineContext *param0)
{
    VecFx32 v0;
    OverworldAnimManager *v1;

    v0.x = (FX32_ONE * (128 - (((6 + 5) * 8) / 2)));
    v0.y = ((FX32_ONE * 192) + (FX32_ONE * (96 + 16)));
    v1 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineButton2Funcs, &v0, 0, param0, 142);

    return v1;
}

static int SlotMachine_Button2_Init(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    VecFx32 v1 = { 0, 0, 0 };
    VecFx32 v2 = { 0x2000, 0x2000, 0 };
    SlotMachineButton2 *v3 = param1;

    v3->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);

    OverworldAnimManager_GetPosition(param0, &v0);
    SlotMachineSprite_CreateSprite(v3->context->spriteManager, &v3->sprite, &v0, (NNS_G2D_VRAM_TYPE_2DSUB), 0, 6, 6, 6, 6, 2, 3);

    Sprite_SetAffineOverwriteMode(v3->sprite.sprite, 2);
    Sprite_SetAffineTranslation(v3->sprite.sprite, &v1);
    Sprite_SetAffineScale(v3->sprite.sprite, &v2);
    Sprite_SetAffineZRotation(v3->sprite.sprite, CalcAngleRotationIdx_Wraparound(0));
    Sprite_SetAnimateFlag(v3->sprite.sprite, 1);

    return 1;
}

static void SlotMachine_Button2_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineButton2 *v0 = param1;
    SlotMachineSprite_DeleteSprite(&v0->sprite);
}

static void SlotMachine_Button2_Update(OverworldAnimManager *param0, void *param1)
{
    int v0 = 1;
    SlotMachineButton2 *v1 = param1;

    v1->timer++;

    if (v1->timer >= 45) {
        OverworldAnimManager_Finish(param0);
    }
}

static const OverworldAnimManagerFuncs sSlotMachineButton2Funcs = {
    sizeof(SlotMachineButton2),
    SlotMachine_Button2_Init,
    SlotMachine_Button2_Exit,
    SlotMachine_Button2_Update,
    OverworldAnimManager_DummyRenderFunc
};

static const OverworldAnimManagerFuncs sSlotMachineButton3Funcs;

OverworldAnimManager *SlotMachine_CreateButton3(SlotMachineContext *param0)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { (FX32_ONE * 200), ((FX32_ONE * 192) + (FX32_ONE * 184)), 0 };

    v0 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineButton3Funcs, &v1, 0, param0, 142);
    return v0;
}

static int SlotMachine_Button3_Init(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    SlotMachineButton *v1 = param1;

    v1->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);

    OverworldAnimManager_GetPosition(param0, &v0);
    SlotMachineSprite_CreateSprite(v1->context->spriteManager, &v1->sprite, &v0, (NNS_G2D_VRAM_TYPE_2DSUB), 0, 7, 6, 7, 7, 2, 3);
    Sprite_SetAnimateFlag(v1->sprite.sprite, 1);

    return 1;
}

static void SlotMachine_Button3_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineButton3 *v0 = param1;
    SlotMachineSprite_DeleteSprite(&v0->sprite);
}

static void SlotMachine_Button3_Update(OverworldAnimManager *param0, void *param1)
{
    int v0 = 1;
    SlotMachineButton3 *v1 = param1;
    SlotMachineReelAnimTask *v2 = &v1->context->reelAnimTask;

    if (v2->spritesFinished == 1) {
        v0 = 0;
    }

    Sprite_SetDrawFlag(v1->sprite.sprite, v0);
}

static const OverworldAnimManagerFuncs sSlotMachineButton3Funcs = {
    sizeof(SlotMachineButton3),
    SlotMachine_Button3_Init,
    SlotMachine_Button3_Exit,
    SlotMachine_Button3_Update,
    OverworldAnimManager_DummyRenderFunc
};

static const OverworldAnimManagerFuncs sSlotMachineButton4Funcs;

OverworldAnimManager *SlotMachine_CreateButton4(SlotMachineContext *param0)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { (FX32_ONE * 200), ((FX32_ONE * 192) + (FX32_ONE * 184)), 0 };

    v1.x = (FX32_ONE * (128 - (((10 + 5) * 8) / 2)));
    v1.y = ((FX32_ONE * 192) + (FX32_ONE * (96 - 16)));
    v0 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineButton4Funcs, &v1, 0, param0, 142);

    return v0;
}

static int SlotMachine_Button4_Init(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    VecFx32 v1 = { 0, 0, 0 };
    VecFx32 v2 = { 0x2000, 0x2000, 0 };
    SlotMachineButton4 *v3 = param1;

    v3->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);

    OverworldAnimManager_GetPosition(param0, &v0);
    SlotMachineSprite_CreateSprite(v3->context->spriteManager, &v3->sprite, &v0, (NNS_G2D_VRAM_TYPE_2DSUB), 0, 7, 6, 7, 7, 2, 3);

    Sprite_SetAffineOverwriteMode(v3->sprite.sprite, 2);
    Sprite_SetAffineTranslation(v3->sprite.sprite, &v1);
    Sprite_SetAffineScale(v3->sprite.sprite, &v2);
    Sprite_SetAffineZRotation(v3->sprite.sprite, CalcAngleRotationIdx_Wraparound(0));
    Sprite_SetAnimateFlag(v3->sprite.sprite, 1);

    return 1;
}

static void SlotMachine_Button4_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineButton4 *v0 = param1;
    SlotMachineSprite_DeleteSprite(&v0->sprite);
}

static void SlotMachine_Button4_Update(OverworldAnimManager *param0, void *param1)
{
    int v0 = 1;
    SlotMachineButton4 *v1 = param1;

    v1->timer++;

    if (v1->timer >= 45) {
        OverworldAnimManager_Finish(param0);
    }
}

static const OverworldAnimManagerFuncs sSlotMachineButton4Funcs = {
    sizeof(SlotMachineButton4),
    SlotMachine_Button4_Init,
    SlotMachine_Button4_Exit,
    SlotMachine_Button4_Update,
    OverworldAnimManager_DummyRenderFunc
};

static const OverworldAnimManagerFuncs sSlotMachineCreditDigitFuncs;

OverworldAnimManager *SlotMachine_CreateCreditDigit(SlotMachineContext *param0)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { (FX32_ONE * 14), ((FX32_ONE * 192) + (FX32_ONE * 8)), 0 };

    v0 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineCreditDigitFuncs, &v1, 0, param0, 142);
    return v0;
}

static int SlotMachine_CreditDigit_Init(OverworldAnimManager *param0, void *param1)
{
    int v0;
    VecFx32 v1;
    SlotMachineCreditDigit *v2 = param1;

    v2->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);
    OverworldAnimManager_GetPosition(param0, &v1);

    for (v0 = 0; v0 < 2; v0++) {
        SlotMachineSprite_CreateSprite(v2->context->spriteManager, &v2->sprites[v0], &v1, (NNS_G2D_VRAM_TYPE_2DSUB), 0, 8, 6, 8, 8, 2, 3);
        Sprite_SetDrawFlag(v2->sprites[v0].sprite, FALSE);
        Sprite_SetAnimateFlag(v2->sprites[v0].sprite, 1);
    }

    return 1;
}

static void SlotMachine_CreditDigit_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineCreditDigit *v0 = param1;

    SlotMachineSprite_DeleteSprite(&v0->sprites[0]);
    SlotMachineSprite_DeleteSprite(&v0->sprites[1]);
}

static void SlotMachine_CreditDigit_Update(OverworldAnimManager *param0, void *param1)
{
    SlotMachineCreditDigit *v0 = param1;
    SlotMachineReelAnimTask *v1 = &v0->context->reelAnimTask;

    Sprite_SetDrawFlag(v0->sprites[0].sprite, FALSE);
    Sprite_SetDrawFlag(v0->sprites[1].sprite, FALSE);

    if (v1->spritesFinished == 1) {
        return;
    }

    {
        VecFx32 v2 = { (FX32_ONE * 52), ((FX32_ONE * 192) + (FX32_ONE * 8)), 0 };
        u32 v3 = 0, v4, v5;

        v5 = v0->context->payoutLines;

        if (v5 > 99) {
            v5 = 99;
        }

        v4 = (v5 % 100) / 10;

        if (v4) {
            Sprite_SetPosition(v0->sprites[v3].sprite, &v2);
            Sprite_SetAnim(v0->sprites[v3].sprite, v4);
            Sprite_RestartAnim(v0->sprites[v3].sprite);
            Sprite_SetDrawFlag(v0->sprites[v3].sprite, TRUE);
            v2.x += (FX32_ONE * 8);
            v3++;
        }

        v4 = (v5 % 10);

        Sprite_SetPosition(v0->sprites[v3].sprite, &v2);
        Sprite_SetAnim(v0->sprites[v3].sprite, v4);
        Sprite_RestartAnim(v0->sprites[v3].sprite);
        Sprite_SetDrawFlag(v0->sprites[v3].sprite, TRUE);
    }
}

static const OverworldAnimManagerFuncs sSlotMachineCreditDigitFuncs = {
    sizeof(SlotMachineDigit),
    SlotMachine_CreditDigit_Init,
    SlotMachine_CreditDigit_Exit,
    SlotMachine_CreditDigit_Update,
    OverworldAnimManager_DummyRenderFunc
};

static const OverworldAnimManagerFuncs sSlotMachinePayoutDigitFuncs;

OverworldAnimManager *SlotMachine_CreatePayoutDigit(SlotMachineContext *param0)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { (FX32_ONE * 14), ((FX32_ONE * 192) + (FX32_ONE * 8)), 0 };

    v0 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachinePayoutDigitFuncs, &v1, 0, param0, 142);
    return v0;
}

static int SlotMachine_PayoutDigit_Init(OverworldAnimManager *param0, void *param1)
{
    int v0;
    VecFx32 v1 = { (FX32_ONE * 220), ((FX32_ONE * 192) + (FX32_ONE * 184)), 0 };
    SlotMachinePayoutDigit *v2 = param1;

    v2->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);

    for (v0 = 0; v0 < 5; v0++, v1.x += (FX32_ONE * 8)) {
        SlotMachineSprite_CreateSprite(v2->context->spriteManager, &v2->sprites[v0], &v1, (NNS_G2D_VRAM_TYPE_2DSUB), 0, 8, 6, 8, 8, 2, 3);
    }

    return 1;
}

static void SlotMachine_PayoutDigit_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachinePayoutDigit *v0 = param1;
    int v1;

    for (v1 = 0; v1 < 5; v1++) {
        SlotMachineSprite_DeleteSprite(&v0->sprites[v1]);
    }
}

static void SlotMachine_PayoutDigit_Update(OverworldAnimManager *param0, void *param1)
{
    int v0;
    SlotMachinePayoutDigit *v1 = param1;
    SlotMachineReelAnimTask *v2 = &v1->context->reelAnimTask;

    {
        int v3 = 1;

        if (v2->spritesFinished == 1) {
            v3 = 0;
        }

        for (v0 = 0; v0 < 5; Sprite_SetDrawFlag(v1->sprites[v0].sprite, v3), v0++) {
            (void)0;
        }

        if (v3 == 0) {
            return;
        }
    }

    {
        int v4;
        int v5 = 0, v6, v7;

        v7 = v1->context->payoutCoins;

        if (v7 > 50000) {
            v7 = 50000;
        }

        for (v4 = 10000; v4 >= 1; v4 /= 10, v5++) {
            v6 = (v7 % (v4 * 10)) / v4;
            Sprite_SetAnim(v1->sprites[v5].sprite, v6);
            Sprite_RestartAnim(v1->sprites[v5].sprite);
        }
    }
}

static const OverworldAnimManagerFuncs sSlotMachinePayoutDigitFuncs = {
    sizeof(SlotMachinePayoutDigit),
    SlotMachine_PayoutDigit_Init,
    SlotMachine_PayoutDigit_Exit,
    SlotMachine_PayoutDigit_Update,
    OverworldAnimManager_DummyRenderFunc
};

static const OverworldAnimManagerFuncs sSlotMachineNumberFuncs;

OverworldAnimManager *SlotMachine_CreateNumber(SlotMachineContext *param0, SlotMachineNumberType param1)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { 0, 0, 0 };
    u32 v2;

    v0 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineNumberFuncs, &v1, param1, param0, 142);

    return v0;
}

static int SlotMachine_Number_Init(OverworldAnimManager *param0, void *param1)
{
    int v0, v1, v2;
    VecFx32 v3;
    VecFx32 v4 = { 0, 0, 0 };
    VecFx32 v5 = { 0x2000, 0x2000, 0 };
    SlotMachineNumber *v6 = param1;
    SlotMachineContext *v7 = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);

    v6->numberType = OverworldAnimManager_GetUserInt(param0);
    v6->context = v7;

    if (v6->numberType == SlotMachineNumberType_00) {
        v6->value = v7->bonusRoundStreak;

        if (v6->value > 999) {
            v6->value = 999;
        }

        if (v6->value >= 100) {
            v6->digitCount = 3;
        } else if (v6->value >= 10) {
            v6->digitCount = 2;
        } else {
            v6->digitCount = 1;
        }

        v3.x = (FX32_ONE * (128 + (((4 + 5) * 16) / 2)));
        v3.y = ((FX32_ONE * 192) + (FX32_ONE * (96 + 16)));
    } else {
        v6->value = v7->payoutCoins;

        if (v6->value > 99999) {
            v6->value = 99999;
        }

        if (v6->value >= 10000) {
            v6->digitCount = 5;
        } else if (v6->value >= 1000) {
            v6->digitCount = 4;
        } else if (v6->value >= 100) {
            v6->digitCount = 3;
        } else if (v6->value >= 10) {
            v6->digitCount = 2;
        } else {
            v6->digitCount = 1;
        }

        v3.x = (FX32_ONE * (128 + (((4 + 5) * 16) / 2)));
        v3.y = ((FX32_ONE * 192) + (FX32_ONE * (96 - 16)));
    }

    for (v0 = 0, v1 = 1; v0 < v6->digitCount; v0++, v1 *= 10, v3.x -= (FX32_ONE * 16)) {
        SlotMachineSprite_CreateSprite(v6->context->spriteManager, &v6->sprites[v0], &v3, (NNS_G2D_VRAM_TYPE_2DSUB), 0, 8, 6, 8, 8, 2, 3);

        Sprite_SetAffineOverwriteMode(v6->sprites[v0].sprite, 2);
        Sprite_SetAffineTranslation(v6->sprites[v0].sprite, &v4);
        Sprite_SetAffineScale(v6->sprites[v0].sprite, &v5);
        Sprite_SetAffineZRotation(v6->sprites[v0].sprite, CalcAngleRotationIdx_Wraparound(0));

        v2 = (v6->value % (v1 * 10)) / v1;

        Sprite_SetAnim(v6->sprites[v0].sprite, v2);
        Sprite_RestartAnim(v6->sprites[v0].sprite);
    }

    v6->spriteCount = v0;
    return 1;
}

static void SlotMachine_Number_Exit(OverworldAnimManager *param0, void *param1)
{
    int v0;
    SlotMachineNumber *v1 = param1;

    for (v0 = 0; v0 < v1->spriteCount; v0++) {
        SlotMachineSprite_DeleteSprite(&v1->sprites[v0]);
    }
}

static void SlotMachine_Number_Update(OverworldAnimManager *param0, void *param1)
{
    int v0;
    SlotMachineNumber *v1 = param1;

    v1->timer++;

    if (v1->timer >= 45) {
        OverworldAnimManager_Finish(param0);
    }
}

static const OverworldAnimManagerFuncs sSlotMachineNumberFuncs = {
    sizeof(SlotMachineNumber),
    SlotMachine_Number_Init,
    SlotMachine_Number_Exit,
    SlotMachine_Number_Update,
    OverworldAnimManager_DummyRenderFunc
};

static const OverworldAnimManagerFuncs sSlotMachineNumber2Funcs;

OverworldAnimManager *SlotMachine_CreateNumber2(SlotMachineContext *param0, u32 param1)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { (FX32_ONE * 128), ((FX32_ONE * 192) + (FX32_ONE * 32)), 0 };

    if (param1 > 999) {
        param1 = 999;
    }

    v0 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineNumber2Funcs, &v1, param1, param0, 142);
    return v0;
}

static int SlotMachine_Number2_Init(OverworldAnimManager *param0, void *param1)
{
    int v0;
    u32 v1, v2, v3;
    VecFx32 v4;
    SlotMachineNumber2 *v5 = param1;

    v5->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);
    v1 = OverworldAnimManager_GetUserInt(param0);

    OverworldAnimManager_GetPosition(param0, &v4);

    if (v1 >= 100) {
        v2 = 100;
        v5->digitCount = 3;
        v4.x -= (FX32_ONE * 16);
    } else if (v1 >= 10) {
        v2 = 10;
        v5->digitCount = 2;
        v4.x -= (FX32_ONE * 8);
    } else {
        v2 = 1;
        v5->digitCount = 1;
    }

    for (v0 = 0; v0 < v5->digitCount; v0++, v4.x += (FX32_ONE * 16), v2 /= 10) {
        SlotMachineSprite_CreateSprite(v5->context->spriteManager, &v5->sprites[v0], &v4, (NNS_G2D_VRAM_TYPE_2DSUB), 0, 9, 7, 9, 9, 2, 3);

        v3 = (v1 % (v2 * 10)) / v2;
        Sprite_SetAnim(v5->sprites[v0].sprite, v3);
    }

    return 1;
}

static void SlotMachine_Number2_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachineNumber2 *v0 = param1;
    int v1;

    for (v1 = 0; v1 < v0->digitCount; v1++) {
        SlotMachineSprite_DeleteSprite(&v0->sprites[v1]);
    }
}

static void SlotMachine_Number2_Update(OverworldAnimManager *param0, void *param1)
{
    int v0;
    SlotMachineNumber2 *v1 = param1;

    v1->timer++;

    if (v1->timer >= 60) {
        OverworldAnimManager_Finish(param0);
    }
}

static const OverworldAnimManagerFuncs sSlotMachineNumber2Funcs = {
    sizeof(SlotMachineNumber2),
    SlotMachine_Number2_Init,
    SlotMachine_Number2_Exit,
    SlotMachine_Number2_Update,
    OverworldAnimManager_DummyRenderFunc
};

static const OverworldAnimManagerFuncs sSlotMachineJackpotFuncs;

OverworldAnimManager *SlotMachine_CreateJackpot(SlotMachineContext *param0)
{
    VecFx32 v0 = { 0, 0, 0 };
    OverworldAnimManager *v1 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachineJackpotFuncs, &v0, 0, param0, 140);

    return v1;
}

static const VecFx32 sSlotMachineJackpotPositions[SlotMachinePaletteIndex_05][3] = {
    {
        { (FX32_ONE * 68), ((FX32_ONE * 16) + (FX32_ONE * (32 * 2))), 0x0 },
        { (FX32_ONE * 128), ((FX32_ONE * 16) + (FX32_ONE * (32 * 2))), 0x0 },
        { (FX32_ONE * 188), ((FX32_ONE * 16) + (FX32_ONE * (32 * 2))), 0x0 },
    },
    {
        { (FX32_ONE * 68), ((FX32_ONE * 16) + (FX32_ONE * (32 * 1))), 0x0 },
        { (FX32_ONE * 128), ((FX32_ONE * 16) + (FX32_ONE * (32 * 1))), 0x0 },
        { (FX32_ONE * 188), ((FX32_ONE * 16) + (FX32_ONE * (32 * 1))), 0x0 },
    },
    {
        { (FX32_ONE * 68), ((FX32_ONE * 16) + (FX32_ONE * (32 * 3))), 0x0 },
        { (FX32_ONE * 128), ((FX32_ONE * 16) + (FX32_ONE * (32 * 3))), 0x0 },
        { (FX32_ONE * 188), ((FX32_ONE * 16) + (FX32_ONE * (32 * 3))), 0x0 },
    },
    {
        { (FX32_ONE * 68), ((FX32_ONE * 16) + (FX32_ONE * (32 * 1))), 0x0 },
        { (FX32_ONE * 128), ((FX32_ONE * 16) + (FX32_ONE * (32 * 2))), 0x0 },
        { (FX32_ONE * 188), ((FX32_ONE * 16) + (FX32_ONE * (32 * 3))), 0x0 },
    },
    {
        { (FX32_ONE * 68), ((FX32_ONE * 16) + (FX32_ONE * (32 * 3))), 0x0 },
        { (FX32_ONE * 128), ((FX32_ONE * 16) + (FX32_ONE * (32 * 2))), 0x0 },
        { (FX32_ONE * 188), ((FX32_ONE * 16) + (FX32_ONE * (32 * 1))), 0x0 },
    },
};

static int SlotMachine_Jackpot_Init(OverworldAnimManager *param0, void *param1)
{
    u32 v0;
    SlotMachineJackpot *v1 = param1;

    v1->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);
    v1->symbol = v1->context->winSymbol;

    v0 = v1->context->winLineMask;

    do {
        if (v0 & 0x1) {
            break;
        }

        v0 >>= 1;
        v1->paletteIndex++;
    } while (v1->paletteIndex < SlotMachinePaletteIndex_05);

    GF_ASSERT(v1->paletteIndex < SlotMachinePaletteIndex_05);

    SlotMachine_Jackpot_LoadResources(v1);
    return 1;
}

static void SlotMachine_Jackpot_Exit(OverworldAnimManager *param0, void *param1)
{
    int v0;
    SlotMachineJackpot *v1 = param1;

    if (v1->resourcesRemoved == 0) {
        for (v0 = 0; v0 < 3; v0++) {
            if (v1->sprites[v0].sprite != NULL) {
                SlotMachineSprite_DeleteSprite(&v1->sprites[v0]);
            }
        }

        SlotMachineSprite_RemoveResources(v1->context->spriteManager, 10, 8, 10, 10);
    }
}

static void SlotMachine_Jackpot_Update(OverworldAnimManager *param0, void *param1)
{
    int v0, v1;
    VecFx32 v2;
    SlotMachineJackpot *v3 = param1;

    switch (v3->state) {
    case 0:
        if (v3->loadState != 2) {
            break;
        }

        for (v0 = 0; v0 < 3; v0++) {
            v2 = sSlotMachineJackpotPositions[v3->paletteIndex][v0];
            SlotMachineSprite_CreateSprite(v3->context->spriteManager, &v3->sprites[v0], &v2, (NNS_G2D_VRAM_TYPE_2DBOTH), 0, 10, 0, 10, 10, 1, 0);
            Sprite_SetAnimateFlag(v3->sprites[v0].sprite, 1);
        }

        v3->state++;
        break;
    case 1:
        for (v0 = 0, v1 = 0; v0 < 3; v0++) {
            SlotMachineSprite_GetPosition(v3->sprites[v0].sprite, &v2);
            v2.y += (FX32_ONE * 4);

            if (v2.y >= ((FX32_ONE * 192) + (FX32_ONE * 48))) {
                v2.y = ((FX32_ONE * 192) + (FX32_ONE * 48));
            } else {
                v1 = 1;
            }

            Sprite_SetPosition(v3->sprites[v0].sprite, &v2);
        }

        if (v1 == 0) {
            v3->state++;
        }
        break;
    case 2:
        v3->timer++;

        if (v3->timer >= 30) {
            v3->timer = 0;
            v3->state++;
        }
        break;
    case 3:
        v3->timer++;

        if (v3->timer < 12) {
            v1 = 0;
        } else {
            v1 = 1;
        }

        for (v0 = 0; v0 < 3; v0++) {
            Sprite_SetDrawFlag(v3->sprites[v0].sprite, v1);
        }

        if (v3->timer >= 30) {
            v3->timer = 0;
            v3->flashCount++;

            if (v3->flashCount >= 3) {
                v3->flashCount = 0;
                v3->state++;
            }
        }
        break;
    case 4:
        v3->timer++;

        if (v3->timer >= 30) {
            v3->timer = 0;
            v3->state++;
        }
        break;
    case 5:
        for (v0 = 0; v0 < 3; v0++) {
            SlotMachineSprite_DeleteSprite(&v3->sprites[v0]);
        }

        SlotMachineSprite_RemoveResources(v3->context->spriteManager, 10, 8, 10, 10);

        v3->state++;
        v3->finished = 1;
        v3->resourcesRemoved = 1;
    }
}

static const OverworldAnimManagerFuncs sSlotMachineJackpotFuncs = {
    sizeof(SlotMachineJackpot),
    SlotMachine_Jackpot_Init,
    SlotMachine_Jackpot_Exit,
    SlotMachine_Jackpot_Update,
    OverworldAnimManager_DummyRenderFunc
};

static void SlotMachine_Jackpot_RequestChar(SysTask *param0, void *param1)
{
    SlotMachineJackpot *v0 = param1;
    SlotMachineContext *v1 = v0->context;

    SlotMachineSprite_RequestChar(v1->spriteManager, 10);
    v0->loadState = 1;
    SysTask_Done(param0);
}

static void SlotMachine_Jackpot_ReleaseChar(SysTask *param0, void *param1)
{
    SlotMachineJackpot *v0 = param1;
    SlotMachineContext *v1 = v0->context;

    if (v0->loadState == 1) {
        SlotMachineSprite_ReleaseChar(v1->spriteManager, 10);
        v0->loadState = 2;
        SysTask_Done(param0);
    }
}

static void SlotMachine_Jackpot_LoadResources(SlotMachineJackpot *param0)
{
    SysTask *v0;
    SlotMachineContext *v1 = param0->context;

    if (param0->symbol == 0) {
        SlotMachineSprite_AddTiles(v1->spriteManager, (NNS_G2D_VRAM_TYPE_2DBOTH), v1->narc, 14, 10);
        SlotMachineSprite_AddCell(v1->spriteManager, v1->narc, 15, 10);
        SlotMachineSprite_AddAnim(v1->spriteManager, v1->narc, 16, 10);
    } else {
        SlotMachineSprite_AddTiles(v1->spriteManager, (NNS_G2D_VRAM_TYPE_2DBOTH), v1->narc, 17, 10);
        SlotMachineSprite_AddCell(v1->spriteManager, v1->narc, 18, 10);
        SlotMachineSprite_AddAnim(v1->spriteManager, v1->narc, 19, 10);
    }

    v0 = SysTask_ExecuteOnVBlank(SlotMachine_Jackpot_RequestChar, param0, 257);
    GF_ASSERT(v0 != NULL);
    v0 = SysTask_ExecuteAfterVBlank(SlotMachine_Jackpot_ReleaseChar, param0, 257);
    GF_ASSERT(v0 != NULL);
}

static const int sSlotMachineReelSymbolAnim[6] = {
    0x0,
    0x1,
    0x2,
    0x3,
    0x4,
    0x5
};

static const fx32 sSlotMachinePayoutDigitOffset[10] = {
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0)
};

static const fx32 sSlotMachineCreditDigitOffset[10] = {
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0),
    (FX32_ONE * 0)
};

static const SlotMachineSpriteResources sSlotMachineReelResources[SlotMachineReelType_05] = {
    { 0x18, 0x1B, 0x19, 0x1A },
    { 0x1C, 0x1F, 0x1D, 0x1E },
    { 0x20, 0x23, 0x21, 0x22 },
    { 0x24, 0x27, 0x25, 0x26 },
    { 0x28, 0x2B, 0x29, 0x2A }
};

static const SlotMachineSpriteResources sSlotMachineWinSymbolResources[SlotMachineWinType_03] = {
    { 0x30, 0x33, 0x31, 0x32 },
    { 0x34, 0x33, 0x35, 0x36 },
    { 0x30, 0x37, 0x31, 0x32 }
};
