#ifndef POKEPLATINUM_CONTEST_COMPETITION_0223F118_H
#define POKEPLATINUM_CONTEST_COMPETITION_0223F118_H

#include "struct_decls/struct_02012744_decl.h"

#include "contest_competition/struct_contest_competition_0223F2E4.h"
#include "contest_competition/struct_contest_competition_0223F6E8.h"
#include "contest_competition/struct_contest_competition_0223F744.h"

#include "bg_window.h"
#include "contest.h"
#include "g3d_pipeline.h"
#include "palette.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "text.h"

G3DPipelineBuffers *contest_competition_0223F140(enum HeapID heapID);
void contest_competition_0223F1E0(G3DPipelineBuffers *param0);
void contest_competition_0223F1E8(enum HeapID heapID, BgConfig *param1, SpriteManager *param2, FontOAMManager *param3, UnkStruct_contest_competition_0223F2E4 *param4, const String *param5, enum Font param6, TextColor param7, int param8, int param9, int param10, int param11, int param12, int param13, int param14);
void contest_competition_0223F2E4(UnkStruct_contest_competition_0223F2E4 *param0);
void contest_competition_0223F2F8(UnkStruct_contest_competition_0223F2E4 *param0, int param1, int param2, int param3);
String *Contest_GetJudgeName(u32 judgeNameMessageID, enum HeapID heapID);
void contest_competition_0223F334(Contest *param0, int param1);
void contest_competition_0223F374(Contest *param0);
void contest_competition_0223F560(SpriteSystem *param0, SpriteManager *param1, PaletteData *param2, int param3, int param4, int param5, int param6);
void contest_competition_0223F5E8(SpriteManager *param0, int param1, int param2, int param3, int param4);
void contest_competition_0223F630(UnkStruct_contest_competition_0223F6E8 *param0, SpriteSystem *param1, SpriteManager *param2, int param3, int param4, int param5, int param6, int param7, int param8, int param9, u32 param10);
void contest_competition_0223F6C4(UnkStruct_contest_competition_0223F6E8 *param0);
UnkStruct_contest_competition_0223F744 *contest_competition_0223F70C(enum HeapID heapID, PaletteData *param1, const u16 *param2, int param3, int param4, u32 param5);
void contest_competition_0223F744(UnkStruct_contest_competition_0223F744 *param0);
BOOL contest_competition_0223F760(void);

#endif // POKEPLATINUM_CONTEST_COMPETITION_0223F118_H
