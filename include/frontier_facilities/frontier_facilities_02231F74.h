#ifndef POKEPLATINUM_FRONTIER_FACILITIES_02231F74_H
#define POKEPLATINUM_FRONTIER_FACILITIES_02231F74_H

#include "struct_defs/pokemon.h"

#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CCB8.h"
#include "frontier_facilities/defs.h"
#include "frontier_facilities/frontier_graphics.h"
#include "frontier_facilities/struct_frontier_facilities_0222FEDC.h"

#include "message.h"
#include "sprite.h"
#include "string_template.h"
#include "sys_task_manager.h"

typedef struct FrontierAnimCmd {
    u16 action;
    u16 count;
} FrontierAnimCmd;

typedef struct FrontierAnimData {
    u8 state;
    u8 elapsed;
    s16 delay;
    u16 localID;
    u8 *totalMovementCount;
    const FrontierAnimCmd *animCmd;
    WiFi2DCharMoveQueue *unk_10;
    FrontierObject *frontierObj;
} FrontierAnimData;

void FrontierShowMessage(FrontierScriptManager *scriptMan, const MessageLoader *msgLoader, u16 messageID, u8 canSpeedUp, FrontierMessageOptions *msgOptions);
void Frontier_CloseMessage(FrontierScriptManager *scriptMan);
FrontierMenuManager *FrontierMenuManager_New(FrontierScriptManager *scriptMan, u8 anchorX, u8 anchorY, u8 initalCursorPos, u8 canExitWithB, u16 *selectedOptionPtr, StringTemplate *strTemplate, MessageLoader *msgLoader);
void FrontierMenuManager_AddMenuEntry(FrontierMenuManager *menuManager, u32 entryID, u32 altTextEntryID, u32 index);
void FrontierMenuManager_ShowMenu(FrontierMenuManager *menuManager);
FrontierMenuManager *FrontierMenuManager_New2(FrontierScriptManager *scriptMan, u8 anchorX, u8 anchorY, u8 initialCursorPos, u8 canExitWithB, u16 *selectedOptionPtr, StringTemplate *strTemplate, MessageLoader *msgLoader);
void FrontierMenuManager_AddListMenuEntry(FrontierMenuManager *menuManager, u32 entry, u32 altTextEntryID, u32 index);
void FrontierMenuManager_ShowListMenu(FrontierMenuManager *menuManager);
void FrontierMenuManager_FreeListMenu(FrontierMenuManager *menuManager);
void FrontierObject_DoAnimation(SysTask *task, void *data);
void FrontierFacilities_BuildMoveRequest(WiFi2DCharMoveRequest *param0, WiFi2DCharObject *param1, int param2, int action);
void FrontierFacilities_CreatePokemonFieldSprite(FrontierGraphics *param0, Pokemon *param1, enum HeapID heapID, int param3, int param4, int param5, int param6, int param7, int param8, u16 param9);
void FrontierFacilities_DeletePokemonFieldSprite(FrontierGraphics *param0, int param1);
void BattleFrontier_LoadMonSpriteData(FrontierGraphics *graphics);
void BattleFrontier_UnloadMonSpriteData(FrontierGraphics *graphics);
ManagedSprite *BattleFrontier_CreateMonSprite(FrontierGraphics *graphics, Pokemon *mon, int resourceID, int x, int y);
void BattleFrontier_DeleteMonSprite(FrontierGraphics *graphics, ManagedSprite *sprite, int resourceID);
void BattleFrontier_LoadItemSpriteData(FrontierGraphics *graphics);
void BattleFrontier_UnloadItemSpriteData(FrontierGraphics *graphics);
ManagedSprite *BattleFrontier_CreateItemSprite(FrontierGraphics *graphics, int x, int y);
void BattleFrontier_DeleteItemSprite(FrontierGraphics *graphics, ManagedSprite *sprite);
void BattleFrontier_PrintNormalTrainerMessage(FrontierScriptContext *ctx, u16 *args);
void BattleFrontier_PrintTrainerMessage(FrontierScriptContext *ctx, u16 *args, u32 bankID);
void FrontierFacilities_ShakeObjectTask(SysTask *param0, void *param1);
void FrontierFacilities_WindowEffectTask(SysTask *param0, void *param1);
void FrontierMenuManager_SetHorizontalAnchor(FrontierMenuManager *menuManager, BOOL anchorRight);
void FrontierMenuManager_SetVerticalAnchor(FrontierMenuManager *menuManager, BOOL anchorBottom);

#endif // POKEPLATINUM_FRONTIER_FACILITIES_02231F74_H
