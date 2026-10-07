#include "wifi_note/wifi_note.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"
#include "constants/savedata/vars_flags.h"
#include "constants/string.h"

#include "struct_decls/wi_fi_list.h"
#include "struct_defs/battle_frontier.h"
#include "struct_defs/struct_02089438.h"

#include "applications/naming_screen.h"
#include "overlay063/ov63_0222AE60.h"
#include "overlay063/struct_ov63_0222AE60_decl.h"
#include "overlay063/struct_ov63_0222BB38_decl.h"
#include "wifi_note/struct_wifi_note_sprite_params.h"

#include "appearance.h"
#include "ascii_util.h"
#include "bag.h"
#include "battle_frontier_save.h"
#include "bg_window.h"
#include "char_transfer.h"
#include "character_sprite.h"
#include "enums.h"
#include "font.h"
#include "game_options.h"
#include "game_overlay.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "inlines.h"
#include "list_menu.h"
#include "menu.h"
#include "message.h"
#include "message_util.h"
#include "narc.h"
#include "overlay_manager.h"
#include "pltt_transfer.h"
#include "pokemon.h"
#include "render_oam.h"
#include "render_text.h"
#include "render_view.h"
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
#include "system.h"
#include "system_flags.h"
#include "text.h"
#include "trainer_info.h"
#include "wifi_friend_registration.h"
#include "number_entry_app.h"
#include "vars_flags.h"
#include "vram_transfer.h"
#include "wifi_list.h"

#include "constdata/const_020F2DBC.h"

FS_EXTERN_OVERLAY(overlay63);

typedef struct {
    u32 entryID;
    u32 index;
} WiFiNoteActionMenuEntry;

typedef struct {
    s16 x;
    s16 y;
    u8 width;
    u8 height;
} WiFiNotePageOffset;

typedef struct {
    void *raw[2];
    NNSG2dScreenData *data[2];
} WiFiNoteScreenData;

typedef struct {
    String *name;
    String *friendCode;
} WiFiNoteStateStrings;

typedef struct {
    const u16 *text;
    BOOL pending;
} WiFiNoteStateNameInput;

typedef struct {
    u32 count;
    u8 indices[32];
} WiFiNoteFriendIndexList;

typedef struct {
    SaveData *saveData;
    u8 subState;
    u8 nextPage;
    u8 nextSubState;
    s8 selectedFriend;
    WiFiNoteFriendIndexList friendIndexList;
    WiFiNoteStateStrings strings;
    WiFiNoteStateNameInput nameInput;
} WiFiNoteState;

typedef struct {
    BgConfig *bgConfig;
    SpriteList *spriteList;
    NNSG2dRenderSurface renderSurface;
    G2dRenderer g2dRenderer;
    SpriteResourceCollection *spriteResources[4];
    StringTemplate *stringTemplate;
    MessageLoader *messageLoader;
    NARC *narc;
    Window messageWindow;
    String *string;
    String *fmtString;
    u32 printer;
    SpriteResourcesHeader spriteResourcesHeader;
    SpriteResource *spriteResource[4];
    Sprite *arrows[2];
    WiFiNoteScreenData screenData;
} WiFiNoteGraphics;

typedef struct {
    u32 selection;
    Window window;
    void *screenDataRaw;
    NNSG2dScreenData *screenData;
    Window messageWindow;
    Menu *yesNoMenu;
    u32 printer;
    u32 textFrameDelay;
    String *string;
} WiFiNoteFriendCodeEntry;

typedef struct {
    WiFiNotePageOffset offset;
    Window window;
    UnkStruct_ov63_0222BB38 *sprites[8];
} WiFiNoteFriendSlot;

typedef struct {
    WiFiNotePageOffset rect;
    u32 bgLayer;
} WiFiNoteSlotRect;

typedef struct {
    s16 page;
    s16 prevPage;
    s16 slot;
    s16 prevSlot;
    WiFiNoteFriendSlot slots[3];
    s16 transitionTimer;
    u16 transitionDir;
    UnkStruct_ov63_0222AE60 *spriteManager;
    Window headerWindow;
    Window messageWindow;
    String *string;
    u32 printer;
    u32 textFrameDelay;
    Window menuWindow;
    StringList *menuChoices[2];
    ListMenu *listMenu;
    Menu *yesNoMenu;
    s32 deleteTimer;
    Sprite *deleteSprite;
    u32 deleteAnimFrame;
} WiFiNoteFriendList;

typedef struct {
    ApplicationManager *appMan;
    NamingScreenArgs *namingScreenArgs;
    NumberEntryArgs *numberEntryArgs;
} WiFiNoteNamingScreen;

typedef struct {
    Window window;
    Window codeWindow;
    void *screenDataRaw;
    NNSG2dScreenData *screenData;
} WiFiNoteOwnCode;

typedef struct {
    void *screenDataRaw[7];
    NNSG2dScreenData *screenData[7];
} WiFiNoteDetailGraphics;

typedef struct {
    WiFiNotePageOffset offset;
    u32 baseTile;
    Window *windows[7];
    u32 windowCounts[7];
} WiFiNoteDetailPage;

typedef struct {
    s16 page;
    s16 prevPage;
    s32 transitionTimer;
    int transitionDir;
    u16 holdDelay;
    u16 holdActive;
    BOOL isFirstArrival;
    WiFiNoteDetailPage pages[3];
    WiFiNoteDetailGraphics graphics;
} WiFiNoteFriendDetail;

typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
} WiFiNoteWindowRect;

typedef struct {
    u32 page;
    WiFiNoteGraphics graphics;
    WiFiNoteState state;
    WiFiNoteFriendCodeEntry friendCodeEntry;
    WiFiNoteFriendList friendList;
    WiFiNoteNamingScreen namingScreen;
    WiFiNoteOwnCode ownCode;
    WiFiNoteFriendDetail friendDetail;
    s32 transitionDelay;
} WiFiNote;

