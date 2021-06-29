#include "Glow.h"

[[noreturn]] DWORD WINAPI Glow::glowThread(LPVOID lp) {
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
                        // Set colors
                        *(float*)(glowObject + ((glowIndex * 0x38) + 0x4)) = gui->enemyGlowColor.Value.x;
                        *(float*)(glowObject + ((glowIndex * 0x38) + 0x8)) = gui->enemyGlowColor.Value.y;
                        *(float*)(glowObject + ((glowIndex * 0x38) + 0xC)) = gui->enemyGlowColor.Value.z;
                        *(float*)(glowObject + ((glowIndex * 0x38) + 0x10)) = gui->enemyGlowColor.Value.w;
                    } else {
                        // Set Colors
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

void Glow::start() {
    CreateThread(nullptr, 0, glowThread, this, 0, nullptr);
}
