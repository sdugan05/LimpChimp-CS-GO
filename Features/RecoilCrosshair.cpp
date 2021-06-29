#include "RecoilCrosshair.h"

int RecoilCrosshair::crosshairX;
int RecoilCrosshair::crosshairY;

int RecoilCrosshair::screen_x;
int RecoilCrosshair::screen_y;

[[noreturn]] DWORD WINAPI RecoilCrosshair::recoilCrosshairThread(LPVOID lp) {
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

void RecoilCrosshair::start() {
    screen_x = GetSystemMetrics(SM_CXSCREEN);
    screen_y = GetSystemMetrics(SM_CYSCREEN);
    crosshairX = 0;
    crosshairY = 0;
    CreateThread(nullptr, 0, recoilCrosshairThread, this, 0, nullptr);
}
