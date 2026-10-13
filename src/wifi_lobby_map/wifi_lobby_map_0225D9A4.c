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
    BgConfig *unk_00;
    SpriteList *unk_04;
    G2dRenderer unk_08;
    SpriteResourceCollection *unk_194[4];
    NNSG2dCellTransferState *unk_1A4;
    G3DPipelineBuffers *unk_1A8;
} WiFiLobbyMapRenderer;

typedef struct {
    Window unk_00;
    u32 unk_10;
    u32 unk_14;
    String *unk_18;
    void *unk_1C;
} WiFiLobbyMapMessageBox;

typedef struct {
    ListMenuTemplate unk_00;
    Window unk_20;
    ListMenu *unk_30;
    StringList *unk_34;
    u16 unk_38;
    u16 unk_3A;
    BOOL unk_3C;
    SpriteResource *unk_40[4];
    Sprite *unk_50[2];
} WiFiLobbyMapListMenu;

typedef struct {
    StringList *unk_00;
    ListMenuTemplate unk_04;
} WiFiLobbyMapChoiceMenu;

typedef struct {
    Window unk_00;
} WiFiLobbyMapWindow;

typedef struct {
    Window unk_00;
} WiFiLobbyMapTouchPanel;

typedef struct {
    StringTemplate *unk_00;
    MessageLoader *unk_04[4];
    String *unk_14;
    String *unk_18;
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
    u32 unk_00;
    Window unk_04[5];
    Sprite *unk_54;
    SpriteResource *unk_58[4];
    Sprite *unk_68;
    SpriteResource *unk_6C[4];
    Sprite *unk_7C[12];
    SpriteResource *unk_AC[4];
    SpriteResource *unk_BC[12];
    SpriteResource *unk_EC[4];
    SpriteResource *unk_FC[4];
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
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04_0 : 4;
    u8 unk_04_4 : 4;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    s32 unk_08;
    WiFiLobbyMapSlotFlags unk_0C;
    WiFiPlazaLobbyState *unk_34;
    WiFiLobbyMapArgs *unk_38;
    WiFiLobbyMapRenderer unk_3C;
    WiFiLobbyMapTouchScreen unk_1E8;
    WiFiLobbyMapStringFormatter unk_340;
    WiFiLobbyMapMessageBox unk_35C;
    WiFiLobbyMapMessageBox unk_37C;
    WiFiLobbyMapListMenu unk_39C;
    WiFiLobbyMapWindow unk_3F4;
    WiFiLobbyMapChoiceMenu unk_404;
    WiFiLobbyMapTouchPanel unk_428;
    WiFiLobbyMapAttractionManager *unk_438;
    BOOL unk_43C;
    WiFiLobbyMapTimeEventManager *unk_440;
    WiFiLobbyMapActorManager *unk_444;
    WiFiLobbyMapObjectManager *unk_448;
    WiFiLobbyMapGrid *unk_44C;
    WiFiLobbyMapCamera *unk_450;
    WiFiLobbyMapTaskManager *unk_454;
    TrainerInfo *unk_458;
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

    v0->unk_38 = &v1->mapArgs;
    v0->unk_34 = v1->state;
    v0->unk_02 = WiFiPlazaLobby_State_GetMySlotIndex(v0->unk_34);

    GF_ASSERT(WiFiPlazaLobby_State_GetMySlotIndex(v0->unk_34) != 0xffffffff);

    RenderControlFlags_SetCanABSpeedUpPrint(TRUE);
    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_DISABLED);
    RenderControlFlags_SetSpeedUpOnTouch(FALSE);

    v0->unk_458 = SaveData_GetTrainerInfo(v1->saveData);
    wifi_lobby_map_0225E4EC(&v0->unk_3C, v1->saveData, HEAP_ID_112);
    v0->unk_44C = wifi_lobby_map_0225C858(HEAP_ID_112);

    {
        u32 v2;

        v2 = TrainerInfo_Gender(v0->unk_458);
        v0->unk_444 = wifi_lobby_map_0225C9B4(24, v2, v0->unk_44C, HEAP_ID_112, HEAP_ID_113);
    }

    v0->unk_448 = wifi_lobby_map_02261E10(v1->season, v1->roomType, v0->unk_44C, HEAP_ID_112, HEAP_ID_113);
    v0->unk_450 = wifi_lobby_map_02260A70(HEAP_ID_112);

    wifi_lobby_map_0225E9C8(&v0->unk_35C, &v0->unk_3C, v1->saveData, HEAP_ID_112);
    wifi_lobby_map_0225EBA8(&v0->unk_37C, &v0->unk_3C, v1->saveData, HEAP_ID_112);
    wifi_lobby_map_0225EC20(&v0->unk_39C, &v0->unk_3C, HEAP_ID_112);
    wifi_lobby_map_0225F114(&v0->unk_3F4, &v0->unk_3C, HEAP_ID_112);
    wifi_lobby_map_0225EFD4(&v0->unk_428, &v0->unk_3C, HEAP_ID_112);
    wifi_lobby_map_0225F208(&v0->unk_340, HEAP_ID_112);
    wifi_lobby_map_0225F098(&v0->unk_404, &v0->unk_340, HEAP_ID_112);
    wifi_lobby_map_0225F350(&v0->unk_1E8, v0->unk_38, &v0->unk_3C, v0->unk_458, HEAP_ID_112);

    {
        const WiFiPlazaProfile *v3;

        v3 = WiFiPlazaLobby_State_GetOwnProfile(v0->unk_34);

        if (WiFiPlazaLobby_State_IsAppearanceRankSet(v3) == 1) {
            wifi_lobby_map_0225F8AC(&v0->unk_1E8, &v0->unk_3C, &v0->unk_340, HEAP_ID_112, v3);
        }
    }

    v0->unk_454 = wifi_lobby_map_02262DA8(v0, HEAP_ID_112);

    wifi_lobby_map_022630A4(v0);
    wifi_lobby_map_022630EC(v0);

    v0->unk_438 = wifi_lobby_map_02269190(v0->unk_34, v0->unk_44C, v0->unk_450, v0->unk_444, HEAP_ID_112, HEAP_ID_113);
    v0->unk_440 = wifi_lobby_map_0226C60C(HEAP_ID_112, v0);

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
        v0->unk_03 = 1;
        (*param1)++;
        break;
    case 1:
        v2 = IsScreenFadeDone();

        if (v2 == 1) {
            v0->unk_03 = 0;
            (*param1)++;
        }
        break;
    case 2:
        if (v0->unk_04_0 == 1) {
            if ((WiFiPlazaLobby_Time_HasWifiError() == 1) || (WiFiPlazaLobby_State_GetErrorFlag(v0->unk_34) != 0)) {
                v0->unk_04_4 = 1;
            }
        }

        if (v0->unk_07 == 0) {
            if (WiFiPlazaLobby_State_IsLobbyCloseFinished(v0->unk_34) == 1) {
                v0->unk_06 = 1;
                wifi_lobby_map_0225DF38(v0, 8);
            }
        }

        if ((v0->unk_00 == 1) || (v0->unk_04_4 == 1) || (v0->unk_06 == 1)) {
            if (v0->unk_04_4) {
                (*param1) = 3;
            } else if (v0->unk_06 == 1) {
                (*param1) = 5;
            } else {
                (*param1) = 7;
            }
        }
        break;
    case 3: {
        wifi_lobby_map_0225EB74(&v0->unk_35C);
        wifi_lobby_map_0225EF14(&v0->unk_39C, NULL, NULL);
        wifi_lobby_map_0225F024(&v0->unk_428);
        wifi_lobby_map_0225F100(&v0->unk_404);

        if (CommManager_CheckWifiError()) {
            wifi_lobby_map_0225F184(&v0->unk_3F4, &v0->unk_340);
        } else if (CommManager_IsWifiPlazaError()) {
            wifi_lobby_map_0225F1C0(&v0->unk_3F4, &v0->unk_340, WiFiPlazaLobby_Network_GetLastError());
        } else {
            wifi_lobby_map_0225F1F0(&v0->unk_3F4, &v0->unk_340, WiFiPlazaLobby_State_GetErrorFlag(v0->unk_34));
        }
        (*param1) = 4;
    } break;
    case 4:
        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            (*param1) = 7;
        }
        break;
    case 5: {
        wifi_lobby_map_0225EB74(&v0->unk_35C);
        wifi_lobby_map_0225EF14(&v0->unk_39C, NULL, NULL);
        wifi_lobby_map_0225F024(&v0->unk_428);
        wifi_lobby_map_0225F100(&v0->unk_404);
        wifi_lobby_map_0225EA44(&v0->unk_35C, wifi_lobby_map_0225F288(&v0->unk_340, 1, 70));
        (*param1) = 6;
        v0->unk_08 = 60;
    } break;
    case 6:
        if (wifi_lobby_map_0225EB5C(&v0->unk_35C)) {
            v0->unk_08--;

            if (v0->unk_08 <= 0) {
                (*param1) = 7;
            }
        }
        break;
    case 7: {
        u32 v3;

        v3 = wifi_lobby_map_0225F798(&v0->unk_1E8);

        if (v3 == 5) {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_112);
            v0->unk_03 = 1;
            (*param1)++;
            break;
        }

        if (v3 == 0) {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_112);
            v0->unk_03 = 1;
            (*param1)++;
            break;
        }
    } break;
    case 8:
        v2 = IsScreenFadeDone();

        if (v2 == 1) {
            v0->unk_03 = 0;
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
        v1->exitCode = v0->unk_01;
    }

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    wifi_lobby_map_0226C6F8(v0->unk_440);
    wifi_lobby_map_02269204(v0->unk_438);
    wifi_lobby_map_02262DF4(v0->unk_454);
    wifi_lobby_map_0225F3E4(&v0->unk_1E8, &v0->unk_37C, &v0->unk_3C);
    wifi_lobby_map_0225F25C(&v0->unk_340);
    wifi_lobby_map_0225EA14(&v0->unk_35C);
    wifi_lobby_map_0225EBBC(&v0->unk_37C);
    wifi_lobby_map_0225ED4C(&v0->unk_39C, &v0->unk_3C);
    wifi_lobby_map_0225F144(&v0->unk_3F4);
    wifi_lobby_map_0225F100(&v0->unk_404);
    wifi_lobby_map_0225EFD8(&v0->unk_428);
    wifi_lobby_map_02260AD4(v0->unk_450);
    wifi_lobby_map_022621AC(v0->unk_448);
    wifi_lobby_map_0225CA20(v0->unk_444);
    wifi_lobby_map_0225C894(v0->unk_44C);
    wifi_lobby_map_0225E6D0(&v0->unk_3C);

    Heap_Free(v0);
    Heap_Destroy(HEAP_ID_112);
    Heap_Destroy(HEAP_ID_113);
    Sound_StopAllEffects(0);
    Sound_StopPokemonCries(0);

    return 1;
}

