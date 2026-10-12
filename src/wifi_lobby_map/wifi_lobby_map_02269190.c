#include "wifi_lobby_map/wifi_lobby_map_02269190.h"

#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C700.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C858.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C9B4.h"
#include "wifi_lobby_map/wifi_lobby_map_02260A70.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_grid_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_camera_decl.h"

#include "easy3d_object.h"
#include "graphics.h"
#include "heap.h"
#include "narc.h"
#include "sound_playback.h"
#include "system.h"

typedef struct {
    u16 unk_00;
    u16 unk_02;
} WiFiLobbyMapAttractionAnim;

typedef struct {
    u16 unk_00;
    u8 unk_02;
    u8 unk_03;
} WiFiLobbyMapAttractionPart;

typedef struct {
    s32 unk_00;
    fx32 unk_04;
    fx32 unk_08;
    fx32 unk_0C;
    fx32 unk_10;
    fx32 unk_14;
    fx32 unk_18;
    fx32 unk_1C;
    fx32 unk_20;
    fx32 unk_24;
} WiFiLobbyMapKeyframe;

typedef struct {
    u16 unk_00;
    u16 unk_02;
    fx32 unk_04;
    fx32 unk_08;
} WiFiLobbyMapOscillator;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02[2];
} WiFiLobbyMapAttractionPartData;

typedef struct {
    s16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 unk_06;
    u8 unk_07;
    WiFiLobbyMapKeyframe unk_08[4];
    WiFiLobbyMapOscillator unk_A8[4];
    Easy3DObject *unk_D8[4];
    const WiFiLobbyMapActor *unk_E8;
} WiFiLobbyMapAttractionCar;

typedef union {
    struct {
        s8 unk_00;
        s8 unk_01;
        s16 unk_02;
        fx32 unk_04;
        u8 unk_08[3];
        u8 unk_0B;
        u8 unk_0C[3];
        u8 unk_0F;
        u8 unk_10;
        u8 unk_11;
        u8 unk_12[2];
        WiFiLobbyMapOscillator unk_14[3];
        WiFiLobbyMapKeyframe unk_38[3];
        WiFiLobbyMapKeyframe unk_B0;
        WiFiLobbyMapOscillator unk_D8;
    } val1;
    struct {
        s32 unk_00;
        s32 unk_04[3];
    } val2;
    struct {
        s8 unk_00;
        s8 unk_01;
        u8 unk_02;
        u8 unk_03;
        s8 unk_04[16];
        WiFiLobbyMapKeyframe unk_14[16];
    } val3;
    struct {
        s8 unk_00;
        s8 unk_01;
        s8 unk_02[2];
    } val4;
    struct {
        s32 unk_00;
    } val5;
    struct {
        s16 unk_00;
        s16 unk_02;
    } val6;
    struct {
        WiFiLobbyMapAttractionCar unk_00[4];
        const WiFiLobbyMapAttractionPart *unk_3B0;
        u16 unk_3B4;
        u16 unk_3B6;
        u16 unk_3B8;
        u16 unk_3BA;
    } val7;
} WiFiLobbyMapAttractionState;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    s16 unk_02;
    u32 unk_04;
    WiFiLobbyMapActor *unk_08;
    Easy3DObject unk_0C[18];
    const WiFiLobbyMapAttractionPartData *unk_87C[18];
    fx32 unk_8C4[18][2];
    WiFiLobbyMapAttractionState unk_954;
} WiFiLobbyMapAttraction;

typedef struct WiFiLobbyMapAttractionManager_t {
    WiFiPlazaLobbyState *unk_00;
    WiFiLobbyMapActorManager *unk_04;
    WiFiLobbyMapCamera *unk_08;
    WiFiLobbyMapGrid *unk_0C;
    WiFiLobbyMapAttraction unk_10[20];
    Easy3DModel unk_10550[15];
    void *unk_10640[39];
    Easy3DAnim unk_106DC[16];
    NNSFndAllocator unk_1081C;
} WiFiLobbyMapAttractionManager;

