#include "wifi_lobby_map/wifi_lobby_map_0225D9A4.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"

#include "wifi_menu_app/struct_wifi_menu_app_0222F6EC.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_022324F0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230914.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230E68.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C858.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C9B4.h"
#include "wifi_lobby_map/wifi_lobby_map_02260A70.h"
#include "wifi_lobby_map/wifi_lobby_map_02261E10.h"
#include "wifi_lobby_map/wifi_lobby_map_02262DA8.h"
#include "wifi_lobby_map/wifi_lobby_map_022630A4.h"
#include "wifi_lobby_map/wifi_lobby_map_02269190.h"
#include "wifi_lobby_map/wifi_lobby_map_0226C60C.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_grid_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_camera_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_object_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_task_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_args.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_attraction_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_time_event_manager_decl.h"

#include "bg_window.h"
#include "cell_transfer.h"
#include "char_transfer.h"
#include "comm_manager.h"
#include "enums.h"
#include "error_handling.h"
#include "font.h"
#include "g3d_pipeline.h"
#include "game_options.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "list_menu.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "pltt_transfer.h"
#include "pokemon.h"
#include "render_oam.h"
#include "render_text.h"
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
#include "string_list.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "touch_screen.h"
#include "touch_screen_actions.h"
#include "trainer_info.h"
#include "type_icon.h"
#include "g3_buffer.h"
#include "vram_transfer.h"

typedef struct {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} WiFiLobbyMapTrainerFace;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    s16 unk_04;
    s16 unk_06;
} WiFiLobbyMapMemberSprite;

typedef struct {
    BgConfig *bgConfig;
    SpriteList *spriteList;
    G2dRenderer g2dRenderer;
    SpriteResourceCollection *spriteResources[4];
    NNSG2dCellTransferState *cellTransfer;
    G3DPipelineBuffers *pipeline;
} WiFiLobbyMapRenderer;

typedef struct {
    Window window;
    u32 printer;
    u32 textDelay;
    String *string;
    void *waitDial;
} WiFiLobbyMapMessageBox;

typedef struct {
    ListMenuTemplate template;
    Window window;
    ListMenu *listMenu;
    StringList *stringList;
    u16 stringCount;
    u16 count;
    BOOL showArrows;
    SpriteResource *spriteResources[4];
    Sprite *arrowSprites[2];
} WiFiLobbyMapListMenu;

typedef struct {
    StringList *stringList;
    ListMenuTemplate template;
} WiFiLobbyMapChoiceMenu;

typedef struct {
    Window window;
} WiFiLobbyMapWindow;

typedef struct {
    Window window;
} WiFiLobbyMapTouchPanel;

typedef struct {
    StringTemplate *template;
    MessageLoader *messageLoaders[4];
    String *string;
    String *string2;
} WiFiLobbyMapStringFormatter;

typedef struct {
    s16 unk_00;
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    Window unk_0C;
    TouchScreenActions *unk_1C;
    void *unk_20[3];
    NNSG2dScreenData *unk_2C[3];
} WiFiLobbyMapTouchButton;

typedef struct {
    u32 active;
    Window windows[5];
    Sprite *cursorSprite;
    SpriteResource *cursorResources[4];
    Sprite *pointerSprite;
    SpriteResource *pointerResources[4];
    Sprite *memberSprites[12];
    SpriteResource *memberPalettes[4];
    SpriteResource *memberTiles[12];
    SpriteResource *memberCells[4];
    SpriteResource *memberAnims[4];
} WiFiLobbyMapButtonSprites;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u16 unk_06;
    WiFiLobbyMapButtonSprites unk_08;
    WiFiLobbyMapTouchButton unk_114;
    NARC *unk_14C;
    u16 unk_150;
    u8 unk_152;
    u8 unk_153;
    u16 unk_154;
    u16 unk_156;
} WiFiLobbyMapTouchScreen;

typedef struct {
    u8 unk_00[20];
    u8 unk_14[20];
} WiFiLobbyMapSlotFlags;

typedef struct WiFiLobbyMapApp_t {
    u8 done;
    u8 mode;
    u8 mySlotIndex;
    u8 flag;
    u8 networkActive : 4;
    u8 hasError : 4;
    u8 interactionType;
    u8 lobbyClosed;
    u8 closeHandled;
    s32 exitTimer;
    WiFiLobbyMapSlotFlags slotFlags;
    WiFiPlazaLobbyState *lobbyState;
    WiFiLobbyMapArgs *args;
    WiFiLobbyMapRenderer renderer;
    WiFiLobbyMapTouchScreen touchScreen;
    WiFiLobbyMapStringFormatter stringFormatter;
    WiFiLobbyMapMessageBox messageBox;
    WiFiLobbyMapMessageBox subMessageBox;
    WiFiLobbyMapListMenu listMenu;
    WiFiLobbyMapWindow window;
    WiFiLobbyMapChoiceMenu choiceMenu;
    WiFiLobbyMapTouchPanel touchPanel;
    WiFiLobbyMapAttractionManager *attractionManager;
    BOOL pendingEvent;
    WiFiLobbyMapTimeEventManager *timeEventManager;
    WiFiLobbyMapActorManager *actorManager;
    WiFiLobbyMapObjectManager *objectManager;
    WiFiLobbyMapGrid *grid;
    WiFiLobbyMapCamera *camera;
    WiFiLobbyMapTaskManager *taskManager;
    TrainerInfo *trainerInfo;
} WiFiLobbyMapApp;

static void wifi_lobby_map_0225E4C8(void *param0);
static void wifi_lobby_map_0225E4EC(WiFiLobbyMapRenderer *param0, SaveData *saveData, u32 heapID);
static void wifi_lobby_map_0225E6C0(WiFiLobbyMapRenderer *param0);
static void wifi_lobby_map_0225E6D0(WiFiLobbyMapRenderer *param0);
static void wifi_lobby_map_0225E740(WiFiLobbyMapRenderer *param0);
static void wifi_lobby_map_0225E754(void);
static void wifi_lobby_map_0225E88C(WiFiLobbyMapApp *param0);
static void wifi_lobby_map_0225E92C(WiFiLobbyMapApp *param0);
static void wifi_lobby_map_0225E970(WiFiLobbyMapApp *param0);
static void wifi_lobby_map_0225E9C8(WiFiLobbyMapMessageBox *param0, WiFiLobbyMapRenderer *param1, SaveData *saveData, u32 heapID);
static void wifi_lobby_map_0225EA14(WiFiLobbyMapMessageBox *param0);
static void wifi_lobby_map_0225EA44(WiFiLobbyMapMessageBox *param0, const String *param1);
static void wifi_lobby_map_0225EAA4(WiFiLobbyMapMessageBox *param0, const String *param1);
static void wifi_lobby_map_0225EB08(WiFiLobbyMapMessageBox *param0);
static void wifi_lobby_map_0225EB24(WiFiLobbyMapMessageBox *param0);
static void wifi_lobby_map_0225EB38(WiFiLobbyMapMessageBox *param0);
static BOOL wifi_lobby_map_0225EB4C(const WiFiLobbyMapMessageBox *param0);
static BOOL wifi_lobby_map_0225EB5C(const WiFiLobbyMapMessageBox *param0);
static void wifi_lobby_map_0225EB74(WiFiLobbyMapMessageBox *param0);
static void wifi_lobby_map_0225EBA8(WiFiLobbyMapMessageBox *param0, WiFiLobbyMapRenderer *param1, SaveData *saveData, u32 heapID);
static void wifi_lobby_map_0225EBBC(WiFiLobbyMapMessageBox *param0);
static void wifi_lobby_map_0225EBC4(WiFiLobbyMapMessageBox *param0, const String *param1);
static void wifi_lobby_map_0225EC20(WiFiLobbyMapListMenu *param0, WiFiLobbyMapRenderer *param1, u32 heapID);
static void wifi_lobby_map_0225ED4C(WiFiLobbyMapListMenu *param0, WiFiLobbyMapRenderer *param1);
static void wifi_lobby_map_0225EDA8(WiFiLobbyMapListMenu *param0, u32 param1, u32 heapID, u32 param3);
static void wifi_lobby_map_0225EDE0(WiFiLobbyMapListMenu *param0);
static void wifi_lobby_map_0225EDF8(WiFiLobbyMapListMenu *param0, const String *param1, u32 param2);
static const StringList *wifi_lobby_map_0225EE04(const WiFiLobbyMapListMenu *param0);
static BOOL wifi_lobby_map_0225EE08(const WiFiLobbyMapListMenu *param0, u32 param1);
static void wifi_lobby_map_0225EE30(WiFiLobbyMapListMenu *param0, const ListMenuTemplate *param1, WiFiLobbyMapRenderer *param2, u16 param3, u16 param4, u32 heapID, u8 param6, u8 param7, u8 param8);
static u32 wifi_lobby_map_0225EED8(WiFiLobbyMapListMenu *param0);
static void wifi_lobby_map_0225EF14(WiFiLobbyMapListMenu *param0, u16 *param1, u16 *param2);
static void wifi_lobby_map_0225EF58(ListMenu *param0, u32 param1, u8 param2);
static void wifi_lobby_map_0225EF6C(WiFiLobbyMapListMenu *param0, BOOL param1);
static void wifi_lobby_map_0225EF70(WiFiLobbyMapListMenu *param0);
static void wifi_lobby_map_0225EFD4(WiFiLobbyMapTouchPanel *param0, WiFiLobbyMapRenderer *param1, u32 heapID);
static void wifi_lobby_map_0225EFD8(WiFiLobbyMapTouchPanel *param0);
static void wifi_lobby_map_0225EFE0(WiFiLobbyMapTouchPanel *param0, WiFiLobbyMapRenderer *param1, u32 param2, u8 param3, u8 param4, u8 param5, u8 param6);
static void wifi_lobby_map_0225F024(WiFiLobbyMapTouchPanel *param0);
static void wifi_lobby_map_0225F048(WiFiLobbyMapTouchPanel *param0, const String *param1, u8 param2, u8 param3);
static void wifi_lobby_map_0225F078(WiFiLobbyMapTouchPanel *param0, u16 param1, u16 param2, u16 param3, u16 param4);
static void wifi_lobby_map_0225F098(WiFiLobbyMapChoiceMenu *param0, WiFiLobbyMapStringFormatter *param1, u32 heapID);
static void wifi_lobby_map_0225F100(WiFiLobbyMapChoiceMenu *param0);
static void wifi_lobby_map_0225F114(WiFiLobbyMapWindow *param0, WiFiLobbyMapRenderer *param1, u32 heapID);
static void wifi_lobby_map_0225F144(WiFiLobbyMapWindow *param0);
static void wifi_lobby_map_0225F14C(WiFiLobbyMapWindow *param0, const String *param1);
static void wifi_lobby_map_0225F184(WiFiLobbyMapWindow *param0, WiFiLobbyMapStringFormatter *param1);
static void wifi_lobby_map_0225F1C0(WiFiLobbyMapWindow *param0, WiFiLobbyMapStringFormatter *param1, int param2);
static void wifi_lobby_map_0225F1F0(WiFiLobbyMapWindow *param0, WiFiLobbyMapStringFormatter *param1, int param2);
static void wifi_lobby_map_0225F208(WiFiLobbyMapStringFormatter *param0, u32 heapID);
static void wifi_lobby_map_0225F25C(WiFiLobbyMapStringFormatter *param0);
static String *wifi_lobby_map_0225F288(WiFiLobbyMapStringFormatter *param0, int param1, u32 param2);
static void wifi_lobby_map_0225F2A8(WiFiLobbyMapStringFormatter *param0, u32 param1, u32 param2, u32 param3, int param4);
static void wifi_lobby_map_0225F2C8(WiFiLobbyMapStringFormatter *param0, const TrainerInfo *param1, u32 param2);
static void wifi_lobby_map_0225F2D8(WiFiLobbyMapStringFormatter *param0, enum PlazaMinigame param1, u32 param2);
static void wifi_lobby_map_0225F2E8(WiFiLobbyMapStringFormatter *param0, int param1, u32 param2);
static void wifi_lobby_map_0225F2F8(WiFiLobbyMapStringFormatter *param0, u32 param1, u32 param2);
static void wifi_lobby_map_0225F308(WiFiLobbyMapStringFormatter *param0, u32 param1, u32 param2);
static void wifi_lobby_map_0225F318(WiFiLobbyMapStringFormatter *param0, u32 param1, u32 param2, u32 param3);
static void wifi_lobby_map_0225F32C(WiFiLobbyMapStringFormatter *param0, u32 param1, u16 param2);
static void wifi_lobby_map_0225F338(WiFiLobbyMapStringFormatter *param0);
static void wifi_lobby_map_0225F344(WiFiLobbyMapApp *param0);
static void wifi_lobby_map_0225F350(WiFiLobbyMapTouchScreen *param0, const WiFiLobbyMapArgs *param1, WiFiLobbyMapRenderer *param2, const TrainerInfo *param3, u32 heapID);
static void wifi_lobby_map_0225F3E4(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapRenderer *param2);
static void wifi_lobby_map_0225F418(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapApp *param1, BOOL param2, u32 heapID);
static u32 wifi_lobby_map_0225F798(const WiFiLobbyMapTouchScreen *param0);
static void wifi_lobby_map_0225F79C(WiFiLobbyMapTouchScreen *param0, u32 param1, BOOL param2);
static void wifi_lobby_map_0225F7A8(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1, u32 param2, u32 heapID);
static void wifi_lobby_map_0225F7E0(WiFiLobbyMapTouchScreen *param0);
static void wifi_lobby_map_0225F7EC(WiFiLobbyMapTouchScreen *param0);
static u32 wifi_lobby_map_0225F7F8(const WiFiLobbyMapTouchScreen *param0);
static BOOL wifi_lobby_map_0225F7FC(const WiFiLobbyMapTouchScreen *param0);
static BOOL wifi_lobby_map_0225F814(const WiFiLobbyMapTouchScreen *param0);
static BOOL wifi_lobby_map_0225F828(const WiFiLobbyMapTouchScreen *param0);
static BOOL wifi_lobby_map_0225F834(const WiFiLobbyMapTouchScreen *param0);
static void wifi_lobby_map_0225F844(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapRenderer *param2, WiFiLobbyMapStringFormatter *param3, BOOL param4, u32 heapID, const WiFiPlazaProfile *param6, const WiFiPlazaProfile *param7, BOOL param8, BOOL param9, const WiFiPlazaLobbyPasswordWords *param10, BOOL param11);
static void wifi_lobby_map_0225F89C(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapRenderer *param2);
static void wifi_lobby_map_0225F8AC(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1, WiFiLobbyMapStringFormatter *param2, u32 heapID, const WiFiPlazaProfile *param4);
static void wifi_lobby_map_0225F8F0(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1, u32 heapID, u32 param3);
static void wifi_lobby_map_0225F920(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1);
static void wifi_lobby_map_0225F934(WiFiLobbyMapTouchScreen *param0, BOOL param1);
static void wifi_lobby_map_0225F95C(SysTask *param0, void *param1);
static void wifi_lobby_map_0225F9BC(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 param3, u32 heapID);
static void wifi_lobby_map_0225FA10(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1);
static void wifi_lobby_map_0225FA84(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID);
static void wifi_lobby_map_0225FAA8(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapRenderer *param2);
static void wifi_lobby_map_0225FACC(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapMessageBox *param1);
static void wifi_lobby_map_0225FAD0(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapButtonSprites *param2, WiFiLobbyMapRenderer *param3, WiFiLobbyMapStringFormatter *param4, BOOL param5, NARC *param6, u32 heapID, const WiFiPlazaProfile *param8, const WiFiPlazaProfile *param9, BOOL param10, BOOL param11, const WiFiPlazaLobbyPasswordWords *param12, BOOL param13);
static void wifi_lobby_map_0225FDA0(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapButtonSprites *param1, WiFiLobbyMapRenderer *param2, u32 heapID, const WiFiPlazaProfile *param4);
static void wifi_lobby_map_0225FE80(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapRenderer *param2);
static void wifi_lobby_map_0225FEC4(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID, u32 param4);
static BOOL wifi_lobby_map_0225FEEC(const WiFiLobbyMapButtonSprites *param0);
static void wifi_lobby_map_0225FEF0(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID, u32 param4, BOOL param5);
static void wifi_lobby_map_02260048(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1);
static void wifi_lobby_map_02260080(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID, u32 param4);
static void wifi_lobby_map_02260228(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1);
static void wifi_lobby_map_02260268(NNSG2dPaletteData *param0);
static void wifi_lobby_map_022602C0(WiFiLobbyMapButtonSprites *param0);
static void wifi_lobby_map_022602DC(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapStringFormatter *param1, u32 param2, u32 param3, u8 param4, u8 param5, u32 param6);
static void wifi_lobby_map_02260314(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapStringFormatter *param1, u32 param2, u32 param3, u8 param4, u8 param5, u32 param6);
static void wifi_lobby_map_02260360(WiFiLobbyMapButtonSprites *param0, u32 param1);
static void wifi_lobby_map_02260370(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapStringFormatter *param1, const TrainerInfo *param2);
static void wifi_lobby_map_02260380(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapStringFormatter *param1, const WiFiPlazaProfile *param2);
static void wifi_lobby_map_022603B0(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapStringFormatter *param1, const WiFiPlazaLobbyPasswordWords *param2);
static void wifi_lobby_map_022603CC(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID, const WiFiPlazaProfile *param4, const WiFiPlazaProfile *param5);
static void wifi_lobby_map_0226068C(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1);
static const WiFiLobbyMapMemberSprite *wifi_lobby_map_02260728(int param0, s32 param1, s32 param2, u32 param3);
static void wifi_lobby_map_02260744(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID);
static void wifi_lobby_map_022607A8(WiFiLobbyMapTouchButton *param0);
static BOOL wifi_lobby_map_022607D4(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID);
static void wifi_lobby_map_02260870(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1, WiFiLobbyMapStringFormatter *param2, const WiFiPlazaProfile *param3, NARC *param4, u32 heapID);
static void wifi_lobby_map_02260930(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1, u32 param2, NARC *param3, u32 heapID);
static void wifi_lobby_map_022609A8(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1);
static void wifi_lobby_map_022609D4(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1, u32 param2, NARC *param3, u32 heapID);
static void wifi_lobby_map_02260A50(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void wifi_lobby_map_02260A68(WiFiLobbyMapTouchButton *param0);

static const u8 Unk_wifi_lobby_map_0226D580[2] = {
    0x14,
    0x88
};

static const u16 Unk_wifi_lobby_map_0226D590[2] = {
    0x2E4,
    0x2EC
};

static const u16 Unk_wifi_lobby_map_0226D624[2][2][4] = {
    {
        { 0x2E4, 0x2E5, 0x2E6, 0x2E7 },
        { 0x2E8, 0x2E9, 0x2EA, 0x2EB },
    },
    {
        { 0x2EC, 0x2ED, 0x2EE, 0x2EF },
        { 0x2F0, 0x2F1, 0x2F2, 0x2F3 },
    },
};

static const WindowTemplate Unk_wifi_lobby_map_0226D68C[5] = {
    { 0x6, 0x8, 0x2, 0x10, 0x4, 0x5, 0x140 },
    { 0x6, 0x1, 0x7, 0x1E, 0x6, 0x5, 0x180 },
    { 0x6, 0x1, 0xE, 0x13, 0x4, 0x5, 0x234 },
    { 0x6, 0x1, 0x13, 0x13, 0x4, 0x5, 0x280 },
    { 0x6, 0x0, 0xE, 0x16, 0x8, 0x5, 0x234 },
};

static const WiFiLobbyMapTrainerFace Unk_wifi_lobby_map_0226D724[18] = {
    { 0x0, 0x0, 0x21, 0x23 },
    { 0x61, 0x1, 0x26, 0x24 },
    { 0x3, 0x3C, 0x26, 0x19 },
    { 0x5, 0x6, 0x2C, 0x20 },
    { 0xB, 0x18, 0x26, 0x2C },
    { 0x1F, 0x39, 0x28, 0x28 },
    { 0x32, 0x30, 0x2C, 0x1A },
    { 0x33, 0xE, 0x2C, 0x25 },
    { 0x3E, 0x20, 0x1D, 0x28 },
    { 0x46, 0x31, 0x2A, 0x2C },
    { 0x6, 0x3, 0x27, 0x22 },
    { 0x7, 0xA, 0x28, 0x24 },
    { 0xD, 0x24, 0x26, 0x29 },
    { 0xE, 0x19, 0x24, 0x2A },
    { 0x23, 0x55, 0x26, 0x26 },
    { 0x25, 0x23, 0x26, 0x27 },
    { 0x2A, 0x12, 0x26, 0x23 },
    { 0x3F, 0x21, 0x28, 0x2C }
};

static const WiFiLobbyMapMemberSprite Unk_wifi_lobby_map_0226D844[24] = {
    { 0x0, 0x0, 0x1, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x6, 0x4, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x1, 0x7, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x2, 0xA, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x6, 0xD, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x5, 0x10, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x3, 0x13, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x4, 0x16, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x0, 0x19, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x7, 0x1C, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x4, 0x1F, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x1, 0x22, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x5, 0x25, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x5, 0x28, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x2, 0x2B, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x0, 0x3, 0x2E, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x1, 0x0, 0x67, 0x0, 0x0 },
    { 0x1, 0x1, 0x6A, 0x0, 0x0 },
    { 0x1, 0x0, 0x6D, 0x0, 0x0 },
    { 0x1, 0x0, 0x76, 0x0, 0x0 },
    { 0x1, 0x1, 0x73, 0x0, 0x0 },
    { 0x1, 0x0, 0x70, 0x0, 0x0 },
    { 0x1, 0x1, 0x79, 0x0, 0x0 },
    { 0x1, 0x0, 0x7C, 0x0, 0x0 }
};

static const WiFiLobbyMapMemberSprite Unk_wifi_lobby_map_0226D5FC[2] = {
    { 0x2, 0x0, 0x32, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA },
    { 0x3, 0x0, 0x36, 0xFFFFFFFFFFFFFFF8, 0xFFFFFFFFFFFFFFFA }
};

static const VecFx32 Unk_wifi_lobby_map_0226D7B4[12] = {
    { FX32_CONST(32), FX32_CONST(144) + (256 * FX32_ONE), 0x0 },
    { FX32_CONST(56), FX32_CONST(144) + (256 * FX32_ONE), 0x0 },
    { FX32_CONST(80), FX32_CONST(144) + (256 * FX32_ONE), 0x0 },
    { FX32_CONST(104), FX32_CONST(144) + (256 * FX32_ONE), 0x0 },
    { FX32_CONST(128), FX32_CONST(144) + (256 * FX32_ONE), 0x0 },
    { FX32_CONST(152), FX32_CONST(144) + (256 * FX32_ONE), 0x0 },
    { FX32_CONST(32), FX32_CONST(176) + (256 * FX32_ONE), 0x0 },
    { FX32_CONST(56), FX32_CONST(176) + (256 * FX32_ONE), 0x0 },
    { FX32_CONST(80), FX32_CONST(176) + (256 * FX32_ONE), 0x0 },
    { FX32_CONST(104), FX32_CONST(176) + (256 * FX32_ONE), 0x0 },
    { FX32_CONST(128), FX32_CONST(176) + (256 * FX32_ONE), 0x0 },
    { FX32_CONST(152), FX32_CONST(176) + (256 * FX32_ONE), 0x0 }
};

static const WindowTemplate Unk_wifi_lobby_map_0226D5A4 = {
    0x5,
    0x1,
    0x0,
    0x18,
    0x3,
    0x5,
    0x1D0
};

static const GXRgb Unk_wifi_lobby_map_0226D5EC[8] = {
    GX_RGB(0, 0, 0),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4),
    GX_RGB(4, 4, 4)
};

