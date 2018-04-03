/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Core.cpp
*/

#include "Core.hpp"

Arcade::Core::Core()
{
}

Arcade::Core::Core(const std::string &path)
{
	this->libraryPathes.push_back(path);
}

Arcade::Core::~Core()
{

}

// this function read the libDir and get all the libs in the direcotry.
void Arcade::Core::parseLibDir()
{

}
// same as the function above
void Arcade::Core::parseGameDir()
{

}

Arcade::IGraphicLib *Arcade::Core::getActualLib() const
{
	return actualLib;
}

void Arcade::Core::setActualLib(Arcade::IGraphicLib *actualLib)
{
	Core::actualLib = actualLib;
}

Arcade::IGameLib *Arcade::Core::getActualGame() const
{
	return actualGame;
}

void Arcade::Core::setActualGame(Arcade::IGameLib *actualGame)
{
	Core::actualGame = actualGame;
}

int Arcade::Core::startArcade()
{
	return 0;
}
