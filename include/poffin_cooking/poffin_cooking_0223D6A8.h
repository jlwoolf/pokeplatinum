#ifndef POKEPLATINUM_POFFIN_COOKING_0223D6A8_H
#define POKEPLATINUM_POFFIN_COOKING_0223D6A8_H

#include <nitro/fx/fx.h>

#include "poffin_cooking/struct_poffin_cooking_comm_decl.h"
#include "poffin_cooking/struct_poffin_cooking_sprite_manager.h"
#include "poffin_cooking/struct_poffin_cooking_sprite_set.h"
#include "poffin_cooking/struct_poffin_cooking_scale_anim.h"
#include "poffin_cooking/struct_poffin_cooking_motion_anim.h"
#include "poffin_cooking/struct_poffin_cooking_poffin_anim.h"
#include "poffin_cooking/struct_poffin_cooking_berry_packet.h"
#include "poffin_cooking/struct_poffin_cooking_messages.h"
#include "poffin_cooking/struct_poffin_cooking_player_list_display.h"
#include "poffin_cooking/struct_poffin_cooking_reaction_sprite.h"
#include "poffin_cooking/struct_poffin_cooking_burst_effect.h"
#include "poffin_cooking/struct_poffin_cooking_player_cursor.h"
#include "poffin_cooking/struct_poffin_cooking_message_box.h"
#include "poffin_cooking/struct_poffin_cooking_particle_manager.h"
#include "poffin_cooking/struct_poffin_cooking_arrow_manager.h"
#include "poffin_cooking/struct_poffin_cooking_sparkle_manager.h"
#include "poffin_cooking/struct_poffin_cooking_poffin_sprite.h"
#include "poffin_cooking/struct_poffin_cooking_yes_no_menu.h"
#include "poffin_cooking/struct_poffin_cooking_session.h"

#include "bg_window.h"
#include "narc.h"
#include "software_sprite.h"
#include "sprite.h"
#include "sprite_resource.h"

