//
// Created by Saul on 4/21/2021.
//

#include <iostream>
#include "Memory.h"

#include "process/process.hpp"


Memory::Memory() {
    present = process->scan(process->game_overlay_renderer[0], process->game_overlay_renderer[1], "\xFF\x15\x00\x00\x00\x00\x8B\xF8\x85\xDB", "xx????xxxx") + 2;
    reset = process->scan(process->game_overlay_renderer[0], process->game_overlay_renderer[1], "\xC7\x45\x00\x00\x00\x00\x00\xFF\x15\x00\x00\x00\x00\x8B\xF8", "xx?????xx????xx") + 9;

    std::cout << present << std::endl;

    std::cout << reset << std::endl;
}