WiFiPlazaLobbyState *wifi_lobby_map_0225DEE8(WiFiLobbyMapApp *param0)
{
    return param0->unk_34;
}

WiFiLobbyMapArgs *wifi_lobby_map_0225DEEC(WiFiLobbyMapApp *param0)
{
    return param0->unk_38;
}

WiFiLobbyMapActorManager *wifi_lobby_map_0225DEF0(WiFiLobbyMapApp *param0)
{
    return param0->unk_444;
}

WiFiLobbyMapObjectManager *wifi_lobby_map_0225DEF8(WiFiLobbyMapApp *param0)
{
    return param0->unk_448;
}

WiFiLobbyMapGrid *wifi_lobby_map_0225DF00(WiFiLobbyMapApp *param0)
{
    return param0->unk_44C;
}

WiFiLobbyMapCamera *wifi_lobby_map_0225DF08(WiFiLobbyMapApp *param0)
{
    return param0->unk_450;
}

WiFiLobbyMapTaskManager *wifi_lobby_map_0225DF10(WiFiLobbyMapApp *param0)
{
    return param0->unk_454;
}

void wifi_lobby_map_0225DF18(WiFiLobbyMapApp *param0, BOOL param1)
{
    param0->unk_04_0 = param1;
}

u32 wifi_lobby_map_0225DF2C(const WiFiLobbyMapApp *param0)
{
    return param0->unk_02;
}

BOOL wifi_lobby_map_0225DF30(const WiFiLobbyMapApp *param0)
{
    return param0->unk_03;
}

void wifi_lobby_map_0225DF34(WiFiLobbyMapApp *param0, BOOL param1)
{
    param0->unk_00 = param1;
}

void wifi_lobby_map_0225DF38(WiFiLobbyMapApp *param0, u8 param1)
{
    param0->unk_01 = param1;
}

void wifi_lobby_map_0225DF3C(WiFiLobbyMapApp *param0, u8 param1)
{
    param0->unk_05 = param1;
}

u8 wifi_lobby_map_0225DF40(const WiFiLobbyMapApp *param0)
{
    return param0->unk_05;
}

void wifi_lobby_map_0225DF44(WiFiLobbyMapApp *param0)
{
    param0->unk_07 = 1;
}

void wifi_lobby_map_0225DF4C(WiFiLobbyMapApp *param0, u8 param1, BOOL param2)
{
    GF_ASSERT(param1 < 20);
    param0->unk_0C.unk_00[param1] = param2;
}

BOOL wifi_lobby_map_0225DF64(const WiFiLobbyMapApp *param0, u8 param1)
{
    return param0->unk_0C.unk_00[param1];
}

void wifi_lobby_map_0225DF6C(WiFiLobbyMapApp *param0, u8 param1, BOOL param2)
{
    GF_ASSERT(param1 < 20);
    param0->unk_0C.unk_14[param1] = param2;
}

BOOL wifi_lobby_map_0225DF84(const WiFiLobbyMapApp *param0, u8 param1)
{
    return param0->unk_0C.unk_14[param1];
}

void wifi_lobby_map_0225DF8C(WiFiLobbyMapApp *param0, const String *param1)
{
    wifi_lobby_map_0225EA44(&param0->unk_35C, param1);
}

void wifi_lobby_map_0225DF9C(WiFiLobbyMapApp *param0, const String *param1)
{
    wifi_lobby_map_0225EAA4(&param0->unk_35C, param1);
}

BOOL wifi_lobby_map_0225DFAC(const WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225EB5C(&param0->unk_35C);
}

void wifi_lobby_map_0225DFBC(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EB08(&param0->unk_35C);
}

void wifi_lobby_map_0225DFCC(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EB24(&param0->unk_35C);
}

BOOL wifi_lobby_map_0225DFDC(const WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225EB4C(&param0->unk_35C);
}

void wifi_lobby_map_0225DFEC(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EB74(&param0->unk_35C);
}

void wifi_lobby_map_0225DFFC(WiFiLobbyMapApp *param0, const String *param1)
{
    wifi_lobby_map_0225EBC4(&param0->unk_37C, param1);
}

void wifi_lobby_map_0225E00C(WiFiLobbyMapApp *param0, u32 param1)
{
    wifi_lobby_map_0225EDA8(&param0->unk_39C, param1, HEAP_ID_113, 0);
}

void wifi_lobby_map_0225E020(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    wifi_lobby_map_0225EDA8(&param0->unk_39C, param1, HEAP_ID_113, param2);
}

void wifi_lobby_map_0225E034(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EDE0(&param0->unk_39C);
}

void wifi_lobby_map_0225E044(WiFiLobbyMapApp *param0, const String *param1, u32 param2)
{
    wifi_lobby_map_0225EDF8(&param0->unk_39C, param1, param2);
}

const StringList *wifi_lobby_map_0225E054(const WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225EE04(&param0->unk_39C);
}

BOOL wifi_lobby_map_0225E064(const WiFiLobbyMapApp *param0, u32 param1)
{
    return wifi_lobby_map_0225EE08(&param0->unk_39C, param1);
}

void wifi_lobby_map_0225E074(WiFiLobbyMapApp *param0, const ListMenuTemplate *param1, u16 param2, u16 param3)
{
    wifi_lobby_map_0225EE30(&param0->unk_39C, param1, &param0->unk_3C, param2, param3, HEAP_ID_112, 16, 3, 15);
}

extern void wifi_lobby_map_0225E0A4(WiFiLobbyMapApp *param0, const ListMenuTemplate *param1, u16 param2, u16 param3, u8 param4, u8 param5, u8 param6)
{
    wifi_lobby_map_0225EE30(&param0->unk_39C, param1, &param0->unk_3C, param2, param3, HEAP_ID_112, param4, param5, param6);
}

u32 wifi_lobby_map_0225E0D4(WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225EED8(&param0->unk_39C);
}

void wifi_lobby_map_0225E0E4(WiFiLobbyMapApp *param0, u16 *param1, u16 *param2)
{
    wifi_lobby_map_0225EF14(&param0->unk_39C, param1, param2);
}

void wifi_lobby_map_0225E0F4(WiFiLobbyMapApp *param0, BOOL param1)
{
    wifi_lobby_map_0225EF6C(&param0->unk_39C, param1);
}

