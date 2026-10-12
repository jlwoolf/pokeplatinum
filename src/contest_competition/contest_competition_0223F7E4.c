#include "contest_competition/contest_competition_0223F7E4.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/font_oam.h"
#include "struct_decls/struct_02012744_decl.h"
#include "struct_defs/struct_font_oam_template.h"

#include "contest_competition/contest_competition_0223F118.h"
#include "contest_competition/contest_competition_02241270.h"
#include "contest_competition/contest_competition_022413D8.h"
#include "contest_competition/contest_competition_0224F080.h"
#include "contest_competition/contest_competition_02252AB0.h"
#include "contest_competition/struct_acting_competition_scene.h"
#include "contest_competition/struct_acting_match_state.h"
#include "contest_competition/struct_contest_game_sprite_group_decl.h"

#include "assert.h"
#include "bg_window.h"
#include "char_transfer.h"
#include "contest.h"
#include "font.h"
#include "graphics.h"
#include "heap.h"
#include "message.h"
#include "message_util.h"
#include "move_table.h"
#include "narc.h"
#include "palette.h"
#include "pokemon.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "touch_screen.h"
#include "font_oam.h"
#include "contest_util.h"

#include "res/text/bank/contest_text.h"

typedef struct {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
} ActingMoveMenuCursorOffset;

typedef struct {
    u8 unk_00;
    s8 unk_01;
    s8 unk_02;
    u8 unk_03;
} ActingMoveMenuCursorMove;

typedef struct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} ActingMoveMenuRect;

typedef struct {
    s16 unk_00;
    s16 unk_02;
    union {
        struct {
            ManagedSprite *unk_00[3];
            const s16 *unk_0C;
            const ActingMoveMenuRect *unk_10;
            int unk_14;
            u8 unk_18;
            u8 unk_19;
        } unk_04_val1;
    };
} ActingMoveMenuInput;

typedef struct {
    int unk_00;
    s16 unk_04;
    s16 unk_06;
    u8 unk_08;
    u8 unk_09;
} ActingMoveMenuCursorAnim;

typedef struct {
    const ActingMoveMenuRect *unk_00;
    u8 unk_04;
    s8 unk_05;
} ActingMoveMenuSelection;

typedef struct {
    FontOAM *unk_00;
    CharTransferAllocation unk_04;
    u16 unk_10;
} ActingMoveMenuLabel;

typedef struct {
    Window unk_00;
    u16 unk_10;
    u16 unk_12;
} ActingMoveMenuWindow;

typedef struct {
    ActingMoveMenuWindow unk_00[4];
    ActingMoveMenuWindow unk_50[4];
    ActingMoveMenuWindow unk_A0[4];
    ActingMoveMenuWindow unk_F0[3];
    u8 moveContestEffect[LEARNED_MOVES_MAX];
    u8 moveContestType[LEARNED_MOVES_MAX];
} ActingMoveMenuMoves;

typedef struct ActingMoveMenu_t {
    Contest *unk_00;
    ActingCompetitionScene *unk_04;
    ActingMatchState *unk_08;
    void *unk_0C;
    SysTask *unk_10;
    SysTask *unk_14;
    ActingMoveMenuSelection unk_18;
    u16 *unk_20[5];
    u16 *unk_34[2];
    FontOAMManager *unk_3C;
    ActingMoveMenuLabel unk_40[12];
    ManagedSprite *unk_118[4];
    ManagedSprite *unk_128;
    ManagedSprite *unk_12C[4][6];
    ActingMoveMenuMoves unk_18C;
    void *unk_2C0;
    NNSG2dCharacterData *unk_2C4;
    s8 unk_2C8;
    u8 unk_2C9;
    ActingMoveMenuInput unk_2CC;
    ActingMoveMenuCursorAnim unk_2EC;
    ActingMoveMenuCursorOffset unk_2F6;
    ContestGameSpriteGroup *unk_2FC;
    ActingMoveMenuCursorMove unk_300;
    u8 unk_304;
} ActingMoveMenu;

typedef struct {
    u16 unk_00;
    u16 unk_02;
    union {
        struct {
            u16 unk_04_val1_unk_00;
            u16 unk_04_val1_unk_02;
            u16 unk_04_val1_unk_04;
            u16 unk_04_val1_unk_06;
        };
        u16 unk_04_val2[4];
    };
    union {
        struct {
            u16 unk_0C_val1_unk_00;
            u16 unk_0C_val1_unk_02;
            u16 unk_0C_val1_unk_04;
            u16 unk_0C_val1_unk_06;
        };
        u16 unk_0C_val2[4];
    };
    const TouchScreenRect *touchScreenRect;
    const int *unk_18;
    const u8 *unk_1C;
    int (*unk_20)(ActingMoveMenu *param0, int param1);
    void (*unk_24)(ActingMoveMenu *param0, int param1);
    void (*unk_28)(ActingMoveMenu *param0, int param1, int param2);
    int (*unk_2C)(ActingMoveMenu *param0, int param1, int param2);
} ActingMoveMenuPage;

static void *contest_competition_0223F7E4(void);
static void contest_competition_0223FBD4(ActingMoveMenu *param0, int param1, int param2);
static void contest_competition_0223FCAC(ActingMoveMenu *param0, int param1, int param2);
static void contest_competition_0223FF38(ActingMoveMenu *param0, int param1, int param2);
static int contest_competition_0223FFF4(ActingMoveMenu *param0, int param1, int param2);
static int contest_competition_02240094(ActingMoveMenu *param0, int param1, int param2);
static void contest_competition_0224028C(ActingMoveMenu *param0);
static void contest_competition_022402A8(ActingMoveMenu *param0);
static void contest_competition_022404B0(ActingMoveMenu *param0);
static void contest_competition_022402E8(ActingMoveMenu *param0, u16 param1[]);
static void contest_competition_02240388(ActingMoveMenu *param0);
static void contest_competition_02240424(ActingMoveMenu *param0, int moveContestType, int moveSlot);
static void contest_competition_022404A8(ActingMoveMenu *param0);
static void contest_competition_022404CC(SysTaskFunc param0, ActingMoveMenu *param1);
static void contest_competition_022404FC(ActingMoveMenu *param0);
static void contest_competition_0224051C(SysTask *param0, void *param1);
static void contest_competition_02240658(SysTask *param0, void *param1);
static void contest_competition_022411E4(SysTask *param0, void *param1);
static void contest_competition_02241220(SysTask *param0, void *param1);
static void contest_competition_02240138(ActingMoveMenu *param0, ActingMoveMenuLabel *param1, const String *string, enum Font font, u32 param4, int param5, int param6, int x, int y, int param9, ActingMoveMenuWindow *param10);
static void contest_competition_02240260(ActingMoveMenu *param0);
void contest_competition_0223F80C(BgConfig *param0);
void contest_competition_0223F864(BgConfig *param0);
void *contest_competition_0223F88C(Contest *param0, ActingCompetitionScene *param1, ActingMatchState *param2);
void contest_competition_0223F960(ActingMoveMenu *param0);
void contest_competition_0223F9C4(ActingMoveMenu *param0, int param1, int param2, void *param3);
int contest_competition_0223FAF8(ActingMoveMenu *param0);
BOOL contest_competition_0223FBC0(ActingMoveMenu *param0);
static void contest_competition_022409F4(ActingMoveMenu *param0);
static void contest_competition_02240BF4(ActingMoveMenu *param0, const String *param1, int param2, ActingMoveMenuWindow *param3, u32 param4);
static void contest_competition_02240C60(const String *param0, int param1, int *param2, int *param3);
static void contest_competition_02240950(SysTask *param0, void *param1);
static void contest_competition_02240930(ActingMoveMenu *param0, int param1);
static int contest_competition_02240C90(ActingMoveMenu *param0);
static int contest_competition_02240D04(ActingMoveMenu *param0, int param1);
static void contest_competition_02240E68(ActingMoveMenu *param0, int param1);
static int contest_competition_02240EA4(ActingMoveMenu *param0, int param1);
static void contest_competition_02240FC4(ActingMoveMenu *param0, int param1);
static u32 contest_competition_02241004(ActingMoveMenuCursorMove *param0, int param1, int param2, const u8 *param3);

