project(cpp_arcade)

set(sources core/Color.hpp
        libs/src/IGraphicLib.hpp
        games/src/IGameLib.hpp
        core/Keys.hpp
        core/PixelBox.hpp
        core/TextBox.hpp
        core/Vect.hpp main.cpp core/ArgParser.cpp core/ArgParser.hpp core/Core.cpp core/Core.hpp core/GraphLibLoader.cpp core/GraphLibLoader.hpp core/GameLibLoader.cpp core/GameLibLoader.hpp)

set(lib_test_sources libs/src/test/entryPoint.cpp)

add_executable(cpp_arcade ${sources})

add_library(testlib ${lib_test_sources})