static void WiFiNote_VBlankCallback(void *param0);
static void WiFiNote_ReinitScreens(WiFiNote *param0, enum HeapID heapID);
static void WiFiNote_FreeScreens(WiFiNote *param0);
static void WiFiNoteState_Init(WiFiNoteState *param0, void *param1, enum HeapID heapID);
static void WiFiNoteState_Free(WiFiNoteState *param0);
static void WiFiNoteState_SetPage(WiFiNoteState *param0, u8 param1, u8 param2);
static void WiFiNoteState_SetInputStrings(WiFiNoteState *param0, const String *param1, const String *param2);
static u32 WiFiNoteState_RegisterFriend(WiFiNoteState *param0, String *param1, String *param2);
static void WiFiNoteState_SetPendingName(WiFiNoteState *param0, const u16 *param1);
static void WiFiNoteState_SetSelectedFriend(WiFiNoteState *param0, u32 param1);
static void WiFiNoteState_BuildFriendIndexList(WiFiNoteState *param0);
static void WiFiNoteGraphics_Init(WiFiNoteGraphics *param0, const WiFiNoteState *param1, enum HeapID heapID);
static void WiFiNoteGraphics_UpdateSprites(WiFiNoteGraphics *param0);
static void WiFiNoteGraphics_ProcessVBlank(WiFiNoteGraphics *param0);
static void WiFiNoteGraphics_Free(WiFiNoteGraphics *param0);
static void WiFiNoteGraphics_SetBanks(void);
static void WiFiNoteGraphics_InitBackgrounds(WiFiNoteGraphics *param0, enum HeapID heapID);
static void WiFiNoteGraphics_FreeBackgrounds(WiFiNoteGraphics *param0);
static void WiFiNoteGraphics_InitSpriteSystem(WiFiNoteGraphics *param0, enum HeapID heapID);
static void WiFiNoteGraphics_FreeSpriteSystem(WiFiNoteGraphics *param0);
static void WiFiNoteGraphics_InitMessageLoader(WiFiNoteGraphics *param0, enum HeapID heapID);
static void WiFiNoteGraphics_FreeMessageLoader(WiFiNoteGraphics *param0);
static void WiFiNoteGraphics_InitMessageBox(WiFiNoteGraphics *param0, const WiFiNoteState *param1, enum HeapID heapID);
static void WiFiNoteGraphics_FreeMessageBox(WiFiNoteGraphics *param0);
static void WiFiNoteGraphics_LoadScreenData(WiFiNoteGraphics *param0, enum HeapID heapID);
static void WiFiNoteGraphics_FreeScreenData(WiFiNoteGraphics *param0);
static void WiFiNoteGraphics_PrintMessage(WiFiNoteGraphics *param0, u32 param1);
static void WiFiNoteGraphics_ClearMessageBox(WiFiNoteGraphics *param0);
static void WiFiNoteGraphics_FormatFriendCode(WiFiNoteGraphics *param0, u64 param1);
static void WiFiNoteGraphics_SetNumber(WiFiNoteGraphics *param0, u32 param1);
static void WiFiNoteGraphics_SetPlazaMinigameName(WiFiNoteGraphics *param0, u32 param1);
static void WiFiNoteGraphics_InitArrows(WiFiNoteGraphics *param0, enum HeapID heapID);
static void WiFiNoteGraphics_DeleteArrows(WiFiNoteGraphics *param0);
static void WiFiNoteGraphics_SetArrowsVisible(WiFiNoteGraphics *param0, BOOL param1);
static void WiFiNoteGraphics_SetArrowsAnimating(WiFiNoteGraphics *param0, BOOL param1);
static void WiFiNoteFriendCodeEntry_Init(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static int WiFiNoteFriendCodeEntry_Main(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteFriendCodeEntry_Free(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteFriendCodeEntry_CreateWindows(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteFriendCodeEntry_DestroyWindows(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteFriendCodeEntry_Draw(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static BOOL WiFiNoteFriendCodeEntry_HandleInput(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteFriendCodeEntry_HighlightSelection(WiFiNoteFriendCodeEntry *param0, WiFiNoteGraphics *param1);
static void WiFiNoteFriendCodeEntry_SetNextPage(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1);
static void WiFiNoteFriendCodeEntry_ClearScreen(WiFiNoteFriendCodeEntry *param0, WiFiNoteGraphics *param1);
static void WiFiNoteFriendCodeEntry_ShowMessage(WiFiNoteFriendCodeEntry *param0, WiFiNoteGraphics *param1, u32 param2, enum HeapID heapID);
static BOOL WiFiNoteFriendCodeEntry_IsMessageDone(const WiFiNoteFriendCodeEntry *param0);
static void WiFiNoteFriendCodeEntry_EraseMessageBox(WiFiNoteFriendCodeEntry *param0);
static BOOL WiFiNoteFriendCodeEntry_CanAddFriend(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1);
static void WiFiNoteFriendList_Init(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static int WiFiNoteFriendList_Main(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteFriendList_Free(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteFriendList_CreateWindows(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteFriendList_DestroyWindows(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteFriendList_Draw(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteFriendList_Clear(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static u32 WiFiNoteFriendList_HandleInput(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteFriendList_StartTransition(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static BOOL WiFiNoteFriendList_UpdateTransition(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteFriendList_OpenActionMenu(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static u32 WiFiNoteFriendList_ProcessActionMenu(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static BOOL WiFiNoteFriendList_ShowFriendCode(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteFriendList_ConfirmDelete(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static BOOL WiFiNoteFriendList_CreateDeleteConfirmMenu(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteFriendList_DrawFriendSlot(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, u32 param3, u32 param4, u32 param5, enum HeapID heapID);
static void WiFiNoteFriendList_DrawSelectionCursor(WiFiNoteFriendList *param0, WiFiNoteGraphics *param1, u32 param2);
static void WiFiNoteFriendList_DrawCursorLeft(WiFiNoteFriendList *param0, WiFiNoteGraphics *param1, u32 param2, u32 param3);
static void WiFiNoteFriendList_DrawCursorRight(WiFiNoteFriendList *param0, WiFiNoteGraphics *param1, u32 param2, u32 param3);
static void WiFiNoteFriendList_BeginTransition(WiFiNoteFriendList *param0, WiFiNoteState *param1, int param2);
static void WiFiNoteFriendList_ShowMessage(WiFiNoteFriendList *param0, WiFiNoteGraphics *param1, u32 param2, enum HeapID heapID);
static BOOL WiFiNoteFriendList_IsMessageDone(const WiFiNoteFriendList *param0);
static void WiFiNoteFriendList_EraseMessageBox(WiFiNoteFriendList *param0);
static u32 WiFiNoteFriendList_GetSelectedFriend(const WiFiNoteFriendList *param0);
static void WiFiNoteFriendList_ListMenuCursorCallback(ListMenu *param0, u32 param1, u8 param2);
static void WiFiNoteFriendList_StartDeleteAnimation(WiFiNoteFriendList *param0);
static BOOL WiFiNoteFriendList_UpdateDeleteAnimation(WiFiNoteFriendList *param0);
static void WiFiNoteFriendList_EndDeleteAnimation(WiFiNoteFriendList *param0);
static void WiFiNoteFriendSlot_Init(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1, const WiFiNotePageOffset *param2, u32 param3, u32 param4);
static void WiFiNoteFriendSlot_Free(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1);
static void WiFiNoteFriendSlot_DrawBackground(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1, const WiFiNoteScreenData *param2);
static void WiFiNoteFriendSlot_Highlight(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1, u32 param2);
static void WiFiNoteFriendSlot_DrawEntries(WiFiNoteFriendSlot *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, UnkStruct_ov63_0222AE60 *param3, const WiFiNoteScreenData *param4, const WiFiNoteFriendIndexList *param5, u32 param6, enum HeapID heapID);
static void WiFiNoteFriendSlot_Clear(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1, const WiFiNoteScreenData *param2);
static void WiFiNoteFriendSlot_DeleteSprites(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1);
static void WiFiNoteFriendSlot_DrawFriend(WiFiNoteFriendSlot *param0, UnkStruct_ov63_0222AE60 *param1, WiFiNoteGraphics *param2, const WiFiNoteScreenData *param3, u32 param4, WiFiList *param5, u32 param6, enum HeapID heapID);
static void WiFiNoteFriendSlot_DrawEmpty(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1, const WiFiNoteScreenData *param2, u32 param3);
static void WiFiNoteNamingScreen_Init(WiFiNoteNamingScreen *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static int WiFiNoteNamingScreen_Main(WiFiNoteNamingScreen *param0, WiFiNote *param1, WiFiNoteState *param2, WiFiNoteGraphics *param3, enum HeapID heapID);
static void WiFiNoteNamingScreen_Free(WiFiNoteNamingScreen *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteNamingScreen_Create(WiFiNoteNamingScreen *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteNamingScreen_Destroy(WiFiNoteNamingScreen *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static NamingScreenArgs *WiFiNoteNamingScreen_MakeArgs(WiFiNoteNamingScreen *param0, WiFiNoteState *param1, enum HeapID heapID);
static void WiFiNoteOwnCode_Init(WiFiNoteOwnCode *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static int WiFiNoteOwnCode_Main(WiFiNoteOwnCode *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteOwnCode_Free(WiFiNoteOwnCode *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteOwnCode_CreateWindows(WiFiNoteOwnCode *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteOwnCode_DestroyWindows(WiFiNoteOwnCode *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteOwnCode_Draw(WiFiNoteOwnCode *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteOwnCode_Clear(WiFiNoteOwnCode *param0, WiFiNoteGraphics *param1);
static void WiFiNoteFriendDetail_Init(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static int WiFiNoteFriendDetail_Main(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteFriendDetail_Free(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteFriendDetail_StartTransition(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, u32 param3);
static BOOL WiFiNoteFriendDetail_UpdateTransition(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, u32 param3);
static void WiFiNoteFriendDetail_CreatePages(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteFriendDetail_DestroyPages(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2);
static void WiFiNoteFriendDetail_Draw(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteFriendDetail_Clear(WiFiNoteFriendDetail *param0, WiFiNoteGraphics *param1);
static void WiFiNoteFriendDetail_DrawPage(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, u32 param3, u32 param4, u32 param5);
static void WiFiNoteFriendDetail_DrawSelectionCursor(WiFiNoteFriendDetail *param0, WiFiNoteGraphics *param1, u32 param2, u32 param3);
static void WiFiNoteFriendDetail_ClearSelectionCursor(WiFiNoteFriendDetail *param0, WiFiNoteGraphics *param1);
static void WiFiNoteFriendDetail_DrawCursorLeft(WiFiNoteFriendDetail *param0, WiFiNoteGraphics *param1, u32 param2, u32 param3);
static void WiFiNoteFriendDetail_DrawCursorRight(WiFiNoteFriendDetail *param0, WiFiNoteGraphics *param1, u32 param2, u32 param3);
static BOOL WiFiNoteFriendDetail_FindNextFriend(WiFiNoteState *param0, int param1);
static void WiFiNoteDetailPage_LoadGraphics(WiFiNoteDetailGraphics *param0, WiFiNoteGraphics *param1, enum HeapID heapID);
static void WiFiNoteDetailPage_FreeGraphics(WiFiNoteDetailGraphics *param0);
static void WiFiNoteDetailPage_Init(WiFiNoteDetailPage *param0, WiFiNoteGraphics *param1, const WiFiNotePageOffset *param2, u32 param3, enum HeapID heapID);
static void WiFiNoteDetailPage_Free(WiFiNoteDetailPage *param0);
static void WiFiNoteDetailPage_CreateWindows(WiFiNoteDetailPage *param0, WiFiNoteGraphics *param1, u32 param2, u32 param3, const WiFiNoteWindowRect *param4, enum HeapID heapID);
static void WiFiNoteDetailPage_DeleteWindows(WiFiNoteDetailPage *param0, u32 param1);
static void WiFiNoteDetailPage_ScheduleWindowCopy(WiFiNoteDetailPage *param0, u32 param1);
static void WiFiNoteDetailPage_ClearWindows(WiFiNoteDetailPage *param0, u32 param1);
static void WiFiNoteDetailPage_Draw(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, u32 param3, const WiFiNoteDetailGraphics *param4, u32 param5);
static void WiFiNoteDetailPage_Clear(WiFiNoteDetailPage *param0, WiFiNoteGraphics *param1);
static void WiFiNoteDetailPage_DrawProfile(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteDetailPage_DrawTower(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteDetailPage_DrawFactory(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteDetailPage_DrawCastle(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteDetailPage_DrawHall(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteDetailPage_DrawArcade(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteDetailPage_DrawMinigame(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID);
static void WiFiNoteDetailPage_ClearBackground(WiFiNoteGraphics *param0, const WiFiNotePageOffset *param1);
static void WiFiNoteDetailPage_PrintText(WiFiNoteDetailPage *param0, u32 param1, u32 param2, WiFiNoteState *param3, WiFiNoteGraphics *param4, u32 entryID, u32 xOffset, u32 yOffset, TextColor color, String *string, String *fmtString, u32 param11);
static void WiFiNoteFriendDetail_ChangePage(WiFiNoteFriendDetail *param0, s32 param1);
static BOOL WiFiNoteState_HasPoffinCase(WiFiNoteState *param0, enum HeapID heapID);

static const WiFiNotePageOffset sPageOffsets[3] = {
    { 0x0, 0x0, 0x20, 0x18 },
    { 0x20, 0x0, 0x20, 0x18 },
    { 0xFFFFFFFFFFFFFFE0, 0x0, 0x20, 0x18 }
};

static const BgTemplate sBgTemplates[5] = {
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xc000,
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
        .screenBase = GX_BG_SCRBASE_0xc800,
        .charBase = GX_BG_CHARBASE_0x04000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x1000,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_512x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xd000,
        .charBase = GX_BG_CHARBASE_0x10000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x2,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x1000,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_512x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe000,
        .charBase = GX_BG_CHARBASE_0x20000,
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
        .screenBase = GX_BG_SCRBASE_0xc000,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    }
};

static const u32 sBgLayers[5] = {
    0x0,
    0x1,
    0x2,
    0x3,
    0x4
};

static NNSG2dViewRect sViewRect = {
    { 0x0, (FX32_CONST(256)) },
    { (255 << FX32_SHIFT), (192 << FX32_SHIFT) }
};

static const WindowTemplate sYesNoWindowTemplate = {
    0x1,
    0x19,
    0xD,
    0x6,
    0x4,
    0x7,
    0xDC
};

static const WiFiNoteSlotRect sSlotRects[9] = {
    { { 0x1, 0x4, 0xF, 0x4 },
        0x2 },
    { { 0x1, 0x8, 0xF, 0x4 },
        0x2 },
    { { 0x1, 0xC, 0xF, 0x4 },
        0x2 },
    { { 0x1, 0x10, 0xF, 0x4 },
        0x2 },
    { { 0x10, 0x4, 0xF, 0x4 },
        0x2 },
    { { 0x10, 0x8, 0xF, 0x4 },
        0x2 },
    { { 0x10, 0xC, 0xF, 0x4 },
        0x2 },
    { { 0x10, 0x10, 0xF, 0x4 },
        0x2 },
    { { 0xB, 0x14, 0xA, 0x4 },
        0x0 }
};

static const u8 sCursorTileOffsets[4] = {
    0x0,
    0x1,
    0x2,
    0x3
};

static const WiFiNoteActionMenuEntry sActionMenuEntries[2][4] = {
    { { 0x8, (u32)7 },
        { 0x9, (u32)10 },
        { 0xA, (u32)15 },
        { 0xB, (u32)2 } },
    { { 0x38, (u32)21 },
        { 0x9, (u32)10 },
        { 0xA, (u32)15 },
        { 0xB, (u32)2 } }
};

static const ListMenuTemplate sActionMenuTemplate = {
    NULL,
    WiFiNoteFriendList_ListMenuCursorCallback,
    NULL,
    NULL,
    0x4,
    0x4,
    0x0,
    0x8,
    0x0,
    0x0,
    0x1,
    0xF,
    0x2,
    0x0,
    0x10,
    0x1,
    0x0,
    0x0,
    NULL
};

static const WiFiNoteWindowRect sProfileWindowRects[5] = {
    { 0xE, 0x4, 0x10, 0x6 },
    { 0x16, 0xA, 0x8, 0x5 },
    { 0xE, 0xF, 0x11, 0x6 },
    { 0x2, 0x15, 0x1C, 0x3 },
    { 0x1, 0x5, 0xB, 0xD }
};

static const WiFiNoteWindowRect sTowerWindowRects[1] = {
    { 0x2, 0x4, 0x14, 0x9 }
};

static const WiFiNoteWindowRect sFactoryWindowRects[5] = {
    { 0x2, 0x5, 0xE, 0x2 },
    { 0x2, 0x8, 0x1C, 0x2 },
    { 0x2, 0xB, 0x1C, 0x4 },
    { 0x2, 0x10, 0x1C, 0x2 },
    { 0x2, 0x13, 0x1C, 0x4 }
};

static const WiFiNoteWindowRect sCastleWindowRects[1] = {
    { 0x2, 0x5, 0x1C, 0xB }
};

static const WiFiNoteWindowRect sHallWindowRects[1] = {
    { 0x2, 0x5, 0x14, 0xB }
};

static const WiFiNoteWindowRect sArcadeWindowRects[1] = {
    { 0x2, 0x5, 0x14, 0xB }
};

static const WiFiNoteWindowRect sMinigameWindowRects[1] = {
    { 0x2, 0x5, 0x16, 0xB }
};

static const WiFiNoteWindowRect *sDetailPageWindowRects[7] = {
    sProfileWindowRects,
    sMinigameWindowRects,
    sTowerWindowRects,
    sFactoryWindowRects,
    sCastleWindowRects,
    sHallWindowRects,
    sArcadeWindowRects
};

static const u8 sDetailPageWindowCounts[7] = {
    0x5,
    0x1,
    0x1,
    0x5,
    0x1,
    0x1,
    0x1
};

int WiFiNote_Init(ApplicationManager *appMan, int *param1)
{
    WiFiNote *v0;

    Overlay_LoadByID(FS_OVERLAY_ID(overlay63), 2);
    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_52, 0x70000);

    v0 = ApplicationManager_NewData(appMan, sizeof(WiFiNote), HEAP_ID_52);
    memset(v0, 0, sizeof(WiFiNote));

    WiFiNoteState_Init(&v0->state, ApplicationManager_Args(appMan), HEAP_ID_52);
    WiFiNoteGraphics_Init(&v0->graphics, &v0->state, HEAP_ID_52);
    WiFiNoteFriendCodeEntry_Init(&v0->friendCodeEntry, &v0->state, &v0->graphics, HEAP_ID_52);
    WiFiNoteFriendList_Init(&v0->friendList, &v0->state, &v0->graphics, HEAP_ID_52);
    WiFiNoteNamingScreen_Init(&v0->namingScreen, &v0->state, &v0->graphics, HEAP_ID_52);
    WiFiNoteOwnCode_Init(&v0->ownCode, &v0->state, &v0->graphics, HEAP_ID_52);
    WiFiNoteFriendDetail_Init(&v0->friendDetail, &v0->state, &v0->graphics, HEAP_ID_52);

    SetVBlankCallback(WiFiNote_VBlankCallback, v0);
    DisableHBlank();

    return 1;
}

int WiFiNote_Main(ApplicationManager *appMan, int *param1)
{
    WiFiNote *v0 = ApplicationManager_Data(appMan);
    int v1;

    switch (*param1) {
    case 0:

        switch (v0->page) {
        case 0:
            v1 = WiFiNoteFriendCodeEntry_Main(&v0->friendCodeEntry, &v0->state, &v0->graphics, HEAP_ID_52);
            break;
        case 1:
            v1 = WiFiNoteFriendList_Main(&v0->friendList, &v0->state, &v0->graphics, HEAP_ID_52);
            break;
        case 2:
            v1 = WiFiNoteNamingScreen_Main(&v0->namingScreen, v0, &v0->state, &v0->graphics, HEAP_ID_52);
            break;
        case 3:
            v1 = WiFiNoteOwnCode_Main(&v0->ownCode, &v0->state, &v0->graphics);
            break;
        case 4:
            v1 = WiFiNoteFriendDetail_Main(&v0->friendDetail, &v0->state, &v0->graphics, HEAP_ID_52);
            break;
        case 5:
            return 1;
        }

        if (v1 == 1) {
            v0->page = v0->state.nextPage;
            v0->state.subState = v0->state.nextSubState;
            v0->transitionDelay = 4;
            (*param1) = 1;
        }
        break;
    case 1:
        v0->transitionDelay--;

        if (v0->transitionDelay <= 0) {
            (*param1) = 0;
        }
        break;
    }

    WiFiNoteGraphics_UpdateSprites(&v0->graphics);

    return 0;
}

int WiFiNote_Exit(ApplicationManager *appMan, int *param1)
{
    WiFiNote *v0 = ApplicationManager_Data(appMan);

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    WiFiNoteFriendCodeEntry_Free(&v0->friendCodeEntry, &v0->state, &v0->graphics);
    WiFiNoteFriendList_Free(&v0->friendList, &v0->state, &v0->graphics);
    WiFiNoteNamingScreen_Free(&v0->namingScreen, &v0->state, &v0->graphics);
    WiFiNoteOwnCode_Free(&v0->ownCode, &v0->state, &v0->graphics);
    WiFiNoteFriendDetail_Free(&v0->friendDetail, &v0->state, &v0->graphics);

    WiFiNoteGraphics_Free(&v0->graphics);
    WiFiNoteState_Free(&v0->state);

    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_52);
    Overlay_UnloadByID(FS_OVERLAY_ID(overlay63));

    return 1;
}

static void WiFiNote_VBlankCallback(void *param0)
{
    WiFiNote *v0 = param0;
    WiFiNoteGraphics_ProcessVBlank(&v0->graphics);
}

static void WiFiNote_ReinitScreens(WiFiNote *param0, enum HeapID heapID)
{
    WiFiNoteGraphics_Init(&param0->graphics, &param0->state, heapID);

    WiFiNoteFriendCodeEntry_CreateWindows(&param0->friendCodeEntry, &param0->state, &param0->graphics, heapID);
    WiFiNoteFriendList_CreateWindows(&param0->friendList, &param0->state, &param0->graphics, heapID);
    WiFiNoteNamingScreen_Create(&param0->namingScreen, &param0->state, &param0->graphics, heapID);
    WiFiNoteOwnCode_CreateWindows(&param0->ownCode, &param0->state, &param0->graphics, heapID);
    WiFiNoteFriendDetail_CreatePages(&param0->friendDetail, &param0->state, &param0->graphics, heapID);

    SetVBlankCallback(WiFiNote_VBlankCallback, param0);
    DisableHBlank();
}

static void WiFiNote_FreeScreens(WiFiNote *param0)
{
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    WiFiNoteFriendCodeEntry_DestroyWindows(&param0->friendCodeEntry, &param0->state, &param0->graphics);
    WiFiNoteFriendList_DestroyWindows(&param0->friendList, &param0->state, &param0->graphics);
    WiFiNoteNamingScreen_Destroy(&param0->namingScreen, &param0->state, &param0->graphics);
    WiFiNoteOwnCode_DestroyWindows(&param0->ownCode, &param0->state, &param0->graphics);
    WiFiNoteFriendDetail_DestroyPages(&param0->friendDetail, &param0->state, &param0->graphics);
    WiFiNoteGraphics_Free(&param0->graphics);
}

static void WiFiNoteState_Init(WiFiNoteState *param0, void *param1, enum HeapID heapID)
{
    param0->saveData = param1;
    param0->strings.name = String_Init(128, heapID);
    param0->strings.friendCode = String_Init(128, heapID);
}

static void WiFiNoteState_Free(WiFiNoteState *param0)
{
    String_Free(param0->strings.name);
    String_Free(param0->strings.friendCode);
}

static void WiFiNoteState_SetPage(WiFiNoteState *param0, u8 param1, u8 param2)
{
    param0->nextPage = param1;
    param0->nextSubState = param2;
}

static void WiFiNoteState_SetInputStrings(WiFiNoteState *param0, const String *param1, const String *param2)
{
    if (param1) {
        String_Copy(param0->strings.name, param1);
    }

    if (param2) {
        String_Copy(param0->strings.friendCode, param2);
    }
}

static u32 WiFiNoteState_RegisterFriend(WiFiNoteState *param0, String *param1, String *param2)
{
    int v0;
    WiFiList *v1;
    BOOL v2;
    BOOL v3;
    u64 v4;
    u64 v5;
    DWCFriendData *v6 = NULL;
    DWCUserData *v7 = NULL;
    int v8;
    int v9;

    v1 = SaveData_GetWiFiList(param0->saveData);
    v5 = DWC_CreateFriendKey(WiFiList_GetUserData(v1));

    for (v0 = 0; v0 < 32; v0++) {
        v2 = WiFiList_IsValidFriendData(v1, v0);

        if (v2 == 0) {
            v4 = String_AtoI(param1, &v3);

            if ((v3 == 1) && (v4 != v5)) {
                v7 = WiFiList_GetUserData(v1);

                if (!DWC_CheckFriendKey(v7, v4)) {
                    return 1;
                }

                v8 = WiFiFriend_FindSlotByFriendKey(param0->saveData, v4, &v9);

                if (v8 == 0) {
                    return 2;
                }

                v6 = WiFiList_GetFriendData(v1, v0);
                DWC_CreateFriendKeyToken(v6, v4);

                WiFiList_SetFriendPlayerName(v1, v0, param2);
                WiFiList_SetFriendField(v1, v0, 8, 2);
                return 0;
            } else {
                return 1;
            }
        }
    }

    GF_ASSERT(FALSE);

    return 0;
}

static void WiFiNoteState_SetPendingName(WiFiNoteState *param0, const u16 *param1)
{
    param0->nameInput.text = param1;
    param0->nameInput.pending = 1;
}

static void WiFiNoteState_SetSelectedFriend(WiFiNoteState *param0, u32 param1)
{
    param0->selectedFriend = param1;
}

static void WiFiNoteState_BuildFriendIndexList(WiFiNoteState *param0)
{
    int v0;
    WiFiList *v1;

    memset(&param0->friendIndexList, 0, sizeof(WiFiNoteFriendIndexList));

    v1 = SaveData_GetWiFiList(param0->saveData);

    param0->friendIndexList.count = 0;

    for (v0 = 0; v0 < (8 * 4); v0++) {
        if (WiFiList_IsValidFriendData(v1, v0) == 1) {
            param0->friendIndexList.indices[param0->friendIndexList.count] = v0;
            param0->friendIndexList.count++;
        }
    }
}

static void WiFiNoteGraphics_Init(WiFiNoteGraphics *param0, const WiFiNoteState *param1, enum HeapID heapID)
{
    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;
    GXLayers_SwapDisplay();
    param0->narc = NARC_ctor(NARC_INDEX_GRAPHIC__PL_WIFINOTE, heapID);

    WiFiNoteGraphics_SetBanks();
    WiFiNoteGraphics_InitBackgrounds(param0, heapID);
    WiFiNoteGraphics_InitSpriteSystem(param0, heapID);
    WiFiNoteGraphics_InitMessageLoader(param0, heapID);
    WiFiNoteGraphics_InitMessageBox(param0, param1, heapID);
    WiFiNoteGraphics_InitArrows(param0, heapID);
    WiFiNoteGraphics_LoadScreenData(param0, heapID);

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    RenderControlFlags_SetCanABSpeedUpPrint(TRUE);
    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_DISABLED);
    RenderControlFlags_SetSpeedUpOnTouch(FALSE);
}

static void WiFiNoteGraphics_UpdateSprites(WiFiNoteGraphics *param0)
{
    SpriteList_Update(param0->spriteList);
}

static void WiFiNoteGraphics_ProcessVBlank(WiFiNoteGraphics *param0)
{
    Bg_RunScheduledUpdates(param0->bgConfig);
    VramTransfer_Process();
    RenderOam_Transfer();
}

static void WiFiNoteGraphics_Free(WiFiNoteGraphics *param0)
{
    WiFiNoteGraphics_DeleteArrows(param0);
    WiFiNoteGraphics_FreeScreenData(param0);
    WiFiNoteGraphics_FreeMessageBox(param0);
    WiFiNoteGraphics_FreeMessageLoader(param0);
    WiFiNoteGraphics_FreeSpriteSystem(param0);
    WiFiNoteGraphics_FreeBackgrounds(param0);

    NARC_dtor(param0->narc);
}

static void WiFiNoteGraphics_SetBanks(void)
{
    GXBanks v0 = {
        GX_VRAM_BG_256_AB,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_80_EF,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_NONE,
        GX_VRAM_TEXPLTT_NONE
    };

    GXLayers_SetBanks(&v0);
}

static void WiFiNoteGraphics_InitBackgrounds(WiFiNoteGraphics *param0, enum HeapID heapID)
{
    int v0;

    param0->bgConfig = BgConfig_New(heapID);

    {
        GraphicsModes v1 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D,
        };

        SetAllGraphicsModes(&v1);
    }

    for (v0 = 0; v0 < 5; v0++) {
        Bg_InitFromTemplate(param0->bgConfig, sBgLayers[v0], &sBgTemplates[v0], 0);
        Bg_ClearTilesRange(sBgLayers[v0], 32, 0, heapID);
        Bg_ClearTilemap(param0->bgConfig, sBgLayers[v0]);
    }

    Graphics_LoadPaletteFromOpenNARC(param0->narc, 0, 0, 0, ((6 + 1) - 0) * 32, heapID);
    Graphics_LoadPaletteFromOpenNARC(param0->narc, 0, 4, 0, ((4 + 1) - 0) * 32, heapID);

    Graphics_LoadTilesToBgLayerFromOpenNARC(param0->narc, 18, param0->bgConfig, sBgLayers[0], 0, 0, 0, heapID);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param0->narc, 18, param0->bgConfig, sBgLayers[2], 0, 0, 0, heapID);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param0->narc, 13, param0->bgConfig, sBgLayers[4], 0, 0, 0, heapID);

    Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->narc, 12, param0->bgConfig, sBgLayers[0], 0, 0, 0, heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->narc, 14, param0->bgConfig, sBgLayers[4], 0, 0, 0, heapID);
}

static void WiFiNoteGraphics_FreeBackgrounds(WiFiNoteGraphics *param0)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        Bg_FreeTilemapBuffer(param0->bgConfig, sBgLayers[v0]);
    }

    Heap_Free(param0->bgConfig);
    param0->bgConfig = NULL;
}

static void WiFiNoteGraphics_InitSpriteSystem(WiFiNoteGraphics *param0, enum HeapID heapID)
{
    int v0;
    BOOL v1;

    NNS_G2dInitOamManagerModule();

    VramTransfer_New(16, heapID);
    RenderOam_Init(0, 126, 0, 30, 0, 126, 0, 30, heapID);

    {
        CharTransferTemplate v2 = {
            64, 0x14000, 0, 0
        };

        v2.heapID = heapID;
        CharTransfer_InitWithVramModes(&v2, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_128K);
    }

    PlttTransfer_Init(64, heapID);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();

    param0->spriteList = SpriteList_InitRendering(64, &param0->g2dRenderer, heapID);

    RenderOam_InitSurface(&param0->renderSurface, &sViewRect, NNS_G2D_SURFACETYPE_MAIN2D, &param0->g2dRenderer.renderer);

    for (v0 = 0; v0 < 4; v0++) {
        param0->spriteResources[v0] = SpriteResourceCollection_New(64, v0, heapID);
    }

    param0->spriteResource[0] = SpriteResourceCollection_AddTilesFrom(param0->spriteResources[0], param0->narc, 15, 0, 100, NNS_G2D_VRAM_TYPE_2DMAIN, heapID);
    param0->spriteResource[1] = SpriteResourceCollection_AddPaletteFrom(param0->spriteResources[1], param0->narc, 0, 0, 100, NNS_G2D_VRAM_TYPE_2DMAIN, 5, heapID);
    param0->spriteResource[2] = SpriteResourceCollection_AddFrom(param0->spriteResources[2], param0->narc, 16, 0, 100, 2, heapID);
    param0->spriteResource[3] = SpriteResourceCollection_AddFrom(param0->spriteResources[3], param0->narc, 17, 0, 100, 3, heapID);

    v1 = SpriteTransfer_RequestCharAtEnd(param0->spriteResource[0]);
    GF_ASSERT(v1);

    v1 = SpriteTransfer_RequestPlttFreeSpace(param0->spriteResource[1]);
    GF_ASSERT(v1);

    SpriteResource_ReleaseData(param0->spriteResource[0]);
    SpriteResource_ReleaseData(param0->spriteResource[1]);
    SpriteResourcesHeader_Init(&param0->spriteResourcesHeader, 100, 100, 100, 100, 0xffffffff, 0xffffffff, 0, 0, param0->spriteResources[0], param0->spriteResources[1], param0->spriteResources[2], param0->spriteResources[3], NULL, NULL);
}

static void WiFiNoteGraphics_FreeSpriteSystem(WiFiNoteGraphics *param0)
{
    int v0;

    SpriteTransfer_ResetCharTransfer(param0->spriteResource[0]);
    SpriteTransfer_ResetPlttTransfer(param0->spriteResource[1]);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Remove(param0->spriteResources[v0], param0->spriteResource[v0]);
    }

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(param0->spriteResources[v0]);
    }

    SpriteList_Delete(param0->spriteList);
    CharTransfer_Free();
    PlttTransfer_Free();
    RenderOam_Free();
    VramTransfer_Free();
}

static void WiFiNoteGraphics_InitMessageLoader(WiFiNoteGraphics *param0, enum HeapID heapID)
{
    param0->stringTemplate = StringTemplate_Default(heapID);
    param0->messageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_PAL_PAD, heapID);
}

static void WiFiNoteGraphics_FreeMessageLoader(WiFiNoteGraphics *param0)
{
    MessageLoader_Free(param0->messageLoader);
    StringTemplate_Free(param0->stringTemplate);
}

static void WiFiNoteGraphics_InitMessageBox(WiFiNoteGraphics *param0, const WiFiNoteState *param1, enum HeapID heapID)
{
    int v0 = Options_Frame(SaveData_GetOptions(param1->saveData));

    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(7), heapID);
    LoadMessageBoxGraphics(param0->bgConfig, sBgLayers[1], 1 + 9, 8, v0, heapID);
    LoadStandardWindowGraphics(param0->bgConfig, sBgLayers[1], 1, 9, 0, heapID);
    Window_Init(&param0->messageWindow);
    Window_Add(param0->bgConfig, &param0->messageWindow, sBgLayers[1], 1, 0, 24, 3, 7, (1 + 9) + (18 + 12));

    param0->string = String_Init(128, heapID);
    param0->fmtString = String_Init(128, heapID);
}

static void WiFiNoteGraphics_FreeMessageBox(WiFiNoteGraphics *param0)
{
    String_Free(param0->string);
    String_Free(param0->fmtString);
    Window_Remove(&param0->messageWindow);
}

static void WiFiNoteGraphics_LoadScreenData(WiFiNoteGraphics *param0, enum HeapID heapID)
{
    static const u8 v0[2] = {
        2,
        3,
    };
    int v1;

    for (v1 = 0; v1 < 2; v1++) {
        param0->screenData.raw[v1] = Graphics_GetScrnDataFromOpenNARC(param0->narc, v0[v1], 0, &param0->screenData.data[v1], heapID);
    }
}

static void WiFiNoteGraphics_FreeScreenData(WiFiNoteGraphics *param0)
{
    int v0;

    for (v0 = 0; v0 < 2; v0++) {
        Heap_Free(param0->screenData.raw[v0]);
    }
}

static void WiFiNoteGraphics_PrintMessage(WiFiNoteGraphics *param0, u32 param1)
{
    if (Text_IsPrinterActive(param0->printer) == 1) {
        Text_RemovePrinter(param0->printer);
    }

    Window_FillTilemap(&param0->messageWindow, 0);
    MessageLoader_GetString(param0->messageLoader, param1, param0->fmtString);
    StringTemplate_Format(param0->stringTemplate, param0->string, param0->fmtString);

    param0->printer = Text_AddPrinterWithParamsAndColor(&param0->messageWindow, FONT_MESSAGE, param0->string, 0, 4, TEXT_SPEED_QUICK, TEXT_COLOR(15, 2, 0), NULL);

    Window_ScheduleCopyToVRAM(&param0->messageWindow);
}

static void WiFiNoteGraphics_ClearMessageBox(WiFiNoteGraphics *param0)
{
    if (Text_IsPrinterActive(param0->printer) == 1) {
        Text_RemovePrinter(param0->printer);
    }

    Window_ClearAndScheduleCopyToVRAM(&param0->messageWindow);
}

static void WiFiNoteGraphics_FormatFriendCode(WiFiNoteGraphics *param0, u64 param1)
{
    u64 v0;

    v0 = param1 / 100000000;
    StringTemplate_SetNumber(param0->stringTemplate, 1, v0, 4, 2, 1);

    v0 = (param1 / 10000) % 10000;
    StringTemplate_SetNumber(param0->stringTemplate, 2, v0, 4, 2, 1);

    v0 = param1 % 10000;
    StringTemplate_SetNumber(param0->stringTemplate, 3, v0, 4, 2, 1);
}

static void WiFiNoteGraphics_SetFriendName(WiFiNoteGraphics *param0, SaveData *saveData, u32 param2, enum HeapID heapID)
{
    WiFiList *v0 = SaveData_GetWiFiList(saveData);
    TrainerInfo *v1 = TrainerInfo_New(heapID);

    TrainerInfo_SetName(v1, WiFiList_GetFriendPlayerName(v0, param2));
    StringTemplate_SetPlayerName(param0->stringTemplate, 0, v1);
    Heap_Free(v1);
}

static void WiFiNoteGraphics_SetFriendGroupName(WiFiNoteGraphics *param0, SaveData *saveData, u32 param2, enum HeapID heapID)
{
    TrainerInfo *v0 = TrainerInfo_New(heapID);
    WiFiList *v1 = SaveData_GetWiFiList(saveData);

    TrainerInfo_SetName(v0, WiFiList_GetFriendGroupName(v1, param2));
    StringTemplate_SetPlayerName(param0->stringTemplate, 0, v0);
    Heap_Free(v0);
}

static BOOL WiFiNoteGraphics_SetFriendDate(WiFiNoteGraphics *param0, SaveData *saveData, u32 param2)
{
    WiFiList *v0 = SaveData_GetWiFiList(saveData);
    u32 v1;
    BOOL v2 = 1;

    v1 = WiFiList_GetFriendField(v0, param2, 6);

    if (v1 == 0) {
        v2 = 0;
    }

    StringTemplate_SetNumber(param0->stringTemplate, 2, v1, 2, 0, 1);
    v1 = WiFiList_GetFriendField(v0, param2, 4);

    StringTemplate_SetNumber(param0->stringTemplate, 0, v1, 4, 0, 1);
    v1 = WiFiList_GetFriendField(v0, param2, 5);

    StringTemplate_SetMonthName(param0->stringTemplate, 1, v1);

    return v2;
}

static void WiFiNoteGraphics_SetNumber(WiFiNoteGraphics *param0, u32 param1)
{
    StringTemplate_SetNumber(param0->stringTemplate, 0, param1, 4, 1, 1);
}

static void WiFiNoteGraphics_SetPlazaMinigameName(WiFiNoteGraphics *param0, u32 param1)
{
    StringTemplate_SetPlazaMinigameName(param0->stringTemplate, 0, param1);
}

static void WiFiNoteGraphics_InitArrows(WiFiNoteGraphics *param0, enum HeapID heapID)
{
    static AffineSpriteListTemplate v0[2] = {
        { NULL,
            NULL,
            { (FX32_CONST(6)), FX32_CONST(98), 0 },
            { FX32_ONE, FX32_ONE, FX32_ONE },
            0,
            8,
            NNS_G2D_VRAM_TYPE_2DMAIN,
            0 },
        { NULL,
            NULL,
            { (FX32_CONST(249)), FX32_CONST(98), 0 },
            { FX32_ONE, FX32_ONE, FX32_ONE },
            0,
            8,
            NNS_G2D_VRAM_TYPE_2DMAIN,
            0 },
    };
    int v1;

    for (v1 = 0; v1 < 2; v1++) {
        v0[v1].list = param0->spriteList;
        v0[v1].resourceData = &param0->spriteResourcesHeader;
        v0[v1].heapID = heapID;

        param0->arrows[v1] = SpriteList_AddAffine(&v0[v1]);

        Sprite_SetAnimateFlag(param0->arrows[v1], 1);
        Sprite_SetDrawFlag(param0->arrows[v1], FALSE);
        Sprite_SetAnim(param0->arrows[v1], v1);
    }
}

static void WiFiNoteGraphics_DeleteArrows(WiFiNoteGraphics *param0)
{
    int v0;

    for (v0 = 0; v0 < 2; v0++) {
        Sprite_Delete(param0->arrows[v0]);
    }
}

static void WiFiNoteGraphics_SetArrowsVisible(WiFiNoteGraphics *param0, BOOL param1)
{
    int v0;

    for (v0 = 0; v0 < 2; v0++) {
        Sprite_SetDrawFlag(param0->arrows[v0], param1);
    }
}

static void WiFiNoteGraphics_SetArrowsAnimating(WiFiNoteGraphics *param0, BOOL param1)
{
    int v0;

    for (v0 = 0; v0 < 2; v0++) {
        Sprite_SetAnimateFlag(param0->arrows[v0], param1);
    }
}

static void WiFiNoteFriendCodeEntry_Init(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    WiFiNoteFriendCodeEntry_CreateWindows(param0, param1, param2, heapID);
}

static int WiFiNoteFriendCodeEntry_Main(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    BOOL v0;

    switch (param1->subState) {
    case 0:
        WiFiNoteFriendCodeEntry_Draw(param0, param1, param2);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_IN, FADE_TYPE_CIRCLE_IN, COLOR_BLACK, 6, 1, heapID);
        param1->subState = 1;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            param1->subState = 3;
        }
        break;
    case 2:
        WiFiNoteFriendCodeEntry_Draw(param0, param1, param2);
        param1->subState = 3;
        break;
    case 3:
        v0 = WiFiNoteFriendCodeEntry_HandleInput(param0, param1, param2);

        if (v0 == 1) {
            if (WiFiNoteFriendCodeEntry_CanAddFriend(param0, param1) == 1) {
                WiFiNoteFriendCodeEntry_SetNextPage(param0, param1);

                if ((param0->selection == 3) || (param0->selection == 1)) {
                    param1->subState = 4;
                } else {
                    WiFiNoteFriendCodeEntry_ClearScreen(param0, param2);
                    return 1;
                }
            } else {
                if (param0->selection == 1) {
                    WiFiNoteFriendCodeEntry_ShowMessage(param0, param2, 53, heapID);
                    param1->subState = 10;
                }
            }
        }
        break;
    case 4:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_OUT, FADE_TYPE_CIRCLE_OUT, COLOR_BLACK, 6, 1, heapID);
        param1->subState++;
        break;
    case 5:
        if (IsScreenFadeDone() == TRUE) {
            return 1;
        }
        break;
    case 6:
        WiFiNoteFriendCodeEntry_Draw(param0, param1, param2);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_IN, FADE_TYPE_CIRCLE_IN, COLOR_BLACK, 6, 1, heapID);
        param1->subState = 7;
        break;
    case 7:
        if (IsScreenFadeDone()) {
            u64 v1;
            TrainerInfo *v2;

            v2 = TrainerInfo_New(heapID);

            TrainerInfo_SetName(v2, String_GetData(param1->strings.name));
            StringTemplate_SetPlayerName(param2->stringTemplate, 0, v2);
            Heap_Free(v2);

            v1 = String_AtoI(param1->strings.friendCode, &v0);

            if (v0) {
                WiFiNoteGraphics_FormatFriendCode(param2, v1);
                WiFiNoteFriendCodeEntry_ShowMessage(param0, param2, 49, heapID);
                param1->subState = 8;
            } else {
                WiFiNoteFriendCodeEntry_ShowMessage(param0, param2, 50, heapID);
                param1->subState = 10;
            }
        }
        break;
    case 8:
        if (WiFiNoteFriendCodeEntry_IsMessageDone(param0) == 0) {
            break;
        }

        param0->yesNoMenu = Menu_MakeYesNoChoice(param2->bgConfig, &sYesNoWindowTemplate, 1, 9, heapID);
        param1->subState = 9;
        break;
    case 9: {
        int v3;
        u32 v4;
        static const u8 v5[3] = {
            0,
            50,
            54,
        };

        v3 = Menu_ProcessInputAndHandleExit(param0->yesNoMenu, heapID);

        switch (v3) {
        case 0xffffffff:
            break;
        case 0xfffffffe:
            WiFiNoteFriendCodeEntry_EraseMessageBox(param0);
            param1->subState = 3;
            break;
        default:
            v4 = WiFiNoteState_RegisterFriend(param1, param1->strings.friendCode, param1->strings.name);

            if (v4 == 0) {
                WiFiNoteFriendCodeEntry_EraseMessageBox(param0);
                param1->subState = 3;
            } else {
                WiFiNoteFriendCodeEntry_ShowMessage(param0, param2, v5[v4], heapID);
                param1->subState = 10;
            }
            break;
        }
    } break;
    case 10:
        if (WiFiNoteFriendCodeEntry_IsMessageDone(param0) == 0) {
            break;
        }

        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            WiFiNoteFriendCodeEntry_EraseMessageBox(param0);
            param1->subState = 3;
        }

        break;
    }

    return 0;
}

static void WiFiNoteFriendCodeEntry_Free(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    WiFiNoteFriendCodeEntry_DestroyWindows(param0, param1, param2);
}

static void WiFiNoteFriendCodeEntry_CreateWindows(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    static const u8 entryIDs[4] = {
        0x1,
        0x2,
        0x3,
        0x4
    };

    static const int xOffsets[4] = {
        0xFFFFFFFFFFFFFFFC,
        0xFFFFFFFFFFFFFFFC,
        0xFFFFFFFFFFFFFFFC,
        0x0
    };

    static const u8 yOffsets[4] = {
        0x8,
        0x30,
        0x58,
        0x80
    };

    Window_Init(&param0->window);
    Window_Add(param2->bgConfig, &param0->window, BG_LAYER_MAIN_3, 3, 4, 26, 20, 7, 1);

    Window_Init(&param0->messageWindow);
    Window_Add(param2->bgConfig, &param0->messageWindow, BG_LAYER_MAIN_1, 2, 19, 27, 4, 7, 112);

    Window_FillTilemap(&param0->window, 0);
    Window_FillTilemap(&param0->messageWindow, 0);

    param0->string = String_Init(128, heapID);
    param0->textFrameDelay = Options_TextFrameDelay(SaveData_GetOptions(param1->saveData));

    String *string = String_Init(128, heapID);
    String *fmtString = String_Init(128, heapID);

    StringTemplate_SetPlayerName(param2->stringTemplate, 0, SaveData_GetTrainerInfo(param1->saveData));

    int i;
    for (i = 0; i < 4; i++) {
        MessageLoader_GetString(param2->messageLoader, entryIDs[i], fmtString);
        StringTemplate_Format(param2->stringTemplate, string, fmtString);
        u32 xOffset = xOffsets[i] + Font_CalcCenterAlignment(FONT_SYSTEM, string, 0, 208);
        Text_AddPrinterWithParamsAndColor(&param0->window, FONT_SYSTEM, string, xOffset, yOffsets[i], TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    }

    String_Free(string);
    String_Free(fmtString);

    param0->screenDataRaw = Graphics_GetScrnDataFromOpenNARC(param2->narc, 1, 0, &param0->screenData, heapID);
}

static void WiFiNoteFriendCodeEntry_DestroyWindows(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    String_Free(param0->string);
    Window_Remove(&param0->window);
    Window_Remove(&param0->messageWindow);
    Heap_Free(param0->screenDataRaw);
}

static void WiFiNoteFriendCodeEntry_Draw(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    WiFiNoteGraphics_PrintMessage(param2, 0);

    Window_ScheduleCopyToVRAM(&param0->window);
    Bg_LoadToTilemapRect(param2->bgConfig, sBgLayers[2], param0->screenData->rawData, 0, 0, param0->screenData->screenWidth / 8, param0->screenData->screenHeight / 8);
    Bg_ScheduleScroll(param2->bgConfig, sBgLayers[2], 0, 0);
    Bg_ScheduleScroll(param2->bgConfig, sBgLayers[2], 3, 0);

    WiFiNoteFriendCodeEntry_HighlightSelection(param0, param2);
    Bg_ScheduleTilemapTransfer(param2->bgConfig, sBgLayers[2]);
}

static BOOL WiFiNoteFriendCodeEntry_HandleInput(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    BOOL v0 = 0;

    if (gSystem.pressedKeys & PAD_BUTTON_A) {
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        return 1;
    }

    if (gSystem.pressedKeys & PAD_BUTTON_B) {
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        param0->selection = 3;
        return 1;
    }

    if (gSystem.pressedKeysRepeatable & PAD_KEY_UP) {
        if (param0->selection > 0) {
            param0->selection--;
            v0 = 1;
        }
    } else if (gSystem.pressedKeysRepeatable & PAD_KEY_DOWN) {
        if (param0->selection < 3) {
            param0->selection++;
            v0 = 1;
        }
    }

    if (v0 == 1) {
        Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);
        WiFiNoteFriendCodeEntry_HighlightSelection(param0, param2);
        Bg_ScheduleTilemapTransfer(param2->bgConfig, sBgLayers[2]);
    }

    return 0;
}

static void WiFiNoteFriendCodeEntry_HighlightSelection(WiFiNoteFriendCodeEntry *param0, WiFiNoteGraphics *param1)
{
    int v0;
    static const u8 sCursorTilePositions[4][2] = {
        { 0x2, 0x4 },
        { 0x2, 0x9 },
        { 0x2, 0xE },
        { 0x2, 0x13 }
    };
    u8 v2;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->selection == v0) {
            v2 = 1;
        } else {
            v2 = 0;
        }

        Bg_ChangeTilemapRectPalette(param1->bgConfig, sBgLayers[2], sCursorTilePositions[v0][0], sCursorTilePositions[v0][1], 28, 4, v2);
    }
}

static void WiFiNoteFriendCodeEntry_SetNextPage(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1)
{
    static const u8 v0[4] = {
        1, 2, 3, 5
    };

    WiFiNoteState_SetPage(param1, v0[param0->selection], 0);
}

static void WiFiNoteFriendCodeEntry_ClearScreen(WiFiNoteFriendCodeEntry *param0, WiFiNoteGraphics *param1)
{
    WiFiNoteGraphics_ClearMessageBox(param1);

    Bg_FillTilemapRect(param1->bgConfig, sBgLayers[2], 0, 0, 0, 32, 24, 0);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[2]);
    Bg_FillTilemapRect(param1->bgConfig, sBgLayers[3], 0, 0, 0, 32, 24, 0);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[3]);

    Window_ClearAndScheduleCopyToVRAM(&param0->window);
}

static void WiFiNoteFriendCodeEntry_ShowMessage(WiFiNoteFriendCodeEntry *param0, WiFiNoteGraphics *param1, u32 param2, enum HeapID heapID)
{
    String *v0 = String_Init(128, heapID);

    Window_FillTilemap(&param0->messageWindow, 15);
    MessageLoader_GetString(param1->messageLoader, param2, v0);
    StringTemplate_Format(param1->stringTemplate, param0->string, v0);

    param0->printer = Text_AddPrinterWithParamsAndColor(&param0->messageWindow, FONT_MESSAGE, param0->string, 0, 0, param0->textFrameDelay, TEXT_COLOR(1, 2, 0), NULL);

    Window_DrawMessageBoxWithScrollCursor(&param0->messageWindow, 1, 1 + 9, 8);
    Window_ScheduleCopyToVRAM(&param0->messageWindow);
    String_Free(v0);
}

static BOOL WiFiNoteFriendCodeEntry_IsMessageDone(const WiFiNoteFriendCodeEntry *param0)
{
    if (Text_IsPrinterActive(param0->printer) == 0) {
        return 1;
    }

    return 0;
}

static void WiFiNoteFriendCodeEntry_EraseMessageBox(WiFiNoteFriendCodeEntry *param0)
{
    Window_EraseMessageBox(&param0->messageWindow, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->messageWindow);
}

static BOOL WiFiNoteFriendCodeEntry_CanAddFriend(WiFiNoteFriendCodeEntry *param0, WiFiNoteState *param1)
{
    int v0;
    WiFiList *v1;

    if (param0->selection == 1) {
        v1 = SaveData_GetWiFiList(param1->saveData);

        for (v0 = 0; v0 < 32; v0++) {
            if (!WiFiList_IsValidFriendData(v1, v0)) {
                return 1;
            }
        }
    } else {
        return 1;
    }

    return 0;
}

static void WiFiNoteFriendList_Init(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    param0->textFrameDelay = Options_TextFrameDelay(SaveData_GetOptions(param1->saveData));
    WiFiNoteFriendList_CreateWindows(param0, param1, param2, heapID);
}

static int WiFiNoteFriendList_Main(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    u32 v0;
    WiFiList *v1;
    u32 v2;

    switch (param1->subState) {
    case 0:
        param0->page = 0;
        param0->prevPage = 0;
        param0->slot = 0;
        param0->prevSlot = 0;
    case 1:
        WiFiNoteState_BuildFriendIndexList(param1);
        WiFiNoteFriendList_Draw(param0, param1, param2, heapID);
        param1->subState = 2;
        break;
    case 2:
        v0 = WiFiNoteFriendList_HandleInput(param0, param1, param2);

        switch (v0) {
        case 0:
            break;
        case 1:
            param0->prevPage = param0->page;
            param0->page--;

            if (param0->page < 0) {
                param0->page += 4;
            }

            WiFiNoteFriendList_BeginTransition(param0, param1, 2);
            break;
        case 2:
            param0->prevPage = param0->page;
            param0->page = (param0->page + 1) % 4;
            WiFiNoteFriendList_BeginTransition(param0, param1, 3);
            break;
        case 3:
            param1->subState = 23;
            break;
        case 4:
            param1->subState = 5;
            break;
        }
        break;
    case 3:
        WiFiNoteFriendList_StartTransition(param0, param1, param2, heapID);
        param1->subState = 4;
        break;
    case 4:
        v0 = WiFiNoteFriendList_UpdateTransition(param0, param1, param2, heapID);

        if (v0 == 1) {
            param1->subState = 2;
        }
        break;
    case 5:
        WiFiNoteState_SetSelectedFriend(param1, WiFiNoteFriendList_GetSelectedFriend(param0));
        WiFiNoteFriendList_OpenActionMenu(param0, param1, param2, heapID);
        param1->subState = 6;
        break;
    case 6:
        param1->subState = WiFiNoteFriendList_ProcessActionMenu(param0, param1, param2, heapID);
        break;
    case 7:
        param0->deleteTimer = 4;
        param1->subState = 8;
        break;
    case 8:
        param0->deleteTimer--;

        if (param0->deleteTimer <= 0) {
            WiFiNoteFriendList_Clear(param0, param1, param2);
            WiFiNoteState_SetPage(param1, 4, 0);
            return 1;
        }
        break;
    case 9:
        param0->page = param1->selectedFriend / 8;
        param0->slot = param1->selectedFriend % 8;
        param1->subState = 1;
        break;
    case 10:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_OUT, FADE_TYPE_CIRCLE_OUT, COLOR_BLACK, 6, 1, heapID);

        v2 = WiFiNoteFriendList_GetSelectedFriend(param0);
        v1 = SaveData_GetWiFiList(param1->saveData);

        WiFiNoteState_SetPendingName(param1, WiFiList_GetFriendPlayerName(v1, param1->friendIndexList.indices[v2]));
        param1->subState = 11;
        break;
    case 11:
        if (IsScreenFadeDone()) {
            WiFiNoteFriendList_Clear(param0, param1, param2);
            WiFiNoteState_SetPage(param1, 2, 4);
            return 1;
        }
        break;
    case 12:
        v2 = WiFiNoteFriendList_GetSelectedFriend(param0);
        v1 = SaveData_GetWiFiList(param1->saveData);
        WiFiList_SetFriendPlayerName(v1, param1->friendIndexList.indices[v2], param1->strings.name);
    case 13:
        WiFiNoteFriendList_Draw(param0, param1, param2, heapID);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_IN, FADE_TYPE_CIRCLE_IN, COLOR_BLACK, 6, 1, heapID);
        param1->subState = 14;
        break;
    case 14:
        if (IsScreenFadeDone()) {
            param1->subState = 2;
        }
        break;
    case 15:
        WiFiNoteFriendList_ConfirmDelete(param0, param1, param2, heapID);
        param1->subState = 16;
        break;
    case 16:
        v0 = WiFiNoteFriendList_CreateDeleteConfirmMenu(param0, param1, param2, heapID);

        if (v0 == 1) {
            param1->subState = 17;
        }
        break;
    case 17:
        v0 = Menu_ProcessInputAndHandleExit(param0->yesNoMenu, heapID);

        switch (v0) {
        case 0xffffffff:
            break;
        case 0xfffffffe:
            WiFiNoteFriendList_EraseMessageBox(param0);
            WiFiNoteGraphics_SetArrowsVisible(param2, 1);
            param1->subState = 2;
            break;
        default:
            WiFiNoteFriendList_EraseMessageBox(param0);
            param1->subState = 18;
            break;
        }
        break;
    case 18:
        WiFiNoteFriendList_StartDeleteAnimation(param0);
        param1->subState = 19;
        break;
    case 19:
        if (WiFiNoteFriendList_UpdateDeleteAnimation(param0) == 1) {
            v1 = SaveData_GetWiFiList(param1->saveData);
            v2 = WiFiNoteFriendList_GetSelectedFriend(param0);

            WiFiList_DeleteFriend(v1, param1->friendIndexList.indices[v2]);
            BattleFrontierSave_ClearFriendStatsAndShift(SaveData_GetBattleFrontier(param1->saveData), param1->friendIndexList.indices[v2]);
            WiFiNoteState_BuildFriendIndexList(param1);
            WiFiNoteFriendList_DrawFriendSlot(param0, param1, param2, param0->page, param0->slot, 0, heapID);
            WiFiNoteGraphics_SetArrowsVisible(param2, 1);
            param1->subState = 20;
        }
        break;
    case 20:
        WiFiNoteFriendList_EndDeleteAnimation(param0);
        param1->subState = 2;
        break;
    case 21:
        v0 = WiFiNoteFriendList_ShowFriendCode(param0, param1, param2, heapID);

        if (v0 == 1) {
            param1->subState = 22;
        } else {
            WiFiNoteGraphics_SetArrowsVisible(param2, 1);
            param1->subState = 2;
        }
        break;
    case 22:
        if (WiFiNoteFriendList_IsMessageDone(param0) == 0) {
            break;
        }

        if (gSystem.pressedKeys) {
            WiFiNoteGraphics_SetArrowsVisible(param2, 1);
            param1->subState = 2;
            WiFiNoteFriendList_EraseMessageBox(param0);
        }
        break;
    case 23:
        WiFiNoteFriendList_Clear(param0, param1, param2);
        WiFiNoteState_SetPage(param1, 0, 2);
        return 1;
    }

    return 0;
}

static void WiFiNoteFriendList_Free(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    WiFiNoteFriendList_DestroyWindows(param0, param1, param2);
}

static void WiFiNoteFriendList_CreateWindows(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    static const u16 sSlotBgBaseTiles[3] = {
        0x1,
        0x1BB,
        0x1BB
    };

    AffineSpriteListTemplate spriteTemplate = {
        NULL,
        NULL,
        { 0x0, 0x0, 0x0 },
        { FX32_ONE, FX32_ONE, FX32_ONE },
        0x0,
        0x0,
        NNS_G2D_VRAM_TYPE_2DMAIN,
        0x0
    };

    int i, j;

    for (i = 0; i < 3; i++) {
        WiFiNoteFriendSlot_Init(&param0->slots[i], param2, &sPageOffsets[i], sSlotBgBaseTiles[i], heapID);
    }

    param0->spriteManager = ov63_0222AE60(param2->spriteList, NULL, 16, heapID);
    ov63_0222B02C(param0->spriteManager, 1, 2, heapID);

    Window_Init(&param0->headerWindow);
    Window_Add(param2->bgConfig, &param0->headerWindow, BG_LAYER_MAIN_1, 13, 21, 8, 3, 7, 112);
    Window_FillTilemap(&param0->headerWindow, 0);

    String *string = String_Init(128, heapID);
    MessageLoader_GetString(param2->messageLoader, 7, string);
    Text_AddPrinterWithParamsAndColor(&param0->headerWindow, FONT_SYSTEM, string, Font_CalcCenterAlignment(FONT_SYSTEM, string, 0, 64), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    String_Free(string);

    Window_Init(&param0->menuWindow);
    Window_Add(param2->bgConfig, &param0->menuWindow, BG_LAYER_MAIN_1, 16, 9, 15, 8, 7, 136);
    Window_FillTilemap(&param0->menuWindow, 0);

    for (i = 0; i < 2; i++) {
        param0->menuChoices[i] = StringList_New(4, heapID);
        for (j = 0; j < 4; j++) {
            StringList_AddFromMessageBank(param0->menuChoices[i], param2->messageLoader, sActionMenuEntries[i][j].entryID, sActionMenuEntries[i][j].index);
        }
    }

    Window_Init(&param0->messageWindow);
    Window_Add(param2->bgConfig, &param0->messageWindow, BG_LAYER_MAIN_1, 2, 19, 27, 4, 7, 256);
    Window_FillTilemap(&param0->messageWindow, 15);

    param0->string = String_Init(128, heapID);

    spriteTemplate.list = param2->spriteList;
    spriteTemplate.resourceData = &param2->spriteResourcesHeader;
    spriteTemplate.heapID = heapID;
    param0->deleteSprite = SpriteList_AddAffine(&spriteTemplate);
    Sprite_SetDrawFlag(param0->deleteSprite, FALSE);
}

static void WiFiNoteFriendList_DestroyWindows(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    int v0;

    Sprite_Delete(param0->deleteSprite);
    Window_Remove(&param0->messageWindow);
    String_Free(param0->string);

    for (v0 = 0; v0 < 2; v0++) {
        StringList_Free(param0->menuChoices[v0]);
    }

    Window_Remove(&param0->menuWindow);
    Window_Remove(&param0->headerWindow);

    ov63_0222B078(param0->spriteManager);
    ov63_0222AF14(param0->spriteManager);

    for (v0 = 0; v0 < 3; v0++) {
        WiFiNoteFriendSlot_Free(&param0->slots[v0], param2);
    }
}

static void WiFiNoteFriendList_Draw(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    int v0;

    WiFiNoteGraphics_PrintMessage(param2, 5);

    Bg_CopyToTilemapRect(param2->bgConfig, sBgLayers[0], 11, 20, 10, 4, param2->screenData.data[1]->rawData, 6, 0, param2->screenData.data[1]->screenWidth / 8, param2->screenData.data[1]->screenHeight / 8);
    Window_ScheduleCopyToVRAM(&param0->headerWindow);

    Bg_ScheduleTilemapTransfer(param2->bgConfig, sBgLayers[0]);

    WiFiNoteGraphics_SetArrowsVisible(param2, 1);
    WiFiNoteFriendList_DrawFriendSlot(param0, param1, param2, param0->page, param0->slot, 0, heapID);
}

static void WiFiNoteFriendList_Clear(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    int v0;

    WiFiNoteGraphics_ClearMessageBox(param2);
    Window_ClearAndScheduleCopyToVRAM(&param0->headerWindow);

    for (v0 = 0; v0 < 3; v0++) {
        WiFiNoteFriendSlot_Clear(&param0->slots[v0], param2, &param2->screenData);
    }

    WiFiNoteGraphics_SetArrowsVisible(param2, 0);

    Bg_CopyToTilemapRect(param2->bgConfig, sBgLayers[0], 11, 20, 10, 4, param2->screenData.data[1]->rawData, 0, 8, param2->screenData.data[1]->screenWidth / 8, param2->screenData.data[1]->screenHeight / 8);
    Bg_CopyToTilemapRect(param2->bgConfig, sBgLayers[0], 0x16, 0, 9, 3, param2->screenData.data[1]->rawData, 0x10, 0x0, param2->screenData.data[1]->screenWidth / 8, param2->screenData.data[1]->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param2->bgConfig, sBgLayers[0]);
}

static u32 WiFiNoteFriendList_HandleInput(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    u16 v0;
    BOOL v1;
    BOOL v2;
    int v3;

    if (gSystem.pressedKeys & PAD_BUTTON_A) {
        if (param0->slot == 8) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
            return 3;
        }

        if (param1->friendIndexList.count <= param0->slot + (param0->page * 8)) {
            return 0;
        }

        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        return 4;
    }

    if (gSystem.pressedKeys & PAD_BUTTON_B) {
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        return 3;
    }

    v0 = param0->slot;
    v1 = 0;
    v2 = 0;

    if (gSystem.pressedKeysRepeatable & PAD_KEY_UP) {
        if (param0->slot == 8) {
            param0->slot = param0->prevSlot;
            v1 = 1;
            WiFiNoteGraphics_SetArrowsVisible(param2, 1);
        } else {
            if (param0->slot < (8 / 2)) {
                if (param0->slot > 0) {
                    param0->slot--;
                    v1 = 1;
                }
            } else {
                if (param0->slot > (8 / 2)) {
                    param0->slot--;
                    v1 = 1;
                }
            }
        }
    } else if (gSystem.pressedKeysRepeatable & PAD_KEY_DOWN) {
        if ((param0->slot == 3) || (param0->slot == 7)) {
            param0->slot = 8;
            v1 = 1;

            WiFiNoteGraphics_SetArrowsVisible(param2, 0);
        } else {
            if (param0->slot < (8 / 2)) {
                if (param0->slot < 3) {
                    param0->slot++;
                    v1 = 1;
                }
            } else {
                if (param0->slot < 7) {
                    param0->slot++;
                    v1 = 1;
                }
            }
        }
    } else if (gSystem.pressedKeysRepeatable & PAD_KEY_LEFT) {
        if (param0->slot != 8) {
            if (param0->slot < (8 / 2)) {
                param0->slot += (8 / 2);
                v1 = 1;
                v2 = 1;
                v3 = 2;
            } else {
                param0->slot -= (8 / 2);
                v1 = 1;
            }
        }
    } else if (gSystem.pressedKeysRepeatable & PAD_KEY_RIGHT) {
        if (param0->slot != 8) {
            if (param0->slot < (8 / 2)) {
                param0->slot += (8 / 2);
                v1 = 1;
            } else {
                param0->slot -= (8 / 2);
                v1 = 1;
                v2 = 1;
                v3 = 3;
            }
        }
    }

    if (v2 == 1) {
        if (v3 == 2) {
            return 1;
        }

        return 2;
    } else {
        if (v1 == 1) {
            Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);

            WiFiNoteFriendSlot_Highlight(&param0->slots[0], param2, param0->slot);
            param0->prevSlot = v0;
        }
    }

    return 0;
}

static void WiFiNoteFriendList_StartTransition(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    u16 v0;

    if (param0->transitionDir == 2) {
        v0 = 2;
    } else {
        v0 = 1;
    }

    WiFiNoteFriendList_DrawFriendSlot(param0, param1, param2, param0->page, param0->slot, v0, heapID);
    WiFiNoteFriendSlot_Highlight(&param0->slots[0], param2, 10);
    WiFiNoteGraphics_SetArrowsAnimating(param2, 0);

    Sound_PlayEffect(SEQ_SE_DP_SELECT5_sseq);
}

static BOOL WiFiNoteFriendList_UpdateTransition(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    u32 v0;
    s32 v1;
    NNSG2dViewRect v2;
    u32 v3;
    static void (*v4[4])(WiFiNoteFriendList *, WiFiNoteGraphics *, u32, u32) = {
        WiFiNoteFriendList_DrawCursorLeft, NULL, WiFiNoteFriendList_DrawCursorRight, NULL
    };

    if (param0->transitionTimer >= 12) {
        Bg_ScheduleScroll(param2->bgConfig, sBgLayers[2], 0, 0);
        Bg_ScheduleScroll(param2->bgConfig, sBgLayers[3], 0, 0);

        v2 = sViewRect;
        SetRenderSurfaceViewRect(&param2->renderSurface, &v2);

        if (param0->transitionDir == 2) {
            v0 = 2;
        } else {
            v0 = 1;
        }

        WiFiNoteFriendSlot_Clear(&param0->slots[v0], param2, &param2->screenData);
        WiFiNoteFriendList_DrawFriendSlot(param0, param1, param2, param0->page, param0->slot, 0, heapID);
        WiFiNoteGraphics_SetArrowsAnimating(param2, 1);
        return 1;
    }

    v1 = (param0->transitionTimer * 256) / 12;

    if (param0->transitionDir == 2) {
        v1 = -v1;
    }

    Bg_ScheduleScroll(param2->bgConfig, sBgLayers[2], 0, v1);
    Bg_ScheduleScroll(param2->bgConfig, sBgLayers[3], 0, v1);

    v2 = sViewRect;
    v2.posTopLeft.x += v1 << FX32_SHIFT;

    SetRenderSurfaceViewRect(&param2->renderSurface, &v2);

    if (param0->transitionTimer % (12 / 4)) {
        v3 = param0->transitionTimer / (12 / 4);

        if (v4[v3]) {
            v4[v3](param0, param2, param0->page, param0->prevPage);
        }
    }

    param0->transitionTimer++;
    return 0;
}

static void WiFiNoteFriendList_OpenActionMenu(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    ListMenuTemplate v0;
    WiFiList *v1;
    u32 v2;
    u32 v3;

    v1 = SaveData_GetWiFiList(param1->saveData);
    v3 = WiFiNoteFriendList_GetSelectedFriend(param0);
    v2 = WiFiList_GetFriendField(v1, param1->friendIndexList.indices[v3], 8);
    v0 = sActionMenuTemplate;

    if (v2 == 2) {
        v0.choices = param0->menuChoices[1];
    } else {
        v0.choices = param0->menuChoices[0];
    }

    v0.window = &param0->menuWindow;
    param0->listMenu = ListMenu_New(&v0, 0, 0, heapID);

    Window_DrawStandardFrame(&param0->menuWindow, 1, 1, 9);
    Window_ScheduleCopyToVRAM(&param0->menuWindow);

    WiFiNoteGraphics_SetFriendName(param2, param1->saveData, param1->friendIndexList.indices[v3], heapID);
    WiFiNoteFriendList_ShowMessage(param0, param2, 12, heapID);
    WiFiNoteGraphics_SetArrowsVisible(param2, 0);
}

static u32 WiFiNoteFriendList_ProcessActionMenu(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    u32 v0;
    u32 v1 = 6;

    if (WiFiNoteFriendList_IsMessageDone(param0) == 0) {
        return v1;
    }

    v0 = ListMenu_ProcessInput(param0->listMenu);

    switch (v0) {
    case 0xffffffff:
        return v1;
    case 0xfffffffe:
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
        WiFiNoteGraphics_SetArrowsVisible(param2, 1);
        v1 = 2;
        break;
    default:
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
        v1 = v0;
        break;
    }

    WiFiNoteFriendList_EraseMessageBox(param0);

    Window_EraseStandardFrame(&param0->menuWindow, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->menuWindow);
    ListMenu_Free(param0->listMenu, NULL, NULL);

    if (v1 == 2) {
        WiFiNoteGraphics_SetArrowsVisible(param2, 1);
    }

    return v1;
}

static BOOL WiFiNoteFriendList_ShowFriendCode(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    WiFiList *v0;
    DWCFriendData *v1;
    u64 v2;
    u32 v3;

    v0 = SaveData_GetWiFiList(param1->saveData);
    v3 = WiFiNoteFriendList_GetSelectedFriend(param0);
    v1 = WiFiList_GetFriendData(v0, param1->friendIndexList.indices[v3]);
    v2 = DWC_GetFriendKey(v1);

    if (v2 != 0) {
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        WiFiNoteGraphics_FormatFriendCode(param2, v2);
        WiFiNoteGraphics_SetFriendName(param2, param1->saveData, param1->friendIndexList.indices[v3], heapID);
        WiFiNoteFriendList_ShowMessage(param0, param2, 55, heapID);
        return 1;
    }

    return 0;
}

static void WiFiNoteFriendList_ConfirmDelete(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    u32 v0 = WiFiNoteFriendList_GetSelectedFriend(param0);

    WiFiNoteGraphics_SetFriendName(param2, param1->saveData, param1->friendIndexList.indices[v0], heapID);
    WiFiNoteFriendList_ShowMessage(param0, param2, 52, heapID);
}

static BOOL WiFiNoteFriendList_CreateDeleteConfirmMenu(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    if (WiFiNoteFriendList_IsMessageDone(param0) == 0) {
        return 0;
    }

    param0->yesNoMenu = Menu_MakeYesNoChoice(param2->bgConfig, &sYesNoWindowTemplate, 1, 9, heapID);
    return 1;
}

static void WiFiNoteFriendList_DrawFriendSlot(WiFiNoteFriendList *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, u32 param3, u32 param4, u32 param5, enum HeapID heapID)
{
    if (0 == param5) {
        param0->page = param3;
        param0->slot = param4;

        WiFiNoteFriendList_DrawSelectionCursor(param0, param2, param3);
    }

    WiFiNoteFriendSlot_DrawBackground(&param0->slots[param5], param2, &param2->screenData);
    WiFiNoteFriendSlot_DrawEntries(&param0->slots[param5], param1, param2, param0->spriteManager, &param2->screenData, &param1->friendIndexList, param3, heapID);
    WiFiNoteFriendSlot_Highlight(&param0->slots[param5], param2, param4);
}

static void WiFiNoteFriendList_DrawSelectionCursor(WiFiNoteFriendList *param0, WiFiNoteGraphics *param1, u32 param2)
{
    u32 v0;

    Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], 0x16, 0, 9, 3, param1->screenData.data[1]->rawData, 0, 4, param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);

    v0 = 0x16 + (2 * param2) + 1;

    Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], v0, 0 + 1, 1, 1, param1->screenData.data[1]->rawData, 3, sCursorTileOffsets[param2], param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[0]);
}

static void WiFiNoteFriendList_DrawCursorLeft(WiFiNoteFriendList *param0, WiFiNoteGraphics *param1, u32 param2, u32 param3)
{
    u32 v0 = 0x16 + (2 * param3) + 1;

    Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], v0, 0 + 1, 1, 1, param1->screenData.data[1]->rawData, 4, sCursorTileOffsets[param3], param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[0]);
}

static void WiFiNoteFriendList_DrawCursorRight(WiFiNoteFriendList *param0, WiFiNoteGraphics *param1, u32 param2, u32 param3)
{
    u32 v0;

    Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], 0x16, 0, 9, 3, param1->screenData.data[1]->rawData, 0, 4, param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);

    v0 = 0x16 + (2 * param2) + 1;

    Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], v0, 0 + 1, 1, 1, param1->screenData.data[1]->rawData, 3, sCursorTileOffsets[param2], param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[0]);
}

static void WiFiNoteFriendList_BeginTransition(WiFiNoteFriendList *param0, WiFiNoteState *param1, int param2)
{
    param1->subState = 3;
    param0->transitionDir = param2;
    param0->transitionTimer = 0;
}

static void WiFiNoteFriendList_ShowMessage(WiFiNoteFriendList *param0, WiFiNoteGraphics *param1, u32 param2, enum HeapID heapID)
{
    String *v0;

    Window_FillTilemap(&param0->messageWindow, 15);

    v0 = String_Init(128, heapID);

    MessageLoader_GetString(param1->messageLoader, param2, v0);
    StringTemplate_Format(param1->stringTemplate, param0->string, v0);

    param0->printer = Text_AddPrinterWithParamsAndColor(&param0->messageWindow, FONT_MESSAGE, param0->string, 0, 0, param0->textFrameDelay, TEXT_COLOR(1, 2, 0), NULL);

    Window_DrawMessageBoxWithScrollCursor(&param0->messageWindow, 1, 1 + 9, 8);
    Window_ScheduleCopyToVRAM(&param0->messageWindow);
    String_Free(v0);
}

static BOOL WiFiNoteFriendList_IsMessageDone(const WiFiNoteFriendList *param0)
{
    if (Text_IsPrinterActive(param0->printer) == 0) {
        return 1;
    }

    return 0;
}

static void WiFiNoteFriendList_EraseMessageBox(WiFiNoteFriendList *param0)
{
    Window_EraseMessageBox(&param0->messageWindow, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->messageWindow);
    Window_ScheduleCopyToVRAM(&param0->headerWindow);
}

static u32 WiFiNoteFriendList_GetSelectedFriend(const WiFiNoteFriendList *param0)
{
    u32 v0 = param0->page * 8;
    v0 += param0->slot;

    return v0;
}

static void WiFiNoteFriendList_ListMenuCursorCallback(ListMenu *param0, u32 param1, u8 param2)
{
    if (param2 == 0) {
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
    }
}

static void WiFiNoteFriendList_StartDeleteAnimation(WiFiNoteFriendList *param0)
{
    VecFx32 v0;
    u32 v1;

    Sprite_SetDrawFlag(param0->deleteSprite, TRUE);
    Sprite_SetAnim(param0->deleteSprite, 2);

    param0->deleteAnimFrame = 0;

    Sprite_SetAnimateFlag(param0->deleteSprite, 1);

    v1 = param0->slot;

    v0.x = ((MATH_ABS(sPageOffsets[0].x) + sSlotRects[v1].rect.x) * 8);
    v0.y = ((MATH_ABS(sPageOffsets[0].y) + sSlotRects[v1].rect.y) * 8) + (-4 + 256);
    v0.x <<= FX32_SHIFT;
    v0.y <<= FX32_SHIFT;

    Sprite_SetPosition(param0->deleteSprite, &v0);

    G2_SetWndOBJInsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2, 0);
    G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
    GX_SetVisibleWnd(GX_WNDMASK_OW);

    Sound_PlayEffect(SEQ_SE_DP_UG_025_sseq);
}

static BOOL WiFiNoteFriendList_UpdateDeleteAnimation(WiFiNoteFriendList *param0)
{
    u32 v0;

    if (Sprite_IsAnimated(param0->deleteSprite) == 0) {
        return 1;
    }

    v0 = Sprite_GetAnimFrame(param0->deleteSprite);

    if ((v0 - param0->deleteAnimFrame) >= 2) {
        param0->deleteAnimFrame = v0;
        Sound_PlayEffect(SEQ_SE_DP_UG_025_sseq);
    }

    return 0;
}

static void WiFiNoteFriendList_EndDeleteAnimation(WiFiNoteFriendList *param0)
{
    GX_SetVisibleWnd(GX_WNDMASK_NONE);

    Sprite_SetDrawFlag(param0->deleteSprite, FALSE);
    Sprite_SetAnimateFlag(param0->deleteSprite, 0);
}

static void WiFiNoteFriendSlot_Init(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1, const WiFiNotePageOffset *param2, u32 param3, u32 param4)
{
    param0->offset = *param2;

    Window_Init(&param0->window);
    Window_Add(param1->bgConfig, &param0->window, sBgLayers[3], 4 + MATH_ABS(param2->x), 4 + MATH_ABS(param2->y), 26, 17, 7, param3);
}

static void WiFiNoteFriendSlot_Free(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1)
{
    Window_Remove(&param0->window);
}

static void WiFiNoteFriendSlot_DrawBackground(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1, const WiFiNoteScreenData *param2)
{
    Bg_LoadToTilemapRect(param1->bgConfig, sBgLayers[2], param2->data[0]->rawData, MATH_ABS(param0->offset.x), MATH_ABS(param0->offset.y), param2->data[0]->screenWidth / 8, param2->data[0]->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[2]);
}

static void WiFiNoteFriendSlot_Highlight(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1, u32 param2)
{
    int v0;
    int v1;

    for (v0 = 0; v0 < 9; v0++) {
        if (param2 == v0) {
            v1 = 6;
        } else {
            v1 = 0;
        }

        Bg_ChangeTilemapRectPalette(param1->bgConfig, sSlotRects[v0].bgLayer, MATH_ABS(param0->offset.x) + sSlotRects[v0].rect.x, MATH_ABS(param0->offset.y) + sSlotRects[v0].rect.y, sSlotRects[v0].rect.width, sSlotRects[v0].rect.height, v1);
    }

    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[2]);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[0]);
}

static void WiFiNoteFriendSlot_DrawEntries(WiFiNoteFriendSlot *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, UnkStruct_ov63_0222AE60 *param3, const WiFiNoteScreenData *param4, const WiFiNoteFriendIndexList *param5, u32 param6, enum HeapID heapID)
{
    int v0;
    int v1;
    WiFiList *v2;

    v2 = SaveData_GetWiFiList(param1->saveData);

    Window_FillTilemap(&param0->window, 0);
    WiFiNoteFriendSlot_DeleteSprites(param0, param2);

    v1 = param6 * 8;

    for (v0 = 0; v0 < 8; v0++) {
        if (param5->count > (v1 + v0)) {
            WiFiNoteFriendSlot_DrawFriend(param0, param3, param2, param4, v0, v2, param5->indices[v1 + v0], heapID);
        } else {
            WiFiNoteFriendSlot_DrawEmpty(param0, param2, param4, v0);
        }
    }

    Bg_ScheduleTilemapTransfer(param2->bgConfig, sBgLayers[2]);
    Window_ScheduleCopyToVRAM(&param0->window);
}

static void WiFiNoteFriendSlot_Clear(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1, const WiFiNoteScreenData *param2)
{
    WiFiNoteFriendSlot_DeleteSprites(param0, param1);

    Window_ClearAndScheduleCopyToVRAM(&param0->window);
    Bg_FillTilemapRect(param1->bgConfig, sBgLayers[2], 0, MATH_ABS(param0->offset.x), MATH_ABS(param0->offset.y), param0->offset.width, param0->offset.height, 0);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[2]);
    Bg_FillTilemapRect(param1->bgConfig, sBgLayers[3], 0, MATH_ABS(param0->offset.x), MATH_ABS(param0->offset.y), param0->offset.width, param0->offset.height, 0);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[3]);
}

static void WiFiNoteFriendSlot_DeleteSprites(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->sprites[v0]) {
            ov63_0222B210(param0->sprites[v0]);
            param0->sprites[v0] = NULL;
        }
    }
}