__attribute__((aligned(4))) static const u16 Unk_contest_competition_02253250[] = {
    0x8,
    0x7,
    0x6,
    0xA,
    0x1D
};

__attribute__((aligned(4))) static const u16 Unk_contest_competition_02253238[] = {
    0x1F,
    0x28
};

__attribute__((aligned(4))) static const u16 Unk_contest_competition_02253278[][2] = {
    { 0x13, 0x20 },
    { 0x93, 0x20 },
    { 0x13, 0x80 },
    { 0x93, 0x80 }
};

__attribute__((aligned(4))) static const u16 Unk_contest_competition_02253314[][2][2] = {
    {
        { 0x13, 0x40 },
        { 0x13, 0x50 },
    },
    {
        { 0x93, 0x40 },
        { 0x93, 0x50 },
    },
    {
        { 0x13, 0xA0 },
        { 0x13, 0xB0 },
    },
    {
        { 0x93, 0xA0 },
        { 0x93, 0xB0 },
    },
};

__attribute__((aligned(4))) static const u16 Unk_contest_competition_0225325C[][2] = {
    { 0x28, 0x48 },
    { 0x80, 0x48 },
    { 0xD8, 0x48 }
};

__attribute__((aligned(4))) static const int Unk_contest_competition_02253334[][2] = {
    { 0x3F, 0x34 },
    { 0xBF, 0x34 },
    { 0x3F, 0x94 },
    { 0xBF, 0x94 }
};

__attribute__((aligned(4))) const u16 Unk_contest_competition_022534B8[] = {
    0x75CD,
    0x7fff,
    0x67ff,
    0x4bff,
    0x2fff,
    0x13ff,
    0x039f,
    0x33E,
    0x154D,
    0x4fff,
    0x2108,
    0x7C2B,
    0x318C,
    0x4631,
    0x5AD6,
    0x0,
    0x75CD,
    0x7fff,
    0x7f9f,
    0x7f3f,
    0x7adf,
    0x729f,
    0x6a5f,
    0x659f,
    0x1CED,
    0x7f5f,
    0x2108,
    0x7C2B,
    0x318C,
    0x4631,
    0x5AD6,
    0x0,
    0x75CD,
    0x7fff,
    0x63fc,
    0x37f7,
    0x2f73,
    0x2730,
    0x1f0c,
    0x16C8,
    0x1146,
    0x5bf8,
    0x2108,
    0x7C2B,
    0x318C,
    0x4631,
    0x5AD6,
    0x0,
    0x75CD,
    0x7fff,
    0x4f1f,
    0x4adf,
    0x467f,
    0x3e1f,
    0x39bf,
    0x00bf,
    0x1CED,
    0x5b5f,
    0x2108,
    0x7C2B,
    0x318C,
    0x4631,
    0x5AD6,
    0x0,
    0x75CD,
    0x7fff,
    0x7ff9,
    0x7f93,
    0x7f0e,
    0x7faa,
    0x7768,
    0x7EC5,
    0x2904,
    0x7fb7,
    0x2108,
    0x7C2B,
    0x318C,
    0x4631,
    0x5AD6,
    0x0
};

static const BgTemplate Unk_contest_competition_02253448[] = {
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0x6000,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0x6800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0x7000,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    },
    {
        .x = 0x0,
        .y = 0x0,
        .bufferSize = 0x800,
        .baseTile = 0x0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0x7800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0x0,
        .areaOver = 0x0,
        .mosaic = FALSE,
    }
};

static const TouchScreenRect Unk_contest_competition_022532D0[] = {
    { 0x8, 0x60, 0x8, 0x78 },
    { 0x8, 0x60, 0x88, 0xF8 },
    { 0x68, 0xC0, 0x8, 0x78 },
    { 0x68, 0xC0, 0x88, 0xF8 },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const int Unk_contest_competition_02253288[NELEMS(Unk_contest_competition_022532D0) - 1] = {
    0x0,
    0x1,
    0x2,
    0x3
};

__attribute__((aligned(4))) static const u8 Unk_contest_competition_02253230[NELEMS(Unk_contest_competition_022532D0) - 1] = {
    0x4,
    0x5,
    0x6,
    0x7
};

__attribute__((aligned(4))) static const u8 Unk_contest_competition_0225323C[2][2] = {
    { 0x0, 0x1 },
    { 0x2, 0x3 }
};

static const TouchScreenRect Unk_contest_competition_022532A8[] = {
    { 0x8, 0x80, 0x0, 0x50 },
    { 0x8, 0x80, 0x58, 0xA8 },
    { 0x8, 0x80, 0xB0, 0xFF },
    { 0x88, 0xC0, 0x0, 0xFF },
    { 0xFF, 0x0, 0x0, 0x0 }
};

static const int Unk_contest_competition_02253268[NELEMS(Unk_contest_competition_022532A8) - 1] = {
    0x0,
    0x1,
    0x2,
    0x3
};

__attribute__((aligned(4))) static const u8 Unk_contest_competition_02253234[NELEMS(Unk_contest_competition_022532A8) - 1] = {
    0x0,
    0x1,
    0x2,
    0x3
};

__attribute__((aligned(4))) static const u8 Unk_contest_competition_02253240[2][3] = {
    { 0x0, 0x1, 0x2 },
    { 0x3, 0x3, 0x3 }
};

static const ActingMoveMenuPage Unk_contest_competition_02253558[] = {
    {
        0x9,
        0x0,
        { 0x1, 0xFFFF, 0x0, 0xFFFF },
        { 0x2, 0x1, 0x3, 0x0 },
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        contest_competition_0223FBD4,
        NULL,
    },
    {
        0xB,
        0x1,
        { 0xFFFF, 0xFFFF, 0x4, 0xFFFF },
        { 0x2, 0x1, 0x3, 0x0 },
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        0xB,
        0x1,
        { 0x2, 0xFFFF, 0x4, 0xFFFF },
        { 0x2, 0x1, 0x3, 0x0 },
        Unk_contest_competition_022532D0,
        Unk_contest_competition_02253288,
        Unk_contest_competition_02253230,
        contest_competition_02240D04,
        contest_competition_02240E68,
        contest_competition_0223FCAC,
        contest_competition_0223FFF4,
    },
    {
        0xB,
        0x1,
        { 0x3, 0xFFFF, 0x4, 0xFFFF },
        { 0x2, 0x1, 0x3, 0x0 },
        Unk_contest_competition_022532A8,
        Unk_contest_competition_02253268,
        Unk_contest_competition_02253234,
        contest_competition_02240EA4,
        contest_competition_02240FC4,
        contest_competition_0223FF38,
        contest_competition_02240094,
    },
};

static const SpriteTemplate Unk_contest_competition_02253354 = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x64,
    0x0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 0x80F6, 0x80EF, 0x80F4, 0x80F4, 0xFFFFFFFF, 0xFFFFFFFF },
    0x1,
    0x0
};

__attribute__((aligned(4))) static const u16 Unk_contest_competition_02253298[][2] = {
    { 0x27, 0x30 },
    { 0xA7, 0x30 },
    { 0x27, 0x90 },
    { 0xA7, 0x90 }
};

__attribute__((aligned(4))) static const s16 Unk_contest_competition_022532E4[][3] = {
    { 0x0, 0xC0, 0x180 },
    { 0x0, 0xC0, 0x180 },
    { 0x0, 0xC0, 0x180 },
    { 0x0, 0xC0, 0x180 }
};

__attribute__((aligned(4))) static const ActingMoveMenuRect Unk_contest_competition_02253388[] = {
    { 0x0, 0xB, 0x1, 0xE },
    { 0x0, 0xB, 0x11, 0x1E },
    { 0xC, 0x17, 0x1, 0xE },
    { 0xC, 0x17, 0x11, 0x1E }
};

__attribute__((aligned(4))) static const s16 Unk_contest_competition_02253248[] = {
    0x214,
    0x211,
    0x20E,
    0x20B
};

__attribute__((aligned(4))) static const ActingMoveMenuRect Unk_contest_competition_02253408[] = {
    { 0x1, 0xB, 0x1, 0xE },
    { 0x1, 0xB, 0x11, 0x1E },
    { 0xD, 0x17, 0x1, 0xE },
    { 0xD, 0x17, 0x11, 0x1E }
};

