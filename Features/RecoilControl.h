#ifndef LIMPCHIMP_CS_GO_RECOILCONTROL_H
#define LIMPCHIMP_CS_GO_RECOILCONTROL_H

#include "../Hacks.h"
#include "../includes.h"

class RecoilControl {
private:
    static Vector3 oPunch;
    [[noreturn]] static DWORD WINAPI rcsThread(LPVOID lp);

public:
    void start();
};

inline std::unique_ptr<RecoilControl> recoilControl;

#endif //LIMPCHIMP_CS_GO_RECOILCONTROL_H
