#include <nitro.h>
#include <string.h>

#include "constants/gba/global.h"
#include "constants/gba/items.h"
#include "constants/gba/pokemon.h"
#include "constants/gba/species.h"
#include "constants/graphics.h"
#include "constants/items.h"
#include "constants/narc.h"
#include "constants/pokemon.h"
#include "constants/species.h"

#include "applications/title_screen.h"
#include "main_menu/gba_convert_string.h"
#include "main_menu/gba_player.h"
#include "main_menu/gba_pokemon.h"
#include "main_menu/gba_save.h"
#include "main_menu/main_menu_util.h"
#include "main_menu/gba_cart.h"
#include "savedata/save_table.h"

#include "bg_window.h"
#include "char_transfer.h"
#include "charcode.h"
#include "font.h"
#include "game_options.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "item.h"
#include "main.h"
#include "message.h"
#include "narc.h"
#include "overlay_manager.h"
#include "pal_park_transfers.h"
#include "palette.h"
#include "pltt_transfer.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "render_oam.h"
#include "render_text.h"
#include "render_window.h"
#include "save_player.h"
#include "savedata.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "system.h"
#include "text.h"
#include "touch_screen.h"
#include "trainer_info.h"
#include "fatal_error_screen.h"
#include "vram_transfer.h"
#include "yes_no_touch_menu.h"

#include "res/graphics/main_menu/main_menu_graphics.naix"
#include "res/text/bank/migrate_from_gba.h"

FS_EXTERN_OVERLAY(game_opening);

enum GBAMigratorState {
    GBA_MIGRATOR_STATE_0 = 0,
    GBA_MIGRATOR_STATE_1,
    GBA_MIGRATOR_STATE_2,
    GBA_MIGRATOR_STATE_3,
    GBA_MIGRATOR_STATE_4,
    GBA_MIGRATOR_STATE_5,
    GBA_MIGRATOR_STATE_6,
    GBA_MIGRATOR_STATE_7,
    GBA_MIGRATOR_STATE_8,
    GBA_MIGRATOR_STATE_9,
    GBA_MIGRATOR_STATE_10,
    GBA_MIGRATOR_STATE_11,
    GBA_MIGRATOR_STATE_12,
    GBA_MIGRATOR_STATE_13,
    GBA_MIGRATOR_STATE_14,
    GBA_MIGRATOR_STATE_WAIT_FOR_FULL_SELECTION_TIMER,
    GBA_MIGRATOR_STATE_16,
    GBA_MIGRATOR_STATE_17,
    GBA_MIGRATOR_STATE_18,
    GBA_MIGRATOR_STATE_19,
    GBA_MIGRATOR_STATE_20,
    GBA_MIGRATOR_STATE_21,
    GBA_MIGRATOR_STATE_22,
    GBA_MIGRATOR_STATE_FADE_OUT_TO_SELECTED_MON,
    GBA_MIGRATOR_STATE_24,
};

enum GBAMonState {
    GBA_MON_STATE_NONE,
    GBA_MON_STATE_SELECTED,
    GBA_MON_STATE_DESELECTED,
    GBA_MON_STATE_EMPTY_SLOT,
    GBA_MON_STATE_IS_EGG,
    GBA_MON_STATE_HAS_HM,
    GBA_MON_STATE_HAS_INVALID_ITEM,
    GBA_MON_STATE_IS_INVALID_SPECIES,
};

enum CannotMigrateMsg {
    CAN_MIGRATE = 0,
    CANNOT_MIGRATE_GBA_PAK_READ_ERROR,
    CANNOT_MIGRATE_WAIT_FOR_FULL_DAY,
    CANNOT_MIGRATE_DIFFERENT_CONSOLE,
    CANNOT_MIGRATE_INTERNAL_CLOCK_ALTERED,
    CANNOT_MIGRATE_LESS_THAN_6_IN_GBA_BOXES,
    CANNOT_MIGRATE_ALREADY_STOCKED,
    CANNOT_MIGRATE_CLOCK_ADJUSTED,
};

typedef struct {
    Window *window;
    int unk_04;
    int x;
    int y;
    int width;
    int height;
    int textX;
    int textY;
    int baseTile;
    int bgLayer;
    int fontID;
    TextColor textColor;
    TextColor fillColor;
    int messageEntryID;
    charcode_t *charcodeString;
    String *string;
    StringTemplate *stringTemplate;
    int textSpeed;
    int printerID;
} GBAMigratorTextBox;

typedef struct {
    Sprite *monIconSprite;
    Sprite *heldItemSprite;
    int unk_08;
} GBAMigratorBoxMonSprites;

typedef struct {
    Sprite *selectionSprite;
    int boxPosition;
    int boxId;
} SelectedMonData;

typedef struct {
    int state;
    int timer;
    void *waitDial;
} GBAMigratorSaveState;

typedef struct {
    int charOffset;
    int paletteIndex;
    Sprite *iconSprite;
    u8 rawData[512];
} GBAMigratorMonSprite;

typedef struct {
    int gbaVersion;
    int canMigrateStatus;
    int messageEntryID;
    int frameCounter;
    SaveData *saveData;
    TrainerInfo *trainerInfo;
    Options *options;
    int messageBoxFrame;
    BgConfig *bgConfig;
    int nextState;
    SpriteList *spriteList;
    G2dRenderer g2dRenderer;
    SpriteResourceCollection *spriteResourceCollections[6];
    SpriteResource *spriteResources[6];
    SpriteResourcesHeader spriteResourcesHeader;
    GBAMigratorBoxMonSprites boxMonSprites[GBA_MAX_MONS_PER_BOX];
    TouchScreenRect touchScreenRects[GBA_MAX_MONS_PER_BOX + 4];
    Sprite *confirmSprites[4];
    Sprite *nextBoxSprites[4];
    Sprite *prevBoxSprites[4];
    SelectedMonData selectedMonData[CATCHING_SHOW_MONS];
    int selectedCount;
    Sprite *selectedMonIcons[CATCHING_SHOW_MONS];
    GBAMigratorTextBox textBox;
    Window boxNameWindow;
    Window monInfoWindow;
    Window messageWindow;
    int loadInfoResult;
    int loadSaveResult;
    GBASaveSlot saveSlot;
    GBAPokemonStorage *pokemonStorage;
    int currentBox;
    int fullSelectionTimer; // Used track how long to wait until fade out once all 6 mon have been selected.
    YesNoTouchMenu *yesNoTouchMenu;
    GBAMigratorSaveState saveState;
    GBAMigratorMonSprite monSprites[GBA_MAX_MONS_PER_BOX];
    void (*flushMonIcons)(void);
    String *messageString;
    String *tempString;
} GBAMigrator;

static void GBAMigrator_ShowBoxName(GBAMigrator *migrator, int boxNum);
static void GBAMigrator_UpdateSelectionSprites(GBAMigrator *migrator);
static void GBAMigrator_InitTextBoxWindow(GBAMigrator *migrator);
static void GBAMigrator_InitYesNoMenu(GBAMigrator *migrator);
static void CopySelectedMonToPalParkTransfer(GBAMigrator *migrator);
void String_CopyNumChars(String *param0, const u16 *param1, u32 param2);
void String_CopyChars(String *param0, const u16 *param1);
void BoxMonGBAToBoxMon(GBABoxPokemon *gbaBoxMon, BoxPokemon *boxMon);

GBAMigratorMonSprite *sGBAMigratorMonSprites;

static int sGBAHMMoves[] = {
    MOVE_CUT,
    MOVE_FLY,
    MOVE_SURF,
    MOVE_STRENGTH,
    MOVE_FLASH,
    MOVE_ROCK_SMASH,
    MOVE_WATERFALL,
    MOVE_DIVE
};

static int sMigrateFromGBAGameMessageIDs[] = {
    NULL,
    [VERSION_SAPPHIRE] = MigrateFromGBA_Text_FromSapphire,
    [VERSION_RUBY] = MigrateFromGBA_Text_FromRuby,
    [VERSION_EMERALD] = MigrateFromGBA_Text_FromEmerald,
    [VERSION_FIRERED] = MigrateFromGBA_Text_FromFirered,
    [VERSION_LEAFGREEN] = MigrateFromGBA_Text_FromLeafgreen,
};

static int sSavingOnGBAGameAndPlatinumMessageIDs[] = {
    NULL,
    [VERSION_SAPPHIRE] = MigrateFromGBA_Text_SavingOnSapphireAndPlatinum,
    [VERSION_RUBY] = MigrateFromGBA_Text_SavingOnRubyAndPlatinum,
    [VERSION_EMERALD] = MigrateFromGBA_Text_SavingOnEmeraldAndPlatinum,
    [VERSION_FIRERED] = MigrateFromGBA_Text_SavingOnFireredAndPlatinum,
    [VERSION_LEAFGREEN] = MigrateFromGBA_Text_SavingOnLeafgreenAndPlatinum,
};

static u8 sGBAGameRectPalettes[] = {
    0x0,
    [VERSION_SAPPHIRE] = 0x2,
    [VERSION_RUBY] = 0x1,
    [VERSION_EMERALD] = 0x3,
    [VERSION_FIRERED] = 0x4,
    [VERSION_LEAFGREEN] = 0x5,
};

static int sCannotMigrateMessageIDs[] = {
    [CAN_MIGRATE] = NULL,
    [CANNOT_MIGRATE_GBA_PAK_READ_ERROR] = MigrateFromGBA_Text_ErrorReadingGBAPak,
    [CANNOT_MIGRATE_WAIT_FOR_FULL_DAY] = MigrateFromGBA_Text_FullDayHasntPassed,
    [CANNOT_MIGRATE_DIFFERENT_CONSOLE] = MigrateFromGBA_Text_DifferentDsOrInternalClockAltered,
    [CANNOT_MIGRATE_INTERNAL_CLOCK_ALTERED] = MigrateFromGBA_Text_DifferentDsOrInternalClockAltered,
    [CANNOT_MIGRATE_LESS_THAN_6_IN_GBA_BOXES] = MigrateFromGBA_Text_LessThanSix,
    [CANNOT_MIGRATE_ALREADY_STOCKED] = MigrateFromGBA_Text_GameCardAlreadyStocked,
    [CANNOT_MIGRATE_CLOCK_ADJUSTED] = MigrateFromGBA_Text_GameClockAdjusted,
};

static BOOL IsGBASpeciesInvalid(int speciesGBA)
{
    if (speciesGBA <= SPECIES_NONE) {
        return TRUE;
    } else if (speciesGBA <= SPECIES_CELEBI) {
        return FALSE;
    } else if (speciesGBA < GBA_SPECIES_TREECKO) {
        return TRUE;
    } else if (speciesGBA <= GBA_SPECIES_CHIMECHO) {
        return FALSE;
    }

    return TRUE;
}

static void GBAMigrator_InitGbaVersion(GBAMigrator *migrator)
{
    switch (GBACart_GetAGBGameType()) {
    case AGB_TYPE_RUBY:
        migrator->gbaVersion = VERSION_RUBY;
        break;
    case AGB_TYPE_SAPPHIRE:
        migrator->gbaVersion = VERSION_SAPPHIRE;
        break;
    case AGB_TYPE_LEAFGREEN:
        migrator->gbaVersion = VERSION_LEAFGREEN;
        break;
    case AGB_TYPE_FIRERED:
        migrator->gbaVersion = VERSION_FIRERED;
        break;
    case AGB_TYPE_EMERALD:
        migrator->gbaVersion = VERSION_EMERALD;
        break;
    default:
        migrator->gbaVersion = -1;
        break;
    }
}

