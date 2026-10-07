#ifndef POKEPLATINUM_WIFI_2D_CHAR_0222D77C_H
#define POKEPLATINUM_WIFI_2D_CHAR_0222D77C_H

#include "constants/heap.h"

#include "wifi_2d_char/struct_wifi_2d_char_0222CCB8.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D77C_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D848_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D894.h"

WiFi2DCharMoveQueue *WiFi2DCharMoveQueue_New(u32 param0, enum HeapID heapID);
void WiFi2DCharMoveQueue_Free(WiFi2DCharMoveQueue *param0);
void WiFi2DCharMoveQueue_Push(WiFi2DCharMoveQueue *param0, const WiFi2DCharMoveRequest *param1);
BOOL WiFi2DCharMoveQueue_Pop(WiFi2DCharMoveQueue *param0, WiFi2DCharMoveRequest *param1);
WiFi2DCharEventQueue *WiFi2DCharEventQueue_New(u32 param0, enum HeapID heapID);
void WiFi2DCharEventQueue_Free(WiFi2DCharEventQueue *param0);
void WiFi2DCharEventQueue_Push(WiFi2DCharEventQueue *param0, const WiFi2DCharEvent *param1);
BOOL WiFi2DCharEventQueue_Pop(WiFi2DCharEventQueue *param0, WiFi2DCharEvent *param1);

#endif // POKEPLATINUM_WIFI_2D_CHAR_0222D77C_H