__attribute__((aligned(4))) static const s16 Unk_contest_competition_022532FC[][3] = {
    { 0x0, 0xC0, 0x180 },
    { 0x0, 0xC0, 0x180 },
    { 0x0, 0xC0, 0x180 },
    { 0x0, 0xC0, 0x180 }
};

__attribute__((aligned(4))) static const ActingMoveMenuRect Unk_contest_competition_022533C8[] = {
    { 0x0, 0xF, 0x0, 0x9 },
    { 0x0, 0xF, 0xB, 0x14 },
    { 0x0, 0xF, 0x16, 0x1F },
    { 0x10, 0x17, 0x0, 0x1F }
};

static void *contest_competition_0223F7E4(void)
{
    ActingMoveMenu *v0 = Heap_Alloc(HEAP_ID_21, sizeof(ActingMoveMenu));
    MI_CpuClear8(v0, sizeof(ActingMoveMenu));
    v0->unk_2C8 = -1;

    return v0;
}

void contest_competition_0223F80C(BgConfig *param0)
{
    int v0;

    for (v0 = 0; v0 < NELEMS(Unk_contest_competition_02253448); v0++) {
        Bg_InitFromTemplate(param0, BG_LAYER_SUB_0 + v0, &Unk_contest_competition_02253448[v0], 0);
        Bg_FillTilemap(param0, 4 + v0, 0);
        Bg_SetOffset(param0, BG_LAYER_SUB_0 + v0, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_SUB_0 + v0, 3, 0);
    }
}

void contest_competition_0223F864(BgConfig *param0)
{
    int v0;

    for (v0 = 0; v0 < NELEMS(Unk_contest_competition_02253448); v0++) {
        Bg_ToggleLayer(BG_LAYER_SUB_0 + v0, 0);
        Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_0 + v0);
    }
}

void *contest_competition_0223F88C(Contest *param0, ActingCompetitionScene *param1, ActingMatchState *param2)
{
    ActingMoveMenu *v0;
    NARC *v1;

    v0 = contest_competition_0223F7E4();

    v0->unk_00 = param0;
    v0->unk_04 = param1;
    v0->unk_08 = param2;
    v0->unk_3C = FontOAMManager_New(12, HEAP_ID_21);

    v1 = NARC_ctor(NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, HEAP_ID_21);

    {
        NNSG2dScreenData *v2;
        void *v3;
        int v4;

        for (v4 = 0; v4 < 5; v4++) {
            v0->unk_20[v4] = Heap_Alloc(HEAP_ID_21, 0x800);
            v3 = Graphics_GetScrnDataFromOpenNARC(v1, Unk_contest_competition_02253250[v4], 1, &v2, HEAP_ID_21);
            MI_CpuCopy32(v2->rawData, v0->unk_20[v4], 0x800);
            Heap_Free(v3);
        }
    }

    {
        u16 *v5;
        PaletteData *v6;
        int v7;

        v6 = v0->unk_04->paletteData;

        for (v7 = 0; v7 < 2; v7++) {
            v0->unk_34[v7] = Heap_Alloc(HEAP_ID_21, 0x200);
            PaletteData_LoadBufferFromFileStart(v6, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, Unk_contest_competition_02253238[v7], HEAP_ID_21, PLTTBUF_SUB_BG, 0, 0);
            v5 = PaletteData_GetUnfadedBuffer(v6, 1);
            MI_CpuCopy16(v5, v0->unk_34[v7], 0x200);
        }
    }

    NARC_dtor(v1);

    return v0;
}

void contest_competition_0223F960(ActingMoveMenu *param0)
{
    int v0;

    contest_competition_022404B0(param0);
    FontOAMManager_Free(param0->unk_3C);
    contest_competition_02252B20(param0->unk_04->spriteManager, 33021, 33009, 33016, 33016);
    contest_competition_02252BCC(param0->unk_2FC);

    for (v0 = 0; v0 < 5; v0++) {
        Heap_Free(param0->unk_20[v0]);
    }

    for (v0 = 0; v0 < 2; v0++) {
        Heap_Free(param0->unk_34[v0]);
    }

    contest_competition_022409F4(param0);
    Heap_Free(param0);
}

void contest_competition_0223F9C4(ActingMoveMenu *param0, int param1, int param2, void *param3)
{
    const ActingMoveMenuPage *v0, *v1;
    int v2;
    BgConfig *v3;
    SpriteSystem *v4;
    SpriteManager *v5;

    param0->unk_0C = param3;

    v3 = param0->unk_04->bgConfig;
    v4 = param0->unk_04->spriteSystem;
    v5 = param0->unk_04->spriteManager;

    if (param0->unk_2C8 == -1) {
        param2 = 1;
        v1 = NULL;
    } else {
        v1 = &Unk_contest_competition_02253558[param0->unk_2C8];
    }

    v0 = &Unk_contest_competition_02253558[param1];

    {
        for (v2 = 0; v2 < 4; v2++) {
            Bg_SetPriority(BG_LAYER_SUB_0 + v2, v0->unk_0C_val2[v2]);
        }
    }

    if (1) {
        PaletteData_LoadBuffer(param0->unk_04->paletteData, param0->unk_34[v0->unk_02], PLTTBUF_SUB_BG, 0, PALETTE_SIZE_BYTES * 16);
    }

    for (v2 = 0; v2 < 4; v2++) {
        if ((v0->unk_04_val2[v2] != 0xffff) && ((param2 == 1) || (v0->unk_04_val2[v2] != v1->unk_04_val2[v2]))) {
            Bg_LoadTilemapBuffer(v3, 4 + v2, param0->unk_20[v0->unk_04_val2[v2]], 0x800);
            Bg_ScheduleTilemapTransfer(v3, 4 + v2);
        }
    }

    param0->unk_2C8 = param1;

    contest_competition_022404B0(param0);

    if (v0->unk_28 != NULL) {
        v0->unk_28(param0, param1, param2);
    }

    if ((v0->unk_00 != 0xffff) && ((param2 == 1) || (v0->unk_00 != v1->unk_00))) {
        param0->unk_2C0 = Graphics_GetCharData(NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, v0->unk_00, 1, &param0->unk_2C4, HEAP_ID_21);
        SysTask_ExecuteAfterVBlank(contest_competition_022411E4, param0, 10);
    }

    SysTask_ExecuteAfterVBlank(contest_competition_02241220, param0, 10);
}

int contest_competition_0223FAF8(ActingMoveMenu *param0)
{
    int v0, v1, v2, v3;
    const ActingMoveMenuPage *v4;
    int v5 = 0;

    GF_ASSERT(param0->unk_2C8 != -1);

    v4 = &Unk_contest_competition_02253558[param0->unk_2C8];

    if (v4->touchScreenRect == NULL) {
        return TOUCHSCREEN_INPUT_NONE;
    }

    GF_ASSERT(v4->unk_18 != NULL);

    v1 = TouchScreen_CheckRectanglePressed(v4->touchScreenRect);

    if (v1 == TOUCHSCREEN_INPUT_NONE) {
        v1 = contest_competition_02240C90(param0);
        v5++;
    }

    if (v1 == TOUCHSCREEN_INPUT_NONE) {
        v0 = 0xffffffff;
        v3 = 0xff;
    } else {
        v0 = v4->unk_18[v1];
        v3 = v4->unk_1C[v1];
    }

    if (v4->unk_2C != NULL) {
        v0 = v4->unk_2C(param0, v0, v3);

        if (v0 != 0xffffffff) {
            if (v4->unk_24 != NULL) {
                v4->unk_24(param0, v1);
            }

            MI_CpuClear8(&param0->unk_300, sizeof(ActingMoveMenuCursorMove));
            contest_competition_02252C9C(param0->unk_2FC);

            if (v5 > 0) {
                param0->unk_304 = 1;
            } else {
                param0->unk_304 = 0;
            }
        }
    }

    return v0;
}

BOOL contest_competition_0223FBC0(ActingMoveMenu *param0)
{
    if ((param0->unk_10 == NULL) && (param0->unk_14 == NULL)) {
        return 1;
    }

    return 0;
}

