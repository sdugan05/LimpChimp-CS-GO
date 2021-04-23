cmake_minimum_required(VERSION 3.19)
project(LimpChimp_CS_GO)

set(CMAKE_CXX_STANDARD 20)


list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/autofit/autofit.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/cff/cff.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/base/ftbase.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/base/ftbitmap.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/base/ftdebug.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/base/ftglyph.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/base/ftinit.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/base/ftsynth.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/base/ftsystem.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/psaux/psaux.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/pshinter/pshinter.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/psnames/psnames.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/raster/raster.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/sfnt/sfnt.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/smooth/smooth.c")
list(APPEND SOURCES "${CMAKE_SOURCE_DIR}/freetype/src/truetype/truetype.c")


add_compile_definitions(FT2_BUILD_LIBRARY)

include_directories(/usr/local/include /usr/local/include "${CMAKE_SOURCE_DIR}/freetype/")
link_directories(/usr/local/lib)

add_library(LimpChimp_CS_GO SHARED LimpChimp.cpp LimpChimp.h Hooks.cpp Hooks.h process/process.cpp Gui.cpp Gui.h imgui/imgui.cpp imgui/imgui_impl_dx9.cpp imgui/imgui_impl_win32.cpp imgui/imgui_tables.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui_freetype.cpp freetype/ft2build.h
        ${SOURCES}
        Memory.cpp Memory.h
        MinHook/MinHook.h
        MinHook/hde/hde32.c
        MinHook/hook.c
        MinHook/buffer.c
        MinHook/trampoline.c
        Helpers.cpp
        )