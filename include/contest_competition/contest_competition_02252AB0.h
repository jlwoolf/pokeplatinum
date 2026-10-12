#ifndef POKEPLATINUM_CONTEST_COMPETITION_02252AB0_H
#define POKEPLATINUM_CONTEST_COMPETITION_02252AB0_H

#include "contest_competition/struct_contest_game_sprite_group_decl.h"

#include "palette.h"
#include "sprite_system.h"

void contest_competition_02252AB0(SpriteSystem *param0, SpriteManager *param1, PaletteData *param2, u32 param3, u32 param4, u32 param5, u32 param6);
void contest_competition_02252B20(SpriteManager *param0, u32 param1, u32 param2, u32 param3, u32 param4);
ContestGameSpriteGroup *contest_competition_02252B48(SpriteSystem *param0, SpriteManager *param1, enum HeapID heapID, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8);
void contest_competition_02252BCC(ContestGameSpriteGroup *param0);
void contest_competition_02252BF0(ContestGameSpriteGroup *param0, int param1, int param2, int param3, int param4, int param5, int param6, int param7, int param8, fx32 param9);
void contest_competition_02252C78(ContestGameSpriteGroup *param0, int touchScreenRectLeft, int touchScreenRectRight, int touchScreenRectTop, int touchScreenRectBottom, fx32 param5);
void contest_competition_02252C9C(ContestGameSpriteGroup *param0);

#endif // POKEPLATINUM_CONTEST_COMPETITION_02252AB0_H
