#ifndef LIMPCHIMP_CS_GO_HACKS_H
#define LIMPCHIMP_CS_GO_HACKS_H

#include "includes.h"
#include "csgo.hpp"

using namespace hazedumper::signatures;
using namespace hazedumper::netvars;

extern DWORD gameModule;
extern DWORD engineModule;
extern DWORD localPlayer;

extern struct Vec3 {
    float x, y, z;

    Vec3 operator+(Vec3 d) {
        return { x + d.x, y + d.y, z + d.z};
    }
    Vec3 operator-(Vec3 d) {
        return { x - d.x, y - d.y, z - d.z};
    }
    Vec3 operator*(float d) {
        return { x * d, y * d, z * d};
    }

    void normalize() {
        while (y < -180) {
            y = 360;
        }
        while (y > 180) {
            y = 360;
        }

        while ( x > 89) {
            x = 89;
        }
        while (x < -89) {
            x = -89;
        }
    }
};

extern int* iShotsFired;

extern Vec3* aimRecoilPunch;
extern Vec3* viewAngles;

extern uintptr_t glowObject;
extern int localTeam;
void reloadHack();

void setClanTag(const char* tag);

void initHack();

[[noreturn]] extern DWORD WINAPI triggerThread(LPVOID lp);

[[noreturn]] DWORD WINAPI rcsThread(LPVOID lp);

[[noreturn]] DWORD WINAPI glowThread(LPVOID lp);

[[noreturn]] extern DWORD WINAPI bhopThread(LPVOID lp);

[[noreturn]] DWORD WINAPI clanTagThread(LPVOID lp);

[[noreturn]] DWORD WINAPI reloadThread(LPVOID lp);

#endif //LIMPCHIMP_CS_GO_HACKS_H
