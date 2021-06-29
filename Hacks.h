#ifndef LIMPCHIMP_CS_GO_HACKS_H
#define LIMPCHIMP_CS_GO_HACKS_H

#include "includes.h"
#include "csgo.hpp"
#include <string>

using namespace hazedumper::signatures;
using namespace hazedumper::netvars;

extern DWORD gameModule;
extern DWORD engineModule;
extern DWORD localPlayer;

extern int* iShotsFired;

extern Vector3* aimRecoilPunch;
extern Vector3* viewAngles;

extern uintptr_t glowObject;
extern int localTeam;
void reloadHack();

void setClanTag(const char* tag);

void initHack();

[[noreturn]] extern DWORD WINAPI bhopThread(LPVOID lp);

[[noreturn]] DWORD WINAPI clanTagThread(LPVOID lp);

[[noreturn]] DWORD WINAPI reloadThread(LPVOID lp);

[[noreturn]] DWORD WINAPI noFlashThread(LPVOID lp);

[[noreturn]] DWORD WINAPI knifeChangerThread(LPVOID lp);

#endif //LIMPCHIMP_CS_GO_HACKS_H
