
#include "wifi_lobby_minigame_bucket/wifi_lobby_minigame_bucket_game.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/font_oam.h"
#include "struct_decls/struct_02012744_decl.h"
#include "struct_decls/struct_02012B20_decl.h"
#include "struct_defs/struct_020127E8.h"

#include "geonet/struct_geonet_angle.h"
#include "wifi_lobby_minigame/wifi_lobby_minigame.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_intro_animation_decl.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_mode.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_stage_data.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_stage.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_throw_data.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_final_scores.h"

#include "bg_window.h"
#include "brightness_controller.h"
#include "camera.h"
#include "char_transfer.h"
#include "easy3d_object.h"
#include "font.h"
#include "g3d_pipeline.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "math_util.h"
#include "message.h"
#include "narc.h"
#include "pltt_transfer.h"
#include "render_oam.h"
#include "render_window.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "system.h"
#include "text.h"
#include "touch_pad.h"
#include "trainer_info.h"
#include "font_oam.h"
#include "g3_buffer.h"
#include "comm_tool.h"
#include "vram_transfer.h"

typedef struct {
    fx32 unk_00;
    fx32 unk_04;
    fx32 unk_08;
    fx32 unk_0C;
    int unk_10;
    int unk_14;
} WiFiLobbyMinigameBucketMotion;

typedef struct {
    u32 unk_00;
    s32 unk_04;
    s32 unk_08;
    Window unk_0C;
} WiFiLobbyMinigameBucketIntroWindow;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    fx32 unk_08;
    MtxFx33 unk_0C;
    MtxFx33 unk_30;
    MtxFx33 unk_54;
    VecFx32 unk_78;
    VecFx32 unk_84;
    fx32 unk_90;
    fx32 unk_94;
    fx32 unk_98;
    VecFx32 unk_9C;
    fx32 unk_A8;
    fx32 unk_AC;
    fx32 unk_B0;
    fx32 unk_B4;
    fx32 unk_B8;
    fx32 unk_BC;
    fx32 unk_C0;
    fx32 unk_C4;
    fx32 unk_C8;
    fx32 unk_CC;
    fx32 unk_D0;
    fx32 unk_D4;
    VecFx32 unk_D8;
    fx32 unk_E4;
} WiFiLobbyMinigameBucketCamera;

typedef struct {
    Easy3DObject unk_00[3];
    Easy3DModel unk_168[3];
    Easy3DAnim unk_198[6];
    u16 unk_210;
    u16 unk_212;
    Easy3DAnim unk_214[1];
    fx32 unk_228;
    u16 unk_22C;
    u16 unk_22E;
} WiFiLobbyMinigameBucketSwalotModel;

typedef struct {
    u16 unk_00;
    u16 unk_02;
    VecFx32 unk_04;
    fx32 unk_10;
    VecFx32 unk_14;
    s32 unk_20;
    BOOL unk_24;
} WiFiLobbyMinigameBucketProjectile;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    WiFiLobbyMinigameBucketProjectile unk_04;
    VecFx32 unk_2C;
    s16 unk_38;
    u16 unk_3A;
    BOOL unk_3C;
    fx32 unk_40;
} WiFiLobbyMinigameBucketProjectileState;

typedef struct {
    u32 unk_00;
    NNSG2dSVec2 unk_04[8];
    u16 unk_24;
    u16 unk_26;
    u32 unk_28;
} WiFiLobbyMinigameBucketTouchBuffer;

typedef struct {
    Easy3DModel unk_00[5];
    Easy3DModel unk_50;
    SpriteResource *unk_60[4];
    SpriteResourcesHeader unk_70;
} WiFiLobbyMinigameBucketBerryModels;

typedef struct {
    Sprite *unk_00;
    Easy3DObject unk_04;
    Easy3DObject unk_7C;
    BOOL unk_F4;
    const WiFiLobbyMinigameBucketProjectileState *unk_F8;
    u16 unk_FC;
    u16 unk_FE;
    u16 unk_100;
    u16 unk_102;
    s16 unk_104;
} WiFiLobbyMinigameBucketBerry;

typedef struct {
    BOOL unk_00;
    Sprite *unk_04;
} WiFiLobbyMinigameBucketCursor;

typedef struct {
    BOOL unk_00;
    Sprite *unk_04;
    VecFx32 unk_08;
    s32 unk_14;
    BOOL unk_18;
} WiFiLobbyMinigameBucketSplashParticle;

typedef struct {
    WiFiLobbyMinigameBucketSplashParticle unk_00[8];
} WiFiLobbyMinigameBucketSplash;

typedef struct {
    Sprite *unk_00[3];
    u32 unk_0C[3];
    VecFx32 unk_18[3];
    BOOL unk_3C;
} WiFiLobbyMinigameBucketThrowSprite;

typedef struct {
    WiFiLobbyMinigameBucketThrowSprite unk_00[4];
} WiFiLobbyMinigameBucketThrowSprites;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    WiFiLobbyMinigameBucketMotion unk_08;
} WiFiLobbyMinigameBucketSceneState;

typedef struct {
    Easy3DObject unk_00[3];
    Easy3DModel unk_168[3];
    Easy3DAnim unk_198[3];
    fx32 unk_1D4;
    u8 unk_1D8;
    u8 unk_1D9;
    s16 unk_1DA;
    fx32 unk_1DC;
    fx32 unk_1E0;
} WiFiLobbyMinigameBucketBucketModel;

typedef struct {
    u16 unk_00;
    s16 unk_02;
    s16 unk_04;
    u8 unk_06;
    u8 unk_07;
} WiFiLobbyMinigameBucketBgFade;

typedef struct {
    WiFiLobbyMinigameBucketStageData unk_00;
    WiFiLobbyMinigameBucketStageData unk_18;
    WiFiLobbyMinigameBucketStageData unk_30;
    s32 unk_48;
} WiFiLobbyMinigameBucketStageTransition;

typedef struct {
    SpriteResource *unk_00[4];
    SpriteResourcesHeader unk_10;
    Sprite *unk_34;
    u8 unk_38;
    u8 unk_39;
    u8 unk_3A;
    u8 unk_3B;
    s32 unk_3C;
} WiFiLobbyMinigameBucketSwalot;

typedef struct {
    u32 unk_00[4];
    u32 unk_10;
    u32 unk_14;
} WiFiLobbyMinigameBucketScoreBoard;

typedef struct {
    SpriteResource *unk_00[4];
    SpriteResourcesHeader unk_10;
    Sprite *unk_34;
    Window unk_38;
    FontOAM *unk_48;
    FontOAMWindow *unk_4C;
    CharTransferAllocation unk_50;
    String *unk_5C;
    SpriteResource *unk_60;
    WiFiLobbyMinigameBucketMotion unk_64;
    WiFiLobbyMinigameBucketMotion unk_7C;
    s16 unk_94;
    s16 unk_96;
    u16 unk_98;
    s16 unk_9A;
    enum HeapID heapID;
} WiFiLobbyMinigameBucketScoreDisplay;

typedef struct {
    u16 unk_00;
    u8 unk_02;
    s8 unk_03;
} WiFiLobbyMinigameBucketFinishEffect;

typedef struct {
    BgConfig *unk_00;
    StringTemplate *unk_04;
    MessageLoader *unk_08;
    String *unk_0C;
    String *unk_10;
    u16 unk_14;
    u16 unk_16;
    G3DPipelineBuffers *unk_18;
    SpriteList *unk_1C;
    G2dRenderer unk_20;
    SpriteResourceCollection *unk_1AC[4];
    SpriteResourcesHeader unk_1BC;
    SpriteResource *unk_1E0[4];
    FontOAMManager *unk_1F0;
    Camera *camera;
    VecFx32 unk_1F8;
    WiFiLobbyMinigameBucketBucketModel unk_204;
    WiFiLobbyMinigameBucketThrowSprites unk_3E8;
    WiFiLobbyMinigameBucketIntroWindow unk_4E8;
    WiFiLobbyMinigameBucketSceneState unk_504;
    WiFiLobbyMinigameBucketSwalotModel unk_524;
    WiFiLobbyMinigameIntroAnimation *unk_754;
    WiFiLobbyMinigameBucketBgFade unk_758;
    WiFiLobbyMinigameBucketBerryModels unk_760;
    WiFiLobbyMinigameBucketBerry unk_7F4[96];
    WiFiLobbyMinigameBucketCursor unk_6A34;
    WiFiLobbyMinigameBucketSplash unk_6A3C;
    WiFiLobbyMinigameBucketScoreDisplay unk_6B1C;
    NNSFndAllocator unk_6BBC;
} WiFiLobbyMinigameBucketScene;

typedef struct WiFiLobbyMinigameBucketGame_t {
    u32 unk_00;
    BOOL unk_04;
    s32 unk_08;
    s32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    WiFiLobbyMinigameBucketTouchBuffer unk_20;
    WiFiLobbyMinigameBucketProjectileState unk_4C[96];
    WiFiLobbyMinigameBucketCamera unk_19CC;
    WiFiLobbyMinigameBucketScene unk_1AB4;
    WiFiLobbyMinigameBucketFinalScores unk_8680;
    TouchPadDataBuffer unk_8690;
    WiFiLobbyMinigameBucketStageTransition unk_86D4;
    const WiFiLobbyMinigameBucketStage *unk_8720;
    u16 unk_8724;
    u16 unk_8726;
    WiFiLobbyMinigameBucketMode unk_8728;
    BOOL unk_872C;
    WiFiLobbyMinigameBucketSwalot unk_8730;
    WiFiLobbyMinigameBucketScoreBoard unk_8770;
    WiFiLobbyMinigameBucketFinishEffect unk_8788;
} WiFiLobbyMinigameBucketGame;

static void WiFiLobbyMinigameBucket_InitMotion(WiFiLobbyMinigameBucketMotion *param0, fx32 param1, fx32 param2, fx32 param3, int param4);
static BOOL WiFiLobbyMinigameBucket_UpdateMotion(WiFiLobbyMinigameBucketMotion *param0);
static void WiFiLobbyMinigameBucket_GetPlayerNamePosition(u32 param0, u32 param1, u32 param2, s32 *param3, s32 *param4);
static void WiFiLobbyMinigameBucket_SpawnThrowFromSwalot(WiFiLobbyMinigameBucketGame *param0, u16 param1, u16 param2, u16 param3, u16 param4, u32 param5);
static u32 WiFiLobbyMinigameBucket_GetScoreForHit(WiFiLobbyMinigameBucketGame *param0);
static void WiFiLobbyMinigameBucket_InitThrowSprites(WiFiLobbyMinigameBucketThrowSprites *param0, WiFiLobbyMinigameBucketScene *param1, u32 param2, u32 param3, u32 param4);
static void WiFiLobbyMinigameBucket_FreeThrowSprites(WiFiLobbyMinigameBucketThrowSprites *param0, WiFiLobbyMinigameBucketScene *param1);
static void WiFiLobbyMinigameBucket_ShowThrowSprite(WiFiLobbyMinigameBucketThrowSprites *param0, u32 param1, u32 param2, int param3);
static void WiFiLobbyMinigameBucket_UpdateThrowSprites(WiFiLobbyMinigameBucketThrowSprites *param0);
static void WiFiLobbyMinigameBucket_InitThrowSprite(WiFiLobbyMinigameBucketThrowSprite *param0, AffineSpriteListTemplate *param1, WiFiLobbyMinigameBucketScene *param2, u32 param3, u32 param4, u32 param5, u32 param6);
static void WiFiLobbyMinigameBucket_FreeThrowSprite(WiFiLobbyMinigameBucketThrowSprite *param0);
static void WiFiLobbyMinigameBucket_ShowThrowSpriteAnim(WiFiLobbyMinigameBucketThrowSprite *param0, u32 param1, u32 param2, int param3);
static void WiFiLobbyMinigameBucket_UpdateThrowSprite(WiFiLobbyMinigameBucketThrowSprite *param0);
static void WiFiLobbyMinigameBucket_SetThrowSpritePosition(WiFiLobbyMinigameBucketThrowSprite *param0, u32 param1);
static void WiFiLobbyMinigameBucket_HideThrowSprite(WiFiLobbyMinigameBucketThrowSprite *param0, u32 param1);
static void WiFiLobbyMinigameBucket_FreeIntroWindow(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1);
static void WiFiLobbyMinigameBucket_ShowIntroWindow(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1);
static BOOL WiFiLobbyMinigameBucket_IsIntroAnimationRunning(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1);
static void WiFiLobbyMinigameBucket_HideIntroWindow(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1);
static void WiFiLobbyMinigameBucket_PlaySwalotIntroAnim(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1);
static BOOL WiFiLobbyMinigameBucket_WaitIntroWindow(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1);
static void WiFiLobbyMinigameBucket_UpdateSwalotModel(WiFiLobbyMinigameBucketScene *param0, const WiFiLobbyMinigameBucketCamera *param1);
static void WiFiLobbyMinigameBucket_ResetIntroState(WiFiLobbyMinigameBucketScene *param0, u32 param1, u32 param2, u32 param3);
static void WiFiLobbyMinigameBucket_Noop(WiFiLobbyMinigameBucketScene *param0, u32 param1);
static void WiFiLobbyMinigameBucket_ShowSwalotAnim(WiFiLobbyMinigameBucketScene *param0);
static BOOL WiFiLobbyMinigameBucket_UpdateSwalotIntroAnim(WiFiLobbyMinigameBucketScene *param0);
static BOOL WiFiLobbyMinigameBucket_IsIntroAnimationDone(WiFiLobbyMinigameBucketScene *param0);
static void WiFiLobbyMinigameBucket_InitCamera(const WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketCamera *param1);
static void WiFiLobbyMinigameBucket_UpdateCamera(const WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketCamera *param1);
static void WiFiLobbyMinigameBucket_SetCameraActive(WiFiLobbyMinigameBucketCamera *param0, BOOL param1);
static void WiFiLobbyMinigameBucket_SetCameraPitch(WiFiLobbyMinigameBucketCamera *param0, u16 param1);
static void WiFiLobbyMinigameBucket_SetCameraYaw(WiFiLobbyMinigameBucketCamera *param0, u16 param1);
static u32 WiFiLobbyMinigameBucket_CheckProjectileCollision(const WiFiLobbyMinigameBucketCamera *param0, const VecFx32 *param1, const VecFx32 *param2, VecFx32 *param3);
static BOOL WiFiLobbyMinigameBucket_IsInsideBucket(const WiFiLobbyMinigameBucketCamera *param0, const VecFx32 *param1);
static fx32 WiFiLobbyMinigameBucket_GetCameraHeight(const WiFiLobbyMinigameBucketCamera *param0, u16 param1);
static fx32 WiFiLobbyMinigameBucket_GetCameraDepth(const WiFiLobbyMinigameBucketCamera *param0, u16 param1);
static void WiFiLobbyMinigameBucket_SetCameraScale(WiFiLobbyMinigameBucketCamera *param0, fx32 param1);
static void WiFiLobbyMinigameBucket_SetCameraRoll(WiFiLobbyMinigameBucketCamera *param0, u16 param1);
static void WiFiLobbyMinigameBucket_SetCameraDistance(WiFiLobbyMinigameBucketCamera *param0, fx32 param1);
static u16 WiFiLobbyMinigameBucket_GetCameraAngleStage0(const WiFiLobbyMinigameBucketCamera *param0, s32 param1, s32 param2);
static u16 WiFiLobbyMinigameBucket_GetCameraAngleStage1(const WiFiLobbyMinigameBucketCamera *param0, s32 param1, s32 param2);
static u16 WiFiLobbyMinigameBucket_GetCameraAngleStage2(const WiFiLobbyMinigameBucketCamera *param0, s32 param1, s32 param2);
static void WiFiLobbyMinigameBucket_ProjectileToThrowData(const WiFiLobbyMinigameBucketProjectile *param0, WiFiLobbyMinigameBucketThrowData *param1);
static void WiFiLobbyMinigameBucket_ThrowDataToProjectile(const WiFiLobbyMinigameBucketThrowData *param0, WiFiLobbyMinigameBucketProjectile *param1);
static void WiFiLobbyMinigameBucket_SpawnProjectile(WiFiLobbyMinigameBucketGame *param0, const WiFiLobbyMinigameBucketProjectile *param1, u32 param2);
static void WiFiLobbyMinigameBucket_SetProjectileState(WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketProjectileState *param1, BOOL param2, u32 param3);
static void WiFiLobbyMinigameBucket_ClearProjectile(WiFiLobbyMinigameBucketProjectileState *param0);
static void WiFiLobbyMinigameBucket_UpdateProjectiles(WiFiLobbyMinigameBucketGame *param0);
static void WiFiLobbyMinigameBucket_UpdateProjectile(WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketProjectileState *param1);
static void WiFiLobbyMinigameBucket_UpdateAllProjectileSprites(WiFiLobbyMinigameBucketGame *param0);
static void WiFiLobbyMinigameBucket_FinishProjectiles(WiFiLobbyMinigameBucketGame *param0);
static void WiFiLobbyMinigameBucket_FinishProjectile(WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketGame *param1);
static void WiFiLobbyMinigameBucket_ResetProjectiles(WiFiLobbyMinigameBucketGame *param0);
static BOOL WiFiLobbyMinigameBucket_HasActiveProjectiles(const WiFiLobbyMinigameBucketGame *param0);
static fx32 WiFiLobbyMinigameBucket_GetProjectileSpeed(const WiFiLobbyMinigameBucketProjectileState *param0);
static void WiFiLobbyMinigameBucket_GetProjectileVelocity(const WiFiLobbyMinigameBucketProjectileState *param0, VecFx32 *param1);
static void WiFiLobbyMinigameBucket_BounceProjectile(WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketGame *param1, BOOL param2);
static void WiFiLobbyMinigameBucket_ReflectProjectile(WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketGame *param1, BOOL param2, fx32 param3, BOOL param4);
static void WiFiLobbyMinigameBucket_UpdateBouncingProjectile(WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketGame *param1);
static BOOL WiFiLobbyMinigameBucket_IsProjectileNearBucket(const WiFiLobbyMinigameBucketProjectileState *param0);
static BOOL WiFiLobbyMinigameBucket_IsProjectileClose(const WiFiLobbyMinigameBucketProjectileState *param0);
static BOOL WiFiLobbyMinigameBucket_IsProjectileFar(WiFiLobbyMinigameBucketProjectileState *param0);
static void WiFiLobbyMinigameBucket_StartProjectileSink(WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketGame *param1);
static void WiFiLobbyMinigameBucket_UpdateSinkingProjectile(WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketGame *param1);
static void WiFiLobbyMinigameBucket_MoveProjectile(WiFiLobbyMinigameBucketProjectileState *param0, const VecFx32 *param1);
static void WiFiLobbyMinigameBucket_HandleTouchInput(WiFiLobbyMinigameBucketGame *param0);
static void WiFiLobbyMinigameBucket_HandleTouchRelease(WiFiLobbyMinigameBucketGame *param0);
static void WiFiLobbyMinigameBucket_HandleTouchDrag(WiFiLobbyMinigameBucketGame *param0);
static BOOL WiFiLobbyMinigameBucket_IsTouchInPlayArea(WiFiLobbyMinigameBucketGame *param0);
static void WiFiLobbyMinigameBucket_ResetTouchBuffer(WiFiLobbyMinigameBucketTouchBuffer *param0);
static void WiFiLobbyMinigameBucket_PushTouchPoint(WiFiLobbyMinigameBucketTouchBuffer *param0, NNSG2dSVec2 param1);
static BOOL WiFiLobbyMinigameBucket_PopTouchPoint(WiFiLobbyMinigameBucketTouchBuffer *param0, NNSG2dSVec2 *param1);
static BOOL WiFiLobbyMinigameBucket_PeekTouchPoint(WiFiLobbyMinigameBucketTouchBuffer *param0, NNSG2dSVec2 *param1);
static BOOL WiFiLobbyMinigameBucket_PeekLastTouchPoint(WiFiLobbyMinigameBucketTouchBuffer *param0, NNSG2dSVec2 *param1);
static u32 WiFiLobbyMinigameBucket_GetTouchPointCount(WiFiLobbyMinigameBucketTouchBuffer *param0);
static void WiFiLobbyMinigameBucket_ResetTouch(WiFiLobbyMinigameBucketGame *param0);
static void WiFiLobbyMinigameBucket_InitStageTransition(WiFiLobbyMinigameBucketStageTransition *param0, const WiFiLobbyMinigameBucketStage *param1, const WiFiLobbyMinigameBucketMode *param2);
static void WiFiLobbyMinigameBucket_StartStageTransition(WiFiLobbyMinigameBucketStageTransition *param0, const WiFiLobbyMinigameBucketStage *param1, const WiFiLobbyMinigameBucketMode *param2, u16 param3, u16 param4);
static BOOL WiFiLobbyMinigameBucket_UpdateStageTransition(WiFiLobbyMinigameBucketStageTransition *param0);
static void WiFiLobbyMinigameBucket_ApplyStageTransition(WiFiLobbyMinigameBucketGame *param0, const WiFiLobbyMinigameBucketStageTransition *param1);
static void WiFiLobbyMinigameBucket_ApplyStageData(WiFiLobbyMinigameBucketGame *param0, const WiFiLobbyMinigameBucketStageData *param1);
static void WiFiLobbyMinigameBucket_GetStageData(const WiFiLobbyMinigameBucketStage *param0, const WiFiLobbyMinigameBucketMode *param1, u32 param2, WiFiLobbyMinigameBucketStageData *param3);
static void WiFiLobbyMinigameBucket_InitSwalot(WiFiLobbyMinigameBucketSwalot *param0, WiFiLobbyMinigameBucketScene *param1, u32 heapID);
static void WiFiLobbyMinigameBucket_FreeSwalot(WiFiLobbyMinigameBucketSwalot *param0, WiFiLobbyMinigameBucketScene *param1);
static void WiFiLobbyMinigameBucket_ShowSwalot(WiFiLobbyMinigameBucketSwalot *param0);
static BOOL WiFiLobbyMinigameBucket_UpdateSwalot(WiFiLobbyMinigameBucketSwalot *param0, WiFiLobbyMinigameBucketGame *param1);
static void WiFiLobbyMinigameBucket_InitScoreBoard(WiFiLobbyMinigameBucketScoreBoard *param0);
static void WiFiLobbyMinigameBucket_AddScoreBoardEntry(WiFiLobbyMinigameBucketScoreBoard *param0, u32 param1, u32 param2);
static void WiFiLobbyMinigameBucket_ResetScoreBoard(WiFiLobbyMinigameBucketScoreBoard *param0);
static u32 WiFiLobbyMinigameBucket_GetScoreBoardLeader(const WiFiLobbyMinigameBucketScoreBoard *param0);
static BOOL WiFiLobbyMinigameBucket_IsScoreBoardFull(const WiFiLobbyMinigameBucketScoreBoard *param0, u32 param1);
static void WiFiLobbyMinigameBucket_InitScene(WiFiLobbyMinigameBucketGame *param0, u32 heapID);
static void WiFiLobbyMinigameBucket_FreeScene(WiFiLobbyMinigameBucketGame *param0);
static void WiFiLobbyMinigameBucket_DrawScene(const WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketScene *param1);
static void WiFiLobbyMinigameBucket_RenderScene(const WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketScene *param1);
static void WiFiLobbyMinigameBucket_SetVramBanks(void);
static void WiFiLobbyMinigameBucket_InitG3D(void);
static void WiFiLobbyMinigameBucket_InitG3DPipeline(WiFiLobbyMinigameBucketScene *param0, u32 param1, u32 param2, u32 heapID);
static void WiFiLobbyMinigameBucket_FreeG3DPipeline(WiFiLobbyMinigameBucketScene *param0);
static void WiFiLobbyMinigameBucket_InitBackgrounds(WiFiLobbyMinigameBucketScene *param0, u32 heapID);
static void WiFiLobbyMinigameBucket_FreeBackgrounds(WiFiLobbyMinigameBucketScene *param0);
static void WiFiLobbyMinigameBucket_InitSpriteSystem(WiFiLobbyMinigameBucketScene *param0, u32 heapID);
static void WiFiLobbyMinigameBucket_FreeSpriteSystem(WiFiLobbyMinigameBucketScene *param0);
static void WiFiLobbyMinigameBucket_InitText(WiFiLobbyMinigameBucketScene *param0, u32 heapID);
static void WiFiLobbyMinigameBucket_FreeText(WiFiLobbyMinigameBucketScene *param0);
static void WiFiLobbyMinigameBucket_InitCamera3D(WiFiLobbyMinigameBucketScene *param0, u32 param1, u32 param2, u32 heapID);
static void WiFiLobbyMinigameBucket_FreeCamera(WiFiLobbyMinigameBucketScene *param0);
static void WiFiLobbyMinigameBucket_UpdateCameraMatrix(WiFiLobbyMinigameBucketScene *param0);
static void WiFiLobbyMinigameBucket_LoadBackgroundTiles(WiFiLobbyMinigameBucketScene *param0, NARC *param1, u32 param2, u32 param3);
static void WiFiLobbyMinigameBucket_Noop2(WiFiLobbyMinigameBucketScene *param0);
static void WiFiLobbyMinigameBucket_LoadSpriteResources(WiFiLobbyMinigameBucketScene *param0, NARC *param1, u32 param2);
static void WiFiLobbyMinigameBucket_FreeSpriteResources(WiFiLobbyMinigameBucketScene *param0);
static void WiFiLobbyMinigameBucket_InitSwalotModel(WiFiLobbyMinigameBucketSwalotModel *param0, NARC *param1, u32 heapID, NNSFndAllocator *param3);
static void WiFiLobbyMinigameBucket_FreeSwalotModel(WiFiLobbyMinigameBucketSwalotModel *param0, NNSFndAllocator *param1);
static void WiFiLobbyMinigameBucket_SetSwalotModelState(WiFiLobbyMinigameBucketSwalotModel *param0, const WiFiLobbyMinigameBucketCamera *param1, int param2);
static void WiFiLobbyMinigameBucket_UpdateSwalotModelAnim(WiFiLobbyMinigameBucketSwalotModel *param0, const WiFiLobbyMinigameBucketCamera *param1, int param2);
static void WiFiLobbyMinigameBucket_SetSwalotModelPosition(WiFiLobbyMinigameBucketSwalotModel *param0, const WiFiLobbyMinigameBucketCamera *param1);
static void WiFiLobbyMinigameBucket_SetSwalotModelRotation(WiFiLobbyMinigameBucketSwalotModel *param0, const WiFiLobbyMinigameBucketCamera *param1);
static void WiFiLobbyMinigameBucket_SetSwalotModelScale(WiFiLobbyMinigameBucketSwalotModel *param0, const WiFiLobbyMinigameBucketCamera *param1);
static void WiFiLobbyMinigameBucket_DrawSwalotModel(WiFiLobbyMinigameBucketSwalotModel *param0, const WiFiLobbyMinigameBucketCamera *param1);
static void WiFiLobbyMinigameBucket_SetSwalotMouthFrame(WiFiLobbyMinigameBucketSwalotModel *param0, u32 param1);
static void WiFiLobbyMinigameBucket_SetSwalotAnim(WiFiLobbyMinigameBucketSwalotModel *param0, u32 param1);
static BOOL WiFiLobbyMinigameBucket_UpdateSwalotAnim(WiFiLobbyMinigameBucketSwalotModel *param0, fx32 param1);
static void WiFiLobbyMinigameBucket_SetSwalotIdleAnim(WiFiLobbyMinigameBucketSwalotModel *param0, BOOL param1);
static void WiFiLobbyMinigameBucket_SetSwalotMouthOpen(WiFiLobbyMinigameBucketSwalotModel *param0, BOOL param1);
static void WiFiLobbyMinigameBucket_SetSwalotAnimIndex(WiFiLobbyMinigameBucketSwalotModel *param0, u32 param1);
static void WiFiLobbyMinigameBucket_UpdateSwalotMouthAnim(WiFiLobbyMinigameBucketSwalotModel *param0);
static void WiFiLobbyMinigameBucket_ScreenToWorld(s16 param0, s16 param1, VecFx32 *param2);
static void WiFiLobbyMinigameBucket_WorldToScreen(const VecFx32 *param0, NNSG2dSVec2 *param1);
static void WiFiLobbyMinigameBucket_RotateWorldToPlayer(const VecFx32 *param0, VecFx32 *param1, u32 param2, u32 param3);
static void WiFiLobbyMinigameBucket_RotatePlayerToWorld(const VecFx32 *param0, VecFx32 *param1, u32 param2, u32 param3);
static void WiFiLobbyMinigameBucket_InitBerryModels(WiFiLobbyMinigameBucketScene *param0, NARC *param1, u32 heapID);
static void WiFiLobbyMinigameBucket_FreeBerryModels(WiFiLobbyMinigameBucketScene *param0);
static void WiFiLobbyMinigameBucket_ShowBerry(WiFiLobbyMinigameBucketScene *param0, const WiFiLobbyMinigameBucketProjectileState *param1, u32 param2, u32 param3);
static void WiFiLobbyMinigameBucket_HideBerry(WiFiLobbyMinigameBucketScene *param0, const WiFiLobbyMinigameBucketProjectileState *param1);
static void WiFiLobbyMinigameBucket_DrawBerries(WiFiLobbyMinigameBucketScene *param0, u32 param1);
static void WiFiLobbyMinigameBucket_InitBerry(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketBerry *param1, u32 param2);
static void WiFiLobbyMinigameBucket_FreeBerry(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketBerry *param1);
static void WiFiLobbyMinigameBucket_ShowBerrySprite(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketBerry *param1, const WiFiLobbyMinigameBucketProjectileState *param2, u32 param3);
static void WiFiLobbyMinigameBucket_ShowBerryModel(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketBerry *param1, const WiFiLobbyMinigameBucketProjectileState *param2);
static void WiFiLobbyMinigameBucket_DrawBerry(WiFiLobbyMinigameBucketBerry *param0, WiFiLobbyMinigameBucketScene *param1, u32 param2);
static void WiFiLobbyMinigameBucket_DrawBerryShadow(WiFiLobbyMinigameBucketBerry *param0);
static void WiFiLobbyMinigameBucket_ResetBerryShadow(WiFiLobbyMinigameBucketBerry *param0);
static void WiFiLobbyMinigameBucket_HideBerryModel(WiFiLobbyMinigameBucketBerry *param0);
static WiFiLobbyMinigameBucketBerry *WiFiLobbyMinigameBucket_AllocBerry(WiFiLobbyMinigameBucketScene *param0);
static BOOL WiFiLobbyMinigameBucket_UpdateBerrySprite(WiFiLobbyMinigameBucketBerry *param0, const WiFiLobbyMinigameBucketProjectileState *param1, u32 param2);
static void WiFiLobbyMinigameBucket_ShowBerryModelInternal(WiFiLobbyMinigameBucketBerry *param0, WiFiLobbyMinigameBucketScene *param1);
static Easy3DModel *WiFiLobbyMinigameBucket_GetBerryModel(const WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketBerryModels *param1);
static void WiFiLobbyMinigameBucket_UpdateBerryRotation(WiFiLobbyMinigameBucketBerry *param0);
static void WiFiLobbyMinigameBucket_InitCursor(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketCursor *param1, u32 param2, u32 param3);
static void WiFiLobbyMinigameBucket_FreeCursor(WiFiLobbyMinigameBucketCursor *param0);
static void WiFiLobbyMinigameBucket_ShowCursor(WiFiLobbyMinigameBucketCursor *param0);
static void WiFiLobbyMinigameBucket_UpdateCursor(WiFiLobbyMinigameBucketCursor *param0);
static void WiFiLobbyMinigameBucket_HideCursor(WiFiLobbyMinigameBucketCursor *param0);
static void WiFiLobbyMinigameBucket_SetCursorPosition(WiFiLobbyMinigameBucketCursor *param0, s32 param1, s32 param2);
static void WiFiLobbyMinigameBucket_InitSplash(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketSplash *param1, u32 param2, u32 param3);
static void WiFiLobbyMinigameBucket_FreeSplash(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketSplash *param1);
static void WiFiLobbyMinigameBucket_UpdateSplash(WiFiLobbyMinigameBucketSplash *param0);
static void WiFiLobbyMinigameBucket_SpawnSplash(WiFiLobbyMinigameBucketSplash *param0, s32 param1, s32 param2);
static void WiFiLobbyMinigameBucket_CalcSplashVelocity(int param0, int param1, int param2, int param3, int param4, s32 *param5, s32 *param6);
static void WiFiLobbyMinigameBucket_InitBucketModel(WiFiLobbyMinigameBucketBucketModel *param0, WiFiLobbyMinigameBucketScene *param1, NARC *param2, int param3, u32 param4, u32 heapID, NNSFndAllocator *param6);
static void WiFiLobbyMinigameBucket_FreeBucketModel(WiFiLobbyMinigameBucketBucketModel *param0, WiFiLobbyMinigameBucketScene *param1, NNSFndAllocator *param2);
static void WiFiLobbyMinigameBucket_DrawBucketModel(WiFiLobbyMinigameBucketBucketModel *param0);
static void WiFiLobbyMinigameBucket_StartBucketFill(WiFiLobbyMinigameBucketBucketModel *param0);
static void WiFiLobbyMinigameBucket_SetBucketAnimSpeed(WiFiLobbyMinigameBucketBucketModel *param0, fx32 param1);
static void WiFiLobbyMinigameBucket_RayIntersect(const VecFx32 *param0, const VecFx32 *param1, const VecFx32 *param2, fx32 param3, VecFx32 *param4, fx32 *param5);
static void WiFiLobbyMinigameBucket_SetCameraTargetHeight(WiFiLobbyMinigameBucketScene *param0, fx32 param1);
static void WiFiLobbyMinigameBucket_SetCameraAngle(WiFiLobbyMinigameBucketScene *param0, u16 param1);
static void WiFiLobbyMinigameBucket_InitBgFade(WiFiLobbyMinigameBucketBgFade *param0, u8 param1);
static void WiFiLobbyMinigameBucket_UpdateBgFade(WiFiLobbyMinigameBucketBgFade *param0, WiFiLobbyMinigameBucketScene *param1);
static void WiFiLobbyMinigameBucket_AdvanceBgFade(WiFiLobbyMinigameBucketBgFade *param0);
static void WiFiLobbyMinigameBucket_SetBgRotation(WiFiLobbyMinigameBucketScene *param0, s16 param1, u16 param2);
static void WiFiLobbyMinigameBucket_InitScoreDisplay(WiFiLobbyMinigameBucketScoreDisplay *param0, WiFiLobbyMinigameBucketScene *param1, NARC *param2, u32 heapID);
static void WiFiLobbyMinigameBucket_FreeScoreDisplay(WiFiLobbyMinigameBucketScoreDisplay *param0, WiFiLobbyMinigameBucketScene *param1);
static void WiFiLobbyMinigameBucket_ShowScore(WiFiLobbyMinigameBucketScoreDisplay *param0, WiFiLobbyMinigameBucketScene *param1, u32 param2);
static void WiFiLobbyMinigameBucket_HideScore(WiFiLobbyMinigameBucketScoreDisplay *param0);
static void WiFiLobbyMinigameBucket_UpdateScore(WiFiLobbyMinigameBucketScoreDisplay *param0, WiFiLobbyMinigameBucketScene *param1, u32 param2);
static void WiFiLobbyMinigameBucket_UpdateScoreDisplay(WiFiLobbyMinigameBucketScoreDisplay *param0);
static void WiFiLobbyMinigameBucket_StartFinishEffect(WiFiLobbyMinigameBucketFinishEffect *param0);
static void WiFiLobbyMinigameBucket_UpdateFinishEffect(WiFiLobbyMinigameBucketFinishEffect *param0, WiFiLobbyMinigameBucketBucketModel *param1, WiFiLobbyMinigameBucketSwalotModel *param2);
static void WiFiLobbyMinigameBucket_ResetFinishEffect(WiFiLobbyMinigameBucketFinishEffect *param0);

