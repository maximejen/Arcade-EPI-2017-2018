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

namespace Arcade {
	class PlayerName {
	public:
		PlayerName();
		void setPlayerName(IGraphicLib &);
		std::string getPlayerName() const;

	private:
		std::string playerName;
		void addNewLetter(Keys);
		bool endEntry(Keys curKey);
	};
}

#endif //CPP_ARCADE_PLAYERNAME_HPP
