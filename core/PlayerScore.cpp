/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**        ${Description}
*/

#include "PlayerScore.hpp"
#include <unistd.h>

static const std::string INFOMSG= "Enter you Nickname, Press enter when done Press Escape to exit";

Arcade::PlayerScore::PlayerScore()
{
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	this->playerName.clear();
	this->timer = t1;
}

bool Arcade::PlayerScore::setPlayerName(IGraphicLib &graphLib)
{
	Keys curKey = Keys::NONE;
	Vect<size_t> size = graphLib.getScreenSize();
	Arcade::TextBox text("Name ", {size.getX() / 3, size.getY() / 3}, 25);
	std::cerr << size.getX() << std::endl;

	std::cerr << size.getX() / 3 << std::endl;
	Arcade::TextBox info(INFOMSG, {50, size.getY() / 2}, 20);
	while (curKey != Keys::DOWN) {
		while (graphLib.pollEvents()) {
			curKey = graphLib.getLastEvent();
			if (endEntry(curKey))
				return true;
			if (!this->endescape(curKey))
				return false;
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

bool Arcade::PlayerScore::endescape(Keys curKey)
{
	if (curKey == Keys::ESC) {
		return false;
	}
	return true;
}

bool Arcade::PlayerScore::endEntry(Keys curKey)
{
	if (curKey == Keys::SPACE)
		return true;
	return false;
}

void Arcade::PlayerScore::addNewLetter(Keys curKey)
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

std::string Arcade::PlayerScore::getPlayerName() const
{
	return this->playerName;
}

void Arcade::PlayerScore::openScore()
{
	std::ifstream file;
	std::string line;

	file.open("score.txt", std::ifstream::in);
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
		this->score.insert(std::pair<int ,std::string>(std::stoi(line.substr(line.find(" "))), line.substr(0, line.find(" "))));
	}
}

bool Arcade::PlayerScore::writeScoreInFile()
{
	this->openScore();
	if (this->playerName == "")
		this->playerName = "Unknow_Player";
	this->score.insert(std::pair<int, std::string>(this->curScore, this->playerName));

	std::ofstream outputFile;
	outputFile.open("score.txt");

	for(auto it = this->score.cbegin(); it != this->score.cend(); ++it)
	{
		outputFile << it->second << " " << it->first << std::endl;
		std::cout << it->first << " " << it->second << "\n";
	}
	return true;
}

void Arcade::PlayerScore::setScore(int score)
{
	this->curScore = score;
}