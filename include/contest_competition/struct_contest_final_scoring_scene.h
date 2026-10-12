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
    ContestData *unk_00;
    PokemonSpriteManager *unk_04;
    PokemonSprite *unk_08[CONTEST_NUM_PARTICIPANTS];
    SpriteSystem *unk_18;
    SpriteManager *unk_1C;
    BgConfig *unk_20;
    Window unk_24[9];
    MessageLoader *contestResultsMessages;
    StringTemplate *contestResultsTemplate;
    String *unk_BC;
    PaletteData *unk_C0;
    FontOAMManager *unk_C4;
    PokemonSpriteData pokemonSpriteDataArray[4];
    ContestSpriteGroup unk_108;
    SysTask *unk_124;
    ManagedSprite *unk_128[CONTEST_NUM_PARTICIPANTS];
    ManagedSprite *unk_138[4];
    ManagedSprite *unk_148[4][12];
    ManagedSprite *unk_208[4][12];
    ManagedSprite *unk_2C8[4][12];
    u8 unk_388;
} ContestFinalScoringScene;

#endif // POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_SCENE_H
