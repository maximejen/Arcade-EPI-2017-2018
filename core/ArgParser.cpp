/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** ArgParser.cpp
*/

#include <iostream>
#include <fstream>
#include "ArgParser.hpp"

Arcade::ArgParser::ArgParser()
= default;

int Arcade::ArgParser::parseArgs(int argc, char **argv)
{
	std::string path;
	int ret = 0;

	if (argc != 2)
		return -1;
	path = argv[1];
	std::ifstream lib(path);
	if (lib.fail())
		ret = 84;
	return ret;
}
