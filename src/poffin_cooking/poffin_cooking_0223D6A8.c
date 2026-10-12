#include "poffin_cooking/poffin_cooking_0223D6A8.h"

#include <nitro.h>
#include <string.h>

#include "poffin_cooking/poffin_cooking_0223D4CC.h"
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
#include "poffin_cooking/struct_poffin_cooking_particle.h"
#include "poffin_cooking/struct_poffin_cooking_arrow_manager.h"
#include "poffin_cooking/struct_poffin_cooking_arrow.h"
#include "poffin_cooking/struct_poffin_cooking_sparkle_manager.h"
#include "poffin_cooking/struct_poffin_cooking_sparkle.h"
#include "poffin_cooking/struct_poffin_cooking_poffin_sprite.h"
#include "poffin_cooking/struct_poffin_cooking_yes_no_menu.h"
#include "poffin_cooking/struct_poffin_cooking_blend_state.h"
#include "poffin_cooking/struct_poffin_cooking_session.h"

#include "bg_window.h"
#include "font.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "int_distance.h"
#include "math_util.h"
#include "narc.h"
#include "poffin_sprite.h"
#include "render_window.h"
#include "software_sprite.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "text.h"
#include "yes_no_touch_menu.h"

typedef struct {
    fx32 velocityX;
    fx32 velocityY;
    s16 startX;
    s16 endX;
    s16 startY;
    s16 endY;
    u8 duration;
    u8 delay;
} PoffinCookingPoffinAnimTemplate;

typedef struct {
    fx32 distanceMin;
    fx32 distanceRange;
    fx32 scaleVelocity;
    fx32 speedZ;
    u8 radiusMin;
    u8 radiusRange;
    u8 angleMin;
    u8 angleRange;
    u8 animID;
    u8 spriteSetIndex;
    u8 heapID;
    u8 state;
    u8 duration;
    u8 followStir;
    u8 priority;
} PoffinCookingParticleTemplate;

static void poffin_cooking_0223E09C(PoffinCookingPlayerListDisplay *param0, u32 heapID);
static void poffin_cooking_0223E138(PoffinCookingPlayerListDisplay *param0);
static void poffin_cooking_0223E15C(PoffinCookingPlayerListDisplay *param0, u32 param1, NARC *param2);
static void poffin_cooking_0223E208(PoffinCookingPlayerListDisplay *param0);
static void poffin_cooking_0223E21C(Window *param0, String *param1, int param2, int param3);
static void poffin_cooking_0223E77C(PoffinCookingMessageBox *param0, u32 heapID);
static void poffin_cooking_0223E824(PoffinCookingMessageBox *param0);
static void poffin_cooking_0223E844(PoffinCookingMessageBox *param0, u32 heapID, NARC *param2);
static PoffinCookingParticle *poffin_cooking_0223EFF4(PoffinCookingParticleManager *param0);
static PoffinCookingParticle *poffin_cooking_0223F018(PoffinCookingParticleManager *param0);
static void poffin_cooking_0223F054(PoffinCookingParticle *param0);
static void poffin_cooking_0223F074(PoffinCookingParticle *param0);
static void poffin_cooking_0223F0F4(PoffinCookingParticle *param0, PoffinCookingSession *param1);
static void poffin_cooking_0223F1C0(PoffinCookingParticle *param0, int param1, fx32 param2, fx32 param3, fx32 param4, fx32 param5, fx32 param6, fx32 param7, fx32 param8, fx32 param9, fx32 param10, BOOL param11, int param12, PoffinCookingSpriteSet *param13, int param14, PoffinCookingSpriteManager *param15, u32 param16, BOOL param17, u8 param18);
static void poffin_cooking_0223F268(PoffinCookingParticle *param0);
static void poffin_cooking_0223F410(PoffinCookingArrow *param0);
static void poffin_cooking_0223F420(PoffinCookingArrow *param0);
static void poffin_cooking_0223F44C(PoffinCookingArrow *param0);
static void poffin_cooking_0223F458(PoffinCookingArrow *param0);
static PoffinCookingSparkle *poffin_cooking_0223F650(PoffinCookingSparkleManager *param0);
static void poffin_cooking_0223F670(PoffinCookingSparkle *param0);
static void poffin_cooking_0223F6B4(PoffinCookingSparkle *param0);
static void poffin_cooking_0223F6CC(PoffinCookingSparkle *param0, int param1, fx32 param2, fx32 param3, fx32 param4, fx32 param5, fx32 param6, fx32 param7);

static int poffin_cooking_0223D6A8(int param0, const String *param1, int param2)
{
    u32 v0 = Font_CalcStringWidth(param2, param1, 0);
    v0 /= 2;
    param0 -= v0;

    return param0;
}

static SoftwareSpriteChars *poffin_cooking_0223D6BC(SoftwareSpriteManager *param0, u32 param1, u32 param2, NARC *param3)
{
    SoftwareSpriteCharsTemplate v0;
    void *v1;
    NNSG2dCharacterData *v2;
    SoftwareSpriteChars *v3;

    v1 = Graphics_GetCharDataFromOpenNARC(param3, param1, 0, &v2, param2);
    v0.softSpriteMan = param0;
    v0.charsData = v2;
    v3 = SoftwareSprite_LoadChars(&v0);

    Heap_Free(v1);

    return v3;
}

static SoftwareSpritePalette *poffin_cooking_0223D6EC(SoftwareSpriteManager *param0, u32 param1, u32 param2, NARC *param3)
{
    SoftwareSpritePaletteTemplate v0;
    void *v1;
    NNSG2dPaletteData *v2;
    SoftwareSpritePalette *v3;

    v1 = Graphics_GetPlttDataFromOpenNARC(param3, param1, &v2, param2);
    v0.softSpriteMan = param0;
    v0.paletteData = v2;
    v0.paletteSlot = 1;
    v3 = SoftwareSprite_LoadPalette(&v0);

    Heap_Free(v1);

    return v3;
}

static SoftwareSprite *poffin_cooking_0223D720(SoftwareSpriteManager *param0, SoftwareSpriteChars *param1, SoftwareSpritePalette *param2, int param3, int param4, int param5)
{
    SoftwareSpriteTemplate v0;
    SoftwareSprite *v1;

    v0.softSpriteMan = param0;
    v0.chars = param1;
    v0.palette = param2;
    v0.xPos = param3;
    v0.yPos = param4;
    v0.rotation = 0;
    v0.alpha = 31;
    v0.priority = param5;
    v0.paletteSlot = 0;

    v1 = SoftwareSprite_Load(&v0);
    SoftwareSprite_SetVisible(v1, 0);

    return v1;
}

void poffin_cooking_0223D754(PoffinCookingSpriteManager *param0, int param1, int param2, enum HeapID heapID)
{
    int i;

    param0->spriteList = SpriteList_InitRendering(param1, &param0->renderer, heapID);

    for (i = 0; i < 4; i++) {
        param0->resourceCollections[i] = SpriteResourceCollection_New(param2, i, heapID);
    }
}

void poffin_cooking_0223D784(PoffinCookingSpriteManager *param0)
{
    int v0;

    SpriteList_Delete(param0->spriteList);
    param0->spriteList = NULL;

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(param0->resourceCollections[v0]);
    }
}

void poffin_cooking_0223D7A8(PoffinCookingSpriteManager *param0, PoffinCookingSpriteSet *param1, NARC *param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9)
{
    BOOL v0;

    param1->resources[0] = SpriteResourceCollection_AddTilesFromEx(param0->resourceCollections[0], param2, param5, 0, param8, NNS_G2D_VRAM_TYPE_2DMAIN, param9, HEAP_ID_SAVE);
    param1->resources[1] = SpriteResourceCollection_AddPaletteFromEx(param0->resourceCollections[1], param2, param3, 0, param8, NNS_G2D_VRAM_TYPE_2DMAIN, param4, param9, HEAP_ID_SAVE);
    param1->sharedPalette = 0;
    param1->resources[2] = SpriteResourceCollection_AddFrom(param0->resourceCollections[2], param2, param6, 0, param8, 2, param9);
    param1->resources[3] = SpriteResourceCollection_AddFrom(param0->resourceCollections[3], param2, param7, 0, param8, 3, param9);

    v0 = SpriteTransfer_RequestCharAtEndWithHardwareMappingType(param1->resources[0]);
    GF_ASSERT(v0);
    SpriteResource_ReleaseData(param1->resources[0]);

    v0 = SpriteTransfer_RequestPlttFreeSpace(param1->resources[1]);
    GF_ASSERT(v0);
    SpriteResource_ReleaseData(param1->resources[1]);

    SpriteResourcesHeader_Init(&param1->header, param8, param8, param8, param8, 0xffffffff, 0xffffffff, 0, 0, param0->resourceCollections[0], param0->resourceCollections[1], param0->resourceCollections[2], param0->resourceCollections[3], NULL, NULL);
}

