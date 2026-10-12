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
    ContestData *unk_00;
    PokemonSpriteManager *unk_04;
    PokemonSprite *unk_08[4];
    PokemonSprite *unk_18;
    SpriteSystem *unk_1C;
    SpriteManager *unk_20;
    BgConfig *unk_24;
    Window unk_28[1];
    MessageLoader *visualCompetitionMessages;
    StringTemplate *unk_3C;
    String *unk_40;
    PaletteData *unk_44;
    PokemonSpriteData pokemonSpriteDataArray[4];
    ManagedSprite *unk_88[8];
    ContestSpriteGroup unk_A8;
    u8 unk_C4;
} VisualCompetitionScene;

#endif // POKEPLATINUM_STRUCT_VISUAL_COMPETITION_SCENE_H