static void wifi_lobby_map_022692B4(WiFiLobbyMapKeyframe *param0, fx32 param1, fx32 param2, fx32 param3, fx32 param4, fx32 param5, fx32 param6, s32 param7);
static BOOL wifi_lobby_map_022692DC(WiFiLobbyMapKeyframe *param0, s32 param1);
static void wifi_lobby_map_02269488(const WiFiLobbyMapKeyframe *param0, fx32 *param1, fx32 *param2, fx32 *param3);
static void wifi_lobby_map_0226949C(WiFiLobbyMapOscillator *param0, u16 param1, u16 param2, fx32 param3);
static void wifi_lobby_map_022694D0(WiFiLobbyMapOscillator *param0);
static void wifi_lobby_map_02269508(const WiFiLobbyMapOscillator *param0, fx32 *param1);
static void wifi_lobby_map_02269540(WiFiLobbyMapAttractionManager *param0, NARC *param1, u32 heapID);
static void wifi_lobby_map_022695C4(WiFiLobbyMapAttractionManager *param0);
static void wifi_lobby_map_022695E0(WiFiLobbyMapAttractionManager *param0, NARC *param1, u32 param2);
static void wifi_lobby_map_02269608(WiFiLobbyMapAttractionManager *param0);
static void wifi_lobby_map_0226965C(WiFiLobbyMapAttractionManager *param0, NARC *param1, u32 param2);
static void wifi_lobby_map_02269700(WiFiLobbyMapAttractionManager *param0);
static void wifi_lobby_map_02269738(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, WiFiLobbyMapActor *param2, u32 param3);
static void wifi_lobby_map_0226978C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_022697C8(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_022697F0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_02269800(const WiFiLobbyMapAttraction *param0);
static BOOL wifi_lobby_map_02269810(const WiFiLobbyMapAttraction *param0, u32 param1);
static void wifi_lobby_map_02269828(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, const WiFiLobbyMapAttractionPartData *param3);
static void wifi_lobby_map_02269878(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2);
static void wifi_lobby_map_022699BC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, u32 param3);
static BOOL wifi_lobby_map_022699D0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, u32 param3);
static void wifi_lobby_map_022699E4(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, u32 param3, fx32 param4);
static BOOL wifi_lobby_map_02269A3C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, u32 param3, fx32 param4);
static void wifi_lobby_map_02269A90(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, u32 param3, fx32 param4);
static fx32 wifi_lobby_map_02269AE8(const WiFiLobbyMapAttractionManager *param0, const WiFiLobbyMapAttraction *param1, u32 param2, u32 param3);
static void wifi_lobby_map_02269B10(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_02269B1C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_02269B28(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_02269B34(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_02269B40(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_02269B4C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_02269B58(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_02269BB8(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_02269CFC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_02269F30(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A1FC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A208(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A214(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A220(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A22C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A238(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A244(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A294(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A2E4(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A334(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A384(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A3D4(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A424(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A478(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A4CC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226A520(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226A5F0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226A5FC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226A608(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226A614(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226A6C8(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226A820(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226A858(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226A930(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226A958(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226A998(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226A9D0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2);
static void wifi_lobby_map_0226AB14(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226ABAC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226AC08(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226AC24(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226AD20(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226ADA0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226ADBC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226AF1C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226AF60(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226AF7C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static BOOL wifi_lobby_map_0226B1D0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226B324(WiFiLobbyMapAttraction *param0);
static void wifi_lobby_map_0226B51C(WiFiLobbyMapAttraction *param0);
static BOOL wifi_lobby_map_0226B714(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, u32 param3);
static void wifi_lobby_map_0226B744(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2);
static void wifi_lobby_map_0226B7B0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2);
static BOOL wifi_lobby_map_0226B8C4(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2);
static void wifi_lobby_map_0226B92C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2);
static BOOL wifi_lobby_map_0226B998(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2);
static void wifi_lobby_map_0226BAC8(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2);
static void wifi_lobby_map_0226BB34(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226BBA8(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226BBDC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1);
static void wifi_lobby_map_0226BC40(WiFiLobbyMapAttractionState *param0, const WiFiLobbyMapAttractionPart *param1, u32 param2, u32 param3, u32 param4, WiFiLobbyMapAttraction *param5);
static int wifi_lobby_map_0226BCC0(WiFiLobbyMapAttractionState *param0, u32 param1);
static void wifi_lobby_map_0226BD64(WiFiLobbyMapAttractionCar *param0, Easy3DObject *param1, Easy3DObject *param2, Easy3DObject *param3, Easy3DObject *param4, const WiFiLobbyMapActor *param5, u32 param6);
static void wifi_lobby_map_0226BDA0(WiFiLobbyMapAttractionCar *param0, u32 param1);
static BOOL wifi_lobby_map_0226BDE8(WiFiLobbyMapAttractionCar *param0);
static void wifi_lobby_map_0226BE3C(WiFiLobbyMapAttractionCar *param0, const WiFiLobbyMapActor *param1);
static BOOL wifi_lobby_map_0226BF5C(WiFiLobbyMapAttractionCar *param0);
static void wifi_lobby_map_0226BFE4(WiFiLobbyMapAttractionCar *param0, const WiFiLobbyMapActor *param1);
static BOOL wifi_lobby_map_0226C0D8(WiFiLobbyMapAttractionCar *param0);
static void wifi_lobby_map_0226C17C(WiFiLobbyMapAttractionCar *param0, const WiFiLobbyMapActor *param1);
static BOOL wifi_lobby_map_0226C1DC(WiFiLobbyMapAttractionCar *param0);
static void wifi_lobby_map_0226C2A4(WiFiLobbyMapAttractionCar *param0, u32 param1, const VecFx32 *param2, fx32 param3, fx32 param4, fx32 param5, fx32 param6, u32 param7);

static const u8 Unk_wifi_lobby_map_0226E2E8[3] = {
    0x30,
    0x54,
    0x80
};

static const WiFi2DCharPosition Unk_wifi_lobby_map_0226E328[3] = {
    { 0x2, 0x38 },
    { 0xE, 0x38 },
    { 0x8, 0x3C }
};

static const WiFi2DCharPosition Unk_wifi_lobby_map_0226E340[3] = {
    { 0x2, 0x2C },
    { 0xE, 0x2C },
    { 0x8, 0x30 }
};

static const VecFx32 Unk_wifi_lobby_map_0226E370[4] = {
    { (8 * FX32_ONE), (FX32_CONST(16)), (-8 * FX32_ONE) + (10 * FX32_ONE) },
    { (8 * FX32_ONE) + (10 * FX32_ONE), (FX32_CONST(16)), (-8 * FX32_ONE) },
    { (8 * FX32_ONE), (FX32_CONST(16)), (-8 * FX32_ONE) - (10 * FX32_ONE) },
    { (8 * FX32_ONE) - (10 * FX32_ONE), (FX32_CONST(16)), (-8 * FX32_ONE) }
};

static const VecFx32 Unk_wifi_lobby_map_0226E3A0[4] = {
    { 0x0, (-FX32_CONST(8)), (FX32_CONST(8)) },
    { (FX32_CONST(8)), (-FX32_CONST(8)), 0x0 },
    { 0x0, (-FX32_CONST(8)), -(FX32_CONST(8)) },
    { -(FX32_CONST(8)), (-FX32_CONST(8)), 0x0 }
};

static const WiFiLobbyMapAttractionAnim Unk_wifi_lobby_map_0226E514[3][12] = {
    {
        { 0x0, 0x1 },
        { 0x0, 0x0 },
        { 0x0, 0x2 },
        { 0x0, 0x0 },
        { 0x0, 0x1 },
        { 0x0, 0x0 },
        { 0x0, 0x2 },
        { 0x0, 0x0 },
        { 0x0, 0x1 },
        { 0x0, 0x0 },
        { 0x0, 0x2 },
        { 0x0, 0x0 },
    },
    {
        { 0x1, 0x1 },
        { 0x1, 0x0 },
        { 0x0, 0x2 },
        { 0x0, 0x0 },
        { 0x1, 0x1 },
        { 0x1, 0x0 },
        { 0x0, 0x2 },
        { 0x0, 0x0 },
        { 0x1, 0x1 },
        { 0x1, 0x0 },
        { 0x0, 0x2 },
        { 0x0, 0x0 },
    },
    {
        { 0x0, 0x1 },
        { 0x0, 0x0 },
        { 0x1, 0x2 },
        { 0x1, 0x0 },
        { 0x2, 0x1 },
        { 0x2, 0x0 },
        { 0x0, 0x2 },
        { 0x1, 0x1 },
        { 0x2, 0x2 },
        { 0x0, 0x1 },
        { 0x1, 0x2 },
        { 0x2, 0x1 },
    },
};

static const u8 Unk_wifi_lobby_map_0226E640[16] = {
    0x13,
    0x14,
    0x13,
    0x14,
    0x13,
    0x14,
    0x13,
    0x14,
    0x13,
    0x14,
    0x13,
    0x14,
    0x13,
    0x14,
    0x13,
    0x14
};

static const u8 Unk_wifi_lobby_map_0226E650[16] = {
    0x13,
    0x14,
    0x15,
    0x13,
    0x1C,
    0x1D,
    0x1B,
    0x19,
    0x19,
    0x1D,
    0x14,
    0x13,
    0x1D,
    0x1B,
    0x17,
    0x13
};

static const u8 Unk_wifi_lobby_map_0226E660[16] = {
    0x13,
    0x14,
    0x1F,
    0x23,
    0x20,
    0x22,
    0x1B,
    0x1E,
    0x24,
    0x1D,
    0x18,
    0x21,
    0x1E,
    0x15,
    0x22,
    0x1F
};

static const WiFiLobbyMapAttractionPart Unk_wifi_lobby_map_0226E2EC[] = {
    { 0x0, 0x0, 0x2 },
    { 0x18, 0x2, 0x2 }
};

static const WiFiLobbyMapAttractionPart Unk_wifi_lobby_map_0226E304[] = {
    { 0x0, 0x0, 0x3 },
    { 0x18, 0x2, 0x3 }
};

static const WiFiLobbyMapAttractionPart Unk_wifi_lobby_map_0226E34C[] = {
    { 0x0, 0x0, 0x4 },
    { 0x10, 0x2, 0x4 },
    { 0x20, 0x0, 0x4 }
};

static const WiFiLobbyMapAttractionPart Unk_wifi_lobby_map_0226E2FC[] = {
    { 0x0, 0x0, 0x2 },
    { 0x18, 0x2, 0x2 }
};

static const WiFiLobbyMapAttractionPart Unk_wifi_lobby_map_0226E334[] = {
    { 0x0, 0x0, 0x3 },
    { 0x10, 0x2, 0x3 },
    { 0x28, 0x0, 0x3 }
};

static const WiFiLobbyMapAttractionPart Unk_wifi_lobby_map_0226E358[] = {
    { 0x0, 0x0, 0x4 },
    { 0x10, 0x2, 0x4 },
    { 0x23, 0x0, 0x4 }
};

static const WiFiLobbyMapAttractionPart Unk_wifi_lobby_map_0226E314[] = {
    { 0x0, 0x0, 0x2 },
    { 0x18, 0x1, 0x2 }
};

static const WiFiLobbyMapAttractionPart Unk_wifi_lobby_map_0226E2F4[] = {
    { 0x0, 0x0, 0x2 },
    { 0x18, 0x2, 0x2 }
};

static const WiFiLobbyMapAttractionPart Unk_wifi_lobby_map_0226E30C[] = {
    { 0x0, 0x0, 0x4 },
    { 0x14, 0x2, 0x4 }
};

static const WiFiLobbyMapAttractionPartData Unk_wifi_lobby_map_0226E5A4[39] = {
    {
        0x0,
        0x0,
        { 0x0, 0x11 },
    },
    {
        0x0,
        0x1,
        { 0x0, 0x11 },
    },
    {
        0x0,
        0x2,
        { 0x0, 0x11 },
    },
    {
        0x1,
        0x3,
        { 0x1, 0x2 },
    },
    {
        0x1,
        0x4,
        { 0x1, 0x2 },
    },
    {
        0x1,
        0x5,
        { 0x1, 0x2 },
    },
    {
        0x1,
        0x6,
        { 0x3, 0x11 },
    },
    {
        0x1,
        0x7,
        { 0x3, 0x11 },
    },
    {
        0x1,
        0x8,
        { 0x3, 0x11 },
    },
    {
        0x5,
        0xB,
        { 0x6, 0x11 },
    },
    {
        0x3,
        0x9,
        { 0x4, 0x11 },
    },
    {
        0x4,
        0xA,
        { 0x5, 0x11 },
    },
    {
        0x6,
        0xC,
        { 0x7, 0x11 },
    },
    {
        0x7,
        0xD,
        { 0x8, 0x11 },
    },
    {
        0x8,
        0xE,
        { 0x9, 0x11 },
    },
    {
        0x9,
        0xF,
        { 0xA, 0x11 },
    },
    {
        0xA,
        0x10,
        { 0xB, 0x11 },
    },
    {
        0xB,
        0x11,
        { 0xC, 0x11 },
    },
    {
        0xC,
        0x12,
        { 0xD, 0x11 },
    },
    {
        0x2,
        0x13,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x14,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x15,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x16,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x17,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x18,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x19,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x1A,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x1B,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x1C,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x1D,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x1E,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x1F,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x20,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x21,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x22,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x23,
        { 0x11, 0x11 },
    },
    {
        0x2,
        0x24,
        { 0x11, 0x11 },
    },
    {
        0xD,
        0x25,
        { 0xE, 0x11 },
    },
    {
        0xE,
        0x26,
        { 0xF, 0x11 },
    },
};

WiFiLobbyMapAttractionManager *wifi_lobby_map_02269190(WiFiPlazaLobbyState *param0, WiFiLobbyMapGrid *param1, WiFiLobbyMapCamera *param2, WiFiLobbyMapActorManager *param3, enum HeapID heapID, u32 heapID2)
{
    WiFiLobbyMapAttractionManager *v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMapAttractionManager));
    memset(v0, 0, sizeof(WiFiLobbyMapAttractionManager));

    v0->unk_00 = param0;
    v0->unk_04 = param3;
    v0->unk_08 = param2;
    v0->unk_0C = param1;

    {
        NARC *v1;

        v1 = NARC_ctor(NARC_INDEX_GRAPHIC__WIFI_LOBBY_OTHER, heapID);

        HeapExp_FndInitAllocator(&v0->unk_1081C, heapID2, 4);

        wifi_lobby_map_02269540(v0, v1, heapID2);
        wifi_lobby_map_022695E0(v0, v1, heapID2);
        wifi_lobby_map_0226965C(v0, v1, heapID2);

        NARC_dtor(v1);
    }

    return v0;
}

void wifi_lobby_map_02269204(WiFiLobbyMapAttractionManager *param0)
{
    {
        wifi_lobby_map_022695C4(param0);
        wifi_lobby_map_02269608(param0);
        wifi_lobby_map_02269700(param0);
    }

    Heap_Free(param0);
}

void wifi_lobby_map_02269220(WiFiLobbyMapAttractionManager *param0)
{
    int v0;

    for (v0 = 0; v0 < 20; v0++) {
        wifi_lobby_map_0226978C(param0, &param0->unk_10[v0]);
    }
}

void wifi_lobby_map_02269240(WiFiLobbyMapAttractionManager *param0)
{
    int v0;
    BOOL v1;
    WiFiLobbyMapActor *v2 = wifi_lobby_map_0225CCAC(param0->unk_04);

    for (v0 = 0; v0 < 20; v0++) {
        wifi_lobby_map_022697C8(param0, &param0->unk_10[v0]);
    }
}

void wifi_lobby_map_02269268(WiFiLobbyMapAttractionManager *param0, u32 param1, u32 param2)
{
    WiFiLobbyMapActor *v0;

    GF_ASSERT(param1 < 20);

    v0 = wifi_lobby_map_0225CC70(param0->unk_04, param1);

    if (v0 == NULL) {
        return;
    }

    wifi_lobby_map_02269738(param0, &param0->unk_10[param1], v0, param2);
}

BOOL wifi_lobby_map_02269298(const WiFiLobbyMapAttractionManager *param0, u32 param1)
{
    if (wifi_lobby_map_02269800(&param0->unk_10[param1]) == 1) {
        return 0;
    }

    return 1;
}

static void wifi_lobby_map_022692B4(WiFiLobbyMapKeyframe *param0, fx32 param1, fx32 param2, fx32 param3, fx32 param4, fx32 param5, fx32 param6, s32 param7)
{
    param0->unk_00 = param7;
    param0->unk_04 = param1;
    param0->unk_10 = param2 - param1;
    param0->unk_14 = param1;
    param0->unk_08 = param3;
    param0->unk_18 = param4 - param3;
    param0->unk_1C = param3;
    param0->unk_0C = param5;
    param0->unk_20 = param6 - param5;
    param0->unk_24 = param5;
}

static BOOL wifi_lobby_map_022692DC(WiFiLobbyMapKeyframe *param0, s32 param1)
{
    s32 v0;
    BOOL v1 = 0;

    if (param1 > param0->unk_00) {
        v0 = param0->unk_00;
        v1 = 1;
    } else {
        v0 = param1;
    }

    if (param0->unk_10 != 0) {
        param0->unk_04 = param0->unk_14 + FX_Div(FX_Mul(FX32_CONST(v0), param0->unk_10), FX32_CONST(param0->unk_00));
    }

    if (param0->unk_18 != 0) {
        param0->unk_08 = param0->unk_1C + FX_Div(FX_Mul(FX32_CONST(v0), param0->unk_18), FX32_CONST(param0->unk_00));
    }

    if (param0->unk_20 != 0) {
        param0->unk_0C = param0->unk_24 + FX_Div(FX_Mul(FX32_CONST(v0), param0->unk_20), FX32_CONST(param0->unk_00));
    }

    return v1;
}

static void wifi_lobby_map_02269488(const WiFiLobbyMapKeyframe *param0, fx32 *param1, fx32 *param2, fx32 *param3)
{
    *param1 = param0->unk_04;
    *param2 = param0->unk_08;
    *param3 = param0->unk_0C;
}

static void wifi_lobby_map_0226949C(WiFiLobbyMapOscillator *param0, u16 param1, u16 param2, fx32 param3)
{
    param0->unk_00 = param1;
    param0->unk_02 = param2;
    param0->unk_04 = param3;
    param0->unk_08 = FX_Mul(FX_SinIdx(param1), param0->unk_04);
}

static void wifi_lobby_map_022694D0(WiFiLobbyMapOscillator *param0)
{
    param0->unk_00 += param0->unk_02;
    param0->unk_08 = FX_Mul(FX_SinIdx(param0->unk_00), param0->unk_04);
}

static void wifi_lobby_map_02269508(const WiFiLobbyMapOscillator *param0, fx32 *param1)
{
    *param1 = param0->unk_08;
}

static void wifi_lobby_map_02269510(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 seqID)
{
    if (param1->unk_08 == wifi_lobby_map_0225CCAC(param0->unk_04)) {
        Sound_PlayEffectOnPlayer(seqID, 5);
    } else {
        if (wifi_lobby_map_0225CE70(param1->unk_08) == 0) {
            Sound_PlayEffect(seqID);
        }
    }
}

static void wifi_lobby_map_02269540(WiFiLobbyMapAttractionManager *param0, NARC *param1, u32 heapID)
{
    int v0;

    for (v0 = 0; v0 < 15; v0++) {
        param0->unk_10550[v0].data = LoadMemberFromOpenNARC(param1, 129 + v0, 0, heapID, 0);
        param0->unk_10550[v0].set = NNS_G3dGetMdlSet(param0->unk_10550[v0].data);
        param0->unk_10550[v0].model = NNS_G3dGetMdlByIdx(param0->unk_10550[v0].set, 0);
        param0->unk_10550[v0].texture = NULL;

        NNS_G3dMdlSetMdlEmiAll(param0->unk_10550[v0].model, GX_RGB(31, 31, 31));
    }
}

static void wifi_lobby_map_022695C4(WiFiLobbyMapAttractionManager *param0)
{
    int v0;

    for (v0 = 0; v0 < 15; v0++) {
        Heap_Free(param0->unk_10550[v0].data);
    }
}

static void wifi_lobby_map_022695E0(WiFiLobbyMapAttractionManager *param0, NARC *param1, u32 heapID)
{
    int v0;

    for (v0 = 0; v0 < 39; v0++) {
        wifi_lobby_map_0225C730(&param0->unk_10640[v0], param1, 144 + v0, heapID);
    }
}

static void wifi_lobby_map_02269608(WiFiLobbyMapAttractionManager *param0)
{
    int v0;
    NNSG3dTexKey v1;
    NNSG3dTexKey v2;
    NNSG3dPlttKey v3;
    NNSG3dResTex *v4;

    for (v0 = 0; v0 < 39; v0++) {
        v4 = NNS_G3dGetTex(param0->unk_10640[v0]);

        NNS_G3dTexReleaseTexKey(v4, &v1, &v2);
        NNS_GfdFreeTexVram(v1);
        NNS_GfdFreeTexVram(v2);

        v3 = NNS_G3dPlttReleasePlttKey(v4);
        NNS_GfdFreePlttVram(v3);
        Heap_Free(param0->unk_10640[v0]);
    }
}

static void wifi_lobby_map_0226965C(WiFiLobbyMapAttractionManager *param0, NARC *param1, u32 param2)
{
    int v0, v1;

    for (v0 = 0; v0 < 39; v0++) {
        for (v1 = 0; v1 < 2; v1++) {
            if (Unk_wifi_lobby_map_0226E5A4[v0].unk_02[v1] != 17) {
                if (param0->unk_106DC[Unk_wifi_lobby_map_0226E5A4[v0].unk_02[v1]].data == NULL) {
                    param0->unk_10550[Unk_wifi_lobby_map_0226E5A4[v0].unk_00].texture = NNS_G3dGetTex(param0->unk_10640[Unk_wifi_lobby_map_0226E5A4[v0].unk_01]);
                    Easy3DAnim_LoadFrom(&param0->unk_106DC[Unk_wifi_lobby_map_0226E5A4[v0].unk_02[v1]], &param0->unk_10550[Unk_wifi_lobby_map_0226E5A4[v0].unk_00], param1, 183 + Unk_wifi_lobby_map_0226E5A4[v0].unk_02[v1], param2, &param0->unk_1081C);
                }
            }
        }
    }
}

static void wifi_lobby_map_02269700(WiFiLobbyMapAttractionManager *param0)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        if (param0->unk_106DC[v0].data != NULL) {
            Easy3DAnim_Release(&param0->unk_106DC[v0], &param0->unk_1081C);
            param0->unk_106DC[v0].data = NULL;
        }
    }
}

static void wifi_lobby_map_02269738(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, WiFiLobbyMapActor *param2, u32 param3)
{
    static void (*const v0[27])(WiFiLobbyMapAttractionManager *, WiFiLobbyMapAttraction *) = {
        wifi_lobby_map_0226A244,
        wifi_lobby_map_0226A294,
        wifi_lobby_map_0226A2E4,
        wifi_lobby_map_0226A334,
        wifi_lobby_map_0226A384,
        wifi_lobby_map_0226A3D4,
        wifi_lobby_map_0226A424,
        wifi_lobby_map_0226A478,
        wifi_lobby_map_0226A4CC,
        wifi_lobby_map_02269B10,
        wifi_lobby_map_02269B1C,
        wifi_lobby_map_02269B28,
        wifi_lobby_map_02269B58,
        wifi_lobby_map_02269B58,
        wifi_lobby_map_02269B58,
        wifi_lobby_map_02269B34,
        wifi_lobby_map_02269B40,
        wifi_lobby_map_02269B4C,
        wifi_lobby_map_02269BB8,
        wifi_lobby_map_02269CFC,
        wifi_lobby_map_02269F30,
        wifi_lobby_map_0226A220,
        wifi_lobby_map_0226A22C,
        wifi_lobby_map_0226A238,
        wifi_lobby_map_0226A1FC,
        wifi_lobby_map_0226A208,
        wifi_lobby_map_0226A214
    };

    static const u32 v1[27] = {
        SEQ_SE_PL_HIROBA01_4_sseq,
        SEQ_SE_PL_HIROBA01_5_sseq,
        SEQ_SE_PL_HIROBA01_6_sseq,
        SEQ_SE_PL_HIROBA03_sseq,
        SEQ_SE_PL_HIROBA03_2_sseq,
        SEQ_SE_PL_HIROBA03_3_sseq,
        SEQ_SE_PL_HIROBA02_4_sseq,
        SEQ_SE_PL_HIROBA02_5_sseq,
        SEQ_SE_PL_HIROBA02_6_sseq,
        SEQ_SE_PL_HIROBA70_sseq,
        SEQ_SE_PL_HIROBA70_2_sseq,
        SEQ_SE_PL_HIROBA70_3_sseq,
        SEQ_SE_PL_HIROBA100_sseq,
        SEQ_SE_PL_HIROBA100_2_sseq,
        SEQ_SE_PL_HIROBA100_3_sseq,
        SEQ_SE_PL_HIROBA05_sseq,
        SEQ_SE_PL_HIROBA05_2_sseq,
        SEQ_SE_PL_HIROBA05_3_sseq,
        SEQ_SE_PL_W030_sseq,
        SEQ_SE_PL_W030_2_sseq,
        SEQ_SE_PL_W030_3_sseq,
        SEQ_SE_PL_W019_sseq,
        SEQ_SE_PL_W019_2_sseq,
        SEQ_SE_PL_W019_3_sseq,
        SEQ_SE_PL_HIROBA30_sseq,
        SEQ_SE_PL_HIROBA30_sseq,
        SEQ_SE_PL_HIROBA30_sseq
    };

    GF_ASSERT(param3 < 27);

    wifi_lobby_map_022697F0(param0, param1);

    param1->unk_08 = param2;
    param1->unk_00 = param3;
    param1->unk_04 = 40 + wifi_lobby_map_0225CD60(param2, 5);

    v0[param1->unk_00](param0, param1);

    wifi_lobby_map_02269510(param0, param1, v1[param1->unk_00]);
}

static void wifi_lobby_map_0226978C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    static BOOL (*const v0[27])(WiFiLobbyMapAttractionManager *, WiFiLobbyMapAttraction *) = {
        wifi_lobby_map_0226A930,
        wifi_lobby_map_0226A930,
        wifi_lobby_map_0226A930,
        wifi_lobby_map_0226A930,
        wifi_lobby_map_0226A930,
        wifi_lobby_map_0226A930,
        wifi_lobby_map_0226A958,
        wifi_lobby_map_0226A958,
        wifi_lobby_map_0226A958,
        wifi_lobby_map_0226A520,
        wifi_lobby_map_0226A520,
        wifi_lobby_map_0226A520,
        wifi_lobby_map_0226A5F0,
        wifi_lobby_map_0226A5FC,
        wifi_lobby_map_0226A608,
        wifi_lobby_map_0226A614,
        wifi_lobby_map_0226A614,
        wifi_lobby_map_0226A614,
        wifi_lobby_map_0226A6C8,
        wifi_lobby_map_0226A6C8,
        wifi_lobby_map_0226A6C8,
        wifi_lobby_map_0226A858,
        wifi_lobby_map_0226A858,
        wifi_lobby_map_0226A858,
        wifi_lobby_map_0226A820,
        wifi_lobby_map_0226A820,
        wifi_lobby_map_0226A820
    };

    if (wifi_lobby_map_02269800(param1) == 0) {
        return;
    }

    GF_ASSERT(param1->unk_00 < 27);

    if (v0[param1->unk_00](param0, param1) == 1) {
        wifi_lobby_map_022697F0(param0, param1);
    }
}

static BOOL wifi_lobby_map_022697C8(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    if (wifi_lobby_map_02269800(param1) == 0) {
        return 0;
    }

    GF_ASSERT(param1->unk_00 < 27);

    return wifi_lobby_map_0226A998(param0, param1);
}

static void wifi_lobby_map_022697F0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    memset(param1, 0, sizeof(WiFiLobbyMapAttraction));
}

static BOOL wifi_lobby_map_02269800(const WiFiLobbyMapAttraction *param0)
{
    if (param0->unk_08 == NULL) {
        return 0;
    }

    return 1;
}

static BOOL wifi_lobby_map_02269810(const WiFiLobbyMapAttraction *param0, u32 param1)
{
    if (param0->unk_87C[param1] == NULL) {
        return 0;
    }

    return 1;
}

static void wifi_lobby_map_02269828(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, const WiFiLobbyMapAttractionPartData *param3)
{
    int v0;

    GF_ASSERT(param2 < 18);
    GF_ASSERT(param1->unk_87C[param2] == NULL);

    param1->unk_87C[param2] = param3;

    Easy3DObject_Init(&param1->unk_0C[param2], &param0->unk_10550[param3->unk_00]);
}

static void wifi_lobby_map_02269878(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2)
{
    BOOL v0;
    void *v1;
    Easy3DModel *v2;
    Easy3DAnim *v3;
    int v4;

    GF_ASSERT(param1->unk_87C[param2] != NULL);

    if (Easy3DObject_IsVisible(&param1->unk_0C[param2]) == 0) {
        return;
    }

    v1 = param0->unk_10640[param1->unk_87C[param2]->unk_01];
    v2 = &param0->unk_10550[param1->unk_87C[param2]->unk_00];
    v2->texture = NNS_G3dGetTex(v1);
    v0 = NNS_G3dForceBindMdlTex(v2->model, v2->texture, 0, 0);
    GF_ASSERT(v0);

    v0 = NNS_G3dForceBindMdlPltt(v2->model, v2->texture, 0, 0);
    GF_ASSERT(v0);

    for (v4 = 0; v4 < 2; v4++) {
        if (param1->unk_87C[param2]->unk_02[v4] != 17) {
            v3 = &param0->unk_106DC[param1->unk_87C[param2]->unk_02[v4]];
            Easy3DObject_AddAnim(&param1->unk_0C[param2], v3);
            Easy3DAnim_SetFrame(v3, param1->unk_8C4[param2][v4]);
        } else {
            break;
        }
    }

    NNS_G3dMdlSetMdlPolygonIDAll(v2->model, param1->unk_04);
    Easy3DObject_Draw(&param1->unk_0C[param2]);

    for (v4 = 0; v4 < 2; v4++) {
        if (param1->unk_87C[param2]->unk_02[v4] != 17) {
            v3 = &param0->unk_106DC[param1->unk_87C[param2]->unk_02[v4]];
            Easy3DObject_RemoveAnim(&param1->unk_0C[param2], v3);
        } else {
            break;
        }
    }

    NNS_G3dReleaseMdlTex(v2->model);
    NNS_G3dReleaseMdlPltt(v2->model);

    v2->texture = NULL;
}

static void wifi_lobby_map_022699BC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, u32 param3)
{
    wifi_lobby_map_022699E4(param0, param1, param2, param3, (FX32_ONE * 2));
}

static BOOL wifi_lobby_map_022699D0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, u32 param3)
{
    return wifi_lobby_map_02269A3C(param0, param1, param2, param3, (FX32_ONE * 2));
}

static void wifi_lobby_map_022699E4(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, u32 param3, fx32 param4)
{
    fx32 v0;
    Easy3DAnim *v1 = &param0->unk_106DC[param1->unk_87C[param2]->unk_02[param3]];
    v0 = Easy3DAnim_GetFrameCount(v1);

    if ((param1->unk_8C4[param2][param3] + param4) < v0) {
        param1->unk_8C4[param2][param3] += param4;
    } else {
        param1->unk_8C4[param2][param3] = (param1->unk_8C4[param2][param3] + (FX32_ONE * 2)) % v0;
    }
}

static BOOL wifi_lobby_map_02269A3C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, u32 param3, fx32 param4)
{
    fx32 v0;
    BOOL v1;
    Easy3DAnim *v2 = &param0->unk_106DC[param1->unk_87C[param2]->unk_02[param3]];
    v0 = Easy3DAnim_GetFrameCount(v2);

    if ((param1->unk_8C4[param2][param3] + param4) < v0) {
        param1->unk_8C4[param2][param3] += param4;
        v1 = 0;
    } else {
        param1->unk_8C4[param2][param3] = v0 - FX32_HALF;
        v1 = 1;
    }

    return v1;
}

static void wifi_lobby_map_02269A90(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, u32 param3, fx32 param4)
{
    fx32 v0;
    Easy3DAnim *v1 = &param0->unk_106DC[param1->unk_87C[param2]->unk_02[param3]];
    v0 = Easy3DAnim_GetFrameCount(v1);

    if (v0 < param4) {
        param1->unk_8C4[param2][param3] = v0 - FX32_HALF;
    } else {
        param1->unk_8C4[param2][param3] = param4;
    }
}

static fx32 wifi_lobby_map_02269AE8(const WiFiLobbyMapAttractionManager *param0, const WiFiLobbyMapAttraction *param1, u32 param2, u32 param3)
{
    fx32 v0;
    const Easy3DAnim *v1 = &param0->unk_106DC[param1->unk_87C[param2]->unk_02[param3]];
    return Easy3DAnim_GetFrame(v1);
}

static void wifi_lobby_map_02269B10(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    wifi_lobby_map_0226B92C(param0, param1, 1);
}

static void wifi_lobby_map_02269B1C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    wifi_lobby_map_0226B92C(param0, param1, 2);
}

static void wifi_lobby_map_02269B28(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    wifi_lobby_map_0226B92C(param0, param1, 3);
}

static void wifi_lobby_map_02269B34(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    wifi_lobby_map_0226BAC8(param0, param1, 1);
}

static void wifi_lobby_map_02269B40(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    wifi_lobby_map_0226BAC8(param0, param1, 2);
}

static void wifi_lobby_map_02269B4C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    wifi_lobby_map_0226BAC8(param0, param1, 3);
}

static void wifi_lobby_map_02269B58(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;
    VecFx32 v1;

    for (v0 = 0; v0 < 3; v0++) {
        wifi_lobby_map_02269828(param0, param1, v0, &Unk_wifi_lobby_map_0226E5A4[3 + v0]);
        wifi_lobby_map_0225D054(param1->unk_08, &v1);

        v1.x += (FX32_CONST(0));
        v1.z += (FX32_CONST(0));
        v1.y += (FX32_CONST(8)) + (FX_Mul(FX32_ONE * v0, (FX32_CONST(0))));

        Easy3DObject_SetPosition(&param1->unk_0C[v0], v1.x, v1.y, v1.z);
        Easy3DObject_SetVisible(&param1->unk_0C[v0], 0);
    }

    param1->unk_954.val5.unk_00 = 0xff;
}

static void wifi_lobby_map_02269BB8(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    VecFx32 v0, v1;
    u32 v2;

    wifi_lobby_map_02269828(param0, param1, 1, &Unk_wifi_lobby_map_0226E5A4[9]);
    wifi_lobby_map_02269828(param0, param1, 0, &Unk_wifi_lobby_map_0226E5A4[12]);
    Easy3DObject_SetVisible(&param1->unk_0C[1], 0);
    wifi_lobby_map_0225D054(param1->unk_08, &v0);

    v0.y += (FX32_CONST(16));
    v0.x += (FX32_CONST(8));
    v1 = v0;
    v1.y += (FX32_CONST(16));

    param1->unk_954.val2.unk_04[0] = 8;

    v2 = wifi_lobby_map_0225CD60(param1->unk_08, 6);

    switch (v2) {
    case 0:
        v0.z -= (FX32_CONST(28));
        v1.z -= (FX32_CONST(14));
        Easy3DObject_SetRotation(&param1->unk_0C[1], ((270 * 0xffff) / 360), 1);
        break;
    case 1:
        v0.z += (FX32_CONST(24));
        v1.z += (FX32_CONST(11));
        Easy3DObject_SetRotation(&param1->unk_0C[1], ((90 * 0xffff) / 360), 1);
        break;
    case 2:
        v0.x -= (FX32_CONST(23));
        v1.x -= (FX32_CONST(7));
        v1.z += (FX32_CONST(8));
        Easy3DObject_SetRotation(&param1->unk_0C[1], ((0 * 0xffff) / 360), 1);
        break;
    case 3:
        v0.x += (FX32_CONST(23));
        v1.x += (FX32_CONST(7));
        v1.z += (FX32_CONST(8));
        Easy3DObject_SetRotation(&param1->unk_0C[1], ((180 * 0xffff) / 360), 1);
        break;
    default:
        break;
    }

    Easy3DObject_SetPosition(&param1->unk_0C[1], v0.x, v0.y, v0.z);
    Easy3DObject_SetPosition(&param1->unk_0C[0], v1.x, v1.y, v1.z);
}

static void wifi_lobby_map_02269CFC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    VecFx32 v0, v1;
    u32 v2;

    wifi_lobby_map_02269828(param0, param1, 1, &Unk_wifi_lobby_map_0226E5A4[9]);
    wifi_lobby_map_02269828(param0, param1, 0, &Unk_wifi_lobby_map_0226E5A4[12]);
    wifi_lobby_map_02269828(param0, param1, 2, &Unk_wifi_lobby_map_0226E5A4[10]);
    Easy3DObject_SetVisible(&param1->unk_0C[1], 0);
    wifi_lobby_map_0225D054(param1->unk_08, &v0);

    v0.y += (FX32_CONST(16));
    v0.x += (FX32_CONST(8));
    v1 = v0;
    v1.y += (FX32_CONST(16));

    param1->unk_954.val2.unk_04[0] = 8;
    param1->unk_954.val2.unk_04[1] = 8;

    v2 = wifi_lobby_map_0225CD60(param1->unk_08, 6);

    switch (v2) {
    case 0:
        v0.z -= (FX32_CONST(28));
        v1.z -= (FX32_CONST(14));
        Easy3DObject_SetRotation(&param1->unk_0C[1], (((270 - 40) * 0xffff) / 360), 1);
        Easy3DObject_SetRotation(&param1->unk_0C[2], (((270 + 40) * 0xffff) / 360), 1);
        Easy3DObject_SetPosition(&param1->unk_0C[1], v0.x + (FX32_CONST(8)), v0.y, v0.z);
        Easy3DObject_SetPosition(&param1->unk_0C[2], v0.x - (FX32_CONST(8)), v0.y, v0.z);
        break;
    case 1:
        v0.z += (FX32_CONST(24));
        v1.z += (FX32_CONST(11));

        Easy3DObject_SetRotation(&param1->unk_0C[1], (((90 - 40) * 0xffff) / 360), 1);
        Easy3DObject_SetRotation(&param1->unk_0C[2], (((90 + 40) * 0xffff) / 360), 1);
        Easy3DObject_SetPosition(&param1->unk_0C[1], v0.x - (FX32_CONST(8)), v0.y, v0.z);
        Easy3DObject_SetPosition(&param1->unk_0C[2], v0.x + (FX32_CONST(8)), v0.y, v0.z);
        break;
    case 2:
        v0.x -= (FX32_CONST(23));
        v1.x -= (FX32_CONST(7));
        v1.z += (FX32_CONST(8));

        Easy3DObject_SetRotation(&param1->unk_0C[1], (((0 - 40) * 0xffff) / 360), 1);
        Easy3DObject_SetRotation(&param1->unk_0C[2], (((0 + 40) * 0xffff) / 360), 1);
        Easy3DObject_SetPosition(&param1->unk_0C[1], v0.x, v0.y, v0.z - (FX32_CONST(8)));
        Easy3DObject_SetPosition(&param1->unk_0C[2], v0.x, v0.y, v0.z + (FX32_CONST(8)));
        break;
    case 3:
        v0.x += (FX32_CONST(23));
        v1.x += (FX32_CONST(7));
        v1.z += (FX32_CONST(8));

        Easy3DObject_SetRotation(&param1->unk_0C[1], (((180 - 40) * 0xffff) / 360), 1);
        Easy3DObject_SetRotation(&param1->unk_0C[2], (((180 + 40) * 0xffff) / 360), 1);
        Easy3DObject_SetPosition(&param1->unk_0C[1], v0.x, v0.y, v0.z + (FX32_CONST(8)));
        Easy3DObject_SetPosition(&param1->unk_0C[2], v0.x, v0.y, v0.z - (FX32_CONST(8)));
        break;
    default:
        break;
    }

    Easy3DObject_SetPosition(&param1->unk_0C[0], v1.x, v1.y, v1.z);
}

static void wifi_lobby_map_02269F30(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    VecFx32 v0, v1;
    u32 v2;

    wifi_lobby_map_02269828(param0, param1, 1, &Unk_wifi_lobby_map_0226E5A4[9]);
    wifi_lobby_map_02269828(param0, param1, 0, &Unk_wifi_lobby_map_0226E5A4[12]);
    wifi_lobby_map_02269828(param0, param1, 2, &Unk_wifi_lobby_map_0226E5A4[10]);
    wifi_lobby_map_02269828(param0, param1, 3, &Unk_wifi_lobby_map_0226E5A4[11]);

    Easy3DObject_SetVisible(&param1->unk_0C[1], 0);

    param1->unk_954.val2.unk_04[0] = 8;
    param1->unk_954.val2.unk_04[1] = 8;
    param1->unk_954.val2.unk_04[2] = 8;

    wifi_lobby_map_0225D054(param1->unk_08, &v0);

    v0.y += (FX32_CONST(16));
    v0.x += (FX32_CONST(8));
    v1 = v0;
    v1.y += (FX32_CONST(16));
    v2 = wifi_lobby_map_0225CD60(param1->unk_08, 6);

    switch (v2) {
    case 0:
        v0.z -= (FX32_CONST(28));
        v1.z -= (FX32_CONST(14));

        Easy3DObject_SetRotation(&param1->unk_0C[1], (((270 - 40) * 0xffff) / 360), 1);
        Easy3DObject_SetRotation(&param1->unk_0C[2], (((270 + 40) * 0xffff) / 360), 1);
        Easy3DObject_SetRotation(&param1->unk_0C[3], ((270 * 0xffff) / 360), 1);
        Easy3DObject_SetPosition(&param1->unk_0C[1], v0.x + (FX32_CONST(8)), v0.y, v0.z);
        Easy3DObject_SetPosition(&param1->unk_0C[2], v0.x - (FX32_CONST(8)), v0.y, v0.z);
        Easy3DObject_SetPosition(&param1->unk_0C[3], v0.x, v0.y, v0.z);
        break;
    case 1:
        v0.z += (FX32_CONST(24));
        v1.z += (FX32_CONST(11));

        Easy3DObject_SetRotation(&param1->unk_0C[1], (((90 - 40) * 0xffff) / 360), 1);
        Easy3DObject_SetRotation(&param1->unk_0C[2], (((90 + 40) * 0xffff) / 360), 1);
        Easy3DObject_SetRotation(&param1->unk_0C[3], ((90 * 0xffff) / 360), 1);
        Easy3DObject_SetPosition(&param1->unk_0C[1], v0.x - (FX32_CONST(8)), v0.y, v0.z);
        Easy3DObject_SetPosition(&param1->unk_0C[2], v0.x + (FX32_CONST(8)), v0.y, v0.z);
        Easy3DObject_SetPosition(&param1->unk_0C[3], v0.x, v0.y, v0.z);
        break;
    case 2:
        v0.x -= (FX32_CONST(23));
        v1.x -= (FX32_CONST(7));
        v1.z += (FX32_CONST(8));

        Easy3DObject_SetRotation(&param1->unk_0C[1], (((0 - 40) * 0xffff) / 360), 1);
        Easy3DObject_SetRotation(&param1->unk_0C[2], (((0 + 40) * 0xffff) / 360), 1);
        Easy3DObject_SetRotation(&param1->unk_0C[3], ((0 * 0xffff) / 360), 1);
        Easy3DObject_SetPosition(&param1->unk_0C[1], v0.x, v0.y, v0.z - (FX32_CONST(8)));
        Easy3DObject_SetPosition(&param1->unk_0C[2], v0.x, v0.y, v0.z + (FX32_CONST(8)));
        Easy3DObject_SetPosition(&param1->unk_0C[3], v0.x, v0.y, v0.z);
        break;
    case 3:
        v0.x += (FX32_CONST(23));
        v1.x += (FX32_CONST(7));
        v1.z += (FX32_CONST(8));

        Easy3DObject_SetRotation(&param1->unk_0C[1], (((180 - 40) * 0xffff) / 360), 1);
        Easy3DObject_SetRotation(&param1->unk_0C[2], (((180 + 40) * 0xffff) / 360), 1);
        Easy3DObject_SetRotation(&param1->unk_0C[3], ((180 * 0xffff) / 360), 1);
        Easy3DObject_SetPosition(&param1->unk_0C[1], v0.x, v0.y, v0.z + (FX32_CONST(8)));
        Easy3DObject_SetPosition(&param1->unk_0C[2], v0.x, v0.y, v0.z - (FX32_CONST(8)));
        Easy3DObject_SetPosition(&param1->unk_0C[3], v0.x, v0.y, v0.z);
        break;
    default:
        break;
    }

    Easy3DObject_SetPosition(&param1->unk_0C[0], v1.x, v1.y, v1.z);
}

static void wifi_lobby_map_0226A1FC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    wifi_lobby_map_0226A9D0(param0, param1, 1);
}

static void wifi_lobby_map_0226A208(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    wifi_lobby_map_0226A9D0(param0, param1, 2);
}

static void wifi_lobby_map_0226A214(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    wifi_lobby_map_0226A9D0(param0, param1, 3);
}

static void wifi_lobby_map_0226A220(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    wifi_lobby_map_0226B7B0(param0, param1, 1);
}

static void wifi_lobby_map_0226A22C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    wifi_lobby_map_0226B7B0(param0, param1, 2);
}

static void wifi_lobby_map_0226A238(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    wifi_lobby_map_0226B7B0(param0, param1, 4);
}

static void wifi_lobby_map_0226A244(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        wifi_lobby_map_02269828(param0, param1, v0, &Unk_wifi_lobby_map_0226E5A4[Unk_wifi_lobby_map_0226E640[v0]]);
    }

    wifi_lobby_map_0226BC40(&param1->unk_954, Unk_wifi_lobby_map_0226E2EC, NELEMS(Unk_wifi_lobby_map_0226E2EC), 33, 0, param1);
}

static void wifi_lobby_map_0226A294(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        wifi_lobby_map_02269828(param0, param1, v0, &Unk_wifi_lobby_map_0226E5A4[Unk_wifi_lobby_map_0226E650[v0]]);
    }

    wifi_lobby_map_0226BC40(&param1->unk_954, Unk_wifi_lobby_map_0226E304, NELEMS(Unk_wifi_lobby_map_0226E304), 33, 0, param1);
}

static void wifi_lobby_map_0226A2E4(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        wifi_lobby_map_02269828(param0, param1, v0, &Unk_wifi_lobby_map_0226E5A4[Unk_wifi_lobby_map_0226E660[v0]]);
    }

    wifi_lobby_map_0226BC40(&param1->unk_954, Unk_wifi_lobby_map_0226E34C, NELEMS(Unk_wifi_lobby_map_0226E34C), 33, 0, param1);
}

static void wifi_lobby_map_0226A334(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        wifi_lobby_map_02269828(param0, param1, v0, &Unk_wifi_lobby_map_0226E5A4[Unk_wifi_lobby_map_0226E640[v0]]);
    }

    wifi_lobby_map_0226BC40(&param1->unk_954, Unk_wifi_lobby_map_0226E2FC, NELEMS(Unk_wifi_lobby_map_0226E2FC), 33, 1, param1);
}

static void wifi_lobby_map_0226A384(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        wifi_lobby_map_02269828(param0, param1, v0, &Unk_wifi_lobby_map_0226E5A4[Unk_wifi_lobby_map_0226E650[v0]]);
    }

    wifi_lobby_map_0226BC40(&param1->unk_954, Unk_wifi_lobby_map_0226E334, NELEMS(Unk_wifi_lobby_map_0226E334), 41, 1, param1);
}

static void wifi_lobby_map_0226A3D4(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        wifi_lobby_map_02269828(param0, param1, v0, &Unk_wifi_lobby_map_0226E5A4[Unk_wifi_lobby_map_0226E660[v0]]);
    }

    wifi_lobby_map_0226BC40(&param1->unk_954, Unk_wifi_lobby_map_0226E358, NELEMS(Unk_wifi_lobby_map_0226E358), 33, 1, param1);
}

static void wifi_lobby_map_0226A424(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;
    VecFx32 v1;

    for (v0 = 0; v0 < 16; v0++) {
        wifi_lobby_map_02269828(param0, param1, v0, &Unk_wifi_lobby_map_0226E5A4[Unk_wifi_lobby_map_0226E640[v0]]);
    }

    wifi_lobby_map_0226BC40(&param1->unk_954, Unk_wifi_lobby_map_0226E314, NELEMS(Unk_wifi_lobby_map_0226E314), 33, 2, param1);
    wifi_lobby_map_0226BB34(param0, param1);
}

static void wifi_lobby_map_0226A478(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;
    VecFx32 v1;

    for (v0 = 0; v0 < 16; v0++) {
        wifi_lobby_map_02269828(param0, param1, v0, &Unk_wifi_lobby_map_0226E5A4[Unk_wifi_lobby_map_0226E650[v0]]);
    }

    wifi_lobby_map_0226BC40(&param1->unk_954, Unk_wifi_lobby_map_0226E2F4, NELEMS(Unk_wifi_lobby_map_0226E2F4), 33, 2, param1);
    wifi_lobby_map_0226BB34(param0, param1);
}

static void wifi_lobby_map_0226A4CC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        wifi_lobby_map_02269828(param0, param1, v0, &Unk_wifi_lobby_map_0226E5A4[Unk_wifi_lobby_map_0226E660[v0]]);
    }

    wifi_lobby_map_0226BC40(&param1->unk_954, Unk_wifi_lobby_map_0226E30C, NELEMS(Unk_wifi_lobby_map_0226E30C), 33, 2, param1);
    wifi_lobby_map_0226BB34(param0, param1);
}

static BOOL wifi_lobby_map_0226A520(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;
    BOOL v1;
    u32 v2;
    u32 v3;

    if ((param1->unk_02 + 1) <= 54) {
        param1->unk_02++;
    }

    v2 = (param1->unk_02 * 6) / 54;

    for (v0 = param1->unk_954.val4.unk_01; v0 < v2; v0++) {
        v3 = v0 % 3;

        if (v3 < param1->unk_954.val4.unk_00) {
            Easy3DObject_SetVisible(&param1->unk_0C[v3], 1);
        }
    }

    param1->unk_954.val4.unk_01 = v2;

    v1 = 1;

    for (v0 = 0; v0 < param1->unk_954.val4.unk_00; v0++) {
        if (Easy3DObject_IsVisible(&param1->unk_0C[v0]) == 1) {
            v1 = wifi_lobby_map_022699D0(param0, param1, v0, 0);

            if (v1) {
                Easy3DObject_SetVisible(&param1->unk_0C[v0], 0);
                wifi_lobby_map_02269A90(param0, param1, v0, 0, 0);
            }
        }
    }

    if ((param1->unk_954.val4.unk_01 >= 6) && (v1 == 1)) {
        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_0226A5F0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    return wifi_lobby_map_0226B998(param0, param1, 0);
}

static BOOL wifi_lobby_map_0226A5FC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    return wifi_lobby_map_0226B998(param0, param1, 1);
}

static BOOL wifi_lobby_map_0226A608(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    return wifi_lobby_map_0226B998(param0, param1, 2);
}

static BOOL wifi_lobby_map_0226A614(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    u32 v0;
    int v1;
    BOOL v2;

    v0 = (param1->unk_02 * 3) / 32;

    if (v0 != param1->unk_954.val6.unk_00) {
        param1->unk_954.val6.unk_00 = v0;

        if (param1->unk_954.val6.unk_02 > v0) {
            if (v0 > 0) {
                Easy3DObject_SetVisible(&param1->unk_0C[v0 - 1], 0);
            }

            Easy3DObject_SetVisible(&param1->unk_0C[v0], 1);
        }
    }

    if (param1->unk_02 < 32) {
        param1->unk_02++;
    }

    v2 = 0;

    for (v1 = 0; v1 < param1->unk_954.val6.unk_02; v1++) {
        if (Easy3DObject_IsVisible(&param1->unk_0C[v1])) {
            if (v1 == param1->unk_954.val6.unk_02 - 1) {
                v2 = wifi_lobby_map_022699D0(param0, param1, v1, 0);
            } else {
                wifi_lobby_map_022699BC(param0, param1, v1, 0);
            }
        }
    }

    return v2;
}

static BOOL wifi_lobby_map_0226A6C8(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    BOOL v0;
    BOOL v1;
    int v2;

    GF_ASSERT(param1->unk_87C[0]->unk_02[0] != 17);

    if (param1->unk_954.val2.unk_00 > 0) {
        param1->unk_954.val2.unk_00--;
        Easy3DObject_SetVisible(&param1->unk_0C[0], 0);
    } else {
        if (param1->unk_02 < 3) {
            if (wifi_lobby_map_02269810(param1, param1->unk_02 + 1) == 1) {
                Easy3DObject_SetVisible(&param1->unk_0C[0], 1);
                v0 = wifi_lobby_map_022699D0(param0, param1, 0, 0);

                if (v0 == 1) {
                    param1->unk_02++;
                    param1->unk_954.val2.unk_00 = 3;

                    if (param1->unk_02 < 3) {
                        wifi_lobby_map_02269A90(param0, param1, 0, 0, 0);
                    } else {
                        Easy3DObject_SetVisible(&param1->unk_0C[0], 0);
                    }
                }
            }
        }
    }

    v1 = 1;

    for (v2 = 1; v2 <= 3; v2++) {
        if (wifi_lobby_map_02269810(param1, v2) == 1) {
            if (param1->unk_02 > (v2 - 1)) {
                Easy3DObject_SetVisible(&param1->unk_0C[v2], 1);
                v0 = wifi_lobby_map_02269A3C(param0, param1, v2, 0, FX32_CONST(2.50f));

                if (v0 == 0) {
                    v1 = 0;
                } else {
                    s32 v3;
                    s32 v4;

                    v4 = v2 - 1;

                    if (param1->unk_954.val2.unk_04[v4] == 0) {
                        Easy3DObject_SetVisible(&param1->unk_0C[v2], 0);
                        NNS_G3dMdlSetMdlAlphaAll(param0->unk_10550[param1->unk_87C[v2]->unk_00].model, 31);
                    } else {
                        param1->unk_954.val2.unk_04[v4]--;
                        v3 = (param1->unk_954.val2.unk_04[v4] * 20) / 8;
                        NNS_G3dMdlSetMdlAlphaAll(param0->unk_10550[param1->unk_87C[v2]->unk_00].model, v3);
                        v1 = 0;
                    }
                }
            } else {
                v1 = 0;
            }
        }
    }

    return v1;
}

static BOOL wifi_lobby_map_0226A820(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    BOOL v0;

    switch (param1->unk_01) {
    case 0:
        v0 = wifi_lobby_map_0226AC08(param0, param1);

        if (v0) {
            param1->unk_01 = 1;
            wifi_lobby_map_0226ADA0(param0, param1);
        }
        break;
    case 1:
        v0 = wifi_lobby_map_0226AF60(param0, param1);

        if (v0) {
            return 1;
        }
        break;
    }

    return 0;
}

static BOOL wifi_lobby_map_0226A858(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    BOOL v0;
    u32 v1;
    int v2;

    if (param1->unk_954.val3.unk_01 < param1->unk_954.val3.unk_02) {
        param1->unk_954.val3.unk_00++;

        if (param1->unk_954.val3.unk_00 >= 8) {
            param1->unk_954.val3.unk_00 = 0;
            param1->unk_954.val3.unk_01++;
        }

        v1 = (param1->unk_954.val3.unk_00 * 4) / 8;
        v1 += param1->unk_954.val3.unk_01 * 4;

        for (v2 = param1->unk_954.val3.unk_03; v2 < v1; v2++) {
            Easy3DObject_SetVisible(&param1->unk_0C[v2], 1);
        }

        param1->unk_954.val3.unk_03 = v1;
    }

    for (v2 = 0; v2 < param1->unk_954.val3.unk_03; v2++) {
        if (Easy3DObject_IsVisible(&param1->unk_0C[v2]) == 1) {
            v0 = wifi_lobby_map_0226B8C4(param0, param1, v2);

            if (v0 == 1) {
                Easy3DObject_SetVisible(&param1->unk_0C[v2], 0);
            }
        }
    }

    if ((param1->unk_954.val3.unk_01 == param1->unk_954.val3.unk_02) && (v0 == 1)) {
        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_0226A930(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    u32 v0 = wifi_lobby_map_0226BCC0(&param1->unk_954, param1->unk_02);
    param1->unk_02++;

    if (v0 == 2) {
        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_0226A958(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    u32 v0;
    int v1;

    v0 = wifi_lobby_map_0226BCC0(&param1->unk_954, param1->unk_02);
    param1->unk_02++;

    if (v0 == 1) {
        wifi_lobby_map_0226BBA8(param0, param1);
    }

    wifi_lobby_map_0226BBDC(param0, param1);

    if (v0 == 2) {
        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_0226A998(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;

    if (wifi_lobby_map_0225CE70(param1->unk_08) == 1) {
        return 0;
    }

    for (v0 = 0; v0 < 18; v0++) {
        if (wifi_lobby_map_02269810(param1, v0) == 1) {
            wifi_lobby_map_02269878(param0, param1, v0);
        }
    }

    return 1;
}

static void wifi_lobby_map_0226A9D0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2)
{
    VecFx32 v0;

    {
        if (param1->unk_08 == wifi_lobby_map_0225CCAC(param0->unk_04)) {
            wifi_lobby_map_02260B3C(param0->unk_08);
        }
    }

    {
        WiFi2DCharPosition v1;
        u32 v2;

        v1 = wifi_lobby_map_0225CD34(param1->unk_08);
        v2 = wifi_lobby_map_0225C8C4(param0->unk_0C, (v1.x) / 16, (v1.y) / 16);

        if (v2 == 42) {
            param1->unk_954.val1.unk_11 = 1;
        } else {
            param1->unk_954.val1.unk_11 = 0;
        }
    }

    switch (param2) {
    case 1:
        wifi_lobby_map_02269828(param0, param1, 0, &Unk_wifi_lobby_map_0226E5A4[16]);
        wifi_lobby_map_0226B714(param0, param1, 0, 0);
        break;
    case 2:
        wifi_lobby_map_02269828(param0, param1, 0, &Unk_wifi_lobby_map_0226E5A4[16]);
        wifi_lobby_map_02269828(param0, param1, 1, &Unk_wifi_lobby_map_0226E5A4[17]);
        wifi_lobby_map_0226B714(param0, param1, 0, 2);
        wifi_lobby_map_0226B714(param0, param1, 1, 1);
        break;
    default:
    case 3:
        wifi_lobby_map_02269828(param0, param1, 0, &Unk_wifi_lobby_map_0226E5A4[16]);
        wifi_lobby_map_02269828(param0, param1, 1, &Unk_wifi_lobby_map_0226E5A4[17]);
        wifi_lobby_map_02269828(param0, param1, 2, &Unk_wifi_lobby_map_0226E5A4[18]);
        wifi_lobby_map_0226B714(param0, param1, 0, 0);
        wifi_lobby_map_0226B714(param0, param1, 1, 2);
        wifi_lobby_map_0226B714(param0, param1, 2, 1);
        break;
    }

    param1->unk_954.val1.unk_01 = param2;
    wifi_lobby_map_0225D030(param1->unk_08, 0);

    if (param1->unk_954.val1.unk_11 == 0) {
        wifi_lobby_map_0226AB14(param0, param1);
    } else {
        wifi_lobby_map_0226ABAC(param0, param1);
    }
}

static void wifi_lobby_map_0226AB14(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    VecFx32 v0;

    wifi_lobby_map_0225D054(param1->unk_08, &v0);
    wifi_lobby_map_022692B4(&param1->unk_954.val1.unk_B0, v0.x, v0.x, v0.y, v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E2E8[param1->unk_954.val1.unk_01 - 1]), v0.z, v0.z, 108);
    wifi_lobby_map_0226949C(&param1->unk_954.val1.unk_D8, 0, (10 * 182), FX32_CONST(8));
    wifi_lobby_map_0226B324(param1);

    param1->unk_954.val1.unk_02 = 0;
}

static void wifi_lobby_map_0226ABAC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    VecFx32 v0;

    wifi_lobby_map_0225D054(param1->unk_08, &v0);
    wifi_lobby_map_022692B4(&param1->unk_954.val1.unk_B0, v0.x, v0.x, v0.y, v0.y + FX32_CONST(2), v0.z, v0.z, 2);
    wifi_lobby_map_0226949C(&param1->unk_954.val1.unk_D8, 0, (10 * 182), FX32_CONST(0));
    wifi_lobby_map_0226B51C(param1);

    param1->unk_954.val1.unk_02 = 0;
}

static BOOL wifi_lobby_map_0226AC08(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    BOOL v0;

    if (param1->unk_954.val1.unk_11 == 0) {
        v0 = wifi_lobby_map_0226AC24(param0, param1);
    } else {
        v0 = wifi_lobby_map_0226AD20(param0, param1);
    }

    return v0;
}

static BOOL wifi_lobby_map_0226AC24(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    BOOL v0;
    VecFx32 v1;
    fx32 v2;
    int v3;

    v0 = wifi_lobby_map_022692DC(&param1->unk_954.val1.unk_B0, param1->unk_954.val1.unk_02);
    wifi_lobby_map_022694D0(&param1->unk_954.val1.unk_D8);
    param1->unk_954.val1.unk_02++;

    wifi_lobby_map_0225D054(param1->unk_08, &v1);
    wifi_lobby_map_02269488(&param1->unk_954.val1.unk_B0, &v1.x, &v1.y, &v1.z);
    wifi_lobby_map_02269508(&param1->unk_954.val1.unk_D8, &v2);

    if (v0 == 0) {
        v1.x += v2;
    }

    wifi_lobby_map_0225D048(param1->unk_08, &v1);
    wifi_lobby_map_0226B324(param1);

    for (v3 = 0; v3 < param1->unk_954.val1.unk_01; v3++) {
        wifi_lobby_map_0226B744(param0, param1, v3);
    }

    if (param1->unk_08 == wifi_lobby_map_0225CCAC(param0->unk_04)) {
        u32 v4 = 4;

        if (gSystem.pressedKeys & PAD_KEY_UP) {
            v4 = 0;
        }

        if (gSystem.pressedKeys & PAD_KEY_DOWN) {
            v4 = 1;
        }

        if (gSystem.pressedKeys & PAD_KEY_RIGHT) {
            v4 = 3;
        }

        if (gSystem.pressedKeys & PAD_KEY_LEFT) {
            v4 = 2;
        }

        if (v4 != 4) {
            wifi_lobby_map_0225D060(param1->unk_08, v4);
            wifi_lobby_map_0225CD04(param1->unk_08, wifi_lobby_map_0225CD34(param1->unk_08), v4);
        }
    }

    return v0;
}

static BOOL wifi_lobby_map_0226AD20(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    BOOL v0;
    VecFx32 v1;
    int v2;

    v0 = wifi_lobby_map_022692DC(&param1->unk_954.val1.unk_B0, param1->unk_954.val1.unk_02);
    wifi_lobby_map_022694D0(&param1->unk_954.val1.unk_D8);
    param1->unk_954.val1.unk_02++;

    wifi_lobby_map_0225D054(param1->unk_08, &v1);
    wifi_lobby_map_02269488(&param1->unk_954.val1.unk_B0, &v1.x, &v1.y, &v1.z);
    wifi_lobby_map_0225D048(param1->unk_08, &v1);
    wifi_lobby_map_0226B51C(param1);

    for (v2 = 0; v2 < param1->unk_954.val1.unk_01; v2++) {
        wifi_lobby_map_0226B744(param0, param1, v2);
    }

    return v0;
}

static void wifi_lobby_map_0226ADA0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    if (param1->unk_954.val1.unk_11 == 0) {
        wifi_lobby_map_0226ADBC(param0, param1);
    } else {
        wifi_lobby_map_0226AF1C(param0, param1);
    }
}

static void wifi_lobby_map_0226ADBC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    VecFx32 v0;
    VecFx32 v1;
    int v2;
    u32 v3;

    wifi_lobby_map_0225D054(param1->unk_08, &v0);
    wifi_lobby_map_022692B4(&param1->unk_954.val1.unk_B0, v0.x, v0.x, v0.y, v0.y - FX32_CONST(Unk_wifi_lobby_map_0226E2E8[param1->unk_954.val1.unk_01 - 1]), v0.z, v0.z, 10);

    param1->unk_954.val1.unk_02 = 0;
    param1->unk_954.val1.unk_00 = 0;

    for (v2 = 0; v2 < param1->unk_954.val1.unk_01; v2++) {
        Easy3DObject_GetPosition(&param1->unk_0C[v2], &v0.x, &v0.y, &v0.z);
        v3 = param1->unk_954.val1.unk_0C[v2];

        switch (v3) {
        case 0:
            v1.x = v0.x;
            v1.y = v0.y + (FX32_CONST(64));
            v1.z = v0.z - (FX32_CONST(64));
            break;
        case 1:
            v1.x = v0.x + (FX32_CONST(64));
            v1.y = v0.y + (FX32_CONST(64));
            v1.z = v0.z;
            break;
        case 2:
            v1.x = v0.x - (FX32_CONST(64));
            v1.y = v0.y + (FX32_CONST(64));
            v1.z = v0.z;
            break;
        }

        wifi_lobby_map_022692B4(&param1->unk_954.val1.unk_38[v2], v0.x, v1.x, v0.y, v1.y, v0.z, v1.z, (10 + 16));
        wifi_lobby_map_0226949C(&param1->unk_954.val1.unk_14[v2], 0, (15 * 182), (FX32_CONST(6)));
        wifi_lobby_map_0226B714(param0, param1, v2, 3);
    }

    param1->unk_954.val1.unk_10 = 0;
}

static void wifi_lobby_map_0226AF1C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    VecFx32 v0;
    VecFx32 v1;

    wifi_lobby_map_0225D054(param1->unk_08, &v0);
    wifi_lobby_map_022692B4(&param1->unk_954.val1.unk_B0, v0.x, v0.x, v0.y, v0.y - FX32_CONST(2), v0.z, v0.z, 1);

    param1->unk_954.val1.unk_02 = 0;
    param1->unk_954.val1.unk_00 = 0;
}

static BOOL wifi_lobby_map_0226AF60(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    BOOL v0;

    if (param1->unk_954.val1.unk_11 == 0) {
        v0 = wifi_lobby_map_0226AF7C(param0, param1);
    } else {
        v0 = wifi_lobby_map_0226B1D0(param0, param1);
    }

    return v0;
}

static BOOL wifi_lobby_map_0226AF7C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;

    switch (param1->unk_954.val1.unk_00) {
    case 0:
        param1->unk_954.val1.unk_02++;

        if (param1->unk_954.val1.unk_02 >= 8) {
            param1->unk_954.val1.unk_00 = 1;
        }
        break;
    case 1:
        wifi_lobby_map_0225D09C(param1->unk_08, 1);
        param1->unk_954.val1.unk_02 = 16;
        param1->unk_954.val1.unk_00 = 2;
        break;
    case 2:
        param1->unk_954.val1.unk_02--;

        if (param1->unk_954.val1.unk_02 <= 0) {
            wifi_lobby_map_0225D09C(param1->unk_08, 0);
            param1->unk_954.val1.unk_00 = 3;
            param1->unk_954.val1.unk_02 = 0;

            {
                u32 v1;

                v1 = wifi_lobby_map_0225CD60(param1->unk_08, 6);
                wifi_lobby_map_0225D060(param1->unk_08, v1);
            }
        }
        break;
    case 3: {
        BOOL v2;
        VecFx32 v3;

        v2 = wifi_lobby_map_022692DC(&param1->unk_954.val1.unk_B0, param1->unk_954.val1.unk_02);
        param1->unk_954.val1.unk_02++;

        wifi_lobby_map_0225D054(param1->unk_08, &v3);
        wifi_lobby_map_02269488(&param1->unk_954.val1.unk_B0, &v3.x, &v3.y, &v3.z);
        wifi_lobby_map_0225D048(param1->unk_08, &v3);

        if (v2 == 1) {
            param1->unk_954.val1.unk_00 = 4;
            param1->unk_954.val1.unk_02 = 0;
            param1->unk_954.val1.unk_04 = v3.y;

            wifi_lobby_map_02269510(param0, param1, SEQ_SE_PL_SUTYA2_sseq_1);
        }
    } break;
    case 4: {
        u16 v4;
        fx32 v5;
        VecFx32 v6;

        v4 = (0x7fff * param1->unk_954.val1.unk_02) / 10;
        v5 = FX_Mul(FX_SinIdx(v4), (FX32_CONST(8)));

        wifi_lobby_map_0225D054(param1->unk_08, &v6);
        v6.y = param1->unk_954.val1.unk_04 + v5;
        wifi_lobby_map_0225D048(param1->unk_08, &v6);

        if ((param1->unk_954.val1.unk_02 + 1) > 10) {
            wifi_lobby_map_0225D030(param1->unk_08, 1);

            {
                if (param1->unk_08 == wifi_lobby_map_0225CCAC(param0->unk_04)) {
                    wifi_lobby_map_02260B38(param0->unk_08, param1->unk_08);
                }
            }

            return 1;
        } else {
            param1->unk_954.val1.unk_02++;
        }
    } break;
    }

    param1->unk_954.val1.unk_10++;

    for (v0 = 0; v0 < param1->unk_954.val1.unk_01; v0++) {
        {
            BOOL v7;
            VecFx32 v8;
            fx32 v9;
            BOOL v10;

            v7 = wifi_lobby_map_022692DC(&param1->unk_954.val1.unk_38[v0], param1->unk_954.val1.unk_10);

            if (v7 == 0) {
                wifi_lobby_map_022694D0(&param1->unk_954.val1.unk_14[v0]);
                Easy3DObject_GetPosition(&param1->unk_0C[v0], &v8.x, &v8.y, &v8.z);
                wifi_lobby_map_02269488(&param1->unk_954.val1.unk_38[v0], &v8.x, &v8.y, &v8.z);
                wifi_lobby_map_02269508(&param1->unk_954.val1.unk_14[v0], &v9);

                v8.x += v9;

                Easy3DObject_SetPosition(&param1->unk_0C[v0], v8.x, v8.y, v8.z);
            } else {
                v10 = wifi_lobby_map_0226B714(param0, param1, v0, 4);

                if (v10 == 1) {
                    wifi_lobby_map_02269510(param0, param1, SEQ_SE_PL_HIROBA20_sseq);
                }
            }
        }

        wifi_lobby_map_0226B744(param0, param1, v0);
    }

    return 0;
}

static BOOL wifi_lobby_map_0226B1D0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;

    for (v0 = 0; v0 < param1->unk_954.val1.unk_01; v0++) {
        wifi_lobby_map_0226B744(param0, param1, v0);
    }

    switch (param1->unk_954.val1.unk_00) {
    case 0:
        wifi_lobby_map_02269510(param0, param1, SEQ_SE_PL_HIROBA20_sseq);

        for (v0 = 0; v0 < param1->unk_954.val1.unk_01; v0++) {
            wifi_lobby_map_0226B714(param0, param1, v0, 4);
        }

        param1->unk_954.val1.unk_00 = 1;
        break;
    case 1:
        wifi_lobby_map_0225D09C(param1->unk_08, 1);
        param1->unk_954.val1.unk_02 = 8;
        param1->unk_954.val1.unk_00 = 2;
        break;
    case 2:
        param1->unk_954.val1.unk_02--;

        if (param1->unk_954.val1.unk_02 <= 0) {
            wifi_lobby_map_0225D09C(param1->unk_08, 0);
            param1->unk_954.val1.unk_00 = 3;
            param1->unk_954.val1.unk_02 = 0;

            {
                u32 v1;

                v1 = wifi_lobby_map_0225CD60(param1->unk_08, 6);
                wifi_lobby_map_0225D060(param1->unk_08, v1);
            }
        }
        break;
    case 3: {
        BOOL v2;
        VecFx32 v3;

        v2 = wifi_lobby_map_022692DC(&param1->unk_954.val1.unk_B0, param1->unk_954.val1.unk_02);
        param1->unk_954.val1.unk_02++;

        wifi_lobby_map_0225D054(param1->unk_08, &v3);
        wifi_lobby_map_02269488(&param1->unk_954.val1.unk_B0, &v3.x, &v3.y, &v3.z);
        wifi_lobby_map_0225D048(param1->unk_08, &v3);

        if (v2 == 1) {
            param1->unk_954.val1.unk_02 = 0;
            param1->unk_954.val1.unk_04 = v3.y;

            wifi_lobby_map_02269510(param0, param1, SEQ_SE_PL_SUTYA2_sseq_1);
            wifi_lobby_map_0225D030(param1->unk_08, 1);

            {
                if (param1->unk_08 == wifi_lobby_map_0225CCAC(param0->unk_04)) {
                    wifi_lobby_map_02260B38(param0->unk_08, param1->unk_08);
                }
            }

            return 1;
        }
    } break;
    }

    return 0;
}

static void wifi_lobby_map_0226B324(WiFiLobbyMapAttraction *param0)
{
    VecFx32 v0;

    wifi_lobby_map_0225D054(param0->unk_08, &v0);

    switch (param0->unk_954.val1.unk_01) {
    case 1:
        Easy3DObject_SetPosition(&param0->unk_0C[0], v0.x + FX32_CONST(Unk_wifi_lobby_map_0226E328[2].x), v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E328[2].y), v0.z + (FX32_CONST(1)));
        break;
    case 2:
        Easy3DObject_SetPosition(&param0->unk_0C[0], v0.x + FX32_CONST(Unk_wifi_lobby_map_0226E328[0].x), v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E328[0].y), v0.z + (FX32_CONST(1)));
        Easy3DObject_SetPosition(&param0->unk_0C[1], v0.x + FX32_CONST(Unk_wifi_lobby_map_0226E328[1].x), v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E328[1].y), v0.z + (FX32_CONST(1)));
        break;
    default:
    case 3:
        Easy3DObject_SetPosition(&param0->unk_0C[0], v0.x + FX32_CONST(Unk_wifi_lobby_map_0226E328[2].x), v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E328[2].y), v0.z + (FX32_CONST(1)));
        Easy3DObject_SetPosition(&param0->unk_0C[1], v0.x + FX32_CONST(Unk_wifi_lobby_map_0226E328[0].x), v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E328[0].y), v0.z + (FX32_CONST(1)));
        Easy3DObject_SetPosition(&param0->unk_0C[2], v0.x + FX32_CONST(Unk_wifi_lobby_map_0226E328[1].x), v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E328[1].y), v0.z + (FX32_CONST(1)));
        break;
    }
}

static void wifi_lobby_map_0226B51C(WiFiLobbyMapAttraction *param0)
{
    VecFx32 v0;

    wifi_lobby_map_0225D054(param0->unk_08, &v0);

    switch (param0->unk_954.val1.unk_01) {
    case 1:
        Easy3DObject_SetPosition(&param0->unk_0C[0], v0.x + FX32_CONST(Unk_wifi_lobby_map_0226E340[2].x), v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E340[2].y), v0.z + (-FX32_CONST(8)));
        break;
    case 2:
        Easy3DObject_SetPosition(&param0->unk_0C[0], v0.x + FX32_CONST(Unk_wifi_lobby_map_0226E340[0].x), v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E340[0].y), v0.z + (-FX32_CONST(8)));
        Easy3DObject_SetPosition(&param0->unk_0C[1], v0.x + FX32_CONST(Unk_wifi_lobby_map_0226E340[1].x), v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E340[1].y), v0.z + (-FX32_CONST(8)));
        break;
    default:
    case 3:
        Easy3DObject_SetPosition(&param0->unk_0C[0], v0.x + FX32_CONST(Unk_wifi_lobby_map_0226E340[2].x), v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E340[2].y), v0.z + (-FX32_CONST(8)));
        Easy3DObject_SetPosition(&param0->unk_0C[1], v0.x + FX32_CONST(Unk_wifi_lobby_map_0226E340[0].x), v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E340[0].y), v0.z + (-FX32_CONST(8)));
        Easy3DObject_SetPosition(&param0->unk_0C[2], v0.x + FX32_CONST(Unk_wifi_lobby_map_0226E340[1].x), v0.y + FX32_CONST(Unk_wifi_lobby_map_0226E340[1].y), v0.z + (-FX32_CONST(8)));
        break;
    }
}