static void WiFiNoteFriendSlot_DrawFriend(WiFiNoteFriendSlot *param0, UnkStruct_ov63_0222AE60 *param1, WiFiNoteGraphics *param2, const WiFiNoteScreenData *param3, u32 param4, WiFiList *param5, u32 param6, enum HeapID heapID)
{
    int v0;
    int v1;
    WiFiNoteSpriteParams v2;
    String *v3;
    int v4, v5;
    static const u32 v6[] = { TEXT_COLOR(5, 6, 0), TEXT_COLOR(3, 4, 0), TEXT_COLOR(1, 2, 0) };

    v1 = WiFiList_GetFriendField(param5, param6, 7);
    v0 = WiFiList_GetFriendField(param5, param6, 8);

    if (v0 == 2) {
        WiFiNoteFriendSlot_DrawEmpty(param0, param2, param3, param4);
    } else {
        v2.x = ((param0->offset.x + sSlotRects[param4].rect.x) * 8) + 8;
        v2.y = ((param0->offset.y + sSlotRects[param4].rect.y) * 8) + (6 + 256);
        v2.priority = 8;
        v2.explicitPriority = 1;
        param0->sprites[param4] = ov63_0222B0C0(param1, &v2, v1, heapID);
    }

    v4 = ((sSlotRects[param4].rect.x) * 8) + 0;
    v5 = ((sSlotRects[param4].rect.y) * 8) + -24;
    v3 = String_Init(128, heapID);

    String_CopyChars(v3, WiFiList_GetFriendPlayerName(param5, param6));
    Text_AddPrinterWithParamsAndColor(&param0->window, FONT_SYSTEM, v3, v4, v5, TEXT_SPEED_NO_TRANSFER, v6[v0], NULL);
    String_Free(v3);
}

