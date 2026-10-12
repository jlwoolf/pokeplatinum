#ifndef POKEPLATINUM_STRUCT_PHOTO_VIEWER_ARGS_H
#define POKEPLATINUM_STRUCT_PHOTO_VIEWER_ARGS_H

#include "struct_defs/image_clips.h"

typedef struct {
    ImageClips *imageClips;
    u32 slot;
    u32 photoType;
} PhotoViewerArgs;

#endif // POKEPLATINUM_STRUCT_PHOTO_VIEWER_ARGS_H
