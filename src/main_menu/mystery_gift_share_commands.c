#include "main_menu/mystery_gift_share_commands.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/comm_cmd_table.h"

#include "main_menu/mystery_gift_share.h"

#include "comm_cmd.h"

static const CommCmdTable sMysteryGiftShareCommands[] = {
    { MysteryGiftShare_OnEventDataReceived, MysteryGiftShare_GetWonderCardSize, MysteryGiftShare_GetWonderCardBuffer },
    { MysteryGiftShare_OnPlayerInfoReceived, CommPacketSizeOf_Nothing, NULL }
};

void MysteryGiftShare_InitCommands(void *param0)
{
    int v0 = sizeof(sMysteryGiftShareCommands) / sizeof(CommCmdTable);
    CommCmd_Init(sMysteryGiftShareCommands, v0, param0);
}
