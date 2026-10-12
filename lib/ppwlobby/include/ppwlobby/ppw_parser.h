#ifndef PPWLOBBY_PARSER_H
#define PPWLOBBY_PARSER_H

#include "ilobby/dwci_lobby_util.h"
#include "ppwlobby/ppw_lobby.h"

class PPW_MessageParser : public DWCi_LobbyObject {
public:
    typedef enum MessageKind {
        PPW_LOBBY_MESSAGE_KIND_SYSTEM,
        PPW_LOBBY_MESSAGE_KIND_USER
    } MessageKind;

    struct ParsedMessage : public DWCi_LobbyObject {
        u32 unk_00;
        u32 unk_04;
        int unk_08;
        MessageKind unk_0C;
        s32 unk_10;
        u32 unused;
        std::vector<u8, PPW_Allocator<u8> > unk_18;

        ParsedMessage()
            : unk_00(0)
            , unk_04(6)
            , unk_08(0)
            , unk_0C(PPW_MessageParser::PPW_LOBBY_MESSAGE_KIND_SYSTEM)
            , unk_10(0)
            , unused(0)
            , unk_18()
        {
        }
    };

    static BOOL Parse(const PPWString &param0, ParsedMessage &param1);
    static BOOL Build(int param0, MessageKind param1, s32 param2, const char *param3, std::size_t param4, PPWString &param5);
};

#endif // PPWLOBBY_PARSER_H
