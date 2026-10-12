#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_MESSAGES_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_MESSAGES_H

#include "message.h"
#include "string_gf.h"
#include "string_template.h"

typedef struct {
    MessageLoader *messageLoader;
    StringTemplate *stringTemplate;
    String *formattedString;
    String *string00;
    String *string01;
    String *string02;
    String *string20;
    String *string21;
    String *string22;
    String *string23;
    String *string24;
    String *string25;
    String *string08;
    String *string09;
    String *strings03[5];
    String *strings10[10];
} PoffinCookingMessages;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_MESSAGES_H
