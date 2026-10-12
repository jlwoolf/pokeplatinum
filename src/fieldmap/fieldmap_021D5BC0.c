#include "fieldmap/fieldmap_021D5BC0.h"

#include <nitro.h>
#include <string.h>

#include "field/field_system.h"
#include "fieldmap/fieldmap_021EA714.h"
#include "union_room_chat/union_room_chat.h"

#include "field_comm_manager.h"
#include "game_overlay.h"

FS_EXTERN_OVERLAY(union_room_chat);

typedef struct BottomScreenHandlers {
    // clang-format off
    void (* initFn)(FieldSystem *);
    BOOL (* isRunningDummyFn)(FieldSystem *);
    void (* endFn)(FieldSystem *);
    BOOL (* isDoneFn)(FieldSystem *);
    // clang-format on
} BottomScreenHandlers;

static void FieldMap_021D5C4C(FieldSystem *fieldSystem);
static void FieldMap_021D5C54(FieldSystem *fieldSystem);
static void FieldMap_021D5C5C(FieldSystem *fieldSystem);
static void FieldMap_021D5C78(FieldSystem *fieldSystem);
static void FieldMap_021D5C80(FieldSystem *fieldSystem);
static void FieldMap_021D5C88(FieldSystem *fieldSystem);
static BOOL FieldMap_021D5CA0(FieldSystem *fieldSystem);
static BOOL FieldMap_021D5CAC(FieldSystem *fieldSystem);
static BOOL FieldMap_021D5CA8(FieldSystem *fieldSystem);

static const BottomScreenHandlers sBottomScreenHandlers[] = {
    { FieldMap_021D5C4C, NULL, FieldMap_021D5C78, FieldMap_021D5CA0 },
    { FieldMap_021D5C54, NULL, FieldMap_021D5C80, FieldMap_021D5CAC },
    { FieldMap_021D5C5C, NULL, FieldMap_021D5C88, FieldMap_021D5CA8 },
    { FieldMap_021EA830, NULL, FieldMap_021EA848, FieldMap_021EA854 }
};

static int FieldSystem_GetBottomScreenIndex(FieldSystem *fieldSystem)
{
    int fieldBottomScreen = fieldSystem->bottomScreen;

    GF_ASSERT(fieldBottomScreen != 0);
    GF_ASSERT(fieldBottomScreen < 5);

    return fieldBottomScreen - 1;
}

void FieldSystem_InitBottomScreen(FieldSystem *fieldSystem)
{
    sBottomScreenHandlers[FieldSystem_GetBottomScreenIndex(fieldSystem)].initFn(fieldSystem);
}

BOOL FieldSystem_IsBottomScreenRunningDummy(FieldSystem *fieldSystem)
{
    // clang-format off
    BOOL (* isRunningDummyFn)(FieldSystem *);
    // clang-format on

    isRunningDummyFn = sBottomScreenHandlers[FieldSystem_GetBottomScreenIndex(fieldSystem)].isRunningDummyFn;

    if (isRunningDummyFn == NULL) {
        return 1;
    }

    return isRunningDummyFn(fieldSystem);
}

void FieldSystem_EndBottomScreen(FieldSystem *fieldSystem)
{
    sBottomScreenHandlers[FieldSystem_GetBottomScreenIndex(fieldSystem)].endFn(fieldSystem);
}

BOOL FieldSystem_IsBottomScreenDone(FieldSystem *fieldSystem)
{
    return sBottomScreenHandlers[FieldSystem_GetBottomScreenIndex(fieldSystem)].isDoneFn(fieldSystem);
}

static void FieldMap_021D5C4C(FieldSystem *fieldSystem)
{
    FieldMap_021EA728(fieldSystem);
}

static void FieldMap_021D5C54(FieldSystem *fieldSystem)
{
    FieldCommManager_UnpauseUndergroundResources();
}

static void FieldMap_021D5C5C(FieldSystem *fieldSystem)
{
    Overlay_LoadByID(FS_OVERLAY_ID(union_room_chat), 2);
    fieldSystem->unk_84 = UnionRoomChat_New(fieldSystem);
}

static void FieldMap_021D5C78(FieldSystem *fieldSystem)
{
    FieldMap_021EA790(fieldSystem);
}

static void FieldMap_021D5C80(FieldSystem *fieldSystem)
{
    FieldCommManager_PauseUndergroundResources();
}

static void FieldMap_021D5C88(FieldSystem *fieldSystem)
{
    UnionRoomChat_Free(fieldSystem->unk_84);
    Overlay_UnloadByID(FS_OVERLAY_ID(union_room_chat));
}

static BOOL FieldMap_021D5CA0(FieldSystem *fieldSystem)
{
    return FieldMap_021EA7CC(fieldSystem);
}

static BOOL FieldMap_021D5CA8(FieldSystem *fieldSystem)
{
    return 1;
}

static BOOL FieldMap_021D5CAC(FieldSystem *fieldSystem)
{
    return 1;
}