static const u32 sStageScoreThresholds[3] = {
    0x0,
    0x294,
    0x2EE
};

static const u8 sSwalotAnimFrameRanges[5][2] = {
    { 0x0, 0x0 },
    { 0x1, 0xA },
    { 0xB, 0x14 },
    { 0x15, 0x1E },
    { 0x1F, 0x28 }
};

static const NNSG3dResName sSwalotAnimNodeNames[6][15] = {
    {
        "polySurface2",
        "polySurface3",
        "pTorus2",
        "null1",
    },
    {
        "polySurface7",
        "polySurface13",
        "pSphere2",
        "pSphere3",
        "pSphere6",
        "pSphere7",
    },
    { "polySurface13",
        "pSphere7" },
    {
        "null1",
        "pCylinder4",
        "pCylinder5",
        "pSphere2",
        "pSphere3",
        "pSphere6",
        "pSphere7",
        "pTorus1",
        "pTorus2",
        "polySurface13",
        "polySurface8",
        "polySurface2",
        "polySurface3",
        "polySurface7",
        "polySurface12",
    },
    {
        "polySurface7",
        "polySurface13",
        "pSphere2",
        "pSphere3",
        "pSphere6",
        "pSphere7",
        "null1",
    },
    {
        "polySurface7",
        "polySurface13",
        "pSphere2",
        "pSphere3",
        "pSphere6",
        "pSphere7",
    },
};

static const u8 sSwalotAnimModelForAnim[6] = {
    0x0,
    0x0,
    0x0,
    0x2,
    0x1,
    0x0,
};

static const u8 sSwalotAnimModelIndex[1] = {
    0x0,
};

static const VecFx32 sSwalotBasePosition = {
    (FX32_CONST(0)),
    FX32_CONST(-90),
    FX32_CONST(0),
};

static const VecFx32 sCameraTargetOffset = {
    0x0,
    FX32_CONST(2500),
    0x0,
};

static const u32 sScorePerHit[3] = {
    0x64,
    0xC8,
    0x12C,
};

static const u16 sPlayerRotationAngles[4][4] = {
    { 0x0, 0x0, 0x0, 0x0 },
    { 0x0, 0x7FFF, 0x0, 0x0 },
    { 0x0, 0x5555, 0xAAAA, 0x0 },
    { 0x0, 0x7FFF, 0x3FFF, 0xBFFF },
};

static const u16 sStageRotationAngles[4][4] = {
    { 0x0, 0x0, 0x0, 0x0 },
    { 0x7FFF, 0x0, 0x0, 0x0 },
    { 0x7FFF, 0xD554, 0x2AAA, 0x0 },
    { 0x7FFF, 0x0, 0xBFFF, 0x3FFF },
};

static const GeonetAngle sPlayerNamePositions[4][4][4] = {
    {
        { 0x0 },
        {
            { 0x0, 0x0 },
            { 0xC, 0x2 },
        },
        {
            { 0x0, 0x0 },
            { 0x17, 0x4 },
            { 0x1, 0x4 },
        },
        {
            { 0x0, 0x0 },
            { 0xC, 0x2 },
            { 0x17, 0x6 },
            { 0x1, 0x6 },
        },
    },
    {
        { 0x0 },
        {
            { 0xC, 0x2 },
            { 0x0, 0x0 },
        },
        {
            { 0x1, 0x4 },
            { 0x0, 0x0 },
            { 0x17, 0x4 },
        },
        {
            { 0xC, 0x2 },
            { 0x0, 0x0 },
            { 0x1, 0x6 },
            { 0x17, 0x6 },
        },
    },
    {
        { 0x0 },
        {
            { 0x0 },
        },
        {
            { 0x17, 0x4 },
            { 0x1, 0x4 },
            { 0x0, 0x0 },
        },
        {
            { 0x1, 0x6 },
            { 0x17, 0x6 },
            { 0x0, 0x0 },
            { 0xC, 0x2 },
        },
    },
    {
        { 0x0 },
        {
            { 0x0 },
        },
        {
            { 0x0, 0x0 },
        },
        {
            { 0x17, 0x6 },
            { 0x1, 0x6 },
            { 0xC, 0x2 },
            { 0x0, 0x0 },
        },
    },
};

static TPData sTouchPadBuffer[8];

static const s16 sSwalotMouthYPositions[12] = {
    0xB1,
    0xA7,
    0x93,
    0x89,
    0x7F,
    0x75,
    0x6B,
    0x61,
    0x57,
    0x4D,
    0x4D,
    0x4D
};

WiFiLobbyMinigameBucketGame *WiFiLobbyMinigameBucket_CreateGame(u32 heapID, u32 param1, u32 param2, u32 param3, WiFiLobbyMinigameBucketStage *param4)
{
    WiFiLobbyMinigameBucketGame *v0;
    u32 v1;

    v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMinigameBucketGame));
    memset(v0, 0, sizeof(WiFiLobbyMinigameBucketGame));

    v0->unk_04 = 1;
    v0->unk_08 = 0;
    v0->unk_0C = param1;
    v0->unk_10 = param2;
    v0->unk_14 = param3;
    v0->unk_8720 = param4;

    WiFiLobbyMinigameBucket_InitCamera(v0, &v0->unk_19CC);
    WiFiLobbyMinigameBucket_InitScene(v0, heapID);
    WiFiLobbyMinigameBucket_InitSwalot(&v0->unk_8730, &v0->unk_1AB4, heapID);
    WiFiLobbyMinigameBucket_InitScoreBoard(&v0->unk_8770);

    v1 = InitializeTouchPadWithExternalBuffer(sTouchPadBuffer, 8, 4);
    GF_ASSERT(v1 == 1);

    return v0;
}

void WiFiLobbyMinigameBucket_FreeGame(WiFiLobbyMinigameBucketGame *param0)
{
    u32 v0 = DisableTouchPad();
    GF_ASSERT(v0 == 1);

    WiFiLobbyMinigameBucket_FreeSwalot(&param0->unk_8730, &param0->unk_1AB4);
    WiFiLobbyMinigameBucket_FreeScene(param0);
    Heap_Free(param0);
}

BOOL WiFiLobbyMinigameBucket_UpdateIntro(WiFiLobbyMinigameBucketGame *param0, u32 param1)
{
    BOOL v0;
    BOOL v1 = 1;
    s32 v2;

    if (param0->unk_1AB4.unk_4E8.unk_00 >= 4) {
        if (param0->unk_8728.unk_01) {
            v2 = -120;
        } else {
            v2 = 120;
        }

        WiFiLobbyMinigameBucket_SetCameraYaw(&param0->unk_19CC, param0->unk_19CC.unk_02 + v2);
    }

    WiFiLobbyMinigameBucket_UpdateSwalotModel(&param0->unk_1AB4, &param0->unk_19CC);
    WiFiLobbyMinigameBucket_SetSwalotModelRotation(&param0->unk_1AB4.unk_524, &param0->unk_19CC);
    WiFiLobbyMinigameBucket_SetSwalotModelScale(&param0->unk_1AB4.unk_524, &param0->unk_19CC);

    switch (param0->unk_1AB4.unk_4E8.unk_00) {
    case 0:
        WiFiLobbyMinigameBucket_ShowSwalot(&param0->unk_8730);
        param0->unk_1AB4.unk_4E8.unk_00++;
        break;
    case 1:
        v0 = WiFiLobbyMinigameBucket_UpdateSwalot(&param0->unk_8730, param0);

        if (v0 == 1) {
            param0->unk_1AB4.unk_4E8.unk_00++;
            CommTiming_StartSync(2);
        }
        break;
    case 2:
        if (!CommTiming_IsSyncState(2)) {
            break;
        }

        param0->unk_1AB4.unk_4E8.unk_00++;
        param0->unk_1AB4.unk_4E8.unk_08 = 65;
        break;
    case 3:
        param0->unk_1AB4.unk_4E8.unk_08--;

        if (param0->unk_1AB4.unk_4E8.unk_08 == 50) {
            Sound_PlayEffect(SEQ_SE_DP_KI_GASYAN_sseq);
        }

        if (param0->unk_1AB4.unk_4E8.unk_08 == 20) {
            Sound_PlayEffect(SEQ_SE_DP_HAMARU_sseq);
        }

        WiFiLobbyMinigameBucket_UpdateSwalotAnim(&param0->unk_1AB4.unk_524, FX32_CONST(1.0));

        if (param0->unk_1AB4.unk_4E8.unk_08 == 0) {
            WiFiLobbyMinigameBucket_PlaySwalotIntroAnim(&param0->unk_1AB4.unk_4E8, &param0->unk_1AB4);
            param0->unk_1AB4.unk_4E8.unk_00 = 4;
        }
        break;
    case 4:
        if (param1 == 1) {
            param0->unk_1AB4.unk_4E8.unk_00 = 5;
        }
        break;
    case 5:
        WiFiLobbyMinigameBucket_ShowIntroWindow(&param0->unk_1AB4.unk_4E8, &param0->unk_1AB4);
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        param0->unk_1AB4.unk_4E8.unk_00 = 6;
        break;
    case 6:
        v0 = WiFiLobbyMinigameBucket_IsIntroAnimationRunning(&param0->unk_1AB4.unk_4E8, &param0->unk_1AB4);

        if (v0 == 0) {
            param0->unk_1AB4.unk_4E8.unk_00 = 7;
        }
        break;
    case 7:
        v0 = WiFiLobbyMinigameBucket_WaitIntroWindow(&param0->unk_1AB4.unk_4E8, &param0->unk_1AB4);

        if (v0 == 0) {
            param0->unk_1AB4.unk_4E8.unk_00 = 8;
        }
        break;
    case 8:
        WiFiLobbyMinigameBucket_HideIntroWindow(&param0->unk_1AB4.unk_4E8, &param0->unk_1AB4);
        WiFiLobbyMinigameBucket_SetCameraActive(&param0->unk_19CC, 1);
        v1 = 0;
        break;
    }

    WiFiLobbyMinigameBucket_UpdateSwalotModelAnim(&param0->unk_1AB4.unk_524, &param0->unk_19CC, param0->unk_00);
    WiFiLobbyMinigameBucket_RenderScene(param0, &param0->unk_1AB4);
    return v1;
}

BOOL WiFiLobbyMinigameBucket_UpdateOutro(WiFiLobbyMinigameBucketGame *param0, u32 param1)
{
    BOOL v0;
    BOOL v1 = 1;
    s32 v2;

    switch (param0->unk_1AB4.unk_504.unk_00) {
    case 0:

        WiFiLobbyMinigameBucket_ResetProjectiles(param0);
        WiFiLobbyMinigameBucket_ResetTouch(param0);

        BrightnessController_StartTransition(24, -14, 0, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, BRIGHTNESS_SUB_SCREEN);

        WiFiLobbyMinigameBucket_ShowSwalotAnim(&param0->unk_1AB4);
        WiFiLobbyMinigame_StartIntroAnimationPop(param0->unk_1AB4.unk_754);
        WiFiLobbyMinigameBucket_ResetFinishEffect(&param0->unk_8788);
        WiFiLobbyMinigameBucket_HideScore(&param0->unk_1AB4.unk_6B1C);

        param0->unk_1AB4.unk_504.unk_00++;
        break;
    case 1:
        v0 = 1;

        if (WiFiLobbyMinigameBucket_UpdateSwalotIntroAnim(&param0->unk_1AB4) == 0) {
            v0 = 0;
        }

        WiFiLobbyMinigameBucket_UpdateProjectiles(param0);
        WiFiLobbyMinigameBucket_FinishProjectiles(param0);

        if (WiFiLobbyMinigameBucket_HasActiveProjectiles(param0) == 1) {
            v0 = 0;
        }

        if (WiFiLobbyMinigameBucket_IsIntroAnimationDone(&param0->unk_1AB4) == 0) {
            v0 = 0;
        }

        if (BrightnessController_IsTransitionComplete(BRIGHTNESS_SUB_SCREEN) == FALSE) {
            v0 = 0;
        }

        if ((v0 == 1) && (param1 == 1)) {
            param0->unk_1AB4.unk_504.unk_04 = 0;
            param0->unk_1AB4.unk_504.unk_00++;
        }
        break;
    case 2:
        param0->unk_1AB4.unk_504.unk_04++;

        if (param0->unk_1AB4.unk_504.unk_04 >= 64) {
            param0->unk_1AB4.unk_504.unk_00++;
        }
        break;
    case 3:
        v1 = 0;
        break;
    }

    if (param0->unk_8728.unk_01) {
        v2 = -120;
    } else {
        v2 = 120;
    }

    WiFiLobbyMinigameBucket_SetCameraYaw(&param0->unk_19CC, param0->unk_19CC.unk_02 + v2);
    WiFiLobbyMinigameBucket_SetSwalotModelPosition(&param0->unk_1AB4.unk_524, &param0->unk_19CC);
    WiFiLobbyMinigameBucket_SetSwalotModelRotation(&param0->unk_1AB4.unk_524, &param0->unk_19CC);
    WiFiLobbyMinigameBucket_UpdateSwalotModelAnim(&param0->unk_1AB4.unk_524, &param0->unk_19CC, param0->unk_00);
    WiFiLobbyMinigameBucket_RenderScene(param0, &param0->unk_1AB4);
    WiFiLobbyMinigameBucket_UpdateScoreDisplay(&param0->unk_1AB4.unk_6B1C);

    return v1;
}

