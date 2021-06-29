#include "RecoilControl.h"

Vector3 RecoilControl::oPunch;

[[noreturn]] DWORD WINAPI RecoilControl::rcsThread(LPVOID lp) {
    while (true) {
        while(localPlayer == NULL || aimRecoilPunch == nullptr) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        if (gui->rcs) {
            reloadHack();
            Vector3 punchAngle = *aimRecoilPunch * (gui->rcsAmount * 2);

            if (*iShotsFired > 1 && GetAsyncKeyState(VK_LBUTTON)) {
                reloadHack();
                Vector3 newAngle = *viewAngles + oPunch - punchAngle;
                newAngle.normalize();

                // Set the viewangles
                *viewAngles = newAngle;
            }
            oPunch = punchAngle;
        }
    }
};

void RecoilControl::start() {
    oPunch = {0, 0, 0};
    CreateThread(nullptr, 0, rcsThread, this, 0, nullptr);
}