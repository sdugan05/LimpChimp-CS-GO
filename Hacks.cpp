#include "Hacks.h"



DWORD gameModule;
DWORD engineModule;
DWORD localPlayer;

int* iShotsFired;

Vector3* aimRecoilPunch;
Vector3* viewAngles;

uintptr_t glowObject;
int localTeam;

void reloadHack() {
    localPlayer = *(DWORD*)(gameModule + dwLocalPlayer);

    if (localPlayer != NULL) {
        localTeam = *(int*)(localPlayer + m_iTeamNum);

        iShotsFired = (int*)(localPlayer + m_iShotsFired);

        aimRecoilPunch = (Vector3*)(localPlayer + m_aimPunchAngle);

        viewAngles = (Vector3*)(*(uintptr_t*)(engineModule + dwClientState) + dwClientState_ViewAngles);
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

        aimRecoilPunch = (Vector3*)(localPlayer + m_aimPunchAngle);
    } else {
        Sleep(1000);
        reloadHack();
        return;
    }

    viewAngles = (Vector3*)(*(uintptr_t*)(engineModule + dwClientState) + dwClientState_ViewAngles);
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

std::string animate(std::string a) {
    std::string temp_str_1 = std::string(a);
    std::string temp_str_2 = std::string(a);

    char end_char = temp_str_1[temp_str_1.length() - 1];
    for (int i = 1; i <= temp_str_1.length(); ++i) {
        temp_str_2[i] = temp_str_1[i - 1];
    }
    temp_str_2[0] = end_char;
    return temp_str_2;
}


[[noreturn]] DWORD WINAPI clanTagThread(LPVOID lp) {
    Sleep(200);

    while (true) {
        Sleep(200);
        if (gui->changeClanTag) {
            setClanTag(gui->clanTag);
            gui->changeClanTag = false;
        }
        if (gui->animatedClantag) {
            std::string temp = std::string(gui->clanTag);
            while (gui->animatedClantag) {
                temp = animate(std::string(temp));
                setClanTag(temp.c_str());

                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }

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

[[noreturn]] DWORD WINAPI noFlashThread(LPVOID lp) {
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (gui->noFlash) {
            localPlayer = *(DWORD*)(gameModule + dwLocalPlayer);
            if (localPlayer != NULL) {
                *(float*)(localPlayer + m_flFlashDuration) = 0.0f;
            }
        }
    }
};

[[noreturn]] DWORD WINAPI knifeChangerThread(LPVOID lp) {
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if(gui->bayonet) {
            localPlayer = *(DWORD*)(gameModule + dwLocalPlayer);
            if (localPlayer != NULL) {
                DWORD weaponIndex = *(DWORD*)(localPlayer + m_hActiveWeapon) & 0xFFFF;
                DWORD entityList = *(DWORD*)(gameModule + dwEntityList + (weaponIndex - 1) *  0x10);
                DWORD weaponId = *(DWORD*)(entityList + m_iItemDefinitionIndex);

                *(int*)(entityList + m_iItemIDHigh) = -1;
                *(DWORD*)(entityList + m_nFallbackPaintKit) = 38;
                *(float*)(entityList + m_flFallbackWear) = 0.00001;
            }
        }
    }
}

//// Box ESP
//
//float boxWidth = 0.5;
//int boxThickness = 2;
//
//int backingAlpha = 35;
//
//int tracerBone = 9;
//
//struct Color4 {
//    int r, g, b, a;
//};
//
//Color4 boxColor;
//Color4 tracerColor;
//
//int screen_x = GetSystemMetrics(SM_CXSCREEN);
//int screen_y = GetSystemMetrics(SM_CXSCREEN);
//
//bool worldToScreen(Vector3 position, Vector2& screenPos, float matrix[16], int width, int height) {
//    Vector4 clipCoords;
//    clipCoords.x = position.x * matrix[0] + position.y * matrix[1] + position.z * matrix[2] + matrix[3];
//    clipCoords.y = position.x * matrix[4] + position.y * matrix[5] + position.z * matrix[6] + matrix[7];
//    clipCoords.z = position.x * matrix[8] + position.y * matrix[9] + position.z * matrix[10] + matrix[11];
//    clipCoords.w = position.x * matrix[12] + position.y * matrix[13] + position.z * matrix[14] + matrix[15];
//
//    if (clipCoords.w < 0.1f) {
//        return false;
//    }
//
//    Vector3 ndc;
//    ndc.x = clipCoords.x / clipCoords.w;
//    ndc.y = clipCoords.y / clipCoords.w;
//    ndc.z = clipCoords.z / clipCoords.w;
//
//    screenPos.x = (width / 2 * ndc.x) + (ndc.x + width / 2);
//    screenPos.y = -(height / 2 * ndc.y) + (ndc.y + height / 2);
//
//    return true;
//}
//
//Vector2 GetBonePosition(uintptr_t entity, int bone) {
//    uintptr_t boneMatrixBase = *(uintptr_t*)(entity + m_dwBoneMatrix);
//    BoneMatrix boneMatrix = *(BoneMatrix*)(boneMatrixBase + sizeof(boneMatrix) * bone);
//    Vector3 boneLocation = {boneMatrix.x, boneMatrix.y, boneMatrix.z};
//
//    Vector2 screenCoords;
//
//    float viewMatrix[16];
//    memcpy(&viewMatrix, (PBYTE*)(gameModule + dwViewMatrix), sizeof(viewMatrix));
//
//    if (worldToScreen(boneLocation, screenCoords, viewMatrix, screen_x, screen_y)) {
//        return screenCoords;
//    }
//    return {0,0};
//}