BOOL WiFiLobbyMinigameBucket_UpdateGame(WiFiLobbyMinigameBucketGame *param0)
{
    BOOL v0;

    if (param0->unk_00 < 3 - 1) {
        if (sStageScoreThresholds[param0->unk_00 + 1] <= param0->unk_08) {
            param0->unk_00++;

            if (param0->unk_00 == 1) {
                WiFiLobbyMinigameBucket_StartFinishEffect(&param0->unk_8788);
            }
        }
    }

    WriteAutoSamplingDataToBuffer(&param0->unk_8690, TOUCH_PAD_EXTERNAL_BUFFER_WRITE_METHOD_ONLY_TOUCHES_WITH_WRAPPING, 0);
    WiFiLobbyMinigameBucket_HandleTouchInput(param0);

    {
        v0 = WiFiLobbyMinigameBucket_UpdateStageTransition(&param0->unk_86D4);

        if (v0 == 0) {
            WiFiLobbyMinigameBucket_ApplyStageTransition(param0, &param0->unk_86D4);
        }
    }

    {
        u32 v1;

        v0 = WiFiLobbyMinigameBucket_IsScoreBoardFull(&param0->unk_8770, param0->unk_10);

        if (v0 == 1) {
            v1 = WiFiLobbyMinigameBucket_GetScoreBoardLeader(&param0->unk_8770);

            if (v1 != 0xffff) {
                WiFiLobbyMinigameBucket_SetSwalotAnimIndex(&param0->unk_1AB4.unk_524, v1);
            }

            WiFiLobbyMinigameBucket_ResetScoreBoard(&param0->unk_8770);
        }
    }

    WiFiLobbyMinigameBucket_UpdateProjectiles(param0);
    WiFiLobbyMinigameBucket_UpdateCamera(param0, &param0->unk_19CC);
    WiFiLobbyMinigameBucket_DrawScene(param0, &param0->unk_1AB4);
    WiFiLobbyMinigameBucket_UpdateAllProjectileSprites(param0);
    WiFiLobbyMinigameBucket_UpdateFinishEffect(&param0->unk_8788, &param0->unk_1AB4.unk_204, &param0->unk_1AB4.unk_524);

    if (param0->unk_04 == 1) {
        param0->unk_08++;
    }

    if (param0->unk_08 >= param0->unk_0C) {
        param0->unk_08 = param0->unk_0C;
        return 1;
    }

    return 0;
}

void WiFiLobbyMinigameBucket_VBlank(WiFiLobbyMinigameBucketGame *param0)
{
    Bg_RunScheduledUpdates(param0->unk_1AB4.unk_00);
    VramTransfer_Process();
    RenderOam_Transfer();
}

s32 WiFiLobbyMinigameBucket_GetElapsedTime(const WiFiLobbyMinigameBucketGame *param0)
{
    return param0->unk_08;
}

void WiFiLobbyMinigameBucket_HandleThrow(WiFiLobbyMinigameBucketGame *param0, const WiFiLobbyMinigameBucketThrowData *param1)
{
    WiFiLobbyMinigameBucketProjectile v0;

    if (param0->unk_14 != param1->unk_00) {
        WiFiLobbyMinigameBucket_ThrowDataToProjectile(param1, &v0);
        WiFiLobbyMinigameBucket_SpawnProjectile(param0, &v0, 2);

        if (param1->unk_02) {
            WiFiLobbyMinigameBucket_ShowThrowSprite(&param0->unk_1AB4.unk_3E8, param1->unk_00, param1->unk_12, param0->unk_00);
        }
    }
}

BOOL WiFiLobbyMinigameBucket_PopQueuedThrow(WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketThrowData *param1)
{
    int v0;

    for (v0 = 0; v0 < 96; v0++) {
        if (param0->unk_4C[v0].unk_00 == 4) {
            WiFiLobbyMinigameBucket_ProjectileToThrowData(&param0->unk_4C[v0].unk_04, param1);
            WiFiLobbyMinigameBucket_ClearProjectile(&param0->unk_4C[v0]);
            return 1;
        }
    }

    return 0;
}

void WiFiLobbyMinigameBucket_SetFinalScores(WiFiLobbyMinigameBucketGame *param0, const WiFiLobbyMinigameBucketFinalScores *param1)
{
    param0->unk_8680 = *param1;
}

u32 WiFiLobbyMinigameBucket_GetScore(const WiFiLobbyMinigameBucketGame *param0)
{
    return param0->unk_18;
}

void WiFiLobbyMinigameBucket_SetStage(WiFiLobbyMinigameBucketGame *param0, u32 param1)
{
    param0->unk_8726 = param0->unk_8724;
    param0->unk_8724 = param1;

    WiFiLobbyMinigameBucket_StartStageTransition(&param0->unk_86D4, param0->unk_8720, &param0->unk_8728, param0->unk_8726, param0->unk_8724);
}

void WiFiLobbyMinigameBucket_AddScore(WiFiLobbyMinigameBucketGame *param0, u32 param1, u32 param2)
{
    WiFiLobbyMinigameBucket_AddScoreBoardEntry(&param0->unk_8770, param1, param2);
}

void WiFiLobbyMinigameBucket_SetMode(WiFiLobbyMinigameBucketGame *param0, const WiFiLobbyMinigameBucketMode *param1)
{
    param0->unk_8728 = *param1;
    param0->unk_872C = 1;

    WiFiLobbyMinigameBucket_InitStageTransition(&param0->unk_86D4, param0->unk_8720, &param0->unk_8728);
    WiFiLobbyMinigameBucket_ApplyStageTransition(param0, &param0->unk_86D4);
}

static void WiFiLobbyMinigameBucket_InitMotion(WiFiLobbyMinigameBucketMotion *param0, fx32 param1, fx32 param2, fx32 param3, int param4)
{
    fx32 v0;
    fx32 v1;
    fx32 v2;
    fx32 v3;

    v2 = param2 - param1;
    v0 = (param4 * param4) << FX32_SHIFT;
    v1 = FX_Mul(param3, param4 * FX32_ONE);
    v1 = v2 - v1;
    v1 = FX_Mul(v1, 2 * FX32_ONE);
    v3 = FX_Div(v1, v0);

    param0->unk_00 = param1;
    param0->unk_04 = param1;
    param0->unk_08 = param3;
    param0->unk_0C = v3;
    param0->unk_10 = 0;
    param0->unk_14 = param4;
}

static BOOL WiFiLobbyMinigameBucket_UpdateMotion(WiFiLobbyMinigameBucketMotion *param0)
{
    fx32 v0;
    fx32 v1;
    fx32 v2;
    fx32 v3;

    v3 = FX_Mul(param0->unk_08, param0->unk_10 << FX32_SHIFT);
    v1 = (param0->unk_10 * param0->unk_10) << FX32_SHIFT;
    v2 = FX_Mul(param0->unk_0C, v1);
    v2 = FX_Div(v2, 2 * FX32_ONE);
    v0 = v3 + v2;

    param0->unk_00 = param0->unk_04 + v0;

    if ((param0->unk_10 + 1) <= param0->unk_14) {
        param0->unk_10++;
        return 0;
    }

    param0->unk_10 = param0->unk_14;
    return 1;
}

static void WiFiLobbyMinigameBucket_GetPlayerNamePosition(u32 param0, u32 param1, u32 param2, s32 *param3, s32 *param4)
{
    static const GeonetAngle v0[4][4][4] = {
        {
            { 0 },
            {
                { 128, 144 },
                { 128, 48 },
            },
            {
                { 128, 144 },
                { 208, 64 },
                { 48, 64 },
            },
            {
                { 128, 144 },
                { 128, 48 },
                { 208, 96 },
                { 48, 96 },
            },
        },
        {
            { 0 },
            {
                { 128, 48 },
                { 128, 144 },
            },
            {
                { 48, 64 },
                { 128, 144 },
                { 208, 64 },
            },
            {
                { 128, 48 },
                { 128, 144 },
                { 48, 96 },
                { 208, 96 },
            },
        },
        {
            { 0 },
            {
                { 0 },
            },
            {
                { 208, 64 },
                { 48, 64 },
                { 128, 144 },
            },
            {
                { 48, 96 },
                { 208, 96 },
                { 128, 144 },
                { 128, 48 },
            },
        },
        {
            { 0 },
            {
                { 0 },
            },
            {
                { 0, 0 },
            },
            {
                { 208, 96 },
                { 48, 96 },
                { 128, 48 },
                { 128, 144 },
            },
        },
    };

    *param3 = v0[param1][param0 - 1][param2].x;
    *param4 = v0[param1][param0 - 1][param2].y;
}

static void WiFiLobbyMinigameBucket_SpawnThrowFromSwalot(WiFiLobbyMinigameBucketGame *param0, u16 param1, u16 param2, u16 param3, u16 param4, u32 param5)
{
    WiFiLobbyMinigameBucketProjectile v0;
    NNSG2dSVec2 v1;
    BOOL v2;
    s32 v3;
    BOOL v4 = 0;
    fx32 v5;

    v0.unk_00 = param0->unk_14;
    v0.unk_02 = 0;
    v1.x = (param1 - param3) / 2;
    v1.y = (param2 - param4) / 2;
    v0.unk_04.x = v1.x << FX32_SHIFT;
    v0.unk_04.z = v1.y << FX32_SHIFT;
    v0.unk_04.y = 0;
    v5 = VEC_Mag(&v0.unk_04);

    if (v5 > (0x8000 + 0x16200)) {
        VEC_Normalize(&v0.unk_04, &v0.unk_04);
        v0.unk_04.x = FX_Mul(v0.unk_04.x, 0x8000 + 0x16200);
        v0.unk_04.z = FX_Mul(v0.unk_04.z, 0x8000 + 0x16200);
    }

    v0.unk_04.y = 0x26000;
    v0.unk_10 = VEC_Mag(&v0.unk_04);
    v0.unk_10 = FX_Mul(v0.unk_10, FX32_CONST(0.6));

    VEC_Normalize(&v0.unk_04, &v0.unk_04);
    WiFiLobbyMinigameBucket_ScreenToWorld(param3, param4, &v0.unk_14);

    v0.unk_14.y = (FX32_CONST(0));

    WiFiLobbyMinigameBucket_RotateWorldToPlayer(&v0.unk_14, &v0.unk_14, v0.unk_00, param0->unk_10);
    WiFiLobbyMinigameBucket_RotateWorldToPlayer(&v0.unk_04, &v0.unk_04, v0.unk_00, param0->unk_10);

    v0.unk_24 = 0;

    WiFiLobbyMinigameBucket_SpawnProjectile(param0, &v0, param5);
}

static u32 WiFiLobbyMinigameBucket_GetScoreForHit(WiFiLobbyMinigameBucketGame *param0)
{
    u8 v0;
    u32 v1;

    if (param0->unk_1C >= 3) {
        v0 = 3 - 1;
    } else {
        v0 = param0->unk_1C;
    }

    v1 = sScorePerHit[v0];

    if (param0->unk_00 == 2) {
        v1 *= 3;
    }

    return v1;
}

static void WiFiLobbyMinigameBucket_InitThrowSprites(WiFiLobbyMinigameBucketThrowSprites *param0, WiFiLobbyMinigameBucketScene *param1, u32 param2, u32 param3, u32 param4)
{
    AffineSpriteListTemplate v0;
    int v1, v2;
    u32 v3;

    v0.list = param1->unk_1C;
    v0.resourceData = &param1->unk_1BC;
    v0.affineScale.x = FX32_ONE;
    v0.affineScale.y = FX32_ONE;
    v0.affineScale.z = FX32_ONE;
    v0.affineZRotation = 0;
    v0.priority = 0;
    v0.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v0.heapID = param4;

    v3 = param3;

    for (v1 = 0; v1 < 4; v1++) {
        WiFiLobbyMinigameBucket_InitThrowSprite(&param0->unk_00[v1], &v0, param1, param2, v1, v3, param4);
    }
}

static void WiFiLobbyMinigameBucket_FreeThrowSprites(WiFiLobbyMinigameBucketThrowSprites *param0, WiFiLobbyMinigameBucketScene *param1)
{
    int v0, v1;

    for (v0 = 0; v0 < 4; v0++) {
        WiFiLobbyMinigameBucket_FreeThrowSprite(&param0->unk_00[v0]);
    }
}

static void WiFiLobbyMinigameBucket_ShowThrowSprite(WiFiLobbyMinigameBucketThrowSprites *param0, u32 param1, u32 param2, int param3)
{
    WiFiLobbyMinigameBucket_ShowThrowSpriteAnim(&param0->unk_00[param1], param1, param2, param3);
}

static void WiFiLobbyMinigameBucket_UpdateThrowSprites(WiFiLobbyMinigameBucketThrowSprites *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        WiFiLobbyMinigameBucket_UpdateThrowSprite(&param0->unk_00[v0]);
    }
}

static void WiFiLobbyMinigameBucket_InitThrowSprite(WiFiLobbyMinigameBucketThrowSprite *param0, AffineSpriteListTemplate *param1, WiFiLobbyMinigameBucketScene *param2, u32 param3, u32 param4, u32 param5, u32 param6)
{
    int v0;
    s32 v1, v2;

    for (v0 = 0; v0 < 3; v0++) {
        WiFiLobbyMinigameBucket_GetPlayerNamePosition(param3, param5, param4, &v1, &v2);
        param1->position.x = v1 << FX32_SHIFT;
        param1->position.y = v2 << FX32_SHIFT;
        param0->unk_18[v0] = param1->position;
        param0->unk_00[v0] = SpriteList_AddAffine(param1);

        Sprite_SetAnim(param0->unk_00[v0], 2);
        Sprite_SetDrawFlag(param0->unk_00[v0], FALSE);
        Sprite_SetAnimateFlag(param0->unk_00[v0], 1);
        Sprite_SetAnimSpeed(param0->unk_00[v0], FX32_CONST(1.5));

        param0->unk_0C[v0] = 0;
    }

    if (param5 == param4) {
        param0->unk_3C = 1;
    } else {
        param0->unk_3C = 0;
    }
}

static void WiFiLobbyMinigameBucket_FreeThrowSprite(WiFiLobbyMinigameBucketThrowSprite *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Sprite_Delete(param0->unk_00[v0]);
    }
}

static void WiFiLobbyMinigameBucket_ShowThrowSpriteAnim(WiFiLobbyMinigameBucketThrowSprite *param0, u32 param1, u32 param2, int param3)
{
    int v0;
    int v1;
    BOOL v2;
    u32 v3;
    u32 v4;
    u32 v5;
    u32 v6;

    v2 = 0;
    v4 = 0;
    v1 = -1;

    for (v0 = 0; v0 < 3; v0++) {
        if (Sprite_GetDrawFlag(param0->unk_00[v0]) == 0) {
            v1 = v0;
            v2 = 1;
        } else {
            v3 = Sprite_GetPriority(param0->unk_00[v0]);
            v3++;
            Sprite_SetPriority(param0->unk_00[v0], v3);

            if ((v2 == 0) && (v4 <= v3)) {
                v4 = v3;
                v1 = v0;
            }
        }
    }

    GF_ASSERT(v1 >= 0);

    if (param2 >= 3) {
        param2 = 3 - 1;
    }

    if (param3 != 2) {
        if (param0->unk_3C == 1) {
            v5 = param2 + 2;
        } else {
            v5 = param2 + 8;
        }

        v6 = 3 + param1;
    } else {
        if (param0->unk_3C == 1) {
            v5 = param2 + 5;
        } else {
            v5 = param2 + 11;
        }

        v6 = 7;
    }

    Sprite_SetAnim(param0->unk_00[v1], v5);
    param0->unk_0C[v1] = 0;
    Sprite_SetDrawFlag(param0->unk_00[v1], TRUE);
    WiFiLobbyMinigameBucket_SetThrowSpritePosition(param0, v1);
    Sprite_SetPriority(param0->unk_00[v1], 0);
    Sprite_SetExplicitPalette(param0->unk_00[v1], v6);
}

static void WiFiLobbyMinigameBucket_UpdateThrowSprite(WiFiLobbyMinigameBucketThrowSprite *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        if (Sprite_GetDrawFlag(param0->unk_00[v0]) == 1) {
            param0->unk_0C[v0]++;

            if (param0->unk_0C[v0] > 16) {
                WiFiLobbyMinigameBucket_HideThrowSprite(param0, v0);
            } else {
                WiFiLobbyMinigameBucket_SetThrowSpritePosition(param0, v0);
            }
        }
    }
}

static void WiFiLobbyMinigameBucket_SetThrowSpritePosition(WiFiLobbyMinigameBucketThrowSprite *param0, u32 param1)
{
    fx32 v0;
    VecFx32 v1;

    v0 = FX_Div(FX_Mul(FX32_ONE * param0->unk_0C[param1], -FX32_CONST(16)), FX32_CONST(16));
    v1 = param0->unk_18[param1];
    v1.y += v0;

    Sprite_SetPosition(param0->unk_00[param1], &v1);
}

static void WiFiLobbyMinigameBucket_HideThrowSprite(WiFiLobbyMinigameBucketThrowSprite *param0, u32 param1)
{
    Sprite_SetDrawFlag(param0->unk_00[param1], FALSE);
}

static void WiFiLobbyMinigameBucket_InitIntroWindow(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1, const WiFiLobbyMinigameBucketStage *param2, u32 param3, u32 param4, NARC *param5, u32 heapID)
{
    String *v0;
    AffineSpriteListTemplate v1;

    memset(param0, 0, sizeof(WiFiLobbyMinigameBucketIntroWindow));

    Window_Add(param1->unk_00, &param0->unk_0C, 1, 2, 19, 28, 4, 5, 1 + 9);
    Window_FillRectWithColor(&param0->unk_0C, 15, 0, 0, 28 * 8, 4 * 8);

    v0 = String_Init(128, heapID);

    MessageLoader_GetString(param1->unk_08, 0, v0);
    Text_AddPrinterWithParamsAndColor(&param0->unk_0C, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
    String_Free(v0);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param5, 18, param1->unk_00, 2, 0, 0, 0, heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param5, 20 + (param3 - 2), param1->unk_00, 2, 0, 0, 0, heapID);
    Graphics_LoadPaletteFromOpenNARC(param5, 19, 0, 0 * 32, (3 + 1) * 32, heapID);

    {
        int v2;
        s32 v3, v4;
        Window v5;
        u32 v6;
        String *v7;
        TextColor v8;
        u32 v9;
        u32 v10;

        Window_Init(&v5);
        Window_Add(param1->unk_00, &v5, 2, 0, 0, 8, 2, 5, 256);

        v6 = 256;
        v7 = String_Init(128, heapID);

        for (v2 = 0; v2 < param3; v2++) {
            if (v2 != param4) {
                v3 = sPlayerNamePositions[param4][param3 - 1][v2].x;
                v4 = sPlayerNamePositions[param4][param3 - 1][v2].y;

                Bg_ChangeTilemapRectPalette(param1->unk_00, 2, v3 - 1, v4 - 1, 10, 4, 0 + v2);
                Window_FillTilemap(&v5, 15);

                if (param2->unk_18[v2] == 1) {
                    v8 = TEXT_COLOR(5, 6, 15);
                } else {
                    v8 = TEXT_COLOR(1, 2, 15);
                }

                TrainerInfo_NameString(param2->unk_08[v2], v7);
                Window_SetXPos(&v5, v3);
                Window_SetYPos(&v5, v4);

                v5.baseTile = v6;
                v9 = Font_CalcStringWidth(FONT_SYSTEM, v7, 0);
                v10 = ((8 * 8) - v9) / 2;
                Text_AddPrinterWithParamsAndColor(&v5, FONT_SYSTEM, v7, v10, 0, TEXT_SPEED_INSTANT, v8, NULL);
                v6 += (8 * 2);
            }
        }

        String_Free(v7);
        Window_Remove(&v5);
    }

    param0->unk_04 = 0;

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
}

static void WiFiLobbyMinigameBucket_FreeIntroWindow(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1)
{
    Window_Remove(&param0->unk_0C);
}

static void WiFiLobbyMinigameBucket_ShowIntroWindow(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1)
{
    Window_DrawStandardFrame(&param0->unk_0C, 0, 1, 4);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
    WiFiLobbyMinigame_StartIntroAnimationRoll(param1->unk_754);
}

