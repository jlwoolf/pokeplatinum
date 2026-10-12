#include "spin_trade/spin_trade.h"

#include <nitro.h>
#include <string.h>

#include "generated/game_records.h"
#include "generated/journal_online_events.h"
#include "generated/text_banks.h"
#include "generated/trainer_score_events.h"

#include "struct_defs/struct_0209BDF8.h"
#include "struct_defs/struct_0209C0F0.h"
#include "struct_defs/struct_0209C194.h"

#include "spin_trade/struct_spin_trade_order.h"
#include "spin_trade/struct_spin_trade_result.h"

#include "bag.h"
#include "bg_window.h"
#include "camera.h"
#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "font.h"
#include "game_records.h"
#include "gx_layers.h"
#include "heap.h"
#include "journal.h"
#include "math_util.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "palette.h"
#include "party.h"
#include "pokemon.h"
#include "render_window.h"
#include "screen_fade.h"
#include "simple3d.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "touch_pad.h"
#include "trainer_info.h"
#include "g3_buffer.h"
#include "comm_tool.h"
#include "comm_sync_save.h"
#include "pokemon_info_display.h"
#include "union_room_comm.h"
#include "vram_transfer.h"

typedef struct {
    VecFx32 unk_00;
    VecFx32 unk_0C;
    VecFx32 unk_18;
    VecFx32 unk_24;
    VecFx32 unk_30;
    fx32 unk_3C;
    fx32 unk_40;
    fx32 unk_44;
    fx32 unk_48;
    Simple3DRotationAngles unk_4C;
    Simple3DModel unk_54;
    Simple3DRenderObj unk_68;
} SpinTradeEggModel;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    fx32 unk_1C;
    fx32 unk_20;
    Simple3DRotationAngles unk_24;
    VecFx32 unk_2C;
    VecFx32 unk_38;
    VecFx32 unk_44;
    VecFx32 unk_50;
    Simple3DRenderObj unk_5C;
} SpinTradeMonModel;

typedef struct {
    int unk_00;
    Simple3DRotationAngles unk_04;
    VecFx32 unk_0C;
    VecFx32 unk_18;
    Simple3DRenderObj unk_24;
    SpinTradeMonModel *unk_78;
} SpinTradeMonShadow;

typedef struct {
    int unk_00;
    VecFx32 unk_04;
    Simple3DRenderObj unk_10;
    SpinTradeMonModel *unk_64;
} SpinTradeMonAnim;

typedef struct {
    Simple3DModel unk_00;
    Simple3DModel unk_14;
    Simple3DModel unk_28[5];
    Simple3DAnimation unk_8C[5];
    SpinTradeMonModel unk_140[5];
    SpinTradeMonShadow unk_4B0[5];
    SpinTradeMonAnim unk_71C[5];
} SpinTradeModels;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    fx32 unk_0C;
    SpinTradeMonModel *unk_10;
    SpinTrade *unk_14;
} SpinTradeMonDropTask;

typedef struct {
    int unk_00;
    MessageLoader *unk_04;
    StringTemplate *unk_08;
    Window unk_0C[1];
    Window unk_1C[5];
    void *unk_6C;
} SpinTradeWindows;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
} SpinTradeSpinOrder;

typedef struct {
    fx32 unk_00;
    u32 unk_04;
    VecFx32 unk_08;
    CameraAngle cameraAngle;
    Camera *camera;
} SpinTradeCamera;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    TouchPadDataBuffer unk_10;
} SpinTradeTouchInput;

typedef struct {
    SpinTrade *unk_00;
    int unk_04;
    u32 unk_08;
} SpinTradeFadeTask;

typedef struct {
    u16 min;
    u16 max;
} SpinTradeRange;

typedef struct {
    int count;
    const SpinTradeRange *ranges;
} SpinTradeRangeSet;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    fx32 unk_10;
    fx32 unk_14;
    fx32 unk_18;
    SpinTradeMonModel *unk_1C;
} SpinTradeBounceTask;

typedef struct {
    SpinTradeBounceTask unk_00[5];
} SpinTradeBounceTasks;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    fx32 unk_0C;
    SpinTradeMonModel *unk_10;
} SpinTradeShakeTask;

typedef struct {
    SpinTradeShakeTask unk_00[5];
} SpinTradeShakeTasks;

typedef struct {
    int unk_00;
    int unk_04;
    fx32 unk_08;
    fx32 unk_0C;
    fx32 unk_10;
    SpinTradeMonModel *unk_14;
} SpinTradeWobbleTask;

typedef struct {
    SpinTradeWobbleTask unk_00[5];
} SpinTradeWobbleTasks;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    fx32 unk_10;
} SpinTradeIntroTask;

typedef struct {
    u16 unk_00;
    u16 unk_02;
    int unk_04;
} SpinTradeFlashTask;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    SpinTradeMonModel *unk_0C;
} SpinTradeBobTask;

typedef struct {
    SpinTradeBobTask unk_00[5];
} SpinTradeBobTasks;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18[5];
    UnionRoomCommSpinTradePos unk_2C;
    SpinTradeResult unk_34;
    SpinTradeOrder unk_44[5];
    TrainerInfo *unk_58[5];
    String *unk_6C[5];
} SpinTradeCommState;

typedef struct SpinTrade_t {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    u32 unk_20;
    Party *unk_24;
    SpinTradeMonModel *unk_28;
    SpinTradeCommState unk_2C;
    u8 unk_AC[32];
    UnionRoomSpinTradeSession *unk_CC;
    UnionRoomComm *unk_D0;
    SpinTradeEggModel unk_D4;
    SpinTradeModels unk_190;
    SpinTradeBounceTasks unk_AB4;
    SpinTradeShakeTasks unk_B54;
    SpinTradeWobbleTasks unk_BB8;
    SpinTradeIntroTask unk_C30;
    SpinTradeFlashTask unk_C44;
    SpinTradeBobTasks unk_C4C;
    SpinTradeWindows unk_C9C;
    SpinTradeCamera unk_D0C;
    SpinTradeTouchInput unk_D2C;
    NARC *unk_D80;
    BgConfig *unk_D84;
    NNSG2dScreenData *unk_D88;
    NNSG2dCharacterData *unk_D8C;
    NNSG2dPaletteData *unk_D90;
    SpriteSystem *unk_D94;
    SpriteManager *unk_D98;
    PaletteData *unk_D9C;
    GXRgb unk_DA0[8];
    SysTask *unk_DB0;
    SysTask *unk_DB4;
    SysTask *unk_DB8;
    SysTask *unk_DBC;
    SysTask *unk_DC0;
    SysTask *unk_DC4;
    void *unk_DC8;
} SpinTrade;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    SpinTrade *unk_10;
    ManagedSprite *unk_14;
} SpinTradeSparkleTask;

static void SpinTrade_ResetCommFlags(SpinTrade *param0);
static void SpinTrade_VBlankCallback(void *param0);
static void SpinTrade_InitGraphics(SpinTrade *param0);
static void SpinTrade_FreeGraphics(SpinTrade *param0);
static void SpinTrade_DrawFrame(SpinTrade *param0);
static void SpinTrade_SetGXBanks(SpinTrade *param0);
static void SpinTrade_EnableLayers(SpinTrade *param0);
static void SpinTrade_DisableLayers(SpinTrade *param0);
static void SpinTrade_InitG3D(SpinTrade *param0);
static void SpinTrade_InitBg(SpinTrade *param0);
static void SpinTrade_LoadGraphics(SpinTrade *param0);
static void SpinTrade_FreeBg(SpinTrade *param0);
static void SpinTrade_ShowTilemapA(SpinTrade *param0);
static void SpinTrade_ShowTilemapB(SpinTrade *param0);
static void SpinTrade_ShowTilemapC(SpinTrade *param0);
static void SpinTrade_InitPalette(SpinTrade *param0);
static void SpinTrade_FreePalette(SpinTrade *param0);
static void SpinTrade_SetPaletteBlend(SpinTrade *param0, u32 param1);
static void SpinTrade_InitSprites(SpinTrade *param0);
static void SpinTrade_LoadSpriteResources(SpinTrade *param0);
static void SpinTrade_FreeSprites(SpinTrade *param0);
static ManagedSprite *SpinTrade_NewSprite(SpinTrade *param0, const SpriteTemplate *param1);
static void SpinTrade_InitWindows(SpinTrade *param0);
static void SpinTrade_FreeWindows(SpinTrade *param0);
static void SpinTrade_ShowMessage(SpinTrade *param0, u32 param1);
static void SpinTrade_ShowMessageWithTrainer(SpinTrade *param0, u32 param1, const TrainerInfo *param2);
static void SpinTrade_ShowMessageWithItem(SpinTrade *param0, u32 param1, u32 param2);
static void SpinTrade_EraseMessage(SpinTrade *param0);
static void SpinTrade_AddPlayerWindows(SpinTrade *param0, int param1);
static void SpinTrade_RemovePlayerWindows(SpinTrade *param0);
static void SpinTrade_DrawPlayerName(SpinTrade *param0, String *param1, int param2, TextColor param3);
static void SpinTrade_DrawPlayerNameColored(SpinTrade *param0, String *param1, int param2, int param3);
static void SpinTrade_ErasePlayerWindow(SpinTrade *param0, int param1);
static void SpinTrade_InitCamera(SpinTrade *param0);
static void SpinTrade_FreeCamera(SpinTrade *param0);
static void SpinTrade_UpdateTouchInput(SpinTrade *param0);
static BOOL SpinTrade_IsCenterTouched(SpinTrade *param0);
static void SpinTrade_LoadEggModel(SpinTrade *param0);
static void SpinTrade_FreeEggModel(SpinTrade *param0);
static void SpinTrade_UpdateEggModel(SpinTrade *param0);
static void SpinTrade_DrawEggModel(SpinTrade *param0);
static void SpinTrade_AdvanceEggRotation(SpinTradeEggModel *param0, fx32 param1);
static void SpinTrade_LoadModels(SpinTrade *param0);
static void SpinTrade_FreeModels(SpinTrade *param0);
static void SpinTrade_LoadMonModels(SpinTrade *param0);
static void SpinTrade_FreeMonModels(SpinTrade *param0);
static void SpinTrade_CreateMonRenderObj(SpinTrade *param0, SpinTradeMonModel *param1);
static void SpinTrade_UpdateMonModels(SpinTrade *param0);
static void SpinTrade_DrawMonModels(SpinTrade *param0);
static void SpinTrade_AdvanceMonRotation(SpinTrade *param0, fx32 param1);
static void SpinTrade_UpdateMonPosition(SpinTradeMonModel *param0, const VecFx32 *param1);
static SpinTradeMonModel *SpinTrade_GetLeadingMon(SpinTrade *param0);
static void SpinTrade_CreateMonShadow(SpinTrade *param0, SpinTradeMonModel *param1);
static void SpinTrade_UpdateMonShadow(SpinTrade *param0, SpinTradeMonShadow *param1);
static void SpinTrade_CreateMonAnim(SpinTrade *param0, SpinTradeMonModel *param1);
static void SpinTrade_UpdateMonAnim(SpinTrade *param0, SpinTradeMonAnim *param1);
static SysTask *SpinTrade_StartMonDropTask(SpinTrade *param0, int param1, int param2, int param3, int param4, int param5, SpinTradeMonModel *param6);
static void SpinTrade_MonDropTask(SysTask *param0, void *param1);
static void SpinTrade_InitBounceTasks(SpinTrade *param0);
static void SpinTrade_FreeBounceTasks(SpinTrade *param0);
static void SpinTrade_StartAllBounceTasks(SpinTrade *param0);
static BOOL SpinTrade_AreBounceTasksActive(SpinTrade *param0);
static void SpinTrade_InitShakeTasks(SpinTrade *param0);
static void SpinTrade_FreeShakeTasks(SpinTrade *param0);
static void SpinTrade_StartShakeTask(SpinTrade *param0, SpinTradeMonModel *param1);
static void SpinTrade_InitWobbleTasks(SpinTrade *param0);
static void SpinTrade_FreeWobbleTasks(SpinTrade *param0);
static void SpinTrade_StartWobbleTask(SpinTrade *param0, SpinTradeMonModel *param1);
static void SpinTrade_InitIntroTask(SpinTrade *param0);
static void SpinTrade_FreeIntroTask(SpinTrade *param0);
static void SpinTrade_StartIntroTask(SpinTrade *param0);
static BOOL SpinTrade_IsIntroTaskRunning(SpinTrade *param0);
static BOOL SpinTrade_IsIntroTaskDone(SpinTrade *param0);
static void SpinTrade_InitFlashTask(SpinTrade *param0);
static void SpinTrade_FreeFlashTask(SpinTrade *param0);
static BOOL SpinTrade_IsFlashTaskRunning(SpinTrade *param0);
static void SpinTrade_StartFlashTask(SpinTrade *param0);
static void SpinTrade_InitBobTasks(SpinTrade *param0);
static void SpinTrade_FreeBobTasks(SpinTrade *param0);
static void SpinTrade_StartBobTask(SpinTrade *param0, SpinTradeMonModel *param1);
static void SpinTrade_StartAllBobTasks(SpinTrade *param0);
static SysTask *SpinTrade_StartSparkleTask(SpinTrade *param0);
static void SpinTrade_StartFadeTask(SpinTrade *param0, int param1);
static void SpinTrade_AddRotation(fx32 *param0, fx32 param1);
static void SpinTrade_AdvanceRotation(SpinTrade *param0, fx32 param1);
static BOOL SpinTrade_UpdateSpinTimer(SpinTrade *param0);
static void *SpinTrade_LoadNarcMember(SpinTrade *param0, u32 param1, BOOL param2);
static void *SpinTrade_GetSendBuffer(SpinTrade *param0, u32 param1);
static void *SpinTrade_GetSendBufferPtr(SpinTrade *param0);
static BOOL SpinTrade_CheckStageFlag(SpinTrade *param0, u16 param1);
static BOOL SpinTrade_AreAllParticipantsConnected(SpinTrade *param0);
static int SpinTrade_CountParticipants(SpinTrade *param0);
static BOOL SpinTrade_IsNetIdConnected(SpinTrade *param0, int param1);
static void SpinTrade_CopyReceivedMon(SpinTrade *param0, int param1);
static int SpinTrade_CountReceivedTrainerData(SpinTrade *param0);
static BOOL SpinTrade_IsInRange(SpinTrade *param0, fx32 param1, int param2);
static BOOL SpinTrade_HasBadEgg(Party *param0);
static BOOL SpinTrade_AnyBadEgg(SpinTrade *param0);
static int SpinTrade_CountEggOk(SpinTrade *param0);
static BOOL SpinTrade_HasBadEggFlag(SpinTrade *param0);

