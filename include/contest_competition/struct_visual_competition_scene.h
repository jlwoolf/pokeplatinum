#ifndef POKEPLATINUM_STRUCT_VISUAL_COMPETITION_SCENE_H
#define POKEPLATINUM_STRUCT_VISUAL_COMPETITION_SCENE_H

#include "struct_defs/struct_02095C48_sub1.h"

#include "battle/pokemon_sprite_data.h"
#include "contest_competition/struct_contest_sprite_group.h"

#include "bg_window.h"
#include "message.h"
#include "palette.h"
#include "pokemon_sprite.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "string_template.h"

typedef struct {
    ContestData *contestData;
    PokemonSpriteManager *pokemonSpriteManager;
    PokemonSprite *pokemonSprites[4];
    PokemonSprite *trainerSprite;
    SpriteSystem *spriteSystem;
    SpriteManager *spriteManager;
    BgConfig *bgConfig;
    Window windows[1];
    MessageLoader *visualCompetitionMessages;
    StringTemplate *stringTemplate;
    String *string;
    PaletteData *paletteData;
    PokemonSpriteData pokemonSpriteDataArray[4];
    ManagedSprite *sprites[8];
    ContestSpriteGroup spriteGroup;
    u8 printerID;
} VisualCompetitionScene;

#endif // POKEPLATINUM_STRUCT_VISUAL_COMPETITION_SCENE_H
