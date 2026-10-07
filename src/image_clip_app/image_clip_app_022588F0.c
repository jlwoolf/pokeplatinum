#include "image_clip_app/image_clip_app_022588F0.h"

#include <nitro.h>
#include <string.h>

#include "image_clip_app/struct_image_clip_app_02258A48.h"

#include "system.h"

static void PhotoRendererController_DefaultCallback(PhotoRendererController *param0);

void PhotoRendererController_InitInput(PhotoRendererController *param0)
{
    memset(param0, 0, sizeof(PhotoRendererController));

    param0->unk_04 = PhotoRendererController_DefaultCallback;
    param0->unk_08 = PhotoRendererController_DefaultCallback;
    param0->unk_0C = PhotoRendererController_DefaultCallback;
}

void PhotoRendererController_UpdateInput(PhotoRendererController *param0)
{
    if (gSystem.touchPressed) {
        param0->unk_04(param0);
    } else {
        if (gSystem.touchHeld) {
            param0->unk_0C(param0);
        } else {
            if (param0->unk_18) {
                param0->unk_08(param0);
            }
        }
    }

    param0->unk_14 = gSystem.touchX;
    param0->unk_16 = gSystem.touchY;
    param0->unk_18 = gSystem.touchHeld;
}

static void PhotoRendererController_DefaultCallback(PhotoRendererController *param0)
{
    return;
}
