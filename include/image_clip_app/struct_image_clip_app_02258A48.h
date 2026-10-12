#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02258A48_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02258A48_H

typedef struct PhotoRendererController {
    void *data;
    void (*onTouchDown)(struct PhotoRendererController *param0);
    void (*onTouchUp)(struct PhotoRendererController *param0);
    void (*onTouchDrag)(struct PhotoRendererController *param0);
    void (*onFree)(struct PhotoRendererController *param0);
    s16 touchX;
    s16 touchY;
    u8 wasTouchHeld;
    u8 padding[3];
} PhotoRendererController;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02258A48_H