static const GXBanks Unk_wifi_lobby_map_0226D664 = {
    GX_VRAM_BG_128_B,
    GX_VRAM_BGEXTPLTT_NONE,
    GX_VRAM_SUB_BG_32_H,
    GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_32_FG,
    GX_VRAM_OBJEXTPLTT_NONE,
    GX_VRAM_SUB_OBJ_16_I,
    GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_01_AC,
    GX_VRAM_TEXPLTT_0123_E
};

static const GraphicsModes Unk_wifi_lobby_map_0226D5BC = {
    GX_DISPMODE_GRAPHICS,
    GX_BGMODE_0,
    GX_BGMODE_0,
    GX_BG0_AS_3D
};

static const u32 Unk_wifi_lobby_map_0226D5CC[4] = {
    0x1,
    0x4,
    0x5,
    0x6
};

static const BgTemplate Unk_wifi_lobby_map_0226D6B4[4] = {
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0x7800,
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
        .screenBase = GX_BG_SCRBASE_0x7800,
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
        .screenBase = GX_BG_SCRBASE_0x7000,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x1,
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
        .screenBase = GX_BG_SCRBASE_0x6800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
};

static const CharTransferTemplate Unk_wifi_lobby_map_0226D5DC = {
    0x18,
    0x8000,
    0x4000,
    0x70,
};

static const ListMenuTemplate Unk_wifi_lobby_map_0226D644 = {
    NULL,
    NULL,
    NULL,
    NULL,
    0x0,
    0x2,
    0x0,
    0x8,
    0x0,
    0x0,
    0x1,
    0xF,
    0x2,
    0x0,
    0x10,
    0x0,
    0x0,
    0x0,
    NULL,
};

int wifi_lobby_map_0225D9A4(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMapApp *v0;
    WiFiPlazaLobbyMainAppArgs *v1 = ApplicationManager_Args(appMan);

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_112, 0x3a000);
    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_113, 0x3d000);

    v0 = ApplicationManager_NewData(appMan, sizeof(WiFiLobbyMapApp), HEAP_ID_112);
    memset(v0, 0, sizeof(WiFiLobbyMapApp));

    v0->args = &v1->unk_0C;
    v0->lobbyState = v1->unk_1C;
    v0->mySlotIndex = WiFiPlazaLobby_State_GetMySlotIndex(v0->lobbyState);

    GF_ASSERT(WiFiPlazaLobby_State_GetMySlotIndex(v0->lobbyState) != 0xffffffff);

    RenderControlFlags_SetCanABSpeedUpPrint(TRUE);
    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_DISABLED);
    RenderControlFlags_SetSpeedUpOnTouch(FALSE);

    v0->trainerInfo = SaveData_GetTrainerInfo(v1->saveData);
    wifi_lobby_map_0225E4EC(&v0->renderer, v1->saveData, HEAP_ID_112);
    v0->grid = wifi_lobby_map_0225C858(HEAP_ID_112);

    {
        u32 v2;

        v2 = TrainerInfo_Gender(v0->trainerInfo);
        v0->actorManager = wifi_lobby_map_0225C9B4(24, v2, v0->grid, HEAP_ID_112, HEAP_ID_113);
    }

    v0->objectManager = wifi_lobby_map_02261E10(v1->unk_04, v1->unk_08, v0->grid, HEAP_ID_112, HEAP_ID_113);
    v0->camera = wifi_lobby_map_02260A70(HEAP_ID_112);

    wifi_lobby_map_0225E9C8(&v0->messageBox, &v0->renderer, v1->saveData, HEAP_ID_112);
    wifi_lobby_map_0225EBA8(&v0->subMessageBox, &v0->renderer, v1->saveData, HEAP_ID_112);
    wifi_lobby_map_0225EC20(&v0->listMenu, &v0->renderer, HEAP_ID_112);
    wifi_lobby_map_0225F114(&v0->window, &v0->renderer, HEAP_ID_112);
    wifi_lobby_map_0225EFD4(&v0->touchPanel, &v0->renderer, HEAP_ID_112);
    wifi_lobby_map_0225F208(&v0->stringFormatter, HEAP_ID_112);
    wifi_lobby_map_0225F098(&v0->choiceMenu, &v0->stringFormatter, HEAP_ID_112);
    wifi_lobby_map_0225F350(&v0->touchScreen, v0->args, &v0->renderer, v0->trainerInfo, HEAP_ID_112);

    {
        const WiFiPlazaProfile *v3;

        v3 = WiFiPlazaLobby_State_GetOwnProfile(v0->lobbyState);

        if (WiFiPlazaLobby_State_IsAppearanceRankSet(v3) == 1) {
            wifi_lobby_map_0225F8AC(&v0->touchScreen, &v0->renderer, &v0->stringFormatter, HEAP_ID_112, v3);
        }
    }

    v0->taskManager = wifi_lobby_map_02262DA8(v0, HEAP_ID_112);

    wifi_lobby_map_022630A4(v0);
    wifi_lobby_map_022630EC(v0);

    v0->attractionManager = wifi_lobby_map_02269190(v0->lobbyState, v0->grid, v0->camera, v0->actorManager, HEAP_ID_112, HEAP_ID_113);
    v0->timeEventManager = wifi_lobby_map_0226C60C(HEAP_ID_112, v0);

    SetVBlankCallback(wifi_lobby_map_0225E4C8, v0);
    DisableHBlank();

    return 1;
}