static BOOL wifi_lobby_map_0226B714(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2, u32 param3)
{
    if (param1->unk_954.val1.unk_0C[param2] != param3) {
        param1->unk_954.val1.unk_0C[param2] = param3;
        param1->unk_954.val1.unk_08[param2] = 0;
        wifi_lobby_map_02269A90(param0, param1, param2, 0, (param3 * (FX32_ONE * 2)));
        return 1;
    }

    return 0;
}

static void wifi_lobby_map_0226B744(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2)
{
    fx32 v0;
    u32 v1 = param1->unk_954.val1.unk_0C[param2];

    if (param1->unk_954.val1.unk_08[param2] <= 0) {
        v0 = wifi_lobby_map_02269AE8(param0, param1, param2, 0);

        if (v0 == (v1 * (FX32_ONE * 2))) {
            v0 = (v1 * (FX32_ONE * 2)) + FX32_ONE;
        } else {
            if (v1 != 4) {
                v0 = (v1 * (FX32_ONE * 2));
            } else {
                Easy3DObject_SetVisible(&param1->unk_0C[param2], 0);
            }
        }

        wifi_lobby_map_02269A90(param0, param1, param2, 0, v0);

        param1->unk_954.val1.unk_08[param2] = 8;
    }

    param1->unk_954.val1.unk_08[param2]--;
}

