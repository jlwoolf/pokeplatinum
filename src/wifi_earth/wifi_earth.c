#include "wifi_earth/wifi_earth.h"

#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"
#include "constants/versions.h"

#include "struct_defs/wi_fi_history.h"

#include "overlay066/ov66_0222DDF0.h"
#include "overlay066/ov66_02231428.h"
#include "overlay066/struct_ov66_02230F50.h"
#include "overlay066/struct_ov66_02231428.h"
#include "overlay066/struct_ov66_02231560.h"
#include "wifi_earth/struct_wifi_earth_region_entry.h"
#include "overlay092/struct_ov92_021D1530.h"

#include "bg_window.h"
#include "camera.h"
#include "char_transfer.h"
#include "easy3d_object.h"
#include "font.h"
#include "g3d_pipeline.h"
#include "game_options.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "math_util.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "pltt_transfer.h"
#include "render_oam.h"
#include "render_window.h"
#include "save_player.h"
#include "savedata.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "g3_buffer.h"
#include "wifi_earth_place.h"
#include "vram_transfer.h"
#include "wifi_history_save_data.h"
#include "yes_no_touch_menu.h"

// A marker drawn on the globe. `rotation` orients the marker so that it stands
// upright on the globe's surface at (longitude, latitude). `spriteIndex` is the
// marker model to draw (3 = no marker), `country`/`region` identify the place.
typedef struct {
    s16 unk_00; // longitude
    s16 unk_02; // latitude
    MtxFx33 unk_04; // rotation
    u16 unk_28; // spriteIndex
    u16 unk_2A; // country
    u16 unk_2C; // region
} WiFiEarthPlaceMarker;

// Every place marker loaded for the globe. `unk_00` is the number of valid
// entries at the front of `unk_04`.
typedef struct {
    u32 unk_00; // count
    WiFiEarthPlaceMarker unk_04[1024];
} WiFiEarthPlaceMarkerList;

// Maps a place index to the marker sprite and animation to use.
typedef struct {
    u8 unk_00; // spriteIndex
    u8 unk_01; // animIndex
} WiFiEarthMarkerSprite;

// One keyframe of a marker's bounce animation.
typedef struct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u16 unk_0E;
} WiFiEarthMarkerAnimFrame;

// NARC members and palette used to draw one profile graphic.
typedef struct {
    u16 unk_00[2]; // screenDataMembers
    u16 unk_04; // numScreenData
    u16 unk_06; // paletteMember
    u16 unk_08; // numPaletteFrames
    u16 unk_0A; // paletteOffset
} WiFiEarthProfileGraphicParams;

typedef struct {
    u32 worldUnlocked : 1;
    u32 isJapanese : 1;
    u32 : 30;
    u32 unk_04_0 : 31; // unused
    u32 : 1;
} WiFiEarthAppFlags;

// All rendering state owned by the overlay.
typedef struct {
    BgConfig *unk_00; // bgConfig
    SpriteList *unk_04; // spriteList
    G2dRenderer unk_08; // g2dRenderer
    SpriteResourceCollection *unk_194[4]; // spriteResources
    G3DPipelineBuffers *unk_1A4; // g3dPipeline
    NARC *unk_1A8; // worldTimerNarc
} WiFiEarthGraphics;

// The globe model and its transform.
typedef struct {
    VecFx32 unk_00; // position
    VecFx32 unk_0C; // scale
    VecFx32 unk_18; // rotation (x = pitch, y = yaw, z = roll)
    Easy3DObject unk_24; // object
    Easy3DModel unk_9C; // model
} WiFiEarthGlobeObject;

// The place markers and the three marker models drawn on the globe.
typedef struct {
    WiFiEarthPlaceMarkerList unk_00; // placeMarkers
    VecFx32 unk_B804; // markerScale
    Easy3DObject unk_B810[3]; // markerObjects
    Easy3DModel unk_B978[3]; // markerModels
} WiFiEarthGlobe;

typedef struct {
    Camera *camera;
    CameraAngle unk_04; // angle
    fx32 unk_0C; // distance
    u16 unk_10; // zoomedIn
    u16 unk_12; // animating
} WiFiEarthCamera;

// A visitor profile shown on the panel: the place index and its country/region.
typedef struct {
    u32 unk_00; // placeIndex
    u32 unk_04; // country
    u32 unk_08; // region
} WiFiEarthProfile;

// A scrolling profile graphic loaded from the world-timer NARC.
typedef struct {
    u16 unk_00; // frame
    u16 unk_02; // numFrames
    u8 unk_04[4]; // visible
    void *unk_08[2]; // screenData
    NNSG2dScreenData *unk_10[2]; // screenDataPtrs
    u16 unk_18; // numScreenData
    u16 unk_1A; // currentScreenData
    void *unk_1C; // paletteData
    NNSG2dPaletteData *unk_20; // palette
    u8 unk_24; // numPaletteFrames
    u8 unk_25; // currentPaletteFrame
    u8 unk_26; // paletteOffset
    u8 unk_27; // unused
} WiFiEarthProfileGraphic;

// Per-tile animation state while a profile is revealed.
typedef struct {
    u8 unk_00; // started
    s8 unk_01; // progress
    u8 unk_02[2]; // padding
} WiFiEarthProfileTileState;

// A marker's bounce animation state.
typedef struct {
    s16 unk_00; // startX
    s16 unk_02; // startY
    s16 unk_04; // endX
    s16 unk_06; // endY
    u16 unk_08; // flagA
    u16 unk_0A; // flagB
    const WiFiEarthMarkerAnimFrame *unk_0C; // frame
} WiFiEarthMarkerAnimation;

// The twelve marker sprites and their per-animation state.
typedef struct {
    WiFiEarthMarkerAnimation unk_00[3]; // animations
    s16 unk_30; // timer
    s16 unk_32; // delay
    u8 unk_34[4]; // visible
    u8 unk_38[4]; // spriteIndex
    Sprite *unk_3C[12]; // sprites
    SpriteResource *unk_6C[12][4]; // resources
} WiFiEarthMarkerSprites;

// The two sub-screen window masks used to clip the profile panel.
typedef struct {
    s16 unk_00; // window0Active
    s16 unk_02; // window1Active
    s16 unk_04; // window0Top
    s16 unk_06; // window0Bottom
    s16 unk_08; // window1Top
    s16 unk_0A; // window1Bottom
    SysTask *unk_0C; // task
} WiFiEarthWindowMask;

// The sliding panel that lists the visitor profiles.
typedef struct {
    u32 unk_00; // state
    WiFiEarthProfile unk_04[4]; // profileHistory
    u16 unk_34; // historyStart
    u16 unk_36; // historyEnd
    u32 unk_38; // historyCount
    u16 unk_3C; // progress
    u16 unk_3E; // numTiles
    WiFiEarthProfileTileState unk_40[18]; // tileStates
    u32 unk_88[3]; // profileGraphics
    void *unk_94; // headerScreenData
    NNSG2dScreenData *unk_98; // headerScreenDataPtr
    u16 unk_9C; // unused
    u16 unk_9E; // unused
    WiFiEarthProfileGraphic unk_A0[5]; // profileGraphics
    Window unk_168[3]; // profileWindows
    Window unk_198; // headerWindow
    Window unk_1A8; // messageWindow
    WiFiEarthMarkerSprites unk_1B8; // markerSprites
    WiFiEarthWindowMask unk_2E4; // windowMask
} WiFiEarthProfilePanel;

// The on-screen EXIT banner, which also synthesises key input from touch drags.
typedef struct {
    int unk_00; // input
    int unk_04; // touchX
    int unk_08; // touchY
    int unk_0C; // state
    int unk_10; // dragX
    int unk_14; // dragY
    int unk_18; // delay
    Window unk_1C; // window
} WiFiEarthExitWindow;

// The "Exit the Visitor Profiles?" confirmation box.
typedef struct {
    u32 unk_00; // state
    u32 unk_04; // printer
    u32 unk_08; // textDelay
    String *unk_0C; // message
    Window unk_10; // window
    YesNoTouchMenu *unk_20; // yesNoMenu
} WiFiEarthConfirmWindow;

typedef struct {
    MessageLoader *unk_00; // messageLoader
    StringTemplate *unk_04; // stringTemplate
    String *unk_08; // string
    String *unk_0C; // formattedString
} WiFiEarthMessageLoader;

// State shared by every screen of the overlay.
typedef struct {
    u16 unk_00; // state
    u16 unk_02; // subState
    WiFiEarthAppFlags unk_04; // flags
    WiFiHistory *wiFiHistory;
    Options *options;
    int unk_14; // country
    int unk_18; // region
    UnkStruct_ov66_02231428 unk_1C; // localTime
    WiFiEarthGraphics unk_20; // graphics
    WiFiEarthMessageLoader unk_1CC; // messageLoader
    WiFiEarthGlobeObject unk_1DC; // globeObject
    WiFiEarthGlobe unk_288; // globe
    WiFiEarthCamera unk_BC30; // camera
    WiFiEarthExitWindow unk_BC44; // exitWindow
    WiFiEarthProfilePanel unk_BC70; // profilePanel
    WiFiEarthConfirmWindow unk_BF64; // confirmWindow
} WiFiEarthAppData;

