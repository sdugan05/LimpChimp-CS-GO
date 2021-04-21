//
// Created by Saul on 4/21/2021.
//

#include <ios>
#include <iostream>
#include "Hooks.h"

#include <thread>

#include "MinHook/MinHook.h"

#include "imgui/imgui.h"

#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#include "process/process.hpp"


void Hooks::initialize() {

}

void Hooks::findModules() {
    std::cout << "Waiting for Counter-Strike: Global Offensive..." << std::endl;

    while (!process->window)
    {
        process->window = FindWindowA(nullptr, "Counter-Strike: Global Offensive");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "Counter-Strike: Global Offensive found!" << std::endl;

    while (!process->process_id)
    {
        GetWindowThreadProcessId(process->window, reinterpret_cast<LPDWORD>(&process->process_id));
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << "ProcessID = " << process->process_id << std::endl;

    if (!process->attach()) {
        std::cout << "Attach failed! -> Error: " << GetLastError() << std::endl;
        std::cin.get();
        ExitProcess(0);
    }

    std::cout << "Waiting for serverbrowser.dll..." << std::endl;

    while (!process->GetModuleBaseAddress("serverbrowser.dll")[0])
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "serverbrowser.dll found!" << std::endl;

    std::cout << "Trying to get necessary modules..." << std::endl;

    while (!process->csgo[0] || !process->client[0] || !process->engine[0])
    {
        if (!process->csgo[0])
            process->csgo = process->GetModuleBaseAddress("csgo.exe");

        if (!process->client[0])
            process->client = process->GetModuleBaseAddress("client.dll");

        if (!process->engine[0])
            process->engine = process->GetModuleBaseAddress("engine.dll");

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << "All necessary modules found!" << std::endl;

    std::cout << "csgo.exe = " << std::hex << process->csgo[0] << std::endl;
    std::cout << "client.dll = " << std::hex << process->client[0] << std::endl;
    std::cout << "engine.dll = " << std::hex << process->engine[0] << std::endl;
}

Hooks::Hooks(HMODULE moduleHandle) {
    this->moduleHandle = moduleHandle;

    this->window = FindWindowA(nullptr, "Counter-Strike: Global Offensive");

    Hooks::findModules();
}