static const WindowTemplate sMessageWindowTemplate[1];
static const WindowTemplate *const sPlayerWindowTemplates[5 + 1];
static const u16 sPlayerStartAngles[5 + 1][5];
static const u16 sPlayerTargetAngles[5 + 1][5];
static const SpinTradeRangeSet sRangeSets[5 + 1];
static const u32 sItemRanges[5 + 1][2];
static const u32 sEggModelIndices[5 + 1];
static const fx32 sEggModelAngles[5 + 1];
static int (*const sStateHandlers[54])(SpinTrade *);
static int (*const sMonDropStateHandlers[3])(SpinTradeMonDropTask *);

int SpinTrade_Init(ApplicationManager *appMan, int *param1)
{
    SpinTrade *v0;
    UnionRoomSpinTradeSession *v1 = ApplicationManager_Args(appMan);

    CommManager_SetErrorHandling(1, 1);
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    ResetLock(RESET_LOCK_0x2);
    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_95, 0x80000);

    v0 = ApplicationManager_NewData(appMan, sizeof(SpinTrade), HEAP_ID_95);
    memset(v0, 0, sizeof(SpinTrade));

    v1->spinAppData = v0;
    v0->unk_CC = v1;
    v0->unk_D0 = v1->comm;
    v0->unk_24 = SaveData_GetParty(v0->unk_CC->context.saveData);
    v0->unk_D80 = NARC_ctor(NARC_INDEX_DATA__GURU2, HEAP_ID_95);

    VramTransfer_New(8, HEAP_ID_95);
    EnableTouchPad();
    InitializeTouchPad(4);
    SpinTrade_InitGraphics(v0);
    SetVBlankCallback(SpinTrade_VBlankCallback, v0);
    SpinTrade_LoadEggModel(v0);
    SpinTrade_LoadModels(v0);

    {
        int v2 = 0, v3 = 0;
        int v4 = CommSys_CurNetId();
        SpinTradeEggModel *v5 = &v0->unk_D4;

        do {
            if (v0->unk_CC->connectedBitmap & (1 << v2)) {
                if (v2 == v4) {
                    break;
                }

                v3++;
            }

            v2++;
        } while (v2 < 5);

        v5->unk_40 = (FX32_ONE * (sPlayerStartAngles[v0->unk_CC->connectedCount][v3]));
    }

    v0->unk_1C = Sound_GetCurrentBGM();

    SpinTrade_InitBounceTasks(v0);
    SpinTrade_InitShakeTasks(v0);
    SpinTrade_InitWobbleTasks(v0);
    SpinTrade_InitIntroTask(v0);
    SpinTrade_InitFlashTask(v0);
    SpinTrade_InitBobTasks(v0);
    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 8, 1, HEAP_ID_95);

    return 1;
}

int SpinTrade_Exit(ApplicationManager *appMan, int *param1)
{
    SpinTrade *v0 = ApplicationManager_Data(appMan);

    if (DisableTouchPad() != 1) {
        GF_ASSERT(FALSE);
    }

    SpinTrade_FreeBounceTasks(v0);
    SpinTrade_FreeShakeTasks(v0);
    SpinTrade_FreeWobbleTasks(v0);
    SpinTrade_FreeIntroTask(v0);
    SpinTrade_FreeFlashTask(v0);
    SpinTrade_FreeBobTasks(v0);
    SpinTrade_FreeEggModel(v0);
    SpinTrade_FreeModels(v0);
    SpinTrade_FreeGraphics(v0);

    SetVBlankCallback(NULL, NULL);
    VramTransfer_Free();
    NARC_dtor(v0->unk_D80);
    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_95);
    ResetUnlock(RESET_LOCK_0x2);

    return 1;
}

int SpinTrade_Main(ApplicationManager *appMan, int *param1)
{
    int v0;
    SpinTrade *v1 = ApplicationManager_Data(appMan);

    SpinTrade_UpdateTouchInput(v1);

    do {
        v0 = sStateHandlers[v1->unk_00](v1);
    } while (v0 == 1);

    if (v0 == 2) {
        return 1;
    }

    SpinTrade_UpdateEggModel(v1);
    SpinTrade_UpdateMonModels(v1);
    SpinTrade_DrawFrame(v1);
    SpinTrade_ResetCommFlags(v1);

    return 0;
}

static void SpinTrade_ResetCommFlags(SpinTrade *param0)
{
    param0->unk_2C.unk_08 = 0;
    param0->unk_2C.unk_10 = 0;
}

static int SpinTrade_State0(SpinTrade *param0)
{
    SpinTrade_ShowMessage(param0, 0);
    param0->unk_00 = 1;
    return 0;
}

static int SpinTrade_State1(SpinTrade *param0)
{
    if (IsScreenFadeDone()) {
        if (CommSys_CurNetId() == 0) {
            param0->unk_00 = 2;
        } else {
            param0->unk_00 = 8;
        }

        return 1;
    }

    return 0;
}

static int SpinTrade_State2(SpinTrade *param0)
{
    if (SpinTrade_AreAllParticipantsConnected(param0)) {
        param0->unk_00 = 3;
        return 1;
    }

    return 0;
}

static int SpinTrade_State3(SpinTrade *param0)
{
    u16 v0 = (1 << 0);

    if (UnionRoomComm_Send(param0->unk_D0, 8, &v0, 2) == 1) {
        param0->unk_00 = 4;
        return 1;
    }

    return 0;
}

static int SpinTrade_State4(SpinTrade *param0)
{
    int v0 = SpinTrade_CountParticipants(param0) + 1;

    if (v0 != CommSys_ConnectedCount()) {
        return 0;
    }

    param0->unk_00 = 5;
    return 1;
}

static int SpinTrade_State5(SpinTrade *param0)
{
    int v0;

    param0->unk_2C.unk_04 = SpinTrade_CountParticipants(param0) + 1;

    v0 = UnionRoomComm_Send(param0->unk_D0, 13, &param0->unk_2C.unk_04, 4);

    if (v0 == 1) {
        param0->unk_14 = 0;
        param0->unk_00 = 6;
    }

    return 0;
}

static int SpinTrade_State6(SpinTrade *param0)
{
    int v0;
    SpinTradeOrder v1;

    if (param0->unk_14 == 0) {
        v1.netId = 0;
        v1.slot = 0;

        v0 = UnionRoomComm_Send(param0->unk_D0, 12, &v1, sizeof(SpinTradeOrder));

        if (v0 == 1) {
            param0->unk_14++;
        }

        return 0;
    }

    {
        int v2 = 1, v3 = 1;
        u32 v4 = param0->unk_D0->participantBitmap;

        do {
            if (v4 & (1 << v2)) {
                if (v3 >= param0->unk_14) {
                    v1.netId = v2;
                    v1.slot = param0->unk_14;

                    v0 = UnionRoomComm_Send(param0->unk_D0, 12, &v1, sizeof(SpinTradeOrder));

                    if (v0 == 1) {
                        param0->unk_14++;
                    }
                    break;
                }

                v3++;
            }

            v2++;
        } while (v2 < 5);
    }

    if (param0->unk_14 >= param0->unk_2C.unk_04) {
        param0->unk_00 = 7;
    }

    return 0;
}

static int SpinTrade_State7(SpinTrade *param0)
{
    u16 v0 = (1 << 3);

    if (UnionRoomComm_Send(param0->unk_D0, 8, &v0, 2) == 1) {
        param0->unk_00 = 10;
    }

    return 0;
}

static int SpinTrade_State8(SpinTrade *param0)
{
    int v0 = UnionRoomComm_Send(param0->unk_D0, 9, NULL, 0);

    if (v0 == 1) {
        param0->unk_10 = 0;
        param0->unk_00 = 9;
        return 0;
    }

    return 0;
}

static int SpinTrade_State9(SpinTrade *param0)
{
    if (SpinTrade_CheckStageFlag(param0, 1 << 3) == 1) {
        GF_ASSERT(param0->unk_2C.unk_04 >= 2);
        GF_ASSERT(param0->unk_2C.unk_00 != 0);
        param0->unk_00 = 10;
    }

    return 0;
}

static int SpinTrade_State10(SpinTrade *param0)
{
    CommTiming_StartSync(202);
    param0->unk_00 = 11;
    return 0;
}

static int SpinTrade_State11(SpinTrade *param0)
{
    if (CommTiming_IsSyncState(202)) {
        param0->unk_00 = 12;
    }

    return 0;
}

static int SpinTrade_State12(SpinTrade *param0)
{
    if (UnionRoomComm_Send(param0->unk_D0, 14, &param0->unk_CC->selectedMonSlot, 4)) {
        param0->unk_00 = 13;
    }

    return 0;
}

static int SpinTrade_State13(SpinTrade *param0)
{
    int v0;
    u32 v1 = (u32)param0->unk_24;
    v0 = CommSys_SendDataHuge(131, (void *)v1, 236 * 6 + 4 * 2);

    if (v0) {
        param0->unk_00 = 14;
    }

    return 0;
}

static int SpinTrade_State14(SpinTrade *param0)
{
    if (SpinTrade_CountReceivedTrainerData(param0) == param0->unk_2C.unk_04) {
        if (SpinTrade_AnyBadEgg(param0) == 1) {
            UnionRoomComm_Send(param0->unk_D0, 16, NULL, 0);
            param0->unk_00 = 46;
        } else {
            UnionRoomComm_Send(param0->unk_D0, 17, NULL, 0);
            param0->unk_00 = 15;
        }
    }

    return 0;
}

static int SpinTrade_State15(SpinTrade *param0)
{
    if (SpinTrade_HasBadEggFlag(param0) == 1) {
        param0->unk_00 = 46;
    } else if (SpinTrade_CountEggOk(param0) == param0->unk_2C.unk_04) {
        param0->unk_00 = 16;
    }

    return 0;
}

static int SpinTrade_State16(SpinTrade *param0)
{
    int v0;
    SpinTradeSpinOrder *v1 = SpinTrade_GetSendBuffer(param0, sizeof(SpinTradeSpinOrder));

    v1->unk_10 = param0->unk_2C.unk_00;
    v1->unk_14 = param0->unk_2C.unk_04;
    v1->unk_04 = sPlayerStartAngles[v1->unk_14][param0->unk_2C.unk_00];

    for (v0 = 0; v0 < (7 + 1); v0++) {
        if (SpinTrade_IsNetIdConnected(param0, v0)) {
            param0->unk_2C.unk_58[v0] = CommInfo_TrainerInfo(v0);
            TrainerInfo_NameString(
                param0->unk_2C.unk_58[v0], param0->unk_2C.unk_6C[v0]);
        }
    }

    param0->unk_D4.unk_40 = (FX32_ONE * (v1->unk_04));
    param0->unk_00 = 17;

    Sound_SetSceneAndPlayBGM(SOUND_SCENE_15, SEQ_PL_GURUGURU_sseq, 1);
    SpinTrade_EraseMessage(param0);

    return 1;
}

static int SpinTrade_State17(SpinTrade *param0)
{
    param0->unk_0C--;

    if (param0->unk_0C > 0) {
        return 0;
    }

    param0->unk_0C = 15;

    {
        SpinTradeSpinOrder *v0 = SpinTrade_GetSendBufferPtr(param0);
        u16 v1 = sPlayerTargetAngles[v0->unk_14][v0->unk_10];
        int v2 = param0->unk_2C.unk_44[v0->unk_10].netId;

        SpinTrade_StartMonDropTask(param0, v2, v0->unk_10, v0->unk_00, v1, v0->unk_04, &param0->unk_190.unk_140[v0->unk_10]);

        v0->unk_10++;
        v0->unk_10 %= v0->unk_14;
        v0->unk_00++;

        if (v0->unk_00 == v0->unk_14) {
            param0->unk_0C = 0;
            param0->unk_00 = 18;
        }
    }

    return 0;
}

static int SpinTrade_State18(SpinTrade *param0)
{
    SpinTradeModels *v0 = &param0->unk_190;
    int v1 = 0, v2 = 0, v3 = param0->unk_2C.unk_04;

    do {
        if (v0->unk_140[v1].unk_08 == 1) {
            v2++;
        }

        v1++;
    } while (v1 < v3);

    if (v2 == v3) {
        param0->unk_00 = 19;
        return 1;
    }

    return 0;
}

static int SpinTrade_State19(SpinTrade *param0)
{
    param0->unk_0C++;

    if (param0->unk_0C > 30) {
        param0->unk_0C = 0;

        if (CommSys_CurNetId() == 0) {
            param0->unk_00 = 20;
        } else {
            param0->unk_00 = 21;
        }
    }

    return 0;
}

static int SpinTrade_State20(SpinTrade *param0)
{
    u16 v0 = (1 << 2);

    if (UnionRoomComm_Send(param0->unk_D0, 8, &v0, 2) == 1) {
        param0->unk_00 = 22;
    }

    return 0;
}

static int SpinTrade_State21(SpinTrade *param0)
{
    if (SpinTrade_CheckStageFlag(param0, 1 << 2) == 1) {
        param0->unk_00 = 22;

        return 1;
    }

    return 0;
}

static int SpinTrade_State22(SpinTrade *param0)
{
    CommTiming_StartSync(202);
    param0->unk_00 = 23;
    return 0;
}

static int SpinTrade_State23(SpinTrade *param0)
{
    if (CommTiming_IsSyncState(202)) {
        param0->unk_00 = 24;
    }

    return 0;
}

static int SpinTrade_State24(SpinTrade *param0)
{
    SpinTrade_StartFadeTask(param0, 1);
    SpinTrade_StartSparkleTask(param0);
    param0->unk_00 = 25;

    return 0;
}

static int SpinTrade_State25(SpinTrade *param0)
{
    int v0;

    param0->unk_0C++;

    if (param0->unk_0C < (30 * 3 + 5)) {
        return 0;
    }

    for (v0 = 0; v0 < param0->unk_2C.unk_04; v0++) {
        SpinTrade_ErasePlayerWindow(param0, v0);
    }

    param0->unk_0C = 0;
    param0->unk_00 = 26;

    return 0;
}

static int SpinTrade_State26(SpinTrade *param0)
{
    if (CommSys_CurNetId() == 0) {
        param0->unk_00 = 27;
    } else {
        param0->unk_00 = 27;
    }

    return 0;
}

