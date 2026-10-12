#ifndef POKEPLATINUM_STRUCT_02095EAC_T_H
#define POKEPLATINUM_STRUCT_02095EAC_T_H

#include "struct_defs/struct_union_room_drawing_app_args.h"
#include "struct_defs/struct_02095EAC_sub1.h"

#include "union_room_drawing/struct_union_room_drawing_prev_point.h"
#include "union_room_drawing/struct_union_room_drawing_status.h"

#include "bg_window.h"
#include "message.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "trainer_info.h"
#include "yes_no_touch_menu.h"

// State for the Union Room drawing (oekaki) app (union_room_drawing). The app lets up
// to five players share a canvas; the comm handlers in
// union_room_drawing_comm.c operate on this struct.
struct UnionRoomDrawing {
    BgConfig *bgConfig;
    BOOL unused_04;
    UnionRoomDrawingAppArgs *appArgs;
    StringTemplate *strTemplate;
    MessageLoader *msgLoader;
    String *playerNameStrings[5];
    String *headerString;
    String *messageString;
    int textPrinterID;
    SpriteList *spriteList;
    G2dRenderer g2dRenderer;
    SpriteResourceCollection *spriteResourceCollections[4];
    SpriteResource *spriteResources[2][4];
    SpriteResourcesHeader spriteHeader0;
    SpriteResourcesHeader spriteHeader1;
    Sprite *playerCursors[14];
    Sprite *penColorSprites[14];
    Sprite *toolSprites[12];
    Window playerWindows[5];
    Window drawingWindow; // 30x15-tile canvas the players draw on
    Window messageWindow;
    Window headerWindow;
    Window *unused_35C[2];
    int appState; // top-level app state, mirrored from the app's *param1
    int state;
    int nextState;
    int unused_370;
    int inputTimer;
    int connectedCountSnapshot;
    int connectedCount; // connected player count snapshot
    int connectedBitmap; // connected net-ID bitmap snapshot
    int drawingPlayerNetId; // net ID of the player currently drawing
    u8 unused_388[8][2];
    TrainerInfo *trainerInfo[8][2];
    u8 scratchBuffer[16384];
    u16 cursorColorAngle;
    u8 penColor;
    u8 penSize;
    UnionRoomDrawingStatus localDrawingStatus; // this player's pen/cursor status
    UnionRoomDrawingStatus drawingStatus[5]; // every player's pen/cursor status
    UnionRoomDrawingPrevPoint prevPoints[5];
    u8 *canvasBuffer;
    int sendChunkIndex; // index of the canvas chunk currently being streamed
    u8 drawingTiles[14400]; // canvas tile data (30 * 15 tiles of 32 bytes)
    UnionRoomDrawingChunk sendChunk; // chunk currently being streamed to clients
    UnionRoomDrawingChunk recvChunks[5]; // per-net-ID receive buffers for incoming chunks
    s32 connectedCount;
    u32 ackedNetIds; // server: net IDs that accepted the join handshake
    u16 ackedCount; // client: connected count reported by the server
    s16 commTimer;
    u8 flag;
    UnionRoomDrawingStatus drawingStatusBroadcast[5]; // server: statuses relayed to all players
    YesNoTouchMenu *yesNoMenu;
    int drawingState; // 1 = idle/ready, 2 = drawing in progress
    int clientReadySent;
    int clientReadySent; // server: a client has reported ready
    int readyToDraw;
    int disconnectHandled;
    int disconnectedBitmap;
};

#endif // POKEPLATINUM_STRUCT_02095EAC_T_H