void wifi_lobby_map_0225E104(WiFiLobbyMapApp *param0, u8 param1, u8 param2, u8 param3, u8 param4)
{
    wifi_lobby_map_0225EFE0(&param0->unk_428, &param0->unk_3C, 112, param1, param2, param3, param4);
}

void wifi_lobby_map_0225E12C(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225F024(&param0->unk_428);
}

void wifi_lobby_map_0225E13C(WiFiLobbyMapApp *param0, const String *param1, u8 param2, u8 param3)
{
    wifi_lobby_map_0225F048(&param0->unk_428, param1, param2, param3);
}

void wifi_lobby_map_0225E14C(WiFiLobbyMapApp *param0, u16 param1, u16 param2, u16 param3, u16 param4)
{
    wifi_lobby_map_0225F078(&param0->unk_428, param1, param2, param3, param4);
}

void wifi_lobby_map_0225E164(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EE30(&param0->unk_39C, &param0->unk_404.unk_04, &param0->unk_3C, 0, 0, HEAP_ID_112, 25, 13, 6);
}

void wifi_lobby_map_0225E194(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225EE30(&param0->unk_39C, &param0->unk_404.unk_04, &param0->unk_3C, 0, 1, HEAP_ID_112, 25, 13, 6);
}

int wifi_lobby_map_0225E1C4(WiFiLobbyMapApp *param0)
{
    u32 v0 = wifi_lobby_map_0225EED8(&param0->unk_39C);

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
    wifi_lobby_map_0225EF14(&param0->unk_39C, NULL, NULL);
}

String *wifi_lobby_map_0225E20C(WiFiLobbyMapApp *param0, int param1, u32 param2)
{
    return wifi_lobby_map_0225F288(&param0->unk_340, param1, param2);
}

void wifi_lobby_map_0225E21C(WiFiLobbyMapApp *param0, u32 param1, u32 param2, u32 param3, int param4)
{
    wifi_lobby_map_0225F2A8(&param0->unk_340, param1, param2, param3, param4);
}

void wifi_lobby_map_0225E234(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    TrainerInfo *v0;
    const WiFiPlazaProfile *v1;

    v0 = TrainerInfo_New(HEAP_ID_112);

    if (param1 == WiFiPlazaLobby_State_GetMySlotIndex(param0->unk_34)) {
        v1 = WiFiPlazaLobby_State_GetOwnProfile(param0->unk_34);
    } else {
        v1 = WiFiPlazaLobby_State_GetProfileBySlot(param0->unk_34, param1);
    }

    WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v1, v0, HEAP_ID_112);
    wifi_lobby_map_0225F2C8(&param0->unk_340, v0, param2);
    Heap_Free(v0);
}

void wifi_lobby_map_0225E27C(WiFiLobbyMapApp *param0, enum PlazaMinigame param1, u32 param2)
{
    wifi_lobby_map_0225F2D8(&param0->unk_340, param1, param2);
}

void wifi_lobby_map_0225E28C(WiFiLobbyMapApp *param0, int param1, u32 param2)
{
    wifi_lobby_map_0225F2E8(&param0->unk_340, param1, param2);
}

void wifi_lobby_map_0225E29C(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    wifi_lobby_map_0225F2F8(&param0->unk_340, param1, param2);
}

void wifi_lobby_map_0225E2AC(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    StringTemplate_SetJPGreeting(param0->unk_340.unk_00, param1, param2);
}

void wifi_lobby_map_0225E2BC(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    StringTemplate_SetENGreeting(param0->unk_340.unk_00, param1, param2);
}

void wifi_lobby_map_0225E2CC(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    StringTemplate_SetFRGreeting(param0->unk_340.unk_00, param1, param2);
}

void wifi_lobby_map_0225E2DC(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    StringTemplate_SetITGreeting(param0->unk_340.unk_00, param1, param2);
}

void wifi_lobby_map_0225E2EC(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    StringTemplate_SetDEGreeting(param0->unk_340.unk_00, param1, param2);
}

void wifi_lobby_map_0225E2FC(WiFiLobbyMapApp *param0, u32 param1, u32 param2)
{
    StringTemplate_SetESGreeting(param0->unk_340.unk_00, param1, param2);
}

void wifi_lobby_map_0225E30C(WiFiLobbyMapApp *param0, u32 param1, int param2)
{
    param2 = WiFiPlazaLobby_Time_GetTypeIconIndex(param2);
    StringTemplate_SetPokemonTypeName(param0->unk_340.unk_00, param1, param2);
}

void wifi_lobby_map_0225E328(WiFiLobbyMapApp *param0, u32 param1, BOOL param2)
{
    if ((wifi_lobby_map_0225F7F8(&param0->unk_1E8) == param1) && (wifi_lobby_map_0225F7FC(&param0->unk_1E8) == 1) && (wifi_lobby_map_0225F834(&param0->unk_1E8) == 0) && (wifi_lobby_map_0225F828(&param0->unk_1E8) == param2)) {
        return;
    }

    wifi_lobby_map_0225F79C(&param0->unk_1E8, param1, param2);
}

void wifi_lobby_map_0225E378(WiFiLobbyMapApp *param0, u32 param1)
{
    wifi_lobby_map_0225F7A8(&param0->unk_1E8, &param0->unk_3C, param1, HEAP_ID_112);
}

void wifi_lobby_map_0225E390(WiFiLobbyMapApp *param0)
{
    const WiFiPlazaProfile *v0;
    u32 v1;

    if (wifi_lobby_map_0225F7FC(&param0->unk_1E8) == 0) {
        return;
    }

    v1 = wifi_lobby_map_0225F7F8(&param0->unk_1E8);
    v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0->unk_34, v1);

    wifi_lobby_map_0225FDA0(&param0->unk_1E8, &param0->unk_1E8.unk_08, &param0->unk_3C, HEAP_ID_112, v0);
}

void wifi_lobby_map_0225E3D0(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225F7E0(&param0->unk_1E8);
}

u32 wifi_lobby_map_0225E3E0(const WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225F7F8(&param0->unk_1E8);
}

BOOL wifi_lobby_map_0225E3F0(const WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225F7FC(&param0->unk_1E8);
}

BOOL wifi_lobby_map_0225E400(const WiFiLobbyMapApp *param0)
{
    return wifi_lobby_map_0225F814(&param0->unk_1E8);
}

void wifi_lobby_map_0225E410(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_0225F7EC(&param0->unk_1E8);
}

BOOL wifi_lobby_map_0225E420(const WiFiLobbyMapApp *param0, u32 param1)
{
    return wifi_lobby_map_0226C810(param0->unk_440, param1, 1);
}

void wifi_lobby_map_0225E430(WiFiLobbyMapApp *param0)
{
    param0->unk_1E8.unk_06 = 1;
}

void wifi_lobby_map_0225E43C(WiFiLobbyMapApp *param0, BOOL param1)
{
    wifi_lobby_map_0225F934(&param0->unk_1E8, param1);
}

void wifi_lobby_map_0225E44C(WiFiLobbyMapApp *param0)
{
    wifi_lobby_map_02260A68(&param0->unk_1E8.unk_114);
}

BOOL wifi_lobby_map_0225E45C(WiFiLobbyMapApp *param0)
{
    BOOL v0 = param0->unk_43C;
    param0->unk_43C = 0;

    return v0;
}

void wifi_lobby_map_0225E46C(WiFiLobbyMapApp *param0, u32 param1)
{
    const WiFiPlazaProfile *v0;
    u32 v1;

    GF_ASSERT(param1 < 20);

    v0 = WiFiPlazaLobby_State_GetProfileBySlot(param0->unk_34, param1);
    v1 = WiFiPlazaLobby_State_GetAppearanceRank(v0);

    wifi_lobby_map_02269268(param0->unk_438, param1, v1);

    if (param1 == WiFiPlazaLobby_State_GetMySlotIndex(param0->unk_34)) {
        WiFiPlazaLobby_State_BroadcastCosmeticID(param0->unk_34, v1);
    }
}

BOOL wifi_lobby_map_0225E4AC(const WiFiLobbyMapApp *param0, u32 param1)
{
    GF_ASSERT(param1 < 20);
    return wifi_lobby_map_02269298(param0->unk_438, param1);
}

