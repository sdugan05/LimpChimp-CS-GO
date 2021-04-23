#include "includes.h"

#include "csgo.hpp"

using namespace hazedumper::signatures;
using namespace hazedumper::netvars;

#include <thread>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene oEndScene = NULL;
WNDPROC oWndProc;
static HWND window = NULL;

void InitImGui(LPDIRECT3DDEVICE9 pDevice) {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    io.Fonts->AddFontDefault();
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX9_Init(pDevice);
}

bool init = false;
bool init_2 = false;

// Draw gui
bool show_main = true;

int screen_x = GetSystemMetrics(SM_CXSCREEN);
int screen_y = GetSystemMetrics(SM_CXSCREEN);

bool esp = false;
bool bhop = true;

bool first = true;

long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice) {

    if (!init) {
        InitImGui(pDevice);
        init = true;
    }



    if (GetAsyncKeyState(VK_INSERT) & 1) {
        show_main = !show_main;
    }

    ImGui::SetNextWindowSize(ImVec2(500, 350));
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    if (show_main) {
        ImGui::Begin("LimpChimp's CS:GO cheat");
        // GUI CONTENTS

        ImGui::Checkbox("Gaming", &bhop);

        ImGui::End();
    }



    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    if (init && !init_2) {
        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        init_2 = true;

        InitImGui(pDevice);
    }

    return oEndScene(pDevice);
}


LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam) {
    DWORD wndProcId;
    GetWindowThreadProcessId(handle, &wndProcId);

    if (GetCurrentProcessId() != wndProcId)
        return TRUE; // skip to next window

    window = handle;
    return FALSE; // window found abort search
}

HWND GetProcessWindow() {
    window = NULL;
    EnumWindows(EnumWindowsCallback, NULL);
    return window;
}

[[noreturn]] DWORD WINAPI MainThread(LPVOID lpReserved)
{
    bool attached = false;

    do {
        if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success) {
            kiero::bind(42, (void**)& oEndScene, hkEndScene);
            do
                window = GetProcessWindow();
            while (window == NULL);
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
            attached = true;
        }
    } while (!attached);
    return TRUE;
}



[[noreturn]] DWORD WINAPI bhopThread(LPVOID lp) {
    // Handle for client module
    DWORD gameModule = (DWORD)GetModuleHandle("client.dll");

    DWORD localPlayer = *(DWORD*)(gameModule + dwLocalPlayer);

    while(localPlayer == NULL) {
        localPlayer = *(DWORD*)(gameModule + dwLocalPlayer);
    }

    while (true) {
        while(bhop) {
            DWORD flag = *(BYTE*)(localPlayer + m_fFlags);

            if (GetAsyncKeyState(VK_SPACE) && flag & (1 << 0)) {
                *(DWORD*)(gameModule + dwForceJump) = 6;
            }
        }
    }
}
// Dll entrypoint
BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, bhopThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}