static void wifi_lobby_map_0226B7B0(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2)
{
    int v0, v1;
    VecFx32 v2;
    VecFx32 v3;
    VecFx32 v4;
    u32 v5;
    u32 v6;

    wifi_lobby_map_0225D054(param1->unk_08, &v2);

    for (v0 = 0; v0 < param2; v0++) {
        v6 = 13 + v0;

        if (v6 > 15) {
            v6 = 15;
        }

        for (v1 = 0; v1 < 4; v1++) {
            v5 = (v0 * 4) + v1;
            wifi_lobby_map_02269828(param0, param1, v5, &Unk_wifi_lobby_map_0226E5A4[v6]);
            VEC_Add(&v2, &Unk_wifi_lobby_map_0226E370[v1], &v3);
            VEC_Add(&v3, &Unk_wifi_lobby_map_0226E3A0[v1], &v4);
            Easy3DObject_SetPosition(&param1->unk_0C[v5], v3.x, v3.y, v3.z);
            Easy3DObject_SetVisible(&param1->unk_0C[v5], 0);
            param1->unk_954.val3.unk_04[v5] = 0;
            wifi_lobby_map_022692B4(&param1->unk_954.val3.unk_14[v5], v3.x, v4.x, v3.y, v4.y, v3.z, v4.z, 14);
        }
    }

    param1->unk_954.val3.unk_02 = param2;
    param1->unk_954.val3.unk_01 = 0;
    param1->unk_954.val3.unk_00 = 0;
    param1->unk_954.val3.unk_03 = 0;
}

