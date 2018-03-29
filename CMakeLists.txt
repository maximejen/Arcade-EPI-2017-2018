project(cpp_arcade)

set(sources core/Color.hpp
        entryPoint.cpp
        games/src/IGameLib.hpp
        libs/src/IGraphicLib.hpp
        core/Keys.hpp
        core/PixelBox.hpp
        core/TextBox.hpp
        core/Vect.hpp main.cpp core/ArgParser.cpp core/ArgParser.hpp core/Core.cpp core/Core.hpp core/DlLoader.cpp core/DlLoader.hpp)

add_executable(cpp_arcade ${sources})