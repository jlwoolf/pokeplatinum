#ifndef POKEPLATINUM_WIFI_2D_CHAR_0222D1C0_H
#define POKEPLATINUM_WIFI_2D_CHAR_0222D1C0_H

#include "wifi_2d_char/struct_wifi_2d_char_0222D160.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D1C0_decl.h"
#include "overlay065/struct_ov65_0223582C.h"

#include "bg_window.h"
#include "sprite_util.h"

WiFi2DCharBackground *WiFi2DCharBackground_New(G2dRenderer *param0, BgConfig *param1, const UnkStruct_ov65_0223582C *param2, enum HeapID heapID);
void WiFi2DCharBackground_Free(WiFi2DCharBackground *param0);
void WiFi2DCharBackground_Update(WiFi2DCharBackground *param0, const WiFi2DCharViewOffset *param1);

#endif // POKEPLATINUM_WIFI_2D_CHAR_0222D1C0_H
