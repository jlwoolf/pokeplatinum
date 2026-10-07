#ifndef POKEPLATINUM_CONTEST_COMPETITION_022413D8_H
#define POKEPLATINUM_CONTEST_COMPETITION_022413D8_H

#include "generated/moves.h"
#include "generated/pokemon_contest_ranks.h"
#include "generated/pokemon_contest_types.h"

#include "contest_competition/struct_contest_competition_0223F88C.h"
#include "contest_competition/struct_contest_competition_0224145C.h"
#include "contest_competition/struct_contest_competition_0224365C.h"
#include "contest_competition/struct_contest_competition_022439C8.h"
#include "contest_competition/struct_contest_competition_022449B8.h"
#include "contest_competition/struct_contest_competition_02246F24.h"
#include "contest_competition/struct_contest_competition_022472F8.h"

#include "contest.h"
#include "narc.h"
#include "palette.h"
#include "sprite_system.h"

enum ActingCompetitionMessagesID {
    ACTING_COMPETITION_MESSAGE_NONE,
    ACTING_COMPETITION_MESSAGE_CHOOSE_JUDGE,
    ACTING_COMPETITION_MESSAGE_WHICH_MOVE_IS_YOUR_CHOICE,
    ACTING_COMPETITION_MESSAGE_LAST_PERFORMANCE_CHOOSE_MOVE,
    ACTING_COMPETITION_MESSAGE_TO_JUDGE_MON_PERFORMED_MOVE,
    ACTING_COMPETITION_MESSAGE_SOMEONE_ALREADY_PERFORMED_FOR_JUDGE,
    ACTING_COMPETITION_MESSAGE_EMPTY1,
    ACTING_COMPETITION_MESSAGE_JUDGE_STRONGLY_IMPRESSED, // two mon performed for judge, +2
    ACTING_COMPETITION_MESSAGE_JUDGE_WAS_IMPRESSED, // three mon performed for judge, +1
    ACTING_COMPETITION_MESSAGE_EVERYONE_PERFORMED_FOR_SAME_JUDGE, // four mon performed for judge, +0
    ACTING_COMPETITION_MESSAGE_JUDGE_VERY_IMPRESSED, // one mon performed for judge, +3
    ACTING_COMPETITION_MESSAGE_EMPTY2,
    ACTING_COMPETITION_MESSAGE_COOL_MOVE_VOLTAGE_UP,
    ACTING_COMPETITION_MESSAGE_BEAUTY_MOVE_VOLTAGE_UP,
    ACTING_COMPETITION_MESSAGE_CUTE_MOVE_VOLTAGE_UP,
    ACTING_COMPETITION_MESSAGE_SMART_MOVE_VOLTAGE_UP,
    ACTING_COMPETITION_MESSAGE_TOUGH_MOVE_VOLTAGE_UP,
    ACTING_COMPETITION_MESSAGE_EMPTY3,
    ACTING_COMPETITION_MESSAGE_COOL_MOVE_VOLTAGE_DOWN,
    ACTING_COMPETITION_MESSAGE_BEAUTY_MOVE_VOLTAGE_DOWN,
    ACTING_COMPETITION_MESSAGE_CUTE_MOVE_VOLTAGE_DOWN,
    ACTING_COMPETITION_MESSAGE_SMART_MOVE_VOLTAGE_DOWN,
    ACTING_COMPETITION_MESSAGE_TOUGH_MOVE_VOLTAGE_DOWN,
    ACTING_COMPETITION_MESSAGE_EMPTY4,
    ACTING_COMPETITION_MESSAGE_EMPTY5,
    ACTING_COMPETITION_MESSAGE_AUDIENCE_IS_PRETTY_EXCITED,
    ACTING_COMPETITION_MESSAGE_AUDIENCE_IS_GOING_WILD,
    ACTING_COMPETITION_MESSAGE_EMPTY6,
    ACTING_COMPETITION_MESSAGE_EMPTY7,
    ACTING_COMPETITION_MESSAGE_EMPTY8,
    ACTING_COMPETITION_MESSAGE_EMPTY9,
    ACTING_COMPETITION_MESSAGE_MON_DIDNT_STAND_OUT,
    ACTING_COMPETITION_MESSAGE_MON_ATTRACTED_LITTLE_ATTENTION,
    ACTING_COMPETITION_MESSAGE_MON_ATTRACTED_DECENT_ATTENTION,
    ACTING_COMPETITION_MESSAGE_MON_ATTRACTED_A_LOT_OF_ATTENTION,
    ACTING_COMPETITION_MESSAGE_MON_COMMANDED_TOTAL_ATTENTION,
    ACTING_COMPETITION_MESSAGE_TIME_FOR_CUTE_ACTING_COMPETITION,
    ACTING_COMPETITION_MESSAGE_EMPTY10,
    ACTING_COMPETITION_MESSAGE_TIME_FOR_SMART_ACTING_COMPETITION,
    ACTING_COMPETITION_MESSAGE_TIME_FOR_TOUGH_ACTING_COMPETITION,
    ACTING_COMPETITION_MESSAGE_TIME_FOR_BEAUTY_ACTING_COMPETITION,
    ACTING_COMPETITION_MESSAGE_TIME_FOR_COOL_ACTING_COMPETITION,
    ACTING_COMPETITION_MESSAGE_NEXT_TURN_LOWEST_SCORING_PERFORM_FIRST,
    ACTING_COMPETITION_MESSAGE_JUDGING_IS_OVER,
    ACTING_COMPETITION_MESSAGE_EMPTY11,
    ACTING_COMPETITION_MESSAGE_BEGIN_PRACTICE,
    ACTING_COMPETITION_MESSAGE_COMMUNICATING_PLEASE_STAND_BY,
    ACTING_COMPETITION_MESSAGE_MAX,
};

