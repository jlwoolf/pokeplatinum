#include "global_terminal/global_terminal_0222AE60.h"

#include <nitro.h>

#include "constants/species.h"

#include "struct_defs/dress_up_photo.h"
#include "struct_defs/struct_02030A80.h"

#include "global_terminal/struct_global_terminal_0222AE80.h"
#include "global_terminal/struct_global_terminal_0222AFC0.h"
#include "global_terminal/struct_global_terminal_0222AFCC.h"
#include "overlay062/struct_ov62_02239DA4.h"
#include "overlay062/struct_ov62_02239DA4_sub1.h"

#include "pc_boxes.h"
#include "savedata.h"
#include "string_gf.h"
#include "image_clips.h"

void GlobalTerminal_SerializeDressUpPhoto(SaveData *saveData, const DressUpPhoto *photo, GlobalTerminalDressUpPhoto *param2)
{
    DressUpPhoto_Serialize(photo, param2);
    param2->unk_5C.unk_00 = SaveData_CalculateChecksum(saveData, param2, sizeof(GlobalTerminalDressUpPhoto) - (sizeof(UnkStruct_ov62_02239DA4_sub1)));
}

void GlobalTerminal_DeserializeDressUpPhoto(const GlobalTerminalDressUpPhoto *param0, DressUpPhoto *photo)
{
    DressUpPhoto_Deserialize(param0, photo);
}

void GlobalTerminal_SerializePCBox(SaveData *saveData, const PCBoxes *pcBoxes, int boxID, UnkStruct_ov62_02239DA4 *param3, enum HeapID heapID)
{
    String *v0;
    int v1;

    MI_CpuClear8(param3, sizeof(UnkStruct_ov62_02239DA4));

    v0 = String_Init(20 * 3, heapID);
    PCBoxes_BufferBoxName(pcBoxes, boxID, v0);
    String_ToChars(v0, param3->unk_00, 20);
    String_Free(v0);

    for (v1 = 0; v1 < 30; v1++) {
        param3->unk_28[v1] = PCBoxes_GetBoxMonData(pcBoxes, boxID, v1, MON_DATA_SPECIES, NULL);
        param3->unk_64[v1] = PCBoxes_GetBoxMonData(pcBoxes, boxID, v1, MON_DATA_PERSONALITY, NULL);
        param3->unk_DC[v1] = PCBoxes_GetBoxMonData(pcBoxes, boxID, v1, MON_DATA_OT_ID, NULL);

        if (PCBoxes_GetBoxMonData(pcBoxes, boxID, v1, MON_DATA_SPECIES_OR_EGG, NULL) == SPECIES_EGG) {
            param3->unk_154 |= 1 << v1;
        }

        param3->unk_158[v1] = PCBoxes_GetBoxMonData(pcBoxes, boxID, v1, MON_DATA_FORM, NULL);
    }

    param3->unk_176 = PCBoxes_GetWallpaper(pcBoxes, boxID);
    param3->unk_177 = 0;
    param3->unk_198.unk_00 = SaveData_CalculateChecksum(saveData, param3, sizeof(UnkStruct_ov62_02239DA4) - (sizeof(UnkStruct_ov62_02239DA4_sub1)));
}

void GlobalTerminal_UpdatePCBoxChecksum(SaveData *saveData, UnkStruct_ov62_02239DA4 *param1, int param2)
{
    param1->unk_177 = param2;
    param1->unk_198.unk_00 = SaveData_CalculateChecksum(saveData, param1, sizeof(UnkStruct_ov62_02239DA4) - (sizeof(UnkStruct_ov62_02239DA4_sub1)));
}

void GlobalTerminal_SerializePlayerProfile(SaveData *saveData, const PlayerProfile *param1, GlobalTerminalPlayerProfile *param2)
{
    GF_ASSERT(sizeof(GlobalTerminalPlayerProfile) == sizeof(PlayerProfile));
    MI_CpuClear8(param2, sizeof(GlobalTerminalPlayerProfile));
    MI_CpuCopy8(param1, param2, sizeof(GlobalTerminalPlayerProfile));
}

void GlobalTerminal_DeserializePlayerProfile(const GlobalTerminalPlayerProfile *param0, PlayerProfile *param1)
{
    GF_ASSERT(sizeof(GlobalTerminalPlayerProfile) == sizeof(PlayerProfile));
    MI_CpuCopy8(param0, param1, sizeof(GlobalTerminalPlayerProfile));
}

void GlobalTerminal_SerializeProfileSummary(SaveData *saveData, const PlayerProfile *param1, GlobalTerminalProfileSummary *param2)
{
    MI_CpuClear8(param2, sizeof(GlobalTerminalProfileSummary));

    param2->version = param1->version;
    param2->language = param1->language;
    param2->month = param1->month;
    param2->appearance = param1->appearance;
    param2->species = param1->species;
    param2->isEgg = param1->isEgg;
}
