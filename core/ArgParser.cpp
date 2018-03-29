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
		ret = -1;
	std::ifstream lib(argv[1]);
	if (lib.fail())
		ret = -1;
	return ret;
}
