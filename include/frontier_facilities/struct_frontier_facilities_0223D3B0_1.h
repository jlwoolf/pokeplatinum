#ifndef POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223D3B0_1_H
#define POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223D3B0_1_H

#include "sprite_system.h"

// The eight managed-sprite slots owned by FrontierGraphics: the sprites,
// their resource IDs, a visibility bitmask, and the loaded resource IDs.
typedef struct {
    ManagedSprite *sprites[8];
    u16 resourceIDs[8];
    u32 visibleMask;
    u16 loadedResourceIDs[8];
} FrontierFacilitiesSpriteSlots;

#endif // POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223D3B0_1_H