int wifi_lobby_map_0225DB90(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMapApp *v0;
    WiFiPlazaLobbyMainAppArgs *v1;
    BOOL v2;

    v0 = ApplicationManager_Data(appMan);
    v1 = ApplicationManager_Args(appMan);

    switch (*param1) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_112);
        v0->flag = 1;
        (*param1)++;
        break;
    case 1:
        v2 = IsScreenFadeDone();

        if (v2 == 1) {
            v0->flag = 0;
            (*param1)++;
        }
        break;
    case 2:
        if (v0->networkActive == 1) {
            if ((WiFiPlazaLobby_Time_HasWifiError() == 1) || (WiFiPlazaLobby_State_GetErrorFlag(v0->lobbyState) != 0)) {
                v0->hasError = 1;
            }
        }

        if (v0->closeHandled == 0) {
            if (WiFiPlazaLobby_State_IsLobbyCloseFinished(v0->lobbyState) == 1) {
                v0->lobbyClosed = 1;
                wifi_lobby_map_0225DF38(v0, 8);
            }
        }

        if ((v0->done == 1) || (v0->hasError == 1) || (v0->lobbyClosed == 1)) {
            if (v0->hasError) {
                (*param1) = 3;
            } else if (v0->lobbyClosed == 1) {
                (*param1) = 5;
            } else {
                (*param1) = 7;
            }
        }
        break;
    case 3: {
        wifi_lobby_map_0225EB74(&v0->messageBox);
        wifi_lobby_map_0225EF14(&v0->listMenu, NULL, NULL);
        wifi_lobby_map_0225F024(&v0->touchPanel);
        wifi_lobby_map_0225F100(&v0->choiceMenu);

        if (CommManager_CheckWifiError()) {
            wifi_lobby_map_0225F184(&v0->window, &v0->stringFormatter);
        } else if (CommManager_IsWifiPlazaError()) {
            wifi_lobby_map_0225F1C0(&v0->window, &v0->stringFormatter, WiFiPlazaLobby_Network_GetLastError());
        } else {
            wifi_lobby_map_0225F1F0(&v0->window, &v0->stringFormatter, WiFiPlazaLobby_State_GetErrorFlag(v0->lobbyState));
        }
        (*param1) = 4;
    } break;
    case 4:
        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            (*param1) = 7;
        }
        break;
    case 5: {
        wifi_lobby_map_0225EB74(&v0->messageBox);
        wifi_lobby_map_0225EF14(&v0->listMenu, NULL, NULL);
        wifi_lobby_map_0225F024(&v0->touchPanel);
        wifi_lobby_map_0225F100(&v0->choiceMenu);
        wifi_lobby_map_0225EA44(&v0->messageBox, wifi_lobby_map_0225F288(&v0->stringFormatter, 1, 70));
        (*param1) = 6;
        v0->exitTimer = 60;
    } break;
    case 6:
        if (wifi_lobby_map_0225EB5C(&v0->messageBox)) {
            v0->exitTimer--;

            if (v0->exitTimer <= 0) {
                (*param1) = 7;
            }
        }
        break;
    case 7: {
        u32 v3;

        v3 = wifi_lobby_map_0225F798(&v0->touchScreen);

        if (v3 == 5) {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_112);
            v0->flag = 1;
            (*param1)++;
            break;
        }

        if (v3 == 0) {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_112);
            v0->flag = 1;
            (*param1)++;
            break;
        }
    } break;
    case 8:
        v2 = IsScreenFadeDone();

        if (v2 == 1) {
            v0->flag = 0;
            return 1;
        }
        break;
    }

    wifi_lobby_map_0225E88C(v0);
    wifi_lobby_map_0225E92C(v0);

    return 0;
}

int wifi_lobby_map_0225DDF8(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMapApp *v0 = ApplicationManager_Data(appMan);
    WiFiPlazaLobbyMainAppArgs *v1 = ApplicationManager_Args(appMan);

    {
        v1->unk_18 = v0->mode;
    }

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    wifi_lobby_map_0226C6F8(v0->timeEventManager);
    wifi_lobby_map_02269204(v0->attractionManager);
    wifi_lobby_map_02262DF4(v0->taskManager);
    wifi_lobby_map_0225F3E4(&v0->touchScreen, &v0->subMessageBox, &v0->renderer);
    wifi_lobby_map_0225F25C(&v0->stringFormatter);
    wifi_lobby_map_0225EA14(&v0->messageBox);
    wifi_lobby_map_0225EBBC(&v0->subMessageBox);
    wifi_lobby_map_0225ED4C(&v0->listMenu, &v0->renderer);
    wifi_lobby_map_0225F144(&v0->window);
    wifi_lobby_map_0225F100(&v0->choiceMenu);
    wifi_lobby_map_0225EFD8(&v0->touchPanel);
    wifi_lobby_map_02260AD4(v0->camera);
    wifi_lobby_map_022621AC(v0->objectManager);
    wifi_lobby_map_0225CA20(v0->actorManager);
    wifi_lobby_map_0225C894(v0->grid);
    wifi_lobby_map_0225E6D0(&v0->renderer);

    Heap_Free(v0);
    Heap_Destroy(HEAP_ID_112);
    Heap_Destroy(HEAP_ID_113);
    Sound_StopAllEffects(0);
    Sound_StopPokemonCries(0);

    return 1;
}

WiFiPlazaLobbyState *wifi_lobby_map_0225DEE8(WiFiLobbyMapApp *param0)
{
    return param0->lobbyState;
}

WiFiLobbyMapArgs *wifi_lobby_map_0225DEEC(WiFiLobbyMapApp *param0)
{
    return param0->args;
}

WiFiLobbyMapActorManager *wifi_lobby_map_0225DEF0(WiFiLobbyMapApp *param0)
{
    return param0->actorManager;
}

WiFiLobbyMapObjectManager *wifi_lobby_map_0225DEF8(WiFiLobbyMapApp *param0)
{
    return param0->objectManager;
}

WiFiLobbyMapGrid *wifi_lobby_map_0225DF00(WiFiLobbyMapApp *param0)
{
    return param0->grid;
}

WiFiLobbyMapCamera *wifi_lobby_map_0225DF08(WiFiLobbyMapApp *param0)
{
    return param0->camera;
}

WiFiLobbyMapTaskManager *wifi_lobby_map_0225DF10(WiFiLobbyMapApp *param0)
{
    return param0->taskManager;
}

void wifi_lobby_map_0225DF18(WiFiLobbyMapApp *param0, BOOL param1)
{
    param0->networkActive = param1;
}

u32 wifi_lobby_map_0225DF2C(const WiFiLobbyMapApp *param0)
{
    return param0->mySlotIndex;
}

BOOL wifi_lobby_map_0225DF30(const WiFiLobbyMapApp *param0)
{
    return param0->flag;
}

void wifi_lobby_map_0225DF34(WiFiLobbyMapApp *param0, BOOL param1)
{
    param0->done = param1;
}

void wifi_lobby_map_0225DF38(WiFiLobbyMapApp *param0, u8 param1)
{
    param0->mode = param1;
}

void wifi_lobby_map_0225DF3C(WiFiLobbyMapApp *param0, u8 param1)
{
    param0->interactionType = param1;
}

u8 wifi_lobby_map_0225DF40(const WiFiLobbyMapApp *param0)
{
    return param0->interactionType;
}

void wifi_lobby_map_0225DF44(WiFiLobbyMapApp *param0)
{
    param0->closeHandled = 1;
}

void wifi_lobby_map_0225DF4C(WiFiLobbyMapApp *param0, u8 param1, BOOL param2)
{
    GF_ASSERT(param1 < 20);
    param0->slotFlags.unk_00[param1] = param2;
}

BOOL wifi_lobby_map_0225DF64(const WiFiLobbyMapApp *param0, u8 param1)
{
    return param0->slotFlags.unk_00[param1];
}

void wifi_lobby_map_0225DF6C(WiFiLobbyMapApp *param0, u8 param1, BOOL param2)
{
    GF_ASSERT(param1 < 20);
    param0->slotFlags.unk_14[param1] = param2;
}

BOOL wifi_lobby_map_0225DF84(const WiFiLobbyMapApp *param0, u8 param1)
{
    return param0->slotFlags.unk_14[param1];
}

void wifi_lobby_map_0225DF8C(WiFiLobbyMapApp *param0, const String *param1)
{
    wifi_lobby_map_0225EA44(&param0->messageBox, param1);
}

void wifi_lobby_map_0225DF9C(WiFiLobbyMapApp *param0, const String *param1)
{
    wifi_lobby_map_0225EAA4(&param0->messageBox, param1);
}

BOOL wifi_lobby_map_0225DFAC(const WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225EB5C(&param0->messageBox);
}

void wifi_lobby_map_0225DFBC(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EB08(&param0->messageBox);
}

void wifi_lobby_map_0225DFCC(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EB24(&param0->messageBox);
}

BOOL wifi_lobby_map_0225DFDC(const WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225EB4C(&param0->messageBox);
}

void wifi_lobby_map_0225DFEC(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EB74(&param0->messageBox);
}

void wifi_lobby_map_0225DFFC(WiFiLobbyMapApp *param0, const String *param1)
{
    wifi_lobby_map_0225EBC4(&param0->subMessageBox, param1);
}

void wifi_lobby_map_0225E00C(WiFiLobbyMapApp *param0, u32 param1)
{
    wifi_lobby_map_0225EDA8(&param0->listMenu, param1, HEAP_ID_113, 0);
}

void wifi_lobby_map_0225E020(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    wifi_lobby_map_0225EDA8(&param0->listMenu, param1, HEAP_ID_113, param2);
}

void wifi_lobby_map_0225E034(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EDE0(&param0->listMenu);
}

void wifi_lobby_map_0225E044(WiFiLobbyMapApp *param0, const String *param1, u32 param2)
{
    wifi_lobby_map_0225EDF8(&param0->listMenu, param1, param2);
}

const StringList *wifi_lobby_map_0225E054(const WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225EE04(&param0->listMenu);
}

BOOL wifi_lobby_map_0225E064(const WiFiLobbyMapApp *param0, u32 param1)
{
    return wifi_lobby_map_0225EE08(&param0->listMenu, param1);
}

void wifi_lobby_map_0225E074(WiFiLobbyMapApp *param0, const ListMenuTemplate *param1, u16 param2, u16 param3)
{
    wifi_lobby_map_0225EE30(&param0->listMenu, param1, &param0->renderer, param2, param3, HEAP_ID_112, 16, 3, 15);
}

extern void wifi_lobby_map_0225E0A4(WiFiLobbyMapApp *param0, const ListMenuTemplate *param1, u16 param2, u16 param3, u8 param4, u8 param5, u8 param6)
{
    wifi_lobby_map_0225EE30(&param0->listMenu, param1, &param0->renderer, param2, param3, HEAP_ID_112, param4, param5, param6);
}

u32 wifi_lobby_map_0225E0D4(WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225EED8(&param0->listMenu);
}

void wifi_lobby_map_0225E0E4(WiFiLobbyMapApp *param0, u16 *param1, u16 *param2)
{
    wifi_lobby_map_0225EF14(&param0->listMenu, param1, param2);
}

void wifi_lobby_map_0225E0F4(WiFiLobbyMapApp *param0, BOOL param1)
{
    wifi_lobby_map_0225EF6C(&param0->listMenu, param1);
}

void wifi_lobby_map_0225E104(WiFiLobbyMapApp *param0, u8 param1, u8 param2, u8 param3, u8 param4)
{
    wifi_lobby_map_0225EFE0(&param0->touchPanel, &param0->renderer, 112, param1, param2, param3, param4);
}

void wifi_lobby_map_0225E12C(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225F024(&param0->touchPanel);
}

void wifi_lobby_map_0225E13C(WiFiLobbyMapApp *param0, const String *param1, u8 param2, u8 param3)
{
    wifi_lobby_map_0225F048(&param0->touchPanel, param1, param2, param3);
}

void wifi_lobby_map_0225E14C(WiFiLobbyMapApp *param0, u16 param1, u16 param2, u16 param3, u16 param4)
{
    wifi_lobby_map_0225F078(&param0->touchPanel, param1, param2, param3, param4);
}

void wifi_lobby_map_0225E164(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EE30(&param0->listMenu, &param0->choiceMenu.template, &param0->renderer, 0, 0, HEAP_ID_112, 25, 13, 6);
}

void wifi_lobby_map_0225E194(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EE30(&param0->listMenu, &param0->choiceMenu.template, &param0->renderer, 0, 1, HEAP_ID_112, 25, 13, 6);
}

int wifi_lobby_map_0225E1C4(WiFiLobbyMapApp *param0)
{
    u32 v0 = wifi_lobby_map_0225EED8(&param0->listMenu);

    switch (v0) {
    case 0xfffffffe:
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
    case 1:
        return 1;
    case 0:
        return 0;
    default:
        break;
    }

    return 2;
}

void wifi_lobby_map_0225E1F8(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EF14(&param0->listMenu, NULL, NULL);
}

String *wifi_lobby_map_0225E20C(WiFiLobbyMapApp *param0, int param1, u32 param2)
{
    return wifi_lobby_map_0225F288(&param0->stringFormatter, param1, param2);
}

void wifi_lobby_map_0225E21C(WiFiLobbyMapApp *param0, u32 param1, u32 param2, u32 param3, int param4)
{
    wifi_lobby_map_0225F2A8(&param0->stringFormatter, param1, param2, param3, param4);
}

void wifi_lobby_map_0225E234(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    TrainerInfo *v0;
    const WiFiPlazaProfile *v1;

    v0 = TrainerInfo_New(HEAP_ID_112);

    if (param1 == WiFiPlazaLobby_State_GetMySlotIndex(param0->lobbyState)) {
        v1 = WiFiPlazaLobby_State_GetOwnProfile(param0->lobbyState);
    } else {
        v1 = WiFiPlazaLobby_State_GetProfileBySlot(param0->lobbyState, param1);
    }

    WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v1, v0, HEAP_ID_112);
    wifi_lobby_map_0225F2C8(&param0->stringFormatter, v0, param2);
    Heap_Free(v0);
}

void wifi_lobby_map_0225E27C(WiFiLobbyMapApp *param0, enum PlazaMinigame param1, u32 param2)
{
    wifi_lobby_map_0225F2D8(&param0->stringFormatter, param1, param2);
}

void wifi_lobby_map_0225E28C(WiFiLobbyMapApp *param0, int param1, u32 param2)
{
    wifi_lobby_map_0225F2E8(&param0->stringFormatter, param1, param2);
}

void wifi_lobby_map_0225E29C(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    wifi_lobby_map_0225F2F8(&param0->stringFormatter, param1, param2);
}

void wifi_lobby_map_0225E2AC(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    StringTemplate_SetJPGreeting(param0->stringFormatter.template, param1, param2);
}

void wifi_lobby_map_0225E2BC(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    StringTemplate_SetENGreeting(param0->stringFormatter.template, param1, param2);
}

void wifi_lobby_map_0225E2CC(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    StringTemplate_SetFRGreeting(param0->stringFormatter.template, param1, param2);
}

void wifi_lobby_map_0225E2DC(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    StringTemplate_SetITGreeting(param0->stringFormatter.template, param1, param2);
}

void wifi_lobby_map_0225E2EC(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    StringTemplate_SetDEGreeting(param0->stringFormatter.template, param1, param2);
}

void wifi_lobby_map_0225E2FC(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    StringTemplate_SetESGreeting(param0->stringFormatter.template, param1, param2);
}

void wifi_lobby_map_0225E30C(WiFiLobbyMapApp *param0, u32 param1, int param2)
{
    param2 = WiFiPlazaLobby_Time_GetTypeIconIndex(param2);
    StringTemplate_SetPokemonTypeName(param0->stringFormatter.template, param1, param2);
}

void wifi_lobby_map_0225E328(WiFiLobbyMapApp *param0, u32 param1, BOOL param2)
{
    if ((wifi_lobby_map_0225F7F8(&param0->touchScreen) == param1) && (wifi_lobby_map_0225F7FC(&param0->touchScreen) == 1) && (wifi_lobby_map_0225F834(&param0->touchScreen) == 0) && (wifi_lobby_map_0225F828(&param0->touchScreen) == param2)) {
        return;
    }

    wifi_lobby_map_0225F79C(&param0->touchScreen, param1, param2);
}

void wifi_lobby_map_0225E378(WiFiLobbyMapApp *param0, u32 param1)
{
    wifi_lobby_map_0225F7A8(&param0->touchScreen, &param0->renderer, param1, HEAP_ID_112);
}