void poffin_cooking_0223D894(PoffinCookingSpriteManager *param0, PoffinCookingSpriteSet *param1, NARC *param2, SpriteResource *param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8)
{
    BOOL v0;
    u32 v1;

    param1->resources[0] = SpriteResourceCollection_AddTilesFromEx(param0->resourceCollections[0], param2, param4, 0, param7, NNS_G2D_VRAM_TYPE_2DMAIN, param8, HEAP_ID_SAVE);
    param1->resources[1] = param3;
    param1->sharedPalette = 1;

    v1 = SpriteResource_GetID(param3);

    param1->resources[2] = SpriteResourceCollection_AddFrom(param0->resourceCollections[2], param2, param5, 0, param7, 2, param8);
    param1->resources[3] = SpriteResourceCollection_AddFrom(param0->resourceCollections[3], param2, param6, 0, param7, 3, param8);

    v0 = SpriteTransfer_RequestCharAtEndWithHardwareMappingType(param1->resources[0]);
    GF_ASSERT(v0);

    SpriteResource_ReleaseData(param1->resources[0]);
    SpriteResourcesHeader_Init(&param1->header, param7, v1, param7, param7, 0xffffffff, 0xffffffff, 0, 0, param0->resourceCollections[0], param0->resourceCollections[1], param0->resourceCollections[2], param0->resourceCollections[3], NULL, NULL);
}

void poffin_cooking_0223D95C(PoffinCookingSpriteManager *param0, PoffinCookingSpriteSet *param1)
{
    int v0;

    SpriteTransfer_ResetCharTransfer(param1->resources[0]);

    if (param1->sharedPalette == 0) {
        SpriteTransfer_ResetPlttTransfer(param1->resources[1]);
    }

    for (v0 = 0; v0 < 4; v0++) {
        if (v0 != 1) {
            SpriteResourceCollection_Remove(param0->resourceCollections[v0], param1->resources[v0]);
        } else {
            if (param1->sharedPalette == 0) {
                SpriteResourceCollection_Remove(param0->resourceCollections[v0], param1->resources[v0]);
            }
        }
    }
}

Sprite *poffin_cooking_0223D9A8(PoffinCookingSpriteManager *param0, PoffinCookingSpriteSet *param1, fx32 param2, fx32 param3, fx32 param4, int param5, int param6)
{
    SpriteListTemplate v0;
    Sprite *v1;

    v0.list = param0->spriteList;
    v0.resourceData = &param1->header;
    v0.position.x = param2;
    v0.position.y = param3;
    v0.position.z = param4;
    v0.priority = param5;
    v0.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v0.heapID = param6;

    v1 = SpriteList_Add(&v0);
    GF_ASSERT(v1);

    return v1;
}

void poffin_cooking_0223D9DC(PoffinCookingScaleAnim *param0, fx32 param1, fx32 param2, int param3)
{
    param0->current = param1;
    param0->start = param1;
    param0->delta = param2 - param1;
    param0->duration = param3;
    param0->elapsed = 0;
}

BOOL poffin_cooking_0223D9EC(PoffinCookingScaleAnim *param0)
{
    fx32 v0;

    v0 = FX_Mul(param0->delta, param0->elapsed << FX32_SHIFT);
    v0 = FX_Div(v0, param0->duration << FX32_SHIFT);

    param0->current = v0 + param0->start;

    if ((param0->elapsed + 1) <= param0->duration) {
        param0->elapsed++;
        return 0;
    }

    param0->elapsed = param0->duration;

    return 1;
}

void poffin_cooking_0223DA34(PoffinCookingMotionAnim *param0, fx32 param1, fx32 param2, fx32 param3, int param4)
{
    fx32 v0;
    fx32 v1;
    fx32 v2;
    fx32 v3;

    v2 = param2 - param1;

    v0 = (param4 * param4) << FX32_SHIFT;
    v1 = FX_Mul(param3, param4 * FX32_ONE);
    v1 = v2 - v1;
    v1 = FX_Mul(v1, 2 * FX32_ONE);
    v3 = FX_Div(v1, v0);

    param0->current = param1;
    param0->start = param1;
    param0->velocity = param3;
    param0->acceleration = v3;
    param0->elapsed = 0;
    param0->duration = param4;
}

BOOL poffin_cooking_0223DA94(PoffinCookingMotionAnim *param0)
{
    fx32 v0;
    fx32 v1;
    fx32 v2;
    fx32 v3;

    v3 = FX_Mul(param0->velocity, param0->elapsed << FX32_SHIFT);
    v1 = (param0->elapsed * param0->elapsed) << FX32_SHIFT;
    v2 = FX_Mul(param0->acceleration, v1);
    v2 = FX_Div(v2, 2 * FX32_ONE);
    v0 = v3 + v2;

    param0->current = param0->start + v0;

    if ((param0->elapsed + 1) <= param0->duration) {
        param0->elapsed++;
        return 0;
    }

    param0->elapsed = param0->duration;
    return 1;
}

VecFx32 poffin_cooking_0223DAFC(fx32 param0, fx32 param1, fx32 param2)
{
    VecFx32 v0;

    v0.x = param0;
    v0.y = param1;
    v0.z = param2;
    return v0;
}

static const PoffinCookingPoffinAnimTemplate Unk_poffin_cooking_02240460[4] = {
    { FX32_CONST(0), FX32_CONST(0), 0x40, 0x60, 0xFFFFFFFFFFFFFFE0, 0x58, 0x20, 0xA },
    { FX32_CONST(0), FX32_CONST(0), 0x118, 0x9C, 0xC0, 0x80, 0x20, 0x20 },
    { FX32_CONST(0), FX32_CONST(0), 0xFFFFFFFFFFFFFFE0, 0x80, 0x20, 0x60, 0x20, 0x20 },
    { FX32_CONST(0), FX32_CONST(0), 0x80, 0x74, 0xFFFFFFFFFFFFFFE0, 0x60, 0x20, 0x20 }
};

void poffin_cooking_0223DB18(PoffinCookingPoffinAnim *param0, int param1)
{
    memset(param0, 0, sizeof(PoffinCookingPoffinAnim));
    param0->count = param1;
}

void poffin_cooking_0223DB30(PoffinCookingPoffinAnim *param0)
{
    GF_ASSERT(param0->active == 0);
    memset(param0, 0, sizeof(PoffinCookingPoffinAnim));
}

void poffin_cooking_0223DB4C(PoffinCookingPoffinAnim *param0, PoffinCookingBerryPacket *param1, PoffinCookingSpriteManager *param2, PoffinCookingSpriteSet *param3, u32 heapID)
{
    int v0;
    int v1;
    NARC *v2 = NARC_ctor(NARC_INDEX_GRAPHIC__NTAG_GRA, heapID);
    v1 = 0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param1->berries[v0].itemID != 0) {
            poffin_cooking_0223D7A8(param2, &param0->spriteSets[v1], v2, 70 + ((param1->berries[v0].itemID) - 149), 1, 6 + ((param1->berries[v0].itemID) - 149), 5, 4, 1000 + v0, heapID);

            param0->poffinSprites[v1] = poffin_cooking_0223D9A8(param2, &param0->spriteSets[v1], 0, 0, 0, 0, heapID);
            Sprite_SetDrawFlag(param0->poffinSprites[v1], FALSE);

            param0->burstSprites[v1] = poffin_cooking_0223D9A8(param2, &param3[0], 0, 0, 0, 0, heapID);
            Sprite_SetDrawFlag(param0->burstSprites[v1], FALSE);
            Sprite_SetAnim(param0->burstSprites[v1], 1);
            v1++;
        }

        if (param0->count == v1) {
            break;
        }
    }

    NARC_dtor(v2);

    param0->active = 1;
}

void poffin_cooking_0223DC1C(PoffinCookingPoffinAnim *param0, PoffinCookingSpriteManager *param1)
{
    int v0;

    GF_ASSERT(param0->active == 1);

    for (v0 = 0; v0 < param0->count; v0++) {
        Sprite_Delete(param0->poffinSprites[v0]);
        Sprite_Delete(param0->burstSprites[v0]);
        poffin_cooking_0223D95C(param1, &param0->spriteSets[v0]);
    }

    param0->active = 0;
}

