#include "wifi_plaza_lobby/wifi_plaza_lobby_02231428.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "nintendo_wfc/main.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231560.h"

#include "comm_manager.h"
#include "wifi_earth_place.h"

void WiFiPlazaLobby_Time_SetFromSeconds(WiFiPlazaLobbyTime *param0, const s64 *param1)
{
    RTCDate v0;
    RTCTime v1;

    RTC_ConvertSecondToDateTime(&v0, &v1, *param1);

    param0->hour = v1.hour;
    param0->minute = v1.minute;
    param0->second = v1.second;
}

void WiFiPlazaLobby_Time_Add(const WiFiPlazaLobbyTime *param0, const WiFiPlazaLobbyTime *param1, WiFiPlazaLobbyTime *param2)
{
    u32 v0;
    WiFiPlazaLobbyTime v1;
    WiFiPlazaLobbyTime v2;

    v1 = *param0;
    v2 = *param1;

    v1.second += v2.second;
    v0 = v1.second / 60;
    v1.minute += v0;

    param2->second = v1.second % 60;

    v1.minute += v2.minute;
    v0 = v1.minute / 60;
    v1.hour += v0;

    param2->minute = v1.minute % 60;

    v1.hour += v2.hour;
    param2->hour = v1.hour % 24;
}

void WiFiPlazaLobby_Time_Subtract(const WiFiPlazaLobbyTime *param0, const WiFiPlazaLobbyTime *param1, WiFiPlazaLobbyTime *param2)
{
    u32 v0;
    s32 v1;
    WiFiPlazaLobbyTime v2;
    WiFiPlazaLobbyTime v3;

    v2 = *param0;
    v3 = *param1;
    v1 = ((s8)v2.second - (s8)v3.second);

    if (v1 < 0) {
        v0 = ((-v1) / 60) + 1;
        v2.second += 60 * v0;
        v2.minute -= v0;
    }

    param2->second = v2.second - v3.second;

    v1 = ((s8)v2.minute - (s8)v3.minute);

    if (v1 < 0) {
        v0 = ((-v1) / 60) + 1;
        v2.minute += 60 * v0;
        v2.hour -= v0;
    }

    param2->minute = v2.minute - v3.minute;

    v1 = ((s8)v2.hour - (s8)v3.hour);

    if (v1 < 0) {
        v0 = ((-v1) / 24) + 1;
        v2.hour += 24 * v0;
    }

    param2->hour = v2.hour - v3.hour;
}

void WiFiPlazaLobby_Time_AddPlace(WiFiPlazaLobbyPlaceList *param0, u16 param1, u8 param2, BOOL param3)
{
    int v0;
    BOOL v1;
    u32 v2;

    if (param1 == 0) {
        return;
    }

    v2 = WiFiEarthPlace_GetRegionLimit(param1);

    if (param2 > v2) {
        return;
    }

    v1 = 0;

    for (v0 = 0; v0 < 50; v0++) {
        if (param0->places[v0].isActive == 0) {
            v1 = 1;
        } else {
            if ((param0->places[v0].country == param1) && (param0->places[v0].region == param2)) {
                if (param3 == 1) {
                    return;
                } else {
                    v1 = 1;
                }
            }
        }

        if (v1) {
            param0->places[v0].country = param1;
            param0->places[v0].region = param2;
            param0->places[v0].isSelf = param3;
            param0->places[v0].isActive = 1;
            return;
        }
    }
}

u16 WiFiPlazaLobby_Time_GetPlaceCountry(const WiFiPlazaLobbyPlaceList *param0, u8 param1)
{
    GF_ASSERT(param1 < 50);
    GF_ASSERT(param0->places[param1].isActive == 1);

    return param0->places[param1].country;
}

u8 WiFiPlazaLobby_Time_GetPlaceRegion(const WiFiPlazaLobbyPlaceList *param0, u8 param1)
{
    GF_ASSERT(param1 < 50);
    GF_ASSERT(param0->places[param1].isActive == 1);

    return param0->places[param1].region;
}

BOOL WiFiPlazaLobby_Time_GetPlaceIsSelf(const WiFiPlazaLobbyPlaceList *param0, u8 param1)
{
    GF_ASSERT(param1 < 50);
    GF_ASSERT(param0->places[param1].isActive == 1);

    return param0->places[param1].isSelf;
}

BOOL WiFiPlazaLobby_Time_IsPlaceActive(const WiFiPlazaLobbyPlaceList *param0, u8 param1)
{
    GF_ASSERT(param1 < 50);

    return param0->places[param1].isActive;
}

void WiFiPlazaLobby_Time_SetupModelGlobalLighting(void *param0)
{
    NNSG3dResMdlSet *v0 = NNS_G3dGetMdlSet(param0);
    NNSG3dResMdl *v1 = NNS_G3dGetMdlByIdx(v0, 0);

    NNS_G3dMdlUseGlbDiff(v1);
    NNS_G3dMdlUseGlbAmb(v1);
    NNS_G3dMdlUseGlbSpec(v1);
    NNS_G3dMdlUseGlbEmi(v1);
}

BOOL WiFiPlazaLobby_Time_IsValidCountryRegion(u16 param0, u16 param1)
{
    u32 v0 = WiFiEarthPlace_GetRegionLimit(param0);

    if (v0 == 0) {
        if (param1 == 0) {
            return 1;
        }
    }

    if ((param1 >= 1) && (param1 <= v0)) {
        return 1;
    }

    return 0;
}

u32 WiFiPlazaLobby_Time_GetTypeIconIndex(int param0)
{
    static const u8 v0[18] = {
        9,
        0,
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
        17,
    };

    return v0[param0];
}

int WiFiPlazaLobby_Time_GetWFCErrorMessageID(int param0, int param1)
{
    int v0;
    int v1;

    v0 = NintendoWFC_GetErrorCode(param0, param1);

    if ((v0 == 11) || (param0 == ((DWC_ERROR_NUM) + 5))) {
        v1 = 14;
    } else if (param0 == ((DWC_ERROR_NUM) + 6)) {
        v1 = 13;
    } else {
        if (v0 >= 0) {
            v1 = 0 + v0;
        } else {
            v1 = 11;
        }
    }

    return v1;
}

int WiFiPlazaLobby_Time_IsWFCErrorRetryable(int param0, int param1)
{
    int v0;
    int v1;

    v0 = NintendoWFC_GetErrorCode(param0, param1);

    if (param0 == ((DWC_ERROR_NUM) + 5)) {
        v0 = 11;
    } else if (param0 == ((DWC_ERROR_NUM) + 6)) {
        v0 = 12;
    }

    switch (v0) {
    case 1:
    case 4:
    case 5:
    case 11:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
        v1 = 0;
        break;
    case 0:
    case 2:
    case 3:
    default:
        v1 = 1;
        break;
    }

    return v1;
}

BOOL WiFiPlazaLobby_Time_HasWifiError(void)
{
    if (CommManager_CheckWifiError() || CommManager_IsWifiPlazaError()) {
        return 1;
    }

    return 0;
}
