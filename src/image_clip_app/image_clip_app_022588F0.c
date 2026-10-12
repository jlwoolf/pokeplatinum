#include "image_clip_app/image_clip_app_022588F0.h"

#include <nitro.h>
#include <string.h>

#include "image_clip_app/struct_image_clip_app_02258A48.h"

#include "system.h"

static void PhotoRendererController_DefaultCallback(PhotoRendererController *param0);

void PhotoRendererController_InitInput(PhotoRendererController *param0)
{
    memset(param0, 0, sizeof(PhotoRendererController));

    param0->onTouchDown = PhotoRendererController_DefaultCallback;
    param0->onTouchUp = PhotoRendererController_DefaultCallback;
    param0->onTouchDrag = PhotoRendererController_DefaultCallback;
}

void PhotoRendererController_UpdateInput(PhotoRendererController *param0)
{
    if (gSystem.touchPressed) {
        param0->onTouchDown(param0);
    } else {
        if (gSystem.touchHeld) {
            param0->onTouchDrag(param0);
        } else {
            if (param0->wasTouchHeld) {
                param0->onTouchUp(param0);
            }
        }
    }

    param0->touchX = gSystem.touchX;
    param0->touchY = gSystem.touchY;
    param0->wasTouchHeld = gSystem.touchHeld;
}

static void PhotoRendererController_DefaultCallback(PhotoRendererController *param0)
{
    return;
}
