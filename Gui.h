#include <memory>
#include "imgui/imgui.h"

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
};

inline std::unique_ptr<Gui> gui;