static int SpinTrade_State27(SpinTrade *param0)
{
    {
        BOOL v0 = SpinTrade_UpdateSpinTimer(param0);

        if ((v0 == 1) && (SpinTrade_IsIntroTaskDone(param0) == 0)) {
            param0->unk_00 = 29;
            return 1;
        }
    }

    if (param0->unk_2C.unk_08) {
        if (SpinTrade_IsIntroTaskDone(param0) == 0) {
            SpinTrade_StartIntroTask(param0);
        }
    }

    if (SpinTrade_IsFlashTaskRunning(param0) == 0) {
        if (SpinTrade_IsCenterTouched(param0) == 1) {
            if (SpinTrade_IsIntroTaskDone(param0) == 0) {
                SpinTrade_StartIntroTask(param0);
                param0->unk_2C.unk_0C = 1;
            }

            SpinTrade_StartFlashTask(param0);
        }
    }

    if (param0->unk_2C.unk_0C) {
        if (UnionRoomComm_Send(param0->unk_CC->comm, 10, &param0->unk_2C.unk_0C, 1) == 1) {
            param0->unk_2C.unk_0C = 0;
        }
    }

    {
        fx32 v1;
        SpinTradeEggModel *v2 = &param0->unk_D4;

        if (param0->unk_08 < ((30 * 20) / 2)) {
            v2->unk_48 += (FX32_ONE * 14 / ((30 * 20) / 2));

            if (v2->unk_48 >= (FX32_ONE * 14)) {
                v2->unk_48 = (FX32_ONE * 14);
            }
        } else {
            v2->unk_48 -= (FX32_ONE * 14 / ((30 * 20) / 2));

            if (v2->unk_48 < (FX32_ONE * 4)) {
                v2->unk_48 = (FX32_ONE * 4);
            }
        }

        v1 = v2->unk_48;

        if (SpinTrade_IsIntroTaskRunning(param0) == 1) {
            SpinTrade_AdvanceEggRotation(&param0->unk_D4, (v1) << 1);
        } else {
            SpinTrade_AdvanceRotation(param0, v1);
        }
    }

    {
        UnionRoomCommSpinTradePos v3;

        v3.state = param0->unk_08;
        v3.posX = ((param0->unk_D4.unk_48) / FX32_ONE);
        v3.posY = ((param0->unk_D4.unk_3C) / FX32_ONE);

        UnionRoomComm_Send(param0->unk_D0, 11, &v3, sizeof(UnionRoomCommSpinTradePos));
    }

    return 0;
}

static int SpinTrade_State28(SpinTrade *param0)
{
    if (param0->unk_2C.unk_10 == 1) {
        param0->unk_D4.unk_3C = (FX32_ONE * (param0->unk_2C.unk_2C.posY));
        param0->unk_D4.unk_48 = (FX32_ONE * (param0->unk_2C.unk_2C.posX));
        param0->unk_08 = param0->unk_2C.unk_2C.state;
    }

    {
        BOOL v0 = SpinTrade_UpdateSpinTimer(param0);

        if ((v0 == 1) && (SpinTrade_IsIntroTaskDone(param0) == 0)) {
            param0->unk_00 = 29;
            return 1;
        }
    }

    if (param0->unk_2C.unk_08) {
        if (SpinTrade_IsIntroTaskDone(param0) == 0) {
            SpinTrade_StartIntroTask(param0);
        }
    }

    if (SpinTrade_IsFlashTaskRunning(param0) == 0) {
        if (SpinTrade_IsCenterTouched(param0) == 1) {
            if (SpinTrade_IsIntroTaskDone(param0) == 0) {
                SpinTrade_StartIntroTask(param0);
                param0->unk_2C.unk_0C = 1;
            }

            SpinTrade_StartFlashTask(param0);
        }
    }

    if (param0->unk_2C.unk_0C) {
        if (UnionRoomComm_Send(param0->unk_CC->comm, 10, &param0->unk_2C.unk_0C, 1) == 1) {
            param0->unk_2C.unk_0C = 0;
        }
    }

    if (SpinTrade_IsIntroTaskRunning(param0) == 1) {
        SpinTrade_AdvanceEggRotation(&param0->unk_D4, (param0->unk_D4.unk_48) << 1);
    } else {
        SpinTrade_AdvanceRotation(param0, param0->unk_D4.unk_48);
    }

    return 0;
}

static int SpinTrade_State29(SpinTrade *param0)
{
    SpinTrade_StartFadeTask(param0, 0);

    param0->unk_28 = SpinTrade_GetLeadingMon(param0);

    if (param0->unk_28->unk_0C == CommSys_CurNetId()) {
        param0->unk_00 = 30;
    } else {
        param0->unk_00 = 31;
    }

    Sound_PlayEffect(SEQ_SE_DP_PINPON_sseq);
    return 1;
}

static int SpinTrade_State30(SpinTrade *param0)
{
    u32 v0;
    SpinTradeMonModel *v1 = param0->unk_28;

    SpinTrade_AdvanceRotation(param0, FX32_ONE * 4);
    param0->unk_28 = SpinTrade_GetLeadingMon(param0);

    if (param0->unk_28->unk_0C != CommSys_CurNetId()) {
        param0->unk_00 = 31;
    }

    return 0;
}

static int SpinTrade_State31(SpinTrade *param0)
{
    int v0, v1;
    fx32 v2, v3, v4, v5;
    SpinTradeMonModel *v6 = param0->unk_28;

    v1 = param0->unk_2C.unk_00;
    v0 = param0->unk_2C.unk_04;
    v5 = (FX32_ONE * 4);
    v2 = v6->unk_1C;
    v3 = (FX32_ONE * (sPlayerTargetAngles[v0][v1]));

    v4 = v3 - v2;

    if (v4 < 0) {
        v4 = (v3 + (FX32_ONE * 360)) - v2;
    }

    if (v4 <= (FX32_ONE * 16)) {
        v5 >>= 1;
    }

    if (v4 < v5) {
        v5 = v4;
    }

    SpinTrade_AdvanceEggRotation(&param0->unk_D4, v5);
    SpinTrade_AdvanceMonRotation(param0, v5);
    SpinTrade_AddRotation(&v2, v5);

    if (((v2) / FX32_ONE) == ((v3) / FX32_ONE)) {
        param0->unk_00 = 32;
    }

    return 0;
}

static int SpinTrade_State32(SpinTrade *param0)
{
    CommTiming_StartSync(202);
    param0->unk_00 = 33;
    return 0;
}

static int SpinTrade_State33(SpinTrade *param0)
{
    if (CommTiming_IsSyncState(202)) {
        if (CommSys_CurNetId() == 0) {
            param0->unk_00 = 34;
        } else {
            param0->unk_00 = 35;
        }
    }

    return 0;
}

static int SpinTrade_State34(SpinTrade *param0)
{
    int v0, v1;
    SpinTradeMonModel *v2;
    SpinTradeResult v3;

    v3.eggAngle = ((param0->unk_D4.unk_3C) / FX32_ONE);

    for (v0 = 0, param0->unk_20 = 0; v0 < param0->unk_2C.unk_04; v0++) {
        v2 = &param0->unk_190.unk_140[v0];
        GF_ASSERT(v2->unk_00);
        v3.slotAngles[v2->unk_10] = (u16)((v2->unk_1C) / FX32_ONE);

        if (SpinTrade_IsInRange(param0, v2->unk_1C, param0->unk_2C.unk_04) == 1) {
            param0->unk_20 |= (1 << v2->unk_0C);
        }
    }

    v3.winnerBitmap = param0->unk_20;
    v1 = UnionRoomComm_Send(param0->unk_D0, 15, &v3, sizeof(SpinTradeResult));

    if (v1 == 1) {
        param0->unk_00 = 36;
    }

    return 0;
}

static int SpinTrade_State35(SpinTrade *param0)
{
    if (param0->unk_2C.unk_14 == 1) {
        int v0;
        SpinTradeMonModel *v1;
        SpinTradeResult *v2 = &param0->unk_2C.unk_34;

        param0->unk_D4.unk_3C = (FX32_ONE * (v2->eggAngle));

        for (v0 = 0; v0 < param0->unk_2C.unk_04; v0++) {
            v1 = &param0->unk_190.unk_140[v0];
            GF_ASSERT(v1->unk_00);
            v1->unk_1C = (FX32_ONE * (v2->slotAngles[v1->unk_10]));
        }

        param0->unk_20 = v2->winnerBitmap;

        SpinTrade_UpdateEggModel(param0);
        SpinTrade_UpdateMonModels(param0);

        param0->unk_28 = SpinTrade_GetLeadingMon(param0);
        param0->unk_00 = 36;
    }

    return 0;
}

static int SpinTrade_State36(SpinTrade *param0)
{
    int v0, v1;
    int v2 = param0->unk_28->unk_10;

    for (v0 = 0; v0 < param0->unk_2C.unk_04; v0++) {
        v1 = param0->unk_190.unk_140[v2].unk_0C;
        SpinTrade_DrawPlayerNameColored(param0, param0->unk_2C.unk_6C[v1], v0, v1);
        v2++;
        v2 %= param0->unk_2C.unk_04;
    }

    param0->unk_0C = 0;
    param0->unk_00 = 37;

    return 0;
}

static int SpinTrade_State37(SpinTrade *param0)
{
    param0->unk_0C++;

    if (param0->unk_0C < (30 * 4)) {
        return 0;
    }

    param0->unk_0C = 0;

    {
        int v0;

        for (v0 = 0; v0 < param0->unk_2C.unk_04; v0++) {
            SpinTrade_ErasePlayerWindow(param0, v0);
        }
    }

    {
        int v1 = param0->unk_28->unk_0C;
        SpinTrade_ShowMessageWithTrainer(param0, 2, param0->unk_2C.unk_58[v1]);
    }

    {
        Sound_PlayFanfare(SEQ_FANFA4_sseq);
    }

    param0->unk_00 = 38;
    return 0;
}

static int SpinTrade_State38(SpinTrade *param0)
{
    if (param0->unk_0C < (30 * 4)) {
        param0->unk_0C++;
    } else if (Sound_IsBGMPausedByFanfare() == 0) {
        param0->unk_0C = 0;
        param0->unk_00 = 39;
    }

    return 0;
}

static int SpinTrade_State39(SpinTrade *param0)
{
    SpinTrade_StartAllBobTasks(param0);

    if ((param0->unk_20 & (1 << param0->unk_28->unk_0C)) == 0) {
        param0->unk_00 = 43;
        return 0;
    }

    {
        u32 v0;

        v0 = sItemRanges[param0->unk_2C.unk_04][0];
        v0 += LCRNG_Next() % (sItemRanges[param0->unk_2C.unk_04][1] - v0 + 1);

        if (v0 < sItemRanges[param0->unk_2C.unk_04][0]) {
            v0 = sItemRanges[param0->unk_2C.unk_04][0];
        } else if (v0 > sItemRanges[param0->unk_2C.unk_04][1]) {
            v0 = sItemRanges[param0->unk_2C.unk_04][1];
        }

        SpinTrade_ShowMessageWithItem(param0, 3, v0);

        BOOL removedItem = Bag_TryAddItem(SaveData_GetBag(param0->unk_CC->context.saveData), v0, 1, HEAP_ID_95);
        Sound_PlayFanfare(SEQ_FANFA4_sseq);

        if (removedItem == TRUE) {
            param0->unk_00 = 40;
        } else {
            param0->unk_00 = 41;
        }
    }

    return 0;
}

static int SpinTrade_State40(SpinTrade *param0)
{
    if (param0->unk_0C < (30 * 4)) {
        param0->unk_0C++;
    } else if (Sound_IsBGMPausedByFanfare() == 0) {
        param0->unk_0C = 0;
        param0->unk_00 = 43;
    }

    return 0;
}

static int SpinTrade_State41(SpinTrade *param0)
{
    if (param0->unk_0C < (30 * 4)) {
        param0->unk_0C++;
    } else if (Sound_IsBGMPausedByFanfare() == 0) {
        param0->unk_0C = 0;
        param0->unk_00 = 40;
        SpinTrade_ShowMessage(param0, 4);
    }

    return 0;
}

static int SpinTrade_State42(SpinTrade *param0)
{
    if (param0->unk_0C < (30 * 4)) {
        param0->unk_0C++;
    } else {
        param0->unk_0C = 0;
        param0->unk_00 = 43;
    }

    return 0;
}

static int SpinTrade_State43(SpinTrade *param0)
{
    void *journalEntryOnlineEvent = JournalEntry_CreateEventMisc(95, ONLINE_EVENT_SPIN_TRADE);

    JournalEntry_SaveData(param0->unk_CC->context.journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
    GameRecords_IncrementRecordValue(param0->unk_CC->context.records, RECORD_UNK_119);
    GameRecords_IncrementTrainerScore(param0->unk_CC->context.records, TRAINER_SCORE_EVENT_UNK_45);
    SpinTrade_ShowMessage(param0, 11);
    CommTiming_StartSync(202);

    gSystem.inhibitReset = 1;
    param0->unk_00 = 44;

    return 0;
}

static int SpinTrade_State44(SpinTrade *param0)
{
    if (CommTiming_IsSyncState(202)) {
        SpinTrade_CopyReceivedMon(param0, param0->unk_28->unk_0C);
        CommSyncSave_Reset(&param0->unk_04);
        param0->unk_DC8 = Window_AddWaitDial(&param0->unk_C9C.unk_0C[0], 1 + 9);
        param0->unk_00 = 45;
    }

    return 0;
}

static int SpinTrade_State45(SpinTrade *param0)
{
    int v0 = CommSyncSave_Update(
        param0->unk_CC->context.saveData, 2, &param0->unk_04);

    if (v0) {
        gSystem.inhibitReset = 0;
        DestroyWaitDial(param0->unk_DC8);
        param0->unk_00 = 48;
    }

    return 0;
}

static int SpinTrade_State46(SpinTrade *param0)
{
    SpinTrade_ShowMessage(param0, 12);
    param0->unk_00 = 47;
    return 0;
}

static int SpinTrade_State47(SpinTrade *param0)
{
    param0->unk_0C++;

    if (param0->unk_0C >= (30 * 4)) {
        param0->unk_0C = 0;
        param0->unk_00 = 48;

        return 1;
    }

    return 0;
}

static int SpinTrade_State48(SpinTrade *param0)
{
    if (param0->unk_18 == 0) {
        CommTiming_StartSync(202);
    }

    SpinTrade_ShowMessage(param0, 10);
    param0->unk_00 = 49;

    return 0;
}

static int SpinTrade_State49(SpinTrade *param0)
{
    if (param0->unk_18 == 0) {
        if (CommTiming_IsSyncState(202)) {
            CommManager_SetErrorHandling(0, 0);
            CommManager_SetMaxNumConnections(1);
            CommManager_UnionRestartSearch();
            param0->unk_00 = 50;
        }
    } else {
        param0->unk_0C++;

        if (param0->unk_0C >= (30 * 4)) {
            param0->unk_0C = 0;

            if (param0->unk_D0->pendingSendCount == 0) {
                CommManager_SetErrorHandling(0, 0);
                CommManager_SetMaxNumConnections(1);
                CommManager_UnionRestartSearch();
            }

            param0->unk_00 = 50;
        }
    }

    return 0;
}

static int SpinTrade_State50(SpinTrade *param0)
{
    if (CommSys_ConnectedCount() <= 1) {
        param0->unk_00 = 51;
        return 1;
    }

    return 0;
}

static int SpinTrade_State51(SpinTrade *param0)
{
    StartScreenFade(FADE_SUB_THEN_MAIN, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 8, 1, HEAP_ID_95);

    if (param0->unk_1C != Sound_Impl_GetCurrentBGM()) {
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_FIELD, param0->unk_1C, 1);
    }

    param0->unk_00 = 52;
    return 0;
}

