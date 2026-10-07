#ifndef POKEPLATINUM_WIFI_2D_CHAR_H
#define POKEPLATINUM_WIFI_2D_CHAR_H

#include "wifi_2d_char/struct_wifi_2d_char_0222AE60_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BB38_decl.h"
#include "wifi_note/struct_wifi_note_sprite_params.h"

#include "palette.h"
#include "sprite.h"

WiFi2DCharManager *WiFi2DCharManager_New(SpriteList *param0, PaletteData *param1, u32 param2, u32 heapID);
void WiFi2DCharManager_Free(WiFi2DCharManager *param0);
void WiFi2DCharManager_LoadSpecies(WiFi2DCharManager *param0, u32 param1, u32 param2, int param3, u32 heapID);
void WiFi2DCharManager_UnloadSpecies(WiFi2DCharManager *param0, u32 param1);
BOOL WiFi2DCharManager_IsSpeciesLoaded(const WiFi2DCharManager *param0, u32 param1);
void WiFi2DCharManager_UnloadAllSpecies(WiFi2DCharManager *param0);
void WiFi2DCharManager_LoadShadowResources(WiFi2DCharManager *param0, u32 param1, int param2, u32 heapID);
void WiFi2DCharManager_UnloadShadowResources(WiFi2DCharManager *param0);
void WiFi2DCharManager_LoadShadow(WiFi2DCharManager *param0, u32 param1, u32 param2, u32 heapID);
void WiFi2DCharManager_UnloadShadow(WiFi2DCharManager *param0);
WiFi2DCharSprite *WiFi2DCharSprite_New(WiFi2DCharManager *param0, const WiFiNoteSpriteParams *param1, u32 param2, u32 heapID);
void WiFi2DCharSprite_Delete(WiFi2DCharSprite *param0);
const Sprite *WiFi2DCharSprite_GetSprite(const WiFi2DCharSprite *param0);
void WiFi2DCharSprite_SetPosition(WiFi2DCharSprite *param0, s16 param1, s16 param2);
void WiFi2DCharSprite_SetPriority(WiFi2DCharSprite *param0, u16 param1);
u16 WiFi2DCharSprite_GetPriority(const WiFi2DCharSprite *param0);
void WiFi2DCharSprite_SetVisible(WiFi2DCharSprite *param0, BOOL param1);
BOOL WiFi2DCharSprite_IsVisible(const WiFi2DCharSprite *param0);
int WiFi2DCharSprite_GetResourceType(const WiFi2DCharSprite *param0);
int WiFi2DCharSprite_GetAnimState(const WiFi2DCharSprite *param0);
void WiFi2DCharSprite_SetAnimFrame(WiFi2DCharSprite *param0, u16 param1);
u16 WiFi2DCharSprite_GetAnimFrame(const WiFi2DCharSprite *param0);
void WiFi2DCharSprite_SetShadowPosition(WiFi2DCharSprite *param0, s16 param1, s16 param2);
void WiFi2DCharSprite_SetAnim(WiFi2DCharSprite *param0, int param1, int param2);
void WiFi2DCharSprite_UpdateAnim(WiFi2DCharSprite *param0);

#endif // POKEPLATINUM_WIFI_2D_CHAR_H
