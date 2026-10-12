#include "ppwlobby/ppw_parser.h"

BOOL PPW_MessageParser::Parse(const PPWString &param0, ParsedMessage &param1)
{
    std::vector<PPWString, PPW_Allocator<PPWString> > v0 = PPW_SplitString<PPWString>(param0, "  ", 2);

    if (v0.size() != 2) {
        return FALSE;
    }

    if (v0[0].length() > 40) {
        return FALSE;
    }

    if (v0[1].length() > PPW_LOBBY_MAX_STRING_SIZE) {
        return FALSE;
    }

    {
        std::vector<PPWString, PPW_Allocator<PPWString> > v1 = PPW_SplitString<PPWString>(v0[0], " ");
        if (v1.size() < 6) {
            return FALSE;
        }

        char *v2;
        param1.unk_00 = strtoul(v1[0].c_str(), &v2, 16);
        param1.unk_04 = strtoul(v1[1].c_str(), &v2, 16);
        param1.unk_08 = PPW_StrniCmpCStr(v1[2].c_str(), "B", 1) == 0 ? 1 : 0;
        param1.unk_0C = PPW_StrniCmpCStr(v1[3].c_str(), "S", 1) == 0 ? PPW_LOBBY_MESSAGE_KIND_SYSTEM : PPW_LOBBY_MESSAGE_KIND_USER;
        param1.unk_10 = strtol(v1[4].c_str(), &v2, 16);
    }

    if (param1.unk_08 == 1) {
        if (!PPW_Base64DecodeToVector(v0[1].c_str(), param1.unk_18)) {
            return FALSE;
        }
    } else {
        param1.unk_18.assign((const u8 *)v0[1].c_str(), (const u8 *)v0[1].c_str() + v0[1].length());
        param1.unk_18.push_back('\0');
    }

    return TRUE;
}

BOOL PPW_MessageParser::Build(int param0, PPW_MessageParser::MessageKind param1, s32 param2, const char *param3, std::size_t param4, PPWString &param5)
{
    if (param0 == 0 && param4 > PPW_LOBBY_MAX_STRING_SIZE) {
        return FALSE;
    }
    if (param0 == 1 && param4 > PPW_LOBBY_MAX_BINARY_SIZE) {
        return FALSE;
    }

    param5 = "";

    param5 += PPW_FormatStringTrunc<PPWString>(3, "%x", 0);
    param5 += " ";
    param5 += PPW_FormatStringTrunc<PPWString>(2, "%x", 6);
    param5 += " ";

    switch (param0) {
    case 0:
        param5 += "S";
        break;
    case 1:
        param5 += "B";
        break;
    default:
        return FALSE;
    }

    param5 += " ";

    switch (param1) {
    case PPW_MessageParser::PPW_LOBBY_MESSAGE_KIND_USER:
        param5 += "A";
        break;
    case PPW_MessageParser::PPW_LOBBY_MESSAGE_KIND_SYSTEM:
        param5 += "S";
        break;
    default:
        return FALSE;
    }

    param5 += " ";

    param5 += PPW_FormatStringTrunc<PPWString>(8, "%x", param2);
    param5 += " ";

    param5 += "_";

    param5 += "  ";

    switch (param0) {
    case 0:
        param5 += PPW_FormatStringTrunc<PPWString>(param4, "%s", param3);
        break;
    case 1: {
        char v0[PPW_LOBBY_MAX_STRING_SIZE + 1];
        MI_CpuClear8(v0, sizeof(v0));

        int writtenSize = DWC_Base64Encode(param3, param4, v0, sizeof(v0));
        if (writtenSize == -1) {
            return FALSE;
        }
        param5 += v0;
    } break;
    default:
        return FALSE;
    }
    return TRUE;
}
