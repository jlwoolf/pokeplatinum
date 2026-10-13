#ifndef POKEPLATINUM_STRUCT_MAIN_MENU_02232AC8_H
#define POKEPLATINUM_STRUCT_MAIN_MENU_02232AC8_H

typedef struct {
    void *unk_00;
    void *buffer;
    void *sendBuffer;
    void *recvBuffer;
    u32 sendSize;
    u32 recvSize;
    vu8 mode;
    vu8 state;
    u8 timer;
    u8 retryCount;
    u8 port;
} WirelessCommTransfer;

#endif // POKEPLATINUM_STRUCT_MAIN_MENU_02232AC8_H
