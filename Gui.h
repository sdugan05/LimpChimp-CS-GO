//
// Created by Saul on 4/21/2021.
//

#ifndef LIMPCHIMP_CS_GO_GUI_H
#define LIMPCHIMP_CS_GO_GUI_H

#include <memory>
#include <vector>
#include <string>
#include "imgui/imgui.h"

class Gui {
public:
    Gui();

    struct {
        ImFont* normal15px = nullptr;
    } fonts;

    std::vector<std::string> systemFonts{ "Default" };
};

inline std::unique_ptr<Gui> gui;

#endif //LIMPCHIMP_CS_GO_GUI_H
