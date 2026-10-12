#ifndef POKEPLATINUM_MAIN_MENU_02235D18_H
#define POKEPLATINUM_MAIN_MENU_02235D18_H

#include "main_menu/gba_save.h"

enum AGBGameType {
    AGB_TYPE_RUBY = 0,
    AGB_TYPE_SAPPHIRE,
    AGB_TYPE_LEAFGREEN,
    AGB_TYPE_FIRERED,
    AGB_TYPE_EMERALD,
};

enum AGBGameSet {
    AGB_SET_RUBYSAPP = 0,
    AGB_SET_FIRELEAF,
    AGB_SET_EMERALD,
};

int GBACart_LoadInfo(GBASaveSlot *saveSlot);
void ResetLoadedGBACartInfo(void);
int GBACart_GetAGBGameType(void);
int GBACart_GetLanguage(void);
int GBACart_LoadSave(void);
BOOL GBACart_WriteNextSector(void);
int GBACart_GetWriteResult(void);
int GBACart_GetWriteState(void);
GBAPokemonStorage *GetGBAPokemonStorage(void);
GBASaveBlock2 *GetGBASaveBlock2(void);

#endif // POKEPLATINUM_MAIN_MENU_02235D18_H
