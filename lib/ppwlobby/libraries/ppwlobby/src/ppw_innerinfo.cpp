#include "ppwlobby/ppw_innerinfo.h"

#include <lobby/dwci_lobby.h>

#include "ilobby/dwci_lobbybase.h"
#include "ilobby/dwci_lobby_util.h"
#include "ppwlobby/ppw_lobby_impl.h"
#include "ppwlobby/ppw_parser.h"

PPW_LobbyInnerInfo::PPW_LobbyInnerInfo()
    : unk_00(0)
    , unk_04(FALSE)
    , unk_08()
    , unk_10(PPW_LOBBY_INVALID_TIME)
    , unk_18(FALSE)
    , unk_1C()
    , unk_20()
    , unk_28()
    , unk_29()
    , unk_2C()
    , unk_38()
    , unk_50()
    , unk_5C()
{
}

BOOL PPW_LobbyInnerInfo::GetSchedule(PPW_LobbySchedule *param0, u32 &param1) const
{
    u32 v0 = sizeof(PPW_LobbySchedule) + sizeof(PPW_LobbyScheduleRecord) * (unk_2C.size() - 1);

    u32 v1 = param1;
    param1 = v0;
    if (v1 < v0 || !param0) {
        return FALSE;
    }

    param0->lockTime = unk_1C;
    param0->random = unk_20;
    param0->roomFlag = unk_24;
    param0->roomType = unk_28;
    param0->season = unk_29;
    param0->scheduleRecordNum = unk_2C.size();
    if (param0->scheduleRecordNum != 0) {
        MI_CpuCopy8(PPW_GetVectorData(unk_2C), param0->scheduleRecords, sizeof(PPW_LobbyScheduleRecord) * unk_2C.size());
    }
    return TRUE;
}

std::vector<u8, PPW_Allocator<u8> > PPW_LobbyInnerInfo::SerializeSchedule() const
{
    u32 v0 = 0;
    GetSchedule(NULL, v0);
    std::vector<u8, PPW_Allocator<u8> > v1(v0);
    GetSchedule((PPW_LobbySchedule *)PPW_GetVectorData(v1), v0);
    return v1;
}

BOOL PPW_LobbyInnerInfo::SetSchedule(const u8 *param0, u32 param1)
{
    if (!ValidateSchedule(param0, param1)) {
        return FALSE;
    }

    PPW_LobbySchedule *v0 = (PPW_LobbySchedule *)param0;
    unk_28 = v0->roomType;
    unk_29 = v0->season;
    unk_1C = v0->lockTime;
    unk_20 = v0->random;
    unk_2C.assign(v0->scheduleRecords, v0->scheduleRecords + v0->scheduleRecordNum);
    std::stable_sort(unk_2C.begin(), unk_2C.end(), ScheduleRecordLess());

    unk_38.assign(unk_2C.begin(), unk_2C.end());
    return TRUE;
}

BOOL PPW_LobbyInnerInfo::ValidateSchedule(const u8 *param0, u32 param1)
{
    if (param1 < sizeof(PPW_LobbySchedule) - sizeof(PPW_LobbyScheduleRecord)) {
        return FALSE;
    }

    PPW_LobbySchedule *v0 = (PPW_LobbySchedule *)param0;

    if (param1 < sizeof(PPW_LobbySchedule) + sizeof(PPW_LobbyScheduleRecord) * (v0->scheduleRecordNum - 1)) {
        return FALSE;
    }
    return TRUE;
}

BOOL PPW_LobbyInnerInfo::SetVip(const u8 *param0, u32 param1)
{
    ValidateVip(param0, param1);

    u32 v0 = param1 / sizeof(PPW_LobbyVipRecord);

    PPW_LobbyVipRecord *tempRecords = (PPW_LobbyVipRecord *)param0;
    unk_50.assign(tempRecords, tempRecords + v0);
    return TRUE;
}

BOOL PPW_LobbyInnerInfo::ValidateVip(const u8 *param0, u32 param1)
{
    if (param1 % sizeof(PPW_LobbyVipRecord) != 0) {
        return FALSE;
    }

    if (param1 == 0) {
        unk_50.clear();
        return TRUE;
    }

    return TRUE;
}

BOOL PPW_LobbyInnerInfo::GetQuestionnaire(PPW_LobbyQuestionnaire *param0)
{
    if (!unk_334) {
        return FALSE;
    }

    MI_CpuCopy8(&unk_5C, param0, sizeof(PPW_LobbyQuestionnaire));
    return TRUE;
}

void PPW_LobbyInnerInfo::SetQuestionnaire(const PPW_LobbyQuestionnaire *param0)
{
    MI_CpuCopy8(param0, &unk_5C, sizeof(PPW_LobbyQuestionnaire));
    unk_334 = TRUE;
}

void PPW_LobbyInnerInfo::Update()
{
    switch (unk_00) {
    case 0:
    case 1:
    case 2:
    case 3:
        break;
    case 4:
        if (ShouldProgressSchedule()) {
            DWCi_LobbySetChannelMode(PPW_LobbyGetImpl()->GetMainChannel().GetName().c_str(), &PPW_LOBBY_CHANNEL_MODE_MAIN_LOCK);

            PPW_LobbyEmptyMessage v0;
            PPW_LobbySendMessage(PPW_LOBBY_INVALID_USER_ID, PPW_LOBBY_CHANNEL_KIND_MAIN, 1, PPW_MessageParser::PPW_LOBBY_MESSAGE_KIND_SYSTEM, 0, (u8 *)&v0, sizeof(PPW_LobbyEmptyMessage));

            ProgressSchedule();
        }
        break;
    case 5:
        if (unk_38.empty()) {
            break;
        }
        PPW_LobbyScheduleRecord &v1 = unk_38.front();
        s64 v2 = PPW_GetCurrentTimeSeconds();
        while (v1.time <= v2 - unk_10) {
            PPW_LobbyGetImpl()->GetCallbacks().lobbyScheduleProgressCallback(v1.event);
            unk_38.pop_front();
            if (unk_38.empty()) {
                break;
            }
            v1 = unk_38.front();
        }
        break;
    default:
        break;
    }
}

BOOL PPW_LobbyInnerInfo::ShouldProgressSchedule() const
{
    if (unk_00 == 5 || PPW_LobbyGetImpl()->GetState() != 8) {
        return FALSE;
    }

    if (unk_10 != PPW_LOBBY_INVALID_TIME) {
        return FALSE;
    }

    if (unk_18) {
        return TRUE;
    }

    if (PPW_LobbyGetImpl()->GetPlayers().IsFull()) {
        return TRUE;
    }

    if (PPW_GetCurrentTimeSeconds() > unk_08.unk_00 + unk_1C) {
        return TRUE;
    }

    return FALSE;
}

BOOL PPW_LobbyInnerInfo::ProgressSchedule()
{
    if (unk_00 != 5 && PPW_LobbyGetImpl()->GetState() == 8) {
        unk_10 = PPW_GetCurrentTimeSeconds();
        unk_00 = 5;
        unk_18 = FALSE;

        PPW_LobbyGetImpl()->GetCallbacks().lobbyScheduleProgressCallback(PPW_LOBBY_TIME_EVENT_LOCK);
        return TRUE;
    }

    unk_18 = TRUE;

    return FALSE;
}
