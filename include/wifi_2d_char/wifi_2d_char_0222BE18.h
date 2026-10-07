#ifndef POKEPLATINUM_WIFI_2D_CHAR_0222BE18_H
#define POKEPLATINUM_WIFI_2D_CHAR_0222BE18_H

#include "constants/heap.h"

#include "wifi_2d_char/struct_wifi_2d_char_0222BE18_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CCB8.h"
#include "overlay065/struct_ov65_022376D0.h"

WiFi2DCharObjectManager *WiFi2DCharObjectManager_New(u32 param0, enum HeapID heapID);
void WiFi2DCharObjectManager_Free(WiFi2DCharObjectManager *param0);
void WiFi2DCharObjectManager_StartMove(WiFi2DCharObjectManager *param0, const WiFi2DCharMoveRequest *param1);
void WiFi2DCharObjectManager_Update(WiFi2DCharObjectManager *param0);
u32 WiFi2DCharObjectManager_GetCapacity(const WiFi2DCharObjectManager *param0);
WiFi2DCharObject *WiFi2DCharObjectManager_AddObject(WiFi2DCharObjectManager *param0, const UnkStruct_ov65_022376D0 *param1);
void WiFi2DCharObject_Reset(WiFi2DCharObject *param0);
WiFi2DCharObject *WiFi2DCharObjectManager_FindObjectByID(WiFi2DCharObjectManager *param0, u16 param1);
WiFi2DCharObject *WiFi2DCharObjectManager_GetObject(WiFi2DCharObjectManager *param0, u16 param1);
const WiFi2DCharObject *WiFi2DCharObjectManager_FindObjectByIDConst(const WiFi2DCharObjectManager *param0, u16 param1);
const WiFi2DCharObject *WiFi2DCharObjectManager_GetObjectConst(const WiFi2DCharObjectManager *param0, u16 param1);
s32 WiFi2DCharObject_GetField(const WiFi2DCharObject *param0, int param1);
void WiFi2DCharObject_SetField(WiFi2DCharObject *param0, int param1, s32 param2);
WiFi2DCharPosition WiFi2DCharPosition_OffsetByDirection(WiFi2DCharPosition param0, int param1);
int WiFi2DChar_DirectionOpposite(int param0);
WiFi2DCharPosition WiFi2DCharObject_GetPosition(const WiFi2DCharObject *param0);
WiFi2DCharPosition WiFi2DCharObject_GetTargetPosition(const WiFi2DCharObject *param0);
WiFi2DCharPosition WiFi2DCharObject_GetInterpolatedPosition(const WiFi2DCharObject *param0);
void WiFi2DCharObject_SetPosition(WiFi2DCharObject *param0, WiFi2DCharPosition param1);
void WiFi2DCharObject_SetTargetPosition(WiFi2DCharObject *param0, WiFi2DCharPosition param1);
const WiFi2DCharObject *WiFi2DCharObjectManager_FindObjectAtOffset(const WiFi2DCharObject *param0, const WiFi2DCharObjectManager *param1, int param2);
const WiFi2DCharObject *WiFi2DCharObjectManager_FindObjectAtPosition(const WiFi2DCharObjectManager *param0, WiFi2DCharPosition param1);

#endif // POKEPLATINUM_WIFI_2D_CHAR_0222BE18_H
