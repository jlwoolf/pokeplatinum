#ifndef POKEPLATINUM_WIFI_2D_CHAR_0222BCE8_H
#define POKEPLATINUM_WIFI_2D_CHAR_0222BCE8_H

#include "constants/heap.h"

#include "wifi_2d_char/struct_wifi_2d_char_0222BCE8_decl.h"
#include "wifi_2d_char/union_wifi_2d_char_0222BDAC.h"

WiFi2DCharGrid *WiFi2DCharGrid_New(u16 param0, u16 param1, enum HeapID heapID);
void WiFi2DCharGrid_Free(WiFi2DCharGrid *param0);
u16 WiFi2DCharGrid_GetWidth(const WiFi2DCharGrid *param0);
u16 WiFi2DCharGrid_GetHeight(const WiFi2DCharGrid *param0);
void WiFi2DCharGrid_SetTiles(WiFi2DCharGrid *param0, const WiFi2DCharTile *param1);
WiFi2DCharTile WiFi2DCharGrid_GetTile(const WiFi2DCharGrid *param0, u16 param1, u16 param2);
BOOL WiFi2DCharGrid_IsTileBlocked(const WiFi2DCharGrid *param0, u16 param1, u16 param2);
u32 WiFi2DCharGrid_GetTileFlags(const WiFi2DCharGrid *param0, u16 param1, u16 param2);

#endif // POKEPLATINUM_WIFI_2D_CHAR_0222BCE8_H