static void WiFiEarth_AddPlaceMarker(WiFiEarthGlobe *param0, u32 param1, s16 param2, s16 param3, u16 param4, u16 param5, const UnkStruct_ov66_02231560 *param6);
static void WiFiEarth_BuildRotationMatrix(MtxFx33 *param0, const VecFx32 *param1);
static void WiFiEarth_BuildMarkerRotationMatrix(MtxFx33 *param0, const VecFx32 *param1);
static void WiFiEarth_CalcTouchDrag(int param0, int param1, int *param2, int *param3, int *param4, int *param5);
static u32 WiFiEarth_ProcessGlobeInput(WiFiEarthAppData *param0, int param1, int param2);
static void WiFiEarth_WrapAngle(VecFx32 *param0);
static BOOL WiFiEarth_UpdateState(WiFiEarthAppData *param0);
static void WiFiEarth_UpdateProfilePanelState(WiFiEarthAppData *param0);
static void WiFiEarth_DrawFrame(WiFiEarthAppData *param0);
static void WiFiEarth_VBlankCallback(void *param0);
static u32 WiFiEarth_ProcessInput(WiFiEarthAppData *param0);
static void WiFiEarth_SelectInitialMarker(WiFiEarthAppData *param0, const UnkStruct_ov66_02230F50 *param1);
static BOOL WiFiEarth_GetMarkerUnderCursor(const WiFiEarthAppData *param0, WiFiEarthProfile *param1);
static u32 WiFiEarth_FindNearestMarker(const WiFiEarthAppData *param0);
static u32 WiFiEarth_AngleDistance(const VecFx32 *param0, const VecFx32 *param1);
static u32 WiFiEarth_CalcLocalTime(const WiFiEarthAppData *param0, u32 param1, UnkStruct_ov66_02231428 param2);
static BOOL WiFiEarth_MoveCameraToPlace(WiFiEarthAppData *param0, u8 param1, u8 param2);
static void WiFiEarth_InitWorldUnlock(WiFiEarthAppData *param0, const UnkStruct_ov66_02230F50 *param1);
static void WiFiEarth_InitGraphics(WiFiEarthGraphics *param0, Options *options, u32 heapID);
static void WiFiEarth_FreeGraphics(WiFiEarthGraphics *param0);
static void WiFiEarth_UpdateSprites(WiFiEarthGraphics *param0);
static void WiFiEarth_ProcessVBlank(WiFiEarthGraphics *param0);
static void WiFiEarth_InitBackgrounds(WiFiEarthGraphics *param0, Options *options, u32 param2);
static void WiFiEarth_FreeBackgrounds(WiFiEarthGraphics *param0);
static void WiFiEarth_InitSpriteSystem(WiFiEarthGraphics *param0, u32 heapID);
static void WiFiEarth_FreeSpriteSystem(WiFiEarthGraphics *param0);
static void WiFiEarth_Init3D(WiFiEarthGraphics *param0, u32 heapID);
static void WiFiEarth_Free3D(WiFiEarthGraphics *param0);
static void WiFiEarth_Setup3D(void);
static void WiFiEarth_InitGlobe(WiFiEarthGlobeObject *param0, WiFiEarthGraphics *param1, u32 heapID);
static void WiFiEarth_FreeGlobe(WiFiEarthGlobeObject *param0);
static void WiFiEarth_DrawGlobe(WiFiEarthGlobeObject *param0);
static void WiFiEarth_GetGlobePosition(const WiFiEarthGlobeObject *param0, VecFx32 *param1);
static void WiFiEarth_GetGlobeRotationMatrix(const WiFiEarthGlobeObject *param0, MtxFx33 *param1);
static void WiFiEarth_GetGlobeRotation(const WiFiEarthGlobeObject *param0, VecFx32 *param1);
static void WiFiEarth_SetGlobeRotation(WiFiEarthGlobeObject *param0, const VecFx32 *param1);
static void WiFiEarth_InitPlaceMarkers(WiFiEarthGlobe *param0, const UnkStruct_ov66_02231560 *param1, WiFiEarthGraphics *param2, WiFiEarthAppFlags param3, u32 heapID);
static void WiFiEarth_FreePlaceMarkers(WiFiEarthGlobe *param0);
static void WiFiEarth_DrawPlaceMarkers(WiFiEarthGlobe *param0, const WiFiEarthGlobeObject *param1);
static u32 WiFiEarth_GetPlaceStatus(const UnkStruct_ov66_02231560 *param0, u16 param1, u16 param2);
static u32 WiFiEarth_FindMarkerByPlace(const WiFiEarthGlobe *param0, u16 param1, u16 param2, VecFx32 *param3);
static u32 WiFiEarth_GetMarkerIndex(const WiFiEarthGlobe *param0, u16 param1, u16 param2);
static void WiFiEarth_GetMarkerPosition(const WiFiEarthGlobe *param0, VecFx32 *param1, int param2);
static u32 WiFiEarth_GetMarkerStatus(const WiFiEarthGlobe *param0, int param1);
static u32 WiFiEarth_GetMarkerCountry(const WiFiEarthGlobe *param0, int param1);
static u32 WiFiEarth_GetMarkerRegion(const WiFiEarthGlobe *param0, int param1);
static u32 WiFiEarth_GetMarkerCount(const WiFiEarthGlobe *param0);
static void WiFiEarth_InitCamera(WiFiEarthCamera *param0, WiFiEarthAppFlags param1, enum HeapID param2);
static void WiFiEarth_FreeCamera(WiFiEarthCamera *param0);
static void WiFiEarth_UpdateCamera(const WiFiEarthCamera *param0);
static void WiFiEarth_ToggleZoom(WiFiEarthCamera *param0);
static BOOL WiFiEarth_UpdateZoom(WiFiEarthCamera *param0, WiFiEarthGlobe *param1);
static u32 WiFiEarth_IsZoomedIn(const WiFiEarthCamera *param0);
static void WiFiEarth_InitExitWindow(WiFiEarthExitWindow *param0, WiFiEarthGraphics *param1, WiFiEarthMessageLoader *param2, u32 heapID);
static void WiFiEarth_FreeExitWindow(WiFiEarthExitWindow *param0);
static void WiFiEarth_ProcessExitWindowInput(WiFiEarthExitWindow *param0);
static int WiFiEarth_GetExitWindowInput(const WiFiEarthExitWindow *param0, u32 param1);
static void WiFiEarth_ShowExitWindow(WiFiEarthExitWindow *param0);
static void WiFiEarth_HideExitWindow(WiFiEarthExitWindow *param0);
static void WiFiEarth_InitConfirmWindow(WiFiEarthConfirmWindow *param0, WiFiEarthGraphics *param1, WiFiEarthMessageLoader *param2, SaveData *saveData, u32 heapID);
static void WiFiEarth_FreeConfirmWindow(WiFiEarthConfirmWindow *param0);
static void WiFiEarth_ShowConfirmWindow(WiFiEarthConfirmWindow *param0);
static u32 WiFiEarth_ProcessConfirmInput(WiFiEarthConfirmWindow *param0);
static void WiFiEarth_HideConfirmWindow(WiFiEarthConfirmWindow *param0);
static void WiFiEarth_InitProfilePanel(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1, WiFiEarthMessageLoader *param2, enum HeapID heapID);
static void WiFiEarth_FreeProfilePanel(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1);
static void WiFiEarth_UpdateProfilePanel(WiFiEarthProfilePanel *param0, WiFiEarthMessageLoader *param1, WiFiEarthGraphics *param2);
static void WiFiEarth_HideProfilePanel(WiFiEarthProfilePanel *param0);
static void WiFiEarth_ShowProfilePanel(WiFiEarthProfilePanel *param0);
static BOOL WiFiEarth_PushProfile(WiFiEarthProfilePanel *param0, const WiFiEarthProfile *param1);
static BOOL WiFiEarth_ProfileExists(const WiFiEarthProfilePanel *param0, const WiFiEarthProfile *param1);
static void WiFiEarth_ResetProfileHistory(WiFiEarthProfilePanel *param0);
static void WiFiEarth_ClearProfileHistory(WiFiEarthProfilePanel *param0);
static void WiFiEarth_AddProfileToHistory(WiFiEarthProfilePanel *param0, const WiFiEarthProfile *param1);
static void WiFiEarth_PopProfileHistory(WiFiEarthProfilePanel *param0);
static BOOL WiFiEarth_GetProfileFromHistory(const WiFiEarthProfilePanel *param0, WiFiEarthProfile *param1, u32 param2);
static void WiFiEarth_UpdateProfileSprites(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1);
static void WiFiEarth_ShowProfiles(WiFiEarthProfilePanel *param0, WiFiEarthMessageLoader *param1, WiFiEarthGraphics *param2);
static BOOL WiFiEarth_AnimateProfilesSlow(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1);
static void WiFiEarth_HalveProfileProgress(WiFiEarthProfilePanel *param0);
static BOOL WiFiEarth_AnimateProfilesFast(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1);
static BOOL WiFiEarth_AnimateProfileProgress(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1, int param2);
static void WiFiEarth_StartProfileTile(WiFiEarthProfilePanel *param0, u32 param1);
static BOOL WiFiEarth_UpdateProfileTile(WiFiEarthProfilePanel *param0, u32 param1, WiFiEarthGraphics *param2);
static void WiFiEarth_CopyProfileTilemap(WiFiEarthProfilePanel *param0, u32 param1, WiFiEarthGraphics *param2);
static void WiFiEarth_InitWindowMask(WiFiEarthWindowMask *param0);
static void WiFiEarth_FreeWindowMask(WiFiEarthWindowMask *param0);
static void WiFiEarth_SetWindow0(WiFiEarthWindowMask *param0, s16 param1, s16 param2);
static void WiFiEarth_SetWindow1(WiFiEarthWindowMask *param0, s16 param1, s16 param2);
static void WiFiEarth_ApplyWindowMask(SysTask *param0, void *param1);
static void WiFiEarth_InitProfileWindows(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1, u32 param2);
static void WiFiEarth_FreeProfileWindows(WiFiEarthProfilePanel *param0);
static void WiFiEarth_PrintProfile(WiFiEarthProfilePanel *param0, u32 param1, const WiFiEarthProfile *param2, WiFiEarthMessageLoader *param3);
static u8 *WiFiEarth_GetProfileTilePixels(WiFiEarthProfilePanel *param0, u32 param1, u32 param2);
static u8 *WiFiEarth_GetProfileHeaderPixels(WiFiEarthProfilePanel *param0, u32 param1);
static void WiFiEarth_TransferProfileTile(WiFiEarthProfilePanel *param0, u32 param1, u32 param2, const u8 *param3);
static void WiFiEarth_InitProfileGraphic(WiFiEarthProfileGraphic *param0, WiFiEarthGraphics *param1, const WiFiEarthProfileGraphicParams *param2, u16 param3, enum HeapID heapID);
static void WiFiEarth_FreeProfileGraphic(WiFiEarthProfileGraphic *param0);
static void WiFiEarth_UpdateProfileGraphic(WiFiEarthProfileGraphic *param0, WiFiEarthGraphics *param1);
static void WiFiEarth_SetProfileGraphicVisible(WiFiEarthProfileGraphic *param0, u32 param1, BOOL param2);
static void WiFiEarth_ClearProfileGraphicVisible(WiFiEarthProfileGraphic *param0);
static void WiFiEarth_DrawProfileGraphic(WiFiEarthProfileGraphic *param0, u32 param1, WiFiEarthGraphics *param2);
static void WiFiEarth_InitMarkerSprites(WiFiEarthMarkerSprites *param0, WiFiEarthGraphics *param1, WiFiEarthWindowMask *param2, u32 param3);
static void WiFiEarth_FreeMarkerSprites(WiFiEarthMarkerSprites *param0, WiFiEarthGraphics *param1);
static void WiFiEarth_ResetMarkerSprites(WiFiEarthMarkerSprites *param0);
static void WiFiEarth_ShowMarkerSprite(WiFiEarthMarkerSprites *param0, u8 param1, u8 param2, u8 param3);
static void WiFiEarth_HideMarkerSprites(WiFiEarthMarkerSprites *param0);
static void WiFiEarth_UpdateMarkerSprites(WiFiEarthMarkerSprites *param0, WiFiEarthWindowMask *param1);
static BOOL WiFiEarth_ShowMarkerSpriteByIndex(WiFiEarthMarkerSprites *param0, u32 param1, WiFiEarthWindowMask *param2);
static BOOL WiFiEarth_HideMarkerSpriteByIndex(WiFiEarthMarkerSprites *param0, u32 param1, WiFiEarthWindowMask *param2);
static void WiFiEarth_InitMarkerAnimation(WiFiEarthMarkerAnimation *param0, const WiFiEarthMarkerAnimFrame *param1);
static void WiFiEarth_SetMarkerAnimFlagA(WiFiEarthMarkerAnimation *param0, BOOL param1);
static void WiFiEarth_SetMarkerAnimFlagB(WiFiEarthMarkerAnimation *param0, BOOL param1);
static BOOL WiFiEarth_UpdateMarkerAnimation(WiFiEarthMarkerAnimation *param0, WiFiEarthWindowMask *param1);
static void WiFiEarth_RestartMarkerAnimation(WiFiEarthMarkerAnimation *param0, WiFiEarthWindowMask *param1);
static void WiFiEarth_GetMarkerSpritePosition(const WiFiEarthMarkerAnimation *param0, VecFx32 *param1);
static void WiFiEarth_UpdateMarkerPosition(WiFiEarthMarkerAnimation *param0);
static void WiFiEarth_UpdateMarkerWindowMask(const WiFiEarthMarkerAnimation *param0, WiFiEarthWindowMask *param1);
static void WiFiEarth_SetMarkerSpritePosition(WiFiEarthMarkerSprites *param0, u32 param1);
static u16 WiFiEarth_GetMarkerSpriteIndex(u32 param0);
static u16 WiFiEarth_GetMarkerSpriteAnim(u32 param0);
static void WiFiEarth_InitMessageLoader(WiFiEarthMessageLoader *param0, u32 heapID);
static void WiFiEarth_FreeMessageLoader(WiFiEarthMessageLoader *param0);
static String *WiFiEarth_GetMessage(WiFiEarthMessageLoader *param0, u32 param1);
static String *WiFiEarth_FormatCountryName(WiFiEarthMessageLoader *param0, u32 param1);
static String *WiFiEarth_FormatCityName(WiFiEarthMessageLoader *param0, u32 param1, u32 param2);
static void WiFiEarth_GetMessageInto(WiFiEarthMessageLoader *param0, u32 param1, String *param2);
static u32 WiFiEarth_GetPlayerCountryIndex(const UnkStruct_ov66_02231560 *param0);

static const u32 sGlobeModelMembers[3] = {
    0x0,
    0x1,
    0x2
};

static const GXBanks sGxBanks = {
    GX_VRAM_BG_16_F,
    GX_VRAM_BGEXTPLTT_NONE,
    GX_VRAM_SUB_BG_128_C,
    GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_16_G,
    GX_VRAM_OBJEXTPLTT_NONE,
    GX_VRAM_SUB_OBJ_16_I,
    GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_01_AB,
    GX_VRAM_TEXPLTT_0123_E
};

static const GraphicsModes sGraphicsModes = {
    GX_DISPMODE_GRAPHICS,
    GX_BGMODE_0,
    GX_BGMODE_0,
    GX_BG0_AS_3D
};

static const u32 sBgLayers[5] = {
    0x1,
    0x6,
    0x7,
    0x4,
    0x5
};

static const BgTemplate sBgTemplates[5] = {
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0x3800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xd000,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x2,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe000,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x3,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe800,
        .charBase = GX_BG_CHARBASE_0x10000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xd800,
        .charBase = GX_BG_CHARBASE_0x10000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x1,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
};

static const CharTransferTemplate sCharTransferTemplate = {
    0x20,
    0x4000,
    0x4000,
    0x69
};

static const VecFx32 sCameraTarget = {
    0x0,
    0x0,
    0x0
};

static const VecFx32 sCameraPosition = {
    0x0,
    0x0,
    0x128000
};

static const WiFiEarthMarkerSprite sMarkerSpriteTable[24] = {
    { 0x0, 0x0 },
    { 0x0, 0x0 },
    { 0x0, 0x1 },
    { 0x0, 0x1 },
    { 0x0, 0x2 },
    { 0x0, 0x2 },
    { 0x1, 0x3 },
    { 0x1, 0x3 },
    { 0x1, 0x4 },
    { 0x1, 0x4 },
    { 0x1, 0x5 },
    { 0x1, 0x5 },
    { 0x2, 0x6 },
    { 0x2, 0x6 },
    { 0x2, 0x7 },
    { 0x2, 0x7 },
    { 0x3, 0x8 },
    { 0x3, 0x8 },
    { 0x3, 0x9 },
    { 0x3, 0x9 },
    { 0x4, 0xA },
    { 0x4, 0xA },
    { 0x4, 0xB },
    { 0x4, 0xB },
};

static const u8 sProfileGraphicFrames[5] = {
    0x1E,
    0x1E,
    0x1E,
    0x1E,
    0x1E,
};

static const TextColor sProfileTextColors[5] = {
    TEXT_COLOR(5, 6, 0),
    TEXT_COLOR(7, 8, 0),
    TEXT_COLOR(9, 10, 0),
    TEXT_COLOR(11, 12, 0),
    TEXT_COLOR(11, 12, 0),
};

