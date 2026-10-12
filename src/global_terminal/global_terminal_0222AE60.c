#include "global_terminal/global_terminal_0222AE60.h"

#include <nitro.h>

#include "constants/species.h"

#include "struct_defs/dress_up_photo.h"
#include "struct_defs/struct_02030A80.h"

#include "global_terminal/struct_global_terminal_0222AE80.h"
#include "global_terminal/struct_global_terminal_0222AFC0.h"
#include "global_terminal/struct_global_terminal_0222AFCC.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02239DA4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02239DA4_sub1.h"

#include "pc_boxes.h"
#include "savedata.h"
#include "string_gf.h"
#include "image_clips.h"

void GlobalTerminal_SerializeDressUpPhoto(SaveData *saveData, const DressUpPhoto *photo, GlobalTerminalDressUpPhoto *param2)
{
    DressUpPhoto_Serialize(photo, param2);
    param2->checksum.value = SaveData_CalculateChecksum(saveData, param2, sizeof(GlobalTerminalDressUpPhoto) - (sizeof(VsRecorderViewerBoxChecksum)));
}

void GlobalTerminal_DeserializeDressUpPhoto(const GlobalTerminalDressUpPhoto *param0, DressUpPhoto *photo)
{
    DressUpPhoto_Deserialize(param0, photo);
}

void GlobalTerminal_SerializePCBox(SaveData *saveData, const PCBoxes *pcBoxes, int boxID, VsRecorderViewerBoxData *param3, enum HeapID heapID)
{
    String *v0;
    int v1;

    MI_CpuClear8(param3, sizeof(VsRecorderViewerBoxData));

    v0 = String_Init(20 * 3, heapID);
    PCBoxes_BufferBoxName(pcBoxes, boxID, v0);
    String_ToChars(v0, param3->boxName, 20);
    String_Free(v0);

    for (v1 = 0; v1 < 30; v1++) {
        param3->species[v1] = PCBoxes_GetBoxMonData(pcBoxes, boxID, v1, MON_DATA_SPECIES, NULL);
        param3->personality[v1] = PCBoxes_GetBoxMonData(pcBoxes, boxID, v1, MON_DATA_PERSONALITY, NULL);
        param3->otId[v1] = PCBoxes_GetBoxMonData(pcBoxes, boxID, v1, MON_DATA_OT_ID, NULL);

        if (PCBoxes_GetBoxMonData(pcBoxes, boxID, v1, MON_DATA_SPECIES_OR_EGG, NULL) == SPECIES_EGG) {
            param3->eggFlags |= 1 << v1;
        }

        param3->form[v1] = PCBoxes_GetBoxMonData(pcBoxes, boxID, v1, MON_DATA_FORM, NULL);
    }

    param3->wallpaper = PCBoxes_GetWallpaper(pcBoxes, boxID);
    param3->version = 0;
    param3->checksum.value = SaveData_CalculateChecksum(saveData, param3, sizeof(VsRecorderViewerBoxData) - (sizeof(VsRecorderViewerBoxChecksum)));
}

void GlobalTerminal_UpdatePCBoxChecksum(SaveData *saveData, VsRecorderViewerBoxData *param1, int param2)
{
    param1->version = param2;
    param1->checksum.value = SaveData_CalculateChecksum(saveData, param1, sizeof(VsRecorderViewerBoxData) - (sizeof(VsRecorderViewerBoxChecksum)));
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