static int GBAMigrator_HandleSave(GBAMigrator *migrator)
{
    int v0;
    u8 v1[16];
    int saveResult;
    MigratedPokemon *transferData;
    GBAMigratorSaveState *v4 = &migrator->saveState;

    switch (v4->state) {
    case 0:
        CopySelectedMonToPalParkTransfer(migrator);
        transferData = SaveData_GetPalParkTransfer(migrator->saveData);
        PalParkTransfer_SaveTransferHistory(transferData, GetGBAPlayerTrainerId());
        v4->state++;
        break;
    case 1:
        v4->timer = 1 + OS_GetTick() % 120;
        v4->state++;
        break;
    case 2:
        if (--v4->timer == 0) {
            v4->state++;
        }
        break;
    case 3:
        SaveData_SaveStateInit(migrator->saveData, 2);
        v4->state++;
        break;
    case 4:
        saveResult = SaveData_SaveStateMain(migrator->saveData);

        if (saveResult == SAVE_RESULT_CORRUPT) {
            return 12;
        }

        if (saveResult == SAVE_RESULT_PROCEED_FINAL) {
            v4->state++;
        }
        break;
    case 5:
        CTRDG_ReadAgbFlash(0, 0, v1, sizeof(v1));
        v4->state++;
        break;
    case 6:
        v0 = GBACart_WriteNextSector();

        if (v0 == 0) {
            SleepUnlock(SLEEP_TYPE_SAVE_DATA);
            return 12;
        }

        v4->state++;
        break;
    case 7:
        if (GBACart_GetWriteState() == 9) {
            break;
        }

        if (GBACart_GetWriteState() == 11) {
            v4->state++;
        } else {
            v0 = GBACart_GetWriteResult();

            if (v0 == 8) {
                SleepUnlock(SLEEP_TYPE_SAVE_DATA);
                return 12;
            }
        }
        break;
    case 8:
        do {
            saveResult = SaveData_SaveStateMain(migrator->saveData);

            if (saveResult == SAVE_RESULT_CORRUPT) {
                return 12;
            }
        } while (saveResult != SAVE_RESULT_OK);

        GBACart_GetWriteResult();
        SleepLock(SLEEP_TYPE_SAVE_DATA);
        v4->state++;
        break;
    case 9:
        v0 = GBACart_GetWriteResult();

        if (v0 == 8) {
            SleepUnlock(SLEEP_TYPE_SAVE_DATA);
            return 12;
        }

        if (v0 == 0) {
            SleepUnlock(SLEEP_TYPE_SAVE_DATA);
            return 11;
        }
        break;
    }

    return 10;
}

static void GBAMigrator_SaveGame(GBAMigrator *migrator)
{
    enum SaveResult result;
    MigratedPokemon *transferData = SaveData_GetPalParkTransfer(migrator->saveData);

    PalParkTransfer_SaveTransferHistory(transferData, GetGBAPlayerTrainerId());
    ResetLock(RESET_LOCK_SOFT_RESET);

    result = SaveData_Save(migrator->saveData);
    ResetUnlock(RESET_LOCK_SOFT_RESET);
}

static void CopySelectedMonToPalParkTransfer(GBAMigrator *migrator)
{
    int i, boxNum, boxPos;
    u16 species;
    GBABoxPokemon *gbaBoxMon;
    Pokemon mon;
    MigratedPokemon *transfer = SaveData_GetPalParkTransfer(migrator->saveData);
    BoxPokemon *boxMon = Pokemon_GetBoxPokemon(&mon);

    for (i = 0; i < CATCHING_SHOW_MONS; i++) {
        boxPos = migrator->selectedMonData[i].boxPosition;
        boxNum = migrator->selectedMonData[i].boxId;
        gbaBoxMon = &migrator->pokemonStorage->boxes[boxNum][boxPos];

        BoxMonGBAToBoxMon(gbaBoxMon, boxMon);
        BoxMonToTransferData(transfer, boxMon, i);
    }

    species = SPECIES_NONE;

    for (i = 0; i < CATCHING_SHOW_MONS; i++) {
        boxPos = migrator->selectedMonData[i].boxPosition;
        boxNum = migrator->selectedMonData[i].boxId;

        if ((boxPos != -1) && (boxNum != GBA_MAX_PC_BOXES)) {
            GBABoxPokemon_SetData(&(migrator->pokemonStorage->boxes[boxNum][boxPos]), GBA_MON_DATA_SPECIES, (u8 *)&species);
        }
    }
}

static int GBAMigrator_CalcTextX(GBAMigratorTextBox *param0, String *param1, int param2)
{
    int v0, v1;

    if (param2 & 0x1) {
        v0 = Font_CalcStringWidth(FONT_MESSAGE, (const String *)param1, 0);
        v1 = param0->width * 8;
        return (v1 - v0) / 2;
    } else {
        return param0->textX;
    }
}

static void GBAMigrator_DrawTextBox(GBAMigrator *migrator, GBAMigratorTextBox *param1, int param2)
{
    String *v0;
    StringTemplate *v1;
    MessageLoader *msgLoader;
    int v3, v4, v5;
    String *v6;

    if (param1->textSpeed == 0) {
        v5 = TEXT_SPEED_NO_TRANSFER;
    } else {
        v5 = param1->textSpeed;
    }

    if (param1->window->bgConfig == NULL) {
        Window_Add(migrator->bgConfig, param1->window, param1->bgLayer, param1->x, param1->y, param1->width, param1->height, 15, param1->baseTile);
    }

    if (!(param2 & 0x2)) {
        Window_FillTilemap(param1->window, param1->fillColor);
    }

    if (param1->messageEntryID != -1) {
        msgLoader = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_MIGRATE_FROM_GBA, HEAP_ID_MIGRATE_FROM_GBA);

        if (param1->stringTemplate) {
            v1 = param1->stringTemplate;
        } else {
            v1 = StringTemplate_Default(HEAP_ID_MIGRATE_FROM_GBA);
        }

        String_Clear(migrator->messageString);

        v0 = migrator->messageString;
        v6 = MessageLoader_GetNewString(msgLoader, param1->messageEntryID);

        StringTemplate_Format(v1, migrator->messageString, v6);
        String_Free(v6);

        v3 = GBAMigrator_CalcTextX(param1, v0, param2);
        param1->printerID = Text_AddPrinterWithParamsAndColor(param1->window, param1->fontID, v0, v3, param1->textY, v5, param1->textColor, NULL);

        if (param1->stringTemplate == NULL) {
            StringTemplate_Free(v1);
        }

        MessageLoader_Free(msgLoader);
        param1->messageEntryID = -1;
    }

    if (param1->charcodeString) {
        v0 = migrator->tempString;
        String_CopyNumChars(v0, param1->charcodeString, 64);
        v3 = GBAMigrator_CalcTextX(param1, v0, param2);
        param1->printerID = Text_AddPrinterWithParamsAndColor(param1->window, param1->fontID, v0, v3, param1->textY, v5, param1->textColor, NULL);
        param1->charcodeString = NULL;
    }

    if (param1->string) {
        v3 = GBAMigrator_CalcTextX(param1, param1->string, param2);

        param1->printerID = Text_AddPrinterWithParamsAndColor(param1->window, param1->fontID, param1->string, v3, param1->textY, v5, param1->textColor, NULL);
        param1->string = NULL;
    }

    if (!(param2 & 0x4)) {
        Window_CopyToVRAM(param1->window);
    }

    if (param2 & 0x8) {
        if (param2 & 0x10) {
            Window_DrawMessageBoxWithScrollCursor(param1->window, 0, 0x3F0 - (18 + 12), 13);
        } else {
            Window_DrawStandardFrame(param1->window, 0, 0x3F0, 14);
        }
    }
}

static void GBAMigrator_InitTransfers(void)
{
    {
        CharTransferTemplate v0 = {
            .maxTasks = 20,
            .sizeMain = 2048,
            .sizeSub = 2048,
            .heapID = HEAP_ID_MIGRATE_FROM_GBA,
        };

        CharTransfer_Init(&v0);
    }

    PlttTransfer_Init(20, HEAP_ID_MIGRATE_FROM_GBA);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
}

static void GBAMigrator_InitSprites(GBAMigrator *migrator)
{
    int i;

    NNS_G2dInitOamManagerModule();

    RenderOam_Init(0, 126, 0, 32, 0, 126, 0, 32, HEAP_ID_MIGRATE_FROM_GBA);
    migrator->spriteList = SpriteList_InitRendering(80, &migrator->g2dRenderer, HEAP_ID_MIGRATE_FROM_GBA);
    SetSubScreenViewRect(&migrator->g2dRenderer, 0, 256 * FX32_ONE);

    for (i = 0; i < 6; i++) {
        migrator->spriteResourceCollections[i] = SpriteResourceCollection_New(3, i, HEAP_ID_MIGRATE_FROM_GBA);
    }

    migrator->spriteResources[0] = SpriteResourceCollection_AddTiles(migrator->spriteResourceCollections[0], NARC_INDEX_GRAPHIC__MYSTERY, gba_migration_sprites_NCGR_lz, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAP_ID_MIGRATE_FROM_GBA);
    migrator->spriteResources[1] = SpriteResourceCollection_AddPalette(migrator->spriteResourceCollections[1], NARC_INDEX_GRAPHIC__MYSTERY, gba_migration_sprites_NCLR, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 4, HEAP_ID_MIGRATE_FROM_GBA);
    migrator->spriteResources[2] = SpriteResourceCollection_Add(migrator->spriteResourceCollections[2], NARC_INDEX_GRAPHIC__MYSTERY, gba_migration_sprites_cell_NCER_lz, 1, 0, 2, HEAP_ID_MIGRATE_FROM_GBA);
    migrator->spriteResources[3] = SpriteResourceCollection_Add(migrator->spriteResourceCollections[3], NARC_INDEX_GRAPHIC__MYSTERY, gba_migration_sprites_anim_NANR_lz, 1, 0, 3, HEAP_ID_MIGRATE_FROM_GBA);

    SpriteTransfer_RequestChar(migrator->spriteResources[0]);
    SpriteTransfer_RequestPlttWholeRange(migrator->spriteResources[1]);
    Graphics_LoadPalette(NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, PokeIconPalettesFileIndex(), 1, 8 * 0x20, 0, HEAP_ID_MIGRATE_FROM_GBA);
}