static BOOL wifi_lobby_map_0226B8C4(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2)
{
    BOOL v0;
    VecFx32 v1;

    param1->unk_954.val3.unk_04[param2]++;

    v0 = wifi_lobby_map_022692DC(&param1->unk_954.val3.unk_14[param2], param1->unk_954.val3.unk_04[param2]);

    wifi_lobby_map_02269488(&param1->unk_954.val3.unk_14[param2], &v1.x, &v1.y, &v1.z);
    Easy3DObject_SetPosition(&param1->unk_0C[param2], v1.x, v1.y, v1.z);
    wifi_lobby_map_022699BC(param0, param1, param2, 0);

    return v0;
}

static void wifi_lobby_map_0226B92C(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2)
{
    int v0;
    VecFx32 v1;

    for (v0 = 0; v0 < param2; v0++) {
        wifi_lobby_map_02269828(param0, param1, v0, &Unk_wifi_lobby_map_0226E5A4[0 + v0]);
        wifi_lobby_map_0225D054(param1->unk_08, &v1);

        v1.y += (FX32_CONST(8));
        v1.z += (FX32_CONST(6));

        Easy3DObject_SetPosition(&param1->unk_0C[v0], v1.x, v1.y, v1.z);
        Easy3DObject_SetVisible(&param1->unk_0C[v0], 0);
    }

    param1->unk_954.val4.unk_00 = param2;
}