static void wifi_lobby_map_0225E4C8(void *param0)
{
    WiFiLobbyMapApp *v0 = param0;

    wifi_lobby_map_022622A4(v0->unk_448);
    wifi_lobby_map_0225CAE0(v0->unk_444);
    wifi_lobby_map_0225E740(&v0->unk_3C);
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
        param0->unk_00 = BgConfig_New(heapID);

        for (v0 = 0; v0 < 4; v0++) {
            Bg_InitFromTemplate(param0->unk_00, Unk_wifi_lobby_map_0226D5CC[v0], &Unk_wifi_lobby_map_0226D6B4[v0], 0);
            Bg_ClearTilesRange(Unk_wifi_lobby_map_0226D5CC[v0], 32, 0, heapID);
            Bg_ClearTilemap(param0->unk_00, Unk_wifi_lobby_map_0226D5CC[v0]);
        }
    }

    {
        Options *options = SaveData_GetOptions(saveData);
        u8 v2 = Options_Frame(options);

        Font_LoadTextPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(5), heapID);
        Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(4), heapID);

        LoadStandardWindowGraphics(param0->unk_00, Unk_wifi_lobby_map_0226D5CC[0], (1 + (18 + 12)) + ((18 + 12) + 24), 3, 0, heapID);
        LoadMessageBoxGraphics(param0->unk_00, Unk_wifi_lobby_map_0226D5CC[0], 1, 1, v2, heapID);
        LoadSignpostContentGraphics(param0->unk_00, Unk_wifi_lobby_map_0226D5CC[0], 1 + (18 + 12), 2, SIGNPOST_TYPE_SCROLLING, 0, heapID);

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
        param0->unk_04 = SpriteList_InitRendering(24, &param0->unk_08, heapID);
        SetSubScreenViewRect(&param0->unk_08, 0, 256 * FX32_ONE);

        for (v3 = 0; v3 < 4; v3++) {
            param0->unk_194[v3] = SpriteResourceCollection_New(24, v3, heapID);
        }

        param0->unk_1A4 = CellTransfer_New(24, heapID);

        GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
    }

    {
        param0->unk_1A8 = G3DPipeline_Init(heapID, TEXTURE_VRAM_SIZE_256K, PALETTE_VRAM_SIZE_64K, wifi_lobby_map_0225E754);
    }
}

static void wifi_lobby_map_0225E6C0(WiFiLobbyMapRenderer *param0)
{
    SpriteList_Update(param0->unk_04);
    CellTransfer_Update();
}

static void wifi_lobby_map_0225E6D0(WiFiLobbyMapRenderer *param0)
{
    VramTransfer_Free();

    {
        int v0;

        for (v0 = 0; v0 < 4; v0++) {
            Bg_FreeTilemapBuffer(param0->unk_00, Unk_wifi_lobby_map_0226D5CC[v0]);
        }

        Heap_Free(param0->unk_00);
    }

    {
        int v1;

        CellTransfer_Free(param0->unk_1A4);
        param0->unk_1A4 = NULL;

        for (v1 = 0; v1 < 4; v1++) {
            SpriteResourceCollection_Delete(param0->unk_194[v1]);
        }

        SpriteList_Delete(param0->unk_04);
        CharTransfer_Free();
        PlttTransfer_Free();
        RenderOam_Free();
    }

    {
        G3DPipelineBuffers_Free(param0->unk_1A8);
    }
}

static void wifi_lobby_map_0225E740(WiFiLobbyMapRenderer *param0)
{
    Bg_RunScheduledUpdates(param0->unk_00);
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
    wifi_lobby_map_0225CA44(param0->unk_444);

    if ((param0->unk_04_4 == 0) && (param0->unk_06 == 0)) {
        {
            wifi_lobby_map_02262E20(param0->unk_454);
        }
    }

    wifi_lobby_map_02262210(param0->unk_448);

    if ((param0->unk_04_4 == 0) && (param0->unk_06 == 0)) {
        wifi_lobby_map_0225CA5C(param0->unk_444);

        {
            wifi_lobby_map_02262E2C(param0->unk_454);
        }

        wifi_lobby_map_0226C718(param0->unk_440);
    }

    wifi_lobby_map_0225E970(param0);

    if (param0->unk_03 == 0) {
        BOOL v0;

        if ((param0->unk_04_4 == 1) || (param0->unk_06 == 1) || (param0->unk_00 == 1)) {
            v0 = 1;
        } else {
            v0 = 0;
        }

        wifi_lobby_map_0225F418(&param0->unk_1E8, param0, v0, HEAP_ID_112);
    }

    wifi_lobby_map_02269220(param0->unk_438);
}

static void wifi_lobby_map_0225E92C(WiFiLobbyMapApp *param0)
{
    MtxFx44 v0;

    G3_ResetG3X();

    wifi_lobby_map_02260AEC(param0->unk_450);
    wifi_lobby_map_02262298(param0->unk_448);
    wifi_lobby_map_0225CAD4(param0->unk_444);
    wifi_lobby_map_02269240(param0->unk_438);

    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);

    wifi_lobby_map_0225E6C0(&param0->unk_3C);
}

static void wifi_lobby_map_0225E970(WiFiLobbyMapApp *param0)
{
    int v0;
    BOOL v1;
    BOOL v2;
    u32 v3;
    u32 v4;
    BOOL v5 = WiFiPlazaLobby_State_IsMinigameFinished(param0->unk_34);

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
        wifi_lobby_map_022627BC(param0->unk_448, WiFiPlazaLobbyActivity_00 + v0, v3, v2, v1, v5);
    }
}

static void wifi_lobby_map_0225E9C8(WiFiLobbyMapMessageBox *param0, WiFiLobbyMapRenderer *param1, SaveData *saveData, u32 heapID)
{
    Window_Add(param1->unk_00, &param0->unk_00, Unk_wifi_lobby_map_0226D5CC[0], 2, 19, 27, 4, 4, ((1 + (18 + 12)) + ((18 + 12) + 24)) + 9);
    Window_FillTilemap(&param0->unk_00, 15);

    param0->unk_18 = String_Init(384, heapID);
    param0->unk_14 = Options_TextFrameDelay(SaveData_GetOptions(saveData));
}

static void wifi_lobby_map_0225EA14(WiFiLobbyMapMessageBox *param0)
{
    if (Text_IsPrinterActive(param0->unk_10)) {
        Text_RemovePrinter(param0->unk_10);
    }

    wifi_lobby_map_0225EB38(param0);

    String_Free(param0->unk_18);
    Window_Remove(&param0->unk_00);
}

static void wifi_lobby_map_0225EA44(WiFiLobbyMapMessageBox *param0, const String *param1)
{
    if (Text_IsPrinterActive(param0->unk_10)) {
        Text_RemovePrinter(param0->unk_10);
    }

    Window_FillTilemap(&param0->unk_00, 15);
    String_Copy(param0->unk_18, param1);

    param0->unk_10 = Text_AddPrinterWithParamsAndColor(&param0->unk_00, FONT_MESSAGE, param0->unk_18, 0, 0, param0->unk_14, TEXT_COLOR(1, 2, 15), NULL);

    Window_DrawMessageBoxWithScrollCursor(&param0->unk_00, 1, 1, 1);
}

