/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**        ${Description}
*/

#include "PlayerName.hpp"
#include <unistd.h>

Arcade::PlayerName::PlayerName()
{

}

void Arcade::PlayerName::setPlayerName(IGraphicLib &graphLib)
{
	Keys curKey = Keys::NONE;
	Vect<size_t> size = graphLib.getScreenSize();
	Arcade::TextBox text("Name ", {size.getY() / 2, size.getX() / 3 }, 25, {120, 120,120, 120}, {255, 255, 255, 255});
	bool in = true;
	while (curKey != Keys::DOWN) {
		graphLib.clearWindow();
		while (graphLib.pollEvents()) {
			if (endEntry(curKey))
				return;
			curKey = graphLib.getLastEvent();
			if (in) {
				this->addNewLetter(curKey);
				in = false;
			} else
				in = true;
		}
		text.setValue("Name: " + this->playerName);
		graphLib.drawText(text);
	}
}

bool Arcade::PlayerName::endEntry(Keys curKey)
{
	if (curKey == Keys::SPACE)
		return true;
	return false;
}

void Arcade::PlayerName::addNewLetter(Keys curKey)
{
	char val;
	if (curKey == Keys::BACKSPACE)
		this->playerName = this->playerName.substr(0, this->playerName.size() -1);
	else {
		std::cout << curKey << std::endl;
		val = curKey + 96;
		if (val >= 96 && val <= 122)
			this->playerName += val;
	}
}

std::string Arcade::PlayerName::getPlayerName() const
{
	return this->playerName;
}