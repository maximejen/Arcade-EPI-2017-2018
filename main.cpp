/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** main.cpp
*/

#include <iostream>
#include "core/ArgParser.hpp"
#include "core/DlLoader.hpp"

static const char *HELP_MESSAGE = "BINARY NAME :\n"
	"\tarcade\n"
	"\nUSAGE :\n"
	"\t./arcade [path]\n"
	"\n\tpath : Path to a graphic lib to start the arcade bin.\n"
	"\tThe file should be a .so file.\n"
	"\nDESCRIPTION :\n"
	"\tThe arcade project has the purpose to "
	"load with any graphical lib in C++\n"
	"\tany game that you can find in the /games folder.\n"
	"\n\tin the /libs folder, you will find the libs loadable"
	" by the arcade project.\n"
	"\tin the /games folder, the games you can play with "
	"any loadable lib.\n"
	"\nABOUT :\n"
	"\tFor more information, see the documentation of "
	"the project in the folder.\n";

// here we need to create the core, then launch the program with the lib
// given in argument by the user
int main(int argc, char **argv)
{
	int ret = 0;
	Arcade::DlLoader loader;

	if ((ret = Arcade::ArgParser::parseArgs(argc, argv)) != 0) {
		std::cout << HELP_MESSAGE << std::endl;
	}
	if (ret == 0) {
		loader.loadLib(argv[1]);
		loader.unloadLib();
	}
	return ret;
}