static void WiFiNoteFriendSlot_DrawEmpty(WiFiNoteFriendSlot *param0, WiFiNoteGraphics *param1, const WiFiNoteScreenData *param2, u32 param3)
{
    Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[2], MATH_ABS(param0->offset.x) + sSlotRects[param3].rect.x, MATH_ABS(param0->offset.y) + sSlotRects[param3].rect.y, 3, 4, param2->data[1]->rawData, 0, 0, param2->data[1]->screenWidth / 8, param2->data[1]->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[2]);
}

static void WiFiNoteNamingScreen_Init(WiFiNoteNamingScreen *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    WiFiNoteNamingScreen_Create(param0, param1, param2, heapID);
}

static int WiFiNoteNamingScreen_Main(WiFiNoteNamingScreen *param0, WiFiNote *param1, WiFiNoteState *param2, WiFiNoteGraphics *param3, enum HeapID heapID)
{
    int v0[4];

    switch (param2->subState) {
    case 0:
        param0->namingScreenArgs = WiFiNoteNamingScreen_MakeArgs(param0, param2, heapID);

        v0[0] = 4;
        v0[1] = 4;
        v0[2] = 4;
        v0[3] = 0;

        param0->numberEntryArgs = NumberEntryArgs_New(heapID, 12, v0, SaveData_GetOptions(param2->saveData), 0, 0);
        WiFiNote_FreeScreens(param1);
        param0->appMan = ApplicationManager_New(&gNamingScreenAppTemplate, param0->namingScreenArgs, heapID);
        param2->subState = 1;
        break;
    case 1:
        if (ApplicationManager_Exec(param0->appMan) == 0) {
            break;
        }

        ApplicationManager_Free(param0->appMan);

        if (param0->namingScreenArgs->returnCode == NAMING_SCREEN_CODE_OK) {
            param0->appMan = ApplicationManager_New(&gNumberEntryAppTemplate, param0->numberEntryArgs, heapID);
            param2->subState = 2;
        } else {
            WiFiNoteState_SetPage(param2, 0, 0);
            param2->subState = 3;
        }
        break;
    case 2:
        if (ApplicationManager_Exec(param0->appMan) == 0) {
            break;
        }

        ApplicationManager_Free(param0->appMan);
        WiFiNoteState_SetInputStrings(param2, param0->namingScreenArgs->textInputStr, param0->numberEntryArgs->numberString);
        WiFiNoteState_SetPage(param2, 0, 6);
        param2->subState = 3;
        break;
    case 3:
        NamingScreenArgs_Free(param0->namingScreenArgs);
        NumberEntryArgs_Free(param0->numberEntryArgs);
        WiFiNote_ReinitScreens(param1, heapID);
        return 1;
    case 4:
        param0->namingScreenArgs = WiFiNoteNamingScreen_MakeArgs(param0, param2, heapID);
        WiFiNote_FreeScreens(param1);
        param0->appMan = ApplicationManager_New(&gNamingScreenAppTemplate, param0->namingScreenArgs, heapID);
        param2->subState = 5;
        break;
    case 5:
        if (ApplicationManager_Exec(param0->appMan) == 0) {
            break;
        }

        ApplicationManager_Free(param0->appMan);

        if (param0->namingScreenArgs->returnCode == NAMING_SCREEN_CODE_OK) {
            WiFiNoteState_SetPage(param2, 1, 12);
            WiFiNoteState_SetInputStrings(param2, param0->namingScreenArgs->textInputStr, NULL);
            param2->subState = 6;
        } else {
            WiFiNoteState_SetPage(param2, 1, 13);
            param2->subState = 6;
        }
        break;
    case 6:
        NamingScreenArgs_Free(param0->namingScreenArgs);
        WiFiNote_ReinitScreens(param1, heapID);
        return 1;
    }

    return 0;
}