static void contest_competition_0223FBD4(ActingMoveMenu *param0, int param1, int param2)
{
    String *contestRankString, *contestTypeString;
    u32 contestRankMessageID = Contest_GetContestRankTitleMessageID(param0->unk_04->contestData->contestRank, param0->unk_04->contestData->competitionType, param0->unk_00->isLinkContest);
    u32 contestTypeMessageID = Contest_GetFullContestTypeMessageID(param0->unk_04->contestData->contestType, param0->unk_04->contestData->competitionType);
    contestRankString = MessageLoader_GetNewString(param0->unk_04->contestTextMessageLoader, contestRankMessageID);
    contestTypeString = MessageLoader_GetNewString(param0->unk_04->contestTextMessageLoader, contestTypeMessageID);

    contest_competition_02240138(param0, &param0->unk_40[0], contestRankString, FONT_SYSTEM, TEXT_COLOR(1, 2, 0), 0, 33008, 128, 8 * 0x10 - 1, 1, NULL);
    contest_competition_02240138(param0, &param0->unk_40[1], contestTypeString, FONT_SYSTEM, TEXT_COLOR(1, 2, 0), 0, 33008, 128, 8 * 0x14 - 1, 1, NULL);

    String_Free(contestRankString);
    String_Free(contestTypeString);
    PaletteData_LoadBufferFromFile(param0->unk_04->paletteData, NARC_INDEX_CONTEST__GRAPHIC__CONTEST_BG, 38, HEAP_ID_21, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES, PLTT_DEST(2), PLTT_DEST(param0->unk_04->contestData->contestType));
}

static void contest_competition_0223FCAC(ActingMoveMenu *param0, int param1, int param2)
{
    u16 moveList[LEARNED_MOVES_MAX];
    u16 moveContestEffects[LEARNED_MOVES_MAX];
    int i;
    String *v3;
    String *v4, *v5;
    u32 v6, v7;
    ActingMoveMenuMoves *v8 = &param0->unk_18C;
    param0->unk_2C9 = 0xff;

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        moveList[i] = Pokemon_GetValue(param0->unk_04->contestData->contestMons[param0->unk_04->contestData->playerContestantID], MON_DATA_MOVE1 + i, NULL);

        if (moveList[i] != MOVE_NONE) {
            moveContestEffects[i] = v8->moveContestEffect[i];
        } else {
            moveContestEffects[i] = 0;
        }

        contest_competition_02240138(param0, &param0->unk_40[0 + i], NULL, FONT_SUBSCREEN, TEXT_COLOR(1, 7, 8), 0, 33008, Unk_contest_competition_02253278[i][0], Unk_contest_competition_02253278[i][1], 0, &v8->unk_00[i]);
        contest_competition_02240138(param0, &param0->unk_40[4 + i], NULL, FONT_SYSTEM, TEXT_COLOR(1, 2, 0), 0, 33008, Unk_contest_competition_02253314[i][0][0], Unk_contest_competition_02253314[i][0][1], 0, &v8->unk_50[i]);
        contest_competition_02240138(param0, &param0->unk_40[8 + i], NULL, FONT_SYSTEM, TEXT_COLOR(1, 2, 0), 0, 33008, Unk_contest_competition_02253314[i][1][0], Unk_contest_competition_02253314[i][1][1], 0, &v8->unk_A0[i]);

        if (moveList[i] == MOVE_NONE) {
            FontOAM_SetDrawFlag(param0->unk_40[0 + i].unk_00, 0);
            FontOAM_SetDrawFlag(param0->unk_40[4 + i].unk_00, 0);
            FontOAM_SetDrawFlag(param0->unk_40[8 + i].unk_00, 0);
        }
    }

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        if (moveList[i] != MOVE_NONE) {
            int moveContestType;

            moveContestType = v8->moveContestType[i];
            contest_competition_02240424(param0, moveContestType, i);
        } else {
            contest_competition_02240424(param0, -1, i);
        }
    }

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        if (moveList[i] != MOVE_NONE && contest_competition_02243A98(param0->unk_08, param0->unk_04->contestData->playerContestantID, moveList[i]) == 0) {
            PaletteData_LoadBuffer(param0->unk_04->paletteData, &param0->unk_34[1][0x8 * 16], PLTTBUF_SUB_BG, PLTT_DEST(4 + i), PALETTE_SIZE_BYTES);

            GF_ASSERT(param0->unk_2C9 == 0xff);
            param0->unk_2C9 = i;
        }
    }

    contest_competition_022402E8(param0, moveList);

    int v10;
    int v11, v12;

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        if (moveList[i] == MOVE_NONE) {
            continue;
        }

        v10 = Contest_GetAppealPoints(moveContestEffects[i]);
        v11 = MATH_IAbs(v10) / 10;

        GF_ASSERT(v11 <= 6);

        for (v12 = 0; v12 < v11; v12++) {
            GF_ASSERT(param0->unk_12C[i][v12] == NULL);
            param0->unk_12C[i][v12] = contest_competition_0224136C(param0->unk_04->spriteSystem, param0->unk_04->spriteManager, Unk_contest_competition_02253334[i][0] + 8 * v12, Unk_contest_competition_02253334[i][1], v10);
        }
    }
}

static void contest_competition_0223FF38(ActingMoveMenu *param0, int param1, int param2)
{
    int v0;
    BgConfig *v1;
    String *message;
    ActingMoveMenuMoves *v3 = &param0->unk_18C;
    v1 = param0->unk_04->bgConfig;

    for (v0 = 0; v0 < (1 + 2); v0++) {
        contest_competition_02240138(param0, &param0->unk_40[0 + v0], NULL, FONT_SUBSCREEN, TEXT_COLOR(1, 9, 0xa), 0, 33008, Unk_contest_competition_0225325C[v0][0], Unk_contest_competition_0225325C[v0][1], 1, &v3->unk_F0[v0]);
    }

    message = MessageLoader_GetNewString(param0->unk_04->contestTextMessageLoader, Contest_Text_Exit);

    contest_competition_02240138(param0, &param0->unk_40[0 + v0], message, FONT_SUBSCREEN, TEXT_COLOR(1, 9, 0xa), 0, 33008, 128, 0x14 * 8 + 4, 1, NULL);
    String_Free(message);

    param0->unk_128 = contest_competition_022412C0(param0->unk_04->spriteSystem, param0->unk_04->spriteManager, param0->unk_04->contestData->bonusJudgeIndex);
}

static int contest_competition_0223FFF4(ActingMoveMenu *param0, int moveSlot, int param2)
{
    u32 v0;
    int moveID;
    const s16 *v2;
    const ActingMoveMenuRect *v3;

    v0 = moveSlot;

    switch (moveSlot) {
    case 0xffffffff:
    default:
        return 0xffffffff;
    case 0:
    case 1:
    case 2:
    case 3:
        moveID = Pokemon_GetValue(param0->unk_04->contestData->contestMons[param0->unk_04->contestData->playerContestantID], MON_DATA_MOVE1 + moveSlot, NULL);

        if (moveID == MOVE_NONE || param0->unk_2C9 == moveSlot) {
            return 0xffffffff;
        }

        v2 = Unk_contest_competition_022532E4[v0];
        v3 = &Unk_contest_competition_02253388[v0];
        break;
    }

    contest_competition_02240930(param0, param2);
    contest_competition_022404CC(contest_competition_02240658, param0);

    param0->unk_2CC.unk_04_val1.unk_0C = v2;
    param0->unk_2CC.unk_04_val1.unk_10 = v3;
    param0->unk_2CC.unk_04_val1.unk_18 = 2;
    param0->unk_2CC.unk_04_val1.unk_14 = moveSlot;

    return moveSlot;
}

static int contest_competition_02240094(ActingMoveMenu *param0, int param1, int param2)
{
    int v0;
    int v1;

    switch (param1) {
    case 0xffffffff:
    default:
        return param1;
    case 0:
        v0 = 0;
        break;
    case 1:
        v0 = 1;
        break;
    case 2:
        v0 = 2;
        break;
    case 3:
        v0 = 3;
        break;
    }

    v1 = (param1 == param0->unk_04->contestData->bonusJudgeIndex) ? 1 : 0;

    contest_competition_02240930(param0, param2);
    contest_competition_022404CC(contest_competition_0224051C, param0);

    param0->unk_2CC.unk_04_val1.unk_0C = Unk_contest_competition_022532FC[param1];
    param0->unk_2CC.unk_04_val1.unk_10 = &Unk_contest_competition_022533C8[param1];
    param0->unk_2CC.unk_04_val1.unk_18 = 3;
    param0->unk_2CC.unk_04_val1.unk_14 = param1;
    param0->unk_2CC.unk_04_val1.unk_19 = v0;

    if (v1 == 1) {
        param0->unk_2CC.unk_04_val1.unk_00[0] = param0->unk_128;
    }

    return param1;
}

