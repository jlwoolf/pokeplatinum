#ifndef POKEPLATINUM_STRUCT_MYSTERY_GIFT_GAME_INFO_H
#define POKEPLATINUM_STRUCT_MYSTERY_GIFT_GAME_INFO_H

typedef struct {
    u32 trainerId;
    u8 commType;
    u8 contestRegulation;
    u8 padding_06[2];
    u8 eventData[84];
} MysteryGiftGameInfo;

#endif // POKEPLATINUM_STRUCT_MYSTERY_GIFT_GAME_INFO_H
