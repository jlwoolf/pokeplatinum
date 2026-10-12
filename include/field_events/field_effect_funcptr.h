#ifndef POKEPLATINUM_FIELD_EFFECT_FUNCPTR_H
#define POKEPLATINUM_FIELD_EFFECT_FUNCPTR_H

#include "field/field_system_decl.h"
#include "fieldmap/struct_field_effect_decl.h"

typedef void (*FieldEffectFunc)(FieldEffect *, FieldSystem *, void *);

#endif // POKEPLATINUM_FIELD_EFFECT_FUNCPTR_H
