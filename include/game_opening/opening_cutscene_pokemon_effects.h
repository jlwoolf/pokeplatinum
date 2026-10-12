#ifndef POKEPLATINUM_OPENING_CUTSCENE_POKEMON_EFFECTS_H
#define POKEPLATINUM_OPENING_CUTSCENE_POKEMON_EFFECTS_H

#include "game_opening/struct_opening_cutscene_pokemon_effects_decl.h"

#include "particle_system.h"
#include "spl.h"

const int OpeningCutscenePokemonEffects_GetSize(void);
ParticleSystem *OpeningCutscenePokemonEffects_GetParticleSystem(OpeningCutscenePokemonEffects *param0);
SPLEmitter *OpeningCutscenePokemonEffects_CreateEmitter(OpeningCutscenePokemonEffects *param0, int param1);
void OpeningCutscenePokemonEffects_Init(OpeningCutscenePokemonEffects *param0);
void OpeningCutscenePokemonEffects_Free(OpeningCutscenePokemonEffects *param0);
void OpeningCutscenePokemonEffects_UpdateSprites(OpeningCutscenePokemonEffects *param0);
void OpeningCutscenePokemonEffects_Draw(OpeningCutscenePokemonEffects *param0);
BOOL OpeningCutscenePokemonEffects_RunAnimation(OpeningCutscenePokemonEffects *param0, const u8 param1, const int param2);

#endif // POKEPLATINUM_OPENING_CUTSCENE_POKEMON_EFFECTS_H
