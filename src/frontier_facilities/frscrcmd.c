#include "frontier_facilities/frscrcmd.h"

#include <nitro.h>

#include "constants/field_base_tiles.h"
#include "constants/string.h"
#include "generated/game_records.h"
#include "generated/genders.h"
#include "generated/object_events_gfx.h"
#include "generated/vars_flags.h"

#include "struct_decls/tv_broadcast.h"
#include "struct_decls/wi_fi_list.h"

#include "applications/naming_screen.h"
#include "global/utility.h"
#include "nintendo_wfc/main.h"
#include "wifi_2d_char/wifi_2d_char_0222BE18.h"
#include "wifi_2d_char/wifi_2d_char_0222CCE4.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CE44.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D77C_decl.h"
#include "frontier_facilities/defs.h"
#include "frontier_facilities/frontier_brain_encounter_effect.h"
#include "frontier_facilities/frontier_graphics.h"
#include "frontier_facilities/frontier_opponents.h"
#include "frontier_facilities/frontier_particle_system.h"
#include "frontier_facilities/frontier_script_context.h"
#include "frontier_facilities/frontier_script_manager.h"
#include "frontier_facilities/frscrcmd_battle_arcade.h"
#include "frontier_facilities/frscrcmd_battle_castle.h"
#include "frontier_facilities/frscrcmd_battle_factory.h"
#include "frontier_facilities/frscrcmd_battle_hall.h"
#include "frontier_facilities/frscrcmd_battle_tower.h"
#include "frontier_facilities/frscrcmd_sound.h"
#include "frontier_facilities/frscrcmd_wfc_facility_selector.h"
#include "frontier_facilities/frontier_facilities_02231F74.h"
#include "frontier_facilities/frontier_facilities_0223D768.h"
#include "frontier_facilities/frontier_facilities_0223D860.h"
#include "frontier_facilities/frontier_facilities_0223E894.h"
#include "frontier_facilities/struct_frontier_facilities_0222FEDC.h"
#include "frontier_facilities/struct_frontier_facilities_02230BE4.h"
#include "frontier_facilities/struct_frontier_facilities_0223319C.h"
#include "frontier_facilities/struct_frontier_facilities_022331E8.h"
#include "frontier_facilities/struct_frontier_facilities_0223C634.h"
#include "frontier_facilities/struct_frontier_facilities_0223C688.h"
#include "frontier_facilities/struct_frontier_facilities_0223D570.h"
#include "frontier_facilities/struct_frontier_facilities_0223EBD0_decl.h"
#include "frontier_facilities/struct_frontier_facilities_0223F094.h"
#include "frontier_facilities/struct_frontier_facilities_0223F174_decl.h"
#include "frontier_facilities/struct_frontier_facilities_0223F1B4.h"
#include "savedata/save_table.h"

#include "battle_frontier.h"
#include "battle_frontier_stats.h"
#include "bg_window.h"
#include "brightness_controller.h"
#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "enums.h"
#include "field_battle_data_transfer.h"
#include "field_comm_manager.h"
#include "game_records.h"
#include "heap.h"
#include "item_use_pokemon.h"
#include "math_util.h"
#include "menu.h"
#include "message.h"
#include "narc.h"
#include "palette.h"
#include "particle_system.h"
#include "party.h"
#include "pokemon.h"
#include "render_window.h"
#include "save_player.h"
#include "savedata.h"
#include "screen_fade.h"
#include "sound.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "trainer_info.h"
#include "tv_segment.h"
#include "battle_recording.h"
#include "comm_server_client.h"
#include "comm_tool.h"
#include "vars_flags.h"
#include "wifi_battle_tower_save.h"
#include "wifi_list.h"

#include "constdata/const_020EA358.h"

typedef struct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    int unk_0C;
} FrontierFacilitiesAffineBand;

typedef struct {
    FrontierFacilitiesAffineBand unk_00[96];
    FrontierFacilitiesAffineBuffer *unk_600;
    int unk_604;
} FrontierFacilitiesAffineScroll;

typedef struct {
    FrontierGraphics *unk_00;
    int unk_04;
    int unk_08;
    BOOL unk_0C;
    BOOL unk_10;
    void *unk_14;
    FrontierFacilitiesScreenScroll unk_18;
    FrontierFacilitiesAffineScroll *unk_24;
    Window *unk_28;
    FrontierFacilitiesWipeManager *unk_2C;
} FrontierFacilitiesNamingScreen;

