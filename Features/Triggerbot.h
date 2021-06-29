#ifndef LIMPCHIMP_CS_GO_TRIGGERBOT_H
#define LIMPCHIMP_CS_GO_TRIGGERBOT_H

#include "../includes.h"
#include "../Hacks.h"

class Triggerbot {
private:
    [[noreturn]] static DWORD WINAPI triggerThread(LPVOID lp);

public:
    void start();
};

inline std::unique_ptr<Triggerbot> triggerbot;

#endif //LIMPCHIMP_CS_GO_TRIGGERBOT_H
