#include <memory>
#include "imgui/imgui.h"

#ifndef gui_class
#define gui_class

class Gui {
public:
    void DoGui();

    // Hack features
    bool bhop = false;
    bool rcs = false;
    bool triggerBot = false;
    bool triggerBotDelay = false;
    bool triggerBotRandomness = false;
    bool triggerBotCustomDelay = false;
    int triggerBotCustomDelayTime= 0;

    float rcsAmount = 0.0f;

    bool glow = false;
    bool teamGlow = false;
    ImColor enemyGlowColor;
    ImColor teamGlowColor;

    const char* clanTag = "";
    bool changeClanTag = false;
    bool animatedClantag = false;

    bool noFlash = false;

    bool bayonet = false;

    bool boxEsp = false;
    bool tracers = false;
    bool drawBacking = false;

    bool recoilCrosshair = false;
    ImColor recoilCrosshairColor;
    bool recoilCrosshairLine = false;
};

inline std::unique_ptr<Gui> gui;

#endif