static void WiFiNoteNamingScreen_Free(WiFiNoteNamingScreen *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    WiFiNoteNamingScreen_Destroy(param0, param1, param2);
}

static void WiFiNoteNamingScreen_Create(WiFiNoteNamingScreen *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    return;
}

static void WiFiNoteNamingScreen_Destroy(WiFiNoteNamingScreen *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    return;
}

static NamingScreenArgs *WiFiNoteNamingScreen_MakeArgs(WiFiNoteNamingScreen *param0, WiFiNoteState *param1, enum HeapID heapID)
{
    NamingScreenArgs *v0;

    v0 = NamingScreenArgs_Init(heapID, NAMING_SCREEN_TYPE_PAL_PAD, 0, TRAINER_NAME_LEN, SaveData_GetOptions(param1->saveData));

    if (param1->nameInput.pending == 1) {
        {
            if (IsFullWidthChar(*param1->nameInput.text) == 0) {
                String_CopyChars(v0->textInputStr, param1->nameInput.text);
            } else {
                String_Clear(v0->textInputStr);
            }
        }

        param1->nameInput.pending = 0;
    }

    return v0;
}

static void WiFiNoteOwnCode_Init(WiFiNoteOwnCode *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    WiFiNoteOwnCode_CreateWindows(param0, param1, param2, heapID);
}

