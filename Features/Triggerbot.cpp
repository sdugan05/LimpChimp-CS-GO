#include "Triggerbot.h"

[[noreturn]] DWORD WINAPI Triggerbot::triggerThread(LPVOID lp) {
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

void Triggerbot::start() {
    CreateThread(nullptr, 0, triggerThread, this, 0, nullptr);
}