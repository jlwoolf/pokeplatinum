#ifndef POKEPLATINUM_STRUCT_WIFI_MENU_APP_022358CC_H
#define POKEPLATINUM_STRUCT_WIFI_MENU_APP_022358CC_H

#include "wifi_menu_app/struct_wifi_menu_app_022358CC_sub1.h"

#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_util.h"

typedef struct {
    SpriteList *spriteList;
    G2dRenderer renderer;
    SpriteResourceCollection *resourceCollections[4];
    WiFiMenuAppSpriteSet spriteSet;
} WiFiMenuAppSpriteManager;

#endif // POKEPLATINUM_STRUCT_WIFI_MENU_APP_022358CC_H
