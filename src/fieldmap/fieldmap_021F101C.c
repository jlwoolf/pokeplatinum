#include "fieldmap/fieldmap_021F101C.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_020711C8.h"

#include "field/field_system.h"
#include "fieldmap/fieldmap_021F007C.h"
#include "fieldmap/struct_sweet_scent_task_decl.h"
#include "field_events/hm_cut_in.h"

#include "field_task.h"
#include "heap.h"
#include "player_avatar.h"
#include "sys_task_manager.h"

typedef struct {
    SysTask *unk_00;
    SweetScentTask *unk_04;
} SweetScentCutInTask;

BOOL FieldMap_021F101C(FieldTask *param0)
{
    FieldSystem *fieldSystem = FieldTask_GetFieldSystem(param0);
    FieldMoveMon *v1 = FieldTask_GetEnv(param0);
    int *v2 = FieldTask_GetState(param0);
    SweetScentCutInTask *v3 = v1->taskData;

    switch (*v2) {
    case 0:
        v1->taskData = Heap_AllocAtEnd(HEAP_ID_FIELD2, sizeof(SweetScentCutInTask));
        (*v2)++;
        break;
    case 1: {
        int v4 = FieldMap_021F0484();

        v3->unk_04 = Heap_AllocAtEnd(HEAP_ID_FIELD2, v4);
        memset(v3->unk_04, 0, v4);
    }
        (*v2)++;
        break;
    case 2: {
        int v5 = PlayerAvatar_GetGender(fieldSystem->playerAvatar);
        v3->unk_00 = HMCutIn_StartTask(fieldSystem, 0, v1->mon, v5);
    }
        (*v2)++;
        break;
    case 3:
        if (HMCutIn_IsFinished(v3->unk_00)) {
            HMCutIn_EndTask(v3->unk_00);
            (*v2)++;
        }
        break;
    case 4:
        FieldTask_InitCall(param0, FieldMap_021F0488, v3->unk_04);
        (*v2)++;
        break;
    case 5:
        Heap_Free(v1->taskData);
        Heap_Free(v1);
        return 1;
    }

    return 0;
}