static int WiFiNoteOwnCode_Main(WiFiNoteOwnCode *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    switch (param1->subState) {
    case 0:
        WiFiNoteOwnCode_Draw(param0, param1, param2);
        param1->subState = 1;
        break;
    case 1:
        if (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B)) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
            WiFiNoteState_SetPage(param1, 0, 2);
            WiFiNoteOwnCode_Clear(param0, param2);
            return 1;
        }
        break;
    }

    return 0;
}

static void WiFiNoteOwnCode_Free(WiFiNoteOwnCode *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    WiFiNoteOwnCode_DestroyWindows(param0, param1, param2);
}

static void WiFiNoteOwnCode_CreateWindows(WiFiNoteOwnCode *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    Window_Init(&param0->window);
    Window_Add(param2->bgConfig, &param0->window, BG_LAYER_MAIN_3, 5, 13, 23, 8, 7, 1);

    Window_Init(&param0->codeWindow);
    Window_Add(param2->bgConfig, &param0->codeWindow, BG_LAYER_MAIN_3, 9, 8, 15, 2, 7, 185);

    Window_FillTilemap(&param0->window, 0);
    Window_FillTilemap(&param0->codeWindow, 0);

    String *string = String_Init(128, heapID);
    String *fmtString = String_Init(128, heapID);

    u64 friendCode = DWC_CreateFriendKey(WiFiList_GetUserData(SaveData_GetWiFiList(param1->saveData)));
    if (friendCode) {
        MessageLoader_GetString(param2->messageLoader, 47, string);
        u32 xOffset = (184 - Font_CalcMaxLineWidth(FONT_SYSTEM, string, 0)) / 2;
        Text_AddPrinterWithParamsAndColor(&param0->window, FONT_SYSTEM, string, xOffset, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

        WiFiNoteGraphics_FormatFriendCode(param2, friendCode);
        MessageLoader_GetString(param2->messageLoader, 51, fmtString);
        StringTemplate_Format(param2->stringTemplate, string, fmtString);
        Text_AddPrinterWithParamsAndColor(&param0->codeWindow, FONT_SYSTEM, string, Font_CalcCenterAlignment(FONT_SYSTEM, string, 0, 120), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    } else {
        MessageLoader_GetString(param2->messageLoader, 48, string);
        u32 xOffset = (184 - Font_CalcMaxLineWidth(FONT_SYSTEM, string, 0)) / 2;
        Text_AddPrinterWithParamsAndColor(&param0->window, FONT_SYSTEM, string, xOffset, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    }

    String_Free(string);
    String_Free(fmtString);

    param0->screenDataRaw = Graphics_GetScrnDataFromOpenNARC(param2->narc, 11, 0, &param0->screenData, heapID);
}

static void WiFiNoteOwnCode_DestroyWindows(WiFiNoteOwnCode *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    Window_Remove(&param0->window);
    Window_Remove(&param0->codeWindow);
    Heap_Free(param0->screenDataRaw);
}

static void WiFiNoteOwnCode_Draw(WiFiNoteOwnCode *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    StringTemplate_SetPlayerName(param2->stringTemplate, 0, SaveData_GetTrainerInfo(param1->saveData));
    WiFiNoteGraphics_PrintMessage(param2, 46);

    Bg_LoadToTilemapRect(param2->bgConfig, sBgLayers[2], param0->screenData->rawData, 0, 0, param0->screenData->screenWidth / 8, param0->screenData->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param2->bgConfig, sBgLayers[2]);
    Window_ScheduleCopyToVRAM(&param0->window);
    Window_ScheduleCopyToVRAM(&param0->codeWindow);
}

static void WiFiNoteOwnCode_Clear(WiFiNoteOwnCode *param0, WiFiNoteGraphics *param1)
{
    WiFiNoteGraphics_ClearMessageBox(param1);

    Bg_FillTilemapRect(param1->bgConfig, sBgLayers[2], 0, 0, 0, 32, 24, 0);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[2]);

    Window_ClearAndScheduleCopyToVRAM(&param0->window);
    Window_ClearAndScheduleCopyToVRAM(&param0->codeWindow);

    Bg_FillTilemapRect(param1->bgConfig, sBgLayers[3], 0, 0, 0, 32, 24, 0);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[3]);
}

static void WiFiNoteFriendDetail_Init(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    param0->isFirstArrival = SystemFlag_HandleFirstArrivalToZone(SaveData_GetVarsFlags(param1->saveData), HANDLE_FLAG_CHECK, FIRST_ARRIVAL_BATTLE_PARK);

    WiFiNoteFriendDetail_CreatePages(param0, param1, param2, heapID);
}

static int WiFiNoteFriendDetail_Main(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    BOOL v0;

    switch (param1->subState) {
    case 0:
        param0->holdActive = 0;
        param0->page = 0;
    case 1:
        WiFiNoteFriendDetail_Draw(param0, param1, param2, heapID);
        param1->subState = 2;
        break;
    case 2:
        if (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B)) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
            param1->subState = 6;
        } else {
            if (gSystem.pressedKeysRepeatable & PAD_KEY_LEFT) {
                WiFiNoteFriendDetail_ChangePage(param0, -1);
                param1->subState = 3;
                param0->transitionDir = 2;
            } else if (gSystem.pressedKeysRepeatable & PAD_KEY_RIGHT) {
                WiFiNoteFriendDetail_ChangePage(param0, 1);
                param1->subState = 3;
                param0->transitionDir = 3;
            } else if (gSystem.heldKeys & PAD_KEY_UP) {
                param1->subState = 5;
                param0->transitionDir = 0;
                param0->holdDelay = 4;
            } else if (gSystem.heldKeys & PAD_KEY_DOWN) {
                param1->subState = 5;
                param0->transitionDir = 1;
                param0->holdDelay = 4;
            }
        }

        if ((gSystem.heldKeys & (PAD_KEY_UP | PAD_KEY_DOWN)) == 0) {
            param0->holdActive = 0;
        }
        break;
    case 3:
        WiFiNoteFriendDetail_StartTransition(param0, param1, param2, heapID);
        WiFiNoteFriendDetail_UpdateTransition(param0, param1, param2, heapID);
        param1->subState = 4;
        break;
    case 4:
        v0 = WiFiNoteFriendDetail_UpdateTransition(param0, param1, param2, heapID);

        if (v0 == 1) {
            param1->subState = 2;
        }
        break;
    case 5:
        if (param0->holdActive) {
            param0->holdDelay--;

            if (param0->holdDelay > 0) {
                break;
            }
        }

        v0 = WiFiNoteFriendDetail_FindNextFriend(param1, param0->transitionDir);

        if (v0) {
            Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);

            WiFiNoteFriendDetail_Clear(param0, param2);
            WiFiNoteState_SetPage(param1, 4, 1);

            param0->holdActive = 1;
            return 1;
        }

        param1->subState = 2;
        break;
    case 6:
        WiFiNoteFriendDetail_Clear(param0, param2);
        WiFiNoteState_SetPage(param1, 1, 9);
        return 1;
    }

    return 0;
}

