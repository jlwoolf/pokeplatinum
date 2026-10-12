#ifndef POKEPLATINUM_STRUCT_DANCE_COMPETITION_SCENE_H
#define POKEPLATINUM_STRUCT_DANCE_COMPETITION_SCENE_H

#include "struct_decls/struct_02012744_decl.h"
#include "struct_defs/struct_02095C48_sub1.h"

#include "battle/pokemon_sprite_data.h"
#include "contest_competition/struct_contest_text_label.h"
#include "contest_competition/struct_dance_contestant_slot_task.h"
#include "contest_competition/struct_dance_sprite_task.h"
#include "contest_competition/struct_dance_move_icon_task.h"
#include "contest_competition/struct_dance_note_task.h"
#include "contest_competition/struct_dance_score_task.h"
#include "contest_competition/struct_dance_photo_sprite.h"
#include "contest_competition/struct_dance_combo_task.h"
#include "contest_competition/struct_dance_beat_task.h"
#include "contest_competition/struct_dance_move_definition.h"

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
    DancePhotoSprite unk_04[4];
    PokemonSpriteManager *unk_44;
    PokemonSprite *unk_48[4];
    SpriteSystem *unk_58;
    SpriteManager *unk_5C;
    BgConfig *unk_60;
    Window unk_64[2];
    MessageLoader *danceMessageLoader;
    StringTemplate *unk_88;
    String *danceMessage;
    PaletteData *unk_90;
    FontOAMManager *unk_94;
    PokemonSpriteData pokemonSpriteDataArray[4];
    ManagedSprite *unk_D8[68];
    ManagedSprite *unk_1E8;
    SysTask *unk_1EC;
    DanceBeatTask unk_1F0;
    DanceComboTask *unk_1FC;
    DanceMoveIconTask unk_200[CONTEST_NUM_PARTICIPANTS];
    DanceContestantSlotTask unk_254[4];
    DanceNoteTask unk_290[4][16];
    DanceScoreTask unk_910;
    DanceSpriteTask unk_92C[3];
    ManagedSprite *unk_960[3];
    ContestTextLabel unk_96C[3][3];
    const DanceMoveDefinition *unk_A10;
    u8 unk_A14[4];
    u8 unk_A18;
    u8 unk_A19[4];
    u8 unk_A1D[4];
    u8 unk_A21[4];
    u8 unk_A25;
    u8 unk_A26;
    u8 unk_A27;
    u8 unk_A28[4];
    u8 unk_A2C;
} DanceCompetitionScene;

#endif // POKEPLATINUM_STRUCT_DANCE_COMPETITION_SCENE_H
