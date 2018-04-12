/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**        ${Description}
*/

#include "PlayerName.hpp"
#include <unistd.h>

static const std::string INFOMSG= "Enter you Nickname, Press enter when done Press Escape to exit";

Arcade::PlayerName::PlayerName()
{
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	this->playerName.clear();
	this->timer = t1;
}

bool Arcade::PlayerName::setPlayerName(IGraphicLib &graphLib)
{
	Keys curKey = Keys::NONE;
	Vect<size_t> size = graphLib.getScreenSize();
	Arcade::TextBox text("Name ", {size.getY() / 5, size.getX() / 3}, 25);
	Arcade::TextBox info(INFOMSG, {size.getY() / 2, 50}, 20);
	while (curKey != Keys::DOWN) {
		while (graphLib.pollEvents()) {
			if (endEntry(curKey))
				return true;
			if (!this->endescape(curKey))
				return false;
			curKey = graphLib.getLastEvent();
				this->addNewLetter(curKey);
		}
		text.setValue("Name: " + this->playerName);
		std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - this->timer);
		if (time_span.count() >= 0.2) {
			graphLib.clearWindow();
			graphLib.drawText(text);
			graphLib.drawText(info);
			graphLib.refreshWindow();
			this->timer = t2;
		}
	}
	return true;
}

bool Arcade::PlayerName::endescape(Keys curKey)
{
	if (curKey == Keys::ESC)
		return false;
	return true;
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
		this->playerName = this->playerName.substr(0,
							   this->playerName.size() -
							   1);
	else if (this->playerName.size() < 13){
		val = curKey + 96;
		if (val >= 96 && val <= 122)
			this->playerName += val;
	}
}

std::string Arcade::PlayerName::getPlayerName() const
{
	return this->playerName;
}