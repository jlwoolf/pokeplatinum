#ifndef POKEPLATINUM_MAIN_MENU_02232054_H
#define POKEPLATINUM_MAIN_MENU_02232054_H

#include "main_menu/mystery_gift_app.h"

#include "bg_window.h"
#include "savedata.h"

void MysteryGiftUtil_SetupGxBanks(void);
void MysteryGiftUtil_InitBg(BgConfig *param0);
int MysteryGiftUtil_GetEventReceiveStatus(SaveData *saveData, MysteryGiftEventData *param1);

#endif // POKEPLATINUM_MAIN_MENU_02232054_H
