#include "ilobby/dwci_lobbybase.h"

UnkFuncPtr_0225B6E4 DWCi_LobbyObject::sAllocFailureCallback = 0;

void *DWCi_LobbyObject::operator new(std::size_t param0) throw()
{
    if (param0 == 0) {
        param0 = 1;
    }

    while (TRUE) {
        void *v0 = DWC_Alloc(DWC_ALLOCTYPE_AUTH, param0);

        if (v0) {
            return v0;
        }

        UnkFuncPtr_0225B6E4 v1 = DWCi_LobbyObject::ExchangeAllocFailureCallback(0);
        DWCi_LobbyObject::ExchangeAllocFailureCallback(v1);

        if (v1) {
            (*v1)();
        } else {
            return NULL;
        }
    }
}
