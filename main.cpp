#include "includes.h"

#include <iostream>

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

uintptr_t glowObject;
int localTeam;

void openConsole() {
    FILE *pFile = nullptr;
    AllocConsole();
    freopen_s(&pFile, "CONOUT$", "w", stdout);
    SetConsoleTitle("LimpChimp CS:GO");
}

void reloadHack() {
    localPlayer = *(DWORD*)(gameModule + dwLocalPlayer);

    if (localPlayer != NULL) {
        localTeam = *(int*)(localPlayer + m_iTeamNum);

        iShotsFired = (int*)(localPlayer + m_iShotsFired);

        aimRecoilPunch = (Vec3*)(localPlayer + m_aimPunchAngle);
    }

    glowObject = *(uintptr_t*)(gameModule + dwGlowObjectManager);


}

void initHack() {
    gameModule = (DWORD)GetModuleHandle("client.dll");
    engineModule = (DWORD)GetModuleHandle("engine.dll");
    localPlayer = *(DWORD*)(gameModule + dwLocalPlayer);

    gui->enemyGlowColor.Value.w = 1;
    gui->teamGlowColor.Value.w = 1;

    if (*(DWORD*)(gameModule + dwLocalPlayer) != NULL) {
        iShotsFired = (int*)(localPlayer + m_iShotsFired);

        aimRecoilPunch = (Vec3*)(localPlayer + m_aimPunchAngle);
    } else {
        Sleep(1000);
        reloadHack();
        return;
    }

    viewAngles = (Vec3*)(*(uintptr_t*)(engineModule + dwClientState) + dwClientState_ViewAngles);
}

void setClanTag(const char* tag) {
    if (!init) {
        return;
    }
    auto fnClantagChanged = reinterpret_cast<int(__fastcall*)(const char*, const char*)>(engineModule + dwSetClanTag);

    fnClantagChanged(tag, tag);
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
    while(localPlayer == NULL) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    while (true) {
        while (gui->triggerBot) {
            if (GetAsyncKeyState(VK_LMENU)) {

                reloadHack();
                int crosshair = *(int *) (localPlayer + m_iCrosshairId);
                int localTeam = *(int *) (localPlayer + m_iTeamNum);

                // At least one entity on the crosshair
                if (crosshair != 0 && crosshair < 64) {
                    uintptr_t entity = *(uintptr_t *) (gameModule + dwEntityList + (crosshair - 1) * 0x10);
                    int entityTeam = *(int *) (entity + m_iTeamNum);
                    int entityHealth = *(int *) (entity + m_iHealth);

                    if (entityTeam != localTeam && entityHealth > 0 && entityHealth <= 100) {
                        if (gui->triggerBotDelay) {

                            // For random triggerbot delay
                            if (gui->triggerBotRandomness) {
                                std::this_thread::sleep_for(std::chrono::milliseconds(rand() + 50));
                                // Shoot
                                *(int *) (gameModule + dwForceAttack) = 5;
                                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                                // Stop shooting
                                *(int *) (gameModule + dwForceAttack) = 4;
                            }
                                // Custom delay
                            else if (gui->triggerBotCustomDelay) {
                                std::this_thread::sleep_for(std::chrono::milliseconds(gui->triggerBotCustomDelayTime));
                                // Shoot
                                *(int *) (gameModule + dwForceAttack) = 5;
                                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                                // Stop shooting
                                *(int *) (gameModule + dwForceAttack) = 4;
                            }
                        }
                            // No delay
                        else {
                            // Shoot
                            *(int *) (gameModule + dwForceAttack) = 5;
                            std::this_thread::sleep_for(std::chrono::milliseconds(20));
                            // Stop shooting
                            *(int *) (gameModule + dwForceAttack) = 4;
                        }
                    }
                }
            }
        }
        Sleep(2000);
    }
};

[[noreturn]] DWORD WINAPI rcsThread(LPVOID lp) {
    while (true) {
        while(localPlayer == NULL || aimRecoilPunch == nullptr) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        if (gui->rcs) {
            reloadHack();
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

[[noreturn]] DWORD WINAPI glowThread(LPVOID lp) {

    glowObject = *(uintptr_t*)(gameModule + dwGlowObjectManager);

    while (true) {
        while(glowObject == NULL) {
            Sleep(200);
        }
        if (gui->glow) {
            reloadHack();
            // 64 possible entities
            for (int i = 0; i < 64; ++i) {
                uintptr_t entity = *(uintptr_t*)(gameModule + dwEntityList + i * 0x10);

                if (entity != NULL) {
                    int entityTeam = *(int*)(entity + m_iTeamNum);
                    int glowIndex = *(int*)(entity + m_iGlowIndex);

                    // If enemy
                    if (localTeam != entityTeam) {
                        *(float*)(glowObject + ((glowIndex * 0x38) + 0x4)) = gui->enemyGlowColor.Value.x;
                        *(float*)(glowObject + ((glowIndex * 0x38) + 0x8)) = gui->enemyGlowColor.Value.y;
                        *(float*)(glowObject + ((glowIndex * 0x38) + 0xC)) = gui->enemyGlowColor.Value.z;
                        *(float*)(glowObject + ((glowIndex * 0x38) + 0x10)) = gui->enemyGlowColor.Value.w;
                    } else {
                        *(float*)(glowObject + ((glowIndex * 0x38) + 0x4)) = gui->teamGlowColor.Value.x;
                        *(float*)(glowObject + ((glowIndex * 0x38) + 0x8)) = gui->teamGlowColor.Value.y;
                        *(float*)(glowObject + ((glowIndex * 0x38) + 0xC)) = gui->teamGlowColor.Value.z;
                        *(float*)(glowObject + ((glowIndex * 0x38) + 0x10)) = gui->teamGlowColor.Value.w;
                    }
                    // Set glow on

                    *(bool*)(glowObject + ((glowIndex * 0x38) + 0x24)) = true;
                    *(bool*)(glowObject + ((glowIndex * 0x38) + 0x25)) = false;


                }
            }
        }
    }
}

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


[[noreturn]] DWORD WINAPI clanTagThread(LPVOID lp) {
    Sleep(200);

    while (true) {
        if (gui->changeClanTag) {
            setClanTag(gui->clanTag);
            gui->changeClanTag = false;
        }
    }
};


[[noreturn]] DWORD WINAPI reloadThread(LPVOID lp) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    openConsole();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    while (true) {
        if (localPlayer == NULL || glowObject == NULL) {
            reloadHack();
            std::cout << "hack reloaded" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
};



// Dll entrypoint
BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		gui = std::make_unique<Gui>();
            CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
            Sleep(200);
            CreateThread(nullptr, 0, reloadThread, hMod, 0, nullptr);
            Sleep(200);
            CreateThread(nullptr, 0, bhopThread, hMod, 0, nullptr);
            CreateThread(nullptr, 0, rcsThread, hMod, 0, nullptr);
            CreateThread(nullptr, 0, triggerThread, hMod, 0, nullptr);
            CreateThread(nullptr, 0, glowThread, hMod, 0, nullptr);
            Sleep(8000);
            CreateThread(nullptr, 0, clanTagThread, hMod, 0, nullptr);

		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}