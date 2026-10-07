#include "poffin_cooking/poffin_cooking_0223D144.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/comm_cmd_table.h"

#include "poffin_cooking/poffin_cooking_0223D150.h"

#include "poffin.h"

static const CommCmdTable Unk_poffin_cooking_02240390[] = {
    { poffin_cooking_0223D204, poffin_cooking_0223D4AC, NULL },
    { poffin_cooking_0223D210, poffin_cooking_0223D4AC, NULL },
    { poffin_cooking_0223D21C, poffin_cooking_0223D4B4, NULL },
    { poffin_cooking_0223D258, poffin_cooking_0223D4B8, NULL },
    { poffin_cooking_0223D2E8, poffin_cooking_0223D4BC, NULL },
    { poffin_cooking_0223D3D8, poffin_cooking_0223D4C0, NULL },
    { poffin_cooking_0223D3F8, Poffin_SizeOf, NULL },
    { poffin_cooking_0223D410, poffin_cooking_0223D4B0, NULL },
    { poffin_cooking_0223D430, poffin_cooking_0223D4B0, NULL },
    { poffin_cooking_0223D354, poffin_cooking_0223D4C4, NULL },
    { poffin_cooking_0223D3A8, poffin_cooking_0223D4C8, NULL }
};

const CommCmdTable *poffin_cooking_0223D144(void)
{
    return Unk_poffin_cooking_02240390;
}

int poffin_cooking_0223D14C(void)
{
    return sizeof(Unk_poffin_cooking_02240390) / sizeof(CommCmdTable);
}
