#include "Gui.h"

void Gui::DoGui() {
    ImGui::Begin("LimpChimp's CS:GO cheat");
    // GUI CONTENTS

    // Bhop
    ImGui::Checkbox("Gaming", &bhop);

    ImGui::Separator();

    // Recoil control
    ImGui::Checkbox("Epic Gaming", &rcs);

    // Amount of recoil control
    if (rcs) {
        ImGui::SliderFloat("Epic Gaming Amount", &rcsAmount, 0, 1);
    }

    ImGui::Separator();

    // Triggerbot
    ImGui::Checkbox("Triggerbot", &triggerBot);

    if (triggerBot) {
        ImGui::Checkbox("Triggerbot Delay", &triggerBotDelay);

        if (triggerBotDelay) {
            if (!triggerBotCustomDelay) {
                ImGui::Checkbox("Triggerbot Random Delay", &triggerBotRandomness);
            }

            if (!triggerBotRandomness) {
                ImGui::Checkbox("Custom Delay", &triggerBotCustomDelay);
                if (triggerBotCustomDelay) {
                    ImGui::InputInt("Delay Time", &triggerBotCustomDelayTime);
                }
            }
        }
    }

    ImGui::End();
}
