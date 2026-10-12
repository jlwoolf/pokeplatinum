#ifndef POKEPLATINUM_MAIN_MENU_0222D04C_H
#define POKEPLATINUM_MAIN_MENU_0222D04C_H

#include "main_menu/mystery_gift_app.h"

#include "savedata.h"

void MysteryGiftShare_StartServer(MysteryGiftAppData *param0, SaveData *saveData, int param2);
void MysteryGiftShare_SendDataHuge(const void *param0, int param1);
void MysteryGiftShare_StartClient(MysteryGiftAppData *param0, int param1);
void MysteryGiftShare_ConnectToServer(int param0);
int MysteryGiftShare_FindReceivedEventData(MysteryGiftAppData *param0);
void MysteryGiftShare_OnEventDataReceived(int param0, int param1, void *param2, void *param3);
int MysteryGiftShare_HasReceivedEventData(void);
int MysteryGiftShare_GetWonderCardSize(void);
u8 *MysteryGiftShare_GetWonderCardBuffer(int param0, void *param1, int param2);
void MysteryGiftShare_OnPlayerInfoReceived(int param0, int param1, void *param2, void *param3);
void MysteryGiftShare_End(void);

#endif // POKEPLATINUM_MAIN_MENU_0222D04C_H