static void GBAMigrator_InitSpriteResources(GBAMigrator *migrator)
{
    SpriteResourcesHeader_Init(&migrator->spriteResourcesHeader, 0, 0, 0, 0, -1, -1, 0, 0, migrator->spriteResourceCollections[0], migrator->spriteResourceCollections[1], migrator->spriteResourceCollections[2], migrator->spriteResourceCollections[3], NULL, NULL);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void GBAMigrator_SetSpriteTemplate(AffineSpriteListTemplate *param0, GBAMigrator *migrator, SpriteResourcesHeader *param2, int param3)
{
    param0->list = migrator->spriteList;
    param0->resourceData = &migrator->spriteResourcesHeader;
    param0->position.z = 0;
    param0->affineScale.x = FX32_ONE;
    param0->affineScale.y = FX32_ONE;
    param0->affineScale.z = FX32_ONE;
    param0->affineZRotation = 0;
    param0->priority = 20;
    param0->vramType = param3;
    param0->heapID = HEAP_ID_MIGRATE_FROM_GBA;
}

static int GetGBABoxMonSpeciesInBox(GBAMigrator *migrator, int boxId, int boxPosition)
{
    return GBABoxPokemon_GetData(&(migrator->pokemonStorage->boxes[boxId][boxPosition]), GBA_MON_DATA_SPECIES, NULL);
}

static int IsGBABoxMonEggInBox(GBAMigrator *migrator, int boxId, int boxPosition)
{
    return GBABoxPokemon_GetData(&(migrator->pokemonStorage->boxes[boxId][boxPosition]), GBA_MON_DATA_IS_EGG, NULL);
}

static int GetGBABoxMonPersonalityInBox(GBAMigrator *migrator, int boxId, int boxPosition)
{
    return GBABoxPokemon_GetData(&(migrator->pokemonStorage->boxes[boxId][boxPosition]), GBA_MON_DATA_PERSONALITY, NULL);
}

static void GBAMigrator_SetTouchRect(TouchScreenRect *rect, int param1, int param2, int param3, int param4)
{
    rect->rect.top = param2 - param4 / 2;
    rect->rect.left = param1 - param3 / 2;
    rect->rect.bottom = param2 + param4 / 2;
    rect->rect.right = param1 + param3 / 2;
}

static void *GBAMigrator_LoadCharacterData(u32 narcID, u32 memberIndex, NNSG2dCharacterData **param2, enum HeapID heapID)
{
    void *v0 = Heap_AllocAtEnd(heapID, 4096);

    if (v0 != NULL) {
        NARC_ReadWholeMemberByIndexPair(v0, narcID, memberIndex);

        if (NNS_G2dGetUnpackedBGCharacterData(v0, param2) == 0) {
            Heap_Free(v0);
            return NULL;
        }
    }

    return v0;
}

static void GBAMigrator_ReadCharacterData(u32 memberIndex, NNSG2dCharacterData **param1, void *param2, NARC *param3)
{
    NARC_ReadWholeMember(param3, memberIndex, param2);
    NNS_G2dGetUnpackedBGCharacterData(param2, param1);
}

#define NUM_UNOWN_FORMS 28

#define GET_UNOWN_LETTER_FROM_PERSONALITY(personality) ((                                          \
                                                            (((personality) & 0x03000000) >> 18)   \
                                                            | (((personality) & 0x00030000) >> 12) \
                                                            | (((personality) & 0x00000300) >> 6)  \
                                                            | (((personality) & 0x00000003) >> 0)) \
    % NUM_UNOWN_FORMS)

static u8 GetSpeciesGBAForm(int speciesNDS, u32 personality, int gbaVersion)
{
    u8 form = 0;

    switch (speciesNDS) {
    case SPECIES_UNOWN:
        form = GET_UNOWN_LETTER_FROM_PERSONALITY(personality);
        break;
    case SPECIES_DEOXYS:
        switch (gbaVersion) {
        default:
        case VERSION_RUBY:
        case VERSION_SAPPHIRE:
            form = DEOXYS_FORM_NORMAL;
            break;
        case VERSION_FIRERED:
            form = DEOXYS_FORM_ATTACK;
            break;
        case VERSION_LEAFGREEN:
            form = DEOXYS_FORM_DEFENSE;
            break;
        case VERSION_EMERALD:
            form = DEOXYS_FORM_SPEED;
            break;
        }

        break;
    }

    return form;
}

static void GBAMigrator_LoadMonIcon(int species, int isEgg, u32 personality, int gbaVersion, int param4, Sprite *iconSprite)
{
    u8 *v0;
    u8 form;
    NNSG2dCharacterData *v2;

    species = GBAPokemon_ConvertSpeciesToDS(species);

    form = GetSpeciesGBAForm(species, personality, gbaVersion);
    v0 = GBAMigrator_LoadCharacterData(NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, PokeIconSpriteIndex(species, isEgg, form), &v2, HEAP_ID_MIGRATE_FROM_GBA);

    DC_FlushRange(v2->pRawData, (4 * 4) * 0x20);
    GX_LoadOBJ(v2->pRawData, (0x64 + param4 * (4 * 4)) * 0x20, (4 * 4) * 0x20);

    Sprite_SetExplicitPalette(iconSprite, PokeIconPaletteIndex(species, form, isEgg) + 8);
    Heap_Free(v0);
}

// speciesGBA is reused to store NDS species
static void GBAMigrator_LoadMonIconData(int speciesGBA, int isEgg, int form, int param3, Sprite *monIconSprite, void *param5, NARC *param6)
{
    u32 spriteIndex;
    NNSG2dCharacterData *v1;
    GBAMigratorMonSprite *v2 = sGBAMigratorMonSprites + param3;

    if (monIconSprite != NULL) {
        if (IsGBASpeciesInvalid(speciesGBA) == FALSE) {
            speciesGBA = GBAPokemon_ConvertSpeciesToDS(speciesGBA);
        } else {
            speciesGBA = SPECIES_NONE;
        }

        spriteIndex = PokeIconSpriteIndex(speciesGBA, isEgg, form);

        GBAMigrator_ReadCharacterData(spriteIndex, &v1, param5, param6);
        MI_CpuCopyFast(v1->pRawData, v2->rawData, (4 * 4) * 0x20);

        v2->charOffset = (0x64 + param3 * (4 * 4)) * 0x20;
        v2->iconSprite = monIconSprite;
        v2->paletteIndex = PokeIconPaletteIndex(speciesGBA, form, isEgg) + 8;
    } else {
        v2->iconSprite = NULL;
    }
}

static void GBAMigrator_FlushMonIcons(void)
{
    int i;
    GBAMigratorMonSprite *v1 = sGBAMigratorMonSprites;

    for (i = 0; i < GBA_MAX_MONS_PER_BOX; i++, v1++) {
        if (v1->iconSprite) {
            DC_FlushRange(v1->rawData, (4 * 4) * 0x20);
            GX_LoadOBJ(v1->rawData, v1->charOffset, (4 * 4) * 0x20);
            Sprite_SetExplicitPalette(v1->iconSprite, v1->paletteIndex);
        }
    }
}

static void GBAMigrator_LoadBoxSprites(GBAMigrator *migrator)
{
    int i, speciesGBA, isEgg, gbaVersion, form;
    u32 personality;
    void *v6;
    NARC *v7 = NARC_ctor(NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, HEAP_ID_MIGRATE_FROM_GBA);
    v6 = Heap_AllocAtEnd(HEAP_ID_MIGRATE_FROM_GBA, 4096);

    for (i = 0; i < GBA_MAX_MONS_PER_BOX; i++) {
        if (GBABoxPokemon_GetData(&(migrator->pokemonStorage->boxes[migrator->currentBox][i]), GBA_MON_DATA_SANITY_HAS_SPECIES, NULL)) {
            speciesGBA = GetGBABoxMonSpeciesInBox(migrator, migrator->currentBox, i);
            isEgg = IsGBABoxMonEggInBox(migrator, migrator->currentBox, i);
            personality = GetGBABoxMonPersonalityInBox(migrator, migrator->currentBox, i);
            gbaVersion = gSystem.gbaCartridgeVersion;
            form = GetSpeciesGBAForm(GBAPokemon_ConvertSpeciesToDS(speciesGBA), personality, gbaVersion);

            GBAMigrator_LoadMonIconData(speciesGBA, isEgg, form, i, migrator->boxMonSprites[i].monIconSprite, v6, v7);
            Sprite_SetDrawFlag(migrator->boxMonSprites[i].monIconSprite, TRUE);

            if (GBABoxPokemon_GetData(&(migrator->pokemonStorage->boxes[migrator->currentBox][i]), GBA_MON_DATA_HELD_ITEM, NULL)) {
                Sprite_SetDrawFlag(migrator->boxMonSprites[i].heldItemSprite, TRUE);
            } else {
                Sprite_SetDrawFlag(migrator->boxMonSprites[i].heldItemSprite, FALSE);
            }
        } else {
            GBAMigrator_LoadMonIconData(speciesGBA, isEgg, form, i, NULL, v6, v7);
            Sprite_SetDrawFlag(migrator->boxMonSprites[i].monIconSprite, FALSE);
            Sprite_SetDrawFlag(migrator->boxMonSprites[i].heldItemSprite, FALSE);
        }
    }

    Heap_Free(v6);
    NARC_dtor(v7);

    migrator->flushMonIcons = GBAMigrator_FlushMonIcons;

    GBAMigrator_ShowBoxName(migrator, migrator->currentBox);
    GBAMigrator_UpdateSelectionSprites(migrator);
}

static void InitBoxPokemonSprites(GBAMigrator *migrator)
{
    int count, col, row;
    AffineSpriteListTemplate v3;

    GBAMigrator_SetSpriteTemplate(&v3, migrator, &migrator->spriteResourcesHeader, NNS_G2D_VRAM_TYPE_2DMAIN);

    count = 0;

    for (row = 0; row < GBA_MAX_PC_ROWS; row++) {
        for (col = 0; col < GBA_MAX_PC_COLS; col++) {
            GBAMigrator_SetTouchRect(&migrator->touchScreenRects[count], col * 40 + 28, row * 24 + 40, 28, 28);

            v3.position.x = FX32_ONE * (col * 40 + 28);
            v3.position.y = FX32_ONE * (row * 24 + 40);

            if (migrator->boxMonSprites[count].monIconSprite == NULL) {
                migrator->boxMonSprites[count].monIconSprite = SpriteList_AddAffine(&v3);
            }

            Sprite_SetAnimateFlag(migrator->boxMonSprites[count].monIconSprite, 1);
            Sprite_SetAnim(migrator->boxMonSprites[count].monIconSprite, 10 + count);
            Sprite_SetExplicitPriority(migrator->boxMonSprites[count].monIconSprite, 1);
            Sprite_SetDrawFlag(migrator->boxMonSprites[count].monIconSprite, TRUE);
            Sprite_SetPriority(migrator->boxMonSprites[count].monIconSprite, 100 + count);

            v3.position.x += FX32_ONE * 6;
            v3.position.y += FX32_ONE * 12;

            if (migrator->boxMonSprites[count].heldItemSprite == NULL) {
                migrator->boxMonSprites[count].heldItemSprite = SpriteList_AddAffine(&v3);
            }

            Sprite_SetAnimateFlag(migrator->boxMonSprites[count].heldItemSprite, 1);
            Sprite_SetAnim(migrator->boxMonSprites[count].heldItemSprite, 40);
            Sprite_SetExplicitPriority(migrator->boxMonSprites[count].heldItemSprite, 1);
            Sprite_SetDrawFlag(migrator->boxMonSprites[count].heldItemSprite, FALSE);
            Sprite_SetPriority(migrator->boxMonSprites[count].heldItemSprite, 0 + count);

            count++;

            if (count == GBA_MAX_MONS_PER_BOX) {
                return;
            }
        }
    }
}