static void contest_competition_02240138(ActingMoveMenu *param0, ActingMoveMenuLabel *param1, const String *string, enum Font font, u32 textColor, int param5, int param6, int x, int y, int param9, ActingMoveMenuWindow *param10)
{
    FontOAMTemplate v0;
    Window window;
    CharTransferAllocation v2;
    int v3;
    FontOAM *v4;
    BgConfig *v5;
    SpriteManager *v6;
    int v7, v8;

    GF_ASSERT(param1->unk_00 == NULL);

    v5 = param0->unk_04->bgConfig;
    v6 = param0->unk_04->spriteManager;

    if (param10 == NULL) {
        contest_competition_02240C60(string, font, &v7, &v8);
    } else {
        v7 = param10->unk_12;
        v8 = param10->unk_10;
    }

    if (param10 == NULL) {
        Window_Init(&window);
        Window_AddToTopLeftCorner(v5, &window, v8, 16 / 8, 0, 0);
        Text_AddPrinterWithParamsColorAndSpacing(&window, font, string, 0, 0, TEXT_SPEED_NO_TRANSFER, textColor, 0, 0, NULL);
    } else {
        window = param10->unk_00;
    }

    v3 = FontOAM_GetWindowSize(&window, NNS_G2D_VRAM_TYPE_2DSUB, HEAP_ID_21);
    CharTransfer_AllocRange(v3, 1, NNS_G2D_VRAM_TYPE_2DSUB, &v2);

    if (param9 == 1) {
        x -= v7 / 2;
    }

    y += (((192 + 80) << FX32_SHIFT) >> FX32_SHIFT) - 8;

    v0.fontOAMManager = param0->unk_3C;
    v0.window = &window;
    v0.spriteList = SpriteManager_GetSpriteList(v6);
    v0.paletteProxy = SpriteManager_FindPlttResourceProxy(v6, param6);
    v0.parentSprite = NULL;
    v0.charOffset = v2.offset;
    v0.x = x;
    v0.y = y;
    v0.resourcePriority = 0;
    v0.spritePriority = 100;
    v0.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    v0.heapID = HEAP_ID_21;

    v4 = FontOAM_New(&v0);

    FontOAM_SetExplicitPaletteOffsetAutoAdjust(v4, param5);
    FontOAM_SetXY(v4, x, y);

    if (param10 == NULL) {
        Window_Remove(&window);
    }

    param1->unk_00 = v4;
    param1->unk_04 = v2;
    param1->unk_10 = v7;
}

static void contest_competition_02240260(ActingMoveMenu *param0)
{
    int v0;

    for (v0 = 0; v0 < 12; v0++) {
        if (param0->unk_40[v0].unk_00 != NULL) {
            FontOAM_Free(param0->unk_40[v0].unk_00);
            CharTransfer_ClearRange(&param0->unk_40[v0].unk_04);
            param0->unk_40[v0].unk_00 = NULL;
        }
    }
}

static void contest_competition_0224028C(ActingMoveMenu *param0)
{
    if (param0->unk_128 != NULL) {
        contest_competition_02241314(param0->unk_128);
        param0->unk_128 = NULL;
    }
}

static void contest_competition_022402A8(ActingMoveMenu *param0)
{
    int v0, v1;

    for (v1 = 0; v1 < 4; v1++) {
        for (v0 = 0; v0 < 6; v0++) {
            if (param0->unk_12C[v1][v0] != NULL) {
                contest_competition_022413AC(param0->unk_12C[v1][v0]);
                param0->unk_12C[v1][v0] = NULL;
            }
        }
    }
}

static void contest_competition_022402E8(ActingMoveMenu *param0, u16 param1[])
{
    int i;
    SpriteSystem *v1;
    SpriteManager *v2;
    SpriteTemplate v3;
    int v4;

    v1 = param0->unk_04->spriteSystem;
    v2 = param0->unk_04->spriteManager;
    v3 = Unk_contest_competition_02253354;

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        GF_ASSERT(param0->unk_118[i] == NULL);

        if (param1[i] != 0) {
            v4 = param0->unk_18C.moveContestType[i];

            v3.resources[0] = 33014 + i;
            v3.x = Unk_contest_competition_02253298[i][0];
            v3.y = Unk_contest_competition_02253298[i][1];

            param0->unk_118[i] = contest_competition_0224F154(v1, v2, v4, &v3);
            ManagedSprite_SetPositionXYWithSubscreenOffset(param0->unk_118[i], v3.x, v3.y, (192 + 80) << FX32_SHIFT);
        }
    }
}

static void contest_competition_02240388(ActingMoveMenu *param0)
{
    int v0;
    SpriteSystem *v1 = param0->unk_04->spriteSystem;
    SpriteManager *v2 = param0->unk_04->spriteManager;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->unk_118[v0] != NULL) {
            contest_competition_0224F184(param0->unk_118[v0]);
            param0->unk_118[v0] = NULL;
        }
    }
}

static void contest_competition_022403B0(ActingMoveMenu *param0, const s16 *param1, const ActingMoveMenuRect *param2, int param3, int param4)
{
    int v0, v1;
    BgConfig *v2;
    u16 *v3, *v4;
    u16 *v5, *v6;
    int v7;

    v2 = param0->unk_04->bgConfig;
    v3 = Bg_GetTilemapBuffer(v2, 4);
    v5 = param0->unk_20[param3];
    v7 = param1[param4];

    for (v1 = param2->unk_00; v1 <= param2->unk_04; v1++) {
        v4 = &v3[v1 * 32];
        v6 = &v5[v1 * 32];

        for (v0 = param2->unk_08; v0 <= param2->unk_0C; v0++) {
            v4[v0] = v6[v0] + v7;
        }
    }

    Bg_ScheduleTilemapTransfer(v2, 4);
}

static void contest_competition_02240424(ActingMoveMenu *param0, int moveContestType, int moveSlot)
{
    const u16 *const v0[] = {
        &Unk_contest_competition_022534B8[16 * 3],
        &Unk_contest_competition_022534B8[16 * 4],
        &Unk_contest_competition_022534B8[16 * 1],
        &Unk_contest_competition_022534B8[16 * 2],
        &Unk_contest_competition_022534B8[16 * 0],
    };

    if (moveContestType != -1) {
        PaletteData_LoadBuffer(param0->unk_04->paletteData, v0[moveContestType], PLTTBUF_SUB_BG, PLTT_DEST(4 + moveSlot), PALETTE_SIZE_BYTES);
    } else {
        contest_competition_022403B0(param0, &Unk_contest_competition_02253248[moveSlot], &Unk_contest_competition_02253408[moveSlot], 2, 0);
        PaletteData_LoadBuffer(param0->unk_04->paletteData, &param0->unk_34[1][0x8 * 16], PLTTBUF_SUB_BG, PLTT_DEST(4 + moveSlot), PALETTE_SIZE_BYTES);
    }
}

static void contest_competition_022404A8(ActingMoveMenu *param0)
{
    contest_competition_022404B0(param0);
}

static void contest_competition_022404B0(ActingMoveMenu *param0)
{
    contest_competition_0224028C(param0);
    contest_competition_022402A8(param0);
    contest_competition_02240388(param0);
    contest_competition_02240260(param0);
}

static void contest_competition_022404CC(SysTaskFunc param0, ActingMoveMenu *param1)
{
    GF_ASSERT(param1->unk_10 == NULL);

    MI_CpuClear8(&param1->unk_2CC, sizeof(ActingMoveMenuInput));
    param1->unk_10 = SysTask_Start(param0, param1, 1300);
}

static void contest_competition_022404FC(ActingMoveMenu *param0)
{
    if (param0->unk_10 != NULL) {
        SysTask_Done(param0->unk_10);
        param0->unk_10 = NULL;
        MI_CpuClear8(&param0->unk_2CC, sizeof(ActingMoveMenuInput));
    }
}

