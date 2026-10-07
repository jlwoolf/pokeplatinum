#ifndef POKEPLATINUM_ENUMS_H
#define POKEPLATINUM_ENUMS_H

typedef enum {
    UnkEnum_0202F510_00,
    UnkEnum_0202F510_01,
    UnkEnum_0202F510_02,
    UnkEnum_0202F510_03,
    UnkEnum_0202F510_04,
    UnkEnum_0202F510_05,
    UnkEnum_0202F510_06,
    UnkEnum_0202F510_07,
    UnkEnum_0202F510_08,
    UnkEnum_0202F510_09,
    UnkEnum_0202F510_10,
    UnkEnum_0202F510_11,
    UnkEnum_0202F510_12,
    UnkEnum_0202F510_13,
    UnkEnum_0202F510_14,
    UnkEnum_0202F510_15,
    UnkEnum_0202F510_16,
    UnkEnum_0202F510_17,
    UnkEnum_0202F510_18,
    UnkEnum_0202F510_19,
    UnkEnum_0202F510_20,
    UnkEnum_0202F510_21,
    UnkEnum_0202F510_22,
    UnkEnum_0202F510_23,
    UnkEnum_0202F510_24,
    UnkEnum_0202F510_25,
    UnkEnum_0202F510_26,
    UnkEnum_0202F510_27,
    UnkEnum_0202F510_28,
    UnkEnum_0202F510_29,
    UnkEnum_0202F510_30,
    UnkEnum_0202F510_31,
    UnkEnum_0202F510_32,
    UnkEnum_0202F510_33 = 0xfa,
    UnkEnum_0202F510_34 = 0xfb,
    UnkEnum_0202F510_35 = 0xfc,
    UnkEnum_0202F510_36 = 0xfd,
    UnkEnum_0202F510_37 = 0xfe,
    UnkEnum_0202F510_38 = 0xff,
} UnkEnum_0202F510;

typedef enum {
    SlotMachineSymbol_00 = 0,
    SlotMachineSymbol_01,
    SlotMachineSymbol_02,
    SlotMachineSymbol_03,
    SlotMachineSymbol_04,
    SlotMachineSymbol_05,
    SlotMachineSymbol_06,
} SlotMachineSymbol;

typedef enum {
    SlotMachineReelIndex_00,
    SlotMachineReelIndex_01,
    SlotMachineReelIndex_02,
    SlotMachineReelIndex_03,
} SlotMachineReelIndex;

typedef enum {
    SlotMachinePaletteIndex_00 = 0,
    SlotMachinePaletteIndex_01,
    SlotMachinePaletteIndex_02,
    SlotMachinePaletteIndex_03,
    SlotMachinePaletteIndex_04,
    SlotMachinePaletteIndex_05,
} SlotMachinePaletteIndex;

typedef enum {
    SlotMachineReelButtonState_00 = 0,
    SlotMachineReelButtonState_01,
    SlotMachineReelButtonState_02,
} SlotMachineReelButtonState;

typedef enum {
    SlotMachineReelType_00 = 0,
    SlotMachineReelType_01,
    SlotMachineReelType_02,
    SlotMachineReelType_03,
    SlotMachineReelType_04,
    SlotMachineReelType_05,
} SlotMachineReelType;

typedef enum {
    SlotMachineReelStateEnum_00 = 0,
    SlotMachineReelStateEnum_01,
    SlotMachineReelStateEnum_02,
    SlotMachineReelStateEnum_03,
    SlotMachineReelStateEnum_04,
    SlotMachineReelStateEnum_05,
    SlotMachineReelStateEnum_06,
    SlotMachineReelStateEnum_07,
} SlotMachineReelStateEnum;

typedef enum {
    SlotMachineWinType_00 = 0,
    SlotMachineWinType_01,
    SlotMachineWinType_02,
    SlotMachineWinType_03,
} SlotMachineWinType;

typedef enum {
    SlotMachineWinSymbolState_00,
    SlotMachineWinSymbolState_01,
    SlotMachineWinSymbolState_02,
    SlotMachineWinSymbolState_03,
    SlotMachineWinSymbolState_04,
    SlotMachineWinSymbolState_05,
    SlotMachineWinSymbolState_06,
    SlotMachineWinSymbolState_07,
    SlotMachineWinSymbolState_08,
    SlotMachineWinSymbolState_09,
} SlotMachineWinSymbolState;

