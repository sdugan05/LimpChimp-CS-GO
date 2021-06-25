#include "Hacks.h"



DWORD gameModule;
DWORD engineModule;
DWORD localPlayer;

int* iShotsFired;

Vec3* aimRecoilPunch;
Vec3* viewAngles;
Vec3 oPunch = {0,0,0};

uintptr_t glowObject;
int localTeam;

void reloadHack() {
    localPlayer = *(DWORD*)(gameModule + dwLocalPlayer);

    if (localPlayer != NULL) {
        localTeam = *(int*)(localPlayer + m_iTeamNum);

        iShotsFired = (int*)(localPlayer + m_iShotsFired);

        aimRecoilPunch = (Vec3*)(localPlayer + m_aimPunchAngle);

        viewAngles = (Vec3*)(*(uintptr_t*)(engineModule + dwClientState) + dwClientState_ViewAngles);
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

[[noreturn]] DWORD WINAPI triggerThread(LPVOID lp) {
    // Triggerbot
    while(localPlayer == NULL) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    while (true) {
        while (gui->triggerBot) {
            // Triggerbot key is left alt
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
                reloadHack();
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

void setClanTag(const char* tag) {
    reloadHack();
    auto fnClantagChanged = reinterpret_cast<int(__fastcall*)(const char*, const char*)>(engineModule + dwSetClanTag);

    fnClantagChanged(tag, tag);
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
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
};