static BOOL WiFiLobbyMinigameBucket_IsIntroAnimationRunning(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1)
{
    BOOL v0 = WiFiLobbyMinigame_IntroAnimationIsDone(param1->unk_754);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static void WiFiLobbyMinigameBucket_HideIntroWindow(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1)
{
    Window_EraseStandardFrame(&param0->unk_0C, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->unk_0C);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
}

static void WiFiLobbyMinigameBucket_PlaySwalotIntroAnim(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1)
{
    WiFiLobbyMinigameBucket_SetSwalotAnim(&param1->unk_524, 1);
    Easy3DAnim_SetFrame(&param1->unk_524.unk_198[1], FX32_CONST(180));
    WiFiLobbyMinigameBucket_SetSwalotIdleAnim(&param1->unk_524, 1);
}

static BOOL WiFiLobbyMinigameBucket_WaitIntroWindow(WiFiLobbyMinigameBucketIntroWindow *param0, WiFiLobbyMinigameBucketScene *param1)
{
    param0->unk_04++;

    if (param0->unk_04 >= 8) {
        return 0;
    }

    return 1;
}

static void WiFiLobbyMinigameBucket_UpdateSwalotModel(WiFiLobbyMinigameBucketScene *param0, const WiFiLobbyMinigameBucketCamera *param1)
{
    WiFiLobbyMinigameBucket_SetSwalotModelPosition(&param0->unk_524, param1);
}

static void WiFiLobbyMinigameBucket_ResetIntroState(WiFiLobbyMinigameBucketScene *param0, u32 param1, u32 param2, u32 param3)
{
    param0->unk_504.unk_00 = 0;
    param0->unk_504.unk_04 = 0;
}

static void WiFiLobbyMinigameBucket_Noop(WiFiLobbyMinigameBucketScene *param0, u32 param1)
{
    return;
}

static void WiFiLobbyMinigameBucket_ShowSwalotAnim(WiFiLobbyMinigameBucketScene *param0)
{
    WiFiLobbyMinigameBucket_SetSwalotAnim(&param0->unk_524, 5);
}

static BOOL WiFiLobbyMinigameBucket_UpdateSwalotIntroAnim(WiFiLobbyMinigameBucketScene *param0)
{
    BOOL v0;

    param0->unk_504.unk_04++;

    if (param0->unk_504.unk_04 >= 60) {
        v0 = Easy3DAnim_Update(&param0->unk_524.unk_198[5], FX32_CONST(2));

        if (v0 == 1) {
            return 1;
        }
    }

    return 0;
}

static BOOL WiFiLobbyMinigameBucket_IsIntroAnimationDone(WiFiLobbyMinigameBucketScene *param0)
{
    BOOL v0 = WiFiLobbyMinigame_IntroAnimationIsDone(param0->unk_754);

    if (v0 == 1) {
        return 1;
    }

    return 0;
}

static void WiFiLobbyMinigameBucket_InitCamera(const WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketCamera *param1)
{
    param1->unk_06 = 0;

    WiFiLobbyMinigameBucket_SetCameraYaw(param1, (180 * 0xffff) / 360);
    WiFiLobbyMinigameBucket_SetCameraPitch(param1, (20 * 0xffff) / 360);

    param1->unk_00 = 0;
    param1->unk_01 = 1;
    param1->unk_94 = (FX32_CONST(200));
    param1->unk_98 = (FX32_CONST(0.03));
    param1->unk_08 = ((FX32_CONST(50)) + (FX32_CONST(30)));
    param1->unk_9C = sSwalotBasePosition;

    WiFiLobbyMinigameBucket_SetCameraScale(param1, 2500);

    param1->unk_D8 = sSwalotBasePosition;
    param1->unk_E4 = param1->unk_C0;
}

static void WiFiLobbyMinigameBucket_UpdateCamera(const WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketCamera *param1)
{
    static u16 (*const v0[3])(const WiFiLobbyMinigameBucketCamera *, s32, s32) = {
        WiFiLobbyMinigameBucket_GetCameraAngleStage0,
        WiFiLobbyMinigameBucket_GetCameraAngleStage1,
        WiFiLobbyMinigameBucket_GetCameraAngleStage2,
    };

    u16 v1;

    switch (param0->unk_00) {
    case 1:
        param1->unk_01 = 0;
        break;

    default:
        param1->unk_01 = 1;
        break;
    }

    v1 = v0[param0->unk_00](param1, param0->unk_08, param0->unk_0C);
    WiFiLobbyMinigameBucket_SetCameraPitch(param1, v1);
    param1->unk_08 = WiFiLobbyMinigameBucket_GetCameraHeight(param1, param1->unk_04);
    param1->unk_E4 = WiFiLobbyMinigameBucket_GetCameraDepth(param1, param1->unk_04);
    WiFiLobbyMinigameBucket_SetCameraYaw(param1, param1->unk_02 + param1->unk_06);
}

static void WiFiLobbyMinigameBucket_SetCameraActive(WiFiLobbyMinigameBucketCamera *param0, BOOL param1)
{
    param0->unk_00 = param1;
}

static void WiFiLobbyMinigameBucket_SetCameraPitch(WiFiLobbyMinigameBucketCamera *param0, u16 param1)
{
    param0->unk_04 = param1;

    MTX_Identity33(&param0->unk_0C);
    MTX_RotX33(&param0->unk_0C, FX_SinIdx(param1), FX_CosIdx(param1));
}

static void WiFiLobbyMinigameBucket_SetCameraYaw(WiFiLobbyMinigameBucketCamera *param0, u16 param1)
{
    VecFx32 v0;

    param0->unk_02 = param1;

    MTX_Identity33(&param0->unk_54);
    MTX_Identity33(&param0->unk_30);
    MTX_RotY33(&param0->unk_30, FX_SinIdx(param1), FX_CosIdx(param1));
    MTX_Concat33(&param0->unk_0C, &param0->unk_30, &param0->unk_54);
    MTX_MultVec33(&sCameraTargetOffset, &param0->unk_54, &param0->unk_78);

    v0.x = 0;
    v0.y = 0;
    v0.z = -param0->unk_08;

    MTX_MultVec33(&v0, &param0->unk_54, &param0->unk_84);

    v0.x = param0->unk_B8 + param0->unk_9C.x;
    v0.y = param0->unk_BC;
    v0.z = param0->unk_9C.z + ((FX32_CONST(50)) + (FX32_CONST(30)));

    MTX_MultVec33(&v0, &param0->unk_30, &v0);
    VEC_Add(&v0, &param0->unk_84, &param0->unk_84);

    param0->unk_90 = FX_Mul(param0->unk_78.x, param0->unk_84.x) + FX_Mul(param0->unk_78.y, param0->unk_84.y) + FX_Mul(param0->unk_78.z, param0->unk_84.z);

    MTX_MultVec33(&param0->unk_9C, &param0->unk_30, &param0->unk_D8);
}

static u32 WiFiLobbyMinigameBucket_CheckProjectileCollision(const WiFiLobbyMinigameBucketCamera *param0, const VecFx32 *param1, const VecFx32 *param2, VecFx32 *param3)
{
    fx32 v0;
    VecFx32 v1;
    fx32 v2;
    fx32 v3;
    VecFx32 v4;
    VecFx32 v5;
    u32 v6 = 0;

    if (param0->unk_00 == 0) {
        return 0;
    }

    WiFiLobbyMinigameBucket_RayIntersect(param1, param2, &param0->unk_78, param0->unk_90, &v1, &v0);
    VEC_Subtract(&param0->unk_84, param1, &v4);

    v2 = VEC_Mag(&v4);

    if ((v0 >= 0) && (v0 <= FX32_ONE)) {
        if (v2 <= param0->unk_08) {
            if (param0->unk_01 == 1) {
                v6 = 1;
            } else {
                v6 = 2;
            }
        } else {
            return 2;
        }
    }

    if ((v0 > 0) && (v2 < param0->unk_94)) {
        v3 = FX_Mul(param0->unk_94 - v2, param0->unk_98);
        VEC_Normalize(&v4, &v5);

        param3->x = FX_Mul(v5.x, v3);
        param3->y = FX_Mul(v5.y, v3);
        param3->z = FX_Mul(v5.z, v3);

        if ((v2 - v3) <= param0->unk_08) {
            if (param0->unk_01 == 1) {
                v6 = 1;
            } else {
                v6 = 2;
            }
        } else {
            v6 = 3;
        }
    }

    return v6;
}

static BOOL WiFiLobbyMinigameBucket_IsInsideBucket(const WiFiLobbyMinigameBucketCamera *param0, const VecFx32 *param1)
{
    VecFx32 v0;
    VecFx32 v1, v2;
    fx32 v3;
    fx32 v4;
    s32 v5;

    if (param0->unk_00 == 0) {
        return 0;
    }

    if ((param0->unk_D8.y < param1->y) && ((param0->unk_D8.y + param0->unk_E4) > param1->y)) {
        v1.x = param0->unk_D8.x;
        v1.z = param0->unk_D8.z;
        v1.y = 0;
        v2.x = param1->x;
        v2.z = param1->z;
        v2.y = 0;

        VEC_Subtract(&v1, &v2, &v0);

        v3 = VEC_Mag(&v0);
        v5 = param1->y - param0->unk_D8.y;
        v5 = v5 >> FX32_SHIFT;
        v4 = (v5 * param0->unk_D0) / (param0->unk_E4 >> FX32_SHIFT);
        v4 = param0->unk_CC - v4;

        if (v3 < v4) {
            return 1;
        }
    }

    return 0;
}

static fx32 WiFiLobbyMinigameBucket_GetCameraHeight(const WiFiLobbyMinigameBucketCamera *param0, u16 param1)
{
    s32 v0;
    fx32 v1;

    v0 = (param1 * 360) / 0xffff;
    v0 = 90 - v0;
    v1 = (v0 * param0->unk_AC) / 90;
    v1 += param0->unk_B0;

    return v1;
}

static fx32 WiFiLobbyMinigameBucket_GetCameraDepth(const WiFiLobbyMinigameBucketCamera *param0, u16 param1)
{
    s32 v0;
    fx32 v1;

    v0 = (param1 * 360) / 0xffff;
    v1 = (v0 * param0->unk_C4) / 90;
    v1 += param0->unk_C0;

    return v1;
}

static void WiFiLobbyMinigameBucket_SetCameraScale(WiFiLobbyMinigameBucketCamera *param0, fx32 param1)
{
    param0->unk_A8 = param1;
    param0->unk_AC = FX_Mul(FX32_CONST(30), param1);
    param0->unk_B0 = FX_Mul(FX32_CONST(50), param1);
    param0->unk_B4 = FX_Mul((FX32_CONST(50)) + (FX32_CONST(30)), param1);
    param0->unk_B8 = FX_Mul(0, param1);
    param0->unk_BC = FX_Mul(FX32_CONST(55), param1);
    param0->unk_C0 = FX_Mul(FX32_CONST(150), param1);
    param0->unk_C4 = FX_Mul(FX32_CONST(60), param1);
    param0->unk_C8 = FX_Mul(FX32_CONST(80), param1);
    param0->unk_CC = FX_Mul(FX32_CONST(120), param1);
    param0->unk_D0 = param0->unk_CC - param0->unk_C8;
    param0->unk_D4 = FX_Mul(FX32_CONST(1.50f), param1);
}

static void WiFiLobbyMinigameBucket_SetCameraRoll(WiFiLobbyMinigameBucketCamera *param0, u16 param1)
{
    param0->unk_06 = param1;
}

static void WiFiLobbyMinigameBucket_SetCameraDistance(WiFiLobbyMinigameBucketCamera *param0, fx32 param1)
{
    param0->unk_9C.z = param1;
}

static u16 WiFiLobbyMinigameBucket_GetCameraAngleStage0(const WiFiLobbyMinigameBucketCamera *param0, s32 param1, s32 param2)
{
    return (20 * 0xffff) / 360;
}

static u16 WiFiLobbyMinigameBucket_GetCameraAngleStage1(const WiFiLobbyMinigameBucketCamera *param0, s32 param1, s32 param2)
{
    return (90 * 0xffff) / 360;
}

static u16 WiFiLobbyMinigameBucket_GetCameraAngleStage2(const WiFiLobbyMinigameBucketCamera *param0, s32 param1, s32 param2)
{
    s32 v0;
    s32 v1;

    v0 = (param1 - sStageScoreThresholds[2]) % 50;
    v1 = (v0 * ((((90 * 0xffff) / 360) - ((20 * 0xffff) / 360)) * 2)) / 50;

    if (v1 > (((90 * 0xffff) / 360) - ((20 * 0xffff) / 360))) {
        v1 = (((90 * 0xffff) / 360) - ((20 * 0xffff) / 360)) - (v1 % (((90 * 0xffff) / 360) - ((20 * 0xffff) / 360)));
    }

    return ((20 * 0xffff) / 360) + v1;
}

static void WiFiLobbyMinigameBucket_ProjectileToThrowData(const WiFiLobbyMinigameBucketProjectile *param0, WiFiLobbyMinigameBucketThrowData *param1)
{
    param1->unk_00 = param0->unk_00;
    param1->unk_02 = param0->unk_02;
    param1->unk_04.x = param0->unk_04.x;
    param1->unk_04.y = param0->unk_04.y;
    param1->unk_04.z = param0->unk_04.z;
    param1->unk_10 = FX_Mul(param0->unk_10, FX32_CONST(0.16));
    param1->unk_0A.x = param0->unk_14.x >> FX32_SHIFT;
    param1->unk_0A.y = param0->unk_14.y >> FX32_SHIFT;
    param1->unk_0A.z = param0->unk_14.z >> FX32_SHIFT;
    param1->unk_12 = param0->unk_20;
    param1->unk_13 = param0->unk_24;
}

static void WiFiLobbyMinigameBucket_ThrowDataToProjectile(const WiFiLobbyMinigameBucketThrowData *param0, WiFiLobbyMinigameBucketProjectile *param1)
{
    param1->unk_00 = param0->unk_00;
    param1->unk_02 = param0->unk_02;
    param1->unk_04.x = param0->unk_04.x;
    param1->unk_04.y = param0->unk_04.y;
    param1->unk_04.z = param0->unk_04.z;
    param1->unk_10 = FX_Div(param0->unk_10, FX32_CONST(0.16));
    param1->unk_14.x = param0->unk_0A.x << FX32_SHIFT;
    param1->unk_14.y = param0->unk_0A.y << FX32_SHIFT;
    param1->unk_14.z = param0->unk_0A.z << FX32_SHIFT;
    param1->unk_24 = param0->unk_13;
}

static void WiFiLobbyMinigameBucket_SpawnProjectile(WiFiLobbyMinigameBucketGame *param0, const WiFiLobbyMinigameBucketProjectile *param1, u32 param2)
{
    int v0;

    for (v0 = 0; v0 < 96; v0++) {
        if (param0->unk_4C[v0].unk_00 == 0) {
            param0->unk_4C[v0].unk_04 = *param1;
            param0->unk_4C[v0].unk_00 = param2;
            param0->unk_4C[v0].unk_2C = param1->unk_14;
            param0->unk_4C[v0].unk_02 = 0;
            param0->unk_4C[v0].unk_3C = 0;

            WiFiLobbyMinigameBucket_ShowBerry(&param0->unk_1AB4, &param0->unk_4C[v0], param0->unk_10, param0->unk_14);

            return;
        }
    }

    if (param2 == 1) {
        for (v0 = 0; v0 < 96; v0++) {
            if ((param0->unk_4C[v0].unk_00 == 2) || (param0->unk_4C[v0].unk_00 == 5)) {
                WiFiLobbyMinigameBucket_HideBerry(&param0->unk_1AB4, &param0->unk_4C[v0]);
                WiFiLobbyMinigameBucket_ClearProjectile(&param0->unk_4C[v0]);

                param0->unk_4C[v0].unk_04 = *param1;
                param0->unk_4C[v0].unk_00 = param2;
                param0->unk_4C[v0].unk_2C = param1->unk_14;
                param0->unk_4C[v0].unk_02 = 0;
                param0->unk_4C[v0].unk_3C = 0;

                WiFiLobbyMinigameBucket_ShowBerry(&param0->unk_1AB4, &param0->unk_4C[v0], param0->unk_10, param0->unk_14);

                return;
            }
        }

        GF_ASSERT(FALSE);
    }
}

static void WiFiLobbyMinigameBucket_SetProjectileState(WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketProjectileState *param1, BOOL param2, u32 param3)
{
    param1->unk_01 = 1;
    param1->unk_04.unk_02 = param2;
    param1->unk_04.unk_20 = param3;
}

static void WiFiLobbyMinigameBucket_ClearProjectile(WiFiLobbyMinigameBucketProjectileState *param0)
{
    memset(param0, 0, sizeof(WiFiLobbyMinigameBucketProjectileState));
}

static void WiFiLobbyMinigameBucket_UpdateProjectiles(WiFiLobbyMinigameBucketGame *param0)
{
    int v0;

    for (v0 = 0; v0 < 96; v0++) {
        if ((param0->unk_4C[v0].unk_00 == 1) || (param0->unk_4C[v0].unk_00 == 2)) {
            WiFiLobbyMinigameBucket_UpdateProjectile(param0, &param0->unk_4C[v0]);
        } else if (param0->unk_4C[v0].unk_00 == 5) {
            WiFiLobbyMinigameBucket_UpdateBouncingProjectile(&param0->unk_4C[v0], param0);
        } else if (param0->unk_4C[v0].unk_00 == 3) {
            WiFiLobbyMinigameBucket_UpdateSinkingProjectile(&param0->unk_4C[v0], param0);
        }
    }
}

static void WiFiLobbyMinigameBucket_UpdateProjectile(WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketProjectileState *param1)
{
    VecFx32 v0;
    u32 v1;
    VecFx32 v2;
    BOOL v3;
    fx32 v4;
    u32 v5;

    if ((param1->unk_00 != 1) && (param1->unk_00 != 2)) {
        return;
    }

    v4 = param1->unk_2C.y;
    v5 = param1->unk_00;

    WiFiLobbyMinigameBucket_GetProjectileVelocity(param1, &v0);

    if (param1->unk_00 == 1) {
        v1 = WiFiLobbyMinigameBucket_CheckProjectileCollision(&param0->unk_19CC, &param1->unk_2C, &v0, &v2);
    } else {
        v1 = 0;
    }

    WiFiLobbyMinigameBucket_MoveProjectile(param1, &v0);

    if ((v1 == 3) || (v1 == 1)) {
        WiFiLobbyMinigameBucket_MoveProjectile(param1, &v2);
    }

    param1->unk_02++;

    if (v1 == 1) {
        param0->unk_18 += WiFiLobbyMinigameBucket_GetScoreForHit(param0);

        if (param0->unk_18 > 99999) {
            param0->unk_18 = 99999;
        }

        switch (param0->unk_1C) {
        case 0:
            Sound_PlayEffect(SEQ_SE_PL_NOMI02_sseq);
            Sound_PlayEffect(SEQ_SE_PL_POINT1_sseq);
            break;
        case 1:
            Sound_PlayEffect(SEQ_SE_PL_NOMI02_sseq);
            Sound_PlayEffect(SEQ_SE_PL_POINT2_sseq);
            break;
        default:
            Sound_PlayEffect(SEQ_SE_PL_NOMI02_sseq);
            Sound_PlayEffect(SEQ_SE_PL_POINT3_sseq);
            break;
        }

        WiFiLobbyMinigameBucket_StartProjectileSink(param1, param0);
        WiFiLobbyMinigameBucket_ShowThrowSprite(&param0->unk_1AB4.unk_3E8, param0->unk_14, param0->unk_1C, param0->unk_00);

        if (param0->unk_1C < 99) {
            param0->unk_1C++;
        }

        if (param0->unk_1C == 3) {
            WiFiLobbyMinigameBucket_ShowScore(&param0->unk_1AB4.unk_6B1C, &param0->unk_1AB4, param0->unk_1C);
        } else {
            WiFiLobbyMinigameBucket_UpdateScore(&param0->unk_1AB4.unk_6B1C, &param0->unk_1AB4, param0->unk_1C);
        }
    } else {
        v3 = 0;
        v1 = WiFiLobbyMinigameBucket_IsInsideBucket(&param0->unk_19CC, &param1->unk_2C);

        if (v1 == 1) {
            v3 = 1;

            if (v5 == 1) {
                Sound_PlayEffect(SEQ_SE_DP_023_sseq);
            }

            WiFiLobbyMinigameBucket_BounceProjectile(param1, param0, 1);
        } else if (param1->unk_2C.y <= (FX32_CONST(-50))) {
            v1 = WiFiLobbyMinigameBucket_IsProjectileNearBucket(param1);

            if (v1 == 0) {
                v3 = 1;

                if (v4 <= (FX32_CONST(-50))) {
                    WiFiLobbyMinigameBucket_SetProjectileState(param0, param1, 0, param0->unk_1C);
                } else {
                    WiFiLobbyMinigameBucket_BounceProjectile(param1, param0, 0);
                }
            } else if (param1->unk_2C.y <= (FX32_CONST(0.250f))) {
                v3 = 1;
                WiFiLobbyMinigameBucket_SetProjectileState(param0, param1, 0, param0->unk_1C);
            }
        } else {
            v1 = WiFiLobbyMinigameBucket_IsProjectileFar(param1);

            if (v1 == 1) {
                v3 = 1;

                VEC_Subtract(&param1->unk_2C, &v0, &param1->unk_2C);
                WiFiLobbyMinigameBucket_ReflectProjectile(param1, param0, 1, FX32_CONST(0.250f), 0);
            }
        }

        if ((v3 == 1) && (v5 == 1)) {
            param0->unk_1C = 0;
            WiFiLobbyMinigameBucket_HideScore(&param0->unk_1AB4.unk_6B1C);
        }
    }
}

static void WiFiLobbyMinigameBucket_UpdateAllProjectileSprites(WiFiLobbyMinigameBucketGame *param0)
{
    int v0;

    for (v0 = 0; v0 < 96; v0++) {
        WiFiLobbyMinigameBucket_FinishProjectile(&param0->unk_4C[v0], param0);
    }
}

static void WiFiLobbyMinigameBucket_FinishProjectiles(WiFiLobbyMinigameBucketGame *param0)
{
    int v0;

    for (v0 = 0; v0 < 96; v0++) {
        if (param0->unk_4C[v0].unk_01 == 1) {
            param0->unk_4C[v0].unk_00 = 2;
        }

        WiFiLobbyMinigameBucket_FinishProjectile(&param0->unk_4C[v0], param0);
    }
}

static void WiFiLobbyMinigameBucket_FinishProjectile(WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketGame *param1)
{
    if (param0->unk_01) {
        if ((param0->unk_00 == 3) && (param0->unk_04.unk_02 == 1)) {
            param0->unk_00 = 4;
        } else {
            WiFiLobbyMinigameBucket_ClearProjectile(param0);
        }

        WiFiLobbyMinigameBucket_HideBerry(&param1->unk_1AB4, param0);
    }
}

static void WiFiLobbyMinigameBucket_ResetProjectiles(WiFiLobbyMinigameBucketGame *param0)
{
    int v0;

    for (v0 = 0; v0 < 96; v0++) {
        if (param0->unk_4C[v0].unk_00 == 1) {
            param0->unk_4C[v0].unk_00 = 2;
        }
    }
}

static BOOL WiFiLobbyMinigameBucket_HasActiveProjectiles(const WiFiLobbyMinigameBucketGame *param0)
{
    int v0;

    for (v0 = 0; v0 < 96; v0++) {
        if ((param0->unk_4C[v0].unk_00 == 1) || (param0->unk_4C[v0].unk_00 == 2) || (param0->unk_4C[v0].unk_00 == 5) || (param0->unk_4C[v0].unk_00 == 3)) {
            return 1;
        }
    }

    return 0;
}

static fx32 WiFiLobbyMinigameBucket_GetProjectileSpeed(const WiFiLobbyMinigameBucketProjectileState *param0)
{
    fx32 v0;

    v0 = param0->unk_04.unk_10 - FX_Mul(0x670, param0->unk_02 * FX32_ONE);

    if (v0 < 0) {
        v0 = 0;
    }

    return v0;
}

static void WiFiLobbyMinigameBucket_GetProjectileVelocity(const WiFiLobbyMinigameBucketProjectileState *param0, VecFx32 *param1)
{
    fx32 v0;
    VecFx32 v1;

    v0 = WiFiLobbyMinigameBucket_GetProjectileSpeed(param0);

    param1->x = FX_Mul(param0->unk_04.unk_04.x, v0);
    param1->y = FX_Mul(param0->unk_04.unk_04.y, v0);
    param1->y += FX_Mul(0xffffeccc, param0->unk_02 * FX32_ONE);
    param1->z = FX_Mul(param0->unk_04.unk_04.z, v0);
}

static void WiFiLobbyMinigameBucket_BounceProjectile(WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketGame *param1, BOOL param2)
{
    fx32 v0;

    if (param2 == 1) {
        v0 = (FX32_CONST(0.850f));
    } else {
        v0 = (FX32_CONST(0.80f));
    }

    WiFiLobbyMinigameBucket_ReflectProjectile(param0, param1, param2, v0, 1);
}

static void WiFiLobbyMinigameBucket_ReflectProjectile(WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketGame *param1, BOOL param2, fx32 param3, BOOL param4)
{
    fx32 v0;
    fx32 v1;
    VecFx32 v2;
    u32 v3;

    if (param2) {
        param0->unk_04.unk_04.x = -param0->unk_04.unk_04.x;
        param0->unk_04.unk_04.z = -param0->unk_04.unk_04.z;

        if (param4) {
            v3 = MTRNG_Next();

            if (MATH_ABS(param0->unk_04.unk_04.x) <= MATH_ABS(param0->unk_04.unk_04.z)) {
                v1 = FX_Mul(param0->unk_04.unk_04.z, FX32_CONST(1.0f));

                if ((v3 % 2) == 1) {
                    param0->unk_04.unk_04.x = -v1;
                } else {
                    param0->unk_04.unk_04.x = v1;
                }
            } else {
                v1 = FX_Mul(param0->unk_04.unk_04.x, FX32_CONST(1.0f));

                if ((v3 % 2) == 1) {
                    param0->unk_04.unk_04.z = -v1;
                } else {
                    param0->unk_04.unk_04.z = v1;
                }
            }
        }
    }

    param0->unk_04.unk_10 = FX_Mul(param0->unk_04.unk_10, param3);
    param0->unk_02 = 0;
    param0->unk_00 = 5;

    WiFiLobbyMinigameBucket_GetProjectileVelocity(param0, &v2);
    WiFiLobbyMinigameBucket_MoveProjectile(param0, &v2);

    param0->unk_02++;
}

static void WiFiLobbyMinigameBucket_UpdateBouncingProjectile(WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketGame *param1)
{
    VecFx32 v0;
    BOOL v1;
    BOOL v2 = 0;
    fx32 v3;

    if (param0->unk_00 != 5) {
        return;
    }

    v3 = param0->unk_2C.y;

    WiFiLobbyMinigameBucket_GetProjectileVelocity(param0, &v0);
    WiFiLobbyMinigameBucket_MoveProjectile(param0, &v0);

    param0->unk_02++;

    v1 = WiFiLobbyMinigameBucket_IsInsideBucket(&param1->unk_19CC, &param0->unk_2C);

    if (v1 == 1) {
        WiFiLobbyMinigameBucket_BounceProjectile(param0, param1, 1);
    } else {
        if (param0->unk_2C.y <= (FX32_CONST(-50))) {
            v1 = WiFiLobbyMinigameBucket_IsProjectileNearBucket(param0);

            if (v1 == 0) {
                if (v3 <= (FX32_CONST(-50))) {
                    v2 = 1;
                } else {
                    WiFiLobbyMinigameBucket_BounceProjectile(param0, param1, 0);
                }
            } else if (param0->unk_2C.y <= (FX32_CONST(-100))) {
                v2 = 1;
            }

            if (param0->unk_04.unk_10 <= 0x2000) {
                v2 = 1;
            }
        } else {
            v1 = WiFiLobbyMinigameBucket_IsProjectileFar(param0);

            if (v1 == 1) {
                VEC_Subtract(&param0->unk_2C, &v0, &param0->unk_2C);
                WiFiLobbyMinigameBucket_ReflectProjectile(param0, param1, 1, FX32_CONST(0.250f), 0);
            }
        }
    }

    if (param0->unk_04.unk_10 <= 0x1000) {
        v2 = 1;
    }

    if (v2 == 1) {
        WiFiLobbyMinigameBucket_SetProjectileState(param1, param0, 0, param1->unk_1C);
    }
}

static BOOL WiFiLobbyMinigameBucket_IsProjectileNearBucket(const WiFiLobbyMinigameBucketProjectileState *param0)
{
    if ((param0->unk_40 >= (FX32_CONST(188))) && (param0->unk_40 <= (FX32_CONST(240)))) {
        return 1;
    }

    return 0;
}

static BOOL WiFiLobbyMinigameBucket_IsProjectileClose(const WiFiLobbyMinigameBucketProjectileState *param0)
{
    if (param0->unk_40 <= (FX32_CONST(120))) {
        return 1;
    }

    return 0;
}

static BOOL WiFiLobbyMinigameBucket_IsProjectileFar(WiFiLobbyMinigameBucketProjectileState *param0)
{
    if (param0->unk_40 >= (FX32_CONST(240))) {
        if (param0->unk_3C == 1) {
            return 1;
        }
    } else if (param0->unk_3C == 0) {
        param0->unk_3C = 1;
    }

    return 0;
}

static void WiFiLobbyMinigameBucket_StartProjectileSink(WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketGame *param1)
{
    param0->unk_00 = 3;
    param0->unk_38 = 8;
    param0->unk_3A = param1->unk_1C;
}

static void WiFiLobbyMinigameBucket_UpdateSinkingProjectile(WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketGame *param1)
{
    VecFx32 v0;
    u32 v1;
    VecFx32 v2;

    WiFiLobbyMinigameBucket_GetProjectileVelocity(param0, &v0);
    v1 = WiFiLobbyMinigameBucket_CheckProjectileCollision(&param1->unk_19CC, &param0->unk_2C, &v0, &v2);
    WiFiLobbyMinigameBucket_MoveProjectile(param0, &v0);

    if ((v1 == 3) || (v1 == 1)) {
        WiFiLobbyMinigameBucket_MoveProjectile(param0, &v2);
    }

    param0->unk_02++;
    param0->unk_38--;

    if (param0->unk_38 <= 0) {
        WiFiLobbyMinigameBucket_SetProjectileState(param1, param0, 1, param0->unk_3A);
    }
}

static void WiFiLobbyMinigameBucket_MoveProjectile(WiFiLobbyMinigameBucketProjectileState *param0, const VecFx32 *param1)
{
    VecFx32 v0;

    VEC_Add(&param0->unk_2C, param1, &param0->unk_2C);

    v0.y = 0;
    v0.x = param0->unk_2C.x;
    v0.z = param0->unk_2C.z;

    param0->unk_40 = VEC_Mag(&v0);
}

static void WiFiLobbyMinigameBucket_HandleTouchInput(WiFiLobbyMinigameBucketGame *param0)
{
    if (gSystem.touchHeld == 0) {
        WiFiLobbyMinigameBucket_HandleTouchRelease(param0);
    } else {
        WiFiLobbyMinigameBucket_HandleTouchDrag(param0);
    }
}

static void WiFiLobbyMinigameBucket_HandleTouchRelease(WiFiLobbyMinigameBucketGame *param0)
{
    WiFiLobbyMinigameBucketProjectile v0;
    NNSG2dSVec2 v1;
    BOOL v2;
    NNSG2dSVec2 v3, v4;
    s32 v5;
    BOOL v6 = 0;
    fx32 v7;

    if (param0->unk_20.unk_00 == 0) {
        param0->unk_20.unk_28++;
        return;
    }

    v2 = WiFiLobbyMinigameBucket_PeekTouchPoint(&param0->unk_20, &v3);
    GF_ASSERT(v2);
    v2 = WiFiLobbyMinigameBucket_PeekLastTouchPoint(&param0->unk_20, &v4);
    GF_ASSERT(v2);
    v5 = WiFiLobbyMinigameBucket_GetTouchPointCount(&param0->unk_20);

    if (v5 >= 2) {
        v0.unk_00 = param0->unk_14;
        v0.unk_02 = 0;
        v1.x = (v3.x - v4.x) / v5;
        v1.y = (v3.y - v4.y) / v5;
        v0.unk_04.x = v1.x << FX32_SHIFT;
        v0.unk_04.z = v1.y << FX32_SHIFT;
        v0.unk_04.y = 0;

        v7 = VEC_Mag(&v0.unk_04);

        if (v7 < 0x8000) {
            if (v7 != 0) {
                VEC_Normalize(&v0.unk_04, &v0.unk_04);
                v0.unk_04.x = FX_Mul(v0.unk_04.x, 0x8000);
                v0.unk_04.z = FX_Mul(v0.unk_04.z, 0x8000);
            } else {
                v6 = 1;
            }
        } else if (v7 > (0x8000 + 0x16200)) {
            VEC_Normalize(&v0.unk_04, &v0.unk_04);
            v0.unk_04.x = FX_Mul(v0.unk_04.x, 0x8000 + 0x16200);
            v0.unk_04.z = FX_Mul(v0.unk_04.z, 0x8000 + 0x16200);
        }

        if (v6 == 0) {
            v0.unk_04.y = 0x26000;
            v0.unk_10 = VEC_Mag(&v0.unk_04);
            v0.unk_10 = FX_Mul(v0.unk_10, FX32_CONST(0.6));

            VEC_Normalize(&v0.unk_04, &v0.unk_04);
            WiFiLobbyMinigameBucket_ScreenToWorld(v4.x, v4.y, &v0.unk_14);

            v0.unk_14.y = (FX32_CONST(0));

            WiFiLobbyMinigameBucket_RotateWorldToPlayer(&v0.unk_14, &v0.unk_14, v0.unk_00, param0->unk_10);
            WiFiLobbyMinigameBucket_RotateWorldToPlayer(&v0.unk_04, &v0.unk_04, v0.unk_00, param0->unk_10);

            if (param0->unk_1C >= 5) {
                v0.unk_24 = 1;
            } else {
                v0.unk_24 = 0;
            }

            WiFiLobbyMinigameBucket_SpawnProjectile(param0, &v0, 1);
            Sound_PlayEffect(SEQ_SE_DP_FW104_sseq);
        }
    } else {
        v6 = 1;
    }

    if (v6 == 1) {
        WiFiLobbyMinigameBucket_SpawnSplash(&param0->unk_1AB4.unk_6A3C, v4.x, v4.y);
    }

    WiFiLobbyMinigameBucket_ResetTouch(param0);
    param0->unk_20.unk_28 = 0;
}

static void WiFiLobbyMinigameBucket_HandleTouchDrag(WiFiLobbyMinigameBucketGame *param0)
{
    NNSG2dSVec2 v0;
    BOOL v1;

    if (param0->unk_20.unk_00 == 0) {
        v1 = WiFiLobbyMinigameBucket_IsTouchInPlayArea(param0);

        if (v1 == 1) {
            param0->unk_20.unk_00 = 1;

            WiFiLobbyMinigameBucket_ShowCursor(&param0->unk_1AB4.unk_6A34);
            WiFiLobbyMinigameBucket_AdvanceBgFade(&param0->unk_1AB4.unk_758);
        }
    }

    if (param0->unk_20.unk_00 == 1) {
        if (param0->unk_8690.bufferSize == 1) {
            v0.x = param0->unk_8690.buffer[0].x;
            v0.y = param0->unk_8690.buffer[0].y;
            WiFiLobbyMinigameBucket_PushTouchPoint(&param0->unk_20, v0);
        } else if (param0->unk_8690.bufferSize >= 2) {
            v0.x = param0->unk_8690.buffer[0].x;
            v0.y = param0->unk_8690.buffer[0].y;
            WiFiLobbyMinigameBucket_PushTouchPoint(&param0->unk_20, v0);
            v0.x = param0->unk_8690.buffer[param0->unk_8690.bufferSize - 1].x;
            v0.y = param0->unk_8690.buffer[param0->unk_8690.bufferSize - 1].y;
            WiFiLobbyMinigameBucket_PushTouchPoint(&param0->unk_20, v0);
        } else {
            v0.x = gSystem.touchX;
            v0.y = gSystem.touchY;
            WiFiLobbyMinigameBucket_PushTouchPoint(&param0->unk_20, v0);
        }
    }
}

static BOOL WiFiLobbyMinigameBucket_IsTouchInPlayArea(WiFiLobbyMinigameBucketGame *param0)
{
    s32 v0;
    s32 v1;
    s32 v2;

    if (param0->unk_20.unk_28 < 2) {
        return 0;
    }

    v0 = 128 - gSystem.touchX;
    v1 = -96 - gSystem.touchY;
    v2 = FX_Sqrt(((v0 * v0) + (v1 * v1)) << FX32_SHIFT) >> FX32_SHIFT;

    if (v2 <= (190 - -96)) {
        return 1;
    }

    return 0;
}

static void WiFiLobbyMinigameBucket_ResetTouchBuffer(WiFiLobbyMinigameBucketTouchBuffer *param0)
{
    memset(param0->unk_04, 0, sizeof(NNSG2dSVec2) * 8);
    param0->unk_24 = 0;
    param0->unk_26 = 0;
}

static void WiFiLobbyMinigameBucket_PushTouchPoint(WiFiLobbyMinigameBucketTouchBuffer *param0, NNSG2dSVec2 param1)
{
    if (((param0->unk_26 + 1) % 8) == param0->unk_24) {
        NNSG2dSVec2 v0;

        WiFiLobbyMinigameBucket_PopTouchPoint(param0, &v0);
    }

    param0->unk_04[param0->unk_26] = param1;
    param0->unk_26 = (param0->unk_26 + 1) % 8;
}

static BOOL WiFiLobbyMinigameBucket_PopTouchPoint(WiFiLobbyMinigameBucketTouchBuffer *param0, NNSG2dSVec2 *param1)
{
    if (param0->unk_26 == param0->unk_24) {
        return 0;
    }

    *param1 = param0->unk_04[param0->unk_24];
    param0->unk_24 = (param0->unk_24 + 1) % 8;

    return 1;
}

static BOOL WiFiLobbyMinigameBucket_PeekTouchPoint(WiFiLobbyMinigameBucketTouchBuffer *param0, NNSG2dSVec2 *param1)
{
    if (param0->unk_26 == param0->unk_24) {
        return 0;
    }

    *param1 = param0->unk_04[param0->unk_24];

    return 1;
}

static BOOL WiFiLobbyMinigameBucket_PeekLastTouchPoint(WiFiLobbyMinigameBucketTouchBuffer *param0, NNSG2dSVec2 *param1)
{
    s32 v0;

    if (param0->unk_26 == param0->unk_24) {
        return 0;
    }

    v0 = param0->unk_26 - 1;

    if (v0 < 0) {
        v0 += 8;
    }

    *param1 = param0->unk_04[v0];

    return 1;
}

static u32 WiFiLobbyMinigameBucket_GetTouchPointCount(WiFiLobbyMinigameBucketTouchBuffer *param0)
{
    if (param0->unk_24 > param0->unk_26) {
        return (8 - param0->unk_24) + param0->unk_26;
    }

    return param0->unk_26 - param0->unk_24;
}

static void WiFiLobbyMinigameBucket_ResetTouch(WiFiLobbyMinigameBucketGame *param0)
{
    param0->unk_20.unk_00 = 0;

    WiFiLobbyMinigameBucket_ResetTouchBuffer(&param0->unk_20);
    WiFiLobbyMinigameBucket_HideCursor(&param0->unk_1AB4.unk_6A34);
}

static void WiFiLobbyMinigameBucket_InitStageTransition(WiFiLobbyMinigameBucketStageTransition *param0, const WiFiLobbyMinigameBucketStage *param1, const WiFiLobbyMinigameBucketMode *param2)
{
    param0->unk_48 = 16;
    WiFiLobbyMinigameBucket_GetStageData(param1, param2, 0, &param0->unk_00);
}

static void WiFiLobbyMinigameBucket_StartStageTransition(WiFiLobbyMinigameBucketStageTransition *param0, const WiFiLobbyMinigameBucketStage *param1, const WiFiLobbyMinigameBucketMode *param2, u16 param3, u16 param4)
{
    WiFiLobbyMinigameBucketStageData v0, v1;

    WiFiLobbyMinigameBucket_GetStageData(param1, param2, param3, &v0);
    WiFiLobbyMinigameBucket_GetStageData(param1, param2, param4, &v1);

    param0->unk_18 = v0;
    param0->unk_00 = v0;
    param0->unk_30.unk_00 = v1.unk_00 - v0.unk_00;
    param0->unk_30.unk_08 = v1.unk_08 - v0.unk_08;
    param0->unk_30.unk_10 = v1.unk_10 - v0.unk_10;
    param0->unk_30.unk_14 = v1.unk_14 - v0.unk_14;

    if ((v1.unk_04 - v0.unk_04) < ((0xffff + v1.unk_04) - v0.unk_04)) {
        param0->unk_30.unk_04 = v1.unk_04 - v0.unk_04;
    } else {
        param0->unk_30.unk_04 = ((0xffff + v1.unk_04) - v0.unk_04);
    }

    if ((v1.unk_0C - v0.unk_0C) < ((0xffff + v1.unk_0C) - v0.unk_0C)) {
        param0->unk_30.unk_0C = v1.unk_0C - v0.unk_0C;
    } else {
        param0->unk_30.unk_0C = ((0xffff + v1.unk_0C) - v0.unk_0C);
    }

    param0->unk_48 = 0;
}

static BOOL WiFiLobbyMinigameBucket_UpdateStageTransition(WiFiLobbyMinigameBucketStageTransition *param0)
{
    if (param0->unk_48 >= 16) {
        return 1;
    }

    param0->unk_48++;

    param0->unk_00.unk_00 = param0->unk_18.unk_00 + ((param0->unk_30.unk_00 * param0->unk_48) / 16);
    param0->unk_00.unk_04 = param0->unk_18.unk_04 + ((param0->unk_30.unk_04 * param0->unk_48) / 16);
    param0->unk_00.unk_08 = param0->unk_18.unk_08 + ((param0->unk_30.unk_08 * param0->unk_48) / 16);
    param0->unk_00.unk_0C = param0->unk_18.unk_0C + ((param0->unk_30.unk_0C * param0->unk_48) / 16);
    param0->unk_00.unk_10 = param0->unk_18.unk_10 + ((param0->unk_30.unk_10 * param0->unk_48) / 16);
    param0->unk_00.unk_14 = param0->unk_18.unk_14 + ((param0->unk_30.unk_14 * param0->unk_48) / 16);

    return 0;
}

static void WiFiLobbyMinigameBucket_ApplyStageTransition(WiFiLobbyMinigameBucketGame *param0, const WiFiLobbyMinigameBucketStageTransition *param1)
{
    WiFiLobbyMinigameBucket_ApplyStageData(param0, &param1->unk_00);
}

static void WiFiLobbyMinigameBucket_ApplyStageData(WiFiLobbyMinigameBucketGame *param0, const WiFiLobbyMinigameBucketStageData *param1)
{
    WiFiLobbyMinigameBucket_SetCameraRoll(&param0->unk_19CC, param1->unk_04);
    WiFiLobbyMinigameBucket_SetCameraTargetHeight(&param0->unk_1AB4, param1->unk_08);
    WiFiLobbyMinigameBucket_SetCameraAngle(&param0->unk_1AB4, param1->unk_0C);
    WiFiLobbyMinigameBucket_SetCameraDistance(&param0->unk_19CC, param1->unk_10);
    WiFiLobbyMinigameBucket_SetCameraScale(&param0->unk_19CC, param1->unk_14);
}

static void WiFiLobbyMinigameBucket_GetStageData(const WiFiLobbyMinigameBucketStage *param0, const WiFiLobbyMinigameBucketMode *param1, u32 param2, WiFiLobbyMinigameBucketStageData *param3)
{
    u16 v0;
    s32 v1;

    GF_ASSERT(param2 < param0->unk_00);

    *param3 = param0->unk_04[param2];

    v0 = param3->unk_04;
    param3->unk_04 = v0;

    v0 = param3->unk_0C;
    param3->unk_0C = v0;

    if (param1->unk_00) {
        v1 = 6 - (param2 + 1);

        if (v1 < 0) {
            v1 = 0;
        }

        param3->unk_14 = param0->unk_04[v1].unk_14;
    }

    if (param1->unk_01) {
        param3->unk_04 = -param3->unk_04;
    }
}

static void WiFiLobbyMinigameBucket_InitSwalot(WiFiLobbyMinigameBucketSwalot *param0, WiFiLobbyMinigameBucketScene *param1, u32 heapID)
{
    NARC *v0;
    BOOL v1;

    memset(param0, 0, sizeof(WiFiLobbyMinigameBucketSwalot));

    v0 = NARC_ctor(NARC_INDEX_RESOURCE__ENG__WIFI_LOBBY_MINIGAME__WLMNGM_TOOL, heapID);

    {
        param0->unk_00[0] = SpriteResourceCollection_AddTilesFrom(param1->unk_1AC[0], v0, 21, 0, 120, NNS_G2D_VRAM_TYPE_2DSUB, heapID);
        param0->unk_00[1] = SpriteResourceCollection_AddPaletteFrom(param1->unk_1AC[1], v0, 20, 0, 120, NNS_G2D_VRAM_TYPE_2DSUB, 2, heapID);
        param0->unk_00[2] = SpriteResourceCollection_AddFrom(param1->unk_1AC[2], v0, 22, 0, 120, 2, heapID);
        param0->unk_00[3] = SpriteResourceCollection_AddFrom(param1->unk_1AC[3], v0, 23, 0, 120, 3, heapID);

        v1 = SpriteTransfer_RequestCharAtEndWithHardwareMappingType(param0->unk_00[0]);
        GF_ASSERT(v1);
        v1 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_00[1]);
        GF_ASSERT(v1);

        SpriteResource_ReleaseData(param0->unk_00[0]);
        SpriteResource_ReleaseData(param0->unk_00[1]);
        SpriteResourcesHeader_Init(&param0->unk_10, 120, 120, 120, 120, 0xffffffff, 0xffffffff, 0, 0, param1->unk_1AC[0], param1->unk_1AC[1], param1->unk_1AC[2], param1->unk_1AC[3], NULL, NULL);
    }

    {
        SpriteListTemplate v2;

        v2.list = param1->unk_1C;
        v2.resourceData = &param0->unk_10;
        v2.position.x = FX32_CONST(128);
        v2.position.y = FX32_CONST(120) + (512 << FX32_SHIFT);
        v2.priority = 0;
        v2.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
        v2.heapID = heapID;

        param0->unk_34 = SpriteList_Add(&v2);
        Sprite_SetDrawFlag(param0->unk_34, FALSE);
    }

    NARC_dtor(v0);
}

