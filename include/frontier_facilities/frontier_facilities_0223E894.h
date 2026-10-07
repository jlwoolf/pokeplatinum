#ifndef POKEPLATINUM_FRONTIER_FACILITIES_0223E894_H
#define POKEPLATINUM_FRONTIER_FACILITIES_0223E894_H

#include "frontier_facilities/struct_frontier_facilities_0223E9EC.h"
#include "frontier_facilities/struct_frontier_facilities_0223EA38.h"
#include "frontier_facilities/struct_frontier_facilities_0223EA84_decl.h"
#include "frontier_facilities/struct_frontier_facilities_0223EBD0_decl.h"
#include "frontier_facilities/struct_frontier_facilities_0223F094.h"
#include "frontier_facilities/struct_frontier_facilities_0223F174_decl.h"
#include "frontier_facilities/struct_frontier_facilities_0223F1B4.h"

#include "bg_window.h"

void FrontierFacilities_StartScreenFlash(int param0, u32 param1, u32 param2, BOOL *param3, u32 param4);
void FrontierFacilities_SetMasterBrightness(int param0, int param1);
void FrontierFacilities_StartBrightnessFade(FrontierFacilitiesAnimation *param0, int param1, int param2, int param3, int param4);
BOOL FrontierFacilities_UpdateBrightnessFade(FrontierFacilitiesAnimation *param0);
void FrontierFacilities_InitAnimation(FrontierFacilitiesLinearAnimation *param0, int param1, int param2, int param3);
BOOL FrontierFacilities_StepAnimation(FrontierFacilitiesLinearAnimation *param0);
FrontierFacilitiesWipeRect *FrontierFacilities_NewWipeRect(enum HeapID heapID);
void FrontierFacilities_FreeWipeRect(FrontierFacilitiesWipeRect *param0);
void FrontierFacilities_StartWipeRect(FrontierFacilitiesWipeRect *param0, int param1, int param2, int param3, int param4, int param5, Window *param6, u32 param7, u32 param8, u8 param9);
BOOL FrontierFacilities_UpdateWipeRect(FrontierFacilitiesWipeRect *param0);
FrontierFacilitiesWipeManager *FrontierFacilities_NewWipeManager(enum HeapID heapID);
void FrontierFacilities_FreeWipeManager(FrontierFacilitiesWipeManager *param0);
void FrontierFacilities_StartWipe(FrontierFacilitiesWipeManager *param0, u8 param1, u8 param2, Window *param3, u8 param4);
BOOL FrontierFacilities_UpdateHorizontalWipe(FrontierFacilitiesWipeManager *param0);
BOOL FrontierFacilities_UpdateVerticalWipe(FrontierFacilitiesWipeManager *param0);
void FrontierFacilities_InitScreenScroll(FrontierFacilitiesScreenScroll *param0, enum HeapID heapID);
void FrontierFacilities_BeginScreenScroll(FrontierFacilitiesScreenScroll *param0, u8 param1, u8 param2, u16 param3, fx32 param4, s16 param5, u32 param6, u32 param7, u32 param8);
FrontierFacilitiesAffineBuffer *FrontierFacilities_NewAffineBuffer(u32 param0, FrontierFacilitiesAffineEntry *param1, enum HeapID heapID);
void FrontierFacilities_FreeAffineBuffer(FrontierFacilitiesAffineBuffer *param0);
void *FrontierFacilities_GetAffineWriteBuffer(const FrontierFacilitiesAffineBuffer *param0);

#endif // POKEPLATINUM_FRONTIER_FACILITIES_0223E894_H