void poffin_cooking_0223D754(PoffinCookingSpriteManager *param0, int param1, int param2, enum HeapID heapID);
void poffin_cooking_0223D784(PoffinCookingSpriteManager *param0);
void poffin_cooking_0223D7A8(PoffinCookingSpriteManager *param0, PoffinCookingSpriteSet *param1, NARC *param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9);
void poffin_cooking_0223D894(PoffinCookingSpriteManager *param0, PoffinCookingSpriteSet *param1, NARC *param2, SpriteResource *param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8);
void poffin_cooking_0223D95C(PoffinCookingSpriteManager *param0, PoffinCookingSpriteSet *param1);
Sprite *poffin_cooking_0223D9A8(PoffinCookingSpriteManager *param0, PoffinCookingSpriteSet *param1, fx32 param2, fx32 param3, fx32 param4, int param5, int param6);
void poffin_cooking_0223D9DC(PoffinCookingScaleAnim *param0, fx32 param1, fx32 param2, int param3);
BOOL poffin_cooking_0223D9EC(PoffinCookingScaleAnim *param0);
void poffin_cooking_0223DA34(PoffinCookingMotionAnim *param0, fx32 param1, fx32 param2, fx32 param3, int param4);
BOOL poffin_cooking_0223DA94(PoffinCookingMotionAnim *param0);
VecFx32 poffin_cooking_0223DAFC(fx32 param0, fx32 param1, fx32 param2);
void poffin_cooking_0223DB18(PoffinCookingPoffinAnim *param0, int param1);
void poffin_cooking_0223DB30(PoffinCookingPoffinAnim *param0);
void poffin_cooking_0223DB4C(PoffinCookingPoffinAnim *param0, PoffinCookingBerryPacket *param1, PoffinCookingSpriteManager *param2, PoffinCookingSpriteSet *param3, u32 param4);
void poffin_cooking_0223DC1C(PoffinCookingPoffinAnim *param0, PoffinCookingSpriteManager *param1);
void poffin_cooking_0223DC68(PoffinCookingPoffinAnim *param0);
u32 poffin_cooking_0223DD30(PoffinCookingPoffinAnim *param0);
void poffin_cooking_0223DEA0(PoffinCookingPlayerListDisplay *param0, int param1, PoffinCookingMessages *param2, PoffinCookingSession *param3, int param4, u32 param5);
void poffin_cooking_0223DEC4(PoffinCookingPlayerListDisplay *param0);
void poffin_cooking_0223DEE0(PoffinCookingPlayerListDisplay *param0, BgConfig *param1, u32 heapID, NARC *param3);
void poffin_cooking_0223DF10(PoffinCookingPlayerListDisplay *param0);
void poffin_cooking_0223DF30(PoffinCookingPlayerListDisplay *param0, int param1);
void poffin_cooking_0223DF70(PoffinCookingPlayerListDisplay *param0);
void poffin_cooking_0223DF84(PoffinCookingPlayerListDisplay *param0);
void poffin_cooking_0223DFAC(PoffinCookingPlayerListDisplay *param0);
void poffin_cooking_0223E244(PoffinCookingReactionSprite *param0);
void poffin_cooking_0223E260(PoffinCookingReactionSprite *param0);
void poffin_cooking_0223E28C(PoffinCookingReactionSprite *param0, PoffinCookingSpriteManager *param1, PoffinCookingSpriteSet *param2, u32 param3, u32 param4, u32 param5);
void poffin_cooking_0223E2C8(PoffinCookingReactionSprite *param0);
void poffin_cooking_0223E2E4(PoffinCookingReactionSprite *param0);
void poffin_cooking_0223E2FC(PoffinCookingReactionSprite *param0);
BOOL poffin_cooking_0223E32C(PoffinCookingReactionSprite *param0);
void poffin_cooking_0223E340(PoffinCookingBurstEffect *param0);
void poffin_cooking_0223E34C(PoffinCookingBurstEffect *param0);
void poffin_cooking_0223E368(PoffinCookingBurstEffect *param0, SoftwareSpriteManager *param1, u32 param2, NARC *param3);
void poffin_cooking_0223E438(PoffinCookingBurstEffect *param0);
void poffin_cooking_0223E484(PoffinCookingBurstEffect *param0, u32 param1, BOOL param2);
void poffin_cooking_0223E4A4(PoffinCookingBurstEffect *param0, u16 param1);
void poffin_cooking_0223E4C0(PoffinCookingBurstEffect *param0, fx32 param1);
void poffin_cooking_0223E4E0(PoffinCookingBurstEffect *param0, u32 param1, u32 param2);
void poffin_cooking_0223E500(PoffinCookingBurstEffect *param0);
void poffin_cooking_0223E51C(PoffinCookingBurstEffect *param0, int param1);
void poffin_cooking_0223E5A4(PoffinCookingPlayerCursor *param0, const PoffinCookingSession *param1, u32 param2, PoffinCookingComm *param3);
void poffin_cooking_0223E5C0(PoffinCookingPlayerCursor *param0);
void poffin_cooking_0223E5DC(PoffinCookingPlayerCursor *param0, PoffinCookingSpriteManager *param1, PoffinCookingSpriteSet *param2, u32 param3);
void poffin_cooking_0223E63C(PoffinCookingPlayerCursor *param0);
void poffin_cooking_0223E658(PoffinCookingPlayerCursor *param0);
void poffin_cooking_0223E69C(PoffinCookingPlayerCursor *param0, BOOL param1);
void poffin_cooking_0223E6D4(PoffinCookingMessageBox *param0, int param1, PoffinCookingMessages *param2, PoffinCookingSession *param3, int param4, u32 param5);
void poffin_cooking_0223E6F8(PoffinCookingMessageBox *param0);
void poffin_cooking_0223E720(PoffinCookingMessageBox *param0, BgConfig *param1, u32 heapID, NARC *param3);
void poffin_cooking_0223E760(PoffinCookingMessageBox *param0);
void poffin_cooking_0223E908(PoffinCookingMessageBox *param0, u32 param1);
BOOL poffin_cooking_0223E984(const PoffinCookingMessageBox *param0);
void poffin_cooking_0223E994(PoffinCookingMessageBox *param0);
void poffin_cooking_0223E9BC(PoffinCookingMessageBox *param0);
void poffin_cooking_0223E9D0(PoffinCookingMessageBox *param0);
void poffin_cooking_0223EC4C(PoffinCookingMessageBox *param0, u32 param1);
void poffin_cooking_0223EC70(PoffinCookingMessageBox *param0);
void poffin_cooking_0223EC8C(PoffinCookingMessageBox *param0, u32 param1);
void poffin_cooking_0223ED3C(PoffinCookingParticleManager *param0);
void poffin_cooking_0223ED4C(PoffinCookingParticleManager *param0);
void poffin_cooking_0223ED6C(PoffinCookingParticleManager *param0, PoffinCookingSpriteManager *param1, PoffinCookingSpriteSet *param2, u32 param3);
void poffin_cooking_0223ED78(PoffinCookingParticleManager *param0);
void poffin_cooking_0223EDA4(PoffinCookingParticleManager *param0, PoffinCookingSession *param1);
void poffin_cooking_0223EDDC(PoffinCookingParticleManager *param0, int param1, int param2);
void poffin_cooking_0223EFCC(PoffinCookingParticleManager *param0);
void poffin_cooking_0223F29C(PoffinCookingArrowManager *param0);
void poffin_cooking_0223F2A8(PoffinCookingArrowManager *param0);
void poffin_cooking_0223F2C4(PoffinCookingArrowManager *param0, PoffinCookingSpriteManager *param1, u32 param2, NARC *param3);
void poffin_cooking_0223F348(PoffinCookingArrowManager *param0);
void poffin_cooking_0223F378(PoffinCookingArrowManager *param0);
void poffin_cooking_0223F3A0(PoffinCookingArrowManager *param0, int param1);
void poffin_cooking_0223F3D0(PoffinCookingArrowManager *param0, int param1);
BOOL poffin_cooking_0223F3F0(const PoffinCookingArrowManager *param0, int param1);
void poffin_cooking_0223F494(PoffinCookingSparkleManager *param0, int param1);
void poffin_cooking_0223F4AC(PoffinCookingSparkleManager *param0);
void poffin_cooking_0223F4CC(PoffinCookingSparkleManager *param0, PoffinCookingSpriteManager *param1, PoffinCookingSpriteSet *param2, u32 param3);
void poffin_cooking_0223F510(PoffinCookingSparkleManager *param0);
void poffin_cooking_0223F52C(PoffinCookingSparkleManager *param0);
void poffin_cooking_0223F544(PoffinCookingSparkleManager *param0, int param1, int param2);
void poffin_cooking_0223F730(PoffinCookingPoffinSprite *param0, int param1, int param2, int param3, int param4);
void poffin_cooking_0223F770(PoffinCookingPoffinSprite *param0);
void poffin_cooking_0223F784(PoffinCookingPoffinSprite *param0);
void poffin_cooking_0223F790(PoffinCookingYesNoMenu *param0, enum HeapID heapID, BgConfig *param2);
void poffin_cooking_0223F7A4(PoffinCookingYesNoMenu *param0);
void poffin_cooking_0223F7B0(PoffinCookingYesNoMenu *param0);
u32 poffin_cooking_0223F7DC(PoffinCookingYesNoMenu *param0);

#endif // POKEPLATINUM_POFFIN_COOKING_0223D6A8_H