static void WiFiLobbyMinigameBucket_FreeSwalot(WiFiLobbyMinigameBucketSwalot *param0, WiFiLobbyMinigameBucketScene *param1)
{
    {
        Sprite_Delete(param0->unk_34);
    }

    {
        SpriteTransfer_ResetCharTransfer(param0->unk_00[0]);
        SpriteTransfer_ResetPlttTransfer(param0->unk_00[1]);
        SpriteResourceCollection_Remove(param1->unk_1AC[0], param0->unk_00[0]);
        SpriteResourceCollection_Remove(param1->unk_1AC[1], param0->unk_00[1]);
        SpriteResourceCollection_Remove(param1->unk_1AC[2], param0->unk_00[2]);
        SpriteResourceCollection_Remove(param1->unk_1AC[3], param0->unk_00[3]);
    }

    memset(param0, 0, sizeof(WiFiLobbyMinigameBucketSwalot));
}

static void WiFiLobbyMinigameBucket_ShowSwalot(WiFiLobbyMinigameBucketSwalot *param0)
{
    {
        param0->unk_38 = 1;
        param0->unk_3A = 0;
        param0->unk_39 = 0;
    }

    Sprite_SetDrawFlag(param0->unk_34, TRUE);
}

static BOOL WiFiLobbyMinigameBucket_UpdateSwalot(WiFiLobbyMinigameBucketSwalot *param0, WiFiLobbyMinigameBucketGame *param1)
{
    switch (param0->unk_3A) {
    case 0:
        Sprite_SetAnimFrame(param0->unk_34, 0);
        WiFiLobbyMinigameBucket_ShowCursor(&param1->unk_1AB4.unk_6A34);
        WiFiLobbyMinigameBucket_SetCursorPosition(&param1->unk_1AB4.unk_6A34, 128, sSwalotMouthYPositions[0]);

        param0->unk_3B = 0;
        param0->unk_3A++;
        break;
    case 1:
        Sprite_UpdateAnim(param0->unk_34, FX32_CONST(2));

        {
            u32 v0;

            v0 = Sprite_GetAnimFrame(param0->unk_34);

            switch (v0) {
            case 10:
                if (param0->unk_3B == 0) {
                    WiFiLobbyMinigameBucket_SpawnThrowFromSwalot(param1, 128, 96, 128, 64, 2);
                    Sound_PlayEffect(SEQ_SE_DP_FW104_sseq);
                    param0->unk_3B = 1;
                }
                break;
            case 11:
                param0->unk_39++;

                if (param0->unk_39 >= 2) {
                    param0->unk_3A = 3;
                } else {
                    param0->unk_3A = 2;
                    param0->unk_3C = 16;
                }

                WiFiLobbyMinigameBucket_HideCursor(&param1->unk_1AB4.unk_6A34);
                break;
            default:
                break;
            }

            WiFiLobbyMinigameBucket_SetCursorPosition(&param1->unk_1AB4.unk_6A34, 128, sSwalotMouthYPositions[v0]);
        }
        break;
    case 2:
        param0->unk_3C--;

        if (param0->unk_3C <= 0) {
            param0->unk_3A = 0;
        }
        break;
    case 3:
        if (WiFiLobbyMinigameBucket_HasActiveProjectiles(param1) == 0) {
            Sprite_SetDrawFlag(param0->unk_34, FALSE);
            return 1;
        }
        break;
    }

    WiFiLobbyMinigameBucket_UpdateProjectiles(param1);
    WiFiLobbyMinigameBucket_UpdateAllProjectileSprites(param1);

    return 0;
}

static void WiFiLobbyMinigameBucket_InitScoreBoard(WiFiLobbyMinigameBucketScoreBoard *param0)
{
    memset(param0, 0, sizeof(WiFiLobbyMinigameBucketScoreBoard));
    param0->unk_14 = 0xffff;
}

static void WiFiLobbyMinigameBucket_AddScoreBoardEntry(WiFiLobbyMinigameBucketScoreBoard *param0, u32 param1, u32 param2)
{
    param0->unk_00[param2] = param1;
    param0->unk_10 |= 1 << param2;

    if (param1 == 0) {
        return;
    }

    if (param0->unk_14 != 0xffff) {
        if (param0->unk_00[param0->unk_14] < param1) {
            param0->unk_14 = param2;
        }
    } else {
        param0->unk_14 = param2;
    }
}

static void WiFiLobbyMinigameBucket_ResetScoreBoard(WiFiLobbyMinigameBucketScoreBoard *param0)
{
    param0->unk_10 = 0;
    param0->unk_14 = 0xffff;
}

static u32 WiFiLobbyMinigameBucket_GetScoreBoardLeader(const WiFiLobbyMinigameBucketScoreBoard *param0)
{
    return param0->unk_14;
}

static BOOL WiFiLobbyMinigameBucket_IsScoreBoardFull(const WiFiLobbyMinigameBucketScoreBoard *param0, u32 param1)
{
    int v0;
    int v1 = 0;

    for (v0 = 0; v0 < 4; v0++) {
        if ((param0->unk_10 & (1 << v0)) != 0) {
            v1++;
        }
    }

    if (param1 <= v1) {
        return 1;
    }

    return 0;
}

static void WiFiLobbyMinigameBucket_SetVramBanks(void)
{
    GXBanks v0 = {
        GX_VRAM_BG_32_FG,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_128_B,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_0_A,
        GX_VRAM_TEXPLTT_0123_E
    };

    GXLayers_SetBanks(&v0);
}

