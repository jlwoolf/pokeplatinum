#ifndef POKEPLATINUM_STRUCT_MAP_OBJECT_TEXTURE_MANAGER_H
#define POKEPLATINUM_STRUCT_MAP_OBJECT_TEXTURE_MANAGER_H

#include "resource_collection.h"

typedef struct {
    vu32 uploaded;
    int textureID;
    TextureResourceManager *textureManager;
} MapObjectTextureManager;

#endif // POKEPLATINUM_STRUCT_MAP_OBJECT_TEXTURE_MANAGER_H