static void wifi_lobby_map_0225EAA4(WiFiLobbyMapMessageBox *param0, const String *param1)
{
    if (Text_IsPrinterActive(param0->unk_10)) {
        Text_RemovePrinter(param0->unk_10);
    }

    Window_FillTilemap(&param0->unk_00, 15);
    String_Copy(param0->unk_18, param1);
    Text_AddPrinterWithParamsAndColor(&param0->unk_00, FONT_MESSAGE, param0->unk_18, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
    Window_DrawMessageBoxWithScrollCursor(&param0->unk_00, 1, 1, 1);
    Window_ScheduleCopyToVRAM(&param0->unk_00);
}

static void wifi_lobby_map_0225EB08(WiFiLobbyMapMessageBox *param0)
{
    GF_ASSERT(param0->unk_1C == NULL);
    param0->unk_1C = Window_AddWaitDial(&param0->unk_00, 1);
}

static void wifi_lobby_map_0225EB24(WiFiLobbyMapMessageBox *param0)
{
    if (param0->unk_1C != NULL) {
        DestroyWaitDial(param0->unk_1C);
        param0->unk_1C = NULL;
    }
}

static void wifi_lobby_map_0225EB38(WiFiLobbyMapMessageBox *param0)
{
    if (param0->unk_1C != NULL) {
        DestroyWaitDialTaskOnly(param0->unk_1C);
        param0->unk_1C = NULL;
    }
}

static BOOL wifi_lobby_map_0225EB4C(const WiFiLobbyMapMessageBox *param0)
{
    if (param0->unk_1C != NULL) {
        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_0225EB5C(const WiFiLobbyMapMessageBox *param0)
{
    if (Text_IsPrinterActive(param0->unk_10) == 0) {
        return 1;
    }

    return 0;
}

static void wifi_lobby_map_0225EB74(WiFiLobbyMapMessageBox *param0)
{
    if (Text_IsPrinterActive(param0->unk_10)) {
        Text_RemovePrinter(param0->unk_10);
    }

    wifi_lobby_map_0225EB38(param0);

    Window_EraseMessageBox(&param0->unk_00, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->unk_00);
}

static void wifi_lobby_map_0225EBA8(WiFiLobbyMapMessageBox *param0, WiFiLobbyMapRenderer *param1, SaveData *saveData, u32 heapID)
{
    wifi_lobby_map_0225E9C8(param0, param1, saveData, heapID);
    Window_SetPalette(&param0->unk_00, 2);
}

static void wifi_lobby_map_0225EBBC(WiFiLobbyMapMessageBox *param0)
{
    wifi_lobby_map_0225EA14(param0);
}

static void wifi_lobby_map_0225EBC4(WiFiLobbyMapMessageBox *param0, const String *param1)
{
    if (Text_IsPrinterActive(param0->unk_10)) {
        Text_RemovePrinter(param0->unk_10);
    }

    Window_FillTilemap(&param0->unk_00, 15);
    String_Copy(param0->unk_18, param1);

    param0->unk_10 = Text_AddPrinterWithParams(&param0->unk_00, FONT_MESSAGE, param0->unk_18, 0, 0, param0->unk_14, NULL);

    Window_DrawSignpost(&param0->unk_00, 1, 1 + (18 + 12), 2, 3);
}

static void wifi_lobby_map_0225EC20(WiFiLobbyMapListMenu *param0, WiFiLobbyMapRenderer *param1, u32 heapID)
{
    SpriteResourcesHeader v0;
    SpriteListTemplate v1;
    int v2;
    NARC *v3 = NARC_ctor(NARC_INDEX_GRAPHIC__SHOP_GRA, heapID);

    param0->unk_40[0] = SpriteResourceCollection_AddTilesFrom(param1->unk_194[0], v3, 4, 0, 5000, NNS_G2D_VRAM_TYPE_2DMAIN, heapID);
    param0->unk_40[1] = SpriteResourceCollection_AddPaletteFrom(param1->unk_194[1], v3, 10, 0, 5000, NNS_G2D_VRAM_TYPE_2DMAIN, 1, heapID);
    param0->unk_40[2] = SpriteResourceCollection_AddFrom(param1->unk_194[2], v3, 5, 0, 5000, 2, heapID);
    param0->unk_40[3] = SpriteResourceCollection_AddFrom(param1->unk_194[3], v3, 6, 0, 5000, 3, heapID);

    NARC_dtor(v3);
    SpriteTransfer_RequestCharAtEnd(param0->unk_40[0]);
    SpriteTransfer_RequestPlttFreeSpace(param0->unk_40[1]);
    SpriteResourcesHeader_Init(&v0, 5000, 5000, 5000, 5000, 0xffffffff, 0xffffffff, 0, 0, param1->unk_194[0], param1->unk_194[1], param1->unk_194[2], param1->unk_194[3], NULL, NULL);

    v1.list = param1->unk_04;
    v1.resourceData = &v0;
    v1.priority = 0;
    v1.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v1.heapID = heapID;
    v1.position.x = 192 * FX32_ONE;

    for (v2 = 0; v2 < 2; v2++) {
        v1.position.y = Unk_wifi_lobby_map_0226D580[v2] * FX32_ONE;
        param0->unk_50[v2] = SpriteList_Add(&v1);

        Sprite_SetAnim(param0->unk_50[v2], v2);
        Sprite_SetAnimateFlag(param0->unk_50[v2], 1);
        Sprite_SetDrawFlag(param0->unk_50[v2], FALSE);
    }

    param0->unk_3C = 0;
}

static void wifi_lobby_map_0225ED4C(WiFiLobbyMapListMenu *param0, WiFiLobbyMapRenderer *param1)
{
    int v0;

    if (param0->unk_34 != NULL) {
        wifi_lobby_map_0225EDE0(param0);
    }

    if (param0->unk_30 != NULL) {
        wifi_lobby_map_0225EF14(param0, NULL, NULL);
    }

    for (v0 = 0; v0 < 2; v0++) {
        Sprite_Delete(param0->unk_50[v0]);
        param0->unk_50[v0] = NULL;
    }

    SpriteTransfer_ResetCharTransfer(param0->unk_40[0]);
    SpriteTransfer_ResetPlttTransfer(param0->unk_40[1]);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Remove(param1->unk_194[v0], param0->unk_40[v0]);
    }
}

static void wifi_lobby_map_0225EDA8(WiFiLobbyMapListMenu *param0, u32 param1, u32 heapID, u32 param3)
{
    int v0;
    GF_ASSERT(param0->unk_34 == NULL);
    param0->unk_34 = StringList_New(param1, heapID);
    param0->unk_38 = param1;

    for (v0 = 0; v0 < param1; v0++) {
        param0->unk_34[v0].index = param3;
    }
}

static void wifi_lobby_map_0225EDE0(WiFiLobbyMapListMenu *param0)
{
    if (param0->unk_34 != NULL) {
        StringList_Free(param0->unk_34);
        param0->unk_34 = NULL;
        param0->unk_38 = 0;
    }
}

static void wifi_lobby_map_0225EDF8(WiFiLobbyMapListMenu *param0, const String *param1, u32 param2)
{
    StringList_AddFromString(param0->unk_34, param1, param2);
}

static const StringList *wifi_lobby_map_0225EE04(const WiFiLobbyMapListMenu *param0)
{
    return param0->unk_34;
}

static BOOL wifi_lobby_map_0225EE08(const WiFiLobbyMapListMenu *param0, u32 param1)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_38; v0++) {
        if (param0->unk_34[v0].index == param1) {
            return 1;
        }
    }

    return 0;
}

static void wifi_lobby_map_0225EE30(WiFiLobbyMapListMenu *param0, const ListMenuTemplate *param1, WiFiLobbyMapRenderer *param2, u16 param3, u16 param4, u32 heapID, u8 param6, u8 param7, u8 param8)
{
    GF_ASSERT(param0->unk_30 == NULL);
    GF_ASSERT((param1->maxDisplay * 2) < 18);

    param0->unk_00 = *param1;
    param0->unk_00.window = &param0->unk_20;
    param0->unk_3A = param1->count;
    param0->unk_00.cursorCallback = wifi_lobby_map_0225EF58;

    Window_Add(param2->unk_00, &param0->unk_20, Unk_wifi_lobby_map_0226D5CC[0], param6, param7, param8, param1->maxDisplay * 2, 5, (((1 + (18 + 12)) + ((18 + 12) + 24)) + 9) + (27 * 4));
    Window_FillTilemap(&param0->unk_20, 15);
    Window_DrawStandardFrame(&param0->unk_20, 1, (1 + (18 + 12)) + ((18 + 12) + 24), 3);

    param0->unk_30 = ListMenu_New(&param0->unk_00, param3, param4, heapID);

    Window_ScheduleCopyToVRAM(&param0->unk_20);
}

