/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**        ${Description}
*/
#ifndef CPP_ARCADE_SCOREMANAGER_HPP
#define CPP_ARCADE_SCOREMANAGER_HPP

#include "../libs/src/IGraphicLib.hpp"
#include <iostream>
#include <ios>
#include <chrono>
#include <fstream>
#include <map>

namespace Arcade {
	class ScoreManager {
	public:
		ScoreManager();
		void printScore(IGraphicLib &graphLib);

	private:
		void printPlayers(IGraphicLib &graphLib);
		std::chrono::steady_clock::time_point timer;
		std::map<int, std::string> score;


	};
}

#endif //CPP_ARCADE_SCOREMANAGER_HPP