static void WiFiNoteFriendDetail_Free(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    WiFiNoteFriendDetail_DestroyPages(param0, param1, param2);
}

static void WiFiNoteFriendDetail_StartTransition(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, u32 param3)
{
    u32 v0;

    param0->transitionTimer = 0;

    WiFiNoteGraphics_SetArrowsAnimating(param2, 0);

    if (param0->transitionDir == 2) {
        v0 = 2;
    } else {
        v0 = 1;
    }

    WiFiNoteFriendDetail_DrawPage(param0, param1, param2, v0, param0->page, param3);
    Sound_PlayEffect(SEQ_SE_DP_SELECT5_sseq);
}

static BOOL WiFiNoteFriendDetail_UpdateTransition(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, u32 param3)
{
    u32 v0;
    s32 v1;
    NNSG2dViewRect v2;
    u32 v3;
    static void (*v4[4])(WiFiNoteFriendDetail *, WiFiNoteGraphics *, u32, u32) = {
        WiFiNoteFriendDetail_DrawCursorLeft, NULL, WiFiNoteFriendDetail_DrawCursorRight, NULL
    };

    if (param0->transitionTimer > 4) {
        Bg_ScheduleScroll(param2->bgConfig, sBgLayers[2], 0, 0);
        Bg_ScheduleScroll(param2->bgConfig, sBgLayers[3], 0, 0);

        if (param0->transitionDir == 2) {
            v0 = 2;
        } else {
            v0 = 1;
        }

        WiFiNoteFriendDetail_DrawPage(param0, param1, param2, 0, param0->page, param3);
        WiFiNoteGraphics_SetArrowsAnimating(param2, 1);

        return 1;
    }

    v1 = (param0->transitionTimer * 256) / 4;

    if (param0->transitionDir == 2) {
        v1 = -v1;
    }

    Bg_ScheduleScroll(param2->bgConfig, sBgLayers[2], 0, v1);
    Bg_ScheduleScroll(param2->bgConfig, sBgLayers[3], 0, v1);

    if (param0->transitionTimer % (4 / 4)) {
        v3 = param0->transitionTimer / (4 / 4);

        if (v4[v3]) {
            v4[v3](param0, param2, param0->page, param0->prevPage);
        }
    }

    param0->transitionTimer++;

    return 0;
}

static void WiFiNoteFriendDetail_CreatePages(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    int v0, v1;
    static const u32 v2[3] = {
        1,
        1 + 500,
        1 + 500,
    };

    WiFiNoteDetailPage_LoadGraphics(&param0->graphics, param2, heapID);

    for (v0 = 0; v0 < 3; v0++) {
        WiFiNoteDetailPage_Init(&param0->pages[v0], param2, &sPageOffsets[v0], v2[v0], heapID);

        for (v1 = 0; v1 < 7; v1++) {
            WiFiNoteDetailPage_CreateWindows(&param0->pages[v0], param2, v1, sDetailPageWindowCounts[v1], sDetailPageWindowRects[v1], heapID);
        }
    }
}

static void WiFiNoteFriendDetail_DestroyPages(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2)
{
    int v0, v1;

    for (v0 = 0; v0 < 3; v0++) {
        for (v1 = 0; v1 < 7; v1++) {
            WiFiNoteDetailPage_DeleteWindows(&param0->pages[v0], v1);
        }

        WiFiNoteDetailPage_Free(&param0->pages[v0]);
    }

    WiFiNoteDetailPage_FreeGraphics(&param0->graphics);
}

static void WiFiNoteFriendDetail_Draw(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    WiFiNoteGraphics_SetFriendName(param2, param1->saveData, param1->friendIndexList.indices[param1->selectedFriend], heapID);
    WiFiNoteGraphics_PrintMessage(param2, 13);
    WiFiNoteFriendDetail_DrawPage(param0, param1, param2, 0, param0->page, heapID);
    WiFiNoteGraphics_SetArrowsVisible(param2, 1);
}

static void WiFiNoteFriendDetail_Clear(WiFiNoteFriendDetail *param0, WiFiNoteGraphics *param1)
{
    int v0;

    WiFiNoteGraphics_SetArrowsVisible(param1, 0);

    for (v0 = 0; v0 < 3; v0++) {
        WiFiNoteDetailPage_Clear(&param0->pages[v0], param1);
    }

    WiFiNoteFriendDetail_ClearSelectionCursor(param0, param1);
    WiFiNoteGraphics_ClearMessageBox(param1);
}

static void WiFiNoteFriendDetail_DrawPage(WiFiNoteFriendDetail *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, u32 param3, u32 param4, u32 param5)
{
    if (param3 == 0) {
        param0->page = param4;

        WiFiNoteFriendDetail_DrawSelectionCursor(param0, param2, param4, param5);
    }

    WiFiNoteDetailPage_Draw(&param0->pages[param3], param1, param2, param4, &param0->graphics, param5);
}

static void WiFiNoteFriendDetail_DrawSelectionCursor(WiFiNoteFriendDetail *param0, WiFiNoteGraphics *param1, u32 param2, u32 param3)
{
    u32 v0;

    if (param0->isFirstArrival == 1) {
        Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], 22, 0, 9, 3, param1->screenData.data[1]->rawData, 16, 4, param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);
    } else {
        Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], 22, 0, 9, 3, param1->screenData.data[1]->rawData, 16, 4 + 3, param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);
    }

    v0 = 22 + (1 * param2) + 1;

    Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], v0, 0 + 1, 1, 1, param1->screenData.data[1]->rawData, 5, 0, param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[0]);
}

static void WiFiNoteFriendDetail_ClearSelectionCursor(WiFiNoteFriendDetail *param0, WiFiNoteGraphics *param1)
{
    Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], 22, 0, 9, 3, param1->screenData.data[1]->rawData, 0x10, 0x0, param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[0]);
}

static void WiFiNoteFriendDetail_DrawCursorLeft(WiFiNoteFriendDetail *param0, WiFiNoteGraphics *param1, u32 param2, u32 param3)
{
    int v0 = 22 + (1 * param3) + 1;

    Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], v0, 0 + 1, 1, 1, param1->screenData.data[1]->rawData, 5, 1, param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[0]);
}

static void WiFiNoteFriendDetail_DrawCursorRight(WiFiNoteFriendDetail *param0, WiFiNoteGraphics *param1, u32 param2, u32 param3)
{
    int v0;

    if (param0->isFirstArrival == 1) {
        Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], 22, 0, 9, 3, param1->screenData.data[1]->rawData, 16, 4, param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);
    } else {
        Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], 22, 0, 9, 3, param1->screenData.data[1]->rawData, 16, 4 + 3, param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);
    }

    v0 = 22 + (1 * param2) + 1;

    Bg_CopyToTilemapRect(param1->bgConfig, sBgLayers[0], v0, 0 + 1, 1, 1, param1->screenData.data[1]->rawData, 5, 0, param1->screenData.data[1]->screenWidth / 8, param1->screenData.data[1]->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param1->bgConfig, sBgLayers[0]);
}

static BOOL WiFiNoteFriendDetail_FindNextFriend(WiFiNoteState *param0, int param1)
{
    int v0;
    u32 v1;
    s32 v2;
    WiFiList *v3 = SaveData_GetWiFiList(param0->saveData);
    v2 = param0->selectedFriend;

    if (param1 == 0) {
        for (v0 = 0; v0 < param0->friendIndexList.count - 1; v0++) {
            v2--;

            if (v2 < 0) {
                v2 += param0->friendIndexList.count;
            }

            v1 = WiFiList_GetFriendField(v3, param0->friendIndexList.indices[v2], 8);

            if (v1 != 2) {
                param0->selectedFriend = v2;
                return 1;
            }
        }
    } else {
        for (v0 = 0; v0 < param0->friendIndexList.count - 1; v0++) {
            v2 = (v2 + 1) % param0->friendIndexList.count;

            v1 = WiFiList_GetFriendField(v3, param0->friendIndexList.indices[v2], 8);

            if (v1 != 2) {
                param0->selectedFriend = v2;
                return 1;
            }
        }
    }

    return 0;
}

static void WiFiNoteDetailPage_LoadGraphics(WiFiNoteDetailGraphics *param0, WiFiNoteGraphics *param1, enum HeapID heapID)
{
    static const u8 v0[7] = {
        4,
        5,
        6,
        7,
        8,
        9,
        10,
    };
    int v1;

    for (v1 = 0; v1 < 7; v1++) {
        param0->screenDataRaw[v1] = Graphics_GetScrnDataFromOpenNARC(param1->narc, v0[v1], 0, &param0->screenData[v1], heapID);
    }
}

static void WiFiNoteDetailPage_FreeGraphics(WiFiNoteDetailGraphics *param0)
{
    int v0;

    for (v0 = 0; v0 < 7; v0++) {
        Heap_Free(param0->screenDataRaw[v0]);
    }
}

static void WiFiNoteDetailPage_Init(WiFiNoteDetailPage *param0, WiFiNoteGraphics *param1, const WiFiNotePageOffset *param2, u32 param3, enum HeapID heapID)
{
    int v0;

    param0->offset = *param2;
    param0->baseTile = param3;

    for (v0 = 0; v0 < 7; v0++) {
        param0->windows[v0] = NULL;
        param0->windowCounts[v0] = 0;
    }
}

static void WiFiNoteDetailPage_Free(WiFiNoteDetailPage *param0)
{
    return;
}

static void WiFiNoteDetailPage_CreateWindows(WiFiNoteDetailPage *param0, WiFiNoteGraphics *param1, u32 param2, u32 param3, const WiFiNoteWindowRect *param4, enum HeapID heapID)
{
    int v0;
    u16 v1;

    param0->windows[param2] = Window_New(heapID, param3);
    param0->windowCounts[param2] = param3;

    v1 = param0->baseTile;

    for (v0 = 0; v0 < param3; v0++) {
        Window_Init(&param0->windows[param2][v0]);
        Window_Add(param1->bgConfig, &param0->windows[param2][v0], sBgLayers[3], MATH_ABS(param0->offset.x) + param4[v0].x, MATH_ABS(param0->offset.y) + param4[v0].y, param4[v0].width, param4[v0].height, 7, v1);
        Window_FillTilemap(&param0->windows[param2][v0], 0);
        v1 += (param4[v0].width * param4[v0].height);
    }
}

static void WiFiNoteDetailPage_DeleteWindows(WiFiNoteDetailPage *param0, u32 param1)
{
    if (param0->windows[param1]) {
        Windows_Delete(param0->windows[param1], param0->windowCounts[param1]);
        param0->windows[param1] = NULL;
        param0->windowCounts[param1] = 0;
    }
}

static void WiFiNoteDetailPage_ScheduleWindowCopy(WiFiNoteDetailPage *param0, u32 param1)
{
    int v0;

    for (v0 = 0; v0 < param0->windowCounts[param1]; v0++) {
        Window_ScheduleCopyToVRAM(&param0->windows[param1][v0]);
    }
}

static void WiFiNoteDetailPage_ClearWindows(WiFiNoteDetailPage *param0, u32 param1)
{
    int v0;

    for (v0 = 0; v0 < param0->windowCounts[param1]; v0++) {
        Window_ClearAndScheduleCopyToVRAM(&param0->windows[param1][v0]);
        Window_FillTilemap(&param0->windows[param1][v0], 0);
    }
}

static void WiFiNoteDetailPage_Draw(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, u32 param3, const WiFiNoteDetailGraphics *param4, u32 param5)
{
    static void (*v0[7])(WiFiNoteDetailPage *, WiFiNoteState *, WiFiNoteGraphics *, enum HeapID) = {
        WiFiNoteDetailPage_DrawProfile,
        WiFiNoteDetailPage_DrawMinigame,
        WiFiNoteDetailPage_DrawTower,
        WiFiNoteDetailPage_DrawFactory,
        WiFiNoteDetailPage_DrawCastle,
        WiFiNoteDetailPage_DrawHall,
        WiFiNoteDetailPage_DrawArcade
    };

    WiFiNoteDetailPage_Clear(param0, param2);

    Bg_LoadToTilemapRect(param2->bgConfig, sBgLayers[2], param4->screenData[param3]->rawData, MATH_ABS(param0->offset.x), MATH_ABS(param0->offset.y), param4->screenData[param3]->screenWidth / 8, param4->screenData[param3]->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param2->bgConfig, sBgLayers[2]);

    v0[param3](param0, param1, param2, param5);
}

static void WiFiNoteDetailPage_Clear(WiFiNoteDetailPage *param0, WiFiNoteGraphics *param1)
{
    int v0;

    for (v0 = 0; v0 < 7; v0++) {
        WiFiNoteDetailPage_ClearWindows(param0, v0);
    }

    WiFiNoteDetailPage_ClearBackground(param1, &param0->offset);
}