static const WiFiEarthMarkerAnimFrame sMarkerAnimFrames[12][3] = {
    {
        { 0xA0, 0x30, 0xBE, 0x0, 0x13F, 0x8, 0x50 },
        { 0xCE, 0x60, 0xA0, 0x30, 0x13F, 0x8, 0x50 },
        { 0x96, 0x90, 0xCE, 0x60, 0x13F, 0x8, 0x50 },
    },
    {
        { 0xBE, 0x30, 0x8C, 0x0, 0xDC, 0xC, 0x36 },
        { 0x96, 0x60, 0xBE, 0x30, 0xDC, 0xC, 0x36 },
        { 0xC8, 0x90, 0x96, 0x60, 0xDC, 0xC, 0x36 },
    },
    {
        { 0x80, 0x30, 0xA0, 0x0, 0xDC, 0xC, 0x36 },
        { 0xD2, 0x60, 0x80, 0x30, 0xDC, 0xC, 0x36 },
        { 0xA0, 0x90, 0xD2, 0x60, 0xDC, 0xC, 0x36 },
    },
    {
        { 0xB4, 0x30, 0x8A, 0x0, 0xDC, 0xC, 0x36 },
        { 0x8A, 0x60, 0xB4, 0x30, 0xDC, 0xC, 0x36 },
        { 0xB4, 0x90, 0x8A, 0x60, 0xDC, 0xC, 0x36 },
    },
    {
        { 0xB4, 0x30, 0xA0, 0x0, 0x18F, 0x4, 0x64 },
        { 0x82, 0x60, 0xB4, 0x30, 0x18F, 0x4, 0x64 },
        { 0x80, 0x90, 0x82, 0x60, 0x18F, 0x4, 0x64 },
    },
    {
        { 0xB4, 0x30, 0x74, 0x0, 0x13F, 0x8, 0x50 },
        { 0x74, 0x60, 0xB4, 0x30, 0x13F, 0x8, 0x50 },
        { 0xB4, 0x90, 0x74, 0x60, 0x13F, 0x8, 0x50 },
    },
    {
        { 0xB4, 0x30, 0xF0, 0x0, 0xDC, 0xC, 0x36 },
        { 0xA0, 0x60, 0xB4, 0x30, 0xDC, 0xC, 0x36 },
        { 0x60, 0x90, 0xA0, 0x60, 0xDC, 0xC, 0x36 },
    },
    {
        { 0x90, 0x30, 0xDA, 0x0, 0xDC, 0xC, 0x36 },
        { 0xDA, 0x60, 0x90, 0x30, 0xDC, 0xC, 0x36 },
        { 0x90, 0x90, 0xDA, 0x60, 0xDC, 0xC, 0x36 },
    },
    {
        { 0xA0, 0x30, 0xC0, 0x0, 0x18F, 0x4, 0x64 },
        { 0xC0, 0x60, 0xA0, 0x30, 0x18F, 0x4, 0x64 },
        { 0xA0, 0x90, 0xC0, 0x60, 0x18F, 0x4, 0x64 },
    },
    {
        { 0x8C, 0x30, 0x60, 0x0, 0x13F, 0x8, 0x50 },
        { 0xBE, 0x60, 0x8C, 0x30, 0x13F, 0x8, 0x50 },
        { 0xF0, 0x90, 0xBE, 0x60, 0x13F, 0x8, 0x50 },
    },
    {
        { 0xD4, 0x30, 0xA0, 0x0, 0x18F, 0x4, 0x64 },
        { 0xD4, 0x60, 0xD4, 0x30, 0x18F, 0x4, 0x64 },
        { 0xA0, 0x90, 0xD4, 0x60, 0x18F, 0x4, 0x64 },
    },
    {
        { 0x7B, 0x30, 0xAA, 0x0, 0x13F, 0x8, 0x50 },
        { 0xC6, 0x60, 0x7B, 0x30, 0x13F, 0x8, 0x50 },
        { 0x85, 0x90, 0xC6, 0x60, 0x13F, 0x8, 0x50 },
    },
};

static const YesNoTouchMenuParams sYesNoTouchMenuParams = {
    NULL,
    0x1,
    0xA0,
    0x3,
    0x19,
    0x6,
};

static const WiFiEarthProfileGraphicParams sProfileGraphicParams[5] = {
    {
        { 0x6 },
        0x1,
        0xD,
        0x4,
        0x0,
    },
    {
        { 0x10, 0x11 },
        0x2,
        0x0,
        0x0,
        0x1,
    },
    {
        { 0x8 },
        0x1,
        0xE,
        0x4,
        0x2,
    },
    {
        { 0x9 },
        0x1,
        0xF,
        0x10,
        0x3,
    },
    {
        { 0xA },
        0x1,
        0xF,
        0x10,
        0x3,
    },
};

int WiFiEarth_Init(ApplicationManager *appMan, int *param1)
{
    WiFiEarthAppData *v0;
    UnkStruct_ov66_02230F50 *v1 = ApplicationManager_Args(appMan);
    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_105, 0x50000);

    v0 = ApplicationManager_NewData(appMan, sizeof(WiFiEarthAppData), HEAP_ID_105);
    memset(v0, 0, sizeof(WiFiEarthAppData));

    v0->wiFiHistory = SaveData_WiFiHistory(v1->saveData);
    v0->options = SaveData_GetOptions(v1->saveData);
    v0->unk_14 = WiFiHistory_GetCountry(v0->wiFiHistory);
    v0->unk_18 = WiFiHistory_GetRegion(v0->wiFiHistory);
    v0->unk_1C = v1->unk_08;

    WiFiEarth_InitWorldUnlock(v0, v1);
    WiFiEarth_InitGraphics(&v0->unk_20, v0->options, HEAP_ID_105);
    WiFiEarth_InitGlobe(&v0->unk_1DC, &v0->unk_20, HEAP_ID_105);
    WiFiEarth_InitMessageLoader(&v0->unk_1CC, HEAP_ID_105);
    WiFiEarth_InitPlaceMarkers(&v0->unk_288, v1->unk_00, &v0->unk_20, v0->unk_04, HEAP_ID_105);
    WiFiEarth_InitCamera(&v0->unk_BC30, v0->unk_04, HEAP_ID_105);
    WiFiEarth_InitExitWindow(&v0->unk_BC44, &v0->unk_20, &v0->unk_1CC, HEAP_ID_105);
    WiFiEarth_InitConfirmWindow(&v0->unk_BF64, &v0->unk_20, &v0->unk_1CC, v1->saveData, HEAP_ID_105);
    WiFiEarth_InitProfilePanel(&v0->unk_BC70, &v0->unk_20, &v0->unk_1CC, HEAP_ID_105);
    WiFiEarth_SelectInitialMarker(v0, v1);

    SetVBlankCallback(WiFiEarth_VBlankCallback, v0);
    DisableHBlank();

    return 1;
}

int WiFiEarth_Main(ApplicationManager *appMan, int *param1)
{
    WiFiEarthAppData *v0;
    UnkStruct_ov66_02230F50 *v1;
    BOOL v2;

    v0 = ApplicationManager_Data(appMan);
    v1 = ApplicationManager_Args(appMan);

    switch (*param1) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_105);
        ov66_0222E31C(v1->unk_0C, 1);
        (*param1)++;
        break;
    case 1:
        v2 = IsScreenFadeDone();

        if (v2 == 1) {
            (*param1)++;
        }
        break;
    case 2:
        v2 = WiFiEarth_UpdateState(v0);
        WiFiEarth_UpdateProfilePanelState(v0);

        if (ov66_0222E12C(v1->unk_0C) == 1) {
            ov66_0222E2A4(v1->unk_0C);
            v2 = 1;
        }

        if (ov66_02231760() == 1) {
            v2 = 1;
        }

        if (v2 == 1) {
            (*param1) = 5;
        }
        break;
    case 5:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_105);
        (*param1)++;
        break;
    case 6:
        v2 = IsScreenFadeDone();

        if (v2 == 1) {
            return 1;
        }
        break;
    }

    WiFiEarth_DrawFrame(v0);

    return 0;
}

int WiFiEarth_Exit(ApplicationManager *appMan, int *param1)
{
    WiFiEarthAppData *v0 = ApplicationManager_Data(appMan);
    UnkStruct_ov66_02230F50 *v1 = ApplicationManager_Args(appMan);

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    WiFiEarth_FreeProfilePanel(&v0->unk_BC70, &v0->unk_20);
    WiFiEarth_FreeConfirmWindow(&v0->unk_BF64);
    WiFiEarth_FreeExitWindow(&v0->unk_BC44);
    WiFiEarth_FreeCamera(&v0->unk_BC30);
    WiFiEarth_FreeGlobe(&v0->unk_1DC);
    WiFiEarth_FreePlaceMarkers(&v0->unk_288);
    WiFiEarth_FreeMessageLoader(&v0->unk_1CC);
    WiFiEarth_FreeGraphics(&v0->unk_20);

    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_105);

    return 1;
}

static void WiFiEarth_LoadPlaceMarkers(WiFiEarthGlobe *param0, const UnkStruct_ov66_02231560 *param1, u32 heapID)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_APPLICATION__WIFI_EARTH__WIFI_EARTH_PLACE, heapID);

    param0->unk_00.unk_00 = 0;

    {
        void *v1;
        WiFiEarthPlaceEntry *v2;
        u32 v3;
        int v4, v5;

        v1 = LoadMemberFromOpenNARC_OutFileSize(v0, 18, 0, heapID, 0, &v3);
        v2 = (WiFiEarthPlaceEntry *)v1;
        v5 = v3 / 6;

        v2++;

        for (v4 = 1; v4 < v5; v4++) {
            if (v2->type != 2) {
                WiFiEarth_AddPlaceMarker(param0, param0->unk_00.unk_00, v2->longitude, v2->latitude, v4, 0, param1);
                param0->unk_00.unk_00++;
            }

            v2++;
        }

        Heap_Free(v1);
    }
    {
        void *v6;
        WiFiEarthRegionEntry *v7;
        u32 v8, v9;
        int v10, v11, v12, v13;

        v12 = 1;
        v11 = WiFiEarthPlace_GetCount();

        while (v12 < v11) {
            v9 = WiFiEarthPlace_GetNarcMemberIndex(v12);
            v6 = LoadMemberFromOpenNARC_OutFileSize(v0, v9, 0, heapID, 0, &v8);
            v7 = (WiFiEarthRegionEntry *)v6;
            v13 = v8 / 4;

            v7++;

            for (v10 = 1; v10 < v13; v10++) {
                WiFiEarth_AddPlaceMarker(param0, param0->unk_00.unk_00, v7->longitude, v7->latitude, WiFiEarthPlace_GetCountry(v12), v10, param1);
                param0->unk_00.unk_00++;
                v7++;
            }

            Heap_Free(v6);
            v12++;
        }
    }

    NARC_dtor(v0);
}

static void WiFiEarth_AddPlaceMarker(WiFiEarthGlobe *param0, u32 param1, s16 param2, s16 param3, u16 param4, u16 param5, const UnkStruct_ov66_02231560 *param6)
{
    MtxFx33 v0 = { FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0, FX32_ONE };
    VecFx32 v1;

    param0->unk_00.unk_04[param1].unk_00 = param2;
    param0->unk_00.unk_04[param1].unk_02 = param3;

    v1.x = param2;
    v1.y = param3;
    v1.z = 0;

    WiFiEarth_BuildMarkerRotationMatrix(&v0, &v1);

    param0->unk_00.unk_04[param1].unk_04 = v0;

    if (param6 != NULL) {
        param0->unk_00.unk_04[param1].unk_28 = WiFiEarth_GetPlaceStatus(param6, param4, param5);
    }

    param0->unk_00.unk_04[param1].unk_2A = param4;
    param0->unk_00.unk_04[param1].unk_2C = param5;
}

static void WiFiEarth_BuildRotationMatrix(MtxFx33 *param0, const VecFx32 *param1)
{
    MtxFx33 v0;

    MTX_RotY33(param0, FX_SinIdx((u16)param1->y), FX_CosIdx((u16)param1->y));
    MTX_RotX33(&v0, FX_SinIdx((u16)param1->x), FX_CosIdx((u16)param1->x));
    MTX_Concat33(param0, &v0, param0);
    MTX_RotZ33(&v0, FX_SinIdx((u16)param1->z), FX_CosIdx((u16)param1->z));
    MTX_Concat33(param0, &v0, param0);
}

static void WiFiEarth_BuildMarkerRotationMatrix(MtxFx33 *param0, const VecFx32 *param1)
{
    MtxFx33 v0;

    MTX_RotY33(param0, FX_SinIdx((u16)param1->x), FX_CosIdx((u16)param1->x));
    MTX_RotX33(&v0, FX_SinIdx((u16)-param1->y), FX_CosIdx((u16)-param1->y));
    MTX_Concat33(param0, &v0, param0);
    MTX_RotZ33(&v0, FX_CosIdx((u16)param1->z), FX_SinIdx((u16)param1->z));
    MTX_Concat33(param0, &v0, param0);
}

static void WiFiEarth_CalcTouchDrag(int param0, int param1, int *param2, int *param3, int *param4, int *param5)
{
    int v0 = 0;
    int v1 = 0;
    int v2 = 0;
    int v3 = 0;

    if (gSystem.touchX != 0xffff) {
        v2 = gSystem.touchX - param0;

        if (v2 < 0) {
            v2 ^= -1;
            v0 = PAD_KEY_RIGHT;
        } else {
            if (v2 > 0) {
                v0 = PAD_KEY_LEFT;
            }
        }
    }

    v2 &= 0x3f;

    *param2 = v0;
    *param3 = v2;

    if (gSystem.touchY != 0xffff) {
        v3 = gSystem.touchY - param1;

        if (v3 < 0) {
            v3 ^= -1;
            v1 = PAD_KEY_DOWN;
        } else {
            if (v3 > 0) {
                v1 = PAD_KEY_UP;
            }
        }
    }

    v3 &= 0x3f;

    *param4 = v1;
    *param5 = v3;
}

