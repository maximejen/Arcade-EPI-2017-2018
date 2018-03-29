/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** main.cpp
*/

#include "core/ArgParser.hpp"

int main(int argc, char **argv)
{
	if (Arcade::ArgParser::parseArgs(argc, argv) == -1)
		return (84);
}