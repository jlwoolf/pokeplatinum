#include "wifi_2d_char/wifi_2d_char_0222D160.h"

#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/wifi_2d_char_0222BE18.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D160.h"

void WiFi2DCharViewOffset_SetFromObject(WiFi2DCharViewOffset *param0, const WiFi2DCharObject *param1)
{
    WiFi2DCharPosition v0;

    v0 = WiFi2DCharObject_GetInterpolatedPosition(param1);
    WiFi2DCharViewOffset_Set(param0, v0.y - 96, v0.x - 112);
}

void WiFi2DCharViewOffset_Reset(WiFi2DCharViewOffset *param0)
{
    memset(param0, 0, sizeof(WiFi2DCharViewOffset));
}

void WiFi2DCharViewOffset_Set(WiFi2DCharViewOffset *param0, s16 param1, s16 param2)
{
    param0->x = param1;
    param0->y = param2;
}

s16 WiFi2DCharViewOffset_GetX(const WiFi2DCharViewOffset *param0)
{
    return param0->x;
}

s16 WiFi2DCharViewOffset_GetY(const WiFi2DCharViewOffset *param0)
{
    return param0->y;
}
