#ifndef POKEPLATINUM_STRUCT_WIFI_MENU_APP_02235130_H
#define POKEPLATINUM_STRUCT_WIFI_MENU_APP_02235130_H

#include "wifi_2d_char/struct_wifi_2d_char_0222BCE8_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BE18_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CD2C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D160.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D1C0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D848_decl.h"
#include "wifi_menu_app/struct_wifi_menu_app_022354D8.h"
#include "wifi_menu_app/struct_wifi_menu_app_022358CC.h"
#include "wifi_menu_app/struct_wifi_menu_app_02236318.h"

#include "bg_window.h"

typedef struct WiFiMenuAppBoard_t {
    BOOL active;
    u32 heapID;
    u32 unk_08;
    BOOL busy;
    BgConfig *bgConfig;
    WiFiMenuAppSpriteManager spriteManager;
    WiFiMenuAppActor actors[48];
    WiFiMenuAppActor *player;
    WiFiMenuAppPalette palette;
    WiFi2DCharGrid *grid;
    WiFi2DCharObjectManager *objectManager;
    WiFi2DCharRenderer *renderer;
    WiFi2DCharViewOffset viewOffset;
    WiFi2DCharBackground *background;
    WiFi2DCharEventQueue *eventQueue;
} WiFiMenuAppBoard;

#endif // POKEPLATINUM_STRUCT_WIFI_MENU_APP_02235130_H
