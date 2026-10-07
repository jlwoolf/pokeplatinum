#ifndef POKEPLATINUM_STRUCT_OV65_022354D8_H
#define POKEPLATINUM_STRUCT_OV65_022354D8_H

#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CE44.h"
#include "overlay065/struct_ov65_02235130_decl.h"

typedef struct UnkStruct_ov65_022354D8_t {
    WiFi2DCharObject *unk_00;
    WiFi2DCharRenderObject *unk_04;
    s16 unk_08;
    u8 unk_0A;
    u8 unk_0B;
    u16 unk_0C;
    u16 unk_0E;

    // clang-format off
    BOOL (* unk_10)(UnkStruct_ov65_02235130 *, struct UnkStruct_ov65_022354D8_t *);
    BOOL (* unk_14)(UnkStruct_ov65_02235130 *, struct UnkStruct_ov65_022354D8_t *);
    // clang-format on

    void (*unk_18)(UnkStruct_ov65_02235130 *, struct UnkStruct_ov65_022354D8_t *);
} UnkStruct_ov65_022354D8;

#endif // POKEPLATINUM_STRUCT_OV65_022354D8_H