static int SpinTrade_State52(SpinTrade *param0)
{
    if (IsScreenFadeDone()) {
        param0->unk_00 = 53;
        return 1;
    }

    return 0;
}

static int SpinTrade_State53(SpinTrade *param0)
{
    return 2;
}

static int (*const sStateHandlers[54])(SpinTrade *g2m) = {
    SpinTrade_State0,
    SpinTrade_State1,
    SpinTrade_State2,
    SpinTrade_State3,
    SpinTrade_State4,
    SpinTrade_State5,
    SpinTrade_State6,
    SpinTrade_State7,
    SpinTrade_State8,
    SpinTrade_State9,
    SpinTrade_State10,
    SpinTrade_State11,
    SpinTrade_State12,
    SpinTrade_State13,
    SpinTrade_State14,
    SpinTrade_State15,
    SpinTrade_State16,
    SpinTrade_State17,
    SpinTrade_State18,
    SpinTrade_State19,
    SpinTrade_State20,
    SpinTrade_State21,
    SpinTrade_State22,
    SpinTrade_State23,
    SpinTrade_State24,
    SpinTrade_State25,
    SpinTrade_State26,
    SpinTrade_State27,
    SpinTrade_State28,
    SpinTrade_State29,
    SpinTrade_State30,
    SpinTrade_State31,
    SpinTrade_State32,
    SpinTrade_State33,
    SpinTrade_State34,
    SpinTrade_State35,
    SpinTrade_State36,
    SpinTrade_State37,
    SpinTrade_State38,
    SpinTrade_State39,
    SpinTrade_State40,
    SpinTrade_State41,
    SpinTrade_State42,
    SpinTrade_State43,
    SpinTrade_State44,
    SpinTrade_State45,
    SpinTrade_State46,
    SpinTrade_State47,
    SpinTrade_State48,
    SpinTrade_State49,
    SpinTrade_State50,
    SpinTrade_State51,
    SpinTrade_State52,
    SpinTrade_State53,
};

static void SpinTrade_VBlankCallback(void *param0)
{
    SpinTrade *v0 = param0;

    VramTransfer_Process();
    SpriteSystem_TransferOam();
    PaletteData_CommitFadedBuffers(v0->unk_D9C);
    Bg_RunScheduledUpdates(v0->unk_D84);
}

static void SpinTrade_InitGraphics(SpinTrade *param0)
{
    SpinTrade_SetGXBanks(param0);
    SpinTrade_InitG3D(param0);
    SpinTrade_InitCamera(param0);
    SpinTrade_InitBg(param0);
    SpinTrade_InitPalette(param0);
    SpinTrade_InitSprites(param0);

    SpinTrade_LoadGraphics(param0);
    SpinTrade_InitWindows(param0);
    SpinTrade_LoadSpriteResources(param0);
    SpinTrade_EnableLayers(param0);
}

static void SpinTrade_FreeGraphics(SpinTrade *param0)
{
    SpinTrade_DisableLayers(param0);
    SpinTrade_FreeSprites(param0);
    SpinTrade_FreeWindows(param0);
    SpinTrade_FreeBg(param0);
    SpinTrade_FreePalette(param0);
    SpinTrade_FreeCamera(param0);
}

static void SpinTrade_DrawFrame(SpinTrade *param0)
{
    G3_ResetG3X();
    Camera_ComputeViewMatrix();

    NNS_G3dGlbLightVector(0, 0, -FX32_ONE, 0);
    NNS_G3dGlbLightColor(0, GX_RGB(31, 31, 31));
    NNS_G3dGlbMaterialColorDiffAmb(GX_RGB(31, 31, 31), GX_RGB(31, 31, 31), 0);
    NNS_G3dGlbMaterialColorSpecEmi(GX_RGB(31, 31, 31), GX_RGB(31, 31, 31), 0);

    SpinTrade_DrawEggModel(param0);
    SpinTrade_DrawMonModels(param0);

    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
    SpriteSystem_DrawSprites(param0->unk_D98);
}

static void SpinTrade_SetGXBanks(SpinTrade *param0)
{
    GXBanks v0 = {
        GX_VRAM_BG_128_B,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_80_EF,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_0_A,
        GX_VRAM_TEXPLTT_0_G
    };

    GXLayers_SetBanks(&v0);
}

static void SpinTrade_EnableLayers(SpinTrade *param0)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);

    G2_SetBG0Priority(1);
    G2_SetBG1Priority(0);
    G2_SetBG2Priority(2);
    G2_SetBG3Priority(3);
    G2S_SetBG0Priority(0);
    G2S_SetBG1Priority(1);
    G2S_SetBG2Priority(2);
    G2S_SetBG3Priority(3);

    {
        G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BD, 11, 10);
    }
}

static void SpinTrade_DisableLayers(SpinTrade *param0)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 0);
}

static void SpinTrade_InitG3D(SpinTrade *param0)
{
    int v0;

    NNS_G3dInit();
    G3X_InitMtxStack();
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(1);
    G3X_AlphaTest(0, 0);
    G3X_AlphaBlend(1);
    G3X_EdgeMarking(1);

    for (v0 = 0; v0 < 8; v0++) {
        param0->unk_DA0[v0] = GX_RGB(4, 4, 4);
    }

    G3X_SetEdgeColorTable(param0->unk_DA0);
    G3X_SetClearColor(GX_RGB(31, 31, 31), 0, 0x7fff, 63, 0);
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);
    G3_ViewPort(0, 0, 255, 191);

    NNS_GfdInitFrmTexVramManager(1, 1);
    NNS_GfdInitFrmPlttVramManager(0x4000, 1);
}

static void SpinTrade_InitBg(SpinTrade *param0)
{
    param0->unk_D84 = BgConfig_New(HEAP_ID_95);
    GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_3D
        };

        SetAllGraphicsModes(&v0);
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x0000,
            .charBase = GX_BG_CHARBASE_0x04000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_D84, BG_LAYER_MAIN_1, &v1, 0);
        Bg_ClearTilemap(param0->unk_D84, BG_LAYER_MAIN_1);
        Bg_ClearTilesRange(BG_LAYER_MAIN_1, 32, 0, HEAP_ID_95);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x0800,
            .charBase = GX_BG_CHARBASE_0x0c000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_D84, BG_LAYER_MAIN_2, &v2, 0);
        Bg_ClearTilemap(param0->unk_D84, BG_LAYER_MAIN_2);
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x1000,
            .charBase = GX_BG_CHARBASE_0x0c000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_D84, BG_LAYER_MAIN_3, &v3, 0);
        Bg_ClearTilemap(param0->unk_D84, BG_LAYER_MAIN_3);
    }

    {
        BgTemplate v4 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x1000,
            .charBase = GX_BG_CHARBASE_0x14000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_D84, BG_LAYER_SUB_2, &v4, 0);
        Bg_ClearTilemap(param0->unk_D84, BG_LAYER_SUB_2);
    }

    {
        BgTemplate v5 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x1800,
            .charBase = GX_BG_CHARBASE_0x1c000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_D84, BG_LAYER_SUB_3, &v5, 0);
        Bg_ClearTilemap(param0->unk_D84, BG_LAYER_SUB_3);
    }
}

static void SpinTrade_LoadGraphics(SpinTrade *param0)
{
    void *v0 = SpinTrade_LoadNarcMember(param0, 17, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &param0->unk_D90);
    PaletteData_LoadBuffer(param0->unk_D9C, param0->unk_D90->pRawData, PLTTBUF_MAIN_BG, 0, PALETTE_SIZE_BYTES * 2);
    Heap_Free(v0);

    v0 = SpinTrade_LoadNarcMember(param0, 20, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &param0->unk_D90);
    PaletteData_LoadBuffer(param0->unk_D9C, param0->unk_D90->pRawData, PLTTBUF_SUB_BG, 0, PALETTE_SIZE_BYTES * 2);
    Heap_Free(v0);

    PaletteData_BlendMulti(param0->unk_D9C, PLTTBUF_SUB_BG, 0xffff, 8, 0);

    v0 = SpinTrade_LoadNarcMember(param0, 16, 0);
    NNS_G2dGetUnpackedCharacterData(v0, &param0->unk_D8C);
    Bg_LoadTiles(param0->unk_D84, 3, param0->unk_D8C->pRawData, param0->unk_D8C->szByte, 32 * 0);
    Heap_Free(v0);

    v0 = SpinTrade_LoadNarcMember(param0, 22, 0);
    NNS_G2dGetUnpackedCharacterData(v0, &param0->unk_D8C);
    Bg_LoadTiles(param0->unk_D84, 6, param0->unk_D8C->pRawData, param0->unk_D8C->szByte, 32 * 0);
    Heap_Free(v0);

    v0 = SpinTrade_LoadNarcMember(param0, 21, 0);
    NNS_G2dGetUnpackedCharacterData(v0, &param0->unk_D8C);
    Bg_LoadTiles(param0->unk_D84, 7, param0->unk_D8C->pRawData, param0->unk_D8C->szByte, 32 * 0);
    Heap_Free(v0);

    v0 = SpinTrade_LoadNarcMember(param0, 19, 0);
    NNS_G2dGetUnpackedScreenData(v0, &param0->unk_D88);
    Bg_LoadTilemapBuffer(param0->unk_D84, 2, (void *)param0->unk_D88->rawData, param0->unk_D88->szByte);
    Bg_CopyTilemapBufferToVRAM(param0->unk_D84, 2);
    Heap_Free(v0);

    v0 = SpinTrade_LoadNarcMember(param0, 18, 0);
    NNS_G2dGetUnpackedScreenData(v0, &param0->unk_D88);
    Bg_LoadTilemapBuffer(param0->unk_D84, 3, (void *)param0->unk_D88->rawData, param0->unk_D88->szByte);
    Bg_CopyTilemapBufferToVRAM(param0->unk_D84, 3);
    Heap_Free(v0);

    v0 = SpinTrade_LoadNarcMember(param0, 24, 0);
    NNS_G2dGetUnpackedScreenData(v0, &param0->unk_D88);
    Bg_LoadTilemapBuffer(param0->unk_D84, 6, (void *)param0->unk_D88->rawData, param0->unk_D88->szByte);
    Bg_CopyTilemapBufferToVRAM(param0->unk_D84, 6);
    Heap_Free(v0);

    v0 = SpinTrade_LoadNarcMember(param0, 23, 0);
    NNS_G2dGetUnpackedScreenData(v0, &param0->unk_D88);
    Bg_LoadTilemapBuffer(param0->unk_D84, 7, (void *)param0->unk_D88->rawData, param0->unk_D88->szByte);
    Bg_CopyTilemapBufferToVRAM(param0->unk_D84, 7);
    Heap_Free(v0);
}

static void SpinTrade_FreeBg(SpinTrade *param0)
{
    Bg_FreeTilemapBuffer(param0->unk_D84, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0->unk_D84, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0->unk_D84, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(param0->unk_D84, BG_LAYER_SUB_2);
    Bg_FreeTilemapBuffer(param0->unk_D84, BG_LAYER_SUB_3);
    Heap_Free(param0->unk_D84);
}

static void SpinTrade_LoadTilemap(SpinTrade *param0, u32 param1)
{
    void *v0 = SpinTrade_LoadNarcMember(param0, param1, 0);
    NNS_G2dGetUnpackedScreenData(v0, &param0->unk_D88);

    Bg_LoadTilemapBuffer(param0->unk_D84, 6, (void *)param0->unk_D88->rawData, param0->unk_D88->szByte);
    Bg_CopyTilemapBufferToVRAM(param0->unk_D84, 6);
    Heap_Free(v0);
}

static void SpinTrade_ShowTilemapA(SpinTrade *param0)
{
    SpinTrade_LoadTilemap(param0, 26);
}

static void SpinTrade_ShowTilemapB(SpinTrade *param0)
{
    SpinTrade_LoadTilemap(param0, 24);
}

static void SpinTrade_ShowTilemapC(SpinTrade *param0)
{
    SpinTrade_LoadTilemap(param0, 25);
}

static void SpinTrade_InitPalette(SpinTrade *param0)
{
    param0->unk_D9C = PaletteData_New(HEAP_ID_95);

    PaletteData_SetAutoTransparent(param0->unk_D9C, TRUE);
    PaletteData_AllocBuffer(param0->unk_D9C, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_95);
    PaletteData_AllocBuffer(param0->unk_D9C, PLTTBUF_MAIN_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_95);
    PaletteData_AllocBuffer(param0->unk_D9C, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_95);
    PaletteData_AllocBuffer(param0->unk_D9C, PLTTBUF_SUB_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_95);
}

static void SpinTrade_FreePalette(SpinTrade *param0)
{
    PaletteData_FreeBuffer(param0->unk_D9C, PLTTBUF_MAIN_BG);
    PaletteData_FreeBuffer(param0->unk_D9C, PLTTBUF_MAIN_OBJ);
    PaletteData_FreeBuffer(param0->unk_D9C, PLTTBUF_SUB_BG);
    PaletteData_FreeBuffer(param0->unk_D9C, PLTTBUF_SUB_OBJ);
    PaletteData_Free(param0->unk_D9C);
}

static void SpinTrade_SetPaletteBlend(SpinTrade *param0, u32 param1)
{
    PaletteData_BlendMulti(param0->unk_D9C, PLTTBUF_SUB_BG, 0xffff, param1, 0);
}

static void SpinTrade_InitSprites(SpinTrade *param0)
{
    {
        const RenderOamTemplate v0 = {
            0,
            128,
            0,
            32,
            0,
            128,
            0,
            32,
        };
        const CharTransferTemplateWithModes v1 = {
            48 + 48, 1024 * 0x40, 512 * 0x20, GX_OBJVRAMMODE_CHAR_1D_64K, GX_OBJVRAMMODE_CHAR_1D_32K
        };

        param0->unk_D94 = SpriteSystem_Alloc(HEAP_ID_95);
        SpriteSystem_Init(param0->unk_D94, &v0, &v1, 16 + 16);
    }

    {
        BOOL v2;
        const SpriteResourceCapacities v3 = {
            48 + 48,
            16 + 16,
            64,
            64,
            16,
            16,
        };

        param0->unk_D98 = SpriteManager_New(param0->unk_D94);
        v2 = SpriteSystem_InitSprites(param0->unk_D94, param0->unk_D98, 255);
        GF_ASSERT(v2);
        v2 = SpriteSystem_InitManagerWithCapacities(param0->unk_D94, param0->unk_D98, &v3);
        GF_ASSERT(v2);
    }
}

static void SpinTrade_LoadSpriteResources(SpinTrade *param0)
{
    SpriteSystem *v0 = param0->unk_D94;
    SpriteManager *v1 = param0->unk_D98;
    PaletteData *v2 = param0->unk_D9C;
    NARC *v3 = param0->unk_D80;

    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    NARC *v4;

    v4 = NARC_ctor(NARC_INDEX_GRAPHIC__NUTMIXER, HEAP_ID_95);

    SpriteSystem_LoadCharResObjFromOpenNarc(v0, v1, v4, 14, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 4);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v2, PLTTBUF_MAIN_OBJ, v0, v1, v4, 8, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 5);
    SpriteSystem_LoadCellResObjFromOpenNarc(v0, v1, v4, 13, FALSE, 6);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v0, v1, v4, 12, FALSE, 7);
    NARC_dtor(v4);

    NetworkIcon_Init();

    NNSG2dPaletteData *v5;
    void *v6 = NetworkIcon_GetPalette(HEAP_ID_95);

    NNS_G2dGetUnpackedPaletteData(v6, &v5);
    PaletteData_LoadBuffer(v2, v5->pRawData, PLTTBUF_MAIN_OBJ, PLTT_DEST(14), PALETTE_SIZE_BYTES);
    Heap_Free(v6);
}

