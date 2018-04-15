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
}

__attribute__((destructor))
void out()
{
	delete ret;
}


extern "C" Arcade::IGraphicLib *entryPoint()
{
	return ret;
}