static u32 wifi_lobby_map_0225EED8(WiFiLobbyMapListMenu *param0)
{
    u32 v0;

    if (param0->unk_30 == NULL) {
        return 0xfffffffe;
    }

    v0 = ListMenu_ProcessInput(param0->unk_30);

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

    if (param0->unk_30 == NULL) {
        return;
    }

    ListMenu_Free(param0->unk_30, param1, param2);

    param0->unk_30 = NULL;

    Window_EraseStandardFrame(&param0->unk_20, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->unk_20);
    Window_Remove(&param0->unk_20);

    param0->unk_3C = 0;

    for (v0 = 0; v0 < 2; v0++) {
        Sprite_SetDrawFlag(param0->unk_50[v0], FALSE);
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
    param0->unk_3C = param1;
}

static void wifi_lobby_map_0225EF70(WiFiLobbyMapListMenu *param0)
{
    u16 v0;

    if (param0->unk_3C == 0) {
        Sprite_SetDrawFlag(param0->unk_50[0], FALSE);
        Sprite_SetDrawFlag(param0->unk_50[1], FALSE);
        return;
    }

    ListMenu_GetListAndCursorPos(param0->unk_30, &v0, NULL);

    if (v0 <= 0) {
        Sprite_SetDrawFlag(param0->unk_50[0], FALSE);
    } else {
        Sprite_SetDrawFlag(param0->unk_50[0], TRUE);
    }

    if (v0 >= (param0->unk_3A - 7)) {
        Sprite_SetDrawFlag(param0->unk_50[1], FALSE);
    } else {
        Sprite_SetDrawFlag(param0->unk_50[1], TRUE);
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
    Window_Add(param1->unk_00, &param0->unk_00, Unk_wifi_lobby_map_0226D5CC[0], param3, param4, param5, param6, 5, (((1 + (18 + 12)) + ((18 + 12) + 24)) + 9) + (27 * 4));
    Window_DrawStandardFrame(&param0->unk_00, 1, (1 + (18 + 12)) + ((18 + 12) + 24), 3);
    Window_FillTilemap(&param0->unk_00, 15);
    Window_ScheduleCopyToVRAM(&param0->unk_00);
}

static void wifi_lobby_map_0225F024(WiFiLobbyMapTouchPanel *param0)
{
    if (Window_IsInUse(&param0->unk_00) == 1) {
        Window_EraseStandardFrame(&param0->unk_00, 1);
        Window_ClearAndScheduleCopyToVRAM(&param0->unk_00);
        Window_Remove(&param0->unk_00);
    }
}

static void wifi_lobby_map_0225F048(WiFiLobbyMapTouchPanel *param0, const String *param1, u8 param2, u8 param3)
{
    Text_AddPrinterWithParamsAndColor(&param0->unk_00, FONT_SYSTEM, param1, param2, param3, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
    Window_ScheduleCopyToVRAM(&param0->unk_00);
}

static void wifi_lobby_map_0225F078(WiFiLobbyMapTouchPanel *param0, u16 param1, u16 param2, u16 param3, u16 param4)
{
    Window_FillRectWithColor(&param0->unk_00, 15, param1, param2, param3, param4);
}

static void wifi_lobby_map_0225F098(WiFiLobbyMapChoiceMenu *param0, WiFiLobbyMapStringFormatter *param1, u32 heapID)
{
    String *v0;

    GF_ASSERT(param0->unk_00 == NULL);
    param0->unk_00 = StringList_New(2, heapID);

    v0 = wifi_lobby_map_0225F288(param1, 1, 67);
    StringList_AddFromString(param0->unk_00, v0, 0);
    v0 = wifi_lobby_map_0225F288(param1, 1, 66);
    StringList_AddFromString(param0->unk_00, v0, 1);

    param0->unk_04 = Unk_wifi_lobby_map_0226D644;
    param0->unk_04.count = 2;
    param0->unk_04.choices = param0->unk_00;
}

static void wifi_lobby_map_0225F100(WiFiLobbyMapChoiceMenu *param0)
{
    if (param0->unk_00 != NULL) {
        StringList_Free(param0->unk_00);
        param0->unk_00 = NULL;
    }
}

static void wifi_lobby_map_0225F114(WiFiLobbyMapWindow *param0, WiFiLobbyMapRenderer *param1, u32 heapID)
{
    Window_Add(param1->unk_00, &param0->unk_00, Unk_wifi_lobby_map_0226D5CC[0], 4, 4, 23, 16, 5, ((1 + (18 + 12)) + ((18 + 12) + 24)) + 9);
    Window_FillTilemap(&param0->unk_00, 15);
}

static void wifi_lobby_map_0225F144(WiFiLobbyMapWindow *param0)
{
    Window_Remove(&param0->unk_00);
}

static void wifi_lobby_map_0225F14C(WiFiLobbyMapWindow *param0, const String *param1)
{
    Text_AddPrinterWithParamsAndColor(&param0->unk_00, FONT_SYSTEM, param1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
    Window_DrawStandardFrame(&param0->unk_00, 1, (1 + (18 + 12)) + ((18 + 12) + 24), 3);
    Window_ScheduleCopyToVRAM(&param0->unk_00);
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

    param0->unk_00 = StringTemplate_New(8, 64, heapID);

    for (v0 = 0; v0 < 4; v0++) {
        param0->unk_04[v0] = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, v1[v0], heapID);
    }

    param0->unk_14 = String_Init(480, heapID);
    param0->unk_18 = String_Init(480, heapID);
}

static void wifi_lobby_map_0225F25C(WiFiLobbyMapStringFormatter *param0)
{
    int v0;

    StringTemplate_Free(param0->unk_00);

    for (v0 = 0; v0 < 4; v0++) {
        MessageLoader_Free(param0->unk_04[v0]);
    }

    String_Free(param0->unk_14);
    String_Free(param0->unk_18);
}

static String *wifi_lobby_map_0225F288(WiFiLobbyMapStringFormatter *param0, int param1, u32 param2)
{
    MessageLoader_GetString(param0->unk_04[param1], param2, param0->unk_18);
    StringTemplate_Format(param0->unk_00, param0->unk_14, param0->unk_18);
    return param0->unk_14;
}

static void wifi_lobby_map_0225F2A8(WiFiLobbyMapStringFormatter *param0, u32 param1, u32 param2, u32 param3, int param4)
{
    StringTemplate_SetNumber(param0->unk_00, param3, param1, param2, param4, 1);
}

static void wifi_lobby_map_0225F2C8(WiFiLobbyMapStringFormatter *param0, const TrainerInfo *param1, u32 param2)
{
    StringTemplate_SetPlayerName(param0->unk_00, param2, param1);
}

static void wifi_lobby_map_0225F2D8(WiFiLobbyMapStringFormatter *param0, enum PlazaMinigame param1, u32 param2)
{
    StringTemplate_SetPlazaMinigameName(param0->unk_00, param2, param1);
}

static void wifi_lobby_map_0225F2E8(WiFiLobbyMapStringFormatter *param0, int param1, u32 param2)
{
    StringTemplate_SetPlazaEventName(param0->unk_00, param2, param1);
}

static void wifi_lobby_map_0225F2F8(WiFiLobbyMapStringFormatter *param0, u32 param1, u32 param2)
{
    StringTemplate_SetPlazaItemName(param0->unk_00, param2, param1);
}

static void wifi_lobby_map_0225F308(WiFiLobbyMapStringFormatter *param0, u32 param1, u32 param2)
{
    StringTemplate_SetCountryName(param0->unk_00, param2, param1);
}

static void wifi_lobby_map_0225F318(WiFiLobbyMapStringFormatter *param0, u32 param1, u32 param2, u32 param3)
{
    StringTemplate_SetCityName(param0->unk_00, param3, param1, param2);
}

static void wifi_lobby_map_0225F32C(WiFiLobbyMapStringFormatter *param0, u32 param1, u16 param2)
{
    StringTemplate_SetEasyChatWord(param0->unk_00, param1, param2);
}

static void wifi_lobby_map_0225F338(WiFiLobbyMapStringFormatter *param0)
{
    StringTemplate_ClearArgs(param0->unk_00);
}

static void wifi_lobby_map_0225F344(WiFiLobbyMapApp *param0)
{
    param0->unk_43C = 1;
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

    if (param1->unk_06 == 0) {
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

    v0 = param1->unk_34;
    v1 = &param1->unk_3C;
    v2 = &param1->unk_340;

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
                wifi_lobby_map_0225F8AC(param0, v1, &param1->unk_340, heapID, v4);
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
                if (wifi_lobby_map_0226C810(param1->unk_440, param0->unk_150, param0->unk_152) == 0) {
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
            wifi_lobby_map_0225FACC(&param0->unk_08, &param1->unk_37C);
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
                wifi_lobby_map_0225F89C(param0, &param1->unk_37C, v1);
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
            wifi_lobby_map_0225F8AC(param0, v1, &param1->unk_340, heapID, v8);
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

            wifi_lobby_map_0225F844(param0, &param1->unk_37C, v1, v2, v12, heapID, v8, v13, v9, v10, v11, 1);
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
            wifi_lobby_map_0225FACC(&param0->unk_08, &param1->unk_37C);
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

        Graphics_LoadTilesToBgLayerFromOpenNARC(param2, 54, param1->unk_00, Unk_wifi_lobby_map_0226D5CC[1], 0, 0, 0, heapID);
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

    Bg_LoadToTilemapRect(param0->unk_00, param3, v1->rawData, 0, 0, v1->screenWidth / 8, v1->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param0->unk_00, param3);
    Heap_Free(v0);
}

static void wifi_lobby_map_0225FA84(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID)
{
    {
        int v0;

        for (v0 = 0; v0 < 5; v0++) {
            Window_AddFromTemplate(param1->unk_00, &param0->unk_04[v0], &Unk_wifi_lobby_map_0226D68C[v0]);
        }
    }
}

static void wifi_lobby_map_0225FAA8(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapRenderer *param2)
{
    if (param0->unk_54 != NULL) {
        wifi_lobby_map_0225FE80(param0, param1, param2);
    }

    {
        int v0;

        for (v0 = 0; v0 < 5; v0++) {
            Window_Remove(&param0->unk_04[v0]);
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

    Bg_ScheduleFillTilemap(param3->unk_00, Unk_wifi_lobby_map_0226D5CC[1], 0);
    Bg_ScheduleFillTilemap(param3->unk_00, Unk_wifi_lobby_map_0226D5CC[2], 0);
    Bg_ScheduleFillTilemap(param3->unk_00, Unk_wifi_lobby_map_0226D5CC[3], 0);

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
        param2->unk_00 = 1;

        wifi_lobby_map_02260370(param2, param4, v1);
        wifi_lobby_map_022602DC(param2, param4, 4, 56, 8, 0, v0);
        wifi_lobby_map_022603B0(param2, param4, param12);
        wifi_lobby_map_022602DC(param2, param4, 4, 59, 6, 24, TEXT_COLOR(1, 2, 0));
        wifi_lobby_map_022602DC(param2, param4, 4, 60, 90, 24, TEXT_COLOR(1, 2, 0));
        wifi_lobby_map_022602DC(param2, param4, 4, 61, 6, 44, TEXT_COLOR(1, 2, 0));
        wifi_lobby_map_022602DC(param2, param4, 4, 62, 90, 44, TEXT_COLOR(1, 2, 0));
        wifi_lobby_map_02260360(param2, 4);
    } else {
        param2->unk_00 = 0;

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

            Bg_LoadTiles(param2->unk_00, Unk_wifi_lobby_map_0226D5CC[3], v4->pRawData, 4 * 2 * 32, Unk_wifi_lobby_map_0226D590[v1]);
            Heap_Free(v3);
            Bg_CopyToTilemapRect(param2->unk_00, Unk_wifi_lobby_map_0226D5CC[3], 26, 2 + (2 * v1), 4, 2, Unk_wifi_lobby_map_0226D624[v1], 0, 0, 4, 2);
            Bg_ChangeTilemapRectPalette(param2->unk_00, Unk_wifi_lobby_map_0226D5CC[3], 26, 2 + (2 * v1), 4, 2, 11 + TypeIcon_GetPltt(v2));
            Bg_ScheduleTilemapTransfer(param2->unk_00, Unk_wifi_lobby_map_0226D5CC[3]);
        }
    }
}

static void wifi_lobby_map_0225FE80(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapMessageBox *param1, WiFiLobbyMapRenderer *param2)
{
    if (param0->unk_00 == 1) {
        param0->unk_00 = 0;
    } else {
        wifi_lobby_map_0226068C(param0, param2);
    }

    wifi_lobby_map_02260048(param0, param2);
    wifi_lobby_map_02260228(param0, param2);

    Bg_ClearTilemap(param2->unk_00, Unk_wifi_lobby_map_0226D5CC[1]);
    Bg_ClearTilemap(param2->unk_00, Unk_wifi_lobby_map_0226D5CC[2]);
    Bg_ClearTilemap(param2->unk_00, Unk_wifi_lobby_map_0226D5CC[3]);
}

static void wifi_lobby_map_0225FEC4(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID, u32 param4)
{
    wifi_lobby_map_02260048(param0, param1);
    wifi_lobby_map_0225FEF0(param0, param1, param2, heapID, param4, 1);
}

static BOOL wifi_lobby_map_0225FEEC(const WiFiLobbyMapButtonSprites *param0)
{
    return param0->unk_00;
}

static void wifi_lobby_map_0225FEF0(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID, u32 param4, BOOL param5)
{
    u32 v0;
    u32 v1;

    GF_ASSERT(param4 < 27);
    GF_ASSERT(param0->unk_54 == NULL);

    v0 = param4 / 3;
    v1 = param4 % 3;

    {
        BOOL v2;

        param0->unk_58[0] = SpriteResourceCollection_AddTilesFrom(param1->unk_194[0], param2, 61 + (v0 * 3), 0, 100, NNS_G2D_VRAM_TYPE_2DSUB, heapID);

        v2 = SpriteTransfer_RequestCharAtEnd(param0->unk_58[0]);
        GF_ASSERT(v2);
        SpriteResource_ReleaseData(param0->unk_58[0]);

        param0->unk_58[1] = SpriteResourceCollection_AddPaletteFrom(param1->unk_194[1], param2, 89, 0, 100, NNS_G2D_VRAM_TYPE_2DSUB, 3, heapID);

        v2 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_58[1]);
        GF_ASSERT(v2);
        SpriteResource_ReleaseData(param0->unk_58[1]);

        param0->unk_58[2] = SpriteResourceCollection_AddFrom(param1->unk_194[2], param2, 60 + (v0 * 3), 0, 100, 2, heapID);
        param0->unk_58[3] = SpriteResourceCollection_AddFrom(param1->unk_194[3], param2, 59 + (v0 * 3), 0, 100, 3, heapID);
    }

    {
        SpriteResourcesHeader v3;
        SpriteListTemplate v4 = { NULL };

        SpriteResourcesHeader_Init(&v3, 100, 100, 100, 100, 0xffffffff, 0xffffffff, 0, 0, param1->unk_194[0], param1->unk_194[1], param1->unk_194[2], param1->unk_194[3], NULL, NULL);

        v4.list = param1->unk_04;
        v4.resourceData = &v3;
        v4.priority = 16;
        v4.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
        v4.heapID = heapID;
        v4.position.x = (FX32_CONST(208));
        v4.position.y = (FX32_CONST(152) + (256 * FX32_ONE));
        param0->unk_54 = SpriteList_Add(&v4);

        Sprite_SetAnim(param0->unk_54, v1);
        Sprite_SetDrawFlag(param0->unk_54, param5);
    }
}

static void wifi_lobby_map_02260048(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1)
{
    Sprite_Delete(param0->unk_54);
    param0->unk_54 = NULL;

    {
        int v0;

        SpriteTransfer_ResetCharTransfer(param0->unk_58[0]);
        SpriteTransfer_ResetPlttTransfer(param0->unk_58[1]);

        for (v0 = 0; v0 < 4; v0++) {
            SpriteResourceCollection_Remove(param1->unk_194[v0], param0->unk_58[v0]);
        }
    }
}

static void wifi_lobby_map_02260080(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1, NARC *param2, u32 heapID, u32 param4)
{
    enum TrainerClass trainerClass;
    u16 v1, v2;
    u32 v3;
    TrainerClassGraphicIndex v4;

    GF_ASSERT(param0->unk_68 == NULL);

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

        param0->unk_6C[0] = SpriteResourceCollection_AddTiles(param1->unk_194[0], v4.narcID, v4.tiles, 0, 101, NNS_G2D_VRAM_TYPE_2DSUB, heapID);
        v5 = SpriteTransfer_RequestCharAtEnd(param0->unk_6C[0]);
        GF_ASSERT(v5);

        param0->unk_6C[1] = SpriteResourceCollection_AddPalette(param1->unk_194[1], v4.narcID, v4.palette, 0, 101, NNS_G2D_VRAM_TYPE_2DSUB, 1, heapID);
        wifi_lobby_map_02260268(SpriteResource_GetPaletteFade(param0->unk_6C[1]));
        v5 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_6C[1]);
        GF_ASSERT(v5);

        SpriteResource_ReleaseData(param0->unk_6C[1]);

        param0->unk_6C[2] = SpriteResourceCollection_Add(param1->unk_194[2], v4.narcID, v4.cells, 0, 101, 2, heapID);
        param0->unk_6C[3] = SpriteResourceCollection_Add(param1->unk_194[3], v4.narcID, v4.anims, 0, 101, 3, heapID);
    }

    {
        SpriteResourcesHeader v6;
        SpriteListTemplate v7 = { NULL };

        SpriteResourcesHeader_Init(&v6, 101, 101, 101, 101, 0xffffffff, 0xffffffff, 1, 3, param1->unk_194[0], param1->unk_194[1], param1->unk_194[2], param1->unk_194[3], NULL, NULL);

        v7.list = param1->unk_04;
        v7.resourceData = &v6;
        v7.priority = 32;
        v7.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
        v7.heapID = heapID;
        v7.position.x = FX32_CONST(v1);
        v7.position.y = FX32_CONST(v2) + (256 * FX32_ONE);

        param0->unk_68 = SpriteList_Add(&v7);
    }
}

static void wifi_lobby_map_02260228(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1)
{
    CharTransfer_DeleteTask(Sprite_GetImageProxy(param0->unk_68));
    Sprite_Delete(param0->unk_68);

    param0->unk_68 = NULL;

    {
        int v0;

        SpriteTransfer_ResetCharTransfer(param0->unk_6C[0]);
        SpriteTransfer_ResetPlttTransfer(param0->unk_6C[1]);

        for (v0 = 0; v0 < 4; v0++) {
            SpriteResourceCollection_Remove(param1->unk_194[v0], param0->unk_6C[v0]);
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
        Window_FillTilemap(&param0->unk_04[v0], 0);
    }
}

static void wifi_lobby_map_022602DC(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapStringFormatter *param1, u32 param2, u32 param3, u8 param4, u8 param5, u32 param6)
{
    String *v0 = wifi_lobby_map_0225F288(param1, 1, param3);
    Text_AddPrinterWithParamsAndColor(&param0->unk_04[param2], FONT_SYSTEM, v0, param4, param5, TEXT_SPEED_NO_TRANSFER, param6, NULL);
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

    Text_AddPrinterWithParamsAndColor(&param0->unk_04[param2], FONT_SYSTEM, v0, v2, param5, TEXT_SPEED_NO_TRANSFER, param6, NULL);
}

static void wifi_lobby_map_02260360(WiFiLobbyMapButtonSprites *param0, u32 param1)
{
    Window_ScheduleCopyToVRAM(&param0->unk_04[param1]);
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
        wifi_lobby_map_0225F32C(param1, v0, param2->words[v0]);
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
                param0->unk_AC[v0] = NULL;
                param0->unk_EC[v0] = NULL;
                param0->unk_FC[v0] = NULL;
                continue;
            }
        } else if (v0 == 3) {
            if (v7 == 0) {
                param0->unk_AC[v0] = NULL;
                param0->unk_EC[v0] = NULL;
                param0->unk_FC[v0] = NULL;
                continue;
            }
        }

        if (v11[v0][0] == 192) {
            v2 = v1;
        } else {
            v2 = param2;
        }

        param0->unk_AC[v0] = SpriteResourceCollection_AddPaletteFrom(param1->unk_194[1], v2, v11[v0][1], 0, 150 + v0, NNS_G2D_VRAM_TYPE_2DSUB, v11[v0][2], heapID);
        v3 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_AC[v0]);
        GF_ASSERT(v3);

        SpriteResource_ReleaseData(param0->unk_AC[v0]);

        param0->unk_EC[v0] = SpriteResourceCollection_AddFrom(param1->unk_194[2], v2, v12[v0], 0, 150 + v0, 2, heapID);
        param0->unk_FC[v0] = SpriteResourceCollection_AddFrom(param1->unk_194[3], v2, v13[v0], 0, 150 + v0, 3, heapID);
    }

    for (v0 = 0; v0 < 12; v0++) {
        v4 = WiFiPlazaLobby_State_GetNthActiveSlot(param4, v0);
        v5 = WiFiPlazaLobby_State_GetNthActiveUserID(param4, v0);

        if (v4 == 24) {
            param0->unk_BC[v0] = NULL;
            param0->unk_7C[v0] = NULL;
        } else {
            v10 = wifi_lobby_map_02260728(v4, v5, v6, v7);

            if (v10->unk_00 == 1) {
                v2 = param2;
            } else {
                v2 = v1;
            }

            param0->unk_BC[v0] = SpriteResourceCollection_AddTilesFrom(param1->unk_194[0], v2, v10->unk_02, 0, 150 + v0, NNS_G2D_VRAM_TYPE_2DSUB, heapID);

            v3 = SpriteTransfer_RequestCharAtEnd(param0->unk_BC[v0]);
            GF_ASSERT(v3);

            SpriteResource_ReleaseData(param0->unk_BC[v0]);
            SpriteResourcesHeader_Init(&v9, 150 + v0, 150 + v10->unk_00, 150 + v10->unk_00, 150 + v10->unk_00, 0xffffffff, 0xffffffff, 0, 0, param1->unk_194[0], param1->unk_194[1], param1->unk_194[2], param1->unk_194[3], NULL, NULL);

            v8.list = param1->unk_04;
            v8.resourceData = &v9;
            v8.priority = 0;
            v8.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
            v8.heapID = heapID;
            v8.position = Unk_wifi_lobby_map_0226D7B4[v0];
            v8.position.x += FX32_CONST(v10->unk_04);
            v8.position.y += FX32_CONST(v10->unk_06);

            param0->unk_7C[v0] = SpriteList_Add(&v8);

            Sprite_SetExplicitPaletteOffsetAutoAdjust(param0->unk_7C[v0], v10->unk_01);
        }
    }

    NARC_dtor(v1);
}

