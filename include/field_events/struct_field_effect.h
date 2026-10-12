#ifndef POKEPLATINUM_STRUCT_FIELD_EFFECT_H
#define POKEPLATINUM_STRUCT_FIELD_EFFECT_H

#include "field_events/field_effect_funcptr.h"

typedef struct {
    u32 unk_00;
    u16 unk_04;
    FieldEffectFunc unk_08;
    FieldEffectFunc unk_0C;
    FieldEffectFunc unk_10;
    FieldEffectFunc unk_14;
} FieldEffectTemplate;

#endif // POKEPLATINUM_STRUCT_FIELD_EFFECT_H
