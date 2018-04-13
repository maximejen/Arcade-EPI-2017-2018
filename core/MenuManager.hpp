/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**        ${Description}
*/
#ifndef CPP_ARCADE_MENUMANAGER_HPP
#define CPP_ARCADE_MENUMANAGER_HPP

#include <iostream>
#include <vector>
#include "../libs/src/IGraphicLib.hpp"
#include "../games/src/IGameLib.hpp"
#include <chrono>

namespace Arcade {
	class MenuManager {
	public:
		MenuManager();
		void setLibPath(std::vector<std::string> &gameLib, std::vector<std::string> &graphLib);
		std::string printMenu(IGraphicLib &graphLib);
		void ScrenStart(IGraphicLib &graphLib);

	private:
		void printGameLib(IGraphicLib &graphLib, Vect<size_t> size);
		void printGraphLib(IGraphicLib &graphLib, Vect<size_t> size);
		void moveCursos(Keys key);
		bool canMoveDown();
		std::string returnValue();
		std::pair<int, int> cursPos;
		std::vector<std::string> gameLib;
		std::vector<std::string> graphLib;
		std::chrono::steady_clock::time_point timer;
	};
}

#endif //CPP_ARCADE_MENUMANAGER_HPP
