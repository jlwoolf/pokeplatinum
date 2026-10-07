#include "wifi_2d_char/wifi_2d_char_0222CA88.h"

#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/wifi_2d_char_0222BCE8.h"
#include "wifi_2d_char/wifi_2d_char_0222BE18.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BCE8_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BE18_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CCB8.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D894.h"

static BOOL WiFi2DCharAI_State0(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4);
static BOOL WiFi2DCharAI_State1(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4);
static BOOL WiFi2DCharAI_State2(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4);
static BOOL WiFi2DCharAI_State3(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4);
static BOOL WiFi2DCharAI_State4(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4);
static BOOL WiFi2DCharAI_State5(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4);
static BOOL WiFi2DCharAI_State6(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4);
static BOOL WiFi2DCharAI_State7(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4);
static BOOL WiFi2DCharAI_IsTileBlocked(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, int param2);
static BOOL WiFi2DCharAI_IsObjectAtOffset(const WiFi2DCharObject *param0, const WiFi2DCharObjectManager *param1, int param2);
static void WiFi2DCharAI_SetMoveRequest(WiFi2DCharMoveRequest *param0, const WiFi2DCharObject *param1, int param2, u32 param3, int param4);

BOOL WiFi2DCharAI_ChooseMove(const WiFi2DCharGrid *param0, const WiFi2DCharObjectManager *param1, const WiFi2DCharEvent *param2, WiFi2DCharMoveRequest *param3)
{
    const WiFi2DCharObject *v0;
    static BOOL (*const v1[12])(const WiFi2DCharObject *, const WiFi2DCharGrid *, const WiFi2DCharObjectManager *, const WiFi2DCharEvent *, WiFi2DCharMoveRequest *) = {
        WiFi2DCharAI_State0,
        WiFi2DCharAI_State1,
        WiFi2DCharAI_State2,
        WiFi2DCharAI_State3,
        WiFi2DCharAI_State4,
        WiFi2DCharAI_State5,
        WiFi2DCharAI_State6,
        WiFi2DCharAI_State2,
        WiFi2DCharAI_State7,
        WiFi2DCharAI_State7,
        WiFi2DCharAI_State7,
        WiFi2DCharAI_State7,
    };

    BOOL v2;

    GF_ASSERT(param0);
    GF_ASSERT(param1);
    GF_ASSERT(param2);
    GF_ASSERT(param3);

    v0 = WiFi2DCharObjectManager_FindObjectByIDConst(param1, param2->unk_03);
    GF_ASSERT(v0);

    v2 = v1[param2->unk_00](v0, param0, param1, param2, param3);
    return v2;
}

static BOOL WiFi2DCharAI_State0(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4)
{
    s32 v0 = WiFi2DCharObject_GetField(param0, 5);

    if ((v0 == 0) || (v0 == 4)) {
        WiFi2DCharAI_SetMoveRequest(param4, param0, param3->unk_00, param3->unk_03, param3->unk_02);
        return 1;
    }

    return 0;
}

static BOOL WiFi2DCharAI_State1(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4)
{
    s32 v0;
    s32 v1;

    v0 = WiFi2DCharObject_GetField(param0, 5);
    v1 = WiFi2DCharObject_GetField(param0, 6);

    if (v0 == 0) {
        if (v1 != param3->unk_02) {
            WiFi2DCharAI_SetMoveRequest(param4, param0, param3->unk_00, param3->unk_03, param3->unk_02);
            return 1;
        }
    }

    return 0;
}

static BOOL WiFi2DCharAI_State2(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4)
{
    s32 v0;
    BOOL v1;
    s32 v2;

    do {
        v0 = WiFi2DCharObject_GetField(param0, 5);

        if (v0 != 0) {
            break;
        }

        v1 = WiFi2DCharAI_IsTileBlocked(param0, param1, param3->unk_02);

        if (v1 == 1) {
            break;
        }

        v1 = WiFi2DCharAI_IsObjectAtOffset(param0, param2, param3->unk_02);

        if (v1 == 1) {
            break;
        }

        WiFi2DCharAI_SetMoveRequest(param4, param0, param3->unk_00, param3->unk_03, param3->unk_02);
        return 1;
    } while (0);

    if (v0 == 0) {
        v2 = WiFi2DCharObject_GetField(param0, 10);

        if (v2 >= 8) {
            WiFi2DCharAI_SetMoveRequest(param4, param0, 5, param3->unk_03, param3->unk_02);
            return 1;
        }
    }

    return 0;
}

static BOOL WiFi2DCharAI_State3(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4)
{
    return WiFi2DCharAI_State2(param0, param1, param2, param3, param4);
}

static BOOL WiFi2DCharAI_State4(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4)
{
    s32 v0 = WiFi2DCharObject_GetField(param0, 5);

    if (v0 == 0) {
        WiFi2DCharAI_SetMoveRequest(param4, param0, param3->unk_00, param3->unk_03, param3->unk_02);
        return 1;
    }

    return 0;
}

static BOOL WiFi2DCharAI_State5(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4)
{
    GF_ASSERT(FALSE);
    return 0;
}

static BOOL WiFi2DCharAI_State6(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4)
{
    return WiFi2DCharAI_State2(param0, param1, param2, param3, param4);
}

static BOOL WiFi2DCharAI_State7(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, const WiFi2DCharObjectManager *param2, const WiFi2DCharEvent *param3, WiFi2DCharMoveRequest *param4)
{
    s32 v0 = WiFi2DCharObject_GetField(param0, 5);

    if (v0 == 0) {
        WiFi2DCharAI_SetMoveRequest(param4, param0, param3->unk_00, param3->unk_03, param3->unk_02);
        return 1;
    }

    return 0;
}

static BOOL WiFi2DCharAI_IsTileBlocked(const WiFi2DCharObject *param0, const WiFi2DCharGrid *param1, int param2)
{
    WiFi2DCharPosition v0;

    v0 = WiFi2DCharObject_GetPosition(param0);
    v0 = WiFi2DCharPosition_OffsetByDirection(v0, param2);

    return WiFi2DCharGrid_IsTileBlocked(param1, (v0.x) / 16, (v0.y) / 16);
}

static BOOL WiFi2DCharAI_IsObjectAtOffset(const WiFi2DCharObject *param0, const WiFi2DCharObjectManager *param1, int param2)
{
    const WiFi2DCharObject *v0 = WiFi2DCharObjectManager_FindObjectAtOffset(param0, param1, param2);

    if (v0 == NULL) {
        return 0;
    }

    return 1;
}

static void WiFi2DCharAI_SetMoveRequest(WiFi2DCharMoveRequest *param0, const WiFi2DCharObject *param1, int param2, u32 param3, int param4)
{
    param0->unk_00 = WiFi2DCharObject_GetPosition(param1);
    param0->unk_04 = param2;
    param0->unk_07 = param3;
    param0->unk_06 = param4;
}