static void WiFiLobbyMinigameBucket_InitG3D(void)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);

    G2_SetBG0Priority(2);
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(1);
    G3X_AlphaTest(0, 0);
    G3X_AlphaBlend(1);
    G3X_EdgeMarking(1);
    G3X_SetFog(0, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0);
    G3X_SetClearColor(GX_RGB(26, 26, 26), 0, 0x7fff, 63, 0);
    G3_ViewPort(0, 0, 255, 191);
}

static void WiFiLobbyMinigameBucket_InitG3DPipeline(WiFiLobbyMinigameBucketScene *param0, u32 param1, u32 param2, u32 heapID)
{
    param0->unk_18 = G3DPipeline_Init(heapID, TEXTURE_VRAM_SIZE_128K, PALETTE_VRAM_SIZE_64K, WiFiLobbyMinigameBucket_InitG3D);
    WiFiLobbyMinigameBucket_InitCamera3D(param0, param1, param2, heapID);
}

static void WiFiLobbyMinigameBucket_FreeG3DPipeline(WiFiLobbyMinigameBucketScene *param0)
{
    WiFiLobbyMinigameBucket_FreeCamera(param0);
    G3DPipelineBuffers_Free(param0->unk_18);
}

static void WiFiLobbyMinigameBucket_InitScene(WiFiLobbyMinigameBucketGame *param0, u32 heapID)
{
    NARC *v0;

    HeapExp_FndInitAllocator(&param0->unk_1AB4.unk_6BBC, heapID, 32);

    WiFiLobbyMinigameBucket_SetVramBanks();
    WiFiLobbyMinigameBucket_InitG3DPipeline(&param0->unk_1AB4, param0->unk_10, param0->unk_14, heapID);
    WiFiLobbyMinigameBucket_InitBackgrounds(&param0->unk_1AB4, heapID);
    WiFiLobbyMinigameBucket_InitSpriteSystem(&param0->unk_1AB4, heapID);
    WiFiLobbyMinigameBucket_InitText(&param0->unk_1AB4, heapID);

    v0 = NARC_ctor(NARC_INDEX_GRAPHIC__BUCKET, heapID);

    WiFiLobbyMinigameBucket_LoadSpriteResources(&param0->unk_1AB4, v0, heapID);
    WiFiLobbyMinigameBucket_InitBucketModel(&param0->unk_1AB4.unk_204, &param0->unk_1AB4, v0, param0->unk_10, param0->unk_14, heapID, &param0->unk_1AB4.unk_6BBC);
    WiFiLobbyMinigameBucket_InitSwalotModel(&param0->unk_1AB4.unk_524, v0, heapID, &param0->unk_1AB4.unk_6BBC);
    WiFiLobbyMinigameBucket_InitBerryModels(&param0->unk_1AB4, v0, heapID);
    WiFiLobbyMinigameBucket_InitCursor(&param0->unk_1AB4, &param0->unk_1AB4.unk_6A34, param0->unk_14, heapID);
    WiFiLobbyMinigameBucket_InitSplash(&param0->unk_1AB4, &param0->unk_1AB4.unk_6A3C, param0->unk_14, heapID);
    WiFiLobbyMinigameBucket_LoadBackgroundTiles(&param0->unk_1AB4, v0, param0->unk_14, heapID);
    WiFiLobbyMinigameBucket_InitIntroWindow(&param0->unk_1AB4.unk_4E8, &param0->unk_1AB4, param0->unk_8720, param0->unk_10, param0->unk_14, v0, heapID);
    WiFiLobbyMinigameBucket_ResetIntroState(&param0->unk_1AB4, param0->unk_10, param0->unk_14, heapID);
    WiFiLobbyMinigameBucket_InitThrowSprites(&param0->unk_1AB4.unk_3E8, &param0->unk_1AB4, param0->unk_10, param0->unk_14, heapID);
    WiFiLobbyMinigameBucket_InitBgFade(&param0->unk_1AB4.unk_758, param0->unk_14);
    WiFiLobbyMinigameBucket_InitScoreDisplay(&param0->unk_1AB4.unk_6B1C, &param0->unk_1AB4, v0, heapID);

    NARC_dtor(v0);
    param0->unk_1AB4.unk_754 = WiFiLobbyMinigame_CreateIntroAnimation(param0->unk_1AB4.unk_1C, heapID);
}

static void WiFiLobbyMinigameBucket_FreeScene(WiFiLobbyMinigameBucketGame *param0)
{
    WiFiLobbyMinigameBucket_FreeScoreDisplay(&param0->unk_1AB4.unk_6B1C, &param0->unk_1AB4);
    WiFiLobbyMinigameBucket_FreeThrowSprites(&param0->unk_1AB4.unk_3E8, &param0->unk_1AB4);
    WiFiLobbyMinigameBucket_Noop(&param0->unk_1AB4, param0->unk_10);
    WiFiLobbyMinigameBucket_FreeIntroWindow(&param0->unk_1AB4.unk_4E8, &param0->unk_1AB4);
    WiFiLobbyMinigameBucket_Noop2(&param0->unk_1AB4);
    WiFiLobbyMinigameBucket_FreeSplash(&param0->unk_1AB4, &param0->unk_1AB4.unk_6A3C);
    WiFiLobbyMinigameBucket_FreeCursor(&param0->unk_1AB4.unk_6A34);
    WiFiLobbyMinigameBucket_FreeBerryModels(&param0->unk_1AB4);
    WiFiLobbyMinigameBucket_FreeSwalotModel(&param0->unk_1AB4.unk_524, &param0->unk_1AB4.unk_6BBC);
    WiFiLobbyMinigameBucket_FreeBucketModel(&param0->unk_1AB4.unk_204, &param0->unk_1AB4, &param0->unk_1AB4.unk_6BBC);
    WiFiLobbyMinigameBucket_FreeSpriteResources(&param0->unk_1AB4);
    WiFiLobbyMinigame_FreeIntroAnimation(param0->unk_1AB4.unk_754);
    WiFiLobbyMinigameBucket_FreeBackgrounds(&param0->unk_1AB4);
    WiFiLobbyMinigameBucket_FreeSpriteSystem(&param0->unk_1AB4);
    WiFiLobbyMinigameBucket_FreeText(&param0->unk_1AB4);
    WiFiLobbyMinigameBucket_FreeG3DPipeline(&param0->unk_1AB4);

    G2_BlendNone();
    G2S_BlendNone();
}

static void WiFiLobbyMinigameBucket_DrawScene(const WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketScene *param1)
{
    WiFiLobbyMinigameBucket_SetSwalotModelState(&param1->unk_524, &param0->unk_19CC, param0->unk_00);
    WiFiLobbyMinigameBucket_UpdateSwalotModelAnim(&param1->unk_524, &param0->unk_19CC, param0->unk_00);
    WiFiLobbyMinigameBucket_UpdateCursor(&param1->unk_6A34);
    WiFiLobbyMinigameBucket_RenderScene(param0, param1);
    WiFiLobbyMinigameBucket_UpdateBgFade(&param1->unk_758, param1);
    WiFiLobbyMinigameBucket_UpdateScoreDisplay(&param1->unk_6B1C);
}

static void WiFiLobbyMinigameBucket_RenderScene(const WiFiLobbyMinigameBucketGame *param0, WiFiLobbyMinigameBucketScene *param1)
{
    WiFiLobbyMinigameBucket_UpdateSplash(&param1->unk_6A3C);
    WiFiLobbyMinigameBucket_UpdateThrowSprites(&param1->unk_3E8);

    G3_ResetG3X();

    WiFiLobbyMinigameBucket_UpdateCameraMatrix(param1);

    NNS_G3dGlbLightVector(0, 0, -FX32_ONE, 0);
    NNS_G3dGlbLightColor(0, GX_RGB(31, 31, 31));
    NNS_G3dGlbMaterialColorDiffAmb(GX_RGB(31, 31, 31), GX_RGB(31, 31, 31), 0);
    NNS_G3dGlbMaterialColorSpecEmi(GX_RGB(31, 31, 31), GX_RGB(31, 31, 31), 0);
    NNS_G3dGePushMtx();

    {
        WiFiLobbyMinigameBucket_DrawBucketModel(&param1->unk_204);
    }

    NNS_G3dGePopMtx(1);
    NNS_G3dGePushMtx();

    {
        WiFiLobbyMinigameBucket_DrawSwalotModel(&param1->unk_524, &param0->unk_19CC);
    }

    NNS_G3dGePopMtx(1);
    NNS_G3dGePushMtx();

    {
        WiFiLobbyMinigameBucket_DrawBerries(param1, param0->unk_10);
    }

    NNS_G3dGePopMtx(1);

    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
    SpriteList_Update(param1->unk_1C);
}

static void WiFiLobbyMinigameBucket_InitBackgrounds(WiFiLobbyMinigameBucketScene *param0, u32 heapID)
{
    param0->unk_00 = BgConfig_New(heapID);

    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_3D,
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
            .screenBase = GX_BG_SCRBASE_0x7800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_00, BG_LAYER_MAIN_1, &v1, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_1, 32, 0, heapID);
        Bg_ClearTilemap(param0->unk_00, BG_LAYER_MAIN_1);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0x7000,
            .charBase = GX_BG_CHARBASE_0x04000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_00, BG_LAYER_MAIN_2, &v2, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_2, 32, 0, heapID);
        Bg_ClearTilemap(param0->unk_00, BG_LAYER_MAIN_2);
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xd000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_00, BG_LAYER_SUB_0, &v3, 0);
        Bg_ClearTilesRange(BG_LAYER_SUB_0, 32, 0, heapID);
        Bg_ClearTilemap(param0->unk_00, BG_LAYER_SUB_0);
    }

    {
        BgTemplate v4 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xd800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_00, BG_LAYER_SUB_1, &v4, 0);
        Bg_ClearTilesRange(BG_LAYER_SUB_1, 32, 0, heapID);
        Bg_ClearTilemap(param0->unk_00, BG_LAYER_SUB_1);
    }

    {
        BgTemplate v5 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_00, BG_LAYER_SUB_2, &v5, 0);
        Bg_ClearTilesRange(BG_LAYER_SUB_2, 32, 0, heapID);
        Bg_ClearTilemap(param0->unk_00, BG_LAYER_SUB_2);
    }

    {
        BgTemplate v6 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_00, BG_LAYER_SUB_3, &v6, 0);
        Bg_ClearTilesRange(BG_LAYER_SUB_3, 32, 0, heapID);
        Bg_ClearTilemap(param0->unk_00, BG_LAYER_SUB_3);
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(5), heapID);
    LoadStandardWindowGraphics(param0->unk_00, BG_LAYER_MAIN_1, 1, 4, 0, heapID);
}

static void WiFiLobbyMinigameBucket_FreeBackgrounds(WiFiLobbyMinigameBucketScene *param0)
{
    Bg_FreeTilemapBuffer(param0->unk_00, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0->unk_00, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0->unk_00, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(param0->unk_00, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(param0->unk_00, BG_LAYER_SUB_2);
    Bg_FreeTilemapBuffer(param0->unk_00, BG_LAYER_SUB_3);
    Heap_Free(param0->unk_00);
}

static void WiFiLobbyMinigameBucket_InitSpriteSystem(WiFiLobbyMinigameBucketScene *param0, u32 heapID)
{
    int v0;

    NNS_G2dInitOamManagerModule();
    RenderOam_Init(0, 126, 0, 31, 0, 126, 0, 31, heapID);

    {
        CharTransferTemplate v1 = {
            16, 128 * 1024, 16 * 1024, 0
        };

        v1.heapID = heapID;
        CharTransfer_InitWithVramModes(&v1, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_128K);
    }

    PlttTransfer_Init(16, heapID);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_128K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    param0->unk_1C = SpriteList_InitRendering(128, &param0->unk_20, heapID);

    SetSubScreenViewRect(&param0->unk_20, 0, 512 << FX32_SHIFT);

    for (v0 = 0; v0 < 4; v0++) {
        param0->unk_1AC[v0] = SpriteResourceCollection_New(16, v0, heapID);
    }

    param0->unk_1F0 = FontOAMManager_New(8, heapID);
}

static void WiFiLobbyMinigameBucket_FreeSpriteSystem(WiFiLobbyMinigameBucketScene *param0)
{
    int v0;

    FontOAMManager_Free(param0->unk_1F0);
    SpriteList_Delete(param0->unk_1C);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(param0->unk_1AC[v0]);
    }

    CharTransfer_Free();
    PlttTransfer_Free();
    RenderOam_Free();
}

static void WiFiLobbyMinigameBucket_LoadSpriteResources(WiFiLobbyMinigameBucketScene *param0, NARC *param1, u32 param2)
{
    BOOL v0;

    {
        param0->unk_1E0[0] = SpriteResourceCollection_AddTilesFrom(param0->unk_1AC[0], param1, 2, 0, 200, NNS_G2D_VRAM_TYPE_2DMAIN, param2);
        param0->unk_1E0[1] = SpriteResourceCollection_AddPaletteFrom(param0->unk_1AC[1], param1, 3, 0, 200, NNS_G2D_VRAM_TYPE_2DMAIN, 8, param2);
        param0->unk_1E0[2] = SpriteResourceCollection_AddFrom(param0->unk_1AC[2], param1, 1, 0, 200, 2, param2);
        param0->unk_1E0[3] = SpriteResourceCollection_AddFrom(param0->unk_1AC[3], param1, 0, 0, 200, 3, param2);

        v0 = SpriteTransfer_RequestCharAtEndWithHardwareMappingType(param0->unk_1E0[0]);
        GF_ASSERT(v0);
        v0 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_1E0[1]);
        GF_ASSERT(v0);

        SpriteResource_ReleaseData(param0->unk_1E0[0]);
        SpriteResource_ReleaseData(param0->unk_1E0[1]);
        SpriteResourcesHeader_Init(&param0->unk_1BC, 200, 200, 200, 200, 0xffffffff, 0xffffffff, 0, 0, param0->unk_1AC[0], param0->unk_1AC[1], param0->unk_1AC[2], param0->unk_1AC[3], NULL, NULL);
    }
}

static void WiFiLobbyMinigameBucket_FreeSpriteResources(WiFiLobbyMinigameBucketScene *param0)
{
    {
        SpriteTransfer_ResetCharTransfer(param0->unk_1E0[0]);
        SpriteTransfer_ResetPlttTransfer(param0->unk_1E0[1]);
        SpriteResourceCollection_Remove(param0->unk_1AC[0], param0->unk_1E0[0]);
        SpriteResourceCollection_Remove(param0->unk_1AC[1], param0->unk_1E0[1]);
        SpriteResourceCollection_Remove(param0->unk_1AC[2], param0->unk_1E0[2]);
        SpriteResourceCollection_Remove(param0->unk_1AC[3], param0->unk_1E0[3]);
    }
}

static void WiFiLobbyMinigameBucket_InitText(WiFiLobbyMinigameBucketScene *param0, u32 heapID)
{
    param0->unk_04 = StringTemplate_Default(heapID);
    param0->unk_08 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0407, heapID);
    param0->unk_0C = String_Init(128, heapID);
    param0->unk_10 = String_Init(128, heapID);
}

static void WiFiLobbyMinigameBucket_FreeText(WiFiLobbyMinigameBucketScene *param0)
{
    String_Free(param0->unk_10);
    String_Free(param0->unk_0C);
    MessageLoader_Free(param0->unk_08);
    StringTemplate_Free(param0->unk_04);
}

static void WiFiLobbyMinigameBucket_InitCamera3D(WiFiLobbyMinigameBucketScene *param0, u32 param1, u32 param2, u32 heapID)
{
    CameraAngle v0;
    VecFx32 v1;
    MtxFx33 v2;

    param0->camera = Camera_Alloc(heapID);
    param0->unk_1F8.x = 0;
    param0->unk_1F8.y = 0;
    param0->unk_1F8.z = 0;

    v0.x = 0xf112;
    v0.y = sStageRotationAngles[param1 - 1][param2];
    v0.z = ((0 * 0xffff) / 360);

    Camera_InitWithTarget(&param0->unk_1F8, 0x1d9000, &v0, (22 * 0xffff) / 360, 0, 1, param0->camera);

    v1.x = 0;
    v1.y = (FX32_ONE);
    v1.z = 0;

    Camera_SetUp(&v1, param0->camera);
    Camera_SetAsActive(param0->camera);
    Camera_SetClipping(FX32_CONST(200), FX32_CONST(1000), param0->camera);
}

static void WiFiLobbyMinigameBucket_FreeCamera(WiFiLobbyMinigameBucketScene *param0)
{
    Camera_Delete(param0->camera);
}

static void WiFiLobbyMinigameBucket_UpdateCameraMatrix(WiFiLobbyMinigameBucketScene *param0)
{
    Camera_ComputeViewMatrix();
}

static void WiFiLobbyMinigameBucket_LoadBackgroundTiles(WiFiLobbyMinigameBucketScene *param0, NARC *param1, u32 param2, u32 param3)
{
    static const u8 v0[4] = {
        0,
        9,
        10,
        11,
    };

    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 12, param0->unk_00, 4, 0, 0, 0, param3);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 14, param0->unk_00, 7, 0, 0, 0, param3);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 15, param0->unk_00, 6, 0, 0, 0, param3);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 16, param0->unk_00, 5, 0, 0, 0, param3);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 17, param0->unk_00, 4, 0, 0, 0, param3);
    Graphics_LoadPaletteFromOpenNARC(param1, 13, 4, 0, 12 * 32, param3);
    Bg_ChangeTilemapRectPalette(param0->unk_00, 7, 0, 0, 32, 32, v0[param2]);
    Bg_ChangeTilemapRectPalette(param0->unk_00, 6, 0, 0, 32, 32, 2 + (param2 * 2));
    Bg_ChangeTilemapRectPalette(param0->unk_00, 5, 0, 0, 32, 32, 1 + (param2 * 2));
    Bg_ChangeTilemapRectPalette(param0->unk_00, 4, 0, 0, 32, 32, 1 + (param2 * 2));
    Bg_CopyTilemapBufferToVRAM(param0->unk_00, 4);
    Bg_CopyTilemapBufferToVRAM(param0->unk_00, 5);
    Bg_CopyTilemapBufferToVRAM(param0->unk_00, 6);
    Bg_CopyTilemapBufferToVRAM(param0->unk_00, 7);
}

static void WiFiLobbyMinigameBucket_Noop2(WiFiLobbyMinigameBucketScene *param0)
{
    return;
}

static void WiFiLobbyMinigameBucket_InitSwalotModel(WiFiLobbyMinigameBucketSwalotModel *param0, NARC *param1, u32 heapID, NNSFndAllocator *param3)
{
    static const u16 v0[6] = {
        26,
        27,
        28,
        29,
        30,
        31,
    };

    static const u16 v1[3] = {
        23,
        24,
        25,
    };

    int v2, v3, v4, v5;
    const NNSG3dResName *v6;
    const NNSG3dResNodeInfo *v7;

    memset(param0, 0, sizeof(WiFiLobbyMinigameBucketSwalotModel));

    for (v2 = 0; v2 < 3; v2++) {
        Easy3DModel_LoadFrom(&param0->unk_168[v2], param1, v1[v2], heapID);
        Easy3DObject_Init(&param0->unk_00[v2], &param0->unk_168[v2]);
        Easy3DObject_SetVisible(&param0->unk_00[v2], 0);
        Easy3DObject_SetPosition(&param0->unk_00[v2], sSwalotBasePosition.x, sSwalotBasePosition.y + (-FX32_CONST(200)), sSwalotBasePosition.z);
        Easy3DObject_SetScale(&param0->unk_00[v2], FX32_CONST(1.50f), FX32_CONST(1.50f), FX32_CONST(1.50f));
    }

    for (v2 = 0; v2 < 6; v2++) {
        Easy3DAnim_LoadFrom(&param0->unk_198[v2], &param0->unk_168[sSwalotAnimModelForAnim[v2]], param1, v0[v2], heapID, param3);
        Easy3DAnim_SetFrame(&param0->unk_198[v2], 0);

        v3 = 0;
        v7 = NNS_G3dGetNodeInfo(param0->unk_168[sSwalotAnimModelForAnim[v2]].model);

        while ((v6 = NNS_G3dGetNodeNameByIdx(v7, v3)) != NULL) {
            NNS_G3dAnmObjDisableID(param0->unk_198[v2].animObj, v3);
            v3++;
        }

        for (v3 = 0; v3 < 15; v3++) {
            v5 = NNS_G3dGetNodeIdxByName(v7, &sSwalotAnimNodeNames[v2][v3]);

            if (v5 != -1) {
                NNS_G3dAnmObjEnableID(param0->unk_198[v2].animObj, v5);
            }
        }
    }

    for (v2 = 0; v2 < 1; v2++) {
        Easy3DAnim_LoadFrom(&param0->unk_214[v2], &param0->unk_168[sSwalotAnimModelIndex[v2]], param1, 32, heapID, param3);
        Easy3DObject_AddAnim(&param0->unk_00[sSwalotAnimModelIndex[v2]], &param0->unk_214[v2]);
    }

    param0->unk_22C = 4;
    param0->unk_22E = 0;

    WiFiLobbyMinigameBucket_SetSwalotIdleAnim(param0, 0);

    Easy3DObject_AddAnim(&param0->unk_00[1], &param0->unk_198[4]);
    Easy3DAnim_SetFrame(&param0->unk_198[4], 0);
    Easy3DObject_SetVisible(&param0->unk_00[1], 1);

    param0->unk_210 = 4;
}

static void WiFiLobbyMinigameBucket_FreeSwalotModel(WiFiLobbyMinigameBucketSwalotModel *param0, NNSFndAllocator *param1)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Easy3DModel_Release(&param0->unk_168[v0]);
    }

    for (v0 = 0; v0 < 6; v0++) {
        Easy3DAnim_Release(&param0->unk_198[v0], param1);
    }

    for (v0 = 0; v0 < 1; v0++) {
        Easy3DAnim_Release(&param0->unk_214[v0], param1);
    }

    memset(param0, 0, sizeof(WiFiLobbyMinigameBucketSwalotModel));
}

static void WiFiLobbyMinigameBucket_SetSwalotModelState(WiFiLobbyMinigameBucketSwalotModel *param0, const WiFiLobbyMinigameBucketCamera *param1, int param2)
{
    WiFiLobbyMinigameBucket_SetSwalotModelPosition(param0, param1);
    WiFiLobbyMinigameBucket_SetSwalotModelRotation(param0, param1);
    WiFiLobbyMinigameBucket_SetSwalotModelScale(param0, param1);

    switch (param2) {
    case 0:
    case 2:
        WiFiLobbyMinigameBucket_SetSwalotAnim(param0, 1);
        WiFiLobbyMinigameBucket_SetSwalotMouthFrame(param0, param1->unk_04);
        WiFiLobbyMinigameBucket_SetSwalotIdleAnim(param0, 1);
        break;
    case 1:
        WiFiLobbyMinigameBucket_SetSwalotAnim(param0, 3);
        WiFiLobbyMinigameBucket_SetSwalotIdleAnim(param0, 0);
        WiFiLobbyMinigameBucket_UpdateSwalotAnim(param0, FX32_CONST(1.0));
        break;
    }
}

static void WiFiLobbyMinigameBucket_UpdateSwalotModelAnim(WiFiLobbyMinigameBucketSwalotModel *param0, const WiFiLobbyMinigameBucketCamera *param1, int param2)
{
    Easy3DAnim_UpdateLooped(&param0->unk_198[0], FX32_CONST(1));
    WiFiLobbyMinigameBucket_UpdateSwalotMouthAnim(param0);
}

static void WiFiLobbyMinigameBucket_SetSwalotModelPosition(WiFiLobbyMinigameBucketSwalotModel *param0, const WiFiLobbyMinigameBucketCamera *param1)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Easy3DObject_SetPosition(&param0->unk_00[v0], param1->unk_D8.x, param1->unk_D8.y, param1->unk_D8.z);
    }
}

static void WiFiLobbyMinigameBucket_SetSwalotModelRotation(WiFiLobbyMinigameBucketSwalotModel *param0, const WiFiLobbyMinigameBucketCamera *param1)
{
    int v0;
    fx32 v1;
    u32 v2 = param1->unk_02 + ((0 * 0xffff) / 360);

    for (v0 = 0; v0 < 3; v0++) {
        Easy3DObject_SetRotation(&param0->unk_00[v0], (u16)v2, 1);
    }
}

