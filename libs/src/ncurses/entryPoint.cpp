/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** entryPoint.cpp
*/

#include <iostream>
#include "../IGraphicLib.hpp"

/* "Arcade::SFML" : For example, use the class of your lib */
//Arcade::SFML *ret = nullptr;

__attribute__((constructor))
void enter()
{
	/* Again, it's for example, use the class of your lib */
//	ret = new Arcade::SFML;
	std::cout << "Constructor of the testLib" << std::endl;
}

__attribute__((destructor))
void out()
{
	std::cout << "Desctructor of the testLib" << std::endl;
//	delete ret;
}


extern "C" Arcade::IGraphicLib *entryPoint()
{
//	return ret;
	std::cout << "entryPoint of the testLib" << std::endl;
	return nullptr;
}