static Sprite *GBAMigrator_AddSprite(GBAMigrator *migrator, int param1, int param2, int param3, int param4)
{
    AffineSpriteListTemplate v0;
    Sprite *v1;

    GBAMigrator_SetSpriteTemplate(&v0, migrator, &migrator->spriteResourcesHeader, NNS_G2D_VRAM_TYPE_2DMAIN);

    v0.position.x = FX32_ONE * param1;
    v0.position.y = FX32_ONE * param2;
    v0.priority = 10;

    v1 = SpriteList_AddAffine(&v0);

    Sprite_SetAnimateFlag(v1, 1);
    Sprite_SetAnim(v1, param3);
    Sprite_SetExplicitPriority(v1, 1);
    Sprite_SetDrawFlag(v1, param4);

    return v1;
}

static void GBAMigrator_InitBoxScreen(GBAMigrator *migrator)
{
    int i;

    GBAMigrator_SetTouchRect(&migrator->touchScreenRects[(GBA_MAX_MONS_PER_BOX + 0)], 228, 176, 50, 32);
    migrator->confirmSprites[0] = GBAMigrator_AddSprite(migrator, 228, 176, 6, 1);

    GBAMigrator_SetTouchRect(&migrator->touchScreenRects[(GBA_MAX_MONS_PER_BOX + 2)], 176, 176, 32, 32);
    migrator->nextBoxSprites[0] = GBAMigrator_AddSprite(migrator, 176, 176, 3, 1);

    GBAMigrator_SetTouchRect(&migrator->touchScreenRects[(GBA_MAX_MONS_PER_BOX + 1)], 24, 176, 32, 32);
    migrator->prevBoxSprites[0] = GBAMigrator_AddSprite(migrator, 24, 176, 0, 1);
    migrator->touchScreenRects[(GBA_MAX_MONS_PER_BOX + 3)].rect.top = 0xff;

    for (i = 0; i < CATCHING_SHOW_MONS; i++) {
        migrator->selectedMonData[i].selectionSprite = GBAMigrator_AddSprite(migrator, 36 * i, 64, 9, 0);
        migrator->selectedMonData[i].boxPosition = -1;
        migrator->selectedMonData[i].boxId = GBA_MAX_PC_BOXES;
    }

    migrator->selectedCount = 0;
}

static BOOL BoxMonGBAIsEgg(GBAMigrator *migrator, int boxPosition)
{
    GBABoxPokemon *gbaBoxMon = &migrator->pokemonStorage->boxes[migrator->currentBox][boxPosition];

    if (GBABoxPokemon_GetData(gbaBoxMon, GBA_MON_DATA_SPECIES_OR_EGG, NULL) == GBA_SPECIES_EGG) {
        return TRUE;
    }

    return FALSE;
}

