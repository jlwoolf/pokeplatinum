#include "image_clip_app/image_clip_app_0225AF44.h"

#include <nitro.h>
#include <string.h>

#include "image_clip_app/image_clip_app_022597BC.h"
#include "image_clip_app/struct_image_clip_app_02257964.h"
#include "image_clip_app/struct_image_clip_app_0225AF44.h"
#include "image_clip_app/struct_image_clip_app_0225AF68.h"

void PhotoRendererBg_Init(PhotoRendererBg *param0, const PhotoRenderer *param1, int param2)
{
    PhotoRendererBgTemplate v0;

    param0->renderer = param1;

    v0.bg = &param1->context.bg;
    v0.firstFrameIndex = (param1->context.backdropIndex) * 4 + 134 + 3;
    v0.frameDuration = 16;
    v0.heapID = param2;

    ImageClipBg_InitBackgroundAnimation(&param0->animation, &v0);
}

void PhotoRendererBg_Update(PhotoRendererBg *param0)
{
    ImageClipBg_UpdateBackgroundAnimation(&param0->animation, 1);
}

void PhotoRendererBg_Free(PhotoRendererBg *param0)
{
    ImageClipBg_StopBackgroundAnimation(&param0->animation);
    memset(param0, 0, sizeof(PhotoRendererBg));
}