static void contest_competition_0224051C(SysTask *param0, void *param1)
{
    ActingMoveMenu *v0 = param1;
    BgConfig *v1;
    int v2, v3;
    int v4;

    v1 = v0->unk_04->bgConfig;

    switch (v0->unk_2CC.unk_00) {
    case 0:
        contest_competition_022403B0(v0, v0->unk_2CC.unk_04_val1.unk_0C, v0->unk_2CC.unk_04_val1.unk_10, v0->unk_2CC.unk_04_val1.unk_18, 2);
        FontOAM_GetXY(v0->unk_40[v0->unk_2CC.unk_04_val1.unk_19].unk_00, &v2, &v3);
        FontOAM_SetXY(v0->unk_40[v0->unk_2CC.unk_04_val1.unk_19].unk_00, v2, v3 + -2);

        for (v4 = 0; v4 < 3; v4++) {
            if (v0->unk_2CC.unk_04_val1.unk_00[v4] != NULL) {
                Sprite_OffsetPositionXY(v0->unk_2CC.unk_04_val1.unk_00[v4]->sprite, 0, -2);
            }
        }

        v0->unk_2CC.unk_00++;
        break;
    case 1:
        v0->unk_2CC.unk_02++;

        if (v0->unk_2CC.unk_02 <= 0) {
            break;
        }

        v0->unk_2CC.unk_02 = 0;
        v0->unk_2CC.unk_00++;

    case 2:
        contest_competition_022403B0(v0, v0->unk_2CC.unk_04_val1.unk_0C, v0->unk_2CC.unk_04_val1.unk_10, v0->unk_2CC.unk_04_val1.unk_18, 1);
        FontOAM_GetXY(v0->unk_40[v0->unk_2CC.unk_04_val1.unk_19].unk_00, &v2, &v3);
        FontOAM_SetXY(v0->unk_40[v0->unk_2CC.unk_04_val1.unk_19].unk_00, v2, v3 + 1);

        for (v4 = 0; v4 < 3; v4++) {
            if (v0->unk_2CC.unk_04_val1.unk_00[v4] != NULL) {
                Sprite_OffsetPositionXY(v0->unk_2CC.unk_04_val1.unk_00[v4]->sprite, 0, 1);
            }
        }

        v0->unk_2CC.unk_00++;
        break;
    default:
        v0->unk_2CC.unk_02++;

        if (v0->unk_2CC.unk_02 > 0) {
            contest_competition_022404A8(v0);
            contest_competition_022404FC(v0);
            return;
        }
        break;
    }
}

static void contest_competition_02240658(SysTask *param0, void *param1)
{
    ActingMoveMenu *v0 = param1;
    BgConfig *v1;
    int v2, v3;
    int v4, v5, v6;
    int v7, v8;
    u16 learnedMoves[LEARNED_MOVES_MAX];
    int v10, v11;

    v1 = v0->unk_04->bgConfig;

    for (v10 = 0; v10 < LEARNED_MOVES_MAX; v10++) {
        learnedMoves[v10] = Pokemon_GetValue(v0->unk_04->contestData->contestMons[v0->unk_04->contestData->playerContestantID], MON_DATA_MOVE1 + v10, NULL);
    }

    switch (v0->unk_2CC.unk_04_val1.unk_14) {
    case 0:
        v4 = 0;
        v5 = 4;
        v6 = 8;
        v7 = 0;
        v8 = learnedMoves[0];
        v11 = 0;
        break;
    case 1:
        v4 = 1;
        v5 = 5;
        v6 = 9;
        v7 = 1;
        v8 = learnedMoves[1];
        v11 = 1;
        break;
    case 2:
        v4 = 2;
        v5 = 6;
        v6 = 10;
        v7 = 2;
        v8 = learnedMoves[2];
        v11 = 2;
        break;
    case 3:
        v4 = 3;
        v5 = 7;
        v6 = 11;
        v7 = 3;
        v8 = learnedMoves[3];
        v11 = 3;
        break;
    default:
        v4 = 0;
        v5 = 0;
        v6 = 0;
        v7 = 0;
        v8 = 0;
        break;
    }

    switch (v0->unk_2CC.unk_00) {
    case 0:
        contest_competition_022403B0(v0, v0->unk_2CC.unk_04_val1.unk_0C, v0->unk_2CC.unk_04_val1.unk_10, v0->unk_2CC.unk_04_val1.unk_18, 2);

        if (1) {
            FontOAM_GetXY(v0->unk_40[v4].unk_00, &v2, &v3);
            FontOAM_SetXY(v0->unk_40[v4].unk_00, v2, v3 + -2);
            FontOAM_GetXY(v0->unk_40[v5].unk_00, &v2, &v3);
            FontOAM_SetXY(v0->unk_40[v5].unk_00, v2, v3 + -2);
            FontOAM_GetXY(v0->unk_40[v6].unk_00, &v2, &v3);
            FontOAM_SetXY(v0->unk_40[v6].unk_00, v2, v3 + -2);

            if (v8 != 0) {
                Sprite_OffsetPositionXY(v0->unk_118[v7]->sprite, 0, -2);

                for (v10 = 0; v10 < 6; v10++) {
                    if (v0->unk_12C[v11][v10] != NULL) {
                        Sprite_OffsetPositionXY(v0->unk_12C[v11][v10]->sprite, 0, -2);
                    }
                }
            }
        } else {
            (void)0;
        }

        v0->unk_2CC.unk_00++;
        break;
    case 1:
        v0->unk_2CC.unk_02++;

        if (v0->unk_2CC.unk_02 <= 0) {
            break;
        }

        v0->unk_2CC.unk_02 = 0;
        v0->unk_2CC.unk_00++;
    case 2:
        contest_competition_022403B0(v0, v0->unk_2CC.unk_04_val1.unk_0C, v0->unk_2CC.unk_04_val1.unk_10, v0->unk_2CC.unk_04_val1.unk_18, 1);

        if (1) {
            FontOAM_GetXY(v0->unk_40[v4].unk_00, &v2, &v3);
            FontOAM_SetXY(v0->unk_40[v4].unk_00, v2, v3 + 1);
            FontOAM_GetXY(v0->unk_40[v5].unk_00, &v2, &v3);
            FontOAM_SetXY(v0->unk_40[v5].unk_00, v2, v3 + 1);
            FontOAM_GetXY(v0->unk_40[v6].unk_00, &v2, &v3);
            FontOAM_SetXY(v0->unk_40[v6].unk_00, v2, v3 + 1);

            if (v8 != 0) {
                Sprite_OffsetPositionXY(v0->unk_118[v7]->sprite, 0, 1);

                for (v10 = 0; v10 < 6; v10++) {
                    if (v0->unk_12C[v11][v10] != NULL) {
                        Sprite_OffsetPositionXY(v0->unk_12C[v11][v10]->sprite, 0, 1);
                    }
                }
            }
        } else {
            (void)0;
        }

        v0->unk_2CC.unk_00++;
        break;
    default:
        v0->unk_2CC.unk_02++;

        if (v0->unk_2CC.unk_02 > 0) {
            contest_competition_022404A8(v0);
            contest_competition_022404FC(v0);
            return;
        }
        break;
    }
}

static void contest_competition_022408E0(SysTaskFunc param0, ActingMoveMenu *param1)
{
    GF_ASSERT(param1->unk_14 == NULL);

    MI_CpuClear8(&param1->unk_2EC, sizeof(ActingMoveMenuCursorAnim));
    param1->unk_14 = SysTask_Start(param0, param1, 1320);
}

static void contest_competition_02240910(ActingMoveMenu *param0)
{
    if (param0->unk_14 != NULL) {
        SysTask_Done(param0->unk_14);
        param0->unk_14 = NULL;
        MI_CpuClear8(&param0->unk_2EC, sizeof(ActingMoveMenuCursorAnim));
    }
}

static void contest_competition_02240930(ActingMoveMenu *param0, int param1)
{
    if (param1 == 0xff) {
        return;
    }

    contest_competition_022408E0(contest_competition_02240950, param0);
    param0->unk_2EC.unk_09 = param1;
}

