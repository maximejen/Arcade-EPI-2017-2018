project(cpp_arcade)

set(sources
        core/Color.hpp
        libs/src/IGraphicLib.hpp
        games/src/IGameLib.hpp
        core/Keys.hpp
        core/PixelBox.hpp
        core/TextBox.hpp
        core/Vect.hpp
        main.cpp
        core/ArgParser.cpp
        core/ArgParser.hpp
        core/Core.cpp
        core/Core.hpp
        core/GraphLibLoader.cpp
        core/GraphLibLoader.hpp
        core/GameLibLoader.cpp
        core/GameLibLoader.hpp
        core/LogicException.cpp
        core/LogicException.hpp
        core/TextBox.cpp
        core/PixelBox.cpp core/Color.cpp)

set(lib_test_sources libs/src/ncurses/entryPoint.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-ldl")
set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_arcade ${sources})

add_library(testlib ${lib_test_sources})