static void WiFiNoteDetailPage_DrawProfile(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    WiFiList *wifiList = SaveData_GetWiFiList(param1->saveData);

    String *string = String_Init(128, heapID);
    String *fmtString = String_Init(128, heapID);

    WiFiNoteDetailPage_PrintText(param0, 0, 0, param1, param2, 14, 0, 4, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetFriendGroupName(param2, param1->saveData, param1->friendIndexList.indices[param1->selectedFriend], heapID);
    WiFiNoteDetailPage_PrintText(param0, 0, 0, param1, param2, 61, 128, 4, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_PrintText(param0, 0, 0, param1, param2, 15, 0, 28, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteDetailPage_PrintText(param0, 0, 1, param1, param2, 16, 0, 4, TEXT_COLOR(1, 2, 0), string, fmtString, 0);
    WiFiNoteGraphics_SetNumber(param2, WiFiList_GetFriendField(wifiList, param1->friendIndexList.indices[param1->selectedFriend], 1));
    WiFiNoteDetailPage_PrintText(param0, 0, 1, param1, param2, 18, 64, 4, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_PrintText(param0, 0, 1, param1, param2, 17, 0, 20, TEXT_COLOR(1, 2, 0), string, fmtString, 0);
    WiFiNoteGraphics_SetNumber(param2, WiFiList_GetFriendField(wifiList, param1->friendIndexList.indices[param1->selectedFriend], 2));
    WiFiNoteDetailPage_PrintText(param0, 0, 1, param1, param2, 18, 64, 20, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_PrintText(param0, 0, 2, param1, param2, 19, 0, 4, TEXT_COLOR(1, 2, 0), string, fmtString, 0);
    WiFiNoteGraphics_SetNumber(param2, WiFiList_GetFriendField(wifiList, param1->friendIndexList.indices[param1->selectedFriend], 3));
    WiFiNoteDetailPage_PrintText(param0, 0, 2, param1, param2, 20, 128, 4, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    if (WiFiNoteState_HasPoffinCase(param1, heapID)) {
        WiFiNoteDetailPage_PrintText(param0, 0, 2, param1, param2, 21, 0, 20, TEXT_COLOR(1, 2, 0), string, fmtString, 0);
        WiFiNoteGraphics_SetNumber(param2, WiFiList_GetFriendField(wifiList, param1->friendIndexList.indices[param1->selectedFriend], 9));
        WiFiNoteDetailPage_PrintText(param0, 0, 2, param1, param2, 22, 128, 20, TEXT_COLOR(1, 2, 0), string, fmtString, 2);
    }

    WiFiNoteDetailPage_PrintText(param0, 0, 3, param1, param2, 23, 0, 6, TEXT_COLOR(15, 2, 0), string, fmtString, 0);

    if (WiFiNoteGraphics_SetFriendDate(param2, param1->saveData, param1->friendIndexList.indices[param1->selectedFriend]) != 0) {
        WiFiNoteDetailPage_PrintText(param0, 0, 3, param1, param2, 24, 224, 6, TEXT_COLOR(15, 2, 0), string, fmtString, 2);
    }

    TrainerClassGraphicIndex v3;
    u32 v0 = WiFiList_GetFriendField(wifiList, param1->friendIndexList.indices[param1->selectedFriend], 8);
    u32 v1 = WiFiList_GetFriendField(wifiList, param1->friendIndexList.indices[param1->selectedFriend], 7);
    SpriteSystem_SetTrainerClassGraphicsIndex(Appearance_GetData(v0, v1, APPEARANCE_DATA_TRAINER_CLASS_2), FACE_FRONT, &v3);

    void *buffer = Heap_Alloc(heapID, 0xC80);
    CharacterSprite_LoadTiledData(v3.narcID, v3.scan, heapID, 0, 0, 10, 10, buffer);
    Window_BlitBitmapRect(&param0->windows[0][4], buffer, 0, 0, 80, 80, 4, 4, 80, 80);
    Heap_Free(buffer);

    Graphics_LoadPalette(v3.narcID, v3.palette, PAL_LOAD_MAIN_BG, 320, 32, heapID);

    TextColor color;
    if (v0 == 0) {
        color = TEXT_COLOR(5, 6, 0);
    } else if (v0 == 1) {
        color = TEXT_COLOR(3, 4, 0);
    } else {
        color = TEXT_COLOR(1, 2, 0);
    }

    WiFiNoteGraphics_SetFriendName(param2, param1->saveData, param1->friendIndexList.indices[param1->selectedFriend], heapID);
    WiFiNoteDetailPage_PrintText(param0, 0, 4, param1, param2, 6, 44, 88, color, string, fmtString, 1);

    WiFiNoteDetailPage_ScheduleWindowCopy(param0, 0);

    int x = Window_GetXPos(&param0->windows[0][4]);
    int y = Window_GetYPos(&param0->windows[0][4]);
    Bg_ChangeTilemapRectPalette(param2->bgConfig, BG_LAYER_MAIN_3, x, y, 11, 11, 10);

    String_Free(string);
    String_Free(fmtString);
}

static void WiFiNoteDetailPage_DrawTower(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    BattleFrontierSave *frontier = SaveData_GetBattleFrontier(param1->saveData);

    String *string = String_Init(128, heapID);
    String *fmtString = String_Init(128, heapID);

    WiFiNoteDetailPage_PrintText(param0, 2, 0, param1, param2, 25, 0, 8, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    u32 entryID;
    if (BattleFrontierSave_GetStat(frontier, STAT_TOWER_WFC_STREAK_ACTIVE, param1->friendIndexList.indices[param1->selectedFriend]) == 0) {
        entryID = 30;
    } else {
        entryID = 31;
    }

    WiFiNoteDetailPage_PrintText(param0, 2, 0, param1, param2, entryID, 0, 32, TEXT_COLOR(1, 2, 0), string, fmtString, 0);
    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_TOWER_LATEST_STREAK_MODE_6, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 2, 0, param1, param2, 38, 160, 32, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_PrintText(param0, 2, 0, param1, param2, 32, 0, 56, TEXT_COLOR(1, 2, 0), string, fmtString, 0);
    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_TOWER_RECORD_STREAK_MODE_6, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 2, 0, param1, param2, 38, 160, 56, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_ScheduleWindowCopy(param0, 2);

    String_Free(string);
    String_Free(fmtString);
}

static void WiFiNoteDetailPage_DrawFactory(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    BattleFrontierSave *frontier = SaveData_GetBattleFrontier(param1->saveData);

    String *string = String_Init(128, heapID);
    String *fmtString = String_Init(128, heapID);

    WiFiNoteDetailPage_PrintText(param0, 3, 0, param1, param2, 26, 0, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteDetailPage_PrintText(param0, 3, 1, param1, param2, 33, 0, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 0);
    WiFiNoteDetailPage_PrintText(param0, 3, 1, param1, param2, 35, 224, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    u32 entryID;
    if (BattleFrontierSave_GetStat(frontier, STAT_FACTORY_50_WFC_STREAK_ACTIVE, param1->friendIndexList.indices[param1->selectedFriend]) == 0) {
        entryID = 30;
    } else {
        entryID = 31;
    }

    WiFiNoteDetailPage_PrintText(param0, 3, 2, param1, param2, entryID, 0, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_FACTORY_LATEST_STREAK_50_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 3, 2, param1, param2, 38, 112, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 1);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_FACTORY_LATEST_TRADE_COUNT_50_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 3, 2, param1, param2, 39, 224, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_PrintText(param0, 3, 2, param1, param2, 32, 0, 16, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_FACTORY_RECORD_STREAK_50_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 3, 2, param1, param2, 38, 112, 16, TEXT_COLOR(1, 2, 0), string, fmtString, 1);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_FACTORY_RECORD_TRADE_COUNT_50_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 3, 2, param1, param2, 39, 224, 16, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_PrintText(param0, 3, 3, param1, param2, 34, 0, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 0);
    WiFiNoteDetailPage_PrintText(param0, 3, 3, param1, param2, 35, 224, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    if (BattleFrontierSave_GetStat(frontier, STAT_FACTORY_OPEN_WFC_STREAK_ACTIVE, param1->friendIndexList.indices[param1->selectedFriend]) == 0) {
        entryID = 30;
    } else {
        entryID = 31;
    }

    WiFiNoteDetailPage_PrintText(param0, 3, 4, param1, param2, entryID, 0, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_FACTORY_LATEST_STREAK_OPEN_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 3, 4, param1, param2, 38, 112, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 1);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_FACTORY_LATEST_TRADE_COUNT_OPEN_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 3, 4, param1, param2, 39, 224, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_PrintText(param0, 3, 4, param1, param2, 32, 0, 16, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_FACTORY_RECORD_STREAK_OPEN_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 3, 4, param1, param2, 38, 112, 16, TEXT_COLOR(1, 2, 0), string, fmtString, 1);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_FACTORY_RECORD_TRADE_COUNT_OPEN_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 3, 4, param1, param2, 39, 224, 16, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_ScheduleWindowCopy(param0, 3);

    String_Free(string);
    String_Free(fmtString);
}

static void WiFiNoteDetailPage_DrawCastle(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    BattleFrontierSave *frontier = SaveData_GetBattleFrontier(param1->saveData);

    String *string = String_Init(128, heapID);
    String *fmtString = String_Init(128, heapID);

    WiFiNoteDetailPage_PrintText(param0, 4, 0, param1, param2, 27, 0, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 0);
    WiFiNoteDetailPage_PrintText(param0, 4, 0, param1, param2, 36, 224, 20, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    u32 entryID;
    if (BattleFrontierSave_GetStat(frontier, STAT_CASTLE_WFC_STREAK_ACTIVE, param1->friendIndexList.indices[param1->selectedFriend]) == 0) {
        entryID = 30;
    } else {
        entryID = 31;
    }

    WiFiNoteDetailPage_PrintText(param0, 4, 0, param1, param2, entryID, 0, 48, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_CASTLE_LATEST_STREAK_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 4, 0, param1, param2, 41, 112, 48, TEXT_COLOR(1, 2, 0), string, fmtString, 1);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_CASTLE_LATEST_CP_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 4, 0, param1, param2, 40, 224, 48, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_PrintText(param0, 4, 0, param1, param2, 32, 0, 72, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_CASTLE_RECORD_STREAK_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 4, 0, param1, param2, 41, 112, 72, TEXT_COLOR(1, 2, 0), string, fmtString, 1);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_CASTLE_RECORD_CP_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 4, 0, param1, param2, 40, 224, 72, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_ScheduleWindowCopy(param0, 4);

    String_Free(string);
    String_Free(fmtString);
}

static void WiFiNoteDetailPage_DrawHall(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    BattleFrontierSave *frontier = SaveData_GetBattleFrontier(param1->saveData);

    String *string = String_Init(128, heapID);
    String *fmtString = String_Init(128, heapID);

    WiFiNoteDetailPage_PrintText(param0, 5, 0, param1, param2, 28, 0, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    String *speciesName = MessageUtil_SpeciesName(BattleFrontierSave_GetStat(frontier, STAT_HALL_LATEST_SPECIES_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]), heapID);
    Text_AddPrinterWithParamsAndColor(&param0->windows[5][0], FONT_SYSTEM, speciesName, 0, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    String_Free(speciesName);

    u32 entryID;
    if (BattleFrontierSave_GetStat(frontier, STAT_HALL_WFC_STREAK_ACTIVE, param1->friendIndexList.indices[param1->selectedFriend]) == 0) {
        entryID = 30;
    } else {
        entryID = 31;
    }

    WiFiNoteDetailPage_PrintText(param0, 5, 0, param1, param2, entryID, 0, 48, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_HALL_LATEST_STREAK_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 5, 0, param1, param2, 38, 160, 48, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_PrintText(param0, 5, 0, param1, param2, 32, 0, 72, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, 122, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 5, 0, param1, param2, 38, 160, 72, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_ScheduleWindowCopy(param0, 5);

    String_Free(string);
    String_Free(fmtString);
}

static void WiFiNoteDetailPage_DrawArcade(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    BattleFrontierSave *frontier = SaveData_GetBattleFrontier(param1->saveData);

    String *string = String_Init(128, heapID);
    String *fmtString = String_Init(128, heapID);

    WiFiNoteDetailPage_PrintText(param0, 6, 0, param1, param2, 29, 0, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    u32 entryID;
    if (BattleFrontierSave_GetStat(frontier, STAT_ARCADE_WFC_STREAK_ACTIVE, param1->friendIndexList.indices[param1->selectedFriend]) == 0) {
        entryID = 30;
    } else {
        entryID = 31;
    }

    WiFiNoteDetailPage_PrintText(param0, 6, 0, param1, param2, entryID, 0, 24, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_ARCADE_LATEST_STREAK_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 6, 0, param1, param2, 42, 160, 24, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_PrintText(param0, 6, 0, param1, param2, 32, 0, 48, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, BattleFrontierSave_GetStat(frontier, STAT_ARCADE_RECORD_STREAK_MULTI_WFC, param1->friendIndexList.indices[param1->selectedFriend]));
    WiFiNoteDetailPage_PrintText(param0, 6, 0, param1, param2, 42, 160, 48, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_ScheduleWindowCopy(param0, 6);

    String_Free(string);
    String_Free(fmtString);
}

static void WiFiNoteDetailPage_DrawMinigame(WiFiNoteDetailPage *param0, WiFiNoteState *param1, WiFiNoteGraphics *param2, enum HeapID heapID)
{
    BattleFrontierSave *unused = SaveData_GetBattleFrontier(param1->saveData);
    WiFiList *wifiList = SaveData_GetWiFiList(param1->saveData);

    String *string = String_Init(128, heapID);
    String *fmtString = String_Init(128, heapID);

    WiFiNoteDetailPage_PrintText(param0, 1, 0, param1, param2, 43, 0, 0, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetPlazaMinigameName(param2, 0);
    WiFiNoteDetailPage_PrintText(param0, 1, 0, param1, param2, 44, 0, 24, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, WiFiList_GetFriendField(wifiList, param1->friendIndexList.indices[param1->selectedFriend], 10));
    WiFiNoteDetailPage_PrintText(param0, 1, 0, param1, param2, 45, 160, 24, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteGraphics_SetPlazaMinigameName(param2, 1);
    WiFiNoteDetailPage_PrintText(param0, 1, 0, param1, param2, 44, 0, 48, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, WiFiList_GetFriendField(wifiList, param1->friendIndexList.indices[param1->selectedFriend], 11));
    WiFiNoteDetailPage_PrintText(param0, 1, 0, param1, param2, 45, 160, 48, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteGraphics_SetPlazaMinigameName(param2, 2);
    WiFiNoteDetailPage_PrintText(param0, 1, 0, param1, param2, 44, 0, 72, TEXT_COLOR(1, 2, 0), string, fmtString, 0);

    WiFiNoteGraphics_SetNumber(param2, WiFiList_GetFriendField(wifiList, param1->friendIndexList.indices[param1->selectedFriend], 12));
    WiFiNoteDetailPage_PrintText(param0, 1, 0, param1, param2, 45, 160, 72, TEXT_COLOR(1, 2, 0), string, fmtString, 2);

    WiFiNoteDetailPage_ScheduleWindowCopy(param0, 1);

    String_Free(string);
    String_Free(fmtString);
}

static void WiFiNoteDetailPage_ClearBackground(WiFiNoteGraphics *param0, const WiFiNotePageOffset *param1)
{
    Bg_FillTilemapRect(param0->bgConfig, sBgLayers[2], 0, MATH_ABS(param1->x), MATH_ABS(param1->y), 32, 24, 0);
    Bg_ScheduleTilemapTransfer(param0->bgConfig, sBgLayers[2]);
    Bg_FillTilemapRect(param0->bgConfig, sBgLayers[3], 0, MATH_ABS(param1->x), MATH_ABS(param1->y), 32, 24, 0);
    Bg_ScheduleTilemapTransfer(param0->bgConfig, sBgLayers[3]);
}

static void WiFiNoteDetailPage_PrintText(WiFiNoteDetailPage *param0, u32 param1, u32 param2, WiFiNoteState *param3, WiFiNoteGraphics *param4, u32 entryID, u32 xOffset, u32 yOffset, TextColor color, String *string, String *fmtString, u32 param11)
{
    MessageLoader_GetString(param4->messageLoader, entryID, fmtString);
    StringTemplate_Format(param4->stringTemplate, string, fmtString);

    switch (param11) {
    case 1:
        xOffset -= ((Font_CalcStringWidth(FONT_SYSTEM, string, 0) + 1) / 2);
        break;
    case 2:
        xOffset -= Font_CalcStringWidth(FONT_SYSTEM, string, 0);
        break;
    }

    Text_AddPrinterWithParamsAndColor(&param0->windows[param1][param2], FONT_SYSTEM, string, xOffset, yOffset, TEXT_SPEED_NO_TRANSFER, color, NULL);
}

static void WiFiNoteFriendDetail_ChangePage(WiFiNoteFriendDetail *param0, s32 param1)
{
    int v0;

    if (param0->isFirstArrival == 1) {
        v0 = 7;
    } else {
        v0 = 2;
    }

    if (param1 > 0) {
        param0->prevPage = param0->page;
        param0->page = (param0->page + param1) % v0;
    } else if (param1 < 0) {
        param0->prevPage = param0->page;
        param0->page = param0->page + param1;

        if (param0->page < 0) {
            param0->page += v0;
        }
    }
}

static BOOL WiFiNoteState_HasPoffinCase(WiFiNoteState *param0, enum HeapID heapID)
{
    if (!Bag_GetItemQuantity(SaveData_GetBag(param0->saveData), ITEM_POFFIN_CASE, heapID)) {
        return 0;
    }

    return 1;
}
