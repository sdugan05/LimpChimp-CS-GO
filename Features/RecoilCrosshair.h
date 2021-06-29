#ifndef LIMPCHIMP_CS_GO_RECOILCROSSHAIR_H
#define LIMPCHIMP_CS_GO_RECOILCROSSHAIR_H

#include <memory>
#include "../includes.h"
#include "../Hacks.h"

class RecoilCrosshair {
private:
    static int screen_x;
    static int screen_y;

    [[noreturn]] static DWORD WINAPI recoilCrosshairThread(LPVOID lp);

public:
    static int crosshairX;
    static int crosshairY;

    void start();
};

inline std::unique_ptr<RecoilCrosshair> recoilCrosshair;

#endif //LIMPCHIMP_CS_GO_RECOILCROSSHAIR_H
