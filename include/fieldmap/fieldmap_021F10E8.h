#ifndef POKEPLATINUM_FIELDMAP_021F10E8_H
#define POKEPLATINUM_FIELDMAP_021F10E8_H

#include <nitro/fx/fx.h>

#include "struct_decls/map_object.h"

#include "fieldmap/field_effect_manager.h"

#include "overworld_anim_manager.h"
#include "simple3d.h"

void *FieldMap_021F10E8(FieldEffectManager *param0);
void FieldMap_021F10FC(void *param0);
void FieldMap_021F1188(FieldEffectManager *param0, u32 param1);
void FieldMap_021F11C0(FieldEffectManager *param0, u32 param1, u32 param2);
Simple3DRenderObj *FieldMap_021F11FC(FieldEffectManager *param0, u32 param1);
OverworldAnimManager *FieldMap_021F121C(const MapObject *param0, const VecFx32 *param1);
void FieldEffect_InitRenderObject(FieldEffectManager *param0);

#endif // POKEPLATINUM_FIELDMAP_021F10E8_H
