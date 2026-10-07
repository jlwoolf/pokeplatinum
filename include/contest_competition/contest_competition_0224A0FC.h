#ifndef POKEPLATINUM_CONTEST_COMPETITION_0224A0FC_H
#define POKEPLATINUM_CONTEST_COMPETITION_0224A0FC_H

#include <nitro/gx.h>

#include "generated/pokemon_contest_ranks.h"
#include "generated/pokemon_contest_types.h"

#include "contest_competition/struct_contest_competition_0224A1EC.h"
#include "contest_competition/struct_contest_competition_0224ABFC.h"
#include "contest_competition/struct_contest_competition_0224B058.h"
#include "contest_competition/struct_contest_competition_0224B09C.h"
#include "contest_competition/struct_contest_competition_0224C0C0.h"
#include "contest_competition/struct_contest_competition_0224C384.h"
#include "contest_competition/struct_contest_competition_0224DF54.h"
#include "contest_competition/struct_contest_competition_0224EDE0.h"
#include "contest_competition/struct_contest_competition_02253084.h"

#include "narc.h"
#include "pokemon_sprite.h"
#include "sprite_system.h"

s16 contest_competition_0224A0FC(int contestantID);
s16 contest_competition_0224A10C(int contestantID);
s16 contest_competition_0224A120(int contestantID);
void contest_competition_0224A134(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224A1EC(UnkStruct_contest_competition_0224A1EC *param0);
void contest_competition_0224A20C(SpriteSystem *param0, SpriteManager *param1);
void contest_competition_0224A210(SpriteManager *param0);
void contest_competition_0224A214(UnkStruct_contest_competition_0224A1EC *param0, int param1, int param2);
void contest_competition_0224A368(UnkStruct_contest_competition_0224A1EC *param0, int param1, int param2, int param3);
void contest_competition_0224A390(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224A428(SpriteManager *param0);
void contest_competition_0224A580(UnkStruct_contest_competition_0224A1EC *param0);
void contest_competition_0224A5A8(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224A5F8(SpriteManager *param0);
void contest_competition_0224A61C(UnkStruct_contest_competition_0224A1EC *param0, SpriteSystem *param1, SpriteManager *param2);
void contest_competition_0224A650(UnkStruct_contest_competition_0224A1EC *param0);
void contest_competition_0224A674(UnkStruct_contest_competition_0224A1EC *param0);
void contest_competition_0224A7B8(UnkStruct_contest_competition_0224A1EC *param0);
void contest_competition_0224A7E0(UnkStruct_contest_competition_0224A1EC *param0, SpriteSystem *param1, SpriteManager *param2, int param3, int param4, u8 param5);
void contest_competition_0224A95C(UnkStruct_contest_competition_0224A1EC *param0);
void contest_competition_0224A984(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224A9D4(SpriteManager *param0);
void contest_competition_0224A9F8(UnkStruct_contest_competition_0224A1EC *param0, SpriteSystem *param1, SpriteManager *param2);
void contest_competition_0224AA1C(UnkStruct_contest_competition_0224A1EC *param0);
void contest_competition_0224AA38(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224AA58(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224AA94(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224AAE4(SpriteManager *param0);
void contest_competition_0224AB08(UnkStruct_contest_competition_0224A1EC *param0, SpriteSystem *param1, SpriteManager *param2);
void contest_competition_0224ABB0(UnkStruct_contest_competition_0224A1EC *param0);
void contest_competition_0224ABDC(UnkStruct_contest_competition_0224A1EC *param0, int param1);
void contest_competition_0224AC78(UnkStruct_contest_competition_0224ABFC *param0, int param1, int param2);
void contest_competition_0224AC80(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224ACD0(SpriteManager *param0);
void contest_competition_0224ACF4(UnkStruct_contest_competition_0224A1EC *param0, SpriteSystem *param1, SpriteManager *param2);
void contest_competition_0224ACF8(UnkStruct_contest_competition_0224A1EC *param0);
void contest_competition_0224ACFC(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224AD4C(SpriteManager *param0);
BOOL contest_competition_0224AD70(UnkStruct_contest_competition_0224DF54 *param0, int param1, int param2);
void contest_competition_0224AFA8(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224AFF8(SpriteManager *param0);
BOOL contest_competition_0224B01C(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224B058(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224B068(UnkStruct_contest_competition_0224A1EC *param0, int param1);
void contest_competition_0224B09C(PokemonSprite *param0, UnkStruct_contest_competition_0224B09C *param1);
void contest_competition_0224B0CC(UnkStruct_contest_competition_0224A1EC *param0);
void contest_competition_0224B20C(UnkStruct_contest_competition_0224DF54 *param0, const UnkStruct_contest_competition_0224EDE0 *param1);
void contest_competition_0224B59C(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224B5B8(UnkStruct_contest_competition_0224DF54 *param0);
BOOL contest_competition_0224B5C8(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224BC4C(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224BC68(UnkStruct_contest_competition_0224DF54 *param0, int param1, int param2);
void contest_competition_0224BD00(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224BD28(UnkStruct_contest_competition_0224DF54 *param0, int param1, int param2);
int contest_competition_0224BDF0(UnkStruct_contest_competition_0224DF54 *param0, int param1);
int contest_competition_0224BE24(UnkStruct_contest_competition_0224DF54 *param0, int param1);
void contest_competition_0224C2CC(UnkStruct_contest_competition_0224DF54 *param0, u32 param1, const UnkStruct_contest_competition_0224C0C0 *param2);
int contest_competition_0224C300(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224C310(SpriteSystem *param0, SpriteManager *param1, NARC *param2);
void contest_competition_0224C360(SpriteManager *param0);
void contest_competition_0224C384(UnkStruct_contest_competition_0224DF54 *param0, SpriteSystem *param1, SpriteManager *param2);
void contest_competition_0224C3E4(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224C434(UnkStruct_contest_competition_0224B058 *param0, u32 param1, u32 param2, int param3);
void contest_competition_0224C47C(UnkStruct_contest_competition_0224B058 *param0, int param1);
void contest_competition_0224C49C(UnkStruct_contest_competition_0224C384 *param0, u32 param1, u32 param2, int param3);
void contest_competition_0224C540(UnkStruct_contest_competition_0224C384 *param0);
void contest_competition_0224C54C(UnkStruct_contest_competition_0224C384 *param0, int param1);
int contest_competition_0224C57C(enum PokemonContestRank contestRank);
void contest_competition_0224C5A0(UnkStruct_contest_competition_0224DF54 *param0, u32 param1, const UnkStruct_contest_competition_0224C0C0 *param2);
void contest_competition_0224C640(UnkStruct_contest_competition_0224DF54 *param0);
s64 contest_competition_0224C660(UnkStruct_contest_competition_0224DF54 *param0, const UnkStruct_contest_competition_02253084 *param1, int param2);
s64 contest_competition_0224C6A8(UnkStruct_contest_competition_0224DF54 *param0, const UnkStruct_contest_competition_02253084 *param1, int param2);
void contest_competition_0224C6B0(UnkStruct_contest_competition_0224DF54 *param0, int param1, u8 *param2);
void contest_competition_0224C848(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224C84C(void);
void contest_competition_0224C864(UnkStruct_contest_competition_0224DF54 *param0, int param1);
void contest_competition_0224C8E8(UnkStruct_contest_competition_0224DF54 *param0, u32 param1);
void contest_competition_0224C9A4(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224C9D4(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224C9F0(UnkStruct_contest_competition_0224DF54 *param0, int param1);
void contest_competition_0224CA90(UnkStruct_contest_competition_0224DF54 *param0, u32 param1, s32 param2, s32 param3, s32 param4, fx32 param5);
void contest_competition_0224CD84(UnkStruct_contest_competition_0224DF54 *param0, u32 param1, u32 param2, int param3, int param4, u16 param5);
void contest_competition_0224CDB4(UnkStruct_contest_competition_0224DF54 *param0, int param1);
void contest_competition_0224CDC0(UnkStruct_contest_competition_0224DF54 *param0, int param1, int param2);
void contest_competition_0224CE08(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224CE28(UnkStruct_contest_competition_0224DF54 *param0);
void contest_competition_0224CEE4(UnkStruct_contest_competition_0224DF54 *param0, int param1, GXRgb param2, GXRgb param3, int param4, int param5, u8 *param6);
BOOL contest_competition_0224CFA8(u32 param0);

#endif // POKEPLATINUM_CONTEST_COMPETITION_0224A0FC_H
