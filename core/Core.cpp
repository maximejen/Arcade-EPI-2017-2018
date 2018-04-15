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
	this->playerName = new PlayerScore;
	this->menuManager = new MenuManager;
	this->scoreManager = new ScoreManager;
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

bool Arcade::Core::initMenu()
{
	std::string lib;

	this->menuManager->setLibPath(this->gamePathes, this->libraryPathes);
	lib = this->menuManager->printMenu(*this->graphlib);
	if (lib != "") {
		if (std::find(this->gamePathes.begin(), this->gamePathes.end(), lib) != this->gamePathes.end()) {
			this->gameLoader.unloadLib();
			if (!this->gameLoader.loadLib(lib))
				return false;
			this->gameLib = this->gameLoader.getLibInstance();

		}
		else if (std::find(this->libraryPathes.begin(), this->libraryPathes.end(), lib) != this->libraryPathes.end()) {
			this->graphLoader.unloadLib();
			if (!this->graphLoader.loadLib(lib))
				return false;
			this->graphlib= this->graphLoader.getLibInstance();

		}
	} else
		return false;
	this->menuManager->ScrenStart(*this->graphlib);
	return true;
}

int Arcade::Core::startArcade()
{
	bool ctn = true;

	Keys key = Keys::NONE;
	if (this->libraryPathes.empty() || this->gamePathes.empty())
		throw Arcade::LogicException("Error while parsing libs.");
	if (!this->graphLoader.loadLib(this->libraryPathes[this->selectedLib]))
		return 0;
	if (!this->gameLoader.loadLib(this->gamePathes[this->selectedGame]))
		return 0;
	this->graphlib= this->graphLoader.getLibInstance();
	this->gameLib = this->gameLoader.getLibInstance();
	if (!this->playerName->setPlayerName(*this->graphlib))
		return false;
	if (!this->initMenu())
		return 1;
	while (ctn) {
		if (this->arcadeLoop(key) == 0)
			ctn = false;
	}
	this->playerName->setScore(this->gameLib->getScore());
	this->playerName->writeScoreInFile();
	this->gameLoader.unloadLib();
	this->graphLoader.unloadLib();
	return 1;
}

int Arcade::Core::arcadeLoop(Keys key)
{
	while (this->graphlib->pollEvents()) {
		key = this->graphlib->getLastEvent();
		if (key == Arcade::Keys::ESC)
			return 0;
		if (key == Arcade::Keys::M)
			this->initMenu();
		if (key == Arcade::Keys::P)
			this->scoreManager->printScore(*this->graphlib);
		this->checkEvents(key);
		gameLib->applyEvent(key);
	}
	if (this->gameLib->stop() && !this->initMenu())
		return 0;
	this->gameLib->update();
	this->gameLib->refresh(*this->graphlib);
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

bool Arcade::Core::checkEvents(Arcade::Keys key)
{
	if (key == Arcade::Keys::I) {
		size_t size = this->libraryPathes.size();
		this->graphLoader.unloadLib();
		this->selectedLib++;
		this->graphLoader.loadLib(
			this->libraryPathes[this->selectedLib % size]);
		this->graphlib = this->graphLoader.getLibInstance();
		std::cout << "Switch to : " << this->graphlib->getName() << std::endl;
		return false;
	}
	if (key == Arcade::Keys::O) {
		this->playerName->setScore((int)this->gameLib->getScore());
		size_t size = this->gamePathes.size();
		this->gameLoader.unloadLib();
		this->selectedGame++;
		this->gameLoader.loadLib(
			this->gamePathes[this->selectedGame % size]);
		this->gameLib = this->gameLoader.getLibInstance();
		this->gameLib->init();
		this->playerName->writeScoreInFile();
		return false;
	}
	return true;
}