static void contest_competition_02240950(SysTask *param0, void *param1)
{
    ActingMoveMenu *v0 = param1;
    ActingMoveMenuCursorAnim *v1;
    PaletteData *v2;
    int v3, v4;

    v1 = &v0->unk_2EC;
    v2 = v0->unk_04->paletteData;
    v4 = 0;

    switch (v1->unk_08) {
    case 0:
        v1->unk_04 = (10 << 8);
        v1->unk_06 = -((10 << 8) / 2);
        v1->unk_04 -= v1->unk_06;
        v1->unk_08++;
    case 1:
        v1->unk_04 += v1->unk_06;

        if ((v1->unk_06 >= 0) && (v1->unk_04 >= (16 << 8))) {
            v1->unk_04 = 16 << 8;
            v4 = 1;
        } else if ((v1->unk_06 < 0) && (v1->unk_04 <= 0)) {
            v1->unk_04 = 0;
            v4 = 1;
        }

        PaletteData_Blend(v2, PLTTBUF_SUB_BG, v1->unk_09 * PALETTE_SIZE, 16, v1->unk_04 >> 8, 0x7fff);

        if (v4 == 1) {
            contest_competition_02240910(v0);
            return;
        }
        break;
    }
}

static void contest_competition_022409F4(ActingMoveMenu *param0)
{
    int v0, v1;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->unk_18C.unk_00[v0].unk_00.pixels != NULL) {
            Window_Remove(&param0->unk_18C.unk_00[v0].unk_00);
        }

        if (param0->unk_18C.unk_50[v0].unk_00.pixels != NULL) {
            Window_Remove(&param0->unk_18C.unk_50[v0].unk_00);
        }

        if (param0->unk_18C.unk_A0[v0].unk_00.pixels != NULL) {
            Window_Remove(&param0->unk_18C.unk_A0[v0].unk_00);
        }
    }

    for (v0 = 0; v0 < (1 + 2); v0++) {
        if (param0->unk_18C.unk_F0[v0].unk_00.pixels != NULL) {
            Window_Remove(&param0->unk_18C.unk_F0[v0].unk_00);
        }
    }
}

void contest_competition_02240A80(ActingMoveMenu *param0, u16 moves[])
{
    ActingMoveMenuMoves *v0;
    int v1;
    String *v2;
    String *lineOneEffectMessage, *lineTwoEffectMessage, *judgeName;
    u32 lineOneEffectMessageID, lineTwoEffectMessageID;

    v0 = &param0->unk_18C;

    for (v1 = 0; v1 < LEARNED_MOVES_MAX; v1++) {
        if (moves[v1] != 0) {
            v0->moveContestEffect[v1] = MoveTable_LoadParam(moves[v1], MOVEATTRIBUTE_CONTEST_EFFECT);
            v0->moveContestType[v1] = MoveTable_LoadParam(moves[v1], MOVEATTRIBUTE_CONTEST_TYPE);
        } else {
            v0->moveContestEffect[v1] = 0;
            v0->moveContestType[v1] = 0;
        }

        v2 = MessageUtil_MoveName(moves[v1], HEAP_ID_21);

        contest_competition_02240BF4(param0, v2, FONT_SUBSCREEN, &v0->unk_00[v1], TEXT_COLOR(1, 7, 8));
        String_Free(v2);
        Contest_LoadTwoLineContestEffectMessages(v0->moveContestEffect[v1], &lineOneEffectMessageID, &lineTwoEffectMessageID);

        lineOneEffectMessage = MessageLoader_GetNewString(param0->unk_04->contestEffectMessages, lineOneEffectMessageID);
        lineTwoEffectMessage = MessageLoader_GetNewString(param0->unk_04->contestEffectMessages, lineTwoEffectMessageID);

        contest_competition_02240BF4(param0, lineOneEffectMessage, FONT_SYSTEM, &v0->unk_50[v1], TEXT_COLOR(1, 2, 0));
        contest_competition_02240BF4(param0, lineTwoEffectMessage, FONT_SYSTEM, &v0->unk_A0[v1], TEXT_COLOR(1, 2, 0));

        String_Free(lineOneEffectMessage);
        String_Free(lineTwoEffectMessage);
    }

    for (v1 = 0; v1 < (1 + 2); v1++) {
        judgeName = Contest_GetJudgeName(param0->unk_04->contestData->judges[v1].judgeNameMessageID, HEAP_ID_21);
        contest_competition_02240BF4(param0, judgeName, FONT_SUBSCREEN, &v0->unk_F0[v1], TEXT_COLOR(1, 9, 0xa));
        String_Free(judgeName);
    }

    {
        contest_competition_02252AB0(param0->unk_04->spriteSystem, param0->unk_04->spriteManager, param0->unk_04->paletteData, 33021, 33009, 33016, 33016);
        param0->unk_2FC = contest_competition_02252B48(param0->unk_04->spriteSystem, param0->unk_04->spriteManager, HEAP_ID_21, 33021, 33009, 33016, 33016, 5, 0);
    }
}

static void contest_competition_02240BF4(ActingMoveMenu *param0, const String *param1, int param2, ActingMoveMenuWindow *param3, u32 param4)
{
    int v0, v1;

    contest_competition_02240C60(param1, param2, &v0, &v1);

    param3->unk_12 = v0;
    param3->unk_10 = v1;

    if (param3->unk_00.pixels != NULL) {
        Window_Remove(&param3->unk_00);
    }

    Window_Init(&param3->unk_00);
    Window_AddToTopLeftCorner(param0->unk_04->bgConfig, &param3->unk_00, v1, 16 / 8, 0, 0);
    Text_AddPrinterWithParamsColorAndSpacing(&param3->unk_00, param2, param1, 0, 0, TEXT_SPEED_NO_TRANSFER, param4, 0, 0, NULL);
}

static void contest_competition_02240C60(const String *param0, int param1, int *param2, int *param3)
{
    int v0 = Font_CalcStringWidth(param1, param0, 0);
    int v1 = v0 / 8;

    if (FX_ModS32(v0, 8) != 0) {
        v1++;
    }

    *param2 = v0;
    *param3 = v1;
}

static int contest_competition_02240C90(ActingMoveMenu *param0)
{
    ActingMoveMenuCursorMove *v0;
    const ActingMoveMenuPage *v1;

    v0 = &param0->unk_300;
    v1 = &Unk_contest_competition_02253558[param0->unk_2C8];

    if (v1->unk_20 == NULL) {
        return 0xffffffff;
    }

    if (v0->unk_00 == 0) {
        if ((param0->unk_304 == 1) || (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_X | PAD_BUTTON_Y | PAD_KEY_RIGHT | PAD_KEY_LEFT | PAD_KEY_UP | PAD_KEY_DOWN))) {
            if (param0->unk_304 == 0) {
                Sound_PlayEffect(SE_CONFIRM_sseq_3);
            }

            v0->unk_00 = 1;
            param0->unk_304 = 0;
            v1->unk_20(param0, 1);
        }

        return 0xffffffff;
    }

    return v1->unk_20(param0, 0);
}

static int contest_competition_02240D04(ActingMoveMenu *param0, int param1)
{
    ActingMoveMenuCursorMove *v0;
    u32 v1;
    const ActingMoveMenuPage *v2;
    int v3, v4;
    u8 v5[2][2];
    ActingMoveMenuCursorOffset *v6;
    u16 v7[LEARNED_MOVES_MAX];

    v6 = &param0->unk_2F6;
    v0 = &param0->unk_300;
    v2 = &Unk_contest_competition_02253558[param0->unk_2C8];

    for (v4 = 0; v4 < LEARNED_MOVES_MAX; v4++) {
        v7[v4] = Pokemon_GetValue(param0->unk_04->contestData->contestMons[param0->unk_04->contestData->playerContestantID], MON_DATA_MOVE1 + v4, NULL);
    }

    if (param1 == 1) {
        v0->unk_02 = v6->unk_00;
        v0->unk_01 = v6->unk_01;
        v3 = Unk_contest_competition_0225323C[v0->unk_01][v0->unk_02];

        if (v7[v3 - 0] == 0) {
            v6->unk_00 = 0;
            v6->unk_01 = 0;
            v0->unk_02 = 0;
            v0->unk_01 = 0;
            v3 = Unk_contest_competition_0225323C[v0->unk_01][v0->unk_02];
        }

        contest_competition_02252C78(param0->unk_2FC, v2->touchScreenRect[v3].rect.left + 8, v2->touchScreenRect[v3].rect.right - 8, v2->touchScreenRect[v3].rect.top + 8, v2->touchScreenRect[v3].rect.bottom - 8, (192 + 80) << FX32_SHIFT);
        return 0xffffffff;
    }

    MI_CpuCopy8(Unk_contest_competition_0225323C, v5, 2 * 2);

    v1 = contest_competition_02241004(v0, 2, 2, v5[0]);

    switch (v1) {
    case PAD_KEY_UP:
    case PAD_KEY_DOWN:
    case PAD_KEY_LEFT:
    case PAD_KEY_RIGHT:
        v3 = Unk_contest_competition_0225323C[v0->unk_01][v0->unk_02];
        contest_competition_02252C78(param0->unk_2FC, v2->touchScreenRect[v3].rect.left + 8, v2->touchScreenRect[v3].rect.right - 8, v2->touchScreenRect[v3].rect.top + 8, v2->touchScreenRect[v3].rect.bottom - 8, (192 + 80) << FX32_SHIFT);
        break;
    case PAD_BUTTON_A:
        return Unk_contest_competition_0225323C[v0->unk_01][v0->unk_02];
    case PAD_BUTTON_B:
        break;
    }

    return 0xffffffff;
}

