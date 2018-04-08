/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Core.cpp
*/

#include <cstdio>
#include <iostream>
#include <dirent.h>
#include <regex>
#include <cstdlib>
#include "Core.hpp"
#include "LogicException.hpp"

static const std::regex REGEX("^[a-zA-Z0-9_]*.so");

Arcade::Core::Core(const std::string &libPath) : selectedGame(0),
						 selectedLib(0)
{
	this->libraryPathes.push_back(libPath);
	this->parseLibDir();
	this->parseGameDir();
	this->selectedLib = 0;
	this->selectedGame = 0;
	this->playerName = new PlayerName;
}

Arcade::Core::~Core()
{

}

// this function read the libDir and get all the libs in the direcotry.
void Arcade::Core::parseLibDir()
{
	struct dirent **namelist;
	int n = scandir("./libs", &namelist, nullptr, alphasort);

	if (n < 0) {
		perror("scandir");
		return;
	}
	for (int i = 0 ; i < n ; i++) {
		std::cmatch cm;
		std::string name = namelist[i]->d_name;
		if (std::regex_match(name.c_str(), cm, REGEX) &&
		    std::find(this->libraryPathes.begin(),
			      this->libraryPathes.end(), "./libs/" + name) ==
		    this->libraryPathes.end()) {
			this->libraryPathes.push_back("./libs/" + name);
		}
		free(namelist[i]);
	}
}

// same as the function above
void Arcade::Core::parseGameDir()
{
	struct dirent **namelist;
	int n = scandir("./games", &namelist, nullptr, alphasort);
	if (n < 0) {
		perror("scandir");
		return;
	}
	for (int i = 0 ; i < n ; i++) {
		std::cmatch cm;
		std::string name = namelist[i]->d_name;
		if (std::regex_match(name.c_str(), cm, REGEX)) {
			this->gamePathes.push_back("games/" + name);
		}
		free(namelist[i]);
	}
}

int Arcade::Core::startArcade()
{
	Keys key = Keys::NONE;
	if (this->libraryPathes.empty() || this->gamePathes.empty())
		throw Arcade::LogicException("Error while parsing libs.");
	this->graphLoader.loadLib(this->libraryPathes[this->selectedLib]);
	this->gameLoader.loadLib(this->gamePathes[this->selectedGame]);
	auto graphLib = this->graphLoader.getLibInstance();
	auto gameLib = this->gameLoader.getLibInstance();
	this->playerName->setPlayerName(*graphLib);
//	if (!gameLib)
//		std::cout << "No games loaded" << std::endl;
	while (1) {
		if (this->arcadeLoop(graphLib, gameLib, key) == 0)
			return 0;
	}
	return 1;
}

int Arcade::Core::arcadeLoop(IGraphicLib *graphLib, IGameLib *gameLib, Keys key)
{
	while (graphLib->pollEvents()) {
		key = graphLib->getLastEvent();
		if (key == Arcade::Keys::ESC) {
			this->graphLoader.unloadLib();
			return 0;
		}
		this->checkEvents(key, graphLib, gameLib);
		gameLib->applyEvent(key);
	}
	gameLib->update();
	gameLib->refresh(*graphLib);
	return 1;
}

const Arcade::GameLibLoader &Arcade::Core::getGameLoader() const
{
	return gameLoader;
}

void Arcade::Core::setGameLoader(const Arcade::GameLibLoader &gameLoader)
{
	Core::gameLoader = gameLoader;
}

const Arcade::GraphLibLoader &Arcade::Core::getGraphLoader() const
{
	return graphLoader;
}

void Arcade::Core::setGraphLoader(const Arcade::GraphLibLoader &graphLoader)
{
	Core::graphLoader = graphLoader;
}

void Arcade::Core::checkEvents(Arcade::Keys key, IGraphicLib *&graphicLib,
	IGameLib *&gameLib)
{
	if (key == Arcade::Keys::I) {
		size_t size = this->libraryPathes.size();
		this->graphLoader.unloadLib();
		this->selectedLib++;
		this->graphLoader.loadLib(
			this->libraryPathes[this->selectedLib % size]);
		graphicLib = this->graphLoader.getLibInstance();
	}
	if (key == Arcade::Keys::O) {
		size_t size = this->gamePathes.size();
		this->gameLoader.unloadLib();
		this->selectedGame++;
		this->gameLoader.loadLib(
			this->gamePathes[this->selectedGame % size]);
		gameLib = this->gameLoader.getLibInstance();
	}
}