static void SpinTrade_FreeSprites(SpinTrade *param0)
{
    SpriteSystem_FreeResourcesAndManager(param0->unk_D94, param0->unk_D98);
    SpriteSystem_Free(param0->unk_D94);
}

static ManagedSprite *SpinTrade_NewSprite(SpinTrade *param0, const SpriteTemplate *param1)
{
    ManagedSprite *v0 = SpriteSystem_NewSprite(param0->unk_D94, param0->unk_D98, param1);
    return v0;
}

static void SpinTrade_InitWindows(SpinTrade *param0)
{
    int v0 = 0;
    SpinTradeWindows *v1 = &param0->unk_C9C;

    LoadStandardWindowGraphics(param0->unk_D84, BG_LAYER_MAIN_1, 1, 15, 0, HEAP_ID_95);
    LoadMessageBoxGraphics(param0->unk_D84, BG_LAYER_MAIN_1, 1 + 9, 14, param0->unk_CC->context.messageBoxFrame, HEAP_ID_95);
    PaletteData_LoadBufferFromFileStart(param0->unk_D9C, NARC_INDEX_GRAPHIC__PL_WINFRAME, GetMessageBoxPaletteNARCMember(param0->unk_CC->context.messageBoxFrame), HEAP_ID_95, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
    PaletteData_LoadBufferFromFileStart(param0->unk_D9C, NARC_INDEX_GRAPHIC__PL_FONT, 7, HEAP_ID_95, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(15));

    v1->unk_04 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_SPIN_TRADE, HEAP_ID_95);
    v1->unk_08 = StringTemplate_Default(HEAP_ID_95);

    Window_AddFromTemplate(param0->unk_D84, &v1->unk_0C[v0], &sMessageWindowTemplate[v0]);

    v1->unk_6C = String_Init(0x100, HEAP_ID_95);

    for (v0 = 0; v0 < 5; v0++) {
        param0->unk_2C.unk_6C[v0] = String_Init(7 + 1, HEAP_ID_95);
    }

    SpinTrade_AddPlayerWindows(param0, param0->unk_CC->connectedCount);
}

static void SpinTrade_FreeWindows(SpinTrade *param0)
{
    int v0;
    SpinTradeWindows *v1 = &param0->unk_C9C;

    for (v0 = 0; v0 < 1; v0++) {
        Window_ClearAndCopyToVRAM(&v1->unk_0C[v0]);
        Window_Remove(&v1->unk_0C[v0]);
    }

    SpinTrade_RemovePlayerWindows(param0);

    MessageLoader_Free(v1->unk_04);
    StringTemplate_Free(v1->unk_08);
    String_Free(v1->unk_6C);

    for (v0 = 0; v0 < 5; v0++) {
        String_Free(param0->unk_2C.unk_6C[v0]);
    }
}

static void SpinTrade_ShowMessage(SpinTrade *param0, u32 param1)
{
    SpinTradeWindows *v0 = &param0->unk_C9C;
    Window *v1 = &v0->unk_0C[0];

    Window_FillTilemap(v1, 15);
    Window_DrawMessageBoxWithScrollCursor(v1, 1, 1 + 9, 14);
    Window_FillTilemap(v1, 15);
    MessageLoader_GetString(v0->unk_04, param1, v0->unk_6C);
    Text_AddPrinterWithParams(v1, FONT_MESSAGE, v0->unk_6C, 0, 0, TEXT_SPEED_NO_TRANSFER, NULL);
    Window_ScheduleCopyToVRAM(v1);
}

static void SpinTrade_ShowMessageWithTrainer(SpinTrade *param0, u32 param1, const TrainerInfo *param2)
{
    String *v0;
    SpinTradeWindows *v1 = &param0->unk_C9C;
    Window *v2 = &v1->unk_0C[0];

    StringTemplate_SetPlayerName(v1->unk_08, 1, CommInfo_TrainerInfo(CommSys_CurNetId()));
    StringTemplate_SetPlayerName(v1->unk_08, 2, param2);

    v0 = String_Init(0x100, HEAP_ID_95);

    MessageLoader_GetString(v1->unk_04, param1, v0);
    StringTemplate_Format(v1->unk_08, v1->unk_6C, v0);
    String_Free(v0);
    Window_DrawMessageBoxWithScrollCursor(v2, 1, 1 + 9, 14);
    Window_FillTilemap(v2, 15);
    Text_AddPrinterWithParams(v2, FONT_MESSAGE, v1->unk_6C, 0, 0, TEXT_SPEED_NO_TRANSFER, NULL);
    Window_ScheduleCopyToVRAM(v2);
}

static void SpinTrade_ShowMessageWithItem(SpinTrade *param0, u32 param1, u32 param2)
{
    String *v0;
    SpinTradeWindows *v1 = &param0->unk_C9C;
    Window *v2 = &v1->unk_0C[0];

    StringTemplate_SetItemName(v1->unk_08, 0, param2);

    v0 = String_Init(0x100, HEAP_ID_95);

    MessageLoader_GetString(v1->unk_04, param1, v0);
    StringTemplate_Format(v1->unk_08, v1->unk_6C, v0);
    String_Free(v0);
    Window_DrawMessageBoxWithScrollCursor(v2, 1, 1 + 9, 14);
    Window_FillTilemap(v2, 15);
    Text_AddPrinterWithParams(v2, FONT_MESSAGE, v1->unk_6C, 0, 0, TEXT_SPEED_NO_TRANSFER, NULL);
    Window_ScheduleCopyToVRAM(v2);
}

static void SpinTrade_EraseMessage(SpinTrade *param0)
{
    SpinTradeWindows *v0 = &param0->unk_C9C;
    Window *v1 = &v0->unk_0C[0];

    Window_EraseMessageBox(v1, 1);
    Window_FillTilemap(v1, 0);
    Window_ScheduleCopyToVRAM(v1);
}

static void SpinTrade_AddPlayerWindows(SpinTrade *param0, int param1)
{
    int v0;
    SpinTradeWindows *v1 = &param0->unk_C9C;
    const WindowTemplate *v2 = sPlayerWindowTemplates[param1];

    v1->unk_00 = param1;

    for (v0 = 0; v0 < param1; v0++) {
        Window_AddFromTemplate(param0->unk_D84, &v1->unk_1C[v0], &v2[v0]);
    }
}

static void SpinTrade_RemovePlayerWindows(SpinTrade *param0)
{
    int v0;
    SpinTradeWindows *v1 = &param0->unk_C9C;

    for (v0 = 0; v0 < v1->unk_00; v0++) {
        Window_ClearAndCopyToVRAM(&v1->unk_1C[v0]);
        Window_Remove(&v1->unk_1C[v0]);
    }
}

static void SpinTrade_DrawPlayerName(SpinTrade *param0, String *param1, int param2, TextColor param3)
{
    SpinTradeWindows *v0 = &param0->unk_C9C;
    Window *v1 = &v0->unk_1C[param2];
    Window_DrawStandardFrame(v1, 1, 1, 14);
    Window_FillTilemap(v1, 15);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, param1, Font_CalcCenterAlignment(FONT_SYSTEM, param1, 0, 8 * 8), 0, TEXT_SPEED_NO_TRANSFER, param3, NULL);
    Window_ScheduleCopyToVRAM(v1);
}

static void SpinTrade_DrawPlayerNameColored(SpinTrade *param0, String *param1, int param2, int param3)
{
    TextColor v0 = TEXT_COLOR(1, 2, 0);

    if (param3 == CommSys_CurNetId()) {
        v0 = TEXT_COLOR(3, 4, 0);
    }

    SpinTrade_DrawPlayerName(param0, param1, param2, v0);
}

static void SpinTrade_ErasePlayerWindow(SpinTrade *param0, int param1)
{
    SpinTradeWindows *v0 = &param0->unk_C9C;
    Window *v1 = &v0->unk_1C[param1];

    Window_EraseMessageBox(v1, 1);
    Window_FillTilemap(v1, 0);
    Window_ScheduleCopyToVRAM(v1);
}

static void SpinTrade_InitCamera(SpinTrade *param0)
{
    SpinTradeCamera *v0 = &param0->unk_D0C;

    v0->camera = Camera_Alloc(HEAP_ID_95);

    {
        VecFx32 v1;

        v0->unk_08.x = (FX32_ONE * 0);
        v0->unk_08.y = (FX32_ONE * 0);
        v0->unk_08.z = (FX32_ONE * 0);

        v0->cameraAngle.x = ((-32 * 0xffff) / 360);
        v0->cameraAngle.y = ((0 * 0xffff) / 360);
        v0->cameraAngle.z = ((0 * 0xffff) / 360);

        v0->unk_00 = (0x143 << FX32_SHIFT);
        v0->unk_04 = ((6 * 0xffff) / 360);

        Camera_InitWithTarget(&v0->unk_08, v0->unk_00, &v0->cameraAngle, v0->unk_04, 0, 1, v0->camera);

        v1.x = 0;
        v1.y = FX32_ONE;
        v1.z = 0;

        Camera_SetUp(&v1, v0->camera);
        Camera_SetAsActive(v0->camera);
    }
}

static void SpinTrade_FreeCamera(SpinTrade *param0)
{
    SpinTradeCamera *v0 = &param0->unk_D0C;
    Camera_Delete(v0->camera);
}

static void SpinTrade_UpdateTouchInput(SpinTrade *param0)
{
    int v0 = 0, v1 = 4 - 1;
    SpinTradeTouchInput *v2 = &param0->unk_D2C;

    WriteAutoSamplingDataToBuffer(&v2->unk_10, TOUCH_PAD_EXTERNAL_BUFFER_WRITE_METHOD_NO_WRITE, 0);

    while (v1 >= 0) {
        if (v2->unk_10.buffer[v1].touch == 1) {
            v2->unk_00 = v2->unk_10.buffer[v1].x;
            v2->unk_04 = v2->unk_10.buffer[v1].y;
            v0 = 1;
        }

        v1--;
    }

    v2->unk_08 = v0 & (v0 ^ v2->unk_0C);
    v2->unk_0C = v0;
}

static BOOL SpinTrade_IsTouchInCenter(SpinTradeTouchInput *param0)
{
    int v0, v1, v2, v3, v4, v5;

    v4 = param0->unk_00;
    v5 = param0->unk_04;
    v0 = 128 - (128 / 2);
    v1 = 96 - (128 / 2);
    v2 = 128 + (128 / 2) - 1;
    v3 = 96 + (128 / 2) - 1;

    if (((v5 >= v1) && (v5 <= v3)) && ((v4 >= v0) && (v4 <= v2))) {
        return 1;
    }

    return 0;
}

static BOOL SpinTrade_IsCenterTouched(SpinTrade *param0)
{
    SpinTradeTouchInput *v0 = &param0->unk_D2C;

    if (v0->unk_08) {
        if (SpinTrade_IsTouchInCenter(v0) == 1) {
            return 1;
        }
    }

    return 0;
}

static void SpinTrade_LoadEggModel(SpinTrade *param0)
{
    int v0;
    u32 v1;
    SpinTradeEggModel *v2 = &param0->unk_D4;
    NARC *v3 = param0->unk_D80;

    v0 = param0->unk_CC->connectedCount;
    v1 = sEggModelIndices[v0];

    Simple3D_LoadModelFromSet(&v2->unk_54, 0, v3, v1, HEAP_ID_95, 0);
    Simple3D_ScheduleBindModelTexture(&v2->unk_54);
    Simple3D_CreateRenderObject(&v2->unk_68, &v2->unk_54);

    v2->unk_3C = (FX32_ONE * 0);
    v2->unk_44 = sEggModelAngles[v0];
    v2->unk_18.x = FX32_ONE;
    v2->unk_18.y = FX32_ONE;
    v2->unk_18.z = FX32_ONE;
    v2->unk_4C.alpha = 0;
    v2->unk_4C.beta = 0;
    v2->unk_4C.gamma = 0;
    v2->unk_00.x = (FX32_ONE * 0);
    v2->unk_00.y = (FX32_ONE * -36);
    v2->unk_00.z = (FX32_ONE * 0);
    v2->unk_0C = v2->unk_00;
}

static void SpinTrade_FreeEggModel(SpinTrade *param0)
{
    SpinTradeEggModel *v0 = &param0->unk_D4;
    Simple3D_FreeModel(&v0->unk_54);
}

static void SpinTrade_UpdateEggModel(SpinTrade *param0)
{
    SpinTradeEggModel *v0 = &param0->unk_D4;
    fx32 v1 = v0->unk_3C;

    SpinTrade_AddRotation(&v1, v0->unk_40);
    SpinTrade_AddRotation(&v1, v0->unk_44);

    v0->unk_4C.beta = (360 - ((v1) / FX32_ONE)) % 360;
    v0->unk_0C.x = v0->unk_00.x + v0->unk_30.x + v0->unk_24.x;
    v0->unk_0C.y = v0->unk_00.y + v0->unk_30.y + v0->unk_24.y;
    v0->unk_0C.z = v0->unk_00.z + v0->unk_30.z + v0->unk_24.z;
}

static void SpinTrade_DrawEggModel(SpinTrade *param0)
{
    SpinTradeEggModel *v0 = &param0->unk_D4;
    Simple3D_DrawRenderObjRotationAngles(&v0->unk_68, &v0->unk_0C, &v0->unk_18, &v0->unk_4C);
}

static void SpinTrade_AdvanceEggRotation(SpinTradeEggModel *param0, fx32 param1)
{
    SpinTrade_AddRotation(&param0->unk_3C, param1);
}

static void SpinTrade_LoadModels(SpinTrade *param0)
{
    SpinTradeModels *v0 = &param0->unk_190;
    SpinTrade_LoadMonModels(param0);
}

static void SpinTrade_FreeModels(SpinTrade *param0)
{
    int v0;
    SpinTradeMonModel *v1;
    SpinTradeModels *v2 = &param0->unk_190;

    for (v0 = 0; v0 < 5; v0++) {
        v1 = &v2->unk_140[v0];
    }

    SpinTrade_FreeMonModels(param0);
}

