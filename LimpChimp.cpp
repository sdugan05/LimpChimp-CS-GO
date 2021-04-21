#include "LimpChimp.h"

#include <iostream>


extern "C" BOOL WINAPI _CRT_INIT(HMODULE moduleHandle, DWORD reason, LPVOID reserved);

void openConsole() {
    FILE *pFile = nullptr;
    AllocConsole();
    freopen_s(&pFile, "CONOUT$", "w", stdout);
    SetConsoleTitle("LimpChimp CS:GO");
}

BOOL APIENTRY DllMain(HMODULE module_handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        openConsole();

        std::cout << "Injected" << std::endl;

        hooks = std::make_unique<Hooks>(module_handle);
    }



    return TRUE;
}
