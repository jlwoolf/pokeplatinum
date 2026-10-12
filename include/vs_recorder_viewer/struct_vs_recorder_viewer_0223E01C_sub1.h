#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223E01C_SUB1_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223E01C_SUB1_H

#include "message.h"

typedef struct {
    int entryCount;
    int pokedexCount;
    u16 *pokedex;
    MessageLoader *messageLoader;
    BOOL active;
} VsRecorderViewerRankingMessageBox;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223E01C_SUB1_H