static const u32 sMonModelIndices[5] = {
    0x6,
    0x7,
    0x8,
    0x9,
    0xA
};

static const u32 sMonAnimIndices[5] = {
    0xB,
    0xC,
    0xD,
    0xE,
    0xF
};

static void SpinTrade_LoadMonModels(SpinTrade *param0)
{
    int v0;
    const u32 *v1, *v2;
    SpinTradeModels *v3 = &param0->unk_190;

    Simple3D_LoadModelFromSet(&v3->unk_00, 0, param0->unk_D80, 0, HEAP_ID_95, 0);
    Simple3D_ScheduleBindModelTexture(&v3->unk_00);
    Simple3D_LoadModelFromSet(&v3->unk_14, 0, param0->unk_D80, 5, HEAP_ID_95, 0);
    Simple3D_ScheduleBindModelTexture(&v3->unk_14);

    v1 = sMonModelIndices;
    v2 = sMonAnimIndices;

    for (v0 = 0; v0 < 5; v0++, v1++, v2++) {
        Simple3D_LoadModelFromSet(&v3->unk_28[v0], 0, param0->unk_D80, *v1, HEAP_ID_95, 0);
        Simple3D_ScheduleBindModelTexture(&v3->unk_28[v0]);
        Simple3D_LoadAnimFromOpenNARC(&v3->unk_8C[v0], 0, param0->unk_D80, *v2, HEAP_ID_95, 0);
        Simple3D_BindModelToAnim(&v3->unk_8C[v0], &v3->unk_28[v0], HEAP_ID_95);
        Simple3D_InitG3DAnimObject(&v3->unk_8C[v0], &v3->unk_28[v0]);
    }
}

static void SpinTrade_FreeMonModels(SpinTrade *param0)
{
    int v0;
    SpinTradeModels *v1 = &param0->unk_190;

    Simple3D_FreeModel(&v1->unk_00);
    Simple3D_FreeModel(&v1->unk_14);

    for (v0 = 0; v0 < 5; v0++) {
        Simple3D_FreeModel(&v1->unk_28[v0]);
        Simple3D_FreeAnimationSet(&v1->unk_8C[v0]);
    }
}

static void SpinTrade_CreateMonRenderObj(SpinTrade *param0, SpinTradeMonModel *param1)
{
    SpinTradeModels *v0 = &param0->unk_190;

    Simple3D_CreateRenderObject(&param1->unk_5C, &v0->unk_00);
    param1->unk_04 = 1;

    SpinTrade_CreateMonShadow(param0, param1);
    SpinTrade_CreateMonAnim(param0, param1);
}

static void SpinTrade_UpdateMonModels(SpinTrade *param0)
{
    int v0 = 0, v1 = param0->unk_2C.unk_04;
    SpinTradeModels *v2 = &param0->unk_190;

    while (v0 < v1) {
        if (v2->unk_140[v0].unk_00) {
            SpinTrade_UpdateMonPosition(&v2->unk_140[v0], &param0->unk_D4.unk_30);
        }

        if (v2->unk_4B0[v0].unk_00) {
            SpinTrade_UpdateMonShadow(param0, &v2->unk_4B0[v0]);
        }

        if (v2->unk_71C[v0].unk_00) {
            SpinTrade_UpdateMonAnim(param0, &v2->unk_71C[v0]);
        }

        v0++;
    }
}

static void SpinTrade_DrawMonModels(SpinTrade *param0)
{
    int v0 = 0, v1 = param0->unk_2C.unk_04;
    SpinTradeModels *v2 = &param0->unk_190;
    SpinTradeMonModel *v3 = v2->unk_140;
    SpinTradeMonShadow *v4 = v2->unk_4B0;
    SpinTradeMonAnim *v5 = v2->unk_71C;

    while (v0 < v1) {
        if (v3->unk_04) {
            Simple3D_DrawRenderObjRotationAngles(&v3->unk_5C, &v3->unk_44, &v3->unk_38, &v3->unk_24);
        }

        if (v4->unk_00) {
            Simple3D_DrawRenderObjRotationAngles(&v4->unk_24, &v4->unk_18, &v4->unk_0C, &v4->unk_04);
        }

        if (v5->unk_00) {
            Simple3D_DrawRenderObjWithPos(&v5->unk_10, &v5->unk_04);
        }

        v3++;
        v4++;
        v5++;
        v0++;
    }
}

static void SpinTrade_AdvanceMonRotation(SpinTrade *param0, fx32 param1)
{
    int v0 = 0, v1 = param0->unk_2C.unk_04;
    SpinTradeModels *v2 = &param0->unk_190;

    while (v0 < v1) {
        if (v2->unk_140[v0].unk_00) {
            SpinTrade_AddRotation(&v2->unk_140[v0].unk_1C, param1);
        }

        v0++;
    }
}

static void SpinTrade_UpdateMonPosition(SpinTradeMonModel *param0, const VecFx32 *param1)
{
    u16 v0;
    fx32 v1;

    v1 = param0->unk_1C;
    SpinTrade_AddRotation(&v1, param0->unk_20);
    v0 = (u16)((v1) / FX32_ONE);

    param0->unk_44.x = (FX32_ONE * 0) + param0->unk_50.x + param1->x + (CalcCosineDegrees(v0) * 22);
    param0->unk_44.y = (FX32_ONE * -6) + param0->unk_50.y + param1->y;
    param0->unk_44.z = (FX32_ONE * 0) + param0->unk_50.z + param1->z + (CalcSineDegrees(v0) * 22);

    param0->unk_24.alpha = ((param0->unk_2C.x) / FX32_ONE);
    param0->unk_24.beta = ((param0->unk_2C.y) / FX32_ONE);
    param0->unk_24.gamma = ((param0->unk_2C.z) / FX32_ONE);
}

static SpinTradeMonModel *SpinTrade_GetLeadingMon(SpinTrade *param0)
{
    int v0, v1, v2, v3;
    fx32 v4, v5, v6;
    int v7 = param0->unk_2C.unk_04;
    int v8[5], v9[5];
    SpinTradeModels *v10 = &param0->unk_190;

    v0 = 0;
    v4 = (FX32_ONE * (sPlayerTargetAngles[v7][param0->unk_2C.unk_00]));

    do {
        v9[v0] = v0, v8[v0] = 0xffff;
    } while (++v0 < v7);

    for (v0 = 0; v0 < v7; v0++) {
        v5 = v10->unk_140[v0].unk_1C;
        v6 = v4 - v5;

        if (v6 < 0) {
            v6 = (v4 + (FX32_ONE * 360)) - v5;
        }

        v8[v0] = ((v6) / FX32_ONE);
    }

    for (v0 = 1; v0 < v7; v0++) {
        v3 = v9[v0];
        v2 = v8[v3];

        for (v1 = v0 - 1; v1 >= 0 && v8[v9[v1]] > v2; v1--) {
            v9[v1 + 1] = v9[v1];
        }

        v9[v1 + 1] = v3;
    }

    return &v10->unk_140[v9[0]];
}

static void SpinTrade_CreateMonShadow(SpinTrade *param0, SpinTradeMonModel *param1)
{
    SpinTradeModels *v0 = &param0->unk_190;
    SpinTradeMonShadow *v1 = &v0->unk_4B0[param1->unk_10];

    v1->unk_00 = 1;
    v1->unk_78 = param1;
    Simple3D_CreateRenderObject(&v1->unk_24, &v0->unk_14);
    SpinTrade_UpdateMonShadow(param0, v1);
}

static void SpinTrade_UpdateMonShadow(SpinTrade *param0, SpinTradeMonShadow *param1)
{
    fx32 v0;

    param1->unk_04.alpha = 0;
    param1->unk_04.beta = 0;
    param1->unk_04.gamma = 0;
    param1->unk_18 = param1->unk_78->unk_44;
    param1->unk_18.x -= param1->unk_78->unk_50.x;
    param1->unk_18.y -= param1->unk_78->unk_50.y;
    param1->unk_18.z -= param1->unk_78->unk_50.z;
    param1->unk_18.y += (FX32_ONE * 2);

    v0 = param1->unk_78->unk_50.y;

    if (v0 < 0) {
        v0 = -v0;
    }

    v0 /= 0x80;

    if (v0 > 0x800) {
        v0 = 0x800;
    }

    param1->unk_0C.x = FX32_ONE - v0;
    param1->unk_0C.y = FX32_ONE - v0;
    param1->unk_0C.z = FX32_ONE - v0;
}

static void SpinTrade_CreateMonAnim(SpinTrade *param0, SpinTradeMonModel *param1)
{
    SpinTradeModels *v0 = &param0->unk_190;
    SpinTradeMonAnim *v1 = &v0->unk_71C[param1->unk_10];

    v1->unk_00 = 1;
    v1->unk_64 = param1;

    Simple3D_CreateRenderObjectWithAnim(&v1->unk_10, &v0->unk_28[param1->unk_10], &v0->unk_8C[param1->unk_10]);
}

static void SpinTrade_UpdateMonAnim(SpinTrade *param0, SpinTradeMonAnim *param1)
{
    SpinTradeModels *v0 = &param0->unk_190;

    param1->unk_04 = param1->unk_64->unk_44;
    param1->unk_04.y += (FX32_ONE * 20);

    Simple3D_UpdateAnim(&v0->unk_8C[param1->unk_64->unk_10], FX32_ONE, 1);
}

static SysTask *SpinTrade_StartMonDropTask(SpinTrade *param0, int param1, int param2, int param3, int param4, int param5, SpinTradeMonModel *param6)
{
    SysTask *v0;
    SpinTradeMonDropTask *v1;

    param6->unk_0C = param1;
    param6->unk_10 = param2;
    param6->unk_14 = param3;
    param6->unk_18 = param2;
    param6->unk_1C = (FX32_ONE * (param4));
    param6->unk_20 = (FX32_ONE * (param5));
    param6->unk_00 = 1;
    param6->unk_08 = 0;

    v1 = Heap_AllocAtEnd(HEAP_ID_95, sizeof(SpinTradeMonDropTask));
    memset(v1, 0, sizeof(SpinTradeMonDropTask));
    v1->unk_14 = param0;
    v1->unk_10 = param6;
    v0 = SysTask_Start(SpinTrade_MonDropTask, v1, 0);

    return v0;
}

static void SpinTrade_MonDropTask(SysTask *param0, void *param1)
{
    int v0;
    SpinTradeMonDropTask *v1 = param1;

    do {
        v0 = sMonDropStateHandlers[v1->unk_00](v1);
    } while (v0 == 1);

    if (v0 == 2) {
        v1->unk_10->unk_08 = 1;
        Heap_Free(v1);
        SysTask_Done(param0);
    }
}

static int SpinTrade_MonDropState0(SpinTradeMonDropTask *param0)
{
    SpinTradeMonModel *v0 = param0->unk_10;

    v0->unk_38.x = FX32_ONE;
    v0->unk_38.y = FX32_ONE;
    v0->unk_38.z = FX32_ONE;
    v0->unk_50.y = (FX32_ONE * 192);

    SpinTrade_CreateMonRenderObj(param0->unk_14, v0);

    param0->unk_0C = (FX32_ONE * 8);
    param0->unk_00 = 1;

    return 0;
}

static int SpinTrade_MonDropState1(SpinTradeMonDropTask *param0)
{
    SpinTradeMonModel *v0 = param0->unk_10;

    v0->unk_50.y -= param0->unk_0C;

    if (param0->unk_08 == 0) {
        if (v0->unk_50.y <= (FX32_ONE * 104)) {
            param0->unk_08 = 1;
            Sound_PlayEffect(SEQ_SE_DP_FW104_sseq);
        }
    }

    if (v0->unk_50.y <= (FX32_ONE * 32)) {
        v0->unk_50.y = (FX32_ONE * 32);
        param0->unk_00 = 2;
    }

    return 0;
}

static int SpinTrade_MonDropState2(SpinTradeMonDropTask *param0)
{
    SpinTradeMonModel *v0 = param0->unk_10;

    if (param0->unk_0C > (FX32_ONE * 1)) {
        param0->unk_0C -= 0x1000;

        if (param0->unk_0C < (FX32_ONE * 1)) {
            param0->unk_0C = (FX32_ONE * 1);
        }
    }

    v0->unk_50.y -= param0->unk_0C;

    if (v0->unk_50.y <= 0) {
        v0->unk_50.y = 0;

        SpinTrade_DrawPlayerNameColored(param0->unk_14, param0->unk_14->unk_2C.unk_6C[v0->unk_0C], v0->unk_14, v0->unk_0C);

        return 2;
    }

    return 0;
}

static int (*const sMonDropStateHandlers[3])(SpinTradeMonDropTask *) = {
    SpinTrade_MonDropState0,
    SpinTrade_MonDropState1,
    SpinTrade_MonDropState2,
};

static void SpinTrade_UpdateBounceTask(SpinTrade *param0, SpinTradeBounceTask *param1)
{
    SpinTradeMonModel *v0 = param1->unk_1C;

    switch (param1->unk_04) {
    case 0:
        SpinTrade_StartShakeTask(param0, v0);
        param1->unk_10 = (FX32_ONE * 4);
        param1->unk_14 = -((FX32_ONE * 4) / (30 / 2));
        param1->unk_04++;
    case 1:
        v0->unk_50.y += param1->unk_10;
        param1->unk_10 += param1->unk_14;
        param1->unk_08++;

        if (param1->unk_08 < (30 / 2)) {
            break;
        }

        param1->unk_08 = 0;
        param1->unk_10 = 0;

        if (param1->unk_0C == 0) {
            param1->unk_0C = 1;
            break;
        }

        v0->unk_50.y = 0;
        SpinTrade_StartWobbleTask(param0, v0);
        memset(param1, 0, sizeof(SpinTradeBounceTask));
    }
}

static void SpinTrade_BounceTask(SysTask *param0, void *param1)
{
    int v0;
    SpinTrade *v1 = param1;
    SpinTradeBounceTasks *v2 = &v1->unk_AB4;
    SpinTradeBounceTask *v3 = v2->unk_00;

    for (v0 = 0; v0 < 5; v0++, v3++) {
        if (v3->unk_00) {
            SpinTrade_UpdateBounceTask(v1, v3);
        }
    }
}

static void SpinTrade_InitBounceTasks(SpinTrade *param0)
{
    SpinTradeBounceTasks *v0 = &param0->unk_AB4;
    memset(v0, 0, sizeof(SpinTradeBounceTasks));

    param0->unk_DB0 = SysTask_Start(SpinTrade_BounceTask, param0, 256);
    GF_ASSERT(param0->unk_DB0);
}

static void SpinTrade_FreeBounceTasks(SpinTrade *param0)
{
    SysTask_Done(param0->unk_DB0);
}

