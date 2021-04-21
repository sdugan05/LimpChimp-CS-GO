//
// Created by Saul on 4/21/2021.
//

#ifndef LIMPCHIMP_CS_GO_HOOKS_H
#define LIMPCHIMP_CS_GO_HOOKS_H

#include "Windows.h"
#include "Hooks/MinHook.h"

class Hooks {

public:
    Hooks(HMODULE moduleHandle);

    void initialize();


    HMODULE moduleHandle;
    HWND window;
};

inline std::unique_ptr<Hooks> hooks;

#endif //LIMPCHIMP_CS_GO_HOOKS_H