void poffin_cooking_0223DC68(PoffinCookingPoffinAnim *param0)
{
    int v0;
    VecFx32 v1;

    GF_ASSERT(param0->animating == 0);

    for (v0 = 0; v0 < param0->count; v0++) {
        poffin_cooking_0223DA34(&param0->motionX[v0], Unk_poffin_cooking_02240460[v0].startX * FX32_ONE, Unk_poffin_cooking_02240460[v0].endX * FX32_ONE, Unk_poffin_cooking_02240460[v0].velocityX, Unk_poffin_cooking_02240460[v0].duration);
        poffin_cooking_0223DA34(&param0->motionY[v0], Unk_poffin_cooking_02240460[v0].startY * FX32_ONE, Unk_poffin_cooking_02240460[v0].endY * FX32_ONE, Unk_poffin_cooking_02240460[v0].velocityY, Unk_poffin_cooking_02240460[v0].duration);

        v1 = poffin_cooking_0223DAFC(param0->motionX[v0].current, param0->motionY[v0].current, 0);
        Sprite_SetPosition(param0->poffinSprites[v0], &v1);

        param0->states[v0] = 0;
        param0->delays[v0] = Unk_poffin_cooking_02240460[v0].delay;
    }

    param0->nextIndex = 0;
    param0->animating = 1;
}

u32 poffin_cooking_0223DD30(PoffinCookingPoffinAnim *param0)
{
    int v0;
    BOOL v1;
    VecFx32 v2;
    u32 v3 = 0;

    if (param0->animating == 0) {
        return 1;
    }

    if (param0->nextIndex < param0->count) {
        param0->delays[param0->nextIndex]--;

        if (param0->delays[param0->nextIndex] <= 0) {
            param0->states[param0->nextIndex] = 1;
            Sprite_SetDrawFlag(param0->poffinSprites[param0->nextIndex], TRUE);

            v3 = 2 + param0->nextIndex;
            param0->nextIndex++;
        }
    }

    for (v0 = 0; v0 < param0->count; v0++) {
        switch (param0->states[v0]) {
        case 0:
            break;
        case 1:
            v1 = poffin_cooking_0223DA94(&param0->motionX[v0]);
            poffin_cooking_0223DA94(&param0->motionY[v0]);

            v2 = poffin_cooking_0223DAFC(param0->motionX[v0].current, param0->motionY[v0].current, 0);
            Sprite_SetPosition(param0->poffinSprites[v0], &v2);

            if (v1 == 1) {
                Sprite_SetPosition(param0->burstSprites[v0], &v2);
                Sprite_SetDrawFlag(param0->burstSprites[v0], TRUE);
                Sprite_SetAnimateFlag(param0->burstSprites[v0], 1);
                Sprite_SetDrawFlag(param0->poffinSprites[v0], FALSE);
                Sound_PlayEffect(SEQ_SE_DP_NM09_sseq);
                param0->states[v0]++;
            }
            break;
        case 2:
            if (Sprite_IsAnimated(param0->burstSprites[v0]) == 0) {
                Sprite_SetDrawFlag(param0->burstSprites[v0], FALSE);
                param0->states[v0]++;
            }
            break;
        case 3:
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }
    }

    if (param0->states[param0->count - 1] == 3) {
        param0->animating = 0;
        return 1;
    }

    return v3;
}

void poffin_cooking_0223DEA0(PoffinCookingPlayerListDisplay *param0, int param1, PoffinCookingMessages *param2, PoffinCookingSession *param3, int param4, u32 param5)
{
    memset(param0, 0, sizeof(PoffinCookingPlayerListDisplay));
    param0->messages = param2;
    param0->playerCount = param1;
    param0->heapID = param5;
    param0->session = param3;
    param0->frameType = param4;
}

void poffin_cooking_0223DEC4(PoffinCookingPlayerListDisplay *param0)
{
    GF_ASSERT(param0->loaded == 0);
    memset(param0, 0, sizeof(PoffinCookingPlayerListDisplay));
}

void poffin_cooking_0223DEE0(PoffinCookingPlayerListDisplay *param0, BgConfig *param1, u32 heapID, NARC *param3)
{
    GF_ASSERT(param0->loaded == 0);

    param0->bgConfig = param1;

    poffin_cooking_0223E09C(param0, heapID);
    poffin_cooking_0223E15C(param0, heapID, param3);

    param0->loaded = 1;
}

void poffin_cooking_0223DF10(PoffinCookingPlayerListDisplay *param0)
{
    GF_ASSERT(param0->loaded == 1);

    poffin_cooking_0223E138(param0);
    poffin_cooking_0223E208(param0);

    param0->loaded = 0;
}

void poffin_cooking_0223DF30(PoffinCookingPlayerListDisplay *param0, int param1)
{
    StringTemplate_SetItemName(param0->messages->stringTemplate, 0, param1);
    StringTemplate_Format(param0->messages->stringTemplate, param0->messages->formattedString, param0->messages->string01);
    Window_FillTilemap(param0->messageWindow, 15);
    poffin_cooking_0223E21C(param0->messageWindow, param0->messages->formattedString, 0, 0);
    Window_DrawMessageBoxWithScrollCursor(param0->messageWindow, 0, 1, 0);
}

void poffin_cooking_0223DF70(PoffinCookingPlayerListDisplay *param0)
{
    Window_ClearAndCopyToVRAM(param0->messageWindow);
    Bg_ClearTilemap(param0->bgConfig, BG_LAYER_SUB_0);
}

void poffin_cooking_0223DF84(PoffinCookingPlayerListDisplay *param0)
{
    Window_FillTilemap(param0->messageWindow, 15);
    poffin_cooking_0223E21C(param0->messageWindow, param0->messages->string00, 0, 0);
    Window_DrawMessageBoxWithScrollCursor(param0->messageWindow, 0, 1, 0);
}

void poffin_cooking_0223DFAC(PoffinCookingPlayerListDisplay *param0)
{
    int v0;
    int v1;
    int v2;
    int v3;
    int v4;
    int v5;
    int v6, v7;

    if (param0->playerCount == 1) {
        return;
    }

    for (v0 = 0; v0 < param0->playerCount; v0++) {
        v1 = v0 % 2;
        v2 = (v0 / 2);
        v3 = v1 * 12;
        v4 = v2 * 5;
        v1 *= 10;
        v2 *= 4;

        Bg_CopyToTilemapRect(param0->bgConfig, 5, 5 + v3, 13 + v4, 10, 4, param0->nameScreenDataHeader->rawData, v1, v2, 10 * 2, 4 * 2);
        Bg_ChangeTilemapRectPalette(param0->bgConfig, 5, 5 + v3, 13 + v4, 10, 4, 2);

        v5 = param0->session->playerNetIDs[v0];
        StringTemplate_SetPlayerName(param0->messages->stringTemplate, 0, param0->session->trainerInfos[v5]);
        StringTemplate_Format(param0->messages->stringTemplate, param0->messages->formattedString, param0->messages->string02);

        v6 = poffin_cooking_0223D6A8((v3 * 8) + 32, param0->messages->formattedString, 1);
        v7 = (v4 * 8) + 8;
        poffin_cooking_0223E21C(param0->nameWindow, param0->messages->formattedString, v6, v7);
    }

    Window_ScheduleCopyToVRAM(param0->nameWindow);
    Bg_ScheduleTilemapTransfer(param0->bgConfig, 5);
}

static void poffin_cooking_0223E09C(PoffinCookingPlayerListDisplay *param0, u32 heapID)
{
    param0->messageWindow = Window_New(heapID, 1);
    param0->nameWindow = Window_New(heapID, 1);

    Window_Add(param0->bgConfig, param0->messageWindow, 4, 4, 19, 23, 4, 1, (18 + 12) + 1);
    Window_Add(param0->bgConfig, param0->nameWindow, 4, 6, 13, 20, 8, 1, (18 + 12) + 1);
    Window_FillTilemap(param0->messageWindow, 15);
    Window_FillTilemap(param0->nameWindow, 0);
    LoadMessageBoxGraphics(param0->bgConfig, BG_LAYER_SUB_0, 1, 0, param0->frameType, heapID);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_SUB_BG, PLTT_OFFSET(1), heapID);
    Window_DrawMessageBoxWithScrollCursor(param0->messageWindow, 1, 1, 0);
}

static void poffin_cooking_0223E138(PoffinCookingPlayerListDisplay *param0)
{
    Window_Remove(param0->messageWindow);
    Windows_Delete(param0->messageWindow, 1);
    Window_Remove(param0->nameWindow);
    Windows_Delete(param0->nameWindow, 1);
}

static void poffin_cooking_0223E15C(PoffinCookingPlayerListDisplay *param0, u32 heapID, NARC *param2)
{
    int v0;

    Graphics_LoadPaletteFromOpenNARC(param2, 1, 4, 2 * 32, 2 * 32, heapID);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param2, 0, param0->bgConfig, 5, 0, 0, 0, heapID);

    if (param0->playerCount == 1) {
        v0 = 2;
    } else {
        v0 = 3;
    }

    param0->screenData = Graphics_GetScrnDataFromOpenNARC(param2, v0, 0, &param0->screenDataHeader, heapID);

    Bg_LoadToTilemapRect(param0->bgConfig, 5, param0->screenDataHeader->rawData, 0, 0, param0->screenDataHeader->screenWidth / 8, param0->screenDataHeader->screenHeight / 8);
    Bg_ChangeTilemapRectPalette(param0->bgConfig, 5, 0, 0, param0->screenDataHeader->screenWidth / 8, param0->screenDataHeader->screenHeight / 8, 2 + 1);

    param0->nameScreenData = Graphics_GetScrnDataFromOpenNARC(param2, 4, 0, &param0->nameScreenDataHeader, heapID);

    Bg_ScheduleTilemapTransfer(param0->bgConfig, 5);
}

