/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Core.hpp
*/

#ifndef CPP_ARCADE_CORE_HPP
	#define CPP_ARCADE_CORE_HPP

	#include <string>
	#include <vector>
	#include "../libs/src/IGraphicLib.hpp"
	#include "../games/src/IGameLib.hpp"

namespace Arcade {
	// The core will be initialized by the main, then it will handle the program
	// The purpose of the Core is to handle the main loop for the program
	// Then load the actual lib chosen by the user and load the other libs when needed.
	// Then Core will call the function to render the game and then the lib function to do when the game "asks"

	// The core will get the events and "declare" them to the game.
	class Core {
	public:
		// path => the path to the lib given by the user in argument.
		// Error handling not necessary done, so need to do it then continue or not.
		explicit Core(const std::string &path);
		Core();
		~Core();

		// Begin of the Core and the program.
		int startArcade();
		// find all the graph libs (.so files) in the /libs folder and fill the libraryPathes mem
		void parseLibDir();
		// find all the games (.so files) in the /games folder and fill the gamePathes mem
		void parseGameDir();
		IGraphicLib *getActualLib() const;
		void setActualLib(IGraphicLib *actualLib);
		IGameLib *getActualGame() const;
		void setActualGame(IGameLib *actualGame);


	private:
		std::vector<std::string> libraryPathes;
		std::vector<std::string> gamePathes;
		IGraphicLib *actualLib;
		IGameLib *actualGame;
	};
}


#endif //CPP_ARCADE_CORE_HPP
