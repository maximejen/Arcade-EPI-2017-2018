project(cpp_arcade)

set(sources
        core/Color.hpp
        libs/src/IGraphicLib.hpp
        games/src/IGameLib.hpp
        core/Keys.hpp
        core/PixelBox.hpp
        core/TextBox.hpp
        core/Vect.hpp
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
        core/PixelBox.cpp core/Color.cpp
        libs/src/SDL/LibSDL.cpp
        libs/src/SDL/LibSDL.hpp
        libs/src/SDL/entryPoint.cpp
        games/src/Nibbler/entryPoint.cpp
        games/src/Nibbler/LibNibbler.cpp core/PlayerScore.cpp core/PlayerScore.hpp
        games/src/Pacman/entryPoint.cpp
        games/src/Nibbler/LibNibbler.hpp
        games/src/Pacman/LibPacman.cpp
        games/src/Pacman/LibPacman.hpp games/src/Nibbler/LibNibbler.cpp core/MenuManager.cpp core/ScoreManager.cpp core/ScoreManager.hpp)

set(lib_ncurse_sources libs/src/ncurses/entryPoint.cpp libs/src/ncurses/LibNcurses.cpp libs/src/ncurses/LibNcurses.hpp)

set(lib_sfml_sources libs/src/SFML/entryPoint.cpp libs/src/SFML/LibSFML.cpp libs/src/SFML/LibSFML.hpp)

set(CMAKE_EXE_LINKER_FLAGS "-ldl")
set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_arcade ${sources})

add_library(ncurses_lib ${lib_ncurse_sources})
add_library(sfml_lib ${lib_sfml_sources})