static void poffin_cooking_0223E208(PoffinCookingPlayerListDisplay *param0)
{
    Heap_Free(param0->screenData);
    Heap_Free(param0->nameScreenData);
}

static void poffin_cooking_0223E21C(Window *param0, String *param1, int param2, int param3)
{
    Text_AddPrinterWithParamsAndColor(param0, FONT_MESSAGE, param1, param2, param3, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
}

void poffin_cooking_0223E244(PoffinCookingReactionSprite *param0)
{
    memset(param0, 0, sizeof(PoffinCookingReactionSprite));
}

void poffin_cooking_0223E260(PoffinCookingReactionSprite *param0)
{
    GF_ASSERT(param0->active == 0);
    memset(param0, 0, sizeof(PoffinCookingReactionSprite));
}

void poffin_cooking_0223E28C(PoffinCookingReactionSprite *param0, PoffinCookingSpriteManager *param1, PoffinCookingSpriteSet *param2, u32 param3, u32 param4, u32 param5)
{
    param0->sprite = poffin_cooking_0223D9A8(param1, &param2[param4], 128 * FX32_ONE , 96 * FX32_ONE , 0, 0, param3);
    Sprite_SetDrawFlag(param0->sprite, FALSE);
    Sprite_SetAnim(param0->sprite, param5);
    param0->active = 1;
}

void poffin_cooking_0223E2C8(PoffinCookingReactionSprite *param0)
{
    GF_ASSERT(param0->active == 1);
    Sprite_Delete(param0->sprite);
    param0->active = 0;
}

void poffin_cooking_0223E2E4(PoffinCookingReactionSprite *param0)
{
    Sprite_SetDrawFlag(param0->sprite, TRUE);
    Sprite_SetAnimateFlag(param0->sprite, 1);
}

void poffin_cooking_0223E2FC(PoffinCookingReactionSprite *param0)
{
    VecFx32 v0;

    Sprite_SetDrawFlag(param0->sprite, TRUE);
    Sprite_SetAnimateFlag(param0->sprite, 1);

    v0.x = 168 * FX32_ONE;
    v0.y = 60 * FX32_ONE;

    Sprite_SetPosition(param0->sprite, &v0);
}

BOOL poffin_cooking_0223E32C(PoffinCookingReactionSprite *param0)
{
    if (Sprite_IsAnimated(param0->sprite) == 0) {
        return 1;
    }

    return 0;
}

static const u8 Unk_poffin_cooking_02240414[3] = {
    0x4,
    0x3,
    0x2
};

static const fx32 Unk_poffin_cooking_02240448[3] = {
    FX32_CONST(0.98f),
    FX32_CONST(0.95f),
    FX32_CONST(0.92f)
};

static const fx32 Unk_poffin_cooking_02240454[3] = {
    FX32_CONST(1.0f),
    FX32_CONST(1.0f),
    FX32_CONST(1.0f)
};

void poffin_cooking_0223E340(PoffinCookingBurstEffect *param0)
{
    memset(param0, 0, sizeof(PoffinCookingBurstEffect));
}

void poffin_cooking_0223E34C(PoffinCookingBurstEffect *param0)
{
    GF_ASSERT(param0->active == 0);
    memset(param0, 0, sizeof(PoffinCookingBurstEffect));
}

void poffin_cooking_0223E368(PoffinCookingBurstEffect *param0, SoftwareSpriteManager *param1, u32 param2, NARC *param3)
{
    int v0;
    static const u8 v1[] = {
        34,
        38,
        40,
        42,
        44,
        46,
    };
    static const u8 v2[] = {
        35,
        36,
        37,
        39,
        41,
        43,
        45,
        47,
    };
    static const u8 v3[] = {
        0,
        0,
        0,
        1,
        2,
        3,
        4,
        5,
    };
    static const u8 v4[] = {
        3,
        2,
        1,
        7,
        0,
        6,
        5,
        4,
    };
    static const u8 v5[] = {
        0,
        0,
        0,
        0,
        0,
        64,
        64,
        64,
    };
    static const u8 v6[] = {
        0,
        0,
        0,
        0,
        0,
        32,
        32,
        32,
    };

    GF_ASSERT(param0->active == 0);

    for (v0 = 0; v0 < 6; v0++) {
        param0->chars[v0] = poffin_cooking_0223D6BC(param1, v1[v0], param2, param3);
    }

    for (v0 = 0; v0 < 8; v0++) {
        param0->palettes[v0] = poffin_cooking_0223D6EC(param1, v2[v0], param2, param3);
    }

    for (v0 = 0; v0 < 8; v0++) {
        param0->sprites[v0] = poffin_cooking_0223D720(param1, param0->chars[v3[v0]], param0->palettes[v0], v5[v0], v6[v0], v4[v0]);
        SoftwareSprite_SetCenter(param0->sprites[v0], 128 - v5[v0], 96 - v6[v0]);
    }

    param0->active = 1;
}

void poffin_cooking_0223E438(PoffinCookingBurstEffect *param0)
{
    int v0;

    GF_ASSERT(param0->active == 1);

    for (v0 = 0; v0 < 8; v0++) {
        SoftwareSprite_Reset(param0->sprites[v0]);
    }

    for (v0 = 0; v0 < 6; v0++) {
        SoftwareSprite_FreeChars(param0->chars[v0]);
    }

    for (v0 = 0; v0 < 8; v0++) {
        SoftwareSprite_FreePalette(param0->palettes[v0]);
    }

    param0->active = 0;
}

void poffin_cooking_0223E484(PoffinCookingBurstEffect *param0, u32 param1, BOOL param2)
{
    GF_ASSERT(param1 < 8);
    SoftwareSprite_SetVisible(param0->sprites[param1], param2);
}

void poffin_cooking_0223E4A4(PoffinCookingBurstEffect *param0, u16 param1)
{
    int v0;

    for (v0 = 5; v0 <= 7; v0++) {
        SoftwareSprite_SetRotation(param0->sprites[v0], param1);
    }
}

void poffin_cooking_0223E4C0(PoffinCookingBurstEffect *param0, fx32 param1)
{
    int v0;

    for (v0 = 5; v0 <= 7; v0++) {
        SoftwareSprite_SetScalingFactors(param0->sprites[v0], param1, param1);
    }
}

void poffin_cooking_0223E4E0(PoffinCookingBurstEffect *param0, u32 param1, u32 param2)
{
    GF_ASSERT(param1 < 8);
    SoftwareSprite_SetAlpha(param0->sprites[param1], param2);
}

void poffin_cooking_0223E500(PoffinCookingBurstEffect *param0)
{
    param0->scaleState = 1;
    param0->scaleDirection = 0;

    poffin_cooking_0223D9DC(&param0->scaleAnim, FX32_ONE, Unk_poffin_cooking_02240448[0], Unk_poffin_cooking_02240414[0]);
}

void poffin_cooking_0223E51C(PoffinCookingBurstEffect *param0, int param1)
{
    BOOL v0;
    int v1;

    switch (param0->scaleState) {
    case 0:

        if (param0->scaleDirection == 0) {
            poffin_cooking_0223D9DC(&param0->scaleAnim, Unk_poffin_cooking_02240448[param1], Unk_poffin_cooking_02240454[param1], Unk_poffin_cooking_02240414[param1]);
        } else {
            poffin_cooking_0223D9DC(&param0->scaleAnim, Unk_poffin_cooking_02240454[param1], Unk_poffin_cooking_02240448[param1], Unk_poffin_cooking_02240414[param1]);
        }

        param0->scaleState++;
    case 1:
        v0 = poffin_cooking_0223D9EC(&param0->scaleAnim);

        for (v1 = 0; v1 <= 2; v1++) {
            SoftwareSprite_SetScalingFactors(param0->sprites[v1], param0->scaleAnim.current, param0->scaleAnim.current);
        }

        if (v0 == 1) {
            param0->scaleState = 0;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

void poffin_cooking_0223E5A4(PoffinCookingPlayerCursor *param0, const PoffinCookingSession *param1, u32 param2, PoffinCookingComm *param3)
{
    memset(param0, 0, sizeof(PoffinCookingPlayerCursor));
    param0->session = param1;
    param0->playerCount = param2;
    param0->comm = param3;
}

void poffin_cooking_0223E5C0(PoffinCookingPlayerCursor *param0)
{
    GF_ASSERT(param0->active == 0);
    memset(param0, 0, sizeof(PoffinCookingPlayerCursor));
}

void poffin_cooking_0223E5DC(PoffinCookingPlayerCursor *param0, PoffinCookingSpriteManager *param1, PoffinCookingSpriteSet *param2, u32 param3)
{
    int v0;
    VecFx32 v1;

    v1.x = 128 * FX32_ONE;
    v1.y = 96 * FX32_ONE;

    for (v0 = 0; v0 < 4; v0++) {
        param0->sprites[v0] = poffin_cooking_0223D9A8(param1, &param2[1], 128, 96, 0, 2, param3);
        Sprite_SetDrawFlag(param0->sprites[v0], FALSE);
        Sprite_SetAnim(param0->sprites[v0], 4 + v0);
        Sprite_SetPosition(param0->sprites[v0], &v1);
    }

    param0->active = 1;
}

void poffin_cooking_0223E63C(PoffinCookingPlayerCursor *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        Sprite_Delete(param0->sprites[v0]);
    }

    param0->active = 0;
}

void poffin_cooking_0223E658(PoffinCookingPlayerCursor *param0)
{
    int v0;
    int v1;
    VecFx32 v2;
    const PoffinCookingBlendState *v3 = &param0->session->participants[0].blendState;

    for (v0 = 0; v0 < param0->playerCount; v0++) {
        v1 = param0->session->playerNetIDs[v0];
        v2.x = v3->posX[v1] * FX32_ONE;
        v2.y = v3->posY[v1] * FX32_ONE;
        Sprite_SetPosition(param0->sprites[v0], &v2);
    }
}

void poffin_cooking_0223E69C(PoffinCookingPlayerCursor *param0, BOOL param1)
{
    int v0;
    int v1;

    for (v0 = 0; v0 < param0->playerCount; v0++) {
        v1 = param0->session->playerNetIDs[v0];

        if (poffin_cooking_0223D570(param0->comm) != v1) {
            Sprite_SetDrawFlag(param0->sprites[v0], param1);
        }
    }
}

void poffin_cooking_0223E6D4(PoffinCookingMessageBox *param0, int param1, PoffinCookingMessages *param2, PoffinCookingSession *param3, int param4, u32 param5)
{
    memset(param0, 0, sizeof(PoffinCookingMessageBox));
    param0->messages = param2;
    param0->playerCount = param1;
    param0->heapID = param5;
    param0->session = param3;
    param0->frameType = param4;
}

void poffin_cooking_0223E6F8(PoffinCookingMessageBox *param0)
{
    GF_ASSERT(param0->loaded == 0);

    poffin_cooking_0223E994(param0);
    poffin_cooking_0223E9D0(param0);

    memset(param0, 0, sizeof(PoffinCookingMessageBox));
}

void poffin_cooking_0223E720(PoffinCookingMessageBox *param0, BgConfig *param1, u32 heapID, NARC *param3)
{
    GF_ASSERT(param0->loaded == 0);

    param0->bgConfig = param1;

    poffin_cooking_0223E77C(param0, heapID);
    poffin_cooking_0223E844(param0, heapID, param3);

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);

    param0->loaded = 1;
}

void poffin_cooking_0223E760(PoffinCookingMessageBox *param0)
{
    GF_ASSERT(param0->loaded == 1);

    poffin_cooking_0223E824(param0);

    param0->loaded = 0;
}

static void poffin_cooking_0223E77C(PoffinCookingMessageBox *param0, u32 heapID)
{
    int v0;
    static u16 v1[4][6] = {
        { 8, 11, 16, 4, 2, 40 },
        { 2, 1, 28, 15, 3, 40 },
        { 2, 18, 28, 5, 3, 460 },
        { 2, 2, 27, 5, 2, 40 }
    };

    LoadMessageBoxGraphics(param0->bgConfig, BG_LAYER_MAIN_2, 1, 0, param0->frameType, heapID);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(2), heapID);
    LoadStandardWindowGraphics(param0->bgConfig, BG_LAYER_MAIN_2, 1 + (18 + 12), 1, 0, heapID);
    Font_LoadTextPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(3), heapID);

    for (v0 = 0; v0 < 4; v0++) {
        param0->windows[v0] = Window_New(heapID, 1);
        Window_Add(param0->bgConfig, param0->windows[v0], 2, v1[v0][0], v1[v0][1], v1[v0][2], v1[v0][3], v1[v0][4], v1[v0][5]);
        Window_FillTilemap(param0->windows[v0], 0);
    }
}

