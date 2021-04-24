#include "includes.h"

#include "csgo.hpp"

#include "Gui.h"

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

bool first = true;

DWORD gameModule;
DWORD engineModule;
DWORD localPlayer;

struct Vec3 {
    float x, y, z;

    Vec3 operator+(Vec3 d) {
        return { x + d.x, y + d.y, z + d.z};
    }
    Vec3 operator-(Vec3 d) {
        return { x - d.x, y - d.y, z - d.z};
    }
    Vec3 operator*(float d) {
        return { x * d, y * d, z * d};
    }

    void normalize() {
        while (y < -180) {
            y = 360;
        }
        while (y > 180) {
            y = 360;
        }

        while ( x > 89) {
            x = 89;
        }
        while (x < -89) {
            x = -89;
        }
    }
};

int* iShotsFired;

Vec3* aimRecoilPunch;
Vec3* viewAngles;
Vec3 oPunch{0,0,0};


void initHack() {
    gameModule = (DWORD)GetModuleHandle("client.dll");
    engineModule = (DWORD)GetModuleHandle("engine.dll");
    localPlayer = *(DWORD*)(gameModule + dwLocalPlayer);

    iShotsFired = (int*)(localPlayer + m_iShotsFired);

    aimRecoilPunch = (Vec3*)(localPlayer + m_aimPunchAngle);

    viewAngles = (Vec3*)(*(uintptr_t*)(engineModule + dwClientState) + dwClientState_ViewAngles);
}



long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice) {

    if (!init) {
        initHack();
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

[[noreturn]] DWORD WINAPI triggerThread(LPVOID lp) {
    while (true) {
        while (gui->triggerBot && GetAsyncKeyState()) {
            int crosshair = *(int*)(localPlayer + m_iCrosshairId);
            int localTeam = *(int*)(localPlayer + m_iTeamNum);

            // At least one entity on the crosshair
            if (crosshair != 0  && crosshair < 64) {
                uintptr_t entity = *(uintptr_t*)(gameModule + dwEntityList + (crosshair - 1) * 0x10);
                int entityTeam = *(int*)(entity + m_iTeamNum);
                int entityHealth = *(int*)(entity + m_iHealth);

                if (entityTeam != localTeam && entityHealth > 0 && entityHealth <= 100) {
                    if (gui->triggerBotDelay) {

                        // For random triggerbot delay
                        if (gui->triggerBotRandomness) {
                            std::this_thread::sleep_for(std::chrono::milliseconds(rand() + 50));
                            // Shoot
                            *(int*)(gameModule + dwForceAttack) = 5;
                            std::this_thread::sleep_for(std::chrono::milliseconds(20));
                            // Stop shooting
                            *(int*)(gameModule + dwForceAttack) = 4;
                        }
                        // Custom delay
                        else if (gui->triggerBotCustomDelay) {
                            std::this_thread::sleep_for(std::chrono::milliseconds(gui->triggerBotCustomDelayTime));
                            // Shoot
                            *(int*)(gameModule + dwForceAttack) = 5;
                            std::this_thread::sleep_for(std::chrono::milliseconds(20));
                            // Stop shooting
                            *(int*)(gameModule + dwForceAttack) = 4;
                        }
                    }
                    // No delay
                    else {
                        // Shoot
                        *(int*)(gameModule + dwForceAttack) = 5;
                        std::this_thread::sleep_for(std::chrono::milliseconds(20));
                        // Stop shooting
                        *(int*)(gameModule + dwForceAttack) = 4;
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
};

[[noreturn]] DWORD WINAPI rcsThread(LPVOID lp) {
    while (true) {
        if (gui->rcs) {
            Vec3 punchAngle = *aimRecoilPunch * (gui->rcsAmount * 2);

            if (*iShotsFired > 1 && GetAsyncKeyState(VK_LBUTTON)) {
                Vec3 newAngle = *viewAngles + oPunch - punchAngle;
                newAngle.normalize();

                // Set the viewangles
                *viewAngles = newAngle;
            }
            oPunch = punchAngle;
        }
    }
};

[[noreturn]] DWORD WINAPI bhopThread(LPVOID lp) {
    while(localPlayer == NULL) {
        localPlayer = *(DWORD*)(gameModule + dwLocalPlayer);
    }

    while (true) {
        while(gui->bhop) {
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
		gui = std::make_unique<Gui>();
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		CreateThread(nullptr, 0, bhopThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, rcsThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, triggerThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}
