/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** entryPoint.cpp
*/

#include <iostream>
#include "LibNcurses.hpp"

/* "Arcade::SFML" : For example, use the class of your lib */
Arcade::IGraphicLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	/* Again, it's for example, use the class of your lib */
	ret = new Arcade::LibNcurses({0, 0}, "Arcade");
	std::cout << "Constructor of the ncurses" << std::endl;
}

__attribute__((destructor))
void out()
{
	std::cout << "Desctructor of the ncurses" << std::endl;
	delete ret;
}


extern "C" Arcade::IGraphicLib *entryPoint()
{
	std::cout << "entryPoint of the ncurses" << std::endl;
	return ret;
}
