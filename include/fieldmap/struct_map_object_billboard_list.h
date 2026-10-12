#ifndef POKEPLATINUM_STRUCT_MAP_OBJECT_BILLBOARD_LIST_H
#define POKEPLATINUM_STRUCT_MAP_OBJECT_BILLBOARD_LIST_H

#include "struct_decls/map_object.h"

#include "billboard.h"

typedef struct {
    int unk_00;
    MapObject *unk_04;
    Billboard **unk_08;
} MapObjectBillboardList;

#endif // POKEPLATINUM_STRUCT_MAP_OBJECT_BILLBOARD_LIST_H
