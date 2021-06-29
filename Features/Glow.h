#ifndef LIMPCHIMP_CS_GO_GLOW_H
#define LIMPCHIMP_CS_GO_GLOW_H

#include "../Hacks.h"
#include "../includes.h"

class Glow {
private:
    [[noreturn]] static DWORD WINAPI glowThread(LPVOID lp);

public:
    void start();
};

inline std::unique_ptr<Glow> glow;

#endif //LIMPCHIMP_CS_GO_GLOW_H
