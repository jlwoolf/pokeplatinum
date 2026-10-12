#ifndef POKEPLATINUM_OPENING_CUTSCENE_SPRITES_H
#define POKEPLATINUM_OPENING_CUTSCENE_SPRITES_H

#include "game_opening/struct_opening_cutscene_sprites_decl.h"
#include "game_opening/struct_opening_cutscene_sparkle_pool_decl.h"

const int OpeningCutsceneSprites_GetSize(void);
void OpeningCutsceneSprites_Init(OpeningCutsceneSprites *param0);
void OpeningCutsceneSprites_Free(OpeningCutsceneSprites *param0);
void OpeningCutsceneSprites_Create(OpeningCutsceneSprites *param0);
void OpeningCutsceneSprites_CreateForeground(OpeningCutsceneSprites *param0, OpeningCutsceneSparklePool *param1);
void OpeningCutsceneSprites_HideForeground(OpeningCutsceneSprites *param0, OpeningCutsceneSparklePool *param1);
void OpeningCutsceneSprites_Update(OpeningCutsceneSprites *param0);
void OpeningCutsceneSprites_SetVisible(OpeningCutsceneSprites *param0, const u8 param1, const u8 param2);
void OpeningCutsceneSprites_SetAnimate(OpeningCutsceneSprites *param0, const u8 param1);
void OpeningCutsceneSprites_MovePair(OpeningCutsceneSprites *param0);
BOOL OpeningCutsceneSprites_MoveActorLeft(OpeningCutsceneSprites *param0, int param1);
BOOL OpeningCutsceneSprites_MoveActorRight(OpeningCutsceneSprites *param0, int param1);
void OpeningCutsceneSprites_ScrollStripes(OpeningCutsceneSprites *param0, fx32 param1);
void OpeningCutsceneSprites_SetStripePalette(OpeningCutsceneSprites *param0, int param1);
void OpeningCutsceneSprites_RotateStripes(OpeningCutsceneSprites *param0, int param1);
void OpeningCutsceneSprites_MoveTrio(OpeningCutsceneSprites *param0, const int param1);

#endif // POKEPLATINUM_OPENING_CUTSCENE_SPRITES_H