void contest_competition_022413D8(void);
void contest_competition_022413E4(UnkStruct_contest_competition_02246F24 *param0, int param1, int param2);
void contest_competition_02241428(UnkStruct_contest_competition_02246F24 *param0);
UnkStruct_contest_competition_0224145C *contest_competition_0224145C(UnkStruct_contest_competition_02246F24 *param0, int param1);
void contest_competition_02241494(UnkStruct_contest_competition_0224145C *param0);
void contest_competition_022414B0(UnkStruct_contest_competition_0224145C *param0);
BOOL contest_competition_022414BC(UnkStruct_contest_competition_0224145C *param0);
void contest_competition_02241524(UnkStruct_contest_competition_0223F88C *param0, int contestantID);
void contest_competition_022415E4(UnkStruct_contest_competition_0223F88C *param0);
void contest_competition_022416E4(UnkStruct_contest_competition_0223F88C *param0);
void contest_competition_02241928(UnkStruct_contest_competition_0223F88C *param0, Contest *param1, NARC *param2);
void contest_competition_0224197C(UnkStruct_contest_competition_0223F88C *param0);
void contest_competition_022419AC(PaletteData *param0, SpriteSystem *param1, SpriteManager *param2, NARC *param3);
void contest_competition_02241A00(SpriteManager *param0);
void contest_competition_02241A24(UnkStruct_contest_competition_0223F88C *param0);
void contest_competition_02241A64(UnkStruct_contest_competition_0223F88C *param0);
void contest_competition_02241A8C(UnkStruct_contest_competition_0223F88C *param0, int param1, int param2);
void contest_competition_02241B1C(UnkStruct_contest_competition_0223F88C *param0);
void contest_competition_02241B3C(UnkStruct_contest_competition_02246F24 *param0, int param1, int param2, u8 *param3);
void contest_competition_02241D94(UnkStruct_contest_competition_0223F88C *param0, int param1, NARC *param2);
void contest_competition_02241E24(UnkStruct_contest_competition_0223F88C *param0);
void contest_competition_02241E58(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_02241EA4(SpriteManager *param0);
void contest_competition_02241EF0(UnkStruct_contest_competition_0223F88C *param0);
void contest_competition_02241F34(UnkStruct_contest_competition_0223F88C *param0, int param1, int param2, int param3);
void contest_competition_02242154(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_022421E0(SpriteManager *param0);
void contest_competition_02242248(UnkStruct_contest_competition_0223F88C *param0);
BOOL contest_competition_022424A8(UnkStruct_contest_competition_0223F88C *param0, int param1);
void contest_competition_022424D4(UnkStruct_contest_competition_0223F88C *param0, int param1, int param2);
void contest_competition_022426E8(UnkStruct_contest_competition_02246F24 *param0, int param1, u8 *param2);
void contest_competition_02242DA8(UnkStruct_contest_competition_02246F24 *param0);
void contest_competition_02242E5C(UnkStruct_contest_competition_02246F24 *param0, enum ActingCompetitionMessagesID actingMessagesID, const UnkStruct_contest_competition_022449B8 *param2, const void *param3);
void contest_competition_02242E9C(UnkStruct_contest_competition_02246F24 *param0, int contestMoveEffect, int param2, const UnkStruct_contest_competition_022449B8 *param3, const void *param4);
int contest_competition_02242ECC(UnkStruct_contest_competition_02246F24 *param0);
void contest_competition_02242EE4(UnkStruct_contest_competition_02246F24 *param0, int param1);
void contest_competition_02242FA4(UnkStruct_contest_competition_02246F24 *param0);
void contest_competition_02242FC0(UnkStruct_contest_competition_02246F24 *param0);
void contest_competition_02242FE8(UnkStruct_contest_competition_02246F24 *param0);
void contest_competition_02243040(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224308C(SpriteManager *param0);
void contest_competition_022430AC(UnkStruct_contest_competition_0223F88C *param0, int param1, int param2);
void contest_competition_022430F8(UnkStruct_contest_competition_0223F88C *param0);
void contest_competition_02243120(UnkStruct_contest_competition_02246F24 *param0, UnkStruct_contest_competition_022449B8 *param1, int contestantID);
u32 contest_competition_0224314C(int param0, int param1, UnkStruct_contest_competition_022449B8 *param2);
int contest_competition_02243174(int param0);
void contest_competition_022431A0(UnkStruct_contest_competition_02246F24 *param0, int param1, u8 param2, int param3, int param4, u8 *param5);
void contest_competition_0224331C(UnkStruct_contest_competition_02246F24 *param0, int param1, int param2, u8 *param3, UnkStruct_contest_competition_0224145C *param4);
UnkStruct_contest_competition_0224365C *contest_competition_0224365C(UnkStruct_contest_competition_02246F24 *param0, int param1);
void contest_competition_02243690(UnkStruct_contest_competition_0224365C *param0);
void contest_competition_022436D0(UnkStruct_contest_competition_02246F24 *param0, int param1, int param2, int param3, u8 *param4);
u32 Contest_GetActingCompetitionMessageIntroAnnouncement(enum PokemonContestType contestType);
u32 Contest_GetActingCompetitionMessageGoodMoveType(enum PokemonContestType contestType);
u32 Contest_GetActingCompetitionMessageBadMoveType(enum PokemonContestType contestType);
void contest_competition_022439C8(Contest *param0, int contestantID, enum Move moveID, UnkStruct_contest_competition_022439C8 *param3);
BOOL contest_competition_02243A98(UnkStruct_contest_competition_022472F8 *param0, int contestantID, int moveID);

#endif // POKEPLATINUM_CONTEST_COMPETITION_022413D8_H