static void poffin_cooking_0223E824(PoffinCookingMessageBox *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        Window_Remove(param0->windows[v0]);
        Windows_Delete(param0->windows[v0], 1);
    }
}

static void poffin_cooking_0223E844(PoffinCookingMessageBox *param0, u32 heapID, NARC *param2)
{
    void *v0;
    NNSG2dScreenData *v1;

    Graphics_LoadPaletteFromOpenNARC(param2, 6, 0, 4 * 32, 1 * 32, heapID);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param2, 5, param0->bgConfig, 1, 0, 0, 0, heapID);

    v0 = Graphics_GetScrnDataFromOpenNARC(param2, 7, 0, &v1, heapID);

    Bg_LoadToTilemapRect(param0->bgConfig, 1, v1->rawData, 0, 0, v1->screenWidth / 8, v1->screenHeight / 8);
    Bg_ChangeTilemapRectPalette(param0->bgConfig, 1, 0, 0, v1->screenWidth / 8, v1->screenHeight / 8, 4);
    Heap_Free(v0);
    Bg_ScheduleTilemapTransfer(param0->bgConfig, 1);
}

static void poffin_cooking_0223E8DC(SysTask *param0, void *param1)
{
    PoffinCookingMessageBox *v0 = param1;

    v0->timer++;

    if (v0->timer >= 30) {
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        SysTask_Done(param0);
        v0->task = NULL;
    }
}

