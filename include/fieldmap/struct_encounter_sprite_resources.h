#ifndef POKEPLATINUM_STRUCT_ENCOUNTER_SPRITE_RESOURCES_H
#define POKEPLATINUM_STRUCT_ENCOUNTER_SPRITE_RESOURCES_H

#include "sprite.h"
#include "sprite_resource.h"

typedef struct {
    SpriteResource *resources[4];
    SpriteResourcesHeader header;
} EncounterSpriteResources;

#endif // POKEPLATINUM_STRUCT_ENCOUNTER_SPRITE_RESOURCES_H
