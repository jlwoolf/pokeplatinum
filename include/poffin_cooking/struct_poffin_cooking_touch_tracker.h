#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_TOUCH_TRACKER_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_TOUCH_TRACKER_H

typedef struct {
    int x;
    int y;
    int prevX;
    int prevY;
    s32 delta;
    BOOL held;
} PoffinCookingTouchTracker;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_TOUCH_TRACKER_H