static BOOL BoxMonGBAHasHM(GBAMigrator *migrator, int boxPosition)
{
    int i, j, move;
    GBABoxPokemon *boxMon = &migrator->pokemonStorage->boxes[migrator->currentBox][boxPosition];

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        move = GBABoxPokemon_GetData(boxMon, GBA_MON_DATA_MOVE1 + i, NULL);

        for (j = 0; j < sizeof(sGBAHMMoves) / sizeof(int); j++) {
            if (sGBAHMMoves[j] == move) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

u16 sInvalidGBAItems[] = {
    GBA_ITEM_SAFARI_BALL,
    GBA_ITEM_034,
    GBA_ITEM_035,
    GBA_ITEM_036,
    GBA_ITEM_037,
    GBA_ITEM_038,
    GBA_ITEM_039,
    GBA_ITEM_03A,
    GBA_ITEM_03B,
    GBA_ITEM_03C,
    GBA_ITEM_03D,
    GBA_ITEM_03E,
    GBA_ITEM_048,
    GBA_ITEM_052,
    GBA_ITEM_057,
    GBA_ITEM_058,
    GBA_ITEM_059,
    GBA_ITEM_05A,
    GBA_ITEM_05B,
    GBA_ITEM_05C,
    GBA_ITEM_063,
    GBA_ITEM_064,
    GBA_ITEM_065,
    GBA_ITEM_066,
    GBA_ITEM_069,
    GBA_ITEM_070,
    GBA_ITEM_071,
    GBA_ITEM_072,
    GBA_ITEM_073,
    GBA_ITEM_074,
    GBA_ITEM_075,
    GBA_ITEM_076,
    GBA_ITEM_077,
    GBA_ITEM_078,
    GBA_ITEM_ORANGE_MAIL,
    GBA_ITEM_HARBOR_MAIL,
    GBA_ITEM_GLITTER_MAIL,
    GBA_ITEM_MECH_MAIL,
    GBA_ITEM_WOOD_MAIL,
    GBA_ITEM_WAVE_MAIL,
    GBA_ITEM_BEAD_MAIL,
    GBA_ITEM_SHADOW_MAIL,
    GBA_ITEM_TROPIC_MAIL,
    GBA_ITEM_DREAM_MAIL,
    GBA_ITEM_FAB_MAIL,
    GBA_ITEM_RETRO_MAIL,
    GBA_ITEM_UNUSED_BERRY_1,
    GBA_ITEM_UNUSED_BERRY_2,
    GBA_ITEM_UNUSED_BERRY_3,
    GBA_ITEM_0E2,
    GBA_ITEM_0E3,
    GBA_ITEM_0E4,
    GBA_ITEM_0E5,
    GBA_ITEM_0E6,
    GBA_ITEM_0E7,
    GBA_ITEM_0E8,
    GBA_ITEM_0E9,
    GBA_ITEM_0EA,
    GBA_ITEM_0EB,
    GBA_ITEM_0EC,
    GBA_ITEM_0ED,
    GBA_ITEM_0EE,
    GBA_ITEM_0EF,
    GBA_ITEM_0F0,
    GBA_ITEM_0F1,
    GBA_ITEM_0F2,
    GBA_ITEM_0F3,
    GBA_ITEM_0F4,
    GBA_ITEM_0F5,
    GBA_ITEM_0F6,
    GBA_ITEM_0F7,
    GBA_ITEM_0F8,
    GBA_ITEM_0F9,
    GBA_ITEM_0FA,
    GBA_ITEM_0FB,
    GBA_ITEM_0FC,
    GBA_ITEM_0FD,
    GBA_ITEM_MACH_BIKE,
    GBA_ITEM_COIN_CASE,
    GBA_ITEM_ITEMFINDER,
    GBA_ITEM_OLD_ROD,
    GBA_ITEM_GOOD_ROD,
    GBA_ITEM_SUPER_ROD,
    GBA_ITEM_SS_TICKET,
    GBA_ITEM_CONTEST_PASS,
    GBA_ITEM_10B,
    GBA_ITEM_WAILMER_PAIL,
    GBA_ITEM_DEVON_GOODS,
    GBA_ITEM_SOOT_SACK,
    GBA_ITEM_BASEMENT_KEY,
    GBA_ITEM_ACRO_BIKE,
    GBA_ITEM_POKEBLOCK_CASE,
    GBA_ITEM_LETTER,
    GBA_ITEM_EON_TICKET,
    GBA_ITEM_RED_ORB,
    GBA_ITEM_BLUE_ORB,
    GBA_ITEM_SCANNER,
    GBA_ITEM_GO_GOGGLES,
    GBA_ITEM_METEORITE,
    GBA_ITEM_ROOM_1_KEY,
    GBA_ITEM_ROOM_2_KEY,
    GBA_ITEM_ROOM_4_KEY,
    GBA_ITEM_ROOM_6_KEY,
    GBA_ITEM_STORAGE_KEY,
    GBA_ITEM_ROOT_FOSSIL,
    GBA_ITEM_CLAW_FOSSIL,
    GBA_ITEM_DEVON_SCOPE,
    GBA_ITEM_HM01,
    GBA_ITEM_HM02,
    GBA_ITEM_HM03,
    GBA_ITEM_HM04,
    GBA_ITEM_HM05,
    GBA_ITEM_HM06,
    GBA_ITEM_HM07,
    GBA_ITEM_HM08,
    GBA_ITEM_15B,
    GBA_ITEM_15C,
    GBA_ITEM_OAKS_PARCEL,
    GBA_ITEM_POKE_FLUTE,
    GBA_ITEM_SECRET_KEY,
    GBA_ITEM_BIKE_VOUCHER,
    GBA_ITEM_GOLD_TEETH,
    GBA_ITEM_OLD_AMBER,
    GBA_ITEM_CARD_KEY,
    GBA_ITEM_LIFT_KEY,
    GBA_ITEM_HELIX_FOSSIL,
    GBA_ITEM_DOME_FOSSIL,
    GBA_ITEM_SILPH_SCOPE,
    GBA_ITEM_BICYCLE,
    GBA_ITEM_TOWN_MAP,
    GBA_ITEM_VS_SEEKER,
    GBA_ITEM_FAME_CHECKER,
    GBA_ITEM_TM_CASE,
    GBA_ITEM_BERRY_POUCH,
    GBA_ITEM_TEACHY_TV,
    GBA_ITEM_TRI_PASS,
    GBA_ITEM_RAINBOW_PASS,
    GBA_ITEM_TEA,
    GBA_ITEM_MYSTIC_TICKET,
    GBA_ITEM_AURORA_TICKET,
    GBA_ITEM_POWDER_JAR,
    GBA_ITEM_RUBY,
    GBA_ITEM_SAPPHIRE,
    GBA_ITEM_MAGMA_EMBLEM,
    GBA_ITEM_OLD_SEA_MAP,
    ITEM_NONE
};

static BOOL BoxMonGBAHasInvalidItem(GBAMigrator *migrator, int boxPosition)
{
    GBABoxPokemon *gbaBoxMon = &migrator->pokemonStorage->boxes[migrator->currentBox][boxPosition];
    int item = GBABoxPokemon_GetData(gbaBoxMon, GBA_MON_DATA_HELD_ITEM, NULL);
    int i;

    for (i = 0; sInvalidGBAItems[i] != ITEM_NONE; i++) {
        if (item == sInvalidGBAItems[i]) {
            return TRUE;
        }
    }

    return FALSE;
}

static BOOL IsBoxMonGBAInvalidSpecies(GBAMigrator *migrator, int boxPosition)
{
    GBABoxPokemon *gbaBoxMon = &migrator->pokemonStorage->boxes[migrator->currentBox][boxPosition];
    int species = GBABoxPokemon_GetData(gbaBoxMon, GBA_MON_DATA_SPECIES, NULL);

    return IsGBASpeciesInvalid(species);
}

static int GBAMigrator_TrySelectGBABoxMon(GBAMigrator *migrator, int boxPosition)
{
    int i, v1;

    if (migrator->boxMonSprites[boxPosition].monIconSprite != NULL
        && (Sprite_GetDrawFlag(migrator->boxMonSprites[boxPosition].monIconSprite) == FALSE)) {
        return GBA_MON_STATE_EMPTY_SLOT;
    }

    for (v1 = -1, i = 0; v1 == -1 && i < CATCHING_SHOW_MONS; i++) {
        if ((migrator->selectedMonData[i].boxId == migrator->currentBox) && (migrator->selectedMonData[i].boxPosition == boxPosition)) {
            v1 = i;
        }
    }

    if (BoxMonGBAIsEgg(migrator, boxPosition) == TRUE) {
        return GBA_MON_STATE_IS_EGG;
    }

    if (BoxMonGBAHasHM(migrator, boxPosition) == TRUE) {
        return GBA_MON_STATE_HAS_HM;
    }

    if (BoxMonGBAHasInvalidItem(migrator, boxPosition) == TRUE) {
        return GBA_MON_STATE_HAS_INVALID_ITEM;
    }

    if (IsBoxMonGBAInvalidSpecies(migrator, boxPosition) == TRUE) {
        return GBA_MON_STATE_IS_INVALID_SPECIES;
    }

    if (v1 == -1) {
        const VecFx32 *v2;
        VecFx32 v3;

        if (migrator->selectedCount == CATCHING_SHOW_MONS) {
            return GBA_MON_STATE_NONE;
        }

        for (i = 0; i < CATCHING_SHOW_MONS; i++) {
            if (migrator->selectedMonData[i].boxPosition == -1) {
                v2 = Sprite_GetPosition(migrator->boxMonSprites[boxPosition].monIconSprite);
                Sprite_SetPosition(migrator->selectedMonData[i].selectionSprite, v2);
                v2 = Sprite_GetPosition(migrator->selectedMonData[i].selectionSprite);

                v3 = *v2;
                v3.x -= FX32_ONE * 8;
                v3.y -= FX32_ONE * 4;

                Sprite_SetPosition(migrator->selectedMonData[i].selectionSprite, &v3);
                Sprite_SetDrawFlag(migrator->selectedMonData[i].selectionSprite, TRUE);

                migrator->selectedMonData[i].boxPosition = boxPosition;
                migrator->selectedMonData[i].boxId = migrator->currentBox;
                migrator->selectedCount++;

                return GBA_MON_STATE_SELECTED;
            }
        }
    } else {
        Sprite_SetDrawFlag(migrator->selectedMonData[v1].selectionSprite, FALSE);

        migrator->selectedMonData[v1].boxPosition = -1;
        migrator->selectedCount--;

        return GBA_MON_STATE_DESELECTED;
    }

    return GBA_MON_STATE_NONE;
}

static void GBAMigrator_UpdateSelectionSprites(GBAMigrator *migrator)
{
    int i;

    for (i = 0; i < CATCHING_SHOW_MONS; i++) {
        if ((migrator->selectedMonData[i].boxPosition != -1) && (migrator->selectedMonData[i].boxId == migrator->currentBox)) {
            Sprite_SetDrawFlag(migrator->selectedMonData[i].selectionSprite, TRUE);
        } else {
            Sprite_SetDrawFlag(migrator->selectedMonData[i].selectionSprite, FALSE);
        }
    }
}

static void GBAMigrator_ShowBoxName(GBAMigrator *migrator, int boxNum)
{
    GBAMigratorTextBox v0;
    u16 boxName[GBA_BOX_NAME_LEN + 1];

    memset(&v0, 0, sizeof(GBAMigratorTextBox));

    v0.window = &migrator->boxNameWindow;
    v0.x = 6;
    v0.y = 21;
    v0.width = 13;
    v0.height = 2;
    v0.messageEntryID = -1;
    v0.textX = 0;
    v0.textY = 0;
    v0.bgLayer = BG_LAYER_MAIN_1;
    v0.fontID = 1;
    v0.textColor = TEXT_COLOR(1, 2, 0);
    v0.baseTile = 0xA0;

    GBA_ConvertStringToDS(migrator->pokemonStorage->boxNames[boxNum], boxName, GBA_BOX_NAME_LEN + 1, GBACart_GetLanguage());
    v0.charcodeString = boxName;
    GBAMigrator_DrawTextBox(migrator, &v0, 0x1);
}

static void GBAMigrator_DrawMarkings(GBAMigrator *migrator, GBABoxPokemon *gbaBoxMon)
{
    u16 *v0 = Bg_GetTilemapBuffer(migrator->bgConfig, BG_LAYER_MAIN_2);
    u8 markings;
    int i;

    if (gbaBoxMon != NULL) {
        markings = GBABoxPokemon_GetData(gbaBoxMon, GBA_MON_DATA_MARKINGS, NULL);
    } else {
        markings = 0;
    }

    for (i = 0; i < 4; i++) {
        if (markings & 1) {
            v0[32 * 3 + 11 + i] = 0x80 + i;
        } else {
            v0[32 * 3 + 11 + i] = 0x60 + i;
        }

        markings >>= 1;
    }

    Bg_CopyTilemapBufferToVRAM(migrator->bgConfig, BG_LAYER_MAIN_2);
}

static void PrintGBABoxMonInfo(GBAMigrator *migrator, GBABoxPokemon *gbaBoxMon)
{
    int species, level;
    int gbaItemID, itemID;
    GBAMigratorTextBox v4;
    MessageLoader *msgLoader;
    u8 gbaNickname[GBA_MON_NAME_LEN + 1];
    u16 dsNickname[MON_NAME_LEN + 1];
    String *string;

    memset(&v4, 0, sizeof(GBAMigratorTextBox));

    v4.window = &migrator->monInfoWindow;
    v4.x = 0;
    v4.y = 0;
    v4.width = 32;
    v4.height = 4;
    v4.bgLayer = BG_LAYER_MAIN_1;
    v4.fontID = 1;
    v4.baseTile = (14 * 2 + 0xA0);
    v4.textColor = TEXT_COLOR(15, 2, 0);
    v4.charcodeString = NULL;

    v4.messageEntryID = MigrateFromGBA_Text_Item;
    v4.textX = 18 * 8;
    v4.textY = 0;

    GBAMigrator_DrawTextBox(migrator, &v4, 0x4);

    v4.messageEntryID = MigrateFromGBA_Text_Level;
    v4.textX = 10 * 8;
    v4.textY = 8;

    GBAMigrator_DrawTextBox(migrator, &v4, 0x4 | 0x2);
    GBAMigrator_DrawMarkings(migrator, gbaBoxMon);

    if (gbaBoxMon == NULL) {
        Window_CopyToVRAM(v4.window);
        return;
    }

    GBABoxPokemon_GetData(gbaBoxMon, GBA_MON_DATA_NICKNAME, gbaNickname);
    GBA_ConvertStringToDS(gbaNickname, dsNickname, GBA_MON_NAME_LEN + 1, GBABoxPokemon_GetData(gbaBoxMon, GBA_MON_DATA_LANGUAGE, NULL));

    v4.charcodeString = dsNickname;
    v4.messageEntryID = -1;
    v4.textX = 1 * 8;
    v4.textY = 0;

    GBAMigrator_DrawTextBox(migrator, &v4, 0x4 | 0x2);

    string = String_Init(64, HEAP_ID_MIGRATE_FROM_GBA);
    msgLoader = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_SPECIES_NAME, HEAP_ID_MIGRATE_FROM_GBA);
    species = GBAPokemon_ConvertSpeciesToDS(GBABoxPokemon_GetData(gbaBoxMon, GBA_MON_DATA_SPECIES, NULL));

    MessageLoader_GetString(msgLoader, species, string);

    v4.string = string;
    v4.messageEntryID = -1;
    v4.textX = 2 * 8;
    v4.textY = 2 * 8;

    GBAMigrator_DrawTextBox(migrator, &v4, 0x4 | 0x2);

    MessageLoader_Free(msgLoader);
    String_Free(string);

    gbaItemID = GBABoxPokemon_GetData(gbaBoxMon, GBA_MON_DATA_HELD_ITEM, NULL);

    if (gbaItemID) {
        itemID = Item_FromGBAID(gbaItemID);
        string = String_Init(64, HEAP_ID_MIGRATE_FROM_GBA);

        Item_LoadName(string, itemID, HEAP_ID_MIGRATE_FROM_GBA);

        v4.string = string;
        v4.messageEntryID = -1;
        v4.textX = 19 * 8;
        v4.textY = 2 * 8;

        GBAMigrator_DrawTextBox(migrator, &v4, 0x4 | 0x2);
        String_Free(string);
    }

    level = GBABoxPokemon_GetLevel(gbaBoxMon);
    string = String_Init(10, HEAP_ID_MIGRATE_FROM_GBA);

    String_FormatInt(string, level, 3, PADDING_MODE_SPACES, CHARSET_MODE_EN);

    v4.string = string;
    v4.messageEntryID = -1;
    v4.textX = 12 * 8 + 4;
    v4.textY = 1 * 8;

    GBAMigrator_DrawTextBox(migrator, &v4, 0x2);

    String_Free(string);
    Sound_PlayPokemonCry(species, 0);
}

static void GBAMigrator_FadeIn(GBAMigrator *migrator, enum FadeType fadeType, int param2, int *state)
{
    StartScreenFade(FADE_BOTH_SCREENS, fadeType, fadeType, COLOR_BLACK, 6, 1, HEAP_ID_MIGRATE_FROM_GBA);

    if (state != NULL) {
        *state = GBA_MIGRATOR_STATE_FADE_OUT_TO_SELECTED_MON;
    }

    migrator->nextState = param2;
}

static void GBAMigrator_FadeOut(GBAMigrator *migrator, enum FadeType fadeType, int param2, int *state)
{
    StartScreenFade(FADE_BOTH_SCREENS, fadeType, fadeType, COLOR_WHITE, 6, 1, HEAP_ID_MIGRATE_FROM_GBA);

    if (state != NULL) {
        *state = GBA_MIGRATOR_STATE_FADE_OUT_TO_SELECTED_MON;
    }

    migrator->nextState = param2;
}

static void GBAMigrator_InitBg(BgConfig *bgConfig)
{
    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D
        };

        SetAllGraphicsModes(&v0);
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = 0,
        };

        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_0, &v1, 0);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_0);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe800,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = 0,
        };

        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_1, &v2, 0);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_1);
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_23,
            .priority = 2,
            .areaOver = 0,
            .mosaic = 0,
        };

        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_2, &v3, 0);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_2);
    }

    {
        BgTemplate v4 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_23,
            .priority = 3,
            .areaOver = 0,
            .mosaic = 0,
        };

        Bg_InitFromTemplate(bgConfig, BG_LAYER_MAIN_3, &v4, 0);
        Bg_ClearTilemap(bgConfig, BG_LAYER_MAIN_3);
    }
}

static void GBAMigrator_InitGraphics(GBAMigrator *migrator)
{
    GXBanks v0 = {
        GX_VRAM_BG_128_A,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_64_E,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_0_B,
        GX_VRAM_TEXPLTT_01_FG
    };

    GXLayers_SetBanks(&v0);
    GBAMigrator_InitBg(migrator->bgConfig);

    gSystem.whichScreenIs3D = DS_SCREEN_SUB;

    GXLayers_SwapDisplay();
    Text_ResetAllPrinters();

    Font_LoadTextPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(15), HEAP_ID_MIGRATE_FROM_GBA);
    Graphics_LoadPalette(NARC_INDEX_GRAPHIC__MYSTERY, gba_migration_bg_tiles_NCLR, 0, 0, 32 * 6, HEAP_ID_MIGRATE_FROM_GBA);
    Graphics_LoadTilesToBgLayer(NARC_INDEX_GRAPHIC__MYSTERY, gba_migration_bg_tiles_NCGR_lz, migrator->bgConfig, 2, 0, 10 * 16 * 0x20, 1, HEAP_ID_MIGRATE_FROM_GBA);
    Font_InitManager(FONT_SUBSCREEN, HEAP_ID_MIGRATE_FROM_GBA);
}