static BOOL wifi_lobby_map_0226B998(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2)
{
    BOOL v0;
    u32 v1;
    WiFiLobbyMapAttractionAnim v2;

    v1 = (param1->unk_02 * 12) / 48;

    if (v1 != param1->unk_954.val5.unk_00) {
        param1->unk_954.val5.unk_00 = v1;

        if (v1 > 0) {
            v2 = Unk_wifi_lobby_map_0226E514[param2][v1 - 1];
            Easy3DObject_SetVisible(&param1->unk_0C[v2.unk_00], 0);
        }

        v2 = Unk_wifi_lobby_map_0226E514[param2][v1];

        if (0 != v2.unk_02) {
            wifi_lobby_map_02269A90(param0, param1, v2.unk_00, 0, FX32_CONST(v2.unk_02));
            wifi_lobby_map_02269A90(param0, param1, v2.unk_00, 1, FX32_CONST(v2.unk_02));
            Easy3DObject_SetVisible(&param1->unk_0C[v2.unk_00], 1);
        } else {
            Easy3DObject_SetVisible(&param1->unk_0C[v2.unk_00], 0);
        }
    }

    if (param1->unk_02 < 48) {
        param1->unk_02++;
    }

    if (param1->unk_02 >= 48) {
        return 1;
    }

    return 0;
}