typedef enum {
    SlotMachinePayoutResultEnum_00 = 0,
    SlotMachinePayoutResultEnum_01,
    SlotMachinePayoutResultEnum_02,
    SlotMachinePayoutResultEnum_03,
} SlotMachinePayoutResultEnum;

typedef enum {
    SlotMachineNumberType_00 = 0,
    SlotMachineNumberType_01,
} SlotMachineNumberType;

typedef enum {
    SlotMachineBonusType_00 = 0,
    SlotMachineBonusType_01,
    SlotMachineBonusType_02,
    SlotMachineBonusType_03,
    SlotMachineBonusType_04,
    SlotMachineBonusType_05,
    SlotMachineBonusType_06,
} SlotMachineBonusType;

typedef enum {
    SlotMachineBonusKind_00 = 0,
    SlotMachineBonusKind_01,
    SlotMachineBonusKind_02,
    SlotMachineBonusKind_03,
} SlotMachineBonusKind;

typedef enum {
    SlotMachinePayoutThreshold_00 = 0,
    SlotMachinePayoutThreshold_01 = 5,
    SlotMachinePayoutThreshold_02 = 15,
    SlotMachinePayoutThreshold_03 = 25,
    SlotMachinePayoutThreshold_04 = 35,
    SlotMachinePayoutThreshold_05 = 45,
    SlotMachinePayoutThreshold_06 = 55,
    SlotMachinePayoutThreshold_07 = 65,
    SlotMachinePayoutThreshold_08 = 75,
    SlotMachinePayoutThreshold_09 = 9,
} SlotMachinePayoutThreshold;

typedef enum {
    SlotMachineBgmMode_00,
    SlotMachineBgmMode_01,
    SlotMachineBgmMode_02,
    SlotMachineBgmMode_03,
} SlotMachineBgmMode;

typedef enum {
    WiFiPlazaLobbyNewsResultFlags_00 = 0,
    WiFiPlazaLobbyNewsResultFlags_01 = 1 << 0,
    WiFiPlazaLobbyNewsResultFlags_02 = 1 << 1,
} WiFiPlazaLobbyNewsResultFlags;

typedef enum {
    WiFiPlazaLobbyNewsState_00,
    WiFiPlazaLobbyNewsState_01,
    WiFiPlazaLobbyNewsState_02,
} WiFiPlazaLobbyNewsState;

enum PlazaMinigame {
    WiFiPlazaLobbyActivity_00,
    WiFiPlazaLobbyActivity_01,
    WiFiPlazaLobbyActivity_02,
    WiFiPlazaLobbyActivity_03,
    WiFiPlazaLobbyActivity_04,
    WiFiPlazaLobbyActivity_05,
    WiFiPlazaLobbyActivity_06,
    WiFiPlazaLobbyActivity_07,
    WiFiPlazaLobbyActivity_08,
    WiFiPlazaLobbyActivity_09,
    WiFiPlazaLobbyActivity_10,
    WiFiPlazaLobbyActivity_11,
    WiFiPlazaLobbyActivity_12 = WiFiPlazaLobbyActivity_02 + 1,
};

enum {
    GX_BLEND_BGALL = GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3,
    GX_BLEND_ALL = GX_BLEND_BGALL | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD,
};

enum {
    GX_WND_PLANEMASK_BGALL = GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3,
    GX_WND_PLANEMASK_ALL = GX_WND_PLANEMASK_BGALL | GX_WND_PLANEMASK_OBJ,
};

typedef enum {
    WiFiPlazaLobbyNetworkLobbyState_00,
    WiFiPlazaLobbyNetworkLobbyState_01,
    WiFiPlazaLobbyNetworkLobbyState_02,
    WiFiPlazaLobbyNetworkLobbyState_03,
    WiFiPlazaLobbyNetworkLobbyState_04
} WiFiPlazaLobbyNetworkLobbyState;