static void GBAMigrator_LoadBoxTilemap(GBAMigrator *migrator)
{
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_GRAPHIC__MYSTERY, gba_migration_box_NSCR_lz, migrator->bgConfig, 2, 0, 32 * 24 * 2, 1, HEAP_ID_MIGRATE_FROM_GBA);
    Bg_ChangeTilemapRectPalette(migrator->bgConfig, 2, 0, 0, 32, 24, sGBAGameRectPalettes[migrator->gbaVersion]);
    Bg_CopyTilemapBufferToVRAM(migrator->bgConfig, 2);
}

static void GBAMigrator_InitTextBoxWindow(GBAMigrator *migrator)
{
    Font_LoadTextPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(14), HEAP_ID_MIGRATE_FROM_GBA);
    LoadStandardWindowGraphics(migrator->bgConfig, BG_LAYER_MAIN_0, 0x3F0, 14, 0, HEAP_ID_MIGRATE_FROM_GBA);
    LoadMessageBoxGraphics(migrator->bgConfig, BG_LAYER_MAIN_0, 0x3F0 - (18 + 12), 13, migrator->messageBoxFrame, HEAP_ID_MIGRATE_FROM_GBA);

    memset(&migrator->textBox, 0, sizeof(GBAMigratorTextBox));

    migrator->textBox.window = &migrator->messageWindow;
    migrator->textBox.x = 2;
    migrator->textBox.y = 1;
    migrator->textBox.width = 27;
    migrator->textBox.height = 4;
    migrator->textBox.bgLayer = BG_LAYER_MAIN_0;
    migrator->textBox.fontID = 1;
    migrator->textBox.baseTile = 0 + 1;
    migrator->textBox.textColor = TEXT_COLOR(1, 2, 15);
    migrator->textBox.fillColor = TEXT_COLOR(15, 2, 15);
    migrator->textBox.charcodeString = NULL;
    migrator->textBox.string = NULL;
}

static void GBAMigrator_InitConfirmScreen(GBAMigrator *migrator)
{
    int i, species, isEgg, gbaVersion;
    u32 personality;
    AffineSpriteListTemplate v5;

    for (i = 0; i < GBA_MAX_MONS_PER_BOX; i++) {
        Sprite_SetDrawFlag(migrator->boxMonSprites[i].monIconSprite, FALSE);
        Sprite_SetDrawFlag(migrator->boxMonSprites[i].heldItemSprite, FALSE);
    }

    for (i = 0; i < CATCHING_SHOW_MONS; i++) {
        Sprite_SetDrawFlag(migrator->selectedMonData[i].selectionSprite, FALSE);
    }

    Sprite_SetDrawFlag(migrator->confirmSprites[0], FALSE);
    Sprite_SetDrawFlag(migrator->prevBoxSprites[0], FALSE);
    Sprite_SetDrawFlag(migrator->nextBoxSprites[0], FALSE);

    GBAMigrator_SetSpriteTemplate(&v5, migrator, &migrator->spriteResourcesHeader, NNS_G2D_VRAM_TYPE_2DMAIN);

    for (i = 0; i < CATCHING_SHOW_MONS; i++) {
        v5.position.x = FX32_ONE * (i * 40 + 28);
        v5.position.y = FX32_ONE * 142;

        migrator->selectedMonIcons[i] = SpriteList_AddAffine(&v5);

        Sprite_SetAnimateFlag(migrator->selectedMonIcons[i], 1);
        Sprite_SetAnim(migrator->selectedMonIcons[i], 10 + i);
        Sprite_SetExplicitPriority(migrator->selectedMonIcons[i], 1);
        Sprite_SetDrawFlag(migrator->selectedMonIcons[i], TRUE);

        species = GetGBABoxMonSpeciesInBox(migrator, migrator->selectedMonData[i].boxId, migrator->selectedMonData[i].boxPosition);
        isEgg = IsGBABoxMonEggInBox(migrator, migrator->selectedMonData[i].boxId, migrator->selectedMonData[i].boxPosition);
        personality = GetGBABoxMonPersonalityInBox(migrator, migrator->selectedMonData[i].boxId, migrator->selectedMonData[i].boxPosition);
        gbaVersion = gSystem.gbaCartridgeVersion;

        GBAMigrator_LoadMonIcon(species, isEgg, personality, gbaVersion, i, migrator->selectedMonIcons[i]);
    }

    Graphics_LoadTilemapToBgLayer(NARC_INDEX_GRAPHIC__MYSTERY, gba_migration_confirm_NSCR_lz, migrator->bgConfig, 2, 0, 32 * 24 * 2, 1, HEAP_ID_MIGRATE_FROM_GBA);
    Bg_ChangeTilemapRectPalette(migrator->bgConfig, BG_LAYER_MAIN_2, 0, 0, 32, 24, sGBAGameRectPalettes[migrator->gbaVersion]);
    Bg_CopyTilemapBufferToVRAM(migrator->bgConfig, BG_LAYER_MAIN_2);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    Font_LoadTextPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(14), HEAP_ID_MIGRATE_FROM_GBA);
    LoadStandardWindowGraphics(migrator->bgConfig, BG_LAYER_MAIN_0, 0x3F0, 14, 0, HEAP_ID_MIGRATE_FROM_GBA);
    LoadMessageBoxGraphics(migrator->bgConfig, BG_LAYER_MAIN_0, 0x3F0 - (18 + 12), 13, migrator->messageBoxFrame, HEAP_ID_MIGRATE_FROM_GBA);

    GBAMigrator_InitTextBoxWindow(migrator);
    migrator->textBox.messageEntryID = MigrateFromGBA_Text_SixChosenWillMigrate;
    GBAMigrator_DrawTextBox(migrator, &migrator->textBox, 0x8 | 0x10);
}

static void GBAMigrator_RemoveWindow(Window *window)
{
    if (window->bgConfig != NULL) {
        Window_EraseMessageBox(window, 0);
        Window_ClearAndCopyToVRAM(window);
        Window_Remove(window);
    }
}