static void wifi_lobby_map_0226BAC8(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1, u32 param2)
{
    int v0;
    VecFx32 v1;

    for (v0 = 0; v0 < param2; v0++) {
        wifi_lobby_map_02269828(param0, param1, v0, &Unk_wifi_lobby_map_0226E5A4[6 + v0]);
        wifi_lobby_map_0225D054(param1->unk_08, &v1);

        v1.y += (FX32_CONST(8));

        Easy3DObject_SetPosition(&param1->unk_0C[v0], v1.x, v1.y, v1.z);
        Easy3DObject_SetVisible(&param1->unk_0C[v0], 0);
    }

    param1->unk_954.val6.unk_00 = 0xff;
    param1->unk_954.val6.unk_02 = param2;
}

static void wifi_lobby_map_0226BB34(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    VecFx32 v0;
    int v1;

    wifi_lobby_map_0225D054(param1->unk_08, &v0);

    v0.z += (-FX32_CONST(10));
    v0.x += (-FX32_CONST(4));
    v0.y += (FX32_CONST(16)) + (-FX32_CONST(0));

    for (v1 = 0; v1 < 2; v1++) {
        wifi_lobby_map_02269828(param0, param1, 16 + v1, &Unk_wifi_lobby_map_0226E5A4[37 + v1]);
        Easy3DObject_SetPosition(&param1->unk_0C[v1 + 16], v0.x + (v1 * (FX32_CONST(24))), v0.y, v0.z);
    }
}

static void wifi_lobby_map_0226BBA8(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;

    param1->unk_954.val7.unk_3B8 = 1;
    param1->unk_954.val7.unk_3BA = 0;

    for (v0 = 0; v0 < 2; v0++) {
        Easy3DObject_SetVisible(&param1->unk_0C[v0 + 16], 1);
    }
}

