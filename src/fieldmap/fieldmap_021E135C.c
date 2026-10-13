#include "fieldmap/fieldmap_021E135C.h"

#include <nitro.h>
#include <nitro/os.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "field/field_system.h"
#include "fieldmap/fieldmap_021ECC20.h"

#include "heap.h"
#include "map_object.h"
#include "player_avatar.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sys_task.h"
#include "sys_task_manager.h"

typedef struct {
    FieldSystem *fieldSystem;
    BOOL *done;
    int state;
    int timer;
    int direction;
} WarpAnimation;

static void FieldMap_021E135C(WarpAnimation *param0)
{
    switch (param0->direction) {
    case 0:
        param0->direction = 2;
        break;
    case 2:
        param0->direction = 1;
        break;
    case 1:
        param0->direction = 3;
        break;
    case 3:
        param0->direction = 0;
        break;
    }

    PlayerAvatar_TryFace(param0->fieldSystem->playerAvatar, param0->direction);
}

static void FieldMap_021E139C(SysTask *param0, void *param1)
{
    WarpAnimation *v0 = param1;
    MapObject *v1 = PlayerAvatar_GetMapObject(v0->fieldSystem->playerAvatar);
    VecFx32 v2;

    switch (v0->state) {
    case 0:
        v0->state = 1;
        Sound_PlayEffect(SEQ_SE_DP_TELE2_sseq);
    case 1:
        if (v0->timer % 2) {
            FieldMap_021E135C(v0);
        }

        MapObject_GetSpritePosOffset(v1, &v2);
        v2.y = ((FX32_ONE * 2.2) + ((FX32_ONE / 2) * v0->timer)) * v0->timer;

        MapObject_SetSpritePosOffset(v1, &v2);
        v0->timer++;

        if (v0->timer == 20) {
            StartScreenFade(FADE_SUB_THEN_MAIN, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_FIELD1);
        } else if ((v0->timer > 20) && IsScreenFadeDone()) {
            *v0->done = 1;
            Heap_Free(v0);
            SysTask_Done(param0);
        } else {
            break;
        }
    }
}

static void FieldMap_021E1470(SysTask *param0, void *param1)
{
    WarpAnimation *v0 = param1;
    MapObject *v1 = PlayerAvatar_GetMapObject(v0->fieldSystem->playerAvatar);
    VecFx32 v2;
    int v3;

    switch (v0->state) {
    case 0: {
        MapObject_SetPauseMovementOff(v1);
        MapObject_GetSpritePosOffset(v1, &v2);
        v3 = (20 - v0->timer);
        v2.y = ((FX32_ONE * 2.2) + ((FX32_ONE / 2) * v3)) * v3;
        MapObject_SetSpritePosOffset(v1, &v2);
        MapObject_Draw(v1);
    }

        Sound_PlayEffect(SEQ_SE_DP_TELE2_sseq);
        v0->state = 1;
    case 1:
        if (v0->timer % 2) {
            FieldMap_021E135C(v0);
        }

        MapObject_GetSpritePosOffset(v1, &v2);
        v3 = (20 - v0->timer);
        v2.y = ((FX32_ONE * 2.2) + ((FX32_ONE / 2) * v3)) * v3;
        MapObject_SetSpritePosOffset(v1, &v2);
        v0->timer++;

        if (v0->timer == 2) {
            StartScreenFade(FADE_MAIN_THEN_SUB, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_FIELD1);
        }

        if (v0->timer > 20) {
            v0->state = 2;
        }
        break;
    case 2:
        if (IsScreenFadeDone()) {
            PlayerAvatar_TryFace(v0->fieldSystem->playerAvatar, 1);
            *v0->done = 1;
            Heap_Free(v0);
            SysTask_Done(param0);
        }
        break;
    }
}

void FieldSystem_StartWarpAnimation(FieldSystem *fieldSystem, BOOL param1, BOOL *param2)
{
    WarpAnimation *v0 = Heap_AllocAtEnd(HEAP_ID_FIELD1, sizeof(WarpAnimation));

    MI_CpuClear8(v0, sizeof(WarpAnimation));

    v0->fieldSystem = fieldSystem;
    v0->done = param2;
    v0->direction = PlayerAvatar_GetFacingDir(fieldSystem->playerAvatar);

    if (param1) {
        SysTask_Start(FieldMap_021E139C, v0, 100);
    } else {
        SysTask_Start(FieldMap_021E1470, v0, 100);
    }
}