void wifi_lobby_map_0225E390(WiFiLobbyMapApp *param0)
{
    const WiFiPlazaProfile *v0;
    u32 v1;

    if (wifi_lobby_map_0225F7FC(&param0->touchScreen) == 0) {
        return;
    }

    v1 = wifi_lobby_map_0225F7F8(&param0->touchScreen);
    v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0->lobbyState, v1);

    wifi_lobby_map_0225FDA0(&param0->touchScreen, &param0->touchScreen.unk_08, &param0->renderer, HEAP_ID_112, v0);
}

void wifi_lobby_map_0225E3D0(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225F7E0(&param0->touchScreen);
}

u32 wifi_lobby_map_0225E3E0(const WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225F7F8(&param0->touchScreen);
}

BOOL wifi_lobby_map_0225E3F0(const WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225F7FC(&param0->touchScreen);
}

BOOL wifi_lobby_map_0225E400(const WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225F814(&param0->touchScreen);
}

void wifi_lobby_map_0225E410(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225F7EC(&param0->touchScreen);
}

BOOL wifi_lobby_map_0225E420(const WiFiLobbyMapApp *param0, u32 param1)
{
    return wifi_lobby_map_0226C810(param0->timeEventManager, param1, 1);
}

void wifi_lobby_map_0225E430(WiFiLobbyMapApp *param0)
{
    param0->touchScreen.unk_06 = 1;
}

void wifi_lobby_map_0225E43C(WiFiLobbyMapApp *param0, BOOL param1)
{
    wifi_lobby_map_0225F934(&param0->touchScreen, param1);
}

void wifi_lobby_map_0225E44C(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_02260A68(&param0->touchScreen.unk_114);
}

BOOL wifi_lobby_map_0225E45C(WiFiLobbyMapApp *param0)
{
    BOOL v0 = param0->pendingEvent;
    param0->pendingEvent = 0;

    return v0;
}

void wifi_lobby_map_0225E46C(WiFiLobbyMapApp *param0, u32 param1)
{
    const WiFiPlazaProfile *v0;
    u32 v1;

    GF_ASSERT(param1 < 20);

    v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0->lobbyState, param1);
    v1 = WiFiPlazaLobby_State_GetAppearanceRank(v0);

    wifi_lobby_map_02269268(param0->attractionManager, param1, v1);

    if (param1 == WiFiPlazaLobby_State_GetMySlotIndex(param0->lobbyState)) {
        WiFiPlazaLobby_State_BroadcastCosmeticID(param0->lobbyState, v1);
    }
}

BOOL wifi_lobby_map_0225E4AC(const WiFiLobbyMapApp *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    return wifi_lobby_map_02269298(param0->attractionManager, param1);
}

static void wifi_lobby_map_0225E4C8(void *param0)
{
    WiFiLobbyMapApp *v0 = param0;

    wifi_lobby_map_022622A4(v0->objectManager);
    wifi_lobby_map_0225CAE0(v0->actorManager);
    wifi_lobby_map_0225E740(&v0->renderer);
}

static void wifi_lobby_map_0225E4EC(WiFiLobbyMapRenderer *param0, SaveData *saveData, u32 heapID)
{
    G2_BlendNone();
    G2S_BlendNone();

    VramTransfer_New(32, heapID);
    GXLayers_SetBanks(&Unk_wifi_lobby_map_0226D664);
    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;
    GXLayers_SwapDisplay();

    {
        Bg_MaskPalette(BG_LAYER_MAIN_0, 0);
    }

    {
        int v0;

        SetAllGraphicsModes(&Unk_wifi_lobby_map_0226D5BC);
        param0->bgConfig = BgConfig_New(heapID);

        for (v0 = 0; v0 < 4; v0++) {
            Bg_InitFromTemplate(param0->bgConfig, Unk_wifi_lobby_map_0226D5CC[v0], &Unk_wifi_lobby_map_0226D6B4[v0], 0);
            Bg_ClearTilesRange(Unk_wifi_lobby_map_0226D5CC[v0], 32, 0, heapID);
            Bg_ClearTilemap(param0->bgConfig, Unk_wifi_lobby_map_0226D5CC[v0]);
        }
    }

    {
        Options *options = SaveData_GetOptions(saveData);
        u8 v2 = Options_Frame(options);

        Font_LoadTextPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(5), heapID);
        Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(4), heapID);

        LoadStandardWindowGraphics(param0->bgConfig, Unk_wifi_lobby_map_0226D5CC[0], (1 + (18 + 12)) + ((18 + 12) + 24), 3, 0, heapID);
        LoadMessageBoxGraphics(param0->bgConfig, Unk_wifi_lobby_map_0226D5CC[0], 1, 1, v2, heapID);
        LoadSignpostContentGraphics(param0->bgConfig, Unk_wifi_lobby_map_0226D5CC[0], 1 + (18 + 12), 2, SIGNPOST_TYPE_SCROLLING, 0, heapID);

        Graphics_LoadPalette(NARC_INDEX_GRAPHIC__WIFI_LOBBY_OTHER, 90, 0, 2 * 32, 32, heapID);
    }

    {
        int v3;

        NNS_G2dInitOamManagerModule();

        RenderOam_Init(0, 126, 0, 31, 0, 126, 0, 31, heapID);
        CharTransfer_InitWithVramModes(&Unk_wifi_lobby_map_0226D5DC, GX_OBJVRAMMODE_CHAR_1D_32K, GX_OBJVRAMMODE_CHAR_1D_64K);
        PlttTransfer_Init(24, heapID);

        CharTransfer_ClearBuffers();
        PlttTransfer_Clear();

        ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_32K);
        ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

        NetworkIcon_Init();
        param0->spriteList = SpriteList_InitRendering(24, &param0->g2dRenderer, heapID);
        SetSubScreenViewRect(&param0->g2dRenderer, 0, 256 * FX32_ONE);

        for (v3 = 0; v3 < 4; v3++) {
            param0->spriteResources[v3] = SpriteResourceCollection_New(24, v3, heapID);
        }

        param0->cellTransfer = CellTransfer_New(24, heapID);

        GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
    }

    {
        param0->pipeline = G3DPipeline_Init(heapID, TEXTURE_VRAM_SIZE_256K, PALETTE_VRAM_SIZE_64K, wifi_lobby_map_0225E754);
    }
}

static void wifi_lobby_map_0225E6C0(WiFiLobbyMapRenderer *param0)
{
    SpriteList_Update(param0->spriteList);
    CellTransfer_Update();
}

static void wifi_lobby_map_0225E6D0(WiFiLobbyMapRenderer *param0)
{
    VramTransfer_Free();

    {
        int v0;

        for (v0 = 0; v0 < 4; v0++) {
            Bg_FreeTilemapBuffer(param0->bgConfig, Unk_wifi_lobby_map_0226D5CC[v0]);
        }

        Heap_Free(param0->bgConfig);
    }

    {
        int v1;

        CellTransfer_Free(param0->cellTransfer);
        param0->cellTransfer = NULL;

        for (v1 = 0; v1 < 4; v1++) {
            SpriteResourceCollection_Delete(param0->spriteResources[v1]);
        }

        SpriteList_Delete(param0->spriteList);
        CharTransfer_Free();
        PlttTransfer_Free();
        RenderOam_Free();
    }

    {
        G3DPipelineBuffers_Free(param0->pipeline);
    }
}

static void wifi_lobby_map_0225E740(WiFiLobbyMapRenderer *param0)
{
    Bg_RunScheduledUpdates(param0->bgConfig);
    RenderOam_Transfer();
    VramTransfer_Process();
}

static void wifi_lobby_map_0225E754(void)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);

    G2_SetBG0Priority(1);

    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(1);
    G3X_AlphaTest(0, 0);
    G3X_AlphaBlend(1);
    G3X_EdgeMarking(1);
    G3X_SetEdgeColorTable(Unk_wifi_lobby_map_0226D5EC);
    G3X_SetFog(0, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0);
    G3X_SetClearColor(GX_RGB(26, 26, 26), 0, 0x7fff, 63, 0);
    G3_ViewPort(0, 0, 255, 191);

    {
        VecFx16 v0;

        {
            NNS_G3dGlbLightVector(0, 0xfffff805, 0xfffff224, 0x6e);
        }

        {
            VEC_Fx16Set(&v0, 0, 0, FX16_ONE);
            VEC_Fx16Normalize(&v0, &v0);
            NNS_G3dGlbLightVector(1, v0.x, v0.y, v0.z);
        }

        {
            VEC_Fx16Set(&v0, 0, 0, FX16_ONE);
            VEC_Fx16Normalize(&v0, &v0);
            NNS_G3dGlbLightVector(2, v0.x, v0.y, v0.z);
            NNS_G3dGlbLightColor(2, GX_RGB(31, 31, 31));
        }

        {
            VEC_Fx16Set(&v0, 0, 0, FX16_ONE);
            VEC_Fx16Normalize(&v0, &v0);
            NNS_G3dGlbLightVector(3, v0.x, v0.y, v0.z);
            NNS_G3dGlbLightColor(3, GX_RGB(31, 31, 31));
        }
    }
}

static void wifi_lobby_map_0225E88C(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225CA44(param0->actorManager);

    if ((param0->hasError == 0) && (param0->lobbyClosed == 0)) {
        {
            wifi_lobby_map_02262E20(param0->taskManager);
        }
    }

    wifi_lobby_map_02262210(param0->objectManager);

    if ((param0->hasError == 0) && (param0->lobbyClosed == 0)) {
        wifi_lobby_map_0225CA5C(param0->actorManager);

        {
            wifi_lobby_map_02262E2C(param0->taskManager);
        }

        wifi_lobby_map_0226C718(param0->timeEventManager);
    }

    wifi_lobby_map_0225E970(param0);

    if (param0->flag == 0) {
        BOOL v0;

        if ((param0->hasError == 1) || (param0->lobbyClosed == 1) || (param0->done == 1)) {
            v0 = 1;
        } else {
            v0 = 0;
        }

        wifi_lobby_map_0225F418(&param0->touchScreen, param0, v0, HEAP_ID_112);
    }

    wifi_lobby_map_02269220(param0->attractionManager);
}

static void wifi_lobby_map_0225E92C(WiFiLobbyMapApp *param0)
{
    MtxFx44 v0;

    G3_ResetG3X();

    wifi_lobby_map_02260AEC(param0->camera);
    wifi_lobby_map_02262298(param0->objectManager);
    wifi_lobby_map_0225CAD4(param0->actorManager);
    wifi_lobby_map_02269240(param0->attractionManager);

    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);

    wifi_lobby_map_0225E6C0(&param0->renderer);
}

static void wifi_lobby_map_0225E970(WiFiLobbyMapApp *param0)
{
    int v0;
    BOOL v1;
    BOOL v2;
    u32 v3;
    u32 v4;
    BOOL v5 = WiFiPlazaLobby_State_IsMinigameFinished(param0->lobbyState);

    for (v0 = 0; v0 < WiFiPlazaLobbyNetworkGameKind_03; v0++) {
        v2 = WiFiPlazaLobby_Network_IsGameRecruiting(v0);

        if (v2 == 1) {
            if (WiFiPlazaLobby_Network_IsRecruitAcceptingPlayers(v0) == 0) {
                v1 = 1;
            } else {
                v1 = 0;
            }
        } else {
            v1 = 0;
        }

        v3 = WiFiPlazaLobby_Network_GetRecruitPlayerCount(v0);
        wifi_lobby_map_022627BC(param0->objectManager, WiFiPlazaLobbyActivity_00 + v0, v3, v2, v1, v5);
    }
}

static void wifi_lobby_map_0225E9C8(WiFiLobbyMapMessageBox *param0, WiFiLobbyMapRenderer *param1, SaveData *saveData, u32 heapID)
{
    Window_Add(param1->bgConfig, &param0->window, Unk_wifi_lobby_map_0226D5CC[0], 2, 19, 27, 4, 4, ((1 + (18 + 12)) + ((18 + 12) + 24)) + 9);
    Window_FillTilemap(&param0->window, 15);

    param0->string = String_Init(384, heapID);
    param0->textDelay = Options_TextFrameDelay(SaveData_GetOptions(saveData));
}

static void wifi_lobby_map_0225EA14(WiFiLobbyMapMessageBox *param0)
{
    if (Text_IsPrinterActive(param0->printer)) {
        Text_RemovePrinter(param0->printer);
    }

    wifi_lobby_map_0225EB38(param0);

    String_Free(param0->string);
    Window_Remove(&param0->window);
}

static void wifi_lobby_map_0225EA44(WiFiLobbyMapMessageBox *param0, const String *param1)
{
    if (Text_IsPrinterActive(param0->printer)) {
        Text_RemovePrinter(param0->printer);
    }

    Window_FillTilemap(&param0->window, 15);
    String_Copy(param0->string, param1);

    param0->printer = Text_AddPrinterWithParamsAndColor(&param0->window, FONT_MESSAGE, param0->string, 0, 0, param0->textDelay, TEXT_COLOR(1, 2, 15), NULL);

    Window_DrawMessageBoxWithScrollCursor(&param0->window, 1, 1, 1);
}

