#ifndef PPWLOBBY_INNERINFO_H
#define PPWLOBBY_INNERINFO_H

// needs to be included first to match
// clang-format off
#include <vector>
// clang-format on
#include <deque>
#include <functional>

#include "ilobby/dwci_lobbydata.h"
#include "ilobby/dwci_lobby_util.h"
#include "ppwlobby/ppw_lobby.h"

class PPW_LobbyInnerInfo : public DWCi_LobbyObject {
public:
    struct OpenedTime {
        s64 unk_00;

        OpenedTime()
            : unk_00(PPW_LOBBY_INVALID_TIME)
        {
        }

        void SetQuestionnaireReceived()
        {
            unk_00 = PPW_GetCurrentTimeSeconds();
        }
    };

private:
    struct ScheduleRecordLess : std::binary_function<const PPW_LobbyScheduleRecord &, const PPW_LobbyScheduleRecord &, bool> {
        bool operator()(const PPW_LobbyScheduleRecord &param0, const PPW_LobbyScheduleRecord &param1) const
        {
            return param0.time < param1.time;
        }
    };

    int unk_00;
    BOOL unk_04;
    OpenedTime unk_08;
    s64 unk_10;
    BOOL unk_18;
    u32 unk_1C;
    u32 unk_20;
    u32 unk_24;
    u8 unk_28;
    u8 unk_29;
    std::vector<PPW_LobbyScheduleRecord, PPW_Allocator<PPW_LobbyScheduleRecord> > unk_2C;
    std::deque<PPW_LobbyScheduleRecord, PPW_Allocator<PPW_LobbyScheduleRecord> > unk_38;
    std::vector<PPW_LobbyVipRecord, PPW_Allocator<PPW_LobbyVipRecord> > unk_50;
    PPW_LobbyQuestionnaire unk_5C;
    BOOL unk_334;

public:
    PPW_LobbyInnerInfo();

    BOOL GetSchedule(PPW_LobbySchedule *param0, u32 &param1) const;
    BOOL SetSchedule(const u8 *param0, u32 param1);
    BOOL ValidateSchedule(const u8 *param0, u32 param1);
    BOOL SetVip(const u8 *param0, u32 param1);
    BOOL ValidateVip(const u8 *param0, u32 param1);
    BOOL GetQuestionnaire(PPW_LobbyQuestionnaire *param0);
    void SetQuestionnaire(const PPW_LobbyQuestionnaire *param0);
    std::vector<u8, PPW_Allocator<u8> > SerializeSchedule() const;
    void Update();
    BOOL ShouldProgressSchedule() const;
    BOOL ProgressSchedule();

    BOOL SetQuestionnaireReceived()
    {
        unk_00 = 2;
        return TRUE;
    }

    BOOL IsQuestionnaireReceived()
    {
        return unk_00 >= 2;
    }

    BOOL SetScheduleReceived()
    {
        unk_00 = 4;
        return TRUE;
    }

    BOOL IsScheduleReceived() const
    {
        return unk_00 >= 4;
    }

    BOOL IsOpenedTimeSet() const
    {
        return unk_04;
    }

    void SetOpenedTime(OpenedTime param0)
    {
        unk_04 = TRUE;
        unk_08 = param0;
    }

    void GetTimeInfo(PPW_LobbyTimeInfo &param0) const
    {
        param0.currentTime = PPW_GetCurrentTimeSeconds();
        param0.openedTime = unk_08.unk_00;
        param0.lockedTime = unk_10;
    }

    OpenedTime RefreshOpenedTime()
    {
        unk_08.SetQuestionnaireReceived();
        return unk_08;
    }
};

#endif // PPWLOBBY_INNERINFO_H