static void WiFiLobbyMinigameBucket_SetSwalotModelScale(WiFiLobbyMinigameBucketSwalotModel *param0, const WiFiLobbyMinigameBucketCamera *param1)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Easy3DObject_SetScale(&param0->unk_00[v0], param1->unk_D4, param1->unk_D4, param1->unk_D4);
    }
}

static void WiFiLobbyMinigameBucket_DrawSwalotModel(WiFiLobbyMinigameBucketSwalotModel *param0, const WiFiLobbyMinigameBucketCamera *param1)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Easy3DObject_Draw(&param0->unk_00[v0]);
    }
}

static void WiFiLobbyMinigameBucket_SetSwalotMouthFrame(WiFiLobbyMinigameBucketSwalotModel *param0, u32 param1)
{
    fx32 v0;

    param1 -= ((20 * 0xffff) / 360);
    v0 = (param1 * 90) / CalcAngleRotationIdx_Wraparound(90 - ((20 * 0xffff) / 360));
    v0 = (v0 * (FX32_CONST(180))) / 90;
    v0 = FX32_CONST(180) - v0;

    Easy3DAnim_SetFrame(&param0->unk_198[1], v0);
}

static void WiFiLobbyMinigameBucket_SetSwalotAnim(WiFiLobbyMinigameBucketSwalotModel *param0, u32 param1)
{
    GF_ASSERT(param1 < 6);

    if (param0->unk_210 != param1) {
        Easy3DObject_RemoveAnim(&param0->unk_00[sSwalotAnimModelForAnim[param0->unk_210]], &param0->unk_198[param0->unk_210]);
        Easy3DObject_AddAnim(&param0->unk_00[sSwalotAnimModelForAnim[param1]], &param0->unk_198[param1]);
        Easy3DAnim_SetFrame(&param0->unk_198[param1], 0);
        Easy3DObject_SetVisible(&param0->unk_00[sSwalotAnimModelForAnim[param0->unk_210]], 0);
        Easy3DObject_SetVisible(&param0->unk_00[sSwalotAnimModelForAnim[param1]], 1);
        param0->unk_210 = param1;
    }
}

static BOOL WiFiLobbyMinigameBucket_UpdateSwalotAnim(WiFiLobbyMinigameBucketSwalotModel *param0, fx32 param1)
{
    return Easy3DAnim_Update(&param0->unk_198[param0->unk_210], param1);
}

static void WiFiLobbyMinigameBucket_SetSwalotIdleAnim(WiFiLobbyMinigameBucketSwalotModel *param0, BOOL param1)
{
    if (param0->unk_212 != param1) {
        if (param1 == 1) {
            Easy3DObject_AddAnim(&param0->unk_00[sSwalotAnimModelForAnim[0]], &param0->unk_198[0]);
        } else {
            Easy3DObject_RemoveAnim(&param0->unk_00[sSwalotAnimModelForAnim[0]], &param0->unk_198[0]);
        }

        param0->unk_212 = param1;
    }
}

static void WiFiLobbyMinigameBucket_SetSwalotMouthOpen(WiFiLobbyMinigameBucketSwalotModel *param0, BOOL param1)
{
    param0->unk_22E = param1;
}

static void WiFiLobbyMinigameBucket_SetSwalotAnimIndex(WiFiLobbyMinigameBucketSwalotModel *param0, u32 param1)
{
    param0->unk_22C = param1;
}

static void WiFiLobbyMinigameBucket_UpdateSwalotMouthAnim(WiFiLobbyMinigameBucketSwalotModel *param0)
{
    int v0;

    if (param0->unk_22E == 1) {
        if ((param0->unk_228 + (FX32_CONST(2))) < (sSwalotAnimFrameRanges[4][1] * FX32_ONE)) {
            param0->unk_228 += (FX32_CONST(2));
        } else {
            param0->unk_228 = (sSwalotAnimFrameRanges[1][0] * FX32_ONE);
        }
    } else {
        u32 v1;

        if (param0->unk_22C == 4) {
            v1 = 0;
        } else {
            v1 = 1 + param0->unk_22C;
        }

        if (param0->unk_228 < (sSwalotAnimFrameRanges[v1][0] * FX32_ONE)) {
            param0->unk_228 = sSwalotAnimFrameRanges[v1][0] * FX32_ONE;
        } else if ((param0->unk_228 + (FX32_CONST(2))) < (sSwalotAnimFrameRanges[v1][1] * FX32_ONE)) {
            param0->unk_228 += (FX32_CONST(2));
        } else {
            param0->unk_228 = sSwalotAnimFrameRanges[v1][0] * FX32_ONE;
        }
    }

    for (v0 = 0; v0 < 1; v0++) {
        Easy3DAnim_SetFrame(&param0->unk_214[v0], param0->unk_228);
    }
}

static void WiFiLobbyMinigameBucket_ScreenToWorld(s16 param0, s16 param1, VecFx32 *param2)
{
    param2->x = (((255 - param0) * ((FX32_CONST(150)) / 256)) - ((FX32_CONST(150)) / 2));
    param2->z = (FX32_CONST(-300)) - (((param1) * ((FX32_CONST(150)) / 256)) - ((FX32_CONST(150)) / 2));
}

static void WiFiLobbyMinigameBucket_WorldToScreen(const VecFx32 *param0, NNSG2dSVec2 *param1)
{
    param1->x = 255 - (((param0->x) + ((FX32_CONST(150)) / 2)) / ((FX32_CONST(150)) / 256));
    param1->y = ((((-param0->z) + ((fx32)((-300 > 0) ? (-300 * (1 << 12) + 0.5f) : (-300 * (1 << 12) - 0.5f)))) + ((FX32_CONST(150)) / 2)) / ((FX32_CONST(150)) / 256));
}

static void WiFiLobbyMinigameBucket_RotateWorldToPlayer(const VecFx32 *param0, VecFx32 *param1, u32 param2, u32 param3)
{
    MtxFx33 v0;

    MTX_Identity33(&v0);
    MTX_RotY33(&v0, FX_SinIdx(sPlayerRotationAngles[param3 - 1][param2]), FX_CosIdx(sPlayerRotationAngles[param3 - 1][param2]));
    MTX_MultVec33(param0, &v0, param1);
}

static void WiFiLobbyMinigameBucket_RotatePlayerToWorld(const VecFx32 *param0, VecFx32 *param1, u32 param2, u32 param3)
{
    MtxFx33 v0;

    MTX_Identity33(&v0);
    MTX_RotY33(&v0, FX_SinIdx(sPlayerRotationAngles[param3 - 1][param2]), FX_CosIdx(sPlayerRotationAngles[param3 - 1][param2]));
    MTX_Inverse33(&v0, &v0);
    MTX_MultVec33(param0, &v0, param1);
}

static void WiFiLobbyMinigameBucket_InitBerryModels(WiFiLobbyMinigameBucketScene *param0, NARC *param1, u32 heapID)
{
    BOOL v0;
    int v1;
    static const u8 v2[5] = {
        41,
        42,
        43,
        44,
        45,
    };

    for (v1 = 0; v1 < 5; v1++) {
        Easy3DModel_LoadFrom(&param0->unk_760.unk_00[v1], param1, v2[v1], heapID);
    }

    Easy3DModel_LoadFrom(&param0->unk_760.unk_50, param1, 46, heapID);
    NNS_G3dMdlUseGlbAlpha(param0->unk_760.unk_50.model);

    {
        param0->unk_760.unk_60[0] = SpriteResourceCollection_AddTilesFrom(param0->unk_1AC[0], param1, 7, 0, 100, NNS_G2D_VRAM_TYPE_2DSUB, heapID);
        param0->unk_760.unk_60[1] = SpriteResourceCollection_AddPaletteFrom(param0->unk_1AC[1], param1, 4, 0, 100, NNS_G2D_VRAM_TYPE_2DSUB, 4, heapID);
        param0->unk_760.unk_60[2] = SpriteResourceCollection_AddFrom(param0->unk_1AC[2], param1, 6, 0, 100, 2, heapID);
        param0->unk_760.unk_60[3] = SpriteResourceCollection_AddFrom(param0->unk_1AC[3], param1, 5, 0, 100, 3, heapID);

        v0 = SpriteTransfer_RequestCharAtEndWithHardwareMappingType(param0->unk_760.unk_60[0]);
        GF_ASSERT(v0);
        v0 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_760.unk_60[1]);
        GF_ASSERT(v0);

        SpriteResource_ReleaseData(param0->unk_760.unk_60[0]);
        SpriteResource_ReleaseData(param0->unk_760.unk_60[1]);
    }

    SpriteResourcesHeader_Init(&param0->unk_760.unk_70, 100, 100, 100, 100, 0xffffffff, 0xffffffff, 0, 0, param0->unk_1AC[0], param0->unk_1AC[1], param0->unk_1AC[2], param0->unk_1AC[3], NULL, NULL);

    for (v1 = 0; v1 < 96; v1++) {
        WiFiLobbyMinigameBucket_InitBerry(param0, &param0->unk_7F4[v1], heapID);
    }
}

static void WiFiLobbyMinigameBucket_FreeBerryModels(WiFiLobbyMinigameBucketScene *param0)
{
    int v0;

    for (v0 = 0; v0 < 96; v0++) {
        WiFiLobbyMinigameBucket_FreeBerry(param0, &param0->unk_7F4[v0]);
    }

    {
        SpriteTransfer_ResetCharTransfer(param0->unk_760.unk_60[0]);
        SpriteTransfer_ResetPlttTransfer(param0->unk_760.unk_60[1]);
        SpriteResourceCollection_Remove(param0->unk_1AC[0], param0->unk_760.unk_60[0]);
        SpriteResourceCollection_Remove(param0->unk_1AC[1], param0->unk_760.unk_60[1]);
        SpriteResourceCollection_Remove(param0->unk_1AC[2], param0->unk_760.unk_60[2]);
        SpriteResourceCollection_Remove(param0->unk_1AC[3], param0->unk_760.unk_60[3]);
    }

    for (v0 = 0; v0 < 5; v0++) {
        Easy3DModel_Release(&param0->unk_760.unk_00[v0]);
    }

    Easy3DModel_Release(&param0->unk_760.unk_50);

    memset(&param0->unk_760, 0, sizeof(WiFiLobbyMinigameBucketBerryModels));
    memset(&param0->unk_7F4, 0, sizeof(WiFiLobbyMinigameBucketBerry) * 96);
}

static void WiFiLobbyMinigameBucket_ShowBerry(WiFiLobbyMinigameBucketScene *param0, const WiFiLobbyMinigameBucketProjectileState *param1, u32 param2, u32 param3)
{
    WiFiLobbyMinigameBucketBerry *v0 = WiFiLobbyMinigameBucket_AllocBerry(param0);

    if (param1->unk_04.unk_00 == param3) {
        WiFiLobbyMinigameBucket_ShowBerrySprite(param0, v0, param1, param2);
    } else {
        WiFiLobbyMinigameBucket_ShowBerryModel(param0, v0, param1);
    }
}

static void WiFiLobbyMinigameBucket_HideBerry(WiFiLobbyMinigameBucketScene *param0, const WiFiLobbyMinigameBucketProjectileState *param1)
{
    int v0;

    for (v0 = 0; v0 < 96; v0++) {
        if (param0->unk_7F4[v0].unk_F8 == param1) {
            WiFiLobbyMinigameBucket_HideBerryModel(&param0->unk_7F4[v0]);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

static void WiFiLobbyMinigameBucket_DrawBerries(WiFiLobbyMinigameBucketScene *param0, u32 param1)
{
    int v0;

    for (v0 = 0; v0 < 96; v0++) {
        if (param0->unk_7F4[v0].unk_F8 != NULL) {
            WiFiLobbyMinigameBucket_DrawBerry(&param0->unk_7F4[v0], param0, param1);
        }
    }
}

static void WiFiLobbyMinigameBucket_InitBerry(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketBerry *param1, u32 param2)
{
    {
        AffineSpriteListTemplate v0 = { 0 };

        v0.list = param0->unk_1C;
        v0.resourceData = &param0->unk_760.unk_70;
        v0.affineScale.x = FX32_ONE;
        v0.affineScale.y = FX32_ONE;
        v0.affineScale.z = FX32_ONE;
        v0.priority = 32;
        v0.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
        v0.heapID = param2;
        param1->unk_00 = SpriteList_AddAffine(&v0);

        Sprite_SetDrawFlag(param1->unk_00, FALSE);
    }

    Easy3DObject_Init(&param1->unk_7C, &param0->unk_760.unk_50);
    Easy3DObject_SetVisible(&param1->unk_7C, 0);
}

static void WiFiLobbyMinigameBucket_FreeBerry(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketBerry *param1)
{
    Sprite_Delete(param1->unk_00);
    memset(param1, 0, sizeof(WiFiLobbyMinigameBucketBerry));
}

static void WiFiLobbyMinigameBucket_ShowBerrySprite(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketBerry *param1, const WiFiLobbyMinigameBucketProjectileState *param2, u32 param3)
{
    param1->unk_F8 = param2;
    param1->unk_F4 = 1;
    param1->unk_104 = 0;

    Sprite_SetExplicitPalette(param1->unk_00, param2->unk_04.unk_00);
    WiFiLobbyMinigameBucket_UpdateBerrySprite(param1, param2, param3);
    Sprite_SetDrawFlag(param1->unk_00, TRUE);
}

static void WiFiLobbyMinigameBucket_ShowBerryModel(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketBerry *param1, const WiFiLobbyMinigameBucketProjectileState *param2)
{
    param1->unk_F8 = param2;
    param1->unk_104 = 0;

    Sprite_SetDrawFlag(param1->unk_00, FALSE);
    WiFiLobbyMinigameBucket_ShowBerryModelInternal(param1, param0);
}

static void WiFiLobbyMinigameBucket_DrawBerry(WiFiLobbyMinigameBucketBerry *param0, WiFiLobbyMinigameBucketScene *param1, u32 param2)
{
    BOOL v0;
    Easy3DModel *v1;

    if (param0->unk_F4 == 1) {
        v0 = WiFiLobbyMinigameBucket_UpdateBerrySprite(param0, param0->unk_F8, param2);

        if (v0 == 0) {
            WiFiLobbyMinigameBucket_ShowBerryModelInternal(param0, param1);
        }
    }

    if (param0->unk_F4 == 0) {
        v1 = WiFiLobbyMinigameBucket_GetBerryModel(param0->unk_F8, &param1->unk_760);

        if (param0->unk_F8->unk_00 == 5) {
            NNS_G3dMdlSetMdlAmbAll(v1->model, GX_RGB(31, 31, 31));
        } else {
            NNS_G3dMdlSetMdlAmbAll(v1->model, GX_RGB(18, 18, 18));
        }

        WiFiLobbyMinigameBucket_UpdateBerryRotation(param0);
        Easy3DObject_SetPosition(&param0->unk_04, param0->unk_F8->unk_2C.x, param0->unk_F8->unk_2C.y, param0->unk_F8->unk_2C.z);
        Easy3DObject_Draw(&param0->unk_04);

        if (Easy3DObject_IsVisible(&param0->unk_7C) == 1) {
            WiFiLobbyMinigameBucket_DrawBerryShadow(param0);
            Easy3DObject_Draw(&param0->unk_7C);
            WiFiLobbyMinigameBucket_ResetBerryShadow(param0);
        }
    }
}

static void WiFiLobbyMinigameBucket_DrawBerryShadow(WiFiLobbyMinigameBucketBerry *param0)
{
    BOOL v0;
    fx32 v1;
    fx32 v2;
    fx32 v3;
    int v4;

    v0 = WiFiLobbyMinigameBucket_IsProjectileClose(param0->unk_F8);

    if (v0 == 1) {
        v2 = (FX32_CONST(-300));
    } else {
        v0 = WiFiLobbyMinigameBucket_IsProjectileNearBucket(param0->unk_F8);

        if (v0 == 0) {
            v2 = (FX32_CONST(-50) - FX32_CONST(1));
        } else {
            v2 = (FX32_CONST(-300));
        }
    }

    Easy3DObject_SetPosition(&param0->unk_7C, param0->unk_F8->unk_2C.x, v2, param0->unk_F8->unk_2C.z);

    v1 = param0->unk_F8->unk_2C.y - v2;
    v3 = FX32_ONE + (FX_Div(FX_Mul(v1, FX32_CONST(1)), FX32_CONST(300)));

    Easy3DObject_SetScale(&param0->unk_7C, v3, v3, v3);

    v4 = (FX_Div(FX_Mul(v1, FX32_CONST(16)), FX32_CONST(300))) >> FX32_SHIFT;
    v4 = 8 + 16 - v4;

    NNS_G3dGlbPolygonAttr(0, 0, 0, 0, v4, 0);
}

static void WiFiLobbyMinigameBucket_ResetBerryShadow(WiFiLobbyMinigameBucketBerry *param0)
{
    NNS_G3dGlbPolygonAttr(0, 0, 0, 0, 31, 0);
}

static void WiFiLobbyMinigameBucket_HideBerryModel(WiFiLobbyMinigameBucketBerry *param0)
{
    param0->unk_F8 = NULL;
    param0->unk_F4 = 0;

    Sprite_SetDrawFlag(param0->unk_00, FALSE);
    Easy3DObject_SetVisible(&param0->unk_7C, 0);
}

static WiFiLobbyMinigameBucketBerry *WiFiLobbyMinigameBucket_AllocBerry(WiFiLobbyMinigameBucketScene *param0)
{
    int v0;

    for (v0 = 0; v0 < 96; v0++) {
        if (param0->unk_7F4[v0].unk_F8 == NULL) {
            return &param0->unk_7F4[v0];
        }
    }

    GF_ASSERT(FALSE);
    return NULL;
}

static BOOL WiFiLobbyMinigameBucket_UpdateBerrySprite(WiFiLobbyMinigameBucketBerry *param0, const WiFiLobbyMinigameBucketProjectileState *param1, u32 param2)
{
    VecFx32 v0;
    NNSG2dSVec2 v1;

    v0 = param0->unk_F8->unk_2C;

    WiFiLobbyMinigameBucket_RotatePlayerToWorld(&v0, &v0, param0->unk_F8->unk_04.unk_00, param2);
    WiFiLobbyMinigameBucket_WorldToScreen(&v0, &v1);

    v0.x = v1.x << FX32_SHIFT;
    v0.y = (v1.y << FX32_SHIFT) + (512 << FX32_SHIFT);
    v0.z = 0;

    Sprite_SetPosition(param0->unk_00, &v0);

    if ((v1.x < 0) || (v1.y < 0)) {
        return 0;
    }

    return 1;
}

static void WiFiLobbyMinigameBucket_ShowBerryModelInternal(WiFiLobbyMinigameBucketBerry *param0, WiFiLobbyMinigameBucketScene *param1)
{
    Easy3DModel *v0;

    Sprite_SetDrawFlag(param0->unk_00, FALSE);
    param0->unk_F4 = 0;

    v0 = WiFiLobbyMinigameBucket_GetBerryModel(param0->unk_F8, &param1->unk_760);

    Easy3DObject_Init(&param0->unk_04, v0);
    Easy3DObject_SetVisible(&param0->unk_04, 1);

    if (param0->unk_F8->unk_00 == 1) {
        Easy3DObject_SetVisible(&param0->unk_7C, 1);
    }
}

static Easy3DModel *WiFiLobbyMinigameBucket_GetBerryModel(const WiFiLobbyMinigameBucketProjectileState *param0, WiFiLobbyMinigameBucketBerryModels *param1)
{
    u32 v0;

    if (param0->unk_04.unk_24 == 1) {
        v0 = 4;
    } else {
        v0 = param0->unk_04.unk_00;
    }

    return &param1->unk_00[v0];
}

static void WiFiLobbyMinigameBucket_UpdateBerryRotation(WiFiLobbyMinigameBucketBerry *param0)
{
    fx32 v0;
    u16 v1;
    u16 v2;

    param0->unk_104--;

    if (param0->unk_104 < 0) {
        v0 = WiFiLobbyMinigameBucket_GetProjectileSpeed(param0->unk_F8);
        v2 = ((v0 * (1024 - 512)) / (0x8000 + 0x16200));
        v1 = FX_Atan2Idx(param0->unk_F8->unk_04.unk_04.z, param0->unk_F8->unk_04.unk_04.x);

        param0->unk_100 = 512 + (FX_Mul(FX_SinIdx(v1), v2 << FX32_SHIFT) >> FX32_SHIFT);
        param0->unk_102 = 512 + (FX_Mul(FX_CosIdx(v1), v2 << FX32_SHIFT) >> FX32_SHIFT);
        param0->unk_104 = 8;
    }

    param0->unk_FC += param0->unk_100;
    param0->unk_FE += param0->unk_102;

    Easy3DObject_SetRotation(&param0->unk_04, param0->unk_FC, 0);
    Easy3DObject_SetRotation(&param0->unk_04, param0->unk_FE, 2);
}

static void WiFiLobbyMinigameBucket_InitCursor(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketCursor *param1, u32 param2, u32 param3)
{
    AffineSpriteListTemplate v0 = { 0 };

    v0.list = param0->unk_1C;
    v0.resourceData = &param0->unk_760.unk_70;
    v0.affineScale.x = FX32_ONE;
    v0.affineScale.y = FX32_ONE;
    v0.affineScale.z = FX32_ONE;
    v0.priority = 32;
    v0.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    v0.heapID = param3;

    param1->unk_04 = SpriteList_AddAffine(&v0);

    Sprite_SetDrawFlag(param1->unk_04, FALSE);
    Sprite_SetExplicitPalette(param1->unk_04, param2);

    param1->unk_00 = 0;
}

static void WiFiLobbyMinigameBucket_FreeCursor(WiFiLobbyMinigameBucketCursor *param0)
{
    Sprite_Delete(param0->unk_04);
}

static void WiFiLobbyMinigameBucket_ShowCursor(WiFiLobbyMinigameBucketCursor *param0)
{
    Sprite_SetDrawFlag(param0->unk_04, TRUE);
    param0->unk_00 = 1;
}

static void WiFiLobbyMinigameBucket_UpdateCursor(WiFiLobbyMinigameBucketCursor *param0)
{
    VecFx32 v0;

    if (param0->unk_00 == 0) {
        return;
    }

    WiFiLobbyMinigameBucket_SetCursorPosition(param0, gSystem.touchX, gSystem.touchY);
}

static void WiFiLobbyMinigameBucket_SetCursorPosition(WiFiLobbyMinigameBucketCursor *param0, s32 param1, s32 param2)
{
    VecFx32 v0;

    v0.x = param1 << FX32_SHIFT;
    v0.y = (param2 << FX32_SHIFT) + (512 << FX32_SHIFT);

    Sprite_SetPosition(param0->unk_04, &v0);
}

static void WiFiLobbyMinigameBucket_HideCursor(WiFiLobbyMinigameBucketCursor *param0)
{
    Sprite_SetDrawFlag(param0->unk_04, FALSE);
    param0->unk_00 = 0;
}

static void WiFiLobbyMinigameBucket_InitSplash(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketSplash *param1, u32 param2, u32 param3)
{
    int v0;
    AffineSpriteListTemplate v1 = { 0 };

    v1.list = param0->unk_1C;
    v1.resourceData = &param0->unk_760.unk_70;
    v1.affineScale.x = 9;
    v1.affineScale.y = 9;
    v1.affineScale.z = 9;
    v1.priority = 32;
    v1.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    v1.heapID = param3;

    for (v0 = 0; v0 < 8; v0++) {
        param1->unk_00[v0].unk_04 = SpriteList_AddAffine(&v1);
        Sprite_SetDrawFlag(param1->unk_00[v0].unk_04, FALSE);
        Sprite_SetAffineOverwriteMode(param1->unk_00[v0].unk_04, 1);
        Sprite_SetExplicitPalette(param1->unk_00[v0].unk_04, param2);
        param1->unk_00[v0].unk_00 = 0;
    }
}

static void WiFiLobbyMinigameBucket_FreeSplash(WiFiLobbyMinigameBucketScene *param0, WiFiLobbyMinigameBucketSplash *param1)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        Sprite_Delete(param1->unk_00[v0].unk_04);
    }
}

static void WiFiLobbyMinigameBucket_UpdateSplash(WiFiLobbyMinigameBucketSplash *param0)
{
    int v0;
    s32 v1;
    s32 v2, v3;
    fx32 v4;
    VecFx32 v5;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->unk_00[v0].unk_00 == 1) {
            if (param0->unk_00[v0].unk_14 < 16) {
                v1 = param0->unk_00[v0].unk_14;
                WiFiLobbyMinigameBucket_CalcSplashVelocity(v1, 16, 8, 190, 125, &v2, &v3);
            } else if (param0->unk_00[v0].unk_14 < (16 + 10)) {
                v1 = param0->unk_00[v0].unk_14 - 16;
                WiFiLobbyMinigameBucket_CalcSplashVelocity(v1, 10, 4, 182, 140, &v2, &v3);
            } else {
                v1 = param0->unk_00[v0].unk_14 - (16 + 10);
                WiFiLobbyMinigameBucket_CalcSplashVelocity(v1, 6, 3, 180, 160, &v2, &v3);
            }

            param0->unk_00[v0].unk_14++;

            v4 = 9 - ((param0->unk_00[v0].unk_14 * 3) / (16 + 10 + 6));
            v4 = FX_Div(v4 << FX32_SHIFT, FX32_CONST(10));
            v5.x = v4;
            v5.y = v4;

            Sprite_SetAffineScale(param0->unk_00[v0].unk_04, &v5);

            if (param0->unk_00[v0].unk_18) {
                param0->unk_00[v0].unk_08.x += v2 << FX32_SHIFT;
            } else {
                param0->unk_00[v0].unk_08.x -= v2 << FX32_SHIFT;
            }

            param0->unk_00[v0].unk_08.y += v3 << FX32_SHIFT;
            Sprite_SetPosition(param0->unk_00[v0].unk_04, &param0->unk_00[v0].unk_08);

            if ((param0->unk_00[v0].unk_08.x < (-FX32_CONST(32))) || (param0->unk_00[v0].unk_08.x > (FX32_CONST(288))) || (param0->unk_00[v0].unk_08.y < (-FX32_CONST(32)) + (512 << FX32_SHIFT)) || (param0->unk_00[v0].unk_08.y > (FX32_CONST(224)) + (512 << FX32_SHIFT))) {
                param0->unk_00[v0].unk_00 = 0;
                Sprite_SetDrawFlag(param0->unk_00[v0].unk_04, FALSE);
            }
        }
    }
}