static void wifi_lobby_map_0225EAA4(WiFiLobbyMapMessageBox *param0, const String *param1)
{
    if (Text_IsPrinterActive(param0->printer)) {
        Text_RemovePrinter(param0->printer);
    }

    Window_FillTilemap(&param0->window, 15);
    String_Copy(param0->string, param1);
    Text_AddPrinterWithParamsAndColor(&param0->window, FONT_MESSAGE, param0->string, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
    Window_DrawMessageBoxWithScrollCursor(&param0->window, 1, 1, 1);
    Window_ScheduleCopyToVRAM(&param0->window);
}

static void wifi_lobby_map_0225EB08(WiFiLobbyMapMessageBox *param0)
{
    GF_ASSERT(param0->waitDial == NULL);
    param0->waitDial = Window_AddWaitDial(&param0->window, 1);
}

static void wifi_lobby_map_0225EB24(WiFiLobbyMapMessageBox *param0)
{
    if (param0->waitDial != NULL) {
        DestroyWaitDial(param0->waitDial);
        param0->waitDial = NULL;
    }
}

static void wifi_lobby_map_0225EB38(WiFiLobbyMapMessageBox *param0)
{
    if (param0->waitDial != NULL) {
        DestroyWaitDialTaskOnly(param0->waitDial);
        param0->waitDial = NULL;
    }
}

static BOOL wifi_lobby_map_0225EB4C(const WiFiLobbyMapMessageBox *param0)
{
    if (param0->waitDial != NULL) {
        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_0225EB5C(const WiFiLobbyMapMessageBox *param0)
{
    if (Text_IsPrinterActive(param0->printer) == 0) {
        return 1;
    }

    return 0;
}

static void wifi_lobby_map_0225EB74(WiFiLobbyMapMessageBox *param0)
{
    if (Text_IsPrinterActive(param0->printer)) {
        Text_RemovePrinter(param0->printer);
    }

    wifi_lobby_map_0225EB38(param0);

    Window_EraseMessageBox(&param0->window, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->window);
}

static void wifi_lobby_map_0225EBA8(WiFiLobbyMapMessageBox *param0, WiFiLobbyMapRenderer *param1, SaveData *saveData, u32 heapID)
{
    wifi_lobby_map_0225E9C8(param0, param1, saveData, heapID);
    Window_SetPalette(&param0->window, 2);
}

static void wifi_lobby_map_0225EBBC(WiFiLobbyMapMessageBox *param0)
{
    wifi_lobby_map_0225EA14(param0);
}

static void wifi_lobby_map_0225EBC4(WiFiLobbyMapMessageBox *param0, const String *param1)
{
    if (Text_IsPrinterActive(param0->printer)) {
        Text_RemovePrinter(param0->printer);
    }

    Window_FillTilemap(&param0->window, 15);
    String_Copy(param0->string, param1);

    param0->printer = Text_AddPrinterWithParams(&param0->window, FONT_MESSAGE, param0->string, 0, 0, param0->textDelay, NULL);

    Window_DrawSignpost(&param0->window, 1, 1 + (18 + 12), 2, 3);
}

static void wifi_lobby_map_0225EC20(WiFiLobbyMapListMenu *param0, WiFiLobbyMapRenderer *param1, u32 heapID)
{
    SpriteResourcesHeader v0;
    SpriteListTemplate v1;
    int v2;
    NARC *v3 = NARC_ctor(NARC_INDEX_GRAPHIC__SHOP_GRA, heapID);

    param0->spriteResources[0] = SpriteResourceCollection_AddTilesFrom(param1->spriteResources[0], v3, 4, 0, 5000, NNS_G2D_VRAM_TYPE_2DMAIN, heapID);
    param0->spriteResources[1] = SpriteResourceCollection_AddPaletteFrom(param1->spriteResources[1], v3, 10, 0, 5000, NNS_G2D_VRAM_TYPE_2DMAIN, 1, heapID);
    param0->spriteResources[2] = SpriteResourceCollection_AddFrom(param1->spriteResources[2], v3, 5, 0, 5000, 2, heapID);
    param0->spriteResources[3] = SpriteResourceCollection_AddFrom(param1->spriteResources[3], v3, 6, 0, 5000, 3, heapID);

    NARC_dtor(v3);
    SpriteTransfer_RequestCharAtEnd(param0->spriteResources[0]);
    SpriteTransfer_RequestPlttFreeSpace(param0->spriteResources[1]);
    SpriteResourcesHeader_Init(&v0, 5000, 5000, 5000, 5000, 0xffffffff, 0xffffffff, 0, 0, param1->spriteResources[0], param1->spriteResources[1], param1->spriteResources[2], param1->spriteResources[3], NULL, NULL);

    v1.list = param1->spriteList;
    v1.resourceData = &v0;
    v1.priority = 0;
    v1.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v1.heapID = heapID;
    v1.position.x = 192 * FX32_ONE;

    for (v2 = 0; v2 < 2; v2++) {
        v1.position.y = Unk_wifi_lobby_map_0226D580[v2] * FX32_ONE;
        param0->arrowSprites[v2] = SpriteList_Add(&v1);

        Sprite_SetAnim(param0->arrowSprites[v2], v2);
        Sprite_SetAnimateFlag(param0->arrowSprites[v2], 1);
        Sprite_SetDrawFlag(param0->arrowSprites[v2], FALSE);
    }

    param0->showArrows = 0;
}

static void wifi_lobby_map_0225ED4C(WiFiLobbyMapListMenu *param0, WiFiLobbyMapRenderer *param1)
{
    int v0;

    if (param0->stringList != NULL) {
        wifi_lobby_map_0225EDE0(param0);
    }

    if (param0->listMenu != NULL) {
        wifi_lobby_map_0225EF14(param0, NULL, NULL);
    }

    for (v0 = 0; v0 < 2; v0++) {
        Sprite_Delete(param0->arrowSprites[v0]);
        param0->arrowSprites[v0] = NULL;
    }

    SpriteTransfer_ResetCharTransfer(param0->spriteResources[0]);
    SpriteTransfer_ResetPlttTransfer(param0->spriteResources[1]);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Remove(param1->spriteResources[v0], param0->spriteResources[v0]);
    }
}

static void wifi_lobby_map_0225EDA8(WiFiLobbyMapListMenu *param0, u32 param1, u32 heapID, u32 param3)
{
    int v0;
    GF_ASSERT(param0->stringList == NULL);
    param0->stringList = StringList_New(param1, heapID);
    param0->stringCount = param1;

    for (v0 = 0; v0 < param1; v0++) {
        param0->stringList[v0].index = param3;
    }
}

static void wifi_lobby_map_0225EDE0(WiFiLobbyMapListMenu *param0)
{
    if (param0->stringList != NULL) {
        StringList_Free(param0->stringList);
        param0->stringList = NULL;
        param0->stringCount = 0;
    }
}

static void wifi_lobby_map_0225EDF8(WiFiLobbyMapListMenu *param0, const String *param1, u32 param2)
{
    StringList_AddFromString(param0->stringList, param1, param2);
}

static const StringList *wifi_lobby_map_0225EE04(const WiFiLobbyMapListMenu *param0)
{
    return param0->stringList;
}

static BOOL wifi_lobby_map_0225EE08(const WiFiLobbyMapListMenu *param0, u32 param1)
{
    int v0;

    for (v0 = 0; v0 < param0->stringCount; v0++) {
        if (param0->stringList[v0].index == param1) {
            return 1;
        }
    }

    return 0;
}

static void wifi_lobby_map_0225EE30(WiFiLobbyMapListMenu *param0, const ListMenuTemplate *param1, WiFiLobbyMapRenderer *param2, u16 param3, u16 param4, u32 heapID, u8 param6, u8 param7, u8 param8)
{
    GF_ASSERT(param0->listMenu == NULL);
    GF_ASSERT((param1->maxDisplay * 2) < 18);

    param0->template = *param1;
    param0->template.window = &param0->window;
    param0->count = param1->count;
    param0->template.cursorCallback = wifi_lobby_map_0225EF58;

    Window_Add(param2->bgConfig, &param0->window, Unk_wifi_lobby_map_0226D5CC[0], param6, param7, param8, param1->maxDisplay * 2, 5, (((1 + (18 + 12)) + ((18 + 12) + 24)) + 9) + (27 * 4));
    Window_FillTilemap(&param0->window, 15);
    Window_DrawStandardFrame(&param0->window, 1, (1 + (18 + 12)) + ((18 + 12) + 24), 3);

    param0->listMenu = ListMenu_New(&param0->template, param3, param4, heapID);

    Window_ScheduleCopyToVRAM(&param0->window);
}

static u32 wifi_lobby_map_0225EED8(WiFiLobbyMapListMenu *param0)
{
    u32 v0;

    if (param0->listMenu == NULL) {
        return 0xfffffffe;
    }

    v0 = ListMenu_ProcessInput(param0->listMenu);

    switch (v0) {
    case 0xffffffff:
    case 0xfffffffe:
        wifi_lobby_map_0225EF70(param0);
        break;
    default:
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
        break;
    }

    return v0;
}

static void wifi_lobby_map_0225EF14(WiFiLobbyMapListMenu *param0, u16 *param1, u16 *param2)
{
    int v0;

    if (param0->listMenu == NULL) {
        return;
    }

    ListMenu_Free(param0->listMenu, param1, param2);

    param0->listMenu = NULL;

    Window_EraseStandardFrame(&param0->window, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->window);
    Window_Remove(&param0->window);

    param0->showArrows = 0;

    for (v0 = 0; v0 < 2; v0++) {
        Sprite_SetDrawFlag(param0->arrowSprites[v0], FALSE);
    }
}

static void wifi_lobby_map_0225EF58(ListMenu *param0, u32 param1, u8 param2)
{
    if (param2 == 0) {
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
    }
}

static void wifi_lobby_map_0225EF6C(WiFiLobbyMapListMenu *param0, BOOL param1)
{
    param0->showArrows = param1;
}

static void wifi_lobby_map_0225EF70(WiFiLobbyMapListMenu *param0)
{
    u16 v0;

    if (param0->showArrows == 0) {
        Sprite_SetDrawFlag(param0->arrowSprites[0], FALSE);
        Sprite_SetDrawFlag(param0->arrowSprites[1], FALSE);
        return;
    }

    ListMenu_GetListAndCursorPos(param0->listMenu, &v0, NULL);

    if (v0 <= 0) {
        Sprite_SetDrawFlag(param0->arrowSprites[0], FALSE);
    } else {
        Sprite_SetDrawFlag(param0->arrowSprites[0], TRUE);
    }

    if (v0 >= (param0->count - 7)) {
        Sprite_SetDrawFlag(param0->arrowSprites[1], FALSE);
    } else {
        Sprite_SetDrawFlag(param0->arrowSprites[1], TRUE);
    }
}

static void wifi_lobby_map_0225EFD4(WiFiLobbyMapTouchPanel *param0, WiFiLobbyMapRenderer *param1, u32 heapID)
{
    return;
}

static void wifi_lobby_map_0225EFD8(WiFiLobbyMapTouchPanel *param0)
{
    wifi_lobby_map_0225F024(param0);
}

static void wifi_lobby_map_0225EFE0(WiFiLobbyMapTouchPanel *param0, WiFiLobbyMapRenderer *param1, u32 param2, u8 param3, u8 param4, u8 param5, u8 param6)
{
    Window_Add(param1->bgConfig, &param0->window, Unk_wifi_lobby_map_0226D5CC[0], param3, param4, param5, param6, 5, (((1 + (18 + 12)) + ((18 + 12) + 24)) + 9) + (27 * 4));
    Window_DrawStandardFrame(&param0->window, 1, (1 + (18 + 12)) + ((18 + 12) + 24), 3);
    Window_FillTilemap(&param0->window, 15);
    Window_ScheduleCopyToVRAM(&param0->window);
}

static void wifi_lobby_map_0225F024(WiFiLobbyMapTouchPanel *param0)
{
    if (Window_IsInUse(&param0->window) == 1) {
        Window_EraseStandardFrame(&param0->window, 1);
        Window_ClearAndScheduleCopyToVRAM(&param0->window);
        Window_Remove(&param0->window);
    }
}

static void wifi_lobby_map_0225F048(WiFiLobbyMapTouchPanel *param0, const String *param1, u8 param2, u8 param3)
{
    Text_AddPrinterWithParamsAndColor(&param0->window, FONT_SYSTEM, param1, param2, param3, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
    Window_ScheduleCopyToVRAM(&param0->window);
}

static void wifi_lobby_map_0225F078(WiFiLobbyMapTouchPanel *param0, u16 param1, u16 param2, u16 param3, u16 param4)
{
    Window_FillRectWithColor(&param0->window, 15, param1, param2, param3, param4);
}

static void wifi_lobby_map_0225F098(WiFiLobbyMapChoiceMenu *param0, WiFiLobbyMapStringFormatter *param1, u32 heapID)
{
    String *v0;

    GF_ASSERT(param0->stringList == NULL);
    param0->stringList = StringList_New(2, heapID);

    v0 = wifi_lobby_map_0225F288(param1, 1, 67);
    StringList_AddFromString(param0->stringList, v0, 0);
    v0 = wifi_lobby_map_0225F288(param1, 1, 66);
    StringList_AddFromString(param0->stringList, v0, 1);

    param0->template = Unk_wifi_lobby_map_0226D644;
    param0->template.count = 2;
    param0->template.choices = param0->stringList;
}

static void wifi_lobby_map_0225F100(WiFiLobbyMapChoiceMenu *param0)
{
    if (param0->stringList != NULL) {
        StringList_Free(param0->stringList);
        param0->stringList = NULL;
    }
}

static void wifi_lobby_map_0225F114(WiFiLobbyMapWindow *param0, WiFiLobbyMapRenderer *param1, u32 heapID)
{
    Window_Add(param1->bgConfig, &param0->window, Unk_wifi_lobby_map_0226D5CC[0], 4, 4, 23, 16, 5, ((1 + (18 + 12)) + ((18 + 12) + 24)) + 9);
    Window_FillTilemap(&param0->window, 15);
}

static void wifi_lobby_map_0225F144(WiFiLobbyMapWindow *param0)
{
    Window_Remove(&param0->window);
}

static void wifi_lobby_map_0225F14C(WiFiLobbyMapWindow *param0, const String *param1)
{
    Text_AddPrinterWithParamsAndColor(&param0->window, FONT_SYSTEM, param1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
    Window_DrawStandardFrame(&param0->window, 1, (1 + (18 + 12)) + ((18 + 12) + 24), 3);
    Window_ScheduleCopyToVRAM(&param0->window);
}

static void wifi_lobby_map_0225F184(WiFiLobbyMapWindow *param0, WiFiLobbyMapStringFormatter *param1)
{
    u32 v0;
    String *v1;
    WiFiCommErrorInfo *v2 = CommManager_GetUnk34();
    v0 = WiFiPlazaLobby_Time_GetWFCErrorMessageID(v2->unk_00, v2->unk_04);

    wifi_lobby_map_0225F2A8(param1, v2->unk_00, 5, 0, 2);
    v1 = wifi_lobby_map_0225F288(param1, 2, v0);
    wifi_lobby_map_0225F14C(param0, v1);
}

static void wifi_lobby_map_0225F1C0(WiFiLobbyMapWindow *param0, WiFiLobbyMapStringFormatter *param1, int param2)
{
    u32 v0;
    s32 v1;
    String *v2;

    v1 = WiFiPlazaLobby_Network_ToErrorCode(param2);
    wifi_lobby_map_0225F2A8(param1, v1, 5, 0, 2);
    v2 = wifi_lobby_map_0225F288(param1, 2, 32);

    wifi_lobby_map_0225F14C(param0, v2);
}

static void wifi_lobby_map_0225F1F0(WiFiLobbyMapWindow *param0, WiFiLobbyMapStringFormatter *param1, int param2)
{
    String *v0 = wifi_lobby_map_0225F288(param1, 2, 14);
    wifi_lobby_map_0225F14C(param0, v0);
}

static void wifi_lobby_map_0225F208(WiFiLobbyMapStringFormatter *param0, u32 heapID)
{
    int v0;
    static const u32 v1[4] = {
        672, 673, 695, 662
    };

    param0->template = StringTemplate_New(8, 64, heapID);

    for (v0 = 0; v0 < 4; v0++) {
        param0->messageLoaders[v0] = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, v1[v0], heapID);
    }

    param0->string = String_Init(480, heapID);
    param0->string2 = String_Init(480, heapID);
}

static void wifi_lobby_map_0225F25C(WiFiLobbyMapStringFormatter *param0)
{
    int v0;

    StringTemplate_Free(param0->template);

    for (v0 = 0; v0 < 4; v0++) {
        MessageLoader_Free(param0->messageLoaders[v0]);
    }

    String_Free(param0->string);
    String_Free(param0->string2);
}

static String *wifi_lobby_map_0225F288(WiFiLobbyMapStringFormatter *param0, int param1, u32 param2)
{
    MessageLoader_GetString(param0->messageLoaders[param1], param2, param0->string2);
    StringTemplate_Format(param0->template, param0->string, param0->string2);
    return param0->string;
}

static void wifi_lobby_map_0225F2A8(WiFiLobbyMapStringFormatter *param0, u32 param1, u32 param2, u32 param3, int param4)
{
    StringTemplate_SetNumber(param0->template, param3, param1, param2, param4, 1);
}

static void wifi_lobby_map_0225F2C8(WiFiLobbyMapStringFormatter *param0, const TrainerInfo *param1, u32 param2)
{
    StringTemplate_SetPlayerName(param0->template, param2, param1);
}

static void wifi_lobby_map_0225F2D8(WiFiLobbyMapStringFormatter *param0, enum PlazaMinigame param1, u32 param2)
{
    StringTemplate_SetPlazaMinigameName(param0->template, param2, param1);
}

static void wifi_lobby_map_0225F2E8(WiFiLobbyMapStringFormatter *param0, int param1, u32 param2)
{
    StringTemplate_SetPlazaEventName(param0->template, param2, param1);
}

static void wifi_lobby_map_0225F2F8(WiFiLobbyMapStringFormatter *param0, u32 param1, u32 param2)
{
    StringTemplate_SetPlazaItemName(param0->template, param2, param1);
}

static void wifi_lobby_map_0225F308(WiFiLobbyMapStringFormatter *param0, u32 param1, u32 param2)
{
    StringTemplate_SetCountryName(param0->template, param2, param1);
}

static void wifi_lobby_map_0225F318(WiFiLobbyMapStringFormatter *param0, u32 param1, u32 param2, u32 param3)
{
    StringTemplate_SetCityName(param0->template, param3, param1, param2);
}

static void wifi_lobby_map_0225F32C(WiFiLobbyMapStringFormatter *param0, u32 param1, u16 param2)
{
    StringTemplate_SetEasyChatWord(param0->template, param1, param2);
}

static void wifi_lobby_map_0225F338(WiFiLobbyMapStringFormatter *param0)
{
    StringTemplate_ClearArgs(param0->template);
}

static void wifi_lobby_map_0225F344(WiFiLobbyMapApp *param0)
{
    param0->pendingEvent = 1;
}

static void wifi_lobby_map_0225F350(WiFiLobbyMapTouchScreen *param0, const WiFiLobbyMapArgs *param1, WiFiLobbyMapRenderer *param2, const TrainerInfo *param3, u32 heapID)
{
    u32 v0 = TrainerInfo_Gender(param3);

    param0->unk_14C = NARC_ctor(NARC_INDEX_GRAPHIC__WIFI_LOBBY_OTHER, heapID);

    wifi_lobby_map_0225F9BC(param0, param2, param0->unk_14C, v0, heapID);
    wifi_lobby_map_0225FA84(&param0->unk_08, param2, param0->unk_14C, heapID);
    wifi_lobby_map_02260744(&param0->unk_114, param2, param0->unk_14C, heapID);

    param0->unk_02 = 0;
    param0->unk_01 = 0;

    if (param1->taskType == 0) {
        param0->unk_00 = 0;

        Bg_MaskPalette(BG_LAYER_SUB_0, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
    } else {
        param0->unk_00 = 5;
    }
}

static void wifi_lobby_map_0225F3E4(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapRenderer *param2)
{
    wifi_lobby_map_022607A8(&param0->unk_114);
    wifi_lobby_map_0225FAA8(&param0->unk_08, param1, param2);
    wifi_lobby_map_0225FA10(param0, param2);

    NARC_dtor(param0->unk_14C);
}

static void wifi_lobby_map_0225F418(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapApp *param1, BOOL param2, u32 heapID)
{
    WiFiPlazaLobbyState *v0;
    WiFiLobbyMapRenderer *v1;
    WiFiLobbyMapStringFormatter *v2;
    BOOL v3;

    v0 = param1->lobbyState;
    v1 = &param1->renderer;
    v2 = &param1->stringFormatter;

    switch (param0->unk_00) {
    case 0:
        if (param0->unk_06 == 1) {
            param0->unk_00++;
        }
        break;
    case 1:
        StartScreenFade(FADE_SUB_ONLY, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_WHITE, 4, 1, heapID);
        param0->unk_00++;
        break;
    case 2:
        if (IsScreenFadeDone() == TRUE) {
            {
                const WiFiPlazaProfile *v4;

                v4 = WiFiPlazaLobby_State_GetOwnProfile(v0);
                wifi_lobby_map_0225F8AC(param0, v1, &param1->stringFormatter, heapID, v4);
                param0->unk_01 = 4;
            }

            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
            param0->unk_00++;
        }
        break;
    case 3:
        StartScreenFade(FADE_SUB_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_WHITE, 6, 1, heapID);
        param0->unk_00++;
        break;
    case 4:
        if (IsScreenFadeDone() == TRUE) {
            param0->unk_00++;
        }
        break;
    case 5:
        if (param2 == 1) {
            break;
        }

        switch (param0->unk_01) {
        case 1:
            v3 = wifi_lobby_map_022607D4(&param0->unk_114, v1, param0->unk_14C, heapID);

            if (v3 == 1) {
                wifi_lobby_map_0225F344(param1);
            }
            break;
        case 4:
            break;
        case 3:
            if (param0->unk_153) {
                if (wifi_lobby_map_0226C810(param1->timeEventManager, param0->unk_150, param0->unk_152) == 0) {
                    param0->unk_153 = 0;
                    wifi_lobby_map_02260A68(&param0->unk_114);
                }
            }

            v3 = wifi_lobby_map_022607D4(&param0->unk_114, v1, param0->unk_14C, heapID);

            if (v3 == 1) {
                WiFiPlazaLobby_State_SetFloatSlotTrigger(v0, WiFiPlazaLobby_State_GetMySlotIndex(v0));
                WiFiPlazaLobby_State_SendFloatTriggerEvent(v0);

                {
                    u32 v5, v6, v7;

                    v5 = WiFiPlazaLobby_State_FindFloatSlotByUserID(v0, WiFiPlazaLobby_State_GetMySlotIndex(v0));
                    WiFiPlazaLobby_State_FloatSlotToRowCol(v5, &v6, &v7);

                    param0->unk_153 = 1;
                    param0->unk_150 = v6;
                    param0->unk_152 = v7;
                }
            }
            break;
        case 2:
            wifi_lobby_map_0225FACC(&param0->unk_08, &param1->subMessageBox);
            break;
        default:
            break;
        }

        if (param0->unk_02 != 0) {
            param0->unk_00++;
        }
        break;
    case 6:
        StartScreenFade(FADE_SUB_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 3, 1, heapID);
        param0->unk_00++;
        break;
    case 7:
        if (IsScreenFadeDone() == TRUE) {
            switch (param0->unk_01) {
            case 1:
            case 4:
            case 3:
                wifi_lobby_map_0225F920(param0, v1);
                break;
            case 2:
                wifi_lobby_map_0225F89C(param0, &param1->subMessageBox, v1);
                break;
            }

            param0->unk_00++;
        }
        break;
    case 8: {
        const WiFiPlazaProfile *v8;
        BOOL v9;
        BOOL v10;
        const WiFiPlazaLobbyPasswordWords *v11;

        switch (param0->unk_02) {
        case 1:
        case 4:
            v8 = WiFiPlazaLobby_State_GetOwnProfile(v0);
            wifi_lobby_map_0225F8AC(param0, v1, &param1->stringFormatter, heapID, v8);
            break;
        case 2: {
            BOOL v12;
            const WiFiPlazaProfile *v13;

            v13 = WiFiPlazaLobby_State_GetOwnProfile(v0);

            if (param0->unk_03 == WiFiPlazaLobby_State_GetMySlotIndex(v0)) {
                v8 = WiFiPlazaLobby_State_GetOwnProfile(v0);
                v12 = 1;
            } else {
                v8 = WiFiPlazaLobby_State_GetProfileBySlot(v0, param0->unk_03);
                v12 = 0;
            }

            v9 = WiFiPlazaLobby_State_IsMemberPresent(v0, param0->unk_03);

            if (param0->unk_04 == 1) {
                v10 = WiFiPlazaLobby_State_HasMemberPassword(v0, param0->unk_03);
                v11 = WiFiPlazaLobby_State_GetMemberPassword(v0, param0->unk_03);

                if (v11 == NULL) {
                    v10 = 0;
                }
            } else {
                v10 = 0;
                v11 = NULL;
            }

            wifi_lobby_map_0225F844(param0, &param1->subMessageBox, v1, v2, v12, heapID, v8, v13, v9, v10, v11, 1);
        } break;
        case 3: {
            u32 v14;
            u32 v15;
            u32 v16;

            v14 = WiFiPlazaLobby_State_FindFloatSlotByUserID(v0, WiFiPlazaLobby_State_GetMySlotIndex(v0));

            if (v14 == 0xffffffff) {
                GF_ASSERT(FALSE);

                v14 = 0;
            }

            WiFiPlazaLobby_State_FloatSlotToRowCol(v14, &v15, &v16);
            wifi_lobby_map_0225F8F0(param0, v1, heapID, v16);
        } break;
        }

        param0->unk_02 = 0;
        param0->unk_00++;
    } break;
    case 9:
        StartScreenFade(FADE_SUB_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 3, 1, heapID);

        if (param0->unk_01 == 2) {
            wifi_lobby_map_0225FACC(&param0->unk_08, &param1->subMessageBox);
        }

        param0->unk_00++;
        break;
    case 10:
        if (IsScreenFadeDone() == TRUE) {
            param0->unk_00 = 5;
        }
        break;
    }
}

static u32 wifi_lobby_map_0225F798(const WiFiLobbyMapTouchScreen *param0)
{
    return param0->unk_00;
}

static void wifi_lobby_map_0225F79C(WiFiLobbyMapTouchScreen *param0, u32 param1, BOOL param2)
{
    param0->unk_02 = 2;
    param0->unk_03 = param1;
    param0->unk_04 = param2;
}

static void wifi_lobby_map_0225F7A8(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1, u32 param2, u32 heapID)
{
    GF_ASSERT(param2 < 27);
    GF_ASSERT(param0->unk_01 == 2);

    if (param0->unk_01 == 2) {
        wifi_lobby_map_0225FEC4(&param0->unk_08, param1, param0->unk_14C, heapID, param2);
    }
}

static void wifi_lobby_map_0225F7E0(WiFiLobbyMapTouchScreen *param0)
{
    if (param0->unk_01 != 1) {
        param0->unk_02 = 1;
    }
}

static void wifi_lobby_map_0225F7EC(WiFiLobbyMapTouchScreen *param0)
{
    if (param0->unk_01 != 3) {
        param0->unk_02 = 3;
    }
}

static u32 wifi_lobby_map_0225F7F8(const WiFiLobbyMapTouchScreen *param0)
{
    return param0->unk_03;
}

static BOOL wifi_lobby_map_0225F7FC(const WiFiLobbyMapTouchScreen *param0)
{
    if (param0->unk_02 == 2) {
        return 1;
    }

    if (param0->unk_01 == 2) {
        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_0225F814(const WiFiLobbyMapTouchScreen *param0)
{
    if ((param0->unk_02 == 0) && (param0->unk_01 == 2)) {
        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_0225F828(const WiFiLobbyMapTouchScreen *param0)
{
    return wifi_lobby_map_0225FEEC(&param0->unk_08);
}

static BOOL wifi_lobby_map_0225F834(const WiFiLobbyMapTouchScreen *param0)
{
    if (param0->unk_02 != 0) {
        return 1;
    }

    return 0;
}

static void wifi_lobby_map_0225F844(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapRenderer *param2, WiFiLobbyMapStringFormatter *param3, BOOL param4, u32 heapID, const WiFiPlazaProfile *param6, const WiFiPlazaProfile *param7, BOOL param8, BOOL param9, const WiFiPlazaLobbyPasswordWords *param10, BOOL param11)
{
    if (param0->unk_01 == 2) {
        wifi_lobby_map_0225F89C(param0, param1, param2);
    }

    wifi_lobby_map_0225FAD0(param0, param1, &param0->unk_08, param2, param3, param4, param0->unk_14C, heapID, param6, param7, param8, param9, param10, param11);
    param0->unk_01 = 2;
}

static void wifi_lobby_map_0225F89C(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapRenderer *param2)
{
    wifi_lobby_map_0225FE80(&param0->unk_08, param1, param2);
    param0->unk_01 = 0;
}

static void wifi_lobby_map_0225F8AC(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1, WiFiLobbyMapStringFormatter *param2, u32 heapID, const WiFiPlazaProfile *param4)
{
    if ((param0->unk_01 == 1) || (param0->unk_01 == 4) || (param0->unk_01 == 3)) {
        wifi_lobby_map_0225F920(param0, param1);
    }

    wifi_lobby_map_02260870(&param0->unk_114, param1, param2, param4, param0->unk_14C, heapID);
    param0->unk_01 = 1;
}

static void wifi_lobby_map_0225F8F0(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1, u32 heapID, u32 param3)
{
    if (param0->unk_01 == 3) {
        wifi_lobby_map_0225F920(param0, param1);
    }

    wifi_lobby_map_02260930(&param0->unk_114, param1, param3, param0->unk_14C, heapID);
    param0->unk_01 = 3;
}

static void wifi_lobby_map_0225F920(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1)
{
    wifi_lobby_map_022609A8(&param0->unk_114, param1);
    param0->unk_01 = 0;
}

static void wifi_lobby_map_0225F934(WiFiLobbyMapTouchScreen *param0, BOOL param1)
{
    param0->unk_114.unk_06 = param1;
}

static void wifi_lobby_map_0225F940(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1, u32 param2, u32 heapID)
{
    param0->unk_154 = param2;
    param0->unk_156 = heapID;

    SysTask_ExecuteAfterVBlank(wifi_lobby_map_0225F95C, param0, 0);
}

static void wifi_lobby_map_0225F95C(SysTask *param0, void *param1)
{
    WiFiLobbyMapTouchScreen *v0 = param1;

    {
        Graphics_LoadPaletteFromOpenNARC(v0->unk_14C, v0->unk_154, 4, 0, 0, v0->unk_156);
    }

    {
        Font_LoadTextPalette(PAL_LOAD_SUB_BG, PLTT_OFFSET(5), v0->unk_156);
    }

    {
        Graphics_LoadPalette(TypeIcon_GetNARC(), TypeIcon_GetPlttSrc(), 4, 11 * 32, 3 * 32, v0->unk_156);
    }

    SysTask_Done(param0);
}

static void wifi_lobby_map_0225F9BC(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 param3, u32 heapID)
{
    {
        if (param3 == 0) {
            Graphics_LoadPaletteFromOpenNARC(param2, 86, 4, 0, 0, heapID);
        } else {
            Graphics_LoadPaletteFromOpenNARC(param2, 87, 4, 0, 0, heapID);
        }

        Graphics_LoadTilesToBgLayerFromOpenNARC(param2, 54, param1->bgConfig, Unk_wifi_lobby_map_0226D5CC[1], 0, 0, 0, heapID);
    }

    {
        Font_LoadTextPalette(PAL_LOAD_SUB_BG, PLTT_OFFSET(5), heapID);
    }
}

static void wifi_lobby_map_0225FA10(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapRenderer *param1)
{
    return;
}

static void wifi_lobby_map_0225FA14(WiFiLobbyMapRenderer *param0, NARC *param1, u32 param2, u32 param3, u32 param4, u32 heapID)
{
    void *v0;
    NNSG2dScreenData *v1;

    v0 = Graphics_GetScrnDataFromOpenNARC(param1, param2, 0, &v1, heapID);

    {
        int v2;
        u16 *v3;
        int v4;

        v4 = v1->szByte / 2;
        v3 = (u16 *)v1->rawData;

        for (v2 = 0; v2 < v4; v2++) {
            v3[v2] += param4;
        }
    }

    Bg_LoadToTilemapRect(param0->bgConfig, param3, v1->rawData, 0, 0, v1->screenWidth / 8, v1->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param0->bgConfig, param3);
    Heap_Free(v0);
}

static void wifi_lobby_map_0225FA84(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID)
{
    {
        int v0;

        for (v0 = 0; v0 < 5; v0++) {
            Window_AddFromTemplate(param1->bgConfig, &param0->windows[v0], &Unk_wifi_lobby_map_0226D68C[v0]);
        }
    }
}

static void wifi_lobby_map_0225FAA8(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapRenderer *param2)
{
    if (param0->cursorSprite != NULL) {
        wifi_lobby_map_0225FE80(param0, param1, param2);
    }

    {
        int v0;

        for (v0 = 0; v0 < 5; v0++) {
            Window_Remove(&param0->windows[v0]);
        }
    }
}

static void wifi_lobby_map_0225FACC(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapMessageBox *param1)
{
    return;
}

static void wifi_lobby_map_0225FAD0(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapButtonSprites *param2, WiFiLobbyMapRenderer *param3, WiFiLobbyMapStringFormatter *param4, BOOL param5, NARC *param6, u32 heapID, const WiFiPlazaProfile *param8, const WiFiPlazaProfile *param9, BOOL param10, BOOL param11, const WiFiPlazaLobbyPasswordWords *param12, BOOL param13)
{
    u32 v0;
    TrainerInfo *v1;

    wifi_lobby_map_0225F338(param4);

    if (WiFiPlazaProfile_GetGender(param8) == 0) {
        v0 = TEXT_COLOR(7, 8, 0);

        if (param10 == 0) {
            wifi_lobby_map_0225F940(param0, param3, 86, heapID);
        } else {
            wifi_lobby_map_0225F940(param0, param3, 88, heapID);
        }
    } else {
        v0 = TEXT_COLOR(3, 4, 0);

        if (param10 == 0) {
            wifi_lobby_map_0225F940(param0, param3, 87, heapID);
        } else {
            wifi_lobby_map_0225F940(param0, param3, 88, heapID);
        }
    }

    Bg_ScheduleFillTilemap(param3->bgConfig, Unk_wifi_lobby_map_0226D5CC[1], 0);
    Bg_ScheduleFillTilemap(param3->bgConfig, Unk_wifi_lobby_map_0226D5CC[2], 0);
    Bg_ScheduleFillTilemap(param3->bgConfig, Unk_wifi_lobby_map_0226D5CC[3], 0);

    wifi_lobby_map_022602C0(param2);
    wifi_lobby_map_0225FA14(param3, param6, 92, Unk_wifi_lobby_map_0226D5CC[1], 0, heapID);

    v1 = TrainerInfo_New(heapID);
    WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(param8, v1, heapID);

    {
        u32 v2;

        wifi_lobby_map_022602DC(param2, param4, 0, 44, 0, 0, v0);
        wifi_lobby_map_0225F2A8(param4, TrainerInfo_ID_LowHalf(v1), 5, 0, 2);
        wifi_lobby_map_02260314(param2, param4, 0, 49, 122, 0, TEXT_COLOR(1, 2, 0));
        wifi_lobby_map_022602DC(param2, param4, 0, 45, 0, 16, v0);
        wifi_lobby_map_02260370(param2, param4, v1);
        wifi_lobby_map_02260314(param2, param4, 0, 50, 122, 16, TEXT_COLOR(1, 2, 0));
        wifi_lobby_map_02260360(param2, 0);
    }

    {
        wifi_lobby_map_022602DC(param2, param4, 1, 46, 0, 0, v0);

        if (WiFiPlazaLobby_State_GetCountry(param8) == 0) {
            wifi_lobby_map_022602DC(param2, param4, 1, 55, 32, 16, TEXT_COLOR(1, 2, 0));
        } else {
            wifi_lobby_map_02260380(param2, param4, param8);
            wifi_lobby_map_022602DC(param2, param4, 1, 51, 32, 16, TEXT_COLOR(1, 2, 0));
        }

        wifi_lobby_map_02260360(param2, 1);
    }

    if (param11) {
        param2->active = 1;

        wifi_lobby_map_02260370(param2, param4, v1);
        wifi_lobby_map_022602DC(param2, param4, 4, 56, 8, 0, v0);
        wifi_lobby_map_022603B0(param2, param4, param12);
        wifi_lobby_map_022602DC(param2, param4, 4, 59, 6, 24, TEXT_COLOR(1, 2, 0));
        wifi_lobby_map_022602DC(param2, param4, 4, 60, 90, 24, TEXT_COLOR(1, 2, 0));
        wifi_lobby_map_022602DC(param2, param4, 4, 61, 6, 44, TEXT_COLOR(1, 2, 0));
        wifi_lobby_map_022602DC(param2, param4, 4, 62, 90, 44, TEXT_COLOR(1, 2, 0));
        wifi_lobby_map_02260360(param2, 4);
    } else {
        param2->active = 0;

        wifi_lobby_map_022602DC(param2, param4, 4, 48, 8, 0, v0);
        wifi_lobby_map_02260360(param2, 4);
        wifi_lobby_map_022603CC(param2, param3, param6, heapID, param8, param9);
    }

    wifi_lobby_map_0225FEF0(param2, param3, param6, heapID, WiFiPlazaLobby_State_GetAppearanceRank(param8), param13);

    {
        u32 v3;

        if (param5 == 1) {
            if (WiFiPlazaProfile_GetGender(param8) == 1) {
                v3 = 0x61;
            } else {
                v3 = 0x0;
            }
        } else {
            v3 = WiFiPlazaProfile_GetTrainerAppearanceGraphicsID(param8);
        }

        wifi_lobby_map_02260080(param2, param3, param6, heapID, v3);
    }

    wifi_lobby_map_0225FDA0(param0, param2, param3, heapID, param8);

    Heap_Free(v1);
}

static void wifi_lobby_map_0225FDA0(WiFiLobbyMapTouchScreen *param0, WiFiLobbyMapButtonSprites *param1, WiFiLobbyMapRenderer *param2, u32 heapID, const WiFiPlazaProfile *param4)
{
    u16 v0;
    int v1;
    u16 v2;
    void *v3;
    NNSG2dCharacterData *v4;

    for (v1 = 0; v1 < 2; v1++) {
        v0 = WiFiPlazaLobby_State_GetProfilePokemonType(param4, v1);

        if (v0 != 0) {
            v2 = WiFiPlazaLobby_Time_GetTypeIconIndex(v0);
            v3 = LoadMemberFromNARC(TypeIcon_GetNARC(), TypeIcon_GetChar(v2), 1, heapID, 1);

            NNS_G2dGetUnpackedCharacterData(v3, &v4);

            Bg_LoadTiles(param2->bgConfig, Unk_wifi_lobby_map_0226D5CC[3], v4->pRawData, 4 * 2 * 32, Unk_wifi_lobby_map_0226D590[v1]);
            Heap_Free(v3);
            Bg_CopyToTilemapRect(param2->bgConfig, Unk_wifi_lobby_map_0226D5CC[3], 26, 2 + (2 * v1), 4, 2, Unk_wifi_lobby_map_0226D624[v1], 0, 0, 4, 2);
            Bg_ChangeTilemapRectPalette(param2->bgConfig, Unk_wifi_lobby_map_0226D5CC[3], 26, 2 + (2 * v1), 4, 2, 11 + TypeIcon_GetPltt(v2));
            Bg_ScheduleTilemapTransfer(param2->bgConfig, Unk_wifi_lobby_map_0226D5CC[3]);
        }
    }
}

static void wifi_lobby_map_0225FE80(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapRenderer *param2)
{
    if (param0->active == 1) {
        param0->active = 0;
    } else {
        wifi_lobby_map_0226068C(param0, param2);
    }

    wifi_lobby_map_02260048(param0, param2);
    wifi_lobby_map_02260228(param0, param2);

    Bg_ClearTilemap(param2->bgConfig, Unk_wifi_lobby_map_0226D5CC[1]);
    Bg_ClearTilemap(param2->bgConfig, Unk_wifi_lobby_map_0226D5CC[2]);
    Bg_ClearTilemap(param2->bgConfig, Unk_wifi_lobby_map_0226D5CC[3]);
}

static void wifi_lobby_map_0225FEC4(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID, u32 param4)
{
    wifi_lobby_map_02260048(param0, param1);
    wifi_lobby_map_0225FEF0(param0, param1, param2, heapID, param4, 1);
}

static BOOL wifi_lobby_map_0225FEEC(const WiFiLobbyMapButtonSprites *param0)
{
    return param0->active;
}

static void wifi_lobby_map_0225FEF0(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID, u32 param4, BOOL param5)
{
    u32 v0;
    u32 v1;

    GF_ASSERT(param4 < 27);
    GF_ASSERT(param0->cursorSprite == NULL);

    v0 = param4 / 3;
    v1 = param4 % 3;

    {
        BOOL v2;

        param0->cursorResources[0] = SpriteResourceCollection_AddTilesFrom(param1->spriteResources[0], param2, 61 + (v0 * 3), 0, 100, NNS_G2D_VRAM_TYPE_2DSUB, heapID);

        v2 = SpriteTransfer_RequestCharAtEnd(param0->cursorResources[0]);
        GF_ASSERT(v2);
        SpriteResource_ReleaseData(param0->cursorResources[0]);

        param0->cursorResources[1] = SpriteResourceCollection_AddPaletteFrom(param1->spriteResources[1], param2, 89, 0, 100, NNS_G2D_VRAM_TYPE_2DSUB, 3, heapID);

        v2 = SpriteTransfer_RequestPlttFreeSpace(param0->cursorResources[1]);
        GF_ASSERT(v2);
        SpriteResource_ReleaseData(param0->cursorResources[1]);

        param0->cursorResources[2] = SpriteResourceCollection_AddFrom(param1->spriteResources[2], param2, 60 + (v0 * 3), 0, 100, 2, heapID);
        param0->cursorResources[3] = SpriteResourceCollection_AddFrom(param1->spriteResources[3], param2, 59 + (v0 * 3), 0, 100, 3, heapID);
    }

    {
        SpriteResourcesHeader v3;
        SpriteListTemplate v4 = { NULL };

        SpriteResourcesHeader_Init(&v3, 100, 100, 100, 100, 0xffffffff, 0xffffffff, 0, 0, param1->spriteResources[0], param1->spriteResources[1], param1->spriteResources[2], param1->spriteResources[3], NULL, NULL);

        v4.list = param1->spriteList;
        v4.resourceData = &v3;
        v4.priority = 16;
        v4.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
        v4.heapID = heapID;
        v4.position.x = (FX32_CONST(208));
        v4.position.y = (FX32_CONST(152) + (256 * FX32_ONE));
        param0->cursorSprite = SpriteList_Add(&v4);

        Sprite_SetAnim(param0->cursorSprite, v1);
        Sprite_SetDrawFlag(param0->cursorSprite, param5);
    }
}

static void wifi_lobby_map_02260048(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1)
{
    Sprite_Delete(param0->cursorSprite);
    param0->cursorSprite = NULL;

    {
        int v0;

        SpriteTransfer_ResetCharTransfer(param0->cursorResources[0]);
        SpriteTransfer_ResetPlttTransfer(param0->cursorResources[1]);

        for (v0 = 0; v0 < 4; v0++) {
            SpriteResourceCollection_Remove(param1->spriteResources[v0], param0->cursorResources[v0]);
        }
    }
}

static void wifi_lobby_map_02260080(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID, u32 param4)
{
    enum TrainerClass trainerClass;
    u16 v1, v2;
    u32 v3;
    TrainerClassGraphicIndex v4;

    GF_ASSERT(param0->pointerSprite == NULL);

    for (v3 = 0; v3 < 18; v3++) {
        if (Unk_wifi_lobby_map_0226D724[v3].unk_00 == param4) {
            trainerClass = Unk_wifi_lobby_map_0226D724[v3].unk_02;
            v1 = Unk_wifi_lobby_map_0226D724[v3].unk_04;
            v2 = Unk_wifi_lobby_map_0226D724[v3].unk_06;
        }
    }

    SpriteSystem_SetTrainerClassGraphicsIndex(trainerClass, FACE_FRONT, &v4);

    {
        BOOL v5;

        param0->pointerResources[0] = SpriteResourceCollection_AddTiles(param1->spriteResources[0], v4.narcID, v4.tiles, 0, 101, NNS_G2D_VRAM_TYPE_2DSUB, heapID);
        v5 = SpriteTransfer_RequestCharAtEnd(param0->pointerResources[0]);
        GF_ASSERT(v5);

        param0->pointerResources[1] = SpriteResourceCollection_AddPalette(param1->spriteResources[1], v4.narcID, v4.palette, 0, 101, NNS_G2D_VRAM_TYPE_2DSUB, 1, heapID);
        wifi_lobby_map_02260268(SpriteResource_GetPaletteFade(param0->pointerResources[1]));
        v5 = SpriteTransfer_RequestPlttFreeSpace(param0->pointerResources[1]);
        GF_ASSERT(v5);

        SpriteResource_ReleaseData(param0->pointerResources[1]);

        param0->pointerResources[2] = SpriteResourceCollection_Add(param1->spriteResources[2], v4.narcID, v4.cells, 0, 101, 2, heapID);
        param0->pointerResources[3] = SpriteResourceCollection_Add(param1->spriteResources[3], v4.narcID, v4.anims, 0, 101, 3, heapID);
    }

    {
        SpriteResourcesHeader v6;
        SpriteListTemplate v7 = { NULL };

        SpriteResourcesHeader_Init(&v6, 101, 101, 101, 101, 0xffffffff, 0xffffffff, 1, 3, param1->spriteResources[0], param1->spriteResources[1], param1->spriteResources[2], param1->spriteResources[3], NULL, NULL);

        v7.list = param1->spriteList;
        v7.resourceData = &v6;
        v7.priority = 32;
        v7.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
        v7.heapID = heapID;
        v7.position.x = FX32_CONST(v1);
        v7.position.y = FX32_CONST(v2) + (256 * FX32_ONE);

        param0->pointerSprite = SpriteList_Add(&v7);
    }
}

static void wifi_lobby_map_02260228(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1)
{
    CharTransfer_DeleteTask(Sprite_GetImageProxy(param0->pointerSprite));
    Sprite_Delete(param0->pointerSprite);

    param0->pointerSprite = NULL;

    {
        int v0;

        SpriteTransfer_ResetCharTransfer(param0->pointerResources[0]);
        SpriteTransfer_ResetPlttTransfer(param0->pointerResources[1]);

        for (v0 = 0; v0 < 4; v0++) {
            SpriteResourceCollection_Remove(param1->spriteResources[v0], param0->pointerResources[v0]);
        }
    }
}

static void wifi_lobby_map_02260268(NNSG2dPaletteData *param0)
{
    int v0, v1, v2, v3, v4;
    int v5;
    u16 *v6;

    v5 = param0->szByte / 2;
    v6 = param0->pRawData;

    for (v0 = 0; v0 < v5; v0++) {
        v1 = ((*v6) & 0x1f);
        v2 = (((*v6) >> 5) & 0x1f);
        v3 = (((*v6) >> 10) & 0x1f);
        v4 = ((v1) * 76 + (v2) * 151 + (v3) * 29) >> 8;
        v1 = ((v4) * 256) >> 8;
        v2 = ((v4) * 200) >> 8;
        v3 = ((v4) * 128) >> 8;

        if (v1 > 31) {
            v1 = 31;
        }

        *v6 = (u16)((v3 << 10) | (v2 << 5) | v1);
        v6++;
    }
}

static void wifi_lobby_map_022602C0(WiFiLobbyMapButtonSprites *param0)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        Window_FillTilemap(&param0->windows[v0], 0);
    }
}

static void wifi_lobby_map_022602DC(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapStringFormatter *param1, u32 param2, u32 param3, u8 param4, u8 param5, u32 param6)
{
    String *v0 = wifi_lobby_map_0225F288(param1, 1, param3);
    Text_AddPrinterWithParamsAndColor(&param0->windows[param2], FONT_SYSTEM, v0, param4, param5, TEXT_SPEED_NO_TRANSFER, param6, NULL);
}

static void wifi_lobby_map_02260314(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapStringFormatter *param1, u32 param2, u32 param3, u8 param4, u8 param5, u32 param6)
{
    String *v0;
    u32 v1;
    s32 v2;

    v0 = wifi_lobby_map_0225F288(param1, 1, param3);
    v1 = Font_CalcStringWidth(FONT_SYSTEM, v0, 0);
    v2 = param4 - v1;

    if (v2 < 0) {
        v2 = 0;
    }

    Text_AddPrinterWithParamsAndColor(&param0->windows[param2], FONT_SYSTEM, v0, v2, param5, TEXT_SPEED_NO_TRANSFER, param6, NULL);
}

static void wifi_lobby_map_02260360(WiFiLobbyMapButtonSprites *param0, u32 param1)
{
    Window_ScheduleCopyToVRAM(&param0->windows[param1]);
}

static void wifi_lobby_map_02260370(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapStringFormatter *param1, const TrainerInfo *param2)
{
    wifi_lobby_map_0225F2C8(param1, param2, 0);
}

static void wifi_lobby_map_02260380(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapStringFormatter *param1, const WiFiPlazaProfile *param2)
{
    u32 v0;
    u32 v1;

    v0 = WiFiPlazaLobby_State_GetCountry(param2);
    v1 = WiFiPlazaLobby_State_GetRegion(param2);

    wifi_lobby_map_0225F308(param1, v0, 0);
    wifi_lobby_map_0225F318(param1, v0, v1, 1);
}

static void wifi_lobby_map_022603B0(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapStringFormatter *param1, const WiFiPlazaLobbyPasswordWords *param2)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        wifi_lobby_map_0225F32C(param1, v0, param2->unk_00[v0]);
    }
}

static void wifi_lobby_map_022603CC(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID, const WiFiPlazaProfile *param4, const WiFiPlazaProfile *param5)
{
    int v0;
    NARC *v1;
    NARC *v2;
    BOOL v3;
    u32 v4;
    u32 v5;
    u32 v6;
    u32 v7;
    SpriteListTemplate v8;
    SpriteResourcesHeader v9;
    const WiFiLobbyMapMemberSprite *v10;
    static const u16 v11[4][3] = {
        { 192, 0, 8 },
        { 186, 102, 2 },
        { 192, 49, 1 },
        { 192, 53, 1 },
    };
    static const u16 v12[4] = {
        2,
        104,
        51,
        55,
    };
    static const u16 v13[4] = {
        3,
        105,
        52,
        56,
    };

    v1 = NARC_ctor(NARC_INDEX_GRAPHIC__UNIONOBJ2D_ONLYFRONT, heapID);
    v6 = WiFiPlazaLobby_State_GetProfileUserId(param5);
    v7 = WiFiPlazaProfile_GetGender(param5);

    for (v0 = 0; v0 < 4; v0++) {
        if (v0 == 2) {
            if (v7 == 1) {
                param0->memberPalettes[v0] = NULL;
                param0->memberCells[v0] = NULL;
                param0->memberAnims[v0] = NULL;
                continue;
            }
        } else if (v0 == 3) {
            if (v7 == 0) {
                param0->memberPalettes[v0] = NULL;
                param0->memberCells[v0] = NULL;
                param0->memberAnims[v0] = NULL;
                continue;
            }
        }

        if (v11[v0][0] == 192) {
            v2 = v1;
        } else {
            v2 = param2;
        }

        param0->memberPalettes[v0] = SpriteResourceCollection_AddPaletteFrom(param1->spriteResources[1], v2, v11[v0][1], 0, 150 + v0, NNS_G2D_VRAM_TYPE_2DSUB, v11[v0][2], heapID);
        v3 = SpriteTransfer_RequestPlttFreeSpace(param0->memberPalettes[v0]);
        GF_ASSERT(v3);

        SpriteResource_ReleaseData(param0->memberPalettes[v0]);

        param0->memberCells[v0] = SpriteResourceCollection_AddFrom(param1->spriteResources[2], v2, v12[v0], 0, 150 + v0, 2, heapID);
        param0->memberAnims[v0] = SpriteResourceCollection_AddFrom(param1->spriteResources[3], v2, v13[v0], 0, 150 + v0, 3, heapID);
    }

    for (v0 = 0; v0 < 12; v0++) {
        v4 = WiFiPlazaLobby_State_GetNthActiveSlot(param4, v0);
        v5 = WiFiPlazaLobby_State_GetNthActiveUserID(param4, v0);

        if (v4 == 24) {
            param0->memberTiles[v0] = NULL;
            param0->memberSprites[v0] = NULL;
        } else {
            v10 = wifi_lobby_map_02260728(v4, v5, v6, v7);

            if (v10->unk_00 == 1) {
                v2 = param2;
            } else {
                v2 = v1;
            }

            param0->memberTiles[v0] = SpriteResourceCollection_AddTilesFrom(param1->spriteResources[0], v2, v10->unk_02, 0, 150 + v0, NNS_G2D_VRAM_TYPE_2DSUB, heapID);

            v3 = SpriteTransfer_RequestCharAtEnd(param0->memberTiles[v0]);
            GF_ASSERT(v3);

            SpriteResource_ReleaseData(param0->memberTiles[v0]);
            SpriteResourcesHeader_Init(&v9, 150 + v0, 150 + v10->unk_00, 150 + v10->unk_00, 150 + v10->unk_00, 0xffffffff, 0xffffffff, 0, 0, param1->spriteResources[0], param1->spriteResources[1], param1->spriteResources[2], param1->spriteResources[3], NULL, NULL);

            v8.list = param1->spriteList;
            v8.resourceData = &v9;
            v8.priority = 0;
            v8.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
            v8.heapID = heapID;
            v8.position = Unk_wifi_lobby_map_0226D7B4[v0];
            v8.position.x += FX32_CONST(v10->unk_04);
            v8.position.y += FX32_CONST(v10->unk_06);

            param0->memberSprites[v0] = SpriteList_Add(&v8);

            Sprite_SetExplicitPaletteOffsetAutoAdjust(param0->memberSprites[v0], v10->unk_01);
        }
    }

    NARC_dtor(v1);
}

static void wifi_lobby_map_0226068C(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1)
{
    int v0;

    for (v0 = 0; v0 < 12; v0++) {
        if (param0->memberTiles[v0] != NULL) {
            Sprite_Delete(param0->memberSprites[v0]);

            param0->memberSprites[v0] = NULL;

            SpriteTransfer_ResetCharTransfer(param0->memberTiles[v0]);
            SpriteResourceCollection_Remove(param1->spriteResources[0], param0->memberTiles[v0]);

            param0->memberTiles[v0] = NULL;
        }
    }

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->memberPalettes[v0] != NULL) {
            SpriteTransfer_ResetPlttTransfer(param0->memberPalettes[v0]);
            SpriteResourceCollection_Remove(param1->spriteResources[1], param0->memberPalettes[v0]);
            SpriteResourceCollection_Remove(param1->spriteResources[2], param0->memberCells[v0]);
            SpriteResourceCollection_Remove(param1->spriteResources[3], param0->memberAnims[v0]);
            param0->memberPalettes[v0] = NULL;
        }
    }
}

static const WiFiLobbyMapMemberSprite *wifi_lobby_map_02260728(int param0, s32 param1, s32 param2, u32 param3)
{
    if (param1 == param2) {
        return &Unk_wifi_lobby_map_0226D5FC[param3];
    }

    return &Unk_wifi_lobby_map_0226D844[param0];
}

static void wifi_lobby_map_02260744(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID)
{
    int v0;

    Window_AddFromTemplate(param1->bgConfig, &param0->unk_0C, &Unk_wifi_lobby_map_0226D5A4);

    for (v0 = 0; v0 < 3; v0++) {
        param0->unk_20[v0] = Graphics_GetScrnDataFromOpenNARC(param2, 56 + v0, 0, &param0->unk_2C[v0], heapID);
    }

    {
        static const TouchScreenHitTable v1 = { 32, 160, 40, 216 };
        param0->unk_1C = TouchScreenActions_RegisterHandler(&v1, 1, wifi_lobby_map_02260A50, param0, heapID);
    }

    param0->unk_06 = 1;
}

static void wifi_lobby_map_022607A8(WiFiLobbyMapTouchButton *param0)
{
    int v0;

    TouchScreenActions_Free(param0->unk_1C);
    Window_Remove(&param0->unk_0C);

    for (v0 = 0; v0 < 3; v0++) {
        Heap_Free(param0->unk_20[v0]);
    }

    param0->unk_02 = 0;
}

static BOOL wifi_lobby_map_022607D4(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID)
{
    BOOL v0 = 0;

    if (param0->unk_06 == 0) {
        TouchScreenActions_HandleAction(param0->unk_1C);
    } else {
        param0->unk_03 = 1;
    }

    if (param0->unk_02 == 1) {
        if (param0->unk_00 == 0) {
            param0->unk_02 = 0;
            wifi_lobby_map_022609D4(param0, param1, 0, param2, heapID);
        }
    }

    if (param0->unk_03 != param0->unk_04) {
        param0->unk_04 = param0->unk_03;

        if (param0->unk_03 == 2) {
            wifi_lobby_map_022609D4(param0, param1, 1, param2, heapID);
        } else {
            if (param0->unk_02 == 0) {
                wifi_lobby_map_022609D4(param0, param1, 0, param2, heapID);
            } else {
                wifi_lobby_map_022609D4(param0, param1, 2, param2, heapID);
            }
        }

        if ((param0->unk_02 == 0) && (param0->unk_03 == 2)) {
            v0 = 1;
            param0->unk_02 = 1;
            param0->unk_00 = 1;
        }
    }

    return v0;
}

static void wifi_lobby_map_02260870(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1, WiFiLobbyMapStringFormatter *param2, const WiFiPlazaProfile *param3, NARC *param4, u32 heapID)
{
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param4, 55, param1->bgConfig, Unk_wifi_lobby_map_0226D5CC[1], 0, 0, 0, heapID);

    param0->unk_08 = 0;
    param0->unk_0A = WiFiPlazaLobby_State_GetAppearanceRank(param3);

    Graphics_LoadTilesToBgLayerFromOpenNARC(param4, 0 + param0->unk_0A, param1->bgConfig, Unk_wifi_lobby_map_0226D5CC[3], 320, 0, 0, heapID);
    wifi_lobby_map_0225FA14(param1, param4, 27 + param0->unk_0A, Unk_wifi_lobby_map_0226D5CC[3], 320, heapID);

    {
        String *v0;

        v0 = wifi_lobby_map_0225F288(param2, 1, 63);

        Window_FillTilemap(&param0->unk_0C, 0);
        Text_AddPrinterWithParamsAndColor(&param0->unk_0C, FONT_SYSTEM, v0, 0, 4, TEXT_SPEED_INSTANT, TEXT_COLOR(15, 14, 0), NULL);
    }

    if (param0->unk_02 == 0) {
        wifi_lobby_map_022609D4(param0, param1, 0, param4, heapID);
    } else {
        wifi_lobby_map_022609D4(param0, param1, 2, param4, heapID);
    }
}

static void wifi_lobby_map_02260930(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1, u32 param2, NARC *param3, u32 heapID)
{
    GF_ASSERT(param2 < 3);

    {
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param3, 55, param1->bgConfig, Unk_wifi_lobby_map_0226D5CC[1], 0, 0, 0, heapID);
    }

    param0->unk_08 = 1;
    param0->unk_0A = param2;

    Graphics_LoadTilesToBgLayerFromOpenNARC(param3, 93 + param0->unk_0A, param1->bgConfig, Unk_wifi_lobby_map_0226D5CC[3], 320, 0, 0, heapID);

    if (param0->unk_02 == 0) {
        wifi_lobby_map_022609D4(param0, param1, 0, param3, heapID);
    } else {
        wifi_lobby_map_022609D4(param0, param1, 2, param3, heapID);
    }
}