static void contest_competition_02240E68(ActingMoveMenu *param0, int param1)
{
    ActingMoveMenuCursorOffset *v0;
    int v1, v2;

    v0 = &param0->unk_2F6;

    for (v2 = 0; v2 < 2; v2++) {
        for (v1 = 0; v1 < 2; v1++) {
            if (param1 == Unk_contest_competition_0225323C[v2][v1]) {
                v0->unk_00 = v1;
                v0->unk_01 = v2;
                return;
            }
        }
    }
}

static int contest_competition_02240EA4(ActingMoveMenu *param0, int param1)
{
    ActingMoveMenuCursorMove *v0;
    u32 v1;
    const ActingMoveMenuPage *v2;
    int v3, v4;
    u8 v5[2][3];
    ActingMoveMenuCursorOffset *v6 = &param0->unk_2F6;
    v0 = &param0->unk_300;
    v2 = &Unk_contest_competition_02253558[param0->unk_2C8];

    if (param1 == 1) {
        v0->unk_02 = v6->unk_02;
        v0->unk_01 = v6->unk_03;
        v3 = Unk_contest_competition_02253240[v0->unk_01][v0->unk_02];
        contest_competition_02252C78(param0->unk_2FC, v2->touchScreenRect[v3].rect.left + 8, v2->touchScreenRect[v3].rect.right - 8, v2->touchScreenRect[v3].rect.top + 8, v2->touchScreenRect[v3].rect.bottom - 8, (192 + 80) << FX32_SHIFT);
        return 0xffffffff;
    }

    MI_CpuCopy8(Unk_contest_competition_02253240, v5, 2 * 3);
    v1 = contest_competition_02241004(v0, 3, 2, v5[0]);

    switch (v1) {
    case PAD_KEY_UP:
    case PAD_KEY_DOWN:
    case PAD_KEY_LEFT:
    case PAD_KEY_RIGHT:
        v3 = Unk_contest_competition_02253240[v0->unk_01][v0->unk_02];
        contest_competition_02252C78(param0->unk_2FC, v2->touchScreenRect[v3].rect.left + 8, v2->touchScreenRect[v3].rect.right - 8, v2->touchScreenRect[v3].rect.top + 8, v2->touchScreenRect[v3].rect.bottom - 8, (192 + 80) << FX32_SHIFT);
        break;
    case PAD_BUTTON_A:
        return Unk_contest_competition_02253240[v0->unk_01][v0->unk_02];
    case PAD_BUTTON_B:
        return 3;
    }

    return 0xffffffff;
}

static void contest_competition_02240FC4(ActingMoveMenu *param0, int param1)
{
    ActingMoveMenuCursorOffset *v0;
    int v1, v2, v3;

    if (param1 == 3) {
        return;
    }

    v0 = &param0->unk_2F6;

    for (v3 = 0; v3 < 2; v3++) {
        for (v2 = 0; v2 < 3; v2++) {
            if (param1 == Unk_contest_competition_02253240[v3][v2]) {
                v0->unk_02 = v2;
                v0->unk_03 = v3;
                return;
            }
        }
    }
}

static u32 contest_competition_02241004(ActingMoveMenuCursorMove *param0, int param1, int param2, const u8 *param3)
{
    int v0, v1;
    u32 v2;

    v1 = param0->unk_02;
    v0 = param0->unk_01;

    if (gSystem.pressedKeys & PAD_KEY_UP) {
        param0->unk_01--;

        if (param0->unk_01 < 0) {
            param0->unk_01 = 0;
        }

        if (param3 != NULL) {
            while (param3[param1 * param0->unk_01 + param0->unk_02] == 0xff) {
                param0->unk_01--;

                if (param0->unk_01 < 0) {
                    param0->unk_01 = v0;
                    break;
                }
            }
        }

        v2 = PAD_KEY_UP;
    } else if (gSystem.pressedKeys & PAD_KEY_DOWN) {
        param0->unk_01++;

        if (param0->unk_01 >= param2) {
            param0->unk_01 = param2 - 1;
        }

        if (param3 != NULL) {
            while (param3[param1 * param0->unk_01 + param0->unk_02] == 0xff) {
                param0->unk_01++;

                if (param0->unk_01 >= param2) {
                    param0->unk_01 = v0;
                    break;
                }
            }
        }

        v2 = PAD_KEY_DOWN;
    } else if (gSystem.pressedKeys & PAD_KEY_LEFT) {
        param0->unk_02--;

        if (param0->unk_02 < 0) {
            param0->unk_02 = 0;
        }

        if (param3 != NULL) {
            while (param3[param1 * param0->unk_01 + param0->unk_02] == 0xff) {
                param0->unk_02--;

                if (param0->unk_02 < 0) {
                    param0->unk_02 = v1;
                    break;
                }
            }
        }

        v2 = PAD_KEY_LEFT;
    } else if (gSystem.pressedKeys & PAD_KEY_RIGHT) {
        param0->unk_02++;

        if (param0->unk_02 >= param1) {
            param0->unk_02 = param1 - 1;
        }

        if (param3 != NULL) {
            while (param3[param1 * param0->unk_01 + param0->unk_02] == 0xff) {
                param0->unk_02++;

                if (param0->unk_02 >= param1) {
                    param0->unk_02 = v1;
                    break;
                }
            }
        }

        v2 = PAD_KEY_RIGHT;
    } else if (gSystem.pressedKeys & PAD_BUTTON_A) {
        v2 = PAD_BUTTON_A;
    } else if (gSystem.pressedKeys & PAD_BUTTON_B) {
        v2 = PAD_BUTTON_B;
    } else {
        return 0;
    }

    if (param3 != NULL) {
        int v3, v4;

        v3 = param3[param1 * v0 + v1];
        v4 = param3[param1 * param0->unk_01 + param0->unk_02];

        if (v3 == v4) {
            param0->unk_02 = v1;
            param0->unk_01 = v0;
        }
    }

    if ((param0->unk_02 != v1) || (param0->unk_01 != v0)) {
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
    } else {
        if (v2 & PAD_KEY) {
            return 0;
        }
    }

    return v2;
}

static void contest_competition_022411E4(SysTask *param0, void *param1)
{
    ActingMoveMenu *v0 = param1;

    Bg_LoadTiles(v0->unk_04->bgConfig, 4, v0->unk_2C4->pRawData, 0x6000, 0);
    Heap_Free(v0->unk_2C0);

    v0->unk_2C0 = NULL;

    SysTask_Done(param0);
}

static void contest_competition_02241220(SysTask *param0, void *param1)
{
    ActingMoveMenu *v0 = param1;
    const ActingMoveMenuPage *v1;
    int v2;

    v1 = &Unk_contest_competition_02253558[v0->unk_2C8];

    for (v2 = 0; v2 < 4; v2++) {
        if (v1->unk_04_val2[v2] == 0xffff) {
            Bg_ToggleLayer(BG_LAYER_SUB_0 + v2, 0);
        } else {
            Bg_ToggleLayer(BG_LAYER_SUB_0 + v2, 1);
        }
    }

    SysTask_Done(param0);
}