static void wifi_lobby_map_0226BBDC(WiFiLobbyMapAttractionManager *param0, WiFiLobbyMapAttraction *param1)
{
    int v0;

    if (param1->unk_954.val7.unk_3B8 == 0) {
        return;
    }

    if (param1->unk_954.val7.unk_3BA < 13) {
        param1->unk_954.val7.unk_3BA++;
    } else {
        param1->unk_954.val7.unk_3B8 = 0;
    }

    for (v0 = 0; v0 < 2; v0++) {
        if (param1->unk_954.val7.unk_3BA < 13) {
            wifi_lobby_map_022699BC(param0, param1, v0 + 16, 0);
        } else {
            Easy3DObject_SetVisible(&param1->unk_0C[v0 + 16], 0);
        }
    }
}

static void wifi_lobby_map_0226BC40(WiFiLobbyMapAttractionState *param0, const WiFiLobbyMapAttractionPart *param1, u32 param2, u32 param3, u32 param4, WiFiLobbyMapAttraction *param5)
{
    int v0;

    param0->val7.unk_3B0 = param1;
    param0->val7.unk_3B4 = param2;
    param0->val7.unk_3B6 = param3;

    for (v0 = 0; v0 < 4; v0++) {
        wifi_lobby_map_0226BD64(&param0->val7.unk_00[v0], &param5->unk_0C[(v0 * 4) + 0], &param5->unk_0C[(v0 * 4) + 1], &param5->unk_0C[(v0 * 4) + 2], &param5->unk_0C[(v0 * 4) + 3], param5->unk_08, param4);
    }
}

static int wifi_lobby_map_0226BCC0(WiFiLobbyMapAttractionState *param0, u32 param1)
{
    int v0;
    WiFiLobbyMapAttractionPart v1;
    BOOL v2;
    BOOL v3;
    BOOL v4 = 0;

    for (v0 = 0; v0 < param0->val7.unk_3B4; v0++) {
        v1 = param0->val7.unk_3B0[v0];

        if (v1.unk_00 == param1) {
            GF_ASSERT(v1.unk_02 < 4);
            GF_ASSERT(v1.unk_03 <= 4);
            wifi_lobby_map_0226BDA0(&param0->val7.unk_00[v1.unk_02], v1.unk_03);
            v4 = 1;
        }
    }

    v3 = 1;

    for (v0 = 0; v0 < 4; v0++) {
        v2 = wifi_lobby_map_0226BDE8(&param0->val7.unk_00[v0]);

        if (v2 == 0) {
            v3 = 0;
        }
    }

    if ((param0->val7.unk_3B6 <= param1) && (v3 == 1)) {
        v4 = 2;
    }

    return v4;
}

static void wifi_lobby_map_0226BD64(WiFiLobbyMapAttractionCar *param0, Easy3DObject *param1, Easy3DObject *param2, Easy3DObject *param3, Easy3DObject *param4, const WiFiLobbyMapActor *param5, u32 param6)
{
    GF_ASSERT(param6 < 3);

    param0->unk_D8[0] = param1;
    param0->unk_D8[1] = param2;
    param0->unk_D8[2] = param3;
    param0->unk_D8[3] = param4;
    param0->unk_E8 = param5;
    param0->unk_02 = param6;
}

static void wifi_lobby_map_0226BDA0(WiFiLobbyMapAttractionCar *param0, u32 param1)
{
    int v0;

    static void (*const v1[3])(WiFiLobbyMapAttractionCar *, const WiFiLobbyMapActor *) = {
        wifi_lobby_map_0226BE3C, wifi_lobby_map_0226BFE4, wifi_lobby_map_0226C17C
    };

    for (v0 = 0; v0 < param1; v0++) {
        Easy3DObject_SetVisible(param0->unk_D8[v0], 1);
    }

    param0->unk_00 = 0;
    param0->unk_06 = 1;
    param0->unk_04 = param1;

    v1[param0->unk_02](param0, param0->unk_E8);
}

static BOOL wifi_lobby_map_0226BDE8(WiFiLobbyMapAttractionCar *param0)
{
    int v0;
    BOOL v1;

    static BOOL (*const v2[3])(WiFiLobbyMapAttractionCar *) = {
        wifi_lobby_map_0226BF5C, wifi_lobby_map_0226C0D8, wifi_lobby_map_0226C1DC
    };

    if (param0->unk_06 == 0) {
        return 1;
    }

    v1 = v2[param0->unk_02](param0);

    param0->unk_00++;

    if (v1 == 1) {
        for (v0 = 0; v0 < param0->unk_04; v0++) {
            Easy3DObject_SetVisible(param0->unk_D8[v0], 0);
        }

        param0->unk_06 = 0;
    }

    return v1;
}

static void wifi_lobby_map_0226BE3C(WiFiLobbyMapAttractionCar *param0, const WiFiLobbyMapActor *param1)
{
    int v0;
    VecFx32 v1;
    VecFx32 v2;
    u16 v3;

    wifi_lobby_map_0225D054(param1, &v1);

    v1.x += (FX32_CONST(8));
    v1.y += (FX32_CONST(16));
    v1.z += (-FX32_CONST(8));

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        switch (v0) {
        case 0:
            v2.x = v1.x - (FX32_CONST(12));
            v2.y = v1.y + (FX32_CONST(16));
            v2.z = v1.z + 0;
            v3 = ((0 * 0xffff) / 360);
            break;
        case 1:
            v2.x = v1.x + (FX32_CONST(12));
            v2.y = v1.y + (FX32_CONST(16));
            v2.z = v1.z + 0;
            v3 = ((180 * 0xffff) / 360);
            break;
        case 2:
            v2.x = v1.x - (FX32_CONST(8));
            v2.y = v1.y + (FX32_CONST(16));
            v2.z = v1.z - (FX32_CONST(6));
            v3 = ((180 * 0xffff) / 360);
            break;
        case 3:
            v2.x = v1.x + (FX32_CONST(8));
            v2.y = v1.y + (FX32_CONST(16));
            v2.z = v1.z - (FX32_CONST(6));
            v3 = ((0 * 0xffff) / 360);
            break;
        }

        wifi_lobby_map_022692B4(&param0->unk_08[v0], v1.x, v2.x, v1.y, v2.y, v1.z, v2.z, 18);
        wifi_lobby_map_0226949C(&param0->unk_A8[v0], v3, ((18 * 0xffff) / 360), (FX32_CONST(6)));
        Easy3DObject_SetPosition(param0->unk_D8[v0], v1.x, v1.y, v1.z);
    }
}

static BOOL wifi_lobby_map_0226BF5C(WiFiLobbyMapAttractionCar *param0)
{
    int v0;
    BOOL v1;
    VecFx32 v2;
    fx32 v3;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        wifi_lobby_map_022694D0(&param0->unk_A8[v0]);

        v1 = wifi_lobby_map_022692DC(&param0->unk_08[v0], param0->unk_00);

        wifi_lobby_map_02269508(&param0->unk_A8[v0], &v3);
        wifi_lobby_map_02269488(&param0->unk_08[v0], &v2.x, &v2.y, &v2.z);

        v2.x += v3;

        Easy3DObject_SetPosition(param0->unk_D8[v0], v2.x, v2.y, v2.z);
    }

    return v1;
}

static void wifi_lobby_map_0226BFE4(WiFiLobbyMapAttractionCar *param0, const WiFiLobbyMapActor *param1)
{
    int v0;
    VecFx32 v1;
    VecFx32 v2;

    wifi_lobby_map_0225D054(param1, &v1);

    v1.x += (FX32_CONST(8));
    v1.y += (FX32_CONST(8));
    v1.z += (-FX32_CONST(8));

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        switch (v0) {
        case 0:
            v2.x = v1.x - (FX32_CONST(16));
            v2.y = v1.y;
            v2.z = v1.z + (FX32_CONST(16));
            break;
        case 1:
            v2.x = v1.x + (FX32_CONST(16));
            v2.y = v1.y;
            v2.z = v1.z + (FX32_CONST(16));
            break;
        case 2:
            if (param0->unk_04 == 3) {
                v2.x = v1.x;
                v2.y = v1.y;
                v2.z = v1.z - ((FX32_CONST(16)) + (FX32_CONST(16)));
            } else {
                v2.x = v1.x - (FX32_CONST(16));
                v2.y = v1.y;
                v2.z = v1.z - (FX32_CONST(16));
            }
            break;
        case 3:
            v2.x = v1.x + (FX32_CONST(16));
            v2.y = v1.y;
            v2.z = v1.z - (FX32_CONST(16));
            break;
        }

        wifi_lobby_map_022692B4(&param0->unk_08[v0], v1.x, v2.x, v1.y, v2.y, v1.z, v2.z, 19);
        wifi_lobby_map_0226949C(&param0->unk_A8[v0], ((30 * 0xffff) / 360), ((10 * 0xffff) / 360), (FX32_CONST(32)));
    }

    wifi_lobby_map_0226C0D8(param0);
}

static BOOL wifi_lobby_map_0226C0D8(WiFiLobbyMapAttractionCar *param0)
{
    int v0;
    BOOL v1;
    VecFx32 v2;
    fx32 v3;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        if (param0->unk_00 == 14) {
            wifi_lobby_map_0226949C(&param0->unk_A8[v0], ((0 * 0xffff) / 360), ((20 * 0xffff) / 360), (FX32_CONST(12)));
        } else {
            wifi_lobby_map_022694D0(&param0->unk_A8[v0]);
        }

        wifi_lobby_map_022692DC(&param0->unk_08[v0], param0->unk_00);
        wifi_lobby_map_02269508(&param0->unk_A8[v0], &v3);
        wifi_lobby_map_02269488(&param0->unk_08[v0], &v2.x, &v2.y, &v2.z);

        v2.y += v3;

        Easy3DObject_SetPosition(param0->unk_D8[v0], v2.x, v2.y, v2.z);
    }

    if (param0->unk_00 >= (14 + 8)) {
        return 1;
    }

    return 0;
}

static void wifi_lobby_map_0226C17C(WiFiLobbyMapAttractionCar *param0, const WiFiLobbyMapActor *param1)
{
    int v0;
    VecFx32 v1;
    VecFx32 v2;

    wifi_lobby_map_0225D054(param1, &v1);

    v1.x += (FX32_CONST(8));
    v1.y += (FX32_CONST(16)) + (FX32_CONST(4));
    v1.z += (-FX32_CONST(8));

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        wifi_lobby_map_0226C2A4(param0, v0, &v1, (FX32_CONST(13)), (FX32_CONST(5)), (FX32_CONST(7)), (FX32_CONST(14)), 8);
    }
}

static BOOL wifi_lobby_map_0226C1DC(WiFiLobbyMapAttractionCar *param0)
{
    int v0;
    BOOL v1;
    VecFx32 v2;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        v1 = wifi_lobby_map_022692DC(&param0->unk_08[v0], param0->unk_00);

        wifi_lobby_map_02269488(&param0->unk_08[v0], &v2.x, &v2.y, &v2.z);
        Easy3DObject_SetPosition(param0->unk_D8[v0], v2.x, v2.y, v2.z);

        if (v1 == 1) {
            if (param0->unk_07 == 0) {
                wifi_lobby_map_0226C2A4(param0, v0, &v2, (-FX32_CONST(3)), (FX32_CONST(4)), (-FX32_CONST(3)), (FX32_CONST(3)), 3);
            } else {
                wifi_lobby_map_0226C2A4(param0, v0, &v2, (FX32_CONST(10)), (FX32_CONST(5)), (FX32_CONST(6)), (FX32_CONST(10)), 4);
            }
        }
    }

    if (v1 == 1) {
        if ((param0->unk_07 + 1) < 3) {
            param0->unk_07++;
            param0->unk_00 = 0;
        } else {
            return 1;
        }
    }

    return 0;
}

static void wifi_lobby_map_0226C2A4(WiFiLobbyMapAttractionCar *param0, u32 param1, const VecFx32 *param2, fx32 param3, fx32 param4, fx32 param5, fx32 param6, u32 param7)
{
    VecFx32 v0;

    switch (param1) {
    case 0:
        v0.x = param2->x - param3;
        v0.y = param2->y + param4;
        v0.z = param2->z;
        break;
    case 1:
        v0.x = param2->x + param3;
        v0.y = param2->y + param4;
        v0.z = param2->z;
        break;
    case 2:
        v0.x = param2->x - param5;
        v0.y = param2->y + param6;
        v0.z = param2->z;
        break;
    case 3:
        v0.x = param2->x + param5;
        v0.y = param2->y + param6;
        v0.z = param2->z;
        break;
    }

    wifi_lobby_map_022692B4(&param0->unk_08[param1], param2->x, v0.x, param2->y, v0.y, param2->z, v0.z, param7);
    Easy3DObject_SetPosition(param0->unk_D8[param1], param2->x, param2->y, param2->z);
}
