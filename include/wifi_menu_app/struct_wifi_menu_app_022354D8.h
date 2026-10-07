#ifndef POKEPLATINUM_STRUCT_WIFI_MENU_APP_022354D8_H
#define POKEPLATINUM_STRUCT_WIFI_MENU_APP_022354D8_H

#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CE44.h"
#include "wifi_menu_app/struct_wifi_menu_app_02235130_decl.h"

typedef struct WiFiMenuAppActor_t {
    WiFi2DCharObject *unk_00;
    WiFi2DCharRenderObject *unk_04;
    s16 unk_08;
    u8 unk_0A;
    u8 unk_0B;
    u16 unk_0C;
    u16 unk_0E;

    // clang-format off
    BOOL (* unk_10)(WiFiMenuAppBoard *, struct WiFiMenuAppActor_t *);
    BOOL (* unk_14)(WiFiMenuAppBoard *, struct WiFiMenuAppActor_t *);
    // clang-format on

    void (*unk_18)(WiFiMenuAppBoard *, struct WiFiMenuAppActor_t *);
} WiFiMenuAppActor;

#endif // POKEPLATINUM_STRUCT_WIFI_MENU_APP_022354D8_H
