#ifndef POKEPLATINUM_STRUCT_WIFI_MENU_APP_022354D8_H
#define POKEPLATINUM_STRUCT_WIFI_MENU_APP_022354D8_H

#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CE44.h"
#include "wifi_menu_app/struct_wifi_menu_app_02235130_decl.h"

typedef struct WiFiMenuAppActor_t {
    WiFi2DCharObject *object;
    WiFi2DCharRenderObject *renderObject;
    s16 timer;
    u8 facingActorID;
    u8 pendingState;
    u16 state;
    u16 prevState;

    // clang-format off
    BOOL (* updateFunc)(WiFiMenuAppBoard *, struct WiFiMenuAppActor_t *);
    BOOL (* savedUpdateFunc)(WiFiMenuAppBoard *, struct WiFiMenuAppActor_t *);
    // clang-format on

    void (*drawFunc)(WiFiMenuAppBoard *, struct WiFiMenuAppActor_t *);
} WiFiMenuAppActor;

#endif // POKEPLATINUM_STRUCT_WIFI_MENU_APP_022354D8_H
