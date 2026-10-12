#ifndef POKEPLATINUM_CONTEST_COMPETITION_0224A0FC_H
#define POKEPLATINUM_CONTEST_COMPETITION_0224A0FC_H

#include <nitro/gx.h>

#include "generated/pokemon_contest_ranks.h"
#include "generated/pokemon_contest_types.h"

#include "contest_competition/struct_dance_competition_scene.h"
#include "contest_competition/struct_dance_move_icon_task.h"
#include "contest_competition/struct_dance_score_task.h"
#include "contest_competition/struct_dance_photo_sprite.h"
#include "contest_competition/struct_dance_message_args.h"
#include "contest_competition/struct_dance_combo_task.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_dance_packet.h"
#include "contest_competition/struct_dance_move_definition.h"

#include "narc.h"
#include "pokemon_sprite.h"
#include "sprite_system.h"

s16 contest_competition_0224A0FC(int contestantID);
s16 contest_competition_0224A10C(int contestantID);
s16 contest_competition_0224A120(int contestantID);
void contest_competition_0224A134(DanceCompetition *param0);
void contest_competition_0224A1EC(DanceCompetitionScene *param0);
void contest_competition_0224A20C(SpriteSystem *param0, SpriteManager *param1);
void contest_competition_0224A210(SpriteManager *param0);
void contest_competition_0224A214(DanceCompetitionScene *param0, int param1, int param2);
void contest_competition_0224A368(DanceCompetitionScene *param0, int param1, int param2, int param3);
void contest_competition_0224A390(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224A428(SpriteManager *param0);
void contest_competition_0224A580(DanceCompetitionScene *param0);
void contest_competition_0224A5A8(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224A5F8(SpriteManager *param0);
void contest_competition_0224A61C(DanceCompetitionScene *param0, SpriteSystem *param1, SpriteManager *param2);
void contest_competition_0224A650(DanceCompetitionScene *param0);
void contest_competition_0224A674(DanceCompetitionScene *param0);
void contest_competition_0224A7B8(DanceCompetitionScene *param0);
void contest_competition_0224A7E0(DanceCompetitionScene *param0, SpriteSystem *param1, SpriteManager *param2, int param3, int param4, u8 param5);
void contest_competition_0224A95C(DanceCompetitionScene *param0);
void contest_competition_0224A984(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224A9D4(SpriteManager *param0);
void contest_competition_0224A9F8(DanceCompetitionScene *param0, SpriteSystem *param1, SpriteManager *param2);
void contest_competition_0224AA1C(DanceCompetitionScene *param0);
void contest_competition_0224AA38(DanceCompetition *param0);
void contest_competition_0224AA58(DanceCompetition *param0);
void contest_competition_0224AA94(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224AAE4(SpriteManager *param0);
void contest_competition_0224AB08(DanceCompetitionScene *param0, SpriteSystem *param1, SpriteManager *param2);
void contest_competition_0224ABB0(DanceCompetitionScene *param0);
void contest_competition_0224ABDC(DanceCompetitionScene *param0, int param1);
void contest_competition_0224AC78(DanceMoveIconTask *param0, int param1, int param2);
void contest_competition_0224AC80(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224ACD0(SpriteManager *param0);
void contest_competition_0224ACF4(DanceCompetitionScene *param0, SpriteSystem *param1, SpriteManager *param2);
void contest_competition_0224ACF8(DanceCompetitionScene *param0);
void contest_competition_0224ACFC(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224AD4C(SpriteManager *param0);
BOOL contest_competition_0224AD70(DanceCompetition *param0, int param1, int param2);
void contest_competition_0224AFA8(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224AFF8(SpriteManager *param0);
BOOL contest_competition_0224B01C(DanceCompetition *param0);
void contest_competition_0224B058(DanceCompetition *param0);
void contest_competition_0224B068(DanceCompetitionScene *param0, int param1);
void contest_competition_0224B09C(PokemonSprite *param0, DancePhotoSprite *param1);
void contest_competition_0224B0CC(DanceCompetitionScene *param0);
void contest_competition_0224B20C(DanceCompetition *param0, const DancePacket *param1);
void contest_competition_0224B59C(DanceCompetition *param0);
void contest_competition_0224B5B8(DanceCompetition *param0);
BOOL contest_competition_0224B5C8(DanceCompetition *param0);
void contest_competition_0224BC4C(DanceCompetition *param0);
void contest_competition_0224BC68(DanceCompetition *param0, int param1, int param2);
void contest_competition_0224BD00(DanceCompetition *param0);
void contest_competition_0224BD28(DanceCompetition *param0, int param1, int param2);
int contest_competition_0224BDF0(DanceCompetition *param0, int param1);
int contest_competition_0224BE24(DanceCompetition *param0, int param1);
void contest_competition_0224C2CC(DanceCompetition *param0, u32 param1, const DanceMessageArgs *param2);
int contest_competition_0224C300(DanceCompetition *param0);
void contest_competition_0224C310(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224C360(SpriteManager *param0);
void contest_competition_0224C384(DanceCompetition *param0, SpriteSystem *param1, SpriteManager *param2);
void contest_competition_0224C3E4(DanceCompetition *param0);
void contest_competition_0224C434(DanceScoreTask *param0, u32 param1, u32 param2, int param3);
void contest_competition_0224C47C(DanceScoreTask *param0, int param1);
void contest_competition_0224C49C(DanceComboTask *param0, u32 param1, u32 param2, int param3);
void contest_competition_0224C540(DanceComboTask *param0);
void contest_competition_0224C54C(DanceComboTask *param0, int param1);
int contest_competition_0224C57C(enum PokemonContestRank contestRank);
void contest_competition_0224C5A0(DanceCompetition *param0, u32 param1, const DanceMessageArgs *param2);
void contest_competition_0224C640(DanceCompetition *param0);
s64 contest_competition_0224C660(DanceCompetition *param0, const DanceMoveDefinition *param1, int param2);
s64 contest_competition_0224C6A8(DanceCompetition *param0, const DanceMoveDefinition *param1, int param2);
void contest_competition_0224C6B0(DanceCompetition *param0, int param1, u8 *param2);
void contest_competition_0224C848(DanceCompetition *param0);
void contest_competition_0224C84C(void);
void contest_competition_0224C864(DanceCompetition *param0, int param1);
void contest_competition_0224C8E8(DanceCompetition *param0, u32 param1);
void contest_competition_0224C9A4(DanceCompetition *param0);
void contest_competition_0224C9D4(DanceCompetition *param0);
void contest_competition_0224C9F0(DanceCompetition *param0, int param1);
void contest_competition_0224CA90(DanceCompetition *param0, u32 param1, s32 param2, s32 param3, s32 param4, fx32 param5);
void contest_competition_0224CD84(DanceCompetition *param0, u32 param1, u32 param2, int param3, int param4, u16 param5);
void contest_competition_0224CDB4(DanceCompetition *param0, int param1);
void contest_competition_0224CDC0(DanceCompetition *param0, int param1, int param2);
void contest_competition_0224CE08(DanceCompetition *param0);
void contest_competition_0224CE28(DanceCompetition *param0);
void contest_competition_0224CEE4(DanceCompetition *param0, int param1, GXRgb param2, GXRgb param3, int param4, int param5, u8 *param6);
BOOL contest_competition_0224CFA8(u32 param0);

#endif // POKEPLATINUM_CONTEST_COMPETITION_0224A0FC_H