static void wifi_lobby_map_022609A8(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1)
{
    Bg_ClearTilemap(param1->bgConfig, Unk_wifi_lobby_map_0226D5CC[1]);
    Bg_ClearTilemap(param1->bgConfig, Unk_wifi_lobby_map_0226D5CC[2]);
    Bg_ClearTilemap(param1->bgConfig, Unk_wifi_lobby_map_0226D5CC[3]);
    Bg_SetOffset(param1->bgConfig, Unk_wifi_lobby_map_0226D5CC[3], 3, 0);
}

static void wifi_lobby_map_022609D4(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1, u32 param2, NARC *param3, u32 heapID)
{
    static const s8 v0[3] = {
        0, 9, 6
    };

    Bg_CopyToTilemapRect(param1->bgConfig, Unk_wifi_lobby_map_0226D5CC[2], 0, 3, 32, 21, (const void *)param0->unk_2C[param2]->rawData, 0, 3, 32, 32);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, Unk_wifi_lobby_map_0226D5CC[2]);

    if (param0->unk_08 == 1) {
        static const u8 v1[3] = {
            0, 1, 0
        };
        u32 v2;

        v2 = (param0->unk_0A * 2) + v1[param2];
        wifi_lobby_map_0225FA14(param1, param3, 96 + v2, Unk_wifi_lobby_map_0226D5CC[3], 320, heapID);
    }

    Bg_ScheduleScroll(param1->bgConfig, Unk_wifi_lobby_map_0226D5CC[3], 3, v0[param2]);
}

static void wifi_lobby_map_02260A50(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    WiFiLobbyMapTouchButton *v0 = param2;

    v0->unk_03 = param1;

    if (v0->unk_03 == 0) {
        v0->unk_03 = 2;
    } else {
        if (v0->unk_03 == 3) {
            v0->unk_03 = 1;
        }
    }
}

static void wifi_lobby_map_02260A68(WiFiLobbyMapTouchButton *param0)
{
    param0->unk_00 = 0;
}
