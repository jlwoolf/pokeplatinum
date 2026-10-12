#ifndef POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_SCENE_H
#define POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_SCENE_H

#include "struct_decls/struct_02012744_decl.h"
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
#include "sys_task_manager.h"

typedef struct {
    ContestData *contestData;
    PokemonSpriteManager *pokemonSpriteManager;
    PokemonSprite *pokemonSprites[CONTEST_NUM_PARTICIPANTS];
    SpriteSystem *spriteSystem;
    SpriteManager *spriteManager;
    BgConfig *bgConfig;
    Window windows[9];
    MessageLoader *contestResultsMessages;
    StringTemplate *contestResultsTemplate;
    String *string;
    PaletteData *paletteData;
    FontOAMManager *fontOAMManager;
    PokemonSpriteData pokemonSpriteDataArray[4];
    ContestSpriteGroup spriteGroup;
    SysTask *task;
    ManagedSprite *iconSprites[CONTEST_NUM_PARTICIPANTS];
    ManagedSprite *rankSprites[4];
    ManagedSprite *placementSprites[4][12];
    ManagedSprite *categorySprites[4][12];
    ManagedSprite *scoreSprites[4][12];
    u8 printerID;
} ContestFinalScoringScene;

#endif // POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_SCENE_H