u16 FrontierScriptContext_TryGetVar(FrontierScriptContext *ctx, u16 varID);
u16 *FrontierScriptContext_GetVarPointer(FrontierScriptContext *ctx, u16 varID);
static BOOL FrontierScrCmd_Noop(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_End(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_ExitFrontier(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_WaitTime(FrontierScriptContext *ctx);
static BOOL DecrementTimer(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_MessageInstant(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_MessageNoSkip(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_Message(FrontierScriptContext *ctx);
static BOOL WaitForPrinter(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_CloseMessage(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_FadeScreen(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_WaitFadeScreen(FrontierScriptContext *ctx);
static BOOL ScreenWipeDone(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_InitGlobalTextMenu(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_InitLocalTextMenu(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_AddMenuEntry(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_AddMenuEntryWithDesc(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_ShowMenu(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_InitGlobalTextListMenu(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_InitLocalTextListMenu(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_AddListMenuEntry(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_ShowListMenu(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_FreeListMenu(FrontierScriptContext *ctx);
static BOOL ResumeOnMenuSelection(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_CompareVarToValue(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_CompareVarToVar(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_SetVarFromValue(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_SetVarFromVar(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_AddVar(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_SubVar(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_GoTo(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_GoToIf(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_34(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_ShowYesNoMenu(FrontierScriptContext *ctx);
static BOOL WaitForYesNoResult(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_22(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_23(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_24(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_25(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_ApplyMovement(FrontierScriptContext *ctx);
static void FrontierSystem_StartAnimation(u16 localID, FrontierObject *object, const FrontierAnimCmd *animCmd, WiFi2DCharMoveQueue *param3, u8 *movementCount, enum HeapID heapID);
static BOOL FrontierScrCmd_WaitMovement(FrontierScriptContext *ctx);
static BOOL WaitForMovement(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_InitNewBattleRecording(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_6D(FrontierScriptContext *ctx);
static BOOL FrontierFacilities_WaitForBattleRecordingSave(FrontierScriptContext *ctx);
static int FrontierFacilities_GetBattleRecordingBattleType(u16 param0, u16 param1);
static BOOL FrontierScrCmd_6E(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_FreeBattleRecording(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_70(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_72(FrontierScriptContext *ctx);
static BOOL WaitForSaveStateFinish(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_73(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_SaveDataExtraInit(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_GetMiscSaveBlockInitFlag(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_ShowSavingIcon(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_HideSavingIcon(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_BufferItemName(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_BufferNumber(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_BufferPlayerName(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_BufferPartnerName(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_BufferMoveName(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_BufferSpeciesName(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_BufferTypeName(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_BufferRivalName(FrontierScriptContext *ctx);
static String *GetSpeciesNameString(u16 species, u32 heapID);
static BOOL FrontierScrCmd_GetNumBattlePoints(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_GiveBattlePoints(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_RemoteBattlePoints(FrontierScriptContext *ctx);
static u16 GetNumberDigitCount(u32 number);
u16 *FrontierScriptContext_TryGetVarPointer(FrontierScriptContext *ctx);
u16 FrontierScriptContext_GetVar(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_Call(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_Return(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_CallIf(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_ChangeSceneWithinScript(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_ChangeScript(FrontierScriptContext *ctx);
static BOOL Resume(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_26(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_Dummy27(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_SyncConnectedPlayers(FrontierScriptContext *ctx);
static BOOL WaitForSyncState(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_ClearReceivedTempDataAllPlayers(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_EndCommunication(FrontierScriptContext *ctx);
static BOOL WaitForCommManIsDeleted(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_GetRandom(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_HealParty(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_WaitABPress(FrontierScriptContext *ctx);
static BOOL CheckABPress(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_WaitABPressTime(FrontierScriptContext *ctx);
static BOOL DecrementABPressTimer(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_Dummy3C(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_SetSystemVar(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_GetSystemVar(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_2A(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_2B(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_2C(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_2D(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_2E(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_2F(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_30(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_31(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_32(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_33(FrontierScriptContext *ctx);
static BOOL FrontierFacilities_WaitForSpriteAnimation(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_3F(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_GetPlayerObjEventGfx(FrontierScriptContext *ctx);
static BOOL FrontierFacilities_UpdateNamingScreen(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_InitParticleSystem(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_FreeParticleSystem(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_CreateParticleSystemEmitter(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_WaitForParticleSystemEmitters(FrontierScriptContext *ctx);
static BOOL WaitForEmitters(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_4C(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_4D(FrontierScriptContext *ctx);
static BOOL FrontierFacilities_WaitForOscillationTask(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_4E(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_4F(FrontierScriptContext *ctx);
static BOOL FrontierFacilities_WaitForWindowRegionTask(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_Dummy96(FrontierScriptContext *ctx);
static void FrontierFacilities_SetObjectMovementWithParams(FrontierScriptContext *ctx, int param1, int param2);
static BOOL FrontierScrCmd_53(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_54(FrontierScriptContext *ctx);
static u32 FrontierFacilities_PackU16Pair(u16 param0, u16 param1);
static BOOL FrontierScrCmd_45(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_46(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_PlayFrontierBrainEncounterEffect(FrontierScriptContext *ctx);
static BOOL WaitForFrontierBrainEncounterEffectFinished(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_IncrementRecordValue(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_AddToRecordValue(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_IncrementTrainerScore(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_4B(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_71(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_SetWiFiListHostFriendCurrentDate(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_C8(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_C9(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_SetMenuXOriginSide(FrontierScriptContext *ctx);
static BOOL FrontierScrCmd_SetMenuYOriginSide(FrontierScriptContext *ctx);
static void FrontierFacilities_FreeNamingScreenArgs(void *namingScreenArgs);
static BOOL FrontierFacilities_NamingScreenFadeToBlack(FrontierFacilitiesNamingScreen *param0);
static BOOL FrontierFacilities_NamingScreenTileWipeHorizontal(FrontierFacilitiesNamingScreen *param0);
static BOOL FrontierFacilities_NamingScreenTileWipeVertical(FrontierFacilitiesNamingScreen *param0);
static BOOL FrontierFacilities_NamingScreenAffineWaveA(FrontierFacilitiesNamingScreen *param0);
static BOOL FrontierFacilities_NamingScreenAffineWaveB(FrontierFacilitiesNamingScreen *param0);
static BOOL FrontierFacilities_NamingScreenBg3Scroll(FrontierFacilitiesNamingScreen *param0);

static const WindowTemplate sYesNoWindowTemplate = {
    .bgLayer = BG_LAYER_MAIN_1,
    .tilemapLeft = 25,
    .tilemapTop = 13,
    .width = 6,
    .height = 4,
    .palette = 14,
    .baseTile = 0x355,
};

static const u8 sConditionTable[6][3] = {
    //   <     ==      >
    { TRUE, FALSE, FALSE }, //  <
    { FALSE, TRUE, FALSE }, //  ==
    { FALSE, FALSE, TRUE }, //  >
    { TRUE, TRUE, FALSE }, //  <=
    { FALSE, TRUE, TRUE }, //  >=
    { TRUE, FALSE, TRUE }, //  !=
};

const FrontierScrCmdFunc gFrontierScrCmdFuncs[] = {
#include "data/scripts/frscrcmd.h"
};

const u32 gFrontierScrCmdFuncsCount = NELEMS(gFrontierScrCmdFuncs);

u16 *FrontierScriptContext_TryGetVarPointer(FrontierScriptContext *ctx)
{
    u16 *var;
    u16 varID = FrontierScriptContext_ReadHalfWord(ctx);

    var = FrontierScriptContext_GetVarPointer(ctx, varID);

    if (var == NULL) {
        (void)0;
    }

    GF_ASSERT(var != NULL);
    return var;
}

u16 FrontierScriptContext_GetVar(FrontierScriptContext *ctx)
{
    return FrontierScriptContext_TryGetVar(ctx, FrontierScriptContext_ReadHalfWord(ctx));
}

u16 *FrontierScriptContext_GetVarPointer(FrontierScriptContext *ctx, u16 varID)
{
    if (varID < SCRIPT_LOCAL_VARS_START) {
        return NULL;
    } else if (varID < ((SCRIPT_LOCAL_VARS_START + 7) + 1)) {
        return &ctx->unk_08[varID - SCRIPT_LOCAL_VARS_START];
    } else if (varID < ((((SCRIPT_LOCAL_VARS_START + 7) + 1) + 7) + 1)) {
        return FrontierFacilities_GetScriptVarPointer(ctx->scriptMan, varID - ((SCRIPT_LOCAL_VARS_START + 7) + 1));
    } else if (varID < ((((((SCRIPT_LOCAL_VARS_START + 7) + 1) + 7) + 1) + 3) + 1)) {
        return &ctx->data[varID - ((((SCRIPT_LOCAL_VARS_START + 7) + 1) + 7) + 1)];
    } else if (varID == 0xFD13) {
        return NULL;
    } else if (varID == 0xEEEE) {
        return NULL;
    } else if (varID == 0xEEEF) {
        return NULL;
    }

    GF_ASSERT(FALSE);
    return NULL;
}

u16 FrontierScriptContext_TryGetVar(FrontierScriptContext *ctx, u16 varID)
{
    u16 *var = FrontierScriptContext_GetVarPointer(ctx, varID);

    if (var == NULL) {
        return varID;
    }

    return *var;
}

static BOOL FrontierScrCmd_Noop(FrontierScriptContext *ctx)
{
    return FALSE;
}

static BOOL FrontierScrCmd_End(FrontierScriptContext *ctx)
{
    FrontierScriptContext_Stop(ctx);
    return FALSE;
}

static BOOL FrontierScrCmd_ExitFrontier(FrontierScriptContext *ctx)
{
    FrontierScriptContext_Stop(ctx);
    BattleFrontier_ExitFrontier(ctx->scriptMan->frontier);

    return FALSE;
}

static BOOL FrontierScrCmd_ChangeSceneWithinScript(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    u16 sceneID = FrontierScriptContext_GetVar(ctx);

    BattleFrontier_ChangeScene(scriptMan->frontier, sceneID, NO_NEW_ENTRY_POINT);
    FrontierScriptContext_Pause(ctx, Resume);

    return TRUE;
}

static BOOL Resume(FrontierScriptContext *ctx)
{
    return TRUE;
}

static BOOL FrontierScrCmd_ChangeScript(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    u16 sceneID = FrontierScriptContext_GetVar(ctx);
    u16 offsetID = FrontierScriptContext_GetVar(ctx);

    BattleFrontier_ChangeScene(scriptMan->frontier, sceneID, offsetID);
    FrontierScriptContext_Stop(ctx);

    return FALSE;
}

static BOOL FrontierScrCmd_WaitTime(FrontierScriptContext *ctx)
{
    u16 frames = FrontierScriptContext_ReadHalfWord(ctx);
    u16 countdownVarID = FrontierScriptContext_ReadHalfWord(ctx);

    u16 *countdownVar = FrontierScriptContext_GetVarPointer(ctx, countdownVarID);
    *countdownVar = frames;
    ctx->data[0] = countdownVarID;
    FrontierScriptContext_Pause(ctx, DecrementTimer);
    return TRUE;
}

static BOOL DecrementTimer(FrontierScriptContext *ctx)
{
    u16 *frames = FrontierScriptContext_GetVarPointer(ctx, ctx->data[0]);
    (*frames)--;
    return *frames == 0;
}

static BOOL FrontierScrCmd_SetVarFromValue(FrontierScriptContext *ctx)
{
    u16 *destVar = FrontierScriptContext_TryGetVarPointer(ctx);
    *destVar = FrontierScriptContext_ReadHalfWord(ctx);
    return FALSE;
}

static BOOL FrontierScrCmd_SetVarFromVar(FrontierScriptContext *ctx)
{
    u16 *destVar = FrontierScriptContext_TryGetVarPointer(ctx);
    u16 *srcVar = FrontierScriptContext_TryGetVarPointer(ctx);
    *destVar = *srcVar;
    return FALSE;
}

static BOOL FrontierScrCmd_AddVar(FrontierScriptContext *ctx)
{
    u16 *destVar = FrontierScriptContext_TryGetVarPointer(ctx);
    *destVar += FrontierScriptContext_GetVar(ctx);
    return FALSE;
}

static BOOL FrontierScrCmd_SubVar(FrontierScriptContext *ctx)
{
    u16 *destVar = FrontierScriptContext_TryGetVarPointer(ctx);
    *destVar -= FrontierScriptContext_GetVar(ctx);
    return FALSE;
}

static u8 Compare(u16 value0, u16 value1)
{
    if (value0 < value1) {
        return 0;
    } else if (value0 == value1) {
        return 1;
    }

    return 2;
}

static BOOL FrontierScrCmd_CompareVarToValue(FrontierScriptContext *ctx)
{
    u16 value0 = FrontierScriptContext_GetVar(ctx);
    u16 value1 = FrontierScriptContext_ReadHalfWord(ctx);
    ctx->comparisonResult = Compare(value0, value1);
    return FALSE;
}

static BOOL FrontierScrCmd_CompareVarToVar(FrontierScriptContext *ctx)
{
    u16 *var0 = FrontierScriptContext_TryGetVarPointer(ctx);
    u16 *var1 = FrontierScriptContext_TryGetVarPointer(ctx);
    ctx->comparisonResult = Compare(*var0, *var1);
    return FALSE;
}

static void FrontierScriptContext_Jump(FrontierScriptContext *ctx, u8 *ptr)
{
    ctx->scriptPtr = ptr;
}

static BOOL FrontierScrCmd_GoTo(FrontierScriptContext *ctx)
{
    s32 offset = FrontierScriptContext_ReadWord(ctx);
    FrontierScriptContext_Jump(ctx, ctx->scriptPtr + offset);
    return FALSE;
}

static BOOL FrontierScrCmd_GoToIf(FrontierScriptContext *ctx)
{
    u8 condition = FrontierScriptContext_ReadByte(ctx);
    s32 offset = FrontierScriptContext_ReadWord(ctx);
    if (sConditionTable[condition][ctx->comparisonResult] == TRUE) {
        FrontierScriptContext_Jump(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

static BOOL FrontierScrCmd_Call(FrontierScriptContext *ctx)
{
    s32 offset = FrontierScriptContext_ReadWord(ctx);
    FrontierScriptContext_Call(ctx, ctx->scriptPtr + offset);
    return FALSE;
}

static BOOL FrontierScrCmd_Return(FrontierScriptContext *ctx)
{
    FrontierScriptContext_Return(ctx);
    return FALSE;
}

static BOOL FrontierScrCmd_CallIf(FrontierScriptContext *ctx)
{
    u8 condition = FrontierScriptContext_ReadByte(ctx);
    s32 offset = FrontierScriptContext_ReadWord(ctx);
    if (sConditionTable[condition][ctx->comparisonResult] == TRUE) {
        FrontierScriptContext_Call(ctx, ctx->scriptPtr + offset);
    }
    return FALSE;
}

static BOOL FrontierScrCmd_MessageInstant(FrontierScriptContext *ctx)
{
    FrontierMessageOptions printParams;
    u16 messageID = FrontierScriptContext_ReadHalfWord(ctx);

    printParams.renderDelay = TEXT_SPEED_INSTANT;
    printParams.scrollFlags = AUTO_SCROLL_DISABLED;
    printParams.font = FONT_MESSAGE;
    printParams.unused = 0;

    FrontierShowMessage(ctx->scriptMan, ctx->msgLoader, messageID, FALSE, &printParams);

    return FALSE;
}

static BOOL FrontierScrCmd_MessageNoSkip(FrontierScriptContext *ctx)
{
    u16 messageID = FrontierScriptContext_ReadHalfWord(ctx);

    FrontierShowMessage(ctx->scriptMan, ctx->msgLoader, messageID, FALSE, NULL);
    FrontierScriptContext_Pause(ctx, WaitForPrinter);
    return TRUE;
}

static BOOL FrontierScrCmd_Message(FrontierScriptContext *ctx)
{
    u16 messageID = FrontierScriptContext_ReadHalfWord(ctx);

    FrontierShowMessage(ctx->scriptMan, ctx->msgLoader, messageID, TRUE, NULL);
    FrontierScriptContext_Pause(ctx, WaitForPrinter);
    return TRUE;
}

static BOOL WaitForPrinter(FrontierScriptContext *ctx)
{
    return !Text_IsPrinterActive(ctx->scriptMan->printerID);
}

static BOOL FrontierScrCmd_CloseMessage(FrontierScriptContext *ctx)
{
    Frontier_CloseMessage(ctx->scriptMan);
    return FALSE;
}

static BOOL FrontierScrCmd_FadeScreen(FrontierScriptContext *ctx)
{
    u16 transition = FrontierScriptContext_ReadHalfWord(ctx);
    u16 frames = FrontierScriptContext_ReadHalfWord(ctx);
    u16 type = FrontierScriptContext_ReadHalfWord(ctx);
    u16 color = FrontierScriptContext_ReadHalfWord(ctx);

    StartScreenFade(FADE_BOTH_SCREENS, type, type, color, transition, frames, HEAP_ID_FIELD2);
    ResetVisibleHardwareWindows(DS_SCREEN_MAIN);
    ResetVisibleHardwareWindows(DS_SCREEN_SUB);
    return FALSE;
}

static BOOL FrontierScrCmd_WaitFadeScreen(FrontierScriptContext *ctx)
{
    FrontierScriptContext_Pause(ctx, ScreenWipeDone);
    return TRUE;
}

static BOOL ScreenWipeDone(FrontierScriptContext *ctx)
{
    return IsScreenFadeDone() == TRUE;
}

static BOOL FrontierScrCmd_InitGlobalTextMenu(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    u8 anchorX = FrontierScriptContext_ReadByte(ctx);
    u8 anchorY = FrontierScriptContext_ReadByte(ctx);
    u8 initialCursorPos = FrontierScriptContext_ReadByte(ctx);
    u8 canExitWithB = FrontierScriptContext_ReadByte(ctx);
    u16 selectedOptionVar = FrontierScriptContext_ReadHalfWord(ctx);

    scriptMan->menuMan = FrontierMenuManager_New(scriptMan, anchorX, anchorY, initialCursorPos, canExitWithB, FrontierScriptContext_GetVarPointer(ctx, selectedOptionVar), scriptMan->strTemplate, NULL);
    ctx->data[0] = selectedOptionVar;

    return TRUE;
}

static BOOL FrontierScrCmd_InitLocalTextMenu(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    u8 anchorX = FrontierScriptContext_ReadByte(ctx);
    u8 anchorY = FrontierScriptContext_ReadByte(ctx);
    u8 initialCursorPos = FrontierScriptContext_ReadByte(ctx);
    u8 canExitWithB = FrontierScriptContext_ReadByte(ctx);
    u16 selectedOptionVar = FrontierScriptContext_ReadHalfWord(ctx);

    scriptMan->menuMan = FrontierMenuManager_New(scriptMan, anchorX, anchorY, initialCursorPos, canExitWithB, FrontierScriptContext_GetVarPointer(ctx, selectedOptionVar), scriptMan->strTemplate, ctx->msgLoader);
    ctx->data[0] = selectedOptionVar;

    return TRUE;
}

static BOOL FrontierScrCmd_AddMenuEntry(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;

    u16 entryID = FrontierScriptContext_ReadHalfWord(ctx);
    u16 descriptionID = 0xff;
    u16 index = FrontierScriptContext_ReadHalfWord(ctx);

    FrontierMenuManager_AddMenuEntry(scriptMan->menuMan, entryID, descriptionID, index);
    return FALSE;
}

static BOOL FrontierScrCmd_AddMenuEntryWithDesc(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;

    u16 entryID = FrontierScriptContext_ReadHalfWord(ctx);
    u16 descriptionID = FrontierScriptContext_ReadHalfWord(ctx);
    u16 index = FrontierScriptContext_ReadHalfWord(ctx);

    FrontierMenuManager_AddMenuEntry(scriptMan->menuMan, entryID, descriptionID, index);
    return FALSE;
}

static BOOL FrontierScrCmd_ShowMenu(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;

    FrontierMenuManager_ShowMenu(scriptMan->menuMan);
    FrontierScriptContext_Pause(ctx, ResumeOnMenuSelection);

    return TRUE;
}

static BOOL ResumeOnMenuSelection(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    u16 *selectedOptionPtr = FrontierScriptContext_GetVarPointer(ctx, ctx->data[0]);

    if (*selectedOptionPtr == LIST_MENU_NO_SELECTION_YET) {
        return FALSE;
    }

    scriptMan->menuMan = NULL;
    return TRUE;
}

static BOOL FrontierScrCmd_InitGlobalTextListMenu(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    u8 anchorX = FrontierScriptContext_ReadByte(ctx);
    u8 anchorY = FrontierScriptContext_ReadByte(ctx);
    u8 initialCursorPos = FrontierScriptContext_ReadByte(ctx);
    u8 canExitWithB = FrontierScriptContext_ReadByte(ctx);
    u16 selectedOptionVar = FrontierScriptContext_ReadHalfWord(ctx);

    scriptMan->menuMan = FrontierMenuManager_New2(scriptMan, anchorX, anchorY, initialCursorPos, canExitWithB, FrontierScriptContext_GetVarPointer(ctx, selectedOptionVar), scriptMan->strTemplate, NULL);
    ctx->data[0] = selectedOptionVar;

    return TRUE;
}

static BOOL FrontierScrCmd_InitLocalTextListMenu(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    u8 anchorX = FrontierScriptContext_ReadByte(ctx);
    u8 anchorY = FrontierScriptContext_ReadByte(ctx);
    u8 initialCursorPos = FrontierScriptContext_ReadByte(ctx);
    u8 canExitWithB = FrontierScriptContext_ReadByte(ctx);
    u16 selectedOptionVar = FrontierScriptContext_ReadHalfWord(ctx);

    scriptMan->menuMan = FrontierMenuManager_New2(scriptMan, anchorX, anchorY, initialCursorPos, canExitWithB, FrontierScriptContext_GetVarPointer(ctx, selectedOptionVar), scriptMan->strTemplate, ctx->msgLoader);
    ctx->data[0] = selectedOptionVar;

    return TRUE;
}

static BOOL FrontierScrCmd_AddListMenuEntry(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;

    u16 entryID = FrontierScriptContext_ReadHalfWord(ctx);
    u16 descriptionID = FrontierScriptContext_ReadHalfWord(ctx);
    u16 index = FrontierScriptContext_ReadHalfWord(ctx);

    FrontierMenuManager_AddListMenuEntry(scriptMan->menuMan, entryID, descriptionID, index);
    return FALSE;
}

static BOOL FrontierScrCmd_ShowListMenu(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;

    FrontierMenuManager_ShowListMenu(scriptMan->menuMan);
    FrontierScriptContext_Pause(ctx, ResumeOnMenuSelection);

    return TRUE;
}

static BOOL FrontierScrCmd_FreeListMenu(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;

    FrontierMenuManager_FreeListMenu(scriptMan->menuMan);
    return TRUE;
}

static BOOL FrontierScrCmd_ShowYesNoMenu(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    FrontierGraphics *graphics = FrontierScriptManager_GetGraphics(scriptMan);
    u16 destVarID = FrontierScriptContext_ReadHalfWord(ctx);
    u8 cursorStart = FrontierScriptContext_ReadByte(ctx);

    scriptMan->menu = Menu_MakeYesNoChoiceWithCursorAt(graphics->bgConfig, &sYesNoWindowTemplate, BASE_TILE_STANDARD_WINDOW_FRAME, 12, cursorStart, scriptMan->heapID);
    ctx->data[0] = destVarID;
    FrontierScriptContext_Pause(ctx, WaitForYesNoResult);
    return TRUE;
}

static BOOL WaitForYesNoResult(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    u16 *destVar = FrontierScriptContext_GetVarPointer(ctx, ctx->data[0]);
    u32 result = Menu_ProcessInputAndHandleExit(scriptMan->menu, scriptMan->heapID);
    if (result == MENU_NOTHING_CHOSEN) {
        return FALSE;
    }
    if (result == MENU_YES) {
        *destVar = MENU_YES;
    } else {
        *destVar = MENU_NO;
    }
    return TRUE;
}

static BOOL FrontierScrCmd_22(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);
    const u8 *currScriptPtr;
    FrontierObjectGfx v3;
    s32 offset = FrontierScriptContext_ReadWord(ctx);
    currScriptPtr = ctx->scriptPtr;

    ctx->scriptPtr = (u8 *)(ctx->scriptPtr + offset);

    while (TRUE) {
        v3.gfxID = FrontierScriptContext_GetVar(ctx);

        if (v3.gfxID == 0xFD13) {
            break;
        }

        v3.unk_02 = FrontierScriptContext_ReadByte(ctx);

        if (v3.gfxID == 0xEEEE) {
            FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(v0->frontier);
            const TrainerInfo *trainerInfo = SaveData_GetTrainerInfo(fieldData->saveData);
            v3.gfxID = BattleFrontier_GetPlayerObjEventGfx(trainerInfo);

            FrontierFacilities_AddObjectGfx(v1, &v3);
        } else if (v3.gfxID == 0xEEEF) {
            if (CommSys_IsInitialized() == TRUE) {
                const TrainerInfo *trainerInfo;
                int connectedCount = CommSys_ConnectedCount(), i;

                for (i = 0; i < connectedCount; i++) {
                    trainerInfo = CommInfo_TrainerInfo(i);
                    v3.gfxID = BattleFrontier_GetPlayerObjEventGfx(trainerInfo);
                    FrontierFacilities_AddObjectGfx(v1, &v3);
                }
            } else {
                (void)0;
            }
        } else {
            FrontierFacilities_AddObjectGfx(v1, &v3);
        }
    }

    ctx->scriptPtr = currScriptPtr;
    return FALSE;
}

static BOOL FrontierScrCmd_23(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);
    u16 v2 = FrontierScriptContext_GetVar(ctx);
    FrontierFacilities_RemoveObjectGfx(v1, v2);

    return FALSE;
}

static BOOL FrontierScrCmd_24(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);
    const u8 *currScriptPtr;
    s32 offset = FrontierScriptContext_ReadWord(ctx);
    FrontierObjectParams v4;
    int v5;

    currScriptPtr = ctx->scriptPtr;

    ctx->scriptPtr = (u8 *)(ctx->scriptPtr + offset);

    while (TRUE) {
        v5 = -1;
        v4.unk_04 = FrontierScriptContext_GetVar(ctx);

        if (v4.unk_04 == 0xFD13) {
            break;
        }

        v4.unk_00 = FrontierScriptContext_GetVar(ctx);
        v4.unk_0A = FrontierScriptContext_ReadByte(ctx);
        v4.unk_06 = FrontierScriptContext_ReadHalfWord(ctx) + -8;
        v4.unk_08 = FrontierScriptContext_ReadHalfWord(ctx) + -16;
        v4.unk_0B = FrontierScriptContext_ReadByte(ctx);
        v4.unk_0C = FrontierScriptContext_ReadByte(ctx);
        v4.unk_02 = 0;

        if (v4.unk_00 == 0xEEEE) {
            const TrainerInfo *trainerInfo;
            FieldFrontierDTO *fieldData;

            fieldData = BattleFrontier_GetFieldData(v0->frontier);
            trainerInfo = SaveData_GetTrainerInfo(fieldData->saveData);
            v4.unk_00 = BattleFrontier_GetPlayerObjEventGfx(trainerInfo);
            v5 = (32 - 1);
        } else if (v4.unk_00 == 0xEEEF) {
            int netID = FrontierScriptContext_ReadByte(ctx);
            const TrainerInfo *trainerInfo = CommInfo_TrainerInfo(netID);
            v4.unk_00 = BattleFrontier_GetPlayerObjEventGfx(trainerInfo);
        } else {
            (void)0;
        }

        FrontierFacilities_AddObject(v1, &v4, v5);
    }

    ctx->scriptPtr = currScriptPtr;
    return FALSE;
}

static BOOL FrontierScrCmd_25(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);
    WiFi2DCharObject *v2;
    u16 v3 = FrontierScriptContext_GetVar(ctx);
    v2 = WiFi2DCharObjectManager_FindObjectByID(v1->unk_14, v3);

    FrontierFacilities_RemoveObject(v1, v2);

    return FALSE;
}

static BOOL FrontierScrCmd_26(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);
    u16 v2 = FrontierScriptContext_GetVar(ctx);
    u8 v3 = FrontierScriptContext_ReadByte(ctx);
    WiFi2DCharRenderObject *v4 = NULL;

    FrontierFacilities_GetObjectAndSprite(v1, v2, NULL, &v4);
    GF_ASSERT(v4 != NULL);
    WiFi2DCharRenderer_SetObjectVisible(v4, v3);

    return FALSE;
}

static BOOL FrontierScrCmd_Dummy27(FrontierScriptContext *ctx)
{
    return FALSE;
}

static BOOL FrontierScrCmd_ApplyMovement(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    FrontierGraphics *graphics = BattleFrontier_GetGraphics(scriptMan->frontier);
    u16 localID = FrontierScriptContext_GetVar(ctx);
    u32 offset = FrontierScriptContext_ReadWord(ctx);
    FrontierObject *object = FrontierFacilities_GetObject(scriptMan->frontier, localID);

    if (object == NULL) {
        GF_ASSERT(FALSE);
    }

    FrontierAnimCmd *animCmd = (FrontierAnimCmd *)(ctx->scriptPtr + offset);
    FrontierSystem_StartAnimation(localID, object, animCmd, graphics->unk_30, &scriptMan->movementCount, scriptMan->heapID);
    scriptMan->movementCount++;

    return FALSE;
}

static void FrontierSystem_StartAnimation(u16 localID, FrontierObject *object, const FrontierAnimCmd *animCmd, WiFi2DCharMoveQueue *param3, u8 *movementCount, enum HeapID heapID)
{
    FrontierAnimData *data = Heap_Alloc(heapID, sizeof(FrontierAnimData));
    MI_CpuClear8(data, sizeof(FrontierAnimData));

    data->frontierObj = object;
    data->animCmd = animCmd;
    data->unk_10 = param3;
    data->localID = localID;
    data->totalMovementCount = movementCount;

    GF_ASSERT(object->movementTask == NULL);
    object->movementTask = SysTask_Start(FrontierObject_DoAnimation, data, 60100);
}

static BOOL FrontierScrCmd_WaitMovement(FrontierScriptContext *ctx)
{
    FrontierScriptContext_Pause(ctx, WaitForMovement);
    return TRUE;
}

static BOOL WaitForMovement(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;

    return scriptMan->movementCount == 0;
}

static BOOL FrontierScrCmd_2A(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);
    const u8 *currScriptPtr;
    s32 offset = FrontierScriptContext_ReadWord(ctx);
    u16 v4;
    NARC *narc;

    currScriptPtr = ctx->scriptPtr;
    ctx->scriptPtr = (u8 *)(ctx->scriptPtr + offset);
    narc = NARC_ctor(NARC_INDEX_RESOURCE__ENG__FRONTIER_GRAPHIC__FRONTIER_OBJ, v0->heapID);

    while (TRUE) {
        v4 = FrontierScriptContext_GetVar(ctx);

        if (v4 == 0xFD13) {
            break;
        }

        FrontierFacilities_LoadObjectSpriteResources(v1->spriteSystem, v1->spriteMan, narc, v1->plttData, v4);
        FrontierFacilities_AddSpriteID(v1, v4);
    }

    NARC_dtor(narc);
    ctx->scriptPtr = currScriptPtr;

    return FALSE;
}

static BOOL FrontierScrCmd_2B(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);
    u16 v2 = FrontierScriptContext_GetVar(ctx);

    FrontierFacilities_UnloadObjectSpriteResources(v1->spriteMan, v2);
    FrontierFacilities_RemoveSpriteID(v1, v2);

    return FALSE;
}

static BOOL FrontierScrCmd_2C(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);
    const u8 *currScriptPtr;
    s32 offset = FrontierScriptContext_ReadWord(ctx);
    u16 v4, x, y, draw, v8, v9;
    ManagedSprite *managedSprite;
    currScriptPtr = ctx->scriptPtr;

    ctx->scriptPtr = (u8 *)(ctx->scriptPtr + offset);

    while (TRUE) {
        v4 = FrontierScriptContext_GetVar(ctx);

        if (v4 == 0xFD13) {
            break;
        }

        x = FrontierScriptContext_GetVar(ctx);
        y = FrontierScriptContext_GetVar(ctx);
        draw = FrontierScriptContext_GetVar(ctx);
        v8 = FrontierScriptContext_ReadByte(ctx);
        v9 = FrontierScriptContext_ReadByte(ctx);
        managedSprite = FrontierFacilities_AddManagedSprite(v1, v9, v4);

        ManagedSprite_SetPositionXY(managedSprite, x, y);
        ManagedSprite_SetDrawFlag(managedSprite, draw);

        FrontierFacilities_SetSpriteVisible(v1, v9, v8);
    }

    ctx->scriptPtr = currScriptPtr;
    return FALSE;
}

static BOOL FrontierScrCmd_2D(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    u16 v1;
    FrontierGraphics *v2 = BattleFrontier_GetGraphics(v0->frontier);

    v1 = FrontierScriptContext_GetVar(ctx);
    FrontierFacilities_RemoveManagedSprite(v2, v1);

    return FALSE;
}

static BOOL FrontierScrCmd_2E(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);
    u16 v2 = FrontierScriptContext_GetVar(ctx);
    u8 draw = FrontierScriptContext_ReadByte(ctx);
    ManagedSprite *managedSprite = FrontierFacilities_GetManagedSprite(v1, v2);

    GF_ASSERT(managedSprite != NULL);
    ManagedSprite_SetDrawFlag(managedSprite, draw);

    return FALSE;
}

static BOOL FrontierScrCmd_2F(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);
    u16 v2 = FrontierScriptContext_GetVar(ctx);
    ManagedSprite *managedSprite = FrontierFacilities_GetManagedSprite(v1, v2);

    GF_ASSERT(managedSprite != NULL);
    Sprite_SetFlipMode2(managedSprite->sprite, 1);

    return FALSE;
}

static BOOL FrontierScrCmd_30(FrontierScriptContext *ctx)
{
    ManagedSprite *managedSprite;
    FrontierScriptManager *v1 = ctx->scriptMan;
    FrontierGraphics *v2 = BattleFrontier_GetGraphics(v1->frontier);
    u16 v3 = FrontierScriptContext_GetVar(ctx);
    u16 v4 = FrontierScriptContext_GetVar(ctx);

    managedSprite = FrontierFacilities_GetManagedSprite(v2, v3);
    GF_ASSERT(managedSprite != NULL);

    if (v4 == 0) {
        Sprite_SetExplicitOamMode2(managedSprite->sprite, GX_OAM_MODE_NORMAL);
    } else {
        Sprite_SetExplicitOamMode2(managedSprite->sprite, GX_OAM_MODE_XLU);
    }

    return FALSE;
}

static BOOL FrontierScrCmd_31(FrontierScriptContext *ctx)
{
    u16 v0 = FrontierScriptContext_GetVar(ctx);
    u16 animID = FrontierScriptContext_GetVar(ctx);
    ManagedSprite *managedSprite;
    FrontierGraphics *v3 = BattleFrontier_GetGraphics(ctx->scriptMan->frontier);

    managedSprite = FrontierFacilities_GetManagedSprite(v3, v0);

    ManagedSprite_SetAnim(managedSprite, animID);
    FrontierFacilities_SetSpriteVisible(v3, v0, 1);

    return FALSE;
}

static BOOL FrontierScrCmd_32(FrontierScriptContext *ctx)
{
    u16 v0 = FrontierScriptContext_GetVar(ctx);
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(ctx->scriptMan->frontier);

    FrontierFacilities_SetSpriteVisible(v1, v0, 0);
    return FALSE;
}

static BOOL FrontierScrCmd_33(FrontierScriptContext *ctx)
{
    u16 v0 = FrontierScriptContext_GetVar(ctx);

    ctx->data[0] = v0;
    FrontierScriptContext_Pause(ctx, FrontierFacilities_WaitForSpriteAnimation);

    return TRUE;
}

static BOOL FrontierFacilities_WaitForSpriteAnimation(FrontierScriptContext *ctx)
{
    ManagedSprite *managedSprite;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(ctx->scriptMan->frontier);

    managedSprite = FrontierFacilities_GetManagedSprite(v1, ctx->data[0]);

    if (FrontierFacilities_IsSpriteVisible(v1, ctx->data[0]) == 0 || ManagedSprite_IsAnimated(managedSprite) == FALSE) {
        return TRUE;
    }

    return FALSE;
}

static void FrontierFacilities_SetObjectMovementWithParams(FrontierScriptContext *ctx, int param1, int param2)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    s16 *v1;
    u16 v2;
    int v3;

    GF_ASSERT(param2 <= 7);

    v1 = Heap_Alloc(v0->heapID, sizeof(s16) * param2);
    v2 = FrontierScriptContext_GetVar(ctx);

    for (v3 = 0; v3 < 3; v3++) {
        v1[v3] = FrontierScriptContext_GetVar(ctx);
    }

    FrontierFacilities_SetObjectMovement(v0->frontier, v2, 1, v1, 3);
    Heap_Free(v1);
}

static BOOL FrontierScrCmd_53(FrontierScriptContext *ctx)
{
    u16 v0 = FrontierScriptContext_GetVar(ctx);
    FrontierFacilities_SetObjectMovement(ctx->scriptMan->frontier, v0, 0, NULL, 0);

    return FALSE;
}

static BOOL FrontierScrCmd_54(FrontierScriptContext *ctx)
{
    FrontierFacilities_SetObjectMovementWithParams(ctx, 1, 3);
    return FALSE;
}

static BOOL FrontierScrCmd_34(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    void *namingScreenArgs = NamingScreenArgs_Init(HEAP_ID_FIELD2, NAMING_SCREEN_TYPE_PLAYER, 0, 8, (void *)fieldData->options);

    BattleFrontier_RunSubApp(ctx->scriptMan->frontier, &gNamingScreenAppTemplate, namingScreenArgs, 0, FrontierFacilities_FreeNamingScreenArgs);

    return TRUE;
}

static void FrontierFacilities_FreeNamingScreenArgs(void *namingScreenArgs)
{
    NamingScreenArgs_Free(namingScreenArgs);
}

static BOOL FrontierScrCmd_InitNewBattleRecording(FrontierScriptContext *ctx)
{
    int resultCode;
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);

    BattleRecording_New(fieldData->saveData, HEAP_ID_FIELD2, &resultCode);
    return FALSE;
}

static BOOL FrontierScrCmd_6D(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    u16 v1 = FrontierScriptContext_ReadHalfWord(ctx);
    u16 v2 = FrontierScriptContext_GetVar(ctx);
    u16 v3 = FrontierScriptContext_GetVar(ctx);
    u16 *v4 = FrontierScriptContext_TryGetVarPointer(ctx);

    if (v3 > 9999) {
        v3 = 9999;
    }

    v0->unk_B0 = 0;
    v0->unk_B2 = 0;
    v0->unk_B4 = FrontierFacilities_GetBattleRecordingBattleType(v1, v2);
    v0->unk_B6 = v3;
    v0->unk_B8 = v4;

    FrontierScriptContext_Pause(ctx, FrontierFacilities_WaitForBattleRecordingSave);
    return TRUE;
}

static BOOL FrontierFacilities_WaitForBattleRecordingSave(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    int v2 = BattleRecording_SaveWithSummary(fieldData->saveData, v0->unk_B4, v0->unk_B6, 0, &v0->unk_B0, &v0->unk_B2);

    if ((v2 == 2) || (v2 == 3)) {
        if (v2 == 2) {
            *(v0->unk_B8) = 1;
        } else {
            *(v0->unk_B8) = 0;
        }

        return TRUE;
    }

    return FALSE;
}

static int FrontierFacilities_GetBattleRecordingBattleType(u16 param0, u16 param1)
{
    int v0 = (UnkEnum_0202F510_15);

    switch (param0) {
    case 1:
        switch (param1) {
        case 0:
            v0 = (UnkEnum_0202F510_15);
            break;
        case 1:
            v0 = (UnkEnum_0202F510_16);
            break;
        case 2:
        case 3:
        case 6:
            v0 = (UnkEnum_0202F510_17);
            break;
        case 4:
        case 5:
            v0 = (UnkEnum_0202F510_15);
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }
        break;
    case 2:
        switch (param1) {
        case 0:
            v0 = (UnkEnum_0202F510_18);
            break;
        case 1:
            v0 = (UnkEnum_0202F510_19);
            break;
        case 2:
        case 3:
            v0 = (UnkEnum_0202F510_20);
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }
        break;
    case 3:
        switch (param1) {
        case 0:
            v0 = (UnkEnum_0202F510_21);
            break;
        case 1:
            v0 = (UnkEnum_0202F510_22);
            break;
        case 2:
        case 3:
            v0 = (UnkEnum_0202F510_23);
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }
        break;
    case 4:
        switch (param1) {
        case 0:
            v0 = (UnkEnum_0202F510_27);
            break;
        case 1:
            v0 = (UnkEnum_0202F510_28);
            break;
        case 2:
        case 3:
            v0 = (UnkEnum_0202F510_29);
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }
        break;
    case 5:
        switch (param1) {
        case 0:
            v0 = (UnkEnum_0202F510_24);
            break;
        case 1:
            v0 = (UnkEnum_0202F510_25);
            break;
        case 2:
        case 3:
            v0 = (UnkEnum_0202F510_26);
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }
        break;
    case 6:
        switch (param1) {
        case 0:
            v0 = (UnkEnum_0202F510_30);
            break;
        case 1:
            v0 = (UnkEnum_0202F510_31);
            break;
        case 2:
        case 3:
            v0 = (UnkEnum_0202F510_32);
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }
        break;
    }

    return v0;
}

static BOOL FrontierScrCmd_6E(FrontierScriptContext *ctx)
{
    int v0;
    FieldBattleDTO *dto;
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);

    dto = Heap_Alloc(HEAP_ID_FIELD2, sizeof(FieldBattleDTO));
    MI_CpuClear8(dto, sizeof(FieldBattleDTO));

    BattleRecording_Load(fieldData->saveData, 11, &v0, dto, 0);
    Sound_SetSceneAndPlayBGM(SOUND_SCENE_BATTLE, BATTLE_TRAINER_sseq, 1);
    BattleFrontier_RunSubApp(ctx->scriptMan->frontier, &gBattleApplicationTemplate, dto, 1, NULL);

    return TRUE;
}

static BOOL FrontierScrCmd_FreeBattleRecording(FrontierScriptContext *ctx)
{
    BattleRecording_Free();
    return FALSE;
}

static BOOL FrontierScrCmd_70(FrontierScriptContext *ctx)
{
    int v0;
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    u16 *v2 = FrontierScriptContext_TryGetVarPointer(ctx);

    *v2 = BattleRecording_Validate(fieldData->saveData, 11, &v0, 0);
    return FALSE;
}

static BOOL FrontierScrCmd_72(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    u16 *unused = FrontierScriptContext_TryGetVarPointer(ctx);
    SaveData_Save(fieldData->saveData);
    return FALSE;
}

static BOOL FrontierScrCmd_73(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    u16 *v2 = FrontierScriptContext_TryGetVarPointer(ctx);

    ResetLock(RESET_LOCK_SOFT_RESET);
    InitHeapCanary(v0->heapID);
    SaveData_SaveStateInit(fieldData->saveData, 2);

    FrontierScriptContext_Pause(ctx, WaitForSaveStateFinish);
    return TRUE;
}

static BOOL WaitForSaveStateFinish(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    int saveResult = SaveData_SaveStateMain(fieldData->saveData);

    if (saveResult == SAVE_RESULT_OK) {
        FreeHeapCanary();
        ResetUnlock(RESET_LOCK_SOFT_RESET);
        return TRUE;
    }

    if (saveResult == SAVE_RESULT_CORRUPT) {
        FreeHeapCanary();
        ResetUnlock(RESET_LOCK_SOFT_RESET);
        return TRUE;
    }

    return FALSE;
}

static BOOL FrontierScrCmd_SaveDataExtraInit(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);

    SaveDataExtra_Init(fieldData->saveData);
    return FALSE;
}

static BOOL FrontierScrCmd_GetMiscSaveBlockInitFlag(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    u16 *destVar = FrontierScriptContext_TryGetVarPointer(ctx);

    *destVar = SaveData_MiscSaveBlock_InitFlag(fieldData->saveData);
    return FALSE;
}

static BOOL FrontierScrCmd_ShowSavingIcon(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    scriptMan->savingIcon = Window_AddWaitDial(&scriptMan->msgWindow, BASE_TILE_SCROLLING_MESSAGE_BOX);
    return FALSE;
}

static BOOL FrontierScrCmd_HideSavingIcon(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    DestroyWaitDial(scriptMan->savingIcon);
    return FALSE;
}

static BOOL FrontierScrCmd_BufferItemName(FrontierScriptContext *ctx)
{
    u8 templateArg = FrontierScriptContext_ReadByte(ctx);
    u16 item = FrontierScriptContext_GetVar(ctx);

    StringTemplate_SetItemName(ctx->scriptMan->strTemplate, templateArg, item);
    return FALSE;
}

static BOOL FrontierScrCmd_BufferNumber(FrontierScriptContext *ctx)
{
    u8 templateArg = FrontierScriptContext_ReadByte(ctx);
    u16 number = FrontierScriptContext_GetVar(ctx);

    StringTemplate_SetNumber(ctx->scriptMan->strTemplate, templateArg, number, GetNumberDigitCount(number), PADDING_MODE_SPACES, CHARSET_MODE_EN);
    return FALSE;
}

static u16 GetNumberDigitCount(u32 number)
{
    if (number / 10 == 0) {
        return 1;
    } else if (number / 100 == 0) {
        return 2;
    } else if (number / 1000 == 0) {
        return 3;
    } else if (number / 10000 == 0) {
        return 4;
    } else if (number / 100000 == 0) {
        return 5;
    } else if (number / 1000000 == 0) {
        return 6;
    } else if (number / 10000000 == 0) {
        return 7;
    } else if (number / 100000000 == 0) {
        return 8;
    }

    return 1;
}

static BOOL FrontierScrCmd_BufferPlayerName(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    u8 templateArg = FrontierScriptContext_ReadByte(ctx);

    StringTemplate_SetPlayerName(ctx->scriptMan->strTemplate, templateArg, SaveData_GetTrainerInfo(fieldData->saveData));
    return FALSE;
}

static BOOL FrontierScrCmd_BufferPartnerName(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    u8 templateArg = FrontierScriptContext_ReadByte(ctx);

    StringTemplate_SetPlayerName(ctx->scriptMan->strTemplate, templateArg, CommInfo_TrainerInfo(CommSys_CurNetId() ^ 1));
    return FALSE;
}

BOOL FrontierScrCmd_BufferMoveName(FrontierScriptContext *ctx)
{
    u8 templateArg = FrontierScriptContext_ReadByte(ctx);
    u16 move = FrontierScriptContext_GetVar(ctx);

    StringTemplate_SetMoveName(ctx->scriptMan->strTemplate, templateArg, move);
    return FALSE;
}

BOOL FrontierScrCmd_BufferSpeciesName(FrontierScriptContext *ctx)
{
    u8 templateArg = FrontierScriptContext_ReadByte(ctx);
    u16 species = FrontierScriptContext_GetVar(ctx);
    u16 unused1 = FrontierScriptContext_ReadHalfWord(ctx);
    u8 unused2 = FrontierScriptContext_ReadByte(ctx);
    String *speciesName = GetSpeciesNameString(species, HEAP_ID_FIELD2);

    StringTemplate_SetString(ctx->scriptMan->strTemplate, templateArg, speciesName, unused1, unused2, GAME_LANGUAGE);
    String_Free(speciesName);
    return FALSE;
}

static String *GetSpeciesNameString(u16 species, u32 heapID)
{
    MessageLoader *speciesNames = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_SPECIES_NAME, heapID);
    String *buffer = MessageLoader_GetNewString(speciesNames, species);

    MessageLoader_Free(speciesNames);
    return buffer;
}

static BOOL FrontierScrCmd_BufferTypeName(FrontierScriptContext *ctx)
{
    u8 templateArg = FrontierScriptContext_ReadByte(ctx);
    u16 type = FrontierScriptContext_GetVar(ctx);

    StringTemplate_SetPokemonTypeName(ctx->scriptMan->strTemplate, templateArg, type);
    return FALSE;
}

static BOOL FrontierScrCmd_BufferRivalName(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    u8 templateArg = FrontierScriptContext_ReadByte(ctx);

    StringTemplate_SetRivalName(ctx->scriptMan->strTemplate, templateArg, fieldData->saveData);
    return FALSE;
}

static BOOL FrontierScrCmd_GetNumBattlePoints(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    u16 *destVar = FrontierScriptContext_TryGetVarPointer(ctx);

    *destVar = WifiBattleTowerRecord_UpdateBattlePoints(SaveData_GetWifiBattleTowerRecord(fieldData->saveData), 0, BATTLE_POINTS_FUNC_NONE);
    return FALSE;
}

static BOOL FrontierScrCmd_GiveBattlePoints(FrontierScriptContext *ctx)
{
    TVBroadcast *broadcast;
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    u16 battlePoints = FrontierScriptContext_GetVar(ctx);

    broadcast = SaveData_GetTVBroadcast(fieldData->saveData);

    TVBroadcast_AddBattlePoints(broadcast, battlePoints);
    GameRecords_AddToRecordValue(SaveData_GetGameRecords(fieldData->saveData), RECORD_BATTLE_POINTS_RECEIVED, battlePoints);
    WifiBattleTowerRecord_UpdateBattlePoints(SaveData_GetWifiBattleTowerRecord(fieldData->saveData), battlePoints, BATTLE_POINTS_FUNC_ADD);

    return FALSE;
}

static BOOL FrontierScrCmd_RemoteBattlePoints(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    u16 battlePoints = FrontierScriptContext_GetVar(ctx);

    GameRecords_AddToRecordValue(SaveData_GetGameRecords(fieldData->saveData), RECORD_BATTLE_POINTS_SPENT, battlePoints);
    WifiBattleTowerRecord_UpdateBattlePoints(SaveData_GetWifiBattleTowerRecord(fieldData->saveData), battlePoints, BATTLE_POINTS_FUNC_SUB);

    return FALSE;
}

static BOOL FrontierScrCmd_SyncConnectedPlayers(FrontierScriptContext *ctx)
{
    u16 syncNo = FrontierScriptContext_GetVar(ctx);

    ctx->data[0] = syncNo;

    CommTiming_StartSync(syncNo);
    FrontierScriptContext_Pause(ctx, WaitForSyncState);

    return TRUE;
}

static BOOL WaitForSyncState(FrontierScriptContext *ctx)
{
    int result;

    if (CommSys_ConnectedCount() < 2) {
        result = TRUE;
    } else {
        result = CommTiming_IsSyncState(ctx->data[0]);
    }

    return result;
}

static BOOL FrontierScrCmd_ClearReceivedTempDataAllPlayers(FrontierScriptContext *ctx)
{
    CommTool_ClearReceivedTempDataAllPlayers();
    return FALSE;
}

static BOOL FrontierScrCmd_EndCommunication(FrontierScriptContext *ctx)
{
    FieldCommManager_EndBattleNoSync();
    FrontierScriptContext_Pause(ctx, WaitForCommManIsDeleted);

    return TRUE;
}

static BOOL WaitForCommManIsDeleted(FrontierScriptContext *ctx)
{
    return CommManager_IsInitialized() != TRUE && CommServerClient_IsInitialized() != TRUE;
}

static BOOL FrontierScrCmd_GetRandom(FrontierScriptContext *ctx)
{
    u16 *destVar = FrontierScriptContext_TryGetVarPointer(ctx);
    u16 upperBound = FrontierScriptContext_GetVar(ctx);

    *destVar = LCRNG_Next() % upperBound;
    return TRUE;
}

static BOOL FrontierScrCmd_HealParty(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    Party_HealAllMembers(SaveData_GetParty(fieldData->saveData));
    return FALSE;
}

static BOOL FrontierScrCmd_WaitABPress(FrontierScriptContext *ctx)
{
    FrontierScriptContext_Pause(ctx, CheckABPress);
    return TRUE;
}

static BOOL CheckABPress(FrontierScriptContext *ctx)
{
    return JOY_NEW(PAD_BUTTON_A | PAD_BUTTON_B) != 0;
}

static BOOL FrontierScrCmd_WaitABPressTime(FrontierScriptContext *ctx)
{
    ctx->data[0] = FrontierScriptContext_GetVar(ctx);
    FrontierScriptContext_Pause(ctx, DecrementABPressTimer);
    return TRUE;
}

static BOOL DecrementABPressTimer(FrontierScriptContext *ctx)
{
    if (JOY_NEW(PAD_BUTTON_A | PAD_BUTTON_B)) {
        return TRUE;
    }

    ctx->data[0]--;

    return ctx->data[0] == 0;
}

static BOOL FrontierScrCmd_Dummy3C(FrontierScriptContext *ctx)
{
    u16 *unused = FrontierScriptContext_TryGetVarPointer(ctx);

    return TRUE;
}

BOOL FrontierScrCmd_SetSystemVar(FrontierScriptContext *ctx)
{
    u16 destVarID = FrontierScriptContext_ReadHalfWord(ctx);
    u16 value = FrontierScriptContext_GetVar(ctx);
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);

    u16 *destVar = VarsFlags_GetVarAddress(SaveData_GetVarsFlags(fieldData->saveData), destVarID);
    *destVar = value;

    return FALSE;
}

BOOL FrontierScrCmd_GetSystemVar(FrontierScriptContext *ctx)
{
    u16 srcVarID = FrontierScriptContext_ReadHalfWord(ctx);
    u16 *dest = FrontierScriptContext_TryGetVarPointer(ctx);
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);

    u16 *srcVar = VarsFlags_GetVarAddress(SaveData_GetVarsFlags(fieldData->saveData), srcVarID);
    *dest = *srcVar;

    return FALSE;
}

static BOOL (*const sFrontierFacilitiesNamingScreenStates[])(FrontierFacilitiesNamingScreen *) = {
    FrontierFacilities_NamingScreenFadeToBlack,
    FrontierFacilities_NamingScreenTileWipeHorizontal,
    FrontierFacilities_NamingScreenTileWipeVertical,
    FrontierFacilities_NamingScreenAffineWaveA,
    FrontierFacilities_NamingScreenAffineWaveB,
    FrontierFacilities_NamingScreenBg3Scroll
};

static BOOL FrontierFacilities_NamingScreenFadeToBlack(FrontierFacilitiesNamingScreen *param0)
{
    switch (param0->unk_04) {
    case 0:
        FrontierFacilities_StartScreenFlash(1, 16, -16, &param0->unk_0C, 2);
        param0->unk_04++;
        break;
    case 1:
        if (param0->unk_0C == 0) {
            break;
        }

        ResetVisibleHardwareWindows(DS_SCREEN_MAIN);
        ResetVisibleHardwareWindows(DS_SCREEN_SUB);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_UNK_32, FADE_TYPE_UNK_32, COLOR_BLACK, 12, 1, HEAP_ID_FIELD2);
        param0->unk_04++;
        break;
    default:
        if (IsScreenFadeDone() == TRUE) {
            return FALSE;
        }
        break;
    }

    return TRUE;
}

static BOOL FrontierFacilities_NamingScreenTileWipeHorizontal(FrontierFacilitiesNamingScreen *param0)
{
    switch (param0->unk_04) {
    case 0:
        FrontierFacilities_StartScreenFlash(1, 16, -16, &param0->unk_0C, 2);
        param0->unk_04++;
        break;
    case 1:
        if (param0->unk_0C == 0) {
            break;
        }

        param0->unk_28 = Window_New(HEAP_ID_FIELD2, 1);

        Window_Add(param0->unk_00->bgConfig, param0->unk_28, 1, 0, 0, 32, 32, 0, 0);
        PaletteData_FillBufferRange(param0->unk_00->plttData, PLTTBUF_MAIN_BG, PLTTSEL_BOTH, 0x0, 0, 16);
        Window_FillTilemap(param0->unk_28, 0);
        Window_ScheduleCopyToVRAM(param0->unk_28);

        param0->unk_2C = FrontierFacilities_NewWipeManager(HEAP_ID_FIELD2);
        param0->unk_04++;
    case 2:
        FrontierFacilities_StartWipe(param0->unk_2C, 1, 1, param0->unk_28, 15);
        param0->unk_04++;
        break;
    case 3:
        BOOL v0 = FrontierFacilities_UpdateHorizontalWipe(param0->unk_2C);

        Window_ScheduleCopyToVRAM(param0->unk_28);

        if (v0) {
            param0->unk_04++;
        }
        break;
    default:
        if (IsScreenFadeDone() == TRUE) {
            FrontierFacilities_FreeWipeManager(param0->unk_2C);

            Window_ClearAndCopyToVRAM(param0->unk_28);
            Window_Remove(param0->unk_28);
            Windows_Delete(param0->unk_28, 1);
            SetScreenColorBrightness(DS_SCREEN_MAIN, COLOR_BLACK);
            SetScreenColorBrightness(DS_SCREEN_SUB, COLOR_BLACK);
            Bg_ClearTilesRange(BG_LAYER_MAIN_1, 32, 0, HEAP_ID_FIELD2);
            Bg_ClearTilemap(param0->unk_00->bgConfig, 1);

            return FALSE;
        }
        break;
    }

    return TRUE;
}

static BOOL FrontierFacilities_NamingScreenTileWipeVertical(FrontierFacilitiesNamingScreen *param0)
{
    switch (param0->unk_04) {
    case 0:
        FrontierFacilities_StartScreenFlash(1, 16, -16, &param0->unk_0C, 2);
        param0->unk_04++;
        break;
    case 1:
        if (param0->unk_0C == 0) {
            break;
        }

        param0->unk_28 = Window_New(HEAP_ID_FIELD2, 1);

        Window_Add(param0->unk_00->bgConfig, param0->unk_28, 1, 0, 0, 32, 32, 0, 0);
        PaletteData_FillBufferRange(param0->unk_00->plttData, PLTTBUF_MAIN_BG, PLTTSEL_BOTH, 0x0, 0, 16);
        Window_FillTilemap(param0->unk_28, 0);
        Window_ScheduleCopyToVRAM(param0->unk_28);

        param0->unk_2C = FrontierFacilities_NewWipeManager(HEAP_ID_FIELD2);
        param0->unk_04++;
    case 2:
        FrontierFacilities_StartWipe(param0->unk_2C, 1, 1, param0->unk_28, 15);
        param0->unk_04++;
        break;
    case 3:
        BOOL v0 = FrontierFacilities_UpdateVerticalWipe(param0->unk_2C);

        Window_ScheduleCopyToVRAM(param0->unk_28);

        if (v0) {
            param0->unk_04++;
        }
        break;

    default:
        if (IsScreenFadeDone() == TRUE) {
            FrontierFacilities_FreeWipeManager(param0->unk_2C);

            Window_ClearAndCopyToVRAM(param0->unk_28);
            Window_Remove(param0->unk_28);
            Windows_Delete(param0->unk_28, 1);

            SetScreenColorBrightness(DS_SCREEN_MAIN, COLOR_BLACK);
            SetScreenColorBrightness(DS_SCREEN_SUB, COLOR_BLACK);

            Bg_ClearTilesRange(BG_LAYER_MAIN_1, 32, 0, HEAP_ID_FIELD2);
            Bg_ClearTilemap(param0->unk_00->bgConfig, 1);

            return FALSE;
        }
        break;
    }

    return TRUE;
}

static u32 FrontierFacilities_PackU16Pair(u16 param0, u16 param1)
{
    return (param1 << 16) | param0;
}

static void FrontierFacilities_AffineScrollTask(SysTask *param0, void *param1)
{
    int v0, v1;
    FrontierFacilitiesAffineEntry *v2;
    FrontierFacilitiesNamingScreen *v3 = param1;
    FrontierFacilitiesAffineScroll *v4 = v3->unk_24;
    MtxFx22 v5;
    int v6, v7, v8, v9;

    v6 = Bg_GetXOffset2(v3->unk_00->bgConfig, 2);
    v7 = Bg_GetXOffset2(v3->unk_00->bgConfig, 2);
    v8 = Bg_GetXOffset2(v3->unk_00->bgConfig, 3);
    v9 = Bg_GetXOffset2(v3->unk_00->bgConfig, 3);

    if (v3->unk_10 == 1) {
        v2 = FrontierFacilities_GetAffineWriteBuffer(v4->unk_600);

        for (v0 = 0; v0 < (192 / 2); v0++) {
            v4->unk_00[v0].unk_08 = 0;
            v4->unk_00[v0].unk_0A = 0;

            for (v1 = v4->unk_00[v0].unk_00; v1 < v4->unk_00[v0].unk_02; v1++) {
                s16 v10, v11;
                s16 v12, v13;

                v10 = v4->unk_00[v0].unk_0C & 0xFFFF;
                v11 = v4->unk_00[v0].unk_0C >> 16;

                CreateAffineTransformationMatrix(&v5, 0, FX32_ONE, FX32_ONE, AFFINE_MODE_NORMAL);

                v12 = v6 + v4->unk_00[v0].unk_08;
                v13 = v7 + v4->unk_00[v0].unk_0A;

                if (v4->unk_604 == 2) {
                    v12 %= 256;
                    v13 %= 256;
                } else if (v4->unk_604 == 1) {
                    if (v12 < 0) {
                        v12 = 256 + v12;
                    }

                    if (v13 < 0) {
                        v13 = -v13;
                    }

                    v12 %= 256;
                }

                G2x_SetBGyAffine_((u32)&v2[v1].unk_00, &v5, 0, 0, v12, v13);

                v12 = v8 + v4->unk_00[v0].unk_08;
                v13 = v9 + v4->unk_00[v0].unk_0A;

                if (v4->unk_604 == 2) {
                    v12 %= 256;
                    v13 %= 256;
                } else if (v4->unk_604 == 1) {
                    if (v12 < 0) {
                        v12 = 256 + v12;
                    }

                    if (v13 < 0) {
                        v13 = -v13;
                    }

                    v12 %= 256;
                }

                G2x_SetBGyAffine_((u32)&v2[v1].unk_10, &v5, 0, 0, v12, v13);
            }
        }

        FrontierFacilities_FreeAffineBuffer(v4->unk_600);

        Heap_Free(v4);
        SysTask_Done(param0);

        return;
    }

    v2 = FrontierFacilities_GetAffineWriteBuffer(v4->unk_600);

    for (v0 = 0; v0 < (192 / 2); v0++) {
        v4->unk_00[v0].unk_08 += v4->unk_00[v0].unk_04;
        v4->unk_00[v0].unk_0A += v4->unk_00[v0].unk_06;

        for (v1 = v4->unk_00[v0].unk_00; v1 < v4->unk_00[v0].unk_02; v1++) {
            s16 v14, v15;
            s16 v16, v17;

            v14 = v4->unk_00[v0].unk_0C & 0xFFFF;
            v15 = v4->unk_00[v0].unk_0C >> 16;

            CreateAffineTransformationMatrix(&v5, 0, FX32_ONE, FX32_ONE, AFFINE_MODE_NORMAL);

            v16 = v6 + v4->unk_00[v0].unk_08;
            v17 = v7 + v4->unk_00[v0].unk_0A;

            if (v4->unk_604 == 2) {
                v16 %= 256;
                v17 %= 256;
            } else if (v4->unk_604 == 1) {
                if (v16 < 0) {
                    v16 = 256 + v16;
                }

                if (v17 < 0) {
                    v17 = -v17;
                }

                v16 %= 256;
            }

            G2x_SetBGyAffine_((u32)&v2[v1].unk_00, &v5, 0, 0, v16, v17);

            v16 = v8 + v4->unk_00[v0].unk_08;
            v17 = v9 + v4->unk_00[v0].unk_0A;

            if (v4->unk_604 == 2) {
                v16 %= 256;
                v17 %= 256;
            } else if (v4->unk_604 == 1) {
                if (v16 < 0) {
                    v16 = 256 + v16;
                }

                if (v17 < 0) {
                    v17 = -v17;
                }

                v16 %= 256;
            }

            G2x_SetBGyAffine_((u32)&v2[v1].unk_10, &v5, 0, 0, v16, v17);
        }
    }
}

static BOOL FrontierFacilities_NamingScreenAffineWaveA(FrontierFacilitiesNamingScreen *param0)
{
    FrontierFacilitiesAffineEntry v0;

    switch (param0->unk_04) {
    case 0:
        FrontierFacilities_StartScreenFlash(1, 16, -16, &param0->unk_0C, 2);
        param0->unk_04++;
        break;
    case 1:
        if (param0->unk_0C == 0) {
            break;
        }

        MI_CpuClear8(&v0, sizeof(FrontierFacilitiesAffineEntry));

        param0->unk_10 = 0;
        param0->unk_24 = Heap_Alloc(HEAP_ID_94, sizeof(FrontierFacilitiesAffineScroll));
        param0->unk_24->unk_604 = 1;
        param0->unk_24->unk_600 = FrontierFacilities_NewAffineBuffer((u32)&reg_G2_BG2PA, &v0, HEAP_ID_94);

        int v1;

        for (v1 = 0; v1 < (192 / 2); v1++) {
            param0->unk_24->unk_00[v1].unk_00 = (v1 * 2);
            param0->unk_24->unk_00[v1].unk_02 = param0->unk_24->unk_00[v1].unk_00 + 2;
            param0->unk_24->unk_00[v1].unk_04 = ((((192 / 2) / 2) - v1) + 1) % 8;
            param0->unk_24->unk_00[v1].unk_06 = ((((192 / 2) / 2) - v1) + 1) / 4;
            param0->unk_24->unk_00[v1].unk_08 = 0;
            param0->unk_24->unk_00[v1].unk_0A = 0;
            param0->unk_24->unk_00[v1].unk_0C = FrontierFacilities_PackU16Pair(0, 0);
        }

        BrightnessController_StartTransition(40, -16, 0, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ, BRIGHTNESS_MAIN_SCREEN);
        SysTask_Start(FrontierFacilities_AffineScrollTask, param0, 0x1000);

        param0->unk_04++;
        break;
    case 2:
        if (BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN) == FALSE) {
            break;
        }

        param0->unk_10 = 1;

        Bg_ToggleLayer(BG_LAYER_MAIN_3, 0);
        Bg_SetOffset(param0->unk_00->bgConfig, 3, 0, 0);
        Bg_SetOffset(param0->unk_00->bgConfig, 3, 3, 0);

        param0->unk_04++;
        break;
    default:
        return FALSE;
    }

    return TRUE;
}

static BOOL FrontierFacilities_NamingScreenAffineWaveB(FrontierFacilitiesNamingScreen *param0)
{
    FrontierFacilitiesAffineEntry v0;

    switch (param0->unk_04) {
    case 0:
        FrontierFacilities_StartScreenFlash(1, 16, -16, &param0->unk_0C, 2);
        param0->unk_04++;
        break;
    case 1:
        if (param0->unk_0C == 0) {
            break;
        }

        MI_CpuClear8(&v0, sizeof(FrontierFacilitiesAffineEntry));

        param0->unk_10 = 0;
        param0->unk_24 = Heap_Alloc(HEAP_ID_94, sizeof(FrontierFacilitiesAffineScroll));
        param0->unk_24->unk_604 = 2;
        param0->unk_24->unk_600 = FrontierFacilities_NewAffineBuffer((u32)&reg_G2_BG2PA, &v0, HEAP_ID_94);

        int v1;

        for (v1 = 0; v1 < (192 / 2); v1++) {
            param0->unk_24->unk_00[v1].unk_00 = (v1 * 2);
            param0->unk_24->unk_00[v1].unk_02 = param0->unk_24->unk_00[v1].unk_00 + 2;
            param0->unk_24->unk_00[v1].unk_04 = ((((192 / 2) / 2) - v1) / 8) + 1;

            if (v1 % 2) {
                param0->unk_24->unk_00[v1].unk_04 *= -1;
            }

            if (v1 < ((192 / 2) / 2)) {
                param0->unk_24->unk_00[v1].unk_06 = v1;
            } else {
                param0->unk_24->unk_00[v1].unk_06 = (192 / 2) - v1;
            }

            param0->unk_24->unk_00[v1].unk_08 = 0;
            param0->unk_24->unk_00[v1].unk_0A = 0;
            param0->unk_24->unk_00[v1].unk_0C = FrontierFacilities_PackU16Pair(0, 0);
        }

        BrightnessController_StartTransition(40, -16, 0, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ, BRIGHTNESS_MAIN_SCREEN);
        SysTask_Start(FrontierFacilities_AffineScrollTask, param0, 0x1000);

        param0->unk_04++;
        break;
    case 2:
        if (BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN) == FALSE) {
            break;
        }

        param0->unk_10 = 1;

        Bg_ToggleLayer(BG_LAYER_MAIN_3, 0);
        Bg_SetOffset(param0->unk_00->bgConfig, 3, 0, 0);
        Bg_SetOffset(param0->unk_00->bgConfig, 3, 3, 0);

        param0->unk_04++;
        break;
    default:
        return FALSE;
    }

    return TRUE;
}

static BOOL FrontierFacilities_NamingScreenBg3Scroll(FrontierFacilitiesNamingScreen *param0)
{
    switch (param0->unk_04) {
    case 0:
        FrontierFacilities_InitScreenScroll(&param0->unk_18, HEAP_ID_94);
        param0->unk_04++;
        break;
    case 1:
        FrontierFacilities_BeginScreenScroll(&param0->unk_18, 0, 191, (0xFFFF / 192) * 2, FX32_CONST(18), 4 * 100, REG_BG3HOFS_ADDR, 0, 5 - 1);
        param0->unk_04++;
        break;
    default:
        break;
    }

    return TRUE;
}

static BOOL FrontierScrCmd_3F(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData;
    FrontierFacilitiesNamingScreen *v1;

    fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    ctx->data[0] = FrontierScriptContext_GetVar(ctx);

    Sound_SetSceneAndPlayBGM(SOUND_SCENE_BATTLE, BATTLE_TRAINER_sseq, 1);

    v1 = Heap_Alloc(HEAP_ID_FIELD2, sizeof(FrontierFacilitiesNamingScreen));
    v1->unk_14 = BattleFrontier_GetFacilityStruct(ctx->scriptMan->frontier);
    v1->unk_04 = 0;
    v1->unk_08 = ctx->data[0];
    v1->unk_00 = FrontierScriptManager_GetGraphics(ctx->scriptMan);

    BattleFrontier_SetFacilityStruct(ctx->scriptMan->frontier, v1);
    FrontierScriptContext_Pause(ctx, FrontierFacilities_UpdateNamingScreen);
    PaletteData_FillBufferRange(v1->unk_00->plttData, PLTTBUF_MAIN_BG, PLTTSEL_BOTH, 0x0, 0, 1);

    return TRUE;
}

static BOOL FrontierFacilities_UpdateNamingScreen(FrontierScriptContext *ctx)
{
    BOOL v0;
    FrontierFacilitiesNamingScreen *v1 = BattleFrontier_GetFacilityStruct(ctx->scriptMan->frontier);

    v0 = sFrontierFacilitiesNamingScreenStates[v1->unk_08](v1);

    if (v0 == 0) {
        SetScreenColorBrightness(DS_SCREEN_MAIN, COLOR_BLACK);
        SetScreenColorBrightness(DS_SCREEN_SUB, COLOR_BLACK);
        BattleFrontier_SetFacilityStruct(ctx->scriptMan->frontier, v1->unk_14);
        Heap_Free(v1);
    }

    return !v0;
}

static BOOL FrontierScrCmd_GetPlayerObjEventGfx(FrontierScriptContext *ctx)
{
    u16 objEventGfx;
    FieldFrontierDTO *fieldData;
    u16 *destVar = FrontierScriptContext_TryGetVarPointer(ctx);

    fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);

    if (TrainerInfo_Gender(SaveData_GetTrainerInfo(fieldData->saveData)) == GENDER_MALE) {
        objEventGfx = OBJ_EVENT_GFX_PLAYER_M;
    } else {
        objEventGfx = OBJ_EVENT_GFX_PLAYER_F;
    }

    *destVar = objEventGfx;
    return FALSE;
}

static BOOL FrontierScrCmd_InitParticleSystem(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    FrontierGraphics *graphics = BattleFrontier_GetGraphics(scriptMan->frontier);
    u16 index = FrontierScriptContext_GetVar(ctx);
    u16 narcIdx = FrontierScriptContext_GetVar(ctx);
    u16 projection = FrontierScriptContext_GetVar(ctx);

    FrontierParticleSystem_NewParticleSystem(graphics->particleSys, index, narcIdx, projection);

    return FALSE;
}

static BOOL FrontierScrCmd_FreeParticleSystem(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    FrontierGraphics *graphics = BattleFrontier_GetGraphics(scriptMan->frontier);
    u16 index = FrontierScriptContext_GetVar(ctx);
    FrontierParticleSystem_FreeParticleSystem(graphics->particleSys, index);

    return FALSE;
}

static BOOL FrontierScrCmd_CreateParticleSystemEmitter(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    FrontierGraphics *graphics = BattleFrontier_GetGraphics(scriptMan->frontier);
    u16 index = FrontierScriptContext_GetVar(ctx);
    u16 resourceID = FrontierScriptContext_GetVar(ctx);
    ParticleSystem *particleSystem = FrontierParticleSystem_GetParticleSystem(graphics->particleSys, index);

    ParticleSystem_CreateEmitterWithCallback(particleSystem, resourceID, NULL, NULL);

    return FALSE;
}

static BOOL FrontierScrCmd_WaitForParticleSystemEmitters(FrontierScriptContext *ctx)
{
    FrontierScriptContext_Pause(ctx, WaitForEmitters);
    return TRUE;
}

static BOOL WaitForEmitters(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    FrontierGraphics *graphics = BattleFrontier_GetGraphics(scriptMan->frontier);

    return FrontierParticleSystem_NoActiveEmitters(graphics->particleSys) == TRUE;
}

static BOOL FrontierScrCmd_4C(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);
    u16 v2, v3, v4, v5;
    FrontierFacilitiesShakeState *v6 = &v1->unk_A4;

    if (v6->unk_00 != NULL) {
        GF_ASSERT(FALSE);
        SysTask_Done(v6->unk_00);
    }

    v2 = FrontierScriptContext_GetVar(ctx);
    v3 = FrontierScriptContext_GetVar(ctx);
    v4 = FrontierScriptContext_GetVar(ctx);
    v5 = FrontierScriptContext_GetVar(ctx);

    MI_CpuClear8(v6, sizeof(FrontierFacilitiesShakeState));

    v6->unk_04 = v2;
    v6->unk_06 = v3;
    v6->unk_09 = v4;
    v6->unk_0A = v5;
    v6->unk_00 = SysTask_Start(FrontierFacilities_ShakeObjectTask, v6, 70000);

    return FALSE;
}

static BOOL FrontierScrCmd_4D(FrontierScriptContext *ctx)
{
    FrontierScriptContext_Pause(ctx, FrontierFacilities_WaitForOscillationTask);
    return TRUE;
}

static BOOL FrontierFacilities_WaitForOscillationTask(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);

    if (v1->unk_A4.unk_00 == NULL) {
        return TRUE;
    }

    return FALSE;
}

static BOOL FrontierScrCmd_4E(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);
    u16 v2, v3, v4, v5;
    FrontierFacilitiesWindowEffectState *v6 = &v1->unk_B0;

    if (v6->unk_00 != NULL) {
        GF_ASSERT(FALSE);
        SysTask_Done(v6->unk_00);
    }

    MI_CpuClear8(v6, sizeof(FrontierFacilitiesWindowEffectState));

    v6->unk_04 = FrontierScriptContext_GetVar(ctx);
    v6->unk_05 = FrontierScriptContext_GetVar(ctx);
    v6->unk_06 = FrontierScriptContext_GetVar(ctx);
    v6->unk_07 = FrontierScriptContext_GetVar(ctx);
    v6->unk_08 = FrontierScriptContext_GetVar(ctx);
    v6->unk_0A = FrontierScriptContext_GetVar(ctx);
    v6->unk_00 = SysTask_Start(FrontierFacilities_WindowEffectTask, v6, 300);

    return FALSE;
}

static BOOL FrontierScrCmd_4F(FrontierScriptContext *ctx)
{
    FrontierScriptContext_Pause(ctx, FrontierFacilities_WaitForWindowRegionTask);
    return TRUE;
}

static BOOL FrontierFacilities_WaitForWindowRegionTask(FrontierScriptContext *ctx)
{
    FrontierScriptManager *v0 = ctx->scriptMan;
    FrontierGraphics *v1 = BattleFrontier_GetGraphics(v0->frontier);

    if (v1->unk_B0.unk_00 == NULL) {
        return TRUE;
    }

    return FALSE;
}

static BOOL FrontierScrCmd_Dummy96(FrontierScriptContext *ctx)
{
    u16 unused = FrontierScriptContext_ReadHalfWord(ctx);

    return FALSE;
}

static BOOL FrontierScrCmd_45(FrontierScriptContext *ctx)
{
    Party *party;
    Pokemon *mon;
    FieldFrontierDTO *fieldData;
    FrontierGraphics *v3 = FrontierScriptManager_GetGraphics(ctx->scriptMan);
    u16 slot = FrontierScriptContext_GetVar(ctx);
    u16 x = FrontierScriptContext_GetVar(ctx);
    u16 y = FrontierScriptContext_GetVar(ctx);
    u16 v7 = FrontierScriptContext_ReadHalfWord(ctx);
    u16 blendFraction = FrontierScriptContext_ReadHalfWord(ctx);
    u16 blendTarget = FrontierScriptContext_ReadHalfWord(ctx);

    fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    party = SaveData_GetParty(fieldData->saveData);
    mon = Party_GetPokemonBySlotIndex(party, slot);
    blendFraction = 8;
    blendTarget = GX_RGB(0, 0, 0);

    FrontierFacilities_CreatePokemonFieldSprite(v3, mon, HEAP_ID_FIELD2, v7, x, y, 0, 0, blendFraction, blendTarget);
    return FALSE;
}

static BOOL FrontierScrCmd_46(FrontierScriptContext *ctx)
{
    FrontierGraphics *v0 = FrontierScriptManager_GetGraphics(ctx->scriptMan);
    u16 v1 = FrontierScriptContext_ReadHalfWord(ctx);

    FrontierFacilities_DeletePokemonFieldSprite(v0, v1);
    return FALSE;
}

static BOOL FrontierScrCmd_PlayFrontierBrainEncounterEffect(FrontierScriptContext *ctx)
{
    FrontierGraphics *graphics = FrontierScriptManager_GetGraphics(ctx->scriptMan);
    u16 facility = FrontierScriptContext_ReadHalfWord(ctx);
    s16 v2, v3;

    FrontierFacilities_GetViewOffset(graphics, &v2, &v3);
    BattleFrontier_PlayFrontierBrainEncounterEffect(facility, graphics->bgConfig, graphics->spriteSystem, graphics->spriteMan, graphics->plttData, &ctx->data[0], v2, v3);
    Sound_SetSceneAndPlayBGM(SOUND_SCENE_BATTLE, BATTLE_FRONTIER_BRAIN_sseq, 1);
    FrontierScriptContext_Pause(ctx, WaitForFrontierBrainEncounterEffectFinished);

    return TRUE;
}

static BOOL WaitForFrontierBrainEncounterEffectFinished(FrontierScriptContext *ctx)
{
    UNUSED(BattleFrontier_GetGraphics(ctx->scriptMan->frontier));

    return ctx->data[0] == TRUE;
}

static BOOL FrontierScrCmd_IncrementRecordValue(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData;
    u16 recordID = FrontierScriptContext_ReadHalfWord(ctx);

    fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    GameRecords_IncrementRecordValue(SaveData_GetGameRecords(fieldData->saveData), recordID);

    return FALSE;
}

static BOOL FrontierScrCmd_AddToRecordValue(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData;
    u16 recordID = FrontierScriptContext_ReadHalfWord(ctx);
    u16 value = FrontierScriptContext_GetVar(ctx);

    fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    GameRecords_AddToRecordValue(SaveData_GetGameRecords(fieldData->saveData), recordID, value);

    return FALSE;
}

static BOOL FrontierScrCmd_IncrementTrainerScore(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData;
    u16 scoreID = FrontierScriptContext_ReadHalfWord(ctx);

    fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    GameRecords_IncrementTrainerScore(SaveData_GetGameRecords(fieldData->saveData), scoreID);

    return FALSE;
}

static BOOL FrontierScrCmd_4B(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData;
    u16 *destVar = FrontierScriptContext_TryGetVarPointer(ctx);

    fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    *destVar = BattleFrontierStats_IsDebugBuild(fieldData->saveData);

    return FALSE;
}

static BOOL FrontierScrCmd_71(FrontierScriptContext *ctx)
{
    u16 *destVar = FrontierScriptContext_TryGetVarPointer(ctx);

    *destVar = BattleRecording_CheckSystemVersions();
    return FALSE;
}

static BOOL FrontierScrCmd_SetWiFiListHostFriendCurrentDate(FrontierScriptContext *ctx)
{
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    WiFiList *wiFiList = SaveData_GetWiFiList(fieldData->saveData);

    WiFiList_SetHostFriendCurrentDate(wiFiList, NintendoWFC_GetHostFriendIdx());
    return FALSE;
}

static BOOL FrontierScrCmd_C8(FrontierScriptContext *ctx)
{
    u16 v0;
    TVBroadcast *broadcast;
    TrainerInfo *trainerInfo;
    FieldFrontierDTO *fieldData = BattleFrontier_GetFieldData(ctx->scriptMan->frontier);
    broadcast = SaveData_GetTVBroadcast(fieldData->saveData);
    v0 = FrontierScriptContext_GetVar(ctx);
    trainerInfo = CommInfo_TrainerInfo(1 - CommSys_CurNetId());

    TVBroadcast_SetBattleFrontierFrontlineNewsMultiInfo(broadcast, v0, trainerInfo);
    return FALSE;
}

static BOOL FrontierScrCmd_C9(FrontierScriptContext *ctx)
{
    u16 v0 = FrontierScriptContext_GetVar(ctx);

    CommSys_SetRecvLimitEnabled(v0);
    return FALSE;
}

static BOOL FrontierScrCmd_SetMenuXOriginSide(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    u8 isRightSide = FrontierScriptContext_ReadByte(ctx);
    FrontierMenuManager_SetHorizontalAnchor(scriptMan->menuMan, isRightSide);
    return TRUE;
}

static BOOL FrontierScrCmd_SetMenuYOriginSide(FrontierScriptContext *ctx)
{
    FrontierScriptManager *scriptMan = ctx->scriptMan;
    u8 isBottomSide = FrontierScriptContext_ReadByte(ctx);
    FrontierMenuManager_SetVerticalAnchor(scriptMan->menuMan, isBottomSide);
    return TRUE;
}
