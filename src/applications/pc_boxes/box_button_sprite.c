#include "applications/pc_boxes/box_button_sprite.h"

#include <nitro.h>
#include <string.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_button_sprite.h"

#include "graphics.h"
#include "heap.h"
#include "narc.h"
#include "sprite.h"

BOOL BoxButtonSprite_Load(BoxButtonSprite *param0, BoxGraphics *param1, const BoxApplication *param2, SpriteList *param3, NARC *param4)
{
    param0->unk_44 = param1;
    param0->unk_3C = param3;
    param0->unk_40 = param2;
    param0->unk_00 = param3;
    param0->unk_04 = NULL;
    param0->unk_08 = Graphics_GetCellBankFromOpenNARC(param4, 10, 1, &(param0->unk_10), HEAP_ID_BOX_GRAPHICS);
    param0->unk_0C = Graphics_GetAnimBankFromOpenNARC(param4, 11, 1, &(param0->unk_14), HEAP_ID_BOX_GRAPHICS);

    if ((param0->unk_08 == NULL) || (param0->unk_0C == NULL)) {
        return 0;
    }

    return 1;
}

void BoxButtonSprite_Init(BoxButtonSprite *param0, NARC *param1)
{
    SpriteResourcesHeader v0;

    NNS_G2dInitImageProxy(&(param0->unk_18));

    Graphics_LoadImageMappingFromOpenNARC(param1, 9, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 1256 * 0x20, 10, &(param0->unk_18));
    BoxGraphics_InitSpriteResources(&v0, &(param0->unk_18), BoxGraphics_GetPaletteProxy(param0->unk_44), param0->unk_10, param0->unk_14, 2);
    param0->unk_04 = BoxGraphics_CreateSprite(param0->unk_00, &v0, 183 + BoxGraphics_GetCompareXOffset(param0->unk_44), 176, 44, NNS_G2D_VRAM_TYPE_2DMAIN);
    Sprite_SetExplicitPalette(param0->unk_04, 1);
}

void BoxButtonSprite_Free(BoxButtonSprite *param0)
{
    if (param0->unk_08 != NULL) {
        Heap_Free(param0->unk_08);
        param0->unk_08 = NULL;
    }

    if (param0->unk_0C != NULL) {
        Heap_Free(param0->unk_0C);
        param0->unk_0C = NULL;
    }
}

void BoxButtonSprite_SetState(BoxButtonSprite *param0, int param1)
{
    switch (param1) {
    case 0:
        Sprite_SetAnim(param0->unk_04, 0);
        break;
    case 1:
        Sprite_SetAnim(param0->unk_04, 1);
        break;
    case 2:
        Sprite_SetAnim(param0->unk_04, 2);
        break;
    }
}
