#ifndef POKEPLATINUM_STRUCT_ACTING_COMPETITION_SCENE_H
#define POKEPLATINUM_STRUCT_ACTING_COMPETITION_SCENE_H

#include "struct_decls/struct_02012744_decl.h"
#include "struct_defs/struct_02095C48_sub1.h"

#include "battle/pokemon_sprite_data.h"
#include "battle_anim/battle_anim_system.h"
#include "contest_competition/struct_contest_text_label.h"

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
    PokemonSprite *pokemonSprites[CONTEST_NUM_PARTICIPANTS];
    SpriteSystem *spriteSystem;
    SpriteManager *spriteManager;
    BattleAnimSystem *battleAnimSystem;
    BgConfig *bgConfig;
    Window windows[1];
    MessageLoader *contestTextMessageLoader;
    MessageLoader *contestOpponentNames;
    MessageLoader *contestEffectMessages;
    MessageLoader *contestActingCompetitionMessages;
    StringTemplate *stringTemplate;
    String *string;
    PaletteData *paletteData;
    FontOAMManager *fontOAMManager;
    PokemonSpriteData pokemonSpriteDataArray[CONTEST_NUM_PARTICIPANTS];
    PokemonSpriteData pokemonSpriteData;
    ManagedSprite *scoreGaugeSprites[3];
    ManagedSprite *judgeSprites[3];
    ManagedSprite *cursorSprite;
    ManagedSprite *moveIconSprites[4][6];
    ManagedSprite *moveEffectSprites[3][5];
    ManagedSprite *contestantSprites[4];
    ManagedSprite *judgeFaceSprites[3];
    ManagedSprite *voltageGaugeSprite;
    ContestTextLabel trainerNameLabels[CONTEST_NUM_PARTICIPANTS];
    ContestTextLabel contestantNameLabels[CONTEST_NUM_PARTICIPANTS];
    u8 printerID;
} ActingCompetitionScene;

#endif // POKEPLATINUM_STRUCT_ACTING_COMPETITION_SCENE_H
