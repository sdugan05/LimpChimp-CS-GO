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

#include "Memory.h"

#include "Gui.h"

int once = 0;

static LRESULT __stdcall wndProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
//    [[maybe_unused]] static const auto once = [](HWND window) noexcept {
//        std::cout << "once" << std::endl;
//        ImGui::CreateContext();
//        ImGui_ImplWin32_Init(window);
//
//        gui = std::make_unique<Gui>();
//
//        std::cout << "render???" << std::endl;
//        hooks->initialize();
//
//        return true;
//    }(window);

    if(once == 0) {


        ImGui::CreateContext();

        ImGui_ImplWin32_Init(window);

        gui = std::make_unique<Gui>();

        std::cout << "render???" << std::endl;
        hooks->initialize();
        once = 1;
    }

    LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    ImGui_ImplWin32_WndProcHandler(window, msg, wParam, lParam);

    return CallWindowProcW(hooks->originalWndProc, window, msg, wParam, lParam);
}


static HRESULT __stdcall present(IDirect3DDevice9* device, const RECT* src, const RECT* dest, HWND windowOverride, const RGNDATA* dirtyRegion) noexcept {
    [[maybe_unused]] static bool imguiInit{ ImGui_ImplDX9_Init(device) };

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    ImGui::Text("AAA");

    ImGui::EndFrame();
    ImGui::Render();

    if (device->BeginScene() == D3D_OK) {
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        device->EndScene();
    }

    return hooks->originalPresent(device, src, dest, windowOverride, dirtyRegion);
}

static HRESULT __stdcall reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept {
    ImGui_ImplDX9_InvalidateDeviceObjects();
    return hooks->originalReset(device, params);
}


void Hooks::initialize() {
    std::cout << "innit" << std::endl;
    originalPresent = **reinterpret_cast<decltype(originalPresent)**>(memory->present);
    **reinterpret_cast<decltype(present)***>(memory->present) = present;
    originalReset = **reinterpret_cast<decltype(originalReset)**>(memory->reset);
    **reinterpret_cast<decltype(reset)***>(memory->reset) = reset;

    MH_Initialize();
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

        if(!process->game_overlay_renderer[0])
            process->game_overlay_renderer = process->GetModuleBaseAddress("gameoverlayrenderer.dll");

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << "All necessary modules found!" << std::endl;

    std::cout << "csgo.exe = " << std::hex << process->csgo[0] << std::endl;
    std::cout << "client.dll = " << std::hex << process->client[0] << std::endl;
    std::cout << "engine.dll = " << std::hex << process->engine[0] << std::endl;
    std::cout << "GameOverlayRenderer.dll = " << std::hex << process->game_overlay_renderer[0] << std::endl;
}

Hooks::Hooks(HMODULE moduleHandle) {
    this->moduleHandle = moduleHandle;

    this->window = FindWindowA(nullptr, "Counter-Strike: Global Offensive");
    Hooks::findModules();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    memory = std::make_unique<Memory>();
    originalWndProc = WNDPROC(SetWindowLongPtrW(window, GWLP_WNDPROC, LONG_PTR(wndProc)));

}