static u32 WiFiEarth_ProcessGlobeInput(WiFiEarthAppData *param0, int param1, int param2)
{
    u16 v0;
    u16 v1;
    s16 v2;
    s16 v3;
    u32 v4 = 0;
    VecFx32 v5;
    int v6;
    int v7, v8;
    u32 v9;

    WiFiEarth_GetGlobeRotation(&param0->unk_1DC, &v5);

    v6 = WiFiEarth_GetExitWindowInput(&param0->unk_BC44, 0);
    v7 = WiFiEarth_GetExitWindowInput(&param0->unk_BC44, 1);
    v8 = WiFiEarth_GetExitWindowInput(&param0->unk_BC44, 2);
    v9 = WiFiEarth_IsZoomedIn(&param0->unk_BC30);

    v2 = v5.x;
    v3 = v5.y;

    if ((param1 & PAD_BUTTON_A) || (v6 & PAD_BUTTON_A)) {
        if (param0->unk_04.worldUnlocked == 1) {
            v4 = 1;
        }

        return v4;
    }

    if (v9 == 0) {
        if ((v7) || (v8)) {
            v0 = (0x200 / 6) * v7;
            v1 = (0x200 / 6) * v8;
        } else {
            v0 = 0x200;
            v1 = 0x200;
        }
    } else {
        if ((v7) || (v8)) {
            v0 = (0x20 / 3) * v7;
            v1 = (0x20 / 3) * v8;
        } else {
            v0 = 0x20;
            v1 = 0x20;
        }
    }

    if ((param2 & PAD_KEY_LEFT) || (v6 & PAD_KEY_LEFT)) {
        if (param0->unk_04.worldUnlocked == 1) {
            v5.y += v0;
        } else {
            if (v3 < (s16)0xd820) {
                v5.y += v0;
            }
        }
    }

    if ((param2 & PAD_KEY_RIGHT) || (v6 & PAD_KEY_RIGHT)) {
        if (param0->unk_04.worldUnlocked == 1) {
            v5.y -= v0;
        } else {
            if (v3 > (s16)0xcc80) {
                v5.y -= v0;
            }
        }
    }

    if ((param2 & PAD_KEY_UP) || (v6 & PAD_KEY_UP)) {
        if (param0->unk_04.worldUnlocked == 1) {
            if ((v2 + v1) < (0x4000 - 0x200)) {
                v5.x += v1;
            } else {
                v5.x = (0x4000 - 0x200);
            }
        } else {
            if (v2 < (s16)0x2020) {
                v5.x += v1;
            }
        }
    }

    if ((param2 & PAD_KEY_DOWN) || (v6 & PAD_KEY_DOWN)) {
        if (param0->unk_04.worldUnlocked == 1) {
            if ((v2 - v1) > (-0x4000 + 0x200)) {
                v5.x -= v1;
            } else {
                v5.x = (-0x4000 + 0x200);
            }
        } else {
            if (v2 > (s16)0x1300) {
                v5.x -= v1;
            }
        }
    }

    WiFiEarth_SetGlobeRotation(&param0->unk_1DC, &v5);
    return v4;
}

static void WiFiEarth_WrapAngle(VecFx32 *param0)
{
    if (param0->x >= 0) {
        param0->x = param0->x % 0xffff;
    } else {
        param0->x = param0->x + (0xffff * ((MATH_ABS(param0->x) / 0xffff) + 1));
    }

    if (param0->y >= 0) {
        param0->y = param0->y % 0xffff;
    } else {
        param0->y = param0->y + (0xffff * ((MATH_ABS(param0->y) / 0xffff) + 1));
    }
}

static BOOL WiFiEarth_UpdateState(WiFiEarthAppData *param0)
{
    u32 v0;

    switch (param0->unk_00) {
    case 0:
        v0 = WiFiEarth_ProcessInput(param0);

        switch (v0) {
        case 0:
            break;
        case 1:
            WiFiEarth_ToggleZoom(&param0->unk_BC30);
            param0->unk_00 = 1;
            break;
        case 2:
            param0->unk_00 = 2;
            break;
        }
        break;
    case 1:
        v0 = WiFiEarth_UpdateZoom(&param0->unk_BC30, &param0->unk_288);

        if (v0 == 1) {
            param0->unk_00 = 0;
        }
        break;
    case 2:
        WiFiEarth_ShowConfirmWindow(&param0->unk_BF64);
        WiFiEarth_HideProfilePanel(&param0->unk_BC70);
        WiFiEarth_ShowExitWindow(&param0->unk_BC44);
        param0->unk_00++;
        break;
    case 3: {
        u32 v1;

        v1 = WiFiEarth_ProcessConfirmInput(&param0->unk_BF64);

        switch (v1) {
        case YES_NO_TOUCH_MENU_NOTHING_CHOSEN:
            break;
        case YES_NO_TOUCH_MENU_NO:
            WiFiEarth_ShowProfilePanel(&param0->unk_BC70);
            WiFiEarth_HideConfirmWindow(&param0->unk_BF64);
            WiFiEarth_HideExitWindow(&param0->unk_BC44);
            param0->unk_00 = 0;
            break;
        default:
        case YES_NO_TOUCH_MENU_YES:
            return 1;
        }
    } break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

static void WiFiEarth_UpdateProfilePanelState(WiFiEarthAppData *param0)
{
    switch (param0->unk_02) {
    case 0:
        WiFiEarth_UpdateProfilePanel(&param0->unk_BC70, &param0->unk_1CC, &param0->unk_20);
        break;
    }
}

static void WiFiEarth_DrawFrame(WiFiEarthAppData *param0)
{
    G3_ResetG3X();

    WiFiEarth_UpdateCamera(&param0->unk_BC30);
    WiFiEarth_DrawGlobe(&param0->unk_1DC);
    WiFiEarth_DrawPlaceMarkers(&param0->unk_288, &param0->unk_1DC);
    WiFiEarth_UpdateSprites(&param0->unk_20);

    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);
}

static void WiFiEarth_VBlankCallback(void *param0)
{
    WiFiEarthAppData *v0 = param0;
    WiFiEarth_ProcessVBlank(&v0->unk_20);
}

static u32 WiFiEarth_ProcessInput(WiFiEarthAppData *param0)
{
    u32 v0;
    BOOL v1;

    WiFiEarth_ProcessExitWindowInput(&param0->unk_BC44);

    if (param0->unk_BC44.unk_00 & PAD_BUTTON_B) {
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        return 2;
    } else {
        if (gSystem.pressedKeys & PAD_BUTTON_X) {
            {
                WiFiEarthProfile v2;

                v1 = WiFiEarth_GetMarkerUnderCursor(param0, &v2);

                if (v1 == 1) {
                    v1 = WiFiEarth_ProfileExists(&param0->unk_BC70, &v2);

                    if (v1 == 0) {
                        v1 = WiFiEarth_PushProfile(&param0->unk_BC70, &v2);

                        if (v1 == 0) {
                            (void)0;
                        } else {
                            WiFiEarth_MoveCameraToPlace(param0, v2.unk_04, v2.unk_08);
                            Sound_PlayEffect(SEQ_SE_PL_TIMER04_sseq);
                        }
                    }
                }
            }
        } else {
            v0 = WiFiEarth_ProcessGlobeInput(param0, gSystem.pressedKeys, gSystem.heldKeys);
        }
    }

    return v0;
}

static void WiFiEarth_SelectInitialMarker(WiFiEarthAppData *param0, const UnkStruct_ov66_02230F50 *param1)
{
    int v0;
    int v1;
    int v2;
    BOOL v3 = WiFiEarth_MoveCameraToPlace(param0, param0->unk_14, param0->unk_18);

    if (v3 == 0) {
        v0 = WiFiEarth_GetPlayerCountryIndex(param1->unk_00);

        if (v0 != 50) {
            v1 = ov66_022315D8(param1->unk_00, v0);
            v2 = ov66_022315FC(param1->unk_00, v0);
            v3 = WiFiEarth_MoveCameraToPlace(param0, v1, v2);

            GF_ASSERT(v3 == 1);
        } else {
            (void)0;
        }
    }
}

static BOOL WiFiEarth_GetMarkerUnderCursor(const WiFiEarthAppData *param0, WiFiEarthProfile *param1)
{
    u32 v0 = WiFiEarth_FindNearestMarker(param0);

    if (v0 >= WiFiEarth_GetMarkerCount(&param0->unk_288)) {
        return 0;
    }

    param1->unk_00 = WiFiEarth_CalcLocalTime(param0, v0, param0->unk_1C);
    param1->unk_04 = WiFiEarth_GetMarkerCountry(&param0->unk_288, v0);
    param1->unk_08 = WiFiEarth_GetMarkerRegion(&param0->unk_288, v0);

    return 1;
}

static u32 WiFiEarth_FindNearestMarker(const WiFiEarthAppData *param0)
{
    int v0;
    s16 v1;
    s16 v2;
    s16 v3;
    s16 v4;
    u32 v5;
    u32 v6;
    VecFx32 v7;
    VecFx32 v8;
    u32 v9;
    u32 v10;
    u32 v11;
    BOOL v12;
    BOOL v13;

    v10 = WiFiEarth_GetMarkerCount(&param0->unk_288);

    WiFiEarth_GetGlobeRotation(&param0->unk_1DC, &v7);

    v1 = (s16)(v7.x - 0x80);
    v2 = (s16)(v7.x + 0x80);
    v3 = (s16)(v7.y - 0x80);
    v4 = (s16)(v7.y + 0x80);
    v6 = 0x80 * 2;
    v11 = v10;

    for (v0 = 0; v0 < v10; v0++) {
        WiFiEarth_GetMarkerPosition(&param0->unk_288, &v8, v0);
        v9 = WiFiEarth_GetMarkerStatus(&param0->unk_288, v0);

        if ((v8.x > v1) && (v8.x < v2) && (v8.y > v3) && (v8.y < v4) && (v9 != 3)) {
            WiFiEarth_WrapAngle(&v7);
            WiFiEarth_WrapAngle(&v8);

            v5 = WiFiEarth_AngleDistance(&v7, &v8);

            if (v5 < v6) {
                v6 = v5;
                v11 = v0;
            }
        }
    }

    return v11;
}

static u32 WiFiEarth_AngleDistance(const VecFx32 *param0, const VecFx32 *param1)
{
    s32 v0, v1;
    u32 v2;

    v0 = MATH_ABS(param0->x - param1->x);
    v1 = MATH_ABS(param0->y - param1->y);

    if (v0 > CalcAngleRotationIdx(180)) {
        v0 = 0xffff - v0;
    }

    if (v1 > CalcAngleRotationIdx(180)) {
        v1 = 0xffff - v1;
    }

    v2 = FX_Sqrt(((v0 * v0) + (v1 * v1)) << FX32_SHIFT) >> FX32_SHIFT;

    return v2;
}

static u32 WiFiEarth_CalcLocalTime(const WiFiEarthAppData *param0, u32 param1, UnkStruct_ov66_02231428 param2)
{
    s32 v0;
    u16 v1;
    VecFx32 v2;
    VecFx32 v3;
    int v4;

    v0 = param2.unk_00_val2_unk_00 - 4;
    v4 = WiFiEarth_GetMarkerIndex(&param0->unk_288, 219, 3);

    GF_ASSERT(v4 < WiFiEarth_GetMarkerCount(&param0->unk_288));

    WiFiEarth_GetMarkerPosition(&param0->unk_288, &v2, v4);
    WiFiEarth_GetMarkerPosition(&param0->unk_288, &v3, param1);

    v1 = v2.y - v3.y;
    v0 += (v1 * 24) / 0xffff;

    if (v0 < 0) {
        v0 += 24;
    }

    if (v0 >= 24) {
        v0 %= 24;
    }

    return v0;
}

static BOOL WiFiEarth_MoveCameraToPlace(WiFiEarthAppData *param0, u8 param1, u8 param2)
{
    VecFx32 v0;
    VecFx32 v1;
    u32 v2 = WiFiEarth_FindMarkerByPlace(&param0->unk_288, param1, param2, &v0);

    if (v2 != 3) {
        WiFiEarth_GetGlobeRotation(&param0->unk_1DC, &v1);
        v0.z = v1.z;
        WiFiEarth_SetGlobeRotation(&param0->unk_1DC, &v0);
        return 1;
    }

    return 0;
}

static void WiFiEarth_InitWorldUnlock(WiFiEarthAppData *param0, const UnkStruct_ov66_02230F50 *param1)
{
    int v0;

    param0->unk_04.isJapanese = 0;
    param0->unk_04.worldUnlocked = 0;

    if (gGameLanguage == LANGUAGE_JAPANESE) {
        param0->unk_04.isJapanese = 1;
    } else {
        param0->unk_04.isJapanese = 0;
    }

    if (param0->unk_04.isJapanese == 1) {
        for (v0 = 0; v0 < 50; v0++) {
            if (param1->unk_00->unk_00[v0].unk_03_4 == 1) {
                if (param1->unk_00->unk_00[v0].unk_00 != 103) {
                    param0->unk_04.worldUnlocked = 1;
                }
            }
        }
    } else {
        param0->unk_04.worldUnlocked = 1;
    }
}

static void WiFiEarth_InitGraphics(WiFiEarthGraphics *param0, Options *options, u32 heapID)
{
    param0->unk_1A8 = NARC_ctor(NARC_INDEX_GRAPHIC__WORLDTIMER, heapID);

    VramTransfer_New(64, heapID);
    GXLayers_SetBanks(&sGxBanks);

    WiFiEarth_InitBackgrounds(param0, options, heapID);
    WiFiEarth_InitSpriteSystem(param0, heapID);
    WiFiEarth_Init3D(param0, heapID);
}

static void WiFiEarth_FreeGraphics(WiFiEarthGraphics *param0)
{
    NARC_dtor(param0->unk_1A8);
    VramTransfer_Free();

    WiFiEarth_FreeBackgrounds(param0);
    WiFiEarth_FreeSpriteSystem(param0);
    WiFiEarth_Free3D(param0);
}

static void WiFiEarth_UpdateSprites(WiFiEarthGraphics *param0)
{
    SpriteList_Update(param0->unk_04);
}

static void WiFiEarth_ProcessVBlank(WiFiEarthGraphics *param0)
{
    Bg_RunScheduledUpdates(param0->unk_00);
    RenderOam_Transfer();
    VramTransfer_Process();
}

static void WiFiEarth_InitBackgrounds(WiFiEarthGraphics *param0, Options *options, u32 heapID)
{
    SetAllGraphicsModes(&sGraphicsModes);

    param0->unk_00 = BgConfig_New(heapID);
    gSystem.whichScreenIs3D = DS_SCREEN_SUB;

    GXLayers_SwapDisplay();

    int i;

    for (i = 0; i < 5; i++) {
        Bg_InitFromTemplate(param0->unk_00, sBgLayers[i], &sBgTemplates[i], 0);
        Bg_ClearTilesRange(sBgLayers[i], 32, 0, heapID);
        Bg_ClearTilemap(param0->unk_00, sBgLayers[i]);
    }

    Graphics_LoadPaletteFromOpenNARC(param0->unk_1A8, 5, 4, 0, 0, heapID);

    Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_1A8, 11, param0->unk_00, 4, 0, 0, 0, heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_1A8, 12, param0->unk_00, 4, 0, 0, 0, heapID);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_1A8, 4, param0->unk_00, 6, 0, 0, 0, heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_1A8, 18, param0->unk_00, 7, 0, 0, 0, heapID);

    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(1), heapID);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_SUB_BG, PLTT_OFFSET(11), heapID);
    LoadStandardWindowGraphics(param0->unk_00, BG_LAYER_MAIN_1, 1 + (18 + 12), 0, 0, heapID);
    LoadStandardWindowGraphics(param0->unk_00, BG_LAYER_MAIN_1, 1 + (18 + 12), 0, 0, heapID);

    u8 v1 = Options_Frame(options);

    LoadMessageBoxGraphics(param0->unk_00, BG_LAYER_SUB_0, 10, 10, v1, heapID);
    LoadMessageBoxGraphics(param0->unk_00, BG_LAYER_MAIN_1, 1, 2, v1, heapID);

    Bg_MaskPalette(BG_LAYER_MAIN_0, 0x72ca);
}

