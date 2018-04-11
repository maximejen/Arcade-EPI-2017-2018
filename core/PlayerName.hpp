/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**        ${Description}
*/
#ifndef CPP_ARCADE_PLAYERNAME_HPP
#define CPP_ARCADE_PLAYERNAME_HPP

#include <iostream>
#include <ios>
#include <string>
#include "Keys.hpp"
#include "../libs/src/IGraphicLib.hpp"
#include <chrono>

namespace Arcade {
	class PlayerName {
	public:
		PlayerName();
		bool setPlayerName(IGraphicLib &);
		std::string getPlayerName() const;

	private:
		bool endescape(Keys curKey);
		std::string playerName;
		void addNewLetter(Keys);
		bool endEntry(Keys curKey);
		std::chrono::steady_clock::time_point timer;

	};
}

#endif //CPP_ARCADE_PLAYERNAME_HPP
