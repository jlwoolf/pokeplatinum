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
    ContestData *contestData;
    DancePhotoSprite photoSprites[4];
    PokemonSpriteManager *pokemonSpriteManager;
    PokemonSprite *pokemonSprites[4];
    SpriteSystem *spriteSystem;
    SpriteManager *spriteManager;
    BgConfig *bgConfig;
    Window windows[2];
    MessageLoader *danceMessageLoader;
    StringTemplate *stringTemplate;
    String *danceMessage;
    PaletteData *paletteData;
    FontOAMManager *fontOAMManager;
    PokemonSpriteData pokemonSpriteDataArray[4];
    ManagedSprite *sprites[68];
    ManagedSprite *comboSprite;
    SysTask *task;
    DanceBeatTask beatTask;
    DanceComboTask *comboTask;
    DanceMoveIconTask moveIconTasks[CONTEST_NUM_PARTICIPANTS];
    DanceContestantSlotTask slotTasks[4];
    DanceNoteTask noteTasks[4][16];
    DanceScoreTask scoreTask;
    DanceSpriteTask spriteTasks[3];
    ManagedSprite *judgeSprites[3];
    ContestTextLabel textLabels[3][3];
    const DanceMoveDefinition *moveDefinitions;
    u8 contestantIsHuman[4];
    u8 printerID;
    u8 comboCount[4];
    u8 noteCount[4];
    u8 missCount[4];
    u8 perfectCount;
    u8 goodCount;
    u8 badCount;
    u8 hitCount[4];
    u8 playerContestantID;
} DanceCompetitionScene;

#endif // POKEPLATINUM_STRUCT_DANCE_COMPETITION_SCENE_H
