#ifndef POKEPLATINUM_GTS_EMAIL_H
#define POKEPLATINUM_GTS_EMAIL_H

#include "constants/heap.h"

#include "string_gf.h"

void GTSEmail_ConvertString(String *param0, char *param1, enum HeapID heapID);
int GTSEmail_IsAllZeros(String *param0, enum HeapID heapID);
void GTSEmail_ParseNumbers(const char *param0, u32 *param1, int param2);

#endif // POKEPLATINUM_GTS_EMAIL_H
