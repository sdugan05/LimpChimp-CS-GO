cmake_minimum_required(VERSION 3.19)
project(LimpChimp_CS_GO)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include /usr/local/include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include")

link_directories(/usr/local/lib )

add_library(LimpChimp_CS_GO SHARED main.cpp
        kiero/kiero.cpp
        kiero/minhook/include/MinHook.h
        kiero/minhook/src/trampoline.c
        kiero/minhook/src/buffer.c
        kiero/minhook/src/hook.c
        kiero/minhook/src/hde/hde32.c

        imgui/imgui.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_impl_win32.cpp
        imgui/imgui_impl_dx9.cpp

        csgo.hpp Gui.cpp Gui.h Hacks.cpp Hacks.h)

target_link_libraries(LimpChimp_CS_GO d3d9)