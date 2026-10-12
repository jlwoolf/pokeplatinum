#ifndef POKEPLATINUM_BOX_BUTTON_SPRITE_H
#define POKEPLATINUM_BOX_BUTTON_SPRITE_H

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_button_sprite.h"

#include "narc.h"
#include "sprite.h"

BOOL BoxButtonSprite_Load(BoxButtonSprite *param0, BoxGraphics *param1, const BoxApplication *param2, SpriteList *param3, NARC *param4);
void BoxButtonSprite_Init(BoxButtonSprite *param0, NARC *param1);
void BoxButtonSprite_Free(BoxButtonSprite *param0);
void BoxButtonSprite_SetState(BoxButtonSprite *param0, int param1);

#endif // POKEPLATINUM_BOX_BUTTON_SPRITE_H
