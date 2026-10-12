#include "field_events/field_event_dispatch.h"

#include <nitro.h>
#include <string.h>

#include "field/field_system.h"
#include "overlay005/struct_ov5_021D1BEC_decl.h"
#include "field_events/field_events_0223E140.h"

#include "camera.h"

static UnkStruct_ov5_021D1BEC *sFieldEvent;

BOOL FieldEventDispatch_ProcessCommand(FieldSystem *fieldSystem, int param1)
{
    VecFx32 v0;
    CameraAngle v1;

    switch (param1) {
    case 0:
        sFieldEvent = ClimaxSequence_New(fieldSystem);
        break;
    case 1:
        if (ClimaxSequence_IsFinished(sFieldEvent)) {
            ClimaxSequence_Delete(sFieldEvent);
            return 1;
        } else {
            return 0;
        }
        break;
    case 2:
        sFieldEvent = ClimaxObjectEffect_New(fieldSystem);
        break;
    case 3:
        ClimaxObjectEffect_Delete(sFieldEvent);
        break;
    case 4:
        sFieldEvent = ClimaxActor_New(fieldSystem);
        break;
    case 5:
        ClimaxActor_Finish(sFieldEvent);
        break;
    case 6:
        if (ClimaxActor_GetState(sFieldEvent) == 6) {
            ClimaxActor_Delete(sFieldEvent);
            return 1;
        } else {
            return 0;
        }
        break;
    case 7:
        sFieldEvent = ClimaxScene_New(fieldSystem, 0);
        break;
    case 8:
        sFieldEvent = ClimaxScene_New(fieldSystem, 1);
        break;
    case 9:
        sFieldEvent = ClimaxScene_New(fieldSystem, 2);
        break;
    default:
        GF_ASSERT(FALSE);
    }

    return 0;
}
