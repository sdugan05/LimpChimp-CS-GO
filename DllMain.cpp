#include "DllMain.h"

#include <iostream>

BOOL APIENTRY hello(HMODULE module_handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        std::cout << "Hello, World!" << std::endl;
    }

    return TRUE;
}