static void wifi_lobby_map_0226068C(WiFiLobbyMapButtonSprites *param0, WiFiLobbyMapRenderer *param1)
{
    int v0;

    for (v0 = 0; v0 < 12; v0++) {
        if (param0->unk_BC[v0] != NULL) {
            Sprite_Delete(param0->unk_7C[v0]);

            param0->unk_7C[v0] = NULL;

            SpriteTransfer_ResetCharTransfer(param0->unk_BC[v0]);
            SpriteResourceCollection_Remove(param1->unk_194[0], param0->unk_BC[v0]);

            param0->unk_BC[v0] = NULL;
        }
    }

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->unk_AC[v0] != NULL) {
            SpriteTransfer_ResetPlttTransfer(param0->unk_AC[v0]);
            SpriteResourceCollection_Remove(param1->unk_194[1], param0->unk_AC[v0]);
            SpriteResourceCollection_Remove(param1->unk_194[2], param0->unk_EC[v0]);
            SpriteResourceCollection_Remove(param1->unk_194[3], param0->unk_FC[v0]);
            param0->unk_AC[v0] = NULL;
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

    Window_AddFromTemplate(param1->unk_00, &param0->unk_0C, &Unk_wifi_lobby_map_0226D5A4);

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
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param4, 55, param1->unk_00, Unk_wifi_lobby_map_0226D5CC[1], 0, 0, 0, heapID);

    param0->unk_08 = 0;
    param0->unk_0A = WiFiPlazaLobby_State_GetAppearanceRank(param3);

    Graphics_LoadTilesToBgLayerFromOpenNARC(param4, 0 + param0->unk_0A, param1->unk_00, Unk_wifi_lobby_map_0226D5CC[3], 320, 0, 0, heapID);
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
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param3, 55, param1->unk_00, Unk_wifi_lobby_map_0226D5CC[1], 0, 0, 0, heapID);
    }

    param0->unk_08 = 1;
    param0->unk_0A = param2;

    Graphics_LoadTilesToBgLayerFromOpenNARC(param3, 93 + param0->unk_0A, param1->unk_00, Unk_wifi_lobby_map_0226D5CC[3], 320, 0, 0, heapID);

    if (param0->unk_02 == 0) {
        wifi_lobby_map_022609D4(param0, param1, 0, param3, heapID);
    } else {
        wifi_lobby_map_022609D4(param0, param1, 2, param3, heapID);
    }
}

