//
// Created by Saul on 4/21/2021.
//

#include "Hooks.h"

void Hooks::initialize() {

}

Hooks::Hooks(HMODULE moduleHandle) {
    this->moduleHandle = moduleHandle;

    this->window = FindWindowW(L"Valve001", nullptr);
}