void poffin_cooking_0223E908(PoffinCookingMessageBox *param0, u32 param1)
{
    GF_ASSERT(param0->task == NULL);

    param0->task = SysTask_Start(poffin_cooking_0223E8DC, param0, 1024);
    param0->timer = 0;

    Window_FillTilemap(param0->windows[0], 0);

    {
        u32 v0 = Font_CalcCenterAlignment(FONT_MESSAGE, param0->messages->strings03[param1], 0, 128);
        Text_AddPrinterWithParamsAndColor(param0->windows[0], FONT_MESSAGE, param0->messages->strings03[param1], v0, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    }

    Window_CopyToVRAM(param0->windows[0]);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
}

BOOL poffin_cooking_0223E984(const PoffinCookingMessageBox *param0)
{
    if (param0->task == NULL) {
        return 1;
    }

    return 0;
}

void poffin_cooking_0223E994(PoffinCookingMessageBox *param0)
{
    if (param0->task == NULL) {
        return;
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
    SysTask_Done(param0->task);

    param0->task = NULL;
}

void poffin_cooking_0223E9BC(PoffinCookingMessageBox *param0)
{
    poffin_cooking_0223E9D0(param0);
    param0->waitDial = Window_AddWaitDial(param0->windows[3], 1);
}

void poffin_cooking_0223E9D0(PoffinCookingMessageBox *param0)
{
    if (param0->waitDial != NULL) {
        DestroyWaitDial(param0->waitDial);
        param0->waitDial = NULL;
    }
}

static void poffin_cooking_0223E9E4(PoffinCookingMessageBox *param0)
{
    Bg_ClearTilemap(param0->bgConfig, BG_LAYER_MAIN_2);
    Window_FillTilemap(param0->windows[1], 15);

    {
        u32 v0 = Font_CalcCenterAlignment(FONT_SYSTEM, param0->messages->string09, 0, 224);
        Text_AddPrinterWithParamsAndColor(param0->windows[1], FONT_SYSTEM, param0->messages->string09, v0, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    }

    Window_DrawStandardFrame(param0->windows[1], 0, 1 + (18 + 12), 1);
    Window_FillTilemap(param0->windows[2], 15);
    Text_AddPrinterWithParamsAndColor(param0->windows[2], FONT_SYSTEM, param0->messages->strings10[6], 0, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    Window_DrawStandardFrame(param0->windows[2], 0, 1 + (18 + 12), 1);
    Window_ScheduleCopyToVRAM(param0->windows[1]);
    Window_ScheduleCopyToVRAM(param0->windows[2]);
}

static void poffin_cooking_0223EA6C(PoffinCookingMessageBox *param0)
{
    Text_AddPrinterWithParamsAndColor(param0->windows[1], FONT_SYSTEM, param0->messages->strings10[0], 0, 24, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    StringTemplate_SetNumber(param0->messages->stringTemplate, 0, param0->session->receivedResult.minutes, 2, 2, 1);
    StringTemplate_SetNumber(param0->messages->stringTemplate, 1, param0->session->receivedResult.seconds, 2, 2, 1);
    StringTemplate_SetNumber(param0->messages->stringTemplate, 2, param0->session->receivedResult.centiseconds, 2, 2, 1);
    StringTemplate_Format(param0->messages->stringTemplate, param0->messages->formattedString, param0->messages->strings10[1]);
    Text_AddPrinterWithParamsAndColor(param0->windows[1], FONT_SYSTEM, param0->messages->formattedString, 160, 24, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    Text_AddPrinterWithParamsAndColor(param0->windows[1], FONT_SYSTEM, param0->messages->strings10[2], 0, 48, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    StringTemplate_SetNumber(param0->messages->stringTemplate, 0, param0->session->receivedResult.greatStirCount, 4, 0, 1);

    {
        int v0 = (param0->session->receivedResult.greatStirCount == 1) ? 3 : 5;
        StringTemplate_Format(param0->messages->stringTemplate, param0->messages->formattedString, param0->messages->strings10[v0]);
    }

    Text_AddPrinterWithParamsAndColor(param0->windows[1], FONT_SYSTEM, param0->messages->formattedString, 160, 48, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    Text_AddPrinterWithParamsAndColor(param0->windows[1], FONT_SYSTEM, param0->messages->strings10[4], 0, 68, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    StringTemplate_SetNumber(param0->messages->stringTemplate, 0, param0->session->receivedResult.goodStirCount, 4, 0, 1);

    {
        int v1 = (param0->session->receivedResult.goodStirCount == 1) ? 3 : 5;
        StringTemplate_Format(param0->messages->stringTemplate, param0->messages->formattedString, param0->messages->strings10[v1]);
    }

    Text_AddPrinterWithParamsAndColor(param0->windows[1], FONT_SYSTEM, param0->messages->formattedString, 160, 68, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    Window_ScheduleCopyToVRAM(param0->windows[1]);
}

static void poffin_cooking_0223EBD8(PoffinCookingMessageBox *param0)
{
    StringTemplate_SetPoffinName(param0->messages->stringTemplate, 3, param0->session->receivedResult.poffinSpecies);
    StringTemplate_SetNumber(param0->messages->stringTemplate, 1, param0->session->receivedResult.level, 2, 2, 1);
    StringTemplate_SetNumber(param0->messages->stringTemplate, 2, param0->playerCount, 2, 2, 1);
    StringTemplate_Format(param0->messages->stringTemplate, param0->messages->formattedString, param0->messages->strings10[7]);
    Text_AddPrinterWithParamsAndColor(param0->windows[2], FONT_SYSTEM, param0->messages->formattedString, 16, 24, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    Window_ScheduleCopyToVRAM(param0->windows[2]);
}

void poffin_cooking_0223EC4C(PoffinCookingMessageBox *param0, u32 param1)
{
    switch (param1) {
    case 0:
        poffin_cooking_0223E9E4(param0);
        break;
    case 1:
        poffin_cooking_0223EA6C(param0);
        break;
    case 2:
        poffin_cooking_0223EBD8(param0);
        break;
    }
}

void poffin_cooking_0223EC70(PoffinCookingMessageBox *param0)
{
    Bg_ClearTilemap(param0->bgConfig, BG_LAYER_MAIN_2);
    Window_ClearAndCopyToVRAM(param0->windows[1]);
    Window_ClearAndCopyToVRAM(param0->windows[2]);
}

void poffin_cooking_0223EC8C(PoffinCookingMessageBox *param0, u32 param1)
{
    String *v0;
    int v1;

    poffin_cooking_0223E9D0(param0);
    Window_FillTilemap(param0->windows[3], 15);

    switch (param1) {
    case 0:
        StringTemplate_SetPlayerName(param0->messages->stringTemplate, 0, param0->session->trainerInfos[param0->session->localPlayerIndex]);
        StringTemplate_Format(param0->messages->stringTemplate, param0->messages->formattedString, param0->messages->string20);
        v0 = param0->messages->formattedString;
        break;
    case 1:
        v0 = param0->messages->string21;
        break;
    case 2:
        v0 = param0->messages->string24;
        break;
    case 3:
        v0 = param0->messages->string23;
        break;
    case 4:
        v0 = param0->messages->string22;
        break;
    case 5:
        v0 = param0->messages->string25;
        break;
    case 6:
        v0 = param0->messages->string00;
        break;
    }

    Text_AddPrinterWithParamsAndColor(param0->windows[3], FONT_MESSAGE, v0, 0, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    Window_DrawMessageBoxWithScrollCursor(param0->windows[3], 0, 1, 0);
    Window_ScheduleCopyToVRAM(param0->windows[3]);
}

static const PoffinCookingParticleTemplate Unk_poffin_cooking_022404B0[8] = {
    { FX32_CONST(0.50f), FX32_CONST(1.50f), FX32_CONST(0.0f), FX32_CONST(0.0f), 0x20, 0x40, 0x0, 0x0, 0x20, 0x2, 0x1, 0x0, 0x0, 0x0, 0x5 },
    { FX32_CONST(0.50f), FX32_CONST(1.0f), FX32_CONST(0.0f), FX32_CONST(0.0f), 0x0, 0x8, 0x0, 0x18, 0x10, 0x2, 0x2, 0x1, 0x1, 0x1, 0xA },
    { FX32_CONST(0.50f), FX32_CONST(1.50f), FX32_CONST(0.0f), FX32_CONST(2.0f), 0x20, 0x40, 0x20, 0x40, 0x10, 0x2, 0x0, 0x0, 0x0, 0x0, 0x5 },
    { FX32_CONST(0.50f), FX32_CONST(1.50f), FX32_CONST(0.0f), FX32_CONST(0.0f), 0x20, 0x40, 0x0, 0x0, 0x20, 0x3, 0x1, 0x0, 0x0, 0x0, 0x5 },
    { FX32_CONST(0.50f), FX32_CONST(1.0f), FX32_CONST(0.0f), FX32_CONST(0.0f), 0x0, 0x8, 0x0, 0x18, 0x10, 0x3, 0x2, 0x1, 0x1, 0x1, 0xA },
    { FX32_CONST(0.50f), FX32_CONST(1.50f), FX32_CONST(0.0f), FX32_CONST(4.0f), 0x20, 0x40, 0x20, 0x40, 0x10, 0x3, 0x0, 0x0, 0x0, 0x0, 0x5 },
    { FX32_CONST(0.50f), FX32_CONST(1.50f), FX32_CONST(0.0f), FX32_CONST(0.0f), 0x20, 0x40, 0x0, 0x0, 0x20, 0x4, 0x0, 0x0, 0x0, 0x0, 0x5 },
    { FX32_CONST(0.50f), FX32_CONST(1.50f), FX32_CONST(0.0f), FX32_CONST(0.0f), 0x20, 0x40, 0x0, 0x0, 0x20, 0x4, 0x1, 0x0, 0x0, 0x0, 0x5 }
};

void poffin_cooking_0223ED3C(PoffinCookingParticleManager *param0)
{
    memset(param0, 0, sizeof(PoffinCookingParticleManager));
}

void poffin_cooking_0223ED4C(PoffinCookingParticleManager *param0)
{
    GF_ASSERT(param0->loaded == 0);
    memset(param0, 0, sizeof(PoffinCookingParticleManager));
}

void poffin_cooking_0223ED6C(PoffinCookingParticleManager *param0, PoffinCookingSpriteManager *param1, PoffinCookingSpriteSet *param2, u32 param3)
{
    param0->spriteManager = param1;
    param0->spriteSets = param2;
    param0->heapID = param3;
    param0->loaded = 1;
}

void poffin_cooking_0223ED78(PoffinCookingParticleManager *param0)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->particles[v0].sprite != NULL) {
            poffin_cooking_0223F054(&param0->particles[v0]);
        }
    }

    param0->loaded = 0;
}

void poffin_cooking_0223EDA4(PoffinCookingParticleManager *param0, PoffinCookingSession *param1)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->particles[v0].sprite) {
            poffin_cooking_0223F074(&param0->particles[v0]);

            if (param0->particles[v0].followStir) {
                poffin_cooking_0223F0F4(&param0->particles[v0], param1);
            }
        }
    }
}

void poffin_cooking_0223EDDC(PoffinCookingParticleManager *param0, int param1, int param2)
{
    PoffinCookingParticle *v0;
    u16 v1;
    fx32 v2, v3, v4, v5, v6, v7, v8;
    PoffinCookingParticleTemplate v9 = Unk_poffin_cooking_022404B0[param1 * 3 + param2];
    int v10, v11;

    if ((param1 * 3 + param2) >= ((3 * 3) - 1)) {
        return;
    }

    v0 = poffin_cooking_0223EFF4(param0);

    if (v0 == NULL) {
        v0 = poffin_cooking_0223F018(param0);
        GF_ASSERT(v0);
        poffin_cooking_0223F054(v0);
    }

    v1 = MTRNG_Next();
    v10 = v9.radiusMin + (MTRNG_Next() % v9.radiusRange);
    v11 = v9.angleMin + (MTRNG_Next() % v9.angleRange);

    v11 += v10;

    v2 = FX_Mul(FX_SinIdx(v1), v10 * FX32_ONE);
    v4 = FX_Mul(FX_CosIdx(v1), v10 * FX32_ONE);
    v3 = FX_Mul(FX_SinIdx(v1), v11 * FX32_ONE);
    v5 = FX_Mul(FX_CosIdx(v1), v11 * FX32_ONE);
    v7 = FX_Mul(FX_SinIdx(v1), v9.speedZ);
    v8 = FX_Mul(FX_CosIdx(v1), v9.speedZ);

    v2 += 128 * FX32_ONE;
    v3 += 128 * FX32_ONE;
    v4 += 96 * FX32_ONE;
    v5 += 96 * FX32_ONE;

    v6 = v9.distanceMin + (MTRNG_Next() % v9.distanceRange);
    poffin_cooking_0223F1C0(v0, v9.state, v2, v3, v7, v4, v5, v8, FX32_CONST(0.10f), v6, v9.scaleVelocity, v9.duration, v9.animID, &param0->spriteSets[v9.spriteSetIndex], v9.heapID, param0->spriteManager, param0->heapID, v9.followStir, v9.priority);
    v0->serial = param0->nextSerial;

    param0->nextSerial++;
}

void poffin_cooking_0223EFCC(PoffinCookingParticleManager *param0)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->particles[v0].sprite != NULL) {
            poffin_cooking_0223F268(&param0->particles[v0]);
        }
    }
}

static PoffinCookingParticle *poffin_cooking_0223EFF4(PoffinCookingParticleManager *param0)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->particles[v0].sprite == NULL) {
            return &param0->particles[v0];
        }
    }

    return NULL;
}

