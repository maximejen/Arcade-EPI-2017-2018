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
#include <map>
#include <fstream>

namespace Arcade {
	class PlayerScore {
	public:
		PlayerScore();
		bool setPlayerName(IGraphicLib &);
		std::string getPlayerName() const;
		bool writeScoreInFile();
		void setScore(int score);

	private:
		bool endescape(Keys curKey);
		std::string playerName;
		void addNewLetter(Keys);
		bool endEntry(Keys curKey);
		std::chrono::steady_clock::time_point timer;
		std::map<int, std::string> score;
		void openScore();
		int curScore;

	};
}

#endif //CPP_ARCADE_PLAYERNAME_HPP