static void WiFiEarth_FreeBackgrounds(WiFiEarthGraphics *param0)
{
    {
        int v0;

        for (v0 = 0; v0 < 5; v0++) {
            Bg_FreeTilemapBuffer(param0->unk_00, sBgLayers[v0]);
        }
    }

    Heap_Free(param0->unk_00);
    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;
    GXLayers_SwapDisplay();
}

static void WiFiEarth_InitSpriteSystem(WiFiEarthGraphics *param0, u32 heapID)
{
    int i;

    NNS_G2dInitOamManagerModule();

    RenderOam_Init(0, 126, 0, 31, 0, 126, 0, 31, heapID);
    CharTransfer_InitWithVramModes(&sCharTransferTemplate, GX_OBJVRAMMODE_CHAR_1D_32K, GX_OBJVRAMMODE_CHAR_1D_32K);
    PlttTransfer_Init(32, heapID);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_32K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    param0->unk_04 = SpriteList_InitRendering(32, &param0->unk_08, heapID);

    SetSubScreenViewRect(&param0->unk_08, 0, FX32_CONST(256));

    for (i = 0; i < 4; i++) {
        param0->unk_194[i] = SpriteResourceCollection_New(32, i, heapID);
    }

    NetworkIcon_Init();
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void WiFiEarth_FreeSpriteSystem(WiFiEarthGraphics *param0)
{
    int v0;

    SpriteList_Delete(param0->unk_04);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(param0->unk_194[v0]);
    }

    CharTransfer_Free();
    PlttTransfer_Free();
    RenderOam_Free();
}

static void WiFiEarth_Init3D(WiFiEarthGraphics *param0, u32 heapID)
{
    param0->unk_1A4 = G3DPipeline_Init(heapID, TEXTURE_VRAM_SIZE_256K, PALETTE_VRAM_SIZE_64K, WiFiEarth_Setup3D);
    NNS_G3dGlbLightVector(0, 0, 0, -(FX32_ONE - 1));
}

static void WiFiEarth_Free3D(WiFiEarthGraphics *param0)
{
    G3DPipelineBuffers_Free(param0->unk_1A4);
}

static void WiFiEarth_Setup3D(void)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);

    G2_SetBG0Priority(1);
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(1);
    G3X_AlphaTest(0, 0);
    G3X_AlphaBlend(1);
    G3X_EdgeMarking(1);
    G3X_SetFog(0, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0);
    G3X_SetClearColor(GX_RGB(26, 26, 26), 0, 0x7fff, 63, 0);
    G3_ViewPort(0, 0, 255, 191);
}

static void WiFiEarth_InitGlobe(WiFiEarthGlobeObject *param0, WiFiEarthGraphics *param1, u32 heapID)
{
    VEC_Set(&param0->unk_00, 0, 0, 0);
    VEC_Set(&param0->unk_0C, FX32_ONE, FX32_ONE, FX32_ONE);
    VEC_Set(&param0->unk_18, 0x1A40, 0x7C00, 0);
    Easy3DModel_LoadFrom(&param0->unk_9C, param1->unk_1A8, 3, heapID);
    Easy3DObject_Init(&param0->unk_24, &param0->unk_9C);
}

static void WiFiEarth_FreeGlobe(WiFiEarthGlobeObject *param0)
{
    Easy3DModel_Release(&param0->unk_9C);
}

static void WiFiEarth_DrawGlobe(WiFiEarthGlobeObject *param0)
{
    MtxFx33 v0;

    WiFiEarth_GetGlobeRotationMatrix(param0, &v0);

    Easy3DObject_SetPosition(&param0->unk_24, param0->unk_00.x, param0->unk_00.y, param0->unk_00.z);
    Easy3DObject_SetScale(&param0->unk_24, param0->unk_0C.x, param0->unk_0C.y, param0->unk_0C.z);

    Easy3DObject_DrawRotated(&param0->unk_24, &v0);
}

static void WiFiEarth_GetGlobePosition(const WiFiEarthGlobeObject *param0, VecFx32 *param1)
{
    *param1 = param0->unk_00;
}

static void WiFiEarth_GetGlobeRotationMatrix(const WiFiEarthGlobeObject *param0, MtxFx33 *param1)
{
    WiFiEarth_BuildRotationMatrix(param1, &param0->unk_18);
}

static void WiFiEarth_GetGlobeRotation(const WiFiEarthGlobeObject *param0, VecFx32 *param1)
{
    *param1 = param0->unk_18;
}

static void WiFiEarth_SetGlobeRotation(WiFiEarthGlobeObject *param0, const VecFx32 *param1)
{
    param0->unk_18 = *param1;
}

static void WiFiEarth_InitPlaceMarkers(WiFiEarthGlobe *param0, const UnkStruct_ov66_02231560 *param1, WiFiEarthGraphics *param2, WiFiEarthAppFlags param3, u32 heapID)
{
    int v0;

    WiFiEarth_LoadPlaceMarkers(param0, param1, heapID);

    for (v0 = 0; v0 < 3; v0++) {
        Easy3DModel_LoadFrom(&param0->unk_B978[v0], param2->unk_1A8, sGlobeModelMembers[v0], heapID);
        Easy3DObject_Init(&param0->unk_B810[v0], &param0->unk_B978[v0]);
    }

    if (param3.worldUnlocked == 0) {
        VEC_Set(&param0->unk_B804, 0x300, 0x300, FX32_ONE);
    } else {
        VEC_Set(&param0->unk_B804, FX32_ONE, FX32_ONE, FX32_ONE);
    }
}

static void WiFiEarth_FreePlaceMarkers(WiFiEarthGlobe *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Easy3DModel_Release(&param0->unk_B978[v0]);
    }
}

static void WiFiEarth_DrawPlaceMarkers(WiFiEarthGlobe *param0, const WiFiEarthGlobeObject *param1)
{
    MtxFx33 v0;
    int v1;
    MtxFx33 v2;
    VecFx32 v3;

    WiFiEarth_GetGlobePosition(param1, &v3);
    WiFiEarth_GetGlobeRotationMatrix(param1, &v2);

    for (v1 = 0; v1 < 3; v1++) {
        Easy3DObject_SetPosition(&param0->unk_B810[v1], v3.x, v3.y, v3.z);

        if (v1 == 2) {
            Easy3DObject_SetScale(&param0->unk_B810[v1], param0->unk_B804.x, param0->unk_B804.y, param0->unk_B804.z + (FX32_CONST(0.1)));
        } else {
            Easy3DObject_SetScale(&param0->unk_B810[v1], param0->unk_B804.x, param0->unk_B804.y, param0->unk_B804.z);
        }
    }

    {
        MTX_Identity33(&v0);
        Easy3DObject_DrawRotated(&param0->unk_B810[2], &v0);
    }

    {
        for (v1 = 0; v1 < param0->unk_00.unk_00; v1++) {
            MTX_Concat33(&param0->unk_00.unk_04[v1].unk_04, &v2, &v0);

            if (param0->unk_00.unk_04[v1].unk_28 != 3) {
                Easy3DObject_DrawRotated(&param0->unk_B810[param0->unk_00.unk_04[v1].unk_28], &v0);
            }
        }
    }
}

static u32 WiFiEarth_GetPlaceStatus(const UnkStruct_ov66_02231560 *param0, u16 param1, u16 param2)
{
    int v0;
    BOOL v1;
    BOOL v2;
    u8 v3, v4;

    for (v0 = 0; v0 < 50; v0++) {
        v2 = ov66_0223164C(param0, v0);

        if (v2) {
            v1 = ov66_02231624(param0, v0);
            v3 = ov66_022315D8(param0, v0);
            v4 = ov66_022315FC(param0, v0);

            if ((v3 == param1) && (v4 == param2)) {
                if (v1 == 1) {
                    return 1;
                }

                return 0;
            }
        }
    }

    return 3;
}

static u32 WiFiEarth_FindMarkerByPlace(const WiFiEarthGlobe *param0, u16 param1, u16 param2, VecFx32 *param3)
{
    u32 v0 = 3;
    int v1;
    int v2 = WiFiEarth_GetMarkerCount(param0);
    v1 = WiFiEarth_GetMarkerIndex(param0, param1, param2);

    if (v1 < v2) {
        v0 = WiFiEarth_GetMarkerStatus(param0, v1);

        WiFiEarth_GetMarkerPosition(param0, param3, v1);
    }

    return v0;
}

static u32 WiFiEarth_GetMarkerIndex(const WiFiEarthGlobe *param0, u16 param1, u16 param2)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_00.unk_00; v0++) {
        if ((param0->unk_00.unk_04[v0].unk_2A == param1) && (param0->unk_00.unk_04[v0].unk_2C == param2)) {
            return v0;
        }
    }

    return param0->unk_00.unk_00;
}

static void WiFiEarth_GetMarkerPosition(const WiFiEarthGlobe *param0, VecFx32 *param1, int param2)
{
    GF_ASSERT(param2 < param0->unk_00.unk_00);

    param1->x = param0->unk_00.unk_04[param2].unk_00;
    param1->y = param0->unk_00.unk_04[param2].unk_02;
    param1->z = 0;
}

static u32 WiFiEarth_GetMarkerStatus(const WiFiEarthGlobe *param0, int param1)
{
    GF_ASSERT(param1 < param0->unk_00.unk_00);
    return param0->unk_00.unk_04[param1].unk_28;
}

static u32 WiFiEarth_GetMarkerCountry(const WiFiEarthGlobe *param0, int param1)
{
    GF_ASSERT(param1 < param0->unk_00.unk_00);
    return param0->unk_00.unk_04[param1].unk_2A;
}

static u32 WiFiEarth_GetMarkerRegion(const WiFiEarthGlobe *param0, int param1)
{
    GF_ASSERT(param1 < param0->unk_00.unk_00);
    return param0->unk_00.unk_04[param1].unk_2C;
}

static u32 WiFiEarth_GetMarkerCount(const WiFiEarthGlobe *param0)
{
    return param0->unk_00.unk_00;
}

static void WiFiEarth_InitCamera(WiFiEarthCamera *param0, WiFiEarthAppFlags param1, enum HeapID heapID)
{
    param0->camera = Camera_Alloc(heapID);

    Camera_InitWithTargetAndPosition(&sCameraTarget, &sCameraPosition, 0x5c1, 0, 0, param0->camera);
    Camera_SetClipping(0, FX32_ONE * 100, param0->camera);
    Camera_ComputeProjectionMatrix(0, param0->camera);
    Camera_SetAsActive(param0->camera);

    if (param1.worldUnlocked == 0) {
        param0->unk_10 = 1;
        param0->unk_0C = 0x50000;
    } else {
        param0->unk_10 = 0;
        param0->unk_0C = 0x128000;
    }

    Camera_SetDistance(param0->unk_0C, param0->camera);
}

static void WiFiEarth_FreeCamera(WiFiEarthCamera *param0)
{
    Camera_Delete(param0->camera);
}

static void WiFiEarth_UpdateCamera(const WiFiEarthCamera *param0)
{
    Camera_ComputeViewMatrix();
}

static void WiFiEarth_ToggleZoom(WiFiEarthCamera *param0)
{
    if (param0->unk_10 == 0) {
        param0->unk_10 = 1;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    } else {
        param0->unk_10 = 0;
        Sound_PlayEffect(SEQ_SE_PL_TIMER03_sseq);
    }

    param0->unk_12 = 1;
}