static void ResetChosenPokemonData(GBAMigrator *migrator)
{
    int i;

    for (i = 0; i < CATCHING_SHOW_MONS; i++) {
        Sprite_Delete(migrator->selectedMonIcons[i]);
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GBAMigrator_RemoveWindow(&migrator->messageWindow);

    Sprite_SetDrawFlag(migrator->confirmSprites[0], TRUE);
    Sprite_SetDrawFlag(migrator->prevBoxSprites[0], TRUE);
    Sprite_SetDrawFlag(migrator->nextBoxSprites[0], TRUE);

    for (i = 0; i < CATCHING_SHOW_MONS; i++) {
        migrator->selectedMonData[i].boxPosition = -1;
        migrator->selectedMonData[i].boxId = GBA_MAX_PC_BOXES;
    }

    migrator->selectedCount = 0;
}

static void GBAMigrator_FreeUi(GBAMigrator *migrator)
{
    int i;

    SetVBlankCallback(NULL, NULL);

    for (i = 0; i < GBA_MAX_MONS_PER_BOX; i++) {
        if (migrator->boxMonSprites[i].monIconSprite != NULL) {
            Sprite_Delete(migrator->boxMonSprites[i].monIconSprite);
        }

        if (migrator->boxMonSprites[i].heldItemSprite != NULL) {
            Sprite_Delete(migrator->boxMonSprites[i].heldItemSprite);
        }
    }

    for (i = 0; i < CATCHING_SHOW_MONS; i++) {
        if (migrator->selectedMonData[i].selectionSprite) {
            Sprite_Delete(migrator->selectedMonData[i].selectionSprite);
        }
    }

    if (migrator->confirmSprites[0]) {
        Sprite_Delete(migrator->confirmSprites[0]);
    }

    if (migrator->prevBoxSprites[0]) {
        Sprite_Delete(migrator->prevBoxSprites[0]);
    }

    if (migrator->nextBoxSprites[0]) {
        Sprite_Delete(migrator->nextBoxSprites[0]);
    }

    GBAMigrator_RemoveWindow(&migrator->boxNameWindow);
    GBAMigrator_RemoveWindow(&migrator->monInfoWindow);
    GBAMigrator_RemoveWindow(&migrator->messageWindow);

    Font_Free(FONT_SUBSCREEN);
    SpriteTransfer_ResetCharTransfer(migrator->spriteResources[0]);
    SpriteTransfer_ResetPlttTransfer(migrator->spriteResources[1]);

    for (i = 0; i < 6; i++) {
        SpriteResourceCollection_Delete(migrator->spriteResourceCollections[i]);
    }

    SpriteList_Delete(migrator->spriteList);
    migrator->spriteList = NULL;

    RenderOam_Free();
    CharTransfer_Free();
    PlttTransfer_Free();

    YesNoTouchMenu_Free(migrator->yesNoTouchMenu);
    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;
    GXLayers_SwapDisplay();

    Bg_FreeTilemapBuffer(migrator->bgConfig, BG_LAYER_MAIN_0);
    Bg_FreeTilemapBuffer(migrator->bgConfig, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(migrator->bgConfig, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(migrator->bgConfig, BG_LAYER_MAIN_3);
}

static void GBAMigrator_InitYesNoMenu(GBAMigrator *migrator)
{
    YesNoTouchMenuParams v0;

    v0.bgConfig = migrator->bgConfig;
    v0.bgLayer = BG_LAYER_MAIN_0;
    v0.baseTile = 512;
    v0.palette = 8;
    v0.tilemapLeft = 25;
    v0.tilemapTop = 7;

    YesNoTouchMenu_InitWithParams(migrator->yesNoTouchMenu, &v0);
}

static void GBAMigrator_ShowConfirmMessage(GBAMigrator *migrator)
{
    GBAMigratorTextBox v0;
    StringTemplate *strTemplate;
    String *string;
    u16 playerName[GBA_PLAYER_NAME_LEN + 1];

    GBA_ConvertStringToDS(GetGBAPlayerName(), playerName, GBA_PLAYER_NAME_LEN + 1, GBACart_GetLanguage());

    strTemplate = StringTemplate_Default(HEAP_ID_MIGRATE_FROM_GBA);
    string = String_Init(GBA_PLAYER_NAME_LEN + 1, HEAP_ID_MIGRATE_FROM_GBA);

    String_CopyChars(string, playerName);
    StringTemplate_SetString(strTemplate, 1, string, 0, 1, GAME_LANGUAGE);

    GBAMigrator_InitTextBoxWindow(migrator);

    migrator->textBox.messageEntryID = sMigrateFromGBAGameMessageIDs[migrator->gbaVersion];
    migrator->textBox.stringTemplate = strTemplate;

    GBAMigrator_DrawTextBox(migrator, &migrator->textBox, 0x8 | 0x10);

    String_Free(string);
    StringTemplate_Free(strTemplate);

    GBAMigrator_InitYesNoMenu(migrator);
}

static void GBAMigrator_VBlankCallback(void *param0)
{
    GBAMigrator *migrator = (GBAMigrator *)param0;

    if (migrator->flushMonIcons) {
        migrator->flushMonIcons();
        migrator->flushMonIcons = NULL;
    }

    VramTransfer_Process();
    RenderOam_Transfer();
    Bg_RunScheduledUpdates(migrator->bgConfig);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static int GetCanMigrateStatus(GBAMigrator *migrator)
{
    int timeDiff;
    u32 gbaTrainerId;
    MigratedPokemon *transferData = SaveData_GetPalParkTransfer(migrator->saveData);

    if (IsPalParkTransferMacAddressUnset(transferData) == FALSE) {
        if (MacAddressMatchesLastPalParkTransfer(transferData) == FALSE) {
            return CANNOT_MIGRATE_DIFFERENT_CONSOLE;
        }

        if (RtcOffsetMatchesLastPalParkTransfer(transferData) == FALSE) {
            return CANNOT_MIGRATE_INTERNAL_CLOCK_ALTERED;
        }

        gbaTrainerId = GetGBAPlayerTrainerId();
        timeDiff = PalParkTransfer_GetSecondsSinceLastTransfer(transferData, gbaTrainerId);

        if (timeDiff == 0) {
            timeDiff = (60 * 60 * 24) * 2;
        }

        if (timeDiff < (60 * 60 * 24)) {
            return CANNOT_MIGRATE_WAIT_FOR_FULL_DAY;
        }
    }

    {
        GBABoxPokemon *gbaBoxMon;
        int boxPos, boxNum, count = 0;

        for (boxNum = 0; boxNum < GBA_MAX_PC_BOXES; boxNum++) {
            for (boxPos = 0; boxPos < GBA_MAX_MONS_PER_BOX; boxPos++) {
                gbaBoxMon = &migrator->pokemonStorage->boxes[boxNum][boxPos];

                if (GBABoxPokemon_GetData(gbaBoxMon, GBA_MON_DATA_SANITY_HAS_SPECIES, NULL)) {
                    count++;
                }
            }
        }

        if (count < CATCHING_SHOW_MONS) {
            return CANNOT_MIGRATE_LESS_THAN_6_IN_GBA_BOXES;
        }
    }

    if (GetPalParkTransferMonCount(transferData) != 0) {
        return CANNOT_MIGRATE_ALREADY_STOCKED;
    }

    return CAN_MIGRATE;
}

static BOOL GBAMigrator_WaitCannotMigrateMessage(GBAMigrator *migrator, int canMigrateStatus)
{
    if (migrator->canMigrateStatus != CAN_MIGRATE) {
        GBAMigrator_InitTextBoxWindow(migrator);
        RenderControlFlags_SetSpeedUpOnTouch(TRUE);
        migrator->textBox.messageEntryID = sCannotMigrateMessageIDs[canMigrateStatus];
        migrator->textBox.textSpeed = 1;
        GBAMigrator_DrawTextBox(migrator, &migrator->textBox, 0x8 | 0x10);
        migrator->canMigrateStatus = CAN_MIGRATE;
    } else {
        if (Text_IsPrinterActive(migrator->textBox.printerID) == 0) {
            RenderControlFlags_SetSpeedUpOnTouch(FALSE);
            return TRUE;
        }
    }

    return FALSE;
}

static BOOL GBAMigrator_WaitCannotMigrateMessageYesNo(GBAMigrator *migrator, int cannotMigrateID)
{
    if (migrator->canMigrateStatus != CAN_MIGRATE) {
        GBAMigrator_InitTextBoxWindow(migrator);
        RenderControlFlags_SetSpeedUpOnTouch(TRUE);
        migrator->textBox.messageEntryID = sCannotMigrateMessageIDs[cannotMigrateID];
        migrator->textBox.textSpeed = 1;
        GBAMigrator_DrawTextBox(migrator, &migrator->textBox, 0x8 | 0x10);
        migrator->canMigrateStatus = CAN_MIGRATE;
    } else {
        if (Text_IsPrinterActive(migrator->textBox.printerID) == 0) {
            GBAMigrator_InitYesNoMenu(migrator);
            RenderControlFlags_SetSpeedUpOnTouch(FALSE);
            return TRUE;
        }
    }

    return FALSE;
}

static BOOL GBAMigrator_WaitMessage(GBAMigrator *migrator, int param1)
{
    if (migrator->messageEntryID != -1) {
        GBAMigrator_InitTextBoxWindow(migrator);
        RenderControlFlags_SetSpeedUpOnTouch(TRUE);
        migrator->textBox.messageEntryID = migrator->messageEntryID;
        migrator->textBox.textSpeed = param1;
        GBAMigrator_DrawTextBox(migrator, &migrator->textBox, 0x8 | 0x10);
        migrator->messageEntryID = -1;
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
    } else {
        if (param1) {
            if (Text_IsPrinterActive(migrator->textBox.printerID) == 0) {
                RenderControlFlags_SetSpeedUpOnTouch(FALSE);
                return TRUE;
            }
        } else {
            if (gSystem.touchPressed || gSystem.pressedKeys) {
                RenderControlFlags_SetSpeedUpOnTouch(FALSE);
                Sound_PlayEffect(SE_CONFIRM_sseq_3);
                return TRUE;
            }
        }
    }

    return FALSE;
}

static int GBAMigrator_Init(ApplicationManager *appMan, int *state)
{
    GBAMigrator *migrator;

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_MIGRATE_FROM_GBA, HEAP_SIZE_MIGRATE_FROM_GBA);

    migrator = ApplicationManager_NewData(appMan, sizeof(GBAMigrator), HEAP_ID_MIGRATE_FROM_GBA);
    memset(migrator, 0, sizeof(GBAMigrator));

    migrator->bgConfig = BgConfig_New(HEAP_ID_MIGRATE_FROM_GBA);
    migrator->yesNoTouchMenu = YesNoTouchMenu_New(HEAP_ID_MIGRATE_FROM_GBA);

    SetScreenColorBrightness(DS_SCREEN_MAIN, COLOR_BLACK);
    SetScreenColorBrightness(DS_SCREEN_SUB, COLOR_BLACK);

    migrator->saveData = ((ApplicationArgs *)ApplicationManager_Args(appMan))->saveData;
    migrator->trainerInfo = SaveData_GetTrainerInfo(migrator->saveData);
    migrator->options = SaveData_GetOptions(migrator->saveData);
    migrator->messageBoxFrame = Options_Frame(migrator->options);
    migrator->messageString = String_Init(256, HEAP_ID_MIGRATE_FROM_GBA);
    migrator->tempString = String_Init(256, HEAP_ID_MIGRATE_FROM_GBA);

    Sound_SetSceneAndPlayBGM(SOUND_SCENE_9, SEQ_PRESENT_sseq, 1);

    if (OS_IsTickAvailable() == 0) {
        OS_InitTick();
    }

    MainMenuUtil_UnsetGBACartIRQFunc();
    sGBAMigratorMonSprites = migrator->monSprites;

    return 1;
}

extern int gIgnoreCartridgeForWake;

static int GBAMigrator_Main(ApplicationManager *appMan, int *state)
{
    int boxPos, gbaMonValidity, v2;
    GBAMigrator *migrator = ApplicationManager_Data(appMan);

    CTRDG_IsExisting();

    if ((CTRDG_IsPulledOut() == TRUE) || gIgnoreCartridgeForWake) {
        GBAMigratorSaveState *v4 = &migrator->saveState;

        if ((v4->state == 3) || (v4->state == 4)) {
            SaveData_SaveStateCancel(migrator->saveData);
        }

        FatalErrorScreen_ShowGbaPakError(HEAP_ID_MIGRATE_FROM_GBA);
    }

    migrator->frameCounter++;

    switch (*state) {
    case GBA_MIGRATOR_STATE_0:
        ResetLoadedGBACartInfo();
        migrator->loadInfoResult = GBACart_LoadInfo(&migrator->saveSlot);

        if (migrator->loadInfoResult == 0) {
            migrator->loadSaveResult = GBACart_LoadSave();

            if (migrator->loadSaveResult == 0) {
                migrator->pokemonStorage = GetGBAPokemonStorage();
                migrator->currentBox = migrator->pokemonStorage->currentBox;
            } else {
                migrator->canMigrateStatus = CANNOT_MIGRATE_GBA_PAK_READ_ERROR;
            }
        } else {
            (void)0;
        }

        GBAMigrator_InitGbaVersion(migrator);
        *state = GBA_MIGRATOR_STATE_1;
        break;

    case GBA_MIGRATOR_STATE_1:
        GBAMigrator_InitGraphics(migrator);
        GBAMigrator_InitTransfers();
        GBAMigrator_InitSprites(migrator);
        GBAMigrator_InitSpriteResources(migrator);
        GBAMigrator_InitBoxScreen(migrator);

        SetVBlankCallback(GBAMigrator_VBlankCallback, migrator);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 0);

        if (migrator->canMigrateStatus == CANNOT_MIGRATE_GBA_PAK_READ_ERROR) {
            GBAMigrator_FadeIn(migrator, FADE_TYPE_BRIGHTNESS_IN, 11, state);
        } else {
            *state = GBA_MIGRATOR_STATE_2;
        }
        break;
    case GBA_MIGRATOR_STATE_2:
        GBAMigrator_ShowConfirmMessage(migrator);
        GBAMigrator_FadeIn(migrator, FADE_TYPE_BRIGHTNESS_IN, 3, state);
        break;
    case GBA_MIGRATOR_STATE_3:
        boxPos = YesNoTouchMenu_ProcessInput(migrator->yesNoTouchMenu);

        switch (boxPos) {
        case YES_NO_TOUCH_MENU_YES:
            YesNoTouchMenu_Reset(migrator->yesNoTouchMenu);
            migrator->messageEntryID = MigrateFromGBA_Text_CannotReturnToGBAMigrateToPlatinum;
            *state = GBA_MIGRATOR_STATE_4;
            break;
        case YES_NO_TOUCH_MENU_NO:
            YesNoTouchMenu_Reset(migrator->yesNoTouchMenu);
            GBAMigrator_FadeOut(migrator, FADE_TYPE_BRIGHTNESS_OUT, 24, state);
            break;
        }
        break;
    case GBA_MIGRATOR_STATE_4:
        if (GBAMigrator_WaitMessage(migrator, 1)) {
            GBAMigrator_InitYesNoMenu(migrator);
            *state = GBA_MIGRATOR_STATE_5;
        }
        break;
    case GBA_MIGRATOR_STATE_5:
        boxPos = YesNoTouchMenu_ProcessInput(migrator->yesNoTouchMenu);

        switch (boxPos) {
        case YES_NO_TOUCH_MENU_YES:
            YesNoTouchMenu_Reset(migrator->yesNoTouchMenu);

            migrator->canMigrateStatus = GetCanMigrateStatus(migrator);

            if (migrator->canMigrateStatus != CAN_MIGRATE) {
                if ((migrator->canMigrateStatus == CANNOT_MIGRATE_DIFFERENT_CONSOLE)
                    || (migrator->canMigrateStatus == CANNOT_MIGRATE_INTERNAL_CLOCK_ALTERED)) {
                    *state = GBA_MIGRATOR_STATE_8;
                } else {
                    *state = GBA_MIGRATOR_STATE_11;
                }
            } else {
                migrator->messageEntryID = MigrateFromGBA_Text_PleaseChooseSix;
                *state = GBA_MIGRATOR_STATE_6;
            }
            break;
        case YES_NO_TOUCH_MENU_NO:
            YesNoTouchMenu_Reset(migrator->yesNoTouchMenu);
            GBAMigrator_FadeOut(migrator, FADE_TYPE_BRIGHTNESS_OUT, 24, state);
            break;
        }
        break;
    case GBA_MIGRATOR_STATE_6:
        if (GBAMigrator_WaitMessage(migrator, 1)) {
            *state = GBA_MIGRATOR_STATE_7;
        }
        break;
    case GBA_MIGRATOR_STATE_7:
        if (gSystem.touchPressed || gSystem.pressedKeys) {
            GBAMigrator_FadeIn(migrator, FADE_TYPE_BRIGHTNESS_OUT, 12, state);
        }
        break;
    case GBA_MIGRATOR_STATE_8:
        if (GBAMigrator_WaitCannotMigrateMessageYesNo(migrator, migrator->canMigrateStatus)) {
            *state = GBA_MIGRATOR_STATE_9;
        }
        break;
    case GBA_MIGRATOR_STATE_9:
        boxPos = YesNoTouchMenu_ProcessInput(migrator->yesNoTouchMenu);

        switch (boxPos) {
        case YES_NO_TOUCH_MENU_YES:
            YesNoTouchMenu_Reset(migrator->yesNoTouchMenu);
            migrator->textBox.textSpeed = 0;
            migrator->textBox.messageEntryID = MigrateFromGBA_Text_MakingAdjustments;
            GBAMigrator_DrawTextBox(migrator, &migrator->textBox, 0);
            migrator->saveState.waitDial = Window_AddWaitDial(&migrator->messageWindow, 0x3F0 - (18 + 12));
            *state = GBA_MIGRATOR_STATE_10;
            break;
        case YES_NO_TOUCH_MENU_NO:
            YesNoTouchMenu_Reset(migrator->yesNoTouchMenu);
            GBAMigrator_FadeOut(migrator, FADE_TYPE_BRIGHTNESS_OUT, 24, state);
            break;
        }
        break;
    case GBA_MIGRATOR_STATE_10:
        GBAMigrator_SaveGame(migrator);
        DestroyWaitDial(migrator->saveState.waitDial);
        migrator->canMigrateStatus = CANNOT_MIGRATE_CLOCK_ADJUSTED;
        *state = GBA_MIGRATOR_STATE_11;
        break;
    case GBA_MIGRATOR_STATE_11:
        if (GBAMigrator_WaitCannotMigrateMessage(migrator, migrator->canMigrateStatus)) {
            *state = GBA_MIGRATOR_STATE_22;
        }
        break;
    case GBA_MIGRATOR_STATE_12:
        GBAMigrator_RemoveWindow(&migrator->messageWindow);
        GBAMigrator_LoadBoxTilemap(migrator);
        InitBoxPokemonSprites(migrator);
        GBAMigrator_LoadBoxSprites(migrator);

        SetVBlankCallback(GBAMigrator_VBlankCallback, migrator);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);

        PrintGBABoxMonInfo(migrator, NULL);
        GBAMigrator_FadeIn(migrator, FADE_TYPE_BRIGHTNESS_IN, 13, state);

        break;
    case GBA_MIGRATOR_STATE_13:
        boxPos = TouchScreen_CheckRectanglePressed((const TouchScreenRect *)migrator->touchScreenRects);

        if (boxPos != -1) {
            if (boxPos < GBA_MAX_MONS_PER_BOX) {
                gbaMonValidity = GBAMigrator_TrySelectGBABoxMon(migrator, boxPos);

                if (gbaMonValidity == GBA_MON_STATE_SELECTED) {
                    PrintGBABoxMonInfo(migrator, &(migrator->pokemonStorage->boxes[migrator->currentBox][boxPos]));

                    if (migrator->selectedCount == CATCHING_SHOW_MONS) {
                        migrator->fullSelectionTimer = 45;
                        *state = GBA_MIGRATOR_STATE_WAIT_FOR_FULL_SELECTION_TIMER;
                    }
                } else if (gbaMonValidity == GBA_MON_STATE_DESELECTED) {
                    PrintGBABoxMonInfo(migrator, NULL);
                } else if (gbaMonValidity == GBA_MON_STATE_IS_EGG) {
                    migrator->messageEntryID = MigrateFromGBA_Text_EggCannotMigrate;
                    *state = GBA_MIGRATOR_STATE_14;
                } else if (gbaMonValidity == GBA_MON_STATE_HAS_HM) {
                    migrator->messageEntryID = MigrateFromGBA_Text_KnowsHiddenMove;
                    *state = GBA_MIGRATOR_STATE_14;
                } else if (gbaMonValidity == GBA_MON_STATE_HAS_INVALID_ITEM) {
                    migrator->messageEntryID = MigrateFromGBA_Text_MonNotPermittedToMigrate;
                    *state = GBA_MIGRATOR_STATE_14;
                } else if (gbaMonValidity == GBA_MON_STATE_IS_INVALID_SPECIES) {
                    migrator->messageEntryID = MigrateFromGBA_Text_MonNotPermittedToMigrate;
                    *state = GBA_MIGRATOR_STATE_14;
                }
            } else {
                switch (boxPos) {
                case (GBA_MAX_MONS_PER_BOX + 1):
                    if (migrator->currentBox == 0) {
                        migrator->currentBox = GBA_MAX_PC_BOXES - 1;
                    } else {
                        migrator->currentBox--;
                    }

                    GBAMigrator_LoadBoxSprites(migrator);
                    Sound_PlayEffect(SE_CONFIRM_sseq_3);
                    break;
                case (GBA_MAX_MONS_PER_BOX + 2):
                    if (++migrator->currentBox == GBA_MAX_PC_BOXES) {
                        migrator->currentBox = 0;
                    }

                    GBAMigrator_LoadBoxSprites(migrator);
                    Sound_PlayEffect(SE_CONFIRM_sseq_3);
                    break;
                case (GBA_MAX_MONS_PER_BOX + 0):
                    GBAMigrator_FadeOut(migrator, FADE_TYPE_BRIGHTNESS_OUT, 24, state);
                    Sound_PlayEffect(SE_CONFIRM_sseq_3);
                    break;
                }
            }
        }
        break;
    case GBA_MIGRATOR_STATE_14:
        if (GBAMigrator_WaitMessage(migrator, 0)) {
            GBAMigrator_RemoveWindow(&migrator->messageWindow);
            *state = GBA_MIGRATOR_STATE_13;
        }
        break;
    case GBA_MIGRATOR_STATE_WAIT_FOR_FULL_SELECTION_TIMER:
        if (--migrator->fullSelectionTimer == 0) {
            GBAMigrator_FadeIn(migrator, FADE_TYPE_BRIGHTNESS_OUT, 16, state);
        }
        break;
    case GBA_MIGRATOR_STATE_16:
        GBAMigrator_InitConfirmScreen(migrator);
        GBAMigrator_FadeIn(migrator, FADE_TYPE_BRIGHTNESS_IN, 17, state);
        GBAMigrator_InitYesNoMenu(migrator);

        break;
    case GBA_MIGRATOR_STATE_17:
        boxPos = YesNoTouchMenu_ProcessInput(migrator->yesNoTouchMenu);

        switch (boxPos) {
        case YES_NO_TOUCH_MENU_YES:
            YesNoTouchMenu_Reset(migrator->yesNoTouchMenu);
            *state = GBA_MIGRATOR_STATE_18;
            break;
        case YES_NO_TOUCH_MENU_NO:
            YesNoTouchMenu_Reset(migrator->yesNoTouchMenu);
            GBAMigrator_FadeIn(migrator, FADE_TYPE_BRIGHTNESS_OUT, 20, state);
            break;
        }
        break;
    case GBA_MIGRATOR_STATE_18: {
        GBAMigratorTextBox v5;

        migrator->textBox.messageEntryID = MigrateFromGBA_Text_CannotReturnToGBA;

        GBAMigrator_DrawTextBox(migrator, &migrator->textBox, 0);
        GBAMigrator_InitYesNoMenu(migrator);

        Sound_PlayEffect(SE_CONFIRM_sseq_3);
        *state = GBA_MIGRATOR_STATE_19;
    } break;
    case GBA_MIGRATOR_STATE_19:
        boxPos = YesNoTouchMenu_ProcessInput(migrator->yesNoTouchMenu);

        switch (boxPos) {
        case YES_NO_TOUCH_MENU_YES:
            migrator->textBox.messageEntryID = sSavingOnGBAGameAndPlatinumMessageIDs[migrator->gbaVersion];
            GBAMigrator_DrawTextBox(migrator, &migrator->textBox, 0);
            YesNoTouchMenu_Reset(migrator->yesNoTouchMenu);
            migrator->saveState.state = 0;
            migrator->saveState.waitDial = Window_AddWaitDial(&migrator->messageWindow, 0x3F0 - (18 + 12));
            *state = GBA_MIGRATOR_STATE_21;
            ResetLock(RESET_LOCK_SOFT_RESET);
            break;
        case YES_NO_TOUCH_MENU_NO:
            YesNoTouchMenu_Reset(migrator->yesNoTouchMenu);
            GBAMigrator_FadeIn(migrator, FADE_TYPE_BRIGHTNESS_OUT, 20, state);
            break;
        }
        break;
    case GBA_MIGRATOR_STATE_20:
        ResetChosenPokemonData(migrator);
        *state = GBA_MIGRATOR_STATE_12;
        break;
    case GBA_MIGRATOR_STATE_21:
        v2 = GBAMigrator_HandleSave(migrator);

        if (v2 != 10) {
            DestroyWaitDial(migrator->saveState.waitDial);
            Sound_PlayEffect(SEQ_SE_DP_SAVE_sseq);

            if (v2 == 11) {
                migrator->textBox.messageEntryID = MigrateFromGBA_Text_SafelyMigratedToPlatinum;
            } else {
                migrator->textBox.messageEntryID = MigrateFromGBA_Text_SaveFailed;
            }

            GBAMigrator_DrawTextBox(migrator, &migrator->textBox, 0);
            *state = GBA_MIGRATOR_STATE_22;
            ResetUnlock(RESET_LOCK_SOFT_RESET);
        }
        break;
    case GBA_MIGRATOR_STATE_22:
        if (gSystem.touchPressed || gSystem.pressedKeys) {
            GBAMigrator_FadeOut(migrator, FADE_TYPE_BRIGHTNESS_OUT, 24, state);
            Sound_PlayEffect(SE_CONFIRM_sseq_3);
        }
        break;
    case GBA_MIGRATOR_STATE_FADE_OUT_TO_SELECTED_MON:
        if (IsScreenFadeDone()) {
            *state = migrator->nextState;
        }
        break;
    case GBA_MIGRATOR_STATE_24:
        GBAMigrator_FreeUi(migrator);
        return 1;
        break;
    }

    if (migrator->spriteList != NULL) {
        SpriteList_Update(migrator->spriteList);
    }

    return 0;
}

static int GBAMigrator_Exit(ApplicationManager *appMan, int *state)
{
    FS_EXTERN_OVERLAY(game_opening);

    GBAMigrator *migrator = ApplicationManager_Data(appMan);

    String_Free(migrator->messageString);
    String_Free(migrator->tempString);
    Heap_Free(migrator->bgConfig);
    EnqueueApplication(FS_OVERLAY_ID(game_opening), &gTitleScreenAppTemplate);
    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_MIGRATE_FROM_GBA);

    MainMenuUtil_ToggleTerminateOnGBACartRemoved(FALSE);

    return 1;
}

const ApplicationManagerTemplate gGBAMigratorAppTemplate = {
    GBAMigrator_Init,
    GBAMigrator_Main,
    GBAMigrator_Exit,
    FS_OVERLAY_ID_NONE
};
