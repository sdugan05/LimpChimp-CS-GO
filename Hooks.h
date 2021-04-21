//
// Created by Saul on 4/21/2021.
//

#ifndef LIMPCHIMP_CS_GO_HOOKS_H
#define LIMPCHIMP_CS_GO_HOOKS_H

#include "Windows.h"

#include <d3d9.h>
#include <memory>

class Hooks {

public:
    Hooks(HMODULE moduleHandle);

    void initialize();

    void findModules();



    std::add_pointer_t<HRESULT __stdcall(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*)> originalPresent;
    std::add_pointer_t<HRESULT __stdcall(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*)> originalReset;
    WNDPROC originalWndProc;
    HMODULE moduleHandle;
    HWND window;
};

inline std::unique_ptr<Hooks> hooks;

#endif //LIMPCHIMP_CS_GO_HOOKS_H