static BOOL WiFiEarth_UpdateZoom(WiFiEarthCamera *param0, WiFiEarthGlobe *param1)
{
    if (param0->unk_12 == 0) {
        return 1;
    }

    switch (param0->unk_10) {
    case 1:
        if (param0->unk_0C > (0x50000 + 0x8000)) {
            param0->unk_0C -= 0x8000;
            param1->unk_B804.x -= 0x80;
            param1->unk_B804.y = param1->unk_B804.x;
        } else {
            param0->unk_0C = 0x50000;
            param0->unk_12 = 0;
        }
        break;
    case 0:
        if (param0->unk_0C < (0x128000 - 0x8000)) {
            param0->unk_0C += 0x8000;
            param1->unk_B804.x += 0x80;
            param1->unk_B804.y = param1->unk_B804.x;
        } else {
            param0->unk_0C = 0x128000;
            param0->unk_12 = 0;
        }
        break;
    }

    Camera_SetDistance(param0->unk_0C, param0->camera);

    return 0;
}

static u32 WiFiEarth_IsZoomedIn(const WiFiEarthCamera *param0)
{
    return param0->unk_10;
}

static void WiFiEarth_InitExitWindow(WiFiEarthExitWindow *param0, WiFiEarthGraphics *param1, WiFiEarthMessageLoader *param2, u32 heapID)
{
    memset(param0, 0, sizeof(WiFiEarthExitWindow));

    Window_Add(param1->unk_00, &param0->unk_1C, 1, 25, 21, 6, 2, 1, (1 + (18 + 12)) + 9);
    Window_FillTilemap(&param0->unk_1C, 15);

    {
        String *v0;

        v0 = WiFiEarth_GetMessage(param2, 1);

        Font_InitManager(FONT_SUBSCREEN, heapID);
        {
            u32 v1 = Font_CalcCenterAlignment(FONT_SUBSCREEN, v0, 0, 48);
            Text_AddPrinterWithParamsAndColor(&param0->unk_1C, FONT_SUBSCREEN, v0, v1, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(2, 1, 15), NULL);
        }

        Font_Free(FONT_SUBSCREEN);
    }

    Window_DrawStandardFrame(&param0->unk_1C, 0, 1 + (18 + 12), 0);
}

static void WiFiEarth_FreeExitWindow(WiFiEarthExitWindow *param0)
{
    Window_Remove(&param0->unk_1C);
}

static void WiFiEarth_ProcessExitWindowInput(WiFiEarthExitWindow *param0)
{
    int v0, v1, v2, v3;

    param0->unk_00 = 0;

    if (gSystem.touchPressed) {
        if ((gSystem.touchX >= (25 * 8)) && (gSystem.touchX <= ((25 + 6) * 8)) && (gSystem.touchY >= (21 * 8)) && (gSystem.touchY <= ((21 + 2) * 8))) {
            param0->unk_00 = PAD_BUTTON_B;
            return;
        } else {
            param0->unk_04 = 0;
            param0->unk_10 = 0;
            param0->unk_14 = 0;
            param0->unk_18 = 0;
            param0->unk_00 = 0;
            param0->unk_08 = gSystem.touchX;
            param0->unk_0C = gSystem.touchY;
            param0->unk_18 = 4;
        }
    }

    if (gSystem.touchHeld) {
        switch (param0->unk_04) {
        case 0:

            if (!param0->unk_18) {
                param0->unk_04++;
            } else {
                param0->unk_18--;
            }
        case 1:
            WiFiEarth_CalcTouchDrag(param0->unk_08, param0->unk_0C, &v0, &v1, &v2, &v3);
            param0->unk_00 = v0 | v2;
            param0->unk_10 = v1;
            param0->unk_14 = v3;
            param0->unk_08 = gSystem.touchX;
            param0->unk_0C = gSystem.touchY;
            break;
        }
    } else {
        if (param0->unk_18) {
            param0->unk_00 = PAD_BUTTON_A;
        }

        param0->unk_04 = 0;
        param0->unk_10 = 0;
        param0->unk_14 = 0;
        param0->unk_18 = 0;
    }
}

static int WiFiEarth_GetExitWindowInput(const WiFiEarthExitWindow *param0, u32 param1)
{
    int v0;

    switch (param1) {
    case 0:
        v0 = param0->unk_00;
        break;
    case 1:
        v0 = param0->unk_10;
        break;
    case 2:
        v0 = param0->unk_14;
        break;
    default:
        break;
    }

    return v0;
}

static void WiFiEarth_ShowExitWindow(WiFiEarthExitWindow *param0)
{
    Window_EraseStandardFrame(&param0->unk_1C, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->unk_1C);
}

static void WiFiEarth_HideExitWindow(WiFiEarthExitWindow *param0)
{
    Window_ScheduleCopyToVRAM(&param0->unk_1C);
    Window_DrawStandardFrame(&param0->unk_1C, 0, 1 + (18 + 12), 0);
}

static void WiFiEarth_InitConfirmWindow(WiFiEarthConfirmWindow *param0, WiFiEarthGraphics *param1, WiFiEarthMessageLoader *param2, SaveData *saveData, u32 heapID)
{
    memset(param0, 0, sizeof(WiFiEarthExitWindow));

    param0->unk_08 = Options_TextFrameDelay(SaveData_GetOptions(saveData));
    param0->unk_0C = String_Init(128, heapID);

    Window_Add(param1->unk_00, &param0->unk_10, 1, 2, 1, 27, 4, 1, ((1 + (18 + 12)) + 9) + (6 * 2));
    Window_FillTilemap(&param0->unk_10, 15);

    WiFiEarth_GetMessageInto(param2, 5, param0->unk_0C);

    param0->unk_20 = YesNoTouchMenu_New(heapID);
}

static void WiFiEarth_FreeConfirmWindow(WiFiEarthConfirmWindow *param0)
{
    if (Text_IsPrinterActive(param0->unk_04) != 0) {
        Text_RemovePrinter(param0->unk_04);
    }

    String_Free(param0->unk_0C);
    YesNoTouchMenu_Free(param0->unk_20);
    Window_Remove(&param0->unk_10);
}

static void WiFiEarth_ShowConfirmWindow(WiFiEarthConfirmWindow *param0)
{
    Window_FillTilemap(&param0->unk_10, 15);
    Window_DrawMessageBoxWithScrollCursor(&param0->unk_10, 1, 1, 2);
    Window_ScheduleCopyToVRAM(&param0->unk_10);

    param0->unk_04 = Text_AddPrinterWithParams(&param0->unk_10, FONT_MESSAGE, param0->unk_0C, 0, 0, param0->unk_08, NULL);
    param0->unk_00 = 0;
}

static u32 WiFiEarth_ProcessConfirmInput(WiFiEarthConfirmWindow *param0)
{
    u32 v0;

    switch (param0->unk_00) {
    case 0:
        v0 = 0;

        if (Text_IsPrinterActive(param0->unk_04) == 0) {
            YesNoTouchMenuParams v1;

            v1 = sYesNoTouchMenuParams;
            v1.bgConfig = Window_GetBgConfig(&param0->unk_10);
            YesNoTouchMenu_InitWithParams(param0->unk_20, &v1);
            param0->unk_00++;
        }
        break;
    case 1:
        v0 = YesNoTouchMenu_ProcessInput(param0->unk_20);
        break;
    }

    return v0;
}

static void WiFiEarth_HideConfirmWindow(WiFiEarthConfirmWindow *param0)
{
    YesNoTouchMenu_Reset(param0->unk_20);
    Window_EraseMessageBox(&param0->unk_10, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->unk_10);
}

static void WiFiEarth_InitProfilePanel(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1, WiFiEarthMessageLoader *param2, enum HeapID heapID)
{
    param0->unk_00 = 0;

    WiFiEarth_ResetProfileHistory(param0);

    {
        int v0;

        for (v0 = 0; v0 < 5; v0++) {
            WiFiEarth_InitProfileGraphic(&param0->unk_A0[v0], param1, &sProfileGraphicParams[v0], sProfileGraphicFrames[v0], heapID);
        }
    }

    {
        String *v1;

        Window_Add(param1->unk_00, &param0->unk_1A8, 4, 2, 19, 27, 4, 11, 10 + (18 + 12));
        Window_FillTilemap(&param0->unk_1A8, 15);

        v1 = WiFiEarth_GetMessage(param2, 0);

        Text_AddPrinterWithParams(&param0->unk_1A8, FONT_MESSAGE, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, NULL);
        Window_DrawMessageBoxWithScrollCursor(&param0->unk_1A8, 0, 10, 10);
    }

    WiFiEarth_InitProfileWindows(param0, param1, heapID);

    {
        param0->unk_94 = Graphics_GetScrnDataFromOpenNARC(param1->unk_1A8, 19, 0, &param0->unk_98, heapID);
    }

    WiFiEarth_InitMarkerSprites(&param0->unk_1B8, param1, &param0->unk_2E4, heapID);
    WiFiEarth_InitWindowMask(&param0->unk_2E4);
}

static void WiFiEarth_FreeProfilePanel(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1)
{
    WiFiEarth_FreeWindowMask(&param0->unk_2E4);
    WiFiEarth_FreeMarkerSprites(&param0->unk_1B8, param1);

    Heap_Free(param0->unk_94);
    WiFiEarth_FreeProfileWindows(param0);
    Window_Remove(&param0->unk_1A8);
    WiFiEarth_ClearProfileHistory(param0);

    {
        int v0;

        for (v0 = 0; v0 < 5; v0++) {
            WiFiEarth_FreeProfileGraphic(&param0->unk_A0[v0]);
        }
    }
}

static void WiFiEarth_UpdateProfilePanel(WiFiEarthProfilePanel *param0, WiFiEarthMessageLoader *param1, WiFiEarthGraphics *param2)
{
    BOOL v0;

    switch (param0->unk_00) {
    case 0:
        WiFiEarth_UpdateProfileSprites(param0, param2);
        WiFiEarth_UpdateMarkerSprites(&param0->unk_1B8, &param0->unk_2E4);
        break;
    case 1:
        WiFiEarth_ShowProfiles(param0, param1, param2);
        param0->unk_00 = 2;
        break;
    case 2:
        v0 = WiFiEarth_AnimateProfilesSlow(param0, param2);

        if (v0 == 1) {
            param0->unk_00 = 0;
        }
        break;
    case 3:
        WiFiEarth_HalveProfileProgress(param0);
        WiFiEarth_AnimateProfilesFast(param0, param2);
        param0->unk_00 = 4;
        break;
    case 4:
        v0 = WiFiEarth_AnimateProfilesFast(param0, param2);

        if (v0 == 1) {
            param0->unk_00 = 0;
        }
        break;
    }
}

static void WiFiEarth_HideProfilePanel(WiFiEarthProfilePanel *param0)
{
    Window_EraseMessageBox(&param0->unk_1A8, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->unk_1A8);
}

static void WiFiEarth_ShowProfilePanel(WiFiEarthProfilePanel *param0)
{
    Window_ScheduleCopyToVRAM(&param0->unk_1A8);
    Window_DrawMessageBoxWithScrollCursor(&param0->unk_1A8, 1, 10, 10);
}

static BOOL WiFiEarth_PushProfile(WiFiEarthProfilePanel *param0, const WiFiEarthProfile *param1)
{
    switch (param0->unk_00) {
    case 0:
        param0->unk_00 = 1;
        break;
    case 2:
        param0->unk_00 = 3;
        return 0;
    case 3:
    case 4:
    case 1:
        return 0;
    }

    WiFiEarth_AddProfileToHistory(param0, param1);

    return 1;
}

static BOOL WiFiEarth_ProfileExists(const WiFiEarthProfilePanel *param0, const WiFiEarthProfile *param1)
{
    int v0;
    WiFiEarthProfile v1;
    BOOL v2;

    for (v0 = 0; v0 < 3; v0++) {
        v2 = WiFiEarth_GetProfileFromHistory(param0, &v1, v0);

        if (v2 == 0) {
            return 0;
        }

        if ((v1.unk_04 == param1->unk_04) && (v1.unk_08 == param1->unk_08)) {
            return 1;
        }
    }

    return 0;
}

static void WiFiEarth_ResetProfileHistory(WiFiEarthProfilePanel *param0)
{
    param0->unk_34 = 0;
    param0->unk_36 = 0;
    param0->unk_38 = 0;
}

static void WiFiEarth_ClearProfileHistory(WiFiEarthProfilePanel *param0)
{
    param0->unk_34 = 0;
    param0->unk_36 = 0;
    param0->unk_38 = 0;
}

static void WiFiEarth_AddProfileToHistory(WiFiEarthProfilePanel *param0, const WiFiEarthProfile *param1)
{
    if (((param0->unk_36 + 1) % 4) == param0->unk_34) {
        WiFiEarth_PopProfileHistory(param0);
    }

    param0->unk_04[param0->unk_36] = *param1;
    param0->unk_36 = (param0->unk_36 + 1) % 4;
    param0->unk_38++;
}

static void WiFiEarth_PopProfileHistory(WiFiEarthProfilePanel *param0)
{
    if (param0->unk_36 == param0->unk_34) {
        return;
    }

    param0->unk_34 = (param0->unk_34 + 1) % 4;
    param0->unk_38--;
}

static BOOL WiFiEarth_GetProfileFromHistory(const WiFiEarthProfilePanel *param0, WiFiEarthProfile *param1, u32 param2)
{
    s32 v0;

    if (param2 >= param0->unk_38) {
        return 0;
    }

    v0 = (param0->unk_36 - 1) - param2;

    if (v0 < 0) {
        v0 += 4;
    }

    *param1 = param0->unk_04[v0];

    return 1;
}

static void WiFiEarth_UpdateProfileSprites(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        WiFiEarth_UpdateProfileGraphic(&param0->unk_A0[v0], param1);
    }
}