static void SpinTrade_StartBounceTask(SpinTrade *param0, SpinTradeMonModel *param1)
{
    int v0;
    SpinTradeBounceTasks *v1 = &param0->unk_AB4;
    SpinTradeBounceTask *v2 = v1->unk_00;

    for (v0 = 0; v0 < 5; v0++, v2++) {
        if (v2->unk_00 == 0) {
            v2->unk_00 = 1;
            v2->unk_1C = param1;
            return;
        }
    }

    GF_ASSERT(FALSE);
}

static void SpinTrade_StartAllBounceTasks(SpinTrade *param0)
{
    SpinTradeModels *v0 = &param0->unk_190;
    int v1 = 0, v2 = param0->unk_2C.unk_04;

    do {
        if (v0->unk_140[v1].unk_00) {
            SpinTrade_StartBounceTask(param0, &v0->unk_140[v1]);
        }

        v1++;
    } while (v1 < v2);
}

static BOOL SpinTrade_AreBounceTasksActive(SpinTrade *param0)
{
    int v0;
    SpinTradeBounceTasks *v1 = &param0->unk_AB4;
    SpinTradeBounceTask *v2 = v1->unk_00;

    for (v0 = 0; v0 < 5; v0++, v2++) {
        if (v2->unk_00) {
            return 1;
        }
    }

    return 0;
}

static void SpinTrade_UpdateShakeTask(SpinTradeShakeTask *param0)
{
    fx32 v0;
    SpinTradeMonModel *v1 = param0->unk_10;

    switch (param0->unk_04) {
    case 0:
        param0->unk_0C = (FX32_ONE * 24);
        v1->unk_2C.y = 0;
        param0->unk_04++;
    case 1:
        v0 = v1->unk_2C.y;
        SpinTrade_AddRotation(&v1->unk_2C.y, param0->unk_0C);

        if (v1->unk_2C.y < (FX32_ONE * 4)) {
            param0->unk_0C = (u32)(param0->unk_0C) >> 1;

            if (param0->unk_0C < (FX32_ONE * 4)) {
                v1->unk_2C.y = 0;
                memset(param0, 0, sizeof(SpinTradeShakeTask));
            }
        }
    }
}

static void SpinTrade_ShakeTask(SysTask *param0, void *param1)
{
    int v0;
    SpinTrade *v1 = param1;
    SpinTradeShakeTasks *v2 = &v1->unk_B54;
    SpinTradeShakeTask *v3 = v2->unk_00;

    for (v0 = 0; v0 < 5; v0++, v3++) {
        if (v3->unk_00) {
            SpinTrade_UpdateShakeTask(v3);
        }
    }
}

static void SpinTrade_InitShakeTasks(SpinTrade *param0)
{
    SpinTradeShakeTasks *v0 = &param0->unk_B54;
    memset(v0, 0, sizeof(SpinTradeShakeTasks));

    param0->unk_DB4 = SysTask_Start(SpinTrade_ShakeTask, param0, 257);
    GF_ASSERT(param0->unk_DB4);
}

static void SpinTrade_FreeShakeTasks(SpinTrade *param0)
{
    SysTask_Done(param0->unk_DB4);
}

static void SpinTrade_StartShakeTask(SpinTrade *param0, SpinTradeMonModel *param1)
{
    int v0;
    SpinTradeShakeTasks *v1 = &param0->unk_B54;
    SpinTradeShakeTask *v2 = v1->unk_00;

    for (v0 = 0; v0 < 5; v0++, v2++) {
        if ((v2->unk_00 == 1) && (v2->unk_10 == param1)) {
            v2->unk_04 = 0;
            return;
        }
    }

    for (v0 = 0, v2 = v1->unk_00; v0 < 5; v0++, v2++) {
        if (v2->unk_00 == 0) {
            v2->unk_00 = 1;
            v2->unk_10 = param1;
            return;
        }
    }

    GF_ASSERT(FALSE);
}

static void SpinTrade_UpdateWobbleTask(SpinTradeWobbleTask *param0)
{
    fx32 v0;
    SpinTradeMonModel *v1 = param0->unk_14;

    switch (param0->unk_04) {
    case 0:
        v1->unk_2C.z = 0;
        param0->unk_10 = 0;
        param0->unk_08 = (FX32_ONE * 30);
        param0->unk_0C = (FX32_ONE * 20);
        param0->unk_04++;
    case 1:
        v0 = CalcSineDegrees((param0->unk_10) / FX32_ONE) * ((param0->unk_08) / FX32_ONE);
        v1->unk_2C.z = 0;
        SpinTrade_AddRotation(&v1->unk_2C.z, v0);

        v0 = param0->unk_10;
        SpinTrade_AddRotation(&param0->unk_10, param0->unk_0C);

        if (param0->unk_10 < v0) {
            param0->unk_08 = (u32)(param0->unk_08) >> 1;

            if (param0->unk_08 == 0) {
                v1->unk_2C.z = 0;
                memset(param0, 0, sizeof(SpinTradeWobbleTask));
            }
        }
    }
}

static void SpinTrade_WobbleTask(SysTask *param0, void *param1)
{
    int v0;
    SpinTrade *v1 = param1;
    SpinTradeWobbleTasks *v2 = &v1->unk_BB8;
    SpinTradeWobbleTask *v3 = v2->unk_00;

    for (v0 = 0; v0 < 5; v0++, v3++) {
        if (v3->unk_00) {
            SpinTrade_UpdateWobbleTask(v3);
        }
    }
}

static void SpinTrade_InitWobbleTasks(SpinTrade *param0)
{
    SpinTradeWobbleTasks *v0 = &param0->unk_BB8;
    memset(v0, 0, sizeof(SpinTradeWobbleTasks));

    param0->unk_DB8 = SysTask_Start(SpinTrade_WobbleTask, param0, 258);
    GF_ASSERT(param0->unk_DB8);
}

static void SpinTrade_FreeWobbleTasks(SpinTrade *param0)
{
    SysTask_Done(param0->unk_DB8);
}

static void SpinTrade_StartWobbleTask(SpinTrade *param0, SpinTradeMonModel *param1)
{
    int v0;
    SpinTradeWobbleTasks *v1 = &param0->unk_BB8;
    SpinTradeWobbleTask *v2 = v1->unk_00;

    for (v0 = 0; v0 < 5; v0++, v2++) {
        if ((v2->unk_00 == 1) && (v2->unk_14 == param1)) {
            v2->unk_04 = 0;
            return;
        }
    }

    for (v0 = 0, v2 = v1->unk_00; v0 < 5; v0++, v2++) {
        if (v2->unk_00 == 0) {
            v2->unk_00 = 1;
            v2->unk_14 = param1;
            return;
        }
    }

    GF_ASSERT(FALSE);
}

static void SpinTrade_UpdateIntroTask(SpinTrade *param0, SpinTradeIntroTask *param1)
{
    SpinTradeEggModel *v0 = &param0->unk_D4;

    switch (param1->unk_00) {
    case 0:
        break;
    case 1:
        param1->unk_10 = (FX32_ONE * 4);
        param1->unk_0C = 0;
        param1->unk_00++;
    case 2:
        v0->unk_30.y -= (FX32_ONE * 1);

        if (v0->unk_30.y <= (FX32_ONE * -8)) {
            param1->unk_00++;
        }
        break;
    case 3:
        v0->unk_30.y += (FX32_ONE * 2);

        if (v0->unk_30.y >= (FX32_ONE * 0)) {
            v0->unk_30.y = 0;
            SpinTrade_StartAllBounceTasks(param0);
            param1->unk_04 = 1;
            param1->unk_00++;
            Sound_PlayEffect(SEQ_SE_PL_DANSA5_sseq_1);
        }
        break;
    case 4:
        v0->unk_24.y = param1->unk_10;
        param1->unk_10 = -param1->unk_10;
        param1->unk_0C++;

        if ((param1->unk_0C & 0x3) == 0) {
            if (param1->unk_10 <= (FX32_ONE * 1)) {
                v0->unk_24.y = 0;
                param1->unk_00++;
            } else {
                param1->unk_10 >>= 1;
            }
        }
        break;
    case 5:
        if (SpinTrade_AreBounceTasksActive(param0) == 0) {
            param1->unk_08 = 0;
            param1->unk_04 = 0;
            param1->unk_00 = 0;
            Sound_PlayEffect(SEQ_SE_PL_SUTYA2_sseq_2);
        }
        break;
    }
}

static void SpinTrade_IntroTask(SysTask *param0, void *param1)
{
    SpinTrade *v0 = param1;
    SpinTradeIntroTask *v1 = &v0->unk_C30;

    SpinTrade_UpdateIntroTask(v0, v1);
}

static void SpinTrade_InitIntroTask(SpinTrade *param0)
{
    SpinTradeIntroTask *v0 = &param0->unk_C30;
    memset(v0, 0, sizeof(SpinTradeIntroTask));
    param0->unk_DBC = SysTask_Start(SpinTrade_IntroTask, param0, 255);

    GF_ASSERT(param0->unk_DBC);
}

static void SpinTrade_FreeIntroTask(SpinTrade *param0)
{
    SysTask_Done(param0->unk_DBC);
}

static void SpinTrade_StartIntroTask(SpinTrade *param0)
{
    SpinTradeIntroTask *v0 = &param0->unk_C30;
    GF_ASSERT(v0->unk_04 == 0);
    v0->unk_08 = 1;
    v0->unk_00 = 1;
}

static BOOL SpinTrade_IsIntroTaskRunning(SpinTrade *param0)
{
    SpinTradeIntroTask *v0 = &param0->unk_C30;
    return v0->unk_04;
}

static BOOL SpinTrade_IsIntroTaskDone(SpinTrade *param0)
{
    SpinTradeIntroTask *v0 = &param0->unk_C30;
    return v0->unk_08;
}

static void SpinTrade_SparkleTask(SysTask *param0, void *param1)
{
    SpinTradeSparkleTask *v0 = param1;

    switch (v0->unk_00) {
    case 0:
        if (v0->unk_0C < 4) {
            int v1[4] = { 1501, 1501, 1501, 1603 };

            v0->unk_04--;

            if (v0->unk_04 <= 0) {
                v0->unk_04 = 30;
                Sound_PlayEffect(v1[v0->unk_0C]);
                v0->unk_0C++;
            }
        }

        ManagedSprite_TickNFrames(v0->unk_14, FX32_ONE + (FX32_ONE / 2));

        if (ManagedSprite_IsAnimated(v0->unk_14) == 0) {
            v0->unk_00++;
        }

        break;
    case 1:
        Sprite_DeleteAndFreeResources(v0->unk_14);
        Heap_Free(v0);
        SysTask_Done(param0);
    }
}

static SysTask *SpinTrade_StartSparkleTask(SpinTrade *param0)
{
    SpriteTemplate v0;
    SpinTradeSparkleTask *v1 = Heap_AllocAtEnd(HEAP_ID_95, sizeof(SpinTradeSparkleTask));

    memset(v1, 0, sizeof(SpinTradeSparkleTask));

    v0.x = 128;
    v0.y = 100;
    v0.z = 0;
    v0.animIdx = 0;
    v0.priority = 0;
    v0.plttIdx = 0;
    v0.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v0.bgPriority = 0;
    v0.vramTransfer = FALSE;
    v0.resources[0] = 4;
    v0.resources[1] = 5;
    v0.resources[2] = 6;
    v0.resources[3] = 7;
    v0.resources[4] = SPRITE_RESOURCE_NONE;
    v0.resources[5] = SPRITE_RESOURCE_NONE;

    v1->unk_14 = SpinTrade_NewSprite(param0, &v0);
    ManagedSprite_TickFrame(v1->unk_14);

    v1->unk_10 = param0;
    {
        SysTask *v2 = SysTask_Start(SpinTrade_SparkleTask, v1, 0);

        GF_ASSERT(v2 != NULL);
        return v2;
    }
}

static void SpinTrade_UpdateFlashTask(SpinTrade *param0, SpinTradeFlashTask *param1)
{
    switch (param1->unk_00) {
    case 0:
        break;
    case 1:
        SpinTrade_ShowTilemapA(param0);
        Sound_PlayEffect(SEQ_SE_DP_BUTTON9_sseq);
        param1->unk_04 = 0;
        param1->unk_00++;
    case 2:
        param1->unk_04++;

        if (param1->unk_04 >= 2) {
            param1->unk_04 = 0;
            param1->unk_00++;
            SpinTrade_ShowTilemapC(param0);
        }
        break;
    case 3:
        param1->unk_04++;

        if (param1->unk_04 >= 4) {
            SpinTrade_ShowTilemapA(param0);
            param1->unk_04 = 0;
            param1->unk_00++;
        }
        break;
    case 4:
        param1->unk_04++;

        if (param1->unk_04 >= 2) {
            SpinTrade_ShowTilemapB(param0);
            param1->unk_02 = 0;
            param1->unk_00 = 0;
        }
        break;
    }
}

static void SpinTrade_FlashTask(SysTask *param0, void *param1)
{
    SpinTrade *v0 = param1;
    SpinTradeFlashTask *v1 = &v0->unk_C44;

    SpinTrade_UpdateFlashTask(v0, v1);
}

static void SpinTrade_InitFlashTask(SpinTrade *param0)
{
    SpinTradeFlashTask *v0 = &param0->unk_C44;
    memset(v0, 0, sizeof(SpinTradeFlashTask));
    param0->unk_DC0 = SysTask_Start(SpinTrade_FlashTask, param0, 259);
    GF_ASSERT(param0->unk_DC0);
}

static void SpinTrade_FreeFlashTask(SpinTrade *param0)
{
    SysTask_Done(param0->unk_DC0);
}

static BOOL SpinTrade_IsFlashTaskRunning(SpinTrade *param0)
{
    SpinTradeFlashTask *v0 = &param0->unk_C44;
    return v0->unk_02;
}

static void SpinTrade_StartFlashTask(SpinTrade *param0)
{
    SpinTradeFlashTask *v0 = &param0->unk_C44;
    GF_ASSERT(v0->unk_02 == 0);
    v0->unk_02 = 1;
    v0->unk_00 = 1;
}

static void SpinTrade_UpdateBobTask(SpinTrade *param0, SpinTradeBobTask *param1)
{
    switch (param1->unk_00) {
    case 0:
        break;
    case 1: {
        static int v0[16] = {
            4, 6, 8, 10, 11, 12, 12, 12, 11, 10, 9, 8, 6, 4, 0, 0
        };

        param1->unk_0C->unk_50.y = (FX32_ONE * (v0[param1->unk_04]));
        param1->unk_04++;

        if (param1->unk_04 >= 16) {
            param1->unk_04 = 0;
            param1->unk_00++;
        }
    } break;
    case 2:
        param1->unk_08++;

        if (param1->unk_08 >= 15) {
            param1->unk_08 = 0;
            param1->unk_00 = 1;
        }
        break;
    }
}