typedef enum {
    WiFiPlazaLobbyNetworkScheduleField_00,
    WiFiPlazaLobbyNetworkScheduleField_01,
    WiFiPlazaLobbyNetworkScheduleField_02,
    WiFiPlazaLobbyNetworkScheduleField_03,
    WiFiPlazaLobbyNetworkScheduleField_04,
    WiFiPlazaLobbyNetworkScheduleField_05,
    WiFiPlazaLobbyNetworkScheduleField_06,
    WiFiPlazaLobbyNetworkScheduleField_07,
    WiFiPlazaLobbyNetworkScheduleField_08,
} WiFiPlazaLobbyNetworkScheduleField;

typedef enum {
    WiFiPlazaLobbyNetworkSubChannelKind_00,
    WiFiPlazaLobbyNetworkSubChannelKind_01,
    WiFiPlazaLobbyNetworkSubChannelKind_02,
    WiFiPlazaLobbyNetworkSubChannelKind_03,
    WiFiPlazaLobbyNetworkSubChannelKind_04,
} WiFiPlazaLobbyNetworkSubChannelKind;

typedef enum {
    WiFiPlazaLobbyNetworkSubChannelJoinState_00,
    WiFiPlazaLobbyNetworkSubChannelJoinState_01,
    WiFiPlazaLobbyNetworkSubChannelJoinState_02,
} WiFiPlazaLobbyNetworkSubChannelJoinState;

typedef enum {
    WiFiPlazaLobbyNetworkGameKind_00,
    WiFiPlazaLobbyNetworkGameKind_01,
    WiFiPlazaLobbyNetworkGameKind_02,
    WiFiPlazaLobbyNetworkGameKind_03,
} WiFiPlazaLobbyNetworkGameKind;

typedef enum {
    WiFiPlazaLobbyNetworkQuestionnaireSubmitState_00,
    WiFiPlazaLobbyNetworkQuestionnaireSubmitState_01,
    WiFiPlazaLobbyNetworkQuestionnaireSubmitState_02,
    WiFiPlazaLobbyNetworkQuestionnaireSubmitState_03,
} WiFiPlazaLobbyNetworkQuestionnaireSubmitState;

typedef enum {
    WiFiPlazaLobbyNetworkQuestionnaireField_00,
    WiFiPlazaLobbyNetworkQuestionnaireField_01,
    WiFiPlazaLobbyNetworkQuestionnaireField_02,
    WiFiPlazaLobbyNetworkQuestionnaireField_03,
    WiFiPlazaLobbyNetworkQuestionnaireField_04,
    WiFiPlazaLobbyNetworkQuestionnaireField_05,
    WiFiPlazaLobbyNetworkQuestionnaireField_06,
    WiFiPlazaLobbyNetworkQuestionnaireField_07,
    WiFiPlazaLobbyNetworkQuestionnaireField_08,
    WiFiPlazaLobbyNetworkQuestionnaireField_09,
    WiFiPlazaLobbyNetworkQuestionnaireField_10,
    WiFiPlazaLobbyNetworkQuestionnaireField_11,
} WiFiPlazaLobbyNetworkQuestionnaireField;

typedef enum {
    WiFiPlazaLobbyNetworkQuestionnaireText_00,
    WiFiPlazaLobbyNetworkQuestionnaireText_01,
    WiFiPlazaLobbyNetworkQuestionnaireText_02,
    WiFiPlazaLobbyNetworkQuestionnaireText_03,
    WiFiPlazaLobbyNetworkQuestionnaireText_04,
    WiFiPlazaLobbyNetworkQuestionnaireText_05,
    WiFiPlazaLobbyNetworkQuestionnaireText_06,
    WiFiPlazaLobbyNetworkQuestionnaireText_07,
    WiFiPlazaLobbyNetworkQuestionnaireText_08,
} WiFiPlazaLobbyNetworkQuestionnaireText;

typedef enum {
    WiFiPlazaLobbyNetworkQuestionnaireLanguage_00,
    WiFiPlazaLobbyNetworkQuestionnaireLanguage_01,
    WiFiPlazaLobbyNetworkQuestionnaireLanguage_02,
} WiFiPlazaLobbyNetworkQuestionnaireLanguage;

#endif // POKEPLATINUM_ENUMS_H