static void WiFiEarth_ShowProfiles(WiFiEarthProfilePanel *param0, WiFiEarthMessageLoader *param1, WiFiEarthGraphics *param2)
{
    memset(param0->unk_40, 0, sizeof(WiFiEarthProfileTileState) * (3 * 6));

    param0->unk_3C = 0;
    param0->unk_3E = 0;

    {
        int v0;
        int v1;
        int v2;
        BOOL v3;
        int v4;
        WiFiEarthProfile v5;

        for (v0 = 0; v0 < 5; v0++) {
            WiFiEarth_ClearProfileGraphicVisible(&param0->unk_A0[v0]);
        }

        WiFiEarth_ResetMarkerSprites(&param0->unk_1B8);

        v4 = -1;

        for (v0 = 0; v0 < 3; v0++) {
            v1 = 2 - v0;
            v3 = WiFiEarth_GetProfileFromHistory(param0, &v5, v0);

            if (v3 == 1) {
                v2 = WiFiEarth_GetMarkerSpriteIndex(v5.unk_00);

                WiFiEarth_SetProfileGraphicVisible(&param0->unk_A0[v2], v1, 1);
                WiFiEarth_PrintProfile(param0, v1, &v5, param1);

                param0->unk_88[v1] = v2;
                WiFiEarth_ShowMarkerSprite(&param0->unk_1B8, v1, v5.unk_00, v4);
                param0->unk_3E += 6;

                v4 = v5.unk_00;
            } else {
                param0->unk_88[v1] = 5;
                v4 = -1;
            }
        }
    }
}

static BOOL WiFiEarth_AnimateProfilesSlow(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1)
{
    return WiFiEarth_AnimateProfileProgress(param0, param1, 2);
}

static void WiFiEarth_HalveProfileProgress(WiFiEarthProfilePanel *param0)
{
    int v0 = param0->unk_3C / 2;
    param0->unk_3C = v0 * 1;
}

static BOOL WiFiEarth_AnimateProfilesFast(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1)
{
    return WiFiEarth_AnimateProfileProgress(param0, param1, 1);
}

static BOOL WiFiEarth_AnimateProfileProgress(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1, int param2)
{
    u32 v0;
    int v1;
    BOOL v2;
    BOOL v3 = 1;

    if ((param0->unk_3C % param2) == 0) {
        v0 = param0->unk_3C / param2;
        WiFiEarth_StartProfileTile(param0, v0);
    }

    if ((param0->unk_3C + 1) < ((3 * 6) * param2)) {
        param0->unk_3C++;
    }

    for (v1 = 0; v1 < param0->unk_3E; v1++) {
        v2 = WiFiEarth_UpdateProfileTile(param0, v1, param1);

        if (v2 == 0) {
            v3 = 0;
        }
    }

    if (v3 == 1) {
        WiFiEarth_HideMarkerSprites(&param0->unk_1B8);
        WiFiEarth_SetWindow1(&param0->unk_2E4, 0, 0);
    }

    return v3;
}

static void WiFiEarth_StartProfileTile(WiFiEarthProfilePanel *param0, u32 param1)
{
    param0->unk_40[param1].unk_00 = 1;
}

static BOOL WiFiEarth_UpdateProfileTile(WiFiEarthProfilePanel *param0, u32 param1, WiFiEarthGraphics *param2)
{
    u32 v0;
    u32 v1;
    u32 v2;
    u32 v3;

    if (param0->unk_40[param1].unk_00 == 0) {
        return 0;
    }

    if (param0->unk_40[param1].unk_01 >= 2) {
        return 1;
    }

    v0 = ((3 * 6) - param1) - 1;
    v2 = v0 / 6;
    v1 = v0 % 6;
    v3 = param0->unk_88[v2];

    switch (param0->unk_40[param1].unk_01) {
    case 0: {
        u8 *v4;

        v4 = WiFiEarth_GetProfileHeaderPixels(param0, v1);
        WiFiEarth_TransferProfileTile(param0, v2, v1, v4);
    }

        {
            WiFiEarth_CopyProfileTilemap(param0, v0, param2);
        }

        {
            WiFiEarth_SetWindow1(&param0->unk_2E4, v0 * 8, (3 * 6) * 8);
        }
        break;
    case 1: {
        u8 *v5;

        v5 = WiFiEarth_GetProfileTilePixels(param0, v2, v1);
        WiFiEarth_TransferProfileTile(param0, v2, v1, v5);
    }
        {
            WiFiEarth_DrawProfileGraphic(&param0->unk_A0[v3], v0, param2);
        }
        break;
    default:
        break;
    }

    param0->unk_40[param1].unk_01++;
    return 0;
}

static void WiFiEarth_CopyProfileTilemap(WiFiEarthProfilePanel *param0, u32 param1, WiFiEarthGraphics *param2)
{
    Bg_CopyToTilemapRect(param2->unk_00, 6, 0, 0 + param1, 32, 1, param0->unk_98->rawData, 0, 0 + param1, param0->unk_98->screenWidth / 8, param0->unk_98->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param2->unk_00, 6);
}

static void WiFiEarth_InitWindowMask(WiFiEarthWindowMask *param0)
{
    GXS_SetVisibleWnd(GX_WNDMASK_W0 | GX_WNDMASK_W1);
    G2S_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 0);
    G2S_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3, 0);
    G2S_SetWnd1InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3, 0);

    WiFiEarth_SetWindow0(param0, 0, 0);
    WiFiEarth_SetWindow1(param0, 0, 0);

    param0->unk_0C = SysTask_ExecuteAfterVBlank(WiFiEarth_ApplyWindowMask, param0, 0);
}

static void WiFiEarth_FreeWindowMask(WiFiEarthWindowMask *param0)
{
    SysTask_Done(param0->unk_0C);
    GXS_SetVisibleWnd(GX_WNDMASK_NONE);
}

static void WiFiEarth_SetWindow0(WiFiEarthWindowMask *param0, s16 param1, s16 param2)
{
    if (param1 < 0) {
        param1 = 0;
    }

    if (param2 < 0) {
        param2 = 0;
    }

    param0->unk_00 = 1;
    param0->unk_04 = param1;
    param0->unk_06 = param2;
}

static void WiFiEarth_SetWindow1(WiFiEarthWindowMask *param0, s16 param1, s16 param2)
{
    if (param1 < 0) {
        param1 = 0;
    }

    if (param2 < 0) {
        param2 = 0;
    }

    param0->unk_02 = 1;
    param0->unk_08 = param1;
    param0->unk_0A = param2;
}

static void WiFiEarth_ApplyWindowMask(SysTask *param0, void *param1)
{
    WiFiEarthWindowMask *v0 = param1;

    if (v0->unk_00) {
        G2S_SetWnd0Position(0, v0->unk_04, 255, v0->unk_06);
        v0->unk_00 = 0;
    }

    if (v0->unk_02) {
        G2S_SetWnd1Position(0, v0->unk_08, 255, v0->unk_0A);
        v0->unk_02 = 0;
    }
}

static void WiFiEarth_InitProfileWindows(WiFiEarthProfilePanel *param0, WiFiEarthGraphics *param1, u32 param2)
{
    int v0;
    int v1 = ((10 + (18 + 12)) + (27 * 4));

    for (v0 = 0; v0 < 3; v0++) {
        Window_Add(param1->unk_00, &param0->unk_168[v0], 5, 0, 0 + (6 * v0), 27, 6, 14, v1);

        v1 += (27 * 6);

        Window_FillTilemap(&param0->unk_168[v0], 0);
        Window_CopyToVRAM(&param0->unk_168[v0]);
    }

    Window_Add(param1->unk_00, &param0->unk_198, 5, 0, 0, 27, 6, 14, (10 + (18 + 12)) + (27 * 4));
    Window_FillTilemap(&param0->unk_198, 0);
}

static void WiFiEarth_FreeProfileWindows(WiFiEarthProfilePanel *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        Window_Remove(&param0->unk_168[v0]);
    }

    Window_Remove(&param0->unk_198);
}

