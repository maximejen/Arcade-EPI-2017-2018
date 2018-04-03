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

static const std::regex REGEX("^[a-z0-9]*.so");

Arcade::Core::Core() : selectedGame(0), selectedLib(0)
{
	this->parseLibDir();
	this->parseGameDir();
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
			      this->libraryPathes.end(), name) ==
		    this->libraryPathes.end()) {
			std::cout << name << std::endl;
			this->libraryPathes.push_back(name);
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
		if (std::regex_match(name.c_str(), cm, REGEX) &&
		    std::find(this->libraryPathes.begin(),
			      this->libraryPathes.end(), name) ==
		    this->libraryPathes.end()) {
			std::cout << name << std::endl;
			this->gamePathes.push_back(name);
		}
		free(namelist[i]);
	}
}

int Arcade::Core::startArcade()
{
	if (this->libraryPathes.empty() || this->gamePathes.empty())
		throw Arcade::LogicException("Error while parsing libs.");
	this->graphLoader.loadLib(this->libraryPathes[this->selectedLib]);
	this->gameLoader.loadLib(this->gamePathes[this->selectedGame]);
	auto graphLib = this->graphLoader.getLibInstance();
	while (1) {
		this->arcadeLoop(graphLib);
	}
	return 1;
}

int Arcade::Core::arcadeLoop(IGraphicLib *graphLib)
{
	while (graphLib->pollEvents()) {
		// Todo : check if event concerns the Core, then declare the Event to the Game
	}
	// Todo : Update and then refresh the game.
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