static void WiFiLobbyMinigameBucket_SpawnSplash(WiFiLobbyMinigameBucketSplash *param0, s32 param1, s32 param2)
{
    int v0;
    WiFiLobbyMinigameBucketSplashParticle *v1 = NULL;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->unk_00[v0].unk_00 == 0) {
            v1 = &param0->unk_00[v0];
            break;
        }
    }

    if (v1 == NULL) {
        return;
    }

    if (param1 < 128) {
        v1->unk_18 = 1;
    } else {
        v1->unk_18 = 0;
    }

    v1->unk_08.x = param1 << FX32_SHIFT;
    v1->unk_08.y = (param2 << FX32_SHIFT) + (512 << FX32_SHIFT);

    Sprite_SetPosition(v1->unk_04, &v1->unk_08);

    v1->unk_00 = 1;
    Sprite_SetDrawFlag(v1->unk_04, TRUE);
    v1->unk_14 = 0;
}

static void WiFiLobbyMinigameBucket_CalcSplashVelocity(int param0, int param1, int param2, int param3, int param4, s32 *param5, s32 *param6)
{
    s16 v0;
    s32 v1 = param4 - param3;
    v0 = param3 + ((param0 * v1) / param1);

    *param5 = FX_Mul(CalcCosineDegrees(v0), param2 << FX32_SHIFT) >> FX32_SHIFT;
    *param6 = FX_Mul(CalcSineDegrees(v0), param2 << FX32_SHIFT) >> FX32_SHIFT;
}

static void WiFiLobbyMinigameBucket_InitBucketModel(WiFiLobbyMinigameBucketBucketModel *param0, WiFiLobbyMinigameBucketScene *param1, NARC *param2, int param3, u32 param4, u32 heapID, NNSFndAllocator *param6)
{
    static const u16 v0[4] = {
        35,
        35,
        34,
        33,
    };
    static const u16 v1[3] = {
        38,
        39,
        40,
    };
    static const u16 v2[3] = {
        0,
        1,
        1,
    };
    u32 v3;
    int v4;

    for (v4 = 0; v4 < 3; v4++) {
        if (v4 == 0) {
            v3 = 36;
        } else if (v4 == 1) {
            v3 = 37;
        } else {
            v3 = v0[param3 - 1];
        }

        Easy3DModel_LoadFrom(&param0->unk_168[v4], param2, v3, heapID);
        Easy3DObject_Init(&param0->unk_00[v4], &param0->unk_168[v4]);
        Easy3DObject_SetPosition(&param0->unk_00[v4], 0, FX32_CONST(-90) - FX32_CONST(8), 0);
        Easy3DObject_SetScale(&param0->unk_00[v4], FX32_CONST(1.50f), FX32_CONST(1.50f), FX32_CONST(1.50f));

        if (v4 == 1) {
            Easy3DObject_SetVisible(&param0->unk_00[v4], 0);
        }

        if ((v4 == 0) || (v4 == 1)) {
            Easy3DObject_SetRotation(&param0->unk_00[v4], sStageRotationAngles[param3 - 1][param4], 1);
        } else {
            Easy3DObject_SetRotation(&param0->unk_00[v4], CalcAngleRotationIdx(180), 1);
        }
    }

    for (v4 = 0; v4 < 3; v4++) {
        Easy3DAnim_LoadFrom(&param0->unk_198[v4], &param0->unk_168[v2[v4]], param2, v1[v4], heapID, param6);
        Easy3DObject_AddAnim(&param0->unk_00[v2[v4]], &param0->unk_198[v4]);
    }

    param0->unk_1D4 = (FX32_CONST(1));
}

static void WiFiLobbyMinigameBucket_FreeBucketModel(WiFiLobbyMinigameBucketBucketModel *param0, WiFiLobbyMinigameBucketScene *param1, NNSFndAllocator *param2)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Easy3DAnim_Release(&param0->unk_198[v0], param2);
    }

    for (v0 = 0; v0 < 3; v0++) {
        Easy3DModel_Release(&param0->unk_168[v0]);
    }
}

static void WiFiLobbyMinigameBucket_DrawBucketModel(WiFiLobbyMinigameBucketBucketModel *param0)
{
    int v0;

    Easy3DAnim_UpdateLooped(&param0->unk_198[0], param0->unk_1D4);

    if (param0->unk_1D8) {
        switch (param0->unk_1D9) {
        case 0:

            if ((param0->unk_1DC + param0->unk_1E0) < (FX32_CONST(51))) {
                param0->unk_1DC += param0->unk_1E0;
            } else {
                param0->unk_1DC = 0;
            }

            if ((param0->unk_1E0 + (FX32_CONST(0.10))) <= (FX32_CONST(2.30))) {
                param0->unk_1E0 += (FX32_CONST(0.10));
            } else {
                param0->unk_1E0 = (FX32_CONST(2.30));
                param0->unk_1DA = 24;
                param0->unk_1D9++;
            }
            break;
        case 1:
            if ((param0->unk_1DC + param0->unk_1E0) < (FX32_CONST(51))) {
                param0->unk_1DC += param0->unk_1E0;
            } else {
                param0->unk_1DC = 0;
            }

            param0->unk_1DA--;

            if (param0->unk_1DA <= 0) {
                param0->unk_1D9++;
                param0->unk_1DC = (FX32_CONST(51));
            }
            break;
        case 2:
            if ((param0->unk_1DC + (FX32_CONST(1.0))) < (FX32_CONST(100))) {
                param0->unk_1DC += (FX32_CONST(1.0));
            } else {
                param0->unk_1DC = (FX32_CONST(51));
            }
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }

        Easy3DAnim_SetFrame(&param0->unk_198[1], param0->unk_1DC);
        Easy3DAnim_SetFrame(&param0->unk_198[2], param0->unk_1DC);
    }

    for (v0 = 0; v0 < 3; v0++) {
        Easy3DObject_Draw(&param0->unk_00[v0]);
    }
}

static void WiFiLobbyMinigameBucket_StartBucketFill(WiFiLobbyMinigameBucketBucketModel *param0)
{
    Easy3DObject_SetVisible(&param0->unk_00[0], 0);
    Easy3DObject_SetVisible(&param0->unk_00[1], 1);

    param0->unk_1DC = 0;
    param0->unk_1E0 = (FX32_CONST(1.0));
    param0->unk_1D8 = 1;
    param0->unk_1D9 = 0;
}

static void WiFiLobbyMinigameBucket_SetBucketAnimSpeed(WiFiLobbyMinigameBucketBucketModel *param0, fx32 param1)
{
    param0->unk_1D4 = param1;
}

static void WiFiLobbyMinigameBucket_RayIntersect(const VecFx32 *param0, const VecFx32 *param1, const VecFx32 *param2, fx32 param3, VecFx32 *param4, fx32 *param5)
{
    fx32 v0;
    fx32 v1;
    fx32 v2;

    v1 = FX_Mul(param2->x, param1->x) + FX_Mul(param2->y, param1->y) + FX_Mul(param2->z, param1->z);
    v2 = -FX_Mul(param2->x, param0->x) - FX_Mul(param2->y, param0->y) - FX_Mul(param2->z, param0->z);
    v0 = FX_Div(v2 + param3, v1);

    param4->x = param0->x + FX_Mul(param1->x, v0);
    param4->y = param0->y + FX_Mul(param1->y, v0);
    param4->x = param0->z + FX_Mul(param1->z, v0);

    *param5 = v0;
}

static void WiFiLobbyMinigameBucket_SetCameraTargetHeight(WiFiLobbyMinigameBucketScene *param0, fx32 param1)
{
    param0->unk_1F8.y = param1;
}

static void WiFiLobbyMinigameBucket_SetCameraAngle(WiFiLobbyMinigameBucketScene *param0, u16 param1)
{
    CameraAngle v0;

    v0 = Camera_GetAngle(param0->camera);
    v0.x = param1;

    Camera_SetAngleAroundTarget(&v0, param0->camera);
}

static void WiFiLobbyMinigameBucket_InitBgFade(WiFiLobbyMinigameBucketBgFade *param0, u8 param1)
{
    memset(param0, 0, sizeof(WiFiLobbyMinigameBucketBgFade));
    param0->unk_04 = 2;
    param0->unk_06 = param1;
}

static void WiFiLobbyMinigameBucket_UpdateBgFade(WiFiLobbyMinigameBucketBgFade *param0, WiFiLobbyMinigameBucketScene *param1)
{
    switch (param0->unk_00) {
    case 0:
        break;
    case 1:
        WiFiLobbyMinigameBucket_SetBgRotation(param1, param0->unk_04 - 1, param0->unk_06);
        param0->unk_00++;
        param0->unk_02 = 0;
    case 2:
        if (param0->unk_02 >= 16) {
            param0->unk_00 = 3;
            param0->unk_02 = 0;
            WiFiLobbyMinigameBucket_SetBgRotation(param1, param0->unk_04, param0->unk_06);
            G2S_SetBlendAlpha(1 << param0->unk_04, GX_BLEND_PLANEMASK_BG3, 0, 16);
        } else {
            param0->unk_02++;

            {
                s32 v0, v1, v2;
                s32 v3;

                v0 = param0->unk_04;
                v1 = param0->unk_04 - 2;
                v2 = param0->unk_04 - 1;

                if (v0 < 0) {
                    v0 += 3;
                }

                if (v1 < 0) {
                    v1 += 3;
                }

                if (v2 < 0) {
                    v2 += 3;
                }

                v3 = 16 - ((param0->unk_02 * 16) / 16);
                G2S_SetBlendAlpha(1 << v0, (1 << v1) | (1 << v2) | GX_BLEND_PLANEMASK_BG3, v3, 16 - v3);
            }
        }
        break;
    case 3:
        if (param0->unk_02 >= 8) {
            param0->unk_00 = 0;
            G2S_BlendNone();
        } else {
            param0->unk_02++;
            {
                s32 v4;

                v4 = (param0->unk_02 * 16) / 8;
                G2S_SetBlendAlpha(1 << param0->unk_04, GX_BLEND_PLANEMASK_BG3, v4, 16 - v4);
            }
        }
        break;
    }
}

static void WiFiLobbyMinigameBucket_AdvanceBgFade(WiFiLobbyMinigameBucketBgFade *param0)
{
    param0->unk_07++;

    if (param0->unk_07 >= 10) {
        param0->unk_00 = 1;
        param0->unk_04 = (param0->unk_04 + 1) % 3;
        param0->unk_07 = 0;
    }
}

static void WiFiLobbyMinigameBucket_SetBgRotation(WiFiLobbyMinigameBucketScene *param0, s16 param1, u16 param2)
{
    int v0;
    s32 v1;

    for (v0 = 0; v0 < 3; v0++) {
        v1 = param1 - v0;

        if (v1 < 0) {
            v1 += 3;
        }

        v1 += 4;

        Bg_SetPriority(v1, 2 - v0);

        if (v0 == 0) {
            Bg_ChangeTilemapRectPalette(param0->unk_00, v1, 0, 0, 32, 32, 2 + (param2 * 2));
        } else {
            Bg_ChangeTilemapRectPalette(param0->unk_00, v1, 0, 0, 32, 32, 1 + (param2 * 2));
        }

        Bg_CopyTilemapBufferToVRAM(param0->unk_00, v1);
    }
}

static void WiFiLobbyMinigameBucket_InitScoreDisplay(WiFiLobbyMinigameBucketScoreDisplay *param0, WiFiLobbyMinigameBucketScene *param1, NARC *param2, u32 heapID)
{
    param0->heapID = heapID;

    {
        BOOL v0;

        param0->unk_00[0] = SpriteResourceCollection_AddTilesFrom(param1->unk_1AC[0], param2, 10, 0, 140, NNS_G2D_VRAM_TYPE_2DMAIN, heapID);
        param0->unk_00[1] = SpriteResourceCollection_AddPaletteFrom(param1->unk_1AC[1], param2, 11, 0, 140, NNS_G2D_VRAM_TYPE_2DMAIN, 1, heapID);
        param0->unk_00[2] = SpriteResourceCollection_AddFrom(param1->unk_1AC[2], param2, 9, 0, 140, 2, heapID);
        param0->unk_00[3] = SpriteResourceCollection_AddFrom(param1->unk_1AC[3], param2, 8, 0, 140, 3, heapID);

        v0 = SpriteTransfer_RequestCharAtEndWithHardwareMappingType(param0->unk_00[0]);
        GF_ASSERT(v0);
        v0 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_00[1]);
        GF_ASSERT(v0);

        SpriteResource_ReleaseData(param0->unk_00[0]);
        SpriteResource_ReleaseData(param0->unk_00[1]);
        SpriteResourcesHeader_Init(&param0->unk_10, 140, 140, 140, 140, 0xffffffff, 0xffffffff, 0, 0, param1->unk_1AC[0], param1->unk_1AC[1], param1->unk_1AC[2], param1->unk_1AC[3], NULL, NULL);
    }

    {
        SpriteListTemplate v1;

        v1.list = param1->unk_1C;
        v1.resourceData = &param0->unk_10;
        v1.position.x = (-FX32_CONST(64));
        v1.position.y = (FX32_CONST(48));
        v1.priority = (0 + 1);
        v1.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
        v1.heapID = heapID;

        param0->unk_34 = SpriteList_Add(&v1);
        Sprite_SetDrawFlag(param0->unk_34, FALSE);
    }

    {
        int v2;
        BOOL v3;
        UnkStruct_020127E8 v4;

        param0->unk_5C = String_Init(16, heapID);
        Window_AddToTopLeftCorner(param1->unk_00, &param0->unk_38, 3, 2, 0, 0);
        param0->unk_4C = FontOAMWindow_New(&param0->unk_38, heapID);

        v2 = FontOAMWindow_GetSize(param0->unk_4C, NNS_G2D_VRAM_TYPE_2DMAIN);
        v3 = CharTransfer_AllocRange(v2, 1, NNS_G2D_VRAM_TYPE_2DMAIN, &param0->unk_50);
        GF_ASSERT(v3 == 1);

        param0->unk_60 = SpriteResourceCollection_AddPalette(param1->unk_1AC[1], 14, 6, 0, 150, NNS_G2D_VRAM_TYPE_2DMAIN, 1, heapID);
        v3 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_60);
        GF_ASSERT(v3);

        SpriteResource_ReleaseData(param0->unk_60);

        v4.unk_00 = param1->unk_1F0;
        v4.unk_04 = &param0->unk_38;
        v4.unk_08 = param1->unk_1C;
        v4.unk_0C = SpriteTransfer_GetPaletteProxy(param0->unk_60, NULL);
        v4.unk_10 = param0->unk_34;
        v4.unk_14 = param0->unk_50.offset;
        v4.unk_18 = -7;
        v4.unk_1C = -5;
        v4.unk_20 = 0;
        v4.unk_24 = 0;
        v4.unk_28 = NNS_G2D_VRAM_TYPE_2DMAIN;
        v4.heapID = heapID;

        param0->unk_48 = FontOAM_NewFromWindow(&v4, param0->unk_4C);

        FontOAM_SetDrawFlag(param0->unk_48, 0);
        Window_Remove(&param0->unk_38);
    }

    WiFiLobbyMinigameBucket_InitMotion(&param0->unk_64, -FX32_CONST(64), FX32_CONST(32), FX32_CONST(36), 8);
    WiFiLobbyMinigameBucket_InitMotion(&param0->unk_7C, FX32_CONST(48), FX32_CONST(48), FX32_CONST(12), 4);

    param0->unk_94 = 0;
    param0->unk_96 = 4;
}

static void WiFiLobbyMinigameBucket_FreeScoreDisplay(WiFiLobbyMinigameBucketScoreDisplay *param0, WiFiLobbyMinigameBucketScene *param1)
{
    {
        FontOAM_Delete(param0->unk_48);
        SpriteTransfer_ResetPlttTransfer(param0->unk_60);
        SpriteResourceCollection_Remove(param1->unk_1AC[1], param0->unk_60);
        CharTransfer_ClearRange(&param0->unk_50);
        FontOAMWindow_Free(param0->unk_4C);
        String_Free(param0->unk_5C);
    }

    Sprite_Delete(param0->unk_34);

    {
        SpriteTransfer_ResetCharTransfer(param0->unk_00[0]);
        SpriteTransfer_ResetPlttTransfer(param0->unk_00[1]);
        SpriteResourceCollection_Remove(param1->unk_1AC[0], param0->unk_00[0]);
        SpriteResourceCollection_Remove(param1->unk_1AC[1], param0->unk_00[1]);
        SpriteResourceCollection_Remove(param1->unk_1AC[2], param0->unk_00[2]);
        SpriteResourceCollection_Remove(param1->unk_1AC[3], param0->unk_00[3]);
    }
}

static void WiFiLobbyMinigameBucket_ShowScore(WiFiLobbyMinigameBucketScoreDisplay *param0, WiFiLobbyMinigameBucketScene *param1, u32 param2)
{
    {
        String_FormatInt(param0->unk_5C, param2, 2, 2, 1);
        Window_AddToTopLeftCorner(param1->unk_00, &param0->unk_38, 3, 2, 0, 0);
        Text_AddPrinterWithParamsAndColor(&param0->unk_38, FONT_SYSTEM, param0->unk_5C, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
        FontOAMWindow_UploadToVRAM(param0->unk_48, param0->unk_4C, &param0->unk_38, param0->heapID);
        Window_Remove(&param0->unk_38);
    }

    FontOAM_SetDrawFlag(param0->unk_48, 1);
    Sprite_SetDrawFlag(param0->unk_34, TRUE);

    param0->unk_98 = 1;
    param0->unk_9A = 0;
}

static void WiFiLobbyMinigameBucket_HideScore(WiFiLobbyMinigameBucketScoreDisplay *param0)
{
    if (param0->unk_98 != 3) {
        if (param0->unk_98 == 2) {
            param0->unk_9A = 12;
        }

        param0->unk_98 = 3;
    }
}

static void WiFiLobbyMinigameBucket_UpdateScore(WiFiLobbyMinigameBucketScoreDisplay *param0, WiFiLobbyMinigameBucketScene *param1, u32 param2)
{
    if (param0->unk_98 != 3) {
        {
            String_FormatInt(param0->unk_5C, param2, 2, 2, 1);
            Window_AddToTopLeftCorner(param1->unk_00, &param0->unk_38, 3, 2, 0, 0);
            Text_AddPrinterWithParamsAndColor(&param0->unk_38, FONT_SYSTEM, param0->unk_5C, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
            FontOAMWindow_UploadToVRAM(param0->unk_48, param0->unk_4C, &param0->unk_38, param0->heapID);
            Window_Remove(&param0->unk_38);
        }

        param0->unk_96 = 0;
    }
}

static void WiFiLobbyMinigameBucket_UpdateScoreDisplay(WiFiLobbyMinigameBucketScoreDisplay *param0)
{
    switch (param0->unk_98) {
    case 0:
        break;
    case 1:
        if (param0->unk_94 < 8) {
            param0->unk_94++;
        } else {
            param0->unk_98 = 2;
        }
        break;
    case 2:
        break;
    case 3:
        if (param0->unk_9A > 0) {
            param0->unk_9A--;
            break;
        }

        if (param0->unk_94 > 0) {
            param0->unk_94--;
        } else {
            param0->unk_98 = 0;
            FontOAM_SetDrawFlag(param0->unk_48, 0);
            Sprite_SetDrawFlag(param0->unk_34, FALSE);
        }
        break;
    }

    if (param0->unk_96 < 4) {
        param0->unk_96++;
        param0->unk_7C.unk_10 = param0->unk_96;
        WiFiLobbyMinigameBucket_UpdateMotion(&param0->unk_7C);
    }

    {
        param0->unk_64.unk_10 = param0->unk_94;
        WiFiLobbyMinigameBucket_UpdateMotion(&param0->unk_64);
    }

    {
        VecFx32 v0;

        v0.x = param0->unk_64.unk_00;
        v0.y = param0->unk_7C.unk_00;

        Sprite_SetPosition(param0->unk_34, &v0);
        FontOAM_UpdatePosition(param0->unk_48);
    }
}

static void WiFiLobbyMinigameBucket_StartFinishEffect(WiFiLobbyMinigameBucketFinishEffect *param0)
{
    param0->unk_00 = 0;
    param0->unk_02 = 1;
    param0->unk_03 = 0;
    Sound_PlayEffect(SEQ_SE_PL_PINPON_sseq);
}

static void WiFiLobbyMinigameBucket_UpdateFinishEffect(WiFiLobbyMinigameBucketFinishEffect *param0, WiFiLobbyMinigameBucketBucketModel *param1, WiFiLobbyMinigameBucketSwalotModel *param2)
{
    fx32 v0;
    u32 v1;

    if (param0->unk_02 == 0) {
        return;
    }

    switch (param0->unk_00) {
    case 0:
        param0->unk_03++;

        v0 = (param0->unk_03 * (FX32_CONST(25))) / 58;
        v0 += (FX32_CONST(1));

        WiFiLobbyMinigameBucket_SetBucketAnimSpeed(param1, v0);

        v1 = (param0->unk_03 * 150) / 58;
        v1 += 256;

        Sound_SetTempoRatioForHandle(7, v1);

        if (12 == param0->unk_03) {
            Sound_PlayEffect(SEQ_SE_PL_BALLOON05_2_sseq);
        }

        if (param0->unk_03 >= 58) {
            param0->unk_00++;
        }
        break;
    case 1:
        BrightnessController_StartTransition(4, 16, 0, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, BRIGHTNESS_MAIN_SCREEN);
        param0->unk_00++;
        break;
    case 2:
        if (BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN) == TRUE) {
            WiFiLobbyMinigameBucket_StartBucketFill(param1);
            WiFiLobbyMinigameBucket_SetBucketAnimSpeed(param1, FX32_CONST(2));
            WiFiLobbyMinigameBucket_SetSwalotMouthOpen(param2, 1);
            param0->unk_00++;
        }
        break;
    case 3:
        BrightnessController_StartTransition(14, 0, 16, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, BRIGHTNESS_MAIN_SCREEN);
        param0->unk_00++;
        break;
    case 4:
        if (BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN) == TRUE) {
            param0->unk_00++;
        }
        break;
    case 5:
        param0->unk_02 = 0;
        param0->unk_00 = 0;
        break;
    }
}

static void WiFiLobbyMinigameBucket_ResetFinishEffect(WiFiLobbyMinigameBucketFinishEffect *param0)
{
    Sound_SetTempoRatioForHandle(7, 256);
}