static void WiFiEarth_PrintProfile(WiFiEarthProfilePanel *param0, u32 param1, const WiFiEarthProfile *param2, WiFiEarthMessageLoader *param3)
{
    String *v0;
    Window *v1;
    u32 v2;

    GF_ASSERT(param1 < 3);

    v1 = &param0->unk_168[param1];
    Window_FillTilemap(v1, 0);
    v2 = WiFiEarth_GetMarkerSpriteIndex(param2->unk_00);

    {
        v0 = WiFiEarth_GetMessage(param3, 2);
        Text_AddPrinterWithParamsAndColor(v1, FONT_MESSAGE, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, sProfileTextColors[v2], NULL);
    }

    {
        v0 = WiFiEarth_FormatCountryName(param3, param2->unk_04);
        Text_AddPrinterWithParamsAndColor(v1, FONT_MESSAGE, v0, 0, 16, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    }

    {
        v0 = WiFiEarth_FormatCityName(param3, param2->unk_04, param2->unk_08);
        Text_AddPrinterWithParamsAndColor(v1, FONT_MESSAGE, v0, 0, 32, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    }
}

static u8 *WiFiEarth_GetProfileTilePixels(WiFiEarthProfilePanel *param0, u32 param1, u32 param2)
{
    u8 *v0;

    GF_ASSERT(param1 < 3);
    v0 = param0->unk_168[param1].pixels;

    return &v0[((27 * param2) * 32)];
}

static u8 *WiFiEarth_GetProfileHeaderPixels(WiFiEarthProfilePanel *param0, u32 param1)
{
    u8 *v0 = param0->unk_198.pixels;
    return &v0[((27 * param1) * 32)];
}

static void WiFiEarth_TransferProfileTile(WiFiEarthProfilePanel *param0, u32 param1, u32 param2, const u8 *param3)
{
    u16 v0 = Window_GetBaseTile(&param0->unk_168[param1]);
    v0 += (27 * param2);

    VramTransfer_Request(NNS_GFD_DST_2D_BG1_CHAR_SUB, v0 * 32, (void *)param3, 27 * 32);
}

static void WiFiEarth_InitProfileGraphic(WiFiEarthProfileGraphic *param0, WiFiEarthGraphics *param1, const WiFiEarthProfileGraphicParams *param2, u16 param3, enum HeapID heapID)
{
    int v0;

    memset(param0, 0, sizeof(WiFiEarthProfileGraphic));
    param0->unk_02 = param3;

    if (param2->unk_04 > 0) {
        param0->unk_18 = param2->unk_04;

        for (v0 = 0; v0 < param0->unk_18; v0++) {
            param0->unk_08[v0] = Graphics_GetScrnDataFromOpenNARC(
                param1->unk_1A8, param2->unk_00[v0], 0, &param0->unk_10[v0], heapID);
        }
    }

    if (param2->unk_08 > 0) {
        param0->unk_24 = param2->unk_08;
        param0->unk_26 = param2->unk_0A;
        param0->unk_1C = Graphics_GetPlttDataFromOpenNARC(param1->unk_1A8, param2->unk_06, &param0->unk_20, heapID);
    }
}

static void WiFiEarth_FreeProfileGraphic(WiFiEarthProfileGraphic *param0)
{
    int v0;

    if (param0->unk_18 > 0) {
        for (v0 = 0; v0 < param0->unk_18; v0++) {
            Heap_Free(param0->unk_08[v0]);
        }
    }

    if (param0->unk_24 > 0) {
        Heap_Free(param0->unk_1C);
    }
}

static void WiFiEarth_UpdateProfileGraphic(WiFiEarthProfileGraphic *param0, WiFiEarthGraphics *param1)
{
    int v0;
    u32 v1, v2;

    v2 = (param0->unk_00 * param0->unk_18) / param0->unk_02;
    v1 = (param0->unk_00 * param0->unk_24) / param0->unk_02;

    param0->unk_00 = (param0->unk_00 + 1) % param0->unk_02;

    if ((param0->unk_18 > 0) && (v2 != param0->unk_1A)) {
        param0->unk_1A = v2;

        for (v0 = 0; v0 < 3; v0++) {
            if (param0->unk_04[v0] == 1) {
                Bg_CopyToTilemapRect(param1->unk_00, 6, 0, 0 + (6 * v0), 32, 6, param0->unk_10[param0->unk_1A]->rawData, 0, 0 + (6 * v0), param0->unk_10[param0->unk_1A]->screenWidth / 8, param0->unk_10[param0->unk_1A]->screenHeight / 8);
                Bg_ScheduleTilemapTransfer(param1->unk_00, 6);
            }
        }
    }

    if ((param0->unk_24 > 0) && (v1 != param0->unk_25)) {
        BOOL v3;
        u8 *v4;

        param0->unk_25 = v1;

        v4 = (u8 *)param0->unk_20->pRawData;
        v3 = VramTransfer_Request(NNS_GFD_DST_2D_BG_PLTT_SUB, param0->unk_26 * 32, &v4[param0->unk_25 * 32], 32);
        GF_ASSERT(v3);
    }
}

static void WiFiEarth_SetProfileGraphicVisible(WiFiEarthProfileGraphic *param0, u32 param1, BOOL param2)
{
    GF_ASSERT(param1 < 3);
    param0->unk_04[param1] = param2;
}

static void WiFiEarth_ClearProfileGraphicVisible(WiFiEarthProfileGraphic *param0)
{
    memset(param0->unk_04, 0, sizeof(u8) * 4);
}

static void WiFiEarth_DrawProfileGraphic(WiFiEarthProfileGraphic *param0, u32 param1, WiFiEarthGraphics *param2)
{
    if (param0->unk_18 > 0) {
        Bg_CopyToTilemapRect(param2->unk_00, 6, 0, 0 + param1, 32, 1, param0->unk_10[param0->unk_1A]->rawData, 0, 0 + param1, param0->unk_10[param0->unk_1A]->screenWidth / 8, param0->unk_10[param0->unk_1A]->screenHeight / 8);
        Bg_ScheduleTilemapTransfer(param2->unk_00, 6);
    }
}

static void WiFiEarth_InitMarkerSprites(WiFiEarthMarkerSprites *param0, WiFiEarthGraphics *param1, WiFiEarthWindowMask *param2, u32 param3)
{
    int v0;
    SpriteResourcesHeader v1;
    BOOL v2;
    SpriteListTemplate v3 = { NULL };

    memset(param0, 0, sizeof(WiFiEarthMarkerSprites));

    param0->unk_30 = 2;
    param0->unk_32 = 128;

    v3.list = param1->unk_04;
    v3.resourceData = &v1;
    v3.priority = 64;
    v3.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    v3.heapID = param3;

    param0->unk_6C[0][1] = SpriteResourceCollection_AddPaletteFrom(param1->unk_194[1], param1->unk_1A8, 20, 0, 0, NNS_G2D_VRAM_TYPE_2DSUB, 12, param3);
    v2 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_6C[0][1]);
    GF_ASSERT(v2);
    SpriteResource_ReleaseData(param0->unk_6C[0][1]);

    for (v0 = 0; v0 < 12; v0++) {
        param0->unk_6C[v0][0] = SpriteResourceCollection_AddTilesFrom(param1->unk_194[0], param1->unk_1A8, 21 + ((v0) * 3), 0, v0, NNS_G2D_VRAM_TYPE_2DSUB, param3);
        param0->unk_6C[v0][2] = SpriteResourceCollection_AddFrom(param1->unk_194[2], param1->unk_1A8, 22 + ((v0) * 3), 0, v0, 2, param3);
        param0->unk_6C[v0][3] = SpriteResourceCollection_AddFrom(param1->unk_194[3], param1->unk_1A8, 23 + ((v0) * 3), 0, v0, 3, param3);

        v2 = SpriteTransfer_RequestCharAtEnd(param0->unk_6C[v0][0]);
        GF_ASSERT(v2);

        SpriteResource_ReleaseData(param0->unk_6C[v0][0]);
        SpriteResourcesHeader_Init(&v1, v0, 0, v0, v0, 0xffffffff, 0xffffffff, 0, 1, param1->unk_194[0], param1->unk_194[1], param1->unk_194[2], param1->unk_194[3], NULL, NULL);

        param0->unk_3C[v0] = SpriteList_Add(&v3);

        Sprite_SetAnimateFlag(param0->unk_3C[v0], 1);
        Sprite_SetAnimSpeed(param0->unk_3C[v0], FX32_ONE);
    }

    WiFiEarth_HideMarkerSprites(param0);
    WiFiEarth_SetWindow1(param2, 0, 0);
}

static void WiFiEarth_FreeMarkerSprites(WiFiEarthMarkerSprites *param0, WiFiEarthGraphics *param1)
{
    int v0, v1;

    Sound_StopEffect(1473, 0);

    for (v0 = 0; v0 < 12; v0++) {
        Sprite_Delete(param0->unk_3C[v0]);
        SpriteTransfer_ResetCharTransfer(param0->unk_6C[v0][0]);

        if (v0 == 0) {
            SpriteTransfer_ResetPlttTransfer(param0->unk_6C[v0][1]);
            SpriteResourceCollection_Remove(param1->unk_194[1], param0->unk_6C[v0][1]);
        }

        for (v1 = 0; v1 < 4; v1++) {
            if (v1 != 1) {
                SpriteResourceCollection_Remove(param1->unk_194[v1], param0->unk_6C[v0][v1]);
            }
        }
    }
}

static void WiFiEarth_ResetMarkerSprites(WiFiEarthMarkerSprites *param0)
{
    memset(param0->unk_34, 0, sizeof(u8) * 4);
    memset(param0->unk_38, 0, sizeof(u8) * 4);

    param0->unk_30 = 2;
    param0->unk_32 = 128;
}

static void WiFiEarth_ShowMarkerSprite(WiFiEarthMarkerSprites *param0, u8 param1, u8 param2, u8 param3)
{
    int v0;

    param0->unk_34[param1] = 1;
    param0->unk_38[param1] = WiFiEarth_GetMarkerSpriteAnim(param2);

    WiFiEarth_InitMarkerAnimation(&param0->unk_00[param1], &sMarkerAnimFrames[param0->unk_38[param1]][param1]);

    if (param3 < 24) {
        v0 = WiFiEarth_GetMarkerSpriteAnim(param3);

        if (v0 == param0->unk_38[param1]) {
            if (param1 < 2) {
                WiFiEarth_SetMarkerAnimFlagB(&param0->unk_00[param1 + 1], 1);
                WiFiEarth_SetMarkerAnimFlagA(&param0->unk_00[param1], 1);
            }
        }
    }
}

static void WiFiEarth_HideMarkerSprites(WiFiEarthMarkerSprites *param0)
{
    int v0;

    for (v0 = 0; v0 < 12; v0++) {
        Sprite_SetDrawFlag(param0->unk_3C[v0], FALSE);
    }
}

static void WiFiEarth_UpdateMarkerSprites(WiFiEarthMarkerSprites *param0, WiFiEarthWindowMask *param1)
{
    BOOL v0;

    if (param0->unk_32 > 0) {
        param0->unk_32--;

        if (param0->unk_32 == 0) {
            v0 = WiFiEarth_ShowMarkerSpriteByIndex(param0, param0->unk_30, param1);

            if (v0 == 1) {
                Sound_PlayEffect(SEQ_SE_PL_TOKEI3_sseq);
            }
        }

        return;
    }

    v0 = WiFiEarth_HideMarkerSpriteByIndex(param0, param0->unk_30, param1);

    if (v0 == 1) {
        if ((param0->unk_30 - 1) >= 0) {
            param0->unk_30--;
            WiFiEarth_ShowMarkerSpriteByIndex(param0, param0->unk_30, param1);
        } else {
            Sound_StopEffect(1473, 0);
            param0->unk_30 = 2;
            param0->unk_32 = 128;
        }
    }
}

static BOOL WiFiEarth_ShowMarkerSpriteByIndex(WiFiEarthMarkerSprites *param0, u32 param1, WiFiEarthWindowMask *param2)
{
    if (param0->unk_34[param1] == 0) {
        return 0;
    }

    WiFiEarth_RestartMarkerAnimation(&param0->unk_00[param1], param2);
    Sprite_SetDrawFlag(param0->unk_3C[param0->unk_38[param1]], TRUE);
    WiFiEarth_SetMarkerSpritePosition(param0, param1);

    return 1;
}

static BOOL WiFiEarth_HideMarkerSpriteByIndex(WiFiEarthMarkerSprites *param0, u32 param1, WiFiEarthWindowMask *param2)
{
    BOOL v0;

    if (param0->unk_34[param1] == 0) {
        return 1;
    }

    v0 = WiFiEarth_UpdateMarkerAnimation(&param0->unk_00[param1], param2);
    WiFiEarth_SetMarkerSpritePosition(param0, param1);

    if (v0 == 1) {
        Sprite_SetDrawFlag(param0->unk_3C[param0->unk_38[param1]], FALSE);
    }

    return v0;
}

static void WiFiEarth_InitMarkerAnimation(WiFiEarthMarkerAnimation *param0, const WiFiEarthMarkerAnimFrame *param1)
{
    param0->unk_0C = param1;
    param0->unk_00 = param1->unk_00;
    param0->unk_02 = param1->unk_02 + 16;
    param0->unk_04 = 0;
    param0->unk_06 = 0;
    param0->unk_08 = 0;
    param0->unk_0A = 0;
}

static void WiFiEarth_SetMarkerAnimFlagA(WiFiEarthMarkerAnimation *param0, BOOL param1)
{
    param0->unk_08 = param1;
}

static void WiFiEarth_SetMarkerAnimFlagB(WiFiEarthMarkerAnimation *param0, BOOL param1)
{
    param0->unk_0A = param1;
}

static BOOL WiFiEarth_UpdateMarkerAnimation(WiFiEarthMarkerAnimation *param0, WiFiEarthWindowMask *param1)
{
    if (param0->unk_04 > param0->unk_0C->unk_08) {
        return 1;
    }

    WiFiEarth_UpdateMarkerPosition(param0);
    param0->unk_04++;

    if ((param0->unk_06 + 1) > param0->unk_0C->unk_0C) {
        param0->unk_06 = 0;
    } else {
        param0->unk_06++;
    }

    WiFiEarth_UpdateMarkerWindowMask(param0, param1);

    return 0;
}

static void WiFiEarth_RestartMarkerAnimation(WiFiEarthMarkerAnimation *param0, WiFiEarthWindowMask *param1)
{
    param0->unk_04 = 0;
    param0->unk_06 = 0;

    WiFiEarth_UpdateMarkerPosition(param0);
    WiFiEarth_UpdateMarkerWindowMask(param0, param1);
}

static void WiFiEarth_GetMarkerSpritePosition(const WiFiEarthMarkerAnimation *param0, VecFx32 *param1)
{
    param1->x = param0->unk_00 << FX32_SHIFT;
    param1->y = (param0->unk_02 << FX32_SHIFT) + (FX32_CONST(256));
}

static void WiFiEarth_UpdateMarkerPosition(WiFiEarthMarkerAnimation *param0)
{
    u16 v0;
    s16 v1, v2;

    if (param0->unk_0A == 0) {
        v2 = param0->unk_0C->unk_06 - 16;
    } else {
        v2 = param0->unk_0C->unk_06;
    }

    if (param0->unk_08 == 0) {
        v1 = param0->unk_0C->unk_02 + 16;
    } else {
        v1 = param0->unk_0C->unk_02;
    }

    param0->unk_00 = param0->unk_0C->unk_00 + (((param0->unk_0C->unk_04 - param0->unk_0C->unk_00) * param0->unk_04) / param0->unk_0C->unk_08);
    param0->unk_02 = v1 + (((v2 - v1) * param0->unk_04) / param0->unk_0C->unk_08);

    v0 = (param0->unk_06 * 0xffff) / param0->unk_0C->unk_0C;
    param0->unk_00 += FX_Mul(FX32_CONST(param0->unk_0C->unk_0A), FX_SinIdx(v0)) >> FX32_SHIFT;
}

static void WiFiEarth_UpdateMarkerWindowMask(const WiFiEarthMarkerAnimation *param0, WiFiEarthWindowMask *param1)
{
    WiFiEarth_SetWindow0(param1, 0, 0);

    if (param0->unk_08 == 0) {
        if (param0->unk_02 > (param0->unk_0C->unk_02 - 16)) {
            WiFiEarth_SetWindow0(param1, param0->unk_0C->unk_02, param0->unk_0C->unk_02 + 32);
        }
    }

    if (param0->unk_0A == 0) {
        if ((param0->unk_02 - 16) <= param0->unk_0C->unk_06) {
            WiFiEarth_SetWindow0(param1, param0->unk_0C->unk_06 - 32, param0->unk_0C->unk_06);
        }
    }
}

static void WiFiEarth_SetMarkerSpritePosition(WiFiEarthMarkerSprites *param0, u32 param1)
{
    VecFx32 v0;
    Sprite *v1;

    WiFiEarth_GetMarkerSpritePosition(&param0->unk_00[param1], &v0);

    v1 = param0->unk_3C[param0->unk_38[param1]];
    Sprite_SetPosition(v1, &v0);
}

static u16 WiFiEarth_GetMarkerSpriteIndex(u32 param0)
{
    GF_ASSERT(param0 < 24);
    return sMarkerSpriteTable[param0].unk_00;
}

static u16 WiFiEarth_GetMarkerSpriteAnim(u32 param0)
{
    GF_ASSERT(param0 < 24);
    return sMarkerSpriteTable[param0].unk_01;
}

static void WiFiEarth_InitMessageLoader(WiFiEarthMessageLoader *param0, u32 heapID)
{
    param0->unk_00 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0696, heapID);
    param0->unk_04 = StringTemplate_New(8, 64, heapID);
    param0->unk_08 = String_Init(128, heapID);
    param0->unk_0C = String_Init(128, heapID);
}

static void WiFiEarth_FreeMessageLoader(WiFiEarthMessageLoader *param0)
{
    {
        MessageLoader_Free(param0->unk_00);
    }

    {
        StringTemplate_Free(param0->unk_04);
    }

    String_Free(param0->unk_08);
    String_Free(param0->unk_0C);
}

static String *WiFiEarth_GetMessage(WiFiEarthMessageLoader *param0, u32 param1)
{
    MessageLoader_GetString(param0->unk_00, param1, param0->unk_08);
    return param0->unk_08;
}

static void WiFiEarth_GetMessageInto(WiFiEarthMessageLoader *param0, u32 param1, String *param2)
{
    MessageLoader_GetString(param0->unk_00, param1, param2);
}

static String *WiFiEarth_FormatCountryName(WiFiEarthMessageLoader *param0, u32 param1)
{
    MessageLoader_GetString(param0->unk_00, 3, param0->unk_0C);
    StringTemplate_SetCountryName(param0->unk_04, 0, param1);
    StringTemplate_Format(param0->unk_04, param0->unk_08, param0->unk_0C);

    return param0->unk_08;
}

static String *WiFiEarth_FormatCityName(WiFiEarthMessageLoader *param0, u32 param1, u32 param2)
{
    StringTemplate_ClearArgs(param0->unk_04);
    MessageLoader_GetString(param0->unk_00, 3, param0->unk_0C);
    StringTemplate_SetCityName(param0->unk_04, 0, param1, param2);
    StringTemplate_Format(param0->unk_04, param0->unk_08, param0->unk_0C);

    return param0->unk_08;
}

static u32 WiFiEarth_GetPlayerCountryIndex(const UnkStruct_ov66_02231560 *param0)
{
    int v0;
    u8 v1;

    for (v0 = 0; v0 < 50; v0++) {
        v1 = ov66_0223164C(param0, v0);

        if (v1 == 1) {
            return v0;
        }
    }

    return 50;
}
