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
    param0->boxGraphics = param1;
    param0->buttonSpriteList = param3;
    param0->boxApp = param2;
    param0->spriteList = param3;
    param0->sprite = NULL;
    param0->cellBank = Graphics_GetCellBankFromOpenNARC(param4, 10, 1, &(param0->cellBankData), HEAP_ID_BOX_GRAPHICS);
    param0->animBank = Graphics_GetAnimBankFromOpenNARC(param4, 11, 1, &(param0->animBankData), HEAP_ID_BOX_GRAPHICS);

    if ((param0->cellBank == NULL) || (param0->animBank == NULL)) {
        return 0;
    }

    return 1;
}

void BoxButtonSprite_Init(BoxButtonSprite *param0, NARC *param1)
{
    SpriteResourcesHeader v0;

    NNS_G2dInitImageProxy(&(param0->imageProxy));

    Graphics_LoadImageMappingFromOpenNARC(param1, 9, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 1256 * 0x20, 10, &(param0->imageProxy));
    BoxGraphics_InitSpriteResources(&v0, &(param0->imageProxy), BoxGraphics_GetPaletteProxy(param0->boxGraphics), param0->cellBankData, param0->animBankData, 2);
    param0->sprite = BoxGraphics_CreateSprite(param0->spriteList, &v0, 183 + BoxGraphics_GetCompareXOffset(param0->boxGraphics), 176, 44, NNS_G2D_VRAM_TYPE_2DMAIN);
    Sprite_SetExplicitPalette(param0->sprite, 1);
}

void BoxButtonSprite_Free(BoxButtonSprite *param0)
{
    if (param0->cellBank != NULL) {
        Heap_Free(param0->cellBank);
        param0->cellBank = NULL;
    }

    if (param0->animBank != NULL) {
        Heap_Free(param0->animBank);
        param0->animBank = NULL;
    }
}

void BoxButtonSprite_SetState(BoxButtonSprite *param0, int param1)
{
    switch (param1) {
    case 0:
        Sprite_SetAnim(param0->sprite, 0);
        break;
    case 1:
        Sprite_SetAnim(param0->sprite, 1);
        break;
    case 2:
        Sprite_SetAnim(param0->sprite, 2);
        break;
    }
}
