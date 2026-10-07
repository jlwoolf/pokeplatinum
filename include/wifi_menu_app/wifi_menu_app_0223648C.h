#ifndef POKEPLATINUM_WIFI_MENU_APP_0223648C_H
#define POKEPLATINUM_WIFI_MENU_APP_0223648C_H

#include "wifi_menu_app/struct_wifi_menu_app_022366E4.h"
#include "wifi_menu_app/struct_wifi_menu_app_02236744_decl.h"
#include "wifi_menu_app/struct_wifi_menu_app_02236760.h"

#include "overlay_manager.h"

int WiFiCommApp_Init(ApplicationManager *appMan, int *param1);
int WiFiCommApp_Main(ApplicationManager *appMan, int *param1);
int WiFiCommApp_Exit(ApplicationManager *appMan, int *param1);
void WiFiCommApp_HandlePlayerStatus(WiFiCommApp *param0, const WiFiCommPlayerStatus *param1);
void WiFiCommApp_RequestSync(WiFiCommApp *param0);
void WiFiCommApp_HandleVoiceChatFlags(WiFiCommApp *param0, const WiFiCommVoiceChatFlags *param1);

#endif // POKEPLATINUM_WIFI_MENU_APP_0223648C_H
