#ifndef ILOBBY_DWCI_LOBBY_UTIL_H
#define ILOBBY_DWCI_LOBBY_UTIL_H

#include <algorithm>
#include <dwc.h>
#include <gs/chat/chat.h>
#include <string>
#include <vector>

#include "ilobby/dwci_lobbybase.h"

typedef std::basic_string<char, std::char_traits<char>, PPW_Allocator<char> > PPWString;

template <bool>
class PPW_StaticAssert;
template <>
class PPW_StaticAssert<true> {};
#define PPW_STATIC_ASSERT(exp) PPW_StaticAssert<(exp)>()

template <class T, class AllocatorT>
T *PPW_GetVectorData(const std::vector<T, AllocatorT> &param0)
{
    if (param0.empty()) {
        return NULL;
    }

    return const_cast<T *>(&param0[0]);
}

template <class T>
s32 PPW_StrniCmp(T param0, T param1, std::size_t param2)
{
    typedef typename T::value_type (*ValueTypeFunc)(typename T::value_type);

    std::transform(param0.begin(), param0.end(), param0.begin(), (ValueTypeFunc)std::tolower);
    std::transform(param1.begin(), param1.end(), param1.begin(), (ValueTypeFunc)std::tolower);
    return param0.compare(0, param2, param1);
}

inline s32 PPW_StrniCmpCStr(const char *param0, const char *param1, std::size_t param2)
{
    return PPW_StrniCmp(PPWString(param0), PPWString(param1), param2);
}

inline s64 PPW_GetCurrentTimeSeconds()
{
    RTCDate v0;
    RTCTime v1;
    DWC_GetDateTime(&v0, &v1);
    return RTC_ConvertDateTimeToSecond(&v0, &v1);
}

template <typename T>
T PPW_FormatStringAlloc(const char *param0, ...)
{
    va_list v0;
    std::vector<char, typename T::allocator_type> v1;

    va_start(v0, param0);

    int v2 = OS_VSNPrintf(NULL, 0, param0, v0) + 1;

    v1.resize((std::size_t)v2);
    OS_VSNPrintf(PPW_GetVectorData(v1), (std::size_t)v2, param0, v0);

    v1[(std::size_t)v2 - 1] = '\0';

    va_end(v0);

    return T(PPW_GetVectorData(v1));
}

template <class T>
T PPW_FormatStringTrunc(std::size_t param0, const char *param1, ...)
{
    va_list v0;
    std::vector<char, typename T::allocator_type> v1(param0);

    va_start(v0, param1);
    OS_VSNPrintf(PPW_GetVectorData(v1), param0, param1, v0);
    va_end(v0);

    return T(PPW_GetVectorData(v1));
}

template <class T>
std::vector<T, PPW_Allocator<T> > PPW_SplitStringAnyOf(const T &param0, const T &param1, std::size_t param2 = 0)
{
    std::vector<T, PPW_Allocator<T> > v0;
    std::size_t v1;
    std::size_t v2 = 1;
    T v3(param0);

    while (v2 != param2 && (v1 = v3.find_first_of(param1)) != v3.npos) {
        if (v1 > 0) {
            v0.push_back(v3.substr(0, v1));
            v2++;
        }
        v3 = v3.substr(v1 + 1);
    }
    if (v3.length() > 0) {
        v0.push_back(v3);
    }
    return v0;
}

template <class T>
std::vector<T, PPW_Allocator<T> > PPW_SplitString(const T &param0, const T &param1, std::size_t param2 = 0)
{
    std::vector<T, PPW_Allocator<T> > v0;
    std::size_t v1;
    std::size_t v2 = 1;
    T v3(param0);

    while (v2 != param2 && (v1 = v3.find(param1)) != v3.npos) {
        if (v1 > 0) {
            v0.push_back(v3.substr(0, v1));
            v2++;
        }
        v3 = v3.substr(v1 + param1.length());
    }
    if (v3.length() > 0) {
        v0.push_back(v3);
    }
    return v0;
}

template <class T, class Allocator>
BOOL PPW_Base64DecodeToVector(const char *param0, std::vector<T, Allocator> &param1)
{
    PPW_STATIC_ASSERT(sizeof(T) == 1);

    u32 v0 = strlen(param0);
    param1.resize(v0);
    if (v0 == 0) {
        return TRUE;
    }
    int v1 = DWC_Base64Decode(param0, strlen(param0), (char *)PPW_GetVectorData(param1), param1.size());
    if (v1 == -1) {
        return FALSE;
    }
    param1.resize((std::size_t)v1);
    return TRUE;
}

#endif // ILOBBY_DWCI_LOBBY_UTIL_H