static void wifi_lobby_map_022609A8(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1)
{
    Bg_ClearTilemap(param1->unk_00, Unk_wifi_lobby_map_0226D5CC[1]);
    Bg_ClearTilemap(param1->unk_00, Unk_wifi_lobby_map_0226D5CC[2]);
    Bg_ClearTilemap(param1->unk_00, Unk_wifi_lobby_map_0226D5CC[3]);
    Bg_SetOffset(param1->unk_00, Unk_wifi_lobby_map_0226D5CC[3], 3, 0);
}

static void wifi_lobby_map_022609D4(WiFiLobbyMapTouchButton *param0, WiFiLobbyMapRenderer *param1, u32 param2, NARC *param3, u32 heapID)
{
    static const s8 v0[3] = {
        0, 9, 6
    };

    Bg_CopyToTilemapRect(param1->unk_00, Unk_wifi_lobby_map_0226D5CC[2], 0, 3, 32, 21, (const void *)param0->unk_2C[param2]->rawData, 0, 3, 32, 32);
    Bg_ScheduleTilemapTransfer(param1->unk_00, Unk_wifi_lobby_map_0226D5CC[2]);

    if (param0->unk_08 == 1) {
        static const u8 v1[3] = {
            0, 1, 0
        };
        u32 v2;

        v2 = (param0->unk_0A * 2) + v1[param2];
        wifi_lobby_map_0225FA14(param1, param3, 96 + v2, Unk_wifi_lobby_map_0226D5CC[3], 320, heapID);
    }

    Bg_ScheduleScroll(param1->unk_00, Unk_wifi_lobby_map_0226D5CC[3], 3, v0[param2]);
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
