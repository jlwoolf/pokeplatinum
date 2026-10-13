#ifndef POKEPLATINUM_STRUCT_FIELD_EFFECT_H
#define POKEPLATINUM_STRUCT_FIELD_EFFECT_H

#include "field_events/field_effect_funcptr.h"

typedef struct {
    u32 priority;
    u16 dataSize;
    FieldEffectFunc init;
    FieldEffectFunc free;
    FieldEffectFunc update;
    FieldEffectFunc draw;
} FieldEffectTemplate;

#endif // POKEPLATINUM_STRUCT_FIELD_EFFECT_H
