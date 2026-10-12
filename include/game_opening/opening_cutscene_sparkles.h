#ifndef POKEPLATINUM_OPENING_CUTSCENE_SPARKLES_H
#define POKEPLATINUM_OPENING_CUTSCENE_SPARKLES_H

#include "game_opening/struct_opening_cutscene_sprite_manager_decl.h"
#include "game_opening/struct_opening_cutscene_sparkle_pool_decl.h"

#include "sprite.h"

OpeningCutsceneSpriteManager *OpeningCutsceneSpriteManager_New(void);
OpeningCutsceneSparklePool *OpeningCutsceneSparklePool_New(const int param0);
void OpeningCutsceneSparklePool_Free(OpeningCutsceneSparklePool *param0);
Sprite **OpeningCutsceneSparklePool_GetSprite(OpeningCutsceneSparklePool *param0, const int param1);
void OpeningCutsceneSpriteManager_Free(OpeningCutsceneSpriteManager *param0);
void OpeningCutsceneSpriteManager_Update(OpeningCutsceneSpriteManager *param0, const int param1);
void OpeningCutsceneSparklePool_StartSpawning(OpeningCutsceneSparklePool *param0, int param1);

#endif // POKEPLATINUM_OPENING_CUTSCENE_SPARKLES_H