static PoffinCookingParticle *poffin_cooking_0223F018(PoffinCookingParticleManager *param0)
{
    int v0;
    PoffinCookingParticle *v1 = NULL;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->particles[v0].sprite != NULL) {
            if (v1 == NULL) {
                v1 = &param0->particles[v0];
            } else {
                if (v1->serial > param0->particles[v0].serial) {
                    v1 = &param0->particles[v0];
                }
            }
        }
    }

    return v1;
}

static void poffin_cooking_0223F054(PoffinCookingParticle *param0)
{
    GF_ASSERT(param0->sprite);

    Sprite_Delete(param0->sprite);
    memset(param0, 0, sizeof(PoffinCookingParticle));
}

static void poffin_cooking_0223F074(PoffinCookingParticle *param0)
{
    BOOL v0;

    if (param0->motionDone == 0) {
        param0->motionDone = poffin_cooking_0223DA94(&param0->motionX);
        poffin_cooking_0223DA94(&param0->motionY);
        poffin_cooking_0223DA94(&param0->motionScale);

        param0->position.x = param0->motionX.current;
        param0->position.y = param0->motionY.current;

        Sprite_SetPosition(param0->sprite, &param0->position);

        if (param0->hasScale) {
            param0->scale.x = param0->motionScale.current;
            param0->scale.y = param0->motionScale.current;
            param0->scale.z = param0->motionScale.current;

            Sprite_SetAffineScale(param0->sprite, &param0->scale);
        }
    }

    if (param0->animDone == 0) {
        if (Sprite_IsAnimated(param0->sprite) == 0) {
            param0->animDone = 1;
        }
    }

    if (param0->state == 0) {
        if ((param0->motionDone == 1) && (param0->animDone == 1)) {
            poffin_cooking_0223F054(param0);
        }
    }
}

static void poffin_cooking_0223F0F4(PoffinCookingParticle *param0, PoffinCookingSession *param1)
{
    VecFx32 v0;
    u32 v1;
    u16 v2;
    u16 v3;
    fx32 v4, v5;

    if ((param0->motionDone == 1) && (param0->animDone == 1)) {
        if (param1->participants[0].blendState.direction == 0) {
            param0->angle += param1->participants[0].blendState.stirSpeed;
        } else {
            param0->angle -= param1->participants[0].blendState.stirSpeed;
        }

        v4 = param0->position.x - (128 * FX32_ONE);
        v5 = param0->position.y - (96 * FX32_ONE);
        v1 = CalcDistance2D(v4 >> FX32_SHIFT, v5 >> FX32_SHIFT, 0, 0);
        v2 = FX_Atan2Idx(v5, v4);
        v3 = v2 + param0->angle;

        v0.x = FX_Mul(FX_CosIdx(v3), v1 * FX32_ONE);
        v0.y = FX_Mul(FX_SinIdx(v3), v1 * FX32_ONE);
        v0.x += (128 * FX32_ONE);
        v0.y += (96 * FX32_ONE);

        Sprite_SetPosition(param0->sprite, &v0);
    }
}

static void poffin_cooking_0223F1C0(PoffinCookingParticle *param0, int param1, fx32 param2, fx32 param3, fx32 param4, fx32 param5, fx32 param6, fx32 param7, fx32 param8, fx32 param9, fx32 param10, BOOL param11, int param12, PoffinCookingSpriteSet *param13, int param14, PoffinCookingSpriteManager *param15, u32 param16, BOOL param17, u8 param18)
{
    param0->state = param1;

    poffin_cooking_0223DA34(&param0->motionX, param2, param3, param4, param12);
    poffin_cooking_0223DA34(&param0->motionY, param5, param6, param7, param12);
    poffin_cooking_0223DA34(&param0->motionScale, param8, param9, param10, param12);

    param0->position.x = param2;
    param0->position.y = param5;
    param0->scale.x = param8;
    param0->scale.y = param8;
    param0->scale.z = param8;
    param0->hasScale = param11;
    param0->followStir = param17;
    param0->sprite = poffin_cooking_0223D9A8(param15, param13, param2, param5, 0, param18, param16);

    GF_ASSERT(param0->sprite);

    if (param0->hasScale) {
        Sprite_SetAffineScaleEx(param0->sprite, &param0->scale, 2);
    }

    Sprite_SetAnim(param0->sprite, param14);
    Sprite_SetAnimateFlag(param0->sprite, 1);
    Sprite_SetExplicitPriority(param0->sprite, 2);
}

static void poffin_cooking_0223F268(PoffinCookingParticle *param0)
{
    if (param0->state != 1) {
        return;
    }

    poffin_cooking_0223DA34(&param0->motionScale, param0->motionScale.current, FX32_CONST(0.050f), 0, 8);

    param0->state = 0;
    param0->hasScale = 1;

    Sprite_SetAffineOverwriteMode(param0->sprite, 2);
}

void poffin_cooking_0223F29C(PoffinCookingArrowManager *param0)
{
    memset(param0, 0, sizeof(PoffinCookingArrowManager));
}

void poffin_cooking_0223F2A8(PoffinCookingArrowManager *param0)
{
    GF_ASSERT(param0->loaded == 0);
    memset(param0, 0, sizeof(PoffinCookingArrowManager));
}

void poffin_cooking_0223F2C4(PoffinCookingArrowManager *param0, PoffinCookingSpriteManager *param1, u32 param2, NARC *param3)
{
    int v0;

    GF_ASSERT(param0->loaded == 0);

    param0->spriteManager = param1;

    poffin_cooking_0223D7A8(param1, &param0->spriteSet, param3, 33, 2, 32, 31, 30, 7000, param2);

    for (v0 = 0; v0 < 4; v0++) {
        param0->arrows[v0].sprite = poffin_cooking_0223D9A8(param1, &param0->spriteSet, 128 * FX32_ONE , 96 * FX32_ONE , 0, 0, param2);

        if (v0 >= 2) {
            Sprite_SetAnim(param0->arrows[v0].sprite, 1);
        }

        Sprite_SetDrawFlag(param0->arrows[v0].sprite, FALSE);
    }

    param0->loaded = 1;
}

void poffin_cooking_0223F348(PoffinCookingArrowManager *param0)
{
    int v0;

    GF_ASSERT(param0->loaded == 1);

    for (v0 = 0; v0 < 4; v0++) {
        Sprite_Delete(param0->arrows[v0].sprite);
    }

    poffin_cooking_0223D95C(param0->spriteManager, &param0->spriteSet);

    param0->loaded = 0;
}

void poffin_cooking_0223F378(PoffinCookingArrowManager *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        if ((v0 == 2) || (v0 == 0)) {
            poffin_cooking_0223F420(&param0->arrows[v0]);
        } else {
            poffin_cooking_0223F458(&param0->arrows[v0]);
        }
    }
}

