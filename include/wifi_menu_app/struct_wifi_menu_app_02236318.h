#ifndef POKEPLATINUM_STRUCT_WIFI_MENU_APP_02236318_H
#define POKEPLATINUM_STRUCT_WIFI_MENU_APP_02236318_H

#include <nnsys.h>

typedef struct {
    void *heapData;
    NNSG2dPaletteData *paletteData;
    u8 enabledMask;
    u8 frameIndex;
    s16 frameTimer;
    u8 flashIndex;
    u8 flashStep;
    s16 flashTimer;
    u8 flashRequested;
    u8 padding[3];
} WiFiMenuAppPalette;

#endif // POKEPLATINUM_STRUCT_WIFI_MENU_APP_02236318_H
