#include "includes.h"

#include <iostream>

#include "csgo.hpp"


using namespace hazedumper::signatures;
using namespace hazedumper::netvars;

#include "Hacks.h"

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

// Draw gui
bool show_main = true;



bool first = true;

void openConsole() {
    FILE *pFile = nullptr;
    AllocConsole();
    freopen_s(&pFile, "CONOUT$", "w", stdout);
    SetConsoleTitle("LimpChimp CS:GO");
}


int screen_x = GetSystemMetrics(SM_CXSCREEN);
int screen_y = GetSystemMetrics(SM_CYSCREEN);

// Recoil Crosshair
int crosshairX = 0;
int crosshairY = 0;

LPDIRECT3DDEVICE9 externalDevice;

void drawFilledRect(int x, int y, int width, int height, D3DCOLOR color) {
    D3DRECT rect = {x, y, x + width, y + height};
    externalDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void drawLine(int x1, int y1, int x2, int y2, int thickness, bool antiAlias, D3DCOLOR color) {
    ID3DXLine* lineL;
    D3DXCreateLine(externalDevice, &lineL);

    D3DXVECTOR2 line[2];
    line[0] = D3DXVECTOR2(x1, y1);
    line[1] = D3DXVECTOR2(x2, y2);

    lineL->SetWidth(thickness);
    lineL->SetAntialias(antiAlias);
    lineL->Draw(line, 2, color);
    lineL->Release();
}

void recoilCrosshair() {
    if (crosshairX > 0 && crosshairY > 0 && gui->recoilCrosshair) {
        D3DCOLOR col = D3DCOLOR_ARGB( 255, (int)gui->recoilCrosshairColor.Value.x, (int)gui->recoilCrosshairColor.Value.y, (int)gui->recoilCrosshairColor.Value.z );
        if (gui->recoilCrosshairLine) {
            drawLine(screen_x / 2, screen_y / 2, crosshairX, crosshairY, 3, true, col);
        } else {
            drawFilledRect(crosshairX - 2, crosshairY - 2, 4, 4, col);
        }
    }
}

[[noreturn]] DWORD WINAPI recoilCrosshairThread(LPVOID lp) {
    while(true) {
        if (gui->recoilCrosshair) {
            localPlayer = *(DWORD*)(gameModule + dwLocalPlayer);
            if (localPlayer != NULL) {
                reloadHack();

                auto angle = *(Vector3*)(localPlayer + m_aimPunchAngle);

                crosshairX = screen_x / 2 - (screen_x / 90 * angle.y);
                crosshairY = screen_y / 2 + (screen_y / 90 * angle.x);
            }
        }
    }
}

long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice) {
    externalDevice = pDevice;

    if (!init) {
        initHack();
        InitImGui(pDevice);
        init = true;
    }

    if (GetAsyncKeyState(VK_INSERT) & 1) {
        show_main = !show_main;
    }

    if (crosshairX > 0 && crosshairY > 0 && gui->recoilCrosshair) {
        D3DCOLOR col = D3DCOLOR_ARGB( 255, (int)gui->recoilCrosshairColor.Value.x, (int)gui->recoilCrosshairColor.Value.y, (int)gui->recoilCrosshairColor.Value.z );
        if (gui->recoilCrosshairLine) {
            drawLine(screen_x / 2, screen_y / 2, crosshairX, crosshairY, 3, true, col);
        } else {
            drawFilledRect(crosshairX - 2, crosshairY - 2, 4, 4, col);
        }
    }

    ImGui::SetNextWindowSize(ImVec2(500, 350));
    ImGui::SetNextWindowPos({0,0});
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    if (show_main) {
        gui->DoGui();
    }

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

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

[[noreturn]] DWORD WINAPI MainThread(LPVOID lpReserved) {
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

// Dll entrypoint
BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
        gui = std::make_unique<Gui>();
            CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
            Sleep(400);
            CreateThread(nullptr, 0, reloadThread, hMod, 0, nullptr);
            Sleep(200);
            CreateThread(nullptr, 0, bhopThread, hMod, 0, nullptr);
            CreateThread(nullptr, 0, rcsThread, hMod, 0, nullptr);
            CreateThread(nullptr, 0, triggerThread, hMod, 0, nullptr);
            CreateThread(nullptr, 0, glowThread, hMod, 0, nullptr);
            Sleep(400);
            CreateThread(nullptr, 0, clanTagThread, hMod, 0, nullptr);

            CreateThread(nullptr, 0, noFlashThread, hMod, 0, nullptr);
            CreateThread(nullptr, 0, recoilCrosshairThread, hMod, 0, nullptr);

//            CreateThread(nullptr, 0, knifeChangerThread, hMod, 0, nullptr);

		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}