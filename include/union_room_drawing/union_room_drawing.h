#ifndef POKEPLATINUM_UNION_ROOM_DRAWING_H
#define POKEPLATINUM_UNION_ROOM_DRAWING_H

#include "struct_decls/struct_02095EAC_decl.h"

#include "overlay_manager.h"

int UnionRoomDrawing_Init(ApplicationManager *appMan, int *param1);
int UnionRoomDrawing_Main(ApplicationManager *appMan, int *param1);
int UnionRoomDrawing_Exit(ApplicationManager *appMan, int *param1);
void UnionRoomDrawing_HandleCommState(UnionRoomDrawing *param0, int param1, u8 param2);
int UnionRoomDrawing_GetConnectedCount(void);

#endif // POKEPLATINUM_UNION_ROOM_DRAWING_H
