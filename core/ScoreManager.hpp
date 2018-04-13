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
		std::cout << line << std::endl;
		this->score.insert(std::pair<int ,std::string>(std::stoi(line.substr(line.find(" "))), line.substr(0, line.find(" "))));
	}
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
		}
	}
	//Arcade::TextBox text("Graphics", { size.getX() / 2, size.getY() / 6}, 25);

}

void Arcade::ScoreManager::printPlayers(IGraphicLib &graphLib)
{
	for(auto it = this->score.cbegin(); it != this->score.cend(); ++it) {
		Arcade::TextBox text("Graphics", { size.getX() / 2, size.getY() / 6}, 25);

	}

}