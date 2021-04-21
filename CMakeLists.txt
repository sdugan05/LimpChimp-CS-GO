cmake_minimum_required(VERSION 3.19)
project(LimpChimp_CS_GO)

set(CMAKE_CXX_STANDARD 17)


add_compile_definitions(FT2_BUILD_LIBRARY)

add_library(LimpChimp_CS_GO SHARED LimpChimp.cpp LimpChimp.h Hooks.cpp Hooks.h process/process.cpp)