static void SpinTrade_BobTask(SysTask *param0, void *param1)
{
    int v0;
    SpinTrade *v1 = param1;
    SpinTradeBobTasks *v2 = &v1->unk_C4C;
    SpinTradeBobTask *v3 = v2->unk_00;

    for (v0 = 0; v0 < 5; v0++, v3++) {
        SpinTrade_UpdateBobTask(v1, v3);
    }
}

static void SpinTrade_InitBobTasks(SpinTrade *param0)
{
    SpinTradeBobTasks *v0 = &param0->unk_C4C;
    memset(v0, 0, sizeof(SpinTradeBobTasks));
    param0->unk_DC4 = SysTask_Start(SpinTrade_BobTask, param0, 260);
    GF_ASSERT(param0->unk_DC4);
}

static void SpinTrade_FreeBobTasks(SpinTrade *param0)
{
    SysTask_Done(param0->unk_DC4);
}

static void SpinTrade_StartBobTask(SpinTrade *param0, SpinTradeMonModel *param1)
{
    int v0 = param1->unk_0C;
    SpinTradeBobTasks *v1 = &param0->unk_C4C;
    SpinTradeBobTask *v2 = &v1->unk_00[v0];

    GF_ASSERT(v0 < 5);
    GF_ASSERT(v2->unk_00 == 0);

    v2->unk_00 = 1;
    v2->unk_0C = param1;
}

static void SpinTrade_StartAllBobTasks(SpinTrade *param0)
{
    u32 v0 = param0->unk_20;
    int v1 = 0, v2 = param0->unk_2C.unk_04;
    SpinTradeModels *v3 = &param0->unk_190;

    while (v1 < v2) {
        if (v3->unk_140[v1].unk_00 && (v0 & (1 << v3->unk_140[v1].unk_0C))) {
            SpinTrade_StartBobTask(param0, &v3->unk_140[v1]);
        }

        v1++;
    }
}

static void SpinTrade_FadeTask(SysTask *param0, void *param1)
{
    int v0 = 0;
    SpinTradeFadeTask *v1 = param1;

    if (v1->unk_04 == 1) {
        v1->unk_08--;

        if ((int)v1->unk_08 <= 0) {
            v1->unk_08 = 0;
            v0 = 1;
        }
    } else {
        v1->unk_08++;

        if ((int)v1->unk_08 >= 8) {
            v1->unk_08 = 8;
            v0 = 1;
        }
    }

    SpinTrade_SetPaletteBlend(v1->unk_00, v1->unk_08);

    if (v0 == 1) {
        Heap_Free(v1);
        SysTask_Done(param0);
    }
}

static void SpinTrade_StartFadeTask(SpinTrade *param0, int param1)
{
    SysTask *v0;
    u32 v1[2] = { 0, 8 };
    SpinTradeFadeTask *v2 = Heap_AllocAtEnd(HEAP_ID_95, sizeof(SpinTradeFadeTask));

    v2->unk_00 = param0;
    v2->unk_04 = param1;
    v2->unk_08 = v1[param1];

    v0 = SysTask_Start(SpinTrade_FadeTask, v2, 0);
    GF_ASSERT(v0 != NULL);
}

static void SpinTrade_AddRotation(fx32 *param0, fx32 param1)
{
    (*param0) += param1;

    while ((*param0) < 0) {
        (*param0) += (FX32_ONE * 360);
    }

    (*param0) %= (FX32_ONE * 360);
}

static void SpinTrade_AdvanceRotation(SpinTrade *param0, fx32 param1)
{
    SpinTrade_AdvanceEggRotation(&param0->unk_D4, param1);
    SpinTrade_AdvanceMonRotation(param0, param1);
}

static BOOL SpinTrade_UpdateSpinTimer(SpinTrade *param0)
{
    param0->unk_08++;

    if (param0->unk_08 < (30 * 20)) {
        return 0;
    }

    param0->unk_08 = (30 * 20);
    return 1;
}

static void *SpinTrade_LoadNarcMember(SpinTrade *param0, u32 param1, BOOL param2)
{
    void *v0;
    u32 v1 = NARC_GetMemberSize(param0->unk_D80, param1);

    if (param2 == 1) {
        v0 = Heap_Alloc(HEAP_ID_95, v1);
    } else {
        v0 = Heap_AllocAtEnd(HEAP_ID_95, v1);
    }

    NARC_ReadWholeMember(param0->unk_D80, param1, v0);
    return v0;
}

void SpinTrade_SetState(SpinTrade *param0, u32 param1)
{
    if (param1 != 0) {
        param0->unk_2C.unk_08 = param1;
    }
}

void SpinTrade_HandleSpinTradePos(SpinTrade *param0, const UnionRoomCommSpinTradePos *param1)
{
    param0->unk_2C.unk_10 = 1;
    param0->unk_2C.unk_2C = *param1;
}

static void *SpinTrade_GetSendBuffer(SpinTrade *param0, u32 param1)
{
    GF_ASSERT(param1 < 32);
    memset(param0->unk_AC, 0, 32);
    return param0->unk_AC;
}

static void *SpinTrade_GetSendBufferPtr(SpinTrade *param0)
{
    return param0->unk_AC;
}

static BOOL SpinTrade_CheckStageFlag(SpinTrade *param0, u16 param1)
{
    u32 v0 = param0->unk_D0->stageFlags;

    if (v0 & param1) {
        return 1;
    }

    return 0;
}

static BOOL SpinTrade_AreAllParticipantsConnected(SpinTrade *param0)
{
    int v0 = 0;
    int v1 = param0->unk_CC->connectedCount - 1;
    u32 v2 = param0->unk_D0->participantBitmap;

    while (v2) {
        v0 += (v2 & 0x1);
        v2 >>= 1;
    }

    if (v0 >= v1) {
        return 1;
    }

    return 0;
}

static int SpinTrade_CountParticipants(SpinTrade *param0)
{
    int v0 = 0;
    u32 v1 = param0->unk_D0->participantBitmap;

    while (v1) {
        v0 += (v1 & 0x1);
        v1 >>= 1;
    }

    return v0;
}

void SpinTrade_HandleOrder(SpinTrade *param0, const SpinTradeOrder *param1)
{
    param0->unk_2C.unk_44[param1->slot] = *param1;

    if (param1->netId == CommSys_CurNetId()) {
        param0->unk_2C.unk_00 = param1->slot;
    }
}

void SpinTrade_SetPlayerCount(SpinTrade *param0, int param1)
{
    param0->unk_2C.unk_04 = param1;
}

static BOOL SpinTrade_IsNetIdConnected(SpinTrade *param0, int param1)
{
    if (param1 != 0) {
        u32 v0 = 1 << (u32)param1;

        if ((param0->unk_D0->participantBitmap & v0) == 0) {
            return 0;
        }
    }

    return 1;
}

static void SpinTrade_CopyReceivedMon(SpinTrade *param0, int param1)
{
    int v0, v1;
    Party *v2, *v3;
    Pokemon *v4, *v5;

    v2 = param0->unk_24;
    v3 = (Party *)UnionRoomComm_GetRecvTrainerData(param0->unk_D0, param1);

    v0 = param0->unk_CC->selectedMonSlot;
    v1 = param0->unk_2C.unk_18[param1];

    v4 = Party_GetPokemonBySlotIndex(v2, v0);
    v5 = Party_GetPokemonBySlotIndex(v3, v1);

    UpdateMonStatusAndTrainerInfo(v5, CommInfo_TrainerInfo(CommSys_CurNetId()), 5, 0, HEAP_ID_FIELD2);
    Pokemon_Copy(v5, v4);
}

static int SpinTrade_CountReceivedTrainerData(SpinTrade *param0)
{
    int v0 = 0;
    u32 v1 = param0->unk_D0->trainerDataBitmap;

    while (v1) {
        v0 += (v1 & 0x1);
        v1 >>= 1;
    }

    return v0;
}

void SpinTrade_SetMonSlot(SpinTrade *param0, int param1, int param2)
{
    param0->unk_2C.unk_18[param1] = param2;
}

void SpinTrade_HandleResult(SpinTrade *param0, const SpinTradeResult *param1)
{
    param0->unk_2C.unk_34 = *param1;
    param0->unk_2C.unk_14 = 1;
}

static BOOL SpinTrade_IsInRange(SpinTrade *param0, fx32 param1, int param2)
{
    int v0;
    fx32 v1;
    u32 v2, v3;
    const SpinTradeRangeSet *v4;
    const SpinTradeRange *v5;

    SpinTrade_AddRotation(&param1, -param0->unk_D4.unk_3C);

    v1 = param1;
    SpinTrade_AddRotation(&v1, FX32_ONE * -4);
    v2 = ((v1) / FX32_ONE);

    v1 = param1;
    SpinTrade_AddRotation(&v1, FX32_ONE * 5);
    v3 = ((v1) / FX32_ONE);

    v4 = &sRangeSets[param2];
    v0 = v4->count;
    v5 = v4->ranges;

    while (v0) {
        if (((v2 >= v5->min) && (v2 <= v5->max)) || ((v3 >= v5->min) && (v3 <= v5->max))) {
            return 1;
        }

        v5++;
        v0--;
    }

    return 0;
}

static BOOL SpinTrade_HasBadEgg(Party *param0)
{
    int v0, v1;
    Pokemon *v2;

    v1 = Party_GetCurrentCount(param0);

    for (v0 = 0; v0 < v1; v0++) {
        v2 = Party_GetPokemonBySlotIndex(param0, v0);

        if (Pokemon_GetValue(v2, MON_DATA_IS_EGG, NULL)) {
            if (Pokemon_GetValue(v2, MON_DATA_CHECKSUM_FAILED, NULL)) {
                return 1;
            }
        }
    }

    return 0;
}

static BOOL SpinTrade_AnyBadEgg(SpinTrade *param0)
{
    if (SpinTrade_HasBadEgg(param0->unk_24) == 1) {
        return 1;
    }

    {
        int v0;
        Party *v1;

        for (v0 = 0; v0 < 5; v0++) {
            if (SpinTrade_IsNetIdConnected(param0, v0)) {
                v1 = UnionRoomComm_GetRecvTrainerData(param0->unk_D0, v0);

                if (SpinTrade_HasBadEgg(v1) == 1) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

static int SpinTrade_CountEggOk(SpinTrade *param0)
{
    int v0 = 0;
    u32 v1 = param0->unk_D0->eggOkBitmap;

    while (v1) {
        v0 += v1 & 0x1;
        v1 >>= 1;
    }

    return v0;
}

static BOOL SpinTrade_HasBadEggFlag(SpinTrade *param0)
{
    int v0 = 0;
    u32 v1 = param0->unk_D0->badEggBitmap;

    if (v1) {
        return 1;
    }

    return 0;
}

static const WindowTemplate sMessageWindowTemplate[1] = {
    0x1,
    0x2,
    0x13,
    0x1A,
    0x4,
    0xF,
    0x28
};

static const WindowTemplate sPlayerWindowTemplates2[2] = {
    { 0x1, 0xC, 0x12, 0x8, 0x2, 0xF, 0x94 },
    { 0x1, 0xC, 0x6, 0x8, 0x2, 0xF, 0xBC }
};

static const WindowTemplate sPlayerWindowTemplates3[3] = {
    { 0x1, 0xC, 0x12, 0x8, 0x2, 0xF, 0x94 },
    { 0x1, 0x5, 0xA, 0x8, 0x2, 0xF, 0xBC },
    { 0x1, 0x13, 0xA, 0x8, 0x2, 0xF, 0xE4 }
};

static const WindowTemplate sPlayerWindowTemplates4[4] = {
    { 0x1, 0xC, 0x12, 0x8, 0x2, 0xF, 0x94 },
    { 0x1, 0x4, 0xD, 0x8, 0x2, 0xF, 0xBC },
    { 0x1, 0xC, 0x6, 0x8, 0x2, 0xF, 0xE4 },
    { 0x1, 0x14, 0xD, 0x8, 0x2, 0xF, 0x10C }
};

static const WindowTemplate sPlayerWindowTemplates5[5] = {
    { 0x1, 0xC, 0x13, 0x8, 0x2, 0xF, 0x94 },
    { 0x1, 0x4, 0xE, 0x8, 0x2, 0xF, 0xBC },
    { 0x1, 0x6, 0x9, 0x8, 0x2, 0xF, 0xE4 },
    { 0x1, 0x12, 0x9, 0x8, 0x2, 0xF, 0x10C },
    { 0x1, 0x14, 0xE, 0x8, 0x2, 0xF, 0X134 }
};

static const WindowTemplate *const sPlayerWindowTemplates[5 + 1] = {
    NULL,
    NULL,
    sPlayerWindowTemplates2,
    sPlayerWindowTemplates3,
    sPlayerWindowTemplates4,
    sPlayerWindowTemplates5
};

static const u16 sPlayerStartAngles[5 + 1][5] = {
    { 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x0, 0xB4, 0x0, 0x0, 0x0 },
    { 0x0, 0xF0, 0x78, 0x0, 0x0 },
    { 0x0, 0x10E, 0xB4, 0x5A, 0x0 },
    { 0x0, 0x120, 0xD8, 0x90, 0x48 }
};

static const u16 sPlayerTargetAngles[5 + 1][5] = {
    { 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x0, 0x0, 0x0, 0x0, 0x0 },
    { 0x5A, 0x10E, 0x0, 0x0, 0x0 },
    { 0x5A, 0xD2, 0x14A, 0x0, 0x0 },
    { 0x5A, 0xB4, 0x10E, 0x0, 0x0 },
    { 0x5A, 0xA2, 0xEA, 0x132, 0x12 }
};

static const SpinTradeRange sRange1 = {
    0x0,
    0xB4
};

static const SpinTradeRange sRange2[2] = {
    { 0x0, 0xC6 },
    { 0x156, 0x167 }
};

static const SpinTradeRange sRange3[2] = {
    { 0x25, 0x8E },
    { 0xD7, 0x143 }
};

static const SpinTradeRange sRange4[2] = {
    { 0x0, 0xD7 },
    { 0x143, 0x167 }
};

static const SpinTradeRangeSet sRangeSets[5 + 1] = {
    { 0x0, NULL },
    { 0x0, NULL },
    { 0x1, &sRange1 },
    { 0x2, sRange2 },
    { 0x2, sRange3 },
    { 0x2, sRange4 }
};

static const u32 sItemRanges[5 + 1][2] = {
    { 0x0, 0x0 },
    { 0x0, 0x0 },
    { 0x9F, 0xA3 },
    { 0x9F, 0xA3 },
    { 0xA4, 0xA8 },
    { 0xAF, 0xB7 }
};

static const u32 sEggModelIndices[5 + 1] = {
    0x0,
    0x0,
    0x1,
    0x2,
    0x3,
    0x4
};

static const fx32 sEggModelAngles[5 + 1] = {
    0x0,
    0x0,
    FX32_ONE * -72,
    FX32_ONE * 0,
    FX32_ONE * -181,
    (FX32_ONE * 0)
};
