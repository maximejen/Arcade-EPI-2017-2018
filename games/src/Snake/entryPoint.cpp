/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** entryPoint.cpp
*/

#include <iostream>
#include "LibSnake.hpp"

/* "Arcade::SFML" : For example, use the class of your lib */
Arcade::IGameLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	/* Again, it's for example, use the class of your lib */
	ret = new Arcade::LibSnake;
}

__attribute__((destructor))
void out()
{
	delete ret;
}


extern "C" Arcade::IGameLib *entryPoint()
{
	return ret;
}
