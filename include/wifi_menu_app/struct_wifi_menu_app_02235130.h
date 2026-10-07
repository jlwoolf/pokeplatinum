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
    BOOL unk_00;
    u32 heapID;
    u32 unk_08;
    BOOL unk_0C;
    BgConfig *unk_10;
    WiFiMenuAppSpriteManager unk_14;
    WiFiMenuAppActor unk_1F0[48];
    WiFiMenuAppActor *unk_730;
    WiFiMenuAppPalette unk_734;
    WiFi2DCharGrid *unk_748;
    WiFi2DCharObjectManager *unk_74C;
    WiFi2DCharRenderer *unk_750;
    WiFi2DCharViewOffset unk_754;
    WiFi2DCharBackground *unk_758;
    WiFi2DCharEventQueue *unk_75C;
} WiFiMenuAppBoard;

#endif // POKEPLATINUM_STRUCT_WIFI_MENU_APP_02235130_H
