#ifndef POKEPLATINUM_WIFI_2D_CHAR_0222CCE4_H
#define POKEPLATINUM_WIFI_2D_CHAR_0222CCE4_H

#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CD2C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CE44.h"

#include "palette.h"
#include "sprite.h"

WiFi2DCharRenderer *WiFi2DCharRenderer_New(SpriteList *param0, PaletteData *param1, u32 param2, u32 param3, u32 heapID);
WiFi2DCharRenderer *WiFi2DCharRenderer_NewWithShadow(SpriteList *param0, PaletteData *param1, u32 param2, u32 param3, int param4, u32 param5, u32 heapID);
void WiFi2DCharRenderer_Free(WiFi2DCharRenderer *param0);
void WiFi2DCharRenderer_LoadSpecies(WiFi2DCharRenderer *param0, u32 param1, int param2, u32 heapID);
void WiFi2DCharRenderer_UnloadSpecies(WiFi2DCharRenderer *param0, u32 param1);
BOOL WiFi2DCharRenderer_IsSpeciesLoaded(const WiFi2DCharRenderer *param0, u32 param1);
void WiFi2DCharRenderer_UnloadAllSpecies(WiFi2DCharRenderer *param0);
void WiFi2DCharRenderer_LoadShadowResources(WiFi2DCharRenderer *param0, int param1, u32 heapID);
WiFi2DCharRenderObject *WiFi2DCharRenderer_AddObject(WiFi2DCharRenderer *param0, const WiFi2DCharObject *param1, BOOL param2, u32 heapID);
void WiFi2DCharRenderer_RemoveObject(WiFi2DCharRenderObject *param0);
void WiFi2DCharRenderer_UpdateAll(WiFi2DCharRenderer *param0);
void WiFi2DCharRenderer_UpdateObject(WiFi2DCharRenderObject *param0);
void WiFi2DCharRenderer_SetObjectEnabled(WiFi2DCharRenderObject *param0, BOOL param1);
void WiFi2DCharRenderer_ResetObjectAnim(WiFi2DCharRenderObject *param0);
void WiFi2DCharRenderer_UpdateObjectAnim(WiFi2DCharRenderObject *param0);
void WiFi2DCharRenderer_RefreshObject(WiFi2DCharRenderObject *param0);
void WiFi2DCharRenderer_SetObjectPosition(WiFi2DCharRenderObject *param0, WiFi2DCharPosition param1);
BOOL WiFi2DCharRenderer_IsObjectVisible(const WiFi2DCharRenderObject *param0);
void WiFi2DCharRenderer_SetObjectVisible(WiFi2DCharRenderObject *param0, BOOL param1);
u16 WiFi2DCharRenderer_GetObjectPriority(const WiFi2DCharRenderObject *param0);
void WiFi2DCharRenderer_SetObjectAnim(WiFi2DCharRenderObject *param0, int param1);
u32 WiFi2DChar_GetPriorityForY(s16 param0, BOOL param1);
u32 WiFi2DCharRenderer_GetObjectPaletteOffset(const WiFi2DCharRenderObject *param0);
void WiFi2DCharRenderer_SetObjectShadowPosition(WiFi2DCharRenderObject *param0, WiFi2DCharPosition param1);

#endif // POKEPLATINUM_WIFI_2D_CHAR_0222CCE4_H
