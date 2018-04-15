/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
**        ${Description}
*/

#include "ScoreManager.hpp"

Arcade::ScoreManager::ScoreManager()
{
	std::ifstream file;
	std::string line;

	file.open("score.txt", std::ifstream::in);
	while (std::getline(file, line)) {
		if (std::regex_match(line, std::regex("^[a-zA-Z_]{0,} [0-9]{0,}"))) {
			this->score.insert(std::pair<int ,std::string>(std::stoi(line.substr(line.find(" "))), line.substr(0, line.find(" "))));
		}
	}
	std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	this->timer = t1;
}

void Arcade::ScoreManager::printScore(IGraphicLib &graphLib)
{
	Keys curKey = Keys::NONE;

	while (curKey != Keys::SPACE) {
		while (graphLib.pollEvents()) {
			curKey = graphLib.getLastEvent();
		}
		std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - this->timer);
		if (time_span.count() >= 0.2) {
			graphLib.clearWindow();
			this->printPlayers(graphLib);
			graphLib.refreshWindow();
			this->timer = t2;
		}
	}

}

void Arcade::ScoreManager::printPlayers(IGraphicLib &graphLib)
{
	Vect<size_t> size = graphLib.getScreenSize();

	size_t pos = 0;
	size_t inc = size.getY() / 25;
	for(auto it = this->score.cbegin(); it != this->score.cend(); ++it) {
		Arcade::TextBox text(it->second + " : " + std::to_string(it->first), {size.getX() / 2, size.getY() / 5 + pos}, 25);
		pos += inc;
		graphLib.drawText(text);
	}
}