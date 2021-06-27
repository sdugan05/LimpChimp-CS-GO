#include "Gui.h"

void Gui::DoGui() {
    ImGui::Begin("LimpChimp's CS:GO cheat");
    // GUI CONTENTS

    // Bhop
    ImGui::Checkbox("Bhop", &bhop);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Recoil control
    ImGui::Checkbox("RCS", &rcs);

    // Amount of recoil control
    if (rcs) {
        ImGui::SliderFloat("RCS Amount", &rcsAmount, 0, 1);
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

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

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // Glow

    ImGui::Checkbox("Glow", &glow);

    if (glow) {
        ImGui::ColorPicker4("Enemy Glow Color", (float*)&enemyGlowColor);

        ImGui::Checkbox("Team Glow", &teamGlow);
        if (teamGlow) {
            ImGui::ColorPicker4("Team Glow Color", (float*)&teamGlowColor);
        }
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Checkbox("Update Clantag", &changeClanTag);

    ImGui::Checkbox("Animated Clantag", &animatedClantag);

    ImGui::Text("Clantag");

    if (ImGui::InputText("", const_cast<char *>(clanTag), 16)) {

    }

    ImGui::Text("%s", clanTag);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();


    ImGui::Checkbox("No Flash", &noFlash);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Checkbox("Bayonet", &bayonet);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Checkbox("Box ESP", &boxEsp);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Checkbox("Recoil Crosshair", &recoilCrosshair);
    ImGui::Checkbox("Recoil Crosshair Line", &recoilCrosshairLine);

    ImGui::ColorPicker4("Recoil Crosshair Color", (float*)&recoilCrosshairColor);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::End();
}