void poffin_cooking_0223F3A0(PoffinCookingArrowManager *param0, int param1)
{
    GF_ASSERT(param1 < 4);

    if ((param1 == 2) || (param1 == 0)) {
        poffin_cooking_0223F410(&param0->arrows[param1]);
    } else {
        poffin_cooking_0223F44C(&param0->arrows[param1]);
    }
}

void poffin_cooking_0223F3D0(PoffinCookingArrowManager *param0, int param1)
{
    GF_ASSERT(param1 < 4);

    param0->arrows[param1].active = 0;

    Sprite_SetDrawFlag(param0->arrows[param1].sprite, FALSE);
}

BOOL poffin_cooking_0223F3F0(const PoffinCookingArrowManager *param0, int param1)
{
    GF_ASSERT(param1 < 4);

    if (param0->arrows[param1].active == 0) {
        return 1;
    }

    return 0;
}

static void poffin_cooking_0223F410(PoffinCookingArrow *param0)
{
    param0->frame = 0;
    param0->framesRemaining = 3;
    param0->active = 1;
}

static void poffin_cooking_0223F420(PoffinCookingArrow *param0)
{
    if (param0->active == 0) {
        return;
    }

    poffin_cooking_0223F458(param0);

    if (param0->frame == 0) {
        param0->framesRemaining--;

        if (param0->framesRemaining <= 0) {
            param0->active = 0;

            Sprite_SetDrawFlag(param0->sprite, FALSE);
        }
    }
}

static void poffin_cooking_0223F44C(PoffinCookingArrow *param0)
{
    param0->frame = 0;
    param0->active = 1;
}

static void poffin_cooking_0223F458(PoffinCookingArrow *param0)
{
    if (param0->active == 0) {
        return;
    }

    if (param0->frame == 0) {
        Sprite_SetDrawFlag(param0->sprite, TRUE);
    } else if (param0->frame == 8) {
        Sprite_SetDrawFlag(param0->sprite, FALSE);
    } else if (param0->frame == (8 * 2)) {
        param0->frame = 0;
        return;
    }

    param0->frame++;
}

void poffin_cooking_0223F494(PoffinCookingSparkleManager *param0, int param1)
{
    memset(param0, 0, sizeof(PoffinCookingSparkleManager));
    param0->maxSparkles = param1;
}

void poffin_cooking_0223F4AC(PoffinCookingSparkleManager *param0)
{
    GF_ASSERT(param0->loaded == 0);
    memset(param0, 0, sizeof(PoffinCookingSparkleManager));
}

void poffin_cooking_0223F4CC(PoffinCookingSparkleManager *param0, PoffinCookingSpriteManager *param1, PoffinCookingSpriteSet *param2, u32 param3)
{
    int v0;

    for (v0 = 0; v0 < 32; v0++) {
        param0->sparkles[v0].sprite = poffin_cooking_0223D9A8(param1, &param2[1], 0, 0, 0, 5, param3);
        Sprite_SetDrawFlag(param0->sparkles[v0].sprite, FALSE);
    }

    param0->loaded = 1;
}

void poffin_cooking_0223F510(PoffinCookingSparkleManager *param0)
{
    int v0;

    for (v0 = 0; v0 < 32; v0++) {
        Sprite_Delete(param0->sparkles[v0].sprite);
    }

    param0->loaded = 0;
}

void poffin_cooking_0223F52C(PoffinCookingSparkleManager *param0)
{
    int v0;

    for (v0 = 0; v0 < 32; v0++) {
        poffin_cooking_0223F670(&param0->sparkles[v0]);
    }
}

void poffin_cooking_0223F544(PoffinCookingSparkleManager *param0, int param1, int param2)
{
    PoffinCookingSparkle *v0;
    u32 v1;
    fx32 v2, v3;
    fx32 v4, v5;
    int v6;

    v1 = FX_Atan2Idx(param1 - 128, param2 - 96);
    v2 = FX_Mul(FX_CosIdx(v1), FX32_CONST(16));
    v3 = FX_Mul(FX_SinIdx(v1), FX32_CONST(16));
    v4 = FX_Mul(FX_CosIdx(v1), FX32_CONST(1));
    v5 = FX_Mul(FX_SinIdx(v1), FX32_CONST(1));
    v0 = poffin_cooking_0223F650(param0);

    if (v0) {
        poffin_cooking_0223F6CC(v0, param0->nextSparkle, param1 * FX32_ONE, param2 * FX32_ONE, (128 * FX32_ONE) + v2, (96 * FX32_ONE) + v3, v4, v5);
    }

    v0 = poffin_cooking_0223F650(param0);

    if (v0) {
        poffin_cooking_0223F6CC(v0, param0->nextSparkle, param1 * FX32_ONE, param2 * FX32_ONE, (128 * FX32_ONE) - v2, (96 * FX32_ONE) - v3, -v4, -v5);
    }

    param0->nextSparkle = (param0->nextSparkle + 1) % param0->maxSparkles;
}

static PoffinCookingSparkle *poffin_cooking_0223F650(PoffinCookingSparkleManager *param0)
{
    int v0;

    for (v0 = 0; v0 < 32; v0++) {
        if (param0->sparkles[v0].active == 0) {
            return &param0->sparkles[v0];
        }
    }

    return NULL;
}

static void poffin_cooking_0223F670(PoffinCookingSparkle *param0)
{
    BOOL v0;

    if (param0->active == 0) {
        return;
    }

    if (param0->motionDone == 0) {
        param0->motionDone = poffin_cooking_0223DA94(&param0->motionX);
        poffin_cooking_0223DA94(&param0->motionY);
        param0->position.x = param0->motionX.current;
        param0->position.y = param0->motionY.current;
        Sprite_SetPosition(param0->sprite, &param0->position);
    }

    if (param0->motionDone == 1) {
        poffin_cooking_0223F6B4(param0);
    }
}

static void poffin_cooking_0223F6B4(PoffinCookingSparkle *param0)
{
    if (param0->active == 0) {
        return;
    }

    Sprite_SetDrawFlag(param0->sprite, FALSE);
    param0->active = 0;
}

static void poffin_cooking_0223F6CC(PoffinCookingSparkle *param0, int param1, fx32 param2, fx32 param3, fx32 param4, fx32 param5, fx32 param6, fx32 param7)
{
    poffin_cooking_0223DA34(&param0->motionX, param2, param4, param6, 16);
    poffin_cooking_0223DA34(&param0->motionY, param3, param5, param7, 16);

    param0->position.x = param2;
    param0->position.y = param3;

    Sprite_SetDrawFlag(param0->sprite, TRUE);
    Sprite_SetAnim(param0->sprite, param1);
    Sprite_RestartAnim(param0->sprite);
    Sprite_SetAnimateFlag(param0->sprite, 1);
    Sprite_SetExplicitPriority(param0->sprite, 2);

    param0->active = 1;
    param0->motionDone = 0;
}

void poffin_cooking_0223F730(PoffinCookingPoffinSprite *param0, int param1, int param2, int param3, int param4)
{
    param0->spriteManager = PoffinSpriteManager_New(param4, 1, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 2);
    param0->sprite = PoffinSprite_New(param0->spriteManager, param3, param1, param2, 0, 0, 0, 0);
}

void poffin_cooking_0223F770(PoffinCookingPoffinSprite *param0)
{
    PoffinSprite_Free(param0->spriteManager, param0->sprite);
    PoffinSpriteManager_Free(param0->spriteManager);
}

void poffin_cooking_0223F784(PoffinCookingPoffinSprite *param0)
{
    PoffinSpriteManager_DrawSprites(param0->spriteManager);
}

void poffin_cooking_0223F790(PoffinCookingYesNoMenu *param0, enum HeapID heapID, BgConfig *param2)
{
    param0->menu = YesNoTouchMenu_New(heapID);
    param0->bgConfig = param2;
}

void poffin_cooking_0223F7A4(PoffinCookingYesNoMenu *param0)
{
    YesNoTouchMenu_Free(param0->menu);
}

void poffin_cooking_0223F7B0(PoffinCookingYesNoMenu *param0)
{
    YesNoTouchMenuParams v0;

    v0.bgConfig = param0->bgConfig;
    v0.bgLayer = BG_LAYER_MAIN_2;
    v0.baseTile = (((1 + (18 + 12)) + 9) + (27 * 5));
    v0.palette = 5;
    v0.tilemapLeft = 24;
    v0.tilemapTop = 8;

    YesNoTouchMenu_InitWithParams(param0->menu, &v0);
}

u32 poffin_cooking_0223F7DC(PoffinCookingYesNoMenu *param0)
{
    u32 v0 = YesNoTouchMenu_ProcessInput(param0->menu);

    if (v0 != YES_NO_TOUCH_MENU_NOTHING_CHOSEN) {
        YesNoTouchMenu_Reset(param0->menu);
    }

    return v0;
}
