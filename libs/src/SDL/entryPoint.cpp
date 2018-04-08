/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** ${Description}
*/

#include <iostream>
#include "LibSDL.hpp"

Arcade::IGraphicLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Arcade::LibSDL({800, 800}, "Arcade");
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