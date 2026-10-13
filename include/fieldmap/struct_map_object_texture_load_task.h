#ifndef POKEPLATINUM_STRUCT_MAP_OBJECT_TEXTURE_LOAD_TASK_H
#define POKEPLATINUM_STRUCT_MAP_OBJECT_TEXTURE_LOAD_TASK_H

#include "resource_collection.h"

typedef struct {
    u32 narcMemberIdx;
    int textureID;
    int isDynamic;
    TextureResourceManager *textureManager;
} MapObjectTextureLoadTask;

#endif // POKEPLATINUM_STRUCT_MAP_OBJECT_TEXTURE_LOAD_TASK_H
